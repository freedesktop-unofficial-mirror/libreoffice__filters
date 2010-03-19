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
#ifndef _SFXIITM_HXX
#define _SFXIITM_HXX

#ifndef _SFXPOOLITEM_HXX //autogen
#include <bf_svtools/poolitem.hxx>
#endif

#ifndef _FRACT_HXX //autogen
#include <tools/fract.hxx>
#endif
namespace binfilter {

/*************************************************************************/
/* FractionItem                                                          */
/*************************************************************************/

class SdrFractionItem: public SfxPoolItem {
    Fraction nValue;
public:
    TYPEINFO();
    SdrFractionItem(USHORT nId=0): SfxPoolItem(nId) {}
    SdrFractionItem(USHORT nId, const Fraction& rVal): SfxPoolItem(nId), nValue(rVal) {}
    SdrFractionItem(USHORT nId, SvStream& rIn);
    virtual int              operator==(const SfxPoolItem&) const;
    virtual SvStream&        Store(SvStream&, USHORT nItemVers) const;
    virtual SfxPoolItem*     Clone(SfxItemPool *pPool=NULL) const;
            const Fraction&  GetValue() const { return nValue; }
            void             SetValue(const Fraction& rVal) { nValue = rVal; }
#ifdef SDR_ISPOOLABLE
    virtual int IsPoolable() const;
#endif
};

}//end of namespace binfilter
#endif
