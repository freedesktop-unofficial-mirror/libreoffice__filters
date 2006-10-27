/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: sw_pagedesc.cxx,v $
 *
 *  $Revision: 1.5 $
 *
 *  last change: $Author: rt $ $Date: 2006-10-27 22:54:54 $
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

#define ITEMID_BOXINFO      SID_ATTR_BORDER_INNER
#include <hintids.hxx>

#ifndef _SVX_PBINITEM_HXX //autogen
#include <bf_svx/pbinitem.hxx>
#endif
#ifndef _SVX_ULSPITEM_HXX //autogen
#include <bf_svx/ulspitem.hxx>
#endif
#ifndef _SVX_BOXITEM_HXX //autogen
#include <bf_svx/boxitem.hxx>
#endif
#ifndef _SVX_BRSHITEM_HXX //autogen
#include <bf_svx/brshitem.hxx>
#endif
#ifndef _SVX_SHADITEM_HXX //autogen
#include <bf_svx/shaditem.hxx>
#endif
#ifndef _SVX_LRSPITEM_HXX //autogen
#include <bf_svx/lrspitem.hxx>
#endif
#ifndef _SVX_FRMDIRITEM_HXX
#include "bf_svx/frmdiritem.hxx"
#endif
#ifndef _FMTCLDS_HXX //autogen
#include <fmtclds.hxx>
#endif
#ifndef _FMTFSIZE_HXX //autogen
#include <fmtfsize.hxx>
#endif
#ifndef _FRMATR_HXX
#include <frmatr.hxx>
#endif
#ifndef _PAGEFRM_HXX //autogen
#include <pagefrm.hxx>
#endif
#ifndef _PAGEDESC_HXX
#include <pagedesc.hxx>
#endif
#ifndef _NODE_HXX //autogen
#include <node.hxx>
#endif

#ifndef _HORIORNT_HXX
#include <horiornt.hxx>
#endif

#ifndef _DOC_HXX
#include <doc.hxx>			// fuer GetAttrPool
#endif
namespace binfilter {

/*************************************************************************
|*
|*	SwPageDesc::SwPageDesc()
|*
|*	Ersterstellung		MA 25. Jan. 93
|*	Letzte Aenderung	MA 16. Feb. 94
|*
|*************************************************************************/



/*N*/ SwPageDesc::SwPageDesc( const String& rName, SwFrmFmt *pFmt, SwDoc *pDc ) :
/*N*/ 	SwModify( 0 ),
/*N*/ 	aDescName( rName ),
/*N*/ 	aDepend( this, 0 ),
/*N*/ 	nRegHeight( 0 ),
/*N*/ 	nRegAscent( 0 ),
/*N*/ 	bLandscape( FALSE ),
/*N*/ 	eUse( (UseOnPage)(PD_ALL | PD_HEADERSHARE | PD_FOOTERSHARE) ),
/*N*/ 	aMaster( pDc->GetAttrPool(), rName, pFmt ),
/*N*/ 	aLeft( pDc->GetAttrPool(), rName, pFmt ),
/*N*/ 	pFollow( this ),
/*N*/ 	aFtnInfo()
/*N*/ {
/*N*/ }



/*N*/ SwPageDesc::SwPageDesc( const SwPageDesc &rCpy ) :
/*N*/ 	SwModify( 0 ),
/*N*/ 	aDepend( this, (SwModify*)rCpy.aDepend.GetRegisteredIn() ),
/*N*/ 	nRegHeight( rCpy.GetRegHeight() ),
/*N*/ 	nRegAscent( rCpy.GetRegAscent() ),
/*N*/ 	aDescName( rCpy.GetName() ),
/*N*/ 	bLandscape( rCpy.GetLandscape() ),
/*N*/ 	aNumType( rCpy.GetNumType() ),
/*N*/ 	eUse( rCpy.ReadUseOn() ),
/*N*/ 	aMaster( rCpy.GetMaster() ),
/*N*/ 	aLeft( rCpy.GetLeft() ),
/*N*/ 	pFollow( rCpy.pFollow ),
/*N*/ 	aFtnInfo( rCpy.GetFtnInfo() )
/*N*/ {
/*N*/ }



/*N*/ SwPageDesc::~SwPageDesc()
/*N*/ {
/*N*/ }

/*************************************************************************
|*
|*	SwPageDesc::Mirror()
|*
|* 	Beschreibung		Gespiegelt werden nur die Raender.
|* 		Attribute wie Umrandung und dergleichen werden 1:1 kopiert.
|*	Ersterstellung		MA 25. Jan. 93
|*	Letzte Aenderung	01. Nov. 94
|*
|*************************************************************************/



/*N*/ void SwPageDesc::Mirror()
/*N*/ {
/*N*/ 	//Das Spiegeln findet nur beim RandAttribut statt, alle anderen Werte
/*N*/ 	//werden schlicht uebertragen.
/*N*/ 	SvxLRSpaceItem aLR;
/*N*/ 	const SvxLRSpaceItem &rLR = aMaster.GetLRSpace();
/*N*/ 	aLR.SetLeft(  rLR.GetRight() );
/*N*/ 	aLR.SetRight( rLR.GetLeft() );
/*N*/ 
/*N*/ 	SfxItemSet aSet( *aMaster.GetAttrSet().GetPool(),
/*N*/ 					 aMaster.GetAttrSet().GetRanges() );
/*N*/ 	aSet.Put( aLR );
/*N*/ 	aSet.Put( aMaster.GetFrmSize() );
/*N*/ 	aSet.Put( aMaster.GetPaperBin() );
/*N*/ 	aSet.Put( aMaster.GetULSpace() );
/*N*/ 	aSet.Put( aMaster.GetBox() );
/*N*/ 	aSet.Put( aMaster.GetBackground() );
/*N*/ 	aSet.Put( aMaster.GetShadow() );
/*N*/ 	aSet.Put( aMaster.GetCol() );
/*N*/ 	aLeft.SetAttr( aSet );
/*N*/ }

/*N*/ void SwPageDesc::ResetAllAttr( sal_Bool bLeft )
/*N*/ {
/*N*/ 	SwFrmFmt& rFmt = bLeft ? GetLeft() : GetMaster();
/*N*/ 
/*N*/ 	rFmt.ResetAllAttr();
/*N*/ 	rFmt.SetAttr( SvxFrameDirectionItem() );
/*N*/ }

/*************************************************************************
|*
|*                SwPageDesc::GetInfo()
|*
|*    Beschreibung      erfragt Informationen
|*    Ersterstellung    JP 31.03.94
|*    Letzte Aenderung	JP 31.03.94
|*
*************************************************************************/


    // erfrage vom Modify Informationen

/*************************************************************************
|*
|*                SwPageDesc::SetRegisterFmtColl()
|*
|*    Beschreibung      setzt die Vorlage fuer die Registerhaltigkeit
|*    Ersterstellung    AMA 22.07.96
|*    Letzte Aenderung	AMA 22.07.96
|*
*************************************************************************/


/*N*/ void SwPageDesc::SetRegisterFmtColl( const SwTxtFmtColl* pFmt )
/*N*/ {
/*N*/ 	if( pFmt != GetRegisterFmtColl() )
/*N*/ 	{
/*N*/ 		if( pFmt )
/*N*/ 			((SwTxtFmtColl*)pFmt)->Add( &aDepend );
/*N*/ 		else
/*?*/ 			((SwTxtFmtColl*)GetRegisterFmtColl())->Remove( &aDepend );
/*N*/ 
/*N*/ 		RegisterChange();
/*N*/ 	}
/*N*/ }

/*************************************************************************
|*
|*                SwPageDesc::GetRegisterFmtColl()
|*
|*    Beschreibung      holt die Vorlage fuer die Registerhaltigkeit
|*    Ersterstellung    AMA 22.07.96
|*    Letzte Aenderung	AMA 22.07.96
|*
*************************************************************************/


/*N*/ const SwTxtFmtColl* SwPageDesc::GetRegisterFmtColl() const
/*N*/ {
/*N*/ 	const SwModify* pReg = aDepend.GetRegisteredIn();
/*N*/ 	return (SwTxtFmtColl*)pReg;
/*N*/ }

/*************************************************************************
|*
|*                SwPageDesc::RegisterChange()
|*
|*    Beschreibung      benachrichtigt alle betroffenen PageFrames
|*    Ersterstellung    AMA 22.07.96
|*    Letzte Aenderung	AMA 22.07.96
|*
*************************************************************************/


/*N*/ void SwPageDesc::RegisterChange()
/*N*/ {
/*N*/ 	nRegHeight = 0;
/*N*/ 	{
/*N*/ 		SwClientIter aIter( GetMaster() );
/*N*/ 		for( SwClient* pLast = aIter.First(TYPE(SwFrm)); pLast;
/*N*/ 				pLast = aIter.Next() )
/*N*/ 		{
/*N*/ 			if( ((SwFrm*)pLast)->IsPageFrm() )
/*N*/ 				((SwPageFrm*)pLast)->PrepareRegisterChg();
/*N*/ 		}
/*N*/ 	}
/*N*/ 	{
/*N*/ 		SwClientIter aIter( GetLeft() );
/*N*/ 		for( SwClient* pLast = aIter.First(TYPE(SwFrm)); pLast;
/*N*/ 				pLast = aIter.Next() )
/*N*/ 		{
/*N*/ 			if( ((SwFrm*)pLast)->IsPageFrm() )
/*N*/ 				((SwPageFrm*)pLast)->PrepareRegisterChg();
/*N*/ 		}
/*N*/ 	}
/*N*/ }

/*************************************************************************
|*
|*                SwPageDesc::Modify()
|*
|*    Beschreibung      reagiert insbesondere auf Aenderungen
|* 	                    der Vorlage fuer die Registerhaltigkeit
|*    Ersterstellung    AMA 22.07.96
|*    Letzte Aenderung	AMA 22.07.96
|*
*************************************************************************/


/*N*/ void SwPageDesc::Modify( SfxPoolItem *pOld, SfxPoolItem *pNew )
/*N*/ {
/*N*/ 	const USHORT nWhich = pOld ? pOld->Which() : pNew ? pNew->Which() : 0;
/*N*/ 	SwModify::Modify( pOld, pNew );
/*N*/ 
/*N*/ 	if( RES_ATTRSET_CHG == nWhich || RES_FMT_CHG == nWhich ||
/*N*/ 		( nWhich >= RES_CHRATR_BEGIN && nWhich < RES_CHRATR_END ) ||
/*N*/ 		 nWhich == RES_PARATR_LINESPACING )
/*N*/ 		RegisterChange();
/*N*/ }





/*************************************************************************
|*
|*	SwPageFtnInfo::SwPageFtnInfo()
|*
|*	Ersterstellung		MA 24. Feb. 93
|*	Letzte Aenderung	MA 24. Feb. 93
|*
|*************************************************************************/



/*N*/ SwPageFtnInfo::SwPageFtnInfo() :
/*N*/ 	nMaxHeight( 0 ),
/*N*/ //	aPen( PEN_SOLID ),
/*N*/ 	nLineWidth(10),
/*N*/ 	aWidth( 25, 100 ),
/*N*/ 	eAdj( FTNADJ_LEFT ),
/*N*/ 	nTopDist( 57 ),			//1mm
/*N*/ 	nBottomDist( 57 )
/*N*/ {
/*N*/ //	aPen.SetWidth( 10 );
/*N*/ }



/*N*/ SwPageFtnInfo::SwPageFtnInfo( const SwPageFtnInfo &rCpy ) :
/*N*/ 	nMaxHeight( rCpy.GetHeight() ),
/*N*/ //	aPen( rCpy.GetPen() ),
/*N*/ 	nLineWidth(rCpy.nLineWidth),
/*N*/ 	aLineColor(rCpy.aLineColor),
/*N*/ 	aWidth( rCpy.GetWidth() ),
/*N*/ 	eAdj( rCpy.GetAdj() ),
/*N*/ 	nTopDist( rCpy.GetTopDist() ),
/*N*/ 	nBottomDist( rCpy.GetBottomDist() )
/*N*/ {
/*N*/ }

/*************************************************************************
|*
|*	SwPageFtnInfo::operator=
|*
|*	Ersterstellung		MA 24. Feb. 93
|*	Letzte Aenderung	MA 24. Feb. 93
|*
|*************************************************************************/



/*N*/ SwPageFtnInfo &SwPageFtnInfo::operator=( const SwPageFtnInfo& rCpy )
/*N*/ {
/*N*/ 	nMaxHeight	= rCpy.GetHeight();
/*N*/ //	aPen		= rCpy.GetPen();
/*N*/ 	nLineWidth 	= rCpy.nLineWidth;
/*N*/ 	aLineColor 	= rCpy.aLineColor;
/*N*/ 	aWidth		= rCpy.GetWidth();
/*N*/ 	eAdj		= rCpy.GetAdj();
/*N*/ 	nTopDist	= rCpy.GetTopDist();
/*N*/ 	nBottomDist = rCpy.GetBottomDist();
/*N*/ 	return *this;
/*N*/ }
/*************************************************************************
|*
|*	SwPageFtnInfo::operator==
|*
|*	Ersterstellung		MA 01. Mar. 93
|*	Letzte Aenderung	MA 01. Mar. 93
|*
|*************************************************************************/



/*N*/ BOOL SwPageFtnInfo::operator==( const SwPageFtnInfo& rCmp ) const
/*N*/ {
/*N*/ //	const Pen aTmp( rCmp.GetPen() );
/*N*/ 	return ( nMaxHeight == rCmp.GetHeight() &&
/*N*/ //			 aPen       == aTmp &&
/*N*/ 			 nLineWidth == rCmp.nLineWidth &&
/*N*/ 			 aLineColor == rCmp.aLineColor &&
/*N*/ 			 aWidth     == rCmp.GetWidth() &&
/*N*/ 			 eAdj       == rCmp.GetAdj() &&
/*N*/ 			 nTopDist   == rCmp.GetTopDist() &&
/*N*/ 			 nBottomDist== rCmp.GetBottomDist() );
/*N*/ }




}
