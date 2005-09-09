/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: svdtouch.hxx,v $
 *
 *  $Revision: 1.3 $
 *
 *  last change: $Author: rt $ $Date: 2005-09-09 14:46:54 $
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

#ifndef _SVDTOUCH_HXX
#define _SVDTOUCH_HXX

#ifndef _SOLAR_H
#include <tools/solar.h>
#endif
class Point;
class Polygon;
class PolyPolygon;
class Rectangle;
class OutputDevice;
namespace binfilter {

////////////////////////////////////////////////////////////////////////////////////////////////////

class XPolygon;
class XPolyPolygon;

FASTBOOL IsPointInsidePoly(const Polygon& rPoly, const Point& rHit);
//STRIP001 FASTBOOL IsPointInsidePoly(const PolyPolygon& rPoly, const Point& rHit);
//STRIP001 FASTBOOL IsPointInsidePoly(const XPolygon& rPoly, const Point& rHit, OutputDevice* pOut=NULL);
//STRIP001 FASTBOOL IsPointInsidePoly(const XPolyPolygon& rPoly, const Point& rHit, OutputDevice* pOut=NULL);

//STRIP001 FASTBOOL IsRectTouchesPoly(const Polygon& rPoly, const Rectangle& rHit);
FASTBOOL IsRectTouchesPoly(const PolyPolygon& rPoly, const Rectangle& rHit);
//STRIP001 FASTBOOL IsRectTouchesPoly(const XPolygon& rPoly, const Rectangle& rHit, OutputDevice* pOut=NULL);
//STRIP001 FASTBOOL IsRectTouchesPoly(const XPolyPolygon& rPoly, const Rectangle& rHit, OutputDevice* pOut=NULL);

//STRIP001 FASTBOOL IsRectTouchesLine(const Point& rPt1, const Point& rPt2, const Rectangle& rHit);
FASTBOOL IsRectTouchesLine(const Polygon& rLine, const Rectangle& rHit);
//STRIP001 FASTBOOL IsRectTouchesLine(const PolyPolygon& rLine, const Rectangle& rHit);
//STRIP001 FASTBOOL IsRectTouchesLine(const XPolygon& rLine, const Rectangle& rHit, OutputDevice* pOut=NULL);
//STRIP001 FASTBOOL IsRectTouchesLine(const XPolyPolygon& rLine, const Rectangle& rHit, OutputDevice* pOut=NULL);

////////////////////////////////////////////////////////////////////////////////////////////////////

}//end of namespace binfilter
#endif //_SVDTOUCH_HXX

