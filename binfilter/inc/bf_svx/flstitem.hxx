/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: flstitem.hxx,v $
 *
 *  $Revision: 1.5 $
 *
 *  last change: $Author: rt $ $Date: 2008-03-12 12:50:59 $
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
#ifndef _SVX_FLSTITEM_HXX
#define _SVX_FLSTITEM_HXX

// include ---------------------------------------------------------------

#ifndef _SFXPOOLITEM_HXX //autogen
#include <bf_svtools/poolitem.hxx>
#endif
#ifndef   ITEMID_FONTLIST
#define   ITEMID_FONTLIST 0
#endif
namespace binfilter {
class FontList;

// class SvxFontListItem -------------------------------------------------


/*
    [Beschreibung]

    Dieses Item dient als Transport-Medium fuer eine FontListe.
    Die Fontliste wird nicht kopiert und nicht geloescht!
*/

class SvxFontListItem : public SfxPoolItem
{
private:
    const FontList*         pFontList;

public:
    TYPEINFO();

    SvxFontListItem( const FontList* pFontLst,
                     const USHORT nId = ITEMID_FONTLIST );
    SvxFontListItem( const SvxFontListItem& rItem );

    virtual int				operator==( const SfxPoolItem& ) const;
    virtual SfxPoolItem*	Clone( SfxItemPool *pPool = 0 ) const;


    const FontList*			GetFontList() const { return pFontList; }
};

}//end of namespace binfilter
#endif

