/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: svx_svdotxat.cxx,v $
 *
 *  $Revision: 1.5 $
 *
 *  last change: $Author: rt $ $Date: 2005-09-08 07:01:53 $
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

// auto strip #include <svtools/style.hxx>
// auto strip #include "svdotext.hxx"
#include "svditext.hxx"
#include "svdmodel.hxx" // fuer GetMaxObjSize und GetStyleSheetPool
#include "svdoutl.hxx"
// auto strip #include "svdorect.hxx" // fuer SetDirty bei NbcAdjustTextFrameWidthAndHeight
#include "svdocapt.hxx" // fuer SetDirty bei NbcAdjustTextFrameWidthAndHeight
// auto strip #include <svdetc.hxx>
#include "writingmodeitem.hxx"
// auto strip #include "editeng.hxx"
#include "eeitem.hxx"

// auto strip #ifndef _PSTM_HXX
// auto strip #include <tools/pstm.hxx>
// auto strip #endif

#ifndef _SVX_ITEMDATA_HXX
#include "itemdata.hxx"
#endif

// auto strip #include "flditem.hxx"


// auto strip #ifndef _MyEDITVIEW_HXX
// auto strip #include "editview.hxx"
// auto strip #endif

#ifndef _SFXSMPLHINT_HXX //autogen
#include <svtools/smplhint.hxx>
#endif

// auto strip #ifndef _SFX_WHITER_HXX //autogen
// auto strip #include <svtools/whiter.hxx>
// auto strip #endif

#ifndef _OUTLOBJ_HXX //autogen
#include <outlobj.hxx>
#endif

// auto strip #ifndef _OUTLINER_HXX //autogen
// auto strip #include "outliner.hxx"
// auto strip #endif

#ifndef _EEITEM_HXX //autogen
#include "eeitem.hxx"
#endif

#ifndef _EDITOBJ_HXX //autogen
#include <editobj.hxx>
#endif

#ifndef _SVX_FHGTITEM_HXX //autogen
#include "fhgtitem.hxx"
#endif

#include <charscaleitem.hxx>

#ifndef _SFXSTYLE_HXX //autogen
#include <svtools/style.hxx>
#endif

#ifndef _SFXITEMITER_HXX //autogen
#include <svtools/itemiter.hxx>
#endif

#define ITEMID_LRSPACE			EE_PARA_LRSPACE
// auto strip #ifndef _SVX_LRSPITEM_HXX //autogen
// auto strip #include <lrspitem.hxx>
// auto strip #endif

// auto strip #ifndef _SFXITEMPOOL_HXX //autogen
// auto strip #include <svtools/itempool.hxx>
// auto strip #endif

// auto strip #ifndef _SVX_NUMITEM_HXX //autogen
// auto strip #include <numitem.hxx>
// auto strip #endif

// auto strip #ifndef _MyEDITENG_HXX //autogen
// auto strip #include <editeng.hxx>
// auto strip #endif

// auto strip #ifndef _SVX_POSTITEM_HXX //autogen
// auto strip #include <postitem.hxx>
// auto strip #endif
namespace binfilter {

////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  @@@@@@ @@@@@ @@   @@ @@@@@@  @@@@  @@@@@  @@@@@@
//    @@   @@    @@@ @@@   @@   @@  @@ @@  @@     @@
//    @@   @@     @@@@@    @@   @@  @@ @@  @@     @@
//    @@   @@@@    @@@     @@   @@  @@ @@@@@      @@
//    @@   @@     @@@@@    @@   @@  @@ @@  @@     @@
//    @@   @@    @@@ @@@   @@   @@  @@ @@  @@ @@  @@
//    @@   @@@@@ @@   @@   @@    @@@@  @@@@@   @@@@
//
//  Attribute, StyleSheets und AutoGrow
//
////////////////////////////////////////////////////////////////////////////////////////////////////

/*N*/ void __EXPORT SdrTextObj::SFX_NOTIFY(SfxBroadcaster& rBC, const TypeId& rBCType, const SfxHint& rHint, const TypeId& rHintType)
/*N*/ {
/*N*/ 	SdrAttrObj::SFX_NOTIFY(rBC,rBCType,rHint,rHintType);
/*N*/ 	if (pOutlinerParaObject!=NULL)
/*N*/ 	{
/*N*/ 		if (HAS_BASE(SfxStyleSheet, &rBC))
/*N*/ 		{
/*N*/ 			SfxSimpleHint* pSimple=PTR_CAST(SfxSimpleHint,&rHint);
/*N*/ 			ULONG nId=pSimple==NULL ? 0 : pSimple->GetId();
/*N*/ 			if (nId==SFX_HINT_DATACHANGED)
/*N*/ 			{
/*N*/ 				bPortionInfoChecked=FALSE;
/*N*/ 				pOutlinerParaObject->ClearPortionInfo();
/*N*/ 				SetTextSizeDirty();
/*N*/ 				if (bTextFrame && NbcAdjustTextFrameWidthAndHeight())
/*N*/ 				{
/*?*/ 					SendRepaintBroadcast();
/*N*/ 				}
/*N*/ 			}
/*N*/ 			if (nId==SFX_HINT_DYING)
/*N*/ 			{
/*?*/ 				bPortionInfoChecked=FALSE;
/*?*/ 				pOutlinerParaObject->ClearPortionInfo();
/*N*/ 			}
/*N*/ 		}
/*N*/ 		else if (HAS_BASE(SfxStyleSheetBasePool, &rBC))
/*N*/ 		{
/*N*/ 			SfxStyleSheetHintExtended* pExtendedHint = PTR_CAST(SfxStyleSheetHintExtended, &rHint);
/*N*/ 
/*N*/ 			if (pExtendedHint && pExtendedHint->GetHint() == SFX_STYLESHEET_MODIFIED)
/*N*/ 			{
/*N*/ 				String aOldName(pExtendedHint->GetOldName());
/*N*/ 				String aNewName(pExtendedHint->GetStyleSheet()->GetName());
/*N*/ 				SfxStyleFamily eFamily = pExtendedHint->GetStyleSheet()->GetFamily();
/*N*/ 
/*N*/ 				if(!aOldName.Equals(aNewName))
/*N*/ 					pOutlinerParaObject->ChangeStyleSheetName(eFamily, aOldName, aNewName);
/*N*/ 			}
/*N*/ 		}
/*N*/ 	}
/*N*/ }

/*N*/ void SdrTextObj::NbcSetStyleSheet(SfxStyleSheet* pNewStyleSheet, FASTBOOL bDontRemoveHardAttr)
/*N*/ {
/*N*/ 	SdrAttrObj::NbcSetStyleSheet(pNewStyleSheet,bDontRemoveHardAttr);
/*N*/ 
/*N*/ 	if ( pOutlinerParaObject && !pEdtOutl && !IsLinkedText() )
/*N*/ 	{
/*N*/ 		// StyleSheet auf alle Absaetze anwenden
/*N*/ 		SdrOutliner& rOutliner=ImpGetDrawOutliner();
/*N*/ 		rOutliner.SetText(*pOutlinerParaObject);
/*N*/ 		USHORT nParaCount=(USHORT)rOutliner.GetParagraphCount();
/*N*/ 		if (nParaCount!=0)
/*N*/ 		{
/*N*/ 			SfxItemSet* pTempSet;
/*N*/ 			for (USHORT nPara=0; nPara<nParaCount; nPara++)
/*N*/ 			{
/*N*/ 				// since setting the stylesheet removes all para attributes
/*N*/ 				if( bDontRemoveHardAttr )
/*N*/ 				{
/*N*/ 					// we need to remember them if we want to keep them
/*N*/ 					pTempSet = new SfxItemSet( rOutliner.GetParaAttribs( nPara ) );
/*N*/ 				}
/*N*/ 
/*N*/ 				if ( GetStyleSheet() )
/*N*/ 				{
/*N*/ 					if( eTextKind == OBJ_OUTLINETEXT && GetObjInventor() == SdrInventor )
/*N*/ 					{
/*N*/ 						String aNewStyleSheetName( GetStyleSheet()->GetName() );
/*N*/ 						aNewStyleSheetName.Erase( aNewStyleSheetName.Len()-1, 1 );
/*N*/ 						aNewStyleSheetName += String::CreateFromInt32( rOutliner.GetDepth( nPara ) );
/*N*/ 
/*N*/ 						SfxStyleSheetBasePool* pStylePool = pModel!=NULL ? pModel->GetStyleSheetPool() : NULL;
/*N*/ 						SfxStyleSheet* pNewStyle = (SfxStyleSheet*) pStylePool->Find( aNewStyleSheetName, GetStyleSheet()->GetFamily() );
/*N*/ 						DBG_ASSERT( pNewStyle, "AutoStyleSheetName - Style not found!" );
/*N*/ 						if ( pNewStyle )
/*N*/ 							rOutliner.SetStyleSheet( nPara, pNewStyle );
/*N*/ 					}
/*N*/ 					else
/*N*/ 						rOutliner.SetStyleSheet( nPara, GetStyleSheet() );
/*N*/ 				}
/*N*/ 				else
/*N*/ 					rOutliner.SetStyleSheet( nPara, NULL ); // StyleSheet entfernen
/*N*/ 
/*N*/ 				if( bDontRemoveHardAttr )
/*N*/ 				{
/*N*/ 					// restore para attributes
/*N*/ 					rOutliner.SetParaAttribs( nPara, *pTempSet );
/*N*/ 					delete pTempSet;
/*N*/ 				}
/*N*/ 				else
/*N*/ 				{
/*N*/ 					if(pNewStyleSheet!=NULL)
/*N*/ 					{
/*N*/ 						// Harte Absatz-Attributierung aller im
/*N*/ 						// StyleSheet vorhandenen Items entfernen
/*N*/ 						// -> Parents beruecksichtigen !!!
/*N*/ 						SfxItemIter aIter(pNewStyleSheet->GetItemSet());
/*N*/ 						const SfxPoolItem* pItem=aIter.FirstItem();
/*N*/ 						while (pItem!=NULL) {
/*N*/ 							if (!IsInvalidItem(pItem)) {
/*N*/ 								USHORT nW=pItem->Which();
/*N*/ 								if (nW>=EE_ITEMS_START && nW<=EE_ITEMS_END) {
/*N*/ 									// gibts noch nicht, baut Malte aber ein:
/*N*/ 									rOutliner.QuickRemoveCharAttribs(nPara,nW);
/*N*/ 								}
/*N*/ 							}
/*N*/ 							pItem=aIter.NextItem();
/*N*/ 						}
/*N*/ 					}
/*N*/ 				}
/*N*/ 			}
/*N*/ 			OutlinerParaObject* pTemp=rOutliner.CreateParaObject( 0, nParaCount );
/*N*/ 			rOutliner.Clear();
/*N*/ 			NbcSetOutlinerParaObject(pTemp);
/*N*/ 		}
/*N*/ 	}
/*N*/ 	if (bTextFrame) {
/*N*/ 		NbcAdjustTextFrameWidthAndHeight();
/*N*/ 	}
/*N*/ }

////////////////////////////////////////////////////////////////////////////////////////////////////
// private support routines for ItemSet access

/*N*/ void SdrTextObj::ItemSetChanged(const SfxItemSet& rSet)
/*N*/ {
/*N*/ 	// handle outliner attributes
/*N*/ 	ImpForceItemSet();
/*N*/ 
/*N*/ 	if(pOutlinerParaObject)
/*N*/ 	{
/*N*/ 		Outliner* pOutliner;
/*N*/ 
/*N*/ 		if(!pEdtOutl)
/*N*/ 		{
/*N*/ 			pOutliner = &ImpGetDrawOutliner();
/*N*/ 			pOutliner->SetText(*pOutlinerParaObject);
/*N*/ 		}
/*N*/ 		else
/*N*/ 		{
/*?*/ 			pOutliner = pEdtOutl;
/*N*/ 		}
/*N*/ 
/*N*/ 		sal_uInt16 nParaCount((sal_uInt16)pOutliner->GetParagraphCount());
/*N*/ 		for(sal_uInt16 nPara(0); nPara < nParaCount; nPara++)
/*N*/ 		{
/*N*/ 			SfxItemSet aSet( pOutliner->GetParaAttribs(nPara) );
/*N*/ 			aSet.Put( rSet );
/*N*/ 			pOutliner->SetParaAttribs(nPara, aSet);
/*N*/ 		}
/*N*/ 
/*N*/ 		if(!pEdtOutl)
/*N*/ 		{
/*N*/ 			if(nParaCount)
/*N*/ 			{
/*N*/ 				SfxItemSet aNewSet(pOutliner->GetParaAttribs(0));
/*N*/ 				mpObjectItemSet->Put(aNewSet);
/*N*/ 			}
/*N*/ 
/*N*/ 			OutlinerParaObject* pTemp = pOutliner->CreateParaObject(0, nParaCount);
/*N*/ 			pOutliner->Clear();
/*N*/ 			NbcSetOutlinerParaObject(pTemp);
/*N*/ 		}
/*N*/ 	}
/*N*/ 
/*N*/ 	// Extra-Repaint wenn das Layout so radikal geaendert wird (#43139#)
/*N*/ 	if(SFX_ITEM_SET == mpObjectItemSet->GetItemState(SDRATTR_TEXT_CONTOURFRAME))
/*N*/ 		SendRepaintBroadcast();
/*N*/ 
/*N*/ 	// call parent
/*N*/ 	SdrAttrObj::ItemSetChanged(rSet);
/*N*/ }

////////////////////////////////////////////////////////////////////////////////////////////////////

/*N*/ void SdrTextObj::ItemChange(const sal_uInt16 nWhich, const SfxPoolItem* pNewItem)
/*N*/ {
/*N*/ 	if( pNewItem && nWhich == SDRATTR_TEXTDIRECTION )
/*N*/ 	{
/*N*/ 		bool bVertical = ( (SvxWritingModeItem*) pNewItem )->GetValue() == ::com::sun::star::text::WritingMode_TB_RL;
/*N*/ 
/*N*/ 		if( bVertical || pOutlinerParaObject )
/*N*/ 		{
/*N*/ 			SetVerticalWriting( bVertical );
/*N*/ 		}
/*N*/ 	}
/*N*/ 
/*N*/ 	// #95501# reset to default
/*N*/ 	if(!pNewItem && !nWhich && pOutlinerParaObject)
/*N*/ 	{
/*?*/ 		SdrOutliner& rOutliner = ImpGetDrawOutliner();
/*?*/ 		rOutliner.SetText(*pOutlinerParaObject);
/*?*/ 		sal_uInt16 nParaCount(sal_uInt16(rOutliner.GetParagraphCount()));
/*?*/ 		
/*?*/ 		if(nParaCount) 
/*?*/ 		{
/*?*/ 			DBG_BF_ASSERT(0, "STRIP"); //STRIP001 ESelection aSelection( 0, 0, EE_PARA_ALL, EE_PARA_ALL);
//STRIP001 /*?*/ 			rOutliner.RemoveAttribs(aSelection, TRUE, 0);
//STRIP001 /*?*/ 
//STRIP001 /*?*/ 			OutlinerParaObject* pTemp = rOutliner.CreateParaObject(0, nParaCount);
//STRIP001 /*?*/ 			rOutliner.Clear();
//STRIP001 /*?*/ 			NbcSetOutlinerParaObject(pTemp);
/*?*/ 		}
/*N*/ 	}
/*N*/ 
/*N*/ 	SdrAttrObj::ItemChange( nWhich, pNewItem );
/*N*/ }

////////////////////////////////////////////////////////////////////////////////////////////////////

//STRIP001 void SdrTextObj::BurnInStyleSheetAttributes( BOOL bPseudoSheetsOnly )
//STRIP001 {
//STRIP001 	SdrAttrObj::BurnInStyleSheetAttributes();
//STRIP001 
//STRIP001 	if ( pModel && pOutlinerParaObject && !pEdtOutl && !IsLinkedText() )
//STRIP001 	{
//STRIP001 		Outliner* pOutliner = SdrMakeOutliner( OUTLINERMODE_OUTLINEOBJECT, pModel );
//STRIP001 		pOutliner->SetText( *pOutlinerParaObject );
//STRIP001 
//STRIP001 		USHORT nParaCount = (USHORT) pOutliner->GetParagraphCount();
//STRIP001 		if ( nParaCount > 0 )
//STRIP001 		{
//STRIP001 			BOOL bBurnIn = FALSE;
//STRIP001 
//STRIP001 			for ( USHORT nPara = 0; nPara < nParaCount; nPara++ )
//STRIP001 			{
//STRIP001 				SfxStyleSheet* pSheet = pOutliner->GetStyleSheet( nPara );
//STRIP001 				if( pSheet && ( !bPseudoSheetsOnly || pSheet->GetFamily() == SFX_STYLE_FAMILY_PSEUDO ) )
//STRIP001 				{
//STRIP001 					SfxItemSet aParaSet( pOutliner->GetParaAttribs( nPara ) );
//STRIP001 
//STRIP001 					SfxItemSet aSet( *aParaSet.GetPool() );
//STRIP001 					aSet.Put( pSheet->GetItemSet() );
//STRIP001 
//STRIP001 					/** the next code handles a special case for paragraphs that contain a
//STRIP001 						url field. The color for URL fields is either the system color for
//STRIP001 						urls or the char color attribute that formats the portion in which the
//STRIP001 						url field is contained.
//STRIP001 						When we set a char color attribute to the paragraphs item set from the
//STRIP001 						styles item set, we would have this char color attribute as an attribute
//STRIP001 						that is spanned over the complete paragraph after xml import due to some
//STRIP001 						problems in the xml import (using a XCursor on import so it does not know
//STRIP001 						the paragraphs and can't set char attributes to paragraphs ).
//STRIP001 
//STRIP001 						To avoid this, as soon as we try to set a char color attribute from the style
//STRIP001 						we
//STRIP001 						1. check if we have at least one url field in this paragraph
//STRIP001 						2. if we found at least one url field, we span the char color attribute over
//STRIP001 						   all portions that are not url fields and remove the char color attribute
//STRIP001 						   from the paragraphs item set
//STRIP001 					*/
//STRIP001 
//STRIP001 					bool bHasURL = false;
//STRIP001 					if( SFX_ITEM_SET == aSet.GetItemState(EE_CHAR_COLOR) )
//STRIP001 					{
//STRIP001 
//STRIP001 						EditEngine* pEditEngine = const_cast<EditEngine*>( &(pOutliner->GetEditEngine()) );
//STRIP001 
//STRIP001 						EECharAttribArray aAttribs;
//STRIP001 						pEditEngine->GetCharAttribs( nPara, aAttribs );
//STRIP001 						USHORT nAttrib;
//STRIP001 
//STRIP001 						for( nAttrib = 0; nAttrib < aAttribs.Count(); nAttrib++ )
//STRIP001 						{
//STRIP001 							struct EECharAttrib aAttrib(aAttribs.GetObject( nAttrib ));
//STRIP001 							if( aAttrib.pAttr->Which() == EE_FEATURE_FIELD )
//STRIP001 							{
//STRIP001 								if( aAttrib.pAttr )
//STRIP001 								{
//STRIP001 									SvxFieldItem* pFieldItem = (SvxFieldItem*)aAttrib.pAttr;
//STRIP001 									if( pFieldItem )
//STRIP001 									{
//STRIP001 										const SvxFieldData* pData = pFieldItem->GetField();
//STRIP001 										if( pData && pData->ISA( SvxURLField ) )
//STRIP001 										{
//STRIP001 											bHasURL = true;
//STRIP001 											break;
//STRIP001 										}
//STRIP001 									}
//STRIP001 								}
//STRIP001 							}
//STRIP001 						}
//STRIP001 
//STRIP001 					
//STRIP001 						if( bHasURL )
//STRIP001 						{
//STRIP001 							SfxItemSet aColorSet( *aSet.GetPool(), EE_CHAR_COLOR, EE_CHAR_COLOR );
//STRIP001 							aColorSet.Put( aSet, FALSE );
//STRIP001 
//STRIP001 							ESelection aSel( nPara, 0 );
//STRIP001 							for( nAttrib = 0; nAttrib < aAttribs.Count(); nAttrib++ )
//STRIP001 							{
//STRIP001 								struct EECharAttrib aAttrib(aAttribs.GetObject( nAttrib ));
//STRIP001 								if( aAttrib.pAttr->Which() == EE_FEATURE_FIELD )
//STRIP001 								{
//STRIP001 									aSel.nEndPos = aAttrib.nStart;
//STRIP001 									if( aSel.nStartPos != aSel.nEndPos )
//STRIP001 										pEditEngine->QuickSetAttribs( aColorSet, aSel );
//STRIP001 
//STRIP001 									aSel.nStartPos = aAttrib.nEnd;
//STRIP001 								}
//STRIP001 							}
//STRIP001 							aSel.nEndPos = pEditEngine->GetTextLen( nPara );
//STRIP001 							if( aSel.nStartPos != aSel.nEndPos )
//STRIP001 								pEditEngine->QuickSetAttribs( aColorSet, aSel );
//STRIP001 						}
//STRIP001 						
//STRIP001 					}
//STRIP001 
//STRIP001 					aSet.Put( aParaSet, FALSE );
//STRIP001 
//STRIP001 					if( bHasURL )
//STRIP001 						aSet.ClearItem( EE_CHAR_COLOR );
//STRIP001 
//STRIP001 					pOutliner->SetParaAttribs( nPara, aSet );
//STRIP001 					bBurnIn = TRUE;
//STRIP001 				}
//STRIP001 			}
//STRIP001 
//STRIP001 			if( bBurnIn )
//STRIP001 			{
//STRIP001 				OutlinerParaObject* pTemp = pOutliner->CreateParaObject( 0, nParaCount );
//STRIP001 				NbcSetOutlinerParaObject( pTemp );
//STRIP001 			}
//STRIP001 		}
//STRIP001 
//STRIP001 		delete pOutliner;
//STRIP001 	}
//STRIP001 }

/*N*/ FASTBOOL SdrTextObj::AdjustTextFrameWidthAndHeight(Rectangle& rR, FASTBOOL bHgt, FASTBOOL bWdt) const
/*N*/ {
/*N*/ 	if (bTextFrame && pModel!=NULL && !rR.IsEmpty()) {
/*N*/ 		SdrFitToSizeType eFit=GetFitToSize();
/*N*/ 		FASTBOOL bFitToSize=(eFit==SDRTEXTFIT_PROPORTIONAL || eFit==SDRTEXTFIT_ALLLINES);
/*N*/ 		FASTBOOL bWdtGrow=bWdt && IsAutoGrowWidth();
/*N*/ 		FASTBOOL bHgtGrow=bHgt && IsAutoGrowHeight();
/*N*/ 		SdrTextAniKind eAniKind=GetTextAniKind();
/*N*/ 		SdrTextAniDirection eAniDir=GetTextAniDirection();
/*N*/ 		FASTBOOL bScroll=eAniKind==SDRTEXTANI_SCROLL || eAniKind==SDRTEXTANI_ALTERNATE || eAniKind==SDRTEXTANI_SLIDE;
/*N*/ 		FASTBOOL bHScroll=bScroll && (eAniDir==SDRTEXTANI_LEFT || eAniDir==SDRTEXTANI_RIGHT);
/*N*/ 		FASTBOOL bVScroll=bScroll && (eAniDir==SDRTEXTANI_UP || eAniDir==SDRTEXTANI_DOWN);
/*N*/ 		if (!bFitToSize && (bWdtGrow || bHgtGrow)) {
/*N*/ 			Rectangle aR0(rR);
/*N*/ 			long nHgt=0,nMinHgt=0,nMaxHgt=0;
/*N*/ 			long nWdt=0,nMinWdt=0,nMaxWdt=0;
/*N*/ 			Size aSiz(rR.GetSize()); aSiz.Width()--; aSiz.Height()--;
/*N*/ 			Size aMaxSiz(100000,100000);
/*N*/ 			Size aTmpSiz(pModel->GetMaxObjSize());
/*N*/ 			if (aTmpSiz.Width()!=0) aMaxSiz.Width()=aTmpSiz.Width();
/*N*/ 			if (aTmpSiz.Height()!=0) aMaxSiz.Height()=aTmpSiz.Height();
/*N*/ 			if (bWdtGrow) {
/*N*/ 				nMinWdt=GetMinTextFrameWidth();
/*N*/ 				nMaxWdt=GetMaxTextFrameWidth();
/*N*/ 				if (nMaxWdt==0 || nMaxWdt>aMaxSiz.Width()) nMaxWdt=aMaxSiz.Width();
/*N*/ 				if (nMinWdt<=0) nMinWdt=1;
/*N*/ 				aSiz.Width()=nMaxWdt;
/*N*/ 			}
/*N*/ 			if (bHgtGrow) {
/*N*/ 				nMinHgt=GetMinTextFrameHeight();
/*N*/ 				nMaxHgt=GetMaxTextFrameHeight();
/*N*/ 				if (nMaxHgt==0 || nMaxHgt>aMaxSiz.Height()) nMaxHgt=aMaxSiz.Height();
/*N*/ 				if (nMinHgt<=0) nMinHgt=1;
/*N*/ 				aSiz.Height()=nMaxHgt;
/*N*/ 			}
/*N*/ 			long nHDist=GetTextLeftDistance()+GetTextRightDistance();
/*N*/ 			long nVDist=GetTextUpperDistance()+GetTextLowerDistance();
/*N*/ 			aSiz.Width()-=nHDist;
/*N*/ 			aSiz.Height()-=nVDist;
/*N*/ 			if (aSiz.Width()<2) aSiz.Width()=2;   // Mindestgroesse 2
/*N*/ 			if (aSiz.Height()<2) aSiz.Height()=2; // Mindestgroesse 2
/*N*/ 
/*N*/ 			// #101684#
/*N*/ 			BOOL bInEditMode = IsInEditMode();
/*N*/ 			
/*N*/ 			if(!bInEditMode)
/*N*/ 			{
/*N*/ 				if (bHScroll) aSiz.Width()=0x0FFFFFFF; // Laufschrift nicht umbrechen
/*N*/ 				if (bVScroll) aSiz.Height()=0x0FFFFFFF;
/*N*/ 			}
/*N*/ 
/*N*/ 			if(pEdtOutl)
/*N*/ 			{
/*?*/ 				pEdtOutl->SetMaxAutoPaperSize(aSiz);
/*?*/ 				if (bWdtGrow) {
/*?*/ 					Size aSiz(pEdtOutl->CalcTextSize());
/*?*/ 					nWdt=aSiz.Width()+1; // lieber etwas Tolleranz
/*?*/ 					if (bHgtGrow) nHgt=aSiz.Height()+1; // lieber etwas Tolleranz
/*?*/ 				} else {
/*?*/ 					nHgt=pEdtOutl->GetTextHeight()+1; // lieber etwas Tolleranz
/*?*/ 				}
/*N*/ 			} else {
/*N*/ 				Outliner& rOutliner=ImpGetDrawOutliner();
/*N*/ 				rOutliner.SetPaperSize(aSiz);
/*N*/ 				rOutliner.SetUpdateMode(TRUE);
/*N*/ 				// !!! hier sollte ich wohl auch noch mal die Optimierung mit
/*N*/ 				// bPortionInfoChecked usw einbauen
/*N*/ 				if (pOutlinerParaObject!=NULL) rOutliner.SetText(*pOutlinerParaObject);
/*N*/ 				if (bWdtGrow) {
/*N*/ 					Size aSiz(rOutliner.CalcTextSize());
/*N*/ 					nWdt=aSiz.Width()+1; // lieber etwas Tolleranz
/*N*/ 					if (bHgtGrow) nHgt=aSiz.Height()+1; // lieber etwas Tolleranz
/*N*/ 				} else {
/*N*/ 					nHgt=rOutliner.GetTextHeight()+1; // lieber etwas Tolleranz
/*N*/ 				}
/*N*/ 				rOutliner.Clear();
/*N*/ 			}
/*N*/ 			if (nWdt<nMinWdt) nWdt=nMinWdt;
/*N*/ 			if (nWdt>nMaxWdt) nWdt=nMaxWdt;
/*N*/ 			nWdt+=nHDist;
/*N*/ 			if (nWdt<1) nWdt=1; // nHDist kann auch negativ sein
/*N*/ 			if (nHgt<nMinHgt) nHgt=nMinHgt;
/*N*/ 			if (nHgt>nMaxHgt) nHgt=nMaxHgt;
/*N*/ 			nHgt+=nVDist;
/*N*/ 			if (nHgt<1) nHgt=1; // nVDist kann auch negativ sein
/*N*/ 			long nWdtGrow=nWdt-(rR.Right()-rR.Left());
/*N*/ 			long nHgtGrow=nHgt-(rR.Bottom()-rR.Top());
/*N*/ 			if (nWdtGrow==0) bWdtGrow=FALSE;
/*N*/ 			if (nHgtGrow==0) bHgtGrow=FALSE;
/*N*/ 			if (bWdtGrow || bHgtGrow) {
/*N*/ 				if (bWdtGrow) {
/*N*/ 					SdrTextHorzAdjust eHAdj=GetTextHorizontalAdjust();
/*N*/ 					if (eHAdj==SDRTEXTHORZADJUST_LEFT) rR.Right()+=nWdtGrow;
/*N*/ 					else if (eHAdj==SDRTEXTHORZADJUST_RIGHT) rR.Left()-=nWdtGrow;
/*N*/ 					else {
/*N*/ 						long nWdtGrow2=nWdtGrow/2;
/*N*/ 						rR.Left()-=nWdtGrow2;
/*N*/ 						rR.Right()=rR.Left()+nWdt;
/*N*/ 					}
/*N*/ 				}
/*N*/ 				if (bHgtGrow) {
/*N*/ 					SdrTextVertAdjust eVAdj=GetTextVerticalAdjust();
/*N*/ 					if (eVAdj==SDRTEXTVERTADJUST_TOP) rR.Bottom()+=nHgtGrow;
/*N*/ 					else if (eVAdj==SDRTEXTVERTADJUST_BOTTOM) rR.Top()-=nHgtGrow;
/*N*/ 					else {
/*N*/ 						long nHgtGrow2=nHgtGrow/2;
/*N*/ 						rR.Top()-=nHgtGrow2;
/*N*/ 						rR.Bottom()=rR.Top()+nHgt;
/*N*/ 					}
/*N*/ 				}
/*N*/ 				if (aGeo.nDrehWink!=0) {
/*N*/ 					Point aD1(rR.TopLeft());
/*N*/ 					aD1-=aR0.TopLeft();
/*N*/ 					Point aD2(aD1);
/*N*/ 					RotatePoint(aD2,Point(),aGeo.nSin,aGeo.nCos);
/*N*/ 					aD2-=aD1;
/*N*/ 					rR.Move(aD2.X(),aD2.Y());
/*N*/ 				}
/*N*/ 				return TRUE;
/*N*/ 			}
/*N*/ 		}
/*N*/ 	}
/*N*/ 	return FALSE;
/*N*/ }

/*N*/ FASTBOOL SdrTextObj::NbcAdjustTextFrameWidthAndHeight(FASTBOOL bHgt, FASTBOOL bWdt)
/*N*/ {
/*N*/ 	FASTBOOL bRet=AdjustTextFrameWidthAndHeight(aRect,bHgt,bWdt);
/*N*/ 	if (bRet) {
/*N*/ 		SetRectsDirty();
/*N*/ 		if (HAS_BASE(SdrRectObj,this)) { // mal wieder 'nen Hack
/*N*/ 			((SdrRectObj*)this)->SetXPolyDirty();
/*N*/ 		}
/*N*/ 		if (HAS_BASE(SdrCaptionObj,this)) { // mal wieder 'nen Hack
/*N*/ 			((SdrCaptionObj*)this)->ImpRecalcTail();
/*N*/ 		}
/*N*/ 	}
/*N*/ 	return bRet;
/*N*/ }

//STRIP001 FASTBOOL SdrTextObj::AdjustTextFrameWidthAndHeight(FASTBOOL bHgt, FASTBOOL bWdt)
//STRIP001 {
//STRIP001 	Rectangle aNeuRect(aRect);
//STRIP001 	FASTBOOL bRet=AdjustTextFrameWidthAndHeight(aNeuRect,bHgt,bWdt);
//STRIP001 	if (bRet) {
//STRIP001 		Rectangle aBoundRect0; if (pUserCall!=NULL) aBoundRect0=GetBoundRect();
//STRIP001 		SendRepaintBroadcast();
//STRIP001 		aRect=aNeuRect;
//STRIP001 		SetRectsDirty();
//STRIP001 		if (HAS_BASE(SdrRectObj,this)) { // mal wieder 'nen Hack
//STRIP001 			((SdrRectObj*)this)->SetXPolyDirty();
//STRIP001 		}
//STRIP001 		if (HAS_BASE(SdrCaptionObj,this)) { // mal wieder 'nen Hack
//STRIP001 			((SdrCaptionObj*)this)->ImpRecalcTail();
//STRIP001 		}
//STRIP001 		SetChanged();
//STRIP001 		SendRepaintBroadcast();
//STRIP001 		SendUserCall(SDRUSERCALL_RESIZE,aBoundRect0);
//STRIP001 	}
//STRIP001 	return bRet;
//STRIP001 }

/*N*/ void SdrTextObj::ImpSetTextStyleSheetListeners()
/*N*/ {
/*N*/ 	SfxStyleSheetBasePool* pStylePool=pModel!=NULL ? pModel->GetStyleSheetPool() : NULL;
/*N*/ 	if (pStylePool!=NULL) {
/*N*/ 		Container aStyles(1024,64,64);
/*N*/ 		if (pOutlinerParaObject!=NULL) {
/*N*/ 			// Zunaechst werden alle im ParaObject enthaltenen StyleSheets
/*N*/ 			// im Container aStyles gesammelt. Dazu wird die Family jeweils
/*N*/ 			// ans Ende des StyleSheet-Namen drangehaengt.
/*N*/ 			const EditTextObject& rTextObj=pOutlinerParaObject->GetTextObject();
/*N*/ 			XubString aStyleName;
/*N*/ 			SfxStyleFamily eStyleFam;
/*N*/ 			USHORT nParaAnz=rTextObj.GetParagraphCount();
/*N*/ 
/*N*/ 			for(UINT16 nParaNum(0); nParaNum < nParaAnz; nParaNum++)
/*N*/ 			{
/*N*/ 				rTextObj.GetStyleSheet(nParaNum, aStyleName, eStyleFam);
/*N*/ 
/*N*/ 				if(aStyleName.Len())
/*N*/ 				{
/*N*/ 					XubString aFam = UniString::CreateFromInt32((UINT16)eStyleFam);
/*N*/ 					aFam.Expand(5);
/*N*/ 
/*N*/ 					aStyleName += sal_Unicode('|');
/*N*/ 					aStyleName += aFam;
/*N*/ 
/*N*/ 					BOOL bFnd(FALSE);
/*N*/ 					UINT32 nNum(aStyles.Count());
/*N*/ 
/*N*/ 					while(!bFnd && nNum > 0)
/*N*/ 					{
/*N*/ 						// kein StyleSheet doppelt!
/*N*/ 						nNum--;
/*N*/ 						bFnd = (aStyleName.Equals(*(XubString*)aStyles.GetObject(nNum)));
/*N*/ 					}
/*N*/ 
/*N*/ 					if(!bFnd)
/*N*/ 					{
/*N*/ 						aStyles.Insert(new XubString(aStyleName), CONTAINER_APPEND);
/*N*/ 					}
/*N*/ 				}
/*N*/ 			}
/*N*/ 		}
/*N*/ 
/*N*/ 		// nun die Strings im Container durch StyleSheet* ersetzten
/*N*/ 		ULONG nNum=aStyles.Count();
/*N*/ 		while (nNum>0) {
/*N*/ 			nNum--;
/*N*/ 			XubString* pName=(XubString*)aStyles.GetObject(nNum);
/*N*/ 
/*N*/ 			// UNICODE: String aFam(pName->Cut(pName->Len()-6));
/*N*/ 			String aFam = pName->Copy(0, pName->Len() - 6);
/*N*/ 
/*N*/ 			aFam.Erase(0,1);
/*N*/ 			aFam.EraseTrailingChars();
/*N*/ 
/*N*/ 			// UNICODE: USHORT nFam=USHORT(aFam);
/*N*/ 			UINT16 nFam = (UINT16)aFam.ToInt32();
/*N*/ 
/*N*/ 			SfxStyleFamily eFam=(SfxStyleFamily)nFam;
/*N*/ 			SfxStyleSheetBase* pStyleBase=pStylePool->Find(*pName,eFam);
/*N*/ 			SfxStyleSheet* pStyle=PTR_CAST(SfxStyleSheet,pStyleBase);
/*N*/ 			delete pName;
/*N*/ 			if (pStyle!=NULL && pStyle!=GetStyleSheet()) {
/*?*/ 				aStyles.Replace(pStyle,nNum);
/*N*/ 			} else {
/*N*/ 				aStyles.Remove(nNum);
/*N*/ 			}
/*N*/ 		}
/*N*/ 		// jetzt alle ueberfluessigen StyleSheets entfernen
/*N*/ 		nNum=GetBroadcasterCount();
/*N*/ 		while (nNum>0) {
/*N*/ 			nNum--;
/*N*/ 			SfxBroadcaster* pBroadcast=GetBroadcasterJOE((USHORT)nNum);
/*N*/ 			SfxStyleSheet* pStyle=PTR_CAST(SfxStyleSheet,pBroadcast);
/*N*/ 			if (pStyle!=NULL && pStyle!=GetStyleSheet()) { // Sonderbehandlung fuer den StyleSheet des Objekts
/*N*/ 				if (aStyles.GetPos(pStyle)==CONTAINER_ENTRY_NOTFOUND) {
/*N*/ 					EndListening(*pStyle);
/*N*/ 				}
/*N*/ 			}
/*N*/ 		}
/*N*/ 		// und schliesslich alle in aStyles enthaltenen StyleSheets mit den vorhandenen Broadcastern mergen
/*N*/ 		nNum=aStyles.Count();
/*N*/ 		while (nNum>0) {
/*N*/ 			nNum--;
/*N*/ 			SfxStyleSheet* pStyle=(SfxStyleSheet*)aStyles.GetObject(nNum);
/*N*/ 			// StartListening soll selbst nachsehen, ob hier nicht evtl. schon gehorcht wird
/*N*/ 			StartListening(*pStyle,TRUE);
/*N*/ 		}
/*N*/ 	}
/*N*/ }

/*N*/ void SdrTextObj::NbcResizeTextAttributes(const Fraction& xFact, const Fraction& yFact)
/*N*/ {
/*N*/ 	if (pOutlinerParaObject!=NULL && xFact.IsValid() && yFact.IsValid()) {
/*N*/ 		Fraction n100(100,1);
/*N*/ 		long nX=long(xFact*n100);
/*N*/ 		long nY=long(yFact*n100);
/*N*/ 		if (nX<0) nX=-nX;
/*N*/ 		if (nX<1) nX=1;
/*N*/ 		if (nX>0xFFFF) nX=0xFFFF;
/*N*/ 		if (nY<0) nY=-nY;
/*N*/ 		if (nY<1) nY=1;
/*N*/ 		if (nY>0xFFFF) nY=0xFFFF;
/*N*/ 		if (nX!=100 || nY!=100)
/*N*/ 		{
/*N*/ 			// Rahmenattribute
/*N*/ 			const SfxItemSet& rSet = GetItemSet();
/*N*/ 			const SvxCharScaleWidthItem& rOldWdt=(SvxCharScaleWidthItem&)rSet.Get(EE_CHAR_FONTWIDTH);
/*N*/ 			const SvxFontHeightItem& rOldHgt=(SvxFontHeightItem&)rSet.Get(EE_CHAR_FONTHEIGHT);
/*N*/ 
/*N*/ 			// erstmal die alten Werte holen
/*N*/ 			long nRelWdt=rOldWdt.GetValue();
/*N*/ 			long nAbsHgt=rOldHgt.GetHeight();
/*N*/ 			long nRelHgt=rOldHgt.GetProp();
/*N*/ 
/*N*/ 			// Relative Breite aendern
/*N*/ 			nRelWdt*=nX;
/*N*/ 			nRelWdt/=nY;
/*N*/ 			if (nRelWdt<0) nRelWdt=-nRelWdt; // nicht negativ
/*N*/ 			if (nRelWdt<=0) nRelWdt=1;       // und mind. 1%
/*N*/ 			if (nRelWdt>0xFFFF) nRelWdt=0xFFFF;
/*N*/ 
/*N*/ 			// Absolute Hoehe aendern
/*N*/ 			nAbsHgt*=nY;
/*N*/ 			nAbsHgt/=100;
/*N*/ 			if (nAbsHgt<0) nAbsHgt=-nAbsHgt; // nicht negativ
/*N*/ 			if (nAbsHgt<=0) nAbsHgt=1;       // und mind. 1
/*N*/ 			if (nAbsHgt>0xFFFF) nAbsHgt=0xFFFF;
/*N*/ 
/*N*/ 			// und nun attributieren
/*N*/ 			SetItem(SvxCharScaleWidthItem( (USHORT) nRelWdt));
/*N*/ 			SetItem(SvxFontHeightItem(nAbsHgt,(USHORT)nRelHgt));
/*N*/ 			// Zeichen- und Absatzattribute innerhalb des OutlinerParaObjects
/*N*/ 			Outliner& rOutliner=ImpGetDrawOutliner();
/*N*/ 			rOutliner.SetPaperSize(Size(LONG_MAX,LONG_MAX));
/*N*/ 			rOutliner.SetText(*pOutlinerParaObject);
/*N*/ 			rOutliner.DoStretchChars((USHORT)nX,(USHORT)nY);
/*N*/ 			OutlinerParaObject* pNewPara=rOutliner.CreateParaObject();
/*N*/ 			NbcSetOutlinerParaObject(pNewPara);
/*N*/ 			rOutliner.Clear();
/*N*/ 		}
/*N*/ 	}
/*N*/ }

/** #103836# iterates over the paragraphs of a given SdrObject and removes all
             hard set character attributes with the which ids contained in the 
             given vector
*/
//STRIP001 void SdrTextObj::RemoveOutlinerCharacterAttribs( const std::vector<sal_uInt16>& rCharWhichIds )
//STRIP001 {
//STRIP001 	if(pOutlinerParaObject)
//STRIP001 	{
//STRIP001 		Outliner* pOutliner = pEdtOutl;
//STRIP001 
//STRIP001 		if(!pOutliner)
//STRIP001 		{
//STRIP001 			pOutliner = &ImpGetDrawOutliner();
//STRIP001 			pOutliner->SetText(*pOutlinerParaObject);
//STRIP001 		}
//STRIP001 
//STRIP001 		ESelection aSelAll( 0, 0, 0xffff, 0xffff );
//STRIP001 		std::vector<sal_uInt16>::const_iterator aIter( rCharWhichIds.begin() );
//STRIP001 		while( aIter != rCharWhichIds.end() )
//STRIP001 		{
//STRIP001 			pOutliner->RemoveAttribs( aSelAll, false, (*aIter++) );
//STRIP001 		}
//STRIP001 
//STRIP001 		if(!pEdtOutl)
//STRIP001 		{
//STRIP001 			const sal_uInt16 nParaCount = pOutliner->GetParagraphCount();
//STRIP001 			OutlinerParaObject* pTemp = pOutliner->CreateParaObject(0, nParaCount);
//STRIP001 			pOutliner->Clear();
//STRIP001 			NbcSetOutlinerParaObject(pTemp);
//STRIP001 		}
//STRIP001 	}
//STRIP001 }
}
