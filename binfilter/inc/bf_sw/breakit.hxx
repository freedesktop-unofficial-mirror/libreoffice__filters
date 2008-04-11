/*************************************************************************
 *
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER.
 * 
 * Copyright 2008 by Sun Microsystems, Inc.
 *
 * OpenOffice.org - a multi-platform office productivity suite
 *
 * $RCSfile: breakit.hxx,v $
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

#ifndef _BREAKIT_HXX
#define _BREAKIT_HXX

#ifndef _SOLAR_H
#include <tools/solar.h>
#endif
#ifndef INCLUDED_I18NPOOL_LANG_H
#include <i18npool/lang.h>
#endif

/*************************************************************************
 *						class SwBreakIt
 *************************************************************************/

#ifndef _COM_SUN_STAR_UNO_REFERENCE_H_
#include <com/sun/star/uno/Reference.h>
#endif

#ifndef _COM_SUN_STAR_I18N_XBREAKITERATOR_HPP_
#include <com/sun/star/i18n/XBreakIterator.hpp>
#endif

#ifndef _COM_SUN_STAR_I18N_FORBIDDENCHARACTERS_HDL_
#include <com/sun/star/i18n/ForbiddenCharacters.hdl>
#endif
class String; 
namespace binfilter {



class SwBreakIt
{
public:
    ::com::sun::star::uno::Reference < ::com::sun::star::i18n::XBreakIterator > xBreak;
private:
    ::com::sun::star::lang::Locale* pLocale;
    ::com::sun::star::i18n::ForbiddenCharacters* pForbidden;
    LanguageType aLast;          // language of the current locale
    LanguageType aForbiddenLang; // language of the current forbiddenChar struct

    void _GetLocale( const LanguageType aLang );
    void _GetForbidden( const LanguageType	aLang );
public:
    SwBreakIt();
    ~SwBreakIt() { delete pLocale; delete pForbidden; }
    ::com::sun::star::lang::Locale& GetLocale( const LanguageType aLang )
    {
        if( aLast != aLang )
            _GetLocale( aLang );
        return *pLocale;
    }
    ::com::sun::star::i18n::ForbiddenCharacters& GetForbidden( const LanguageType aLang )
    {
        if( !pForbidden || aForbiddenLang != aLang )
            _GetForbidden( aLang );
        return *pForbidden;
    }

    USHORT GetRealScriptOfText( const String& rTxt, xub_StrLen nPos ) const;
};

extern SwBreakIt* pBreakIt;


} //namespace binfilter
#endif

