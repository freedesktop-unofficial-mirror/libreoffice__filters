/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: wrt_fn.hxx,v $
 *
 *  $Revision: 1.3 $
 *
 *  last change: $Author: rt $ $Date: 2005-09-09 03:18:22 $
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
#ifndef _WRT_FN_HXX
#define _WRT_FN_HXX

#include "hintids.hxx"		// fuer die Konstanten
class SfxPoolItem;
class SfxItemSet; 

namespace binfilter {

// einige Forward-Deklarationen
class SwFmt;
class SwNode;
class SwCntntNode;
class Writer;


/* Funktionspointer auf die Attribut-Write-Funktionen */
typedef Writer& (*FnAttrOut)( Writer&, const SfxPoolItem& );
typedef FnAttrOut SwAttrFnTab[ POOLATTR_END - POOLATTR_BEGIN ];

Writer& Out( const SwAttrFnTab, const SfxPoolItem&, Writer& );
Writer& Out_SfxItemSet( const SwAttrFnTab, Writer&, const SfxItemSet&,
                         BOOL bDeep, BOOL bTstForDefault = TRUE );


/* Funktionspointer auf die Node-Write-Funktionen */

enum RES_NODE
{
RES_NODE_BEGIN = 0,
    RES_TXTNODE = RES_NODE_BEGIN,
    RES_GRFNODE,
    RES_OLENODE,
RES_NODE_END
};

typedef Writer& (*FnNodeOut)( Writer&, SwCntntNode& );
typedef FnNodeOut SwNodeFnTab[ RES_NODE_END - RES_NODE_BEGIN ];

Writer& Out( const SwNodeFnTab, SwNode&, Writer & rWrt );




} //namespace binfilter
#endif	//	_WRT_FN_HXX
