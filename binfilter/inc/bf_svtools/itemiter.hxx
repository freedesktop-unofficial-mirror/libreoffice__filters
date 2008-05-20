/*************************************************************************
 *
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER.
 * 
 * Copyright 2008 by Sun Microsystems, Inc.
 *
 * OpenOffice.org - a multi-platform office productivity suite
 *
 * $RCSfile: itemiter.hxx,v $
 * $Revision: 1.4 $
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
#ifndef _SFXITEMITER_HXX
#define _SFXITEMITER_HXX

#ifndef _SOLAR_H
#include <tools/solar.h>
#endif

#ifndef _SFXITEMSET_HXX
#include <bf_svtools/itemset.hxx>
#endif

namespace binfilter
{

class SfxPoolItem;
class SfxItemSet;
class SfxItemPool;

class  SfxItemIter
{
    // Item-Feld - Start & Ende
    const SfxItemSet&	_rSet;
    USHORT				_nStt, _nEnd, _nAkt;

public:
    SfxItemIter( const SfxItemSet& rSet );
    ~SfxItemIter();

    // falls es diese gibt, returne sie, sonst 0
    const SfxPoolItem* FirstItem()
                       { _nAkt = _nStt;
                         return _rSet._nCount ? *(_rSet._aItems+_nAkt) : 0; }
    const SfxPoolItem* LastItem()
                       { _nAkt = _nEnd;
                         return _rSet._nCount ? *(_rSet._aItems+_nAkt) : 0; }
    const SfxPoolItem* GetCurItem()
                       { return _rSet._nCount ? *(_rSet._aItems+_nAkt) : 0; }
    const SfxPoolItem* NextItem();

    BOOL			   IsAtStart() const { return _nAkt == _nStt; }
    BOOL               IsAtEnd() const   { return _nAkt == _nEnd; }

    USHORT             GetCurPos() const { return _nAkt; }
    USHORT             GetFirstPos() const { return _nStt; }
    USHORT             GetLastPos() const { return _nEnd; }
};

}

#endif
