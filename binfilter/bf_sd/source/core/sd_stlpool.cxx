/*************************************************************************
 *
 *  $RCSfile: sd_stlpool.cxx,v $
 *
 *  $Revision: 1.4 $
 *
 *  last change: $Author: hr $ $Date: 2004-08-03 13:29:30 $
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

#pragma hdrstop

//#ifndef NOOLDSV //autogen
//#include <vcl/system.hxx>
//#endif
#ifndef _EEITEMID_HXX //autogen
#include <bf_svx/eeitemid.hxx>
#endif
#ifndef _EEITEM_HXX //autogen
#include <bf_svx/eeitem.hxx>
#endif
#ifndef _SVX_FHGTITEM_HXX //autogen
#include <bf_svx/fhgtitem.hxx>
#endif
#ifndef _SVX_COLRITEM_HXX //autogen
#include <bf_svx/colritem.hxx>
#endif
#ifndef _SVX_ITEM_HXX //autogen
#include <bf_svx/cntritem.hxx>
#endif
#ifndef _SVX_SHDDITEM_HXX //autogen
#include <bf_svx/shdditem.hxx>
#endif
#ifndef _SVX_CRSDITEM_HXX //autogen
#include <bf_svx/crsditem.hxx>
#endif
#ifndef _SVX_UDLNITEM_HXX //autogen
#include <bf_svx/udlnitem.hxx>
#endif
#ifndef _SVX_WGHTITEM_HXX //autogen
#include <bf_svx/wghtitem.hxx>
#endif
#ifndef _SVX_POSTITEM_HXX //autogen
#include <bf_svx/postitem.hxx>
#endif
#ifndef _SVX_FONTITEM_HXX //autogen
#include <bf_svx/fontitem.hxx>
#endif
// auto strip #ifndef _SFXPOOLITEM_HXX //autogen
// auto strip #include <svtools/poolitem.hxx>
// auto strip #endif
#ifndef SVX_XFILLIT0_HXX //autogen
#include <bf_svx/xfillit0.hxx>
#endif
#ifndef _SVX_XLINEIT0_HXX //autogen
#include <bf_svx/xlineit0.hxx>
#endif
#ifndef _SVX_ULSPITEM_HXX //autogen
#include <bf_svx/ulspitem.hxx>
#endif
#ifndef _SVX_NUMITEM_HXX //autogen
#include <bf_svx/numitem.hxx>
#endif
#define ITEMID_BRUSH	0
// auto strip #ifndef _SVX_BRSHITEM_HXX //autogen
// auto strip #include <bf_svx/brshitem.hxx>
// auto strip #endif
#ifndef _MyEDITENG_HXX //autogen
#include <bf_svx/editeng.hxx>
#endif
#ifndef _SFXSMPLHINT_HXX //autogen
#include <svtools/smplhint.hxx>
#endif
// auto strip #ifndef _SVX_LANGITEM_HXX
// auto strip #include <bf_svx/langitem.hxx>
// auto strip #endif
#define ITEMID_EMPHASISMARK       EE_CHAR_EMPHASISMARK
#define ITEMID_CHARRELIEF         EE_CHAR_RELIEF
#ifndef _SVX_CHARRELIEFITEM_HXX
#include <bf_svx/charreliefitem.hxx>
#endif
#ifndef _SVX_EMPHITEM_HXX
#include <bf_svx/emphitem.hxx>
#endif


#include <bf_svx/svdattr.hxx>
// auto strip #include "eetext.hxx"
// auto strip #include <bf_svx/xtable.hxx>			// fuer RGB_Color
#include <bf_svx/bulitem.hxx>
#include <bf_svx/lrspitem.hxx>
#include <bf_svx/adjitem.hxx>
#ifndef _SFXITEMPOOL_HXX //autogen
#include <svtools/itempool.hxx>
#endif

#define _SDR_POSITIVE
#define _SDR_ITEMS

#include "stlpool.hxx"
#include "sdresid.hxx"
#include "stlsheet.hxx"
#include "glob.hrc"
// auto strip #include "glob.hxx"
#include "drawdoc.hxx"
#include "sdmod.hxx"
#include "sdpage.hxx"
#include "helpids.h"
namespace binfilter {


/*************************************************************************
|*
|* Ctor
|*
\************************************************************************/

/*N*/ SdStyleSheetPool::SdStyleSheetPool(SfxItemPool& rPool, SdDrawDocument* pDocument) :
/*N*/ 	SfxStyleSheetPool(rPool),
/*N*/ 	pActualStyleSheet(NULL),
/*N*/ 	pDoc(pDocument)
/*N*/ {
/*N*/ }

/*************************************************************************
|*
|* Dtor
|*
\************************************************************************/

/*N*/ SdStyleSheetPool::~SdStyleSheetPool()
/*N*/ {
/*N*/ }

/*************************************************************************
|*
|* Vorlage erzeugen
|*
\************************************************************************/

/*N*/ SfxStyleSheetBase* SdStyleSheetPool::Create(const String& rName,
/*N*/ 											SfxStyleFamily eFamily,
/*N*/ 											USHORT nMask )
/*N*/ {
/*N*/ 	return new SdStyleSheet(rName, *this, eFamily, nMask);
/*N*/ }


/*************************************************************************
|*
|* Vorlage nach Vorbild erzeugen
|*
\************************************************************************/

//STRIP001 SfxStyleSheetBase* SdStyleSheetPool::Create(const SdStyleSheet& rStyle)
//STRIP001 {
//STRIP001 	return new SdStyleSheet(rStyle);
//STRIP001 }

/*************************************************************************
|*
|* eine Titelvorlage fuer ein Praesentationslayout suchen
|*
\************************************************************************/

/*N*/ SfxStyleSheetBase* SdStyleSheetPool::GetTitleSheet(const String& rLayoutName)
/*N*/ {
/*N*/ 	String aName(rLayoutName);
/*N*/ 	aName.AppendAscii( RTL_CONSTASCII_STRINGPARAM( SD_LT_SEPARATOR ));
/*N*/ 	aName += String(SdResId(STR_LAYOUT_TITLE));
/*N*/ 	SfxStyleSheetBase* pResult = Find(aName, SD_LT_FAMILY);
/*N*/ 	return pResult;
/*N*/ }

/*************************************************************************
|*
|* LayoutName des ersten Layouts ermitteln
|*
\************************************************************************/

//STRIP001 String SdStyleSheetPool::GetLayoutName() const
//STRIP001 {
//STRIP001 	String aName( SdResId(STR_LAYOUT_DEFAULT_NAME ) );
//STRIP001 	ULONG  nCount = aStyles.Count();
//STRIP001 
//STRIP001 	for( ULONG n = 0; n < nCount; n++ )
//STRIP001 	{
//STRIP001 		aName = aStyles.GetObject( n )->GetName();
//STRIP001 		USHORT nPos = aName.SearchAscii( SD_LT_SEPARATOR );
//STRIP001 		if( nPos != STRING_NOTFOUND )
//STRIP001 			break;
//STRIP001 	}
//STRIP001 
//STRIP001 	USHORT nPos = aName.Search( sal_Unicode( ' ' ));
//STRIP001 	if( nPos != STRING_NOTFOUND )
//STRIP001 		aName.Erase( nPos );       // removing blanks and number (e.g. "Gliederung 1")
//STRIP001 
//STRIP001 	return aName;
//STRIP001 }

/*************************************************************************
|*
|* eine Liste der Gliederungstextvorlagen fuer ein Praesentationlayout
|* erstellen, der Aufrufer muss die Liste wieder loeschen
|*
\************************************************************************/

/*N*/ List* SdStyleSheetPool::CreateOutlineSheetList (const String& rLayoutName)
/*N*/ {
/*N*/ 	String aName(rLayoutName);
/*N*/ 	aName.AppendAscii( RTL_CONSTASCII_STRINGPARAM( SD_LT_SEPARATOR ));
/*N*/ 	aName += String(SdResId(STR_LAYOUT_OUTLINE));
/*N*/ 	List* pList = new List;
/*N*/ 	for (USHORT nSheet = 1; nSheet < 10; nSheet++)
/*N*/ 	{
/*N*/ 		String aFullName(aName);
/*N*/ 		aFullName.Append( sal_Unicode( ' ' ));
/*N*/ 		aFullName.Append( String::CreateFromInt32( (sal_Int32)nSheet ));
/*N*/ 		SfxStyleSheetBase* pSheet = Find(aFullName, SD_LT_FAMILY);
/*N*/ 		pList->Insert(pSheet, LIST_APPEND);
/*N*/ 	}
/*N*/ 	return pList;
/*N*/ }

/*************************************************************************
|*
|* StyleSheets mit Defaultweren fuer das genannte Praesentationslayout erzeugen
|*
\************************************************************************/

/*N*/ void SdStyleSheetPool::CreateLayoutStyleSheets(const String& rLayoutName, sal_Bool bCheck /*=sal_False*/ )
/*N*/ {
/*N*/ 	sal_Bool bCreated = sal_False;
/*N*/ 
/*N*/ 	SfxStyleSheetBase* pSheet = NULL;
/*N*/ 
/*N*/ 	String aPrefix(rLayoutName);
/*N*/ 	String aSep( RTL_CONSTASCII_USTRINGPARAM( SD_LT_SEPARATOR ));
/*N*/ 	aPrefix.Insert(aSep);
/*N*/ 
/*N*/ 	Font aLatinFont, aCJKFont, aCTLFont;
/*N*/ 
/*N*/ 	pDoc->getDefaultFonts( aLatinFont, aCJKFont, aCTLFont );
/*N*/ 
/*N*/ 	// Font fuer Titel und Gliederung
/*N*/ 	SvxFontItem aSvxFontItem( aLatinFont.GetFamily(), aLatinFont.GetName(), aLatinFont.GetStyleName(), aLatinFont.GetPitch(),
/*N*/ 		                      aLatinFont.GetCharSet(), EE_CHAR_FONTINFO );
/*N*/ 
/*N*/ 	SvxFontItem aSvxFontItemCJK( aCJKFont.GetFamily(), aCJKFont.GetName(), aCJKFont.GetStyleName(), aCJKFont.GetPitch(),
/*N*/ 		                         aCJKFont.GetCharSet(), EE_CHAR_FONTINFO_CJK );
/*N*/ 
/*N*/ 	SvxFontItem aSvxFontItemCTL( aCTLFont.GetFamily(), aCTLFont.GetName(), aCTLFont.GetStyleName(), aCTLFont.GetPitch(),
/*N*/ 		                         aCTLFont.GetCharSet(), EE_CHAR_FONTINFO_CTL );
/*N*/ 
/*N*/ 	Font aBulletFont( GetBulletFont() );
/*N*/ 
    /**************************************************************************
    * Gliederungsebenen
    **************************************************************************/
/*N*/ 	String aName(SdResId(STR_LAYOUT_OUTLINE));
/*N*/ 	String aHelpFile;
/*N*/ 
/*N*/ 	SfxStyleSheetBase* pParent = NULL;
/*N*/ 	SvxLRSpaceItem aSvxLRSpaceItem;
/*N*/ 	SvxULSpaceItem aSvxULSpaceItem;
/*N*/ 	USHORT nLevel;
/*N*/ 
/*N*/ 	for( nLevel = 1; nLevel < 10; nLevel++)
/*N*/ 	{
/*N*/ 		String aLevelName(aName);
/*N*/ 		aLevelName.Append( sal_Unicode( ' ' ));
/*N*/ 		aLevelName.Append( String::CreateFromInt32( sal_Int32( nLevel )));
/*N*/ 
/*N*/ 		aLevelName.Insert(aPrefix, 0);
/*N*/ 
/*N*/ 		if (!Find(aLevelName, SD_LT_FAMILY))
/*N*/ 		{
/*N*/ 			bCreated = sal_True;
/*N*/ 			pSheet = &Make(aLevelName, SD_LT_FAMILY);
/*N*/ 			pSheet->SetHelpId( aHelpFile, HID_PSEUDOSHEET_OUTLINE + nLevel );
/*N*/ 
/*N*/ 			pSheet->SetParent( String() );
/*N*/ 
/*N*/ 			// Attributierung fuer Level 1, die anderen Ebenen "erben"
/*N*/ 			if (nLevel == 1)
/*N*/ 			{
/*N*/ 				SfxItemSet&     rSet = pSheet->GetItemSet();
/*N*/ 
/*N*/ 				rSet.Put(aSvxFontItem);
/*N*/ 				rSet.Put(aSvxFontItemCJK);
/*N*/ 				rSet.Put(aSvxFontItemCTL);
/*N*/ 				rSet.Put( SvxPostureItem( ITALIC_NONE, EE_CHAR_ITALIC ) );
/*N*/ 				rSet.Put( SvxPostureItem( ITALIC_NONE, EE_CHAR_ITALIC_CJK ) );
/*N*/ 				rSet.Put( SvxPostureItem( ITALIC_NONE, EE_CHAR_ITALIC_CTL ) );
/*N*/ 				rSet.Put( SvxWeightItem( WEIGHT_NORMAL, EE_CHAR_WEIGHT ) );
/*N*/ 				rSet.Put( SvxWeightItem( WEIGHT_NORMAL, EE_CHAR_WEIGHT_CJK ) );
/*N*/ 				rSet.Put( SvxWeightItem( WEIGHT_NORMAL, EE_CHAR_WEIGHT_CTL ) );
/*N*/ 				rSet.Put( SvxUnderlineItem(UNDERLINE_NONE) );
/*N*/ 				rSet.Put( SvxCrossedOutItem(STRIKEOUT_NONE) );
/*N*/ 				rSet.Put( SvxShadowedItem(FALSE) );
/*N*/ 				rSet.Put( SvxContourItem(FALSE) );
/*N*/ 				rSet.Put( SvxEmphasisMarkItem(EMPHASISMARK_NONE) );
/*N*/ 				rSet.Put( SvxCharReliefItem(RELIEF_NONE) );
/*N*/ 				rSet.Put( SvxColorItem( Color(COL_AUTO)) );
/*N*/ 				rSet.Put( XLineStyleItem(XLINE_NONE) );
/*N*/ 				rSet.Put( XFillStyleItem(XFILL_NONE) );
/*N*/ 
/*N*/ 				if( nLevel == 1 )
/*N*/ 				{
/*N*/ 					Font aBulletFont( GetBulletFont() );
/*N*/ 					PutNumBulletItem( pSheet, aBulletFont );
/*N*/ 				}
/*N*/ 			}
/*N*/ 
/*N*/ 			ULONG nFontSize = 20;
/*N*/ 			short nFirstIndent = -600;
/*N*/ 			USHORT nIndent = nLevel * 1200;
/*N*/ 			USHORT nLower = 100;
/*N*/ 
/*N*/ 			switch (nLevel)
/*N*/ 			{
/*N*/ 				case 1:
/*N*/ 				{
/*N*/ 					nFontSize = 32;
/*N*/ 					nLower = 500;
/*N*/ 					nFirstIndent = -900;
/*N*/ 				}
/*N*/ 				break;
/*N*/ 
/*N*/ 				case 2:
/*N*/ 				{
/*N*/ 					nFontSize = 28;
/*N*/ 					nLower = 400;
/*N*/ 					nFirstIndent = -800;
/*N*/ 				}
/*N*/ 				break;
/*N*/ 
/*N*/ 				case 3:
/*N*/ 				{
/*N*/ 					nFontSize = 24;
/*N*/ 					nLower = 300;
/*N*/ 				}
/*N*/ 				break;
/*N*/ 
/*N*/ 				case 4:
/*N*/ 				{
/*N*/ 					nLower = 200;
/*N*/ 				}
/*N*/ 				break;
/*N*/ 			}
/*N*/ 
/*N*/ 			// FontSize
/*N*/ 			nFontSize = (USHORT)((nFontSize * 2540L) / 72);  // Pt --> 1/100 mm
/*N*/ 			SfxItemSet& rOutlineSet = pSheet->GetItemSet();
/*N*/ 			rOutlineSet.Put( SvxFontHeightItem( nFontSize, 100, EE_CHAR_FONTHEIGHT ) );
/*N*/ 			rOutlineSet.Put( SvxFontHeightItem( nFontSize, 100, EE_CHAR_FONTHEIGHT_CJK ) );
/*N*/ 			rOutlineSet.Put( SvxFontHeightItem( nFontSize, 100, EE_CHAR_FONTHEIGHT_CTL ) );
/*N*/ 
/*N*/ 			// Einzuege
/*N*/ 			aSvxLRSpaceItem.SetTxtFirstLineOfst(nFirstIndent);
/*N*/ 			aSvxLRSpaceItem.SetTxtLeft(nIndent);
/*N*/ 			aSvxLRSpaceItem.SetRight(0);
/*N*/ 			aSvxLRSpaceItem.SetBulletFI(TRUE);
/*N*/ 			pSheet->GetItemSet().Put(aSvxLRSpaceItem);
/*N*/ 
/*N*/ 			// Zeilendurchschuss (Abstand nach unten)
/*N*/ 			aSvxULSpaceItem.SetLower(nLower);
/*N*/ 			pSheet->GetItemSet().Put(aSvxULSpaceItem);
/*N*/ 
/*N*/ 			if (nLevel == 1)
/*N*/ 			{
/*N*/ 				SfxUInt16Item aBulletStateItem(EE_PARA_BULLETSTATE, 1); // Bullets sichtbar
/*N*/ 				pSheet->GetItemSet().Put(aBulletStateItem);
/*N*/ 			}
/*N*/ 
/*
            // Gliederungsvorlagen haben die naechsthoehere Ebene als Parent
            if (pParent)
                pSheet->SetParent(pParent->GetName());
            pParent = pSheet;
*/
/*N*/ 		}
/*N*/ 	}
/*N*/ 
/*N*/ 	// if we created outline styles, we need to chain them
/*N*/ 	if( bCreated )
/*N*/ 	{
/*N*/ 		pParent = NULL;
/*N*/ 		for (nLevel = 1; nLevel < 10; nLevel++)
/*N*/ 		{
/*N*/ 			String aLevelName(aName);
/*N*/ 			aLevelName.Append( sal_Unicode( ' ' ));
/*N*/ 			aLevelName.Append( String::CreateFromInt32( sal_Int32( nLevel )));
/*N*/ 
/*N*/ 			aLevelName.Insert(aPrefix, 0);
/*N*/ 
/*N*/ 			pSheet = Find(aLevelName, SD_LT_FAMILY);
/*N*/ 
/*N*/ 			DBG_ASSERT( pSheet, "missing layout style!");
/*N*/ 
/*N*/ 			if( pSheet )
/*N*/ 			{
/*N*/ 				if (pParent)
/*N*/ 					pSheet->SetParent(pParent->GetName());
/*N*/ 				pParent = pSheet;
/*N*/ 			}
/*N*/ 		}
/*N*/ 	}
/*N*/ 
    /**************************************************************************
    * Titel
    **************************************************************************/
/*N*/ 	aName = String(SdResId(STR_LAYOUT_TITLE));
/*N*/ 	aName.Insert(aPrefix, 0);
/*N*/ 
/*N*/ 	if (!Find(aName, SD_LT_FAMILY))
/*N*/ 	{
/*N*/ 		bCreated = sal_True;
/*N*/ 
/*N*/ 		pSheet = &Make(aName, SD_LT_FAMILY);
/*N*/ 		pSheet->SetHelpId( aHelpFile, HID_PSEUDOSHEET_TITLE );
/*N*/ 		pSheet->SetParent(String());
/*N*/ 		SfxItemSet& rTitleSet = pSheet->GetItemSet();
/*N*/ 		rTitleSet.Put(XLineStyleItem(XLINE_NONE));
/*N*/ 		rTitleSet.Put(XFillStyleItem(XFILL_NONE));
/*N*/ 		rTitleSet.Put(aSvxFontItem);
/*N*/ 		rTitleSet.Put(aSvxFontItemCJK);
/*N*/ 		rTitleSet.Put(aSvxFontItemCTL);
/*N*/ 		rTitleSet.Put(SvxPostureItem( ITALIC_NONE, EE_CHAR_ITALIC ) );
/*N*/ 		rTitleSet.Put(SvxPostureItem( ITALIC_NONE, EE_CHAR_ITALIC_CJK ) );
/*N*/ 		rTitleSet.Put(SvxPostureItem( ITALIC_NONE, EE_CHAR_ITALIC_CTL ) );
/*N*/ 		rTitleSet.Put(SvxWeightItem( WEIGHT_NORMAL, EE_CHAR_WEIGHT ) );
/*N*/ 		rTitleSet.Put(SvxWeightItem( WEIGHT_NORMAL, EE_CHAR_WEIGHT_CJK ) );
/*N*/ 		rTitleSet.Put(SvxWeightItem( WEIGHT_NORMAL, EE_CHAR_WEIGHT_CTL ) );
/*N*/ 		rTitleSet.Put(SvxFontHeightItem( 1552, 100, EE_CHAR_FONTHEIGHT ) );		            // 44 pt
/*N*/ 		rTitleSet.Put(SvxFontHeightItem( 1552, 100, EE_CHAR_FONTHEIGHT_CJK ) );		            // 44 pt
/*N*/ 		rTitleSet.Put(SvxFontHeightItem( 1552, 100, EE_CHAR_FONTHEIGHT_CTL ) );		            // 44 pt
/*N*/ 		rTitleSet.Put(SvxUnderlineItem(UNDERLINE_NONE));
/*N*/ 		rTitleSet.Put(SvxCrossedOutItem(STRIKEOUT_NONE));
/*N*/ 		rTitleSet.Put(SvxShadowedItem(FALSE));
/*N*/ 		rTitleSet.Put(SvxContourItem(FALSE));
/*N*/ 		rTitleSet.Put( SvxEmphasisMarkItem(EMPHASISMARK_NONE) );
/*N*/ 		rTitleSet.Put( SvxCharReliefItem(RELIEF_NONE) );
/*N*/ 		rTitleSet.Put(SvxColorItem( Color(COL_AUTO)));
/*N*/ 		rTitleSet.Put(SvxAdjustItem(SVX_ADJUST_CENTER));
/*N*/ 		rTitleSet.Put( SdrTextVertAdjustItem( SDRTEXTVERTADJUST_CENTER ) );
/*N*/ 		rTitleSet.Put( SfxUInt16Item(EE_PARA_BULLETSTATE, 0) );
/*N*/ 		aBulletFont.SetSize(Size(0,1552));					// 44 pt
/*N*/ 		PutNumBulletItem( pSheet, aBulletFont );
/*N*/ 	}
/*N*/ 
    /**************************************************************************
    * Untertitel
    * Aenderugen auch in AdjustLRSpaceItems() vornehmen!
    **************************************************************************/
/*N*/ 	aName = String(SdResId(STR_LAYOUT_SUBTITLE));
/*N*/ 	aName.Insert(aPrefix, 0);
/*N*/ 
/*N*/ 	if (!Find(aName, SD_LT_FAMILY))
/*N*/ 	{
/*N*/ 		bCreated = sal_True;
/*N*/ 
/*N*/ 		pSheet = &Make(aName, SD_LT_FAMILY);
/*N*/ 		pSheet->SetHelpId( aHelpFile, HID_PSEUDOSHEET_SUBTITLE );
/*N*/ 		pSheet->SetParent(String());
/*N*/ 		SfxItemSet& rSubtitleSet = pSheet->GetItemSet();
/*N*/ 		rSubtitleSet.Put(XLineStyleItem(XLINE_NONE));
/*N*/ 		rSubtitleSet.Put(XFillStyleItem(XFILL_NONE));
/*N*/ 		rSubtitleSet.Put(aSvxFontItem);
/*N*/ 		rSubtitleSet.Put(aSvxFontItemCJK);
/*N*/ 		rSubtitleSet.Put(aSvxFontItemCTL);
/*N*/ 		rSubtitleSet.Put(SvxPostureItem( ITALIC_NONE, EE_CHAR_ITALIC ) );
/*N*/ 		rSubtitleSet.Put(SvxPostureItem( ITALIC_NONE, EE_CHAR_ITALIC_CJK ) );
/*N*/ 		rSubtitleSet.Put(SvxPostureItem( ITALIC_NONE, EE_CHAR_ITALIC_CTL ) );
/*N*/ 		rSubtitleSet.Put(SvxWeightItem( WEIGHT_NORMAL, EE_CHAR_WEIGHT ) );
/*N*/ 		rSubtitleSet.Put(SvxWeightItem( WEIGHT_NORMAL, EE_CHAR_WEIGHT_CJK ) );
/*N*/ 		rSubtitleSet.Put(SvxWeightItem( WEIGHT_NORMAL, EE_CHAR_WEIGHT_CTL ) );
/*N*/ 		rSubtitleSet.Put( SvxFontHeightItem( 1129, 100, EE_CHAR_FONTHEIGHT ) );	    // 32 pt
/*N*/ 		rSubtitleSet.Put( SvxFontHeightItem( 1129, 100, EE_CHAR_FONTHEIGHT_CJK ) ); // 32 pt
/*N*/ 		rSubtitleSet.Put( SvxFontHeightItem( 1129, 100, EE_CHAR_FONTHEIGHT_CTL ) ); // 32 pt
/*N*/ 		rSubtitleSet.Put(SvxUnderlineItem(UNDERLINE_NONE));
/*N*/ 		rSubtitleSet.Put(SvxCrossedOutItem(STRIKEOUT_NONE));
/*N*/ 		rSubtitleSet.Put(SvxShadowedItem(FALSE));
/*N*/ 		rSubtitleSet.Put(SvxContourItem(FALSE));
/*N*/ 		rSubtitleSet.Put( SvxEmphasisMarkItem(EMPHASISMARK_NONE) );
/*N*/ 		rSubtitleSet.Put( SvxCharReliefItem(RELIEF_NONE) );
/*N*/ 		rSubtitleSet.Put(SvxColorItem( Color(COL_AUTO)));
/*N*/ 		rSubtitleSet.Put(SvxAdjustItem(SVX_ADJUST_CENTER));
/*N*/ 		rSubtitleSet.Put( SdrTextVertAdjustItem( SDRTEXTVERTADJUST_CENTER ) );
/*N*/ 		rSubtitleSet.Put( SfxUInt16Item(EE_PARA_BULLETSTATE, 0) );
/*N*/ 		aSvxLRSpaceItem.SetTxtLeft(0);
/*N*/ 		rSubtitleSet.Put(aSvxLRSpaceItem);
/*N*/ 		Font aBulletFont( GetBulletFont() );
/*N*/ 		aBulletFont.SetSize(Size(0, 1129));		// 32 pt
/*N*/ 		PutNumBulletItem( pSheet, aBulletFont );
/*N*/ 	}
/*N*/ 
    /**************************************************************************
    * Notizen
    **************************************************************************/
/*N*/ 	aName = String(SdResId(STR_LAYOUT_NOTES));
/*N*/ 	aName.Insert(aPrefix, 0);
/*N*/ 
/*N*/ 	if (!Find(aName, SD_LT_FAMILY))
/*N*/ 	{
/*N*/ 		bCreated = sal_True;
/*N*/ 
/*N*/ 		pSheet = &Make(aName, SD_LT_FAMILY);
/*N*/ 		pSheet->SetHelpId( aHelpFile, HID_PSEUDOSHEET_NOTES );
/*N*/ 		pSheet->SetParent(String());
/*N*/ 		SfxItemSet& rNotesSet = pSheet->GetItemSet();
/*N*/ 		rNotesSet.Put(XLineStyleItem(XLINE_NONE));
/*N*/ 		rNotesSet.Put(XFillStyleItem(XFILL_NONE));
/*N*/ 		rNotesSet.Put(aSvxFontItem);
/*N*/ 		rNotesSet.Put(aSvxFontItemCJK);
/*N*/ 		rNotesSet.Put(aSvxFontItemCTL);
/*N*/ 		rNotesSet.Put( SvxPostureItem( ITALIC_NONE, EE_CHAR_ITALIC ) );
/*N*/ 		rNotesSet.Put( SvxPostureItem( ITALIC_NONE, EE_CHAR_ITALIC_CJK ) );
/*N*/ 		rNotesSet.Put( SvxPostureItem( ITALIC_NONE, EE_CHAR_ITALIC_CTL ) );
/*N*/ 		rNotesSet.Put( SvxWeightItem( WEIGHT_NORMAL, EE_CHAR_WEIGHT ) );
/*N*/ 		rNotesSet.Put( SvxWeightItem( WEIGHT_NORMAL, EE_CHAR_WEIGHT_CJK ) );
/*N*/ 		rNotesSet.Put( SvxWeightItem( WEIGHT_NORMAL, EE_CHAR_WEIGHT_CTL ) );
/*N*/ 		rNotesSet.Put( SvxFontHeightItem( 705, 100, EE_CHAR_FONTHEIGHT ) );	    // 20 pt
/*N*/ 		rNotesSet.Put( SvxFontHeightItem( 705, 100, EE_CHAR_FONTHEIGHT_CJK ) ); // 20 pt
/*N*/ 		rNotesSet.Put( SvxFontHeightItem( 705, 100, EE_CHAR_FONTHEIGHT_CTL ) ); // 20 pt
/*N*/ 		rNotesSet.Put( SvxUnderlineItem(UNDERLINE_NONE) );
/*N*/ 		rNotesSet.Put( SvxCrossedOutItem(STRIKEOUT_NONE) );
/*N*/ 		rNotesSet.Put( SvxShadowedItem(FALSE) );
/*N*/ 		rNotesSet.Put( SvxContourItem(FALSE) );
/*N*/ 		rNotesSet.Put( SvxEmphasisMarkItem(EMPHASISMARK_NONE) );
/*N*/ 		rNotesSet.Put( SvxCharReliefItem(RELIEF_NONE) );
/*N*/ 		rNotesSet.Put( SvxColorItem( Color(COL_AUTO)) );
/*N*/ 		rNotesSet.Put( SfxUInt16Item(EE_PARA_BULLETSTATE, 0) );
/*N*/ 		rNotesSet.Put( SvxLRSpaceItem( 0, 0, 600, -600 ) );
/*N*/ 
/*N*/ 		SvxNumBulletItem aNumBullet( (const SvxNumBulletItem&) rNotesSet.Get(EE_PARA_NUMBULLET) );
/*N*/ 
/*N*/ 		EditEngine::ImportBulletItem( aNumBullet, 0, NULL,
/*N*/ 								&(const SvxLRSpaceItem&) rNotesSet.Get( EE_PARA_LRSPACE ) );
/*N*/ 
/*N*/ 		( (SfxItemSet&) rNotesSet).Put( aNumBullet );
/*N*/ 
/*N*/ 	}
/*N*/ 
    /**************************************************************************
    * Hintergrundobjekte
    **************************************************************************/
/*N*/ 	aName = String(SdResId(STR_LAYOUT_BACKGROUNDOBJECTS));
/*N*/ 	aName.Insert(aPrefix, 0);
/*N*/ 
/*N*/ 	if (!Find(aName, SD_LT_FAMILY))
/*N*/ 	{
/*N*/ 		bCreated = sal_True;
/*N*/ 
/*N*/ 		pSheet = &Make(aName, SD_LT_FAMILY);
/*N*/ 		pSheet->SetHelpId( aHelpFile, HID_PSEUDOSHEET_BACKGROUNDOBJECTS );
/*N*/ 		pSheet->SetParent(String());
/*N*/ 		SfxItemSet& rBackgroundObjectsSet = pSheet->GetItemSet();
/*N*/ 		rBackgroundObjectsSet.Put(SdrShadowItem(FALSE));
/*N*/ 		rBackgroundObjectsSet.Put(SdrShadowColorItem(String(), Color(COL_GRAY)));
/*N*/ 		rBackgroundObjectsSet.Put(SdrShadowXDistItem(300));	// 3 mm Schattendistanz
/*N*/ 		rBackgroundObjectsSet.Put(SdrShadowYDistItem(300));
/*N*/ 	}
/*N*/ 
    /**************************************************************************
    * Hintergrund
    **************************************************************************/
/*N*/ 	aName = String(SdResId(STR_LAYOUT_BACKGROUND));
/*N*/ 	aName.Insert(aPrefix, 0);
/*N*/ 
/*N*/ 	if (!Find(aName, SD_LT_FAMILY))
/*N*/ 	{
/*N*/ 		bCreated = sal_True;
/*N*/ 
/*N*/ 		pSheet = &Make(aName, SD_LT_FAMILY);
/*N*/ 		pSheet->SetHelpId( aHelpFile, HID_PSEUDOSHEET_BACKGROUND );
/*N*/ 		pSheet->SetParent(String());
/*N*/ 		SfxItemSet& rBackgroundSet = pSheet->GetItemSet();
/*N*/ 		rBackgroundSet.Put(XLineStyleItem(XLINE_NONE));
/*N*/ 		rBackgroundSet.Put(XFillStyleItem(XFILL_NONE));
/*N*/ 	}
/*N*/ 
/*N*/ 	DBG_ASSERT( !bCheck || !bCreated, "missing layout style sheets detected!" );
/*N*/ }

/*************************************************************************
|*
|* StyleSheets des genannten Praesentationslayouts loeschen
|*
\************************************************************************/

//STRIP001 void SdStyleSheetPool::EraseLayoutStyleSheets(const String& rLayoutName)
//STRIP001 {
//STRIP001 	SfxStyleSheetBase* pSheet = NULL;
//STRIP001 
//STRIP001 	List* pNameList = CreateLayoutSheetNames(rLayoutName);
//STRIP001 
//STRIP001 	String* pName = (String*)pNameList->First();
//STRIP001 	while (pName)
//STRIP001 	{
//STRIP001 		pSheet = Find(*pName, SD_LT_FAMILY);
//STRIP001 		DBG_ASSERT(pSheet, "EraseLayoutStyleSheets: Vorlage nicht gefunden");
//STRIP001 		if (pSheet)
//STRIP001 			Erase(pSheet);
//STRIP001 		delete pName;
//STRIP001 		pName = (String*)pNameList->Next();
//STRIP001 	}
//STRIP001 	delete pNameList;
//STRIP001 }


/*************************************************************************
|*
|* Graphik-StyleSheets  aus dem Quellpool in diesen Pool kopieren
|*
|* (rSourcePool kann nicht const sein, weil SfxStyleSheetPoolBase::Find
|*	nicht const ist)
|*
\************************************************************************/

//STRIP001 void SdStyleSheetPool::CopyGraphicSheets(SdStyleSheetPool& rSourcePool)
//STRIP001 {
//STRIP001 	ULONG nCount = rSourcePool.aStyles.Count();
//STRIP001 
//STRIP001 	std::vector< std::pair< SfxStyleSheetBase*, String > > aNewStyles;
//STRIP001 
//STRIP001 	for (ULONG n = 0; n < nCount; n++)
//STRIP001 	{
//STRIP001 		SfxStyleSheet* pSheet = (SfxStyleSheet*) rSourcePool.aStyles.GetObject(n);
//STRIP001 
//STRIP001 		if( pSheet->GetFamily() == SFX_STYLE_FAMILY_PARA )
//STRIP001 		{
//STRIP001 			String aName( pSheet->GetName() );
//STRIP001 			if ( !Find( aName, SFX_STYLE_FAMILY_PARA ) )
//STRIP001 			{
//STRIP001 				SfxStyleSheetBase& rNewSheet = Make( aName, SFX_STYLE_FAMILY_PARA );
//STRIP001 
//STRIP001                 // #91588# Also set parent relation for copied style sheets
//STRIP001                 String aParent( pSheet->GetParent() );
//STRIP001                 if( aParent.Len() )
//STRIP001 					aNewStyles.push_back( std::pair< SfxStyleSheetBase*, String >( &rNewSheet, aParent ) );
//STRIP001 
//STRIP001 				rNewSheet.GetItemSet().Put( pSheet->GetItemSet() );
//STRIP001 			}
//STRIP001 		}
//STRIP001 	}
//STRIP001 
//STRIP001 	// set parents on newly added stylesheets
//STRIP001 	std::vector< std::pair< SfxStyleSheetBase*, String > >::iterator aIter;
//STRIP001 	for( aIter = aNewStyles.begin(); aIter != aNewStyles.end(); aIter++ )
//STRIP001 	{
//STRIP001         DBG_ASSERT( rSourcePool.Find( (*aIter).second, SFX_STYLE_FAMILY_PARA ), "StyleSheet has invalid parent: Family mismatch" );
//STRIP001 		(*aIter).first->SetParent( (*aIter).second );
//STRIP001 	}
//STRIP001 }


/*************************************************************************
|*
|* StyleSheets des genannten Praesentationslayouts aus dem Quellpool in diesen
|* Pool kopieren. Kopiert werden nur solche StyleSheets, die in diesem Pool
|* noch nicht vorhanden sind.
|* pCreatedSheets wird - wenn ungleich NULL - mit Zeigern auf die erzeugten
|* StyleSheets gefuellt.
|*
|* (rSourcePool kann nicht const sein, weil SfxStyleSheetPoolBase::Find
|*	nicht const ist)
|*
\************************************************************************/

//STRIP001 void SdStyleSheetPool::CopyLayoutSheets(const String& rLayoutName,
//STRIP001 										SdStyleSheetPool& rSourcePool,
//STRIP001 										List* pCreatedSheets)
//STRIP001 {
//STRIP001 	SfxStyleSheetBase* pSheet = NULL;
//STRIP001 
//STRIP001 	String aOutlineTag(SdResId(STR_LAYOUT_OUTLINE));
//STRIP001 
//STRIP001 	List* pNameList = CreateLayoutSheetNames(rLayoutName);
//STRIP001 
//STRIP001 	String* pName = (String*)pNameList->First();
//STRIP001 	while (pName)
//STRIP001 	{
//STRIP001 		pSheet = Find(*pName, SD_LT_FAMILY);
//STRIP001 		if (!pSheet)
//STRIP001 		{
//STRIP001 			SfxStyleSheetBase* pSourceSheet =
//STRIP001 								rSourcePool.Find(*pName, SD_LT_FAMILY);
//STRIP001 			DBG_ASSERT(pSourceSheet,
//STRIP001 					   "CopyLayoutSheets: Quellvorlage nicht gefunden");
//STRIP001 			if (pSourceSheet)	// falls einer mit Methusalem-Doks. ankommt
//STRIP001 			{
//STRIP001 				SfxStyleSheetBase& rNewSheet = Make(*pName, SD_LT_FAMILY);
//STRIP001 				rNewSheet.GetItemSet().Put(pSourceSheet->GetItemSet());
//STRIP001 				if (pCreatedSheets)
//STRIP001 					pCreatedSheets->Insert(&rNewSheet, LIST_APPEND);
//STRIP001 			}
//STRIP001 		}
//STRIP001 		delete pName;
//STRIP001 		pName = (String*)pNameList->Next();
//STRIP001 	}
//STRIP001 	delete pNameList;
//STRIP001 
//STRIP001 	// Sonderbehandlung fuer Gliederungsvorlagen: Parentbeziehungen aufbauen
//STRIP001 	List* pOutlineSheets = CreateOutlineSheetList(rLayoutName);
//STRIP001 	SfxStyleSheetBase* pParent = (SfxStyleSheetBase*)pOutlineSheets->First();
//STRIP001 	pSheet = (SfxStyleSheetBase*)pOutlineSheets->Next();
//STRIP001 	while (pSheet)
//STRIP001 	{
//STRIP001 		// kein Parent?
//STRIP001 		if (pSheet->GetParent().Len() == 0)
//STRIP001 			pSheet->SetParent(pParent->GetName());
//STRIP001 		pParent = pSheet;
//STRIP001 		pSheet = (SfxStyleSheetBase*)pOutlineSheets->Next();
//STRIP001 	}
//STRIP001 	delete pOutlineSheets;
//STRIP001 }

/*************************************************************************
|*
|* Liste mit den Namen der Praesentationsvorlagen eines Layouts erzeugen.
|* Die Liste und die enthaltenen Strings gehoeren dem Caller!
|*
\************************************************************************/

//STRIP001 List* SdStyleSheetPool::CreateLayoutSheetNames(const String& rLayoutName) const
//STRIP001 {
//STRIP001 	String aPrefix(rLayoutName);
//STRIP001 	String aSep( RTL_CONSTASCII_USTRINGPARAM( SD_LT_SEPARATOR ));
//STRIP001 	aPrefix.Insert(aSep);
//STRIP001 
//STRIP001 	List* pNameList = new List;
//STRIP001 
//STRIP001 	String aName(SdResId(STR_LAYOUT_OUTLINE));
//STRIP001 	String* pName = NULL;
//STRIP001 
//STRIP001 	for (USHORT nLevel = 1; nLevel < 10; nLevel++)
//STRIP001 	{
//STRIP001 		pName = new String(aName);
//STRIP001 		pName->Append( sal_Unicode( ' ' ));
//STRIP001 		pName->Append( String::CreateFromInt32( sal_Int32( nLevel )));
//STRIP001 		pName->Insert(aPrefix, 0);
//STRIP001 		pNameList->Insert(pName, LIST_APPEND);
//STRIP001 	}
//STRIP001 
//STRIP001 	pName = new String(SdResId(STR_LAYOUT_TITLE));
//STRIP001 	pName->Insert(aPrefix, 0);
//STRIP001 	pNameList->Insert(pName, LIST_APPEND);
//STRIP001 
//STRIP001 	pName = new String(SdResId(STR_LAYOUT_SUBTITLE));
//STRIP001 	pName->Insert(aPrefix, 0);
//STRIP001 	pNameList->Insert(pName, LIST_APPEND);
//STRIP001 
//STRIP001 	pName = new String(SdResId(STR_LAYOUT_NOTES));
//STRIP001 	pName->Insert(aPrefix, 0);
//STRIP001 	pNameList->Insert(pName, LIST_APPEND);
//STRIP001 
//STRIP001 	pName = new String(SdResId(STR_LAYOUT_BACKGROUNDOBJECTS));
//STRIP001 	pName->Insert(aPrefix, 0);
//STRIP001 	pNameList->Insert(pName, LIST_APPEND);
//STRIP001 
//STRIP001 	pName = new String(SdResId(STR_LAYOUT_BACKGROUND));
//STRIP001 	pName->Insert(aPrefix, 0);
//STRIP001 	pNameList->Insert(pName, LIST_APPEND);
//STRIP001 
//STRIP001 	return pNameList;
//STRIP001 }

/*************************************************************************
|*
|* Liste mit Zeigern auf Praesentationsvorlagen eines Layouts erzeugen.
|* Die Liste gehoert dem Caller!
|*
\************************************************************************/

//STRIP001 List* SdStyleSheetPool::CreateLayoutSheetList(const String& rLayoutName)
//STRIP001 {
//STRIP001 	List* pList = new List; 			// die kriegt der Caller
//STRIP001 	String aLayoutNameWithSep(rLayoutName);
//STRIP001 	aLayoutNameWithSep.AppendAscii( RTL_CONSTASCII_STRINGPARAM( SD_LT_SEPARATOR ));
//STRIP001 	USHORT nLen = aLayoutNameWithSep.Len();
//STRIP001 
//STRIP001 	SfxStyleSheetIterator aIter(this, SD_LT_FAMILY);
//STRIP001 	SfxStyleSheetBase* pSheet = aIter.First();
//STRIP001 
//STRIP001 	while (pSheet)
//STRIP001 	{
//STRIP001 		if (pSheet->GetName().Match(aLayoutNameWithSep) == nLen)
//STRIP001 			pList->Insert(pSheet, LIST_APPEND);
//STRIP001 		pSheet = aIter.Next();
//STRIP001 	}
//STRIP001 	return pList;
//STRIP001 }

/*************************************************************************
|*
|* ggfs. PseudoStyleSheets erzeugen
|*
\************************************************************************/

/*N*/ void SdStyleSheetPool::CreatePseudosIfNecessary()
/*N*/ {
/*N*/ 	String aName;
/*N*/ 	String aHelpFile;
/*N*/ 	SfxStyleSheetBase* pSheet = NULL;
/*N*/ 	SfxStyleSheetBase* pParent = NULL;
/*N*/ 
/*N*/ 	//USHORT nMask = SFXSTYLEBIT_ALL & ~SFXSTYLEBIT_USERDEF;
/*N*/ 	USHORT nMask = SFXSTYLEBIT_USED;
/*N*/ 
/*N*/ 	aName = String(SdResId(STR_PSEUDOSHEET_TITLE));
/*N*/ 	if (!(pSheet = Find(aName, SFX_STYLE_FAMILY_PSEUDO)))
/*N*/ 	{
/*N*/ 		pSheet = &Make(aName, SFX_STYLE_FAMILY_PSEUDO, nMask);
/*N*/ 		pSheet->SetParent( String() );
/*N*/ 		((SfxStyleSheet*)pSheet)->StartListening(*this);
/*N*/ 	}
/*N*/ 	pSheet->SetHelpId( aHelpFile, HID_PSEUDOSHEET_TITLE );
/*N*/ 
/*N*/ 	aName = String(SdResId(STR_PSEUDOSHEET_SUBTITLE));
/*N*/ 	if (!(pSheet = Find(aName, SFX_STYLE_FAMILY_PSEUDO)))
/*N*/ 	{
/*N*/ 		pSheet = &Make(aName, SFX_STYLE_FAMILY_PSEUDO, nMask);
/*N*/ 		pSheet->SetParent(String());
/*N*/ 		((SfxStyleSheet*)pSheet)->StartListening(*this);
/*N*/ 	}
/*N*/ 	pSheet->SetHelpId( aHelpFile, HID_PSEUDOSHEET_SUBTITLE );
/*N*/ 
/*N*/ 	aName = String(SdResId(STR_PSEUDOSHEET_BACKGROUNDOBJECTS));
/*N*/ 	if (!(pSheet = Find(aName, SFX_STYLE_FAMILY_PSEUDO)))
/*N*/ 	{
/*N*/ 		pSheet = &Make(aName, SFX_STYLE_FAMILY_PSEUDO, nMask);
/*N*/ 		pSheet->SetParent( String() );
/*N*/ 		((SfxStyleSheet*)pSheet)->StartListening(*this);
/*N*/ 	}
/*N*/ 	pSheet->SetHelpId( aHelpFile, HID_PSEUDOSHEET_BACKGROUNDOBJECTS );
/*N*/ 
/*N*/ 	aName = String(SdResId(STR_PSEUDOSHEET_BACKGROUND));
/*N*/ 	if (!(pSheet = Find(aName, SFX_STYLE_FAMILY_PSEUDO)))
/*N*/ 	{
/*N*/ 		pSheet = &Make(aName, SFX_STYLE_FAMILY_PSEUDO, nMask);
/*N*/ 		pSheet->SetParent( String() );
/*N*/ 		((SfxStyleSheet*)pSheet)->StartListening(*this);
/*N*/ 	}
/*N*/ 	pSheet->SetHelpId( aHelpFile, HID_PSEUDOSHEET_BACKGROUND );
/*N*/ 
/*N*/ 	aName = String(SdResId(STR_PSEUDOSHEET_NOTES));
/*N*/ 	if (!(pSheet = Find(aName, SFX_STYLE_FAMILY_PSEUDO)))
/*N*/ 	{
/*N*/ 		pSheet = &Make(aName, SFX_STYLE_FAMILY_PSEUDO, nMask);
/*N*/ 		pSheet->SetParent( String() );
/*N*/ 		((SfxStyleSheet*)pSheet)->StartListening(*this);
/*N*/ 	}
/*N*/ 	pSheet->SetHelpId( aHelpFile, HID_PSEUDOSHEET_NOTES );
/*N*/ 
/*N*/ 	pParent = NULL;
/*N*/ 	SetSearchMask(SFX_STYLE_FAMILY_PSEUDO);
/*N*/ 	aName = String(SdResId(STR_PSEUDOSHEET_OUTLINE));
/*N*/ 	for (USHORT nLevel = 1; nLevel < 10; nLevel++)
/*N*/ 	{
/*N*/ 		String aLevelName(aName);
/*N*/ 		aLevelName.Append( sal_Unicode( ' ' ));
/*N*/ 		aLevelName.Append( String::CreateFromInt32( sal_Int32( nLevel )));
/*N*/ 
/*N*/ 		if (!(pSheet = Find(aLevelName, SFX_STYLE_FAMILY_PSEUDO)))
/*N*/ 		{
/*N*/ 			pSheet = &Make(aLevelName, SFX_STYLE_FAMILY_PSEUDO, nMask);
/*N*/ 
/*N*/ 			if (pSheet)
/*N*/ 			{
/*N*/ 				if (pParent)
/*N*/ 					pSheet->SetParent(pParent->GetName());
/*N*/ 				pParent = pSheet;
/*N*/ 				((SfxStyleSheet*)pSheet)->StartListening(*this);
/*N*/ 			}
/*N*/ 		}
/*N*/ 		pSheet->SetHelpId( aHelpFile, HID_PSEUDOSHEET_OUTLINE + nLevel );
/*N*/ 	}
/*N*/ }


/*************************************************************************
|*
|* Standard-Styles den richtigen Namen in der Programm-Sprache geben
|*
\************************************************************************/

/*N*/ void SdStyleSheetPool::UpdateStdNames()
/*N*/ {
/*N*/ 	BOOL bNewHelpIds = FALSE;
/*N*/ 	String aHelpFile;
/*N*/ 	ULONG  nCount = aStyles.Count();
/*N*/ 	List* pEraseList = NULL;
/*N*/ 
/*N*/ 	for( ULONG n=0; n < nCount; n++ )
/*N*/ 	{
/*N*/ 		SfxStyleSheetBase* pStyle = aStyles.GetObject( n );
/*N*/ 
/*N*/ 		if( !pStyle->IsUserDefined() )
/*N*/ 		{
/*N*/ 			String aOldName		= pStyle->GetName();
/*N*/ 			ULONG nHelpId		= pStyle->GetHelpId( aHelpFile );
/*N*/ 			SfxStyleFamily eFam	= pStyle->GetFamily();
/*N*/ 
/*N*/ 			BOOL bHelpKnown = TRUE;
/*N*/ 			String aNewName;
/*N*/ 			USHORT nNameId = 0;
/*N*/ 			switch( nHelpId )
/*N*/ 			{
/*N*/ 				case HID_STANDARD_STYLESHEET_NAME:	nNameId = STR_STANDARD_STYLESHEET_NAME;	break;
/*N*/ 				case HID_POOLSHEET_OBJWITHARROW:	nNameId = STR_POOLSHEET_OBJWITHARROW;	break;
/*N*/ 				case HID_POOLSHEET_OBJWITHSHADOW:	nNameId = STR_POOLSHEET_OBJWITHSHADOW;	break;
/*N*/ 				case HID_POOLSHEET_OBJWITHOUTFILL:	nNameId = STR_POOLSHEET_OBJWITHOUTFILL;	break;
/*N*/ 				case HID_POOLSHEET_TEXT:			nNameId = STR_POOLSHEET_TEXT;			break;
/*N*/ 				case HID_POOLSHEET_TEXTBODY:		nNameId = STR_POOLSHEET_TEXTBODY;		break;
/*N*/ 				case HID_POOLSHEET_TEXTBODY_JUSTIFY:nNameId = STR_POOLSHEET_TEXTBODY_JUSTIFY;break;
/*N*/ 				case HID_POOLSHEET_TEXTBODY_INDENT:	nNameId = STR_POOLSHEET_TEXTBODY_INDENT;break;
/*N*/ 				case HID_POOLSHEET_TITLE:			nNameId = STR_POOLSHEET_TITLE;			break;
/*N*/ 				case HID_POOLSHEET_TITLE1:			nNameId = STR_POOLSHEET_TITLE1;			break;
/*N*/ 				case HID_POOLSHEET_TITLE2:			nNameId = STR_POOLSHEET_TITLE2;			break;
/*N*/ 				case HID_POOLSHEET_HEADLINE:		nNameId = STR_POOLSHEET_HEADLINE;		break;
/*N*/ 				case HID_POOLSHEET_HEADLINE1:		nNameId = STR_POOLSHEET_HEADLINE1;		break;
/*N*/ 				case HID_POOLSHEET_HEADLINE2:		nNameId = STR_POOLSHEET_HEADLINE2;		break;
/*N*/ 				case HID_POOLSHEET_MEASURE:			nNameId = STR_POOLSHEET_MEASURE;		break;
/*N*/ 
/*N*/ 				case HID_PSEUDOSHEET_TITLE:			nNameId = STR_PSEUDOSHEET_TITLE; 		break;
/*N*/ 				case HID_PSEUDOSHEET_SUBTITLE:	 	nNameId = STR_PSEUDOSHEET_SUBTITLE; 	break;
/*N*/ 				case HID_PSEUDOSHEET_OUTLINE1:
/*N*/ 				case HID_PSEUDOSHEET_OUTLINE2:
/*N*/ 				case HID_PSEUDOSHEET_OUTLINE3:
/*N*/ 				case HID_PSEUDOSHEET_OUTLINE4:
/*N*/ 				case HID_PSEUDOSHEET_OUTLINE5:
/*N*/ 				case HID_PSEUDOSHEET_OUTLINE6:
/*N*/ 				case HID_PSEUDOSHEET_OUTLINE7:
/*N*/ 				case HID_PSEUDOSHEET_OUTLINE8:
/*N*/ 				case HID_PSEUDOSHEET_OUTLINE9:		nNameId = STR_PSEUDOSHEET_OUTLINE; 		break;
/*N*/ 				case HID_PSEUDOSHEET_BACKGROUNDOBJECTS:	nNameId = STR_PSEUDOSHEET_BACKGROUNDOBJECTS; break;
/*N*/ 				case HID_PSEUDOSHEET_BACKGROUND:	nNameId = STR_PSEUDOSHEET_BACKGROUND; 	break;
/*N*/ 				case HID_PSEUDOSHEET_NOTES:			nNameId = STR_PSEUDOSHEET_NOTES; 		break;
/*N*/ 
/*N*/ 				default:
/*N*/ 					// 0 oder falsche (alte) HelpId
/*N*/ 					bHelpKnown = FALSE;
/*N*/ 			}
/*N*/ 			if( bHelpKnown )
/*N*/ 			{
/*N*/ 				if( nNameId )
/*N*/ 				{
/*N*/ 					aNewName = String( SdResId( nNameId ) );
/*N*/ 					if( nNameId == STR_PSEUDOSHEET_OUTLINE )
/*N*/ 					{
/*N*/ 						aNewName.Append( sal_Unicode( ' ' ));
/*N*/ 						aNewName.Append( String::CreateFromInt32( sal_Int32( nHelpId - HID_PSEUDOSHEET_OUTLINE )));
/*N*/ 					}
/*N*/ 				}
/*N*/ 
/*N*/ 				if( aNewName.Len() && aNewName != aOldName )
/*N*/ 				{
/*N*/ 					SfxStyleSheetBase* pSheetFound = Find( aNewName, eFam );
/*N*/ 
/*N*/ 					if ( !pSheetFound )
/*N*/ 					{
/*N*/ 						// Sheet existiert noch nicht: Altes Sheet wird umbenannt
/*N*/ 						pStyle->SetName( aNewName );	// setzt auch Parents um
/*N*/ 					}
/*N*/ 					else
/*N*/ 					{
/*N*/ 						// Sheet existiert schon: Altes Sheet muss entfernt werden
/*N*/ 						if( !pEraseList )
/*N*/ 						{
/*N*/ 							pEraseList = new List();
/*N*/ 						}
/*N*/ 
/*N*/ 						pEraseList->Insert( pStyle );
/*N*/ 					}
/*N*/ 				}
/*N*/ 			}
/*N*/ 			else
/*N*/ 			{
/*N*/ 				//	falsche oder keine HelpId -> neue generieren
/*N*/ 
/*N*/ 				DBG_WARNING("Default-Vorlage mit falscher oder keiner HelpId");
/*N*/ 
/*N*/ 				// Da bisher nur deutsche Dokumente erzeugt worden sein koennen,
/*N*/ 				// kann hier auch der deutsche Text abgefragt werden, damit man
/*N*/ 				// nicht in einer anderssprachigen Version auf die deutsche
/*N*/ 				// Version zurueckgreifen muss!
/*N*/ 
/*N*/ 				USHORT nNewId = 0;
/*N*/ 				if( eFam == SFX_STYLE_FAMILY_PARA )
/*N*/ 				{
/*N*/ 					if( aOldName == String( SdResId( STR_STANDARD_STYLESHEET_NAME ) ) ||
/*N*/ 						aOldName.EqualsAscii( "Standard", 0, RTL_CONSTASCII_LENGTH( "Standard" )) )
/*N*/ 						nNewId = HID_STANDARD_STYLESHEET_NAME;
/*N*/ 					else if( aOldName == String( SdResId( STR_POOLSHEET_OBJWITHARROW ) ) ||
/*N*/ 						aOldName.EqualsAscii( "Objekt mit Pfeilspitze", 0, RTL_CONSTASCII_LENGTH( "Objekt mit Pfeilspitze" )) )
/*N*/ 						nNewId = HID_POOLSHEET_OBJWITHARROW;
/*N*/ 					else if( aOldName == String( SdResId( STR_POOLSHEET_OBJWITHSHADOW ) ) ||
/*N*/ 						aOldName.EqualsAscii( "Objekt mit Schatten", 0, RTL_CONSTASCII_LENGTH( "Objekt mit Schatten" )) )
/*N*/ 						nNewId = HID_POOLSHEET_OBJWITHSHADOW;
/*N*/ 					else if( aOldName == String( SdResId( STR_POOLSHEET_OBJWITHOUTFILL ) ) ||
/*N*/ 						aOldName == String( SdResId( STR_POOLSHEET_OBJWITHOUTFILL_NT ) ) )
/*N*/ 						//aOldName.EqualsAscii( "Objekt ohne F�llung", 0, RTL_CONSTASCII_LENGTH( "Objekt ohne F�llung" )) )
/*N*/ 						nNewId = HID_POOLSHEET_OBJWITHOUTFILL;
/*N*/ 					else if( aOldName == String( SdResId( STR_POOLSHEET_TEXT ) ) ||
/*N*/ 						aOldName.EqualsAscii( "Text", 0, RTL_CONSTASCII_LENGTH( "Text" )) )
/*N*/ 						nNewId = HID_POOLSHEET_TEXT;
/*N*/ 					else if( aOldName == String( SdResId( STR_POOLSHEET_TEXTBODY ) ) ||
/*N*/ 						aOldName == String( SdResId( STR_POOLSHEET_TEXTBODY_NT ) ) )
/*N*/ 						//aOldName.EqualsAscii( "Textk�rper", 0, RTL_CONSTASCII_LENGTH( "Textk�rper" )) )
/*N*/ 						nNewId = HID_POOLSHEET_TEXTBODY;
/*N*/ 					else if( aOldName == String( SdResId( STR_POOLSHEET_TEXTBODY_JUSTIFY ) ) ||
/*N*/ 						aOldName == String( SdResId( STR_POOLSHEET_TEXTBODY_JUSTIFY_NT ) ) )
/*N*/ 						//aOldName.EqualsAscii( "Textk�rper Blocksatz", 0, RTL_CONSTASCII_LENGTH( "Textk�rper Blocksatz" )) )
/*N*/ 						nNewId = HID_POOLSHEET_TEXTBODY_JUSTIFY;
/*N*/ 					else if( aOldName == String( SdResId( STR_POOLSHEET_TEXTBODY_INDENT ) ) ||
/*N*/ 						aOldName == String( SdResId( STR_POOLSHEET_TEXTBODY_INDENT_NT ) ) )
/*N*/ 						//aOldName.EqualsAscii( "Textk�rper Einzug", 0, RTL_CONSTASCII_LENGTH( "Textk�rper Einzug" )) )
/*N*/ 						nNewId = HID_POOLSHEET_TEXTBODY_INDENT;
/*N*/ 					else if( aOldName == String( SdResId( STR_POOLSHEET_TITLE ) ) ||
/*N*/ 						aOldName.EqualsAscii( "Titel", 0, RTL_CONSTASCII_LENGTH( "Titel" )) )
/*N*/ 						nNewId = HID_POOLSHEET_TITLE;
/*N*/ 					else if( aOldName == String( SdResId( STR_POOLSHEET_TITLE1 ) ) ||
/*N*/ 						aOldName.EqualsAscii( "Titel1", 0, RTL_CONSTASCII_LENGTH( "Titel1" )) )
/*N*/ 						nNewId = HID_POOLSHEET_TITLE1;
/*N*/ 					else if( aOldName == String( SdResId( STR_POOLSHEET_TITLE2 ) ) ||
/*N*/ 						aOldName.EqualsAscii( "Titel2", 0, RTL_CONSTASCII_LENGTH( "Titel2" )) )
/*N*/ 						nNewId = HID_POOLSHEET_TITLE2;
/*N*/ 					else if( aOldName == String( SdResId( STR_POOLSHEET_HEADLINE ) ) ||
/*N*/ 						aOldName == String( SdResId( STR_POOLSHEET_HEADLINE_NT ) ) )
/*N*/ 						//aOldName.EqualsAscii( "�berschrift", 0, RTL_CONSTASCII_LENGTH( "�berschrift" )) )
/*N*/ 						nNewId = HID_POOLSHEET_HEADLINE;
/*N*/ 					else if( aOldName == String( SdResId( STR_POOLSHEET_HEADLINE1 ) ) ||
/*N*/ 						aOldName == String( SdResId( STR_POOLSHEET_HEADLINE1_NT ) ) )
/*N*/ 						//aOldName.EqualsAscii( "�berschrift1", 0, RTL_CONSTASCII_LENGTH( "�berschrift1" )) )
/*N*/ 						nNewId = HID_POOLSHEET_HEADLINE1;
/*N*/ 					else if( aOldName == String( SdResId( STR_POOLSHEET_HEADLINE2 ) ) ||
/*N*/ 						aOldName == String( SdResId( STR_POOLSHEET_HEADLINE2_NT ) ) )
/*N*/ 						//aOldName.EqualsAscii( "�berschrift2", 0, RTL_CONSTASCII_LENGTH( "�berschrift2" )) )
/*N*/ 						nNewId = HID_POOLSHEET_HEADLINE2;
/*N*/ 					else if( aOldName == String( SdResId( STR_POOLSHEET_MEASURE ) ) ||
/*N*/ 						aOldName == String( SdResId( STR_POOLSHEET_MEASURE_NT ) ) )
/*N*/ 						//aOldName.EqualsAscii( "Ma�linie", 0, RTL_CONSTASCII_LENGTH( "Ma�linie" )) )
/*N*/ 						nNewId = HID_POOLSHEET_MEASURE;
/*N*/ 				}
/*N*/ 				else if( eFam == SFX_STYLE_FAMILY_PSEUDO )
/*N*/ 				{
/*N*/ 					String aStr( SdResId( STR_PSEUDOSHEET_OUTLINE ) );
/*N*/ 					aStr.Append( sal_Unicode( ' ' ));
/*N*/ 					String aStr2( RTL_CONSTASCII_USTRINGPARAM( "Gliederung " ));
/*N*/ 					sal_Int32 nNumber = 0;
/*N*/ 
/*N*/ 					if( aOldName == String( SdResId( STR_PSEUDOSHEET_TITLE ) ) ||
/*N*/ 						aOldName.EqualsAscii( "Titel", 0, RTL_CONSTASCII_LENGTH( "Titel" )))
/*N*/ 						nNewId = HID_PSEUDOSHEET_TITLE;
/*N*/ 					else if( aOldName == String( SdResId( STR_PSEUDOSHEET_SUBTITLE ) ) ||
/*N*/ 						aOldName.EqualsAscii( "Untertitel", 0, RTL_CONSTASCII_LENGTH( "Untertitel" )) )
/*N*/ 						nNewId = HID_PSEUDOSHEET_SUBTITLE;
/*N*/ 					else if( aOldName == String( SdResId( STR_PSEUDOSHEET_BACKGROUNDOBJECTS ) ) ||
/*N*/ 						aOldName.EqualsAscii( "Hintergrundobjekte", 0, RTL_CONSTASCII_LENGTH( "Hintergrundobjekte" )) )
/*N*/ 						nNewId = HID_PSEUDOSHEET_BACKGROUNDOBJECTS;
/*N*/ 					else if( aOldName == String( SdResId( STR_PSEUDOSHEET_BACKGROUND ) ) ||
/*N*/ 						aOldName.EqualsAscii( "Hintergrund", 0, RTL_CONSTASCII_LENGTH( "Hintergrund" )) )
/*N*/ 						nNewId = HID_PSEUDOSHEET_BACKGROUND;
/*N*/ 					else if( aOldName == String( SdResId( STR_PSEUDOSHEET_NOTES ) ) ||
/*N*/ 						aOldName.EqualsAscii( "Notizen", 0, RTL_CONSTASCII_LENGTH( "Notizen" )) )
/*N*/ 						nNewId = HID_PSEUDOSHEET_NOTES;
/*N*/ 					else if( aOldName.Equals( String( String( aStr ).Append( String( UniString::CreateFromAscii( RTL_CONSTASCII_STRINGPARAM( "1" ) ) ) ) ) ) ||
/*N*/ 						     aOldName.Equals( String( String( aStr2 ).Append( String( UniString::CreateFromAscii( RTL_CONSTASCII_STRINGPARAM( "1" ) ) ) ) ) ) )
/*N*/ 						nNewId = HID_PSEUDOSHEET_OUTLINE1;
/*N*/ 					else if( aOldName.Equals( String( String( aStr ).Append( String( UniString::CreateFromAscii( RTL_CONSTASCII_STRINGPARAM( "2" ) ) ) ) ) ) ||
/*N*/ 						     aOldName.Equals( String( String( aStr2 ).Append( String( UniString::CreateFromAscii( RTL_CONSTASCII_STRINGPARAM( "2" ) ) ) ) ) ) )
/*N*/ 						nNewId = HID_PSEUDOSHEET_OUTLINE2;
/*N*/ 					else if( aOldName.Equals( String( String( aStr ).Append( String( UniString::CreateFromAscii( RTL_CONSTASCII_STRINGPARAM( "3" ) ) ) ) ) ) ||
/*N*/ 						     aOldName.Equals( String( String( aStr2 ).Append( String( UniString::CreateFromAscii( RTL_CONSTASCII_STRINGPARAM( "3" ) ) ) ) ) ) )
/*N*/ 						nNewId = HID_PSEUDOSHEET_OUTLINE3;
/*N*/ 					else if( aOldName.Equals( String( String( aStr ).Append( String( UniString::CreateFromAscii( RTL_CONSTASCII_STRINGPARAM( "4" ) ) ) ) ) ) ||
/*N*/ 						     aOldName.Equals( String( String( aStr2 ).Append( String( UniString::CreateFromAscii( RTL_CONSTASCII_STRINGPARAM( "4" ) ) ) ) ) ) )
/*N*/ 						nNewId = HID_PSEUDOSHEET_OUTLINE4;
/*N*/ 					else if( aOldName.Equals( String( String( aStr ).Append( String( UniString::CreateFromAscii( RTL_CONSTASCII_STRINGPARAM( "5" ) ) ) ) ) ) ||
/*N*/ 						     aOldName.Equals( String( String( aStr2 ).Append( String( UniString::CreateFromAscii( RTL_CONSTASCII_STRINGPARAM( "5" ) ) ) ) ) ) )
/*N*/ 						nNewId = HID_PSEUDOSHEET_OUTLINE5;
/*N*/ 					else if( aOldName.Equals( String( String( aStr ).Append( String( UniString::CreateFromAscii( RTL_CONSTASCII_STRINGPARAM( "6" ) ) ) ) ) ) ||
/*N*/ 						     aOldName.Equals( String( String( aStr2 ).Append( String( UniString::CreateFromAscii( RTL_CONSTASCII_STRINGPARAM( "6" ) ) ) ) ) ) )
/*N*/ 						nNewId = HID_PSEUDOSHEET_OUTLINE6;
/*N*/ 					else if( aOldName.Equals( String( String( aStr ).Append( String( UniString::CreateFromAscii( RTL_CONSTASCII_STRINGPARAM( "7" ) ) ) ) ) ) ||
/*N*/ 						     aOldName.Equals( String( String( aStr2 ).Append( String( UniString::CreateFromAscii( RTL_CONSTASCII_STRINGPARAM( "7" ) ) ) ) ) ) )
/*N*/ 						nNewId = HID_PSEUDOSHEET_OUTLINE7;
/*N*/ 					else if( aOldName.Equals( String( String( aStr ).Append( String( UniString::CreateFromAscii( RTL_CONSTASCII_STRINGPARAM( "8" ) ) ) ) ) ) ||
/*N*/ 						     aOldName.Equals( String( String( aStr2 ).Append( String( UniString::CreateFromAscii( RTL_CONSTASCII_STRINGPARAM( "8" ) ) ) ) ) ) )
/*N*/ 						nNewId = HID_PSEUDOSHEET_OUTLINE8;
/*N*/ 					else if( aOldName.Equals( String( String( aStr ).Append( String( UniString::CreateFromAscii( RTL_CONSTASCII_STRINGPARAM( "9" ) ) ) ) ) ) ||
/*N*/ 						     aOldName.Equals( String( String( aStr2 ).Append( String( UniString::CreateFromAscii( RTL_CONSTASCII_STRINGPARAM( "9" ) ) ) ) ) ) )
/*N*/ 						nNewId = HID_PSEUDOSHEET_OUTLINE9;
/*N*/ 				}
/*N*/ 
/*N*/ 				if ( nNewId )
/*N*/ 				{
/*N*/ 					bNewHelpIds = TRUE;
/*N*/ 					pStyle->SetHelpId( aHelpFile, nNewId );
/*N*/ 				}
/*N*/ 			}
/*N*/ 		}
/*N*/ 	}
/*N*/ 
/*N*/ 	if ( pEraseList )
/*N*/ 	{
/*N*/ 		// Styles, welche nicht umbenannt werden konnten, muessen entfernt werden
/*N*/ 		for ( ULONG i = 0; i < pEraseList->Count(); i++ )
/*N*/ 		{
/*N*/ 			SfxStyleSheetBase* pEraseSheet = ( SfxStyleSheetBase* ) pEraseList->GetObject( i );
/*N*/ 			Erase( pEraseSheet );
/*N*/ 		}
/*N*/ 
/*N*/ 		delete pEraseList;
/*N*/ 		pEraseList = NULL;
/*N*/ 	}
/*N*/ 
/*N*/ 	// Wenn neue HelpIDs gefunden wurden koennen die Namen auch gleich ersetzt werden
/*N*/ 	if( bNewHelpIds )
/*N*/ 		UpdateStdNames();
/*N*/ }


/*************************************************************************
|*
|* Da sich die Bedeutung der SvxLRSpaceItems ab nFileFormatVersion = 16
|* geaendert hat (Bullet-Handling des Outliners, siehe auch
|* SdDrawDocument::NewOrLoadCompleted()), muss fuer aeltere Versionen
|* eine Korrektur vorgenommen werden.
|*
\************************************************************************/

/*N*/ void SdStyleSheetPool::AdjustLRSpaceItems()
/*N*/ {
/*N*/ 	String aHelpFile;
/*N*/ 	ULONG nCount = aStyles.Count();
/*N*/ 
/*N*/ 	// #63254# Aenderungen nicht mehr broadcasten,statt dessen nach
/*N*/ 	// AdjustLRSpaceItems() ein UpdateStyleSheets am Outliner
/*N*/ 
/*N*/ 	if ( nCount > 0 )
/*N*/ 	{
        /**************************************************************************
        * All LayoutStyleSheets loaded? (e.g. new Subtitle LayoutStyleSheet)
        **************************************************************************/
/*N*/ 		USHORT nMasterPageCount = pDoc->GetMasterSdPageCount(PK_STANDARD);
/*N*/ 
/*N*/ 		for ( USHORT i = 0; i < nMasterPageCount; i++ )
/*N*/ 		{
/*N*/ 			String aName(pDoc->GetMasterSdPage(i, PK_STANDARD)->GetLayoutName());
/*N*/ 			aName.Erase( aName.SearchAscii( SD_LT_SEPARATOR ));
/*N*/ 			CreateLayoutStyleSheets(aName);
/*N*/ 		}
/*N*/ 	}
/*N*/ 
/*N*/ 	String aOutlineName( RTL_CONSTASCII_USTRINGPARAM( SD_LT_SEPARATOR ));
/*N*/ 	aOutlineName += String(SdResId(STR_PSEUDOSHEET_OUTLINE));
/*N*/ 	String aTitleName( RTL_CONSTASCII_USTRINGPARAM( SD_LT_SEPARATOR ));
/*N*/ 	aTitleName += String(SdResId(STR_PSEUDOSHEET_TITLE));
/*N*/ 	String aSubtitleName( RTL_CONSTASCII_USTRINGPARAM( SD_LT_SEPARATOR ));
/*N*/ 	aSubtitleName += String(SdResId(STR_PSEUDOSHEET_SUBTITLE));
/*N*/ 	String aStandardName(SdResId(STR_STANDARD_STYLESHEET_NAME));
/*N*/ 	SfxStyleSheet* pSheetOutlineLevelOne = NULL;
/*N*/ 
/*N*/ 	for (ULONG n = 0; n < nCount; n++)
/*N*/ 	{
/*N*/ 		SfxStyleSheet* pSheet = (SfxStyleSheet*)aStyles.GetObject(n);
/*N*/ 		SfxItemSet& rSet = pSheet->GetItemSet();
/*N*/ 		String aName( pSheet->GetName() );
/*N*/ 		String aHelpFile;
/*N*/ 		ULONG nHelpId = pSheet->GetHelpId( aHelpFile );
/*N*/ 
/*N*/ 		if( nHelpId == 0)
/*N*/ 		{
/*N*/ 			if( aName.Len() == aOutlineName.Len() + 1 &&
/*N*/ 				aName.Match( aOutlineName ) == STRING_MATCH )
/*N*/ 			{
/*?*/ 				sal_Int32 nNumber = String( aName, aName.Len(), 1 ).ToInt32();
/*?*/ 				if( 1 <= nNumber && nNumber <= 9 )
/*?*/ 					nHelpId = HID_PSEUDOSHEET_OUTLINE + nNumber;
/*N*/ 			}
/*N*/ 		}
/*N*/ 
/*N*/ 		if ( nHelpId &&
/*N*/ 			 ( HID_PSEUDOSHEET_OUTLINE + 1 <= nHelpId &&
/*N*/ 			   nHelpId <= HID_PSEUDOSHEET_OUTLINE + 9 ))
/*N*/ 		{
/*N*/ 			// Gliederungsvorlage
/*N*/ 			// Bei Gliederungsobjektvorlagen Korrektur vornehmen
/*N*/ 			// Es handelt sich hier um die RealStyleSheets und die Pseudos!
/*N*/ 			// (siehe SdStyleSheet::GetRealStyleSheet())
/*N*/ 			if ( nHelpId == HID_PSEUDOSHEET_OUTLINE + 1 )
/*N*/ 			{
/*N*/ 				if (rSet.GetItemState(EE_PARA_BULLETSTATE) != SFX_ITEM_ON)
/*N*/ 				{
/*N*/ 					SfxUInt16Item aBulletStateItem(EE_PARA_BULLETSTATE, 1); // Bullets sichtbar
/*N*/ 					rSet.Put(aBulletStateItem);
/*N*/ 				}
/*N*/ 			}
/*N*/ 
/*N*/ 			// Gliederungs-Vorlage
/*N*/ 			const SvxBulletItem* pOldBullet = NULL;
/*N*/ 			if ( rSet.GetItemState( EE_PARA_BULLET ) == SFX_ITEM_ON )
/*N*/ 				pOldBullet = &(const SvxBulletItem&) rSet.Get(EE_PARA_BULLET);
/*N*/ 
/*N*/ 			const SvxLRSpaceItem* pOldLRSpace = NULL;
/*N*/ 			if ( rSet.GetItemState( EE_PARA_LRSPACE ) == SFX_ITEM_ON )
/*N*/ 				pOldLRSpace = &(const SvxLRSpaceItem&) rSet.Get(EE_PARA_LRSPACE);
/*N*/ 
/*N*/ 			USHORT nLevel = (USHORT) (nHelpId - HID_PSEUDOSHEET_OUTLINE);
/*N*/ 
/*N*/ 			if ( nHelpId == HID_PSEUDOSHEET_OUTLINE + 1 )
/*N*/ 			{
/*N*/ 				pSheetOutlineLevelOne = pSheet;
/*N*/ 				SvxNumBulletItem aDefaultNumBullet( *(SvxNumBulletItem*) rSet.GetPool()->GetSecondaryPool()->GetPoolDefaultItem(EE_PARA_NUMBULLET) );
/*N*/ 				aDefaultNumBullet.GetNumRule()->SetNumRuleType( SVX_RULETYPE_PRESENTATION_NUMBERING );
/*N*/ 				EditEngine::ImportBulletItem( aDefaultNumBullet, nLevel, pOldBullet, pOldLRSpace );
/*N*/ 				rSet.Put( aDefaultNumBullet );
/*N*/ 
/*N*/ 				if (rSet.GetItemState( XATTR_FILLSTYLE ) != SFX_ITEM_ON )
/*N*/ 				{
/*N*/ 					// Flaechenattribute sind nun unsichtbar
/*N*/ 					XFillStyleItem aFillStyleItem(XFILL_NONE);
/*N*/ 					rSet.Put(aFillStyleItem);
/*N*/ 				}
/*N*/ 
/*N*/ 				if (rSet.GetItemState( XATTR_LINESTYLE ) != SFX_ITEM_ON )
/*N*/ 				{
/*N*/ 					// Linienattribute sind nun unsichtbar
/*N*/ 					XLineStyleItem aLineStyleItem(XLINE_NONE);
/*N*/ 					rSet.Put(aLineStyleItem);
/*N*/ 				}
/*N*/ 			}
/*N*/ 			else
/*N*/ 			{
/*N*/ 				SfxItemSet& rSetOutlineLevelOne = pSheetOutlineLevelOne->GetItemSet();
/*N*/ 				SvxNumBulletItem aNumBullet( (const SvxNumBulletItem&) rSetOutlineLevelOne.Get(EE_PARA_NUMBULLET) );
/*N*/ 				EditEngine::ImportBulletItem( aNumBullet, nLevel, pOldBullet, pOldLRSpace );
/*N*/ 				rSetOutlineLevelOne.Put( aNumBullet );
/*N*/ 
/*N*/ 				// SvxNumBulletItems darf es nur in der ersten Gliederungsebene geben!
/*N*/ 				if ( rSet.GetItemState( EE_PARA_NUMBULLET ) == SFX_ITEM_ON )
/*N*/ 					rSet.ClearItem( EE_PARA_NUMBULLET );
/*N*/ 			}
/*N*/ 
/*N*/ 			if (rSet.GetItemState(EE_PARA_LRSPACE) == SFX_ITEM_ON)
/*N*/ 			{
/*N*/ 				const SvxLRSpaceItem& rLRItem = (const SvxLRSpaceItem&) rSet.Get(EE_PARA_LRSPACE);
/*N*/ 
/*N*/ 				if (rLRItem.GetTxtFirstLineOfst() == 0)
/*N*/ 				{
/*N*/ 					SvxLRSpaceItem aNewLRItem(rLRItem);
/*N*/ 					const SvxBulletItem& rBulletItem = (const SvxBulletItem&) rSet.Get(EE_PARA_BULLET);
/*N*/ 					short nFirstLineOfst = (short) -rBulletItem.GetWidth();
/*N*/ 					aNewLRItem.SetTxtFirstLineOfst(nFirstLineOfst);
/*N*/ 					rSet.Put(aNewLRItem);
/*N*/ 				}
/*N*/ 			}
/*N*/ 		}
/*N*/ 		else if ( nHelpId == HID_PSEUDOSHEET_TITLE               ||
/*N*/ 				  nHelpId == HID_PSEUDOSHEET_SUBTITLE            ||
/*N*/ 				  aName.Search(aTitleName)    != STRING_NOTFOUND ||
/*N*/ 				  aName.Search(aSubtitleName) != STRING_NOTFOUND )
/*N*/ 		{
/*N*/ 			// Titel- oder Untertitel-Vorlage
/*N*/ 			SfxItemSet& rSet = pSheet->GetItemSet();
/*N*/ 
/*N*/ 			if (rSet.GetItemState(EE_PARA_BULLETSTATE) != SFX_ITEM_ON ||
/*N*/ 				((const SfxUInt16Item&) rSet.Get(EE_PARA_BULLETSTATE)).GetValue() == 1)
/*N*/ 			{
/*N*/ 				SfxUInt16Item aBulletStateItem(EE_PARA_BULLETSTATE, 0); // Bullets nicht sichtbar
/*N*/ 				rSet.Put(aBulletStateItem);
/*N*/ 			}
/*N*/ 
/*N*/ 			if( nHelpId == HID_PSEUDOSHEET_TITLE ||
/*N*/ 				aName.Search(aTitleName) != STRING_NOTFOUND )
/*N*/ 			{
/*N*/ 				Font aBulletFont( GetBulletFont() );
/*N*/ 				aBulletFont.SetSize(Size(0,1552));					// 44 pt
/*N*/ 				PutNumBulletItem( pSheet, aBulletFont );
/*N*/ 			}
/*N*/ 			else if( nHelpId == HID_PSEUDOSHEET_SUBTITLE ||
/*N*/ 					 aName.Search(aSubtitleName) != STRING_NOTFOUND )
/*N*/ 			{
/*N*/ 				Font aBulletFont( GetBulletFont() );
/*N*/ 				aBulletFont.SetSize(Size(0, 1129));		// 32 pt
/*N*/ 				PutNumBulletItem( pSheet, aBulletFont );
/*N*/ 			}
/*N*/ 		}
/*N*/ 		else if ( aName == aStandardName )
/*N*/ 		{
/*N*/ 			// Standardvorlage
/*N*/ 			Font aBulletFont( GetBulletFont() );
/*N*/ 			aBulletFont.SetSize(Size(0,846));		// 24 pt
/*N*/ 			PutNumBulletItem( pSheet, aBulletFont );
/*N*/ 		}
/*N*/ 		else if ( rSet.GetItemState( EE_PARA_LRSPACE ) == SFX_ITEM_ON )
/*N*/ 		{
/*N*/ 			// SvxLRSpaceItem hart gesetzt: NumBulletItem anpassen
/*N*/ 			SvxNumBulletItem aNumBullet( (const SvxNumBulletItem&) rSet.Get(EE_PARA_NUMBULLET) );
/*N*/ 
/*N*/ 			EditEngine::ImportBulletItem( aNumBullet, 0, NULL, &(const SvxLRSpaceItem&) rSet.Get( EE_PARA_LRSPACE ) );
/*N*/ 			rSet.Put( aNumBullet );
/*N*/ 		}
/*N*/ 	}
/*N*/ }


/*************************************************************************
|*
|* Neues SvxNumBulletItem fuer das jeweilige StyleSheet setzen
|*
\************************************************************************/

/*N*/ void SdStyleSheetPool::PutNumBulletItem( SfxStyleSheetBase* pSheet,
/*N*/ 										 Font& rBulletFont )
/*N*/ {
/*N*/ 	String aHelpFile;
/*N*/ 	ULONG nHelpId = pSheet->GetHelpId( aHelpFile );
/*N*/ 	SfxItemSet& rSet = pSheet->GetItemSet();
/*N*/ 
/*N*/ 	switch ( nHelpId )
/*N*/ 	{
/*N*/ 		case HID_STANDARD_STYLESHEET_NAME :
/*N*/ 		{
/*N*/ 			// Standard-Vorlage
/*N*/ 			SvxNumberFormat aNumberFormat(SVX_NUM_CHAR_SPECIAL);
/*N*/ 			aNumberFormat.SetBulletFont(&rBulletFont);
/*N*/ 			aNumberFormat.SetBulletChar( 0x25CF ); // StarBats: 0xF000 + 34
/*N*/ 			aNumberFormat.SetBulletRelSize(45);
/*N*/ 			aNumberFormat.SetBulletColor(Color(COL_AUTO));
/*N*/ 			aNumberFormat.SetStart(1);
/*N*/ 			aNumberFormat.SetNumAdjust(SVX_ADJUST_LEFT);
/*N*/ 
/*N*/ 			SvxNumRule aNumRule( NUM_BULLET_REL_SIZE|NUM_BULLET_COLOR|NUM_CHAR_TEXT_DISTANCE, 10 , FALSE);
/*N*/ 			aNumberFormat.SetLSpace( 0 );
/*N*/ 			aNumberFormat.SetAbsLSpace( 0 );
/*N*/ 			aNumberFormat.SetFirstLineOffset( 0 );
/*N*/ 			aNumRule.SetLevel( 0, aNumberFormat );
/*N*/ 
/*N*/ 			for( USHORT i = 1; i < 10; i++ )
/*N*/ 			{
/*N*/ 				const short nLSpace = (i + 1) * 600;
/*N*/ 				aNumberFormat.SetLSpace(nLSpace);
/*N*/ 				aNumberFormat.SetAbsLSpace(nLSpace);
/*N*/ 				aNumberFormat.SetFirstLineOffset(-600);
/*N*/ 				aNumRule.SetLevel( i, aNumberFormat );
/*N*/ 			}
/*N*/ 
/*N*/ 			rSet.Put( SvxNumBulletItem( aNumRule, EE_PARA_NUMBULLET ) );
/*N*/ 			((SfxStyleSheet*)pSheet)->Broadcast(SfxSimpleHint( SFX_HINT_DATACHANGED ) );
/*N*/ 		}
/*N*/ 		break;
/*N*/ 
/*N*/ 		case HID_PSEUDOSHEET_TITLE:
/*N*/ 			/* #84013# title gets same bullet as subtitle and not that page symbol anymore */
/*N*/  		case HID_PSEUDOSHEET_SUBTITLE :
/*N*/  		{
/*N*/  			// Untertitel-Vorlage
/*N*/  			SvxNumRule* pDefaultRule = ((SvxNumBulletItem*) rSet.GetPool()->GetSecondaryPool()->GetPoolDefaultItem(EE_PARA_NUMBULLET))->GetNumRule();
/*N*/  			DBG_ASSERT( pDefaultRule, "Wo ist mein Default? [CL]" );
/*N*/  
/*N*/  			if(pDefaultRule)
/*N*/  			{
/*N*/  				SvxNumRule aNumRule(pDefaultRule->GetFeatureFlags(), 9, FALSE);
/*N*/  				for(USHORT i=0; i < aNumRule.GetLevelCount(); i++)
/*N*/  				{
/*N*/  					SvxNumberFormat aFrmt( pDefaultRule->GetLevel(i) );
/*N*/  					aFrmt.SetNumberingType(SVX_NUM_CHAR_SPECIAL);
/*N*/  					aFrmt.SetStart(1);
/*N*/  					aFrmt.SetBulletRelSize(45);
/*N*/  					aFrmt.SetBulletChar( 0x25CF );  // StarBats: 0xF000 + 34
/*N*/  					aFrmt.SetBulletFont(&rBulletFont);
/*N*/  					aNumRule.SetLevel(i, aFrmt);
/*N*/  				}
/*N*/  
/*N*/  				rSet.Put( SvxNumBulletItem( aNumRule, EE_PARA_NUMBULLET ) );
/*N*/  				((SfxStyleSheet*)pSheet)->Broadcast(SfxSimpleHint( SFX_HINT_DATACHANGED ) );
/*N*/  			}
/*N*/  		}
/*N*/  		break;
/*N*/  
/*N*/  		case HID_PSEUDOSHEET_OUTLINE + 1 :
/*N*/  		{
/*N*/  			// Gliederungs-Vorlage
/*N*/  			SvxNumberFormat aNumberFormat(SVX_NUM_CHAR_SPECIAL);
/*N*/  			aNumberFormat.SetBulletColor(Color(COL_AUTO));
/*N*/  			aNumberFormat.SetStart(1);
/*N*/  			aNumberFormat.SetNumAdjust(SVX_ADJUST_LEFT);
/*N*/  
/*N*/  			SvxNumRule aNumRule( NUM_BULLET_REL_SIZE|NUM_BULLET_COLOR|NUM_CHAR_TEXT_DISTANCE|NUM_SYMBOL_ALIGNMENT,
/*N*/  								 10, FALSE, SVX_RULETYPE_PRESENTATION_NUMBERING );
/*N*/  			for( UINT16 i = 0; i < 10; i++ )
/*N*/  			{
/*N*/  				aNumberFormat.SetBulletChar( 0x25CF );  // StarBats: 0xF000 + 34
/*N*/  				aNumberFormat.SetBulletRelSize(45);
/*N*/  				const short nLSpace = i ? i * 1200 : 1200;
/*N*/  				aNumberFormat.SetLSpace(nLSpace);
/*N*/  				aNumberFormat.SetAbsLSpace(nLSpace);
/*N*/  				USHORT nFirstLineOffset = -600;
/*N*/  
/*N*/  				ULONG nFontSize = 20;
/*N*/  				switch(i)
/*N*/  				{
/*N*/  					case 0:
/*N*/  					case 1:
/*N*/  					{
/*N*/  						nFontSize = 32;
/*N*/  						nFirstLineOffset = -900;
/*N*/  					}
/*N*/  					break;
/*N*/  
/*N*/  					case 2:
/*N*/  					{
/*N*/  						nFontSize = 28;
/*N*/  						nFirstLineOffset = -800;
/*N*/  						aNumberFormat.SetBulletChar( 0x2013 );  // StarBats: 0xF000 + 150
/*N*/  						aNumberFormat.SetBulletRelSize(75);
/*N*/  					}
/*N*/  					break;
/*N*/  
/*N*/  					case 3:
/*N*/  					{
/*N*/  						nFontSize = 24;
/*N*/  					}
/*N*/  					break;
/*N*/  
/*N*/  					case 4:
/*N*/  					{
/*N*/  						aNumberFormat.SetBulletChar( 0x2013 ); // StarBats: 0xF000 + 150
/*N*/  						aNumberFormat.SetBulletRelSize(75);
/*N*/  					}
/*N*/  					break;
/*N*/  				}
/*N*/  
/*N*/  				aNumberFormat.SetFirstLineOffset(nFirstLineOffset);
/*N*/  				nFontSize = (USHORT)((nFontSize * 2540L) / 72);  // Pt --> 1/100 mm
/*N*/  				rBulletFont.SetSize(Size(0,846));		// 24 pt
/*N*/  				aNumberFormat.SetBulletFont(&rBulletFont);
/*N*/  				aNumRule.SetLevel( i, aNumberFormat );
/*N*/  			}
/*N*/  
/*N*/  			rSet.Put( SvxNumBulletItem( aNumRule, EE_PARA_NUMBULLET ) );
/*N*/  			((SfxStyleSheet*)pSheet)->Broadcast(SfxSimpleHint( SFX_HINT_DATACHANGED ) );
/*N*/  		}
/*N*/  		break;
/*N*/  	}
/*N*/ }

/*************************************************************************
|*
|* Standard Bullet-Font erzeugen (ohne Groesse)
|*
\************************************************************************/

/*N*/ Font SdStyleSheetPool::GetBulletFont() const
/*N*/ {
/*N*/ 	Font aBulletFont( String( RTL_CONSTASCII_USTRINGPARAM( "StarSymbol" )), Size(0, 1000) );
/*N*/ 	aBulletFont.SetCharSet(RTL_TEXTENCODING_UNICODE);
/*N*/ 	aBulletFont.SetWeight(WEIGHT_NORMAL);
/*N*/ 	aBulletFont.SetUnderline(UNDERLINE_NONE);
/*N*/ 	aBulletFont.SetStrikeout(STRIKEOUT_NONE);
/*N*/ 	aBulletFont.SetItalic(ITALIC_NONE);
/*N*/ 	aBulletFont.SetOutline(FALSE);
/*N*/ 	aBulletFont.SetShadow(FALSE);
/*N*/ 	aBulletFont.SetColor(Color(COL_AUTO));
/*N*/ 	aBulletFont.SetTransparent(TRUE);
/*N*/ 
/*N*/ 	return aBulletFont;
/*N*/ }





}
