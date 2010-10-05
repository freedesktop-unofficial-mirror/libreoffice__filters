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

#ifndef SC_FMTUNO_HXX
#define SC_FMTUNO_HXX

#include "global.hxx"			// ScRange, ScAddress


#include <bf_svtools/itemprop.hxx>

#include <com/sun/star/sheet/XSheetConditionalEntries.hpp>
#include <com/sun/star/sheet/XSheetCondition.hpp>
#include <com/sun/star/sheet/XSheetConditionalEntry.hpp>
#include <com/sun/star/lang/XServiceInfo.hpp>
#include <com/sun/star/container/XNameAccess.hpp>
#include <com/sun/star/container/XEnumerationAccess.hpp>
#include <com/sun/star/lang/XUnoTunnel.hpp>
#include <com/sun/star/beans/XPropertySet.hpp>

#include <cppuhelper/implbase3.hxx>
#include <cppuhelper/implbase4.hxx>
#include <cppuhelper/implbase5.hxx>
namespace binfilter {


class ScDocument;
class ScTableConditionalEntry;
class ScConditionalFormat;
class ScValidationData;


//	"erstmal" nur dummer Container

class ScTableConditionalFormat : public cppu::WeakImplHelper5<
                            ::com::sun::star::sheet::XSheetConditionalEntries,
                            ::com::sun::star::container::XNameAccess,
                            ::com::sun::star::container::XEnumerationAccess,
                            ::com::sun::star::lang::XUnoTunnel,
                            ::com::sun::star::lang::XServiceInfo >
{
private:
    List	aEntries;

    ScTableConditionalEntry*	GetObjectByIndex_Impl(USHORT nIndex) const;
    void						AddEntry_Impl( USHORT nMode,
                                    const String& rExpr1, const String& rExpr2,
                                    const ScAddress& rPos, const String& rStyle );

public:
                            ScTableConditionalFormat(ScDocument* pDoc, ULONG nKey,
                                                        BOOL bEnglish, BOOL bCompileXML);
    virtual					~ScTableConditionalFormat();

    void					FillFormat( ScConditionalFormat& rFormat,
                                            ScDocument* pDoc, BOOL bEnglish, BOOL bCompileXML ) const;
    void					DataChanged();

                            // XSheetConditionalEntries
    virtual void SAL_CALL	addNew( const ::com::sun::star::uno::Sequence<
                                    ::com::sun::star::beans::PropertyValue >& aConditionalEntry )
                                throw(::com::sun::star::uno::RuntimeException);
    virtual void SAL_CALL	removeByIndex( sal_Int32 nIndex )
                                throw(::com::sun::star::uno::RuntimeException);
    virtual void SAL_CALL	clear() throw(::com::sun::star::uno::RuntimeException);

                            // XIndexAccess
    virtual sal_Int32 SAL_CALL getCount() throw(::com::sun::star::uno::RuntimeException);
    virtual ::com::sun::star::uno::Any SAL_CALL getByIndex( sal_Int32 Index )
                                throw(::com::sun::star::lang::IndexOutOfBoundsException,
                                    ::com::sun::star::lang::WrappedTargetException,
                                    ::com::sun::star::uno::RuntimeException);

                            // XNameAccess
    virtual ::com::sun::star::uno::Any SAL_CALL getByName( const ::rtl::OUString& aName )
                                throw(::com::sun::star::container::NoSuchElementException,
                                    ::com::sun::star::lang::WrappedTargetException,
                                    ::com::sun::star::uno::RuntimeException);
    virtual ::com::sun::star::uno::Sequence< ::rtl::OUString > SAL_CALL getElementNames()
                                throw(::com::sun::star::uno::RuntimeException);
    virtual sal_Bool SAL_CALL hasByName( const ::rtl::OUString& aName )
                                throw(::com::sun::star::uno::RuntimeException);

                            // XEnumerationAccess
    virtual ::com::sun::star::uno::Reference< ::com::sun::star::container::XEnumeration > SAL_CALL
                            createEnumeration() throw(::com::sun::star::uno::RuntimeException);

                            // XElementAccess
    virtual ::com::sun::star::uno::Type SAL_CALL getElementType()
                                throw(::com::sun::star::uno::RuntimeException);
    virtual sal_Bool SAL_CALL hasElements() throw(::com::sun::star::uno::RuntimeException);

                            // XUnoTunnel
    virtual sal_Int64 SAL_CALL getSomething( const ::com::sun::star::uno::Sequence<
                                    sal_Int8 >& aIdentifier )
                                throw(::com::sun::star::uno::RuntimeException);

    static const ::com::sun::star::uno::Sequence<sal_Int8>& getUnoTunnelId();
    static ScTableConditionalFormat* getImplementation( const ::com::sun::star::uno::Reference<
                                    ::com::sun::star::sheet::XSheetConditionalEntries> xObj );

                            // XServiceInfo
    virtual ::rtl::OUString SAL_CALL getImplementationName()
                                throw(::com::sun::star::uno::RuntimeException);
    virtual sal_Bool SAL_CALL supportsService( const ::rtl::OUString& ServiceName )
                                throw(::com::sun::star::uno::RuntimeException);
    virtual ::com::sun::star::uno::Sequence< ::rtl::OUString > SAL_CALL getSupportedServiceNames()
                                throw(::com::sun::star::uno::RuntimeException);
};



class ScTableConditionalEntry : public cppu::WeakImplHelper3<
                            ::com::sun::star::sheet::XSheetCondition,
                            ::com::sun::star::sheet::XSheetConditionalEntry,
                            ::com::sun::star::lang::XServiceInfo >
{
private:
    ScTableConditionalFormat*	pParent;
    USHORT						nMode;		// enum ScConditionMode
    String						aExpr1;
    String						aExpr2;
    ScAddress					aSrcPos;
    String						aStyle;		// display name as stored in ScStyleSheet

public:
                            ScTableConditionalEntry( ScTableConditionalFormat* pPar,
                                                     USHORT nM, const String& rEx1,
                                                     const String& rEx2, const ScAddress& rPos,
                                                     const String& rSt );
    virtual					~ScTableConditionalEntry();

    void					GetData( USHORT& rM, String& rEx1, String& rEx2,
                                        ScAddress& rPos, String& rSt ) const;

                            // XSheetCondition
    virtual ::com::sun::star::sheet::ConditionOperator SAL_CALL getOperator()
                                throw(::com::sun::star::uno::RuntimeException);
    virtual void SAL_CALL	setOperator( ::com::sun::star::sheet::ConditionOperator nOperator )
                                throw(::com::sun::star::uno::RuntimeException);
    virtual ::rtl::OUString SAL_CALL getFormula1() throw(::com::sun::star::uno::RuntimeException);
    virtual void SAL_CALL	setFormula1( const ::rtl::OUString& aFormula1 )
                                throw(::com::sun::star::uno::RuntimeException);
    virtual ::rtl::OUString SAL_CALL getFormula2() throw(::com::sun::star::uno::RuntimeException);
    virtual void SAL_CALL	setFormula2( const ::rtl::OUString& aFormula2 )
                                throw(::com::sun::star::uno::RuntimeException);
    virtual ::com::sun::star::table::CellAddress SAL_CALL getSourcePosition()
                                throw(::com::sun::star::uno::RuntimeException);
    virtual void SAL_CALL setSourcePosition( const ::com::sun::star::table::CellAddress& aSourcePosition )
                                throw(::com::sun::star::uno::RuntimeException);

                            // XSheetConditionalEntry
    virtual ::rtl::OUString	SAL_CALL getStyleName() throw(::com::sun::star::uno::RuntimeException);
    virtual void SAL_CALL	setStyleName( const ::rtl::OUString& aStyleName )
                                throw(::com::sun::star::uno::RuntimeException);

                            // XServiceInfo
    virtual ::rtl::OUString SAL_CALL getImplementationName()
                                throw(::com::sun::star::uno::RuntimeException);
    virtual sal_Bool SAL_CALL supportsService( const ::rtl::OUString& ServiceName )
                                throw(::com::sun::star::uno::RuntimeException);
    virtual ::com::sun::star::uno::Sequence< ::rtl::OUString > SAL_CALL getSupportedServiceNames()
                                throw(::com::sun::star::uno::RuntimeException);
};



class ScTableValidationObj : public cppu::WeakImplHelper4<
                            ::com::sun::star::sheet::XSheetCondition,
                            ::com::sun::star::beans::XPropertySet,
                            ::com::sun::star::lang::XUnoTunnel,
                            ::com::sun::star::lang::XServiceInfo >
{
private:
    SfxItemPropertySet	aPropSet;
    USHORT				nMode;			// enum ScConditionMode
    String				aExpr1;
    String				aExpr2;
    ScAddress			aSrcPos;
    USHORT				nValMode;		// enum ScValidationMode
    BOOL				bIgnoreBlank;
    BOOL				bShowInput;
    String				aInputTitle;
    String				aInputMessage;
    BOOL				bShowError;
    USHORT				nErrorStyle;	// enum ScValidErrorStyle
    String				aErrorTitle;
    String				aErrorMessage;

    void					ClearData_Impl();

public:
                            ScTableValidationObj(ScDocument* pDoc, ULONG nKey,
                                                BOOL bEnglish, BOOL bCompileXML);
    virtual					~ScTableValidationObj();

    ScValidationData*		CreateValidationData( ScDocument* pDoc,
                                                BOOL bEnglish, BOOL bCompileXML ) const;
    void					DataChanged();

                            // XSheetCondition
    virtual ::com::sun::star::sheet::ConditionOperator SAL_CALL getOperator()
                                throw(::com::sun::star::uno::RuntimeException);
    virtual void SAL_CALL	setOperator( ::com::sun::star::sheet::ConditionOperator nOperator )
                                throw(::com::sun::star::uno::RuntimeException);
    virtual ::rtl::OUString SAL_CALL getFormula1() throw(::com::sun::star::uno::RuntimeException);
    virtual void SAL_CALL	setFormula1( const ::rtl::OUString& aFormula1 )
                                throw(::com::sun::star::uno::RuntimeException);
    virtual ::rtl::OUString SAL_CALL getFormula2() throw(::com::sun::star::uno::RuntimeException);
    virtual void SAL_CALL	setFormula2( const ::rtl::OUString& aFormula2 )
                                throw(::com::sun::star::uno::RuntimeException);
    virtual ::com::sun::star::table::CellAddress SAL_CALL getSourcePosition()
                                throw(::com::sun::star::uno::RuntimeException);
    virtual void SAL_CALL setSourcePosition( const ::com::sun::star::table::CellAddress& aSourcePosition )
                                throw(::com::sun::star::uno::RuntimeException);

                            // XPropertySet
    virtual ::com::sun::star::uno::Reference< ::com::sun::star::beans::XPropertySetInfo >
                            SAL_CALL getPropertySetInfo()
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

                            // XUnoTunnel
    virtual sal_Int64 SAL_CALL getSomething( const ::com::sun::star::uno::Sequence<
                                    sal_Int8 >& aIdentifier )
                                throw(::com::sun::star::uno::RuntimeException);

    static const ::com::sun::star::uno::Sequence<sal_Int8>& getUnoTunnelId();
    static ScTableValidationObj* getImplementation( const ::com::sun::star::uno::Reference<
                                    ::com::sun::star::beans::XPropertySet> xObj );

                            // XServiceInfo
    virtual ::rtl::OUString SAL_CALL getImplementationName()
                                throw(::com::sun::star::uno::RuntimeException);
    virtual sal_Bool SAL_CALL supportsService( const ::rtl::OUString& ServiceName )
                                throw(::com::sun::star::uno::RuntimeException);
    virtual ::com::sun::star::uno::Sequence< ::rtl::OUString > SAL_CALL getSupportedServiceNames()
                                throw(::com::sun::star::uno::RuntimeException);
};


} //namespace binfilter
#endif

