/*************************************************************************
 *
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER.
 * 
 * Copyright 2008 by Sun Microsystems, Inc.
 *
 * OpenOffice.org - a multi-platform office productivity suite
 *
 * $RCSfile: shapegroupcontext.cxx,v $
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

#include <com/sun/star/xml/sax/FastToken.hpp>
#include <com/sun/star/beans/XMultiPropertySet.hpp>
#include <com/sun/star/container/XNamed.hpp>

#include "oox/drawingml/shapegroupcontext.hxx"
#include "oox/drawingml/connectorshapecontext.hxx"
#include "oox/drawingml/graphicshapecontext.hxx"
#include "oox/drawingml/lineproperties.hxx"
#include "oox/drawingml/drawingmltypes.hxx"
#include "oox/drawingml/customshapegeometry.hxx"
#include "oox/drawingml/textbodycontext.hxx"
#include "oox/core/namespaces.hxx"
#include "tokens.hxx"

using rtl::OUString;
using namespace oox::core;
using namespace ::com::sun::star;
using namespace ::com::sun::star::uno;
using namespace ::com::sun::star::drawing;
using namespace ::com::sun::star::beans;
using namespace ::com::sun::star::text;
using namespace ::com::sun::star::xml::sax;

namespace oox { namespace drawingml {

ShapeGroupContext::ShapeGroupContext( ContextHandler& rParent, ShapePtr pMasterShapePtr, ShapePtr pGroupShapePtr )
: ContextHandler( rParent )
, mpGroupShapePtr( pGroupShapePtr )
, mpMasterShapePtr( pMasterShapePtr )
{
}

ShapeGroupContext::~ShapeGroupContext()
{
    if ( mpMasterShapePtr.get() && mpGroupShapePtr.get() )
        mpMasterShapePtr->addChild( mpGroupShapePtr );
}

Reference< XFastContextHandler > ShapeGroupContext::createFastChildContext( sal_Int32 aElementToken, const Reference< XFastAttributeList >& xAttribs ) throw (SAXException, RuntimeException)
{
    Reference< XFastContextHandler > xRet;

    switch( getToken( aElementToken ) )
    {
    case XML_cNvPr:
        mpGroupShapePtr->setId( xAttribs->getOptionalValue( XML_id ) );
        mpGroupShapePtr->setName( xAttribs->getOptionalValue( XML_name ) );
        break;
    case XML_ph:
        mpGroupShapePtr->setSubType( xAttribs->getOptionalValueToken( XML_type, FastToken::DONTKNOW ) );
        mpGroupShapePtr->setIndex( xAttribs->getOptionalValue( XML_idx ).toInt32() );
        break;
    // nvSpPr CT_ShapeNonVisual end

    case XML_grpSpPr:
        xRet = new ShapePropertiesContext( *this, *mpGroupShapePtr );
        break;
    case XML_spPr:
        xRet = new ShapePropertiesContext( *this, *mpGroupShapePtr );
        break;
/*
    case XML_style:
        xRet = new ShapeStyleContext( getParser() );
        break;
*/
    case XML_cxnSp:			// connector shape
        xRet.set( new ConnectorShapeContext( *this, mpGroupShapePtr, ShapePtr( new Shape( "com.sun.star.drawing.ConnectorShape" ) ) ) );
        break;
    case XML_grpSp:			// group shape
        xRet.set( new ShapeGroupContext( *this, mpGroupShapePtr, ShapePtr( new Shape( "com.sun.star.drawing.GroupShape" ) ) ) );
        break;
    case XML_sp:			// shape
        xRet.set( new ShapeContext( *this, mpGroupShapePtr, ShapePtr( new Shape( "com.sun.star.drawing.CustomShape" ) ) ) );
        break;
    case XML_pic:			// CT_Picture
        xRet.set( new GraphicShapeContext( *this, mpGroupShapePtr, ShapePtr( new Shape( "com.sun.star.drawing.GraphicObjectShape" ) ) ) );
        break;
    case XML_graphicFrame:	// CT_GraphicalObjectFrame
        xRet.set( new GraphicalObjectFrameContext( *this, mpGroupShapePtr, ShapePtr( new Shape( "com.sun.star.drawing.OLE2Shape" ) ) ) );
        break;
    }
    if( !xRet.is() )
        xRet.set( this );


    return xRet;
}

} }
