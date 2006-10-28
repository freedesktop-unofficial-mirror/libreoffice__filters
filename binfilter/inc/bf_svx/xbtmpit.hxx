/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: xbtmpit.hxx,v $
 *
 *  $Revision: 1.4 $
 *
 *  last change: $Author: rt $ $Date: 2006-10-28 04:24:50 $
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

#ifndef _SVX_XBTMPIT_HXX
#define _SVX_XBTMPIT_HXX

#include <bf_svx/xbitmap.hxx>
namespace binfilter {

class SdrModel;

//----------------------
// class XFillBitmapItem
//----------------------
class XFillBitmapItem : public NameOrIndex
{
    XOBitmap aXOBitmap;

public:
            TYPEINFO();
            XFillBitmapItem() : NameOrIndex(XATTR_FILLBITMAP, -1 ) {}
            XFillBitmapItem( long nIndex, const XOBitmap& rTheBitmap );
            XFillBitmapItem( const String& rName, const XOBitmap& rTheBitmap );
            XFillBitmapItem( SfxItemPool* pPool, const XOBitmap& rTheBitmap );
            XFillBitmapItem( SfxItemPool* pPool );
            XFillBitmapItem( const XFillBitmapItem& rItem );
            XFillBitmapItem( SvStream& rIn, USHORT nVer = 0 );

    virtual int             operator==( const SfxPoolItem& rItem ) const;
    virtual SfxPoolItem*    Clone( SfxItemPool* pPool = 0 ) const;
    virtual SfxPoolItem*    Create( SvStream& rIn, USHORT nVer ) const;
    virtual SvStream&       Store( SvStream& rOut, USHORT nItemVersion  ) const;
    virtual USHORT          GetVersion( USHORT nFileFormatVersion ) const;

    virtual	sal_Bool        	 QueryValue( ::com::sun::star::uno::Any& rVal, BYTE nMemberId = 0 ) const;
    virtual	sal_Bool			 PutValue( const ::com::sun::star::uno::Any& rVal, BYTE nMemberId = 0 );


    const XOBitmap& GetValue( const XBitmapTable* pTable = 0 ) const;
    void           SetValue( const XOBitmap& rNew )  { aXOBitmap = rNew; Detach(); }

    static BOOL CompareValueFunc( const NameOrIndex* p1, const NameOrIndex* p2 );
    XFillBitmapItem* checkForUniqueItem( SdrModel* pModel ) const;
};

}//end of namespace binfilter
#endif
