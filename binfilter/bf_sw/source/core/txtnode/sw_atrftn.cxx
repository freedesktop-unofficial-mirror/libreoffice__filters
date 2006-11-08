/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: sw_atrftn.cxx,v $
 *
 *  $Revision: 1.8 $
 *
 *  last change: $Author: kz $ $Date: 2006-11-08 12:35:56 $
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

#define _SVSTDARR_USHORTS
#define _SVSTDARR_USHORTSSORT

#ifndef _HORIORNT_HXX
#include <horiornt.hxx>
#endif

#ifndef _DOC_HXX
#include <doc.hxx>
#endif
#ifndef _CNTFRM_HXX
#include <cntfrm.hxx>       // ASSERT in ~SwTxtFtn()
#endif
#ifndef _PAGEFRM_HXX
#include <pagefrm.hxx>      // RemoveFtn()
#endif
#ifndef _FMTFTN_HXX //autogen
#include <fmtftn.hxx>
#endif
#ifndef _TXTFTN_HXX //autogen
#include <txtftn.hxx>
#endif
#ifndef _FTNIDX_HXX //autogen
#include <ftnidx.hxx>
#endif
#ifndef _FTNINFO_HXX //autogen
#include <ftninfo.hxx>
#endif
#ifndef _NDTXT_HXX
#include <ndtxt.hxx>
#endif
#ifndef _POOLFMT_HXX
#include <poolfmt.hxx>
#endif
#ifndef _FTNFRM_HXX
#include <ftnfrm.hxx>
#endif
#ifndef _NDINDEX_HXX
#include <ndindex.hxx>
#endif
#ifndef _FMTFTNTX_HXX //autogen
#include <fmtftntx.hxx>
#endif
#ifndef _SECTION_HXX
#include <section.hxx>
#endif
namespace binfilter {

/*************************************************************************
|*
|*    class SwFmtFtn
|*
|*    Beschreibung
|*    Ersterstellung    JP 09.08.94
|*    Letzte Aenderung  JP 08.08.94
|*
*************************************************************************/


/*N*/ SwFmtFtn::SwFmtFtn( BOOL bEN )
/*N*/ 	: SfxPoolItem( RES_TXTATR_FTN ),
/*N*/ 	nNumber( 0 ),
/*N*/ 	pTxtAttr( 0 ),
/*N*/ 	bEndNote( bEN )
/*N*/ {
/*N*/ }


int SwFmtFtn::operator==( const SfxPoolItem& rAttr ) const
{
    {DBG_BF_ASSERT(0, "STRIP");} return 0;//STRIP001 	ASSERT( SfxPoolItem::operator==( rAttr ), "keine gleichen Attribute" );
}


/*N*/ SfxPoolItem* SwFmtFtn::Clone( SfxItemPool* ) const
/*N*/ {
/*N*/ 	SwFmtFtn* pNew	= new SwFmtFtn;
/*N*/ 	pNew->aNumber	= aNumber;
/*N*/ 	pNew->nNumber	= nNumber;
/*N*/ 	pNew->bEndNote	= bEndNote;
/*N*/ 	return pNew;
/*N*/ }

void SwFmtFtn::SetEndNote( BOOL b )
{
    if ( b != bEndNote )
    {
        if ( GetTxtFtn() )
            GetTxtFtn()->DelFrms();
        bEndNote = b;
    }
}

/*N*/ SwFmtFtn::~SwFmtFtn()
/*N*/ {
/*N*/ }



    // returnt den anzuzeigenden String der Fuss-/Endnote
/*N*/ XubString SwFmtFtn::GetViewNumStr( const SwDoc& rDoc, BOOL bInclStrings ) const
/*N*/ {
/*N*/ 	XubString sRet( GetNumStr() );
/*N*/ 	if( !sRet.Len() )
/*N*/ 	{
/*N*/ 		// dann ist die Nummer von Interesse, also ueber die Info diese
/*N*/ 		// besorgen.
/*N*/ 		BOOL bMakeNum = TRUE;
/*N*/ 		const SwSectionNode* pSectNd = pTxtAttr
/*N*/ 					? SwUpdFtnEndNtAtEnd::FindSectNdWithEndAttr( *pTxtAttr )
/*N*/ 					: 0;
/*N*/
/*N*/ 		if( pSectNd )
/*N*/ 		{
/*N*/ 			const SwFmtFtnEndAtTxtEnd& rFtnEnd = (SwFmtFtnEndAtTxtEnd&)
/*N*/ 				pSectNd->GetSection().GetFmt()->GetAttr(
/*?*/ 					IsEndNote() ? RES_END_AT_TXTEND : RES_FTN_AT_TXTEND );
/*N*/
/*N*/ 			if( FTNEND_ATTXTEND_OWNNUMANDFMT == rFtnEnd.GetValue() )
/*N*/ 			{
/*?*/ 				bMakeNum = FALSE;
/*?*/ 				sRet = rFtnEnd.GetSwNumType().GetNumStr( GetNumber() );
/*?*/ 				if( bInclStrings )
/*?*/ 				{
/*?*/ 					sRet.Insert( rFtnEnd.GetPrefix(), 0 );
/*?*/ 					sRet += rFtnEnd.GetSuffix();
/*?*/ 				}
/*N*/ 			}
/*N*/ 		}
/*N*/
/*N*/ 		if( bMakeNum )
/*N*/ 		{
/*N*/ 			const SwEndNoteInfo* pInfo;
/*N*/ 			if( IsEndNote() )
/*?*/ 				pInfo = &rDoc.GetEndNoteInfo();
/*N*/ 			else
/*N*/ 				pInfo = &rDoc.GetFtnInfo();
/*N*/ 			sRet = pInfo->aFmt.GetNumStr( GetNumber() );
/*N*/ 			if( bInclStrings )
/*N*/ 			{
/*N*/ 				sRet.Insert( pInfo->GetPrefix(), 0 );
/*N*/ 				sRet += pInfo->GetSuffix();
/*N*/ 			}
/*N*/ 		}
/*N*/ 	}
/*N*/ 	return sRet;
/*N*/ }

/*************************************************************************
 *						class SwTxt/FmtFnt
 *************************************************************************/

/*N*/ SwTxtFtn::SwTxtFtn( const SwFmtFtn& rAttr, xub_StrLen nStart )
/*N*/ 	: SwTxtAttr( rAttr, nStart ),
/*N*/ 	pMyTxtNd( 0 ),
/*N*/ 	pStartNode( 0 ),
/*N*/ 	nSeqNo( USHRT_MAX )
/*N*/ {
/*N*/ 	((SwFmtFtn&)rAttr).pTxtAttr = this;
/*N*/ }


/*N*/ SwTxtFtn::~SwTxtFtn()
/*N*/ {
/*N*/ 	SetStartNode( 0 );
/*N*/ }



/*N*/ void SwTxtFtn::SetStartNode( const SwNodeIndex *pNewNode, BOOL bDelNode )
/*N*/ {
/*N*/ 	if( pNewNode )
/*N*/ 	{
/*N*/ 		if( !pStartNode )
/*N*/ 			pStartNode = new SwNodeIndex( *pNewNode );
/*N*/ 		else
/*N*/ 			*pStartNode = *pNewNode;
/*N*/ 	}
/*N*/ 	else if( pStartNode )
/*N*/ 	{
/*N*/ 		// Zwei Dinge muessen erledigt werden:
/*N*/ 		// 1) Die Fussnoten muessen bei ihren Seiten abgemeldet werden
/*N*/ 		// 2) Die Fussnoten-Sektion in den Inserts muss geloescht werden.
/*N*/ 		SwDoc* pDoc;
/*N*/ 		if( pMyTxtNd )
/*N*/ 			pDoc = pMyTxtNd->GetDoc();
/*N*/ 		else
/*N*/ 		{
/*N*/ 			//JP 27.01.97: der sw3-Reader setzt einen StartNode aber das
/*N*/ 			//				Attribut ist noch nicht im TextNode verankert.
/*N*/ 			//				Wird es geloescht (z.B. bei Datei einfuegen mit
/*N*/ 			//				Ftn in einen Rahmen), muss auch der Inhalt
/*N*/ 			//				geloescht werden
/*?*/ 			pDoc = pStartNode->GetNodes().GetDoc();
/*N*/ 		}
/*N*/
/*N*/ 		// Wir duerfen die Fussnotennodes nicht loeschen
/*N*/ 		// und brauchen die Fussnotenframes nicht loeschen, wenn
/*N*/ 		// wir im ~SwDoc() stehen.
/*N*/ 		if( !pDoc->IsInDtor() )
/*N*/ 		{
/*?*/ 			if( bDelNode )
/*?*/ 			{
/*?*/ 				// 1) Die Section fuer die Fussnote wird beseitigt
/*?*/ 				// Es kann sein, dass die Inserts schon geloescht wurden.
/*?*/ 				pDoc->DeleteSection( &pStartNode->GetNode() );
/*?*/ 			}
/*?*/ 			else
/*?*/ 				// Werden die Nodes nicht geloescht mussen sie bei den Seiten
/*?*/ 				// abmeldet (Frms loeschen) werden, denn sonst bleiben sie
/*?*/ 				// stehen (Undo loescht sie nicht!)
                {DBG_BF_ASSERT(0, "STRIP");} //STRIP001 /*?*/ 				DelFrms();
/*N*/ 		}
/*N*/ 		DELETEZ( pStartNode );
/*N*/
/*N*/ 		// loesche die Fussnote noch aus dem Array am Dokument
/*N*/ 		for( USHORT n = 0; n < pDoc->GetFtnIdxs().Count(); ++n )
/*?*/ 			if( this == pDoc->GetFtnIdxs()[n] )
/*?*/ 			{
/*?*/ 				pDoc->GetFtnIdxs().Remove( n );
/*?*/ 				// gibt noch weitere Fussnoten
/*?*/ 				if( !pDoc->IsInDtor() && n < pDoc->GetFtnIdxs().Count() )
/*?*/ 				{
/*?*/ 					SwNodeIndex aTmp( pDoc->GetFtnIdxs()[n]->GetTxtNode() );
/*?*/ 					pDoc->GetFtnIdxs().UpdateFtn( aTmp );
/*?*/ 				}
/*?*/ 				break;
/*?*/ 			}
/*N*/ 	}
/*N*/ }


/*N*/ void SwTxtFtn::SetNumber( const USHORT nNewNum, const XubString* pStr )
/*N*/ {
/*N*/ 	SwFmtFtn& rFtn = (SwFmtFtn&)GetFtn();
/*N*/ 	if( pStr && pStr->Len() )
/*N*/ 		rFtn.aNumber = *pStr;
/*N*/ 	else
/*N*/ 	{
/*N*/ 		rFtn.nNumber = nNewNum;
/*N*/ 		rFtn.aNumber = aEmptyStr;
/*N*/ 	}
/*N*/
/*N*/ 	ASSERT( pMyTxtNd, "wo ist mein TextNode?" );
/*N*/ 	SwNodes &rNodes = pMyTxtNd->GetDoc()->GetNodes();
/*N*/ 	pMyTxtNd->Modify( 0, &rFtn );
/*N*/ 	if( pStartNode )
/*N*/ 	{
/*N*/ 		// Wir muessen ueber alle TxtNodes iterieren, wegen der
/*N*/ 		// Fussnoten, die auf anderen Seiten stehen.
/*N*/ 		SwNode* pNd;
/*N*/ 		ULONG nSttIdx = pStartNode->GetIndex() + 1,
/*N*/ 			  nEndIdx = pStartNode->GetNode().EndOfSectionIndex();
/*N*/ 		for( ; nSttIdx < nEndIdx; ++nSttIdx )
/*N*/ 		{
/*N*/ 			// Es koennen ja auch Grafiken in der Fussnote stehen ...
/*N*/ 			if( ( pNd = rNodes[ nSttIdx ] )->IsTxtNode() )
/*N*/ 				((SwTxtNode*)pNd)->Modify( 0, &rFtn );
/*N*/ 		}
/*N*/ 	}
/*N*/ }

// Die Fussnoten duplizieren


    // lege eine neue leere TextSection fuer diese Fussnote an
/*N*/ void SwTxtFtn::MakeNewTextSection( SwNodes& rNodes )
/*N*/ {
/*N*/ 	if( pStartNode )
/*N*/ 		return;
/*N*/
/*N*/ 	// Nun verpassen wir dem TxtNode noch die Fussnotenvorlage.
/*N*/ 	SwTxtFmtColl *pFmtColl;
/*N*/ 	const SwEndNoteInfo* pInfo;
/*N*/ 	USHORT nPoolId;
/*N*/
/*N*/ 	if( GetFtn().IsEndNote() )
/*N*/ 	{
/*?*/ 		pInfo = &rNodes.GetDoc()->GetEndNoteInfo();
/*?*/ 		nPoolId = RES_POOLCOLL_ENDNOTE;
/*N*/ 	}
/*N*/ 	else
/*N*/ 	{
/*N*/ 		pInfo = &rNodes.GetDoc()->GetFtnInfo();
/*N*/ 		nPoolId = RES_POOLCOLL_FOOTNOTE;
/*N*/ 	}
/*N*/
/*N*/ 	if( 0 == (pFmtColl = pInfo->GetFtnTxtColl() ) )
/*N*/ 		pFmtColl = rNodes.GetDoc()->GetTxtCollFromPool( nPoolId );
/*N*/
/*N*/ 	SwStartNode* pSttNd = rNodes.MakeTextSection( SwNodeIndex( rNodes.GetEndOfInserts() ),
/*N*/ 										SwFootnoteStartNode, pFmtColl );
/*N*/ 	pStartNode = new SwNodeIndex( *pSttNd );
/*N*/ }


 void SwTxtFtn::DelFrms()
 {
    // loesche die Ftn-Frames aus den Seiten
    ASSERT( pMyTxtNd, "wo ist mein TextNode?" );
    if( !pMyTxtNd )
        return ;

    BOOL bFrmFnd = FALSE;
    {
        SwClientIter aIter( *pMyTxtNd );
        for( SwCntntFrm* pFnd = (SwCntntFrm*)aIter.First( TYPE( SwCntntFrm ));
                pFnd; pFnd = (SwCntntFrm*)aIter.Next() )
        {
             SwPageFrm* pPage = pFnd->FindPageFrm();
             if( pPage )
             {
                 pPage->RemoveFtn( pFnd, this );
                 bFrmFnd = TRUE;
             }
        }
    }
    //JP 13.05.97: falls das Layout vorm loeschen der Fussnoten entfernt
    //              wird, sollte man das ueber die Fussnote selbst tun
    if( !bFrmFnd && pStartNode )
    {
        SwNodeIndex aIdx( *pStartNode );
        SwCntntNode* pCNd = pMyTxtNd->GetNodes().GoNext( &aIdx );
        if( pCNd )
        {
            SwClientIter aIter( *pCNd );
            for( SwCntntFrm* pFnd = (SwCntntFrm*)aIter.First( TYPE( SwCntntFrm ));
                    pFnd; pFnd = (SwCntntFrm*)aIter.Next() )
            {
                SwPageFrm* pPage = pFnd->FindPageFrm();

                SwFrm *pFrm = pFnd->GetUpper();
                while ( pFrm && !pFrm->IsFtnFrm() )
                    pFrm = pFrm->GetUpper();

                SwFtnFrm *pFtn = (SwFtnFrm*)pFrm;
                while ( pFtn && pFtn->GetMaster() )
                    pFtn = pFtn->GetMaster();
                ASSERT( pFtn->GetAttr() == this, "Ftn mismatch error." );

                while ( pFtn )
                {
                    SwFtnFrm *pFoll = pFtn->GetFollow();
                    pFtn->Cut();
                    delete pFtn;
                    pFtn = pFoll;
                }
                pPage->UpdateFtnNum();
            }
        }
    }
 }


/*N*/ USHORT SwTxtFtn::SetSeqRefNo()
/*N*/ {
/*N*/ 	if( !pMyTxtNd )
/*N*/ 		return USHRT_MAX;
/*N*/
/*N*/ 	SwDoc* pDoc = pMyTxtNd->GetDoc();
/*N*/ 	if( pDoc->IsInReading() )
/*N*/ 		return USHRT_MAX;
/*N*/
/*N*/ 	USHORT n, nFtnCnt = pDoc->GetFtnIdxs().Count();
/*N*/
/*N*/ 	BYTE nTmp = 255 < nFtnCnt ? 255 : nFtnCnt;
/*N*/ 	SvUShortsSort aArr( nTmp, nTmp );
/*N*/
/*N*/ 	// dann testmal, ob die Nummer schon vergeben ist oder ob eine neue
/*N*/ 	// bestimmt werden muss.
/*N*/ 	SwTxtFtn* pTxtFtn;
/*N*/ 	for( n = 0; n < nFtnCnt; ++n )
/*N*/ 		if( (pTxtFtn = pDoc->GetFtnIdxs()[ n ]) != this )
/*?*/ 			aArr.Insert( pTxtFtn->nSeqNo );
/*N*/
/*N*/ 	// teste erstmal ob die Nummer schon vorhanden ist:
/*N*/ 	if( USHRT_MAX != nSeqNo )
/*N*/ 	{
/*N*/ 		for( n = 0; n < aArr.Count(); ++n )
/*?*/ 			if( aArr[ n ] > nSeqNo )
/*?*/ 				return nSeqNo;			// nicht vorhanden -> also benutzen
/*?*/ 			else if( aArr[ n ] == nSeqNo )
/*?*/ 				break;					// schon vorhanden -> neue erzeugen
/*N*/
/*N*/ 		if( n == aArr.Count() )
/*N*/ 			return nSeqNo;			// nicht vorhanden -> also benutzen
/*N*/ 	}
/*N*/
/*N*/ 	// alle Nummern entsprechend geflag, also bestimme die richtige Nummer
/*N*/ 	for( n = 0; n < aArr.Count(); ++n )
/*N*/ 		if( n != aArr[ n ] )
/*N*/ 			break;
/*N*/
/*N*/ 	return nSeqNo = n;
/*N*/ }

/*N*/ void SwTxtFtn::SetUniqueSeqRefNo( SwDoc& rDoc )
/*N*/ {
/*N*/ 	USHORT n, nStt = 0, nFtnCnt = rDoc.GetFtnIdxs().Count();
/*N*/
/*N*/ 	BYTE nTmp = 255 < nFtnCnt ? 255 : nFtnCnt;
/*N*/ 	SvUShortsSort aArr( nTmp, nTmp );
/*N*/
/*N*/ 	// dann alle Nummern zusammensammeln die schon existieren
/*N*/ 	SwTxtFtn* pTxtFtn;
/*N*/ 	for( n = 0; n < nFtnCnt; ++n )
/*N*/ 		if( USHRT_MAX != (pTxtFtn = rDoc.GetFtnIdxs()[ n ])->nSeqNo )
/*N*/ 			aArr.Insert( pTxtFtn->nSeqNo );
/*N*/
/*N*/
/*N*/ 	for( n = 0; n < nFtnCnt; ++n )
/*N*/ 		if( USHRT_MAX == (pTxtFtn = rDoc.GetFtnIdxs()[ n ])->nSeqNo )
/*N*/ 		{
/*N*/ 			for( ; nStt < aArr.Count(); ++nStt )
/*?*/ 				if( nStt != aArr[ nStt ] )
/*?*/ 				{
/*?*/
/*?*/ 					pTxtFtn->nSeqNo = nStt;
/*?*/ 					break;
/*?*/ 				}
/*N*/
/*N*/ 			if( USHRT_MAX == pTxtFtn->nSeqNo )
/*N*/ 				break;	// nichts mehr gefunden
/*N*/ 		}
/*N*/
/*N*/ 	// alle Nummern schon vergeben, also mit nStt++ weitermachen
/*N*/ 	for( ; n < nFtnCnt; ++n )
/*N*/ 		if( USHRT_MAX == (pTxtFtn = rDoc.GetFtnIdxs()[ n ])->nSeqNo )
/*N*/ 			pTxtFtn->nSeqNo = nStt++;
/*N*/ }





}
