/*************************************************************************
 *
 *  $RCSfile: fielduno.hxx,v $
 *
 *  $Revision: 1.1.1.1 $
 *
 *  last change: $Author: hjs $ $Date: 2003-10-01 12:23:19 $
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

#ifndef SC_FIELDUNO_HXX
#define SC_FIELDUNO_HXX

#ifndef SC_SCGLOB_HXX
#include "global.hxx"			// ScRange, ScAddress
#endif
#ifndef SC_MUTEXHLP_HXX
#include "mutexhlp.hxx"
#endif
 
#ifndef _SFXLSTNER_HXX //autogen
#include <svtools/lstner.hxx>
#endif
#ifndef _SFX_ITEMPROP_HXX
#include <svtools/itemprop.hxx>
#endif
#ifndef _MyEDITDATA_HXX //autogen
#include <bf_svx/editdata.hxx>
#endif

#ifndef _COM_SUN_STAR_TEXT_XTEXTFIELD_HPP_
#include <com/sun/star/text/XTextField.hpp>
#endif
#ifndef _COM_SUN_STAR_LANG_XSERVICEINFO_HPP_
#include <com/sun/star/lang/XServiceInfo.hpp>
#endif
#ifndef _COM_SUN_STAR_CONTAINER_XCONTAINER_HPP_
#include <com/sun/star/container/XContainer.hpp>
#endif
#ifndef _COM_SUN_STAR_LANG_XUNOTUNNEL_HPP_
#include <com/sun/star/lang/XUnoTunnel.hpp>
#endif
#ifndef _COM_SUN_STAR_CONTAINER_XENUMERATIONACCESS_HPP_
#include <com/sun/star/container/XEnumerationAccess.hpp>
#endif
#ifndef _COM_SUN_STAR_CONTAINER_XINDEXACCESS_HPP_
#include <com/sun/star/container/XIndexAccess.hpp>
#endif
#ifndef _COM_SUN_STAR_BEANS_XPROPERTYSET_HPP_
#include <com/sun/star/beans/XPropertySet.hpp>
#endif
#ifndef _COM_SUN_STAR_UTIL_XREFRESHABLE_HPP_
#include <com/sun/star/util/XRefreshable.hpp>
#endif

#ifndef _CPPUHELPER_COMPONENT_HXX_
#include <cppuhelper/component.hxx>
#endif
#ifndef _CPPUHELPER_IMPLBASE5_HXX_
#include <cppuhelper/implbase5.hxx>
#endif
#ifndef _OSL_MUTEX_HXX_ 
#include <osl/mutex.hxx>
#endif

class SvxEditSource;
class SvxFieldItem;
class ScCellFieldObj;
class ScHeaderFieldObj;
class ScHeaderFooterContentObj;


//------------------------------------------------------------------


class ScCellFieldsObj : public cppu::WeakImplHelper5<
                            com::sun::star::container::XEnumerationAccess,
                            com::sun::star::container::XIndexAccess,
                            com::sun::star::container::XContainer,
                            com::sun::star::util::XRefreshable,
                            com::sun::star::lang::XServiceInfo >,
                        public SfxListener
{
private:
    ScDocShell*				pDocShell;
    ScAddress				aCellPos;
    SvxEditSource*			pEditSource;
    ///	List of refresh listeners.
    cppu::OInterfaceContainerHelper* mpRefreshListeners;
    /// mutex to lock the InterfaceContainerHelper
    osl::Mutex              aMutex;

    ScCellFieldObj*			GetObjectByIndex_Impl(INT32 Index) const;

public:
                            ScCellFieldsObj(ScDocShell* pDocSh, const ScAddress& rPos);
    virtual					~ScCellFieldsObj();

    virtual void			Notify( SfxBroadcaster& rBC, const SfxHint& rHint );

                            // XIndexAccess
    virtual sal_Int32 SAL_CALL getCount() throw(::com::sun::star::uno::RuntimeException);
    virtual ::com::sun::star::uno::Any SAL_CALL getByIndex( sal_Int32 Index )
                                throw(::com::sun::star::lang::IndexOutOfBoundsException,
                                    ::com::sun::star::lang::WrappedTargetException,
                                    ::com::sun::star::uno::RuntimeException);

                            // XEnumerationAccess
    virtual ::com::sun::star::uno::Reference< ::com::sun::star::container::XEnumeration > SAL_CALL
                            createEnumeration() throw(::com::sun::star::uno::RuntimeException);

                            // XElementAccess
    virtual ::com::sun::star::uno::Type SAL_CALL getElementType()
                                throw(::com::sun::star::uno::RuntimeException);
    virtual sal_Bool SAL_CALL hasElements() throw(::com::sun::star::uno::RuntimeException);

                            // XContainer
    virtual void SAL_CALL	addContainerListener( const ::com::sun::star::uno::Reference<
                                ::com::sun::star::container::XContainerListener >& xListener )
                                    throw(::com::sun::star::uno::RuntimeException);
    virtual void SAL_CALL	removeContainerListener( const ::com::sun::star::uno::Reference<
                                ::com::sun::star::container::XContainerListener >& xListener )
                                    throw(::com::sun::star::uno::RuntimeException);

                            // XRefreshable
    virtual void SAL_CALL refresh(  ) 
                                    throw (::com::sun::star::uno::RuntimeException);
    virtual void SAL_CALL addRefreshListener( const ::com::sun::star::uno::Reference< 
                                ::com::sun::star::util::XRefreshListener >& l )
                                    throw (::com::sun::star::uno::RuntimeException);
    virtual void SAL_CALL removeRefreshListener( const ::com::sun::star::uno::Reference<
                                ::com::sun::star::util::XRefreshListener >& l )
                                    throw (::com::sun::star::uno::RuntimeException);

                            // XServiceInfo
    virtual ::rtl::OUString SAL_CALL getImplementationName()
                                throw(::com::sun::star::uno::RuntimeException);
    virtual sal_Bool SAL_CALL supportsService( const ::rtl::OUString& ServiceName )
                                throw(::com::sun::star::uno::RuntimeException);
    virtual ::com::sun::star::uno::Sequence< ::rtl::OUString > SAL_CALL getSupportedServiceNames()
                                throw(::com::sun::star::uno::RuntimeException);
};


class ScCellFieldObj : public ScMutexHelper,
                        public ::cppu::OComponentHelper,
                        public ::com::sun::star::text::XTextField,
                        public ::com::sun::star::beans::XPropertySet,
                        public ::com::sun::star::lang::XUnoTunnel,
                        public ::com::sun::star::lang::XServiceInfo,
                        public SfxListener
{
private:
    SfxItemPropertySet		aPropSet;
    ScDocShell*				pDocShell;
    ScAddress				aCellPos;
    SvxEditSource*			pEditSource;
    ESelection				aSelection;

    String					aUrl;				// Inhalt, wenn noch nicht eingefuegt (nur dann!)
    String					aRepresentation;
    String					aTarget;

public:
                            ScCellFieldObj();
                            ScCellFieldObj(ScDocShell* pDocSh, const ScAddress& rPos,
                                            const ESelection& rSel);
    virtual					~ScCellFieldObj();

    virtual void			Notify( SfxBroadcaster& rBC, const SfxHint& rHint );

                            // per getImplementation gerufen:
    void					DeleteField();
    BOOL					IsInserted() const		{ return pEditSource != NULL; }
    SvxFieldItem			CreateFieldItem();
    void					InitDoc( ScDocShell* pDocSh, const ScAddress& rPos,
                                        const ESelection& rSel );

    virtual ::com::sun::star::uno::Any SAL_CALL queryAggregation(
                                const ::com::sun::star::uno::Type & rType )
                                    throw(::com::sun::star::uno::RuntimeException);
    virtual ::com::sun::star::uno::Any SAL_CALL queryInterface(
                                const ::com::sun::star::uno::Type & rType )
                                    throw(::com::sun::star::uno::RuntimeException);
    virtual void SAL_CALL	acquire() throw();
    virtual void SAL_CALL	release() throw();

                            // XTextField
    virtual ::rtl::OUString SAL_CALL getPresentation( sal_Bool bShowCommand )
                                throw(::com::sun::star::uno::RuntimeException);

                            // XTextContent
    virtual void SAL_CALL	attach( const ::com::sun::star::uno::Reference<
                                ::com::sun::star::text::XTextRange >& xTextRange )
                                    throw(::com::sun::star::lang::IllegalArgumentException,
                                            ::com::sun::star::uno::RuntimeException);
    virtual ::com::sun::star::uno::Reference< ::com::sun::star::text::XTextRange > SAL_CALL
                            getAnchor() throw(::com::sun::star::uno::RuntimeException);

                            // XComponent
    virtual void SAL_CALL	dispose() throw(::com::sun::star::uno::RuntimeException);
    virtual void SAL_CALL	addEventListener( const ::com::sun::star::uno::Reference<
                                ::com::sun::star::lang::XEventListener >& xListener )
                                    throw(::com::sun::star::uno::RuntimeException);
    virtual void SAL_CALL	removeEventListener( const ::com::sun::star::uno::Reference<
                                ::com::sun::star::lang::XEventListener >& aListener )
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

    static const com::sun::star::uno::Sequence<sal_Int8>& getUnoTunnelId();
    static ScCellFieldObj* getImplementation( const com::sun::star::uno::Reference<
                                    com::sun::star::text::XTextContent> xObj );

                            // XServiceInfo
    virtual ::rtl::OUString SAL_CALL getImplementationName()
                                throw(::com::sun::star::uno::RuntimeException);
    virtual sal_Bool SAL_CALL supportsService( const ::rtl::OUString& ServiceName )
                                throw(::com::sun::star::uno::RuntimeException);
    virtual ::com::sun::star::uno::Sequence< ::rtl::OUString > SAL_CALL getSupportedServiceNames()
                                throw(::com::sun::star::uno::RuntimeException);

                            // XTypeProvider
    virtual ::com::sun::star::uno::Sequence< ::com::sun::star::uno::Type > SAL_CALL getTypes()
                                throw(::com::sun::star::uno::RuntimeException);
    virtual ::com::sun::star::uno::Sequence< sal_Int8 > SAL_CALL getImplementationId()
                                throw(::com::sun::star::uno::RuntimeException);
};

//------------------------------------------------------------------

class ScHeaderFieldsObj : public cppu::WeakImplHelper5<
                            com::sun::star::container::XEnumerationAccess,
                            com::sun::star::container::XIndexAccess,
                            com::sun::star::container::XContainer,
                            com::sun::star::util::XRefreshable,
                            com::sun::star::lang::XServiceInfo >
{
private:
    ScHeaderFooterContentObj*	pContentObj;
    USHORT						nPart;
    UINT16						nType;
    SvxEditSource*				pEditSource;

    ///	List of refresh listeners.
    cppu::OInterfaceContainerHelper* mpRefreshListeners;
    /// mutex to lock the InterfaceContainerHelper
    osl::Mutex                  aMutex;

    ScHeaderFieldObj*		GetObjectByIndex_Impl(INT32 Index) const;

public:
                            ScHeaderFieldsObj(ScHeaderFooterContentObj* pContent,
                                                USHORT nP, USHORT nT);
    virtual					~ScHeaderFieldsObj();

                            // XIndexAccess
    virtual sal_Int32 SAL_CALL getCount() throw(::com::sun::star::uno::RuntimeException);
    virtual ::com::sun::star::uno::Any SAL_CALL getByIndex( sal_Int32 Index )
                                throw(::com::sun::star::lang::IndexOutOfBoundsException,
                                    ::com::sun::star::lang::WrappedTargetException,
                                    ::com::sun::star::uno::RuntimeException);

                            // XEnumerationAccess
    virtual ::com::sun::star::uno::Reference< ::com::sun::star::container::XEnumeration > SAL_CALL
                            createEnumeration() throw(::com::sun::star::uno::RuntimeException);

                            // XElementAccess
    virtual ::com::sun::star::uno::Type SAL_CALL getElementType()
                                throw(::com::sun::star::uno::RuntimeException);
    virtual sal_Bool SAL_CALL hasElements() throw(::com::sun::star::uno::RuntimeException);

                            // XContainer
    virtual void SAL_CALL	addContainerListener( const ::com::sun::star::uno::Reference<
                                ::com::sun::star::container::XContainerListener >& xListener )
                                    throw(::com::sun::star::uno::RuntimeException);
    virtual void SAL_CALL	removeContainerListener( const ::com::sun::star::uno::Reference<
                                ::com::sun::star::container::XContainerListener >& xListener )
                                    throw(::com::sun::star::uno::RuntimeException);

                            // XRefreshable
    virtual void SAL_CALL refresh(  ) 
                                    throw (::com::sun::star::uno::RuntimeException);
    virtual void SAL_CALL addRefreshListener( const ::com::sun::star::uno::Reference< 
                                ::com::sun::star::util::XRefreshListener >& l )
                                    throw (::com::sun::star::uno::RuntimeException);
    virtual void SAL_CALL removeRefreshListener( const ::com::sun::star::uno::Reference<
                                ::com::sun::star::util::XRefreshListener >& l )
                                    throw (::com::sun::star::uno::RuntimeException);

                            // XServiceInfo
    virtual ::rtl::OUString SAL_CALL getImplementationName()
                                throw(::com::sun::star::uno::RuntimeException);
    virtual sal_Bool SAL_CALL supportsService( const ::rtl::OUString& ServiceName )
                                throw(::com::sun::star::uno::RuntimeException);
    virtual ::com::sun::star::uno::Sequence< ::rtl::OUString > SAL_CALL getSupportedServiceNames()
                                throw(::com::sun::star::uno::RuntimeException);
};


class ScHeaderFieldObj : public ScMutexHelper,
                            public ::cppu::OComponentHelper,
                            public ::com::sun::star::text::XTextField,
                            public ::com::sun::star::beans::XPropertySet,
                            public ::com::sun::star::lang::XUnoTunnel,
                            public ::com::sun::star::lang::XServiceInfo
{
private:
    SfxItemPropertySet			aPropSet;
    ScHeaderFooterContentObj*	pContentObj;
    USHORT						nPart;
    UINT16						nType;
    SvxEditSource*				pEditSource;
    ESelection					aSelection;
    sal_Int16					nFileFormat;		// enum SvxFileFormat, valid if not inserted

public:
                            ScHeaderFieldObj();
                            ScHeaderFieldObj(ScHeaderFooterContentObj* pContent, USHORT nP,
                                            USHORT nT, const ESelection& rSel);
    virtual					~ScHeaderFieldObj();

                            // per getImplementation gerufen:
    void					DeleteField();
    BOOL					IsInserted() const		{ return pEditSource != NULL; }
    SvxFieldItem			CreateFieldItem();
    void					InitDoc( ScHeaderFooterContentObj* pContent, USHORT nP,
                                        const ESelection& rSel );

    virtual ::com::sun::star::uno::Any SAL_CALL queryAggregation(
                                const ::com::sun::star::uno::Type & rType )
                                    throw(::com::sun::star::uno::RuntimeException);
    virtual ::com::sun::star::uno::Any SAL_CALL queryInterface(
                                const ::com::sun::star::uno::Type & rType )
                                    throw(::com::sun::star::uno::RuntimeException);
    virtual void SAL_CALL	acquire() throw();
    virtual void SAL_CALL	release() throw();

                            // XTextField
    virtual ::rtl::OUString SAL_CALL getPresentation( sal_Bool bShowCommand )
                                throw(::com::sun::star::uno::RuntimeException);

                            // XTextContent
    virtual void SAL_CALL	attach( const ::com::sun::star::uno::Reference<
                                ::com::sun::star::text::XTextRange >& xTextRange )
                                    throw(::com::sun::star::lang::IllegalArgumentException,
                                            ::com::sun::star::uno::RuntimeException);
    virtual ::com::sun::star::uno::Reference< ::com::sun::star::text::XTextRange > SAL_CALL
                            getAnchor() throw(::com::sun::star::uno::RuntimeException);

                            // XComponent
    virtual void SAL_CALL	dispose() throw(::com::sun::star::uno::RuntimeException);
    virtual void SAL_CALL	addEventListener( const ::com::sun::star::uno::Reference<
                                ::com::sun::star::lang::XEventListener >& xListener )
                                    throw(::com::sun::star::uno::RuntimeException);
    virtual void SAL_CALL	removeEventListener( const ::com::sun::star::uno::Reference<
                                ::com::sun::star::lang::XEventListener >& aListener )
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

    static const com::sun::star::uno::Sequence<sal_Int8>& getUnoTunnelId();
    static ScHeaderFieldObj* getImplementation( const com::sun::star::uno::Reference<
                                    com::sun::star::text::XTextContent> xObj );

                            // XServiceInfo
    virtual ::rtl::OUString SAL_CALL getImplementationName()
                                throw(::com::sun::star::uno::RuntimeException);
    virtual sal_Bool SAL_CALL supportsService( const ::rtl::OUString& ServiceName )
                                throw(::com::sun::star::uno::RuntimeException);
    virtual ::com::sun::star::uno::Sequence< ::rtl::OUString > SAL_CALL getSupportedServiceNames()
                                throw(::com::sun::star::uno::RuntimeException);

                            // XTypeProvider
    virtual ::com::sun::star::uno::Sequence< ::com::sun::star::uno::Type > SAL_CALL getTypes()
                                throw(::com::sun::star::uno::RuntimeException);
    virtual ::com::sun::star::uno::Sequence< sal_Int8 > SAL_CALL getImplementationId()
                                throw(::com::sun::star::uno::RuntimeException);
};

#endif

