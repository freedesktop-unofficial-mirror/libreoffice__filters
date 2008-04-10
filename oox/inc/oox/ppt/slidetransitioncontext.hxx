/*************************************************************************
 *
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER.
 * 
 * Copyright 2008 by Sun Microsystems, Inc.
 *
 * OpenOffice.org - a multi-platform office productivity suite
 *
 * $RCSfile: slidetransitioncontext.hxx,v $
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

#ifndef OOX_PPT_SLIDETRANSITIONCONTEXT
#define OOX_PPT_SLIDETRANSITIONCONTEXT

#include "oox/core/contexthandler.hxx"
#include "oox/ppt/slidetransition.hxx"

namespace oox { class PropertyMap; }

namespace oox { namespace ppt {

    class SlideTransitionContext : public ::oox::core::ContextHandler
    {
    public:
        SlideTransitionContext( ::oox::core::ContextHandler& rParent,
            const ::com::sun::star::uno::Reference< ::com::sun::star::xml::sax::XFastAttributeList >& xAttributes,
            PropertyMap & aProperties ) throw();
        virtual ~SlideTransitionContext() throw();

    virtual void SAL_CALL endFastElement( sal_Int32 aElement ) throw (::com::sun::star::xml::sax::SAXException, ::com::sun::star::uno::RuntimeException);
    virtual ::com::sun::star::uno::Reference< ::com::sun::star::xml::sax::XFastContextHandler > SAL_CALL
        createFastChildContext( ::sal_Int32 Element,
            const ::com::sun::star::uno::Reference< ::com::sun::star::xml::sax::XFastAttributeList >& Attribs )
            throw (::com::sun::star::xml::sax::SAXException, ::com::sun::star::uno::RuntimeException);

    private:
        PropertyMap&                    maSlideProperties;
        ::sal_Bool                      mbHasTransition;
        SlideTransition                 maTransition;
    };

} }

#endif // OOX_PPT_SLIDEFRAGMENTHANDLER
