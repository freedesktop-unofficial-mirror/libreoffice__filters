/*************************************************************************
 *
 *  $RCSfile: svx_xpool.cxx,v $
 *
 *  $Revision: 1.2 $
 *
 *  last change: $Author: mwu $ $Date: 2003-11-06 07:47:40 $
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

#pragma hdrstop

#include "xtable.hxx"
#include "xattr.hxx"
#include "xpool.hxx"
#include "svdattr.hxx"
#include "svxids.hrc"
namespace binfilter {

#define GLOBALOVERFLOW3

static USHORT nVersion1Map[40];
static USHORT nVersion2Map[66];
static USHORT nVersion3Map[124];
static USHORT nVersion4Map[141];

/*************************************************************************
|*
|* Konstruktor
|*
\************************************************************************/


/*N*/ XOutdevItemPool::XOutdevItemPool(USHORT nAttrStart, USHORT nAttrEnd, FASTBOOL bLoadRefCounts):
/*N*/ 	SfxItemPool(String("XOutdevItemPool", gsl_getSystemTextEncoding()), nAttrStart, nAttrEnd, NULL, NULL, bLoadRefCounts)
/*N*/ {
/*N*/ 	Ctor(NULL,nAttrStart,nAttrEnd);
/*N*/ }


/*N*/ XOutdevItemPool::XOutdevItemPool(SfxItemPool* pMaster, USHORT nAttrStart, USHORT nAttrEnd, FASTBOOL bLoadRefCounts):
/*N*/ 	SfxItemPool(String("XOutdevItemPool", gsl_getSystemTextEncoding()), nAttrStart, nAttrEnd, NULL, NULL, bLoadRefCounts)
/*N*/ {
/*N*/ 	Ctor(pMaster,nAttrStart,nAttrEnd);
/*N*/ }


/*N*/ void XOutdevItemPool::Ctor(SfxItemPool* pMaster, USHORT nAttrStart, USHORT nAttrEnd)
/*N*/ {
/*N*/ 	// Mich als Secondary an den MasterPool (Joe)
/*N*/ 	if (pMaster==NULL) {
/*N*/ 		pMaster=this;
/*N*/ 	} else {
/*N*/ 		// Ich ganz hinten dran
/*N*/ 		SfxItemPool* pParent=pMaster;
/*N*/ 		while (pParent->GetSecondaryPool()!=NULL) {
/*?*/ 			pParent=pParent->GetSecondaryPool();
/*N*/ 		}
/*N*/ 		pParent->SetSecondaryPool(this);
/*N*/ 	}
/*N*/ 
/*N*/ 	SfxItemSet* pSet;
/*N*/ 
/*N*/ 	nStart=nAttrStart;
/*N*/ 	nEnd  =nAttrEnd;
/*N*/ 	ppPoolDefaults = new SfxPoolItem* [nEnd-nStart+1];
/*N*/ 
/*N*/ 	USHORT i;
/*N*/ 
/*N*/ 	// Am 27-06-1995 hat Elmar 13 neue Whiches fuer XATTR_FORMTXT bei Which 1021
/*N*/ 	// eingebaut.
/*N*/ 	// Alles was zu diesem Zeitpunkt >1021 war verschiebt sich also um
/*N*/ 	// 13 Positionen nach hinten.
/*N*/ 	// Alles was davor liegt (11 LineItems, 6 FillItems, 5 von 6 FormTextItems)
/*N*/ 	// behaelt seine WhichId.
/*N*/ 
/*N*/ 	for (i=1000; i<=1021; i++) {
/*N*/ 		nVersion1Map[i-1000]=i;
/*N*/ 	}
/*N*/ 	for (i=1022; i<=1039; i++) {
/*N*/ 		nVersion1Map[i-1000]=i+13;
/*N*/ 	}
/*N*/ 	SetVersionMap(1,1000,1039,nVersion1Map);
/*N*/ 
/*N*/ 	// Am 09-11-1995 haben dann wiederum Kai Ahrens 14 und Joe 44 (also beide
/*N*/ 	// insgesamt 58) neue Whiches an verschiedenen Stellen spendiert (siehe
/*N*/ 	// auch die Beschreibung in svx\inc\SvdAttr.HXX).
/*N*/ 
/*N*/ 	for (i=1000; i<=1009; i++) {  // XOut
/*N*/ 		nVersion2Map[i-1000]=i;
/*N*/ 	}
/*N*/ 	for (i=1010; i<=1015; i++) {  // XOut
/*N*/ 		nVersion2Map[i-1000]=i+7;
/*N*/ 	}
/*N*/ 	for (i=1016; i<=1035; i++) {  // XOut
/*N*/ 		nVersion2Map[i-1000]=i+14;
/*N*/ 	}
/*N*/ 	for (i=1036; i<=1039; i++) {  // SvDraw
/*N*/ 		nVersion2Map[i-1000]=i+14;
/*N*/ 	}
/*N*/ 	for (i=1040; i<=1050; i++) {  // SvDraw
/*N*/ 		nVersion2Map[i-1000]=i+22;
/*N*/ 	}
/*N*/ 	for (i=1051; i<=1056; i++) {  // SvDraw
/*N*/ 		nVersion2Map[i-1000]=i+27;
/*N*/ 	}
/*N*/ 	for (i=1057; i<=1065; i++) {  // SvDraw
/*N*/ 		nVersion2Map[i-1000]=i+52;
/*N*/ 	}
/*N*/ 	SetVersionMap(2,1000,1065,nVersion2Map);
/*N*/ 
/*N*/ 
/*N*/ 	// Am 29-02-1996 hat KA 17 neue Whiches
/*N*/ 	// fuer das XOut spendiert
/*N*/ 
/*N*/ 	for (i=1000; i<=1029; i++) {
/*N*/ 		nVersion3Map[i-1000]=i;
/*N*/ 	}
/*N*/ 	for (i=1030; i<=1123; i++) {
/*N*/ 		nVersion3Map[i-1000]=i+17;
/*N*/ 	}
/*N*/ 	SetVersionMap(3,1000,1123,nVersion3Map);
/*N*/ 
/*N*/ 
/*N*/ 	// Am 10-08-1996 hat Joe 45 neue Items in SvDraw eingebaut
/*N*/ 	// fuer Bemassung, Verbinder und Laufschrift
/*N*/ 
/*N*/ 	for (i=1000; i<=1126; i++) {
/*N*/ 		nVersion4Map[i-1000]=i;
/*N*/ 	}
/*N*/ 	for (i=1127; i<=1140; i++) {
/*N*/ 		nVersion4Map[i-1000]=i+45;
/*N*/ 	}
/*N*/ 	SetVersionMap(4,1000,1140,nVersion4Map);
/*N*/ 
/*N*/ 
/*N*/ 	XubString    aNullStr;
/*N*/ 	Bitmap      aNullBmp;
/*N*/ 	XPolygon    aNullPol;
/*N*/ 	Color       aNullLineCol(RGB_Color(COL_BLACK));
/*N*/ 
/*N*/ 	Color       aNullFillCol(Color(0,184,255));  // "Blau 7"
/*N*/ 
/*N*/ 	Color       aNullShadowCol(RGB_Color(COL_LIGHTGRAY));
/*N*/ 	XDash       aNullDash;
/*N*/ 	XGradient   aNullGrad(aNullLineCol, RGB_Color(COL_WHITE));
/*N*/ 	XHatch      aNullHatch(aNullLineCol);
/*N*/ 
/*N*/ 	// LineItems
/*N*/ 	ppPoolDefaults[XATTR_LINESTYLE          -XATTR_START] = new XLineStyleItem;
/*N*/ 	ppPoolDefaults[XATTR_LINEDASH           -XATTR_START] = new XLineDashItem(this,aNullDash);
/*N*/ 	ppPoolDefaults[XATTR_LINEWIDTH          -XATTR_START] = new XLineWidthItem;
/*N*/ 	ppPoolDefaults[XATTR_LINECOLOR          -XATTR_START] = new XLineColorItem(aNullStr,aNullLineCol);
/*N*/ 	ppPoolDefaults[XATTR_LINESTART          -XATTR_START] = new XLineStartItem(this,aNullPol);
/*N*/ 	ppPoolDefaults[XATTR_LINEEND            -XATTR_START] = new XLineEndItem  (this,aNullPol);
/*N*/ 	ppPoolDefaults[XATTR_LINESTARTWIDTH     -XATTR_START] = new XLineStartWidthItem;
/*N*/ 	ppPoolDefaults[XATTR_LINEENDWIDTH       -XATTR_START] = new XLineEndWidthItem;
/*N*/ 	ppPoolDefaults[XATTR_LINESTARTCENTER    -XATTR_START] = new XLineStartCenterItem;
/*N*/ 	ppPoolDefaults[XATTR_LINEENDCENTER      -XATTR_START] = new XLineEndCenterItem;
/*N*/ 	ppPoolDefaults[XATTR_LINETRANSPARENCE   -XATTR_START] = new XLineTransparenceItem;
/*N*/ 	ppPoolDefaults[XATTR_LINEJOINT	        -XATTR_START] = new XLineJointItem;
/*N*/ 
/*N*/ 	// Reserven fuer LineItems
/*N*/ 	ppPoolDefaults[XATTR_LINERESERVED2      -XATTR_START] = new SfxVoidItem(XATTR_LINERESERVED2);
/*N*/ 	ppPoolDefaults[XATTR_LINERESERVED3      -XATTR_START] = new SfxVoidItem(XATTR_LINERESERVED3);
/*N*/ 	ppPoolDefaults[XATTR_LINERESERVED4      -XATTR_START] = new SfxVoidItem(XATTR_LINERESERVED4);
/*N*/ 	ppPoolDefaults[XATTR_LINERESERVED5      -XATTR_START] = new SfxVoidItem(XATTR_LINERESERVED5);
/*N*/ 	ppPoolDefaults[XATTR_LINERESERVED_LAST  -XATTR_START] = new SfxVoidItem(XATTR_LINERESERVED_LAST);
/*N*/ 
/*N*/ 	// FillItems
/*N*/ 	ppPoolDefaults[XATTR_FILLSTYLE				-XATTR_START] = new XFillStyleItem;
/*N*/ 	ppPoolDefaults[XATTR_FILLCOLOR				-XATTR_START] = new XFillColorItem   (aNullStr,aNullFillCol);
/*N*/ 	ppPoolDefaults[XATTR_FILLGRADIENT			-XATTR_START] = new XFillGradientItem(this,aNullGrad);
/*N*/ 	ppPoolDefaults[XATTR_FILLHATCH				-XATTR_START] = new XFillHatchItem   (this,aNullHatch);
/*N*/ 	ppPoolDefaults[XATTR_FILLBITMAP				-XATTR_START] = new XFillBitmapItem  (this,aNullBmp);
/*N*/ 	ppPoolDefaults[XATTR_FILLTRANSPARENCE		-XATTR_START] = new XFillTransparenceItem;
/*N*/ 	ppPoolDefaults[XATTR_GRADIENTSTEPCOUNT		-XATTR_START] = new XGradientStepCountItem;
/*N*/ 	ppPoolDefaults[XATTR_FILLBMP_TILE			-XATTR_START] = new XFillBmpTileItem;
/*N*/ 	ppPoolDefaults[XATTR_FILLBMP_POS			-XATTR_START] = new XFillBmpPosItem;
/*N*/ 	ppPoolDefaults[XATTR_FILLBMP_SIZEX			-XATTR_START] = new XFillBmpSizeXItem;
/*N*/ 	ppPoolDefaults[XATTR_FILLBMP_SIZEY			-XATTR_START] = new XFillBmpSizeYItem;
/*N*/ 	ppPoolDefaults[XATTR_FILLBMP_SIZELOG		-XATTR_START] = new XFillBmpSizeLogItem;
/*N*/ 	ppPoolDefaults[XATTR_FILLBMP_TILEOFFSETX	-XATTR_START] = new XFillBmpTileOffsetXItem;
/*N*/ 	ppPoolDefaults[XATTR_FILLBMP_TILEOFFSETY	-XATTR_START] = new XFillBmpTileOffsetYItem;
/*N*/ 	ppPoolDefaults[XATTR_FILLBMP_STRETCH		-XATTR_START] = new XFillBmpStretchItem;
/*N*/ 	ppPoolDefaults[XATTR_FILLBMP_POSOFFSETX		-XATTR_START] = new XFillBmpPosOffsetXItem;
/*N*/ 	ppPoolDefaults[XATTR_FILLBMP_POSOFFSETY		-XATTR_START] = new XFillBmpPosOffsetYItem;
/*N*/ 	ppPoolDefaults[XATTR_FILLFLOATTRANSPARENCE	-XATTR_START] = new XFillFloatTransparenceItem( this, aNullGrad, FALSE );
/*N*/ 
/*N*/ 	// Reserven fuer FillItems
/*N*/ 	ppPoolDefaults[XATTR_FILLRESERVED2			-XATTR_START] = new SfxVoidItem(XATTR_FILLRESERVED2);
/*N*/ 	ppPoolDefaults[XATTR_FILLRESERVED3			-XATTR_START] = new SfxVoidItem(XATTR_FILLRESERVED3);
/*N*/ 	ppPoolDefaults[XATTR_FILLRESERVED4			-XATTR_START] = new SfxVoidItem(XATTR_FILLRESERVED4);
/*N*/ 	ppPoolDefaults[XATTR_FILLRESERVED5			-XATTR_START] = new SfxVoidItem(XATTR_FILLRESERVED5);
/*N*/ 	ppPoolDefaults[XATTR_FILLRESERVED6			-XATTR_START] = new SfxVoidItem(XATTR_FILLRESERVED6);
/*N*/ 	ppPoolDefaults[XATTR_FILLRESERVED7			-XATTR_START] = new SfxVoidItem(XATTR_FILLRESERVED7);
/*N*/ 	ppPoolDefaults[XATTR_FILLRESERVED8			-XATTR_START] = new SfxVoidItem(XATTR_FILLRESERVED8);
/*N*/ 	ppPoolDefaults[XATTR_FILLBACKGROUND			-XATTR_START] = new XFillBackgroundItem;
/*N*/ 	ppPoolDefaults[XATTR_FILLRESERVED10			-XATTR_START] = new SfxVoidItem(XATTR_FILLRESERVED10);
/*N*/ 	ppPoolDefaults[XATTR_FILLRESERVED11			-XATTR_START] = new SfxVoidItem(XATTR_FILLRESERVED11);
/*N*/ 	ppPoolDefaults[XATTR_FILLRESERVED_LAST		-XATTR_START] = new SfxVoidItem(XATTR_FILLRESERVED_LAST);
/*N*/ 
/*N*/ 	// FormTextItems
/*N*/ 	ppPoolDefaults[XATTR_FORMTXTSTYLE       -XATTR_START] = new XFormTextStyleItem;
/*N*/ 	ppPoolDefaults[XATTR_FORMTXTADJUST      -XATTR_START] = new XFormTextAdjustItem;
/*N*/ 	ppPoolDefaults[XATTR_FORMTXTDISTANCE    -XATTR_START] = new XFormTextDistanceItem;
/*N*/ 	ppPoolDefaults[XATTR_FORMTXTSTART       -XATTR_START] = new XFormTextStartItem;
/*N*/ 	ppPoolDefaults[XATTR_FORMTXTMIRROR      -XATTR_START] = new XFormTextMirrorItem;
/*N*/ 	ppPoolDefaults[XATTR_FORMTXTOUTLINE     -XATTR_START] = new XFormTextOutlineItem;
/*N*/ 	ppPoolDefaults[XATTR_FORMTXTSHADOW      -XATTR_START] = new XFormTextShadowItem;
/*N*/ 	ppPoolDefaults[XATTR_FORMTXTSHDWCOLOR   -XATTR_START] = new XFormTextShadowColorItem(aNullStr,aNullShadowCol);
/*N*/ 	ppPoolDefaults[XATTR_FORMTXTSHDWXVAL    -XATTR_START] = new XFormTextShadowXValItem;
/*N*/ 	ppPoolDefaults[XATTR_FORMTXTSHDWYVAL    -XATTR_START] = new XFormTextShadowYValItem;
/*N*/ 	ppPoolDefaults[XATTR_FORMTXTSTDFORM     -XATTR_START] = new XFormTextStdFormItem;
/*N*/ 	ppPoolDefaults[XATTR_FORMTXTHIDEFORM    -XATTR_START] = new XFormTextHideFormItem;
/*N*/ 
/*N*/ 	// Reserven fuer FormTextItems
/*N*/ 	ppPoolDefaults[XATTR_FORMTXTSHDWTRANSP  -XATTR_START] = new XFormTextShadowTranspItem;
/*N*/ 	ppPoolDefaults[XATTR_FTRESERVED2        -XATTR_START] = new SfxVoidItem(XATTR_FTRESERVED2);
/*N*/ 	ppPoolDefaults[XATTR_FTRESERVED3        -XATTR_START] = new SfxVoidItem(XATTR_FTRESERVED3);
/*N*/ 	ppPoolDefaults[XATTR_FTRESERVED4        -XATTR_START] = new SfxVoidItem(XATTR_FTRESERVED4);
/*N*/ 	ppPoolDefaults[XATTR_FTRESERVED5        -XATTR_START] = new SfxVoidItem(XATTR_FTRESERVED5);
/*N*/ 	ppPoolDefaults[XATTR_FTRESERVED_LAST    -XATTR_START] = new SfxVoidItem(XATTR_FTRESERVED_LAST);
/*N*/ 
/*N*/ 	// SetItems erzeugen
/*N*/ 	pSet=new SfxItemSet(*pMaster, XATTR_LINE_FIRST, XATTR_LINE_LAST);
/*N*/ 	ppPoolDefaults[XATTRSET_LINE - XATTR_START] = new XLineAttrSetItem(pSet);
/*N*/ 	pSet=new SfxItemSet(*pMaster, XATTR_FILL_FIRST, XATTR_FILL_LAST);
/*N*/ 	ppPoolDefaults[XATTRSET_FILL - XATTR_START] = new XFillAttrSetItem(pSet);
/*N*/ 	pSet=new SfxItemSet(*pMaster, XATTR_TEXT_FIRST, XATTR_TEXT_LAST);
/*N*/ 	ppPoolDefaults[XATTRSET_TEXT - XATTR_START] = new XTextAttrSetItem(pSet);
/*N*/ 
/*N*/ 	// ItemInfos
/*N*/ 	pItemInfos=new SfxItemInfo[nEnd-nStart+1];
/*N*/ 	for (i=nStart; i<=nEnd; i++) {
/*N*/ 		pItemInfos[i-nStart]._nSID=0;
/*N*/ 		pItemInfos[i-nStart]._nFlags=SFX_ITEM_POOLABLE;
/*N*/ 	}
/*N*/ 
/*N*/ 	pItemInfos[XATTR_LINESTYLE        -XATTR_START]._nSID = SID_ATTR_LINE_STYLE;
/*N*/ 	pItemInfos[XATTR_LINEDASH         -XATTR_START]._nSID = SID_ATTR_LINE_DASH;
/*N*/ 	pItemInfos[XATTR_LINEWIDTH        -XATTR_START]._nSID = SID_ATTR_LINE_WIDTH;
/*N*/ 	pItemInfos[XATTR_LINECOLOR        -XATTR_START]._nSID = SID_ATTR_LINE_COLOR;
/*N*/ 	pItemInfos[XATTR_LINESTART        -XATTR_START]._nSID = SID_ATTR_LINE_START;
/*N*/ 	pItemInfos[XATTR_LINEEND          -XATTR_START]._nSID = SID_ATTR_LINE_END;
/*N*/ 	pItemInfos[XATTR_LINESTARTWIDTH   -XATTR_START]._nSID = SID_ATTR_LINE_STARTWIDTH;
/*N*/ 	pItemInfos[XATTR_LINEENDWIDTH     -XATTR_START]._nSID = SID_ATTR_LINE_ENDWIDTH;
/*N*/ 	pItemInfos[XATTR_LINESTARTCENTER  -XATTR_START]._nSID = SID_ATTR_LINE_STARTCENTER;
/*N*/ 	pItemInfos[XATTR_LINEENDCENTER    -XATTR_START]._nSID = SID_ATTR_LINE_ENDCENTER;
/*N*/ 
/*N*/ 	pItemInfos[XATTR_FILLSTYLE        -XATTR_START]._nSID = SID_ATTR_FILL_STYLE;
/*N*/ 	pItemInfos[XATTR_FILLCOLOR        -XATTR_START]._nSID = SID_ATTR_FILL_COLOR;
/*N*/ 	pItemInfos[XATTR_FILLGRADIENT     -XATTR_START]._nSID = SID_ATTR_FILL_GRADIENT;
/*N*/ 	pItemInfos[XATTR_FILLHATCH        -XATTR_START]._nSID = SID_ATTR_FILL_HATCH;
/*N*/ 	pItemInfos[XATTR_FILLBITMAP       -XATTR_START]._nSID = SID_ATTR_FILL_BITMAP;
/*N*/ 
/*N*/ 	pItemInfos[XATTR_FORMTXTSTYLE     -XATTR_START]._nSID = SID_FORMTEXT_STYLE;
/*N*/ 	pItemInfos[XATTR_FORMTXTADJUST    -XATTR_START]._nSID = SID_FORMTEXT_ADJUST;
/*N*/ 	pItemInfos[XATTR_FORMTXTDISTANCE  -XATTR_START]._nSID = SID_FORMTEXT_DISTANCE;
/*N*/ 	pItemInfos[XATTR_FORMTXTSTART     -XATTR_START]._nSID = SID_FORMTEXT_START;
/*N*/ 	pItemInfos[XATTR_FORMTXTMIRROR    -XATTR_START]._nSID = SID_FORMTEXT_MIRROR;
/*N*/ 	pItemInfos[XATTR_FORMTXTOUTLINE   -XATTR_START]._nSID = SID_FORMTEXT_OUTLINE;
/*N*/ 	pItemInfos[XATTR_FORMTXTSHADOW    -XATTR_START]._nSID = SID_FORMTEXT_SHADOW;
/*N*/ 	pItemInfos[XATTR_FORMTXTSHDWCOLOR -XATTR_START]._nSID = SID_FORMTEXT_SHDWCOLOR;
/*N*/ 	pItemInfos[XATTR_FORMTXTSHDWXVAL  -XATTR_START]._nSID = SID_FORMTEXT_SHDWXVAL;
/*N*/ 	pItemInfos[XATTR_FORMTXTSHDWYVAL  -XATTR_START]._nSID = SID_FORMTEXT_SHDWYVAL;
/*N*/ 	pItemInfos[XATTR_FORMTXTSTDFORM   -XATTR_START]._nSID = SID_FORMTEXT_STDFORM;
/*N*/ 	pItemInfos[XATTR_FORMTXTHIDEFORM  -XATTR_START]._nSID = SID_FORMTEXT_HIDEFORM;
/*N*/ 
/*N*/ #if SUPD<355
/*N*/ 	pSlotIds = new USHORT[nEnd-nStart+1];
/*N*/ 
/*N*/ 	pSlotIds[XATTR_LINESTYLE        -XATTR_START] = SID_ATTR_LINE_STYLE;
/*N*/ 	pSlotIds[XATTR_LINEDASH         -XATTR_START] = SID_ATTR_LINE_DASH;
/*N*/ 	pSlotIds[XATTR_LINEWIDTH        -XATTR_START] = SID_ATTR_LINE_WIDTH;
/*N*/ 	pSlotIds[XATTR_LINECOLOR        -XATTR_START] = SID_ATTR_LINE_COLOR;
/*N*/ 	pSlotIds[XATTR_LINESTART        -XATTR_START] = SID_ATTR_LINE_START;
/*N*/ 	pSlotIds[XATTR_LINEEND          -XATTR_START] = SID_ATTR_LINE_END;
/*N*/ 	pSlotIds[XATTR_LINESTARTWIDTH   -XATTR_START] = SID_ATTR_LINE_STARTWIDTH;
/*N*/ 	pSlotIds[XATTR_LINEENDWIDTH     -XATTR_START] = SID_ATTR_LINE_ENDWIDTH;
/*N*/ 	pSlotIds[XATTR_LINESTARTCENTER  -XATTR_START] = SID_ATTR_LINE_STARTCENTER;
/*N*/ 	pSlotIds[XATTR_LINEENDCENTER    -XATTR_START] = SID_ATTR_LINE_ENDCENTER;
/*N*/ 	pSlotIds[XATTR_LINETRANSPARENCE -XATTR_START] = 0;
/*N*/ 	pSlotIds[XATTR_LINEJOINT        -XATTR_START] = 0;
/*N*/ 
/*N*/ 	// Line-Reserven
/*N*/ 	pSlotIds[XATTR_LINERESERVED2        -XATTR_START] = 0;
/*N*/ 	pSlotIds[XATTR_LINERESERVED3        -XATTR_START] = 0;
/*N*/ 	pSlotIds[XATTR_LINERESERVED4        -XATTR_START] = 0;
/*N*/ 	pSlotIds[XATTR_LINERESERVED5        -XATTR_START] = 0;
/*N*/ 	pSlotIds[XATTR_LINERESERVED_LAST    -XATTR_START] = 0;
/*N*/ 
/*N*/ 	pSlotIds[XATTR_FILLSTYLE        -XATTR_START] = SID_ATTR_FILL_STYLE;
/*N*/ 	pSlotIds[XATTR_FILLCOLOR        -XATTR_START] = SID_ATTR_FILL_COLOR;
/*N*/ 	pSlotIds[XATTR_FILLGRADIENT     -XATTR_START] = SID_ATTR_FILL_GRADIENT;
/*N*/ 	pSlotIds[XATTR_FILLHATCH        -XATTR_START] = SID_ATTR_FILL_HATCH;
/*N*/ 	pSlotIds[XATTR_FILLBITMAP       -XATTR_START] = SID_ATTR_FILL_BITMAP;
/*N*/ 	pSlotIds[XATTR_FILLTRANSPARENCE -XATTR_START] = 0;
/*N*/ 	pSlotIds[XATTR_GRADIENTSTEPCOUNT-XATTR_START] = 0;
/*N*/ 
/*N*/ 	pSlotIds[XATTR_FILLBMP_TILE				-XATTR_START] = 0;
/*N*/ 	pSlotIds[XATTR_FILLBMP_POS				-XATTR_START] = 0;
/*N*/ 	pSlotIds[XATTR_FILLBMP_SIZEX			-XATTR_START] = 0;
/*N*/ 	pSlotIds[XATTR_FILLBMP_SIZEY			-XATTR_START] = 0;
/*N*/ 	pSlotIds[XATTR_FILLBMP_SIZELOG			-XATTR_START] = 0;
/*N*/ 	pSlotIds[XATTR_FILLBMP_TILEOFFSETX		-XATTR_START] = 0;
/*N*/ 	pSlotIds[XATTR_FILLBMP_TILEOFFSETY		-XATTR_START] = 0;
/*N*/ 	pSlotIds[XATTR_FILLBMP_STRETCH			-XATTR_START] = 0;
/*N*/ 	pSlotIds[XATTR_FILLBMP_POSOFFSETX		-XATTR_START] = 0;
/*N*/ 	pSlotIds[XATTR_FILLBMP_POSOFFSETY		-XATTR_START] = 0;
/*N*/ 	pSlotIds[XATTR_FILLFLOATTRANSPARENCE	-XATTR_START] = 0;
/*N*/ 
/*N*/ 	// Fill-Reserven
/*N*/ 	pSlotIds[XATTR_FILLRESERVED2        -XATTR_START] = 0;
/*N*/ 	pSlotIds[XATTR_FILLRESERVED3        -XATTR_START] = 0;
/*N*/ 	pSlotIds[XATTR_FILLRESERVED4        -XATTR_START] = 0;
/*N*/ 	pSlotIds[XATTR_FILLRESERVED5        -XATTR_START] = 0;
/*N*/ 	pSlotIds[XATTR_FILLRESERVED6        -XATTR_START] = 0;
/*N*/ 	pSlotIds[XATTR_FILLRESERVED7        -XATTR_START] = 0;
/*N*/ 	pSlotIds[XATTR_FILLRESERVED8        -XATTR_START] = 0;
/*N*/ 	pSlotIds[XATTR_FILLBACKGROUND       -XATTR_START] = 0;
/*N*/ 	pSlotIds[XATTR_FILLRESERVED10       -XATTR_START] = 0;
/*N*/ 	pSlotIds[XATTR_FILLRESERVED11       -XATTR_START] = 0;
/*N*/ 	pSlotIds[XATTR_FILLRESERVED_LAST    -XATTR_START] = 0;
/*N*/ 
/*N*/ 	pSlotIds[XATTR_FORMTXTSTYLE     -XATTR_START] = SID_FORMTEXT_STYLE;
/*N*/ 	pSlotIds[XATTR_FORMTXTADJUST    -XATTR_START] = SID_FORMTEXT_ADJUST;
/*N*/ 	pSlotIds[XATTR_FORMTXTDISTANCE  -XATTR_START] = SID_FORMTEXT_DISTANCE;
/*N*/ 	pSlotIds[XATTR_FORMTXTSTART     -XATTR_START] = SID_FORMTEXT_START;
/*N*/ 	pSlotIds[XATTR_FORMTXTMIRROR    -XATTR_START] = SID_FORMTEXT_MIRROR;
/*N*/ 	pSlotIds[XATTR_FORMTXTOUTLINE   -XATTR_START] = SID_FORMTEXT_OUTLINE;
/*N*/ 	pSlotIds[XATTR_FORMTXTSHADOW    -XATTR_START] = SID_FORMTEXT_SHADOW;
/*N*/ 	pSlotIds[XATTR_FORMTXTSHDWCOLOR -XATTR_START] = SID_FORMTEXT_SHDWCOLOR;
/*N*/ 	pSlotIds[XATTR_FORMTXTSHDWXVAL  -XATTR_START] = SID_FORMTEXT_SHDWXVAL;
/*N*/ 	pSlotIds[XATTR_FORMTXTSHDWYVAL  -XATTR_START] = SID_FORMTEXT_SHDWYVAL;
/*N*/ 	pSlotIds[XATTR_FORMTXTSTDFORM   -XATTR_START] = SID_FORMTEXT_STDFORM;
/*N*/ 	pSlotIds[XATTR_FORMTXTHIDEFORM  -XATTR_START] = SID_FORMTEXT_HIDEFORM;
/*N*/ 
/*N*/ 	// FormText-Reserven
/*N*/ 	pSlotIds[XATTR_FORMTXTSHDWTRANSP-XATTR_START] = 0;
/*N*/ 	pSlotIds[XATTR_FTRESERVED2      -XATTR_START] = 0;
/*N*/ 	pSlotIds[XATTR_FTRESERVED3      -XATTR_START] = 0;
/*N*/ 	pSlotIds[XATTR_FTRESERVED4      -XATTR_START] = 0;
/*N*/ 	pSlotIds[XATTR_FTRESERVED5      -XATTR_START] = 0;
/*N*/ 	pSlotIds[XATTR_FTRESERVED_LAST  -XATTR_START] = 0;
/*N*/ 
/*N*/ 	pSlotIds[XATTRSET_LINE - XATTR_START] = 0; // 20136; alter Hack von MI
/*N*/ 	pSlotIds[XATTRSET_FILL - XATTR_START] = 0; // 20135; alter Hack von MI
/*N*/ 	pSlotIds[XATTRSET_TEXT - XATTR_START] = 0;
/*N*/ #endif
/*N*/ 
/*N*/ 	if (nAttrStart==XATTR_START && nAttrEnd==XATTR_END)
/*N*/ 	{
/*N*/ 		SetDefaults(ppPoolDefaults);
/*N*/ 		SetItemInfos(pItemInfos);
/*N*/ #if SUPD<355
/*N*/ 		SetMap(pSlotIds);
/*N*/ #endif
/*N*/ 	}
/*N*/ }


/*************************************************************************
|*
|* copy ctor, sorgt dafuer, dass die static defaults gecloned werden
|*            (Parameter 2 = TRUE)
|*
\************************************************************************/

/*N*/ XOutdevItemPool::XOutdevItemPool(const XOutdevItemPool& rPool) :
/*N*/ 	SfxItemPool(rPool, TRUE)
/*N*/ {
    // damit geclonete Pools nicht im dtor auf die Nase fallen
    // endgueltige Loesung --> MI
/*N*/ 	ppPoolDefaults = NULL;
/*N*/ }

/*************************************************************************
|*
|* Clone()
|*
\************************************************************************/

/*N*/ SfxItemPool* XOutdevItemPool::Clone() const
/*N*/ {
/*N*/ 	return new XOutdevItemPool(*this);
/*N*/ }

/*************************************************************************
|*
|* Destruktor
|*
\************************************************************************/

/*N*/ XOutdevItemPool::~XOutdevItemPool()
/*N*/ {
/*N*/ #if SUPD<355
/*N*/ 	if (pSlotIds!=NULL) delete[] pSlotIds;
/*N*/ #endif
/*N*/ 
/*N*/ 	Delete();
/*N*/ 	if ( ppPoolDefaults )
/*N*/ 	{
/*N*/ 		SfxPoolItem** ppDefaultItem = ppPoolDefaults;
/*N*/ 		for ( USHORT i = nEnd - nStart + 1; i; --i, ++ppDefaultItem )
/*N*/ 		{
/*N*/ 			if ( *ppDefaultItem ) //Teile schon von abgel. Klasse abgeraeumt!
/*N*/ 			{
/*N*/ #ifndef PRODUCT
/*N*/ 				SetRefCount( **ppDefaultItem, 0 );
/*N*/ #endif
/*N*/ 				delete *ppDefaultItem;
/*N*/ 			}
/*N*/ 		}
/*N*/ 		delete[] ppPoolDefaults;
/*N*/ 	}
/*N*/ 	if (pItemInfos!=NULL) delete[] pItemInfos;
/*N*/ 
/*N*/ }


}
