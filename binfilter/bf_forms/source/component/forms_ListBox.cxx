/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: forms_ListBox.cxx,v $
 *
 *  $Revision: 1.9 $
 *
 *  last change: $Author: rt $ $Date: 2006-10-27 14:03:35 $
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

#ifndef _COMPHELPER_PROPERTY_ARRAY_HELPER_HXX_
#include <comphelper/proparrhlp.hxx>
#endif

#ifndef _FORMS_LISTBOX_HXX_
#include "ListBox.hxx"
#endif
#ifndef _FRM_PROPERTY_HRC_
#include "property.hrc"
#endif
#ifndef _FRM_SERVICES_HXX_
#include "services.hxx"
#endif
#ifndef _FRM_RESOURCE_HXX_
#include "frm_resource.hxx"
#endif
#ifndef _FRM_RESOURCE_HRC_
#include "frm_resource.hrc"
#endif
#ifndef _FORMS_BASELISTBOX_HXX_
#include "BaseListBox.hxx"
#endif
#ifndef _COMPHELPER_CONTAINER_HXX_
#include <comphelper/container.hxx>
#endif
#ifndef _COMPHELPER_NUMBERS_HXX_
#include <comphelper/numbers.hxx>
#endif
#ifndef _DBHELPER_DBCONVERSION_HXX_
#include <connectivity/dbconversion.hxx>
#endif

#ifndef _COM_SUN_STAR_UTIL_XNUMBERFORMATTYPES_HPP_
#include <com/sun/star/util/XNumberFormatTypes.hpp>
#endif
#ifndef _COM_SUN_STAR_CONTAINER_XINDEXACCESS_HPP_
#include <com/sun/star/container/XIndexAccess.hpp>
#endif
#ifndef _COM_SUN_STAR_SDB_XSQLQUERYCOMPOSERFACTORY_HPP_
#include <com/sun/star/sdb/XSQLQueryComposerFactory.hpp>
#endif
#ifndef _COM_SUN_STAR_SDB_XQUERIESSUPPLIER_HPP_
#include <com/sun/star/sdb/XQueriesSupplier.hpp>
#endif
#ifndef _COM_SUN_STAR_UTIL_NUMBERFORMAT_HPP_
#include <com/sun/star/util/NumberFormat.hpp>
#endif
#ifndef _COM_SUN_STAR_AWT_XLISTBOX_HPP_
#include <com/sun/star/awt/XListBox.hpp>
#endif
#ifndef _COM_SUN_STAR_AWT_XWINDOW_HPP_
#include <com/sun/star/awt/XWindow.hpp>
#endif
#ifndef _COM_SUN_STAR_SDBC_XCONNECTION_HPP_
#include <com/sun/star/sdbc/XConnection.hpp>
#endif
#ifndef _COM_SUN_STAR_SDB_COMMANDTYPE_HPP_
#include <com/sun/star/sdb/CommandType.hpp>
#endif
#ifndef _CONNECTIVITY_DBTOOLS_HXX_
#include <connectivity/dbtools.hxx>
#endif
#ifndef _SV_SVAPP_HXX
#include <vcl/svapp.hxx>
#endif

#ifndef _COM_SUN_STAR_FORM_FORMCOMPONENTTYPE_HPP_
#include <com/sun/star/form/FormComponentType.hpp>
#endif

#ifndef _COM_SUN_STAR_BEANS_PROPERTYATTRIBUTE_HPP_
#include <com/sun/star/beans/PropertyAttribute.hpp>
#endif

#ifndef _COMPHELPER_PROPERTY_HXX_
#include <comphelper/property.hxx>
#endif

#ifndef _COM_SUN_STAR_SDBCX_XCOLUMNSSUPPLIER_HPP_
#include <com/sun/star/sdbcx/XColumnsSupplier.hpp>
#endif

namespace binfilter {


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
using namespace ::dbtools;

//==================================================================
//= OListBoxModel
//==================================================================
sal_Int32 OListBoxModel::nSelectHandle = -1;
//------------------------------------------------------------------
InterfaceRef SAL_CALL OListBoxModel_CreateInstance(const Reference<XMultiServiceFactory>& _rxFactory) throw (RuntimeException)
{
    return *(new OListBoxModel(_rxFactory));
}

//------------------------------------------------------------------------------
Sequence< Type> OListBoxModel::_getTypes()
{
    return ::comphelper::concatSequences(
        OBoundControlModel::_getTypes(),
        OListBoxModel_BASE::getTypes(),
        OErrorBroadcaster::getTypes()
    );
}


DBG_NAME(OListBoxModel)
//------------------------------------------------------------------
OListBoxModel::OListBoxModel(const Reference<XMultiServiceFactory>& _rxFactory)
    :OBoundControlModel(_rxFactory, VCL_CONTROLMODEL_LISTBOX, FRM_CONTROL_LISTBOX)
                                    // use the old control name for compytibility reasons
    ,OErrorBroadcaster( OComponentHelper::rBHelper )
    ,m_aRefreshListeners(m_aMutex)
    ,m_bBoundComponent(sal_False)
    ,m_nNULLPos(-1)
{
    DBG_CTOR(OListBoxModel,NULL);

    m_nClassId = FormComponentType::LISTBOX;
    m_eListSourceType = ListSourceType_VALUELIST;
    m_aBoundColumn <<= (sal_Int16)1;
    m_sDataFieldConnectivityProperty = PROPERTY_SELECT_SEQ;
    if (OListBoxModel::nSelectHandle == -1)
        OListBoxModel::nSelectHandle = getOriginalHandle(PROPERTY_ID_SELECT_SEQ);
}

//------------------------------------------------------------------
OListBoxModel::OListBoxModel( const OListBoxModel* _pOriginal, const Reference<XMultiServiceFactory>& _rxFactory )
    :OBoundControlModel( _pOriginal, _rxFactory )
    ,OErrorBroadcaster( OComponentHelper::rBHelper )
    ,m_aRefreshListeners( m_aMutex )
    ,m_bBoundComponent(sal_False)
    ,m_nNULLPos(-1)
{
    DBG_CTOR(OListBoxModel,NULL);
    m_eListSourceType = _pOriginal->m_eListSourceType;
    m_aBoundColumn = _pOriginal->m_aBoundColumn;
}

//------------------------------------------------------------------
OListBoxModel::~OListBoxModel()
{
    if (!OComponentHelper::rBHelper.bDisposed)
    {
        acquire();
        dispose();
    }

    DBG_DTOR(OListBoxModel,NULL);
}

// XCloneable
//------------------------------------------------------------------------------
IMPLEMENT_DEFAULT_CLONING( OListBoxModel )

// XServiceInfo
//------------------------------------------------------------------------------
StringSequence SAL_CALL OListBoxModel::getSupportedServiceNames() throw(RuntimeException)
{
    StringSequence aSupported = OBoundControlModel::getSupportedServiceNames();
    aSupported.realloc(aSupported.getLength() + 2);

    ::rtl::OUString* pArray = aSupported.getArray();
    pArray[aSupported.getLength()-2] = FRM_SUN_COMPONENT_DATABASE_LISTBOX;
    pArray[aSupported.getLength()-1] = FRM_SUN_COMPONENT_LISTBOX;
    return aSupported;
}

//------------------------------------------------------------------------------
Any SAL_CALL OListBoxModel::queryAggregation(const Type& _rType) throw (RuntimeException)
{
    Any aReturn = OBoundControlModel::queryAggregation( _rType );
    if ( !aReturn.hasValue() )
        aReturn = OListBoxModel_BASE::queryInterface( _rType );
    if ( !aReturn.hasValue() )
        aReturn = OErrorBroadcaster::queryInterface( _rType );
    return aReturn;
}

// OComponentHelper
//------------------------------------------------------------------------------
void OListBoxModel::disposing()
{
    EventObject aEvt( static_cast< XWeak* >( this ) );
    m_aRefreshListeners.disposeAndClear(aEvt);

    OBoundControlModel::disposing();
    OErrorBroadcaster::disposing();
}

// XRefreshable
//------------------------------------------------------------------------------
void SAL_CALL OListBoxModel::addRefreshListener(const Reference<XRefreshListener>& _rxListener) throw(RuntimeException)
{
    m_aRefreshListeners.addInterface(_rxListener);
}

//------------------------------------------------------------------------------
void SAL_CALL OListBoxModel::removeRefreshListener(const Reference<XRefreshListener>& _rxListener) throw(RuntimeException)
{
    m_aRefreshListeners.removeInterface(_rxListener);
}

//------------------------------------------------------------------------------
void SAL_CALL OListBoxModel::refresh() throw(RuntimeException)
{
    {
        ::osl::MutexGuard aGuard(m_aMutex);
        if (m_eListSourceType != ListSourceType_VALUELIST)
        {
            if (getField().is())
                m_aValueSeq = StringSequence();

            if (m_xCursor.is())
                loadData();
        }
    }

    EventObject aEvt(static_cast< XWeak*>(this));
    m_aRefreshListeners.notifyEach(&XRefreshListener::refreshed, aEvt);
}

//------------------------------------------------------------------------------
void OListBoxModel::getFastPropertyValue(Any& _rValue, sal_Int32 _nHandle) const
{
    switch (_nHandle)
    {
        case PROPERTY_ID_BOUNDCOLUMN:
            _rValue <<= m_aBoundColumn;
            break;

        case PROPERTY_ID_LISTSOURCETYPE:
            _rValue <<= m_eListSourceType;
            break;

        case PROPERTY_ID_LISTSOURCE:
            _rValue <<= m_aListSourceSeq;
            break;

        case PROPERTY_ID_VALUE_SEQ:
            _rValue <<= m_aValueSeq;
            break;

        case PROPERTY_ID_DEFAULT_SELECT_SEQ:
            _rValue <<= m_aDefaultSelectSeq;
            break;

        default:
            OBoundControlModel::getFastPropertyValue(_rValue, _nHandle);
    }
}

//------------------------------------------------------------------------------
void OListBoxModel::setFastPropertyValue_NoBroadcast(sal_Int32 _nHandle, const Any& _rValue) throw (com::sun::star::uno::Exception)
{
    switch (_nHandle)
    {
        case PROPERTY_ID_BOUNDCOLUMN :
            DBG_ASSERT((_rValue.getValueType().getTypeClass() == TypeClass_SHORT) || (_rValue.getValueType().getTypeClass() == TypeClass_VOID),
                "OListBoxModel::setFastPropertyValue_NoBroadcast : invalid type !" );
            m_aBoundColumn = _rValue;
            break;

        case PROPERTY_ID_LISTSOURCETYPE :
            DBG_ASSERT(_rValue.getValueType().equals(::getCppuType(reinterpret_cast<ListSourceType*>(NULL))),
                "OComboBoxModel::setFastPropertyValue_NoBroadcast : invalid type !" );
            _rValue >>= m_eListSourceType;
            break;

        case PROPERTY_ID_LISTSOURCE :
            DBG_ASSERT(_rValue.getValueType().equals(::getCppuType(reinterpret_cast<StringSequence*>(NULL))),
                "OListBoxModel::setFastPropertyValue_NoBroadcast : invalid type !" );
            _rValue >>= m_aListSourceSeq;

            if (m_eListSourceType == ListSourceType_VALUELIST)
                m_aValueSeq = m_aListSourceSeq;
            else if (m_xCursor.is() && !getField().is()) // Listbox bereits mit Datenbank verbunden
                // Aenderung der Datenquelle -> neu laden
                loadData();

            break;

        case PROPERTY_ID_VALUE_SEQ :
            DBG_ASSERT(_rValue.getValueType().equals(::getCppuType(reinterpret_cast<StringSequence*>(NULL))),
                "OListBoxModel::setFastPropertyValue_NoBroadcast : invalid type !" );
            _rValue >>= m_aValueSeq;
            break;

        case PROPERTY_ID_DEFAULT_SELECT_SEQ :
            DBG_ASSERT(_rValue.getValueType().equals(::getCppuType(reinterpret_cast< Sequence<sal_Int16>*>(NULL))),
                "OListBoxModel::setFastPropertyValue_NoBroadcast : invalid type !" );
            _rValue >>= m_aDefaultSelectSeq;

            DBG_ASSERT(m_xAggregateFastSet.is(), "OListBoxModel::setFastPropertyValue_NoBroadcast(DEFAULT_SELECT_SEQ) : invalid aggregate !");
            if (m_xAggregateFastSet.is())
            {	// release our mutex once (it's acquired in the calling method !), as setting aggregate properties
                // may cause any uno controls belonging to us to lock the solar mutex, which is potentially dangerous with
                // our own mutex locked
                // FS - 72451 - 31.01.00
                MutexRelease aRelease(m_aMutex);
                m_xAggregateFastSet->setFastPropertyValue(OListBoxModel::nSelectHandle, _rValue);
            }
            break;

        default:
            OBoundControlModel::setFastPropertyValue_NoBroadcast(_nHandle, _rValue);
    }

    if (PROPERTY_ID_STRINGITEMLIST == _nHandle)
        _reset();
}

//------------------------------------------------------------------------------
sal_Bool OListBoxModel::convertFastPropertyValue(
            Any& _rConvertedValue, Any& _rOldValue, sal_Int32 _nHandle, const Any& _rValue)
                        throw (IllegalArgumentException)
{
    sal_Bool bModified(sal_False);
    switch (_nHandle)
    {
        case PROPERTY_ID_BOUNDCOLUMN :
            bModified = tryPropertyValue(_rConvertedValue, _rOldValue, _rValue, m_aBoundColumn, ::getCppuType(reinterpret_cast<sal_Int16*>(NULL)));
            break;

        case PROPERTY_ID_LISTSOURCETYPE:
            bModified = tryPropertyValueEnum(_rConvertedValue, _rOldValue, _rValue, m_eListSourceType);
            break;

        case PROPERTY_ID_LISTSOURCE:
            bModified = tryPropertyValue(_rConvertedValue, _rOldValue, _rValue, m_aListSourceSeq);
            break;

        case PROPERTY_ID_VALUE_SEQ :
            bModified = tryPropertyValue(_rConvertedValue, _rOldValue, _rValue, m_aValueSeq);
            break;

        case PROPERTY_ID_DEFAULT_SELECT_SEQ :
            bModified = tryPropertyValue(_rConvertedValue, _rOldValue, _rValue, m_aDefaultSelectSeq);
            break;

        default:
            return OBoundControlModel::convertFastPropertyValue(_rConvertedValue, _rOldValue, _nHandle, _rValue);
    }
    return bModified;
}

//------------------------------------------------------------------------------
Reference<XPropertySetInfo> SAL_CALL OListBoxModel::getPropertySetInfo() throw(RuntimeException)
{
        Reference<XPropertySetInfo> xInfo( createPropertySetInfo( getInfoHelper() ) );
    return xInfo;
}

//------------------------------------------------------------------------------
cppu::IPropertyArrayHelper& OListBoxModel::getInfoHelper()
{
    return *const_cast<OListBoxModel*>(this)->getArrayHelper();
}

//------------------------------------------------------------------------------
void OListBoxModel::fillProperties(
                Sequence< Property >& _rProps,
                Sequence< Property >& _rAggregateProps ) const
{
    FRM_BEGIN_PROP_HELPER(13)
        DECL_PROP2(CLASSID, 			sal_Int16,						READONLY, TRANSIENT);
        DECL_PROP1(NAME,				::rtl::OUString,				BOUND);
        DECL_PROP1(TAG, 				::rtl::OUString,				BOUND);
        DECL_PROP1(TABINDEX,			sal_Int16,						BOUND);
        DECL_PROP2(BOUNDCOLUMN, 		sal_Int16,						BOUND, MAYBEVOID);
        DECL_PROP1(LISTSOURCETYPE,		ListSourceType, 				BOUND);
        DECL_PROP1(LISTSOURCE,			StringSequence, 				BOUND);
        DECL_PROP3(VALUE_SEQ,			StringSequence, 				BOUND, READONLY, TRANSIENT);
        DECL_PROP1(DEFAULT_SELECT_SEQ,	Sequence<sal_Int16>,			BOUND);
        DECL_PROP1(CONTROLSOURCE,		::rtl::OUString,				BOUND);
        DECL_IFACE_PROP3(BOUNDFIELD,	XPropertySet,					BOUND,READONLY, TRANSIENT);
        DECL_IFACE_PROP2(CONTROLLABEL,	XPropertySet,					BOUND, MAYBEVOID);
        DECL_PROP2(CONTROLSOURCEPROPERTY,	rtl::OUString,				READONLY, TRANSIENT);
    FRM_END_PROP_HELPER();
}

//------------------------------------------------------------------------------
::rtl::OUString SAL_CALL OListBoxModel::getServiceName() throw(RuntimeException)
{
    return FRM_COMPONENT_LISTBOX;	// old (non-sun) name for compatibility !
}

//------------------------------------------------------------------------------
void SAL_CALL OListBoxModel::write(const Reference<stario::XObjectOutputStream>& _rxOutStream)
    throw(stario::IOException, RuntimeException)
{
    OBoundControlModel::write(_rxOutStream);

    // Dummy-Seq, um Kompatible zu bleiben, wenn SelectSeq nicht mehr gespeichert wird
    Sequence<sal_Int16> aDummySeq;

    // Version
    // Version 0x0002: ListSource wird StringSeq
    _rxOutStream->writeShort(0x0004);

    // Maskierung fuer any
    sal_uInt16 nAnyMask = 0;
    if (m_aBoundColumn.getValueType().getTypeClass() != TypeClass_VOID)
        nAnyMask |= BOUNDCOLUMN;

    _rxOutStream << nAnyMask;

    _rxOutStream << m_aListSourceSeq;
    _rxOutStream << (sal_Int16)m_eListSourceType;
    _rxOutStream << aDummySeq;
    _rxOutStream << m_aDefaultSelectSeq;

    if ((nAnyMask & BOUNDCOLUMN) == BOUNDCOLUMN)
    {
        sal_Int16 nBoundColumn;
        m_aBoundColumn >>= nBoundColumn;
        _rxOutStream << nBoundColumn;
    }
    writeHelpTextCompatibly(_rxOutStream);

    // from version 0x0004 : common properties
    writeCommonProperties(_rxOutStream);
}

//------------------------------------------------------------------------------
void SAL_CALL OListBoxModel::read(const Reference<stario::XObjectInputStream>& _rxInStream) throw(stario::IOException, RuntimeException)
{
    // Bei manchen Variblen muessen Abhaengigkeiten beruecksichtigt werden.
    // Deshalb muessen sie explizit ueber setPropertyValue() gesetzt werden.

    OBoundControlModel::read(_rxInStream);
    ::osl::MutexGuard aGuard(m_aMutex);

    // Version
    sal_uInt16 nVersion = _rxInStream->readShort();
    DBG_ASSERT(nVersion > 0, "OListBoxModel::read : version 0 ? this should never have been written !");

    if (nVersion > 0x0004)
    {
        DBG_ERROR("OListBoxModel::read : invalid (means unknown) version !");
        m_aListSourceSeq.realloc(0);
        m_aBoundColumn <<= (sal_Int16)0;
        m_aValueSeq.realloc(0);
        m_eListSourceType = ListSourceType_VALUELIST;
        m_aDefaultSelectSeq.realloc(0);
        defaultCommonProperties();
        return;
    }

    // Maskierung fuer any
    sal_uInt16 nAnyMask;
    _rxInStream >> nAnyMask;

    // ListSourceSeq
    StringSequence aListSourceSeq;
    if (nVersion == 0x0001)
    {
        // ListSourceSeq aus String zusammenstellen;
        ::rtl::OUString sListSource;
        _rxInStream >> sListSource;

        sal_Int32 nTokens = 1;
        const sal_Unicode* pStr = sListSource.getStr();
        while ( *pStr )
        {
            if ( *pStr == ';' )
                nTokens++;
            pStr++;
        }
        aListSourceSeq.realloc( nTokens );
        for (sal_uInt16 i=0; i<nTokens; ++i)
        {
            sal_Int32 nTmp = 0;
            aListSourceSeq.getArray()[i] = sListSource.getToken(i,';',nTmp);
        }
    }
    else
        _rxInStream >> aListSourceSeq;

    sal_Int16 nListSourceType;
    _rxInStream >> nListSourceType;
    m_eListSourceType = (ListSourceType)nListSourceType;
    Any aListSourceSeqAny;
    aListSourceSeqAny <<= aListSourceSeq;

    setFastPropertyValue(PROPERTY_ID_LISTSOURCE, aListSourceSeqAny );

    // Dummy-Seq, um Kompatible zu bleiben, wenn SelectSeq nicht mehr gespeichert wird
    Sequence<sal_Int16> aDummySeq;
    _rxInStream >> aDummySeq;

    // DefaultSelectSeq
    Sequence<sal_Int16> aDefaultSelectSeq;
    _rxInStream >> aDefaultSelectSeq;
    Any aDefaultSelectSeqAny;
    aDefaultSelectSeqAny <<= aDefaultSelectSeq;
    setFastPropertyValue(PROPERTY_ID_DEFAULT_SELECT_SEQ, aDefaultSelectSeqAny);

    // BoundColumn
    if ((nAnyMask & BOUNDCOLUMN) == BOUNDCOLUMN)
    {
        sal_Int16 nValue;
        _rxInStream >> nValue;
        m_aBoundColumn <<= nValue;
    }

    if (nVersion > 2)
        readHelpTextCompatibly(_rxInStream);

    // Stringliste muss gelehrt werden, wenn nicht ueber WerteListe gefuellt wird
    // dieses kann der Fall sein wenn im alive modus gespeichert wird
    if (m_eListSourceType != ListSourceType_VALUELIST && m_xAggregateSet.is())
    {
        StringSequence aSequence;
        setFastPropertyValue(PROPERTY_ID_STRINGITEMLIST, makeAny(aSequence));
    }

    if (nVersion > 3)
        readCommonProperties(_rxInStream);

    // Nach dem Lesen die Defaultwerte anzeigen
    if (m_aControlSource.getLength())
        // (not if we don't have a control source - the "State" property acts like it is persistent, then
        _reset();
}

//------------------------------------------------------------------------------
void OListBoxModel::loadData()
{
    DBG_ASSERT(m_eListSourceType != ListSourceType_VALUELIST, "fuer Werteliste kein Laden aus der Datenbank")

    m_nNULLPos = -1;
    m_bBoundComponent = sal_False;

    // Connection holen
    Reference<XRowSet> xForm(m_xCursor, UNO_QUERY);
    if (!xForm.is())
        return;
    Reference<XConnection> xConnection = getConnection(xForm);
    if (!xConnection.is())
        return;

    // we need a com::sun::star::sdb::Connection for some of the code below ...
        Reference<XServiceInfo> xServiceInfo(xConnection, UNO_QUERY);
    if (!xServiceInfo.is() || !xServiceInfo->supportsService(SRV_SDB_CONNECTION))
    {
        DBG_ERROR("OListBoxModel::loadData : invalid connection !");
        return;
    }

    Reference< XRowSet > xContentRowSet(m_xServiceFactory->createInstance(SRV_SDB_ROWSET), UNO_QUERY);
    Reference< XPropertySet > xContentSetProperties(xContentRowSet, UNO_QUERY);
    Reference<XResultSet> xListCursor(xContentSetProperties, UNO_QUERY);
    if (!xListCursor.is())
    {
        DBG_ERROR("OListBoxModel::loadData: could not instantiate a RowSet!");
        return;
    }

    // Wenn der ListSourceType keine Werteliste ist,
    // muss die String-Seq zu einem String zusammengefasst werden
    ::rtl::OUString sListSource;
    const ::rtl::OUString* pustrListSouceStrings = m_aListSourceSeq.getConstArray();
    sal_Int32 i;
    for (i=0; i<m_aListSourceSeq.getLength(); ++i)
        sListSource = sListSource + pustrListSouceStrings[i];
    if (!sListSource.getLength())
        return;

    sal_Int16 nBoundColumn = 0;
    if (m_aBoundColumn.getValueType().getTypeClass() == TypeClass_SHORT)
        m_aBoundColumn >>= nBoundColumn;

    try
    {
        sal_Bool bExecute = sal_False;
        switch (m_eListSourceType)
        {
            case ListSourceType_TABLEFIELDS:
                // don't work with a statement here, the fields will be collected below
                break;
            case ListSourceType_TABLE:
            {
                Reference<XNameAccess> xFieldsByName = getTableFields(xConnection, sListSource);
                Reference<XIndexAccess> xFieldsByIndex(xFieldsByName, UNO_QUERY);

                // do we have a bound column if yes we have to select it
                // and the displayed column is the first column othwhise we act as a combobox
                ::rtl::OUString aFieldName;
                ::rtl::OUString aBoundFieldName;

                if ((nBoundColumn > 0) && xFieldsByIndex.is())
                {
                    if (xFieldsByIndex->getCount() <= nBoundColumn)
                        break;

                                        Reference<XPropertySet> xFieldAsSet;
                    xFieldsByIndex->getByIndex(nBoundColumn) >>= xFieldAsSet;
                    xFieldAsSet->getPropertyValue(PROPERTY_NAME) >>= aBoundFieldName;
                    nBoundColumn = 1;

                    xFieldsByIndex->getByIndex(0) >>= xFieldAsSet;
                    xFieldAsSet->getPropertyValue(PROPERTY_NAME) >>= aFieldName;
                }
                else if (xFieldsByName.is())
                {
                    if (xFieldsByName->hasByName(m_aControlSource))
                        aFieldName = m_aControlSource;
                    else
                    {
                        // otherwise look for the alias
                        Reference<XSQLQueryComposerFactory> xFactory(xConnection, UNO_QUERY);
                        if (!xFactory.is())
                            break;

                        Reference<XSQLQueryComposer> xComposer = xFactory->createQueryComposer();
                        try
                        {
                            Reference<XPropertySet> xFormAsSet(xForm, UNO_QUERY);
                            ::rtl::OUString aStatement;
                            xFormAsSet->getPropertyValue(PROPERTY_ACTIVECOMMAND) >>= aStatement;
                            xComposer->setQuery(aStatement);
                        }
                        catch(Exception&)
                        {
                            disposeComponent(xComposer);
                            break;
                        }

                        // search the field
                        Reference<XColumnsSupplier> xSupplyFields(xComposer, UNO_QUERY);
                        DBG_ASSERT(xSupplyFields.is(), "OListBoxModel::loadData : invalid query composer !");

                        Reference<XNameAccess> xFieldNames = xSupplyFields->getColumns();
                        if (xFieldNames->hasByName(m_aControlSource))
                        {
                                                        Reference<XPropertySet> xComposerFieldAsSet;
                            xFieldNames->getByName(m_aControlSource) >>= xComposerFieldAsSet;
                            if (hasProperty(PROPERTY_FIELDSOURCE, xComposerFieldAsSet))
                                xComposerFieldAsSet->getPropertyValue(PROPERTY_FIELDSOURCE) >>= aFieldName;
                        }
                        disposeComponent(xComposer);
                    }
                }
                if (!aFieldName.getLength())
                    break;

                Reference<XDatabaseMetaData> xMeta = xConnection->getMetaData();
                ::rtl::OUString aQuote = xMeta->getIdentifierQuoteString();
                ::rtl::OUString aStatement = ::rtl::OUString::createFromAscii("SELECT ");
                if (!aBoundFieldName.getLength())	// act like a combobox
                    aStatement += ::rtl::OUString::createFromAscii("DISTINCT ");

                aStatement += quoteName(aQuote,aFieldName);
                if (aBoundFieldName.getLength())
                {
                    aStatement += ::rtl::OUString::createFromAscii(", ");
                    aStatement += quoteName(aQuote, aBoundFieldName);
                }
                aStatement += ::rtl::OUString::createFromAscii(" FROM ");
                aStatement += quoteTableName(xMeta, sListSource,::dbtools::eInDataManipulation);

                xContentSetProperties->setPropertyValue(PROPERTY_COMMAND, makeAny(aStatement));
                bExecute = sal_True;
            }	break;
            case ListSourceType_QUERY:
            {
                Reference<XQueriesSupplier> xSupplyQueries(xConnection, UNO_QUERY);
                Reference<XPropertySet> xQuery(*(InterfaceRef*)xSupplyQueries->getQueries()->getByName(sListSource).getValue(), UNO_QUERY);
                xContentSetProperties->setPropertyValue(PROPERTY_ESCAPE_PROCESSING, xQuery->getPropertyValue(PROPERTY_ESCAPE_PROCESSING));

                xContentSetProperties->setPropertyValue(PROPERTY_COMMAND, xQuery->getPropertyValue(PROPERTY_COMMAND));
                bExecute = sal_True;
            }	break;
            default:
            {
                if (ListSourceType_SQLPASSTHROUGH == m_eListSourceType)
                    xContentSetProperties->setPropertyValue(PROPERTY_ESCAPE_PROCESSING, ::cppu::bool2any((sal_False)));
                xContentSetProperties->setPropertyValue(PROPERTY_COMMAND, makeAny(sListSource));
                bExecute = sal_True;
            }
        }

        if (bExecute)
        {
            Reference< XPropertySet > xFormProps(xForm, UNO_QUERY);

            xContentSetProperties->setPropertyValue( PROPERTY_COMMANDTYPE, makeAny( CommandType::COMMAND ) );
            xContentSetProperties->setPropertyValue( PROPERTY_DATASOURCE, xFormProps->getPropertyValue( PROPERTY_DATASOURCE ) );

            // try to give the row set the connection of our form - this saves the rowset from creating an own one
            xContentSetProperties->setPropertyValue( PROPERTY_ACTIVE_CONNECTION, xFormProps->getPropertyValue( PROPERTY_ACTIVE_CONNECTION ) );

            xContentRowSet->execute();
        }
    }
    catch(SQLException& eSQL)
    {
        onError(eSQL, FRM_RES_STRING(RID_BASELISTBOX_ERROR_FILLLIST));
        disposeComponent(xListCursor);
        return;
    }
    catch(Exception& eUnknown)
    {
        eUnknown;
        disposeComponent(xListCursor);
        return;
    }

    if (ListSourceType_TABLEFIELDS != m_eListSourceType && !xListCursor.is())
        // something went wrong ...
        return;

    // Anzeige- und Werteliste fuellen
    vector< ::rtl::OUString >	aValueList, aStringList;
    aValueList.reserve(16);
    aStringList.reserve(16);
    sal_Bool bUseNULL = getField().is() && !m_bRequired;
    try
    {
        switch (m_eListSourceType)
        {
            case ListSourceType_SQL:
            case ListSourceType_SQLPASSTHROUGH:
            case ListSourceType_TABLE:
            case ListSourceType_QUERY:
            {
                // Feld der 1. Column des ResultSets holen
                Reference<XColumnsSupplier> xSupplyCols(xListCursor, UNO_QUERY);
                DBG_ASSERT(xSupplyCols.is(), "OListBoxModel::loadData : cursor supports the row set service but is no column supplier ??!");
                Reference<XIndexAccess> xColumns;
                if (xSupplyCols.is())
                {
                    xColumns = Reference<XIndexAccess>(xSupplyCols->getColumns(), UNO_QUERY);
                    DBG_ASSERT(xColumns.is(), "OListBoxModel::loadData : no columns supplied by the row set !");
                }
                Reference<XColumn> xDataField;
                if (xColumns.is())
                    xColumns->getByIndex(0) >>= xDataField;
                if (!xDataField.is())
                {
                    disposeComponent(xListCursor);
                    return;
                }

                Reference<XNumberFormatsSupplier> xSupplier = getNumberFormats(xConnection, sal_False, m_xServiceFactory);

                ::com::sun::star::util::Date aNullDate(DBTypeConversion::getStandardDate());
                sal_Int32 nFormatKey = 0;
                sal_Int32 nFieldType = DataType::OTHER;
                sal_Int16 nKeyType	 = NumberFormat::UNDEFINED;
                sal_Bool bHaveFormat = sal_False;
                Reference<XPropertySet> xFieldAsSet(xDataField, UNO_QUERY);
                try
                {
                    xFieldAsSet->getPropertyValue(PROPERTY_FIELDTYPE) >>= nFieldType;
                    bHaveFormat = (xFieldAsSet->getPropertyValue(PROPERTY_FORMATKEY) >>= nFormatKey);
                }
                catch(Exception&)
                {
                    DBG_ERROR("OListBoxModel::loadData: could not obtain the field type and/or format key of the bound column!");
                }

                if (!bHaveFormat)
                {
                    Locale aAppLanguage = Application::GetSettings().GetUILocale();
                    if (xSupplier.is())
                    {
                        Reference< XNumberFormatTypes > xNumTypes(xSupplier->getNumberFormats(), UNO_QUERY);
                        if (xNumTypes.is())
                            nFormatKey = getDefaultNumberFormat(xFieldAsSet, xNumTypes, aAppLanguage);
                    }
                }

                Reference<XNumberFormatter> xFormatter;
                if (xSupplier.is())
                {
                    xFormatter = Reference<XNumberFormatter>(
                                    m_xServiceFactory->createInstance(FRM_NUMBER_FORMATTER),
                                    UNO_QUERY
                                );
                    if (xFormatter.is())
                    {
                        xFormatter->attachNumberFormatsSupplier(xSupplier);
                        xFormatter->getNumberFormatsSupplier()->getNumberFormatSettings()->getPropertyValue(
                            ::rtl::OUString::createFromAscii("NullDate")) >>= aNullDate;
                        nKeyType = getNumberFormatType(xFormatter->getNumberFormatsSupplier()->getNumberFormats(), nFormatKey);
                    }
                }

                // Feld der BoundColumn des ResultSets holen
                Reference<XColumn> xBoundField;
                if ((nBoundColumn > 0) && m_xColumn.is())
                    // don't look for a bound column if we're not connected to a field
                    xColumns->getByIndex(nBoundColumn) >>= xBoundField;
                m_bBoundComponent = xBoundField.is();

                //  Ist die LB an ein Feld gebunden und sind Leereintraege zulaessig
                //	dann wird die Position fuer einen Leereintrag gemerkt

                ::rtl::OUString aStr;
                sal_Int16 i = 0;
                // per definitionem the list cursor is positioned _before_ the first row at the moment
                while (xListCursor->next() && (i++<SHRT_MAX)) // max anzahl eintraege
                {
                    aStr = DBTypeConversion::getValue(xDataField,
                                            xFormatter,
                                            aNullDate,
                                            nFormatKey,
                                            nKeyType);

                    aStringList.push_back(aStr);

                    if (m_bBoundComponent)
                    {
                        aStr = xBoundField->getString();
                        aValueList.push_back(aStr);
                    }

                    if (bUseNULL && (m_nNULLPos == -1) && !aStr.getLength())
                        m_nNULLPos = (sal_Int16)aStringList.size() - 1;
                }
            }
            break;

            case ListSourceType_TABLEFIELDS:
            {
                Reference<XNameAccess> xFieldNames = getTableFields(xConnection, sListSource);
                if (xFieldNames.is())
                {
                    StringSequence seqNames = xFieldNames->getElementNames();
                    sal_Int32 nFieldsCount = seqNames.getLength();
                    const ::rtl::OUString* pustrNames = seqNames.getConstArray();

                    for (sal_Int32 k=0; k<nFieldsCount; ++k, ++pustrNames)
                        aStringList.push_back(*pustrNames);
                }
            }
            break;
        }
    }
    catch(SQLException& eSQL)
    {
        onError(eSQL, FRM_RES_STRING(RID_BASELISTBOX_ERROR_FILLLIST));
        disposeComponent(xListCursor);
        return;
    }
    catch(Exception& eUnknown)
    {
        eUnknown;
        disposeComponent(xListCursor);
        return;
    }


    // Value-Sequence erzeugen
    // NULL eintrag hinzufuegen
    if (bUseNULL && m_nNULLPos == -1)
    {
        if (m_bBoundComponent)
            aValueList.insert(aValueList.begin(), ::rtl::OUString());

        aStringList.insert(aStringList.begin(), ::rtl::OUString());
        m_nNULLPos = 0;
    }

    m_aValueSeq.realloc(aValueList.size());
    ::rtl::OUString* pustrValues = m_aValueSeq.getArray();
    for (i = 0; i < (sal_Int32)aValueList.size(); ++i)
        pustrValues[i] = aValueList[i];

    // String-Sequence fuer ListBox erzeugen
    StringSequence aStringSeq(aStringList.size());
    ::rtl::OUString* pustrStrings = aStringSeq.getArray();
    for (i = 0; i < (sal_Int32)aStringList.size(); ++i)
        pustrStrings[i] = aStringList[i];

    setFastPropertyValue(PROPERTY_ID_STRINGITEMLIST, makeAny(aStringSeq));


    // Statement + Cursor zerstoeren
    disposeComponent(xListCursor);
}

//------------------------------------------------------------------------------
void OListBoxModel::_loaded(const EventObject& rEvent)
{
    // an Felder gebundene Listboxen haben keine Multiselektion
    if (getField().is())
    {
        setFastPropertyValue(PROPERTY_ID_MULTISELECTION, ::cppu::bool2any((sal_False)));
    }

    if (m_eListSourceType != ListSourceType_VALUELIST)
    {
        if (getField().is())
            m_aValueSeq = StringSequence();

        if (m_xCursor.is())
            loadData();
    }
}

//------------------------------------------------------------------------------
void OListBoxModel::_unloaded()
{
    if (m_eListSourceType != ListSourceType_VALUELIST)
    {
        m_aValueSeq = StringSequence();
        m_nNULLPos = -1;
        m_bBoundComponent = sal_False;

        StringSequence aSequence;
        setFastPropertyValue(PROPERTY_ID_STRINGITEMLIST, makeAny(aSequence));
    }
}

//------------------------------------------------------------------------------
StringSequence OListBoxModel::GetCurValueSeq() const
{
    StringSequence aCurValues;

    // Aus den selektierten Indizes Werte-Sequence aufbauen
    DBG_ASSERT(m_xAggregateFastSet.is(), "OListBoxModel::GetCurValueSeq : invalid aggregate !");
    if (!m_xAggregateFastSet.is())
        return aCurValues;
    Any aTmp = m_xAggregateFastSet->getFastPropertyValue(OListBoxModel::nSelectHandle);

    Sequence<sal_Int16> aSelectSeq; aTmp >>= aSelectSeq;
    const sal_Int16 *pSels = aSelectSeq.getConstArray();
    sal_uInt32 nSelCount = aSelectSeq.getLength();

    if (nSelCount)
    {
        const ::rtl::OUString *pVals	= NULL;
        sal_Int32 nValCnt			= 0;
        if (m_aValueSeq.getLength())
        {
            pVals = m_aValueSeq.getConstArray();
            nValCnt = m_aValueSeq.getLength();
        }
        else
        {
            aTmp	= const_cast<OListBoxModel*>(this)->OPropertySetAggregationHelper::getFastPropertyValue(PROPERTY_ID_STRINGITEMLIST);
            pVals	= (*(StringSequence*)aTmp.getValue()).getConstArray();
            nValCnt = (*(StringSequence*)aTmp.getValue()).getLength();
        }

        if (nSelCount > 1)
        {
            // Einfach- oder Mehrfach-Selektion
            sal_Bool bMultiSel;
            const_cast<OListBoxModel*>(this)->OPropertySetAggregationHelper::getFastPropertyValue(PROPERTY_ID_MULTISELECTION) >>= bMultiSel;
            if (bMultiSel)
                nSelCount = 1;
        }

        // ist der Eintrag fuer NULL selektiert ?
        // dann leere Selektion liefern
        if (m_nNULLPos != -1 && nSelCount == 1 && pSels[0] == m_nNULLPos)
            nSelCount = 0;

        aCurValues.realloc(nSelCount);
        ::rtl::OUString *pCurVals = aCurValues.getArray();

        for (sal_uInt16 i = 0; i < nSelCount; i++)
        {
            if (pSels[i] < nValCnt)
                pCurVals[i] = pVals[pSels[i]];
        }
    }
    return aCurValues;
}

// XBoundComponent
//------------------------------------------------------------------------------
sal_Bool OListBoxModel::_commit()
{
    // derzeitige Selectionsliste
    Any aNewValue;
    StringSequence aCurValueSeq = GetCurValueSeq();
    if (aCurValueSeq.getLength())
        aNewValue <<= aCurValueSeq.getConstArray()[0];

    if (!compare(aNewValue, m_aSaveValue))
    {
        if (!aNewValue.hasValue())
            m_xColumnUpdate->updateNull();
        else
        {
            try
            {
                ::rtl::OUString sNewValue;
                aNewValue >>= sNewValue;
                m_xColumnUpdate->updateString(sNewValue);
            }
            catch(Exception&)
            {
                return sal_False;
            }
        }
        m_aSaveValue = aNewValue;
    }
    return sal_True;
}

// XPropertiesChangeListener
//------------------------------------------------------------------------------
void OListBoxModel::_onValueChanged()
{
    DBG_ASSERT(m_xAggregateFastSet.is() && m_xAggregateSet.is(), "OListBoxModel::_onValueChanged : invalid aggregate !");
    if (!m_xAggregateFastSet.is() || !m_xAggregateSet.is())
        return;

    Sequence<sal_Int16> aSelSeq;

    // Bei NULL-Eintraegen Selektion aufheben!
    ::rtl::OUString sValue = m_xColumn->getString();
    if (m_xColumn->wasNull())
    {
        m_aSaveValue.clear();
        if (m_nNULLPos != -1)
        {
            aSelSeq.realloc(1);
            aSelSeq.getArray()[0] = m_nNULLPos;
        }
    }
    else
    {
        m_aSaveValue <<= sValue;

        // In der Werteliste nur einzelne Werte suchen, wenn das Control mit einem Datenbankfeld verbunden ist
        if (m_aValueSeq.getLength())	// WerteListe
            aSelSeq = findValue(m_aValueSeq, sValue, m_bBoundComponent);
        else
        {
            StringSequence aStringSeq; m_xAggregateSet->getPropertyValue(PROPERTY_STRINGITEMLIST) >>= aStringSeq;
            aSelSeq = findValue(aStringSeq, sValue, m_bBoundComponent);
        }
    }
    Any aSelectAny;
    aSelectAny <<= aSelSeq;
    {	// release our mutex once (it's acquired in the calling method !), as setting aggregate properties
        // may cause any uno controls belonging to us to lock the solar mutex, which is potentially dangerous with
        // our own mutex locked
        // FS - 72451 - 31.01.00
        MutexRelease aRelease(m_aMutex);
        m_xAggregateFastSet->setFastPropertyValue(OListBoxModel::nSelectHandle, aSelectAny );
    }
}

// XReset
//------------------------------------------------------------------------------
void OListBoxModel::_reset( void )
{
    DBG_ASSERT(m_xAggregateFastSet.is() && m_xAggregateSet.is(), "OListBoxModel::reset : invalid aggregate !");
    if (!m_xAggregateFastSet.is() || !m_xAggregateSet.is())
        return;

    Any aValue;
    if (m_aDefaultSelectSeq.getLength())
        aValue <<= m_aDefaultSelectSeq;
    else if (m_nNULLPos != -1)	// gebundene Listbox
    {
        Sequence<sal_Int16> aSeq(1);
        aSeq.getArray()[0] = m_nNULLPos;
        aValue <<= aSeq;
    }
    else
    {
        Sequence<sal_Int16> aSeq;
        aValue <<= aSeq;
    }
    {	// release our mutex once (it's acquired in the calling method !), as setting aggregate properties
        // may cause any uno controls belonging to us to lock the solar mutex, which is potentially dangerous with
        // our own mutex locked
        // FS - 72451 - 31.01.00
        MutexRelease aRelease(m_aMutex);
        m_xAggregateFastSet->setFastPropertyValue(OListBoxModel::nSelectHandle, aValue);
    }
}

//==================================================================
// OListBoxControl
//==================================================================

//------------------------------------------------------------------
InterfaceRef SAL_CALL OListBoxControl_CreateInstance(const Reference<XMultiServiceFactory>& _rxFactory) throw (RuntimeException)
{
    return *(new OListBoxControl(_rxFactory));
}

//------------------------------------------------------------------------------
Sequence< Type> OListBoxControl::_getTypes()
{
    static Sequence< Type> aTypes;
    if (!aTypes.getLength())
        aTypes = concatSequences(OBoundControl::_getTypes(), OListBoxControl_BASE::getTypes());
    return aTypes;
}

//------------------------------------------------------------------
Any SAL_CALL OListBoxControl::queryAggregation(const Type& _rType) throw (RuntimeException)
{
    Any aReturn = OBoundControl::queryAggregation(_rType);
    if (!aReturn.hasValue())
        aReturn = OListBoxControl_BASE::queryInterface(_rType);

    return aReturn;
}

DBG_NAME(OListBoxControl)
//------------------------------------------------------------------------------
OListBoxControl::OListBoxControl(const Reference<XMultiServiceFactory>& _rxFactory)
                  :OBoundControl(_rxFactory, VCL_CONTROL_LISTBOX)
                  ,m_aChangeListeners(m_aMutex)
{
    DBG_CTOR(OListBoxControl,NULL);

    increment(m_refCount);
    {
        // als FocusListener anmelden
        Reference<XWindow> xComp;
        if (query_aggregation(m_xAggregate, xComp))
            xComp->addFocusListener(this);

        // als ItemListener anmelden
        Reference<XListBox> xListbox;
        if (query_aggregation(m_xAggregate, xListbox))
            xListbox->addItemListener(this);
    }
    // Refcount bei 2 fuer angemeldete Listener
    decrement(m_refCount);

    m_aChangeTimer.SetTimeout(500);
    m_aChangeTimer.SetTimeoutHdl(LINK(this,OListBoxControl,OnTimeout));
}

//------------------------------------------------------------------------------
OListBoxControl::~OListBoxControl()
{
    if (!OComponentHelper::rBHelper.bDisposed)
    {
        acquire();
        dispose();
    }

    DBG_DTOR(OListBoxControl,NULL);
}

//------------------------------------------------------------------------------
StringSequence SAL_CALL OListBoxControl::getSupportedServiceNames() throw(RuntimeException)
{
    StringSequence aSupported = OBoundControl::getSupportedServiceNames();
    aSupported.realloc(aSupported.getLength() + 1);

    ::rtl::OUString* pArray = aSupported.getArray();
    pArray[aSupported.getLength()-1] = FRM_SUN_CONTROL_LISTBOX;
    return aSupported;
}


// XFocusListener
//------------------------------------------------------------------------------
void SAL_CALL OListBoxControl::focusGained(const FocusEvent& _rEvent) throw(RuntimeException)
{
    ::osl::MutexGuard aGuard(m_aMutex);
    if (m_aChangeListeners.getLength()) // only if there are listeners
    {
        Reference<XPropertySet> xSet(getModel(), UNO_QUERY);
        if (xSet.is())
        {
            // memorize the current selection for posting the change event
            m_aCurrentSelection = xSet->getPropertyValue(PROPERTY_SELECT_SEQ);
        }
    }
}

//------------------------------------------------------------------------------
void SAL_CALL OListBoxControl::focusLost(const FocusEvent& _rEvent) throw(RuntimeException)
{
    m_aCurrentSelection.clear();
}

// XItemListener
//------------------------------------------------------------------------------
void SAL_CALL OListBoxControl::itemStateChanged(const ItemEvent& _rEvent) throw(RuntimeException)
{
   // call the changelistener delayed
   ::osl::ClearableMutexGuard aGuard(m_aMutex);
   if (m_aChangeTimer.IsActive())
   {
        Reference<XPropertySet> xSet(getModel(), UNO_QUERY);
        m_aCurrentSelection = xSet->getPropertyValue(PROPERTY_SELECT_SEQ);

        m_aChangeTimer.Stop();
        m_aChangeTimer.Start();
   }
   else
   {
       if (m_aChangeListeners.getLength() && m_aCurrentSelection.hasValue())
       {
            Reference<XPropertySet> xSet(getModel(), UNO_QUERY);
            if (xSet.is())
            {
                // Has the selection been changed?
                sal_Bool bModified(sal_False);
                Any aValue = xSet->getPropertyValue(PROPERTY_SELECT_SEQ);

                Sequence<sal_Int16>& rSelection = *(Sequence<sal_Int16> *)aValue.getValue();
                Sequence<sal_Int16>& rOldSelection = *(Sequence<sal_Int16> *)m_aCurrentSelection.getValue();
                sal_Int32 nLen = rSelection.getLength();
                if (nLen != rOldSelection.getLength())
                    bModified = sal_True;
                else
                {
                    const sal_Int16* pVal = rSelection.getConstArray();
                    const sal_Int16* pCompVal = rOldSelection.getConstArray();

                    while (nLen-- && !bModified)
                        bModified = pVal[nLen] != pCompVal[nLen];
                }

                if (bModified)
                {
                    m_aCurrentSelection = aValue;
                    m_aChangeTimer.Start();
                }
            }
        }
        else if (m_aCurrentSelection.hasValue())
            m_aCurrentSelection.clear();
   }
}

// XEventListener
//------------------------------------------------------------------------------
void SAL_CALL OListBoxControl::disposing(const EventObject& _rSource) throw (RuntimeException)
{
    OBoundControl::disposing(_rSource);
}

// XChangeBroadcaster
//------------------------------------------------------------------------------
void SAL_CALL OListBoxControl::addChangeListener(const Reference<XChangeListener>& _rxListener) throw(RuntimeException)
{
    m_aChangeListeners.addInterface(_rxListener);
}

//------------------------------------------------------------------------------
void SAL_CALL OListBoxControl::removeChangeListener(const Reference<XChangeListener>& _rxListener) throw(RuntimeException)
{
    m_aChangeListeners.removeInterface(_rxListener);
}

// OComponentHelper
//------------------------------------------------------------------------------
void OListBoxControl::disposing()
{
    if (m_aChangeTimer.IsActive())
        m_aChangeTimer.Stop();

    EventObject aEvt(static_cast< XWeak*>(this));
    m_aChangeListeners.disposeAndClear(aEvt);

    OBoundControl::disposing();
}

//------------------------------------------------------------------------------
IMPL_LINK(OListBoxControl, OnTimeout, void*, EMPTYTAG)
{
    EventObject aEvt(static_cast< XWeak*>(this));
    m_aChangeListeners.notifyEach(&XChangeListener::changed, aEvt);
    return 1;
}

//.........................................................................
}
//.........................................................................

}
