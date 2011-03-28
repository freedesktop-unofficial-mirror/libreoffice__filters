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

#include "oox/xls/sharedstringsbuffer.hxx"

#include "oox/xls/biffinputstream.hxx"

namespace oox {
namespace xls {

// ============================================================================

using namespace ::com::sun::star::text;
using namespace ::com::sun::star::uno;

// ============================================================================

SharedStringsBuffer::SharedStringsBuffer( const WorkbookHelper& rHelper ) :
     WorkbookHelper( rHelper )
{
}

RichStringRef SharedStringsBuffer::createRichString()
{
    RichStringRef xString( new RichString( *this ) );
    maStrings.push_back( xString );
    return xString;
}

void SharedStringsBuffer::importSst( BiffInputStream& rStrm )
{
    rStrm.skip( 4 );
    sal_Int32 nStringCount = rStrm.readInt32();
    if( nStringCount > 0 )
    {
        maStrings.clear();
        maStrings.reserve( static_cast< size_t >( nStringCount ) );
        for( ; !rStrm.isEof() && (nStringCount > 0); --nStringCount )
        {
            RichStringRef xString( new RichString( *this ) );
            maStrings.push_back( xString );
            xString->importUniString( rStrm );
        }
    }
}

void SharedStringsBuffer::finalizeImport()
{
    maStrings.forEachMem( &RichString::finalizeImport );
}

RichStringRef SharedStringsBuffer::getString( sal_Int32 nStringId ) const
{
    return maStrings.get( nStringId );
}

// ============================================================================

} // namespace xls
} // namespace oox
