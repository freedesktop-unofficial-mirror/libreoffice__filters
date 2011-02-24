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


#ifdef _MSC_VER
#pragma hdrstop
#endif
#include <vcl/graph.hxx>
#include <vcl/gdimtf.hxx>
#include <bf_so3/ipobj.hxx>

#include <tools/poly.hxx>
#include <vcl/outdev.hxx>

#include <horiornt.hxx>


#include <osl/diagnose.h>

#include <ndgrf.hxx>
#include <ndole.hxx>
#include <hints.hxx>			// fuer SwFmtChg
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
/*N*/ 	OSL_ENSURE( !pAttrSet, "AttrSet ist doch gesetzt" );
/*N*/ 	pAttrSet = new SwAttrSet( rPool, aNoTxtNodeSetRange );
/*N*/ 	pAttrSet->SetParent( &GetFmtColl()->GetAttrSet() );
/*N*/ }

// Dummies fuer das Laden/Speichern von persistenten Daten
// bei Grafiken und OLE-Objekten






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



/*N*/ const PolyPolygon *SwNoTxtNode::HasContour() const
/*N*/ {
/*N*/ 	if( !bContourMapModeValid )
/*N*/ 	{
/*?*/ 		DBG_BF_ASSERT(0, "STRIP");
/*N*/ 	}
/*N*/ 
/*N*/ 	return pContour;
/*N*/ }



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
 /*?*/      OSL_ENSURE( aGrfMap.GetMapUnit() != MAP_PIXEL ||
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

BOOL SwNoTxtNode::IsPixelContour() const
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
        OSL_ENSURE( GetOLENode(), "new type of Node?" );
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

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
