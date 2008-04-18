/*************************************************************************
 *
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER.
 * 
 * Copyright 2008 by Sun Microsystems, Inc.
 *
 * OpenOffice.org - a multi-platform office productivity suite
 *
 * $RCSfile: textfieldcontext.cxx,v $
 * $Revision: 1.5 $
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

#include <rtl/ustring.hxx>

#include "oox/drawingml/textparagraphpropertiescontext.hxx"
#include "oox/drawingml/textcharacterpropertiescontext.hxx"
#include "oox/drawingml/textfieldcontext.hxx"
#include "oox/core/namespaces.hxx"
#include "tokens.hxx"

using ::rtl::OUString;
using namespace ::oox::core;
using namespace ::com::sun::star::uno;
using namespace ::com::sun::star::xml::sax;

namespace oox { namespace drawingml {

    TextFieldContext::TextFieldContext( ContextHandler& rParent,
                const Reference< XFastAttributeList >& rXAttributes,
                const TextFieldPtr & pTextField)
        : ContextHandler( rParent )
            ,	mpTextField( pTextField )
            , mbIsInText( false )
    {
        try {
            pTextField->setUuid( rXAttributes->getValue( XML_id ) );
        }
        catch(...)
        {

        }
        pTextField->setType( rXAttributes->getOptionalValue( XML_type ) );
    }

    void TextFieldContext::endFastElement( sal_Int32 aElementToken ) throw (SAXException, RuntimeException)
    {
        if( aElementToken == (NMSP_DRAWINGML|XML_t) )
        {
            mbIsInText = false;
        }
    }

    void TextFieldContext::characters( const OUString& aChars ) throw (SAXException, RuntimeException)
    {
        if( mbIsInText )
        {
            mpTextField->getText() += aChars;
        }
    }

    Reference< XFastContextHandler > TextFieldContext::createFastChildContext( sal_Int32 aElementToken,
                                                                                                                                                         const Reference< XFastAttributeList >& xAttribs )
        throw (SAXException, RuntimeException)
    {
        Reference< XFastContextHandler > xRet;
        switch( aElementToken )
        {
        case NMSP_DRAWINGML|XML_rPr:
            xRet.set( new TextCharacterPropertiesContext( *this, xAttribs, *mpTextField->getTextCharacterProperties() ) );
            break;
        case NMSP_DRAWINGML|XML_pPr:
            xRet.set( new TextParagraphPropertiesContext( *this, xAttribs, *mpTextField->getTextParagraphProperties() ) );
            break;
        case NMSP_DRAWINGML|XML_t:
            mbIsInText = true;
            break;
        }
        if ( !xRet.is() )
            xRet.set( this );
        return xRet;
    }


} }
