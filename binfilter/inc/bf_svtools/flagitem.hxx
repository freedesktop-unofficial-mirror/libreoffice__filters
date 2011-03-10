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
#ifndef _SFXFLAGITEM_HXX
#define _SFXFLAGITEM_HXX

#include "bf_svtools/svtdllapi.h"

#include <bf_svtools/bf_solar.h>
#include <tools/rtti.hxx>
#include <bf_svtools/poolitem.hxx>

class SvStream;

namespace binfilter
{

extern USHORT nSfxFlagVal[16];

// -----------------------------------------------------------------------

DBG_NAMEEX_VISIBILITY(SfxFlagItem, )

class  SfxFlagItem: public SfxPoolItem
{
    USHORT					 nVal;

public:
                             TYPEINFO();

                             SfxFlagItem( USHORT nWhich = 0, USHORT nValue = 0 );
                             SfxFlagItem( const SfxFlagItem& );

                             ~SfxFlagItem() {
                                DBG_DTOR(SfxFlagItem, 0); }

    virtual BYTE			 GetFlagCount() const;
    virtual XubString		 GetFlagText( BYTE nFlag ) const;

    virtual int 			 operator==( const SfxPoolItem& ) const;
    virtual SfxPoolItem*     Create(SvStream &, USHORT nVersion) const;
    virtual SvStream&		 Store(SvStream &, USHORT nItemVersion) const;

    virtual SfxPoolItem*	 Clone( SfxItemPool *pPool = 0 ) const;
    virtual SfxItemPresentation GetPresentation( SfxItemPresentation ePres,
                                    SfxMapUnit eCoreMetric,
                                    SfxMapUnit ePresMetric,
                                    XubString &rText,
                                    const ::IntlWrapper * = 0 ) const;
            USHORT           GetValue() const { return nVal; }
            void			 SetValue( USHORT nNewVal ) {
                                 DBG_ASSERT( GetRefCount() == 0, "SetValue() with pooled item" );
                                 nVal = nNewVal;
                             }
            int 			 GetFlag( BYTE nFlag ) const {
                                 return ( (nVal & nSfxFlagVal[nFlag]) != 0 ); }
};

}

#endif

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
