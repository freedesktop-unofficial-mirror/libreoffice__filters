/*************************************************************************
 *
 *  $RCSfile: sfx2_objstor.cxx,v $
 *
 *  $Revision: 1.7 $
 *
 *  last change: $Author: rt $ $Date: 2005-01-11 11:37:25 $
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

#ifndef _MSGBOX_HXX //autogen
#include <vcl/msgbox.hxx>
#endif
#ifndef _SFXENUMITEM_HXX //autogen
#include <svtools/eitem.hxx>
#endif
#ifndef _SFXSTRITEM_HXX //autogen
#include <svtools/stritem.hxx>
#endif
#ifndef _SVSTOR_HXX //autogen
#include <so3/svstor.hxx>
#endif
#ifndef _EXTATTR_HXX //autogen
#include <svtools/extattr.hxx>
#endif
#ifndef _ZCODEC_HXX //autogen
#include <tools/zcodec.hxx>
#endif
#ifndef _COM_SUN_STAR_FRAME_XSTORABLE_HPP_
#include <com/sun/star/frame/XStorable.hpp>
#endif
#ifndef _COM_SUN_STAR_FRAME_XMODEL_HPP_
#include <com/sun/star/frame/XModel.hpp>
#endif
#ifndef _COM_SUN_STAR_FRAME_XFRAME_HPP_
#include <com/sun/star/frame/XFrame.hpp>
#endif

#ifndef _COM_SUN_STAR_DOCUMENT_XFILTER_HPP_
#include <com/sun/star/document/XFilter.hpp>
#endif
#ifndef _COM_SUN_STAR_DOCUMENT_XIMPORTER_HPP_
#include <com/sun/star/document/XImporter.hpp>
#endif
#ifndef _COM_SUN_STAR_DOCUMENT_XEXPORTER_HPP_
#include <com/sun/star/document/XExporter.hpp>
#endif
#ifndef _COM_SUN_STAR_DOCUMENT_FILTEROPTIONSREQUEST_HPP_
#include <com/sun/star/document/FilterOptionsRequest.hpp>
#endif
#ifndef _COM_SUN_STAR_DOCUMENT_XINTERACTIONFILTEROPTIONS_HPP_
#include <com/sun/star/document/XInteractionFilterOptions.hpp>
#endif
#ifndef _COM_SUN_STAR_TASK_XINTERACTIONHANDLER_HPP_
#include <com/sun/star/task/XInteractionHandler.hpp>
#endif

#ifndef  _COM_SUN_STAR_LANG_XINITIALIZATION_HPP_
#include <com/sun/star/lang/XInitialization.hpp>
#endif

#ifndef _COM_SUN_STAR_DOCUMENT_MACROEXECMODE_HPP_
#include <com/sun/star/document/MacroExecMode.hpp>
#endif
#ifndef  _COM_SUN_STAR_UI_DIALOGS_EXTENDEDFILEPICKERELEMENTIDS_HPP_
#include <com/sun/star/ui/dialogs/ExtendedFilePickerElementIds.hpp>
#endif
#ifndef  _COM_SUN_STAR_UI_DIALOGS_XFILEPICKERCONTROLACCESS_HPP_
#include <com/sun/star/ui/dialogs/XFilePickerControlAccess.hpp>
#endif
#ifndef  _COM_SUN_STAR_UI_DIALOGS_XFILEPICKER_HPP_
#include <com/sun/star/ui/dialogs/XFilePicker.hpp>
#endif
#ifndef  _COM_SUN_STAR_BEANS_XPROPERTYSETINFO_HPP_
#include <com/sun/star/beans/XPropertySetInfo.hpp>
#endif

#ifndef _COM_SUN_STAR_LANG_XMULTISERVICEFACTORY_HPP_
#include <com/sun/star/lang/XMultiServiceFactory.hpp>
#endif

#ifndef _COM_SUN_STAR_BEANS_XPROPERTYACCESS_HPP_
#include <com/sun/star/beans/XPropertyAccess.hpp>
#endif

#ifndef _COM_SUN_STAR_BEANS_PROPERTYVALUE_HPP_
#include <com/sun/star/beans/PropertyValue.hpp>
#endif

#ifndef _COM_SUN_STAR_CONTAINER_XNAMEACCESS_HPP_
#include <com/sun/star/container/XNameAccess.hpp>
#endif

#ifndef _UNOTOOLS_PROCESSFACTORY_HXX_
#include <comphelper/processfactory.hxx>
#endif

#pragma hdrstop

#ifndef _SFXECODE_HXX
#include <svtools/sfxecode.hxx>
#endif

#ifndef _CPPUHELPER_WEAK_HXX_
#include <cppuhelper/weak.hxx>
#endif
#ifndef _COMPHELPER_PROCESSFACTORY_HXX_
#include <comphelper/processfactory.hxx>
#endif

#ifndef _SO_CLSIDS_HXX
#include <so3/clsids.hxx>
#endif
#ifndef _CACHESTR_HXX
#include <tools/cachestr.hxx>
#endif
#ifndef INCLUDED_SVTOOLS_ADDXMLTOSTORAGEOPTIONS_HXX
#include <svtools/addxmltostorageoptions.hxx>
#endif
#ifndef _UTL_STREAM_WRAPPER_HXX_
#include <unotools/streamwrap.hxx>
#endif

#include <svtools/saveopt.hxx>
#include <svtools/useroptions.hxx>
#include <svtools/pathoptions.hxx>
#include <tools/urlobj.hxx>
#include <unotools/localfilehelper.hxx>
#include <unotools/ucbhelper.hxx>
#include <unotools/tempfile.hxx>
#include <ucbhelper/content.hxx>
#include <sot/storinfo.hxx>
#include <shell/systemshell.hxx>

#include "objsh.hxx"
#include "childwin.hxx"
#include "sfxdir.hxx"
#include "request.hxx"
#include "sfxresid.hxx"
#include "docfile.hxx"
#include "fltfnc.hxx"
#include "docfilt.hxx"
#include "docinf.hxx"
#include "docfac.hxx"
#include "cfgmgr.hxx"
#include "objshimp.hxx"
#include "sfxtypes.hxx"
#include "appdata.hxx"
#include "doc.hrc"
#include "sfxsids.hrc"
#include "interno.hxx"
#include "module.hxx"
#include "dispatch.hxx"
#include "openflag.hxx"
#include "helper.hxx"
#include "dlgcont.hxx"
#include "filedlghelper.hxx"

#ifndef _BASMGR_HXX
#include <basic/basmgr.hxx>
#endif

#include "scriptcont.hxx"
#include "event.hxx"
#include "fltoptint.hxx"

#ifndef _LEGACYBINFILTERMGR_HXX
#include <legacysmgr/legacy_binfilters_smgr.hxx>	//STRIP002 
#endif
#include "so3/staticbaseurl.hxx"
namespace binfilter {

#define S2BS(s) ByteString( s, RTL_TEXTENCODING_MS_1252 )


extern sal_uInt32 CheckPasswd_Impl( SfxObjectShell*, SfxItemPool&, SfxMedium* );


using namespace ::com::sun::star::container;
using namespace ::com::sun::star::lang;
using namespace ::com::sun::star::ui::dialogs;
using namespace ::com::sun::star::uno;
using namespace ::com::sun::star::beans;
using namespace ::com::sun::star::ucb;
using namespace ::com::sun::star::task;
using namespace ::com::sun::star::document;
using namespace ::rtl;
using namespace ::cppu;

//=========================================================================

/*N*/ sal_Bool ShallSetBaseURL_Impl( SfxMedium &rMed )
/*N*/ {
/*N*/     SvtSaveOptions aOpt;
/*N*/ 	sal_Bool bIsRemote = rMed.IsRemote();
/*N*/     return  aOpt.IsSaveRelINet() && bIsRemote || aOpt.IsSaveRelFSys() && !bIsRemote;
/*N*/ }

//=========================================================================

/*N*/ sal_Bool SfxObjectShell::Save()
/*N*/ {
/*N*/     if( SOFFICE_FILEFORMAT_60 <= GetStorage()->GetVersion() )
/*N*/         return sal_True;
/*N*/     else
/*N*/         return SaveInfoAndConfig_Impl( GetMedium()->GetStorage() );
/*N*/ }

//--------------------------------------------------------------------------

/*N*/ sal_Bool SfxObjectShell::SaveAs( SvStorage* pNewStg )
/*N*/ {
/*N*/     if( SOFFICE_FILEFORMAT_60 <= pNewStg->GetVersion() )
/*N*/         return sal_True;
/*N*/     else
/*N*/         return SaveInfoAndConfig_Impl( pNewStg );
/*N*/ }

//-------------------------------------------------------------------------

/*N*/ sal_Bool GetPasswd_Impl( const SfxItemSet* pSet, String& rPasswd )
/*N*/ {
/*N*/ 	const SfxPoolItem* pItem = NULL;
/*N*/ 	if ( pSet && SFX_ITEM_SET == pSet->GetItemState( SID_PASSWORD, sal_True, &pItem ) )
/*N*/ 	{
/*?*/ 		DBG_ASSERT( pItem->IsA( TYPE(SfxStringItem) ), "wrong item type" );
/*?*/ 		rPasswd = ( (const SfxStringItem*)pItem )->GetValue();
/*?*/ 		return sal_True;
/*N*/ 	}
/*N*/ 	return sal_False;
/*N*/ }

//-------------------------------------------------------------------------
/*N*/ sal_Bool SfxObjectShell::DoInitNew_Impl( const String& rName )

/*  [Beschreibung]
*/

/*N*/ {
/*N*/ 	if ( rName.Len() )
/*N*/ 	{
/*?*/ 		ModifyBlocker_Impl aBlock( this );
/*?*/ 		pMedium = new SfxMedium( rName, SFX_STREAM_READONLY_MAKECOPY, sal_False );
/*?*/ 		if ( InitNew( pMedium->GetStorage() ) )
/*?*/ 		{
/*?*/ 			bIsTmp = !( pMedium->GetStorage() );
/*?*/ 			if ( SFX_CREATE_MODE_EMBEDDED == eCreateMode )
/*?*/ 				SetTitle( String( SfxResId( STR_NONAME ) ));
/*?*/ 
/*?*/             ::com::sun::star::uno::Reference< ::com::sun::star::frame::XModel >  xModel ( GetModel(), ::com::sun::star::uno::UNO_QUERY );
/*?*/             if ( xModel.is() )
/*?*/             {
/*?*/                 SfxItemSet *pSet = GetMedium()->GetItemSet();
/*?*/                 ::com::sun::star::uno::Sequence< ::com::sun::star::beans::PropertyValue > aArgs;
/*?*/                 TransformItems( SID_OPENDOC, *pSet, aArgs );
/*?*/                 sal_Int32 nLength = aArgs.getLength();
/*?*/                 aArgs.realloc( nLength + 1 );
/*?*/                 aArgs[nLength].Name = DEFINE_CONST_UNICODE("Title");
/*?*/                 aArgs[nLength].Value <<= ::rtl::OUString( GetTitle( SFX_TITLE_DETECT ) );
/*?*/                 xModel->attachResource( ::rtl::OUString(), aArgs );
/*?*/             }
/*?*/ 
/*?*/         	SetActivateEvent_Impl( SFX_EVENT_CREATEDOC );
/*?*/ 			return sal_True;
/*?*/ 		}
/*?*/ 		return sal_False;
/*N*/ 	}
/*N*/ 	else
/*N*/ 		return DoInitNew(0);
/*N*/ }


/*N*/ sal_Bool SfxObjectShell::DoInitNew( SvStorage * pStor )

/*  [Beschreibung]

    Diese von SvPersist geerbte virtuelle Methode wird gerufen, um
    die SfxObjectShell-Instanz aus einem Storage (pStor != 0) bzw.
    (pStor == 0) ganz neu zu initialisieren.

    Wie alle Do...-Methoden liegt hier eine Steuerung vor, die eigentliche
    Implementierung erfolgt, indem die ebenfalls virtuellen Methode
    InitNew(SvStorate*) von der SfxObjectShell-Subclass implementiert wird.

    F"ur pStor == 0 wird ein die SfxObjectShell-Instanz mit einem leeren
    SfxMedium verbunden, sonst mit einem SfxMedium, welches auf den
    als Parameter "ubergeben SvStorage verweist.

    Erst nach InitNew() oder Load() ist das Objekt korrekt initialisiert.

    [R"uckgabewert]
    sal_True            Das Objekt wurde initialisiert.
    sal_False           Das Objekt konnte nicht initialisiert werden
*/

/*N*/ {
/*N*/ 	ModifyBlocker_Impl aBlock( this );
/*N*/ 	if ( pStor )
/*N*/ 		pMedium = new SfxMedium( pStor );
/*N*/ 	else
/*N*/ 	{
/*N*/ 		bIsTmp = sal_True;
/*N*/ 		pMedium = new SfxMedium;
/*N*/ 	}
/*N*/ 
/*N*/ 	if ( InitNew( pStor ) )
/*N*/ 	{
/*N*/ 		// empty documents always get their macros from the user, so there is no reason to restrict access
/*N*/ 		pImp->nMacroMode = MacroExecMode::ALWAYS_EXECUTE_NO_WARN;
/*N*/ 		if ( SFX_CREATE_MODE_EMBEDDED == eCreateMode )
/*N*/ 			SetTitle( String( SfxResId( STR_NONAME ) ));
/*N*/ 
/*N*/ 		::com::sun::star::uno::Reference< ::com::sun::star::frame::XModel >  xModel ( GetModel(), ::com::sun::star::uno::UNO_QUERY );
/*N*/ 		if ( xModel.is() )
/*N*/ 		{
/*N*/ 			SfxItemSet *pSet = GetMedium()->GetItemSet();
/*N*/             pSet->Put( SfxStringItem( SID_FILTER_NAME, GetFactory().GetFilter(0)->GetFilterName() ) );
/*N*/ 			::com::sun::star::uno::Sequence< ::com::sun::star::beans::PropertyValue > aArgs;
/*N*/ 			TransformItems( SID_OPENDOC, *pSet, aArgs );
/*N*/             sal_Int32 nLength = aArgs.getLength();
/*N*/             aArgs.realloc( nLength + 1 );
/*N*/             aArgs[nLength].Name = DEFINE_CONST_UNICODE("Title");
/*N*/             aArgs[nLength].Value <<= ::rtl::OUString( GetTitle( SFX_TITLE_DETECT ) );
/*N*/             xModel->attachResource( ::rtl::OUString(), aArgs );
/*N*/ 		}
/*N*/ 
/*N*/         SetActivateEvent_Impl( SFX_EVENT_CREATEDOC );
/*N*/ 		return sal_True;
/*N*/ 	}
/*N*/ 	return sal_False;
/*N*/ }

//-------------------------------------------------------------------------

void SfxObjectShell::DoHandsOffNoMediumClose()
/*N*/ {
/*N*/     const SfxFilter *pFilter = pMedium->GetFilter();
/*N*/     if( !pFilter || pFilter->IsOwnFormat() || ( pFilter->GetFilterFlags() & SFX_FILTER_PACKED ) )
/*N*/ 		HandsOff();
/*N*/ 
/*N*/ 	// Force document library containers to release storage
/*N*/ 	SotStorageRef xDummyStorage;
/*N*/ 	SfxDialogLibraryContainer* pDialogCont = pImp->pDialogLibContainer;
/*N*/ 	if( pDialogCont )
/*N*/ 		pDialogCont->setStorage( xDummyStorage );
/*N*/ 
/*N*/ 	SfxScriptLibraryContainer* pBasicCont = pImp->pBasicLibContainer;
/*N*/ 	if( pBasicCont )
/*N*/ 		pBasicCont->setStorage( xDummyStorage );
/*N*/ }

//-------------------------------------------------------------------------

/*N*/ void SfxObjectShell::DoHandsOff()

/*  [Beschreibung]

    Diese von SvPersist geerbte virtuelle Methode wird gerufen, um
    das Objekt aufzufordern, den ihm zugeteilten SvStorage freizugeben,
    insbesondere Substorages und Streams zu schlie"sen.

    Als Do...-Methode liegt hier nur die Steuerung. Der Implementierer
    von Subclasses kann die ebenfalls virtuelle Methode HandsOff()
    implementieren, um seine Substorages und Streams zu schlie"sen.

    Nach dem Aufruf dieser Methode, ist dem Objekt kein SfxMedium mehr
    zugeordnet, bis SaveCompleted() durchlaufen ist.
*/

/*N*/ {
/*N*/ 	DoHandsOffNoMediumClose();
/*N*/ 	pMedium->Close();
/*N*/ //  DELETEZ( pMedium );
/*N*/ }

//-------------------------------------------------------------------------

/*?*/ sal_Bool SfxObjectShell::DoLoad(
/*?*/ 	const String& rFileName, StreamMode nStreamMode, StorageMode nStorageMode)
/*?*/ {DBG_BF_ASSERT(0, "STRIP"); //STRIP001 
//STRIP001 /*?*/ 	// Es wird nur die IPersistStorage-Schnittstelle angeboten
//STRIP001 /*?*/ 	ModifyBlocker_Impl aBlock( this );
//STRIP001 /*?*/ 	SvStorageRef xStor = new SvStorage( rFileName, nStreamMode | STREAM_WRITE, nStorageMode );
//STRIP001 /*?*/ 	if( !xStor.Is() )
//STRIP001 /*?*/ 		xStor = new SvStorage( rFileName, nStreamMode, nStorageMode );
//STRIP001 /*?*/ 
//STRIP001 /*?*/ 	if ( SVSTREAM_OK == xStor->GetError() )
//STRIP001 /*?*/ 	{
//STRIP001 /*?*/ 		SfxMedium* pMedium = new SfxMedium( xStor );
//STRIP001 /*?*/ 		pMedium->SetName( rFileName );
//STRIP001 /*?*/ 		pMedium->Init_Impl();
//STRIP001 /*?*/ 
//STRIP001 /*?*/ 		// Muss !!!
//STRIP001 /*?*/ 		SetFileName( rFileName );
//STRIP001 /*?*/ 
//STRIP001 /*?*/ 		if( DoLoad( pMedium ) )
//STRIP001 /*?*/ 		{
//STRIP001 /*?*/ 			if ( SFX_CREATE_MODE_EMBEDDED == eCreateMode )
//STRIP001 /*?*/ 				SetTitle( rFileName );
//STRIP001 /*?*/ 			return sal_True;
//STRIP001 /*?*/ 		}
//STRIP001 /*?*/ 	}
/*?*/ 	return sal_False;
/*?*/ }


//-------------------------------------------------------------------------

/*N*/ sal_Bool SfxObjectShell::DoLoad( SvStorage * pStor )

/*  [Beschreibung]

    Diese von SvPersist geerbte virtuelle Methode steuert das Laden
    des Objektes aus einem Storage. Dabei wird der SvStorage zun"achst
    in einem SfxMedium verpackt und SfxObjectShell::DoLoad(SfxMedium*)
    mit diesem gerufen.

    [R"uckgabewert]
    sal_True                Das Objekt wurde initialisiert.
    sal_False               Das Objekt konnte nicht initialisiert werden
*/

/*N*/ {
/*N*/ 	pMedium = new SfxMedium( pStor );
/*N*/ 	if ( DoLoad(pMedium) )
/*N*/ 	{
/*N*/ 		if ( SFX_CREATE_MODE_EMBEDDED == eCreateMode )
/*N*/ 		{
/*N*/ 			ModifyBlocker_Impl aBlock( this );
/*N*/ 			// bei Embedded Objekten setzt sonst keiner den Namen
/*N*/ //            DBG_ASSERT( pStor->GetName().Len(),
/*N*/ //                        "StorageName hat Laenge Null" );
/*N*/ 			SetTitle( pStor->GetName() );
/*N*/ 		}
/*N*/ 		return sal_True;
/*N*/ 	}
/*N*/ 
/*N*/ 	return sal_False;
/*N*/ }

//-------------------------------------------------------------------------

/*N*/ sal_Bool SfxObjectShell::DoLoad( SfxMedium *pMed )

/*  [Beschreibung]

    Diese Methode steuert das Laden des Objektes aus dem von dem
    "ubergebenen SfxMedium beschriebenen Medium. Hinterher ist das Objekt
    mit diesem SfxMedium verbunden.

    Handelt es sich bei dem SfxMedium um einen Storage im eigenen Format,
    wird die virtuelle Methode SvPersit::Load(SvStorage*) gerufen, welche
    die Implementierer von Subclasses "uberladen m"ussen, um das Objekt
    aus einem eigenen Storage zu laden (=> Swapping m"oeglich).

    Handelt es sich bei dem SfxMedium um einen Storage in einem fremden
    Format, oder um ein Flat-File, dann wird die virtuelle Methode
    <SfxObjectShell::ConvertFrom(SfxMedium*)> gerufen, welche die
    Implementierer von Subclasses "uberladen m"ussen, um das Objekt
    aus dem SfxMedium zu konvertieren. W"ahrend der Bearbeitung ist
    das Objekt dann mit einem tempor"aren SvStorage verbunden.

    Erst nach InitNew() oder Load() ist das Objekt korrekt
    initialisiert.

    [R"uckgabewert]
    sal_True                Das Objekt wurde geladen.
    sal_False           Das Objekt konnte nicht geladen werden
*/

/*N*/ {
/*N*/ 	SfxApplication *pSfxApp = SFX_APP();
/*N*/ 	ModifyBlocker_Impl aBlock( this );
/*N*/ 
/*N*/ 	if ( SFX_CREATE_MODE_EMBEDDED != eCreateMode )
/*N*/ 		GetpApp()->ShowStatusText( SfxResId(STR_DOC_LOADING) );
/*N*/ 
/*N*/ 	pMedium = pMed;
/*N*/ 	sal_Bool bOk = sal_False;
/*N*/ 	const SfxFilter* pFilter = pMed->GetFilter();
/*N*/ 	SfxItemSet* pSet = pMedium->GetItemSet();
/*N*/ 	if( !pImp->nEventId )
/*N*/ 	{
/*N*/ 		SFX_ITEMSET_ARG(
/*N*/ 			pSet, pTemplateItem, SfxBoolItem,
/*N*/ 			SID_TEMPLATE, sal_False);
/*N*/ #if SUPD < 635
/*N*/         SFX_ITEMSET_ARG(
/*N*/             pSet, pBrowsingItem, SfxBoolItem, SID_BROWSING, sal_False );
/*N*/         SetActivateEvent_Impl(
/*N*/             ( pTemplateItem && pTemplateItem->GetValue() )
/*N*/             ? SFX_EVENT_CREATEDOC : SFX_EVENT_OPENDOC,
/*N*/             pBrowsingItem && pBrowsingItem->GetValue() );
/*N*/ #else
/*N*/         SetActivateEvent_Impl(
/*N*/ 			( pTemplateItem && pTemplateItem->GetValue() )
/*N*/             ? SFX_EVENT_CREATEDOC : SFX_EVENT_OPENDOC );
/*N*/ #endif
/*N*/ 	}
/*N*/ 
/*N*/ 
/*N*/ 	SFX_ITEMSET_ARG( pSet, pBaseItem, SfxStringItem,
/*N*/ 					 SID_BASEURL, sal_False);
/*N*/ 	String aBaseURL;
/*N*/ 	SFX_ITEMSET_ARG( pMedium->GetItemSet(), pSalvageItem, SfxStringItem, SID_DOC_SALVAGE, sal_False);
/*N*/ 	if( pBaseItem )
/*N*/ 		aBaseURL = pBaseItem->GetValue();
/*N*/ 	else
/*N*/ 	{
/*N*/ 		if( GetCreateMode() == SFX_CREATE_MODE_EMBEDDED )
/*N*/ 		{
/*N*/ 			aBaseURL = so3::StaticBaseUrl::GetBaseURL();
/*N*/ 			SetBaseURL( aBaseURL );
/*N*/ 		}
/*N*/ 		else if ( pSalvageItem )
/*N*/ 		{
/*N*/             String aName( pMed->GetPhysicalName() );
/*N*/             ::utl::LocalFileHelper::ConvertPhysicalNameToURL( aName, aBaseURL );
/*N*/ 		}
/*N*/ 		else
/*N*/ 			aBaseURL = pMed->GetBaseURL();
/*N*/ 	}
/*N*/ 
/*N*/ 	SfxApplication* pApp = SFX_APP();
/*N*/ 	pImp->nLoadedFlags = 0;
/*N*/     sal_Bool bHasStorage = !pFilter || ( pFilter->IsOwnFormat() && pFilter->UsesStorage() );
/*N*/ 	if ( !bHasStorage && pFilter && ( pFilter->GetFilterFlags() & SFX_FILTER_PACKED ) )
/*N*/ 	{
/*N*/ 		bHasStorage = pMed->TryStorage();
/*N*/ 		if ( bHasStorage )
/*N*/ 		{
/*N*/             String aName( pMed->GetPhysicalName() );
/*N*/             ::utl::LocalFileHelper::ConvertPhysicalNameToURL( aName, aBaseURL );
/*N*/ 		}
/*N*/ 	}
/*N*/ 
/*N*/ 	if ( pMedium->GetFilter() )
/*N*/ 	{
/*N*/ 		sal_uInt32 nError = HandleFilter( pMedium, this );
/*N*/ 		if ( nError != ERRCODE_NONE )
/*N*/ 			SetError( nError );
/*N*/ 	}
/*N*/ 
/*N*/     if ( GetError() == ERRCODE_NONE && pMed->IsStorage() ) // STRIP003 && bHasStorage && ( !pFilter || !( pFilter->GetFilterFlags() & SFX_FILTER_STARONEFILTER ) ) )
/*N*/ 	{
/*N*/ 		SvStorageRef xStor( pMed->GetStorage() );
/*N*/ 		if( pMed->GetLastStorageCreationState() == ERRCODE_NONE )
/*N*/ 		{
/*N*/         	DBG_ASSERT( pFilter, "No filter for storage found!" );
/*N*/         	if( xStor.Is() && !xStor->GetError() && pMed->GetFilter() && pMed->GetFilter()->GetVersion() < SOFFICE_FILEFORMAT_60 )
/*N*/ 			{
/*N*/             	// Undoobjekte aufraeumen, muss vor dem eigentlichen Laden erfolgen
/*N*/ 				SvEmbeddedObjectRef xThis = this;
/*N*/ 				SvPersistRef xPer;
/*N*/ 				if ( xThis.Is() )
/*N*/ 					xPer = new SvEmbeddedObject;
/*N*/ 				else
/*?*/ 					xPer = new SvPersist;
/*N*/ 
/*N*/ 				xPer->DoOwnerLoad(xStor);
/*N*/ 				xPer->CleanUp();
/*N*/ 				xPer->DoSave();
/*N*/ 				xPer->DoSaveCompleted( 0 );
/*N*/ 			}
/*N*/ 
/*N*/         	if ( xStor.Is() )
/*N*/         	{
/*N*/             	SvStorageInfoList aList;
/*N*/             	xStor->FillInfoList( &aList );
/*N*/             	if ( !aList.Count() && !xStor->IsOLEStorage() )
/*?*/                 	SetError( ERRCODE_IO_BROKENPACKAGE );
/*N*/             	else
/*N*/             	{
/*N*/                 	BOOL bHasMacros = FALSE;
/*N*/                 	if ( xStor->IsOLEStorage() )
/*N*/                     	bHasMacros = BasicManager::HasBasicWithModules(
                                *xStor,
                                so3::StaticBaseUrl::GetBaseURL(
                                    INetURLObject::NO_DECODE) );
/*N*/                 	else
/*?*/                     	bHasMacros = xStor->IsStorage( String::CreateFromAscii("Basic") );
/*N*/ 
/*N*/                 	if ( bHasMacros )
/*N*/                     	AdjustMacroMode( String() );
/*N*/ 					else
/*N*/ 					{
/*N*/ 						// if macros will be added by the user later, the security check is obsolete
/*N*/ 						pImp->nMacroMode = MacroExecMode::ALWAYS_EXECUTE_NO_WARN;
/*N*/ 					}
/*N*/             	}
/*N*/         	}
/*N*/ 
/*N*/         	// Load
/*N*/         	if ( !GetError() )
/*N*/         	{
/*N*/             	const String aOldURL( so3::StaticBaseUrl::GetBaseURL() );
/*N*/             	if( aBaseURL.Len() ) so3::StaticBaseUrl::SetBaseURL( aBaseURL );
/*N*/             	pImp->nLoadedFlags = 0;
/*N*/             	bOk = xStor.Is() && LoadOwnFormat( *pMed );
/*N*/             	so3::StaticBaseUrl::SetBaseURL( aOldURL );
/*N*/             	if ( bOk )
/*N*/             	{
/*N*/                 	GetDocInfo().Load(xStor);
/*N*/                 	bHasName = sal_True;
/*N*/             	}
/*N*/             	else
/*?*/                 	SetError( ERRCODE_ABORT );
/*N*/         	}
/*N*/ 		}
/*N*/ 		else
/*?*/ 			SetError( pMed->GetLastStorageCreationState() );
/*N*/ 	} else /*STRIP003 IsStorage() IS required, else file is corrupt */ { SetError(ERRCODE_IO_WRONGFORMAT); bOk = sal_False; }
//STRIP003/*N*/     else if ( GetError() == ERRCODE_NONE && InitNew(0) )
//STRIP003/*?*/ /*N*/ 	{
//STRIP003/*?*/ 		// Name vor ConvertFrom setzen, damit GetSbxObject() schon funktioniert
//STRIP003/*?*/ 		bHasName = sal_True;
//STRIP003/*?*/ 		SetName( SfxResId( STR_NONAME ) );
//STRIP003/*?*/ 
//STRIP003/*?*/ 		// Importieren
//STRIP003/*?*/ 		const String aOldURL( so3::StaticBaseUrl::GetBaseURL() );
//STRIP003/*?*/ 		if( aBaseURL.Len() ) so3::StaticBaseUrl::SetBaseURL( aBaseURL );
//STRIP003/*?*/         if( !pMedium->GetFilter()->UsesStorage() )
//STRIP003/*?*/ 			pMedium->GetInStream();
//STRIP003/*?*/         else
//STRIP003/*?*/             pMedium->GetStorage();
//STRIP003/*?*/ 
//STRIP003/*?*/ 		pImp->nLoadedFlags = 0;
//STRIP003/*?*/ 		if ( pMedium->GetFilter() &&  ( pMedium->GetFilter()->GetFilterFlags() & SFX_FILTER_STARONEFILTER ) )
//STRIP003/*?*/ 		{
//STRIP003/*?*/ 			bOk = ImportFrom(*pMedium);
//STRIP003/*?*/             FinishedLoading( SFX_LOADED_ALL );
//STRIP003/*?*/ 		}
//STRIP003/*?*/ 		else
//STRIP003/*?*/ 		{
//STRIP003/*?*/ 			bOk = ConvertFrom(*pMedium);
//STRIP003/*?*/ 		}
//STRIP003/*?*/ 
//STRIP003/*?*/ 		so3::StaticBaseUrl::SetBaseURL( aOldURL );
//STRIP003/*?*/ 
//STRIP003/*?*/         if( bOk && pMedium->GetOpenMode() & STREAM_WRITE )
//STRIP003/*?*/ 		//Medium offen halten um andere Zugriffe zu verhindern
//STRIP003/*?*/ 		{
//STRIP003/*?*/ 			if(pMedium->GetFilter() && pMedium->GetFilter()->UsesStorage())
//STRIP003/*?*/ 			{
//STRIP003/*?*/ 				pMedium->GetStorage();
//STRIP003/*?*/ 				if( pMedium->GetLastStorageCreationState() != ERRCODE_NONE )
//STRIP003/*?*/ 					pMedium->SetError( pMedium->GetLastStorageCreationState() );
//STRIP003/*?*/ 			}
//STRIP003/*?*/ 			else
//STRIP003/*?*/ 				pMedium->GetInStream();
//STRIP003/*?*/ 			if(pMedium->GetError())
//STRIP003/*?*/ 				bOk = sal_False;
//STRIP003/*?*/ 		}
//STRIP003/*?*/ 	}
/*N*/ 
/*N*/ 	if ( bOk )
/*N*/ 	{
/*N*/         try
/*?*/ /*N*/         {
/*?*/             ::ucb::Content aContent( pMedium->GetName(), ::com::sun::star::uno::Reference < XCommandEnvironment >() );
/*?*/             ::com::sun::star::uno::Reference < XPropertySetInfo > xProps = aContent.getProperties();
/*?*/             if ( xProps.is() )
/*?*/             {
/*?*/                 ::rtl::OUString aAuthor( RTL_CONSTASCII_USTRINGPARAM("Author") );
/*?*/                 ::rtl::OUString aKeywords( RTL_CONSTASCII_USTRINGPARAM("Keywords") );
/*?*/                 ::rtl::OUString aSubject( RTL_CONSTASCII_USTRINGPARAM("Subject") );
/*?*/                 Any aAny;
/*?*/                 ::rtl::OUString aValue;
/*?*/                 SfxDocumentInfo& rInfo = GetDocInfo();
/*?*/                 if ( xProps->hasPropertyByName( aAuthor ) )
/*?*/                 {
/*?*/                     aAny = aContent.getPropertyValue( aAuthor );
/*?*/                     if ( ( aAny >>= aValue ) )
/*?*/                         rInfo.SetCreated( SfxStamp( String( aValue ) ) );
/*?*/                 }
/*?*/                 if ( xProps->hasPropertyByName( aKeywords ) )
/*?*/                 {
/*?*/                     aAny = aContent.getPropertyValue( aKeywords );
/*?*/                     if ( ( aAny >>= aValue ) )
/*?*/                         rInfo.SetKeywords( aValue );
/*?*/                 }
/*?*/                 if ( xProps->hasPropertyByName( aSubject ) )
/*?*/                 {
/*?*/                     aAny = aContent.getPropertyValue( aSubject );
/*?*/                     if ( ( aAny >>= aValue ) )
/*?*/                         rInfo.SetTheme( aValue );
/*?*/                 }
/*?*/             }
/*?*/         }
/*N*/         catch( Exception& )
/*N*/         {
/*N*/         }
/*N*/ 
/*N*/         ::rtl::OUString aTitle = GetTitle( SFX_TITLE_DETECT );
/*N*/ 
/*N*/ 		// Falls nicht asynchron geladen wird selbst FinishedLoading aufrufen
/*N*/ 		if ( !( pImp->nLoadedFlags & SFX_LOADED_MAINDOCUMENT ) &&
/*N*/             ( !pMedium->GetFilter() ||
/*N*/                pMedium->GetFilter()->UsesStorage() ||
/*N*/                !( pMedium->GetFilter()->GetFilterFlags() & SFX_FILTER_ASYNC ) ||
/*N*/                !pMedium->GetLoadEnvironment() ) )
/*N*/ 			FinishedLoading( SFX_LOADED_MAINDOCUMENT );
/*N*/ 
/*N*/ 		if ( pSalvageItem )
/*N*/ 		{
/*?*/             pImp->aTempName = pMedium->GetPhysicalName();
/*?*/ 			pMedium->GetItemSet()->ClearItem( SID_DOC_SALVAGE );
/*?*/ 			pMedium->GetItemSet()->ClearItem( SID_FILE_NAME );
/*N*/ 		}
/*N*/ 		else
/*N*/ 		{
/*N*/ 			pMedium->GetItemSet()->ClearItem( SID_PROGRESS_STATUSBAR_CONTROL );
/*N*/ 			pMedium->GetItemSet()->ClearItem( SID_DOCUMENT );
/*N*/ 		}
/*N*/ 
/*N*/ 		pMedium->GetItemSet()->ClearItem( SID_REFERER );
/*N*/ 		::com::sun::star::uno::Reference< ::com::sun::star::frame::XModel >  xModel ( GetModel(), ::com::sun::star::uno::UNO_QUERY );
/*N*/ 		if ( xModel.is() )
/*N*/ 		{
/*N*/ 			::rtl::OUString aURL = GetMedium()->GetOrigURL();
/*N*/ 			SfxItemSet *pSet = GetMedium()->GetItemSet();
/*N*/             if ( !GetMedium()->IsReadOnly() )
/*N*/                 pSet->ClearItem( SID_INPUTSTREAM );
/*N*/ 			::com::sun::star::uno::Sequence< ::com::sun::star::beans::PropertyValue > aArgs;
/*N*/ 			TransformItems( SID_OPENDOC, *pSet, aArgs );
/*N*/ 			xModel->attachResource( aURL, aArgs );
/*N*/ 		}
/*N*/ 
/*N*/         if( IsOwnStorageFormat_Impl(*pMed) && pMed->GetFilter() )
/*N*/ 		{
/*N*/ //???? dv			DirEntry aDirEntry( pMed->GetPhysicalName() );
/*N*/ //???? dv			SetFileName( aDirEntry.GetFull() );
/*N*/ 		}
/*N*/ 		Broadcast( SfxSimpleHint(SFX_HINT_NAMECHANGED) );
/*N*/ 	}
/*N*/ 
/*N*/ 	if ( SFX_CREATE_MODE_EMBEDDED != eCreateMode )
/*N*/ 	{
/*N*/ 		GetpApp()->HideStatusText();
/*N*/ 
//STRIP007 		SFX_ITEMSET_ARG( pMedium->GetItemSet(), pAsTempItem, SfxBoolItem, SID_TEMPLATE, sal_False);
//STRIP007 		SFX_ITEMSET_ARG( pMedium->GetItemSet(), pPreviewItem, SfxBoolItem, SID_PREVIEW, sal_False);
//STRIP007 		SFX_ITEMSET_ARG( pMedium->GetItemSet(), pHiddenItem, SfxBoolItem, SID_HIDDEN, sal_False);
//STRIP007 		if( bOk && pMedium->GetOrigURL().Len()
//STRIP007 		 && !( pAsTempItem && pAsTempItem->GetValue() )
//STRIP007 		 && !( pPreviewItem && pPreviewItem->GetValue() )
//STRIP007 		 && !( pHiddenItem && pHiddenItem->GetValue() ) )
//STRIP007 		{
//STRIP007 			INetURLObject aUrl( pMedium->GetOrigURL() );
//STRIP007 			if ( aUrl.GetProtocol() == INET_PROT_FILE )
//STRIP007 				SystemShell::AddToRecentDocumentList( aUrl.GetURLNoPass( INetURLObject::NO_DECODE ) );
//STRIP007 		}
/*N*/ 	}
/*N*/ 
/*N*/ 	return bOk;
/*N*/ }

/*N*/ sal_uInt32 SfxObjectShell::HandleFilter( SfxMedium* pMedium, SfxObjectShell* pDoc )
/*N*/ {
/*N*/ 	sal_uInt32 nError = ERRCODE_NONE;
/*N*/ 	SfxItemSet* pSet = pMedium->GetItemSet();
/*N*/ 	SFX_ITEMSET_ARG( pSet, pOptions, SfxStringItem, SID_FILE_FILTEROPTIONS, sal_False );
/*N*/ 	SFX_ITEMSET_ARG( pSet, pData, SfxUsrAnyItem, SID_FILTER_DATA, sal_False );
/*N*/ 	if ( !pData && !pOptions )
/*N*/ 	{
/*N*/     	::com::sun::star::uno::Reference< XMultiServiceFactory > xServiceManager = ::legacy_binfilters::getLegacyProcessServiceFactory();
/*N*/ 		::com::sun::star::uno::Reference< XNameAccess > xFilterCFG;
/*N*/ 		if( xServiceManager.is() )
/*N*/ 		{
/*N*/ 			xFilterCFG = ::com::sun::star::uno::Reference< XNameAccess >(
/*N*/ 				xServiceManager->createInstance( ::rtl::OUString::createFromAscii( "com.sun.star.document.FilterFactory" ) ),
/*N*/ 				UNO_QUERY );
/*N*/ 		}
/*N*/ 
/*N*/ 		if( xFilterCFG.is() )
/*N*/     	{
/*N*/         	BOOL bAbort = FALSE;
/*N*/         	try {
/*N*/ 				const SfxFilter* pFilter = pMedium->GetFilter();
/*N*/             	Sequence < PropertyValue > aProps;
/*N*/             	Any aAny = xFilterCFG->getByName( pFilter->GetName() );
/*N*/             	if ( aAny >>= aProps )
/*N*/             	{
/*N*/                 	::rtl::OUString aServiceName;
/*N*/                 	sal_Int32 nPropertyCount = aProps.getLength();
/*N*/                 	for( sal_Int32 nProperty=0; nProperty < nPropertyCount; ++nProperty )
/*N*/                     	if( aProps[nProperty].Name.equals( ::rtl::OUString::createFromAscii("UIComponent")) )
/*N*/                     	{
/*N*/                         	::rtl::OUString aServiceName;
/*N*/                         	aProps[nProperty].Value >>= aServiceName;
/*N*/                         	if( aServiceName.getLength() )
/*?*/                         	{
/*?*/ 								::com::sun::star::uno::Reference< XInteractionHandler > rHandler = pMedium->GetInteractionHandler();
/*?*/ 								if( rHandler.is() )
/*?*/ 								{
/*?*/ 									// we need some properties in the media descriptor, so we have to make sure that they are in
/*?*/ 									Any aAny;
/*?*/ 									aAny <<= pMedium->GetInputStream();
/*?*/ 									if ( pSet->GetItemState( SID_INPUTSTREAM ) < SFX_ITEM_SET )
/*?*/ 									pSet->Put( SfxUsrAnyItem( SID_INPUTSTREAM, aAny ) );
/*?*/ 									if ( pSet->GetItemState( SID_FILE_NAME ) < SFX_ITEM_SET )
/*?*/ 										pSet->Put( SfxStringItem( SID_FILE_NAME, pMedium->GetName() ) );
/*?*/ 									if ( pSet->GetItemState( SID_FILTER_NAME ) < SFX_ITEM_SET )
/*?*/ 										pSet->Put( SfxStringItem( SID_FILTER_NAME, pFilter->GetName() ) );
/*?*/ 
/*?*/ 									Sequence< PropertyValue > rProperties;
/*?*/                                 	TransformItems( SID_OPENDOC, *pSet, rProperties, NULL );
/*?*/ 									RequestFilterOptions* pFORequest = new RequestFilterOptions( pDoc->GetModel(), rProperties );
/*?*/ 
/*?*/ 									::com::sun::star::uno::Reference< XInteractionRequest > rRequest( pFORequest );
/*?*/ 									rHandler->handle( rRequest );
/*?*/ 
/*?*/ 									if ( !pFORequest->isAbort() )
/*?*/ 									{
/*?*/                                    		SfxAllItemSet aNewParams( pDoc->GetPool() );
/*?*/                                    		TransformParameters( SID_OPENDOC,
/*?*/ 														 	pFORequest->getFilterOptions(),
/*?*/                                                          	aNewParams,
/*?*/                                                          	NULL );
/*?*/ 
/*?*/                                    		SFX_ITEMSET_ARG( &aNewParams,
/*?*/ 													 	pOptions,
/*?*/ 													 	SfxStringItem,
/*?*/ 													 	SID_FILE_FILTEROPTIONS,
/*?*/ 													 	sal_False );
/*?*/                                    		if ( pOptions )
/*?*/                                        		pSet->Put( *pOptions );
/*?*/ 
/*?*/                                    		SFX_ITEMSET_ARG( &aNewParams,
/*?*/ 													 	pData,
/*?*/ 													 	SfxUsrAnyItem,
/*?*/ 													 	SID_FILTER_DATA,
/*?*/ 													 	sal_False );
/*?*/                                    		if ( pData )
/*?*/                                        		pSet->Put( *pData );
/*?*/ 									}
/*?*/                                 	else
/*?*/                                     	bAbort = TRUE;
/*?*/ 								}
/*?*/                         	}
/*N*/ 
/*N*/                         	break;
/*N*/                     	}
/*N*/             	}
/*N*/ 
/*N*/             	if( bAbort )
/*N*/ 				{
/*N*/ 					// filter options were not entered
/*N*/ 					nError = ERRCODE_ABORT;
/*N*/ 				}
/*N*/         	}
/*N*/         	catch( NoSuchElementException& )
/*N*/         	{
/*N*/             	// the filter name is unknown
/*N*/             	nError = ERRCODE_IO_INVALIDPARAMETER;
/*N*/         	}
/*N*/         	catch( Exception& )
/*N*/         	{
/*N*/ 				nError = ERRCODE_ABORT;
/*N*/         	}
/*N*/     	}
/*N*/ 	}
/*N*/ 
/*N*/ 	return nError;
/*N*/ }

//-------------------------------------------------------------------------

/*N*/ sal_Bool SfxObjectShell::IsOwnStorageFormat_Impl(const SfxMedium &rMedium) const
/*N*/ {
/*N*/ 	return !rMedium.GetFilter() || // Embedded
/*N*/ 		   ( rMedium.GetFilter()->IsOwnFormat() &&
/*N*/ 			 rMedium.GetFilter()->UsesStorage() );
/*N*/ }

//-------------------------------------------------------------------------

/*N*/ sal_Bool SfxObjectShell::DoSave()
// DoSave wird nur noch ueber OLE aufgerufen. Sichern eigener Dokumente im SFX
// laeuft uber DoSave_Impl, um das Anlegen von Backups zu ermoeglichen.
// Save in eigenes Format jetzt auch wieder Hierueber
/*N*/ {
/*N*/ 	sal_Bool bOk = sal_False ;
/*N*/ 	{
/*N*/ 		ModifyBlocker_Impl aBlock( this );
/*N*/ 		SfxForceLinkTimer_Impl aFLT( this );
/*N*/ 		pImp->bIsSaving = sal_True;
/*N*/ 		String aPasswd;
/*N*/ 		if ( IsOwnStorageFormat_Impl( *GetMedium() ) &&
/*N*/ 			 GetPasswd_Impl( GetMedium()->GetItemSet(), aPasswd ) )
/*N*/ 			GetMedium()->GetStorage()->SetKey( S2BS( aPasswd ) );	//!!! (pb) needs new implementation
/*N*/ 		GetStorage()->SetVersion( GetMedium()->GetFilter()->GetVersion() );
/*N*/ 		bOk = Save();
/*N*/ 	}

//#88046
//    if ( bOk )
//        SetModified( sal_False );
/*N*/ 	return bOk;
/*N*/ }

/*N*/ void Lock_Impl( SfxObjectShell* pDoc, BOOL bLock )
/*N*/ {
/*N*/     SfxViewFrame *pFrame= SfxViewFrame::GetFirst( pDoc );
/*N*/ 	while ( pFrame )
/*N*/ 	{
/*N*/         pFrame->GetDispatcher()->Lock( bLock );
/*N*/         pFrame->Enable( !bLock );
/*N*/         pFrame = SfxViewFrame::GetNext( *pFrame, pDoc );
/*N*/ 	}
/*N*/ 
/*N*/ }

//-------------------------------------------------------------------------

/*N*/ sal_Bool SfxObjectShell::SaveTo_Impl
/*N*/ (
/*N*/ 	 SfxMedium &rMedium, // Medium, in das gespeichert werden soll
/*N*/      const SfxItemSet* pSet,
/*N*/      BOOL bPrepareForDirectAccess
/*N*/ )

/*  [Beschreibung]

    Schreibt den aktuellen Inhalt in das Medium rMedium.
    Ist das Zielmedium kein Storage, so wird ueber ein temporaeres
    Medium gespeichert, sonst direkt, da das Medium transacted
    geschaltet ist, wenn wir es selbst geoeffnet haben und falls wir
    Server sind entweder der Container einen transacted Storage zur
    Verfuegung stellt oder selbst einen temporaeren Storage erzeugt hat.
*/

/*N*/ {
/*N*/ 	SfxForceLinkTimer_Impl aFLT( this );
/*N*/     EnableSetModified( FALSE );
/*N*/ 
/*N*/ 	const SfxFilter *pFilter = rMedium.GetFilter();
/*N*/ 	if ( !pFilter )
/*N*/ 	{
/*N*/         // if no filter was set, use the default filter
/*N*/         // this should be changed in the feature, it should be an error!
/*?*/ 		pFilter = GetFactory().GetFilter(0);
/*?*/ 		rMedium.SetFilter(pFilter);
/*N*/ 	}
/*N*/ 
/*N*/     if( pFilter->UsesStorage() )
/*N*/         // create an output storage in the correct format
/*N*/         rMedium.GetOutputStorage( SOFFICE_FILEFORMAT_60 <= pFilter->GetVersion() );
/*N*/ 	else
/*?*/ 		rMedium.GetOutStream();
/*N*/ 
/*N*/ 	if( rMedium.GetErrorCode() )
/*N*/ 		return sal_False;
/*N*/ 
/*N*/ 	sal_Bool bOldStat = pImp->bForbidReload;
/*N*/ 	pImp->bForbidReload = sal_True;
/*N*/ 
/*N*/     // lock user interface while saving the document
/*N*/     Lock_Impl( this, sal_True );
/*N*/ 
/*N*/ 	sal_Bool bOk = sal_False;
/*N*/	if( sal_True ) // STRIP003 IsOwnStorageFormat_Impl(rMedium) && !(pFilter->GetFilterFlags() & SFX_FILTER_STARONEFILTER))
/*N*/ 	{
/*N*/ 		SvStorageRef aMedRef = rMedium.GetStorage();
/*N*/ 		if ( !aMedRef.Is() )
/*N*/         {
/*?*/             // no saving without storage, unlock UI and return
/*?*/             Lock_Impl( this, sal_False );
/*?*/ 			return sal_False;
/*N*/         }
/*N*/ 
/*N*/         // transfer password from the parameters to the storage
/*N*/         String aPasswd;
/*N*/ 		if ( GetPasswd_Impl( rMedium.GetItemSet(), aPasswd ) )
/*N*/ 			aMedRef->SetKey( S2BS( aPasswd ) ); //!!! (pb) needs new implementation
/*N*/ 
/*N*/ 		const SfxFilter* pFilter = rMedium.GetFilter();
/*N*/ 		if(  ((SvStorage *)aMedRef) == ((SvStorage *)GetStorage() ) )
/*N*/ 		{
/*N*/             // target storage and object storage are identical, should never happen here
/*?*/             DBG_ERROR( "Saving storage without copy!");
/*?*/ 			aMedRef->SetVersion( pFilter->GetVersion() );
/*?*/ 			bOk = Save();
/*N*/ 		}
/*N*/ 		else
/*N*/             // save to target
/*N*/ 			bOk = SaveAsOwnFormat( rMedium );
/*N*/ 
/*N*/         // look for a "version" parameter
/*N*/ 		const SfxStringItem *pVersionItem = pSet ? (const SfxStringItem*)
/*N*/             SfxRequest::GetItem( pSet, SID_DOCINFO_COMMENTS, sal_False, TYPE(SfxStringItem) ) : NULL;
/*N*/ 
/*N*/ 		if ( pVersionItem )
/*N*/ 		{DBG_BF_ASSERT(0, "STRIP"); //STRIP001 
//STRIP001 /*?*/             // store a version also
//STRIP001 /*?*/             const SfxStringItem *pAuthorItem = pSet ? (const SfxStringItem*)
//STRIP001 /*?*/                 SfxRequest::GetItem( pSet, SID_DOCINFO_AUTHOR, sal_False, TYPE(SfxStringItem) ) : NULL;
//STRIP001 /*?*/ 
//STRIP001 /*?*/             // version comment
//STRIP001 /*?*/ 			SfxVersionInfo aInfo;
//STRIP001 /*?*/ 			aInfo.aComment = pVersionItem->GetValue();
//STRIP001 /*?*/ 
//STRIP001 /*?*/             // version author
//STRIP001 /*?*/ 			String aAuthor;
//STRIP001 /*?*/ 			if ( pAuthorItem )
//STRIP001 /*?*/ 				aAuthor = pAuthorItem->GetValue();
//STRIP001 /*?*/ 			else
//STRIP001 /*?*/                 // if not transferred as a parameter, get it from user settings
//STRIP001 /*?*/ 				aAuthor = SvtUserOptions().GetFullName();
//STRIP001 /*?*/ 
//STRIP001 /*?*/             // time stamp for version
//STRIP001 /*?*/             aInfo.aCreateStamp.SetName( aAuthor );
//STRIP001 /*?*/ 
//STRIP001 /*?*/             // desired format for version information
//STRIP001 /*?*/             sal_Bool bUseXML = SOFFICE_FILEFORMAT_60 <= pFilter->GetVersion();
//STRIP001 /*?*/ 
//STRIP001 /*?*/             // get storage for version streams
//STRIP001 /*?*/             SvStorageRef xVersion = bUseXML ?
//STRIP001 /*?*/                     aMedRef->OpenUCBStorage( DEFINE_CONST_UNICODE( "Versions" ) ) :
//STRIP001 /*?*/                     aMedRef->OpenStorage( DEFINE_CONST_UNICODE( "Versions" ) );
//STRIP001 /*?*/ 
//STRIP001 /*?*/             // all preliminary saved versions must be copied from the object storage to the the target storage
//STRIP001 /*?*/             SvStorageRef xOldVersions = GetStorage()->OpenStorage( DEFINE_CONST_UNICODE( "Versions" ), SFX_STREAM_READONLY | STREAM_NOCREATE);
//STRIP001 /*?*/ 			if ( xOldVersions.Is() && xOldVersions->GetError() == SVSTREAM_OK )
//STRIP001 /*?*/ 			{
//STRIP001 /*?*/ 				const SfxVersionTableDtor *pList = rMedium.GetVersionList();
//STRIP001 /*?*/ 				sal_uInt32 n=0;
//STRIP001 /*?*/ 				SfxVersionInfo* pInfo = pList->GetObject(n++);
//STRIP001 /*?*/ 				while( pInfo )
//STRIP001 /*?*/ 				{
//STRIP001 /*?*/ 					const String& rName = pInfo->aName;
//STRIP001 /*?*/ 					if ( xOldVersions->IsContained( rName ) )
//STRIP001 /*?*/ 						xOldVersions->CopyTo( rName, xVersion, rName );
//STRIP001 /*?*/ 					pInfo = pList->GetObject(n++);
//STRIP001 /*?*/ 				}
//STRIP001 /*?*/ 
//STRIP001 /*?*/                 xOldVersions.Clear();
//STRIP001 /*?*/ 			}
//STRIP001 /*?*/ 
//STRIP001 /*?*/             // add new version information into the versionlist and save the versionlist
//STRIP001 /*?*/             // the version list must have been transferred from the "old" medium before
//STRIP001 /*?*/ 			rMedium.AddVersion_Impl( aInfo );
//STRIP001 /*?*/ 			rMedium.SaveVersionList_Impl( bUseXML );
//STRIP001 /*?*/ 
//STRIP001 /*?*/             ::utl::TempFile aTmpFile;
//STRIP001 /*?*/             aTmpFile.EnableKillingFile( sal_True );
//STRIP001 /*?*/             SvStorageRef xTmp = new SvStorage( ( SOFFICE_FILEFORMAT_60 <= pFilter->GetVersion() ), aTmpFile.GetURL(),
//STRIP001 /*?*/ 													SFX_STREAM_READWRITE, STORAGE_TRANSACTED );
//STRIP001 /*?*/ 
//STRIP001 /*?*/ 
//STRIP001 /*?*/             // save the new version to the storage, perhaps also with password if the root storage is password protected
//STRIP001 /*?*/ 			if ( aPasswd.Len() )
//STRIP001 /*?*/ 				xTmp->SetKey( S2BS( aPasswd ) ); //!!! (pb) needs new implementation
//STRIP001 /*?*/ 
//STRIP001 /*?*/             // save again, now as a version, use the target medium as a transport medium
//STRIP001 /*?*/             // this should be changed in the future, using a different medium seems to be better
//STRIP001 /*?*/             rMedium.SetStorage_Impl( xTmp );
//STRIP001 /*?*/             bOk = SaveAsOwnFormat( rMedium );
//STRIP001 /*?*/ 			xTmp->Commit();
//STRIP001 /*?*/ 
//STRIP001 /*?*/             // reconnect medium to "old" storage
//STRIP001 /*?*/ 			rMedium.SetStorage_Impl( aMedRef );
//STRIP001 /*?*/ 
//STRIP001 /*?*/             // close storage, it must be reopened as stream
//STRIP001 /*?*/             xTmp.Clear();
//STRIP001 /*?*/ 
//STRIP001 /*?*/             // compress stream and store it into the root storage
//STRIP001 /*?*/ 			SvStorageStreamRef xStrm = xVersion->OpenStream( aInfo.aName );
//STRIP001 /*?*/ 			if ( SOFFICE_FILEFORMAT_60 <= pFilter->GetVersion() )
//STRIP001 /*?*/ 			{
//STRIP001 /*?*/ 				*xStrm << *aTmpFile.GetStream( STREAM_READ );
//STRIP001 /*?*/ 			}
//STRIP001 /*?*/ 			else
//STRIP001 /*?*/ 			{
//STRIP001 /*?*/ 				ZCodec aCodec;
//STRIP001 /*?*/ 				aCodec.BeginCompression( ZCODEC_BEST_COMPRESSION );
//STRIP001 /*?*/ 				aCodec.Compress( *aTmpFile.GetStream( STREAM_READ ), *xStrm );
//STRIP001 /*?*/ 				aCodec.EndCompression();
//STRIP001 /*?*/ 			}
//STRIP001 /*?*/ 
//STRIP001 /*?*/             // commit the version storage
//STRIP001 /*?*/ 			xVersion->Commit();
/*N*/ 		}
/*N*/ 		else if ( pImp->bIsSaving )
/*N*/ 		{DBG_BF_ASSERT(0, "STRIP"); //STRIP001 
//STRIP001 /*?*/             // it's a "Save", not a "SaveAs"
//STRIP001 /*?*/             // so all preliminary saved versions must be copied from the object storage to the the target storage
//STRIP001 /*?*/ 			sal_Bool bUseXML = SOFFICE_FILEFORMAT_60 <= pFilter->GetVersion();
//STRIP001 /*?*/ 
//STRIP001 /*?*/             // save the version list
//STRIP001 /*?*/             // the version list must have been transferred from the "old" medium before
//STRIP001 /*?*/             rMedium.SaveVersionList_Impl( bUseXML );
//STRIP001 /*?*/ 			const SfxVersionTableDtor *pList = rMedium.GetVersionList();
//STRIP001 /*?*/ 			if ( pList && pList->Count() )
//STRIP001 /*?*/ 			{
//STRIP001 /*?*/                 // copy the version streams
//STRIP001 /*?*/                 SvStorageRef xVersion = bUseXML ?
//STRIP001 /*?*/                     aMedRef->OpenUCBStorage( DEFINE_CONST_UNICODE( "Versions" ) ) :
//STRIP001 /*?*/                     aMedRef->OpenStorage( DEFINE_CONST_UNICODE( "Versions" ) );
//STRIP001 /*?*/                 SvStorageRef xOldVersions = GetStorage()->OpenStorage( DEFINE_CONST_UNICODE( "Versions" ), SFX_STREAM_READONLY | STREAM_NOCREATE );
//STRIP001 /*?*/ 				if ( xOldVersions.Is() && xOldVersions->GetError() == SVSTREAM_OK )
//STRIP001 /*?*/ 				{
//STRIP001 /*?*/ 					sal_uInt32 n=0;
//STRIP001 /*?*/ 					SfxVersionInfo* pInfo = pList->GetObject(n++);
//STRIP001 /*?*/ 					while( pInfo )
//STRIP001 /*?*/ 					{
//STRIP001 /*?*/ 						const String& rName = pInfo->aName;
//STRIP001 /*?*/ 						if ( xOldVersions->IsContained( rName ) )
//STRIP001 /*?*/ 							xOldVersions->CopyTo( rName, xVersion, rName );
//STRIP001 /*?*/ 						pInfo = pList->GetObject(n++);
//STRIP001 /*?*/ 					}
//STRIP001 /*?*/ 
//STRIP001 /*?*/                     xOldVersions.Clear();
//STRIP001 /*?*/ 				}
//STRIP001 /*?*/ 
//STRIP001 /*?*/                 // commit the version storage
//STRIP001 /*?*/                 xVersion->Commit();
//STRIP001 /*?*/ 			}
/*N*/ 		}
/*N*/ 	}
//STRIP003/*N*/ 	else
//STRIP003/*N*/ 	{
//STRIP003/*?*/         // it's a "SaveAs" in an alien format
//STRIP003/*?*/ 		if ( rMedium.GetFilter() && ( rMedium.GetFilter()->GetFilterFlags() & SFX_FILTER_STARONEFILTER ) )
//STRIP003/*?*/             bOk = ExportTo( rMedium );
//STRIP003/*?*/ 		else
//STRIP003/*?*/             bOk = ConvertTo( rMedium );
//STRIP003/*?*/ 
//STRIP003/*?*/         // after saving the document, the temporary object storage must be updated
//STRIP003/*?*/         // if the old object storage was not a temporary one, it will be updated also, because it will be used
//STRIP003/*?*/         // as a source for copying the objects into the new temporary storage that will be created below
//STRIP003/*?*/         // updating means: all child objects must be stored into it
//STRIP003/*?*/         // ( same as on loading, where these objects are copied to the temporary storage )
//STRIP003/*?*/         // but don't commit these changes, because in the case when the old object storage is not a temporary one,
//STRIP003/*?*/         // all changes will be written into the original file !
//STRIP003/*?*/         if( bOk )
//STRIP003/*?*/             bOk = SaveChilds() && SaveCompletedChilds( NULL );
//STRIP003/*N*/ 	}

    // SetModified must be enabled when SaveCompleted is called, otherwise the modified flag of child objects will not be cleared
/*N*/     EnableSetModified( sal_True );
/*N*/ 
/*N*/     sal_Bool bCopyTo = sal_False;
/*N*/     SfxItemSet *pMedSet = rMedium.GetItemSet();
/*N*/     if( pMedSet )
/*N*/     {
/*N*/         SFX_ITEMSET_ARG( pMedSet, pSaveToItem, SfxBoolItem, SID_SAVETO, sal_False );
/*N*/         bCopyTo =   GetCreateMode() == SFX_CREATE_MODE_EMBEDDED ||
/*N*/                     pSaveToItem && pSaveToItem->GetValue();
/*N*/     }
/*N*/ 
/*N*/     if( bOk )
/*N*/ 	{
/*N*/         // remember new object storage, if it is a temporary one, because we will need it for a "SaveCompleted" later
/*N*/         SvStorageRef xNewTempRef;
/*N*/         if ( bOk && bPrepareForDirectAccess )
/*N*/         {
/*N*/             // if the target medium is an alien format and the "old" medium was an own format, the object storage
/*N*/             // must be exchanged, because now we need a new temporary storage as object storage
/*N*/             BOOL bNeedsStorage = !bCopyTo && IsOwnStorageFormat_Impl(*pMedium) && !IsOwnStorageFormat_Impl(rMedium);
/*N*/             if ( bNeedsStorage )
/*N*/             {
/*?*/                 if( !pMedium->GetName().Len() )
/*?*/                     // if the old object storage was a temporary one too, we can continue with it
/*?*/                     xNewTempRef = GetStorage();
/*?*/                 else
/*?*/                 {
/*?*/                     // copy storage of old medium to new temporary storage and take this over
/*?*/                     if( ConnectTmpStorage_Impl( pMedium->GetStorage() ) )
/*?*/                         xNewTempRef = GetStorage();
/*?*/                     else
/*?*/                         bOk = sal_False;
/*?*/                 }
/*N*/             }
/*N*/ 
/*N*/             // When the new medium ( rMedium ) has the same name as the current one,
/*N*/             // we need to call DoHandsOff() so Commit() can overwrite the old version
/*N*/             if ( bOk && pMedium && ( rMedium.GetName().EqualsIgnoreCaseAscii( pMedium->GetName() ) )
/*N*/ 			  && rMedium.GetName().CompareIgnoreCaseToAscii( "private:stream", 14 ) != COMPARE_EQUAL )
/*?*/                 DoHandsOff();
/*N*/         }
/*N*/ 
/*N*/         if ( bOk && pMedium && ( rMedium.GetName() == pMedium->GetName() ) )
/*N*/         {
/*N*/             // before we overwrite the original file, we will make a backup if there is a demand for that
/*N*/             const sal_Bool bDoBackup = SvtSaveOptions().IsBackup();
/*N*/             if ( bDoBackup )
/*N*/ 			{{DBG_BF_ASSERT(0, "STRIP");}//STRIP001 
//STRIP001 /*N*/                 pMedium->DoBackup_Impl();
//STRIP001 /*N*/ 				bOk = ( pMedium->GetError() == ERRCODE_NONE );
//STRIP001 /*N*/ 				if ( !bOk )
//STRIP001 /*N*/ 				{
//STRIP001 /*N*/ 					SetError( pMedium->GetErrorCode() );
//STRIP001 /*N*/ 					pMedium->ResetError();
//STRIP001 /*N*/ 				}
/*N*/ 			}
/*N*/         }
/*N*/ 
/*N*/         if ( bOk )
/*N*/         {
/*N*/             // transfer data to its destinated location
/*N*/             EnableSetModified( sal_False );
/*N*/             RegisterTransfer( rMedium );
/*N*/             bOk = rMedium.Commit();
/*N*/             EnableSetModified( sal_True );
/*N*/ 
/*N*/ 			if ( bOk )
/*N*/ 			{
/*N*/             	// watch: if the document was successfully saved into an own format, no "SaveCompleted" was called,
/*N*/             	// this must be done by the caller ( because they want to do different calls )
/*N*/ 				if( xNewTempRef.Is() && xNewTempRef != GetStorage() )
/*N*/                 	// if the new object storage is a temporary one, because the target format is an alien format
/*?*/                 	SaveCompleted( xNewTempRef );
/*N*/ 			}
/*N*/ 			else
/*N*/ 			{
/*?*/ 				// if the storing process fails on medium commit step it means that
/*?*/ 				// the new medium should contain successfully written temporary representation
/*?*/ 				// of the document, so the docshell can just switch to new medium.
/*?*/ 				// it is reasonable in case an open document suddenly became unavailable.
/*?*/ 
/*?*/ 				OUString aOrigName = pMedium ? OUString(pMedium->GetName()) : OUString();
/*?*/ 				if ( aOrigName.getLength() && aOrigName.compareToAscii( "private:", 8 ) != COMPARE_EQUAL
/*?*/ 				  	&& !::utl::UCBContentHelper::Exists( aOrigName ) )
/*?*/ 				{DBG_BF_ASSERT(0, "STRIP");//STRIP001 
//STRIP001 /*?*/         			if ( !IsHandsOff() )
//STRIP001 /*?*/             			DoHandsOff();
//STRIP001 /*?*/ 
//STRIP001 /*?*/ 					rMedium.MoveTempTo_Impl( pMedium );
/*?*/ 				}
/*N*/ 			}
/*N*/         }
/*N*/ 	}
/*N*/ 
/*N*/     // unlock user interface
/*N*/     Lock_Impl( this, sal_False );
/*N*/     pImp->bForbidReload = bOldStat;
/*N*/ 
/*N*/     if ( bOk )
/*N*/     {
/*N*/         DBG_ASSERT( pFilter, "No filter after successful save?!" );
/*N*/         if( pFilter )
/*N*/             if( !bCopyTo && pFilter->IsAlienFormat() )
/*N*/                 // set flag, that the user will be warned for possible data loss on closing this document
/*N*/                 pImp->bDidDangerousSave=sal_True;
/*N*/             else
/*?*/                 pImp->bDidDangerousSave=sal_False;
/*N*/ 
/*N*/ 		if ( pImp->bIsSaving )
/*?*/ 			SetEAs_Impl(rMedium);
/*N*/ 
/*N*/         try
/*N*/         {
/*?*/             ::ucb::Content aContent( rMedium.GetName(), ::com::sun::star::uno::Reference < XCommandEnvironment >() );
/*?*/             ::com::sun::star::uno::Reference < XPropertySetInfo > xProps = aContent.getProperties();
/*?*/             if ( xProps.is() )
/*?*/             {
/*?*/                 ::rtl::OUString aAuthor( RTL_CONSTASCII_USTRINGPARAM("Author") );
/*?*/                 ::rtl::OUString aKeywords( RTL_CONSTASCII_USTRINGPARAM("Keywords") );
/*?*/                 ::rtl::OUString aSubject( RTL_CONSTASCII_USTRINGPARAM("Subject") );
/*?*/                 Any aAny;
/*?*/                 if ( xProps->hasPropertyByName( aAuthor ) )
/*?*/                 {
/*?*/                     aAny <<= ::rtl::OUString( GetDocInfo().GetCreated().GetName() );
/*?*/                     aContent.setPropertyValue( aAuthor, aAny );
/*?*/                 }
/*?*/                 if ( xProps->hasPropertyByName( aKeywords ) )
/*?*/                 {
/*?*/                     aAny <<= ::rtl::OUString( GetDocInfo().GetKeywords() );
/*?*/                     aContent.setPropertyValue( aKeywords, aAny );
/*?*/                 }
/*?*/                 if ( xProps->hasPropertyByName( aSubject ) )
/*?*/                 {
/*?*/                     aAny <<= ::rtl::OUString( GetDocInfo().GetTheme() );
/*?*/                     aContent.setPropertyValue( aSubject, aAny );
/*?*/                 }
/*?*/             }
/*N*/         }
/*N*/         catch( Exception& )
/*N*/         {
/*N*/         }
/*N*/     }
/*N*/ 
/*N*/ 	return bOk;
/*N*/ }

//------------------------------------------------------------------------

/*?*/ sal_Bool SfxObjectShell::ConnectTmpStorage_Impl( SvStorage* pStg)

/*   [Beschreibung]

     Arbeitet die Applikation auf einem temporaeren Storage,
     so darf der temporaere Storage nicht aus dem SaveCompleted
     genommen werden. Daher wird in diesem Fall schon hier an
     den neuen Storage connected. SaveCompleted tut dann nichts.

     */

/*?*/ {
/*?*/ 	// wenn es kein temp. Storage ist, einen anlegen
/*?*/     SvStorageRef aTmpMed = new SvStorage( (pStg->GetVersion() >= SOFFICE_FILEFORMAT_60), String() );
/*?*/ 
/*?*/ 	// nach HandsOff muss der alte Storage wieder eingesetzt werden
/*?*/ 	if ( !pStg->CopyTo(aTmpMed) )
/*?*/ 	{
/*?*/ 		SetError(aTmpMed->GetErrorCode());
/*?*/ 		aTmpMed.Clear();
/*?*/ 		return sal_False;
/*?*/ 	}
/*?*/ 
/*?*/ 	SetError(GetMedium()->GetErrorCode());
/*?*/ 	SaveCompleted(aTmpMed); // neuer temp. Storage; gibt alten frei
/*?*/ 	return sal_True;
/*?*/ }


//-------------------------------------------------------------------------

/*N*/ sal_Bool SfxObjectShell::DoSaveAs( SvStorage * pNewStor )
/*N*/ {
/*N*/ // DoSaveAs wird nur noch ueber OLE aufgerufen
/*N*/ 	sal_Bool bOk;
/*N*/ 	{
/*N*/ 		SfxForceLinkTimer_Impl aFLT( this );
/*N*/ 		ModifyBlocker_Impl aBlock( this );
/*N*/ 		//Abwehr gegen feindlich gesinnte Applikationen.
/*N*/ 		if ( !pNewStor->GetFormat() )
/*N*/ 			SetupStorage( pNewStor );
/*N*/ 
/*N*/ 		pImp->bIsSaving = sal_False;
/*N*/ 		SfxMedium* pNewMed = new SfxMedium( pNewStor );
/*N*/ 		const String aOldURL( so3::StaticBaseUrl::GetBaseURL() );
/*N*/ 
/*N*/ 		bOk = SaveAsOwnFormat( *pNewMed );
/*N*/ 		so3::StaticBaseUrl::SetBaseURL( aOldURL );
/*N*/ 		delete pNewMed;
/*N*/ 	}
/*N*/ 	return bOk;
/*N*/ }

//-------------------------------------------------------------------------

/*?*/ sal_Bool SfxObjectShell::DoSaveAs( SfxMedium &rMedium )
/*?*/ {
/*?*/ 	// hier kommen nur Root-Storages rein, die via Temp-File gespeichert werden
/*?*/     rMedium.CreateTempFileNoCopy();
/*?*/     SetError(rMedium.GetErrorCode());
/*?*/     if ( GetError() )
/*?*/         return sal_False;
/*?*/ 
/*?*/ 	const String aOldURL( so3::StaticBaseUrl::GetBaseURL() );
/*?*/ 	if( GetCreateMode() != SFX_CREATE_MODE_EMBEDDED )
/*?*/ 		if ( ShallSetBaseURL_Impl( rMedium ) )
/*?*/ 			so3::StaticBaseUrl::SetBaseURL( rMedium.GetBaseURL() );
/*?*/ 		else
/*?*/ 			so3::StaticBaseUrl::SetBaseURL( String() );
/*?*/ 
/*?*/     sal_Bool bRet = SaveTo_Impl( rMedium, NULL, sal_False );
/*?*/ 	so3::StaticBaseUrl::SetBaseURL( aOldURL );
/*?*/ 	if( bRet )
/*?*/ 		DoHandsOff();
/*?*/ 	else
/*?*/ 		SetError(rMedium.GetErrorCode());
/*?*/ 	return bRet;
/*?*/ }

//-------------------------------------------------------------------------

/*N*/ sal_Bool SfxObjectShell::DoSaveCompleted( SfxMedium * pNewMed )
/*N*/ {
    sal_Bool bOk = sal_True;
    sal_Bool bMedChanged = pNewMed && pNewMed!=pMedium;
/*	sal_Bool bCreatedTempStor = pNewMed && pMedium &&
        IsOwnStorageFormat_Impl(*pMedium) &&
        !IsOwnStorageFormat_Impl(*pNewMed) &&
        pMedium->GetName().Len();
*/
/*N*/     DBG_ASSERT( !pNewMed || pNewMed->GetError() == ERRCODE_NONE, "DoSaveCompleted: Medium has error!" );
/*N*/ 	if ( bMedChanged )
/*N*/ 	{
/*N*/ 		delete pMedium;
/*N*/ 		pMedium = pNewMed;
/*N*/ 		//MI? DELETEZ(pImp->pDocInfo);
/*N*/ 	}
/*N*/ 
/*N*/ 	const SfxFilter *pFilter = pMedium ? pMedium->GetFilter() : 0;
/*N*/ 	if ( pNewMed )
/*N*/ 	{
/*N*/ 		if( bMedChanged )
/*N*/ 		{
/*N*/ 			if( pNewMed->GetName().Len() )
/*N*/ 				bHasName = sal_True;
/*N*/ 			String aBase = GetBaseURL();
/*N*/ 			if( Current() == this && aBase.Len() )
/*N*/ 				so3::StaticBaseUrl::SetBaseURL( aBase );
/*N*/ 			Broadcast( SfxSimpleHint(SFX_HINT_NAMECHANGED) );
/*N*/ 		}
/*N*/ 
/*N*/ 		SvStorage *pStorage=NULL;
/*N*/ 		if ( !pFilter||sal_True  ) //STRIP007 if ( !pFilter || pFilter->IsOwnFormat() )
/*N*/ 		{
/*N*/ 			pStorage = pMedium->GetStorage();
/*N*/ 			bOk = SaveCompleted( pStorage );
/*N*/ 		}
/*N*/ 		else
/*N*/ 		{
/*?*/ 			pStorage = GetStorage();
/*?*/ 			if( pFilter->UsesStorage() )
/*?*/ 				pMedium->GetStorage();
/*?*/ 			else if( pMedium->GetOpenMode() & STREAM_WRITE )
/*?*/ 				pMedium->GetInStream();
/*N*/ 		}
/*N*/ 
/*N*/ 		// Set storage in document library containers
/*N*/ 		SfxDialogLibraryContainer* pDialogCont = pImp->pDialogLibContainer;
/*N*/ 		if( pDialogCont )
/*N*/ 			pDialogCont->setStorage( pStorage );
/*N*/ 
/*N*/ 		SfxScriptLibraryContainer* pBasicCont = pImp->pBasicLibContainer;
/*N*/ 		if( pBasicCont )
/*N*/ 			pBasicCont->setStorage( pStorage );
/*N*/ 	}
/*N*/ 	else
/*N*/ 	{
/*N*/ 		if( pMedium )
/*N*/ 		{
/*N*/ 			const SfxFilter* pFilter = pMedium->GetFilter();
/*N*/ 			if( pFilter && !pFilter->IsOwnFormat() &&
/*N*/ 				(pMedium->GetOpenMode() & STREAM_WRITE ))
/*N*/ 				 pMedium->ReOpen();
/*N*/ 			else
/*N*/ 				SaveCompleted( 0 );
/*N*/ 		}
/*N*/ 		// entweder Save oder ConvertTo
/*N*/ 		else
/*?*/ 			bOk = SaveCompleted( NULL );
/*N*/ 	}
/*N*/ 
/*N*/ 	if ( bOk && pNewMed )
/*N*/ 	{
/*N*/ 		if( bMedChanged )
/*N*/ 		{
/*N*/ 			// Titel neu setzen
/*N*/ 			if ( pNewMed->GetName().Len() &&
/*N*/ 				 SFX_CREATE_MODE_EMBEDDED != eCreateMode )
/*N*/ 				InvalidateName();
/*N*/ 			SetModified(sal_False); // nur bei gesetztem Medium zur"ucksetzen
/*N*/             Broadcast( SfxSimpleHint(SFX_HINT_MODECHANGED) );
/*N*/ 		}
/*N*/ 	}
/*N*/ 
/*N*/ 	return bOk;
/*N*/ }

//-------------------------------------------------------------------------

/*N*/ sal_Bool SfxObjectShell::DoSaveCompleted( SvStorage * pNewStor )
/*N*/ {
/*N*/ 	return DoSaveCompleted(pNewStor? new SfxMedium( pNewStor ): 0);
/*N*/ }

//-------------------------------------------------------------------------

/*?*/ sal_Bool SfxObjectShell::ConvertFrom
/*?*/ (
/*?*/ 	SfxMedium&  rMedium     /*  <SfxMedium>, welches die Quell-Datei beschreibt
                                (z.B. Dateiname, <SfxFilter>, Open-Modi etc.) */
/*?*/ )

/*  [Beschreibung]

    Diese Methode wird zum Laden von Dokumenten "uber alle Filter gerufen,
    die nicht SFX_FILTER_OWN sind oder f"ur die kein Clipboard-Format
    registriert wurde (also kein Storage-Format benutzen). Mit anderen Worten:
    mit dieser Methode wird importiert.

    Das hier zu "offende File sollte "uber 'rMedium' ge"offnet werden,
    um die richtigen Open-Modi zu gew"ahrleisten. Insbesondere wenn das
    Format beibehalten wird (nur m"oglich bei SFX_FILTER_SIMULATE oder
    SFX_FILTER_ONW) mu\s die Datei STREAM_SHARE_DENYWRITE ge"offnet werden.


    [R"uckgabewert]

    sal_Bool                sal_True
                        Das Dokument konnte geladen werden.

                        sal_False
                        Das Dokument konnte nicht geladen werden, ein
                        Fehlercode ist mit <SvMedium::GetError()const> zu
                        erhalten.


    [Beispiel]

    sal_Bool DocSh::ConvertFrom( SfxMedium &rMedium )
    {
        SvStreamRef xStream = rMedium.GetInStream();
        if( xStream.is() )
        {
            xStream->SetBufferSize(4096);
            *xStream >> ...;

            // NICHT 'rMedium.CloseInStream()' rufen! File gelockt halten!
            return SVSTREAM_OK == rMedium.GetError();
        }

        return sal_False;
    }


    [Querverweise]

    <SfxObjectShell::ConvertTo(SfxMedium&)>
    <SFX_FILTER_REGISTRATION>
*/
/*?*/ {
/*?*/ 	return sal_False;
/*?*/ }

/*?*/ sal_Bool SfxObjectShell::ImportFrom( SfxMedium& rMedium )
/*?*/ {DBG_BF_ASSERT(0, "STRIP"); //STRIP001 
//STRIP001 /*?*/     ::rtl::OUString aTypeName( rMedium.GetFilter()->GetTypeName() );
//STRIP001 /*?*/     ::rtl::OUString aFilterName( rMedium.GetFilter()->GetFilterName() );
//STRIP001 /*?*/ 
//STRIP001 /*?*/     ::com::sun::star::uno::Reference< ::com::sun::star::lang::XMultiServiceFactory >  xMan = ::legacy_binfilters::getLegacyProcessServiceFactory();
//STRIP001 /*?*/     ::com::sun::star::uno::Reference < ::com::sun::star::lang::XMultiServiceFactory > xFilterFact (
//STRIP001 /*?*/                 xMan->createInstance( DEFINE_CONST_UNICODE( "com.sun.star.document.FilterFactory" ) ), ::com::sun::star::uno::UNO_QUERY );
//STRIP001 /*?*/ 
//STRIP001 /*?*/     ::com::sun::star::uno::Sequence < ::com::sun::star::beans::PropertyValue > aProps;
//STRIP001 /*?*/     ::com::sun::star::uno::Reference < ::com::sun::star::container::XNameAccess > xFilters ( xFilterFact, ::com::sun::star::uno::UNO_QUERY );
//STRIP001 /*?*/     if ( xFilters->hasByName( aFilterName ) )
//STRIP001 /*?*/         xFilters->getByName( aFilterName ) >>= aProps;
//STRIP001 /*?*/ 
//STRIP001 /*?*/     ::rtl::OUString aFilterImplName;
//STRIP001 /*?*/     sal_Int32 nFilterProps = aProps.getLength();
//STRIP001 /*?*/     for ( sal_Int32 nFilterProp = 0; nFilterProp<nFilterProps; nFilterProp++ )
//STRIP001 /*?*/     {
//STRIP001 /*?*/         const ::com::sun::star::beans::PropertyValue& rFilterProp = aProps[nFilterProp];
//STRIP001 /*?*/         if ( rFilterProp.Name.compareToAscii("FilterService") == COMPARE_EQUAL )
//STRIP001 /*?*/         {
//STRIP001 /*?*/             rFilterProp.Value >>= aFilterImplName;
//STRIP001 /*?*/             break;
//STRIP001 /*?*/         }
//STRIP001 /*?*/     }
//STRIP001 /*?*/ 
//STRIP001 /*?*/     ::com::sun::star::uno::Sequence < ::com::sun::star::uno::Any > aArgs(1);
//STRIP001 /*?*/     ::com::sun::star::beans::PropertyValue aFilterProp;
//STRIP001 /*?*/     aFilterProp.Name = DEFINE_CONST_UNICODE("FilterName");
//STRIP001 /*?*/     aFilterProp.Value <<= aFilterName;
//STRIP001 /*?*/     aArgs[0] <<= aFilterProp;
//STRIP001 /*?*/     ::com::sun::star::uno::Reference< ::com::sun::star::document::XFilter > xLoader;
//STRIP001 /*?*/     if ( aFilterImplName.getLength() )
//STRIP001 /*?*/         xLoader = ::com::sun::star::uno::Reference< ::com::sun::star::document::XFilter >
//STRIP001 /*?*/             ( xFilterFact->createInstanceWithArguments( aTypeName, aArgs ), ::com::sun::star::uno::UNO_QUERY );
//STRIP001 /*?*/ 	if ( xLoader.is() )
//STRIP001 /*?*/ 	{
//STRIP001 /*?*/ 		::com::sun::star::uno::Reference< ::com::sun::star::lang::XComponent >  xComp( GetModel(), ::com::sun::star::uno::UNO_QUERY );
//STRIP001 /*?*/         ::com::sun::star::uno::Reference< ::com::sun::star::document::XImporter > xImporter( xLoader, ::com::sun::star::uno::UNO_QUERY );
//STRIP001 /*?*/         xImporter->setTargetDocument( xComp );
//STRIP001 /*?*/ 
//STRIP001 /*?*/         ::com::sun::star::uno::Sequence < ::com::sun::star::beans::PropertyValue > lDescriptor;
//STRIP001 /*?*/         rMedium.GetItemSet()->Put( SfxStringItem( SID_FILE_NAME, rMedium.GetName() ) );
//STRIP001 /*?*/         TransformItems( SID_OPENDOC, *rMedium.GetItemSet(), lDescriptor );
//STRIP001 /*?*/ 
//STRIP001 /*?*/ 		::com::sun::star::uno::Sequence < ::com::sun::star::beans::PropertyValue > aArgs ( lDescriptor.getLength() + 1);
//STRIP001 /*?*/ 		::com::sun::star::beans::PropertyValue * pNewValue = aArgs.getArray();
//STRIP001 /*?*/ 		const ::com::sun::star::beans::PropertyValue * pOldValue = lDescriptor.getConstArray();
//STRIP001 /*?*/ 		const OUString sInputStream ( RTL_CONSTASCII_USTRINGPARAM ( "InputStream" ) );
//STRIP001 /*?*/ 
//STRIP001 /*?*/ 		sal_Bool bHasInputStream = sal_False;
//STRIP001 /*?*/ 		for ( sal_Int32 i = 0, nEnd = lDescriptor.getLength(); i < nEnd; i++ )
//STRIP001 /*?*/ 		{
//STRIP001 /*?*/ 			pNewValue[i] = pOldValue[i];
//STRIP001 /*?*/ 			if ( pOldValue [i].Name == sInputStream )
//STRIP001 /*?*/ 				bHasInputStream = sal_True;
//STRIP001 /*?*/ 		}
//STRIP001 /*?*/ 		if ( !bHasInputStream )
//STRIP001 /*?*/ 		{
//STRIP001 /*?*/ 			pNewValue[i].Name = sInputStream;
//STRIP001 /*?*/ 			pNewValue[i].Value <<= ::com::sun::star::uno::Reference < ::com::sun::star::io::XInputStream > ( new utl::OSeekableInputStreamWrapper ( *rMedium.GetInStream() ) );
//STRIP001 /*?*/ 		}
//STRIP001 /*?*/ 		else
//STRIP001 /*?*/ 			aArgs.realloc ( i-1 );
//STRIP001 /*?*/ 
//STRIP001 /*?*/         return xLoader->filter( aArgs );
//STRIP001 /*?*/ 	}
//STRIP001 /*?*/ 
/*?*/ 	return sal_False;
/*?*/ }

/*?*/ sal_Bool SfxObjectShell::ExportTo( SfxMedium& rMedium )
/*?*/ { // #dochnoetig# DBG_BF_ASSERT(0, "STRIP"); //STRIP001 
/*N*/     ::rtl::OUString aTypeName( rMedium.GetFilter()->GetTypeName() );
/*N*/     ::rtl::OUString aFilterName( rMedium.GetFilter()->GetFilterName() );
/*N*/     ::com::sun::star::uno::Reference< ::com::sun::star::document::XExporter > xExporter;
/*N*/ 
/*N*/ 	{
/*N*/         ::com::sun::star::uno::Reference< ::com::sun::star::lang::XMultiServiceFactory >  xMan = ::legacy_binfilters::getLegacyProcessServiceFactory();
/*N*/         ::com::sun::star::uno::Reference < ::com::sun::star::lang::XMultiServiceFactory > xFilterFact (
/*N*/                 xMan->createInstance( DEFINE_CONST_UNICODE( "com.sun.star.document.FilterFactory" ) ), ::com::sun::star::uno::UNO_QUERY );
/*N*/ 
/*N*/         ::com::sun::star::uno::Sequence < ::com::sun::star::beans::PropertyValue > aProps;
/*N*/         ::com::sun::star::uno::Reference < ::com::sun::star::container::XNameAccess > xFilters ( xFilterFact, ::com::sun::star::uno::UNO_QUERY );
/*N*/         if ( xFilters->hasByName( aFilterName ) )
/*N*/             xFilters->getByName( aFilterName ) >>= aProps;
/*N*/ 
/*N*/         ::rtl::OUString aFilterImplName;
/*N*/         sal_Int32 nFilterProps = aProps.getLength();
/*N*/         for ( sal_Int32 nFilterProp = 0; nFilterProp<nFilterProps; nFilterProp++ )
/*N*/         {
/*N*/             const ::com::sun::star::beans::PropertyValue& rFilterProp = aProps[nFilterProp];
/*N*/             if ( rFilterProp.Name.compareToAscii("FilterService") == COMPARE_EQUAL )
/*N*/             {
/*N*/                 rFilterProp.Value >>= aFilterImplName;
/*N*/                 break;
/*N*/             }
/*N*/         }
/*N*/ 
/*N*/         ::com::sun::star::uno::Sequence < ::com::sun::star::uno::Any > aArgs(1);
/*N*/         aArgs[0] <<= aFilterName;
/*N*/         if ( aFilterImplName.getLength() )
/*N*/             xExporter = ::com::sun::star::uno::Reference< ::com::sun::star::document::XExporter >
/*N*/                 ( xFilterFact->createInstanceWithArguments( aTypeName, aArgs ), ::com::sun::star::uno::UNO_QUERY );
/*N*/ 	}
/*N*/ 
/*N*/     if ( xExporter.is() )
/*N*/ 	{
/*N*/ 		::com::sun::star::uno::Reference< ::com::sun::star::lang::XComponent >  xComp( GetModel(), ::com::sun::star::uno::UNO_QUERY );
/*N*/         ::com::sun::star::uno::Reference< ::com::sun::star::document::XFilter > xFilter( xExporter, ::com::sun::star::uno::UNO_QUERY );
/*N*/         xExporter->setSourceDocument( xComp );
/*N*/ 
/*N*/         ::com::sun::star::uno::Sequence < ::com::sun::star::beans::PropertyValue > aOldArgs;
/*N*/         SfxItemSet* pItems = rMedium.GetItemSet();
/*N*/         TransformItems( SID_SAVEASDOC, *pItems, aOldArgs );
/*N*/ 
/*N*/ 		const ::com::sun::star::beans::PropertyValue * pOldValue = aOldArgs.getConstArray();
/*N*/ 		::com::sun::star::uno::Sequence < ::com::sun::star::beans::PropertyValue > aArgs ( aOldArgs.getLength() + 1 );
/*N*/ 		::com::sun::star::beans::PropertyValue * pNewValue = aArgs.getArray();
/*N*/ 
/*N*/ 		// put in the REAL file name, and copy all PropertyValues
/*N*/         const OUString sOutputStream ( RTL_CONSTASCII_USTRINGPARAM ( "OutputStream" ) );
/*N*/         BOOL bHasStream = FALSE;
/*N*/ 		sal_Int32 i, nEnd; for ( i = 0, nEnd = aOldArgs.getLength(); i < nEnd; i++ )
/*N*/ 		{
/*N*/ 			pNewValue[i] = pOldValue[i];
/*N*/             if ( pOldValue[i].Name.equalsAsciiL ( RTL_CONSTASCII_STRINGPARAM ( "FileName" ) ) )
/*N*/ 				pNewValue[i].Value <<= OUString ( rMedium.GetName() );
/*N*/             if ( pOldValue[i].Name == sOutputStream )
/*N*/                 bHasStream = sal_True;
/*N*/ 		}
/*N*/ 
/*N*/         if ( !bHasStream )
/*N*/ 		{
/*N*/             pNewValue[i].Name = sOutputStream;
/*N*/             pNewValue[i].Value <<= ::com::sun::star::uno::Reference < ::com::sun::star::io::XOutputStream > ( new ::utl::OOutputStreamWrapper ( *rMedium.GetOutStream() ) );
/*N*/ 		}
/*N*/ 		else
/*N*/ 			aArgs.realloc ( i-1 );
/*N*/ 
/*N*/         return xFilter->filter( aArgs );
/*N*/ 	}
/*N*/ 
/*?*/ 	return sal_False;
/*?*/ }

//-------------------------------------------------------------------------

/*?*/ sal_Bool SfxObjectShell::ConvertTo
/*?*/ (
/*?*/ 	SfxMedium&  rMedium     /*  <SfxMedium>, welches die Ziel-Datei beschreibt
                                (z.B. Dateiname, <SfxFilter>, Open-Modi etc.) */
/*?*/ )

/*  [Beschreibung]

    Diese Methode wird zum Speichern von Dokumenten "uber alle Filter gerufen,
    die nicht SFX_FILTER_OWN sind oder f"ur die kein Clipboard-Format
    registriert wurde (also kein Storage-Format benutzen). Mit anderen Worten:
    mit dieser Methode wird exportiert.

    Das hier zu "offende File sollte "uber 'rMedium' ge"offnet werden,
    um die richtigen Open-Modi zu gew"ahrleisten. Insbesondere wenn das
    Format beibehalten wird (nur m"oglich bei SFX_FILTER_SIMULATE oder
    SFX_FILTER_ONW) mu\s die Datei auch nach dem Speichern im Modus
    STREAM_SHARE_DENYWRITE ge"offnet bleiben.


    [R"uckgabewert]

    sal_Bool                sal_True
                        Das Dokument konnte gespeichert werden.

                        sal_False
                        Das Dokument konnte nicht gespeichert werden, ein
                        Fehlercode ist mit <SvMedium::GetError()const> zu
                        erhalten.


    [Beispiel]

    sal_Bool DocSh::ConvertTo( SfxMedium &rMedium )
    {
        SvStreamRef xStream = rMedium.GetOutStream();
        if ( xStream.is() )
        {
            xStream->SetBufferSize(4096);
            *xStream << ...;

            rMedium.CloseOutStream(); // "offnet automatisch wieder den InStream
            return SVSTREAM_OK == rMedium.GetError();
        }
        return sal_False ;
    }


    [Querverweise]

    <SfxObjectShell::ConvertFrom(SfxMedium&)>
    <SFX_FILTER_REGISTRATION>
*/

/*?*/ {
/*?*/ 	return sal_False;
/*?*/ }

//-------------------------------------------------------------------------

/*?*/ void SfxObjectShell::SetEAs_Impl( SfxMedium &rMedium )
/*?*/ {DBG_BF_ASSERT(0, "STRIP"); //STRIP001 
//STRIP001 	//!! wenn OV eine entsprechende Funktionalitaet zur Verfuegung stellt,
//STRIP001 	// besser auf der geoeffneten Datei arbeiten
//STRIP001 /*?*/ 	SvEaMgr *pMgr = rMedium.GetEaMgr();
//STRIP001 /*?*/ 	SvEaMgr *pOld = GetMedium()->GetEaMgr();
//STRIP001 /*?*/ 	if ( !pMgr )
//STRIP001 /*?*/ 		return;
//STRIP001 /*?*/ 
//STRIP001 /*?*/ 	if ( pOld )
//STRIP001 /*?*/ 		pOld->Clone( *pMgr );
//STRIP001 /*?*/ 
//STRIP001 /*?*/ 	String aBuffer;
//STRIP001 /*?*/ 	pMgr->SetComment( GetDocInfo().GetComment() );
//STRIP001 /*?*/ 
//STRIP001 /*?*/ 	pMgr->SetFileType( rMedium.GetFilter()->GetTypeName().GetToken( 0, ';' ) );
//STRIP001 /*?*/ 	if ( SvEaMgr::GetAppCreator(aBuffer) )
//STRIP001 /*?*/ 		pMgr->SetCreator(aBuffer);
//STRIP001 /*?*/ 
//STRIP001 /*?*/ 	if ( rMedium.GetLongName().Len() )
//STRIP001 /*?*/ 		pMgr->SetLongName(rMedium.GetLongName());
/*?*/ }

//-------------------------------------------------------------------------

/*?*/ sal_Bool SfxObjectShell::DoSave_Impl( const SfxItemSet* pArgs )
/*?*/ {DBG_BF_ASSERT(0, "STRIP"); return sal_False; //STRIP001 
//STRIP001 /*?*/ 	SfxMedium *pMedium = GetMedium();
//STRIP001 /*?*/     const SfxFilter* pFilter = pMedium->GetFilter();
//STRIP001 /*?*/ 
//STRIP001 /*?*/     // copy the original itemset, but remove the "version" item, because pMediumTmp
//STRIP001 /*?*/     // is a new medium "from scratch", so no version should be stored into it
//STRIP001 /*?*/     SfxItemSet* pSet = pMedium->GetItemSet() ? new SfxAllItemSet(*pMedium->GetItemSet()): 0;
//STRIP001 /*?*/     pSet->ClearItem( SID_VERSION );
//STRIP001 /*?*/ 
//STRIP001 /*?*/     // create a medium as a copy; this medium is only for writingm, because it uses the same name as the original one
//STRIP001 /*?*/     // writing is done through a copy, that will be transferred to the target ( of course after calling HandsOff )
//STRIP001 /*?*/     SfxMedium* pMediumTmp = new SfxMedium( pMedium->GetName(), pMedium->GetOpenMode(), pMedium->IsDirect(), pFilter, pSet );
//STRIP001 /*?*/     pMediumTmp->SetLongName( pMedium->GetLongName() );
//STRIP001 /*?*/     pMediumTmp->CreateTempFileNoCopy();
//STRIP001 /*?*/     if ( pMediumTmp->GetErrorCode() != ERRCODE_NONE )
//STRIP001 /*?*/     {
//STRIP001 /*?*/         SetError( pMediumTmp->GetError() );
//STRIP001 /*?*/         delete pMediumTmp;
//STRIP001 /*?*/         return sal_False;
//STRIP001 /*?*/     }
//STRIP001 /*?*/ 
//STRIP001 /*?*/     // some awful base URL stuff
//STRIP001 /*?*/     const String aOldURL( so3::StaticBaseUrl::GetBaseURL() );
//STRIP001 /*?*/     if( GetCreateMode() != SFX_CREATE_MODE_EMBEDDED )
//STRIP001 /*?*/         if ( ShallSetBaseURL_Impl(*pMedium) )
//STRIP001 /*?*/             so3::StaticBaseUrl::SetBaseURL( pMedium->GetBaseURL() );
//STRIP001 /*?*/         else
//STRIP001 /*?*/             so3::StaticBaseUrl::SetBaseURL( String() );
//STRIP001 /*?*/ 
//STRIP001 /*?*/     // copy version list from "old" medium to target medium, so it can be used on saving
//STRIP001 /*?*/     pMediumTmp->TransferVersionList_Impl( *pMedium );
//STRIP001 /*?*/ 
//STRIP001 /*?*/     if ( pFilter && ( pFilter->GetFilterFlags() & SFX_FILTER_PACKED ) )
//STRIP001 /*?*/         SetError( GetMedium()->Unpack_Impl( pMedium->GetPhysicalName() ) );
//STRIP001 /*?*/ 
//STRIP001 /*?*/ 	// an interaction handler here can aquire only in case of GUI Saving
//STRIP001 /*?*/ 	// and should be removed after the saving is done
//STRIP001 /*?*/ 	::com::sun::star::uno::Reference< XInteractionHandler > xInteract;
//STRIP001 /*?*/ 	SFX_ITEMSET_ARG( pArgs, pxInteractionItem, SfxUnoAnyItem, SID_INTERACTIONHANDLER, sal_False );
//STRIP001 /*?*/ 	if ( pxInteractionItem && ( pxInteractionItem->GetValue() >>= xInteract ) && xInteract.is() )
//STRIP001 /*?*/ 		pMediumTmp->GetItemSet()->Put( SfxUnoAnyItem( SID_INTERACTIONHANDLER, makeAny( xInteract ) ) );
//STRIP001 /*?*/ 
//STRIP001 /*?*/ 	sal_Bool bSaved = sal_False;
//STRIP001 /*?*/     if( !GetError() && SaveTo_Impl( *pMediumTmp, pArgs, sal_True ) )
//STRIP001 /*?*/     {
//STRIP001 /*?*/         bSaved = sal_True;
//STRIP001 /*?*/ 
//STRIP001 /*?*/         // restore BaseURL
//STRIP001 /*?*/         so3::StaticBaseUrl::SetBaseURL( aOldURL );
//STRIP001 /*?*/ 
//STRIP001 /*?*/ 		if( pMediumTmp->GetItemSet() )
//STRIP001 /*?*/ 			pMediumTmp->GetItemSet()->ClearItem( SID_INTERACTIONHANDLER );
//STRIP001 /*?*/ 
//STRIP001 /*?*/         SetError(pMediumTmp->GetErrorCode());
//STRIP001 /*?*/ 
//STRIP001 /*?*/         if ( !IsHandsOff() )
//STRIP001 /*?*/             DoHandsOff();
//STRIP001 /*?*/ 		pMediumTmp->Close();
//STRIP001 /*?*/ 
//STRIP001 /*?*/         sal_Bool bOpen = DoSaveCompleted(pMediumTmp);
//STRIP001 /*?*/         DBG_ASSERT(bOpen,"Fehlerbehandlung fuer DoSaveCompleted nicht implementiert");
//STRIP001 /*?*/     }
//STRIP001 /*?*/     else
//STRIP001 /*?*/     {
//STRIP001 /*?*/         // restore BaseURL
//STRIP001 /*?*/         so3::StaticBaseUrl::SetBaseURL( aOldURL );
//STRIP001 /*?*/ 
//STRIP001 /*?*/         // transfer error code from medium to objectshell
//STRIP001 /*?*/         SetError( pMediumTmp->GetError() );
//STRIP001 /*?*/ 
//STRIP001 /*?*/         // reconnect to object storage
//STRIP001 /*?*/         if ( IsHandsOff() )
//STRIP001 /*?*/         {
//STRIP001 /*?*/             if ( !DoSaveCompleted( pMedium ) )
//STRIP001 /*?*/                 DBG_ERROR("Case not handled - no way to get a storage!");
//STRIP001 /*?*/         }
//STRIP001 /*?*/         else
//STRIP001 /*?*/             DoSaveCompleted( (SvStorage*)0 );
//STRIP001 /*?*/ 
//STRIP001 /*?*/         delete pMediumTmp;
//STRIP001 /*?*/     }
//STRIP001 /*?*/ 
//STRIP001 /*?*/     SetModified( !bSaved );
//STRIP001 /*?*/ 	return bSaved;
/*?*/ }

//-------------------------------------------------------------------------

/*?*/ sal_Bool SfxObjectShell::Save_Impl( const SfxItemSet* pSet )
/*?*/ {DBG_BF_ASSERT(0, "STRIP"); return sal_False;//STRIP001 
//STRIP001 /*?*/ 	DBG_CHKTHIS(SfxObjectShell, 0);
//STRIP001 /*?*/ 	SfxApplication *pSfxApp = SFX_APP();
//STRIP001 /*?*/ 
//STRIP001 /*?*/ 	pImp->bIsSaving = sal_True;
//STRIP001 /*?*/ 	sal_Bool bSaved;
//STRIP001 /*?*/ 	SFX_ITEMSET_ARG( GetMedium()->GetItemSet(), pSalvageItem, SfxStringItem, SID_DOC_SALVAGE, sal_False);
//STRIP001 /*?*/ 	if ( pSalvageItem )
//STRIP001 /*?*/ 	{
//STRIP001 /*?*/ 		SFX_ITEMSET_ARG( GetMedium()->GetItemSet(), pFilterItem, SfxStringItem, SID_FILTER_NAME, sal_False);
//STRIP001 /*?*/         String aFilterName;
//STRIP001 /*?*/         const SfxFilter *pFilter = NULL;
//STRIP001 /*?*/         if ( pFilterItem )
//STRIP001 /*?*/             pFilter = GetFactory().GetFilterContainer()->GetFilter( aFilterName );
//STRIP001 /*?*/ 
//STRIP001 /*?*/ 		SfxMedium *pMed = new SfxMedium(
//STRIP001 /*?*/ 			pSalvageItem->GetValue(), STREAM_READWRITE | STREAM_SHARE_DENYWRITE, sal_False, pFilter );
//STRIP001 /*?*/ 
//STRIP001 /*?*/ 		SFX_ITEMSET_ARG( GetMedium()->GetItemSet(), pPasswordItem, SfxStringItem, SID_PASSWORD, sal_False );
//STRIP001 /*?*/ 		if ( pPasswordItem )
//STRIP001 /*?*/ 			pMed->GetItemSet()->Put( *pPasswordItem );
//STRIP001 /*?*/ 
//STRIP001 /*?*/ 		bSaved = DoSaveAs( *pMed );
//STRIP001 /*?*/ 		if ( bSaved )
//STRIP001 /*?*/ 			bSaved = DoSaveCompleted( pMed );
//STRIP001 /*?*/ 		else
//STRIP001 /*?*/ 			delete pMed;
//STRIP001 /*?*/ 	}
//STRIP001 /*?*/ 	else
//STRIP001 /*?*/ 		bSaved = DoSave_Impl( pSet );
//STRIP001 /*?*/     if ( bSaved && SvtSaveOptions().IsAutoSave() )
//STRIP001 /*?*/ 		pSfxApp->GetAutoSaveTimer_Impl()->Start();
//STRIP001 /*?*/ 	return bSaved;
/*?*/ }

//-------------------------------------------------------------------------

/*N*/ sal_Bool SfxObjectShell::CommonSaveAs_Impl
/*N*/ (
/*N*/ 	const INetURLObject&   aURL,
/*N*/ 	const String&   aFilterName,
/*N*/ 	SfxItemSet*     aParams
/*N*/ )
/*N*/ {
/*N*/ 	SFX_APP()->NotifyEvent(SfxEventHint(SFX_EVENT_SAVEASDOC,this));
/*N*/ 	BOOL bWasReadonly = IsReadOnly();
/*N*/ 
/*N*/ 	if( aURL.HasError() )
/*N*/ 	{
/*N*/ 		SetError( ERRCODE_IO_INVALIDPARAMETER );
/*N*/ 		return sal_False;
/*N*/ 	}
/*N*/ 
/*N*/     DBG_ASSERT( aURL.GetProtocol() != INET_PROT_NOT_VALID, "Illegal URL!" );
/*N*/     DBG_ASSERT( aParams->Count() != 0, "fehlerhafte Parameter");
/*N*/ 
/*N*/     SFX_ITEMSET_ARG( aParams, pSaveToItem, SfxBoolItem, SID_SAVETO, sal_False );
/*N*/     sal_Bool bSaveTo = pSaveToItem ? pSaveToItem->GetValue() : sal_False;
/*N*/ 
/*N*/     const SfxFilter* pFilter = GetFactory().GetFilterContainer()->GetFilter( aFilterName );
/*N*/     if ( !pFilter
/*N*/ 		|| !pFilter->CanExport()
/*N*/ 		|| !bSaveTo && !pFilter->CanImport() )
/*N*/     {
/*N*/         SetError( ERRCODE_IO_INVALIDPARAMETER );
/*N*/         return sal_False;
/*N*/     }
/*N*/ 
/*N*/ 	pImp->bPasswd = aParams && SFX_ITEM_SET == aParams->GetItemState(SID_PASSWORD);
/*N*/ 
/*N*/ 	SfxMedium *pActMed = GetMedium();
/*N*/ 	const INetURLObject aActName(pActMed->GetName());
/*N*/ 
/*N*/ 	if ( aURL == aActName 
/*N*/ 		&& aURL != INetURLObject( OUString::createFromAscii( "private:stream" ) ) )
/*N*/ 	{
/*?*/ 		if ( IsReadOnly() )
/*?*/ 		{
/*?*/ 			SetError(ERRCODE_SFX_DOCUMENTREADONLY);
/*?*/ 			return sal_False;
/*?*/ 		}
/*?*/ 		// gleicher Filter? -> Save()
/*?*/ 		const SfxFilter *pFilter = pActMed->GetFilter();
/*?*/         if ( pFilter && pFilter->GetFilterName() == aFilterName )
/*?*/ 		{
/*?*/ 			pImp->bIsSaving=sal_False;
/*?*/ 			if ( aParams )
/*?*/ 			{
/*?*/ 				SfxItemSet* pSet = pMedium->GetItemSet();
/*?*/ 				pSet->ClearItem( SID_PASSWORD );
/*?*/ 				pSet->Put( *aParams );
/*?*/ 			}
/*?*/ 			return DoSave_Impl();
/*?*/ 		}
/*N*/ 	}

/*N*/     if( SFX_ITEM_SET != aParams->GetItemState(SID_UNPACK) && SvtSaveOptions().IsSaveUnpacked() )
/*N*/         aParams->Put( SfxBoolItem( SID_UNPACK, sal_False ) );
/*N*/ 
/*N*/ 	if ( PreDoSaveAs_Impl(aURL.GetMainURL( INetURLObject::NO_DECODE ),aFilterName,aParams))
/*N*/ 	{
/*N*/ 		pImp->bWaitingForPicklist = sal_True;
/*N*/ 		if (!pImp->bSetStandardName)
/*N*/ 			pImp->bDidWarnFormat=sal_False;
/*N*/ 
/*N*/ 		// Daten am Medium updaten
/*N*/ 		SfxItemSet *pSet = GetMedium()->GetItemSet();
/*N*/ 		pSet->ClearItem( SID_INTERACTIONHANDLER );
/*N*/ 
/*N*/ 		if ( !bSaveTo )
/*N*/ 		{
/*N*/ 			pSet->ClearItem( SID_REFERER );
/*N*/ 			pSet->ClearItem( SID_POSTDATA );
/*N*/ 			pSet->ClearItem( SID_TEMPLATE );
/*N*/ 			pSet->ClearItem( SID_DOC_READONLY );
/*N*/ 			pSet->ClearItem( SID_CONTENTTYPE );
/*N*/ 			pSet->ClearItem( SID_CHARSET );
/*N*/ 			pSet->ClearItem( SID_FILTER_NAME );
/*N*/ 			pSet->ClearItem( SID_OPTIONS );
/*N*/ 			//pSet->ClearItem( SID_FILE_FILTEROPTIONS );
/*N*/ 			pSet->ClearItem( SID_VERSION );
/*N*/ 			//pSet->ClearItem( SID_USE_FILTEROPTIONS );
/*N*/ 			pSet->ClearItem( SID_EDITDOC );
/*N*/ 
/*N*/ 			SFX_ITEMSET_GET( (*aParams), pFilterItem, SfxStringItem, SID_FILTER_NAME, sal_False );
/*N*/ 			if ( pFilterItem )
/*N*/ 				pSet->Put( *pFilterItem );
/*N*/ 
/*N*/ 			SFX_ITEMSET_GET( (*aParams), pOptionsItem, SfxStringItem, SID_OPTIONS, sal_False );
/*N*/ 			if ( pOptionsItem )
/*N*/ 				pSet->Put( *pOptionsItem );
/*N*/ 
/*N*/ 			SFX_ITEMSET_GET( (*aParams), pFilterOptItem, SfxStringItem, SID_FILE_FILTEROPTIONS, sal_False );
/*N*/ 			if ( pFilterOptItem )
/*N*/ 				pSet->Put( *pFilterOptItem );
/*N*/ 		}
/*N*/ 
/*N*/ 		SFX_APP()->NotifyEvent(SfxEventHint(SFX_EVENT_SAVEASDOCDONE,this));
/*N*/ 
/*N*/ 		if ( bWasReadonly && !bSaveTo )
/*N*/ 			Broadcast( SfxSimpleHint(SFX_HINT_MODECHANGED) );
/*N*/ 
/*N*/ 		return sal_True;
/*N*/ 	}
/*N*/ 	else
/*N*/ 		return sal_False;
/*N*/ }

//-------------------------------------------------------------------------

/*N*/ sal_Bool SfxObjectShell::PreDoSaveAs_Impl
/*N*/ (
/*N*/ 	const String&   rFileName,
/*N*/ 	const String&   aFilterName,
/*N*/ 	SfxItemSet*     pParams
/*N*/ )
/*N*/ {
/*N*/     // copy all items stored in the itemset of the current medium
/*N*/     SfxAllItemSet* pMergedParams = new SfxAllItemSet( *pMedium->GetItemSet() );
/*N*/ 
/*N*/     // in "SaveAs" title and password will be cleared ( maybe the new itemset contains new values, otherwise they will be empty )
/*N*/ 	pMergedParams->ClearItem( SID_PASSWORD );
/*N*/ 	pMergedParams->ClearItem( SID_DOCINFO_TITLE );
/*N*/ 
/*N*/ 	pMergedParams->ClearItem( SID_INPUTSTREAM );
/*N*/ 	pMergedParams->ClearItem( SID_CONTENT );
/*N*/ 
/*N*/ 	pMergedParams->ClearItem( SID_REPAIRPACKAGE );
/*N*/ 
/*N*/     // "SaveAs" will never store any version information - it's a complete new file !
/*N*/     pMergedParams->ClearItem( SID_VERSION );
/*N*/ 
/*N*/     // merge the new parameters into the copy
/*N*/     // all values present in both itemsets will be overwritten by the new parameters
/*N*/     if( pParams )
/*N*/ 		pMergedParams->Put( *pParams );
/*N*/     //DELETEZ( pParams );
/*N*/ 
/*N*/ #ifdef DBG_UTIL
/*N*/     if ( pMergedParams->GetItemState( SID_DOC_SALVAGE) >= SFX_ITEM_SET )
/*N*/         DBG_ERROR("Salvage item present in Itemset, check the parameters!");
/*N*/ #endif
/*N*/ 
/*N*/     // should be unneccessary - too hot to handle!
/*N*/ 	pMergedParams->ClearItem( SID_DOC_SALVAGE );
/*N*/ 
/*N*/     // take over the new merged itemset
/*N*/ 	pParams = pMergedParams;
/*N*/ 
/*N*/     // create a medium for the target URL
/*N*/     SfxMedium *pNewFile = new SfxMedium( rFileName, STREAM_READWRITE | STREAM_SHARE_DENYWRITE, sal_False, 0, pParams );
/*N*/ 
/*N*/     // set filter; if no filter is given, take the default filter of the factory
/*N*/     if ( aFilterName.Len() )
/*N*/         pNewFile->SetFilter( GetFactory(), aFilterName );
/*N*/ 	else
/*N*/         pNewFile->SetFilter( GetFactory().GetFilterContainer()->GetFilter(0) );
/*N*/ 
/*N*/     // saving is alway done using a temporary file
/*N*/     pNewFile->CreateTempFileNoCopy();
/*N*/     if ( pNewFile->GetErrorCode() != ERRCODE_NONE )
/*N*/     {
/*N*/         // creating temporary file failed ( f.e. floppy disk not inserted! )
/*N*/         SetError( pNewFile->GetError() );
/*N*/         delete pNewFile;
/*N*/         return sal_False;
/*N*/     }
/*N*/ 
/*N*/     // check if a "SaveTo" is wanted, no "SaveAs"
/*N*/     SFX_ITEMSET_ARG( pParams, pSaveToItem, SfxBoolItem, SID_SAVETO, sal_False );
/*N*/     sal_Bool bCopyTo = GetCreateMode() == SFX_CREATE_MODE_EMBEDDED || pSaveToItem && pSaveToItem->GetValue();
/*N*/ 
/*N*/     // some base URL stuff ( awful, but not avoidable ... )
/*N*/     const String aOldURL( so3::StaticBaseUrl::GetBaseURL() );
/*N*/ 	if( GetCreateMode() != SFX_CREATE_MODE_EMBEDDED )
/*N*/ 		if ( ShallSetBaseURL_Impl(*pNewFile) )
/*N*/ 			so3::StaticBaseUrl::SetBaseURL( pNewFile->GetBaseURL() );
/*N*/ 		else
/*N*/ 			so3::StaticBaseUrl::SetBaseURL( String() );
/*N*/ 
/*N*/     // distinguish between "Save" and "SaveAs"
/*N*/     pImp-> bIsSaving = sal_False;
/*N*/ 
/*N*/ 	sal_Bool bToOwnFormat = sal_True;//STRIP007 IsOwnStorageFormat_Impl(*pNewFile);
/*N*/ 	if ( bToOwnFormat )
/*N*/ 	{
/*N*/         // If the filter is a "cross export" filter ( f.e. a filter for exporting an impress document from
/*N*/         // a draw document ), the ClassId of the destination storage is different from the ClassId of this
/*N*/         // document. It can be retrieved from the default filter for the desired target format
/*N*/         long nFormat = pNewFile->GetFilter()->GetFormat();
/*N*/ 		SfxFilterMatcher& rMatcher = SFX_APP()->GetFilterMatcher();
/*N*/ 		const SfxFilter *pFilt = rMatcher.GetFilter4ClipBoardId( nFormat );
/*N*/ 		if ( pFilt )
/*N*/ 		{
/*N*/             if ( pFilt->GetFilterContainer() != pNewFile->GetFilter()->GetFilterContainer() )
/*N*/                 pNewFile->GetStorage()->SetClass( SvFactory::GetServerName( nFormat ), nFormat, pFilt->GetTypeName() );
/*N*/ 		}
/*N*/ 	}
/*N*/ 
/*N*/ 	if ( GetMedium()->GetFilter() && ( GetMedium()->GetFilter()->GetFilterFlags() & SFX_FILTER_PACKED ) )
/*N*/ 	{DBG_BF_ASSERT(0, "STRIP"); //STRIP001 
//STRIP001 /*?*/ 		SfxMedium *pMed = bCopyTo ? pMedium : pNewFile;
//STRIP001 /*?*/         pNewFile->SetError( GetMedium()->Unpack_Impl( pMed->GetPhysicalName() ) );
/*N*/ 	}
/*N*/ 
/*N*/     // Save the document ( first as temporary file, then transfer to the target URL by committing the medium )
/*N*/     sal_Bool bOk = sal_False;
/*N*/     if ( !pNewFile->GetErrorCode() && SaveTo_Impl( *pNewFile, NULL, sal_True ) )
/*N*/ 	{
/*N*/ 		bOk = sal_True;
/*N*/ 
/*N*/         // restore old BaseURL
/*N*/ 		so3::StaticBaseUrl::SetBaseURL( aOldURL );
/*N*/ 
/*N*/         // transfer a possible error from the medium to the document
/*N*/         SetError( pNewFile->GetErrorCode() );
/*N*/ 
/*N*/         // notify the document that saving was done successfully
/*N*/         if ( bCopyTo )
/*N*/ 		{
/*N*/         	if ( IsHandsOff() )
/*N*/ 				bOk = DoSaveCompleted( pMedium );
/*N*/ 		}
/*N*/ 		else
/*N*/ 		{
/*N*/ 			// Muss !!!
/*N*/ 			if ( bToOwnFormat )
/*N*/ 				SetFileName( pNewFile->GetPhysicalName() );
/*N*/ 
/*N*/ 			bOk = DoSaveCompleted( pNewFile );
/*N*/ 		}
/*N*/ 
/*N*/ 		if( bOk )
/*N*/ 		{
/*N*/             if( !bCopyTo )
/*N*/                 SetModified( sal_False );
/*N*/ 		}
/*N*/ 		else
/*N*/ 		{
/*N*/             DBG_ASSERT( !bCopyTo, "Error while reconnecting to medium, can't be handled!");
/*N*/ 			SetError( pNewFile->GetErrorCode() );
/*N*/ 
/*N*/             if ( !bCopyTo )
/*N*/             {
/*N*/                 // reconnect to the old medium
/*?*/                 BOOL bRet = DoSaveCompleted( pMedium );
/*?*/                 DBG_ASSERT( bRet, "Error in DoSaveCompleted, can't be handled!");
/*N*/             }
/*N*/ 
/*N*/ 			DELETEZ( pNewFile );
/*N*/ 		}
/*N*/ 
/*N*/ 		String aPasswd;
/*N*/ 		if ( IsOwnStorageFormat_Impl( *GetMedium() ) && GetPasswd_Impl( GetMedium()->GetItemSet(), aPasswd ) )
/*?*/ 			GetMedium()->GetStorage()->SetKey( S2BS( aPasswd ) );	//!!! (pb) needs new implementation
/*N*/ 	}
/*N*/ 	else
/*N*/ 	{
/*?*/ 		so3::StaticBaseUrl::SetBaseURL( aOldURL );
/*?*/         SetError( pNewFile->GetErrorCode() );
/*?*/ 
/*?*/         // reconnect to the old storage
/*?*/         if ( IsHandsOff() )
/*?*/             DoSaveCompleted( pMedium );
/*?*/         else
/*?*/             DoSaveCompleted( (SvStorage*)0 );
/*?*/ 
/*?*/         DELETEZ( pNewFile );
/*N*/ 	}
/*N*/ 
/*N*/     if( !bOk )
/*?*/         SetModified( sal_True );
/*N*/ 
/*N*/ 	if ( bCopyTo )
/*N*/         DELETEZ( pNewFile );
/*N*/ 
/*N*/ 	return bOk;
/*N*/ }

//------------------------------------------------------------------------

/*?*/ sal_Bool SfxObjectShell::LoadFrom( SvStorage *pStor )
/*?*/ {
/*?*/ #if SUPD<635
/*?*/     if (pStor->IsStream(SfxConfigManager::GetStreamName()))
/*?*/         SetConfigManager (new SfxConfigManager( pStor, 0));
/*?*/ #else
/*?*/ 	GetConfigManager();
/*?*/ #endif
/*?*/ 	GetDocInfo().Load(pStor);
/*?*/ 	return sal_True;
/*?*/ }

//-------------------------------------------------------------------------

/*?*/ sal_Bool SfxObjectShell::CanReload_Impl()

/*  [Beschreibung]

    Interne Methode zum Feststellen, ob eine erneutes Laden des
    Dokuments (auch als RevertToSaved oder LastVersion bekannt)
    m"oglich ist.
*/

/*?*/ {
/*?*/     return pMedium && HasName() && !IsInModalMode() && !pImp->bForbidReload;
/*?*/ }

//-------------------------------------------------------------------------

/*N*/ sal_Bool SfxObjectShell::IsInformationLost()
/*N*/ {
/*N*/ 	const SfxFilter *pFilt = GetMedium()->GetFilter();
/*N*/     if ( pFilt == GetFactory().GetFilterContainer()->GetFilter(0) )
/*N*/         return sal_False;
/*N*/     return pFilt && pFilt->IsAlienFormat() && pImp->bDidDangerousSave && !(pFilt->GetFilterFlags() & SFX_FILTER_SILENTEXPORT);
/*N*/ }

/*N*/ sal_Bool SfxObjectShell::LoadOwnFormat( SfxMedium& rMedium )
/*N*/ {
/*N*/ 	SvStorageRef xStor = rMedium.GetStorage();
/*N*/ 	if ( xStor.Is() )
/*N*/ 	{
/*N*/ 		if ( rMedium.GetFileVersion() )
/*N*/ 			xStor->SetVersion( rMedium.GetFileVersion() );
/*N*/ 
/*N*/ 		// Password
/*N*/         SFX_ITEMSET_ARG( rMedium.GetItemSet(), pPasswdItem, SfxStringItem, SID_PASSWORD, sal_False );
/*N*/         if ( pPasswdItem || ERRCODE_IO_ABORT != CheckPasswd_Impl( this, SFX_APP()->GetPool(), pMedium ) )
/*N*/ 		{
/*N*/ 			String aPasswd;
/*N*/ 			if ( GetPasswd_Impl(pMedium->GetItemSet(), aPasswd) )
/*N*/ 				xStor->SetKey( S2BS( aPasswd ) ); //!!! (pb) needs new implementation
/*N*/ 
/*N*/ 			// load document
/*N*/ 			return Load( xStor );
/*N*/ 		}
/*N*/ 		return sal_False;
/*N*/ 	}
/*N*/ 	else
/*N*/ 		return sal_False;
/*N*/ }

/*N*/ sal_Bool SfxObjectShell::SaveAsOwnFormat( SfxMedium& rMedium )
/*N*/ {
/*N*/ 	SvStorageRef xStor = rMedium.GetStorage();
/*N*/ 	if( xStor.Is() )
/*N*/ 	{
/*N*/ 		ULONG nVersion = rMedium.GetFilter()->GetVersion();
/*N*/ 		xStor->SetVersion( nVersion );
/*N*/ 
/*N*/ 		// Initialize Basic
/*N*/ 		GetBasicManager();
/*N*/ 
/*N*/ 		// Save dialog container
/*N*/ 		if( nVersion >= 6200 )
/*N*/ 		{
/*N*/ 			SfxDialogLibraryContainer* pDialogCont = pImp->pDialogLibContainer;
/*N*/ 			if( pDialogCont )
/*N*/ 				pDialogCont->storeLibrariesToStorage( (SotStorage*)(SvStorage*)xStor );
/*N*/ 
/*N*/ 			SfxScriptLibraryContainer* pBasicCont = pImp->pBasicLibContainer;
/*N*/ 			if( pBasicCont )
/*N*/ 				pBasicCont->storeLibrariesToStorage( (SotStorage*)(SvStorage*)xStor );
/*N*/ 
/*N*/ 			// Konfiguration schreiben
/*N*/ 			if ( GetConfigManager() )
/*N*/ 			{
/* //!MBA
                if ( rDocInfo.HasTemplateConfig() )
                {
                    const String aTemplFileName( rDocInfo.GetTemplateFileName() );
                    if ( aTemplFileName.Len() )
                    {
                        INetURLObject aURL( aTemplFileName );
                        DBG_ASSERT( aURL.GetProtocol() != INET_PROT_NOT_VALID, "Illegal URL !" );

                        SvStorageRef aStor = new SvStorage( aURL.GetMainURL( INetURLObject::NO_DECODE ) );
                        if ( SVSTREAM_OK == aStor->GetError() )
                        {
                            GetConfigManager()->StoreConfiguration(aStor);
                            if (aRef->IsStream(SfxConfigManager::GetStreamName()))
                                aRef->Remove(SfxConfigManager::GetStreamName());
                        }
                    }
                }
                else
 */
/*N*/ 				{
//! MBA                    GetConfigManager()->SetModified( sal_True );
/*N*/ 					SotStorageRef xCfgStor = pImp->pCfgMgr->GetConfigurationStorage( xStor );
/*N*/                     if ( pImp->pCfgMgr->StoreConfiguration( xCfgStor ) )
/*N*/ 						xCfgStor->Commit();
/*N*/ 				}
/*N*/ 			}
/*N*/ 
/*N*/ 		}
/*N*/ 
/*N*/ 		const SfxFilter* pFilter = rMedium.GetFilter();
/*N*/ 		return SaveAs( xStor );
/*N*/ 	}
/*N*/ 	else return sal_False;
/*N*/ }


/*N*/ void SfxObjectShell::AddXMLAsZipToTheStorage( SvStorage& rRoot )
/*N*/ {
/*N*/ 	static struct _ObjExpType {
/*N*/ 		sal_Bool (SvtAddXMLToStorageOptions:: *fnIsAdd)() const;
/*N*/ 		const sal_Char* pModuleNm;
/*N*/ 		// GlobalNameId
/*N*/ 		UINT32 n1;
/*N*/ 		USHORT n2, n3;
/*N*/ 		BYTE b8, b9, b10, b11, b12, b13, b14, b15;
/*N*/ 	} aArr[] = {
/*N*/ 		{ &SvtAddXMLToStorageOptions::IsWriter_Add_XML_to_Storage,
/*N*/ 			"Writer", BF_SO3_SW_CLASSID_50 },
/*N*/ 		{ &SvtAddXMLToStorageOptions::IsCalc_Add_XML_to_Storage,
/*N*/ 			"Calc", BF_SO3_SC_CLASSID_50 },
/*N*/ 		{ &SvtAddXMLToStorageOptions::IsImpress_Add_XML_to_Storage,
/*N*/ 			"Impress", BF_SO3_SIMPRESS_CLASSID_50 },
/*N*/ 		{ &SvtAddXMLToStorageOptions::IsDraw_Add_XML_to_Storage,
/*N*/ 			"Draw", BF_SO3_SDRAW_CLASSID_50 },
/*N*/ 		{ 0 }
/*N*/ 	};
/*N*/ 
/*N*/ 	for( const _ObjExpType* pArr = aArr; pArr->fnIsAdd; ++pArr )
/*N*/ 	{
/*N*/ 		SvGlobalName aGlbNm( pArr->n1, pArr->n2, pArr->n3,
/*N*/ 							pArr->b8, pArr->b9, pArr->b10, pArr->b11,
/*N*/ 							pArr->b12, pArr->b13, pArr->b14, pArr->b15 );
/*N*/ 		if( *GetSvFactory() == aGlbNm )
/*N*/ 		{
/*?*/ 			// 1. check if the option is set and unequal 0 or is not set
/*?*/ 			SvtAddXMLToStorageOptions aOpt;
/*?*/ 			if( (aOpt.*pArr->fnIsAdd)() )
/*?*/ 			{
/*?*/ 				// the flag is set
/*?*/ 				String sStr;
/*?*/ 				sStr.AssignAscii( "StarOffice XML (" );
/*?*/ 				sStr.AppendAscii( pArr->pModuleNm );
/*?*/ 				sStr += ')';
/*?*/ 				// 2. exist the XML filter? "StarOffice XML (<Application>)"?
/*?*/ 				const SfxFilter* pFilter = GetFactory().GetFilterContainer()->
/*?*/ 												GetFilter4FilterName( sStr );
/*?*/ 				if( pFilter )
/*?*/ 				{
/*?*/ 					::utl::TempFile aTempFile;
/*?*/ 					SfxMedium		aTmpMed( aTempFile.GetURL(), STREAM_READ | STREAM_WRITE, sal_True );
/*?*/ 
/*?*/ 					aTmpMed.SetFilter( pFilter );
/*?*/ 
/*?*/ 					if( ConvertTo( aTmpMed ) )
/*?*/ 					{
/*?*/                         SvStorage* pXMLStor = aTmpMed.GetStorage();
/*?*/ 
/*?*/ 						if( pXMLStor )
/*?*/ 						{
/*?*/ 							const String	aContent( String::CreateFromAscii( "Content" ) );
/*?*/ 							const String	aContentXML( String::CreateFromAscii( "Content.xml" ) );
/*?*/ 							const String	aXMLFormatName( String::CreateFromAscii( "XMLFormat2" ) );
/*?*/ 							String			aContentName;
/*?*/ 
/*?*/ 							if( pXMLStor->IsContained( aContentXML ) )
/*?*/ 								aContentName = aContentXML;
/*?*/ 							else if( pXMLStor->IsContained( aContent ) )
/*?*/ 								aContentName = aContent;
/*?*/ 
/*?*/ 							if( aContentName.Len() )
/*?*/ 							{
/*?*/ 								SvStorageStreamRef	xOStm( rRoot.OpenStream( aXMLFormatName, STREAM_WRITE | STREAM_TRUNC ) );
/*?*/ 								SvStorageStreamRef	xIStm( pXMLStor->OpenStream( aContentName, STREAM_READ | STREAM_NOCREATE ) );
/*?*/ 
/*?*/ 								if( xOStm.Is() && xIStm.Is() )
/*?*/ 								{
/*?*/ 									ZCodec aCodec;
/*?*/ 
/*?*/ 									xIStm->Seek( 0 );
/*?*/ 									aCodec.BeginCompression( ZCODEC_BEST_COMPRESSION );
/*?*/ 									aCodec.Compress( *xIStm, *xOStm );
/*?*/ 									aCodec.EndCompression();
/*?*/ 									xOStm->Commit();
/*?*/ 								}
/*?*/ 							}
/*?*/ 						}
/*?*/ 					}
/*?*/ 				}
/*?*/ 			}
/*?*/ 			// that's all
/*?*/ 			break;
/*N*/ 		}
/*N*/ 	}
/*N*/ }
}
