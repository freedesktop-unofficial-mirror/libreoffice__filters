/*************************************************************************
 *
 *  $RCSfile: fwdtitem.hxx,v $
 *
 *  $Revision: 1.2 $
 *
 *  last change: $Author: mwu $ $Date: 2003-11-06 08:27:51 $
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
#ifndef _SVX_FWDTITEM_HXX
#define _SVX_FWDTITEM_HXX

// include ---------------------------------------------------------------

#ifndef _SFXPOOLITEM_HXX //autogen
#include <svtools/poolitem.hxx>
#endif
#ifndef   ITEMID_FONTWIDTH
#define   ITEMID_FONTWIDTH 0
#endif
namespace binfilter {

// class SvxFontWidthItem -----------------------------------------------

/*	[Beschreibung]

    Dieses Item beschreibt die Font-Breite.
*/

class SvxFontWidthItem : public SfxPoolItem
{
    UINT16	nWidth;			// 0 = default
    USHORT	nProp;			// default 100%
public:
//STRIP001 	TYPEINFO();

    SvxFontWidthItem(	const USHORT nSz = 0,
                        const USHORT nPropWidth = 100,
                        const USHORT nId = ITEMID_FONTWIDTH );

//STRIP001 	// "pure virtual Methoden" vom SfxPoolItem
//STRIP001 	virtual int 			 operator==( const SfxPoolItem& ) const;
//STRIP001 	virtual	sal_Bool        	 QueryValue( ::com::sun::star::uno::Any& rVal, BYTE nMemberId = 0 ) const;
//STRIP001 	virtual	sal_Bool			 PutValue( const ::com::sun::star::uno::Any& rVal, BYTE nMemberId = 0 );
//STRIP001 
//STRIP001 	virtual SfxItemPresentation GetPresentation( SfxItemPresentation ePres,
//STRIP001 									SfxMapUnit eCoreMetric,
//STRIP001 									SfxMapUnit ePresMetric,
//STRIP001                                     String &rText, const IntlWrapper * = 0 ) const;
//STRIP001 
//STRIP001 	virtual SfxPoolItem*	 Clone( SfxItemPool *pPool = 0 ) const;
//STRIP001 	virtual SfxPoolItem*     Create(SvStream &, USHORT) const;
//STRIP001 	virtual SvStream&		 Store(SvStream &, USHORT nItemVersion) const;
//STRIP001 	virtual int				 ScaleMetrics( long nMult, long nDiv );
//STRIP001 	virtual	int				 HasMetrics() const;
//STRIP001 
//STRIP001 	inline SvxFontWidthItem& operator=(const SvxFontWidthItem& rItem )
//STRIP001 		{
//STRIP001 			SetWidthValue( rItem.GetWidth() );
//STRIP001 			SetProp( rItem.GetProp() );
//STRIP001 			return *this;
//STRIP001 		}
//STRIP001 
//STRIP001 	void SetWidth( UINT16 nNewWidth, const USHORT nNewProp = 100 )
//STRIP001 		{
//STRIP001 			DBG_ASSERT( GetRefCount() == 0, "SetValue() with pooled item" );
//STRIP001 			nWidth = UINT16(( (UINT32)nNewWidth * nNewProp ) / 100 );
//STRIP001 			nProp = nNewProp;
//STRIP001 		}

    UINT16 GetWidth() const { return nWidth; }

//STRIP001 	void SetWidthValue( UINT16 nNewWidth )
//STRIP001 		{
//STRIP001 			DBG_ASSERT( GetRefCount() == 0, "SetValue() with pooled item" );
//STRIP001 			nWidth = nNewWidth;
//STRIP001 		}
//STRIP001 
//STRIP001 	void SetProp( const USHORT nNewProp )
//STRIP001 		{
//STRIP001 			DBG_ASSERT( GetRefCount() == 0, "SetValue() with pooled item" );
//STRIP001 			nProp = nNewProp;
//STRIP001 		}
//STRIP001 
//STRIP001 	USHORT GetProp() const { return nProp; }
};

}//end of namespace binfilter
#endif

