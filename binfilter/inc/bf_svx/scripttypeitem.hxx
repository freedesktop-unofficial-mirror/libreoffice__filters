/*************************************************************************
 *
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER.
 * 
 * Copyright 2008 by Sun Microsystems, Inc.
 *
 * OpenOffice.org - a multi-platform office productivity suite
 *
 * $RCSfile: scripttypeitem.hxx,v $
 * $Revision: 1.6 $
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
#ifndef _SVX_SCRIPTTYPEITEM_HXX
#define _SVX_SCRIPTTYPEITEM_HXX

// include ---------------------------------------------------------------

#ifndef _SFXINTITEM_HXX
#include <bf_svtools/intitem.hxx>
#endif
#ifndef _SVX_SVXIDS_HRC
#include <bf_svx/svxids.hrc>
#endif
#ifndef _SVTOOLS_LANGUAGEOPTIONS_HXX
#include <bf_svtools/languageoptions.hxx>
#endif
namespace binfilter {

// class SvxScriptTypeItem ----------------------------------------------

/* [Description]

        This item describe  the scriptype of the selected text and is only
    used for the user interface.
*/

USHORT GetI18NScriptTypeOfLanguage( USHORT nLang );
USHORT GetItemScriptType( short nI18NType );
short  GetI18NScriptType( USHORT nItemType );


class SvxScriptSetItem : public SfxSetItem
{
public:
    TYPEINFO();

    SvxScriptSetItem( USHORT nSlotId, SfxItemPool& rPool );

    virtual SfxPoolItem* Clone( SfxItemPool *pPool = 0 ) const;
    virtual SfxPoolItem* Create( SvStream &, USHORT nVersion ) const;

    static const SfxPoolItem* GetItemOfScriptSet( const SfxItemSet& rSet,
                                                    USHORT nWhich );
    inline const SfxPoolItem* GetItemOfScriptSet( USHORT nWhich ) const
    { return SvxScriptSetItem::GetItemOfScriptSet( GetItemSet(), nWhich ); }

    const SfxPoolItem* GetItemOfScript( USHORT nScript ) const;


    void GetWhichIds( USHORT& rLatin, USHORT& rAsian, USHORT& rComplex) const;

    static void GetSlotIds( USHORT nSlotId, USHORT& rLatin, USHORT& rAsian,
                                            USHORT& rComplex );
    inline void GetSlotIds( USHORT& rLatin, USHORT& rAsian,
                                USHORT& rComplex ) const
    { GetSlotIds( Which(), rLatin, rAsian, rComplex ); }
};

}//end of namespace binfilter
#endif

