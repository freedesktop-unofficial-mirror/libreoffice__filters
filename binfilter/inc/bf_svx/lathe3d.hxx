/*************************************************************************
 *
 *  $RCSfile: lathe3d.hxx,v $
 *
 *  $Revision: 1.2 $
 *
 *  last change: $Author: mwu $ $Date: 2003-11-06 08:28:03 $
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

#ifndef _E3D_LATHE3D_HXX
#define _E3D_LATHE3D_HXX

#ifndef _E3D_OBJ3D_HXX
#include <bf_svx/obj3d.hxx>
#endif

#ifndef _E3D_POLY3D_HXX
#include <bf_svx/poly3d.hxx>
#endif
namespace binfilter {

/*************************************************************************
|*
|* 3D-Rotationsobjekt aus uebergebenem 2D-Polygon erzeugen
|*
|* Das aPolyPoly3D wird in nHSegments-Schritten um die Achse rotiert.
|* nVSegments gibt die Anzahl der Linien von aPolyPoly3D an und stellt damit
|* quasi eine vertikale Segmentierung dar.
|*
\************************************************************************/

class E3dLatheObj : public E3dCompoundObject
{
    // Partcodes fuer Wireframe-Generierung: Standard oder Deckelflaeche
    enum { LATHE_PART_STD = 1, LATHE_PART_COVER = 2 };
    PolyPolygon3D	aPolyPoly3D;
    double			fLatheScale;

    // #78972#
    PolyPolygon3D	maLinePolyPolygon;

    // #107245# unsigned		bLatheSmoothed				: 1;
    // #107245# unsigned		bLatheSmoothFrontBack		: 1;
    // #107245# unsigned		bLatheCharacterMode			: 1;
    // #107245# unsigned		bLatheCloseFront			: 1;
    // #107245# unsigned		bLatheCloseBack				: 1;

 protected:
    void SetDefaultAttributes(E3dDefaultAttributes& rDefault);

    PolyPolygon3D CreateLathePolyPoly(PolyPolygon3D& rPoly3D, long nVSegs);
    Polygon3D CreateLathePoly(Polygon3D& rPoly3D, long nVSegs);

 public:
    TYPEINFO();
    E3dLatheObj(E3dDefaultAttributes& rDefault, const PolyPolygon& rPoly);
    // es wird keine Bezier-Konvertierung des XPolygon durchgefuehrt,
    // sondern es werden nur die Punkte uebernommen!
    E3dLatheObj(E3dDefaultAttributes& rDefault, const XPolyPolygon& rXPoly);
    E3dLatheObj(E3dDefaultAttributes& rDefault, const XPolygon& rXPoly);
    E3dLatheObj(E3dDefaultAttributes& rDefault, const PolyPolygon3D rPoly3D);
    E3dLatheObj();

    // HorizontalSegments:
    sal_Int32 GetHorizontalSegments() const 
        { return ((const Svx3DHorizontalSegmentsItem&)GetUnmergedItemSet().Get(SDRATTR_3DOBJ_HORZ_SEGS)).GetValue(); }

    // VerticalSegments:
    sal_Int32 GetVerticalSegments() const 
        { return ((const Svx3DVerticalSegmentsItem&)GetUnmergedItemSet().Get(SDRATTR_3DOBJ_VERT_SEGS)).GetValue(); }

    // PercentDiagonal: 0..100, before 0.0..0.5
    sal_uInt16 GetPercentDiagonal() const 
        { return ((const Svx3DPercentDiagonalItem&)GetUnmergedItemSet().Get(SDRATTR_3DOBJ_PERCENT_DIAGONAL)).GetValue(); }

    // BackScale: 0..100, before 0.0..1.0
    sal_uInt16 GetBackScale() const 
        { return ((const Svx3DBackscaleItem&)GetUnmergedItemSet().Get(SDRATTR_3DOBJ_BACKSCALE)).GetValue(); }

    // EndAngle: 0..10000
    sal_uInt32 GetEndAngle() const 
        { return ((const Svx3DEndAngleItem&)GetUnmergedItemSet().Get(SDRATTR_3DOBJ_END_ANGLE)).GetValue(); }

    // #107245# GetSmoothNormals() for bLatheSmoothed
    sal_Bool GetSmoothNormals() const 
        { return ((const Svx3DSmoothNormalsItem&)GetUnmergedItemSet().Get(SDRATTR_3DOBJ_SMOOTH_NORMALS)).GetValue(); }

    // #107245# GetSmoothLids() for bLatheSmoothFrontBack
    sal_Bool GetSmoothLids() const 
        { return ((const Svx3DSmoothLidsItem&)GetUnmergedItemSet().Get(SDRATTR_3DOBJ_SMOOTH_LIDS)).GetValue(); }

    // #107245# GetCharacterMode() for bLatheCharacterMode
    sal_Bool GetCharacterMode() const 
        { return ((const Svx3DCharacterModeItem&)GetUnmergedItemSet().Get(SDRATTR_3DOBJ_CHARACTER_MODE)).GetValue(); }

    // #107245# GetCloseFront() for bLatheCloseFront
    sal_Bool GetCloseFront() const 
        { return ((const Svx3DCloseFrontItem&)GetUnmergedItemSet().Get(SDRATTR_3DOBJ_CLOSE_FRONT)).GetValue(); }

    // #107245# GetCloseBack() for bLatheCloseBack
    sal_Bool GetCloseBack() const 
        { return ((const Svx3DCloseBackItem&)GetUnmergedItemSet().Get(SDRATTR_3DOBJ_CLOSE_BACK)).GetValue(); }

    virtual UINT16 GetObjIdentifier() const;

    virtual void CreateWireframe(Polygon3D& rWirePoly, const Matrix4D* pTf = NULL,
        E3dDragDetail eDetail = E3DDETAIL_DEFAULT);

    const   PolyPolygon3D& GetPolyPolygon() const { return aPolyPoly3D; }
//STRIP001 	void    ReSegment(long nHSegs, long nVSegs);

//STRIP001 	virtual void operator=(const SdrObject&);
    virtual void WriteData(SvStream& rOut) const;
    virtual void ReadData(const SdrObjIOHeader& rHead, SvStream& rIn);

//STRIP001 	virtual SdrObject* DoConvertToPolyObj(BOOL bBezier) const;

    // Geometrieerzeugung
    virtual void CreateGeometry();

    // Give out simple line geometry
//STRIP001 	virtual void GetLineGeometry(PolyPolygon3D& rLinePolyPolygon) const;

    // TakeObjName...() ist fuer die Anzeige in der UI, z.B. "3 Rahmen selektiert".
//STRIP001 	virtual void TakeObjNameSingul(String& rName) const;
//STRIP001 	virtual void TakeObjNamePlural(String& rName) const;

    // Lokale Parameter setzen/lesen mit Geometrieneuerzeugung
    void SetPolyPoly3D(const PolyPolygon3D& rNew);
    const PolyPolygon3D& GetPolyPoly3D() { return aPolyPoly3D; }

//STRIP001 	void SetLatheScale(double fNew);
    double GetLatheScale() const { return fLatheScale; }

    // #107245# 
    // void SetLatheSmoothed(BOOL bNew);
    // BOOL GetLatheSmoothed() const { return bLatheSmoothed; }
    // void SetLatheSmoothFrontBack(BOOL bNew);
    // BOOL GetLatheSmoothFrontBack() const { return bLatheSmoothFrontBack; }
    // void SetLatheCharacterMode(BOOL bNew);
    // BOOL GetLatheCharacterMode() const { return bLatheCharacterMode; }
    // void SetLatheCloseFront(BOOL bNew);
    // BOOL GetLatheCloseFront() const { return bLatheCloseFront; }
    // void SetLatheCloseBack(BOOL bNew);
    // BOOL GetLatheCloseBack() const { return bLatheCloseBack; }

    // private support routines for ItemSet access. NULL pointer means clear item.
    virtual void PostItemChange(const sal_uInt16 nWhich);

    // Aufbrechen
//STRIP001 	virtual BOOL IsBreakObjPossible();
//STRIP001 	virtual SdrAttrObj* GetBreakObj();
};

}//end of namespace binfilter
#endif			// _E3D_LATHE3D_HXX

