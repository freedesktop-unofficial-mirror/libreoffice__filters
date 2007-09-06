/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: sch_itempool.cxx,v $
 *
 *  $Revision: 1.6 $
 *
 *  last change: $Author: kz $ $Date: 2007-09-06 11:17:20 $
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


#ifdef _MSC_VER
#pragma hdrstop
#endif

#include <bf_sfx2/sfxsids.hrc>
#include "schattr.hxx"
#define ITEMID_CHARTDATADESCR	SCHATTR_DATADESCR_DESCR
#define ITEMID_CHARTLEGENDPOS	SCHATTR_LEGEND_POS
#define ITEMID_CHARTTEXTORDER	SCHATTR_TEXT_ORDER
#define ITEMID_CHARTTEXTORIENT	SCHATTR_TEXT_ORIENT
#define ITEMID_DOUBLE			0
#define ITEMID_CHARTINDICATE    SCHATTR_STAT_INDICATE
#define ITEMID_CHARTKINDERROR   SCHATTR_STAT_KIND_ERROR
#define ITEMID_CHARTREGRESSION  SCHATTR_STAT_REGRESSTYPE

#ifndef _SVX_CHRTITEM_HXX //autogen

#ifndef _SFXENUMITEM_HXX
#include <svtools/eitem.hxx>
#endif

#endif

// header for class SvXMLAttrContainerItem
#ifndef _SVX_XMLCNITM_HXX
#include <bf_svx/xmlcnitm.hxx>
#endif

#ifndef _SVX_BRSHITEM_HXX //autogen
#define ITEMID_BRUSH SCHATTR_SYMBOL_BRUSH
#include <bf_svx/brshitem.hxx>
#endif
#ifndef _SVX_SIZEITEM_HXX //autogen
#define ITEMID_SIZE 0
#include <bf_svx/sizeitem.hxx>
#endif

#include "itempool.hxx"
#include "chaxis.hxx"
namespace binfilter {


/*************************************************************************
|*
|* Konstruktor
|*
\************************************************************************/

/*N*/ SchItemPool::SchItemPool():
/*N*/ 		SfxItemPool( String( RTL_CONSTASCII_USTRINGPARAM( "SchItemPool" )), SCHATTR_START, SCHATTR_END, NULL, NULL )
/*N*/ {
    /**************************************************************************
     * PoolDefaults
     **************************************************************************/
/*N*/ 	ppPoolDefaults = new SfxPoolItem*[SCHATTR_END - SCHATTR_START + 1];
/*N*/ 
/*N*/ 	ppPoolDefaults[SCHATTR_DATADESCR_DESCR			- SCHATTR_START] = new SvxChartDataDescrItem;
/*N*/ 	ppPoolDefaults[SCHATTR_DATADESCR_SHOW_SYM		- SCHATTR_START] = new SfxBoolItem(SCHATTR_DATADESCR_SHOW_SYM);
/*N*/ 	ppPoolDefaults[SCHATTR_LEGEND_POS				- SCHATTR_START] = new SvxChartLegendPosItem( CHLEGEND_RIGHT );
/*N*/ 	ppPoolDefaults[SCHATTR_TEXT_ORIENT				- SCHATTR_START] = new SvxChartTextOrientItem;
/*N*/ 	ppPoolDefaults[SCHATTR_TEXT_ORDER				- SCHATTR_START] = new SvxChartTextOrderItem;
/*N*/ 
/*N*/ 	ppPoolDefaults[SCHATTR_Y_AXIS_AUTO_MIN			- SCHATTR_START] = new SfxBoolItem(SCHATTR_Y_AXIS_AUTO_MIN);
/*N*/ 	ppPoolDefaults[SCHATTR_Y_AXIS_MIN				- SCHATTR_START] = new SvxDoubleItem(0.0, SCHATTR_Y_AXIS_MIN);
/*N*/ 	ppPoolDefaults[SCHATTR_Y_AXIS_AUTO_MAX	  		- SCHATTR_START] = new SfxBoolItem(SCHATTR_Y_AXIS_AUTO_MAX);
/*N*/ 	ppPoolDefaults[SCHATTR_Y_AXIS_MAX				- SCHATTR_START] = new SvxDoubleItem(0.0, SCHATTR_Y_AXIS_MAX);
/*N*/ 	ppPoolDefaults[SCHATTR_Y_AXIS_AUTO_STEP_MAIN	- SCHATTR_START] = new SfxBoolItem(SCHATTR_Y_AXIS_AUTO_STEP_MAIN);
/*N*/ 	ppPoolDefaults[SCHATTR_Y_AXIS_STEP_MAIN			- SCHATTR_START] = new SvxDoubleItem(0.0, SCHATTR_Y_AXIS_STEP_MAIN);
/*N*/ 	ppPoolDefaults[SCHATTR_Y_AXIS_AUTO_STEP_HELP	- SCHATTR_START] = new SfxBoolItem(SCHATTR_Y_AXIS_AUTO_STEP_HELP);
/*N*/ 	ppPoolDefaults[SCHATTR_Y_AXIS_STEP_HELP			- SCHATTR_START] = new SvxDoubleItem(0.0, SCHATTR_Y_AXIS_STEP_HELP);
/*N*/ 	ppPoolDefaults[SCHATTR_Y_AXIS_LOGARITHM			- SCHATTR_START] = new SfxBoolItem(SCHATTR_Y_AXIS_LOGARITHM);
/*N*/ 	ppPoolDefaults[SCHATTR_Y_AXIS_AUTO_ORIGIN		- SCHATTR_START] = new SfxBoolItem(SCHATTR_Y_AXIS_AUTO_ORIGIN);
/*N*/ 	ppPoolDefaults[SCHATTR_Y_AXIS_ORIGIN			- SCHATTR_START] = new SvxDoubleItem(0.0, SCHATTR_Y_AXIS_ORIGIN);
/*N*/ 
/*N*/ 	ppPoolDefaults[SCHATTR_X_AXIS_AUTO_MIN			- SCHATTR_START] = new SfxBoolItem(SCHATTR_X_AXIS_AUTO_MIN);
/*N*/ 	ppPoolDefaults[SCHATTR_X_AXIS_MIN				- SCHATTR_START] = new SvxDoubleItem(0.0, SCHATTR_X_AXIS_MIN);
/*N*/ 	ppPoolDefaults[SCHATTR_X_AXIS_AUTO_MAX	  		- SCHATTR_START] = new SfxBoolItem(SCHATTR_X_AXIS_AUTO_MAX);
/*N*/ 	ppPoolDefaults[SCHATTR_X_AXIS_MAX				- SCHATTR_START] = new SvxDoubleItem(0.0, SCHATTR_X_AXIS_MAX);
/*N*/ 	ppPoolDefaults[SCHATTR_X_AXIS_AUTO_STEP_MAIN	- SCHATTR_START] = new SfxBoolItem(SCHATTR_X_AXIS_AUTO_STEP_MAIN);
/*N*/ 	ppPoolDefaults[SCHATTR_X_AXIS_STEP_MAIN			- SCHATTR_START] = new SvxDoubleItem(0.0, SCHATTR_X_AXIS_STEP_MAIN);
/*N*/ 	ppPoolDefaults[SCHATTR_X_AXIS_AUTO_STEP_HELP	- SCHATTR_START] = new SfxBoolItem(SCHATTR_X_AXIS_AUTO_STEP_HELP);
/*N*/ 	ppPoolDefaults[SCHATTR_X_AXIS_STEP_HELP			- SCHATTR_START] = new SvxDoubleItem(0.0, SCHATTR_X_AXIS_STEP_HELP);
/*N*/ 	ppPoolDefaults[SCHATTR_X_AXIS_LOGARITHM			- SCHATTR_START] = new SfxBoolItem(SCHATTR_X_AXIS_LOGARITHM);
/*N*/ 	ppPoolDefaults[SCHATTR_X_AXIS_AUTO_ORIGIN		- SCHATTR_START] = new SfxBoolItem(SCHATTR_X_AXIS_AUTO_ORIGIN);
/*N*/ 	ppPoolDefaults[SCHATTR_X_AXIS_ORIGIN			- SCHATTR_START] = new SvxDoubleItem(0.0, SCHATTR_X_AXIS_ORIGIN);
/*N*/ 
/*N*/ 	ppPoolDefaults[SCHATTR_Z_AXIS_AUTO_MIN			- SCHATTR_START] = new SfxBoolItem(SCHATTR_Z_AXIS_AUTO_MIN);
/*N*/ 	ppPoolDefaults[SCHATTR_Z_AXIS_MIN				- SCHATTR_START] = new SvxDoubleItem(0.0, SCHATTR_Z_AXIS_MIN);
/*N*/ 	ppPoolDefaults[SCHATTR_Z_AXIS_AUTO_MAX	  		- SCHATTR_START] = new SfxBoolItem(SCHATTR_Z_AXIS_AUTO_MAX);
/*N*/ 	ppPoolDefaults[SCHATTR_Z_AXIS_MAX				- SCHATTR_START] = new SvxDoubleItem(0.0, SCHATTR_Z_AXIS_MAX);
/*N*/ 	ppPoolDefaults[SCHATTR_Z_AXIS_AUTO_STEP_MAIN	- SCHATTR_START] = new SfxBoolItem(SCHATTR_Z_AXIS_AUTO_STEP_MAIN);
/*N*/ 	ppPoolDefaults[SCHATTR_Z_AXIS_STEP_MAIN			- SCHATTR_START] = new SvxDoubleItem(0.0, SCHATTR_Z_AXIS_STEP_MAIN);
/*N*/ 	ppPoolDefaults[SCHATTR_Z_AXIS_AUTO_STEP_HELP	- SCHATTR_START] = new SfxBoolItem(SCHATTR_Z_AXIS_AUTO_STEP_HELP);
/*N*/ 	ppPoolDefaults[SCHATTR_Z_AXIS_STEP_HELP			- SCHATTR_START] = new SvxDoubleItem(0.0, SCHATTR_Z_AXIS_STEP_HELP);
/*N*/ 	ppPoolDefaults[SCHATTR_Z_AXIS_LOGARITHM			- SCHATTR_START] = new SfxBoolItem(SCHATTR_Z_AXIS_LOGARITHM);
/*N*/ 	ppPoolDefaults[SCHATTR_Z_AXIS_AUTO_ORIGIN		- SCHATTR_START] = new SfxBoolItem(SCHATTR_Z_AXIS_AUTO_ORIGIN);
/*N*/ 	ppPoolDefaults[SCHATTR_Z_AXIS_ORIGIN			- SCHATTR_START] = new SvxDoubleItem(0.0, SCHATTR_Z_AXIS_ORIGIN);
/*N*/ 
/*N*/ 	ppPoolDefaults[SCHATTR_AXISTYPE      			- SCHATTR_START] = new SfxInt32Item(SCHATTR_AXISTYPE, CHART_AXIS_X);
/*N*/ 	ppPoolDefaults[SCHATTR_DUMMY0		         	- SCHATTR_START] = new SfxInt32Item(SCHATTR_DUMMY0, 0);
/*N*/ 	ppPoolDefaults[SCHATTR_DUMMY1       			- SCHATTR_START] = new SfxInt32Item(SCHATTR_DUMMY1, 0);
/*N*/ 	ppPoolDefaults[SCHATTR_DUMMY2		        	- SCHATTR_START] = new SfxInt32Item(SCHATTR_DUMMY2, 0);
/*N*/ 	ppPoolDefaults[SCHATTR_DUMMY3	         		- SCHATTR_START] = new SfxInt32Item(SCHATTR_DUMMY3, 0);
/*N*/ 	ppPoolDefaults[SCHATTR_DUMMY_END		        - SCHATTR_START] = new SfxInt32Item(SCHATTR_DUMMY_END, 0);
/*N*/ 
/*N*/ 	ppPoolDefaults[SCHATTR_STAT_AVERAGE             - SCHATTR_START] = new SfxBoolItem (SCHATTR_STAT_AVERAGE);
/*N*/ 	ppPoolDefaults[SCHATTR_STAT_KIND_ERROR          - SCHATTR_START] = new SfxInt32Item (SCHATTR_STAT_KIND_ERROR, 0);
/*N*/ 	ppPoolDefaults[SCHATTR_STAT_PERCENT             - SCHATTR_START] = new SvxDoubleItem (0.0, SCHATTR_STAT_PERCENT);
/*N*/ 	ppPoolDefaults[SCHATTR_STAT_BIGERROR            - SCHATTR_START] = new SvxDoubleItem (0.0, SCHATTR_STAT_BIGERROR);
/*N*/ 	ppPoolDefaults[SCHATTR_STAT_CONSTPLUS           - SCHATTR_START] = new SvxDoubleItem (0.0, SCHATTR_STAT_CONSTPLUS);
/*N*/ 	ppPoolDefaults[SCHATTR_STAT_CONSTMINUS          - SCHATTR_START] = new SvxDoubleItem (0.0, SCHATTR_STAT_CONSTMINUS);
/*N*/ 	ppPoolDefaults[SCHATTR_STAT_REGRESSTYPE         - SCHATTR_START] = new SfxInt32Item (SCHATTR_STAT_REGRESSTYPE, 0);
/*N*/ 	ppPoolDefaults[SCHATTR_STAT_INDICATE            - SCHATTR_START] = new SfxInt32Item (SCHATTR_STAT_INDICATE, 0);
/*N*/ 
/*N*/ 	ppPoolDefaults[SCHATTR_TEXT_DEGREES				- SCHATTR_START] = new SfxInt32Item(SCHATTR_TEXT_DEGREES, 0);
/*N*/ 	ppPoolDefaults[SCHATTR_TEXT_OVERLAP	        	- SCHATTR_START] = new SfxBoolItem(SCHATTR_TEXT_OVERLAP,FALSE);
/*N*/ 	ppPoolDefaults[SCHATTR_TEXT_DUMMY0		       	- SCHATTR_START] = new SfxInt32Item(SCHATTR_TEXT_DUMMY0, 0);
/*N*/ 	ppPoolDefaults[SCHATTR_TEXT_DUMMY1      		- SCHATTR_START] = new SfxInt32Item(SCHATTR_TEXT_DUMMY1, 0);
/*N*/ 	ppPoolDefaults[SCHATTR_TEXT_DUMMY2		      	- SCHATTR_START] = new SfxInt32Item(SCHATTR_TEXT_DUMMY2, 0);
/*N*/ 	ppPoolDefaults[SCHATTR_TEXT_DUMMY3	       		- SCHATTR_START] = new SfxInt32Item(SCHATTR_TEXT_DUMMY3, 0);
/*N*/ 
/*N*/ 
/*N*/ 	ppPoolDefaults[SCHATTR_STYLE_DEEP     - SCHATTR_START] = new SfxBoolItem (SCHATTR_STYLE_DEEP, 0);
/*N*/ 	ppPoolDefaults[SCHATTR_STYLE_3D       - SCHATTR_START] = new SfxBoolItem (SCHATTR_STYLE_3D, 0);
/*N*/ 	ppPoolDefaults[SCHATTR_STYLE_VERTICAL - SCHATTR_START] = new SfxBoolItem (SCHATTR_STYLE_VERTICAL, 0);
/*N*/ 	ppPoolDefaults[SCHATTR_STYLE_BASETYPE - SCHATTR_START] = new SfxInt32Item(SCHATTR_STYLE_BASETYPE, 0);
/*N*/ 	ppPoolDefaults[SCHATTR_STYLE_LINES    - SCHATTR_START] = new SfxBoolItem (SCHATTR_STYLE_LINES, 0);
/*N*/ 	ppPoolDefaults[SCHATTR_STYLE_PERCENT  - SCHATTR_START] = new SfxBoolItem (SCHATTR_STYLE_PERCENT, 0);
/*N*/ 	ppPoolDefaults[SCHATTR_STYLE_STACKED  - SCHATTR_START] = new SfxBoolItem (SCHATTR_STYLE_STACKED, 0);
/*N*/ 	ppPoolDefaults[SCHATTR_STYLE_SPLINES  - SCHATTR_START] = new SfxInt32Item (SCHATTR_STYLE_SPLINES, 0); //Bug: war Bool! ->Fileformat testen (betrifft nur 5er)
/*N*/ 	ppPoolDefaults[SCHATTR_STYLE_SYMBOL   - SCHATTR_START] = new SfxInt32Item (SCHATTR_STYLE_SYMBOL, 0);
/*N*/ 	ppPoolDefaults[SCHATTR_STYLE_SHAPE    - SCHATTR_START] = new SfxInt32Item (SCHATTR_STYLE_SHAPE, 0);
/*N*/ 
/*N*/ 	ppPoolDefaults[SCHATTR_AXIS					- SCHATTR_START] = new SfxInt32Item(SCHATTR_AXIS,2); //2 = Y-Achse!!!
/*N*/ 
/*N*/ 	ppPoolDefaults[SCHATTR_AXIS_AUTO_MIN		- SCHATTR_START] = new SfxBoolItem(SCHATTR_AXIS_AUTO_MIN);
/*N*/ 	ppPoolDefaults[SCHATTR_AXIS_MIN				- SCHATTR_START] = new SvxDoubleItem(0.0, SCHATTR_AXIS_MIN);
/*N*/ 	ppPoolDefaults[SCHATTR_AXIS_AUTO_MAX	  	- SCHATTR_START] = new SfxBoolItem(SCHATTR_AXIS_AUTO_MAX);
/*N*/ 	ppPoolDefaults[SCHATTR_AXIS_MAX				- SCHATTR_START] = new SvxDoubleItem(0.0, SCHATTR_AXIS_MAX);
/*N*/ 	ppPoolDefaults[SCHATTR_AXIS_AUTO_STEP_MAIN	- SCHATTR_START] = new SfxBoolItem(SCHATTR_AXIS_AUTO_STEP_MAIN);
/*N*/ 	ppPoolDefaults[SCHATTR_AXIS_STEP_MAIN		- SCHATTR_START] = new SvxDoubleItem(0.0, SCHATTR_AXIS_STEP_MAIN);
/*N*/ 	ppPoolDefaults[SCHATTR_AXIS_AUTO_STEP_HELP	- SCHATTR_START] = new SfxBoolItem(SCHATTR_AXIS_AUTO_STEP_HELP);
/*N*/ 	ppPoolDefaults[SCHATTR_AXIS_STEP_HELP		- SCHATTR_START] = new SvxDoubleItem(0.0, SCHATTR_AXIS_STEP_HELP);
/*N*/ 	ppPoolDefaults[SCHATTR_AXIS_LOGARITHM		- SCHATTR_START] = new SfxBoolItem(SCHATTR_AXIS_LOGARITHM);
/*N*/ 	ppPoolDefaults[SCHATTR_AXIS_AUTO_ORIGIN		- SCHATTR_START] = new SfxBoolItem(SCHATTR_AXIS_AUTO_ORIGIN);
/*N*/ 	ppPoolDefaults[SCHATTR_AXIS_ORIGIN			- SCHATTR_START] = new SvxDoubleItem(0.0, SCHATTR_AXIS_ORIGIN);
/*N*/ 
/*N*/ 	ppPoolDefaults[SCHATTR_AXIS_TICKS			- SCHATTR_START] = new SfxInt32Item(SCHATTR_AXIS_TICKS,CHAXIS_MARK_OUTER);
/*N*/ 	ppPoolDefaults[SCHATTR_AXIS_HELPTICKS		- SCHATTR_START] = new SfxInt32Item(SCHATTR_AXIS_HELPTICKS,0);
/*N*/ 	ppPoolDefaults[SCHATTR_AXIS_NUMFMT			- SCHATTR_START] = new SfxUInt32Item(SCHATTR_AXIS_NUMFMT,0);
/*N*/ 	ppPoolDefaults[SCHATTR_AXIS_NUMFMTPERCENT	- SCHATTR_START] = new SfxUInt32Item(SCHATTR_AXIS_NUMFMTPERCENT,11);
/*N*/ 	ppPoolDefaults[SCHATTR_AXIS_SHOWAXIS		- SCHATTR_START] = new SfxBoolItem(SCHATTR_AXIS_SHOWAXIS,0);
/*N*/ 	ppPoolDefaults[SCHATTR_AXIS_SHOWDESCR		- SCHATTR_START] = new SfxBoolItem(SCHATTR_AXIS_SHOWDESCR,0);
/*N*/ 	ppPoolDefaults[SCHATTR_AXIS_SHOWMAINGRID	- SCHATTR_START] = new SfxBoolItem(SCHATTR_AXIS_SHOWMAINGRID,0);
/*N*/ 	ppPoolDefaults[SCHATTR_AXIS_SHOWHELPGRID	- SCHATTR_START] = new SfxBoolItem(SCHATTR_AXIS_SHOWHELPGRID,0);
/*N*/ 	ppPoolDefaults[SCHATTR_AXIS_TOPDOWN			- SCHATTR_START] = new SfxBoolItem(SCHATTR_AXIS_TOPDOWN,0);
/*N*/ 
/*N*/ 	ppPoolDefaults[SCHATTR_AXIS_DUMMY0			- SCHATTR_START] = new SfxInt32Item(SCHATTR_AXIS_DUMMY0,0);
/*N*/ 	ppPoolDefaults[SCHATTR_AXIS_DUMMY1			- SCHATTR_START] = new SfxInt32Item(SCHATTR_AXIS_DUMMY1,0);
/*N*/ 	ppPoolDefaults[SCHATTR_AXIS_DUMMY2			- SCHATTR_START] = new SfxInt32Item(SCHATTR_AXIS_DUMMY2,0);
/*N*/ 	ppPoolDefaults[SCHATTR_AXIS_DUMMY3			- SCHATTR_START] = new SfxInt32Item(SCHATTR_AXIS_DUMMY3,0);
/*N*/ 	ppPoolDefaults[SCHATTR_BAR_OVERLAP			- SCHATTR_START] = new SfxInt32Item(SCHATTR_BAR_OVERLAP,0);
/*N*/ 	ppPoolDefaults[SCHATTR_BAR_GAPWIDTH			- SCHATTR_START] = new SfxInt32Item(SCHATTR_BAR_GAPWIDTH,0);
/*N*/ 
/*N*/ 	ppPoolDefaults[SCHATTR_SYMBOL_BRUSH			- SCHATTR_START] = new SvxBrushItem(SCHATTR_SYMBOL_BRUSH);
/*N*/ 
/*N*/ 	ppPoolDefaults[SCHATTR_STOCK_VOLUME 		- SCHATTR_START] = new SfxBoolItem(SCHATTR_STOCK_VOLUME,0);
/*N*/ 	ppPoolDefaults[SCHATTR_STOCK_UPDOWN			- SCHATTR_START] = new SfxBoolItem(SCHATTR_STOCK_UPDOWN,0);
/*N*/ 
/*N*/ 	ppPoolDefaults[SCHATTR_SYMBOL_SIZE			- SCHATTR_START] = new SvxSizeItem(SCHATTR_SYMBOL_SIZE,Size(0,0));
/*N*/ 	ppPoolDefaults[SCHATTR_USER_DEFINED_ATTR	- SCHATTR_START] = new SvXMLAttrContainerItem( SCHATTR_USER_DEFINED_ATTR );
/*N*/ 
     /**************************************************************************
     * ItemInfos
     **************************************************************************/
/*N*/ 	pItemInfos = new SfxItemInfo[SCHATTR_END - SCHATTR_START + 1];
/*N*/ 
/*N*/     USHORT i;
/*N*/ 	for( i = SCHATTR_START; i <= SCHATTR_END; i++ )
/*N*/ 	{
/*N*/ 		pItemInfos[i - SCHATTR_START]._nSID = 0;
/*N*/ 		pItemInfos[i - SCHATTR_START]._nFlags = SFX_ITEM_POOLABLE;
/*N*/ 	}
/*N*/ 
/*N*/     // non-persistent items
/*N*/     for( i = SCHATTR_NONPERSISTENT_START; i <= SCHATTR_NONPERSISTENT_END; i++ )
/*N*/     {
/*N*/         pItemInfos[ i - SCHATTR_START ]._nFlags = 0;
/*N*/     }
/*N*/ 
/*N*/     // slot ids differing from which ids
/*N*/ 	pItemInfos[SCHATTR_LEGEND_POS - SCHATTR_START]._nSID = CHATTR_LEGEND_POS;
/*N*/ 	pItemInfos[SCHATTR_SYMBOL_BRUSH - SCHATTR_START]._nSID = SID_ATTR_BRUSH;
/*N*/ 	pItemInfos[SCHATTR_STYLE_SYMBOL - SCHATTR_START]._nSID = SID_ATTR_SYMBOLTYPE;
/*N*/ 	pItemInfos[SCHATTR_SYMBOL_SIZE - SCHATTR_START]._nSID  = SID_ATTR_SYMBOLSIZE;
/*N*/ 
/*N*/ 	SetDefaults(ppPoolDefaults);
/*N*/ 	SetItemInfos(pItemInfos);
/*N*/ }

/*************************************************************************
|*
|* Kopier-Konstruktor, sorgt dafuer, dass die static defaults geclont
|* werden (Parameter 2 = TRUE)
|*
\************************************************************************/


/*************************************************************************
|*
|* Destruktor
|*
\************************************************************************/

/*N*/ SchItemPool::~SchItemPool()
/*N*/ {
/*N*/ 	Delete();
/*N*/ 
/*N*/ 	delete[] pItemInfos;
/*N*/ 
/*N*/ 	SetRefCount(*ppPoolDefaults[SCHATTR_DATADESCR_DESCR          - SCHATTR_START], 0);
/*N*/ 	delete	ppPoolDefaults[SCHATTR_DATADESCR_DESCR			- SCHATTR_START];
/*N*/ 	SetRefCount(*ppPoolDefaults[SCHATTR_DATADESCR_SHOW_SYM		- SCHATTR_START], 0);
/*N*/ 	delete	ppPoolDefaults[SCHATTR_DATADESCR_SHOW_SYM		- SCHATTR_START];
/*N*/ 	SetRefCount(*ppPoolDefaults[SCHATTR_LEGEND_POS				- SCHATTR_START], 0);
/*N*/ 	delete	ppPoolDefaults[SCHATTR_LEGEND_POS				- SCHATTR_START];
/*N*/ 	SetRefCount(*ppPoolDefaults[SCHATTR_TEXT_ORIENT				- SCHATTR_START], 0);
/*N*/ 	delete  ppPoolDefaults[SCHATTR_TEXT_ORIENT				- SCHATTR_START];
/*N*/ 	SetRefCount(*ppPoolDefaults[SCHATTR_TEXT_ORDER				- SCHATTR_START], 0);
/*N*/ 	delete  ppPoolDefaults[SCHATTR_TEXT_ORDER				- SCHATTR_START];
/*N*/ 	SetRefCount(*ppPoolDefaults[SCHATTR_TEXT_DEGREES 			- SCHATTR_START], 0);
/*N*/ 	delete  ppPoolDefaults[SCHATTR_TEXT_DEGREES				- SCHATTR_START];
/*N*/ 	SetRefCount(*ppPoolDefaults[SCHATTR_TEXT_OVERLAP 			- SCHATTR_START], 0);
/*N*/ 	delete  ppPoolDefaults[SCHATTR_TEXT_OVERLAP				- SCHATTR_START];
/*N*/ 
/*N*/ 	SetRefCount(*ppPoolDefaults[SCHATTR_Y_AXIS_AUTO_MIN			- SCHATTR_START], 0);
/*N*/ 	delete  ppPoolDefaults[SCHATTR_Y_AXIS_AUTO_MIN			- SCHATTR_START];
/*N*/ 	SetRefCount(*ppPoolDefaults[SCHATTR_Y_AXIS_MIN				- SCHATTR_START], 0);
/*N*/ 	delete  ppPoolDefaults[SCHATTR_Y_AXIS_MIN				- SCHATTR_START];
/*N*/ 	SetRefCount(*ppPoolDefaults[SCHATTR_Y_AXIS_AUTO_MAX	  		- SCHATTR_START], 0);
/*N*/ 	delete  ppPoolDefaults[SCHATTR_Y_AXIS_AUTO_MAX	  		- SCHATTR_START];
/*N*/ 	SetRefCount(*ppPoolDefaults[SCHATTR_Y_AXIS_MAX		  		- SCHATTR_START], 0);
/*N*/ 	delete  ppPoolDefaults[SCHATTR_Y_AXIS_MAX		  		- SCHATTR_START];
/*N*/ 	SetRefCount(*ppPoolDefaults[SCHATTR_Y_AXIS_AUTO_STEP_MAIN	- SCHATTR_START], 0);
/*N*/ 	delete  ppPoolDefaults[SCHATTR_Y_AXIS_AUTO_STEP_MAIN	- SCHATTR_START];
/*N*/ 	SetRefCount(*ppPoolDefaults[SCHATTR_Y_AXIS_STEP_MAIN			- SCHATTR_START], 0);
/*N*/ 	delete  ppPoolDefaults[SCHATTR_Y_AXIS_STEP_MAIN			- SCHATTR_START];
/*N*/ 	SetRefCount(*ppPoolDefaults[SCHATTR_Y_AXIS_AUTO_STEP_HELP	- SCHATTR_START], 0);
/*N*/ 	delete  ppPoolDefaults[SCHATTR_Y_AXIS_AUTO_STEP_HELP	- SCHATTR_START];
/*N*/ 	SetRefCount(*ppPoolDefaults[SCHATTR_Y_AXIS_STEP_HELP			- SCHATTR_START], 0);
/*N*/ 	delete  ppPoolDefaults[SCHATTR_Y_AXIS_STEP_HELP			- SCHATTR_START];
/*N*/ 	SetRefCount(*ppPoolDefaults[SCHATTR_Y_AXIS_LOGARITHM			- SCHATTR_START], 0);
/*N*/ 	delete  ppPoolDefaults[SCHATTR_Y_AXIS_LOGARITHM			- SCHATTR_START];
/*N*/ 	SetRefCount(*ppPoolDefaults[SCHATTR_Y_AXIS_AUTO_ORIGIN		- SCHATTR_START], 0);
/*N*/ 	delete  ppPoolDefaults[SCHATTR_Y_AXIS_AUTO_ORIGIN		- SCHATTR_START];
/*N*/ 	SetRefCount(*ppPoolDefaults[SCHATTR_Y_AXIS_ORIGIN			- SCHATTR_START], 0);
/*N*/ 	delete  ppPoolDefaults[SCHATTR_Y_AXIS_ORIGIN			- SCHATTR_START];
/*N*/ 
/*N*/ 	SetRefCount(*ppPoolDefaults[SCHATTR_X_AXIS_AUTO_MIN			- SCHATTR_START], 0);
/*N*/ 	delete  ppPoolDefaults[SCHATTR_X_AXIS_AUTO_MIN			- SCHATTR_START];
/*N*/ 	SetRefCount(*ppPoolDefaults[SCHATTR_X_AXIS_MIN				- SCHATTR_START], 0);
/*N*/ 	delete  ppPoolDefaults[SCHATTR_X_AXIS_MIN				- SCHATTR_START];
/*N*/ 	SetRefCount(*ppPoolDefaults[SCHATTR_X_AXIS_AUTO_MAX	  		- SCHATTR_START], 0);
/*N*/ 	delete  ppPoolDefaults[SCHATTR_X_AXIS_AUTO_MAX	  		- SCHATTR_START];
/*N*/ 	SetRefCount(*ppPoolDefaults[SCHATTR_X_AXIS_MAX		  		- SCHATTR_START], 0);
/*N*/ 	delete  ppPoolDefaults[SCHATTR_X_AXIS_MAX		  		- SCHATTR_START];
/*N*/ 	SetRefCount(*ppPoolDefaults[SCHATTR_X_AXIS_AUTO_STEP_MAIN	- SCHATTR_START], 0);
/*N*/ 	delete  ppPoolDefaults[SCHATTR_X_AXIS_AUTO_STEP_MAIN	- SCHATTR_START];
/*N*/ 	SetRefCount(*ppPoolDefaults[SCHATTR_X_AXIS_STEP_MAIN			- SCHATTR_START], 0);
/*N*/ 	delete  ppPoolDefaults[SCHATTR_X_AXIS_STEP_MAIN			- SCHATTR_START];
/*N*/ 	SetRefCount(*ppPoolDefaults[SCHATTR_X_AXIS_AUTO_STEP_HELP	- SCHATTR_START], 0);
/*N*/ 	delete  ppPoolDefaults[SCHATTR_X_AXIS_AUTO_STEP_HELP	- SCHATTR_START];
/*N*/ 	SetRefCount(*ppPoolDefaults[SCHATTR_X_AXIS_STEP_HELP			- SCHATTR_START], 0);
/*N*/ 	delete  ppPoolDefaults[SCHATTR_X_AXIS_STEP_HELP			- SCHATTR_START];
/*N*/ 	SetRefCount(*ppPoolDefaults[SCHATTR_X_AXIS_LOGARITHM			- SCHATTR_START], 0);
/*N*/ 	delete  ppPoolDefaults[SCHATTR_X_AXIS_LOGARITHM			- SCHATTR_START];
/*N*/ 	SetRefCount(*ppPoolDefaults[SCHATTR_X_AXIS_AUTO_ORIGIN		- SCHATTR_START], 0);
/*N*/ 	delete  ppPoolDefaults[SCHATTR_X_AXIS_AUTO_ORIGIN		- SCHATTR_START];
/*N*/ 	SetRefCount(*ppPoolDefaults[SCHATTR_X_AXIS_ORIGIN			- SCHATTR_START], 0);
/*N*/ 	delete  ppPoolDefaults[SCHATTR_X_AXIS_ORIGIN			- SCHATTR_START];
/*N*/ 
/*N*/ 	SetRefCount(*ppPoolDefaults[SCHATTR_Z_AXIS_AUTO_MIN			- SCHATTR_START], 0);
/*N*/ 	delete  ppPoolDefaults[SCHATTR_Z_AXIS_AUTO_MIN			- SCHATTR_START];
/*N*/ 	SetRefCount(*ppPoolDefaults[SCHATTR_Z_AXIS_MIN				- SCHATTR_START], 0);
/*N*/ 	delete  ppPoolDefaults[SCHATTR_Z_AXIS_MIN				- SCHATTR_START];
/*N*/ 	SetRefCount(*ppPoolDefaults[SCHATTR_Z_AXIS_AUTO_MAX	  		- SCHATTR_START], 0);
/*N*/ 	delete  ppPoolDefaults[SCHATTR_Z_AXIS_AUTO_MAX	  		- SCHATTR_START];
/*N*/ 	SetRefCount(*ppPoolDefaults[SCHATTR_Z_AXIS_MAX		  		- SCHATTR_START], 0);
/*N*/ 	delete  ppPoolDefaults[SCHATTR_Z_AXIS_MAX		  		- SCHATTR_START];
/*N*/ 	SetRefCount(*ppPoolDefaults[SCHATTR_Z_AXIS_AUTO_STEP_MAIN	- SCHATTR_START], 0);
/*N*/ 	delete  ppPoolDefaults[SCHATTR_Z_AXIS_AUTO_STEP_MAIN	- SCHATTR_START];
/*N*/ 	SetRefCount(*ppPoolDefaults[SCHATTR_Z_AXIS_STEP_MAIN			- SCHATTR_START], 0);
/*N*/ 	delete  ppPoolDefaults[SCHATTR_Z_AXIS_STEP_MAIN			- SCHATTR_START];
/*N*/ 	SetRefCount(*ppPoolDefaults[SCHATTR_Z_AXIS_AUTO_STEP_HELP	- SCHATTR_START], 0);
/*N*/ 	delete  ppPoolDefaults[SCHATTR_Z_AXIS_AUTO_STEP_HELP	- SCHATTR_START];
/*N*/ 	SetRefCount(*ppPoolDefaults[SCHATTR_Z_AXIS_STEP_HELP			- SCHATTR_START], 0);
/*N*/ 	delete  ppPoolDefaults[SCHATTR_Z_AXIS_STEP_HELP			- SCHATTR_START];
/*N*/ 	SetRefCount(*ppPoolDefaults[SCHATTR_Z_AXIS_LOGARITHM			- SCHATTR_START], 0);
/*N*/ 	delete  ppPoolDefaults[SCHATTR_Z_AXIS_LOGARITHM			- SCHATTR_START];
/*N*/ 	SetRefCount(*ppPoolDefaults[SCHATTR_Z_AXIS_AUTO_ORIGIN		- SCHATTR_START], 0);
/*N*/ 	delete  ppPoolDefaults[SCHATTR_Z_AXIS_AUTO_ORIGIN		- SCHATTR_START];
/*N*/ 	SetRefCount(*ppPoolDefaults[SCHATTR_Z_AXIS_ORIGIN			- SCHATTR_START], 0);
/*N*/ 	delete  ppPoolDefaults[SCHATTR_Z_AXIS_ORIGIN			- SCHATTR_START];
/*N*/ 
/*N*/ 	SetRefCount(*ppPoolDefaults[SCHATTR_AXISTYPE      			- SCHATTR_START], 0);
/*N*/ 	delete  ppPoolDefaults[SCHATTR_AXISTYPE      			- SCHATTR_START];
/*N*/ 	SetRefCount(*ppPoolDefaults[SCHATTR_DUMMY0		         	- SCHATTR_START], 0);
/*N*/ 	delete  ppPoolDefaults[SCHATTR_DUMMY0		         	- SCHATTR_START];
/*N*/ 	SetRefCount(*ppPoolDefaults[SCHATTR_DUMMY1       			- SCHATTR_START], 0);
/*N*/ 	delete  ppPoolDefaults[SCHATTR_DUMMY1       			- SCHATTR_START];
/*N*/ 	SetRefCount(*ppPoolDefaults[SCHATTR_DUMMY2		        	- SCHATTR_START], 0);
/*N*/ 	delete  ppPoolDefaults[SCHATTR_DUMMY2		        	- SCHATTR_START];
/*N*/ 	SetRefCount(*ppPoolDefaults[SCHATTR_DUMMY3	         		- SCHATTR_START], 0);
/*N*/ 	delete  ppPoolDefaults[SCHATTR_DUMMY3	         		- SCHATTR_START];
/*N*/ 	SetRefCount(*ppPoolDefaults[SCHATTR_DUMMY_END		        - SCHATTR_START], 0);
/*N*/ 	delete  ppPoolDefaults[SCHATTR_DUMMY_END		        - SCHATTR_START];
/*N*/ 
/*N*/ 	SetRefCount(*ppPoolDefaults[SCHATTR_STAT_AVERAGE             - SCHATTR_START], 0);
/*N*/ 	delete  ppPoolDefaults[SCHATTR_STAT_AVERAGE             - SCHATTR_START];
/*N*/ 	SetRefCount(*ppPoolDefaults[SCHATTR_STAT_KIND_ERROR          - SCHATTR_START], 0);
/*N*/ 	delete  ppPoolDefaults[SCHATTR_STAT_KIND_ERROR          - SCHATTR_START];
/*N*/ 	SetRefCount(*ppPoolDefaults[SCHATTR_STAT_PERCENT             - SCHATTR_START], 0);
/*N*/ 	delete  ppPoolDefaults[SCHATTR_STAT_PERCENT             - SCHATTR_START];
/*N*/ 	SetRefCount(*ppPoolDefaults[SCHATTR_STAT_BIGERROR            - SCHATTR_START], 0);
/*N*/ 	delete  ppPoolDefaults[SCHATTR_STAT_BIGERROR            - SCHATTR_START];
/*N*/ 	SetRefCount(*ppPoolDefaults[SCHATTR_STAT_CONSTPLUS           - SCHATTR_START], 0);
/*N*/ 	delete  ppPoolDefaults[SCHATTR_STAT_CONSTPLUS           - SCHATTR_START];
/*N*/ 	SetRefCount(*ppPoolDefaults[SCHATTR_STAT_CONSTMINUS          - SCHATTR_START], 0);
/*N*/ 	delete  ppPoolDefaults[SCHATTR_STAT_CONSTMINUS          - SCHATTR_START];
/*N*/ 	SetRefCount(*ppPoolDefaults[SCHATTR_STAT_INDICATE            - SCHATTR_START], 0);
/*N*/ 	delete  ppPoolDefaults[SCHATTR_STAT_INDICATE            - SCHATTR_START];
/*N*/ 	SetRefCount(*ppPoolDefaults[SCHATTR_STAT_REGRESSTYPE         - SCHATTR_START], 0);
/*N*/ 	delete  ppPoolDefaults[SCHATTR_STAT_REGRESSTYPE         - SCHATTR_START];
/*N*/ 
/*N*/ 
/*N*/ 
/*N*/ 
/*N*/ 	SetRefCount(*ppPoolDefaults[SCHATTR_STYLE_DEEP     - SCHATTR_START],0);
/*N*/ 	SetRefCount(*ppPoolDefaults[SCHATTR_STYLE_3D       - SCHATTR_START],0);
/*N*/ 	SetRefCount(*ppPoolDefaults[SCHATTR_STYLE_VERTICAL - SCHATTR_START],0);
/*N*/ 	SetRefCount(*ppPoolDefaults[SCHATTR_STYLE_BASETYPE - SCHATTR_START],0);
/*N*/ 	SetRefCount(*ppPoolDefaults[SCHATTR_STYLE_LINES    - SCHATTR_START],0);
/*N*/ 	SetRefCount(*ppPoolDefaults[SCHATTR_STYLE_PERCENT  - SCHATTR_START],0);
/*N*/ 	SetRefCount(*ppPoolDefaults[SCHATTR_STYLE_STACKED  - SCHATTR_START],0);
/*N*/ 	SetRefCount(*ppPoolDefaults[SCHATTR_STYLE_SPLINES  - SCHATTR_START],0);
/*N*/ 	SetRefCount(*ppPoolDefaults[SCHATTR_STYLE_SYMBOL   - SCHATTR_START],0);
/*N*/ 	SetRefCount(*ppPoolDefaults[SCHATTR_STYLE_SHAPE    - SCHATTR_START],0);
/*N*/ 
/*N*/ 	delete  ppPoolDefaults[SCHATTR_STYLE_DEEP     - SCHATTR_START];
/*N*/ 	delete  ppPoolDefaults[SCHATTR_STYLE_3D       - SCHATTR_START];
/*N*/ 	delete  ppPoolDefaults[SCHATTR_STYLE_VERTICAL - SCHATTR_START];
/*N*/ 	delete  ppPoolDefaults[SCHATTR_STYLE_BASETYPE - SCHATTR_START];
/*N*/ 	delete  ppPoolDefaults[SCHATTR_STYLE_LINES    - SCHATTR_START];
/*N*/ 	delete  ppPoolDefaults[SCHATTR_STYLE_PERCENT  - SCHATTR_START];
/*N*/ 	delete  ppPoolDefaults[SCHATTR_STYLE_STACKED  - SCHATTR_START];
/*N*/ 	delete  ppPoolDefaults[SCHATTR_STYLE_SPLINES  - SCHATTR_START];
/*N*/ 	delete  ppPoolDefaults[SCHATTR_STYLE_SYMBOL   - SCHATTR_START];
/*N*/ 	delete  ppPoolDefaults[SCHATTR_STYLE_SHAPE    - SCHATTR_START];
/*N*/ 
/*N*/ 	SetRefCount(*ppPoolDefaults[SCHATTR_TEXT_DUMMY0 	- SCHATTR_START], 0);
/*N*/ 	delete  ppPoolDefaults[SCHATTR_TEXT_DUMMY0 	- SCHATTR_START];
/*N*/ 	SetRefCount(*ppPoolDefaults[SCHATTR_TEXT_DUMMY1  - SCHATTR_START], 0);
/*N*/ 	delete  ppPoolDefaults[SCHATTR_TEXT_DUMMY1  - SCHATTR_START];
/*N*/ 	SetRefCount(*ppPoolDefaults[SCHATTR_TEXT_DUMMY2	- SCHATTR_START], 0);
/*N*/ 	delete  ppPoolDefaults[SCHATTR_TEXT_DUMMY2	- SCHATTR_START];
/*N*/ 	SetRefCount(*ppPoolDefaults[SCHATTR_TEXT_DUMMY3	- SCHATTR_START], 0);
/*N*/ 	delete  ppPoolDefaults[SCHATTR_TEXT_DUMMY3	- SCHATTR_START];
/*N*/ 
/*N*/ 	SetRefCount(*ppPoolDefaults[SCHATTR_AXIS_AUTO_MIN		- SCHATTR_START], 0);
/*N*/ 	delete  ppPoolDefaults[SCHATTR_AXIS_AUTO_MIN		- SCHATTR_START];
/*N*/ 	SetRefCount(*ppPoolDefaults[SCHATTR_AXIS_MIN				- SCHATTR_START], 0);
/*N*/ 	delete  ppPoolDefaults[SCHATTR_AXIS_MIN				- SCHATTR_START];
/*N*/ 	SetRefCount(*ppPoolDefaults[SCHATTR_AXIS_AUTO_MAX		- SCHATTR_START], 0);
/*N*/ 	delete  ppPoolDefaults[SCHATTR_AXIS_AUTO_MAX		- SCHATTR_START];
/*N*/ 	SetRefCount(*ppPoolDefaults[SCHATTR_AXIS_MAX		  		- SCHATTR_START], 0);
/*N*/ 	delete  ppPoolDefaults[SCHATTR_AXIS_MAX		  		- SCHATTR_START];
/*N*/ 	SetRefCount(*ppPoolDefaults[SCHATTR_AXIS_AUTO_STEP_MAIN	- SCHATTR_START], 0);
/*N*/ 	delete  ppPoolDefaults[SCHATTR_AXIS_AUTO_STEP_MAIN	- SCHATTR_START];
/*N*/ 	SetRefCount(*ppPoolDefaults[SCHATTR_AXIS_STEP_MAIN		- SCHATTR_START], 0);
/*N*/ 	delete  ppPoolDefaults[SCHATTR_AXIS_STEP_MAIN		- SCHATTR_START];
/*N*/ 	SetRefCount(*ppPoolDefaults[SCHATTR_AXIS_AUTO_STEP_HELP	- SCHATTR_START], 0);
/*N*/ 	delete  ppPoolDefaults[SCHATTR_AXIS_AUTO_STEP_HELP	- SCHATTR_START];
/*N*/ 	SetRefCount(*ppPoolDefaults[SCHATTR_AXIS_STEP_HELP		- SCHATTR_START], 0);
/*N*/ 	delete  ppPoolDefaults[SCHATTR_AXIS_STEP_HELP		- SCHATTR_START];
/*N*/ 	SetRefCount(*ppPoolDefaults[SCHATTR_AXIS_LOGARITHM		- SCHATTR_START], 0);
/*N*/ 	delete  ppPoolDefaults[SCHATTR_AXIS_LOGARITHM		- SCHATTR_START];
/*N*/ 	SetRefCount(*ppPoolDefaults[SCHATTR_AXIS_AUTO_ORIGIN		- SCHATTR_START], 0);
/*N*/ 	delete  ppPoolDefaults[SCHATTR_AXIS_AUTO_ORIGIN		- SCHATTR_START];
/*N*/ 	SetRefCount(*ppPoolDefaults[SCHATTR_AXIS_ORIGIN			- SCHATTR_START], 0);
/*N*/ 	delete  ppPoolDefaults[SCHATTR_AXIS_ORIGIN			- SCHATTR_START];
/*N*/ 
/*N*/ 	SetRefCount(*ppPoolDefaults[SCHATTR_AXIS					- SCHATTR_START], 0);
/*N*/ 	delete  ppPoolDefaults[SCHATTR_AXIS					- SCHATTR_START];
/*N*/ 	SetRefCount(*ppPoolDefaults[SCHATTR_AXIS_TICKS			- SCHATTR_START], 0);
/*N*/ 	delete  ppPoolDefaults[SCHATTR_AXIS_TICKS			- SCHATTR_START];
/*N*/ 	SetRefCount(*ppPoolDefaults[SCHATTR_AXIS_HELPTICKS		- SCHATTR_START], 0);
/*N*/ 	delete  ppPoolDefaults[SCHATTR_AXIS_HELPTICKS		- SCHATTR_START];
/*N*/ 	SetRefCount(*ppPoolDefaults[SCHATTR_AXIS_NUMFMT			- SCHATTR_START], 0);
/*N*/ 	delete  ppPoolDefaults[SCHATTR_AXIS_NUMFMT			- SCHATTR_START];
/*N*/ 	SetRefCount(*ppPoolDefaults[SCHATTR_AXIS_NUMFMTPERCENT	- SCHATTR_START], 0);
/*N*/ 	delete  ppPoolDefaults[SCHATTR_AXIS_NUMFMTPERCENT	- SCHATTR_START];
/*N*/ 	SetRefCount(*ppPoolDefaults[SCHATTR_AXIS_SHOWAXIS		- SCHATTR_START], 0);
/*N*/ 	delete  ppPoolDefaults[SCHATTR_AXIS_SHOWAXIS		- SCHATTR_START];
/*N*/ 	SetRefCount(*ppPoolDefaults[SCHATTR_AXIS_SHOWDESCR		- SCHATTR_START], 0);
/*N*/ 	delete  ppPoolDefaults[SCHATTR_AXIS_SHOWDESCR		- SCHATTR_START];
/*N*/ 	SetRefCount(*ppPoolDefaults[SCHATTR_AXIS_SHOWMAINGRID	- SCHATTR_START], 0);
/*N*/ 	delete  ppPoolDefaults[SCHATTR_AXIS_SHOWMAINGRID	- SCHATTR_START];
/*N*/ 	SetRefCount(*ppPoolDefaults[SCHATTR_AXIS_SHOWHELPGRID	- SCHATTR_START], 0);
/*N*/ 	delete  ppPoolDefaults[SCHATTR_AXIS_SHOWHELPGRID	- SCHATTR_START];
/*N*/ 	SetRefCount(*ppPoolDefaults[SCHATTR_AXIS_TOPDOWN			- SCHATTR_START], 0);
/*N*/ 	delete  ppPoolDefaults[SCHATTR_AXIS_TOPDOWN			- SCHATTR_START];
/*N*/ 
/*N*/ 	SetRefCount(*ppPoolDefaults[SCHATTR_AXIS_DUMMY0			- SCHATTR_START], 0);
/*N*/ 	delete  ppPoolDefaults[SCHATTR_AXIS_DUMMY0			- SCHATTR_START];
/*N*/ 	SetRefCount(*ppPoolDefaults[SCHATTR_AXIS_DUMMY1			- SCHATTR_START], 0);
/*N*/ 	delete  ppPoolDefaults[SCHATTR_AXIS_DUMMY1			- SCHATTR_START];
/*N*/ 	SetRefCount(*ppPoolDefaults[SCHATTR_AXIS_DUMMY2			- SCHATTR_START], 0);
/*N*/ 	delete  ppPoolDefaults[SCHATTR_AXIS_DUMMY2			- SCHATTR_START];
/*N*/ 	SetRefCount(*ppPoolDefaults[SCHATTR_AXIS_DUMMY3			- SCHATTR_START], 0);
/*N*/ 	delete  ppPoolDefaults[SCHATTR_AXIS_DUMMY3			- SCHATTR_START];
/*N*/ 	SetRefCount(*ppPoolDefaults[SCHATTR_BAR_OVERLAP			- SCHATTR_START], 0);
/*N*/ 	delete  ppPoolDefaults[SCHATTR_BAR_OVERLAP			- SCHATTR_START];
/*N*/ 	SetRefCount(*ppPoolDefaults[SCHATTR_BAR_GAPWIDTH			- SCHATTR_START], 0);
/*N*/ 	delete  ppPoolDefaults[SCHATTR_BAR_GAPWIDTH			- SCHATTR_START];
/*N*/ 	SetRefCount(*ppPoolDefaults[SCHATTR_SYMBOL_BRUSH			- SCHATTR_START], 0);
/*N*/ 	delete  ppPoolDefaults[SCHATTR_SYMBOL_BRUSH			- SCHATTR_START];
/*N*/ 
/*N*/ 
/*N*/ 	SetRefCount(*ppPoolDefaults[SCHATTR_STOCK_UPDOWN			- SCHATTR_START], 0);
/*N*/ 	delete  ppPoolDefaults[SCHATTR_STOCK_UPDOWN			- SCHATTR_START];
/*N*/ 	SetRefCount(*ppPoolDefaults[SCHATTR_STOCK_VOLUME			- SCHATTR_START], 0);
/*N*/ 	delete  ppPoolDefaults[SCHATTR_STOCK_VOLUME			- SCHATTR_START];
/*N*/ 
/*N*/ 	SetRefCount(*ppPoolDefaults[SCHATTR_SYMBOL_SIZE			- SCHATTR_START], 0);
/*N*/ 	delete  ppPoolDefaults[SCHATTR_SYMBOL_SIZE			- SCHATTR_START];
/*N*/ 
/*N*/ 	SetRefCount(*ppPoolDefaults[SCHATTR_USER_DEFINED_ATTR    - SCHATTR_START], 0);
/*N*/ 	delete  ppPoolDefaults[SCHATTR_USER_DEFINED_ATTR    - SCHATTR_START];
/*N*/ 
/*N*/ 	delete[] ppPoolDefaults;
/*N*/ }

/*************************************************************************
|*
|* Clone()
|*
\************************************************************************/


/*************************************************************************
|*
|* Liefert fuer alle Which-Ids 100TH_MM als MapUnit
|*
\************************************************************************/




}
