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

#include <string.h>



#ifndef _OSL_DIAGNOSE_H_
#include <osl/diagnose.h>
#endif


#include <cppuhelper/factory.hxx>
#include <uno/lbnames.h>
namespace binfilter {

using namespace rtl;
using namespace ::com::sun::star;

// impress import
extern uno::Sequence< OUString > SAL_CALL SdImpressXMLImport_getSupportedServiceNames() throw();
extern OUString SAL_CALL SdImpressXMLImport_getImplementationName() throw();
extern uno::Reference< uno::XInterface > SAL_CALL SdImpressXMLImport_createInstance(const uno::Reference< lang::XMultiServiceFactory > & rSMgr) throw( uno::Exception );

// impress import.styles
extern uno::Sequence< OUString > SAL_CALL SdImpressXMLImport_Style_getSupportedServiceNames() throw();
extern OUString SAL_CALL SdImpressXMLImport_Style_getImplementationName() throw();
extern uno::Reference< uno::XInterface > SAL_CALL SdImpressXMLImport_Style_createInstance(const uno::Reference< lang::XMultiServiceFactory > & rSMgr) throw( uno::Exception );

// impress import.content
extern uno::Sequence< OUString > SAL_CALL SdImpressXMLImport_Content_getSupportedServiceNames() throw();
extern OUString SAL_CALL SdImpressXMLImport_Content_getImplementationName() throw();
extern uno::Reference< uno::XInterface > SAL_CALL SdImpressXMLImport_Content_createInstance(const uno::Reference< lang::XMultiServiceFactory > & rSMgr) throw( uno::Exception );

// impress import.meta
extern uno::Sequence< OUString > SAL_CALL SdImpressXMLImport_Meta_getSupportedServiceNames() throw();
extern OUString SAL_CALL SdImpressXMLImport_Meta_getImplementationName() throw();
extern uno::Reference< uno::XInterface > SAL_CALL SdImpressXMLImport_Meta_createInstance(const uno::Reference< lang::XMultiServiceFactory > & rSMgr) throw( uno::Exception );

// impress import.settings
extern uno::Sequence< OUString > SAL_CALL SdImpressXMLImport_Settings_getSupportedServiceNames() throw();
extern OUString SAL_CALL SdImpressXMLImport_Settings_getImplementationName() throw();
extern uno::Reference< uno::XInterface > SAL_CALL SdImpressXMLImport_Settings_createInstance(const uno::Reference< lang::XMultiServiceFactory > & rSMgr) throw( uno::Exception );

// for every module, export functionality is disabled for SVX_LIGHT (which means: SOPlayer)
#ifndef SVX_LIGHT
// impress export
extern uno::Sequence< OUString > SAL_CALL SdImpressXMLExport_getSupportedServiceNames() throw();
extern OUString SAL_CALL SdImpressXMLExport_getImplementationName() throw();
extern uno::Reference< uno::XInterface > SAL_CALL SdImpressXMLExport_createInstance(const uno::Reference< lang::XMultiServiceFactory > & rSMgr) throw( uno::Exception );

// impress export.styles
extern uno::Sequence< OUString > SAL_CALL SdImpressXMLExport_Style_getSupportedServiceNames() throw();
extern OUString SAL_CALL SdImpressXMLExport_Style_getImplementationName() throw();
extern uno::Reference< uno::XInterface > SAL_CALL SdImpressXMLExport_Style_createInstance(const uno::Reference< lang::XMultiServiceFactory > & rSMgr) throw( uno::Exception );

// impress export.content
extern uno::Sequence< OUString > SAL_CALL SdImpressXMLExport_Content_getSupportedServiceNames() throw();
extern OUString SAL_CALL SdImpressXMLExport_Content_getImplementationName() throw();
extern uno::Reference< uno::XInterface > SAL_CALL SdImpressXMLExport_Content_createInstance(const uno::Reference< lang::XMultiServiceFactory > & rSMgr) throw( uno::Exception );

// impress export.meta
extern uno::Sequence< OUString > SAL_CALL SdImpressXMLExport_Meta_getSupportedServiceNames() throw();
extern OUString SAL_CALL SdImpressXMLExport_Meta_getImplementationName() throw();
extern uno::Reference< uno::XInterface > SAL_CALL SdImpressXMLExport_Meta_createInstance(const uno::Reference< lang::XMultiServiceFactory > & rSMgr) throw( uno::Exception );

// impress export.settings
extern uno::Sequence< OUString > SAL_CALL SdImpressXMLExport_Settings_getSupportedServiceNames() throw();
extern OUString SAL_CALL SdImpressXMLExport_Settings_getImplementationName() throw();
extern uno::Reference< uno::XInterface > SAL_CALL SdImpressXMLExport_Settings_createInstance(const uno::Reference< lang::XMultiServiceFactory > & rSMgr) throw( uno::Exception );
#endif // #ifndef SVX_LIGHT

// draw import
extern uno::Sequence< OUString > SAL_CALL SdDrawXMLImport_getSupportedServiceNames() throw();
extern OUString SAL_CALL SdDrawXMLImport_getImplementationName() throw();
extern uno::Reference< uno::XInterface > SAL_CALL SdDrawXMLImport_createInstance(const uno::Reference< lang::XMultiServiceFactory > & rSMgr) throw( uno::Exception );

// draw import.styles
extern uno::Sequence< OUString > SAL_CALL SdDrawXMLImport_Style_getSupportedServiceNames() throw();
extern OUString SAL_CALL SdDrawXMLImport_Style_getImplementationName() throw();
extern uno::Reference< uno::XInterface > SAL_CALL SdDrawXMLImport_Style_createInstance(const uno::Reference< lang::XMultiServiceFactory > & rSMgr) throw( uno::Exception );

// draw import.content
extern uno::Sequence< OUString > SAL_CALL SdDrawXMLImport_Content_getSupportedServiceNames() throw();
extern OUString SAL_CALL SdDrawXMLImport_Content_getImplementationName() throw();
extern uno::Reference< uno::XInterface > SAL_CALL SdDrawXMLImport_Content_createInstance(const uno::Reference< lang::XMultiServiceFactory > & rSMgr) throw( uno::Exception );

// draw import.meta
extern uno::Sequence< OUString > SAL_CALL SdDrawXMLImport_Meta_getSupportedServiceNames() throw();
extern OUString SAL_CALL SdDrawXMLImport_Meta_getImplementationName() throw();
extern uno::Reference< uno::XInterface > SAL_CALL SdDrawXMLImport_Meta_createInstance(const uno::Reference< lang::XMultiServiceFactory > & rSMgr) throw( uno::Exception );

// draw import.settings
extern uno::Sequence< OUString > SAL_CALL SdDrawXMLImport_Settings_getSupportedServiceNames() throw();
extern OUString SAL_CALL SdDrawXMLImport_Settings_getImplementationName() throw();
extern uno::Reference< uno::XInterface > SAL_CALL SdDrawXMLImport_Settings_createInstance(const uno::Reference< lang::XMultiServiceFactory > & rSMgr) throw( uno::Exception );

#ifndef SVX_LIGHT
// draw export
extern uno::Sequence< OUString > SAL_CALL SdDrawXMLExport_getSupportedServiceNames() throw();
extern OUString SAL_CALL SdDrawXMLExport_getImplementationName() throw();
extern uno::Reference< uno::XInterface > SAL_CALL SdDrawXMLExport_createInstance(const uno::Reference< lang::XMultiServiceFactory > & rSMgr) throw( uno::Exception );

// drawing layer export
extern uno::Sequence< OUString > SAL_CALL DrawingLayerXMLExport_getSupportedServiceNames() throw();
extern OUString SAL_CALL DrawingLayerXMLExport_getImplementationName() throw();
extern uno::Reference< uno::XInterface > SAL_CALL DrawingLayerXMLExport_createInstance(const uno::Reference< lang::XMultiServiceFactory > & rSMgr) throw( uno::Exception );

// impress xml clipboard export
extern uno::Sequence< OUString > SAL_CALL ImpressXMLClipboardExport_getSupportedServiceNames() throw();
extern OUString SAL_CALL ImpressXMLClipboardExport_getImplementationName() throw();
extern uno::Reference< uno::XInterface > SAL_CALL ImpressXMLClipboardExport_createInstance(const uno::Reference< lang::XMultiServiceFactory > & rSMgr) throw( uno::Exception );

// draw export.style
extern uno::Sequence< OUString > SAL_CALL SdDrawXMLExport_Style_getSupportedServiceNames() throw();
extern OUString SAL_CALL SdDrawXMLExport_Style_getImplementationName() throw();
extern uno::Reference< uno::XInterface > SAL_CALL SdDrawXMLExport_Style_createInstance(const uno::Reference< lang::XMultiServiceFactory > & rSMgr) throw( uno::Exception );

// draw export.content
extern uno::Sequence< OUString > SAL_CALL SdDrawXMLExport_Content_getSupportedServiceNames() throw();
extern OUString SAL_CALL SdDrawXMLExport_Content_getImplementationName() throw();
extern uno::Reference< uno::XInterface > SAL_CALL SdDrawXMLExport_Content_createInstance(const uno::Reference< lang::XMultiServiceFactory > & rSMgr) throw( uno::Exception );

// draw export.meta
extern uno::Sequence< OUString > SAL_CALL SdDrawXMLExport_Meta_getSupportedServiceNames() throw();
extern OUString SAL_CALL SdDrawXMLExport_Meta_getImplementationName() throw();
extern uno::Reference< uno::XInterface > SAL_CALL SdDrawXMLExport_Meta_createInstance(const uno::Reference< lang::XMultiServiceFactory > & rSMgr) throw( uno::Exception );

// draw export.settings
extern uno::Sequence< OUString > SAL_CALL SdDrawXMLExport_Settings_getSupportedServiceNames() throw();
extern OUString SAL_CALL SdDrawXMLExport_Settings_getImplementationName() throw();
extern uno::Reference< uno::XInterface > SAL_CALL SdDrawXMLExport_Settings_createInstance(const uno::Reference< lang::XMultiServiceFactory > & rSMgr) throw( uno::Exception );
#endif // #ifndef SVX_LIGHT

// complete chart is disabled for SVX_LIGHT
#ifndef SVX_LIGHT
// chart import
// ------------
extern uno::Sequence< OUString > SAL_CALL SchXMLImport_getSupportedServiceNames() throw();
extern OUString SAL_CALL SchXMLImport_getImplementationName() throw();
extern uno::Reference< uno::XInterface > SAL_CALL SchXMLImport_createInstance(const uno::Reference< lang::XMultiServiceFactory > & rSMgr) throw( uno::Exception );

// styles
extern uno::Sequence< OUString > SAL_CALL SchXMLImport_Styles_getSupportedServiceNames() throw();
extern OUString SAL_CALL SchXMLImport_Styles_getImplementationName() throw();
extern uno::Reference< uno::XInterface > SAL_CALL SchXMLImport_Styles_createInstance(const uno::Reference< lang::XMultiServiceFactory > & rSMgr) throw( uno::Exception );

// content
extern uno::Sequence< OUString > SAL_CALL SchXMLImport_Content_getSupportedServiceNames() throw();
extern OUString SAL_CALL SchXMLImport_Content_getImplementationName() throw();
extern uno::Reference< uno::XInterface > SAL_CALL SchXMLImport_Content_createInstance(const uno::Reference< lang::XMultiServiceFactory > & rSMgr) throw( uno::Exception );

// chart export
// ------------
extern uno::Sequence< OUString > SAL_CALL SchXMLExport_getSupportedServiceNames() throw();
extern OUString SAL_CALL SchXMLExport_getImplementationName() throw();
extern uno::Reference< uno::XInterface > SAL_CALL SchXMLExport_createInstance(const uno::Reference< lang::XMultiServiceFactory > & rSMgr) throw( uno::Exception );

// styles
extern uno::Sequence< OUString > SAL_CALL SchXMLExport_Styles_getSupportedServiceNames() throw();
extern OUString SAL_CALL SchXMLExport_Styles_getImplementationName() throw();
extern uno::Reference< uno::XInterface > SAL_CALL SchXMLExport_Styles_createInstance(const uno::Reference< lang::XMultiServiceFactory > & rSMgr) throw( uno::Exception );

// content
extern uno::Sequence< OUString > SAL_CALL SchXMLExport_Content_getSupportedServiceNames() throw();
extern OUString SAL_CALL SchXMLExport_Content_getImplementationName() throw();
extern uno::Reference< uno::XInterface > SAL_CALL SchXMLExport_Content_createInstance(const uno::Reference< lang::XMultiServiceFactory > & rSMgr) throw( uno::Exception );
#endif // #ifndef SVX_LIGHT


#ifndef SVX_LIGHT
// meta export
extern uno::Sequence< OUString > SAL_CALL XMLMetaExportComponent_getSupportedServiceNames() throw();
extern OUString SAL_CALL XMLMetaExportComponent_getImplementationName() throw();
extern uno::Reference< uno::XInterface > SAL_CALL XMLMetaExportComponent_createInstance(const uno::Reference< lang::XMultiServiceFactory > & rSMgr) throw( uno::Exception );
#endif // #ifndef SVX_LIGHT

// meta import
extern uno::Sequence< OUString > SAL_CALL XMLMetaImportComponent_getSupportedServiceNames() throw();
extern OUString SAL_CALL XMLMetaImportComponent_getImplementationName() throw();
extern uno::Reference< uno::XInterface > SAL_CALL XMLMetaImportComponent_createInstance(const uno::Reference< lang::XMultiServiceFactory > & rSMgr) throw( uno::Exception );

// component register functionality only for shared lib
#ifndef SVX_LIGHT

//
#ifdef __cplusplus
extern "C"
{
#endif

void SAL_CALL component_getImplementationEnvironment( const sal_Char ** ppEnvTypeName, uno_Environment ** ppEnv )
{
    *ppEnvTypeName = CPPU_CURRENT_LANGUAGE_BINDING_NAME;
}

void * SAL_CALL component_getFactory( const sal_Char * pImplName, void * pServiceManager, void * pRegistryKey )
{
    void * pRet = 0;
    if( pServiceManager )
    {
        uno::Reference< lang::XMultiServiceFactory > xMSF( reinterpret_cast< lang::XMultiServiceFactory * >( pServiceManager ) );

        uno::Reference< lang::XSingleServiceFactory > xFactory;

        const sal_Int32 nImplNameLen = strlen( pImplName );
        if( SdImpressXMLImport_getImplementationName().equalsAsciiL( pImplName, nImplNameLen ) )
        {
            xFactory = ::cppu::createSingleFactory( xMSF,
                SdImpressXMLImport_getImplementationName(),
                SdImpressXMLImport_createInstance,
                SdImpressXMLImport_getSupportedServiceNames() );
        }
        else if( SdImpressXMLImport_Style_getImplementationName().equalsAsciiL( pImplName, nImplNameLen ) )
        {
            xFactory = ::cppu::createSingleFactory( xMSF,
                SdImpressXMLImport_Style_getImplementationName(),
                SdImpressXMLImport_Style_createInstance,
                SdImpressXMLImport_Style_getSupportedServiceNames() );
        }
        else if( SdImpressXMLImport_Content_getImplementationName().equalsAsciiL( pImplName, nImplNameLen ) )
        {
            xFactory = ::cppu::createSingleFactory( xMSF,
                SdImpressXMLImport_Content_getImplementationName(),
                SdImpressXMLImport_Content_createInstance,
                SdImpressXMLImport_Content_getSupportedServiceNames() );
        }
        else if( SdImpressXMLImport_Meta_getImplementationName().equalsAsciiL( pImplName, nImplNameLen ) )
        {
            xFactory = ::cppu::createSingleFactory( xMSF,
                SdImpressXMLImport_Meta_getImplementationName(),
                SdImpressXMLImport_Meta_createInstance,
                SdImpressXMLImport_Meta_getSupportedServiceNames() );
        }
        else if( SdImpressXMLImport_Settings_getImplementationName().equalsAsciiL( pImplName, nImplNameLen ) )
        {
            xFactory = ::cppu::createSingleFactory( xMSF,
                SdImpressXMLImport_Settings_getImplementationName(),
                SdImpressXMLImport_Settings_createInstance,
                SdImpressXMLImport_Settings_getSupportedServiceNames() );
        }
        else if( SdDrawXMLImport_getImplementationName().equalsAsciiL( pImplName, nImplNameLen ) )
        {
            xFactory = ::cppu::createSingleFactory( xMSF,
                SdDrawXMLImport_getImplementationName(),
                SdDrawXMLImport_createInstance,
                SdDrawXMLImport_getSupportedServiceNames() );
        }
        else if( SdDrawXMLImport_Style_getImplementationName().equalsAsciiL( pImplName, nImplNameLen ) )
        {
            xFactory = ::cppu::createSingleFactory( xMSF,
                SdDrawXMLImport_Style_getImplementationName(),
                SdDrawXMLImport_Style_createInstance,
                SdDrawXMLImport_Style_getSupportedServiceNames() );
        }
        else if( SdDrawXMLImport_Content_getImplementationName().equalsAsciiL( pImplName, nImplNameLen ) )
        {
            xFactory = ::cppu::createSingleFactory( xMSF,
                SdDrawXMLImport_Content_getImplementationName(),
                SdDrawXMLImport_Content_createInstance,
                SdDrawXMLImport_Content_getSupportedServiceNames() );
        }
        else if( SdDrawXMLImport_Meta_getImplementationName().equalsAsciiL( pImplName, nImplNameLen ) )
        {
            xFactory = ::cppu::createSingleFactory( xMSF,
                SdDrawXMLImport_Meta_getImplementationName(),
                SdDrawXMLImport_Meta_createInstance,
                SdDrawXMLImport_Meta_getSupportedServiceNames() );
        }
        else if( SdDrawXMLImport_Settings_getImplementationName().equalsAsciiL( pImplName, nImplNameLen ) )
        {
            xFactory = ::cppu::createSingleFactory( xMSF,
                SdDrawXMLImport_Settings_getImplementationName(),
                SdDrawXMLImport_Settings_createInstance,
                SdDrawXMLImport_Settings_getSupportedServiceNames() );
        }
        else if( SdImpressXMLExport_getImplementationName().equalsAsciiL( pImplName, nImplNameLen ) )
        {
            xFactory = ::cppu::createSingleFactory( xMSF,
                SdImpressXMLExport_getImplementationName(),
                SdImpressXMLExport_createInstance,
                SdImpressXMLExport_getSupportedServiceNames() );
        }
        else if( SdImpressXMLExport_Style_getImplementationName().equalsAsciiL( pImplName, nImplNameLen ) )
        {
            xFactory = ::cppu::createSingleFactory( xMSF,
                SdImpressXMLExport_Style_getImplementationName(),
                SdImpressXMLExport_Style_createInstance,
                SdImpressXMLExport_Style_getSupportedServiceNames() );
        }
        else if( SdImpressXMLExport_Content_getImplementationName().equalsAsciiL( pImplName, nImplNameLen ) )
        {
            xFactory = ::cppu::createSingleFactory( xMSF,
                SdImpressXMLExport_Content_getImplementationName(),
                SdImpressXMLExport_Content_createInstance,
                SdImpressXMLExport_Content_getSupportedServiceNames() );
        }
        else if( SdImpressXMLExport_Meta_getImplementationName().equalsAsciiL( pImplName, nImplNameLen ) )
        {
            xFactory = ::cppu::createSingleFactory( xMSF,
                SdImpressXMLExport_Meta_getImplementationName(),
                SdImpressXMLExport_Meta_createInstance,
                SdImpressXMLExport_Meta_getSupportedServiceNames() );
        }
        else if( SdImpressXMLExport_Settings_getImplementationName().equalsAsciiL( pImplName, nImplNameLen ) )
        {
            xFactory = ::cppu::createSingleFactory( xMSF,
                SdImpressXMLExport_Settings_getImplementationName(),
                SdImpressXMLExport_Settings_createInstance,
                SdImpressXMLExport_Settings_getSupportedServiceNames() );
        }
        else if( SdDrawXMLExport_getImplementationName().equalsAsciiL( pImplName, nImplNameLen ) )
        {
            xFactory = ::cppu::createSingleFactory( xMSF,
                SdDrawXMLExport_getImplementationName(),
                SdDrawXMLExport_createInstance,
                SdDrawXMLExport_getSupportedServiceNames() );
        }
        else if( DrawingLayerXMLExport_getImplementationName().equalsAsciiL( pImplName, nImplNameLen ) )
        {
            xFactory = ::cppu::createSingleFactory( xMSF,
                DrawingLayerXMLExport_getImplementationName(),
                DrawingLayerXMLExport_createInstance,
                DrawingLayerXMLExport_getSupportedServiceNames() );
        }
        else if( ImpressXMLClipboardExport_getImplementationName().equalsAsciiL( pImplName, nImplNameLen ) )
        {
            xFactory = ::cppu::createSingleFactory( xMSF,
                ImpressXMLClipboardExport_getImplementationName(),
                ImpressXMLClipboardExport_createInstance,
                ImpressXMLClipboardExport_getSupportedServiceNames() );
        }
        else if( SdDrawXMLExport_Style_getImplementationName().equalsAsciiL( pImplName, nImplNameLen ) )
        {
            xFactory = ::cppu::createSingleFactory( xMSF,
                SdDrawXMLExport_Style_getImplementationName(),
                SdDrawXMLExport_Style_createInstance,
                SdDrawXMLExport_Style_getSupportedServiceNames() );
        }
        else if( SdDrawXMLExport_Content_getImplementationName().equalsAsciiL( pImplName, nImplNameLen ) )
        {
            xFactory = ::cppu::createSingleFactory( xMSF,
                SdDrawXMLExport_Content_getImplementationName(),
                SdDrawXMLExport_Content_createInstance,
                SdDrawXMLExport_Content_getSupportedServiceNames() );
        }
        else if( SdDrawXMLExport_Meta_getImplementationName().equalsAsciiL( pImplName, nImplNameLen ) )
        {
            xFactory = ::cppu::createSingleFactory( xMSF,
                SdDrawXMLExport_Meta_getImplementationName(),
                SdDrawXMLExport_Meta_createInstance,
                SdDrawXMLExport_Meta_getSupportedServiceNames() );
        }
        else if( SdDrawXMLExport_Settings_getImplementationName().equalsAsciiL( pImplName, nImplNameLen ) )
        {
            xFactory = ::cppu::createSingleFactory( xMSF,
                SdDrawXMLExport_Settings_getImplementationName(),
                SdDrawXMLExport_Settings_createInstance,
                SdDrawXMLExport_Settings_getSupportedServiceNames() );
        }
        else if( SchXMLImport_getImplementationName().equalsAsciiL( pImplName, nImplNameLen ) )
        {
            xFactory = ::cppu::createSingleFactory( xMSF,
                SchXMLImport_getImplementationName(),
                SchXMLImport_createInstance,
                SchXMLImport_getSupportedServiceNames() );
        }
        else if( SchXMLExport_getImplementationName().equalsAsciiL( pImplName, nImplNameLen ) )
        {
            xFactory = ::cppu::createSingleFactory( xMSF,
                SchXMLExport_getImplementationName(),
                SchXMLExport_createInstance,
                SchXMLExport_getSupportedServiceNames() );
        }

        else if( SchXMLImport_Styles_getImplementationName().equalsAsciiL( pImplName, nImplNameLen ) )
        {
            xFactory = ::cppu::createSingleFactory( xMSF,
                SchXMLImport_Styles_getImplementationName(),
                SchXMLImport_Styles_createInstance,
                SchXMLImport_Styles_getSupportedServiceNames() );
        }
        else if( SchXMLExport_Styles_getImplementationName().equalsAsciiL( pImplName, nImplNameLen ) )
        {
            xFactory = ::cppu::createSingleFactory( xMSF,
                SchXMLExport_Styles_getImplementationName(),
                SchXMLExport_Styles_createInstance,
                SchXMLExport_Styles_getSupportedServiceNames() );
        }
        else if( SchXMLImport_Content_getImplementationName().equalsAsciiL( pImplName, nImplNameLen ) )
        {
            xFactory = ::cppu::createSingleFactory( xMSF,
                SchXMLImport_Content_getImplementationName(),
                SchXMLImport_Content_createInstance,
                SchXMLImport_Content_getSupportedServiceNames() );
        }
        else if( SchXMLExport_Content_getImplementationName().equalsAsciiL( pImplName, nImplNameLen ) )
        {
            xFactory = ::cppu::createSingleFactory( xMSF,
                SchXMLExport_Content_getImplementationName(),
                SchXMLExport_Content_createInstance,
                SchXMLExport_Content_getSupportedServiceNames() );
        }
        else if ( XMLMetaExportComponent_getImplementationName().equalsAsciiL( pImplName, nImplNameLen ) )
        {
            xFactory = ::cppu::createSingleFactory( xMSF,
                XMLMetaExportComponent_getImplementationName(),
                XMLMetaExportComponent_createInstance,
                XMLMetaExportComponent_getSupportedServiceNames() );
        }
        else if ( XMLMetaImportComponent_getImplementationName().equalsAsciiL( pImplName, nImplNameLen ) )
        {
            xFactory = ::cppu::createSingleFactory( xMSF,
                XMLMetaImportComponent_getImplementationName(),
                XMLMetaImportComponent_createInstance,
                XMLMetaImportComponent_getSupportedServiceNames() );
        }
        if( xFactory.is())
        {
            xFactory->acquire();
            pRet = xFactory.get();
        }
    }
    return pRet;
}

#ifdef __cplusplus
}
#endif

#else

// register necessary services manually
sal_Bool XMLRegisterServices( ::com::sun::star::uno::Reference< ::com::sun::star::lang::XMultiServiceFactory > xServiceFactory )
{
    // ask the MultiServiceFactory for the XSet interface
    uno::Reference< ::com::sun::star::container::XSet > xSet( xServiceFactory, uno::UNO_QUERY );
            
    if ( !xSet.is() )
        return sal_False;
        
    try
    {
        uno::Any	aAny;

        // SdImpressXMLImport
        aAny <<= ::cppu::createSingleFactory( xServiceFactory,
                                              SdImpressXMLImport_getImplementationName(),
                                              SdImpressXMLImport_createInstance,
                                              SdImpressXMLImport_getSupportedServiceNames() );
        xSet->insert( aAny );

        aAny <<= ::cppu::createSingleFactory( xServiceFactory,
                                              SdImpressXMLImport_Style_getImplementationName(),
                                              SdImpressXMLImport_Style_createInstance,
                                              SdImpressXMLImport_Style_getSupportedServiceNames() );
        xSet->insert( aAny );

        aAny <<= ::cppu::createSingleFactory( xServiceFactory,
                                              SdImpressXMLImport_Content_getImplementationName(),
                                              SdImpressXMLImport_Content_createInstance,
                                              SdImpressXMLImport_Content_getSupportedServiceNames() );
        xSet->insert( aAny );

        aAny <<= ::cppu::createSingleFactory( xServiceFactory,
                                              SdImpressXMLImport_Meta_getImplementationName(),
                                              SdImpressXMLImport_Meta_createInstance,
                                              SdImpressXMLImport_Meta_getSupportedServiceNames() );
        xSet->insert( aAny );

        aAny <<= ::cppu::createSingleFactory( xServiceFactory,
                                              SdImpressXMLImport_Settings_getImplementationName(),
                                              SdImpressXMLImport_Settings_createInstance,
                                              SdImpressXMLImport_Settings_getSupportedServiceNames() );
        xSet->insert( aAny );

        // SdDrawXMLImport
        aAny <<= ::cppu::createSingleFactory( xServiceFactory,
                                              SdDrawXMLImport_getImplementationName(),
                                              SdDrawXMLImport_createInstance,
                                              SdDrawXMLImport_getSupportedServiceNames() );
        xSet->insert( aAny );

        aAny <<= ::cppu::createSingleFactory( xServiceFactory,
                                              SdDrawXMLImport_Style_getImplementationName(),
                                              SdDrawXMLImport_Style_createInstance,
                                              SdDrawXMLImport_Style_getSupportedServiceNames() );
        xSet->insert( aAny );

        aAny <<= ::cppu::createSingleFactory( xServiceFactory,
                                              SdDrawXMLImport_Content_getImplementationName(),
                                              SdDrawXMLImport_Content_createInstance,
                                              SdDrawXMLImport_Content_getSupportedServiceNames() );
        xSet->insert( aAny );

        aAny <<= ::cppu::createSingleFactory( xServiceFactory,
                                              SdDrawXMLImport_Meta_getImplementationName(),
                                              SdDrawXMLImport_Meta_createInstance,
                                              SdDrawXMLImport_Meta_getSupportedServiceNames() );
        xSet->insert( aAny );

        aAny <<= ::cppu::createSingleFactory( xServiceFactory,
                                              SdDrawXMLImport_Settings_getImplementationName(),
                                              SdDrawXMLImport_Settings_createInstance,
                                              SdDrawXMLImport_Settings_getSupportedServiceNames() );
        xSet->insert( aAny );
    }
    catch( uno::Exception& )
    {
#ifdef DBG_UTIL
        DBG_ERROR( "Cannot register XMLOFF services" );
#endif			
        return sal_False; 
    }

    return sal_True;
}	

#endif // #ifndef SVX_LIGHT
}//end of namespace binfilter
