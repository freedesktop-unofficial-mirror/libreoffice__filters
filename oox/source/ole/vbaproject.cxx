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

#include "oox/ole/vbaproject.hxx"
#include <com/sun/star/document/XEventsSupplier.hpp>
#include <com/sun/star/document/XStorageBasedDocument.hpp>
#include <com/sun/star/embed/ElementModes.hpp>
#include <com/sun/star/embed/XTransactedObject.hpp>
#include <com/sun/star/lang/XMultiServiceFactory.hpp>
#include <com/sun/star/script/ModuleType.hpp>
#include <com/sun/star/script/XLibraryContainer.hpp>
#include <com/sun/star/script/XVBACompat.hpp>
#include <rtl/tencinfo.h>
#include <rtl/ustrbuf.h>
#include <comphelper/configurationhelper.hxx>
#include <comphelper/string.hxx>
#include "properties.hxx"
#include "tokens.hxx"
#include "oox/helper/binaryinputstream.hxx"
#include "oox/helper/containerhelper.hxx"
#include "oox/helper/propertyset.hxx"
#include "oox/helper/textinputstream.hxx"
#include "oox/ole/olestorage.hxx"
#include "oox/ole/vbacontrol.hxx"
#include "oox/ole/vbahelper.hxx"
#include "oox/ole/vbainputstream.hxx"
#include "oox/ole/vbamodule.hxx"

using ::rtl::OUString;
using ::rtl::OUStringBuffer;
using ::com::sun::star::container::XNameAccess;
using ::com::sun::star::container::XNameContainer;
using ::com::sun::star::document::XEventsSupplier;
using ::com::sun::star::document::XStorageBasedDocument;
using ::com::sun::star::embed::XStorage;
using ::com::sun::star::embed::XTransactedObject;
using ::com::sun::star::frame::XModel;
using ::com::sun::star::io::XStream;
using ::com::sun::star::lang::XMultiServiceFactory;
using ::com::sun::star::script::XLibraryContainer;
using ::com::sun::star::script::XVBACompat;
using ::com::sun::star::uno::Any;
using ::com::sun::star::uno::Exception;
using ::com::sun::star::uno::Reference;
using ::com::sun::star::uno::UNO_QUERY;
using ::com::sun::star::uno::UNO_QUERY_THROW;
using ::com::sun::star::uno::UNO_SET_THROW;
using ::com::sun::star::uno::XInterface;
using ::comphelper::ConfigurationHelper;

namespace ApiModuleType = ::com::sun::star::script::ModuleType;

namespace oox {
namespace ole {

// ============================================================================

namespace {

bool lclReadConfigItem( const Reference< XInterface >& rxConfigAccess, const OUString& rItemName )
{
    // some applications do not support all configuration items, assume 'false' in this case
    try
    {
        Any aItem = ConfigurationHelper::readRelativeKey( rxConfigAccess, CREATE_OUSTRING( "Filter/Import/VBA" ), rItemName );
        return aItem.has< bool >() && aItem.get< bool >();
    }
    catch( Exception& )
    {
    }
    return false;
}

} // namespace

// ----------------------------------------------------------------------------

VbaFilterConfig::VbaFilterConfig( const Reference< XMultiServiceFactory >& rxGlobalFactory, const OUString& rConfigCompName )
{
    OSL_ENSURE( rxGlobalFactory.is(), "VbaFilterConfig::VbaFilterConfig - missing service factory" );
    try
    {
        OSL_ENSURE( rConfigCompName.getLength() > 0, "VbaFilterConfig::VbaFilterConfig - invalid configuration component name" );
        OUString aConfigPackage = CREATE_OUSTRING( "org.openoffice.Office." ) + rConfigCompName;
        mxConfigAccess = ConfigurationHelper::openConfig( rxGlobalFactory, aConfigPackage, ConfigurationHelper::E_READONLY );
    }
    catch( Exception& )
    {
    }
    OSL_ENSURE( mxConfigAccess.is(), "VbaFilterConfig::VbaFilterConfig - cannot open configuration" );
}

VbaFilterConfig::~VbaFilterConfig()
{
}

bool VbaFilterConfig::isImportVba() const
{
    return lclReadConfigItem( mxConfigAccess, CREATE_OUSTRING( "Load" ) );
}

bool VbaFilterConfig::isImportVbaExecutable() const
{
    return lclReadConfigItem( mxConfigAccess, CREATE_OUSTRING( "Executable" ) );
}

bool VbaFilterConfig::isExportVba() const
{
    return lclReadConfigItem( mxConfigAccess, CREATE_OUSTRING( "Save" ) );
}

// ============================================================================

VbaProject::VbaProject( const Reference< XMultiServiceFactory >& rxGlobalFactory,
        const Reference< XModel >& rxDocModel, const OUString& rConfigCompName ) :
    VbaFilterConfig( rxGlobalFactory, rConfigCompName ),
    mxGlobalFactory( rxGlobalFactory ),
    mxDocModel( rxDocModel ),
    maLibName( CREATE_OUSTRING( "Standard" ) )
{
    OSL_ENSURE( mxDocModel.is(), "VbaProject::VbaProject - missing document model" );
    mxBasicLib = openLibrary( PROP_BasicLibraries, false );
    mxDialogLib = openLibrary( PROP_DialogLibraries, false );
}

VbaProject::~VbaProject()
{
}

void VbaProject::importVbaProject( StorageBase& rVbaPrjStrg, const GraphicHelper& rGraphicHelper, bool bDefaultColorBgr )
{
    if( rVbaPrjStrg.isStorage() )
    {
        // load the code modules and forms
        if( isImportVba() )
            importVba( rVbaPrjStrg, rGraphicHelper, bDefaultColorBgr );
        // copy entire storage into model
        if( isExportVba() )
            copyStorage( rVbaPrjStrg );
    }
}

bool VbaProject::hasModules() const
{
    return mxBasicLib.is() && mxBasicLib->hasElements();
}

bool VbaProject::hasModule( const OUString& rModuleName ) const
{
    return mxBasicLib.is() && mxBasicLib->hasByName( rModuleName );
}

bool VbaProject::hasDialogs() const
{
    return mxDialogLib.is() && mxDialogLib->hasElements();
}

bool VbaProject::hasDialog( const OUString& rDialogName ) const
{
    return mxDialogLib.is() && mxDialogLib->hasByName( rDialogName );
}

// private --------------------------------------------------------------------

Reference< XLibraryContainer > VbaProject::getLibraryContainer( sal_Int32 nPropId )
{
    PropertySet aDocProp( mxDocModel );
    Reference< XLibraryContainer > xLibContainer( aDocProp.getAnyProperty( nPropId ), UNO_QUERY );
    return xLibContainer;
}

Reference< XNameContainer > VbaProject::openLibrary( sal_Int32 nPropId, bool bCreateMissing )
{
    Reference< XNameContainer > xLibrary;
    try
    {
        Reference< XLibraryContainer > xLibContainer( getLibraryContainer( nPropId ), UNO_SET_THROW );
        if( bCreateMissing && !xLibContainer->hasByName( maLibName ) )
            xLibContainer->createLibrary( maLibName );
        xLibrary.set( xLibContainer->getByName( maLibName ), UNO_QUERY_THROW );
    }
    catch( Exception& )
    {
    }
    OSL_ENSURE( !bCreateMissing || xLibrary.is(), "VbaProject::openLibrary - cannot create library" );
    return xLibrary;
}

Reference< XNameContainer > VbaProject::createBasicLibrary()
{
    if( !mxBasicLib.is() )
        mxBasicLib = openLibrary( PROP_BasicLibraries, true );
    return mxBasicLib;
}

Reference< XNameContainer > VbaProject::createDialogLibrary()
{
    if( !mxDialogLib.is() )
        mxDialogLib = openLibrary( PROP_DialogLibraries, true );
    return mxDialogLib;
}

void VbaProject::importVba( StorageBase& rVbaPrjStrg, const GraphicHelper& rGraphicHelper, bool bDefaultColorBgr )
{
    StorageRef xVbaStrg = rVbaPrjStrg.openSubStorage( CREATE_OUSTRING( "VBA" ), false );
    OSL_ENSURE( xVbaStrg.get(), "VbaProject::importVba - cannot open 'VBA' substorage" );
    if( !xVbaStrg )
        return;

    /*  Read the 'VBA/dir' stream which contains general settings of the VBA
        project such as the text encoding used throughout several streams, and
        a list of all code modules.
     */
    BinaryXInputStream aInStrm( xVbaStrg->openInputStream( CREATE_OUSTRING( "dir" ) ), true );
    // VbaInputStream implements decompression
    VbaInputStream aDirStrm( aInStrm );
    OSL_ENSURE( !aDirStrm.isEof(), "VbaProject::importVba - cannot open 'dir' stream" );
    if( aDirStrm.isEof() )
        return;

    // read all records of the directory
    rtl_TextEncoding eTextEnc = RTL_TEXTENCODING_MS_1252;
    sal_uInt16 nModuleCount = 0;
    bool bExecutable = isImportVbaExecutable();

    typedef RefMap< OUString, VbaModule > VbaModuleMap;
    VbaModuleMap aModules, aModulesByStrm;

    sal_uInt16 nRecId = 0;
    StreamDataSequence aRecData;
    while( VbaHelper::readDirRecord( nRecId, aRecData, aDirStrm ) && (nRecId != VBA_ID_PROJECTEND) )
    {
        // create record stream object from imported record data
        SequenceInputStream aRecStrm( aRecData );
        sal_Int32 nRecSize = aRecData.getLength();
        switch( nRecId )
        {
#define OOX_ENSURE_RECORDSIZE( cond ) OSL_ENSURE( cond, "VbaProject::importVba - invalid record size" )
            case VBA_ID_PROJECTCODEPAGE:
            {
                OOX_ENSURE_RECORDSIZE( nRecSize == 2 );
                OSL_ENSURE( aModules.empty(), "VbaProject::importVba - unexpected PROJECTCODEPAGE record" );
                rtl_TextEncoding eNewTextEnc = rtl_getTextEncodingFromWindowsCodePage( aRecStrm.readuInt16() );
                OSL_ENSURE( eNewTextEnc != RTL_TEXTENCODING_DONTKNOW, "VbaProject::importVba - unknown text encoding" );
                if( eNewTextEnc != RTL_TEXTENCODING_DONTKNOW )
                    eTextEnc = eNewTextEnc;
            }
            break;
            case VBA_ID_PROJECTMODULES:
                OOX_ENSURE_RECORDSIZE( nRecSize == 2 );
                OSL_ENSURE( aModules.empty(), "VbaProject::importVba - unexpected PROJECTMODULES record" );
                aRecStrm >> nModuleCount;
            break;
            case VBA_ID_MODULENAME:
            {
                OUString aName = aRecStrm.readCharArrayUC( nRecSize, eTextEnc );
                OSL_ENSURE( aName.getLength() > 0, "VbaProject::importVba - invalid module name" );
                OSL_ENSURE( !aModules.has( aName ), "VbaProject::importVba - multiple modules with the same name" );
                VbaModuleMap::mapped_type& rxModule = aModules[ aName ];
                rxModule.reset( new VbaModule( mxDocModel, aName, eTextEnc, bExecutable ) );
                // read all remaining records until the MODULEEND record
                rxModule->importDirRecords( aDirStrm );
                OSL_ENSURE( !aModulesByStrm.has( rxModule->getStreamName() ), "VbaProject::importVba - multiple modules with the same stream name" );
                aModulesByStrm[ rxModule->getStreamName() ] = rxModule;
            }
            break;
#undef OOX_ENSURE_RECORDSIZE
        }
    }
    OSL_ENSURE( nModuleCount == aModules.size(), "VbaProject::importVba - invalid module count" );
    
    /*  The directory does not contain the real type of the modules, it
        distinguishes only between 'procedural' and 'document' (the latter
        includes class and form modules). Now, the exact type of all modules
        will be read from the 'PROJECT' stream. It consists of text lines in
        'key=value' format which list the code modules by type.

        -   The line 'document=<modulename>/&HXXXXXXXX' declares document
            modules. These are attached to the Word document (usually called
            'ThisDocument'), the Excel workbook (usually called
            'ThisWorkbook'), or single Excel worksheets or chartsheets (usually
            called 'SheetX' or 'ChartX', X being a decimal number). Of course,
            users may rename all these modules. The slash character separates
            an automation server version number (hexadecimal 'XXXXXXXX') from
            the module name.
        -   The line 'Module=<modulename>' declares common procedural code
            modules.
        -   The line 'Class=<modulename>' declares a class module.
        -   The line 'BaseClass=<modulename>' declares a code module attached
            to a user form with the same name.
     */
    BinaryXInputStream aPrjStrm( rVbaPrjStrg.openInputStream( CREATE_OUSTRING( "PROJECT" ) ), true );
    OSL_ENSURE( !aPrjStrm.isEof(), "VbaProject::importVba - cannot open 'PROJECT' stream" );
    // do not exit if this stream does not exist, but proceed to load the modules below
    if( !aPrjStrm.isEof() )
    {
        TextInputStream aPrjTextStrm( aPrjStrm, eTextEnc );
        OUString aKey, aValue;
        bool bExitLoop = false;
        while( !bExitLoop && !aPrjTextStrm.isEof() )
        {
            // read a text line from the stream
            OUString aLine = aPrjTextStrm.readLine().trim();
            sal_Int32 nLineLen = aLine.getLength();
            // exit if a subsection starts (section name is given in brackets)
            bExitLoop = (nLineLen >= 2) && (aLine[ 0 ] == '[') && (aLine[ nLineLen - 1 ] == ']');
            if( !bExitLoop && VbaHelper::extractKeyValue( aKey, aValue, aLine ) )
            {
                sal_Int32 nType = ApiModuleType::UNKNOWN;
                if( aKey.equalsIgnoreAsciiCaseAsciiL( RTL_CONSTASCII_STRINGPARAM( "Document" ) ) )
                {
                    nType = ApiModuleType::DOCUMENT;
                    // strip automation server version from module names
                    sal_Int32 nSlashPos = aValue.indexOf( '/' );
                    if( nSlashPos >= 0 )
                        aValue = aValue.copy( 0, nSlashPos );
                }
                else if( aKey.equalsIgnoreAsciiCaseAsciiL( RTL_CONSTASCII_STRINGPARAM( "Module" ) ) )
                    nType = ApiModuleType::NORMAL;
                else if( aKey.equalsIgnoreAsciiCaseAsciiL( RTL_CONSTASCII_STRINGPARAM( "Class" ) ) )
                    nType = ApiModuleType::CLASS;
                else if( aKey.equalsIgnoreAsciiCaseAsciiL( RTL_CONSTASCII_STRINGPARAM( "BaseClass" ) ) )
                    nType = ApiModuleType::FORM;

                if( (nType != ApiModuleType::UNKNOWN) && (aValue.getLength() > 0) )
                {
                    OSL_ENSURE( aModules.has( aValue ), "VbaProject::importVba - module not found" );
                    if( VbaModule* pModule = aModules.get( aValue ).get() )
                        pModule->setType( nType );
                }
            }
        }
    }

    /*  Now it is time to load the source code. All modules will be inserted
        into the Basic library of the document specified by the 'maLibName'
        member. Do not create the Basic library, if there are no modules
        specified. */
    if( !aModules.empty() ) try
    {
        // get the basic library
        Reference< XNameContainer > xBasicLib( createBasicLibrary(), UNO_SET_THROW );

        // set library container to VBA compatibility mode
        try
        {
            Reference< XVBACompat >( getLibraryContainer( PROP_BasicLibraries ), UNO_QUERY_THROW )->setVBACompatModeOn( sal_True );
        }
        catch( Exception& )
        {
        }

        // try to get access to document objects related to code modules
        Reference< XNameAccess > xDocObjectNA;
        try
        {
            Reference< XMultiServiceFactory > xModelFactory( mxDocModel, UNO_QUERY_THROW );
            xDocObjectNA.set( xModelFactory->createInstance( CREATE_OUSTRING( "ooo.vba.VBAObjectModuleObjectProvider" ) ), UNO_QUERY );
        }
        catch( Exception& )
        {
            // not all documents support this
        }

        // call Basic source code import for each module, boost::[c]ref enforces pass-by-ref
        if( xBasicLib.is() )
            aModules.forEachMem( &VbaModule::importSourceCode,
                ::boost::ref( *xVbaStrg ), ::boost::cref( xBasicLib ), ::boost::cref( xDocObjectNA ) );
    }
    catch( Exception& )
    {
    }

    /*  Load the forms. The file format specification requires that a module
        must exist for every form. We are a bit more tolerant and scan the
        project storage for all form substorages. This may 'repair' broken VBA
        storages that misses to mention a module for an existing form. */
    ::std::vector< OUString > aElements;
    rVbaPrjStrg.getElementNames( aElements );
    for( ::std::vector< OUString >::iterator aIt = aElements.begin(), aEnd = aElements.end(); aIt != aEnd; ++aIt )
    {
        // try to open the element as storage
        if( !aIt->equals( CREATE_OUSTRING( "VBA" ) ) )
        {
            StorageRef xSubStrg = rVbaPrjStrg.openSubStorage( *aIt, false );
            if( xSubStrg.get() ) try
            {
                // resolve module name from storage name (which equals the module stream name)
                VbaModule* pModule = aModulesByStrm.get( *aIt ).get();
                OSL_ENSURE( pModule && (pModule->getType() == ApiModuleType::FORM),
                    "VbaProject::importVba - form substorage without form module" );
                OUString aModuleName;
                if( pModule )
                    aModuleName = pModule->getName();

                // create and import the form
                Reference< XNameContainer > xDialogLib( createDialogLibrary(), UNO_SET_THROW );
                VbaUserForm aForm( mxGlobalFactory, rGraphicHelper, bDefaultColorBgr );
                aForm.importForm( xDialogLib, *xSubStrg, aModuleName, eTextEnc );
            }
            catch( Exception& )
            {
            }
        }
    }
}

void VbaProject::copyStorage( StorageBase& rVbaPrjStrg )
{
    try
    {
        Reference< XStorageBasedDocument > xStorageBasedDoc( mxDocModel, UNO_QUERY_THROW );
        Reference< XStorage > xDocStorage( xStorageBasedDoc->getDocumentStorage(), UNO_QUERY_THROW );
        {
            using namespace ::com::sun::star::embed::ElementModes;
            Reference< XStream > xDocStream( xDocStorage->openStreamElement( CREATE_OUSTRING( "_MS_VBA_Macros" ), SEEKABLE | WRITE | TRUNCATE ), UNO_SET_THROW );
            OleStorage aDestStorage( mxGlobalFactory, xDocStream, false );
            rVbaPrjStrg.copyStorageToStorage( aDestStorage );
            aDestStorage.commit();
        }
        Reference< XTransactedObject >( xDocStorage, UNO_QUERY_THROW )->commit();
    }
    catch( Exception& )
    {
    }
}

// ============================================================================

} // namespace ole
} // namespace oox
