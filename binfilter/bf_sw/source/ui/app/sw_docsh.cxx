/*************************************************************************
 *
 *  $RCSfile: sw_docsh.cxx,v $
 *
 *  $Revision: 1.6 $
 *
 *  last change: $Author: vg $ $Date: 2005-02-16 17:43:19 $
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

#ifndef _RTL_LOGFILE_HXX_
#include <rtl/logfile.hxx>
#endif
// auto strip #ifndef _MSGBOX_HXX
// auto strip #include <vcl/msgbox.hxx>
// auto strip #endif
// auto strip #ifndef _APP_HXX //autogen
// auto strip #include <vcl/svapp.hxx>
// auto strip #endif
// auto strip #ifndef _WRKWIN_HXX //autogen
// auto strip #include <vcl/wrkwin.hxx>
// auto strip #endif
// auto strip #ifndef _SV_JOBSET_HXX //autogen
// auto strip #include <vcl/jobset.hxx>
// auto strip #endif
#ifndef _URLOBJ_HXX //autogen
#include <tools/urlobj.hxx>
#endif
#ifndef _SFX_WHITER_HXX //autogen
#include <svtools/whiter.hxx>
#endif
// auto strip #ifndef _ZFORLIST_HXX //autogen
// auto strip #include <svtools/zforlist.hxx>
// auto strip #endif
// auto strip #ifndef _SFXENUMITEM_HXX //autogen
// auto strip #include <svtools/eitem.hxx>
// auto strip #endif
#ifndef _SFXSTRITEM_HXX
#include <svtools/stritem.hxx>
#endif
#ifndef _SVX_ADJITEM_HXX //autogen
#include <bf_svx/adjitem.hxx>
#endif

// auto strip #ifndef _SBXCLASS_HXX //autogen
// auto strip #include <svtools/sbx.hxx>
// auto strip #endif
// auto strip #ifndef INCLUDED_SVTOOLS_MODULEOPTIONS_HXX
// auto strip #include <svtools/moduleoptions.hxx>
// auto strip #endif
// auto strip #ifndef _SFXAPP_HXX
// auto strip #include <bf_sfx2/app.hxx>
// auto strip #endif
// auto strip #ifndef _SFX_MISCCFG_HXX
// auto strip #include <bf_sfx2/misccfg.hxx>
// auto strip #endif
// auto strip #ifndef _SFXDOCINF_HXX //autogen
// auto strip #include <bf_sfx2/docinf.hxx>
// auto strip #endif
// auto strip #ifndef _PASSWD_HXX
// auto strip #include <bf_sfx2/passwd.hxx>
// auto strip #endif
#ifndef _SFX_BINDINGS_HXX //autogen
#include <bf_sfx2/bindings.hxx>
#endif
#ifndef _SFXDOCFILE_HXX //autogen
#include <bf_sfx2/docfile.hxx>
#endif
// auto strip #ifndef _SFX_EVENTCONF_HXX //autogen
// auto strip #include <bf_sfx2/evntconf.hxx>
// auto strip #endif
#ifndef _SFX_DOCFILT_HACK_HXX //autogen
#include <bf_sfx2/docfilt.hxx>
#endif
#ifndef _SFX_PRINTER_HXX //autogen
#include <bf_sfx2/printer.hxx>
#endif
#ifndef _SVXLINKMGR_HXX
#include <bf_svx/linkmgr.hxx>
#endif
// auto strip #ifndef _SVX_SRCHITEM_HXX
// auto strip #include <bf_svx/srchitem.hxx>
// auto strip #endif
// auto strip #ifndef _SVX_HTMLMODE_HXX
// auto strip #include <bf_svx/htmlmode.hxx>
// auto strip #endif
// auto strip #ifndef _SVXMSBAS_HXX
// auto strip #include <bf_svx/svxmsbas.hxx>
// auto strip #endif
// auto strip #ifndef _OFF_APP_HXX //autogen
// auto strip #include <bf_offmgr/app.hxx>
// auto strip #endif
// auto strip #ifndef _OFA_HTMLCFG_HXX //autogen
// auto strip #include <bf_offmgr/htmlcfg.hxx>
// auto strip #endif
// auto strip #ifndef _OFA_FLTRCFG_HXX
// auto strip #include <bf_offmgr/fltrcfg.hxx>
// auto strip #endif
// auto strip #ifndef _SOERR_HXX
// auto strip #include <so3/soerr.hxx>
// auto strip #endif
#ifndef _SO_CLSIDS_HXX
#include <so3/clsids.hxx>
#endif
// auto strip #ifndef _BASMGR_HXX //autogen
// auto strip #include <basic/basmgr.hxx>
// auto strip #endif
// auto strip #ifndef _SB_SBMOD_HXX //autogen
// auto strip #include <basic/sbmod.hxx>
// auto strip #endif
//#ifndef _SB_SBJSMOD_HXX //autogen
//#include <basic/sbjsmod.hxx>
//#endif

// auto strip #ifndef _SWEVENT_HXX //autogen
// auto strip #include <swevent.hxx>
// auto strip #endif
#ifndef _FMTPDSC_HXX //autogen
#include <fmtpdsc.hxx>
#endif
#ifndef _FMTFSIZE_HXX //autogen
#include <fmtfsize.hxx>
#endif

#ifndef _ERRHDL_HXX
#include <errhdl.hxx>
#endif

// auto strip #ifndef _NODE_HXX //autogen
// auto strip #include <node.hxx>
// auto strip #endif
#ifndef _SWWAIT_HXX
#include <swwait.hxx>
#endif
// auto strip #ifndef _SWPRTOPT_HXX
// auto strip #include <swprtopt.hxx>
// auto strip #endif
// auto strip #ifndef _FRMATR_HXX
// auto strip #include <frmatr.hxx>
// auto strip #endif
#ifndef _VIEW_HXX
#include <view.hxx> 		// fuer die aktuelle Sicht
#endif
#ifndef _EDTWIN_HXX
#include <edtwin.hxx>
#endif

#ifndef _HORIORNT_HXX
#include <horiornt.hxx>
#endif

#ifndef _WRTSH_HXX
#include <wrtsh.hxx>		// Verbindung zur Core
#endif
// auto strip #ifndef _DOCSH_HXX
// auto strip #include <docsh.hxx>	  	// Dokumenterzeugung
// auto strip #endif
// auto strip #ifndef _BASESH_HXX
// auto strip #include <basesh.hxx>
// auto strip #endif
// auto strip #ifndef _VIEWOPT_HXX
// auto strip #include <viewopt.hxx>
// auto strip #endif
#ifndef _WDOCSH_HXX
#include <wdocsh.hxx>
#endif
#ifndef _SWMODULE_HXX
#include <swmodule.hxx>
#endif
#ifndef _GLOBDOC_HXX
#include <globdoc.hxx>
#endif
#ifndef _USRPREF_HXX
#include <usrpref.hxx>
#endif
#ifndef _SHELLIO_HXX
#include <shellio.hxx> 		// I/O
#endif
#ifndef _SW3IO_HXX
#include <sw3io.hxx>		// I/O, Hausformat
#endif
// auto strip #ifndef _DOCSTYLE_HXX
// auto strip #include <docstyle.hxx>
// auto strip #endif
#ifndef _DOC_HXX
#include <doc.hxx>
#endif
#ifndef _PAGEDESC_HXX
#include <pagedesc.hxx>
#endif
#ifndef _PVIEW_HXX
#include <pview.hxx>
#endif
// auto strip #ifndef _MDIEXP_HXX
// auto strip #include <mdiexp.hxx>
// auto strip #endif
#ifndef _SWBASLNK_HXX
#include <swbaslnk.hxx>
#endif
#ifndef _SRCVIEW_HXX
#include <srcview.hxx>
#endif
#ifndef _NDINDEX_HXX
#include <ndindex.hxx>
#endif
#ifndef _NDOLE_HXX
#include <ndole.hxx>
#endif

#ifndef _SWSWERROR_H
#include <swerror.h>		// Fehlermeldungen
#endif
#ifndef _HELPID_H
#include <helpid.h>
#endif
#ifndef _CMDID_H
#include <cmdid.h>			//
#endif
#ifndef _GLOBALS_HRC
#include <globals.hrc>
#endif
#ifndef _APP_HRC
#include <app.hrc>
#endif

#include <svtools/moduleoptions.hxx>

using namespace rtl;
using namespace ::com::sun::star::uno;

#define SwDocShell
#ifndef _ITEMDEF_HXX
#include <itemdef.hxx>
#endif

// auto strip #ifndef _COM_SUN_STAR_SCRIPT_XLIBRARYCONTAINER_HPP_
// auto strip #include <com/sun/star/script/XLibraryContainer.hpp>
// auto strip #endif
namespace binfilter {
#ifndef _SWSLOTS_HXX
#include <swslots.hxx>
#endif
using namespace ::com::sun::star::uno;
using namespace ::com::sun::star::script;
using namespace ::com::sun::star::container;

/*N*/ class SwTmpPersist : public SvPersist
/*N*/{
/*N*/	SwDocShell* pDShell;
/*N*/	virtual void FillClass( SvGlobalName * pClassName,
/*N*/							ULONG * pClipFormat,
/*N*/							String * pAppName,
/*N*/							String * pLongUserName,
/*N*/							String * pUserName,
/*N*/							long nFileFormat=SOFFICE_FILEFORMAT_CURRENT ) const;
/*N*/	virtual BOOL Save();
/*N*/	virtual BOOL SaveCompleted( SvStorage * );
/*N*/ public:
/*N*/	SwTmpPersist( SwDocShell& rDSh ) : pDShell( &rDSh ) {}
/*N*/};


/*N*/ SFX_IMPL_INTERFACE( SwDocShell, SfxObjectShell, SW_RES(0) )
/*N*/ {
/*N*/     if ( SvtModuleOptions().IsWriter() )
/*N*/     {
/*N*/         SwGlobalDocShell::Factory().RegisterHelpFile(String::CreateFromAscii("swriter.svh"));
/*N*/         SwGlobalDocShell::Factory().RegisterHelpPIFile(String::CreateFromAscii("swriter.svh"));
/*N*/     }
/*N*/ }

/*--------------------------------------------------------------------
    Beschreibung:	Aller Filter registrieren
 --------------------------------------------------------------------*/

SFX_IMPL_OBJECTFACTORY_DLL(SwDocShell, SFXOBJECTSHELL_STD_NORMAL|SFXOBJECTSHELL_HASMENU,  \
//swriter3	0xDC5C7E40L, 0xB35C, 0x101B, 0x99, 0x61, 0x04, 0x02, 0x1C, 0x00, 0x70,0x02)
//swriter4	0x8b04e9b0,  0x420e, 0x11d0, 0xa4, 0x5e, 0x0,  0xa0, 0x24, 0x9d, 0x57,0xb1, Sw)
//swriter5  0xc20cf9d1, 0x85ae, 0x11d1, 0xaa, 0xb4, 0x0, 0x60, 0x97, 0xda, 0x56, 0x1a
  SvGlobalName(BF_SO3_SW_CLASSID), Sw)      /*swriter5,*/

/*{
    ::RegisterFilterInSfxFactory( (SfxObjectFactory&)Factory(), RC_DOC_ICON );
}
  */


/*N*/ TYPEINIT2(SwDocShell, SfxObjectShell, SfxListener);

/*--------------------------------------------------------------------
    Beschreibung: Laden vorbereiten
 --------------------------------------------------------------------*/


/*N*/ Reader* SwDocShell::StartConvertFrom(SfxMedium& rMedium, SwReader** ppRdr,
/*N*/ 									SwCrsrShell *pCrsrShell,
/*N*/ 									SwPaM* pPaM )
/*N*/ {
/*N*/ 	DBG_BF_ASSERT(0, "STRIP"); return NULL; //STRIP001 BOOL bAPICall = FALSE;
//STRIP001 	const SfxPoolItem* pApiItem;
//STRIP001 	const SfxItemSet* pMedSet;
//STRIP001 	if( 0 != ( pMedSet = rMedium.GetItemSet() ) && SFX_ITEM_SET ==
//STRIP001 			pMedSet->GetItemState( FN_API_CALL, TRUE, &pApiItem ) )
//STRIP001 			bAPICall = ((const SfxBoolItem*)pApiItem)->GetValue();
//STRIP001
//STRIP001 	const SfxFilter* pFlt = rMedium.GetFilter();
//STRIP001 	if( !pFlt )
//STRIP001 	{
//STRIP001 		if(!bAPICall)
//STRIP001 		{
//STRIP001 			InfoBox( 0, SW_RESSTR(STR_CANTOPEN)).Execute();
//STRIP001 		}
//STRIP001 		return 0;
//STRIP001 	}
//STRIP001 	String aFileName( rMedium.GetName() );
//STRIP001 	SwRead pRead = SwIoSystem::GetReader( pFlt->GetUserData() );
//STRIP001 	if( !pRead )
//STRIP001 		return 0;
//STRIP001
//STRIP001 	if( rMedium.IsStorage()
//STRIP001 		? SW_STORAGE_READER & pRead->GetReaderType()
//STRIP001 		: SW_STREAM_READER & pRead->GetReaderType() )
//STRIP001 	{
//STRIP001 		*ppRdr = pPaM ? new SwReader( rMedium, aFileName, *pPaM ) :
//STRIP001 			pCrsrShell ?
//STRIP001 				new SwReader( rMedium, aFileName, *pCrsrShell->GetCrsr() )
//STRIP001 					: new SwReader( rMedium, aFileName, pDoc );
//STRIP001 	}
//STRIP001 	else
//STRIP001 		return 0;
//STRIP001
//STRIP001 	// PassWord Checken
//STRIP001 	String aPasswd;
//STRIP001 	if ((*ppRdr)->NeedsPasswd( *pRead ))
//STRIP001 	{
//STRIP001 		if(!bAPICall)
//STRIP001 		{
//STRIP001 			SfxPasswordDialog* pPasswdDlg =
//STRIP001 					new SfxPasswordDialog( 0 );
//STRIP001 				if(RET_OK == pPasswdDlg->Execute())
//STRIP001 					aPasswd = pPasswdDlg->GetPassword();
//STRIP001 		}
//STRIP001 		else
//STRIP001 		{
//STRIP001 			const SfxItemSet* pSet = rMedium.GetItemSet();
//STRIP001 			const SfxPoolItem *pPassItem;
//STRIP001 			if(pSet && SFX_ITEM_SET == pSet->GetItemState(SID_PASSWORD, TRUE, &pPassItem))
//STRIP001 				aPasswd = ((const SfxStringItem *)pPassItem)->GetValue();
//STRIP001 		}
//STRIP001
//STRIP001 		if (!(*ppRdr)->CheckPasswd( aPasswd, *pRead ))
//STRIP001 		{
//STRIP001 			InfoBox( 0, SW_RES(MSG_ERROR_PASSWD)).Execute();
//STRIP001 				delete *ppRdr;
//STRIP001 //JP: SFX-Aenderung - kein close rufen
//STRIP001 //            if( !rMedium.IsStorage() )
//STRIP001 //                rMedium.CloseInStream();
//STRIP001 			return 0;
//STRIP001 		}
//STRIP001 	}
//STRIP001 	if(rMedium.IsStorage())
//STRIP001 	{
//STRIP001 		SvStorageRef aStor( rMedium.GetStorage() );
//STRIP001 		const SfxItemSet* pSet = rMedium.GetItemSet();
//STRIP001 		const SfxPoolItem *pItem;
//STRIP001 		if(pSet && SFX_ITEM_SET == pSet->GetItemState(SID_PASSWORD, TRUE, &pItem))
//STRIP001 		{
//STRIP001 			DBG_ASSERT(pItem->IsA( TYPE(SfxStringItem) ), "Fehler Parametertype");
//STRIP001 			ByteString aPasswd( ((const SfxStringItem *)pItem)->GetValue(),
//STRIP001 								gsl_getSystemTextEncoding() );
//STRIP001 			aStor->SetKey( aPasswd );
//STRIP001 		}
//STRIP001 		// Fuer's Dokument-Einfuegen noch die FF-Version, wenn's der
//STRIP001 		// eigene Filter ist.
//STRIP001 		ASSERT( pRead != ReadSw3 || pRead != ReadXML || pFlt->GetVersion(),
//STRIP001 				"Am Filter ist keine FF-Version gesetzt" );
//STRIP001 		if( (pRead == ReadSw3 || pRead == ReadXML) && pFlt->GetVersion() )
//STRIP001 			aStor->SetVersion( (long)pFlt->GetVersion() );
//STRIP001 	}
//STRIP001 	// beim Sw3-Reader noch den pIo-Pointer setzen
//STRIP001 	if( pRead == ReadSw3 )
//STRIP001 		((Sw3Reader*)pRead)->SetSw3Io( pIo );
//STRIP001
//STRIP001 	if( pFlt->GetDefaultTemplate().Len() )
//STRIP001 		pRead->SetTemplateName( pFlt->GetDefaultTemplate() );
//STRIP001
//STRIP001 	if( pRead == ReadAscii && 0 != rMedium.GetInStream() &&
//STRIP001 		pFlt->GetUserData().EqualsAscii( FILTER_TEXT_DLG ) )
//STRIP001 	{
//STRIP001 		SwAsciiOptions aOpt;
//STRIP001 		const SfxItemSet* pSet;
//STRIP001 		const SfxPoolItem* pItem;
//STRIP001 		if( 0 != ( pSet = rMedium.GetItemSet() ) && SFX_ITEM_SET ==
//STRIP001 			pSet->GetItemState( SID_FILE_FILTEROPTIONS, TRUE, &pItem ) )
//STRIP001 			aOpt.ReadUserData( ((const SfxStringItem*)pItem)->GetValue() );
//STRIP001
//STRIP001 		if( pRead )
//STRIP001 			pRead->GetReaderOpt().SetASCIIOpts( aOpt );
//STRIP001 	}
//STRIP001
//STRIP001 	return pRead;
/*N*/ }

/*--------------------------------------------------------------------
    Beschreibung: Laden
 --------------------------------------------------------------------*/

//STRIP001 BOOL SwDocShell::ConvertFrom( SfxMedium& rMedium )
//STRIP001 {
//STRIP001 	RTL_LOGFILE_CONTEXT_AUTHOR( aLog, "SW", "JP93722",  "SwDocShell::ConvertFrom" );
//STRIP001
//STRIP001 	SwReader* pRdr;
//STRIP001 	SwRead pRead = StartConvertFrom(rMedium, &pRdr);
//STRIP001 	if (!pRead)
//STRIP001 		return FALSE;
//STRIP001
//STRIP001 	SwWait aWait( *this, TRUE );
//STRIP001
//STRIP001 		// SfxProgress unterdruecken, wenn man Embedded ist
//STRIP001 	SW_MOD()->SetEmbeddedLoadSave(
//STRIP001 							SFX_CREATE_MODE_EMBEDDED == GetCreateMode() );
//STRIP001
//STRIP001 	pRdr->GetDoc()->SetHTMLMode( ISA(SwWebDocShell) );
//STRIP001
//STRIP001     /* #106748# Restore the pool default if reading a saved document. */
//STRIP001     pDoc->RemoveAllFmtLanguageDependencies();
//STRIP001
//STRIP001 	ULONG nErr = pRdr->Read( *pRead );
//STRIP001
//STRIP001 	// Evtl. ein altes Doc weg
//STRIP001 	if( pDoc )
//STRIP001 		RemoveLink();
//STRIP001 	pDoc = pRdr->GetDoc();
//STRIP001
//STRIP001 	// die DocInfo vom Doc am DocShell-Medium setzen
//STRIP001 	if( GetMedium()->GetFilter() &&
//STRIP001 		GetMedium()->GetFilter()->UsesStorage() )
//STRIP001 	{
//STRIP001 		SvStorageRef aRef = GetMedium()->GetStorage();
//STRIP001 		if( aRef.Is() )
//STRIP001 			pDoc->GetInfo()->Save(aRef);
//STRIP001 	}
//STRIP001
//STRIP001 	AddLink();
//STRIP001
//STRIP001 	ASSERT( !pBasePool, "wer hat seinen Pool nicht zerstoert?" );
//STRIP001 	pBasePool = new SwDocStyleSheetPool( *pDoc,
//STRIP001 						SFX_CREATE_MODE_ORGANIZER == GetCreateMode() );
//STRIP001 	UpdateFontList();
//STRIP001 	InitDraw();
//STRIP001
//STRIP001 	delete pRdr;
//STRIP001
//STRIP001 	SW_MOD()->SetEmbeddedLoadSave( FALSE );
//STRIP001
//STRIP001 	SetError( nErr );
//STRIP001 	BOOL bOk = !IsError( nErr );
//STRIP001
//STRIP001 	// StartFinishedLoading rufen. Nicht bei asynchronen Filtern!
//STRIP001 	// Diese muessen das selbst rufen!
//STRIP001 	if( bOk && !pDoc->IsInLoadAsynchron() )
//STRIP001 		StartLoadFinishedTimer();
//STRIP001
//STRIP001 	return bOk;
//STRIP001 }

/*--------------------------------------------------------------------
    Beschreibung: Sichern des Default-Formats, Stg vorhanden
 --------------------------------------------------------------------*/


/*?*/ BOOL SwDocShell::Save()
/*?*/ {
/*?*/ 	 RTL_LOGFILE_CONTEXT_AUTHOR( aLog, "SW", "JP93722",  "SwDocShell::Save" );
 /*?*/ 	sal_Bool bXML = pIo->GetStorage()->GetVersion() >= SOFFICE_FILEFORMAT_60;
    //#i3370# remove quick help to prevent saving of autocorrection suggestions
 /*?*/     if(pView)
 /*?*/         pView->GetEditWin().StopQuickHelp();
 /*?*/     SwWait aWait( *this, TRUE );
 /*?*/
 /*?*/ 	CalcLayoutForOLEObjects();	// format for OLE objets

 /*?*/ 	ULONG nErr = ERR_SWG_WRITE_ERROR, nVBWarning = ERRCODE_NONE;
 /*?*/ 	if( SfxInPlaceObject::Save() )
 /*?*/ 	{
 /*?*/ 		switch( GetCreateMode() )
 /*?*/ 		{
 /*?*/ 		case SFX_CREATE_MODE_INTERNAL:
 /*?*/ 			nErr = 0;
 /*?*/ 			break;
 /*?*/
 /*?*/ 		case SFX_CREATE_MODE_ORGANIZER:
 /*?*/ 			if( bXML )
 /*?*/ 			{
 /*?*/ 				WriterRef xWrt;
/*?*/ 				::binfilter::GetXMLWriter( aEmptyStr, xWrt );
 /*?*/ 				xWrt->SetOrganizerMode( TRUE );
 /*?*/ 				SwWriter aWrt( *pIo->GetStorage(), *pDoc );
 /*?*/ 				nErr = aWrt.Write( xWrt );
 /*?*/ 				xWrt->SetOrganizerMode( FALSE );
 /*?*/ 			}
 /*?*/ 			else
 /*?*/ 				nErr = pIo->SaveStyles();
 /*?*/ 			break;
 /*?*/
 /*?*/ 		case SFX_CREATE_MODE_EMBEDDED:
 /*?*/ 			// SfxProgress unterdruecken, wenn man Embedded ist
 /*?*/ 			SW_MOD()->SetEmbeddedLoadSave( TRUE );
 /*?*/ 			// kein break;
 /*?*/
 /*?*/ 		case SFX_CREATE_MODE_STANDARD:
 /*?*/ 		case SFX_CREATE_MODE_PREVIEW:
 /*?*/ 		default:
 /*?*/ 			{
 /*?*/ 				if( pDoc->ContainsMSVBasic() )
 /*?*/ 				{DBG_BF_ASSERT(0, "STRIP");//STRIP001
//STRIP001  /*?*/ 					SvxImportMSVBasic aTmp( *this, *pIo->GetStorage() );
//STRIP001  /*?*/ 					aTmp.SaveOrDelMSVBAStorage( FALSE, aEmptyStr );
//STRIP001  /*?*/ 					if( OFF_APP()->GetFilterOptions()->IsLoadWordBasicStorage() )
//STRIP001  /*?*/ 						nVBWarning = SvxImportMSVBasic::
//STRIP001  /*?*/ 										GetSaveWarningOfMSVBAStorage( *this );
//STRIP001  /*?*/ 					pDoc->SetContainsMSVBasic( FALSE );
 /*?*/ 				}
 /*?*/
 /*?*/ 				if( !bXML &&
 /*?*/ 					!ISA( SwGlobalDocShell ) && !ISA( SwWebDocShell ) &&
 /*?*/ 					SFX_CREATE_MODE_EMBEDDED != GetCreateMode() )
 /*?*/ 					AddXMLAsZipToTheStorage( *pIo->GetStorage() );
 /*?*/
 /*?*/ 				// TabellenBox Edit beenden!
 /*?*/ 				if( pWrtShell )
 /*?*/ 					pWrtShell->EndAllTblBoxEdit();
 /*?*/
 /*?*/ 				WriterRef xWrt;
 /*?*/ 				if( bXML )
 /*?*/ 				{
/*?*/ 					::binfilter::GetXMLWriter( aEmptyStr, xWrt );
 /*?*/ 				}
 /*?*/ 				else
 /*?*/ 				{
/*?*/ 					::binfilter::GetSw3Writer( aEmptyStr, xWrt );
 /*?*/ 					((Sw3Writer*)&xWrt)->SetSw3Io( pIo, FALSE );
 /*?*/ 				}
 /*?*/
 /*?*/                 BOOL bLockedView;
 /*?*/                 if ( pWrtShell )
 /*?*/                 {
 /*?*/                     bLockedView = pWrtShell->IsViewLocked();
 /*?*/                     pWrtShell->LockView( TRUE );    //lock visible section
 /*?*/                 }
 /*?*/
 /*?*/ 				SwWriter aWrt( *pIo->GetStorage(), *pDoc );
 /*?*/ 				nErr = aWrt.Write( xWrt );
 /*?*/
 /*?*/                 if ( pWrtShell )
 /*?*/                     pWrtShell->LockView( bLockedView );
 /*?*/ 			}
 /*?*/ 			break;
 /*?*/ 		}
 /*?*/ 		SW_MOD()->SetEmbeddedLoadSave( FALSE );
 /*?*/ 	}
 /*?*/ 	SetError( nErr ? nErr : nVBWarning );
 /*?*/
 /*?*/ 	SfxViewFrame* pFrm = pWrtShell ? pWrtShell->GetView().GetViewFrame() : 0;
 /*?*/ 	if( pFrm )
 /*?*/ 	{
 /*?*/ 		pFrm->GetBindings().SetState( SfxStringItem( SID_DOC_MODIFIED, ' ' ));
 /*?*/ 	}
 /*?*/ 	return !IsError( nErr );
/*?*/ }

/*--------------------------------------------------------------------
    Beschreibung: Sichern im Defaultformat
 --------------------------------------------------------------------*/


/*N*/ BOOL SwDocShell::SaveAs( SvStorage * pStor )
/*N*/ {
/*N*/ 	RTL_LOGFILE_CONTEXT_AUTHOR( aLog, "SW", "JP93722",  "SwDocShell::SaveAs" );
/*N*/ 	sal_Bool bXML = pStor->GetVersion() >= SOFFICE_FILEFORMAT_60;
/*N*/
/*N*/ 	SwWait aWait( *this, TRUE );
/*N*/     //#i3370# remove quick help to prevent saving of autocorrection suggestions
/*N*/     if(pView)
/*N*/         pView->GetEditWin().StopQuickHelp();
/*N*/
/*N*/ 	if( pDoc->IsGlobalDoc() && !pDoc->IsGlblDocSaveLinks() )
/*N*/ 		RemoveOLEObjects();
/*N*/
/*N*/ 	{
/*N*/ 		// Task 75666 - is the Document imported by our Microsoft-Filters?
/*N*/ 		const SfxFilter* pOldFilter = GetMedium()->GetFilter();
/*N*/ 		if( pOldFilter &&
/*N*/ 			( pOldFilter->GetUserData().EqualsAscii( FILTER_WW8 ) ||
/*N*/ 			  pOldFilter->GetUserData().EqualsAscii( "CWW6" ) ||
/*N*/ 			  pOldFilter->GetUserData().EqualsAscii( "WW6" ) ||
/*N*/ 			  pOldFilter->GetUserData().EqualsAscii( "WW1" ) ))
/*N*/ 		{
/*?*/ 			DBG_BF_ASSERT(0, "STRIP"); //STRIP001 // when saving it in our own fileformat, then remove the template
/*?*/ 			// name from the docinfo.
//STRIP001 /*?*/ 			SfxDocumentInfo aInfo = GetDocInfo();
//STRIP001 /*?*/ 			if( aInfo.GetTemplateName().Len() ||
//STRIP001 /*?*/ 			    aInfo.GetTemplateFileName().Len() )
//STRIP001 /*?*/ 			{
//STRIP001 /*?*/ 				aInfo.SetTemplateName( aEmptyStr );
//STRIP001 /*?*/ 			    aInfo.SetTemplateFileName( aEmptyStr );
//STRIP001 /*?*/ 				SetDocumentInfo( aInfo );
//STRIP001 /*?*/ 			}
/*N*/ 		}
/*N*/ 	}
/*N*/
/*N*/ 	CalcLayoutForOLEObjects();	// format for OLE objets
/*N*/
/*N*/ 	ULONG nErr = ERR_SWG_WRITE_ERROR, nVBWarning = ERRCODE_NONE;
/*N*/ 	if( SfxInPlaceObject::SaveAs( pStor ) )
/*N*/ 	{
/*N*/ 		if( GetDoc()->IsGlobalDoc() && !ISA( SwGlobalDocShell ) )
/*N*/ 		{
/*?*/ 			// This is to set the correct class id if SaveAs is
/*?*/ 			// called from SwDoc::SplitDoc to save a normal doc as
/*?*/ 			// global doc. In this case, SaveAs is called at a
/*?*/ 			// normal doc shell, therefore, SfxInplaceObject::SaveAs
/*?*/ 			// will set the wrong class id.
/*?*/ 			SvGlobalName aClassName;
/*?*/ 			ULONG nClipFormat;
/*?*/ 			String aAppName, aLongUserName, aUserName;
/*?*/ 			SfxObjectShellRef xDocSh =
/*?*/ 				new SwGlobalDocShell( SFX_CREATE_MODE_INTERNAL );
/*?*/ 			xDocSh->FillClass( &aClassName, &nClipFormat, &aAppName,
/*?*/ 								&aLongUserName, &aUserName,
/*?*/ 								pStor->GetVersion() );
/*?*/ 			pStor->SetClass( aClassName, nClipFormat, aUserName );
/*N*/ 		}

/*N*/ 		if( pDoc->ContainsMSVBasic() )
/*N*/ 		{
/*?*/ 		DBG_BF_ASSERT(0, "STRIP"); //STRIP001 	SvxImportMSVBasic aTmp( *this, *pIo->GetStorage() );
//STRIP001 /*?*/ 			aTmp.SaveOrDelMSVBAStorage( FALSE, aEmptyStr );
//STRIP001 /*?*/ 					if( OFF_APP()->GetFilterOptions()->IsLoadWordBasicStorage() )
//STRIP001 /*?*/ 						nVBWarning = SvxImportMSVBasic::
//STRIP001 /*?*/ 										GetSaveWarningOfMSVBAStorage( *this );
//STRIP001 /*?*/ 			pDoc->SetContainsMSVBasic( FALSE );
/*N*/ 		}

/*N*/ 		if( !bXML && !ISA( SwGlobalDocShell ) && !ISA( SwWebDocShell ) &&
/*N*/ 			SFX_CREATE_MODE_EMBEDDED != GetCreateMode() )
/*N*/ 			AddXMLAsZipToTheStorage( *pStor );

        // TabellenBox Edit beenden!
/*N*/ 		if( pWrtShell )
/*N*/ 			pWrtShell->EndAllTblBoxEdit();

        // Modified-Flag merken und erhalten ohne den Link zu Callen
        // (fuer OLE; nach Anweisung von MM)
/*N*/ 		BOOL bIsModified = pDoc->IsModified();
/*N*/ 		Link aOldOLELnk( pDoc->GetOle2Link() );
/*N*/ 		pDoc->SetOle2Link( Link() );

            // SfxProgress unterdruecken, wenn man Embedded ist
/*N*/ 		SW_MOD()->SetEmbeddedLoadSave(
/*N*/ 							SFX_CREATE_MODE_EMBEDDED == GetCreateMode() );
/*N*/
/*N*/ 		WriterRef xWrt;
/*N*/ 		if( bXML )
/*N*/ 		{
/*?*/ 			::binfilter::GetXMLWriter( aEmptyStr, xWrt );
/*N*/ 		}
/*N*/ 		else
/*N*/ 		{
/*N*/ 			::binfilter::GetSw3Writer( aEmptyStr, xWrt );
/*N*/ 			((Sw3Writer*)&xWrt)->SetSw3Io( pIo, TRUE );
/*N*/ 		}

/*N*/         BOOL bLockedView;
/*N*/         if ( pWrtShell )
/*N*/         {
/*N*/             bLockedView = pWrtShell->IsViewLocked();
/*N*/             pWrtShell->LockView( TRUE );    //lock visible section
/*N*/         }
/*N*/
/*N*/ 		SwWriter aWrt( *pStor, *pDoc );
/*N*/ 		nErr = aWrt.Write( xWrt );
/*N*/
/*N*/         if ( pWrtShell )
/*N*/             pWrtShell->LockView( bLockedView );
/*N*/
/*N*/ 		if( bIsModified )
/*N*/ 			pDoc->SetModified();
/*N*/ 		pDoc->SetOle2Link( aOldOLELnk );
/*N*/
/*N*/ 		SW_MOD()->SetEmbeddedLoadSave( FALSE );
/*N*/ 	}
/*N*/ 	SetError( nErr ? nErr : nVBWarning );
/*N*/
/*N*/ 	return !IsError( nErr );
/*N*/ }

/*--------------------------------------------------------------------
    Beschreibung: Sichern aller Formate
 --------------------------------------------------------------------*/
//STRIP001 SwSrcView* lcl_GetSourceView( SwDocShell* pSh )
//STRIP001 {
//STRIP001 	// sind wir in der SourceView?
//STRIP001 	SfxViewFrame* pVFrame = SfxViewFrame::GetFirst( pSh );
//STRIP001 	SfxViewShell* pViewShell = pVFrame ? pVFrame->GetViewShell() : 0;
//STRIP001 	return PTR_CAST( SwSrcView, pViewShell);
//STRIP001 }

//STRIP001 BOOL SwDocShell::ConvertTo( SfxMedium& rMedium )
//STRIP001 {
//STRIP001 	RTL_LOGFILE_CONTEXT_AUTHOR( aLog, "SW", "JP93722",  "SwDocShell::ConvertTo" );
//STRIP001 	const SfxFilter* pFlt = rMedium.GetFilter();
//STRIP001 	if( !pFlt )
//STRIP001 		return FALSE;
//STRIP001
//STRIP001 	WriterRef xWriter;
//STRIP001 	SwIoSystem::GetWriter( pFlt->GetUserData(), xWriter );
//STRIP001 	if( !xWriter.Is() )
//STRIP001 	{ 	// Der Filter ist nicht vorhanden
//STRIP001 		InfoBox( 0,
//STRIP001 				 SW_RESSTR(STR_DLLNOTFOUND) ).Execute();
//STRIP001 		return FALSE;
//STRIP001 	}
//STRIP001     //#i3370# remove quick help to prevent saving of autocorrection suggestions
//STRIP001     if(pView)
//STRIP001         pView->GetEditWin().StopQuickHelp();
//STRIP001 	ULONG nVBWarning = 0;
//STRIP001 	if( pDoc->ContainsMSVBasic() )
//STRIP001 	{
//STRIP001 		BOOL bSave = pFlt->GetUserData().EqualsAscii( "CWW8" )
//STRIP001 			 && OFF_APP()->GetFilterOptions()->IsLoadWordBasicStorage();
//STRIP001
//STRIP001 		SvStorage* pStg;
//STRIP001 		if( xWriter->IsStgWriter() )
//STRIP001 			pStg = rMedium.GetStorage();
//STRIP001 		else
//STRIP001 			pStg = pIo->GetStorage();
//STRIP001 		SvxImportMSVBasic aTmp( *this, *pStg );
//STRIP001 		nVBWarning = aTmp.SaveOrDelMSVBAStorage( bSave,
//STRIP001 								String::CreateFromAscii("Macros") );
//STRIP001 		pDoc->SetContainsMSVBasic( bSave );
//STRIP001 	}
//STRIP001
//STRIP001 	// TabellenBox Edit beenden!
//STRIP001 	if( pWrtShell )
//STRIP001 		pWrtShell->EndAllTblBoxEdit();
//STRIP001
//STRIP001 	if( pFlt->GetUserData().EqualsAscii( "HTML") )
//STRIP001 	{
//STRIP001 		OfficeApplication* pOffApp = OFF_APP();
//STRIP001 		OfaHtmlOptions* pHtmlOpt = pOffApp->GetHtmlOptions();
//STRIP001         if( !pHtmlOpt->IsStarBasic() && pHtmlOpt->IsStarBasicWarning() && HasBasic() )
//STRIP001 		{
//STRIP001             Reference< XLibraryContainer > xLibCont(GetBasicContainer(), UNO_QUERY);
//STRIP001             Reference< XNameAccess > xLib;
//STRIP001             Sequence<rtl::OUString> aNames = xLibCont->getElementNames();
//STRIP001             const ::rtl::OUString* pNames = aNames.getConstArray();
//STRIP001             for(sal_Int32 nLib = 0; nLib < aNames.getLength(); nLib++)
//STRIP001             {
//STRIP001                 Any aLib = xLibCont->getByName(pNames[nLib]);
//STRIP001                 aLib >>= xLib;
//STRIP001                 if(xLib.is())
//STRIP001                 {
//STRIP001                     Sequence<rtl::OUString> aModNames = xLib->getElementNames();
//STRIP001                     if(aModNames.getLength())
//STRIP001                     {
//STRIP001                         SetError(WARN_SWG_HTML_NO_MACROS);
//STRIP001                         break;
//STRIP001                     }
//STRIP001                 }
//STRIP001             }
//STRIP001         }
//STRIP001 		UpdateDocInfoForSave();
//STRIP001 	}
//STRIP001
//STRIP001 	CalcLayoutForOLEObjects();	// format for OLE objets
//STRIP001
//STRIP001 	if( xWriter->IsStgWriter() &&
//STRIP001 		( xWriter->IsSw3Writer() ||
//STRIP001 		  pFlt->GetUserData().EqualsAscii( FILTER_XML ) ||
//STRIP001 	 	  pFlt->GetUserData().EqualsAscii( FILTER_XMLV ) ||
//STRIP001 	 	  pFlt->GetUserData().EqualsAscii( FILTER_XMLVW ) ) )
//STRIP001 	{
//STRIP001 		// eigenen Typ ermitteln
//STRIP001 		BYTE nMyType = 0;
//STRIP001 		if( ISA( SwWebDocShell) )
//STRIP001 			nMyType = 1;
//STRIP001 		else if( ISA( SwGlobalDocShell) )
//STRIP001 			nMyType = 2;
//STRIP001
//STRIP001 		// gewuenschten Typ ermitteln
//STRIP001 		BYTE nSaveType = 0;
//STRIP001 		ULONG nSaveClipId = pFlt->GetFormat();
//STRIP001 		if( SOT_FORMATSTR_ID_STARWRITERWEB_60 == nSaveClipId ||
//STRIP001 			SOT_FORMATSTR_ID_STARWRITERWEB_50 == nSaveClipId ||
//STRIP001 			SOT_FORMATSTR_ID_STARWRITERWEB_40 == nSaveClipId )
//STRIP001 			nSaveType = 1;
//STRIP001 		else if( SOT_FORMATSTR_ID_STARWRITERGLOB_60 == nSaveClipId ||
//STRIP001 				 SOT_FORMATSTR_ID_STARWRITERGLOB_50 == nSaveClipId ||
//STRIP001 				 SOT_FORMATSTR_ID_STARWRITERGLOB_40 == nSaveClipId )
//STRIP001 			nSaveType = 2;
//STRIP001
//STRIP001 		// Flags am Dokument entsprechend umsetzen
//STRIP001 		BOOL bIsHTMLModeSave = GetDoc()->IsHTMLMode();
//STRIP001 		BOOL bIsGlobalDocSave = GetDoc()->IsGlobalDoc();
//STRIP001 		BOOL bIsGlblDocSaveLinksSave = GetDoc()->IsGlblDocSaveLinks();
//STRIP001 		if( nMyType != nSaveType )
//STRIP001 		{
//STRIP001 			GetDoc()->SetHTMLMode( 1 == nSaveType );
//STRIP001 			GetDoc()->SetGlobalDoc( 2 == nSaveType );
//STRIP001 			if( 2 != nSaveType )
//STRIP001 				GetDoc()->SetGlblDocSaveLinks( FALSE );
//STRIP001 		}
//STRIP001
//STRIP001 		// Jetzt das Dokument normal speichern
//STRIP001 		BOOL bRet = SaveAs( rMedium.GetStorage() );
//STRIP001
//STRIP001 		if( nMyType != nSaveType )
//STRIP001 		{
//STRIP001 			GetDoc()->SetHTMLMode( bIsHTMLModeSave );
//STRIP001 			GetDoc()->SetGlobalDoc( bIsGlobalDocSave );
//STRIP001 			GetDoc()->SetGlblDocSaveLinks( bIsGlblDocSaveLinksSave );
//STRIP001 		}
//STRIP001
//STRIP001 		if( bRet && nMyType != nSaveType )
//STRIP001 		{
//STRIP001 			SvGlobalName aClassName;
//STRIP001 			ULONG nClipFormat;
//STRIP001 			String aAppName, aLongUserName, aUserName;
//STRIP001 			SfxObjectShellRef xDocSh;
//STRIP001 			switch( nSaveType )
//STRIP001 			{
//STRIP001 			case 0:
//STRIP001 				xDocSh = new SwDocShell( SFX_CREATE_MODE_INTERNAL );
//STRIP001 				break;
//STRIP001 			case 1:
//STRIP001 				xDocSh = new SwWebDocShell( SFX_CREATE_MODE_INTERNAL );
//STRIP001 				break;
//STRIP001 			case 2:
//STRIP001 				xDocSh = new SwGlobalDocShell( SFX_CREATE_MODE_INTERNAL );
//STRIP001 				break;
//STRIP001 			}
//STRIP001 			xDocSh->FillClass( &aClassName, &nClipFormat, &aAppName,
//STRIP001 								&aLongUserName, &aUserName,
//STRIP001 								pFlt->GetVersion() );
//STRIP001 			ASSERT( nClipFormat == nSaveClipId,
//STRIP001 					"FillClass hat falsche Clipboard-Id gesetzt" );
//STRIP001 			rMedium.GetStorage()->SetClass( aClassName, nClipFormat,
//STRIP001 											aUserName );
//STRIP001 		}
//STRIP001
//STRIP001 		return bRet;
//STRIP001 	}
//STRIP001
//STRIP001 	if( pFlt->GetUserData().EqualsAscii( FILTER_TEXT_DLG ) &&
//STRIP001 		( pWrtShell || !::lcl_GetSourceView( this ) ))
//STRIP001 	{
//STRIP001 		SwAsciiOptions aOpt;
//STRIP001 		String sItemOpt;
//STRIP001 		const SfxItemSet* pSet;
//STRIP001 		const SfxPoolItem* pItem;
//STRIP001 		if( 0 != ( pSet = rMedium.GetItemSet() ) )
//STRIP001 		{
//STRIP001 			if( SFX_ITEM_SET == pSet->GetItemState( SID_FILE_FILTEROPTIONS,
//STRIP001 													TRUE, &pItem ) )
//STRIP001 				sItemOpt = ((const SfxStringItem*)pItem)->GetValue();
//STRIP001 		}
//STRIP001         if(sItemOpt.Len())
//STRIP001             aOpt.ReadUserData( sItemOpt );
//STRIP001
//STRIP001 		xWriter->SetAsciiOptions( aOpt );
//STRIP001 	}
//STRIP001
//STRIP001 		// SfxProgress unterdruecken, wenn man Embedded ist
//STRIP001 	SW_MOD()->SetEmbeddedLoadSave(
//STRIP001 							SFX_CREATE_MODE_EMBEDDED == GetCreateMode());
//STRIP001
//STRIP001 	// Kontext aufspannen, um die Anzeige der Selektion zu unterbinden
//STRIP001 	ULONG nErrno;
//STRIP001 	String aFileName( rMedium.GetName() );
//STRIP001
//STRIP001 	//Keine View also das ganze Dokument!
//STRIP001 	if ( pWrtShell )
//STRIP001 	{
//STRIP001 		SwWait aWait( *this, TRUE );
//STRIP001 		pWrtShell->StartAllAction();
//STRIP001 		pWrtShell->Push();
//STRIP001 		SwWriter aWrt( rMedium, *pWrtShell, TRUE );
//STRIP001 		nErrno = aWrt.Write( xWriter, &aFileName );
//STRIP001 		//JP 16.05.97: falls der SFX uns die View waehrend des speicherns
//STRIP001 		//				entzieht
//STRIP001 		if( pWrtShell )
//STRIP001 		{
//STRIP001 			pWrtShell->Pop(FALSE);
//STRIP001 			pWrtShell->EndAllAction();
//STRIP001 		}
//STRIP001 	}
//STRIP001 	else
//STRIP001 	{
//STRIP001 		// sind wir in der SourceView?
//STRIP001 		SwSrcView* pSrcView = ::lcl_GetSourceView( this );
//STRIP001 		if( pSrcView )
//STRIP001 		{
//STRIP001 			pSrcView->SaveContentTo(rMedium);
//STRIP001 			nErrno = 0;
//STRIP001 		}
//STRIP001 		else
//STRIP001 		{
//STRIP001 			SwWriter aWrt( rMedium, *pDoc );
//STRIP001 			nErrno = aWrt.Write( xWriter, &aFileName );
//STRIP001 		}
//STRIP001 	}
//STRIP001
//STRIP001 	SW_MOD()->SetEmbeddedLoadSave( FALSE );
//STRIP001 	SetError( nErrno ? nErrno : nVBWarning );
//STRIP001 	if( !rMedium.IsStorage() )
//STRIP001 		rMedium.CloseOutStream();
//STRIP001
//STRIP001 	return !IsError( nErrno );
//STRIP001 }

/*--------------------------------------------------------------------
    Beschreibung:	Haende weg
 --------------------------------------------------------------------*/


/*N*/ void SwDocShell::HandsOff()
/*N*/ {
/*N*/ 	pIo->HandsOff();
/*N*/ 	SfxInPlaceObject::HandsOff();
/*N*/ }

/*--------------------------------------------------------------------
    Beschreibung: ??? noch nicht zu aktivieren, muss TRUE liefern
 --------------------------------------------------------------------*/


/*N*/ BOOL SwDocShell::SaveCompleted( SvStorage * pStor )
/*N*/ {
/*N*/ 	RTL_LOGFILE_CONTEXT_AUTHOR( aLog, "SW", "JP93722",  "SwDocShell::SaveCompleted" );
/*N*/ 	BOOL bRet = SfxInPlaceObject::SaveCompleted( pStor );
/*N*/ 	if( bRet )
/*N*/ 	{
/*N*/ 		// erst hier entscheiden, ob das Speichern geklappt hat oder nicht
/*N*/ 		if( IsModified() )
/*?*/ 			pDoc->SetModified();
/*N*/ 		else
/*N*/ 			pDoc->ResetModified();
/*N*/
/*N*/ 		bRet = pIo->SaveCompleted( pStor );
/*N*/ 	}

/*N*/ 	if( xOLEChildList.Is() )
/*N*/ 	{
/*N*/ 		BOOL bResetModified = IsEnableSetModified();
/*N*/ 		if( bResetModified )
/*N*/ 			EnableSetModified( FALSE );
/*N*/
/*N*/ 		SvPersist* pPersist = this;
/*N*/ 		const SvInfoObjectMemberList* pInfList = xOLEChildList->GetObjectList();
/*N*/
/*N*/ 		for( ULONG n = pInfList->Count(); n; )
/*N*/ 		{
/*N*/ 			SvInfoObjectRef aRef( pInfList->GetObject( --n ));
/*N*/ 			pPersist->Move( &aRef, aRef->GetStorageName() );
/*N*/ 		}
/*N*/
/*N*/ 		xOLEChildList.Clear();
/*N*/ 		if( bResetModified )
/*N*/ 			EnableSetModified( TRUE );
/*N*/ 	}
/*N*/ 	return bRet;
/*N*/ }

/*--------------------------------------------------------------------
    Beschreibung: Draw()-Overload fuer OLE2 (Sfx)
 --------------------------------------------------------------------*/

//STRIP001 void SwDocShell::Draw( OutputDevice* pDev, const JobSetup& rSetup,
//STRIP001 							   USHORT nAspect )
//STRIP001 {
//STRIP001 	//fix #25341# Draw sollte das Modified nicht beeinflussen
//STRIP001 	BOOL bResetModified;
//STRIP001 	if ( TRUE == (bResetModified = IsEnableSetModified()) )
//STRIP001 		EnableSetModified( FALSE );
//STRIP001
//STRIP001 	//sollte am Document ein JobSetup haengen, dann kopieren wir uns diesen,
//STRIP001 	//um nach dem PrtOle2 diesen wieder am Doc zu verankern.
//STRIP001 	//Einen leeren JobSetup setzen wir nicht ein, denn der wuerde nur zu
//STRIP001 	//fragwuerdigem Ergebnis nach teurer Neuformatierung fuehren (Preview!)
//STRIP001 	JobSetup *pOrig = 0;
//STRIP001 	if ( rSetup.GetPrinterName().Len() && ASPECT_THUMBNAIL != nAspect )
//STRIP001 	{
//STRIP001 		JobSetup* pOrig = (JobSetup*)pDoc->GetJobsetup();
//STRIP001 		if( pOrig )			// dann kopieren wir uns den
//STRIP001 			pOrig = new JobSetup( *pOrig );
//STRIP001 		pDoc->SetJobsetup( rSetup );
//STRIP001 	}
//STRIP001
//STRIP001 	Rectangle aRect( nAspect == ASPECT_THUMBNAIL ?
//STRIP001 			GetVisArea( nAspect ) : ((SvEmbeddedObject*)this)->GetVisArea() );
//STRIP001
//STRIP001 	pDev->Push();
//STRIP001 	pDev->SetFillColor();
//STRIP001 	pDev->SetLineColor();
//STRIP001 	pDev->SetBackground();
//STRIP001 	BOOL bWeb = 0 != PTR_CAST(SwWebDocShell, this);
//STRIP001     SwPrtOptions aOpts( aEmptyStr );
//STRIP001     ViewShell::PrtOle2( pDoc, SW_MOD()->GetUsrPref(bWeb), aOpts, pDev, aRect );
//STRIP001 	pDev->Pop();
//STRIP001
//STRIP001 	if( pOrig )
//STRIP001 	{
//STRIP001 		pDoc->SetJobsetup( *pOrig );
//STRIP001 		delete pOrig;
//STRIP001 	}
//STRIP001 	if ( bResetModified )
//STRIP001 		EnableSetModified( TRUE );
//STRIP001 }


/*N*/ void SwDocShell::SetVisArea( const Rectangle &rRect )
/*N*/ {
/*N*/ 	Rectangle aRect( rRect );
/*N*/ 	if ( pView )
/*N*/ 	{
/*?*/ 		Size aSz( pView->GetDocSz() );
/*?*/ 		aSz.Width() += DOCUMENTBORDER; aSz.Height() += DOCUMENTBORDER;
/*?*/ 		long nMoveX = 0, nMoveY = 0;
/*?*/ 		if ( aRect.Right() > aSz.Width() )
/*?*/ 			nMoveX = aSz.Width() - aRect.Right();
/*?*/ 		if ( aRect.Bottom() > aSz.Height() )
/*?*/ 			nMoveY = aSz.Height() - aRect.Bottom();
/*?*/ 		aRect.Move( nMoveX, nMoveY );
/*?*/ 		nMoveX = aRect.Left() < 0 ? -aRect.Left() : 0;
/*?*/ 		nMoveY = aRect.Top()  < 0 ? -aRect.Top()  : 0;
/*?*/ 		aRect.Move( nMoveX, nMoveY );
/*?*/
/*?*/ 		//Ruft das SfxInPlaceObject::SetVisArea()!
/*?*/ 		pView->SetVisArea( aRect, TRUE );
/*N*/ 	}
/*N*/ 	else
/*N*/ 		SfxInPlaceObject::SetVisArea( aRect );
/*N*/ }


/*N*/ Rectangle SwDocShell::GetVisArea( USHORT nAspect ) const
/*N*/ {
/*N*/ 	if ( nAspect == ASPECT_THUMBNAIL )
/*N*/ 	{
/*?*/ 		//PreView: VisArea auf die erste Seite einstellen.
/*?*/
/*?*/ 		//PageDesc besorgen, vom ersten Absatz oder den default.
/*?*/ 		SwNodeIndex aIdx( pDoc->GetNodes().GetEndOfExtras(), 1 );
/*?*/ 		SwCntntNode* pNd = pDoc->GetNodes().GoNext( &aIdx );
/*?*/ 		const SwFmtPageDesc &rDesc = pNd->GetSwAttrSet().GetPageDesc();
/*?*/ 		const SwPageDesc* pDesc = rDesc.GetPageDesc();
/*?*/ 		if( !pDesc )
/*?*/ 			pDesc = &pDoc->GetPageDesc( 0 );
/*?*/
/*?*/ 		//Das Format wird evtl. von der virtuellen Seitennummer bestimmt.
/*?*/ 		const USHORT nPgNum = rDesc.GetNumOffset();
/*?*/ 		const BOOL bOdd = nPgNum % 2 ? TRUE : FALSE;
/*?*/ 		const SwFrmFmt *pFmt = bOdd ? pDesc->GetRightFmt() : pDesc->GetLeftFmt();
/*?*/ 		if ( !pFmt ) //#40568#
/*?*/ 			pFmt = bOdd ? pDesc->GetLeftFmt() : pDesc->GetRightFmt();
/*?*/
/*?*/ 		if ( pFmt->GetFrmSize().GetWidth() == LONG_MAX )
/*?*/ 			//Jetzt wird es aber Zeit fuer die Initialisierung
/*?*/ 			pDoc->GetPrt( TRUE );
/*?*/
/*?*/ 		const SwFmtFrmSize& rFrmSz = pFmt->GetFrmSize();
/*?*/ 		const Size aSz( rFrmSz.GetWidth(), rFrmSz.GetHeight() );
/*?*/ 		const Point aPt( DOCUMENTBORDER, DOCUMENTBORDER );
/*?*/ 		const Rectangle aRect( aPt, aSz );
/*?*/ 		return aRect;
/*N*/ 	}
/*N*/ 	return SvEmbeddedObject::GetVisArea( nAspect );
/*N*/ }

/*N*/ Printer *SwDocShell::GetDocumentPrinter()
/*N*/ {
/*N*/ 	return pDoc->GetPrt();
/*N*/ }

/*N*/ OutputDevice* SwDocShell::GetDocumentRefDev()
/*N*/ {
/*N*/     return pDoc->_GetRefDev();
/*N*/ }

/*N*/ void SwDocShell::OnDocumentPrinterChanged( Printer * pNewPrinter )
/*N*/ {
/*N*/ 	if ( pNewPrinter )
/*N*/ 		GetDoc()->SetJobsetup( pNewPrinter->GetJobSetup() );
/*N*/ 	else
/*N*/ 		GetDoc()->SetPrt( 0 );
/*N*/ }

/*N*/ ULONG SwDocShell::GetMiscStatus() const
/*N*/ {
/*N*/ 	return SfxInPlaceObject::GetMiscStatus() |
/*N*/ 		   SVOBJ_MISCSTATUS_RESIZEONPRINTERCHANGE;
/*N*/ }


/*--------------------------------------------------------------------
    Beschreibung:
 --------------------------------------------------------------------*/


/*N*/ void SwDocShell::GetState(SfxItemSet& rSet)
/*N*/ {
/*N*/ 	SfxWhichIter aIter(rSet);
/*N*/ 	USHORT 	nWhich 	= aIter.FirstWhich();
/*N*/
/*N*/ 	while (nWhich)
/*N*/ 	{
/*N*/ 		switch (nWhich)
/*N*/ 		{
        // MT: MakroChosser immer enablen, weil Neu moeglich
        // case SID_BASICCHOOSER:
        // {
        // 	StarBASIC* pBasic = GetBasic();
        // 	StarBASIC* pAppBasic = SFX_APP()->GetBasic();
        // 	if ( !(pBasic->GetModules()->Count() ||
        // 		pAppBasic->GetModules()->Count()) )
        // 			rSet.DisableItem(nWhich);
        // }
        // break;
/*N*/ 		case SID_PRINTPREVIEW:
/*N*/ 		{
/*?*/ 			FASTBOOL bDisable = GetProtocol().IsInPlaceActive();
/*?*/ 			if ( !bDisable )
/*?*/ 			{
/*?*/ 				SfxViewFrame *pTmpFrm = SfxViewFrame::GetFirst(this);
/*?*/ 				while (pTmpFrm)		// Preview suchen
/*?*/ 				{
/*?*/ 					if ( PTR_CAST(SwView, pTmpFrm->GetViewShell()) &&
/*?*/ 						 ((SwView*)pTmpFrm->GetViewShell())->GetWrtShell().
/*?*/ 													GetDoc()->IsBrowseMode())
/*?*/ 					{
/*?*/ 						bDisable = TRUE;
/*?*/ 						break;
/*?*/ 					}
/*?*/ 					pTmpFrm = pTmpFrm->GetNext(*pTmpFrm, this);
/*?*/ 				}
/*?*/ 			}
/*?*/ 			if ( bDisable )
/*?*/ 				rSet.DisableItem( SID_PRINTPREVIEW );
/*?*/ 			else
/*?*/ 			{
/*?*/ 				SfxBoolItem aBool( SID_PRINTPREVIEW, FALSE );
/*?*/ 				if( PTR_CAST( SwPagePreView, SfxViewShell::Current()) )
/*?*/ 					aBool.SetValue( TRUE );
/*?*/ 				rSet.Put( aBool );
/*?*/ 			}
/*?*/ 		}
/*?*/ 		break;
/*N*/ 		case SID_SOURCEVIEW:
/*N*/ 		{
/*?*/ 			if(IsLoading())
/*?*/ 				rSet.DisableItem(nWhich);
/*?*/ 			else
/*?*/ 			{
/*?*/ 				SfxViewShell* pView = GetView() ? (SfxViewShell*)GetView()
/*?*/ 											: SfxViewShell::Current();
/*?*/ 				BOOL bSourceView = 0 != PTR_CAST(SwSrcView, pView);
/*?*/ 				rSet.Put(SfxBoolItem(SID_SOURCEVIEW, bSourceView));
/*?*/ 			}
/*?*/ 		}
/*?*/ 		break;
/*?*/ 		case SID_HTML_MODE:
/*?*/ 			rSet.Put(SfxUInt16Item(SID_HTML_MODE, ::binfilter::GetHtmlMode(this)));
/*?*/ 		break;
/*?*/
/*?*/ 		case FN_ABSTRACT_STARIMPRESS:
/*?*/ 		case FN_OUTLINE_TO_IMPRESS:
/*?*/ 			{
/*?*/ 				SvtModuleOptions aMOpt;
/*?*/ 				if ( !aMOpt.IsImpress() )
/*?*/ 					rSet.DisableItem( nWhich );
/*?*/ 			}
/*?*/ 			/* no break here */
/*?*/ 		case FN_ABSTRACT_NEWDOC:
/*?*/ 		case FN_OUTLINE_TO_CLIPBOARD:
/*?*/ 			{
/*?*/ 				if ( !GetDoc()->GetNodes().GetOutLineNds().Count() )
/*?*/ 					rSet.DisableItem( nWhich );
/*?*/ 			}
/*?*/ 			break;
/*?*/
/*?*/ 		case SID_BROWSER_MODE:
/*?*/ 			{
/*N*/ 				SfxViewShell* pViewShell = SfxViewShell::Current();
/*N*/ 				BOOL bDisable = PTR_CAST(SwPagePreView, pViewShell) != 0;
/*N*/
/*N*/ 				if (bDisable)
/*?*/ 					rSet.DisableItem( nWhich );
/*N*/ 				else
/*N*/ 					rSet.Put( SfxBoolItem( nWhich, GetDoc()->IsBrowseMode()));
/*N*/ 				break;
/*?*/ 			}
/*?*/ 		case FN_PRINT_LAYOUT:
/*?*/ 			{
/*?*/ 				SfxViewShell* pViewShell = SfxViewShell::Current();
/*?*/ 				BOOL bDisable = 0 != PTR_CAST(SwPagePreView, pViewShell) ||
/*?*/ 								0 != PTR_CAST(SwSrcView, pViewShell);
/*?*/ 				if (bDisable)
/*?*/ 					rSet.DisableItem( nWhich );
/*?*/ 				else
/*?*/ 					rSet.Put( SfxBoolItem( nWhich, !GetDoc()->IsBrowseMode()));
/*?*/ 			}
/*?*/ 			break;
/*?*/
/*?*/ 		case FN_NEW_GLOBAL_DOC:
/*?*/ 			if ( ISA(SwGlobalDocShell) )
/*?*/ 				rSet.DisableItem( nWhich );
/*?*/ 			break;
/*?*/
/*?*/ 		case FN_NEW_HTML_DOC:
/*?*/ 			if( ISA( SwWebDocShell ) )
/*?*/ 				rSet.DisableItem( nWhich );
/*?*/ 			break;
/*?*/
/*?*/ 		case SID_ATTR_YEAR2000:
/*?*/ 			{
/*?*/ 			DBG_BF_ASSERT(0, "STRIP"); //STRIP001 	const SvNumberFormatter* pFmtr = pDoc->GetNumberFormatter(FALSE);
//STRIP001 /*?*/ 				rSet.Put( SfxUInt16Item( nWhich,
//STRIP001 /*?*/ 						pFmtr ? pFmtr->GetYear2000()
//STRIP001 /*?*/ 							  :	SFX_APP()->GetMiscConfig()->GetYear2000() ));
/*?*/ 			}
/*?*/ 			break;
/*?*/
/*?*/ 		default: DBG_ASSERT(!this,"Hier darfst Du nicht hinein!");
/*?*/
/*?*/ 		}
/*N*/ 		nWhich = aIter.NextWhich();
/*N*/ 	}
/*N*/ }

/*--------------------------------------------------------------------
    Beschreibung:	OLE-Hdls
 --------------------------------------------------------------------*/


/*N*/ IMPL_LINK( SwDocShell, Ole2ModifiedHdl, void *, p )
/*N*/ {
/*N*/ 	// vom Doc wird der Status mitgegeben (siehe doc.cxx)
/*N*/ 	// 	Bit 0:	-> alter Zustand
/*N*/ 	//	Bit 1: 	-> neuer Zustand
/*N*/ 	long nStatus = (long)p;
/*N*/ 	if( IsEnableSetModified() )
/*N*/ 		SetModified( (nStatus & 2) ? TRUE : FALSE );
/*N*/ 	return 0;
/*N*/ }

/*--------------------------------------------------------------------
    Beschreibung:	Pool returnen Hier weil virtuelll
 --------------------------------------------------------------------*/


/*N*/ SfxStyleSheetBasePool*	SwDocShell::GetStyleSheetPool()
/*N*/ {
/*N*/ 	return pBasePool;
/*N*/ }


/*N*/ void SwDocShell::SetView(SwView* pVw)
/*N*/ {
/*N*/ 	if ( 0 != (pView = pVw) )
/*N*/ 		pWrtShell = &pView->GetWrtShell();
/*N*/ 	else
/*N*/ 		pWrtShell = 0;
/*N*/ }


//STRIP001 void SwDocShell::PrepareReload()
//STRIP001 {
//STRIP001 	::DelAllGrfCacheEntries( pDoc );
//STRIP001 }


/*N*/ void SwDocShell::StartLoadFinishedTimer()
/*N*/ {
/*N*/ 	BOOL bSttTimer = FALSE;
    // ohne WrtShell haben wir eine WebDocShell und muessen uns die
    // Optionen vom Modul holen
/*N*/ 	if( pWrtShell ? pWrtShell->GetViewOptions()->IsGraphic()
/*N*/ 				  :	SW_MOD()->GetUsrPref(TRUE)->IsGraphic() )
/*N*/ 	{
/*N*/ 		const SvxLinkManager& rLnkMgr = pDoc->GetLinkManager();
/*N*/ 		const ::so3::SvBaseLinks& rLnks = rLnkMgr.GetLinks();
/*N*/ 		for( USHORT n = 0; n < rLnks.Count(); ++n )
/*N*/ 		{
/*N*/ 			::so3::SvBaseLink* pLnk = &(*rLnks[ n ]);
/*N*/ 			if( pLnk && OBJECT_CLIENT_GRF == pLnk->GetObjType() &&
/*N*/ 				pLnk->ISA( SwBaseLink ) )
/*N*/ 			{
/*N*/ 				::so3::SvLinkSource* pLnkObj = pLnk->GetObj();
/*N*/ 				if( !pLnkObj )
/*N*/ 				{
/*N*/ 					String sFileNm;
/*N*/ 					if( rLnkMgr.GetDisplayNames( pLnk, 0, &sFileNm, 0, 0 ))
/*N*/ 					{
/*N*/ 						INetURLObject aURL( sFileNm );
/*N*/ 						switch( aURL.GetProtocol() )
/*N*/ 						{
/*N*/ 						case INET_PROT_NOT_VALID:
/*N*/ 						case INET_PROT_FILE:
/*N*/ 						case INET_PROT_MAILTO:
/*N*/ 						case INET_PROT_NEWS:
/*N*/ 						case INET_PROT_CID:
/*N*/ 							break;
/*N*/
/*N*/ 						default:
/*?*/ 							((SwBaseLink*)pLnk)->SwapIn();
/*?*/ 							((SwBaseLink*)pLnk)->GetCntntNode()->SetAutoFmtLvl(1);
/*?*/ 							bSttTimer = TRUE;
/*N*/ 							break;
/*N*/ 						}
/*N*/ 					}
/*N*/ 				}
/*N*/ 				else
/*N*/ 				{
/*N*/ 					BOOL bSendState = FALSE;
/*N*/ 					if( pLnkObj->IsPending() )
/*N*/ 						bSttTimer = TRUE;		// Pending?
/*N*/ 					else if( !pLnkObj->IsDataComplete() )
/*N*/ 					{
/*N*/ 						// falls aber nicht angetickert werden muss (liegt
/*N*/ 						// im QuickdrawCache)
/*N*/ 						if( !((SwBaseLink*)pLnk)->IsShowQuickDrawBmp() )
/*N*/ 						{
/*N*/ 							((SwBaseLink*)pLnk)->SwapIn();
/*N*/ 							((SwBaseLink*)pLnk)->GetCntntNode()->SetAutoFmtLvl(1);
/*N*/ 							bSttTimer = TRUE;
/*N*/ 						}
/*N*/ 						else
/*N*/ 							// dann muss aber auf jedenfall der Status
/*N*/ 							// an die Handler verschickt werden!
/*N*/ 							bSendState = TRUE;
/*N*/ 					}
/*N*/ 					else if( ((SwBaseLink*)pLnk)->IsShowQuickDrawBmp() )
/*N*/ 						// Wenn die Grafik aus dem QuickDrawCache kommt,
/*N*/ 						// wird sie nie angefordert!
/*N*/ 						// Dann muss aber auf jedenfall der Status
/*N*/ 						// an die Handler verschickt werden!
/*N*/ 						bSendState = TRUE;
/*N*/
/*N*/ 					if( bSendState )
/*N*/ 					{
/*?*/ 						::com::sun::star::uno::Any aValue;
/*?*/ 						aValue <<= ::rtl::OUString::valueOf(
/*?*/ 											(sal_Int32)STATE_LOAD_OK );
/*?*/ 						String sMimeType( SotExchange::GetFormatMimeType(
/*?*/ 							SvxLinkManager::RegisterStatusInfoId() ));
/*?*/ 						pLnkObj->DataChanged( sMimeType, aValue );
/*N*/ 					}
/*N*/ 				}
/*N*/ 			}
/*N*/ 		}
/*N*/ 	}
/*N*/
/*N*/ 	if( bSttTimer )
/*N*/ 	{
/*N*/ 		aFinishedTimer.SetTimeoutHdl( STATIC_LINK( this, SwDocShell, IsLoadFinished ));
/*N*/ 		aFinishedTimer.SetTimeout( 1000 );
/*N*/ 		aFinishedTimer.Start();
/*N*/ 		GetDoc()->StopIdleTimer();
/*N*/ 	}
/*N*/ 	FinishedLoading( SFX_LOADED_MAINDOCUMENT |
/*N*/ 					( bSttTimer ? 0 : SFX_LOADED_IMAGES ));
    // jetzt noch testen, ob die SourceView noch geladen werden muss
/*N*/ 	SfxViewFrame* pVFrame = SfxViewFrame::GetFirst(this);
/*N*/ 	if(pVFrame)
/*N*/ 	{
/*?*/ 		DBG_BF_ASSERT(0, "STRIP"); //STRIP001 SfxViewShell* pShell = pVFrame->GetViewShell();
//STRIP001 /*?*/ 		if(PTR_CAST(SwSrcView, pShell))
//STRIP001 /*?*/ 			((SwSrcView*)pShell)->Load(this);
/*N*/ 	}
/*N*/ }


/*N*/ IMPL_STATIC_LINK( SwDocShell, IsLoadFinished, void*, EMPTYARG )
/*N*/ {
/*N*/ 	BOOL bSttTimer = FALSE;
/*N*/
/*N*/ 	if( !pThis->IsAbortingImport() )
/*N*/ 	{
/*N*/ 		const SvxLinkManager& rLnkMgr = pThis->pDoc->GetLinkManager();
/*N*/ 		const ::so3::SvBaseLinks& rLnks = rLnkMgr.GetLinks();
/*N*/ 		for( USHORT n = rLnks.Count(); n; )
/*N*/ 		{
/*N*/ 			::so3::SvBaseLink* pLnk = &(*rLnks[ --n ]);
/*N*/ 			if( pLnk && OBJECT_CLIENT_GRF == pLnk->GetObjType() &&
/*N*/ 				pLnk->ISA( SwBaseLink ) )
/*N*/ 			{
/*N*/ 				::so3::SvLinkSource* pLnkObj = pLnk->GetObj();
/*N*/ 				if( pLnkObj && pLnkObj->IsPending() &&
/*N*/ 					!((SwBaseLink*)pLnk)->IsShowQuickDrawBmp() )
/*N*/ 				{
/*?*/ 					bSttTimer = TRUE;
/*?*/ 					break;
/*N*/ 				}
/*N*/ 			}
/*N*/ 		}
/*N*/ 	}

/*N*/ 	if( bSttTimer )
/*?*/ 		pThis->aFinishedTimer.Start();
/*N*/ 	else
/*N*/ 	{
/*N*/ 		BOOL bIsModifiedEnabled = pThis->IsEnableSetModified();
/*N*/ 		pThis->EnableSetModified( FALSE );
/*N*/ 		pThis->FinishedLoading( SFX_LOADED_MAINDOCUMENT | SFX_LOADED_IMAGES );
/*N*/ 		pThis->EnableSetModified( bIsModifiedEnabled );
/*N*/
/*N*/ 		pThis->GetDoc()->StartIdleTimer();
/*N*/ 	}
/*N*/ 	return 0;
/*N*/ }


// eine Uebertragung wird abgebrochen (wird aus dem SFX gerufen)
/*N*/ void SwDocShell::CancelTransfers()
/*N*/ {
/*N*/ 	// alle Links vom LinkManager Canceln
/*N*/ 	aFinishedTimer.Stop();
/*N*/ 	pDoc->GetLinkManager().CancelTransfers();
/*N*/ 	SfxObjectShell::CancelTransfers();
/*N*/ }

//STRIP001 SwFEShell* SwDocShell::GetFEShell()
//STRIP001 {
//STRIP001 	return pWrtShell;
//STRIP001 }

    // embedded alle lokalen Links (Bereiche/Grafiken)
//STRIP001 BOOL SwDocShell::EmbedAllLinks()
//STRIP001 {
//STRIP001 	if( pWrtShell )
//STRIP001 		return pWrtShell->EmbedAllLinks();
//STRIP001 	return pDoc->EmbedAllLinks();
//STRIP001 }


/*N*/ void SwDocShell::RemoveOLEObjects()
/*N*/ {
/*N*/ 	SvPersist* pPersist = this;
/*N*/ 	SwClientIter aIter( *(SwModify*)pDoc->GetDfltGrfFmtColl() );
/*N*/ 	for( SwCntntNode* pNd = (SwCntntNode*)aIter.First( TYPE( SwCntntNode ) );
/*N*/ 			pNd; pNd = (SwCntntNode*)aIter.Next() )
/*N*/ 	{
/*N*/ 		SwOLENode* pOLENd = pNd->GetOLENode();
/*N*/ 		if( pOLENd && ( pOLENd->IsOLEObjectDeleted() ||
/*N*/ 						pOLENd->IsInGlobalDocSection() ) )
/*N*/ 		{
/*N*/ 			SvInfoObjectRef aRef( pPersist->Find(
/*N*/ 									pOLENd->GetOLEObj().GetName() ) );
/*N*/ 			if( aRef.Is() )
/*N*/ 			{
/*N*/ 				if( !xOLEChildList.Is() )
/*N*/ 				{
/*N*/ 					xOLEChildList = new SwTmpPersist( *this );
/*N*/ 					xOLEChildList->DoInitNew( 0 );
/*N*/ 				}
/*N*/
/*N*/                 xOLEChildList->Move( &aRef, aRef->GetStorageName(), TRUE );
/*N*/ 				pPersist->Remove( &aRef );
/*N*/ 			}
/*N*/ 		}
/*N*/ 	}
/*N*/ }

// When a document is loaded, SwDoc::PrtOLENotify is called to update
// the sizes of math objects. However, for objects that do not have a
// SwFrm at this time, only a flag is set (bIsOLESizeInvalid) and the
// size change takes place later, while calculating the layout in the
// idle handler. If this document is saved now, it is saved with invalid
// sizes. For this reason, the layout has to be calculated before a document is
// saved, but of course only id there are OLE objects with bOLESizeInvalid set.
/*N*/ void SwDocShell::CalcLayoutForOLEObjects()
/*N*/ {
/*N*/ 	if( !pWrtShell )
/*N*/ 		return;
/*N*/
/*N*/ 	SwClientIter aIter( *(SwModify*)pDoc->GetDfltGrfFmtColl() );
/*N*/ 	for( SwCntntNode* pNd = (SwCntntNode*)aIter.First( TYPE( SwCntntNode ) );
/*N*/ 			pNd; pNd = (SwCntntNode*)aIter.Next() )
/*N*/ 	{
/*N*/ 		SwOLENode* pOLENd = pNd->GetOLENode();
/*N*/ 		if( pOLENd && pOLENd->IsOLESizeInvalid() )
/*N*/ 		{
/*N*/ 			pWrtShell->CalcLayout();
/*N*/ 			break;
/*N*/ 		}
/*N*/ 	}
/*N*/ }
/* -----------------------------12.02.01 12:08--------------------------------

 ---------------------------------------------------------------------------*/
/*N*/ #if SUPD>620
/*N*/ Sequence< OUString >	SwDocShell::GetEventNames()
/*N*/ {
/*N*/ 	Sequence< OUString > aRet = SfxObjectShell::GetEventNames();
/*N*/ 	sal_Int32 nLen = aRet.getLength();
/*N*/ 	aRet.realloc(nLen + 2);
/*N*/ 	OUString* pNames = aRet.getArray();
/*N*/ 	pNames[nLen++] = OUString::createFromAscii("OnMailMerge");
/*N*/ 	pNames[nLen] = OUString::createFromAscii("OnPageCountChange");
/*N*/ 	return aRet;
/*N*/ }
/*N*/ #endif
/*N*/ void SwTmpPersist::FillClass( SvGlobalName * pClassName,
/*N*/ 							ULONG * pClipFormat,
/*N*/ 							String * pAppName,
/*N*/ 							String * pLongUserName,
/*N*/ 							String * pUserName,
/*N*/ 							long nFileFormat ) const
/*N*/ {
/*N*/ 	pDShell->SwDocShell::FillClass( pClassName, pClipFormat, pAppName,
/*N*/ 									pLongUserName, pUserName, nFileFormat );
/*N*/ }

/*N*/ BOOL SwTmpPersist::Save()
/*N*/{
/*N*/	if( SaveChilds() )
/*N*/		return SvPersist::Save();
/*N*/	return FALSE;
/*N*/}

/*N*/ BOOL SwTmpPersist::SaveCompleted( SvStorage * pStor )
/*N*/{
/*N*/	if( SaveCompletedChilds( pStor ) )
/*N*/		return SvPersist::SaveCompleted( pStor );
/*N*/	return FALSE;
/*N*/}



}
