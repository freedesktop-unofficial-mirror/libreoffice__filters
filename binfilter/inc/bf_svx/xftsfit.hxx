/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: xftsfit.hxx,v $
 *
 *  $Revision: 1.3 $
 *
 *  last change: $Author: rt $ $Date: 2005-09-09 15:31:32 $
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
namespace binfilter {

#ifndef _SVX_XFTSFIT_HXX
#define _SVX_XFTSFIT_HXX

/*************************************************************************
|*
|* FormText-StdFormItem
|*
\************************************************************************/

class XFormTextStdFormItem : public SfxEnumItem
{
public:
                            TYPEINFO();
                            XFormTextStdFormItem(XFormTextStdForm = XFTFORM_NONE);
                            XFormTextStdFormItem(SvStream& rIn);
    virtual SfxPoolItem*    Clone(SfxItemPool* pPool = 0) const;
    virtual SfxPoolItem*    Create(SvStream& rIn, USHORT nVer) const;
    virtual USHORT          GetValueCount() const;
    XFormTextStdForm		GetValue() const { return (XFormTextStdForm) SfxEnumItem::GetValue(); }
    // #FontWork#
    virtual	sal_Bool        QueryValue( ::com::sun::star::uno::Any& rVal, BYTE nMemberId = 0 ) const;
    virtual	sal_Bool		PutValue( const ::com::sun::star::uno::Any& rVal, BYTE nMemberId = 0 );
};

}//end of namespace binfilter
#endif

