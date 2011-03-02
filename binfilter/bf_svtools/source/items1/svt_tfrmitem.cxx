/* -*- Mode: C++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */
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

// MARKER(update_precomp.py): autogen include statement, do not remove


#include <com/sun/star/uno/Any.hxx>

#include <tools/stream.hxx>
#include <tools/debug.hxx>
#include <tools/string.hxx>

#include <bf_svtools/tfrmitem.hxx>

namespace binfilter
{

DBG_NAME( SfxTargetFrameItem )
TYPEINIT1( SfxTargetFrameItem, SfxPoolItem );

// -----------------------------------------------------------------------

SfxTargetFrameItem::SfxTargetFrameItem( USHORT which ) :
    SfxPoolItem( which )
{
    DBG_CTOR( SfxTargetFrameItem, 0 );
}

// -----------------------------------------------------------------------

SfxTargetFrameItem::SfxTargetFrameItem( const SfxTargetFrameItem& rItem ) :
    SfxPoolItem( rItem )
{
    DBG_CTOR( SfxTargetFrameItem, 0 );
    for( USHORT nCur = 0; nCur <= (USHORT)SfxOpenModeLast; nCur++ )
        _aFrames[nCur] = rItem._aFrames[nCur];
}

// -----------------------------------------------------------------------

SfxTargetFrameItem::~SfxTargetFrameItem()
{
    DBG_DTOR(SfxTargetFrameItem, 0);
}

// -----------------------------------------------------------------------

int SfxTargetFrameItem::operator==( const SfxPoolItem& rItem ) const
{
    DBG_CHKTHIS( SfxTargetFrameItem, 0 );
    DBG_ASSERT( SfxPoolItem::operator==( rItem ), "unequal type" );

    for( USHORT nCur = 0; nCur <= (USHORT)SfxOpenModeLast; nCur++ )
    {
        if(	_aFrames[nCur] != ((const SfxTargetFrameItem&)rItem)._aFrames[nCur] )
            return 0;
    }
    return 1;
}

// -----------------------------------------------------------------------

SfxPoolItem* SfxTargetFrameItem::Create( SvStream& rStream, USHORT ) const
{
    DBG_CHKTHIS(SfxTargetFrameItem, 0);
    SfxTargetFrameItem* pItem = new SfxTargetFrameItem( Which() );
    USHORT nCount = 0;
    rStream >> nCount;
    for(USHORT nCur=0; nCur<= (USHORT)SfxOpenModeLast && nCount; nCur++,nCount--)
    {
        readByteString(rStream, pItem->_aFrames[ nCur ]);
    }
    // die uebriggebliebenen ueberspringen
    String aTemp;
    while( nCount )
    {
        readByteString(rStream, aTemp);
        nCount--;
    }
    return pItem;
}

// -----------------------------------------------------------------------

SvStream& SfxTargetFrameItem::Store( SvStream& rStream, USHORT ) const
{
    DBG_CHKTHIS( SfxTargetFrameItem, 0 );
    USHORT nCount = (USHORT)(SfxOpenModeLast+1);
    rStream << nCount;
    for( USHORT nCur = 0; nCur <= (USHORT)SfxOpenModeLast; nCur++ )
    {
        writeByteString(rStream, _aFrames[ nCur ]);
    }
    return rStream;
}

// -----------------------------------------------------------------------

SfxPoolItem* SfxTargetFrameItem::Clone( SfxItemPool* ) const
{
    DBG_CHKTHIS( SfxTargetFrameItem, 0 );
    return new SfxTargetFrameItem( *this );
}

// -----------------------------------------------------------------------
// virtual
bool SfxTargetFrameItem::QueryValue( com::sun::star::uno::Any& rVal,BYTE ) const
{
    String aVal;
    for ( int i = 0; i <= SfxOpenModeLast; i++ )
    {
        aVal += _aFrames[ i ];
        aVal += ';' ;
    }

    rVal <<= rtl::OUString( aVal );
    return true;
}

// -----------------------------------------------------------------------
// virtual
bool SfxTargetFrameItem::PutValue( const com::sun::star::uno::Any& rVal,BYTE )
{
    rtl::OUString aValue;
    if ( rVal >>= aValue )
    {
        const String aVal( aValue );

        for ( USHORT i = 0; i <= SfxOpenModeLast; i++ )
            _aFrames[ i ] = aVal.GetToken( i );

        return true;
    }

    OSL_FAIL( "SfxTargetFrameItem::PutValue - Wrong type!" );
    return false;
}

}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
