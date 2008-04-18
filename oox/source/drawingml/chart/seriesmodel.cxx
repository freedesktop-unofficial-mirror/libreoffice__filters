/*************************************************************************
 *
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER.
 * 
 * Copyright 2008 by Sun Microsystems, Inc.
 *
 * OpenOffice.org - a multi-platform office productivity suite
 *
 * $RCSfile: seriesmodel.cxx,v $
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

#include "oox/drawingml/chart/seriesmodel.hxx"

namespace oox {
namespace drawingml {
namespace chart {

// ============================================================================

DataLabelModelBase::DataLabelModelBase() :
    mbDeleted( false )
{
}

DataLabelModelBase::~DataLabelModelBase()
{
}

// ============================================================================

DataLabelModel::DataLabelModel() :
    mnIndex( -1 )
{
}

DataLabelModel::~DataLabelModel()
{
}

// ============================================================================

DataLabelsModel::DataLabelsModel()
{
}

DataLabelsModel::~DataLabelsModel()
{
}

// ============================================================================

ErrorBarModel::ErrorBarModel() :
    mfValue( 0.0 ),
    mnDirection( XML_TOKEN_INVALID ),
    mnTypeId( XML_both ),
    mnValueType( XML_fixedVal ),
    mbNoEndCap( false )
{
}

ErrorBarModel::~ErrorBarModel()
{
}

// ============================================================================

TrendlineModel::TrendlineModel() :
    mnOrder( 2 ),
    mnPeriod( 2 ),
    mnTypeId( XML_linear ),
    mbDispEquation( false ),
    mbDispRSquared( false )
{
}

TrendlineModel::~TrendlineModel()
{
}

// ============================================================================

DataPointModel::DataPointModel() :
    mnIndex( -1 )
{
}

DataPointModel::~DataPointModel()
{
}

// ============================================================================

SeriesModel::SeriesModel() :
    mnExplosion( 0 ),
    mnIndex( -1 ),
    mnMarkerSize( 5 ),
    mnMarkerSymbol( XML_auto ),
    mnOrder( -1 ),
    mbInvertNeg( false )
{
}

SeriesModel::~SeriesModel()
{
}

// ============================================================================

} // namespace chart
} // namespace drawingml
} // namespace oox

