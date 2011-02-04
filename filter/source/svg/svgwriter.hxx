/*************************************************************************
 *
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER.
 * 
 * Copyright 2008 by Sun Microsystems, Inc.
 *
 * OpenOffice.org - a multi-platform office productivity suite
 *
 * $RCSfile: svgwriter.hxx,v $
 * $Revision: 1.5.86.14 $
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

#ifndef SVGWRITER_HXX
#define SVGWRITER_HXX

#include <cppuhelper/weak.hxx>
#include <rtl/ustring.hxx>
#include <tools/debug.hxx>
#include <tools/stream.hxx>
#include <tools/string.hxx>
#include <tools/urlobj.hxx>
#include <tools/stack.hxx>
#ifndef _SALBTYPE_HXX
#include <vcl/salbtype.hxx>
#endif
#ifndef _GDIMTF_HXX
#include <vcl/gdimtf.hxx>
#endif
#ifndef _METAACT_HXX
#include <vcl/metaact.hxx>
#endif
#ifndef _METAACT_HXX
#include <vcl/metric.hxx>
#endif
#ifndef _VIRDEV_HXX
#include <vcl/virdev.hxx>
#endif
#ifndef _CVTGRF_HXX
#include <vcl/cvtgrf.hxx>
#endif
#include <vcl/graphictools.hxx>
#include <vcl/rendergraphicrasterizer.hxx>
#include <xmloff/xmlexp.hxx>
#include <xmloff/nmspmap.hxx>

#include <com/sun/star/uno/Reference.h>
#include <com/sun/star/uno/RuntimeException.hpp>
#include <com/sun/star/lang/XMultiServiceFactory.hpp>
#include <com/sun/star/lang/XComponent.hpp>
#include <com/sun/star/registry/XRegistryKey.hpp>
#include <com/sun/star/lang/XComponent.hpp>
#include <com/sun/star/io/XInputStream.hpp>
#include <com/sun/star/io/XOutputStream.hpp>
#include <com/sun/star/xml/sax/XDocumentHandler.hpp>
#include <com/sun/star/xml/sax/XExtendedDocumentHandler.hpp>
#include <com/sun/star/i18n/CharacterIteratorMode.hpp>
#include <com/sun/star/i18n/XBreakIterator.hpp>

// -----------------------------------------------------------------------------

#undef _SVG_WRITE_EXTENTS
#undef _SVG_WRITE_TEXT_DESC
#undef _SVG_USE_CONFIG

// -----------------------------------------------------------------------------

#define NMSP_CPPU				cppu
#define NMSP_UNO				com::sun::star::uno
#define NMSP_LANG				com::sun::star::lang
#define NMSP_SAX				com::sun::star::xml::sax
#define NMSP_SVG				com::sun::star::svg
#define NMSP_REGISTRY			com::sun::star::registry


#define REF( _def_Obj )			NMSP_UNO::Reference< _def_Obj >
#define SEQ( _def_Obj )			NMSP_UNO::Sequence< _def_Obj > 
#define B2UCONST( _def_pChar )	(::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM(_def_pChar )))
#define SVG_DTD_STRING			B2UCONST( "<!DOCTYPE svg PUBLIC \"-//W3C//DTD SVG 1.1//EN\" \"http://www.w3.org/Graphics/SVG/1.1/DTD/svg11.dtd\">" )
#define SVG_TINY_DTD_STRING     B2UCONST( "<!DOCTYPE svg PUBLIC \"-//W3C//DTD SVG Tiny 1.1//EN\" \"http://www.w3.org/Graphics/SVG/1.1/DTD/svg11-tiny.dtd\">" )

#define SVGWRITER_WRITE_NONE	    0x00000000
#define SVGWRITER_WRITE_FILL        0x00000001
#define SVGWRITER_WRITE_TEXT	    0x00000002
#define SVGWRITER_NO_SHAPE_COMMENTS 0x01000000

// ----------------------
// - SVGAttributeWriter -
// ----------------------

class SVGActionWriter;
class SVGExport;
class SVGFontExport;

class SVGAttributeWriter
{
private:

    Font					maCurFont;
    Color					maCurLineColor;
    Color					maCurFillColor;
    SVGExport&			    mrExport;
    SVGFontExport&          mrFontExport;
    SvXMLElementExport*		mpElemFont;
    SvXMLElementExport*		mpElemPaint;
                            
                            SVGAttributeWriter();
                     
    void                    ImplGetColorStr( const Color& rColor, ::rtl::OUString& rColorStr );
    double                  ImplRound( double fVal, sal_Int32 nDecs = 3 );
                   
public:

                            SVGAttributeWriter( SVGExport& rExport, SVGFontExport& rFontExport );
    virtual					~SVGAttributeWriter();

    void                    AddColorAttr( const char* pColorAttrName, const char* pColorOpacityAttrName, const Color& rColor );
    void                    AddGradientDef( const Rectangle& rObjRect,const Gradient& rGradient, ::rtl::OUString& rGradientId );
    void                    AddPaintAttr( const Color& rLineColor, const Color& rFillColor, 
                                          const Rectangle* pObjBoundRect = NULL, const Gradient* pFillGradient = NULL );
    
    void                    SetFontAttr( const Font& rFont );
};

// ----------------------
// - SVGShapeDescriptor -
// ----------------------

struct SVGShapeDescriptor
{
    PolyPolygon                 maShapePolyPoly;
    Color                       maShapeFillColor;
    Color                       maShapeLineColor;
    sal_Int32                   mnStrokeWidth;
    SvtGraphicStroke::DashArray maDashArray;
    ::std::auto_ptr< Gradient > mapShapeGradient;
    ::rtl::OUString             maId;

    // -------------------------------------------------------------------------

    SVGShapeDescriptor() :
        maShapeFillColor( Color( COL_TRANSPARENT ) ),
        maShapeLineColor( Color( COL_TRANSPARENT ) ),
        mnStrokeWidth( 0 )
    {
    }
};

// -------------------
// - SVGActionWriter -
// -------------------

class SVGAttributeWriter;
class SvXMLExport;
class GDIMetaFile;

class SVGActionWriter
{
private:

    Stack					                maContextStack;
    ::std::auto_ptr< SVGShapeDescriptor >   mapCurShape;
    SVGExport&			                    mrExport;
    SVGFontExport&                          mrFontExport;
    SVGAttributeWriter*                     mpContext;
    VirtualDevice*			                mpVDev;
    MapMode					                maTargetMapMode;
    sal_uInt32                              mnInnerMtfCount;
    sal_Bool				                mbDestroyVDev;
    sal_Bool				                mbPaintAttrChanged;
    sal_Bool				                mbFontAttrChanged;
    sal_Bool				                mbClipAttrChanged;

    SVGAttributeWriter*		ImplAcquireContext() { maContextStack.Push( mpContext = new SVGAttributeWriter( mrExport, mrFontExport ) ); return mpContext; }
    void					ImplReleaseContext() { delete (SVGAttributeWriter*)	maContextStack.Pop(); mpContext = (SVGAttributeWriter*) maContextStack.Top(); }

    long					ImplMap( sal_Int32 nVal ) const; 
    Point&					ImplMap( const Point& rPt, Point& rDstPt ) const;
    Size&					ImplMap( const Size& rSz, Size& rDstSz ) const;
    Rectangle&              ImplMap( const Rectangle& rRect, Rectangle& rDstRect ) const;
    Polygon&                ImplMap( const Polygon& rPoly, Polygon& rDstPoly ) const;
    PolyPolygon&            ImplMap( const PolyPolygon& rPolyPoly, PolyPolygon& rDstPolyPoly ) const;

    void					ImplWriteLine( const Point& rPt1, const Point& rPt2, const Color* pLineColor = NULL, 
                                           bool bApplyMapping = true );
    void					ImplWriteRect( const Rectangle& rRect, long nRadX = 0, long nRadY = 0, 
                                           bool bApplyMapping = true );
    void					ImplWriteEllipse( const Point& rCenter, long nRadX, long nRadY, 
                                              bool bApplyMapping = true );
    void					ImplWritePolyPolygon( const PolyPolygon& rPolyPoly, sal_Bool bLineOnly, 
                                                  bool bApplyMapping = true );
    void                    ImplWriteShape( const SVGShapeDescriptor& rShape, bool bApplyMapping = true );
    void					ImplWriteGradientEx( const PolyPolygon& rPolyPoly, const Gradient& rGradient, sal_uInt32 nWriteFlags, 
                                                 bool bApplyMapping = true );
    void					ImplWriteText( const Point& rPos, const String& rText, const sal_Int32* pDXArray, long nWidth, 
                                           bool bApplyMapping = true );
    void					ImplWriteBmp( const BitmapEx& rBmpEx, const Point& rPt, const Size& rSz, const Point& rSrcPt, const Size& rSrcSz, 
                                          bool bApplyMapping = true );

    void					ImplCheckFontAttributes();
    void					ImplCheckPaintAttributes();
    
    void					ImplWriteActions( const GDIMetaFile& rMtf, sal_uInt32 nWriteFlags, const ::rtl::OUString* pElementId );

public:

    static ::rtl::OUString	GetPathString( const PolyPolygon& rPolyPoly, sal_Bool bLine );

public:

                            SVGActionWriter( SVGExport& rExport, SVGFontExport& rFontExport );
    virtual					~SVGActionWriter();

    void					WriteMetaFile( const Point& rPos100thmm, 
                                           const Size& rSize100thmm,
                                           const GDIMetaFile& rMtf, 
                                           sal_uInt32 nWriteFlags,
                                           const ::rtl::OUString* pElementId = NULL );
};

#endif
