/* -*- Mode: C++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */
/*************************************************************************
 *
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER.
 * 
 * Copyright 2000, 2010 Oracle and/or its affiliates.
 *
 * OpenOffice.org - a multi-platform office productivity suite
 *
 * This file is part of OpenOffice.org.
 *
 * OpenOffice.org is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License version 3
 * only, as published by the Free Software Foundation.
 *
 * OpenOffice.org is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License version 3 for more details
 * (a copy is included in the LICENSE file that accompanied this code).
 *
 * You should have received a copy of the GNU Lesser General Public License
 * version 3 along with OpenOffice.org.  If not, see
 * <http://www.openoffice.org/license.html>
 * for a copy of the LGPLv3 License.
 *
 ************************************************************************/

// include ---------------------------------------------------------------

#include <tools/stream.hxx>
#ifdef _MSC_VER
#pragma hdrstop
#endif

// Erstmal definieren, damit die Klassendeklarionen angezogen werden.
#define  ITEMID_PAGE 		0
#define  ITEMID_SETITEM 	0

#include <bf_svtools/poolitem.hxx>

#include "pageitem.hxx"
#include "itemtype.hxx"
#include <unomid.hxx>

#include <com/sun/star/style/PageStyleLayout.hpp>

#include <bf_svtools/itemset.hxx>
namespace binfilter {

using namespace ::rtl;
using namespace ::com::sun::star;

// STATIC DATA -----------------------------------------------------------

/*N*/ TYPEINIT1_AUTOFACTORY( SvxPageItem, SfxPoolItem );

/*--------------------------------------------------------------------
    Beschreibung: Konstruktor
 --------------------------------------------------------------------*/

/*N*/ SvxPageItem::SvxPageItem( const USHORT nId ) : SfxPoolItem( nId ),
/*N*/ 
/*N*/ 	eNumType	( SVX_ARABIC ),
/*N*/ 	bLandscape	( sal_False ),
/*N*/ 	eUse		( SVX_PAGE_ALL )
/*N*/ {
/*N*/ }

/*--------------------------------------------------------------------
    Beschreibung: Copy-Konstruktor
 --------------------------------------------------------------------*/

/*N*/ SvxPageItem::SvxPageItem( const SvxPageItem& rItem )
/*N*/ 	: SfxPoolItem( rItem )
/*N*/ {
/*N*/ 	eNumType 	= rItem.eNumType;
/*N*/ 	bLandscape 	= rItem.bLandscape;
/*N*/ 	eUse 		= rItem.eUse;
/*N*/ }

/*--------------------------------------------------------------------
    Beschreibung: Clonen
 --------------------------------------------------------------------*/

/*N*/ SfxPoolItem* SvxPageItem::Clone( SfxItemPool* /*pPool*/ ) const
/*N*/ {
/*N*/ 	return new SvxPageItem( *this );
/*N*/ }

/*--------------------------------------------------------------------
    Beschreibung: Abfrage auf Gleichheit
 --------------------------------------------------------------------*/

/*N*/ int SvxPageItem::operator==( const SfxPoolItem& rAttr ) const
/*N*/ {
/*N*/ 	DBG_ASSERT( SfxPoolItem::operator==(rAttr), "unequal types" );
/*N*/ 	const SvxPageItem& rItem = (SvxPageItem&)rAttr;
/*N*/ 	return ( eNumType 	== rItem.eNumType 	&&
/*N*/ 			 bLandscape == rItem.bLandscape &&
/*N*/ 			 eUse 		== rItem.eUse );
/*N*/ }

/*?*/ inline XubString GetUsageText( const USHORT eU )
/*?*/ {
/*?*/ 	if ( eU & SVX_PAGE_LEFT )
/*?*/ 		return SVX_RESSTR(RID_SVXITEMS_PAGE_USAGE_LEFT);
/*?*/ 	if ( eU & SVX_PAGE_RIGHT )
/*?*/ 		return SVX_RESSTR(RID_SVXITEMS_PAGE_USAGE_RIGHT);
/*?*/ 	if ( eU & SVX_PAGE_ALL )
/*?*/ 		return SVX_RESSTR(RID_SVXITEMS_PAGE_USAGE_ALL);
/*?*/ 	if ( eU & SVX_PAGE_MIRROR )
/*?*/ 		return SVX_RESSTR(RID_SVXITEMS_PAGE_USAGE_MIRROR);
/*?*/ 	return String();
/*?*/ }

//------------------------------------------------------------------------


//------------------------------------------------------------------------
/*N*/ bool SvxPageItem::QueryValue( uno::Any& rVal, BYTE nMemberId ) const
/*N*/ {
/*N*/
/*N*/     nMemberId &= ~CONVERT_TWIPS;
/*N*/ 	switch( nMemberId )
/*N*/ 	{
/*N*/ 		case MID_PAGE_NUMTYPE:
/*N*/ 		{
/*N*/ 			//!	die Konstanten sind nicht mehr in den IDLs ?!?
/*N*/ 			rVal <<= (sal_Int16)( eNumType );
/*N*/ 		}
/*N*/ 		break;
/*N*/ 		case MID_PAGE_ORIENTATION:
/*N*/ 			//Landscape= sal_True
/*N*/ 			rVal = Bool2Any(bLandscape);
/*N*/ 		break;
/*N*/ 		case MID_PAGE_LAYOUT     :
/*N*/ 		{
/*N*/ 			style::PageStyleLayout eRet;
/*N*/ 			switch(eUse & 0x0f)
/*N*/ 			{
/*N*/ 				case SVX_PAGE_LEFT	: eRet = style::PageStyleLayout_LEFT;	   break;
/*N*/ 				case SVX_PAGE_RIGHT	: eRet = style::PageStyleLayout_RIGHT;	   break;
/*N*/ 				case SVX_PAGE_ALL	: eRet = style::PageStyleLayout_ALL;	   break;
/*N*/ 				case SVX_PAGE_MIRROR: eRet = style::PageStyleLayout_MIRRORED; break;
/*N*/ 				default:
/*N*/ 					OSL_FAIL("was fuer ein Layout ist das?");
/*N*/ 					return sal_False;
/*N*/ 			}
/*N*/ 			rVal <<= eRet;
/*N*/ 		}
/*N*/ 		break;
/*N*/ 	}
/*N*/ 
/*N*/ 	return sal_True;
/*N*/ }
//------------------------------------------------------------------------
/*N*/ bool SvxPageItem::PutValue( const uno::Any& rVal, BYTE nMemberId )
/*N*/ {
/*N*/ 	switch( nMemberId )
/*N*/ 	{
/*N*/ 		case MID_PAGE_NUMTYPE:
/*N*/ 		{
/*N*/ 			sal_Int32 nValue = 0;
/*N*/ 			if(!(rVal >>= nValue))
/*N*/ 				return sal_False;
/*N*/ 
/*N*/ 			eNumType = (SvxNumType)nValue;
/*N*/ 		}
/*N*/ 		break;
/*N*/ 		case MID_PAGE_ORIENTATION:
/*N*/ 			bLandscape = Any2Bool(rVal);
/*N*/ 		break;
/*N*/ 		case MID_PAGE_LAYOUT     :
/*N*/ 		{
/*N*/ 			style::PageStyleLayout eLayout;
/*N*/ 			if(!(rVal >>= eLayout))
/*N*/ 			{
/*N*/ 				sal_Int32 nValue = 0;
/*?*/ 				if(!(rVal >>= nValue))
/*?*/ 					return sal_False;
/*?*/ 				eLayout = (style::PageStyleLayout)nValue;
/*N*/ 			}
/*N*/ 			eUse &= 0xfff0;
/*N*/ 			switch( eLayout )
/*N*/ 			{
/*N*/ 				case style::PageStyleLayout_LEFT  	 : eUse |= SVX_PAGE_LEFT ; break;
/*N*/ 				case style::PageStyleLayout_RIGHT   : eUse |= SVX_PAGE_RIGHT; break;
/*?*/ 				case style::PageStyleLayout_ALL     : eUse |= SVX_PAGE_ALL  ; break;
/*N*/ 				case style::PageStyleLayout_MIRRORED: eUse |= SVX_PAGE_MIRROR;break;
                    default: break;
                }
/*N*/ 		}
/*N*/ 		break;
/*N*/ 	}
/*N*/ 	return sal_True;
/*N*/ }

//------------------------------------------------------------------------

/*N*/ SfxPoolItem* SvxPageItem::Create( SvStream& rStream, USHORT ) const
/*N*/ {
/*N*/ 	XubString sStr;
/*N*/ 	BYTE eType;
/*N*/ 	sal_Bool bLand;
/*N*/ 	USHORT nUse;
/*N*/ 
/*N*/ 	// UNICODE: rStream >> sStr;
/*N*/ 	rStream.ReadByteString( sStr );
/*N*/ 
/*N*/ 	rStream >> eType;
/*N*/ 	rStream >> bLand;
/*N*/ 	rStream >> nUse;
/*N*/ 
/*N*/ 	SvxPageItem* pPage = new SvxPageItem( Which() );
/*N*/ 	pPage->SetDescName( sStr );
/*N*/ 	pPage->SetNumType( (SvxNumType)eType );
/*N*/ 	pPage->SetLandscape( bLand );
/*N*/ 	pPage->SetPageUsage( nUse );
/*N*/ 	return pPage;
/*N*/ }

/*--------------------------------------------------------------------
    Beschreibung:	HeaderFooterSet
 --------------------------------------------------------------------*/

/*N*/ SvxSetItem::SvxSetItem( const USHORT nId, const SfxItemSet& rSet ) :
/*N*/ 
/*N*/ 	SfxSetItem( nId, rSet )
/*N*/ {
/*N*/ }

/*N*/ SvxSetItem::SvxSetItem( const SvxSetItem& rItem ) :
/*N*/ 
/*N*/ 	SfxSetItem( rItem )
/*N*/ {
/*N*/ }


/*N*/ SfxPoolItem* SvxSetItem::Clone( SfxItemPool* /*pPool*/ ) const
/*N*/ {
/*N*/ 	return new SvxSetItem(*this);
/*N*/ }

//------------------------------------------------------------------------


/*N*/ SfxPoolItem* SvxSetItem::Create(SvStream &rStrm, USHORT /*nVersion*/) const
/*N*/ {
/*N*/ 	SfxItemSet* _pSet = new SfxItemSet( *GetItemSet().GetPool(),
/*N*/ 									   GetItemSet().GetRanges() );
/*N*/ 
/*N*/ 	_pSet->Load( rStrm );
/*N*/ 
/*N*/ 	return new SvxSetItem( Which(), *_pSet );
/*N*/ }


}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
