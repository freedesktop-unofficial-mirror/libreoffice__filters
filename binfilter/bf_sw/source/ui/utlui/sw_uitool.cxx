/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: sw_uitool.cxx,v $
 *
 *  $Revision: 1.8 $
 *
 *  last change: $Author: hr $ $Date: 2007-01-02 18:11:33 $
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

#ifndef _HINTIDS_HXX
#include <hintids.hxx>
#endif
#ifndef _UIPARAM_HXX
#include <uiparam.hxx>
#endif



#ifndef _SVX_TSTPITEM_HXX //autogen
#include <bf_svx/tstpitem.hxx>
#endif
#ifndef _SVX_BOXITEM_HXX //autogen
#include <bf_svx/boxitem.hxx>
#endif
#ifndef _SVX_SIZEITEM_HXX //autogen
#include <bf_svx/sizeitem.hxx>
#endif
#ifndef _SVX_PAGEITEM_HXX //autogen
#include <bf_svx/pageitem.hxx>
#endif

#ifndef _HORIORNT_HXX
#include <horiornt.hxx>
#endif


#ifndef _FMTFSIZE_HXX //autogen
#include <fmtfsize.hxx>
#endif
#ifndef _FMTHDFT_HXX //autogen
#include <fmthdft.hxx>
#endif
#ifndef _UIITEMS_HXX
#include <uiitems.hxx>
#endif

#ifndef _HORIORNT_HXX
#include <horiornt.hxx>
#endif

#ifndef _PARATR_HXX
#include <paratr.hxx>
#endif
#ifndef _FMTCOL_HXX
#include <fmtcol.hxx>
#endif

#ifndef _ERROR_H
#include <error.h>
#endif
#ifndef _CMDID_H
#include <cmdid.h>
#endif
#ifndef _GLOBALS_HRC
#include <globals.hrc>
#endif
#ifndef _UTLUI_HRC
#include <utlui.hrc>
#endif
#ifndef _DOC_HXX //autogen wg. SwDoc
#include <doc.hxx>
#endif
#ifndef _SWSTYLENAMEMAPPER_HXX
#include <SwStyleNameMapper.hxx>
#endif
#include "so3/staticbaseurl.hxx"
namespace binfilter {
// 50 cm 28350
//
#define MAXHEIGHT 28350
#define MAXWIDTH  28350

/*--------------------------------------------------------------------
    Beschreibung: Allgemeine List von StringPointern
 --------------------------------------------------------------------*/


/*--------------------------------------------------------------------
    Beschreibung: Metric umschalten
 --------------------------------------------------------------------*/



/*--------------------------------------------------------------------
    Beschreibung:	Boxinfo-Attribut setzen
 --------------------------------------------------------------------*/



/*--------------------------------------------------------------------
    Beschreibung:	Header Footer fuellen
 --------------------------------------------------------------------*/


/*N*/ void FillHdFt(SwFrmFmt* pFmt, const  SfxItemSet& rSet)
/*N*/ {
/*N*/ 	SwAttrSet aSet(pFmt->GetAttrSet());
/*N*/ 	aSet.Put(rSet);
/*N*/ 
/*N*/ 	const SvxSizeItem& rSize = (const SvxSizeItem&)rSet.Get(SID_ATTR_PAGE_SIZE);
/*N*/ 	const SfxBoolItem& rDynamic = (const SfxBoolItem&)rSet.Get(SID_ATTR_PAGE_DYNAMIC);
/*N*/ 
/*N*/ 	// Groesse umsetzen
/*N*/ 	//
/*N*/ 	SwFmtFrmSize aFrmSize(rDynamic.GetValue() ? ATT_MIN_SIZE : ATT_FIX_SIZE,
/*N*/ 							rSize.GetSize().Width(),
/*N*/ 							rSize.GetSize().Height());
/*N*/ 	aSet.Put(aFrmSize);
/*N*/ 	pFmt->SetAttr(aSet);
/*N*/ }

/*--------------------------------------------------------------------
    Beschreibung:	PageDesc <-> in Sets wandeln und zurueck
 --------------------------------------------------------------------*/


/*N*/ void ItemSetToPageDesc( const SfxItemSet& rSet, SwPageDesc& rPageDesc )
/*N*/ {
/*N*/ 	SwFrmFmt& rMaster = rPageDesc.GetMaster();
/*N*/ 
/*N*/ 	// alle allgemeinen Rahmen-Attribute uebertragen
/*N*/ 	//
/*N*/ 	rMaster.SetAttr(rSet);
/*N*/ 
/*N*/ 	// PageData
/*N*/ 	//
/*N*/ 	if(rSet.GetItemState(SID_ATTR_PAGE) == SFX_ITEM_SET)
/*N*/ 	{
/*N*/ 		const SvxPageItem& rPageItem = (const SvxPageItem&)rSet.Get(SID_ATTR_PAGE);
/*N*/ 
/*N*/ 		USHORT nUse = (USHORT)rPageItem.GetPageUsage();
/*N*/ 		if(nUse & 0x04)
/*N*/ 			nUse |= 0x03;
/*N*/ 		if(nUse)
/*N*/ 			rPageDesc.SetUseOn( (UseOnPage) nUse );
/*N*/ 		rPageDesc.SetLandscape(rPageItem.IsLandscape());
/*N*/ 		SvxNumberType aNumType;
/*N*/ 		aNumType.SetNumberingType(rPageItem.GetNumType());
/*N*/ 		rPageDesc.SetNumType(aNumType);
/*N*/ 	}
/*N*/ 	// Groesse
/*N*/ 	//
/*N*/ 	if(rSet.GetItemState(SID_ATTR_PAGE_SIZE) == SFX_ITEM_SET)
/*N*/ 	{
/*N*/ 		const SvxSizeItem& rSizeItem = (const SvxSizeItem&)rSet.Get(SID_ATTR_PAGE_SIZE);
/*N*/ 		SwFmtFrmSize aSize(ATT_FIX_SIZE);
/*N*/ 		aSize.SetSize(rSizeItem.GetSize());
/*N*/ 		rMaster.SetAttr(aSize);
/*N*/ 	}
/*N*/ 	// Kopzeilen-Attribute auswerten
/*N*/ 	//
/*N*/ 	const SfxPoolItem* pItem;
/*N*/ 	if( SFX_ITEM_SET == rSet.GetItemState( SID_ATTR_PAGE_HEADERSET,
/*N*/ 			FALSE, &pItem ) )
/*N*/ 	{
/*N*/ 		const SfxItemSet& rHeaderSet = ((SvxSetItem*)pItem)->GetItemSet();
/*N*/ 		const SfxBoolItem& rHeaderOn = (const SfxBoolItem&)rHeaderSet.Get(SID_ATTR_PAGE_ON);
/*N*/ 
/*N*/ 		if(rHeaderOn.GetValue())
/*N*/ 		{
/*N*/ 			// Werte uebernehmen
/*N*/ 			if(!rMaster.GetHeader().IsActive())
/*N*/ 				rMaster.SetAttr(SwFmtHeader(TRUE));
/*N*/ 
/*N*/ 			// Das Headerformat rausholen und anpassen
/*N*/ 			//
/*N*/ 			SwFmtHeader aHeaderFmt(rMaster.GetHeader());
/*N*/ 			SwFrmFmt *pHeaderFmt = aHeaderFmt.GetHeaderFmt();
/*N*/ 			ASSERT(pHeaderFmt != 0, "kein HeaderFormat");
/*N*/ 
/*N*/ 			::binfilter::FillHdFt(pHeaderFmt, rHeaderSet);
/*N*/ 
/*N*/ 			rPageDesc.ChgHeaderShare(((const SfxBoolItem&)
/*N*/ 						rHeaderSet.Get(SID_ATTR_PAGE_SHARED)).GetValue());
/*N*/ 		}
/*N*/ 		else
/*N*/ 		{	// Header ausschalten
/*N*/ 			//
/*?*/ 			if(rMaster.GetHeader().IsActive())
/*?*/ 			{
/*?*/ 				rMaster.SetAttr(SwFmtHeader(BOOL(FALSE)));
/*?*/ 				rPageDesc.ChgHeaderShare(FALSE);
/*N*/ 			}
/*N*/ 		}
/*N*/ 	}
/*N*/ 
/*N*/ 	// Fusszeilen-Attribute auswerten
/*N*/ 	//
/*N*/ 	if( SFX_ITEM_SET == rSet.GetItemState( SID_ATTR_PAGE_FOOTERSET,
/*N*/ 			FALSE, &pItem ) )
/*N*/ 	{
/*N*/ 		const SfxItemSet& rFooterSet = ((SvxSetItem*)pItem)->GetItemSet();
/*N*/ 		const SfxBoolItem& rFooterOn = (const SfxBoolItem&)rFooterSet.Get(SID_ATTR_PAGE_ON);
/*N*/ 
/*N*/ 		if(rFooterOn.GetValue())
/*N*/ 		{
/*N*/ 			// Werte uebernehmen
/*N*/ 			if(!rMaster.GetFooter().IsActive())
/*N*/ 				rMaster.SetAttr(SwFmtFooter(TRUE));
/*N*/ 
/*N*/ 			// Das Footerformat rausholen und anpassen
/*N*/ 			//
/*N*/ 			SwFmtFooter aFooterFmt(rMaster.GetFooter());
/*N*/ 			SwFrmFmt *pFooterFmt = aFooterFmt.GetFooterFmt();
/*N*/ 			ASSERT(pFooterFmt != 0, "kein FooterFormat");
/*N*/ 
/*N*/ 			::binfilter::FillHdFt(pFooterFmt, rFooterSet);
/*N*/ 
/*N*/ 			rPageDesc.ChgFooterShare(((const SfxBoolItem&)
/*N*/ 						rFooterSet.Get(SID_ATTR_PAGE_SHARED)).GetValue());
/*N*/ 		}
/*N*/ 		else
/*N*/ 		{	// Footer ausschalten
/*?*/ 			//
/*?*/ 			if(rMaster.GetFooter().IsActive())
/*?*/ 			{
/*?*/ 				rMaster.SetAttr(SwFmtFooter(BOOL(FALSE)));
/*?*/ 				rPageDesc.ChgFooterShare(FALSE);
/*?*/ 			}
/*N*/ 		}
/*N*/ 	}
/*N*/ 
/*N*/ 	// Fussnoten
/*N*/ 	//
/*N*/ 	if( SFX_ITEM_SET == rSet.GetItemState( FN_PARAM_FTN_INFO,
/*N*/ 			FALSE, &pItem ) )
/*N*/ 		rPageDesc.SetFtnInfo( ((SwPageFtnInfoItem*)pItem)->GetPageFtnInfo() );
/*N*/ 
/*N*/ 
/*N*/ 	//
/*N*/ 	// Columns
/*N*/ 	//
/*N*/ 
/*N*/ 	// Registerhaltigkeit
/*N*/ 
/*N*/ 	if(SFX_ITEM_SET == rSet.GetItemState(
/*N*/ 							SID_SWREGISTER_MODE, FALSE, &pItem))
/*N*/ 	{
/*N*/ 		BOOL bSet = ((const SfxBoolItem*)pItem)->GetValue();
/*N*/ 		if(!bSet)
/*N*/ 			rPageDesc.SetRegisterFmtColl(0);
/*N*/ 		else if(SFX_ITEM_SET == rSet.GetItemState(
/*N*/ 								SID_SWREGISTER_COLLECTION, FALSE, &pItem))
/*N*/ 		{
/*N*/ 			const String& rColl = ((const SfxStringItem*)pItem)->GetValue();
/*N*/ 			SwDoc& rDoc = *rMaster.GetDoc();
/*N*/ 			SwTxtFmtColl* pColl = rDoc.FindTxtFmtCollByName( rColl );
/*N*/ 			if( !pColl )
/*N*/ 			{
/*?*/ 				USHORT nId = SwStyleNameMapper::GetPoolIdFromUIName( rColl, GET_POOLID_TXTCOLL );
/*?*/ 				if( USHRT_MAX != nId )
/*?*/ 					pColl = rDoc.GetTxtCollFromPool( nId );
/*?*/ 				else
/*?*/ 					pColl = rDoc.MakeTxtFmtColl( rColl,
/*?*/ 								(SwTxtFmtColl*)rDoc.GetDfltTxtFmtColl() );
/*N*/ 			}
/*N*/ 			if( pColl )
/*N*/ 				pColl->SetAttr( SwRegisterItem ( TRUE ));
/*N*/ 			rPageDesc.SetRegisterFmtColl( pColl );
/*N*/ 		}
/*N*/ 	}
/*N*/ }

/*--------------------------------------------------------------------
    Beschreibung:
 --------------------------------------------------------------------*/


/*N*/ void PageDescToItemSet(	const SwPageDesc& rPageDesc, SfxItemSet& rSet)
/*N*/ {
/*N*/ 	const SwFrmFmt& rMaster = rPageDesc.GetMaster();
/*N*/ 
/*N*/ 	// Seitendaten
/*N*/ 	//
/*N*/ 	SvxPageItem aPageItem(SID_ATTR_PAGE);
/*N*/ 	aPageItem.SetDescName(rPageDesc.GetName());
/*N*/ 	aPageItem.SetPageUsage((SvxPageUsage)rPageDesc.GetUseOn());
/*N*/ 	aPageItem.SetLandscape(rPageDesc.GetLandscape());
/*N*/ 	aPageItem.SetNumType((SvxNumType)rPageDesc.GetNumType().GetNumberingType());
/*N*/ 	rSet.Put(aPageItem);
/*N*/ 
/*N*/ 	// Groesse
/*N*/ 	SvxSizeItem aSizeItem(SID_ATTR_PAGE_SIZE, rMaster.GetFrmSize().GetSize());
/*N*/ 	rSet.Put(aSizeItem);
/*N*/ 
/*N*/ 	// Maximale Groesse
/*N*/ 	SvxSizeItem aMaxSizeItem(SID_ATTR_PAGE_MAXSIZE, Size(MAXWIDTH, MAXHEIGHT));
/*N*/ 	rSet.Put(aMaxSizeItem);
/*N*/ 
/*N*/ 	// Raender, Umrandung und das andere Zeug
/*N*/ 	//
/*N*/ 	rSet.Put(rMaster.GetAttrSet());
/*N*/ 
/*N*/ 	SvxBoxInfoItem aBoxInfo;
/*N*/ 	const SfxPoolItem *pBoxInfo;
/*N*/ 	if ( SFX_ITEM_SET == rSet.GetItemState( SID_ATTR_BORDER_INNER,
/*N*/ 											TRUE, &pBoxInfo) )
/*?*/ 		{DBG_BF_ASSERT(0, "STRIP");} //STRIP001 aBoxInfo = *(SvxBoxInfoItem*)pBoxInfo;
/*N*/ 
/*N*/ 	aBoxInfo.SetTable( FALSE );
/*N*/ 		// Abstandsfeld immer anzeigen
/*N*/ 	aBoxInfo.SetDist( TRUE);
/*N*/ 		// Minimalgroesse in Tabellen und Absaetzen setzen
/*N*/ 	aBoxInfo.SetMinDist( FALSE );
/*N*/ 	// Default-Abstand immer setzen
/*N*/ 	aBoxInfo.SetDefDist( MIN_BORDER_DIST );
/*N*/ 		// Einzelne Linien koennen nur in Tabellen DontCare-Status haben
/*N*/ 	aBoxInfo.SetValid( VALID_DISABLE );
/*N*/ 	rSet.Put( aBoxInfo );
/*N*/ 
/*N*/ 
/*N*/ 	SfxStringItem aFollow(SID_ATTR_PAGE_EXT1, aEmptyStr);
/*N*/ 	if(rPageDesc.GetFollow())
/*N*/ 		aFollow.SetValue(rPageDesc.GetFollow()->GetName());
/*N*/ 	rSet.Put(aFollow);
/*N*/ 
/*N*/ 	// Header
/*N*/ 	//
/*N*/ 	if(rMaster.GetHeader().IsActive())
/*N*/ 	{
/*N*/ 		const SwFmtHeader &rHeaderFmt = rMaster.GetHeader();
/*N*/ 		const SwFrmFmt *pHeaderFmt = rHeaderFmt.GetHeaderFmt();
/*N*/ 		ASSERT(pHeaderFmt != 0, kein HeaderFormat.);
/*N*/ 
/*N*/ 		// HeaderInfo, Raender, Hintergrund, Umrandung
/*N*/ 		//
/*N*/ 		SfxItemSet aHeaderSet( *rSet.GetPool(),
/*N*/ 					SID_ATTR_PAGE_ON, 		SID_ATTR_PAGE_SHARED,
/*N*/ 					SID_ATTR_PAGE_SIZE, 	SID_ATTR_PAGE_SIZE,
/*N*/ 					SID_ATTR_BORDER_INNER,	SID_ATTR_BORDER_INNER,
/*N*/ 					RES_FRMATR_BEGIN,		RES_FRMATR_END-1,
/*N*/ 					0);
/*N*/ 
/*N*/ 		// dynamische oder feste Hoehe
/*N*/ 		//
/*N*/ 		SfxBoolItem aOn(SID_ATTR_PAGE_ON, TRUE);
/*N*/ 		aHeaderSet.Put(aOn);
/*N*/ 
/*N*/ 		const SwFmtFrmSize &rFrmSize = pHeaderFmt->GetFrmSize();
/*N*/ 		const SwFrmSize eSizeType = rFrmSize.GetSizeType();
/*N*/ 		SfxBoolItem aDynamic(SID_ATTR_PAGE_DYNAMIC, eSizeType != ATT_FIX_SIZE);
/*N*/ 		aHeaderSet.Put(aDynamic);
/*N*/ 
/*N*/ 		// Links gleich rechts
/*N*/ 		//
/*N*/ 		SfxBoolItem aShared(SID_ATTR_PAGE_SHARED, rPageDesc.IsHeaderShared());
/*N*/ 		aHeaderSet.Put(aShared);
/*N*/ 
/*N*/ 		// Groesse
/*N*/ 		SvxSizeItem aSize(SID_ATTR_PAGE_SIZE, Size(rFrmSize.GetSize()));
/*N*/ 		aHeaderSet.Put(aSize);
/*N*/ 
/*N*/ 		// Rahmen-Attribute umschaufeln
/*N*/ 		//
/*N*/ 		aHeaderSet.Put(pHeaderFmt->GetAttrSet());
/*N*/ 		aHeaderSet.Put( aBoxInfo );
/*N*/ 
/*N*/ 		// SetItem erzeugen
/*N*/ 		//
/*N*/ 		SvxSetItem aSetItem(SID_ATTR_PAGE_HEADERSET, aHeaderSet);
/*N*/ 		rSet.Put(aSetItem);
/*N*/ 	}
/*N*/ 
/*N*/ 	// Footer
/*N*/ 	if(rMaster.GetFooter().IsActive())
/*N*/ 	{
/*N*/ 		const SwFmtFooter &rFooterFmt = rMaster.GetFooter();
/*N*/ 		const SwFrmFmt *pFooterFmt = rFooterFmt.GetFooterFmt();
/*N*/ 		ASSERT(pFooterFmt != 0, kein FooterFormat.);
/*N*/ 
/*N*/ 		// FooterInfo, Raender, Hintergrund, Umrandung
/*N*/ 		//
/*N*/ 		SfxItemSet aFooterSet( *rSet.GetPool(),
/*N*/ 					SID_ATTR_PAGE_ON, 		SID_ATTR_PAGE_SHARED,
/*N*/ 					SID_ATTR_PAGE_SIZE, 	SID_ATTR_PAGE_SIZE,
/*N*/ 					SID_ATTR_BORDER_INNER,	SID_ATTR_BORDER_INNER,
/*N*/ 					RES_FRMATR_BEGIN, 		RES_FRMATR_END-1,
/*N*/ 					0);
/*N*/ 
/*N*/ 		// dynamische oder feste Hoehe
/*N*/ 		//
/*N*/ 		SfxBoolItem aOn(SID_ATTR_PAGE_ON, TRUE);
/*N*/ 		aFooterSet.Put(aOn);
/*N*/ 
/*N*/ 		const SwFmtFrmSize &rFrmSize = pFooterFmt->GetFrmSize();
/*N*/ 		const SwFrmSize eSizeType = rFrmSize.GetSizeType();
/*N*/ 		SfxBoolItem aDynamic(SID_ATTR_PAGE_DYNAMIC, eSizeType != ATT_FIX_SIZE);
/*N*/ 		aFooterSet.Put(aDynamic);
/*N*/ 
/*N*/ 		// Links gleich rechts
/*N*/ 		//
/*N*/ 		SfxBoolItem aShared(SID_ATTR_PAGE_SHARED, rPageDesc.IsFooterShared());
/*N*/ 		aFooterSet.Put(aShared);
/*N*/ 
/*N*/ 		// Groesse
/*N*/ 		SvxSizeItem aSize(SID_ATTR_PAGE_SIZE, Size(rFrmSize.GetSize()));
/*N*/ 		aFooterSet.Put(aSize);
/*N*/ 
/*N*/ 		// Rahmen-Attribute umschaufeln
/*N*/ 		//
/*N*/ 		aFooterSet.Put(pFooterFmt->GetAttrSet());
/*N*/ 		aFooterSet.Put( aBoxInfo );
/*N*/ 
/*N*/ 		// SetItem erzeugen
/*N*/ 		//
/*N*/ 		SvxSetItem aSetItem(SID_ATTR_PAGE_FOOTERSET, aFooterSet);
/*N*/ 		rSet.Put(aSetItem);
/*N*/ 	}
/*N*/ 
/*N*/ 	// Fussnoten einbauen
/*N*/ 	//
/*N*/ 	SwPageFtnInfo& rInfo = (SwPageFtnInfo&)rPageDesc.GetFtnInfo();
/*N*/ 	SwPageFtnInfoItem aFtnItem(FN_PARAM_FTN_INFO, rInfo);
/*N*/ 	rSet.Put(aFtnItem);
/*N*/ 
/*N*/ 	// Registerhaltigkeit
/*N*/ 
/*N*/ 	const SwTxtFmtColl* pCol = rPageDesc.GetRegisterFmtColl();
/*N*/ 	SwRegisterItem aReg(pCol != 0);
/*N*/ 	aReg.SetWhich(SID_SWREGISTER_MODE);
/*N*/ 	rSet.Put(aReg);
/*N*/ 	if(pCol)
/*N*/ 		rSet.Put(SfxStringItem(SID_SWREGISTER_COLLECTION, pCol->GetName()));
/*N*/ 
/*N*/ }
}
