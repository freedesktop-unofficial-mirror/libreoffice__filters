/*************************************************************************
 *
 *  $RCSfile: SchXMLPlotAreaContext.hxx,v $
 *
 *  $Revision: 1.1 $
 *
 *  last change: $Author: aw $ $Date: 2003-12-05 09:30:41 $
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
#ifndef _SCH_XMLPLOTAREACONTEXT_HXX_
#define _SCH_XMLPLOTAREACONTEXT_HXX_

#ifndef _XMLOFF_XMLICTXT_HXX
#include "xmlictxt.hxx"
#endif
#ifndef _XMLOFF_SHAPEIMPORT_HXX_
#include "shapeimport.hxx"
#endif

#ifndef _COM_SUN_STAR_UNO_SEQUENCE_H_ 
#include <com/sun/star/uno/Sequence.h>
#endif
#ifndef _COM_SUN_STAR_CHART_CHARTSERIESADDRESS_HPP_
#include <com/sun/star/chart/ChartSeriesAddress.hpp>
#endif

#include <list>

#include "transporttypes.hxx"
namespace com { namespace sun { namespace star {
    namespace chart {
        class XDiagram;
        class X3DDisplay;
        class XStatisticDisplay;
    }
    namespace xml { namespace sax {
        class XAttributeList;
}}}}}
namespace binfilter {

class SvXMLImport;



// ----------------------------------------

namespace chartxml 
{
    
struct DataRowPointStyle
{
    enum StyleType
    {
        DATA_POINT,
        DATA_SERIES,
        MEAN_VALUE,
        REGRESSION,
        ERROR_INDICATOR
    };

    StyleType meType;
    sal_Int32 mnSeries;
    sal_Int32 mnIndex;
    sal_Int32 mnRepeat;
    ::rtl::OUString msStyleName;
    sal_Int32 mnAttachedAxis;

    DataRowPointStyle( StyleType eType,
                       sal_Int32 nSeries, sal_Int32 nIndex, sal_Int32 nRepeat, ::rtl::OUString sStyleName,
                       sal_Int32 nAttachedAxis = 0 ) :
            meType( eType ),
            mnSeries( nSeries ),
            mnIndex( nIndex ),
            mnRepeat( nRepeat ),
            msStyleName( sStyleName ),
            mnAttachedAxis( nAttachedAxis )
        {}
};

}	// namespace


// ----------------------------------------

class SchXMLPlotAreaContext : public SvXMLImportContext
{
private:
    SchXMLImportHelper& mrImportHelper;
    ::com::sun::star::uno::Reference< ::com::sun::star::chart::XDiagram > mxDiagram;
    std::vector< SchXMLAxis > maAxes;
    ::com::sun::star::uno::Sequence< ::com::sun::star::chart::ChartSeriesAddress >& mrSeriesAddresses;
    ::rtl::OUString& mrCategoriesAddress;
    ::std::list< chartxml::DataRowPointStyle > maSeriesStyleList;
    sal_Int32 mnDomainOffset;
    sal_Int32 mnSeries;
    sal_Int32 mnMaxSeriesLength;
    SdXML3DSceneAttributesHelper maSceneImportHelper;
    ::com::sun::star::awt::Size maSize;
    ::com::sun::star::awt::Point maPosition;
    ::rtl::OUString msAutoStyleName;
    ::rtl::OUString& mrChartAddress;
    ::rtl::OUString& mrTableNumberList;

public:
    SchXMLPlotAreaContext( SchXMLImportHelper& rImpHelper,
                           SvXMLImport& rImport, const ::rtl::OUString& rLocalName,
                           ::com::sun::star::uno::Sequence<
                               ::com::sun::star::chart::ChartSeriesAddress >& rSeriesAddresses,
                           ::rtl::OUString& rCategoriesAddress,
                           ::rtl::OUString& rChartAddress,
                           ::rtl::OUString& rTableNumberList );
    virtual ~SchXMLPlotAreaContext();

    virtual void StartElement( const ::com::sun::star::uno::Reference< ::com::sun::star::xml::sax::XAttributeList >& xAttrList );
    virtual SvXMLImportContext* CreateChildContext(
        USHORT nPrefix,
        const ::rtl::OUString& rLocalName,
        const ::com::sun::star::uno::Reference< ::com::sun::star::xml::sax::XAttributeList >& xAttrList );
    virtual void EndElement();
};

// ----------------------------------------

class SchXMLAxisContext : public SvXMLImportContext
{
private:
    SchXMLImportHelper& mrImportHelper;
    ::com::sun::star::uno::Reference< ::com::sun::star::chart::XDiagram > mxDiagram;
    SchXMLAxis maCurrentAxis;
    std::vector< SchXMLAxis >& maAxes;
    ::rtl::OUString msAutoStyleName;

    ::com::sun::star::uno::Reference< ::com::sun::star::drawing::XShape > getTitleShape();
    void CreateGrid( ::rtl::OUString sAutoStyleName, sal_Bool bIsMajor );

public:
    SchXMLAxisContext( SchXMLImportHelper& rImpHelper,
                       SvXMLImport& rImport, const ::rtl::OUString& rLocalName,
                       ::com::sun::star::uno::Reference< ::com::sun::star::chart::XDiagram > xDiagram,
                       ::std::vector< SchXMLAxis >& aAxes );
    virtual ~SchXMLAxisContext();

    virtual void StartElement( const ::com::sun::star::uno::Reference< ::com::sun::star::xml::sax::XAttributeList >& xAttrList );
    virtual void EndElement();
    virtual SvXMLImportContext* CreateChildContext(
        USHORT nPrefix,
        const ::rtl::OUString& rLocalName,
        const ::com::sun::star::uno::Reference< ::com::sun::star::xml::sax::XAttributeList >& xAttrList );
};

// ----------------------------------------

class SchXMLSeriesContext : public SvXMLImportContext
{
private:
    SchXMLImportHelper& mrImportHelper;
    ::com::sun::star::uno::Reference< ::com::sun::star::chart::XDiagram > mxDiagram;
    std::vector< SchXMLAxis >& mrAxes;
    ::com::sun::star::chart::ChartSeriesAddress& mrSeriesAddress;
    ::std::list< chartxml::DataRowPointStyle >& mrStyleList;
    sal_Int32 mnSeriesIndex;
    sal_Int32 mnDataPointIndex;
    sal_Int32& mrMaxSeriesLength;
    sal_Int32& mrDomainOffset;
    SchXMLAxis* mpAttachedAxis;
    sal_Int32 mnAttachedAxis;
    ::rtl::OUString msAutoStyleName;

public:
    SchXMLSeriesContext( SchXMLImportHelper& rImpHelper,
                         SvXMLImport& rImport, const ::rtl::OUString& rLocalName,
                         ::com::sun::star::uno::Reference< ::com::sun::star::chart::XDiagram >& xDiagram,
                         ::std::vector< SchXMLAxis >& rAxes,
                         ::com::sun::star::chart::ChartSeriesAddress& rSeriesAddress,
                         ::std::list< chartxml::DataRowPointStyle >& rStyleList,
                         sal_Int32 nSeriesIndex,
                         sal_Int32& rMaxSeriesLength,
                         sal_Int32& rDomainOffset );
    virtual ~SchXMLSeriesContext();

    virtual void StartElement( const ::com::sun::star::uno::Reference< ::com::sun::star::xml::sax::XAttributeList >& xAttrList );
    virtual SvXMLImportContext* CreateChildContext(
        USHORT nPrefix,
        const ::rtl::OUString& rLocalName,
        const ::com::sun::star::uno::Reference< ::com::sun::star::xml::sax::XAttributeList >& xAttrList );
    virtual void EndElement();
};

//----------------------------------------

class SchXMLDataPointContext : public SvXMLImportContext
{
private:
    SchXMLImportHelper& mrImportHelper;
    ::com::sun::star::uno::Reference< ::com::sun::star::chart::XDiagram > mxDiagram;
    ::std::list< chartxml::DataRowPointStyle >& mrStyleList;
    sal_Int32 mnSeries;
    sal_Int32& mrIndex;

public:
    SchXMLDataPointContext(  SchXMLImportHelper& rImpHelper,
                             SvXMLImport& rImport, const ::rtl::OUString& rLocalName,
                             ::com::sun::star::uno::Reference< ::com::sun::star::chart::XDiagram >& xDiagram,
                             ::std::list< chartxml::DataRowPointStyle >& rStyleList,
                             sal_Int32 nSeries, sal_Int32& rIndex );
    virtual ~SchXMLDataPointContext();

    virtual void StartElement( const ::com::sun::star::uno::Reference< ::com::sun::star::xml::sax::XAttributeList >& xAttrList );
};

// ----------------------------------------

class SchXMLCategoriesDomainContext : public SvXMLImportContext
{
private:
    SchXMLImportHelper& mrImportHelper;
    ::rtl::OUString& mrAddress;

public:
    SchXMLCategoriesDomainContext( SchXMLImportHelper& rImpHelper,
                                   SvXMLImport& rImport,
                                   sal_uInt16 nPrefix,
                                   const ::rtl::OUString& rLocalName,
                                   ::rtl::OUString& rAddress );
    virtual ~SchXMLCategoriesDomainContext();
    virtual void StartElement( const ::com::sun::star::uno::Reference< ::com::sun::star::xml::sax::XAttributeList >& xAttrList );
};

// ----------------------------------------

class SchXMLWallFloorContext : public SvXMLImportContext
{
public:
    enum ContextType
    {
        CONTEXT_TYPE_WALL,
        CONTEXT_TYPE_FLOOR
    };

private:
    SchXMLImportHelper& mrImportHelper;
    ::com::sun::star::uno::Reference< ::com::sun::star::chart::X3DDisplay > mxWallFloorSupplier;
    ContextType meContextType;

public:
    SchXMLWallFloorContext( SchXMLImportHelper& rImportHelper,
                            SvXMLImport& rImport,
                            sal_uInt16 nPrefix,
                            const ::rtl::OUString& rLocalName,
                            ::com::sun::star::uno::Reference< ::com::sun::star::chart::XDiagram >& xDiagram,							
                            ContextType eContextType );
    virtual ~SchXMLWallFloorContext();
    virtual void StartElement( const ::com::sun::star::uno::Reference< ::com::sun::star::xml::sax::XAttributeList >& xAttrList );
};

// ----------------------------------------

class SchXMLStockContext : public SvXMLImportContext
{
public:
    enum ContextType
    {
        CONTEXT_TYPE_GAIN,
        CONTEXT_TYPE_LOSS,
        CONTEXT_TYPE_RANGE
    };

private:
    SchXMLImportHelper& mrImportHelper;
    ::com::sun::star::uno::Reference< ::com::sun::star::chart::XStatisticDisplay > mxStockPropProvider;
    ContextType meContextType;

public:
    SchXMLStockContext( SchXMLImportHelper& rImportHelper,
                        SvXMLImport& rImport,
                        sal_uInt16 nPrefix,
                        const ::rtl::OUString& rLocalName,
                        ::com::sun::star::uno::Reference< ::com::sun::star::chart::XDiagram >& xDiagram,							
                        ContextType eContextType );
    virtual ~SchXMLStockContext();
    virtual void StartElement( const ::com::sun::star::uno::Reference< ::com::sun::star::xml::sax::XAttributeList >& xAttrList );
};

// ----------------------------------------

class SchXMLStatisticsObjectContext : public SvXMLImportContext
{
public:
    enum ContextType
    {
        CONTEXT_TYPE_MEAN_VALUE_LINE,
        CONTEXT_TYPE_REGRESSION_CURVE,
        CONTEXT_TYPE_ERROR_INDICATOR
    };

    SchXMLStatisticsObjectContext(
        SchXMLImportHelper& rImportHelper,
        SvXMLImport& rImport,
        sal_uInt16 nPrefix,
        const ::rtl::OUString& rLocalName,
        ::std::list< chartxml::DataRowPointStyle >& rStyleList,
        sal_Int32 nSeries,
        ContextType eContextType );

    virtual ~SchXMLStatisticsObjectContext();

    virtual void StartElement( const ::com::sun::star::uno::Reference< ::com::sun::star::xml::sax::XAttributeList >& xAttrList );

private:
    SchXMLImportHelper &                           mrImportHelper;
    ::std::list< chartxml::DataRowPointStyle > & mrStyleList;
    sal_Int32                                      mnSeriesIndex;
    ContextType                                    meContextType;
};

}//end of namespace binfilter
#endif	// _SCH_XMLPLOTAREACONTEXT_HXX_
