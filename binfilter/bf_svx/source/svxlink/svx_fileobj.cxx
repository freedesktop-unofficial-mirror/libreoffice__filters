/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: svx_fileobj.cxx,v $
 *
 *  $Revision: 1.5 $
 *
 *  last change: $Author: rt $ $Date: 2005-09-08 07:12:01 $
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

#ifdef OS2
// auto strip #include <vcl/sysdep.hxx>
#endif


// auto strip #ifndef _SV_WRKWIN_HXX
// auto strip #include <vcl/wrkwin.hxx>
// auto strip #endif
// auto strip #ifndef _SV_MSGBOX_HXX
// auto strip #include <vcl/msgbox.hxx>
// auto strip #endif
// auto strip #ifndef _URLOBJ_HXX
// auto strip #include <tools/urlobj.hxx>
// auto strip #endif
// auto strip #ifndef _STREAM_HXX
// auto strip #include <tools/stream.hxx>
// auto strip #endif
#ifndef _SOT_FORMATS_HXX
#include <sot/formats.hxx>
#endif
// auto strip #ifndef _FILTER_HXX
// auto strip #include <svtools/filter.hxx>
// auto strip #endif
// auto strip #ifndef _SOERR_HXX
// auto strip #include <so3/soerr.hxx>
// auto strip #endif
#ifndef _LNKBASE_HXX
#include <so3/lnkbase.hxx>
#endif
#ifndef _SFXAPP_HXX
#include <bf_sfx2/app.hxx>
#endif
#ifndef _SFX_PROGRESS_HXX
#include <bf_sfx2/progress.hxx>
#endif
#ifndef _SFX_INTERNO_HXX
#include <bf_sfx2/interno.hxx>
#endif
// auto strip #ifndef _SFX_DOCFILT_HACK_HXX
// auto strip #include <bf_sfx2/docfilt.hxx>
// auto strip #endif
// auto strip #include <sot/exchange.hxx>
// auto strip #include <com/sun/star/uno/Any.hxx>
// auto strip #include <com/sun/star/uno/Sequence.hxx>

#include "fileobj.hxx"
#include "linkmgr.hxx"
#include "dialmgr.hxx"
#include "dialogs.hrc"
// auto strip #include "xoutbmp.hxx"
// auto strip #include "opengrf.hxx"
#include "impgrf.hxx"
namespace binfilter {

using namespace ::com::sun::star::uno;


/*N*/ #define FILETYPE_TEXT		1
/*N*/ #define FILETYPE_GRF		2

/*N*/ class SvxFileObjProgress_Impl : public SfxProgress
/*N*/ {
/*N*/ public:
/*N*/ 	SvxFileObjProgress_Impl( const String& rStr )
/*N*/ 		: SfxProgress( 0, rStr, 100, TRUE, FALSE )
/*N*/ 	{}
/*N*/ 
/*N*/ 	DECL_STATIC_LINK( SvxFileObjProgress_Impl, UpdatePercentHdl, GraphicFilter* );
/*N*/ };


/*N*/ struct Impl_DownLoadData
/*N*/ {
/*N*/ 	Graphic aGrf;
/*N*/ 	Timer aTimer;
/*N*/ 
/*N*/ 	Impl_DownLoadData( const Link& rLink )
/*N*/ 	{
/*N*/ 		aTimer.SetTimeout( 100 );
/*N*/ 		aTimer.SetTimeoutHdl( rLink  );
/*N*/ 		aGrf.SetDefaultType();
/*N*/ 	}
/*N*/ 	~Impl_DownLoadData()
/*N*/ 	{
/*N*/ 		aTimer.Stop();
/*N*/ 	}
/*N*/ };

// --------------------------------------------------------------------------


/*N*/ SvFileObject::SvFileObject()
/*N*/ 	: nType( FILETYPE_TEXT ), pDownLoadData( 0 )
/*N*/ {
/*N*/ 	bLoadAgain = bMedUseCache = TRUE;
/*N*/ 	bSynchron = bLoadError = bWaitForData = bDataReady = bNativFormat =
/*N*/ 	bClearMedium = bProgress = bStateChangeCalled = bInCallDownLoad = FALSE;
/*N*/ }


/*N*/ SvFileObject::~SvFileObject()
/*N*/ {
/*N*/ 	if ( xMed.Is() )
/*N*/ 	{
/*?*/ 		xMed->SetDataAvailableLink( Link() );
/*?*/ 		xMed->SetDoneLink( Link() );
/*?*/ 		xMed.Clear();
/*N*/ 	}
/*N*/ 	delete pDownLoadData;
/*N*/ }


/*N*/ BOOL SvFileObject::GetData( ::com::sun::star::uno::Any & rData,
/*N*/ 								const String & rMimeType,
/*N*/ 								BOOL bGetSynchron )
/*N*/ {
/*N*/ 	ULONG nFmt = SotExchange::GetFormatStringId( rMimeType );
/*N*/ 	switch( nType )
/*N*/ 	{
/*N*/ 	case FILETYPE_TEXT:
/*N*/ 		if( FORMAT_FILE == nFmt )
/*N*/ 		{
/*N*/ 			// das Medium muss in der Applikation geoffnet werden, um die
/*N*/ 			// relativen Datei Links aufzuloesen!!!! Wird ueber den
/*N*/ 			// LinkManager und damit von dessen Storage erledigt.
/*N*/ 			rData <<= ::rtl::OUString( sFileNm );
/*N*/ 
/*
===========================================================================
JP 28.02.96: noch eine Baustelle:
                Idee: hier das Medium und die DocShell anlegen, Doc laden
                      und ueber OLE-SS (GetObj(...)) den Bereich als
                      PseudoObject erfragen. Dieses mit den Daten oder
                      dessen Daten verschicken.

===========================================================================

            SfxMedium aMed( aFileNm.GetFull(), STREAM_READ, TRUE );
            aMed.DownLoad();		// nur mal das Medium anfassen (DownLoaden)

            if( aMed.IsStorage() )
                pSvData->SetData( SvStorageRef( aMed.GetStorage() ),
                                    TRANSFER_COPY );
            else
            {
                SvStream* pStream = aMed.GetInStream();
                if( !pStream )
                    return FALSE;

                UINT32 nLen = pStream->Seek( STREAM_SEEK_TO_END );
                pStream->Seek( STREAM_SEEK_TO_BEGIN );

                void* pData = SvMemAlloc( nLen );
                pStream->Read( pData, nLen );
                pSvData->SetData( pData, nLen, TRANSFER_MOVE );
            }
*/
/*N*/ 		}
/*N*/ 		break;
/*N*/ 
/*N*/ 	case FILETYPE_GRF:
/*?*/ 		if( !bLoadError )
/*?*/ 		{
/*?*/ 			SfxMediumRef xTmpMed;
/*?*/ 
/*?*/ 			if( FORMAT_GDIMETAFILE == nFmt || FORMAT_BITMAP == nFmt ||
/*?*/ 				SOT_FORMATSTR_ID_SVXB == nFmt )
/*?*/ 			{
/*?*/ 				Graphic aGrf;
/*?*/ 
/*?*/ 				//JP 15.07.98: Bug 52959
/*?*/ 				//		falls das Nativformat doch erwuenscht ist, muss am
/*?*/ 				//		Ende das Flag zurueckgesetzt werden.
/*?*/ // wird einzig und allein im sw/ndgrf.cxx benutzt, wenn der Link vom
/*?*/ // GraphicNode entfernt wird.
/*?*/ 				BOOL bOldNativFormat = bNativFormat;
/*?*/ //!!??				bNativFormat = 0 != (ASPECT_ICON & pSvData->GetAspect());
/*?*/ 
/*?*/ 				// falls gedruckt werden soll, warten wir bis die
/*?*/ 				// Daten vorhanden sind
/*?*/ 				if( bGetSynchron )
/*?*/ 				{
/*?*/ 					// testhalber mal ein LoadFile rufen um das nach-
/*?*/ 					// laden ueberahaupt anzustossen
/*?*/ 					if( !xMed.Is() )
/*?*/ 					{
/*?*/ 						LoadFile_Impl();
/*?*/ 						if( xMed.Is() )
/*?*/ 							// dann mit der hoechsten Prioritaet
/*?*/ 							xMed->SetTransferPriority( SFX_TFPRIO_VISIBLE_LOWRES_GRAPHIC );
/*?*/ 					}
/*?*/ 
/*?*/ 					if( !bInCallDownLoad )
/*?*/ 					{
/*?*/ 						xTmpMed = xMed;
/*?*/ 						while( bWaitForData )
/*?*/ 							Application::Reschedule();
/*?*/ 
/*?*/ 						xMed = xTmpMed;
/*?*/ 						bClearMedium = TRUE;
/*?*/ 					}
/*?*/ 				}
/*?*/ 
/*?*/ 				if( pDownLoadData ||
/*?*/ 					( !bWaitForData && ( xMed.Is() || 		// wurde als URL geladen
/*?*/ 						( bSynchron && LoadFile_Impl() && xMed.Is() ) )) )
/*?*/ 				{
/*?*/ 					// falls
/*?*/ 
/*?*/ 					// falls es uebers Internet gesogen wurde, nicht
/*?*/ 					// wieder versuchen
/*?*/ 					if( !bGetSynchron )
/*?*/ 						bLoadAgain = !xMed->IsRemote();
/*?*/ 					bLoadError = !GetGraphic_Impl( aGrf, xMed->GetInStream() );
/*?*/ 				}
/*?*/ 				else if( !LoadFile_Impl() ||
/*?*/ 						!GetGraphic_Impl( aGrf, xMed.Is() ? xMed->GetInStream() : 0 ))
/*?*/ 				{
/*?*/ 					if( !xMed.Is() )
/*?*/ 						break;
/*?*/ 					aGrf.SetDefaultType();
/*?*/ 				}
/*?*/ 
/*?*/ 				if( SOT_FORMATSTR_ID_SVXB != nFmt )
/*?*/ 					nFmt = (bLoadError || GRAPHIC_BITMAP == aGrf.GetType())
/*?*/ 								? FORMAT_BITMAP
/*?*/ 								: FORMAT_GDIMETAFILE;
/*?*/ 
/*?*/ 				SvMemoryStream aMemStm( 0, 65535 );
/*?*/ 				switch ( nFmt )
/*?*/ 				{
/*?*/ 				case SOT_FORMATSTR_ID_SVXB:
/*?*/ 					if( GRAPHIC_NONE != aGrf.GetType() )
/*?*/ 					{
/*?*/ 						aMemStm.SetVersion( SOFFICE_FILEFORMAT_50 );
/*?*/ 						aMemStm << aGrf;
/*?*/ 					}
/*?*/ 					break;
/*?*/ 
/*?*/ 				case  FORMAT_BITMAP:
/*?*/ 					if( !aGrf.GetBitmap().IsEmpty())
/*?*/ 						aMemStm << aGrf.GetBitmap();
/*?*/ 					break;
/*?*/ 
/*?*/ 				default:
/*?*/ 					if( aGrf.GetGDIMetaFile().GetActionCount() )
/*?*/ 					{
/*?*/ 						GDIMetaFile aMeta( aGrf.GetGDIMetaFile() );
/*?*/ 						aMeta.Write( aMemStm );
/*?*/ 					}
/*?*/ 				}
/*?*/ 				rData <<= Sequence< sal_Int8 >( (sal_Int8*) aMemStm.GetData(),
/*?*/ 										aMemStm.Seek( STREAM_SEEK_TO_END ) );
/*?*/ 
/*?*/ 				bNativFormat = bOldNativFormat;
/*?*/ 
/*?*/ 				// alles fertig?
/*?*/ 				if( xMed.Is() && !bSynchron && bClearMedium )
/*?*/ 				{
/*?*/ 					xMed.Clear();
/*?*/ 					bClearMedium = FALSE;
/*?*/ 				}
/*?*/ 			}
/*?*/ 		}
/*?*/ 		break;
/*N*/ 	}
/*N*/ 	return sal_True/*0 != aTypeList.Count()*/;
/*N*/ }




/*N*/ BOOL SvFileObject::Connect( ::so3::SvBaseLink* pLink )
/*N*/ {
/*N*/ 	if( !pLink || !pLink->GetLinkManager() )
/*N*/ 		return FALSE;
/*N*/ 
/*N*/ 	// teste doch mal, ob nicht ein anderer Link mit der gleichen
/*N*/ 	// Verbindung schon existiert
/*N*/ 	pLink->GetLinkManager()->GetDisplayNames( pLink, 0, &sFileNm, 0, &sFilter );
/*N*/ 
/*N*/ 	if( OBJECT_CLIENT_GRF == pLink->GetObjType() )
/*N*/ 	{
/*?*/ 		if( !pLink->IsUseCache() )
/*?*/ 			bMedUseCache = FALSE;
/*?*/ 
/*?*/ 		// Reload-Erkennung ???
/*?*/ 		SvInPlaceObjectRef aRef( pLink->GetLinkManager()->GetPersist() );
/*?*/ 		if( aRef.Is() )
/*?*/ 		{
/*?*/ 			SfxObjectShell* pShell = ((SfxInPlaceObject*)&aRef)->GetObjectShell();
/*?*/ 			if( pShell->IsAbortingImport() )
/*?*/ 				return FALSE;
/*?*/ 
/*?*/ 			if( pShell->IsReloading() )
/*?*/ 				bMedUseCache = FALSE;
/*?*/ 
/*?*/ 			if( pShell->GetMedium() )
/*?*/ 				sReferer = pShell->GetMedium()->GetName();
/*?*/ 		}
/*N*/ 	}
/*N*/ 
/*N*/ 	switch( pLink->GetObjType() )
/*N*/ 	{
/*N*/ 	case OBJECT_CLIENT_GRF:
/*?*/ 		nType = FILETYPE_GRF;
/*?*/ 		bSynchron = pLink->IsSynchron();
/*?*/ 		break;
/*N*/ 
/*N*/ 	case OBJECT_CLIENT_FILE:
/*N*/ 		nType = FILETYPE_TEXT;
/*N*/ 		break;
/*N*/ 
/*N*/ 	default:
/*N*/ 		return FALSE;
/*N*/ 	}
/*N*/ 
/*N*/ 	SetUpdateTimeout( 0 );
/*N*/ 
/*N*/ 	// und jetzt bei diesem oder gefundenem Pseudo-Object anmelden
/*N*/ 	AddDataAdvise( pLink,
/*N*/ 					SotExchange::GetFormatMimeType( pLink->GetContentType()),
/*N*/ 					(bProgress ? ADVISEMODE_ONLYONCE : 0 ));
/*N*/ 	return TRUE;
/*N*/ }


/*?*/ BOOL SvFileObject::LoadFile_Impl()
/*?*/ {
/*?*/ 	// wir sind noch im Laden!!
/*?*/ 	if( bWaitForData || !bLoadAgain || xMed.Is() || pDownLoadData )
/*?*/ 		return FALSE;
/*?*/ 
/*?*/ 	// z.Z. nur auf die aktuelle DocShell
/*?*/ 	xMed = new SfxMedium( sFileNm, STREAM_STD_READ, TRUE );
/*?*/ 	// Keinen Eintrag im Roter Button Menu
/*?*/ 	xMed->SetDontCreateCancellable();
/*?*/ 	xMed->SetUsesCache( bMedUseCache );
/*?*/ 	if( sReferer.Len() )
/*?*/ 		xMed->SetReferer( sReferer );
/*?*/ 	// erstmal mit der niedrigsten Prioritaet
/*?*/ 	xMed->SetTransferPriority( SFX_TFPRIO_INVISIBLE_HIGHRES_GRAPHIC );
/*?*/ 
/*?*/ 	if( !bSynchron )
/*?*/ 	{
/*?*/ 		bLoadAgain = bDataReady = bInNewData = FALSE;
/*?*/ 		bWaitForData = TRUE;
/*?*/ 
/*?*/ 		SfxMediumRef xTmpMed = xMed;
/*?*/ 		xMed->SetDataAvailableLink( STATIC_LINK( this, SvFileObject, LoadGrfNewData_Impl ) );
/*?*/ 		bInCallDownLoad = TRUE;
/*?*/ 		xMed->DownLoad( STATIC_LINK( this, SvFileObject, LoadGrfReady_Impl ) );
/*?*/ 		bInCallDownLoad = FALSE;
/*?*/ 
/*?*/ 		bClearMedium = !xMed.Is();
/*?*/ 		if( bClearMedium )
/*?*/ 			xMed = xTmpMed;		// falls gleich im DownLoad schon schluss ist
/*?*/ 		return bDataReady;
/*?*/ 	}
/*?*/ 
/*?*/ 	bWaitForData = TRUE;
/*?*/ 	bDataReady = bInNewData = FALSE;
/*?*/ 	xMed->DownLoad();
/*?*/ 	bLoadAgain = !xMed->IsRemote();
/*?*/ 	bWaitForData = FALSE;
/*?*/ 
/*?*/ 	// Grafik ist fertig, also DataChanged von der Statusaederung schicken:
/*?*/ 	SendStateChg_Impl( xMed->GetInStream() && xMed->GetInStream()->GetError()
/*?*/ 						? STATE_LOAD_ERROR : STATE_LOAD_OK );
/*?*/ 
/*?*/ 	return TRUE;
/*?*/ }


/*?*/ BOOL SvFileObject::GetGraphic_Impl( Graphic& rGrf, SvStream* pStream )
/*?*/ {
/*?*/ 	Link aPercentLnk;
/*?*/ 	GraphicFilter* pGF = GetGrfFilter();
/*?*/ 	SvxFileObjProgress_Impl* pProgress = 0;
/*?*/ 	if( bProgress && !SfxGetpApp()->GetProgress() )
/*?*/ 	{
/*?*/ 		pProgress = new SvxFileObjProgress_Impl(
/*?*/ 			String( ResId( RID_SVXSTR_GRFLINKPROGRESS, DIALOG_MGR() ) ) );
/*?*/ 
/*?*/ 		aPercentLnk = pGF->GetUpdatePercentHdl();
/*?*/ 		pGF->SetUpdatePercentHdl(
/*?*/ 			STATIC_LINK( pProgress, SvxFileObjProgress_Impl, UpdatePercentHdl ));
/*?*/ 	}
/*?*/ 
/*?*/ 	const int nFilter = sFilter.Len() && pGF->GetImportFormatCount()
/*?*/ 							? pGF->GetImportFormatNumber( sFilter )
/*?*/ 							: GRFILTER_FORMAT_DONTKNOW;
/*?*/ 
/*?*/ 	String aEmptyStr;
/*?*/ 	int nRes;
/*?*/ 
/*?*/ 	// vermeiden, dass ein native Link angelegt wird
/*?*/ 	if( ( !pStream || !pDownLoadData ) && !rGrf.IsLink() &&
/*?*/ 		!rGrf.GetContext() && !bNativFormat )
/*?*/ 		rGrf.SetLink( GfxLink() );
/*?*/ 
/*?*/ 	if( !pStream )
/*?*/ 		nRes = xMed.Is() ? GRFILTER_OPENERROR
/*?*/ 						 : pGF->ImportGraphic( rGrf, INetURLObject(sFileNm), nFilter );
/*?*/ 	else if( !pDownLoadData )
/*?*/ 	{
/*?*/ 		pStream->Seek( STREAM_SEEK_TO_BEGIN );
/*?*/ 		nRes = pGF->ImportGraphic( rGrf, aEmptyStr, *pStream, nFilter );
/*?*/ 	}
/*?*/ 	else
/*?*/ 	{
/*?*/ 		nRes = pGF->ImportGraphic( pDownLoadData->aGrf, aEmptyStr,
/*?*/ 									*pStream, nFilter );
/*?*/ 
/*?*/ 		if( pDownLoadData )
/*?*/ 		{
/*?*/ 			rGrf = pDownLoadData->aGrf;
/*?*/ 			if( GRAPHIC_NONE == rGrf.GetType() )
/*?*/ 				rGrf.SetDefaultType();
/*?*/ 
/*?*/ 
/*?*/ 			if( !pDownLoadData->aGrf.GetContext() )
/*?*/ 			{
/*?*/ 				xMed->SetDataAvailableLink( Link() );
/*?*/ //				xMed->SetDoneLink( Link() );
/*?*/ 				delete pDownLoadData, pDownLoadData = 0;
/*?*/ 				bDataReady = TRUE;
/*?*/ 				bWaitForData = FALSE;
/*?*/ 			}
/*?*/ 			else if( FALSE )
/*?*/ 			{
/*?*/ 				// Timer aufsetzen, um zurueck zukehren
/*?*/ 				pDownLoadData->aTimer.Start();
/*?*/ 			}
/*?*/ 		}
/*?*/ 	}
/*?*/ 
/*?*/ 	if( pStream && ERRCODE_IO_PENDING == pStream->GetError() )
/*?*/ 		pStream->ResetError();
/*?*/ 
/*?*/ #ifndef PRODUCT
/*?*/ 	if( nRes )
/*?*/ 	{
/*?*/ 		if( xMed.Is() && !pStream )
/*?*/ 		{
/*?*/ 			DBG_WARNING3( "GrafikFehler [%d] - [%s] URL[%s]",
/*?*/ 							nRes,
/*?*/ 							xMed->GetPhysicalName().GetBuffer(),
/*?*/ 							sFileNm.GetBuffer() );
/*?*/ 		}
/*?*/ 		else
/*?*/ 		{
/*?*/ 			DBG_WARNING2( "GrafikFehler [%d] - [%s]",
/*?*/ 							nRes, sFileNm.GetBuffer() );
/*?*/ 		}
/*?*/ 	}
/*?*/ #endif
/*?*/ 
/*?*/ 	if( pProgress )
/*?*/ 	{
/*?*/ 		pGF->SetUpdatePercentHdl( aPercentLnk );
/*?*/ 		delete pProgress;
/*?*/ 
/*?*/ 		// Statusaederung schicken:
/*?*/ 		SendStateChg_Impl( GRFILTER_OK == nRes ? STATE_LOAD_OK : STATE_LOAD_ERROR );
/*?*/ 	}
/*?*/ 
/*?*/ 	return GRFILTER_OK == nRes;
/*?*/ }


//STRIP001 String SvFileObject::Edit( Window* pParent, ::so3::SvBaseLink* pLink )
//STRIP001 {
//STRIP001 	String sFile, sRange, sTmpFilter;
//STRIP001 	if( !pLink || !pLink->GetLinkManager() )
//STRIP001 		return sFile;
//STRIP001 
//STRIP001 	pLink->GetLinkManager()->GetDisplayNames( pLink, 0, &sFile, &sRange,
//STRIP001 														&sTmpFilter );
//STRIP001 
//STRIP001 	switch( pLink->GetObjType() )
//STRIP001 	{
//STRIP001 	case OBJECT_CLIENT_GRF:
//STRIP001 		{
//STRIP001 			nType = FILETYPE_GRF;		// falls noch nicht gesetzt
//STRIP001 
//STRIP001 			SvxOpenGraphicDialog aDlg(ResId(RID_SVXSTR_EDITGRFLINK, DIALOG_MGR()));
//STRIP001 			aDlg.EnableLink(sal_False);
//STRIP001 			aDlg.SetPath( sFile, sal_True );
//STRIP001 			aDlg.SetCurrentFilter( sTmpFilter );
//STRIP001 
//STRIP001 			if( !aDlg.Execute() )
//STRIP001 			{
//STRIP001 				sFile = aDlg.GetPath();
//STRIP001 				sFile += ::so3::cTokenSeperator;
//STRIP001 				sFile += ::so3::cTokenSeperator;
//STRIP001 				sFile += aDlg.GetCurrentFilter();
//STRIP001 			}
//STRIP001 			else
//STRIP001 				sFile.Erase();
//STRIP001 		}
//STRIP001 		break;
//STRIP001 	case OBJECT_CLIENT_FILE:
//STRIP001 		{
//STRIP001 			nType = FILETYPE_TEXT;		// falls noch nicht gesetzt
//STRIP001 			Window* pOld = Application::GetDefModalDialogParent();
//STRIP001 			Application::SetDefModalDialogParent( pParent );
//STRIP001 
//STRIP001 			const SfxObjectFactory* pFactory;
//STRIP001 			SvInPlaceObjectRef aRef( pLink->GetLinkManager()->GetPersist() );
//STRIP001 			if( aRef.Is() )
//STRIP001 			{
//STRIP001 				SfxObjectShell* pShell = ((SfxInPlaceObject*)&aRef)->GetObjectShell();
//STRIP001 				pFactory = &pShell->GetFactory();
//STRIP001 			}
//STRIP001 			else
//STRIP001 				pFactory = &SFX_APP()->GetDefaultFactory();
//STRIP001 			SfxMediumRef xMed = SFX_APP()->InsertDocumentDialog( 0, *pFactory );
//STRIP001 
//STRIP001 			if( xMed.Is() )
//STRIP001 			{
//STRIP001 				sFile = xMed->GetName();
//STRIP001 				sFile += ::so3::cTokenSeperator;
//STRIP001 // Bereich! 		sFile += xMed->GetFilter()->GetName();
//STRIP001 				sFile += ::so3::cTokenSeperator;
//STRIP001 				sFile += xMed->GetFilter()->GetFilterName();
//STRIP001 			}
//STRIP001 			else
//STRIP001 				sFile.Erase();
//STRIP001 			Application::SetDefModalDialogParent( pOld );
//STRIP001 		}
//STRIP001 		break;
//STRIP001 
//STRIP001 	default:
//STRIP001 		sFile.Erase();
//STRIP001 	}
//STRIP001 
//STRIP001 	return sFile;
//STRIP001 }


/*?*/ IMPL_STATIC_LINK( SvxFileObjProgress_Impl, UpdatePercentHdl,
/*?*/ 				GraphicFilter *, pFilter )
/*?*/ {
/*?*/ 	pThis->SetState( pFilter->GetPercent() );
/*?*/ 	return 0;
/*?*/ }


/*?*/ IMPL_STATIC_LINK( SvFileObject, LoadGrfReady_Impl, void*, EMPTYARG )
/*?*/ {
/*?*/ 	// wenn wir von hier kommen, kann es kein Fehler mehr sein
/*?*/ 	pThis->bLoadError = FALSE;
/*?*/ 	pThis->bWaitForData = FALSE;
/*?*/ 	pThis->bInCallDownLoad = FALSE;
/*?*/ 
/*?*/ 	if( !pThis->bInNewData && !pThis->bDataReady )
/*?*/ 	{
/*?*/ 			// Grafik ist fertig, also DataChanged von der Status-
/*?*/ 			// aederung schicken:
/*?*/ 		pThis->bDataReady = TRUE;
/*?*/ 		pThis->SendStateChg_Impl( STATE_LOAD_OK );
/*?*/ 
/*?*/ 			// und dann nochmal die Daten senden
/*?*/ 		pThis->NotifyDataChanged();
/*?*/ 	}
/*?*/ 
/*?*/ 	if( pThis->bDataReady )
/*?*/ 	{
/*?*/ 		pThis->bLoadAgain = TRUE;
/*?*/ 		if( pThis->xMed.Is() )
/*?*/ 		{
/*?*/ 			pThis->xMed->SetDataAvailableLink( Link() );
/*?*/ 			pThis->xMed->SetDoneLink( Link() );
/*?*/ 
/*?*/ 			Application::PostUserEvent(
/*?*/ 						STATIC_LINK( pThis, SvFileObject, DelMedium_Impl ),
/*?*/ 						new SfxMediumRef( pThis->xMed ));
/*?*/ 			pThis->xMed.Clear();
/*?*/ 		}
/*?*/ 		if( pThis->pDownLoadData )
/*?*/ 			delete pThis->pDownLoadData, pThis->pDownLoadData = 0;
/*?*/ 	}
/*?*/ 
/*?*/ 	return 0;
/*?*/ }

/*?*/ IMPL_STATIC_LINK( SvFileObject, DelMedium_Impl, SfxMediumRef*, pDelMed )
/*?*/ {
/*?*/ 	delete pDelMed;
/*?*/ 	return 0;
/*?*/ }

/*?*/ IMPL_STATIC_LINK( SvFileObject, LoadGrfNewData_Impl, void*, EMPTYARG )
/*?*/ {
/*?*/ 	// wenn wir von hier kommen, kann es kein Fehler mehr sein
/*?*/ 	if( pThis->bInNewData )
/*?*/ 		return 0;
/*?*/ 
/*?*/ 	pThis->bInNewData = TRUE;
/*?*/ 	pThis->bLoadError = FALSE;
/*?*/ 
/*?*/ 	if( !pThis->pDownLoadData )
/*?*/ 	{
/*?*/ 		pThis->pDownLoadData = new Impl_DownLoadData(
/*?*/ 						STATIC_LINK( pThis, SvFileObject, LoadGrfNewData_Impl ) );
/*?*/ 
/*?*/ 		// Null-Link setzen, damit keine temporaeren Grafiken
/*?*/ 		// rausgeswapt werden; der Filter prueft, ob schon
/*?*/ 		// ein Link gesetzt ist => falls dies zutrifft, wird
/*?*/ 		// _kein_ neuer Link gesetzt; der Link muss hier gesetzt werden,
/*?*/ 		// (bevor das erste Mal gefiltert wird), um zu verhindern,
/*?*/ 		// dass der Kontext zurueckgesetzt wird (aynchrones Laden)
/*?*/ 		if( !pThis->bNativFormat )
/*?*/ 		{
/*?*/ 			static GfxLink aDummyLink;
/*?*/ 			pThis->pDownLoadData->aGrf.SetLink( aDummyLink );
/*?*/ 		}
/*?*/ 	}
/*?*/ 
/*?*/ 	pThis->NotifyDataChanged();
/*?*/ 
/*?*/ 	SvStream* pStrm = pThis->xMed.Is() ? pThis->xMed->GetInStream() : 0;
/*?*/ 	if( pStrm && pStrm->GetError() )
/*?*/ 	{
/*?*/ 		if( ERRCODE_IO_PENDING == pStrm->GetError() )
/*?*/ 			pStrm->ResetError();
/*?*/ 
/*?*/ 		// im DataChanged ein DataReady?
/*?*/ 		else if( pThis->bWaitForData && pThis->pDownLoadData )
/*?*/ 		{
/*?*/ 			pThis->bLoadError = TRUE;
/*?*/ 		}
/*?*/ 	}
/*?*/ 
/*?*/ 	if( pThis->bDataReady )
/*?*/ 	{
/*?*/ 		// Grafik ist fertig, also DataChanged von der Status-
/*?*/ 		// aederung schicken:
/*?*/ 		pThis->SendStateChg_Impl( pStrm->GetError() ? STATE_LOAD_ERROR
/*?*/ 													: STATE_LOAD_OK );
/*?*/ 	}
/*?*/ 
/*?*/ 	pThis->bInNewData = FALSE;
/*?*/ 	return 0;
/*?*/ }


/*	[Beschreibung]

    Die Methode stellt fest, ob aus einem DDE-Object die Daten gelesen
    werden kann.
    Zurueckgegeben wird:
        ERRCODE_NONE 			wenn sie komplett gelesen wurde
        ERRCODE_SO_PENDING		wenn sie noch nicht komplett gelesen wurde
        ERRCODE_SO_FALSE		sonst
*/
//STRIP001 BOOL SvFileObject::IsPending() const
//STRIP001 {
//STRIP001 	return FILETYPE_GRF == nType && !bLoadError &&
//STRIP001 			( pDownLoadData || bWaitForData );
//STRIP001 }
//STRIP001 BOOL SvFileObject::IsDataComplete() const
//STRIP001 {
//STRIP001 	BOOL bRet = FALSE;
//STRIP001 	if( FILETYPE_GRF != nType )
//STRIP001 		bRet = TRUE;
//STRIP001 	else if( !bLoadError && ( !bWaitForData && !pDownLoadData ))
//STRIP001 	{
//STRIP001 		SvFileObject* pThis = (SvFileObject*)this;
//STRIP001 		if( bDataReady ||
//STRIP001 			( bSynchron && pThis->LoadFile_Impl() && xMed.Is() ) )
//STRIP001 			bRet = TRUE;
//STRIP001 		else
//STRIP001 		{
//STRIP001 			INetURLObject aUrl( sFileNm );
//STRIP001 			if( aUrl.HasError() ||
//STRIP001 				INET_PROT_NOT_VALID == aUrl.GetProtocol() )
//STRIP001 				bRet = TRUE;
//STRIP001 		}
//STRIP001 	}
//STRIP001 	return bRet;
//STRIP001 }



/*N*/ void SvFileObject::CancelTransfers()
/*N*/ {
/*N*/ 	if( xMed.Is() )
/*?*/ 		xMed->CancelTransfers();
/*N*/ 
/*N*/ 	// und aus dem Cache austragen, wenn man mitten im Laden ist
/*N*/ 	if( !bDataReady )
/*N*/ 	{
/*N*/ 		// nicht noch mal aufsetzen
/*N*/ 		bLoadAgain = bMedUseCache = FALSE;
/*N*/ 		bDataReady = bLoadError = bWaitForData = TRUE;
/*N*/ 		SendStateChg_Impl( STATE_LOAD_ABORT );
/*N*/ 	}
/*N*/ }


//STRIP001 void SvFileObject::SetTransferPriority( USHORT nPrio )
//STRIP001 {
//STRIP001 	if( xMed.Is() )
//STRIP001 		xMed->SetTransferPriority( nPrio );
//STRIP001 }


/*N*/ void SvFileObject::SendStateChg_Impl( USHORT nState )
/*N*/ {
/*N*/ 	if( !bStateChangeCalled && HasDataLinks() )
/*N*/ 	{
/*N*/ 		Any aAny;
/*N*/ 		aAny <<= ::rtl::OUString::valueOf( (sal_Int32)nState );
/*N*/ 		DataChanged( SotExchange::GetFormatName(
/*N*/ 						SvxLinkManager::RegisterStatusInfoId()), aAny );
/*N*/ 		bStateChangeCalled = TRUE;
/*N*/ 	}
/*N*/ }


}
