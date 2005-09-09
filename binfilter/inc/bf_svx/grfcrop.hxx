/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: grfcrop.hxx,v $
 *
 *  $Revision: 1.3 $
 *
 *  last change: $Author: rt $ $Date: 2005-09-09 13:35:34 $
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
#ifndef _SVX_GRFCROP_HXX
#define _SVX_GRFCROP_HXX

#ifndef _SFXPOOLITEM_HXX
#include <svtools/poolitem.hxx>
#endif
namespace binfilter {

#define GRFCROP_VERSION_SWDEFAULT		0
#define GRFCROP_VERSION_MOVETOSVX 		1

class SvxGrfCrop : public SfxPoolItem
{
    sal_Int32	nLeft, nRight, nTop, nBottom;
public:
//	TYPEINFO();

    SvxGrfCrop( USHORT = ITEMID_GRF_CROP );
    SvxGrfCrop( sal_Int32 nLeft,	sal_Int32 nRight,
                sal_Int32 nTop,		sal_Int32 nBottom,
                USHORT = ITEMID_GRF_CROP );
    virtual ~SvxGrfCrop();

    // "pure virtual Methoden" vom SfxPoolItem
    virtual int            		operator==( const SfxPoolItem& ) const;
// must be implement by the specific items
//	virtual SfxPoolItem*		Clone( SfxItemPool *pPool = 0 ) const;
//	virtual USHORT			 	GetVersion( USHORT nFileVersion ) const;
    virtual SfxPoolItem*		Create(SvStream &, USHORT nVer) const;
    virtual SvStream&			Store(SvStream &, USHORT nIVer) const;
//STRIP001 	virtual SfxItemPresentation GetPresentation( SfxItemPresentation ePres,
//STRIP001 									SfxMapUnit eCoreMetric,
//STRIP001 									SfxMapUnit ePresMetric,
//STRIP001 									String &rText,
//STRIP001                                     const IntlWrapper* pIntl = 0 ) const;
    virtual	BOOL        	 QueryValue( ::com::sun::star::uno::Any& rVal,
                                        BYTE nMemberId = 0 ) const;
    virtual	BOOL			 PutValue( const ::com::sun::star::uno::Any& rVal,
                                        BYTE nMemberId = 0 );

    void SetLeft( sal_Int32 nVal )		{ nLeft = nVal; }
    void SetRight( sal_Int32 nVal )		{ nRight = nVal; }
    void SetTop( sal_Int32 nVal )		{ nTop = nVal; }
    void SetBottom( sal_Int32 nVal )	{ nBottom = nVal; }

    sal_Int32 GetLeft() const			{ return nLeft; }
    sal_Int32 GetRight() const 			{ return nRight; }
    sal_Int32 GetTop() const			{ return nTop; }
    sal_Int32 GetBottom() const			{ return nBottom; }

    inline SvxGrfCrop& operator=( const SvxGrfCrop& rCrop )
        {
            nLeft = rCrop.GetLeft(); 		nTop = rCrop.GetTop();
            nRight = rCrop.GetRight();		nBottom = rCrop.GetBottom();
            return *this;
        }
};

}//end of namespace binfilter
#endif  // _GRFATR_HXX
