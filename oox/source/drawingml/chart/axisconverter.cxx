/*************************************************************************
 *
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER.
 * 
 * Copyright 2008 by Sun Microsystems, Inc.
 *
 * OpenOffice.org - a multi-platform office productivity suite
 *
 * $RCSfile: axisconverter.cxx,v $
 *
 * $Revision: 1.2 $
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

#include "oox/drawingml/chart/axisconverter.hxx"
#include <com/sun/star/chart2/AxisPosition.hpp>
#include <com/sun/star/chart2/AxisType.hpp>
#include <com/sun/star/chart2/XAxis.hpp>
#include <com/sun/star/chart2/XCoordinateSystem.hpp>
#include <com/sun/star/chart2/XTitled.hpp>
#include "oox/drawingml/chart/axismodel.hxx"
#include "oox/drawingml/chart/titleconverter.hxx"
#include "oox/drawingml/chart/typegroupconverter.hxx"

using ::rtl::OUString;
using ::com::sun::star::uno::Any;
using ::com::sun::star::uno::Reference;
using ::com::sun::star::uno::Sequence;
using ::com::sun::star::uno::Exception;
using ::com::sun::star::uno::UNO_QUERY;
using ::com::sun::star::uno::UNO_QUERY_THROW;
using ::com::sun::star::chart2::IncrementData;
using ::com::sun::star::chart2::ScaleData;
using ::com::sun::star::chart2::SubIncrement;
using ::com::sun::star::chart2::XAxis;
using ::com::sun::star::chart2::XCoordinateSystem;
using ::com::sun::star::chart2::XScaling;
using ::com::sun::star::chart2::XTitled;

namespace oox {
namespace drawingml {
namespace chart {

// ============================================================================

namespace {

template< typename Type >
inline void lclSetValueOrClearAny( Any& orAny, const OptValue< Type >& rValue )
{
    if( rValue.has() ) orAny <<= rValue.get(); else orAny.clear();
}

void lclSetScaledValueOrClearAny( Any& orAny, const OptDouble& rValue, const Reference< XScaling >& rxScaling )
{
    if( rValue.has() && rxScaling.is() )
        orAny <<= rxScaling->doScaling( rValue.get() );
    else
        lclSetValueOrClearAny( orAny, rValue );
}

} // namespace

// ============================================================================

AxisConverter::AxisConverter( const ConverterRoot& rParent, AxisModel& rModel ) :
    ConverterBase< AxisModel >( rParent, rModel )
{
}

AxisConverter::~AxisConverter()
{
}

void AxisConverter::convertModelToDocument( const Reference< XCoordinateSystem >& rxCoordSystem,
        TypeGroupConverter& rTypeGroup, sal_Int32 nAxesSetIdx, sal_Int32 nAxisIdx )
{
    Reference< XAxis > xAxis = createAxis( rTypeGroup, nAxesSetIdx, nAxisIdx );
    if( xAxis.is() && rxCoordSystem.is() ) try
    {
        // insert axis into coordinate system
        rxCoordSystem->setAxisByDimension( nAxisIdx, xAxis, nAxesSetIdx );
    }
    catch( Exception& )
    {
        OSL_ENSURE( false, "AxisConverter::convertModelToDocument - cannot insert axis into coordinate system" );
    }
}

// private --------------------------------------------------------------------

Reference< XAxis > AxisConverter::createAxis( TypeGroupConverter& rTypeGroup, sal_Int32 nAxesSetIdx, sal_Int32 nAxisIdx )
{
    Reference< XAxis > xAxis;
    try
    {
        // create the axis object (always)
        xAxis.set( createInstance( CREATE_OUSTRING( "com.sun.star.chart2.Axis" ) ), UNO_QUERY_THROW );
        PropertySet aAxisProp( xAxis );
        // #i58688# axis enabled
        aAxisProp.setProperty( CREATE_OUSTRING( "Show" ), !mrModel.mbDeleted );

        // axis line properties -----------------------------------------------

        //! TODO

        // axis ticks and tick labels -----------------------------------------

        //! TODO

        // axis type and X axis categories ------------------------------------

        const TypeGroupInfo& rTypeInfo = rTypeGroup.getTypeInfo();
        ScaleData aScaleData = xAxis->getScaleData();
        // set axis type
        namespace ApiAxisType = ::com::sun::star::chart2::AxisType;
        switch( nAxisIdx )
        {
            case API_X_AXIS:
                if( rTypeInfo.mbCategoryAxis )
                {
                    OSL_ENSURE( (mrModel.mnTypeId == C_TOKEN( catAx )) || (mrModel.mnTypeId == C_TOKEN( dateAx )),
                        "AxisConverter::createAxis - unexpected axis model type (must: c:catAx or c:dateEx)" );
                    aScaleData.AxisType = ApiAxisType::CATEGORY;
                    aScaleData.Categories = rTypeGroup.createCategorySequence();
                }
                else
                {
                    OSL_ENSURE( mrModel.mnTypeId == C_TOKEN( valAx ), "AxisConverter::createAxis - unexpected axis model type (must: c:valAx)" );
                    aScaleData.AxisType = ApiAxisType::REALNUMBER;
                }
            break;
            case API_Y_AXIS:
                OSL_ENSURE( mrModel.mnTypeId == C_TOKEN( valAx ), "AxisConverter::createAxis - unexpected axis model type (must: c:valAx)" );
                aScaleData.AxisType = rTypeGroup.isPercent() ? ApiAxisType::PERCENT : ApiAxisType::REALNUMBER;
            break;
            case API_Z_AXIS:
                OSL_ENSURE( mrModel.mnTypeId == C_TOKEN( serAx ), "AxisConverter::createAxis - unexpected axis model type (must: c:serAx)" );
                OSL_ENSURE( rTypeGroup.isDeep3dChart(), "AxisConverter::createAxis - series axis not supported by this chart type" );
                aScaleData.AxisType = ApiAxisType::SERIES;
            break;
        }

        // axis scaling and increment -----------------------------------------

        switch( aScaleData.AxisType )
        {
            case ApiAxisType::CATEGORY:
            case ApiAxisType::SERIES:
            {
                // do not overlap text
                aAxisProp.setProperty( CREATE_OUSTRING( "TextOverlap" ), false );
                // do not break text into several lines
                aAxisProp.setProperty( CREATE_OUSTRING( "TextBreak" ), false );
                // origin (min-cross or max-cross not supported, fall back to auto-cross)
                lclSetValueOrClearAny( aScaleData.Origin, mrModel.mofCrossesAt );
                //! TODO #i58731# show n-th category
            }
            break;
            case ApiAxisType::REALNUMBER:
            case ApiAxisType::PERCENT:
            {
                // scaling algorithm
                bool bLogScale = mrModel.mofLogBase.has() && (2.0 <= mrModel.mofLogBase.get()) && (mrModel.mofLogBase.get() <= 1000.0);
                OUString aScalingService = bLogScale ?
                    CREATE_OUSTRING( "com.sun.star.chart2.LogarithmicScaling" ) :
                    CREATE_OUSTRING( "com.sun.star.chart2.LinearScaling" );
                Reference< XScaling > xScaling( createInstance( aScalingService ), UNO_QUERY );
                Reference< XScaling > xLogScaling;
                if( xScaling.is() )
                {
                    aScaleData.Scaling = xScaling;
                    if( bLogScale )
                        xLogScaling = xScaling->getInverseScaling();
                }
                // min/max
                lclSetScaledValueOrClearAny( aScaleData.Minimum, mrModel.mofMin, xLogScaling );
                lclSetScaledValueOrClearAny( aScaleData.Maximum, mrModel.mofMax, xLogScaling );
                // origin (min-cross or max-cross not supported, fall back to auto-cross)
                lclSetScaledValueOrClearAny( aScaleData.Origin, mrModel.mofCrossesAt, xLogScaling );
                // major increment
                IncrementData& rIncrementData = aScaleData.IncrementData;
                lclSetValueOrClearAny( rIncrementData.Distance, mrModel.mofMajorUnit );
                // minor increment
                Sequence< SubIncrement >& rSubIncrementSeq = rIncrementData.SubIncrements;
                rSubIncrementSeq.realloc( 1 );
                OptInt32 nCount;
                if( mrModel.mofMajorUnit.has() && mrModel.mofMinorUnit.has() && (0.0 < mrModel.mofMinorUnit.get()) && (mrModel.mofMinorUnit.get() <= mrModel.mofMajorUnit.get()) )
                {
                    double fCount = mrModel.mofMajorUnit.get() / mrModel.mofMinorUnit.get() + 0.5;
                    if( (1.0 <= fCount) && (fCount < 1001.0) )
                        nCount = static_cast< sal_Int32 >( fCount );
                }
                lclSetValueOrClearAny( rSubIncrementSeq[ 0 ].IntervalCount, nCount );
            }
            break;
            default:
                OSL_ENSURE( false, "AxisConverter::createAxis - unknown axis type" );
        }

        // axis orientation ---------------------------------------------------

        // #i85167# pie/donut charts need hard reverse attribute at Y axis
        bool bReverse = (mrModel.mnOrientation == XML_maxMin) || ((nAxisIdx == API_Y_AXIS) && (rTypeInfo.meTypeCategory == TYPECATEGORY_PIE));
        namespace cssc = ::com::sun::star::chart2;
        aScaleData.Orientation = bReverse ? cssc::AxisOrientation_REVERSE : cssc::AxisOrientation_MATHEMATICAL;

        // write back scaling data
        xAxis->setScaleData( aScaleData );

        // grid ---------------------------------------------------------------

        //! TODO

        // axis position ------------------------------------------------------

        namespace ApiAxisPosition = ::com::sun::star::chart2::AxisPosition;
        sal_Int32 nPosition = (nAxesSetIdx == API_PRIM_AXESSET) ? ApiAxisPosition::MAIN : ApiAxisPosition::SECONDARY;
        aAxisProp.setProperty( CREATE_OUSTRING( "AxisPosition" ), nPosition );

        // axis title ---------------------------------------------------------

        if( mrModel.mxTitle.is() )
        {
            Reference< XTitled > xTitled( xAxis, UNO_QUERY_THROW );
            TitleConverter aTitleConv( *this, *mrModel.mxTitle );
            aTitleConv.convertModelToDocument( xTitled, CREATE_OUSTRING( "Axis Title" ) );
        }
    }
    catch( Exception& )
    {
    }

    return xAxis;
}

// ============================================================================

} // namespace chart
} // namespace drawingml
} // namespace oox

