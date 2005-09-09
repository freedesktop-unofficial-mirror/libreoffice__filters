/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: srchdefs.hxx,v $
 *
 *  $Revision: 1.3 $
 *
 *  last change: $Author: rt $ $Date: 2005-09-09 12:39:03 $
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

#ifndef _SFX_SRCHDEFS_HXX_
#define _SFX_SRCHDEFS_HXX_
namespace binfilter {

#define SEARCH_OPTIONS_SEARCH       ((sal_uInt16)0x0001)
#define SEARCH_OPTIONS_SEARCH_ALL   ((sal_uInt16)0x0002)
#define SEARCH_OPTIONS_REPLACE      ((sal_uInt16)0x0004)
#define SEARCH_OPTIONS_REPLACE_ALL  ((sal_uInt16)0x0008)
#define SEARCH_OPTIONS_WHOLE_WORDS  ((sal_uInt16)0x0010)
#define SEARCH_OPTIONS_BACKWARDS    ((sal_uInt16)0x0020)
#define SEARCH_OPTIONS_REG_EXP      ((sal_uInt16)0x0040)
#define SEARCH_OPTIONS_EXACT        ((sal_uInt16)0x0080)
#define SEARCH_OPTIONS_SELECTION    ((sal_uInt16)0x0100)
#define SEARCH_OPTIONS_FAMILIES     ((sal_uInt16)0x0200)
#define SEARCH_OPTIONS_FORMAT       ((sal_uInt16)0x0400)
#define SEARCH_OPTIONS_MORE			((sal_uInt16)0x0800)
#define SEARCH_OPTIONS_SIMILARITY	((sal_uInt16)0x1000)
#define SEARCH_OPTIONS_CONTENT		((sal_uInt16)0x2000)

}//end of namespace binfilter
#endif

