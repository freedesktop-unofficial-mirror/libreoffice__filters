/*************************************************************************
 *
 *  $RCSfile: sw_ndgrf.cxx,v $
 *
 *  $Revision: 1.4 $
 *
 *  last change: $Author: hr $ $Date: 2004-08-03 17:30:05 $
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
#ifndef _HINTIDS_HXX
#include <hintids.hxx>
#endif

#ifndef _SV_SALBTYPE_HXX
#include <vcl/salbtype.hxx>             // FRound
#endif
#ifndef _URLOBJ_HXX //autogen
#include <tools/urlobj.hxx>
#endif
#ifndef _UNDO_HXX //autogen
#include <svtools/undo.hxx>
#endif
#ifndef SVTOOLS_FSTATHELPER_HXX
#include <svtools/fstathelper.hxx>
#endif
#ifndef _IMAP_HXX //autogen
#include <svtools/imap.hxx>
#endif
#ifndef _FILTER_HXX //autogen
#include <svtools/filter.hxx>
#endif
#ifndef _SVSTOR_HXX //autogen
#include <so3/svstor.hxx>
#endif
#ifndef _SFXDOCINF_HXX //autogen
#include <bf_sfx2/docinf.hxx>
#endif
#ifndef _SVXLINKMGR_HXX
#include <bf_svx/linkmgr.hxx>
#endif
#ifndef _SVX_BOXITEM_HXX //autogen
#include <bf_svx/boxitem.hxx>
#endif
#ifndef _SVX_IMPGRF_HXX //autogen
#include <bf_svx/impgrf.hxx>
#endif
#ifndef _SOT_FORMATS_HXX
#include <sot/formats.hxx>
#endif

#ifndef _FMTFSIZE_HXX
#include <fmtfsize.hxx>
#endif
#ifndef _FMTURL_HXX
#include <fmturl.hxx>
#endif
#ifndef _FRMFMT_HXX
#include <frmfmt.hxx>
#endif

#ifndef _HORIORNT_HXX
#include <horiornt.hxx>
#endif

#ifndef _DOC_HXX
#include <doc.hxx>
#endif
#ifndef _FRMATR_HXX
#include <frmatr.hxx>
#endif
#ifndef _GRFATR_HXX
#include <grfatr.hxx>
#endif
#ifndef _SWTYPES_HXX
#include <swtypes.hxx>
#endif

#ifndef _ERRHDL_HXX
#include <errhdl.hxx>
#endif

#ifndef _NDGRF_HXX
#include <ndgrf.hxx>
#endif
#ifndef _FMTCOL_HXX
#include <fmtcol.hxx>
#endif
#ifndef _HINTS_HXX
#include <hints.hxx>
#endif
#ifndef _SW3IO_HXX
#include <sw3io.hxx>
#endif
#ifndef _SWBASLNK_HXX
#include <swbaslnk.hxx>
#endif
#ifndef _PAGEFRM_HXX
#include <pagefrm.hxx>
#endif
#ifndef _EDITSH_HXX
#include <editsh.hxx>
#endif
#ifndef _PAM_HXX
#include <pam.hxx>
#endif
namespace binfilter {

// --------------------
// SwGrfNode
// --------------------
/*N*/ SwGrfNode::SwGrfNode( const SwNodeIndex & rWhere,
/*N*/ 				  const String& rGrfName, const String& rFltName,
/*N*/ 				  const Graphic* pGraphic,
/*N*/ 				  SwGrfFmtColl *pGrfColl,
/*N*/ 				  SwAttrSet* pAutoAttr )
/*N*/ 	: SwNoTxtNode( rWhere, ND_GRFNODE, pGrfColl, pAutoAttr )
/*N*/ {
/*N*/ 	aGrfObj.SetSwapStreamHdl( LINK( this, SwGrfNode, SwapGraphic ) );
/*N*/ 	bInSwapIn = bChgTwipSize = bChgTwipSizeFromPixel = bLoadLowResGrf = 
/*N*/ 		bFrameInPaint = bScaleImageMap = FALSE;
/*N*/ 	bGrafikArrived = TRUE;
/*N*/ 	ReRead( rGrfName, rFltName, pGraphic, 0, FALSE );
/*N*/ }

/*N*/ SwGrfNode::SwGrfNode( const SwNodeIndex & rWhere,
/*N*/ 				  		const GraphicObject& rGrfObj,
/*N*/ 				  		SwGrfFmtColl *pGrfColl, SwAttrSet* pAutoAttr )
/*N*/ 	: SwNoTxtNode( rWhere, ND_GRFNODE, pGrfColl, pAutoAttr )
/*N*/ {
/*N*/ 	aGrfObj = rGrfObj;
/*N*/ 	aGrfObj.SetSwapStreamHdl( LINK( this, SwGrfNode, SwapGraphic ) );
/*N*/ 	if( rGrfObj.HasUserData() && rGrfObj.IsSwappedOut() )
/*?*/ 		aGrfObj.SetSwapState();
/*N*/ 	bInSwapIn = bChgTwipSize = bChgTwipSizeFromPixel= bLoadLowResGrf = 
/*N*/ 		bFrameInPaint = bScaleImageMap = FALSE;
/*N*/ 	bGrafikArrived = TRUE;
/*N*/ }

// Konstruktor fuer den SW/G-Reader. Dieser ctor wird verwendet,
// wenn eine gelinkte Grafik gelesen wird. Sie liest diese NICHT ein.


/*N*/ SwGrfNode::SwGrfNode( const SwNodeIndex & rWhere,
/*N*/ 				  const String& rGrfName, const String& rFltName,
/*N*/ 				  SwGrfFmtColl *pGrfColl,
/*N*/ 				  SwAttrSet* pAutoAttr )
/*N*/ 	: SwNoTxtNode( rWhere, ND_GRFNODE, pGrfColl, pAutoAttr )
/*N*/ {
/*N*/ 	aGrfObj.SetSwapStreamHdl( LINK( this, SwGrfNode, SwapGraphic ) );
/*N*/ 
/*N*/ 	Graphic aGrf; aGrf.SetDefaultType();
/*N*/ 	aGrfObj.SetGraphic( aGrf, rGrfName );
/*N*/ 
/*N*/ 	bInSwapIn = bChgTwipSize = bChgTwipSizeFromPixel = bLoadLowResGrf = 
/*N*/ 		bFrameInPaint = bScaleImageMap = FALSE;
/*N*/ 	bGrafikArrived = TRUE;
/*N*/ 
/*N*/ 	InsertLink( rGrfName, rFltName );
/*N*/ 	if( IsLinkedFile() )
/*N*/ 	{
/*N*/ 		INetURLObject aUrl( rGrfName );
/*N*/ 		if( INET_PROT_FILE == aUrl.GetProtocol() &&
/*N*/ 			FStatHelper::IsDocument( aUrl.GetMainURL( INetURLObject::NO_DECODE ) ))
/*N*/ 		{
/*N*/ 			// File vorhanden, Verbindung herstellen ohne ein Update
/*N*/ 			((SwBaseLink*)&refLink)->Connect();
/*N*/ 		}
/*N*/ 	}
/*N*/ }


// erneutes Einlesen, falls Graphic nicht Ok ist. Die
// aktuelle wird durch die neue ersetzt.

/*N*/ BOOL SwGrfNode::ReRead( const String& rGrfName, const String& rFltName,
/*N*/ 						const Graphic* pGraphic, const GraphicObject* pGrfObj,
/*N*/ 						BOOL bNewGrf )
/*N*/ {
/*N*/ 	BOOL bReadGrf = FALSE, bSetTwipSize = TRUE;
/*N*/ 
/*N*/ 	ASSERT( pGraphic || pGrfObj || rGrfName.Len(),
/*N*/ 			"GraphicNode without a name, Graphic or GraphicObject" );
/*N*/ 
/*N*/ 	// ReadRead mit Namen
/*N*/ 	if( refLink.Is() )
/*N*/ 	{
/*?*/ 		ASSERT( !bInSwapIn, "ReRead: stehe noch im SwapIn" );
/*?*/ 		if( rGrfName.Len() )
/*?*/ 		{
/*?*/ 			// Besonderheit: steht im FltNamen DDE, handelt es sich um eine
/*?*/ 			//					DDE-gelinkte Grafik
/*?*/ 			String sCmd( rGrfName );
/*?*/ 			if( rFltName.Len() )
/*?*/ 			{
/*?*/ 				USHORT nNewType;
/*?*/ 				if( rFltName.EqualsAscii( "DDE" ))
/*?*/ 					nNewType = OBJECT_CLIENT_DDE;
/*?*/ 				else
/*?*/ 				{
/*?*/                     ::so3::MakeLnkName( sCmd, 0, rGrfName, aEmptyStr, &rFltName );
/*?*/ 					nNewType = OBJECT_CLIENT_GRF;
/*?*/ 				}
/*?*/ 
/*?*/ 				if( nNewType != refLink->GetObjType() )
/*?*/ 				{
/*?*/ 					refLink->Disconnect();
/*?*/ 					((SwBaseLink*)&refLink)->SetObjType( nNewType );
/*?*/ 				}
/*?*/ 			}
/*?*/ 
/*?*/ 			refLink->SetLinkSourceName( sCmd );
/*?*/ 		}
/*?*/ 		else		// kein Name mehr, Link aufheben
/*?*/ 		{
/*?*/ 			GetDoc()->GetLinkManager().Remove( refLink );
/*?*/ 			refLink.Clear();
/*?*/ 		}
/*?*/ 
/*?*/ 		if( pGraphic )
/*?*/ 		{
/*?*/ 			aGrfObj.SetGraphic( *pGraphic, rGrfName );
/*?*/ 			bReadGrf = TRUE;
/*?*/ 		}
/*?*/ 		else if( pGrfObj )
/*?*/ 		{
/*?*/ 			aGrfObj = *pGrfObj;
/*?*/ 			if( pGrfObj->HasUserData() && pGrfObj->IsSwappedOut() )
/*?*/ 				aGrfObj.SetSwapState();
/*?*/ 			aGrfObj.SetLink( rGrfName );
/*?*/ 			bReadGrf = TRUE;
/*?*/ 		}
/*?*/ 		else
/*?*/ 		{
/*?*/ 			// MIB 25.02.97: Daten der alten Grafik zuruecksetzen, damit
/*?*/ 			// die korrekte Ersatz-Darstellung erscheint, wenn die
/*?*/ 			// der neue Link nicht geladen werden konnte.
/*?*/ 			Graphic aGrf; aGrf.SetDefaultType();
/*?*/ 			aGrfObj.SetGraphic( aGrf, rGrfName );
/*?*/ 
/*?*/ 			if( refLink.Is() )
/*?*/ 			{
/*?*/ 				if( GetFrm() )
/*?*/ 				{
/*?*/ 					SwMsgPoolItem aMsgHint( RES_GRF_REREAD_AND_INCACHE );
/*?*/ 					Modify( &aMsgHint, &aMsgHint );
/*?*/ 				}
/*?*/ 				else
/*?*/ 					((SwBaseLink*)&refLink)->SwapIn();
/*?*/ 			}
/*?*/ 			bSetTwipSize = FALSE;
/*?*/ 		}
/*N*/ 	}
/*N*/ 	else if( pGraphic && !rGrfName.Len() )
/*N*/ 	{
/*N*/ 		// MIB 27.02.2001: Old stream must be deleted before the new one is set.
/*N*/ 		if( HasStreamName() )
                {DBG_BF_ASSERT(0, "STRIP");} //STRIP001 /*?*/ 			DelStreamName();
/*N*/ 
/*N*/ 		aGrfObj.SetGraphic( *pGraphic );
/*N*/ 		bReadGrf = TRUE;
/*N*/ 	}
/*N*/ 	else if( pGrfObj && !rGrfName.Len() )
/*N*/ 	{
/*N*/ 		// MIB 27.02.2001: Old stream must be deleted before the new one is set.
/*?*/ 		if( HasStreamName() )
                {DBG_BF_ASSERT(0, "STRIP");} //STRIP001 /*?*/ 			DelStreamName();
/*?*/ 
/*?*/ 		aGrfObj = *pGrfObj;
/*?*/ 		if( pGrfObj->HasUserData() && pGrfObj->IsSwappedOut() )
/*?*/ 			aGrfObj.SetSwapState();
/*?*/ 		bReadGrf = TRUE;
/*N*/ 	}
/*N*/ 		// Import einer Grafik:
/*N*/ 		// Ist die Grafik bereits geladen?
/*N*/ 	else if( !bNewGrf && GRAPHIC_NONE != aGrfObj.GetType() )
/*N*/ 		return TRUE;
/*N*/ 
/*N*/ 	else
/*N*/ 	{
/*N*/ 		if( HasStreamName() )
                {DBG_BF_ASSERT(0, "STRIP");} //STRIP001 /*?*/ 			DelStreamName();
/*N*/ 
/*N*/ 		// einen neuen Grafik-Link anlegen
/*N*/ 		InsertLink( rGrfName, rFltName );
/*N*/ 
/*N*/ 		if( GetNodes().IsDocNodes() )
/*N*/ 		{
/*N*/ 			if( pGraphic )
/*N*/ 			{
/*N*/ 				aGrfObj.SetGraphic( *pGraphic, rGrfName );
/*N*/ 				bReadGrf = TRUE;
/*N*/ 				// Verbindung herstellen ohne ein Update; Grafik haben wir!
/*N*/ 				((SwBaseLink*)&refLink)->Connect();
/*N*/ 			}
/*N*/ 			else if( pGrfObj )
/*N*/ 			{
/*?*/ 				aGrfObj = *pGrfObj;
/*?*/ 				aGrfObj.SetLink( rGrfName );
/*?*/ 				bReadGrf = TRUE;
/*?*/ 				// Verbindung herstellen ohne ein Update; Grafik haben wir!
/*?*/ 				((SwBaseLink*)&refLink)->Connect();
/*N*/ 			}
/*N*/ 			else
/*N*/ 			{
/*N*/ 				// MIB 25.02.97: Daten der alten Grafik zuruecksetzen, damit
/*N*/ 				// die korrekte Ersatz-Darstellung erscheint, wenn die
/*N*/ 				// der neue Kink nicht geladen werden konnte.
/*N*/ 				Graphic aGrf; aGrf.SetDefaultType();
/*N*/ 				aGrfObj.SetGraphic( aGrf, rGrfName );
/*N*/ 				((SwBaseLink*)&refLink)->SwapIn();
/*N*/ 			}
/*N*/ 		}
/*N*/ 	}
/*N*/ 
/*N*/ 	// Bug 39281: Size nicht sofort loeschen - Events auf ImageMaps
/*N*/ 	//			  sollten nicht beim Austauschen nicht ins "leere greifen"
/*N*/ 	if( bSetTwipSize )
/*N*/ 		SetTwipSize( ::binfilter::GetGraphicSizeTwip( aGrfObj.GetGraphic(), 0 ) );
/*N*/ 
/*N*/ 	// erzeuge noch einen Update auf die Frames
/*N*/ 	if( bReadGrf && bNewGrf )
/*N*/ 	{
/*?*/ 		SwMsgPoolItem aMsgHint( RES_UPDATE_ATTR );
/*?*/ 		Modify( &aMsgHint, &aMsgHint );
/*N*/ 	}
/*N*/ 
/*N*/ 	return bReadGrf;
/*N*/ }


/*N*/ SwGrfNode::~SwGrfNode()
/*N*/ {
/*N*/ 	SwDoc* pDoc = GetDoc();
/*N*/ 	if( refLink.Is() )
/*N*/ 	{
/*N*/ 		ASSERT( !bInSwapIn, "DTOR: stehe noch im SwapIn" );
/*N*/ 		pDoc->GetLinkManager().Remove( refLink );
/*N*/ 		refLink->Disconnect();
/*N*/ 	}
/*N*/ 	else
/*N*/ 	{
/*N*/ 		if( !pDoc->IsInDtor() && HasStreamName() )
                {DBG_BF_ASSERT(0, "STRIP");} //STRIP001 /*?*/ 			DelStreamName();
/*N*/ 	}
/*N*/ 	//#39289# Die Frames muessen hier bereits geloescht weil der DTor der
/*N*/ 	//Frms die Grafik noch fuer StopAnimation braucht.
/*N*/ 	if( GetDepends() )
/*?*/ 		DelFrms();
/*N*/ }


/*N*/ SwCntntNode *SwGrfNode::SplitNode( const SwPosition &rPos )
/*N*/ {
/*?*/ 	return this;
/*N*/ }


/*N*/ SwGrfNode * SwNodes::MakeGrfNode( const SwNodeIndex & rWhere,
/*N*/ 								const String& rGrfName,
/*N*/ 								const String& rFltName,
/*N*/ 								const Graphic* pGraphic,
/*N*/ 								SwGrfFmtColl* pGrfColl,
/*N*/ 								SwAttrSet* pAutoAttr,
/*N*/ 								BOOL bDelayed )
/*N*/ {
/*N*/ 	ASSERT( pGrfColl, "MakeGrfNode: Formatpointer ist 0." );
/*N*/ 	SwGrfNode *pNode;
/*N*/ 	// Delayed erzeugen nur aus dem SW/G-Reader
/*N*/ 	if( bDelayed )
/*N*/ 		pNode = new SwGrfNode( rWhere, rGrfName,
/*N*/ 								rFltName, pGrfColl, pAutoAttr );
/*N*/ 	else
/*N*/ 		pNode = new SwGrfNode( rWhere, rGrfName,
/*N*/ 								rFltName, pGraphic, pGrfColl, pAutoAttr );
/*N*/ 	return pNode;
/*N*/ }

/*N*/ SwGrfNode * SwNodes::MakeGrfNode( const SwNodeIndex & rWhere,
/*N*/ 								const GraphicObject& rGrfObj,
/*N*/ 								SwGrfFmtColl* pGrfColl,
/*N*/ 								SwAttrSet* pAutoAttr )
/*N*/ {
/*N*/ 	ASSERT( pGrfColl, "MakeGrfNode: Formatpointer ist 0." );
/*N*/ 	return new SwGrfNode( rWhere, rGrfObj, pGrfColl, pAutoAttr );
/*N*/ }


/*N*/ Size SwGrfNode::GetTwipSize() const
/*N*/ {
/*N*/ 	return nGrfSize;
/*N*/ }



//STRIP001 BOOL SwGrfNode::ImportGraphic( SvStream& rStrm )
//STRIP001 {
//STRIP001 	Graphic aGraphic;
//STRIP001 	if( !GetGrfFilter()->ImportGraphic( aGraphic, String(), rStrm ) )
//STRIP001 	{
//STRIP001 		const String aUserData( aGrfObj.GetUserData() );
//STRIP001 
//STRIP001 		aGrfObj.SetGraphic( aGraphic );
//STRIP001 		aGrfObj.SetUserData( aUserData );
//STRIP001 		return TRUE;
//STRIP001 	}
//STRIP001 
//STRIP001 	return FALSE;
//STRIP001 }

// Returnwert:
// -1 : ReRead erfolgreich
//  0 : nicht geladen
//  1 : Einlesen erfolgreich

//STRIP001 short SwGrfNode::SwapIn( BOOL bWaitForData )
//STRIP001 {
//STRIP001 	if( bInSwapIn )					// nicht rekuriv!!
//STRIP001 		return !aGrfObj.IsSwappedOut();
//STRIP001 
//STRIP001 	short nRet = 0;
//STRIP001 	bInSwapIn = TRUE;
//STRIP001 	SwBaseLink* pLink = (SwBaseLink*)(::so3::SvBaseLink*) refLink;
//STRIP001 	if( pLink )
//STRIP001 	{
//STRIP001 		if( GRAPHIC_NONE == aGrfObj.GetType() ||
//STRIP001 			GRAPHIC_DEFAULT == aGrfObj.GetType() )
//STRIP001 		{
//STRIP001 			// noch nicht geladener Link
//STRIP001 			if( pLink->SwapIn( bWaitForData ) )
//STRIP001 				nRet = -1;
//STRIP001 			else if( GRAPHIC_DEFAULT == aGrfObj.GetType() )
//STRIP001 			{
//STRIP001 				// keine default Bitmap mehr, also neu Painten!
//STRIP001 				aGrfObj.SetGraphic( Graphic() );
//STRIP001 				SwMsgPoolItem aMsgHint( RES_GRAPHIC_PIECE_ARRIVED );
//STRIP001 				Modify( &aMsgHint, &aMsgHint );
//STRIP001 			}
//STRIP001 		}
//STRIP001 		else if( aGrfObj.IsSwappedOut() )
//STRIP001 			// nachzuladender Link
//STRIP001 			nRet = pLink->SwapIn( bWaitForData ) ? 1 : 0;
//STRIP001 		else
//STRIP001 			nRet = 1;
//STRIP001 	}
//STRIP001 	else if( aGrfObj.IsSwappedOut() )
//STRIP001 	{
//STRIP001 		// Die Grafik ist im Storage oder im TempFile drin
//STRIP001 		if( !HasStreamName() )
//STRIP001 			nRet = (short)aGrfObj.SwapIn();
//STRIP001 		else
//STRIP001 		{
//STRIP001 			SvStorageRef refRoot = GetDoc()->GetDocStorage();
//STRIP001 			ASSERT( refRoot.Is(), "Kein Storage am Doc" );
//STRIP001 			if( refRoot.Is() )
//STRIP001 			{
//STRIP001 				String aStrmName, aPicStgName;
//STRIP001 				BOOL bGraphic = GetStreamStorageNames( aStrmName, aPicStgName );
//STRIP001 				SvStorageRef refPics = aPicStgName.Len()
//STRIP001 				   	? refRoot->OpenStorage( aPicStgName,
//STRIP001 						STREAM_READ | STREAM_SHARE_DENYWRITE )
//STRIP001 					: &refRoot;
//STRIP001 				if( refPics->GetError() == SVSTREAM_OK )
//STRIP001 				{
//STRIP001 					SvStorageStreamRef refStrm =
//STRIP001 						refPics->OpenStream( aStrmName,
//STRIP001 						STREAM_READ | STREAM_SHARE_DENYWRITE );
//STRIP001 					if( refStrm->GetError() == SVSTREAM_OK )
//STRIP001 					{
//STRIP001 						refStrm->SetVersion( refRoot->GetVersion() );
//STRIP001 						if( bGraphic ? aGrfObj.SwapIn( refStrm )
//STRIP001 									 : ImportGraphic( *refStrm ) )
//STRIP001 							nRet = 1;
//STRIP001 					}
//STRIP001 				}
//STRIP001 			}
//STRIP001 		}
//STRIP001 		if( 1 == nRet )
//STRIP001 		{
//STRIP001 			SwMsgPoolItem aMsg( RES_GRAPHIC_SWAPIN );
//STRIP001 			SwCntntNode::Modify( &aMsg, &aMsg );
//STRIP001 		}
//STRIP001 	}
//STRIP001 	else
//STRIP001 		nRet = 1;
//STRIP001 	DBG_ASSERTWARNING( nRet, "Grafik kann nicht eingeswapt werden" );
//STRIP001 
//STRIP001 	if( nRet )
//STRIP001 	{
//STRIP001 		if( !nGrfSize.Width() && !nGrfSize.Height() )
//STRIP001 			SetTwipSize( ::GetGraphicSizeTwip( aGrfObj.GetGraphic(), 0 ) );
//STRIP001 	}
//STRIP001 	bInSwapIn = FALSE;
//STRIP001 	return nRet;
//STRIP001 }


//STRIP001 short SwGrfNode::SwapOut()
//STRIP001 {
//STRIP001 	if( aGrfObj.GetType() != GRAPHIC_DEFAULT &&
//STRIP001 		aGrfObj.GetType() != GRAPHIC_NONE &&
//STRIP001 		!aGrfObj.IsSwappedOut() && !bInSwapIn )
//STRIP001 	{
//STRIP001 		if( !refLink.Is() )
//STRIP001 		{
//STRIP001 			// Das Swapping brauchen wir nur fuer Embedded Pictures
//STRIP001 			// Die Grafik wird in eine TempFile geschrieben, wenn
//STRIP001 			// sie frisch eingefuegt war, d.h. wenn es noch keinen
//STRIP001 			// Streamnamen im Storage gibt.
//STRIP001 			if( !HasStreamName() )
//STRIP001 				if( !aGrfObj.SwapOut() )
//STRIP001 					return 0;
//STRIP001 		}
//STRIP001 		// Geschriebene Grafiken oder Links werden jetzt weggeschmissen
//STRIP001 		return (short) aGrfObj.SwapOut( NULL );
//STRIP001 	}
//STRIP001 	return 1;
//STRIP001 }

// Wird nach einem SaveAs aufgerufen und setzt die StreamNamen um


/*N*/ void SwGrfNode::SaveCompleted( BOOL bClear )
/*N*/ {
/*N*/ 	if( aNewStrmName.Len() )
/*N*/ 	{
/*N*/ 		if( !bClear )		// der Name wird zum aktuellen
/*N*/ 			SetStreamName( aNewStrmName );
/*N*/ 		aNewStrmName.Erase();
/*N*/ 	}
/*N*/ }


// Falls die Grafik noch nicht im Doc-Storage existiert,
// wird sie neu geschrieben; falls sie bereits drin ist,
// wird nicht geschrieben. Wenn der Storage nicht dem
// Doc-Storage entspricht, wird, falls aNewStrmName nicht
// besetzt ist, in diesem Storage unter dem angegebenen
// Streamnamen abgelegt (SaveAs). nach einem SaveAs wird
// vom SW3-I/O-System noch SaveCompleted() aufgerufen,
// da nun der Doc-Storage dem neuen Storage entspricht.
// MIB 02/28/2001: This method is called only to store graphics
// in the 3.1 to 5.0 formats. For the 6.0 format, graphics
// are exported using the SvXMLGraphicObjectHelper class.


/*N*/ BOOL SwGrfNode::StoreGraphics( SvStorage* pRoot )
/*N*/ {
/*N*/ 	if( !refLink.Is() )
/*N*/ 	{
/*N*/ 		BOOL bGraphic = TRUE; // Does the graphic stream (if it exists)
/*N*/ 							  // contain a streamed graphic (TRUE) or the
/*N*/ 							  // raw image data only (FALSE)
/*N*/ 		String aSrcStrmName, aSrcPicStgName;
/*N*/ 		if( HasStreamName() )
/*N*/ 			bGraphic = GetStreamStorageNames( aSrcStrmName, aSrcPicStgName );
/*N*/ 		SvStorage* pDocStg = GetDoc()->GetDocStorage();
/*N*/ 		if( !pRoot )
/*N*/ 			pRoot = pDocStg;
/*N*/ 		ASSERT( SOFFICE_FILEFORMAT_60 > pRoot->GetVersion(),
/*N*/ 				"SwGrfNode::StoreGraphic called for 6.0+ file format" );
/*N*/ 
/*N*/ 		String aDstPicStgName(
/*N*/ 				RTL_CONSTASCII_STRINGPARAM( "EmbeddedPictures" ) );
/*N*/ 		String aDstStrmName( aSrcStrmName );
/*N*/ 		if( pRoot != pDocStg || !bGraphic )
/*N*/ 		{
/*N*/ 			// If the stream does not contain a streamed graphic object,
/*N*/ 			// the graphic has to be stored again.
/*N*/ 			ASSERT( pRoot != pDocStg || aSrcStrmName.Len(),
/*N*/ 					"raw image data stream but no stream name" );
/*N*/ 			// Neuer Storage. Wenn die Grafik im DocStg drin ist,
/*N*/ 			// kann sie bequem per CopyTo() kopiert werden.
/*N*/ 			if( aSrcStrmName.Len() )
/*N*/ 			{
/*N*/ 				SvStorageRef refSrcPics = aSrcPicStgName.Len()
/*N*/ 					? pDocStg->OpenStorage( aSrcPicStgName,
/*N*/ 						STREAM_READ | STREAM_SHARE_DENYWRITE )
/*N*/ 					: pDocStg;
/*N*/ 
/*N*/ 				SvStorageStreamRef refStrm;
/*N*/ 
/*N*/ 				BOOL bWriteNew = pDocStg->GetVersion() != pRoot->GetVersion() ||
/*N*/ 								 !bGraphic;
/*N*/ 				if( !bWriteNew &&
/*N*/ 					SOFFICE_FILEFORMAT_40 <= pRoot->GetVersion() )
/*N*/ 				{
/*N*/ 					refStrm = refSrcPics->OpenStream( aSrcStrmName,
/*N*/ 									STREAM_READ | STREAM_SHARE_DENYWRITE );
/*N*/ 					if( SVSTREAM_OK == refStrm->GetError() )
/*N*/ 					{
/*N*/ 						// JP 21.06.98: pruefe ob der CompressMode uebereinstimmt
/*N*/ 						USHORT nCmprsMode =
/*N*/ 								Graphic::GetGraphicsCompressMode(*refStrm ) &
/*N*/ 								~(COMPRESSMODE_ZBITMAP|COMPRESSMODE_NATIVE );
/*N*/ 						USHORT nNewCmprsMode = 0;
/*N*/ 						if( GRAPHIC_BITMAP == aGrfObj.GetType() &&
/*N*/ 							GetDoc()->GetInfo()->IsSaveGraphicsCompressed() )
/*N*/ 							nNewCmprsMode |= COMPRESSMODE_ZBITMAP;
/*N*/ 						if( SOFFICE_FILEFORMAT_40 < pRoot->GetVersion() &&
/*N*/ 							GetDoc()->GetInfo()->IsSaveOriginalGraphics() )
/*N*/ 							nNewCmprsMode |= COMPRESSMODE_NATIVE;
/*N*/ 
/*N*/ 						if( nCmprsMode != nNewCmprsMode )
/*N*/ 						{
/*N*/ 							// der Kompressedmode stimmt nicht, also muss
/*N*/ 							// ggfs. die Grafik reingeswappt und ueber den
/*N*/ 							// unteren Teil neu geschrieben werden.
/*N*/ 							bWriteNew = TRUE;
/*N*/ 							refStrm->Seek( STREAM_SEEK_TO_BEGIN );
/*N*/ 						}
/*N*/ 					}
/*N*/ 				}
/*N*/ 
/*N*/ 				if( bWriteNew )
/*N*/ 				{
/*N*/ 					if( aGrfObj.IsSwappedOut() &&
/*N*/ 						SVSTREAM_OK == refSrcPics->GetError() )
/*N*/ 					{
/*N*/ 						if( !refStrm.Is() )
/*?*/ 							refStrm = refSrcPics->OpenStream( aSrcStrmName,
/*?*/ 									STREAM_READ | STREAM_SHARE_DENYWRITE );
/*N*/ 						if( SVSTREAM_OK == refStrm->GetError() )
/*N*/ 						{
/*N*/ 							refStrm->SetVersion( pDocStg->GetVersion() );
/*N*/ 							if( !(bGraphic ? aGrfObj.SwapIn( refStrm )
/*N*/ 							 			   : ImportGraphic( *refStrm ) ) )
/*N*/ 								return FALSE;
/*N*/ 						}
/*N*/ 					}
/*N*/ 					// If the graphic is restored within the same storage,
/*N*/ 					// its storage has to be removed.
/*N*/ 					if( pRoot == pDocStg )
/*N*/ 					{
                            {DBG_BF_ASSERT(0, "STRIP");} //STRIP001 /*?*/ 						refStrm.Clear();
//STRIP001 /*?*/ 						DelStreamName();
/*N*/ 					}
/*N*/ 					aDstStrmName.Erase();
/*N*/ 				}
/*N*/ 				else
/*N*/ 				{
/*N*/ 					SvStorageRef refDstPics =
/*N*/ 						pRoot->OpenStorage( aDstPicStgName,
/*N*/ 							STREAM_READWRITE | STREAM_SHARE_DENYALL );
/*N*/ 					if( refDstPics->IsContained( aDstStrmName ) )
/*N*/ 						// nur neu erzeugen, wenn Name schon vorhanden ist!
/*?*/ 						aDstStrmName = Sw3Io::UniqueName( refDstPics, "Pic" );
/*N*/ 
/*N*/ 					if( refSrcPics->CopyTo( aSrcStrmName, refDstPics,
/*N*/ 											aDstStrmName )
/*N*/ 						&& refDstPics->Commit() )
/*N*/ 						aNewStrmName = aDstStrmName;
/*N*/ 					else
/*N*/ 						return FALSE;
/*N*/ 				}
/*N*/ 			}
/*N*/ 		}
/*N*/ 
/*N*/ 		if( !aDstStrmName.Len() )
/*N*/ 		{
/*N*/ 			ASSERT( pRoot, "Kein Storage gegeben" );
/*N*/ 			if( pRoot )
/*N*/ 			{
/*N*/ 				SvStorageRef refPics =
/*N*/ 					pRoot->OpenStorage( aDstPicStgName,
/*N*/ 						STREAM_READWRITE | STREAM_SHARE_DENYALL );
/*N*/ 				if( SVSTREAM_OK == refPics->GetError() )
/*N*/ 				{
/*N*/ 					aDstStrmName = Sw3Io::UniqueName( refPics, "Pic" );
/*N*/ 					SvStorageStreamRef refStrm =
/*N*/ 						refPics->OpenStream( aDstStrmName,
/*N*/ 						STREAM_READWRITE | STREAM_SHARE_DENYALL );
/*N*/ 					if( SVSTREAM_OK == refStrm->GetError() )
/*N*/ 					{
/*N*/ 						// HACK bis die Grafik als Portable markiert
/*N*/ 						// werden kann!!!
/*N*/ 						// Die Grafik kann in einer TempFile sein!
/*N*/ 						FASTBOOL bIsSwapOut = aGrfObj.IsSwappedOut();
/*N*/ 						if( bIsSwapOut && !aGrfObj.SwapIn() )
/*N*/ 							return FALSE;
/*N*/ 
/*N*/ 						refStrm->SetVersion( pRoot->GetVersion() );
/*N*/ 
/*N*/ 						//JP 04.05.98: laut ChangesMail vom KA und Bug 49617
/*N*/ 						//JP 21.06.98: laut ChangesMail vom KA, natives Save
/*N*/ 						USHORT nComprMode = refStrm->GetCompressMode();
/*N*/ 						if( SOFFICE_FILEFORMAT_40 <= refStrm->GetVersion() &&
/*N*/ 							GRAPHIC_BITMAP == aGrfObj.GetType() &&
/*N*/ 							GetDoc()->GetInfo()->IsSaveGraphicsCompressed() )
/*N*/ 							nComprMode |= COMPRESSMODE_ZBITMAP;
/*N*/ 						else
/*N*/ 							nComprMode &= ~COMPRESSMODE_ZBITMAP;
/*N*/ 
/*N*/ 						//JP 21.06.98: laut ChangesMail vom KA, natives Save
/*N*/ 						if( SOFFICE_FILEFORMAT_40 < refStrm->GetVersion() &&
/*N*/ 							GetDoc()->GetInfo()->IsSaveOriginalGraphics() )
/*N*/ 							nComprMode |= COMPRESSMODE_NATIVE;
/*N*/ 						else
/*N*/ 							nComprMode &= ~COMPRESSMODE_NATIVE;
/*N*/ 						refStrm->SetCompressMode( nComprMode );
/*N*/ 
/*N*/ 						BOOL bRes = FALSE;
/*N*/ 						if( pRoot == pDocStg )
/*N*/ 						{
/*?*/ 							if( aGrfObj.SwapOut( refStrm ) &&
/*?*/ 								( refStrm->Commit() | refPics->Commit()
/*?*/ 								  /*| pRoot->Commit()*/ ))
/*?*/ 							{
/*?*/ 								SetStreamName( aDstStrmName );
/*?*/ 								bRes = TRUE;
/*?*/ 							}
/*N*/ 						}
/*N*/ 						else if( ((Graphic&)aGrfObj.GetGraphic()).
/*N*/ 												WriteEmbedded( *refStrm )
/*N*/ 								&& ( refStrm->Commit() | refPics->Commit()
/*N*/ 								  /*| pRoot->Commit()*/ ))
/*N*/ 						{
/*N*/ 							if( bIsSwapOut )
/*?*/ 								aGrfObj.SwapOut();
/*N*/ 							aNewStrmName = aDstStrmName;
/*N*/ 							bRes = TRUE;
/*N*/ 						}
/*N*/ 						return bRes;
/*N*/ 					}
/*N*/ 				}
/*N*/ 			}
/*N*/ 			// Da fehlte doch was?
/*N*/ 			return FALSE;
/*N*/ 		}
/*N*/ 	}
/*N*/ 	// Schon drin im Storage oder Linked
/*N*/ 	return TRUE;
/*N*/ }


/*N*/ BOOL SwGrfNode::GetFileFilterNms( String* pFileNm, String* pFilterNm ) const
/*N*/ {
/*N*/ 	BOOL bRet = FALSE;
/*N*/ 	if( refLink.Is() && refLink->GetLinkManager() )
/*N*/ 	{
/*N*/ 		USHORT nType = refLink->GetObjType();
/*N*/ 		if( OBJECT_CLIENT_GRF == nType )
/*N*/ 			bRet = refLink->GetLinkManager()->GetDisplayNames(
/*N*/ 					refLink, 0, pFileNm, 0, pFilterNm );
/*N*/ 		else if( OBJECT_CLIENT_DDE == nType && pFileNm && pFilterNm )
/*N*/ 		{
/*?*/ 			String sApp, sTopic, sItem;
/*?*/ 			if( refLink->GetLinkManager()->GetDisplayNames(
/*?*/ 					refLink, &sApp, &sTopic, &sItem ) )
/*?*/ 			{
/*?*/                 ( *pFileNm = sApp ) += ::so3::cTokenSeperator;
/*?*/                 ( *pFileNm += sTopic ) += ::so3::cTokenSeperator;
/*?*/ 				*pFileNm += sItem;
/*?*/ 				pFilterNm->AssignAscii( RTL_CONSTASCII_STRINGPARAM( "DDE" ));
/*?*/ 				bRet = TRUE;
/*?*/ 			}
/*N*/ 		}
/*N*/ 	}
/*N*/ 	return bRet;
/*N*/ }


/*N*/ String SwGrfNode::GetStreamName() const
/*N*/ {
/*N*/ 	if( aNewStrmName.Len() )
/*N*/ 		return aNewStrmName;
/*N*/ 	return aGrfObj.GetUserData();
/*N*/ }

// Eine Grafik Undo-faehig machen. Falls sie sich bereits in
// einem Storage befindet, muss sie geladen werden.

//STRIP001 BOOL SwGrfNode::SavePersistentData()
//STRIP001 {
//STRIP001 	if( refLink.Is() )
//STRIP001 	{
//STRIP001 		ASSERT( !bInSwapIn, "SavePersistentData: stehe noch im SwapIn" );
//STRIP001 		GetDoc()->GetLinkManager().Remove( refLink );
//STRIP001 		return TRUE;
//STRIP001 	}
//STRIP001 
//STRIP001 	// Erst mal reinswappen, falls sie im Storage ist
//STRIP001 	if( HasStreamName() && !SwapIn() )
//STRIP001 		return FALSE;
//STRIP001 
//STRIP001 	if( HasStreamName() )
//STRIP001 		DelStreamName();
//STRIP001 
//STRIP001 	// Und in TempFile rausswappen
//STRIP001 	return (BOOL) SwapOut();
//STRIP001 }


//STRIP001 BOOL SwGrfNode::RestorePersistentData()
//STRIP001 {
//STRIP001 	if( refLink.Is() )
//STRIP001 	{
//STRIP001 		refLink->SetVisible( GetDoc()->IsVisibleLinks() );
//STRIP001 		GetDoc()->GetLinkManager().InsertDDELink( refLink );
//STRIP001 		if( GetDoc()->GetRootFrm() )
//STRIP001 			refLink->Update();
//STRIP001 	}
//STRIP001 	return TRUE;
//STRIP001 }


/*N*/ void SwGrfNode::InsertLink( const String& rGrfName, const String& rFltName )
/*N*/ {
/*N*/     refLink = new SwBaseLink( ::so3::LINKUPDATE_ONCALL, FORMAT_GDIMETAFILE, this );
/*N*/ 	SwDoc* pDoc = GetDoc();
/*N*/ 	if( GetNodes().IsDocNodes() )
/*N*/ 	{
/*N*/ 		refLink->SetVisible( pDoc->IsVisibleLinks() );
/*N*/ 		if( rFltName.EqualsAscii( "DDE" ))
/*N*/ 		{
/*?*/ 			USHORT nTmp = 0;
/*?*/ 			String sApp, sTopic, sItem;
/*?*/             sApp = rGrfName.GetToken( 0, ::so3::cTokenSeperator, nTmp );
/*?*/             sTopic = rGrfName.GetToken( 0, ::so3::cTokenSeperator, nTmp );
/*?*/ 			sItem = rGrfName.Copy( nTmp );
/*?*/ 			pDoc->GetLinkManager().InsertDDELink( refLink,
/*N*/ 											sApp, sTopic, sItem );
/*N*/ 		}
/*N*/ 		else
/*N*/ 		{
/*N*/ 			BOOL bSync = rFltName.EqualsAscii( "SYNCHRON" );
/*N*/ 			refLink->SetSynchron( bSync );
/*N*/             refLink->SetContentType( SOT_FORMATSTR_ID_SVXB );
/*N*/ 
/*N*/ 			pDoc->GetLinkManager().InsertFileLink( *refLink,
/*N*/ 											OBJECT_CLIENT_GRF, rGrfName,
/*N*/ 								(!bSync && rFltName.Len() ? &rFltName : 0) );
/*N*/ 		}
/*N*/ 	}
/*N*/ 	aGrfObj.SetLink( rGrfName );
/*N*/ }


//STRIP001 void SwGrfNode::ReleaseLink()
//STRIP001 {
//STRIP001 	if( refLink.Is() )
//STRIP001 	{
//STRIP001 		// erst die Grafik reinswappen!
//STRIP001 //		if( aGraphic.IsSwapOut() || !refLink->IsSynchron() )
//STRIP001 		{
//STRIP001 			bInSwapIn = TRUE;
//STRIP001 			SwBaseLink* pLink = (SwBaseLink*)(::so3::SvBaseLink*) refLink;
//STRIP001 			pLink->SwapIn( TRUE, TRUE );
//STRIP001 			bInSwapIn = FALSE;
//STRIP001 		}
//STRIP001 		GetDoc()->GetLinkManager().Remove( refLink );
//STRIP001 		refLink.Clear();
//STRIP001 		aGrfObj.SetLink();
//STRIP001 	}
//STRIP001 }


/*N*/ void SwGrfNode::SetTwipSize( const Size& rSz )
/*N*/ {
/*N*/ 	nGrfSize = rSz;
/*N*/ 	if( IsScaleImageMap() && nGrfSize.Width() && nGrfSize.Height() )
/*N*/ 	{
/*N*/ 		// Image-Map an Grafik-Groesse anpassen
            DBG_BF_ASSERT(0, "STRIP"); //STRIP001 /*?*/ 		ScaleImageMap();
//STRIP001 /*?*/ 
//STRIP001 /*?*/ 		// Image-Map nicht noch einmal skalieren
//STRIP001 /*?*/ 		SetScaleImageMap( FALSE );
/*N*/ 	}
/*N*/ }

        // Prioritaet beim Laden der Grafik setzen. Geht nur, wenn der Link
        // ein FileObject gesetzt hat
//STRIP001 void SwGrfNode::SetTransferPriority( USHORT nPrio )
//STRIP001 {
//STRIP001 	if( refLink.Is() && refLink->GetObj() )
//STRIP001 		SvxLinkManager::SetTransferPriority( *refLink, nPrio );
//STRIP001 }


//STRIP001 void SwGrfNode::ScaleImageMap()
//STRIP001 {
//STRIP001 	if( !nGrfSize.Width() || !nGrfSize.Height() )
//STRIP001 		return;
//STRIP001 
//STRIP001 	// dann die Image-Map skalieren
//STRIP001 	SwFrmFmt* pFmt = GetFlyFmt();
//STRIP001 
//STRIP001 	if( !pFmt )
//STRIP001 		return;
//STRIP001 
//STRIP001 	SwFmtURL aURL( pFmt->GetURL() );
//STRIP001 	if ( !aURL.GetMap() )
//STRIP001 		return;
//STRIP001 
//STRIP001 	BOOL bScale = FALSE;
//STRIP001 	Fraction aScaleX( 1, 1 );
//STRIP001 	Fraction aScaleY( 1, 1 );
//STRIP001 
//STRIP001 	const SwFmtFrmSize& rFrmSize = pFmt->GetFrmSize();
//STRIP001 	const SvxBoxItem& rBox = pFmt->GetBox();
//STRIP001 
//STRIP001 	if( !rFrmSize.GetWidthPercent() )
//STRIP001 	{
//STRIP001 		SwTwips nWidth = rFrmSize.GetWidth();
//STRIP001 
//STRIP001 		nWidth -= rBox.CalcLineSpace(BOX_LINE_LEFT) +
//STRIP001 				  rBox.CalcLineSpace(BOX_LINE_RIGHT);
//STRIP001 
//STRIP001 		ASSERT( nWidth>0, "Gibt es 0 twip breite Grafiken!?" );
//STRIP001 
//STRIP001 		if( nGrfSize.Width() != nWidth )
//STRIP001 		{
//STRIP001 			aScaleX = Fraction( nGrfSize.Width(), nWidth );
//STRIP001 			bScale = TRUE;
//STRIP001 		}
//STRIP001 	}
//STRIP001 	if( !rFrmSize.GetHeightPercent() )
//STRIP001 	{
//STRIP001 		SwTwips nHeight = rFrmSize.GetHeight();
//STRIP001 
//STRIP001 		nHeight -= rBox.CalcLineSpace(BOX_LINE_TOP) +
//STRIP001 				   rBox.CalcLineSpace(BOX_LINE_BOTTOM);
//STRIP001 
//STRIP001 		ASSERT( nHeight>0, "Gibt es 0 twip hohe Grafiken!?" );
//STRIP001 
//STRIP001 		if( nGrfSize.Height() != nHeight )
//STRIP001 		{
//STRIP001 			aScaleY = Fraction( nGrfSize.Height(), nHeight );
//STRIP001 			bScale = TRUE;
//STRIP001 		}
//STRIP001 	}
//STRIP001 
//STRIP001 	if( bScale )
//STRIP001 	{
//STRIP001 		aURL.GetMap()->Scale( aScaleX, aScaleY );
//STRIP001 		pFmt->SetAttr( aURL );
//STRIP001 	}
//STRIP001 }


//STRIP001 void SwGrfNode::DelStreamName()
//STRIP001 {
//STRIP001 	if( HasStreamName() )
//STRIP001 	{
//STRIP001 		// Dann die Grafik im Storage loeschen
//STRIP001 		SvStorage* pDocStg = GetDoc()->GetDocStorage();
//STRIP001 		if( pDocStg )
//STRIP001 		{
//STRIP001 			String aPicStgName, aStrmName;
//STRIP001 			GetStreamStorageNames( aStrmName, aPicStgName );
//STRIP001 			SvStorageRef refPics = aPicStgName.Len()
//STRIP001 				? pDocStg->OpenStorage( aPicStgName,
//STRIP001 					STREAM_READWRITE | STREAM_SHARE_DENYALL )
//STRIP001 				: pDocStg;
//STRIP001 			if( refPics->GetError() == SVSTREAM_OK )
//STRIP001 			{
//STRIP001 				refPics->Remove( aStrmName );
//STRIP001 				refPics->Commit();
//STRIP001 				refPics->ResetError();	// Falls wir ReadOnly waren
//STRIP001 			}
//STRIP001 		}
//STRIP001 		aGrfObj.SetUserData();
//STRIP001 	}
//STRIP001 }

/*N*/ BOOL SwGrfNode::GetStreamStorageNames( String& rStrmName,
/*N*/ 									  String& rStorName ) const
/*N*/ {
/*N*/ 	BOOL bGraphic = FALSE;
/*N*/ 	rStorName.Erase();
/*N*/ 	rStrmName.Erase();
/*N*/ 
/*N*/ 	String aUserData( aGrfObj.GetUserData() );
/*N*/ 	if( !aUserData.Len() )
/*N*/ 		return FALSE;
/*N*/ 
/*N*/ 	String aProt( RTL_CONSTASCII_STRINGPARAM( "vnd.sun.star.Package:" ) );
/*N*/ 	if( 0 == aUserData.CompareTo( aProt, aProt.Len() ) )
/*N*/ 	{
/*N*/ 		// 6.0 (XML) Package
/*?*/ 		xub_StrLen nPos = aUserData.Search( '/' );
/*?*/ 		if( STRING_NOTFOUND == nPos )
/*?*/ 		{
/*?*/ 			rStrmName = aUserData.Copy( aProt.Len() );
/*?*/ 		}
/*?*/ 		else
/*?*/ 		{
/*?*/ 			rStorName = aUserData.Copy( aProt.Len(), nPos-aProt.Len() );
/*?*/ 			rStrmName = aUserData.Copy( nPos+1 );
/*?*/ 		}
/*N*/ 	}
/*N*/ 	else
/*N*/ 	{
/*N*/ 		// 3.1 - 5.2
/*N*/ 		rStorName = String( RTL_CONSTASCII_STRINGPARAM( "EmbeddedPictures" ) );
/*N*/ 		rStrmName = aUserData;
/*N*/ 		bGraphic = TRUE;
/*N*/ 	}
/*N*/ 	ASSERT( STRING_NOTFOUND == rStrmName.Search( '/' ),
/*N*/ 			"invalid graphic stream name" );
/*N*/ 
/*N*/ 	return bGraphic;
/*N*/ }

/*N*/ SwCntntNode* SwGrfNode::MakeCopy( SwDoc* pDoc, const SwNodeIndex& rIdx ) const
/*N*/ {
/*N*/ 	// kopiere die Formate in das andere Dokument:
/*N*/ 	SwGrfFmtColl* pColl = pDoc->CopyGrfColl( *GetGrfColl() );
/*N*/ 
/*N*/ 	SwGrfNode* pThis = (SwGrfNode*)this;
/*N*/ 
/*N*/ 	Graphic aTmpGrf;
/*N*/ 	SwBaseLink* pLink = (SwBaseLink*)(::so3::SvBaseLink*) refLink;
/*N*/ 	if( !pLink && HasStreamName() )
/*N*/ 	{
/*?*/ 		SvStorageRef refRoot = pThis->GetDoc()->GetDocStorage();
/*?*/ 		ASSERT( refRoot.Is(), "Kein Storage am Doc" );
/*?*/ 		if( refRoot.Is() )
/*?*/ 		{
/*?*/ 			String aStrmName, aPicStgName;
/*?*/ 			BOOL bGraphic = GetStreamStorageNames( aStrmName, aPicStgName );
/*?*/ 			SvStorageRef refPics = aPicStgName.Len()
/*?*/ 			   	? refRoot->OpenStorage( aPicStgName,
/*?*/ 						STREAM_READ | STREAM_SHARE_DENYWRITE )
/*?*/ 				: &refRoot;
/*?*/ 			if( refPics->GetError() == SVSTREAM_OK )
/*?*/ 			{
/*?*/ 				SvStorageStreamRef refStrm = refPics->OpenStream( aStrmName,
/*?*/ 						STREAM_READ | STREAM_SHARE_DENYWRITE );
/*?*/ 				if( refStrm->GetError() == SVSTREAM_OK )
/*?*/ 				{
/*?*/ 					refStrm->SetVersion( refRoot->GetVersion() );
/*?*/ 					if( bGraphic )
/*?*/ 						aTmpGrf.SwapIn( refStrm );
/*?*/ 					else
/*?*/ 						GetGrfFilter()->ImportGraphic( aTmpGrf, String(),
/*?*/ 													   *refStrm );
/*?*/ 				}
/*?*/ 			}
/*N*/ 		}
/*N*/ 	}
/*N*/ 	else
/*N*/ 	{
/*N*/ 		if( aGrfObj.IsSwappedOut() )
                {DBG_BF_ASSERT(0, "STRIP");} //STRIP001 /*?*/ 			pThis->SwapIn();
/*N*/ 		aTmpGrf = aGrfObj.GetGraphic();
/*N*/ 	}
/*N*/ 
/*N*/ 	const ::so3::SvLinkManager& rMgr = GetDoc()->GetLinkManager();
/*N*/ 	String sFile, sFilter;
/*N*/ 	if( IsLinkedFile() )
/*N*/ 		rMgr.GetDisplayNames( refLink, 0, &sFile, 0, &sFilter );
/*N*/ 	else if( IsLinkedDDE() )
/*N*/ 	{
/*?*/ 		String sTmp1, sTmp2;
/*?*/ 		rMgr.GetDisplayNames( refLink, &sTmp1, &sTmp2, &sFilter );
/*?*/         ::so3::MakeLnkName( sFile, &sTmp1, sTmp2, sFilter );
/*?*/ 		sFilter.AssignAscii( RTL_CONSTASCII_STRINGPARAM( "DDE" ));
/*N*/ 	}
/*N*/ 
/*N*/ 	SwGrfNode* pGrfNd = pDoc->GetNodes().MakeGrfNode( rIdx, sFile, sFilter,
/*N*/ 													&aTmpGrf, pColl,
/*N*/ 											(SwAttrSet*)GetpSwAttrSet() );
/*N*/ 	pGrfNd->SetAlternateText( GetAlternateText() );
/*N*/     pGrfNd->SetContour( HasContour(), HasAutomaticContour() );
/*N*/ 	return pGrfNd;
/*N*/ }

/*M*/ IMPL_LINK( SwGrfNode, SwapGraphic, GraphicObject*, pGrfObj )
/*M*/ {
/*M*/ 	SvStream* pRet;
/*M*/ 
/*M*/ 	// #101174#: Keep graphic while in swap in. That's at least important
/*M*/ 	// when breaking links, because in this situation a reschedule call and
/*M*/ 	// a DataChanged call lead to a paint of the graphic. 
/*M*/ 	if( pGrfObj->IsInSwapOut() && (IsSelected() || bInSwapIn) )
/*M*/ 		pRet = GRFMGR_AUTOSWAPSTREAM_NONE;
/*M*/ 	else if( refLink.Is() )
/*M*/ 	{DBG_BF_ASSERT(0, "STRIP"); //STRIP001 
//STRIP001 /*?*/ 		if( pGrfObj->IsInSwapIn() )
//STRIP001 /*?*/ 		{
//STRIP001 /*?*/ 			// then make it by your self
//STRIP001 /*?*/ 			if( !bInSwapIn )
//STRIP001 /*?*/ 			{
//STRIP001 /*?*/ 				BOOL bIsModifyLocked = IsModifyLocked();
//STRIP001 /*?*/ 				LockModify();
//STRIP001 /*?*/ 				SwapIn( FALSE );
//STRIP001 /*?*/ 				if( !bIsModifyLocked )
//STRIP001 /*?*/ 					UnlockModify();
//STRIP001 /*?*/ 			}
//STRIP001 /*?*/ 			pRet = GRFMGR_AUTOSWAPSTREAM_NONE;
//STRIP001 /*?*/ 		}
//STRIP001 /*?*/ 		else
//STRIP001 /*?*/ 			pRet = GRFMGR_AUTOSWAPSTREAM_LINK;
/*M*/ 	}
/*M*/ 	else
/*M*/ 	{
/*M*/ 		pRet = GRFMGR_AUTOSWAPSTREAM_TEMP;
/*M*/ 
/*M*/ 		if( HasStreamName() )
/*M*/ 		{
/*M*/ 			SvStorageRef refRoot = GetDoc()->GetDocStorage();
/*M*/ 			ASSERT( refRoot.Is(), "Kein Storage am Doc" );
/*M*/ 			if( refRoot.Is() )
/*M*/ 			{
/*M*/ 				String aStrmName, aPicStgName;
/*M*/ 				BOOL bGraphic = GetStreamStorageNames( aStrmName, aPicStgName );
/*M*/ 				SvStorageRef refPics = aPicStgName.Len()
/*M*/ 					? refRoot->OpenStorage( aPicStgName,
/*M*/ 						STREAM_READ | STREAM_SHARE_DENYWRITE )
/*M*/ 					: &refRoot;
/*M*/ 				if( refPics->GetError() == SVSTREAM_OK )
/*M*/ 				{
/*M*/ 					SvStream* pTmp = refPics->OpenStream( aStrmName,
/*M*/ 						STREAM_READ | STREAM_SHARE_DENYWRITE );
/*M*/ 					BOOL bDelStrm = TRUE;
/*M*/ 					if( pTmp->GetError() == SVSTREAM_OK )
/*M*/ 					{
/*M*/ 						if( pGrfObj->IsInSwapOut() )
/*M*/ 							pRet = GRFMGR_AUTOSWAPSTREAM_LINK;
/*M*/ 						else
/*M*/ 						{
/*M*/ 							if( bGraphic )
/*M*/ 							{
/*M*/ 								pRet = pTmp;
/*M*/ 								bDelStrm = FALSE;
/*M*/ 								pRet->SetVersion( refRoot->GetVersion() );
/*M*/ 							}
/*M*/ 							else
/*M*/ 							{
/*M*/ 								ImportGraphic( *pTmp );
/*M*/ 								pRet = GRFMGR_AUTOSWAPSTREAM_LOADED;
/*M*/ 							}
/*M*/ 						}
/*M*/ 					}
/*M*/ 					if( bDelStrm )
/*M*/ 						delete pTmp;
/*M*/ 				}
/*M*/ 			}
/*M*/ 		}
/*M*/ 	}
/*M*/ 
/*M*/ 	return (long)pRet;
/*M*/ }


// alle QuickDraw-Bitmaps eines speziellen Docs loeschen
//STRIP001 void DelAllGrfCacheEntries( SwDoc* pDoc )
//STRIP001 {
//STRIP001 	if( pDoc )
//STRIP001 	{
//STRIP001 		// alle Graphic-Links mit dem Namen aus dem Cache loeschen
//STRIP001 		const SvxLinkManager& rLnkMgr = pDoc->GetLinkManager();
//STRIP001 		const ::so3::SvBaseLinks& rLnks = rLnkMgr.GetLinks();
//STRIP001 		SwGrfNode* pGrfNd;
//STRIP001 		String sFileNm;
//STRIP001 		for( USHORT n = rLnks.Count(); n; )
//STRIP001 		{
//STRIP001 			::so3::SvBaseLink* pLnk = &(*rLnks[ --n ]);
//STRIP001 			if( pLnk && OBJECT_CLIENT_GRF == pLnk->GetObjType() &&
//STRIP001 				rLnkMgr.GetDisplayNames( pLnk, 0, &sFileNm ) &&
//STRIP001 				pLnk->ISA( SwBaseLink ) && 0 != ( pGrfNd =
//STRIP001 				((SwBaseLink*)pLnk)->GetCntntNode()->GetGrfNode()) )
//STRIP001 			{
//STRIP001 				pGrfNd->GetGrfObj().ReleaseFromCache();
//STRIP001 			}
//STRIP001 		}
//STRIP001 	}
//STRIP001 }

// returns the with our graphic attributes filled Graphic-Attr-Structure
//STRIP001 GraphicAttr& SwGrfNode::GetGraphicAttr( GraphicAttr& rGA,
//STRIP001 										const SwFrm* pFrm ) const
//STRIP001 {
//STRIP001 	const SwAttrSet& rSet = GetSwAttrSet();
//STRIP001 
//STRIP001 	rGA.SetDrawMode( (GraphicDrawMode)rSet.GetDrawModeGrf().GetValue() );
//STRIP001 
//STRIP001 	const SwMirrorGrf & rMirror = rSet.GetMirrorGrf();
//STRIP001 	ULONG nMirror = BMP_MIRROR_NONE;
//STRIP001 	if( rMirror.IsGrfToggle() && pFrm && !pFrm->FindPageFrm()->OnRightPage() )
//STRIP001 	{
//STRIP001 		switch( rMirror.GetValue() )
//STRIP001 		{
//STRIP001 		case RES_DONT_MIRROR_GRF: 	nMirror = BMP_MIRROR_HORZ; break;
//STRIP001 		case RES_MIRROR_GRF_VERT: 	nMirror = BMP_MIRROR_NONE; break;
//STRIP001 		case RES_MIRROR_GRF_HOR: 	nMirror = BMP_MIRROR_HORZ|BMP_MIRROR_VERT;
//STRIP001 									break;
//STRIP001 		default: 					nMirror = BMP_MIRROR_VERT; break;
//STRIP001 		}
//STRIP001 	}
//STRIP001 	else
//STRIP001 		switch( rMirror.GetValue() )
//STRIP001 		{
//STRIP001 		case RES_MIRROR_GRF_BOTH: 	nMirror = BMP_MIRROR_HORZ|BMP_MIRROR_VERT;
//STRIP001 									break;
//STRIP001 		case RES_MIRROR_GRF_VERT:	nMirror = BMP_MIRROR_HORZ; break;
//STRIP001 		case RES_MIRROR_GRF_HOR:	nMirror = BMP_MIRROR_VERT; break;
//STRIP001 		}
//STRIP001 
//STRIP001 	rGA.SetMirrorFlags( nMirror );
//STRIP001 
//STRIP001 	const SwCropGrf& rCrop = rSet.GetCropGrf();
//STRIP001 	rGA.SetCrop( TWIP_TO_MM100( rCrop.GetLeft() ),
//STRIP001 				 TWIP_TO_MM100( rCrop.GetTop() ),
//STRIP001 				 TWIP_TO_MM100( rCrop.GetRight() ),
//STRIP001 				 TWIP_TO_MM100( rCrop.GetBottom() ));
//STRIP001 
//STRIP001 	const SwRotationGrf& rRotation = rSet.GetRotationGrf();
//STRIP001 	rGA.SetRotation( rRotation.GetValue() );
//STRIP001 
//STRIP001 	rGA.SetLuminance( rSet.GetLuminanceGrf().GetValue() );
//STRIP001 	rGA.SetContrast( rSet.GetContrastGrf().GetValue() );
//STRIP001 	rGA.SetChannelR( rSet.GetChannelRGrf().GetValue() );
//STRIP001 	rGA.SetChannelG( rSet.GetChannelGGrf().GetValue() );
//STRIP001 	rGA.SetChannelB( rSet.GetChannelBGrf().GetValue() );
//STRIP001 	rGA.SetGamma( rSet.GetGammaGrf().GetValue() );
//STRIP001 	rGA.SetInvert( rSet.GetInvertGrf().GetValue() );
//STRIP001 
//STRIP001 	const sal_uInt16 nTrans = rSet.GetTransparencyGrf().GetValue();
//STRIP001 	rGA.SetTransparency( (BYTE) FRound(
//STRIP001 								Min( nTrans, (USHORT) 100 )  * 2.55 ) );
//STRIP001 
//STRIP001 	return rGA;
//STRIP001 }

/*N*/ BOOL SwGrfNode::IsTransparent() const
/*N*/ {
/*N*/ 	BOOL bRet = aGrfObj.IsTransparent();
/*N*/ 	if( !bRet )	// ask the attribut
/*N*/ 		bRet = 0 != GetSwAttrSet().GetTransparencyGrf().GetValue();
/*N*/ 
/*N*/     /// OD 17.09.2002 #102099# - if return value is still FALSE and
/*N*/     ///     graphic is swapped out, assume that graphic is transparent.
/*N*/     ///     Thus, for safety reasons, paint errors are avoided, because the
/*N*/     ///     background is painted not only by the graphic node.
/*N*/     if ( !bRet && aGrfObj.IsSwappedOut() )
/*N*/     {
/*N*/         bRet = true;
/*N*/     }
/*N*/ 
/*N*/ 	return bRet;
/*N*/ }


//STRIP001 BOOL SwGrfNode::IsSelected() const
//STRIP001 {
//STRIP001 	BOOL bRet = FALSE;
//STRIP001 	const SwEditShell* pESh = GetDoc()->GetEditShell();
//STRIP001 	if( pESh )
//STRIP001 	{
//STRIP001 		const SwNode* pN = this;
//STRIP001 		const ViewShell* pV = pESh;
//STRIP001 		do {
//STRIP001 			if( pV->ISA( SwEditShell ) && pN == &((SwCrsrShell*)pV)
//STRIP001 								->GetCrsr()->GetPoint()->nNode.GetNode() )
//STRIP001 			{
//STRIP001 				bRet = TRUE;
//STRIP001 				break;
//STRIP001 			}
//STRIP001 		}
//STRIP001 		while( pESh != ( pV = (ViewShell*)pV->GetNext() ));
//STRIP001 	}
//STRIP001 	return bRet;
//STRIP001 }
}
