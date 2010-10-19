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

#include "diagramdefinitioncontext.hxx"
#include "oox/core/namespaces.hxx"
#include "layoutnodecontext.hxx"
#include "datamodelcontext.hxx"
#include "tokens.hxx"

using namespace ::oox::core;
using namespace ::com::sun::star::uno;
using namespace ::com::sun::star::xml::sax;
using ::rtl::OUString;

namespace oox { namespace drawingml {


// CT_DiagramDefinition
DiagramDefinitionContext::DiagramDefinitionContext( ContextHandler& rParent,
                                                    const Reference< XFastAttributeList >& xAttributes,
                                                    const DiagramLayoutPtr &pLayout )
    : ContextHandler( rParent )
    , mpLayout( pLayout )
{
    OSL_TRACE( "OOX: DiagramDefinitionContext::DiagramDefinitionContext()" );
    mpLayout->setDefStyle( xAttributes->getOptionalValue( XML_defStyle ) );
    OUString sValue = xAttributes->getOptionalValue( XML_minVer );
    if( sValue.getLength() == 0 )
    {
        sValue = CREATE_OUSTRING( "http://schemas.openxmlformats.org/drawingml/2006/diagram" );
    }
    mpLayout->setMinVer( sValue );
    mpLayout->setUniqueId( xAttributes->getOptionalValue( XML_uniqueId ) );
}


DiagramDefinitionContext::~DiagramDefinitionContext()
{
    mpLayout->getNode()->dump(0);
}

void SAL_CALL DiagramDefinitionContext::endFastElement( ::sal_Int32 )
    throw (SAXException, RuntimeException)
{

}


Reference< XFastContextHandler > SAL_CALL
DiagramDefinitionContext::createFastChildContext( ::sal_Int32 aElement,
                                                  const Reference< XFastAttributeList >& xAttribs )
    throw (SAXException, RuntimeException)
{
    Reference< XFastContextHandler > xRet;

    switch( aElement )
    {
    case NMSP_DIAGRAM|XML_title:
        mpLayout->setTitle( xAttribs->getOptionalValue( XML_val ) );
        break;
    case NMSP_DIAGRAM|XML_desc:
        mpLayout->setDesc( xAttribs->getOptionalValue( XML_val ) );
        break;
    case NMSP_DIAGRAM|XML_layoutNode:
    {
        LayoutNodePtr pNode( new LayoutNode() );
        mpLayout->getNode() = pNode;
        pNode->setChildOrder( xAttribs->getOptionalValueToken( XML_chOrder, XML_b ) );
        pNode->setMoveWith( xAttribs->getOptionalValue( XML_moveWith ) );
        pNode->setStyleLabel( xAttribs->getOptionalValue( XML_styleLbl ) );
        xRet.set( new LayoutNodeContext( *this, xAttribs, pNode ) );
        break;
    }
     case NMSP_DIAGRAM|XML_clrData:
        // TODO, does not matter for the UI. skip.
        return xRet;
    case NMSP_DIAGRAM|XML_sampData:
        mpLayout->getSampData().reset( new DiagramData );
        xRet.set( new DataModelContext( *this, mpLayout->getSampData() ) );
        break;
    case NMSP_DIAGRAM|XML_styleData:
        mpLayout->getStyleData().reset( new DiagramData );
        xRet.set( new DataModelContext( *this, mpLayout->getStyleData() ) );
        break;
    case NMSP_DIAGRAM|XML_cat:
    case NMSP_DIAGRAM|XML_catLst:
        // TODO, does not matter for the UI
    default:
        break;
    }
    if( !xRet.is() )
        xRet.set(this);

    return xRet;
}


} }

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
