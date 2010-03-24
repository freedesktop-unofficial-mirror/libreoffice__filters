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

#include "oox/drawingml/chart/titlemodel.hxx"

namespace oox {
namespace drawingml {
namespace chart {

// ============================================================================

LayoutModel::LayoutModel() :
    mfX( 0.0 ),
    mfY( 0.0 ),
    mfW( 0.0 ),
    mfH( 0.0 ),
    mnXMode( XML_factor ),
    mnYMode( XML_factor ),
    mnWMode( XML_factor ),
    mnHMode( XML_factor ),
    mnTarget( XML_outer )
{
}

LayoutModel::~LayoutModel()
{
}

// ============================================================================

TextModel::TextModel()
{
}

TextModel::~TextModel()
{
}

// ============================================================================

TitleModel::TitleModel() :
    mbOverlay( false )
{
}

TitleModel::~TitleModel()
{
}

// ============================================================================

LegendModel::LegendModel() :
    mnPosition( XML_r ),
    mbOverlay( false )
{
}

LegendModel::~LegendModel()
{
}

// ============================================================================

} // namespace chart
} // namespace drawingml
} // namespace oox

