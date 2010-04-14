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
#include <com/sun/star/container/XNameContainer.hpp>
#include <com/sun/star/script/ModuleInfo.hpp>
#include <com/sun/star/script/ModuleType.hpp>
#include <com/sun/star/script/XVBAModuleInfo.hpp>
#include "oox/helper/binaryinputstream.hxx"
#include "oox/helper/storagebase.hxx"
#include "oox/helper/textinputstream.hxx"
#include "oox/ole/vbahelper.hxx"
#include "oox/ole/vbainputstream.hxx"

using ::rtl::OUString;
using ::rtl::OUStringBuffer;
using ::com::sun::star::container::XNameAccess;
using ::com::sun::star::container::XNameContainer;
using ::com::sun::star::frame::XModel;
using ::com::sun::star::script::ModuleInfo;
using ::com::sun::star::script::XVBAModuleInfo;
using ::com::sun::star::uno::Any;
using ::com::sun::star::uno::Exception;
using ::com::sun::star::uno::Reference;
using ::com::sun::star::uno::UNO_QUERY;
using ::com::sun::star::uno::UNO_QUERY_THROW;

namespace ApiModuleType = ::com::sun::star::script::ModuleType;

namespace oox {
namespace ole {

// ============================================================================

VbaModule::VbaModule( const Reference< XModel >& rxDocModel, const OUString& rName, rtl_TextEncoding eTextEnc, bool bExecutable ) :
    mxDocModel( rxDocModel ),
    maName( rName ),
    meTextEnc( eTextEnc ),
    mnType( ApiModuleType::Unknown ),
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
                OSL_ENSURE( mnType == ApiModuleType::Unknown, "VbaModule::importDirRecords - multiple module type records" );
                mnType = ApiModuleType::Normal;
            break;
            case VBA_ID_MODULETYPEDOCUMENT:
                OOX_ENSURE_RECORDSIZE( nRecSize == 0 );
                OSL_ENSURE( mnType == ApiModuleType::Unknown, "VbaModule::importDirRecords - multiple module type records" );
                mnType = ApiModuleType::Document;
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
    OSL_ENSURE( mnType != ApiModuleType::Unknown, "VbaModule::importDirRecords - missing module type" );
    OSL_ENSURE( mnOffset < SAL_MAX_UINT32, "VbaModule::importDirRecords - missing module stream offset" );
}

void VbaModule::importSourceCode( StorageBase& rVbaStrg,
        const Reference< XNameContainer >& rxBasicLib, const Reference< XNameAccess >& rxDocObjectNA ) const
{
    if( (maName.getLength() == 0) || (maStreamName.getLength() == 0) || (mnOffset == SAL_MAX_UINT32) )
        return;
        
    BinaryXInputStream aInStrm( rVbaStrg.openInputStream( maStreamName ), true );
    OSL_ENSURE( !aInStrm.isEof(), "VbaModule::importSourceCode - cannot open module stream" );
    // skip the 'performance cache' stored before the actual source code
    aInStrm.seek( mnOffset );
    // if stream is still valid, load the source code
    if( aInStrm.isEof() )
        return;

    // prepare the Basic module
    ModuleInfo aModuleInfo;
    aModuleInfo.ModuleType = mnType;
    OUStringBuffer aSourceCode;
    aSourceCode.appendAscii( RTL_CONSTASCII_STRINGPARAM( "Rem Attribute VBA_ModuleType=" ) );
    switch( mnType )
    {
        case ApiModuleType::Normal:
            aSourceCode.appendAscii( RTL_CONSTASCII_STRINGPARAM( "VBAModule" ) );
        break;
        case ApiModuleType::Class:
            aSourceCode.appendAscii( RTL_CONSTASCII_STRINGPARAM( "VBAClassModule" ) );
        break;
        case ApiModuleType::Form:
            aSourceCode.appendAscii( RTL_CONSTASCII_STRINGPARAM( "VBAFormModule" ) );
            // hack from old filter, document Basic should know the XModel, but it doesn't
            aModuleInfo.ModuleObject.set( mxDocModel, UNO_QUERY );
        break;
        case ApiModuleType::Document:
            aSourceCode.appendAscii( RTL_CONSTASCII_STRINGPARAM( "VBADocumentModule" ) );
            // get the VBA object associated to the document module
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
        if( mnType == ApiModuleType::Class )
            aSourceCode.appendAscii( RTL_CONSTASCII_STRINGPARAM( "Option ClassModule\n" ) );
    }
    else
    {
        // add a subroutine named after the module itself
        aSourceCode.appendAscii( RTL_CONSTASCII_STRINGPARAM( "Sub " ) ).
            append( maName.replace( ' ', '_' ) ).append( sal_Unicode( '\n' ) );
    }

    // decompression starts at current stream position of aInStrm
    VbaInputStream aVbaStrm( aInStrm );
    // load the source code line-by-line, with some more processing
    TextInputStream aVbaTextStrm( aVbaStrm, meTextEnc );
    while( !aVbaTextStrm.isEof() )
    {
        OUString aCodeLine = aVbaTextStrm.readLine();
        // skip all 'Attribute' statements
        if( !aCodeLine.matchAsciiL( RTL_CONSTASCII_STRINGPARAM( "Attribute " ) ) )
        {
            if( !mbExecutable )
                aSourceCode.appendAscii( RTL_CONSTASCII_STRINGPARAM( "Rem " ) );
            aSourceCode.append( aCodeLine ).append( sal_Unicode( '\n' ) );
        }
    }

    // close the subroutine named after the module
    if( !mbExecutable )
        aSourceCode.appendAscii( RTL_CONSTASCII_STRINGPARAM( "End Sub\n" ) );

    // insert the module into the passed Basic library
    try
    {
        rxBasicLib->insertByName( maName, Any( aSourceCode.makeStringAndClear() ) );
    }
    catch( Exception& )
    {
        OSL_ENSURE( false, "VbaModule::importSourceCode - cannot insert module into library" );
    }

    // insert extended module info
    try
    {
        Reference< XVBAModuleInfo > xVBAModuleInfo( rxBasicLib, UNO_QUERY_THROW );
        xVBAModuleInfo->insertModuleInfo( maName, aModuleInfo );
    }
    catch( Exception& )
    {
    }
}

// ============================================================================

} // namespace ole
} // namespace oox
