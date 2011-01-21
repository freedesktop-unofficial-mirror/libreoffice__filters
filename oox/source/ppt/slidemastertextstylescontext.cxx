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

#include "oox/drawingml/textliststyle.hxx"
#include "oox/drawingml/textliststylecontext.hxx"
#include "oox/ppt/slidemastertextstylescontext.hxx"

using rtl::OUString;
using namespace ::oox::core;
using namespace ::com::sun::star::uno;
using namespace ::com::sun::star::xml::sax;

namespace oox { namespace ppt {

SlideMasterTextStylesContext::SlideMasterTextStylesContext( ContextHandler& rParent, SlidePersistPtr pSlidePersistPtr )
: ContextHandler( rParent )
, mpSlidePersistPtr( pSlidePersistPtr )
{
}

SlideMasterTextStylesContext::~SlideMasterTextStylesContext()
{
}

Reference< XFastContextHandler > SlideMasterTextStylesContext::createFastChildContext( sal_Int32 aElementToken, const Reference< XFastAttributeList >& /* xAttribs */ ) throw (SAXException, RuntimeException)
{
    oox::drawingml::TextListStylePtr aTextListStylePtr;
    Reference< XFastContextHandler > xRet;
    switch( aElementToken )
    {
        case PPT_TOKEN( titleStyle ):
        {
            aTextListStylePtr = mpSlidePersistPtr->getTitleTextStyle();
            break;
        }
        case PPT_TOKEN( bodyStyle ):
        {
            aTextListStylePtr = mpSlidePersistPtr->getBodyTextStyle();
            break;
        }
        case PPT_TOKEN( notesStyle ):
        {
            aTextListStylePtr = mpSlidePersistPtr->getNotesTextStyle();
            break;
        }
        case PPT_TOKEN( otherStyle ):
        {
            aTextListStylePtr = mpSlidePersistPtr->getOtherTextStyle();
            break;
        }
    }
    if ( aTextListStylePtr )			// sj: the master list style is the last instance of from where properties 
    {									// are obtained. i got some documents without having the textsize set at 
        for ( int i = 0; i < 9; i++ )	// any point, the master reference application is using 18pt then
            aTextListStylePtr->getListStyle()[ i ]->getTextCharacterProperties().moHeight = 1800;
        xRet.set( new oox::drawingml::TextListStyleContext( *this, *aTextListStylePtr ) );
    }
    if( !xRet.is() )
        xRet.set( this );

    return xRet;
}

} }
