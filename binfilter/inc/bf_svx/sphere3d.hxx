/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: sphere3d.hxx,v $
 *
 *  $Revision: 1.3 $
 *
 *  last change: $Author: rt $ $Date: 2005-09-09 14:29:08 $
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

#ifndef _E3D_SPHERE3D_HXX
#define _E3D_SPHERE3D_HXX

#ifndef _E3D_OBJ3D_HXX
#include <bf_svx/obj3d.hxx>
#endif
namespace binfilter {

/*************************************************************************
|*
|* Kugelobjekt mit Durchmesser r3DSize; Anzahl der Flaechen wird durch
|* die horizontale und vertikale Segmentanzahl vorgegeben
|*
\************************************************************************/

class E3dSphereObj : public E3dCompoundObject
{
    Vector3D		aCenter;
    Vector3D		aSize;

protected:
    void SetDefaultAttributes(E3dDefaultAttributes& rDefault);

public:
    TYPEINFO();
    E3dSphereObj(E3dDefaultAttributes& rDefault, const Vector3D& rCenter, const Vector3D& r3DSize);
    E3dSphereObj();

    // HorizontalSegments:
    sal_Int32 GetHorizontalSegments() const 
        { return ((const Svx3DHorizontalSegmentsItem&)GetUnmergedItemSet().Get(SDRATTR_3DOBJ_HORZ_SEGS)).GetValue(); }

    // VerticalSegments:
    sal_Int32 GetVerticalSegments() const 
        { return ((const Svx3DVerticalSegmentsItem&)GetUnmergedItemSet().Get(SDRATTR_3DOBJ_VERT_SEGS)).GetValue(); }

//STRIP001 	virtual UINT16 GetObjIdentifier() const;
//STRIP001 	virtual void CreateWireframe(Polygon3D& rWirePoly, const Matrix4D* pTf = NULL,
//STRIP001 		E3dDragDetail eDetail = E3DDETAIL_DEFAULT);

    virtual SdrObject* DoConvertToPolyObj(BOOL bBezier) const;

//STRIP001 	virtual void operator=(const SdrObject&);
    virtual void WriteData(SvStream& rOut) const;
    virtual void ReadData(const SdrObjIOHeader& rHead, SvStream& rIn);

    void ReSegment(long nHorzSegments, long nVertSegments);
    const Vector3D Center() const { return aCenter; }
    const Vector3D Size() const { return aSize; }

    // FG: Dieser Konstruktor wird nur von MakeObject aus der 3d-Objectfactory beim
    //     Laden von Dokumenten mit Kugeln aufgerufen. Dieser Konstruktor ruft kein
    //     CreateSphere auf, er erzeugt also keine Kugel.
    E3dSphereObj(int dummy);

    // FG: Liest die Kugel im Format der Version 31 ein. Diese Funktion wurde aus
    //     Gruenden der Uebersichtlichkeit ausgelagert.
    void ReadData31(const SdrObjIOHeader& rHead, SvStream& rIn);

    // Geometrieerzeugung
    virtual void CreateGeometry();

    // Give out simple line geometry
    virtual void GetLineGeometry(PolyPolygon3D& rLinePolyPolygon) const;

    // Lokale Parameter setzen mit Geometrieneuerzeugung
    void SetCenter(const Vector3D& rNew);
    void SetSize(const Vector3D& rNew);

    // private support routines for ItemSet access. NULL pointer means clear item.
    virtual void PostItemChange(const sal_uInt16 nWhich);

    // TakeObjName...() ist fuer die Anzeige in der UI, z.B. "3 Rahmen selektiert".
//STRIP001 	virtual void TakeObjNameSingul(String& rName) const;
//STRIP001 	virtual void TakeObjNamePlural(String& rName) const;
};

}//end of namespace binfilter
#endif			// _E3D_SPHERE3D_HXX
