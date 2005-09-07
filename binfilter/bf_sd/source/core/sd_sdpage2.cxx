/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: sd_sdpage2.cxx,v $
 *
 *  $Revision: 1.8 $
 *
 *  last change: $Author: rt $ $Date: 2005-09-07 23:24:33 $
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

#ifndef _SFXDOCFILE_HXX //autogen
#include <bf_sfx2/docfile.hxx>
#endif

// auto strip #ifndef _SV_SVAPP_HXX
// auto strip #include <vcl/svapp.hxx>
// auto strip #endif
// auto strip #ifndef _OUTLINER_HXX
// auto strip #include <bf_svx/outliner.hxx>
// auto strip #endif
#ifndef _SVXLINK_HXX
#include <bf_svx/linkmgr.hxx>
#endif
#ifndef _SVDOTEXT_HXX //autogen
#include <bf_svx/svdotext.hxx>
#endif
// auto strip #ifndef _URLOBJ_HXX //autogen
// auto strip #include <tools/urlobj.hxx>
// auto strip #endif
// auto strip #ifndef _OUTLOBJ_HXX //autogen
// auto strip #include <bf_svx/outlobj.hxx>
// auto strip #endif
#include <svtools/urihelper.hxx>

#ifndef _SVX_XMLCNITM_HXX
#include <bf_svx/xmlcnitm.hxx>
#endif

#ifndef _SVDITER_HXX
#include <bf_svx/svditer.hxx>
#endif

// auto strip #ifndef _LIST_HXX
// auto strip #include <tools/list.hxx>
// auto strip #endif

// auto strip #include "sdresid.hxx"
#include "sdpage.hxx"
#include "glob.hxx"
#include "glob.hrc"
#include "drawdoc.hxx"
#include "stlpool.hxx"
#include "sdiocmpt.hxx"
#include "pglink.hxx"
#include "strmname.h"
#include "anminfo.hxx"

#ifdef MAC
#include "::ui:inc:strings.hrc"
// auto strip #include "::ui:inc:docshell.hxx"
#else
#ifdef UNX
#include "../ui/inc/strings.hrc"
#include "../ui/inc/docshell.hxx"
#else
// auto strip #include "..\ui\inc\cfgids.hxx"
#include "..\ui\inc\strings.hrc"
#include "..\ui\inc\docshell.hxx"
#endif
#endif

// #90477#
#ifndef _TOOLS_TENCCVT_HXX
#include <tools/tenccvt.hxx>
#endif
#include "so3/staticbaseurl.hxx"
namespace binfilter {

using namespace ::com::sun::star;

/*************************************************************************
|*
|* SetPresentationLayout, setzt: Layoutnamen, Masterpage-Verkn�pfung und
|* Vorlagen fuer Praesentationsobjekte
|*
|* Vorraussetzungen: - Die Seite muss bereits das richtige Model kennen!
|*					 - Die entsprechende Masterpage muss bereits im Model sein.
|*					 - Die entsprechenden StyleSheets muessen bereits im
|*					   im StyleSheetPool sein.
|*
|*  bReplaceStyleSheets = TRUE : Benannte StyleSheets werden ausgetauscht
|*                        FALSE: Alle StyleSheets werden neu zugewiesen
|*
|*  bSetMasterPage      = TRUE : MasterPage suchen und zuweisen
|*
|*  bReverseOrder       = FALSE: MasterPages von vorn nach hinten suchen
|*                        TRUE : MasterPages von hinten nach vorn suchen (fuer Undo-Action)
|*
\************************************************************************/

//STRIP001 void SdPage::SetPresentationLayout(const String& rLayoutName,
//STRIP001 								   BOOL bReplaceStyleSheets,
//STRIP001 								   BOOL bSetMasterPage,
//STRIP001 								   BOOL bReverseOrder)
//STRIP001 {
//STRIP001 	/*********************************************************************
//STRIP001 	|* Layoutname der Seite
//STRIP001 	\********************************************************************/
//STRIP001 	String aOldLayoutName(aLayoutName); 	// merken
//STRIP001 	aLayoutName = rLayoutName;
//STRIP001 	aLayoutName.AppendAscii( RTL_CONSTASCII_STRINGPARAM( SD_LT_SEPARATOR ));
//STRIP001 	aLayoutName += String(SdResId(STR_LAYOUT_OUTLINE));
//STRIP001 
//STRIP001 	/*********************************************************************
//STRIP001 	|* ggf. Masterpage suchen und setzen
//STRIP001 	\********************************************************************/
//STRIP001 	if (bSetMasterPage && !IsMasterPage())
//STRIP001 	{
//STRIP001 		SdPage* pMaster;
//STRIP001 		USHORT nMaster = 0;
//STRIP001 		USHORT nMasterCount = pModel->GetMasterPageCount();
//STRIP001 
//STRIP001 		if( !bReverseOrder )
//STRIP001 		{
//STRIP001 			for ( nMaster = 0; nMaster < nMasterCount; nMaster++ )
//STRIP001 			{
//STRIP001 				pMaster = (SdPage*)pModel->GetMasterPage(nMaster);
//STRIP001 				if (pMaster->GetPageKind() == ePageKind &&
//STRIP001 					pMaster->GetLayoutName() == aLayoutName)
//STRIP001 				{
//STRIP001 					break;
//STRIP001 				}
//STRIP001 			}
//STRIP001 		}
//STRIP001 		else
//STRIP001 		{
//STRIP001 			for ( nMaster = nMasterCount - 1; nMaster >= 0; nMaster-- )
//STRIP001 			{
//STRIP001 				pMaster = (SdPage*)pModel->GetMasterPage(nMaster);
//STRIP001 				if (pMaster->GetPageKind() == ePageKind &&
//STRIP001 					pMaster->GetLayoutName() == aLayoutName)
//STRIP001 				{
//STRIP001 					break;
//STRIP001 				}
//STRIP001 			}
//STRIP001 		}
//STRIP001 
//STRIP001 		DBG_ASSERT(nMaster < nMasterCount, "Masterpage nicht gefunden");
//STRIP001 
//STRIP001 		// falls es eine oder mehrere Masterpages gibt: die 1. ersetzen
//STRIP001 		if (GetMasterPageCount() > 0)
//STRIP001 			SetMasterPageNum(nMaster, 0);
//STRIP001 		// sonst: als 1. Masterpage einfuegen
//STRIP001 		else
//STRIP001 			InsertMasterPage(nMaster);
//STRIP001 	}
//STRIP001 
//STRIP001 	/*********************************************************************
//STRIP001 	|* Vorlagen fuer Praesentationsobjekte
//STRIP001 	\********************************************************************/
//STRIP001 	// Listen mit:
//STRIP001 	// - Vorlagenzeigern fuer Gliederungstextobjekt (alte und neue Vorlagen)
//STRIP001 	// -Replacedaten fuer OutlinerParaObject
//STRIP001 	List aOutlineStyles;
//STRIP001 	List aOldOutlineStyles;
//STRIP001 	List aReplList;
//STRIP001 	BOOL bListsFilled = FALSE;
//STRIP001 
//STRIP001 	ULONG nObjCount = GetObjCount();
//STRIP001 
//STRIP001 	for (ULONG nObj = 0; nObj < nObjCount; nObj++)
//STRIP001 	{
//STRIP001 		SdrTextObj* pObj = (SdrTextObj*) GetObj(nObj);
//STRIP001 
//STRIP001 		if (pObj->GetObjInventor() == SdrInventor &&
//STRIP001 			pObj->GetObjIdentifier() == OBJ_OUTLINETEXT)
//STRIP001 		{
//STRIP001 			if (!bListsFilled || !bReplaceStyleSheets)
//STRIP001 			{
//STRIP001 				String aFullName;
//STRIP001 				String aOldFullName;
//STRIP001 				SfxStyleSheetBase* pSheet = NULL;
//STRIP001 				SfxStyleSheetBasePool* pStShPool = pModel->GetStyleSheetPool();
//STRIP001 
//STRIP001 				for (USHORT i = 1; i < 10; i++)
//STRIP001 				{
//STRIP001 					aFullName = aLayoutName;
//STRIP001 					aOldFullName = aOldLayoutName;
//STRIP001 					aFullName += sal_Unicode( ' ' );
//STRIP001 					aFullName += String::CreateFromInt32( (sal_Int32)i );
//STRIP001 					aOldFullName += sal_Unicode( ' ' );
//STRIP001 					aOldFullName += String::CreateFromInt32( (sal_Int32)i );
//STRIP001 
//STRIP001 					pSheet = pStShPool->Find(aOldFullName, SD_LT_FAMILY);
//STRIP001 					DBG_ASSERT(pSheet, "alte Gliederungsvorlage nicht gefunden");
//STRIP001 					aOldOutlineStyles.Insert(pSheet, LIST_APPEND);
//STRIP001 
//STRIP001 					pSheet = pStShPool->Find(aFullName, SD_LT_FAMILY);
//STRIP001 					DBG_ASSERT(pSheet, "neue Gliederungsvorlage nicht gefunden");
//STRIP001 					aOutlineStyles.Insert(pSheet, LIST_APPEND);
//STRIP001 
//STRIP001 					if (bReplaceStyleSheets && pSheet)
//STRIP001 					{
//STRIP001 						// Replace anstatt Set
//STRIP001 						StyleReplaceData* pReplData = new StyleReplaceData;
//STRIP001 						pReplData->nNewFamily = pSheet->GetFamily();
//STRIP001 						pReplData->nFamily    = pSheet->GetFamily();
//STRIP001 						pReplData->aNewName   = aFullName;
//STRIP001 						pReplData->aName      = aOldFullName;
//STRIP001 						aReplList.Insert(pReplData, LIST_APPEND);
//STRIP001 					}
//STRIP001 					else
//STRIP001 					{
//STRIP001 		            	OutlinerParaObject* pOPO = ((SdrTextObj*)pObj)->GetOutlinerParaObject();
//STRIP001 
//STRIP001                         if( pOPO )
//STRIP001 						    pOPO->SetStyleSheets( i,  aFullName, SD_LT_FAMILY );
//STRIP001 					}
//STRIP001 				}
//STRIP001 
//STRIP001 				bListsFilled = TRUE;
//STRIP001 			}
//STRIP001 
//STRIP001 			SfxStyleSheet* pSheet = (SfxStyleSheet*)aOutlineStyles.First();
//STRIP001 			SfxStyleSheet* pOldSheet = (SfxStyleSheet*)aOldOutlineStyles.First();
//STRIP001 			while (pSheet)
//STRIP001 			{
//STRIP001 				if (pSheet != pOldSheet)
//STRIP001 				{
//STRIP001 					pObj->EndListening(*pOldSheet);
//STRIP001 
//STRIP001 					if (!pObj->IsListening(*pSheet))
//STRIP001 						pObj->StartListening(*pSheet);
//STRIP001 				}
//STRIP001 
//STRIP001 				pSheet = (SfxStyleSheet*)aOutlineStyles.Next();
//STRIP001 				pOldSheet = (SfxStyleSheet*)aOldOutlineStyles.Next();
//STRIP001 			}
//STRIP001 
//STRIP001 			OutlinerParaObject* pOPO = ((SdrTextObj*)pObj)->GetOutlinerParaObject();
//STRIP001 			if ( bReplaceStyleSheets && pOPO )
//STRIP001 			{
//STRIP001 				StyleReplaceData* pReplData = (StyleReplaceData*) aReplList.First();
//STRIP001 
//STRIP001 				while( pReplData )
//STRIP001 				{
//STRIP001 					pOPO->ChangeStyleSheets( pReplData->aName, pReplData->nFamily, pReplData->aNewName, pReplData->nNewFamily );
//STRIP001 					pReplData = (StyleReplaceData*) aReplList.Next();
//STRIP001 				}
//STRIP001 			}
//STRIP001 		}
//STRIP001 		else if (pObj->GetObjInventor() == SdrInventor &&
//STRIP001 				 pObj->GetObjIdentifier() == OBJ_TITLETEXT)
//STRIP001 		{
//STRIP001 			// PresObjKind nicht ueber GetPresObjKind() holen, da dort nur
//STRIP001 			// die PresObjListe beruecksichtigt wird. Es sollen aber alle
//STRIP001 			// "Titelobjekte" hier beruecksichtigt werden (Paste aus Clipboard usw.)
//STRIP001 			SfxStyleSheet* pSheet = GetStyleSheetForPresObj(PRESOBJ_TITLE);
//STRIP001 
//STRIP001 			if (pSheet)
//STRIP001 				pObj->SetStyleSheet(pSheet, TRUE);
//STRIP001 		}
//STRIP001 		else
//STRIP001 		{
//STRIP001 			SfxStyleSheet* pSheet = GetStyleSheetForPresObj(GetPresObjKind(pObj));
//STRIP001 
//STRIP001 			if (pSheet)
//STRIP001 				pObj->SetStyleSheet(pSheet, TRUE);
//STRIP001 		}
//STRIP001 	}
//STRIP001 
//STRIP001 	for (ULONG i = 0; i < aReplList.Count(); i++)
//STRIP001 	{
//STRIP001 		delete (StyleReplaceData*) aReplList.GetObject(i);
//STRIP001 	}
//STRIP001 }


/*************************************************************************
|*
|* das Gliederungstextobjekt bei den Vorlagen fuer die Gliederungsebenen
|* abmelden
|*
\************************************************************************/

/*N*/ void SdPage::EndListenOutlineText()
/*N*/ {
/*N*/ 	SdrObject* pOutlineTextObj = GetPresObj(PRESOBJ_OUTLINE);
/*N*/ 
/*N*/ 	if (pOutlineTextObj)
/*N*/ 	{
/*N*/ 		SdStyleSheetPool* pSPool = (SdStyleSheetPool*)pModel->GetStyleSheetPool();
/*N*/ 		DBG_ASSERT(pSPool, "StyleSheetPool nicht gefunden");
/*N*/ 		String aTrueLayoutName(aLayoutName);
/*N*/ 		aTrueLayoutName.Erase( aTrueLayoutName.SearchAscii( SD_LT_SEPARATOR ));
/*N*/ 		List* pOutlineStyles = pSPool->CreateOutlineSheetList(aTrueLayoutName);
/*N*/ 		for (SfxStyleSheet* pSheet = (SfxStyleSheet*)pOutlineStyles->First();
/*N*/ 			 pSheet;
/*N*/ 			 pSheet = (SfxStyleSheet*)pOutlineStyles->Next())
/*N*/ 			{
/*N*/ 				pOutlineTextObj->EndListening(*pSheet);
/*N*/ 			}
/*N*/ 
/*N*/ 		delete pOutlineStyles;
/*N*/ 	}
/*N*/ }

/*************************************************************************
|*
|* schreibt Member der SdPage
|*
\************************************************************************/

/*N*/ void SdPage::WriteData(SvStream& rOut) const
/*N*/ {
/*N*/ 	FmFormPage::WriteData( rOut );
/*N*/ 	// #90477# rOut.SetStreamCharSet( ::GetStoreCharSet( gsl_getSystemTextEncoding()));
/*N*/ 	rOut.SetStreamCharSet(GetSOStoreTextEncoding(gsl_getSystemTextEncoding(), (sal_uInt16)rOut.GetVersion()));
/*N*/ 
/*N*/ 	if ( pModel->IsStreamingSdrModel() )
/*N*/ 	{
/*N*/ 		// Es wird nur das SdrModel gestreamt, nicht das SdDrawDocument!
/*N*/ 		// Anwendungsfall: svdraw Clipboard-Format
/*N*/ 		return;
/*N*/ 	}
/*N*/ 
/*N*/ 	// letzter Parameter ist die aktuelle Versionsnummer des Codes
/*N*/ 	SdIOCompat aIO(rOut, STREAM_WRITE, 7);
/*N*/ 
/*N*/ 	BOOL bDummy = TRUE;
/*N*/ 	BOOL bManual = ( PRESCHANGE_MANUAL == ePresChange ); // nur der Kompat.halber
/*N*/ 
/*N*/ 	rOut<<bDummy;					   // ehem. bTemplateMode
/*N*/ 	rOut<<bDummy;					   // ehem. bBackgroundMode
/*N*/ 	rOut<<bDummy;					   // ehem. bOutlineMode
/*N*/ 
/*N*/ 	UINT16 nUI16Temp = (UINT16) eAutoLayout;
/*N*/ 	rOut << nUI16Temp;
/*N*/ 
/*N*/ 	// Selektionskennung ist nicht persistent, wird nicht geschrieben
/*N*/ 
/*N*/ 	ULONG nULTemp;
/*N*/ 	nULTemp = (ULONG)eFadeSpeed;
/*N*/ 	rOut << nULTemp;
/*N*/ 	nULTemp = (ULONG)eFadeEffect;
/*N*/ 	rOut << nULTemp;
/*N*/ 	rOut << bManual;
/*N*/ 	rOut << nTime;
/*N*/ 	rOut << bSoundOn;
/*N*/ 	rOut << bExcluded;
/*N*/ 	rOut.WriteByteString( aLayoutName );
/*N*/ 
/*N*/ 	// Liste der Praesentationsobjekt abspeichern
/*N*/ 	UINT32 nUserCallCount = 0;
/*N*/ 	UINT32 nCount = (UINT32)aPresObjList.Count();
/*N*/ 	UINT32 nValidCount = nCount;
/*N*/ 
/*N*/ 	// NULL-Pointer rauszaehlen. Eigentlich haben die nichts in der Liste
/*N*/ 	// verloren, aber es gibt leider Kundenfiles, in denen so was vorkommt.
/*N*/ 	UINT32 nObj; for (nObj = 0; nObj < nCount; nObj++)
/*N*/ 	{
/*N*/ 		SdrObject* pObj = (SdrObject*)aPresObjList.GetObject(nObj);
/*N*/ 		if (!pObj)
/*N*/ 			nValidCount--;
/*N*/ 	}
/*N*/ 	rOut << nValidCount;
/*N*/ 
/*N*/ 	for (nObj = 0; nObj < nCount; nObj++)
/*N*/ 	{
/*N*/ 		SdrObject* pObj = (SdrObject*)aPresObjList.GetObject(nObj);
/*N*/ 		if (pObj)
/*N*/ 		{
/*N*/ 		   rOut << pObj->GetOrdNum();
/*N*/ 
/*N*/ 		   if ( ( (SdPage*) pObj->GetUserCall() ) == this)
/*N*/ 		   {
/*N*/ 			   nUserCallCount++;
/*N*/ 		   }
/*N*/ 		}
/*N*/ 	}
/*N*/ 
/*N*/ 	nUI16Temp = (UINT16)ePageKind;
/*N*/ 	rOut << nUI16Temp;
/*N*/ 
/*N*/ 	// Liste der Praesentationsobjekt abspeichern,
/*N*/ 	// welche einen UserCall auf die Seite haben
/*N*/ 	rOut << nUserCallCount;
/*N*/ 	for (nObj = 0; nObj < nCount; nObj++)
/*N*/ 	{
/*N*/ 		SdrObject* pObj = (SdrObject*)aPresObjList.GetObject(nObj);
/*N*/ 
/*N*/ 		if ( pObj && ( (SdPage*) pObj->GetUserCall() ) == this)
/*N*/ 		{
/*N*/ 			rOut << pObj->GetOrdNum();
/*N*/ 		}
/*N*/ 	}
/*N*/ 
/*N*/ 	// #90477# INT16 nI16Temp = ::GetStoreCharSet( gsl_getSystemTextEncoding() );  // .EXEs vor 303 werten den aus
/*N*/ 	INT16 nI16Temp = GetSOStoreTextEncoding(gsl_getSystemTextEncoding(), (sal_uInt16)rOut.GetVersion());  
/*N*/ 	
/*N*/ 	rOut << nI16Temp;
/*N*/ 
/*N*/ 	rOut.WriteByteString( so3::StaticBaseUrl::AbsToRel(aSoundFile,
/*N*/ 												  INetURLObject::WAS_ENCODED,
/*N*/ 												  INetURLObject::DECODE_UNAMBIGUOUS));
/*N*/ 	rOut.WriteByteString( so3::StaticBaseUrl::AbsToRel(aFileName,
/*N*/ 												  INetURLObject::WAS_ENCODED,
/*N*/ 												  INetURLObject::DECODE_UNAMBIGUOUS));
/*N*/ 	rOut.WriteByteString( aBookmarkName );
/*N*/ 
/*N*/ 	UINT16 nPaperBinTemp = nPaperBin;
/*N*/ 	rOut << nPaperBinTemp;
/*N*/ 
/*N*/ 	UINT16 nOrientationTemp = (UINT16) eOrientation;
/*N*/ 	rOut << nOrientationTemp;
/*N*/ 
/*N*/ 	UINT16 nPresChangeTemp = (UINT16) ePresChange; // ab 370 (IO-Version 7)
/*N*/ 	rOut << nPresChangeTemp;
/*N*/ }

/*************************************************************************
|*
|* liest Member der SdPage
|*
\************************************************************************/

/*N*/ void SdPage::ReadData(const SdrIOHeader& rHead, SvStream& rIn)
/*N*/ {
/*N*/ 	FmFormPage::ReadData( rHead, rIn );
/*N*/ 
/*N*/ 	// #90477# rIn.SetStreamCharSet( ::GetStoreCharSet( gsl_getSystemTextEncoding()));
/*N*/ 	rIn.SetStreamCharSet(GetSOLoadTextEncoding(gsl_getSystemTextEncoding(), (sal_uInt16)rIn.GetVersion()));
/*N*/ 
/*N*/ 	if ( pModel->IsStreamingSdrModel() )
/*N*/ 	{
/*N*/ 		// Es wird nur das SdrModel gestreamt, nicht das SdDrawDocument!
/*N*/ 		// Anwendungsfall: svdraw Clipboard-Format
/*N*/ 		return;
/*N*/ 	}
/*N*/ 
/*N*/ 	SdIOCompat aIO(rIn, STREAM_READ);
/*N*/ 
/*N*/ 	BOOL bDummy;
/*N*/ 	BOOL bManual;
/*N*/ 
/*N*/ 	rIn>>bDummy;					  // ehem. bTemplateMode
/*N*/ 	rIn>>bDummy;					  // ehem. bBackgroundMode
/*N*/ 	rIn>>bDummy;					  // ehem. bOutlineMode
/*N*/ 
/*N*/ 	UINT16 nAutoLayout;
/*N*/ 	rIn>>nAutoLayout;
/*N*/ 	eAutoLayout = (AutoLayout) nAutoLayout;
/*N*/ 
/*N*/ 	// Selektionskennung ist nicht persistent, wird nicht gelesen
/*N*/ 
/*N*/ 	ULONG nULTemp;
/*N*/ 	rIn >> nULTemp; eFadeSpeed	= (FadeSpeed)nULTemp;
/*N*/ 	rIn >> nULTemp; eFadeEffect = (presentation::FadeEffect)nULTemp;
/*N*/ 	rIn >> bManual;
/*N*/ 	rIn >> nTime;
/*N*/ 	rIn >> bSoundOn;
/*N*/ 	rIn >> bExcluded;
/*N*/ 	rIn.ReadByteString( aLayoutName );
/*N*/ 
/*N*/ 	// Liste der Praesentationsobjekt einlesen
/*N*/ 	if (IsObjOrdNumsDirty())		// Ordnungsnummern muessen dafuer stimmen
/*?*/ 		RecalcObjOrdNums();

/*N*/ 	UINT32 nCount;
/*N*/ 	UINT32 nOrdNum;
/*N*/ 	rIn >> nCount;
/*N*/ 	for (UINT32 nObj = 0; nObj < nCount; nObj++)
/*N*/ 	{
/*N*/ 		rIn >> nOrdNum;
/*N*/ 		SdrObject* pObj = GetObj(nOrdNum);
/*N*/ 		aPresObjList.Insert(pObj, LIST_APPEND);
/*N*/ 	}
/*N*/ 
/*N*/ 	// ab hier werden Daten der Versionen >=1 eingelesen
/*N*/ 	if (aIO.GetVersion() >= 1)
/*N*/ 	{
/*N*/ 		UINT16 nPageKind;
/*N*/ 		rIn >> nPageKind;
/*N*/ 		ePageKind = (PageKind) nPageKind;
/*N*/ 	}
/*N*/ 
/*N*/ 	// ab hier werden Daten der Versionen >=2 eingelesen
/*N*/ 	if (aIO.GetVersion() >=2)
/*N*/ 	{
/*N*/ 		UINT32 nUserCallCount;
/*N*/ 		UINT32 nUserCallOrdNum;
/*N*/ 		rIn >> nUserCallCount;
/*N*/ 		for (UINT32 nObj = 0; nObj < nUserCallCount; nObj++)
/*N*/ 		{
/*N*/ 			rIn >> nUserCallOrdNum;
/*N*/ 			SdrObject* pObj = GetObj(nUserCallOrdNum);
/*N*/ 
/*N*/ 			if (pObj)
/*N*/ 				pObj->SetUserCall(this);
/*N*/ 		}
/*N*/ 	}
/*N*/ 
/*N*/ 	// ab hier werden Daten der Versionen >=3 eingelesen
/*N*/ 	if (aIO.GetVersion() >=3)
/*N*/ 	{
/*N*/ 		INT16 nCharSet;
/*N*/ 		rIn >> nCharSet;	// nur Einlesen, Konvertierung ab 303 durch Stream
/*N*/ 		
/*N*/ 		// #90477# eCharSet = (CharSet) nCharSet;
/*N*/ 		eCharSet = (CharSet)GetSOLoadTextEncoding((rtl_TextEncoding)nCharSet, (sal_uInt16)rIn.GetVersion());
/*N*/ 
/*N*/ 		String aSoundFileRel;
/*N*/ 		rIn.ReadByteString( aSoundFileRel );
/*N*/ 		INetURLObject aURLObj(so3::StaticBaseUrl::SmartRelToAbs(aSoundFileRel, FALSE,
/*N*/ 														 INetURLObject::WAS_ENCODED,
/*N*/ 														 INetURLObject::DECODE_UNAMBIGUOUS));
/*N*/ 		aSoundFile = aURLObj.GetMainURL( INetURLObject::NO_DECODE );
/*N*/ 	}
/*N*/ 
/*N*/ 	// ab hier werden Daten der Versionen >=4 eingelesen
/*N*/ 	if (aIO.GetVersion() >=4)
/*N*/ 	{
/*N*/ 		String aFileNameRel;
/*N*/ 		rIn.ReadByteString( aFileNameRel );
/*N*/ 		INetURLObject aURLObj(so3::StaticBaseUrl::SmartRelToAbs(aFileNameRel, FALSE,
/*N*/ 														 INetURLObject::WAS_ENCODED,
/*N*/ 														 INetURLObject::DECODE_UNAMBIGUOUS));
/*N*/ 		aFileName = aURLObj.GetMainURL( INetURLObject::NO_DECODE );
/*N*/ 
/*N*/ 		rIn.ReadByteString( aBookmarkName );
/*N*/ 	}
/*N*/ 
/*N*/ 	// ab hier werden Daten der Versionen >=5 eingelesen
/*N*/ 	if (aIO.GetVersion() >=5)
/*N*/ 	{
/*N*/ 		UINT16 nPaperBinTemp;
/*N*/ 		rIn >> nPaperBinTemp;
/*N*/ 		nPaperBin = nPaperBinTemp;
/*N*/ 	}
/*N*/ 
/*N*/ 	// ab hier werden Daten der Versionen >=6 eingelesen
/*N*/ 	if (aIO.GetVersion() >=6)
/*N*/ 	{
/*N*/ 		UINT16 nOrientationTemp;
/*N*/ 		rIn >> nOrientationTemp;
/*N*/ 		eOrientation = (Orientation) nOrientationTemp;
/*N*/ 	}
/*N*/ 	else
/*N*/ 	{
/*N*/ 		// In aelteren Versionen wird die Orientation aus der Seitengroesse bestimmt
/*N*/ 		Size aPageSize(GetSize());
/*N*/ 
/*N*/ 		if (aPageSize.Width() > aPageSize.Height())
/*N*/ 		{
/*N*/ 			eOrientation = ORIENTATION_LANDSCAPE;
/*N*/ 		}
/*N*/ 		else
/*N*/ 		{
/*N*/ 			eOrientation = ORIENTATION_PORTRAIT;
/*N*/ 		}
/*N*/ 	}
/*N*/ 
/*N*/ 	// ab hier werden Daten der Versionen >=7 eingelesen
/*N*/ 	if( aIO.GetVersion() >= 7 )
/*N*/ 	{
/*N*/ 		UINT16 nPresChangeTemp;
/*N*/ 		rIn >> nPresChangeTemp;
/*N*/ 		ePresChange = (PresChange) nPresChangeTemp;
/*N*/ 	}
/*N*/ 	else
/*N*/ 		ePresChange = ( bManual ? PRESCHANGE_MANUAL : PRESCHANGE_AUTO );
/*N*/ }



/*************************************************************************
|*
|* Neues Model setzen
|*
\************************************************************************/

/*N*/ void SdPage::SetModel(SdrModel* pNewModel)
/*N*/ {
/*N*/ 	DisconnectLink();
/*N*/ 
/*N*/ 	// Model umsetzen
/*N*/ 	FmFormPage::SetModel(pNewModel);
/*N*/ 
/*N*/ 	ConnectLink();
/*N*/ }



/*************************************************************************
|*
|* Ist die Seite read-only?
|*
\************************************************************************/

//STRIP001 FASTBOOL SdPage::IsReadOnly() const
//STRIP001 {
//STRIP001 	BOOL bReadOnly = FALSE;
//STRIP001 
//STRIP001 	if (pPageLink)
//STRIP001 	{
//STRIP001 		// Seite ist gelinkt
//STRIP001 		// bReadOnly = TRUE wuerde dazu fuehren, dass diese Seite nicht
//STRIP001 		// bearbeitet werden kann. Dieser Effekt ist jedoch z.Z. nicht
//STRIP001 		// gewuenscht, daher auskommentiert:
//STRIP001 //		  bReadOnly = TRUE;
//STRIP001 	}
//STRIP001 
//STRIP001 	return (bReadOnly);
//STRIP001 }



/*************************************************************************
|*
|* Beim LinkManager anmelden
|*
\************************************************************************/

/*N*/ void SdPage::ConnectLink()
/*N*/ {
/*N*/ 	SvxLinkManager* pLinkManager = pModel!=NULL ? pModel->GetLinkManager() : NULL;
/*N*/ 
/*N*/ 	if (pLinkManager && !pPageLink && aFileName.Len() && aBookmarkName.Len() &&
/*N*/ 		ePageKind==PK_STANDARD && !IsMasterPage() &&
/*N*/ 		( (SdDrawDocument*) pModel)->IsNewOrLoadCompleted())
/*?*/ 	{
        /**********************************************************************
        * Anmelden
        * Nur Standardseiten duerfen gelinkt sein
        **********************************************************************/
/*?*/ 		SdDrawDocShell* pDocSh = ((SdDrawDocument*) pModel)->GetDocSh();
/*?*/ 
/*?*/ 		if (!pDocSh || pDocSh->GetMedium()->GetOrigURL() != aFileName)
/*?*/ 		{
/*?*/ 			// Keine Links auf Dokument-eigene Seiten!
/*?*/ 			DBG_BF_ASSERT(0, "STRIP"); //STRIP001 pPageLink = new SdPageLink(this, aFileName, aBookmarkName);
//STRIP001 /*?*/ 			String aFilterName(SdResId(STR_IMPRESS));
//STRIP001 /*?*/ 			pLinkManager->InsertFileLink(*pPageLink, OBJECT_CLIENT_FILE,
//STRIP001 /*?*/ 										 aFileName, &aFilterName, &aBookmarkName);
//STRIP001 /*?*/ 			pPageLink->Connect();
/*?*/ 		}
/*?*/ 	}
/*N*/ }


/*************************************************************************
|*
|* Beim LinkManager abmelden
|*
\************************************************************************/

/*N*/ void SdPage::DisconnectLink()
/*N*/ {
/*N*/ 	SvxLinkManager* pLinkManager = pModel!=NULL ? pModel->GetLinkManager() : NULL;
/*N*/ 
/*N*/ 	if (pLinkManager && pPageLink)
/*?*/ 	{
        /**********************************************************************
        * Abmelden
        * (Bei Remove wird *pGraphicLink implizit deleted)
        **********************************************************************/
/*?*/ 		pLinkManager->Remove(pPageLink);
/*?*/ 		pPageLink=NULL;
/*?*/ 	}
/*N*/ }


/*************************************************************************
|*
|* Copy-Ctor
|*
\************************************************************************/

/*N*/ SdPage::SdPage(const SdPage& rSrcPage) :
/*N*/ 	FmFormPage(rSrcPage),
/*N*/ 	mpItems(NULL)
/*N*/ {
/*N*/ 	ePageKind           = rSrcPage.ePageKind;
/*N*/ 	eAutoLayout         = rSrcPage.eAutoLayout;
/*N*/ 	bOwnArrangement     = FALSE;
/*N*/ 
/*N*/ 	UINT32 nCount = (UINT32) rSrcPage.aPresObjList.Count();
/*N*/ 
/*N*/ 	for (UINT32 nObj = 0; nObj < nCount; nObj++)
/*N*/ 	{
/*N*/ 		// Liste der Praesenationsobjekte fuellen
/*N*/ 		SdrObject* pSrcObj = (SdrObject*) rSrcPage.aPresObjList.GetObject(nObj);
/*N*/ 
/*N*/ 		if (pSrcObj)
/*N*/ 		{
/*N*/ 			aPresObjList.Insert(GetObj(pSrcObj->GetOrdNum()), LIST_APPEND);
/*N*/ 		}
/*N*/ 	}
/*N*/ 
/*N*/ 	bSelected           = FALSE;
/*N*/ 	eFadeSpeed          = rSrcPage.eFadeSpeed;
/*N*/ 	eFadeEffect         = rSrcPage.eFadeEffect;
/*N*/ 	ePresChange			= rSrcPage.ePresChange;
/*N*/ 	nTime               = rSrcPage.nTime;
/*N*/ 	bSoundOn            = rSrcPage.bSoundOn;
/*N*/ 	bExcluded           = rSrcPage.bExcluded;
/*N*/ 
/*N*/ 	aLayoutName         = rSrcPage.aLayoutName;
/*N*/ 	aSoundFile          = rSrcPage.aSoundFile;
/*N*/ 	aCreatedPageName    = String();
/*N*/ 	aFileName           = rSrcPage.aFileName;
/*N*/ 	aBookmarkName       = rSrcPage.aBookmarkName;
/*N*/ 	bScaleObjects       = rSrcPage.bScaleObjects;
/*N*/ 	bBackgroundFullSize = rSrcPage.bBackgroundFullSize;
/*N*/ 	eCharSet            = rSrcPage.eCharSet;
/*N*/ 	nPaperBin           = rSrcPage.nPaperBin;
/*N*/ 	eOrientation        = rSrcPage.eOrientation;
/*N*/ 
/*N*/ 	pPageLink           = NULL;    // Wird beim Einfuegen ueber ConnectLink() gesetzt
/*N*/ }



/*************************************************************************
|*
|* Clone
|*
\************************************************************************/

/*N*/ SdrPage* SdPage::Clone() const
/*N*/ {
/*N*/ 	SdPage* pPage = new SdPage(*this);
/*N*/ 
/*N*/ 	if( (PK_STANDARD == ePageKind) && !IsMasterPage() )
/*N*/ 	{
/*N*/ 		// preserve presentation order on slide duplications
/*N*/ 		SdrObjListIter aSrcIter( *this, IM_DEEPWITHGROUPS );
/*N*/ 		SdrObjListIter aDstIter( *pPage, IM_DEEPWITHGROUPS );
/*N*/ 
/*N*/ 		while( aSrcIter.IsMore() && aDstIter.IsMore() )
/*N*/ 		{
/*N*/ 			SdrObject* pSrc = aSrcIter.Next();
/*N*/ 			SdrObject* pDst = aDstIter.Next();
/*N*/ 
/*N*/ 			SdAnimationInfo* pSrcInfo = ((SdDrawDocument*)pModel)->GetAnimationInfo(pSrc);
/*N*/ 			if( pSrcInfo && (pSrcInfo->nPresOrder != LIST_APPEND) )
/*N*/ 			{
/*N*/ 				SdAnimationInfo* pDstInfo = ((SdDrawDocument*)pModel)->GetAnimationInfo(pDst);
/*N*/ 				DBG_ASSERT( pDstInfo, "shape should have an animation info after clone!" );
/*N*/ 
/*N*/ 				if( pDstInfo )
/*N*/ 					pDstInfo->nPresOrder = pSrcInfo->nPresOrder;
/*N*/ 			}
/*N*/ 		}
/*N*/ 
/*N*/ 		DBG_ASSERT( !aSrcIter.IsMore() && !aDstIter.IsMore(), "unequal shape numbers after a page clone?" );
/*N*/ 	}
/*N*/ 
/*N*/ 	return(pPage);
/*N*/ }

/*************************************************************************
|*
|* GetTextStyleSheetForObject
|*
\************************************************************************/


/*N*/ SfxStyleSheet* SdPage::GetTextStyleSheetForObject( SdrObject* pObj ) const
/*N*/ {
/*N*/ 	const PresObjKind eKind = ((SdPage*)this)->GetPresObjKind(pObj);
/*N*/ 	if( eKind != PRESOBJ_NONE )
/*N*/ 	{
/*N*/ 		return ((SdPage*)this)->GetStyleSheetForPresObj(eKind);
/*N*/ 	}
/*N*/ 
/*N*/ 	return FmFormPage::GetTextStyleSheetForObject( pObj );
/*N*/ }

/*NBFF*/ SfxItemSet* SdPage::getOrCreateItems()
/*NBFF*/ {
/*NBFF*/ 	if( mpItems == NULL )
/*NBFF*/ 		mpItems = new SfxItemSet( pModel->GetItemPool(), SDRATTR_XMLATTRIBUTES, SDRATTR_XMLATTRIBUTES );
/*NBFF*/ 
/*NBFF*/ 	return mpItems;
/*NBFF*/ }


/*N*/ sal_Bool SdPage::setAlienAttributes( const ::com::sun::star::uno::Any& rAttributes )
/*N*/ {
/*NBFF*/	SfxItemSet* pSet = getOrCreateItems();
/*NBFF*/ 
/*NBFF*/ 	SvXMLAttrContainerItem aAlienAttributes( SDRATTR_XMLATTRIBUTES );
/*NBFF*/ 	if( aAlienAttributes.PutValue( rAttributes, 0 ) )
/*NBFF*/ 	{
/*NBFF*/ 		pSet->Put( aAlienAttributes );
/*NBFF*/ 		return sal_True;
/*NBFF*/ 	}
/*NBFF*/ 
/*N*/ 	return sal_False;
/*N*/ }

/*N*/ void SdPage::getAlienAttributes( ::com::sun::star::uno::Any& rAttributes )
/*N*/ {
/*N*/ 	const SfxPoolItem* pItem;
/*N*/ 
/*N*/ 	if( (mpItems == NULL) || ( SFX_ITEM_SET != mpItems->GetItemState( SDRATTR_XMLATTRIBUTES, sal_False, &pItem ) ) )
/*N*/ 	{
/*N*/ 		SvXMLAttrContainerItem aAlienAttributes;
/*N*/ 		aAlienAttributes.QueryValue( rAttributes, 0 );
/*N*/ 	}
/*N*/ 	else
/*N*/ 	{
/*N*/ 		((SvXMLAttrContainerItem*)pItem)->QueryValue( rAttributes, 0 );
/*N*/ 	}
/*N*/ }
/*N*/ 

}
