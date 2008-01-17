/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: recordparser.cxx,v $
 *
 *  $Revision: 1.2 $
 *
 *  last change: $Author: rt $ $Date: 2008-01-17 08:05:50 $
 *
 *  The Contents of this file are made available subject to
 *  the terms of GNU Lesser General Public License Version 2.1.
 *
 *
 *    GNU Lesser General Public License Version 2.1
 *    =============================================
 *    Copyright 2005 by Sun Microsystems, Inc.
 *    901 San Antonio Road, Palo Alto, CA 94303, USA
 *
 *    This library is free software; you can redistribute it and/or
 *    modify it under the terms of the GNU Lesser General Public
 *    License version 2.1, as published by the Free Software Foundation.
 *
 *    This library is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *    Lesser General Public License for more details.
 *
 *    You should have received a copy of the GNU Lesser General Public
 *    License along with this library; if not, write to the Free Software
 *    Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 *    MA  02111-1307  USA
 *
 ************************************************************************/

#include "oox/core/recordparser.hxx"
#include <com/sun/star/lang/DisposedException.hpp>
#include <com/sun/star/xml/sax/XLocator.hpp>
#include <cppuhelper/implbase1.hxx>
#include "oox/helper/recordinputstream.hxx"
#include "oox/core/fragmenthandler.hxx"

using ::rtl::OUString;
using ::com::sun::star::uno::Reference;
using ::com::sun::star::uno::RuntimeException;
using ::com::sun::star::lang::DisposedException;
using ::com::sun::star::io::XInputStream;
using ::com::sun::star::io::IOException;
using ::com::sun::star::xml::sax::SAXException;
using ::com::sun::star::xml::sax::XLocator;

namespace oox {
namespace core {

// ============================================================================

namespace prv {

class Locator : public ::cppu::WeakImplHelper1< XLocator >
{
public:
    inline explicit         Locator( RecordParser* pParser ) : mpParser( pParser ) {}

    void                    dispose();
    void                    checkDispose() throw( RuntimeException );

    // com.sun.star.sax.XLocator interface

    virtual sal_Int32 SAL_CALL getColumnNumber() throw( RuntimeException );
    virtual sal_Int32 SAL_CALL getLineNumber() throw( RuntimeException );
    virtual OUString SAL_CALL getPublicId() throw( RuntimeException );
    virtual OUString SAL_CALL getSystemId() throw( RuntimeException );

private:
    RecordParser*           mpParser;
};

// ----------------------------------------------------------------------------

void Locator::dispose()
{
    mpParser = 0;
}

void Locator::checkDispose() throw( RuntimeException )
{
    if( !mpParser )
        throw DisposedException();
}

sal_Int32 SAL_CALL Locator::getColumnNumber() throw( RuntimeException )
{
    return -1;
}

sal_Int32 SAL_CALL Locator::getLineNumber() throw( RuntimeException )
{
    return -1;
}

OUString SAL_CALL Locator::getPublicId() throw( RuntimeException )
{
    checkDispose();
    return mpParser->getInputSource().maPublicId;
}

OUString SAL_CALL Locator::getSystemId() throw( RuntimeException )
{
    checkDispose();
    return mpParser->getInputSource().maSystemId;
}

// ============================================================================

class ContextStack
{
public:
    explicit            ContextStack( FragmentHandlerRef xHandler );

    inline bool         empty() const { return maStack.empty(); }

    sal_Int32           getCurrentRecId() const;
    bool                hasCurrentEndRecId() const;
    RecordContextRef    getCurrentContext() const;

    void                pushContext( const RecordInfo& rRec, const RecordContextRef& rxContext );
    void                popContext();

private:
    typedef ::std::pair< RecordInfo, RecordContextRef > ContextInfo;
    typedef ::std::vector< ContextInfo >                ContextInfoVec;

    FragmentHandlerRef  mxHandler;
    ContextInfoVec      maStack;
};

// ----------------------------------------------------------------------------

ContextStack::ContextStack( FragmentHandlerRef xHandler ) :
    mxHandler( xHandler )
{
}

sal_Int32 ContextStack::getCurrentRecId() const
{
    return maStack.empty() ? -1 : maStack.back().first.mnStartRecId;
}

bool ContextStack::hasCurrentEndRecId() const
{
    return !maStack.empty() && (maStack.back().first.mnEndRecId >= 0);
}

RecordContextRef ContextStack::getCurrentContext() const
{
    if( !maStack.empty() )
        return maStack.back().second;
    return mxHandler.get();
}

void ContextStack::pushContext( const RecordInfo& rRecInfo, const RecordContextRef& rxContext )
{
    OSL_ENSURE( (rRecInfo.mnEndRecId >= 0) || maStack.empty() || hasCurrentEndRecId(),
        "ContextStack::pushContext - nested incomplete context record identifiers" );
    maStack.push_back( ContextInfo( rRecInfo, rxContext ) );
}

void ContextStack::popContext()
{
    OSL_ENSURE( !maStack.empty(), "ContextStack::popContext - no context on stack" );
    if( !maStack.empty() )
    {
        ContextInfo& rContextInfo = maStack.back();
        if( rContextInfo.second.is() )
            rContextInfo.second->endRecord( rContextInfo.first.mnStartRecId );
        maStack.pop_back();
    }
}

} // namespace prv

// ============================================================================

namespace {

/** Reads a byte from the passed stream, returns true on success. */
inline bool lclReadByte( sal_uInt8& ornByte, BinaryInputStream& rStrm )
{
    return rStrm.read( &ornByte, 1 ) == 1;
}

/** Reads a compressed signed 32-bit integer from the passed stream. */
bool lclReadCompressedInt( sal_Int32& ornValue, BinaryInputStream& rStrm )
{
    ornValue = 0;
    sal_uInt8 nByte;
    if( !lclReadByte( nByte, rStrm ) ) return false;
    ornValue = nByte & 0x7F;
    if( (nByte & 0x80) == 0 ) return true;
    if( !lclReadByte( nByte, rStrm ) ) return false;
    ornValue |= sal_Int32( nByte & 0x7F ) << 7;
    if( (nByte & 0x80) == 0 ) return true;
    if( !lclReadByte( nByte, rStrm ) ) return false;
    ornValue |= sal_Int32( nByte & 0x7F ) << 14;
    if( (nByte & 0x80) == 0 ) return true;
    if( !lclReadByte( nByte, rStrm ) ) return false;
    ornValue |= sal_Int32( nByte & 0x7F ) << 21;
    return true;
}

bool lclReadRecordHeader( sal_Int32& ornRecId, sal_Int32& ornRecSize, BinaryInputStream& rStrm )
{
    return
        lclReadCompressedInt( ornRecId, rStrm ) && (ornRecId >= 0) &&
        lclReadCompressedInt( ornRecSize, rStrm ) && (ornRecSize >= 0);
}

bool lclReadNextRecord( sal_Int32& ornRecId, RecordDataSequence& orData, BinaryInputStream& rStrm )
{
    sal_Int32 nRecSize = 0;
    bool bValid = lclReadRecordHeader( ornRecId, nRecSize, rStrm );
    if( bValid )
    {
        orData.realloc( nRecSize );
        bValid = (nRecSize == 0) || (rStrm.read( orData, nRecSize ) == nRecSize);
    }
    return bValid;
}

} // namespace

// ============================================================================

RecordParser::RecordParser()
{
    mxLocator.set( new prv::Locator( this ) );
}

RecordParser::~RecordParser()
{
    if( mxLocator.is() )
        mxLocator->dispose();
}

void RecordParser::setFragmentHandler( const ::rtl::Reference< FragmentHandler >& rxHandler )
{
    mxHandler = rxHandler;
}

void RecordParser::setRecordInfoProvider( const RecordInfoProviderRef& rxProvider )
{
    mxRecInfoProvider = rxProvider;
}

void RecordParser::parseStream( const RecordInputSource& rInputSource ) throw( SAXException, IOException, RuntimeException )
{
    maSource = rInputSource;

    if( !maSource.mxInStream || !maSource.mxInStream->is() )
        throw IOException();
    if( !mxHandler.is() )
        throw SAXException();
    if( !mxRecInfoProvider )
        throw RuntimeException();

    // start the document
    Reference< XLocator > xLocator( mxLocator.get() );
    mxHandler->setDocumentLocator( xLocator );
    mxHandler->startDocument();

    // parse the stream
    mxStack.reset( new prv::ContextStack( mxHandler ) );
    sal_Int32 nRecId = 0;
    RecordDataSequence aRecData;
    while( lclReadNextRecord( nRecId, aRecData, *maSource.mxInStream ) )
    {
        // create record stream object from imported record data
        RecordInputStream aRecStrm( aRecData );
        // try to leave a context, there may be other incomplete contexts on the stack
        if( const RecordInfo* pEndRecInfo = mxRecInfoProvider->getEndRecordInfo( nRecId ) )
        {
            (void)pEndRecInfo; // shut warning up in non-debug
            // finalize contexts without record identifier for context end
            while( !mxStack->empty() && !mxStack->hasCurrentEndRecId() )
                mxStack->popContext();
            // finalize the current context and pop context info from stack
            OSL_ENSURE( mxStack->getCurrentRecId() == pEndRecInfo->mnStartRecId, "RecordParser::parseStream - context records mismatch" );
            (void)pEndRecInfo;  // suppress compiler warning for unused variable
            RecordContextRef xCurrContext = mxStack->getCurrentContext();
            if( xCurrContext.is() )
            {
                // context end record may contain some data, handle it as simple record
                aRecStrm.seek( 0 );
                xCurrContext->startRecord( nRecId, aRecStrm );
                xCurrContext->endRecord( nRecId );
            }
            mxStack->popContext();
        }
        else
        {
            // end context with incomplete record id, if the same id comes again
            if( (mxStack->getCurrentRecId() == nRecId) && !mxStack->hasCurrentEndRecId() )
                mxStack->popContext();
            // try to start a new context
            RecordContextRef xCurrContext = mxStack->getCurrentContext();
            if( xCurrContext.is() )
            {
                aRecStrm.seek( 0 );
                xCurrContext = xCurrContext->createRecordContext( nRecId, aRecStrm );
            }
            // track all context identifiers on the stack (do not push simple records)
            const RecordInfo* pStartRecInfo = mxRecInfoProvider->getStartRecordInfo( nRecId );
            if( pStartRecInfo )
                mxStack->pushContext( *pStartRecInfo, xCurrContext );
            // import the record
            if( xCurrContext.is() )
            {
                // import the record
                aRecStrm.seek( 0 );
                xCurrContext->startRecord( nRecId, aRecStrm );
                // end simple records (context records are finished in ContextStack::popContext)
                if( !pStartRecInfo )
                    xCurrContext->endRecord( nRecId );
            }
        }
    }
    // close remaining contexts (missing context end records or stream error)
    while( !mxStack->empty() )
        mxStack->popContext();
    mxStack.reset();

    // finish document
    mxHandler->endDocument();

    maSource = RecordInputSource();
}

void RecordParser::pushContext( sal_Int32 nRecId, const RecordContextRef& rxContext )
{
    const RecordInfo* pRecInfo = mxRecInfoProvider->getStartRecordInfo( nRecId );
    OSL_ENSURE( pRecInfo, "RecordParser::pushContext - invalid record identifier" );
    OSL_ENSURE( (pRecInfo->mnEndRecId >= 0) || mxStack->empty() || mxStack->hasCurrentEndRecId(),
        "RecordParser::pushContext - nested incomplete context record identifiers" );
    mxStack->pushContext( *pRecInfo, rxContext );
    if( rxContext.is() )
    {
        RecordDataSequence aEmptyData;
        RecordInputStream aRecStrm( aEmptyData );
        rxContext->startRecord( nRecId, aRecStrm );
    }
}

void RecordParser::popContext()
{
    mxStack->popContext();
}

// ============================================================================

} // namespace core
} // namespace oox

