/*************************************************************************
 *
 *  $RCSfile: sw_docbm.cxx,v $
 *
 *  $Revision: 1.6 $
 *
 *  last change: $Author: hr $ $Date: 2004-08-04 14:18:06 $
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

// auto strip #include <tools/pstm.hxx>
// auto strip #ifndef _SVXLINKMGR_HXX
// auto strip #include <bf_svx/linkmgr.hxx>
// auto strip #endif

#ifndef _FMTANCHR_HXX //autogen
#include <fmtanchr.hxx>
#endif
#ifndef _FRMFMT_HXX //autogen
#include <frmfmt.hxx>
#endif

#ifndef _ERRHDL_HXX
#include <errhdl.hxx>
#endif

// auto strip #ifndef _NODE_HXX //autogen
// auto strip #include <node.hxx>
// auto strip #endif

#ifndef _HORIORNT_HXX
#include <horiornt.hxx>
#endif

#ifndef _DOC_HXX
#include <doc.hxx>
#endif
#ifndef _ERRHDL_HXX
#include <errhdl.hxx>
#endif
#ifndef _CNTFRM_HXX
#include <cntfrm.hxx>
#endif
#ifndef _DCONTACT_HXX
#include <dcontact.hxx>
#endif
#ifndef _BOOKMRK_HXX
#include <bookmrk.hxx>
#endif
#ifndef _UNDOBJ_HXX
#include <undobj.hxx>
#endif
// auto strip #ifndef _PAM_HXX
// auto strip #include <pam.hxx>
// auto strip #endif
#ifndef _MVSAVE_HXX
#include <mvsave.hxx>
#endif
// auto strip #ifndef _SWSERV_HXX
// auto strip #include <swserv.hxx>
// auto strip #endif
#ifndef _REDLINE_HXX
#include <redline.hxx>
#endif
#ifndef _DOCARY_HXX
#include <docary.hxx>
#endif
#ifndef _VISCRS_HXX
#include <viscrs.hxx>
#endif
#ifndef _EDITSH_HXX
#include <editsh.hxx>
#endif
#ifndef _UNOCRSR_HXX
#include <unocrsr.hxx>
#endif
#ifndef _VISCRS_HXX
#include <viscrs.hxx>
#endif
namespace binfilter {


/*N*/ SV_IMPL_OP_PTRARR_SORT(SwBookmarks, SwBookmarkPtr)

#define PCURCRSR (_pCurrCrsr)
#define FOREACHPAM_START(pSttCrsr) \
    {\
        SwPaM *_pStartCrsr = pSttCrsr, *_pCurrCrsr = pSttCrsr; \
        do {

#define FOREACHPAM_END() \
        } while( (_pCurrCrsr=(SwPaM *)_pCurrCrsr->GetNext()) != _pStartCrsr ); \
    }
#define PCURSH ((SwCrsrShell*)_pStartShell)
#define FOREACHSHELL_START( pEShell ) \
    {\
        register ViewShell *_pStartShell = pEShell; \
        do { \
            if( _pStartShell->IsA( TYPE( SwCrsrShell )) ) \
            {

#define FOREACHSHELL_END( pEShell ) \
            } \
        } while((_pStartShell=(ViewShell*)_pStartShell->GetNext())!= pEShell ); \
    }


/*N*/ SwBookmark* SwDoc::MakeBookmark( const SwPaM& rPaM, const KeyCode& rCode,
/*N*/ 								const String& rName, const String& rShortName,
/*N*/ 								BOOKMARK_TYPE eMark )
/*N*/ {
/*N*/ 	SwBookmark *pBM;
/*N*/ 	if( MARK == eMark )
/*?*/ 	 {DBG_BF_ASSERT(0, "STRIP");} //STRIP001 	pBM = new SwMark( *rPaM.GetPoint(), rCode, rName, rShortName );
/*N*/ 	else if( BOOKMARK == eMark )
/*N*/ 	{
/*N*/ 		pBM = new SwBookmark(*rPaM.GetPoint(), rCode, rName, rShortName);
/*N*/ 		if( rPaM.HasMark() )
/*?*/ 			pBM->pPos2 = new SwPosition( *rPaM.GetMark() );
/*N*/ 	}
/*N*/ 	else
/*N*/ 	{
/*N*/ 		pBM = new SwUNOMark(*rPaM.GetPoint(), rCode, rName, rShortName);
/*N*/ 		if( rPaM.HasMark() )
/*N*/ 			pBM->pPos2 = new SwPosition( *rPaM.GetMark() );
/*N*/ 	}
/*N*/ 
/*N*/ 	if( !pBookmarkTbl->Insert( pBM ) )
/*?*/ 		delete pBM, pBM = 0;
/*N*/ 	else
/*N*/ 	{
/*N*/ 		if( BOOKMARK == eMark && DoesUndo() )
/*N*/ 		{
/*N*/ 			ClearRedo();
/*N*/ 			AppendUndo( new SwUndoInsBookmark( *pBM ));
/*N*/ 		}
/*N*/ 		if(UNO_BOOKMARK != eMark)
/*N*/ 			SetModified();
/*N*/ 	}
/*N*/ 	return pBM;
/*N*/ }

/*N*/ void SwDoc::DelBookmark(USHORT nPos)
/*N*/ {
/*N*/ 	SwBookmark *pBM = (*pBookmarkTbl)[nPos];
/*N*/ 	if( DoesUndo() && !pBM->IsUNOMark())
/*N*/ 	{
/*?*/ 	DBG_BF_ASSERT(0, "STRIP"); //STRIP001 	ClearRedo();
//STRIP001 /*?*/ 		AppendUndo( new SwUndoDelBookmark( *pBM ));
/*N*/ 	}
/*N*/ 
/*N*/     // #108964# UNO bookmark don't contribute to the document state,
/*N*/     // and hence changing them shouldn't set the document modified
/*N*/     if( !pBM->IsUNOMark() )
/*N*/ 		SetModified();
/*N*/ 
/*N*/ 	pBookmarkTbl->Remove(nPos);
/*N*/ 
/*N*/ 	SwServerObject* pServObj = pBM->GetObject();
/*N*/ 	if( pServObj )			// dann aus der Liste entfernen
/*?*/ 	{DBG_BF_ASSERT(0, "STRIP");} //STRIP001 	GetLinkManager().RemoveServer( pServObj );
/*N*/ 
/*N*/ 	delete pBM;
/*N*/ }

/*N*/ void SwDoc::DelBookmark( const String& rName )
/*N*/ {
/*N*/ 	USHORT nFnd = FindBookmark( rName );
/*N*/ 	if( USHRT_MAX != nFnd )
/*N*/ 		DelBookmark( nFnd );
/*N*/ }

/*N*/ USHORT SwDoc::FindBookmark( const String& rName )
/*N*/ {
/*N*/ 	ASSERT( rName.Len(), "wo ist der Name?" );
/*N*/ 	for( USHORT n = pBookmarkTbl->Count(); n ; )
/*N*/ 		if( rName.Equals( (*pBookmarkTbl)[ --n ]->GetName() ) )
/*N*/ 			return n;
/*N*/ 	return USHRT_MAX;
/*N*/ }

// Zur Vereinfachung gibt es auch den direkten Zugriff
// auf die "echten" Bookmarks

/*N*/USHORT SwDoc::GetBookmarkCnt(BOOL bBkmrk) const
/*N*/{
/*?*/	USHORT nRet = pBookmarkTbl->Count();
/*?*/	if(bBkmrk)
/*?*/	{
/*?*/		for( USHORT i = nRet; i; --i )
/*?*/		{
/*?*/			if(!(*pBookmarkTbl)[i - 1]->IsBookMark())
/*?*/				nRet--;
/*?*/		}
/*?*/	}
/*?*/	return nRet;
/*N*/}


/*N*/SwBookmark& SwDoc::GetBookmark(USHORT nPos, BOOL bBkmrk)
/*N*/{
/*?*/	if( bBkmrk )
/*?*/	{
/*?*/		USHORT nCount = pBookmarkTbl->Count();
/*?*/		USHORT i = 0;
/*?*/		do {
/*?*/			if(!(*pBookmarkTbl)[i]->IsBookMark())
/*?*/				nPos++;
/*?*/
/*?*/			i++;
/*?*/		}
/*?*/		while( i < nPos || !(*pBookmarkTbl)[nPos]->IsBookMark() );
/*?*/	}
/*?*/	return *(*pBookmarkTbl)[nPos];
/*N*/}


    // erzeugt einen eindeutigen Namen. Der Name selbst muss vorgegeben
    // werden, es wird dann bei gleichen Namen nur durchnumeriert.
/*N*/ void SwDoc::MakeUniqueBookmarkName( String& rNm )
/*N*/ {
/*?*/ 	DBG_BF_ASSERT(0, "STRIP"); //STRIP001 ASSERT( rNm.Len(), "es sollte ein Name vorgegeben werden!" );
//STRIP001 
//STRIP001 	// wir erzeugen uns eine temp. Bookmark
//STRIP001 	String sTmp;
//STRIP001 	USHORT nCnt = 0, n;
//STRIP001 	USHORT nBookCnt = pBookmarkTbl->Count();
//STRIP001 	do {
//STRIP001 		sTmp = rNm;
//STRIP001 		sTmp += String::CreateFromInt32( ++nCnt );
//STRIP001 		for( n = 0; n < nBookCnt; ++n )
//STRIP001 			if( (*pBookmarkTbl)[ n ]->GetName().Equals( sTmp ))
//STRIP001 				break;
//STRIP001 	} while( n < nBookCnt );
//STRIP001 	rNm = sTmp;
/*N*/ }

/*  */

/*N*/ SaveBookmark::SaveBookmark( int eType, const SwBookmark& rBkmk,
/*N*/ 							const SwNodeIndex & rMvPos,
/*N*/ 							const SwIndex* pIdx )
/*N*/ 	: aName( rBkmk.GetName() ), aShortName( rBkmk.GetShortName() ),
/*N*/ 	aCode( rBkmk.GetKeyCode() ), eBkmkType( (SaveBookmarkType)eType ),
/*N*/ 	eOrigBkmType(rBkmk.GetType())
/*N*/ {
    DBG_BF_ASSERT(0, "STRIP"); //STRIP001 nNode1 = rBkmk.GetPos().nNode.GetIndex();
//STRIP001 	nCntnt1 = rBkmk.GetPos().nContent.GetIndex();
//STRIP001 
//STRIP001 	if( BKMK_POS & eBkmkType )
//STRIP001 	{
//STRIP001 		nNode1 -= rMvPos.GetIndex();
//STRIP001 		if( pIdx && !nNode1 )
//STRIP001 			nCntnt1 -= pIdx->GetIndex();
//STRIP001 	}
//STRIP001 
//STRIP001 	if( rBkmk.GetOtherPos() )
//STRIP001 	{
//STRIP001 		nNode2 = rBkmk.GetOtherPos()->nNode.GetIndex();
//STRIP001 		nCntnt2 = rBkmk.GetOtherPos()->nContent.GetIndex();
//STRIP001 
//STRIP001 		if( BKMK_POS_OTHER & eBkmkType )
//STRIP001 		{
//STRIP001 			nNode2 -= rMvPos.GetIndex();
//STRIP001 			if( pIdx && !nNode2 )
//STRIP001 				nCntnt2 -= pIdx->GetIndex();
//STRIP001 		}
//STRIP001 	}
//STRIP001 	else
//STRIP001 		nNode2 = ULONG_MAX, nCntnt2 = STRING_NOTFOUND;
/*N*/ }

//STRIP001 void SaveBookmark::SetInDoc( SwDoc* pDoc, const SwNodeIndex& rNewPos,
//STRIP001 							const SwIndex* pIdx )
//STRIP001 {
//STRIP001 	SwPaM aPam( rNewPos.GetNode() );
//STRIP001 	if( pIdx )
//STRIP001 		aPam.GetPoint()->nContent = *pIdx;
//STRIP001 
//STRIP001 	if( ULONG_MAX != nNode2 )
//STRIP001 	{
//STRIP001 		aPam.SetMark();
//STRIP001 
//STRIP001 		if( BKMK_POS_OTHER & eBkmkType )
//STRIP001 		{
//STRIP001 			aPam.GetMark()->nNode += nNode2;
//STRIP001 			if( pIdx && !nNode2 )
//STRIP001 				aPam.GetMark()->nContent += nCntnt2;
//STRIP001 			else
//STRIP001 				aPam.GetMark()->nContent.Assign( aPam.GetCntntNode( FALSE ),
//STRIP001 														nCntnt2 );
//STRIP001 		}
//STRIP001 		else
//STRIP001 		{
//STRIP001 			aPam.GetMark()->nNode = nNode2;
//STRIP001 			aPam.GetMark()->nContent.Assign( aPam.GetCntntNode( FALSE ),
//STRIP001 													nCntnt2 );
//STRIP001 		}
//STRIP001 	}
//STRIP001 
//STRIP001 	if( BKMK_POS & eBkmkType )
//STRIP001 	{
//STRIP001 		aPam.GetPoint()->nNode += nNode1;
//STRIP001 
//STRIP001 		if( pIdx && !nNode1 )
//STRIP001 			aPam.GetPoint()->nContent += nCntnt1;
//STRIP001 		else
//STRIP001 			aPam.GetPoint()->nContent.Assign( aPam.GetCntntNode(), nCntnt1 );
//STRIP001 	}
//STRIP001 	else
//STRIP001 	{
//STRIP001 		aPam.GetPoint()->nNode = nNode1;
//STRIP001 		aPam.GetPoint()->nContent.Assign( aPam.GetCntntNode(), nCntnt1 );
//STRIP001 	}
//STRIP001 
//STRIP001 	if( !aPam.HasMark() ||
//STRIP001 		CheckNodesRange( aPam.GetPoint()->nNode, aPam.GetMark()->nNode, TRUE ))
//STRIP001 		pDoc->MakeBookmark( aPam, aCode, aName, aShortName, eOrigBkmType );
//STRIP001 }


/*N*/ inline int GreaterThan( const SwPosition& rPos, const SwNodeIndex& rNdIdx,
/*N*/ 						const SwIndex* pIdx )
/*N*/ {
/*N*/ 	return pIdx ? ( rPos.nNode > rNdIdx || ( rPos.nNode == rNdIdx &&
/*N*/ 										rPos.nContent >= pIdx->GetIndex() ))
/*N*/ 				: rPos.nNode >= rNdIdx;
/*N*/ }
/*N*/ inline int Lower( const SwPosition& rPos, const SwNodeIndex& rNdIdx,
/*N*/ 						const SwIndex* pIdx )
/*N*/ {
/*N*/ 	return rPos.nNode < rNdIdx || ( pIdx && rPos.nNode == rNdIdx &&
/*N*/ 										rPos.nContent < pIdx->GetIndex() );
/*N*/ }
/*N*/ inline int Greater( const SwPosition& rPos, const SwNodeIndex& rNdIdx,
/*N*/ 						const SwIndex* pIdx )
/*N*/ {
/*N*/ 	return rPos.nNode > rNdIdx || ( pIdx && rPos.nNode == rNdIdx &&
/*N*/ 										rPos.nContent > pIdx->GetIndex() );
/*N*/ }

/*N*/ void _DelBookmarks( const SwNodeIndex& rStt, const SwNodeIndex& rEnd,
/*N*/ 					SaveBookmarks* pSaveBkmk,
/*N*/ 					const SwIndex* pSttIdx, const SwIndex* pEndIdx )
/*N*/ {
/*N*/ 		// kein gueltiger Bereich ??
/*N*/ 	if( rStt.GetIndex() > rEnd.GetIndex() || ( rStt == rEnd &&
/*N*/ 		(!pSttIdx || pSttIdx->GetIndex() >= pEndIdx->GetIndex())) )
/*N*/ 		return;
/*N*/ 
/*N*/ 	// kopiere alle Bookmarks, die im Move Bereich stehen in ein
/*N*/ 	// Array, das alle Angaben auf die Position als Offset speichert.
/*N*/ 	// Die neue Zuordung erfolgt nach dem Moven.
/*N*/ 	SwDoc* pDoc = rStt.GetNode().GetDoc();
/*N*/ 	const SwBookmarks& rBkmks = pDoc->GetBookmarks();
        USHORT nCnt=0;
/*N*/ 	for( nCnt = 0; nCnt < rBkmks.Count(); ++nCnt )
/*N*/ 	{
/*N*/ 		// liegt auf der Position ??
/*N*/ 		int eType = BKMK_POS_NONE;
/*N*/ 		SwBookmark* pBkmk = rBkmks[ nCnt ];
/*N*/ 		//simple marks should not be moved
/*N*/ 		if(pBkmk->IsMark())
/*N*/ 			continue;
/*N*/ 		if( GreaterThan( pBkmk->GetPos(), rStt, pSttIdx ) &&
/*N*/ 			Lower( pBkmk->GetPos(), rEnd, pEndIdx ))
/*N*/ 			eType = BKMK_POS;
/*N*/ 		if( pBkmk->GetOtherPos() &&
/*N*/ 			GreaterThan( *pBkmk->GetOtherPos(), rStt, pSttIdx ) &&
/*N*/ 			Lower( *pBkmk->GetOtherPos(), rEnd, pEndIdx ))
/*N*/ 			eType |= BKMK_POS_OTHER;
/*N*/ 
/*N*/ 		if( BKMK_POS_NONE == eType )		// auf zum naechsten
/*N*/ 			continue;
/*N*/ 
/*N*/ 		if( pSaveBkmk )
/*N*/ 		{
/*N*/ 				// Besonderheit: komplett eingeschlossen? dann mitnehmen
/*N*/ 			if( pEndIdx && (BKMK_POS_OTHER | BKMK_POS) != eType &&
/*N*/ 				( ( BKMK_POS_OTHER & eType &&
/*N*/ 					pBkmk->GetPos().nNode == rEnd &&
/*N*/ 					pBkmk->GetPos().nContent == *pEndIdx ) ||
/*N*/ 				( BKMK_POS & eType && pBkmk->GetOtherPos() &&
/*N*/ 					pBkmk->GetOtherPos()->nNode == rEnd &&
/*N*/ 					pBkmk->GetOtherPos()->nContent == *pEndIdx ) ) )
/*N*/ 					eType = BKMK_POS_OTHER | BKMK_POS;
/*N*/ 
/*N*/ 			SaveBookmark * pSBkmk = new SaveBookmark( eType, *pBkmk, rStt, pSttIdx );
/*N*/ 			pSaveBkmk->C40_INSERT( SaveBookmark, pSBkmk, pSaveBkmk->Count() );
/*N*/ 			pDoc->DelBookmark( nCnt-- );
/*N*/ 		}
/*N*/ 		else if( (BKMK_POS_OTHER | BKMK_POS ) == eType ||
/*N*/ 				( BKMK_POS == eType && !pBkmk->GetOtherPos() ) )
/*N*/ 			pDoc->DelBookmark( nCnt-- );
/*N*/ 		else
/*N*/ 		{
/*N*/ 			SwPosition* pPos = (SwPosition*)(BKMK_POS & eType
/*N*/ 									? &pBkmk->GetPos()
/*N*/ 									: pBkmk->GetOtherPos());
/*N*/ 			pPos->nNode = rEnd;
/*N*/ 			if( pEndIdx )
/*N*/ 				pPos->nContent = *pEndIdx;
/*N*/ 			else
/*N*/ 			{
/*N*/ 				SwCntntNode* pCNd = pPos->nNode.GetNode().GetCntntNode();
/*N*/ 				BOOL bStt = TRUE;
/*N*/ 				if( !pCNd && 0 == ( pCNd = pDoc->GetNodes().GoNext( &pPos->nNode )) )
/*N*/ 				{
/*N*/ 					bStt = FALSE;
/*N*/ 					pPos->nNode = rStt;
/*N*/ 					if( 0 == ( pCNd = pDoc->GetNodes().GoPrevious( &pPos->nNode )) )
/*N*/ 					{
/*N*/ 						pPos->nNode = BKMK_POS == eType
/*N*/ 										? pBkmk->GetOtherPos()->nNode
/*N*/ 										: pBkmk->GetPos().nNode;
/*N*/ 						pCNd = pPos->nNode.GetNode().GetCntntNode();
/*N*/ 					}
/*N*/ 				}
/*N*/ 				xub_StrLen nTmp = bStt ? 0 : pCNd->Len();
/*N*/ 				pPos->nContent.Assign( pCNd, nTmp );
/*N*/ 			}
/*N*/ 
/*N*/ 			// keine ungueltigen Selektionen zulassen!
/*N*/ 			if( pBkmk->GetOtherPos() &&
/*N*/ 				pBkmk->GetOtherPos()->nNode.GetNode().FindTableBoxStartNode() !=
/*N*/ 				pBkmk->GetPos().nNode.GetNode().FindTableBoxStartNode() )
/*N*/ 			{
/*N*/ 				SwPaM aPam( pPos == pBkmk->GetOtherPos()
/*N*/ 								? pBkmk->GetPos() : *pBkmk->GetOtherPos()  );
/*N*/ 				String sNm( pBkmk->GetName() ), sShortNm( pBkmk->GetShortName() );
/*N*/ 				KeyCode aKCode( pBkmk->GetKeyCode() );
/*N*/ 
/*N*/ 				pDoc->DelBookmark( nCnt-- );
/*N*/ 				pDoc->MakeBookmark( aPam, aKCode, sNm, sShortNm, BOOKMARK );
/*N*/ 			}
/*N*/ 		}
/*N*/ 	}
/*N*/ 
/*N*/ 	// kopiere alle Redlines, die im Move Bereich stehen in ein
/*N*/ 	// Array, das alle Angaben auf die Position als Offset speichert.
/*N*/ 	// Die neue Zuordung erfolgt nach dem Moven.
/*N*/ 	SwRedlineTbl& rTbl = (SwRedlineTbl&)pDoc->GetRedlineTbl();
/*N*/ 	for( nCnt = 0; nCnt < rTbl.Count(); ++nCnt )
/*N*/ 	{
/*N*/ 		// liegt auf der Position ??
/*N*/ 		int eType = BKMK_POS_NONE;
/*N*/ 		SwRedline* pRedl = rTbl[ nCnt ];
/*N*/ 
/*N*/ 		SwPosition *pRStt = &pRedl->GetBound(TRUE),
/*N*/ 				   *pREnd = &pRedl->GetBound(FALSE);
/*N*/ 		if( *pRStt > *pREnd )
/*N*/ 		{
/*N*/ 			SwPosition *pTmp = pRStt; pRStt = pREnd, pREnd = pTmp;
/*N*/ 		}
/*N*/ 
/*N*/ 		if( Greater( *pRStt, rStt, pSttIdx ) && Lower( *pRStt, rEnd, pEndIdx ))
/*N*/ 		{
/*N*/ 			pRStt->nNode = rEnd;
/*N*/ 			if( pEndIdx )
/*N*/ 				pRStt->nContent = *pEndIdx;
/*N*/ 			else
/*N*/ 			{
/*N*/ 				BOOL bStt = TRUE;
/*N*/ 				SwCntntNode* pCNd = pRStt->nNode.GetNode().GetCntntNode();
/*N*/ 				if( !pCNd && 0 == ( pCNd = pDoc->GetNodes().GoNext( &pRStt->nNode )) )
/*N*/ 				{
/*N*/ 					bStt = FALSE;
/*N*/ 					pRStt->nNode = rStt;
/*N*/ 					if( 0 == ( pCNd = pDoc->GetNodes().GoPrevious( &pRStt->nNode )) )
/*N*/ 					{
/*N*/ 						pRStt->nNode = pREnd->nNode;
/*N*/ 						pCNd = pRStt->nNode.GetNode().GetCntntNode();
/*N*/ 					}
/*N*/ 				}
/*N*/ 				xub_StrLen nTmp = bStt ? 0 : pCNd->Len();
/*N*/ 				pRStt->nContent.Assign( pCNd, nTmp );
/*N*/ 			}
/*N*/ 		}
/*N*/ 		if( Greater( *pREnd, rStt, pSttIdx ) && Lower( *pREnd, rEnd, pEndIdx ))
/*N*/ 		{
/*N*/ 			pREnd->nNode = rStt;
/*N*/ 			if( pSttIdx )
/*N*/ 				pREnd->nContent = *pSttIdx;
/*N*/ 			else
/*N*/ 			{
/*N*/ 				BOOL bStt = FALSE;
/*N*/ 				SwCntntNode* pCNd = pREnd->nNode.GetNode().GetCntntNode();
/*N*/ 				if( !pCNd && 0 == ( pCNd = pDoc->GetNodes().GoPrevious( &pREnd->nNode )) )
/*N*/ 				{
/*N*/ 					bStt = TRUE;
/*N*/ 					pREnd->nNode = rEnd;
/*N*/ 					if( 0 == ( pCNd = pDoc->GetNodes().GoNext( &pREnd->nNode )) )
/*N*/ 					{
/*N*/ 						pREnd->nNode = pRStt->nNode;
/*N*/ 						pCNd = pREnd->nNode.GetNode().GetCntntNode();
/*N*/ 					}
/*N*/ 				}
/*N*/ 				xub_StrLen nTmp = bStt ? 0 : pCNd->Len();
/*N*/ 				pREnd->nContent.Assign( pCNd, nTmp );
/*N*/ 			}
/*N*/ 		}
/*N*/ 	}
/*N*/ }

/*  */


// Aufbau vom Array: 2 longs,
//	1. Long enthaelt Type und Position im DocArray,
//	2. die ContentPosition
//
//	CntntType --
//			0x8000 = Bookmark Pos1
//			0x8001 = Bookmark Pos2
//			0x2000 = Absatzgebundener Rahmen
//			0x2001 = Auto-Absatzgebundener Rahmen, der umgehaengt werden soll
//			0x1000 = Redline Mark
//			0x1001 = Redline Point
//			0x0800 = Crsr aus der CrsrShell Mark
//			0x0801 = Crsr aus der CrsrShell Point
//			0x0400 = UnoCrsr Mark
//			0x0401 = UnoCrsr Point
//

/*N*/ class _SwSaveTypeCountContent
/*N*/ {
/*N*/ 	union {
/*N*/ 		struct { USHORT nType, nCount; } TC;
/*N*/ 		ULONG nTypeCount;
/*N*/ 		} TYPECOUNT;
/*N*/ 	xub_StrLen nContent;
/*N*/ 
/*N*/ public:
/*N*/ 	_SwSaveTypeCountContent() { TYPECOUNT.nTypeCount = 0; nContent = 0; }
/*N*/ 	_SwSaveTypeCountContent( USHORT nType )
/*N*/ 		{
/*N*/ 			SetTypeAndCount( nType, 0 );
/*N*/ 			nContent = 0;
/*N*/ 		}
/*N*/ 	_SwSaveTypeCountContent( const SvULongs& rArr, USHORT& rPos )
/*N*/ 		{
/*N*/ 			TYPECOUNT.nTypeCount = rArr[ rPos++ ];
/*N*/ 			nContent = rArr[ rPos++ ];
/*N*/ 		}
/*N*/ 	void Add( SvULongs& rArr )
/*N*/ 	{
/*N*/ 		rArr.Insert( TYPECOUNT.nTypeCount, rArr.Count() );
/*N*/ 		rArr.Insert( nContent, rArr.Count() );
/*N*/ 	}
/*N*/ 
/*N*/ 	void SetType( USHORT n )		{ TYPECOUNT.TC.nType = n; }
/*N*/ 	USHORT GetType() const 			{ return TYPECOUNT.TC.nType; }
/*N*/ 	void IncType() 	 				{ ++TYPECOUNT.TC.nType; }
/*N*/ 	void DecType() 	 				{ --TYPECOUNT.TC.nType; }
/*N*/ 
/*N*/ 	void SetCount( USHORT n ) 		{ TYPECOUNT.TC.nCount = n; }
/*N*/ 	USHORT GetCount() const 		{ return TYPECOUNT.TC.nCount; }
/*N*/ 	USHORT IncCount()  				{ return ++TYPECOUNT.TC.nCount; }
/*N*/ 	USHORT DecCount()  				{ return --TYPECOUNT.TC.nCount; }
/*N*/ 
/*N*/ 	void SetTypeAndCount( USHORT nT, USHORT nC )
/*N*/ 		{ TYPECOUNT.TC.nCount = nC; TYPECOUNT.TC.nType = nT; }
/*N*/ 
/*N*/ 	void SetContent( xub_StrLen n )		{ nContent = n; }
/*N*/ 	xub_StrLen GetContent() const		{ return nContent; }
/*N*/ };


/*N*/ void _ChkPaM( SvULongs& rSaveArr, ULONG nNode, xub_StrLen nCntnt,
/*N*/ 				const SwPaM& rPam, _SwSaveTypeCountContent& rSave,
/*N*/ 				BOOL bChkSelDirection )
/*N*/ {
/*N*/ 	// SelektionsRichtung beachten
/*N*/ 	BOOL bBound1IsStart = !bChkSelDirection ? TRUE :
/*N*/ 						( *rPam.GetPoint() < *rPam.GetMark()
/*N*/ 							? rPam.GetPoint() == &rPam.GetBound()
/*N*/ 							: rPam.GetMark() == &rPam.GetBound());
/*N*/ 
/*N*/ 	const SwPosition* pPos = &rPam.GetBound( TRUE );
/*N*/ 	if( pPos->nNode.GetIndex() == nNode &&
/*N*/ 		( bBound1IsStart ? pPos->nContent.GetIndex() < nCntnt
/*N*/ 							: pPos->nContent.GetIndex() <= nCntnt ))
/*N*/ 	{
/*N*/ 		rSave.SetContent( pPos->nContent.GetIndex() );
/*N*/ 		rSave.Add( rSaveArr );
/*N*/ 	}
/*N*/ 
/*N*/ 	pPos = &rPam.GetBound( FALSE );
/*N*/ 	if( pPos->nNode.GetIndex() == nNode &&
/*N*/ 		( (bBound1IsStart && bChkSelDirection)
/*N*/ 					? pPos->nContent.GetIndex() <= nCntnt
/*N*/ 					: pPos->nContent.GetIndex() < nCntnt ))
/*N*/ 	{
/*N*/ 		rSave.SetContent( pPos->nContent.GetIndex() );
/*N*/ 		rSave.IncType();
/*N*/ 		rSave.Add( rSaveArr );
/*N*/ 		rSave.DecType();
/*N*/ 	}
/*N*/ }


/*N*/ void _SaveCntntIdx( SwDoc* pDoc, ULONG nNode, xub_StrLen nCntnt,
/*N*/ 					SvULongs& rSaveArr, BYTE nSaveFly )
/*N*/ {
/*N*/  	// 1. Bookmarks
/*N*/ 	_SwSaveTypeCountContent aSave;
/*N*/ 	aSave.SetTypeAndCount( 0x8000, 0 );
/*N*/ 
/*N*/ 	const SwBookmarks& rBkmks = pDoc->GetBookmarks();
/*N*/ 	for( ; aSave.GetCount() < rBkmks.Count(); aSave.IncCount() )
/*N*/ 	{
/*N*/ 		const SwBookmark* pBkmk = rBkmks[ aSave.GetCount() ];
/*N*/ 		if( pBkmk->GetPos().nNode.GetIndex() == nNode &&
/*N*/ 			pBkmk->GetPos().nContent.GetIndex() < nCntnt )
/*N*/ 		{
/*N*/ 			aSave.SetContent( pBkmk->GetPos().nContent.GetIndex() );
/*N*/ 			aSave.Add( rSaveArr );
/*N*/ 		}
/*N*/ 
/*N*/ 		if( pBkmk->GetOtherPos() && pBkmk->GetOtherPos()->nNode.GetIndex() ==
/*N*/ 			nNode && pBkmk->GetOtherPos()->nContent.GetIndex() < nCntnt )
/*N*/ 		{
/*N*/ 			aSave.SetContent( pBkmk->GetOtherPos()->nContent.GetIndex() );
/*N*/ 			aSave.IncType();
/*N*/ 			aSave.Add( rSaveArr );
/*N*/ 			aSave.DecType();
/*N*/ 		}
/*N*/ 	}
/*N*/ 
/*N*/ 	// 2. Redlines
/*N*/ 	aSave.SetTypeAndCount( 0x1000, 0 );
/*N*/ 	const SwRedlineTbl& rRedlTbl = pDoc->GetRedlineTbl();
/*N*/ 	for( ; aSave.GetCount() < rRedlTbl.Count(); aSave.IncCount() )
/*N*/ 	{
/*N*/ 		const SwRedline* pRdl = rRedlTbl[ aSave.GetCount() ];
/*N*/ 		if( pRdl->GetPoint()->nNode.GetIndex() == nNode &&
/*N*/ 			pRdl->GetPoint()->nContent.GetIndex() < nCntnt )
/*N*/ 		{
/*N*/ 			aSave.SetContent( pRdl->GetPoint()->nContent.GetIndex() );
/*N*/ 			aSave.IncType();
/*N*/ 			aSave.Add( rSaveArr );
/*N*/ 			aSave.DecType();
/*N*/ 		}
/*N*/ 
/*N*/ 		if( pRdl->HasMark() &&
/*N*/ 			pRdl->GetMark()->nNode.GetIndex() == nNode &&
/*N*/ 			pRdl->GetMark()->nContent.GetIndex() < nCntnt )
/*N*/ 		{
/*N*/ 			aSave.SetContent( pRdl->GetMark()->nContent.GetIndex() );
/*N*/ 			aSave.Add( rSaveArr );
/*N*/ 		}
/*N*/ 	}
/*N*/ 
/*N*/ 	// 4. Absatzgebundene Objekte
/*N*/ 	{
/*N*/ 		SwCntntNode *pNode = pDoc->GetNodes()[nNode]->GetCntntNode();
/*N*/ 		if( pNode )
/*N*/ 		{
/*N*/ 			const SwPosition* pAPos;
/*N*/ 
/*N*/ 			SwFrm* pFrm = pNode->GetFrm();
/*N*/ #if OSL_DEBUG_LEVEL > 1
/*N*/ 			static BOOL bViaDoc = FALSE;
/*N*/ 			if( bViaDoc )
/*N*/ 				pFrm = NULL;
/*N*/ #endif
/*N*/ 			if( pFrm ) // gibt es ein Layout? Dann ist etwas billiger...
/*N*/ 			{
/*N*/ 				if( pFrm->GetDrawObjs() )
/*N*/ 				{
/*N*/ 					const SwDrawObjs& rDObj = *pFrm->GetDrawObjs();
/*N*/ 					for( USHORT n = rDObj.Count(); n; )
/*N*/ 					{
/*N*/ 						SdrObject *pObj = rDObj[ --n ];
/*N*/ 						SwFrmFmt* pFmt = ((SwContact*)GetUserCall(pObj))->GetFmt();
/*N*/ 						const SwFmtAnchor& rAnchor = pFmt->GetAnchor();
/*N*/ 						if( ( ( nSaveFly && FLY_AT_CNTNT == rAnchor.GetAnchorId() ) ||
/*N*/ 							  FLY_AUTO_CNTNT == rAnchor.GetAnchorId() ) &&
/*N*/ 							( 0 != ( pAPos = rAnchor.GetCntntAnchor() ) ) )
/*N*/ 						{
/*N*/ 							aSave.SetType( 0x2000 );
/*N*/ 							aSave.SetContent( pAPos->nContent.GetIndex() );
/*N*/ 
/*N*/ 							ASSERT( nNode == pAPos->nNode.GetIndex(),
/*N*/ 									"_SaveCntntIdx: Wrong Node-Index" );
/*N*/ 							if( FLY_AUTO_CNTNT == rAnchor.GetAnchorId() )
/*N*/ 							{
/*N*/ 								if( nCntnt <= aSave.GetContent() )
/*N*/ 								{
/*N*/ 									if( SAVEFLY_SPLIT == nSaveFly )
/*N*/ 										aSave.IncType(); // = 0x2001;
/*N*/ 									else
/*N*/ 										continue;
/*N*/ 								}
/*N*/ 							}
/*N*/ 							aSave.SetCount( pDoc->GetSpzFrmFmts()->Count() );
/*N*/ 							while( aSave.GetCount() &&
/*N*/ 								   pFmt != (*pDoc->GetSpzFrmFmts())[
/*N*/ 								   			 aSave.DecCount() ] )
/*N*/ 								; // nothing
/*N*/ 							ASSERT( pFmt == (*pDoc->GetSpzFrmFmts())[
/*N*/ 													aSave.GetCount() ],
/*N*/ 									"_SaveCntntIdx: Lost FrameFormat" );
/*N*/ 							aSave.Add( rSaveArr );
/*N*/ 						}
/*N*/ 					}
/*N*/ 				}
/*N*/ 			}
/*N*/ 			else // Schade, kein Layout, dann ist es eben etwas teurer...
/*N*/ 			{
/*N*/ 				for( aSave.SetCount( pDoc->GetSpzFrmFmts()->Count() );
/*N*/ 						aSave.GetCount() ; )
/*N*/ 				{
/*N*/ 					SwFrmFmt* pFrmFmt = (*pDoc->GetSpzFrmFmts())[
/*N*/ 												aSave.DecCount() ];
/*N*/ 					if ( RES_FLYFRMFMT != pFrmFmt->Which() &&
/*N*/ 							RES_DRAWFRMFMT != pFrmFmt->Which() )
/*N*/ 						continue;
/*N*/ 
/*N*/ 					const SwFmtAnchor& rAnchor = pFrmFmt->GetAnchor();
/*N*/ 					if( ( FLY_AT_CNTNT == rAnchor.GetAnchorId() ||
/*N*/ 							FLY_AUTO_CNTNT == rAnchor.GetAnchorId() ) &&
/*N*/ 						0 != ( pAPos = rAnchor.GetCntntAnchor()) &&
/*N*/ 						nNode == pAPos->nNode.GetIndex() )
/*N*/ 					{
/*N*/ 						aSave.SetType( 0x2000 );
/*N*/ 						aSave.SetContent( pAPos->nContent.GetIndex() );
/*N*/ 						if( FLY_AUTO_CNTNT == rAnchor.GetAnchorId() )
/*N*/ 						{
/*N*/ 							if( nCntnt <= aSave.GetContent() )
/*N*/ 							{
/*N*/ 								if( SAVEFLY_SPLIT == nSaveFly )
/*N*/ 									aSave.IncType(); // = 0x2001;
/*N*/ 								else
/*N*/ 									continue;
/*N*/ 							}
/*N*/ 						}
/*N*/ 						aSave.Add( rSaveArr );
/*N*/ 					}
/*N*/ 				}
/*N*/ 			}
/*N*/ 		}
/*N*/ 	}
/*N*/ 	// 5. CrsrShell
/*N*/ 	{
/*N*/ 		SwCrsrShell* pShell = pDoc->GetEditShell();
/*N*/ 		if( pShell )
/*N*/ 		{
/*N*/ 			aSave.SetTypeAndCount( 0x800, 0 );
/*N*/ 			FOREACHSHELL_START( pShell )
/*N*/ 				register SwPaM *_pStkCrsr = PCURSH->GetStkCrsr();
/*N*/ 				if( _pStkCrsr )
/*N*/ 				do {
/*N*/ 					::binfilter::_ChkPaM( rSaveArr, nNode, nCntnt, *_pStkCrsr,
/*N*/ 								aSave, FALSE );
/*N*/ 					aSave.IncCount();
/*N*/ 				} while ( (_pStkCrsr != 0 ) &&
/*N*/ 					((_pStkCrsr=(SwPaM *)_pStkCrsr->GetNext()) != PCURSH->GetStkCrsr()) );
/*N*/ 
/*N*/ 				FOREACHPAM_START( PCURSH->_GetCrsr() )
/*N*/ 					::binfilter::_ChkPaM( rSaveArr, nNode, nCntnt, *PCURCRSR,
/*N*/ 								aSave, FALSE );
/*N*/ 					aSave.IncCount();
/*N*/ 				FOREACHPAM_END()
/*N*/ 
/*N*/ 			FOREACHSHELL_END( pShell )
/*N*/ 		}
/*N*/ 	}
/*N*/ 	// 6. UnoCrsr
/*N*/ 	{
/*N*/ 		aSave.SetTypeAndCount( 0x400, 0 );
/*N*/ 		register const SwUnoCrsrTbl& rTbl = pDoc->GetUnoCrsrTbl();
/*N*/ 		for( USHORT n = 0; n < rTbl.Count(); ++n )
/*N*/ 		{
/*N*/ 			FOREACHPAM_START( rTbl[ n ] )
/*N*/ 				::binfilter::_ChkPaM( rSaveArr, nNode, nCntnt, *PCURCRSR, aSave, FALSE );
/*N*/ 				aSave.IncCount();
/*N*/ 			FOREACHPAM_END()
/*N*/ 
/*N*/ 			SwUnoTableCrsr* pUnoTblCrsr = (SwUnoTableCrsr*)*rTbl[ n ];
/*N*/ 			if( pUnoTblCrsr )
/*N*/ 			{
/*N*/ 				FOREACHPAM_START( &pUnoTblCrsr->GetSelRing() )
/*N*/ 					::binfilter::_ChkPaM( rSaveArr, nNode, nCntnt, *PCURCRSR, aSave, FALSE );
/*N*/ 					aSave.IncCount();
/*N*/ 				FOREACHPAM_END()
/*N*/ 			}
/*N*/ 		}
/*N*/ 	}
/*N*/ }


/*N*/ void _RestoreCntntIdx( SwDoc* pDoc, SvULongs& rSaveArr,
/*N*/ 						ULONG nNode, xub_StrLen nOffset, BOOL bAuto )
/*N*/ {
/*N*/ 	SwCntntNode* pCNd = pDoc->GetNodes()[ nNode ]->GetCntntNode();
/*N*/ 	const SwBookmarks& rBkmks = pDoc->GetBookmarks();
/*N*/ 	const SwRedlineTbl& rRedlTbl = pDoc->GetRedlineTbl();
/*N*/ 	SwSpzFrmFmts* pSpz = pDoc->GetSpzFrmFmts();
/*N*/ 	USHORT n = 0;
/*N*/ 	while( n < rSaveArr.Count() )
/*N*/ 	{
/*N*/ 		_SwSaveTypeCountContent aSave( rSaveArr, n );
/*N*/ 		SwPosition* pPos = 0;
/*N*/ 		switch( aSave.GetType() )
/*N*/ 		{
/*N*/ 		case 0x8000:
/*N*/ 			pPos = (SwPosition*)&rBkmks[ aSave.GetCount() ]->GetPos();
/*N*/ 			break;
/*N*/ 		case 0x8001:
/*N*/ 			pPos = (SwPosition*)rBkmks[ aSave.GetCount() ]->GetOtherPos();
/*N*/ 			break;
/*N*/ 		case 0x1001:
/*N*/ 			pPos = (SwPosition*)rRedlTbl[ aSave.GetCount() ]->GetPoint();
/*N*/ 			break;
/*N*/ 		case 0x1000:
/*N*/ 			pPos = (SwPosition*)rRedlTbl[ aSave.GetCount() ]->GetMark();
/*N*/ 			break;
/*N*/ 		case 0x2000:
/*N*/ 			{
/*N*/ 				SwFrmFmt *pFrmFmt = (*pSpz)[ aSave.GetCount() ];
/*N*/ 				const SwFmtAnchor& rFlyAnchor = pFrmFmt->GetAnchor();
/*N*/ 				if( rFlyAnchor.GetCntntAnchor() )
/*N*/ 				{
/*N*/ 					SwFmtAnchor aNew( rFlyAnchor );
/*N*/ 					SwPosition aNewPos( *rFlyAnchor.GetCntntAnchor() );
/*N*/ 					aNewPos.nNode = *pCNd;
/*N*/ 					if( FLY_AUTO_CNTNT == rFlyAnchor.GetAnchorId() )
/*N*/ 						aNewPos.nContent.Assign( pCNd,
/*N*/ 												 aSave.GetContent() + nOffset );
/*N*/ 					else
/*N*/ 						aNewPos.nContent.Assign( 0, 0 );
/*N*/ 					aNew.SetAnchor( &aNewPos );
/*N*/ 					pFrmFmt->SetAttr( aNew );
/*N*/ 				}
/*N*/ 			}
/*N*/ 			break;
/*N*/ 		case 0x2001:
/*N*/ 			if( bAuto )
/*N*/ 			{
/*N*/ 				SwFrmFmt *pFrmFmt = (*pSpz)[ aSave.GetCount() ];
/*N*/ 				SfxPoolItem *pAnchor = (SfxPoolItem*)&pFrmFmt->GetAnchor();
/*N*/ 				pFrmFmt->SwModify::Modify( pAnchor, pAnchor );
/*N*/ 			}
/*N*/ 			break;
/*N*/ 
/*N*/ 		case 0x0800:
/*N*/ 		case 0x0801:
/*N*/ 			{
/*N*/ 				USHORT nCnt = 0;
/*N*/ 				SwCrsrShell* pShell = pDoc->GetEditShell();
/*N*/ 				if( pShell )
/*N*/ 				{
/*N*/ 					FOREACHSHELL_START( pShell )
/*N*/ 						register SwPaM *_pStkCrsr = PCURSH->GetStkCrsr();
/*N*/ 						if( _pStkCrsr )
/*N*/ 						do {
/*N*/ 							if( aSave.GetCount() == nCnt )
/*N*/ 							{
/*N*/ 								pPos = &_pStkCrsr->GetBound( 0x0800 ==
/*N*/ 													aSave.GetType() );
/*N*/ 								break;
/*N*/ 							}
/*N*/ 							++nCnt;
/*N*/ 						} while ( (_pStkCrsr != 0 ) &&
/*N*/ 							((_pStkCrsr=(SwPaM *)_pStkCrsr->GetNext()) != PCURSH->GetStkCrsr()) );
/*N*/ 
/*N*/ 						if( pPos )
/*N*/ 							break;
/*N*/ 
/*N*/ 						FOREACHPAM_START( PCURSH->_GetCrsr() )
/*N*/ 							if( aSave.GetCount() == nCnt )
/*N*/ 							{
/*N*/ 								pPos = &PCURCRSR->GetBound( 0x0800 ==
/*N*/ 													aSave.GetType() );
/*N*/ 								break;
/*N*/ 							}
/*N*/ 							++nCnt;
/*N*/ 						FOREACHPAM_END()
/*N*/ 						if( pPos )
/*N*/ 							break;
/*N*/ 
/*N*/ 					FOREACHSHELL_END( pShell )
/*N*/ 				}
/*N*/ 			}
/*N*/ 			break;
/*N*/ 
/*N*/ 		case 0x0400:
/*N*/ 		case 0x0401:
/*N*/ 			{
/*N*/ 				USHORT nCnt = 0;
/*N*/ 				register const SwUnoCrsrTbl& rTbl = pDoc->GetUnoCrsrTbl();
/*N*/ 				for( USHORT i = 0; i < rTbl.Count(); ++i )
/*N*/ 				{
/*N*/ 					FOREACHPAM_START( rTbl[ i ] )
/*N*/ 						if( aSave.GetCount() == nCnt )
/*N*/ 						{
/*N*/ 							pPos = &PCURCRSR->GetBound( 0x0400 ==
/*N*/ 													aSave.GetType() );
/*N*/ 							break;
/*N*/ 						}
/*N*/ 						++nCnt;
/*N*/ 					FOREACHPAM_END()
/*N*/ 					if( pPos )
/*N*/ 						break;
/*N*/ 
/*N*/ 					SwUnoTableCrsr* pUnoTblCrsr = (SwUnoTableCrsr*)*rTbl[ i ];
/*N*/ 					if( pUnoTblCrsr )
/*N*/ 					{
/*N*/ 						FOREACHPAM_START( &pUnoTblCrsr->GetSelRing() )
/*N*/ 							if( aSave.GetCount() == nCnt )
/*N*/ 							{
/*N*/ 								pPos = &PCURCRSR->GetBound( 0x0400 ==
/*N*/ 													aSave.GetType() );
/*N*/ 								break;
/*N*/ 							}
/*N*/ 							++nCnt;
/*N*/ 						FOREACHPAM_END()
/*N*/ 					}
/*N*/ 					if( pPos )
/*N*/ 						break;
/*N*/ 				}
/*N*/ 			}
/*N*/ 			break;
/*N*/ 		}
/*N*/ 
/*N*/ 		if( pPos )
/*N*/ 		{
/*N*/ 			pPos->nNode = *pCNd;
/*N*/ 			pPos->nContent.Assign( pCNd, aSave.GetContent() + nOffset );
/*N*/ 		}
/*N*/ 	}
/*N*/ }

/*N*/ void _RestoreCntntIdx( SvULongs& rSaveArr, const SwNode& rNd,
/*N*/ 						xub_StrLen nLen, xub_StrLen nChkLen )
/*N*/ {
DBG_BF_ASSERT(0, "STRIP"); //STRIP001 //STRIP001 	const SwDoc* pDoc = rNd.GetDoc();
//STRIP001 	const SwBookmarks& rBkmks = pDoc->GetBookmarks();
//STRIP001 	const SwRedlineTbl& rRedlTbl = pDoc->GetRedlineTbl();
//STRIP001 	const SwSpzFrmFmts* pSpz = pDoc->GetSpzFrmFmts();
//STRIP001 	SwCntntNode* pCNd = (SwCntntNode*)rNd.GetCntntNode();
//STRIP001 
//STRIP001 	USHORT n = 0;
//STRIP001 	while( n < rSaveArr.Count() )
//STRIP001 	{
//STRIP001 		_SwSaveTypeCountContent aSave( rSaveArr, n );
//STRIP001 		if( aSave.GetContent() >= nChkLen )
//STRIP001 			rSaveArr[ n + 1 ] -= nChkLen;
//STRIP001 		else
//STRIP001 		{
//STRIP001 			SwPosition* pPos = 0;
//STRIP001 			switch( aSave.GetType() )
//STRIP001 			{
//STRIP001 			case 0x8000:
//STRIP001 				pPos = (SwPosition*)&rBkmks[ aSave.GetCount() ]->GetPos();
//STRIP001 				break;
//STRIP001 			case 0x8001:
//STRIP001 				pPos = (SwPosition*)rBkmks[ aSave.GetCount() ]->GetOtherPos();
//STRIP001 				break;
//STRIP001 			case 0x1001:
//STRIP001 				pPos = (SwPosition*)rRedlTbl[ aSave.GetCount() ]->GetPoint();
//STRIP001 				break;
//STRIP001 			case 0x1000:
//STRIP001 				pPos = (SwPosition*)rRedlTbl[ aSave.GetCount() ]->GetMark();
//STRIP001 				break;
//STRIP001 			case 0x2000:
//STRIP001 			case 0x2001:
//STRIP001 				{
//STRIP001 					SwFrmFmt *pFrmFmt = (*pSpz)[ aSave.GetCount() ];
//STRIP001 					const SwFmtAnchor& rFlyAnchor = pFrmFmt->GetAnchor();
//STRIP001 					if( rFlyAnchor.GetCntntAnchor() )
//STRIP001 					{
//STRIP001 						SwFmtAnchor aNew( rFlyAnchor );
//STRIP001 						SwPosition aNewPos( *rFlyAnchor.GetCntntAnchor() );
//STRIP001 						aNewPos.nNode = rNd;
//STRIP001 						if( FLY_AUTO_CNTNT == rFlyAnchor.GetAnchorId() )
//STRIP001 							aNewPos.nContent.Assign( pCNd, Min(
//STRIP001 													 aSave.GetContent(), nLen ) );
//STRIP001 						else
//STRIP001 							aNewPos.nContent.Assign( 0, 0 );
//STRIP001 						aNew.SetAnchor( &aNewPos );
//STRIP001 						pFrmFmt->SetAttr( aNew );
//STRIP001 					}
//STRIP001 				}
//STRIP001 				break;
//STRIP001 
//STRIP001 			case 0x0800:
//STRIP001 			case 0x0801:
//STRIP001 				{
//STRIP001 					USHORT nCnt = 0;
//STRIP001 					SwCrsrShell* pShell = pDoc->GetEditShell();
//STRIP001 					if( pShell )
//STRIP001 					{
//STRIP001 						FOREACHSHELL_START( pShell )
//STRIP001 							register SwPaM *_pStkCrsr = PCURSH->GetStkCrsr();
//STRIP001 							if( _pStkCrsr )
//STRIP001 							do {
//STRIP001 								if( aSave.GetCount() == nCnt )
//STRIP001 								{
//STRIP001 									pPos = &_pStkCrsr->GetBound( 0x0800 ==
//STRIP001 												aSave.GetType() );
//STRIP001 									break;
//STRIP001 								}
//STRIP001 								++nCnt;
//STRIP001 							} while ( (_pStkCrsr != 0 ) &&
//STRIP001 								((_pStkCrsr=(SwPaM *)_pStkCrsr->GetNext()) != PCURSH->GetStkCrsr()) );
//STRIP001 
//STRIP001 							if( pPos )
//STRIP001 								break;
//STRIP001 
//STRIP001 							FOREACHPAM_START( PCURSH->_GetCrsr() )
//STRIP001 								if( aSave.GetCount() == nCnt )
//STRIP001 								{
//STRIP001 									pPos = &PCURCRSR->GetBound( 0x0800 ==
//STRIP001 												aSave.GetType() );
//STRIP001 									break;
//STRIP001 								}
//STRIP001 								++nCnt;
//STRIP001 							FOREACHPAM_END()
//STRIP001 							if( pPos )
//STRIP001 								break;
//STRIP001 
//STRIP001 						FOREACHSHELL_END( pShell )
//STRIP001 					}
//STRIP001 				}
//STRIP001 				break;
//STRIP001 
//STRIP001 			case 0x0400:
//STRIP001 			case 0x0401:
//STRIP001 				{
//STRIP001 					USHORT nCnt = 0;
//STRIP001 					register const SwUnoCrsrTbl& rTbl = pDoc->GetUnoCrsrTbl();
//STRIP001 					for( USHORT i = 0; i < rTbl.Count(); ++i )
//STRIP001 					{
//STRIP001 						FOREACHPAM_START( rTbl[ i ] )
//STRIP001 							if( aSave.GetCount() == nCnt )
//STRIP001 							{
//STRIP001 								pPos = &PCURCRSR->GetBound( 0x0400 ==
//STRIP001 													aSave.GetType() );
//STRIP001 								break;
//STRIP001 							}
//STRIP001 							++nCnt;
//STRIP001 						FOREACHPAM_END()
//STRIP001 						if( pPos )
//STRIP001 							break;
//STRIP001 
//STRIP001 						SwUnoTableCrsr* pUnoTblCrsr = (SwUnoTableCrsr*)*rTbl[ i ];
//STRIP001 						if( pUnoTblCrsr )
//STRIP001 						{
//STRIP001 							FOREACHPAM_START( &pUnoTblCrsr->GetSelRing() )
//STRIP001 								if( aSave.GetCount() == nCnt )
//STRIP001 								{
//STRIP001 									pPos = &PCURCRSR->GetBound( 0x0400 ==
//STRIP001 													aSave.GetType() );
//STRIP001 									break;
//STRIP001 								}
//STRIP001 								++nCnt;
//STRIP001 							FOREACHPAM_END()
//STRIP001 						}
//STRIP001 						if( pPos )
//STRIP001 							break;
//STRIP001 					}
//STRIP001 				}
//STRIP001 				break;
//STRIP001 			}
//STRIP001 
//STRIP001 			if( pPos )
//STRIP001 			{
//STRIP001 				pPos->nNode = rNd;
//STRIP001 				pPos->nContent.Assign( pCNd, Min( aSave.GetContent(), nLen ) );
//STRIP001 			}
//STRIP001 
//STRIP001 			rSaveArr.Remove( n, 2 );
//STRIP001 			n -= 2;
//STRIP001 		}
//STRIP001 	}
/*N*/ }


}
