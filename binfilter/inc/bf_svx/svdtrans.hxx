/*************************************************************************
 *
 *  $RCSfile: svdtrans.hxx,v $
 *
 *  $Revision: 1.3 $
 *
 *  last change: $Author: aw $ $Date: 2004-02-13 14:31:08 $
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

#ifndef _SVDTRANS_HXX
#define _SVDTRANS_HXX

#ifndef _GEN_HXX //autogen
#include <tools/gen.hxx>
#endif

#ifndef _TL_POLY_HXX
#include <tools/poly.hxx>
#endif

#ifndef _FRACT_HXX //autogen
#include <tools/fract.hxx>
#endif

#ifndef _MAPMOD_HXX //autogen
#include <vcl/mapmod.hxx>
#endif

#ifndef _STRING_HXX //autogen
#include <tools/string.hxx>
#endif

#include <vcl/field.hxx>
namespace binfilter {

////////////////////////////////////////////////////////////////////////////////////////////////////

// Winkelangaben der DrawingEngine sind 1/100 Degree
// const nWinkDiv=100;
// Um Winkel der DrawingEngine mit den Trigonometrischen Funktionen
// verarbeiten zu koennen, muessen sie zunaest ins Bogenmass umgerechnet
// werden. Dies gestaltet sich recht einfach mit der folgenden Konstanten
// nPi180. Sei nWink ein Winkel in 1/100 Deg so schreibt man z.B.:
//   double nSin=sin(nWink*nPi180);
// Rueckwandlung entsprechend durch Teilen.
const double nPi=3.14159265358979323846;
const double nPi180=0.000174532925199432957692222; // Bei zuweing Stellen ist tan(4500*nPi180)!=1.0

// Der maximale Shearwinkel
#define SDRMAXSHEAR 8900

class XPolygon;
class XPolyPolygon;

inline long Round(double a) { return a>0.0 ? (long)(a+0.5) : -(long)((-a)+0.5); }

inline void MoveRect(Rectangle& rRect, const Size& S)    { rRect.Move(S.Width(),S.Height()); }
inline void MovePoint(Point& rPnt, const Size& S)        { rPnt.X()+=S.Width(); rPnt.Y()+=S.Height(); }
inline void MovePoly(Polygon& rPoly, const Size& S)      { rPoly.Move(S.Width(),S.Height()); }
inline void MovePoly(PolyPolygon& rPoly, const Size& S)  { rPoly.Move(S.Width(),S.Height()); }
void MoveXPoly(XPolygon& rPoly, const Size& S);
void MoveXPoly(XPolyPolygon& rPoly, const Size& S);

void ResizeRect(Rectangle& rRect, const Point& rRef, const Fraction& xFact, const Fraction& yFact, FASTBOOL bNoJustify=FALSE);
inline void ResizePoint(Point& rPnt, const Point& rRef, Fraction xFact, Fraction yFact);
void ResizePoly(Polygon& rPoly, const Point& rRef, const Fraction& xFact, const Fraction& yFact);
void ResizeXPoly(XPolygon& rPoly, const Point& rRef, const Fraction& xFact, const Fraction& yFact);
void ResizePoly(PolyPolygon& rPoly, const Point& rRef, const Fraction& xFact, const Fraction& yFact);
void ResizeXPoly(XPolyPolygon& rPoly, const Point& rRef, const Fraction& xFact, const Fraction& yFact);

inline void RotatePoint(Point& rPnt, const Point& rRef, double sn, double cs);
void RotatePoly(Polygon& rPoly, const Point& rRef, double sn, double cs);
void RotateXPoly(XPolygon& rPoly, const Point& rRef, double sn, double cs);
void RotatePoly(PolyPolygon& rPoly, const Point& rRef, double sn, double cs);
void RotateXPoly(XPolyPolygon& rPoly, const Point& rRef, double sn, double cs);

// MirrorRect macht nur Sinn bei Spiegelachsen
// mit einem durch 45 Degree teilbaren Winkel!
//STRIP001 void MirrorRect(Rectangle& rRect, const Point& rRef1, const Point& rRef2, FASTBOOL bNoJustify); // ni.
//STRIP001 void MirrorPoint(Point& rPnt, const Point& rRef1, const Point& rRef2);
//STRIP001 void MirrorPoly(Polygon& rPoly, const Point& rRef1, const Point& rRef2);
//STRIP001 void MirrorXPoly(XPolygon& rPoly, const Point& rRef1, const Point& rRef2);
//STRIP001 void MirrorPoly(PolyPolygon& rPoly, const Point& rRef1, const Point& rRef2);
//STRIP001 void MirrorXPoly(XPolyPolygon& rPoly, const Point& rRef1, const Point& rRef2);

inline void ShearPoint(Point& rPnt, const Point& rRef, double tn, FASTBOOL bVShear=FALSE);
void ShearPoly(Polygon& rPoly, const Point& rRef, double tn, FASTBOOL bVShear=FALSE);
void ShearXPoly(XPolygon& rPoly, const Point& rRef, double tn, FASTBOOL bVShear=FALSE);
void ShearPoly(PolyPolygon& rPoly, const Point& rRef, double tn, FASTBOOL bVShear=FALSE);
void ShearXPoly(XPolyPolygon& rPoly, const Point& rRef, double tn, FASTBOOL bVShear=FALSE);

// rPnt.X bzw rPnt.Y wird auf rCenter.X bzw. rCenter.Y gesetzt!
// anschliessend muss rPnt nur noch um rCenter gedreht werden.
// Der Rueckgabewinkel ist ausnahmsweise in Rad.
inline double GetCrookAngle(Point& rPnt, const Point& rCenter, const Point& rRad, FASTBOOL bVertical);
// Die folgenden Methoden behandeln einen Punkt eines XPolygons, wobei die
// benachbarten Kontrollpunkte des eigentlichen Punktes ggf. in pC1/pC2
// uebergeben werden. Ueber rSin/rCos wird gleichzeitig sin(nWink) und cos(nWink)
// zurueckgegeben.
// Der Rueckgabewinkel ist hier ebenfalls in Rad.
//STRIP001 double CrookRotateXPoint(Point& rPnt, Point* pC1, Point* pC2, const Point& rCenter,
//STRIP001 						 const Point& rRad, double& rSin, double& rCos, FASTBOOL bVert);
//STRIP001 double CrookSlantXPoint(Point& rPnt, Point* pC1, Point* pC2, const Point& rCenter,
//STRIP001 						const Point& rRad, double& rSin, double& rCos, FASTBOOL bVert);
//STRIP001 double CrookStretchXPoint(Point& rPnt, Point* pC1, Point* pC2, const Point& rCenter,
//STRIP001 						  const Point& rRad, double& rSin, double& rCos, FASTBOOL bVert,
//STRIP001 						  const Rectangle rRefRect);

//STRIP001 void CrookRotatePoly(XPolygon& rPoly, const Point& rCenter, const Point& rRad, FASTBOOL bVert);
//STRIP001 void CrookSlantPoly(XPolygon& rPoly, const Point& rCenter, const Point& rRad, FASTBOOL bVert);
//STRIP001 void CrookStretchPoly(XPolygon& rPoly, const Point& rCenter, const Point& rRad, FASTBOOL bVert, const Rectangle rRefRect);

//STRIP001 void CrookRotatePoly(XPolyPolygon& rPoly, const Point& rCenter, const Point& rRad, FASTBOOL bVert);
//STRIP001 void CrookSlantPoly(XPolyPolygon& rPoly, const Point& rCenter, const Point& rRad, FASTBOOL bVert);
//STRIP001 void CrookStretchPoly(XPolyPolygon& rPoly, const Point& rCenter, const Point& rRad, FASTBOOL bVert, const Rectangle rRefRect);

/**************************************************************************************************/
/*  Inline                                                                                        */
/**************************************************************************************************/

inline void ResizePoint(Point& rPnt, const Point& rRef, Fraction xFact, Fraction yFact)
{
    if (xFact.GetDenominator()==0) xFact=Fraction(xFact.GetNumerator(),1); // DivZero abfangen
    if (yFact.GetDenominator()==0) yFact=Fraction(yFact.GetNumerator(),1); // DivZero abfangen
    rPnt.X()=rRef.X()+ Round(((double)(rPnt.X()-rRef.X())*xFact.GetNumerator())/xFact.GetDenominator());
    rPnt.Y()=rRef.Y()+ Round(((double)(rPnt.Y()-rRef.Y())*yFact.GetNumerator())/yFact.GetDenominator());
}

inline void RotatePoint(Point& rPnt, const Point& rRef, double sn, double cs)
{
    long dx=rPnt.X()-rRef.X();
    long dy=rPnt.Y()-rRef.Y();
    rPnt.X()=Round(rRef.X()+dx*cs+dy*sn);
    rPnt.Y()=Round(rRef.Y()+dy*cs-dx*sn);
}

inline void ShearPoint(Point& rPnt, const Point& rRef, double tn, FASTBOOL bVShear)
{
    if (!bVShear) { // Horizontal
        if (rPnt.Y()!=rRef.Y()) { // sonst nicht noetig
            rPnt.X()-=Round((rPnt.Y()-rRef.Y())*tn);
        }
    } else { // ansonsten vertikal
        if (rPnt.X()!=rRef.X()) { // sonst nicht noetig
            rPnt.Y()-=Round((rPnt.X()-rRef.X())*tn);
        }
    }
}

inline double GetCrookAngle(Point& rPnt, const Point& rCenter, const Point& rRad, FASTBOOL bVertical)
{
    double nWink;
    if (bVertical) {
        long dy=rPnt.Y()-rCenter.Y();
        nWink=(double)dy/(double)rRad.Y();
        rPnt.Y()=rCenter.Y();
    } else {
        long dx=rCenter.X()-rPnt.X();
        nWink=(double)dx/(double)rRad.X();
        rPnt.X()=rCenter.X();
    }
    return nWink;
}

/**************************************************************************************************/
/**************************************************************************************************/

// Y-Achse zeigt nach unten! Die Funktion negiert bei der
// Winkelberechnung die Y-Achse, sodass GetAngle(Point(0,-1))=90.00?
// GetAngle(Point(0,0)) liefert 0.
// Der Rueckgabewert liegt im Bereich -180.00..179.99 Degree und
// ist in 1/100 Degree angegeben.
long GetAngle(const Point& rPnt);
long NormAngle180(long a); // Winkel normalisieren auf -180.00..179.99
long NormAngle360(long a); // Winkel normalisieren auf    0.00..359.99
USHORT GetAngleSector(long nWink); // Sektor im kartesischen Koordinatensystem bestimmen
// Berechnet die Laenge von (0,0) via a^2 + b^2 = c^2
// Zur Vermeidung von Ueberlaeufen werden ggf. einige Stellen ignoriert.
long GetLen(const Point& rPnt);

/*
  Transformation eines Rechtecks in ein Polygon unter            ?---------?
  Anwendung der Winkelparameter aus GeoStat.                    /1        2/
  Referenzpunkt ist stets der Punkt 0, also die linke          /          /
  obere Ecke des Ausgangsrects.                               /          /
  Bei der Berechnung des Polygons ist die Reihenfolge        /          /
  (erst Shear, dann Rotation vorgegeben).                   /          / \
                                                           /          /   |
  A) Ausgangsrechteck aRect  B) Nach Anwendung von Shear  /0        3/  Rot|
  ?-----------------?      ?-----------------?       ?---------? ------
  |0                1|        \0                1\       C) Nach Anwendung
  |                  |         \                  \      von Rotate
  |                  |       |  \                  \
  |3                2|       |   \3                2\
  ?-----------------?      |    ?-----------------?
                             |Shr |
  Bei Rueckkonvertierung des        Polygons in ein Rect ist die Reihenfolge
  zwangslaeufig umgekehrt:
  - Berechnung des Drehwinkels: Winkel der Strecke 0-1 aus Abb. C) zum Horizont
  - Rueckdrehung des geshearten Rects (man erhaelt Abb B))
  - Bestimmung der Breite des Rects=Laenge der Strecke 0-1 aus Abb. B)
  - Bestimmung der Hoehe des Rects=vertikaler Abstand zwischen den Punkten
    0 und 3 aus Abb. B)
  - Bestimmung des Shear-Winkels aus der Strecke 0-3 zur Senkrechten.
  Es ist darauf zu achten, dass das Polygon bei einer zwischenzeitlichen
  Transformation evtl. gespiegelt wurde (Mirror oder Resize mit neg. Faktor).
  In diesem Fall muss zunaecht eine Normalisierung durch Vertauschung der
  Punkte (z.B. 0 mit 3 und 1 mit 2) durchgefuehrt werden, damit der
  Richtungssinn im Polygon wieder stimmig ist.
  Hinweis: Positiver Shear-Winkel bedeutet Shear mit auf dem Bildschirm
  sichtbarer positiver Kursivierung. Mathematisch waere dass eine negative
  Kursivierung, da die Y-Achse auf dem Bildschirm von oben nach unten verlaeuft.
  Drehwinkel: Positiv bedeutet auf dem Bildschirm sichtbare Linksdrehung.
*/

class GeoStat { // Geometrischer Status fuer ein Rect
public:
    long     nDrehWink;
    long     nShearWink;
    double   nTan;      // tan(nShearWink)
    double   nSin;      // sin(nDrehWink)
    double   nCos;      // cos(nDrehWink)
    FASTBOOL bMirrored; // Horizontal gespiegelt? (ni)
public:
    GeoStat(): nDrehWink(0),nShearWink(0),nTan(0.0),nSin(0.0),nCos(1.0),bMirrored(FALSE) {}
    void RecalcSinCos();
    void RecalcTan();
};

Polygon Rect2Poly(const Rectangle& rRect, const GeoStat& rGeo);
void Poly2Rect(const Polygon& rPol, Rectangle& rRect, GeoStat& rGeo);

void OrthoDistance8(const Point& rPt0, Point& rPt, FASTBOOL bBigOrtho);
void OrthoDistance4(const Point& rPt0, Point& rPt, FASTBOOL bBigOrtho);

// Multiplikation und anschliessende Division.
// Rechnung und Zwischenergebnis sind BigInt.
long BigMulDiv(long nVal, long nMul, long nDiv);

// Fehlerbehaftetes Kuerzen einer Fraction.
// nDigits gibt an, wieviele signifikante Stellen in
// Zaehler/Nenner mindestens erhalten bleiben sollen.
//STRIP001 void Kuerzen(Fraction& rF, unsigned nDigits);

class FrPair {
    Fraction aX;
    Fraction aY;
public:
    FrPair()                                          : aX(0,1),aY(0,1)             {}
    FrPair(const Fraction& rBoth)                     : aX(rBoth),aY(rBoth)         {}
    FrPair(const Fraction& rX, const Fraction& rY)    : aX(rX),aY(rY)               {}
    FrPair(long nMul, long nDiv)                      : aX(nMul,nDiv),aY(nMul,nDiv) {}
    FrPair(long xMul, long xDiv, long yMul, long yDiv): aX(xMul,xDiv),aY(yMul,yDiv) {}
    const Fraction& X() const { return aX; }
    const Fraction& Y() const { return aY; }
    Fraction& X()             { return aX; }
    Fraction& Y()             { return aY; }
};

// Fuer die Umrechnung von Masseinheiten
//STRIP001 FrPair GetMapFactor(MapUnit eS, MapUnit eD);
//STRIP001 FrPair GetMapFactor(MapUnit eS, FieldUnit eD);
//STRIP001 FrPair GetMapFactor(FieldUnit eS, MapUnit eD);
FrPair GetMapFactor(FieldUnit eS, FieldUnit eD);

inline FASTBOOL IsMetric(MapUnit eU) {
    return (eU==MAP_100TH_MM || eU==MAP_10TH_MM || eU==MAP_MM || eU==MAP_CM);
}

inline FASTBOOL IsInch(MapUnit eU) {
    return (eU==MAP_1000TH_INCH || eU==MAP_100TH_INCH || eU==MAP_10TH_INCH || eU==MAP_INCH ||
            eU==MAP_POINT       || eU==MAP_TWIP);
}

inline FASTBOOL IsMetric(FieldUnit eU) {
    return (eU==FUNIT_MM || eU==FUNIT_CM || eU==FUNIT_M || eU==FUNIT_KM || eU==FUNIT_100TH_MM);
}

inline FASTBOOL IsInch(FieldUnit eU) {
    return (eU==FUNIT_TWIP || eU==FUNIT_POINT || eU==FUNIT_PICA ||
            eU==FUNIT_INCH || eU==FUNIT_FOOT || eU==FUNIT_MILE);
}

class SdrFormatter {
    Fraction  aScale;
    long      nMul_;
    long      nDiv_;
    short     nKomma_;
    FASTBOOL  bSrcFU;
    FASTBOOL  bDstFU;
    FASTBOOL  bDirty;
    MapUnit   eSrcMU;
    MapUnit   eDstMU;
    FieldUnit eSrcFU;
    FieldUnit eDstFU;
private:
//STRIP001 	void Undirty();
//STRIP001 	void ForceUndirty() const { if (bDirty) ((SdrFormatter*)this)->Undirty(); }
public:
    SdrFormatter(MapUnit eSrc, MapUnit eDst)     { eSrcMU=eSrc; bSrcFU=FALSE; eDstMU=eDst; bDstFU=FALSE; bDirty=TRUE; }
    SdrFormatter(MapUnit eSrc, FieldUnit eDst)   { eSrcMU=eSrc; bSrcFU=FALSE; eDstFU=eDst; bDstFU=TRUE;  bDirty=TRUE; }
    SdrFormatter(FieldUnit eSrc, MapUnit eDst)   { eSrcFU=eSrc; bSrcFU=TRUE;  eDstMU=eDst; bDstFU=FALSE; bDirty=TRUE; }
    SdrFormatter(FieldUnit eSrc, FieldUnit eDst) { eSrcFU=eSrc; bSrcFU=TRUE;  eDstFU=eDst; bDstFU=TRUE;  bDirty=TRUE; }
    void SetSourceUnit(MapUnit eSrc)        { eSrcMU=eSrc; bSrcFU=FALSE; bDirty=TRUE; }
    void SetSourceUnit(FieldUnit eSrc)      { eSrcFU=eSrc; bSrcFU=TRUE;  bDirty=TRUE; }
    void SetDestinationUnit(MapUnit eDst)   { eDstMU=eDst; bDstFU=FALSE; bDirty=TRUE; }
    void SetDestinationUnit(FieldUnit eDst) { eDstFU=eDst; bDstFU=TRUE;  bDirty=TRUE; }
//STRIP001 	void TakeStr(long nVal, XubString& rStr) const;
//STRIP001 	static void TakeUnitStr(MapUnit eUnit, XubString& rStr);
//STRIP001 	static void TakeUnitStr(FieldUnit eUnit, XubString& rStr);
//STRIP001 	static XubString GetUnitStr(MapUnit eUnit)   { XubString aStr; TakeUnitStr(eUnit,aStr); return aStr; }
//STRIP001 	static XubString GetUnitStr(FieldUnit eUnit) { XubString aStr; TakeUnitStr(eUnit,aStr); return aStr; }
};

////////////////////////////////////////////////////////////////////////////////////////////////////

}//end of namespace binfilter
#endif //_SVDTRANS_HXX

