/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: sch_ChartArea.cxx,v $
 *
 *  $Revision: 1.4 $
 *
 *  last change: $Author: rt $ $Date: 2005-09-07 23:12:34 $
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
#include "ChartArea.hxx"

#include "mapprov.hxx"
// auto strip #include "defines.hxx"

// header for class OGuard
#ifndef _VOS_MUTEX_HXX_
#include <vos/mutex.hxx>
#endif
// header for class Application
#ifndef _SV_SVAPP_HXX
#include <vcl/svapp.hxx>
#endif
#ifndef _RTL_UUID_H_
#include <rtl/uuid.h>
#endif
// auto strip #ifndef _CPPUHELPER_QUERYINTERFACE_HXX_
// auto strip #include <cppuhelper/queryinterface.hxx>
// auto strip #endif
namespace binfilter {

using namespace ::com::sun::star;

ChartArea::ChartArea( ChartModel* pModel, sal_Int32 nObjectId ) :
        ChXChartObject( CHMAP_AREA, pModel, nObjectId )
{
}

ChartArea::~ChartArea()
{}

// XServiceInfo
::rtl::OUString SAL_CALL ChartArea::getImplementationName()
    throw( uno::RuntimeException )
{
    return ::rtl::OUString::createFromAscii( "ChartArea" );
}

uno::Sequence< ::rtl::OUString > SAL_CALL ChartArea::getSupportedServiceNames()
    throw( uno::RuntimeException )
{
    ::vos::OGuard aGuard( Application::GetSolarMutex() );

    uno::Sequence< ::rtl::OUString > aSeq( 4 );
    aSeq[ 0 ] = ::rtl::OUString::createFromAscii( "com.sun.star.chart.ChartArea" );
    aSeq[ 1 ] = ::rtl::OUString::createFromAscii( "com.sun.star.drawing.LineProperties" );
    aSeq[ 2 ] = ::rtl::OUString::createFromAscii( "com.sun.star.drawing.FillProperties" );
    aSeq[ 3 ] = ::rtl::OUString::createFromAscii( "com.sun.star.xml.UserDefinedAttributeSupplier" );

    return aSeq;
}

// XTypeProvider
uno::Sequence< sal_Int8 > SAL_CALL ChartArea::getImplementationId()
    throw( uno::RuntimeException )
{
    static uno::Sequence< sal_Int8 > aId;
    if( aId.getLength() == 0 )
    {
        aId.realloc( 16 );
        rtl_createUuid( (sal_uInt8 *)aId.getArray(), 0, sal_True );
    }
    return aId;
}

// XShapeDescriptor
::rtl::OUString SAL_CALL ChartArea::getShapeType()
    throw( uno::RuntimeException )
{
    return ::rtl::OUString::createFromAscii( "com.sun.star.chart.ChartArea" );
}

// XUnoTunnel
sal_Int64 SAL_CALL ChartArea::getSomething( const uno::Sequence< sal_Int8 >& aIdentifier )
    throw( uno::RuntimeException )
{
    if( aIdentifier.getLength() == 16 && 0 == rtl_compareMemory( getUnoTunnelId().getConstArray(),
                                                                 aIdentifier.getConstArray(), 16 ) )
    {
        return (sal_Int64)this;
    }
    return ChXChartObject::getSomething( aIdentifier );
}

// helpers for XUnoTunnel 
const uno::Sequence< sal_Int8 > & ChartArea::getUnoTunnelId() throw()
{
    static uno::Sequence< sal_Int8 > * pSeq = 0;
    if( !pSeq )
    {
        osl::Guard< osl::Mutex > aGuard( osl::Mutex::getGlobalMutex() );
        if( !pSeq )
        {
            static uno::Sequence< sal_Int8 > aSeq( 16 );
            rtl_createUuid( (sal_uInt8*)aSeq.getArray(), 0, sal_True );
            pSeq = &aSeq;
        }
    }
    return *pSeq;
}

ChartArea* ChartArea::getImplementation( uno::Reference< uno::XInterface > xData ) throw()
{
    uno::Reference< lang::XUnoTunnel > xUT( xData, uno::UNO_QUERY );
    if( xUT.is() )
        return (ChartArea*)xUT->getSomething( ChartArea::getUnoTunnelId() );
    else
        return NULL;
}
}
