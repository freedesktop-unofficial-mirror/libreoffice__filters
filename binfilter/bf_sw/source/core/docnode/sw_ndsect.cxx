/*************************************************************************
 *
 *  $RCSfile: sw_ndsect.cxx,v $
 *
 *  $Revision: 1.2 $
 *
 *  last change: $Author: mwu $ $Date: 2003-11-06 07:49:19 $
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

#ifndef _HINTIDS_HXX
#include <hintids.hxx>
#endif

#ifndef _SVXLINKMGR_HXX
#include <bf_svx/linkmgr.hxx>
#endif
#ifndef _SFXITEMITER_HXX //autogen
#include <svtools/itemiter.hxx>
#endif
#ifndef _TOOLS_RESID_HXX //autogen
#include <tools/resid.hxx>
#endif

#ifndef _FMTCNTNT_HXX //autogen
#include <fmtcntnt.hxx>
#endif
#ifndef _FMTANCHR_HXX //autogen
#include <fmtanchr.hxx>
#endif
#ifndef _TXTFTN_HXX //autogen
#include <txtftn.hxx>
#endif
#ifndef _FMTCLDS_HXX //autogen
#include <fmtclds.hxx>
#endif
#ifndef _DOC_HXX
#include <doc.hxx>
#endif
#ifndef _ROOTFRM_HXX
#include <rootfrm.hxx>
#endif
#ifndef _PAM_HXX
#include <pam.hxx>
#endif
#ifndef _NDTXT_HXX
#include <ndtxt.hxx>
#endif
#ifndef _SECTION_HXX
#include <section.hxx>
#endif
#ifndef _UNDOBJ_HXX
#include <undobj.hxx>
#endif
#ifndef _SWUNDO_HXX
#include <swundo.hxx>
#endif
#ifndef _CALC_HXX
#include <calc.hxx>
#endif
#ifndef _SWTABLE_HXX
#include <swtable.hxx>
#endif
#ifndef _SWSERV_HXX
#include <swserv.hxx>
#endif
#ifndef _FRMFMT_HXX
#include <frmfmt.hxx>
#endif
#ifndef _FTNIDX_HXX
#include <ftnidx.hxx>
#endif
#ifndef _DOCARY_HXX
#include <docary.hxx>
#endif
#ifndef _NDINDEX_HXX
#include <ndindex.hxx>
#endif
#ifndef _REDLINE_HXX
#include <redline.hxx>
#endif
#ifndef _SECTFRM_HXX
#include <sectfrm.hxx>
#endif
#ifndef _PAGEFRM_HXX
#include <pagefrm.hxx>
#endif
#ifndef _CNTFRM_HXX
#include <cntfrm.hxx>
#endif
#ifndef _NODE2LAY_HXX
#include <node2lay.hxx>
#endif
#ifndef _DOCTXM_HXX
#include <doctxm.hxx>
#endif
#ifndef _FMTFTNTX_HXX
#include <fmtftntx.hxx>
#endif
#ifndef _HINTS_HXX
#include <hints.hxx>
#endif

#ifndef _COMCORE_HRC
#include <comcore.hrc>
#endif
namespace binfilter {

/*N*/ int lcl_IsInSameTblBox( SwNodes& rNds, const SwNode& rNd,
/*N*/ 							const SwNodeIndex& rIdx2 )
/*N*/ {
/*N*/ 	const SwTableNode* pTblNd = rNd.FindTableNode();
/*N*/ 	if( !pTblNd )
/*N*/ 		return TRUE;
/*N*/ 
/*?*/ 	// dann suche den StartNode der Box
/*?*/ 	const SwTableSortBoxes& rSortBoxes = pTblNd->GetTable().GetTabSortBoxes();
/*?*/ 	ULONG nIdx = rNd.GetIndex();
/*?*/ 	for( USHORT n = 0; n < rSortBoxes.Count(); ++n )
/*?*/ 	{
/*?*/ 		const SwStartNode* pNd = rSortBoxes[ n ]->GetSttNd();
/*?*/ 		if( pNd->GetIndex() < nIdx &&
/*?*/ 			nIdx < pNd->EndOfSectionIndex() )
/*?*/ 		{
/*?*/ 			// dann muss der andere Index in derselben Section liegen
/*?*/ 			nIdx = rIdx2.GetIndex();
/*?*/ 			return pNd->GetIndex() < nIdx && nIdx < pNd->EndOfSectionIndex();
/*?*/ 		}
/*?*/ 	}
/*?*/ 	return TRUE;
/*N*/ }

//STRIP001 void lcl_CheckEmptyLayFrm( SwNodes& rNds, SwSection& rSect,
//STRIP001 						const SwNode& rStt, const SwNode& rEnd )
//STRIP001 {
//STRIP001 	SwNodeIndex aIdx( rStt );
//STRIP001 	if( !rNds.GoPrevSection( &aIdx, TRUE, FALSE ) ||
//STRIP001 		!CheckNodesRange( rStt, aIdx, TRUE ) ||
//STRIP001 		!lcl_IsInSameTblBox( rNds, rStt, aIdx ))
//STRIP001 	{
//STRIP001 		aIdx = rEnd;
//STRIP001 		if( !rNds.GoNextSection( &aIdx, TRUE, FALSE ) ||
//STRIP001 			!CheckNodesRange( rEnd, aIdx, TRUE ) ||
//STRIP001 			!lcl_IsInSameTblBox( rNds, rEnd, aIdx ))
//STRIP001 			rSect.SetHidden( FALSE );
//STRIP001 	}
//STRIP001 }

/*N*/ SwSection* SwDoc::Insert( const SwPaM& rRange, const SwSection& rNew,
/*N*/ 							const SfxItemSet* pAttr, BOOL bUpdate )
/*N*/ {
/*N*/ 	const SwNode* pPrvNd = 0;
/*N*/ 	USHORT nRegionRet = 0;
/*N*/ 	if( rRange.HasMark() &&
/*N*/ 		0 == ( nRegionRet = IsInsRegionAvailable( rRange, &pPrvNd ) ))
/*N*/ 	{
/*?*/ 		ASSERT( !this, "Selection ueber verschiedene Sections" );
/*?*/ 		return 0;
/*N*/ 	}
/*N*/ 
/*N*/ 	// Teste ob das gesamte Dokument versteckt werden soll,
/*N*/ 	// koennen wir zur Zeit nicht !!!!
/*N*/ 	if( rNew.IsHidden() && rRange.HasMark() )
/*N*/ 	{
/*?*/ 		DBG_ASSERT(0, "STRIP"); //STRIP001 const SwPosition *pStt = rRange.Start(), *pEnd = rRange.End();
//STRIP001 /*?*/ 		if( !pStt->nContent.GetIndex() &&
//STRIP001 /*?*/ 			pEnd->nNode.GetNode().GetCntntNode()->Len() ==
//STRIP001 /*?*/ 			pEnd->nContent.GetIndex() )
//STRIP001 /*?*/ 
//STRIP001 /*?*/ 			::lcl_CheckEmptyLayFrm( GetNodes(), (SwSection&)rNew,
//STRIP001 /*?*/ 									pStt->nNode.GetNode(),
//STRIP001 /*?*/ 									pEnd->nNode.GetNode() );
/*N*/ 	}
/*N*/ 
/*N*/ 	SwUndoInsSection* pUndoInsSect = 0;
/*N*/ 	if( DoesUndo() )
/*N*/ 	{
/*N*/ 		ClearRedo();
/*N*/ 		pUndoInsSect = new SwUndoInsSection( rRange, rNew, pAttr );
/*N*/ 		AppendUndo( pUndoInsSect );
/*N*/ 		DoUndo( FALSE );
/*N*/ 	}
/*N*/ 
/*N*/ 	SwSectionFmt* pFmt = MakeSectionFmt( 0 );
/*N*/ 	if( pAttr )
/*N*/ 		pFmt->SetAttr( *pAttr );
/*N*/ 
/*N*/ 	SwSectionNode* pNewSectNode = 0;
/*N*/ 
/*N*/ 	SwRedlineMode eOld = GetRedlineMode();
/*N*/ 	SetRedlineMode_intern( (eOld & ~REDLINE_SHOW_MASK) | REDLINE_IGNORE );
/*N*/ 
/*N*/ 	if( rRange.HasMark() )
/*N*/ 	{
/*N*/ 		SwPosition *pSttPos = (SwPosition*)rRange.Start(),
/*N*/ 					*pEndPos = (SwPosition*)rRange.End();
/*N*/ 		if( pPrvNd && 3 == nRegionRet )
/*N*/ 		{
/*?*/ 			ASSERT( pPrvNd, "der SectionNode fehlt" );
/*?*/ 			SwNodeIndex aStt( pSttPos->nNode ), aEnd( pEndPos->nNode, +1 );
/*?*/ 			while( pPrvNd != aStt.GetNode().FindStartNode() )
/*?*/ 				aStt--;
/*?*/ 			while( pPrvNd != aEnd.GetNode().FindStartNode() )
/*?*/ 				aEnd++;
/*?*/ 
/*?*/ 			--aEnd;		// im InsertSection ist Ende inclusive
/*?*/ 			pNewSectNode = GetNodes().InsertSection( aStt, *pFmt, rNew, &aEnd );
/*N*/ 		}
/*N*/ 		else
/*N*/ 		{
/*N*/ 			if( pUndoInsSect )
/*N*/ 			{
/*N*/ 				SwTxtNode* pTNd;
/*N*/ 				if( !( pPrvNd && 1 == nRegionRet ) &&
/*N*/ 					pSttPos->nContent.GetIndex() &&
/*N*/ 					0 != ( pTNd = pSttPos->nNode.GetNode().GetTxtNode() ))
/*?*/ 					pUndoInsSect->SaveSplitNode( pTNd, TRUE );
/*N*/ 
/*N*/ 				if( !( pPrvNd && 2 == nRegionRet ) &&
/*N*/ 					0 != ( pTNd = pEndPos->nNode.GetNode().GetTxtNode() ) &&
/*N*/ 					pTNd->GetTxt().Len() != pEndPos->nContent.GetIndex() )
/*?*/ 					pUndoInsSect->SaveSplitNode( pTNd, FALSE );
/*N*/ 			}
/*N*/ 
/*N*/ 			const SwCntntNode* pCNd;
/*N*/ 			if( pPrvNd && 1 == nRegionRet )
/*N*/ 			{
/*?*/ 				pSttPos->nNode.Assign( *pPrvNd );
/*?*/ 				pSttPos->nContent.Assign( pSttPos->nNode.GetNode().GetCntntNode(), 0 );
/*N*/ 			}
/*N*/ 			else if( pSttPos->nContent.GetIndex() )
/*?*/ 				SplitNode( *pSttPos );
/*N*/ 
/*N*/ 			if( pPrvNd && 2 == nRegionRet )
/*N*/ 			{
/*?*/ 				pEndPos->nNode.Assign( *pPrvNd );
/*?*/ 				pEndPos->nContent.Assign( pEndPos->nNode.GetNode().GetCntntNode(), 0 );
/*N*/ 			}
/*N*/ 			else
/*N*/ 			{
/*N*/ 				pCNd = pEndPos->nNode.GetNode().GetCntntNode();
/*N*/ 				if( pCNd && pCNd->Len() != pEndPos->nContent.GetIndex() )
/*N*/ 				{
/*?*/ 					xub_StrLen nCntnt = pSttPos->nContent.GetIndex();
/*?*/ 					SplitNode( *pEndPos );
/*?*/ 
/*?*/ 					SwTxtNode* pTNd;
/*?*/ 					if( pEndPos->nNode.GetIndex() == pSttPos->nNode.GetIndex() )
/*?*/ 					{
/*?*/ 						pSttPos->nNode--;
/*?*/ 						pEndPos->nNode--;
/*?*/ 						pTNd = pSttPos->nNode.GetNode().GetTxtNode();
/*?*/ 						pSttPos->nContent.Assign( pTNd, nCntnt );
/*?*/ 					}
/*?*/ 					else
/*?*/ 					{
/*?*/ 						// wieder ans Ende vom vorherigen setzen
/*?*/ 						pEndPos->nNode--;
/*?*/ 						pTNd = pEndPos->nNode.GetNode().GetTxtNode();
/*?*/ 					}
/*?*/ 					if( pTNd ) nCntnt = pTNd->GetTxt().Len(); else nCntnt = 0;
/*?*/ 					pEndPos->nContent.Assign( pTNd, nCntnt );
/*N*/ 				}
/*N*/ 			}
/*N*/ 			pNewSectNode = GetNodes().InsertSection( pSttPos->nNode, *pFmt, rNew,
/*N*/ 													&pEndPos->nNode );
/*N*/ 		}
/*N*/ 	}
/*N*/ 	else
/*N*/ 	{
/*N*/ 		const SwPosition* pPos = rRange.GetPoint();
/*N*/ 		const SwCntntNode* pCNd = pPos->nNode.GetNode().GetCntntNode();
/*N*/ 		if( !pPos->nContent.GetIndex() )
/*N*/ 		{
/*N*/ 			pNewSectNode = GetNodes().InsertSection( pPos->nNode, *pFmt, rNew, 0, TRUE );
/*N*/ 		}
/*N*/ 		else if( pPos->nContent.GetIndex() == pCNd->Len() )
/*N*/ 		{
/*?*/ 			pNewSectNode = GetNodes().InsertSection( pPos->nNode, *pFmt, rNew, 0, FALSE );
/*N*/ 		}
/*N*/ 		else
/*N*/ 		{
/*?*/ 			if( pUndoInsSect && pCNd->IsTxtNode() )
/*?*/ 				pUndoInsSect->SaveSplitNode( (SwTxtNode*)pCNd, TRUE );
/*?*/ 			SplitNode( *pPos );
/*?*/ 			pNewSectNode = GetNodes().InsertSection( pPos->nNode, *pFmt, rNew, 0, TRUE );
/*N*/ 		}
/*N*/ 	}
/*N*/ 
/*N*/ //FEATURE::CONDCOLL
/*N*/ 	pNewSectNode->CheckSectionCondColl();
/*N*/ //FEATURE::CONDCOLL
/*N*/ 
/*N*/ 	SetRedlineMode_intern( eOld );
/*N*/ 
/*N*/ 	if( IsRedlineOn() || (!IsIgnoreRedline() && pRedlineTbl->Count() ))
/*N*/ 	{
/*?*/ 		DBG_ASSERT(0, "STRIP"); //STRIP001 SwPaM aPam( *pNewSectNode->EndOfSectionNode(), *pNewSectNode, 1 );
//STRIP001 /*?*/ 		if( IsRedlineOn() )
//STRIP001 /*?*/ 			AppendRedline( new SwRedline( REDLINE_INSERT, aPam ));
//STRIP001 /*?*/ 		else
//STRIP001 /*?*/ 			SplitRedline( aPam );
/*N*/ 	}
/*N*/ 
/*N*/ 	// ist eine Condition gesetzt
/*N*/ 	if( rNew.IsHidden() && rNew.GetCondition().Len() )
/*N*/ 	{
/*?*/ 		// dann berechne bis zu dieser Position
/*?*/ 		DBG_ASSERT(0, "STRIP"); //STRIP001 SwCalc aCalc( *this );
//STRIP001 /*?*/         if( ! IsInReading() )
//STRIP001 /*?*/             FldsToCalc( aCalc, pNewSectNode->GetIndex() );
//STRIP001 /*?*/ 		SwSection& rNewSect = pNewSectNode->GetSection();
//STRIP001 /*?*/ 		rNewSect.SetCondHidden( aCalc.Calculate( rNewSect.GetCondition() ).GetBool() );
/*N*/ 	}
/*N*/ 
/*N*/ 	BOOL bUpdateFtn = FALSE;
/*N*/ 	if( GetFtnIdxs().Count() && pAttr )
/*N*/ 	{
/*?*/ 		USHORT nVal = ((SwFmtFtnAtTxtEnd&)pAttr->Get(
/*?*/ 											RES_FTN_AT_TXTEND )).GetValue();
/*?*/ 	   	if( ( FTNEND_ATTXTEND_OWNNUMSEQ == nVal ||
/*?*/ 			  FTNEND_ATTXTEND_OWNNUMANDFMT == nVal ) ||
/*?*/ 			( FTNEND_ATTXTEND_OWNNUMSEQ == ( nVal = ((SwFmtEndAtTxtEnd&)
/*?*/ 							pAttr->Get( RES_END_AT_TXTEND )).GetValue() ) ||
/*?*/ 			  FTNEND_ATTXTEND_OWNNUMANDFMT == nVal ))
/*?*/ 			bUpdateFtn = TRUE;
/*N*/ 	}
/*N*/ 
/*N*/ 	if( pUndoInsSect )
/*N*/ 	{
/*N*/ 		pUndoInsSect->SetSectNdPos( pNewSectNode->GetIndex() );
/*N*/ 		pUndoInsSect->SetUpdtFtnFlag( bUpdateFtn );
/*N*/ 		DoUndo( TRUE );
/*N*/ 	}
/*N*/ 
/*N*/ 	if( rNew.IsLinkType() )
/*?*/ 		pNewSectNode->GetSection().CreateLink( bUpdate ? CREATE_UPDATE : CREATE_CONNECT );
/*N*/ 
/*N*/ 	if( bUpdateFtn )
/*?*/ 		GetFtnIdxs().UpdateFtn( SwNodeIndex( *pNewSectNode ));
/*N*/ 
/*N*/ 	SetModified();
/*N*/ 	return &pNewSectNode->GetSection();
/*N*/ }

/*N*/ USHORT SwDoc::IsInsRegionAvailable( const SwPaM& rRange,
/*N*/ 								const SwNode** ppSttNd ) const
/*N*/ {
/*N*/ 	USHORT nRet = 1;
/*N*/ 	if( rRange.HasMark() )
/*N*/ 	{
/*N*/ 		// teste ob es sich um eine gueltige Selektion handelt
/*N*/ 		const SwPosition* pStt = rRange.Start(),
/*N*/ 						* pEnd = rRange.End();
/*N*/ 
/*N*/ 		const SwCntntNode* pCNd = pEnd->nNode.GetNode().GetCntntNode();
/*N*/ 		const SwNode* pNd = &pStt->nNode.GetNode();
/*N*/ 		const SwSectionNode* pSectNd = pNd->FindSectionNode();
/*N*/         const SwSectionNode* pEndSectNd = pCNd ? pCNd->FindSectionNode() : 0;
/*N*/ 		if( pSectNd && pEndSectNd && pSectNd != pEndSectNd )
/*N*/ 		{
/*?*/ 			// versuche eine umschliessende Section zu erzeugen
/*?*/ 			// Aber, nur wenn der Start am Sectionanfang und das Ende am
/*?*/ 			// Section Ende liegt!
/*?*/ 			nRet = 0;
/*?*/ 			if( !pStt->nContent.GetIndex() && pSectNd->GetIndex()
/*?*/ 				== pStt->nNode.GetIndex() - 1 && pEnd->nContent.GetIndex() ==
/*?*/ 				pCNd->Len() )
/*?*/ 			{
/*?*/ 				SwNodeIndex aIdx( pStt->nNode, -1 );
/*?*/ 				ULONG nCmp = pEnd->nNode.GetIndex();
/*?*/ 				const SwStartNode* pPrvNd;
/*?*/ 				const SwEndNode* pNxtNd;
/*?*/ 				while( 0 != ( pPrvNd = (pNd = &aIdx.GetNode())->GetSectionNode() ) &&
/*?*/ 					!( aIdx.GetIndex() < nCmp &&
/*?*/ 						nCmp < pPrvNd->EndOfSectionIndex() ) )
/*?*/ 				{
/*?*/ 					aIdx--;
/*?*/ 				}
/*?*/ 				if( !pPrvNd )
/*?*/ 					pPrvNd = pNd->IsStartNode() ? (SwStartNode*)pNd
/*?*/ 												: pNd->FindStartNode();
/*?*/ 
/*?*/ 				aIdx = pEnd->nNode.GetIndex() + 1;
/*?*/ 				nCmp = pStt->nNode.GetIndex();
/*?*/ 				while( 0 != ( pNxtNd = (pNd = &aIdx.GetNode())->GetEndNode() ) &&
/*?*/ 					pNxtNd->FindStartNode()->IsSectionNode() &&
/*?*/ 					!( pNxtNd->StartOfSectionIndex() < nCmp &&
/*?*/ 						nCmp < aIdx.GetIndex() ) )
/*?*/ 				{
/*?*/ 					aIdx++;
/*?*/ 				}
/*?*/ 				if( !pNxtNd )
/*?*/ 					pNxtNd = pNd->EndOfSectionNode();
/*?*/ 
/*?*/ 				if( pPrvNd && pNxtNd && pPrvNd == pNxtNd->FindStartNode() )
/*?*/ 				{
/*?*/ 					nRet = 3;
/*?*/ 
/*?*/ 					if( ppSttNd )
/*?*/ 						*ppSttNd = pPrvNd;
/*?*/ 				}
/*?*/ 			}
/*N*/ 		}
/*N*/ 		else if( !pSectNd && pEndSectNd )
/*N*/ 		{
/*?*/ 			// versuche eine umschliessende Section zu erzeugen
/*?*/ 			// Aber, nur wenn das Ende am Section Ende liegt!
/*?*/ 			nRet = 0;
/*?*/ 			if( pEnd->nContent.GetIndex() == pCNd->Len() )
/*?*/ 			{
/*?*/ 				SwNodeIndex aIdx( pEnd->nNode, 1 );
/*?*/ 				if( aIdx.GetNode().IsEndNode() &&
/*?*/ 						0 != aIdx.GetNode().FindSectionNode() )
/*?*/ 				{
/*?*/ 					do {
/*?*/ 						aIdx++;
/*?*/ 					} while( aIdx.GetNode().IsEndNode() &&
/*?*/ 								0 != aIdx.GetNode().FindSectionNode() );
/*?*/ //					if( !aIdx.GetNode().IsEndNode() )
/*?*/ 					{
/*?*/ 						nRet = 2;
/*?*/ 						if( ppSttNd )
/*?*/ 						{
/*?*/ 							aIdx--;
/*?*/ 							*ppSttNd = &aIdx.GetNode();
/*?*/ 						}
/*?*/ 					}
/*?*/ 				}
/*?*/ 			}
/*N*/ 		}
/*N*/ 		else if( pSectNd && !pEndSectNd )
/*N*/ 		{
/*?*/ 			// versuche eine umschliessende Section zu erzeugen
/*?*/ 			// Aber, nur wenn der Start am Section Anfang liegt!
/*?*/ 			nRet = 0;
/*?*/ 			if( !pStt->nContent.GetIndex() )
/*?*/ 			{
/*?*/ 				SwNodeIndex aIdx( pStt->nNode, -1 );
/*?*/ 				if( aIdx.GetNode().IsSectionNode() )
/*?*/ 				{
/*?*/ 					do {
/*?*/ 						aIdx--;
/*?*/ 					} while( aIdx.GetNode().IsSectionNode() );
/*?*/ 					if( !aIdx.GetNode().IsSectionNode() )
/*?*/ 					{
/*?*/ 						nRet = 1;
/*?*/ 						if( ppSttNd )
/*?*/ 						{
/*?*/ 							aIdx++;
/*?*/ 							*ppSttNd = &aIdx.GetNode();
/*?*/ 						}
/*?*/ 					}
/*?*/ 				}
/*?*/ 			}
/*N*/ 		}
/*N*/ 	}
/*N*/ 	return nRet;
/*N*/ }

/*N*/ SwSection* SwDoc::GetCurrSection( const SwPosition& rPos ) const
/*N*/ {
/*N*/ 	const SwSectionNode* pSectNd = rPos.nNode.GetNode().FindSectionNode();
/*N*/ 	if( pSectNd )
/*N*/ 		return (SwSection*)&pSectNd->GetSection();
/*N*/ 	return 0;
/*N*/ }

/*N*/ SwSectionFmt* SwDoc::MakeSectionFmt( SwSectionFmt *pDerivedFrom )
/*N*/ {
/*N*/ 	if( !pDerivedFrom )
/*N*/ 		pDerivedFrom = (SwSectionFmt*)pDfltFrmFmt;
/*N*/ 	SwSectionFmt* pNew = new SwSectionFmt( pDerivedFrom, this );
/*N*/ 	pSectionFmtTbl->Insert( pNew, pSectionFmtTbl->Count() );
/*N*/ 	return pNew;
/*N*/ }

/*N*/ void SwDoc::DelSectionFmt( SwSectionFmt *pFmt, BOOL bDelNodes )
/*N*/ {
/*N*/ 	USHORT nPos = pSectionFmtTbl->GetPos( pFmt );
/*N*/ 	if( USHRT_MAX != nPos )
/*N*/ 	{
/*N*/ 		const SwNodeIndex* pIdx = pFmt->GetCntnt( FALSE ).GetCntntIdx();
/*N*/ 		const SfxPoolItem* pFtnEndAtTxtEnd;
/*N*/ 		if( SFX_ITEM_SET != pFmt->GetItemState(
/*N*/ 							RES_FTN_AT_TXTEND, TRUE, &pFtnEndAtTxtEnd ) ||
/*N*/ 			SFX_ITEM_SET != pFmt->GetItemState(
/*N*/ 							RES_END_AT_TXTEND, TRUE, &pFtnEndAtTxtEnd ))
/*N*/ 			pFtnEndAtTxtEnd = 0;
/*N*/ 
/*N*/ 		const SwSectionNode* pSectNd;
/*N*/ 
/*N*/ 		if( DoesUndo() )
/*N*/ 		{
/*?*/ 			DBG_ASSERT(0, "STRIP"); //STRIP001 ClearRedo();
//STRIP001 /*?*/ 			if( bDelNodes && pIdx && &GetNodes() == &pIdx->GetNodes() &&
//STRIP001 /*?*/ 				0 != (pSectNd = pIdx->GetNode().GetSectionNode() ))
//STRIP001 /*?*/ 			{
//STRIP001 /*?*/ 				SwNodeIndex aUpdIdx( *pIdx );
//STRIP001 /*?*/ 				ClearRedo();
//STRIP001 /*?*/ 				SwPaM aPaM( *pSectNd->EndOfSectionNode(), *pSectNd );
//STRIP001 /*?*/ 				AppendUndo( new SwUndoDelete( aPaM ));
//STRIP001 /*?*/ 				if( pFtnEndAtTxtEnd )
//STRIP001 /*?*/ 					GetFtnIdxs().UpdateFtn( aUpdIdx );
//STRIP001 /*?*/ 				SetModified();
//STRIP001 /*?*/ 				return ;
//STRIP001 /*?*/ 			}
//STRIP001 /*?*/ 			AppendUndo( new SwUndoDelSection( *pFmt ) );
/*N*/ 		}
/*N*/ 		else if( bDelNodes && pIdx && &GetNodes() == &pIdx->GetNodes() &&
/*N*/ 				0 != (pSectNd = pIdx->GetNode().GetSectionNode() ))
/*N*/ 		{
/*?*/ 			SwNodeIndex aUpdIdx( *pIdx );
/*?*/ 			DeleteSection( (SwNode*)pSectNd );
/*?*/ 			if( pFtnEndAtTxtEnd )
/*?*/ 				GetFtnIdxs().UpdateFtn( aUpdIdx );
/*?*/ 			SetModified();
/*?*/ 			return ;
/*N*/ 		}
/*N*/ 
/*N*/ 		{
/*N*/ 			SwPtrMsgPoolItem aMsgHint( RES_REMOVE_UNO_OBJECT, pFmt );
/*N*/ 			pFmt->Modify( &aMsgHint, &aMsgHint );
/*N*/ 		}
/*N*/ 
/*N*/ 		// ACHTUNG: erst aus dem Array entfernen und dann loeschen.
/*N*/ 		//			Der Section-DTOR versucht selbst noch sein Format
/*N*/ 		//			zu loeschen!
/*N*/ 		pSectionFmtTbl->Remove( nPos );
/*N*/ //FEATURE::CONDCOLL
/*N*/ 		ULONG nCnt = 0, nSttNd = 0;
/*N*/ 		if( pIdx && &GetNodes() == &pIdx->GetNodes() &&
/*N*/ 			0 != (pSectNd = pIdx->GetNode().GetSectionNode() ))
/*N*/ 		{
/*?*/ 			nSttNd = pSectNd->GetIndex();
/*?*/ 			nCnt = pSectNd->EndOfSectionIndex() - nSttNd - 1;
/*N*/ 		}
/*N*/ //FEATURE::CONDCOLL
/*N*/ 
/*N*/ 		delete pFmt;
/*N*/ 
/*N*/ 		if( nSttNd && pFtnEndAtTxtEnd )
/*N*/ 		{
/*?*/ 			SwNodeIndex aUpdIdx( GetNodes(), nSttNd );
/*?*/ 			GetFtnIdxs().UpdateFtn( aUpdIdx );
/*N*/ 		}
/*N*/ 
/*N*/ //FEATURE::CONDCOLL
/*N*/ 		SwCntntNode* pCNd;
/*N*/ 		for( ; nCnt--; ++nSttNd )
/*N*/ 			if( 0 != (pCNd = GetNodes()[ nSttNd ]->GetCntntNode() ) &&
/*?*/ 				RES_CONDTXTFMTCOLL == pCNd->GetFmtColl()->Which() )
/*?*/ 				pCNd->ChkCondColl();
/*N*/ //FEATURE::CONDCOLL
/*N*/ 	}
/*N*/ 	SetModified();
/*N*/ }

/*N*/ void SwDoc::ChgSection( USHORT nPos, const SwSection& rSect,
/*N*/ 						const SfxItemSet* pAttr,
/*N*/ 						sal_Bool bPreventLinkUpdate )
/*N*/ {
/*N*/ 	SwSectionFmt* pFmt = (*pSectionFmtTbl)[ nPos ];
/*N*/ 	SwSection* pSection = pFmt->GetSection();
/*N*/     /// OD 04.10.2002 #102894#
/*N*/     /// remember hidden condition flag of SwSection before changes
/*N*/     bool bOldCondHidden = pSection->IsCondHidden() ? true : false;
/*N*/ 
/*N*/ 	if( *pSection == rSect )
/*N*/ 	{
/*N*/ 		// die Attribute ueberpruefen
/*N*/ 		BOOL bOnlyAttrChg = FALSE;
/*N*/ 		if( pAttr && pAttr->Count() )
/*N*/ 		{
/*N*/ 			SfxItemIter aIter( *pAttr );
/*N*/ 			USHORT nWhich = aIter.GetCurItem()->Which();
/*N*/ 			while( TRUE )
/*N*/ 			{
/*N*/ 				if( pFmt->GetAttr( nWhich ) != *aIter.GetCurItem() )
/*N*/ 				{
/*N*/ 					bOnlyAttrChg = TRUE;
/*N*/ 					break;
/*N*/ 				}
/*N*/ 
/*?*/ 				if( aIter.IsAtEnd() )
/*?*/ 					break;
/*?*/ 				nWhich = aIter.NextItem()->Which();
/*N*/ 			}
/*N*/ 		}
/*N*/ 
/*N*/ 		if( bOnlyAttrChg )
/*N*/ 		{
/*N*/ 			if( DoesUndo() )
/*N*/ 			{
/*N*/ 				ClearRedo();
/*N*/ 				AppendUndo( new SwUndoChgSection( *pFmt, TRUE ) );
/*N*/ 			}
/*N*/ 			pFmt->SetAttr( *pAttr );
/*N*/ 			SetModified();
/*N*/ 		}
/*N*/ 		return;
/*N*/ 	}
/*N*/ 
/*N*/ 	// Teste ob eine gesamte Content-Section (Dokument/TabellenBox/Fly)
/*N*/ 	// versteckt werden soll, koennen wir zur Zeit nicht !!!!
/*N*/ 	const SwNodeIndex* pIdx = 0;
/*N*/ 	{
/*N*/ 		const SwSectionNode* pSectNd;
/*N*/ 		if( rSect.IsHidden() && 0 != (pIdx = pFmt->GetCntnt().GetCntntIdx() )
/*N*/ 			&& 0 != (pSectNd = pIdx->GetNode().GetSectionNode() ) )
/*N*/ 		{
/*?*/ 			DBG_ASSERT(0, "STRIP"); //STRIP001 ::lcl_CheckEmptyLayFrm( GetNodes(), (SwSection&)rSect,
//STRIP001 /*?*/ 								*pSectNd, *pSectNd->EndOfSectionNode() );
/*N*/ 		}
/*N*/ 	}
/*N*/ 
/*N*/ 
/*N*/ 	if( DoesUndo() )
/*N*/ 	{
/*N*/ 		ClearRedo();
/*N*/ 		AppendUndo( new SwUndoChgSection( *pFmt, FALSE ) );
/*N*/ 	}
/*N*/ 
/*N*/ 	// #56167# Der LinkFileName koennte auch nur aus Separatoren bestehen
/*N*/     String sCompareString = ::so3::cTokenSeperator;
/*N*/     sCompareString += ::so3::cTokenSeperator;
/*N*/ 	BOOL bUpdate = ( !pSection->IsLinkType() && rSect.IsLinkType() ) ||
/*N*/ 						( rSect.GetLinkFileName().Len() &&
/*N*/ 							rSect.GetLinkFileName() != sCompareString &&
/*N*/ 							rSect.GetLinkFileName() !=
/*N*/ 							pSection->GetLinkFileName());
/*N*/ 
/*N*/ 	String sSectName( rSect.GetName() );
/*N*/ 	if( sSectName != pSection->GetName() )
/*?*/ 		GetUniqueSectionName( &sSectName );
/*N*/ 	else
/*N*/ 		sSectName.Erase();
/*N*/ 
/*N*/     /// OD 04.10.2002 #102894# - NOTE
/*N*/     /// In SwSection::operator=(..) class member bCondHiddenFlag is always set to TRUE.
/*N*/     /// IMHO this have to be changed, but I can't estimate the consequences:
/*N*/     /// Either it is set to TRUE using corresponding method <SwSection.SetCondHidden(..)>,
/*N*/     /// or it is set to the value of SwSection which is assigned to it.
/*N*/     /// Discussion with AMA results that the adjustment to the assignment operator
/*N*/     /// could be very risky -> see notes in bug #102894#.
/*N*/ 	*pSection = rSect;
/*N*/ 
/*N*/ 	if( pAttr )
/*?*/ 		pSection->GetFmt()->SetAttr( *pAttr );
/*N*/ 
/*N*/ 	if( sSectName.Len() )
/*?*/ 		pSection->SetName( sSectName );
/*N*/ 
/*N*/ 	// ist eine Condition gesetzt
/*N*/ 	if( pSection->IsHidden() && pSection->GetCondition().Len() )
/*N*/ 	{
/*?*/ 		// dann berechne bis zu dieser Position
/*?*/ 		DBG_ASSERT(0, "STRIP"); //STRIP001 SwCalc aCalc( *this );
//STRIP001 /*?*/ 		if( !pIdx )
//STRIP001 /*?*/ 			pIdx = pFmt->GetCntnt().GetCntntIdx();
//STRIP001 /*?*/ 		FldsToCalc( aCalc, pIdx->GetIndex() );
//STRIP001 /*?*/ 	        /// OD 04.10.2002 #102894#
//STRIP001         /// Because on using SwSection::operator=() to set up <pSection>
//STRIP001         /// with <rSect> and the above given note, the hidden condition flag
//STRIP001         /// has to be set to FALSE, if hidden condition flag of <pFmt->GetSection()>
//STRIP001         /// (SwSection before the changes) is FALSE (already saved in <bOldCondHidden>)
//STRIP001         /// and new calculated condition is TRUE.
//STRIP001         /// This is necessary, because otherwise the <SetCondHidden> would have
//STRIP001         /// no effect.
//STRIP001         bool bCalculatedCondHidden =
//STRIP001                 aCalc.Calculate( pSection->GetCondition() ).GetBool() ? true : false;
//STRIP001         if ( bCalculatedCondHidden && !bOldCondHidden )
//STRIP001         {
//STRIP001             pSection->SetCondHidden( false );
//STRIP001         }
//STRIP001         pSection->SetCondHidden( bCalculatedCondHidden );
/*N*/ 	}
/*N*/ 
/*N*/ 	if( bUpdate )
/*N*/ 		pSection->CreateLink( bPreventLinkUpdate ? CREATE_CONNECT : CREATE_UPDATE );
/*N*/ 	else if( !pSection->IsLinkType() && pSection->IsConnected() )
/*N*/ 	{
/*?*/ 		pSection->Disconnect();
/*?*/ 		GetLinkManager().Remove( &pSection->GetBaseLink() );
/*N*/ 	}
/*N*/ 
/*N*/ 	SetModified();
/*N*/ }

//STRIP001 void SwDoc::ChgSectionPasswd(
//STRIP001 		const ::com::sun::star::uno::Sequence <sal_Int8>& rNew,
//STRIP001         const SwSection& rSection )
//STRIP001 {
//STRIP001 	SwSectionNode* pSectNd = 0;
//STRIP001     pSectNd = rSection.GetFmt()->GetSectionNode( TRUE );
//STRIP001 
//STRIP001 	if( DoesUndo() )
//STRIP001 		ClearRedo();
//STRIP001 
//STRIP001 	if( pSectNd )
//STRIP001 		pSectNd->GetSection().SetPasswd( rNew );
//STRIP001 
//STRIP001 	SetModified();
//STRIP001 }

/* -----------------19.02.99 09:31-------------------
 * LockFrms wurde im InsertSection genutzt, um zu verhindern, dass
 * SectionFrms durch das DelFrms zerstoert werden. Dies ist durch
 * den Destroy-Listen-Mechanismus ueberfluessig geworden.
 * Falls diese Methode doch noch einmal reanimiert wird, bietet es
 * sich vielleicht an, beim Entlocken die SectionFrms auf Inhalt zu
 * pruefen und dann ggf. zur Zerstoerung anzumelden.
 * --------------------------------------------------*/

// und dann waren da noch die Fussnoten:
/*N*/ void lcl_DeleteFtn( SwSectionNode *pNd, ULONG nStt, ULONG nEnd )
/*N*/ {
/*N*/ 	SwFtnIdxs& rFtnArr = pNd->GetDoc()->GetFtnIdxs();
/*N*/ 	if( rFtnArr.Count() )
/*N*/ 	{
/*?*/ 		DBG_ASSERT(0, "STRIP"); //STRIP001 USHORT nPos;
//STRIP001 /*?*/ 		rFtnArr.SeekEntry( SwNodeIndex( *pNd ), &nPos );
//STRIP001 /*?*/ 		SwTxtFtn* pSrch;
//STRIP001 /*?*/ 
//STRIP001 /*?*/ 		// loesche erstmal alle, die dahinter stehen
//STRIP001 /*?*/ 		while( nPos < rFtnArr.Count() &&
//STRIP001 /*?*/ 			_SwTxtFtn_GetIndex( (pSrch = rFtnArr[ nPos ]) ) <= nEnd )
//STRIP001 /*?*/ 		{
//STRIP001 /*?*/ 			// Werden die Nodes nicht geloescht mussen sie bei den Seiten
//STRIP001 /*?*/ 			// abmeldet (Frms loeschen) werden, denn sonst bleiben sie
//STRIP001 /*?*/ 			// stehen (Undo loescht sie nicht!)
//STRIP001 /*?*/ 			pSrch->DelFrms();
//STRIP001 /*?*/ 			++nPos;
//STRIP001 /*?*/ 		}
//STRIP001 /*?*/ 
//STRIP001 /*?*/ 		while( nPos-- &&
//STRIP001 /*?*/ 			_SwTxtFtn_GetIndex( (pSrch = rFtnArr[ nPos ]) ) >= nStt )
//STRIP001 /*?*/ 		{
//STRIP001 /*?*/ 			// Werden die Nodes nicht geloescht mussen sie bei den Seiten
//STRIP001 /*?*/ 			// abmeldet (Frms loeschen) werden, denn sonst bleiben sie
//STRIP001 /*?*/ 			// stehen (Undo loescht sie nicht!)
//STRIP001 /*?*/ 			pSrch->DelFrms();
//STRIP001 /*?*/ 		}
/*N*/ 	}
/*N*/ }

/*N*/ inline BOOL lcl_IsTOXSection( const SwSection& rSection )
/*N*/ {
/*N*/ 	return TOX_CONTENT_SECTION == rSection.GetType() ||
/*N*/ 			TOX_HEADER_SECTION == rSection.GetType();
/*N*/ }

/*N*/ SwSectionNode* SwNodes::InsertSection( const SwNodeIndex& rNdIdx,
/*N*/ 								SwSectionFmt& rSectionFmt,
/*N*/ 								const SwSection& rSection,
/*N*/ 								const SwNodeIndex* pEnde,
/*N*/ 								BOOL bInsAtStart, BOOL bCreateFrms )
/*N*/ {
/*N*/ 	SwNodeIndex aInsPos( rNdIdx );
/*N*/ 	if( !pEnde )		// kein Bereich also neue Section davor/hinter anlegen
/*N*/ 	{
/*N*/ 		if( bInsAtStart )
/*N*/ 		{
/*?*/ 			if( !lcl_IsTOXSection( rSection ))
/*?*/ 			{
/*?*/ 				do {
/*?*/ 					aInsPos--;
/*?*/ 				} while( aInsPos.GetNode().IsSectionNode() );
/*?*/ 				aInsPos++;
/*?*/ 			}
/*N*/ 		}
/*N*/ 		else
/*N*/ 		{
/*?*/ 			SwNode* pNd;
/*?*/ 			aInsPos++;
/*?*/ 			if( !lcl_IsTOXSection( rSection ))
/*?*/ 				while( aInsPos.GetIndex() < Count() - 1 &&
/*?*/ 						( pNd = &aInsPos.GetNode())->IsEndNode() &&
/*?*/ 						pNd->FindStartNode()->IsSectionNode())
/*?*/ 					aInsPos++;
/*N*/ 		}
/*N*/ 	}
/*N*/ 
/*N*/ 	SwSectionNode* pSectNd = new SwSectionNode( aInsPos, rSectionFmt );
/*N*/ 	if( pEnde )
/*N*/ 	{
/*N*/ 		// Sonderfall fuer die Reader/Writer
/*N*/ 		if( &pEnde->GetNode() != &GetEndOfContent() )
/*N*/ 			aInsPos = pEnde->GetIndex()+1;
/*N*/ 	}
/*N*/ 	else
/*N*/ 	{
/*N*/ 		SwTxtNode* pCpyTNd = rNdIdx.GetNode().GetTxtNode();
/*N*/ 		if( pCpyTNd )
/*N*/ 		{
/*N*/ 			SwTxtNode* pTNd = new SwTxtNode( aInsPos, pCpyTNd->GetTxtColl() );
/*N*/ 			if( pCpyTNd->GetpSwAttrSet() )
/*N*/ 			{
/*?*/ 				// Task 70955 - move PageDesc/Break to the first Node of the
/*?*/ 				//				section
/*?*/ 				const SfxItemSet& rSet = *pCpyTNd->GetpSwAttrSet();
/*?*/ 				if( SFX_ITEM_SET == rSet.GetItemState( RES_BREAK ) ||
/*?*/ 					SFX_ITEM_SET == rSet.GetItemState( RES_PAGEDESC ))
/*?*/ 				{
/*?*/ 					SfxItemSet aSet( rSet );
/*?*/ 					if( bInsAtStart )
/*?*/ 						pCpyTNd->ResetAttr( RES_PAGEDESC, RES_BREAK );
/*?*/ 					else
/*?*/ 					{
/*?*/ 						aSet.ClearItem( RES_PAGEDESC );
/*?*/ 						aSet.ClearItem( RES_BREAK );
/*?*/ 					}
/*?*/ 					pTNd->SwCntntNode::SetAttr( aSet );
/*?*/ 				}
/*?*/ 				else
/*?*/ 					pTNd->SwCntntNode::SetAttr( rSet );
/*N*/ 			}
/*N*/ 			// den Frame anlegen nicht vergessen !!
/*N*/ 			pCpyTNd->MakeFrms( *pTNd );
/*N*/ 		}
/*N*/ 		else
/*?*/ 			new SwTxtNode( aInsPos, (SwTxtFmtColl*)GetDoc()->GetDfltTxtFmtColl() );
/*N*/ 	}
/*N*/ 	SwEndNode* pEndNd = new SwEndNode( aInsPos, *pSectNd );
/*N*/ 
/*N*/ 	pSectNd->GetSection() = rSection;
/*N*/ 	SwSectionFmt* pSectFmt = pSectNd->GetSection().GetFmt();
/*N*/ 
/*N*/ 	// Hier bietet sich als Optimierung an, vorhandene Frames nicht zu
/*N*/ 	// zerstoeren und wieder neu anzulegen, sondern nur umzuhaengen.
/*N*/ 	BOOL bInsFrm = bCreateFrms && !pSectNd->GetSection().IsHidden() &&
/*N*/ 				   GetDoc()->GetRootFrm();
/*N*/ 	SwNode2Layout *pNode2Layout = NULL;
/*N*/ 	if( bInsFrm )
/*N*/ 	{
/*N*/ 		SwNodeIndex aTmp( *pSectNd );
/*N*/ 		if( !pSectNd->GetNodes().FindPrvNxtFrmNode( aTmp, pSectNd->EndOfSectionNode() ) )
/*N*/ 			// dann sammel mal alle Uppers ein
/*?*/ 			pNode2Layout = new SwNode2Layout( *pSectNd );
/*N*/ 	}
/*N*/ 
/*N*/ 	// jetzt noch bei allen im Bereich den richtigen StartNode setzen
/*N*/ 	ULONG nEnde = pSectNd->EndOfSectionIndex();
/*N*/ 	ULONG nStart = pSectNd->GetIndex()+1;
/*N*/ 	ULONG nSkipIdx = ULONG_MAX;
/*N*/ 	for( ULONG n = nStart; n < nEnde; ++n )
/*N*/ 	{
/*N*/ 		SwNode* pNd = (*this)[n];
/*N*/ 
/*N*/ 		//JP 30.04.99: Bug 65644 - alle in der NodeSection liegenden
/*N*/ 		//				Sections unter die neue haengen
/*N*/ 		if( ULONG_MAX == nSkipIdx )
/*N*/ 			pNd->pStartOfSection = pSectNd;
/*N*/ 		else if( n >= nSkipIdx )
/*?*/ 			nSkipIdx = ULONG_MAX;
/*N*/ 
/*N*/ 		if( pNd->IsStartNode() )
/*N*/ 		{
/*?*/ 			// die Verschachtelung der Formate herstellen!
/*?*/ 			if( pNd->IsSectionNode() )
/*?*/ 			{
/*?*/ 				((SwSectionNode*)pNd)->GetSection().GetFmt()->
/*?*/ 									SetDerivedFrom( pSectFmt );
/*?*/ 				((SwSectionNode*)pNd)->DelFrms();
/*?*/ 				n = pNd->EndOfSectionIndex();
/*?*/ 			}
/*?*/ 			else
/*?*/ 			{
/*?*/ 				if( pNd->IsTableNode() )
/*?*/ 					((SwTableNode*)pNd)->DelFrms();
/*?*/ 
/*?*/ 				if( ULONG_MAX == nSkipIdx )
/*?*/ 					nSkipIdx = pNd->EndOfSectionIndex();
/*?*/ 			}
/*N*/ 		}
/*N*/ 		else if( pNd->IsCntntNode() )
/*N*/ 			((SwCntntNode*)pNd)->DelFrms();
/*N*/ 	}
/*N*/ 
/*N*/ 	lcl_DeleteFtn( pSectNd, nStart, nEnde );
/*N*/ 
/*N*/ 	if( bInsFrm )
/*N*/ 	{
/*N*/ 		if( pNode2Layout )
/*N*/ 		{
/*?*/ 			ULONG nIdx = pSectNd->GetIndex();
/*?*/ 			pNode2Layout->RestoreUpperFrms( pSectNd->GetNodes(), nIdx, nIdx + 1 );
/*?*/ 			delete pNode2Layout;
/*N*/ 		}
/*N*/ 		else
/*N*/ 			pSectNd->MakeFrms( &aInsPos );
/*N*/ 	}
/*N*/ 
/*N*/ 	return pSectNd;
/*N*/ }

/*N*/ SwSectionNode* SwNode::FindSectionNode()
/*N*/ {
/*N*/ 	if( IsSectionNode() )
/*N*/ 		return GetSectionNode();
/*N*/ 	SwStartNode* pTmp = pStartOfSection;
/*N*/ 	while( !pTmp->IsSectionNode() && pTmp->GetIndex() )
/*N*/ #if defined( ALPHA ) && defined( UNX )
/*?*/ 		pTmp = ((SwNode*)pTmp)->pStartOfSection;
/*N*/ #else
/*N*/ 		pTmp = pTmp->pStartOfSection;
/*N*/ #endif
/*N*/ 	return pTmp->GetSectionNode();
/*N*/ }


//---------
// SwSectionNode
//---------

/*N*/ SwSectionNode::SwSectionNode( const SwNodeIndex& rIdx, SwSectionFmt& rFmt )
/*N*/ 	: SwStartNode( rIdx, ND_SECTIONNODE )
/*N*/ {
/*N*/ 	SwSectionNode* pParent = FindStartNode()->FindSectionNode();
/*N*/ 	if( pParent )
/*N*/ 	{
/*N*/ 		// das Format beim richtigen Parent anmelden.
/*N*/ 		rFmt.SetDerivedFrom( pParent->GetSection().GetFmt() );
/*N*/ 	}
/*N*/ 	pSection = new SwSection( CONTENT_SECTION, rFmt.GetName(), &rFmt );
/*N*/ 
/*N*/ 	// jetzt noch die Verbindung von Format zum Node setzen
/*N*/ 	// Modify unterdruecken, interresiert keinen
/*N*/ 	rFmt.LockModify();
/*N*/ 	rFmt.SetAttr( SwFmtCntnt( this ) );
/*N*/ 	rFmt.UnlockModify();
/*N*/ }

//Hier werden ueberfluessige SectionFrms entfernt
//STRIP001 SwFrm* SwClearDummies( SwFrm* pFrm )
//STRIP001 {
//STRIP001 	SwFrm* pTmp = pFrm;
//STRIP001 	while( pTmp )
//STRIP001 	{
//STRIP001 		ASSERT( !pTmp->GetUpper(), "SwClearDummies: No Upper allowed!" );
//STRIP001 		if( pTmp->IsSctFrm() )
//STRIP001 		{
//STRIP001 			SwSectionFrm* pSectFrm = (SwSectionFrm*)pFrm;
//STRIP001 			pTmp = pTmp->GetNext();
//STRIP001 			if( !pSectFrm->GetLower() )
//STRIP001 			{
//STRIP001 				if( pSectFrm->GetPrev() )
//STRIP001 					pSectFrm->GetPrev()->pNext = pTmp;
//STRIP001 				else
//STRIP001 					pFrm = pTmp;
//STRIP001 				if( pTmp )
//STRIP001 					pTmp->pPrev = pSectFrm->GetPrev();
//STRIP001 				delete pSectFrm;
//STRIP001 			}
//STRIP001 		}
//STRIP001 		else
//STRIP001 			pTmp = pTmp->GetNext();
//STRIP001 	}
//STRIP001 	return pFrm;
//STRIP001 }

/*N*/ SwSectionNode::~SwSectionNode()
/*N*/ {
/*N*/ 	{
/*N*/ 		SwClientIter aIter( *(pSection->GetFmt()) );
/*N*/ 		SwClient *pLast = aIter.GoStart();
/*N*/ 		while ( pLast )
/*N*/ 		{
/*N*/ 			if ( pLast->IsA( TYPE(SwFrm) ) )
/*N*/ 			{
/*?*/ 				SwSectionFrm *pSectFrm = (SwSectionFrm*)pLast;
/*?*/ 				SwSectionFrm::MoveCntntAndDelete( pSectFrm, TRUE );
/*?*/ 				pLast = aIter.GoStart();
/*N*/ 			}
/*N*/ 			else
/*N*/ 				pLast = aIter++;
/*N*/ 		}
/*N*/ 	}
/*N*/ 	SwDoc* pDoc = GetDoc();
/*N*/ 
/*N*/ 	SwSectionFmt* pFmt = pSection->GetFmt();
/*N*/ 	if( pFmt )
/*N*/ 	{
/*N*/ 		// das Attribut entfernen, weil die Section ihr Format loescht
/*N*/ 		// und falls das Cntnt-Attribut vorhanden ist, die Section aufhebt.
/*N*/ 		pFmt->LockModify();
/*N*/ 		pFmt->ResetAttr( RES_CNTNT );
/*N*/ 		pFmt->UnlockModify();
/*N*/ 	}
/*N*/ 
/*N*/ 	BOOL bUndo = pDoc->DoesUndo();
/*N*/ 	// verhinder beim Loeschen aus der Undo/Redo-History einen rekursiven Aufruf
/*N*/ 	if( bUndo && &pDoc->GetNodes() != &GetNodes() )
/*?*/ 		pDoc->DoUndo( FALSE );
/*N*/ 	DELETEZ( pSection );
/*N*/ 	pDoc->DoUndo( bUndo );
/*N*/ }

// setze ein neues SectionObject. Erstmal nur gedacht fuer die
// neuen VerzeichnisSections. Der geht ueber in den Besitz des Nodes!
/*N*/ void SwSectionNode::SetNewSection( SwSection* pNewSection )
/*N*/ {
/*N*/ 	ASSERT( pNewSection, "ohne Pointer geht hier nichts" );
/*N*/ 	if( pNewSection )
/*N*/ 	{
/*N*/ 		SwNode2Layout aN2L( *this );
/*N*/ 
/*N*/ 		// einige Flags sollten ueber nommen werden!
/*N*/ 		pNewSection->bProtectFlag = pSection->bProtectFlag;
/*N*/ 		pNewSection->bHiddenFlag = pSection->bHiddenFlag;
/*N*/ 		pNewSection->bHidden = pSection->bHidden;
/*N*/ 		pNewSection->bCondHiddenFlag = pSection->bCondHiddenFlag;
/*N*/ 
/*N*/ 		// The section frame contains a pointer to the section. That for,
/*N*/ 		// the frame must be destroyed before deleting the section.
/*N*/ 		DelFrms();
/*N*/ 
/*N*/ 		delete pSection;
/*N*/ 		pSection = pNewSection;
/*N*/ 
/*N*/ 		ULONG nIdx = GetIndex();
/*N*/ 		aN2L.RestoreUpperFrms( GetNodes(), nIdx, nIdx + 1 );
/*N*/ 	}
/*N*/ }

/*N*/ SwFrm *SwSectionNode::MakeFrm()
/*N*/ {
/*N*/ 	pSection->bHiddenFlag = FALSE;
/*N*/ 	return new SwSectionFrm( *pSection );
/*N*/ }

//Methode erzeugt fuer den vorhergehenden Node alle Ansichten vom
//Dokument. Die erzeugten Contentframes werden in das entsprechende
//Layout gehaengt.
//STRIP001 void SwSectionNode::MakeFrms(const SwNodeIndex & rIdx )
//STRIP001 {
//STRIP001 	// also nehme meinen nachfolgenden oder vorhergehenden ContentFrame:
//STRIP001 	SwNodes& rNds = GetNodes();
//STRIP001 	if( rNds.IsDocNodes() && rNds.GetDoc()->GetRootFrm() )
//STRIP001 	{
//STRIP001 		if( GetSection().IsHidden() || IsCntntHidden() )
//STRIP001 		{
//STRIP001 			SwNodeIndex aIdx( *EndOfSectionNode() );
//STRIP001 			SwCntntNode* pCNd = rNds.GoNextSection( &aIdx, TRUE, FALSE );
//STRIP001 			if( !pCNd )
//STRIP001 			{
//STRIP001 				aIdx = *this;
//STRIP001 				if( 0 == ( pCNd = rNds.GoPrevSection( &aIdx, TRUE, FALSE )) )
//STRIP001 					return ;
//STRIP001 			}
//STRIP001 			pCNd = rNds[ aIdx ]->GetCntntNode();
//STRIP001 			pCNd->MakeFrms( (SwCntntNode&)rIdx.GetNode() );
//STRIP001 		}
//STRIP001 		else
//STRIP001 		{
//STRIP001 			SwNode2Layout aNode2Layout( *this, rIdx.GetIndex() );
//STRIP001 			SwFrm *pFrm, *pNew;
//STRIP001 			while( 0 != (pFrm = aNode2Layout.NextFrm()) )
//STRIP001 			{
//STRIP001 				ASSERT( pFrm->IsSctFrm(), "Depend von Section keine Section." );
//STRIP001 				pNew = rIdx.GetNode().GetCntntNode()->MakeFrm();
//STRIP001 
//STRIP001 				SwSectionNode *pS = rIdx.GetNode().FindSectionNode();
//STRIP001 				// if the node is in a section, the sectionframe now
//STRIP001 				// has to be created..
//STRIP001                 // OD 14.11.2002 #104684# - boolean to control <Init()> of a new
//STRIP001                 // section frame.
//STRIP001                 bool bInitNewSect = false;
//STRIP001 				if( pS )
//STRIP001 				{
//STRIP001 					SwSectionFrm *pSct = new SwSectionFrm( pS->GetSection() );
//STRIP001                     // OD 14.11.2002 #104684# - prepare <Init()> of new section frame.
//STRIP001                     bInitNewSect = true;
//STRIP001 					SwLayoutFrm* pUp = pSct;
//STRIP001 					while( pUp->Lower() )  // for columned sections
//STRIP001 					{
//STRIP001 						ASSERT( pUp->Lower()->IsLayoutFrm(),"Who's in there?" );
//STRIP001 						pUp = (SwLayoutFrm*)pUp->Lower();
//STRIP001 					}
//STRIP001 					pNew->Paste( pUp, NULL );
//STRIP001 					pNew = pSct;
//STRIP001 				}
//STRIP001 
//STRIP001 				// wird ein Node vorher oder nachher mit Frames versehen
//STRIP001 				if ( rIdx < GetIndex() )
//STRIP001 					// der neue liegt vor mir
//STRIP001 					pNew->Paste( pFrm->GetUpper(), pFrm );
//STRIP001 				else
//STRIP001 					// der neue liegt hinter mir
//STRIP001 					pNew->Paste( pFrm->GetUpper(), pFrm->GetNext() );
//STRIP001                 if ( bInitNewSect )
//STRIP001                     static_cast<SwSectionFrm*>(pNew)->Init();
//STRIP001 			}
//STRIP001 		}
//STRIP001 	}
//STRIP001 }

//Fuer jedes vorkommen im Layout einen SectionFrm anlegen und vor den
//entsprechenden CntntFrm pasten.

/*N*/ void SwSectionNode::MakeFrms( SwNodeIndex* pIdxBehind, SwNodeIndex* pEndIdx )
/*N*/ {
/*N*/ 	ASSERT( pIdxBehind, "kein Index" );
/*N*/ 	SwNodes& rNds = GetNodes();
/*N*/ 	SwDoc* pDoc = rNds.GetDoc();
/*N*/ 
/*N*/ 	*pIdxBehind = *this;
/*N*/ 
/*N*/ 	pSection->bHiddenFlag = TRUE;
/*N*/ 
/*N*/ 	if( rNds.IsDocNodes() )
/*N*/ 	{
/*N*/ 		SwNodeIndex *pEnd = pEndIdx ? pEndIdx :
/*N*/ 							new SwNodeIndex( *EndOfSectionNode(), 1 );
/*N*/ 		::binfilter::MakeFrms( pDoc, *pIdxBehind, *pEnd );
/*N*/ 		if( !pEndIdx )
/*N*/ 			delete pEnd;
/*N*/ 	}
/*N*/ 
/*N*/ }

/*N*/ void SwSectionNode::DelFrms()
/*N*/ {
/*N*/ 	ULONG nStt = GetIndex()+1, nEnd = EndOfSectionIndex();
/*N*/ 	if( nStt >= nEnd )
/*N*/ 	{
/*?*/ 		// unser Flag muessen wir noch aktualisieren
/*?*/ 		// pSection->bHiddenFlag = TRUE;
/*?*/ 		return ;
/*N*/ 	}
/*N*/ 
/*N*/ 	SwNodes& rNds = GetNodes();
/*N*/ 	pSection->GetFmt()->DelFrms();
/*N*/ 
/*N*/ 	// unser Flag muessen wir noch aktualisieren
/*N*/ 	pSection->bHiddenFlag = TRUE;
/*N*/ 
/*N*/ 	// Bug 30582: falls der Bereich in Fly oder TabellenBox ist, dann
/*N*/ 	//				kann er nur "gehiddet" werden, wenn weiterer Content
/*N*/ 	//				vorhanden ist, der "Frames" haelt. Sonst hat der
/*N*/ 	//				Fly/TblBox-Frame keinen Lower !!!
/*N*/ 	{
/*N*/ 		SwNodeIndex aIdx( *this );
/*N*/ 		if( !rNds.GoPrevSection( &aIdx, TRUE, FALSE ) ||
/*N*/ 			!CheckNodesRange( *this, aIdx, TRUE ) ||
/*N*/ 			!lcl_IsInSameTblBox( rNds, *this, aIdx ))
/*N*/ 		{
/*N*/ 			aIdx = *EndOfSectionNode();
/*N*/ 			if( !rNds.GoNextSection( &aIdx, TRUE, FALSE ) ||
/*N*/ 				!CheckNodesRange( *EndOfSectionNode(), aIdx, TRUE ) ||
/*N*/ 				!lcl_IsInSameTblBox( rNds, *EndOfSectionNode(), aIdx ))
/*?*/ 				pSection->bHiddenFlag = FALSE;
/*N*/ 		}
/*N*/ 	}
/*N*/ }

//STRIP001 SwSectionNode* SwSectionNode::MakeCopy( SwDoc* pDoc, const SwNodeIndex& rIdx ) const
//STRIP001 {
//STRIP001 	// in welchen Array steht ich denn: Nodes, UndoNodes ??
//STRIP001 	const SwNodes& rNds = GetNodes();
//STRIP001 
//STRIP001 	// das SectionFrmFmt kopieren
//STRIP001 	SwSectionFmt* pSectFmt = pDoc->MakeSectionFmt( 0 );
//STRIP001 	pSectFmt->CopyAttrs( *GetSection().GetFmt() );
//STRIP001 
//STRIP001 	SwSectionNode* pSectNd = new SwSectionNode( rIdx, *pSectFmt );
//STRIP001 	SwEndNode* pEndNd = new SwEndNode( rIdx, *pSectNd );
//STRIP001 	SwNodeIndex aInsPos( *pEndNd );
//STRIP001 
//STRIP001 	// Werte uebertragen
//STRIP001 	SwSection* pNewSect = pSectNd->pSection;
//STRIP001 
//STRIP001 	switch( GetSection().GetType() )
//STRIP001 	{
//STRIP001 	case TOX_CONTENT_SECTION:
//STRIP001 		{
//STRIP001 			ASSERT( GetSection().ISA( SwTOXBaseSection ), "keine TOXBaseSection!" );
//STRIP001 			SwTOXBaseSection& rTOXSect = (SwTOXBaseSection&)GetSection();
//STRIP001 			SwTOXBase aTmp( rTOXSect, pDoc );
//STRIP001 
//STRIP001 			SwTOXBaseSection* pNew = new SwTOXBaseSection( aTmp );
//STRIP001 
//STRIP001 			pNewSect = pNew;
//STRIP001 			pSectFmt->Add( pNewSect );
//STRIP001 			pSectNd->SetNewSection( pNew );
//STRIP001 		}
//STRIP001 		break;
//STRIP001 
//STRIP001 	default:
//STRIP001 		// beim Move den Namen beibehalten
//STRIP001 		if( rNds.GetDoc() == pDoc && pDoc->IsCopyIsMove() )
//STRIP001 			pNewSect->SetName( GetSection().GetName() );
//STRIP001 		else
//STRIP001 			pNewSect->SetName( pDoc->GetUniqueSectionName(
//STRIP001 										&GetSection().GetName() ) );
//STRIP001 		break;
//STRIP001 	}
//STRIP001 
//STRIP001 
//STRIP001 	pNewSect->SetType( GetSection().GetType() );
//STRIP001 	pNewSect->SetCondition( GetSection().GetCondition() );
//STRIP001 	pNewSect->SetLinkFileName( GetSection().GetLinkFileName() );
//STRIP001 	if( !pNewSect->IsHiddenFlag() && GetSection().IsHidden() )
//STRIP001 		pNewSect->SetHidden( TRUE );
//STRIP001 	if( !pNewSect->IsProtectFlag() && GetSection().IsProtect() )
//STRIP001 		pNewSect->SetProtect( TRUE );
//STRIP001 
//STRIP001 	SwNodeRange aRg( *this, +1, *EndOfSectionNode() );	// (wo stehe in denn nun ??)
//STRIP001 	rNds._Copy( aRg, aInsPos, FALSE );
//STRIP001 
//STRIP001 	// loesche alle Frames vom kopierten Bereich, diese werden beim
//STRIP001 	// erzeugen des SectionFrames angelegt !
//STRIP001 	pSectNd->DelFrms();
//STRIP001 
//STRIP001 	// dann kopiere auch noch die Links/Server
//STRIP001 	if( pNewSect->IsLinkType() )		// den Link eintragen
//STRIP001 		pNewSect->CreateLink( pDoc->GetRootFrm() ? CREATE_CONNECT
//STRIP001 												 : CREATE_NONE );
//STRIP001 
//STRIP001 	// falls als Server aus dem Undo kopiert wird, wieder eintragen
//STRIP001 	if( pSection->IsServer() && pDoc->GetUndoNds() == &rNds )
//STRIP001 	{
//STRIP001 		pNewSect->SetRefObject( pSection->GetObject() );
//STRIP001 		pDoc->GetLinkManager().InsertServer( pNewSect->GetObject() );
//STRIP001 	}
//STRIP001 
//STRIP001 	return pSectNd;
//STRIP001 }

//STRIP001 BOOL SwSectionNode::IsCntntHidden() const
//STRIP001 {
//STRIP001 	ASSERT( !pSection->IsHidden(), "That's simple: Hidden Section => Hidden Content" );
//STRIP001 	SwNodeIndex aTmp( *this, 1 );
//STRIP001 	ULONG nEnd = EndOfSectionIndex();
//STRIP001 	while( aTmp < nEnd )
//STRIP001 	{
//STRIP001 		if( aTmp.GetNode().IsSectionNode() )
//STRIP001 		{
//STRIP001 			const SwSection& rSect = ((SwSectionNode&)aTmp.GetNode()).GetSection();
//STRIP001 			if( rSect.IsHiddenFlag() )
//STRIP001 				// dann diese Section ueberspringen
//STRIP001 				aTmp = *aTmp.GetNode().EndOfSectionNode();
//STRIP001 		}
//STRIP001 		else
//STRIP001 		{
//STRIP001 			if( aTmp.GetNode().IsCntntNode() || aTmp.GetNode().IsTableNode() )
//STRIP001 				return FALSE; // Nicht versteckter Inhalt wurde gefunden
//STRIP001 			ASSERT( aTmp.GetNode().IsEndNode(), "EndNode expected" );
//STRIP001 		}
//STRIP001 		aTmp++;
//STRIP001 	}
//STRIP001 	return TRUE; // Alles versteckt
//STRIP001 }


//STRIP001 void SwSectionNode::NodesArrChgd()
//STRIP001 {
//STRIP001 	SwSectionFmt* pFmt = pSection->GetFmt();
//STRIP001 	if( pFmt )
//STRIP001 	{
//STRIP001 		SwNodes& rNds = GetNodes();
//STRIP001 		SwDoc* pDoc = pFmt->GetDoc();
//STRIP001 
//STRIP001 		if( !rNds.IsDocNodes() )
//STRIP001 		{
//STRIP001 			SwPtrMsgPoolItem aMsgHint( RES_REMOVE_UNO_OBJECT, pFmt );
//STRIP001 			pFmt->Modify( &aMsgHint, &aMsgHint );
//STRIP001 		}
//STRIP001 
//STRIP001 		pFmt->LockModify();
//STRIP001 		pFmt->SetAttr( SwFmtCntnt( this ));
//STRIP001 		pFmt->UnlockModify();
//STRIP001 
//STRIP001 		SwSectionNode* pSectNd = FindStartNode()->FindSectionNode();
//STRIP001 		// set the correct parent from the new section
//STRIP001 		pFmt->SetDerivedFrom( pSectNd ? pSectNd->GetSection().GetFmt()
//STRIP001 									  : pDoc->GetDfltFrmFmt() );
//STRIP001 
//STRIP001 		// jetzt noch bei allen im Bereich den richtigen StartNode setzen
//STRIP001 		ULONG nStart = GetIndex()+1, nEnde = EndOfSectionIndex();
//STRIP001 		for( ULONG n = nStart; n < nEnde; ++n )
//STRIP001 			// die Verschachtelung der Formate herstellen!
//STRIP001 			if( 0 != ( pSectNd = rNds[ n ]->GetSectionNode() ) )
//STRIP001 			{
//STRIP001 				pSectNd->GetSection().GetFmt()->SetDerivedFrom( pFmt );
//STRIP001 				n = pSectNd->EndOfSectionIndex();
//STRIP001 			}
//STRIP001 
//STRIP001 		// verschieben vom Nodes- ins UndoNodes-Array?
//STRIP001 		if( rNds.IsDocNodes() )
//STRIP001 		{
//STRIP001 			ASSERT( pDoc == GetDoc(),
//STRIP001 					"verschieben in unterschiedliche Documente?" );
//STRIP001 			if( pSection->IsLinkType() )		// den Link austragen
//STRIP001 				pSection->CreateLink( pDoc->GetRootFrm() ? CREATE_CONNECT
//STRIP001 														 : CREATE_NONE );
//STRIP001 
//STRIP001 			if( pSection->IsServer() )					// als Server austragen
//STRIP001 				pDoc->GetLinkManager().InsertServer( pSection->GetObject() );
//STRIP001 		}
//STRIP001 		else
//STRIP001 		{
//STRIP001 			if( CONTENT_SECTION != pSection->GetType() )		// den Link austragen
//STRIP001 				pDoc->GetLinkManager().Remove( &pSection->GetBaseLink() );
//STRIP001 
//STRIP001 			if( pSection->IsServer() )					// als Server austragen
//STRIP001 				pDoc->GetLinkManager().RemoveServer( pSection->GetObject() );
//STRIP001 		}
//STRIP001 	}
//STRIP001 }


/*N*/ String SwDoc::GetUniqueSectionName( const String* pChkStr ) const
/*N*/ {
/*N*/ 	ResId aId( STR_REGION_DEFNAME, pSwResMgr );
/*N*/ 	String aName( aId );
/*N*/ 	xub_StrLen nNmLen = aName.Len();
/*N*/ 
/*N*/ 	USHORT nNum, nTmp, nFlagSize = ( pSectionFmtTbl->Count() / 8 ) +2;
/*N*/ 	BYTE* pSetFlags = new BYTE[ nFlagSize ];
/*N*/ 	memset( pSetFlags, 0, nFlagSize );
/*N*/ 
/*N*/ 	const SwSectionNode* pSectNd;
/*N*/ 	for( USHORT n = 0; n < pSectionFmtTbl->Count(); ++n )
/*N*/ 		if( 0 != ( pSectNd = (*pSectionFmtTbl)[ n ]->GetSectionNode( FALSE ) ))
/*N*/ 		{
/*N*/ 			const String& rNm = pSectNd->GetSection().GetName();
/*N*/ 			if( rNm.Match( aName ) == nNmLen )
/*N*/ 			{
/*?*/ 				// Nummer bestimmen und das Flag setzen
/*?*/ 				nNum = rNm.Copy( nNmLen ).ToInt32();
/*?*/ 				if( nNum-- && nNum < pSectionFmtTbl->Count() )
/*?*/ 					pSetFlags[ nNum / 8 ] |= (0x01 << ( nNum & 0x07 ));
/*N*/ 			}
/*N*/ 			if( pChkStr && pChkStr->Equals( rNm ) )
/*?*/ 				pChkStr = 0;
/*N*/ 		}
/*N*/ 
/*N*/ 	if( !pChkStr )
/*N*/ 	{
/*?*/ 		// alle Nummern entsprechend geflag, also bestimme die richtige Nummer
/*?*/ 		nNum = pSectionFmtTbl->Count();
/*?*/ 		for( n = 0; n < nFlagSize; ++n )
/*?*/ 			if( 0xff != ( nTmp = pSetFlags[ n ] ))
/*?*/ 			{
/*?*/ 				// also die Nummer bestimmen
/*?*/ 				nNum = n * 8;
/*?*/ 				while( nTmp & 1 )
/*?*/ 					++nNum, nTmp >>= 1;
/*?*/ 				break;
/*?*/ 			}
/*?*/ 
/*N*/ 	}
/*N*/ 	__DELETE( nFlagSize ) pSetFlags;
/*N*/ 	if( pChkStr )
/*N*/ 		return *pChkStr;
/*?*/ 	return aName += String::CreateFromInt32( ++nNum );
/*N*/ }


}
