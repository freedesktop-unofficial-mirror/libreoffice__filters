/*************************************************************************
 *
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER.
 * 
 * Copyright 2008 by Sun Microsystems, Inc.
 *
 * OpenOffice.org - a multi-platform office productivity suite
 *
 * $RCSfile: genericfilter.cxx,v $
 * $Revision: 1.6 $
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

// MARKER(update_precomp.py): autogen include statement, do not remove
#include "precompiled_filter.hxx"

#include <stdio.h>



#include <osl/mutex.hxx>

#include <osl/thread.h>

#include <cppuhelper/factory.hxx>



#ifndef _COM_SUN_STAR_LANG_XSINGLESERVICEFACTORY_HPP_

#include <com/sun/star/lang/XSingleServiceFactory.hpp>

#endif



#include "XmlFilterAdaptor.hxx"



using namespace ::rtl;

using namespace ::cppu;

using namespace ::com::sun::star::uno;

using namespace ::com::sun::star::lang;

using namespace ::com::sun::star::registry;



extern "C"

{

//==================================================================================================

void SAL_CALL component_getImplementationEnvironment(

    const sal_Char ** ppEnvTypeName, uno_Environment ** /* ppEnv */ )

{

    *ppEnvTypeName = CPPU_CURRENT_LANGUAGE_BINDING_NAME;

}

//==================================================================================================

sal_Bool SAL_CALL component_writeInfo(

    void * /* pServiceManager */, void * pRegistryKey )

{

    if (pRegistryKey)

    {

        try

        {

            Reference< XRegistryKey > xNewKey(

                reinterpret_cast< XRegistryKey * >( pRegistryKey )->createKey( XmlFilterAdaptor_getImplementationName() ) ); 

            xNewKey = xNewKey->createKey( OUString::createFromAscii( "/UNO/SERVICES" ) );

            

            const Sequence< OUString > & rSNL = XmlFilterAdaptor_getSupportedServiceNames();

            const OUString * pArray = rSNL.getConstArray();

            for ( sal_Int32 nPos = rSNL.getLength(); nPos--; )

                xNewKey->createKey( pArray[nPos] );



            return sal_True;

        }

        catch (InvalidRegistryException &)

        {

            OSL_ENSURE( sal_False, "### InvalidRegistryException!" );

        }

    }

    return sal_False;

}

//==================================================================================================

void * SAL_CALL component_getFactory(

    const sal_Char * pImplName, void * pServiceManager, void * /* pRegistryKey */ )

{

    void * pRet = 0;

    

    OUString implName = OUString::createFromAscii( pImplName );

    if ( pServiceManager && implName.equals(XmlFilterAdaptor_getImplementationName()) )

    {

        Reference< XSingleServiceFactory > xFactory( createSingleFactory(

            reinterpret_cast< XMultiServiceFactory * >( pServiceManager ),

            OUString::createFromAscii( pImplName ),

            XmlFilterAdaptor_createInstance, XmlFilterAdaptor_getSupportedServiceNames() ) );

        

        if (xFactory.is())

        {

            xFactory->acquire();

            pRet = xFactory.get();

        }

    }

    return pRet;

}

}

