/*************************************************************************
 *
 *  $RCSfile: adjitem.hxx,v $
 *
 *  $Revision: 1.2 $
 *
 *  last change: $Author: mwu $ $Date: 2003-11-06 08:27:26 $
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
#ifndef _SVX_ADJITEM_HXX
#define _SVX_ADJITEM_HXX

// include ---------------------------------------------------------------

#ifndef _SFXENUMITEM_HXX //autogen
#include <svtools/eitem.hxx>
#endif
#ifndef _SVX_SVXENUM_HXX
#include <bf_svx/svxenum.hxx>
#endif

#ifndef _SVX_SVXIDS_HRC
#include <bf_svx/svxids.hrc>
#endif

#ifndef _EEITEM_HXX //autogen
#include <bf_svx/eeitem.hxx>
#endif

class SvXMLUnitConverter;
#ifdef _USE_NAMESPACE
namespace rtl
{
#endif
    class OUString;
#ifdef _USE_NAMESPACE
}
#endif
namespace binfilter {

// class SvxAdjustItem ---------------------------------------------------

/*
[Beschreibung]
Dieses Item beschreibt die Zeilenausrichtung.
*/
#define	ADJUST_LASTBLOCK_VERSION		((USHORT)0x0001)

class SvxAdjustItem : public SfxEnumItemInterface
{
    BOOL    bLeft      : 1;
    BOOL    bRight     : 1;
    BOOL    bCenter    : 1;
    BOOL    bBlock     : 1;

    // nur aktiv, wenn bBlock
    BOOL    bOneBlock : 1;
    BOOL    bLastCenter : 1;
    BOOL    bLastBlock : 1;

    friend SvStream& operator<<( SvStream&, SvxAdjustItem& ); //$ ostream
public:
    TYPEINFO();

    SvxAdjustItem( const SvxAdjust eAdjst = SVX_ADJUST_LEFT,
                   const USHORT nId = ITEMID_ADJUST );

    // "pure virtual Methoden" vom SfxPoolItem
    virtual int 			 operator==( const SfxPoolItem& ) const;

    virtual	sal_Bool        	 QueryValue( ::com::sun::star::uno::Any& rVal, BYTE nMemberId = 0 ) const;
    virtual	sal_Bool			 PutValue( const ::com::sun::star::uno::Any& rVal, BYTE nMemberId = 0 );

//STRIP001 	virtual SfxItemPresentation GetPresentation( SfxItemPresentation ePres,
//STRIP001 									SfxMapUnit eCoreMetric,
//STRIP001 									SfxMapUnit ePresMetric,
//STRIP001                                     String &rText, const IntlWrapper * = 0 ) const;
    virtual USHORT			 GetValueCount() const;
//STRIP001 	virtual String			 GetValueTextByPos( USHORT nPos ) const;
    virtual USHORT			 GetEnumValue() const;
    virtual void			 SetEnumValue( USHORT nNewVal );
    virtual SfxPoolItem*	 Clone( SfxItemPool *pPool = 0 ) const;
    virtual SfxPoolItem*	 Create(SvStream &, USHORT) const;
    virtual SvStream&		 Store(SvStream &, USHORT nItemVersion ) const;
    virtual USHORT			 GetVersion( USHORT nFileVersion ) const;

    inline void SetOneWord( const SvxAdjust eType )
    {
        bOneBlock  = eType == SVX_ADJUST_BLOCK;
    }

    inline void SetLastBlock( const SvxAdjust eType )
    {
        bLastBlock = eType == SVX_ADJUST_BLOCK;
        bLastCenter = eType == SVX_ADJUST_CENTER;
    }

    inline void SetAdjust( const SvxAdjust eType )
    {
        bLeft = eType == SVX_ADJUST_LEFT;
        bRight = eType == SVX_ADJUST_RIGHT;
        bCenter = eType == SVX_ADJUST_CENTER;
        bBlock = eType == SVX_ADJUST_BLOCK;
    }

    inline SvxAdjust GetLastBlock() const
    {
        SvxAdjust eRet = SVX_ADJUST_LEFT;

        if ( bLastBlock )
            eRet = SVX_ADJUST_BLOCK;
        else if( bLastCenter )
            eRet = SVX_ADJUST_CENTER;
        return eRet;
    }

    inline SvxAdjust GetOneWord() const
    {
        SvxAdjust eRet = SVX_ADJUST_LEFT;

        if ( bBlock && bOneBlock )
            eRet = SVX_ADJUST_BLOCK;
        return eRet;
    }

    inline SvxAdjust GetAdjust() const
    {
        SvxAdjust eRet = SVX_ADJUST_LEFT;

        if ( bRight )
            eRet = SVX_ADJUST_RIGHT;
        else if ( bCenter )
            eRet = SVX_ADJUST_CENTER;
        else if ( bBlock )
            eRet = SVX_ADJUST_BLOCK;
        return eRet;
    }
};

}//end of namespace binfilter
#endif

