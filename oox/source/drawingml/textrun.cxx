/*************************************************************************
 *
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER.
 * 
 * Copyright 2008 by Sun Microsystems, Inc.
 *
 * OpenOffice.org - a multi-platform office productivity suite
 *
 * $RCSfile: textrun.cxx,v $
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

#include "oox/drawingml/textrun.hxx"

#include <rtl/ustring.hxx>

#include <com/sun/star/text/ControlCharacter.hpp>
#include <com/sun/star/beans/XMultiPropertySet.hpp>
#include <com/sun/star/lang/XMultiServiceFactory.hpp>
#include <com/sun/star/text/XTextField.hpp>

#include "oox/helper/helper.hxx"

using ::rtl::OUString;
using namespace ::com::sun::star::uno;
using namespace ::com::sun::star::text;
using namespace ::com::sun::star::beans;
using namespace ::com::sun::star::frame;
using namespace ::com::sun::star::lang;

namespace oox { namespace drawingml {

TextRun::TextRun()
    : mbIsLineBreak( false )
    , maTextCharacterPropertiesPtr( new TextCharacterProperties() )
{
}


TextRun::~TextRun()
{
}

void TextRun::insertAt(
        const ::oox::core::XmlFilterBase& rFilterBase,
        const Reference < XText > & xText,
        const Reference < XTextCursor > &xAt,
        const TextCharacterPropertiesPtr& rTextCharacterStyle )
{
    try {
        Reference< XTextRange > xStart( xAt, UNO_QUERY );

        Reference< XPropertySet > xProps( xStart, UNO_QUERY);
        if ( rTextCharacterStyle.get() )
            rTextCharacterStyle->pushToPropSet( rFilterBase, xProps );

        maTextCharacterPropertiesPtr->pushToPropSet( rFilterBase, xProps );

        if( maTextCharacterPropertiesPtr->getHyperlinkPropertyMap().empty() )
        {
            if( mbIsLineBreak )
            {
                OSL_TRACE( "OOX: TextRun::insertAt() insert line break" );
                xText->insertControlCharacter( xStart, ControlCharacter::LINE_BREAK, sal_False );
            }
            else
            {
                xText->insertString( xStart, getText(), sal_False );
            }
        }
        else
        {
            OSL_TRACE( "OOX: URL field" );
            Reference< XMultiServiceFactory > xFactory( rFilterBase.getModel(), UNO_QUERY );
            Reference< XTextField > xField( xFactory->createInstance( CREATE_OUSTRING( "com.sun.star.text.TextField.URL" ) ), UNO_QUERY );
            if( xField.is() )
            {
                const rtl::OUString sRepresentation( OUString::intern( RTL_CONSTASCII_USTRINGPARAM( "Representation" ) ) );
                maTextCharacterPropertiesPtr->getHyperlinkPropertyMap()[ sRepresentation ] <<= getText();

                Reference< XPropertySet > xFieldProps( xField, UNO_QUERY);
                maTextCharacterPropertiesPtr->pushToUrlFieldPropSet( xFieldProps );
                Reference< XTextContent > xContent( xField, UNO_QUERY);
                xText->insertTextContent( xStart, xContent, sal_False );
            }
            else
            {
                OSL_TRACE( "OOX: URL field couldn't be created" );
                xText->insertString( xStart, getText(), sal_False );
            }
        }
    }
    catch( const Exception&  )
    {
        OSL_TRACE("OOX:  TextRun::insertAt() exception");
    }
}


} }
