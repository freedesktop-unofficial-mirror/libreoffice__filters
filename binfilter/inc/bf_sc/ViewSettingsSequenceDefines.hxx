/*************************************************************************
 *
 *  $RCSfile: ViewSettingsSequenceDefines.hxx,v $
 *
 *  $Revision: 1.2 $
 *
 *  last change: $Author: mwu $ $Date: 2003-11-06 07:59:26 $
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

#ifndef _SC_VIEWSETTINGSSEQUENCEDEFINES_HXX
#define _SC_VIEWSETTINGSSEQUENCEDEFINES_HXX

// this are the defines for the position of the settings in the
// ViewSettingsSequence
namespace binfilter {

#define SC_VIEWSETTINGS_COUNT				23

#define SC_VIEW_ID							0
#define SC_TABLE_VIEWSETTINGS				1
#define SC_ACTIVE_TABLE						2
#define SC_HORIZONTAL_SCROLL_BAR_WIDTH		3
#define SC_ZOOM_TYPE						4
#define SC_ZOOM_VALUE						5
#define SC_PAGE_VIEW_ZOOM_VALUE				6
#define SC_PAGE_BREAK_PREVIEW				7
#define SC_SHOWZERO							8
#define SC_SHOWNOTES						9
#define SC_SHOWGRID							10
#define SC_GRIDCOLOR						11
#define SC_SHOWPAGEBR						12
#define SC_COLROWHDR						13
#define SC_SHEETTABS						14
#define SC_OUTLSYMB							15
#define SC_SNAPTORASTER						16
#define SC_RASTERVIS						17
#define SC_RASTERRESX						18
#define SC_RASTERRESY						19
#define SC_RASTERSUBX						20
#define SC_RASTERSUBY						21
#define SC_RASTERSYNC						22


// this are the defines for the position of the settings in the
// TableViewSettingsSequence

#define SC_TABLE_VIEWSETTINGS_COUNT			11

#define SC_CURSOR_X							0
#define SC_CURSOR_Y							1
#define SC_HORIZONTAL_SPLIT_MODE			2
#define SC_VERTICAL_SPLIT_MODE				3
#define SC_HORIZONTAL_SPLIT_POSITION		4
#define SC_VERTICAL_SPLIT_POSITION			5
#define SC_ACTIVE_SPLIT_RANGE				6
#define SC_POSITION_LEFT					7
#define SC_POSITION_RIGHT					8
#define SC_POSITION_TOP						9
#define SC_POSITION_BOTTOM					10

#define SC_CURSORPOSITIONX					"CursorPositionX"
#define SC_CURSORPOSITIONY					"CursorPositionY"
#define SC_HORIZONTALSPLITMODE				"HorizontalSplitMode"
#define SC_VERTICALSPLITMODE				"VerticalSplitMode"
#define SC_HORIZONTALSPLITPOSITION			"HorizontalSplitPosition"
#define SC_VERTICALSPLITPOSITION			"VerticalSplitPosition"
#define SC_ACTIVESPLITRANGE					"ActiveSplitRange"
#define SC_POSITIONLEFT						"PositionLeft"
#define SC_POSITIONRIGHT					"PositionRight"
#define SC_POSITIONTOP						"PositionTop"
#define SC_POSITIONBOTTOM					"PositionBottom"

#define SC_TABLES							"Tables"
#define SC_ACTIVETABLE						"ActiveTable"
#define SC_HORIZONTALSCROLLBARWIDTH			"HorizontalScrollbarWidth"
#define SC_ZOOMTYPE							"ZoomType"
#define SC_ZOOMVALUE						"ZoomValue"
#define SC_PAGEVIEWZOOMVALUE				"PageViewZoomValue"
#define SC_SHOWPAGEBREAKPREVIEW					"ShowPageBreakPreview"
#define SC_VIEWID							"ViewId"
#define SC_VIEW								"View"

} //namespace binfilter
#endif
