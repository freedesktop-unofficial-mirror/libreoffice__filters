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

#include "oox/xls/excelfilter.hxx"

#include <com/sun/star/sheet/XSpreadsheetDocument.hpp>
#include "oox/dump/biffdumper.hxx"
#include "oox/dump/xlsbdumper.hxx"
#include "oox/helper/binaryinputstream.hxx"
#include "oox/xls/biffdetector.hxx"
#include "oox/xls/biffinputstream.hxx"
#include "oox/xls/excelchartconverter.hxx"
#include "oox/xls/excelvbaproject.hxx"
#include "oox/xls/stylesbuffer.hxx"
#include "oox/xls/themebuffer.hxx"
#include "oox/xls/workbookfragment.hxx"

namespace oox {
namespace xls {

// ============================================================================

using namespace ::com::sun::star::lang;
using namespace ::com::sun::star::sheet;
using namespace ::com::sun::star::uno;
using namespace ::com::sun::star::xml::sax;
using namespace ::oox::core;

using ::rtl::OUString;
using ::oox::drawingml::table::TableStyleListPtr;

// ============================================================================

ExcelFilterBase::ExcelFilterBase() :
    mpData( 0 )
{
}

ExcelFilterBase::~ExcelFilterBase()
{
    OSL_ENSURE( !mpData, "ExcelFilterBase::~ExcelFilterBase - workbook data not cleared" );
}

void ExcelFilterBase::registerWorkbookData( WorkbookData& rData )
{
    mpData = &rData;
}

WorkbookData& ExcelFilterBase::getWorkbookData() const
{
    OSL_ENSURE( mpData, "ExcelFilterBase::getWorkbookData - missing workbook data" );
    return *mpData;
}

void ExcelFilterBase::unregisterWorkbookData()
{
    mpData = 0;
}

// ============================================================================

OUString SAL_CALL ExcelFilter_getImplementationName() throw()
{
    return CREATE_OUSTRING( "com.sun.star.comp.oox.ExcelFilter" );
}

Sequence< OUString > SAL_CALL ExcelFilter_getSupportedServiceNames() throw()
{
    OUString aServiceName = CREATE_OUSTRING( "com.sun.star.comp.oox.ExcelFilter" );
    Sequence< OUString > aSeq( &aServiceName, 1 );
    return aSeq;
}

Reference< XInterface > SAL_CALL ExcelFilter_createInstance(
        const Reference< XMultiServiceFactory >& rxGlobalFactory ) throw( Exception )
{
    return static_cast< ::cppu::OWeakObject* >( new ExcelFilter( rxGlobalFactory ) );
}

// ----------------------------------------------------------------------------

ExcelFilter::ExcelFilter( const Reference< XMultiServiceFactory >& rxGlobalFactory ) :
    XmlFilterBase( rxGlobalFactory )
{
}

ExcelFilter::~ExcelFilter()
{
}

bool ExcelFilter::importDocument() throw()
{
    /*  to activate the XLSX/XLSB dumper, define the environment variable
        OOO_XLSBDUMPER and insert the full path to the file
        file:///<path-to-oox-module>/source/dump/xlsbdumper.ini. */
    OOX_DUMP_FILE( ::oox::dump::xlsb::Dumper );

    bool bRet = false;
    OUString aWorkbookPath = getFragmentPathFromFirstType( CREATE_OFFICEDOC_RELATIONSTYPE( "officeDocument" ) );
    if( aWorkbookPath.getLength() > 0 )
    {
        WorkbookHelperRoot aHelper( *this );
        bRet = aHelper.isValid() && importFragment( new OoxWorkbookFragment( aHelper, aWorkbookPath ) );
    }
    return bRet;
}

bool ExcelFilter::exportDocument() throw()
{
    return false;
}

const ::oox::drawingml::Theme* ExcelFilter::getCurrentTheme() const
{
    return &WorkbookHelper( getWorkbookData() ).getTheme();
}

::oox::vml::Drawing* ExcelFilter::getVmlDrawing()
{
    return 0;
}

const TableStyleListPtr ExcelFilter::getTableStyles()
{
    return TableStyleListPtr();
}

::oox::drawingml::chart::ChartConverter& ExcelFilter::getChartConverter()
{
    return WorkbookHelper( getWorkbookData() ).getChartConverter();
}

GraphicHelper* ExcelFilter::implCreateGraphicHelper() const
{
    return new ExcelGraphicHelper( getWorkbookData() );
}

::oox::ole::VbaProject* ExcelFilter::implCreateVbaProject() const
{
    return new ExcelVbaProject( getGlobalFactory(), Reference< XSpreadsheetDocument >( getModel(), UNO_QUERY ) );
}

OUString ExcelFilter::implGetImplementationName() const
{
    return ExcelFilter_getImplementationName();
}

// ============================================================================

OUString SAL_CALL ExcelBiffFilter_getImplementationName() throw()
{
    return CREATE_OUSTRING( "com.sun.star.comp.oox.ExcelBiffFilter" );
}

Sequence< OUString > SAL_CALL ExcelBiffFilter_getSupportedServiceNames() throw()
{
    OUString aServiceName = CREATE_OUSTRING( "com.sun.star.comp.oox.ExcelBiffFilter" );
    Sequence< OUString > aSeq( &aServiceName, 1 );
    return aSeq;
}

Reference< XInterface > SAL_CALL ExcelBiffFilter_createInstance(
        const Reference< XMultiServiceFactory >& rxGlobalFactory ) throw( Exception )
{
    return static_cast< ::cppu::OWeakObject* >( new ExcelBiffFilter( rxGlobalFactory ) );
}

// ----------------------------------------------------------------------------

ExcelBiffFilter::ExcelBiffFilter( const Reference< XMultiServiceFactory >& rxGlobalFactory ) :
    BinaryFilterBase( rxGlobalFactory )
{
}

ExcelBiffFilter::~ExcelBiffFilter()
{
}

bool ExcelBiffFilter::importDocument() throw()
{
    /*  to activate the BIFF dumper, define the environment variable
        OOO_BIFFDUMPER and insert the full path to the file
        file:///<path-to-oox-module>/source/dump/biffdumper.ini. */
    OOX_DUMP_FILE( ::oox::dump::biff::Dumper );

    /*  The boolean argument "UseBiffFilter" passed through XInitialisation
        decides whether to use the BIFF file dumper implemented in this filter
        only (false or missing), or to import/export the document (true). */
    Any aUseBiffFilter = getArgument( CREATE_OUSTRING( "UseBiffFilter" ) );
    bool bUseBiffFilter = false;
    if( !(aUseBiffFilter >>= bUseBiffFilter) || !bUseBiffFilter )
        return true;

    bool bRet = false;

    // detect BIFF version and workbook stream name
    OUString aWorkbookName;
    BiffType eBiff = BiffDetector::detectStorageBiffVersion( aWorkbookName, getStorage() );
    OSL_ENSURE( eBiff != BIFF_UNKNOWN, "ExcelBiffFilter::ExcelBiffFilter - invalid file format" );
    if( eBiff != BIFF_UNKNOWN )
    {
        WorkbookHelperRoot aHelper( *this, eBiff );
        bRet = aHelper.isValid() && BiffWorkbookFragment( aHelper, aWorkbookName ).importFragment();
    }
    return bRet;
}

bool ExcelBiffFilter::exportDocument() throw()
{
    return false;
}

GraphicHelper* ExcelBiffFilter::implCreateGraphicHelper() const
{
    return new ExcelGraphicHelper( getWorkbookData() );
}

::oox::ole::VbaProject* ExcelBiffFilter::implCreateVbaProject() const
{
    return new ExcelVbaProject( getGlobalFactory(), Reference< XSpreadsheetDocument >( getModel(), UNO_QUERY ) );
}

OUString ExcelBiffFilter::implGetImplementationName() const
{
    return ExcelBiffFilter_getImplementationName();
}

// ============================================================================

} // namespace xls
} // namespace oox
