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
#ifndef _SXSIITM_HXX
#define _SXSIITM_HXX

#ifndef _SXFIITM_HXX
#include <bf_svx/sxfiitm.hxx>
#endif
namespace binfilter {

class SdrScaleItem: public SdrFractionItem {
public:
    TYPEINFO();
    SdrScaleItem(USHORT nId=0): SdrFractionItem(nId,Fraction(1,1)) {}
    SdrScaleItem(USHORT nId, const Fraction& rVal): SdrFractionItem(nId,rVal) {}
    SdrScaleItem(USHORT nId, SvStream& rIn): SdrFractionItem(nId,rIn) {}
    virtual SfxPoolItem*     Create(SvStream&, USHORT nVer) const;
    virtual SfxPoolItem*     Clone(SfxItemPool *pPool=NULL) const;
};

}//end of namespace binfilter
#endif
