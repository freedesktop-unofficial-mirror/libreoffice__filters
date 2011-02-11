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

#include <com/sun/star/xml/sax/FastToken.hpp>
#include <com/sun/star/beans/XMultiPropertySet.hpp>
#include <com/sun/star/container/XNamed.hpp>

#include "oox/helper/attributelist.hxx"
#include "oox/ppt/pptshape.hxx"
#include "oox/ppt/pptshapecontext.hxx"
#include "oox/ppt/pptshapegroupcontext.hxx"
#include "oox/drawingml/graphicshapecontext.hxx"
#include "oox/drawingml/lineproperties.hxx"
#include "oox/drawingml/drawingmltypes.hxx"
#include "oox/drawingml/customshapegeometry.hxx"
#include "oox/drawingml/textbodycontext.hxx"
#include "oox/drawingml/connectorshapecontext.hxx"

using rtl::OUString;
using namespace oox::core;
using namespace ::com::sun::star;
using namespace ::com::sun::star::uno;
using namespace ::com::sun::star::drawing;
using namespace ::com::sun::star::beans;
using namespace ::com::sun::star::text;
using namespace ::com::sun::star::xml::sax;

namespace oox { namespace ppt {

PPTShapeGroupContext::PPTShapeGroupContext(
        ContextHandler& rParent,
        const oox::ppt::SlidePersistPtr pSlidePersistPtr,
        const ShapeLocation eShapeLocation,
        oox::drawingml::ShapePtr pMasterShapePtr,
        oox::drawingml::ShapePtr pGroupShapePtr )
: ShapeGroupContext( rParent, pMasterShapePtr, pGroupShapePtr )
, mpSlidePersistPtr( pSlidePersistPtr )
, meShapeLocation( eShapeLocation )
{
}

Reference< XFastContextHandler > PPTShapeGroupContext::createFastChildContext( sal_Int32 aElementToken, const Reference< XFastAttributeList >& xAttribs ) throw (SAXException, RuntimeException)
{
    Reference< XFastContextHandler > xRet;

    switch( aElementToken )
    {
    case PPT_TOKEN( cNvPr ):
    {
        AttributeList aAttribs( xAttribs );
        mpGroupShapePtr->setHidden( aAttribs.getBool( XML_hidden, false ) );
        mpGroupShapePtr->setId( xAttribs->getOptionalValue( XML_id ) );
        mpGroupShapePtr->setName( xAttribs->getOptionalValue( XML_name ) );
        break;
    }
    case PPT_TOKEN( ph ):
        mpGroupShapePtr->setSubType( xAttribs->getOptionalValueToken( XML_type, FastToken::DONTKNOW ) );
        mpGroupShapePtr->setSubTypeIndex( xAttribs->getOptionalValue( XML_idx ).toInt32() );
        break;
    // nvSpPr CT_ShapeNonVisual end

    case PPT_TOKEN( grpSpPr ):
        xRet = new oox::drawingml::ShapePropertiesContext( *this, *mpGroupShapePtr );
        break;
    case PPT_TOKEN( spPr ):
        xRet = new oox::drawingml::ShapePropertiesContext( *this, *mpGroupShapePtr );
        break;
/*
    case PPT_TOKEN( style ):
        xRet = new ShapeStyleContext( getParser() );
        break;
*/
    case PPT_TOKEN( cxnSp ):		// connector shape
        xRet.set( new oox::drawingml::ConnectorShapeContext( *this, mpGroupShapePtr, oox::drawingml::ShapePtr( new PPTShape( meShapeLocation, "com.sun.star.drawing.ConnectorShape" ) ) ) );
        break;
    case PPT_TOKEN( grpSp ):		// group shape
        xRet.set( new PPTShapeGroupContext( *this, mpSlidePersistPtr, meShapeLocation, mpGroupShapePtr, oox::drawingml::ShapePtr( new PPTShape( meShapeLocation, "com.sun.star.drawing.GroupShape" ) ) ) );
        break;
    case PPT_TOKEN( sp ):			// Shape
        xRet.set( new PPTShapeContext( *this, mpSlidePersistPtr, mpGroupShapePtr, oox::drawingml::ShapePtr( new PPTShape( meShapeLocation, "com.sun.star.drawing.CustomShape" ) ) ) );
        break;
    case PPT_TOKEN( pic ):			// CT_Picture
        xRet.set( new oox::drawingml::GraphicShapeContext( *this, mpGroupShapePtr,  oox::drawingml::ShapePtr( new PPTShape( meShapeLocation, "com.sun.star.drawing.GraphicObjectShape" ) ) ) );
        break;
    case PPT_TOKEN( graphicFrame ):	// CT_GraphicalObjectFrame
        xRet.set( new oox::drawingml::GraphicalObjectFrameContext( *this, mpGroupShapePtr, oox::drawingml::ShapePtr( new PPTShape( meShapeLocation, "com.sun.star.drawing.OLE2Shape" ) ), true ) );
        break;

    }
    if( !xRet.is() )
        xRet.set( this );


    return xRet;
}

} }
