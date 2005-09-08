/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: svx_UnoForbiddenCharsTable.cxx,v $
 *
 *  $Revision: 1.3 $
 *
 *  last change: $Author: rt $ $Date: 2005-09-08 07:31:18 $
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

#ifndef _SVX_UNOFORBIDDENCHARSTABLE_HXX_
#include "UnoForbiddenCharsTable.hxx"
#endif

#ifndef _FORBIDDENCHARACTERSTABLE_HXX
#include "forbiddencharacterstable.hxx"
#endif

#ifndef _VOS_MUTEX_HXX_ 
#include <vos/mutex.hxx>
#endif
#ifndef _SV_SVAPP_HXX 
#include <vcl/svapp.hxx>
#endif

#ifndef _UNO_LINGU_HXX
#include "unolingu.hxx"
#endif
namespace binfilter {

using namespace ::com::sun::star;
using namespace ::com::sun::star::uno;
using namespace ::com::sun::star::container;
using namespace ::com::sun::star::lang;
using namespace ::com::sun::star::i18n;
using namespace ::rtl;
using namespace ::vos;
using namespace ::cppu;

SvxUnoForbiddenCharsTable::SvxUnoForbiddenCharsTable(ORef<SvxForbiddenCharactersTable> xForbiddenChars) :
    mxForbiddenChars( xForbiddenChars )
{
}

SvxUnoForbiddenCharsTable::~SvxUnoForbiddenCharsTable()
{
}

void SvxUnoForbiddenCharsTable::onChange()
{
}

ForbiddenCharacters SvxUnoForbiddenCharsTable::getForbiddenCharacters( const Locale& rLocale )
    throw(NoSuchElementException, RuntimeException)
{
    OGuard aGuard( Application::GetSolarMutex() );

    if(!mxForbiddenChars.isValid())
        throw RuntimeException();

    const LanguageType eLang = SvxLocaleToLanguage( rLocale );
    const ForbiddenCharacters* pForbidden = mxForbiddenChars->GetForbiddenCharacters( eLang, FALSE );
    if(!pForbidden)
        throw NoSuchElementException();

    return *pForbidden;
}

sal_Bool SvxUnoForbiddenCharsTable::hasForbiddenCharacters( const Locale& rLocale )
    throw(RuntimeException)
{
    OGuard aGuard( Application::GetSolarMutex() );

    if(!mxForbiddenChars.isValid())
        return sal_False;

    const LanguageType eLang = SvxLocaleToLanguage( rLocale );
    const ForbiddenCharacters* pForbidden = mxForbiddenChars->GetForbiddenCharacters( eLang, FALSE );

    return NULL != pForbidden;
}

void SvxUnoForbiddenCharsTable::setForbiddenCharacters(const Locale& rLocale, const ForbiddenCharacters& rForbiddenCharacters )
    throw(RuntimeException)
{
    OGuard aGuard( Application::GetSolarMutex() );

    if(!mxForbiddenChars.isValid())
        throw RuntimeException();

    const LanguageType eLang = SvxLocaleToLanguage( rLocale );
    mxForbiddenChars->SetForbiddenCharacters( eLang, rForbiddenCharacters );

    onChange();
}

void SvxUnoForbiddenCharsTable::removeForbiddenCharacters( const Locale& rLocale )
    throw(RuntimeException)
{
    OGuard aGuard( Application::GetSolarMutex() );

    if(!mxForbiddenChars.isValid())
        throw RuntimeException();

    const LanguageType eLang = SvxLocaleToLanguage( rLocale );
    mxForbiddenChars->ClearForbiddenCharacters( eLang );

    onChange();
}

// XSupportedLocales
Sequence< Locale > SAL_CALL SvxUnoForbiddenCharsTable::getLocales()
    throw(RuntimeException)
{
    OGuard aGuard( Application::GetSolarMutex() );

    const sal_Int32 nCount = mxForbiddenChars.isValid() ? mxForbiddenChars->Count() : 0;

    Sequence< Locale > aLocales( nCount );
    if( nCount )
    {
        Locale* pLocales = aLocales.getArray();

        for( sal_Int32 nIndex = 0; nIndex < nCount; nIndex++ )
        {
            const ULONG nLanguage = mxForbiddenChars->GetObjectKey( nIndex );
            SvxLanguageToLocale ( *pLocales++, static_cast < LanguageType > (nLanguage) );
        }
    }

    return aLocales;
}

sal_Bool SAL_CALL SvxUnoForbiddenCharsTable::hasLocale( const Locale& aLocale )
    throw(RuntimeException)
{
    OGuard aGuard( Application::GetSolarMutex() );

    return hasForbiddenCharacters( aLocale );
}
}
