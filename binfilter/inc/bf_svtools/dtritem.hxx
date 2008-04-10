/*************************************************************************
 *
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER.
 * 
 * Copyright 2008 by Sun Microsystems, Inc.
 *
 * OpenOffice.org - a multi-platform office productivity suite
 *
 * $RCSfile: dtritem.hxx,v $
 * $Revision: 1.3 $
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

#ifndef _DTRITEM_HXX
#define _DTRITEM_HXX

#ifndef _RTTI_HXX
#include <tools/rtti.hxx>
#endif

#ifndef _DATETIME_HXX
#include <tools/datetime.hxx>
#endif

#include <bf_svtools/poolitem.hxx>

class SvStream;

namespace binfilter {

DBG_NAMEEX(SfxDateTimeRangeItem)

// class SfxDateTimeRangeItem -------------------------------------------------

class SfxDateTimeRangeItem : public SfxPoolItem
{
private:
    DateTime				aStartDateTime;
    DateTime				aEndDateTime;

public:
            TYPEINFO();

            SfxDateTimeRangeItem( const SfxDateTimeRangeItem& rCpy );
            SfxDateTimeRangeItem( USHORT nWhich );
            SfxDateTimeRangeItem( USHORT nWhich, const DateTime& rStartDT,
                                  const DateTime& rEndDT );

            ~SfxDateTimeRangeItem()
                { DBG_DTOR(SfxDateTimeRangeItem, 0); }

    virtual	int				operator==( const SfxPoolItem& )			const;
    using SfxPoolItem::Compare;
    virtual int				Compare( const SfxPoolItem &rWith )			const;
    virtual SfxPoolItem*	Create( SvStream&, USHORT nItemVersion )	const;
    virtual SvStream&		Store( SvStream&, USHORT nItemVersion )		const;
    virtual SfxPoolItem*	Clone( SfxItemPool* pPool = 0 )				const;
    virtual SfxItemPresentation GetPresentation( SfxItemPresentation ePres,
                                    SfxMapUnit eCoreMetric,
                                    SfxMapUnit ePresMetric,
                                    XubString &rText,
                                    const ::IntlWrapper * pIntlWrapper = 0 )
        const;

    virtual	BOOL 			PutValue  ( const ::com::sun::star::uno::Any& rVal,
                                         BYTE nMemberId = 0 );
    virtual	BOOL 			QueryValue( ::com::sun::star::uno::Any& rVal,
                                         BYTE nMemberId = 0 ) const;

    const DateTime&			GetStartDateTime()		const { return aStartDateTime; }
    const DateTime&			GetEndDateTime()		const { return aEndDateTime; }

    void					SetStartDateTime( const DateTime& rDT )
                            { DBG_ASSERT( GetRefCount() == 0, "SetDateTime() with pooled item" );
                              aStartDateTime = rDT; }

    void					SetEndDateTime( const DateTime& rDT )
                            { DBG_ASSERT( GetRefCount() == 0, "SetDateTime() with pooled item" );
                              aEndDateTime = rDT; }
};

}

#endif

