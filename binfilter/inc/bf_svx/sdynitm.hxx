/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: sdynitm.hxx,v $
 *
 *  $Revision: 1.6 $
 *
 *  last change: $Author: rt $ $Date: 2008-03-12 13:07:49 $
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
#ifndef _SDYNITM_HXX
#define _SDYNITM_HXX

#ifndef _SFXENUMITEM_HXX //autogen
#include <bf_svtools/eitem.hxx>
#endif
namespace binfilter {

//------------------------------------------------------------
// class SdrYesNoItem
// hier liefert GetValueTextByVal() "ja" oder "nein"
// anstelle von "TRUE" und "FALSE"
//------------------------------------------------------------
class SdrYesNoItem: public SfxBoolItem {
public:
    TYPEINFO();
    SdrYesNoItem(): SfxBoolItem() {}
    SdrYesNoItem(USHORT nId, BOOL bOn=FALSE): SfxBoolItem(nId,bOn) {}
    SdrYesNoItem(USHORT nId, SvStream& rIn):  SfxBoolItem(nId,rIn) {}
    virtual SfxPoolItem* Clone(SfxItemPool* pPool=NULL) const;
    virtual SfxPoolItem* Create(SvStream& rIn, USHORT nVer) const;
#ifdef SDR_ISPOOLABLE
    virtual int IsPoolable() const;
#endif
};

}//end of namespace binfilter
#endif
