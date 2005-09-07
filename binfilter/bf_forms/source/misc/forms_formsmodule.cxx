/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: forms_formsmodule.cxx,v $
 *
 *  $Revision: 1.3 $
 *
 *  last change: $Author: rt $ $Date: 2005-09-07 15:54:39 $
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

#ifndef FORMS_MODULE_HXX
#include "formsmodule.hxx"
#endif

#ifndef _COMPHELPER_SEQUENCE_HXX_
#include <comphelper/sequence.hxx>
#endif
namespace binfilter {

//.........................................................................
namespace frm
{
//.........................................................................

    using namespace ::com::sun::star::uno;
    using namespace ::com::sun::star::lang;
    using namespace ::com::sun::star::registry;
    using namespace ::comphelper;
    using namespace ::cppu;

    //=========================================================================
    //= OFormsModule
    //=========================================================================

    //--------------------------------------------------------------------------
    //- registration helper
    //--------------------------------------------------------------------------

    Sequence< ::rtl::OUString >*				OFormsModule::s_pImplementationNames = NULL;
    Sequence< Sequence< ::rtl::OUString > >*	OFormsModule::s_pSupportedServices = NULL;
    Sequence< sal_Int64 >*						OFormsModule::s_pCreationFunctionPointers = NULL;
    Sequence< sal_Int64 >*						OFormsModule::s_pFactoryFunctionPointers = NULL;

    //--------------------------------------------------------------------------
    void OFormsModule::registerComponent(
        const ::rtl::OUString& _rImplementationName,
        const Sequence< ::rtl::OUString >& _rServiceNames,
        ComponentInstantiation _pCreateFunction,
        FactoryInstantiation _pFactoryFunction)
    {
        if (!s_pImplementationNames)
        {
            OSL_ENSURE(!s_pSupportedServices && !s_pCreationFunctionPointers && !s_pFactoryFunctionPointers,
                "OFormsModule::registerComponent : inconsistent state (the pointers (1)) !");
            s_pImplementationNames = new Sequence< ::rtl::OUString >;
            s_pSupportedServices = new Sequence< Sequence< ::rtl::OUString > >;
            s_pCreationFunctionPointers = new Sequence< sal_Int64 >;
            s_pFactoryFunctionPointers = new Sequence< sal_Int64 >;
        }
        OSL_ENSURE(s_pImplementationNames && s_pSupportedServices && s_pCreationFunctionPointers && s_pFactoryFunctionPointers,
            "OFormsModule::registerComponent : inconsistent state (the pointers (2)) !");

        OSL_ENSURE(	(s_pImplementationNames->getLength() == s_pSupportedServices->getLength())
                    &&	(s_pImplementationNames->getLength() == s_pCreationFunctionPointers->getLength())
                    &&	(s_pImplementationNames->getLength() == s_pFactoryFunctionPointers->getLength()),
            "OFormsModule::registerComponent : inconsistent state !");

        sal_Int32 nOldLen = s_pImplementationNames->getLength();
        s_pImplementationNames->realloc(nOldLen + 1);
        s_pSupportedServices->realloc(nOldLen + 1);
        s_pCreationFunctionPointers->realloc(nOldLen + 1);
        s_pFactoryFunctionPointers->realloc(nOldLen + 1);

        s_pImplementationNames->getArray()[nOldLen] = _rImplementationName;
        s_pSupportedServices->getArray()[nOldLen] = _rServiceNames;
        s_pCreationFunctionPointers->getArray()[nOldLen] = reinterpret_cast<sal_Int64>(_pCreateFunction);
        s_pFactoryFunctionPointers->getArray()[nOldLen] = reinterpret_cast<sal_Int64>(_pFactoryFunction);
    }

    //--------------------------------------------------------------------------
    void OFormsModule::revokeComponent(const ::rtl::OUString& _rImplementationName)
    {
        if (!s_pImplementationNames)
        {
            OSL_ASSERT("OFormsModule::revokeComponent : have no class infos ! Are you sure called this method at the right time ?");
            return;
        }
        OSL_ENSURE(s_pImplementationNames && s_pSupportedServices && s_pCreationFunctionPointers && s_pFactoryFunctionPointers,
            "OFormsModule::revokeComponent : inconsistent state (the pointers) !");
        OSL_ENSURE(	(s_pImplementationNames->getLength() == s_pSupportedServices->getLength())
                    &&	(s_pImplementationNames->getLength() == s_pCreationFunctionPointers->getLength())
                    &&	(s_pImplementationNames->getLength() == s_pFactoryFunctionPointers->getLength()),
            "OFormsModule::revokeComponent : inconsistent state !");

        sal_Int32 nLen = s_pImplementationNames->getLength();
        const ::rtl::OUString* pImplNames = s_pImplementationNames->getConstArray();
        for (sal_Int32 i=0; i<nLen; ++i, ++pImplNames)
        {
            if (pImplNames->equals(_rImplementationName))
            {
                removeElementAt(*s_pImplementationNames, i);
                removeElementAt(*s_pSupportedServices, i);
                removeElementAt(*s_pCreationFunctionPointers, i);
                removeElementAt(*s_pFactoryFunctionPointers, i);
                break;
            }
        }

        if (s_pImplementationNames->getLength() == 0)
        {
            delete s_pImplementationNames; s_pImplementationNames = NULL;
            delete s_pSupportedServices; s_pSupportedServices = NULL;
            delete s_pCreationFunctionPointers; s_pCreationFunctionPointers = NULL;
            delete s_pFactoryFunctionPointers; s_pFactoryFunctionPointers = NULL;
        }
    }

    //--------------------------------------------------------------------------
    sal_Bool OFormsModule::writeComponentInfos(
            const Reference< XMultiServiceFactory >& /*_rxServiceManager*/,
            const Reference< XRegistryKey >& _rxRootKey)
    {
        OSL_ENSURE(_rxRootKey.is(), "OFormsModule::writeComponentInfos : invalid argument !");

        if (!s_pImplementationNames)
        {
            OSL_ASSERT("OFormsModule::writeComponentInfos : have no class infos ! Are you sure called this method at the right time ?");
            return sal_True;
        }
        OSL_ENSURE(s_pImplementationNames && s_pSupportedServices && s_pCreationFunctionPointers && s_pFactoryFunctionPointers,
            "OFormsModule::writeComponentInfos : inconsistent state (the pointers) !");
        OSL_ENSURE(	(s_pImplementationNames->getLength() == s_pSupportedServices->getLength())
                    &&	(s_pImplementationNames->getLength() == s_pCreationFunctionPointers->getLength())
                    &&	(s_pImplementationNames->getLength() == s_pFactoryFunctionPointers->getLength()),
            "OFormsModule::writeComponentInfos : inconsistent state !");

        sal_Int32 nLen = s_pImplementationNames->getLength();
        const ::rtl::OUString* pImplName = s_pImplementationNames->getConstArray();
        const Sequence< ::rtl::OUString >* pServices = s_pSupportedServices->getConstArray();

        ::rtl::OUString sRootKey("/", 1, RTL_TEXTENCODING_ASCII_US);
        for (sal_Int32 i=0; i<nLen; ++i, ++pImplName, ++pServices)
        {
            ::rtl::OUString aMainKeyName(sRootKey);
            aMainKeyName += *pImplName;
            aMainKeyName += ::rtl::OUString::createFromAscii("/UNO/SERVICES");

            try
            {
                Reference< XRegistryKey >  xNewKey( _rxRootKey->createKey(aMainKeyName) );

                const ::rtl::OUString* pService = pServices->getConstArray();
                for (sal_Int32 j=0; j<pServices->getLength(); ++j, ++pService)
                    xNewKey->createKey(*pService);
            }
            catch(Exception&)
            {
                OSL_ASSERT("OFormsModule::writeComponentInfos : something went wrong while creating the keys !");
                return sal_False;
            }
        }

        return sal_True;
    }

    //--------------------------------------------------------------------------
    Reference< XInterface > OFormsModule::getComponentFactory(
        const ::rtl::OUString& _rImplementationName,
        const Reference< XMultiServiceFactory >& _rxServiceManager)
    {
        OSL_ENSURE(_rxServiceManager.is(), "OFormsModule::getComponentFactory : invalid argument (service manager) !");
        OSL_ENSURE(_rImplementationName.getLength(), "OFormsModule::getComponentFactory : invalid argument (implementation name) !");

        if (!s_pImplementationNames)
        {
            OSL_ASSERT("OFormsModule::getComponentFactory : have no class infos ! Are you sure called this method at the right time ?");
            return NULL;
        }
        OSL_ENSURE(s_pImplementationNames && s_pSupportedServices && s_pCreationFunctionPointers && s_pFactoryFunctionPointers,
            "OFormsModule::getComponentFactory : inconsistent state (the pointers) !");
        OSL_ENSURE(	(s_pImplementationNames->getLength() == s_pSupportedServices->getLength())
                    &&	(s_pImplementationNames->getLength() == s_pCreationFunctionPointers->getLength())
                    &&	(s_pImplementationNames->getLength() == s_pFactoryFunctionPointers->getLength()),
            "OFormsModule::getComponentFactory : inconsistent state !");


        Reference< XInterface > xReturn;


        sal_Int32 nLen = s_pImplementationNames->getLength();
        const ::rtl::OUString* pImplName = s_pImplementationNames->getConstArray();
        const Sequence< ::rtl::OUString >* pServices = s_pSupportedServices->getConstArray();
        const sal_Int64* pComponentFunction = s_pCreationFunctionPointers->getConstArray();
        const sal_Int64* pFactoryFunction = s_pFactoryFunctionPointers->getConstArray();

        for (sal_Int32 i=0; i<nLen; ++i, ++pImplName, ++pServices, ++pComponentFunction, ++pFactoryFunction)
        {
            if (pImplName->equals(_rImplementationName))
            {
                const FactoryInstantiation FactoryInstantiationFunction = reinterpret_cast<const FactoryInstantiation>(*pFactoryFunction);
                const ComponentInstantiation ComponentInstantiationFunction = reinterpret_cast<const ComponentInstantiation>(*pComponentFunction);

                xReturn = FactoryInstantiationFunction( _rxServiceManager, *pImplName, ComponentInstantiationFunction, *pServices, NULL);
                if (xReturn.is())
                {
                    xReturn->acquire();
                    return xReturn.get();
                }
            }
        }

        return NULL;
    }


//.........................................................................
}	// namespace frm
//.........................................................................

}
