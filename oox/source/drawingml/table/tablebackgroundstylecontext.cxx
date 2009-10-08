/*************************************************************************
 *
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER.
 *
 * Copyright 2008 by Sun Microsystems, Inc.
 *
 * OpenOffice.org - a multi-platform office productivity suite
 *
 * $RCSfile: tablebackgroundstylecontext.cxx,v $
 * $Revision: 1.3 $
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

#include <osl/diagnose.h>

#include "oox/drawingml/stylematrixreferencecontext.hxx"
#include "oox/drawingml/table/tablebackgroundstylecontext.hxx"
#include "oox/drawingml/fillpropertiesgroupcontext.hxx"
#include "oox/core/namespaces.hxx"
#include "oox/helper/attributelist.hxx"
#include "tokens.hxx"
using namespace ::oox::core;
using namespace ::com::sun::star;
using namespace ::com::sun::star::uno;
using namespace ::com::sun::star::xml::sax;
using ::rtl::OUString;

namespace oox { namespace drawingml { namespace table {

TableBackgroundStyleContext::TableBackgroundStyleContext( ContextHandler& rParent, TableStyle& rTableStyle )
: ContextHandler( rParent )
, mrTableStyle( rTableStyle )
{
}

TableBackgroundStyleContext::~TableBackgroundStyleContext()
{
}

uno::Reference< xml::sax::XFastContextHandler > SAL_CALL
TableBackgroundStyleContext::createFastChildContext( ::sal_Int32 aElementToken, const uno::Reference< xml::sax::XFastAttributeList >& xAttribs )
    throw ( xml::sax::SAXException, uno::RuntimeException)
{
    uno::Reference< xml::sax::XFastContextHandler > xRet;

    AttributeList aAttribs( xAttribs );
    switch( aElementToken )
    {
        // EG_ThemeableFillStyle (choice)
        case NMSP_DRAWINGML|XML_fill:		// CT_FillProperties
            {
                boost::shared_ptr< oox::drawingml::FillProperties >& rFillProperties( mrTableStyle.getBackgroundFillProperties() );
                rFillProperties = boost::shared_ptr< oox::drawingml::FillProperties > ( new oox::drawingml::FillProperties() );
                xRet.set( new oox::drawingml::FillPropertiesContext( *this, *rFillProperties.get() ) );
            }
            break;
        case NMSP_DRAWINGML|XML_fillRef:	// CT_StyleMatrixReference
            {
                ShapeStyleRef& rStyleRef = mrTableStyle.getBackgroundFillStyleRef();
                rStyleRef.mnThemedIdx = aAttribs.getInteger( XML_idx, 0 );
                xRet.set( new StyleMatrixReferenceContext( *this, rStyleRef.maPhClr ) );
            }
            break;

        // EG_ThemeableEffectStyle (choice)
        case NMSP_DRAWINGML|XML_effect:		// CT_EffectProperties
            break;
        case NMSP_DRAWINGML|XML_effectRef:	// CT_StyleMatrixReference
            break;
    }
    if( !xRet.is() )
    {
        uno::Reference<XFastContextHandler> xTmp(this);
        xRet.set( xTmp );
    }
    return xRet;
}

} } }
