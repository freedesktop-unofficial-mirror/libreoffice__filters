/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: poolcach.hxx,v $
 *
 *  $Revision: 1.2 $
 *
 *  last change: $Author: rt $ $Date: 2008-03-12 12:23:20 $
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
#ifndef _SFXPOOLCACH_HXX
#define _SFXPOOLCACH_HXX

#ifndef INCLUDED_SVTDLLAPI_H
#include "bf_svtools/svtdllapi.h"
#endif

#ifndef _SOLAR_H
#include <tools/solar.h>
#endif

namespace binfilter
{

class SfxItemModifyArr_Impl;
class SfxItemPool;
class SfxItemSet;
class SfxPoolItem;
class SfxSetItem;

class  SfxItemPoolCache
{
    SfxItemPool 			*pPool;
    SfxItemModifyArr_Impl	*pCache;
    const SfxItemSet		*pSetToPut;
    const SfxPoolItem		*pItemToPut;

public:
                            SfxItemPoolCache( SfxItemPool *pPool,
                                              const SfxPoolItem *pPutItem );
                            SfxItemPoolCache( SfxItemPool *pPool,
                                              const SfxItemSet *pPutSet );
                            ~SfxItemPoolCache();

    const SfxSetItem&		ApplyTo( const SfxSetItem& rSetItem, BOOL bNew = FALSE );
};

}

#endif

