/*************************************************************************
 *
 *  $RCSfile: svx_textitem.cxx,v $
 *
 *  $Revision: 1.3 $
 *
 *  last change: $Author: aw $ $Date: 2004-02-13 14:30:42 $
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

// include ---------------------------------------------------------------

#ifndef _COM_SUN_STAR_STYLE_CASEMAP_HPP_
#include <com/sun/star/style/CaseMap.hpp>
#endif

#ifndef _SV_BITMAPEX_HXX
#include <vcl/bitmapex.hxx>
#endif
#ifndef _STREAM_HXX
#include <tools/stream.hxx>
#endif
#include <toolkit/unohlp.hxx>
#include <math.h>
#ifndef INCLUDED_RTL_MATH_HXX
#include <rtl/math.hxx>
#endif

#include <eeitem.hxx>

#pragma hdrstop

#define ITEMID_FONTLIST	 		0
#define ITEMID_FONT	 	        0
#define ITEMID_POSTURE	 	    0
#define ITEMID_WEIGHT	 	    0
#define ITEMID_FONTHEIGHT	    0
#define ITEMID_UNDERLINE	    0
#define ITEMID_CROSSEDOUT	    0
#define ITEMID_SHADOWED	 	    0
#define ITEMID_AUTOKERN	 	    0
#define ITEMID_WORDLINEMODE     0
#define ITEMID_CONTOUR	 	    0
#define ITEMID_PROPSIZE	 	    0
#define ITEMID_COLOR	 	    0
#define ITEMID_CHARSETCOLOR     0
#define ITEMID_KERNING	 	    0
#define ITEMID_CASEMAP	 	    0
#define ITEMID_ESCAPEMENT	    0
#define ITEMID_LANGUAGE	 	    0
#define ITEMID_NOLINEBREAK	    0
#define ITEMID_NOHYPHENHERE     0
#define ITEMID_BLINK	 	    0
#define ITEMID_EMPHASISMARK	    0
#define ITEMID_TWOLINES	    	0
#define ITEMID_CHARROTATE		0
#define ITEMID_CHARSCALE_W		0
#define ITEMID_CHARRELIEF		0


#include <svtools/sbx.hxx>
#define GLOBALOVERFLOW3


#include <svtools/memberid.hrc>
#include "svxids.hrc"
#include "svxitems.hrc"

//#ifndef NOOLDSV //autogen
//#include <vcl/system.hxx>
//#endif
#ifndef _VCL_VCLENUM_HXX
#include <vcl/vclenum.hxx>
#endif

#ifndef _BIGINT_HXX //autogen
#include <tools/bigint.hxx>
#endif
#ifndef _TOOLS_TENCCVT_HXX //autogen
#include <tools/tenccvt.hxx>
#endif

#include <rtl/ustring>
#ifndef _ISOLANG_HXX
#include <tools/isolang.hxx>
#endif
#ifndef _SFXITEMSET_HXX
#include <svtools/itemset.hxx>
#endif
#ifndef _SFXITEMPOOL_HXX
#include <svtools/itempool.hxx>
#endif
#ifndef _SV_SETTINGS_HXX
#include <vcl/settings.hxx>
#endif
#ifndef _SV_SVAPP_HXX
#include <vcl/svapp.hxx>
#endif

#ifndef _COM_SUN_STAR_STYLE_CASEMAP_HPP_
#include <com/sun/star/style/CaseMap.hpp>
#endif
#ifndef _COM_SUN_STAR_AWT_SIMPLEFONTMETRIC_HPP_
#include <com/sun/star/awt/SimpleFontMetric.hpp>
#endif
#ifndef _COM_SUN_STAR_AWT_FONTWEIGHT_HPP_
#include <com/sun/star/awt/FontWeight.hpp>
#endif
#ifndef _COM_SUN_STAR_AWT_FONTSLANT_HPP_
#include <com/sun/star/awt/FontSlant.hpp>
#endif
#ifndef _COM_SUN_STAR_AWT_CHARSET_HPP_
#include <com/sun/star/awt/CharSet.hpp>
#endif
#ifndef _COM_SUN_STAR_AWT_FONTDESCRIPTOR_HPP_
#include <com/sun/star/awt/FontDescriptor.hpp>
#endif
#ifndef _COM_SUN_STAR_AWT_FONTWIDTH_HPP_
#include <com/sun/star/awt/FontWidth.hpp>
#endif
#ifndef _COM_SUN_STAR_AWT_XFONT_HPP_
#include <com/sun/star/awt/XFont.hpp>
#endif
#ifndef _COM_SUN_STAR_AWT_FONTTYPE_HPP_
#include <com/sun/star/awt/FontType.hpp>
#endif
#ifndef _COM_SUN_STAR_AWT_FONTUNDERLINE_HPP_
#include <com/sun/star/awt/FontUnderline.hpp>
#endif
#ifndef _COM_SUN_STAR_AWT_FONTSTRIKEOUT_HPP_
#include <com/sun/star/awt/FontStrikeout.hpp>
#endif
#ifndef _COM_SUN_STAR_AWT_FONTFAMILY_HPP_
#include <com/sun/star/awt/FontFamily.hpp>
#endif
#ifndef _COM_SUN_STAR_AWT_FONTPITCH_HPP_
#include <com/sun/star/awt/FontPitch.hpp>
#endif
#ifndef _COM_SUN_STAR_LANG_LOCALE_HPP_
#include <com/sun/star/lang/Locale.hpp>
#endif
#ifndef _COM_SUN_STAR_TEXT_FONTEMPHASIS_HPP_
#include <com/sun/star/text/FontEmphasis.hpp>
#endif
#ifndef _COM_SUN_STAR_I18N_SCRIPTTYPE_HPP_
#include <com/sun/star/i18n/ScriptType.hpp>
#endif

#ifndef _SVX_UNOMID_HXX
#include <unomid.hxx>
#endif


#include "flstitem.hxx"
#include "fontitem.hxx"
#include "postitem.hxx"
#include "wghtitem.hxx"
#include "fhgtitem.hxx"
#include "fwdtitem.hxx"
#include "udlnitem.hxx"
#include "crsditem.hxx"
#include "shdditem.hxx"
#include "akrnitem.hxx"
#include "wrlmitem.hxx"
#include "cntritem.hxx"
#include "prszitem.hxx"
#include "colritem.hxx"
#include "cscoitem.hxx"
#include "kernitem.hxx"
#include "cmapitem.hxx"
#include "escpitem.hxx"
#include "langitem.hxx"
#include "nlbkitem.hxx"
#include "nhypitem.hxx"
#include "lcolitem.hxx"
#include "blnkitem.hxx"
#include "emphitem.hxx"
#include "twolinesitem.hxx"
#include "scripttypeitem.hxx"
#include "charrotateitem.hxx"
#include "charscaleitem.hxx"
#include "charreliefitem.hxx"
#include "itemtype.hxx"
#include "dialmgr.hxx"
#include "langtab.hxx"
#include "dlgutil.hxx"

// #90477#
#ifndef _TOOLS_TENCCVT_HXX
#include <tools/tenccvt.hxx>
#endif
namespace binfilter {

#define STORE_UNICODE_MAGIC_MARKER  0xFE331188

using namespace ::rtl;
using namespace ::com::sun::star;
using namespace ::com::sun::star::text;

// Konvertierung fuer UNO
#define TWIP_TO_MM100(TWIP) 	((TWIP) >= 0 ? (((TWIP)*127L+36L)/72L) : (((TWIP)*127L-36L)/72L))
#define MM100_TO_TWIP(MM100)	((MM100) >= 0 ? (((MM100)*72L+63L)/127L) : (((MM100)*72L-63L)/127L))

BOOL SvxFontItem::bEnableStoreUnicodeNames = FALSE;

// STATIC DATA -----------------------------------------------------------

// -----------------------------------------------------------------------

/*N*/ TYPEINIT1(SvxFontListItem, SfxPoolItem);
/*N*/ TYPEINIT1_AUTOFACTORY(SvxFontItem, SfxPoolItem);
/*N*/ TYPEINIT1_AUTOFACTORY(SvxPostureItem, SfxEnumItem);
/*N*/ TYPEINIT1_AUTOFACTORY(SvxWeightItem, SfxEnumItem);
/*N*/ TYPEINIT1_AUTOFACTORY(SvxFontHeightItem, SfxPoolItem);
//STRIP001 TYPEINIT1_AUTOFACTORY(SvxFontWidthItem, SfxPoolItem);
/*N*/ TYPEINIT1_AUTOFACTORY(SvxUnderlineItem, SfxEnumItem);
/*N*/ TYPEINIT1_AUTOFACTORY(SvxCrossedOutItem, SfxEnumItem);
/*N*/ TYPEINIT1_AUTOFACTORY(SvxShadowedItem, SfxBoolItem);
/*N*/ TYPEINIT1_AUTOFACTORY(SvxAutoKernItem, SfxBoolItem);
/*N*/ TYPEINIT1_AUTOFACTORY(SvxWordLineModeItem, SfxBoolItem);
/*N*/ TYPEINIT1_AUTOFACTORY(SvxContourItem, SfxBoolItem);
/*N*/ TYPEINIT1_AUTOFACTORY(SvxPropSizeItem, SfxUInt16Item);
/*N*/ TYPEINIT1_AUTOFACTORY(SvxColorItem, SfxPoolItem);
/*N*/ TYPEINIT1_AUTOFACTORY(SvxCharSetColorItem, SvxColorItem);
/*N*/ TYPEINIT1_AUTOFACTORY(SvxKerningItem, SfxInt16Item);
/*N*/ TYPEINIT1_AUTOFACTORY(SvxCaseMapItem, SfxEnumItem);
/*N*/ TYPEINIT1_AUTOFACTORY(SvxEscapementItem, SfxPoolItem);
/*N*/ TYPEINIT1_AUTOFACTORY(SvxLanguageItem, SfxEnumItem);
/*N*/ TYPEINIT1_AUTOFACTORY(SvxNoLinebreakItem, SfxBoolItem);
/*N*/ TYPEINIT1_AUTOFACTORY(SvxNoHyphenItem, SfxBoolItem);
//STRIP001 TYPEINIT1_AUTOFACTORY(SvxLineColorItem, SvxColorItem);
/*N*/ TYPEINIT1_AUTOFACTORY(SvxBlinkItem, SfxBoolItem);
/*N*/ TYPEINIT1_AUTOFACTORY(SvxEmphasisMarkItem, SfxUInt16Item);
/*N*/ TYPEINIT1_AUTOFACTORY(SvxTwoLinesItem, SfxPoolItem);
//STRIP001 TYPEINIT1_AUTOFACTORY(SvxScriptTypeItem, SfxUInt16Item);
/*N*/ TYPEINIT1_AUTOFACTORY(SvxCharRotateItem, SfxUInt16Item);
/*N*/ TYPEINIT1_AUTOFACTORY(SvxCharScaleWidthItem, SfxUInt16Item);
/*N*/ TYPEINIT1_AUTOFACTORY(SvxCharReliefItem, SfxEnumItem);


/*N*/ TYPEINIT1(SvxScriptSetItem, SfxSetItem );


// class SvxFontListItem -------------------------------------------------

/*N*/ SvxFontListItem::SvxFontListItem( const FontList* pFontLst,
/*N*/ 								  const USHORT nId ) :
/*N*/ 	SfxPoolItem( nId ),
/*N*/ 	pFontList( pFontLst )
/*N*/ {
/*N*/ }

// -----------------------------------------------------------------------

/*N*/ SvxFontListItem::SvxFontListItem( const SvxFontListItem& rItem ) :
/*N*/ 
/*N*/ 	SfxPoolItem( rItem ),
/*N*/ 	pFontList( rItem.GetFontList() )
/*N*/ {
/*N*/ }

// -----------------------------------------------------------------------

/*N*/ SfxPoolItem* SvxFontListItem::Clone( SfxItemPool* ) const
/*N*/ {
/*N*/ 	return new SvxFontListItem( *this );
/*N*/ }

// -----------------------------------------------------------------------

/*?*/ int SvxFontListItem::operator==( const SfxPoolItem& rAttr ) const
/*?*/ {
/*?*/ DBG_ASSERT(0, "STRIP"); return 0;//STRIP001 	DBG_ASSERT( SfxPoolItem::operator==(rAttr), "unequal types" );
//STRIP001 
//STRIP001 	return( pFontList == ((SvxFontListItem&)rAttr).pFontList );
/*?*/ }

//------------------------------------------------------------------------

//STRIP001 SfxItemPresentation SvxFontListItem::GetPresentation
//STRIP001 (
//STRIP001 	SfxItemPresentation ePres,
//STRIP001 	SfxMapUnit			eCoreUnit,
//STRIP001 	SfxMapUnit			ePresUnit,
//STRIP001     XubString&          rText, const IntlWrapper *pIntl
//STRIP001 )	const
//STRIP001 {
//STRIP001 	rText.Erase();
//STRIP001 	return SFX_ITEM_PRESENTATION_NONE;
//STRIP001 }

// class SvxFontItem -----------------------------------------------------

/*N*/ SvxFontItem::SvxFontItem( const USHORT nId ) :
/*N*/ 	SfxPoolItem( nId )
/*N*/ {
/*N*/ 	eFamily = FAMILY_SWISS;
/*N*/ 	ePitch = PITCH_VARIABLE;
/*N*/ 	eTextEncoding = RTL_TEXTENCODING_DONTKNOW;
/*N*/ }

// -----------------------------------------------------------------------

/*N*/ SvxFontItem::SvxFontItem( const FontFamily eFam, const XubString& aName,
/*N*/ 				  const XubString& aStName, const FontPitch eFontPitch,
/*N*/ 				  const rtl_TextEncoding eFontTextEncoding, const USHORT nId ) :
/*N*/ 
/*N*/ 	SfxPoolItem( nId ),
/*N*/ 
/*N*/ 	aFamilyName(aName),
/*N*/ 	aStyleName(aStName)
/*N*/ {
/*N*/ 	eFamily = eFam;
/*N*/ 	ePitch = eFontPitch;
/*N*/ 	eTextEncoding = eFontTextEncoding;
/*N*/ }

// -----------------------------------------------------------------------

/*N*/ sal_Bool SvxFontItem::QueryValue( uno::Any& rVal, BYTE nMemberId ) const
/*N*/ {
/*N*/     sal_Bool bConvert = 0!=(nMemberId&CONVERT_TWIPS);
/*N*/     nMemberId &= ~CONVERT_TWIPS;
/*N*/ 	switch(nMemberId)
/*N*/ 	{
/*N*/ 		case MID_FONT_FAMILY_NAME	:
/*N*/ 			rVal <<= OUString(aFamilyName.GetBuffer());
/*N*/ 		break;
/*N*/ 		case MID_FONT_STYLE_NAME:
/*N*/ 			rVal <<= OUString(aStyleName.GetBuffer());
/*N*/ 		break;
/*N*/ 		case MID_FONT_FAMILY    : rVal <<= (sal_Int16)(eFamily);	break;
/*N*/ 		case MID_FONT_CHAR_SET  : rVal <<= (sal_Int16)(eTextEncoding);	break;
/*N*/ 		case MID_FONT_PITCH     : rVal <<= (sal_Int16)(ePitch);	break;
/*N*/ 	}
/*N*/ 	return sal_True;
/*N*/ }
// -----------------------------------------------------------------------
/*N*/ sal_Bool SvxFontItem::PutValue( const uno::Any& rVal, BYTE nMemberId)
/*N*/ {
/*N*/     sal_Bool bConvert = 0!=(nMemberId&CONVERT_TWIPS);
/*N*/     nMemberId &= ~CONVERT_TWIPS;
/*N*/ 	switch(nMemberId)
/*N*/ 	{
/*N*/ 		case MID_FONT_FAMILY_NAME	:
/*N*/ 		{
/*N*/ 			OUString aStr;
/*N*/ 			if(!(rVal >>= aStr))
/*N*/ 				return sal_False;
/*N*/ 			aFamilyName = aStr.getStr();
/*N*/ 		}
/*N*/ 		break;
/*N*/ 		case MID_FONT_STYLE_NAME:
/*N*/ 		{
/*N*/ 			OUString aStr;
/*N*/ 			if(!(rVal >>= aStr))
/*N*/ 				return sal_False;
/*N*/ 			aStyleName = aStr.getStr();
/*N*/ 		}
/*N*/ 		break;
/*N*/ 		case MID_FONT_FAMILY :
/*N*/ 		{
/*N*/ 			sal_Int16 nFamily;
/*N*/ 			if(!(rVal >>= nFamily))
/*N*/ 				return sal_False;
/*N*/ 			eFamily = (FontFamily)nFamily;
/*N*/ 		}
/*N*/ 		break;
/*N*/ 		case MID_FONT_CHAR_SET  :
/*N*/ 		{
/*N*/ 			sal_Int16 nSet;
/*N*/ 			if(!(rVal >>= nSet))
/*N*/ 				return sal_False;
/*N*/ 			eTextEncoding = (rtl_TextEncoding)nSet;
/*N*/ 		}
/*N*/ 		break;
/*N*/ 		case MID_FONT_PITCH     :
/*N*/ 		{
/*N*/ 			sal_Int16 nPitch;
/*N*/ 			if(!(rVal >>= nPitch))
/*N*/ 				return sal_False;
/*N*/ 			ePitch =  (FontPitch)nPitch;
/*N*/ 		}
/*N*/ 		break;
/*N*/ 	}
/*N*/ 	return sal_True;
/*N*/ }

// -----------------------------------------------------------------------

/*N*/ int SvxFontItem::operator==( const SfxPoolItem& rAttr ) const
/*N*/ {
/*N*/ 	DBG_ASSERT( SfxPoolItem::operator==(rAttr), "unequal types" );
/*N*/ 
/*N*/ 	const SvxFontItem& rItem = (const SvxFontItem&)rAttr;
/*N*/ 
/*N*/ 	int bRet = ( eFamily == rItem.eFamily &&
/*N*/ 				 aFamilyName == rItem.aFamilyName &&
/*N*/ 				 aStyleName == rItem.aStyleName );
/*N*/ 
/*N*/ 	if ( bRet )
/*N*/ 	{
/*N*/ 		if ( ePitch != rItem.ePitch || eTextEncoding != rItem.eTextEncoding )
/*N*/ 		{
/*N*/ 			bRet = sal_False;
/*N*/ 			DBG_WARNING( "FontItem::operator==(): nur Pitch oder rtl_TextEncoding unterschiedlich" );
/*N*/ 		}
/*N*/ 	}
/*N*/ 	return bRet;
/*N*/ }

// -----------------------------------------------------------------------

/*N*/ SfxPoolItem* SvxFontItem::Clone( SfxItemPool * ) const
/*N*/ {
/*N*/ 	return new SvxFontItem( *this );
/*N*/ }

// -----------------------------------------------------------------------

/*N*/ SvStream& SvxFontItem::Store( SvStream& rStrm , USHORT nItemVersion ) const
/*N*/ {
/*N*/ 	BOOL bToBats =
/*N*/ 		GetFamilyName().EqualsAscii( "StarSymbol", 0, sizeof("StarSymbol")-1 ) ||
/*N*/ 		GetFamilyName().EqualsAscii( "OpenSymbol", 0, sizeof("OpenSymbol")-1 );
/*N*/ 
/*N*/ 	// #90477# rStrm << (BYTE) GetFamily()
/*N*/ 	//	  << (BYTE) GetPitch()
/*N*/ 	//	  << (BYTE)(bToBats ? RTL_TEXTENCODING_SYMBOL : GetStoreCharSet( GetCharSet(), (USHORT)rStrm.GetVersion() ) );
/*N*/ 	rStrm << (BYTE) GetFamily() << (BYTE) GetPitch()
/*N*/ 		  << (BYTE)(bToBats ? RTL_TEXTENCODING_SYMBOL : GetSOStoreTextEncoding(GetCharSet(), (sal_uInt16)rStrm.GetVersion()));
/*N*/ 
/*N*/     String aStoreFamilyName( GetFamilyName() );
/*N*/     if( bToBats )
/*N*/ 		aStoreFamilyName = String( "StarBats", sizeof("StarBats")-1, RTL_TEXTENCODING_ASCII_US );
/*N*/     rStrm.WriteByteString(aStoreFamilyName);
/*N*/ 	rStrm.WriteByteString(GetStyleName());
/*N*/ 
/*N*/     // #96441# Kach for EditEngine, only set while creating clipboard stream.
/*N*/     if ( bEnableStoreUnicodeNames )
/*N*/     {
/*N*/         ULONG nMagic = STORE_UNICODE_MAGIC_MARKER;
/*N*/         rStrm << nMagic;
/*N*/         rStrm.WriteByteString( aStoreFamilyName, RTL_TEXTENCODING_UNICODE );
/*N*/ 	    rStrm.WriteByteString( GetStyleName(), RTL_TEXTENCODING_UNICODE );
/*N*/     }
/*N*/ 
/*N*/ 	return rStrm;
/*N*/ }

// -----------------------------------------------------------------------

/*N*/ SfxPoolItem* SvxFontItem::Create(SvStream& rStrm, USHORT) const
/*N*/ {
/*N*/ 	BYTE eFamily, eFontPitch, eFontTextEncoding;
/*N*/ 	String aName, aStyle;
/*N*/ 	rStrm >> eFamily;
/*N*/ 	rStrm >> eFontPitch;
/*N*/ 	rStrm >> eFontTextEncoding;
/*N*/ 
/*N*/ 	// UNICODE: rStrm >> aName;
/*N*/ 	rStrm.ReadByteString(aName);
/*N*/ 
/*N*/ 	// UNICODE: rStrm >> aStyle;
/*N*/ 	rStrm.ReadByteString(aStyle);
/*N*/ 
/*N*/ 	// Task 91008/90471: set the "correct" textencoding
/*N*/ 	eFontTextEncoding = (BYTE)GetSOLoadTextEncoding( eFontTextEncoding, (USHORT)rStrm.GetVersion() );
/*N*/ 
/*N*/ 	// irgendwann wandelte sich der StarBats vom ANSI- zum SYMBOL-Font
/*N*/ 	if ( RTL_TEXTENCODING_SYMBOL != eFontTextEncoding && aName.EqualsAscii("StarBats") )
/*N*/ 		eFontTextEncoding = RTL_TEXTENCODING_SYMBOL;
/*N*/ 
/*N*/     // Check if we have stored unicode
/*N*/     ULONG nStreamPos = rStrm.Tell();
/*N*/     ULONG nMagic = STORE_UNICODE_MAGIC_MARKER;
/*N*/     rStrm >> nMagic;
/*N*/     if ( nMagic == STORE_UNICODE_MAGIC_MARKER )
/*N*/     {
/*N*/         rStrm.ReadByteString( aName, RTL_TEXTENCODING_UNICODE );
/*N*/ 	    rStrm.ReadByteString( aStyle, RTL_TEXTENCODING_UNICODE );
/*N*/     }
/*N*/     else
/*N*/     {
/*N*/         rStrm.Seek( nStreamPos );
/*N*/     }
/*N*/ 
/*N*/ 
/*N*/ 
/*N*/ 	return new SvxFontItem( (FontFamily)eFamily, aName, aStyle,
/*N*/ 							(FontPitch)eFontPitch, (rtl_TextEncoding)eFontTextEncoding,	Which() );
/*N*/ }

//------------------------------------------------------------------------

//STRIP001 SfxItemPresentation SvxFontItem::GetPresentation
//STRIP001 (
//STRIP001 	SfxItemPresentation ePres,
//STRIP001 	SfxMapUnit			eCoreUnit,
//STRIP001 	SfxMapUnit			ePresUnit,
//STRIP001     XubString&          rText, const IntlWrapper *pIntl
//STRIP001 )	const
//STRIP001 {
//STRIP001 	switch ( ePres )
//STRIP001 	{
//STRIP001 		case SFX_ITEM_PRESENTATION_NONE:
//STRIP001 			rText.Erase();
//STRIP001 			return ePres;
//STRIP001 		case SFX_ITEM_PRESENTATION_NAMELESS:
//STRIP001 		case SFX_ITEM_PRESENTATION_COMPLETE:
//STRIP001 			rText = aFamilyName;
//STRIP001 			return ePres;
//STRIP001 	}
//STRIP001 	return SFX_ITEM_PRESENTATION_NONE;
//STRIP001 }

// class SvxPostureItem --------------------------------------------------

/*N*/ SvxPostureItem::SvxPostureItem( const FontItalic ePosture, const USHORT nId ) :
/*N*/ 	SfxEnumItem( nId, ePosture )
/*N*/ {
/*N*/ }

// -----------------------------------------------------------------------

/*N*/ SfxPoolItem* SvxPostureItem::Clone( SfxItemPool * ) const
/*N*/ {
/*N*/ 	return new SvxPostureItem( *this );
/*N*/ }

// -----------------------------------------------------------------------

/*?*/ USHORT SvxPostureItem::GetValueCount() const
/*?*/ {
/*?*/ DBG_ASSERT(0, "STRIP"); return 0;//STRIP001 /*?*/ 	return ITALIC_NORMAL + 1;	// auch ITALIC_NONE geh"ort dazu
/*?*/ }

// -----------------------------------------------------------------------

/*N*/ SvStream& SvxPostureItem::Store( SvStream& rStrm , USHORT nItemVersion ) const
/*N*/ {
/*N*/ 	rStrm << (BYTE)GetValue();
/*N*/ 	return rStrm;
/*N*/ }

// -----------------------------------------------------------------------

/*N*/ SfxPoolItem* SvxPostureItem::Create(SvStream& rStrm, USHORT) const
/*N*/ {
/*N*/ 	BYTE nPosture;
/*N*/ 	rStrm >> nPosture;
/*N*/ 	return new SvxPostureItem( (const FontItalic)nPosture, Which() );
/*N*/ }

//------------------------------------------------------------------------

//STRIP001 SfxItemPresentation SvxPostureItem::GetPresentation
//STRIP001 (
//STRIP001 	SfxItemPresentation ePres,
//STRIP001 	SfxMapUnit			eCoreUnit,
//STRIP001 	SfxMapUnit			ePresUnit,
//STRIP001     XubString&          rText, const IntlWrapper *pIntl
//STRIP001 )	const
//STRIP001 {
//STRIP001 	switch ( ePres )
//STRIP001 	{
//STRIP001 		case SFX_ITEM_PRESENTATION_NONE:
//STRIP001 			rText.Erase();
//STRIP001 			return ePres;
//STRIP001 		case SFX_ITEM_PRESENTATION_NAMELESS:
//STRIP001 		case SFX_ITEM_PRESENTATION_COMPLETE:
//STRIP001 			rText = GetValueTextByPos( GetValue() );
//STRIP001 			return ePres;
//STRIP001 	}
//STRIP001 	return SFX_ITEM_PRESENTATION_NONE;
//STRIP001 }

// -----------------------------------------------------------------------

//STRIP001 XubString SvxPostureItem::GetValueTextByPos( USHORT nPos ) const
//STRIP001 {
//STRIP001 	DBG_ASSERT( nPos <= (USHORT)ITALIC_NORMAL, "enum overflow!" );
//STRIP001 
//STRIP001 	XubString sTxt;
//STRIP001 	FontItalic eItalic = (FontItalic)nPos;
//STRIP001 	USHORT nId = 0;
//STRIP001 
//STRIP001 	switch ( eItalic )
//STRIP001 	{
//STRIP001 		case ITALIC_NONE:		nId = RID_SVXITEMS_ITALIC_NONE;		break;
//STRIP001 		case ITALIC_OBLIQUE:	nId = RID_SVXITEMS_ITALIC_OBLIQUE;	break;
//STRIP001 		case ITALIC_NORMAL:		nId = RID_SVXITEMS_ITALIC_NORMAL;	break;
//STRIP001 	}
//STRIP001 
//STRIP001 	if ( nId )
//STRIP001 		sTxt = SVX_RESSTR( nId );
//STRIP001 	return sTxt;
//STRIP001 }


/*-----------------13.03.98 14:28-------------------

--------------------------------------------------*/
/*N*/ sal_Bool SvxPostureItem::QueryValue( uno::Any& rVal, BYTE nMemberId ) const
/*N*/ {
/*N*/     sal_Bool bConvert = 0!=(nMemberId&CONVERT_TWIPS);
/*N*/     nMemberId &= ~CONVERT_TWIPS;
/*N*/ 	switch( nMemberId )
/*N*/ 	{
/*N*/ 		case MID_ITALIC:
/*?*/ 			rVal = Bool2Any(GetBoolValue());
/*N*/ 			break;
/*N*/ 		case MID_POSTURE:
/*N*/ 			rVal <<= (awt::FontSlant)GetValue();	// Werte von awt::FontSlant und FontItalic sind gleich
/*N*/ 			break;
/*N*/ 	}
/*N*/ 	return sal_True;
/*N*/ }
/*-----------------13.03.98 14:28-------------------

--------------------------------------------------*/
/*N*/ sal_Bool SvxPostureItem::PutValue( const uno::Any& rVal, BYTE nMemberId )
/*N*/ {
/*N*/     sal_Bool bConvert = 0!=(nMemberId&CONVERT_TWIPS);
/*N*/     nMemberId &= ~CONVERT_TWIPS;
/*N*/ 	switch( nMemberId )
/*N*/ 	{
/*N*/ 		case MID_ITALIC:
/*?*/ 			SetBoolValue(Any2Bool(rVal));
/*N*/ 		break;
/*N*/ 		case MID_POSTURE:
/*N*/ 		{
/*?*/ 			awt::FontSlant eSlant;
/*?*/ 			if(!(rVal >>= eSlant))
/*?*/ 			{
/*?*/ 				sal_Int32 nValue;
/*?*/ 				if(!(rVal >>= nValue))
/*?*/ 					return sal_False;
/*?*/ 
/*?*/ 				eSlant = (awt::FontSlant)nValue;
/*N*/ 			}
/*N*/ 			SetValue((USHORT)eSlant);
/*N*/ 		}
/*N*/ 	}
/*N*/ 	return sal_True;
/*N*/ }
// -----------------------------------------------------------------------

/*N*/ int SvxPostureItem::HasBoolValue() const
/*N*/ {
/*N*/ 	return sal_True;
/*N*/ }

// -----------------------------------------------------------------------

/*N*/ sal_Bool SvxPostureItem::GetBoolValue() const
/*N*/ {
/*N*/ 	return ( (FontItalic)GetValue() >= ITALIC_OBLIQUE );
/*N*/ }

// -----------------------------------------------------------------------

//STRIP001 void SvxPostureItem::SetBoolValue( sal_Bool bVal )
//STRIP001 {
//STRIP001 	SetValue( bVal ? ITALIC_NORMAL : ITALIC_NONE );
//STRIP001 }

// class SvxWeightItem ---------------------------------------------------

/*N*/ SvxWeightItem::SvxWeightItem( const FontWeight eWght, const USHORT nId ) :
/*N*/ 	SfxEnumItem( nId, eWght )
/*N*/ {
/*N*/ }



// -----------------------------------------------------------------------

/*N*/ int SvxWeightItem::HasBoolValue() const
/*N*/ {
/*N*/ 	return sal_True;
/*N*/ }

// -----------------------------------------------------------------------

/*N*/ sal_Bool SvxWeightItem::GetBoolValue() const
/*N*/ {
/*N*/ 	return  (FontWeight)GetValue() >= WEIGHT_BOLD;
/*N*/ }

// -----------------------------------------------------------------------

//STRIP001 void SvxWeightItem::SetBoolValue( sal_Bool bVal )
//STRIP001 {
//STRIP001 	SetValue( bVal ? WEIGHT_BOLD : WEIGHT_NORMAL );
//STRIP001 }

// -----------------------------------------------------------------------

/*?*/ USHORT SvxWeightItem::GetValueCount() const
/*?*/ {
/*?*/ DBG_ASSERT(0, "STRIP"); return 0;//STRIP001 	return WEIGHT_BLACK;	// WEIGHT_DONTKNOW geh"ort nicht dazu
/*?*/ }

// -----------------------------------------------------------------------

/*N*/ SfxPoolItem* SvxWeightItem::Clone( SfxItemPool * ) const
/*N*/ {
/*N*/ 	return new SvxWeightItem( *this );
/*N*/ }

// -----------------------------------------------------------------------

/*N*/ SvStream& SvxWeightItem::Store( SvStream& rStrm , USHORT nItemVersion ) const
/*N*/ {
/*N*/ 	rStrm << (BYTE)GetValue();
/*N*/ 	return rStrm;
/*N*/ }

// -----------------------------------------------------------------------

/*N*/ SfxPoolItem* SvxWeightItem::Create(SvStream& rStrm, USHORT) const
/*N*/ {
/*N*/ 	BYTE nWeight;
/*N*/ 	rStrm >> nWeight;
/*N*/ 	return new SvxWeightItem( (FontWeight)nWeight, Which() );
/*N*/ }

//------------------------------------------------------------------------

//STRIP001 SfxItemPresentation SvxWeightItem::GetPresentation
//STRIP001 (
//STRIP001 	SfxItemPresentation ePres,
//STRIP001 	SfxMapUnit			eCoreUnit,
//STRIP001 	SfxMapUnit			ePresUnit,
//STRIP001     XubString&          rText, const IntlWrapper *pIntl
//STRIP001 )	const
//STRIP001 {
//STRIP001 	switch ( ePres )
//STRIP001 	{
//STRIP001 		case SFX_ITEM_PRESENTATION_NONE:
//STRIP001 			rText.Erase();
//STRIP001 			return ePres;
//STRIP001 		case SFX_ITEM_PRESENTATION_NAMELESS:
//STRIP001 		case SFX_ITEM_PRESENTATION_COMPLETE:
//STRIP001 			rText = GetValueTextByPos( GetValue() );
//STRIP001 			return ePres;
//STRIP001 	}
//STRIP001 	return SFX_ITEM_PRESENTATION_NONE;
//STRIP001 }

// -----------------------------------------------------------------------

//STRIP001 XubString SvxWeightItem::GetValueTextByPos( USHORT nPos ) const
//STRIP001 {
//STRIP001 	DBG_ASSERT( nPos <= (USHORT)WEIGHT_BLACK, "enum overflow!" );
//STRIP001 	return SVX_RESSTR( RID_SVXITEMS_WEIGHT_BEGIN + nPos );
//STRIP001 }

/*-----------------13.03.98 14:18-------------------

--------------------------------------------------*/
/*N*/ sal_Bool SvxWeightItem::QueryValue( uno::Any& rVal, BYTE nMemberId ) const
/*N*/ {
/*N*/     sal_Bool bConvert = 0!=(nMemberId&CONVERT_TWIPS);
/*N*/     nMemberId &= ~CONVERT_TWIPS;
/*N*/ 	switch( nMemberId )
/*N*/ 	{
/*N*/ 		case MID_BOLD	:
/*?*/ 			rVal = Bool2Any(GetBoolValue());
/*N*/ 		break;
/*N*/ 		case MID_WEIGHT:
/*N*/ 		{
/*N*/ 			rVal <<= (float)( VCLUnoHelper::ConvertFontWeight( (FontWeight)GetValue() ) );
/*N*/ 		}
/*N*/ 		break;
/*N*/ 	}
/*N*/ 	return sal_True;
/*N*/ }
/*-----------------13.03.98 14:18-------------------

--------------------------------------------------*/
/*N*/ sal_Bool SvxWeightItem::PutValue( const uno::Any& rVal, BYTE nMemberId )
/*N*/ {
/*N*/     sal_Bool bConvert = 0!=(nMemberId&CONVERT_TWIPS);
/*N*/     nMemberId &= ~CONVERT_TWIPS;
/*N*/ 	switch( nMemberId )
/*N*/ 	{
/*N*/ 		case MID_BOLD	:
/*?*/ 			SetBoolValue(Any2Bool(rVal));
/*N*/ 		break;
/*N*/ 		case MID_WEIGHT:
/*N*/ 		{
/*N*/             double fValue;
/*N*/ 			if(!(rVal >>= fValue))
/*N*/ 			{
/*?*/ 				sal_Int32 nValue;
/*?*/ 				if(!(rVal >>= nValue))
/*?*/ 					return sal_False;
/*?*/ 				fValue = (float)nValue;
/*N*/ 			}
/*N*/ 			SetValue( VCLUnoHelper::ConvertFontWeight((float)fValue) );
/*N*/ 		}
/*N*/ 		break;
/*N*/ 	}
/*N*/ 	return sal_True;
/*N*/ }

// class SvxFontHeightItem -----------------------------------------------

/*N*/ SvxFontHeightItem::SvxFontHeightItem( const ULONG nSz,
/*N*/ 									  const USHORT nPrp,
/*N*/ 									  const USHORT nId ) :
/*N*/ 	SfxPoolItem( nId )
/*N*/ {
/*N*/ 	SetHeight( nSz,nPrp );	// mit den Prozenten rechnen
/*N*/ }

// -----------------------------------------------------------------------

/*N*/ SfxPoolItem* SvxFontHeightItem::Clone( SfxItemPool * ) const
/*N*/ {
/*N*/ 	return new SvxFontHeightItem( *this );
/*N*/ }

// -----------------------------------------------------------------------

/*N*/ SvStream& SvxFontHeightItem::Store( SvStream& rStrm , USHORT nItemVersion ) const
/*N*/ {
/*N*/ 	rStrm << (USHORT)GetHeight();
/*N*/ 
/*N*/ 	if( FONTHEIGHT_UNIT_VERSION <= nItemVersion )
/*N*/ 		rStrm << GetProp() << (USHORT)GetPropUnit();
/*N*/ 	else
/*N*/ 	{
/*N*/ 		// JP 30.06.98: beim Export in alte Versionen geht die relative
/*N*/ 		// Angabe verloren, wenn es keine Prozentuale ist
/*N*/ 		USHORT nProp = GetProp();
/*N*/ 		if( SFX_MAPUNIT_RELATIVE != GetPropUnit() )
/*N*/ 			nProp = 100;
/*N*/ 		rStrm << nProp;
/*N*/ 	}
/*N*/ 	return rStrm;
/*N*/ }

// -----------------------------------------------------------------------

/*N*/ SfxPoolItem* SvxFontHeightItem::Create( SvStream& rStrm,
/*N*/ 												 USHORT nVersion ) const
/*N*/ {
/*N*/ 	USHORT nsize, nprop = 0, nPropUnit = SFX_MAPUNIT_RELATIVE;
/*N*/ 
/*N*/ 	rStrm >> nsize;
/*N*/ 
/*N*/ 	if( FONTHEIGHT_16_VERSION <= nVersion )
/*N*/ 		rStrm >> nprop;
/*N*/ 	else
/*N*/ 	{
/*?*/ 		BYTE nP;
/*?*/ 		rStrm  >> nP;
/*?*/ 		nprop = (USHORT)nP;
/*N*/ 	}
/*N*/ 
/*N*/ 	if( FONTHEIGHT_UNIT_VERSION <= nVersion )
/*N*/ 		rStrm >> nPropUnit;
/*N*/ 
/*N*/ 	SvxFontHeightItem* pItem = new SvxFontHeightItem( nsize, 100, Which() );
/*N*/ 	pItem->SetProp( nprop, (SfxMapUnit)nPropUnit );
/*N*/ 	return pItem;
/*N*/ }

// -----------------------------------------------------------------------

/*N*/ int SvxFontHeightItem::operator==( const SfxPoolItem& rItem ) const
/*N*/ {
/*N*/ 	DBG_ASSERT( SfxPoolItem::operator==( rItem ), "unequal type" );
/*N*/ 	return GetHeight() == ((SvxFontHeightItem&)rItem).GetHeight() &&
/*N*/ 			GetProp() == ((SvxFontHeightItem&)rItem).GetProp() &&
/*N*/ 			GetPropUnit() == ((SvxFontHeightItem&)rItem).GetPropUnit();
/*N*/ }

/*-----------------13.03.98 14:53-------------------

--------------------------------------------------*/
/*N*/ sal_Bool SvxFontHeightItem::QueryValue( uno::Any& rVal, BYTE nMemberId ) const
/*N*/ {
/*N*/ 	//	In StarOne sind im uno::Any immer 1/100mm. Ueber die MemberId wird
/*N*/ 	//	gesteuert, ob der Wert im Item 1/100mm oder Twips sind.
/*N*/ 
/*N*/ 	sal_Bool bConvert = 0!=(nMemberId&CONVERT_TWIPS);
/*N*/ 	nMemberId &= ~CONVERT_TWIPS;
/*N*/ 	switch( nMemberId )
/*N*/ 	{
/*N*/ 		case MID_FONTHEIGHT:
/*N*/ 		{
/*N*/ 			//	Point (also Twips) sind gefragt,
/*N*/ 			//	also umrechnen, wenn CONVERT_TWIPS nicht gesetzt ist
/*N*/ 			if( bConvert )
/*N*/ 			{
/*N*/ 				long nTwips = bConvert ? nHeight : MM100_TO_TWIP(nHeight);
/*N*/ 				rVal <<= (float)( nTwips / 20.0 );
/*N*/ 			}
/*N*/ 			else
/*N*/ 			{
/*N*/ 				double fPoints = MM100_TO_TWIP((long)nHeight) / 20.0;
/*N*/                 float fRoundPoints =
/*N*/                     static_cast<float>(::rtl::math::round(fPoints, 1));
/*N*/ 				rVal <<= fRoundPoints;
/*N*/ 			}
/*N*/ 		}
/*N*/ 		break;
/*N*/ 		case MID_FONTHEIGHT_PROP:
/*N*/ 			rVal <<= (sal_Int16)(SFX_MAPUNIT_RELATIVE == ePropUnit ? nProp : 100);
/*N*/ 		break;
/*N*/ 		case MID_FONTHEIGHT_DIFF:
/*N*/ 		{
/*N*/ 			float fRet = (float)(short)nProp;
/*N*/ 			switch( ePropUnit )
/*N*/ 			{
/*N*/ 				case SFX_MAPUNIT_RELATIVE:
/*N*/ 					fRet = 0.;
/*N*/ 				break;
/*N*/ 				case SFX_MAPUNIT_100TH_MM:
/*?*/ 					fRet = MM100_TO_TWIP(fRet);
/*?*/ 					fRet /= 20.;
/*?*/ 				break;
/*?*/ 				case SFX_MAPUNIT_POINT:
/*?*/ 
/*?*/ 				break;
/*?*/ 				case SFX_MAPUNIT_TWIP:
/*?*/ 					fRet /= 20.;
/*N*/ 				break;
/*N*/ 			}
/*N*/ 			rVal <<= fRet;
/*N*/ 		}
/*N*/ 		break;
/*N*/ 	}
/*N*/ 	return sal_True;
/*N*/ }
/* -----------------01.07.98 13:43-------------------
 * 	Relative Abweichung aus der Hoehe herausrechnen
 * --------------------------------------------------*/
/*N*/ sal_uInt32 lcl_GetRealHeight_Impl(sal_uInt32 nHeight, sal_uInt16 nProp, SfxMapUnit eProp, sal_Bool bCoreInTwip)
/*N*/ {
/*N*/ 	sal_uInt32 nRet = nHeight;
/*N*/ 	short nDiff = 0;
/*N*/ 	switch( eProp )
/*N*/ 	{
/*N*/ 		case SFX_MAPUNIT_RELATIVE:
/*N*/ 			nRet *= 100;
/*N*/ 			nRet /= nProp;
/*N*/ 		break;
/*N*/ 		case SFX_MAPUNIT_POINT:
/*N*/ 		{
/*?*/ 			short nTemp = (short)nProp;
/*?*/ 			nDiff = nTemp * 20;
/*?*/ 			if(!bCoreInTwip)
/*?*/ 				nDiff = (short)TWIP_TO_MM100((long)(nDiff));
/*?*/ 		}
/*?*/ 		break;
/*?*/ 		case SFX_MAPUNIT_100TH_MM:
/*?*/ 			//dann ist die Core doch wohl auch in 1/100 mm
/*?*/ 			nDiff = (short)nProp;
/*?*/ 		break;
/*?*/ 		case SFX_MAPUNIT_TWIP:
/*?*/ 			// hier doch sicher TWIP
/*?*/ 			nDiff = ((short)nProp);
/*N*/ 		break;
/*N*/ 	}
/*N*/ 	nRet -= nDiff;
/*N*/ 
/*N*/ 	return nRet;
/*N*/ }

/*-----------------13.03.98 14:53-------------------

--------------------------------------------------*/
/*N*/ sal_Bool SvxFontHeightItem::PutValue( const uno::Any& rVal, BYTE nMemberId )
/*N*/ {
/*N*/ 	sal_Bool bConvert = 0!=(nMemberId&CONVERT_TWIPS);
/*N*/ 	nMemberId &= ~CONVERT_TWIPS;
/*N*/ 	switch( nMemberId )
/*N*/ 	{
/*N*/ 		case MID_FONTHEIGHT:
/*N*/ 		{
/*N*/ 			ePropUnit = SFX_MAPUNIT_RELATIVE;
/*N*/ 			nProp = 100;
/*N*/             double fPoint;
/*N*/ 			if(!(rVal >>= fPoint))
/*N*/ 			{
/*N*/ 				sal_Int32 nValue;
/*?*/                 if(!(rVal >>= nValue))
/*?*/ 					return sal_False;
/*?*/ 				fPoint = (float)nValue;
/*N*/ 			}
/*N*/             if(fPoint < 0. || fPoint > 10000.)
/*N*/ 					return sal_False;
/*N*/ 
/*N*/ 			nHeight = (long)( fPoint * 20.0 + 0.5 );		// Twips
/*N*/ 			if (!bConvert)
/*N*/ 				nHeight = TWIP_TO_MM100(nHeight);	// umrechnen, wenn das Item 1/100mm enthaelt
/*N*/ 		}
/*N*/ 		break;
/*N*/ 		case MID_FONTHEIGHT_PROP:
/*N*/ 		{
/*N*/ 			sal_Int16 nNew;
/*N*/ 			if(!(rVal >>= nNew))
/*N*/ 				return sal_True;
/*N*/ 
/*N*/ 			nHeight = lcl_GetRealHeight_Impl(nHeight, nProp, ePropUnit, bConvert);
/*N*/ 
/*N*/ 			nHeight *= nNew;
/*N*/ 			nHeight /= 100;
/*N*/ 			nProp = nNew;
/*N*/ 			ePropUnit = SFX_MAPUNIT_RELATIVE;
/*N*/ 		}
/*N*/ 		break;
/*N*/ 		case MID_FONTHEIGHT_DIFF:
/*N*/ 		{
/*?*/ 			nHeight = lcl_GetRealHeight_Impl(nHeight, nProp, ePropUnit, bConvert);
/*?*/ 			float fValue;
/*?*/ 			if(!(rVal >>= fValue))
/*?*/ 			{
/*?*/ 				sal_Int32 nValue;
/*?*/ 				if(!(rVal >>= nValue))
/*?*/ 					return sal_False;
/*?*/ 				fValue = (float)nValue;
/*?*/ 			}
/*?*/ 			sal_Int16 nCoreDiffValue = (sal_Int16)(fValue * 20.);
/*?*/ 			nHeight += bConvert ? nCoreDiffValue : TWIP_TO_MM100(nCoreDiffValue);
/*?*/ 			nProp = (sal_uInt16)((sal_Int16)fValue);
/*?*/ 			ePropUnit = SFX_MAPUNIT_POINT;
/*N*/ 		}
/*N*/ 		break;
/*N*/ 	}
/*N*/ 	return sal_True;
/*N*/ }

//------------------------------------------------------------------------

//STRIP001 SfxItemPresentation SvxFontHeightItem::GetPresentation
//STRIP001 (
//STRIP001 	SfxItemPresentation ePres,
//STRIP001 	SfxMapUnit			eCoreUnit,
//STRIP001 	SfxMapUnit			ePresUnit,
//STRIP001     XubString&          rText, const IntlWrapper *pIntl
//STRIP001 )	const
//STRIP001 {
//STRIP001 #ifndef SVX_LIGHT
//STRIP001 	switch ( ePres )
//STRIP001 	{
//STRIP001 		case SFX_ITEM_PRESENTATION_NONE:
//STRIP001 			rText.Erase();
//STRIP001 			return ePres;
//STRIP001 		case SFX_ITEM_PRESENTATION_NAMELESS:
//STRIP001 		case SFX_ITEM_PRESENTATION_COMPLETE:
//STRIP001 		{
//STRIP001 			if( SFX_MAPUNIT_RELATIVE != ePropUnit )
//STRIP001 			{
//STRIP001 				( rText = String::CreateFromInt32( (short)nProp ) ) +=
//STRIP001 						SVX_RESSTR( GetMetricId( ePropUnit ) );
//STRIP001 				if( 0 <= (short)nProp )
//STRIP001 					rText.Insert( sal_Unicode('+'), 0 );
//STRIP001 			}
//STRIP001 			else if( 100 == nProp )
//STRIP001 			{
//STRIP001 				rText = GetMetricText( (long)nHeight,
//STRIP001                                         eCoreUnit, SFX_MAPUNIT_POINT, pIntl );
//STRIP001 				rText += SVX_RESSTR(GetMetricId(SFX_MAPUNIT_POINT));
//STRIP001 			}
//STRIP001 			else
//STRIP001 				( rText = String::CreateFromInt32( nProp )) += sal_Unicode('%');
//STRIP001 			return ePres;
//STRIP001 		}
//STRIP001 	}
//STRIP001 #endif
//STRIP001 	return SFX_ITEM_PRESENTATION_NONE;
//STRIP001 }

// -----------------------------------------------------------------------

/*N*/ USHORT SvxFontHeightItem::GetVersion(USHORT nFileVersion) const
/*N*/ {
/*N*/ 	return (nFileVersion <= SOFFICE_FILEFORMAT_40)
/*N*/ 			   ? FONTHEIGHT_16_VERSION
/*N*/ 			   : FONTHEIGHT_UNIT_VERSION;
/*N*/ }

// -----------------------------------------------------------------------

//STRIP001 int SvxFontHeightItem::ScaleMetrics( long nMult, long nDiv )
//STRIP001 {
//STRIP001 	nHeight = (sal_uInt32)Scale( nHeight, nMult, nDiv );
//STRIP001 	return 1;
//STRIP001 }

// -----------------------------------------------------------------------

//STRIP001 int SvxFontHeightItem::HasMetrics() const
//STRIP001 {
//STRIP001 	return 1;
//STRIP001 }

/*N*/ void SvxFontHeightItem::SetHeight( sal_uInt32 nNewHeight, const USHORT nNewProp,
/*N*/ 									SfxMapUnit eUnit )
/*N*/ {
/*N*/ 	DBG_ASSERT( GetRefCount() == 0, "SetValue() with pooled item" );
/*N*/ 
/*N*/ #ifndef SVX_LIGHT
/*N*/ 	if( SFX_MAPUNIT_RELATIVE != eUnit )
nHeight = nNewHeight + ::binfilter::ItemToControl( (short)nNewProp, eUnit,//STRIP008 /*N*/ 		nHeight = nNewHeight + ::ItemToControl( (short)nNewProp, eUnit,
/*N*/ 												SFX_FUNIT_TWIP );
/*N*/ 	else
/*N*/ #endif // !SVX_LIGHT
/*N*/ 	if( 100 != nNewProp )
/*N*/ 		nHeight = sal_uInt32(( nNewHeight * nNewProp ) / 100 );
/*N*/ 	else
/*N*/ 		nHeight = nNewHeight;
/*N*/ 
/*N*/ 	nProp = nNewProp;
/*N*/ 	ePropUnit = eUnit;
/*N*/ }

//STRIP001 void SvxFontHeightItem::SetHeight( sal_uInt32 nNewHeight, USHORT nNewProp,
//STRIP001 								 SfxMapUnit eMetric, SfxMapUnit eCoreMetric )
//STRIP001 {
//STRIP001 	DBG_ASSERT( GetRefCount() == 0, "SetValue() with pooled item" );
//STRIP001 
//STRIP001 #ifndef SVX_LIGHT
//STRIP001 	if( SFX_MAPUNIT_RELATIVE != eMetric )
//STRIP001 		nHeight = nNewHeight +
//STRIP001 				::ControlToItem( ::ItemToControl((short)nNewProp, eMetric,
//STRIP001 										SFX_FUNIT_TWIP ), SFX_FUNIT_TWIP,
//STRIP001 										eCoreMetric );
//STRIP001 	else
//STRIP001 #endif // !SVX_LIGHT
//STRIP001 	if( 100 != nNewProp )
//STRIP001 		nHeight = sal_uInt32(( nNewHeight * nNewProp ) / 100 );
//STRIP001 	else
//STRIP001 		nHeight = nNewHeight;
//STRIP001 
//STRIP001 	nProp = nNewProp;
//STRIP001 	ePropUnit = eMetric;
//STRIP001 }

// class SvxFontWidthItem -----------------------------------------------

/*N*/ SvxFontWidthItem::SvxFontWidthItem( const USHORT nSz, const USHORT nPrp, const USHORT nId ) :
/*N*/ 	SfxPoolItem( nId )
/*N*/ {
/*N*/ 	nWidth = nSz;
/*N*/ 	nProp = nPrp;
/*N*/ }

// -----------------------------------------------------------------------

//STRIP001 SfxPoolItem* SvxFontWidthItem::Clone( SfxItemPool * ) const
//STRIP001 {
//STRIP001 	return new SvxFontWidthItem( *this );
//STRIP001 }

// -----------------------------------------------------------------------

//STRIP001 SvStream& SvxFontWidthItem::Store( SvStream& rStrm , USHORT nItemVersion ) const
//STRIP001 {
//STRIP001 	rStrm << GetWidth() << GetProp();
//STRIP001 	return rStrm;
//STRIP001 }

// -----------------------------------------------------------------------

//STRIP001 int SvxFontWidthItem::ScaleMetrics( long nMult, long nDiv )
//STRIP001 {
//STRIP001 	nWidth = (USHORT)Scale( nWidth, nMult, nDiv );
//STRIP001 	return 1;
//STRIP001 }

// -----------------------------------------------------------------------

//STRIP001 int SvxFontWidthItem::HasMetrics() const
//STRIP001 {
//STRIP001 	return 1;
//STRIP001 }

// -----------------------------------------------------------------------

//STRIP001 SfxPoolItem* SvxFontWidthItem::Create( SvStream& rStrm,
//STRIP001 												 USHORT nVersion ) const
//STRIP001 {
//STRIP001 	USHORT nS;
//STRIP001 	USHORT nP;
//STRIP001 
//STRIP001 	rStrm >> nS;
//STRIP001 	rStrm >> nP;
//STRIP001 	SvxFontWidthItem* pItem = new SvxFontWidthItem( 0, nP, Which() );
//STRIP001 	pItem->SetWidthValue( nS );
//STRIP001 	return pItem;
//STRIP001 }

// -----------------------------------------------------------------------

//STRIP001 int SvxFontWidthItem::operator==( const SfxPoolItem& rItem ) const
//STRIP001 {
//STRIP001 	DBG_ASSERT( SfxPoolItem::operator==( rItem ), "unequal type" );
//STRIP001 	return GetWidth() == ((SvxFontWidthItem&)rItem).GetWidth() &&
//STRIP001 			GetProp() == ((SvxFontWidthItem&)rItem).GetProp();
//STRIP001 }

/*-----------------13.03.98 16:03-------------------

--------------------------------------------------*/
//STRIP001 sal_Bool SvxFontWidthItem::QueryValue( uno::Any& rVal, BYTE nMemberId ) const
//STRIP001 {
//STRIP001     sal_Bool bConvert = 0!=(nMemberId&CONVERT_TWIPS);
//STRIP001     nMemberId &= ~CONVERT_TWIPS;
//STRIP001 	switch(nMemberId)
//STRIP001 	{
//STRIP001 		case MID_FONTWIDTH:
//STRIP001 			rVal <<= (sal_Int16)(nWidth);
//STRIP001 		break;
//STRIP001 		case MID_FONTWIDTH_PROP:
//STRIP001 			rVal <<= (sal_Int16)(nProp);
//STRIP001 		break;
//STRIP001 	}
//STRIP001 	return sal_True;
//STRIP001 }
/*-----------------13.03.98 16:03-------------------

--------------------------------------------------*/
//STRIP001 sal_Bool SvxFontWidthItem::PutValue( const uno::Any& rVal, BYTE nMemberId )
//STRIP001 {
//STRIP001     sal_Bool bConvert = 0!=(nMemberId&CONVERT_TWIPS);
//STRIP001     nMemberId &= ~CONVERT_TWIPS;
//STRIP001 	sal_Int16 nVal;
//STRIP001 	if(!(rVal >>= nVal))
//STRIP001 		return sal_False;
//STRIP001 
//STRIP001 	switch(nMemberId)
//STRIP001 	{
//STRIP001 		case MID_FONTWIDTH:
//STRIP001 			nProp = nVal;
//STRIP001 		break;
//STRIP001 		case MID_FONTWIDTH_PROP:
//STRIP001 			nWidth = nVal;
//STRIP001 		break;
//STRIP001 	}
//STRIP001 	return sal_True;
//STRIP001 }

//------------------------------------------------------------------------

//STRIP001 SfxItemPresentation SvxFontWidthItem::GetPresentation
//STRIP001 (
//STRIP001 	SfxItemPresentation ePres,
//STRIP001 	SfxMapUnit			eCoreUnit,
//STRIP001 	SfxMapUnit			ePresUnit,
//STRIP001     XubString&          rText, const IntlWrapper *pIntl
//STRIP001 )	const
//STRIP001 {
//STRIP001 #ifndef SVX_LIGHT
//STRIP001 	switch ( ePres )
//STRIP001 	{
//STRIP001 		case SFX_ITEM_PRESENTATION_NONE:
//STRIP001 			rText.Erase();
//STRIP001 			return ePres;
//STRIP001 		case SFX_ITEM_PRESENTATION_NAMELESS:
//STRIP001 		case SFX_ITEM_PRESENTATION_COMPLETE:
//STRIP001 		{
//STRIP001 			if ( 100 == nProp )
//STRIP001 			{
//STRIP001 				rText = GetMetricText( (long)nWidth,
//STRIP001                                         eCoreUnit, SFX_MAPUNIT_POINT, pIntl );
//STRIP001 				rText += SVX_RESSTR(GetMetricId(SFX_MAPUNIT_POINT));
//STRIP001 			}
//STRIP001 			else
//STRIP001 				( rText = String::CreateFromInt32( nProp )) += sal_Unicode('%');
//STRIP001 			return ePres;
//STRIP001 		}
//STRIP001 	}
//STRIP001 #endif
//STRIP001 	return SFX_ITEM_PRESENTATION_NONE;
//STRIP001 }

// class SvxUnderlineItem ------------------------------------------------

/*N*/ SvxUnderlineItem::SvxUnderlineItem( const FontUnderline eSt, const USHORT nId )
/*N*/ 	: SfxEnumItem( nId, eSt ), mColor( COL_TRANSPARENT )
/*N*/ {
/*N*/ }

// -----------------------------------------------------------------------

/*N*/ int SvxUnderlineItem::HasBoolValue() const
/*N*/ {
/*N*/ 	return sal_True;
/*N*/ }

// -----------------------------------------------------------------------

/*N*/ sal_Bool SvxUnderlineItem::GetBoolValue() const
/*N*/ {
/*N*/ 	return  (FontUnderline)GetValue() != UNDERLINE_NONE;
/*N*/ }

// -----------------------------------------------------------------------

//STRIP001 void SvxUnderlineItem::SetBoolValue( sal_Bool bVal )
//STRIP001 {
//STRIP001 	SetValue( bVal ? UNDERLINE_SINGLE : UNDERLINE_NONE );
//STRIP001 }

// -----------------------------------------------------------------------

/*N*/ SfxPoolItem* SvxUnderlineItem::Clone( SfxItemPool * ) const
/*N*/ {
/*N*/ 	SvxUnderlineItem* pNew = new SvxUnderlineItem( *this );
/*N*/ 	pNew->SetColor( GetColor() );
/*N*/ 	return pNew;
/*N*/ }

// -----------------------------------------------------------------------

/*N*/ USHORT SvxUnderlineItem::GetValueCount() const
/*N*/ {
/*N*/ 	return UNDERLINE_DOTTED + 1;	// auch UNDERLINE_NONE geh"ort dazu
/*N*/ }

// -----------------------------------------------------------------------

/*N*/ SvStream& SvxUnderlineItem::Store( SvStream& rStrm , USHORT nItemVersion ) const
/*N*/ {
/*N*/ 	rStrm << (BYTE)GetValue();
/*N*/ 	return rStrm;
/*N*/ }

// -----------------------------------------------------------------------

/*N*/ SfxPoolItem* SvxUnderlineItem::Create(SvStream& rStrm, USHORT) const
/*N*/ {
/*N*/ 	BYTE nState;
/*N*/ 	rStrm >> nState;
/*N*/ 	return new SvxUnderlineItem(  (FontUnderline)nState, Which() );
/*N*/ }

//------------------------------------------------------------------------

//STRIP001 SfxItemPresentation SvxUnderlineItem::GetPresentation
//STRIP001 (
//STRIP001 	SfxItemPresentation ePres,
//STRIP001 	SfxMapUnit			eCoreUnit,
//STRIP001 	SfxMapUnit			ePresUnit,
//STRIP001     XubString&          rText, const IntlWrapper *pIntl
//STRIP001 )	const
//STRIP001 {
//STRIP001 #ifndef SVX_LIGHT
//STRIP001 	switch ( ePres )
//STRIP001 	{
//STRIP001 		case SFX_ITEM_PRESENTATION_NONE:
//STRIP001 			rText.Erase();
//STRIP001 			return ePres;
//STRIP001 		case SFX_ITEM_PRESENTATION_NAMELESS:
//STRIP001 		case SFX_ITEM_PRESENTATION_COMPLETE:
//STRIP001 			rText = GetValueTextByPos( GetValue() );
//STRIP001 			if( !mColor.GetTransparency() )
//STRIP001 				( rText += cpDelim ) += ::GetColorString( mColor );
//STRIP001 			return ePres;
//STRIP001 	}
//STRIP001 #endif
//STRIP001 	return SFX_ITEM_PRESENTATION_NONE;
//STRIP001 }

// -----------------------------------------------------------------------

//STRIP001 XubString SvxUnderlineItem::GetValueTextByPos( USHORT nPos ) const
//STRIP001 {
//STRIP001 	DBG_ASSERT( nPos <= (USHORT)UNDERLINE_BOLDWAVE, "enum overflow!" );
//STRIP001 	return SVX_RESSTR( RID_SVXITEMS_UL_BEGIN + nPos );
//STRIP001 }

/*-----------------13.03.98 16:25-------------------

--------------------------------------------------*/
/*N*/ sal_Bool SvxUnderlineItem::QueryValue( uno::Any& rVal, BYTE nMemberId ) const
/*N*/ {
/*N*/     sal_Bool bConvert = 0!=(nMemberId&CONVERT_TWIPS);
/*N*/     nMemberId &= ~CONVERT_TWIPS;
/*N*/ 	switch(nMemberId)
/*N*/ 	{
/*N*/ 	case MID_UNDERLINED:
/*?*/ 		rVal = Bool2Any(GetBoolValue());
/*?*/ 		break;
/*N*/ 	case MID_UNDERLINE:
/*N*/ 		rVal <<= (sal_Int16)(GetValue());
/*N*/ 		break;
/*N*/ 	case MID_UL_COLOR:
/*N*/ 		rVal <<= (sal_Int32)( mColor.GetColor() );
/*N*/ 		break;
/*N*/ 	case MID_UL_HASCOLOR:
/*N*/ 		rVal = Bool2Any( !mColor.GetTransparency() );
/*N*/ 		break;
/*N*/ 	}
/*N*/ 	return sal_True;
/*N*/ 
/*N*/ }
/*-----------------13.03.98 16:28-------------------

--------------------------------------------------*/
/*N*/ sal_Bool SvxUnderlineItem::PutValue( const uno::Any& rVal, BYTE nMemberId )
/*N*/ {
/*N*/     sal_Bool bConvert = 0!=(nMemberId&CONVERT_TWIPS);
/*N*/     nMemberId &= ~CONVERT_TWIPS;
/*N*/ 	sal_Bool bRet = sal_True;
/*N*/ 	switch(nMemberId)
/*N*/ 	{
/*N*/ 	case MID_UNDERLINED:
/*?*/ 		SetBoolValue(Any2Bool(rVal));
/*N*/ 	break;
/*N*/ 	case MID_UNDERLINE:
/*N*/ 	{
/*N*/ 		sal_Int32 nValue;
/*N*/ 		if(!(rVal >>= nValue))
/*N*/ 			bRet = sal_False;
/*N*/ 		else
/*N*/ 			SetValue((sal_Int16)nValue);
/*N*/ 	}
/*N*/ 	break;
/*N*/ 	case MID_UL_COLOR:
/*N*/ 	{
/*?*/ 		sal_Int32 nCol;
/*?*/ 		if( !( rVal >>= nCol ) )
/*?*/ 			bRet = sal_False;
/*?*/ 		else
/*?*/ 		{
/*?*/ 			// Keep transparence, because it contains the information
/*?*/ 			// whether the font color or the stored color should be used
/*?*/ 			sal_uInt8 nTrans = mColor.GetTransparency();
/*?*/ 			mColor = Color( nCol );
/*?*/ 			mColor.SetTransparency( nTrans );
/*?*/ 		}
/*N*/ 	}
/*N*/ 	break;
/*N*/ 	case MID_UL_HASCOLOR:
/*N*/ 		mColor.SetTransparency( Any2Bool( rVal ) ? 0 : 0xff );
/*N*/ 	break;
/*N*/ 	}
/*N*/ 	return bRet;
/*N*/ }

/*N*/ int SvxUnderlineItem::operator==( const SfxPoolItem& rItem ) const
/*N*/ {
/*N*/ 	DBG_ASSERT( SfxPoolItem::operator==( rItem ), "unequal type" );
/*N*/ 	return SfxEnumItem::operator==( rItem ) &&
/*N*/ 		   GetColor() == ((SvxUnderlineItem&)rItem).GetColor();
/*N*/ }

// class SvxCrossedOutItem -----------------------------------------------

/*N*/ SvxCrossedOutItem::SvxCrossedOutItem( const FontStrikeout eSt, const USHORT nId )
/*N*/ 	: SfxEnumItem( nId, eSt )
/*N*/ {
/*N*/ }

// -----------------------------------------------------------------------

//STRIP001 int SvxCrossedOutItem::HasBoolValue() const
//STRIP001 {
//STRIP001 	return sal_True;
//STRIP001 }

// -----------------------------------------------------------------------

//STRIP001 sal_Bool SvxCrossedOutItem::GetBoolValue() const
//STRIP001 {
//STRIP001 	return (FontStrikeout)GetValue() != STRIKEOUT_NONE;
//STRIP001 }

// -----------------------------------------------------------------------

//STRIP001 void SvxCrossedOutItem::SetBoolValue( sal_Bool bVal )
//STRIP001 {
//STRIP001 	SetValue( bVal ? STRIKEOUT_SINGLE : STRIKEOUT_NONE );
//STRIP001 }

// -----------------------------------------------------------------------

/*N*/ USHORT SvxCrossedOutItem::GetValueCount() const
/*N*/ {
/*N*/ 	return STRIKEOUT_DOUBLE + 1;	// auch STRIKEOUT_NONE geh"ort dazu
/*N*/ }

// -----------------------------------------------------------------------

/*N*/ SfxPoolItem* SvxCrossedOutItem::Clone( SfxItemPool * ) const
/*N*/ {
/*N*/ 	return new SvxCrossedOutItem( *this );
/*N*/ }

// -----------------------------------------------------------------------

/*N*/ SvStream& SvxCrossedOutItem::Store( SvStream& rStrm , USHORT nItemVersion ) const
/*N*/ {
/*N*/ 	rStrm << (BYTE)GetValue();
/*N*/ 	return rStrm;
/*N*/ }

// -----------------------------------------------------------------------

/*N*/ SfxPoolItem* SvxCrossedOutItem::Create(SvStream& rStrm, USHORT) const
/*N*/ {
/*N*/ 	BYTE eCross;
/*N*/ 	rStrm >> eCross;
/*N*/ 	return new SvxCrossedOutItem(  (FontStrikeout)eCross, Which() );
/*N*/ }

//------------------------------------------------------------------------

//STRIP001 SfxItemPresentation SvxCrossedOutItem::GetPresentation
//STRIP001 (
//STRIP001 	SfxItemPresentation ePres,
//STRIP001 	SfxMapUnit			eCoreUnit,
//STRIP001 	SfxMapUnit			ePresUnit,
//STRIP001     XubString&          rText, const IntlWrapper *pIntl
//STRIP001 )	const
//STRIP001 {
//STRIP001 	switch ( ePres )
//STRIP001 	{
//STRIP001 		case SFX_ITEM_PRESENTATION_NONE:
//STRIP001 			rText.Erase();
//STRIP001 			return ePres;
//STRIP001 		case SFX_ITEM_PRESENTATION_NAMELESS:
//STRIP001 		case SFX_ITEM_PRESENTATION_COMPLETE:
//STRIP001 			rText = GetValueTextByPos( GetValue() );
//STRIP001 			return ePres;
//STRIP001 	}
//STRIP001 	return SFX_ITEM_PRESENTATION_NONE;
//STRIP001 }

// -----------------------------------------------------------------------

//STRIP001 XubString SvxCrossedOutItem::GetValueTextByPos( USHORT nPos ) const
//STRIP001 {
//STRIP001 	DBG_ASSERT( nPos <= (USHORT)STRIKEOUT_X, "enum overflow!" );
//STRIP001 	return SVX_RESSTR( RID_SVXITEMS_STRIKEOUT_BEGIN + nPos );
//STRIP001 }

/*-----------------13.03.98 16:28-------------------

--------------------------------------------------*/
/*N*/ sal_Bool SvxCrossedOutItem::QueryValue( uno::Any& rVal, BYTE nMemberId ) const
/*N*/ {
/*N*/     sal_Bool bConvert = 0!=(nMemberId&CONVERT_TWIPS);
/*N*/     nMemberId &= ~CONVERT_TWIPS;
/*N*/ 	switch(nMemberId)
/*N*/ 	{
/*N*/ 		case MID_CROSSED_OUT:
/*?*/ 			rVal = Bool2Any(GetBoolValue());
/*N*/ 		break;
/*N*/ 		case MID_CROSS_OUT:
/*N*/ 			rVal <<= (sal_Int16)(GetValue());
/*N*/ 		break;
/*N*/ 	}
/*N*/ 	return sal_True;
/*N*/ }
/*-----------------13.03.98 16:29-------------------

--------------------------------------------------*/
/*N*/ sal_Bool SvxCrossedOutItem::PutValue( const uno::Any& rVal, BYTE nMemberId )
/*N*/ {
/*N*/     sal_Bool bConvert = 0!=(nMemberId&CONVERT_TWIPS);
/*N*/     nMemberId &= ~CONVERT_TWIPS;
/*N*/ 	switch(nMemberId)
/*N*/ 	{
/*N*/ 		case MID_CROSSED_OUT:
/*?*/ 			SetBoolValue(Any2Bool(rVal));
/*N*/ 		break;
/*N*/ 		case MID_CROSS_OUT:
/*N*/ 		{
/*N*/ 			sal_Int32 nValue;
/*N*/ 			if(!(rVal >>= nValue))
/*N*/ 				return sal_False;
/*N*/ 			SetValue((sal_Int16)nValue);
/*N*/ 		}
/*N*/ 		break;
/*N*/ 	}
/*N*/ 	return sal_True;
/*N*/ }
// class SvxShadowedItem -------------------------------------------------

/*N*/ SvxShadowedItem::SvxShadowedItem( const sal_Bool bShadowed, const USHORT nId ) :
/*N*/ 	SfxBoolItem( nId, bShadowed )
/*N*/ {
/*N*/ }

// -----------------------------------------------------------------------

/*N*/ SfxPoolItem* SvxShadowedItem::Clone( SfxItemPool * ) const
/*N*/ {
/*N*/ 	return new SvxShadowedItem( *this );
/*N*/ }

// -----------------------------------------------------------------------

/*N*/ SvStream& SvxShadowedItem::Store( SvStream& rStrm , USHORT nItemVersion ) const
/*N*/ {
/*N*/ 	rStrm << (BYTE) GetValue();
/*N*/ 	return rStrm;
/*N*/ }

// -----------------------------------------------------------------------

/*N*/ SfxPoolItem* SvxShadowedItem::Create(SvStream& rStrm, USHORT) const
/*N*/ {
/*N*/ 	BYTE nState;
/*N*/ 	rStrm >> nState;
/*N*/ 	return new SvxShadowedItem( nState, Which() );
/*N*/ }

//------------------------------------------------------------------------

//STRIP001 SfxItemPresentation SvxShadowedItem::GetPresentation
//STRIP001 (
//STRIP001 	SfxItemPresentation ePres,
//STRIP001 	SfxMapUnit			eCoreUnit,
//STRIP001 	SfxMapUnit			ePresUnit,
//STRIP001     XubString&          rText, const IntlWrapper *pIntl
//STRIP001 )	const
//STRIP001 {
//STRIP001 	switch ( ePres )
//STRIP001 	{
//STRIP001 		case SFX_ITEM_PRESENTATION_NONE:
//STRIP001 			rText.Erase();
//STRIP001 			return ePres;
//STRIP001 		case SFX_ITEM_PRESENTATION_NAMELESS:
//STRIP001 		case SFX_ITEM_PRESENTATION_COMPLETE:
//STRIP001 		{
//STRIP001 			USHORT nId = RID_SVXITEMS_SHADOWED_FALSE;
//STRIP001 
//STRIP001 			if ( GetValue() )
//STRIP001 				nId = RID_SVXITEMS_SHADOWED_TRUE;
//STRIP001 			rText = SVX_RESSTR(nId);
//STRIP001 			return ePres;
//STRIP001 		}
//STRIP001 	}
//STRIP001 	return SFX_ITEM_PRESENTATION_NONE;
//STRIP001 }

// class SvxAutoKernItem -------------------------------------------------

/*N*/ SvxAutoKernItem::SvxAutoKernItem( const sal_Bool bAutoKern, const USHORT nId ) :
/*N*/ 	SfxBoolItem( nId, bAutoKern )
/*N*/ {
/*N*/ }

// -----------------------------------------------------------------------

/*N*/ SfxPoolItem* SvxAutoKernItem::Clone( SfxItemPool * ) const
/*N*/ {
/*N*/ 	return new SvxAutoKernItem( *this );
/*N*/ }

// -----------------------------------------------------------------------

/*N*/ SvStream& SvxAutoKernItem::Store( SvStream& rStrm , USHORT nItemVersion ) const
/*N*/ {
/*N*/ 	rStrm << (BYTE) GetValue();
/*N*/ 	return rStrm;
/*N*/ }

// -----------------------------------------------------------------------

/*N*/ SfxPoolItem* SvxAutoKernItem::Create(SvStream& rStrm, USHORT) const
/*N*/ {
/*N*/ 	BYTE nState;
/*N*/ 	rStrm >> nState;
/*N*/ 	return new SvxAutoKernItem( nState, Which() );
/*N*/ }

//------------------------------------------------------------------------

//STRIP001 SfxItemPresentation SvxAutoKernItem::GetPresentation
//STRIP001 (
//STRIP001 	SfxItemPresentation ePres,
//STRIP001 	SfxMapUnit			eCoreUnit,
//STRIP001 	SfxMapUnit			ePresUnit,
//STRIP001     XubString&          rText, const IntlWrapper *pIntl
//STRIP001 )	const
//STRIP001 {
//STRIP001 	switch ( ePres )
//STRIP001 	{
//STRIP001 		case SFX_ITEM_PRESENTATION_NONE:
//STRIP001 			rText.Erase();
//STRIP001 			return ePres;
//STRIP001 		case SFX_ITEM_PRESENTATION_NAMELESS:
//STRIP001 		case SFX_ITEM_PRESENTATION_COMPLETE:
//STRIP001 		{
//STRIP001 			USHORT nId = RID_SVXITEMS_AUTOKERN_FALSE;
//STRIP001 
//STRIP001 			if ( GetValue() )
//STRIP001 				nId = RID_SVXITEMS_AUTOKERN_TRUE;
//STRIP001 			rText = SVX_RESSTR(nId);
//STRIP001 			return ePres;
//STRIP001 		}
//STRIP001 	}
//STRIP001 	return SFX_ITEM_PRESENTATION_NONE;
//STRIP001 }

// class SvxWordLineModeItem ---------------------------------------------

/*N*/ SvxWordLineModeItem::SvxWordLineModeItem( const sal_Bool bWordLineMode,
/*N*/ 										  const USHORT nId ) :
/*N*/ 	SfxBoolItem( nId, bWordLineMode )
/*N*/ {
/*N*/ }

// -----------------------------------------------------------------------

/*N*/ SfxPoolItem* SvxWordLineModeItem::Clone( SfxItemPool * ) const
/*N*/ {
/*N*/ 	return new SvxWordLineModeItem( *this );
/*N*/ }

// -----------------------------------------------------------------------

/*N*/ SvStream& SvxWordLineModeItem::Store( SvStream& rStrm , USHORT nItemVersion ) const
/*N*/ {
/*N*/ 	rStrm << (sal_Bool) GetValue();
/*N*/ 	return rStrm;
/*N*/ }

// -----------------------------------------------------------------------

/*N*/ SfxPoolItem* SvxWordLineModeItem::Create(SvStream& rStrm, USHORT) const
/*N*/ {
/*N*/ 	sal_Bool bValue;
/*N*/ 	rStrm >> bValue;
/*N*/ 	return new SvxWordLineModeItem( bValue, Which() );
/*N*/ }

//------------------------------------------------------------------------

//STRIP001 SfxItemPresentation SvxWordLineModeItem::GetPresentation
//STRIP001 (
//STRIP001 	SfxItemPresentation ePres,
//STRIP001 	SfxMapUnit			eCoreUnit,
//STRIP001 	SfxMapUnit			ePresUnit,
//STRIP001     XubString&          rText, const IntlWrapper *pIntl
//STRIP001 )	const
//STRIP001 {
//STRIP001 	switch ( ePres )
//STRIP001 	{
//STRIP001 		case SFX_ITEM_PRESENTATION_NONE:
//STRIP001 			rText.Erase();
//STRIP001 			return ePres;
//STRIP001 		case SFX_ITEM_PRESENTATION_NAMELESS:
//STRIP001 		case SFX_ITEM_PRESENTATION_COMPLETE:
//STRIP001 		{
//STRIP001 			USHORT nId = RID_SVXITEMS_WORDLINE_FALSE;
//STRIP001 
//STRIP001 			if ( GetValue() )
//STRIP001 				nId = RID_SVXITEMS_WORDLINE_TRUE;
//STRIP001 			rText = SVX_RESSTR(nId);
//STRIP001 			return ePres;
//STRIP001 		}
//STRIP001 	}
//STRIP001 	return SFX_ITEM_PRESENTATION_NONE;
//STRIP001 }

// class SvxContourItem --------------------------------------------------

/*N*/ SvxContourItem::SvxContourItem( const sal_Bool bContoured, const USHORT nId ) :
/*N*/ 	SfxBoolItem( nId, bContoured )
/*N*/ {
/*N*/ }

// -----------------------------------------------------------------------

/*N*/ SfxPoolItem* SvxContourItem::Clone( SfxItemPool * ) const
/*N*/ {
/*N*/ 	return new SvxContourItem( *this );
/*N*/ }

// -----------------------------------------------------------------------

/*N*/ SvStream& SvxContourItem::Store( SvStream& rStrm , USHORT nItemVersion ) const
/*N*/ {
/*N*/ 	rStrm << (sal_Bool) GetValue();
/*N*/ 	return rStrm;
/*N*/ }

// -----------------------------------------------------------------------

/*N*/ SfxPoolItem* SvxContourItem::Create(SvStream& rStrm, USHORT) const
/*N*/ {
/*N*/ 	sal_Bool bValue;
/*N*/ 	rStrm >> bValue;
/*N*/ 	return new SvxContourItem( bValue, Which() );
/*N*/ }

//------------------------------------------------------------------------

//STRIP001 SfxItemPresentation SvxContourItem::GetPresentation
//STRIP001 (
//STRIP001 	SfxItemPresentation ePres,
//STRIP001 	SfxMapUnit			eCoreUnit,
//STRIP001 	SfxMapUnit			ePresUnit,
//STRIP001     XubString&          rText, const IntlWrapper *pIntl
//STRIP001 )	const
//STRIP001 {
//STRIP001 	switch ( ePres )
//STRIP001 	{
//STRIP001 		case SFX_ITEM_PRESENTATION_NONE:
//STRIP001 			rText.Erase();
//STRIP001 			return ePres;
//STRIP001 		case SFX_ITEM_PRESENTATION_NAMELESS:
//STRIP001 		case SFX_ITEM_PRESENTATION_COMPLETE:
//STRIP001 		{
//STRIP001 			USHORT nId = RID_SVXITEMS_CONTOUR_FALSE;
//STRIP001 
//STRIP001 			if ( GetValue() )
//STRIP001 				nId = RID_SVXITEMS_CONTOUR_TRUE;
//STRIP001 			rText = SVX_RESSTR(nId);
//STRIP001 			return ePres;
//STRIP001 		}
//STRIP001 	}
//STRIP001 	return SFX_ITEM_PRESENTATION_NONE;
//STRIP001 }

// class SvxPropSizeItem -------------------------------------------------

/*N*/ SvxPropSizeItem::SvxPropSizeItem( const USHORT nPercent, const USHORT nId ) :
/*N*/ 	SfxUInt16Item( nId, nPercent )
/*N*/ {
/*N*/ }

// -----------------------------------------------------------------------

/*N*/ SfxPoolItem* SvxPropSizeItem::Clone( SfxItemPool * ) const
/*N*/ {
/*N*/ 	return new SvxPropSizeItem( *this );
/*N*/ }

// -----------------------------------------------------------------------

//STRIP001 SvStream& SvxPropSizeItem::Store( SvStream& rStrm , USHORT nItemVersion ) const
//STRIP001 {
//STRIP001 	rStrm << (USHORT) GetValue();
//STRIP001 	return rStrm;
//STRIP001 }

// -----------------------------------------------------------------------

/*N*/ SfxPoolItem* SvxPropSizeItem::Create(SvStream& rStrm, USHORT) const
/*N*/ {
/*N*/ 	USHORT nSize;
/*N*/ 	rStrm >> nSize;
/*N*/ 	return new SvxPropSizeItem( nSize, Which() );
/*N*/ }

//------------------------------------------------------------------------

//STRIP001 SfxItemPresentation SvxPropSizeItem::GetPresentation
//STRIP001 (
//STRIP001 	SfxItemPresentation ePres,
//STRIP001 	SfxMapUnit			eCoreUnit,
//STRIP001 	SfxMapUnit			ePresUnit,
//STRIP001     XubString&          rText, const IntlWrapper *pIntl
//STRIP001 )	const
//STRIP001 {
//STRIP001 	rText.Erase();
//STRIP001 	return SFX_ITEM_PRESENTATION_NONE;
//STRIP001 }

// class SvxColorItem ----------------------------------------------------

/*N*/ SvxColorItem::SvxColorItem( const USHORT nId ) :
/*N*/ 	SfxPoolItem( nId ),
/*N*/ 	mColor( COL_BLACK )
/*N*/ {
/*N*/ }

// -----------------------------------------------------------------------

/*N*/ SvxColorItem::SvxColorItem( const Color& rCol, const USHORT nId ) :
/*N*/ 	SfxPoolItem( nId ),
/*N*/ 	mColor( rCol )
/*N*/ {
/*N*/ }

// -----------------------------------------------------------------------

/*N*/ SvxColorItem::SvxColorItem( SvStream &rStrm, const USHORT nId ) :
/*N*/ 	SfxPoolItem( nId )
/*N*/ {
/*N*/ 	Color aColor;
/*N*/ 	rStrm >> aColor;
/*N*/ 	mColor = aColor;
/*N*/ }

// -----------------------------------------------------------------------

/*N*/ SvxColorItem::SvxColorItem( const SvxColorItem &rCopy ) :
/*N*/ 	SfxPoolItem( rCopy ),
/*N*/ 	mColor( rCopy.mColor )
/*N*/ {
/*N*/ }

// -----------------------------------------------------------------------

/*N*/ SvxColorItem::~SvxColorItem()
/*N*/ {
/*N*/ }

// -----------------------------------------------------------------------
/*N*/ USHORT SvxColorItem::GetVersion( USHORT nFFVer ) const
/*N*/ {
/*N*/ 	DBG_ASSERT( SOFFICE_FILEFORMAT_31==nFFVer ||
/*N*/ 			SOFFICE_FILEFORMAT_40==nFFVer ||
/*N*/ 			SOFFICE_FILEFORMAT_50==nFFVer,
/*N*/ 			"SvxColorItem: Gibt es ein neues Fileformat?" );
/*N*/ 	return  SOFFICE_FILEFORMAT_50 >= nFFVer ? VERSION_USEAUTOCOLOR : 0;
/*N*/ }

// -----------------------------------------------------------------------

/*N*/ int SvxColorItem::operator==( const SfxPoolItem& rAttr ) const
/*N*/ {
/*N*/ 	DBG_ASSERT( SfxPoolItem::operator==(rAttr), "unequal types" );
/*N*/ 
/*N*/ 	return	mColor == ( (const SvxColorItem&)rAttr ).mColor;
/*N*/ }

// -----------------------------------------------------------------------

/*N*/ sal_Bool SvxColorItem::QueryValue( uno::Any& rVal, BYTE nMemberId ) const
/*N*/ {
/*N*/ 	rVal <<= (sal_Int32)(mColor.GetColor());
/*N*/ 	return sal_True;
/*N*/ }

// -----------------------------------------------------------------------

/*N*/ sal_Bool SvxColorItem::PutValue( const uno::Any& rVal, BYTE nMemberId )
/*N*/ {
/*N*/ 	sal_Int32 nColor;
/*N*/ 	if(!(rVal >>= nColor))
/*N*/ 		return sal_False;
/*N*/ 
/*N*/ 	mColor.SetColor( nColor );
/*N*/ 	return sal_True;
/*N*/ }

// -----------------------------------------------------------------------

/*N*/ SfxPoolItem* SvxColorItem::Clone( SfxItemPool * ) const
/*N*/ {
/*N*/ 	return new SvxColorItem( *this );
/*N*/ }

// -----------------------------------------------------------------------

/*N*/ SvStream& SvxColorItem::Store( SvStream& rStrm , USHORT nItemVersion ) const
/*N*/ {
/*N*/ 	if( VERSION_USEAUTOCOLOR == nItemVersion &&
/*N*/ 		COL_AUTO == mColor.GetColor() )
/*N*/ 		rStrm << Color( COL_BLACK );
/*N*/ 	else
/*N*/ 		rStrm << mColor;
/*N*/ 	return rStrm;
/*N*/ }

// -----------------------------------------------------------------------

/*N*/ SfxPoolItem* SvxColorItem::Create(SvStream& rStrm, USHORT nVer ) const
/*N*/ {
/*N*/ 	return new SvxColorItem( rStrm, Which() );
/*N*/ }

//------------------------------------------------------------------------

//STRIP001 SfxItemPresentation SvxColorItem::GetPresentation
//STRIP001 (
//STRIP001 	SfxItemPresentation ePres,
//STRIP001 	SfxMapUnit			eCoreUnit,
//STRIP001 	SfxMapUnit			ePresUnit,
//STRIP001     XubString&          rText, const IntlWrapper *pIntl
//STRIP001 )	const
//STRIP001 {
//STRIP001 #ifndef SVX_LIGHT
//STRIP001 	switch ( ePres )
//STRIP001 	{
//STRIP001 		case SFX_ITEM_PRESENTATION_NONE:
//STRIP001 			rText.Erase();
//STRIP001 			return ePres;
//STRIP001 		case SFX_ITEM_PRESENTATION_NAMELESS:
//STRIP001 		case SFX_ITEM_PRESENTATION_COMPLETE:
//STRIP001 			rText = ::GetColorString( mColor );
//STRIP001 			return ePres;
//STRIP001 	}
//STRIP001 #endif
//STRIP001 	return SFX_ITEM_PRESENTATION_NONE;
//STRIP001 }

// -----------------------------------------------------------------------

/*N*/ void SvxColorItem::SetValue( const Color& rNewCol )
/*N*/ {
/*N*/ 	mColor = rNewCol;
/*N*/ }

// class SvxCharSetColorItem ---------------------------------------------

/*N*/ SvxCharSetColorItem::SvxCharSetColorItem( const USHORT nId ) :
/*N*/ 	SvxColorItem( nId ),
/*N*/ 
/*N*/ 	eFrom( RTL_TEXTENCODING_DONTKNOW )
/*N*/ {
/*N*/ }

// -----------------------------------------------------------------------

/*N*/ SvxCharSetColorItem::SvxCharSetColorItem( const Color& rCol,
/*N*/ 										  const rtl_TextEncoding eFrom,
/*N*/ 										  const USHORT nId ) :
/*N*/ 	SvxColorItem( rCol, nId ),
/*N*/ 
/*N*/ 	eFrom( eFrom )
/*N*/ {
/*N*/ }


// -----------------------------------------------------------------------

/*N*/ SfxPoolItem* SvxCharSetColorItem::Clone( SfxItemPool * ) const
/*N*/ {
/*N*/ 	return new SvxCharSetColorItem( *this );
/*N*/ }

// -----------------------------------------------------------------------

/*N*/ SvStream& SvxCharSetColorItem::Store( SvStream& rStrm , USHORT nItemVersion ) const
/*N*/ {
/*N*/ 	// #90477# rStrm << (BYTE) GetStoreCharSet( GetCharSet(), (USHORT)rStrm.GetVersion() )
/*N*/ 	//	  << GetValue();
/*N*/ 	rStrm << (BYTE)GetSOStoreTextEncoding(GetCharSet(), (sal_uInt16)rStrm.GetVersion())
/*N*/ 		  << GetValue();
/*N*/ 	return rStrm;
/*N*/ }

// -----------------------------------------------------------------------

/*N*/ SfxPoolItem* SvxCharSetColorItem::Create(SvStream& rStrm, USHORT) const
/*N*/ {
/*N*/ 	BYTE cSet;
/*N*/ 	Color aColor;
/*N*/ 	rStrm >> cSet >> aColor;
/*N*/ 	return new SvxCharSetColorItem( aColor,  (rtl_TextEncoding)cSet, Which() );
/*N*/ }

//------------------------------------------------------------------------

//STRIP001 SfxItemPresentation SvxCharSetColorItem::GetPresentation
//STRIP001 (
//STRIP001 	SfxItemPresentation ePres,
//STRIP001 	SfxMapUnit			eCoreUnit,
//STRIP001 	SfxMapUnit			ePresUnit,
//STRIP001     XubString&          rText, const IntlWrapper *pIntl
//STRIP001 )	const
//STRIP001 {
//STRIP001 	rText.Erase();
//STRIP001 	return SFX_ITEM_PRESENTATION_NONE;
//STRIP001 }

// class SvxKerningItem --------------------------------------------------

/*N*/ SvxKerningItem::SvxKerningItem( const short nKern, const USHORT nId ) :
/*N*/ 	SfxInt16Item( nId, nKern )
/*N*/ {
/*N*/ }

// -----------------------------------------------------------------------

/*N*/ SfxPoolItem* SvxKerningItem::Clone( SfxItemPool * ) const
/*N*/ {
/*N*/ 	return new SvxKerningItem( *this );
/*N*/ }

// -----------------------------------------------------------------------

/*N*/ SvStream& SvxKerningItem::Store( SvStream& rStrm , USHORT nItemVersion ) const
/*N*/ {
/*N*/ 	rStrm << (short) GetValue();
/*N*/ 	return rStrm;
/*N*/ }

// -----------------------------------------------------------------------

//STRIP001 int SvxKerningItem::ScaleMetrics( long nMult, long nDiv )
//STRIP001 {
//STRIP001 	SetValue( (sal_Int16)Scale( GetValue(), nMult, nDiv ) );
//STRIP001 	return 1;
//STRIP001 }

// -----------------------------------------------------------------------

//STRIP001 int SvxKerningItem::HasMetrics() const
//STRIP001 {
//STRIP001 	return 1;
//STRIP001 }

// -----------------------------------------------------------------------

/*N*/ SfxPoolItem* SvxKerningItem::Create(SvStream& rStrm, USHORT) const
/*N*/ {
/*N*/ 	short nValue;
/*N*/ 	rStrm >> nValue;
/*N*/ 	return new SvxKerningItem( nValue, Which() );
/*N*/ }

//------------------------------------------------------------------------

//STRIP001 SfxItemPresentation SvxKerningItem::GetPresentation
//STRIP001 (
//STRIP001 	SfxItemPresentation ePres,
//STRIP001 	SfxMapUnit			eCoreUnit,
//STRIP001 	SfxMapUnit			ePresUnit,
//STRIP001     XubString&          rText, const IntlWrapper *pIntl
//STRIP001 )	const
//STRIP001 {
//STRIP001 #ifndef SVX_LIGHT
//STRIP001 	switch ( ePres )
//STRIP001 	{
//STRIP001 		case SFX_ITEM_PRESENTATION_NONE:
//STRIP001 			rText.Erase();
//STRIP001 			return ePres;
//STRIP001 		case SFX_ITEM_PRESENTATION_NAMELESS:
//STRIP001             rText = GetMetricText( (long)GetValue(), eCoreUnit, SFX_MAPUNIT_POINT, pIntl );
//STRIP001             rText += SVX_RESSTR(GetMetricId(SFX_MAPUNIT_POINT));
//STRIP001 			return ePres;
//STRIP001 		case SFX_ITEM_PRESENTATION_COMPLETE:
//STRIP001 		{
//STRIP001 			rText = SVX_RESSTR(RID_SVXITEMS_KERNING_COMPLETE);
//STRIP001 			USHORT nId = 0;
//STRIP001 
//STRIP001 			if ( GetValue() > 0 )
//STRIP001 				nId = RID_SVXITEMS_KERNING_EXPANDED;
//STRIP001 			else if ( GetValue() < 0 )
//STRIP001 				nId = RID_SVXITEMS_KERNING_CONDENSED;
//STRIP001 
//STRIP001 			if ( nId )
//STRIP001 				rText += SVX_RESSTR(nId);
//STRIP001             rText += GetMetricText( (long)GetValue(), eCoreUnit, SFX_MAPUNIT_POINT, pIntl );
//STRIP001             rText += SVX_RESSTR(GetMetricId(SFX_MAPUNIT_POINT));
//STRIP001 			return ePres;
//STRIP001 		}
//STRIP001 	}
//STRIP001 #endif
//STRIP001 	return SFX_ITEM_PRESENTATION_NONE;
//STRIP001 }
/* -----------------------------19.02.01 12:21--------------------------------

 ---------------------------------------------------------------------------*/
/*N*/ sal_Bool SvxKerningItem::QueryValue( uno::Any& rVal, BYTE nMemberId ) const
/*N*/ {
/*N*/ 	sal_Int16 nVal = GetValue();
/*N*/ 	if(nMemberId & CONVERT_TWIPS)
/*N*/ 		nVal = (sal_Int16)TWIP_TO_MM100(nVal);
/*N*/ 	rVal <<= nVal;
/*N*/ 	return sal_True;
/*N*/ }
// -----------------------------------------------------------------------
/*N*/ sal_Bool SvxKerningItem::PutValue( const uno::Any& rVal, BYTE nMemberId)
/*N*/ {
/*N*/ 	sal_Int16 nVal;
/*N*/ 	if(!(rVal >>= nVal))
/*N*/ 		return sal_False;
/*N*/ 	if(nMemberId & CONVERT_TWIPS)
/*N*/ 		nVal = (sal_Int16)MM100_TO_TWIP(nVal);
/*N*/ 	SetValue(nVal);
/*N*/ 	return sal_True;
/*N*/ }

// class SvxCaseMapItem --------------------------------------------------

/*N*/ SvxCaseMapItem::SvxCaseMapItem( const SvxCaseMap eMap, const USHORT nId ) :
/*N*/ 	SfxEnumItem( nId, eMap )
/*N*/ {
/*N*/ }

// -----------------------------------------------------------------------

/*?*/ USHORT SvxCaseMapItem::GetValueCount() const
/*?*/ {
/*?*/ DBG_ASSERT(0, "STRIP"); return 0;//STRIP001 	return SVX_CASEMAP_END;	// SVX_CASEMAP_KAPITAELCHEN	+ 1
/*?*/ }

// -----------------------------------------------------------------------

/*N*/ SfxPoolItem* SvxCaseMapItem::Clone( SfxItemPool * ) const
/*N*/ {
/*N*/ 	return new SvxCaseMapItem( *this );
/*N*/ }

// -----------------------------------------------------------------------

/*N*/ SvStream& SvxCaseMapItem::Store( SvStream& rStrm , USHORT nItemVersion ) const
/*N*/ {
/*N*/ 	rStrm << (BYTE) GetValue();
/*N*/ 	return rStrm;
/*N*/ }

// -----------------------------------------------------------------------

/*N*/ SfxPoolItem* SvxCaseMapItem::Create(SvStream& rStrm, USHORT) const
/*N*/ {
/*N*/ 	BYTE cMap;
/*N*/ 	rStrm >> cMap;
/*N*/ 	return new SvxCaseMapItem( (const SvxCaseMap)cMap, Which() );
/*N*/ }

//------------------------------------------------------------------------

//STRIP001 SfxItemPresentation SvxCaseMapItem::GetPresentation
//STRIP001 (
//STRIP001 	SfxItemPresentation ePres,
//STRIP001 	SfxMapUnit			eCoreUnit,
//STRIP001 	SfxMapUnit			ePresUnit,
//STRIP001     XubString&          rText, const IntlWrapper *pIntl
//STRIP001 )	const
//STRIP001 {
//STRIP001 	switch ( ePres )
//STRIP001 	{
//STRIP001 		case SFX_ITEM_PRESENTATION_NONE:
//STRIP001 			rText.Erase();
//STRIP001 			return ePres;
//STRIP001 		case SFX_ITEM_PRESENTATION_NAMELESS:
//STRIP001 		case SFX_ITEM_PRESENTATION_COMPLETE:
//STRIP001 			rText = GetValueTextByPos( GetValue() );
//STRIP001 			return ePres;
//STRIP001 	}
//STRIP001 	return SFX_ITEM_PRESENTATION_NONE;
//STRIP001 }

// -----------------------------------------------------------------------

//STRIP001 XubString SvxCaseMapItem::GetValueTextByPos( USHORT nPos ) const
//STRIP001 {
//STRIP001 	DBG_ASSERT( nPos < (USHORT)SVX_CASEMAP_END, "enum overflow!" );
//STRIP001 	return SVX_RESSTR( RID_SVXITEMS_CASEMAP_BEGIN + nPos );
//STRIP001 }

/*-----------------13.03.98 16:29-------------------

--------------------------------------------------*/
/*N*/ sal_Bool SvxCaseMapItem::QueryValue( uno::Any& rVal, BYTE nMemberId ) const
/*N*/ {
/*N*/ 	sal_Int16 nRet = style::CaseMap::NONE;
/*N*/ 	switch( GetValue() )
/*N*/ 	{
/*N*/ //		case SVX_CASEMAP_NOT_MAPPED  :		nRet = style::CaseMap::NONE 	; break;
/*N*/ 		case SVX_CASEMAP_VERSALIEN   :      nRet = style::CaseMap::UPPERCASE; break;
/*?*/ 		case SVX_CASEMAP_GEMEINE     :      nRet = style::CaseMap::LOWERCASE; break;
/*N*/ 		case SVX_CASEMAP_TITEL       :      nRet = style::CaseMap::TITLE    ; break;
/*N*/ 		case SVX_CASEMAP_KAPITAELCHEN:      nRet = style::CaseMap::SMALLCAPS; break;
/*N*/ 	}
/*N*/ 	rVal <<= (sal_Int16)(nRet);
/*N*/ 	return sal_True;
/*N*/ }
/*-----------------13.03.98 16:29-------------------

--------------------------------------------------*/
/*N*/ sal_Bool SvxCaseMapItem::PutValue( const uno::Any& rVal, BYTE nMemberId )
/*N*/ {
/*N*/ 	sal_uInt16 nVal;
/*N*/ 	if(!(rVal >>= nVal))
/*N*/ 		return sal_False;
/*N*/ 
/*N*/ 	switch( nVal )
/*N*/ 	{
/*N*/ 	case style::CaseMap::NONE 	 :  nVal = SVX_CASEMAP_NOT_MAPPED  ; break;
/*N*/ 	case style::CaseMap::UPPERCASE:  nVal = SVX_CASEMAP_VERSALIEN   ; break;
/*?*/ 	case style::CaseMap::LOWERCASE:  nVal = SVX_CASEMAP_GEMEINE     ; break;
/*N*/ 	case style::CaseMap::TITLE    :  nVal = SVX_CASEMAP_TITEL       ; break;
/*N*/ 	case style::CaseMap::SMALLCAPS:  nVal = SVX_CASEMAP_KAPITAELCHEN; break;
/*N*/ 	}
/*N*/ 	SetValue(nVal);
/*N*/ 	return sal_True;
/*N*/ }

// class SvxEscapementItem -----------------------------------------------

/*N*/ SvxEscapementItem::SvxEscapementItem( const USHORT nId ) :
/*N*/ 	SfxEnumItemInterface( nId ),
/*N*/ 
/*N*/ 	nEsc	( 0 ),
/*N*/ 	nProp	( 100 )
/*N*/ {
/*N*/ }

// -----------------------------------------------------------------------

//STRIP001 SvxEscapementItem::SvxEscapementItem( const SvxEscapement eEscape,
//STRIP001 									  const USHORT nId ) :
//STRIP001 	SfxEnumItemInterface( nId ),
//STRIP001 	nProp( 100 )
//STRIP001 {
//STRIP001 	SetEscapement( eEscape );
//STRIP001 	if( nEsc )
//STRIP001 		nProp = 58;
//STRIP001 }

// -----------------------------------------------------------------------

/*N*/ SvxEscapementItem::SvxEscapementItem( const short nEsc,
/*N*/ 									  const BYTE nProp,
/*N*/ 									  const USHORT nId ) :
/*N*/ 	SfxEnumItemInterface( nId ),
/*N*/ 	nEsc	( nEsc ),
/*N*/ 	nProp	( nProp )
/*N*/ {
/*N*/ }

// -----------------------------------------------------------------------

/*N*/ int SvxEscapementItem::operator==( const SfxPoolItem& rAttr ) const
/*N*/ {
/*N*/ 	DBG_ASSERT( SfxPoolItem::operator==(rAttr), "unequal types" );
/*N*/ 
/*N*/ 	return( nEsc  == ((SvxEscapementItem&)rAttr).nEsc &&
/*N*/ 			nProp == ((SvxEscapementItem&)rAttr).nProp );
/*N*/ }

// -----------------------------------------------------------------------

/*N*/ SfxPoolItem* SvxEscapementItem::Clone( SfxItemPool * ) const
/*N*/ {
/*N*/ 	return new SvxEscapementItem( *this );
/*N*/ }

// -----------------------------------------------------------------------

/*N*/ SvStream& SvxEscapementItem::Store( SvStream& rStrm , USHORT nItemVersion ) const
/*N*/ {
/*N*/ 	short nEsc = GetEsc();
/*N*/ 	if( SOFFICE_FILEFORMAT_31 == rStrm.GetVersion() )
/*N*/ 	{
/*N*/ 		if( DFLT_ESC_AUTO_SUPER == nEsc )
/*N*/ 			nEsc = DFLT_ESC_SUPER;
/*N*/ 		else if( DFLT_ESC_AUTO_SUB == nEsc )
/*N*/ 			nEsc = DFLT_ESC_SUB;
/*N*/ 	}
/*N*/ 	rStrm << (BYTE) GetProp()
/*N*/ 		  << (short) nEsc;
/*N*/ 	return rStrm;
/*N*/ }

// -----------------------------------------------------------------------

/*N*/ SfxPoolItem* SvxEscapementItem::Create(SvStream& rStrm, USHORT) const
/*N*/ {
/*N*/ 	BYTE nProp;
/*N*/ 	short nEsc;
/*N*/ 	rStrm >> nProp >> nEsc;
/*N*/ 	return new SvxEscapementItem( nEsc, nProp, Which() );
/*N*/ }

// -----------------------------------------------------------------------

/*?*/ USHORT SvxEscapementItem::GetValueCount() const
/*?*/ {
/*?*/ DBG_ASSERT(0, "STRIP"); return 0;//STRIP001 	return SVX_ESCAPEMENT_END;	// SVX_ESCAPEMENT_SUBSCRIPT + 1
/*?*/ }

//------------------------------------------------------------------------

//STRIP001 SfxItemPresentation SvxEscapementItem::GetPresentation
//STRIP001 (
//STRIP001 	SfxItemPresentation ePres,
//STRIP001 	SfxMapUnit			eCoreUnit,
//STRIP001 	SfxMapUnit			ePresUnit,
//STRIP001     XubString&          rText, const IntlWrapper *pIntl
//STRIP001 )	const
//STRIP001 {
//STRIP001 	switch ( ePres )
//STRIP001 	{
//STRIP001 		case SFX_ITEM_PRESENTATION_NONE:
//STRIP001 			rText.Erase();
//STRIP001 			return ePres;
//STRIP001 		case SFX_ITEM_PRESENTATION_NAMELESS:
//STRIP001 		case SFX_ITEM_PRESENTATION_COMPLETE:
//STRIP001 		{
//STRIP001 			rText = GetValueTextByPos( GetEnumValue() );
//STRIP001 
//STRIP001 			if ( nEsc != 0 )
//STRIP001 			{
//STRIP001 				if( DFLT_ESC_AUTO_SUPER == nEsc || DFLT_ESC_AUTO_SUB == nEsc )
//STRIP001 					rText += String( SVX_RESSTR(RID_SVXITEMS_ESCAPEMENT_AUTO) );
//STRIP001 				else
//STRIP001 					( rText += String::CreateFromInt32( nEsc )) += sal_Unicode('%');
//STRIP001 			}
//STRIP001 			return ePres;
//STRIP001 		}
//STRIP001 	}
//STRIP001 	return SFX_ITEM_PRESENTATION_NONE;
//STRIP001 }

// -----------------------------------------------------------------------

//STRIP001 XubString SvxEscapementItem::GetValueTextByPos( USHORT nPos ) const
//STRIP001 {
//STRIP001 	DBG_ASSERT( nPos < (USHORT)SVX_ESCAPEMENT_END, "enum overflow!" );
//STRIP001 	return SVX_RESSTR(RID_SVXITEMS_ESCAPEMENT_BEGIN + nPos);
//STRIP001 }

// -----------------------------------------------------------------------

/*?*/ USHORT SvxEscapementItem::GetEnumValue() const
/*?*/ {
/*?*/ DBG_ASSERT(0, "STRIP"); return 0;//STRIP001 //STRIP001 	if ( nEsc < 0 )
//STRIP001 		return SVX_ESCAPEMENT_SUBSCRIPT;
//STRIP001 	else if ( nEsc > 0 )
//STRIP001 		return SVX_ESCAPEMENT_SUPERSCRIPT;
//STRIP001 	return SVX_ESCAPEMENT_OFF;
/*?*/ }

// -----------------------------------------------------------------------

/*?*/ void SvxEscapementItem::SetEnumValue( USHORT nVal )
/*?*/ {
/*?*/ DBG_ASSERT(0, "STRIP"); //STRIP001 	SetEscapement( (const SvxEscapement)nVal );
/*?*/ }

/*-----------------13.03.98 17:05-------------------

--------------------------------------------------*/
/*N*/ sal_Bool SvxEscapementItem::QueryValue( uno::Any& rVal, BYTE nMemberId ) const
/*N*/ {
/*N*/     sal_Bool bConvert = 0!=(nMemberId&CONVERT_TWIPS);
/*N*/     nMemberId &= ~CONVERT_TWIPS;
/*N*/ 	switch(nMemberId)
/*N*/ 	{
/*N*/ 		case MID_ESC:
/*N*/ 			rVal <<= (sal_Int16)(nEsc);
/*N*/ 		break;
/*N*/ 		case MID_ESC_HEIGHT:
/*N*/ 			rVal <<= (sal_Int8)(nProp);
/*N*/ 		break;
/*N*/ 		case MID_AUTO_ESC:
/*?*/ 			rVal = Bool2Any(DFLT_ESC_AUTO_SUB == nEsc || DFLT_ESC_AUTO_SUPER == nEsc);
/*N*/ 		break;
/*N*/ 	}
/*N*/ 	return sal_True;
/*N*/ }
/*-----------------13.03.98 17:05-------------------

--------------------------------------------------*/
/*N*/ sal_Bool SvxEscapementItem::PutValue( const uno::Any& rVal, BYTE nMemberId )
/*N*/ {
/*N*/     sal_Bool bConvert = 0!=(nMemberId&CONVERT_TWIPS);
/*N*/     nMemberId &= ~CONVERT_TWIPS;
/*N*/ 	switch(nMemberId)
/*N*/ 	{
/*N*/ 		case MID_ESC:
/*N*/ 		{
/*N*/ 			sal_Int16 nVal;
/*N*/ 			if( (rVal >>= nVal) && (Abs(nVal) <= 101))
/*N*/ 				nEsc = nVal;
/*N*/ 			else
/*N*/ 				return sal_False;
/*N*/ 		}
/*N*/ 		break;
/*N*/ 		case MID_ESC_HEIGHT:
/*N*/ 		{
/*N*/ 			sal_Int8 nVal;
/*N*/ 			if( (rVal >>= nVal) && (nVal <= 100))
/*N*/ 				nProp = nVal;
/*N*/ 			else
/*N*/ 				return sal_False;
/*N*/ 		}
/*N*/ 		break;
/*N*/ 		case MID_AUTO_ESC:
/*N*/ 		{
/*?*/ 			BOOL bVal = Any2Bool(rVal);
/*?*/ 			if(bVal)
/*?*/ 			{
/*?*/ 				if(nEsc < 0)
/*?*/ 					nEsc = DFLT_ESC_AUTO_SUB;
/*?*/ 				else
/*?*/ 					nEsc = DFLT_ESC_AUTO_SUPER;
/*?*/ 			}
/*?*/ 			else
/*?*/ 				if(DFLT_ESC_AUTO_SUPER == nEsc )
/*?*/ 					--nEsc;
/*?*/ 				else if(DFLT_ESC_AUTO_SUB == nEsc)
/*?*/ 					++nEsc;
/*N*/ 		}
/*N*/ 		break;
/*N*/ 	}
/*N*/ 	return sal_True;
/*N*/ }

// class SvxLanguageItem -------------------------------------------------

/*N*/ SvxLanguageItem::SvxLanguageItem( const LanguageType eLang, const USHORT nId )
/*N*/ 	: SfxEnumItem( nId , eLang )
/*N*/ {
/*N*/ }

// -----------------------------------------------------------------------

/*?*/ USHORT SvxLanguageItem::GetValueCount() const
/*?*/ {
/*?*/ DBG_ASSERT(0, "STRIP"); return 0;//STRIP001 	return LANGUAGE_COUNT;	// aus tlintl.hxx
/*?*/ }

// -----------------------------------------------------------------------

/*N*/ SfxPoolItem* SvxLanguageItem::Clone( SfxItemPool * ) const
/*N*/ {
/*N*/ 	return new SvxLanguageItem( *this );
/*N*/ }

// -----------------------------------------------------------------------

/*N*/ SvStream& SvxLanguageItem::Store( SvStream& rStrm , USHORT nItemVersion ) const
/*N*/ {
/*N*/ 	rStrm << (USHORT) GetValue();
/*N*/ 	return rStrm;
/*N*/ }

// -----------------------------------------------------------------------

/*N*/ SfxPoolItem* SvxLanguageItem::Create(SvStream& rStrm, USHORT) const
/*N*/ {
/*N*/ 	USHORT nValue;
/*N*/ 	rStrm >> nValue;
/*N*/ 	return new SvxLanguageItem( (LanguageType)nValue, Which() );
/*N*/ }

//------------------------------------------------------------------------

//STRIP001 SfxItemPresentation SvxLanguageItem::GetPresentation
//STRIP001 (
//STRIP001 	SfxItemPresentation ePres,
//STRIP001 	SfxMapUnit			eCoreUnit,
//STRIP001 	SfxMapUnit			ePresUnit,
//STRIP001     XubString&          rText, const IntlWrapper *pIntl
//STRIP001 )	const
//STRIP001 {
//STRIP001 #ifndef SVX_LIGHT
//STRIP001 	switch ( ePres )
//STRIP001 	{
//STRIP001 		case SFX_ITEM_PRESENTATION_NONE:
//STRIP001 			rText.Erase();
//STRIP001 			return ePres;
//STRIP001 		case SFX_ITEM_PRESENTATION_NAMELESS:
//STRIP001 		case SFX_ITEM_PRESENTATION_COMPLETE:
//STRIP001 		{
//STRIP001 			SvxLanguageTable aLangTable;
//STRIP001 			rText = aLangTable.GetString( (LanguageType)GetValue() );
//STRIP001 			return ePres;
//STRIP001 		}
//STRIP001 	}
//STRIP001 #endif // !SVX_LIGHT
//STRIP001 	return SFX_ITEM_PRESENTATION_NONE;
//STRIP001 }

/*-----------------14.03.98 14:13-------------------

--------------------------------------------------*/
/*N*/ sal_Bool SvxLanguageItem::QueryValue( uno::Any& rVal, BYTE nMemberId ) const
/*N*/ {
/*N*/     sal_Bool bConvert = 0!=(nMemberId&CONVERT_TWIPS);
/*N*/     nMemberId &= ~CONVERT_TWIPS;
/*N*/ 	switch(nMemberId)
/*N*/ 	{
/*N*/         case MID_LANG_INT:  // for basic conversions!
/*?*/ 			rVal <<= (sal_Int16)(GetValue());
/*N*/ 		break;
/*N*/ 		case MID_LANG_LOCALE:
/*N*/ 			String sLanguage, sCountry;
/*N*/ 			::ConvertLanguageToIsoNames( GetValue(), sLanguage, sCountry );
/*N*/ 			lang::Locale aRet;
/*N*/ 			aRet.Language = sLanguage;
/*N*/ 			aRet.Country = sCountry;
/*N*/ 			rVal <<= aRet;
/*N*/ 		break;
/*N*/ 	}
/*N*/ 	return sal_True;
/*N*/ }
/*-----------------14.03.98 14:13-------------------

--------------------------------------------------*/
/*N*/ sal_Bool SvxLanguageItem::PutValue( const uno::Any& rVal, BYTE nMemberId )
/*N*/ {
/*N*/     sal_Bool bConvert = 0!=(nMemberId&CONVERT_TWIPS);
/*N*/     nMemberId &= ~CONVERT_TWIPS;
/*N*/ 	switch(nMemberId)
/*N*/ 	{
/*N*/         case MID_LANG_INT:  // for basic conversions!
/*N*/ 		{
/*?*/ 			sal_Int32 nValue;
/*?*/ 			if(!(rVal >>= nValue))
/*?*/ 				return sal_False;
/*?*/ 
/*?*/ 			SetValue((sal_Int16)nValue);
/*N*/ 		}
/*N*/ 		break;
/*N*/ 		case MID_LANG_LOCALE:
/*N*/ 		{
/*N*/ 			lang::Locale aLocale;
/*N*/ 			if(!(rVal >>= aLocale))
/*N*/ 				return sal_False;
/*N*/ 
/*N*/ 			if (aLocale.Language.getLength() || aLocale.Country.getLength())
/*N*/ 				SetValue(ConvertIsoNamesToLanguage( aLocale.Language, aLocale.Country ));
/*N*/ 			else
/*N*/ 				SetValue(LANGUAGE_NONE);
/*N*/ 		}
/*N*/ 		break;
/*N*/ 	}
/*N*/ 	return sal_True;
/*N*/ }

// class SvxNoLinebreakItem ----------------------------------------------
/*N*/ SvxNoLinebreakItem::SvxNoLinebreakItem( const sal_Bool bBreak, const USHORT nId ) :
/*N*/       SfxBoolItem( nId, bBreak )
/*N*/ {
/*N*/ }

// -----------------------------------------------------------------------

//STRIP001 SfxPoolItem* SvxNoLinebreakItem::Clone( SfxItemPool* ) const
//STRIP001 {
//STRIP001 	return new SvxNoLinebreakItem( *this );
//STRIP001 }

// -----------------------------------------------------------------------

//STRIP001 SvStream& SvxNoLinebreakItem::Store( SvStream& rStrm , USHORT nItemVersion ) const
//STRIP001 {
//STRIP001 	rStrm << (sal_Bool)GetValue();
//STRIP001 	return rStrm;
//STRIP001 }

// -----------------------------------------------------------------------

//STRIP001 SfxPoolItem* SvxNoLinebreakItem::Create(SvStream& rStrm, USHORT) const
//STRIP001 {
//STRIP001 	sal_Bool bValue;
//STRIP001 	rStrm >> bValue;
//STRIP001 	return new SvxNoLinebreakItem( bValue, Which() );
//STRIP001 }

//------------------------------------------------------------------------

//STRIP001 SfxItemPresentation SvxNoLinebreakItem::GetPresentation
//STRIP001 (
//STRIP001 	SfxItemPresentation ePres,
//STRIP001 	SfxMapUnit			eCoreUnit,
//STRIP001 	SfxMapUnit			ePresUnit,
//STRIP001     XubString&          rText, const IntlWrapper *pIntl
//STRIP001 )	const
//STRIP001 {
//STRIP001 	rText.Erase();
//STRIP001 	return SFX_ITEM_PRESENTATION_NONE;
//STRIP001 }

// class SvxNoHyphenItem -------------------------------------------------

/*N*/ SvxNoHyphenItem::SvxNoHyphenItem( const sal_Bool bHyphen, const USHORT nId ) :
/*N*/ 	SfxBoolItem( nId , bHyphen )
/*N*/ {
/*N*/ }

// -----------------------------------------------------------------------

//STRIP001 SfxPoolItem* SvxNoHyphenItem::Clone( SfxItemPool* ) const
//STRIP001 {
//STRIP001 	return new SvxNoHyphenItem( *this );
//STRIP001 }

// -----------------------------------------------------------------------

//STRIP001 SvStream& SvxNoHyphenItem::Store( SvStream& rStrm , USHORT nItemVersion ) const
//STRIP001 {
//STRIP001 	rStrm << (sal_Bool) GetValue();
//STRIP001 	return rStrm;
//STRIP001 }

// -----------------------------------------------------------------------

//STRIP001 SfxPoolItem* SvxNoHyphenItem::Create( SvStream& rStrm, USHORT ) const
//STRIP001 {
//STRIP001 	sal_Bool bValue;
//STRIP001 	rStrm >> bValue;
//STRIP001 	return new SvxNoHyphenItem( bValue, Which() );
//STRIP001 }

//------------------------------------------------------------------------

//STRIP001 SfxItemPresentation SvxNoHyphenItem::GetPresentation
//STRIP001 (
//STRIP001 	SfxItemPresentation ePres,
//STRIP001 	SfxMapUnit			eCoreUnit,
//STRIP001 	SfxMapUnit			ePresUnit,
//STRIP001     XubString&          rText, const IntlWrapper *pIntl
//STRIP001 )	const
//STRIP001 {
//STRIP001 	rText.Erase();
//STRIP001 	return SFX_ITEM_PRESENTATION_NONE;
//STRIP001 }

/*
 * Dummy-Item fuer ToolBox-Controls:
 *
 */

// -----------------------------------------------------------------------
// class SvxLineColorItem (== SvxColorItem)
// -----------------------------------------------------------------------

//STRIP001 SvxLineColorItem::SvxLineColorItem( const USHORT nId ) :
//STRIP001 	SvxColorItem( nId )
//STRIP001 {
//STRIP001 }

// -----------------------------------------------------------------------

//STRIP001 SvxLineColorItem::SvxLineColorItem( const Color& rCol, const USHORT nId ) :
//STRIP001 	SvxColorItem( rCol, nId )
//STRIP001 {
//STRIP001 }

// -----------------------------------------------------------------------

//STRIP001 SvxLineColorItem::SvxLineColorItem( SvStream &rStrm, const USHORT nId ) :
//STRIP001 	SvxColorItem( rStrm, nId )
//STRIP001 {
//STRIP001 }

// -----------------------------------------------------------------------

//STRIP001 SvxLineColorItem::SvxLineColorItem( const SvxLineColorItem &rCopy ) :
//STRIP001 	SvxColorItem( rCopy )
//STRIP001 {
//STRIP001 }

// -----------------------------------------------------------------------

//STRIP001 SvxLineColorItem::~SvxLineColorItem()
//STRIP001 {
//STRIP001 }

//------------------------------------------------------------------------

//STRIP001 SfxItemPresentation SvxLineColorItem::GetPresentation
//STRIP001 (
//STRIP001 	SfxItemPresentation ePres,
//STRIP001 	SfxMapUnit			eCoreUnit,
//STRIP001 	SfxMapUnit			ePresUnit,
//STRIP001 	XubString& 			rText,
//STRIP001     const IntlWrapper * pIntlWrapper
//STRIP001 )	const
//STRIP001 {
//STRIP001 	return SvxColorItem::GetPresentation( ePres, eCoreUnit, ePresUnit,
//STRIP001                                           rText, pIntlWrapper );
//STRIP001 }

// class SvxBlinkItem -------------------------------------------------


/*N*/ SvxBlinkItem::SvxBlinkItem( const sal_Bool bBlink, const USHORT nId ) :
/*N*/ 	SfxBoolItem( nId, bBlink )
/*N*/ {
/*N*/ }

// -----------------------------------------------------------------------

/*N*/ SfxPoolItem* SvxBlinkItem::Clone( SfxItemPool * ) const
/*N*/ {
/*N*/ 	return new SvxBlinkItem( *this );
/*N*/ }

// -----------------------------------------------------------------------

/*N*/ SvStream& SvxBlinkItem::Store( SvStream& rStrm , USHORT nItemVersion ) const
/*N*/ {
/*N*/ 	rStrm << (BYTE) GetValue();
/*N*/ 	return rStrm;
/*N*/ }

// -----------------------------------------------------------------------

/*N*/ SfxPoolItem* SvxBlinkItem::Create(SvStream& rStrm, USHORT) const
/*N*/ {
/*N*/ 	BYTE nState;
/*N*/ 	rStrm >> nState;
/*N*/ 	return new SvxBlinkItem( nState, Which() );
/*N*/ }

// -----------------------------------------------------------------------

//STRIP001 SfxItemPresentation SvxBlinkItem::GetPresentation
//STRIP001 (
//STRIP001 	SfxItemPresentation ePres,
//STRIP001 	SfxMapUnit			eCoreUnit,
//STRIP001 	SfxMapUnit			ePresUnit,
//STRIP001     XubString&          rText, const IntlWrapper *pIntl
//STRIP001 )	const
//STRIP001 {
//STRIP001 	switch ( ePres )
//STRIP001 	{
//STRIP001 		case SFX_ITEM_PRESENTATION_NONE:
//STRIP001 			rText.Erase();
//STRIP001 			return ePres;
//STRIP001 		case SFX_ITEM_PRESENTATION_NAMELESS:
//STRIP001 		case SFX_ITEM_PRESENTATION_COMPLETE:
//STRIP001 		{
//STRIP001 			USHORT nId = RID_SVXITEMS_BLINK_FALSE;
//STRIP001 
//STRIP001 			if ( GetValue() )
//STRIP001 				nId = RID_SVXITEMS_BLINK_TRUE;
//STRIP001 			rText = SVX_RESSTR(nId);
//STRIP001 			return ePres;
//STRIP001 		}
//STRIP001 	}
//STRIP001 	return SFX_ITEM_PRESENTATION_NONE;
//STRIP001 }

// class SvxEmphaisMarkItem ---------------------------------------------------

/*N*/ SvxEmphasisMarkItem::SvxEmphasisMarkItem( const FontEmphasisMark nValue,
/*N*/ 										const USHORT nId )
/*N*/ 	: SfxUInt16Item( nId, nValue )
/*N*/ {
/*N*/ }

// -----------------------------------------------------------------------

/*N*/ SfxPoolItem* SvxEmphasisMarkItem::Clone( SfxItemPool * ) const
/*N*/ {
/*N*/ 	return new SvxEmphasisMarkItem( *this );
/*N*/ }

// -----------------------------------------------------------------------

/*N*/ SvStream& SvxEmphasisMarkItem::Store( SvStream& rStrm,
/*N*/ 									 USHORT nItemVersion ) const
/*N*/ {
/*N*/ 	rStrm << (sal_uInt16)GetValue();
/*N*/ 	return rStrm;
/*N*/ }

// -----------------------------------------------------------------------

/*N*/ SfxPoolItem* SvxEmphasisMarkItem::Create( SvStream& rStrm, USHORT ) const
/*N*/ {
/*N*/ 	sal_uInt16 nValue;
/*N*/ 	rStrm >> nValue;
/*N*/ 	return new SvxEmphasisMarkItem( (FontEmphasisMark)nValue, Which() );
/*N*/ }

//------------------------------------------------------------------------

//STRIP001 SfxItemPresentation SvxEmphasisMarkItem::GetPresentation
//STRIP001 (
//STRIP001 	SfxItemPresentation ePres,
//STRIP001 	SfxMapUnit			eCoreUnit,
//STRIP001 	SfxMapUnit			ePresUnit,
//STRIP001 	XubString& 			rText,
//STRIP001     const IntlWrapper *pIntl
//STRIP001 )	const
//STRIP001 {
//STRIP001 	switch ( ePres )
//STRIP001 	{
//STRIP001 		case SFX_ITEM_PRESENTATION_NONE:
//STRIP001 			rText.Erase();
//STRIP001 			return ePres;
//STRIP001 		case SFX_ITEM_PRESENTATION_NAMELESS:
//STRIP001 		case SFX_ITEM_PRESENTATION_COMPLETE:
//STRIP001 			{
//STRIP001 				sal_uInt16 nVal = GetValue();
//STRIP001 		    	rText = SVX_RESSTR( RID_SVXITEMS_EMPHASIS_BEGIN_STYLE +
//STRIP001 										( EMPHASISMARK_STYLE & nVal ));
//STRIP001 				USHORT nId = ( EMPHASISMARK_POS_ABOVE & nVal )
//STRIP001 								? RID_SVXITEMS_EMPHASIS_ABOVE_POS
//STRIP001 								: ( EMPHASISMARK_POS_BELOW & nVal )
//STRIP001 									? RID_SVXITEMS_EMPHASIS_BELOW_POS
//STRIP001 									: 0;
//STRIP001 				if( nId )
//STRIP001 					rText += SVX_RESSTR( nId );
//STRIP001 				return ePres;
//STRIP001 			}
//STRIP001 			break;
//STRIP001 	}
//STRIP001 	return SFX_ITEM_PRESENTATION_NONE;
//STRIP001 }

// -----------------------------------------------------------------------

/*N*/ sal_Bool SvxEmphasisMarkItem::QueryValue( uno::Any& rVal, BYTE nMemberId ) const
/*N*/ {
/*N*/     sal_Bool bConvert = 0!=(nMemberId&CONVERT_TWIPS);
/*N*/     nMemberId &= ~CONVERT_TWIPS;
/*N*/ 	switch( nMemberId )
/*N*/ 	{
/*N*/ 	case MID_EMPHASIS:
/*N*/ 	{
/*N*/ 		sal_Int16 nValue = GetValue();
/*N*/ 		sal_Int16 nRet = 0;
/*N*/ 		switch(nValue & EMPHASISMARK_STYLE)
/*N*/ 		{
/*N*/ 			case EMPHASISMARK_NONE   : nRet = FontEmphasis::NONE;			break;
/*?*/ 			case EMPHASISMARK_DOT	 : nRet = FontEmphasis::DOT_ABOVE;		break;
/*?*/ 			case EMPHASISMARK_CIRCLE : nRet = FontEmphasis::CIRCLE_ABOVE;	break;
/*?*/ 			case EMPHASISMARK_DISC	 : nRet = FontEmphasis::DISK_ABOVE;		break;
/*?*/ 			case EMPHASISMARK_ACCENT : nRet = FontEmphasis::ACCENT_ABOVE;	break;
/*N*/ 		}
/*N*/ 		if(nRet && nValue & EMPHASISMARK_POS_BELOW)
/*N*/ 			nRet += 10;
/*N*/ 		rVal <<= nRet;
/*N*/ 	}
/*N*/ 	break;
/*N*/ 	}
/*N*/ 	return sal_True;
/*N*/ }

/*N*/ sal_Bool SvxEmphasisMarkItem::PutValue( const uno::Any& rVal, BYTE nMemberId )
/*N*/ {
/*N*/     sal_Bool bConvert = 0!=(nMemberId&CONVERT_TWIPS);
/*N*/     nMemberId &= ~CONVERT_TWIPS;
/*N*/ 	sal_Bool bRet = sal_True;
/*N*/ 	switch( nMemberId )
/*N*/ 	{
/*N*/ 	case MID_EMPHASIS:
/*N*/ 	{
/*N*/ 		sal_Int32 nValue = -1;
/*N*/ 		rVal >>= nValue;
/*N*/ 		switch(nValue)
/*N*/ 		{
/*N*/ 			case FontEmphasis::NONE 	   : nValue = EMPHASISMARK_NONE;   break;
/*?*/ 			case FontEmphasis::DOT_ABOVE   : nValue = EMPHASISMARK_DOT|EMPHASISMARK_POS_ABOVE;    break;
/*?*/ 			case FontEmphasis::CIRCLE_ABOVE: nValue = EMPHASISMARK_CIRCLE|EMPHASISMARK_POS_ABOVE; break;
/*?*/ 			case FontEmphasis::DISK_ABOVE  : nValue = EMPHASISMARK_DISC|EMPHASISMARK_POS_ABOVE;   break;
/*?*/ 			case FontEmphasis::ACCENT_ABOVE: nValue = EMPHASISMARK_ACCENT|EMPHASISMARK_POS_ABOVE; break;
/*?*/ 			case FontEmphasis::DOT_BELOW   : nValue = EMPHASISMARK_DOT|EMPHASISMARK_POS_BELOW;    break;
/*?*/ 			case FontEmphasis::CIRCLE_BELOW: nValue = EMPHASISMARK_CIRCLE|EMPHASISMARK_POS_BELOW; break;
/*?*/ 			case FontEmphasis::DISK_BELOW  : nValue = EMPHASISMARK_DISC|EMPHASISMARK_POS_BELOW;   break;
/*?*/ 			case FontEmphasis::ACCENT_BELOW: nValue = EMPHASISMARK_ACCENT|EMPHASISMARK_POS_BELOW; break;
/*?*/ 			default: return sal_False;
/*N*/ 		}
/*N*/ 		SetValue( (sal_Int16)nValue );
/*N*/ 	}
/*N*/ 	break;
/*N*/ 	}
/*N*/ 	return bRet;
/*N*/ }

/*N*/ USHORT SvxEmphasisMarkItem::GetVersion( USHORT nFFVer ) const
/*N*/ {
/*N*/ 	DBG_ASSERT( SOFFICE_FILEFORMAT_31==nFFVer ||
/*N*/ 			SOFFICE_FILEFORMAT_40==nFFVer ||
/*N*/ 			SOFFICE_FILEFORMAT_50==nFFVer,
/*N*/ 			"SvxEmphasisMarkItem: Gibt es ein neues Fileformat?" );
/*N*/ 
/*N*/ 	return SOFFICE_FILEFORMAT_50 > nFFVer ? USHRT_MAX : 0;
/*N*/ }


/*************************************************************************
|*    class SvxTwoLinesItem
*************************************************************************/

/*N*/ SvxTwoLinesItem::SvxTwoLinesItem( sal_Bool bFlag, sal_Unicode nStartBracket,
/*N*/ 									sal_Unicode nEndBracket, sal_uInt16 nW )
/*N*/ 	: SfxPoolItem( nW ),
/*N*/ 	bOn( bFlag ), cStartBracket( nStartBracket ), cEndBracket( nEndBracket )
/*N*/ {
/*N*/ }

//STRIP001 SvxTwoLinesItem::SvxTwoLinesItem( const SvxTwoLinesItem& rAttr )
//STRIP001 	: SfxPoolItem( rAttr.Which() ),
//STRIP001 	bOn( rAttr.bOn ), cStartBracket( rAttr.cStartBracket ),
//STRIP001 	cEndBracket( rAttr.cEndBracket )
//STRIP001 {
//STRIP001 }

/*N*/ SvxTwoLinesItem::~SvxTwoLinesItem()
/*N*/ {
/*N*/ }

/*?*/ int SvxTwoLinesItem::operator==( const SfxPoolItem& rAttr ) const
/*?*/ {
/*?*/ DBG_ASSERT(0, "STRIP"); return 0;//STRIP001 	DBG_ASSERT( SfxPoolItem::operator==( rAttr ), "not equal attribute types" );
//STRIP001 	return bOn == ((SvxTwoLinesItem&)rAttr).bOn &&
//STRIP001 		   cStartBracket == ((SvxTwoLinesItem&)rAttr).cStartBracket &&
//STRIP001 		   cEndBracket == ((SvxTwoLinesItem&)rAttr).cEndBracket;
/*?*/ }

/*?*/ SfxPoolItem* SvxTwoLinesItem::Clone( SfxItemPool* ) const
/*?*/ {
/*?*/ DBG_ASSERT(0, "STRIP"); return NULL;//STRIP001 	return new SvxTwoLinesItem( *this );
/*?*/ }

//STRIP001 sal_Bool SvxTwoLinesItem::QueryValue( ::com::sun::star::uno::Any& rVal,
//STRIP001 								BYTE nMemberId ) const
//STRIP001 {
//STRIP001     sal_Bool bConvert = 0!=(nMemberId&CONVERT_TWIPS);
//STRIP001     nMemberId &= ~CONVERT_TWIPS;
//STRIP001 	sal_Bool bRet = sal_True;
//STRIP001 	switch( nMemberId )
//STRIP001 	{
//STRIP001 	case MID_TWOLINES:
//STRIP001 		rVal = Bool2Any( bOn );
//STRIP001 		break;
//STRIP001 	case MID_START_BRACKET:
//STRIP001 		{
//STRIP001 			OUString s;
//STRIP001 			if( cStartBracket )
//STRIP001 				s = OUString( cStartBracket );
//STRIP001 			rVal <<= s;
//STRIP001 		}
//STRIP001 		break;
//STRIP001 	case MID_END_BRACKET:
//STRIP001 		{
//STRIP001 			OUString s;
//STRIP001 			if( cEndBracket )
//STRIP001 				s = OUString( cEndBracket );
//STRIP001 			rVal <<= s;
//STRIP001 		}
//STRIP001 		break;
//STRIP001 	default:
//STRIP001 		bRet = sal_False;
//STRIP001 		break;
//STRIP001 	}
//STRIP001 	return bRet;
//STRIP001 }

//STRIP001 sal_Bool SvxTwoLinesItem::PutValue( const ::com::sun::star::uno::Any& rVal,
//STRIP001 									BYTE nMemberId )
//STRIP001 {
//STRIP001     sal_Bool bConvert = 0!=(nMemberId&CONVERT_TWIPS);
//STRIP001     nMemberId &= ~CONVERT_TWIPS;
//STRIP001 	sal_Bool bRet = sal_False;
//STRIP001 	OUString s;
//STRIP001 	switch( nMemberId )
//STRIP001 	{
//STRIP001 	case MID_TWOLINES:
//STRIP001 		bOn = Any2Bool( rVal );
//STRIP001 		bRet = sal_True;
//STRIP001 		break;
//STRIP001 	case MID_START_BRACKET:
//STRIP001 		if( rVal >>= s )
//STRIP001 		{
//STRIP001 			cStartBracket = s.getLength() ? s[ 0 ] : 0;
//STRIP001 			bRet = sal_True;
//STRIP001 		}
//STRIP001 		break;
//STRIP001 	case MID_END_BRACKET:
//STRIP001 		if( rVal >>= s )
//STRIP001 		{
//STRIP001 			cEndBracket = s.getLength() ? s[ 0 ] : 0;
//STRIP001 			bRet = sal_True;
//STRIP001 		}
//STRIP001 		break;
//STRIP001 	}
//STRIP001 	return bRet;
//STRIP001 }

//STRIP001 SfxItemPresentation SvxTwoLinesItem::GetPresentation( SfxItemPresentation ePres,
//STRIP001 							SfxMapUnit eCoreMetric, SfxMapUnit ePresMetric,
//STRIP001                             String &rText, const IntlWrapper* pIntl ) const
//STRIP001 {
//STRIP001 	switch( ePres )
//STRIP001 	{
//STRIP001 	case SFX_ITEM_PRESENTATION_NONE:
//STRIP001 		rText.Erase();
//STRIP001 		break;
//STRIP001 	case SFX_ITEM_PRESENTATION_NAMELESS:
//STRIP001 	case SFX_ITEM_PRESENTATION_COMPLETE:
//STRIP001 		{
//STRIP001 			if( !GetValue() )
//STRIP001 				rText = SVX_RESSTR( RID_SVXITEMS_TWOLINES_OFF );
//STRIP001 			else
//STRIP001 			{
//STRIP001 				rText = SVX_RESSTR( RID_SVXITEMS_TWOLINES );
//STRIP001 				if( GetStartBracket() )
//STRIP001 					rText.Insert( GetStartBracket(), 0 );
//STRIP001 				if( GetEndBracket() )
//STRIP001 					rText += GetEndBracket();
//STRIP001 			}
//STRIP001 			return ePres;
//STRIP001 		}
//STRIP001 		break;
//STRIP001 	}
//STRIP001 	return SFX_ITEM_PRESENTATION_NONE;
//STRIP001 }


//STRIP001 SfxPoolItem* SvxTwoLinesItem::Create( SvStream & rStrm, USHORT nVer) const
//STRIP001 {
//STRIP001 	sal_Bool bOn;
//STRIP001 	sal_Unicode cStart, cEnd;
//STRIP001 	rStrm >> bOn >> cStart >> cEnd;
//STRIP001 	return new SvxTwoLinesItem( bOn, cStart, cEnd, Which() );
//STRIP001 }

//STRIP001 SvStream& SvxTwoLinesItem::Store(SvStream & rStrm, USHORT nIVer) const
//STRIP001 {
//STRIP001 	rStrm << GetValue() << GetStartBracket() << GetEndBracket();
//STRIP001 	return rStrm;
//STRIP001 }

/*N*/ USHORT SvxTwoLinesItem::GetVersion( USHORT nFFVer ) const
/*N*/ {
/*N*/ 	DBG_ASSERT( SOFFICE_FILEFORMAT_31==nFFVer ||
/*N*/ 			SOFFICE_FILEFORMAT_40==nFFVer ||
/*N*/ 			SOFFICE_FILEFORMAT_50==nFFVer,
/*N*/ 			"SvxTwoLinesItem: Gibt es ein neues Fileformat?" );
/*N*/ 
/*N*/ 	return SOFFICE_FILEFORMAT_50 > nFFVer ? USHRT_MAX : 0;
/*N*/ }


/*************************************************************************
|*    class SvxCharRotateItem
*************************************************************************/

/*N*/ SvxCharRotateItem::SvxCharRotateItem( sal_uInt16 nValue,
/*N*/ 					   				sal_Bool bFitIntoLine,
/*N*/ 					   				const sal_uInt16 nW )
/*N*/ 	: SfxUInt16Item( nW, nValue ), bFitToLine( bFitIntoLine )
/*N*/ {
/*N*/ }

//STRIP001 SfxPoolItem* SvxCharRotateItem::Clone( SfxItemPool* ) const
//STRIP001 {
//STRIP001 	return new SvxCharRotateItem( GetValue(), IsFitToLine(), Which() );
//STRIP001 }

//STRIP001 SfxPoolItem* SvxCharRotateItem::Create( SvStream& rStrm, USHORT ) const
//STRIP001 {
//STRIP001 	sal_uInt16 nVal;
//STRIP001 	sal_Bool b;
//STRIP001 	rStrm >> nVal >> b;
//STRIP001 	return new SvxCharRotateItem( nVal, b, Which() );
//STRIP001 }

//STRIP001 SvStream& SvxCharRotateItem::Store( SvStream & rStrm, USHORT ) const
//STRIP001 {
//STRIP001 	sal_Bool bFlag = IsFitToLine();
//STRIP001 	rStrm << GetValue() << bFlag;
//STRIP001 	return rStrm;
//STRIP001 }

/*N*/ USHORT SvxCharRotateItem::GetVersion( USHORT nFFVer ) const
/*N*/ {
/*N*/ 	return SOFFICE_FILEFORMAT_50 > nFFVer ? USHRT_MAX : 0;
/*N*/ }

//STRIP001 SfxItemPresentation SvxCharRotateItem::GetPresentation(
//STRIP001 		SfxItemPresentation ePres,
//STRIP001 		SfxMapUnit eCoreMetric, SfxMapUnit ePresMetric,
//STRIP001         String &rText, const IntlWrapper*  ) const
//STRIP001 {
//STRIP001 	switch( ePres )
//STRIP001 	{
//STRIP001 	case SFX_ITEM_PRESENTATION_NONE:
//STRIP001 		rText.Erase();
//STRIP001 		break;
//STRIP001 	case SFX_ITEM_PRESENTATION_NAMELESS:
//STRIP001 	case SFX_ITEM_PRESENTATION_COMPLETE:
//STRIP001 		{
//STRIP001 			if( !GetValue() )
//STRIP001 				rText = SVX_RESSTR( RID_SVXITEMS_CHARROTATE_OFF );
//STRIP001 			else
//STRIP001 			{
//STRIP001 				rText = SVX_RESSTR( RID_SVXITEMS_CHARROTATE );
//STRIP001 				rText.SearchAndReplaceAscii( "$(ARG1)",
//STRIP001 							String::CreateFromInt32( GetValue() / 10 ));
//STRIP001 				if( IsFitToLine() )
//STRIP001 					rText += SVX_RESSTR( RID_SVXITEMS_CHARROTATE_FITLINE );
//STRIP001 			}
//STRIP001 			return ePres;
//STRIP001 		}
//STRIP001 		break;
//STRIP001 	}
//STRIP001 	return SFX_ITEM_PRESENTATION_NONE;
//STRIP001 }

//STRIP001 sal_Bool SvxCharRotateItem::QueryValue( ::com::sun::star::uno::Any& rVal,
//STRIP001 								BYTE nMemberId ) const
//STRIP001 {
//STRIP001     sal_Bool bConvert = 0!=(nMemberId&CONVERT_TWIPS);
//STRIP001     nMemberId &= ~CONVERT_TWIPS;
//STRIP001 	sal_Bool bRet = sal_True;
//STRIP001 	switch( nMemberId )
//STRIP001 	{
//STRIP001 	case MID_ROTATE:
//STRIP001 		rVal <<= (sal_Int16)GetValue();
//STRIP001 		break;
//STRIP001 	case MID_FITTOLINE:
//STRIP001 		rVal = Bool2Any( IsFitToLine() );
//STRIP001 		break;
//STRIP001 	default:
//STRIP001 		bRet = sal_False;
//STRIP001 		break;
//STRIP001 	}
//STRIP001 	return bRet;
//STRIP001 }

//STRIP001 sal_Bool SvxCharRotateItem::PutValue( const ::com::sun::star::uno::Any& rVal,
//STRIP001 									BYTE nMemberId )
//STRIP001 {
//STRIP001     sal_Bool bConvert = 0!=(nMemberId&CONVERT_TWIPS);
//STRIP001     nMemberId &= ~CONVERT_TWIPS;
//STRIP001 	sal_Bool bRet = sal_True;
//STRIP001 	sal_Int16 nVal;
//STRIP001 	switch( nMemberId )
//STRIP001 	{
//STRIP001 	case MID_ROTATE:
//STRIP001 		rVal >>= nVal;
//STRIP001 		if(!nVal || 900 == nVal || 2700 == nVal)
//STRIP001 			SetValue( (USHORT)nVal );
//STRIP001 		else
//STRIP001 			bRet = sal_False;
//STRIP001 		break;
//STRIP001 
//STRIP001 	case MID_FITTOLINE:
//STRIP001 		SetFitToLine( Any2Bool( rVal ) );
//STRIP001 		break;
//STRIP001 	default:
//STRIP001 		bRet = sal_False;
//STRIP001 	}
//STRIP001 	return bRet;
//STRIP001 }

//STRIP001 int SvxCharRotateItem::operator==( const SfxPoolItem& rItem ) const
//STRIP001 {
//STRIP001 	DBG_ASSERT( SfxPoolItem::operator==( rItem ), "unequal type" );
//STRIP001 	return SfxUInt16Item::operator==( rItem ) &&
//STRIP001 		   IsFitToLine() == ((const SvxCharRotateItem&)rItem).IsFitToLine();
//STRIP001 }


/*************************************************************************
|*    class SvxCharScaleItem
*************************************************************************/

/*N*/ SvxCharScaleWidthItem::SvxCharScaleWidthItem( sal_uInt16 nValue,
/*N*/ 					   						const sal_uInt16 nW )
/*N*/ 	: SfxUInt16Item( nW, nValue )
/*N*/ {
/*N*/ }

/*N*/ SfxPoolItem* SvxCharScaleWidthItem::Clone( SfxItemPool* ) const
/*N*/ {
/*N*/ 	return new SvxCharScaleWidthItem( GetValue(), Which() );
/*N*/ }

/*N*/ SfxPoolItem* SvxCharScaleWidthItem::Create( SvStream& rStrm, USHORT ) const
/*N*/ {
/*N*/ 	sal_uInt16 nVal;
/*N*/ 	rStrm >> nVal;
/*N*/ 	SvxCharScaleWidthItem* pItem = new SvxCharScaleWidthItem( nVal, Which() );
/*N*/ 
/*N*/     if ( Which() == EE_CHAR_FONTWIDTH )
/*N*/     {
/*N*/         // #87271#: Was a SvxFontWidthItem in 5.2
/*N*/         // USHORT nFixWidth, USHORT nPropWidth.
/*N*/         // nFixWidth has never been used...
/*N*/ 	    rStrm >> nVal;
/*N*/         USHORT nTest;
/*N*/ 	    rStrm >> nTest;
/*N*/         if ( nTest == 0x1234 )
/*N*/ 	        pItem->SetValue( nVal );
/*N*/         else
/*N*/             rStrm.SeekRel( -2*(long)sizeof(sal_uInt16) );
/*N*/     }
/*N*/ 
/*N*/     return pItem;
/*N*/ }

/*N*/ SvStream& SvxCharScaleWidthItem::Store( SvStream& rStream, USHORT nVer ) const
/*N*/ {
/*N*/     SvStream& rRet = SfxUInt16Item::Store( rStream, nVer );
/*N*/     if ( Which() == EE_CHAR_FONTWIDTH )
/*N*/     {
/*N*/         // see comment in Create()....
/*N*/         rRet.SeekRel( -1*(long)sizeof(USHORT) );
/*N*/         rRet << (USHORT)0;
/*N*/         rRet << GetValue();
/*N*/         // Really ugly, but not a problem for reading the doc in 5.2
/*N*/         rRet << (USHORT)0x1234;
/*N*/     }
/*N*/     return rRet;
/*N*/ }


/*N*/ USHORT SvxCharScaleWidthItem::GetVersion( USHORT nFFVer ) const
/*N*/ {
/*N*/ 	return SOFFICE_FILEFORMAT_50 > nFFVer ? USHRT_MAX : 0;
/*N*/ }

//STRIP001 SfxItemPresentation SvxCharScaleWidthItem::GetPresentation(
//STRIP001 		SfxItemPresentation ePres,
//STRIP001 		SfxMapUnit eCoreMetric, SfxMapUnit ePresMetric,
//STRIP001         String &rText, const IntlWrapper*  ) const
//STRIP001 {
//STRIP001 	switch( ePres )
//STRIP001 	{
//STRIP001 	case SFX_ITEM_PRESENTATION_NONE:
//STRIP001 		rText.Erase();
//STRIP001 		break;
//STRIP001 	case SFX_ITEM_PRESENTATION_NAMELESS:
//STRIP001 	case SFX_ITEM_PRESENTATION_COMPLETE:
//STRIP001 		{
//STRIP001 			if( !GetValue() )
//STRIP001 				rText = SVX_RESSTR( RID_SVXITEMS_CHARSCALE_OFF );
//STRIP001 			else
//STRIP001 			{
//STRIP001 				rText = SVX_RESSTR( RID_SVXITEMS_CHARSCALE );
//STRIP001 				rText.SearchAndReplaceAscii( "$(ARG1)",
//STRIP001 							String::CreateFromInt32( GetValue() ));
//STRIP001 			}
//STRIP001 			return ePres;
//STRIP001 		}
//STRIP001 		break;
//STRIP001 	}
//STRIP001 	return SFX_ITEM_PRESENTATION_NONE;
//STRIP001 }

/*N*/ sal_Bool SvxCharScaleWidthItem::PutValue( const uno::Any& rVal, BYTE nMemberId )
/*N*/ {
/*N*/     // SfxUInt16Item::QueryValue returns sal_Int32 in Any now... (srx642w)
/*N*/     // where we still want this to be a sal_Int16
/*N*/     sal_Int16 nValue;
/*N*/ 	if (rVal >>= nValue)
/*N*/ 	{
/*N*/         SetValue( (UINT16) nValue );
/*N*/ 		return TRUE;
/*N*/ 	}
/*N*/ 
/*N*/     DBG_ERROR( "SvxCharScaleWidthItem::PutValue - Wrong type!" );
/*N*/ 	return FALSE;
/*N*/ }

/*N*/ sal_Bool SvxCharScaleWidthItem::QueryValue( uno::Any& rVal, BYTE nMemberId ) const
/*N*/ {
/*N*/     // SfxUInt16Item::QueryValue returns sal_Int32 in Any now... (srx642w)
/*N*/     // where we still want this to be a sal_Int16
/*N*/     rVal <<= (sal_Int16)GetValue();
/*N*/     return TRUE;
/*N*/ }

/*************************************************************************
|*    class SvxCharReliefItem
*************************************************************************/

/*N*/ SvxCharReliefItem::SvxCharReliefItem( FontRelief eValue,
/*N*/ 					   				  const sal_uInt16 nId )
/*N*/ 	: SfxEnumItem( nId, eValue )
/*N*/ {
/*N*/ }

/*N*/ SfxPoolItem* SvxCharReliefItem::Clone( SfxItemPool *pPool ) const
/*N*/ {
/*N*/ 	return new SvxCharReliefItem( *this );
/*N*/ }

/*N*/ SfxPoolItem* SvxCharReliefItem::Create(SvStream & rStrm, USHORT) const
/*N*/ {
/*N*/ 	sal_uInt16 nVal;
/*N*/ 	rStrm >> nVal;
/*N*/ 	return new SvxCharReliefItem( (FontRelief)nVal, Which() );
/*N*/ }

/*N*/ SvStream& SvxCharReliefItem::Store(SvStream & rStrm, USHORT nIVer) const
/*N*/ {
/*N*/ 	sal_uInt16 nVal = GetValue();
/*N*/ 	rStrm << nVal;
/*N*/ 	return rStrm;
/*N*/ }

/*N*/ USHORT SvxCharReliefItem::GetVersion( USHORT nFFVer ) const
/*N*/ {
/*N*/ 	return SOFFICE_FILEFORMAT_50 > nFFVer ? USHRT_MAX : 0;
/*N*/ }

/*N*/ String SvxCharReliefItem::GetValueTextByPos( USHORT nPos ) const
/*N*/ {
/*N*/ 	DBG_ASSERT( RID_SVXITEMS_RELIEF_ENGRAVED - RID_SVXITEMS_RELIEF_NONE,
/*N*/ 					"enum overflow" );
/*N*/ 	return String( SVX_RES( RID_SVXITEMS_RELIEF_BEGIN + nPos ));
/*N*/ }

/*N*/ USHORT SvxCharReliefItem::GetValueCount() const
/*N*/ {
/*N*/ 	return RID_SVXITEMS_RELIEF_ENGRAVED - RID_SVXITEMS_RELIEF_NONE;
/*N*/ }

/*N*/ SfxItemPresentation SvxCharReliefItem::GetPresentation
/*N*/ (
/*N*/     SfxItemPresentation ePres,
/*N*/     SfxMapUnit          eCoreUnit,
/*N*/     SfxMapUnit          ePresUnit,
/*N*/     XubString&          rText, const IntlWrapper *pIntl
/*N*/ )   const
/*N*/ {
/*?*/ 	SfxItemPresentation eRet = ePres;
/*?*/     switch( ePres )
/*?*/     {
/*?*/     case SFX_ITEM_PRESENTATION_NONE:
/*?*/         rText.Erase();
/*?*/ 		break;
/*?*/ 
/*?*/     case SFX_ITEM_PRESENTATION_NAMELESS:
/*?*/     case SFX_ITEM_PRESENTATION_COMPLETE:
/*?*/         rText = GetValueTextByPos( GetValue() );
/*?*/ 		break;
/*?*/ 
/*?*/ 	default:
/*?*/ 		eRet = SFX_ITEM_PRESENTATION_NONE;
/*?*/     }
/*?*/     return eRet;
/*N*/ }

/*N*/ sal_Bool SvxCharReliefItem::PutValue( const ::com::sun::star::uno::Any& rVal,
/*N*/ 										BYTE nMemberId )
/*N*/ {
/*N*/     sal_Bool bConvert = 0!=(nMemberId&CONVERT_TWIPS);
/*N*/     nMemberId &= ~CONVERT_TWIPS;
/*N*/ 	sal_Bool bRet = sal_True;
/*N*/ 	switch( nMemberId )
/*N*/ 	{
/*N*/ 	case MID_RELIEF:
/*N*/ 		{
/*N*/             sal_Int16 nVal = -1;
/*N*/ 			rVal >>= nVal;
/*N*/             if(nVal >= 0 && nVal <= RELIEF_ENGRAVED)
/*N*/                 SetValue( (FontRelief)nVal );
/*N*/             else
/*N*/                 bRet = sal_False;
/*N*/ 		}
/*N*/ 		break;
/*N*/ 	default:
/*N*/ 		bRet = sal_False;
/*N*/ 		break;
/*N*/ 	}
/*N*/ 	return bRet;
/*N*/ }

/*N*/ sal_Bool SvxCharReliefItem::QueryValue( ::com::sun::star::uno::Any& rVal,
/*N*/ 										BYTE nMemberId ) const
/*N*/ {
/*N*/     sal_Bool bConvert = 0!=(nMemberId&CONVERT_TWIPS);
/*N*/     nMemberId &= ~CONVERT_TWIPS;
/*N*/ 	sal_Bool bRet = sal_True;
/*N*/ 	switch( nMemberId )
/*N*/ 	{
/*N*/ 	case MID_RELIEF:
/*N*/ 		rVal <<= (sal_Int16)GetValue();
/*N*/ 		break;
/*N*/ 	default:
/*N*/ 		bRet = sal_False;
/*N*/ 		break;
/*N*/ 	}
/*N*/ 	return bRet;
/*N*/ }

/*************************************************************************
|*    class SvxScriptTypeItemItem
*************************************************************************/

//STRIP001 SvxScriptTypeItem::SvxScriptTypeItem( sal_uInt16 nType )
//STRIP001 	: SfxUInt16Item( SID_ATTR_CHAR_SCRIPTTYPE, nType )
//STRIP001 {
//STRIP001 }
//STRIP001 SfxPoolItem* SvxScriptTypeItem::Clone( SfxItemPool *pPool ) const
//STRIP001 {
//STRIP001 	return new SvxScriptTypeItem( GetValue() );
//STRIP001 }

/*************************************************************************
|*    class SvxScriptSetItem
*************************************************************************/

/*N*/ SvxScriptSetItem::SvxScriptSetItem( USHORT nSlotId, SfxItemPool& rPool )
/*N*/ 	: SfxSetItem( nSlotId, new SfxItemSet( rPool,
/*N*/ 						SID_ATTR_CHAR_FONT,	SID_ATTR_CHAR_FONT ))
/*N*/ {
/*N*/ 	USHORT nLatin, nAsian, nComplex;
/*N*/ 	GetWhichIds( nLatin, nAsian, nComplex );
/*N*/ 
/*N*/ 	USHORT aIds[ 9 ] = { 0 };
/*N*/ 	aIds[ 0 ] = aIds[ 1 ] = nLatin;
/*N*/ 	aIds[ 2 ] = aIds[ 3 ] = nAsian;
/*N*/ 	aIds[ 4 ] = aIds[ 5 ] = nComplex;
/*N*/ 	aIds[ 6 ] = aIds[ 7 ] = SID_ATTR_CHAR_SCRIPTTYPE;
/*N*/ 	aIds[ 8 ] = 0;
/*N*/ 
/*N*/ 	GetItemSet().SetRanges( aIds );
/*N*/ }

/*N*/ SfxPoolItem* SvxScriptSetItem::Clone( SfxItemPool *pPool ) const
/*N*/ {DBG_ASSERT(0, "STRIP"); return NULL;//STRIP001 
//STRIP001 /*N*/ 	SvxScriptSetItem* p = new SvxScriptSetItem( Which(), *GetItemSet().GetPool() );
//STRIP001 /*N*/ 	p->GetItemSet().Put( GetItemSet(), FALSE );
//STRIP001 /*N*/ 	return p;
/*N*/ }

/*N*/ SfxPoolItem* SvxScriptSetItem::Create( SvStream &, USHORT ) const
/*N*/ {
/*N*/ 	return 0;
/*N*/ }

/*N*/ const SfxPoolItem* SvxScriptSetItem::GetItemOfScriptSet(
/*N*/ 							const SfxItemSet& rSet, USHORT nId )
/*N*/ {
/*N*/ 	const SfxPoolItem* pI;
/*N*/ 	SfxItemState eSt = rSet.GetItemState( nId, FALSE, &pI );
/*N*/ 	if( SFX_ITEM_SET != eSt )
/*N*/ 		pI = SFX_ITEM_DEFAULT == eSt ? &rSet.Get( nId ) : 0;
/*N*/ 	return pI;
/*N*/ }

/*N*/ const SfxPoolItem* SvxScriptSetItem::GetItemOfScript( USHORT nScript ) const
/*N*/ {
/*N*/ 	USHORT nLatin, nAsian, nComplex;
/*N*/ 	GetWhichIds( nLatin, nAsian, nComplex );
/*N*/ 
/*N*/ 	const SfxItemSet& rSet = GetItemSet();
/*N*/ 	const SfxPoolItem *pRet, *pAsn, *pCmplx;
/*N*/ 	switch( nScript )
/*N*/ 	{
/*N*/ 	default:				//no one valid -> match to latin
/*N*/ 	//  case SCRIPTTYPE_LATIN:
/*N*/ 		pRet = GetItemOfScriptSet( rSet, nLatin );
/*N*/ 		break;
/*N*/ 	case SCRIPTTYPE_ASIAN:
/*?*/ 		pRet = GetItemOfScriptSet( rSet, nAsian );
/*?*/ 		break;
/*?*/ 	case SCRIPTTYPE_COMPLEX:
/*?*/ 		pRet = GetItemOfScriptSet( rSet, nComplex );
/*?*/ 		break;
/*?*/ 
/*?*/ 	case SCRIPTTYPE_LATIN|SCRIPTTYPE_ASIAN:
/*?*/ 		if( 0 == (pRet = GetItemOfScriptSet( rSet, nLatin )) ||
/*?*/ 			0 == (pAsn = GetItemOfScriptSet( rSet, nAsian )) ||
/*?*/ 			*pRet != *pAsn )
/*?*/ 			pRet = 0;
/*?*/ 		break;
/*?*/ 		break;
/*?*/ 
/*?*/ 	case SCRIPTTYPE_LATIN|SCRIPTTYPE_COMPLEX:
/*?*/ 		if( 0 == (pRet = GetItemOfScriptSet( rSet, nLatin )) ||
/*?*/ 			0 == (pCmplx = GetItemOfScriptSet( rSet, nComplex )) ||
/*?*/ 			*pRet != *pCmplx )
/*?*/ 			pRet = 0;
/*?*/ 		break;
/*?*/ 
/*?*/ 	case SCRIPTTYPE_ASIAN|SCRIPTTYPE_COMPLEX:
/*?*/ 		if( 0 == (pRet = GetItemOfScriptSet( rSet, nAsian )) ||
/*?*/ 			0 == (pCmplx = GetItemOfScriptSet( rSet, nComplex )) ||
/*?*/ 			*pRet != *pCmplx )
/*?*/ 			pRet = 0;
/*?*/ 		break;
/*?*/ 
/*?*/ 	case SCRIPTTYPE_LATIN|SCRIPTTYPE_ASIAN|SCRIPTTYPE_COMPLEX:
/*?*/ 		if( 0 == (pRet = GetItemOfScriptSet( rSet, nLatin )) ||
/*?*/ 			0 == (pAsn = GetItemOfScriptSet( rSet, nAsian )) ||
/*?*/ 			0 == (pCmplx = GetItemOfScriptSet( rSet, nComplex )) ||
/*?*/ 			*pRet != *pAsn || *pRet != *pCmplx )
/*N*/ 			pRet = 0;
/*N*/ 		break;
/*N*/ 	}
/*N*/ 	return pRet;
/*N*/ }


//STRIP001 void SvxScriptSetItem::PutItemForScriptType( USHORT nScriptType,
//STRIP001 											 const SfxPoolItem& rItem )
//STRIP001 {
//STRIP001 	USHORT nLatin, nAsian, nComplex;
//STRIP001 	GetWhichIds( nLatin, nAsian, nComplex );
//STRIP001 
//STRIP001 	SfxPoolItem* pCpy = rItem.Clone();
//STRIP001 	if( SCRIPTTYPE_LATIN & nScriptType )
//STRIP001 	{
//STRIP001 		pCpy->SetWhich( nLatin );
//STRIP001 		GetItemSet().Put( *pCpy );
//STRIP001 	}
//STRIP001 	if( SCRIPTTYPE_ASIAN & nScriptType )
//STRIP001 	{
//STRIP001 		pCpy->SetWhich( nAsian );
//STRIP001 		GetItemSet().Put( *pCpy );
//STRIP001 	}
//STRIP001 	if( SCRIPTTYPE_COMPLEX & nScriptType )
//STRIP001 	{
//STRIP001 		pCpy->SetWhich( nComplex );
//STRIP001 		GetItemSet().Put( *pCpy );
//STRIP001 	}
//STRIP001 	delete pCpy;
//STRIP001 }

/*N*/ void SvxScriptSetItem::GetWhichIds( USHORT& rLatin, USHORT& rAsian,
/*N*/ 									USHORT& rComplex ) const
/*N*/ {
/*N*/ 	const SfxItemPool& rPool = *GetItemSet().GetPool();
/*N*/ 	GetSlotIds( Which(), rLatin, rAsian, rComplex );
/*N*/ 	rLatin = rPool.GetWhich( rLatin );
/*N*/ 	rAsian = rPool.GetWhich( rAsian );
/*N*/ 	rComplex = rPool.GetWhich( rComplex );
/*N*/ }

/*N*/ void SvxScriptSetItem::GetSlotIds( USHORT nSlotId, USHORT& rLatin,
/*N*/ 									USHORT& rAsian, USHORT& rComplex )
/*N*/ {
/*N*/ 	switch( nSlotId )
/*N*/ 	{
/*N*/ 	default:
/*N*/ 		DBG_ASSERT( FALSE, "wrong SlotId for class SvxScriptSetItem" );
/*N*/ 		// no break - default to font - Id Range !!
/*N*/ 
/*N*/ 	case SID_ATTR_CHAR_FONT:
/*N*/ 		rLatin = SID_ATTR_CHAR_FONT;
/*N*/ 		rAsian = SID_ATTR_CHAR_CJK_FONT;
/*N*/ 		rComplex = SID_ATTR_CHAR_CTL_FONT;
/*N*/ 		break;
/*N*/ 	case SID_ATTR_CHAR_FONTHEIGHT:
/*N*/ 		rLatin = SID_ATTR_CHAR_FONTHEIGHT;
/*N*/ 		rAsian = SID_ATTR_CHAR_CJK_FONTHEIGHT;
/*N*/ 		rComplex = SID_ATTR_CHAR_CTL_FONTHEIGHT;
/*N*/ 		break;
/*N*/ 	case SID_ATTR_CHAR_WEIGHT:
/*N*/ 		rLatin = SID_ATTR_CHAR_WEIGHT;
/*N*/ 		rAsian = SID_ATTR_CHAR_CJK_WEIGHT;
/*N*/ 		rComplex = SID_ATTR_CHAR_CTL_WEIGHT;
/*N*/ 		break;
/*N*/ 	case SID_ATTR_CHAR_POSTURE:
/*N*/ 		rLatin = SID_ATTR_CHAR_POSTURE;
/*N*/ 		rAsian = SID_ATTR_CHAR_CJK_POSTURE;
/*N*/ 		rComplex = SID_ATTR_CHAR_CTL_POSTURE;
/*N*/ 		break;
/*N*/ 	case SID_ATTR_CHAR_LANGUAGE:
/*N*/ 		rLatin = SID_ATTR_CHAR_LANGUAGE;
/*N*/ 		rAsian = SID_ATTR_CHAR_CJK_LANGUAGE;
/*N*/ 		rComplex = SID_ATTR_CHAR_CTL_LANGUAGE;
/*N*/ 		break;
/*N*/ 	}
/*N*/ }

/*N*/ void GetDefaultFonts( SvxFontItem& rLatin, SvxFontItem& rAsian, SvxFontItem& rComplex )
/*N*/ {
/*N*/ 	const USHORT nItemCnt = 3;
/*N*/ 
/*N*/ 	static struct
/*N*/ 	{
/*N*/ 		USHORT nFontType;
/*N*/ 		USHORT nLanguage;
/*N*/ 	}
/*N*/ 	aOutTypeArr[ nItemCnt ] =
/*N*/ 	{
/*N*/ 		{  DEFAULTFONT_LATIN_TEXT, LANGUAGE_ENGLISH_US },
/*N*/ 		{  DEFAULTFONT_CJK_TEXT, LANGUAGE_ENGLISH_US },
/*N*/ 		{  DEFAULTFONT_CTL_TEXT, LANGUAGE_ARABIC_SAUDI_ARABIA }
/*N*/ 	};
/*N*/ 
/*N*/ 	SvxFontItem* aItemArr[ nItemCnt ] = { &rLatin, &rAsian, &rComplex };
/*N*/ 
/*N*/ 	for ( USHORT n = 0; n < nItemCnt; ++n )
/*N*/ 	{
/*N*/ 		Font aFont( OutputDevice::GetDefaultFont( aOutTypeArr[ n ].nFontType,
/*N*/ 												  aOutTypeArr[ n ].nLanguage,
/*N*/ 												  DEFAULTFONT_FLAGS_ONLYONE, 0 ) );
/*N*/ 		SvxFontItem* pItem = aItemArr[ n ];
/*N*/ 		pItem->GetFamily() = aFont.GetFamily();
/*N*/ 		pItem->GetFamilyName() = aFont.GetName();
/*N*/ 		pItem->GetStyleName().Erase();
/*N*/ 		pItem->GetPitch() = aFont.GetPitch();
/*N*/ 		pItem->GetCharSet() = aFont.GetCharSet();
/*N*/ 	}
/*N*/ }


/*N*/ USHORT GetI18NScriptTypeOfLanguage( USHORT nLang )
/*N*/ {
/*N*/     return GetI18NScriptType( SvtLanguageOptions::GetScriptTypeOfLanguage( nLang ) );
/*N*/ }

/*N*/ USHORT GetItemScriptType( short nI18NType )
/*N*/ {
/*N*/     switch ( nI18NType )
/*N*/     {
/*N*/ 	    case i18n::ScriptType::LATIN:   return SCRIPTTYPE_LATIN;
/*?*/ 	    case i18n::ScriptType::ASIAN:   return SCRIPTTYPE_ASIAN;
/*?*/ 	    case i18n::ScriptType::COMPLEX: return SCRIPTTYPE_COMPLEX;
/*N*/     }
/*N*/     return 0;
/*N*/ }

/*N*/ short GetI18NScriptType( USHORT nItemType )
/*N*/ {
/*N*/     switch ( nItemType )
/*N*/     {
/*N*/         case SCRIPTTYPE_LATIN:      return i18n::ScriptType::LATIN;
/*?*/         case SCRIPTTYPE_ASIAN:      return i18n::ScriptType::ASIAN;
/*?*/         case SCRIPTTYPE_COMPLEX:    return i18n::ScriptType::COMPLEX;
/*N*/     }
/*N*/     return 0;
/*N*/ }
}
