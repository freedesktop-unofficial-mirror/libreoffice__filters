/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: sw_unocrsr.cxx,v $
 *
 *  $Revision: 1.7 $
 *
 *  last change: $Author: kz $ $Date: 2007-09-06 11:56:14 $
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


#ifdef _MSC_VER
#pragma hdrstop
#endif

#ifndef _ERRHDL_HXX
#include <errhdl.hxx>
#endif

#ifndef _UNOCRSR_HXX
#include <unocrsr.hxx>
#endif

#ifndef _HORIORNT_HXX
#include <horiornt.hxx>
#endif

#ifndef _DOC_HXX
#include <doc.hxx>
#endif
#ifndef _DOCARY_HXX
#include <docary.hxx>
#endif
namespace binfilter {

/*N*/ SV_IMPL_PTRARR( SwUnoCrsrTbl, SwUnoCrsrPtr )

/*N*/ IMPL_FIXEDMEMPOOL_NEWDEL( SwUnoCrsr, 10, 10 )

/*N*/ SwUnoCrsr::SwUnoCrsr( const SwPosition &rPos, SwPaM* pRing )
/*N*/ 	: SwCursor( rPos, pRing ), SwModify( 0 ),
/*N*/ 	bRemainInSection( TRUE ),
/*N*/ 	bSkipOverHiddenSections( FALSE ),
/*N*/ 	bSkipOverProtectSections( FALSE )
/*N*/ 
/*N*/ {}

/*?*/ SwUnoCrsr::SwUnoCrsr( SwUnoCrsr& rICrsr )
/*?*/ 	: SwCursor( rICrsr ), SwModify( 0 ),
/*?*/ 	bRemainInSection( rICrsr.bRemainInSection ),
/*?*/ 	bSkipOverHiddenSections( rICrsr.bSkipOverHiddenSections ),
/*?*/ 	bSkipOverProtectSections( rICrsr.bSkipOverProtectSections )
/*?*/ {}

/*N*/ SwUnoCrsr::~SwUnoCrsr()
/*N*/ {
/*N*/ 	SwDoc* pDoc = GetDoc();
/*N*/ 	if( !pDoc->IsInDtor() )
/*N*/ 	{
/*N*/ 		// dann muss der Cursor aus dem Array ausgetragen werden
/*N*/ 		SwUnoCrsrTbl& rTbl = (SwUnoCrsrTbl&)pDoc->GetUnoCrsrTbl();
/*N*/ 		USHORT nDelPos = rTbl.GetPos( this );
/*N*/ 
/*N*/ 		if( USHRT_MAX != nDelPos )
/*N*/ 			rTbl.Remove( nDelPos );
/*N*/ 		else
/*N*/ 			ASSERT( !this, "UNO Cursor nicht mehr im Array" );
/*N*/ 	}
/*N*/ 
/*N*/ 	// den gesamten Ring loeschen!
/*N*/ 	while( GetNext() != this )
/*N*/ 	{
/*N*/ 		Ring* pNxt = GetNext();
/*N*/ 		pNxt->MoveTo( 0 );		// ausketten
/*N*/ 		delete pNxt;			// und loeschen
/*N*/ 	}
/*N*/ }

/*N*/ SwUnoCrsr::operator SwUnoCrsr* ()	{ return this; }

/*

SwCursor* SwUnoCrsr::Create( SwPaM* pRing ) const
{
    return new SwUnoCrsr( *GetPoint(), pRing );
}

*/

/*N*/ FASTBOOL SwUnoCrsr::IsSelOvr( int eFlags )
/*N*/ {
/*N*/ 	if( bRemainInSection )
/*N*/ 	{
/*N*/ 		SwDoc* pDoc = GetDoc();
/*N*/ 		SwNodeIndex aOldIdx( *pDoc->GetNodes()[ GetSavePos()->nNode ] );
/*N*/ 		SwNodeIndex& rPtIdx = GetPoint()->nNode;
/*N*/ 		SwStartNode *pOldSttNd = aOldIdx.GetNode().FindStartNode(),
/*N*/ 					*pNewSttNd = rPtIdx.GetNode().FindStartNode();
/*N*/ 		if( pOldSttNd != pNewSttNd )
/*N*/ 		{
/*N*/ 			BOOL bMoveDown = GetSavePos()->nNode < rPtIdx.GetIndex();
/*N*/ 			BOOL bValidPos = FALSE;
/*N*/ 
/*N*/ 			// search the correct surrounded start node - which the index
/*N*/ 			// can't leave.
/*N*/ 			while( pOldSttNd->IsSectionNode() )
/*N*/ 				pOldSttNd = pOldSttNd->StartOfSectionNode();
/*N*/ 
/*N*/ 			// is the new index inside this surrounded section?
/*N*/ 			if( rPtIdx > *pOldSttNd &&
/*N*/ 				rPtIdx < pOldSttNd->EndOfSectionIndex() )
/*N*/ 			{
/*N*/ 				// check if it a valid move inside this section
/*N*/ 				// (only over SwSection's !)
/*N*/ 				const SwStartNode* pInvalidNode;
/*N*/ 				do {
/*N*/ 					pInvalidNode = 0;
/*N*/ 					pNewSttNd = rPtIdx.GetNode().FindStartNode();
/*N*/ 
/*N*/ 					const SwStartNode *pSttNd = pNewSttNd, *pEndNd = pOldSttNd;
/*N*/ 					if( pSttNd->EndOfSectionIndex() >
/*N*/ 						pEndNd->EndOfSectionIndex() )
/*N*/ 					{
/*?*/ 						pEndNd = pNewSttNd;
/*?*/ 						pSttNd = pOldSttNd;
/*N*/ 					}
/*N*/ 
/*N*/ 					while( pSttNd->GetIndex() > pEndNd->GetIndex() )
/*N*/ 					{
/*N*/ 						if( !pSttNd->IsSectionNode() )
/*?*/ 							pInvalidNode = pSttNd;
/*N*/ 						pSttNd = pSttNd->StartOfSectionNode();
/*N*/ 					}
/*N*/ 					if( pInvalidNode )
/*N*/ 					{
/*?*/ 						if( bMoveDown )
/*?*/ 						{
/*?*/ 							rPtIdx.Assign( *pInvalidNode->EndOfSectionNode(), 1 );
/*?*/ 
/*?*/ 							if( !rPtIdx.GetNode().IsCntntNode() &&
/*?*/ 								!pDoc->GetNodes().GoNextSection( &rPtIdx ))
/*?*/ 								break;
/*?*/ 						}
/*?*/ 						else
/*?*/ 						{
/*?*/ 							rPtIdx.Assign( *pInvalidNode, -1 );
/*?*/ 
/*?*/ 							if( !rPtIdx.GetNode().IsCntntNode() &&
/*?*/ 								!pDoc->GetNodes().GoPrevSection( &rPtIdx ))
/*?*/ 								break;
/*?*/ 						}
/*N*/ 					}
/*N*/ 					else
/*N*/ 						bValidPos = TRUE;
/*N*/ 				} while ( pInvalidNode );
/*N*/ 			}
/*N*/ 
/*N*/ 			if( bValidPos )
/*N*/ 			{
/*N*/ 				SwCntntNode* pCNd = GetCntntNode();
/*N*/ 				USHORT nCnt = 0;
/*N*/ 				if( pCNd && !bMoveDown )
/*N*/ 					nCnt = pCNd->Len();
/*N*/ 				GetPoint()->nContent.Assign( pCNd, nCnt );
/*N*/ 			}
/*N*/ 			else
/*N*/ 			{
/*N*/ 				rPtIdx = GetSavePos()->nNode;
/*N*/ 				GetPoint()->nContent.Assign( GetCntntNode(), GetSavePos()->nCntnt );
/*N*/ 				return TRUE;
/*N*/ 			}
/*N*/ 		}
/*N*/ 	}
/*N*/ 	return SwCursor::IsSelOvr( eFlags );
/*N*/ }


/*  */

/*N*/ SwUnoTableCrsr::SwUnoTableCrsr( const SwPosition& rPos )
/*N*/ 	: SwTableCursor( rPos ), SwUnoCrsr( rPos ),	SwCursor( rPos ),
/*N*/ 	aTblSel( rPos )
/*N*/ {
/*?*/ 	DBG_BF_ASSERT(0, "STRIP"); //STRIP001 SetRemainInSection( FALSE );
/*N*/ }

/*N*/ SwUnoTableCrsr::~SwUnoTableCrsr()
/*N*/ {
/*?*/ 	DBG_BF_ASSERT(0, "STRIP"); //STRIP001 while( aTblSel.GetNext() != &aTblSel )
/*N*/ }

/*N*/ SwUnoTableCrsr::operator SwUnoCrsr* ()		{ return this; }
/*N*/ SwUnoTableCrsr::operator SwTableCursor* ()	{ return this; }
/*N*/ SwUnoTableCrsr::operator SwUnoTableCrsr* ()	{ return this; }

/*
SwCursor* SwUnoTableCrsr::Create( SwPaM* pRing ) const
{
    return SwUnoCrsr::Create( pRing );
}
*/

/*N*/ FASTBOOL SwUnoTableCrsr::IsSelOvr( int eFlags )
/*N*/ {
/*?*/ 	DBG_BF_ASSERT(0, "STRIP"); return FALSE;//STRIP001 FASTBOOL bRet = SwUnoCrsr::IsSelOvr( eFlags );
/*N*/ }

/*N*/ void SwUnoTableCrsr::MakeBoxSels()
/*N*/ {DBG_BF_ASSERT(0, "STRIP"); //STRIP001 
/*N*/ }

/*  */

/*N*/ SwUnoCrsr* SwDoc::CreateUnoCrsr( const SwPosition& rPos, BOOL bTblCrsr )
/*N*/ {
/*N*/ 	SwUnoCrsr* pNew;
/*N*/ 	if( bTblCrsr )
/*?*/ 		{DBG_BF_ASSERT(0, "STRIP"); }//STRIP001 pNew = new SwUnoTableCrsr( rPos );
/*N*/ 	else
/*N*/ 		pNew = new SwUnoCrsr( rPos );
/*N*/ 
/*N*/ 	pUnoCrsrTbl->Insert( pNew, pUnoCrsrTbl->Count() );
/*N*/ 	return pNew;
/*N*/ }

}
