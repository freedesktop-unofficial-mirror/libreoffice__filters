/*************************************************************************
 *
 *  $RCSfile: sw_swatrset.cxx,v $
 *
 *  $Revision: 1.3 $
 *
 *  last change: $Author: rt $ $Date: 2004-05-05 16:40:47 $
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

#include <hintids.hxx>

#ifndef _SVX_COLRITEM_HXX //autogen
#include <bf_svx/colritem.hxx>
#endif
#ifndef _SVX_BRSHITEM_HXX //autogen
#include <bf_svx/brshitem.hxx>
#endif
#define ITEMID_LINE             SID_ATTR_LINE_STYLE
#ifndef _SVX_BOLNITEM_HXX //autogen
#include <bf_svx/bolnitem.hxx>
#endif
#ifndef _SVX_BOXITEM_HXX //autogen
#include <bf_svx/boxitem.hxx>
#endif
#ifndef _XTABLE_HXX //autogen
#include <bf_svx/xtable.hxx>
#endif
#ifndef _OFF_APP_HXX //autogen
#include <bf_offmgr/app.hxx>
#endif

#ifndef _FMTPDSC_HXX //autogen
#include <fmtpdsc.hxx>
#endif
#ifndef _PAGEDESC_HXX //autogen
#include <pagedesc.hxx>
#endif
#ifndef _CHARFMT_HXX
#include <charfmt.hxx>
#endif
#ifndef _DOC_HXX
#include <doc.hxx>
#endif
#ifndef _NODE_HXX //autogen
#include <node.hxx>
#endif
#ifndef _FORMAT_HXX //autogen
#include <format.hxx>
#endif
#ifndef _SWATRSET_HXX
#include <swatrset.hxx>
#endif
#ifndef _PARATR_HXX
#include <paratr.hxx>		// fuer SetModifyAtAttr
#endif
#ifndef _CELLATR_HXX
#include <cellatr.hxx>		// fuer SetModifyAtAttr
#endif
#ifndef _CMDID_H
#include <cmdid.h>
#endif
namespace binfilter {


/*N*/ SwAttrPool::SwAttrPool( SwDoc* pD )
/*N*/ 	: SfxItemPool( String::CreateFromAscii(
/*N*/ 								RTL_CONSTASCII_STRINGPARAM( "SWG" )),
/*N*/ 					POOLATTR_BEGIN, POOLATTR_END-1,
/*N*/ 					aSlotTab, aAttrTab ),
/*N*/ 	pDoc( pD )
/*N*/ {
/*N*/ 	SetVersionMap( 1, 1, 60, pVersionMap1 );
/*N*/ 	SetVersionMap( 2, 1, 75, pVersionMap2 );
/*N*/ 	SetVersionMap( 3, 1, 86, pVersionMap3 );
/*N*/ 	SetVersionMap( 4, 1,121, pVersionMap4 );
/*N*/ }


/*?*/ SwAttrSet::SwAttrSet( SwAttrPool& rPool, USHORT nWh1, USHORT nWh2 )
/*?*/ 	: SfxItemSet( rPool, nWh1, nWh2 ), pOldSet( 0 ), pNewSet( 0 )
/*?*/ {
/*?*/ }


/*N*/ SwAttrSet::SwAttrSet( SwAttrPool& rPool, const USHORT* nWhichPairTable )
/*N*/ 	: SfxItemSet( rPool, nWhichPairTable ), pOldSet( 0 ), pNewSet( 0 )
/*N*/ {
/*N*/ }


/*N*/ SwAttrSet::SwAttrSet( const SwAttrSet& rSet )
/*N*/ 	: SfxItemSet( rSet ), pOldSet( 0 ), pNewSet( 0 )
/*N*/ {
/*N*/ }


/*N*/ int SwAttrSet::Put_BC( const SfxPoolItem& rAttr,
/*N*/ 					SwAttrSet* pOld, SwAttrSet* pNew )
/*N*/ {
/*N*/ 	pNewSet = pNew;
/*N*/ 	pOldSet = pOld;
/*N*/ 	int nRet = 0 != SfxItemSet::Put( rAttr );
/*N*/ 	pOldSet = pNewSet = 0;
/*N*/ 	return nRet;
/*N*/ }


/*N*/ int SwAttrSet::Put_BC( const SfxItemSet& rSet,
/*N*/ 					SwAttrSet* pOld, SwAttrSet* pNew )
/*N*/ {
/*N*/ 	pNewSet = pNew;
/*N*/ 	pOldSet = pOld;
/*N*/ 	int nRet = 0 != SfxItemSet::Put( rSet );
/*N*/ 	pOldSet = pNewSet = 0;
/*N*/ 	return nRet;
/*N*/ }



/*N*/ USHORT SwAttrSet::ClearItem_BC( USHORT nWhich,
/*N*/ 						SwAttrSet* pOld, SwAttrSet* pNew )
/*N*/ {
/*N*/ 	pNewSet = pNew;
/*N*/ 	pOldSet = pOld;
/*N*/ 	USHORT nRet = SfxItemSet::ClearItem( nWhich );
/*N*/ 	pOldSet = pNewSet = 0;
/*N*/ 	return nRet;
/*N*/ }


/*N*/ USHORT SwAttrSet::ClearItem_BC( USHORT nWhich1, USHORT nWhich2,
/*N*/ 						SwAttrSet* pOld, SwAttrSet* pNew )
/*N*/ {
/*N*/ 	ASSERT( nWhich1 <= nWhich2, "kein gueltiger Bereich" );
/*N*/ 	pNewSet = pNew;
/*N*/ 	pOldSet = pOld;
/*N*/ 	USHORT nRet = 0;
/*N*/ 	for( ; nWhich1 <= nWhich2; ++nWhich1 )
/*N*/ 		nRet += SfxItemSet::ClearItem( nWhich1 );
/*N*/ 	pOldSet = pNewSet = 0;
/*N*/ 	return nRet;
/*N*/ }



/*N*/ int SwAttrSet::Intersect_BC( const SfxItemSet& rSet,
/*N*/ 							SwAttrSet* pOld, SwAttrSet* pNew )
/*N*/ {
/*N*/ 	pNewSet = pNew;
/*N*/ 	pOldSet = pOld;
/*N*/ 	SfxItemSet::Intersect( rSet );
/*N*/ 	pOldSet = pNewSet = 0;
/*N*/ 	return pNew ? pNew->Count() : ( pOld ? pOld->Count() : 0 );
/*N*/ }


/*N*/ int SwAttrSet::Differentiate_BC( const SfxItemSet& rSet,
/*N*/ 							SwAttrSet* pOld, SwAttrSet* pNew )
/*N*/ {
/*N*/ 	pNewSet = pNew;
/*N*/ 	pOldSet = pOld;
/*N*/ 	SfxItemSet::Differentiate( rSet );
/*N*/ 	pOldSet = pNewSet = 0;
/*N*/ 	return pNew ? pNew->Count() : ( pOld ? pOld->Count() : 0 );
/*N*/ }


/*N*/ int SwAttrSet::MergeValues_BC( const SfxItemSet& rSet,
/*N*/ 							SwAttrSet* pOld, SwAttrSet* pNew )
/*N*/ {
/*N*/ 	pNewSet = pNew;
/*N*/ 	pOldSet = pOld;
/*N*/ 	SfxItemSet::MergeValues( rSet );
/*N*/ 	pOldSet = pNewSet = 0;
/*N*/ 	return pNew ? pNew->Count() : ( pOld ? pOld->Count() : 0 );
/*N*/ }


    // Notification-Callback
/*N*/ void  SwAttrSet::Changed( const SfxPoolItem& rOld,
/*N*/ 								const SfxPoolItem& rNew )
/*N*/ {
/*N*/ 	if( pOldSet )
/*N*/ 		pOldSet->PutChgd( rOld );
/*N*/ 
/*N*/ 	if( pNewSet )
/*N*/ 		pNewSet->PutChgd( rNew );
/*N*/ }


// ----------------------------------------------------------------
// Sonderbehandlung fuer einige Attribute
// Setze den Modify-Pointer (alten pDefinedIn) bei folgenden Attributen:
//	- SwFmtDropCaps
//	- SwFmtPageDesc
// (Wird beim Einfuegen in Formate/Nodes gerufen)
// ----------------------------------------------------------------
/*N*/ void SwAttrSet::SetModifyAtAttr( const SwModify* pModify )
/*N*/ {
/*N*/ 	const SfxPoolItem* pItem;
/*N*/ 	if( SFX_ITEM_SET == GetItemState( RES_PAGEDESC, FALSE, &pItem ) &&
/*N*/ 		((SwFmtPageDesc*)pItem)->GetDefinedIn() != pModify  )
/*N*/ 	{
/*N*/ 		((SwFmtPageDesc*)pItem)->ChgDefinedIn( pModify );
/*N*/ 	}
/*N*/ 
/*N*/ 	if( SFX_ITEM_SET == GetItemState( RES_PARATR_NUMRULE, FALSE, &pItem ) &&
/*N*/ 		((SwNumRuleItem*)pItem)->GetDefinedIn() != pModify  )
/*N*/ 	{
/*N*/ 		((SwNumRuleItem*)pItem)->ChgDefinedIn( pModify );
/*N*/ 	}
/*N*/ 
/*N*/ 	if( SFX_ITEM_SET == GetItemState( RES_PARATR_DROP, FALSE, &pItem ) &&
/*N*/ 		((SwFmtDrop*)pItem)->GetDefinedIn() != pModify )
/*N*/ 	{
/*N*/ 		// CharFormat gesetzt und dann noch in unterschiedlichen
/*N*/ 		// Attribut Pools, dann muss das CharFormat kopiert werden!
/*N*/ 		SwCharFmt* pCharFmt;
/*N*/ 		if( 0 != ( pCharFmt = ((SwFmtDrop*)pItem)->GetCharFmt() )
/*N*/ 			&& GetPool() != pCharFmt->GetAttrSet().GetPool() )
/*N*/ 		{
/*?*/ 			pCharFmt = GetDoc()->CopyCharFmt( *pCharFmt );
/*?*/ 			((SwFmtDrop*)pItem)->SetCharFmt( pCharFmt );
/*N*/ 		}
/*N*/ 		((SwFmtDrop*)pItem)->ChgDefinedIn( pModify );
/*N*/ 	}
/*N*/ 
/*N*/ 	if( SFX_ITEM_SET == GetItemState( RES_BOXATR_FORMULA, FALSE, &pItem ) &&
/*N*/ 		((SwTblBoxFormula*)pItem)->GetDefinedIn() != pModify )
/*N*/ 	{
/*?*/ 		DBG_BF_ASSERT(0, "STRIP"); //STRIP001 ((SwTblBoxFormula*)pItem)->ChgDefinedIn( pModify );
/*N*/ 	}
/*N*/ }


/*N*/ void SwAttrSet::CopyToModify( SwModify& rMod ) const
/*N*/ {
/*N*/ 	// kopiere die Attribute ggfs. ueber Dokumentgrenzen
/*N*/ 	SwCntntNode* pCNd = PTR_CAST( SwCntntNode, &rMod );
/*N*/ 	SwFmt* pFmt = PTR_CAST( SwFmt, &rMod );
/*N*/ 
/*N*/ 	if( pCNd || pFmt )
/*N*/ 	{
/*N*/ 		if( Count() )
/*N*/ 		{
/*N*/ 			const SfxPoolItem* pItem;
/*N*/ 			const SwDoc *pSrcDoc = GetDoc();
/*N*/ 			SwDoc *pDstDoc = pCNd ? pCNd->GetDoc() : pFmt->GetDoc();
/*N*/ 
/*N*/ 			// muss die NumRule kopiert werden?
/*N*/ 			if( pSrcDoc != pDstDoc && SFX_ITEM_SET == GetItemState(
/*N*/ 									RES_PARATR_NUMRULE, FALSE, &pItem ) )
/*N*/ 			{
/*N*/ 				const String& rNm = ((SwNumRuleItem*)pItem)->GetValue();
/*N*/ 				if( rNm.Len() )
/*N*/ 				{
/*N*/ 					SwNumRule* pDestRule = pDstDoc->FindNumRulePtr( rNm );
/*N*/ 					if( pDestRule )
/*N*/ 						pDestRule->SetInvalidRule( TRUE );
/*N*/ 					else
/*N*/ 						pDstDoc->MakeNumRule( rNm,
/*N*/ 											pSrcDoc->FindNumRulePtr( rNm ) );
/*N*/ 				}
/*N*/ 			}
/*N*/ 
/*N*/ 			// JP 04.02.99: Task #61467# Seitenvorlagenwechsel mit kopieren
/*N*/ 			//				Gegenueber dem alten Verhalten, sie zu entfernen
/*N*/ 			const SwPageDesc* pPgDesc;
/*N*/ 			if( pSrcDoc != pDstDoc && SFX_ITEM_SET == GetItemState(
/*N*/ 											RES_PAGEDESC, FALSE, &pItem ) &&
/*N*/ 				0 != ( pPgDesc = ((SwFmtPageDesc*)pItem)->GetPageDesc()) )
/*N*/ 			{
/*N*/ 				SfxItemSet aTmpSet( *this );
/*N*/ 
/*N*/ 				// JP 09.02.99: und jetzt doch wieder nur entfernen
/*N*/ 				aTmpSet.ClearItem( RES_PAGEDESC );
/*N*/ 
/*************************************************************************
                 SwPageDesc* pDstPgDesc = pDstDoc->FindPageDescByName(
                                                    pPgDesc->GetName() );
                 if( !pDstPgDesc )
                 {
                    // dann kopieren, ansonsten den benutzen
                     pDstPgDesc = &pDstDoc->_GetPageDesc( pDstDoc->MakePageDesc(
                                                     pPgDesc->GetName() ));
                    pDstDoc->CopyPageDesc( *pPgDesc, *pDstPgDesc );
                }
                SwFmtPageDesc aDesc( pDstPgDesc );
                aDesc.SetNumOffset( ((SwFmtPageDesc*)pItem)->GetNumOffset() );
                aTmpSet.Put( aDesc );
************************************************************************/
/*N*/ 
/*N*/ 				if( pCNd )
/*N*/ 					pCNd->SetAttr( aTmpSet );
/*N*/ 				else
/*?*/ 					pFmt->SetAttr( aTmpSet );
/*N*/ 			}
/*N*/ 			else if( pCNd )
/*N*/ 				pCNd->SetAttr( *this );
/*N*/ 			else
/*N*/ 				pFmt->SetAttr( *this );
/*N*/ 		}
/*N*/ 	}
/*N*/ #ifndef PRODUCT
/*N*/ 	else
/*N*/ 		ASSERT( !this, "weder Format noch ContentNode - keine Attribute kopiert");
/*N*/ #endif
/*N*/ }

// check if ID is InRange of AttrSet-Ids
/*N*/ BOOL IsInRange( const USHORT* pRange, const USHORT nId )
/*N*/ {
/*N*/ 	while( *pRange )
/*N*/ 	{
/*N*/ 		if( *pRange <= nId && nId <= *(pRange+1) )
/*N*/ 			return TRUE;
/*N*/ 		pRange += 2;
/*N*/ 	}
/*N*/ 	return FALSE;
/*N*/ }




}
