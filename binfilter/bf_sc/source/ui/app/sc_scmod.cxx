/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: sc_scmod.cxx,v $
 *
 *  $Revision: 1.10 $
 *
 *  last change: $Author: obo $ $Date: 2007-07-17 09:15:25 $
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

#ifndef _COM_SUN_STAR_UI_DIALOGS_XEXECUTABLEDIALOG_HPP_
#include <com/sun/star/ui/dialogs/XExecutableDialog.hpp>
#endif
#ifndef _COMPHELPER_PROCESSFACTORY_HXX_
#include <comphelper/processfactory.hxx>
#endif

// INCLUDE ---------------------------------------------------------------

#include "scitems.hxx"

#include <bf_svx/eeitem.hxx>
#define ITEMID_FIELD EE_FEATURE_FIELD

#ifndef _PSTM_HXX
#include <tools/pstm.hxx>
#endif

#ifndef _SFXPOOLITEM_HXX
#include <svtools/poolitem.hxx>
#endif

#ifndef _SVX_ITEMDATA_HXX
#include <bf_svx/itemdata.hxx>
#endif

#ifndef _DATE_HXX
#include <tools/date.hxx>
#endif

#ifndef _TOOLS_TIME_HXX
#include <tools/time.hxx>
#endif

#include <bf_svx/flditem.hxx>
#include <bf_svx/outliner.hxx>
#include "bf_basic/sbstar.hxx"

#include <svtools/ehdl.hxx>
#include <svtools/accessibilityoptions.hxx>
#include <svtools/ctloptions.hxx>
#include <vcl/status.hxx>
#include <bf_sfx2/request.hxx>

#include <bf_sfx2/macrconf.hxx>
#include <bf_sfx2/printer.hxx>
#include <bf_svx/langitem.hxx>
#include <svtools/colorcfg.hxx>

#include <svtools/whiter.hxx>
#include <bf_offmgr/app.hxx>
#include <vcl/msgbox.hxx>
#include <bf_offmgr/ofaids.hrc>
#include <svtools/inethist.hxx>
#include <vcl/waitobj.hxx>

#define ITEMID_SPELLCHECK 0

#include "scmod.hxx"
#include "global.hxx"
#include "viewopti.hxx"
#include "docoptio.hxx"
#include "appoptio.hxx"
#include "inputopt.hxx"
#include "printopt.hxx"
#include "navicfg.hxx"
#include "docsh.hxx"
#include "drwlayer.hxx"
#include "uiitems.hxx"
#include "bf_sc.hrc"
#include "cfgids.hxx"

#include "msgpool.hxx"
#include "scresid.hxx"
#include "teamdlg.hxx"
#include "formdata.hxx"
#include "tpusrlst.hxx"
#include "tpcalc.hxx"
#include "tpprint.hxx"
#include "transobj.hxx"
#include "detfunc.hxx"

#ifndef _LEGACYBINFILTERMGR_HXX
#include <legacysmgr/legacy_binfilters_smgr.hxx>	//STRIP002
#endif
#define SC_IDLE_MIN		150
#define SC_IDLE_MAX		3000
#define SC_IDLE_STEP	75
#define SC_IDLE_COUNT	50
namespace binfilter {

static USHORT nIdleCount = 0;

//------------------------------------------------------------------

/*N*/ ScModule::ScModule( SfxObjectFactory* pFact ) :
/*N*/ 	ScModuleDummy( SFX_APP()->CreateResManager( "bf_sc" ), FALSE, pFact ), //STRIP005
/*N*/ 	bIsWaterCan( FALSE ),
/*N*/ 	bIsInEditCommand( FALSE ),
/*N*/ 	pRefInputHandler( NULL ),
/*N*/ 	pViewCfg( NULL ),
/*N*/ 	pDocCfg( NULL ),
/*N*/ 	pAppCfg( NULL ),
/*N*/ 	pInputCfg( NULL ),
/*N*/ 	pPrintCfg( NULL ),
/*N*/ 	pNavipiCfg( NULL ),
/*N*/ 	pColorConfig( NULL ),
/*N*/ 	pAccessOptions( NULL ),
/*N*/ 	pCTLOptions( NULL ),
/*N*/ 	pTeamDlg( NULL ),
/*N*/ 	nCurRefDlgId( 0 ),
/*N*/ 	pErrorHdl( NULL ),
/*N*/ 	pSvxErrorHdl( NULL ),
/*N*/ 	pMessagePool( NULL ),
/*N*/ 	pFormEditData( NULL )
/*N*/ {
/*N*/ 	//	im ctor ist der ResManager (DLL-Daten) noch nicht initialisiert!
/*N*/
/*N*/ 	SetName(String::CreateFromAscii(RTL_CONSTASCII_STRINGPARAM("StarCalc")));		// fuer Basic
/*N*/
/*N*/ 	ResetDragObject();
/*N*/ 	SetClipObject( NULL, NULL );
/*N*/
/*N*/ 	//	InputHandler braucht nicht mehr angelegt zu werden
/*N*/
/*N*/ 	//	ErrorHandler anlegen - war in Init()
/*N*/ 	//	zwischen OfficeApplication::Init und ScGlobal::Init
/*N*/ //	pSvxErrorHdl = new SvxErrorHandler();
/*N*/ 	pErrorHdl	 = new SfxErrorHandler( RID_ERRHDLSC,
/*N*/ 										ERRCODE_AREA_SC,
/*N*/ 										ERRCODE_AREA_APP2-1,
/*N*/ 										GetResMgr() );
/*N*/
/*N*/ 	aSpellTimer.SetTimeout(10);
/*N*/ 	aSpellTimer.SetTimeoutHdl( LINK( this, ScModule, SpellTimerHdl ) );
/*N*/ 	aIdleTimer.SetTimeout(SC_IDLE_MIN);
/*N*/ 	aIdleTimer.SetTimeoutHdl( LINK( this, ScModule, IdleHandler ) );
/*N*/ 	aIdleTimer.Start();
/*N*/
/*N*/ 	pMessagePool = new ScMessagePool;
/*N*/ 	pMessagePool->FreezeIdRanges();
/*N*/ 	SetPool( pMessagePool );
/*N*/ 	ScGlobal::InitTextHeight( pMessagePool );
/*N*/
/*N*/ 	StartListening( *SFX_APP() );		// for SFX_HINT_DEINITIALIZING
/*N*/ }

/*N*/ ScModule::~ScModule()
/*N*/ {
/*N*/ 	DELETEZ( pMessagePool );
/*N*/
/*N*/ 	DELETEZ( pFormEditData );
/*N*/
/*N*/ 	delete pErrorHdl;
/*N*/ //	delete pSvxErrorHdl;
/*N*/
/*N*/ 	ScGlobal::Clear();		// ruft auch ScDocumentPool::DeleteVersionMaps();
/*N*/
/*N*/ 	DeleteCfg();			// wurde mal aus Exit() gerufen
/*N*/ }

//------------------------------------------------------------------

/*N*/ void ScModule::Notify( SfxBroadcaster& rBC, const SfxHint& rHint )
/*N*/ {
/*N*/ 	if ( rHint.ISA(SfxSimpleHint) )
/*N*/ 	{
/*N*/         ULONG nHintId = ((SfxSimpleHint&)rHint).GetId();
/*N*/         if ( nHintId == SFX_HINT_DEINITIALIZING )
/*N*/ 		{
/*N*/ 			//	ConfigItems must be removed before ConfigManager
/*N*/ 			DeleteCfg();
/*N*/ 		}
/*N*/ 		else if ( nHintId == SFX_HINT_COLORS_CHANGED || nHintId == SFX_HINT_ACCESSIBILITY_CHANGED )
/*N*/ 		{
/*?*/ 		DBG_BF_ASSERT(0, "STRIP"); //STRIP001 	if ( ScDetectiveFunc::IsColorsInitialized() )
/*N*/ 		}
/*N*/         else if ( nHintId == SFX_HINT_CTL_SETTINGS_CHANGED )
/*N*/         {DBG_BF_ASSERT(0, "STRIP"); //STRIP001
/*N*/         }
/*N*/ 	}
/*N*/ }

//------------------------------------------------------------------

/*N*/ void ScModule::DeleteCfg()
/*N*/ {
/*N*/ 	DELETEZ( pViewCfg ); // Speichern passiert vor Exit() automatisch
/*N*/ 	DELETEZ( pDocCfg );
/*N*/ 	DELETEZ( pAppCfg );
/*N*/ 	DELETEZ( pInputCfg );
/*N*/ 	DELETEZ( pPrintCfg );
/*N*/ 	DELETEZ( pNavipiCfg );
/*N*/
/*N*/ 	if ( pColorConfig )
/*N*/ 	{
/*N*/ 	    EndListening(*pColorConfig);
/*N*/ 		DELETEZ( pColorConfig );
/*N*/ 	}
/*N*/ 	if ( pAccessOptions )
/*N*/ 	{
/*N*/ 	    EndListening(*pAccessOptions);
/*N*/ 		DELETEZ( pAccessOptions );
/*N*/ 	}
/*N*/ 	if ( pCTLOptions )
/*N*/ 	{
/*N*/ 	    EndListening(*pCTLOptions);
/*N*/ 		DELETEZ( pCTLOptions );
/*N*/ 	}
/*N*/ }

//------------------------------------------------------------------

/*N*/ SfxModule* ScModule::Load()
/*N*/ {
/*N*/ 	return this;					// ist schon geladen
/*N*/ }

/*N*/ SfxModule* ScModuleDummy::Load()
/*N*/ {
/*N*/ 	return NULL;					// Dummy zum Linken der DLL, wird nicht gerufen
/*N*/ }

//------------------------------------------------------------------

#define TEXT_WIDTH(s)	rStatusBar.GetTextWidth((s))

/*N*/ void ScModule::FillStatusBar(StatusBar& rStatusBar)
/*N*/ {
/*N*/ }

#undef TEXT_WIDTH

//------------------------------------------------------------------
//
//		von der Applikation verschoben:
//
//------------------------------------------------------------------

/*N*/ void ScModule::ResetDragObject()
/*N*/ {
/*N*/ 	aDragData.pCellTransfer = NULL;
/*N*/ 	aDragData.pDrawTransfer = NULL;
/*N*/
/*N*/ 	aDragData.aLinkDoc.Erase();
/*N*/ 	aDragData.aLinkTable.Erase();
/*N*/ 	aDragData.aLinkArea.Erase();
/*N*/ 	aDragData.pJumpLocalDoc = NULL;
/*N*/ 	aDragData.aJumpTarget.Erase();
/*N*/ 	aDragData.aJumpText.Erase();
/*N*/ }

//------------------------------------------------------------------

/*N*/ void ScModule::SetClipObject( ScTransferObj* pCellObj, ScDrawTransferObj* pDrawObj )
/*N*/ {
/*N*/ 	DBG_ASSERT( !pCellObj || !pDrawObj, "SetClipObject: not allowed to set both objects" );
/*N*/
/*N*/ 	aClipData.pCellClipboard = pCellObj;
/*N*/ 	aClipData.pDrawClipboard = pDrawObj;
/*N*/ }

/*N*/ ScDocument* ScModule::GetClipDoc()
/*N*/ {
DBG_BF_ASSERT(0, "STRIP"); //STRIP001 //STRIP001 	//	called from document
/*N*/ 	return NULL;
/*N*/ }


/*N*/ const ScViewOptions& ScModule::GetViewOptions()
/*N*/ {
/*N*/ 	if ( !pViewCfg )
/*N*/ 		pViewCfg = new ScViewCfg;
/*N*/
/*N*/ 	return *pViewCfg;
/*N*/ }


/*N*/ const ScDocOptions& ScModule::GetDocOptions()
/*N*/ {
/*N*/ 	if ( !pDocCfg )
/*N*/ 		pDocCfg = new ScDocCfg;
/*N*/
/*N*/ 	return *pDocCfg;
/*N*/ }

#ifndef	LRU_MAX
#define LRU_MAX 10
#endif


/*N*/ void ScModule::RecentFunctionsChanged()
/*N*/ {
/*?*/	DBG_BF_ASSERT(0, "STRIP");
/*N*/ }

/*N*/ void ScModule::SetAppOptions( const ScAppOptions& rOpt )
/*N*/ {
/*N*/ 	if ( !pAppCfg )
/*N*/ 		pAppCfg = new ScAppCfg;
/*N*/
/*N*/ 	pAppCfg->SetOptions( rOpt );
/*N*/ }

/*N*/ void global_InitAppOptions()
/*N*/ {
/*N*/ 	SC_MOD()->GetAppOptions();
/*N*/ }

/*N*/ const ScAppOptions& ScModule::GetAppOptions()
/*N*/ {
/*N*/ 	if ( !pAppCfg )
/*N*/ 		pAppCfg = new ScAppCfg;
/*N*/
/*N*/ 	return *pAppCfg;
/*N*/ }

/*N*/ void ScModule::SetInputOptions( const ScInputOptions& rOpt )
/*N*/ {
/*N*/ 	if ( !pInputCfg )
/*N*/ 		pInputCfg = new ScInputCfg;
/*N*/
/*N*/ 	pInputCfg->SetOptions( rOpt );
/*N*/ }

/*N*/ const ScInputOptions& ScModule::GetInputOptions()
/*N*/ {
/*N*/ 	if ( !pInputCfg )
/*N*/ 		pInputCfg = new ScInputCfg;
/*N*/
/*N*/ 	return *pInputCfg;
/*N*/ }

/*N*/ void ScModule::SetPrintOptions( const ScPrintOptions& rOpt )
/*N*/ {
/*N*/ 	if ( !pPrintCfg )
/*N*/ 		pPrintCfg = new ScPrintCfg;
/*N*/
/*N*/ 	pPrintCfg->SetOptions( rOpt );
/*N*/ }

/*N*/ const ScPrintOptions& ScModule::GetPrintOptions()
/*N*/ {
/*N*/ 	if ( !pPrintCfg )
/*N*/ 		pPrintCfg = new ScPrintCfg;
/*N*/
/*N*/ 	return *pPrintCfg;
/*N*/ }

/*N*/ svtools::ColorConfig& ScModule::GetColorConfig()
/*N*/ {
/*N*/ 	if ( !pColorConfig )
/*N*/ 	{
/*N*/         pColorConfig = new svtools::ColorConfig;
/*N*/ 	    StartListening(*pColorConfig);
/*N*/ 	}
/*N*/
/*N*/ 	return *pColorConfig;
/*N*/ }

/*N*/ SvtAccessibilityOptions& ScModule::GetAccessOptions()
/*N*/ {
/*N*/ 	if ( !pAccessOptions )
/*N*/ 	{
/*N*/ 		pAccessOptions = new SvtAccessibilityOptions;
/*N*/ 		StartListening(*pAccessOptions);
/*N*/ 	}
/*N*/
/*N*/ 	return *pAccessOptions;
/*N*/ }

/*N*/ SvtCTLOptions& ScModule::GetCTLOptions()
/*N*/ {
/*N*/ 	if ( !pCTLOptions )
/*N*/ 	{
/*N*/ 		pCTLOptions = new SvtCTLOptions;
/*N*/ 		StartListening(*pCTLOptions);
/*N*/ 	}
/*N*/
/*N*/ 	return *pCTLOptions;
/*N*/ }

/*N*/ USHORT ScModule::GetOptDigitLanguage()
/*N*/ {
/*N*/ 	SvtCTLOptions::TextNumerals eNumerals = GetCTLOptions().GetCTLTextNumerals();
/*N*/ 	return ( eNumerals == SvtCTLOptions::NUMERALS_ARABIC ) ? LANGUAGE_ENGLISH_US :
/*N*/ 		   ( eNumerals == SvtCTLOptions::NUMERALS_HINDI)   ? LANGUAGE_ARABIC :
/*N*/ 															 LANGUAGE_SYSTEM;
/*N*/ }

//------------------------------------------------------------------
//
//						Input-Handler
//
//------------------------------------------------------------------


/*N*/ void ScModule::ViewShellGone( ScTabViewShell* )
/*N*/ {
/*N*/ }


/*N*/ BOOL ScModule::IsFormulaMode()
/*N*/ {
/*N*/ 	BOOL bIsFormula = FALSE;
/*?*/	DBG_BF_ASSERT(0, "STRIP");
/*N*/ 	return bIsFormula;
/*N*/ }

//------------------------------------------------------------------
//
//					Idle / Online-Spelling
//
//------------------------------------------------------------------

/*N*/ void ScModule::AnythingChanged()
/*N*/ {
/*N*/ 	ULONG nOldTime = aIdleTimer.GetTimeout();
/*N*/ 	if ( nOldTime != SC_IDLE_MIN )
/*N*/ 		aIdleTimer.SetTimeout( SC_IDLE_MIN );
/*N*/
/*N*/ 	nIdleCount = 0;
/*N*/ }

/*N*/ IMPL_LINK( ScModule, IdleHandler, Timer*, pTimer )
/*N*/ {
/*N*/ 	if ( Application::AnyInput( INPUT_MOUSEANDKEYBOARD ) )
/*N*/ 	{
/*N*/ 		aIdleTimer.Start();			// Timeout unveraendert
/*N*/ 		return 0;
/*N*/ 	}
/*N*/
/*N*/ 	BOOL bMore = FALSE;
/*N*/ 	ScDocShell* pDocSh = PTR_CAST( ScDocShell, SfxObjectShell::Current() );
/*N*/ 	if ( pDocSh )
/*N*/ 	{
/*?*/ 		ScDocument* pDoc = pDocSh->GetDocument();
/*?*/ 		if ( pDoc->IsLoadingDone() )
/*?*/ 		{
/*?*/ 			DBG_BF_ASSERT(0, "STRIP"); //STRIP001 BOOL bLinks = pDoc->IdleCheckLinks();
/*?*/ 		}
/*N*/ 	}
/*N*/
/*N*/ 	ULONG nOldTime = aIdleTimer.GetTimeout();
/*N*/ 	ULONG nNewTime = nOldTime;
/*N*/ 	if ( bMore )
/*N*/ 	{
/*?*/ 		nNewTime = SC_IDLE_MIN;
/*?*/ 		nIdleCount = 0;
/*N*/ 	}
/*N*/ 	else
/*N*/ 	{
/*N*/ 		//	SC_IDLE_COUNT mal mit initialem Timeout, dann hochzaehlen
/*N*/
/*N*/ 		if ( nIdleCount < SC_IDLE_COUNT )
/*N*/ 			++nIdleCount;
/*N*/ 		else
/*N*/ 		{
/*N*/ 			nNewTime += SC_IDLE_STEP;
/*N*/ 			if ( nNewTime > SC_IDLE_MAX )
/*N*/ 				nNewTime = SC_IDLE_MAX;
/*N*/ 		}
/*N*/ 	}
/*N*/ 	if ( nNewTime != nOldTime )
/*N*/ 		aIdleTimer.SetTimeout( nNewTime );
/*N*/
/*N*/ 	aIdleTimer.Start();
/*N*/ 	return 0;
/*N*/ }

IMPL_LINK( ScModule, SpellTimerHdl, Timer*, pTimer )
{
    DBG_BF_ASSERT(0, "STRIP"); //STRIP001 //STRIP001 	if ( Application::AnyInput( INPUT_KEYBOARD ) )
    return 0;
}

/*N*/ IMPL_LINK( ScModule, CalcFieldValueHdl, EditFieldInfo*, pInfo )
/*N*/ {
DBG_BF_ASSERT(0, "STRIP"); //STRIP001 //STRIP001 	if (pInfo)
/*N*/ 	return 0;
/*N*/ }

}
