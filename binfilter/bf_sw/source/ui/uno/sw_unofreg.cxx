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

#include <string.h>

#include <com/sun/star/registry/XRegistryKey.hpp>

#include <osl/diagnose.h>

#include <cppuhelper/factory.hxx>
#include <uno/lbnames.h>
#include <SwXFilterOptions.hxx>
namespace binfilter {

using namespace ::com::sun::star;
using namespace ::com::sun::star::lang;

using ::rtl::OUString;

// writer documents
extern uno::Sequence< OUString > SAL_CALL SwTextDocument_getSupportedServiceNames() throw();
extern OUString SAL_CALL SwTextDocument_getImplementationName() throw();
extern uno::Reference< uno::XInterface > SAL_CALL SwTextDocument_createInstance( const uno::Reference< XMultiServiceFactory > &rSMgr ) throw( uno::Exception );
extern uno::Sequence< OUString > SAL_CALL SwWebDocument_getSupportedServiceNames() throw();
extern OUString SAL_CALL SwWebDocument_getImplementationName() throw();
extern uno::Reference< uno::XInterface > SAL_CALL SwWebDocument_createInstance( const uno::Reference< XMultiServiceFactory > &rSMgr ) throw( uno::Exception );
extern uno::Sequence< OUString > SAL_CALL SwGlobalDocument_getSupportedServiceNames() throw();
extern OUString SAL_CALL SwGlobalDocument_getImplementationName() throw();
extern uno::Reference< uno::XInterface > SAL_CALL SwGlobalDocument_createInstance( const uno::Reference< XMultiServiceFactory > &rSMgr ) throw( uno::Exception );

// xml import
extern uno::Sequence< OUString > SAL_CALL SwXMLImport_getSupportedServiceNames() throw();
extern OUString SAL_CALL SwXMLImport_getImplementationName() throw();
extern uno::Reference< uno::XInterface > SAL_CALL SwXMLImport_createInstance(const uno::Reference< XMultiServiceFactory > & rSMgr)	throw( uno::Exception );
extern uno::Sequence< OUString > SAL_CALL SwXMLImportStyles_getSupportedServiceNames() throw();
extern OUString SAL_CALL SwXMLImportStyles_getImplementationName() throw();
extern uno::Reference< uno::XInterface > SAL_CALL SwXMLImportStyles_createInstance(const uno::Reference< XMultiServiceFactory > & rSMgr)	throw( uno::Exception );
extern uno::Sequence< OUString > SAL_CALL SwXMLImportContent_getSupportedServiceNames() throw();
extern OUString SAL_CALL SwXMLImportContent_getImplementationName() throw();
extern uno::Reference< uno::XInterface > SAL_CALL SwXMLImportContent_createInstance(const uno::Reference< XMultiServiceFactory > & rSMgr)	throw( uno::Exception );

extern uno::Sequence< OUString > SAL_CALL     SwXMLImportMeta_getSupportedServiceNames() throw();
extern OUString SAL_CALL     SwXMLImportMeta_getImplementationName() throw();
extern uno::Reference< uno::XInterface > SAL_CALL SwXMLImportMeta_createInstance(const uno::Reference< XMultiServiceFactory > & rSMgr)	throw( uno::Exception );

extern uno::Sequence< OUString > SAL_CALL SwXMLImportSettings_getSupportedServiceNames() throw();
extern OUString SAL_CALL SwXMLImportSettings_getImplementationName() throw();
extern uno::Reference< uno::XInterface > SAL_CALL SwXMLImportSettings_createInstance(const uno::Reference< XMultiServiceFactory > & rSMgr)	throw( uno::Exception );

// xml export
extern uno::Sequence< OUString > SAL_CALL SwXMLExport_getSupportedServiceNames() throw();
extern OUString SAL_CALL SwXMLExport_getImplementationName() throw();
extern uno::Reference< uno::XInterface > SAL_CALL SwXMLExport_createInstance(const uno::Reference< XMultiServiceFactory > & rSMgr)	throw( uno::Exception );
extern uno::Sequence< OUString > SAL_CALL SwXMLExportContent_getSupportedServiceNames() throw();
extern OUString SAL_CALL SwXMLExportContent_getImplementationName() throw();
extern uno::Reference< uno::XInterface > SAL_CALL SwXMLExportContent_createInstance(const uno::Reference< XMultiServiceFactory > & rSMgr)	throw( uno::Exception );
extern uno::Sequence< OUString > SAL_CALL SwXMLExportStyles_getSupportedServiceNames() throw();
extern OUString SAL_CALL SwXMLExportStyles_getImplementationName() throw();
extern uno::Reference< uno::XInterface > SAL_CALL SwXMLExportStyles_createInstance(const uno::Reference< XMultiServiceFactory > & rSMgr)	throw( uno::Exception );
extern uno::Sequence< OUString > SAL_CALL SwXMLExportMeta_getSupportedServiceNames() throw();
extern OUString SAL_CALL SwXMLExportMeta_getImplementationName() throw();
extern uno::Reference< uno::XInterface > SAL_CALL SwXMLExportMeta_createInstance(const uno::Reference< XMultiServiceFactory > & rSMgr)	throw( uno::Exception );
extern uno::Sequence< OUString > SAL_CALL SwXMLExportSettings_getSupportedServiceNames() throw();
extern OUString SAL_CALL SwXMLExportSettings_getImplementationName() throw();
extern uno::Reference< uno::XInterface > SAL_CALL SwXMLExportSettings_createInstance(const uno::Reference< XMultiServiceFactory > & rSMgr)	throw( uno::Exception );

extern uno::Sequence< OUString > SAL_CALL SwXModule_getSupportedServiceNames() throw();
extern OUString SAL_CALL SwXModule_getImplementationName() throw();
extern uno::Reference< uno::XInterface > SAL_CALL SwXModule_createInstance(const uno::Reference< XMultiServiceFactory > & rSMgr) throw( uno::Exception );

//
#ifdef __cplusplus
extern "C"
{
#endif

void SAL_CALL component_getImplementationEnvironment(
        const sal_Char ** ppEnvTypeName,
        uno_Environment ** /*ppEnv*/ )
{
    *ppEnvTypeName = CPPU_CURRENT_LANGUAGE_BINDING_NAME;
}

void * SAL_CALL component_getFactory( const sal_Char * pImplName,
                                      void * pServiceManager,
                                      void * /*pRegistryKey*/ )
{
    void * pRet = 0;
    if( pServiceManager )
    {
        uno::Reference< XMultiServiceFactory > xMSF(
            reinterpret_cast< XMultiServiceFactory * >( pServiceManager ) );

        uno::Reference< XSingleServiceFactory > xFactory;

        const sal_Int32 nImplNameLen = strlen( pImplName );
        if( SwXMLImport_getImplementationName().equalsAsciiL( pImplName,
                                                              nImplNameLen ) )
        {
            xFactory = ::cppu::createSingleFactory( xMSF,
                SwXMLImport_getImplementationName(),
                SwXMLImport_createInstance,
                SwXMLImport_getSupportedServiceNames() );
        }
        else if( SwXMLImportStyles_getImplementationName().equalsAsciiL(
                                                    pImplName, nImplNameLen ) )
        {
            xFactory = ::cppu::createSingleFactory( xMSF,
                SwXMLImportStyles_getImplementationName(),
                SwXMLImportStyles_createInstance,
                SwXMLImportStyles_getSupportedServiceNames() );
        }
        else if( SwXMLImportContent_getImplementationName().equalsAsciiL(
                                                    pImplName, nImplNameLen ) )
        {
            xFactory = ::cppu::createSingleFactory( xMSF,
                SwXMLImportContent_getImplementationName(),
                SwXMLImportContent_createInstance,
                SwXMLImportContent_getSupportedServiceNames() );
        }
        else if( SwXMLImportMeta_getImplementationName().equalsAsciiL(
                                                    pImplName, nImplNameLen ) )
        {
            xFactory = ::cppu::createSingleFactory( xMSF,
                SwXMLImportMeta_getImplementationName(),
                SwXMLImportMeta_createInstance,
                SwXMLImportMeta_getSupportedServiceNames() );
        }
        else if( SwXMLExport_getImplementationName().equalsAsciiL( pImplName,
                                                            nImplNameLen ) )
        {
            xFactory = ::cppu::createSingleFactory( xMSF,
                SwXMLExport_getImplementationName(),
                SwXMLExport_createInstance,
                SwXMLExport_getSupportedServiceNames() );
        }
        else if( SwXMLExportStyles_getImplementationName().equalsAsciiL(
                                                    pImplName, nImplNameLen ) )
        {
            xFactory = ::cppu::createSingleFactory( xMSF,
                SwXMLExportStyles_getImplementationName(),
                SwXMLExportStyles_createInstance,
                SwXMLExportStyles_getSupportedServiceNames() );
        }
        else if( SwXMLExportContent_getImplementationName().equalsAsciiL(
                                                    pImplName, nImplNameLen ) )
        {
            xFactory = ::cppu::createSingleFactory( xMSF,
                SwXMLExportContent_getImplementationName(),
                SwXMLExportContent_createInstance,
                SwXMLExportContent_getSupportedServiceNames() );
        }
        else if( SwXMLExportMeta_getImplementationName().equalsAsciiL(
                                                    pImplName, nImplNameLen ) )
        {
            xFactory = ::cppu::createSingleFactory( xMSF,
                SwXMLExportMeta_getImplementationName(),
                SwXMLExportMeta_createInstance,
                SwXMLExportMeta_getSupportedServiceNames() );
        }
        else if( SwXMLExportSettings_getImplementationName().equalsAsciiL(
                                                    pImplName, nImplNameLen ) )
        {
            xFactory = ::cppu::createSingleFactory( xMSF,
                SwXMLExportSettings_getImplementationName(),
                SwXMLExportSettings_createInstance,
                SwXMLExportSettings_getSupportedServiceNames() );
        }
        else if( SwXMLImportSettings_getImplementationName().equalsAsciiL(
                                                    pImplName, nImplNameLen ) )
        {
            xFactory = ::cppu::createSingleFactory( xMSF,
                SwXMLImportSettings_getImplementationName(),
                SwXMLImportSettings_createInstance,
                SwXMLImportSettings_getSupportedServiceNames() );
        }
        else if( SwXModule_getImplementationName().equalsAsciiL(
                                                    pImplName, nImplNameLen ) )
        {
            xFactory = ::cppu::createSingleFactory( xMSF,
                SwXModule_getImplementationName(),
                SwXModule_createInstance,
                SwXModule_getSupportedServiceNames() );
        }
        else if( SwXFilterOptions::getImplementationName_Static().equalsAsciiL(
                                                    pImplName, nImplNameLen ) )
        {
            xFactory = ::cppu::createSingleFactory( xMSF,
                SwXFilterOptions::getImplementationName_Static(),
                SwXFilterOptions_createInstance,
                SwXFilterOptions::getSupportedServiceNames_Static() );
        }
        else if( SwTextDocument_getImplementationName().equalsAsciiL(
                                                    pImplName, nImplNameLen ) )
        {
            xFactory = ::cppu::createSingleFactory( xMSF,
                SwTextDocument_getImplementationName(),
                SwTextDocument_createInstance,
                SwTextDocument_getSupportedServiceNames() );
        }
        else if( SwWebDocument_getImplementationName().equalsAsciiL(
                                                    pImplName, nImplNameLen ) )
        {
            xFactory = ::cppu::createSingleFactory( xMSF,
                SwWebDocument_getImplementationName(),
                SwWebDocument_createInstance,
                SwWebDocument_getSupportedServiceNames() );
        }
        else if( SwGlobalDocument_getImplementationName().equalsAsciiL(
                                                    pImplName, nImplNameLen ) )
        {
            xFactory = ::cppu::createSingleFactory( xMSF,
                SwGlobalDocument_getImplementationName(),
                SwGlobalDocument_createInstance,
                SwGlobalDocument_getSupportedServiceNames() );
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
}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
