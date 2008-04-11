/*************************************************************************
 *
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER.
 * 
 * Copyright 2008 by Sun Microsystems, Inc.
 *
 * OpenOffice.org - a multi-platform office productivity suite
 *
 * $RCSfile: xlineit0.hxx,v $
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

#ifndef _SVX_XLINEIT0_HXX
#define _SVX_XLINEIT0_HXX

#ifndef _XENUM_HXX //autogen
#include <bf_svx/xenum.hxx>
#endif
#ifndef _SFXENUMITEM_HXX //autogen
#include <bf_svtools/eitem.hxx>
#endif
namespace binfilter {
//---------------------
// class LineStyleItem
//---------------------

class XLineStyleItem : public SfxEnumItem
{
public:
                            TYPEINFO();
                            XLineStyleItem(XLineStyle = XLINE_SOLID);
                            XLineStyleItem(SvStream& rIn);
    virtual SfxPoolItem*    Clone(SfxItemPool* pPool = 0) const;
    virtual SfxPoolItem*    Create(SvStream& rIn, USHORT nVer) const;

    virtual	sal_Bool        	 QueryValue( ::com::sun::star::uno::Any& rVal, BYTE nMemberId = 0 ) const;
    virtual	sal_Bool			 PutValue( const ::com::sun::star::uno::Any& rVal, BYTE nMemberId = 0 );

    virtual USHORT          GetValueCount() const;
    XLineStyle				GetValue() const { return (XLineStyle) SfxEnumItem::GetValue(); }
};

}//end of namespace binfilter
#endif

