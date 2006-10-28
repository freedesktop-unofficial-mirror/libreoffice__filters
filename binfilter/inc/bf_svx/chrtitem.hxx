/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: chrtitem.hxx,v $
 *
 *  $Revision: 1.5 $
 *
 *  last change: $Author: rt $ $Date: 2006-10-28 03:23:14 $
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
#ifndef _SVX_CHRTITEM_HXX
#define _SVX_CHRTITEM_HXX

// include ---------------------------------------------------------------

namespace binfilter {

//------------------------------------------------------------------------

enum SvxChartStyle
{
    CHSTYLE_2D_LINE,
    CHSTYLE_2D_STACKEDLINE,
    CHSTYLE_2D_PERCENTLINE,
    CHSTYLE_2D_COLUMN,
    CHSTYLE_2D_STACKEDCOLUMN,
    CHSTYLE_2D_PERCENTCOLUMN,
    CHSTYLE_2D_BAR,
    CHSTYLE_2D_STACKEDBAR,
    CHSTYLE_2D_PERCENTBAR,
    CHSTYLE_2D_AREA,
    CHSTYLE_2D_STACKEDAREA,
    CHSTYLE_2D_PERCENTAREA,
    CHSTYLE_2D_PIE,
    CHSTYLE_3D_STRIPE,
    CHSTYLE_3D_COLUMN,
    CHSTYLE_3D_FLATCOLUMN,
    CHSTYLE_3D_STACKEDFLATCOLUMN,
    CHSTYLE_3D_PERCENTFLATCOLUMN,
    CHSTYLE_3D_AREA,
    CHSTYLE_3D_STACKEDAREA,
    CHSTYLE_3D_PERCENTAREA,
    CHSTYLE_3D_SURFACE,
    CHSTYLE_3D_PIE,
    CHSTYLE_2D_XY,
    CHSTYLE_3D_XYZ,
    CHSTYLE_2D_LINESYMBOLS,
    CHSTYLE_2D_STACKEDLINESYM,
    CHSTYLE_2D_PERCENTLINESYM,
    CHSTYLE_2D_XYSYMBOLS,
    CHSTYLE_3D_XYZSYMBOLS,
    CHSTYLE_2D_DONUT1,
    CHSTYLE_2D_DONUT2,
    CHSTYLE_3D_BAR,
    CHSTYLE_3D_FLATBAR,
    CHSTYLE_3D_STACKEDFLATBAR,
    CHSTYLE_3D_PERCENTFLATBAR,
    CHSTYLE_2D_PIE_SEGOF1,
    CHSTYLE_2D_PIE_SEGOFALL,
    CHSTYLE_2D_NET,
    CHSTYLE_2D_NET_SYMBOLS,
    CHSTYLE_2D_NET_STACK,
    CHSTYLE_2D_NET_SYMBOLS_STACK,
    CHSTYLE_2D_NET_PERCENT,
    CHSTYLE_2D_NET_SYMBOLS_PERCENT,
    CHSTYLE_2D_CUBIC_SPLINE,
    CHSTYLE_2D_CUBIC_SPLINE_SYMBOL,
    CHSTYLE_2D_B_SPLINE,
    CHSTYLE_2D_B_SPLINE_SYMBOL,
    CHSTYLE_2D_CUBIC_SPLINE_XY,
    CHSTYLE_2D_CUBIC_SPLINE_SYMBOL_XY,
    CHSTYLE_2D_B_SPLINE_XY,
    CHSTYLE_2D_B_SPLINE_SYMBOL_XY,
    CHSTYLE_2D_XY_LINE,
    CHSTYLE_2D_LINE_COLUMN,
    CHSTYLE_2D_LINE_STACKEDCOLUMN,
    CHSTYLE_2D_STOCK_1,
    CHSTYLE_2D_STOCK_2,
    CHSTYLE_2D_STOCK_3,
    CHSTYLE_2D_STOCK_4,
    CHSTYLE_ADDIN
};

#define CHSTYLE_COUNT   (CHSTYLE_ADDIN + 1)

enum SvxChartDataDescr
{
    CHDESCR_NONE,
    CHDESCR_VALUE,
    CHDESCR_PERCENT,
    CHDESCR_TEXT,
    CHDESCR_TEXTANDPERCENT,
    CHDESCR_NUMFORMAT_PERCENT,
    CHDESCR_NUMFORMAT_VALUE,
    CHDESCR_TEXTANDVALUE
};

#define CHDESCR_COUNT	(CHDESCR_TEXTANDVALUE + 1)

enum SvxChartLegendPos
{
    CHLEGEND_NONE,
    CHLEGEND_LEFT,
    CHLEGEND_TOP,
    CHLEGEND_RIGHT,
    CHLEGEND_BOTTOM,
    CHLEGEND_NONE_TOP,
    CHLEGEND_NONE_LEFT,
    CHLEGEND_NONE_RIGHT,
    CHLEGEND_NONE_BOTTOM
};

#define CHLEGEND_COUNT	(CHLEGEND_BOTTOM + 1)

enum SvxChartTextOrder
{
    CHTXTORDER_SIDEBYSIDE,
    CHTXTORDER_UPDOWN,
    CHTXTORDER_DOWNUP,
    CHTXTORDER_AUTO
};

#define CHTXTORDER_COUNT	(CHTXTORDER_AUTO + 1)

enum SvxChartTextOrient
{
    CHTXTORIENT_AUTOMATIC,
    CHTXTORIENT_STANDARD,
    CHTXTORIENT_BOTTOMTOP,
    CHTXTORIENT_STACKED,
    CHTXTORIENT_TOPBOTTOM
};

#define CHTXTORIENT_COUNT	(CHTXTORIENT_TOPBOTTOM + 1)

enum SvxChartKindError
{
    CHERROR_NONE,
    CHERROR_VARIANT,
    CHERROR_SIGMA,
    CHERROR_PERCENT,
    CHERROR_BIGERROR,
    CHERROR_CONST
};

#define CHERROR_COUNT	(CHERROR_CONST + 1)

enum SvxChartIndicate
{
    CHINDICATE_NONE,
    CHINDICATE_BOTH,
    CHINDICATE_UP,
    CHINDICATE_DOWN
};

#define CHINDICATE_COUNT	(CHINDICATE_DOWN + 1)

enum SvxChartRegress
{
    CHREGRESS_NONE,
    CHREGRESS_LINEAR,
    CHREGRESS_LOG,
    CHREGRESS_EXP,
    CHREGRESS_POWER
};

#define CHREGRESS_COUNT	(CHREGRESS_POWER + 1)

//------------------------------------------------------------------

#ifdef ITEMID_CHARTSTYLE

class SvxChartStyleItem : public SfxEnumItem
{
public:
    TYPEINFO();
    SvxChartStyleItem(SvxChartStyle eStyle = CHSTYLE_2D_LINE,
                      USHORT nId = ITEMID_CHARTSTYLE);

    virtual SfxPoolItem* Clone(SfxItemPool* pPool = 0) const;

    USHORT GetValueCount() const { return CHSTYLE_COUNT; }
    SvxChartStyle GetValue() const
        { return (SvxChartStyle)SfxEnumItem::GetValue(); }
};

#endif

//------------------------------------------------------------------

#ifdef ITEMID_CHARTREGRESS


#endif

//------------------------------------------------------------------

#ifdef ITEMID_CHARTDATADESCR

class SvxChartDataDescrItem : public SfxEnumItem
{
public:
    TYPEINFO();
    SvxChartDataDescrItem(SvxChartDataDescr eDataDescr = CHDESCR_NONE,
                          USHORT nId = ITEMID_CHARTDATADESCR);
    SvxChartDataDescrItem(SvStream& rIn,
                          USHORT nId = ITEMID_CHARTDATADESCR);

    virtual SfxPoolItem* Clone(SfxItemPool* pPool = 0) const;
    virtual SfxPoolItem* Create(SvStream& rIn, USHORT nVer) const;

    USHORT GetValueCount() const { return CHDESCR_COUNT; }
    SvxChartDataDescr GetValue() const
        { return (SvxChartDataDescr)SfxEnumItem::GetValue(); }
};

#endif

//------------------------------------------------------------------

#ifdef ITEMID_CHARTLEGENDPOS

class SvxChartLegendPosItem : public SfxEnumItem
{
public:
    TYPEINFO();
    SvxChartLegendPosItem(SvxChartLegendPos eLegendPos = CHLEGEND_NONE,
                          USHORT nId = ITEMID_CHARTLEGENDPOS);
    SvxChartLegendPosItem(SvStream& rIn,
                          USHORT nId = ITEMID_CHARTLEGENDPOS);

    virtual SfxPoolItem* Clone(SfxItemPool* pPool = 0) const;
    virtual SfxPoolItem* Create(SvStream& rIn, USHORT nVer) const;

    USHORT GetValueCount() const { return CHLEGEND_COUNT; }
    SvxChartLegendPos GetValue() const
        { return (SvxChartLegendPos)SfxEnumItem::GetValue(); }
};

#endif

//------------------------------------------------------------------

#ifdef ITEMID_CHARTTEXTORDER

class SvxChartTextOrderItem : public SfxEnumItem
{
public:
    TYPEINFO();
    SvxChartTextOrderItem(SvxChartTextOrder eOrder = CHTXTORDER_SIDEBYSIDE,
                          USHORT nId = ITEMID_CHARTTEXTORDER);
    SvxChartTextOrderItem(SvStream& rIn,
                          USHORT nId = ITEMID_CHARTTEXTORDER);

    virtual SfxPoolItem* Clone(SfxItemPool* pPool = 0) const;
    virtual SfxPoolItem* Create(SvStream& rIn, USHORT nVer) const;

    USHORT GetValueCount() const { return CHTXTORDER_COUNT; }
    SvxChartTextOrder GetValue() const
        { return (SvxChartTextOrder)SfxEnumItem::GetValue(); }
};

#endif

//------------------------------------------------------------------

#ifdef ITEMID_CHARTTEXTORIENT

class SvxChartTextOrientItem : public SfxEnumItem
{
public:
    TYPEINFO();
    SvxChartTextOrientItem(SvxChartTextOrient eOrient = CHTXTORIENT_STANDARD,
                           USHORT nId = ITEMID_CHARTTEXTORIENT);
    SvxChartTextOrientItem(SvStream& rIn,
                           USHORT nId = ITEMID_CHARTTEXTORIENT);

    virtual SfxPoolItem* Clone(SfxItemPool* pPool = 0) const;
    virtual SfxPoolItem* Create(SvStream& rIn, USHORT nVer) const;

    USHORT GetValueCount() const { return CHTXTORDER_COUNT; }
    SvxChartTextOrient GetValue() const
        { return (SvxChartTextOrient)SfxEnumItem::GetValue(); }
};

#endif

//------------------------------------------------------------------

#ifdef ITEMID_CHARTKINDERROR


#endif

//------------------------------------------------------------------

#ifdef ITEMID_CHARTINDICATE


#endif

//------------------------------------------------------------------

#ifdef ITEMID_DOUBLE

class SvxDoubleItem : public SfxPoolItem
{
    double fVal;

public:
    TYPEINFO();
    SvxDoubleItem(double fValue = 0.0, USHORT nId = ITEMID_DOUBLE);
    SvxDoubleItem(const SvxDoubleItem& rItem);

    virtual	sal_Bool        	 QueryValue( ::com::sun::star::uno::Any& rVal, BYTE nMemberId = 0 ) const;
    virtual	sal_Bool			 PutValue( const ::com::sun::star::uno::Any& rVal, BYTE nMemberId = 0 );


    virtual int 			 operator == (const SfxPoolItem&) const;
    virtual SfxPoolItem* Clone(SfxItemPool *pPool = NULL) const;
    virtual SfxPoolItem* Create(SvStream& rIn, USHORT nVersion) const;
    virtual SvStream& Store(SvStream& rOut, USHORT nItemVersion ) const;



    double GetValue() const { return fVal; }
    void SetValue(double fNewVal) { fVal = fNewVal; }
};

#endif

}//end of namespace binfilter
#endif	 // _SVX_CHRTITEM_HXX

