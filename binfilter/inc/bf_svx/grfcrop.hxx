/*************************************************************************
 *
 *  $RCSfile: grfcrop.hxx,v $
 *
 *  $Revision: 1.1.1.1 $
 *
 *  last change: $Author: hjs $ $Date: 2003-10-01 12:23:39 $
 *
 *  The Contents of this file are made available subject to the terms of
 *  either of the following licenses
 *
 *         - GNU Lesser General Public License Version 2.1
 *         - Sun Industry Standards Source License Version 1.1
 *
 *  Sun Microsystems Inc., October, 2000
 *
 *  GNU Lesser General Public License Version 2.1
 *  =============================================
 *  Copyright 2000 by Sun Microsystems, Inc.
 *  901 San Antonio Road, Palo Alto, CA 94303, USA
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public
 *  License version 2.1, as published by the Free Software Foundation.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public
 *  License along with this library; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 *  MA  02111-1307  USA
 *
 *
 *  Sun Industry Standards Source License Version 1.1
 *  =================================================
 *  The contents of this file are subject to the Sun Industry Standards
 *  Source License Version 1.1 (the "License"); You may not use this file
 *  except in compliance with the License. You may obtain a copy of the
 *  License at http://www.openoffice.org/license.html.
 *
 *  Software provided under this License is provided on an "AS IS" basis,
 *  WITHOUT WARRANTY OF ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING,
 *  WITHOUT LIMITATION, WARRANTIES THAT THE SOFTWARE IS FREE OF DEFECTS,
 *  MERCHANTABLE, FIT FOR A PARTICULAR PURPOSE, OR NON-INFRINGING.
 *  See the License for the specific provisions governing your rights and
 *  obligations concerning the Software.
 *
 *  The Initial Developer of the Original Code is: Sun Microsystems, Inc.
 *
 *  Copyright: 2000 by Sun Microsystems, Inc.
 *
 *  All Rights Reserved.
 *
 *  Contributor(s): _______________________________________
 *
 *
 ************************************************************************/
#ifndef _SVX_GRFCROP_HXX
#define _SVX_GRFCROP_HXX

#ifndef _SFXPOOLITEM_HXX
#include <svtools/poolitem.hxx>
#endif

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
    virtual	BOOL        	 QueryValue( com::sun::star::uno::Any& rVal,
                                        BYTE nMemberId = 0 ) const;
    virtual	BOOL			 PutValue( const com::sun::star::uno::Any& rVal,
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

#endif  // _GRFATR_HXX
