/*************************************************************************
 *
 *  $RCSfile: ChXChartAxis.hxx,v $
 *
 *  $Revision: 1.1.1.1 $
 *
 *  last change: $Author: hjs $ $Date: 2003-10-01 12:23:25 $
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

#ifndef _CHXCHART_AXIS_HXX
#define _CHXCHART_AXIS_HXX

// header for SvNumberFormatsSupplierObj
#ifndef _NUMUNO_HXX
#include <svtools/numuno.hxx>
#endif

#ifndef _COM_SUN_STAR_UTIL_XNUMBERFORMATSSUPPLIER_HPP_
#include <com/sun/star/util/XNumberFormatsSupplier.hpp>
#endif

#include "ChXChartObject.hxx"

class ChXChartAxis :
    public com::sun::star::util::XNumberFormatsSupplier,
    public ChXChartObject
{
private:
    com::sun::star::uno::Reference<
        com::sun::star::util::XNumberFormatsSupplier >	rNumberFormatter;

    com::sun::star::uno::Sequence< com::sun::star::uno::Type > maTypeSequence;

public:
    ChXChartAxis( ChartModel* _Model, long _WhichId );
    virtual ~ChXChartAxis();

    virtual void InitNumberFormatter() throw( com::sun::star::uno::RuntimeException );

    static const com::sun::star::uno::Sequence< sal_Int8 > & getUnoTunnelId() throw();
    static ChXChartAxis* getImplementation( com::sun::star::uno::Reference< com::sun::star::uno::XInterface > ) throw();

    // XServiceInfo
    virtual ::rtl::OUString SAL_CALL getImplementationName() throw( com::sun::star::uno::RuntimeException );
    virtual com::sun::star::uno::Sequence< rtl::OUString > SAL_CALL getSupportedServiceNames() throw( com::sun::star::uno::RuntimeException );

    // XNumberFormatsSupplier
    virtual com::sun::star::uno::Reference< com::sun::star::beans::XPropertySet > SAL_CALL getNumberFormatSettings()
        throw( com::sun::star::uno::RuntimeException );
    virtual com::sun::star::uno::Reference< com::sun::star::util::XNumberFormats > SAL_CALL getNumberFormats()
        throw( com::sun::star::uno::RuntimeException );

    // XPropertySet
    virtual void SAL_CALL setPropertyValue( const ::rtl::OUString& aPropertyName,
                                            const com::sun::star::uno::Any& aValue )
        throw( com::sun::star::beans::UnknownPropertyException,
               com::sun::star::beans::PropertyVetoException,
               com::sun::star::lang::IllegalArgumentException,
               com::sun::star::lang::WrappedTargetException,
               com::sun::star::uno::RuntimeException );
    virtual com::sun::star::uno::Any SAL_CALL getPropertyValue( const ::rtl::OUString& PropertyName )
        throw( com::sun::star::beans::UnknownPropertyException,
               com::sun::star::lang::WrappedTargetException,
               com::sun::star::uno::RuntimeException );

    // XInterface
    virtual com::sun::star::uno::Any SAL_CALL queryInterface( const com::sun::star::uno::Type & rType )
        throw ( com::sun::star::uno::RuntimeException );
    virtual void SAL_CALL acquire() throw();
    virtual void SAL_CALL release() throw();

    // XTypeProvider
    virtual ::com::sun::star::uno::Sequence< ::com::sun::star::uno::Type > SAL_CALL getTypes()
        throw( ::com::sun::star::uno::RuntimeException );
    virtual ::com::sun::star::uno::Sequence< sal_Int8 > SAL_CALL getImplementationId()
        throw( ::com::sun::star::uno::RuntimeException );

    // XShapeDescriptor
    virtual ::rtl::OUString SAL_CALL getShapeType() throw( ::com::sun::star::uno::RuntimeException );

    // XUnoTunnel
    virtual sal_Int64 SAL_CALL getSomething( const com::sun::star::uno::Sequence< sal_Int8 >& aIdentifier )
        throw( com::sun::star::uno::RuntimeException );
        
    //	ChXChartObject::XMultiPropertySet
    virtual void SAL_CALL setPropertyValues	(
                const ::com::sun::star::uno::Sequence< ::rtl::OUString >& aPropertyNames,
                const ::com::sun::star::uno::Sequence< ::com::sun::star::uno::Any >& aValues ) 
        throw (	::com::sun::star::beans::PropertyVetoException,
                ::com::sun::star::lang::IllegalArgumentException,
                ::com::sun::star::lang::WrappedTargetException,
                ::com::sun::star::uno::RuntimeException);

protected:
    /**	@descr	Creates an item set with a which range specific to chart axes.
        @return	Returns a pointer to an item set.  The caller is responsible for deleting it.
    */				
    virtual	SfxItemSet * CreateItemSet	(void);
    
    /**	@descr	Handle the axis special cases and call the base class method for all other.
            See there for further documentation.
        @see	ChxChartObject::GetPropertyValue.
    */
    virtual	void	GetPropertyValue	(const SfxItemPropertyMap & rProperty,
                                        ::com::sun::star::uno::Any & rValue, 
                                        SfxItemSet & rAttributes);
};

#endif	// _CHXCHART_AXIS_HXX

