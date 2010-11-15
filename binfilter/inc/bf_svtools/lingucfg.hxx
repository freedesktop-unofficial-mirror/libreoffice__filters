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

#ifndef _SVTOOLS_LINGUCFG_HXX_
#define _SVTOOLS_LINGUCFG_HXX_

#ifndef _COM_SUN_STAR_BEANS_PROPERTYVALUES_HPP_
#include <com/sun/star/beans/PropertyValues.hpp>
#endif
#ifndef _COM_SUN_STAR_UNO_SEQUENCE_HXX_
#include <com/sun/star/uno/Sequence.hxx>
#endif
#ifndef _COM_SUN_STAR_UNO_ANY_H_
#include <com/sun/star/uno/Any.h>
#endif

#ifndef _SOLAR_H
#include <tools/solar.h>
#endif
#ifndef _RTL_USTRING_HXX_
#include <rtl/ustring.hxx>
#endif
#ifndef _UTL_CONFIGITEM_HXX_
#include <unotools/configitem.hxx>
#endif
#ifndef _OSL_MUTEX_HXX_ 
#include <osl/mutex.hxx>
#endif
#ifndef INCLUDED_SVTOOLS_OPTIONS_HXX
#include <bf_svtools/options.hxx>
#endif

namespace binfilter
{

class SvtLinguConfigItem;

//////////////////////////////////////////////////////////////////////

struct  SvtLinguOptions
{
    ::com::sun::star::uno::Sequence< rtl::OUString >	aActiveDics;
    ::com::sun::star::uno::Sequence< rtl::OUString >    aActiveConvDics;

    BOOL                                                bROActiveDics;
    BOOL                                                bROActiveConvDics;

    // Hyphenator service specific options
    INT16	nHyphMinLeading,
            nHyphMinTrailing,
            nHyphMinWordLength;

    BOOL    bROHyphMinLeading,
            bROHyphMinTrailing,
            bROHyphMinWordLength;

    // misc options (non-service specific)
    INT16	nDefaultLanguage;
    INT16	nDefaultLanguage_CJK;
    INT16	nDefaultLanguage_CTL;

    BOOL    bRODefaultLanguage;
    BOOL    bRODefaultLanguage_CJK;
    BOOL    bRODefaultLanguage_CTL;

    // spelling options (non-service specific)
    BOOL	bIsSpellSpecial;
    BOOL	bIsSpellAuto;
    BOOL	bIsSpellReverse;

    BOOL    bROIsSpellSpecial;
    BOOL    bROIsSpellAuto;
    BOOL    bROIsSpellReverse;

    // hyphenation options (non-service specific)
    BOOL	bIsHyphSpecial;
    BOOL	bIsHyphAuto;

    BOOL    bROIsHyphSpecial;
    BOOL    bROIsHyphAuto;

    // common to SpellChecker, Hyphenator and Thesaurus service
    BOOL	bIsUseDictionaryList;
    BOOL	bIsIgnoreControlCharacters;

    BOOL    bROIsUseDictionaryList;
    BOOL    bROIsIgnoreControlCharacters;

    // SpellChecker service specific options
    BOOL	bIsSpellWithDigits,
            bIsSpellUpperCase,
            bIsSpellCapitalization;

    BOOL    bROIsSpellWithDigits,
            bROIsSpellUpperCase,
            bROIsSpellCapitalization;

    // text conversion specific options
    BOOL    bIsIgnorePostPositionalWord;
    BOOL    bIsAutoCloseDialog;
    BOOL    bIsShowEntriesRecentlyUsedFirst;
    BOOL    bIsAutoReplaceUniqueEntries;
    BOOL    bIsDirectionToSimplified;
    BOOL    bIsUseCharacterVariants;
    BOOL    bIsTranslateCommonTerms;
    BOOL    bIsReverseMapping;

    BOOL    bROIsIgnorePostPositionalWord;
    BOOL    bROIsAutoCloseDialog;
    BOOL    bROIsShowEntriesRecentlyUsedFirst;
    BOOL    bROIsAutoReplaceUniqueEntries;
    BOOL    bROIsDirectionToSimplified;
    BOOL    bROIsUseCharacterVariants;
    BOOL    bROIsTranslateCommonTerms;
    BOOL    bROIsReverseMapping;

    // check value need to determine if the configuration needs to updatet
    // or not (used for a quick check if data files have been changed/added
    // or deleted
    INT32   nDataFilesChangedCheckValue;
    BOOL    bRODataFilesChangedCheckValue;

    SvtLinguOptions();
};

//////////////////////////////////////////////////////////////////////

class  SvtLinguConfig: public Options
{

    // disallow copy-constructor and assignment-operator for now
    SvtLinguConfig( const SvtLinguConfig & );
    SvtLinguConfig & operator = ( const SvtLinguConfig & );

    // returns static object
     SvtLinguConfigItem &   GetConfigItem();

    SvtLinguConfigItem &   GetConfigItem() const    { return const_cast< SvtLinguConfig * >( this )->GetConfigItem(); }

public:
    SvtLinguConfig();
    virtual ~SvtLinguConfig();

    //
    // borrowed from utl::ConfigItem
    //
    com::sun::star::uno::Sequence< rtl::OUString >
        GetNodeNames( const rtl::OUString &rNode );

    BOOL    GetOptions( SvtLinguOptions &rOptions ) const;
};

//////////////////////////////////////////////////////////////////////

}

#endif

