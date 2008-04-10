/*************************************************************************
 *
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER.
 * 
 * Copyright 2008 by Sun Microsystems, Inc.
 *
 * OpenOffice.org - a multi-platform office productivity suite
 *
 * $RCSfile: svt_whiter.cxx,v $
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

// MARKER(update_precomp.py): autogen include statement, do not remove

// INCLUDE ---------------------------------------------------------------
#ifndef GCC
#endif

#include "whiter.hxx"
#include <bf_svtools/itemset.hxx>

namespace binfilter
{

DBG_NAME(SfxWhichIter)

// -----------------------------------------------------------------------

SfxWhichIter::SfxWhichIter( const SfxItemSet& rSet, USHORT nFromWh, USHORT nToWh ):
    pRanges(rSet.GetRanges()),
    pStart(rSet.GetRanges()),
    nOfst(0), nFrom(nFromWh), nTo(nToWh)
{
    DBG_CTOR(SfxWhichIter, 0);
    if ( nFrom > 0 )
        FirstWhich();
}

// -----------------------------------------------------------------------

SfxWhichIter::~SfxWhichIter()
{
    DBG_DTOR(SfxWhichIter, 0);
}

// -----------------------------------------------------------------------

USHORT SfxWhichIter::NextWhich()
{
    DBG_CHKTHIS(SfxWhichIter, 0);
    while ( 0 != *pRanges )
    {
        const USHORT nLastWhich = *pRanges + nOfst;
        ++nOfst;
        if (*(pRanges+1) == nLastWhich)
        {
            pRanges += 2;
            nOfst = 0;
        }
        USHORT nWhich = *pRanges + nOfst;
        if ( 0 == nWhich || ( nWhich >= nFrom && nWhich <= nTo ) )
            return nWhich;
    }
    return 0;
}

// -----------------------------------------------------------------------

USHORT  SfxWhichIter::PrevWhich()
{
    DBG_CHKTHIS(SfxWhichIter, 0);
    while ( pRanges != pStart || 0 != nOfst )
    {
        if(nOfst)
            --nOfst;
        else {
            pRanges -= 2;
            nOfst = *(pRanges+1) - (*pRanges);
        }
        USHORT nWhich = *pRanges + nOfst;
        if ( nWhich >= nFrom && nWhich <= nTo )
            return nWhich;
    }
    return 0;
}

// -----------------------------------------------------------------------

USHORT SfxWhichIter::FirstWhich()
{
    DBG_CHKTHIS(SfxWhichIter, 0);
    pRanges = pStart;
    nOfst = 0;
    if ( *pRanges >= nFrom && *pRanges <= nTo )
        return *pRanges;
    return NextWhich();
}

// -----------------------------------------------------------------------

USHORT SfxWhichIter::LastWhich()
{
    DBG_CHKTHIS(SfxWhichIter, 0);
    while(*pRanges)
        ++pRanges;
    nOfst = 0;
    USHORT nWhich = *(pRanges-1);
    if ( nWhich >= nFrom && nWhich <= nTo )
        return nWhich;
    return PrevWhich();
}

}
