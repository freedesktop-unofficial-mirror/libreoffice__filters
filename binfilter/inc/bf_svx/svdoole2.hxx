/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: svdoole2.hxx,v $
 *
 *  $Revision: 1.8 $
 *
 *  last change: $Author: rt $ $Date: 2008-03-12 13:11:18 $
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

#ifndef _SVDOOLE2_HXX
#define _SVDOOLE2_HXX

#ifndef _COM_SUN_STAR_FRAME_XMODEL_HPP_
#include <com/sun/star/frame/XModel.hpp>
#endif

#ifndef _SVDORECT_HXX
#include <bf_svx/svdorect.hxx>
#endif
#ifndef _GRAPH_HXX //autogen
#include <vcl/graph.hxx>
#endif
#ifndef _GDIMTF_HXX //autogen
#include <vcl/gdimtf.hxx>
#endif

#include <bf_so3/svstor.hxx>

namespace binfilter {

class SvPersist;
class SvInPlaceObjectRef;
class SvEmbeddedInfoObject;

//************************************************************
//   SdrOle2Obj
//************************************************************

class SvxUnoShapeModifyListener;

class SdrOle2ObjImpl;

class SdrOle2Obj :  public SdrRectObj
{
protected:
    SvInPlaceObjectRef*			ppObjRef;    // Referenz auf Objekt

    String						aName;       // Name des Objektes

    Graphic*					pGraphic;
    String						aProgName;

    // wg. Kompatibilitaet erstmal am SdrTextObj
    BOOL						bFrame : 1;
    BOOL						bInDestruction : 1;

    SdrOle2ObjImpl*				mpImpl;

    SvxUnoShapeModifyListener*	pModifyListener;

protected:

/*NBFF*/	void ImpSetVisAreaSize();

    void Init();

public:
    TYPEINFO();

    SdrOle2Obj(FASTBOOL bFrame_=FALSE);
    SdrOle2Obj(const SvInPlaceObjectRef& rNewObjRef, const String& rNewObjName, FASTBOOL bFrame_=FALSE);
    SdrOle2Obj(const SvInPlaceObjectRef& rNewObjRef, const String& rNewObjName, const Rectangle& rNewRect, FASTBOOL bFrame_=FALSE);
    virtual ~SdrOle2Obj();

    // Ein OLE-Zeichenobjekt kann eine StarView-Grafik beinhalten.
    // Diese wird angezeigt, wenn das OLE-Objekt leer ist.
    void        SetGraphic(const Graphic* pGrf);
    Graphic*    GetGraphic() const { return pGraphic; }

    // OLE object has got a separate PersistName member now;
    // !!! use ::SetPersistName( ... ) only, if you know what you do !!!
    String      GetPersistName() const;
    void        SetPersistName( const String& rPersistName );


    virtual String  GetName() const;

    // Einem SdrOle2Obj kann man ein Applikationsnamen verpassen, den man
    // spaeter wieder abfragen kann (SD braucht das fuer Praesentationsobjekte).
    void SetProgName(const String& rNam) { aProgName=rNam; }
    const String& GetProgName() const { return aProgName; }
    FASTBOOL IsEmpty() const;
    void SetObjRef(const SvInPlaceObjectRef& rNewObjRef);
    const SvInPlaceObjectRef& GetObjRef() const;

    virtual void SetPage(SdrPage* pNewPage);
    virtual void SetModel(SdrModel* pModel);

    /** Change the IsClosedObj attribute

        @param bIsClosed
        Whether the OLE object is closed, i.e. has opaque background
     */
    void SetClosedObj( bool bIsClosed );

    virtual UINT16 GetObjIdentifier() const;
    virtual SdrObject* CheckHit(const Point& rPnt, USHORT nTol, const SetOfByte* pVisiLayer) const;




    virtual void NbcMove(const Size& rSize);
    virtual void NbcResize(const Point& rRef, const Fraction& xFact, const Fraction& yFact);
    virtual void NbcSetSnapRect(const Rectangle& rRect);
    virtual void NbcSetLogicRect(const Rectangle& rRect);

    // fuer Import:
    FASTBOOL HasGDIMetaFile() const;
    const GDIMetaFile* GetGDIMetaFile() const;

    virtual void WriteData(SvStream& rOut) const;
    virtual void ReadData(const SdrObjIOHeader& rHead, SvStream& rIn);

    BOOL Unload();

    void Connect();
    void Disconnect();

    ::com::sun::star::uno::Reference< ::com::sun::star::frame::XModel > getXModel() const;

    /// #110015# sets the visible area at the SvInPlaceObject and SvEmbeddedInfoObject
    void SetVisibleArea( const Rectangle& rArea );
};

}//end of namespace binfilter
#endif //_SVDOOLE2_HXX

