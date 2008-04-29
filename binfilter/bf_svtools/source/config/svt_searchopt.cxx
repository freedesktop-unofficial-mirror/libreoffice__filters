/*************************************************************************
 *
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER.
 * 
 * Copyright 2008 by Sun Microsystems, Inc.
 *
 * OpenOffice.org - a multi-platform office productivity suite
 *
 * $RCSfile: svt_searchopt.cxx,v $
 * $Revision: 1.4 $
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


#include "searchopt.hxx"

#ifndef _SOLAR_H
#include <tools/solar.h>
#endif
#ifndef _TOOLS_DEBUG_HXX
#include <tools/debug.hxx>
#endif
#ifndef _UTL_CONFIGITEM_HXX_
#include <unotools/configitem.hxx>
#endif

#ifndef _COM_SUN_STAR_I18N_TRANSLITERATIONMODULES_HPP_
#include <com/sun/star/i18n/TransliterationModules.hpp>
#endif
#ifndef _COM_SUN_STAR_UNO_SEQUENCE_HXX_
#include <com/sun/star/uno/Sequence.hxx>
#endif
#ifndef _COM_SUN_STAR_UNO_ANY_H_
#include <com/sun/star/uno/Any.h>
#endif
#include <rtl/logfile.hxx>


using namespace rtl;
using namespace utl;
using namespace com::sun::star::uno;
using namespace com::sun::star::i18n;

namespace binfilter
{

#define MAX_FLAGS_OFFSET	24

//////////////////////////////////////////////////////////////////////


class SvtSearchOptions_Impl : public ConfigItem
{
    INT32	nFlags;
    BOOL	bModified;

    // disallow copy-constructor and assignment-operator for now
    SvtSearchOptions_Impl( const SvtSearchOptions_Impl & );
    SvtSearchOptions_Impl & operator = ( const SvtSearchOptions_Impl & );

protected:
    BOOL			IsModified() const { return bModified; }
    using ConfigItem::SetModified;
    void			SetModified( BOOL bVal );
    BOOL			Load();
    BOOL			Save();

    Sequence< OUString >	GetPropertyNames() const;

public:
    SvtSearchOptions_Impl();
    virtual ~SvtSearchOptions_Impl();

    // ConfigItem
    virtual void	Commit();

    BOOL			GetFlag( USHORT nOffset ) const;
    void			SetFlag( USHORT nOffset, BOOL bVal );
};



SvtSearchOptions_Impl::SvtSearchOptions_Impl() :
    ConfigItem( OUString::createFromAscii( "Office.Common/SearchOptions" ) )
{
    RTL_LOGFILE_CONTEXT(aLog, "svtools SvtSearchOptions_Impl::SvtSearchOptions_Impl()");
    nFlags = 0x0003FFFF;	// set all options values to 'true'
    Load();
    SetModified( FALSE );
}


SvtSearchOptions_Impl::~SvtSearchOptions_Impl()
{
    Commit();
}

    
void SvtSearchOptions_Impl::Commit()
{
    if (IsModified())
        Save();
}


BOOL SvtSearchOptions_Impl::GetFlag( USHORT nOffset ) const
{
    DBG_ASSERT( nOffset <= MAX_FLAGS_OFFSET, "offset out of range");
    return ((nFlags >> nOffset) & 0x01) ? TRUE : FALSE;
}


void SvtSearchOptions_Impl::SetFlag( USHORT nOffset, BOOL bVal )
{
    DBG_ASSERT( nOffset <= MAX_FLAGS_OFFSET, "offset out of range");
    INT32 nOldFlags = nFlags;
    INT32 nMask = ((INT32) 1)  << nOffset;
    if (bVal)
        nFlags |= nMask;
    else
        nFlags &= ~nMask;
    if (nFlags != nOldFlags)
        SetModified( TRUE );
}

    
void SvtSearchOptions_Impl::SetModified( BOOL bVal )
{
    bModified = bVal;
    if (bModified)
    {
        ConfigItem::SetModified();
    }
}


Sequence< OUString > SvtSearchOptions_Impl::GetPropertyNames() const
{
    static const char* aPropNames[ MAX_FLAGS_OFFSET + 1 ] =
    {
        "IsWholeWordsOnly",						//  0
        "IsBackwards",							//  1
        "IsUseRegularExpression",				//  2
        //"IsCurrentSelectionOnly",				// interactively set or not...
        "IsSearchForStyles",					//  3
        "IsSimilaritySearch",					//  4
        "IsUseAsianOptions",					//  5
        "IsMatchCase",							//  6
        "Japanese/IsMatchFullHalfWidthForms",	//  7
        "Japanese/IsMatchHiraganaKatakana",		//  8
        "Japanese/IsMatchContractions",			//  9
        "Japanese/IsMatchMinusDashCho-on",		// 10
        "Japanese/IsMatchRepeatCharMarks",		// 11
        "Japanese/IsMatchVariantFormKanji",		// 12
        "Japanese/IsMatchOldKanaForms",			// 13
        "Japanese/IsMatch_DiZi_DuZu",			// 14
        "Japanese/IsMatch_BaVa_HaFa",			// 15
        "Japanese/IsMatch_TsiThiChi_DhiZi",		// 16
        "Japanese/IsMatch_HyuIyu_ByuVyu",		// 17
        "Japanese/IsMatch_SeShe_ZeJe",			// 18
        "Japanese/IsMatch_IaIya",				// 19
        "Japanese/IsMatch_KiKu",				// 20
        "Japanese/IsIgnorePunctuation",			// 21
        "Japanese/IsIgnoreWhitespace",			// 22
        "Japanese/IsIgnoreProlongedSoundMark",	// 23
        "Japanese/IsIgnoreMiddleDot"			// 24
    };

    const int nCount = sizeof( aPropNames ) / sizeof( aPropNames[0] );
    Sequence< OUString > aNames( nCount );
    OUString* pNames = aNames.getArray();
    for (INT32 i = 0;  i < nCount;  ++i)
        pNames[i] = OUString::createFromAscii( aPropNames[i] );

    return aNames;
}


BOOL SvtSearchOptions_Impl::Load()
{
    BOOL bSucc = FALSE;
    
    Sequence< OUString > aNames = GetPropertyNames();
    INT32 nProps = aNames.getLength();
    
    const Sequence< Any > aValues = GetProperties( aNames );
    DBG_ASSERT( aValues.getLength() == aNames.getLength(), 
            "GetProperties failed" );
    //EnableNotification( aNames );
    
    if (nProps  &&  aValues.getLength() == nProps)
    {
        bSucc = TRUE;
        
        const Any* pValues = aValues.getConstArray();
        for (USHORT i = 0;  i < nProps;  ++i)
        {
            const Any &rVal = pValues[i];
            DBG_ASSERT( rVal.hasValue(), "property value missing" );
            if (rVal.hasValue())
            {
                BOOL bVal = BOOL();
                if (rVal >>= bVal)
                {
                    if (i <= MAX_FLAGS_OFFSET)
                    {
                        // use index in sequence as flag index
                        SetFlag( i, bVal );
                    }
                    else
                    {
                        DBG_ERROR( "unexpected index" );
                    }
                }
                else
                {
                    DBG_ERROR( "unexpected type" );
                    bSucc = FALSE;
                }
            }
            else
            {
                DBG_ERROR( "value missing" );
                bSucc = FALSE;
            }
        }
    }
    DBG_ASSERT( bSucc, "LoadConfig failed" );
    
    return bSucc;
}


BOOL SvtSearchOptions_Impl::Save()
{
    BOOL bSucc = FALSE;
    
    const Sequence< OUString > aNames = GetPropertyNames();
    INT32 nProps = aNames.getLength();
    
    Sequence< Any > aValues( nProps );
    Any *pValue = aValues.getArray();

    DBG_ASSERT( nProps == MAX_FLAGS_OFFSET + 1,
            "unexpected size of index" );
    if (nProps  &&  nProps == MAX_FLAGS_OFFSET + 1)
    {
        for (USHORT i = 0;  i < nProps;  ++i)
            pValue[i] <<= (BOOL) GetFlag(i);
        bSucc |= PutProperties( aNames, aValues );
    }

    if (bSucc)
        SetModified( FALSE );

    return bSucc;
}


//////////////////////////////////////////////////////////////////////

SvtSearchOptions::SvtSearchOptions()
{
    pImpl = new SvtSearchOptions_Impl;
}


SvtSearchOptions::~SvtSearchOptions()
{
    delete pImpl;
}


INT32 SvtSearchOptions::GetTransliterationFlags() const
{
    INT32 nRes = 0;
    
    if (!IsMatchCase()) // 'IsMatchCase' means act case sensitive
        nRes |= TransliterationModules_IGNORE_CASE;
    if ( IsMatchFullHalfWidthForms())
        nRes |= TransliterationModules_IGNORE_WIDTH;
    if ( IsMatchHiraganaKatakana())
        nRes |= TransliterationModules_IGNORE_KANA;
    if ( IsMatchContractions())
        nRes |= TransliterationModules_ignoreSize_ja_JP;
    if ( IsMatchMinusDashChoon())
        nRes |= TransliterationModules_ignoreMinusSign_ja_JP;
    if ( IsMatchRepeatCharMarks())
        nRes |= TransliterationModules_ignoreIterationMark_ja_JP;
    if ( IsMatchVariantFormKanji())
        nRes |= TransliterationModules_ignoreTraditionalKanji_ja_JP;
    if ( IsMatchOldKanaForms())
        nRes |= TransliterationModules_ignoreTraditionalKana_ja_JP;
    if ( IsMatchDiziDuzu())
        nRes |= TransliterationModules_ignoreZiZu_ja_JP;
    if ( IsMatchBavaHafa())
        nRes |= TransliterationModules_ignoreBaFa_ja_JP;
    if ( IsMatchTsithichiDhizi())
        nRes |= TransliterationModules_ignoreTiJi_ja_JP;
    if ( IsMatchHyuiyuByuvyu())
        nRes |= TransliterationModules_ignoreHyuByu_ja_JP;
    if ( IsMatchSesheZeje())
        nRes |= TransliterationModules_ignoreSeZe_ja_JP;
    if ( IsMatchIaiya())
        nRes |= TransliterationModules_ignoreIandEfollowedByYa_ja_JP;
    if ( IsMatchKiku())
        nRes |= TransliterationModules_ignoreKiKuFollowedBySa_ja_JP;
    if ( IsIgnorePunctuation())
        nRes |= TransliterationModules_ignoreSeparator_ja_JP;
    if ( IsIgnoreWhitespace())
        nRes |= TransliterationModules_ignoreSpace_ja_JP;
    if ( IsIgnoreProlongedSoundMark())
        nRes |= TransliterationModules_ignoreProlongedSoundMark_ja_JP;
    if ( IsIgnoreMiddleDot())
        nRes |= TransliterationModules_ignoreMiddleDot_ja_JP;
    
    return nRes;
}


BOOL SvtSearchOptions::IsWholeWordsOnly() const
{
    return pImpl->GetFlag( 0 );
}


void SvtSearchOptions::SetWholeWordsOnly( BOOL bVal )
{
    pImpl->SetFlag( 0, bVal );
}


BOOL SvtSearchOptions::IsBackwards() const
{
    return pImpl->GetFlag( 1 );
}


void SvtSearchOptions::SetBackwards( BOOL bVal )
{
    pImpl->SetFlag( 1, bVal );
}


BOOL SvtSearchOptions::IsUseRegularExpression() const
{
    return pImpl->GetFlag( 2 );
}


void SvtSearchOptions::SetUseRegularExpression( BOOL bVal )
{
    pImpl->SetFlag( 2, bVal );
}


BOOL SvtSearchOptions::IsSearchForStyles() const
{
    return pImpl->GetFlag( 3 );
}


void SvtSearchOptions::SetSearchForStyles( BOOL bVal )
{
    pImpl->SetFlag( 3, bVal );
}


BOOL SvtSearchOptions::IsSimilaritySearch() const
{
    return pImpl->GetFlag( 4 );
}


void SvtSearchOptions::SetSimilaritySearch( BOOL bVal )
{
    pImpl->SetFlag( 4, bVal );
}


BOOL SvtSearchOptions::IsUseAsianOptions() const
{
    return pImpl->GetFlag( 5 );
}


void SvtSearchOptions::SetUseAsianOptions( BOOL bVal )
{
    pImpl->SetFlag( 5, bVal );
}


BOOL SvtSearchOptions::IsMatchCase() const
{
    return pImpl->GetFlag( 6 );
}


void SvtSearchOptions::SetMatchCase( BOOL bVal )
{
    pImpl->SetFlag( 6, bVal );
}


BOOL SvtSearchOptions::IsMatchFullHalfWidthForms() const
{
    return pImpl->GetFlag( 7 );
}


void SvtSearchOptions::SetMatchFullHalfWidthForms( BOOL bVal )
{
    pImpl->SetFlag( 7, bVal );
}


BOOL SvtSearchOptions::IsMatchHiraganaKatakana() const
{
    return pImpl->GetFlag( 8 );
}


void SvtSearchOptions::SetMatchHiraganaKatakana( BOOL bVal )
{
    pImpl->SetFlag( 8, bVal );
}


BOOL SvtSearchOptions::IsMatchContractions() const
{
    return pImpl->GetFlag( 9 );
}


void SvtSearchOptions::SetMatchContractions( BOOL bVal )
{
    pImpl->SetFlag( 9, bVal );
}


BOOL SvtSearchOptions::IsMatchMinusDashChoon() const
{
    return pImpl->GetFlag( 10 );
}


void SvtSearchOptions::SetMatchMinusDashChoon( BOOL bVal )
{
    pImpl->SetFlag( 10, bVal );
}


BOOL SvtSearchOptions::IsMatchRepeatCharMarks() const
{
    return pImpl->GetFlag( 11 );
}


void SvtSearchOptions::SetMatchRepeatCharMarks( BOOL bVal )
{
    pImpl->SetFlag( 11, bVal );
}


BOOL SvtSearchOptions::IsMatchVariantFormKanji() const
{
    return pImpl->GetFlag( 12 );
}


void SvtSearchOptions::SetMatchVariantFormKanji( BOOL bVal )
{
    pImpl->SetFlag( 12, bVal );
}


BOOL SvtSearchOptions::IsMatchOldKanaForms() const
{
    return pImpl->GetFlag( 13 );
}


void SvtSearchOptions::SetMatchOldKanaForms( BOOL bVal )
{
    pImpl->SetFlag( 13, bVal );
}


BOOL SvtSearchOptions::IsMatchDiziDuzu() const
{
    return pImpl->GetFlag( 14 );
}


void SvtSearchOptions::SetMatchDiziDuzu( BOOL bVal )
{
    pImpl->SetFlag( 14, bVal );
}


BOOL SvtSearchOptions::IsMatchBavaHafa() const
{
    return pImpl->GetFlag( 15 );
}


void SvtSearchOptions::SetMatchBavaHafa( BOOL bVal )
{
    pImpl->SetFlag( 15, bVal );
}


BOOL SvtSearchOptions::IsMatchTsithichiDhizi() const
{
    return pImpl->GetFlag( 16 );
}


void SvtSearchOptions::SetMatchTsithichiDhizi( BOOL bVal )
{
    pImpl->SetFlag( 16, bVal );
}


BOOL SvtSearchOptions::IsMatchHyuiyuByuvyu() const
{
    return pImpl->GetFlag( 17 );
}


void SvtSearchOptions::SetMatchHyuiyuByuvyu( BOOL bVal )
{
    pImpl->SetFlag( 17, bVal );
}


BOOL SvtSearchOptions::IsMatchSesheZeje() const
{
    return pImpl->GetFlag( 18 );
}


void SvtSearchOptions::SetMatchSesheZeje( BOOL bVal )
{
    pImpl->SetFlag( 18, bVal );
}


BOOL SvtSearchOptions::IsMatchIaiya() const
{
    return pImpl->GetFlag( 19 );
}


void SvtSearchOptions::SetMatchIaiya( BOOL bVal )
{
    pImpl->SetFlag( 19, bVal );
}


BOOL SvtSearchOptions::IsMatchKiku() const
{
    return pImpl->GetFlag( 20 );
}


void SvtSearchOptions::SetMatchKiku( BOOL bVal )
{
    pImpl->SetFlag( 20, bVal );
}


BOOL SvtSearchOptions::IsIgnorePunctuation() const
{
    return pImpl->GetFlag( 21 );
}


void SvtSearchOptions::SetIgnorePunctuation( BOOL bVal )
{
    pImpl->SetFlag( 21, bVal );
}


BOOL SvtSearchOptions::IsIgnoreWhitespace() const
{
    return pImpl->GetFlag( 22 );
}


void SvtSearchOptions::SetIgnoreWhitespace( BOOL bVal )
{
    pImpl->SetFlag( 22, bVal );
}


BOOL SvtSearchOptions::IsIgnoreProlongedSoundMark() const
{
    return pImpl->GetFlag( 23 );
}


void SvtSearchOptions::SetIgnoreProlongedSoundMark( BOOL bVal )
{
    pImpl->SetFlag( 23, bVal );
}


BOOL SvtSearchOptions::IsIgnoreMiddleDot() const
{
    return pImpl->GetFlag( 24 );
}


void SvtSearchOptions::SetIgnoreMiddleDot( BOOL bVal )
{
    pImpl->SetFlag( 24, bVal );
}



//////////////////////////////////////////////////////////////////////

}
