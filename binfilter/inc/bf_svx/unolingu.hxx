/*************************************************************************
 *
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER.
 * 
 * Copyright 2008 by Sun Microsystems, Inc.
 *
 * OpenOffice.org - a multi-platform office productivity suite
 *
 * $RCSfile: unolingu.hxx,v $
 * $Revision: 1.9 $
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

#ifndef _UNO_LINGU_HXX
#define _UNO_LINGU_HXX

#ifndef INCLUDED_I18NPOOL_LANG_H
#include <i18npool/lang.h>
#endif
#ifndef _STRING_HXX
#include <tools/string.hxx>
#endif

#ifndef _COM_SUN_STAR_LINGUISTIC2_XLINGUSERVICEMANAGER_HPP_
#include <com/sun/star/linguistic2/XLinguServiceManager.hpp>
#endif
#ifndef _COM_SUN_STAR_LINGUISTIC2_XSPELLCHECKER1_HPP_
#include <com/sun/star/linguistic2/XSpellChecker1.hpp>
#endif
#ifndef _COM_SUN_STAR_LINGUISTIC2_XDICTIONARYLIST_HPP_
#include <com/sun/star/linguistic2/XDictionaryList.hpp>
#endif
#ifndef _COM_SUN_STAR_BEANS_XPROPERTYSET_HPP_
#include <com/sun/star/beans/XPropertySet.hpp>
#endif
#ifndef _COM_SUN_STAR_LINGUISTIC2_XDICTIONARY1_HPP_
#include <com/sun/star/linguistic2/XDictionary1.hpp>
#endif
class Window;
namespace binfilter {

class LinguMgrExitLstnr;


// SvxAddEntryToDic return values
#define DIC_ERR_NONE		0
#define DIC_ERR_FULL		1
#define DIC_ERR_READONLY	2
#define DIC_ERR_UNKNOWN		3
#define DIC_ERR_NOT_EXISTS	4
//#define DIC_ERR_ENTRY_EXISTS	5
//#define DIC_ERR_ENTRY_NOTEXISTS	6

///////////////////////////////////////////////////////////////////////////
// SvxLinguConfigUpdate
// class to update configuration items when (before!) the linguistic is used.
//
// This class is called by all the dummy implementations to update all of the
// configuration (list of used/available services) when the linguistic is
// accessed for the first time.

class SvxLinguConfigUpdate
{
    static BOOL bUpdated;

public:

    static BOOL IsUpdated()	{ return bUpdated; }
    static void UpdateAll();
};

///////////////////////////////////////////////////////////////////////////

class LinguMgr
{
    friend class LinguMgrExitLstnr;

    //static ::VOS::ORefCount aRefCount;

    static ::com::sun::star::uno::Reference<
        ::com::sun::star::linguistic2::XLinguServiceManager > xLngSvcMgr;
    static ::com::sun::star::uno::Reference<
        ::com::sun::star::linguistic2::XSpellChecker1 > xSpell;
    static ::com::sun::star::uno::Reference<
        ::com::sun::star::linguistic2::XHyphenator >	xHyph;
    static ::com::sun::star::uno::Reference<
        ::com::sun::star::linguistic2::XThesaurus >		xThes;
    static ::com::sun::star::uno::Reference<
        ::com::sun::star::linguistic2::XDictionaryList > xDicList;
    static ::com::sun::star::uno::Reference<
        ::com::sun::star::beans::XPropertySet > 		xProp;

    static ::com::sun::star::uno::Reference<
        ::com::sun::star::linguistic2::XDictionary1 >	xIgnoreAll;
    static ::com::sun::star::uno::Reference<
        ::com::sun::star::linguistic2::XDictionary1 >	xChangeAll;

    static LinguMgrExitLstnr						   *pExitLstnr;
    static sal_Bool										bExiting;

    static ::com::sun::star::uno::Reference<
        ::com::sun::star::linguistic2::XHyphenator > 	GetHyph();
    static ::com::sun::star::uno::Reference<
        ::com::sun::star::linguistic2::XDictionaryList > GetDicList();

    // disallow access to copy-constructor and assignment-operator
    LinguMgr(const LinguMgr &);
    LinguMgr & operator = (const LinguMgr &);

public:

    static ::com::sun::star::uno::Reference<
        ::com::sun::star::linguistic2::XHyphenator > 	GetHyphenator();
    static ::com::sun::star::uno::Reference<
        ::com::sun::star::linguistic2::XDictionaryList > GetDictionaryList();
    static ::com::sun::star::uno::Reference<
        ::com::sun::star::beans::XPropertySet > 		GetLinguPropertySet();


    // update all configuration entries
    static void UpdateAll();
};

///////////////////////////////////////////////////////////////////////////
}//end of namespace binfilter
namespace com { namespace sun { namespace star { namespace linguistic2 {
    class XHyphenatedWord;
}}}}
namespace binfilter {
struct SvxAlternativeSpelling
{
    String		aReplacement;
    ::com::sun::star::uno::Reference< 
        ::com::sun::star::linguistic2::XHyphenatedWord >	xHyphWord;
    INT16  		nChangedPos,
                 nChangedLength;
    BOOL		bIsAltSpelling;

    inline SvxAlternativeSpelling();
};

inline SvxAlternativeSpelling::SvxAlternativeSpelling() :
    nChangedPos(-1), nChangedLength(-1), bIsAltSpelling(FALSE)
{
}


///////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////

//TL:TODO: remove those functions or make them inline
//TL:TODO: remove argument or provide SvxGetIgnoreAllList with the same one

///////////////////////////////////////////////////////////////////////////
// misc functions
//

LanguageType 						SvxLocaleToLanguage( 
        const ::com::sun::star::lang::Locale& rLocale );
::com::sun::star::lang::Locale& 	SvxLanguageToLocale( 
        ::com::sun::star::lang::Locale& rLocale, LanguageType eLang );
::com::sun::star::lang::Locale		SvxCreateLocale( LanguageType eLang );


//TL:TODO: soll mal den rictigen R�ckgabetyp bekommen!


}//end of namespace binfilter
#endif

