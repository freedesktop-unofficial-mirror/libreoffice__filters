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

#ifndef OOX_DRAWINGML_COLORCHOICECONTEXT_HXX
#define OOX_DRAWINGML_COLORCHOICECONTEXT_HXX

#include "oox/core/contexthandler.hxx"

namespace oox {
namespace drawingml {

class Color;

// ============================================================================

/** Context handler for the different color value elements (a:scrgbClr,
    a:srgbClr, a:hslClr, a:sysClr, a:schemeClr, a:prstClr). */
class ColorValueContext : public ::oox::core::ContextHandler
{
public:
    explicit            ColorValueContext( ::oox::core::ContextHandler& rParent, Color& rColor );

    virtual void SAL_CALL startFastElement(
                            sal_Int32 nElement,
                            const ::com::sun::star::uno::Reference< ::com::sun::star::xml::sax::XFastAttributeList >& rxAttribs )
                        throw (::com::sun::star::xml::sax::SAXException, ::com::sun::star::uno::RuntimeException);

    virtual ::com::sun::star::uno::Reference< ::com::sun::star::xml::sax::XFastContextHandler > SAL_CALL
                        createFastChildContext(
                            sal_Int32 nElement,
                            const ::com::sun::star::uno::Reference< ::com::sun::star::xml::sax::XFastAttributeList >& rxAttribs )
                        throw (::com::sun::star::xml::sax::SAXException, ::com::sun::star::uno::RuntimeException);

private:
    Color&              mrColor;
};

// ============================================================================

/** Context handler for elements that *contain* a color value element
    (a:scrgbClr, a:srgbClr, a:hslClr, a:sysClr, a:schemeClr, a:prstClr). */
class ColorContext : public ::oox::core::ContextHandler
{
public:
    explicit            ColorContext( ::oox::core::ContextHandler& rParent, Color& rColor );

    virtual ::com::sun::star::uno::Reference< ::com::sun::star::xml::sax::XFastContextHandler > SAL_CALL
                        createFastChildContext(
                            sal_Int32 nElement,
                            const ::com::sun::star::uno::Reference< ::com::sun::star::xml::sax::XFastAttributeList >& rxAttribs )
                        throw (::com::sun::star::xml::sax::SAXException, ::com::sun::star::uno::RuntimeException);

private:
    Color&              mrColor;
};

// ============================================================================

} // namespace drawingml
} // namespace oox

#endif

