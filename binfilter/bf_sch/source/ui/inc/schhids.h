/*************************************************************************
 *
 *  $RCSfile: schhids.h,v $
 *
 *  $Revision: 1.1.1.1 $
 *
 *  last change: $Author: hjs $ $Date: 2003-10-01 12:17:38 $
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



#include <svtools/solar.hrc>

#define HID_SCH_DATA_ROW            (HID_SCH_START + 0)
#define HID_SCH_DATA_LINE           (HID_SCH_START + 1)
#define HID_SCH_DATA_POINT          (HID_SCH_START + 2)
#define HID_SCH_DIAGRAM_X_AXIS      (HID_SCH_START + 3)

#define HID_SCH_ALIGNMENT           (HID_SCH_START + 4)
#define HID_SCH_LEGEND_POS          (HID_SCH_START + 5)
#define HID_SCH_DATA_DESCR          (HID_SCH_START + 6)
#define HID_SCH_SCALE_Y             (HID_SCH_START + 7)
#define HID_SCH_STAT                (HID_SCH_START + 8)
#define HID_SCH_WIN_DOCUMENT        (HID_SCH_START + 9)
#define HID_SCH_CTL_DATA            (HID_SCH_START + 10)
#define HID_SCH_CT_INDICATE         (HID_SCH_START + 11)
#define HID_SCH_CT_REGRESS          (HID_SCH_START + 12)
#define HID_SCH_CT_1_CHARTTYPE      (HID_SCH_START + 13)
#define HID_SCH_CT_2_CHARTVARIANT   (HID_SCH_START + 14)
#define HID_SCH_CTL_TYPE            (HID_SCH_START + 15)
#define HID_SCH_CTL_VARIANT         (HID_SCH_START + 16)
#define HID_SCH_CTL_LIGHT           (HID_SCH_START + 17)
#define HID_SCH_CT_INDICATE2        (HID_SCH_START + 18)
#define HID_SCH_CT_REGRESS2         (HID_SCH_START + 19)
#define HID_SCH_TBI_EDIT_CANCEL     (HID_SCH_START + 20)
#define HID_SCH_TBI_EDIT_ACCEPT     (HID_SCH_START + 21)
#define HID_SCH_TBI_DATA_TRANSFER   (HID_SCH_START + 22)
#define HID_SCH_TBI_DATA_INSERT_ROW (HID_SCH_START + 23)
#define HID_SCH_TBI_DATA_INSERT_COL (HID_SCH_START + 24)
#define HID_SCH_TBI_DATA_DELETE_ROW (HID_SCH_START + 25)
#define HID_SCH_TBI_DATA_DELETE_COL (HID_SCH_START + 26)
#define HID_SCH_TBI_DATA_SWAP_COL   (HID_SCH_START + 27)
#define HID_SCH_TBI_DATA_SWAP_ROW   (HID_SCH_START + 28)
#define HID_SCH_TBI_DATA_SORT_ROW   (HID_SCH_START + 29)
#define HID_SCH_TBI_DATA_SORT_COL   (HID_SCH_START + 30)
#define HID_SCH_TBI_DATA_SORT_TABLE_ROW   (HID_SCH_START + 31)
#define HID_SCH_TBI_DATA_SORT_TABLE_COL   (HID_SCH_START + 32)

#define HID_SCH_TBX_EDIT            (HID_SCH_START + 33)
#define HID_SCH_TBX_DATA            (HID_SCH_START + 34)


#define HID_SCH_ALIGNMENT_CTR_DIAL  (HID_SCH_START + 35)
#define HID_SCH_ALIGNMENT_STACKED   (HID_SCH_START + 36)
#define HID_SCH_ALIGNMENT_DEGREES   (HID_SCH_START + 37)

#define HID_SCH_LAYOUT				(HID_SCH_START + 38)

#define HID_SCH_TBX_EDIT_FIELD		(HID_SCH_START + 39)
#define HID_SCH_DIAGRAM_Y_AXIS      (HID_SCH_START + 40)//war mal 3

#define HID_SCH_DEF_COLOR			(HID_SCH_START + 41)
#define HID_SCH_TP_AXIS_LABEL		(HID_SCH_START + 42)

#define HID_SCH_NUM_OF_LINES        (HID_SCH_START + 43)

#define HID_SCH_CHART_AUTO_FORMAT   (HID_SCH_START + 44)

// HID_SCH_START should be 63280 (checked 25.Nov 2002)

// 453 == SCH_IF_CHARTVIEWSHELL, da SFX_INTERFACE_LIB kein
// Define sondern neuerdings ein Enum ist
#define HID_SCH_VIEWSHELL_DOCUMENT	(453)