/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: keepitem.hxx,v $
 *
 *  $Revision: 1.4 $
 *
 *  last change: $Author: vg $ $Date: 2006-06-02 12:26:18 $
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
#ifndef _SVX_KEEPITEM_HXX
#define _SVX_KEEPITEM_HXX

// include ---------------------------------------------------------------

#ifndef _SFXENUMITEM_HXX //autogen
#include <svtools/eitem.hxx>
#endif
#ifndef _SVX_SVXIDS_HRC
#include <bf_svx/svxids.hrc>
#endif

namespace rtl
{
    class OUString;
}
namespace binfilter {

// class SvxFmtKeepItem ------------------------------------------------

/*
[Beschreibung]
Dieses Item beschreibt eine logische Variable "Absaetze zusammenhalten?".
*/

class SvxFmtKeepItem : public SfxBoolItem
{
public:
    TYPEINFO();

    inline SvxFmtKeepItem( const BOOL bKeep = FALSE,
                           const USHORT nWhich = ITEMID_FMTKEEP );
    inline SvxFmtKeepItem& operator=( const SvxFmtKeepItem& rSplit );

    // "pure virtual Methoden" vom SfxPoolItem
    virtual SfxPoolItem*	Clone( SfxItemPool *pPool = 0 ) const;
    virtual SfxPoolItem*	Create( SvStream&, USHORT ) const;
    virtual SvStream&		Store( SvStream& , USHORT nItemVersion ) const;

//STRIP001 	virtual SfxItemPresentation GetPresentation( SfxItemPresentation ePres,
//STRIP001 									SfxMapUnit eCoreMetric,
//STRIP001 									SfxMapUnit ePresMetric,
//STRIP001                                     String &rText, const IntlWrapper * = 0 ) const;
};

inline SvxFmtKeepItem::SvxFmtKeepItem( const BOOL bKeep, const USHORT nWhich ) :
    SfxBoolItem( nWhich, bKeep )
{}

inline SvxFmtKeepItem& SvxFmtKeepItem::operator=( const SvxFmtKeepItem& rKeep )
{
    SetValue( rKeep.GetValue() );
    return *this;
}

}//end of namespace binfilter
#endif

