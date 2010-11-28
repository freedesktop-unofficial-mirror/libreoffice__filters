/* -*- Mode: C++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */
/*************************************************************************
 *
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER.
 * 
 * Copyright 2000, 2010 Oracle and/or its affiliates.
 *
 * OpenOffice.org - a multi-platform office productivity suite
 *
 * This file is part of OpenOffice.org.
 *
 * OpenOffice.org is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License version 3
 * only, as published by the Free Software Foundation.
 *
 * OpenOffice.org is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License version 3 for more details
 * (a copy is included in the LICENSE file that accompanied this code).
 *
 * You should have received a copy of the GNU Lesser General Public License
 * version 3 along with OpenOffice.org.  If not, see
 * <http://www.openoffice.org/license.html>
 * for a copy of the LGPLv3 License.
 *
 ************************************************************************/

#ifdef _MSC_VER
#pragma hdrstop
#endif

#define _SVSTDARR_USHORTS
#include <bf_svtools/macitem.hxx>
#include <bf_svtools/urihelper.hxx>

#include <horiornt.hxx>

#include <doc.hxx>
#include <errhdl.hxx>
#include <swtable.hxx>

#include <errhdl.hxx>

#include <pam.hxx>
#include <cntfrm.hxx>
#include <pagefrm.hxx>
#include <txtftn.hxx>
#include <fmtftn.hxx>
#include <fmtfld.hxx>
#include <fmtanchr.hxx>
#include <fmthdft.hxx>
#include <fmtcntnt.hxx>
#include <fmtfsize.hxx>
#include <fmtpdsc.hxx>
#include <fmtflcnt.hxx>
#include <fmtrfmrk.hxx>
#include <fchrfmt.hxx>
#include <fmtinfmt.hxx>
#include <fmtcnct.hxx>
#include <charfmt.hxx>
#include <ftninfo.hxx>
#include <sw3imp.hxx>
#include <cellatr.hxx>
#include <tox.hxx>
#include <pagedesc.hxx>
#include <fmtruby.hxx>
#include <tgrditem.hxx>

#include <error.h>
#include "bf_so3/staticbaseurl.hxx"
namespace binfilter {


#define URL_DECODE 	\
    , INetURLObject::WAS_ENCODED, INetURLObject::DECODE_UNAMBIGUOUS


// Diese Datei hat einige Besonderheiten:
// Die aktuelle Sw3IoImp-Instanz wird ueber Sw3IoImp::GetCurrentIo()
// angefordert. Da diese die Variable pStrm mit dem aktuellen I/O-
// Stream besetzt hat, muss dieser auf den uebergebenen Stream umgesetzt
// werden. Dabei wird angenommen, dass alle uebergebenen Streams
// SvStorageStreams sind.

////////////////////////////// Frame-Attribute ////////////////////////////

/*N*/ SfxPoolItem* SwFmtAnchor::Create( SvStream& rStrm, USHORT nIVer ) const
/*N*/ {
/*N*/ 	BYTE cType;
/*N*/ 	USHORT nIndex;
/*N*/ 	rStrm >> cType;
/*N*/ 	if( nIVer < IVER_FMTANCHOR_LONGIDX )
/*N*/ 	{
/*N*/ 		rStrm >> nIndex;
/*N*/ 	}
/*N*/ 	else
/*N*/ 	{
/*N*/ 		UINT32 nIndex32 = Sw3IoImp::InULong( rStrm );
/*N*/ 		ASSERT( nIndex32 <= USHRT_MAX,
/*N*/ 				"SwFmtAnchor: Index/Seitenzahl > USHRT_MAX" );
/*N*/ 		nIndex = (USHORT)nIndex32;
/*N*/ 	}
/*N*/ 	// Dieser Anker ist fuer FLY_AT_CNTNT und FLY_IN_CNTNT
/*N*/ 	// unvollstaendig und muss noch angepasst werden. Dies
/*N*/ 	// geschieht nach dem Einlesen des FrmFmts in InTxtNode().
/*N*/ 	return new SwFmtAnchor( (RndStdIds) cType, nIndex );
/*N*/ }

/*N*/ SvStream& SwFmtAnchor::Store( SvStream& rStrm, USHORT nIVer ) const
/*N*/ {
/*N*/ 	const SwPosition* pPos = GetCntntAnchor();
/*N*/ 	// Der Index hat das Offset fuer FLY_AT_CNTNT und FLY_IN_CNTNT,
/*N*/ 	// sonst die Seitennummer.
/*N*/ 	if( nIVer < IVER_FMTANCHOR_LONGIDX )
/*N*/ 	{
/*N*/ 		// Nur 3.1/4.0-Export
/*N*/ 		ASSERT( SOFFICE_FILEFORMAT_40 >= rStrm.GetVersion(),
/*N*/ 				"SwFmtAnchor:: FF-Version und Item-Version passen nicht" );
/*N*/
/*N*/ 		Sw3IoImp* pIo = Sw3IoImp::GetCurrentIo();
/*N*/
/*N*/ 		if( pIo->IsSw31Export() && pIo->pExportInfo &&
/*N*/ 			pIo->pExportInfo->bDrwFrmFmt31 &&
/*N*/ 			FLY_IN_CNTNT==GetAnchorId() )
/*N*/ 		{
/*N*/ 			// Statt der 0 koennte man auch den Node-Index rausschreiben, aber
/*N*/ 			// wozu, wenn der eh gleich neu gesetzt wird?
/*?*/ 			rStrm << (BYTE) FLY_AT_CNTNT // Igitt, war mal FLY_IN_CNTNT
/*?*/ 				  << (USHORT) 0;
/*N*/ 		}
/*N*/ 		else if( FLY_AT_FLY == GetAnchorId() ||
/*N*/ 				 FLY_AUTO_CNTNT == GetAnchorId() )
/*N*/ 		{
/*?*/ 			BYTE nAnchorId2 = GetAnchorId();
/*?*/ 			USHORT nIndex;
/*?*/ 			if( FLY_AT_FLY == nAnchorId2 )
/*?*/ 			{
/*?*/ 				nAnchorId2 = FLY_PAGE;
/*?*/ 				SwNodeIndex aIdx( pPos->nNode );
/*?*/ 				const SwNodes& rNds = aIdx.GetNodes();
/*?*/ 				const SwCntntNode* pCNd = rNds.GoNext( &aIdx );
/*?*/ 				const SwCntntFrm* pFrm;
/*?*/ 				if( pCNd && 0 != ( pFrm = pCNd->GetFrm() ))
/*?*/ 					nIndex = pFrm->FindPageFrm()->GetPhyPageNum();
/*?*/ 				else
/*?*/ 					nIndex = 1;
/*?*/ 			}
/*?*/ 			else
/*?*/ 			{
/*?*/ 				nAnchorId2 = FLY_AT_CNTNT;
/*?*/ 				xub_StrLen nCntntIdx = pPos->nContent.GetIndex();
/*?*/ 				nIndex = nCntntIdx <= STRING_MAXLEN52 ? nCntntIdx
/*?*/ 													  : STRING_MAXLEN52;
/*?*/ 			}
/*?*/ 			rStrm << (BYTE) nAnchorId2
/*?*/ 				  << (USHORT) nIndex;
/*N*/ 		}
/*N*/ 		else
/*N*/ 		{
/*N*/ 			USHORT nIndex;
/*N*/ 			if( pPos )
/*N*/ 			{
/*N*/ 				xub_StrLen nCntntIdx = pPos->nContent.GetIndex();
/*N*/ 				nIndex = nCntntIdx <= STRING_MAXLEN52 ? nCntntIdx
/*N*/ 													  : STRING_MAXLEN52;
/*N*/ 			}
/*N*/ 			else
/*N*/ 				nIndex = GetPageNum();
/*N*/ 			rStrm << (BYTE) GetAnchorId()
/*N*/ 				  << (USHORT) nIndex;
/*N*/ 		}
/*N*/ 	}
/*N*/ 	else
/*N*/ 	{
/*N*/ 		ASSERT( SOFFICE_FILEFORMAT_40 < rStrm.GetVersion(),
/*N*/ 				"SwFmtAnchor:: FF-Version und Item-Version passen nicht" );
/*N*/ 		ULONG nIndex = pPos ? pPos->nContent.GetIndex() : GetPageNum();
/*N*/ 		if( nIndex > STRING_MAXLEN52 )
/*N*/ 			nIndex = STRING_MAXLEN52;
/*N*/ 		rStrm << (BYTE) GetAnchorId();
/*N*/ 		Sw3IoImp::OutULong( rStrm, nIndex );
/*N*/ 	}
/*N*/
/*N*/ 	return rStrm;
/*N*/ }

/*N*/ USHORT SwFmtAnchor::GetVersion( USHORT nFFVer ) const
/*N*/ {
/*N*/ 	ASSERT( SOFFICE_FILEFORMAT_31==nFFVer ||
/*N*/ 			SOFFICE_FILEFORMAT_40==nFFVer ||
/*N*/ 			SOFFICE_FILEFORMAT_50==nFFVer,
/*N*/ 			"SwFmtAnchor: Gibt es ein neues Fileformat?" );
/*N*/ 	return ( SOFFICE_FILEFORMAT_31==nFFVer ||
/*N*/ 			 SOFFICE_FILEFORMAT_40==nFFVer ) ? 0 : IVER_FMTANCHOR_LONGIDX;
/*N*/ }

/*N*/ SfxPoolItem* SwFmtHeader::Create( SvStream& rStrm, USHORT ) const
/*N*/ {
/*N*/ 	BYTE bActive2;
/*N*/ 	rStrm >> bActive2;
/*N*/ 	Sw3IoImp* pIo = Sw3IoImp::GetCurrentIo();
/*N*/ 	SvStream* p = pIo->pStrm;
/*N*/ 	pIo->pStrm = (SvStorageStream*) &rStrm;
/*N*/
/*N*/ 	USHORT eSave_StartNodeType = pIo->eStartNodeType;
/*N*/ 	pIo->eStartNodeType = SwHeaderStartNode;
/*N*/
/*N*/ 	SwFmtHeader* pAttr = NULL;
/*N*/ 	if( pIo->Peek() == SWG_FREEFMT )
/*N*/ 	{
/*N*/ 		SwFrmFmt* pFmt = (SwFrmFmt*) pIo->InFormat( SWG_FREEFMT, NULL );
/*N*/ 		if( pFmt )
/*N*/ 		{
/*N*/ 			pAttr = new SwFmtHeader( pFmt );
/*N*/ 			pAttr->SetActive( BOOL( bActive2 ) );
/*N*/ 		}
/*N*/ 		else
/*?*/ 			pIo->Error();
/*N*/ 	}
/*N*/ 	// Ohne Format ist das Attribut immer inaktiv!
/*N*/ 	else pAttr = new SwFmtHeader( BOOL( FALSE ) );
/*N*/ 	pIo->pStrm = p;
/*N*/ 	pIo->eStartNodeType = eSave_StartNodeType;
/*N*/
/*N*/ 	return pAttr;
/*N*/ }

/*N*/ SvStream& SwFmtHeader::Store( SvStream& rStrm, USHORT ) const
/*N*/ {
/*N*/ 	rStrm << (BYTE) IsActive();
/*N*/ 	const SwFrmFmt* pFmt = GetHeaderFmt();
/*N*/ 	ASSERT( !IsActive() || pFmt, "Aktiver Header ohne Format" );
/*N*/ 	if( pFmt )
/*N*/ 	{
/*N*/ 		Sw3IoImp* pIo = Sw3IoImp::GetCurrentIo();
/*N*/ 		SvStream* p = pIo->pStrm;
/*N*/ 		pIo->pStrm = (SvStorageStream*) &rStrm;
/*N*/ 		pIo->OutFormat( SWG_FREEFMT, *pFmt );
/*N*/ 		pIo->pStrm = p;
/*N*/ 	}
/*N*/ 	return rStrm;
/*N*/ }

/*N*/ SfxPoolItem* SwFmtFooter::Create( SvStream& rStrm, USHORT ) const
/*N*/ {
/*N*/ 	BYTE bActive3;
/*N*/ 	rStrm >> bActive3;
/*N*/ 	Sw3IoImp* pIo = Sw3IoImp::GetCurrentIo();
/*N*/ 	SvStream* p = pIo->pStrm;
/*N*/ 	pIo->pStrm = (SvStorageStream*) &rStrm;
/*N*/
/*N*/ 	USHORT eSave_StartNodeType = pIo->eStartNodeType;
/*N*/ 	pIo->eStartNodeType = SwFooterStartNode;
/*N*/
/*N*/ 	SwFmtFooter* pAttr = NULL;
/*N*/ 	if( pIo->Peek() == SWG_FREEFMT )
/*N*/ 	{
/*N*/ 		SwFrmFmt* pFmt = (SwFrmFmt*) pIo->InFormat( SWG_FREEFMT, NULL );
/*N*/ 		if( pFmt )
/*N*/ 		{
/*N*/           // --> FME 2005-01-18 #b6218408#
/*N*/           // Emulate 5.2 footer size bug:
/*N*/           if ( pIo->IsVersion( SWG_MAJORVERSION_50 ) )
/*N*/           {
/*N*/               SwFmtFrmSize aSize = pFmt->GetFrmSize( FALSE );
/*N*/               if ( ATT_MIN_SIZE == aSize.GetSizeType() )
/*N*/               {
/*N*/                   aSize.SetHeight( 0 );
/*N*/                   pFmt->SetAttr( aSize );
/*N*/               }
/*N*/           }
/*N*/           // <--
/*N*/           pAttr = new SwFmtFooter( pFmt );
/*N*/ 			pAttr->SetActive( BOOL( bActive3 ) );
/*N*/ 		}
/*N*/ 		else
/*?*/ 			pIo->Error();
/*N*/ 	}
/*N*/ 	// Ohne Format ist das Attribut immer inaktiv!
/*N*/ 	else pAttr = new SwFmtFooter( BOOL( FALSE ) );
/*N*/ 	pIo->pStrm = p;
/*N*/ 	pIo->eStartNodeType = eSave_StartNodeType;
/*N*/
/*N*/ 	return pAttr;
/*N*/ }

/*N*/ SvStream& SwFmtFooter::Store( SvStream& rStrm, USHORT ) const
/*N*/ {
/*N*/ 	rStrm << (BYTE) IsActive();
/*N*/ 	const SwFrmFmt* pFmt = GetFooterFmt();
/*N*/ 	ASSERT( !IsActive() || pFmt, "Aktiver Footer ohne Format" );
/*N*/ 	if( pFmt )
/*N*/ 	{
/*N*/ 		Sw3IoImp* pIo = Sw3IoImp::GetCurrentIo();
/*N*/ 		SvStream* p = pIo->pStrm;
/*N*/ 		pIo->pStrm = (SvStorageStream*) &rStrm;
/*N*/ 		pIo->OutFormat( SWG_FREEFMT, *pFmt );
/*N*/ 		pIo->pStrm = p;
/*N*/ 	}
/*N*/ 	return rStrm;
/*N*/ }

/*N*/ SfxPoolItem* SwFmtCntnt::Create( SvStream& rStrm, USHORT ) const
/*N*/ {
/*N*/ 	Sw3IoImp* pIo = Sw3IoImp::GetCurrentIo();
/*N*/ 	SvStream* p = pIo->pStrm;
/*N*/ 	pIo->pStrm = (SvStorageStream*) &rStrm;
/*N*/ 	if( pIo->bInsert )
/*N*/ 	{
/*?*/ 		if( !pIo->pSectionDepths )
/*?*/ 			pIo->pSectionDepths = new SvUShorts;
/*?*/ 		pIo->pSectionDepths->Insert( (USHORT)0U, pIo->pSectionDepths->Count() );
/*N*/ 	}
/*N*/ 	SwStartNode* pSttNd = &pIo->InContents();
/*N*/ 	if( pIo->bInsert )
/*N*/ 	{
/*?*/ 		ASSERT( pIo->pSectionDepths, "There is the section depth stack?" );
/*?*/ 		ASSERT( pIo->pSectionDepths->Count() > 0U,
/*?*/ 				"section depth stack is empty" );
/*?*/ 		pIo->pSectionDepths->Remove( pIo->pSectionDepths->Count() - 1U );
/*N*/ 	}
/*N*/ 	pIo->pStrm = p;
/*N*/ 	return new SwFmtCntnt( pSttNd );
/*N*/ }

/*N*/ SvStream& SwFmtCntnt::Store( SvStream& rStrm, USHORT ) const
/*N*/ {
/*N*/ 	Sw3IoImp* pIo = Sw3IoImp::GetCurrentIo();
/*N*/ 	SvStream* p = pIo->pStrm;
/*N*/ 	pIo->pStrm = (SvStorageStream*) &rStrm;
/*N*/ 	pIo->OutContents( *GetCntntIdx() );
/*N*/ 	pIo->pStrm = p;
/*N*/ 	return rStrm;
/*N*/ }

/*N*/ SfxPoolItem* SwFmtPageDesc::Create( SvStream& rStrm, USHORT nVersion ) const
/*N*/ {
/*N*/ 	// Hier wird nur der Name im Attribut gesetzt. Spaeter wird
/*N*/ 	// mit ConnectPageDescAttrs() die eigentliche Verbindung
/*N*/ 	// hergestellt.
/*N*/ 	BYTE bAuto;
/*N*/ 	UINT16 nOff, nIdx;
/*N*/ 	if( nVersion < IVER_FMTPAGEDESC_LONGPAGE )
/*N*/ 	{
/*N*/ 		if( nVersion < IVER_FMTPAGEDESC_NOAUTO )
/*N*/ 			rStrm >> bAuto;
/*N*/ 		rStrm >> nOff >> nIdx;
/*N*/ 	}
/*N*/ 	else
/*N*/ 	{
/*N*/ 		ULONG nOff32 = Sw3IoImp::InULong( rStrm );
/*N*/ 		ASSERT( nOff32 <= USHRT_MAX, "SwFmtPageDesc: Seitenzahl > USHRT_MAX" );
/*N*/ 		nOff = (USHORT)nOff32;
/*N*/ 		rStrm >> nIdx;
/*N*/ 	}
/*N*/ 	SwFmtPageDesc* pAttr = new SwFmtPageDesc( 0 );
/*N*/ 	pAttr->SetNumOffset( nOff );
/*N*/ 	pAttr->SetDescNameIdx( nIdx );
/*N*/ 	return pAttr;
/*N*/ }

/*N*/ USHORT SwFmtPageDesc::GetVersion( USHORT nFFVer ) const
/*N*/ {
/*N*/ 	ASSERT( SOFFICE_FILEFORMAT_31==nFFVer ||
/*N*/ 			SOFFICE_FILEFORMAT_40==nFFVer ||
/*N*/ 			SOFFICE_FILEFORMAT_50==nFFVer,
/*N*/ 			"SwFmtPageDesc: Gibt es ein neues Fileformat?" );
/*N*/ 	return ( SOFFICE_FILEFORMAT_31==nFFVer ||
/*N*/ 			 SOFFICE_FILEFORMAT_40==nFFVer ) ? 0 : IVER_FMTPAGEDESC_LONGPAGE;
/*N*/ }

/*N*/ SvStream& SwFmtPageDesc::Store( SvStream& rStrm, USHORT nVersion) const
/*N*/ {
/*N*/ 	ASSERT( IVER_FMTPAGEDESC_NOAUTO != nVersion,
/*N*/ 			"SwFmtPageDesc: Export der Item-Version wird nicht unterstuetzt" );
/*N*/
/*N*/ 	Sw3IoImp* pIo = Sw3IoImp::GetCurrentIo();
/*N*/ 	const SwPageDesc* pDesc = GetPageDesc();
/*N*/ 	USHORT nIdx = IDX_NO_VALUE;
/*N*/ 	if( pDesc )
/*N*/ 		nIdx = pIo->aStringPool.Find( pDesc->GetName(), pDesc->GetPoolFmtId() );
/*N*/ 	USHORT nOff = GetNumOffset();
/*N*/ 	// Eventuell das Header-Bit setzen, dass Seitennummern vorkommen
/*N*/ 	if( nOff )
/*N*/ 		pIo->nFileFlags |= SWGF_HAS_PGNUMS;
/*N*/
/*N*/ 	if( nVersion < IVER_FMTPAGEDESC_LONGPAGE )
/*N*/ 	{
/*N*/ 		rStrm << (BYTE) 0x01		// nicht mehr bei IVER_..._NOAUTO
/*N*/ 			  << (UINT16) nOff
/*N*/ 			  << (UINT16) nIdx;
/*N*/ 	}
/*N*/ 	else
/*N*/ 	{
/*N*/ 		Sw3IoImp::OutULong( rStrm, nOff );
/*N*/ 		rStrm << (UINT16) nIdx;
/*N*/ 	}
/*N*/ 	return rStrm;
/*N*/ }

/*N*/ SfxPoolItem* SwFmtFlyCnt::Create( SvStream& rStrm, USHORT ) const
/*N*/ {
/*N*/ 	Sw3IoImp* pIo = Sw3IoImp::GetCurrentIo();
/*N*/ 	SvStream* p = pIo->pStrm;
/*N*/ 	pIo->pStrm = (SvStorageStream*) &rStrm;
/*N*/
/*N*/ 	USHORT eSave_StartNodeType = pIo->eStartNodeType;
/*N*/ 	pIo->eStartNodeType = SwFlyStartNode;
/*N*/
/*N*/ 	SwFrmFmt* pTmpFmt = NULL;
/*N*/ 	BYTE cKind = pIo->Peek();
/*N*/ 	if( SWG_SDRFMT==cKind )
/*N*/ 	{
/*N*/ 		if( pIo->bInsIntoHdrFtr )
/*N*/ 		{
/*?*/ 			pIo->SkipRec();
/*?*/ 			pIo->bDrawFmtSkipped = TRUE;
/*N*/ 		}
/*N*/ 		else
/*N*/ 		{
/*N*/ 			pTmpFmt = (SwFrmFmt*) pIo->InFormat( SWG_SDRFMT, NULL );
/*N*/ 		}
/*N*/ 	}
/*N*/ 	else
/*N*/ 	{
/*N*/ 		pTmpFmt = (SwFrmFmt*) pIo->InFormat( SWG_FLYFMT, NULL );
/*N*/ 	}
/*N*/
/*N*/ 	pIo->pStrm = p;
/*N*/ 	pIo->eStartNodeType = eSave_StartNodeType;
/*N*/
/*N*/ 	if(	pTmpFmt )
/*N*/ 		return new SwFmtFlyCnt( pTmpFmt );
/*N*/
/*?*/ 	if( !pIo->bInsIntoHdrFtr || SWG_SDRFMT!=cKind )
/*?*/ 		pIo->Error();
/*?*/ 	return NULL;
/*N*/ }

// OD 27.06.2003 #108784# - method to determine, if frame format is allowed
// to be exported in SW3IO.
// Drawing frame formats aren't allowed to be exported.
bool SwFmtFlyCnt::Sw3ioExportAllowed() const
{
    bool bSw3ioExportAllowed = true;

    if ( RES_DRAWFRMFMT == pFmt->Which() )
    {
        const SwFmtAnchor& rFmtAnchor = pFmt->GetAnchor();
        if ( rFmtAnchor.GetAnchorId() != FLY_PAGE &&
             pFmt->GetDoc()->IsInHeaderFooter( rFmtAnchor.GetCntntAnchor()->nNode ) )
        {
            bSw3ioExportAllowed = false;
        }
    }

    return bSw3ioExportAllowed;
}

/*N*/ SvStream& SwFmtFlyCnt::Store( SvStream& rStrm, USHORT ) const
/*N*/ {
/*N*/ 	SwFrmFmt* pFmt1 = GetFrmFmt();
/*N*/ 	if( pFmt1 )
/*N*/ 	{
/*N*/ 		Sw3IoImp* pIo = Sw3IoImp::GetCurrentIo();
/*N*/ 		SvStream* p = pIo->pStrm;
/*N*/ 		pIo->pStrm = (SvStorageStream*) &rStrm;
/*N*/ 		if( RES_DRAWFRMFMT == pFmt1->Which() )
/*N*/ 			pIo->OutFormat( SWG_SDRFMT, *pFmt1 );
/*N*/ 		else
/*N*/ 			pIo->OutFormat( SWG_FLYFMT, *pFmt1 );
/*N*/ 		pIo->pStrm = p;
/*N*/ 	}
/*N*/ 	return rStrm;
/*N*/ }

//////////////////////////////// Text-Attribute ////////////////////////////

/*N*/ SfxPoolItem* SwFmtRefMark::Create( SvStream& rStrm, USHORT ) const
/*N*/ {
/*N*/ 	String aName;
/*N*/ 	rStrm.ReadByteString( aName, rStrm.GetStreamCharSet() );
/*N*/ 	return new SwFmtRefMark( aName );
/*N*/ }

/*N*/ SvStream& SwFmtRefMark::Store( SvStream& rStrm, USHORT ) const
/*N*/ {
/*N*/ 	return rStrm.WriteByteString( GetRefName(), rStrm.GetStreamCharSet() );
/*N*/ }

/*N*/ SfxPoolItem* SwFmtCharFmt::Create( SvStream& rStrm, USHORT ) const
/*N*/ {
/*N*/ 	UINT16 nIdx;
/*N*/ 	rStrm >> nIdx;
/*N*/ 	if( nIdx == IDX_NO_VALUE )
/*N*/ 		return NULL;
/*N*/ 	Sw3IoImp* pIo = Sw3IoImp::GetCurrentIo();
/*N*/ 	SwCharFmt* pChFmt = (SwCharFmt*) pIo->FindFmt( nIdx, SWG_CHARFMT );
/*N*/ 	return new SwFmtCharFmt( pChFmt );
/*N*/ }

/*N*/ SvStream& SwFmtCharFmt::Store( SvStream& rStrm, USHORT ) const
/*N*/ {
/*N*/ 	Sw3IoImp* pIo = Sw3IoImp::GetCurrentIo();
/*N*/ 	SwCharFmt* pFmt = (SwCharFmt*) GetRegisteredIn();
/*N*/ 	return rStrm << (UINT16) pIo->aStringPool.Find( pFmt->GetName(),
/*N*/ 													pFmt->GetPoolFmtId() );
/*N*/ }

/*N*/ SfxPoolItem* SwFmtINetFmt::Create( SvStream& rStrm, USHORT nIVer ) const
/*N*/ {
/*N*/ 	UINT16 nId1, nId2;
/*N*/ 	String aURL1, aTarget;
/*N*/ 	rStrm.ReadByteString( aURL1, rStrm.GetStreamCharSet() );
/*N*/ 	rStrm.ReadByteString( aTarget, rStrm.GetStreamCharSet() );
/*N*/ 	rStrm >> nId1 >> nId2;
/*N*/ 
/*N*/ 	aURL1 = ::binfilter::StaticBaseUrl::SmartRelToAbs( aURL1 );
/*N*/ 	SwFmtINetFmt *pNew = new SwFmtINetFmt( aURL1, aTarget );
/*N*/ 	Sw3IoImp* pIo = Sw3IoImp::GetCurrentIo();
/*N*/ 	if( nId1 != IDX_NO_VALUE )
/*N*/ 	{
/*?*/ 		SwCharFmt* pChFmt = (SwCharFmt*) pIo->FindFmt( nId1, SWG_CHARFMT );
/*?*/ 		if( pChFmt )
/*?*/ 		{
/*?*/ 			pNew->aINetFmt = pChFmt->GetName();
/*?*/ 			pNew->nINetId = pChFmt->GetPoolFmtId();
/*?*/ 		}
/*N*/ 	}
/*N*/ 	if( nId2 != IDX_NO_VALUE )
/*N*/ 	{
/*?*/ 		SwCharFmt* pChFmt = (SwCharFmt*) pIo->FindFmt( nId2, SWG_CHARFMT );
/*?*/ 		if( pChFmt )
/*?*/ 		{
/*?*/ 			pNew->aVisitedFmt = pChFmt->GetName();
/*?*/ 			pNew->nVisitedId = pChFmt->GetPoolFmtId();
/*?*/ 		}
/*N*/ 	}
/*N*/ 	USHORT nCnt;
/*N*/ 	rStrm >> nCnt;
/*N*/ 	while( nCnt-- )
/*N*/ 	{
/*N #i27164#*/ 		USHORT nCurKey;
/*N #i27164#*/ 		String aLibName, aMacName;
/*N #i27164#*/ 		rStrm >> nCurKey;
/*N #i27164#*/ 		rStrm.ReadByteString( aLibName, rStrm.GetStreamCharSet() );
/*N #i27164#*/ 		rStrm.ReadByteString( aMacName, rStrm.GetStreamCharSet() );
/*N #i27164#*/ 		pNew->SetMacro( nCurKey, SvxMacro( aMacName, aLibName, STARBASIC ) );
/*N*/ 	}
/*N*/ 	if( nIVer >= 1 )
/*N*/ 	{
/*N*/ 		String aName1;
/*N*/ 		rStrm.ReadByteString( aName1, rStrm.GetStreamCharSet() );;
/*N*/ 		pNew->SetName( aName1 );
/*N*/ 	}
/*N*/ 	if( nIVer >= 2 )
/*N*/ 	{
/*N*/ 		rStrm >> nCnt;
/*N*/ 		while( nCnt-- )
/*N*/ 		{
/*N #i27164#*/ 			USHORT nCurKey, nScriptType;
/*N #i27164#*/ 			String aLibName, aMacName;
/*N #i27164#*/ 			rStrm >> nCurKey;
/*N #i27164#*/ 			rStrm.ReadByteString( aLibName, rStrm.GetStreamCharSet() );
/*N #i27164#*/ 			rStrm.ReadByteString( aMacName, rStrm.GetStreamCharSet() );
/*N #i27164#*/ 			rStrm >> nScriptType;
/*N #i27164#*/ 			pNew->SetMacro( nCurKey, SvxMacro( aMacName, aLibName,
/*N #i27164#*/ 										(ScriptType)nScriptType ) );
/*N*/ 		}
/*N*/ 	}
/*N*/
/*N*/ 	return pNew;
/*N*/ }

/*N*/ SvStream& SwFmtINetFmt::Store( SvStream& rStrm, USHORT nIVer ) const
/*N*/ {
/*N*/ 	ASSERT( nIVer != USHRT_MAX,
/*N*/ 			"SwFmtINetFmt: Wer faengt da Version USHRT_MAX nicht ab?" );
/*N*/
/*N*/ 	UINT16 nId1 = IDX_NO_VALUE;
/*N*/ 	UINT16 nId2 = IDX_NO_VALUE;
/*N*/ 	Sw3IoImp* pIo = Sw3IoImp::GetCurrentIo();
/*N*/ 	if( aINetFmt.Len() )
/*?*/ 		nId1 = (UINT16) pIo->aStringPool.Find( aINetFmt, nINetId );
/*N*/ 	if( aVisitedFmt.Len() )
/*?*/ 		nId2 = (UINT16) pIo->aStringPool.Find( aVisitedFmt, nVisitedId );
/*N*/ 	String aURL2( GetValue() );
/*N*/ 	lcl_sw3io__ConvertMarkToOutline( aURL2 );
/*N*/ 	rStrm.WriteByteString( ::binfilter::StaticBaseUrl::AbsToRel( aURL URL_DECODE ),
/*N*/ 						   rStrm.GetStreamCharSet() );
/*N*/   	rStrm.WriteByteString( aTargetFrame, rStrm.GetStreamCharSet() );
/*N*/ 	rStrm << nId1 << nId2;
/*N*/
/*N*/ 	USHORT nCnt = pMacroTbl ? (USHORT)pMacroTbl->Count() : 0, nMax = nCnt;
/*N*/ 	if( nCnt )
/*N*/ 	{
/*?*/ 		for( SvxMacro* pMac = pMacroTbl->First(); pMac; pMac = pMacroTbl->Next() )
/*?*/ 			if( STARBASIC != pMac->GetScriptType() )
/*?*/ 				--nCnt;
/*N*/ 	}
/*N*/
/*N*/ 	rStrm << nCnt;
/*N*/
/*N*/ 	if( nCnt )
/*N*/ 	{
/*N*/ 		// erstmal nur die BasicMacros schreiben, die konnte der 3. noch
/*?*/ 		for( SvxMacro* pMac = pMacroTbl->First(); pMac; pMac = pMacroTbl->Next() )
/*?*/ 			if( STARBASIC == pMac->GetScriptType() )
/*?*/ 			{
/*?*/ 				rStrm << (USHORT)pMacroTbl->GetCurKey();
/*?*/ 			  	rStrm.WriteByteString( pMac->GetLibName(),
/*?*/ 									   rStrm.GetStreamCharSet() );
/*?*/ 				rStrm.WriteByteString( pMac->GetMacName(),
/*?*/ 									   rStrm.GetStreamCharSet() );
/*?*/ 			}
/*N*/ 	}
/*N*/
/*N*/ 	if( nIVer >= 1 )
/*N*/ 		rStrm.WriteByteString( GetName(), rStrm.GetStreamCharSet() );
/*N*/
/*N*/ 	if( nIVer >= 2 )
/*N*/ 	{
/*N*/ 		// ab der 4.0 ( nach Technical Beta ) kennen wir auch JavaScript
/*N*/ 		// also noch alle JavaScript-Macros schreiben
/*N*/ 		nCnt = nMax - nCnt;
/*N*/ 		rStrm << nCnt;
/*N*/
/*N*/ 		if( nCnt )
/*N*/ 		{
/*?*/ 			for( SvxMacro* pMac = pMacroTbl->First(); pMac; pMac = pMacroTbl->Next() )
/*?*/ 				if( STARBASIC != pMac->GetScriptType() )
/*?*/ 				{
/*?*/ 					rStrm << (USHORT)pMacroTbl->GetCurKey();
/*?*/ 					rStrm.WriteByteString( pMac->GetLibName(),
/*?*/ 										   rStrm.GetStreamCharSet() );
/*?*/ 					rStrm.WriteByteString( pMac->GetMacName(),
/*?*/ 										   rStrm.GetStreamCharSet() );
/*?*/ 					rStrm << (USHORT)pMac->GetScriptType();
/*N*/ 				}
/*N*/ 		}
/*N*/ 	}
/*N*/
/*N*/ 	return rStrm;
/*N*/ }

/*N*/ USHORT SwFmtINetFmt::GetVersion( USHORT nFFVer ) const
/*N*/ {
/*N*/ 	ASSERT( SOFFICE_FILEFORMAT_31==nFFVer ||
/*N*/ 			SOFFICE_FILEFORMAT_40==nFFVer ||
/*N*/ 			SOFFICE_FILEFORMAT_50==nFFVer,
/*N*/ 			"SwFmtINetFmr: Gibt es ein neues Fileformat?" );
/*N*/ 	return SOFFICE_FILEFORMAT_31==nFFVer ? USHRT_MAX : 2;
/*N*/ }


/*N*/ SfxPoolItem* SwFmtFtn::Create( SvStream& rStrm, USHORT nIVer ) const
/*N*/ {
/*N*/ 	String aNumber1;
/*N*/ 	UINT16 nNumber1;
/*N*/ 	rStrm >> nNumber1;
/*N*/ 	rStrm.ReadByteString( aNumber1, rStrm.GetStreamCharSet() );
/*N*/
/*N*/ 	// Die Section fuer den Text erzeugen
/*N*/ 	Sw3IoImp* pIo = Sw3IoImp::GetCurrentIo();
/*N*/ 	SwNodes& rNodes = pIo->pDoc->GetNodes();
/*N*/ 	SwNodeIndex aStart( rNodes.GetEndOfInserts() );
/*N*/ 	SwStartNode* pSttNd = rNodes.MakeEmptySection( aStart,SwFootnoteStartNode );
/*N*/ 	aStart = *pSttNd->EndOfSectionNode();
/*N*/
/*N*/ 	if( pIo->bInsert )
/*N*/ 	{
/*?*/ 		if( !pIo->pSectionDepths )
/*?*/ 			pIo->pSectionDepths = new SvUShorts;
/*?*/ 		pIo->pSectionDepths->Insert( (USHORT)0U, pIo->pSectionDepths->Count() );
/*N*/ 	}
/*N*/ 	pIo->InContents( aStart, 0, FALSE );
/*N*/ 	if( pIo->bInsert )
/*N*/ 	{
/*?*/ 		ASSERT( pIo->pSectionDepths, "There is the section depth stack?" );
/*?*/ 		ASSERT( pIo->pSectionDepths->Count() > 0U,
/*?*/ 				"section depth stack is empty" );
/*?*/ 		pIo->pSectionDepths->Remove( pIo->pSectionDepths->Count() - 1U );
/*N*/ 	}
/*N*/
/*N*/ 	// die Seq-Nummer einlesen - fuer die Querverweise auf Fussnoten
/*N*/ 	USHORT nSeqNo;
/*N*/ 	BOOL bEndNote1 = FALSE;
/*N*/ 	if( 1 <= nIVer )
/*N*/ 	{
/*N*/ 		rStrm >> nSeqNo;
/*N*/ 	}
/*N*/ 	if( 2 <= nIVer )
/*N*/ 	{
/*N*/ 		BYTE nFlags;
/*N*/ 		rStrm >> nFlags;
/*N*/ 		bEndNote1 = (nFlags & 0x01) != 0;
/*N*/ 	}
/*N*/
/*N*/ 	SwFmtFtn aFtn( bEndNote1 );
/*N*/ 	aFtn.SetNumStr( aNumber1 );
/*N*/ 	aFtn.SetNumber( nNumber1 );
/*N*/
/*N*/ 	// Das Fussnoten-Attribut liest seine Section "auf der Wiese" ein.
/*N*/ 	// Hier muss also der Start errechnet und eingetragen werden.
/*N*/ 	SwFmtFtn& rNew = (SwFmtFtn&)pIo->pDoc->GetAttrPool().Put( aFtn );
/*N*/ 	SwTxtFtn* pAttr = new SwTxtFtn( rNew, 0 );
/*N*/ 	aStart = *pSttNd;
/*N*/ 	pAttr->SetStartNode( &aStart );
/*N*/ 	if( 1 <= nIVer )
/*N*/ 		pAttr->SetSeqNo( nSeqNo );
/*N*/
/*N*/ 	return &rNew;
/*N*/ }

/*N*/ SvStream& SwFmtFtn::Store( SvStream& rStrm, USHORT nIVer ) const
/*N*/ {
/*N*/ 	Sw3IoImp* pIo = Sw3IoImp::GetCurrentIo();
/*N*/
/*N*/ 	rStrm << (UINT16) GetNumber();
/*N*/
/*N*/ 	if( nIVer < 2 && IsEndNote() )
/*N*/ 	{
/*N*/ 		// Im SW 4.0 gab es noch keine End-Noten, also
/*?*/ 		String aNumStr( '*' );
/*?*/ 		if( GetNumStr().Len() )
/*?*/ 			aNumStr += GetNumStr();
/*?*/ 		else
/*?*/ 		{
/*?*/ 			if( pIo )
/*?*/ 				aNumStr += pIo->pDoc->GetEndNoteInfo().aFmt.
/*?*/ 								GetNumStr( GetNumber() );
/*?*/ 			else
/*?*/ 				aNumStr += String::CreateFromInt32( GetNumber() );
/*?*/ 		}
/*?*/ 		rStrm.WriteByteString( aNumStr, rStrm.GetStreamCharSet() );
/*N*/ 	}
/*N*/ 	else
/*N*/ 	{
/*N*/ 		rStrm.WriteByteString( GetNumStr(), rStrm.GetStreamCharSet() );
/*N*/ 	}
/*N*/
/*N*/ 	SwNodeIndex* pStart = GetTxtFtn()->GetStartNode();
/*N*/ 	if( pStart )
/*N*/ 	{
/*N*/ 		ASSERT( pIo, "SwFmtFtn: kein Sw3Io" );
/*N*/ 		SvStream* p = pIo->pStrm;
/*N*/ 		pIo->pStrm = (SvStorageStream*) &rStrm;
/*N*/ 		pIo->OutContents( *pStart );
/*N*/ 		pIo->pStrm = p;
/*N*/ 	}
/*N*/ 	if( 1 <= nIVer )
/*N*/ 		rStrm << (USHORT)pTxtAttr->GetSeqRefNo();
/*N*/ 	if( 2 <= nIVer )
/*N*/ 		rStrm << (BYTE)(IsEndNote() ? 0x01 : 0x00);
/*N*/
/*N*/ 	return rStrm;
/*N*/ }

/*N*/ USHORT SwFmtFtn::GetVersion( USHORT nFFVer ) const
/*N*/ {
/*N*/ 	ASSERT( SOFFICE_FILEFORMAT_31==nFFVer ||
/*N*/ 			SOFFICE_FILEFORMAT_40==nFFVer ||
/*N*/ 			SOFFICE_FILEFORMAT_50==nFFVer,
/*N*/ 			"SwFmtINetFmr: Gibt es ein neues Fileformat?" );
/*N*/ 	return SOFFICE_FILEFORMAT_31 == nFFVer ? 0 :
/*N*/ 		   (SOFFICE_FILEFORMAT_40 == nFFVer ? 1 : 2);
/*N*/ }


/*N*/ SfxPoolItem* SwFmtFld::Create( SvStream& rStrm, USHORT ) const
/*N*/ {
/*N*/ 	Sw3IoImp* pIo = Sw3IoImp::GetCurrentIo();
/*N*/ 	SvStream* p = pIo->pStrm;
/*N*/ 	pIo->pStrm = (SvStorageStream*) &rStrm;
/*N*/ 	SwField* pFld = pIo->InField();
/*N*/ 	pIo->pStrm = p;
/*N*/ 	if( !pFld )
/*N*/ 		return NULL;
/*N*/
/*N*/ 	SwFmtFld* pAttr = new SwFmtFld;
/*N*/ 	pAttr->pField = pFld;
/*N*/ 	return pAttr;
/*N*/ }

/*N*/ SvStream& SwFmtFld::Store( SvStream& rStrm, USHORT ) const
/*N*/ {
/*N*/ 	Sw3IoImp* pIo = Sw3IoImp::GetCurrentIo();
/*N*/ 	SvStream* p = pIo->pStrm;
/*N*/ 	pIo->pStrm = (SvStorageStream*) &rStrm;
/*N*/ 	pIo->OutField( *this );
/*N*/ 	pIo->pStrm = p;
/*N*/ 	return rStrm;
/*N*/ }

/*N*/ SfxPoolItem* SwTOXMark::Create( SvStream& rStrm, USHORT nIVer ) const
/*N*/ {
/*N*/ 	BYTE cType;
/*N*/ 	UINT16 nLevel1, nStrIdx = IDX_NO_VALUE;
/*N*/ 	String aTypeName, aAltText1, aPrimKey, aSecKey;
/*N*/ 	Sw3IoImp* pIo = Sw3IoImp::GetCurrentIo();
/*N*/ 	rStrm >> cType
/*N*/ 		  >> nLevel1;
/*N*/
/*N*/ 	if( nIVer < IVER_TOXMARK_STRPOOL )
/*N*/ 		rStrm.ReadByteString( aTypeName, rStrm.GetStreamCharSet() );
/*N*/ 	else
/*N*/ 		rStrm >> nStrIdx;
/*N*/
/*N*/ 	rStrm.ReadByteString( aAltText1, rStrm.GetStreamCharSet() );
/*N*/ 	rStrm.ReadByteString( aPrimKey, rStrm.GetStreamCharSet() );
/*N*/ 	rStrm.ReadByteString( aSecKey, rStrm.GetStreamCharSet() );
/*N*/
/*N*/ 	BYTE cFlags = 0;
/*N*/ 	// With the 5.2, there are new tox types.
/*N*/ 	if( nIVer >= IVER_TOXMARK_NEWTOX )
/*N*/ 	{
/*N*/ 		rStrm >> cType >> nStrIdx >> cFlags;
/*N*/ 	}
/*N*/
/*N*/ 	TOXTypes eType = (TOXTypes)cType;
/*N*/ 	if( nIVer >= IVER_TOXMARK_STRPOOL )
/*N*/ 	{
/*N*/ 		if( nStrIdx != IDX_NO_VALUE )
/*?*/ 			aTypeName = pIo->aStringPool.Find( nStrIdx );
/*N*/ 		else
/*N*/ 			aTypeName = SwTOXBase::GetTOXName( eType );
/*N*/ 	}
/*N*/
/*N*/ 	// Search tox type
/*N*/ 	const SwTOXType *pType = NULL;
/*N*/ 	USHORT n = pIo->pDoc->GetTOXTypeCount( eType );
/*N*/ 	for( USHORT i = 0; i < n; i++ )
/*N*/ 	{
/*N*/ 		const SwTOXType *pTmp = pIo->pDoc->GetTOXType( eType, i );
/*N*/ 		if( pTmp && pTmp->GetTypeName() == aTypeName )
/*N*/ 		{
/*N*/ 			pType = pTmp;
/*N*/ 			break;
/*N*/ 		}
/*N*/ 	}
/*N*/
/*N*/ 	// If the tox type is unknown, a new one is created.
/*N*/ 	if( !pType )
/*N*/ 	{
/*N*/ 		pIo->pDoc->InsertTOXType( SwTOXType( eType, aTypeName ) );
/*N*/ 		pType = pIo->pDoc->GetTOXType( eType, n );
/*N*/ 	}
/*N*/ 	ASSERT( pType, "unknown tox type" );
/*N*/ 	if( !pType )
/*N*/ 	{
/*?*/ 		pIo->Error();
/*N*/ 		return NULL;
/*N*/ 	}
/*N*/
/*N*/ 	SwTOXMark* pMark = new SwTOXMark( pType );
/*N*/ 	pMark->SetAlternativeText( aAltText1 );
/*N*/ 	switch( eType )
/*N*/ 	{
/*N*/ 		case TOX_INDEX:
/*N*/ 			if( aPrimKey.Len() )
/*N*/ 				pMark->SetPrimaryKey( aPrimKey );
/*N*/ 			if( aSecKey.Len() )
/*?*/ 				pMark->SetSecondaryKey( aSecKey );
/*N*/ 			break;
/*N*/ 		case TOX_USER:
/*N*/ 		case TOX_CONTENT:
/*N*/ 		case TOX_ILLUSTRATIONS:
/*N*/ 		case TOX_OBJECTS:
/*N*/ 		case TOX_TABLES:
/*N*/ 		case TOX_AUTHORITIES:
/*N*/ 			pMark->SetLevel( nLevel1 );
/*N*/ 			break;
/*N*/ 		default:
/*?*/ 			pIo->Error();
/*?*/ 			delete pMark;
/*?*/ 			return 0;
/*N*/ 	}
/*N*/
/*N*/ 	pMark->SetAutoGenerated( 0 != (cFlags & 0x01) );
/*N*/ 	pMark->SetMainEntry( 0 != (cFlags & 0x02) );
/*N*/
/*N*/ 	return pMark;
/*N*/ }

/*N*/ SvStream& SwTOXMark::Store( SvStream& rStrm, USHORT nIVer ) const
/*N*/ {
/*N*/ 	Sw3IoImp* pIo = Sw3IoImp::GetCurrentIo();
/*N*/
/*N*/ 	// Types greater or equal than TOX_ILLUSTRATIONS are new with versuion
/*N*/ 	// 5.2. That for, they must be mapped to a TOX_USER for the 5.1, but their
/*N*/ 	// original type has to be written, too. Some attention must be kept to
/*N*/ 	// the name as well, because if it is the tox types default name, it
/*N*/ 	// must be written for the 5.1 but it has not to be seen by< the 5.2.
/*N*/ 	TOXTypes eType = GetTOXType()->GetType();
/*N*/ 	TOXTypes eOldType = eType >= TOX_ILLUSTRATIONS ? TOX_USER : eType;
/*N*/ 	rStrm << (BYTE)   eOldType
/*N*/ 		  << (UINT16) nLevel;
/*N*/
/*N*/ 	const String& rTypeName = GetTOXType()->GetTypeName();
/*N*/ 	if( nIVer < IVER_TOXMARK_STRPOOL )
/*N*/ 	{
/*N*/ 		// Nur 3.1/4.0-Export
/*N*/ 		ASSERT( SOFFICE_FILEFORMAT_40 >= rStrm.GetVersion(),
/*N*/ 				"SwToxMark: FF-Version und Item-Version passen nicht" );
/*N*/ 		rStrm.WriteByteString( rTypeName, rStrm.GetStreamCharSet() );
/*N*/ 	}
/*N*/ 	else
/*N*/ 	{
/*N*/ 		// Nur 5.0 und folgende
/*N*/ 		ASSERT( SOFFICE_FILEFORMAT_40 < rStrm.GetVersion(),
/*N*/ 				"SwToxMark: FF-Version und Item-Version passen nicht" );
/*N*/ 		UINT16 nStrIdx =
/*N*/ 			( eType >= TOX_ILLUSTRATIONS ||
/*N*/ 			  rTypeName != SwTOXBase::GetTOXName(eType) )
/*N*/ 			? pIo->aStringPool.Find( rTypeName, USHRT_MAX )
/*N*/ 			: IDX_NO_VALUE;
/*N*/ 		rStrm << nStrIdx;
/*N*/ 	}
/*N*/ 	rStrm.WriteByteString( GetAlternativeText(), rStrm.GetStreamCharSet() );
/*N*/ 	rStrm.WriteByteString( aPrimaryKey, rStrm.GetStreamCharSet() );
/*N*/ 	rStrm.WriteByteString( aSecondaryKey, rStrm.GetStreamCharSet() );
/*N*/ 	if( nIVer >= IVER_TOXMARK_NEWTOX )
/*N*/ 	{
/*N*/ 		BYTE cFlags = 0;
/*N*/ 		if( IsAutoGenerated() )
/*N*/ 			cFlags |= 0x01;
/*N*/ 		if( IsMainEntry() )
/*N*/ 			cFlags |= 0x02;
/*N*/ 		UINT16 nStrIdx = rTypeName != SwTOXBase::GetTOXName(eType)
/*N*/ 			? pIo->aStringPool.Find( rTypeName, USHRT_MAX )
/*N*/ 			: IDX_NO_VALUE;
/*N*/ 		rStrm << (BYTE)eType << nStrIdx << cFlags;
/*N*/ 	}
/*N*/
/*N*/ 	return rStrm;
/*N*/ }

/*N*/ USHORT SwTOXMark::GetVersion( USHORT nFFVer ) const
/*N*/ {
/*N*/ 	ASSERT( SOFFICE_FILEFORMAT_31==nFFVer ||
/*N*/ 			SOFFICE_FILEFORMAT_40==nFFVer ||
/*N*/ 			SOFFICE_FILEFORMAT_50==nFFVer,
/*N*/ 			"SwTOXMark: Gibt es ein neues Fileformat?" );
/*N*/ 	return ( SOFFICE_FILEFORMAT_31==nFFVer ||
/*N*/ 			 SOFFICE_FILEFORMAT_40==nFFVer ) ? 0 : IVER_TOXMARK_NEWTOX;
/*N*/ }

SfxPoolItem* SwFmtRuby::Create(SvStream & rStrm, USHORT /*nVer*/) const
{
    String sRubyTxt1;
    SwFmtRuby* pRet = new SwFmtRuby( sRubyTxt1 );

    BOOL bVal;
    rStrm >> bVal;

    return pRet;
}

SvStream& SwFmtRuby::Store( SvStream & rStrm, USHORT /*nIVer*/ ) const
{
    BOOL bVal = 0;
    rStrm << bVal;

    ASSERT( FALSE, "Ruby atribute stored in old format" )

    return rStrm;
}

/*N*/ USHORT SwFmtRuby::GetVersion( USHORT nFFVer ) const
/*N*/ {
/*N*/ 	ASSERT( SOFFICE_FILEFORMAT_31==nFFVer ||
/*N*/ 			SOFFICE_FILEFORMAT_40==nFFVer ||
/*N*/ 			SOFFICE_FILEFORMAT_50==nFFVer,
/*N*/ 			"SwFmtRuby: Gibt es ein neues Fileformat?" );
/*N*/
/*N*/ 	return SOFFICE_FILEFORMAT_50 > nFFVer ? USHRT_MAX : 0;
/*N*/ }


SfxPoolItem* SwTblBoxFormula::Create( SvStream & rStrm, USHORT ) const
{
    String sStr;
    rStrm.ReadByteString( sStr, rStrm.GetStreamCharSet() );
    return new SwTblBoxFormula( sStr );
}

SvStream& SwTblBoxFormula::Store( SvStream & rStrm, USHORT ) const
{
    if( EXTRNL_NAME != GetNameType() && pDefinedIn )
    {
        const SwTableNode* pTblNd;
        const SwTableBox* pBox = (SwTableBox*)GetTableBox();
        if( pBox && pBox->GetSttNd() &&
            0 != ( pTblNd = pBox->GetSttNd()->FindTableNode() ))
        {
            ((SwTblBoxFormula*)this)->PtrToBoxNm( &pTblNd->GetTable() );
        }
    }
    return rStrm.WriteByteString( GetFormula(), rStrm.GetStreamCharSet() );
}

/*N*/ USHORT SwTblBoxFormula::GetVersion( USHORT nFFVer ) const
/*N*/ {
/*N*/ 	ASSERT( SOFFICE_FILEFORMAT_31==nFFVer ||
/*N*/ 			SOFFICE_FILEFORMAT_40==nFFVer ||
/*N*/ 			SOFFICE_FILEFORMAT_50==nFFVer,
/*N*/ 			"SwTblBoxFormula: Gibt es ein neues Fileformat?" );
/*N*/ 	return SOFFICE_FILEFORMAT_31==nFFVer ? USHRT_MAX : 0;
/*N*/ }

SfxPoolItem* SwFmtChain::Create(SvStream& rStrm, USHORT nIVer) const
{
    SwFmtChain *pChain = new SwFmtChain;

    UINT16 nPrevIdx, nNextIdx;
    if( nIVer>0 )
    {
        rStrm   >> nPrevIdx
                >> nNextIdx;

        Sw3IoImp* pIo = Sw3IoImp::GetCurrentIo();
        ASSERT( pIo || nPrevIdx != IDX_NO_VALUE || nNextIdx != IDX_NO_VALUE,
                "SwFmtChain: kein sw3io: Verkettung nicht moeglich" );
        if( pIo )
        {
            // Wenn hier ein Format schon gelesen wurde, erfolgt die
            // Verkettung hier in der einen Richtung und in InFormat
            // in der anderen Richtung.
            // Wenn das Format noch nicht gefunden wurde, erfolgt die
            // Verkettung wenn das Ziel-Format gelesen wird.
            if( nPrevIdx != IDX_NO_VALUE )
            {
                SwFlyFrmFmt *pPrevFlyFmt =
                    (SwFlyFrmFmt *)pIo->aStringPool.FindCachedFmt( nPrevIdx );
                ASSERT( pIo->bInsert ||
                        (SwFlyFrmFmt *)pIo->pDoc->FindSpzFrmFmtByName(
                        pIo->aStringPool.Find( nPrevIdx ) ) == pPrevFlyFmt,
                        "falsches Prev-Format gechached?" );
                pChain->SetPrev( pPrevFlyFmt );
            }
            if( nNextIdx != IDX_NO_VALUE )
            {
                SwFlyFrmFmt *pNextFlyFmt =
                    (SwFlyFrmFmt *)pIo->aStringPool.FindCachedFmt( nNextIdx );
                ASSERT( pIo->bInsert ||
                        (SwFlyFrmFmt *)pIo->pDoc->FindSpzFrmFmtByName(
                        pIo->aStringPool.Find( nNextIdx ) ) == pNextFlyFmt,
                        "falsches Prev-Format gechached?" );
                pChain->SetNext( pNextFlyFmt );
            }
        }
    }

    return pChain;
}

/*N*/ SvStream& SwFmtChain::Store(SvStream &rStrm, USHORT /*nIVer*/) const
/*N*/ {
        ASSERT( nIVer != USHRT_MAX,
                "SwFmtChain: Wer faengt da Version USHRT_MAX nicht ab?" );

        Sw3IoImp* pIo = Sw3IoImp::GetCurrentIo();
        USHORT nPrevIdx = IDX_NO_VALUE, nNextIdx = IDX_NO_VALUE;
        if( pIo )
        {
            if( GetPrev() )
            {
                nPrevIdx = pIo->aStringPool.Find( GetPrev()->GetName(),
                                                  GetPrev()->GetPoolFmtId() );
            }
            if( GetNext() )
            {
                nNextIdx = pIo->aStringPool.Find( GetNext()->GetName(),
                                                  GetNext()->GetPoolFmtId() );
            }
        }

        rStrm   << (UINT16)nPrevIdx
                << (UINT16)nNextIdx;

        return rStrm;
/*N*/ }

/*N*/ USHORT SwFmtChain::GetVersion( USHORT nFFVer ) const
/*N*/ {
/*N*/ 	ASSERT( SOFFICE_FILEFORMAT_31==nFFVer ||
/*N*/ 			SOFFICE_FILEFORMAT_40==nFFVer ||
/*N*/ 			SOFFICE_FILEFORMAT_50==nFFVer,
/*N*/ 			"SwFmtChain: Gibt es ein neues Fileformat?" );
/*N*/ 	return SOFFICE_FILEFORMAT_40 < nFFVer ? 1 : USHRT_MAX;
/*N*/ }

SfxPoolItem* SwTextGridItem::Create(SvStream& rStrm, USHORT /*nIVer*/) const
{
    SwTextGridItem* pRet = new SwTextGridItem;
    BOOL bVal;
    rStrm >> bVal;

    return pRet;
}

SvStream& SwTextGridItem::Store( SvStream & rStrm, USHORT /*nIVer*/ ) const
{
    BOOL bVal = 0;
    rStrm << bVal;

    return rStrm;
}

/*N*/ USHORT SwTextGridItem::GetVersion( USHORT /*nFFVer*/ ) const
/*N*/ {
/*N*/ 	ASSERT( SOFFICE_FILEFORMAT_31==nFFVer ||
/*N*/ 			SOFFICE_FILEFORMAT_40==nFFVer ||
/*N*/ 			SOFFICE_FILEFORMAT_50==nFFVer,
/*N*/             "SwTextGridItem: Gibt es ein neues Fileformat?" );
/*N*/
/*N*/     return USHRT_MAX;
/*N*/ }

}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
