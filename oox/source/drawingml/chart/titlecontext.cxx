/*************************************************************************
 *
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER.
 *
 * Copyright 2008 by Sun Microsystems, Inc.
 *
 * OpenOffice.org - a multi-platform office productivity suite
 *
 * $RCSfile: titlecontext.cxx,v $
 *
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

#include "oox/drawingml/chart/titlecontext.hxx"
#include "oox/drawingml/shapepropertiescontext.hxx"
#include "oox/drawingml/textbodycontext.hxx"
#include "oox/drawingml/chart/datasourcecontext.hxx"
#include "oox/drawingml/chart/titlemodel.hxx"

using ::rtl::OUString;
using ::oox::core::ContextHandler2Helper;
using ::oox::core::ContextWrapper;

namespace oox {
namespace drawingml {
namespace chart {

// ============================================================================

LayoutContext::LayoutContext( ContextHandler2Helper& rParent, LayoutModel& rModel ) :
    ContextBase< LayoutModel >( rParent, rModel )
{
}

LayoutContext::~LayoutContext()
{
}

ContextWrapper LayoutContext::onCreateContext( sal_Int32 nElement, const AttributeList& rAttribs )
{
    switch( getCurrentElement() )
    {
        case C_TOKEN( layout ):
            return  (nElement == C_TOKEN( manualLayout ));

        case C_TOKEN( manualLayout ):
            switch( nElement )
            {
                case C_TOKEN( x ):
                    mrModel.mfX = rAttribs.getDouble( XML_val, 0.0 );
                    return false;
                case C_TOKEN( y ):
                    mrModel.mfY = rAttribs.getDouble( XML_val, 0.0 );
                    return false;
                case C_TOKEN( w ):
                    mrModel.mfW = rAttribs.getDouble( XML_val, 0.0 );
                    return false;
                case C_TOKEN( h ):
                    mrModel.mfH = rAttribs.getDouble( XML_val, 0.0 );
                    return false;
                case C_TOKEN( xMode ):
                    mrModel.mnXMode = rAttribs.getToken( XML_val, XML_factor );
                    return false;
                case C_TOKEN( yMode ):
                    mrModel.mnYMode = rAttribs.getToken( XML_val, XML_factor );
                    return false;
                case C_TOKEN( wMode ):
                    mrModel.mnWMode = rAttribs.getToken( XML_val, XML_factor );
                    return false;
                case C_TOKEN( hMode ):
                    mrModel.mnHMode = rAttribs.getToken( XML_val, XML_factor );
                    return false;
                case C_TOKEN( layoutTarget ):
                    mrModel.mnTarget = rAttribs.getToken( XML_val, XML_outer );
                    return false;
            }
        break;
    }
    return false;
}

// ============================================================================

TextContext::TextContext( ContextHandler2Helper& rParent, TextModel& rModel ) :
    ContextBase< TextModel >( rParent, rModel )
{
}

TextContext::~TextContext()
{
}

ContextWrapper TextContext::onCreateContext( sal_Int32 nElement, const AttributeList& )
{
    switch( getCurrentElement() )
    {
        case C_TOKEN( tx ):
            switch( nElement )
            {
                case C_TOKEN( rich ):
                    return new TextBodyContext( *this, mrModel.mxTextBody.create() );
                case C_TOKEN( strRef ):
                    OSL_ENSURE( !mrModel.mxDataSeq, "TextContext::onCreateContext - multiple data sequences" );
                    return new StringSequenceContext( *this, mrModel.mxDataSeq.create() );
                case C_TOKEN( v ):
                    OSL_ENSURE( !mrModel.mxDataSeq, "TextContext::onCreateContext - multiple data sequences" );
                    return true;
            }
        break;
    }
    return false;
}

void TextContext::onEndElement( const OUString& rChars )
{
    switch( getCurrentElement() )
    {
        case C_TOKEN( v ):
            // store as single string sequence element
            mrModel.mxDataSeq.create().maData[ 0 ] <<= rChars;
        break;
    }
}

// ============================================================================

TitleContext::TitleContext( ContextHandler2Helper& rParent, TitleModel& rModel ) :
    ContextBase< TitleModel >( rParent, rModel )
{
}

TitleContext::~TitleContext()
{
}

ContextWrapper TitleContext::onCreateContext( sal_Int32 nElement, const AttributeList& rAttribs )
{
    switch( getCurrentElement() )
    {
        case C_TOKEN( title ):
            switch( nElement )
            {
                case C_TOKEN( layout ):
                    return new LayoutContext( *this, mrModel.mxLayout.create() );
                case C_TOKEN( overlay ):
                    // default is 'false', not 'true' as specified
                    mrModel.mbOverlay = rAttribs.getBool( XML_val, false );
                    return false;
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

LegendContext::LegendContext( ContextHandler2Helper& rParent, LegendModel& rModel ) :
    ContextBase< LegendModel >( rParent, rModel )
{
}

LegendContext::~LegendContext()
{
}

ContextWrapper LegendContext::onCreateContext( sal_Int32 nElement, const AttributeList& rAttribs )
{
    switch( getCurrentElement() )
    {
        case C_TOKEN( legend ):
            switch( nElement )
            {
                case C_TOKEN( layout ):
                    return new LayoutContext( *this, mrModel.mxLayout.create() );
                case C_TOKEN( legendPos ):
                    mrModel.mnPosition = rAttribs.getToken( XML_val, XML_r );
                    return false;
                case C_TOKEN( overlay ):
                    // default is 'false', not 'true' as specified
                    mrModel.mbOverlay = rAttribs.getBool( XML_val, false );
                    return false;
                case C_TOKEN( spPr ):
                    return new ShapePropertiesContext( *this, mrModel.mxShapeProp.create() );
                case C_TOKEN( txPr ):
                    return new TextBodyContext( *this, mrModel.mxTextProp.create() );
            }
        break;
    }
    return false;
}

// ============================================================================

} // namespace chart
} // namespace drawingml
} // namespace oox

