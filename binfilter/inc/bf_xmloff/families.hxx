/*************************************************************************
 *
 *  $RCSfile: families.hxx,v $
 *
 *  $Revision: 1.1 $
 *
 *  last change: $Author: jmeng $ $Date: 2003-12-04 01:45:38 $
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
#ifndef _XMLOFF_FAMILIES_HXX_
#define _XMLOFF_FAMILIES_HXX_
namespace binfilter {

/** These defines determine the unique ids for XML style-families
    used in the SvXMLAutoStylePoolP.
 */

// Misc (Pool)
// reserved: 0..99
#define XML_STYLE_FAMILY_DATA_STYLE				0
#define XML_STYLE_FAMILY_DATA_STYLE_NAME		"data-style"
#define XML_STYLE_FAMILY_PAGE_MASTER			1
#define XML_STYLE_FAMILY_PAGE_MASTER_NAME		"page-master"
#define XML_STYLE_FAMILY_PAGE_MASTER_PREFIX		"pm"
#define XML_STYLE_FAMILY_MASTER_PAGE			2

// Text
// reserved: 100..199
#define XML_STYLE_FAMILY_TEXT_PARAGRAPH			100
#define XML_STYLE_FAMILY_TEXT_TEXT				101
#define XML_STYLE_FAMILY_TEXT_LIST				102
#define XML_STYLE_FAMILY_TEXT_OUTLINE			103
#define XML_STYLE_FAMILY_TEXT_FOOTNOTECONFIG	105
#define XML_STYLE_FAMILY_TEXT_ENDNOTECONFIG		106
#define XML_STYLE_FAMILY_TEXT_SECTION			107
#define XML_STYLE_FAMILY_TEXT_FRAME				108	// export only
#define XML_STYLE_FAMILY_TEXT_RUBY				109
#define XML_STYLE_FAMILY_TEXT_BIBLIOGRAPHYCONFIG 110
#define XML_STYLE_FAMILY_TEXT_LINENUMBERINGCONFIG 111

// Table
// reserved: 200..299
#define XML_STYLE_FAMILY_TABLE_TABLE			200
#define XML_STYLE_FAMILY_TABLE_TABLE_STYLES_NAME	"table"
#define XML_STYLE_FAMILY_TABLE_TABLE_STYLES_PREFIX	"ta"
#define XML_STYLE_FAMILY_TABLE_COLUMN			202
#define XML_STYLE_FAMILY_TABLE_COLUMN_STYLES_NAME	"table-column"
#define XML_STYLE_FAMILY_TABLE_COLUMN_STYLES_PREFIX	"co"
#define XML_STYLE_FAMILY_TABLE_ROW				203
#define XML_STYLE_FAMILY_TABLE_ROW_STYLES_NAME	"table-row"
#define XML_STYLE_FAMILY_TABLE_ROW_STYLES_PREFIX	"ro"
#define XML_STYLE_FAMILY_TABLE_CELL				204
#define XML_STYLE_FAMILY_TABLE_CELL_STYLES_NAME	"table-cell"
#define XML_STYLE_FAMILY_TABLE_CELL_STYLES_PREFIX	"ce"

// Impress/Draw
// reserved: 300..399
#define XML_STYLE_FAMILY_SD_GRAPHICS_ID			300
#define XML_STYLE_FAMILY_SD_GRAPHICS_NAME		"graphics"
#define XML_STYLE_FAMILY_SD_GRAPHICS_PREFIX		"gr"

#define XML_STYLE_FAMILY_SD_PRESENTATION_ID		301
#define XML_STYLE_FAMILY_SD_PRESENTATION_NAME	"presentation"
#define XML_STYLE_FAMILY_SD_PRESENTATION_PREFIX	"pr"
// families for derived from SvXMLStyleContext
#define XML_STYLE_FAMILY_SD_PAGEMASTERCONEXT_ID			302
#define XML_STYLE_FAMILY_SD_PAGEMASTERSTYLECONEXT_ID	306
#define XML_STYLE_FAMILY_SD_PRESENTATIONPAGELAYOUT_ID	303
// family for draw pool
#define XML_STYLE_FAMILY_SD_POOL_ID				304
#define XML_STYLE_FAMILY_SD_POOL_NAME			"default"
// family for presentation drawpage properties
#define XML_STYLE_FAMILY_SD_DRAWINGPAGE_ID		305
#define XML_STYLE_FAMILY_SD_DRAWINGPAGE_NAME	"drawing-page"
#define XML_STYLE_FAMILY_SD_DRAWINGPAGE_PREFIX	"dp"

// Chart
// reserved: 400..499
#define XML_STYLE_FAMILY_SCH_CHART_ID			400
#define XML_STYLE_FAMILY_SCH_CHART_NAME			"chart"
#define XML_STYLE_FAMILY_SCH_CHART_PREFIX		"ch"

// Math
// reserved: 500..599

// Forms/Controls
// reserved 600..649
#define XML_STYLE_FAMILY_CONTROL_ID				600
#define XML_STYLE_FAMILY_CONTROL_NAME			"control"
#define XML_STYLE_FAMILY_CONTROL_PREFIX			"ctrl"

}//end of namespace binfilter
#endif	// _XMLOFF_FAMILIES_HXX_
