/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: svt_isethint.cxx,v $
 *
 *  $Revision: 1.2 $
 *
 *  last change: $Author: rt $ $Date: 2008-03-12 09:05:41 $
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

// MARKER(update_precomp.py): autogen include statement, do not remove


#ifndef GCC
#endif

#include <bf_svtools/isethint.hxx>
#include <bf_svtools/itemset.hxx>

namespace binfilter
{

//====================================================================

TYPEINIT1(SfxItemSetHint, SfxHint);

//====================================================================

SfxItemSetHint::SfxItemSetHint( SfxItemSet *pItemSet )

/*	[Beschreibung]

    Dieser Ctor "ubernimmt das als Parameter "ubergeben <SfxItemSet>,
    das im Dtor gel"oscht wird.
*/

:	_pItemSet( pItemSet )
{
}

//--------------------------------------------------------------------

SfxItemSetHint::SfxItemSetHint( const SfxItemSet &rItemSet )

/*	[Beschreibung]

    Dieser Ctor kopiert das als Parameter "ubergeben <SfxItemSet>.
*/

:	_pItemSet( rItemSet.Clone() )
{
}

//--------------------------------------------------------------------

SfxItemSetHint::~SfxItemSetHint()
{
    delete _pItemSet;
}

//--------------------------------------------------------------------
}
