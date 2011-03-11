/* -*- Mode: C++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */
/*************************************************************************
 *
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER.
 * 
 * Copyright 2000, 2010 Oracle and/or its affiliates.
 *
 * OpenOffice.org - a multi-platform office productivity suite
 *
 * This file is part of OpenOffice.org.
 *
 * OpenOffice.org is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License version 3
 * only, as published by the Free Software Foundation.
 *
 * OpenOffice.org is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License version 3 for more details
 * (a copy is included in the LICENSE file that accompanied this code).
 *
 * You should have received a copy of the GNU Lesser General Public License
 * version 3 along with OpenOffice.org.  If not, see
 * <http://www.openoffice.org/license.html>
 * for a copy of the LGPLv3 License.
 *
 ************************************************************************/

#include "SchXMLChartContext.hxx"
#include "SchXMLPlotAreaContext.hxx"
#include "SchXMLImport.hxx"

#include <tools/debug.hxx>

#include "xmlnmspe.hxx"
#include "nmspmap.hxx"
#include "xmluconv.hxx"
#include "prstylei.hxx"
#include "xexptran.hxx"

#include <com/sun/star/chart/XTwoAxisXSupplier.hpp>
#include <com/sun/star/chart/XTwoAxisYSupplier.hpp>
#include <com/sun/star/chart/XAxisZSupplier.hpp>
#include <com/sun/star/chart/ChartDataRowSource.hpp>
#include <com/sun/star/chart/ChartAxisAssign.hpp>
#include <com/sun/star/chart/X3DDisplay.hpp>
#include <com/sun/star/chart/XStatisticDisplay.hpp>

namespace binfilter {

using namespace ::com::sun::star;
using namespace ::binfilter::xmloff::token;

using ::rtl::OUString;

static SvXMLEnumMapEntry aXMLAxisClassMap[] =
{
    { XML_CATEGORY, 	SCH_XML_AXIS_CATEGORY	},
    { XML_DOMAIN,		SCH_XML_AXIS_DOMAIN		},
    { XML_VALUE,		SCH_XML_AXIS_VALUE		},
    { XML_SERIES,		SCH_XML_AXIS_SERIES		},
    { XML_TOKEN_INVALID, 0 }
};

SchXMLPlotAreaContext::SchXMLPlotAreaContext( SchXMLImportHelper& rImpHelper,
                                              SvXMLImport& rInImport, const ::rtl::OUString& rLocalName,
                                              uno::Sequence< chart::ChartSeriesAddress >& rSeriesAddresses,
                                              ::rtl::OUString& rCategoriesAddress,
                                              ::rtl::OUString& rChartAddress,
                                              ::rtl::OUString& rTableNumberList) :
        SvXMLImportContext( rInImport, XML_NAMESPACE_CHART, rLocalName ),
        mrImportHelper( rImpHelper ),
        mrSeriesAddresses( rSeriesAddresses ),
        mrCategoriesAddress( rCategoriesAddress ),
        mnDomainOffset( 0 ),
        mnNumOfLines( 0 ),
        mbStockHasVolume( sal_False ),
        mnSeries( 0 ),
        mnMaxSeriesLength( 0 ),
        maSceneImportHelper( rInImport ),
        mrChartAddress( rChartAddress ),
        mrTableNumberList( rTableNumberList )
{
    // get Diagram
    uno::Reference< chart::XChartDocument > xDoc( rImpHelper.GetChartDocument(), uno::UNO_QUERY );
    if( xDoc.is())
    {
        mxDiagram = xDoc->getDiagram();
    }
    DBG_ASSERT( mxDiagram.is(), "Couldn't get XDiagram" );

    // turn off all axes initially
    uno::Any aFalseBool;
    aFalseBool <<= (sal_Bool)(sal_False);

    uno::Reference< lang::XServiceInfo > xInfo( mxDiagram, uno::UNO_QUERY );
    uno::Reference< beans::XPropertySet > xProp( mxDiagram, uno::UNO_QUERY );
    if( xInfo.is() &&
        xProp.is())
    {
        try
        {
            if( xInfo->supportsService( ::rtl::OUString( RTL_CONSTASCII_USTRINGPARAM( "com.sun.star.chart.ChartAxisXSupplier" ))))
            {
                xProp->setPropertyValue(
                    ::rtl::OUString( RTL_CONSTASCII_USTRINGPARAM( "HasXAxis" )), aFalseBool );
                xProp->setPropertyValue(
                    ::rtl::OUString( RTL_CONSTASCII_USTRINGPARAM( "HasXAxisGrid" )), aFalseBool );
                xProp->setPropertyValue(
                    ::rtl::OUString( RTL_CONSTASCII_USTRINGPARAM( "HasXAxisDescription" )), aFalseBool );
            }
            if( xInfo->supportsService( ::rtl::OUString( RTL_CONSTASCII_USTRINGPARAM( "com.sun.star.chart.ChartTwoAxisXSupplier" ))))
            {
                xProp->setPropertyValue(
                    ::rtl::OUString( RTL_CONSTASCII_USTRINGPARAM( "HasSecondaryXAxis" )), aFalseBool );
                xProp->setPropertyValue(
                    ::rtl::OUString( RTL_CONSTASCII_USTRINGPARAM( "HasSecondaryXAxisDescription" )), aFalseBool );
            }

            if( xInfo->supportsService( ::rtl::OUString( RTL_CONSTASCII_USTRINGPARAM( "com.sun.star.chart.ChartAxisYSupplier" ))))
            {
                xProp->setPropertyValue(
                    ::rtl::OUString( RTL_CONSTASCII_USTRINGPARAM( "HasYAxis" )), aFalseBool );
                xProp->setPropertyValue(
                    ::rtl::OUString( RTL_CONSTASCII_USTRINGPARAM( "HasYAxisGrid" )), aFalseBool );
                xProp->setPropertyValue(
                    ::rtl::OUString( RTL_CONSTASCII_USTRINGPARAM( "HasYAxisDescription" )), aFalseBool );
            }
            if( xInfo->supportsService( ::rtl::OUString( RTL_CONSTASCII_USTRINGPARAM( "com.sun.star.chart.ChartTwoAxisYSupplier" ))))
            {
                xProp->setPropertyValue(
                    ::rtl::OUString( RTL_CONSTASCII_USTRINGPARAM( "HasSecondaryYAxis" )), aFalseBool );
                xProp->setPropertyValue(
                    ::rtl::OUString( RTL_CONSTASCII_USTRINGPARAM( "HasSecondaryYAxisDescription" )), aFalseBool );
            }

            if( xInfo->supportsService( ::rtl::OUString( RTL_CONSTASCII_USTRINGPARAM( "com.sun.star.chart.ChartAxisZSupplier" ))))
            {
                xProp->setPropertyValue(
                    ::rtl::OUString( RTL_CONSTASCII_USTRINGPARAM( "HasZAxis" )), aFalseBool );
                xProp->setPropertyValue(
                    ::rtl::OUString( RTL_CONSTASCII_USTRINGPARAM( "HasZAxisDescription" )), aFalseBool );
            }
            uno::Any aAny;
            chart::ChartDataRowSource eSource = chart::ChartDataRowSource_COLUMNS;
            aAny <<= eSource;
            xProp->setPropertyValue( ::rtl::OUString( RTL_CONSTASCII_USTRINGPARAM( "DataRowSource" )), aAny );
        }
        catch( beans::UnknownPropertyException )
        {
            OSL_FAIL( "Property required by service not supported" );
        }
    }
}

SchXMLPlotAreaContext::~SchXMLPlotAreaContext()
{}

SvXMLImportContext* SchXMLPlotAreaContext::CreateChildContext(
    USHORT nInPrefix,
    const ::rtl::OUString& rLocalName,
    const uno::Reference< xml::sax::XAttributeList >& xAttrList )
{
    SvXMLImportContext* pContext = 0;
    const SvXMLTokenMap& rTokenMap = mrImportHelper.GetPlotAreaElemTokenMap();

    switch( rTokenMap.Get( nInPrefix, rLocalName ))
    {
        case XML_TOK_PA_AXIS:
            pContext = new SchXMLAxisContext( mrImportHelper, GetImport(), rLocalName, mxDiagram, maAxes );
            break;

        case XML_TOK_PA_SERIES:
            {
                mrSeriesAddresses.realloc( mnSeries + 1 );
                pContext = new SchXMLSeriesContext( mrImportHelper, GetImport(), rLocalName,
                                                    mxDiagram, maAxes, mrSeriesAddresses[ mnSeries ],
                                                    maSeriesStyleList,
                                                    mnSeries, mnMaxSeriesLength, mnDomainOffset,
                                                    mnNumOfLines, mbStockHasVolume );
                mnSeries++;
            }
            break;

        case XML_TOK_PA_CATEGORIES:
            pContext = new SchXMLCategoriesDomainContext( mrImportHelper, GetImport(),
                                                          nInPrefix, rLocalName,
                                                          mrCategoriesAddress );
            break;

        case XML_TOK_PA_WALL:
            pContext = new SchXMLWallFloorContext( mrImportHelper, GetImport(), nInPrefix, rLocalName, mxDiagram,
                                                   SchXMLWallFloorContext::CONTEXT_TYPE_WALL );
            break;
        case XML_TOK_PA_FLOOR:
            pContext = new SchXMLWallFloorContext( mrImportHelper, GetImport(), nInPrefix, rLocalName, mxDiagram,
                                                   SchXMLWallFloorContext::CONTEXT_TYPE_FLOOR );
            break;

        case XML_TOK_PA_LIGHT_SOURCE:
            pContext = maSceneImportHelper.create3DLightContext( nInPrefix, rLocalName, xAttrList );
            break;

        // elements for stock charts
        case XML_TOK_PA_STOCK_GAIN:
            pContext = new SchXMLStockContext( mrImportHelper, GetImport(), nInPrefix, rLocalName, mxDiagram,
                                               SchXMLStockContext::CONTEXT_TYPE_GAIN );
            break;
        case XML_TOK_PA_STOCK_LOSS:
            pContext = new SchXMLStockContext( mrImportHelper, GetImport(), nInPrefix, rLocalName, mxDiagram,
                                               SchXMLStockContext::CONTEXT_TYPE_LOSS );
            break;
        case XML_TOK_PA_STOCK_RANGE:
            pContext = new SchXMLStockContext( mrImportHelper, GetImport(), nInPrefix, rLocalName, mxDiagram,
                                               SchXMLStockContext::CONTEXT_TYPE_RANGE );
            break;

        default:
            pContext = new SvXMLImportContext( GetImport(), nInPrefix, rLocalName );
    }

    return pContext;
}

void SchXMLPlotAreaContext::StartElement( const uno::Reference< xml::sax::XAttributeList >& xAttrList )
{
    uno::Any aTransMatrixAny;

    // initialize size and position
    uno::Reference< drawing::XShape > xDiaShape( mxDiagram, uno::UNO_QUERY );
    if( xDiaShape.is())
    {
        maSize = xDiaShape->getSize();
        maPosition = xDiaShape->getPosition();
    }

    // parse attributes
    sal_Int16 nAttrCount = xAttrList.is()? xAttrList->getLength(): 0;
    ::rtl::OUString aValue;
    const SvXMLTokenMap& rAttrTokenMap = mrImportHelper.GetPlotAreaAttrTokenMap();

    sal_Bool bColHasLabels = sal_False;
    sal_Bool bRowHasLabels = sal_False;

    for( sal_Int16 i = 0; i < nAttrCount; i++ )
    {
        ::rtl::OUString sAttrName = xAttrList->getNameByIndex( i );
        ::rtl::OUString aLclLocalName;
        ::rtl::OUString aLclValue = xAttrList->getValueByIndex( i );
        USHORT nLclPrefix = GetImport().GetNamespaceMap().GetKeyByAttrName( sAttrName, &aLclLocalName );

        switch( rAttrTokenMap.Get( nLclPrefix, aLclLocalName ))
        {
            case XML_TOK_PA_X:
                GetImport().GetMM100UnitConverter().convertMeasure( maPosition.X, aLclValue );
                break;
            case XML_TOK_PA_Y:
                GetImport().GetMM100UnitConverter().convertMeasure( maPosition.Y, aLclValue );
                break;
            case XML_TOK_PA_WIDTH:
                GetImport().GetMM100UnitConverter().convertMeasure( maSize.Width, aLclValue );
                break;
            case XML_TOK_PA_HEIGHT:
                GetImport().GetMM100UnitConverter().convertMeasure( maSize.Height, aLclValue );
                break;
            case XML_TOK_PA_STYLE_NAME:
                msAutoStyleName = aLclValue;
                break;
            case XML_TOK_PA_CHART_ADDRESS:
                mrChartAddress = aLclValue;
                break;
            case XML_TOK_PA_TABLE_NUMBER_LIST:
                mrTableNumberList = aLclValue;
                break;
            case XML_TOK_PA_DS_HAS_LABELS:
                {
                    if( aLclValue.equals( ::binfilter::xmloff::token::GetXMLToken( ::binfilter::xmloff::token::XML_BOTH )))
                        bColHasLabels = bRowHasLabels = sal_True;
                    else if( aLclValue.equals( ::binfilter::xmloff::token::GetXMLToken( ::binfilter::xmloff::token::XML_ROW )))
                        bRowHasLabels = sal_True;
                    else if( aLclValue.equals( ::binfilter::xmloff::token::GetXMLToken( ::binfilter::xmloff::token::XML_COLUMN )))
                        bColHasLabels = sal_True;
                }
                break;
            default:
                maSceneImportHelper.processSceneAttribute( nLclPrefix, aLclLocalName, aLclValue );
                break;
        }
    }

    uno::Reference< beans::XPropertySet > xDocProp( mrImportHelper.GetChartDocument(), uno::UNO_QUERY );
    if( xDocProp.is())
    {
        try
        {
            uno::Any aAny;
            aAny <<= (sal_Bool)(bColHasLabels);
            xDocProp->setPropertyValue(
                ::rtl::OUString( RTL_CONSTASCII_USTRINGPARAM( "DataSourceLabelsInFirstColumn" )),
                aAny );

            aAny <<= (sal_Bool)(bRowHasLabels);
            xDocProp->setPropertyValue(
                ::rtl::OUString( RTL_CONSTASCII_USTRINGPARAM( "DataSourceLabelsInFirstRow" )),
                aAny );
        }
        catch( beans::UnknownPropertyException )
        {
            DBG_ERRORFILE( "Properties missing" );
        }
    }

    // set properties
    uno::Reference< beans::XPropertySet > xProp( mxDiagram, uno::UNO_QUERY );
    if( msAutoStyleName.getLength())
    {
        if( xProp.is())
        {
            const SvXMLStylesContext* pStylesCtxt = mrImportHelper.GetAutoStylesContext();
            if( pStylesCtxt )
            {
                const SvXMLStyleContext* pStyle = pStylesCtxt->FindStyleChildContext(
                    mrImportHelper.GetChartFamilyID(), msAutoStyleName );

                if( pStyle && pStyle->ISA( XMLPropStyleContext ))
                    (( XMLPropStyleContext* )pStyle )->FillPropertySet( xProp );
            }

            // perform BuildChart to make scene etc. available
            uno::Reference< chart::XChartDocument > xDoc( mrImportHelper.GetChartDocument(), uno::UNO_QUERY );
            if( xDoc.is() &&
                xDoc->hasControllersLocked())
            {
                xDoc->unlockControllers();
                xDoc->lockControllers();
            }
        }
    }
}

void SchXMLPlotAreaContext::EndElement()
{
    sal_Int32 i;

    uno::Reference< beans::XPropertySet > xProp( mxDiagram, uno::UNO_QUERY );
    if( xProp.is())
    {
        sal_Bool bIsThreeDim = sal_False;
        uno::Any aAny = xProp->getPropertyValue( ::rtl::OUString( RTL_CONSTASCII_USTRINGPARAM( "Dim3D" )));
        aAny >>= bIsThreeDim;

        // set 3d scene attributes
        if( bIsThreeDim )
        {
            // set scene attributes at diagram
            maSceneImportHelper.setSceneAttributes( xProp );
        }

        if( mnNumOfLines > 0 &&
            0 == mxDiagram->getDiagramType().reverseCompareToAsciiL(
                RTL_CONSTASCII_STRINGPARAM( "com.sun.star.chart.BarDiagram" )))
        {
            try
            {
                xProp->setPropertyValue( ::rtl::OUString( RTL_CONSTASCII_USTRINGPARAM( "NumberOfLines" )),
                                         uno::makeAny( mnNumOfLines ));
            }
            catch( uno::Exception & aEx )
            {
                String aStr( aEx.Message );
                ByteString aBStr( aStr, RTL_TEXTENCODING_ASCII_US );
                OSL_TRACE( "Exception caught for property NumberOfLines: %s", aBStr.GetBuffer());
            }
        }

        // #i32366# stock has volume
        if( 0 == mxDiagram->getDiagramType().reverseCompareToAsciiL(
                RTL_CONSTASCII_STRINGPARAM( "com.sun.star.chart.StockDiagram" )))
        {
            try
            {
                xProp->setPropertyValue( ::rtl::OUString( RTL_CONSTASCII_USTRINGPARAM( "Volume" )),
                                         uno::makeAny( mbStockHasVolume ));
            }
            catch( uno::Exception & aEx )
            {
                String aStr( aEx.Message );
                ByteString aBStr( aStr, RTL_TEXTENCODING_ASCII_US );
                OSL_TRACE( "Exception caught for property NumberOfLines: %s", aBStr.GetBuffer());
            }
        }
    }

    // set changed size and position after properties (esp. 3d)
    uno::Reference< drawing::XShape > xDiaShape( mxDiagram, uno::UNO_QUERY );
    if( xDiaShape.is())
    {
        xDiaShape->setSize( maSize );
        xDiaShape->setPosition( maPosition );
    }

    // resize data so that all series and data point properties can be set
    mrImportHelper.ResizeChartData( mnSeries + mnDomainOffset, mnMaxSeriesLength );

    // set autostyles for series and data points
    const SvXMLStylesContext* pStylesCtxt = mrImportHelper.GetAutoStylesContext();
    const SvXMLStyleContext* pStyle = NULL;
    ::rtl::OUString sCurrStyleName;

    if( pStylesCtxt )
    {
        ::std::list< chartxml::DataRowPointStyle >::iterator iStyle;
        // iterate over series attributes first ...
        for( iStyle = maSeriesStyleList.begin(); iStyle != maSeriesStyleList.end(); iStyle++ )
        {
            if( iStyle->meType != chartxml::DataRowPointStyle::DATA_POINT )
            {
                // data row style
                for( i = 0; i < iStyle->mnRepeat; i++ )
                {
                    try
                    {
                        xProp = mxDiagram->getDataRowProperties( iStyle->mnSeries + i );

                        if( iStyle->meType != chartxml::DataRowPointStyle::DATA_SERIES &&
                            xProp.is() )
                        {
                            // we have a statistical proertyset
                            uno::Any aAny;
                            switch( iStyle->meType )
                            {
                                case chartxml::DataRowPointStyle::MEAN_VALUE:
                                    aAny = xProp->getPropertyValue(
                                        OUString( RTL_CONSTASCII_USTRINGPARAM(
                                                      "DataMeanValueProperties" )));
                                    break;
                                case chartxml::DataRowPointStyle::REGRESSION:
                                    aAny = xProp->getPropertyValue(
                                        OUString( RTL_CONSTASCII_USTRINGPARAM(
                                                      "DataRegressionProperties" )));
                                    break;
                                case chartxml::DataRowPointStyle::ERROR_INDICATOR:
                                    aAny = xProp->getPropertyValue(
                                        OUString( RTL_CONSTASCII_USTRINGPARAM(
                                                      "DataErrorProperties" )));
                                    break;
                                default:
                                    break;
                            }
                            aAny >>= xProp;
                        }

                        if( xProp.is())
                        {
                            if( (iStyle->msStyleName).getLength())
                            {
                                if( ! sCurrStyleName.equals( iStyle->msStyleName ))
                                {
                                    sCurrStyleName = iStyle->msStyleName;
                                    pStyle = pStylesCtxt->FindStyleChildContext(
                                        mrImportHelper.GetChartFamilyID(), sCurrStyleName );
                                }

                                if( pStyle && pStyle->ISA( XMLPropStyleContext ))
                                    (( XMLPropStyleContext* )pStyle )->FillPropertySet( xProp );
                            }

                            if( iStyle->meType == chartxml::DataRowPointStyle::DATA_SERIES &&
                                iStyle->mnAttachedAxis != 1 )
                            {
                                uno::Any aAny;
                                aAny <<= chart::ChartAxisAssign::SECONDARY_Y;

                                xProp->setPropertyValue( ::rtl::OUString( RTL_CONSTASCII_USTRINGPARAM( "Axis" )), aAny );
                            }
                        }
                    }
                    catch( uno::Exception aEx )
                    {
#ifdef DBG_UTIL
                        String aStr( aEx.Message );
                        ByteString aBStr( aStr, RTL_TEXTENCODING_ASCII_US );
                        OSL_TRACE( "PlotAreaContext:EndElement(): Exception caught: %s", aBStr.GetBuffer());
#endif
                    }
                }
            }
        }

        // ... then iterate over data-point attributes, so the latter are not overwritten
        for( iStyle = maSeriesStyleList.begin(); iStyle != maSeriesStyleList.end(); iStyle++ )
        {
            if( iStyle->mnIndex != -1 )
            {
                // data point style
                for( i = 0; i < iStyle->mnRepeat; i++ )
                {
                    try
                    {
                        xProp = mxDiagram->getDataPointProperties( iStyle->mnIndex + i, iStyle->mnSeries );

                        if( xProp.is())
                        {
                            if( ! sCurrStyleName.equals( iStyle->msStyleName ))
                            {
                                sCurrStyleName = iStyle->msStyleName;
                                pStyle = pStylesCtxt->FindStyleChildContext(
                                    mrImportHelper.GetChartFamilyID(), sCurrStyleName );
                            }

                            if( pStyle && pStyle->ISA( XMLPropStyleContext ))
                                (( XMLPropStyleContext* )pStyle )->FillPropertySet( xProp );
                        }
                    }
                    catch( uno::Exception aEx )
                    {
#ifdef DBG_UTIL
                        String aStr( aEx.Message );
                        ByteString aBStr( aStr, RTL_TEXTENCODING_ASCII_US );
                        OSL_TRACE( "PlotAreaContext:EndElement(): Exception caught: %s", aBStr.GetBuffer());
#endif
                    }
                }
            }
        }	// styles iterator
    }
}

// ========================================

SchXMLAxisContext::SchXMLAxisContext( SchXMLImportHelper& rImpHelper,
                                      SvXMLImport& rInImport, const ::rtl::OUString& rLocalName,
                                      uno::Reference< chart::XDiagram > xDiagram,
                                      ::std::vector< SchXMLAxis >& aAxes ) :
        SvXMLImportContext( rInImport, XML_NAMESPACE_CHART, rLocalName ),
        mrImportHelper( rImpHelper ),
        mxDiagram( xDiagram ),
        maAxes( aAxes )
{
}

SchXMLAxisContext::~SchXMLAxisContext()
{}

/* returns a shape for the current axis's title. The property
   "Has...AxisTitle" is set to "True" to get the shape
 */
uno::Reference< drawing::XShape > SchXMLAxisContext::getTitleShape()
{
    uno::Reference< drawing::XShape > xResult;
    uno::Any aTrueBool;
    aTrueBool <<= (sal_Bool)(sal_True);
    uno::Reference< beans::XPropertySet > xDiaProp( mxDiagram, uno::UNO_QUERY );

    uno::Reference< chart::XChartDocument > xDoc( mrImportHelper.GetChartDocument(), uno::UNO_QUERY );
    sal_Bool bHasControllersLocked = sal_False;
    if( xDoc.is() &&
        (bHasControllersLocked = xDoc->hasControllersLocked()) == sal_True )
        xDoc->unlockControllers();

    switch( maCurrentAxis.eClass )
    {
        case SCH_XML_AXIS_CATEGORY:
        case SCH_XML_AXIS_DOMAIN:
            if( maCurrentAxis.nIndexInCategory == 0 )
            {
                uno::Reference< chart::XAxisXSupplier > xSuppl( mxDiagram, uno::UNO_QUERY );
                if( xSuppl.is())
                {
                    if( xDiaProp.is())
                        xDiaProp->setPropertyValue( ::rtl::OUString( RTL_CONSTASCII_USTRINGPARAM( "HasXAxisTitle" )), aTrueBool );
                    xResult = uno::Reference< drawing::XShape >( xSuppl->getXAxisTitle(), uno::UNO_QUERY );
                }
            }
            break;
        case SCH_XML_AXIS_VALUE:
            if( maCurrentAxis.nIndexInCategory == 0 )
            {
                uno::Reference< chart::XAxisYSupplier > xSuppl( mxDiagram, uno::UNO_QUERY );
                if( xSuppl.is())
                {
                    if( xDiaProp.is())
                        xDiaProp->setPropertyValue( ::rtl::OUString( RTL_CONSTASCII_USTRINGPARAM( "HasYAxisTitle" )), aTrueBool );
                    xResult = uno::Reference< drawing::XShape >( xSuppl->getYAxisTitle(), uno::UNO_QUERY );
                }
            }
            break;
        case SCH_XML_AXIS_SERIES:
            {
                uno::Reference< chart::XAxisZSupplier > xSuppl( mxDiagram, uno::UNO_QUERY );
                if( xSuppl.is())
                {
                    if( xDiaProp.is())
                        xDiaProp->setPropertyValue( ::rtl::OUString( RTL_CONSTASCII_USTRINGPARAM( "HasZAxisTitle" )), aTrueBool );
                    xResult = uno::Reference< drawing::XShape >( xSuppl->getZAxisTitle(), uno::UNO_QUERY );
                }
            }
            break;
        default:
            break;
    }

    if( bHasControllersLocked && xDoc.is())
        xDoc->lockControllers();

    return xResult;
}

void SchXMLAxisContext::CreateGrid( ::rtl::OUString sAutoStyleName,
                                    sal_Bool bIsMajor )
{
    uno::Reference< chart::XDiagram > xDia = mrImportHelper.GetChartDocument()->getDiagram();
    uno::Reference< beans::XPropertySet > xGridProp;
    ::rtl::OUString sPropertyName;
    DBG_ASSERT( xDia.is(), "diagram object is invalid!" );

    switch( maCurrentAxis.eClass )
    {
        case SCH_XML_AXIS_CATEGORY:
        case SCH_XML_AXIS_DOMAIN:
            {
                uno::Reference< chart::XAxisXSupplier > xSuppl( xDia, uno::UNO_QUERY );
                if( xSuppl.is())
                {
                    if( bIsMajor )
                    {
                        xGridProp = xSuppl->getXMainGrid();
                        sPropertyName = ::rtl::OUString( RTL_CONSTASCII_USTRINGPARAM( "HasXAxisGrid" ));
                    }
                    else
                    {
                        xGridProp = xSuppl->getXHelpGrid();
                        sPropertyName = ::rtl::OUString( RTL_CONSTASCII_USTRINGPARAM( "HasXAxisHelpGrid" ));
                    }
                }
            }
            break;
        case SCH_XML_AXIS_VALUE:
            {
                uno::Reference< chart::XAxisYSupplier > xSuppl( xDia, uno::UNO_QUERY );
                if( xSuppl.is())
                {
                    if( bIsMajor )
                    {
                        xGridProp = xSuppl->getYMainGrid();
                        sPropertyName = ::rtl::OUString( RTL_CONSTASCII_USTRINGPARAM( "HasYAxisGrid" ));
                    }
                    else
                    {
                        xGridProp = xSuppl->getYHelpGrid();
                        sPropertyName = ::rtl::OUString( RTL_CONSTASCII_USTRINGPARAM( "HasYAxisHelpGrid" ));
                    }
                }
            }
            break;
        case SCH_XML_AXIS_SERIES:
            {
                uno::Reference< chart::XAxisZSupplier > xSuppl( xDia, uno::UNO_QUERY );
                if( xSuppl.is())
                {
                    if( bIsMajor )
                    {
                        xGridProp = xSuppl->getZMainGrid();
                        sPropertyName = ::rtl::OUString( RTL_CONSTASCII_USTRINGPARAM( "HasZAxisGrid" ));
                    }
                    else
                    {
                        xGridProp = xSuppl->getZHelpGrid();
                        sPropertyName = ::rtl::OUString( RTL_CONSTASCII_USTRINGPARAM( "HasZAxisHelpGrid" ));
                    }
                }
            }
            break;
        default:
            break;
    }

    // enable grid
    if( sPropertyName.getLength())
    {
        uno::Reference< beans::XPropertySet > xDiaProp( xDia, uno::UNO_QUERY );
        uno::Any aTrueBool;
        aTrueBool <<= (sal_Bool)(sal_True);
        if( xDiaProp.is())
        {
            try
            {
                xDiaProp->setPropertyValue( sPropertyName, aTrueBool );
            }
            catch( beans::UnknownPropertyException )
            {
                OSL_FAIL( "Cannot enable grid due to missing property" );
            }
        }
    }

    // set properties
    if( sAutoStyleName.getLength() &&
        xGridProp.is())
    {
        const SvXMLStylesContext* pStylesCtxt = mrImportHelper.GetAutoStylesContext();
        if( pStylesCtxt )
        {
            const SvXMLStyleContext* pStyle = pStylesCtxt->FindStyleChildContext(
                mrImportHelper.GetChartFamilyID(), sAutoStyleName );

            if( pStyle && pStyle->ISA( XMLPropStyleContext ))
                (( XMLPropStyleContext* )pStyle )->FillPropertySet( xGridProp );
        }
    }
}

void SchXMLAxisContext::StartElement( const uno::Reference< xml::sax::XAttributeList >& xAttrList )
{
    // parse attributes
    sal_Int16 nAttrCount = xAttrList.is()? xAttrList->getLength(): 0;
    SchXMLImport& rLclImport = ( SchXMLImport& )GetImport();
    const SvXMLTokenMap& rAttrTokenMap = mrImportHelper.GetAxisAttrTokenMap();

    for( sal_Int16 i = 0; i < nAttrCount; i++ )
    {
        ::rtl::OUString sAttrName = xAttrList->getNameByIndex( i );
        ::rtl::OUString aLclLocalName;
        ::rtl::OUString aLclValue = xAttrList->getValueByIndex( i );
        USHORT nLclPrefix = GetImport().GetNamespaceMap().GetKeyByAttrName( sAttrName, &aLclLocalName );

        switch( rAttrTokenMap.Get( nLclPrefix, aLclLocalName ))
        {
            case XML_TOK_AXIS_CLASS:
                {
                    USHORT nEnumVal;
                    if( rLclImport.GetMM100UnitConverter().convertEnum( nEnumVal, aLclValue, aXMLAxisClassMap ))
                        maCurrentAxis.eClass = ( SchXMLAxisClass )nEnumVal;
                }
                break;
            case XML_TOK_AXIS_NAME:
                maCurrentAxis.aName = aLclValue;
                break;
            case XML_TOK_AXIS_STYLE_NAME:
                msAutoStyleName = aLclValue;
                break;
        }
    }

    // check for number of axes with same category
    maCurrentAxis.nIndexInCategory = 0;
    sal_Int32 nNumOfAxes = maAxes.size();
    for( sal_Int32 nCurrent = 0; nCurrent < nNumOfAxes; nCurrent++ )
    {
        if( maAxes[ nCurrent ].eClass == maCurrentAxis.eClass )
            maCurrentAxis.nIndexInCategory++;
    }
}

void SchXMLAxisContext::EndElement()
{
    // add new Axis to list
    maAxes.push_back( maCurrentAxis );

    // set axis at chart
    uno::Reference< beans::XPropertySet > xDiaProp( mxDiagram, uno::UNO_QUERY );
    uno::Reference< beans::XPropertySet > xProp;
    uno::Any aTrueBool;
    aTrueBool <<= (sal_Bool)(sal_True);
    sal_Bool bHasTitle = ( maCurrentAxis.aTitle.getLength() > 0 );
    uno::Reference< frame::XModel > xDoc( mrImportHelper.GetChartDocument(), uno::UNO_QUERY );

    switch( maCurrentAxis.eClass )
    {
        case SCH_XML_AXIS_CATEGORY:
        case SCH_XML_AXIS_DOMAIN:
            if( maCurrentAxis.nIndexInCategory == 0 )
            {
                try
                {
                    xDiaProp->setPropertyValue(
                        ::rtl::OUString( RTL_CONSTASCII_USTRINGPARAM( "HasXAxis" )), aTrueBool );
                }
                catch( beans::UnknownPropertyException )
                {
                    OSL_FAIL( "Couldn't turn on x axis" );
                }
                uno::Reference< chart::XAxisXSupplier > xSuppl( mxDiagram, uno::UNO_QUERY );
                if( xSuppl.is())
                {
                    xProp = xSuppl->getXAxis();
                    if( bHasTitle )
                    {
                        uno::Reference< beans::XPropertySet > xTitleProp( xSuppl->getXAxisTitle(), uno::UNO_QUERY );
                        if( xTitleProp.is())
                        {
                            try
                            {
                                uno::Any aAny;
                                aAny <<= maCurrentAxis.aTitle;
                                xTitleProp->setPropertyValue( ::rtl::OUString( RTL_CONSTASCII_USTRINGPARAM( "String" )), aAny );
                            }
                            catch( beans::UnknownPropertyException )
                            {
                                OSL_FAIL( "Property String for Title not available" );
                            }
                            uno::Reference< drawing::XShape > xShape( xTitleProp, uno::UNO_QUERY );
                            if( xShape.is())
                            {
                                // perform build chart with new title string
                                // so that setting the position works correctly
                                if( xDoc.is())
                                {
                                    xDoc->unlockControllers();
                                    xDoc->lockControllers();
                                }
                                xShape->setPosition( maCurrentAxis.aPosition );
                            }
                        }
                    }
                }
            }
            else
            {
                try
                {
                    xDiaProp->setPropertyValue(
                        ::rtl::OUString( RTL_CONSTASCII_USTRINGPARAM( "HasSecondaryXAxis" )), aTrueBool );
                }
                catch( beans::UnknownPropertyException )
                {
                    OSL_FAIL( "Couldn't turn on second x axis" );
                }
                uno::Reference< chart::XTwoAxisXSupplier > xSuppl( mxDiagram, uno::UNO_QUERY );
                if( xSuppl.is())
                    xProp = xSuppl->getSecondaryXAxis();
            }
            break;

        case SCH_XML_AXIS_VALUE:
            if( maCurrentAxis.nIndexInCategory == 0 )
            {
                try
                {
                    xDiaProp->setPropertyValue(
                        ::rtl::OUString( RTL_CONSTASCII_USTRINGPARAM( "HasYAxis" )), aTrueBool );
                }
                catch( beans::UnknownPropertyException )
                {
                    OSL_FAIL( "Couldn't turn on y axis" );
                }
                uno::Reference< chart::XAxisYSupplier > xSuppl( mxDiagram, uno::UNO_QUERY );
                if( xSuppl.is())
                {
                    xProp = xSuppl->getYAxis();
                    if( bHasTitle )
                    {
                        uno::Reference< beans::XPropertySet > xTitleProp( xSuppl->getYAxisTitle(), uno::UNO_QUERY );
                        if( xTitleProp.is())
                        {
                            try
                            {
                                uno::Any aAny;
                                aAny <<= maCurrentAxis.aTitle;
                                xTitleProp->setPropertyValue( ::rtl::OUString( RTL_CONSTASCII_USTRINGPARAM( "String" )), aAny );
                            }
                            catch( beans::UnknownPropertyException )
                            {
                                OSL_FAIL( "Property String for Title not available" );
                            }
                            uno::Reference< drawing::XShape > xShape( xTitleProp, uno::UNO_QUERY );
                            if( xShape.is())
                            {
                                // perform build chart with new title string
                                // so that setting the position works correctly
                                if( xDoc.is())
                                {
                                    xDoc->unlockControllers();
                                    xDoc->lockControllers();
                                }
                                xShape->setPosition( maCurrentAxis.aPosition );
                            }
                        }
                    }
                }
            }
            else
            {
                try
                {
                    xDiaProp->setPropertyValue(
                        ::rtl::OUString( RTL_CONSTASCII_USTRINGPARAM( "HasSecondaryYAxis" )), aTrueBool );
                }
                catch( beans::UnknownPropertyException )
                {
                    OSL_FAIL( "Couldn't turn on second y axis" );
                }
                uno::Reference< chart::XTwoAxisYSupplier > xSuppl( mxDiagram, uno::UNO_QUERY );
                if( xSuppl.is())
                    xProp = xSuppl->getSecondaryYAxis();
            }
            break;

        case SCH_XML_AXIS_SERIES:
            {
                try
                {
                    xDiaProp->setPropertyValue(
                        ::rtl::OUString( RTL_CONSTASCII_USTRINGPARAM( "HasZAxis" )), aTrueBool );
                }
                catch( beans::UnknownPropertyException )
                {
                    OSL_FAIL( "Couldn't turn on z axis" );
                }
                uno::Reference< chart::XAxisZSupplier > xSuppl( mxDiagram, uno::UNO_QUERY );
                if( xSuppl.is())
                {
                    xProp = xSuppl->getZAxis();
                    if( bHasTitle )
                    {
                        uno::Reference< beans::XPropertySet > xTitleProp( xSuppl->getZAxisTitle(), uno::UNO_QUERY );
                        if( xTitleProp.is())
                        {
                            try
                            {
                                uno::Any aAny;
                                aAny <<= maCurrentAxis.aTitle;
                                xTitleProp->setPropertyValue( ::rtl::OUString( RTL_CONSTASCII_USTRINGPARAM( "String" )), aAny );
                            }
                            catch( beans::UnknownPropertyException )
                            {
                                OSL_FAIL( "Property String for Title not available" );
                            }
                            uno::Reference< drawing::XShape > xShape( xTitleProp, uno::UNO_QUERY );
                            if( xShape.is())
                            {
                                // perform build chart with new title string
                                // so that setting the position works correctly
                                if( xDoc.is())
                                {
                                    xDoc->unlockControllers();
                                    xDoc->lockControllers();
                                }
                                xShape->setPosition( maCurrentAxis.aPosition );
                            }
                        }
                    }
                }
            }
            break;
        default:
            break;
    }

    // set properties
    if( msAutoStyleName.getLength() &&
        xProp.is())
    {
        // #88077# AutoOrigin 'on' is default
        xProp->setPropertyValue( ::rtl::OUString( RTL_CONSTASCII_USTRINGPARAM( "AutoOrigin" )), aTrueBool );

        const SvXMLStylesContext* pStylesCtxt = mrImportHelper.GetAutoStylesContext();
        if( pStylesCtxt )
        {
            const SvXMLStyleContext* pStyle = pStylesCtxt->FindStyleChildContext(
                mrImportHelper.GetChartFamilyID(), msAutoStyleName );

            if( pStyle && pStyle->ISA( XMLPropStyleContext ))
                (( XMLPropStyleContext* )pStyle )->FillPropertySet( xProp );
        }
    }
}

SvXMLImportContext* SchXMLAxisContext::CreateChildContext(
    USHORT nInPrefix,
    const ::rtl::OUString& rLocalName,
    const uno::Reference< xml::sax::XAttributeList >& xAttrList )
{
    SvXMLImportContext* pContext = 0;
    SchXMLImport& rLclImport = ( SchXMLImport& )GetImport();

    if( nInPrefix == XML_NAMESPACE_CHART )
    {
        if( IsXMLToken( rLocalName, XML_TITLE ) )
        {
            uno::Reference< drawing::XShape > xTitleShape = getTitleShape();
            pContext = new SchXMLTitleContext( mrImportHelper, rLclImport, rLocalName,
                                               maCurrentAxis.aTitle,
                                               xTitleShape,
                                               maCurrentAxis.aPosition );
        }
        else if( IsXMLToken( rLocalName, XML_GRID ) )
        {
            sal_Int16 nAttrCount = xAttrList.is()? xAttrList->getLength(): 0;
            sal_Bool bIsMajor = sal_True;		// default value for class is "major"
            ::rtl::OUString sAutoStyleName;

            for( sal_Int16 i = 0; i < nAttrCount; i++ )
            {
                ::rtl::OUString sAttrName = xAttrList->getNameByIndex( i );
                ::rtl::OUString aLclLocalName;
                USHORT nLclPrefix = GetImport().GetNamespaceMap().GetKeyByAttrName( sAttrName, &aLclLocalName );

                if( nLclPrefix == XML_NAMESPACE_CHART )
                {
                    if( IsXMLToken( aLclLocalName, XML_CLASS ) )
                    {
                        if( IsXMLToken( xAttrList->getValueByIndex( i ), XML_MINOR ) )
                            bIsMajor = sal_False;
                    }
                    else if( IsXMLToken( aLclLocalName, XML_STYLE_NAME ) )
                        sAutoStyleName = xAttrList->getValueByIndex( i );
                }
            }

            CreateGrid( sAutoStyleName, bIsMajor );

            // don't create a context => use default context. grid elements are empty
        }
    }

    if( ! pContext )
        pContext = new SvXMLImportContext( rLclImport, nInPrefix, rLocalName );

    return pContext;
}

// ========================================

SchXMLSeriesContext::SchXMLSeriesContext(
    SchXMLImportHelper& rImpHelper,
    SvXMLImport& rInImport, const ::rtl::OUString& rLocalName,
    uno::Reference< chart::XDiagram >& xDiagram,
    std::vector< SchXMLAxis >& rAxes,
    ::com::sun::star::chart::ChartSeriesAddress& rSeriesAddress,
    ::std::list< chartxml::DataRowPointStyle >& rStyleList,
    sal_Int32 nSeriesIndex,
    sal_Int32& rMaxSeriesLength,
    sal_Int32& rDomainOffset,
    sal_Int32& rNumOfLines,
    sal_Bool&  rStockHasVolume ) :
        SvXMLImportContext( rInImport, XML_NAMESPACE_CHART, rLocalName ),
        mrImportHelper( rImpHelper ),
        mxDiagram( xDiagram ),
        mrAxes( rAxes ),
        mrSeriesAddress( rSeriesAddress ),
        mrStyleList( rStyleList ),
        mnSeriesIndex( nSeriesIndex ),
        mnDataPointIndex( 0 ),
        mrMaxSeriesLength( rMaxSeriesLength ),
        mrDomainOffset( rDomainOffset ),
        mrNumOfLines( rNumOfLines ),
        mrStockHasVolume( rStockHasVolume ),
        mpAttachedAxis( NULL )
{
}

SchXMLSeriesContext::~SchXMLSeriesContext()
{
}

void SchXMLSeriesContext::StartElement( const uno::Reference< xml::sax::XAttributeList >& xAttrList )
{
    // parse attributes
    sal_Int16 nAttrCount = xAttrList.is()? xAttrList->getLength(): 0;
    const SvXMLTokenMap& rAttrTokenMap = mrImportHelper.GetSeriesAttrTokenMap();
    mnAttachedAxis = 1;

    for( sal_Int16 i = 0; i < nAttrCount; i++ )
    {
        ::rtl::OUString sAttrName = xAttrList->getNameByIndex( i );
        ::rtl::OUString aLclLocalName;
        ::rtl::OUString aValue = xAttrList->getValueByIndex( i );
        USHORT nLclPrefix = GetImport().GetNamespaceMap().GetKeyByAttrName( sAttrName, &aLclLocalName );

        switch( rAttrTokenMap.Get( nLclPrefix, aLclLocalName ))
        {
            case XML_TOK_SERIES_CELL_RANGE:
                mrSeriesAddress.DataRangeAddress = aValue;
                break;
            case XML_TOK_SERIES_LABEL_ADDRESS:
                mrSeriesAddress.LabelAddress = aValue;
                break;
            case XML_TOK_SERIES_ATTACHED_AXIS:
                {
                    sal_Int32 nNumOfAxes = mrAxes.size();
                    for( sal_Int32 nCurrent = 0; nCurrent < nNumOfAxes; nCurrent++ )
                    {
                        if( aValue.equals( mrAxes[ nCurrent ].aName ) &&
                            mrAxes[ nCurrent ].eClass == SCH_XML_AXIS_VALUE )
                        {
                            mpAttachedAxis = &( mrAxes[ nCurrent ] );
                        }
                    }
                }
                break;
            case XML_TOK_SERIES_STYLE_NAME:
                msAutoStyleName = aValue;
                break;
            case XML_TOK_SERIES_CHART_CLASS:
                {
                    // used for bar-line combi chart
                    OUString aStrippedValue( aValue );
                    sal_Int32 nColonPos( aValue.indexOf( sal_Unicode(':')));
                    if( nColonPos != -1 )
                        aStrippedValue = aValue.copy( nColonPos + 1 );
                    if( IsXMLToken( aStrippedValue, XML_LINE ))
                        ++mrNumOfLines;
                    if( IsXMLToken( aStrippedValue, XML_BAR ))
                        mrStockHasVolume = sal_True;
                }
                break;
        }
    }

    if( mpAttachedAxis )
    {
        if( mpAttachedAxis->nIndexInCategory > 0 )
        {
            // secondary axis => property has to be set (primary is default)
            mnAttachedAxis = 2;
        }
    }
}

void SchXMLSeriesContext::EndElement()
{
    if( mrMaxSeriesLength < mnDataPointIndex )
        mrMaxSeriesLength = mnDataPointIndex;

    if( msAutoStyleName.getLength() ||
        mnAttachedAxis != 1 )
    {
        chartxml::DataRowPointStyle aStyle(
            chartxml::DataRowPointStyle::DATA_SERIES,
            mnSeriesIndex + mrDomainOffset, -1, 1,
            msAutoStyleName, mnAttachedAxis );
        mrStyleList.push_back( aStyle );
    }
}

SvXMLImportContext* SchXMLSeriesContext::CreateChildContext(
    USHORT nInPrefix,
    const ::rtl::OUString& rLocalName,
    const uno::Reference< xml::sax::XAttributeList >& /*xAttrList*/ )
{
    SvXMLImportContext* pContext = 0;
    const SvXMLTokenMap& rTokenMap = mrImportHelper.GetSeriesElemTokenMap();

    switch( rTokenMap.Get( nInPrefix, rLocalName ))
    {
        case XML_TOK_SERIES_DOMAIN:
            {
                sal_Int32 nIndex = mrSeriesAddress.DomainRangeAddresses.getLength();
                mrSeriesAddress.DomainRangeAddresses.realloc( nIndex + 1 );
                mrDomainOffset++;
                pContext = new SchXMLCategoriesDomainContext(
                    mrImportHelper, GetImport(),
                    nInPrefix, rLocalName,
                    mrSeriesAddress.DomainRangeAddresses[ nIndex ] );
            }
            break;

        case XML_TOK_SERIES_MEAN_VALUE_LINE:
            pContext = new SchXMLStatisticsObjectContext(
                mrImportHelper, GetImport(),
                nInPrefix, rLocalName,
                mrStyleList, mnSeriesIndex + mrDomainOffset,
                SchXMLStatisticsObjectContext::CONTEXT_TYPE_MEAN_VALUE_LINE );
            break;
        case XML_TOK_SERIES_REGRESSION_CURVE:
            pContext = new SchXMLStatisticsObjectContext(
                mrImportHelper, GetImport(),
                nInPrefix, rLocalName,
                mrStyleList, mnSeriesIndex + mrDomainOffset,
                SchXMLStatisticsObjectContext::CONTEXT_TYPE_REGRESSION_CURVE );
            break;
        case XML_TOK_SERIES_ERROR_INDICATOR:
            pContext = new SchXMLStatisticsObjectContext(
                mrImportHelper, GetImport(),
                nInPrefix, rLocalName,
                mrStyleList, mnSeriesIndex + mrDomainOffset,
                SchXMLStatisticsObjectContext::CONTEXT_TYPE_ERROR_INDICATOR );
            break;

        case XML_TOK_SERIES_DATA_POINT:
            pContext = new SchXMLDataPointContext( mrImportHelper, GetImport(), rLocalName, mxDiagram,
                                                   mrStyleList, mnSeriesIndex + mrDomainOffset, mnDataPointIndex );
            break;

        default:
            pContext = new SvXMLImportContext( GetImport(), nInPrefix, rLocalName );
    }

    return pContext;
}

// ========================================

SchXMLDataPointContext::SchXMLDataPointContext(  SchXMLImportHelper& rImpHelper,
                                                 SvXMLImport& rInImport, const ::rtl::OUString& rLocalName,
                                                 uno::Reference< chart::XDiagram >& xDiagram,
                                                 ::std::list< chartxml::DataRowPointStyle >& rStyleList,
                                                 sal_Int32 nSeries, sal_Int32& rIndex ) :
        SvXMLImportContext( rInImport, XML_NAMESPACE_CHART, rLocalName ),
        mrImportHelper( rImpHelper ),
        mxDiagram( xDiagram ),
        mrStyleList( rStyleList ),
        mnSeries( nSeries ),
        mrIndex( rIndex )
{
}

SchXMLDataPointContext::~SchXMLDataPointContext()
{
}

void SchXMLDataPointContext::StartElement( const uno::Reference< xml::sax::XAttributeList >& xAttrList )
{
    sal_Int16 nAttrCount = xAttrList.is()? xAttrList->getLength(): 0;
    ::rtl::OUString aValue;
    ::rtl::OUString sAutoStyleName;
    sal_Int32 nRepeat = 1;

    for( sal_Int16 i = 0; i < nAttrCount; i++ )
    {
        ::rtl::OUString sAttrName = xAttrList->getNameByIndex( i );
        ::rtl::OUString aLclLocalName;
        USHORT nLclPrefix = GetImport().GetNamespaceMap().GetKeyByAttrName( sAttrName, &aLclLocalName );

        if( nLclPrefix == XML_NAMESPACE_CHART )
        {
            if( IsXMLToken( aLclLocalName, XML_STYLE_NAME ) )
                sAutoStyleName = xAttrList->getValueByIndex( i );
            else if( IsXMLToken( aLclLocalName, XML_REPEATED ) )
                nRepeat = xAttrList->getValueByIndex( i ).toInt32();
        }
    }

    if( sAutoStyleName.getLength())
    {
        chartxml::DataRowPointStyle aStyle(
            chartxml::DataRowPointStyle::DATA_POINT,
            mnSeries, mrIndex, nRepeat, sAutoStyleName );
        mrStyleList.push_back( aStyle );
    }
    mrIndex += nRepeat;
}

// ========================================

SchXMLCategoriesDomainContext::SchXMLCategoriesDomainContext(
    SchXMLImportHelper& rImpHelper,
    SvXMLImport& rInImport,
    sal_uInt16 nInPrefix,
    const ::rtl::OUString& rLocalName,
    ::rtl::OUString& rAddress ) :
        SvXMLImportContext( rInImport, nInPrefix, rLocalName ),
        mrImportHelper( rImpHelper ),
        mrAddress( rAddress )
{
}

SchXMLCategoriesDomainContext::~SchXMLCategoriesDomainContext()
{
}

void SchXMLCategoriesDomainContext::StartElement( const uno::Reference< xml::sax::XAttributeList >& xAttrList )
{
    sal_Int16 nAttrCount = xAttrList.is()? xAttrList->getLength(): 0;

    for( sal_Int16 i = 0; i < nAttrCount; i++ )
    {
        ::rtl::OUString sAttrName = xAttrList->getNameByIndex( i );
        ::rtl::OUString aLclLocalName;
        USHORT nLclPrefix = GetImport().GetNamespaceMap().GetKeyByAttrName( sAttrName, &aLclLocalName );

        if( nLclPrefix == XML_NAMESPACE_TABLE &&
            IsXMLToken( aLclLocalName, XML_CELL_RANGE_ADDRESS ) )
        {
            mrAddress = xAttrList->getValueByIndex( i );
        }
    }
}

// ========================================

SchXMLWallFloorContext::SchXMLWallFloorContext(
    SchXMLImportHelper& rImpHelper,
    SvXMLImport& rInImport,
    sal_uInt16 nInPrefix,
    const ::rtl::OUString& rLocalName,
    uno::Reference< chart::XDiagram >& xDiagram,
    ContextType eContextType ) :
        SvXMLImportContext( rInImport, nInPrefix, rLocalName ),
        mrImportHelper( rImpHelper ),
        mxWallFloorSupplier( xDiagram, uno::UNO_QUERY ),
        meContextType( eContextType )
{
}

SchXMLWallFloorContext::~SchXMLWallFloorContext()
{
}

void SchXMLWallFloorContext::StartElement( const uno::Reference< xml::sax::XAttributeList >& xAttrList )
{
    if( mxWallFloorSupplier.is())
    {
        sal_Int16 nAttrCount = xAttrList.is()? xAttrList->getLength(): 0;
        ::rtl::OUString sAutoStyleName;

        for( sal_Int16 i = 0; i < nAttrCount; i++ )
        {
            ::rtl::OUString sAttrName = xAttrList->getNameByIndex( i );
            ::rtl::OUString aLclLocalName;
            USHORT nLclPrefix = GetImport().GetNamespaceMap().GetKeyByAttrName( sAttrName, &aLclLocalName );

            if( nLclPrefix == XML_NAMESPACE_CHART &&
                IsXMLToken( aLclLocalName, XML_STYLE_NAME ) )
            {
                sAutoStyleName = xAttrList->getValueByIndex( i );
            }
        }

        if( sAutoStyleName.getLength())
        {
            // set properties
            uno::Reference< beans::XPropertySet > xProp( ( meContextType == CONTEXT_TYPE_WALL )
                                                         ? mxWallFloorSupplier->getWall()
                                                         : mxWallFloorSupplier->getFloor(),
                                                         uno::UNO_QUERY );
            if( xProp.is())
            {
                const SvXMLStylesContext* pStylesCtxt = mrImportHelper.GetAutoStylesContext();
                if( pStylesCtxt )
                {
                    const SvXMLStyleContext* pStyle = pStylesCtxt->FindStyleChildContext(
                        mrImportHelper.GetChartFamilyID(), sAutoStyleName );

                    if( pStyle && pStyle->ISA( XMLPropStyleContext ))
                        (( XMLPropStyleContext* )pStyle )->FillPropertySet( xProp );
                }
            }
        }
    }
}

// ========================================

SchXMLStockContext::SchXMLStockContext(
    SchXMLImportHelper& rImpHelper,
    SvXMLImport& rInImport,
    sal_uInt16 nInPrefix,
    const ::rtl::OUString& rLocalName,
    uno::Reference< chart::XDiagram >& xDiagram,
    ContextType eContextType ) :
        SvXMLImportContext( rInImport, nInPrefix, rLocalName ),
        mrImportHelper( rImpHelper ),
        mxStockPropProvider( xDiagram, uno::UNO_QUERY ),
        meContextType( eContextType )
{
}

SchXMLStockContext::~SchXMLStockContext()
{
}

void SchXMLStockContext::StartElement( const uno::Reference< xml::sax::XAttributeList >& xAttrList )
{
    if( mxStockPropProvider.is())
    {
        sal_Int16 nAttrCount = xAttrList.is()? xAttrList->getLength(): 0;
        ::rtl::OUString sAutoStyleName;

        for( sal_Int16 i = 0; i < nAttrCount; i++ )
        {
            ::rtl::OUString sAttrName = xAttrList->getNameByIndex( i );
            ::rtl::OUString aLclLocalName;
            USHORT nLclPrefix = GetImport().GetNamespaceMap().GetKeyByAttrName( sAttrName, &aLclLocalName );

            if( nLclPrefix == XML_NAMESPACE_CHART &&
                IsXMLToken( aLclLocalName, XML_STYLE_NAME ) )
            {
                sAutoStyleName = xAttrList->getValueByIndex( i );
            }
        }

        if( sAutoStyleName.getLength())
        {
            // set properties
            uno::Reference< beans::XPropertySet > xProp;
            switch( meContextType )
            {
                case CONTEXT_TYPE_GAIN:
                    xProp = mxStockPropProvider->getUpBar();
                    break;
                case CONTEXT_TYPE_LOSS:
                    xProp = mxStockPropProvider->getDownBar();
                    break;
                case CONTEXT_TYPE_RANGE:
                    xProp = mxStockPropProvider->getMinMaxLine();
                    break;
            }
            if( xProp.is())
            {
                const SvXMLStylesContext* pStylesCtxt = mrImportHelper.GetAutoStylesContext();
                if( pStylesCtxt )
                {
                    const SvXMLStyleContext* pStyle = pStylesCtxt->FindStyleChildContext(
                        mrImportHelper.GetChartFamilyID(), sAutoStyleName );

                    if( pStyle && pStyle->ISA( XMLPropStyleContext ))
                        (( XMLPropStyleContext* )pStyle )->FillPropertySet( xProp );
                }
            }
        }
    }
}

// ========================================

SchXMLStatisticsObjectContext::SchXMLStatisticsObjectContext(

    SchXMLImportHelper& rImpHelper,
    SvXMLImport& rInImport,
    sal_uInt16 nInPrefix,
    const ::rtl::OUString& rLocalName,
    ::std::list< chartxml::DataRowPointStyle >& rStyleList,
    sal_Int32 nSeries, ContextType eContextType ) :

        SvXMLImportContext( rInImport, nInPrefix, rLocalName ),
        mrImportHelper( rImpHelper ),
        mrStyleList( rStyleList ),
        mnSeriesIndex( nSeries ),
        meContextType( eContextType )
{}

SchXMLStatisticsObjectContext::~SchXMLStatisticsObjectContext()
{
}

void SchXMLStatisticsObjectContext::StartElement( const uno::Reference< xml::sax::XAttributeList >& xAttrList )
{
    sal_Int16 nAttrCount = xAttrList.is()? xAttrList->getLength(): 0;
    ::rtl::OUString aValue;
    ::rtl::OUString sAutoStyleName;

    for( sal_Int16 i = 0; i < nAttrCount; i++ )
    {
        ::rtl::OUString sAttrName = xAttrList->getNameByIndex( i );
        ::rtl::OUString aLclLocalName;
        USHORT nLclPrefix = GetImport().GetNamespaceMap().GetKeyByAttrName( sAttrName, &aLclLocalName );

        if( nLclPrefix == XML_NAMESPACE_CHART )
        {
            if( IsXMLToken( aLclLocalName, XML_STYLE_NAME ) )
                sAutoStyleName = xAttrList->getValueByIndex( i );
        }
    }

    if( sAutoStyleName.getLength())
    {
        chartxml::DataRowPointStyle::StyleType eType = chartxml::DataRowPointStyle::MEAN_VALUE;
        switch( meContextType )
        {
            case CONTEXT_TYPE_MEAN_VALUE_LINE:
                eType = chartxml::DataRowPointStyle::MEAN_VALUE;
                break;
            case CONTEXT_TYPE_REGRESSION_CURVE:
                eType = chartxml::DataRowPointStyle::REGRESSION;
                break;
            case CONTEXT_TYPE_ERROR_INDICATOR:
                eType = chartxml::DataRowPointStyle::ERROR_INDICATOR;
                break;
        }
        chartxml::DataRowPointStyle aStyle(
            eType, mnSeriesIndex, -1, 1, sAutoStyleName );
        mrStyleList.push_back( aStyle );
    }
}
}//end of namespace binfilter

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
