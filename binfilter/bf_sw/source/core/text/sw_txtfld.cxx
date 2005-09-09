/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: sw_txtfld.cxx,v $
 *
 *  $Revision: 1.5 $
 *
 *  last change: $Author: rt $ $Date: 2005-09-09 02:32:24 $
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


#pragma hdrstop

// auto strip #include "hintids.hxx"

#ifndef _FMTFLD_HXX //autogen
#include <fmtfld.hxx>
#endif
#ifndef _TXTFLD_HXX //autogen
#include <txtfld.hxx>
#endif
#ifndef _CHARFMT_HXX //autogen
#include <charfmt.hxx>
#endif

#include "viewsh.hxx"   // NewFldPortion, GetDoc()

#ifndef _HORIORNT_HXX
#include <horiornt.hxx>
#endif

#include "doc.hxx"      // NewFldPortion, GetSysFldType()
#include "rootfrm.hxx"  // Info ueber virt. PageNumber
#include "pagefrm.hxx"  // NewFldPortion, GetVirtPageNum()
#include "ndtxt.hxx"    // NewNumberPortion, pHints->GetNum()
// auto strip #include "fldbas.hxx"      // SwField
#include "viewopt.hxx"	// SwViewOptions
#include "flyfrm.hxx"	//IsInBody()
#include "viewimp.hxx"
// auto strip #include "txtatr.hxx"   // SwTxtFld

#include "txtcfg.hxx"

// auto strip #include "swfont.hxx"   // NewFldPortion, new SwFont
// auto strip #include "fntcache.hxx"   // NewFldPortion, SwFntAccess

// auto strip #include "porfld.hxx"
#include "porftn.hxx"   // NewExtraPortion
// auto strip #include "porref.hxx"   // NewExtraPortion
#include "portox.hxx"   // NewExtraPortion
#include "porhyph.hxx"   // NewExtraPortion
#include "porfly.hxx"   // NewExtraPortion
#include "itrform2.hxx"   // SwTxtFormatter

#include "chpfld.hxx"
#include "dbfld.hxx"
#include "expfld.hxx"
#include "docufld.hxx"
#include "pagedesc.hxx"  // NewFldPortion, GetNum()
// auto strip #ifndef _PORMULTI_HXX
// auto strip #include <pormulti.hxx> 	// SwMultiPortion
// auto strip #endif
namespace binfilter {


/*************************************************************************
 *                      SwTxtFormatter::NewFldPortion()
 *************************************************************************/


/*N*/ sal_Bool lcl_IsInBody( SwFrm *pFrm )
/*N*/ {
/*N*/ 	if ( pFrm->IsInDocBody() )
/*N*/ 		return sal_True;
/*N*/ 	else
/*N*/ 	{
/*N*/ 		SwFrm *pTmp = pFrm;
/*N*/ 		SwFlyFrm *pFly;
/*N*/ 		while ( 0 != (pFly = pTmp->FindFlyFrm()) )
/*N*/ 			pTmp = pFly->GetAnchor();
/*N*/ 		return pTmp->IsInDocBody();
/*N*/ 	}
/*N*/ }


/*N*/ SwExpandPortion *SwTxtFormatter::NewFldPortion( SwTxtFormatInfo &rInf,
/*N*/ 												const SwTxtAttr *pHint ) const
/*N*/ {
/*N*/ 	SwExpandPortion *pRet;
/*N*/ 	SwFrm *pFrame = (SwFrm*)pFrm;
/*N*/ 	SwField *pFld = (SwField*)pHint->GetFld().GetFld();
/*N*/ 	const sal_Bool bName = rInf.GetOpt().IsFldName();
/*N*/ 
/*N*/ 	SwCharFmt* pChFmt = 0;
/*N*/ 	sal_Bool bNewFlyPor = sal_False,
/*N*/ 		 bINet = sal_False;
/*N*/ 
/*N*/ 	// Sprache setzen
/*N*/ 	((SwTxtFormatter*)this)->SeekAndChg( rInf );
/*N*/ 	pFld->SetLanguage( GetFnt()->GetLanguage() );
/*N*/ 
/*N*/ 	ViewShell *pSh = rInf.GetVsh();
/*N*/ 
/*N*/ 	switch( pFld->GetTyp()->Which() )
/*N*/ 	{
/*N*/ 		case RES_SCRIPTFLD:
/*N*/ 		case RES_POSTITFLD:
                {DBG_BF_ASSERT(0, "STRIP");} //STRIP001 /*?*/ 			pRet = new SwPostItsPortion( RES_SCRIPTFLD == pFld->GetTyp()->Which() );
/*?*/ 			break;
/*?*/ 
/*?*/ 		case RES_COMBINED_CHARS:
/*?*/ 			{
/*?*/ 				String sStr( pFld->GetCntnt( bName ));
/*?*/ 				if( bName )
/*?*/ 					pRet = new SwFldPortion( sStr );
/*?*/ 				else
                        {DBG_BF_ASSERT(0, "STRIP");} //STRIP001 /*?*/ 					pRet = new SwCombinedPortion( sStr );
/*?*/ 			}
/*?*/ 			break;
/*N*/ 
/*N*/ 		case RES_HIDDENTXTFLD:
/*N*/ 			pRet = new SwHiddenPortion(pFld->GetCntnt( bName ));
/*N*/ 			break;
/*N*/ 
/*N*/ 		case RES_CHAPTERFLD:
/*N*/ 			if( !bName && pSh && !pSh->Imp()->IsUpdateExpFlds() )
/*N*/ 			{
/*N*/ 				((SwChapterField*)pFld)->ChangeExpansion( pFrame,
/*N*/ 										&((SwTxtFld*)pHint)->GetTxtNode() );
/*N*/ 			}
/*N*/ 			pRet = new SwFldPortion( pFld->GetCntnt( bName ) );
/*N*/ 			break;
/*N*/ 
/*N*/ 		case RES_DOCSTATFLD:
/*N*/ 			if( !bName && pSh && !pSh->Imp()->IsUpdateExpFlds() )
/*N*/ 				((SwDocStatField*)pFld)->ChangeExpansion( pFrame );
/*N*/ 			pRet = new SwFldPortion( pFld->GetCntnt( bName ) );
/*N*/ 			break;
/*N*/ 
/*N*/ 		case RES_PAGENUMBERFLD:
/*N*/ 		{
/*N*/ 			if( !bName && pSh && !pSh->Imp()->IsUpdateExpFlds() )
/*N*/ 			{
/*N*/ 				SwDoc* pDoc = pSh->GetDoc();
/*N*/ 				SwPageNumberFieldType *pPageNr = (SwPageNumberFieldType *)
/*N*/ 								pFld->GetTyp();
/*N*/ //???	            	            pDoc->GetSysFldType( RES_PAGENUMBERFLD );
/*N*/ 
/*N*/ //				SwPageFrm *pPage = pFrm->FindPageFrm();
/*N*/ //				sal_Bool bVirt = pPage && pPage->GetNext();
/*N*/ 				sal_Bool bVirt = pSh->GetLayout()->IsVirtPageNum();
/*N*/ 
/*N*/ 				MSHORT nVirtNum = pFrame->GetVirtPageNum(),
/*N*/ 					   nNumPages = pDoc->GetRootFrm()->GetPageNum();
/*N*/ 				sal_Int16 nNumFmt = -1;
/*N*/ 				if(SVX_NUM_PAGEDESC == pFld->GetFormat())
/*N*/ 					nNumFmt = pFrame->FindPageFrm()->GetPageDesc()->GetNumType().GetNumberingType();
/*N*/ 
/*N*/ 				pPageNr->ChangeExpansion( pDoc, nVirtNum, nNumPages,
/*N*/ 											bVirt, nNumFmt > -1 ? &nNumFmt : 0);
/*N*/ 			}
/*N*/ 			pRet = new SwFldPortion( pFld->GetCntnt( bName ) );
/*N*/ 			break;
/*N*/ 		}
/*N*/ 		case RES_GETEXPFLD:
/*N*/ 		{
/*N*/ 			if( !bName && pSh && !pSh->Imp()->IsUpdateExpFlds() )
/*N*/ 			{
/*N*/ 				SwGetExpField* pExpFld = (SwGetExpField*)pFld;
                        /*N*/ 				if( !::binfilter::lcl_IsInBody( pFrame ) )
/*N*/ 				{
/*?*/ 					DBG_BF_ASSERT(0, "STRIP"); //STRIP001 pExpFld->ChgBodyTxtFlag( sal_False );
//STRIP001 /*?*/ 					pExpFld->ChangeExpansion( *pFrame, *((SwTxtFld*)pHint) );
/*N*/ 				}
/*N*/ 				else if( !pExpFld->IsInBodyTxt() )
/*N*/ 				{
/*N*/ 					// war vorher anders, also erst expandieren, dann umsetzen!!
/*?*/ 					DBG_BF_ASSERT(0, "STRIP"); //STRIP001 pExpFld->ChangeExpansion( *pFrame, *((SwTxtFld*)pHint) );
//STRIP001 /*?*/ 					pExpFld->ChgBodyTxtFlag( sal_True );
/*N*/ 				}
/*N*/ 			}
/*N*/ 			pRet = new SwFldPortion( pFld->GetCntnt( bName ) );
/*N*/ 			break;
/*N*/ 		}
/*N*/ 		case RES_DBFLD:
/*N*/ 		{
/*N*/ 			if( !bName )
/*N*/ 			{
/*N*/ 				SwDBField* pDBFld = (SwDBField*)pFld;
/*N*/ 				pDBFld->ChgBodyTxtFlag( ::binfilter::lcl_IsInBody( pFrame ) );
 /* Solange das ChangeExpansion auskommentiert ist.
  * Aktualisieren in Kopf/Fuszeilen geht aktuell nicht.
                 if( !::binfilter::lcl_IsInBody( pFrame ) )
                 {
                     pDBFld->ChgBodyTxtFlag( sal_False );
                     pDBFld->ChangeExpansion( pFrame, (SwTxtFld*)pHint );
                 }
                 else if( !pDBFld->IsInBodyTxt() )
                 {
                     // war vorher anders, also erst expandieren, dann umsetzen!!
                     pDBFld->ChangeExpansion( pFrame, (SwTxtFld*)pHint );
                     pDBFld->ChgBodyTxtFlag( sal_True );
                 }
 */
/*N*/ 			}
/*N*/ 			pRet = new SwFldPortion( pFld->GetCntnt( bName ) );
/*N*/ 			break;
/*N*/ 		}
/*?*/ 		case RES_REFPAGEGETFLD:
/*?*/ 			if( !bName && pSh && !pSh->Imp()->IsUpdateExpFlds() )
                        /*?*/ 				{DBG_BF_ASSERT(0, "STRIP");} //STRIP001 ((SwRefPageGetField*)pFld)->ChangeExpansion( pFrame, (SwTxtFld*)pHint );
/*?*/ 			pRet = new SwFldPortion( pFld->GetCntnt( bName ) );
/*?*/ 			break;
/*N*/ 
/*N*/ 		case RES_JUMPEDITFLD:
/*N*/ 			if( !bName )
/*N*/ 				pChFmt =  ((SwJumpEditField*)pFld)->GetCharFmt();
/*N*/ 			bNewFlyPor = sal_True;
/*N*/ 			break;
/*N*/ 
/*N*/ 		default:
/*N*/ 		{
/*N*/ 			pRet = new SwFldPortion(pFld->GetCntnt( bName ) );
/*N*/ 		}
/*N*/ 	}
/*N*/ 
/*N*/ 	if( bNewFlyPor )
/*N*/ 	{
/*N*/ 		SwFont *pTmpFnt = 0;
/*N*/ 		if( !bName )
/*N*/ 		{
/*N*/ 			pTmpFnt = new SwFont( *pFnt );
/*N*/ 			if( bINet )
/*N*/ 			{
/*?*/ 				SwAttrPool* pPool = pChFmt->GetAttrSet().GetPool();
/*?*/ 				SfxItemSet aSet( *pPool, RES_CHRATR_BEGIN, RES_CHRATR_END );
/*?*/ 				SfxItemSet aTmpSet( aSet );
/*?*/ 				pFrm->GetTxtNode()->GetAttr(aSet,rInf.GetIdx(),rInf.GetIdx()+1);
/*?*/ 				aTmpSet.Set( pChFmt->GetAttrSet() );
/*?*/ 				aTmpSet.Differentiate( aSet );
/*?*/ 				if( aTmpSet.Count() )
/*?*/                     pTmpFnt->SetDiffFnt( &aTmpSet, rInf.GetDoc() );
/*N*/ 			}
/*N*/ 			else
/*N*/                 pTmpFnt->SetDiffFnt( &pChFmt->GetAttrSet(), rInf.GetDoc() );
/*N*/ 		}
/*N*/ 		pRet = new SwFldPortion( pFld->GetCntnt( bName ), pTmpFnt );
/*N*/ 	}
/*N*/ 
/*N*/ 	return pRet;
/*N*/ }


/*************************************************************************
 *                      SwTxtFormatter::NewExtraPortion()
 *************************************************************************/


/*N*/ SwLinePortion *SwTxtFormatter::NewExtraPortion( SwTxtFormatInfo &rInf )
/*N*/ {
/*N*/ 	SwTxtAttr *pHint = GetAttr( rInf.GetIdx() );
/*N*/ 	SwLinePortion *pRet = 0;
/*N*/ 	if( !pHint )
/*N*/ 	{
/*N*/ #if OSL_DEBUG_LEVEL > 1
/*N*/ //        aDbstream << "NewExtraPortion: hint not found?" << endl;
/*N*/ #endif
/*?*/ 		pRet = new SwTxtPortion;
/*?*/ 		pRet->SetLen( 1 );
/*?*/ 		rInf.SetLen( 1 );
/*?*/ 		return pRet;
/*N*/ 	}
/*N*/ 
/*N*/ 	switch( pHint->Which() )
/*N*/ 	{
/*N*/ 		case RES_TXTATR_FLYCNT :
/*N*/ 		{
/*N*/ 			pRet = NewFlyCntPortion( rInf, pHint );
/*N*/ 			break;
/*N*/ 		}
/*N*/ 		case RES_TXTATR_FTN :
/*N*/ 		{
/*N*/ 			pRet = NewFtnPortion( rInf, pHint );
/*N*/ 			break;
/*N*/ 		}
/*?*/ 		case RES_TXTATR_SOFTHYPH :
/*?*/ 		{
/*?*/ 			pRet = new SwSoftHyphPortion;
/*?*/ 			break;
/*?*/ 		}
/*?*/ 		case RES_TXTATR_HARDBLANK :
/*?*/ 		{
                {DBG_BF_ASSERT(0, "STRIP");} //STRIP001 /*?*/ 			pRet = new SwBlankPortion( ((SwTxtHardBlank*)pHint)->GetChar() );
//STRIP001 /*?*/ 			break;
/*?*/ 		}
/*N*/ 		case RES_TXTATR_FIELD :
/*N*/ 		{
/*N*/ 			pRet = NewFldPortion( rInf, pHint );
/*N*/ 			break;
/*N*/ 		}
/*?*/ 		case RES_TXTATR_REFMARK :
                {DBG_BF_ASSERT(0, "STRIP");} //STRIP001 /*?*/ 		{
//STRIP001 /*?*/ 			pRet = new SwIsoRefPortion;
//STRIP001 /*?*/ 			break;
//STRIP001 /*?*/ 		}
/*N*/ 		case RES_TXTATR_TOXMARK :
/*N*/ 		{
/*N*/ 			pRet = new SwIsoToxPortion;
/*N*/ 			break;
/*N*/ 		}
/*N*/ 		default: ;
/*N*/ 	}
/*N*/ 	if( !pRet )
/*N*/ 	{
/*N*/ #if OSL_DEBUG_LEVEL > 1
/*N*/ //        aDbstream << "NewExtraPortion: unknown hint" << endl;
/*N*/ #endif
/*?*/ 		const XubString aNothing;
/*?*/ 		pRet = new SwFldPortion( aNothing );
/*?*/ 		rInf.SetLen( 1 );
/*N*/ 	}
/*N*/ 	return pRet;
/*N*/ }

/*************************************************************************
 *                      SwTxtFormatter::NewNumberPortion()
 *************************************************************************/


/*N*/ SwNumberPortion *SwTxtFormatter::NewNumberPortion( SwTxtFormatInfo &rInf ) const
/*N*/ {
/*N*/ 	if( rInf.IsNumDone() || rInf.GetTxtStart() != nStart
/*N*/ 				|| rInf.GetTxtStart() != rInf.GetIdx() )
/*N*/ 		return 0;
/*N*/ 
/*N*/ 	SwNumberPortion *pRet = 0;
/*N*/ 	const SwTxtNode* pTxtNd = GetTxtFrm()->GetTxtNode();
/*N*/ 	const SwNumRule* pNumRule = pTxtNd->GetNumRule();
/*N*/ 	const SwNodeNum* pNum = pTxtNd->GetNum();
/*N*/ 
/*N*/ 	if( !pNumRule )		// oder sollte OutlineNum an sein?
/*N*/ 	{
/*N*/ 		pNum = pTxtNd->GetOutlineNum();
/*N*/ 		if( pNum )
/*N*/ 			pNumRule = pTxtNd->GetDoc()->GetOutlineNumRule();
/*N*/ 	}
/*N*/ 	// hat ein "gueltige" Nummer ?
/*N*/ 	if( pNumRule && pNum && MAXLEVEL > pNum->GetLevel() )
/*N*/ 	{
/*N*/ 		CONST SwNumFmt &rNumFmt = pNumRule->Get( pNum->GetLevel() );
/*N*/ 		const sal_Bool bLeft = SVX_ADJUST_LEFT == rNumFmt.GetNumAdjust();
/*N*/ 		const sal_Bool bCenter = SVX_ADJUST_CENTER == rNumFmt.GetNumAdjust();
/*N*/ 		const KSHORT nMinDist = rNumFmt.GetCharTextDistance();
/*N*/ 
/*N*/ 		if( SVX_NUM_BITMAP == rNumFmt.GetNumberingType() )
/*N*/ 		{
/*?*/ 			pRet = new SwGrfNumPortion( (SwFrm*)GetTxtFrm(),rNumFmt.GetBrush(),
/*?*/ 				rNumFmt.GetGraphicOrientation(), rNumFmt.GetGraphicSize(),
/*?*/ 				bLeft, bCenter, nMinDist );
/*?*/ 			long nTmpA = rInf.GetLast()->GetAscent();
/*?*/ 			long nTmpD = rInf.GetLast()->Height() - nTmpA;
/*?*/ 			if( !rInf.IsTest() )
                    {DBG_BF_ASSERT(0, "STRIP");} //STRIP001 /*?*/ 				((SwGrfNumPortion*)pRet)->SetBase( nTmpA, nTmpD, nTmpA, nTmpD );
/*N*/ 		}
/*N*/ 		else
/*N*/ 		{
/*N*/ 			// Der SwFont wird dynamisch angelegt und im CTOR uebergeben,
/*N*/ 			// weil das CharFmt nur einen SV-Font zurueckliefert.
/*N*/ 			// Im Dtor vom SwNumberPortion wird der SwFont deletet.
/*N*/ 			SwFont *pNumFnt = 0;
/*N*/ 			const SwAttrSet* pFmt = rNumFmt.GetCharFmt() ?
/*N*/ 				&rNumFmt.GetCharFmt()->GetAttrSet() : NULL;
/*N*/ 			if( SVX_NUM_CHAR_SPECIAL == rNumFmt.GetNumberingType() )
/*N*/ 			{
/*N*/ 				const Font *pFmtFnt = rNumFmt.GetBulletFont();
/*N*/                 pNumFnt = new SwFont( &rInf.GetCharAttr(), rInf.GetDoc() );
/*N*/ 				if( pFmt )
/*N*/                     pNumFnt->SetDiffFnt( pFmt, rInf.GetDoc() );
/*N*/ 				if ( pFmtFnt )
/*N*/ 				{
/*N*/ 					const BYTE nAct = pNumFnt->GetActual();
/*N*/ 					pNumFnt->SetFamily( pFmtFnt->GetFamily(), nAct );
/*N*/ 					pNumFnt->SetName( pFmtFnt->GetName(), nAct );
/*N*/ 					pNumFnt->SetStyleName( pFmtFnt->GetStyleName(), nAct );
/*N*/ 					pNumFnt->SetCharSet( pFmtFnt->GetCharSet(), nAct );
/*N*/ 					pNumFnt->SetPitch( pFmtFnt->GetPitch(), nAct );
/*N*/ 				}
/*N*/                 // we do not allow a vertical font
/*N*/ #ifdef VERTICAL_LAYOUT
/*N*/                 pNumFnt->SetVertical( pNumFnt->GetOrientation(),
/*N*/                                       pFrm->IsVertical() );
/*N*/ #else
/*N*/                 pNumFnt->SetVertical( 0 );
/*N*/ #endif
/*N*/ 
/*N*/ 				pRet = new SwBulletPortion( rNumFmt.GetBulletChar(), pNumFnt, bLeft,
/*N*/ 							bCenter, nMinDist );
/*N*/ 			}
/*N*/ 			else
/*N*/ 			{
/*N*/ 				XubString aTxt( pNumRule->MakeNumString( *pNum ) );
/*N*/ 
/*N*/ 				// 7974: Nicht nur eine Optimierung...
/*N*/ 				// Eine Numberportion ohne Text wird die Breite von 0
/*N*/ 				// erhalten. Die nachfolgende Textportion wird im BreakLine
/*N*/ 				// in das BreakCut laufen, obwohl rInf.GetLast()->GetFlyPortion()
/*N*/ 				// vorliegt!
/*N*/ 				if( aTxt.Len() )
/*N*/ 				{
/*N*/                     pNumFnt = new SwFont( &rInf.GetCharAttr(), rInf.GetDoc() );
/*N*/ 					if( pFmt )
/*N*/                         pNumFnt->SetDiffFnt( pFmt, rInf.GetDoc() );
/*N*/ 					// Die SSize muss erhalten bleiben
/*N*/ 					// pNumFnt->ChangeSize( rInf.GetFont()->GetSize() );
/*N*/ 
/*N*/                     // we do not allow a vertical font
/*N*/ #ifdef VERTICAL_LAYOUT
/*N*/                     pNumFnt->SetVertical( pNumFnt->GetOrientation(), pFrm->IsVertical() );
/*N*/ #else
/*N*/                     pNumFnt->SetVertical( 0 );
/*N*/ #endif
/*N*/ 
/*N*/                     pRet = new SwNumberPortion( aTxt, pNumFnt, bLeft, bCenter,
/*N*/ 												nMinDist );
/*N*/ 				}
/*N*/ 			}
/*N*/ 		}
/*N*/ 	}
/*N*/ 	return pRet;
/*N*/ }
/* -----------------26.06.2003 13:54-----------------

 --------------------------------------------------*/
void SwTxtFld::NotifyContentChange(SwFmtFld& rFmtFld)
{
    //if not in undo section notify the change
    if(pMyTxtNd && pMyTxtNd->GetNodes().IsDocNodes())
        pMyTxtNd->Modify(0, &rFmtFld);
}            


}
