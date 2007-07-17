/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: shell.hxx,v $
 *
 *  $Revision: 1.7 $
 *
 *  last change: $Author: obo $ $Date: 2007-07-17 12:43:35 $
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
#ifndef _SFX_SHELL_HXX
#define _SFX_SHELL_HXX

#ifndef _DEBUG_HXX //autogen
#include <tools/debug.hxx>
#endif
#ifndef _RTTI_HXX //autogen
#include <tools/rtti.hxx>
#endif
#ifndef _SFXBRDCST_HXX //autogen
#include <svtools/brdcst.hxx>
#endif

#include <tools/string.hxx>

class SfxItemPool;
class SfxPoolItem;

namespace binfilter {

struct SfxShell_Impl;

typedef SfxPoolItem* SfxPoolItemPtr;
SV_DECL_PTRARR_DEL( SfxItemPtrArray, SfxPoolItemPtr, 4, 4 )//STRIP008 ;
typedef SfxItemPtrArray SfxItemArray_Impl;

//====================================================================

class SfxShell: public SfxBroadcaster
{
    friend class SfxObjectItem;

    SfxShell_Impl*				pImp;
    SfxItemPool*				pPool;
    String						aName;

private:
                                SfxShell( const SfxShell & ); // n.i.
    SfxShell&					operator = ( const SfxShell & ); // n.i.

protected:
                                SfxShell();
public:
                                TYPEINFO();
    virtual                     ~SfxShell();

    void						SetName( const String &rName ) { aName = rName; }
    const String&   			GetName() const { return aName; }

    SfxItemPool&				GetPool() const { return *pPool; }
    void						SetPool( SfxItemPool *pNewPool ) { pPool = pNewPool; }

    const SfxPoolItem*			GetItem( USHORT nSlotId ) const;
    void						PutItem( const SfxPoolItem& rItem );
    void						RemoveItem( USHORT nSlotId );
};

}//end of namespace binfilter
#endif

