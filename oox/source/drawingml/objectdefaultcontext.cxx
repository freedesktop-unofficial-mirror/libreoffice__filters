/*************************************************************************
 *
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER.
 * 
 * Copyright 2008 by Sun Microsystems, Inc.
 *
 * OpenOffice.org - a multi-platform office productivity suite
 *
 * $RCSfile: objectdefaultcontext.cxx,v $
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

#include "oox/drawingml/objectdefaultcontext.hxx"
#include "oox/drawingml/spdefcontext.hxx"
#include "oox/core/namespaces.hxx"
#include "tokens.hxx"

using rtl::OUString;
using namespace ::oox::core;
using namespace ::com::sun::star::uno;
using namespace ::com::sun::star::xml::sax;

namespace oox { namespace drawingml {

objectDefaultContext::objectDefaultContext( ContextHandler& rParent, Theme& rTheme )
: ContextHandler( rParent )
, mrTheme( rTheme )
{
}

Reference< XFastContextHandler > objectDefaultContext::createFastChildContext( sal_Int32 aElementToken, const Reference< XFastAttributeList >& /* xAttribs */ ) throw (SAXException, RuntimeException)
{
    Reference< XFastContextHandler > xRet;
    switch( aElementToken )
    {
        case NMSP_DRAWINGML|XML_spDef:
        {
            xRet.set( new spDefContext( *this, *mrTheme.getspDef() ) );
            break;
        }
        case NMSP_DRAWINGML|XML_lnDef:
        {
            xRet.set( new spDefContext( *this, *mrTheme.getlnDef() ) );
            break;
        }
        case NMSP_DRAWINGML|XML_txDef:
        {
            xRet.set( new spDefContext( *this, *mrTheme.gettxDef() ) );
            break;
        }
    }
    if( !xRet.is() )
        xRet.set( this );

    return xRet;
}

} }
