/*************************************************************************
 *
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER.
 * 
 * Copyright 2008 by Sun Microsystems, Inc.
 *
 * OpenOffice.org - a multi-platform office productivity suite
 *
 * $RCSfile: svt_itemholder2.cxx,v $
 * $Revision: 1.3 $
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

#include "itemholder2.hxx"

//-----------------------------------------------
// includes

#ifndef _COMPHELPER_PROCESSFACTORY_HXX_
#include <comphelper/processfactory.hxx>
#endif

#ifndef _COM_SUN_STAR_LANG_XCOMPONENT_HPP_
#include <com/sun/star/lang/XComponent.hpp>
#endif

#include <apearcfg.hxx>
#include <bf_svtools/cjkoptions.hxx>
#include <bf_svtools/colorcfg.hxx>
#include <bf_svtools/ctloptions.hxx>
#include <fontsubstconfig.hxx>
#include <bf_svtools/helpopt.hxx>
#include <bf_svtools/languageoptions.hxx>
#include <misccfg.hxx>
#include <bf_svtools/printoptions.hxx>
#include <bf_svtools/syslocaleoptions.hxx>
#include <bf_svtools/undoopt.hxx>
#include <bf_svtools/useroptions.hxx>
#include <bf_svtools/options.hxx>
#include <bf_svtools/miscopt.hxx>        


#include <tools/debug.hxx>

//-----------------------------------------------
// namespaces

namespace css = ::com::sun::star;

namespace binfilter
{

//-----------------------------------------------
// declarations

//-----------------------------------------------
ItemHolder2::ItemHolder2()
    : ItemHolderMutexBase()
{
    try
    {
        css::uno::Reference< css::lang::XMultiServiceFactory > xSMGR = ::comphelper::getProcessServiceFactory();
        css::uno::Reference< css::lang::XComponent > xCfg(
            xSMGR->createInstance(::rtl::OUString::createFromAscii("com.sun.star.configuration.ConfigurationProvider")),
            css::uno::UNO_QUERY);
        if (xCfg.is())
            xCfg->addEventListener(static_cast< css::lang::XEventListener* >(this));
    }
// #i37892  got errorhandling from   ConfigManager::GetConfigurationProvider()
    catch(css::uno::RuntimeException& rREx)
    {
        throw rREx;
    }
#ifdef DBG_UTIL
    catch(css::uno::Exception& rEx)
    {
        static sal_Bool bMessage = sal_True;
        if(bMessage)
        {
            bMessage = sal_False;
            ::rtl::OString sMsg("CreateInstance with arguments exception: ");
            sMsg += ::rtl::OString(rEx.Message.getStr(),
                        rEx.Message.getLength(),
                        RTL_TEXTENCODING_ASCII_US);
            DBG_ERROR(sMsg.getStr());
        }
    }
#else
    catch(css::uno::Exception&){}
#endif
}

//-----------------------------------------------
ItemHolder2::~ItemHolder2()
{
    impl_releaseAllItems();
}

//-----------------------------------------------
void ItemHolder2::holdConfigItem(EItem eItem)
{
    static ItemHolder2* pHolder = new ItemHolder2();
    pHolder->impl_addItem(eItem);
}
    
//-----------------------------------------------
void SAL_CALL ItemHolder2::disposing(const css::lang::EventObject&)
    throw(css::uno::RuntimeException)
{
    impl_releaseAllItems();
}

//-----------------------------------------------
void ItemHolder2::impl_addItem(EItem eItem)
{
    ::osl::ResettableMutexGuard aLock(m_aLock);

    TItems::const_iterator pIt;
    for (  pIt  = m_lItems.begin();
           pIt != m_lItems.end()  ;
         ++pIt                    )
    {
        const TItemInfo& rInfo = *pIt;
        if (rInfo.eItem == eItem)
            return;
    }
    
    TItemInfo aNewItem;
    aNewItem.eItem = eItem;
    impl_newItem(aNewItem);
    if (aNewItem.pItem)
        m_lItems.push_back(aNewItem);
}

//-----------------------------------------------
void ItemHolder2::impl_releaseAllItems()
{
    ::osl::ResettableMutexGuard aLock(m_aLock);
    
    TItems::iterator pIt;
    for (  pIt  = m_lItems.begin();
           pIt != m_lItems.end()  ;
         ++pIt                    )
    {
        TItemInfo& rInfo = *pIt;
        impl_deleteItem(rInfo);
    }
    m_lItems.clear();
}

//-----------------------------------------------
void ItemHolder2::impl_newItem(TItemInfo& rItem)
{
    switch(rItem.eItem)
    {
        case E_APEARCFG :
// no ref count            rItem.pItem = new SvtTabAppearanceCfg();
            break;
            
        case E_CJKOPTIONS :
            rItem.pItem = new SvtCJKOptions();
            break;
            
        case E_COLORCFG :
            rItem.pItem = new ColorConfig();
            break;
            
        case E_CTLOPTIONS :
            rItem.pItem = new SvtCTLOptions();
            break;
            
        case E_FONTSUBSTCONFIG :
// no ref count            rItem.pItem = new SvtFontSubstConfig();
            break;
            
        case E_HELPOPTIONS :
            rItem.pItem = new SvtHelpOptions();
            break;
        
        case E_LANGUAGEOPTIONS :
// capsulate CTL and CJL options !            rItem.pItem = new SvtLanguageOptions();
            break;
        
        case E_MISCCFG :
// no ref count            rItem.pItem = new SfxMiscCfg();
            break;
        
        case E_PRINTOPTIONS :
            rItem.pItem = new SvtPrinterOptions();
            break;
        
        case E_PRINTFILEOPTIONS :
            rItem.pItem = new SvtPrintFileOptions();
            break;
        
        case E_SYSLOCALEOPTIONS :
            rItem.pItem = new SvtSysLocaleOptions();
            break;
            
        case E_UNDOOPTIONS :
            rItem.pItem = new SvtUndoOptions();
            break;
            
        case E_USEROPTIONS :
            rItem.pItem = new SvtUserOptions();
            break;
        case E_MISCOPTIONS :
            rItem.pItem = new SvtMiscOptions();
            break;

        default:
            OSL_ASSERT(false);
            break;
    }
}

//-----------------------------------------------
void ItemHolder2::impl_deleteItem(TItemInfo& rItem)
{
    if (rItem.pItem)
    {
        delete rItem.pItem;
        rItem.pItem = 0;
    }
}
}
