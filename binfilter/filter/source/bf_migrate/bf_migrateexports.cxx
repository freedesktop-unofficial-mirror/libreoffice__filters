/*************************************************************************
 *
 *  $RCSfile: bf_migrateexports.cxx,v $
 *
 *  $Revision: 1.2 $
 *
 *  last change: $Author: mwu $ $Date: 2003-11-06 07:59:00 $
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
#include <stdio.h>

#include <osl/mutex.hxx>
#include <osl/thread.h>
#include <cppuhelper/factory.hxx>

#ifndef _COM_SUN_STAR_LANG_XSINGLESERVICEFACTORY_HPP_
#include <com/sun/star/lang/XSingleServiceFactory.hpp>
#endif

#ifndef _LEGACYBINFILTERMGR_HXX
#include <legacysmgr/legacy_binfilters_smgr.hxx>
#endif

#ifndef _BF_MIGRATEFILTER_HXX
#include <bf_migratefilter.hxx>
#endif
namespace binfilter {

using namespace ::rtl;
using namespace ::cppu;
using namespace ::com::sun::star::uno;
using namespace ::com::sun::star::lang;
using namespace ::com::sun::star::registry;

extern "C"
{

//==================================================================================================
void SAL_CALL component_getImplementationEnvironment(const sal_Char** ppEnvTypeName, uno_Environment** ppEnv)
{
    *ppEnvTypeName = CPPU_CURRENT_LANGUAGE_BINDING_NAME;
}

//==================================================================================================
sal_Bool SAL_CALL component_writeInfo(void* pServiceManager, void* pRegistryKey)
{
    if(pRegistryKey)
    {
        try
        {
            OSL_ENSURE(legacysmgr_component_writeInfo
                ( reinterpret_cast<XMultiServiceFactory*>( pServiceManager), reinterpret_cast<XRegistryKey*> (pRegistryKey) ), 
                "### LegacyServiceManager writeInfo failed!" );

            Reference< XRegistryKey > xNewKey;
            xNewKey = reinterpret_cast< XRegistryKey * >(pRegistryKey)->createKey(bf_MigrateFilter_getImplementationName()); 
            xNewKey = xNewKey->createKey(OUString::createFromAscii("/UNO/SERVICES"));
            
            const Sequence< OUString > & rSNL = bf_MigrateFilter_getSupportedServiceNames();
            const OUString * pArray = rSNL.getConstArray();
            
            for(sal_Int32 nPos(rSNL.getLength()); nPos--; )
                xNewKey->createKey(pArray[nPos]);

            return sal_True;
        }
        catch (InvalidRegistryException &)
        {
            OSL_ENSURE(sal_False, "### InvalidRegistryException!");
        }
    }

    return sal_False;
}

//==================================================================================================
void* SAL_CALL component_getFactory(const sal_Char* pImplName, void* pServiceManager, void* pRegistryKey)
{
    void* pRet = 0;
    
    OUString implName = OUString::createFromAscii(pImplName);

    if(pServiceManager && implName.equals(bf_MigrateFilter_getImplementationName()))
    {
        Reference< XSingleServiceFactory > xFactory(createSingleFactory(
            reinterpret_cast< XMultiServiceFactory * >(pServiceManager),
            OUString::createFromAscii(pImplName),
            bf_MigrateFilter_createInstance, bf_MigrateFilter_getSupportedServiceNames()));
        
        if(xFactory.is())
        {
            xFactory->acquire();
            pRet = xFactory.get();
        }

        // init LegacyServiceFactory
        legacysmgr_component_getFactory( 
            pImplName, 
            reinterpret_cast< XMultiServiceFactory *>(pServiceManager),
            reinterpret_cast<XRegistryKey*> (pRegistryKey) );
    }

    return pRet;
}
}

// eof
}
