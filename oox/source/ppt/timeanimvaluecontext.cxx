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

#include "timeanimvaluecontext.hxx"

#include "animvariantcontext.hxx"

using namespace ::oox::core;
using namespace ::com::sun::star::uno;
using namespace ::com::sun::star::xml::sax;

namespace oox { namespace ppt {

    TimeAnimValueListContext::TimeAnimValueListContext( ContextHandler& rParent,
                const Reference< XFastAttributeList >& /*xAttribs*/,
                TimeAnimationValueList & aTavList )
        : ContextHandler( rParent )
            , maTavList( aTavList )
            , mbInValue( false )
    {
    }


    TimeAnimValueListContext::~TimeAnimValueListContext( )
    {
    }


    void SAL_CALL TimeAnimValueListContext::endFastElement( sal_Int32 aElement )
        throw ( SAXException, RuntimeException)
    {
        if( aElement == PPT_TOKEN( tav ) )
        {
            mbInValue = false;
        }
    }


    Reference< XFastContextHandler > SAL_CALL TimeAnimValueListContext::createFastChildContext( ::sal_Int32 aElementToken,
                                                                                                                                                                                            const Reference< XFastAttributeList >& xAttribs )
        throw ( SAXException, RuntimeException )
    {
        Reference< XFastContextHandler > xRet;

        switch ( aElementToken )
        {
        case PPT_TOKEN( tav ):
        {
            mbInValue = true;
            TimeAnimationValue val;
            val.msFormula = xAttribs->getOptionalValue( XML_fmla );
            val.msTime =  xAttribs->getOptionalValue( XML_tm );
            maTavList.push_back( val );
            break;
        }
        case PPT_TOKEN( val ):
            if( mbInValue )
            {
                // CT_TLAnimVariant
                xRet.set( new AnimVariantContext( *this, aElementToken, maTavList.back().maValue ) );
            }
            break;
        default:
            break;
        }

        if( !xRet.is() )
            xRet.set( this );

        return xRet;
    }


} }
