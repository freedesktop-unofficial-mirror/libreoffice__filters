/*************************************************************************
 *
 *  $RCSfile: sw_swbaslnk.cxx,v $
 *
 *  $Revision: 1.1 $
 *
 *  last change: $Author: aw $ $Date: 2003-10-02 15:14:23 $
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

#define ITEMID_BOXINFO      SID_ATTR_BORDER_INNER

#include <hintids.hxx>

#ifndef _SV_SVAPP_HXX
#include <vcl/svapp.hxx>
#endif
#ifndef _SV_OUTDEV_HXX
#include <vcl/outdev.hxx>
#endif

#ifndef _LNKBASE_HXX //autogen
#include <so3/lnkbase.hxx>
#endif
#ifndef _LINKMGR_HXX
#include <so3/linkmgr.hxx>
#endif
#ifndef _SFX_OBJSH_HXX //autogen
#include <bf_sfx2/objsh.hxx>
#endif
#ifndef _SVX_BOXITEM_HXX //autogen
#include <bf_svx/boxitem.hxx>
#endif
#ifndef _SVX_SVXIDS_HRC
#include <bf_svx/svxids.hrc>		// fuer die EventIds
#endif
#ifndef _SVXLINKMGR_HXX
#include <bf_svx/linkmgr.hxx>
#endif
#ifndef _SOERR_HXX
#include <so3/soerr.hxx>
#endif

#ifndef _FMTFSIZE_HXX //autogen
#include <fmtfsize.hxx>
#endif
#ifndef _FMTANCHR_HXX //autogen
#include <fmtanchr.hxx>
#endif
#ifndef _FRMATR_HXX
#include <frmatr.hxx>
#endif
#ifndef _FRMFMT_HXX //autogen
#include <frmfmt.hxx>
#endif
#ifndef _DOC_HXX
#include <doc.hxx>
#endif
#ifndef _PAM_HXX
#include <pam.hxx>
#endif
#ifndef _EDITSH_HXX
#include <editsh.hxx>
#endif
#ifndef _SWTABLE_HXX
#include <swtable.hxx>
#endif
#ifndef _DOCARY_HXX
#include <docary.hxx>
#endif
#ifndef _SWEVENT_HXX
#include <swevent.hxx>
#endif
#ifndef _SWBASLNK_HXX
#include <swbaslnk.hxx>
#endif
#ifndef _SWSERV_HXX
#include <swserv.hxx>
#endif
#ifndef _NDGRF_HXX
#include <ndgrf.hxx>
#endif
#ifndef _NDOLE_HXX
#include <ndole.hxx>
#endif
#ifndef _HINTS_HXX
#include <hints.hxx>
#endif
#ifndef _TABFRM_HXX
#include <tabfrm.hxx>
#endif
#ifndef _CNTFRM_HXX
#include <cntfrm.hxx>
#endif
#ifndef _HTMLTBL_HXX
#include <htmltbl.hxx>
#endif

/*N*/ BOOL SetGrfFlySize( const Size& rGrfSz, const Size& rFrmSz, SwGrfNode* pGrfNd );

/*N*/ TYPEINIT1( SwBaseLink, ::so3::SvBaseLink );

/*N*/ SV_IMPL_REF( SwServerObject )

/*N*/ SwBaseLink::~SwBaseLink()
/*N*/ {
/*N*/ }

/*N*/ void lcl_CallModify( SwGrfNode& rGrfNd, SfxPoolItem& rItem )
/*N*/ {
/*N*/ 	//JP 4.7.2001: call fist all not SwNoTxtFrames, then the SwNoTxtFrames.
/*N*/ 	//				The reason is, that in the SwNoTxtFrames the Graphic
/*N*/ 	//				after a Paint will be swapped out! So all other "behind"
/*N*/ 	//				them havent't a loaded Graphic. - #86501#
/*N*/ 	rGrfNd.LockModify();
/*N*/ 
/*N*/ 	SwClientIter aIter( rGrfNd );
/*N*/ 	for( int n = 0; n < 2; ++n )
/*N*/ 	{
/*N*/ 		SwClient * pLast = aIter.GoStart();
/*N*/ 		if( pLast ) 	// konnte zum Anfang gesprungen werden ??
/*N*/ 		{
/*N*/ 			do {
/*N*/ 				if( (0 == n) ^ ( 0 != pLast->ISA( SwCntntFrm )) )
/*N*/ 					pLast->Modify( &rItem, &rItem );
/*N*/ 			} while( 0 != ( pLast = aIter++ ));
/*N*/ 		}
/*N*/ 	}
/*N*/ 	rGrfNd.UnlockModify();
/*N*/ }


/*N*/ void SwBaseLink::DataChanged( const String& rMimeType,
/*N*/ 							const ::com::sun::star::uno::Any & rValue )
/*N*/ {
/*N*/ 	if( !pCntntNode )
/*N*/ 	{
/*?*/ 		ASSERT(!this, "DataChanged ohne ContentNode" );
/*?*/ 		return ;
/*N*/ 	}
/*N*/ 
/*N*/ 	SwDoc* pDoc = pCntntNode->GetDoc();
/*N*/ 	if( pDoc->IsInDtor() || ChkNoDataFlag() || bIgnoreDataChanged )
/*N*/ 	{
/*?*/ 		bIgnoreDataChanged = FALSE;
/*?*/ 		return ;
/*N*/ 	}
/*N*/ 
/*N*/ 	ULONG nFmt = SotExchange::GetFormatIdFromMimeType( rMimeType );
/*N*/ 
/*N*/ 	if( pCntntNode->IsNoTxtNode() &&
/*N*/ 		nFmt == SvxLinkManager::RegisterStatusInfoId() )
/*N*/ 	{
/*?*/ 		// nur eine Statusaenderung - Events bedienen ?
/*?*/ 		::rtl::OUString sState;
/*?*/ 		if( rValue.hasValue() && ( rValue >>= sState ))
/*?*/ 		{
/*?*/ 			USHORT nEvent = 0;
/*?*/ 			switch( sState.toInt32() )
/*?*/ 			{
/*?*/ 			case STATE_LOAD_OK:		nEvent = SVX_EVENT_IMAGE_LOAD;	break;
/*?*/ 			case STATE_LOAD_ERROR: 	nEvent = SVX_EVENT_IMAGE_ERROR;	break;
/*?*/ 			case STATE_LOAD_ABORT: 	nEvent = SVX_EVENT_IMAGE_ABORT;	break;
/*?*/ 			}
/*?*/ 
/*?*/ 			SwFrmFmt* pFmt;
/*?*/ 			if( nEvent && 0 != ( pFmt = pCntntNode->GetFlyFmt() ))
/*?*/ 			{
/*?*/ 				DBG_ASSERT(0, "STRIP"); //STRIP001 SwCallMouseEvent aCallEvent;
//STRIP001 /*?*/ 				aCallEvent.Set( EVENT_OBJECT_IMAGE, pFmt );
//STRIP001 /*?*/ 				pDoc->CallEvent( nEvent, aCallEvent );
/*?*/ 			}
/*?*/ 		}
/*?*/ 		return;			// das wars!
/*N*/ 	}
/*N*/ 
/*N*/ 	FASTBOOL bUpdate = FALSE;
/*N*/ 	FASTBOOL bGraphicArrived = FALSE;
/*N*/ 	FASTBOOL bGraphicPieceArrived = FALSE;
/*N*/ 	FASTBOOL bDontNotify = FALSE;
/*N*/ 	Size aGrfSz, aFrmFmtSz;
/*N*/ 
/*N*/ 	if( pCntntNode->IsGrfNode() )
/*N*/ 	{
/*N*/ 		GraphicObject& rGrfObj = ((SwGrfNode*)pCntntNode)->GetGrfObj();
/*N*/ 
/*N*/ 		bDontNotify = ((SwGrfNode*)pCntntNode)->IsFrameInPaint();
/*N*/ 
/*N*/ 		bGraphicArrived = GetObj()->IsDataComplete();
/*N*/ 		bGraphicPieceArrived = GetObj()->IsPending();
/*N*/ 		((SwGrfNode*)pCntntNode)->SetGrafikArrived( bGraphicArrived );
/*N*/ 
/*N*/ 		Graphic aGrf;
/*N*/ 		if( SvxLinkManager::GetGraphicFromAny( rMimeType, rValue, aGrf ) &&
/*N*/ 			( GRAPHIC_DEFAULT != aGrf.GetType() ||
/*N*/ 			  GRAPHIC_DEFAULT != rGrfObj.GetType() ) )
/*N*/ 		{
/*N*/ 			aGrfSz = ::GetGraphicSizeTwip( aGrf, 0 );
/*N*/ 			if( static_cast< const SwGrfNode * >( pCntntNode )->IsChgTwipSizeFromPixel() )
/*N*/ 			{
/*N*/ 				const MapMode aMapTwip( MAP_TWIP );
/*N*/ 				aFrmFmtSz =
/*N*/ 					Application::GetDefaultDevice()->PixelToLogic(
/*N*/ 						aGrf.GetSizePixel(), aMapTwip );
/*N*/ 
/*N*/ 			}
/*N*/ 			else
/*N*/ 			{
/*N*/ 				aFrmFmtSz = aGrfSz;
/*N*/ 			}
/*N*/ 			Size aSz( ((SwGrfNode*)pCntntNode)->GetTwipSize() );
/*N*/ 
/*N*/ 			if( bGraphicPieceArrived && GRAPHIC_DEFAULT != aGrf.GetType() &&
/*N*/ 				( !aSz.Width() || !aSz.Height() ) )
/*N*/ 			{
/*N*/ 				// wenn nur ein Teil ankommt, aber die Groesse nicht
/*N*/ 				// gesetzt ist, dann muss "unten" der Teil von
/*N*/ 				// bGraphicArrived durchlaufen werden!
/*N*/ 				// (ansonten wird die Grafik in deft. Size gepaintet)
/*N*/ 				bGraphicArrived = TRUE;
/*N*/ 				bGraphicPieceArrived = FALSE;
/*N*/ 			}
/*N*/ 
/*N*/ 			rGrfObj.SetGraphic( aGrf, rGrfObj.GetLink() );
/*N*/ 			bUpdate = TRUE;
/*N*/ 
/*N*/ 			// Bug 33999: damit der Node den Transparent-Status
/*N*/ 			//		richtig gesetzt hat, ohne auf die Grafik
/*N*/ 			//		zugreifen zu muessen (sonst erfolgt ein SwapIn!).
/*N*/ 			if( bGraphicArrived )
/*N*/ 			{
/*N*/ 				// Bug #34735#: immer mit der korrekten Grafik-Size
/*N*/ 				//				arbeiten
/*N*/ 				if( aGrfSz.Height() && aGrfSz.Width() &&
/*N*/ 					aSz.Height() && aSz.Width() &&
/*N*/ 					aGrfSz != aSz )
/*?*/ 					((SwGrfNode*)pCntntNode)->SetTwipSize( aGrfSz );
/*N*/ 			}
/*N*/ 		}
/*N*/ 		if ( bUpdate && !bGraphicArrived && !bGraphicPieceArrived )
/*?*/ 			((SwGrfNode*)pCntntNode)->SetTwipSize( Size(0,0) );
/*N*/ 	}
/*N*/ 	else if( pCntntNode->IsOLENode() )
/*?*/ 		bUpdate = TRUE;
/*N*/ 
/*N*/ 	ViewShell *pSh = 0;
/*N*/ 	SwEditShell* pESh = pDoc->GetEditShell( &pSh );
/*N*/ 
/*N*/ 	if ( bUpdate && bGraphicPieceArrived && !(bSwapIn || bDontNotify) )
/*N*/ 	{
/*?*/ 		//Hint ohne Actions verschicken, loest direktes Paint aus.
/*?*/ 		if ( (!pSh || !pSh->ActionPend()) && (!pESh || !pESh->ActionPend()) )
/*?*/ 		{
/*?*/ 			SwMsgPoolItem aMsgHint( RES_GRAPHIC_PIECE_ARRIVED );
/*?*/ 			pCntntNode->Modify( &aMsgHint, &aMsgHint );
/*?*/ 			bUpdate = FALSE;
/*?*/ 		}
/*N*/ 	}
/*N*/ 
/*N*/ 	static BOOL bInNotifyLinks = FALSE;
/*N*/ 	if( bUpdate && !bDontNotify && (!bSwapIn || bGraphicArrived) &&
/*N*/ 		!bInNotifyLinks)
/*N*/ 	{
/*N*/ 		BOOL bLockView = FALSE;
/*N*/ 		if( pSh )
/*N*/ 		{
/*N*/ 			bLockView = pSh->IsViewLocked();
/*N*/ 			pSh->LockView( TRUE );
/*N*/ 		}
/*N*/ 
/*N*/ 		if( pESh )
/*N*/ 			pESh->StartAllAction();
/*N*/ 		else if( pSh )
/*?*/ 			pSh->StartAction();
/*N*/ 
/*N*/ 		SwMsgPoolItem aMsgHint( bGraphicArrived ? RES_GRAPHIC_ARRIVED :
/*N*/ 												  RES_UPDATE_ATTR );
/*N*/ 
/*N*/ 		if ( bGraphicArrived )
/*N*/ 		{
/*N*/ 			//Alle benachrichtigen, die am gleichen Link horchen.
/*N*/ 			bInNotifyLinks = TRUE;
/*N*/ 
/*N*/ 			const ::so3::SvBaseLinks& rLnks = pDoc->GetLinkManager().GetLinks();
/*N*/ 			for( USHORT n = rLnks.Count(); n; )
/*N*/ 			{
/*N*/ 				::so3::SvBaseLink* pLnk = &(*rLnks[ --n ]);
/*N*/ 				if( pLnk && OBJECT_CLIENT_GRF == pLnk->GetObjType() &&
/*N*/ 					pLnk->ISA( SwBaseLink ) && pLnk->GetObj() == GetObj() )
/*N*/ 				{
/*N*/ 					SwBaseLink* pBLink = (SwBaseLink*)pLnk;
/*N*/ 					SwGrfNode* pGrfNd = (SwGrfNode*)pBLink->pCntntNode;
/*N*/ 
/*N*/ 					if( pBLink != this &&
/*N*/ 						( !bSwapIn ||
/*N*/ 							GRAPHIC_DEFAULT == pGrfNd->GetGrfObj().GetType()))
/*N*/ 					{
/*?*/ 						pBLink->bIgnoreDataChanged = FALSE;
/*?*/ 						pBLink->DataChanged( rMimeType, rValue );
/*?*/ 						pBLink->bIgnoreDataChanged = TRUE;
/*?*/ 
/*?*/ 						pGrfNd->SetGrafikArrived( ((SwGrfNode*)pCntntNode)->
/*?*/ 													IsGrafikArrived() );
/*?*/ 
/*?*/ 						// Fly der Grafik anpassen !
/*?*/ 						if( !::SetGrfFlySize( aGrfSz, aFrmFmtSz, pGrfNd ) )
/*?*/ 							::lcl_CallModify( *pGrfNd, aMsgHint );
/*N*/ 					}
/*N*/ 					else if( pBLink == this &&
/*N*/ 							!::SetGrfFlySize( aGrfSz, aFrmFmtSz, pGrfNd ) )
/*N*/ 						// Fly der Grafik anpassen !
/*N*/ 						::lcl_CallModify( *pGrfNd, aMsgHint );
/*N*/ 				}
/*N*/ 			}
/*N*/ 
/*N*/ 			bInNotifyLinks = FALSE;
/*N*/ 		}
/*N*/ 		else
/*N*/ 		{
/*?*/ 			pCntntNode->Modify( &aMsgHint, &aMsgHint );
/*N*/ 		}
/*N*/ 
/*N*/ 
/*N*/ 		if( pESh )
/*N*/ 		{
/*N*/ 			const BOOL bEndActionByVirDev = pESh->IsEndActionByVirDev();
/*N*/ 			pESh->SetEndActionByVirDev( TRUE );
/*N*/ 			pESh->EndAllAction();
/*N*/ 			pESh->SetEndActionByVirDev( bEndActionByVirDev );
/*N*/ 		}
/*N*/ 		else if( pSh )
/*?*/ 			pSh->EndAction();
/*N*/ 
/*N*/ 		if( pSh && !bLockView )
/*N*/ 			pSh->LockView( FALSE );
/*N*/ 	}
/*N*/ }

/*N*/ FASTBOOL SwBaseLink::IsShowQuickDrawBmp() const
/*N*/ {
/*N*/ 	return pCntntNode && pCntntNode->IsGrfNode() &&
/*N*/ #ifdef NEW_GRFOBJ
/*N*/ 			((SwGrfNode*)pCntntNode)->HasMagicId()
/*N*/ #else
/*N*/ 			// wie kommt man an die Info dran, das eine Grafik im Cache steht?
/*N*/ 			FALSE
/*N*/ #endif
/*N*/ 		;
/*N*/ }


/*N*/ BOOL SetGrfFlySize( const Size& rGrfSz, const Size& rFrmSz, SwGrfNode* pGrfNd )
/*N*/ {
/*N*/ 	BOOL bRet = FALSE;
/*N*/ 	ViewShell *pSh;
/*N*/ 	CurrShell *pCurr = 0;
/*N*/ 	if ( pGrfNd->GetDoc()->GetEditShell( &pSh ) )
/*N*/ 		pCurr = new CurrShell( pSh );
/*N*/ 
/*N*/ 	Size aSz = pGrfNd->GetTwipSize();
/*N*/ 	if ( !(aSz.Width() && aSz.Height()) &&
/*N*/ 			rGrfSz.Width() && rGrfSz.Height() )
/*N*/ 	{
/*N*/ 		SwFrmFmt* pFmt;
/*N*/ 		if( pGrfNd->IsChgTwipSize() &&
/*N*/ 			0 != (pFmt = pGrfNd->GetFlyFmt()) )
/*N*/ 		{
/*?*/ 			Size aCalcSz( aSz );
/*?*/ 			if ( !aSz.Height() && aSz.Width() )
/*?*/ 				//passende Hoehe ausrechnen.
/*?*/ 				aCalcSz.Height() = rFrmSz.Height() *
/*?*/ 						aSz.Width() / rFrmSz.Width();
/*?*/ 			else if ( !aSz.Width() && aSz.Height() )
/*?*/ 				//passende Breite ausrechnen
/*?*/ 				aCalcSz.Width() = rFrmSz.Width() *
/*?*/ 						aSz.Height() / rFrmSz.Height();
/*?*/ 			else
/*?*/ 				//Hoehe und Breite uebernehmen
/*?*/ 				aCalcSz = rFrmSz;
/*?*/ 
/*?*/ 			const SvxBoxItem 	 &rBox = pFmt->GetBox();
/*?*/ 			aCalcSz.Width() += rBox.CalcLineSpace(BOX_LINE_LEFT) +
/*?*/ 							   rBox.CalcLineSpace(BOX_LINE_RIGHT);
/*?*/ 			aCalcSz.Height()+= rBox.CalcLineSpace(BOX_LINE_TOP) +
/*?*/ 							   rBox.CalcLineSpace(BOX_LINE_BOTTOM);
/*?*/ 			const SwFmtFrmSize& rOldAttr = pFmt->GetFrmSize();
/*?*/ 			if( rOldAttr.GetSize() != aCalcSz )
/*?*/ 			{
/*?*/ 				SwFmtFrmSize aAttr( rOldAttr  );
/*?*/ 				aAttr.SetSize( aCalcSz );
/*?*/ 				pFmt->SetAttr( aAttr );
/*?*/ 				bRet = TRUE;
/*?*/ 			}
/*?*/ 
/*?*/ 			if( !aSz.Width() )
/*?*/ 			{
/*?*/ 				// Wenn die Grafik in einer Tabelle verankert ist, muess
/*?*/ 				// die Tabellen-Spalten neu berechnet werden
/*?*/ 				const SwDoc *pDoc = pGrfNd->GetDoc();
/*?*/ 				const SwPosition* pAPos = pFmt->GetAnchor().GetCntntAnchor();
/*?*/ 				SwNode *pANd;
/*?*/ 				SwTableNode *pTblNd;
/*?*/ 				if( pAPos &&
/*?*/ 					0 != (pANd = pDoc->GetNodes()[pAPos->nNode]) &&
/*?*/ 					0 != (pTblNd = pANd->FindTableNode()) )
/*?*/ 				{
/*?*/ 					BOOL bLastGrf = !pTblNd->GetTable().DecGrfsThatResize();
/*?*/ 					SwHTMLTableLayout *pLayout =
/*?*/ 						pTblNd->GetTable().GetHTMLTableLayout();
/*?*/ 					if(	pLayout )
/*?*/ 					{
/*?*/ 						DBG_ASSERT(0, "STRIP"); //STRIP001 USHORT nBrowseWidth =
//STRIP001 /*?*/ 							pLayout->GetBrowseWidthByTable( *pDoc );
//STRIP001 /*?*/ 						if( nBrowseWidth )
//STRIP001 /*?*/ 							pLayout->Resize( nBrowseWidth, TRUE, TRUE,
//STRIP001 /*?*/ 											 bLastGrf ? HTMLTABLE_RESIZE_NOW
//STRIP001 /*?*/ 													  : 500 );
/*?*/ 					}
/*?*/ 				}
/*?*/ 			}
/*N*/ 		}
/*N*/ 
/*N*/ 		// SetTwipSize skaliert ggf. eine ImageMap neu und
/*N*/ 		// braucht dazu das Frame-Format
/*N*/ 		pGrfNd->SetTwipSize( rGrfSz );
/*N*/ 	}
/*N*/ 
/*N*/ 	delete pCurr;
/*N*/ 
/*N*/ 	return bRet;
/*N*/ }

/*N*/ FASTBOOL SwBaseLink::SwapIn( BOOL bWaitForData, BOOL bNativFormat )
/*N*/ {
/*N*/ 	bSwapIn = TRUE;
/*N*/ 
/*N*/ 	FASTBOOL bRes;
/*N*/ 
/*N*/ 	if( !GetObj() && ( bNativFormat || ( !IsSynchron() && bWaitForData ) ))
/*N*/ 	{
/*?*/ 		AddNextRef();
/*?*/ 		_GetRealObject();
/*?*/ 		ReleaseRef();
/*N*/ 	}
/*N*/ 
/*N*/ #if OSL_DEBUG_LEVEL > 1
/*N*/ 	{
/*N*/ 		String sGrfNm;
/*N*/ 		GetLinkManager()->GetDisplayNames( this, 0, &sGrfNm, 0, 0 );
/*N*/ 		int x = 0;
/*N*/ 	}
/*N*/ #endif
/*N*/ 
/*N*/ 	if( GetObj() )
/*N*/ 	{
/*N*/ 		String aMimeType( SotExchange::GetFormatMimeType( GetContentType() ));
/*N*/ 
/*N*/ //!! ??? what have we here to do ????
/*N*/ //!!		if( bNativFormat )
/*N*/ //!!			aData.SetAspect( aData.GetAspect() | ASPECT_ICON );
/*N*/ 
/*N*/ 		::com::sun::star::uno::Any aValue;
/*N*/ 		GetObj()->GetData( aValue, aMimeType, !IsSynchron() && bWaitForData );
/*N*/ 
/*N*/ 		if( bWaitForData && !GetObj() )
/*N*/ 		{
/*?*/ 			ASSERT( !this, "das SvxFileObject wurde in einem GetData geloescht!" );
/*?*/ 			bRes = FALSE;
/*N*/ 		}
/*N*/ 		else if( 0 != ( bRes = aValue.hasValue() ) )
/*N*/ 		{
/*N*/ 			//JP 14.04.99: Bug 64820 - das Flag muss beim SwapIn natuerlich
/*N*/ 			//				zurueckgesetzt werden. Die Daten sollen ja neu
/*N*/ 			//				uebernommen werden
/*N*/ 			bIgnoreDataChanged = FALSE;
/*N*/ 			DataChanged( aMimeType, aValue );
/*N*/ 		}
/*N*/ 	}
/*N*/ 	else if( !IsSynchron() && bWaitForData )
/*N*/ 	{
/*?*/ 		SetSynchron( TRUE );
/*?*/ 		bRes = Update();
/*?*/ 		SetSynchron( FALSE );
/*N*/ 	}
/*N*/ 	else
/*N*/ 		bRes = Update();
/*N*/ 
/*N*/ 	bSwapIn = FALSE;
/*N*/ 	return bRes;
/*N*/ }

//STRIP001 void SwBaseLink::Closed()
//STRIP001 {
//STRIP001 	if( pCntntNode && !pCntntNode->GetDoc()->IsInDtor() )
//STRIP001 	{
//STRIP001 		// wir heben die Verbindung auf
//STRIP001 		if( pCntntNode->IsGrfNode() )
//STRIP001 			((SwGrfNode*)pCntntNode)->ReleaseLink();
//STRIP001 	}
//STRIP001 	SvBaseLink::Closed();
//STRIP001 }

//STRIP001 const SwNode* SwBaseLink::GetAnchor() const
//STRIP001 {
//STRIP001 	SwFrmFmt* pFmt;
//STRIP001 	if( pCntntNode && 0 != ( pFmt = pCntntNode->GetFlyFmt()) )
//STRIP001 	{
//STRIP001 		const SwFmtAnchor& rAnchor = pFmt->GetAnchor();
//STRIP001 		const SwPosition* pAPos;
//STRIP001 		if( 0 != ( pAPos = rAnchor.GetCntntAnchor()) &&
//STRIP001 			( FLY_IN_CNTNT == rAnchor.GetAnchorId() ||
//STRIP001 			FLY_AUTO_CNTNT == rAnchor.GetAnchorId() ||
//STRIP001 			FLY_AT_FLY == rAnchor.GetAnchorId() ||
//STRIP001 			FLY_AT_CNTNT == rAnchor.GetAnchorId() ))
//STRIP001 				return &pAPos->nNode.GetNode();
//STRIP001 		return 0;
//STRIP001 	}
//STRIP001 
//STRIP001 	ASSERT( !this, "GetAnchor nicht ueberlagert" );
//STRIP001 	return 0;
//STRIP001 }

/*N*/ BOOL SwBaseLink::IsRecursion( const SwBaseLink* pChkLnk ) const
/*N*/ {
/*N*/ 	SwServerObjectRef aRef( (SwServerObject*)GetObj() );
/*N*/ 	if( aRef.Is() )
/*N*/ 	{
/*N*/ 		// es ist ein ServerObject, also frage nach allen darin
/*N*/ 		// befindlichen Links, ob wir darin enthalten sind. Ansonsten
/*N*/ 		// handelt es sich um eine Rekursion.
/*N*/ 		return aRef->IsLinkInServer( pChkLnk );
/*N*/ 	}
/*N*/ 	return FALSE;
/*N*/ }

/*N*/ BOOL SwBaseLink::IsInRange( ULONG, ULONG, xub_StrLen, xub_StrLen ) const
/*N*/ {
/*N*/ 	// Grafik oder OLE-Links nicht,
/*N*/ 	// Felder oder Sections haben eigene Ableitung!
/*N*/ 	return FALSE;
/*N*/ }




