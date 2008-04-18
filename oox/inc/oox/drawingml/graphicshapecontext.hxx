/*************************************************************************
 *
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER.
 * 
 * Copyright 2008 by Sun Microsystems, Inc.
 *
 * OpenOffice.org - a multi-platform office productivity suite
 *
 * $RCSfile: graphicshapecontext.hxx,v $
 * $Revision: 1.5 $
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

#ifndef OOX_DRAWINGML_GRAPHICSHAPECONTEXT_HXX
#define OOX_DRAWINGML_GRAPHICSHAPECONTEXT_HXX

#include "oox/drawingml/shape.hxx"
#include "oox/drawingml/shapecontext.hxx"
#include "oox/drawingml/diagram/diagram.hxx"

namespace oox { namespace drawingml {

class GraphicShapeContext : public ShapeContext
{
public:
    GraphicShapeContext( ::oox::core::ContextHandler& rParent, ShapePtr pMasterShapePtr, ShapePtr pShapePtr );

    virtual ::com::sun::star::uno::Reference< ::com::sun::star::xml::sax::XFastContextHandler > SAL_CALL createFastChildContext( ::sal_Int32 Element, const ::com::sun::star::uno::Reference< ::com::sun::star::xml::sax::XFastAttributeList >& Attribs ) throw (::com::sun::star::xml::sax::SAXException, ::com::sun::star::uno::RuntimeException);

};

// ====================================================================

class GraphicalObjectFrameContext : public ShapeContext
{
public:
    GraphicalObjectFrameContext( ::oox::core::ContextHandler& rParent, ShapePtr pMasterShapePtr, ShapePtr pShapePtr );

    virtual ::com::sun::star::uno::Reference< ::com::sun::star::xml::sax::XFastContextHandler > SAL_CALL createFastChildContext( ::sal_Int32 Element, const ::com::sun::star::uno::Reference< ::com::sun::star::xml::sax::XFastAttributeList >& Attribs ) throw (::com::sun::star::xml::sax::SAXException, ::com::sun::star::uno::RuntimeException);

};

// ====================================================================

class PresentationOle2006Context : public ShapeContext
{
public:
    PresentationOle2006Context( ::oox::core::ContextHandler& rParent, ShapePtr pShapePtr );
    ~PresentationOle2006Context();
    virtual ::com::sun::star::uno::Reference< ::com::sun::star::xml::sax::XFastContextHandler > SAL_CALL createFastChildContext( ::sal_Int32 Element, const ::com::sun::star::uno::Reference< ::com::sun::star::xml::sax::XFastAttributeList >& Attribs ) throw (::com::sun::star::xml::sax::SAXException, ::com::sun::star::uno::RuntimeException);

private:
    ::rtl::OUString msSpid;
    ::rtl::OUString msName;
    ::rtl::OUString msId;
    sal_Int32		mnWidth;
    sal_Int32		mnHeight;
    ::rtl::OUString msProgId;
    sal_Int32		mnFollowColorSchemeToken;
};

// ====================================================================

class DiagramGraphicDataContext
    : public ShapeContext
{
public:
    DiagramGraphicDataContext( ::oox::core::ContextHandler& rParent, ShapePtr pShapePtr );
    virtual ~DiagramGraphicDataContext();
    virtual ::com::sun::star::uno::Reference< ::com::sun::star::xml::sax::XFastContextHandler > SAL_CALL createFastChildContext( ::sal_Int32 Element, const ::com::sun::star::uno::Reference< ::com::sun::star::xml::sax::XFastAttributeList >& Attribs ) throw (::com::sun::star::xml::sax::SAXException, ::com::sun::star::uno::RuntimeException);

private:
    DiagramPtr loadDiagram();

    ::rtl::OUString msDm;
    ::rtl::OUString msLo;
    ::rtl::OUString msQs;
    ::rtl::OUString msCs;
};

// ====================================================================

class ChartGraphicDataContext : public ShapeContext
{
public:
    explicit            ChartGraphicDataContext(
                            ::oox::core::ContextHandler& rParent,
                            ShapePtr pShapePtr );

    virtual ::com::sun::star::uno::Reference< ::com::sun::star::xml::sax::XFastContextHandler > SAL_CALL
                        createFastChildContext(
                            sal_Int32 nElement,
                            const ::com::sun::star::uno::Reference< ::com::sun::star::xml::sax::XFastAttributeList >& rxAttribs )
                        throw (::com::sun::star::xml::sax::SAXException, ::com::sun::star::uno::RuntimeException);
};

// ====================================================================

} }

#endif  //  OOX_DRAWINGML_GRAPHICSHAPECONTEXT_HXX
