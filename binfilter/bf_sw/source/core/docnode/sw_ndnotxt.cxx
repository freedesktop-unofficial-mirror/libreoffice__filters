/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: sw_ndnotxt.cxx,v $
 *
 *  $Revision: 1.7 $
 *
 *  last change: $Author: rt $ $Date: 2005-09-08 08:48:21 $
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
#ifndef _SV_GRAPH_HXX
#include <vcl/graph.hxx>
#endif
#ifndef _SV_GDIMTF_HXX
#include <vcl/gdimtf.hxx>
#endif
#ifndef _IPOBJ_HXX
#include <so3/ipobj.hxx>
#endif
// auto strip #ifndef _HINTIDS_HXX
// auto strip #include <hintids.hxx>
// auto strip #endif

// auto strip #ifndef _IPOBJ_HXX
// auto strip #include <so3/ipobj.hxx>
// auto strip #endif
// auto strip #ifndef _TL_POLY_HXX
// auto strip #include <tools/poly.hxx>
// auto strip #endif
#ifndef _CONTDLG_HXX_
#include <bf_svx/contdlg.hxx>
#endif
// auto strip #ifndef _SV_SVAPP_HXX 
// auto strip #include <vcl/svapp.hxx>
// auto strip #endif

// auto strip #ifndef _DOCARY_HXX
// auto strip #include <docary.hxx>
// auto strip #endif

#ifndef _HORIORNT_HXX
#include <horiornt.hxx>
#endif

// auto strip #ifndef _DOC_HXX
// auto strip #include <doc.hxx>
// auto strip #endif

#ifndef _ERRHDL_HXX
#include <errhdl.hxx>
#endif

// auto strip #ifndef _FMTCOL_HXX
// auto strip #include <fmtcol.hxx>
// auto strip #endif
// auto strip #ifndef _NDNOTXT_HXX
// auto strip #include <ndnotxt.hxx>
// auto strip #endif
#ifndef _NDGRF_HXX
#include <ndgrf.hxx>
#endif
#ifndef _NDOLE_HXX
#include <ndole.hxx>
#endif
// auto strip #ifndef _NDINDEX_HXX
// auto strip #include <ndindex.hxx>
// auto strip #endif
#ifndef _HINTS_HXX
#include <hints.hxx>			// fuer SwFmtChg
#endif
namespace binfilter {


/*N*/ SwNoTxtNode::SwNoTxtNode( const SwNodeIndex & rWhere,
/*N*/ 				  const BYTE nNdType,
/*N*/ 				  SwGrfFmtColl *pGrfColl,
/*N*/ 				  SwAttrSet* pAutoAttr ) :
/*N*/ 	SwCntntNode( rWhere, nNdType, pGrfColl ),
/*N*/     pContour( 0 ),
/*N*/     bAutomaticContour( FALSE ),
/*N*/ 	bContourMapModeValid( TRUE ),
/*N*/ 	bPixelContour( FALSE )
/*N*/ {
/*N*/ 	// soll eine Harte-Attributierung gesetzt werden?
/*N*/ 	if( pAutoAttr )
/*N*/ 		SetAttr( *pAutoAttr );
/*N*/ }


/*N*/ SwNoTxtNode::~SwNoTxtNode()
/*N*/ {
/*N*/ 	delete pContour;
/*N*/ }


// erzeugt fuer alle Ableitungen einen AttrSet mit Bereichen
// fuer Frame- und Grafik-Attributen
/*N*/ void SwNoTxtNode::NewAttrSet( SwAttrPool& rPool )
/*N*/ {
/*N*/ 	ASSERT( !pAttrSet, "AttrSet ist doch gesetzt" );
/*N*/ 	pAttrSet = new SwAttrSet( rPool, aNoTxtNodeSetRange );
/*N*/ 	pAttrSet->SetParent( &GetFmtColl()->GetAttrSet() );
/*N*/ }

// Dummies fuer das Laden/Speichern von persistenten Daten
// bei Grafiken und OLE-Objekten


//STRIP001 BOOL SwNoTxtNode::RestorePersistentData()
//STRIP001 {
//STRIP001 	return TRUE;
//STRIP001 }


//STRIP001 BOOL SwNoTxtNode::SavePersistentData()
//STRIP001 {
//STRIP001 	return TRUE;
//STRIP001 }


/*N*/ void SwNoTxtNode::SetContour( const PolyPolygon *pPoly, BOOL bAutomatic )
/*N*/ {
/*N*/ 	delete pContour;
/*N*/ 	if ( pPoly )
/*?*/ 		pContour = new PolyPolygon( *pPoly );
/*N*/ 	else
/*N*/ 		pContour = 0;
/*N*/     bAutomaticContour = bAutomatic;
/*N*/ 	bContourMapModeValid = TRUE;
/*N*/ 	bPixelContour = FALSE;
/*N*/ }


//STRIP001 void SwNoTxtNode::CreateContour()
//STRIP001 {
//STRIP001 	ASSERT( !pContour, "Contour available." );
//STRIP001     pContour = new PolyPolygon(SvxContourDlg::CreateAutoContour(GetGraphic()));
//STRIP001     bAutomaticContour = TRUE;
//STRIP001 	bContourMapModeValid = TRUE;
//STRIP001 	bPixelContour = FALSE;
//STRIP001 }

/*N*/ const PolyPolygon *SwNoTxtNode::HasContour() const
/*N*/ {
/*N*/ 	if( !bContourMapModeValid )
/*N*/ 	{
/*?*/ 		DBG_BF_ASSERT(0, "STRIP"); //STRIP001 const MapMode aGrfMap( GetGraphic().GetPrefMapMode() );
//STRIP001 /*?*/ 		BOOL bPixelGrf = aGrfMap.GetMapUnit() == MAP_PIXEL;
//STRIP001 /*?*/ 		const MapMode aContourMap( bPixelGrf ? MAP_PIXEL : MAP_100TH_MM );
//STRIP001 /*?*/ 		if( bPixelGrf ? !bPixelContour : aGrfMap != aContourMap )
//STRIP001 /*?*/ 		{
//STRIP001 /*?*/ 			ASSERT( !bPixelGrf || aGrfMap == aContourMap,
//STRIP001 /*?*/ 					"scale factor for pixel unsupported" );
//STRIP001 /*?*/ 			OutputDevice* pOutDev =
//STRIP001 /*?*/ 				(bPixelGrf || bPixelContour) ? Application::GetDefaultDevice()
//STRIP001 /*?*/ 											 : 0;
//STRIP001 /*?*/ 			USHORT nPolyCount = pContour->Count();
//STRIP001 /*?*/ 			for( USHORT j=0; j<nPolyCount; j++ )
//STRIP001 /*?*/ 			{
//STRIP001 /*?*/ 				Polygon& rPoly = (*pContour)[j];
//STRIP001 /*?*/ 
//STRIP001 /*?*/ 				USHORT nCount = rPoly.GetSize();
//STRIP001 /*?*/ 				for( USHORT i=0 ; i<nCount; i++ )
//STRIP001 /*?*/ 				{
//STRIP001 /*?*/ 					if( bPixelGrf )
//STRIP001 /*?*/ 						rPoly[i] = pOutDev->LogicToPixel( rPoly[i],
//STRIP001 /*?*/ 														  aContourMap );
//STRIP001 /*?*/ 					else if( bPixelContour )
//STRIP001 /*?*/ 						rPoly[i] = pOutDev->PixelToLogic( rPoly[i], aGrfMap );
//STRIP001 /*?*/ 					else
//STRIP001 /*?*/ 						rPoly[i] = OutputDevice::LogicToLogic( rPoly[i],
//STRIP001 /*?*/ 														  	   aContourMap,
//STRIP001 /*?*/ 														  	   aGrfMap );
//STRIP001 /*?*/ 				}
//STRIP001 /*?*/ 			}
//STRIP001 /*?*/ 		}
//STRIP001 /*?*/ 		((SwNoTxtNode *)this)->bContourMapModeValid = TRUE;
//STRIP001 /*?*/ 		((SwNoTxtNode *)this)->bPixelContour = FALSE;
/*N*/ 	}
/*N*/ 
/*N*/ 	return pContour;
/*N*/ }

//STRIP001 void SwNoTxtNode::GetContour( PolyPolygon &rPoly ) const
//STRIP001 {
//STRIP001 	ASSERT( pContour, "Contour not available." );
//STRIP001 	rPoly = *HasContour();
//STRIP001 }

//STRIP001 void SwNoTxtNode::SetContourAPI( const PolyPolygon *pPoly )
//STRIP001 {
//STRIP001 	delete pContour;
//STRIP001 	if ( pPoly )
//STRIP001 		pContour = new PolyPolygon( *pPoly );
//STRIP001 	else
//STRIP001 		pContour = 0;
//STRIP001 	bContourMapModeValid = FALSE;
//STRIP001 }

/*N*/ BOOL SwNoTxtNode::GetContourAPI( PolyPolygon &rContour ) const
/*N*/ {
/*N*/ 	if( !pContour )
/*N*/ 		return FALSE;
/*N*/ 
/*?*/ 	rContour = *pContour;
/*?*/ 	if( bContourMapModeValid )
/*?*/ 	{
/*?*/       const MapMode aGrfMap( GetGraphic().GetPrefMapMode() );
 /*?*/      const MapMode aContourMap( MAP_100TH_MM );
 /*?*/      ASSERT( aGrfMap.GetMapUnit() != MAP_PIXEL ||
 /*?*/              aGrfMap == MapMode( MAP_PIXEL ),
 /*?*/                  "scale factor for pixel unsupported" );
 /*?*/      if( aGrfMap.GetMapUnit() != MAP_PIXEL &&
 /*?*/          aGrfMap != aContourMap )
 /*?*/      {
 /*?*/          USHORT nPolyCount = rContour.Count();
 /*?*/          for( USHORT j=0; j<nPolyCount; j++ )
 /*?*/          {
 /*?*/              Polygon& rPoly = (*pContour)[j];
 /*?*/ 
 /*?*/              USHORT nCount = rPoly.GetSize();
 /*?*/              for( USHORT i=0 ; i<nCount; i++ )
 /*?*/              {
 /*?*/                  rPoly[i] = OutputDevice::LogicToLogic( rPoly[i], aGrfMap,
 /*?*/                                                         aContourMap );
 /*?*/              }
 /*?*/          }
 /*?*/      }
/*?*/ 	}
/*?*/ 
/*?*/ 	return TRUE;
/*N*/ }

const BOOL SwNoTxtNode::IsPixelContour() const
{
    BOOL bRet;
    if( bContourMapModeValid )
    {
        const MapMode aGrfMap( GetGraphic().GetPrefMapMode() );
        bRet = aGrfMap.GetMapUnit() == MAP_PIXEL;
    }
    else
    {
        bRet = bPixelContour;
    }

    return bRet;
}


Graphic SwNoTxtNode::GetGraphic() const
{
    Graphic aRet;
    if ( GetGrfNode() )
    {
        ((SwGrfNode*)this)->SwapIn( TRUE );
        aRet = ((SwGrfNode*)this)->GetGrf();
    }
    else
    {
        ASSERT( GetOLENode(), "new type of Node?" );
        SvInPlaceObjectRef xObj( ((SwOLENode*)this)->GetOLEObj().GetOleRef() );
        GDIMetaFile aMtf;
        aRet = xObj->GetGDIMetaFile( aMtf );
    }
    return aRet;
}


/*N*/ void SwNoTxtNode::SetAlternateText( const String& rTxt, sal_Bool bBroadcast )
/*N*/ {
/*N*/ 	if( bBroadcast )
/*N*/ 	{
/*?*/ 		SwStringMsgPoolItem aOld( RES_ALT_TEXT_CHANGED, aAlternateText );
/*?*/ 		SwStringMsgPoolItem aNew( RES_ALT_TEXT_CHANGED, rTxt );
/*?*/ 		aAlternateText = rTxt;
/*?*/ 		Modify( &aOld, &aNew );
/*N*/ 	}
/*N*/ 	else
/*N*/ 	{
/*N*/ 		aAlternateText = rTxt;
/*N*/ 	}
/*N*/ }

}
