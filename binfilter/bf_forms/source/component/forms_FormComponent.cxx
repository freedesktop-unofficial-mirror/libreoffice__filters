/* -*- Mode: C++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */
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

#include <bf_svtools/bf_solar.h>

#include "FormComponent.hxx"

#include <com/sun/star/awt/XTextComponent.hpp>
#include <com/sun/star/awt/XWindow.hpp>
#include <com/sun/star/io/XMarkableStream.hpp>
#include <com/sun/star/form/XLoadable.hpp>
#include <com/sun/star/form/XForm.hpp>
#include <com/sun/star/sdbc/ColumnValue.hpp>

#include <connectivity/dbtools.hxx>
#include "property.hrc"
#include "services.hxx"
#include <rtl/logfile.hxx>


#include "frm_resource.hxx"
#include "frm_resource.hrc"

#include <comphelper/property.hxx>


#include <com/sun/star/form/FormComponentType.hpp>

#include <com/sun/star/sdbcx/XColumnsSupplier.hpp>

namespace binfilter {


//... namespace frm .......................................................
namespace frm
{
//.........................................................................
using namespace ::com::sun::star::uno;
using namespace ::com::sun::star::sdb;
using namespace ::com::sun::star::sdbc;
using namespace ::com::sun::star::sdbcx;
using namespace ::com::sun::star::beans;
using namespace ::com::sun::star::container;
using namespace ::com::sun::star::form;
using namespace ::com::sun::star::awt;
using namespace ::com::sun::star::io;
using namespace ::com::sun::star::lang;
using namespace ::com::sun::star::util;
using namespace ::dbtools;
using namespace ::comphelper;

//=========================================================================
//= base class for form layer controls
//=========================================================================
DBG_NAME(frm_OControl)
//------------------------------------------------------------------------------
OControl::OControl(const Reference<com::sun::star::lang::XMultiServiceFactory>& _rxFactory, const rtl::OUString& _sService)
            :OComponentHelper(m_aMutex)
            ,m_aService(_sService)
            ,m_xServiceFactory(_rxFactory)
{
    DBG_CTOR(frm_OControl, NULL);
    // VCL-Control aggregieren
    // bei Aggregation den Refcount um eins erhoehen da im setDelegator
    // das Aggregat selbst den Refcount erhoeht
    increment(m_refCount);
    {
        m_xAggregate = Reference<XAggregation>(_rxFactory->createInstance(_sService), UNO_QUERY);
        m_xControl = Reference<XControl>(m_xAggregate, UNO_QUERY);
    }

    if (m_xAggregate.is())
    {
        m_xAggregate->setDelegator(static_cast<XWeak*>(this));
    }

    // Refcount wieder bei NULL
    /*sal_Int32 n =*/ decrement(m_refCount);
}

//------------------------------------------------------------------------------
OControl::~OControl()
{
    DBG_DTOR(frm_OControl, NULL);
    // Freigeben der Aggregation
    if (m_xAggregate.is())
    {
        m_xAggregate->setDelegator(InterfaceRef());
    }
}

// UNO Anbindung
//------------------------------------------------------------------------------
Any SAL_CALL OControl::queryAggregation( const Type& _rType ) throw(RuntimeException)
{
    // ask the base class
    Any aReturn( OComponentHelper::queryAggregation(_rType) );
    // ask our own interfaces
    if (!aReturn.hasValue())
    {
        aReturn = OControl_BASE::queryInterface(_rType);
        // ask our aggregate
        if (!aReturn.hasValue() && m_xAggregate.is())
            aReturn = m_xAggregate->queryAggregation(_rType);
    }

    return aReturn;
}

//------------------------------------------------------------------------------
Sequence<sal_Int8> SAL_CALL OControl::getImplementationId() throw(RuntimeException)
{
    return OImplementationIds::getImplementationId(getTypes());
}

//------------------------------------------------------------------------------
Sequence<Type> SAL_CALL OControl::getTypes() throw(RuntimeException)
{
    Sequence<Type> aOwnTypes = _getTypes();
    Reference<com::sun::star::lang::XTypeProvider> xProv;

    if (query_aggregation(m_xAggregate, xProv))
        return concatSequences(aOwnTypes, xProv->getTypes());
    else
        return aOwnTypes;
}

//------------------------------------------------------------------------------
Sequence<Type> OControl::_getTypes()
{
    static Sequence<Type> aTypes;
    if (!aTypes.getLength())
        aTypes = concatSequences(OComponentHelper::getTypes(), OControl_BASE::getTypes());
    return aTypes;
}

// OComponentHelper
//------------------------------------------------------------------------------
void OControl::disposing()
{
    OComponentHelper::disposing();

    Reference<com::sun::star::lang::XComponent> xComp;
    if (query_aggregation(m_xAggregate, xComp))
        xComp->dispose();
}

// XServiceInfo
//------------------------------------------------------------------------------
sal_Bool SAL_CALL OControl::supportsService(const rtl::OUString& _rsServiceName) throw ( RuntimeException)
{
        Sequence<rtl::OUString> aSupported = getSupportedServiceNames();
    const rtl::OUString* pSupported = aSupported.getConstArray();
    for (sal_Int32 i=0; i<aSupported.getLength(); ++i, ++pSupported)
        if (pSupported->equals(_rsServiceName))
            return sal_True;
    return sal_False;
}

//------------------------------------------------------------------------------
Sequence<rtl::OUString> SAL_CALL OControl::getSupportedServiceNames() throw(RuntimeException)
{
    Sequence< rtl::OUString > aSupported;

    // ask our aggregate
    Reference< com::sun::star::lang::XServiceInfo > xInfo;
    if ( query_aggregation( m_xAggregate, xInfo ) )
        aSupported = xInfo->getSupportedServiceNames();

    return aSupported;
}

// XEventListener
//------------------------------------------------------------------------------
void SAL_CALL OControl::disposing(const com::sun::star::lang::EventObject& _rEvent) throw (RuntimeException)
{
    InterfaceRef xAggAsIface;
    query_aggregation(m_xAggregate, xAggAsIface);

    // does the disposing come from the aggregate ?
    if (xAggAsIface != InterfaceRef(_rEvent.Source, UNO_QUERY))
    {	// no -> forward it
                Reference<com::sun::star::lang::XEventListener> xListener;
        if (query_aggregation(m_xAggregate, xListener))
            xListener->disposing(_rEvent);
    }
}

// XControl
//------------------------------------------------------------------------------
void SAL_CALL OControl::setContext(const InterfaceRef& Context) throw (RuntimeException)
{
    if (m_xControl.is())
        m_xControl->setContext(Context);
}

//------------------------------------------------------------------------------
InterfaceRef SAL_CALL OControl::getContext() throw (RuntimeException)
{
    return m_xControl.is() ? m_xControl->getContext() : InterfaceRef();
}

//------------------------------------------------------------------------------
void SAL_CALL OControl::createPeer(const Reference<XToolkit>& Toolkit, const Reference<XWindowPeer>& Parent) throw (RuntimeException)
{
    if (m_xControl.is())
        m_xControl->createPeer(Toolkit, Parent);
}

//------------------------------------------------------------------------------
Reference<XWindowPeer> SAL_CALL OControl::getPeer() throw ( RuntimeException)
{
        return m_xControl.is() ? m_xControl->getPeer() : Reference<XWindowPeer>();
}

//------------------------------------------------------------------------------
sal_Bool SAL_CALL OControl::setModel(const Reference<XControlModel>& Model) throw ( RuntimeException)
{
    return m_xControl.is() ? m_xControl->setModel( Model ) : sal_False;
}

//------------------------------------------------------------------------------
Reference<XControlModel> SAL_CALL OControl::getModel() throw ( RuntimeException)
{
        return m_xControl.is() ? m_xControl->getModel() : Reference<XControlModel>();
}

//------------------------------------------------------------------------------
Reference<XView> SAL_CALL OControl::getView() throw ( RuntimeException)
{
        return m_xControl.is() ? m_xControl->getView() : Reference<XView>();
}

//------------------------------------------------------------------------------
void SAL_CALL OControl::setDesignMode(sal_Bool bOn) throw ( RuntimeException)
{
    if (m_xControl.is())
        m_xControl->setDesignMode(bOn);
}

//------------------------------------------------------------------------------
sal_Bool SAL_CALL OControl::isDesignMode() throw ( RuntimeException)
{
    return m_xControl.is() ? m_xControl->isDesignMode() : sal_True;
}

//------------------------------------------------------------------------------
sal_Bool SAL_CALL OControl::isTransparent() throw ( RuntimeException)
{
    return m_xControl.is() ? m_xControl->isTransparent() : sal_True;
}

//==================================================================
//= OBoundControl
//==================================================================
DBG_NAME(frm_OBoundControl)
//------------------------------------------------------------------
OBoundControl::OBoundControl(const Reference<com::sun::star::lang::XMultiServiceFactory>& _rxFactory, const ::rtl::OUString& _sService)
        :OControl(_rxFactory, _sService)
        ,m_bLocked(sal_False)
{
    DBG_CTOR(frm_OBoundControl, NULL);
}

//------------------------------------------------------------------
OBoundControl::~OBoundControl()
{
    DBG_DTOR(frm_OBoundControl, NULL);
}
// -----------------------------------------------------------------------------
Sequence< Type>	OBoundControl::_getTypes()
{
    static Sequence<Type> aTypes;
    if (!aTypes.getLength())
        aTypes = concatSequences(OControl::_getTypes(), OBoundControl_BASE::getTypes());
    return aTypes;
}
//------------------------------------------------------------------
Any SAL_CALL OBoundControl::queryAggregation(const Type& _rType) throw(RuntimeException)
{
    // ask the base class
    Any aReturn(OControl::queryAggregation(_rType));
    // ask our own interfaces
    if (!aReturn.hasValue())
        aReturn = OBoundControl_BASE::queryInterface(_rType);

    return aReturn;
}

//------------------------------------------------------------------
sal_Bool SAL_CALL OBoundControl::getLock() throw(RuntimeException)
{
    return m_bLocked;
}

//------------------------------------------------------------------
void SAL_CALL OBoundControl::setLock(sal_Bool _bLock) throw(RuntimeException)
{
    if (m_bLocked == _bLock)
        return;

    osl::MutexGuard aGuard(m_aMutex);
    _setLock(_bLock);
    m_bLocked = _bLock;
}

//------------------------------------------------------------------
void OBoundControl::_setLock(sal_Bool _bLock)
{
    // try to set the text component to readonly
        Reference<XWindowPeer> xPeer = getPeer();
        Reference<com::sun::star::awt::XTextComponent> xText(xPeer, UNO_QUERY);

    if (xText.is())
        xText->setEditable(!_bLock);
    else
    {
        // disable the window
                Reference<XWindow> xComp(xPeer, UNO_QUERY);
        if (xComp.is())
            xComp->setEnable(!_bLock);
    }
}

//==================================================================
//= OControlModel
//==================================================================
ConcretInfoService OControlModel::s_aPropInfos;
DBG_NAME(OControlModel)
//------------------------------------------------------------------
Sequence<sal_Int8> SAL_CALL OControlModel::getImplementationId() throw(RuntimeException)
{
    return OImplementationIds::getImplementationId(getTypes());
}

//------------------------------------------------------------------
Sequence<Type> SAL_CALL OControlModel::getTypes() throw(RuntimeException)
{
    Sequence<Type> aOwnTypes = _getTypes();
    Reference<com::sun::star::lang::XTypeProvider> xProv;

    if (query_aggregation(m_xAggregate, xProv))
        return concatSequences(aOwnTypes, xProv->getTypes());
    else
        return aOwnTypes;
}

//------------------------------------------------------------------------------
Sequence<Type> OControlModel::_getTypes()
{
    static Sequence<Type> aTypes;
    if (!aTypes.getLength())
    {
        // my two base classes
        aTypes = concatSequences(OComponentHelper::getTypes(), OPropertySetAggregationHelper::getTypes(), OControlModel_BASE::getTypes());
    }
    return aTypes;
}

//------------------------------------------------------------------
Any SAL_CALL OControlModel::queryAggregation(const Type& _rType) throw (RuntimeException)
{
    // base class 1
    Any aReturn(OComponentHelper::queryAggregation(_rType));

    // base class 2
    if (!aReturn.hasValue())
    {
        aReturn = OControlModel_BASE::queryInterface(_rType);

        // our own interfaces
        if (!aReturn.hasValue())
        {
            aReturn = OPropertySetAggregationHelper::queryInterface(_rType);
            // our aggregate
            if (!aReturn.hasValue() && m_xAggregate.is() && !_rType.equals(::getCppuType(static_cast< Reference< XCloneable>* >(NULL))))
                aReturn = m_xAggregate->queryAggregation(_rType);
        }
    }
    return aReturn;
}

//------------------------------------------------------------------------------
void OControlModel::readHelpTextCompatibly(const staruno::Reference< stario::XObjectInputStream >& _rxInStream)
{
    ::rtl::OUString sHelpText;
    ::comphelper::operator>>( _rxInStream, sHelpText);
    try
    {
        if (m_xAggregateSet.is())
            m_xAggregateSet->setPropertyValue(PROPERTY_HELPTEXT, makeAny(sHelpText));
    }
    catch(const Exception&)
    {
        OSL_FAIL("OControlModel::readHelpTextCompatibly: could not forward the property value to the aggregate!");
    }
}

//------------------------------------------------------------------------------
void OControlModel::writeHelpTextCompatibly(const staruno::Reference< stario::XObjectOutputStream >& _rxOutStream)
{
    ::rtl::OUString sHelpText;
    try
    {
        if (m_xAggregateSet.is())
            m_xAggregateSet->getPropertyValue(PROPERTY_HELPTEXT) >>= sHelpText;
    }
    catch(const Exception&)
    {
        OSL_FAIL("OControlModel::writeHelpTextCompatibly: could not retrieve the property value from the aggregate!");
    }
    ::comphelper::operator<<( _rxOutStream, sHelpText);
}

//------------------------------------------------------------------
OControlModel::OControlModel(
                        const Reference<com::sun::star::lang::XMultiServiceFactory>& _rxFactory,
            const ::rtl::OUString& _rUnoControlModelTypeName,
            const ::rtl::OUString& rDefault, const sal_Bool _bSetDelegator)
    :OComponentHelper(m_aMutex)
    ,OPropertySetAggregationHelper(OComponentHelper::rBHelper)
    ,m_xServiceFactory(_rxFactory)
    ,m_nTabIndex(FRM_DEFAULT_TABINDEX)
    ,m_nClassId(FormComponentType::CONTROL)
{
    DBG_CTOR(OControlModel, NULL);
    if (_rUnoControlModelTypeName.getLength())	// the is a model we have to aggregate
    {
        increment(m_refCount);

        {
            m_xAggregate = Reference<XAggregation>(_rxFactory->createInstance(_rUnoControlModelTypeName), UNO_QUERY);
            setAggregation(m_xAggregate);

            if (m_xAggregateSet.is() && rDefault.getLength())
                m_xAggregateSet->setPropertyValue(PROPERTY_DEFAULTCONTROL, makeAny(rDefault));
        }

        if (_bSetDelegator)
            doSetDelegator();

        // Refcount wieder bei NULL
        decrement(m_refCount);
    }
}

//------------------------------------------------------------------
OControlModel::OControlModel( const OControlModel* _pOriginal, const Reference< XMultiServiceFactory>& _rxFactory, const sal_Bool _bSetDelegator )
    :OComponentHelper( m_aMutex )
    ,OPropertySetAggregationHelper( OComponentHelper::rBHelper )
    ,m_xServiceFactory( _rxFactory )
    ,m_nTabIndex( FRM_DEFAULT_TABINDEX )
    ,m_nClassId( FormComponentType::CONTROL )
{
    DBG_CTOR( OControlModel, NULL );
    DBG_ASSERT( _pOriginal, "OControlModel::OControlModel: invalid original!" );

    // copy members
    m_aName = _pOriginal->m_aName;
    m_aTag = _pOriginal->m_aTag;
    m_nTabIndex = _pOriginal->m_nTabIndex;
    m_nClassId = _pOriginal->m_nClassId;

    // temporarily increment refcount because of temporary references to ourself in the following
    increment( m_refCount );

    {
        // transfer the (only, at the very moment!) ref count
        m_xAggregate = createAggregateClone( _pOriginal );

        // set aggregation (retrieve other direct interfaces of the aggregate)
        setAggregation( m_xAggregate );
    }

    // set the delegator, if allowed by our derived class
    if ( _bSetDelegator )
        doSetDelegator();

    // decrement ref count
    decrement( m_refCount );
}

//------------------------------------------------------------------
OControlModel::~OControlModel()
{
    DBG_DTOR(OControlModel, NULL);
    // release the aggregate
    if (m_xAggregate.is())
        m_xAggregate->setDelegator(InterfaceRef());
}

//------------------------------------------------------------------------------
void OControlModel::doResetDelegator()
{
    if (m_xAggregate.is())
        m_xAggregate->setDelegator(NULL);
}

//------------------------------------------------------------------------------
void OControlModel::doSetDelegator()
{
    increment(m_refCount);
    if (m_xAggregate.is())
    {
        m_xAggregate->setDelegator(static_cast<XWeak*>(this));
    }
    decrement(m_refCount);
}

// XChild
//------------------------------------------------------------------------------
InterfaceRef SAL_CALL OControlModel::getParent() throw(RuntimeException)
{
    return m_xParent;
}

//------------------------------------------------------------------------------
void SAL_CALL OControlModel::setParent(const InterfaceRef& _rxParent) throw(com::sun::star::lang::NoSupportException, RuntimeException)
{
    osl::MutexGuard aGuard(m_aMutex);

    Reference<XComponent> xComp(m_xParent, UNO_QUERY);
    if (xComp.is())
        xComp->removeEventListener(static_cast<XPropertiesChangeListener*>(this));

    {
        xComp = xComp.query( _rxParent );
        RTL_LOGFILE_CONTEXT( aLogger, "forms::OControlModel::setParent::logOnEventListener" );
        if ( xComp.is() )
            xComp->addEventListener(static_cast<XPropertiesChangeListener*>(this));
    }

    m_xParent = _rxParent;
}

// XNamed
//------------------------------------------------------------------------------
::rtl::OUString SAL_CALL OControlModel::getName() throw(RuntimeException)
{
    ::rtl::OUString aReturn;
    OPropertySetHelper::getFastPropertyValue(PROPERTY_ID_NAME) >>= aReturn;
    return aReturn;
}

//------------------------------------------------------------------------------
void SAL_CALL OControlModel::setName(const ::rtl::OUString& _rName) throw(RuntimeException)
{
        setFastPropertyValue(PROPERTY_ID_NAME, makeAny(_rName));
}

// XServiceInfo
//------------------------------------------------------------------------------
sal_Bool SAL_CALL OControlModel::supportsService(const rtl::OUString& _rServiceName) throw ( RuntimeException)
{
        Sequence<rtl::OUString> aSupported = getSupportedServiceNames();
    const rtl::OUString* pSupported = aSupported.getConstArray();
    for (sal_Int32 i=0; i<aSupported.getLength(); ++i, ++pSupported)
        if (pSupported->equals(_rServiceName))
            return sal_True;
    return sal_False;
}

//------------------------------------------------------------------------------
Sequence<rtl::OUString> SAL_CALL OControlModel::getSupportedServiceNames() throw(RuntimeException)
{
        Sequence<rtl::OUString> aSupported;

    // ask our aggregate
        Reference<com::sun::star::lang::XServiceInfo> xInfo;
    if (query_aggregation(m_xAggregate, xInfo))
        aSupported = xInfo->getSupportedServiceNames();

    aSupported.realloc(aSupported.getLength() + 2);
    ::rtl::OUString* pArray = aSupported.getArray();
    pArray[aSupported.getLength()-2] = FRM_SUN_FORMCOMPONENT;
    pArray[aSupported.getLength()-1] = ::rtl::OUString( RTL_CONSTASCII_USTRINGPARAM( "com.sun.star.form.FormControlModel" ));

    return aSupported;
}

// XEventListener
//------------------------------------------------------------------------------
void SAL_CALL OControlModel::disposing(const com::sun::star::lang::EventObject& _rSource) throw (RuntimeException)
{
    // release the parent
    if (_rSource.Source == m_xParent)
    {
        osl::MutexGuard aGuard(m_aMutex);
        m_xParent = NULL;
    }
    else
    {
        Reference<com::sun::star::lang::XEventListener> xEvtLst;
        if (query_aggregation(m_xAggregate, xEvtLst))
        {
            osl::MutexGuard aGuard(m_aMutex);
            xEvtLst->disposing(_rSource);
        }
    }
}

// OComponentHelper
//-----------------------------------------------------------------------------
void OControlModel::disposing()
{
    OPropertySetAggregationHelper::disposing();

    Reference<com::sun::star::lang::XComponent> xComp;
    if (query_aggregation(m_xAggregate, xComp))
        xComp->dispose();

    setParent(Reference<XFormComponent>());
}

//------------------------------------------------------------------------------
void SAL_CALL OControlModel::write(const Reference<stario::XObjectOutputStream>& _rxOutStream)
                        throw(stario::IOException, RuntimeException)
{
    osl::MutexGuard aGuard(m_aMutex);

    // 1. Schreiben des UnoControls
    Reference<stario::XMarkableStream> xMark(_rxOutStream, UNO_QUERY);
    if ( !xMark.is() )
    {
        throw IOException(
            FRM_RES_STRING( RID_STR_INVALIDSTREAM ),
            static_cast< ::cppu::OWeakObject* >( this )
        );
    }

    sal_Int32 nMark = xMark->createMark();
    sal_Int32 nLen = 0;

    _rxOutStream->writeLong(nLen);

    Reference<stario::XPersistObject> xPersist;
    if (query_aggregation(m_xAggregate, xPersist))
        xPersist->write(_rxOutStream);

    // feststellen der Laenge
    nLen = xMark->offsetToMark(nMark) - 4;
    xMark->jumpToMark(nMark);
    _rxOutStream->writeLong(nLen);
    xMark->jumpToFurthest();
    xMark->deleteMark(nMark);

    // 2. Schreiben einer VersionsNummer
    _rxOutStream->writeShort(0x0003);

    // 3. Schreiben der allgemeinen Properties
    ::comphelper::operator<<( _rxOutStream, m_aName);
    _rxOutStream->writeShort(m_nTabIndex);
    ::comphelper::operator<<( _rxOutStream, m_aTag); // 3. version

    // !!! IMPORTANT NOTE !!!
    // don't write any new members here : this wouldn't be compatible with older versions, as OControlModel
    // is a base class which is called in derived classes "read" method. So if you increment the version
    // and write new stuff, older office versions will read this in the _derived_ classes, which may result
    // in anything from data loss to crash.
    // !!! EOIN !!!
}

//------------------------------------------------------------------------------
void OControlModel::read(const Reference<stario::XObjectInputStream>& InStream) throw (::com::sun::star::io::IOException, RuntimeException)
{
    osl::MutexGuard aGuard(m_aMutex);

    Reference<stario::XMarkableStream> xMark(InStream, UNO_QUERY);
    if ( !xMark.is() )
    {
        throw IOException(
            FRM_RES_STRING( RID_STR_INVALIDSTREAM ),
            static_cast< ::cppu::OWeakObject* >( this )
        );
    }

    // 1. Lesen des UnoControls
    sal_Int32 nLen = InStream->readLong();
    if (nLen)
    {
        sal_Int32 nMark = xMark->createMark();

        Reference<stario::XPersistObject> xPersist;
        if (query_aggregation(m_xAggregate, xPersist))
            xPersist->read(InStream);

        xMark->jumpToMark(nMark);
        InStream->skipBytes(nLen);
        xMark->deleteMark(nMark);
    }

    // 2. Lesen des Versionsnummer
    UINT16 nVersion = InStream->readShort();

    // 3. Lesen der allgemeinen Properties
    ::comphelper::operator>>( InStream, m_aName);
    m_nTabIndex  = InStream->readShort();

    if (nVersion > 0x0002)
        ::comphelper::operator>>( InStream, m_aTag);

    // we had a version where we wrote the help text
    if (nVersion == 0x0004)
        readHelpTextCompatibly(InStream);

    DBG_ASSERT(nVersion < 5, "OControlModel::read : suspicious version number !");
    // 4 was the version where we wrote the help text
    // later versions shouldn't exist (see write for a detailed comment)
}

//------------------------------------------------------------------------------
PropertyState OControlModel::getPropertyStateByHandle( sal_Int32 _nHandle )
{
    Any aDefault = getPropertyDefaultByHandle( _nHandle );
    Any aCurrent;
    getFastPropertyValue( aCurrent, _nHandle );

    if ( ::comphelper::compare( aDefault, aCurrent ) )
        return PropertyState_DEFAULT_VALUE;

    return PropertyState_DIRECT_VALUE;
}

//------------------------------------------------------------------------------
void OControlModel::setPropertyToDefaultByHandle( sal_Int32 _nHandle)
{
    Any aDefault = getPropertyDefaultByHandle( _nHandle );

    Any aConvertedValue, aOldValue;
    if ( convertFastPropertyValue( aConvertedValue, aOldValue, _nHandle, aDefault ) )
    {
        setFastPropertyValue_NoBroadcast( _nHandle, aConvertedValue );
        // TODO: fire the property change
    }
}

//------------------------------------------------------------------------------
Any OControlModel::getPropertyDefaultByHandle( sal_Int32 _nHandle ) const
{
    Any aReturn;
    switch ( _nHandle )
    {
        case PROPERTY_ID_NAME:
        case PROPERTY_ID_TAG:
            aReturn <<= ::rtl::OUString();
            break;

        case PROPERTY_ID_CLASSID:
            aReturn <<= (sal_Int16)FormComponentType::CONTROL;
            break;

        case PROPERTY_ID_TABINDEX:
            aReturn <<= (sal_Int16)FRM_DEFAULT_TABINDEX;
            break;
    }
    return aReturn;
}

//------------------------------------------------------------------------------
void OControlModel::getFastPropertyValue( Any& rValue, sal_Int32 nHandle ) const
{
    switch (nHandle)
    {
        case PROPERTY_ID_NAME:
            rValue <<= m_aName;
            break;
        case PROPERTY_ID_TAG:
            rValue <<= m_aTag;
            break;
        case PROPERTY_ID_CLASSID:
            rValue <<= m_nClassId;
            break;
        case PROPERTY_ID_TABINDEX:
            rValue <<= m_nTabIndex;
            break;
        default:
            OPropertySetAggregationHelper::getFastPropertyValue(rValue, nHandle);
    }
}

//------------------------------------------------------------------------------
sal_Bool OControlModel::convertFastPropertyValue(
                        Any& _rConvertedValue, Any& _rOldValue, sal_Int32 _nHandle, const Any& _rValue)
                        throw (com::sun::star::lang::IllegalArgumentException)
{
    sal_Bool bModified(sal_False);
    switch (_nHandle)
    {
        case PROPERTY_ID_NAME:
            bModified = tryPropertyValue(_rConvertedValue, _rOldValue, _rValue, m_aName);
            break;
        case PROPERTY_ID_TAG:
            bModified = tryPropertyValue(_rConvertedValue, _rOldValue, _rValue, m_aTag);
            break;
        case PROPERTY_ID_TABINDEX:
            bModified = tryPropertyValue(_rConvertedValue, _rOldValue, _rValue, m_nTabIndex);
            break;
    }
    return bModified;
}

//------------------------------------------------------------------------------
void OControlModel::setFastPropertyValue_NoBroadcast(sal_Int32 _nHandle, const Any& _rValue)
                        throw (Exception)
{
    switch (_nHandle)
    {
        case PROPERTY_ID_NAME:
            DBG_ASSERT(_rValue.getValueType() == getCppuType((const ::rtl::OUString*)NULL),
                "OControlModel::setFastPropertyValue_NoBroadcast : invalid type" );
            _rValue >>= m_aName;
            break;
        case PROPERTY_ID_TAG:
            DBG_ASSERT(_rValue.getValueType() == getCppuType((const ::rtl::OUString*)NULL),
                "OControlModel::setFastPropertyValue_NoBroadcast : invalid type" );
            _rValue >>= m_aTag;
            break;
        case PROPERTY_ID_TABINDEX:
            DBG_ASSERT(_rValue.getValueType() == getCppuType((const sal_Int16*)NULL),
                "OControlModel::setFastPropertyValue_NoBroadcast : invalid type" );
            _rValue >>= m_nTabIndex;
            break;
    }
}

//==================================================================
//= OBoundControlModel
//==================================================================
DBG_NAME(frm_OBoundControlModel)
//------------------------------------------------------------------
Any SAL_CALL OBoundControlModel::queryAggregation( const Type& _rType ) throw (RuntimeException)
{
    Any aReturn( OControlModel::queryAggregation(_rType) );
    if (!aReturn.hasValue())
    {
        aReturn = OBoundControlModel_BASE1::queryInterface(_rType);
        if (!aReturn.hasValue() && m_bCommitable)
            aReturn = OBoundControlModel_BASE2::queryInterface(_rType);
    }

    return aReturn;
}

//------------------------------------------------------------------
OBoundControlModel::OBoundControlModel(
        const Reference<com::sun::star::lang::XMultiServiceFactory>& _rxFactory,
        const ::rtl::OUString& _rUnoControlModelTypeName,
        const ::rtl::OUString& _rDefault,
        const sal_Bool _bCommitable,
        const sal_Bool _bSetDelegator)
    :OControlModel(_rxFactory, _rUnoControlModelTypeName, _rDefault, _bSetDelegator)
    ,m_aUpdateListeners(m_aMutex)
    ,m_aResetListeners(m_aMutex)
    ,m_aLabelServiceName(FRM_SUN_COMPONENT_FIXEDTEXT)
    ,m_bLoaded(sal_False)
    ,m_bRequired(sal_False)
    ,m_bCommitable(_bCommitable)
    ,m_bForwardValueChanges(sal_True)
    ,m_bResetting(sal_False)
{
    DBG_CTOR(frm_OBoundControlModel, NULL);
}

//------------------------------------------------------------------
OBoundControlModel::OBoundControlModel(
        const OBoundControlModel* _pOriginal, const Reference< XMultiServiceFactory>& _rxFactory,
        const sal_Bool _bCommitable, const sal_Bool _bSetDelegator )
    :OControlModel( _pOriginal, _rxFactory, _bSetDelegator )
    ,m_aUpdateListeners( m_aMutex )
    ,m_aResetListeners( m_aMutex )
    ,m_bLoaded( sal_False )
    ,m_bRequired( sal_False )
    ,m_bCommitable( _bCommitable )
    ,m_bForwardValueChanges( sal_True )
    ,m_bResetting( sal_False )
{
    DBG_CTOR(frm_OBoundControlModel, NULL);

    m_aLabelServiceName = _pOriginal->m_aLabelServiceName;
    m_sDataFieldConnectivityProperty = _pOriginal->m_sDataFieldConnectivityProperty;
    m_aControlSource = _pOriginal->m_aControlSource;
    // m_xLabelControl, though bneing a property, is not to be cloned, not even the reference will be transfered.
    // (the former should be clear - a clone of the object we're only referencing does not make sense)
    // (the second would violate the restriction for label controls that they're part of the
    // same form component hierarchy - we ourself are no part, yet, so we can't have a label control)
    m_bCommitable = _pOriginal->m_bCommitable;
}

//------------------------------------------------------------------
OBoundControlModel::~OBoundControlModel()
{
    DBG_DTOR(frm_OBoundControlModel, NULL);
}

//-----------------------------------------------------------------------------
Sequence<Type> OBoundControlModel::_getTypes()
{
    if (m_bCommitable)
        return concatSequences(OControlModel::_getTypes(),OBoundControlModel_BASE1::getTypes(),OBoundControlModel_BASE2::getTypes());

    return concatSequences(OControlModel::_getTypes(),OBoundControlModel_BASE1::getTypes());
}

// OComponentHelper
//-----------------------------------------------------------------------------
void OBoundControlModel::disposing()
{
    OControlModel::disposing();

    osl::MutexGuard aGuard(m_aMutex);
    com::sun::star::lang::EventObject aEvt(static_cast<XWeak*>(this));
    m_aResetListeners.disposeAndClear(aEvt);
    m_aUpdateListeners.disposeAndClear(aEvt);

    if (m_xField.is())
    {
        m_xField->removePropertyChangeListener(PROPERTY_VALUE, this);
        resetField();
    }
    m_xCursor = NULL;

    Reference<com::sun::star::lang::XComponent> xComp(m_xLabelControl, UNO_QUERY);
    if (xComp.is())
        xComp->removeEventListener(static_cast<com::sun::star::lang::XEventListener*>(static_cast<XPropertyChangeListener*>(this)));
}

// XChild
//------------------------------------------------------------------------------
void SAL_CALL OBoundControlModel::setParent(const Reference<XInterface>& _rxParent) throw(com::sun::star::lang::NoSupportException, RuntimeException)
{
    osl::MutexGuard aGuard(m_aMutex);

    // log off old listeners
    Reference< XLoadable > xLoadable( m_xParent, UNO_QUERY );
    if ( xLoadable.is() )
        xLoadable->removeLoadListener( this );

    // log on new listeners
    {
        xLoadable = xLoadable.query( _rxParent );
        RTL_LOGFILE_CONTEXT( aLogger, "forms::OBoundControlModel::setParent::logOnLoadListener" );
        if ( xLoadable.is() )
            xLoadable->addLoadListener( this );
    }

    OControlModel::setParent(_rxParent);
}

// XEventListener
//------------------------------------------------------------------------------
void SAL_CALL OBoundControlModel::disposing(const com::sun::star::lang::EventObject& _rEvent) throw (RuntimeException)
{
    osl::MutexGuard aGuard(m_aMutex);
    if (m_xField == _rEvent.Source)
    {
        resetField();
    }
    else if (m_xLabelControl == _rEvent.Source)
    {
        Reference<XPropertySet> xOldValue = m_xLabelControl;
        m_xLabelControl = NULL;

        // fire a property change event
                Any aOldValue; aOldValue <<= xOldValue;
                Any aNewValue; aNewValue <<= m_xLabelControl;
        sal_Int32 nHandle = PROPERTY_ID_CONTROLLABEL;
        OPropertySetHelper::fire(&nHandle, &aNewValue, &aOldValue, 1, sal_False);
    }
    else
        OControlModel::disposing(_rEvent);
}

// XServiceInfo
//------------------------------------------------------------------------------
StringSequence SAL_CALL OBoundControlModel::getSupportedServiceNames() throw(RuntimeException)
{
    StringSequence aSupported = OControlModel::getSupportedServiceNames();
    aSupported.realloc(aSupported.getLength() + 1);

    ::rtl::OUString* pArray = aSupported.getArray();
    pArray[aSupported.getLength()-1] = ::rtl::OUString( RTL_CONSTASCII_USTRINGPARAM( "com.sun.star.form.DataAwareControlModel" ));
    return aSupported;
}


// XPersist
//------------------------------------------------------------------------------
void SAL_CALL OBoundControlModel::write( const Reference<stario::XObjectOutputStream>& _rxOutStream ) throw(stario::IOException, RuntimeException)
{
    OControlModel::write(_rxOutStream);

    osl::MutexGuard aGuard(m_aMutex);

    // Version
    _rxOutStream->writeShort(0x0002);

    // Controlsource
    ::comphelper::operator<<( _rxOutStream, m_aControlSource);

    // !!! IMPORTANT NOTE !!!
    // don't write any new members here : this wouldn't be compatible with older versions, as OBoundControlModel
    // is a base class which is called in derived classes "read" method. So if you increment the version
    // and write new stuff, older office versions will read this in the _derived_ classes, which may result
    // in anything from data loss to crash.
    // (use writeCommonProperties instead, this is called in derived classes write-method)
    // !!! EOIN !!!
}

//------------------------------------------------------------------------------
void OBoundControlModel::defaultCommonProperties()
{
    Reference<com::sun::star::lang::XComponent> xComp(m_xLabelControl, UNO_QUERY);
    if (xComp.is())
        xComp->removeEventListener(static_cast<com::sun::star::lang::XEventListener*>(static_cast<XPropertyChangeListener*>(this)));
    m_xLabelControl = NULL;
}

//------------------------------------------------------------------------------
void OBoundControlModel::readCommonProperties(const Reference<stario::XObjectInputStream>& _rxInStream)
{
    sal_Int32 nLen = _rxInStream->readLong();

        Reference<stario::XMarkableStream> xMark(_rxInStream, UNO_QUERY);
    DBG_ASSERT(xMark.is(), "OBoundControlModel::readCommonProperties : can only work with markable streams !");
    sal_Int32 nMark = xMark->createMark();

    // read the reference to the label control
        Reference<stario::XPersistObject> xPersist;
    sal_Int32 nUsedFlag;
    nUsedFlag = _rxInStream->readLong();
    if (nUsedFlag)
        xPersist = _rxInStream->readObject();
        m_xLabelControl = Reference<XPropertySet>(xPersist, UNO_QUERY);
        Reference<com::sun::star::lang::XComponent> xComp(m_xLabelControl, UNO_QUERY);
    if (xComp.is())
                xComp->addEventListener(static_cast<com::sun::star::lang::XEventListener*>(static_cast<XPropertyChangeListener*>(this)));

    // read any other new common properties here

    // skip the remaining bytes
    xMark->jumpToMark(nMark);
    _rxInStream->skipBytes(nLen);
    xMark->deleteMark(nMark);
}

//------------------------------------------------------------------------------
void OBoundControlModel::writeCommonProperties(const Reference<stario::XObjectOutputStream>& _rxOutStream)
{
        Reference<stario::XMarkableStream> xMark(_rxOutStream, UNO_QUERY);
    DBG_ASSERT(xMark.is(), "OBoundControlModel::writeCommonProperties : can only work with markable streams !");
    sal_Int32 nMark = xMark->createMark();

    // a placeholder where we will write the overall length (later in this method)
    sal_Int32 nLen = 0;
    _rxOutStream->writeLong(nLen);

    // write the reference to the label control
    Reference<stario::XPersistObject> xPersist(m_xLabelControl, UNO_QUERY);
    sal_Int32 nUsedFlag = 0;
    if (xPersist.is())
        nUsedFlag = 1;
    _rxOutStream->writeLong(nUsedFlag);
    if (xPersist.is())
        _rxOutStream->writeObject(xPersist);

    // write any other new common properties here

    // write the correct length at the beginning of the block
    nLen = xMark->offsetToMark(nMark) - sizeof(nLen);
    xMark->jumpToMark(nMark);
    _rxOutStream->writeLong(nLen);
    xMark->jumpToFurthest();
    xMark->deleteMark(nMark);
}

//------------------------------------------------------------------------------
void SAL_CALL OBoundControlModel::read( const Reference< stario::XObjectInputStream >& _rxInStream ) throw(stario::IOException, RuntimeException)
{
    OControlModel::read(_rxInStream);

    osl::MutexGuard aGuard(m_aMutex);
    /*UINT16 nVersion =*/ _rxInStream->readShort();
    ::comphelper::operator>>( _rxInStream, m_aControlSource);
}

//------------------------------------------------------------------------------
void OBoundControlModel::getFastPropertyValue(Any& rValue, sal_Int32 nHandle) const
{
    switch (nHandle)
    {
        case PROPERTY_ID_CONTROLSOURCEPROPERTY:
            rValue <<= m_sDataFieldConnectivityProperty;
            break;
        case PROPERTY_ID_CONTROLSOURCE:
            rValue <<= m_aControlSource;
            break;
        case PROPERTY_ID_BOUNDFIELD:
            rValue <<= m_xField;
            break;
        case PROPERTY_ID_CONTROLLABEL:
            if (!m_xLabelControl.is())
                rValue.clear();
            else
                rValue <<= m_xLabelControl;
            break;
        default:
            OControlModel::getFastPropertyValue(rValue, nHandle);
    }
}

//------------------------------------------------------------------------------
sal_Bool OBoundControlModel::convertFastPropertyValue(
                                Any& _rConvertedValue, Any& _rOldValue,
                sal_Int32 _nHandle,
                                const Any& _rValue)
                throw (com::sun::star::lang::IllegalArgumentException)
{
    sal_Bool bModified(sal_False);
    switch (_nHandle)
    {
        case PROPERTY_ID_CONTROLSOURCE:
            bModified = tryPropertyValue(_rConvertedValue, _rOldValue, _rValue, m_aControlSource);
            break;
        case PROPERTY_ID_BOUNDFIELD:
            bModified = tryPropertyValue(_rConvertedValue, _rOldValue, _rValue, m_xField);
            break;
        case PROPERTY_ID_CONTROLLABEL:
            if (!_rValue.hasValue())
            {	// property set to void
                _rConvertedValue = Any();
                getFastPropertyValue(_rOldValue, _nHandle);
                bModified = m_xLabelControl.is();
            }
            else
            {
                bModified = tryPropertyValue(_rConvertedValue, _rOldValue, _rValue, m_xLabelControl);
                if (!m_xLabelControl.is())
                    // an empty interface is interpreted as VOID
                    _rOldValue.clear();
            }
            break;
        default:
            bModified = OControlModel::convertFastPropertyValue(_rConvertedValue, _rOldValue, _nHandle, _rValue);
    }
    return bModified;
}

//------------------------------------------------------------------------------
void OBoundControlModel::setFastPropertyValue_NoBroadcast( sal_Int32 nHandle, const Any& rValue ) throw (Exception)
{
    switch (nHandle)
    {
        case PROPERTY_ID_CONTROLSOURCE:
            DBG_ASSERT(rValue.getValueType().getTypeClass() == TypeClass_STRING, "invalid type" );
            rValue >>= m_aControlSource;
            break;
        case PROPERTY_ID_BOUNDFIELD:
            OSL_FAIL("OBoundControlModel::setFastPropertyValue_NoBroadcast : BoundField should be a read-only property !");
                throw com::sun::star::lang::IllegalArgumentException();
            break;
        case PROPERTY_ID_CONTROLLABEL:
        {
            DBG_ASSERT(!rValue.hasValue() || (rValue.getValueType().getTypeClass() == TypeClass_INTERFACE),
                "OBoundControlModel::setFastPropertyValue_NoBroadcast : invalid argument !");
            if (!rValue.hasValue())
            {	// set property to "void"
                Reference<com::sun::star::lang::XComponent> xComp(m_xLabelControl, UNO_QUERY);
                if (xComp.is())
                    xComp->removeEventListener(static_cast<com::sun::star::lang::XEventListener*>(static_cast<XPropertyChangeListener*>(this)));
                m_xLabelControl = NULL;
                break;
            }

            InterfaceRef xNewValue;
            rValue >>= xNewValue;

            Reference<XControlModel> xAsModel(xNewValue, UNO_QUERY);
            Reference<com::sun::star::lang::XServiceInfo> xAsServiceInfo(xNewValue, UNO_QUERY);
            Reference<XPropertySet> xAsPropSet(xNewValue, UNO_QUERY);
            Reference<XChild> xAsChild(xNewValue, UNO_QUERY);
            if (!xAsModel.is() || !xAsServiceInfo.is() || !xAsPropSet.is() || !xAsChild.is())
            {
                throw com::sun::star::lang::IllegalArgumentException();
            }

            if (!xAsServiceInfo->supportsService(m_aLabelServiceName))
            {
                throw com::sun::star::lang::IllegalArgumentException();
            }

            // check if weself and the given model have a common anchestor (up to the forms collection)
            Reference<XChild> xCont;
            query_interface(static_cast<XWeak*>(this), xCont);
            InterfaceRef xMyTopLevel = xCont->getParent();
            while (xMyTopLevel.is())
            {
                Reference<XForm> xAsForm(xMyTopLevel, UNO_QUERY);
                if (!xAsForm.is())
                    // found my root
                    break;

                Reference<XChild> xLclAsChild(xMyTopLevel, UNO_QUERY);
                xMyTopLevel = xLclAsChild.is() ? xLclAsChild->getParent() : InterfaceRef();
            }
            InterfaceRef xNewTopLevel = xAsChild->getParent();
            while (xNewTopLevel.is())
            {
                Reference<XForm> xAsForm(xNewTopLevel, UNO_QUERY);
                if (!xAsForm.is())
                    break;

                Reference<XChild> xLclAsChild(xNewTopLevel, UNO_QUERY);
                xNewTopLevel = xLclAsChild.is() ? xLclAsChild->getParent() : InterfaceRef();
            }
            if (xNewTopLevel != xMyTopLevel)
            {
                // the both objects don't belong to the same forms collection -> not acceptable
                throw com::sun::star::lang::IllegalArgumentException();
            }

            m_xLabelControl = xAsPropSet;
            Reference<com::sun::star::lang::XComponent> xComp(m_xLabelControl, UNO_QUERY);
            if (xComp.is())
                xComp->addEventListener(static_cast<com::sun::star::lang::XEventListener*>(static_cast<XPropertyChangeListener*>(this)));
        }
        break;
        default:
            OControlModel::setFastPropertyValue_NoBroadcast(nHandle, rValue );
    }
}

// XPropertyChangeListener
//------------------------------------------------------------------------------
void SAL_CALL OBoundControlModel::propertyChange( const PropertyChangeEvent& evt ) throw(RuntimeException)
{
    // Bei Wertaenderung neu initialisieren
    if (evt.PropertyName.equals(PROPERTY_VALUE))
    {
        osl::MutexGuard aGuard(m_aMutex);
//		if (m_bForwardValueChanges && m_xColumn.is())
//			_onValueChanged();
    }
}

// XBoundComponent
//------------------------------------------------------------------------------
void SAL_CALL OBoundControlModel::addUpdateListener(const Reference<XUpdateListener>& _rxListener) throw(RuntimeException)
{
    m_aUpdateListeners.addInterface(_rxListener);
}

//------------------------------------------------------------------------------
void SAL_CALL OBoundControlModel::removeUpdateListener(const Reference< XUpdateListener>& _rxListener) throw(RuntimeException)
{
    m_aUpdateListeners.removeInterface(_rxListener);
}

//------------------------------------------------------------------------------
sal_Bool SAL_CALL OBoundControlModel::commit() throw(RuntimeException)
{
    DBG_ASSERT(m_bCommitable, "OBoundControlModel::commit : invalid call (I'm not commitable !) ");
    {
        osl::MutexGuard aGuard(m_aMutex);
        if (!m_xField.is())
            return sal_True;
    }

    cppu::OInterfaceIteratorHelper aIter(m_aUpdateListeners);
    com::sun::star::lang::EventObject aEvt;
    aEvt.Source = static_cast<XWeak*>(this);
    sal_Bool bSucceed = sal_True;
    while (aIter.hasMoreElements() && bSucceed)
        bSucceed = ((XUpdateListener*)aIter.next())->approveUpdate(aEvt);

    if (bSucceed)
    {
        osl::MutexGuard aGuard(m_aMutex);
//		try
//		{
//			bSucceed = _commit();
//		}
//		catch(Exception&)
//		{
//			bSucceed = sal_False;
//		}
    }

    if (bSucceed)
    {
        cppu::OInterfaceIteratorHelper aLclIter(m_aUpdateListeners);
        while (aLclIter.hasMoreElements())
            ((XUpdateListener*)aLclIter.next())->updated(aEvt);
    }

    return bSucceed;
}

//------------------------------------------------------------------------------
sal_Bool OBoundControlModel::_approve(sal_Int32 _nColumnType)
{
    if ((_nColumnType == DataType::BINARY) || (_nColumnType == DataType::VARBINARY)
        || (_nColumnType == DataType::LONGVARBINARY) || (_nColumnType == DataType::OTHER)
        || (_nColumnType == DataType::OBJECT) || (_nColumnType == DataType::DISTINCT)
        || (_nColumnType == DataType::STRUCT) || (_nColumnType == DataType::ARRAY)
        || (_nColumnType == DataType::BLOB) || (_nColumnType == DataType::CLOB)
        || (_nColumnType == DataType::REF) || (_nColumnType == DataType::SQLNULL))
        return sal_False;

    return sal_True;
}

// XLoadListener
//------------------------------------------------------------------------------
void SAL_CALL OBoundControlModel::loaded(const com::sun::star::lang::EventObject& /*rEvent*/) throw(RuntimeException)
{
    OSL_ENSURE( false, "OBoundControlModel::loaded: dead code!?" );
}


//------------------------------------------------------------------------------
void SAL_CALL OBoundControlModel::unloaded( const com::sun::star::lang::EventObject& ) throw(RuntimeException)
{
}

//------------------------------------------------------------------------------
void SAL_CALL OBoundControlModel::reloading( const com::sun::star::lang::EventObject& ) throw(RuntimeException)
{
    osl::MutexGuard aGuard(m_aMutex);
    m_bForwardValueChanges = sal_False;
}

//------------------------------------------------------------------------------
void SAL_CALL OBoundControlModel::unloading(const com::sun::star::lang::EventObject& ) throw(RuntimeException)
{
    osl::MutexGuard aGuard(m_aMutex);

    if (m_xField.is())
    {
        m_xField->removePropertyChangeListener(PROPERTY_VALUE, this);
        resetField();
    }
    m_xCursor = NULL;
    m_bLoaded = sal_False;
}

//------------------------------------------------------------------------------
void SAL_CALL OBoundControlModel::reloaded(const com::sun::star::lang::EventObject& /*rEvent*/) throw(RuntimeException)
{
    OSL_ENSURE( false, "OBoundControlModel::reloaded: dead code!?" );
}

//-----------------------------------------------------------------------------
void OBoundControlModel::addResetListener(const Reference<XResetListener>& l) throw (RuntimeException)
{
    m_aResetListeners.addInterface(l);
}

//-----------------------------------------------------------------------------
void OBoundControlModel::removeResetListener(const Reference<XResetListener>& l) throw (RuntimeException)
{
    m_aResetListeners.removeInterface(l);
}

//-----------------------------------------------------------------------------
void OBoundControlModel::reset() throw (RuntimeException)
{
    OSL_ENSURE( false, "OBoundControlModel::reset: dead code!?" );
}
// -----------------------------------------------------------------------------
void OBoundControlModel::setField( const Reference< XPropertySet>& _rxField,sal_Bool _bFire)
{
    // fire a property change event
    if ( m_xField != _rxField )
    {
        Any aOldValue; aOldValue <<= m_xField;
        m_xField = _rxField;
        if ( _bFire )
        {
            Any aNewValue; aNewValue <<= _rxField;
            sal_Int32 nHandle = PROPERTY_ID_BOUNDFIELD;
            OPropertySetHelper::fire(&nHandle, &aNewValue, &aOldValue, 1, sal_False);
        }
    }
}
// -----------------------------------------------------------------------------

//.........................................................................
}
//... namespace frm .......................................................

}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
