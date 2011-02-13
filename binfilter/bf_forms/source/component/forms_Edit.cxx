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

#include <comphelper/proparrhlp.hxx>

#include <com/sun/star/util/XNumberFormatter.hpp>

#include <com/sun/star/awt/XFocusListener.hpp>

#include <com/sun/star/awt/XKeyListener.hpp>

#include <com/sun/star/form/XChangeBroadcaster.hpp>




#include <tools/link.hxx>

#include "Edit.hxx"


#include <com/sun/star/awt/XWindow.hpp>
#include <com/sun/star/container/XIndexAccess.hpp>
#include <com/sun/star/form/XSubmit.hpp>
#include <com/sun/star/util/NumberFormat.hpp>

#include <vcl/svapp.hxx>

#include <comphelper/container.hxx>
#include <comphelper/numbers.hxx>

#include <connectivity/dbtools.hxx>
#include <connectivity/dbconversion.hxx>

#include "services.hxx"

#include <comphelper/property.hxx>

#include <com/sun/star/form/FormComponentType.hpp>

#include <com/sun/star/beans/PropertyAttribute.hpp>

namespace binfilter {

    using namespace ::dbtools;

//.........................................................................
namespace frm
{
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

//------------------------------------------------------------------
InterfaceRef SAL_CALL OEditControl_CreateInstance(const Reference< XMultiServiceFactory > & _rxFactory)
{
    return *(new OEditControl(_rxFactory));
}

//------------------------------------------------------------------------------
Sequence<Type> OEditControl::_getTypes()
{
    static Sequence<Type> aTypes;
    if (!aTypes.getLength())
    {
        // my two base classes
        aTypes = concatSequences(OBoundControl::_getTypes(), OEditControl_BASE::getTypes());
    }
    return aTypes;
}

//------------------------------------------------------------------------------
Any SAL_CALL OEditControl::queryAggregation(const Type& _rType) throw (RuntimeException)
{
    Any aReturn = OBoundControl::queryAggregation(_rType);
    if (!aReturn.hasValue())
        aReturn = OEditControl_BASE::queryInterface(_rType);

    return aReturn;
}

DBG_NAME(OEditControl)
//------------------------------------------------------------------------------
OEditControl::OEditControl(const Reference<XMultiServiceFactory>& _rxFactory)
               :OBoundControl(_rxFactory, VCL_CONTROL_EDIT)
               ,m_aChangeListeners(m_aMutex)
               ,m_nKeyEvent( 0 )
{
    DBG_CTOR(OEditControl,NULL);

    increment(m_refCount);
    {	// als FocusListener anmelden
        Reference<XWindow>  xComp;
        if (query_aggregation(m_xAggregate, xComp))
        {
            xComp->addFocusListener(this);
            xComp->addKeyListener(this);
        }
    }
    // Refcount wieder bei 2 fuer beide Listener
    /*sal_Int32 n =*/ decrement(m_refCount);
}

//------------------------------------------------------------------------------
OEditControl::~OEditControl()
{
    if( m_nKeyEvent )
        Application::RemoveUserEvent( m_nKeyEvent );

    if (!OComponentHelper::rBHelper.bDisposed)
    {
        acquire();
        dispose();
    }

    DBG_DTOR(OEditControl,NULL);
}

// XChangeBroadcaster
//------------------------------------------------------------------------------
void OEditControl::addChangeListener(const Reference<XChangeListener>& l) throw ( ::com::sun::star::uno::RuntimeException)
{
    m_aChangeListeners.addInterface( l );
}

//------------------------------------------------------------------------------
void OEditControl::removeChangeListener(const Reference<XChangeListener>& l) throw ( ::com::sun::star::uno::RuntimeException)
{
    m_aChangeListeners.removeInterface( l );
}

// OComponentHelper
//------------------------------------------------------------------------------
void OEditControl::disposing()
{
    OBoundControl::disposing();

    EventObject aEvt(static_cast<XWeak*>(this));
    m_aChangeListeners.disposeAndClear(aEvt);
}

// XServiceInfo
//------------------------------------------------------------------------------
StringSequence	OEditControl::getSupportedServiceNames() throw()
{
    StringSequence aSupported = OBoundControl::getSupportedServiceNames();
    aSupported.realloc(aSupported.getLength() + 1);

    ::rtl::OUString*pArray = aSupported.getArray();
    pArray[aSupported.getLength()-1] = FRM_SUN_CONTROL_TEXTFIELD;
    return aSupported;
}

// XEventListener
//------------------------------------------------------------------------------
void OEditControl::disposing(const EventObject& Source) throw( RuntimeException )
{
    OBoundControl::disposing(Source);
}

// XFocusListener
//------------------------------------------------------------------------------
void OEditControl::focusGained( const FocusEvent& /*e*/ ) throw ( ::com::sun::star::uno::RuntimeException)
{
    Reference<XPropertySet>  xSet(getModel(), UNO_QUERY);
    if (xSet.is())
        xSet->getPropertyValue( PROPERTY_TEXT ) >>= m_aHtmlChangeValue;
}

//------------------------------------------------------------------------------
void OEditControl::focusLost( const FocusEvent& /*e*/ ) throw ( ::com::sun::star::uno::RuntimeException)
{
    Reference<XPropertySet>  xSet(getModel(), UNO_QUERY);
    if (xSet.is())
    {
        ::rtl::OUString sNewHtmlChangeValue;
        xSet->getPropertyValue( PROPERTY_TEXT ) >>= sNewHtmlChangeValue;
        if( sNewHtmlChangeValue != m_aHtmlChangeValue )
        {
            EventObject aEvt;
            aEvt.Source = *this;
            m_aChangeListeners.notifyEach(&XChangeListener::changed, aEvt);
        }
    }
}

// XKeyListener
//------------------------------------------------------------------------------
void OEditControl::keyPressed(const ::com::sun::star::awt::KeyEvent& e) throw ( ::com::sun::star::uno::RuntimeException)
{
    if( e.KeyCode != KEY_RETURN || e.Modifiers != 0 )
        return;

    // Steht das Control in einem Formular mit einer Submit-URL?
    Reference<XPropertySet>  xSet(getModel(), UNO_QUERY);
    if( !xSet.is() )
        return;

    // nicht fuer multiline edits
    Any aTmp( xSet->getPropertyValue(PROPERTY_MULTILINE));
    if ((aTmp.getValueType().equals(::getBooleanCppuType())) && getBOOL(aTmp))
        return;

    Reference<XFormComponent>  xFComp(xSet, UNO_QUERY);
    InterfaceRef  xParent = xFComp->getParent();
    if( !xParent.is() )
        return;

    Reference<XPropertySet>  xFormSet(xParent, UNO_QUERY);
    if( !xFormSet.is() )
        return;

    aTmp = xFormSet->getPropertyValue( PROPERTY_TARGET_URL );
    if (!aTmp.getValueType().equals(::getCppuType((const ::rtl::OUString*)NULL)) ||
        !getString(aTmp).getLength() )
        return;

    Reference<XIndexAccess>  xElements(xParent, UNO_QUERY);
    sal_Int32 nCount = xElements->getCount();
    if( nCount > 1 )
    {
        Reference<XPropertySet>  xFCSet;
        for( sal_Int32 nIndex=0; nIndex < nCount; nIndex++ )
        {
            //	Any aElement(xElements->getByIndex(nIndex));
            xElements->getByIndex(nIndex) >>= xFCSet;
            OSL_ENSURE(xFCSet.is(),"OEditControl::keyPressed: No XPropertySet!");

            if (hasProperty(PROPERTY_CLASSID, xFCSet) &&
                getINT16(xFCSet->getPropertyValue(PROPERTY_CLASSID)) == FormComponentType::TEXTFIELD)
            {
                // Noch ein weiteres Edit gefunden ==> dann nicht submitten
                if (xFCSet != xSet)
                    return;
            }
        }
    }

    // Da wir noch im Haender stehen, submit asynchron ausloesen
    if( m_nKeyEvent )
        Application::RemoveUserEvent( m_nKeyEvent );
    m_nKeyEvent = Application::PostUserEvent( LINK(this, OEditControl,OnKeyPressed) );
}

//------------------------------------------------------------------------------
void OEditControl::keyReleased(const ::com::sun::star::awt::KeyEvent& /*e*/) throw ( ::com::sun::star::uno::RuntimeException)
{
}

//------------------------------------------------------------------------------
IMPL_LINK(OEditControl, OnKeyPressed, void*, EMPTYARG)
{
    m_nKeyEvent = 0;

    Reference<XFormComponent>  xFComp(getModel(), UNO_QUERY);
    InterfaceRef  xParent = xFComp->getParent();
    Reference<XSubmit>  xSubmit(xParent, UNO_QUERY);
    if (xSubmit.is())
        xSubmit->submit( Reference<XControl>(), ::com::sun::star::awt::MouseEvent() );
    return 0L;
}

/*************************************************************************/
sal_Int32 OEditModel::nTextHandle = -1;

//------------------------------------------------------------------
InterfaceRef SAL_CALL OEditModel_CreateInstance(const Reference<XMultiServiceFactory>& _rxFactory)
{
    return *(new OEditModel(_rxFactory));
}

//------------------------------------------------------------------------------
Sequence<Type> OEditModel::_getTypes()
{
    return OEditBaseModel::_getTypes();
}


DBG_NAME(OEditModel)
//------------------------------------------------------------------
OEditModel::OEditModel(const Reference<XMultiServiceFactory>& _rxFactory)
             :OEditBaseModel( _rxFactory, VCL_CONTROLMODEL_EDIT, FRM_CONTROL_EDIT )
                                    // use the old control name for compytibility reasons
    ,m_nFormatKey(0)
    ,m_aNullDate(DBTypeConversion::getStandardDate())
    ,m_nFieldType(DataType::OTHER)
    ,m_nKeyType(NumberFormat::UNDEFINED)
    ,m_bMaxTextLenModified(sal_False)
    ,m_bWritingFormattedFake(sal_False)
    ,m_bNumericField(sal_False)
{
    DBG_CTOR(OEditModel,NULL);

    m_nClassId = FormComponentType::TEXTFIELD;
    m_sDataFieldConnectivityProperty = PROPERTY_TEXT;
    if (OEditModel::nTextHandle == -1)
        OEditModel::nTextHandle = getOriginalHandle(PROPERTY_ID_TEXT);
}

//------------------------------------------------------------------
OEditModel::OEditModel( const OEditModel* _pOriginal, const Reference<XMultiServiceFactory>& _rxFactory )
        :OEditBaseModel( _pOriginal, _rxFactory )
    ,m_nFormatKey(0)
    ,m_aNullDate(DBTypeConversion::getStandardDate())
    ,m_nFieldType(DataType::OTHER)
    ,m_nKeyType(NumberFormat::UNDEFINED)
    ,m_bMaxTextLenModified(sal_False)
    ,m_bWritingFormattedFake(sal_False)
    ,m_bNumericField(sal_False)
{
    DBG_CTOR( OEditModel, NULL );

    // Note that most of the properties are not clone from the original object:
    // Things as the format key, it's type, and such, depend on the field being part of a loaded form
    // (they're initialized in _loaded). Even if the original object _is_ part of such a form, we ourself
    // certainly aren't, so these members are defaulted. If we're inserted into a form which is already loaded,
    // they will be set to new values, anyway ....
}

//------------------------------------------------------------------
OEditModel::~OEditModel()
{
    if (!OComponentHelper::rBHelper.bDisposed)
    {
        acquire();
        dispose();
    }

    DBG_DTOR(OEditModel,NULL);
}

//------------------------------------------------------------------------------
IMPLEMENT_DEFAULT_CLONING( OEditModel )

//------------------------------------------------------------------------------
void OEditModel::disposing()
{
    OEditBaseModel::disposing();
    m_xFormatter = NULL;
}

// XPersistObject
//------------------------------------------------------------------------------
::rtl::OUString SAL_CALL OEditModel::getServiceName() throw ( ::com::sun::star::uno::RuntimeException)
{
    return FRM_COMPONENT_EDIT;	// old (non-sun) name for compatibility !
}

// XServiceInfo
//------------------------------------------------------------------------------
StringSequence SAL_CALL OEditModel::getSupportedServiceNames() throw()
{
    StringSequence aSupported = OBoundControlModel::getSupportedServiceNames();
    aSupported.realloc(aSupported.getLength() + 2);

    ::rtl::OUString*pArray = aSupported.getArray();
    pArray[aSupported.getLength()-1] = FRM_SUN_COMPONENT_DATABASE_TEXTFIELD;
    pArray[aSupported.getLength()-2] = FRM_SUN_COMPONENT_TEXTFIELD;
    return aSupported;
}

// XPropertySet
//------------------------------------------------------------------------------
Reference<XPropertySetInfo> SAL_CALL OEditModel::getPropertySetInfo() throw(RuntimeException)
{
    Reference<XPropertySetInfo>  xInfo( createPropertySetInfo( getInfoHelper() ) );
    return xInfo;
}
// -----------------------------------------------------------------------------
void SAL_CALL OEditModel::getFastPropertyValue(Any& rValue, sal_Int32 nHandle ) const
{
    if ( PROPERTY_ID_PERSISTENCE_MAXTEXTLENGTH == nHandle )
    {
        if ( m_bMaxTextLenModified )
            rValue <<= sal_Int16(0);
        else if ( m_xAggregateSet.is() )
            rValue = m_xAggregateSet->getPropertyValue(PROPERTY_MAXTEXTLEN);
    }
    else
    {
        OEditBaseModel::getFastPropertyValue(rValue, nHandle );
    }
}

//------------------------------------------------------------------------------
void OEditModel::fillProperties(
        Sequence< Property >& _rProps,
        Sequence< Property >& _rAggregateProps ) const
{
    FRM_BEGIN_PROP_HELPER(12)
        // Text auf transient setzen
//		ModifyPropertyAttributes(_rAggregateProps, PROPERTY_TEXT, PropertyAttribute::TRANSIENT, 0);

        DECL_PROP1(NAME,				::rtl::OUString,		BOUND);
        DECL_PROP2(CLASSID,				sal_Int16,				READONLY, TRANSIENT);
        DECL_PROP2(PERSISTENCE_MAXTEXTLENGTH,sal_Int16,			READONLY, TRANSIENT);
        DECL_PROP2(DEFAULT_TEXT,		::rtl::OUString,		BOUND, MAYBEDEFAULT);
        DECL_BOOL_PROP1(EMPTY_IS_NULL,							BOUND);
        DECL_PROP1(TAG,					::rtl::OUString,		BOUND);
        DECL_PROP1(TABINDEX,			sal_Int16,				BOUND);
        DECL_PROP1(CONTROLSOURCE,		::rtl::OUString,		BOUND);
        DECL_IFACE_PROP3(BOUNDFIELD,	XPropertySet,			BOUND,READONLY, TRANSIENT);
        DECL_BOOL_PROP2(FILTERPROPOSAL,							BOUND, MAYBEDEFAULT);
        DECL_IFACE_PROP2(CONTROLLABEL,	XPropertySet,			BOUND, MAYBEVOID);
        DECL_PROP2(CONTROLSOURCEPROPERTY,	rtl::OUString,		READONLY, TRANSIENT);
    FRM_END_PROP_HELPER();
}

//------------------------------------------------------------------------------
::cppu::IPropertyArrayHelper& OEditModel::getInfoHelper()
{
    return *const_cast<OEditModel*>(this)->getArrayHelper();
}

//------------------------------------------------------------------------------
void OEditModel::write(const Reference<XObjectOutputStream>& _rxOutStream) throw ( ::com::sun::star::io::IOException, ::com::sun::star::uno::RuntimeException)
{
    Any aCurrentText;
    sal_Int16 nOldTextLen = 0;
    // bin ich gerade loaded und habe dazu zeitweilig die MaxTextLen umgesetzt ?
    if ( m_bMaxTextLenModified )
    {	// -> fuer die Dauer des Speicherns meinem aggregierten Model die alte TextLen einreden

        // before doing this we have to save the current text value of the aggregate, as this may be affected by resetting the text len
        aCurrentText = m_xAggregateSet->getPropertyValue(PROPERTY_TEXT);

        m_xAggregateSet->getPropertyValue(PROPERTY_MAXTEXTLEN) >>= nOldTextLen;
        m_xAggregateSet->setPropertyValue(PROPERTY_MAXTEXTLEN, makeAny((sal_Int16)0));
    }

    OEditBaseModel::write(_rxOutStream);

    if ( m_bMaxTextLenModified )
    {	// wieder zuruecksetzen
        m_xAggregateSet->setPropertyValue(PROPERTY_MAXTEXTLEN, makeAny(nOldTextLen));
        // and reset the text
        // First we set it to an empty string : Without this the second setPropertyValue would not do anything as it thinks
        // we aren't changing the prop (it didn't notify the - implicite - change of the text prop while setting the max text len)
        // This seems to be a bug with in toolkit's EditControl-implementation.
        m_xAggregateSet->setPropertyValue(PROPERTY_TEXT, makeAny(::rtl::OUString()));
        m_xAggregateSet->setPropertyValue(PROPERTY_TEXT, aCurrentText);
    }
}

//------------------------------------------------------------------------------
void OEditModel::read(const Reference<XObjectInputStream>& _rxInStream) throw ( ::com::sun::star::io::IOException, ::com::sun::star::uno::RuntimeException)
{
    OEditBaseModel::read(_rxInStream);

    // Some versions (5.1 'til about 552) wrote a wrong DefaultControl-property value which is unknown
    // to older versions (5.0).
    // correct this ...
    if (m_xAggregateSet.is())
    {
        Any aDefaultControl = m_xAggregateSet->getPropertyValue(PROPERTY_DEFAULTCONTROL);
        if	(	(aDefaultControl.getValueType().getTypeClass() == TypeClass_STRING)
            &&	(getString(aDefaultControl).compareTo(FRM_CONTROL_TEXTFIELD) == COMPARE_EQUAL)
            )
        {
            m_xAggregateSet->setPropertyValue(PROPERTY_DEFAULTCONTROL, makeAny(::rtl::OUString(FRM_CONTROL_EDIT)));
            // Older as well as current versions should understand this : the former knew only the FRM_CONTROL_EDIT,
            // the latter are registered for both FRM_CONTROL_EDIT and FRM_CONTROL_TEXTFIELD.
        }
    }
}

//------------------------------------------------------------------------------
sal_Int16 OEditModel::getPersistenceFlags() const
{
    sal_Int16 nFlags = OEditBaseModel::getPersistenceFlags();

    if (m_bWritingFormattedFake)
        nFlags |= PF_FAKE_FORMATTED_FIELD;

    return nFlags;
}

// XLoadListener
//------------------------------------------------------------------------------
void OEditModel::_loaded(const EventObject& rEvent)
{
    m_bNumericField = sal_False;
    Reference<XPropertySet> xField = getField();
    if (xField.is())
    {
        // jetzt den Key und typ ermitteln
        m_nFieldType  = getINT32(xField->getPropertyValue(PROPERTY_FIELDTYPE));
        m_nFormatKey = getINT32(xField->getPropertyValue(PROPERTY_FORMATKEY));

        switch (m_nFieldType)
        {
            case ::com::sun::star::sdbc::DataType::DATE:
            case ::com::sun::star::sdbc::DataType::TIME:
            case ::com::sun::star::sdbc::DataType::TIMESTAMP:
            case ::com::sun::star::sdbc::DataType::BIT:
            case ::com::sun::star::sdbc::DataType::TINYINT:
            case ::com::sun::star::sdbc::DataType::SMALLINT:
            case ::com::sun::star::sdbc::DataType::INTEGER:
            case ::com::sun::star::sdbc::DataType::REAL:
            case ::com::sun::star::sdbc::DataType::BIGINT:
            case ::com::sun::star::sdbc::DataType::DOUBLE:
            case ::com::sun::star::sdbc::DataType::NUMERIC:
            case ::com::sun::star::sdbc::DataType::DECIMAL:
                m_bNumericField = sal_True;
                break;
            default:
                m_bNumericField = sal_False;
                break;
        }

        // XNumberFormatter besorgen
        Reference<XRowSet>  xRowSet(rEvent.Source, UNO_QUERY);
        DBG_ASSERT(xRowSet.is(), "OEditModel::_loaded : source is not a row set ?");
        Reference<XNumberFormatsSupplier>  xSupplier = getNumberFormats(getConnection(xRowSet), sal_False, m_xServiceFactory);
        if (xSupplier.is())
        {
            m_xFormatter =	Reference<XNumberFormatter>(m_xServiceFactory
                                ->createInstance(FRM_NUMBER_FORMATTER), UNO_QUERY);
            if (m_xFormatter.is())
                m_xFormatter->attachNumberFormatsSupplier(xSupplier);

            m_nKeyType  = getNumberFormatType(xSupplier->getNumberFormats(), m_nFormatKey);
            xSupplier->getNumberFormatSettings()->getPropertyValue(::rtl::OUString( RTL_CONSTASCII_USTRINGPARAM( "NullDate" )))
                >>= m_aNullDate;
        }

        if (m_nKeyType != NumberFormat::SCIENTIFIC)
        {
            m_bMaxTextLenModified =	getINT16(m_xAggregateSet->getPropertyValue(PROPERTY_MAXTEXTLEN)) != 0;
            if ( !m_bMaxTextLenModified )
            {
                sal_Int32 nFieldLen(0);
                xField->getPropertyValue(::rtl::OUString( RTL_CONSTASCII_USTRINGPARAM( "Precision" ))) >>= nFieldLen;

                if (nFieldLen && nFieldLen <= USHRT_MAX)
                {
                    Any aVal;
                    aVal <<= (sal_Int16)nFieldLen;
                    m_xAggregateSet->setPropertyValue(PROPERTY_MAXTEXTLEN, aVal);

                    m_bMaxTextLenModified = sal_True;
                }
            }
            else
                m_bMaxTextLenModified = sal_False; // to get sure that the text len won't be set in unloaded
        }
    }
}

//------------------------------------------------------------------------------
void OEditModel::_unloaded()
{
    OEditBaseModel::_unloaded();
    if (getField().is())
    {
        if ( m_bMaxTextLenModified )
        {
            Any aVal;
            aVal <<= (sal_Int16)0;	// nur wenn es 0 war, habe ich es in _loaded umgesetzt
            m_xAggregateSet->setPropertyValue(PROPERTY_MAXTEXTLEN, aVal);
            m_bMaxTextLenModified = sal_False;
        }

        m_xFormatter = 0;
        m_nFieldType = DataType::OTHER;
        m_nFormatKey = 0;
        m_nKeyType	 = NumberFormat::UNDEFINED;
        m_aNullDate	 = DBTypeConversion::getStandardDate();
    }
}

//------------------------------------------------------------------------------
sal_Bool OEditModel::_commit()
{
    ::rtl::OUString sNewValue;
    m_xAggregateFastSet->getFastPropertyValue(OEditModel::nTextHandle) >>= sNewValue;
    if (sNewValue != m_aSaveValue)
    {
        if (!sNewValue.getLength() && !m_bRequired && m_bEmptyIsNull)
            m_xColumnUpdate->updateNull();
        else
        {
            try
            {
                if ( m_bNumericField )
                    DBTypeConversion::setValue(m_xColumnUpdate, m_xFormatter, m_aNullDate, sNewValue, m_nFormatKey, m_nFieldType, m_nKeyType);
                else
                    m_xColumnUpdate->updateString(sNewValue);
            }
            catch(Exception&)
            {
                return sal_False;
            }
        }
        m_aSaveValue = sNewValue;
    }
    return sal_True;
}

// XPropertyChangeListener
//------------------------------------------------------------------------------
void OEditModel::_onValueChanged()
{

    // release our mutex once (it's acquired in the calling method !), as setting aggregate properties
    // may cause any uno controls belonging to us to lock the solar mutex, which is potentially dangerous with
    // our own mutex locked
    // and in this special case do it before calling DBTypeConversion::getValue, as this uses the number formatter
    // which's implementation locks the SM, too :(
    MutexRelease aRelease(m_aMutex);
    m_aSaveValue = DBTypeConversion::getValue(m_xColumn,
                                              m_xFormatter,
                                              m_aNullDate,
                                              m_nFormatKey,
                                              m_nKeyType);

    // #i2817# OJ
    sal_uInt16 nMaxTextLen = getINT16(m_xAggregateSet->getPropertyValue(PROPERTY_MAXTEXTLEN));
    if ( nMaxTextLen && m_aSaveValue.getLength() > nMaxTextLen )
    {
        sal_Int32 nDiff = m_aSaveValue.getLength() - nMaxTextLen;
        m_aSaveValue = m_aSaveValue.replaceAt(nMaxTextLen,nDiff,::rtl::OUString());
    }

    m_xAggregateFastSet->setFastPropertyValue(OEditModel::nTextHandle, makeAny(m_aSaveValue));
}

// XReset
//------------------------------------------------------------------------------
void OEditModel::_reset()
{
    {	// release our mutex once (it's acquired in the calling method !), as setting aggregate properties
        // may cause any uno controls belonging to us to lock the solar mutex, which is potentially dangerous with
        // our own mutex locked
        MutexRelease aRelease(m_aMutex);
        m_xAggregateFastSet->setFastPropertyValue(OEditModel::nTextHandle, makeAny(m_aDefaultText));
    }
}

//.........................................................................
}
//.........................................................................

}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
