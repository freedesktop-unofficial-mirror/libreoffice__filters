/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: svx_unofdesc.cxx,v $
 *
 *  $Revision: 1.5 $
 *
 *  last change: $Author: rt $ $Date: 2006-10-27 21:55:02 $
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

#include "eeitem.hxx"


#ifndef _TOOLKIT_HELPRE_VCLUNOHELPER_HXX_
#include <toolkit/helper/vclunohelper.hxx>
#endif

#define ITEMID_FONT EE_CHAR_FONTINFO
#ifndef _SVX_FONTITEM_HXX //autogen
#include <fontitem.hxx>
#endif

#define ITEMID_FONTHEIGHT EE_CHAR_FONTHEIGHT
#ifndef _SVX_FHGTITEM_HXX //autoge
#include <fhgtitem.hxx>
#endif

#define ITEMID_POSTURE EE_CHAR_ITALIC
#ifndef _SVX_POSTITEM_HXX //autogen
#include <postitem.hxx>
#endif

#define ITEMID_UNDERLINE EE_CHAR_UNDERLINE
#ifndef _SVX_UDLNITEM_HXX //autogen
#include <udlnitem.hxx>
#endif

#define ITEMID_WEIGHT EE_CHAR_WEIGHT
#ifndef _SVX_WGHTITEM_HXX //autogen
#include <wghtitem.hxx>
#endif

#define ITEMID_CROSSEDOUT EE_CHAR_STRIKEOUT
#ifndef _SVX_CRSDITEM_HXX //autog
#include <crsditem.hxx>
#endif

#define ITEMID_WORDLINEMODE EE_CHAR_WLM
#ifndef _SVX_WRLMITEM_HXX //aut
#include <wrlmitem.hxx>
#endif


#ifndef _SFXITEMPOOL_HXX //autogen
#include <svtools/itempool.hxx>
#endif

#include "unofdesc.hxx"
namespace binfilter {

using namespace ::rtl;
using namespace ::com::sun::star;


void SvxUnoFontDescriptor::ConvertToFont( const awt::FontDescriptor& rDesc, Font& rFont )
{
    rFont.SetName( rDesc.Name );
    rFont.SetStyleName( rDesc.StyleName );
    rFont.SetSize( Size( rDesc.Width, rDesc.Height ) );
    rFont.SetFamily( (FontFamily)rDesc.Family );
    rFont.SetCharSet( (CharSet)rDesc.CharSet );
    rFont.SetPitch( (FontPitch)rDesc.Pitch );
    rFont.SetOrientation( (short)(rDesc.Orientation*10) );
    rFont.SetKerning( rDesc.Kerning );
    rFont.SetWeight( VCLUnoHelper::ConvertFontWeight(rDesc.Weight) );
    rFont.SetItalic( (FontItalic)rDesc.Slant );
    rFont.SetUnderline( (FontUnderline)rDesc.Underline );
    rFont.SetStrikeout( (FontStrikeout)rDesc.Strikeout );
    rFont.SetWordLineMode( rDesc.WordLineMode );
}

void SvxUnoFontDescriptor::ConvertFromFont( const Font& rFont, awt::FontDescriptor& rDesc )
{
    rDesc.Name = rFont.GetName();
    rDesc.StyleName = rFont.GetStyleName();
    rDesc.Width = rFont.GetSize().Width();
    rDesc.Height = rFont.GetSize().Height();
    rDesc.Family = rFont.GetFamily();
    rDesc.CharSet = rFont.GetCharSet();
    rDesc.Pitch = rFont.GetPitch();
    rDesc.Orientation = rFont.GetOrientation() / 10;
    rDesc.Kerning = rFont.IsKerning();
    rDesc.Weight = VCLUnoHelper::ConvertFontWeight( rFont.GetWeight() );
    rDesc.Slant = (awt::FontSlant)rFont.GetItalic();
    rDesc.Underline = rFont.GetUnderline();
    rDesc.Strikeout = rFont.GetStrikeout();
    rDesc.WordLineMode = rFont.IsWordLineMode();
}

void SvxUnoFontDescriptor::FillItemSet( const awt::FontDescriptor& rDesc, SfxItemSet& rSet )
{
    uno::Any aTemp;

    {
        SvxFontItem aFontItem( EE_CHAR_FONTINFO );
        aFontItem.GetFamilyName()= rDesc.Name;
        aFontItem.GetStyleName() = rDesc.StyleName;
        aFontItem.GetFamily()    = (FontFamily)rDesc.Family;
        aFontItem.GetCharSet()   = rDesc.CharSet;
        aFontItem.GetPitch()     = (FontPitch)rDesc.Pitch;
        rSet.Put(aFontItem);
    }

    {
        SvxFontHeightItem aFontHeightItem( 0, 100, EE_CHAR_FONTHEIGHT );
        aTemp <<= (float)rDesc.Height;
        ((SfxPoolItem*)&aFontHeightItem)->PutValue( aTemp, MID_FONTHEIGHT|CONVERT_TWIPS );
        rSet.Put(aFontHeightItem);
    }

    {
        SvxPostureItem aPostureItem( (FontItalic)0, EE_CHAR_ITALIC );
        aTemp <<= rDesc.Slant;
        ((SfxPoolItem*)&aPostureItem)->PutValue( aTemp, MID_POSTURE );
        rSet.Put(aPostureItem);
    }

    {
        SvxUnderlineItem aUnderlineItem( (FontUnderline)0, EE_CHAR_UNDERLINE );
        aTemp <<= (sal_Int16)rDesc.Underline;
        ((SfxPoolItem*)&aUnderlineItem)->PutValue( aTemp, MID_UNDERLINE );
        rSet.Put( aUnderlineItem );
    }

    {
        SvxWeightItem aWeightItem( (FontWeight)0, EE_CHAR_WEIGHT );
        aTemp <<= rDesc.Weight;
        ((SfxPoolItem*)&aWeightItem)->PutValue( aTemp, MID_WEIGHT );
        rSet.Put( aWeightItem );
    }

    {
        SvxCrossedOutItem aCrossedOutItem( (FontStrikeout)0, EE_CHAR_STRIKEOUT );
        aTemp <<= rDesc.Strikeout;
        ((SfxPoolItem*)&aCrossedOutItem)->PutValue( aTemp, MID_CROSS_OUT );
        rSet.Put( aCrossedOutItem );
    }

    {
        SvxWordLineModeItem aWLMItem( rDesc.WordLineMode, EE_CHAR_WLM );
        rSet.Put( aWLMItem );
    }
}

void SvxUnoFontDescriptor::FillFromItemSet( const SfxItemSet& rSet, awt::FontDescriptor& rDesc )
{
    const SfxPoolItem* pItem = NULL;
    {
        SvxFontItem* pFontItem = (SvxFontItem*)&rSet.Get( EE_CHAR_FONTINFO, TRUE );
        rDesc.Name		= pFontItem->GetFamilyName();
        rDesc.StyleName	= pFontItem->GetStyleName();
        rDesc.Family	= pFontItem->GetFamily();
        rDesc.CharSet	= pFontItem->GetCharSet();
        rDesc.Pitch		= pFontItem->GetPitch();
    }
    {
        pItem = &rSet.Get( EE_CHAR_FONTHEIGHT, TRUE );
        uno::Any aHeight;
        if( pItem->QueryValue( aHeight, MID_FONTHEIGHT ) )
            aHeight >>= rDesc.Height;
    }
    {
        pItem = &rSet.Get( EE_CHAR_ITALIC, TRUE );
        uno::Any aFontSlant;
        if(pItem->QueryValue( aFontSlant, MID_POSTURE ))
            aFontSlant >>= rDesc.Slant;
    }
    {
        pItem = &rSet.Get( EE_CHAR_UNDERLINE, TRUE );
        uno::Any aUnderline;
        if(pItem->QueryValue( aUnderline, MID_UNDERLINE ))
            aUnderline >>= rDesc.Underline;
    }
    {
        pItem = &rSet.Get( EE_CHAR_WEIGHT, TRUE );
        uno::Any aWeight;
        if(pItem->QueryValue( aWeight, MID_WEIGHT ))
            aWeight >>= rDesc.Weight;
    }
    {
        pItem = &rSet.Get( EE_CHAR_STRIKEOUT, TRUE );
        uno::Any aStrikeOut;
        if(pItem->QueryValue( aStrikeOut, MID_CROSS_OUT ))
            aStrikeOut >>= rDesc.Strikeout;
    }
    {
        SvxWordLineModeItem* pWLMItem = (SvxWordLineModeItem*)&rSet.Get( EE_CHAR_WLM, TRUE );
        rDesc.WordLineMode = pWLMItem->GetValue();
    }
}

#define CheckState( state ) \
    switch( state ) \
    { \
    case SFX_ITEM_DONTCARE: \
    case SFX_ITEM_DISABLED: \
        return beans::PropertyState_AMBIGUOUS_VALUE; \
    case SFX_ITEM_READONLY: \
    case SFX_ITEM_SET: \
        return beans::PropertyState_DIRECT_VALUE; \
    }

beans::PropertyState SvxUnoFontDescriptor::getPropertyState( const SfxItemSet& rSet )
{
    CheckState(rSet.GetItemState( EE_CHAR_FONTINFO, FALSE ));
    CheckState(rSet.GetItemState( EE_CHAR_FONTHEIGHT, FALSE ));
    CheckState(rSet.GetItemState( EE_CHAR_ITALIC, FALSE ));
    CheckState(rSet.GetItemState( EE_CHAR_UNDERLINE, FALSE ));
    CheckState(rSet.GetItemState( EE_CHAR_WEIGHT, FALSE ));
    CheckState(rSet.GetItemState( EE_CHAR_STRIKEOUT, FALSE ));
    CheckState(rSet.GetItemState( EE_CHAR_WLM, FALSE ));

    return beans::PropertyState_DEFAULT_VALUE;
}

void SvxUnoFontDescriptor::setPropertyToDefault( SfxItemSet& rSet )
{
    rSet.InvalidateItem( EE_CHAR_FONTINFO );
    rSet.InvalidateItem( EE_CHAR_FONTHEIGHT );
    rSet.InvalidateItem( EE_CHAR_ITALIC );
    rSet.InvalidateItem( EE_CHAR_UNDERLINE );
    rSet.InvalidateItem( EE_CHAR_WEIGHT );
    rSet.InvalidateItem( EE_CHAR_STRIKEOUT );
    rSet.InvalidateItem( EE_CHAR_WLM );
}

uno::Any SvxUnoFontDescriptor::getPropertyDefault( SfxItemPool* pPool )
{
    SfxItemSet aSet( *pPool, EE_CHAR_FONTINFO, EE_CHAR_FONTINFO,
                             EE_CHAR_FONTHEIGHT, EE_CHAR_FONTHEIGHT,
                             EE_CHAR_ITALIC, EE_CHAR_ITALIC,
                             EE_CHAR_UNDERLINE, EE_CHAR_UNDERLINE,
                             EE_CHAR_WEIGHT, EE_CHAR_WEIGHT,
                             EE_CHAR_STRIKEOUT, EE_CHAR_STRIKEOUT,
                             EE_CHAR_WLM, EE_CHAR_WLM, 0 );

    uno::Any aAny;

    if(!pPool->IsWhich(EE_CHAR_FONTINFO)||
        !pPool->IsWhich(EE_CHAR_FONTHEIGHT)||
        !pPool->IsWhich(EE_CHAR_ITALIC)||
        !pPool->IsWhich(EE_CHAR_UNDERLINE)||
        !pPool->IsWhich(EE_CHAR_WEIGHT)||
        !pPool->IsWhich(EE_CHAR_STRIKEOUT)||
        !pPool->IsWhich(EE_CHAR_WLM))
        return aAny;

    aSet.Put(pPool->GetDefaultItem(EE_CHAR_FONTINFO));
    aSet.Put(pPool->GetDefaultItem(EE_CHAR_FONTHEIGHT));
    aSet.Put(pPool->GetDefaultItem(EE_CHAR_ITALIC));
    aSet.Put(pPool->GetDefaultItem(EE_CHAR_UNDERLINE));
    aSet.Put(pPool->GetDefaultItem(EE_CHAR_WEIGHT));
    aSet.Put(pPool->GetDefaultItem(EE_CHAR_STRIKEOUT));
    aSet.Put(pPool->GetDefaultItem(EE_CHAR_WLM));

    awt::FontDescriptor aDesc;

    FillFromItemSet( aSet, aDesc );

    aAny <<= aDesc;

    return aAny;
}



}
