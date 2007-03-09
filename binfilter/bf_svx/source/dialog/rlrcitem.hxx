/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: rlrcitem.hxx,v $
 *
 *  $Revision: 1.4 $
 *
 *  last change: $Author: obo $ $Date: 2007-03-09 15:20:13 $
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
#ifndef _SVX_RLRCITEM_HXX
#define _SVX_RLRCITEM_HXX

#ifndef _SFXCTRLITEM_HXX
#include <bf_sfx2/ctrlitem.hxx>
#endif
namespace binfilter {

class SvxRuler;

// class SvxRulerItem ----------------------------------------------------

class SvxRulerItem : public SfxControllerItem
{
private:
    SvxRuler& rRuler;

protected:
    virtual void StateChanged( USHORT,
                               SfxItemState, const SfxPoolItem* pState );

public:
    SvxRulerItem( USHORT nId, SvxRuler&, SfxBindings& );
};


}//end of namespace binfilter
#endif
