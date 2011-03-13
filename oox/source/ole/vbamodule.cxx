/* -*- Mode: C++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */
/*************************************************************************
 *
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER.
 *
 * Copyright 2000, 2010 Oracle and/or its affiliates.
 *
 * OpenOffice.org - a multi-platform office productivity suite
 *
 * This file is part of OpenOffice.org.
 *
 * OpenOffice.org is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License version 3
 * only, as published by the Free Software Foundation.
 *
 * OpenOffice.org is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License version 3 for more details
 * (a copy is included in the LICENSE file that accompanied this code).
 *
 * You should have received a copy of the GNU Lesser General Public License
 * version 3 along with OpenOffice.org.  If not, see
 * <http://www.openoffice.org/license.html>
 * for a copy of the LGPLv3 License.
 *
 ************************************************************************/

#include "oox/ole/vbamodule.hxx"
#include <boost/unordered_map.hpp>
#include <com/sun/star/container/XNameContainer.hpp>
#include <com/sun/star/container/XIndexContainer.hpp>
#include <com/sun/star/script/ModuleInfo.hpp>
#include <com/sun/star/script/ModuleType.hpp>
#include <com/sun/star/script/vba/XVBAModuleInfo.hpp>
#include <cppuhelper/implbase1.hxx>
#include "oox/helper/binaryinputstream.hxx"
#include "oox/helper/storagebase.hxx"
#include "oox/helper/textinputstream.hxx"
#include "oox/ole/vbahelper.hxx"
#include "oox/ole/vbainputstream.hxx"

namespace oox {
namespace ole {

// ============================================================================

using namespace ::com::sun::star::container;
using namespace ::com::sun::star::frame;
using namespace ::com::sun::star::lang;
using namespace ::com::sun::star::script;
using namespace ::com::sun::star::script::vba;
using namespace ::com::sun::star::uno;

using ::rtl::OUString;
using ::rtl::OUStringBuffer;
// ============================================================================
typedef ::cppu::WeakImplHelper1< XIndexContainer > OleIdToNameContainer_BASE;
typedef boost::unordered_map< sal_Int32, rtl::OUString >  ObjIdToName;

class OleIdToNameContainer : public OleIdToNameContainer_BASE
{
    ObjIdToName ObjIdToNameHash;
    ::osl::Mutex m_aMutex;
    bool hasByIndex( ::sal_Int32 Index )
    {
        ::osl::MutexGuard aGuard( m_aMutex );
        return ( ObjIdToNameHash.find( Index ) != ObjIdToNameHash.end() );
    }
public:
    OleIdToNameContainer() {}
    // XIndexContainer Methods
    virtual void SAL_CALL insertByIndex( ::sal_Int32 Index, const Any& Element ) throw (IllegalArgumentException, IndexOutOfBoundsException, WrappedTargetException, RuntimeException)
    {
        ::osl::MutexGuard aGuard( m_aMutex );
        rtl::OUString sOleName;
        if ( !( Element >>= sOleName ) )
            throw IllegalArgumentException();
        ObjIdToNameHash[ Index ] = sOleName;
    }
    virtual void SAL_CALL removeByIndex( ::sal_Int32 Index ) throw (IndexOutOfBoundsException, WrappedTargetException, RuntimeException)
    {
        ::osl::MutexGuard aGuard( m_aMutex );
        if ( !hasByIndex( Index ) )
            throw IndexOutOfBoundsException();
        ObjIdToNameHash.erase( ObjIdToNameHash.find( Index ) );
    }
    // XIndexReplace Methods
    virtual void SAL_CALL replaceByIndex( ::sal_Int32 Index, const Any& Element ) throw (IllegalArgumentException, IndexOutOfBoundsException, WrappedTargetException, RuntimeException)
    {
        ::osl::MutexGuard aGuard( m_aMutex );
        if ( !hasByIndex( Index ) )
            throw IndexOutOfBoundsException();
        rtl::OUString sOleName;
        if ( !( Element >>= sOleName ) )
            throw IllegalArgumentException();
        ObjIdToNameHash[ Index ] = sOleName;
    }
    // XIndexAccess Methods
    virtual ::sal_Int32 SAL_CALL getCount(  ) throw (RuntimeException)
    {
        ::osl::MutexGuard aGuard( m_aMutex );
        return ObjIdToNameHash.size();
    }
    virtual Any SAL_CALL getByIndex( ::sal_Int32 Index ) throw (IndexOutOfBoundsException, WrappedTargetException, RuntimeException)
    {
        ::osl::MutexGuard aGuard( m_aMutex );
        if ( !hasByIndex( Index ) )
            throw IndexOutOfBoundsException();
        return makeAny( ObjIdToNameHash[ Index ] );
    }
    // XElementAccess Methods
    virtual Type SAL_CALL getElementType(  ) throw (RuntimeException)
    {
        return ::getCppuType( static_cast< const ::rtl::OUString* >( 0 ) );
    }
    virtual ::sal_Bool SAL_CALL hasElements(  ) throw (RuntimeException)
    {
        ::osl::MutexGuard aGuard( m_aMutex );
        return ( getCount() > 0 );
    }
};

 // ============================================================================

VbaModule::VbaModule( const Reference< XModel >& rxDocModel, const OUString& rName, rtl_TextEncoding eTextEnc, bool bExecutable ) :
    mxDocModel( rxDocModel ),
    maName( rName ),
    meTextEnc( eTextEnc ),
    mnType( ModuleType::UNKNOWN ),
    mnOffset( SAL_MAX_UINT32 ),
    mbReadOnly( false ),
    mbPrivate( false ),
    mbExecutable( bExecutable )
{
}

void VbaModule::importDirRecords( BinaryInputStream& rDirStrm )
{
    sal_uInt16 nRecId = 0;
    StreamDataSequence aRecData;
    while( VbaHelper::readDirRecord( nRecId, aRecData, rDirStrm ) && (nRecId != VBA_ID_MODULEEND) )
    {
        SequenceInputStream aRecStrm( aRecData );
        sal_Int32 nRecSize = aRecData.getLength();
        switch( nRecId )
        {
#define OOX_ENSURE_RECORDSIZE( cond ) OSL_ENSURE( cond, "VbaModule::importDirRecords - invalid record size" )
            case VBA_ID_MODULENAME:
                OSL_ENSURE( false, "VbaModule::importDirRecords - unexpected MODULENAME record" );
                maName = aRecStrm.readCharArrayUC( nRecSize, meTextEnc );
            break;
            case VBA_ID_MODULENAMEUNICODE:
            break;
            case VBA_ID_MODULESTREAMNAME:
                maStreamName = aRecStrm.readCharArrayUC( nRecSize, meTextEnc );
            break;
            case VBA_ID_MODULESTREAMNAMEUNICODE:
            break;
            case VBA_ID_MODULEDOCSTRING:
                maDocString = aRecStrm.readCharArrayUC( nRecSize, meTextEnc );
            break;
            case VBA_ID_MODULEDOCSTRINGUNICODE:
            break;
            case VBA_ID_MODULEOFFSET:
                OOX_ENSURE_RECORDSIZE( nRecSize == 4 );
                aRecStrm >> mnOffset;
            break;
            case VBA_ID_MODULEHELPCONTEXT:
                OOX_ENSURE_RECORDSIZE( nRecSize == 4 );
            break;
            case VBA_ID_MODULECOOKIE:
                OOX_ENSURE_RECORDSIZE( nRecSize == 2 );
            break;
            case VBA_ID_MODULETYPEPROCEDURAL:
                OOX_ENSURE_RECORDSIZE( nRecSize == 0 );
                OSL_ENSURE( mnType == ModuleType::UNKNOWN, "VbaModule::importDirRecords - multiple module type records" );
                mnType = ModuleType::NORMAL;
            break;
            case VBA_ID_MODULETYPEDOCUMENT:
                OOX_ENSURE_RECORDSIZE( nRecSize == 0 );
                OSL_ENSURE( mnType == ModuleType::UNKNOWN, "VbaModule::importDirRecords - multiple module type records" );
                mnType = ModuleType::DOCUMENT;
            break;
            case VBA_ID_MODULEREADONLY:
                OOX_ENSURE_RECORDSIZE( nRecSize == 0 );
                mbReadOnly = true;
            break;
            case VBA_ID_MODULEPRIVATE:
                OOX_ENSURE_RECORDSIZE( nRecSize == 0 );
                mbPrivate = true;
            break;
            default:
                OSL_ENSURE( false, "VbaModule::importDirRecords - unknown module record" );
#undef OOX_ENSURE_RECORDSIZE
        }
    }
    OSL_ENSURE( maName.getLength() > 0, "VbaModule::importDirRecords - missing module name" );
    OSL_ENSURE( maStreamName.getLength() > 0, "VbaModule::importDirRecords - missing module stream name" );
    OSL_ENSURE( mnType != ModuleType::UNKNOWN, "VbaModule::importDirRecords - missing module type" );
    OSL_ENSURE( mnOffset < SAL_MAX_UINT32, "VbaModule::importDirRecords - missing module stream offset" );
}

void VbaModule::createAndImportModule( StorageBase& rVbaStrg, const Reference< XNameContainer >& rxBasicLib,
        const Reference< XNameAccess >& rxDocObjectNA, const Reference< XNameContainer >& rxOleNameOverrides ) const
{
    OUString aVBASourceCode = readSourceCode( rVbaStrg, rxOleNameOverrides );
    createModule( aVBASourceCode, rxBasicLib, rxDocObjectNA );
}

void VbaModule::createEmptyModule( const Reference< XNameContainer >& rxBasicLib, const Reference< XNameAccess >& rxDocObjectNA ) const
{
    createModule( OUString(), rxBasicLib, rxDocObjectNA );
}

OUString VbaModule::readSourceCode( StorageBase& rVbaStrg, const Reference< XNameContainer >& rxOleNameOverrides ) const
{
    OUStringBuffer aSourceCode;
    if( (maStreamName.getLength() > 0) && (mnOffset != SAL_MAX_UINT32) )
    {
        BinaryXInputStream aInStrm( rVbaStrg.openInputStream( maStreamName ), true );
        OSL_ENSURE( !aInStrm.isEof(), "VbaModule::readSourceCode - cannot open module stream" );
        // skip the 'performance cache' stored before the actual source code
        aInStrm.seek( mnOffset );
        // if stream is still valid, load the source code
        if( !aInStrm.isEof() )
        {
            // decompression starts at current stream position of aInStrm
            VbaInputStream aVbaStrm( aInStrm );
            // load the source code line-by-line, with some more processing
            TextInputStream aVbaTextStrm( aVbaStrm, meTextEnc );
            while( !aVbaTextStrm.isEof() )
            {
                OUString aCodeLine = aVbaTextStrm.readLine();
                if( aCodeLine.matchAsciiL( RTL_CONSTASCII_STRINGPARAM( "Attribute " ) ) )
                {
                    // attribute
                    extractOleOverrideFromAttr( aCodeLine, rxOleNameOverrides );
                }
                else
                {
                    // normal source code line
                    if( !mbExecutable )
                        aSourceCode.appendAscii( RTL_CONSTASCII_STRINGPARAM( "Rem " ) );
                    aSourceCode.append( aCodeLine ).append( sal_Unicode( '\n' ) );
                }
            }
        }
    }
    return aSourceCode.makeStringAndClear();
}

void VbaModule::extractOleOverrideFromAttr( const OUString& rAttribute, const Reference< XNameContainer >& rxOleNameOverrides ) const
{
    // format of the attribute we are interested in is
    // Attribute VB_Control = "ControlName", intString, MSForms, ControlTypeAsString
    // e.g.
    // Attribute VB_Control = "CommandButton1, 201, 19, MSForms, CommandButton"
    OUString sControlAttribute = CREATE_OUSTRING( "Attribute VB_Control = \"" );
    if ( rxOleNameOverrides.is() && rAttribute.indexOf( sControlAttribute ) !=  -1 )
    {
        OUString sRest = rAttribute.copy( sControlAttribute.getLength() );
        sal_Int32 nPos = sRest.indexOf( ',' );
        OUString sCntrlName = sRest.copy( 0, nPos );

        sal_Int32 nCntrlId = sRest.copy( nPos + 1 ).copy( 0, sRest.indexOf( ',', nPos + 1) ).toInt32();
        OSL_TRACE("In module %s, assiging %d controlname %s",
            rtl::OUStringToOString( maName, RTL_TEXTENCODING_UTF8 ).getStr(), nCntrlId,
            rtl::OUStringToOString( sCntrlName, RTL_TEXTENCODING_UTF8 ).getStr() );
        if ( !rxOleNameOverrides->hasByName( maName ) )
            rxOleNameOverrides->insertByName( maName, Any( Reference< XIndexContainer> ( new OleIdToNameContainer ) ) );
        Reference< XIndexContainer > xIdToOleName;
        if ( rxOleNameOverrides->getByName( maName ) >>= xIdToOleName )
            xIdToOleName->insertByIndex( nCntrlId, makeAny( sCntrlName ) );
    }
}

void VbaModule::createModule( const OUString& rVBASourceCode,
        const Reference< XNameContainer >& rxBasicLib, const Reference< XNameAccess >& rxDocObjectNA ) const
{
    if( maName.getLength() == 0 )
        return;
        
    // prepare the Basic module
    ModuleInfo aModuleInfo;
    aModuleInfo.ModuleType = mnType;
    OUStringBuffer aSourceCode;
    aSourceCode.appendAscii( RTL_CONSTASCII_STRINGPARAM( "Rem Attribute VBA_ModuleType=" ) );
    switch( mnType )
    {
        case ModuleType::NORMAL:
            aSourceCode.appendAscii( RTL_CONSTASCII_STRINGPARAM( "VBAModule" ) );
        break;
        case ModuleType::CLASS:
            aSourceCode.appendAscii( RTL_CONSTASCII_STRINGPARAM( "VBAClassModule" ) );
        break;
        case ModuleType::FORM:
            aSourceCode.appendAscii( RTL_CONSTASCII_STRINGPARAM( "VBAFormModule" ) );
            // hack from old filter, document Basic should know the XModel, but it doesn't
            aModuleInfo.ModuleObject.set( mxDocModel, UNO_QUERY );
        break;
        case ModuleType::DOCUMENT:
            aSourceCode.appendAscii( RTL_CONSTASCII_STRINGPARAM( "VBADocumentModule" ) );
            // get the VBA implementation object associated to the document module
            if( rxDocObjectNA.is() ) try
            {
                aModuleInfo.ModuleObject.set( rxDocObjectNA->getByName( maName ), UNO_QUERY );
            }
            catch( Exception& )
            {
            }
        break;
        default:
            aSourceCode.appendAscii( RTL_CONSTASCII_STRINGPARAM( "VBAUnknown" ) );
    }
    aSourceCode.append( sal_Unicode( '\n' ) );
    if( mbExecutable )
    {
        aSourceCode.appendAscii( RTL_CONSTASCII_STRINGPARAM( "Option VBASupport 1\n" ) );
        if( mnType == ModuleType::CLASS )
            aSourceCode.appendAscii( RTL_CONSTASCII_STRINGPARAM( "Option ClassModule\n" ) );
    }
    else
    {
        // add a subroutine named after the module itself
        aSourceCode.appendAscii( RTL_CONSTASCII_STRINGPARAM( "Sub " ) ).
            append( maName.replace( ' ', '_' ) ).append( sal_Unicode( '\n' ) );
    }

    // append passed VBA source code
    aSourceCode.append( rVBASourceCode );

    // close the subroutine named after the module
    if( !mbExecutable )
        aSourceCode.appendAscii( RTL_CONSTASCII_STRINGPARAM( "End Sub\n" ) );

    // insert extended module info
    try
    {
        Reference< XVBAModuleInfo > xVBAModuleInfo( rxBasicLib, UNO_QUERY_THROW );
        xVBAModuleInfo->insertModuleInfo( maName, aModuleInfo );
    }
    catch( Exception& )
    {
    }

    // insert the module into the passed Basic library
    try
    {
        rxBasicLib->insertByName( maName, Any( aSourceCode.makeStringAndClear() ) );
    }
    catch( Exception& )
    {
        OSL_ENSURE( false, "VbaModule::createModule - cannot insert module into library" );
    }
}

// ============================================================================

} // namespace ole
} // namespace oox

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
