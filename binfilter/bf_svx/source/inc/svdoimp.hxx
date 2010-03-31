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

#ifndef _SVX_SVDOIMP_HXX
#define _SVX_SVDOIMP_HXX

#include <memory>
#include <vector>

#ifndef _CPPUHELPER_WEAKREF_HXX_
#include <cppuhelper/weakref.hxx>
#endif

#ifndef _MAPMOD_HXX //autogen
#include <vcl/mapmod.hxx>
#endif

#ifndef _SFXLSTNER_HXX //autogen
#include <bf_svtools/lstner.hxx>
#endif

#ifndef _SV_TIMER_HXX
#include <vcl/timer.hxx>
#endif

#ifndef _SVDSOB_HXX //autogen
#include "svdsob.hxx"
#endif

#ifndef _SVDTYPES_HXX
#include "svdtypes.hxx" // fuer SdrLayerID
#endif

#ifndef _SVDGLUE_HXX
#include "svdglue.hxx" // Klebepunkte
#endif

#ifndef _SVX_XDASH_HXX
#include "xdash.hxx"
#endif

#ifndef _XPOLY_HXX
#include "xpoly.hxx"
#endif

#ifndef _POLY3D_HXX
#include "poly3d.hxx"
#endif

#ifndef _XENUM_HXX
#include "xenum.hxx"
#endif
class PolyPolygon;
namespace binfilter {

class SfxItemSet;
class SdrObject;
class ExtOutputDevice;
class XFillAttrSetItem;
class XLineAttrSetItem;
class XPolyPolygon;
class XPolygon;

///////////////////////////////////////////////////////////////////////////////

// #100127# Bracket filled shapes with a comment, if recording a Mtf
class ImpGraphicFill 
{
public:
    ImpGraphicFill( const SdrObject& rObj, const ExtOutputDevice& rXOut, const SfxItemSet& rFillItemSet, bool bIsShadow=false );
    ~ImpGraphicFill();

private:
    const SdrObject&		mrObj;
    const ExtOutputDevice&	mrXOut;
    bool					mbCommentWritten;
};

///////////////////////////////////////////////////////////////////////////////

// #104609# Extracted from XOutputDevice::ImpCalcBmpFillStartValues

/** Calc offset and size for bitmap fill

    This method calculates the size and the offset from the left, top
    position of a shape in logical coordinates

    @param rStartOffset
    The offset from the left, top position of the output rectangle is returned

    @param rBmpOutputSize
    The output size of the bitmap is returned herein

    @param rOutputRect
    Specifies the output rectangle into which the bitmap should be tiled into

    @param rOutputMapMode
    Specifies the logical coordinate system the output rectangle is in

    @param rFillBitmap
    Specifies the bitmap to fill with

    @param rBmpSize
    The desired destination bitmap size. If null, size is taken from the bitmap

    @param rBmpPerCent
    Percentage of bitmap size, relative to the output rectangle

    @param rBmpOffPerCent
    Offset for bitmap tiling, in percentage relative to bitmap output size

    @param bBmpLogSize
    True when using the preferred bitmap size, False when using the percentage value

    @param bBmpTile
    True for tiling. False only paints one instance of the bitmap

    @param bBmpStretch
    True if bitmap should be stretched to output rect dimension

    @param eBmpRectPoint
    Position of the start point relative to the bitmap
    
 */
void ImpCalcBmpFillSizes( Size&			   rStartOffset,
                          Size&			   rBmpOutputSize,
                          const Rectangle& rOutputRect, 
                          const MapMode&   rOutputMapMode,
                          const Bitmap&    rFillBitmap,
                          const Size&      rBmpSize, 
                          const Size&      rBmpPerCent, 
                          const Size&	   rBmpOffPerCent,
                          BOOL             bBmpLogSize, 
                          BOOL             bBmpTile, 
                          BOOL             bBmpStretch, 
                          RECT_POINT       eBmpRectPoint );


///////////////////////////////////////////////////////////////////////////////

class ImpLineStyleParameterPack
{
    OutputDevice*				mpOut;
    XDash						aDash;

    XLineJoint					eLineJoint;
    XLineStyle					eLineStyle;

    const XPolygon&				rStartPolygon;
    const XPolygon&				rEndPolygon;

    INT32						nLineWidth;
    INT32						nStartWidth;
    INT32						nEndWidth;

    ::std::vector<double>		aDotDashArray;
    double						fFullDashDotLen;
    double						fDegreeStepWidth;

    BOOL						bStartCentered;
    BOOL						bEndCentered;
    BOOL						bForceNoArrowsLeft;
    BOOL						bForceNoArrowsRight;
    BOOL						bForceHair;

public:
    ImpLineStyleParameterPack(const SfxItemSet& rSet,
        BOOL bForceHair, OutputDevice* pOut);
    ~ImpLineStyleParameterPack();

    OutputDevice* GetOutDev() const { return mpOut; }
    INT32 GetLineWidth() const { return nLineWidth; }
    INT32 GetDisplayLineWidth() const { return bForceHair ? 0 : nLineWidth; }
    XLineStyle GetLineStyle() const { return eLineStyle; }

    INT32 GetStartWidth() const { return nStartWidth; }
    INT32 GetDisplayStartWidth() const { return bForceHair ? 0 : nStartWidth; }
    INT32 GetEndWidth() const { return nEndWidth; }
    INT32 GetDisplayEndWidth() const { return bForceHair ? 0 : nEndWidth; }

    const XPolygon& GetStartPolygon() const { return rStartPolygon; }
    const XPolygon& GetEndPolygon() const { return rEndPolygon; }

    double GetDegreeStepWidth() const { return fDegreeStepWidth; }

    XLineJoint GetLineJoint() const { return eLineJoint; }
    double GetLinejointMiterUpperBound() const { return 3.0; }

    XDashStyle GetDashStyle() const { return aDash.GetDashStyle(); }
    UINT16 GetDots() const { return aDash.GetDots(); }
    UINT32 GetDotLen() const { return aDash.GetDotLen(); }
    UINT16 GetDashes() const { return aDash.GetDashes(); }
    UINT32 GetDashLen() const { return aDash.GetDashLen(); }
    UINT32 GetDashDistance() const { return aDash.GetDistance(); }
    double GetFullDashDotLen() const { return fFullDashDotLen; }
    UINT16 GetFirstDashDotIndex(double fPos, double& rfDist) const;
    UINT16 GetNextDashDotIndex(UINT16 nInd, double& rfDist) const;
    ::std::vector< double > GetDotDash() const { return ::std::vector< double >(aDotDashArray); }

    BOOL IsStartCentered() const { return bStartCentered; }
    BOOL IsEndCentered() const { return bEndCentered; }

    BOOL IsStartActive() const { return (!bForceNoArrowsLeft && GetStartPolygon().GetPointCount() && GetStartWidth()); }
    BOOL IsEndActive() const { return (!bForceNoArrowsRight && GetEndPolygon().GetPointCount() && GetEndWidth()); }

    void ForceNoArrowsLeft(BOOL bNew) { bForceNoArrowsLeft = bNew; }
    void ForceNoArrowsRight(BOOL bNew) { bForceNoArrowsRight = bNew; }
};

////////////////////////////////////////////////////////////////////////////////////////////////////

class ImpLineGeometryCreator
{
    const ImpLineStyleParameterPack&	mrLineAttr;
    PolyPolygon3D&						mrPolyPoly3D;
    PolyPolygon3D&						mrPolyLine3D;
    BOOL								mbLineDraft;

    // private support functions
    // help functions for line geometry creation
    void ImpCreateLineGeometry(const Polygon3D& rSourcePoly);
    double ImpCreateLineStartEnd(Polygon3D& rArrowPoly, const Polygon3D& rSourcePoly, BOOL bFront, double fWantedWidth, BOOL bCentered);
    void ImpCreateSegmentsForLine(const Vector3D* pPrev, const Vector3D* pLeft, const Vector3D* pRight, const Vector3D* pNext, double fPolyPos);
    void ImpCreateLineSegment(const Vector3D* pPrev, const Vector3D* pLeft, const Vector3D* pRight, const Vector3D* pNext);
    double ImpSimpleFindCutPoint(const Vector3D& rEdge1Start, const Vector3D& rEdge1Delta, const Vector3D& rEdge2Start, const Vector3D& rEdge2Delta);

public:
    ImpLineGeometryCreator(const ImpLineStyleParameterPack& rAttr, PolyPolygon3D& rPoPo,
        PolyPolygon3D& rPoLi, BOOL bIsLineDraft = FALSE)
    :	mrLineAttr(rAttr),
        mrPolyPoly3D(rPoPo),
        mrPolyLine3D(rPoLi),
        mbLineDraft(bIsLineDraft)
    {
    }

    void AddPolygon3D(const Polygon3D& rPoly) { ImpCreateLineGeometry(rPoly); }
    const PolyPolygon3D& GetPolyPolygon3D() const { return mrPolyPoly3D; }
    const PolyPolygon3D& GetPolyLines3D() const { return mrPolyLine3D; }
    void Clear() { mrPolyPoly3D.Clear(); mrPolyLine3D.Clear(); }
};

////////////////////////////////////////////////////////////////////////////////////////////////////

class SdrLineGeometry
{
    PolyPolygon3D				maPolyPoly3D;
    PolyPolygon3D				maLinePoly3D;
    ImpLineStyleParameterPack	maLineAttr;
    BOOL						mbForceOnePixel;
    BOOL						mbForceTwoPixel;

public:
    SdrLineGeometry(const PolyPolygon3D& rPolyPoly, const PolyPolygon3D& rLinePoly,
                    const ImpLineStyleParameterPack& rLineAttr,
                    BOOL bForceOnePixel, BOOL bForceTwoPixel)
    :	maPolyPoly3D(rPolyPoly),
        maLinePoly3D(rLinePoly),
        maLineAttr(rLineAttr),
        mbForceOnePixel(bForceOnePixel),
        mbForceTwoPixel(bForceTwoPixel)
    {}

    PolyPolygon3D& GetPolyPoly3D() { return maPolyPoly3D; }
    PolyPolygon3D& GetLinePoly3D() { return maLinePoly3D; }
    ImpLineStyleParameterPack& GetLineAttr() { return maLineAttr; }
    BOOL DoForceOnePixel() const { return mbForceOnePixel; }
    BOOL DoForceTwoPixel() const { return mbForceTwoPixel; }
};

}//end of namespace binfilter
#endif // _SVX_SVDOIMP_HXX
