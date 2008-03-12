/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: svx_chrtitem.cxx,v $
 *
 *  $Revision: 1.7 $
 *
 *  last change: $Author: rt $ $Date: 2008-03-12 09:30:35 $
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

// include ---------------------------------------------------------------
 
#ifndef _STREAM_HXX
#include <tools/stream.hxx>
#endif
#if defined UNX && !defined LINUX
#include <wchar.h>
#endif

#ifdef MAC
#include <stdlib.h>
#endif

#include <stdio.h>
#include <float.h>

#define ITEMID_CHARTSTYLE       0
#define ITEMID_CHARTDATADESCR	0
#define ITEMID_CHARTLEGENDPOS	0
#define ITEMID_CHARTTEXTORDER	0
#define ITEMID_CHARTTEXTORIENT	0
#define ITEMID_CHARTKINDERROR	0
#define ITEMID_CHARTINDICATE	0
#define ITEMID_DOUBLE           0
#define ITEMID_CHARTREGRESS     0

#ifndef _SFXENUMITEM_HXX
#include <bf_svtools/eitem.hxx>
#endif

#include "chrtitem.hxx"

#ifdef _MSC_VER
#pragma hdrstop
#endif
namespace binfilter {

using namespace ::rtl;
using namespace ::com::sun::star;
// -----------------------------------------------------------------------

/*N*/ TYPEINIT1_AUTOFACTORY(SvxChartStyleItem, SfxEnumItem);
/*N*/ TYPEINIT1(SvxChartDataDescrItem, SfxEnumItem);
/*N*/ TYPEINIT1(SvxChartLegendPosItem, SfxEnumItem);
/*N*/ TYPEINIT1(SvxChartTextOrderItem, SfxEnumItem);
/*N*/ TYPEINIT1(SvxChartTextOrientItem, SfxEnumItem);
/*N*/ TYPEINIT1(SvxDoubleItem, SfxPoolItem);

/*************************************************************************
|*
|*	SvxChartStyleItem
|*
*************************************************************************/

/*N*/ SvxChartStyleItem::SvxChartStyleItem(SvxChartStyle eStyle, USHORT nId) :
/*N*/ 	SfxEnumItem(nId, eStyle)
/*N*/ {
/*N*/ }

// -----------------------------------------------------------------------


// -----------------------------------------------------------------------

/*N*/ SfxPoolItem* SvxChartStyleItem::Clone(SfxItemPool* pPool) const
/*N*/ {
/*N*/ 	return new SvxChartStyleItem(*this);
/*N*/ }

// -----------------------------------------------------------------------


/*************************************************************************
|*
|*	SvxChartDataDescrItem
|*
*************************************************************************/

/*N*/ SvxChartDataDescrItem::SvxChartDataDescrItem(SvxChartDataDescr eDataDescr,
/*N*/ 											 USHORT nId) :
/*N*/ 	SfxEnumItem(nId, eDataDescr)
/*N*/ {
/*N*/ }

// -----------------------------------------------------------------------

/*N*/ SvxChartDataDescrItem::SvxChartDataDescrItem(SvStream& rIn, USHORT nId) :
/*N*/ 	SfxEnumItem(nId, rIn)
/*N*/ {
/*N*/ }

/*N*/ // -----------------------------------------------------------------------
/*N*/ 
/*N*/ SfxPoolItem* SvxChartDataDescrItem::Clone(SfxItemPool* pPool) const
/*N*/ {
/*N*/ 	return new SvxChartDataDescrItem(*this);
/*N*/ }

// -----------------------------------------------------------------------

/*N*/ SfxPoolItem* SvxChartDataDescrItem::Create(SvStream& rIn, USHORT nVer) const
/*N*/ {
/*N*/ 	return new SvxChartDataDescrItem(rIn, Which());
/*N*/ }

/*************************************************************************
|*
|*	SvxChartLegendPosItem
|*
*************************************************************************/

/*N*/ SvxChartLegendPosItem::SvxChartLegendPosItem(SvxChartLegendPos eLegendPos,
/*N*/ 											 USHORT nId) :
/*N*/ 	SfxEnumItem(nId, eLegendPos)
/*N*/ {
/*N*/ }

// -----------------------------------------------------------------------

/*N*/ SvxChartLegendPosItem::SvxChartLegendPosItem(SvStream& rIn, USHORT nId) :
/*N*/ 	SfxEnumItem(nId, rIn)
/*N*/ {
/*N*/ }

// -----------------------------------------------------------------------

/*N*/ SfxPoolItem* SvxChartLegendPosItem::Clone(SfxItemPool* pPool) const
/*N*/ {
/*N*/ 	return new SvxChartLegendPosItem(*this);
/*N*/ }

// -----------------------------------------------------------------------

/*N*/ SfxPoolItem* SvxChartLegendPosItem::Create(SvStream& rIn, USHORT nVer) const
/*N*/ {
/*N*/ 	return new SvxChartLegendPosItem(rIn, Which());
/*N*/ }

/*************************************************************************
|*
|*	SvxChartTextOrderItem
|*
*************************************************************************/

/*N*/ SvxChartTextOrderItem::SvxChartTextOrderItem(SvxChartTextOrder eOrder,
/*N*/ 											 USHORT nId) :
/*N*/ 	SfxEnumItem(nId, eOrder)
/*N*/ {
/*N*/ }

// -----------------------------------------------------------------------

/*N*/ SvxChartTextOrderItem::SvxChartTextOrderItem(SvStream& rIn, USHORT nId) :
/*N*/ 	SfxEnumItem(nId, rIn)
/*N*/ {
/*N*/ }

// -----------------------------------------------------------------------

/*N*/ SfxPoolItem* SvxChartTextOrderItem::Clone(SfxItemPool* pPool) const
/*N*/ {
/*N*/ 	return new SvxChartTextOrderItem(*this);
/*N*/ }

// -----------------------------------------------------------------------

/*N*/ SfxPoolItem* SvxChartTextOrderItem::Create(SvStream& rIn, USHORT nVer) const
/*N*/ {
/*N*/ 	return new SvxChartTextOrderItem(rIn, Which());
/*N*/ }

/*************************************************************************
|*
|*	SvxChartTextOrientItem
|*
*************************************************************************/

/*N*/ SvxChartTextOrientItem::SvxChartTextOrientItem(SvxChartTextOrient eOrient,
/*N*/ 											   USHORT nId) :
/*N*/ 	SfxEnumItem(nId, eOrient)
/*N*/ {
/*N*/ }

// -----------------------------------------------------------------------

/*N*/ SvxChartTextOrientItem::SvxChartTextOrientItem(SvStream& rIn, USHORT nId) :
/*N*/ 	SfxEnumItem(nId, rIn)
/*N*/ {
/*N*/ }

// -----------------------------------------------------------------------

/*N*/ SfxPoolItem* SvxChartTextOrientItem::Clone(SfxItemPool* pPool) const
/*N*/ {
/*N*/ 	return new SvxChartTextOrientItem(*this);
/*N*/ }

// -----------------------------------------------------------------------

/*N*/ SfxPoolItem* SvxChartTextOrientItem::Create(SvStream& rIn, USHORT nVer) const
/*N*/ {
/*N*/ 	return new SvxChartTextOrientItem(rIn, Which());
/*N*/ }

/*************************************************************************
|*
|*	SvxDoubleItem
|*
*************************************************************************/

/*N*/ SvxDoubleItem::SvxDoubleItem(double fValue, USHORT nId) :
/*N*/ 	SfxPoolItem(nId),
/*N*/ 	fVal(fValue)
/*N*/ {
/*N*/ }

// -----------------------------------------------------------------------


// -----------------------------------------------------------------------

/*N*/ SvxDoubleItem::SvxDoubleItem(const SvxDoubleItem& rItem) :
/*N*/ 	SfxPoolItem(rItem),
/*N*/ 	fVal(rItem.fVal)
/*N*/ {
/*N*/ }

// -----------------------------------------------------------------------


// -----------------------------------------------------------------------


// -----------------------------------------------------------------------

/*N*/ int SvxDoubleItem::operator == (const SfxPoolItem& rItem) const
/*N*/ {
/*N*/ 	return (((SvxDoubleItem&)rItem).fVal == fVal);
/*N*/ }

// -----------------------------------------------------------------------

/*N*/ SfxPoolItem* SvxDoubleItem::Clone(SfxItemPool* Pool) const
/*N*/ {
/*N*/ 	return new SvxDoubleItem(*this);
/*N*/ }

// -----------------------------------------------------------------------

/*N*/ SfxPoolItem* SvxDoubleItem::Create(SvStream& rIn, USHORT nVersion) const
/*N*/ {
/*N*/ 	double fVal;
/*N*/ 	rIn >> fVal;
/*N*/ 	return new SvxDoubleItem(fVal, Which());
/*N*/ }

// -----------------------------------------------------------------------

/*N*/ SvStream& SvxDoubleItem::Store(SvStream& rOut, USHORT nItemVersion) const
/*N*/ {
/*N*/ 	rOut << fVal;
/*N*/ 	return rOut;
/*N*/ }

// -----------------------------------------------------------------------


// -----------------------------------------------------------------------


// -----------------------------------------------------------------------





// -----------------------------------------------------------------------
/*N*/ sal_Bool SvxDoubleItem::QueryValue( uno::Any& rVal, BYTE nMemberId ) const
/*N*/ {
/*N*/ 	rVal <<= fVal;
/*N*/ 	return sal_True;
/*N*/ }

// -----------------------------------------------------------------------
/*N*/ sal_Bool SvxDoubleItem::PutValue( const uno::Any& rVal, BYTE nMemberId )
/*N*/ {
/*N*/ 	return rVal >>= fVal;
/*N*/ }



/*************************************************************************
|*
|*	SvxChartKindErrorItem
|*
*************************************************************************/


// -----------------------------------------------------------------------


// -----------------------------------------------------------------------


// -----------------------------------------------------------------------


// -----------------------------------------------------------------------


/*************************************************************************
|*
|*	SvxChartIndicateItem
|*
*************************************************************************/


// -----------------------------------------------------------------------


// -----------------------------------------------------------------------


// -----------------------------------------------------------------------


// -----------------------------------------------------------------------


/*************************************************************************
|*
|*	SvxChartRegressItem
|*
*************************************************************************/


// -----------------------------------------------------------------------


// -----------------------------------------------------------------------


// -----------------------------------------------------------------------


// -----------------------------------------------------------------------



}
