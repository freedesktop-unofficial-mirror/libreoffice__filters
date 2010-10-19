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

#include "oox/xls/richstringcontext.hxx"

#include "oox/xls/stylesfragment.hxx"

namespace oox {
namespace xls {

// ============================================================================

using ::oox::core::ContextHandlerRef;
using ::rtl::OUString;

// ============================================================================

ContextHandlerRef RichStringContext::onCreateContext( sal_Int32 nElement, const AttributeList& rAttribs )
{
    if( isRootElement() )
    {
        switch( nElement )
        {
            case XLS_TOKEN( t ):
                mxPortion = mxString->importText( rAttribs );
                return this;    // collect text in onCharacters()
            case XLS_TOKEN( r ):
                mxPortion = mxString->importRun( rAttribs );
                return this;
            case XLS_TOKEN( rPh ):
                mxPhonetic = mxString->importPhoneticRun( rAttribs );
                return this;
            case XLS_TOKEN( phoneticPr ):
                mxString->importPhoneticPr( rAttribs );
            break;
        }
    }
    else switch( getCurrentElement() )
    {
        case XLS_TOKEN( r ):
            switch( nElement )
            {
                case XLS_TOKEN( rPr ):
                    if( mxPortion.get() )
                        return new FontContext( *this, mxPortion->createFont() );
                break;

                case XLS_TOKEN( t ):
                    return this;    // collect portion text in onCharacters()
            }
        break;

        case XLS_TOKEN( rPh ):
            switch( nElement )
            {
                case XLS_TOKEN( t ):
                    return this;    // collect phonetic text in onCharacters()
            }
        break;
    }
    return 0;
}

void RichStringContext::onCharacters( const OUString& rChars )
{
    if( isCurrentElement( XLS_TOKEN( t ) ) ) switch( getParentElement() )
    {
        case XLS_TOKEN( rPh ):
            if( mxPhonetic.get() )
                mxPhonetic->setText( rChars );
        break;
        default:
            if( mxPortion.get() )
                mxPortion->setText( rChars );
    }
}

// ============================================================================

} // namespace xls
} // namespace oox
