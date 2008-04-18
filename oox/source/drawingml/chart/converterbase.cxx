/*************************************************************************
 *
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER.
 * 
 * Copyright 2008 by Sun Microsystems, Inc.
 *
 * OpenOffice.org - a multi-platform office productivity suite
 *
 * $RCSfile: converterbase.cxx,v $
 *
 * $Revision: 1.2 $
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

#include "oox/drawingml/chart/converterbase.hxx"
#include <com/sun/star/lang/XMultiServiceFactory.hpp>
#include <com/sun/star/frame/XModel.hpp>
#include <comphelper/processfactory.hxx>

using ::rtl::OUString;
using ::com::sun::star::uno::Reference;
using ::com::sun::star::uno::XInterface;
using ::com::sun::star::uno::Exception;
using ::com::sun::star::uno::UNO_QUERY_THROW;
using ::com::sun::star::lang::XMultiServiceFactory;
using ::com::sun::star::frame::XModel;
using ::com::sun::star::chart2::XChartDocument;
using ::oox::core::FilterBase;

namespace oox {
namespace drawingml {
namespace chart {

// ============================================================================

struct ConverterData
{
    FilterBase&         mrFilter;
    ChartConverter&     mrConverter;
    Reference< XChartDocument > mxDoc;

    explicit            ConverterData(
                            FilterBase& rFilter,
                            ChartConverter& rChartConverter,
                            const Reference< XChartDocument >& rxChartDoc );
                        ~ConverterData();
};

// ----------------------------------------------------------------------------

ConverterData::ConverterData(
        FilterBase& rFilter,
        ChartConverter& rChartConverter,
        const Reference< XChartDocument >& rxChartDoc ) :
    mrFilter( rFilter ),
    mrConverter( rChartConverter ),
    mxDoc( rxChartDoc )
{
    OSL_ENSURE( mxDoc.is(), "ConverterData::ConverterData - missing chart document" );
    // lock the model to suppress internal updates during conversion
    try
    {
        Reference< XModel > xModel( mxDoc, UNO_QUERY_THROW );
        xModel->lockControllers();
    }
    catch( Exception& )
    {
    }
}

ConverterData::~ConverterData()
{
    // unlock the model
    try
    {
        Reference< XModel > xModel( mxDoc, UNO_QUERY_THROW );
        xModel->unlockControllers();
    }
    catch( Exception& )
    {
    }
}

// ============================================================================

ConverterRoot::ConverterRoot(
        FilterBase& rFilter,
        ChartConverter& rChartConverter,
        const Reference< XChartDocument >& rxChartDoc ) :
    mxData( new ConverterData( rFilter, rChartConverter, rxChartDoc ) )
{
}

ConverterRoot::~ConverterRoot()
{
}

Reference< XInterface > ConverterRoot::createInstance(
        const Reference< XMultiServiceFactory >& rxFactory, const OUString& rServiceName )
{
    Reference< XInterface > xInt;
    if( rxFactory.is() ) try
    {
        xInt = rxFactory->createInstance( rServiceName );
    }
    catch( Exception& )
    {
    }
    OSL_ENSURE( xInt.is(), "ConverterRoot::createInstance - cannot create instance" );
    return xInt;
}

Reference< XInterface > ConverterRoot::createInstance( const OUString& rServiceName )
{
    return createInstance( ::comphelper::getProcessServiceFactory(), rServiceName );
}

FilterBase& ConverterRoot::getFilter() const
{
    return mxData->mrFilter;
}

ChartConverter& ConverterRoot::getChartConverter() const
{
    return mxData->mrConverter;
}

Reference< XChartDocument > ConverterRoot::getChartDocument() const
{
    return mxData->mxDoc;
}

// ============================================================================

} // namespace chart
} // namespace drawingml
} // namespace oox

