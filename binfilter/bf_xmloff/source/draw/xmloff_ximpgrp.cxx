/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: xmloff_ximpgrp.cxx,v $
 *
 *  $Revision: 1.3 $
 *
 *  last change: $Author: rt $ $Date: 2005-09-09 09:01:32 $
 *
 *  The Contents of this file are made available subject to
 *  the terms of GNU Lesser General Public License Version 2.1.
 *
 *
 *    GNU Lesser General Public License Version 2.1
 *    =============================================
 *    Copyright 2005 by Sun Microsystems, Inc.
 *    901 San Antonio Road, Palo Alto, CA 94303, USA
 *
 *    This library is free software; you can redistribute it and/or
 *    modify it under the terms of the GNU Lesser General Public
 *    License version 2.1, as published by the Free Software Foundation.
 *
 *    This library is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *    Lesser General Public License for more details.
 *
 *    You should have received a copy of the GNU Lesser General Public
 *    License along with this library; if not, write to the Free Software
 *    Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 *    MA  02111-1307  USA
 *
 ************************************************************************/

#pragma hdrstop

#ifndef _XMLOFF_XMLNMSPE_HXX
#include"xmlnmspe.hxx"
#endif

#ifndef _XIMPGROUP_HXX
#include "ximpgrp.hxx"
#endif

// auto strip #ifndef _XMLOFF_XMLTOKEN_HXX
// auto strip #include "xmltoken.hxx"
// auto strip #endif

// auto strip #ifndef _XIMPSHAPE_HXX
// auto strip #include "ximpshap.hxx"
// auto strip #endif

#ifndef _XMLOFF_EVENTIMP_HXX
#include "eventimp.hxx"
#endif
namespace binfilter {

using namespace ::rtl;
using namespace ::com::sun::star;
using ::binfilter::xmloff::token::IsXMLToken;
using ::binfilter::xmloff::token::XML_EVENTS;
using ::binfilter::xmloff::token::XML_GLUE_POINT;

//////////////////////////////////////////////////////////////////////////////

TYPEINIT1( SdXMLGroupShapeContext, SvXMLImportContext );

SdXMLGroupShapeContext::SdXMLGroupShapeContext( 
    SvXMLImport& rImport,
    USHORT nPrfx, const OUString& rLocalName,
    const uno::Reference< xml::sax::XAttributeList>& xAttrList,
    uno::Reference< drawing::XShapes >& rShapes) 
:	SdXMLShapeContext( rImport, nPrfx, rLocalName, xAttrList, rShapes )
{
}

//////////////////////////////////////////////////////////////////////////////

SdXMLGroupShapeContext::~SdXMLGroupShapeContext()
{
}

//////////////////////////////////////////////////////////////////////////////

SvXMLImportContext* SdXMLGroupShapeContext::CreateChildContext( USHORT nPrefix,
    const OUString& rLocalName,
    const uno::Reference< xml::sax::XAttributeList>& xAttrList )
{
    SvXMLImportContext* pContext = 0L;
    
    if( nPrefix == XML_NAMESPACE_OFFICE && IsXMLToken( rLocalName, XML_EVENTS ) )
    {
        pContext = new SdXMLEventsContext( GetImport(), nPrefix, rLocalName, xAttrList, mxShape );
    }
    else if( nPrefix == XML_NAMESPACE_DRAW && IsXMLToken( rLocalName, XML_GLUE_POINT ) )
    {
        addGluePoint( xAttrList );
    }
    else
    {
        // call GroupChildContext function at common ShapeImport
        pContext = GetImport().GetShapeImport()->CreateGroupChildContext(
            GetImport(), nPrefix, rLocalName, xAttrList, mxChilds);
    }

    // call parent when no own context was created
    if(!pContext)
        pContext = SvXMLImportContext::CreateChildContext(
        nPrefix, rLocalName, xAttrList);

    return pContext;
}

//////////////////////////////////////////////////////////////////////////////

void SdXMLGroupShapeContext::StartElement(const uno::Reference< xml::sax::XAttributeList>& xAttrList)
{
    // create new group shape and add it to rShapes, use it
    // as base for the new group import
    AddShape( "com.sun.star.drawing.GroupShape" );

    if(mxShape.is())
    {
        SetStyle( false );

        mxChilds = uno::Reference< drawing::XShapes >::query( mxShape );
        if( mxChilds.is() )
            GetImport().GetShapeImport()->pushGroupForSorting( mxChilds );
    }

    GetImport().GetShapeImport()->finishShape( mxShape, mxAttrList, mxShapes );
}

//////////////////////////////////////////////////////////////////////////////

void SdXMLGroupShapeContext::EndElement()
{
    if( mxChilds.is() )
        GetImport().GetShapeImport()->popGroupAndSort();
}


}//end of namespace binfilter
