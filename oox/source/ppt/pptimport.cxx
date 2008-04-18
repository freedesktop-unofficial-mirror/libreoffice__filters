/*************************************************************************
 *
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER.
 * 
 * Copyright 2008 by Sun Microsystems, Inc.
 *
 * OpenOffice.org - a multi-platform office productivity suite
 *
 * $RCSfile: pptimport.cxx,v $
 * $Revision: 1.5 $
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

#include "oox/ppt/pptimport.hxx"
#include "oox/drawingml/chart/chartconverter.hxx"
#include "oox/dump/pptxdumper.hxx"

using ::rtl::OUString;
using namespace ::com::sun::star;
using namespace ::com::sun::star::uno;
using namespace ::com::sun::star::xml::sax;
using namespace oox::core;

namespace oox { namespace ppt {

OUString SAL_CALL PowerPointImport_getImplementationName() throw()
{
    return CREATE_OUSTRING( "com.sun.star.comp.Impress.oox.PowerPointImport" );
}

uno::Sequence< OUString > SAL_CALL PowerPointImport_getSupportedServiceNames() throw()
{
    const OUString aServiceName = CREATE_OUSTRING( "com.sun.star.comp.ooxpptx" );
    const Sequence< OUString > aSeq( &aServiceName, 1 );
    return aSeq;
}

uno::Reference< uno::XInterface > SAL_CALL PowerPointImport_createInstance(const uno::Reference< lang::XMultiServiceFactory > & rSMgr ) throw( uno::Exception )
{
    return (cppu::OWeakObject*)new PowerPointImport( rSMgr );
}

PowerPointImport::PowerPointImport( const uno::Reference< lang::XMultiServiceFactory > & rSMgr  )
    : XmlFilterBase( rSMgr )
    , mxChartConv( new ::oox::drawingml::chart::ChartConverter )
{
}

PowerPointImport::~PowerPointImport()
{
}

bool PowerPointImport::importDocument() throw()
{
    /*  to activate the PPTX dumper, define the environment variable
        OOO_PPTXDUMPER and insert the full path to the file
        file:///<path-to-oox-module>/source/dump/pptxdumperconfig.dat. */
    OOX_DUMP_FILE( ::oox::dump::pptx::Dumper );

    OUString aFragmentPath = getFragmentPathFromType( CREATE_OFFICEDOC_RELATIONSTYPE( "officeDocument" ) );
    return importFragment( new PresentationFragmentHandler( *this, aFragmentPath ) );
}

bool PowerPointImport::exportDocument() throw()
{
    return false;
}

sal_Int32 PowerPointImport::getSchemeClr( sal_Int32 nColorSchemeToken ) const
{
    sal_Int32 nColor = 0;
    if ( mpActualSlidePersist )
    {
        sal_Bool bColorMapped = sal_False;
        oox::drawingml::ClrMapPtr pClrMapPtr( mpActualSlidePersist->getClrMap() );
        if ( pClrMapPtr )
            bColorMapped = pClrMapPtr->getColorMap( nColorSchemeToken );

        if ( !bColorMapped )	// try masterpage mapping
        {
            SlidePersistPtr pMasterPersist = mpActualSlidePersist->getMasterPersist();
            if ( pMasterPersist )
            {
                pClrMapPtr = pMasterPersist->getClrMap();
                if ( pClrMapPtr )
                    bColorMapped = pClrMapPtr->getColorMap( nColorSchemeToken );
            }
        }
        oox::drawingml::ClrSchemePtr pClrSchemePtr( mpActualSlidePersist->getClrScheme() );
        if ( pClrSchemePtr )
            pClrSchemePtr->getColor( nColorSchemeToken, nColor );
        else
        {
            drawingml::ThemePtr pTheme = mpActualSlidePersist->getTheme();
            if( pTheme )
            {
                pTheme->getClrScheme()->getColor( nColorSchemeToken, nColor );
            }
            else
            {
                OSL_TRACE("OOX: PowerPointImport::mpThemePtr is NULL");
            }
        }
    }
    return nColor;
}

const oox::vml::DrawingPtr PowerPointImport::getDrawings()
{
    oox::vml::DrawingPtr xRet;
    if ( mpActualSlidePersist )
        xRet = mpActualSlidePersist->getDrawing();
    return xRet;
}

::oox::drawingml::chart::ChartConverter& PowerPointImport::getChartConverter()
{
    return *mxChartConv;
}

OUString PowerPointImport::implGetImplementationName() const
{
    return PowerPointImport_getImplementationName();
}

}}
