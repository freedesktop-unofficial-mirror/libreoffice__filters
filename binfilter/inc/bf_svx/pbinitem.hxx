/* -*- Mode: C++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */
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
#ifndef _SVX_PBINITEM_HXX
#define _SVX_PBINITEM_HXX

// include ---------------------------------------------------------------

#include <bf_svtools/intitem.hxx>
#include <bf_svx/svxids.hrc>
namespace binfilter {

// define ----------------------------------------------------------------

#define PAPERBIN_PRINTER_SETTINGS	((BYTE)0xFF)

// class SvxPaperBinItem -------------------------------------------------

/*	[Beschreibung]

    Dieses Item beschreibt die Auswahl eines Papierschachts des Drucker.
*/

class SvxPaperBinItem : public SfxByteItem
{
public:
    TYPEINFO();

    inline SvxPaperBinItem( const USHORT nId = ITEMID_PAPERBIN,
                            const BYTE nTray = PAPERBIN_PRINTER_SETTINGS );
    inline SvxPaperBinItem &operator=( const SvxPaperBinItem &rCpy );

    // "pure virtual Methoden" vom SfxPoolItem
    virtual SfxPoolItem*    Clone( SfxItemPool *pPool = 0 ) const;
    virtual SfxPoolItem*    Create( SvStream &, USHORT ) const;
    virtual SvStream&		Store( SvStream &rStream, USHORT ) const { return rStream; }
};

inline SvxPaperBinItem::SvxPaperBinItem( const USHORT nId, const BYTE nT )
    : SfxByteItem( nId, nT )
{}

inline SvxPaperBinItem &SvxPaperBinItem::operator=(
    const SvxPaperBinItem &rCpy )
{
    SetValue( rCpy.GetValue() );
    return *this;
}

}//end of namespace binfilter
#endif

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
