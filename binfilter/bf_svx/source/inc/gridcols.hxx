/*************************************************************************
 *
 *  $RCSfile: gridcols.hxx,v $
 *
 *  $Revision: 1.1.1.1 $
 *
 *  last change: $Author: hjs $ $Date: 2003-10-01 12:22:01 $
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
#ifndef _SVX_GRIDCOLS_HXX
#define _SVX_GRIDCOLS_HXX

#ifndef _FM_STATIC_HXX_
#include "fmstatic.hxx"
#endif

namespace svxform
{

    // list of possible controls
    DECLARE_CONSTASCII_USTRING(FM_COL_TEXTFIELD);
    DECLARE_CONSTASCII_USTRING(FM_COL_CHECKBOX);
    DECLARE_CONSTASCII_USTRING(FM_COL_COMBOBOX);
    DECLARE_CONSTASCII_USTRING(FM_COL_LISTBOX);
    DECLARE_CONSTASCII_USTRING(FM_COL_NUMERICFIELD);
    DECLARE_CONSTASCII_USTRING(FM_COL_DATEFIELD);
    DECLARE_CONSTASCII_USTRING(FM_COL_TIMEFIELD);
    DECLARE_CONSTASCII_USTRING(FM_COL_CURRENCYFIELD);
    DECLARE_CONSTASCII_USTRING(FM_COL_PATTERNFIELD);
    DECLARE_CONSTASCII_USTRING(FM_COL_FORMATTEDFIELD);

}	// namespace svxform


// column type ids
#define TYPE_CHECKBOX		0
#define TYPE_COMBOBOX		1
#define TYPE_CURRENCYFIELD  2
#define TYPE_DATEFIELD		3
#define TYPE_FORMATTEDFIELD	4
#define TYPE_LISTBOX		5
#define TYPE_NUMERICFIELD	6
#define TYPE_PATTERNFIELD	7
#define TYPE_TEXTFIELD		8
#define TYPE_TIMEFIELD		9

//------------------------------------------------------------------------------
sal_Int32 getColumnTypeByModelName(const ::rtl::OUString& aModelName);


#endif // _SVX_GRIDCOLS_HXX

