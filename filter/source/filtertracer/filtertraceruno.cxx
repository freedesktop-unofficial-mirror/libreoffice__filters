/*************************************************************************
 *
 *  $RCSfile: filtertraceruno.cxx,v $
 *
 *  $Revision: 1.2 $
 *
 *  last change: $Author: hr $ $Date: 2003-03-25 17:57:45 $
 *
 *  The Contents of this file are made available subject to the terms of
 *  either of the following licenses
 *
 *         - GNU Lesser General Public License Version 2.1
 *         - Sun Industry Standards Source License Version 1.1
 *
 *  Sun Microsystems Inc., October, 2000
 *
 *  GNU Lesser General Public License Version 2.1
 *  =============================================
 *  Copyright 2000 by Sun Microsystems, Inc.
 *  901 San Antonio Road, Palo Alto, CA 94303, USA
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public
 *  License version 2.1, as published by the Free Software Foundation.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public
 *  License along with this library; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 *  MA  02111-1307  USA
 *
 *
 *  Sun Industry Standards Source License Version 1.1
 *  =================================================
 *  The contents of this file are subject to the Sun Industry Standards
 *  Source License Version 1.1 (the "License"); You may not use this file
 *  except in compliance with the License. You may obtain a copy of the
 *  License at http://www.openoffice.org/license.html.
 *
 *  Software provided under this License is provided on an "AS IS" basis,
 *  WITHOUT WARRANTY OF ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING,
 *  WITHOUT LIMITATION, WARRANTIES THAT THE SOFTWARE IS FREE OF DEFECTS,
 *  MERCHANTABLE, FIT FOR A PARTICULAR PURPOSE, OR NON-INFRINGING.
 *  See the License for the specific provisions governing your rights and
 *  obligations concerning the Software.
 *
 *  The Initial Developer of the Original Code is: Sun Microsystems, Inc.
 *
 *  Copyright: 2000 by Sun Microsystems, Inc.
 *
 *  All Rights Reserved.
 *
 *  Contributor(s): _______________________________________
 *
 *
 ************************************************************************/

#include "filtertracer.hxx"

#include <cppuhelper/factory.hxx>
#include <uno/mapping.hxx>

// -------------------
// - factory methods -
// -------------------

static REF( NMSP_UNO::XInterface ) SAL_CALL create_FilterTracer( const REF( NMSP_LANG::XMultiServiceFactory )& rxFact )
{
    return REF( NMSP_UNO::XInterface )( *new FilterTracer( rxFact ) );
}

// ------------------------------------------
// - component_getImplementationEnvironment -
// ------------------------------------------

extern "C" void SAL_CALL component_getImplementationEnvironment( const sal_Char ** ppEnvTypeName, uno_Environment ** ppEnv )
{
    *ppEnvTypeName = CPPU_CURRENT_LANGUAGE_BINDING_NAME;
}

// -----------------------
// - component_writeInfo -
// -----------------------

extern "C" sal_Bool SAL_CALL component_writeInfo( void* pServiceManager, void* pRegistryKey )
{
    sal_Bool bRet = sal_False;

    if( pRegistryKey )
    {
        try
        {
            NMSP_UNO::Reference< com::sun::star::registry::XRegistryKey > xNewKey(
                reinterpret_cast< com::sun::star::registry::XRegistryKey * >( pRegistryKey )->createKey(
                    FilterTracer_getImplementationName() ) ); 
            xNewKey = xNewKey->createKey( B2UCONST( "/UNO/SERVICES" ) );
            const SEQ( rtl::OUString )& rSNL = FilterTracer_getSupportedServiceNames();
            const rtl::OUString * pArray = rSNL.getConstArray();
            for ( sal_Int32 nPos = rSNL.getLength(); nPos--; )
                xNewKey->createKey( pArray[nPos] );
            bRet = sal_True;
        }
        catch( com::sun::star::registry::InvalidRegistryException& )
        {
            OSL_ENSURE( sal_False, "### InvalidRegistryException!" );
        }
    }

    return bRet;
}

// ------------------------
// - component_getFactory -
// ------------------------

extern "C" void* SAL_CALL component_getFactory( const sal_Char* pImplName, void* pServiceManager, void* pRegistryKey )
{
    REF( NMSP_LANG::XSingleServiceFactory ) xFactory;
    void*									pRet = 0;
    
    if( rtl_str_compare( pImplName, "com.sun.star.util.FilterTracer" ) == 0 )
    {
        const rtl::OUString aServiceName( B2UCONST( "com.sun.star.util.FilterTracer" ) );

        xFactory = REF( NMSP_LANG::XSingleServiceFactory )( cppu::createSingleFactory(
            reinterpret_cast< NMSP_LANG::XMultiServiceFactory* >( pServiceManager ),
                B2UCONST( "com.sun.star.util.FilterTracer" ),
                        create_FilterTracer, SEQ( rtl::OUString )( &aServiceName, 1 ) ) );
    }
    if( xFactory.is() )
    {
        xFactory->acquire();
        pRet = xFactory.get();
    }
    
    return pRet;
}
