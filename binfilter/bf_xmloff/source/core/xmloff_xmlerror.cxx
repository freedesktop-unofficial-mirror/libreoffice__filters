/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: xmloff_xmlerror.cxx,v $
 *
 *  $Revision: 1.3 $
 *
 *  last change: $Author: rt $ $Date: 2005-09-09 07:46:14 $
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

#ifndef _XMLOFF_XMLERROR_HXX
#include "xmlerror.hxx"
#endif

#ifndef _TOOLS_DEBUG_HXX
#include <tools/debug.hxx>
#endif

// auto strip #ifndef _RTL_USTRING_HXX_
// auto strip #include <rtl/ustring.hxx>
// auto strip #endif

#ifndef _COM_SUN_STAR_XML_SAX_XLOCATOR_HPP_
#include <com/sun/star/xml/sax/XLocator.hpp>
#endif

// auto strip #ifndef _COM_SUN_STAR_XML_SAX_SAXPARSEEXCEPTION_HPP_
// auto strip #include <com/sun/star/xml/sax/SAXParseException.hpp>
// auto strip #endif

// auto strip #ifndef _COM_SUN_STAR_UNO_ANY_HXX_
// auto strip #include <com/sun/star/uno/Any.hxx>
// auto strip #endif

// auto strip #ifndef _COM_SUN_STAR_UNO_REFERENCE_HXX_
// auto strip #include <com/sun/star/uno/Reference.hxx>
// auto strip #endif

#ifndef _COM_SUN_STAR_UNO_SEQUENCE_HXX_
#include <com/sun/star/uno/Sequence.hxx>
#endif


#ifndef _RTL_USTRBUF_HXX_
#include <rtl/ustrbuf.hxx>
#endif

#ifndef _STRING_HXX
#include <tools/string.hxx>
#endif
namespace binfilter {



using ::rtl::OUString;
using ::rtl::OUStringBuffer;
using ::com::sun::star::uno::Any;
using ::com::sun::star::uno::Sequence;
using ::com::sun::star::uno::Reference;
using ::com::sun::star::xml::sax::XLocator;
using ::com::sun::star::xml::sax::SAXParseException;


//
/// ErrorRecord: contains all information for one error
//

class ErrorRecord
{
public:

    ErrorRecord( sal_Int32 nId, 
                 const Sequence<OUString>& rParams,
                 const OUString& rExceptionMessage,
                 sal_Int32 nRow,
                 sal_Int32 nColumn,
                 const OUString& rPublicId,
                 const OUString& rSystemId);
    ~ErrorRecord();

    sal_Int32 nId;  /// error ID

    OUString sExceptionMessage;/// message of original exception (if available)

    // XLocator information:
    sal_Int32 nRow;     /// row number where error occured (or -1 for unknown)
    sal_Int32 nColumn;  /// column number where error occured (or -1)
    OUString sPublicId; /// public identifier
    OUString sSystemId; /// public identifier

    /// message Parameters
    Sequence<OUString> aParams;  
};


ErrorRecord::ErrorRecord( sal_Int32 nID, const Sequence<OUString>& rParams,
    const OUString& rExceptionMessage, sal_Int32 nRowNumber, sal_Int32 nCol,
    const OUString& rPublicId, const OUString& rSystemId) :
        nId(nID),
        aParams(rParams),
        sExceptionMessage(rExceptionMessage),
        nRow(nRowNumber),
        nColumn(nCol),
        sPublicId(rPublicId),
        sSystemId(rSystemId)
{
}
    
ErrorRecord::~ErrorRecord()
{
}




XMLErrors::XMLErrors()
{
}

XMLErrors::~XMLErrors()
{
}

void XMLErrors::AddRecord( 
    sal_Int32 nId,
    const Sequence<OUString> & rParams,
    const OUString& rExceptionMessage,
    sal_Int32 nRow,
    sal_Int32 nColumn,
    const OUString& rPublicId,
    const OUString& rSystemId )
{
    aErrors.push_back( ErrorRecord( nId, rParams, rExceptionMessage, 
                                    nRow, nColumn, rPublicId, rSystemId ) );

#ifndef PRODUCT

    // give detailed assertion on this message

    OUStringBuffer sMessage;

    sMessage.appendAscii( "An error or a warning has occured during XML import/export!\n" );

    // ID & flags
    sMessage.appendAscii( "Error-Id: 0x");
    sMessage.append( nId, 16 );
    sMessage.appendAscii( "\n    Flags: " );
    sal_Int32 nFlags = (nId & XMLERROR_MASK_FLAG);
    sMessage.append( nFlags >> 28, 16 );
    if( (nFlags & XMLERROR_FLAG_WARNING) != 0 )
        sMessage.appendAscii( " WARNING" );
    if( (nFlags & XMLERROR_FLAG_ERROR) != 0 )
        sMessage.appendAscii( " ERRROR" );
    if( (nFlags & XMLERROR_FLAG_SEVERE) != 0 )
        sMessage.appendAscii( " SEVERE" );
    sMessage.appendAscii( "\n    Class: " );
    sal_Int32 nClass = (nId & XMLERROR_MASK_CLASS);
    sMessage.append( nClass >> 16, 16 );
    if( (nClass & XMLERROR_CLASS_IO) != 0 )
        sMessage.appendAscii( " IO" );
    if( (nClass & XMLERROR_CLASS_FORMAT) != 0 )
        sMessage.appendAscii( " FORMAT" );
    if( (nClass & XMLERROR_CLASS_API) != 0 )
        sMessage.appendAscii( " API" );
    if( (nClass & XMLERROR_CLASS_OTHER) != 0 )
        sMessage.appendAscii( " OTHER" );
    sMessage.appendAscii( "\n    Number: " );
    sal_Int32 nNumber = (nId & XMLERROR_MASK_NUMBER);
    sMessage.append( nNumber, 16 );
    sMessage.appendAscii( "\n");

    // the parameters
    sMessage.appendAscii( "Parameters:\n" );
    sal_Int32 nLength = rParams.getLength();
    const OUString* pParams = rParams.getConstArray();
    for( sal_Int32 i = 0; i < nLength; i++ )
    {
        sMessage.appendAscii( "    " );
        sMessage.append( i );
        sMessage.appendAscii( ": " );
        sMessage.append( pParams[i] );
        sMessage.appendAscii( "\n" );
    }

    // the exception message
    sMessage.appendAscii( "Exception-Message: " );
    sMessage.append( rExceptionMessage );
    sMessage.appendAscii( "\n" );

    // position (if given)
    if( (nRow != -1) || (nColumn != -1) )
    {
        sMessage.appendAscii( "Position:\n    Public Identifier: " );
        sMessage.append( rPublicId );
        sMessage.appendAscii( "\n    System Identifier: " );
        sMessage.append( rSystemId );
        sMessage.appendAscii( "\n    Row, Column: " );
        sMessage.append( nRow );
        sMessage.appendAscii( "," );
        sMessage.append( nColumn );
        sMessage.appendAscii( "\n" );
    }

    // convert to byte string and signal the error
    ByteString aError( String( sMessage.makeStringAndClear() ), 
                       RTL_TEXTENCODING_ASCII_US );
    DBG_ERROR( aError.GetBuffer() );
#endif    
}

void XMLErrors::AddRecord( 
    sal_Int32 nId,
    const Sequence<OUString> & rParams,
    const OUString& rExceptionMessage,
    const Reference<XLocator> & rLocator)
{
    if ( rLocator.is() )
    {
        AddRecord( nId, rParams, rExceptionMessage, 
                   rLocator->getLineNumber(), rLocator->getColumnNumber(),
                   rLocator->getPublicId(), rLocator->getSystemId() );
    }
    else
    {
        OUString sEmpty;
        AddRecord( nId, rParams, rExceptionMessage, 
                   -1, -1, sEmpty, sEmpty );
    }
}

void XMLErrors::AddRecord( 
    sal_Int32 nId,
    const Sequence<OUString> & rParams,
    const OUString& rExceptionMessage)
{
    OUString sEmpty;
    AddRecord( nId, rParams, rExceptionMessage, -1, -1, sEmpty, sEmpty );
}

void XMLErrors::AddRecord( 
    sal_Int32 nId,
    const Sequence<OUString> & rParams)
{
    OUString sEmpty;
    AddRecord( nId, rParams, sEmpty, -1, -1, sEmpty, sEmpty );
}
    
void XMLErrors::ThrowErrorAsSAXException(sal_Int32 nIdMask)
    throw( SAXParseException )
{
    // search first error/warning that matches the nIdMask
    for( ErrorList::iterator aIter = aErrors.begin();
         aIter != aErrors.end();
         aIter++ )
    {
        if ( (aIter->nId & nIdMask) != 0 )
        {
            // we throw the error
            ErrorRecord& rErr = aErrors[0];
            Any aAny;
            aAny <<= rErr.aParams;
            throw SAXParseException( 
                rErr.sExceptionMessage, NULL, aAny,
                rErr.sPublicId, rErr.sSystemId, rErr.nRow, rErr.nColumn );
        }
    }
}
}//end of namespace binfilter
