/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: sw_callnk.cxx,v $
 *
 *  $Revision: 1.7 $
 *
 *  last change: $Author: kz $ $Date: 2007-09-06 11:53:39 $
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


#ifndef _COM_SUN_STAR_I18N_SCRIPTTYPE_HDL_
#include <com/sun/star/i18n/ScriptType.hdl>
#endif
#ifndef _FMTCNTNT_HXX //autogen
#include <fmtcntnt.hxx>
#endif
#ifndef _TXATBASE_HXX //autogen
#include <txatbase.hxx>
#endif
#ifndef _VISCRS_HXX
#include <viscrs.hxx>
#endif
#ifndef _CALLNK_HXX
#include <callnk.hxx>
#endif

#ifndef _HORIORNT_HXX
#include <horiornt.hxx>
#endif

#ifndef _CRSRSH_HXX
#include <crsrsh.hxx>
#endif
#ifndef _FRMFMT_HXX
#include <frmfmt.hxx>
#endif
#ifndef _TXTFRM_HXX
#include <txtfrm.hxx>
#endif
#ifndef _NDTXT_HXX
#include <ndtxt.hxx>
#endif
#ifndef _FLYFRM_HXX
#include <flyfrm.hxx>
#endif
#ifndef _BREAKIT_HXX
#include <breakit.hxx>
#endif
namespace binfilter {


/*N*/ SwCallLink::SwCallLink( SwCrsrShell & rSh )
/*N*/ 	: rShell( rSh )
/*N*/ {
    // SPoint-Werte vom aktuellen Cursor merken
/*N*/ 	SwPaM* pCrsr = rShell.IsTableMode() ? rShell.GetTblCrs() : rShell.GetCrsr();
/*N*/ 	SwNode& rNd = pCrsr->GetPoint()->nNode.GetNode();
/*N*/ 	nNode = rNd.GetIndex();
/*N*/ 	nCntnt = pCrsr->GetPoint()->nContent.GetIndex();
/*N*/ 	nNdTyp = rNd.GetNodeType();
/*N*/	bHasSelection = ( *pCrsr->GetPoint() != *pCrsr->GetMark() );
/*N*/ 
/*N*/ 	if( ND_TEXTNODE & nNdTyp )
/*N*/ 		nLeftFrmPos = SwCallLink::GetFrm( (SwTxtNode&)rNd, nCntnt,
/*N*/ 											!rShell.ActionPend() );
/*N*/ 	else
/*N*/ 	{
/*?*/ 		nLeftFrmPos = 0;
/*?*/ 
/*?*/ 		// eine Sonderbehandlung fuer die SwFeShell: diese setzt beim Loeschen
/*?*/ 		// der Kopf-/Fusszeile, Fussnoten den Cursor auf NULL (Node + Content)
/*?*/ 		// steht der Cursor auf keinem CntntNode, wird sich das im NdType
/*?*/ 		// gespeichert.
/*?*/ 		if( ND_CONTENTNODE & nNdTyp )
/*?*/ 			nNdTyp = 0;
/*N*/ 	}
/*N*/ }


/*M*/ SwCallLink::~SwCallLink()
/*M*/ {
/*M*/ 	if( !nNdTyp || !rShell.bCallChgLnk )		// siehe ctor
/*M*/ 		return ;
/*M*/ 
/*M*/ 	// wird ueber Nodes getravellt, Formate ueberpruefen und im neuen
/*M*/ 	// Node wieder anmelden
/*M*/ 	SwPaM* pCurCrsr = rShell.IsTableMode() ? rShell.GetTblCrs() : rShell.GetCrsr();
/*M*/ 	SwCntntNode * pCNd = pCurCrsr->GetCntntNode();
/*M*/ 	if( !pCNd )
/*M*/ 		return;
/*M*/ 
/*M*/ 	xub_StrLen nCmp, nAktCntnt = pCurCrsr->GetPoint()->nContent.GetIndex();
/*M*/ 	USHORT nNdWhich = pCNd->GetNodeType();
/*M*/ 	ULONG nAktNode = pCurCrsr->GetPoint()->nNode.GetIndex();
/*M*/ 
/*M*/ 	// melde die Shell beim akt. Node als abhaengig an, dadurch koennen
/*M*/ 	// alle Attribut-Aenderungen ueber den Link weiter gemeldet werden.
/*M*/ 	pCNd->Add( &rShell );
/*M*/ 
/*M*/ 	if( nNdTyp != nNdWhich || nNode != nAktNode )
/*M*/ 	{
        /* immer, wenn zwischen Nodes gesprungen wird, kann es
         * vorkommen, das neue Attribute gelten; die Text-Attribute.
         * Es muesste also festgestellt werden, welche Attribute
         * jetzt gelten; das kann auch gleich der Handler machen
         */
/*M*/ 		rShell.CallChgLnk();
/*M*/ 	}
/*N*/     else if( bHasSelection != (*pCurCrsr->GetPoint() != *pCurCrsr->GetMark()) )
/*N*/     {
/*N*/         // always call change link when selection changes
/*N*/ 		rShell.CallChgLnk();
/*N*/     }
/*M*/ 	else if( rShell.aChgLnk.IsSet() && ND_TEXTNODE == nNdWhich &&
/*M*/ 			 nCntnt != nAktCntnt )
/*M*/ 	{
/*M*/ 		// nur wenn mit Left/right getravellt, dann Text-Hints pruefen
/*M*/ 		// und sich nicht der Frame geaendert hat (Spalten!)
/*M*/ 		if( nLeftFrmPos == SwCallLink::GetFrm( (SwTxtNode&)*pCNd, nAktCntnt,
/*M*/ 													!rShell.ActionPend() ) &&
/*M*/ 			(( nCmp = nCntnt ) + 1 == nAktCntnt ||			// Right
/*M*/ 			nCntnt -1 == ( nCmp = nAktCntnt )) )			// Left
/*M*/ 		{
/*M*/ 			if( nCmp == nAktCntnt && pCurCrsr->HasMark() ) // left & Sele
/*M*/ 				++nCmp;
/*M*/ 			if ( ((SwTxtNode*)pCNd)->HasHints() )
/*M*/ 			{
/*M*/ 
/*M*/ 				const SwpHints &rHts = ((SwTxtNode*)pCNd)->GetSwpHints();
/*M*/ 				USHORT n;
/*M*/ 				xub_StrLen nStart;
/*M*/ 				const xub_StrLen *pEnd;
/*M*/ 
/*M*/ 				for( n = 0; n < rHts.Count(); n++ )
/*M*/ 				{
/*M*/ 					const SwTxtAttr* pHt = rHts[ n ];
/*M*/ 					pEnd = pHt->GetEnd();
/*M*/ 					nStart = *pHt->GetStart();
/*M*/ 
/*M*/ 					// nur Start oder Start und Ende gleich, dann immer
/*M*/ 					// beim Ueberlaufen von Start callen
/*M*/ 					if( ( !pEnd || ( nStart == *pEnd ) ) &&
/*M*/ 						( nStart == nCntnt || nStart == nAktCntnt) )
/*M*/ 					{
/*M*/ 						rShell.CallChgLnk();
/*M*/ 						return;
/*M*/ 					}
/*M*/ 
/*M*/ 					// hat das Attribut einen Bereich und dieser nicht leer
/*M*/ 					else if( pEnd && nStart < *pEnd &&
/*M*/ 						// dann teste, ob ueber Start/Ende getravellt wurde
/*M*/ 						( nStart == nCmp ||
/*M*/ 							( pHt->DontExpand() ? nCmp == *pEnd-1
/*M*/ 												: nCmp == *pEnd ) ))
/*M*/ 					{
/*M*/ 						rShell.CallChgLnk();
/*M*/ 						return;
/*M*/ 					}
/*M*/ 					nStart = 0;
/*M*/ 				}
/*M*/ 			}
/*M*/ 
/*M*/ 			if( pBreakIt->xBreak.is() )
/*M*/ 			{
/*M*/ 				const String& rTxt = ((SwTxtNode*)pCNd)->GetTxt();
/*M*/ 				if( !nCmp ||
/*M*/ 					pBreakIt->xBreak->getScriptType( rTxt, nCmp )
/*M*/ 					 != pBreakIt->xBreak->getScriptType( rTxt, nCmp - 1 ))
/*M*/ 				{
/*M*/ 					rShell.CallChgLnk();
/*M*/ 					return;
/*M*/ 				}
/*M*/ 			}
/*M*/ 		}
/*M*/ 		else
            /* wenn mit Home/End/.. mehr als 1 Zeichen getravellt, dann
             * immer den ChgLnk rufen, denn es kann hier nicht
             * festgestellt werden, was sich geaendert; etwas kann
             * veraendert sein.
             */
/*M*/ 			rShell.CallChgLnk();
/*M*/ 	}
/*M*/ 
/*M*/ 	const SwFrm* pFrm;
/*M*/ 	const SwFlyFrm *pFlyFrm;
/*M*/ 	if( !rShell.ActionPend() && 0 != ( pFrm = pCNd->GetFrm(0,0,FALSE) ) &&
/*M*/ 		0 != ( pFlyFrm = pFrm->FindFlyFrm() ) && !rShell.IsTableMode() )
/*M*/ 	{
/*M*/ 		const SwNodeIndex* pIndex = pFlyFrm->GetFmt()->GetCntnt().GetCntntIdx();
/*M*/ 		ASSERT( pIndex, "Fly ohne Cntnt" );
/*M*/ 		const SwNode& rStNd = pIndex->GetNode();
/*M*/ 
/*M*/ 		if( rStNd.EndOfSectionNode()->StartOfSectionIndex() > nNode ||
/*M*/ 			nNode > rStNd.EndOfSectionIndex() )
/*M*/ 			rShell.GetFlyMacroLnk().Call( (void*)pFlyFrm->GetFmt() );
/*M*/ 	}
/*M*/ }

/*N*/ long SwCallLink::GetFrm( SwTxtNode& rNd, xub_StrLen nCntPos, BOOL bCalcFrm )
/*N*/ {
/*N*/ 	SwTxtFrm* pFrm = (SwTxtFrm*)rNd.GetFrm(0,0,bCalcFrm), *pNext = pFrm;
/*N*/ 	if ( pFrm && !pFrm->IsHiddenNow() )
/*N*/ 	{
/*N*/ 		if( pFrm->HasFollow() )
/*N*/ 			while( 0 != ( pNext = (SwTxtFrm*)pFrm->GetFollow() ) &&
/*N*/ 					nCntPos >= pNext->GetOfst() )
/*N*/ 				pFrm = pNext;
/*N*/ 
/*N*/ 		return pFrm->Frm().Left();
/*N*/ 	}
/*?*/ 	return 0;
/*N*/ }

/*---------------------------------------------------------------------*/


//SwChgLinkFlag::SwChgLinkFlag( SwCrsrShell& rShell )
//    : rCrsrShell( rShell ), bOldFlag( rShell.bCallChgLnk ), nLeftFrmPos( 0 )
//{
//    rCrsrShell.bCallChgLnk = FALSE;
//    if( bOldFlag && !rCrsrShell.pTblCrsr )
//    {
//        SwNode* pNd = rCrsrShell.pCurCrsr->GetNode();
//        if( ND_TEXTNODE & pNd->GetNodeType() )
//            nLeftFrmPos = SwCallLink::GetFrm( (SwTxtNode&)*pNd,
//                    rCrsrShell.pCurCrsr->GetPoint()->nContent.GetIndex(),
//                    !rCrsrShell.ActionPend() );
//    }
//}


//SwChgLinkFlag::~SwChgLinkFlag()
//{
//    rCrsrShell.bCallChgLnk = bOldFlag;
//    if( bOldFlag && !rCrsrShell.pTblCrsr )
//    {
//        // die Spalten Ueberwachung brauchen wir immer!!!
//        SwNode* pNd = rCrsrShell.pCurCrsr->GetNode();
//        if( ND_TEXTNODE & pNd->GetNodeType() &&
//            nLeftFrmPos != SwCallLink::GetFrm( (SwTxtNode&)*pNd,
//                    rCrsrShell.pCurCrsr->GetPoint()->nContent.GetIndex(),
//                    !rCrsrShell.ActionPend() ))
//        {
//            /* immer, wenn zwischen Frames gesprungen wird, gelten
//             * neue Attribute. Es muesste also festgestellt werden, welche
//             * Attribute jetzt gelten; das kann gleich der Handler machen.
//             * Diesen direkt rufen !!!
//             */
//            rCrsrShell.aChgLnk.Call( &rCrsrShell );
//            rCrsrShell.bChgCallFlag = FALSE;        // Flag zuruecksetzen
//        }
//    }
//}




}
