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

#include "oox/drawingml/textbody.hxx"
#include <com/sun/star/text/XText.hpp>
#include <com/sun/star/text/XTextCursor.hpp>
#include "oox/drawingml/textparagraph.hxx"

using ::rtl::OUString;
using namespace ::com::sun::star::uno;
using namespace ::com::sun::star::text;
using namespace ::com::sun::star::frame;

namespace oox { namespace drawingml {


TextBody::TextBody()
{
}

TextBody::TextBody( TextBodyPtr pBody )
{
    if( pBody.get() ) {
        maTextProperties = pBody->maTextProperties;
        maTextListStyle = pBody->maTextListStyle;
    }
}

TextBody::~TextBody()
{
}

TextParagraph& TextBody::addParagraph()
{
    TextParagraphPtr xPara( new TextParagraph );
    maParagraphs.push_back( xPara );
    return *xPara;
}

void TextBody::insertAt(
        const ::oox::core::XmlFilterBase& rFilterBase,
        const Reference < XText > & xText,
        const Reference < XTextCursor > & xAt,
        const TextCharacterProperties& rTextStyleProperties,
        const TextListStylePtr& pMasterTextListStylePtr ) const
{
    TextListStyle aCombinedTextStyle;
    aCombinedTextStyle.apply( *pMasterTextListStylePtr );
    aCombinedTextStyle.apply( maTextListStyle );

    for( TextParagraphVector::const_iterator aBeg = maParagraphs.begin(), aIt = aBeg, aEnd = maParagraphs.end(); aIt != aEnd; ++aIt )
        (*aIt)->insertAt( rFilterBase, xText, xAt, rTextStyleProperties, aCombinedTextStyle, aIt == aBeg );
}


} }
