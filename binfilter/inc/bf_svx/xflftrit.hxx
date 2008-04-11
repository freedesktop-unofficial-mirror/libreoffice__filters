/*************************************************************************
 *
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER.
 * 
 * Copyright 2008 by Sun Microsystems, Inc.
 *
 * OpenOffice.org - a multi-platform office productivity suite
 *
 * $RCSfile: xflftrit.hxx,v $
 * $Revision: 1.6 $
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

#ifndef _SVX_XFLFTRIT_HXX
#define _SVX_XFLFTRIT_HXX

#ifndef _SVX_XFLGRIT_HXX //autogen
#include <bf_svx/xflgrit.hxx>
#endif
namespace binfilter {

//-----------------------------------
// class XFillFloatTransparenceItem	-
//-----------------------------------

class XFillFloatTransparenceItem : public XFillGradientItem
{
private:

    long					nDummy1;
    long					nDummy2;
    BOOL					bEnabled;

public:
                            TYPEINFO();

                            XFillFloatTransparenceItem();
                            XFillFloatTransparenceItem(const String& rName, const XGradient& rGradient, BOOL bEnable = TRUE );
                            XFillFloatTransparenceItem(SfxItemPool* pPool, const XGradient& rTheGradient, BOOL bEnable = TRUE );
                            XFillFloatTransparenceItem( const XFillFloatTransparenceItem& rItem );
                            XFillFloatTransparenceItem( SvStream& rIn, USHORT nVer = 0 );

    virtual int             operator==( const SfxPoolItem& rItem ) const;
    virtual SfxPoolItem*    Clone( SfxItemPool* pPool = NULL ) const;
    virtual SfxPoolItem*    Create( SvStream& rIn, USHORT nVer ) const;
    virtual SvStream&       Store( SvStream& rOut, USHORT nItemVersion ) const;
    virtual USHORT          GetVersion( USHORT nFileFormatVersion ) const;
    virtual	sal_Bool        	 QueryValue( ::com::sun::star::uno::Any& rVal, BYTE nMemberId = 0 ) const;


    BOOL					IsEnabled() const { return bEnabled; }
    void					SetEnabled( BOOL bEnable ) { bEnabled = bEnable; }

    XFillFloatTransparenceItem* checkForUniqueItem( SdrModel* pModel ) const;
};

}//end of namespace binfilter
#endif
