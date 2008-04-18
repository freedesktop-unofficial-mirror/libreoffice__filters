/*************************************************************************
 *
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER.
 * 
 * Copyright 2008 by Sun Microsystems, Inc.
 *
 * OpenOffice.org - a multi-platform office productivity suite
 *
 * $RCSfile: plotareacontext.hxx,v $
 * $Revision: 1.4 $
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

#ifndef OOX_DRAWINGML_CHART_PLOTAREACONTEXT_HXX
#define OOX_DRAWINGML_CHART_PLOTAREACONTEXT_HXX

#include "oox/drawingml/chart/chartcontextbase.hxx"

namespace oox {
namespace drawingml {
namespace chart {

// ============================================================================

struct View3DModel;

/** Handler for a chart plot area context (c:plotArea element).
 */
class View3DContext : public ContextBase< View3DModel >
{
public:
    explicit            View3DContext( ::oox::core::ContextHandler2Helper& rParent, View3DModel& rModel );
    virtual             ~View3DContext();

    virtual ::oox::core::ContextWrapper onCreateContext( sal_Int32 nElement, const AttributeList& rAttribs );
};

// ============================================================================

struct PlotAreaModel;

/** Handler for a chart plot area context (c:plotArea element).
 */
class PlotAreaContext : public ContextBase< PlotAreaModel >
{
public:
    explicit            PlotAreaContext( ::oox::core::ContextHandler2Helper& rParent, PlotAreaModel& rModel );
    virtual             ~PlotAreaContext();

    virtual ::oox::core::ContextWrapper onCreateContext( sal_Int32 nElement, const AttributeList& rAttribs );
};

// ============================================================================

} // namespace chart
} // namespace drawingml
} // namespace oox

#endif

