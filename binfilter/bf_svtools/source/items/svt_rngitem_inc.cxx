/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: svt_rngitem_inc.cxx,v $
 *
 *  $Revision: 1.2 $
 *
 *  last change: $Author: rt $ $Date: 2008-03-12 08:48:25 $
 *
 *  The Contents of this file are made available subject to
 *  the terms of GNU Lesser General Public License Version 2.1.
 *
 *
 *    GNU Lesser General Public License Version 2.1
 *    =============================================
 *    Copyright 2005 by Sun Microsystems, Inc.
 *    901 San Antonio Road, Palo Alto, CA 94303, USA
 *
 *    This library is free software; you can redistribute it and/or
 *    modify it under the terms of the GNU Lesser General Public
 *    License version 2.1, as published by the Free Software Foundation.
 *
 *    This library is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *    Lesser General Public License for more details.
 *
 *    You should have received a copy of the GNU Lesser General Public
 *    License along with this library; if not, write to the Free Software
 *    Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 *    MA  02111-1307  USA
 *
 ************************************************************************/

namespace binfilter
{

// This snippet of code is included by rngitem.cxx but not compiled directly.
// Ugly hack, probably due to lack of templates in the 20th century.

static inline NUMTYPE Count_Impl(const NUMTYPE * pRanges)
{
    NUMTYPE nCount = 0;
    for (; *pRanges; pRanges += 2) nCount += 2;
    return nCount;
}

// -----------------------------------------------------------------------

TYPEINIT1_AUTOFACTORY(SfxXRangeItem, SfxPoolItem);
TYPEINIT1_AUTOFACTORY(SfxXRangesItem, SfxPoolItem);

NUMTYPE Count_Impl( const NUMTYPE *pRanges );

// -----------------------------------------------------------------------

SfxXRangeItem::SfxXRangeItem()
{
    nFrom = 0;
    nTo = 0;
}

// -----------------------------------------------------------------------

SfxXRangeItem::SfxXRangeItem( USHORT which, NUMTYPE from, NUMTYPE to ):
    SfxPoolItem( which ),
    nFrom( from ),
    nTo( to )
{
}


// -----------------------------------------------------------------------

SfxXRangeItem::SfxXRangeItem( USHORT nW, SvStream &rStream ) :
    SfxPoolItem( nW )
{
    rStream >> nFrom;
    rStream >> nTo;
}

// -----------------------------------------------------------------------

SfxXRangeItem::SfxXRangeItem( const SfxXRangeItem& rItem ) :
    SfxPoolItem( rItem )
{
    nFrom = rItem.nFrom;
    nTo = rItem.nTo;
}

// -----------------------------------------------------------------------

SfxItemPresentation SfxXRangeItem::GetPresentation
(
    SfxItemPresentation 	/*ePresentation*/,
    SfxMapUnit				/*eCoreMetric*/,
    SfxMapUnit				/*ePresentationMetric*/,
    XubString& 				rText,
    const ::IntlWrapper *
)	const
{
    rText = UniString::CreateFromInt64(nFrom);
    rText += ':';
    rText += UniString::CreateFromInt64(nTo);
    return SFX_ITEM_PRESENTATION_NAMELESS;
}

// -----------------------------------------------------------------------

int SfxXRangeItem::operator==( const SfxPoolItem& rItem ) const
{
    DBG_ASSERT( SfxPoolItem::operator==( rItem ), "unequal type" );
    SfxXRangeItem* pT = (SfxXRangeItem*)&rItem;
    if( nFrom==pT->nFrom && nTo==pT->nTo )
        return 1;
    return 0;
}

// -----------------------------------------------------------------------

SfxPoolItem* SfxXRangeItem::Clone(SfxItemPool *) const
{
    return new SfxXRangeItem( Which(), nFrom, nTo );
}

// -----------------------------------------------------------------------

SfxPoolItem* SfxXRangeItem::Create(SvStream &rStream, USHORT) const
{
    NUMTYPE		nVon, nBis;
    rStream >> nVon;
    rStream >> nBis;
    return new SfxXRangeItem( Which(), nVon, nBis );
}

// -----------------------------------------------------------------------

SvStream& SfxXRangeItem::Store(SvStream &rStream, USHORT) const
{
    rStream << nFrom;
    rStream << nTo;
    return rStream;
}

//=========================================================================

SfxXRangesItem::SfxXRangesItem()
:	_pRanges(0)
{
}

//-------------------------------------------------------------------------

SfxXRangesItem::SfxXRangesItem( USHORT nWID, const NUMTYPE *pRanges )
:	SfxPoolItem( nWID )
{
    NUMTYPE nCount = Count_Impl(pRanges) + 1;
    _pRanges = new NUMTYPE[nCount];
    memcpy( _pRanges, pRanges, sizeof(NUMTYPE) * nCount );
}

//-------------------------------------------------------------------------

SfxXRangesItem::SfxXRangesItem( USHORT nWID, SvStream &rStream )
:	SfxPoolItem( nWID )
{
    NUMTYPE nCount;
    rStream >> nCount;
    _pRanges = new NUMTYPE[nCount + 1];
    for ( NUMTYPE n = 0; n < nCount; ++n )
        rStream >> _pRanges[n];
    _pRanges[nCount] = 0;
}

//-------------------------------------------------------------------------

SfxXRangesItem::SfxXRangesItem( const SfxXRangesItem& rItem )
:	SfxPoolItem( rItem )
{
    NUMTYPE nCount = Count_Impl(rItem._pRanges) + 1;
    _pRanges = new NUMTYPE[nCount];
    memcpy( _pRanges, rItem._pRanges, sizeof(NUMTYPE) * nCount );
}

//-------------------------------------------------------------------------

SfxXRangesItem::~SfxXRangesItem()
{
    delete _pRanges;
}

//-------------------------------------------------------------------------

int SfxXRangesItem::operator==( const SfxPoolItem &rItem ) const
{
    const SfxXRangesItem &rOther = (const SfxXRangesItem&) rItem;
    if ( !_pRanges && !rOther._pRanges )
        return TRUE;
    if ( _pRanges || rOther._pRanges )
        return FALSE;

    NUMTYPE n;
    for ( n = 0; _pRanges[n] && rOther._pRanges[n]; ++n )
        if ( *_pRanges != rOther._pRanges[n] )
            return 0;

    return !_pRanges[n] && !rOther._pRanges[n];
}

//-------------------------------------------------------------------------

SfxItemPresentation SfxXRangesItem::GetPresentation( SfxItemPresentation /*ePres*/,
                                    SfxMapUnit /*eCoreMetric*/,
                                    SfxMapUnit /*ePresMetric*/,
                                    XubString &/*rText*/,
                                    const ::IntlWrapper * ) const
{
    HACK(n. i.)
    return SFX_ITEM_PRESENTATION_NONE;
}

//-------------------------------------------------------------------------

SfxPoolItem* SfxXRangesItem::Clone( SfxItemPool * ) const
{
    return new SfxXRangesItem( *this );
}

//-------------------------------------------------------------------------

SfxPoolItem* SfxXRangesItem::Create( SvStream &rStream, USHORT ) const
{
    return new SfxXRangesItem( Which(), rStream );
}

//-------------------------------------------------------------------------

SvStream& SfxXRangesItem::Store( SvStream &rStream, USHORT ) const
{
    NUMTYPE nCount = Count_Impl( _pRanges );
    rStream >> nCount;
    for ( NUMTYPE n = 0; _pRanges[n]; ++n )
        rStream >> _pRanges[n];
    return rStream;
}


#undef NUMTYPE
#undef SfxXRangeItem
#undef SfxXRangesItem
}
