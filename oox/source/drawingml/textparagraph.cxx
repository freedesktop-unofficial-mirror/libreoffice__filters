/*************************************************************************
 *
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER.
 * 
 * Copyright 2008 by Sun Microsystems, Inc.
 *
 * OpenOffice.org - a multi-platform office productivity suite
 *
 * $RCSfile: textparagraph.cxx,v $
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


#include <algorithm>
#include <boost/bind.hpp>

#include <rtl/ustring.hxx>
#include <com/sun/star/text/XText.hpp>
#include <com/sun/star/text/XTextCursor.hpp>
#include <com/sun/star/text/ControlCharacter.hpp>
#include <comphelper/processfactory.hxx>

#include "oox/drawingml/textparagraph.hxx"

using ::rtl::OUString;
using namespace ::com::sun::star::text;
using namespace ::com::sun::star::uno;
using namespace ::com::sun::star::beans;
using namespace ::com::sun::star::frame;

namespace oox { namespace drawingml {

    TextParagraph::TextParagraph()
        : mpProperties( new TextParagraphProperties( ) )
        , mpEndProperties( new TextParagraphProperties( ) )
    {
    }


    TextParagraph::~TextParagraph()
    {
    }


    void TextParagraph::insertAt(
            const ::oox::core::XmlFilterBase& rFilterBase,
            const Reference < XText > &xText,
            const Reference < XTextCursor > &xAt,
            const TextListStylePtr& rTextStyleList, bool bFirst)
    {
        try {
            sal_Int32 nParagraphSize = 0;
            Reference< XTextRange > xStart( xAt, UNO_QUERY );

            sal_Int16 nLevel = mpProperties->getLevel();
            std::vector< TextParagraphPropertiesPtr >& rListStyle = rTextStyleList->getListStyle();
            if ( nLevel >= static_cast< sal_Int16 >( rListStyle.size() ) )
                nLevel = 0;
            TextParagraphPropertiesPtr pTextParagraphStyle;
            TextCharacterPropertiesPtr pTextCharacterStyle;
            if ( rListStyle.size() )
                pTextParagraphStyle = rListStyle[ nLevel ];
            if ( pTextParagraphStyle.get() )
                pTextCharacterStyle = pTextParagraphStyle->getTextCharacterProperties();

            if( !bFirst )
            {
                xText->insertControlCharacter( xStart, ControlCharacter::APPEND_PARAGRAPH, sal_False );
                xAt->gotoEnd(true);
            }

            std::vector< TextRunPtr >::iterator begin( maRuns.begin() );
            while( begin != maRuns.end() )
            {
                (*begin)->insertAt( rFilterBase, xText, xAt, pTextCharacterStyle );
                nParagraphSize += (*begin++)->text().getLength();
            }
            xAt->gotoEnd(true);

            PropertyMap aioBulletList;
            Reference< XPropertySet > xProps( xStart, UNO_QUERY);
            if ( pTextParagraphStyle.get() )
                pTextParagraphStyle->pushToPropSet( rFilterBase, xProps, aioBulletList, sal_False );

            mpProperties->pushToPropSet( rFilterBase, xProps, aioBulletList, sal_True );

            // empty paragraphs do not have bullets in ppt
            if ( !nParagraphSize )
            {
                const rtl::OUString sIsNumbering( CREATE_OUSTRING( "IsNumbering" ) );
                xProps->setPropertyValue( sIsNumbering, Any( sal_False ) );
            }

// FIXME this is causing a lot of dispruption (ie does not work). I wonder what to do -- Hub
//			Reference< XTextRange > xEnd( xAt, UNO_QUERY );
//      Reference< XPropertySet > xProps2( xEnd, UNO_QUERY );
//			mpEndProperties->pushToPropSet( xProps2 );
        }
        catch( Exception & )
        {
            OSL_TRACE("OOX: exception in TextParagraph::insertAt");
        }
    }


} }

