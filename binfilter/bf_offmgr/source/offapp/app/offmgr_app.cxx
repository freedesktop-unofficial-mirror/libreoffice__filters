/*************************************************************************
 *
 *  $RCSfile: offmgr_app.cxx,v $
 *
 *  $Revision: 1.2 $
 *
 *  last change: $Author: mwu $ $Date: 2003-11-06 07:25:37 $
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

#ifdef PRECOMPILED
#include "ofapch.hxx"
#endif

#pragma hdrstop
#ifndef _TOOLS_SIMPLERESMGR_HXX_
#include <tools/simplerm.hxx>
#endif

#ifndef _COM_SUN_STAR_DRAWING_MEASURETEXTVERTPOS_HPP_
#include <com/sun/star/drawing/MeasureTextVertPos.hpp>
#endif
#ifndef _COM_SUN_STAR_DRAWING_TEXTANIMATIONDIRECTION_HPP_
#include <com/sun/star/drawing/TextAnimationDirection.hpp>
#endif
#ifndef _COM_SUN_STAR_DRAWING_CONNECTIONTYPE_HPP_
#include <com/sun/star/drawing/ConnectionType.hpp>
#endif
#ifndef _COM_SUN_STAR_DRAWING_LINESTYLE_HPP_
#include <com/sun/star/drawing/LineStyle.hpp>
#endif
#ifndef _COM_SUN_STAR_DRAWING_TEXTUREMODE_HPP_
#include <com/sun/star/drawing/TextureMode.hpp>
#endif
#ifndef _COM_SUN_STAR_DRAWING_ARRANGEMENT_HPP_
#include <com/sun/star/drawing/Arrangement.hpp>
#endif
#ifndef _COM_SUN_STAR_DRAWING_TEXTANIMATIONKIND_HPP_
#include <com/sun/star/drawing/TextAnimationKind.hpp>
#endif
#ifndef _COM_SUN_STAR_DRAWING_DASHSTYLE_HPP_
#include <com/sun/star/drawing/DashStyle.hpp>
#endif
#ifndef _COM_SUN_STAR_DRAWING_TEXTADJUST_HPP_
#include <com/sun/star/drawing/TextAdjust.hpp>
#endif
#ifndef _COM_SUN_STAR_DRAWING_PROJECTIONMODE_HPP_
#include <com/sun/star/drawing/ProjectionMode.hpp>
#endif
#ifndef _COM_SUN_STAR_DRAWING_LINEENDTYPE_HPP_
#include <com/sun/star/drawing/LineEndType.hpp>
#endif
#ifndef _COM_SUN_STAR_DRAWING_RECTANGLEPOINT_HPP_
#include <com/sun/star/drawing/RectanglePoint.hpp>
#endif
#ifndef _COM_SUN_STAR_DRAWING_MEASURETEXTHORZPOS_HPP_
#include <com/sun/star/drawing/MeasureTextHorzPos.hpp>
#endif
#ifndef _COM_SUN_STAR_DRAWING_CONNECTORTYPE_HPP_
#include <com/sun/star/drawing/ConnectorType.hpp>
#endif
#ifndef _COM_SUN_STAR_DRAWING_MIRRORAXIS_HPP_
#include <com/sun/star/drawing/MirrorAxis.hpp>
#endif
#ifndef _COM_SUN_STAR_DRAWING_TEXTUREKIND_HPP_
#include <com/sun/star/drawing/TextureKind.hpp>
#endif
#ifndef _COM_SUN_STAR_DRAWING_NORMALSKIND_HPP_
#include <com/sun/star/drawing/NormalsKind.hpp>
#endif
#ifndef _COM_SUN_STAR_DRAWING_ALIGNMENT_HPP_
#include <com/sun/star/drawing/Alignment.hpp>
#endif
#ifndef _COM_SUN_STAR_DRAWING_SHADEMODE_HPP_
#include <com/sun/star/drawing/ShadeMode.hpp>
#endif
#ifndef _COM_SUN_STAR_DRAWING_MEASUREKIND_HPP_
#include <com/sun/star/drawing/MeasureKind.hpp>
#endif
#ifndef _COM_SUN_STAR_DRAWING_LAYERTYPE_HPP_
#include <com/sun/star/drawing/LayerType.hpp>
#endif
#ifndef _COM_SUN_STAR_DRAWING_SNAPOBJECTTYPE_HPP_
#include <com/sun/star/drawing/SnapObjectType.hpp>
#endif
#ifndef _COM_SUN_STAR_DRAWING_FILLSTYLE_HPP_
#include <com/sun/star/drawing/FillStyle.hpp>
#endif
#ifndef _COM_SUN_STAR_DRAWING_CIRCLEKIND_HPP_
#include <com/sun/star/drawing/CircleKind.hpp>
#endif
#ifndef _COM_SUN_STAR_DRAWING_HORIZONTALDIMENSIONING_HPP_
#include <com/sun/star/drawing/HorizontalDimensioning.hpp>
#endif
#ifndef _COM_SUN_STAR_DRAWING_HATCHSTYLE_HPP_
#include <com/sun/star/drawing/HatchStyle.hpp>
#endif
#ifndef _COM_SUN_STAR_DRAWING_VERTICALDIMENSIONING_HPP_
#include <com/sun/star/drawing/VerticalDimensioning.hpp>
#endif
#ifndef _COM_SUN_STAR_DRAWING_TEXTFITTOSIZETYPE_HPP_
#include <com/sun/star/drawing/TextFitToSizeType.hpp>
#endif
#ifndef _COM_SUN_STAR_DRAWING_POLYGONKIND_HPP_
#include <com/sun/star/drawing/PolygonKind.hpp>
#endif
#ifndef _COM_SUN_STAR_DRAWING_TEXTUREPROJECTIONMODE_HPP_
#include <com/sun/star/drawing/TextureProjectionMode.hpp>
#endif
#ifndef _COM_SUN_STAR_DRAWING_POLYGONFLAGS_HPP_
#include <com/sun/star/drawing/PolygonFlags.hpp>
#endif
#ifndef _COM_SUN_STAR_DRAWING_DRAWVIEWMODE_HPP_
#include <com/sun/star/drawing/DrawViewMode.hpp>
#endif
#ifndef _COM_SUN_STAR_LOADER_XIMPLEMENTATIONLOADER_HPP_
#include <com/sun/star/loader/XImplementationLoader.hpp>
#endif
#ifndef _COM_SUN_STAR_LOADER_CANNOTACTIVATEFACTORYEXCEPTION_HPP_
#include <com/sun/star/loader/CannotActivateFactoryException.hpp>
#endif
#ifndef _COM_SUN_STAR_CONTAINER_XSET_HPP_
#include <com/sun/star/container/XSet.hpp>
#endif
#include <comphelper/processfactory.hxx>
#include <rtl/logfile.hxx>

#ifndef _SVX_UNOSHCOL_HXX

#include <vcl/config.hxx>

#ifndef _SVX_IMPGRF_HXX	//autogen
#include <bf_svx/impgrf.hxx>
#endif
#ifndef _STRING_HXX //autogen
//#include <tools/string.hxx>
#endif
#ifndef _URLOBJ_HXX //autogen
#include <tools/urlobj.hxx>
#endif
#ifndef _SFXPTITEM_HXX
#include <svtools/ptitem.hxx>
#endif
#ifndef _SFX_FCONTNR_HXX //autogen
#include <bf_sfx2/fcontnr.hxx>
#endif
#ifndef _SFXREQUEST_HXX
#include <bf_sfx2/request.hxx>
#endif
#ifndef _FM_FMOBJFAC_HXX
#include <bf_svx/fmobjfac.hxx>
#endif
#ifndef _SVX_SIIMPORT_HXX
#include <bf_svx/siimport.hxx>
#endif
#ifndef _SVX_TBCONTRL_HXX //autogen
#include <bf_svx/tbcontrl.hxx>
#endif
#ifndef _SVX_SRCHDLG_HXX //autogen
#include <bf_svx/srchdlg.hxx>
#endif
#ifndef _SVX_THESDLG_HXX //autogen
#include <bf_svx/thesdlg.hxx>
#endif
#ifndef _SVX_ADRITEM_HXX //autogen
#include <bf_svx/adritem.hxx>
#endif
#ifndef _OUTLINER_HXX //autogen
#include <bf_svx/outliner.hxx>
#endif
#ifndef _SV_WRKWIN_HXX //autogen
#include <vcl/wrkwin.hxx>
#endif
#ifndef _IMAPDLG_HXX_ //autogen
#include <bf_svx/imapdlg.hxx>
#endif
#ifndef _CPPUHELPER_FACTORY_HXX_
#include <cppuhelper/factory.hxx>
#endif

#ifndef _SFXREQUEST_HXX
#include <bf_sfx2/request.hxx>
#endif

#ifndef _SFXITEMSET_HXX
#include <svtools/itemset.hxx>
#endif
#ifndef _OFA_FONTSUBSTCONFIG_HXX
#include <fontsubstconfig.hxx>
#endif

// include ---------------------------------------------------------------

#ifndef _OFF_APP_HXX
#include "app.hxx"
#endif
#ifndef _OFF_APPIMP_HXX
#include "appimp.hxx"
#endif
#ifndef _OFF_RESID_HXX
#include "resid.hxx"
#endif
#ifndef _OFF_APP_HRC
#include "app.hrc"
#endif

#ifndef _SFX_DBCOLL_HXX
#include "dbcoll.hxx"
#endif
#ifndef _SVX_DLG_HYPERLINK_HXX
#include "hyprlink.hxx"
#endif
#ifndef _SFX_INETOPT_HXX
#include "optuno.hxx"
#endif

#ifndef _SV_MSGBOX_HXX
#include <vcl/msgbox.hxx>
#endif
#ifndef _SFXDISPATCH_HXX
#include <bf_sfx2/dispatch.hxx>
#endif
#ifndef	_SFXMSG_HXX
#include <bf_sfx2/msg.hxx>
#endif
#ifndef _SFXOBJFACE_HXX
#include <bf_sfx2/objface.hxx>
#endif
#define ITEMID_FIELD 0
#ifndef _SVX_FLDITEM_HXX
#include <bf_svx/flditem.hxx>
#endif
#ifndef _SVDFIELD_HXX
#include <bf_svx/svdfield.hxx>
#endif
#ifndef _OBJFAC3D_HXX
#include <bf_svx/objfac3d.hxx>
#endif
#ifndef _SVX_SIZEITEM_HXX
#define ITEMID_SIZE 0
#include <bf_svx/sizeitem.hxx>
#endif
#ifndef _SVX_ZOOMITEM_HXX
#include <bf_svx/zoomitem.hxx>
#endif
#ifndef _SVX_LANGITEM_HXX
#define ITEMID_LANGUAGE 0
#include <bf_svx/langitem.hxx>
#endif
#ifndef _SVX_UNOSHGRP_HXX
#include <bf_svx/unoshcol.hxx>
#endif
#endif

#ifndef _SVX_TAB_HYPERLINK_HXX
#include <bf_svx/hyperdlg.hxx>
#endif
#ifndef _SVX_HLNKITEM_HXX
#include <bf_svx/hlnkitem.hxx>
#endif
#ifndef _NUMUNO_HXX
#include <svtools/numuno.hxx>
#endif
#ifndef _SB_SBSTAR_HXX
#include <basic/sbstar.hxx>
#endif

#include <svtools/moduleoptions.hxx>
#include <bf_sfx2/viewsh.hxx>
#include <bf_sfx2/viewfrm.hxx>

#include "calwin.hxx"
#ifndef _OFA_APEARCFG_HXX
#include "apearcfg.hxx"
#endif

#ifndef _SBASLTID_HRC
#include "sbasltid.hrc"
#endif

#ifndef _VOS_MUTEX_HXX_
#include <vos/mutex.hxx>
#endif

#include <osl/module.hxx>
#ifndef _LEGACYBINFILTERMGR_HXX
#include <legacysmgr/legacy_binfilters_smgr.hxx>	//STRIP002 
#endif

using namespace ::com::sun::star::uno;

//=========================================================================

#define SFX_TYPEMAP
#define Address
#define _ExecAddress  ExecuteApp_Impl
#define _StateAddress GetStateApp_Impl
#define OfficeApplication
//STRIP008 #include "ofaslots.hxx"
namespace binfilter {
#include "ofaslots.hxx"
/*N*/ TYPEINIT1(OfficeApplication,SfxApplication);

#define IS_AVAILABLE(WhichId,ppItem) \
    (pArgs->GetItemState((WhichId), sal_True, ppItem ) == SFX_ITEM_SET)

#define DOSTRING( x )			   			#x
#define STRING( x )				   			DOSTRING( x )

//=========================================================================

typedef	rtl_uString* (SAL_CALL *basicide_choose_macro)(BOOL, BOOL, rtl_uString*);

typedef	long (SAL_CALL *basicide_handle_basic_error)(void*);

//=========================================================================

/*N*/ SFX_IMPL_INTERFACE(OfficeApplication,SfxApplication,OffResId(RID_DESKTOP))
/*N*/ {
/*N*/ 	SFX_CHILDWINDOW_REGISTRATION( SID_HYPERLINK_INSERT );
/*N*/ //  SFX_CHILDWINDOW_REGISTRATION( SID_HYPERLINK_DIALOG );
/*N*/ //	SFX_CHILDWINDOW_REGISTRATION( SID_SHOW_BROWSER );
/*N*/ }

// ------------------------------------------------------------------------
// hack: this must be implemented somewhere else, hack for 554 update

/*N*/  Reference< XInterface > SAL_CALL SvxShapeCollection_CreateInstance( const Reference< ::com::sun::star::lang::XMultiServiceFactory >& rSMgr ) throw( Exception )
/*N*/  {
/*?*/  	return *( new SvxShapeCollection() );
/*N*/  }

/*N*/ void OfficeApplication::Init()
/*N*/ {
/*N*/ 	RTL_LOGFILE_CONTEXT( aLog, "offmgr (cd100003) ::OfficeApplication::Init" );
/*N*/ 
/*N*/     SfxApplication::Init();
/*N*/ 
/*N*/ 	SvxIMapDlgChildWindow::RegisterChildWindow();
/*N*/ 
/*N*/ 	// Handler fuer Grafikfilter setzen; im Handler wird ggf.
/*N*/ 	// der Graphicfilter init., wenn das erste Mal auf einen
/*N*/ 	// Filter zugegriffen wird (KA 04.08.98)
/*N*/ 	Application::SetFilterHdl( LINK( this, OfficeApplication, ImplInitFilterHdl ) );
/*N*/ 
/*N*/     // set basic error handler
/*N*/ 	StarBASIC::SetGlobalErrorHdl( LINK( this, OfficeApplication, GlobalBasicErrorHdl ) );
/*N*/ 
/*N*/ 	CreateDataImpl();
/*N*/ 	UseFontSubst();
/*N*/ 
/*N*/ 	OfficeApplication::RegisterInterface();
/*N*/ 
//STRIP001 /*?*/ 	SvxHyperlinkDlgWrapper::RegisterChildWindow();
/*N*/ 	SvxSearchDialogWrapper::RegisterChildWindow();
/*N*/ 	SvxHlinkDlgWrapper::RegisterChildWindow ();
/*N*/ 
/*N*/ 	//OfficeApplication::RegisterInterface();
/*N*/     SvxReloadControllerItem::RegisterControl( SID_RELOAD );
/*N*/ 
/*N*/     // SvxURLField registrieren
/*N*/ 	SvClassManager& rClassManager = SvxFieldItem::GetClassManager();
/*N*/ 	rClassManager.SV_CLASS_REGISTER( SvxFieldData );
/*N*/ 	rClassManager.SV_CLASS_REGISTER( SvxURLField );
/*N*/ 	rClassManager.SV_CLASS_REGISTER( SvxDateField );
/*N*/ 	rClassManager.SV_CLASS_REGISTER( SvxPageField );
/*N*/ 	rClassManager.SV_CLASS_REGISTER( SvxTimeField );
/*N*/ 	rClassManager.SV_CLASS_REGISTER( SvxExtTimeField );
/*N*/ 	rClassManager.SV_CLASS_REGISTER( SvxExtFileField );
/*N*/ 	rClassManager.SV_CLASS_REGISTER( SvxAuthorField );
/*N*/ 
/*N*/     // SvDraw-Felder registrieren
/*N*/     SdrRegisterFieldClasses();
/*N*/ 
/*N*/     // 3D-Objekt-Factory eintragen
/*N*/     E3dObjFactory();
/*N*/ 
/*N*/     // ::com::sun::star::form::component::Form-Objekt-Factory eintragen
/*N*/     FmFormObjFactory();
/*N*/ 
/*N*/     // factory for dummy import of old si-controls in 3.1 documents
/*N*/     SiImportFactory();
/*N*/ 
/*N*/ 	// Servies etc. registrieren
/*N*/ 	RTL_LOGFILE_CONTEXT_TRACE( aLog, "{ register services: com.sun.star.drawing.ShapeCollection/com.sun.star.util.NumberFormatter" );
/*N*/ 	Reference< ::com::sun::star::lang::XMultiServiceFactory >  xSMgr = ::legacy_binfilters::getLegacyProcessServiceFactory();
/*N*/ 	Reference< ::com::sun::star::container::XSet >  xSet( xSMgr, UNO_QUERY );
/*N*/ 	Sequence< ::rtl::OUString >			aName( 1 );
/*N*/ 	Reference< ::com::sun::star::lang::XSingleServiceFactory > 	xFact;
/*N*/ 
/*N*/ 	aName.getArray()[0] = ::rtl::OUString::createFromAscii("com.sun.star.drawing.ShapeCollection");
/*N*/ 	xFact = ::cppu::createSingleFactory( xSMgr, ::rtl::OUString::createFromAscii("ShapeCollection"), SvxShapeCollection_CreateInstance, aName );
/*N*/ 	xSet->insert( makeAny(xFact) );
/*N*/ 
/*N*/ 	aName.getArray()[0] = ::rtl::OUString::createFromAscii("com.sun.star.util.NumberFormatter");
/*N*/ 	xFact = ::cppu::createSingleFactory( xSMgr, ::rtl::OUString::createFromAscii("NumberFormatter"), SvNumberFormatterServiceObj_NewInstance, aName );
/*N*/ 	xSet->insert( makeAny( xFact ) );
/*N*/ 
/*N*/ 	xSet->insert( makeAny( SfxSettingsContainer::impl_createFactory(xSMgr) ) );
/*N*/ 	RTL_LOGFILE_CONTEXT_TRACE( aLog, "} register services: com.sun.star.drawing.ShapeCollection/com.sun.star.util.NumberFormatter" );
/*N*/ 
/*N*/ 	// options - general - appearance
/*N*/     OfaTabAppearanceCfg* pAppearanceCfg = GetTabAppearanceConfig();
/*N*/ 	pAppearanceCfg->SetInitialized();
/*N*/ 	pAppearanceCfg->SetApplicationDefaults( GetpApp() );
/*N*/ 
/*N*/     pDataImpl->SetVCLSettings();
/*N*/ }

// ------------------------------------------------------------------------
/*N*/ void OfficeApplication::Exit()
/*N*/ {
/*N*/ 	if ( pDataImpl->pWordDeInitFct )
/*?*/ 		pDataImpl->pWordDeInitFct();
/*N*/ }

//------------------------------------------------------------------------------


/*N*/ void OfficeApplication::UseFontSubst()
/*N*/ {
/*N*/ 	OutputDevice::BeginFontSubstitution();
/*N*/ 	// Alte Substitution entfernen
/*N*/ 	sal_uInt16 nOldCount = OutputDevice::GetFontSubstituteCount();
/*N*/ 
/*N*/ 	while (nOldCount)
/*?*/ 		OutputDevice::RemoveFontSubstitute(--nOldCount);

    // Neue Substitution einlesen
/*N*/ 	OfaFontSubstConfig aFontConfig;
/*N*/     sal_Int32 nCount = aFontConfig.IsEnabled() ? aFontConfig.SubstitutionCount() : 0;
/*N*/ 
/*N*/ 	for (sal_Int32  i = 0; i < nCount; i++)
/*N*/ 	{DBG_ASSERT(0, "STRIP"); //STRIP001 
//STRIP001 /*?*/ 	    sal_uInt16 nFlags = 0;
//STRIP001 /*?*/ 		const SubstitutionStruct* pSubs = aFontConfig.GetSubstitution(i);
//STRIP001 /*?*/ 		if(pSubs->bReplaceAlways)
//STRIP001 /*?*/ 			nFlags |= FONT_SUBSTITUTE_ALWAYS;
//STRIP001 /*?*/ 		if(pSubs->bReplaceOnScreenOnly)
//STRIP001 /*?*/ 			nFlags |= FONT_SUBSTITUTE_SCREENONLY;
//STRIP001 /*?*/ 		OutputDevice::AddFontSubstitute( String(pSubs->sFont), String(pSubs->sReplaceBy), nFlags );
/*N*/     }
/*N*/ 	OutputDevice::EndFontSubstitution();
/*N*/ }

// ------------------------------------------------------------------------

/*N*/ ResMgr* OfficeApplication::GetOffResManager()
/*N*/ {
/*N*/ 	if ( !pImpl->pResMgr )
/*N*/ 		pImpl->pResMgr = CreateResManager( "bf_ofa"); //STRIP005
/*N*/ 	return pImpl->pResMgr;
/*N*/ }

// ------------------------------------------------------------------------

//STRIP001 SimpleResMgr* OfficeApplication::GetOffSimpleResManager()
//STRIP001 {
//STRIP001 	if ( !pImpl->m_pThreadSafeRessources )
//STRIP001 	{
//STRIP001         LanguageType nType = Application::GetSettings().GetUILanguage();
//STRIP001 		ByteString sMgrName("ofs");
//STRIP001 		sMgrName += ByteString::CreateFromInt32( SOLARUPD );
//STRIP001 		pImpl->m_pThreadSafeRessources = SimpleResMgr::Create( sMgrName.GetBuffer(), nType );
//STRIP001 	}
//STRIP001 	return pImpl->m_pThreadSafeRessources;
//STRIP001 }

// ------------------------------------------------------------------------

//STRIP001 void OfficeApplication::SetSbxCreatedLink( const Link &rLink )
//STRIP001 // nur bis GetSbxObject virtual ist
//STRIP001 {
//STRIP001 	aSbaCreatedLink = rLink;
//STRIP001 }

// ------------------------------------------------------------------------

/*N*/void OfficeApplication::DrawExec_Impl( SfxRequest &rReq )
/*N*/{DBG_ASSERT(0, "STRIP"); //STRIP001 
//STRIP001 /*
//STRIP001 Slots with the following id's are executed in this function
//STRIP001 SID_AUTOPILOT
//STRIP001 SID_OUTLINE_TO_IMPRESS
//STRIP001 */
//STRIP001 	SvtModuleOptions aModuleOpt;
//STRIP001 
//STRIP001 	// The special slots SID_AUTOPILOT/SID_OUTLINE_TO_IMPRESS are only used for impress.
//STRIP001 	// Because impress uses the drawing library we have to ask for these special slots.
//STRIP001 	if ( !aModuleOpt.IsImpress() &&
//STRIP001 		 (( rReq.GetSlot() == SID_AUTOPILOT			 ) ||
//STRIP001 		  ( rReq.GetSlot() == SID_OUTLINE_TO_IMPRESS ))	  )
//STRIP001 	{
//STRIP001 		vos::OGuard aGuard( Application::GetSolarMutex() );
//STRIP001 		ErrorBox( 0, ResId( RID_ERRBOX_MODULENOTINSTALLED, GetOffResManager() )).Execute();
//STRIP001 		return;
//STRIP001 	}
//STRIP001 
//STRIP001 	// We have to be sure that the drawing module is installed before trying to load draw library.
//STRIP001 	if ( aModuleOpt.IsDraw() || aModuleOpt.IsImpress() )
//STRIP001 	{
//STRIP001 		SfxModule *pMod = (*(SfxModule**) GetAppData(BF_SHL_DRAW))->Load();
//STRIP001 		if(pMod)
//STRIP001 		{
//STRIP001 			pMod->ExecuteSlot( rReq );
//STRIP001 			pMod->Free();
//STRIP001 		}
//STRIP001 	}
//STRIP001 	else
//STRIP001 	{
//STRIP001 		vos::OGuard aGuard( Application::GetSolarMutex() );
//STRIP001 		ErrorBox( 0, ResId( RID_ERRBOX_MODULENOTINSTALLED, GetOffResManager() )).Execute();
//STRIP001 	}
/*N*/ }

// ------------------------------------------------------------------------

/*N*/void OfficeApplication::ModuleState_Impl( SfxItemSet &rSet )
/*N*/{DBG_ASSERT(0, "STRIP"); //STRIP001 
//STRIP001 	// f"ur die Statusabfrage darf das Modul NICHT geladen werden
//STRIP001 
//STRIP001 #if OSL_DEBUG_LEVEL > 1
//STRIP001 // lass mal alle Features aus .ini sehen
//STRIP001 	sal_Bool bf;
//STRIP001 	for ( sal_uInt32 j=1; j; j <<= 1 )
//STRIP001 	{
//STRIP001 		if ( HasFeature( j ) )
//STRIP001 			bf = sal_True;
//STRIP001 		else
//STRIP001 			bf = sal_False;
//STRIP001 	}
//STRIP001 #endif
//STRIP001 
//STRIP001 	SvtModuleOptions aModuleOpt;
//STRIP001 
//STRIP001 	if ( !aModuleOpt.IsCalc() )
//STRIP001 		rSet.DisableItem( SID_SC_EDITOPTIONS );
//STRIP001 
//STRIP001 	if ( !aModuleOpt.IsMath() )
//STRIP001 		rSet.DisableItem( SID_SM_EDITOPTIONS );
//STRIP001 
//STRIP001 	if ( !aModuleOpt.IsImpress() )
//STRIP001 		rSet.DisableItem( SID_SD_EDITOPTIONS );
//STRIP001 
//STRIP001 	if ( !aModuleOpt.IsDraw() )
//STRIP001 		rSet.DisableItem( SID_SD_GRAPHIC_OPTIONS );
//STRIP001 
//STRIP001     if( !aModuleOpt.IsWriter())
//STRIP001     {
//STRIP001         rSet.DisableItem( SID_SW_AGENDA_WIZZARD );
//STRIP001         rSet.DisableItem( SID_SW_FAX_WIZZARD );
//STRIP001         rSet.DisableItem( SID_SW_LETTER_WIZZARD );
//STRIP001         rSet.DisableItem( SID_SW_MEMO_WIZZARD );
//STRIP001         rSet.DisableItem( SID_SW_DOCMAN_PATH );
//STRIP001     }
/*N*/ }


// ------------------------------------------------------------------------

/*N*/void OfficeApplication::WriterExec_Impl( SfxRequest &rReq )
/*N*/{DBG_ASSERT(0, "STRIP"); //STRIP001 
//STRIP001 /*
//STRIP001 Hier werden Executes fuer folgende Slots weitergeleitet
//STRIP001 SID_SW_AGENDA_WIZZARD
//STRIP001 SID_SW_FAX_WIZZARD
//STRIP001 SID_SW_LETTER_WIZZARD
//STRIP001 SID_SW_MEMO_WIZZARD
//STRIP001 SID_SW_EDITOPTIONS
//STRIP001 SID_SW_DOCMAN_PATH
//STRIP001 */
//STRIP001 	SvtModuleOptions aModuleOpt;
//STRIP001 
//STRIP001 	if ( aModuleOpt.IsWriter() )
//STRIP001 	{
//STRIP001 		SfxModule *pMod = (*(SfxModule**) GetAppData(BF_SHL_WRITER))->Load();
//STRIP001 		if(pMod)
//STRIP001 		{
//STRIP001 			pMod->ExecuteSlot( rReq );
//STRIP001 			pMod->Free();
//STRIP001 		}
//STRIP001 	}
//STRIP001 	else
//STRIP001 	{
//STRIP001 		vos::OGuard aGuard( Application::GetSolarMutex() );
//STRIP001 		ErrorBox( 0, ResId( RID_ERRBOX_MODULENOTINSTALLED, GetOffResManager() )).Execute();
//STRIP001 	}
/*N*/ }

// ------------------------------------------------------------------------

//STRIP001 void OfficeApplication::CalcExec_Impl( SfxRequest &rReq )
//STRIP001 {
//STRIP001 /*
//STRIP001 Hier werden Executes fuer folgende Slots weitergeleitet
//STRIP001 */
//STRIP001 
//STRIP001 	SvtModuleOptions aModuleOpt;
//STRIP001 
//STRIP001 	if ( aModuleOpt.IsCalc() )
//STRIP001 	{
//STRIP001 		SfxModule *pMod = (*(SfxModule**) GetAppData(BF_SHL_CALC))->Load();
//STRIP001 		if(pMod)
//STRIP001 		{
//STRIP001 			pMod->ExecuteSlot( rReq );
//STRIP001 			pMod->Free();
//STRIP001 		}
//STRIP001 	}
//STRIP001 	else
//STRIP001 	{
//STRIP001 		vos::OGuard aGuard( Application::GetSolarMutex() );
//STRIP001 		ErrorBox( 0, ResId( RID_ERRBOX_MODULENOTINSTALLED, GetOffResManager() )).Execute();
//STRIP001 	}
//STRIP001 }


// ------------------------------------------------------------------------

/*N*/ IMPL_LINK( OfficeApplication, ImplInitFilterHdl, ConvertData*, pData )
/*N*/ {
/*N*/ 	return GetGrfFilter()->GetFilterCallback().Call( pData );
/*N*/ }

// ------------------------------------------------------------------------

//STRIP001 ::rtl::OUString OfficeApplication::ChooseMacro( BOOL bExecute, BOOL bChooseOnly, const ::rtl::OUString& rMacroDesc )
//STRIP001 {
//STRIP001     // get basctl dllname
//STRIP001     String sLibName = String::CreateFromAscii( STRING( DLL_NAME ) );
//STRIP001 	sLibName.SearchAndReplace( String( RTL_CONSTASCII_USTRINGPARAM( "ofa" ) ), String( RTL_CONSTASCII_USTRINGPARAM( "basctl" ) ) );
//STRIP001 	::rtl::OUString aLibName( sLibName );
//STRIP001 
//STRIP001     // load module
//STRIP001 	oslModule handleMod = osl_loadModule( aLibName.pData, 0 );
//STRIP001 
//STRIP001     // get symbol
//STRIP001     ::rtl::OUString aSymbol( RTL_CONSTASCII_USTRINGPARAM( "basicide_choose_macro" ) );
//STRIP001     basicide_choose_macro pSymbol = (basicide_choose_macro) osl_getSymbol( handleMod, aSymbol.pData );
//STRIP001 
//STRIP001     // call basicide_choose_macro in basctl
//STRIP001     rtl_uString* pScriptURL = pSymbol( bExecute, bChooseOnly, rMacroDesc.pData );
//STRIP001 
//STRIP001     ::rtl::OUString aScriptURL( pScriptURL );
//STRIP001     rtl_uString_release( pScriptURL );
//STRIP001 
//STRIP001 	return aScriptURL;
//STRIP001 }

// ------------------------------------------------------------------------

/*N*/ IMPL_LINK( OfficeApplication, GlobalBasicErrorHdl, StarBASIC*, pBasic )
/*N*/ {DBG_ASSERT(0, "STRIP"); return 0;//STRIP001 
//STRIP001     // get basctl dllname
//STRIP001     String sLibName = String::CreateFromAscii( STRING( DLL_NAME ) );
//STRIP001 	sLibName.SearchAndReplace( String( RTL_CONSTASCII_USTRINGPARAM( "ofa" ) ), String( RTL_CONSTASCII_USTRINGPARAM( "basctl" ) ) );
//STRIP001 	::rtl::OUString aLibName( sLibName );
//STRIP001 
//STRIP001     // load module
//STRIP001 	oslModule handleMod = osl_loadModule( aLibName.pData, 0 );
//STRIP001 
//STRIP001     // get symbol
//STRIP001     ::rtl::OUString aSymbol( RTL_CONSTASCII_USTRINGPARAM( "basicide_handle_basic_error" ) );
//STRIP001     basicide_handle_basic_error pSymbol = (basicide_handle_basic_error) osl_getSymbol( handleMod, aSymbol.pData );
//STRIP001 
//STRIP001     // call basicide_handle_basic_error in basctl
//STRIP001     long nRet = pSymbol( pBasic );
//STRIP001 
//STRIP001 	return nRet;
/*N*/ }

// ------------------------------------------------------------------------
} //namespace binfilter
