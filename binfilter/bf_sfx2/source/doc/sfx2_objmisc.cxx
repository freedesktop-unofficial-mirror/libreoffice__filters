/*************************************************************************
 *
 *  $RCSfile: sfx2_objmisc.cxx,v $
 *
 *  $Revision: 1.4 $
 *
 *  last change: $Author: hr $ $Date: 2004-08-03 14:52:25 $
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

#ifndef _INETMSG_HXX //autogen
#include <svtools/inetmsg.hxx>
#endif
#ifndef _SFXENUMITEM_HXX //autogen
#include <svtools/eitem.hxx>
#endif
#ifndef _SFXSTRITEM_HXX //autogen
#include <svtools/stritem.hxx>
#endif
#ifndef _SFXINTITEM_HXX //autogen
#include <svtools/intitem.hxx>
#endif
// auto strip #ifndef _SVSTOR_HXX //autogen
// auto strip #include <so3/svstor.hxx>
// auto strip #endif
#include <so3/inetbnd.hxx>
#include <vos/mutex.hxx>

#pragma hdrstop

// auto strip #ifndef _COM_SUN_STAR_SCRIPT_XTYPECONVERTER_HPP_
// auto strip #include <com/sun/star/script/XTypeConverter.hpp>
// auto strip #endif
// auto strip #ifndef _COM_SUN_STAR_SCRIPT_FINISHENGINEEVENT_HPP_
// auto strip #include <com/sun/star/script/FinishEngineEvent.hpp>
// auto strip #endif
// auto strip #ifndef _COM_SUN_STAR_SCRIPT_INTERRUPTREASON_HPP_
// auto strip #include <com/sun/star/script/InterruptReason.hpp>
// auto strip #endif
// auto strip #ifndef _COM_SUN_STAR_SCRIPT_XENGINELISTENER_HPP_
// auto strip #include <com/sun/star/script/XEngineListener.hpp>
// auto strip #endif
// auto strip #ifndef _COM_SUN_STAR_SCRIPT_XDEBUGGING_HPP_
// auto strip #include <com/sun/star/script/XDebugging.hpp>
// auto strip #endif
// auto strip #ifndef _COM_SUN_STAR_SCRIPT_XINVOKATION_HPP_
// auto strip #include <com/sun/star/script/XInvocation.hpp>
// auto strip #endif
// auto strip #ifndef _COM_SUN_STAR_SCRIPT_CONTEXTINFORMATION_HPP_
// auto strip #include <com/sun/star/script/ContextInformation.hpp>
// auto strip #endif
// auto strip #ifndef _COM_SUN_STAR_SCRIPT_FINISHREASON_HPP_
// auto strip #include <com/sun/star/script/FinishReason.hpp>
// auto strip #endif
// auto strip #ifndef _COM_SUN_STAR_SCRIPT_XENGINE_HPP_
// auto strip #include <com/sun/star/script/XEngine.hpp>
// auto strip #endif
// auto strip #ifndef _COM_SUN_STAR_SCRIPT_INTERRUPTENGINEEVENT_HPP_
// auto strip #include <com/sun/star/script/InterruptEngineEvent.hpp>
// auto strip #endif
// auto strip #ifndef _COM_SUN_STAR_SCRIPT_XLIBRARYACCESS_HPP_
// auto strip #include <com/sun/star/script/XLibraryAccess.hpp>
// auto strip #endif
#ifndef _COM_SUN_STAR_DOCUMENT_MACROEXECMODE_HPP_
#include <com/sun/star/document/MacroExecMode.hpp>
#endif

// auto strip #ifndef _TOOLKIT_HELPER_VCLUNOHELPER_HXX_
// auto strip #include <toolkit/unohlp.hxx>
// auto strip #endif

#include <com/sun/star/uno/Reference.h>
#include <com/sun/star/uno/Any.h>
#include <com/sun/star/ucb/XContent.hpp>
// auto strip #include <svtools/securityoptions.hxx>


using namespace ::com::sun::star::uno;
using namespace ::com::sun::star::ucb;
using namespace ::com::sun::star::document;

#ifndef _SB_SBUNO_HXX
#include <basic/sbuno.hxx>
#endif
// auto strip #ifndef _SB_SBSTAR_HXX
// auto strip #include <basic/sbstar.hxx>
// auto strip #endif
#ifndef _SB_BASMGR_HXX
#include <basic/basmgr.hxx>
#endif
// auto strip #ifndef _VCL_MSGBOX_HXX
// auto strip #include <vcl/msgbox.hxx>
// auto strip #endif
#ifndef _SBXCLASS_HXX //autogen
#include <svtools/sbx.hxx>
#endif
// auto strip #ifndef _SFXECODE_HXX
// auto strip #include <svtools/sfxecode.hxx>
// auto strip #endif
// auto strip #ifndef _EHDL_HXX
// auto strip #include <svtools/ehdl.hxx>
// auto strip #endif

// auto strip #include <svtools/pathoptions.hxx>
#include <unotools/ucbhelper.hxx>
// auto strip #include <tools/inetmime.hxx>
#include <svtools/inettype.hxx>

// auto strip #include "appdata.hxx"
#include "request.hxx"
// auto strip #include "bindings.hxx"
#include "sfxresid.hxx"
#include "docfile.hxx"
// auto strip #include "docinf.hxx"
// auto strip #include "docfilt.hxx"
#include "interno.hxx"
// auto strip #include "objsh.hxx"
#include "objshimp.hxx"
// auto strip #include "event.hxx"
#include "fltfnc.hxx"
#include "sfx.hrc"
#include "dispatch.hxx"
// auto strip #include "viewfrm.hxx"
#include "viewsh.hxx"
// auto strip #include "ctrlitem.hxx"
// auto strip #include "arrdecl.hxx"
// auto strip #include "module.hxx"
#include "macrconf.hxx"
#include "docfac.hxx"
// auto strip #include "helper.hxx"
#include "doc.hrc"
namespace binfilter {

// class SfxHeaderAttributes_Impl ----------------------------------------

/*N*/ class SfxHeaderAttributes_Impl : public SvKeyValueIterator
/*N*/ {
/*N*/ private:
/*N*/ 	SfxObjectShell* pDoc;
/*N*/ 	SvKeyValueIteratorRef xIter;
/*N*/ 	sal_Bool bAlert;
/*N*/ 
/*N*/ public:
/*N*/ 	SfxHeaderAttributes_Impl( SfxObjectShell* pSh ) :
/*N*/ 		pDoc( pSh ), SvKeyValueIterator(),
/*N*/ 		xIter( pSh->GetMedium()->GetHeaderAttributes_Impl() ),
/*N*/ 		bAlert( sal_False ) {}
/*N*/ 
/*N*/ 	virtual sal_Bool GetFirst( SvKeyValue& rKV ) { return xIter->GetFirst( rKV ); }
/*N*/ 	virtual sal_Bool GetNext( SvKeyValue& rKV ) { return xIter->GetNext( rKV ); }
/*N*/ 	virtual void Append( const SvKeyValue& rKV );
/*N*/ 
/*N*/ 	void ClearForSourceView() { xIter = new SvKeyValueIterator; bAlert = sal_False; }
/*N*/ 	void SetAttributes();
/*N*/ 	void SetAttribute( const SvKeyValue& rKV );
/*N*/ };

//=========================================================================

/*N*/ sal_uInt16 __READONLY_DATA aTitleMap_Impl[3][2] =
/*N*/ {
/*N*/ 								//	local				remote
/*N*/ 	/*	SFX_TITLE_CAPTION	*/	{ 	SFX_TITLE_FILENAME, SFX_TITLE_TITLE },
/*N*/ #ifdef MAC
/*N*/ 	/*	SFX_TITLE_PICKLIST  */	{ 	SFX_TITLE_FILENAME,	SFX_TITLE_FULLNAME },
/*N*/ #else
/*N*/ 	/*	SFX_TITLE_PICKLIST  */	{ 	32,					SFX_TITLE_FULLNAME },
/*N*/ #endif
/*N*/ 	/*	SFX_TITLE_HISTORY	*/	{ 	32,					SFX_TITLE_FULLNAME }
/*N*/ };

//=========================================================================

/*?*/ void SfxObjectShell::AbortImport()
/*?*/ {
/*?*/ 	pImp->bIsAbortingImport = sal_True;
/*?*/ }

//-------------------------------------------------------------------------

/*N*/ sal_Bool SfxObjectShell::IsAbortingImport() const
/*N*/ {
/*N*/ 	return pImp->bIsAbortingImport;
/*N*/ }

//-------------------------------------------------------------------------

/*N*/ #if SUPD<604
/*N*/ void SfxObjectShell::NotifyReloadAvailable()
/*N*/ {
/*N*/ }
/*N*/ #endif

//-------------------------------------------------------------------------

/*N*/ SfxDocumentInfo& SfxObjectShell::GetDocInfo()
/*N*/ {
/*N*/ 	if( !pImp->pDocInfo )
/*N*/ 	{
/*N*/ 		pImp->pDocInfo = new SfxDocumentInfo;
/*N*/ 		pImp->pDocInfo->SetReadOnly( IsReadOnly() );
/*N*/ 	}
/*N*/ 
/*N*/ 	return *pImp->pDocInfo;
/*N*/ }

//-------------------------------------------------------------------------

/*N*/ void SfxObjectShell::FlushDocInfo()
/*N*/ {
/*N*/ 	SetModified(sal_True);
/*N*/ 	SfxDocumentInfo &rInfo = GetDocInfo();
/*N*/ 	Broadcast( SfxDocumentInfoHint( &rInfo ) );
/*N*/ 	SetAutoLoad( rInfo.GetReloadURL(), rInfo.GetReloadDelay() * 1000,
/*N*/ 				 rInfo.IsReloadEnabled() );
/*N*/ 
/*N*/ 	// bitte beachten:
/*N*/ 	// 1. Titel in DocInfo aber nicht am Doc (nach HTML-Import)
/*N*/ 	// 	=> auch am Doc setzen
/*N*/ 	// 2. Titel in DocInfo leer (Briefumschlagsdruck)
/*N*/ 	//	=> nicht am Doc setzen, da sonst "unbenanntX" daraus wird
/*N*/ 	String aDocInfoTitle = GetDocInfo().GetTitle();
/*N*/ 	if ( aDocInfoTitle.Len() )
/*N*/ 		SetTitle( aDocInfoTitle );
/*N*/ }

//-------------------------------------------------------------------------

/*N*/ void SfxObjectShell::SetError(sal_uInt32 lErr)
/*N*/ {
/*N*/ 	if(pImp->lErr==ERRCODE_NONE)
/*N*/ 		pImp->lErr=lErr;
/*N*/ }

//-------------------------------------------------------------------------

/*N*/ sal_uInt32 SfxObjectShell::GetError() const
/*N*/ {
/*N*/ 	return ERRCODE_TOERROR(GetErrorCode());
/*N*/ }

//-------------------------------------------------------------------------

/*N*/ sal_uInt32 SfxObjectShell::GetErrorCode() const
/*N*/ {
/*N*/ 	sal_uInt32 lError=pImp->lErr;
/*N*/ 	if(!lError && GetMedium())
/*N*/ 		lError=GetMedium()->GetErrorCode();
/*N*/ 	if(!lError && HasStorage())
/*N*/ 		lError= GetStorage()->GetErrorCode();
/*N*/ 	return lError;
/*N*/ }

//-------------------------------------------------------------------------

/*N*/ void SfxObjectShell::ResetError()
/*N*/ {
/*N*/ 	pImp->lErr=0;
/*N*/ 	SfxMedium * pMed = GetMedium();
/*N*/ 	if( pMed )
/*N*/ 		pMed->ResetError();
/*N*/ 	SvStorage *pStor= HasStorage() ? GetStorage() : 0;
/*N*/ 	if( pStor )
/*N*/ 		pStor->ResetError();
/*N*/ }

//-------------------------------------------------------------------------

/*N*/ sal_Bool SfxObjectShell::IsTemplate() const
/*N*/ {
/*N*/ 	return pImp->bIsTemplate;
/*N*/ }

//-------------------------------------------------------------------------

/*N*/ void SfxObjectShell::SetTemplate(sal_Bool bIs)
/*N*/ {DBG_BF_ASSERT(0, "STRIP"); //STRIP001 
//STRIP001 	pImp->bIsTemplate=bIs;
//STRIP001 	SfxFilterMatcher aMatcher( GetFactory().GetFilterContainer() );
//STRIP001 	SfxFilterMatcherIter aIter( &aMatcher, SFX_FILTER_TEMPLATEPATH );
//STRIP001 	SfxMedium* pMed = GetMedium();
//STRIP001 	if( pMed ) pMed->SetFilter( aIter.First() );
/*N*/ }

//-------------------------------------------------------------------------

/*N*/ void SfxObjectShell::ModifyChanged()

/*	[Beschreibung]

    Diese virtuelle Methode wird aus der virtuellen Basisklasse SvPersist
    gerufen, wenn sich das Modified-Flag ge"andert hat. Diese Querverbindung
    ist notwendig, da aus einem Zweig einer virtuellen Vererbung nicht
    quer un den anderen gerufen werden kann.
*/

/*N*/ {
/*N*/ 	if ( pImp->bClosing )
/*N*/ 		// SetModified aus dem dispose des Models!
/*N*/ 		return;
/*N*/ 
/*N*/ 	{DBG_CHKTHIS(SfxObjectShell, 0);}
/*N*/ 	SfxObjectShell *pDoc;
/*N*/ 	for ( pDoc = SfxObjectShell::GetFirst(); pDoc;
/*N*/ 		  pDoc = SfxObjectShell::GetNext(*pDoc) )
/*N*/ 		if( pDoc->IsModified() )
/*N*/ 			break;
/*N*/ 	SfxApplication *pSfxApp = SFX_APP();
/*N*/ 	Timer *pTimer = pSfxApp->GetAutoSaveTimer_Impl();
/*N*/ 	if( pDoc )
/*N*/ 	{
/*N*/ 		if( !pTimer->IsActive() )
/*N*/ 			pTimer->Start();
/*N*/ 	}
/*N*/ 	else
/*N*/ 		pTimer->Stop();
/*N*/ 
/*N*/     SfxViewFrame* pViewFrame = SfxViewFrame::Current();
/*N*/     if ( pViewFrame )
/*N*/         pViewFrame->GetBindings().Invalidate( SID_SAVEDOCS );
/*N*/ 
/*N*/ 	pSfxApp->NotifyEvent( SfxEventHint( SFX_EVENT_MODIFYCHANGED, this ) );
/*N*/ }

//--------------------------------------------------------------------

/*N*/ SfxInPlaceObject* SfxObjectShell::GetInPlaceObject() const
/*N*/ {
/*N*/ 	if( !pImp->pInPlaceObj && !pImp->bSetInPlaceObj )
/*N*/ 	{
/*N*/ 		// try to cast
/*N*/ 		SvInPlaceObjectRef xSvIP( (SfxObjectShell *)this );
/*N*/ 		if ( xSvIP.Is() )
/*N*/ 			pImp->pInPlaceObj = (SfxInPlaceObject*) &xSvIP;
/*N*/ 		pImp->bSetInPlaceObj = sal_True;
/*N*/ 	}
/*N*/ 	return pImp->pInPlaceObj;
/*N*/ }

//-------------------------------------------------------------------------

/*N*/ sal_Bool SfxObjectShell::IsReadOnlyUI() const

/* 	[Beschreibung]

    Liefert sal_True, wenn das Dokument fuer die UI wie r/o behandelt werden
    soll. Dieses ist unabhaengig vom tatsaechlichen r/o, welches per
    <IsReadOnly()> erfragbar ist.
*/

/*N*/ {
/*N*/ 	return pImp->bReadOnlyUI;
/*N*/ }

//-------------------------------------------------------------------------

/*N*/ sal_Bool SfxObjectShell::IsReadOnlyMedium() const

/* 	[Beschreibung]

    Liefert sal_True, wenn das Medium r/o ist bzw. r/o geoeffnet wurde.
*/

/*N*/ {
/*N*/ 	if ( !pMedium )
/*N*/ 		return sal_True;
/*N*/ 	return pMedium->IsReadOnly();
/*N*/ }

//-------------------------------------------------------------------------

//STRIP001 void SfxObjectShell::SetReadOnlyUI( sal_Bool bReadOnly )

/* 	[Beschreibung]

    Schaltet das Dokument in einen r/o bzw. r/w Zustand ohne es neu
    zu laden und ohne die Open-Modi des Mediums zu aendern.
*/

//STRIP001 {
//STRIP001 	sal_Bool bWasRO = IsReadOnly();
//STRIP001 	pImp->bReadOnlyUI = bReadOnly;
//STRIP001 	if ( bWasRO != IsReadOnly() )
//STRIP001 	{
//STRIP001 		Broadcast( SfxSimpleHint(SFX_HINT_MODECHANGED) );
//STRIP001 		if ( pImp->pDocInfo )
//STRIP001 			pImp->pDocInfo->SetReadOnly( IsReadOnly() );
//STRIP001 	}
//STRIP001 }

//-------------------------------------------------------------------------

/*N*/ sal_Bool SfxObjectShell::IsReadOnly() const
/*N*/ {
/*N*/ 	return pImp->bReadOnlyUI || IsReadOnlyMedium();
/*N*/ }

//-------------------------------------------------------------------------

/*N*/ sal_Bool SfxObjectShell::IsInModalMode() const
/*N*/ {
/*N*/     return pImp->bModalMode || pImp->bRunningMacro;
/*N*/ }

//-------------------------------------------------------------------------

//STRIP001 sal_Bool SfxObjectShell::HasModalViews() const
//STRIP001 {
//STRIP001 	SfxViewFrame* pFrame = SfxViewFrame::GetFirst( this );
//STRIP001 	while( pFrame )
//STRIP001 	{
//STRIP001 		if ( pFrame->IsInModalMode() )
//STRIP001 			return sal_True;
//STRIP001 
//STRIP001 		pFrame = SfxViewFrame::GetNext( *pFrame, this );
//STRIP001 	}
//STRIP001 
//STRIP001 	return sal_False;
//STRIP001 }

//-------------------------------------------------------------------------

/*N*/ void SfxObjectShell::SetMacroMode_Impl( sal_Bool bModal )
/*N*/ {DBG_BF_ASSERT(0, "STRIP"); //STRIP001 
//STRIP001     if ( !pImp->bRunningMacro != !bModal )
//STRIP001 	{
//STRIP001         pImp->bRunningMacro = bModal;
//STRIP001 		Broadcast( SfxSimpleHint( SFX_HINT_MODECHANGED ) );
//STRIP001 	}
/*N*/ }

//-------------------------------------------------------------------------

//STRIP001 void SfxObjectShell::SetModalMode_Impl( sal_Bool bModal )
//STRIP001 {
//STRIP001 	// nur Broadcasten wenn modifiziert, sonst ggf. Endlosrekursion
//STRIP001 	if ( !pImp->bModalMode != !bModal )
//STRIP001 	{
//STRIP001 		// zentral mitz"ahlen
//STRIP001 		sal_uInt16 &rDocModalCount = SFX_APP()->Get_Impl()->nDocModalMode;
//STRIP001 		if ( bModal )
//STRIP001 			++rDocModalCount;
//STRIP001 		else
//STRIP001 			--rDocModalCount;
//STRIP001 
//STRIP001 		// umschalten
//STRIP001 		pImp->bModalMode = bModal;
//STRIP001 		Broadcast( SfxSimpleHint( SFX_HINT_MODECHANGED ) );
//STRIP001 	}
//STRIP001 }

//--------------------------------------------------------------------

/*?*/ Size SfxObjectShell::GetFirstPageSize()
/*?*/ {
/*?*/ 	Size aRet;
/*?*/ 	SfxInPlaceObject *pIpObj = GetInPlaceObject();
/*?*/ 	if ( pIpObj )
/*?*/ 		aRet = pIpObj->GetVisArea(ASPECT_THUMBNAIL).GetSize();
/*?*/ 	return aRet;
/*?*/ }


//--------------------------------------------------------------------

/*N*/ IndexBitSet& SfxObjectShell::GetNoSet_Impl()
/*N*/ {
/*N*/ 	return pImp->aBitSet;
/*N*/ }

//--------------------------------------------------------------------
// changes the title of the document

/*N*/ void SfxObjectShell::SetTitle
/*N*/ (
/*N*/ 	const String& rTitle		// der neue Titel des Dokuments
/*N*/ )

/*	[Beschreibung]

    Mit dieser Methode kann der Titel des Dokuments gesetzt werden.
    Dieser entspricht initial dem kompletten Dateinamen. Ein Setzen
    des Titels wirkt jedoch nicht zu"uck auf den Dateinamen; er wird
    jedoch in den Caption-Bars der MDI-Fenster angezeigt.
*/

/*N*/ {
/*N*/ 	DBG_CHKTHIS(SfxObjectShell, 0);
/*N*/ 
/*N*/ 	// nix zu tun?
/*N*/ 	if ( ( HasName() && pImp->aTitle == rTitle ) ||
/*N*/ 		 ( !HasName() && GetTitle() == rTitle ) )
/*N*/ 		return;
/*N*/ 
/*N*/ 	SfxApplication *pSfxApp = SFX_APP();
/*N*/ #if 0
/*N*/ 	// wird 'unbenannt#' als Titel gesetzt
/*N*/ 	String aNoName(SfxResId(STR_NONAME));
/*N*/ 	if ( rTitle.Match(aNoName) <= aNoName.Len() )
/*N*/ 	{
/*N*/ 		// er ist es selbst => ignorieren
/*N*/ 		pSfxApp->ReleaseIndex(pImp->nVisualDocumentNumber);
/*N*/ 		pImp->bIsNamedVisible=0;
/*N*/ 	}
/*N*/ #endif
/*N*/ 
/*N*/ 	// ggf. die unbenannt-Nummer freigeben
/*N*/ 	if ( pImp->bIsNamedVisible && USHRT_MAX != pImp->nVisualDocumentNumber )
/*N*/ 	{
/*?*/ 		pSfxApp->ReleaseIndex(pImp->nVisualDocumentNumber);
/*?*/ 		pImp->bIsNamedVisible = 0;
/*N*/ 	}
/*N*/ 
/*N*/ 	// Title setzen
/*N*/ 	pImp->aTitle = rTitle;
/*N*/ //  Wieso denn in der DocInfo?
/*N*/ //	GetDocInfo().SetTitle( rTitle );
/*N*/ //	FlushDocInfo();
/*N*/ 
/*N*/ 	// Benachrichtigungen
/*N*/     if ( GetMedium() )
/*N*/     {
/*N*/         SfxShell::SetName( GetTitle(SFX_TITLE_APINAME) );
/*N*/         Broadcast( SfxSimpleHint(SFX_HINT_TITLECHANGED) );
/*N*/     }
/*N*/ }

//--------------------------------------------------------------------

#if OSL_DEBUG_LEVEL > 1
/*N*/ String X(const String &rRet)
/*N*/ {
/*N*/ 	if ( !rRet.Len() )
/*N*/ 		return DEFINE_CONST_UNICODE( "-empty-" );
/*N*/ 	return rRet;
/*N*/ }
#else
#define X(ret) ret
#endif

//--------------------------------------------------------------------
/*N*/ String SfxObjectShell::GetTitle
/*N*/ (
    sal_uInt16	nMaxLength 		/*	0 (default)
                                der Titel selbst, so wie er ist

                                1 (==SFX_TITLE_FILENAME)
                                liefert den logischen Dateinamen ohne Pfad
                                (unter WNT je nach Systemeinstellung ohne
                                Extension)

                                2 (==SFX_TITLE_FULLNAME)
                                liefert den mit komplettem logischen Dateinamen
                                mit Pfad (remote => ::com::sun::star::util::URL)

                                3 (==SFX_TITLE_APINAME)
                                liefert den logischen Dateinamen ohne Pfad
                                und Extension

                                4 (==SFX_TITLE_DETECT)
                                liefert den kompletten Titel, falls noch
                                nicht gesetzt wird aber aus DocInfo oder
                                dem Namen des Medium erzeugt

                                5 (==SFX_TITLE_CAPTION)
                                liefert den Titel so, wie MB ihn heute in
                                der CaptionBar anzeigen m"ochte

                                6 (==SFX_TITLE_PICKLIST)
                                liefert den Titel so, wie MB ihn heute in
                                der PickList anzeigen m"ochte

                                7 (==SFX_TITLE_HISTORY)
                                liefert den Titel so, wie MB ihn heute in
                                der History anzeigen m"ochte

                                10 bis USHRT_MAX
                                liefert maximal 'nMaxLength' Zeichen vom logischen
                                Dateinamen inkl. Pfad (remote => ::com::sun::star::util::URL)
                                */
/*N*/ ) const

/*	[Beschreibung]

    Liefert den Titel bzw. logischen Dateinamen des Dokuments, je nach
    'nMaxLength'.

    Falls der Dateiname mit Pfad verwendet wird, wird die Namensk"urzung durch
    Ersetzung eines oder mehrerer Directory-Namen durch "..." durchgef"uhrt,
    URLs werden z.Zt. immer komplett geliefert.
*/

/*N*/ {
/*N*/ //    if ( GetCreateMode() == SFX_CREATE_MODE_EMBEDDED )
/*N*/ //        return String();
/*N*/ SfxMedium *pMed = GetMedium();
/*N*/ 
/*N*/ 	// Titel erzeugen?
/*N*/ 	if ( SFX_TITLE_DETECT == nMaxLength && !pImp->aTitle.Len() )
/*N*/ 	{
/*N*/ 		static sal_Bool bRecur = sal_False;
/*N*/ 		if ( bRecur )
/*N*/ 			return DEFINE_CONST_UNICODE( "-not available-" );
/*N*/ 		bRecur = sal_True;
/*N*/ 
/*N*/ 		String aTitle;
/*N*/ 		SfxObjectShell *pThis = (SfxObjectShell*) this;
/*N*/ 
/*N*/ 		if ( pMed )
/*N*/ 		{
/*N*/ 			SFX_ITEMSET_ARG( pMed->GetItemSet(), pNameItem, SfxStringItem, SID_DOCINFO_TITLE, sal_False );
/*N*/ 			if ( pNameItem )
/*N*/ 				aTitle = pNameItem->GetValue();
/*N*/ 		}
/*N*/ 
/*N*/ 		if ( !aTitle.Len() )
/*N*/ 		{
/*N*/ 			// evtl. ist Titel aus DocInfo verwendbar
/*N*/ 			aTitle = pThis->GetDocInfo().GetTitle();
/*N*/ 			aTitle.EraseLeadingChars();
/*N*/ 			aTitle.EraseTrailingChars();
/*N*/ 
/*N*/ 			if ( !aTitle.Len() )
/*N*/ 				// sonst wie SFX_TITLE_FILENAME
/*N*/ 				aTitle = GetTitle( SFX_TITLE_FILENAME );
/*N*/ 		}
/*N*/ 
/*N*/ 		pThis->SetTitle( aTitle );
/*N*/ 		bRecur = sal_False;
/*N*/ 		return X(aTitle);
/*N*/ 	}
/*N*/ 	else if (SFX_TITLE_APINAME == nMaxLength )
/*N*/ 		return X(GetAPIName());
/*N*/ 
/*N*/ 	// Sonderfall Vorlagen:
/*N*/ 	if( IsTemplate() && pImp->aTitle.Len() &&
/*N*/ 		 ( nMaxLength == SFX_TITLE_CAPTION || nMaxLength == SFX_TITLE_PICKLIST ) )
/*N*/ 		return X(pImp->aTitle);
/*N*/ 
/*N*/ 	// Picklist/Caption wird gemappt
/*N*/ 	if ( pMed && ( nMaxLength == SFX_TITLE_CAPTION || nMaxLength == SFX_TITLE_PICKLIST ) )
/*N*/ 	{
/*N*/ 		// Wenn ein spezieller Titel beim "Offnen mitgegebent wurde;
/*N*/ 		// wichtig bei URLs, die INET_PROT_FILE verwenden, denn bei denen
/*N*/ 		// wird der gesetzte Titel nicht beachtet.
/*N*/ 		// (s.u., Auswertung von aTitleMap_Impl)
/*N*/ 		SFX_ITEMSET_ARG( pMed->GetItemSet(), pNameItem, SfxStringItem, SID_DOCINFO_TITLE, sal_False );
/*N*/ 		if ( pNameItem )
/*N*/ 			return X( pNameItem->GetValue() );
/*N*/ 	}
/*N*/ 
/*N*/ 	// noch unbenannt?
/*N*/ 	DBG_ASSERT( !HasName() || pMed, "HasName() aber kein Medium?!?" );
/*N*/ 	if ( !HasName() || !pMed )
/*N*/ 	{
/*N*/ 		// schon Titel gesezt?
/*N*/ 		if ( pImp->aTitle.Len() )
/*N*/ 			return X(pImp->aTitle);
/*N*/ 
/*N*/ 		// mu\s es durchnumeriert werden?
/*N*/ 		String aNoName( SfxResId( STR_NONAME ) );
/*N*/ 		if ( pImp->bIsNamedVisible )
/*N*/ 			// Nummer hintenanh"angen
/*N*/ 			aNoName += String::CreateFromInt32( pImp->nVisualDocumentNumber );
/*N*/ 
/*N*/ 		// Dokument hei\st vorerst 'unbenannt#'
/*N*/ 		return X(aNoName);
/*N*/ 	}
/*N*/ 
/*N*/     const INetURLObject& aURL = INetURLObject( pMed->GetName() );
/*N*/ 	if ( nMaxLength >= SFX_TITLE_CAPTION && nMaxLength <= SFX_TITLE_HISTORY )
/*N*/ 	{
/*N*/ 		sal_uInt16 nRemote;
/*N*/ 		if( !pMed || aURL.GetProtocol() == INET_PROT_FILE )
/*N*/ 			nRemote = 0;
/*N*/ 		else
/*N*/ 			nRemote = 1;
/*N*/ 		nMaxLength = aTitleMap_Impl[nMaxLength-SFX_TITLE_CAPTION][nRemote];
/*N*/ 	}
/*N*/ 
/*N*/ 	// lokale Datei?
/*N*/ 	if ( aURL.GetProtocol() == INET_PROT_FILE )
/*N*/ 	{
/*N*/         String aName( aURL.HasMark() ? INetURLObject( aURL.GetURLNoMark() ).PathToFileName() : aURL.PathToFileName() );
/*N*/ 
/*N*/ //		if ( nMaxLength > SFX_TITLE_MAXLEN )
/*N*/ //			return X( DirEntry( aName ).GetFull( FSYS_STYLE_HOST, sal_False, nMaxLength ) );
/*N*/ //		else
/*N*/ 		if ( nMaxLength == SFX_TITLE_FULLNAME )
/*N*/ 			return X( aName );
/*N*/ 
/*N*/ 		if ( !pImp->aTitle.Len() )
/*N*/ 		{
/*N*/ 			if ( nMaxLength == SFX_TITLE_FILENAME )
/*N*/                 return X( aURL.getName( INetURLObject::LAST_SEGMENT,
/*N*/ 										true, INetURLObject::DECODE_WITH_CHARSET ) );
/*N*/ 
/*N*/ 			// sonst Titel aus Dateiname generieren
/*N*/             pImp->aTitle = aURL.getBase( INetURLObject::LAST_SEGMENT,
/*N*/ 										 true, INetURLObject::DECODE_WITH_CHARSET );
/*N*/ 		}
/*N*/ 	}
/*N*/ 	else
/*N*/ 	{
/*N*/ 		// ::com::sun::star::util::URL-Versionen
/*N*/ 		if ( nMaxLength >= SFX_TITLE_MAXLEN )
/*N*/ 		{
/*N*/             String aComplete( pMed->GetName() );
/*N*/ 			if( aComplete.Len() > nMaxLength )
/*N*/ 			{
/*N*/ 				String aRet( DEFINE_CONST_UNICODE( "..." ) );
/*N*/ 				aRet += aComplete.Copy( aComplete.Len() - nMaxLength + 3, nMaxLength - 3 );
/*N*/ 				return X( aRet );
/*N*/ 			}
/*N*/ 			else
/*N*/                 return X( pMed->GetName() );
/*N*/ 		}
/*N*/ 		else if ( nMaxLength == SFX_TITLE_FILENAME )
/*N*/ 		{
/*N*/ 			String aName( aURL.GetLastName() );
/*N*/ 			aName = INetURLObject::decode( aName, INET_HEX_ESCAPE, INetURLObject::DECODE_WITH_CHARSET );
/*N*/ 			if( !aName.Len() )
/*N*/ 				aName = aURL.GetURLNoPass();
/*N*/ 			return X(aName);
/*N*/ 		}
/*N*/ 		else if ( nMaxLength == SFX_TITLE_FULLNAME )
/*N*/ 			return X(aURL.GetMainURL( INetURLObject::DECODE_TO_IURI ));
/*N*/ 
/*N*/ 		// ggf. Titel aus Dateiname generieren
/*N*/ 		if ( !pImp->aTitle.Len() )
/*N*/ 			pImp->aTitle = aURL.GetBase();
/*N*/ 	}
/*N*/ 
/*N*/ 	// ganzer Titel
/*N*/ 	return X(pImp->aTitle);
/*N*/ }

//--------------------------------------------------------------------

/*N*/ void SfxObjectShell::InvalidateName()

/*	[Beschreibung]

    Ermittelt den Titel des Dokuments neu aus 'unbenannt', DocInfo-Titel
    bzw. Dateinamen. Wird nach Laden aus Template oder SaveAs ben"otigt.
*/

/*N*/ {
/*N*/ 	// Title neu erzeugen
/*N*/ 	pImp->aTitle.Erase();
/*N*/ //	pImp->nVisualDocumentNumber = USHRT_MAX;
/*N*/ 	GetTitle( SFX_TITLE_DETECT );
/*N*/ 	SetName( GetTitle( SFX_TITLE_APINAME ) );
/*N*/ 
/*N*/ 	// Benachrichtigungen
/*N*/ 	Broadcast( SfxSimpleHint(SFX_HINT_TITLECHANGED) );
/*N*/ }

//--------------------------------------------------------------------

/*N*/ void SfxObjectShell::SetNamedVisibility_Impl()
/*N*/ {
/*N*/ 	if ( !pImp->bIsNamedVisible )
/*N*/ 	{
/*N*/ 		// Nummer verpassen
/*N*/ 		pImp->bIsNamedVisible = sal_True;
/*N*/ 		// ggf. neue Nummer verpassen
/*N*/ 		if ( !HasName() && USHRT_MAX == pImp->nVisualDocumentNumber && !pImp->aTitle.Len() )
/*N*/ 		{
/*N*/ 			pImp->nVisualDocumentNumber = SFX_APP()->GetFreeIndex();
/*N*/ 			Broadcast( SfxSimpleHint(SFX_HINT_TITLECHANGED) );
/*N*/ 		}
/*N*/ 	}
/*N*/ 
/*N*/ 	SetName( GetTitle(SFX_TITLE_APINAME) );
/*N*/ }

/*?*/ void SfxObjectShell::SetNoName()
/*?*/ {
/*?*/     bHasName = 0;
/*?*/     bIsTmp = sal_True;
/*?*/     GetModel()->attachResource( ::rtl::OUString(), GetModel()->getArgs() );
/*?*/ }

//--------------------------------------------------------------------

/*?*/ void SfxObjectShell::MemoryError()
/*?*/ {
/*?*/ }

//--------------------------------------------------------------------

/*N*/ SfxProgress* SfxObjectShell::GetProgress() const
/*N*/ {
/*N*/ 	return pImp->pProgress;
/*N*/ }

//--------------------------------------------------------------------

/*N*/ void SfxObjectShell::SetProgress_Impl
/*N*/ (
/*N*/ 	SfxProgress *pProgress	/*	zu startender <SfxProgress> oder 0, falls
                                der Progress zur"uckgesetzt werden soll */
/*N*/ )

/*	[Beschreibung]

    Interne Methode zum setzen oder zur"ucksetzen des Progress-Modes
    f"ur diese SfxObjectShell.
*/

/*N*/ {
/*N*/ 	DBG_ASSERT( ( !pImp->pProgress && pProgress ) ||
/*N*/ 				( pImp->pProgress && !pProgress ),
/*N*/ 				"Progress activation/deacitivation mismatch" );
/*N*/ 	pImp->pProgress = pProgress;
/*N*/ }

//--------------------------------------------------------------------

/*N*/ void SfxObjectShell::PostActivateEvent_Impl()
/*N*/ {
/*N*/ 	SfxApplication* pSfxApp = SFX_APP();
/*N*/ 	if ( !pSfxApp->IsDowning() && !IsLoading() )
/*N*/ 	{
/*N*/ 		if (pImp->nEventId)
/*N*/ 		{
/*N*/ 			SFX_ITEMSET_ARG( pMedium->GetItemSet(), pSalvageItem,
/*N*/ 							 SfxStringItem, SID_DOC_SALVAGE, sal_False );
/*N*/ 			sal_uInt16 nId = pImp->nEventId;
/*N*/ 			pImp->nEventId = 0;
/*N*/ 			if ( !pSalvageItem )
/*N*/                 pSfxApp->NotifyEvent(SfxEventHint( nId, this ), sal_False);
/*N*/ 		}
/*N*/ 
/*N*/ 		if ( GetFrame() )
/*N*/ 			pSfxApp->NotifyEvent(SfxEventHint(SFX_EVENT_ACTIVATEDOC, this), sal_False);
/*N*/ 	}
/*N*/ }

//--------------------------------------------------------------------

/* Stampit #111050# allow writer to set this event id here hardly!
   Please replace ith by a better solution! */
/*?*/ void SfxObjectShell::Stamp_SetActivateEvent(sal_uInt16 nId )
/*?*/ {{DBG_BF_ASSERT(0, "STRIP");}//STRIP001 
//STRIP001     if ( GetFactory().GetFlags() & SFXOBJECTSHELL_HASOPENDOC )
//STRIP001         pImp->nEventId = nId;
/*?*/ }

//--------------------------------------------------------------------

/*N*/ void SfxObjectShell::SetActivateEvent_Impl(sal_uInt16 nId )
/*N*/ {
/*N*/ 	if ( GetFactory().GetFlags() & SFXOBJECTSHELL_HASOPENDOC )
/*N*/ 		pImp->nEventId = nId;
/*N*/ }

//--------------------------------------------------------------------

/*N*/ void SfxObjectShell::RegisterTransfer( SfxMedium& rMedium )
/*  [Beschreibung ]
    Alle Medien, die aufgesetzt werden, um Teile eines Dokumentes zu
    laden, muessen an der zugehoerigen SfxObjectShell angemeldet
    werden. So kann dokumentweise abgebrochen werden.  */
/*N*/ {
/*N*/ 	rMedium.SetCancelManager_Impl( GetMedium()->GetCancelManager_Impl() );
/*N*/ 	if( IsReloading() )
/*?*/ 		rMedium.SetUsesCache( sal_False );
/*N*/ 	rMedium.SetReferer( GetMedium()->GetName() );
/*N*/ }

//-------------------------------------------------------------------------

/*N*/ void SfxObjectShell::PrepareReload( )
/*  [Beschreibung ]
    Wird vor dem Reload gerufen und gibt die Moeglichkeit,
    etwaige Caches zu leeren. */
/*N*/ {
/*N*/ }

//-------------------------------------------------------------------------

/*N*/ sal_Bool SfxObjectShell::IsReloading() const
/*  [Beschreibung ]
    Wird beim Aufsetzen neuer Downloads abgefragt, um gegebenenfalls
    am SfxMedium SetUsesCache( sal_False ) zu rufen. */

/*N*/ {
/*N*/ 	return !GetMedium()->UsesCache();
/*N*/ }

//-------------------------------------------------------------------------

/*?*/ void SfxObjectShell::LockAutoLoad( sal_Bool bLock )

/* 	Verhindert ein evtl. eintreffendes AutoLoad. Wird auch vor AutoLoad
    eines umgebenden FrameSet beruecksichtigt.
*/

/*?*/ {
/*?*/ 	if ( bLock )
/*?*/ 		++pImp->nAutoLoadLocks;
/*?*/ 	else
/*?*/ 		--pImp->nAutoLoadLocks;
/*?*/ }

//-------------------------------------------------------------------------

// kann nach frame.cxx gemoved werden, wenn 358+36x-Stand gemerged sind

/*?*/ sal_Bool SfxFrame::IsAutoLoadLocked_Impl() const
/*?*/ {
/*?*/ 	// sein einges Doc gelockt?
/*?*/ 	const SfxObjectShell* pObjSh = GetCurrentDocument();
/*?*/ 	if ( !pObjSh || !pObjSh->IsAutoLoadLocked() )
/*?*/ 		return sal_False;
/*?*/ 
/*?*/ 	// seine Childs gelockt?
/*?*/ 	for ( sal_uInt16 n = GetChildFrameCount(); n--; )
/*?*/ 		{DBG_BF_ASSERT(0, "STRIP");} //STRIP001 if ( !GetChildFrame(n)->IsAutoLoadLocked_Impl() )
/*?*/ 			return sal_False;
/*?*/ 
/*?*/ 	// sonst ist AutoLoad erlaubt
/*?*/ 	return sal_True;
/*?*/ }

//-------------------------------------------------------------------------

/*?*/ sal_Bool SfxObjectShell::IsAutoLoadLocked() const

/* 	Liefert, ob ein eintreffendes AutoLoad ausgefuehrt werden darf. Wird auch
    vor AutoLoad eines umgebenden FrameSet beruecksichtigt.
*/

/*?*/ {
/*?*/ 	return !IsReadOnly() || pImp->nAutoLoadLocks > 0;
/*?*/ }

//-------------------------------------------------------------------------

/*N*/ void SfxObjectShell::SetAutoLoad(
/*N*/ 	const INetURLObject& rUrl, sal_uInt32 nTime, sal_Bool bReload )
/*  [Beschreibung ]
    Hiermit wird automatisches Laden der Url rUrl nTime
    Millisekunden nach Aufruf von FinishedLoading angefordert. bReload
    bestimmt, ob das Dokument aus dem Cache geladen werden soll oder
    nicht.  */
/*N*/ {
/*N*/ 	if ( pImp->pReloadTimer )
/*?*/ 		DELETEZ(pImp->pReloadTimer);
/*N*/ 	if ( bReload )
/*N*/ 	{
/*N*/ 		pImp->pReloadTimer = new AutoReloadTimer_Impl(
/*N*/ 								rUrl.GetMainURL( INetURLObject::DECODE_TO_IURI ),
/*N*/ 								nTime, bReload, this );
/*?*/ 		pImp->pReloadTimer->Start();
/*N*/ 	}
/*N*/ }

/*N*/ void SfxObjectShell::FinishedLoading( sal_uInt16 nFlags )
/*N*/ {
/*N*/ 	sal_Bool bSetModifiedTRUE = sal_False;
/*N*/ 	if( ( nFlags & SFX_LOADED_MAINDOCUMENT ) &&
/*N*/ 		!(pImp->nLoadedFlags & SFX_LOADED_MAINDOCUMENT ))
/*N*/ 	{
/*N*/ 		((SfxHeaderAttributes_Impl*)GetHeaderAttributes())->SetAttributes();
/*N*/ 		pImp->bImportDone = sal_True;
/*N*/ 		const SfxFilter* pFilter = GetMedium()->GetFilter();
/*N*/ 		if( !IsAbortingImport() )
/*N*/ 		{
//            if( pFilter && !pFilter->UsesStorage() && !(GetMedium()->GetOpenMode() & STREAM_WRITE ) )
//                GetMedium()->Close();
/*N*/ 			PositionView_Impl();
/*N*/ 		}
        // Salvage
/*N*/ 		SFX_ITEMSET_ARG( pMedium->GetItemSet(), pSalvageItem,
/*N*/ 						 SfxStringItem, SID_DOC_SALVAGE, sal_False );
/*N*/ 		if ( pSalvageItem )
/*N*/ 			bSetModifiedTRUE = sal_True;
/*N*/ 	}
/*N*/ 
/*N*/ 	if( ( nFlags & SFX_LOADED_IMAGES ) &&
/*N*/ 		!(pImp->nLoadedFlags & SFX_LOADED_IMAGES ) )
/*N*/ 	{
/*N*/ 		SfxDocumentInfo& rInfo = GetDocInfo();
/*N*/ 		SetAutoLoad( rInfo.GetReloadURL(), rInfo.GetReloadDelay() * 1000,
/*N*/ 					 rInfo.IsReloadEnabled() );
/*N*/ 		if( !bSetModifiedTRUE && IsEnableSetModified() )
/*?*/ 			SetModified( sal_False );
/*N*/ 		Invalidate( SID_SAVEASDOC );
/*N*/ 		SfxFrame* pFrame = GetMedium()->GetLoadTargetFrame();
/*N*/ 		if( pFrame ) pFrame->SetLoadCancelable_Impl( 0 );
/*N*/ 	}
/*N*/ 
/*N*/ 	pImp->nLoadedFlags |= nFlags;
/*N*/ 
/*N*/ 	if( pImp->nLoadedFlags & SFX_LOADED_MAINDOCUMENT &&
/*N*/ 		pImp->nLoadedFlags & SFX_LOADED_IMAGES )
/*N*/ 		GetMedium()->SetUsesCache( sal_True );
/*N*/ 
/*N*/     SFX_ITEMSET_ARG( pMedium->GetItemSet(), pHiddenItem,
/*N*/                      SfxBoolItem, SID_HIDDEN, sal_False );
/*N*/     pImp->bHidden = sal_False;
/*N*/     if ( pHiddenItem )
/*N*/         pImp->bHidden = pHiddenItem->GetValue();
/*N*/ 
/*N*/ 	if ( bSetModifiedTRUE )
/*?*/ 		SetModified( sal_True );
/*N*/ 	if ( pImp->nEventId )
/*N*/ 	{
/*N*/ 		// Falls noch kein OnLoad ausgel"ost wurde, weil beim Erzeugen der ::com::sun::star::sdbcx::View der Frame nicht aktiv war,
/*N*/ 		// mu\s das jetzt nachgeholt werden, indem der Frame benachrichtigt wird.
/*N*/         Broadcast( SfxEventHint( SFX_EVENT_LOADFINISHED, this ) );
/*N*/ 
/*N*/ 		if ( pImp->bHidden )
/*N*/ 		{
/*N*/ 			sal_uInt16 nId = pImp->nEventId;
/*N*/ 			pImp->nEventId = 0;
/*N*/             SFX_APP()->NotifyEvent(SfxEventHint( nId, this ), sal_False);
/*N*/ 		}
/*N*/ 	}
/*N*/ }

//-------------------------------------------------------------------------

/*N*/ void SfxObjectShell::PositionView_Impl()
/*N*/ {
/*N*/ 	MarkData_Impl *pMark = Get_Impl()->pMarkData;
/*N*/ 	if( pMark )
/*N*/ 	{
/*?*/ 		SfxViewShell* pSh = pMark->pFrame->GetViewShell();
/*?*/ 		if( pMark->aUserData.Len() )
/*?*/ 			pSh->ReadUserData( pMark->aUserData, sal_True );
/*?*/ 		else if( pMark->aMark.Len() )
/*?*/ 			pSh->JumpToMark( pMark->aMark );
/*?*/ 		DELETEZ( Get_Impl()->pMarkData );
/*N*/ 	}
/*N*/ }

//-------------------------------------------------------------------------

/*N*/ sal_Bool SfxObjectShell::IsLoading() const
/*  [Beschreibung ]
    Wurde bereits FinishedLoading aufgerufeb? */
/*N*/ {
/*N*/ 	return !( pImp->nLoadedFlags & SFX_LOADED_MAINDOCUMENT );
/*N*/ }

//-------------------------------------------------------------------------

/*N*/ void SfxObjectShell::CancelTransfers()
/*  [Beschreibung ]
    Hier koennen Transfers gecanceled werden, die nicht mit
    RegisterTransfer registiert wurden */
/*N*/ {
/*N*/ 	GetMedium()->CancelTransfers();
/*N*/ 	if( ( pImp->nLoadedFlags & SFX_LOADED_ALL ) != SFX_LOADED_ALL )
/*N*/ 	{
/*?*/ 		AbortImport();
/*?*/ 		if( IsLoading() )
/*?*/ 			FinishedLoading( SFX_LOADED_ALL );

/*
        SfxViewFrame* pFrame = SfxViewFrame::GetFirst( this );
        while( pFrame )
        {
            pFrame->CancelTransfers();
            pFrame = SfxViewFrame::GetNext( *pFrame, this );
        }*/
/*N*/ 	}
/*N*/ }

//-------------------------------------------------------------------------

/*?*/ AutoReloadTimer_Impl::AutoReloadTimer_Impl(
/*?*/ 	const String& rURL, sal_uInt32 nTime, sal_Bool bReloadP, SfxObjectShell* pSh )
/*?*/ 	: aUrl( rURL ), bReload( bReloadP ), pObjSh( pSh )
/*?*/ {
/*?*/ 	SetTimeout( nTime );
/*?*/ }

//-------------------------------------------------------------------------

/*?*/ void AutoReloadTimer_Impl::Timeout()
/*?*/ {
/*?*/ 	SfxViewFrame *pFrame = SfxViewFrame::GetFirst( pObjSh );
/*?*/ 
/*?*/ 	if ( pFrame )
/*?*/ 	{
/*?*/ 		// momentan nicht m"oglich/sinnvoll?
/*?*/         if ( !pObjSh->CanReload_Impl() || pObjSh->IsAutoLoadLocked() || Application::IsUICaptured() )
/*?*/ 		{
/*?*/ 			// erneuten Versuch erlauben
/*?*/ 			Start();
/*?*/ 			return;
/*?*/ 		}
/*?*/ 
/*?*/ 		SfxAllItemSet aSet( SFX_APP()->GetPool() );
/*?*/ 		aSet.Put( SfxBoolItem( SID_AUTOLOAD, sal_True ) );
/*?*/ 		if ( aUrl.Len() )
/*?*/ 			aSet.Put(  SfxStringItem( SID_FILE_NAME, aUrl ) );
/*?*/ 		SfxRequest aReq( SID_RELOAD, 0, aSet );
/*?*/ 		pObjSh->Get_Impl()->pReloadTimer = 0;
/*?*/ 		delete this;
/*?*/ 		pFrame->ExecReload_Impl( aReq );
/*?*/ 		return;
/*?*/ 	}
/*?*/ 
/*?*/ 	pObjSh->Get_Impl()->pReloadTimer = 0;
/*?*/ 	delete this;
/*?*/ }

//-------------------------------------------------------------------------

/*N*/ void SfxObjectShell::SetActualSize( const Size &rSize )
/*N*/ {
/*N*/ 	pImp->aViewSize = rSize;
/*N*/ }

//-------------------------------------------------------------------------

/*?*/ Size SfxObjectShell::GetActualSize() const
/*?*/ {
/*?*/ 	return pImp->aViewSize;
/*?*/ }

/*N*/ sal_Bool SfxObjectShell::IsInFrame() const
/*N*/ {
/*N*/ 	return pImp->bInFrame;
/*N*/ }

/*N*/ void SfxObjectShell::SetInFrame( sal_Bool bOn )
/*N*/ {
/*N*/ 	pImp->bInFrame = bOn;
/*N*/ }

/*N*/ SfxModule* SfxObjectShell::GetModule() const
/*N*/ {
/*N*/ 	return GetFactory().GetModule();
/*N*/ }

/*?*/ sal_Bool SfxObjectShell::IsBasic(
/*?*/ 	const String & rCode, SbxObject * pVCtrl )
/*?*/ {
/*?*/ 	if( !rCode.Len() ) return sal_False;
/*?*/ 	if( !pImp->bIsBasicDefault )
/*?*/ 		return sal_False;
/*?*/ 	return SfxMacroConfig::IsBasic( pVCtrl, rCode, GetBasicManager() );
/*?*/ }

/*N*/ ErrCode SfxObjectShell::CallBasic( const String& rMacro,
/*N*/ 	const String& rBasic, SbxObject* pVCtrl, SbxArray* pArgs,
/*N*/ 	SbxValue* pRet )
/*N*/ {
/*N*/     SfxApplication* pApp = SFX_APP();
/*N*/     if( pApp->GetName() != rBasic )
/*N*/     {
/*N*/         AdjustMacroMode( String() );
/*N*/ 		if( pImp->nMacroMode == MacroExecMode::NEVER_EXECUTE )
/*N*/             return ERRCODE_IO_ACCESSDENIED;
/*N*/     }
/*?*/ 
/*?*/     pApp->EnterBasicCall();
/*?*/     BasicManager *pMgr = GetBasicManager();
/*?*/     if( pApp->GetName() == rBasic )
/*?*/         pMgr = pApp->GetBasicManager();
/*?*/     ErrCode nRet = SfxMacroConfig::Call( pVCtrl, rMacro, pMgr, pArgs, pRet );
/*?*/     pApp->LeaveBasicCall();
/*?*/     return nRet;
/*N*/ }

/*?*/ ErrCode SfxObjectShell::Call( const String & rCode, sal_Bool bIsBasicReturn, SbxObject * pVCtrl )
/*?*/ {
/*?*/ 	ErrCode nErr = ERRCODE_NONE;
/*?*/ 	if ( bIsBasicReturn )
/*?*/ 		CallBasic( rCode, String(), pVCtrl );
/*?*/ 	return nErr;
/*?*/ }
} //namespace binfilter
/*?*/ extern ::com::sun::star::uno::Any sbxToUnoValue( SbxVariable* pVar );
namespace binfilter {//STRIP009
//-------------------------------------------------------------------------
/*N*/ namespace {
/*N*/ 	using namespace ::com::sun::star::uno;
/*N*/ 
/*N*/ 	//.....................................................................
/*N*/ 	static SbxArrayRef lcl_translateUno2Basic( void* _pAnySequence )
/*N*/ 	{
/*?*/ 		SbxArrayRef xReturn;
/*?*/ 		if ( _pAnySequence )
/*?*/ 		{
/*?*/ 			// in real it's a sequence of Any (by convention)
/*?*/ 			Sequence< Any >* pArguments = static_cast< Sequence< Any >* >( _pAnySequence );
/*?*/ 
/*?*/ 			// do we have arguments ?
/*?*/ 			if ( pArguments->getLength() )
/*?*/ 			{
/*?*/ 				// yep
/*?*/ 				xReturn = new SbxArray;
/*?*/ 				String sEmptyName;
/*?*/ 
/*?*/ 				// loop through the sequence
/*?*/ 				const Any* pArg		=			pArguments->getConstArray();
/*?*/ 				const Any* pArgEnd	= pArg	+	pArguments->getLength();
/*?*/ 
/*?*/ 				for ( sal_uInt16 nArgPos=1; pArg != pArgEnd; ++pArg, ++nArgPos )
/*?*/ 					// and create a Sb object for every Any
/*?*/ 					xReturn->Put( GetSbUnoObject( sEmptyName, *pArg ), nArgPos );
/*?*/ 			}
/*?*/ 		}
/*?*/ 		return xReturn;
/*N*/ 	}
    //.....................................................................
/*N*/ 	void lcl_translateBasic2Uno( const SbxVariableRef& _rBasicValue, void* _pAny )
/*N*/ 	{
/*N*/ 		if ( _pAny )
/*N*/ 			*static_cast< Any* >( _pAny ) = sbxToUnoValue( _rBasicValue );
/*N*/ 	}
/*N*/ }
//-------------------------------------------------------------------------
/*N*/ ErrCode SfxObjectShell::CallStarBasicScript( const String& _rMacroName, const String& _rLocation,
/*N*/ 	void* _pArguments, void* _pReturn )
/*N*/ {
/*?*/ 	::vos::OClearableGuard aGuard( Application::GetSolarMutex() );
/*?*/ 
/*?*/ 	// the arguments for the call
/*?*/ 	SbxArrayRef xMacroArguments = lcl_translateUno2Basic( _pArguments );
/*?*/ 
/*?*/ 	// the return value
/*?*/ 	SbxVariableRef xReturn = _pReturn ? new SbxVariable : NULL;
/*?*/ 
/*?*/ 	// the location (document or application)
/*?*/ 	String sMacroLocation;
/*?*/ 	if ( _rLocation.EqualsAscii( "application" ) )
/*?*/ 		sMacroLocation = SFX_APP()->GetName();
/*?*/ #ifdef DBG_UTIL
/*?*/ 	else
/*?*/ 		DBG_ASSERT( _rLocation.EqualsAscii( "document" ),
/*?*/ 			"SfxObjectShell::CallStarBasicScript: invalid (unknown) location!" );
/*?*/ #endif
/*?*/ 
/*?*/ 	// call the script
/*?*/ 	ErrCode eError = CallBasic( _rMacroName, sMacroLocation, NULL, xMacroArguments, xReturn );
/*?*/ 
/*?*/ 	// translate the return value
/*?*/ 	lcl_translateBasic2Uno( xReturn, _pReturn );
/*?*/ 
/*?*/ 	// outta here
/*?*/ 	return eError;
/*N*/ }

//-------------------------------------------------------------------------
/*N*/ ErrCode SfxObjectShell::CallScript(
/*N*/ 	const String & rScriptType,
/*N*/ 	const String & rCode,
/*N*/ 	::com::sun::star::uno::Reference< ::com::sun::star::uno::XInterface >  & rSource,
/*N*/ 	void *pArgs,
/*N*/ 	void *pRet
/*N*/ )
/*N*/ {
/*?*/ 	::vos::OClearableGuard aGuard( Application::GetSolarMutex() );
/*?*/ 	ErrCode nErr = ERRCODE_NONE;
/*?*/ 	if( rScriptType.EqualsAscii( "StarBasic" ) )
/*?*/ 	{
/*?*/ 		// the arguments for the call
/*?*/ 		SbxArrayRef xMacroArguments = lcl_translateUno2Basic( pArgs );
/*?*/ 
/*?*/ 		// the return value
/*?*/ 		SbxVariableRef xReturn = pRet ? new SbxVariable : NULL;
/*?*/ 
/*?*/ 		// call the script
/*?*/ 		nErr = CallBasic( rCode, String(), NULL, xMacroArguments, xReturn );
/*?*/ 
/*?*/ 		// translate the return value
/*?*/ 		lcl_translateBasic2Uno( xReturn, pRet );
/*?*/ 
/*?*/ 		// did this fail because the method was not found?
/*?*/ 		if ( nErr == ERRCODE_BASIC_PROC_UNDEFINED )
/*?*/ 		{	// yep-> look in the application BASIC module
/*?*/ 			nErr = CallBasic( rCode, SFX_APP()->GetName(), NULL, xMacroArguments, xReturn );
/*?*/ 		}
/*?*/ 	}
/*?*/ 	else if( rScriptType.EqualsAscii( "JavaScript" ) )
/*?*/ 	{
/*?*/ 		DBG_ERROR( "JavaScript not allowed" );
/*?*/ 		return 0;
/*?*/ 	}
/*?*/ 	else
/*?*/ 	{
/*?*/ 		DBG_ERROR( "StarScript not allowed" );
/*?*/ 	}
/*?*/ 	return nErr;
/*N*/ }

/*?*/ SfxFrame* SfxObjectShell::GetSmartSelf( SfxFrame* pSelf, SfxMedium& rMedium )
/*?*/ {
/*?*/ 	return pSelf;
/*?*/ }

/*N*/ SfxObjectShellFlags SfxObjectShell::GetFlags() const
/*N*/ {
/*N*/ 	if( pImp->eFlags == SFXOBJECTSHELL_UNDEFINED )
/*N*/ 		pImp->eFlags = GetFactory().GetFlags();
/*N*/ 	return pImp->eFlags;
/*N*/ }

/*?*/ void SfxObjectShell::SetFlags( SfxObjectShellFlags eFlags )
/*?*/ {
/*?*/ 	pImp->eFlags = eFlags;
/*?*/ }

/*N*/ void SfxObjectShell::SetBaseURL( const String& rURL )
/*N*/ {
/*N*/ 	pImp->aBaseURL = rURL;
/*N*/ }

/*N*/ const String& SfxObjectShell::GetBaseURL() const
/*N*/ {
/*N*/ 	if ( pImp->aBaseURL.Len() )
/*N*/ 		return pImp->aBaseURL;
/*N*/ 	else if ( pMedium->GetFilter() && ( pMedium->GetFilter()->GetFilterFlags() & SFX_FILTER_PACKED ) )
/*N*/ 		return pMedium->GetPhysicalName();
/*N*/ 	else
/*N*/ 		return pMedium->GetBaseURL();
/*N*/ }

/*?*/ String SfxObjectShell::QueryTitle( SfxTitleQuery eType ) const
/*?*/ {
/*?*/ 	String aRet;
/*?*/ 
/*?*/ 	switch( eType )
/*?*/ 	{
/*?*/ 		case SFX_TITLE_QUERY_SAVE_NAME_PROPOSAL:
/*?*/ 		{
/*?*/ 			SfxMedium* pMed = GetMedium();
/*?*/ 			const INetURLObject aObj( pMed->GetName() );
/*?*/             aRet = aObj.GetMainURL( INetURLObject::DECODE_TO_IURI );
/*?*/ 			if ( !aRet.Len() )
/*?*/ 				aRet = GetTitle( SFX_TITLE_CAPTION );
/*?*/ 			break;
/*?*/ 		}
/*?*/ 	}
/*?*/ 	return aRet;
/*?*/ }

/*N*/ void SfxHeaderAttributes_Impl::SetAttributes()
/*N*/ {
/*N*/ 	bAlert = sal_True;
/*N*/ 	SvKeyValue aPair;
/*N*/ 	for( sal_Bool bCont = xIter->GetFirst( aPair ); bCont;
/*N*/ 		 bCont = xIter->GetNext( aPair ) )
/*N*/ 		SetAttribute( aPair );
/*N*/ }

/*?*/ void SfxHeaderAttributes_Impl::SetAttribute( const SvKeyValue& rKV )
/*?*/ {
/*?*/ 	String aValue = rKV.GetValue();
/*?*/ 	if( rKV.GetKey().CompareIgnoreCaseToAscii( "refresh" ) == COMPARE_EQUAL && rKV.GetValue().Len() )
/*?*/ 	{
/*?*/ 		sal_uInt32 nTime = aValue.GetToken(  0, ';' ).ToInt32() ;
/*?*/ 		String aURL = aValue.GetToken( 1, ';' );
/*?*/ 		aURL.EraseTrailingChars().EraseLeadingChars();
/*?*/ 		SfxDocumentInfo& rInfo = pDoc->GetDocInfo();
/*?*/ 		if( aURL.Copy(0, 4).CompareIgnoreCaseToAscii( "url=" ) == COMPARE_EQUAL )
/*?*/ 		{
/*?*/ 			INetURLObject aObj;
/*?*/ 			INetURLObject( pDoc->GetMedium()->GetName() ).GetNewAbsURL( aURL.Copy( 4 ), &aObj );
/*?*/ 			rInfo.SetReloadURL( aObj.GetMainURL( INetURLObject::NO_DECODE ) );
/*?*/ 		}
/*?*/ 		rInfo.EnableReload( sal_True );
/*?*/ 		rInfo.SetReloadDelay( nTime );
/*?*/ 		pDoc->FlushDocInfo();
/*?*/ 	}
/*?*/ 	else if( rKV.GetKey().CompareIgnoreCaseToAscii( "expires" ) == COMPARE_EQUAL )
/*?*/ 	{
/*?*/ 		DateTime aDateTime;
/*?*/ 		if( INetRFC822Message::ParseDateField( rKV.GetValue(), aDateTime ) )
/*?*/ 		{DBG_BF_ASSERT(0, "STRIP"); //STRIP001 
//STRIP001 /*?*/ 			aDateTime.ConvertToLocalTime();
//STRIP001 /*?*/ 			pDoc->GetMedium()->SetExpired_Impl( aDateTime );
/*?*/ 		}
/*?*/ 		else
/*?*/ 		{
/*?*/ //			DBG_ERROR( "Schlechtes ::com::sun::star::util::DateTime fuer Expired" );
/*?*/ 			DBG_BF_ASSERT(0, "STRIP"); //STRIP001 pDoc->GetMedium()->SetExpired_Impl( Date( 1, 1, 1970 ) );
/*?*/ 		}
/*?*/ 	}
/*?*/ 	else if( rKV.GetKey().CompareIgnoreCaseToAscii( "content-type" ) == COMPARE_EQUAL )
/*?*/ 	{
/*?*/ 		::rtl::OString sContent = ::rtl::OUStringToOString( aValue, RTL_TEXTENCODING_ASCII_US );
/*?*/ 		ByteString sType, sSubType;
/*?*/ 		INetContentTypeParameterList aParameters;
/*?*/ 
/*?*/ 		if( INetContentTypes::parse( sContent, sType, sSubType, &aParameters ) )
/*?*/ 		{
/*?*/ 			const INetContentTypeParameter * pCharset = aParameters.find("charset");
/*?*/ 			if (pCharset != 0)
/*?*/ 				{DBG_BF_ASSERT(0, "STRIP");}//STRIP001 pDoc->GetMedium()->SetCharset( pCharset->m_sValue );
/*?*/ 		}
/*?*/ 	}
/*?*/ }

/*?*/ void SfxHeaderAttributes_Impl::Append( const SvKeyValue& rKV )
/*?*/ {
/*?*/ 	xIter->Append( rKV );
/*?*/ 	if( bAlert ) SetAttribute( rKV );
/*?*/ }

/*N*/ SvKeyValueIterator* SfxObjectShell::GetHeaderAttributes()
/*N*/ {
/*N*/ 	if( !pImp->xHeaderAttributes.Is() )
/*N*/ 	{
/*N*/ 		DBG_ASSERT( pMedium, "Kein Medium" );
/*N*/ 		pImp->xHeaderAttributes = new SfxHeaderAttributes_Impl( this );
/*N*/ 	}
/*N*/ 	return ( SvKeyValueIterator*) &pImp->xHeaderAttributes;
/*N*/ }

/*?*/ void SfxObjectShell::ClearHeaderAttributesForSourceViewHack()
/*?*/ {
/*?*/ 	((SfxHeaderAttributes_Impl*)GetHeaderAttributes())
/*?*/ 		->ClearForSourceView();
/*?*/ }


/*?*/ void SfxObjectShell::SetHeaderAttributesForSourceViewHack()
/*?*/ {
/*?*/ 	((SfxHeaderAttributes_Impl*)GetHeaderAttributes())
/*?*/ 		->SetAttributes();
/*?*/ }

/*?*/ void SfxObjectShell::StartLoading_Impl()
/*?*/ {
/*?*/ 	pImp->nLoadedFlags = 0;
/*?*/ }

/*N*/ sal_Bool SfxObjectShell::IsPreview() const
/*N*/ {
/*N*/ 	if ( !pMedium )
/*?*/ 		return sal_False;
/*N*/ 
/*N*/ 	sal_Bool bPreview = sal_False;
/*N*/ 	SFX_ITEMSET_ARG( pMedium->GetItemSet(), pFlags, SfxStringItem, SID_OPTIONS, sal_False);
/*N*/ 	if ( pFlags )
/*N*/ 	{
/*?*/ 		// Werte auf einzelne Items verteilen
/*?*/ 		String aFileFlags = pFlags->GetValue();
/*?*/ 		aFileFlags.ToUpperAscii();
/*?*/ 		if ( STRING_NOTFOUND != aFileFlags.Search( 'B' ) )
/*?*/ 			bPreview = sal_True;
/*?*/ 	}
/*N*/ 
/*N*/ 	if ( !bPreview )
/*N*/ 	{
/*N*/ 		SFX_ITEMSET_ARG( pMedium->GetItemSet(), pItem, SfxBoolItem, SID_PREVIEW, sal_False);
/*N*/ 		if ( pItem )
/*?*/ 			bPreview = pItem->GetValue();
/*N*/ 	}
/*N*/ 
/*N*/ 	return bPreview;
/*N*/ }

/*?*/ sal_Bool SfxObjectShell::IsSecure()
/*?*/ {
/*?*/ 	// Wenn globale Warnung an ist, nach Secure-Referer-Liste gehen
/*?*/ 	String aReferer = GetMedium()->GetName();
/*?*/ 	if ( !aReferer.Len() )
/*?*/ 	{
/*?*/ 		// bei neuen Dokumenten das Template als Referer nehmen
/*?*/ 		String aTempl( GetDocInfo().GetTemplateFileName() );
/*?*/ 		if ( aTempl.Len() )
/*?*/             aReferer = INetURLObject( aTempl ).GetMainURL( INetURLObject::NO_DECODE );
/*?*/ 	}
/*?*/ 
/*?*/ 	INetURLObject aURL( "macro:" );
/*?*/     if ( !aReferer.Len() )
/*?*/         // empty new or embedded document
/*?*/         return sal_True;
/*?*/ 
/*?*/ 		SvtSecurityOptions aOpt;
/*?*/ 
/*?*/ 	if( aOpt.GetBasicMode() == eALWAYS_EXECUTE )
/*?*/     	return sal_True;
/*?*/ 
/*?*/ 	if( aOpt.GetBasicMode() == eNEVER_EXECUTE )
/*?*/     	return sal_False;
/*?*/ 
/*?*/ 	if ( aOpt.IsSecureURL( aURL.GetMainURL( INetURLObject::NO_DECODE ), aReferer ) )
/*?*/     //if ( SvtSecurityOptions().IsSecureURL( aURL.GetMainURL( INetURLObject::NO_DECODE ), aReferer ) )
/*?*/ 	{
/*?*/         if ( GetMedium()->GetContent().is() )
/*?*/         {
/*?*/             Any aAny( ::utl::UCBContentHelper::GetProperty( aURL.GetMainURL( INetURLObject::NO_DECODE ), String( RTL_CONSTASCII_USTRINGPARAM("IsProtected")) ) );
/*?*/             sal_Bool bIsProtected = FALSE;
/*?*/             if ( ( aAny >>= bIsProtected ) && bIsProtected )
/*?*/                 return sal_False;
/*?*/             else
/*?*/                 return sal_True;
/*?*/ 		}
/*?*/ 		else
/*?*/ 			return sal_True;
/*?*/ 	}
/*?*/ 	else
/*?*/ 		return sal_False;
/*?*/ }

/*N*/ void SfxObjectShell::SetWaitCursor( BOOL bSet ) const
/*N*/ {
/*N*/     for( SfxViewFrame* pFrame = SfxViewFrame::GetFirst( this ); pFrame; pFrame = SfxViewFrame::GetNext( *pFrame, this ) )
/*N*/     {
/*N*/         if ( bSet )
/*N*/             pFrame->GetFrame()->GetWindow().EnterWait();
/*N*/         else
/*N*/             pFrame->GetFrame()->GetWindow().LeaveWait();
/*N*/     }
/*N*/ }

/*N*/ String SfxObjectShell::GetAPIName() const
/*N*/ {
/*N*/ 	INetURLObject aURL( GetMedium()->GetName() );
/*N*/     String aName( aURL.GetBase() );
/*N*/     if( !aName.Len() )
/*N*/         aName = aURL.GetURLNoPass();
/*N*/     if ( !aName.Len() )
/*N*/         aName = GetTitle( SFX_TITLE_DETECT );
/*N*/     return aName;
/*N*/ }

/*N*/ void SfxObjectShell::Invalidate( USHORT nId )
/*N*/ {
/*N*/     for( SfxViewFrame* pFrame = SfxViewFrame::GetFirst( this ); pFrame; pFrame = SfxViewFrame::GetNext( *pFrame, this ) )
/*?*/         Invalidate_Impl( pFrame->GetBindings(), nId );
/*N*/ }

// nMacroMode == -1 : uninitialized
// other values as in /com/sun/star/document/MacroExecMode.hxx

/*N*/ void SfxObjectShell::AdjustMacroMode( const String& rScriptType )
/*N*/ {
/*N*/ 	if( pImp->nMacroMode < 0 )
/*N*/ 	{
/*N*/ 		SFX_ITEMSET_ARG( pMedium->GetItemSet(), pMacroModeItem, SfxUInt16Item, SID_MACROEXECMODE, sal_False);
/*N*/ 		pImp->nMacroMode = pMacroModeItem ? pMacroModeItem->GetValue() : MacroExecMode::NEVER_EXECUTE;
/*N*/ 	}

    /*
     * take place only in case of api mode
     * that is now uses NEVER_EXECUTE by default
    if ( IsPreview() || eCreateMode != SFX_CREATE_MODE_STANDARD )
    {
        // no execution, no warnings
        pImp->nMacroMode = eNEVER_EXECUTE;
        return;
    }
    */

/*N*/ 	if( pImp->nMacroMode != MacroExecMode::NEVER_EXECUTE
/*N*/ 	 || pImp->nMacroMode != MacroExecMode::ALWAYS_EXECUTE_NO_WARN )
/*N*/ 	{
/*N*/     	SvtSecurityOptions aOpt;
/*N*/ 		sal_Int16 nAutoConformation = 0;
/*N*/ 
/*N*/         // get setting from configuration
/*N*/     	if ( pImp->nMacroMode == MacroExecMode::USE_CONFIG )
/*N*/ 		{
/*?*/         	pImp->nMacroMode = aOpt.GetBasicMode();
/*N*/ 		}
/*N*/ 		else if ( pImp->nMacroMode == MacroExecMode::USE_CONFIG_REJECT_CONFIRMATION )
/*N*/ 		{
/*?*/ 			nAutoConformation = -1;
/*?*/         	pImp->nMacroMode = aOpt.GetBasicMode();
/*N*/ 		}
/*N*/ 		else if ( pImp->nMacroMode == MacroExecMode::USE_CONFIG_APPROVE_CONFIRMATION )
/*N*/ 		{
/*?*/ 			nAutoConformation = 1;
/*?*/         	pImp->nMacroMode = aOpt.GetBasicMode();
/*N*/ 		}
/*N*/ 
/*N*/ 		DBG_ASSERT( pImp->nMacroMode != MacroExecMode::USE_CONFIG
/*N*/ 				 && pImp->nMacroMode != MacroExecMode::USE_CONFIG_REJECT_CONFIRMATION
/*N*/ 				 && pImp->nMacroMode != MacroExecMode::USE_CONFIG_APPROVE_CONFIRMATION,
/*N*/ 					"Configuration should contain explicit value!\n" );
/*N*/ 
/*N*/     	if ( pImp->nMacroMode == MacroExecMode::FROM_LIST || pImp->nMacroMode == MacroExecMode::ALWAYS_EXECUTE )
/*N*/     	{
/*?*/         	// user was not asked before
/*?*/         	// ask one time and store result for all future calls
/*?*/         	sal_Bool bWarn = aOpt.IsWarningEnabled();
/*?*/         	sal_Bool bConfirm = aOpt.IsConfirmationEnabled();
/*?*/ 
/*?*/ 			// test against list of secure URLs
/*?*/ 			INetURLObject aURL( "macro:" );
/*?*/ 
/*?*/ 			// get referer from medium name
/*?*/ 			String aReferer;
/*?*/ 			aReferer = GetMedium()->GetName();
/*?*/ 			if ( !aReferer.Len() )
/*?*/ 			{
/*?*/ 			    // for documents made from a template: get the name of the template
/*?*/ 			    String aTempl( GetDocInfo().GetTemplateFileName() );
/*?*/ 			    if ( aTempl.Len() )
/*?*/ 			        aReferer = INetURLObject( aTempl ).GetMainURL( INetURLObject::NO_DECODE );
/*?*/ 			}
/*?*/ 
/*?*/ 			// no referer means OLE object or new document not from template
/*?*/ 			sal_Bool bIsSecureByList = !aReferer.Len() || aOpt.IsSecureURL( aURL.GetMainURL( INetURLObject::NO_DECODE ), aReferer );
/*?*/ 			sal_Bool bSecure = pImp->nMacroMode == eALWAYS_EXECUTE || bIsSecureByList;
/*?*/         	//sal_Bool bSecure = pImp->nMacroMode == MacroExecMode::ALWAYS_EXECUTE || IsSecure();
/*?*/ 
/*?*/         	if ( bSecure && bWarn || !bSecure && bConfirm )
/*?*/         	{
/*?*/ 				if ( !nAutoConformation )
/*?*/ 				{DBG_BF_ASSERT(0, "STRIP"); //STRIP001 
//STRIP001 /*?*/             		QueryBox aBox( GetDialogParent(), SfxResId( DLG_MACROQUERY ) );
//STRIP001 /*?*/             		aBox.SetButtonText( aBox.GetButtonId(0), String( SfxResId(BTN_OK) ) );
//STRIP001 /*?*/             		aBox.SetButtonText( aBox.GetButtonId(1), String( SfxResId(BTN_CANCEL) ) );
//STRIP001 /*?*/             		String aText = aBox.GetMessText();
//STRIP001 /*?*/             		if ( bSecure )
//STRIP001 /*?*/             		{
//STRIP001 /*?*/                 		aBox.SetFocusButton( aBox.GetButtonId(0) );
//STRIP001 /*?*/                 		aText.SearchAndReplace( String::CreateFromAscii("$(TEXT)"), String( SfxResId(FT_OK) ) );
//STRIP001 /*?*/             		}
//STRIP001 /*?*/             		else
//STRIP001 /*?*/             		{
//STRIP001 /*?*/                 		aBox.SetFocusButton( aBox.GetButtonId(1) );
//STRIP001 /*?*/                 		aText.SearchAndReplace( String::CreateFromAscii("$(TEXT)"), String( SfxResId(FT_CANCEL) ) );
//STRIP001 /*?*/             		}
//STRIP001 /*?*/ 
//STRIP001 /*?*/             		aBox.SetMessText( aText );
//STRIP001 /*?*/ 
//STRIP001 /*?*/ 					if ( !bIsSecureByList )
//STRIP001 /*?*/ 					{
//STRIP001 /*?*/ 					    INetURLObject aObj( aReferer );
//STRIP001 /*?*/ 					    if ( aObj.GetProtocol() == INET_PROT_FILE )
//STRIP001 /*?*/ 					    {
//STRIP001 /*?*/ 					        // for file URLs: possible add directory to list of secure URLs
//STRIP001 /*?*/ 					        SfxResId aResId( RID_SVXSTR_SECURITY_ADDPATH );
//STRIP001 /*?*/ 					        aObj.removeSegment();
//STRIP001 /*?*/ 					        String aText( aResId );
//STRIP001 /*?*/ 					        aText += aObj.PathToFileName();
//STRIP001 /*?*/ 					        aBox.SetCheckBoxText( aText );
//STRIP001 /*?*/ 					    }
//STRIP001 /*?*/ 					}
//STRIP001 /*?*/ 
//STRIP001 /*?*/             		bSecure = ( aBox.Execute() == RET_OK );
//STRIP001 /*?*/ 
//STRIP001 /*?*/ 					if ( aBox.GetCheckBoxState() )
//STRIP001 /*?*/ 					{
//STRIP001 /*?*/ 					    ::com::sun::star::uno::Sequence< ::rtl::OUString > aURLs = aOpt.GetSecureURLs();
//STRIP001 /*?*/ 					    sal_Int32 nLength = aURLs.getLength();
//STRIP001 /*?*/ 					    aURLs.realloc( nLength+1 );
//STRIP001 /*?*/ 					    INetURLObject aObj( aReferer );
//STRIP001 /*?*/ 					    aObj.removeSegment();
//STRIP001 /*?*/ 					    aURLs[nLength] = aObj.GetMainURL( INetURLObject::NO_DECODE );
//STRIP001 /*?*/ 					    aOpt.SetSecureURLs( aURLs );
//STRIP001 /*?*/ 					}
/*?*/ 				}
/*?*/ 				else
/*?*/ 					bSecure = ( nAutoConformation > 0 );
/*?*/         	}
/*?*/ 
/*?*/         	pImp->nMacroMode = bSecure ? MacroExecMode::ALWAYS_EXECUTE_NO_WARN : MacroExecMode::NEVER_EXECUTE;
/*N*/     	}
/*N*/ 	}
/*N*/ }

//STRIP001 Window* SfxObjectShell::GetDialogParent( SfxMedium* pLoadingMedium )
//STRIP001 {
//STRIP001     Window* pWindow = NULL;
//STRIP001 
//STRIP001     // test current view, if it contains this document
//STRIP001     SfxViewFrame* pView = SfxViewFrame::Current();
//STRIP001     if ( !pView || pView->GetObjectShell() != this )
//STRIP001         // get the first visible(!) view
//STRIP001         pView = SfxViewFrame::GetFirst( this );
//STRIP001 
//STRIP001     if ( pView )
//STRIP001         // found ViewFrame, get the frames container window
//STRIP001         pWindow = VCLUnoHelper::GetWindow( pView->GetFrame()->GetFrameInterface()->getContainerWindow() );
//STRIP001 
//STRIP001     if ( !pLoadingMedium )
//STRIP001         // if there is no loading medium, take the medium of this document
//STRIP001         pLoadingMedium = pMedium;
//STRIP001 
//STRIP001     if ( !pWindow && pLoadingMedium )
//STRIP001     {
//STRIP001         // is this document is loading currently?
//STRIP001         SfxFrame* pFrame = pLoadingMedium->GetLoadTargetFrame();
//STRIP001         if ( pFrame )
//STRIP001             // get the frame it is loaded into
//STRIP001             pWindow = VCLUnoHelper::GetWindow( pFrame->GetFrameInterface()->getContainerWindow() );
//STRIP001 
//STRIP001         if ( pWindow )
//STRIP001         {
//STRIP001             // this frame may be invisible, show it if it is allowed
//STRIP001             SFX_ITEMSET_ARG( pLoadingMedium->GetItemSet(), pHiddenItem, SfxBoolItem, SID_HIDDEN, sal_False );
//STRIP001             if ( !pHiddenItem || !pHiddenItem->GetValue() )
//STRIP001                 pWindow->Show();
//STRIP001         }
//STRIP001     }
//STRIP001 
//STRIP001     return pWindow;
//STRIP001 }

/*N*/ String SfxObjectShell::UpdateTitle( SfxMedium* pMed, USHORT nDocViewNumber )
/*N*/ {
/*N*/     // Titel des Fensters
/*N*/     String aTitle;
/*N*/     if ( pMed )
/*N*/ 	{
/*N*/ 		INetURLObject aTmp( pMed->GetName() );
/*N*/         aTitle = aTmp.getName( INetURLObject::LAST_SEGMENT, true, INetURLObject::DECODE_WITH_CHARSET );
/*N*/ 	}
/*N*/     else
/*N*/     {
/*N*/ 		pMed = GetMedium();
/*N*/         aTitle = GetTitle(SFX_TITLE_CAPTION);
/*N*/         String aName(aTitle);
/*N*/         if ( nDocViewNumber )
/*N*/         {
/*N*/             aName += ':';
/*N*/             aName += String::CreateFromInt32( nDocViewNumber );
/*N*/         }
/*N*/     }
/*N*/ 
/*N*/ 	if ( pMed )
/*N*/ 	{
/*N*/ 		SFX_ITEMSET_ARG( pMed->GetItemSet(), pRepairedDocItem, SfxBoolItem, SID_REPAIRPACKAGE, sal_False );
/*N*/ 		if ( pRepairedDocItem && pRepairedDocItem->GetValue() )
/*N*/         	aTitle += String( SfxResId(STR_REPAIREDDOCUMENT) );
/*N*/ 	}
/*N*/ 
/*N*/ 	if ( IsReadOnlyUI() || pMed && pMed->IsReadOnly() )
/*N*/         aTitle += String( SfxResId(STR_READONLY) );
/*N*/     return aTitle;
/*N*/ }

//STRIP001 void SfxObjectShell::SetCreateMode_Impl( SfxObjectCreateMode nMode )
//STRIP001 {
//STRIP001 	eCreateMode = nMode;
//STRIP001 }

}
