/*************************************************************************
 *
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER.
 * 
 * Copyright 2008 by Sun Microsystems, Inc.
 *
 * OpenOffice.org - a multi-platform office productivity suite
 *
 * $RCSfile: axiscontext.cxx,v $
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

#include "oox/drawingml/chart/axiscontext.hxx"
#include "oox/drawingml/shapepropertiescontext.hxx"
#include "oox/drawingml/textbodycontext.hxx"
#include "oox/drawingml/chart/axismodel.hxx"
#include "oox/drawingml/chart/titlecontext.hxx"

using ::oox::core::ContextHandler2Helper;
using ::oox::core::ContextWrapper;

namespace oox {
namespace drawingml {
namespace chart {

// ============================================================================

AxisDispUnitsContext::AxisDispUnitsContext( ContextHandler2Helper& rParent, AxisDispUnitsModel& rModel ) :
    ContextBase< AxisDispUnitsModel >( rParent, rModel )
{
}

AxisDispUnitsContext::~AxisDispUnitsContext()
{
}

ContextWrapper AxisDispUnitsContext::onCreateContext( sal_Int32 nElement, const AttributeList& rAttribs )
{
    switch( getCurrentElement() )
    {
        case C_TOKEN( dispUnits ):
            switch( nElement )
            {
                case C_TOKEN( builtInUnit ):
                    mrModel.mnBuiltInUnit = rAttribs.getToken( XML_val, XML_thousands );
                    return false;
                case C_TOKEN( custUnit ):
                    mrModel.mfCustomUnit = rAttribs.getDouble( XML_val, 0.0 );
                    return false;
                case C_TOKEN( dispUnitsLbl ):
                    return true;
            }
        break;

        case C_TOKEN( dispUnitsLbl ):
            switch( nElement )
            {
                case C_TOKEN( layout ):
                    return new LayoutContext( *this, mrModel.mxLayout.create() );
                case C_TOKEN( spPr ):
                    return new ShapePropertiesContext( *this, mrModel.mxShapeProp.create() );
                case C_TOKEN( tx ):
                    return new TextContext( *this, mrModel.mxText.create() );
                case C_TOKEN( txPr ):
                    return new TextBodyContext( *this, mrModel.mxTextProp.create() );
            }
        break;
    }
    return false;
}

// ============================================================================

AxisContextBase::AxisContextBase( ContextHandler2Helper& rParent, AxisModel& rModel ) :
    ContextBase< AxisModel >( rParent, rModel )
{
}

AxisContextBase::~AxisContextBase()
{
}

ContextWrapper AxisContextBase::onCreateContext( sal_Int32 nElement, const AttributeList& rAttribs )
{
    switch( getCurrentElement() )
    {
        case C_TOKEN( catAx ):
        case C_TOKEN( dateAx ):
        case C_TOKEN( serAx ):
        case C_TOKEN( valAx ):
            switch( nElement )
            {
                case C_TOKEN( axId ):
                    mrModel.mnAxisId = rAttribs.getInteger( XML_val, -1 );
                    return false;
                case C_TOKEN( crossAx ):
                    mrModel.mnCrossAxisId = rAttribs.getInteger( XML_val, -1 );
                    return false;
                case C_TOKEN( crosses ):
                    mrModel.mnCrossMode = rAttribs.getToken( XML_val, XML_autoZero );
                    return false;
                case C_TOKEN( crossesAt ):
                    mrModel.mofCrossesAt = rAttribs.getDouble( XML_val, 0.0 );
                    return false;
                case C_TOKEN( delete ):
                    mrModel.mbDeleted = rAttribs.getBool( XML_val, true );
                    return false;
                case C_TOKEN( majorGridlines ):
                    return new ShapePrWrapperContext( *this, mrModel.mxMajorGridLines.create() );
                case C_TOKEN( majorTickMark ):
                    mrModel.mnMajorTickMark = rAttribs.getToken( XML_val, XML_cross );
                    return false;
                case C_TOKEN( minorGridlines ):
                    return new ShapePrWrapperContext( *this, mrModel.mxMinorGridLines.create() );
                case C_TOKEN( minorTickMark ):
                    mrModel.mnMinorTickMark = rAttribs.getToken( XML_val, XML_cross );
                    return false;
                case C_TOKEN( numFmt ):
                    mrModel.maFormatCode = rAttribs.getString( XML_formatCode );
                    mrModel.mbSourceLinked = rAttribs.getBool( XML_sourceLinked, true );
                    return false;
                case C_TOKEN( scaling ):
                    return true;
                case C_TOKEN( spPr ):
                    return new ShapePropertiesContext( *this, mrModel.mxShapeProp.create() );
                case C_TOKEN( tickLblPos ):
                    mrModel.mnTickLabelPos = rAttribs.getToken( XML_val, XML_nextTo );
                    return false;
                case C_TOKEN( title ):
                    return new TitleContext( *this, mrModel.mxTitle.create() );
                case C_TOKEN( txPr ):
                    return new TextBodyContext( *this, mrModel.mxTextProp.create() );
            }
        break;

        case C_TOKEN( scaling ):
            switch( nElement )
            {
                case C_TOKEN( logBase ):
                    mrModel.mofLogBase = rAttribs.getDouble( XML_val, 0.0 );
                    return false;
                case C_TOKEN( max ):
                    mrModel.mofMax = rAttribs.getDouble( XML_val, 0.0 );
                    return false;
                case C_TOKEN( min ):
                    mrModel.mofMin = rAttribs.getDouble( XML_val, 0.0 );
                    return false;
                case C_TOKEN( orientation ):
                    mrModel.mnOrientation = rAttribs.getToken( XML_val, XML_minMax );
                    return false;
            }
        break;
    }
    return false;
}

// ============================================================================

CatAxisContext::CatAxisContext( ContextHandler2Helper& rParent, AxisModel& rModel ) :
    AxisContextBase( rParent, rModel )
{
}

CatAxisContext::~CatAxisContext()
{
}

ContextWrapper CatAxisContext::onCreateContext( sal_Int32 nElement, const AttributeList& rAttribs )
{
    if( isRootElement() ) switch( nElement )
    {
        case C_TOKEN( auto ):
            mrModel.mbAuto = rAttribs.getBool( XML_val, true );
            return false;
        case C_TOKEN( axPos ):
            mrModel.mnAxisPos = rAttribs.getToken( XML_val );
            return false;
        case C_TOKEN( lblAlgn ):
            mrModel.mnLabelAlign = rAttribs.getToken( XML_val, XML_ctr );
            return false;
        case C_TOKEN( lblOffset ):
            mrModel.mnLabelOffset = rAttribs.getInteger( XML_val, 100 );
            return false;
        case C_TOKEN( noMultiLvlLbl ):
            mrModel.mbNoMultiLevel = rAttribs.getBool( XML_val, true );
            return false;
        case C_TOKEN( tickLblSkip ):
            mrModel.mnTickLabelSkip = rAttribs.getInteger( XML_val, 0 );
            return false;
        case C_TOKEN( tickMarkSkip ):
            mrModel.mnTickMarkSkip = rAttribs.getInteger( XML_val, 0 );
            return false;
    }
    return AxisContextBase::onCreateContext( nElement, rAttribs );
}

// ============================================================================

DateAxisContext::DateAxisContext( ContextHandler2Helper& rParent, AxisModel& rModel ) :
    AxisContextBase( rParent, rModel )
{
}

DateAxisContext::~DateAxisContext()
{
}

ContextWrapper DateAxisContext::onCreateContext( sal_Int32 nElement, const AttributeList& rAttribs )
{
    if( isRootElement() ) switch( nElement )
    {
        case C_TOKEN( auto ):
            mrModel.mbAuto = rAttribs.getBool( XML_val, true );
            return false;
        case C_TOKEN( baseTimeUnit ):
            mrModel.mnBaseTimeUnit = rAttribs.getToken( XML_val, XML_days );
            return false;
        case C_TOKEN( lblOffset ):
            mrModel.mnLabelOffset = rAttribs.getInteger( XML_val, 100 );
            return false;
        case C_TOKEN( majorTimeUnit ):
            mrModel.mnMajorTimeUnit = rAttribs.getToken( XML_val, XML_days );
            return false;
        case C_TOKEN( majorUnit ):
            mrModel.mofMajorUnit = rAttribs.getDouble( XML_val, 0.0 );
            return false;
        case C_TOKEN( minorTimeUnit ):
            mrModel.mnMinorTimeUnit = rAttribs.getToken( XML_val, XML_days );
            return false;
        case C_TOKEN( minorUnit ):
            mrModel.mofMinorUnit = rAttribs.getDouble( XML_val, 0.0 );
            return false;
    }
    return AxisContextBase::onCreateContext( nElement, rAttribs );
}

// ============================================================================

SerAxisContext::SerAxisContext( ContextHandler2Helper& rParent, AxisModel& rModel ) :
    AxisContextBase( rParent, rModel )
{
}

SerAxisContext::~SerAxisContext()
{
}

ContextWrapper SerAxisContext::onCreateContext( sal_Int32 nElement, const AttributeList& rAttribs )
{
    if( isRootElement() ) switch( nElement )
    {
        case C_TOKEN( tickLblSkip ):
            mrModel.mnTickLabelSkip = rAttribs.getInteger( XML_val, 0 );
            return false;
        case C_TOKEN( tickMarkSkip ):
            mrModel.mnTickMarkSkip = rAttribs.getInteger( XML_val, 0 );
            return false;
    }
    return AxisContextBase::onCreateContext( nElement, rAttribs );
}

// ============================================================================

ValAxisContext::ValAxisContext( ContextHandler2Helper& rParent, AxisModel& rModel ) :
    AxisContextBase( rParent, rModel )
{
}

ValAxisContext::~ValAxisContext()
{
}

ContextWrapper ValAxisContext::onCreateContext( sal_Int32 nElement, const AttributeList& rAttribs )
{
    if( isRootElement() ) switch( nElement )
    {
        case C_TOKEN( crossBetween ):
            mrModel.mnCrossBetween = rAttribs.getToken( XML_val, XML_between );
            return false;
        case C_TOKEN( dispUnits ):
            return new AxisDispUnitsContext( *this, mrModel.mxDispUnits.create() );
        case C_TOKEN( majorUnit ):
            mrModel.mofMajorUnit = rAttribs.getDouble( XML_val, 0.0 );
            return false;
        case C_TOKEN( minorUnit ):
            mrModel.mofMinorUnit = rAttribs.getDouble( XML_val, 0.0 );
            return false;
    }
    return AxisContextBase::onCreateContext( nElement, rAttribs );
}

// ============================================================================

} // namespace chart
} // namespace drawingml
} // namespace oox

