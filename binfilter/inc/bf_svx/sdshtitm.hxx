/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: sdshtitm.hxx,v $
 *
 *  $Revision: 1.3 $
 *
 *  last change: $Author: rt $ $Date: 2005-09-09 14:22:28 $
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
#ifndef _SDSHTITM_HXX
#define _SDSHTITM_HXX

#ifndef _SDPRCITM_HXX
#include <bf_svx/sdprcitm.hxx>
#endif

#ifndef _SVDDEF_HXX //autogen
#include <bf_svx/svddef.hxx>
#endif
namespace binfilter {

//---------------------
// class SdrShadowTransparenceItem
//---------------------
class SdrShadowTransparenceItem: public SdrPercentItem {
public:
    SdrShadowTransparenceItem(USHORT nTransp=0): SdrPercentItem(SDRATTR_SHADOWTRANSPARENCE,nTransp) {}
    SdrShadowTransparenceItem(SvStream& rIn)   : SdrPercentItem(SDRATTR_SHADOWTRANSPARENCE,rIn)     {}
};

}//end of namespace binfilter
#endif
