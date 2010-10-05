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

#ifndef _NUMFMUNO_HXX
#define _NUMFMUNO_HXX

#include <com/sun/star/util/XNumberFormatter.hpp>
#include <com/sun/star/util/XNumberFormatPreviewer.hpp>
#include <com/sun/star/util/XNumberFormats.hpp>
#include <com/sun/star/util/XNumberFormatTypes.hpp>
#include <com/sun/star/lang/XServiceInfo.hpp>
#include <com/sun/star/beans/XPropertyAccess.hpp>

#include <cppuhelper/implbase2.hxx>
#include <cppuhelper/implbase3.hxx>

namespace binfilter
{

class SvNumberformat;
class SvNumberFormatter;
class SvNumberFormatsSupplierObj;


//	SvNumberFormatterServiceObj wird global als Service angemeldet

class SvNumberFormatterServiceObj : public cppu::WeakImplHelper3<
                                        com::sun::star::util::XNumberFormatter,
                                        com::sun::star::util::XNumberFormatPreviewer,
                                        com::sun::star::lang::XServiceInfo>
{
private:
    SvNumberFormatsSupplierObj*	pSupplier;

public:
                        SvNumberFormatterServiceObj();
    virtual				~SvNumberFormatterServiceObj();

                        // XNumberFormatter
    virtual void SAL_CALL attachNumberFormatsSupplier(
                            const ::com::sun::star::uno::Reference<
                                ::com::sun::star::util::XNumberFormatsSupplier >& xSupplier )
                                    throw(::com::sun::star::uno::RuntimeException);
    virtual ::com::sun::star::uno::Reference< ::com::sun::star::util::XNumberFormatsSupplier >
                            SAL_CALL getNumberFormatsSupplier()
                                throw(::com::sun::star::uno::RuntimeException);
    virtual sal_Int32 SAL_CALL detectNumberFormat( sal_Int32 nKey, const ::rtl::OUString& aString )
                            throw(::com::sun::star::util::NotNumericException,
                                    ::com::sun::star::uno::RuntimeException);
    virtual double SAL_CALL convertStringToNumber( sal_Int32 nKey, const ::rtl::OUString& aString )
                            throw(::com::sun::star::util::NotNumericException,
                                    ::com::sun::star::uno::RuntimeException);
    virtual ::rtl::OUString SAL_CALL convertNumberToString( sal_Int32 nKey, double fValue )
                            throw(::com::sun::star::uno::RuntimeException);
    virtual ::com::sun::star::util::Color SAL_CALL queryColorForNumber( sal_Int32 nKey,
                            double fValue, ::com::sun::star::util::Color aDefaultColor )
                                throw(::com::sun::star::uno::RuntimeException);
    virtual ::rtl::OUString SAL_CALL formatString( sal_Int32 nKey, const ::rtl::OUString& aString )
                            throw(::com::sun::star::uno::RuntimeException);
    virtual ::com::sun::star::util::Color SAL_CALL queryColorForString( sal_Int32 nKey,
                            const ::rtl::OUString& aString,
                                ::com::sun::star::util::Color aDefaultColor )
                                    throw(::com::sun::star::uno::RuntimeException);
    virtual ::rtl::OUString SAL_CALL getInputString( sal_Int32 nKey, double fValue )
                            throw(::com::sun::star::uno::RuntimeException);

                        // XNumberFormatPreviewer
    virtual ::rtl::OUString SAL_CALL convertNumberToPreviewString(
                            const ::rtl::OUString& aFormat, double fValue,
                            const ::com::sun::star::lang::Locale& nLocale, sal_Bool bAllowEnglish )
                                throw(::com::sun::star::util::MalformedNumberFormatException,
                                        ::com::sun::star::uno::RuntimeException);
    virtual ::com::sun::star::util::Color SAL_CALL queryPreviewColorForNumber(
                            const ::rtl::OUString& aFormat, double fValue,
                            const ::com::sun::star::lang::Locale& nLocale, sal_Bool bAllowEnglish,
                            ::com::sun::star::util::Color aDefaultColor )
                                throw(::com::sun::star::util::MalformedNumberFormatException,
                                        ::com::sun::star::uno::RuntimeException);

                        // XServiceInfo
    virtual ::rtl::OUString SAL_CALL getImplementationName(  )
                            throw(::com::sun::star::uno::RuntimeException);
    virtual sal_Bool SAL_CALL supportsService( const ::rtl::OUString& ServiceName )
                            throw(::com::sun::star::uno::RuntimeException);
    virtual ::com::sun::star::uno::Sequence< ::rtl::OUString > SAL_CALL getSupportedServiceNames()
                            throw(::com::sun::star::uno::RuntimeException);
};


class SvNumberFormatsObj : public cppu::WeakImplHelper3<
                                        com::sun::star::util::XNumberFormats,
                                        com::sun::star::util::XNumberFormatTypes,
                                        com::sun::star::lang::XServiceInfo>
{
private:
    SvNumberFormatsSupplierObj*	pSupplier;

public:
                    SvNumberFormatsObj();
                    SvNumberFormatsObj(SvNumberFormatsSupplierObj* pParent);
    virtual			~SvNumberFormatsObj();


                        // XNumberFormats
    virtual ::com::sun::star::uno::Reference< ::com::sun::star::beans::XPropertySet > SAL_CALL
                            getByKey( sal_Int32 nKey ) throw(::com::sun::star::uno::RuntimeException);
    virtual ::com::sun::star::uno::Sequence< sal_Int32 > SAL_CALL queryKeys( sal_Int16 nType,
                            const ::com::sun::star::lang::Locale& nLocale, sal_Bool bCreate )
                                throw(::com::sun::star::uno::RuntimeException);
    virtual sal_Int32 SAL_CALL queryKey( const ::rtl::OUString& aFormat,
                            const ::com::sun::star::lang::Locale& nLocale, sal_Bool bScan )
                                throw(::com::sun::star::uno::RuntimeException);
    virtual sal_Int32 SAL_CALL addNew( const ::rtl::OUString& aFormat,
                            const ::com::sun::star::lang::Locale& nLocale )
                                throw(::com::sun::star::util::MalformedNumberFormatException,
                                        ::com::sun::star::uno::RuntimeException);
    virtual sal_Int32 SAL_CALL addNewConverted( const ::rtl::OUString& aFormat,
                            const ::com::sun::star::lang::Locale& nLocale,
                            const ::com::sun::star::lang::Locale& nNewLocale )
                                throw(::com::sun::star::util::MalformedNumberFormatException,
                                        ::com::sun::star::uno::RuntimeException);
    virtual void SAL_CALL removeByKey( sal_Int32 nKey ) throw(::com::sun::star::uno::RuntimeException);
    virtual ::rtl::OUString SAL_CALL generateFormat( sal_Int32 nBaseKey,
                            const ::com::sun::star::lang::Locale& nLocale, sal_Bool bThousands,
                            sal_Bool bRed, sal_Int16 nDecimals, sal_Int16 nLeading )
                                throw(::com::sun::star::uno::RuntimeException);

                        // XNumberFormatTypes
    virtual sal_Int32 SAL_CALL getStandardIndex( const ::com::sun::star::lang::Locale& nLocale )
                            throw(::com::sun::star::uno::RuntimeException);
    virtual sal_Int32 SAL_CALL getStandardFormat( sal_Int16 nType,
                            const ::com::sun::star::lang::Locale& nLocale )
                                throw(::com::sun::star::uno::RuntimeException);
    virtual sal_Int32 SAL_CALL getFormatIndex( sal_Int16 nIndex,
                            const ::com::sun::star::lang::Locale& nLocale )
                                throw(::com::sun::star::uno::RuntimeException);
    virtual sal_Bool SAL_CALL isTypeCompatible( sal_Int16 nOldType, sal_Int16 nNewType )
                            throw(::com::sun::star::uno::RuntimeException);
    virtual sal_Int32 SAL_CALL getFormatForLocale( sal_Int32 nKey,
                            const ::com::sun::star::lang::Locale& nLocale )
                                throw(::com::sun::star::uno::RuntimeException);

                        // XServiceInfo
    virtual ::rtl::OUString SAL_CALL getImplementationName(  )
                            throw(::com::sun::star::uno::RuntimeException);
    virtual sal_Bool SAL_CALL supportsService( const ::rtl::OUString& ServiceName )
                            throw(::com::sun::star::uno::RuntimeException);
    virtual ::com::sun::star::uno::Sequence< ::rtl::OUString > SAL_CALL getSupportedServiceNames()
                            throw(::com::sun::star::uno::RuntimeException);
};


class SvNumberFormatObj : public cppu::WeakImplHelper3<
                                        com::sun::star::beans::XPropertySet,
                                        com::sun::star::beans::XPropertyAccess,
                                        com::sun::star::lang::XServiceInfo>
{
private:
    SvNumberFormatsSupplierObj*	pSupplier;
    ULONG						nKey;

public:
                    SvNumberFormatObj(SvNumberFormatsSupplierObj* pParent, ULONG nK);
    virtual			~SvNumberFormatObj();

                            // XPropertySet
    virtual ::com::sun::star::uno::Reference< ::com::sun::star::beans::XPropertySetInfo >
                            SAL_CALL getPropertySetInfo(  )
                                throw(::com::sun::star::uno::RuntimeException);
    virtual void SAL_CALL	setPropertyValue( const ::rtl::OUString& aPropertyName,
                                    const ::com::sun::star::uno::Any& aValue )
                                throw(::com::sun::star::beans::UnknownPropertyException,
                                    ::com::sun::star::beans::PropertyVetoException,
                                    ::com::sun::star::lang::IllegalArgumentException,
                                    ::com::sun::star::lang::WrappedTargetException,
                                    ::com::sun::star::uno::RuntimeException);
    virtual ::com::sun::star::uno::Any SAL_CALL getPropertyValue(
                                    const ::rtl::OUString& PropertyName )
                                throw(::com::sun::star::beans::UnknownPropertyException,
                                    ::com::sun::star::lang::WrappedTargetException,
                                    ::com::sun::star::uno::RuntimeException);
    virtual void SAL_CALL	addPropertyChangeListener( const ::rtl::OUString& aPropertyName,
                                    const ::com::sun::star::uno::Reference<
                                        ::com::sun::star::beans::XPropertyChangeListener >& xListener )
                                throw(::com::sun::star::beans::UnknownPropertyException,
                                    ::com::sun::star::lang::WrappedTargetException,
                                    ::com::sun::star::uno::RuntimeException);
    virtual void SAL_CALL	removePropertyChangeListener( const ::rtl::OUString& aPropertyName,
                                    const ::com::sun::star::uno::Reference<
                                        ::com::sun::star::beans::XPropertyChangeListener >& aListener )
                                throw(::com::sun::star::beans::UnknownPropertyException,
                                    ::com::sun::star::lang::WrappedTargetException,
                                    ::com::sun::star::uno::RuntimeException);
    virtual void SAL_CALL	addVetoableChangeListener( const ::rtl::OUString& PropertyName,
                                    const ::com::sun::star::uno::Reference<
                                        ::com::sun::star::beans::XVetoableChangeListener >& aListener )
                                throw(::com::sun::star::beans::UnknownPropertyException,
                                    ::com::sun::star::lang::WrappedTargetException,
                                    ::com::sun::star::uno::RuntimeException);
    virtual void SAL_CALL	removeVetoableChangeListener( const ::rtl::OUString& PropertyName,
                                    const ::com::sun::star::uno::Reference<
                                        ::com::sun::star::beans::XVetoableChangeListener >& aListener )
                                throw(::com::sun::star::beans::UnknownPropertyException,
                                    ::com::sun::star::lang::WrappedTargetException,
                                    ::com::sun::star::uno::RuntimeException);

                            // XPropertyAccess
    virtual ::com::sun::star::uno::Sequence< ::com::sun::star::beans::PropertyValue > SAL_CALL
                            getPropertyValues() throw(::com::sun::star::uno::RuntimeException);
    virtual void SAL_CALL	setPropertyValues( const ::com::sun::star::uno::Sequence<
                                ::com::sun::star::beans::PropertyValue >& aProps )
                                    throw(::com::sun::star::beans::UnknownPropertyException,
                                            ::com::sun::star::beans::PropertyVetoException,
                                            ::com::sun::star::lang::IllegalArgumentException,
                                            ::com::sun::star::lang::WrappedTargetException,
                                            ::com::sun::star::uno::RuntimeException);

                            // XServiceInfo
    virtual ::rtl::OUString SAL_CALL getImplementationName(  )
                                throw(::com::sun::star::uno::RuntimeException);
    virtual sal_Bool SAL_CALL supportsService( const ::rtl::OUString& ServiceName )
                                throw(::com::sun::star::uno::RuntimeException);
    virtual ::com::sun::star::uno::Sequence< ::rtl::OUString > SAL_CALL getSupportedServiceNames()
                                throw(::com::sun::star::uno::RuntimeException);
};


class SvNumberFormatSettingsObj : public cppu::WeakImplHelper2<
                                        com::sun::star::beans::XPropertySet,
                                        com::sun::star::lang::XServiceInfo>
{
private:
    SvNumberFormatsSupplierObj*	pSupplier;

public:
                    SvNumberFormatSettingsObj(SvNumberFormatsSupplierObj* pParent);
    virtual			~SvNumberFormatSettingsObj();


                            // XPropertySet
    virtual ::com::sun::star::uno::Reference< ::com::sun::star::beans::XPropertySetInfo >
                            SAL_CALL getPropertySetInfo(  )
                                throw(::com::sun::star::uno::RuntimeException);
    virtual void SAL_CALL	setPropertyValue( const ::rtl::OUString& aPropertyName,
                                    const ::com::sun::star::uno::Any& aValue )
                                throw(::com::sun::star::beans::UnknownPropertyException,
                                    ::com::sun::star::beans::PropertyVetoException,
                                    ::com::sun::star::lang::IllegalArgumentException,
                                    ::com::sun::star::lang::WrappedTargetException,
                                    ::com::sun::star::uno::RuntimeException);
    virtual ::com::sun::star::uno::Any SAL_CALL getPropertyValue(
                                    const ::rtl::OUString& PropertyName )
                                throw(::com::sun::star::beans::UnknownPropertyException,
                                    ::com::sun::star::lang::WrappedTargetException,
                                    ::com::sun::star::uno::RuntimeException);
    virtual void SAL_CALL	addPropertyChangeListener( const ::rtl::OUString& aPropertyName,
                                    const ::com::sun::star::uno::Reference<
                                        ::com::sun::star::beans::XPropertyChangeListener >& xListener )
                                throw(::com::sun::star::beans::UnknownPropertyException,
                                    ::com::sun::star::lang::WrappedTargetException,
                                    ::com::sun::star::uno::RuntimeException);
    virtual void SAL_CALL	removePropertyChangeListener( const ::rtl::OUString& aPropertyName,
                                    const ::com::sun::star::uno::Reference<
                                        ::com::sun::star::beans::XPropertyChangeListener >& aListener )
                                throw(::com::sun::star::beans::UnknownPropertyException,
                                    ::com::sun::star::lang::WrappedTargetException,
                                    ::com::sun::star::uno::RuntimeException);
    virtual void SAL_CALL	addVetoableChangeListener( const ::rtl::OUString& PropertyName,
                                    const ::com::sun::star::uno::Reference<
                                        ::com::sun::star::beans::XVetoableChangeListener >& aListener )
                                throw(::com::sun::star::beans::UnknownPropertyException,
                                    ::com::sun::star::lang::WrappedTargetException,
                                    ::com::sun::star::uno::RuntimeException);
    virtual void SAL_CALL	removeVetoableChangeListener( const ::rtl::OUString& PropertyName,
                                    const ::com::sun::star::uno::Reference<
                                        ::com::sun::star::beans::XVetoableChangeListener >& aListener )
                                throw(::com::sun::star::beans::UnknownPropertyException,
                                    ::com::sun::star::lang::WrappedTargetException,
                                    ::com::sun::star::uno::RuntimeException);

                            // XServiceInfo
    virtual ::rtl::OUString SAL_CALL getImplementationName(  )
                                throw(::com::sun::star::uno::RuntimeException);
    virtual sal_Bool SAL_CALL supportsService( const ::rtl::OUString& ServiceName )
                                throw(::com::sun::star::uno::RuntimeException);
    virtual ::com::sun::star::uno::Sequence< ::rtl::OUString > SAL_CALL getSupportedServiceNames()
                                throw(::com::sun::star::uno::RuntimeException);
};


}

#endif

