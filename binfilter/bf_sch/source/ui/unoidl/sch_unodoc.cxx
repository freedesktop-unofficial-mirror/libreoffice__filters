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

// System - Includes -----------------------------------------------------

#include <bf_sfx2/docfac.hxx>


#include "schmod.hxx"

#include <vos/mutex.hxx>
#include <vcl/svapp.hxx>
namespace binfilter {

using namespace ::com::sun::star;

::rtl::OUString SAL_CALL SchDocument_getImplementationName() throw()
{
    return ::rtl::OUString( RTL_CONSTASCII_USTRINGPARAM( "com.sun.star.comp.Chart.ChartDocument" ) );
}

uno::Sequence< ::rtl::OUString > SAL_CALL SchDocument_getSupportedServiceNames() throw()
{
    uno::Sequence< ::rtl::OUString > aSeq( 3 );
    aSeq[0] = ::rtl::OUString( RTL_CONSTASCII_USTRINGPARAM( "com.sun.star.chart.ChartDocument" ) );
    aSeq[1] = ::rtl::OUString( RTL_CONSTASCII_USTRINGPARAM( "com.sun.star.chart.ChartTableAddressSupplier" ) );
    aSeq[2] = ::rtl::OUString( RTL_CONSTASCII_USTRINGPARAM( "com.sun.star.xml.UserDefinedAttributeSupplier" ) );

    return aSeq;
}

uno::Reference< uno::XInterface > SAL_CALL SchDocument_createInstance(
                const uno::Reference< lang::XMultiServiceFactory > & rSMgr ) throw( uno::Exception )
{
    SolarMutexGuard aGuard;

    // to create the service the SW_MOD should be already initialized
    DBG_ASSERT( SCH_MOD1(), "No StarChart module!" );
    
    if ( SCH_MOD1() )
    {
        ::rtl::OUString aFactoryURL( RTL_CONSTASCII_USTRINGPARAM ( "private:factory/schart" ) );
        const SfxObjectFactory* pFactory = SfxObjectFactory::GetFactory( aFactoryURL );
        if ( pFactory )
        {
            SfxObjectShell* pShell = pFactory->CreateObject();
            if( pShell )
                return uno::Reference< uno::XInterface >( pShell->GetModel() );
        }
    }

    return uno::Reference< uno::XInterface >();
}


}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
