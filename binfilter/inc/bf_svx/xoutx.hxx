/*************************************************************************
 *
 *  $RCSfile: xoutx.hxx,v $
 *
 *  $Revision: 1.1.1.1 $
 *
 *  last change: $Author: hjs $ $Date: 2003-10-01 12:23:50 $
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

#ifndef _XOUTX_HXX
#define _XOUTX_HXX

#ifndef _SV_BITMAP_HXX
#include <vcl/bitmap.hxx>
#endif

#include <bf_svx/xhatch.hxx>
#include <bf_svx/xgrad.hxx>
#ifndef _XPOLY_HXX //autogen
#include <bf_svx/xpoly.hxx>
#endif
#ifndef _SVX_RECTENUM_HXX //autogen
#include <bf_svx/rectenum.hxx>
#endif
#ifndef _XENUM_HXX
#include <bf_svx/xenum.hxx>
#endif
#ifndef _OUTDEV_HXX //autogen
#include <vcl/outdev.hxx>
#endif
#ifndef _BITMAP_HXX //autogen
#include <vcl/bitmap.hxx>
#endif

class FormattedText;
class XPolygon;
class XPolyPolygon;
class XLineAttrSetItem;
class XFillAttrSetItem;
class XTextAttrSetItem;
class XLineAttrSetItem;
class XFillAttrSetItem;
class XOutdevItemPool;
class XLineParam;
struct ImpData;
class SfxItemSet;
class GraphicObject;

// #101498# predeclaration for DrawPortionInfo
class DrawPortionInfo;

#if _SOLAR__PRIVATE

// -----------
// - ImpData -
// -----------

struct ImpData
{
    XGradient*	    pTransGradient;
    BOOL		    bSolidHatch;
};

#define iRotTransGradient()	( ( (ImpData*)pImpData )->pTransGradient )
#define iSolidHatch()		( ( (ImpData*)pImpData )->bSolidHatch )

#endif // _PRIVATE

/*************************************************************************
|*
|* Extended OutputDevice
|*
\************************************************************************/

#if defined(MACOSX) && (__GNUC__ < 3)
static Brush aBrush;
static Pen aPen;
#endif

class XOutputDevice
{
private:

    ImpData*			pImpData;

    long*				pLinePattern;
    USHORT				nLinePatternCnt;

    XLineStyle			eLineStyle;
    Color				aLineColor;
    USHORT				nLineTransparence;
    long				nLineWidth;
    XPolygon			aLineStartPoly, aLineEndPoly;
    long				nLineStartSqLen, nLineEndSqLen;
    BOOL				bLineStart, bLineEnd;
    BOOL				bHair;

    XFillStyle			eFillStyle;
    Color				aFillColor;
    USHORT				nFillTransparence;

    Bitmap				maFillBitmap;
    GraphicObject*      mpFillGraphicObject;
    void*               mpDummy1;
    void*               mpDummy2;
    void*               mpDummy3;
    void*               mpDummy4;
    void*               mpDummy5;
    long                mnDummy;
    long                mnDummy2;
    long                mnDummy3;
    long                mnDummy4;
    long                mnDummy5;
    MapMode				maLastMapMode;
    Size				maFillBitmapSize;
    Size				maBmpSize;
    Size				maBmpOutputSize;
    long                mnDummy6;
    long                mnDummy7;
    Point				maStartPoint;
    USHORT				mnBmpPerCentX;
    USHORT				mnBmpPerCentY;
    USHORT				mnBmpOffX;
    USHORT				mnBmpOffY;
    USHORT				mnBmpOffPosX;
    USHORT				mnBmpOffPosY;
    OutDevType			meLastOutDevType;
    RECT_POINT			meBmpRectPoint;
    BOOL				mbBmpTile;
    BOOL				mbBmpStretch;
    BOOL				mbBmpLogSize;
    BOOL				mbDummy;
    BOOL				mbRecalc;

    XGradient			aGradient;
    XHatch				aHatch;
    BOOL				bDither;

    BOOL				bIgnoreLineAttr;
    BOOL				bIgnoreLineStyle;
    BOOL				bIgnoreFillAttr;

    XFormTextStyle      eFormTextStyle;
    XFormTextAdjust     eFormTextAdjust;
    long                nFormTextDistance;
    long                nFormTextStart;
    BOOL                bFormTextMirror;
    BOOL                bFormTextOutline;
    XFormTextShadow     eFormTextShadow;
    Color               aFormTextShdwColor;
    USHORT              nFormTextShdwTransp;
    long                nFormTextShdwXVal;
    long                nFormTextShdwYVal;
    XFormTextStdForm    eFormTextStdForm;
    BOOL                bFormTextHideForm;

    // Zwischenspeicher fuer FormText-Auto-Fonthoehe bei mehreren
    // zusammengehoerigen Aufrufen
    long				nFtAutoHeightSave;
    // umschliessendes Rechteck der Formtext-Effekte
    Rectangle			aFormTextBoundRect;

    void				ImpDrawFillPolyPolygon( const PolyPolygon& rPoly, BOOL bRect, BOOL bPrinter );
    void				ImpDrawLinePolygon(const Polygon& rPoly, BOOL bClosePoly);

protected:

    OutputDevice*		pOut;
    Point				aOfs;

//STRIP001 	void				CalcFatLineJoin(const Point& rEnd, const Point& rNext, XLineParam& rParam);
    void				DrawFillPolyPolygon( const PolyPolygon& rPoly, BOOL bRect = FALSE );
    void				DrawLinePolygon( const Polygon& rPoly, BOOL bClosePoly );
//STRIP001 	void				DrawStartEndPoly(const Point& rPos, const XPolygon& rXPoly, const XLineParam& rParam);
//STRIP001 	void				DrawLineStartEnd(const Polygon& rPoly);
//STRIP001 	void				DrawFatLine(const Point& rStart, const Point& rEnd, const Point* pNext, XLineParam& rParam);
//STRIP001 	void				DrawPatternLine(const Point& rStart, const Point& rEnd, XLineParam& rParam);

    // #101498# changed interface due to bidi requirements
    sal_Int32 ImpDrawFormText(DrawPortionInfo* pInfo, const Polygon& rPoly, sal_Int32 nAbsStart, 
        sal_Bool bToLastPoint, sal_Bool bDraw, sal_Bool bIsShadow);
    void ImpDrawFormTextShadow(DrawPortionInfo* pInfo, const Polygon& rPoly, sal_Int32 nAbsStart, 
        sal_Bool bToLastPoint, sal_Bool bDraw);
    //long				ImpDrawFormText(const String& rText, const Polygon& rPoly,
    //									Font aFont, long nAbsStart, BOOL bIsShadow,
    //									BOOL bToLastPoint, BOOL bDraw,
    //									const long* pDXArray = NULL);
    //void				DrawFormTextShadow(const String& rText, const Polygon& rPoly,
    //									   const Font& rFont, long nAbsStart,
    //									   BOOL bToLastPoint, BOOL bDraw,
    //									   const long* pDXArray = NULL);

//STRIP001 	void				ImpDrawBitmapFill( const Rectangle& rRect, BOOL bPrinter );
//STRIP001 	void				ImpCalcBmpFillStartValues( const Rectangle& rRect, BOOL bPrinter );
/*N*/ 	void				ImpDrawTiledBitmap( OutputDevice* pOut, const Rectangle& rRect,
/*N*/ 											const Point& rStartPoint, const Rectangle& rClipRect,
/*N*/                                             BOOL bPrinter );

 public:
                        XOutputDevice(OutputDevice* pOut);
                        ~XOutputDevice();

    OutputDevice*		GetOutDev() const { return pOut; }
    void				SetOutDev(OutputDevice* pNewOut) { pOut=pNewOut; }

    RasterOp			GetRasterOp() const { return pOut->GetRasterOp(); }
    void				SetRasterOp(RasterOp eRop) { pOut->SetRasterOp(eRop); }

    // Allgemeine Ausgabemethoden
    void				DrawLine( const Point& rStart, const Point& rEnd );
    void				DrawRect( const Rectangle& rRect, ULONG nXRound=0, ULONG nYRound=0 );
    void				DrawEllipse( const Rectangle& rRect );
    void				DrawArc( const Rectangle& rRect, const Point& rStart, const Point& rEnd );
    void				DrawPie( const Rectangle& rRect, const Point& rStart, const Point& rEnd );
    void				DrawPolyLine( const Polygon& rPoly );
    void				DrawPolygon( const Polygon& rPoly );
    void				DrawPolyPolygon( const PolyPolygon& rPolyPoly );
    void				DrawXPolyLine( const XPolygon& rXPoly );
    void				DrawXPolygon( const XPolygon& rXPoly );
    void				DrawXPolyPolygon( const XPolyPolygon& rXPoly );

    // Bitmap Ausgabemethoden
    void				DrawBitmap( const Point& rPos, const Size& rSize, const Bitmap& rBmp );
    void				DrawBitmap( const Point& rDestPos, const Size& rDestSize,
                                    const Point& rSrcPos,  const Size& rSrcSize );

    // Text Ausgabemethoden
    // Der formatierte Text kommt aus der EditEngine von MT
    void				DrawFormattedText( const Point& rPos, const FormattedText& rText );

    // #101498# changed interface due to bidi requirements
    sal_Int32 DrawFormText(DrawPortionInfo* pInfo, const Polygon& rPoly,
        sal_Int32 nAbsStart = 0L, sal_Bool bToLastPoint = sal_True, 
        sal_Bool bDraw = sal_True);

    // #101498# XPolygon version of DrawFormText not used, removed.
    // Difference was only to change XPolygon to Polygon using 
    // XOutCreatePolygon(...)
    //long				DrawFormText(const String& rText, const XPolygon& rXPoly,
    //								 Font aFont, long nAbsStart = 0,
    //								 BOOL bToLastPoint = TRUE, BOOL bDraw = TRUE,
    //								 const long* pDXArray = NULL);

    const Rectangle&	GetFormTextBoundRect() const { return aFormTextBoundRect; }

#ifndef NOOLDSV
    // Nur Temporaer
    const Pen&			GetPen() const { 
#if !(defined(MACOSX) && (__GNUC__ < 3))
                static Pen aPen; 
#endif
                aPen = pOut->GetPen(); return aPen; 
        }
    void				SetPen( const Pen& rPen ) { pOut->SetPen( rPen ); }

    const Brush&		GetBrush() const { 
#if !(defined(MACOSX) && (__GNUC__ < 3))
                static Brush aBrush; 
#endif
                aBrush = pOut->GetFillInBrush(); return aBrush; 
        }
    void				SetFillInBrush( const Brush& rBrush ) { pOut->SetFillInBrush( rBrush ); }

    // StarView-Pen und -FillInBrush temporaer ueberschreiben, z.B. fuer
    // dragging in SvDraw
    void				OverridePen(const Pen& rPen);
    void				OverrideFillInBrush(const Brush& rBrush);
#endif

    // Nur Temporaer
    const Color&		GetLineColor() const { return pOut->GetLineColor(); }
    void				SetLineColor( const Color& rColor ) { pOut->SetLineColor( rColor ); }

    const Color&		GetFillColor() const { return pOut->GetFillColor(); }
    void				SetFillColor( const Color& rColor ) { pOut->SetFillColor( rColor ); }

    // Attributeinstellungen
    void				SetLineAttr(const SfxItemSet& rAttr);
    void				SetFillAttr(const SfxItemSet& rAttr);
    void				SetTextAttr(const SfxItemSet& rAttr);

    // Attributeinstellungen ignorieren
    void				SetIgnoreLineAttr(BOOL bIgnore) { bIgnoreLineAttr = bIgnore; }
    BOOL				GetIgnoreLineAttr() { return bIgnoreLineAttr; }
    void				SetIgnoreLineStyle(BOOL bIgnore) { bIgnoreLineStyle = bIgnore; }
    BOOL				GetIgnoreLineStyle() { return bIgnoreLineStyle; }
    void				SetIgnoreFillAttr(BOOL bIgnore) { bIgnoreFillAttr = bIgnore; }
    BOOL				GetIgnoreFillAttr() { return bIgnoreFillAttr; }

    // StarView- Linecolor/style und Fillcolor/style temporaer ueberschreiben, z.B. fuer
    // dragging in SvDraw
    void				OverrideLineColor(const Color& rColor );
    void				OverrideFillColor(const Color& rColor );

    // Zum Abschalten der Linienenden
    BOOL				IsLineStart() const { return bLineStart; }
    void				OverrideLineStart(BOOL bOn) { bLineStart=bOn; }
    BOOL				IsLineEnd() const { return bLineEnd; }
    void				OverrideLineEnd(BOOL bOn) { bLineEnd=bOn; }

    // Allgemeine Einstellungen
    const Point&		GetOffset() const { return aOfs; }
    void				SetOffset( const Point& rOfs );

    MapMode				GetMapMode() const;
    void				SetMapMode( const MapMode& rMap );

    // Initialisierung der Linienenden statisch, damit auch ohne XOutDev
    // von SvDraw verwendbar
    static long			InitLineStartEnd(XPolygon& rXPoly, long nWidth, BOOL bCenter);
};

// Nur aus Kompatibilitaetsgruenden fuer SvDraw
class ExtOutputDevice : public XOutputDevice 
{
public:

        ExtOutputDevice(OutputDevice* pNewOut): XOutputDevice(pNewOut) {}
};

/*************************************************************************
|*
|* Funktionen zur Berechnung von Bezierkurven; muessen global sein,
|* da sie auch von XPolygon::GetBoundRect benoetigt werden
|*
\************************************************************************/

Rectangle		XOutCalcXPolyExtent(const XPolygon& rXPoly, OutputDevice* pOut);
long			XOutCalcBezierStepCount( const XPolygon& rXPoly, USHORT nIndex, OutputDevice* pOut, USHORT nRough = 0 );
void			XOutCalcBezier( const XPolygon& rXPoly, USHORT nBezIndex, Polygon& rPoly, USHORT nPolyIndex, long nSteps );
Polygon			XOutCreatePolygon( const XPolygon& rXPoly, OutputDevice* pOut, USHORT nRough = 0 );
Polygon			XOutCreatePolygonBezier( const XPolygon& rXPoly, OutputDevice* pOut );
//STRIP001 PolyPolygon		XOutCreatePolyPolygonBezier( const XPolyPolygon& rXPoly, OutputDevice* pOut );
// #102382# Remove XOutGetCharOutline
//XPolyPolygon	XOutGetCharOutline( USHORT nChar, OutputDevice& rOut, BOOL bOptimizeSize = TRUE );

#endif      // _XOUTX_HXX

