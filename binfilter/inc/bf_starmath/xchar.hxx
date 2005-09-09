/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: xchar.hxx,v $
 *
 *  $Revision: 1.4 $
 *
 *  last change: $Author: rt $ $Date: 2005-09-09 12:53:01 $
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

#ifndef XCHAR_HXX
#define XCHAR_HXX


#ifndef _SV_GEN_HXX //autogen
#include <tools/gen.hxx>
#endif
#ifndef _SV_OUTDEV_HXX //autogen
#include <vcl/outdev.hxx>
#endif
#ifndef _TL_POLY_HXX
#include <tools/poly.hxx>
#endif
#ifndef _XPOLY_HXX //autogen
#include <bf_svx/xpoly.hxx>
#endif


#include "rect.hxx"
namespace binfilter {


//STRIP001 PolyPolygon  SmGetPolyPolygon(const XPolyPolygon &rPoly, OutputDevice *pDev);
//STRIP001 void 		 SmDrawPolyPolygon(OutputDevice &rDev, const PolyPolygon &rPPoly);


////////////////////////////////////////
// SmPolygon
//

class SmPolygonLoader;

class SmPolygon
{
    friend class SmPolygonLoader;

    XPolyPolygon	aPoly;
    Rectangle	  	aBoundRect;	// das umgebende Rechteck (ohne Rand!)
                                // wie von OutputDevice::GetBoundRect
    Size			aFontSize;  // vom Originalzeichen (Width != 0 aus FontMetric)
    Point			aPos;
    Size		  	aOrigSize;	// Originalgr��e (des BoundRect)
    Point			aOrigPos;	// Offset des BoundRect im Originalzeichen

    double		  	fScaleX,    // Skalierungsfaktoren der aktuellen (gewollten)
                    fScaleY,	// Gr��e gegen�ber der Originalgr��e

                    fDelayedFactorX,	// dienen zum sammeln der �nderungen
                    fDelayedFactorY;	// bis tats�chlich skaliert wird

    sal_Unicode     cChar;
    BOOL			bDelayedScale,
                    bDelayedBoundRect;

    void			Scale();

public:
    SmPolygon();
    SmPolygon(sal_Unicode cChar);
    // default copy-constructor verwenden

    const Size &  	GetOrigFontSize() const { return aFontSize; };
    const Size &	GetOrigSize() const { return aOrigSize; }
    const Point	&	GetOrigPos() const { return aOrigPos; }

    void 			ScaleBy(double fFactorX, double fFactorY);
    double			GetScaleX() const { return fScaleX * fDelayedFactorX; }
    double			GetScaleY() const { return fScaleY * fDelayedFactorY; }

    void 			AdaptToX(const OutputDevice &rDev, ULONG nWidth);
    void 			AdaptToY(const OutputDevice &rDev, ULONG nHeight);

    void 			Move  (const Point &rPoint);
    void 			MoveTo(const Point &rPoint) { Move(rPoint - aPos); }

    const sal_Unicode       GetChar() const { return cChar; }
//STRIP001 	const XPolyPolygon &	GetXPolyPolygon() const;
    const Rectangle & 		GetBoundRect(const OutputDevice &rDev) const;

//STRIP001 	void 			Draw(OutputDevice &rDev, const Point &rPoint) const;

    // default assignment-operator verwenden

    friend SvStream & operator >> (SvStream &rIStream, SmPolygon &rPoly);
    friend SvStream & operator << (SvStream &rOStream, const SmPolygon &rPoly);
};



} //namespace binfilter
#endif
