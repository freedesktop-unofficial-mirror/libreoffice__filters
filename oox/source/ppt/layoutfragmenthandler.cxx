/*************************************************************************
 *
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER.
 * 
 * Copyright 2008 by Sun Microsystems, Inc.
 *
 * OpenOffice.org - a multi-platform office productivity suite
 *
 * $RCSfile: layoutfragmenthandler.cxx,v $
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

#include "comphelper/anytostring.hxx"
#include "cppuhelper/exc_hlp.hxx"

#include <com/sun/star/beans/XMultiPropertySet.hpp>
#include <com/sun/star/container/XNamed.hpp>

#include "oox/ppt/layoutfragmenthandler.hxx"
#include "oox/drawingml/shapegroupcontext.hxx"
#include "oox/core/namespaces.hxx"
#include "tokens.hxx"

using rtl::OUString;
using namespace ::com::sun::star;
using namespace ::oox::core;
using namespace ::oox::drawingml;
using namespace ::com::sun::star::uno;
using namespace ::com::sun::star::xml::sax;
using namespace ::com::sun::star::container;

namespace oox { namespace ppt {

// CT_SlideLayout

LayoutFragmentHandler::LayoutFragmentHandler( XmlFilterBase& rFilter, const OUString& rFragmentPath, SlidePersistPtr pMasterPersistPtr )
    throw()
: SlideFragmentHandler( rFilter, rFragmentPath, pMasterPersistPtr, Layout )
{
}

LayoutFragmentHandler::~LayoutFragmentHandler()
    throw()
{

}

Reference< XFastContextHandler > LayoutFragmentHandler::createFastChildContext( sal_Int32 aElementToken, const Reference< XFastAttributeList >& xAttribs )
    throw (SAXException, RuntimeException)
{
    Reference< XFastContextHandler > xRet = getFastContextHandler();
    switch( aElementToken )
    {
        case NMSP_PPT|XML_sldLayout:		// CT_SlideLayout
            mpSlidePersistPtr->setLayoutValueToken( xAttribs->getOptionalValueToken( XML_type, 0 ) );	// CT_SlideLayoutType
        break;
        default:
            xRet.set( SlideFragmentHandler::createFastChildContext( aElementToken, xAttribs ) );
    }
    return xRet;
}

void SAL_CALL LayoutFragmentHandler::endDocument()
    throw (::com::sun::star::xml::sax::SAXException, ::com::sun::star::uno::RuntimeException)
{
}

} }

