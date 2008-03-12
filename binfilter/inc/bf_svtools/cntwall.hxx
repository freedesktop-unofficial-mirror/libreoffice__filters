/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: cntwall.hxx,v $
 *
 *  $Revision: 1.2 $
 *
 *  last change: $Author: rt $ $Date: 2008-03-12 11:53:24 $
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
#ifndef _CNTWALL_HXX
#define _CNTWALL_HXX

#ifndef SHL_HXX
#include <tools/shl.hxx>
#endif
#ifndef _RTTI_HXX
#include <tools/rtti.hxx>
#endif
#ifndef _TOOLS_COLOR_HXX
#include <tools/color.hxx>
#endif

#ifndef _SFXPOOLITEM_HXX
#include <bf_svtools/poolitem.hxx>
#endif

class SvStream;

namespace binfilter {

class  CntWallpaperItem : public SfxPoolItem
{
private:
    UniString				_aURL;
    Color					_nColor;
    USHORT					_nStyle;

public:
                            TYPEINFO();

                            CntWallpaperItem( USHORT nWhich );
                            CntWallpaperItem( USHORT nWhich, SvStream& rStream, USHORT nVersion );
                            CntWallpaperItem( const CntWallpaperItem& rCpy );
                            ~CntWallpaperItem();

    virtual USHORT GetVersion(USHORT) const;

    virtual	int				operator==( const SfxPoolItem& ) const;
    virtual SfxPoolItem*	Create( SvStream&, USHORT nItemVersion ) const;
    virtual SvStream&		Store( SvStream&, USHORT nItemVersion ) const;
    virtual SfxPoolItem*	Clone( SfxItemPool* pPool = 0 ) const;

    virtual	BOOL 			QueryValue( ::com::sun::star::uno::Any& rVal,
                                         BYTE nMemberId = 0 ) const;
    virtual	BOOL 			PutValue  ( const ::com::sun::star::uno::Any& rVal,
                                         BYTE nMemberId = 0 );

    void					SetBitmapURL( const UniString& rURL ) { _aURL = rURL; }
    void					SetColor( Color nColor ) { _nColor = nColor; }
    void					SetStyle( USHORT nStyle ) { _nStyle = nStyle; }

    const UniString&		GetBitmapURL() const { return _aURL; }
    Color					GetColor() const { return _nColor; }
    USHORT					GetStyle() const { return _nStyle; }
};

}

////////////////////////////////////////////////////////////////////////////////

#endif // _CNTWALL_HXX

