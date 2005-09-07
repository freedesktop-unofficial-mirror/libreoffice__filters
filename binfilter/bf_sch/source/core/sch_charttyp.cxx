/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: sch_charttyp.cxx,v $
 *
 *  $Revision: 1.3 $
 *
 *  last change: $Author: rt $ $Date: 2005-09-07 21:51:20 $
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

#include "charttyp.hxx"

#include "schattr.hxx"
namespace binfilter {

/*------------------------------------------------------------------------

  Priorit�tenliste:
  -----------------


  3D      > 2D
     >
  Symbols,Splines > no Symbols,no Splines
     >
  Lines   > no Lines
     >
  Percent > Stacked > Normal


  Kompatiblit�tsklassen:

  1 XY-Chart       Hat X-Werte-Spalte
  2 Pie-Chart      keine Achse
  3 Line,Area,Bar  Achse, Symbol,Linie,Splines, ... (fast alles!)
  4 NetChart       ???

        3D   Line  Spline  Symbols Stacked Percent  Deep3D vertikal Errors
--------------------------------------------------------------------------
  1      x     X     X       X          - (x?) -      -      x        X
  2      X     -     -       -          ?      F      -      -        -
  3      x     X     ?       x          X      X      x      x        x
  4      -     F     -       X          X      X      -      -        -?


  X = schaltbar,vorhanden
  x = schaltbar, nicht (vollst.) vrhanden
  F = immer
  ? = weiss noch nicht
  - = gibts nicht
------------------------------------------------------------------------*/

/*N*/ void ChartType::Init()
/*N*/ {
/*N*/     bHasLines = FALSE;
/*N*/     bIsDonut = FALSE;
/*N*/     bIsPercent = FALSE;
/*N*/     bIs3D = FALSE;
/*N*/     bIsDeep3D = FALSE;
/*N*/     bIsVertical = FALSE;
/*N*/     bIsStacked = FALSE;
/*N*/     bHasVolume = FALSE;
/*N*/     bHasUpDown = FALSE;
/*N*/ 
/*N*/     nSymbolType = -2;
/*N*/ 	nShapeType = -1;
/*N*/ 
/*N*/     nSplineType = SPLINE_NONE;
/*N*/     nSpecialType = 0;
/*N*/ 
/*N*/ 	nBaseType = CHSTYLE_2D_COLUMN;
/*N*/ }

/* ************************************************************************
|*
|* SetType initialisiert die ganze Klasse aus einem SvxChartStyle-enum
|* ( = Konvertierung SvxChartStyle -> ChartType )
|*
\*********************************************************************** */
/*N*/ void ChartType::SetType(const ChartModel* pModel)
/*N*/ {
/*N*/ 	SetType(pModel->ChartStyle());
/*N*/ }
/*N*/ void ChartType::SetType(const SfxItemSet *pAttr)
/*N*/ {
/*N*/ 
/*N*/ 	const SfxPoolItem *pPoolItem = NULL;
/*N*/ 
/*N*/ 	if (pAttr->GetItemState(SCHATTR_STYLE_3D, TRUE, &pPoolItem) == SFX_ITEM_SET)
/*N*/ 		bIs3D=((const SfxBoolItem*) pPoolItem)->GetValue();
/*N*/ 
/*N*/ 	if (pAttr->GetItemState(SCHATTR_STYLE_DEEP, TRUE, &pPoolItem) == SFX_ITEM_SET)
/*N*/ 		bIsDeep3D=((const SfxBoolItem*) pPoolItem)->GetValue();
/*N*/ 
/*N*/ 	if (pAttr->GetItemState(SCHATTR_STYLE_VERTICAL, TRUE, &pPoolItem) == SFX_ITEM_SET)
/*N*/ 		bIsVertical=((const SfxBoolItem*) pPoolItem)->GetValue();
/*N*/ 
/*N*/ 	if (pAttr->GetItemState(SCHATTR_STYLE_LINES, TRUE, &pPoolItem) == SFX_ITEM_SET)
/*N*/ 		bHasLines=((const SfxBoolItem*) pPoolItem)->GetValue();
/*N*/ 
/*N*/ 	if (pAttr->GetItemState(SCHATTR_STYLE_PERCENT, TRUE, &pPoolItem) == SFX_ITEM_SET)
/*N*/ 		bIsPercent=((const SfxBoolItem*) pPoolItem)->GetValue();
/*N*/ 
/*N*/ 	if (pAttr->GetItemState(SCHATTR_STYLE_STACKED, TRUE, &pPoolItem) == SFX_ITEM_SET)
/*N*/ 		bIsStacked=((const SfxBoolItem*) pPoolItem)->GetValue();
/*N*/ 
/*N*/ 	if (pAttr->GetItemState(SCHATTR_STYLE_SPLINES, TRUE, &pPoolItem) == SFX_ITEM_SET)
/*N*/ 		nSplineType=((const SfxInt32Item*) pPoolItem)->GetValue();
/*N*/ 
/*N*/ 	if (pAttr->GetItemState(SCHATTR_STYLE_SYMBOL, TRUE, &pPoolItem) == SFX_ITEM_SET)
/*N*/ 		nSymbolType=((const SfxInt32Item*) pPoolItem)->GetValue();
/*N*/ 
/*N*/ 	if (pAttr->GetItemState(SCHATTR_STYLE_SHAPE, TRUE, &pPoolItem) == SFX_ITEM_SET)
/*N*/ 		nShapeType=((const SfxInt32Item*) pPoolItem)->GetValue();
/*N*/ 
/*N*/ 	if (pAttr->GetItemState(SCHATTR_STOCK_VOLUME, TRUE, &pPoolItem) == SFX_ITEM_SET)
/*N*/ 		bHasVolume=((const SfxBoolItem*) pPoolItem)->GetValue();
/*N*/ 
/*N*/ 	if (pAttr->GetItemState(SCHATTR_STOCK_UPDOWN, TRUE, &pPoolItem) == SFX_ITEM_SET)
/*N*/ 		bHasUpDown=((const SfxBoolItem*) pPoolItem)->GetValue();
/*N*/ 
/*N*/     // handle special types
/*N*/     //   4 : CHSTYLE_2D_LINE_COLUMN
/*N*/     //   5 : CHSTYLE_2D_LINE_STACKEDCOLUMN
/*N*/ 
/*N*/     if( 4 == nSpecialType )
/*N*/     {
/*N*/         // CHSTYLE_2D_LINE_COLUMN
/*N*/         if( bIsStacked )
/*N*/         {
/*N*/             // set to CHSTYLE_2D_LINE_STACKEDCOLUMN
/*N*/             nSpecialType = 5;
/*N*/         }
/*N*/     }
/*N*/     else if( 5 == nSpecialType )
/*N*/     {
/*N*/         // CHSTYLE_2D_LINE_STACKEDCOLUMN
/*N*/         if( ! bIsStacked )
/*N*/         {
/*N*/             // set to CHSTYLE_2D_LINE_COLUMN
/*N*/             nSpecialType = 4;
/*N*/         }
/*N*/     }
/*N*/ 
/*N*/     //Todo: extend list (?)
/*N*/ }

/*N*/ void ChartType::GetAttrSet(SfxItemSet *pAttr)
/*N*/ {
/*N*/ 	pAttr->Put(SfxBoolItem(SCHATTR_STOCK_VOLUME     ,bHasVolume));
/*N*/ 	pAttr->Put(SfxBoolItem(SCHATTR_STOCK_UPDOWN     ,bHasUpDown));
/*N*/ 	pAttr->Put(SfxBoolItem(SCHATTR_STYLE_3D         ,bIs3D));
/*N*/ 	pAttr->Put(SfxBoolItem(SCHATTR_STYLE_DEEP       ,bIsDeep3D));
/*N*/ 	pAttr->Put(SfxBoolItem(SCHATTR_STYLE_VERTICAL   ,bIsVertical));
/*N*/ 	pAttr->Put(SfxBoolItem(SCHATTR_STYLE_LINES      ,bHasLines));
/*N*/ 	pAttr->Put(SfxBoolItem(SCHATTR_STYLE_PERCENT    ,bIsPercent));
/*N*/ 	pAttr->Put(SfxBoolItem(SCHATTR_STYLE_STACKED    ,bIsStacked));
/*N*/ 	pAttr->Put(SfxInt32Item(SCHATTR_STYLE_SPLINES    ,nSplineType));
/*N*/ 	pAttr->Put(SfxInt32Item(SCHATTR_STYLE_SYMBOL     ,nSymbolType));
/*N*/ 	if(nShapeType!=-1)
/*N*/ 		pAttr->Put(SfxInt32Item(SCHATTR_STYLE_SHAPE      ,nShapeType));
/*N*/ 	//Todo: erweitern!
/*N*/ }
/*N*/ void ChartType::SetType(const SvxChartStyle eStyle)
/*N*/ {
/*N*/ 	nSymbolType = HasSymbols(eStyle) ? SVX_SYMBOLTYPE_AUTO : SVX_SYMBOLTYPE_NONE;
/*N*/ 	bIs3D       = Is3D(eStyle);
/*N*/ 	bIsStacked  = IsStacked(eStyle);
/*N*/ 	bIsPercent  = IsPercent(eStyle);
/*N*/ 	nBaseType   = GetBaseType(eStyle);
/*N*/ 	bIsDeep3D   = IsDeep3D(eStyle);
/*N*/ 	bIsVertical = IsVertical(eStyle);
/*N*/ 	nSplineType = GetSplineType(eStyle);
/*N*/ 	bIsDonut    = IsDonut(eStyle);
/*N*/ 	bHasLines	= HasLines(eStyle);
/*N*/ 
/*N*/ 
/*N*/ 
/*N*/ 	switch(eStyle)
/*N*/ 	{
/*N*/ 		case CHSTYLE_2D_PIE_SEGOF1:
/*N*/ 			nSpecialType=1;
/*N*/ 			break;
/*N*/ 		case CHSTYLE_2D_PIE_SEGOFALL:
/*N*/ 			nSpecialType=2;
/*N*/ 			break;
/*N*/ 		case CHSTYLE_2D_DONUT2:
/*N*/ 			nSpecialType=3;
/*N*/ 			break;
/*N*/ 		case CHSTYLE_2D_LINE_COLUMN:
/*N*/ 			nSpecialType=4;
/*N*/ 			break;
/*N*/ 		case CHSTYLE_2D_LINE_STACKEDCOLUMN:
/*N*/ 			nSpecialType=5;
/*N*/ 			break;
/*N*/ 		case CHSTYLE_2D_STOCK_1:
/*N*/ 			bHasVolume=FALSE;
/*N*/ 			bHasUpDown=FALSE;
/*N*/ 			break;
/*N*/ 		case CHSTYLE_2D_STOCK_2:
/*N*/ 			bHasVolume=FALSE;
/*N*/ 			bHasUpDown=TRUE;
/*N*/ 			break;
/*N*/ 		case CHSTYLE_2D_STOCK_3:
/*N*/ 			bHasVolume=TRUE;
/*N*/ 			bHasUpDown=FALSE;
/*N*/ 			break;
/*N*/ 		case CHSTYLE_2D_STOCK_4:
/*N*/ 			bHasVolume=TRUE;
/*N*/ 			bHasUpDown=TRUE;
/*N*/ 			break;
/*N*/ 		default:
/*N*/ 			nSpecialType=0;
/*N*/ 			break;
/*N*/ 	}
/*N*/ }
/*************************************************************************
|*
|* Konvertierung ChartType -> SvxChartStyle
|*
\************************************************************************/
/*N*/ SvxChartStyle ChartType::GetChartStyle() const
/*N*/ {
/*N*/ 	SvxChartStyle aResult = CHSTYLE_2D_COLUMN; // in case of error return default
/*N*/ 
/*N*/ 	switch(nSpecialType)
/*N*/ 	{
/*N*/ 	case 1:
/*N*/ 	   return CHSTYLE_2D_PIE_SEGOF1;
/*N*/ 	case 2:
/*N*/ 	   return CHSTYLE_2D_PIE_SEGOFALL;
/*N*/ 	case 3:
/*N*/ 	   return CHSTYLE_2D_DONUT2;
/*N*/ 	case 4:
/*N*/ 	   return CHSTYLE_2D_LINE_COLUMN;
/*N*/ 	case 5 :
/*N*/ 	   return CHSTYLE_2D_LINE_STACKEDCOLUMN;
/*N*/ 	default:
/*N*/ 	   break;
/*N*/ 	}
/*N*/ 
/*N*/ 	switch(nBaseType)
/*N*/ 	{
/*N*/ 		case CHTYPE_DONUT:
/*N*/ 			return CHSTYLE_2D_DONUT1;
/*N*/ 
/*N*/ 		case CHTYPE_LINE:
/*N*/ 		{
/*N*/ 
/*N*/ 			if(bIs3D)
/*N*/ 				return CHSTYLE_3D_STRIPE; //default 3d
/*N*/ 
/*N*/ 			if (nSymbolType!=SVX_SYMBOLTYPE_NONE)
/*N*/ 			{
/*N*/ 
/*N*/ 				if(nSplineType==SPLINE_CUBIC)
/*N*/ 					return CHSTYLE_2D_CUBIC_SPLINE_SYMBOL;
/*N*/ 
/*N*/ 				if(nSplineType==SPLINE_B)
/*N*/ 					return CHSTYLE_2D_B_SPLINE_SYMBOL; //default spline&symbol&line:
/*N*/ 
/*N*/ 				if(bIsPercent) //MUSS vor stacked, da percent auch stacked
/*N*/ 					return CHSTYLE_2D_PERCENTLINESYM;
/*N*/ 
/*N*/ 				if(bIsStacked)
/*N*/ 					return 	CHSTYLE_2D_STACKEDLINESYM;
/*N*/ 
/*N*/ 				return CHSTYLE_2D_LINESYMBOLS;  //default Line&Symbols
/*N*/ 
/*N*/ 
/*N*/ 			}
/*N*/ 
/*N*/ 			if(nSplineType==SPLINE_CUBIC)
/*N*/ 				return CHSTYLE_2D_CUBIC_SPLINE;
/*N*/ 
/*N*/ 			if(nSplineType==SPLINE_B)
/*N*/ 				return CHSTYLE_2D_B_SPLINE;
/*N*/ 
/*N*/ 			if(bIsPercent) //MUSS vor stacked, da percent auch stacked
/*N*/ 				return CHSTYLE_2D_PERCENTLINE;
/*N*/ 
/*N*/ 			if(bIsStacked)
/*N*/ 				return CHSTYLE_2D_STACKEDLINE;
/*N*/ 
/*N*/ 			return CHSTYLE_2D_LINE; //default Line
/*N*/ 		 }
/*N*/ 		 break;
/*N*/ 
/*N*/ 		case CHTYPE_AREA:
/*N*/ 			{
/*N*/ 				if(bIs3D)
/*N*/ 				{
/*N*/ 					if(bIsPercent)
/*N*/ 						return CHSTYLE_3D_PERCENTAREA;
/*N*/ 					if(bIsStacked)
/*N*/ 						return CHSTYLE_3D_STACKEDAREA;
/*N*/ 
/*N*/ 					return CHSTYLE_3D_AREA;
/*N*/ 				}
/*N*/ 
/*N*/ 				if(bIsPercent)
/*N*/ 					return CHSTYLE_2D_PERCENTAREA;
/*N*/ 
/*N*/ 				if(bIsStacked)
/*N*/ 					return CHSTYLE_2D_STACKEDAREA;
/*N*/ 
/*N*/ 				return CHSTYLE_2D_AREA;
/*N*/ 			}
/*N*/ 			break;
/*N*/ 
/*N*/ 		case CHTYPE_CIRCLE:
/*N*/ 			{
/*N*/ 				if(bIs3D)
/*N*/ 					return CHSTYLE_3D_PIE;
/*N*/ 
/*N*/ 				if(bIsDonut || bIsStacked)
/*N*/ 					return CHSTYLE_2D_DONUT1;
/*N*/ 				//case CHSTYLE_2D_PIE_SEGOF1:
/*N*/ 				//case CHSTYLE_2D_PIE_SEGOFALL:
/*N*/ 				//case CHSTYLE_2D_DONUT2:
/*N*/ 				return CHSTYLE_2D_PIE;
/*N*/ 			}
/*N*/ 			break;
/*N*/ 
/*N*/ 		case CHTYPE_XY:
/*N*/ 			{
/*N*/ 				if(nSymbolType!=SVX_SYMBOLTYPE_NONE)
/*N*/ 				{
/*N*/ 					if(nSplineType==SPLINE_CUBIC)
/*N*/ 						return CHSTYLE_2D_CUBIC_SPLINE_SYMBOL_XY;
/*N*/ 
/*N*/ 					if(nSplineType==SPLINE_B)
/*N*/ 						return CHSTYLE_2D_B_SPLINE_SYMBOL_XY;
/*N*/ 				}
/*N*/ 
/*N*/ 				if(nSplineType==SPLINE_CUBIC)
/*N*/ 					return CHSTYLE_2D_CUBIC_SPLINE_XY;
/*N*/ 
/*N*/ 				if(nSplineType==SPLINE_B)
/*N*/ 					return CHSTYLE_2D_B_SPLINE_XY;
/*N*/ 
/*N*/ 				if(bHasLines && (nSymbolType!=SVX_SYMBOLTYPE_NONE))//fehlte! XY=Symbol+Line
/*N*/ 					return CHSTYLE_2D_XY;
/*N*/ 
/*N*/ 				if(bHasLines)
/*N*/ 					return CHSTYLE_2D_XY_LINE;
/*N*/ 
/*N*/ 				if(nSymbolType!=SVX_SYMBOLTYPE_NONE)
/*N*/ 					return CHSTYLE_2D_XYSYMBOLS;
/*N*/ 
/*N*/ 				DBG_ERROR( "Unknown chart type" );
/*N*/ 
/*N*/ 				return CHSTYLE_2D_XY;
/*N*/ 			}
/*N*/ 			break;
/*N*/ 
/*N*/ 		case CHTYPE_NET:
/*N*/ 			{
/*N*/ 				if(nSymbolType!=SVX_SYMBOLTYPE_NONE)
/*N*/ 				{
/*N*/ 					if(bIsPercent)
/*N*/ 						return CHSTYLE_2D_NET_SYMBOLS_PERCENT;
/*N*/ 
/*N*/ 					if(bIsStacked)
/*N*/ 						return CHSTYLE_2D_NET_SYMBOLS_STACK;
/*N*/ 
/*N*/ 					return CHSTYLE_2D_NET_SYMBOLS;
/*N*/ 				}
/*N*/ 
/*N*/ 				if(bIsPercent)
/*N*/ 					return CHSTYLE_2D_NET_PERCENT;
/*N*/ 
/*N*/ 				if(bIsStacked)
/*N*/ 					return CHSTYLE_2D_NET_STACK;
/*N*/ 
/*N*/ 				return CHSTYLE_2D_NET;
/*N*/ 			}
/*N*/ 			break;
/*N*/ 
/*N*/ 		case CHTYPE_COLUMN: //==BAR
/*N*/ 		case CHTYPE_BAR:
/*N*/ 			{
/*N*/ 				if(bIsVertical) //Bar = vertical Column
/*N*/ 				{
/*N*/ 					if(bIs3D)
/*N*/ 					{
/*N*/ 						if(bIsPercent)
/*N*/ 							return CHSTYLE_3D_PERCENTFLATBAR;
/*N*/ 						if(bIsStacked)
/*N*/ 							return CHSTYLE_3D_STACKEDFLATBAR;
/*N*/ 						if(bIsDeep3D)
/*N*/ 							return CHSTYLE_3D_BAR;
/*N*/ 						return CHSTYLE_3D_FLATBAR;
/*N*/ 					}
/*N*/ 					if(bIsPercent)
/*N*/ 						return CHSTYLE_2D_PERCENTBAR;
/*N*/ 					if(bIsStacked)
/*N*/ 						return CHSTYLE_2D_STACKEDBAR;
/*N*/ 
/*N*/ 					return CHSTYLE_2D_BAR;
/*N*/ 				}
/*N*/ 				if(bIs3D)
/*N*/ 				{
/*N*/ 					if(bIsPercent)
/*N*/ 						return CHSTYLE_3D_PERCENTFLATCOLUMN;
/*N*/ 					if(bIsStacked)
/*N*/ 						return CHSTYLE_3D_STACKEDFLATCOLUMN;
/*N*/ 					if(bIsDeep3D)
/*N*/ 						return CHSTYLE_3D_COLUMN;
/*N*/ 					return CHSTYLE_3D_FLATCOLUMN;
/*N*/ 				}
/*N*/ 
/*N*/ 				if(bIsPercent)
/*N*/ 					return CHSTYLE_2D_PERCENTCOLUMN;
/*N*/ 				if(bIsStacked)
/*N*/ 					return CHSTYLE_2D_STACKEDCOLUMN;
/*N*/ 
/*N*/ 				//case CHSTYLE_2D_LINE_COLUMN:
/*N*/ 				//case CHSTYLE_2D_LINE_STACKEDCOLUMN:
/*N*/ 
/*N*/ 				return CHSTYLE_2D_COLUMN;
/*N*/ 			}
/*N*/ 			break;
/*N*/ 
/*N*/ 		case CHTYPE_STOCK:
/*N*/ 			if( bHasVolume )
/*N*/ 				aResult = bHasUpDown
/*N*/ 					? CHSTYLE_2D_STOCK_4
/*N*/ 					: CHSTYLE_2D_STOCK_3;
/*N*/ 			else
/*N*/ 				aResult = bHasUpDown
/*N*/ 					? CHSTYLE_2D_STOCK_2
/*N*/ 					: CHSTYLE_2D_STOCK_1;
/*N*/ 			break;
/*N*/ 
/*N*/ 		case CHTYPE_ADDIN:
/*N*/ 			aResult = CHSTYLE_ADDIN;
/*N*/ 			break;
/*N*/ 
/*N*/ 		default:
/*N*/ 			DBG_ERROR( "ChartModel::GetBaseType: invalid type!" );
/*N*/ 			break;
/*N*/ 	}
/*N*/ 
/*N*/ 	return aResult;
/*N*/ }

/*N*/ BOOL ChartType::HasLines(const SvxChartStyle eChartStyle) const
/*N*/ {
/*N*/     return
/*N*/         ( GetBaseType( eChartStyle ) == CHTYPE_LINE ) ||
/*N*/         ( ( GetBaseType( eChartStyle ) == CHTYPE_XY ) &&
/*N*/           eChartStyle != CHSTYLE_2D_XYSYMBOLS );
/*N*/ }
/*************************************************************************
|*
|* Chart-Typ mit Symbolen
|*
\************************************************************************/
/*N*/ BOOL ChartType::IsDeep3D(const SvxChartStyle eChartStyle) const
/*N*/ {
/*N*/ 	switch(eChartStyle)
/*N*/ 	{
/*N*/ 	case CHSTYLE_3D_COLUMN:
/*N*/ 	case CHSTYLE_3D_BAR:
/*?*/ 		return TRUE;
/*N*/ 	default:
/*N*/ 		break;
/*N*/ 	}
/*N*/ 	return FALSE;
/*N*/ }
/*************************************************************************
|*
|* Chart-Typ mit Splines
|*
\************************************************************************/
//STRIP001 BOOL ChartType::HasSplines(const SvxChartStyle eChartStyle) const
//STRIP001 {
//STRIP001 	switch (eChartStyle)
//STRIP001 	{
//STRIP001 		case CHSTYLE_2D_CUBIC_SPLINE :
//STRIP001 		case CHSTYLE_2D_CUBIC_SPLINE_SYMBOL :
//STRIP001 		case CHSTYLE_2D_B_SPLINE :
//STRIP001 		case CHSTYLE_2D_B_SPLINE_SYMBOL :
//STRIP001 		case CHSTYLE_2D_CUBIC_SPLINE_XY :
//STRIP001 		case CHSTYLE_2D_CUBIC_SPLINE_SYMBOL_XY :
//STRIP001 		case CHSTYLE_2D_B_SPLINE_XY :
//STRIP001 		case CHSTYLE_2D_B_SPLINE_SYMBOL_XY :
//STRIP001 			return TRUE;
//STRIP001 
//STRIP001 		default :
//STRIP001 			return FALSE;
//STRIP001 	}
//STRIP001 }
/*N*/ long ChartType::GetSplineType(const SvxChartStyle eChartStyle) const
/*N*/ {
/*N*/ 	switch (eChartStyle)
/*N*/ 	{
/*N*/ 		case CHSTYLE_2D_CUBIC_SPLINE :
/*N*/ 		case CHSTYLE_2D_CUBIC_SPLINE_SYMBOL :
/*N*/ 		case CHSTYLE_2D_CUBIC_SPLINE_XY :
/*N*/ 		case CHSTYLE_2D_CUBIC_SPLINE_SYMBOL_XY :
/*N*/ 			return SPLINE_CUBIC;
/*N*/ 
/*N*/ 		case CHSTYLE_2D_B_SPLINE :
/*N*/ 		case CHSTYLE_2D_B_SPLINE_SYMBOL :
/*N*/ 		case CHSTYLE_2D_B_SPLINE_XY :
/*N*/ 		case CHSTYLE_2D_B_SPLINE_SYMBOL_XY :
/*N*/ 			return SPLINE_B;
/*N*/ 
/*N*/ 		default :
/*N*/ 			return SPLINE_NONE;
/*N*/ 	}
/*N*/ }
/*************************************************************************
|*
|* Chart-Typ mit Symbolen
|*
\************************************************************************/
/*N*/ BOOL ChartType::HasSymbols(const SvxChartStyle eChartStyle) const
/*N*/ {
/*N*/ 	switch(eChartStyle)
/*N*/ 	{
/*N*/ 		case CHSTYLE_2D_LINESYMBOLS:
/*N*/ 		case CHSTYLE_2D_STACKEDLINESYM:
/*N*/ 		case CHSTYLE_2D_PERCENTLINESYM:
/*N*/ 		case CHSTYLE_2D_XYSYMBOLS:
/*N*/ 		case CHSTYLE_2D_XY://fehlte! XY=Symbol+Line
/*N*/ 		case CHSTYLE_3D_XYZSYMBOLS:
/*N*/ 		case CHSTYLE_2D_NET_SYMBOLS_STACK:
/*N*/ 		case CHSTYLE_2D_NET_SYMBOLS:
/*N*/ 		case CHSTYLE_2D_NET_SYMBOLS_PERCENT:
/*N*/ 		case CHSTYLE_2D_CUBIC_SPLINE_SYMBOL:
/*N*/ 		case CHSTYLE_2D_B_SPLINE_SYMBOL:
/*N*/ 		case CHSTYLE_2D_CUBIC_SPLINE_SYMBOL_XY:
/*N*/ 		case CHSTYLE_2D_B_SPLINE_SYMBOL_XY:
/*N*/ 
/*N*/ 			return TRUE;
/*N*/ 			break;
/*N*/ 
/*N*/ 		default:
/*N*/ 			break;
/*N*/ 	}
/*N*/ 	return FALSE;
/*N*/ }
/*************************************************************************
|*
|* 3D-Chart-Typ
|*
\************************************************************************/
/*N*/ BOOL ChartType::Is3D(const SvxChartStyle eChartStyle) const
/*N*/ {
/*N*/ 	switch (eChartStyle)
/*N*/ 	{
/*N*/ 		case CHSTYLE_3D_STRIPE:
/*N*/ 		case CHSTYLE_3D_COLUMN:
/*N*/ 		case CHSTYLE_3D_BAR:
/*N*/ 		case CHSTYLE_3D_FLATCOLUMN:
/*N*/ 		case CHSTYLE_3D_FLATBAR:
/*N*/ 		case CHSTYLE_3D_STACKEDFLATCOLUMN:
/*N*/ 		case CHSTYLE_3D_STACKEDFLATBAR:
/*N*/ 		case CHSTYLE_3D_PERCENTFLATCOLUMN:
/*N*/ 		case CHSTYLE_3D_PERCENTFLATBAR:
/*N*/ 		case CHSTYLE_3D_AREA:
/*N*/ 		case CHSTYLE_3D_STACKEDAREA:
/*N*/ 		case CHSTYLE_3D_PERCENTAREA:
/*N*/ 		case CHSTYLE_3D_SURFACE:
/*N*/ 		case CHSTYLE_3D_PIE:
/*N*/ 			//neu (aber bisher (380 Build 1502) nicht benutzt):
/*N*/ 		case CHSTYLE_3D_XYZ:
/*N*/ 		case CHSTYLE_3D_XYZSYMBOLS:
/*N*/ 			return TRUE;
/*N*/ 
/*N*/ 		default:
/*N*/ 			return FALSE;
/*N*/ 	}
/*N*/ }

/*************************************************************************
|*
|* Stacked-Chart-Typ (vollstaendig, d.h. percent => stacked
|*
\************************************************************************/
/*N*/ BOOL ChartType::IsStacked(const SvxChartStyle eChartStyle) const
/*N*/ {
/*N*/ 	if(IsPercent(eChartStyle))  //Percent ist immer Stacked!!!
/*N*/ 		return TRUE;
/*N*/ 
/*N*/ 	switch(eChartStyle)
/*N*/ 	{
/*N*/ 		case CHSTYLE_2D_STACKEDCOLUMN:
/*N*/ 		case CHSTYLE_2D_STACKEDBAR:
/*N*/ 		case CHSTYLE_2D_STACKEDLINE:
/*N*/ 		case CHSTYLE_2D_STACKEDAREA:
/*N*/ 		case CHSTYLE_3D_STACKEDFLATCOLUMN:
/*N*/ 		case CHSTYLE_3D_STACKEDFLATBAR:
/*N*/ 		case CHSTYLE_3D_STACKEDAREA:
/*N*/ 		//neu, (siehe auch IsPercent()):
/*N*/ 		case CHSTYLE_2D_STACKEDLINESYM:
/*N*/ 		case CHSTYLE_2D_NET_STACK:
/*N*/ 		case CHSTYLE_2D_NET_SYMBOLS_STACK:
/*N*/ 		case CHSTYLE_2D_LINE_STACKEDCOLUMN:
/*N*/ 
/*N*/ 			return TRUE;
/*N*/ 			break;
/*N*/ 
/*N*/ 		default:
/*N*/ 			break;
/*N*/ 	}
/*N*/ 	return FALSE;
/*N*/ }
/*************************************************************************
|*
|* Percent-Chart-Typ
|*
\************************************************************************/
/*N*/ BOOL ChartType::IsPercent(const SvxChartStyle eChartStyle) const
/*N*/ {
/*N*/ 	switch(eChartStyle)
/*N*/ 	{
/*N*/ 		case CHSTYLE_2D_PERCENTCOLUMN:
/*N*/ 		case CHSTYLE_2D_PERCENTBAR:
/*N*/ 		case CHSTYLE_2D_PERCENTLINE:
/*N*/ 		case CHSTYLE_2D_PERCENTAREA:
/*N*/ 		case CHSTYLE_3D_PERCENTFLATCOLUMN:
/*N*/ 		case CHSTYLE_3D_PERCENTAREA:
/*N*/ 		// Neu:
/*N*/ 		case CHSTYLE_2D_NET_PERCENT:
/*N*/ 		case CHSTYLE_2D_NET_SYMBOLS_PERCENT:
/*N*/ 		case CHSTYLE_2D_PERCENTLINESYM:
/*N*/ 		case CHSTYLE_3D_PERCENTFLATBAR:
/*N*/ 
/*N*/ 			return TRUE;
/*N*/ 			break;
/*N*/ 
/*N*/ 		default:
/*N*/ 			break;
/*N*/ 	}
/*N*/ 	return FALSE;
/*N*/ }

/*************************************************************************
|*
|* Basistyp ermitteln
|*
\************************************************************************/

/*N*/ long ChartType::GetBaseType(const SvxChartStyle eChartStyle) const
/*N*/ {
/*N*/ 	long nResult = CHTYPE_INVALID;
/*N*/ 
/*N*/ 	switch( eChartStyle )
/*N*/ 	{
/*N*/ 		case CHSTYLE_2D_B_SPLINE:
/*N*/ 		case CHSTYLE_2D_B_SPLINE_SYMBOL:
/*N*/ 		case CHSTYLE_2D_LINE:
/*N*/ 		case CHSTYLE_2D_STACKEDLINE:
/*N*/ 		case CHSTYLE_2D_PERCENTLINE:
/*N*/ 		case CHSTYLE_2D_LINESYMBOLS:
/*N*/ 		case CHSTYLE_2D_STACKEDLINESYM:
/*N*/ 		case CHSTYLE_2D_PERCENTLINESYM:
/*N*/ 		case CHSTYLE_2D_CUBIC_SPLINE:
/*N*/ 		case CHSTYLE_2D_CUBIC_SPLINE_SYMBOL:
/*N*/ 		case CHSTYLE_3D_STRIPE:
/*N*/ 			nResult = CHTYPE_LINE;
/*N*/ 			break;
/*N*/ 
/*N*/ 		case CHSTYLE_2D_AREA:
/*N*/ 		case CHSTYLE_2D_STACKEDAREA:
/*N*/ 		case CHSTYLE_2D_PERCENTAREA:
/*N*/ 		case CHSTYLE_3D_AREA:
/*N*/ 		case CHSTYLE_3D_STACKEDAREA:
/*N*/ 		case CHSTYLE_3D_PERCENTAREA:
/*N*/ 			nResult = CHTYPE_AREA;
/*N*/ 			break;
/*N*/ 
/*N*/ 		case CHSTYLE_2D_PIE:
/*N*/ 		case CHSTYLE_2D_PIE_SEGOF1:
/*N*/ 		case CHSTYLE_2D_PIE_SEGOFALL:
/*N*/ 		case CHSTYLE_2D_DONUT1:
/*N*/ 		case CHSTYLE_2D_DONUT2:
/*N*/ 		case CHSTYLE_3D_PIE:
/*N*/ 			nResult = CHTYPE_CIRCLE;
/*N*/ 			break;
/*N*/ 
/*N*/ 		case CHSTYLE_2D_B_SPLINE_XY:
/*N*/ 		case CHSTYLE_2D_XY_LINE:
/*N*/ 		case CHSTYLE_2D_B_SPLINE_SYMBOL_XY:
/*N*/ 		case CHSTYLE_2D_XYSYMBOLS:
/*N*/ 		case CHSTYLE_2D_XY:
/*N*/ 		case CHSTYLE_2D_CUBIC_SPLINE_XY:
/*N*/ 		case CHSTYLE_2D_CUBIC_SPLINE_SYMBOL_XY:
/*N*/ 			nResult = CHTYPE_XY;
/*N*/ 			break;
/*N*/ 
/*N*/ 		case CHSTYLE_2D_NET:
/*N*/ 		case CHSTYLE_2D_NET_SYMBOLS:
/*N*/ 		case CHSTYLE_2D_NET_STACK:
/*N*/ 		case CHSTYLE_2D_NET_SYMBOLS_STACK:
/*N*/ 		case CHSTYLE_2D_NET_PERCENT:
/*N*/ 		case CHSTYLE_2D_NET_SYMBOLS_PERCENT:
/*N*/ 			nResult = CHTYPE_NET;
/*N*/ 			break;
/*N*/ 
/*N*/ 		case CHSTYLE_2D_COLUMN:
/*N*/ 		case CHSTYLE_2D_STACKEDCOLUMN:
/*N*/ 		case CHSTYLE_2D_PERCENTCOLUMN:
/*N*/ 		case CHSTYLE_2D_LINE_COLUMN:
/*N*/ 		case CHSTYLE_2D_LINE_STACKEDCOLUMN:
/*N*/ 		case CHSTYLE_3D_COLUMN:
/*N*/ 		case CHSTYLE_3D_FLATCOLUMN:
/*N*/ 		case CHSTYLE_3D_STACKEDFLATCOLUMN:
/*N*/ 		case CHSTYLE_3D_PERCENTFLATCOLUMN:
/*N*/ 			nResult = CHTYPE_COLUMN;
/*N*/ 			break;
/*N*/ 
/*N*/ 		case CHSTYLE_2D_BAR:
/*N*/ 		case CHSTYLE_2D_STACKEDBAR:
/*N*/ 		case CHSTYLE_2D_PERCENTBAR:
/*N*/ 		case CHSTYLE_3D_BAR:
/*N*/ 		case CHSTYLE_3D_FLATBAR:
/*N*/ 		case CHSTYLE_3D_STACKEDFLATBAR:
/*N*/ 		case CHSTYLE_3D_PERCENTFLATBAR:
/*N*/ 			nResult = CHTYPE_BAR;
/*N*/ 			break;
/*N*/ 
/*N*/ 		case CHSTYLE_2D_STOCK_1:
/*N*/ 		case CHSTYLE_2D_STOCK_2:
/*N*/ 		case CHSTYLE_2D_STOCK_3:
/*N*/ 		case CHSTYLE_2D_STOCK_4:
/*N*/ 			nResult = CHTYPE_STOCK;
/*N*/ 			break;
/*N*/ 
/*N*/ 		case CHSTYLE_ADDIN:
/*N*/ 			nResult = CHTYPE_ADDIN;
/*N*/ 			break;
/*N*/ 			
/*N*/ 		default:
/*N*/ 			DBG_ERROR( "Invalid chart style given!" );
/*N*/ 			break;
/*N*/ 	}
/*N*/ 
/*N*/ 	return nResult;
/*N*/ }

/*************************************************************************
|*
|* Vertikales Chart
|*
\************************************************************************/

/*N*/ BOOL ChartType::IsVertical(const SvxChartStyle eChartStyle) const
/*N*/ {
/*N*/ 	switch(eChartStyle)
/*N*/ 	{
/*N*/ 			case CHSTYLE_2D_BAR:
/*N*/ 			case CHSTYLE_2D_STACKEDBAR:
/*N*/ 			case CHSTYLE_2D_PERCENTBAR:
/*N*/ 
/*N*/ 			case CHSTYLE_3D_BAR:
/*N*/ 			case CHSTYLE_3D_FLATBAR:
/*N*/ 			case CHSTYLE_3D_STACKEDFLATBAR:
/*N*/ 			case CHSTYLE_3D_PERCENTFLATBAR:
/*N*/ 
/*N*/ 				return TRUE;
/*N*/ 				break;
/*N*/ 
/*N*/ 			default:
/*N*/ 				break;
/*N*/ 		}
/*N*/ 		return FALSE;
/*N*/ }




/*N*/ BOOL ChartType::IsDonut(const SvxChartStyle eChartStyle) const
/*N*/ {
/*N*/ 	switch (eChartStyle)
/*N*/ 	{
/*N*/ 		case CHSTYLE_2D_DONUT1:
/*N*/ 		case CHSTYLE_2D_DONUT2:
/*N*/ 
/*N*/ 			return TRUE;
/*N*/ 			break;
/*N*/ 
/*N*/ 		default:
/*N*/ 			break;
/*N*/ 	}
/*N*/ 	return FALSE;
/*N*/ }
/*************************************************************************
|*
|* CleanUp sorgt nach dem Setzen bestimmter Eigenschaften dafuer, das
|* alle �brigen Eigenschaften, die jetzt nicht mehr verf�gbar sind,
|* passend gesetzt werden. Beispiel:
|* Type = Percent, stacked              oder    Typ = Column
|* Percent wird auf FALSE gesetzt               Typ auf Pie
|* nach CleanUp ist auch Stacked = FALSE;       Typ = Pie,Percent,Stacked
|*                                              Typ auf Column
|*                                              Type = Column,Percent,Stacked
\************************************************************************/

//STRIP001 BOOL ChartType::CleanUp()
//STRIP001 {
//STRIP001    SvxChartStyle eOldStyle = GetChartStyle();
//STRIP001    SetType(eOldStyle);
//STRIP001    SvxChartStyle eNewStyle = GetChartStyle();
//STRIP001 
//STRIP001    return eNewStyle == eOldStyle;
//STRIP001 }
//Wie SetBaseType, jedoch werden alle Properties auf defaults gesetz
//STRIP001 BOOL ChartType::SetDefaultBaseType(long nDefault)
//STRIP001 {
//STRIP001 	if(nDefault==-1)
//STRIP001 		nDefault=GetBaseType();
//STRIP001 
//STRIP001 	SvxChartStyle eOldStyle = GetChartStyle();
//STRIP001 
//STRIP001 	SvxChartStyle eNewStyle=CHSTYLE_2D_COLUMN;
//STRIP001 
//STRIP001 	switch(nDefault)
//STRIP001 	{
//STRIP001 		case CHTYPE_LINE:
//STRIP001 			eNewStyle = (Is3D()) ? CHSTYLE_3D_STRIPE : CHSTYLE_2D_LINE;
//STRIP001 			break;
//STRIP001 		case CHTYPE_AREA:
//STRIP001 			eNewStyle = (Is3D()) ?  CHSTYLE_3D_AREA: CHSTYLE_2D_AREA;
//STRIP001 			break;
//STRIP001 		case CHTYPE_DONUT:
//STRIP001 			eNewStyle = CHSTYLE_2D_DONUT1;
//STRIP001 			break;
//STRIP001 		case CHTYPE_CIRCLE:
//STRIP001 			eNewStyle = (Is3D()) ?  CHSTYLE_3D_PIE: CHSTYLE_2D_PIE;
//STRIP001 			break;
//STRIP001 		case CHTYPE_XY:
//STRIP001 			eNewStyle = (Is3D()) ?  CHSTYLE_2D_XY: CHSTYLE_2D_XY;
//STRIP001 			break;
//STRIP001 		case CHTYPE_NET:
//STRIP001 			eNewStyle = (Is3D()) ?  CHSTYLE_2D_NET: CHSTYLE_2D_NET ;
//STRIP001 			break;
//STRIP001 		case CHTYPE_COLUMN:
//STRIP001 		case CHTYPE_BAR:
//STRIP001 			eNewStyle = (Is3D()) ?  CHSTYLE_3D_COLUMN: CHSTYLE_2D_COLUMN;
//STRIP001 			break;
//STRIP001 		case CHTYPE_STOCK:
//STRIP001 			eNewStyle = CHSTYLE_2D_STOCK_1;
//STRIP001 
//STRIP001 			break;
//STRIP001 	}
//STRIP001 
//STRIP001 	SetType(eNewStyle);
//STRIP001 
//STRIP001 	return eNewStyle == eOldStyle;
//STRIP001 }
}
