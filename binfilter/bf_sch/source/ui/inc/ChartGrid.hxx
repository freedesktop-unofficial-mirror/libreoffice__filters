/*************************************************************************
 *
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER.
 * 
 * Copyright 2008 by Sun Microsystems, Inc.
 *
 * OpenOffice.org - a multi-platform office productivity suite
 *
 * $RCSfile: ChartGrid.hxx,v $
 * $Revision: 1.4 $
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
#ifndef _CHARTGRID_HXX_
#define _CHARTGRID_HXX_

#include "ChXChartObject.hxx"
namespace binfilter {

class ChartGrid : public ChXChartObject
{
public:
    ChartGrid( ChartModel* pModel, sal_Int32 nObjectId );
    virtual ~ChartGrid();

    // helpers for XUnoTunnel
    static const ::com::sun::star::uno::Sequence< sal_Int8 > & getUnoTunnelId() throw();
    static ChartGrid* getImplementation( ::com::sun::star::uno::Reference< ::com::sun::star::uno::XInterface > ) throw();

    // XServiceInfo
    virtual ::rtl::OUString SAL_CALL getImplementationName()
        throw( ::com::sun::star::uno::RuntimeException );
    virtual ::com::sun::star::uno::Sequence< ::rtl::OUString > SAL_CALL getSupportedServiceNames()
        throw( ::com::sun::star::uno::RuntimeException );

    // XTypeProvider
    virtual ::com::sun::star::uno::Sequence< sal_Int8 > SAL_CALL getImplementationId()
        throw( ::com::sun::star::uno::RuntimeException );

    // XShapeDescriptor
    virtual ::rtl::OUString SAL_CALL getShapeType() throw( ::com::sun::star::uno::RuntimeException );

    // XUnoTunnel
    virtual sal_Int64 SAL_CALL getSomething( const ::com::sun::star::uno::Sequence< sal_Int8 >& aIdentifier )
        throw( ::com::sun::star::uno::RuntimeException );

};

} //namespace binfilter
#endif	// _CHARTGRID_HXX_
