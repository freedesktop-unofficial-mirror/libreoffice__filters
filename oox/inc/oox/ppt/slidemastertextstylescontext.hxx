/*************************************************************************
 *
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER.
 * 
 * Copyright 2008 by Sun Microsystems, Inc.
 *
 * OpenOffice.org - a multi-platform office productivity suite
 *
 * $RCSfile: slidemastertextstylescontext.hxx,v $
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

#ifndef OOX_DRAWINGML_SLIDEMASTERTEXTSTYLESCONTEXT_HXX
#define OOX_DRAWINGML_SLIDEMASTERTEXTSTYLESCONTEXT_HXX

#include "oox/drawingml/theme.hxx"
#include "oox/core/contexthandler.hxx"
#include "oox/core/fragmenthandler.hxx"
#include "oox/ppt/slidepersist.hxx"

namespace oox { namespace ppt {

class SlideMasterTextStylesContext : public oox::core::ContextHandler
{
public:
    SlideMasterTextStylesContext( ::oox::core::ContextHandler& rParent, SlidePersistPtr pSlidePersistPtr );
    ~SlideMasterTextStylesContext();
    virtual ::com::sun::star::uno::Reference< ::com::sun::star::xml::sax::XFastContextHandler > SAL_CALL createFastChildContext( ::sal_Int32 Element, const ::com::sun::star::uno::Reference< ::com::sun::star::xml::sax::XFastAttributeList >& Attribs ) throw (::com::sun::star::xml::sax::SAXException, ::com::sun::star::uno::RuntimeException);

protected:
    SlidePersistPtr     mpSlidePersistPtr;
};

} }

#endif  //  OOX_DRAWINGML_SLIDEMASTERTEXTSTYLESCONTEXT_HXX
