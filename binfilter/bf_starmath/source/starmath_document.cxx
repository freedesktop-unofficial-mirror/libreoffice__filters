/*************************************************************************
 *
 *  $RCSfile: starmath_document.cxx,v $
 *
 *  $Revision: 1.4 $
 *
 *  last change: $Author: rt $ $Date: 2004-05-05 16:40:21 $
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

#ifndef _COM_SUN_STAR_ACCESSIBILITY_ACCESSIBLEEVENTID_HPP_
#include <com/sun/star/accessibility/AccessibleEventId.hpp>
#endif

#ifndef _RTL_USTRING_HXX_
#include <rtl/ustring.hxx>
#endif
#ifndef _UCBHELPER_CONTENT_HXX
#include <ucbhelper/content.hxx>
#endif
#ifndef _SOT_FORMATS_HXX
#include <sot/formats.hxx>
#endif
#ifndef _SVSTOR_HXX //autogen
#include <so3/svstor.hxx>
#endif
#ifndef _SVTOOLS_LINGUPROPS_HXX_
#include <svtools/linguprops.hxx>
#endif
#ifndef _SVTOOLS_LINGUCFG_HXX_
#include <svtools/lingucfg.hxx>
#endif
#ifndef _SFXSMPLHINT_HXX //autogen
#include <svtools/smplhint.hxx>
#endif
#ifndef INCLUDED_SVTOOLS_PATHOPTIONS_HXX
#include <svtools/pathoptions.hxx>
#endif
#ifndef _SO_CLSIDS_HXX //autogen
#include <so3/clsids.hxx>
#endif
#ifndef _SOT_EXCHANGE_HXX //autogen
#include <sot/exchange.hxx>
#endif
#ifndef _SV_MSGBOX_HXX //autogen
#include <vcl/msgbox.hxx>
#endif

#include <vcl/mapunit.hxx>
#include <vcl/mapmod.hxx>

#ifndef COMPHELPER_ACCESSIBLE_TEXT_HELPER_HXX
#include <comphelper/accessibletexthelper.hxx>
#endif

#ifndef _SFXENUMITEM_HXX //autogen
#include <svtools/eitem.hxx>
#endif
#ifndef _SFX_WHITER_HXX //autogen
#include <svtools/whiter.hxx>
#endif
#ifndef _SFXINTITEM_HXX //autogen
#include <svtools/intitem.hxx>
#endif
#ifndef _SFXSTRITEM_HXX //autogen
#include <svtools/stritem.hxx>
#endif
#ifndef _SFXPTITEM_HXX //autogen
#include <svtools/ptitem.hxx>
#endif
#ifndef _UNDO_HXX //autogen
#include <svtools/undo.hxx>
#endif
#ifndef _SFXITEMPOOL_HXX //autogen
#include <svtools/itempool.hxx>
#endif
#ifndef SVTOOLS_URIHELPER_HXX
#include <svtools/urihelper.hxx>
#endif
#ifndef _SVTOOLS_FSTATHELPER_HXX
#include <svtools/fstathelper.hxx>
#endif
#ifndef _TRANSFER_HXX
#include <svtools/transfer.hxx>
#endif

#ifndef _SFXDISPATCH_HXX //autogen
#include <bf_sfx2/dispatch.hxx>
#endif
#ifndef _SFXDOCINF_HXX //autogen
#include <bf_sfx2/docinf.hxx>
#endif
#ifndef _SFXDOCFILE_HXX //autogen
#include <bf_sfx2/docfile.hxx>
#endif
#ifndef _SFXAPP_HXX //autogen
#include <bf_sfx2/app.hxx>
#endif
#ifndef _SFXREQUEST_HXX //autogen
#include <bf_sfx2/request.hxx>
#endif
#ifndef _SFXVIEWFRM_HXX
#include <bf_sfx2/viewfrm.hxx>
#endif
#ifndef _SFXECODE_HXX //autogen
#include <svtools/sfxecode.hxx>
#endif
#ifndef _SFX_PRINTER_HXX //autogen
#include <bf_sfx2/printer.hxx>
#endif
#ifndef _SFX_DOCFILT_HACK_HXX
#include <bf_sfx2/docfilt.hxx>
#endif
#ifndef _SFXITEMPOOL_HXX
#include <svtools/itempool.hxx>
#endif
#ifndef _MyEDITENG_HXX
#include <bf_svx/editeng.hxx>
#endif
#ifndef _EEITEM_HXX
#include <bf_svx/eeitem.hxx>
#endif
#ifndef _EDITSTAT_HXX
#include <bf_svx/editstat.hxx>
#endif
#ifndef _EEITEMID_HXX
#include <bf_svx/eeitemid.hxx>
#endif
#ifndef _SVX_FONTITEM_HXX
#include <bf_svx/fontitem.hxx>
#endif
#ifndef _SVX_FHGTITEM_HXX
#include <bf_svx/fhgtitem.hxx>
#endif
#ifndef _UNO_LINGU_HXX
#include <bf_svx/unolingu.hxx>
#endif
#ifndef _SFXSLSTITM_HXX
#include <svtools/slstitm.hxx>
#endif

#ifndef _COM_SUN_STAR_UNO_ANY_H_
#include <com/sun/star/uno/Any.h>
#endif
#ifndef _COM_SUN_STAR_LANG_LOCALE_HPP_
#include <com/sun/star/lang/Locale.hpp>
#endif

#ifndef STARMATH_HRC
#include <starmath.hrc>
#endif
#ifndef DOCUMENT_HXX
#include <document.hxx>
#endif
#ifndef UNOMODEL_HXX
#include <unomodel.hxx>
#endif
#ifndef CONFIG_HXX
#include <config.hxx>
#endif
#ifndef SYMBOL_HXX
#include <symbol.hxx>
#endif
#ifndef TOOLBOX_HXX
#include <toolbox.hxx>
#endif
#ifndef DIALOG_HXX
#include <dialog.hxx>
#endif
#ifndef ACTION_HXX
#include <action.hxx>
#endif
#ifndef VIEW_HXX
#include <view.hxx>
#endif
#ifndef UTILITY_HXX
#include <utility.hxx>
#endif
#ifndef FORMAT_HXX
#include <format.hxx>
#endif
#ifndef MATHTYPE_HXX
#include <mathtype.hxx>
#endif
#ifndef MATHML_HXX
#include <mathml.hxx>
#endif
namespace binfilter {



using namespace ::com::sun::star;
using namespace ::com::sun::star::lang;
using namespace ::com::sun::star::ucb;
using namespace ::com::sun::star::uno;
using namespace ::com::sun::star::accessibility;

#define A2OU(x)        ::rtl::OUString::createFromAscii( x )

#ifndef SO2_DECL_SVSTORAGESTREAM_DEFINED
#define SO2_DECL_SVSTORAGESTREAM_DEFINED
SO2_DECL_REF(SvStorageStream)
#endif
#ifndef SO2_DECL_SVSTORAGE_DEFINED
#define SO2_DECL_SVSTORAGE_DEFINED
SO2_DECL_REF(SvStorage)
#endif

#define DOCUMENT_BUFFER_SIZE	(USHORT)32768

static const char __FAR_DATA pStarMathDoc[] = "StarMathDocument";


/**************************************************************************/
/*
**
**	CLASS IMPLEMENTATION
**
**/

#define SmDocShell
#include "smslots.hxx"

/*N*/ TYPEINIT1( SmDocShell, SfxObjectShell );

/*N*/ SFX_IMPL_INTERFACE(SmDocShell, SfxObjectShell, SmResId(0))
/*N*/ {
//STRIP001 /*N*/ 	SFX_POPUPMENU_REGISTRATION(SmResId(RID_VIEWMENU));
//STRIP001 /*N*/ 	SFX_POPUPMENU_REGISTRATION(SmResId(RID_COMMANDMENU));
/*N*/ //	  SFX_OBJECTBAR_REGISTRATION(
/*N*/ //		  SFX_OBJECTBAR_OBJECT|SFX_VISIBILITY_STANDARD|SFX_VISIBILITY_SERVER,
/*N*/ //		  SmResId(RID_DEFAULTTOOLBOX));
/*N*/ }

#if 0
//STRIP001 SFX_IMPL_OBJECTFACTORY(SmDocShell, SFXOBJECTSHELL_STD_NORMAL, smath, SvGlobalName(BF_SO3_SM_CLASSID_50) )
//STRIP001 {
//STRIP001    SFX_SIMPLE_FILTER_REGISTRATION( C2S("StarMath 5.0"), C2S("*.smf"),
//STRIP001 						   SFX_FILTER_OWN | SFX_FILTER_IMPORT | SFX_FILTER_EXPORT,
//STRIP001 						   SOT_FORMATSTR_ID_STARMATH_50,
//STRIP001 						   C2S("SVsm0.smf"), C2S("OS2"), 0, C2S("0"), String());

//JP 13.06.00: das fehlt vwohl noch, oder??
//	SfxObjectFactory& rFactory = (SfxObjectFactory&)Factory();
//	SfxFactoryFilterContainer *pFltContainer = rFactory.GetFilterContainer( FALSE );
//	rFactory.GetFilterContainer()->SetDetectFilter( &SmDLL::DetectFilter );

   // FG: Sonst gibts keine Hilfe im Math  #38447#
//STRIP001    Factory().RegisterHelpFile (C2S("smath.svh"));
//STRIP001 }
#else
/*N*/ SFX_IMPL_OBJECTFACTORY_DLL(SmDocShell, smath, SvGlobalName(BF_SO3_SM_CLASSID), Sm);
#endif

//STRIP001 void SmDocShell::SFX_NOTIFY(SfxBroadcaster&, const TypeId&,
//STRIP001 					const SfxHint& rHint, const TypeId&)
//STRIP001 {
//STRIP001 	switch (((SfxSimpleHint&)rHint).GetId())
//STRIP001 	{
//STRIP001 		case HINT_FORMATCHANGED:
//STRIP001 			SetFormulaArranged(FALSE);
//STRIP001 			nModifyCount++; 	//! merkw�rdig...
//STRIP001 								// ohne dies wird die Grafik letztlich
//STRIP001 								// nicht geupdatet
//STRIP001 			Resize();
//STRIP001 			break;
//STRIP001 	}
//STRIP001 }

//STRIP001 void SmDocShell::LoadSymbols()
//STRIP001 {
//STRIP001     GetSymSetManager().Load();
//STRIP001 }


/*N*/ SmSymSetManager & SmDocShell::GetSymSetManager()
/*N*/ {
/*N*/ 	if (!pSymSetMgr)
/*N*/     {
/*N*/ 		pSymSetMgr = new SmSymSetManager;
/*N*/         pSymSetMgr->Load();
/*N*/     }
/*N*/ 	return *pSymSetMgr;
/*N*/ }


//STRIP001 const String &SmDocShell::GetTitle() const
//STRIP001 {
//STRIP001 	return ((SmDocShell *) this)->GetDocInfo().GetTitle();
//STRIP001 }



//STRIP001 const String &SmDocShell::GetComment() const
//STRIP001 {
//STRIP001 	return ((SmDocShell *) this)->GetDocInfo().GetComment();
//STRIP001 }



/*N*/ void SmDocShell::SetText(const String& rBuffer)
/*N*/ {
/*N*/ 	if (rBuffer != aText)
/*N*/ 	{
/*N*/ 		BOOL bIsEnabled = IsEnableSetModified();
/*N*/ 		if( bIsEnabled )
/*N*/ 			EnableSetModified( FALSE );
/*N*/ 
/*N*/ 		aText = rBuffer;
/*N*/ 		Parse();
/*N*/         //Resize();
/*N*/ 		SmViewShell *pViewSh = SmGetActiveView();
/*N*/ 		if( pViewSh )
/*N*/         {
/*N*/ 			pViewSh->GetViewFrame()->GetBindings().Invalidate(SID_TEXT);
/*N*/ 			if ( GetProtocol().IsInPlaceActive() || SFX_CREATE_MODE_EMBEDDED == GetCreateMode() )
/*N*/                 Resize();
/*N*/             else
/*N*/                 pViewSh->GetGraphicWindow().Invalidate();
/*N*/         }
/*N*/ 
/*N*/ 		if ( bIsEnabled )
/*N*/ 			EnableSetModified( bIsEnabled );
/*N*/ 		SetModified(TRUE);
/*N*/ 
        // launch accessible event if necessary
//STRIP001         SmGraphicAccessible *pAcc = pViewSh ? pViewSh->GetGraphicWindow().GetAccessible() : 0;
//STRIP001         if (pAcc)
//STRIP001         {
//STRIP001 			Any aOldValue, aNewValue;
//STRIP001 			if ( comphelper::OCommonAccessibleText::implInitTextChangedEvent( aText, rBuffer, aOldValue, aNewValue ) )
//STRIP001 			{
//STRIP001 				pAcc->LaunchEvent( AccessibleEventId::TEXT_CHANGED,
//STRIP001 						aOldValue, aNewValue );
//STRIP001 			}
//STRIP001         }
/*N*/ 	}
/*N*/ }

//STRIP001 void SmDocShell::SetFormat(SmFormat& rFormat)
//STRIP001 {
//STRIP001 	aFormat = rFormat;
//STRIP001 	SetFormulaArranged(FALSE);
//STRIP001 	SmViewShell *pViewSh = SmGetActiveView();
//STRIP001 	if (pViewSh)
//STRIP001 		pViewSh->GetViewFrame()->GetBindings().Invalidate(SID_GRAPHIC);
//STRIP001 	SetModified(TRUE);
//STRIP001 }

//STRIP001 String SmDocShell::GetAccessibleText()
//STRIP001 {
//STRIP001     if (!IsFormulaArranged())
//STRIP001         ArrangeFormula();
//STRIP001     if (0 == aAccText.Len())
//STRIP001     {
//STRIP001         DBG_ASSERT( pTree, "Tree missing" );
//STRIP001         if (pTree)
//STRIP001             pTree->GetAccessibleText( aAccText );
//STRIP001     }
//STRIP001     return aAccText;
//STRIP001 }

/*N*/ void SmDocShell::Parse()
/*N*/ {
/*N*/ 	if (pTree)
/*N*/ 		delete pTree;
/*N*/ 	pTree = aInterpreter.Parse(aText);
/*N*/ 	nModifyCount++;
/*N*/     SetFormulaArranged( FALSE );
/*N*/ }


/*N*/ void SmDocShell::ArrangeFormula()
/*N*/ {
/*N*/ 	//! Nur f�r die Dauer der Existenz dieses Objekts sind am Drucker die
/*N*/ 	//! richtigen Einstellungen garantiert.
/*N*/     SmPrinterAccess  aPrtAcc(*this);
/*N*/ //	OutputDevice	*pOutDev = aPrtAcc.GetPrinter();
/*N*/     OutputDevice* pOutDev = aPrtAcc.GetRefDev();
/*N*/ 
/*N*/ #ifndef PRODUCT
/*N*/ 	if (!pOutDev)
/*N*/ 		DBG_WARNING("Sm : kein Drucker vorhanden");
/*N*/ #endif
/*N*/ 
/*N*/ 	// falls n�tig ein anderes OutputDevice holen f�r das formatiert wird
/*N*/ 	if (!pOutDev)
/*N*/ 	{
/*N*/ 		SmViewShell *pView = SmGetActiveView();
/*N*/ 		if (pView)
/*N*/ 			pOutDev = &pView->GetGraphicWindow();
/*N*/ 		else
/*N*/         {   pOutDev = &SM_MOD1()->GetDefaultVirtualDev();
/*N*/ 			pOutDev->SetMapMode( MapMode(MAP_100TH_MM) );
/*N*/ 		}
/*N*/ 	}
/*N*/ 	DBG_ASSERT(pOutDev->GetMapMode().GetMapUnit() == MAP_100TH_MM,
/*N*/ 			   "Sm : falscher MapMode");
/*N*/ 
/*N*/ 	const SmFormat &rFormat = GetFormat();
/*N*/ 	pTree->Prepare(rFormat, *this);
/*N*/ 	pTree->Arrange(*pOutDev, rFormat);
/*N*/ 
/*N*/ 	SetFormulaArranged(TRUE);
/*N*/ 
/*N*/     // invalidate accessible text
/*N*/     aAccText = String();
/*N*/ }


/*N*/ EditEngine& SmDocShell::GetEditEngine()
/*N*/ {
/*N*/ 	if (!pEditEngine)
/*N*/ 	{
/*N*/         //!
/*N*/         //! see also SmEditWindow::DataChanged !
/*N*/         //!
/*N*/ 
/*N*/ 		pEditEngineItemPool = EditEngine::CreatePool();
/*N*/ 
/*N*/         //
/*N*/         // set fonts to be used
/*N*/         //
/*N*/         SvtLinguOptions aOpt;
/*N*/         SvtLinguConfig().GetOptions( aOpt );
/*N*/         //
/*N*/         struct FontDta {
/*N*/             INT16       nFallbackLang;
/*N*/             INT16       nLang;
/*N*/             USHORT      nFontType;
/*N*/             USHORT      nFontInfoId;
/*N*/             } aTable[3] =
/*N*/         {
/*N*/             // info to get western font to be used
/*N*/             {   LANGUAGE_ENGLISH_US,    LANGUAGE_NONE,
/*N*/                 DEFAULTFONT_SERIF,      EE_CHAR_FONTINFO },
/*N*/             // info to get CJK font to be used
/*N*/             {   LANGUAGE_JAPANESE,      LANGUAGE_NONE,
/*N*/                 DEFAULTFONT_CJK_TEXT,   EE_CHAR_FONTINFO_CJK },
/*N*/             // info to get CTL font to be used
/*N*/             {   LANGUAGE_ARABIC,        LANGUAGE_NONE,
/*N*/                 DEFAULTFONT_CTL_TEXT,   EE_CHAR_FONTINFO_CTL }
/*N*/         };
/*N*/         aTable[0].nLang = aOpt.nDefaultLanguage;
/*N*/         aTable[1].nLang = aOpt.nDefaultLanguage_CJK;
/*N*/         aTable[2].nLang = aOpt.nDefaultLanguage_CTL;
/*N*/         //
/*N*/         for (int i = 0;  i < 3;  ++i)
/*N*/         {
/*N*/             const FontDta &rFntDta = aTable[i];
/*N*/             LanguageType nLang = (LANGUAGE_NONE == rFntDta.nLang) ?
/*N*/                     rFntDta.nFallbackLang : rFntDta.nLang;
/*N*/             Font aFont = Application::GetDefaultDevice()->GetDefaultFont(
/*N*/                         rFntDta.nFontType, nLang, DEFAULTFONT_FLAGS_ONLYONE );
/*N*/             pEditEngineItemPool->SetPoolDefaultItem(
/*N*/                     SvxFontItem( aFont.GetFamily(), aFont.GetName(),
/*N*/                         aFont.GetStyleName(), aFont.GetPitch(), aFont.GetCharSet(),
/*N*/                         rFntDta.nFontInfoId ) );
/*N*/         }
/*N*/ 
/*N*/         // set font heights
/*N*/ 		SvxFontHeightItem aFontHeigt(
/*N*/ 						Application::GetDefaultDevice()->LogicToPixel(
/*N*/ 						Size( 0, 10 ), MapMode( MAP_POINT ) ).Height(), 100,
/*N*/ 						EE_CHAR_FONTHEIGHT );
/*N*/ 		pEditEngineItemPool->SetPoolDefaultItem( aFontHeigt );
/*N*/ 		aFontHeigt.SetWhich( EE_CHAR_FONTHEIGHT_CJK );
/*N*/ 		pEditEngineItemPool->SetPoolDefaultItem( aFontHeigt );
/*N*/ 		aFontHeigt.SetWhich( EE_CHAR_FONTHEIGHT_CTL );
/*N*/ 		pEditEngineItemPool->SetPoolDefaultItem( aFontHeigt );
/*N*/ 
/*N*/ 		pEditEngine = new EditEngine( pEditEngineItemPool );
/*N*/ 
/*N*/ 		pEditEngine->EnableUndo( TRUE );
/*N*/ 		pEditEngine->SetDefTab( USHORT(
/*N*/ 			Application::GetDefaultDevice()->GetTextWidth( C2S("XXXX") ) ) );
/*N*/ 
/*N*/ 		pEditEngine->SetControlWord(
/*N*/ 				(pEditEngine->GetControlWord() | EE_CNTRL_AUTOINDENTING) &
/*N*/ 				(~EE_CNTRL_UNDOATTRIBS) &
/*N*/ 				(~EE_CNTRL_PASTESPECIAL) );
/*N*/ 
/*N*/ 		pEditEngine->SetWordDelimiters( C2S(" .=+-*/(){}[];\"" ) );
/*N*/ 		pEditEngine->SetRefMapMode( MAP_PIXEL );
/*N*/ 
/*N*/ 		pEditEngine->SetPaperSize( Size( 800, 0 ) );
/*N*/ 
/*N*/ 		pEditEngine->EraseVirtualDevice();
/*N*/ 
/*N*/         // set initial text if the document already has some...
/*N*/         // (may be the case when reloading a doc)
/*N*/         String aTxt( GetText() );
/*N*/         if (aTxt.Len())
/*N*/             pEditEngine->SetText( aTxt );
/*N*/ 
/*N*/ 		pEditEngine->ClearModifyFlag();
/*N*/ 
/*N*/ 		// forces new settings to be used if the itempool was modified
/*N*/ 		// after cthe creation of the EditEngine
/*N*/ 		//pEditEngine->Clear();	//#77957 incorrect font size
/*N*/ 	}
/*N*/ 	return *pEditEngine;
/*N*/ }


//STRIP001 SfxItemPool& SmDocShell::GetEditEngineItemPool()
//STRIP001 {
//STRIP001 	if (!pEditEngineItemPool)
//STRIP001 		GetEditEngine();
//STRIP001 	DBG_ASSERT( pEditEngineItemPool, "EditEngineItemPool missing" );
//STRIP001 	return *pEditEngineItemPool;
//STRIP001 }


/*N*/ void SmDocShell::Draw(OutputDevice &rDev, Point &rPosition)
/*N*/ {
/*N*/ 	if (!pTree)
/*?*/ 		Parse();
/*N*/ 	DBG_ASSERT(pTree, "Sm : NULL pointer");
/*N*/ 
/*N*/ 	if (!IsFormulaArranged())
/*N*/ 		ArrangeFormula();
/*N*/ 
/*N*/ 	//Problem: Was passiert mit dem WYSIWYG? Wir haben waehrend wir inplace aktiv
/*N*/ 	//sind kein Referenzdevice und sind auch nicht darauf ausgerichtet. Es kann
/*N*/ 	//also jetzt eine Differenz zwischen der VisArea (spricht die Groesse im Client)
/*N*/ 	//und der jetzt vorliegenden Groese geben.
/*N*/ 	//Idee: Die Differenz koennte, zumindest behelfsmaessig, mit SmNod::SetSize
/*N*/ 	//angepasst werden.
/*N*/ 
/*N*/ 	rPosition.X() += aFormat.GetDistance( DIS_LEFTSPACE );
/*N*/ 	rPosition.Y() += aFormat.GetDistance( DIS_TOPSPACE	);
/*N*/ 
/*N*/     //! in case of high contrast-mode (accessibility option!)
/*N*/     //! the draw mode needs to be set to default, because when imbedding
/*N*/     //! Math for example in Calc in "a over b" the fraction bar may not
/*N*/     //! be visible else. More generally: the FillColor may have been changed.
/*N*/     ULONG nOldDrawMode = DRAWMODE_DEFAULT;
/*N*/     BOOL bRestoreDrawMode = FALSE;
/*N*/     if (OUTDEV_WINDOW == rDev.GetOutDevType() &&
/*N*/         ((Window &) rDev).GetDisplayBackground().GetColor().IsDark())
/*N*/     {
/*?*/          nOldDrawMode = rDev.GetDrawMode();
/*?*/          rDev.SetDrawMode( DRAWMODE_DEFAULT );
/*?*/          bRestoreDrawMode = TRUE;
/*N*/     }
/*N*/ 
/*N*/     pTree->Draw(rDev, rPosition);
/*N*/ 
/*N*/     if (bRestoreDrawMode)
/*?*/         rDev.SetDrawMode( nOldDrawMode );
/*N*/ }



/*N*/ Size SmDocShell::GetSize()
/*N*/ {
/*N*/ 	Size aRet;
/*N*/ 
/*N*/ 	if (!pTree)
/*N*/ 		Parse();
/*N*/ 
/*N*/ 	if (pTree)
/*N*/ 	{
/*N*/ 		if (!IsFormulaArranged())
/*N*/ 			ArrangeFormula();
/*N*/ 		aRet = pTree->GetSize();
/*N*/ 
/*N*/ 		if ( !aRet.Width() )
/*?*/ 			aRet.Width() = 2000;
/*N*/ 		else
/*N*/ 			aRet.Width()  += aFormat.GetDistance( DIS_LEFTSPACE ) +
/*N*/ 							 aFormat.GetDistance( DIS_RIGHTSPACE );
/*N*/ 		if ( !aRet.Height() )
/*?*/ 			aRet.Height() = 1000;
/*N*/ 		else
/*N*/ 			aRet.Height() += aFormat.GetDistance( DIS_TOPSPACE ) +
/*N*/ 							 aFormat.GetDistance( DIS_BOTTOMSPACE );
/*N*/ 	}
/*N*/ 
/*N*/ 	return aRet;
/*N*/ }

////////////////////////////////////////

/*N*/ SmPrinterAccess::SmPrinterAccess( SmDocShell &rDocShell )
/*N*/ {
/*N*/ 	if ( 0 != (pPrinter = rDocShell.GetPrt()) )
/*N*/ 	{
/*N*/ 		pPrinter->Push( PUSH_MAPMODE );
/*N*/ 		if ( rDocShell.GetProtocol().IsInPlaceActive() ||
/*N*/ 			 SFX_CREATE_MODE_EMBEDDED == rDocShell.GetCreateMode() )
/*N*/ 		{
/*N*/ 			// if it is an embedded object (without it's own printer)
/*N*/ 			// we change the MapMode temporarily.
/*N*/ 			//!If it is a document with it's own printer the MapMode should
/*N*/ 			//!be set correct (once) elsewhere(!), in order to avoid numerous
/*N*/ 			//!superfluous pushing and poping of the MapMode when using
/*N*/ 			//!this class.
/*N*/ 
/*N*/ 			const MapUnit eOld = pPrinter->GetMapMode().GetMapUnit();
/*?*/  			if ( MAP_100TH_MM != eOld )
/*?*/  			{
/*?*/  				MapMode aMap( pPrinter->GetMapMode() );
/*?*/  				aMap.SetMapUnit( MAP_100TH_MM );
/*?*/  				Point aTmp( aMap.GetOrigin() );
/*?*/  				aTmp.X() = OutputDevice::LogicToLogic( aTmp.X(), eOld, MAP_100TH_MM );
/*?*/  				aTmp.Y() = OutputDevice::LogicToLogic( aTmp.Y(), eOld, MAP_100TH_MM );
/*?*/  				aMap.SetOrigin( aTmp );
/*?*/  				pPrinter->SetMapMode( aMap );
/*?*/  			}
/*N*/ 		}
/*N*/ 	}
/*N*/     if ( 0 != (pRefDev = rDocShell.GetRefDev()) && pPrinter != pRefDev )
/*N*/     {
/*N*/         pRefDev->Push( PUSH_MAPMODE );
/*N*/         if ( rDocShell.GetProtocol().IsInPlaceActive() ||
/*N*/              SFX_CREATE_MODE_EMBEDDED == rDocShell.GetCreateMode() )
/*N*/         {
/*N*/             // if it is an embedded object (without it's own printer)
/*N*/             // we change the MapMode temporarily.
/*N*/             //!If it is a document with it's own printer the MapMode should
/*N*/             //!be set correct (once) elsewhere(!), in order to avoid numerous
/*N*/             //!superfluous pushing and poping of the MapMode when using
/*N*/             //!this class.
/*N*/ 
/*N*/             const MapUnit eOld = pRefDev->GetMapMode().GetMapUnit();
/*N*/             if ( MAP_100TH_MM != eOld )
/*N*/             {
/*N*/                 MapMode aMap( pRefDev->GetMapMode() );
/*N*/                 aMap.SetMapUnit( MAP_100TH_MM );
/*N*/                 Point aTmp( aMap.GetOrigin() );
/*N*/                 aTmp.X() = OutputDevice::LogicToLogic( aTmp.X(), eOld, MAP_100TH_MM );
/*N*/                 aTmp.Y() = OutputDevice::LogicToLogic( aTmp.Y(), eOld, MAP_100TH_MM );
/*N*/                 aMap.SetOrigin( aTmp );
/*N*/                 pRefDev->SetMapMode( aMap );
/*N*/             }
/*N*/         }
/*N*/     }
/*N*/ }

/*N*/ SmPrinterAccess::~SmPrinterAccess()
/*N*/ {
/*N*/ 	if ( pPrinter )
/*N*/ 		pPrinter->Pop();
/*N*/     if ( pRefDev && pRefDev != pPrinter )
/*N*/         pRefDev->Pop();
/*N*/ }

////////////////////////////////////////

/*N*/ Printer* SmDocShell::GetPrt()
/*N*/ {
/*N*/ 	if ( GetProtocol().IsInPlaceActive() ||
/*N*/  		 SFX_CREATE_MODE_EMBEDDED == GetCreateMode() )
/*N*/ 	{
/*N*/ 		//Normalerweise wird der Printer vom Server besorgt. Wenn dieser aber
/*N*/ 		//keinen liefert (weil etwa noch keine connection da ist), kann es
/*N*/ 		//dennoch sein, dass wir den Printer kennen, denn dieser wird in
/*N*/ 		//OnDocumentPrinterChanged vom Server durchgereicht und dann temporaer
/*N*/ 		//festgehalten.
/*N*/         Printer *pPrt = GetDocumentPrinter();
/*N*/         if ( !pPrt && pTmpPrinter )
/*N*/             pPrt = pTmpPrinter;
/*N*/         return pPrt;
/*N*/ 	}
/*N*/ 	else if ( !pPrinter )
/*N*/ 	{
/*N*/ 		SfxItemSet *pOptions =
/*N*/ 			new SfxItemSet(GetPool(),
/*N*/ 						   SID_PRINTSIZE,		SID_PRINTSIZE,
/*N*/ 						   SID_PRINTZOOM,		SID_PRINTZOOM,
/*N*/ 						   SID_PRINTTITLE,		SID_PRINTTITLE,
/*N*/ 						   SID_PRINTTEXT,		SID_PRINTTEXT,
/*N*/ 						   SID_PRINTFRAME,		SID_PRINTFRAME,
/*N*/ 						   SID_NO_RIGHT_SPACES, SID_NO_RIGHT_SPACES,
/*N*/ 						   0);
/*N*/ 
/*N*/ 		SmModule *pp = SM_MOD1();
/*N*/ 		pp->GetConfig()->ConfigToItemSet(*pOptions);
/*N*/ 		pPrinter = new SfxPrinter(pOptions);
/*N*/ 		pPrinter->SetMapMode( MapMode(MAP_100TH_MM) );
/*N*/ 	}
/*N*/ 	return pPrinter;
/*N*/ }

/*N*/ OutputDevice* SmDocShell::GetRefDev()
/*N*/ {
/*N*/     if ( GetProtocol().IsInPlaceActive() ||
/*N*/          SFX_CREATE_MODE_EMBEDDED == GetCreateMode() )
/*N*/     {
/*N*/         OutputDevice* pOutDev = GetDocumentRefDev();
/*N*/         if ( pOutDev )
/*N*/             return pOutDev;
/*N*/     }
/*N*/ 
/*N*/     return GetPrt();
/*N*/ }


/*N*/ void SmDocShell::SetPrinter( SfxPrinter *pNew )
/*N*/ {DBG_BF_ASSERT(0, "STRIP"); //STRIP001 
//STRIP001 	delete pPrinter;
//STRIP001 	pPrinter = pNew;	//Eigentumsuebergang!
//STRIP001 	pPrinter->SetMapMode( MapMode(MAP_100TH_MM) );
//STRIP001 	SetFormulaArranged(FALSE);
//STRIP001 	SM_MOD1()->GetRectCache()->Reset();
//STRIP001 	Resize();
/*N*/ }

/*N*/ void SmDocShell::OnDocumentPrinterChanged( Printer *pPrt )
/*N*/ {
/*N*/ 	pTmpPrinter = pPrt;
/*N*/ 	SetFormulaArranged(FALSE);
/*N*/ 	SM_MOD1()->GetRectCache()->Reset();
/*N*/ 	Size aOldSize = GetVisArea().GetSize();
/*N*/ 	Resize();
/*N*/ 	if( aOldSize != GetVisArea().GetSize() && aText.Len() )
/*N*/ 		SetModified( TRUE );
/*N*/ 	pTmpPrinter = 0;
/*N*/ }

/*N*/ void SmDocShell::Resize()
/*N*/ {
/*N*/ 	Size aVisSize = GetSize();
/*N*/ 
/*N*/ 	BOOL bIsEnabled = IsEnableSetModified();
/*N*/ 	if ( bIsEnabled )
/*?*/ 		EnableSetModified( FALSE );
/*N*/ 
/*N*/ 	SetVisAreaSize( aVisSize );
/*N*/ 	SmViewShell *pViewSh = SmGetActiveView();
/*N*/ 	if (pViewSh)
/*?*/         pViewSh->GetGraphicWindow().Invalidate();
/*N*/ 
/*N*/ 	if ( bIsEnabled )
/*?*/ 		EnableSetModified( bIsEnabled );
/*N*/ }


/*N*/ SmDocShell::SmDocShell(SfxObjectCreateMode eMode) :
/*N*/ 	SfxObjectShell(eMode),
/*N*/ 	pSymSetMgr			( 0 ),
/*N*/ 	pTree				( 0 ),
/*N*/ 	pPrinter			( 0 ),
/*N*/ 	pTmpPrinter			( 0 ),
/*N*/ 	pEditEngineItemPool	( 0 ),
/*N*/ 	pEditEngine			( 0 ),
/*N*/ 	nModifyCount		( 0 ),
/*N*/ 	bIsFormulaArranged	( FALSE )
/*N*/ {
/*N*/ 	SetPool(&SFX_APP()->GetPool());
/*N*/ 
/*N*/ 	SmModule *pp = SM_MOD1();
/*N*/     aFormat = pp->GetConfig()->GetStandardFormat();
/*N*/ 
/*N*/ 	StartListening(aFormat);
/*N*/ 	StartListening(*pp->GetConfig());
/*N*/ 
/*N*/ 	SetShell(this);
/*N*/ 	SetModel( new SmModel(this) );	//! das hier mit new erzeugte Model brauch
/*N*/ 									//! im Destruktor nicht explizit gel�scht werden.
/*N*/ 									//! Dies erledigt das Sfx.
/*N*/ }



/*N*/ SmDocShell::~SmDocShell()
/*N*/ {
/*N*/ 	SmModule *pp = SM_MOD1();
/*N*/ 
/*N*/ 	EndListening(aFormat);
/*N*/ 	EndListening(*pp->GetConfig());
/*N*/ 
/*N*/ 	delete pEditEngine;
/*N*/ 	delete pEditEngineItemPool;
/*N*/ 	delete pTree;
/*N*/ 	delete pPrinter;
/*N*/ }


//STRIP001 BOOL SmDocShell::SetData( const String& rData )
//STRIP001 {
//STRIP001 	SetText( rData );
//STRIP001 	return TRUE;
//STRIP001 }

/*N*/ void SmDocShell::ConvertText( String &rText, SmConvert eConv )
/*N*/     // adapts the text 'rText' that suits one office version to be
/*N*/     // usable in another office version.
/*N*/     // Example: "2 over sin x" acts very different in 4.0 and 5.0,
/*N*/     // and from 5.2 to 6.0 many symbol names were renamed.
/*N*/ {
/*N*/ 	if (pTree)
/*N*/ 		delete pTree;
/*N*/ 
/*N*/     SmConvert  eTmpConv = aInterpreter.GetConversion();
/*N*/ 
/*N*/     // parse in old style and make changes for new style
/*N*/     aInterpreter.SetConversion(eConv);
/*N*/     pTree = aInterpreter.Parse(rText);
/*N*/     // get to new version converted text
/*N*/     rText = aInterpreter.GetText();
/*N*/ 
/*N*/     aInterpreter.SetConversion(eTmpConv);
/*N*/ 
/*N*/ 	// clean up tree parsed in old style
/*N*/ 	if (pTree)
/*N*/ 	{	delete pTree;
/*N*/ 		pTree = NULL;
/*N*/ 	}
/*N*/ }


//STRIP001 BOOL SmDocShell::ConvertFrom(SfxMedium &rMedium)
//STRIP001 {
//STRIP001 	BOOL	 bSuccess = FALSE;
//STRIP001 	const String& rFltName = rMedium.GetFilter()->GetFilterName();
//STRIP001 	if (rFltName.EqualsAscii( MATHML_XML ) ||
//STRIP001 		rFltName.EqualsAscii( STAROFFICE_XML ))
//STRIP001 	{
//STRIP001 		if (pTree)
//STRIP001 		{
//STRIP001 			delete pTree;
//STRIP001 			pTree = 0;
//STRIP001 		}
//STRIP001         Reference< ::com::sun::star::frame::XModel> xModel(GetModel());
//STRIP001 		SmXMLWrapper aEquation(xModel);
//STRIP001         bSuccess = 0 == aEquation.Import(rMedium);
//STRIP001 	}
//STRIP001 	else if( rMedium.IsStorage() && rMedium.GetStorage()->IsStream(
//STRIP001 		C2S( "Equation Native" )))
//STRIP001 	{
//STRIP001 		// is this a MathType Storage?
//STRIP001 		MathType aEquation( aText );
//STRIP001         if (bSuccess = (1 == aEquation.Parse(rMedium.GetStorage())))
//STRIP001 			Parse();
//STRIP001 	}
//STRIP001 	else
//STRIP001 	{
//STRIP001 		SvStream *pStream = rMedium.GetInStream();
//STRIP001 		if (pStream)
//STRIP001 		{
//STRIP001 			bSuccess = ImportSM20File( pStream );
//STRIP001 			rMedium.CloseInStream();
//STRIP001 		}
//STRIP001 	}
//STRIP001 	FinishedLoading( SFX_LOADED_ALL );
//STRIP001 	return bSuccess;
//STRIP001 }



//STRIP001 BOOL SmDocShell::InsertFrom(SfxMedium &rMedium)
//STRIP001 {
//STRIP001     BOOL        bSuccess = FALSE;
//STRIP001     SvStream   *pStream = rMedium.GetInStream();
//STRIP001     String      aTemp = aText;
//STRIP001 
//STRIP001     if (pStream)
//STRIP001     {
//STRIP001         const String& rFltName = rMedium.GetFilter()->GetFilterName();
//STRIP001         if ( rFltName.EqualsAscii(MATHML_XML) )
//STRIP001         {
//STRIP001             Reference< ::com::sun::star::frame::XModel> xModel(GetModel());
//STRIP001             SmXMLWrapper aEquation(xModel);
//STRIP001             bSuccess = 0 == aEquation.Import(rMedium);
//STRIP001         }
//STRIP001         else
//STRIP001         {
//STRIP001             bSuccess = ImportSM20File( pStream );
//STRIP001             rMedium.CloseInStream();
//STRIP001         }
//STRIP001     }
//STRIP001 
//STRIP001     if( bSuccess )
//STRIP001     {
//STRIP001         SmViewShell *pView = SmGetActiveView();
//STRIP001         SmEditWindow *pEditWin = pView ? pView->GetEditWindow() : 0;
//STRIP001 
//STRIP001         if (pEditWin)
//STRIP001             pEditWin->InsertText( aText );
//STRIP001         else
//STRIP001         {
//STRIP001             DBG_ERROR( "EditWindow missing" );
//STRIP001             aTemp += aText;
//STRIP001             aText  = aTemp;
//STRIP001         }
//STRIP001 
//STRIP001         Parse();
//STRIP001         SetModified(TRUE);
//STRIP001         if (pView)
//STRIP001         {
//STRIP001             SfxBindings &rBnd = pView->GetViewFrame()->GetBindings();
//STRIP001             rBnd.Invalidate(SID_GRAPHIC);
//STRIP001             rBnd.Invalidate(SID_TEXT);
//STRIP001         }
//STRIP001     }
//STRIP001 
//STRIP001     return bSuccess;
//STRIP001 }



/*N*/ BOOL SmDocShell::InitNew(SvStorage * pStor)
/*N*/ {
/*N*/ 	BOOL bRet = FALSE;
/*N*/ 	if (SfxInPlaceObject::InitNew(pStor))
/*N*/ 	{
/*N*/ 		bRet = TRUE;
/*N*/ 		SetVisArea(Rectangle(Point(0, 0), Size(2000, 1000)));
/*N*/ #if 0
/*N*/ 		if (pStor)
/*N*/ 		{
/*N*/ 			aDocStream = pStor->OpenStream(String::CreateFromAscii(pStarMathDoc));
/*N*/ 			aDocStream->SetVersion (pStor->GetVersion ());
/*N*/ 			GetPool().SetFileFormatVersion(USHORT(pStor->GetVersion()));
/*N*/ 
/*N*/ 			if (! aDocStream )
/*N*/ 				bRet = FALSE;
/*N*/ 		}
/*N*/ #endif
/*N*/ 	}
/*N*/ 	return bRet;
/*N*/ }


/*N*/ BOOL SmDocShell::Load(SvStorage *pStor)
/*N*/ {
/*N*/ 	BOOL bRet = FALSE;
/*N*/ 	if( SfxInPlaceObject::Load( pStor ))
/*N*/ 	{
/*N*/ 		String aTmpStr( C2S( "Equation Native" ));
/*N*/ 		if( pStor->IsStream( aTmpStr ))
/*N*/ 		{
/*N*/ 			// is this a MathType Storage?
/*?*/ 			DBG_BF_ASSERT(0, "STRIP"); //STRIP001 /*?*/  			MathType aEquation(aText);
//STRIP001 /*?*/  			if (bRet = (1 == aEquation.Parse(pStor)))
//STRIP001 /*?*/  				Parse();
/*N*/ 		}
/*N*/ 		else if( pStor->IsStream(C2S("content.xml")) ||
/*N*/ 				 pStor->IsStream(C2S("Content.xml")) )
/*N*/ 		{
/*?*/  			// is this a fabulous math package ?
/*?*/              Reference< ::com::sun::star::frame::XModel> xModel(GetModel());
/*?*/  			SmXMLWrapper aEquation(xModel);
/*?*/  			SfxMedium aMedium(pStor);
/*?*/              ULONG nError = aEquation.Import(aMedium);
/*?*/              bRet = 0 == nError;
/*?*/              SetError( nError );
/*N*/ 		}
/*N*/ 		else
/*N*/ 		{
/*N*/             bRet = Try3x(pStor, STREAM_READWRITE);
/*N*/ 
/*N*/ 			if( !bRet )
/*N*/ 			{
/*?*/  				pStor->Remove(String::CreateFromAscii(pStarMathDoc));
/*?*/ 					{DBG_BF_ASSERT(0, "STRIP");} //STRIP001 /*?*/                  bRet = Try2x(pStor, STREAM_READWRITE);
/*?*/  				pStor->Remove(C2S("\1Ole10Native"));
/*N*/ 			}
/*N*/ 			else
/*N*/             {
/*N*/                 long nVersion = pStor->GetVersion();
/*N*/                 if ( nVersion <= SOFFICE_FILEFORMAT_40 )
/*N*/                     ConvertText( aText, CONVERT_40_TO_50 );
/*N*/                 if ( nVersion <= SOFFICE_FILEFORMAT_50 )
/*N*/                     ConvertText( aText, CONVERT_50_TO_60 );
/*N*/                 if (pTree)
/*?*/                 {   delete pTree;
/*?*/                     pTree = NULL;
/*N*/                 }
/*N*/ 			}
/*N*/ 		}
/*N*/ 	}
/*N*/ 	FinishedLoading( SFX_LOADED_ALL );
/*N*/ 	return bRet;
/*N*/ }



//STRIP001 BOOL SmDocShell::Insert(SvStorage *pStor)
//STRIP001 {
//STRIP001 	String aTemp = aText;
//STRIP001     BOOL bRet = FALSE, bChkOldVersion = TRUE;
//STRIP001 
//STRIP001 	String aTmpStr( C2S( "Equation Native" ));
//STRIP001 	if( pStor->IsStream( aTmpStr ))
//STRIP001 	{
//STRIP001 		bChkOldVersion = FALSE;
//STRIP001 		// is this a MathType Storage?
//STRIP001 		MathType aEquation(aText);
//STRIP001 		if (bRet = (1 == aEquation.Parse(pStor)))
//STRIP001 			Parse();
//STRIP001 	}
//STRIP001 	else if( pStor->IsStream(C2S("content.xml")) ||
//STRIP001 			 pStor->IsStream(C2S("Content.xml")) )
//STRIP001 	{
//STRIP001 		bChkOldVersion = FALSE;
//STRIP001 		// is this a fabulous math package ?
//STRIP001         Reference< ::com::sun::star::frame::XModel> xModel(GetModel());
//STRIP001 		SmXMLWrapper aEquation(xModel);
//STRIP001 		SfxMedium aMedium(pStor);
//STRIP001         bRet = 0 == aEquation.Import(aMedium);
//STRIP001 	}
//STRIP001     else if (!(bRet = Try3x(pStor, STREAM_STD_READ)))
//STRIP001 	{
//STRIP001         pStor->Remove(String::CreateFromAscii(pStarMathDoc));
//STRIP001         bRet = Try2x(pStor, STREAM_STD_READ);
//STRIP001 		pStor->Remove(C2S("\1Ole10Native"));
//STRIP001 	}
//STRIP001 
//STRIP001 	if( bRet )
//STRIP001 	{
//STRIP001         SmViewShell *pView = SmGetActiveView();
//STRIP001         SmEditWindow *pEditWin = pView ? pView->GetEditWindow() : 0;
//STRIP001 
//STRIP001         if (pEditWin)
//STRIP001             pEditWin->InsertText( aText );
//STRIP001         else
//STRIP001         {
//STRIP001             DBG_ERROR( "EditWindow missing" );
//STRIP001             aTemp += aText;
//STRIP001             aText  = aTemp;
//STRIP001         }
//STRIP001 
//STRIP001         if( bChkOldVersion )
//STRIP001         {
//STRIP001             if( SOFFICE_FILEFORMAT_40 >= pStor->GetVersion() )
//STRIP001                 ConvertText( aText, CONVERT_40_TO_50 );
//STRIP001             if( SOFFICE_FILEFORMAT_50 >= pStor->GetVersion() )
//STRIP001                 ConvertText( aText, CONVERT_50_TO_60 );
//STRIP001         }
//STRIP001 
//STRIP001 		Parse();
//STRIP001 		SetModified(TRUE);
//STRIP001         if (pView)
//STRIP001 		{
//STRIP001             SfxBindings &rBnd = pView->GetViewFrame()->GetBindings();
//STRIP001 			rBnd.Invalidate(SID_GRAPHIC);
//STRIP001 			rBnd.Invalidate(SID_TEXT);
//STRIP001 		}
//STRIP001 	}
//STRIP001 	return bRet;
//STRIP001 }

//------------------------------------------------------------------

/*N*/ void SmDocShell::ImplSave( SvStorageStreamRef xStrm )
/*N*/ {
/*N*/     String aTmp( aText );
/*N*/     if (SOFFICE_FILEFORMAT_50 >= xStrm->GetVersion())
/*N*/         ConvertText( aTmp, CONVERT_60_TO_50 );
/*N*/     ByteString exString( ExportString( aTmp ) );
/*N*/ 
/*N*/ 	*xStrm	<< SM304AIDENT << SM50VERSION
/*N*/ 			<< 'T';
/*N*/ 	xStrm->WriteByteString(exString);
/*N*/ 	*xStrm	<< 'F' << aFormat
/*N*/             << 'S';
/*N*/     xStrm->WriteByteString( ExportString(C2S("unknown")) );
/*N*/     *xStrm  << (USHORT) 0
/*N*/ 			<< '\0';
/*N*/ }

/*N*/ BOOL SmDocShell::Save()
/*N*/ {
/*N*/     //! apply latest changes if necessary
/*N*/     UpdateText();
/*N*/ 
/*N*/     if ( SfxInPlaceObject::Save() )
/*N*/ 	{
/*N*/ 		if( !pTree )
/*N*/ 			Parse();
/*N*/ 		if( pTree && !IsFormulaArranged() )
/*N*/ 			ArrangeFormula();
/*N*/ 
/*N*/ 		SvStorage *pStor = GetStorage();
/*N*/ 		if(pStor->GetVersion() >= SOFFICE_FILEFORMAT_60)
/*N*/ 		{
/*N*/ 			// a math package as a storage
/*N*/             Reference< ::com::sun::star::frame::XModel> xModel(GetModel());
/*N*/ 			SmXMLWrapper aEquation(xModel);
/*N*/ 			SfxMedium aMedium(pStor);
/*N*/ 			aEquation.SetFlat(sal_False);
/*N*/ 			return aEquation.Export(aMedium);
/*N*/ 		}
/*N*/ 		else
/*N*/ 		{
/*?*/ 			aDocStream = pStor->OpenStream(String::CreateFromAscii(pStarMathDoc));
/*?*/ 			aDocStream->SetVersion (pStor->GetVersion ());
/*?*/ 			GetPool().SetFileFormatVersion(USHORT(pStor->GetVersion()));
/*?*/ 
/*?*/ 			aDocStream->Seek(0);
/*?*/ 			ImplSave( aDocStream );
/*?*/ 
/*?*/ 			aDocStream.Clear();
/*?*/ 			return TRUE;
/*N*/ 		}
/*N*/ 	}
/*N*/ 	return FALSE;
/*N*/ }


/*N*/ void SmDocShell::UpdateText()
/*N*/ {
/*N*/     if (pEditEngine && pEditEngine->IsModified())
/*N*/     {
/*N*/         String aEngTxt( pEditEngine->GetText( LINEEND_LF ) );
/*N*/         if (GetText() != aEngTxt)
/*N*/             SetText( aEngTxt );
/*N*/     }
/*N*/ }


/*N*/ BOOL SmDocShell::SaveAs(SvStorage * pNewStor)
/*N*/ {
/*N*/ 	BOOL bRet = FALSE;
/*N*/ 
/*N*/     //! apply latest changes if necessary
/*N*/     UpdateText();
/*N*/ 
/*N*/     if ( SfxInPlaceObject::SaveAs( pNewStor ) )
/*N*/ 	{
/*N*/ 		if( !pTree )
/*?*/ 			Parse();
/*N*/ 		if( pTree && !IsFormulaArranged() )
/*?*/ 			ArrangeFormula();
/*N*/ 
/*N*/ 		if (pNewStor->GetVersion() >= SOFFICE_FILEFORMAT_60)
/*N*/ 		{
/*N*/ 			// a math package as a storage
/*?*/              Reference< ::com::sun::star::frame::XModel> xModel(GetModel());
/*?*/  			SmXMLWrapper aEquation(xModel);
/*?*/  			SfxMedium aMedium(pNewStor);
/*?*/  			aEquation.SetFlat(sal_False);
/*?*/  			bRet = aEquation.Export(aMedium);
/*N*/ 		}
/*N*/ 		else
/*N*/ 		{
/*N*/ 			SvStorageStreamRef aStm = pNewStor->OpenStream(
/*N*/ 										String::CreateFromAscii(pStarMathDoc));
/*N*/ 			aStm->SetVersion( pNewStor->GetVersion() );
/*N*/ 			GetPool().SetFileFormatVersion( USHORT( pNewStor->GetVersion() ));
/*N*/ 			aStm->SetBufferSize(DOCUMENT_BUFFER_SIZE);
/*N*/ 			aStm->SetKey( pNewStor->GetKey() ); // Passwort setzen
/*N*/ 
/*N*/ 			if ( aStm.Is() )
/*N*/ 			{
/*N*/ 				ImplSave( aStm );
/*N*/ 				bRet = TRUE;
/*N*/ 			}
/*N*/ 		}
/*N*/ 	}
/*N*/ 	return bRet;
/*N*/ }

//STRIP001 BOOL SmDocShell::ConvertTo( SfxMedium &rMedium )
//STRIP001 {
//STRIP001 	BOOL bRet = FALSE;
//STRIP001 	const SfxFilter* pFlt = rMedium.GetFilter();
//STRIP001 	if( pFlt )
//STRIP001 	{
//STRIP001 		if( !pTree )
//STRIP001 			Parse();
//STRIP001 		if( pTree && !IsFormulaArranged() )
//STRIP001 			ArrangeFormula();
//STRIP001 
//STRIP001 		const String& rFltName = pFlt->GetFilterName();
//STRIP001 		if(rFltName.EqualsAscii( STAROFFICE_XML ))
//STRIP001 		{
//STRIP001             Reference< ::com::sun::star::frame::XModel> xModel(GetModel());
//STRIP001 			SmXMLWrapper aEquation(xModel);
//STRIP001 			aEquation.SetFlat(sal_False);
//STRIP001 			bRet = aEquation.Export(rMedium);
//STRIP001 		}
//STRIP001 		else if(rFltName.EqualsAscii( MATHML_XML ))
//STRIP001 		{
//STRIP001             Reference< ::com::sun::star::frame::XModel> xModel(GetModel());
//STRIP001 			SmXMLWrapper aEquation(xModel);
//STRIP001 			aEquation.SetFlat(sal_True);
//STRIP001 			bRet = aEquation.Export(rMedium);
//STRIP001 		}
//STRIP001 		else if( pFlt->GetFilterName().EqualsAscii("MathType 3.x"))
//STRIP001 			bRet = WriteAsMathType3( rMedium );
//STRIP001 	}
//STRIP001 	return bRet;
//STRIP001 }

/*N*/ BOOL SmDocShell::SaveCompleted(SvStorage * pStor)
/*N*/ {
/*N*/ 	if( SfxInPlaceObject::SaveCompleted( pStor ))
/*N*/ 	{
/*N*/ #if 0
/*N*/ 		if (! pStor)
/*N*/ 			return TRUE;
/*N*/ 
/*N*/ 		aDocStream = pStor->OpenStream(String::CreateFromAscii(pStarMathDoc));
/*N*/ 		aDocStream->SetVersion (pStor->GetVersion ());
/*N*/ 		GetPool().SetFileFormatVersion(USHORT(pStor->GetVersion()));
/*N*/ 		aDocStream->SetBufferSize(DOCUMENT_BUFFER_SIZE);
/*N*/ 		aDocStream->SetKey( pStor->GetKey() ); // Passwort setzen
/*N*/ 		return aDocStream.Is();
/*N*/ #endif
/*N*/ 		return TRUE;
/*N*/ 	}
/*N*/ 	return FALSE;
/*N*/ }



//STRIP001 BOOL SmDocShell::ImportSM20File(SvStream *pStream)
//STRIP001 {
//STRIP001 	void ReadSM20SymSet(SvStream*, SmSymSet*);
//STRIP001 
//STRIP001 	char		 cTag;
//STRIP001 	ULONG		 lIdent, lVersion;
//STRIP001 	long		 lTime;
//STRIP001 	ULONG		 lDate;
//STRIP001 	String		 aBuffer;
//STRIP001     ByteString   aByteStr;
//STRIP001 	SmSymSet	*pSymbolSet;
//STRIP001 	ULONG		 FilePos = pStream->Tell();
//STRIP001 
//STRIP001 	*pStream >> lIdent >> lVersion;
//STRIP001 
//STRIP001 	if (lIdent == FRMIDENT)
//STRIP001 	{
//STRIP001 		DBG_ASSERT((lVersion == FRMVERSION), "Illegal file version");
//STRIP001 
//STRIP001 		*pStream >> cTag;
//STRIP001         rtl_TextEncoding eEnc = RTL_TEXTENCODING_MS_1252;
//STRIP001 		while (cTag && !pStream->IsEof())
//STRIP001 		{
//STRIP001 			switch (cTag)
//STRIP001 			{
//STRIP001 				case 'T':
//STRIP001                     pStream->ReadByteString( aByteStr );
//STRIP001                     aText = ImportString( aByteStr );
//STRIP001                     Parse();
//STRIP001 					break;
//STRIP001 
//STRIP001 				case 'D':
//STRIP001 					{
//STRIP001 						pStream->ReadByteString(aBuffer, eEnc);
//STRIP001 						pStream->ReadByteString(aBuffer, eEnc);
//STRIP001 						*pStream >> lDate >> lTime;
//STRIP001 						pStream->ReadByteString(aBuffer, eEnc);
//STRIP001 						*pStream >> lDate >> lTime;
//STRIP001 						pStream->ReadByteString(aBuffer, eEnc);
//STRIP001 					}
//STRIP001 					break;
//STRIP001 
//STRIP001 				case 'F':
//STRIP001 					aFormat.ReadSM20Format(*pStream);
//STRIP001 					aFormat.From300To304a ();
//STRIP001 					break;
//STRIP001 
//STRIP001 				case 'S':
//STRIP001 					pSymbolSet = new SmSymSet();
//STRIP001 					ReadSM20SymSet(pStream, pSymbolSet);
//STRIP001                     delete pSymbolSet;
//STRIP001 					break;
//STRIP001 
//STRIP001 				default:
//STRIP001 					DBG_ASSERT((cTag != 0), "Illegal data tag");
//STRIP001 			}
//STRIP001 			*pStream >> cTag;
//STRIP001 		}
//STRIP001 
//STRIP001 		return TRUE;
//STRIP001 	}
//STRIP001 
//STRIP001 	pStream->Seek(FilePos);
//STRIP001 
//STRIP001 	return FALSE;
//STRIP001 }


/*N*/ void SmDocShell::Execute(SfxRequest& rReq)
/*N*/ {
/*N*/ 	SfxBindings *pBindings	= NULL;
/*N*/ 	SmViewShell *pViewSh	= SmGetActiveView();
/*N*/ 	if (pViewSh)
/*?*/ 		pBindings = &pViewSh->GetViewFrame()->GetBindings();
/*N*/ 	switch (rReq.GetSlot())
/*N*/ 	{
/*N*/ 	case SID_TEXTMODE:
/*N*/ 		{
/*?*/ 			SmFormat  &rFormat = GetFormat();
/*?*/ 			rFormat.SetTextmode(!rFormat.IsTextmode());
/*?*/ 			rFormat.RequestApplyChanges();
/*N*/ 		}
/*N*/ 		break;
/*N*/ 
/*?*/ 	case SID_AUTO_REDRAW :
/*?*/ 		{
/*?*/ 			DBG_BF_ASSERT(0, "STRIP"); //STRIP001 SmModule *pp = SM_MOD1();
//STRIP001 /*?*/ 			BOOL bRedraw = pp->GetConfig()->IsAutoRedraw();
//STRIP001 /*?*/ 			pp->GetConfig()->SetAutoRedraw(!bRedraw);
/*?*/ 		}
/*?*/ 		break;
/*?*/ 
/*?*/ 	case SID_SYMBOLS_CATALOGUE:
/*?*/ 		{
/*?*/ 			DBG_BF_ASSERT(0, "STRIP"); //STRIP001 /*?*/ 			SmSymbolDialog(NULL, GetSymSetManager()).Execute();
//STRIP001 /*?*/ 			RestartFocusTimer();
/*?*/ 		}
/*?*/ 		break;
/*?*/ 
/*?*/ 	case SID_TOOLBOX:
/*?*/ 		{
/*?*/ 			SmViewShell *pView = SmGetActiveView();
/*?*/ 			if (pView)
/*?*/ 			{DBG_BF_ASSERT(0, "STRIP"); //STRIP001 
//STRIP001 /*?*/ 				pView->GetViewFrame()->ToggleChildWindow(
//STRIP001 /*?*/ 						SmToolBoxWrapper::GetChildWindowId() );
/*?*/ 			}
/*?*/ 		}
/*?*/ 		break;
/*?*/ 
/*?*/ 	case SID_INSERT_FORMULA:
/*?*/ 		{
/*?*/ 			DBG_BF_ASSERT(0, "STRIP"); //STRIP001 /*?*/ 			SfxMedium *pMedium = SFX_APP()->
//STRIP001 /*?*/                     InsertDocumentDialog( 0, SmDocShell::Factory() );
//STRIP001 /*?*/ 
//STRIP001 /*?*/ 			if (pMedium != NULL)
//STRIP001 /*?*/ 			{
//STRIP001 /*?*/ 				if (pMedium->IsStorage())
//STRIP001 /*?*/ 					Insert(pMedium->GetStorage());
//STRIP001 /*?*/ 				else
//STRIP001 /*?*/ 					InsertFrom(*pMedium);
//STRIP001 /*?*/ 				delete pMedium;
//STRIP001 /*?*/ 
//STRIP001 /*?*/                 UpdateText();
//STRIP001 /*?*/ 				ArrangeFormula();
//STRIP001 /*?*/ 				Resize();
//STRIP001 /*?*/ 				// Fenster anpassen, neuzeichnen, ModifyCount erh�hen,...
//STRIP001 /*?*/ 				if (pBindings)
//STRIP001 /*?*/ 					pBindings->Invalidate(SID_GRAPHIC);
//STRIP001 /*?*/ 			}
//STRIP001 /*?*/ 			RestartFocusTimer();
//STRIP001 /*?*/ 			rReq.SetReturnValue (SfxBoolItem (rReq.GetSlot(), TRUE));
/*?*/ 		}
/*?*/ 		break;
/*?*/ 
/*?*/ 	case SID_LOADSYMBOLS:
/*?*/ 		{DBG_BF_ASSERT(0, "STRIP");} //STRIP001 /*?*/ 		LoadSymbols();
/*?*/ 		break;
/*?*/ 
/*?*/ 	case SID_SAVESYMBOLS:
/*?*/ 		{DBG_BF_ASSERT(0, "STRIP");} //STRIP001 /*?*/ 		SaveSymbols();
/*?*/ 		break;
/*?*/ 
/*?*/ 	case SID_FONT:
/*?*/ 		{
/*?*/ 			DBG_BF_ASSERT(0, "STRIP"); //STRIP001 /*?*/ 			SmFontTypeDialog *pFontTypeDialog = new SmFontTypeDialog(NULL);
//STRIP001 /*?*/ 
//STRIP001 /*?*/ 			pFontTypeDialog->ReadFrom(GetFormat());
//STRIP001 /*?*/ 			if (pFontTypeDialog->Execute() == RET_OK)
//STRIP001 /*?*/ 			{
//STRIP001 /*?*/ 				SmFormat& rOldFormat  = GetFormat();
//STRIP001 /*?*/ 
//STRIP001 /*?*/ 				pFontTypeDialog->WriteTo(GetFormat());
//STRIP001 /*?*/ 				SfxUndoManager *pUndoMgr = GetUndoManager();
//STRIP001 /*?*/ 				if (pUndoMgr)
//STRIP001 /*?*/ 					pUndoMgr->AddUndoAction(
//STRIP001 /*?*/ 						new SmFormatAction(this, rOldFormat, GetFormat()));
//STRIP001 /*?*/ 
//STRIP001 /*?*/ 				if (aText.Len ())
//STRIP001 /*?*/ 				{
//STRIP001 /*?*/ 					SetModified(TRUE);
//STRIP001 /*?*/ 					if (pBindings)
//STRIP001 /*?*/ 						pBindings->Invalidate(SID_GRAPHIC);
//STRIP001 /*?*/ 				}
//STRIP001 /*?*/ 				else SetModified (FALSE);
//STRIP001 /*?*/ 			}
//STRIP001 /*?*/ 			delete pFontTypeDialog;
//STRIP001 /*?*/ 			RestartFocusTimer ();
/*?*/ 		}
/*?*/ 		break;
/*?*/ 
/*?*/ 	case SID_FONTSIZE:
/*?*/ 		{
/*?*/ 			DBG_BF_ASSERT(0, "STRIP"); //STRIP001 /*?*/ 			SmFontSizeDialog *pFontSizeDialog = new SmFontSizeDialog(NULL);
//STRIP001 /*?*/ 
//STRIP001 /*?*/ 			pFontSizeDialog->ReadFrom(GetFormat());
//STRIP001 /*?*/ 			if (pFontSizeDialog->Execute() == RET_OK)
//STRIP001 /*?*/ 			{
//STRIP001 /*?*/ 				SmFormat& rOldFormat  = GetFormat();
//STRIP001 /*?*/ 
//STRIP001 /*?*/ 				pFontSizeDialog->WriteTo(GetFormat());
//STRIP001 /*?*/ 
//STRIP001 /*?*/ 				SfxUndoManager *pUndoMgr = GetUndoManager();
//STRIP001 /*?*/ 				if (pUndoMgr)
//STRIP001 /*?*/ 					pUndoMgr->AddUndoAction(
//STRIP001 /*?*/ 						new SmFormatAction(this, rOldFormat, GetFormat()));
//STRIP001 /*?*/ 
//STRIP001 /*?*/ 				if (aText.Len ())
//STRIP001 /*?*/ 				{
//STRIP001 /*?*/ 					SetModified(TRUE);
//STRIP001 /*?*/ 					if (pBindings)
//STRIP001 /*?*/ 						pBindings->Invalidate(SID_GRAPHIC);
//STRIP001 /*?*/ 				}
//STRIP001 /*?*/ 				else SetModified (FALSE);
//STRIP001 /*?*/ 			}
//STRIP001 /*?*/ 			delete pFontSizeDialog;
//STRIP001 /*?*/ 			RestartFocusTimer ();
/*?*/ 		}
/*?*/ 		break;
/*?*/ 
/*?*/ 	case SID_DISTANCE:
/*?*/ 		{
/*?*/ 			DBG_BF_ASSERT(0, "STRIP"); //STRIP001 /*?*/ 			SmDistanceDialog *pDistanceDialog = new SmDistanceDialog(NULL);
//STRIP001 /*?*/ 
//STRIP001 /*?*/ 			pDistanceDialog->ReadFrom(GetFormat());
//STRIP001 /*?*/ 			if (pDistanceDialog->Execute() == RET_OK)
//STRIP001 /*?*/ 			{
//STRIP001 /*?*/ 				SmFormat& rOldFormat  = GetFormat();
//STRIP001 /*?*/ 
//STRIP001 /*?*/ 				pDistanceDialog->WriteTo(GetFormat());
//STRIP001 /*?*/ 
//STRIP001 /*?*/ 				SfxUndoManager *pUndoMgr = GetUndoManager();
//STRIP001 /*?*/ 				if (pUndoMgr)
//STRIP001 /*?*/ 					pUndoMgr->AddUndoAction(
//STRIP001 /*?*/ 						new SmFormatAction(this, rOldFormat, GetFormat()));
//STRIP001 /*?*/ 
//STRIP001 /*?*/ 				if (aText.Len ())
//STRIP001 /*?*/ 				{
//STRIP001 /*?*/ 					SetModified(TRUE);
//STRIP001 /*?*/ 					if (pBindings)
//STRIP001 /*?*/ 						pBindings->Invalidate(SID_GRAPHIC);
//STRIP001 /*?*/ 				}
//STRIP001 /*?*/ 				else
//STRIP001 /*?*/ 					SetModified (FALSE);
//STRIP001 /*?*/ 			}
//STRIP001 /*?*/ 			delete pDistanceDialog;
//STRIP001 /*?*/ 			RestartFocusTimer ();
/*?*/ 		}
/*?*/ 		break;
/*?*/ 
/*?*/ 	case SID_ALIGN:
/*?*/ 		{
/*?*/ 			DBG_BF_ASSERT(0, "STRIP"); //STRIP001 /*?*/ 			SmAlignDialog *pAlignDialog = new SmAlignDialog(NULL);
//STRIP001 /*?*/ 
//STRIP001 /*?*/ 			pAlignDialog->ReadFrom(GetFormat());
//STRIP001 /*?*/ 			if (pAlignDialog->Execute() == RET_OK)
//STRIP001 /*?*/ 			{
//STRIP001 /*?*/                 SmFormat aOldFormat(GetFormat());
//STRIP001 /*?*/ 
//STRIP001 /*?*/ 				pAlignDialog->WriteTo(GetFormat());
//STRIP001 /*?*/ 
//STRIP001 /*?*/                 SmModule *pp = SM_MOD1();
//STRIP001 /*?*/                 SmFormat aFmt( pp->GetConfig()->GetStandardFormat() );
//STRIP001 /*?*/                 pAlignDialog->WriteTo( aFmt );
//STRIP001 /*?*/                 pp->GetConfig()->SetStandardFormat( aFmt );
//STRIP001 /*?*/ 
//STRIP001 /*?*/ 				SfxUndoManager *pUndoMgr = GetUndoManager();
//STRIP001 /*?*/ 				if (pUndoMgr)
//STRIP001 /*?*/ 					pUndoMgr->AddUndoAction(
//STRIP001 /*?*/                         new SmFormatAction(this, aOldFormat, GetFormat()));
//STRIP001 /*?*/ 
//STRIP001 /*?*/ 				if (aText.Len ())
//STRIP001 /*?*/ 				{
//STRIP001 /*?*/ 					SetModified(TRUE);
//STRIP001 /*?*/ 					if (pBindings)
//STRIP001 /*?*/ 						pBindings->Invalidate(SID_GRAPHIC);
//STRIP001 /*?*/ 				}
//STRIP001 /*?*/ 				else
//STRIP001 /*?*/ 					SetModified (FALSE);
//STRIP001 /*?*/ 			}
//STRIP001 /*?*/ 			delete pAlignDialog;
//STRIP001 /*?*/ 			RestartFocusTimer ();
/*?*/ 		}
/*N*/ 		break;
/*N*/ 
/*N*/ 	case SID_TEXT:
/*N*/ 		{
/*N*/ 			const SfxStringItem& rItem =
/*N*/ 				(const SfxStringItem&)rReq.GetArgs()->Get(SID_TEXT);
/*N*/ 
/*N*/ 			if (GetText() != rItem.GetValue())
/*N*/ 			{
/*?*/ 				SetText(rItem.GetValue());
/*N*/ 			}
/*N*/ 		}
/*N*/ 		break;
/*N*/ 
/*?*/ 	case SID_COPYOBJECT:
/*?*/ 		{
/*?*/     		Reference< datatransfer::XTransferable > xTrans(
/*?*/        										CreateTransferableSnapshot() );
/*?*/ 			if( xTrans.is() )
/*?*/ 			{
/*?*/ 				Reference< lang::XUnoTunnel> xTnnl( xTrans, uno::UNO_QUERY);
/*?*/ 				if( xTnnl.is() )
/*?*/ 				{
/*?*/ 					TransferableHelper* pTrans = (TransferableHelper*)
/*?*/ 						xTnnl->getSomething(
/*?*/ 								TransferableHelper::getUnoTunnelId() );
/*?*/ 					if( pTrans )
/*?*/ 						pTrans->CopyToClipboard( pViewSh
/*?*/ 											? pViewSh->GetEditWindow() : 0 );
/*?*/ 				}
/*?*/ 			}
/*?*/ 		}
/*?*/ 		break;
/*?*/ 
/*?*/ 	case SID_PASTEOBJECT:
/*?*/ 		{
/*?*/ 			TransferableDataHelper aData( TransferableDataHelper::
/*?*/ 				CreateFromSystemClipboard(pViewSh ? pViewSh->GetEditWindow()
/*?*/ 												  : 0) );
/*?*/ 			SotStorageStreamRef xStrm;
/*?*/ 			SotFormatStringId nId;
/*?*/ 			if( aData.GetTransferable().is() &&
/*?*/ 				( aData.HasFormat( nId = SOT_FORMATSTR_ID_EMBEDDED_OBJ ) ||
/*?*/ 				  (aData.HasFormat( SOT_FORMATSTR_ID_OBJECTDESCRIPTOR ) &&
/*?*/ 				   aData.HasFormat( nId = SOT_FORMATSTR_ID_EMBED_SOURCE ))) &&
/*?*/ 				aData.GetSotStorageStream( nId, xStrm ) && xStrm.Is() )
/*?*/ 			{
/*?*/ 				SvStorageRef xStore( new SvStorage( *xStrm ));
/*?*/ 				switch( xStore->GetFormat() )
/*?*/ 				{
/*?*/ 				case SOT_FORMATSTR_ID_STARMATH_60:
/*?*/ 				case SOT_FORMATSTR_ID_STARMATH_50:
/*?*/ 				case SOT_FORMATSTR_ID_STARMATH_40:
/*?*/ //??			case SOT_FORMATSTR_ID_STARMATH:
/*?*/ 					{DBG_BF_ASSERT(0, "STRIP");} //STRIP001 /*?*/ 					Insert( xStore );
/*?*/ 					break;
/*?*/                 default:
/*?*/                     DBG_ERROR( "unexpected format ID" );
/*?*/ 				}
/*?*/                 UpdateText();
/*?*/ 			}
/*?*/ 		}
/*?*/ 		break;
/*?*/ 
/*?*/ 	case SID_UNDO:
/*?*/ 	case SID_REDO:
/*?*/ 		{
/*?*/ 			SfxUndoManager* pUndoMgr = GetUndoManager();
/*?*/ 			if( pUndoMgr )
/*?*/ 			{
/*?*/ 				USHORT nId = rReq.GetSlot(), nCnt = 1;
/*?*/ 				const SfxItemSet* pArgs = rReq.GetArgs();
/*?*/ 				const SfxPoolItem* pItem;
/*?*/ 				if( pArgs && SFX_ITEM_SET == pArgs->GetItemState( nId, FALSE, &pItem ))
/*?*/ 					nCnt = ((SfxUInt16Item*)pItem)->GetValue();
/*?*/ 
/*?*/ 				BOOL (SfxUndoManager:: *fnDo)( USHORT );
/*?*/ 
/*?*/ 				sal_uInt16 nCount;
/*?*/ 				if( SID_UNDO == rReq.GetSlot() )
/*?*/ 				{
/*?*/ 					nCount = pUndoMgr->GetUndoActionCount();
/*?*/ 					fnDo = &SfxUndoManager::Undo;
/*?*/ 				}
/*?*/ 				else
/*?*/ 				{
/*?*/ 					nCount = pUndoMgr->GetRedoActionCount();
/*?*/ 					fnDo = &SfxUndoManager::Redo;
/*?*/ 				}
/*?*/ 
/*?*/ 				for( ; nCnt && nCount; --nCnt, --nCount )
/*?*/ 					(pUndoMgr->*fnDo)( 0 );
/*?*/ 			}
/*?*/ 		}
/*N*/ 		break;
/*N*/ 	}
/*N*/ }


/*N*/ void SmDocShell::GetState(SfxItemSet &rSet)
/*N*/ {
/*N*/ 	SfxWhichIter aIter(rSet);
/*N*/ 
/*N*/ 	for (USHORT nWh = aIter.FirstWhich();  0 != nWh;  nWh = aIter.NextWhich())
/*N*/ 	{
/*N*/ 		switch (nWh)
/*N*/ 		{
/*?*/ 		case SID_TEXTMODE:
/*?*/ 			rSet.Put(SfxBoolItem(SID_TEXTMODE, GetFormat().IsTextmode()));
/*?*/ 			break;
/*?*/ 
/*?*/ 		case SID_DOCTEMPLATE :
/*?*/ 			rSet.DisableItem (SID_DOCTEMPLATE);
/*?*/ 			break;
/*?*/ 
/*?*/ 		case SID_AUTO_REDRAW :
/*?*/ 			{
/*?*/ 				SmModule  *pp = SM_MOD1();
/*?*/ 				BOOL	   bRedraw = pp->GetConfig()->IsAutoRedraw();
/*?*/ 
/*?*/ 				rSet.Put (SfxBoolItem(SID_AUTO_REDRAW, bRedraw));
/*?*/ 			}
/*?*/ 			break;
/*?*/ 
/*?*/ 		case SID_TOOLBOX:
/*?*/ 			{
/*?*/ 				BOOL bState = FALSE;
/*?*/ 				SmViewShell *pView = SmGetActiveView();
/*?*/ 				if (pView)
/*?*/ 				{DBG_BF_ASSERT(0, "STRIP"); //STRIP001 
//STRIP001 /*?*/ 					SfxChildWindow *pChildWnd = pView->GetViewFrame()->
//STRIP001 /*?*/ 							GetChildWindow( SmToolBoxWrapper::GetChildWindowId() );
//STRIP001 /*?*/ 
//STRIP001 /*?*/ 					if (pChildWnd  &&  pChildWnd->GetWindow()->IsVisible())
//STRIP001 /*?*/ 						bState = TRUE;
/*?*/ 				}
/*?*/ 				rSet.Put(SfxBoolItem(SID_TOOLBOX, bState));
/*?*/ 			}
/*N*/ 			break;
/*N*/ 
/*N*/ 		case SID_MODIFYSTATUS:
/*N*/ 			{
/*N*/ 				sal_Unicode cMod = ' ';
/*N*/ 				if (IsModified())
/*?*/ 					cMod = '*';
/*N*/ 				rSet.Put(SfxStringItem(SID_MODIFYSTATUS, String(cMod)));
/*N*/ 			}
/*N*/ 			break;
/*N*/ 
/*N*/ 		case SID_TEXT:
/*N*/ 			rSet.Put(SfxStringItem(SID_TEXT, GetText()));
/*N*/ 			break;
/*N*/ 
/*N*/ 		case SID_GRAPHIC:
/*N*/ 			rSet.Put(SfxInt16Item(SID_GRAPHIC, nModifyCount));
/*N*/ 			break;
/*N*/ 
/*N*/ 		case SID_UNDO:
/*N*/ 		case SID_REDO:
/*N*/ 			{
/*N*/ 				SfxViewFrame* pFrm = SfxViewFrame::GetFirst( this );
/*N*/ 				if( pFrm )
/*N*/ 					pFrm->GetSlotState( nWh, NULL, &rSet );
/*N*/ 				else
/*?*/ 					rSet.DisableItem( nWh );
/*N*/ 			}
/*N*/ 			break;
/*N*/ 
/*N*/ 		case SID_GETUNDOSTRINGS:
/*N*/ 		case SID_GETREDOSTRINGS:
/*N*/ 			{
/*?*/ 				SfxUndoManager* pUndoMgr = GetUndoManager();
/*?*/ 				if( pUndoMgr )
/*?*/ 				{
/*?*/ 					UniString (SfxUndoManager:: *fnGetComment)( USHORT ) const;
/*?*/ 
/*?*/ 					sal_uInt16 nCount;
/*?*/ 					if( SID_GETUNDOSTRINGS == nWh )
/*?*/ 					{
/*?*/ 						nCount = pUndoMgr->GetUndoActionCount();
/*?*/ 						fnGetComment = &SfxUndoManager::GetUndoActionComment;
/*?*/ 					}
/*?*/ 					else
/*?*/ 					{
/*?*/ 						nCount = pUndoMgr->GetRedoActionCount();
/*?*/ 						fnGetComment = &SfxUndoManager::GetRedoActionComment;
/*?*/ 					}
/*?*/ 					if( nCount )
/*?*/ 					{
/*?*/ 						String sList;
/*?*/ 						for( sal_uInt16 n = 0; n < nCount; ++n )
/*?*/ 							( sList += (pUndoMgr->*fnGetComment)( n ) )
/*?*/ 									+= '\n';
/*?*/ 
/*?*/ 						SfxStringListItem aItem( nWh );
/*?*/ 						aItem.SetString( sList );
/*?*/ 						rSet.Put( aItem );
/*?*/ 					}
/*?*/ 				}
/*?*/ 				else
/*?*/ 					rSet.DisableItem( nWh );
/*N*/ 			}
/*N*/ 			break;
/*N*/ 		}
/*N*/ 	}
/*N*/ }


//STRIP001 SfxUndoManager *SmDocShell::GetUndoManager()
//STRIP001 {
//STRIP001 	if (!pEditEngine)
//STRIP001 		GetEditEngine();
//STRIP001 	return &pEditEngine->GetUndoManager();
//STRIP001 }



//STRIP001 void SmDocShell::SaveSymbols()
//STRIP001 {
//STRIP001 	GetSymSetManager().Save();
//STRIP001 }



//STRIP001 void SmDocShell::RestartFocusTimer ()
//STRIP001 {
//STRIP001 	SmCmdBoxWrapper *pWrapper = NULL;
//STRIP001 	SmViewShell *pView = SmGetActiveView();
//STRIP001 	if (pView)
//STRIP001 		pWrapper = (SmCmdBoxWrapper *) pView->GetViewFrame()->
//STRIP001 				GetChildWindow( SmCmdBoxWrapper::GetChildWindowId() );
//STRIP001 
//STRIP001 	if (pWrapper)
//STRIP001 		pWrapper->RestartFocusTimer ();
//STRIP001 }



//STRIP001 void SmDocShell::Draw(OutputDevice *pDevice,
//STRIP001 					  const JobSetup &,
//STRIP001 					  USHORT nAspect)
//STRIP001 {
//STRIP001 	pDevice->IntersectClipRegion(GetVisArea());
//STRIP001 	Point atmppoint;
//STRIP001 	Draw(*pDevice, atmppoint);
//STRIP001 }



/*N*/ void SmDocShell::HandsOff()
/*N*/ {
/*N*/ 	SfxInPlaceObject::HandsOff();
/*N*/ #if 0
/*N*/ 	aDocStream.Clear();
/*N*/ #endif
/*N*/ }


/*N*/ SfxItemPool& SmDocShell::GetPool()
/*N*/ {
/*N*/ 	return SFX_APP()->GetPool();
/*N*/ }

/*N*/ void SmDocShell::SetVisArea (const Rectangle & rVisArea)
/*N*/ {
/*N*/ 	Rectangle aNewRect (rVisArea);
/*N*/ 
/*N*/ 	aNewRect.SetPos(Point ());
/*N*/ 
/*N*/ 	if (! aNewRect.Right ()) aNewRect.Right () = 2000;
/*N*/ 	if (! aNewRect.Bottom ()) aNewRect.Bottom () = 1000;
/*N*/ 
/*N*/ 	BOOL bIsEnabled = IsEnableSetModified();
/*N*/ 	if ( bIsEnabled )
/*?*/ 		EnableSetModified( FALSE );
/*N*/ 
/*N*/ 	// If outplace editing, then dont resize the OutplaceWindow. But the
/*N*/ 	// ObjectShell has to resize. Bug 56470
/*N*/ 	BOOL bUnLockFrame;
/*N*/ 	if( ( GetProtocol().IsEmbed() || GetCreateMode() == SFX_CREATE_MODE_EMBEDDED ) && !GetProtocol().IsInPlaceActive() && GetFrame() )
/*N*/ 	{
/*?*/ 		GetFrame()->LockAdjustPosSizePixel();
/*?*/ 		bUnLockFrame = TRUE;
/*N*/ 	}
/*N*/ 	else
/*N*/ 		bUnLockFrame = FALSE;
/*N*/ 
/*N*/ 	SfxInPlaceObject::SetVisArea( aNewRect );
/*N*/ 
/*N*/ 	if( bUnLockFrame )
/*?*/ 		GetFrame()->UnlockAdjustPosSizePixel();
/*N*/ 
/*N*/ 	if ( bIsEnabled )
/*?*/ 		EnableSetModified( bIsEnabled );
/*N*/ }


/*N*/ BOOL SmDocShell::Try3x (SvStorage *pStor,
/*N*/ 						StreamMode eMode)
/*N*/ 
/*N*/ {
/*N*/ 	BOOL bRet = FALSE;
/*N*/ 
/*N*/ 	SvStorageStreamRef aTempStream = pStor->OpenStream(
/*N*/ 								String::CreateFromAscii(pStarMathDoc), eMode);
/*N*/ 	aTempStream->SetVersion (pStor->GetVersion ());
/*N*/ 	GetPool().SetFileFormatVersion (USHORT(pStor->GetVersion()));
/*N*/ 	aTempStream->SetBufferSize(DOCUMENT_BUFFER_SIZE);
/*N*/ 	aTempStream->SetKey( pStor->GetKey() ); // Passwort setzen
/*N*/ 
/*N*/ 	if (aTempStream->GetError() == 0)
/*N*/ 	{
/*N*/ 		SvStream*	 pSvStream = aTempStream;
/*N*/ 		char		 cTag;
/*N*/ 		ULONG		 lIdent, lVersion;
/*N*/ 		long		 lTime;
/*N*/ 		ULONG		 lDate;
/*N*/ 		String		 aBuffer;
/*N*/         ByteString   aByteStr;
/*N*/ 
/*N*/ 		*pSvStream >> lIdent >> lVersion;
/*N*/ 
/*N*/ 		if ((lIdent == SM30IDENT) || (lIdent == SM30BIDENT) || (lIdent == SM304AIDENT))
/*N*/ 		{
/*N*/ 			DBG_ASSERT((lVersion == SM30VERSION) ||
/*N*/ 					   (lVersion == SM50VERSION), "Illegal file version");
/*N*/ 
/*N*/ 			*pSvStream >> cTag;
/*N*/             rtl_TextEncoding eEnc = RTL_TEXTENCODING_MS_1252;
/*N*/ 			while (cTag && !pSvStream->IsEof())
/*N*/ 			{
/*N*/ 				switch (cTag)
/*N*/ 				{
/*N*/ 					case 'T':
/*N*/                         pSvStream->ReadByteString( aByteStr );
/*N*/                         aText = ImportString( aByteStr );
/*N*/ 						Parse();
/*N*/ 						break;
/*N*/ 
/*N*/ 					case 'D':
/*?*/ 						pSvStream->ReadByteString(aBuffer, eEnc);
/*?*/ 						pSvStream->ReadByteString(aBuffer, eEnc);
/*?*/ 						*pSvStream >> lDate >> lTime;
/*?*/ 						pSvStream->ReadByteString(aBuffer, eEnc);
/*?*/ 						*pSvStream >> lDate >> lTime;
/*?*/ 						pSvStream->ReadByteString(aBuffer, eEnc);
/*?*/ 						break;
/*N*/ 
/*N*/ 					case 'F':
/*N*/ 						*pSvStream >> aFormat;
/*N*/ 						if (lIdent != SM304AIDENT)
/*?*/ 							aFormat.From300To304a ();
/*N*/ 						else if ( lVersion == SM30VERSION )
/*N*/ 						{
/*?*/ 							aFormat.SetDistance(DIS_LEFTSPACE, 100);
/*?*/ 							aFormat.SetDistance(DIS_RIGHTSPACE, 100);
/*?*/ 							aFormat.SetDistance(DIS_TOPSPACE, 100);
/*?*/ 							aFormat.SetDistance(DIS_BOTTOMSPACE, 100);
/*N*/ 						}
/*N*/ 						break;
/*N*/ 
/*N*/ 					case 'S':
/*N*/ 					{
/*N*/                         String      aTmp;
/*N*/                         USHORT      n;
/*N*/                         pSvStream->ReadByteString(aTmp, eEnc);
/*N*/                         *pSvStream >> n;
/*N*/ 						break;
/*N*/ 					}
/*N*/ 
/*N*/ 					default:
/*N*/ 						DBG_ASSERT((cTag != 0), "Illegal data tag");
/*N*/ 				}
/*N*/ 				*pSvStream >> cTag;
/*N*/ 			}
/*N*/ 
/*N*/ 			bRet = TRUE;
/*N*/ #if 0
/*N*/ 			aDocStream = aTempStream;
/*N*/ #endif
/*N*/ 		}
/*N*/ 	}
/*N*/ 
/*N*/ 	if (!bRet)
/*N*/ 	{
/*N*/ 		// kein Passwort gesetzt --> Datei marode
/*?*/ 		if (pStor->GetKey().Len() == 0)
/*?*/ 		{
/*?*/ 			SetError(ERRCODE_SFX_DOLOADFAILED);
/*?*/ 		}
/*?*/ 		// Passwort gesetzt --> war wohl falsch
/*?*/ 		else
/*?*/ 		{
/*?*/ 			SetError(ERRCODE_SFX_WRONGPASSWORD);
/*?*/ 		}
/*N*/ 	}
/*N*/ 
/*N*/ 	return bRet;
/*N*/ }



//STRIP001 BOOL SmDocShell::Try2x (SvStorage *pStor,
//STRIP001 						StreamMode eMode)
//STRIP001 {
//STRIP001 	SvStorageStreamRef aTempStream = pStor->OpenStream(C2S("\1Ole10Native"), eMode);
//STRIP001 	aTempStream->SetVersion (pStor->GetVersion ());
//STRIP001 	GetPool().SetFileFormatVersion(USHORT(pStor->GetVersion ()));
//STRIP001 
//STRIP001     if (aTempStream->GetError() == SVSTREAM_OK)
//STRIP001 	{
//STRIP001 		void ReadSM20SymSet(SvStream*, SmSymSet*);
//STRIP001 
//STRIP001 		SvStream*	 pSvStream = aTempStream;
//STRIP001 		char		 cTag;
//STRIP001 		ULONG		 lIdent, lVersion;
//STRIP001 		long		 lTime;
//STRIP001 		ULONG		 lDate;
//STRIP001 		UINT32		 lDataSize;
//STRIP001 		String		 aBuffer;
//STRIP001         ByteString   aByteStr;
//STRIP001 		SmSymSet	*pSymbolSet;
//STRIP001 
//STRIP001 		*pSvStream >> lDataSize >> lIdent >> lVersion;
//STRIP001 
//STRIP001 		if (lIdent == FRMIDENT)
//STRIP001 		{
//STRIP001 			DBG_ASSERT((lVersion == FRMVERSION), "Illegal file version");
//STRIP001 
//STRIP001 			*pSvStream >> cTag;
//STRIP001             rtl_TextEncoding eEnc = RTL_TEXTENCODING_MS_1252;
//STRIP001 			while (cTag && !pSvStream->IsEof())
//STRIP001 			{
//STRIP001 				switch (cTag)
//STRIP001 				{
//STRIP001 					case 'T':
//STRIP001                         pSvStream->ReadByteString( aByteStr );
//STRIP001                         aText = ImportString( aByteStr );
//STRIP001 						Parse();
//STRIP001 						break;
//STRIP001 
//STRIP001 					case 'D':
//STRIP001 						{
//STRIP001 							pSvStream->ReadByteString(aBuffer, eEnc);
//STRIP001 							pSvStream->ReadByteString(aBuffer, eEnc);
//STRIP001 							*pSvStream >> lDate >> lTime;
//STRIP001 							pSvStream->ReadByteString(aBuffer, eEnc);
//STRIP001 							*pSvStream >> lDate >> lTime;
//STRIP001 							pSvStream->ReadByteString(aBuffer, eEnc);
//STRIP001 						}
//STRIP001 						break;
//STRIP001 
//STRIP001 					case 'F':
//STRIP001 						{
//STRIP001 							//SmFormat aFormat;
//STRIP001 							aFormat.ReadSM20Format(*pSvStream);
//STRIP001 							aFormat.From300To304a ();
//STRIP001 						}
//STRIP001 						break;
//STRIP001 
//STRIP001 					case 'S':
//STRIP001 					{
//STRIP001 						pSymbolSet = new SmSymSet();
//STRIP001 						ReadSM20SymSet(pSvStream, pSymbolSet);
//STRIP001                         delete pSymbolSet;
//STRIP001 						break;
//STRIP001 					}
//STRIP001 
//STRIP001 					default:
//STRIP001 						DBG_ASSERT((cTag != 0), "Illegal data tag");
//STRIP001 				}
//STRIP001 				*pSvStream >> cTag;
//STRIP001 			}
//STRIP001 
//STRIP001 			return TRUE;
//STRIP001 		}
//STRIP001 	}
//STRIP001 
//STRIP001 	return FALSE;
//STRIP001 }


//STRIP001 void SmDocShell::UIActivate (BOOL bActivate)
//STRIP001 {
//STRIP001 	if (bActivate)
//STRIP001 	{
//STRIP001 		SfxInPlaceObject::UIActivate (bActivate);
//STRIP001 		SmCmdBoxWrapper *pWrapper = NULL;
//STRIP001 		SmViewShell *pView = SmGetActiveView();
//STRIP001 		if (pView)
//STRIP001 			pWrapper = (SmCmdBoxWrapper *)pView->GetViewFrame()->
//STRIP001 					GetChildWindow( SmCmdBoxWrapper::GetChildWindowId() );
//STRIP001 
//STRIP001 		if (pWrapper)
//STRIP001 			pWrapper->Grab ();
//STRIP001 	}
//STRIP001 	else
//STRIP001 	{
//STRIP001 		SmViewShell *pViewSh = SmGetActiveView();
//STRIP001 		if (pViewSh)
//STRIP001 		{
//STRIP001 			pViewSh->GetViewFrame()->GetDispatcher()->Execute(
//STRIP001 					SID_GETEDITTEXT, SFX_CALLMODE_STANDARD,
//STRIP001 					new SfxVoidItem (SID_GETEDITTEXT), 0L);
//STRIP001 			Resize();
//STRIP001 		}
//STRIP001 
//STRIP001         SfxInPlaceObject::UIActivate (bActivate);
//STRIP001 	}
//STRIP001 }


/*N*/ void SmDocShell::FillClass(SvGlobalName* pClassName,
/*N*/ 						   ULONG*  pFormat,
/*N*/ 						   String* pAppName,
/*N*/ 						   String* pFullTypeName,
/*N*/ 						   String* pShortTypeName,
/*N*/ 						   long    nFileFormat) const
/*N*/ {
/*N*/ 	SfxInPlaceObject::FillClass(pClassName, pFormat, pAppName, pFullTypeName,
/*N*/ 								pShortTypeName, nFileFormat);
/*N*/ 
/*N*/ 	if (nFileFormat == SOFFICE_FILEFORMAT_31)
/*N*/ 	{
/*N*/ 		*pClassName 	= SvGlobalName(BF_SO3_SM_CLASSID_30);
/*N*/ 		*pFormat		= SOT_FORMATSTR_ID_STARMATH;
/*N*/ 		pAppName->AssignAscii( RTL_CONSTASCII_STRINGPARAM("Smath 3.1"));
/*N*/ 		*pFullTypeName	= String(SmResId(STR_MATH_DOCUMENT_FULLTYPE_31));
/*N*/ 		*pShortTypeName = String(SmResId(RID_DOCUMENTSTR));
/*N*/ 	}
/*N*/ 	else if (nFileFormat == SOFFICE_FILEFORMAT_40)
/*N*/ 	{
/*N*/ 		*pClassName 	= SvGlobalName(BF_SO3_SM_CLASSID_40);
/*N*/ 		*pFormat		= SOT_FORMATSTR_ID_STARMATH_40;
/*N*/ 		*pFullTypeName	= String(SmResId(STR_MATH_DOCUMENT_FULLTYPE_40));
/*N*/ 		*pShortTypeName = String(SmResId(RID_DOCUMENTSTR));
/*N*/ 	}
/*N*/ 	else if (nFileFormat == SOFFICE_FILEFORMAT_50)
/*N*/ 	{
/*N*/ 		*pClassName 	= SvGlobalName(BF_SO3_SM_CLASSID_50);
/*N*/ 		*pFormat		= SOT_FORMATSTR_ID_STARMATH_50;
/*N*/ 		*pFullTypeName	= String(SmResId(STR_MATH_DOCUMENT_FULLTYPE_50));
/*N*/ 		*pShortTypeName = String(SmResId(RID_DOCUMENTSTR));
/*N*/ 	}
/*N*/ 	else if (nFileFormat == SOFFICE_FILEFORMAT_60 )
/*N*/ 	{
/*N*/ 		*pFullTypeName	= String(SmResId(STR_MATH_DOCUMENT_FULLTYPE_60));
/*N*/ 		*pShortTypeName = String(SmResId(RID_DOCUMENTSTR));

            // for binfilter, we need the FormatIDs to be set. Not setting them
            // has always been an error (!)
             *pClassName 	= SvGlobalName(BF_SO3_SM_CLASSID_60);
             *pFormat		= SOT_FORMATSTR_ID_STARMATH_60;

/*N*/ 	}
/*N*/ }


/*N*/ ULONG SmDocShell::GetMiscStatus() const
/*N*/ {
/*N*/ 	return SfxInPlaceObject::GetMiscStatus() | SVOBJ_MISCSTATUS_NOTRESIZEABLE
/*N*/ 											 | SVOBJ_MISCSTATUS_RESIZEONPRINTERCHANGE;
/*N*/ }

/*N*/ void SmDocShell::SetModified(BOOL bModified)
/*N*/ {
/*N*/ 	if( IsEnableSetModified() )
/*N*/ 		SfxObjectShell::SetModified( bModified );
/*N*/ 	Broadcast(SfxSimpleHint(SFX_HINT_DOCCHANGED));
/*N*/ }

//STRIP001 BOOL SmDocShell::WriteAsMathType3( SfxMedium& rMedium )
//STRIP001 {
//STRIP001 	MathType aEquation( aText, pTree );
//STRIP001 	BOOL bRet = 0 != aEquation.ConvertFromStarMath( rMedium.GetStorage() );
//STRIP001 	return bRet;
//STRIP001 }



}
