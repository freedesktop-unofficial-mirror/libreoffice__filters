/*************************************************************************
 *
 *  $RCSfile: xattr.hxx,v $
 *
 *  $Revision: 1.2 $
 *
 *  last change: $Author: mwu $ $Date: 2003-11-06 08:29:29 $
 *
 *  The Contents of this file are made available subject to the terms of
 *  either of the following licenses
 *
 *         - GNU Lesser General Public License Version 2.1
 *         - Sun Industry Standards Source License Version 1.1
 *
 *  Sun Microsystems Inc., October, 2000
 *
 *  GNU Lesser General Public License Version 2.1
 *  =============================================
 *  Copyright 2000 by Sun Microsystems, Inc.
 *  901 San Antonio Road, Palo Alto, CA 94303, USA
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public
 *  License version 2.1, as published by the Free Software Foundation.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public
 *  License along with this library; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 *  MA  02111-1307  USA
 *
 *
 *  Sun Industry Standards Source License Version 1.1
 *  =================================================
 *  The contents of this file are subject to the Sun Industry Standards
 *  Source License Version 1.1 (the "License"); You may not use this file
 *  except in compliance with the License. You may obtain a copy of the
 *  License at http://www.openoffice.org/license.html.
 *
 *  Software provided under this License is provided on an "AS IS" basis,
 *  WITHOUT WARRANTY OF ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING,
 *  WITHOUT LIMITATION, WARRANTIES THAT THE SOFTWARE IS FREE OF DEFECTS,
 *  MERCHANTABLE, FIT FOR A PARTICULAR PURPOSE, OR NON-INFRINGING.
 *  See the License for the specific provisions governing your rights and
 *  obligations concerning the Software.
 *
 *  The Initial Developer of the Original Code is: Sun Microsystems, Inc.
 *
 *  Copyright: 2000 by Sun Microsystems, Inc.
 *
 *  All Rights Reserved.
 *
 *  Contributor(s): _______________________________________
 *
 *
 ************************************************************************/
#ifndef _XATTR_HXX
#define _XATTR_HXX
namespace binfilter {

// include ---------------------------------------------------------------

#ifndef _XDEF_HXX
//#include <bf_svx/xdef.hxx>
#endif
#ifndef _XENUM_HXX
//#include <bf_svx/xenum.hxx>
#endif
#ifndef _XPOLY_HXX
//#include <bf_svx/xpoly.hxx>
#endif
#ifndef _SVX_RECTENUM_HXX
//#include <bf_svx/rectenum.hxx>
#endif

class XColorTable;
class XDashTable;
class XLineEndTable;
class XHatchTable;
class XBitmapTable;
class XGradientTable;
}//end of namespace binfilter

#include <bf_svx/xit.hxx>
#include <bf_svx/xcolit.hxx>
#include <bf_svx/xgrad.hxx>
#include <bf_svx/xhatch.hxx>
#include <bf_svx/xlineit.hxx>
#include <bf_svx/xfillit.hxx>
#include <bf_svx/xtextit.hxx>
#include <bf_svx/xlineit0.hxx>
#include <bf_svx/xfillit0.hxx>
#include <bf_svx/xtextit0.hxx>
#include <bf_svx/xsetit.hxx>
#include <bf_svx/xlinjoit.hxx>


#endif      // _XATTR_HXX

