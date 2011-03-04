/* -*- Mode: C++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */
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

#ifndef OOX_SHAPE_SHAPEFILTERBASE_HXX
#define OOX_SHAPE_SHAPEFILTERBASE_HXX

#include <boost/shared_ptr.hpp>
#include <rtl/ref.hxx>
#include "oox/vml/vmldrawing.hxx"
#include "oox/drawingml/table/tablestylelist.hxx"
#include "oox/core/xmlfilterbase.hxx"

namespace oox {
namespace shape {

// ============================================================================

class ShapeFilterBase : public core::XmlFilterBase
{
public:
    typedef boost::shared_ptr<ShapeFilterBase> Pointer_t;

    explicit            ShapeFilterBase(
                            const ::com::sun::star::uno::Reference< ::com::sun::star::uno::XComponentContext >& rxContext )
                            throw( ::com::sun::star::uno::RuntimeException );

    virtual             ~ShapeFilterBase();

    /** Has to be implemented by each filter, returns the current theme. */
    virtual const ::oox::drawingml::Theme* getCurrentTheme() const;

    /** Has to be implemented by each filter to return the collection of VML shapes. */
    virtual ::oox::vml::Drawing* getVmlDrawing();

    /** Has to be implemented by each filter to return TableStyles. */
    virtual const ::oox::drawingml::table::TableStyleListPtr getTableStyles();

    virtual ::oox::drawingml::chart::ChartConverter& getChartConverter();

    virtual bool importDocument() { return true; }
    virtual bool exportDocument() { return true; }

private:
    virtual ::oox::ole::VbaProject* implCreateVbaProject() const;
    virtual rtl::OUString implGetImplementationName() const;

    ::boost::shared_ptr< ::oox::drawingml::chart::ChartConverter > mxChartConv;
};

// ============================================================================

} // namespace shape
} // namespace oox

#endif

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
