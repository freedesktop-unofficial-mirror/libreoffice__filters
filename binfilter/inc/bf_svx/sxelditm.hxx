/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: sxelditm.hxx,v $
 *
 *  $Revision: 1.4 $
 *
 *  last change: $Author: rt $ $Date: 2006-10-28 04:16:11 $
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
#ifndef _SXELDITM_HXX
#define _SXELDITM_HXX

#ifndef _SVDDEF_HXX //autogen
#include <bf_svx/svddef.hxx>
#endif

#ifndef _SDMETITM_HXX
#include <bf_svx/sdmetitm.hxx>
#endif
namespace binfilter {

class SdrEdgeLineDeltaAnzItem: public SfxUInt16Item {
public:
    SdrEdgeLineDeltaAnzItem(UINT16 nVal=0): SfxUInt16Item(SDRATTR_EDGELINEDELTAANZ,nVal) {}
    SdrEdgeLineDeltaAnzItem(SvStream& rIn): SfxUInt16Item(SDRATTR_EDGELINEDELTAANZ,rIn)  {}
};

class SdrEdgeLine1DeltaItem: public SdrMetricItem {
public:
    SdrEdgeLine1DeltaItem(long nVal=0): SdrMetricItem(SDRATTR_EDGELINE1DELTA,nVal)  {}
    SdrEdgeLine1DeltaItem(SvStream& rIn): SdrMetricItem(SDRATTR_EDGELINE1DELTA,rIn) {}
};

class SdrEdgeLine2DeltaItem: public SdrMetricItem {
public:
    SdrEdgeLine2DeltaItem(long nVal=0): SdrMetricItem(SDRATTR_EDGELINE2DELTA,nVal)  {}
    SdrEdgeLine2DeltaItem(SvStream& rIn): SdrMetricItem(SDRATTR_EDGELINE2DELTA,rIn) {}
};

class SdrEdgeLine3DeltaItem: public SdrMetricItem {
public:
    SdrEdgeLine3DeltaItem(long nVal=0): SdrMetricItem(SDRATTR_EDGELINE3DELTA,nVal)  {}
    SdrEdgeLine3DeltaItem(SvStream& rIn): SdrMetricItem(SDRATTR_EDGELINE3DELTA,rIn) {}
};

}//end of namespace binfilter
#endif
