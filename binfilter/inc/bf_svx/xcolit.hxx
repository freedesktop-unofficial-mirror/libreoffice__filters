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

#ifndef _SVX_XCOLORITEM_HXX
#define _SVX_XCOLORITEM_HXX

#ifndef _COLOR_HXX //autogen
#include <tools/color.hxx>
#endif

#include <bf_svx/xit.hxx>
namespace binfilter {

class XColorTable;

//-----------------
// class XColorItem
//-----------------
class XColorItem : public NameOrIndex
{
    Color   aColor;

public:
            TYPEINFO();
            XColorItem() {}
    virtual	sal_Bool        	 QueryValue( ::com::sun::star::uno::Any& rVal, BYTE nMemberId = 0 ) const;
    virtual	sal_Bool			 PutValue( const ::com::sun::star::uno::Any& rVal, BYTE nMemberId = 0 );

            XColorItem(USHORT nWhich, const String& rName, const Color& rTheColor);
            XColorItem(USHORT nWhich, SvStream& rIn);
            XColorItem(const XColorItem& rItem);

    virtual int             operator==(const SfxPoolItem& rItem) const;
    virtual SfxPoolItem*    Clone(SfxItemPool* pPool = 0) const;
    virtual SfxPoolItem*    Create(SvStream& rIn, USHORT nVer) const;
    virtual SvStream&       Store(SvStream& rOut, USHORT nItemVersion ) const;

    const Color&    GetValue(const XColorTable* pTable = 0) const;
    void            SetValue(const Color& rNew) { aColor = rNew; Detach(); }
};

}//end of namespace binfilter
#endif

