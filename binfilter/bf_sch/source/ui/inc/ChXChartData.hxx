/*************************************************************************
 *
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER.
 * 
 * Copyright 2008 by Sun Microsystems, Inc.
 *
 * OpenOffice.org - a multi-platform office productivity suite
 *
 * $RCSfile: ChXChartData.hxx,v $
 * $Revision: 1.6 $
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

#ifndef _CHART_DATA_HXX
#define _CHART_DATA_HXX

#ifndef _CPPUHELPER_IMPLBASE4_HXX_
#include <cppuhelper/implbase4.hxx>
#endif
// header for OInterfaceContainerHelper
#ifndef _CPPUHELPER_INTERFACECONTAINER_H_
#include <cppuhelper/interfacecontainer.hxx>
#endif

#ifndef _COM_SUN_STAR_CHART_XCHARTDATAARRAY_HPP_
#include <com/sun/star/chart/XChartDataArray.hpp>
#endif
#ifndef _COM_SUN_STAR_CHART_XSERVICEINFO_HPP_
#include <com/sun/star/lang/XServiceInfo.hpp>
#endif
#ifndef _COM_SUN_STAR_UNO_XUNOTUNNEL_HPP_
#include <com/sun/star/lang/XUnoTunnel.hpp>
#endif
#ifndef _COM_SUN_STAR_LANG_XCOMPONENT_HPP_
#include <com/sun/star/lang/XComponent.hpp>
#endif
namespace binfilter {

class ChartModel;

// ----------------------------------------
// ChXChartData
// ----------------------------------------

class ChXChartData : public cppu::WeakImplHelper4<
    ::com::sun::star::chart::XChartData,
    ::com::sun::star::lang::XServiceInfo,
    ::com::sun::star::lang::XEventListener,
    ::com::sun::star::lang::XUnoTunnel >
{
private:
    ::osl::Mutex maMutex;
    cppu::OInterfaceContainerHelper maListeners;

protected:
    ChartModel* mpModel;

public:
    // the model is used for listening for the 'death' of the ChartModel
    ChXChartData( ::com::sun::star::uno::Reference< ::com::sun::star::lang::XComponent > xModel,
                  ChartModel* pModel );
    virtual ~ChXChartData();

    ::osl::Mutex& GetMutex()	{ return maMutex; }

    virtual void DataModified( ::com::sun::star::chart::ChartDataChangeEvent& );

    static const ::com::sun::star::uno::Sequence< sal_Int8 > & getUnoTunnelId() throw();
    static ChXChartData* getImplementation( ::com::sun::star::uno::Reference< ::com::sun::star::uno::XInterface > ) throw();

    // XChartData
    virtual void SAL_CALL addChartDataChangeEventListener(
        const ::com::sun::star::uno::Reference< ::com::sun::star::chart::XChartDataChangeEventListener >& aListener )
        throw( ::com::sun::star::uno::RuntimeException );
    virtual void SAL_CALL removeChartDataChangeEventListener(
        const ::com::sun::star::uno::Reference< ::com::sun::star::chart::XChartDataChangeEventListener >& aListener )
        throw( ::com::sun::star::uno::RuntimeException );
    virtual double SAL_CALL getNotANumber() throw( ::com::sun::star::uno::RuntimeException );
    virtual sal_Bool SAL_CALL isNotANumber( double nNumber ) throw( ::com::sun::star::uno::RuntimeException );

    // XServiceInfo
    virtual ::rtl::OUString SAL_CALL getImplementationName()
        throw( ::com::sun::star::uno::RuntimeException );
    virtual sal_Bool SAL_CALL supportsService( const ::rtl::OUString& ServiceName )
        throw( ::com::sun::star::uno::RuntimeException );
    virtual ::com::sun::star::uno::Sequence< ::rtl::OUString > SAL_CALL getSupportedServiceNames()
        throw( ::com::sun::star::uno::RuntimeException );

    // XUnoTunnel
    virtual sal_Int64 SAL_CALL getSomething( const ::com::sun::star::uno::Sequence< sal_Int8 >& aIdentifier )
        throw( ::com::sun::star::uno::RuntimeException );

    // XEventListener listens to disposing of XModel
    virtual void SAL_CALL disposing( const ::com::sun::star::lang::EventObject& Source )
        throw( ::com::sun::star::uno::RuntimeException );
};


// ----------------------------------------
// ChXChartDataArray
// ----------------------------------------

class ChXChartDataArray :
    public ChXChartData,
    public ::com::sun::star::chart::XChartDataArray
{
private:
    static ::com::sun::star::uno::Sequence< ::com::sun::star::uno::Type > maTypeSequence;

public:
    // the model is used for listening for the 'death' of the ChartModel
    ChXChartDataArray( ::com::sun::star::uno::Reference< ::com::sun::star::lang::XComponent > xModel,
                       ChartModel* pModel );
    virtual ~ChXChartDataArray();

    // XInterface
    virtual ::com::sun::star::uno::Any SAL_CALL queryInterface( const ::com::sun::star::uno::Type& aType )
        throw( ::com::sun::star::uno::RuntimeException );
    virtual void SAL_CALL acquire() throw();
    virtual void SAL_CALL release() throw();

    // XTypeProvider
    virtual ::com::sun::star::uno::Sequence< ::com::sun::star::uno::Type > SAL_CALL getTypes()
        throw( ::com::sun::star::uno::RuntimeException );
    virtual ::com::sun::star::uno::Sequence< sal_Int8 > SAL_CALL getImplementationId()
        throw( ::com::sun::star::uno::RuntimeException );

    // XChartDataArray
    virtual ::com::sun::star::uno::Sequence< ::com::sun::star::uno::Sequence< double > > SAL_CALL getData()
        throw( ::com::sun::star::uno::RuntimeException );
    virtual void SAL_CALL setData( const ::com::sun::star::uno::Sequence< ::com::sun::star::uno::Sequence< double > >& aData )
        throw( ::com::sun::star::uno::RuntimeException );
    virtual ::com::sun::star::uno::Sequence< ::rtl::OUString > SAL_CALL getRowDescriptions()
        throw( ::com::sun::star::uno::RuntimeException );
    virtual void SAL_CALL setRowDescriptions( const ::com::sun::star::uno::Sequence< ::rtl::OUString >& aRowDescriptions )
        throw( ::com::sun::star::uno::RuntimeException );
    virtual ::com::sun::star::uno::Sequence< ::rtl::OUString > SAL_CALL getColumnDescriptions()
        throw( ::com::sun::star::uno::RuntimeException );
    virtual void SAL_CALL setColumnDescriptions( const ::com::sun::star::uno::Sequence< ::rtl::OUString >& aColumnDescriptions )
        throw( ::com::sun::star::uno::RuntimeException );

    // XChartData ( ::XChartDataArray )
    virtual void SAL_CALL addChartDataChangeEventListener(
        const ::com::sun::star::uno::Reference< ::com::sun::star::chart::XChartDataChangeEventListener >& aListener )
        throw( ::com::sun::star::uno::RuntimeException );
    virtual void SAL_CALL removeChartDataChangeEventListener(
        const ::com::sun::star::uno::Reference< ::com::sun::star::chart::XChartDataChangeEventListener >& aListener )
        throw( ::com::sun::star::uno::RuntimeException );
    virtual double SAL_CALL getNotANumber() throw( ::com::sun::star::uno::RuntimeException );
    virtual sal_Bool SAL_CALL isNotANumber( double nNumber ) throw( ::com::sun::star::uno::RuntimeException );

    // XServiceInfo
    virtual ::rtl::OUString SAL_CALL getImplementationName()
        throw( ::com::sun::star::uno::RuntimeException );
    virtual sal_Bool SAL_CALL supportsService( const ::rtl::OUString& ServiceName )
        throw( ::com::sun::star::uno::RuntimeException );
    virtual ::com::sun::star::uno::Sequence< ::rtl::OUString > SAL_CALL getSupportedServiceNames()
        throw( ::com::sun::star::uno::RuntimeException );
};

} //namespace binfilter
#endif	// _CHART_DATA_HXX

