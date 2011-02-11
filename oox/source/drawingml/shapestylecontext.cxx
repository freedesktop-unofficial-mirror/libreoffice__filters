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

#include "oox/drawingml/shapestylecontext.hxx"

#include "oox/helper/attributelist.hxx"
#include "oox/drawingml/colorchoicecontext.hxx"

using ::rtl::OUString;
using namespace ::oox::core;
using namespace ::com::sun::star::uno;
using namespace ::com::sun::star::xml::sax;

namespace oox { namespace drawingml {

// ---------------
// CT_ShapeStyle
// ---------------
ShapeStyleContext::ShapeStyleContext( ContextHandler& rParent, Shape& rShape )
: ContextHandler( rParent )
, mrShape( rShape )
{
}

ShapeStyleContext::~ShapeStyleContext()
{
}

// --------------------------------------------------------------------

void ShapeStyleContext::endFastElement( sal_Int32 ) throw (SAXException, RuntimeException)
{
}

// --------------------------------------------------------------------

Reference< XFastContextHandler > ShapeStyleContext::createFastChildContext( sal_Int32 aElementToken, const Reference< XFastAttributeList >& rxAttributes )
    throw ( SAXException, RuntimeException )
{
    Reference< XFastContextHandler > xRet;
    AttributeList aAttribs( rxAttributes );
    switch( aElementToken )
    {
        case A_TOKEN( lnRef ) :     // CT_StyleMatrixReference
        case A_TOKEN( fillRef ) :   // CT_StyleMatrixReference
        case A_TOKEN( effectRef ) : // CT_StyleMatrixReference
        case A_TOKEN( fontRef ) :   // CT_FontReference
        {
            sal_Int32 nToken = getBaseToken( aElementToken );
            ShapeStyleRef& rStyleRef = mrShape.getShapeStyleRefs()[ nToken ];
            rStyleRef.mnThemedIdx = (nToken == XML_fontRef) ? aAttribs.getToken( XML_idx, XML_none ) : aAttribs.getInteger( XML_idx, 0 );
            xRet.set( new ColorContext( *this, rStyleRef.maPhClr ) );
        }
        break;
    }
    return xRet;
}

// --------------------------------------------------------------------

} }

