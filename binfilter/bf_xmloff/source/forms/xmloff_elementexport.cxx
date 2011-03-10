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

#include <stdio.h>

#include <sal/macros.h>
#include <xmlexp.hxx>
#include "elementexport.hxx"
#include "xmluconv.hxx"
#include <comphelper/extract.hxx>
#include "eventexport.hxx"
#include <com/sun/star/io/XPersistObject.hpp>
#include <com/sun/star/form/FormComponentType.hpp>
#include "formenums.hxx"
#include <com/sun/star/form/FormSubmitEncoding.hpp>
#include <com/sun/star/form/FormSubmitMethod.hpp>
#include <com/sun/star/sdb/CommandType.hpp>
#include <com/sun/star/form/NavigationBarMode.hpp>
#include <com/sun/star/form/TabulatorCycle.hpp>
#include <com/sun/star/form/FormButtonType.hpp>
#include <com/sun/star/form/ListSourceType.hpp>
#include <tools/wintypes.hxx>		// for check states
#include "XMLEventExport.hxx"
#include <xmlnmspe.hxx>
#ifndef XMLOFF_FORMS_FORMCELLBINDING
#include "formcellbinding.hxx"
#endif

#include <drafts/com/sun/star/form/XListEntrySink.hpp>

#include <algorithm>
namespace binfilter {


//.........................................................................
namespace xmloff
{
//.........................................................................

    using namespace ::com::sun::star::uno;
    using namespace ::com::sun::star::sdb;
    using namespace ::com::sun::star::form;
    using namespace ::com::sun::star::lang;
    using namespace ::com::sun::star::lang;
    using namespace ::com::sun::star::beans;
    using namespace ::com::sun::star::container;
    using namespace ::com::sun::star::script;
    using namespace ::com::sun::star::io;
    using namespace ::com::sun::star::table;
    using namespace ::drafts::com::sun::star::form;

    //=====================================================================
    //= OElementExport
    //=====================================================================
    OElementExport::OElementExport(IFormsExportContext& _rContext, const Reference< XPropertySet >& _rxProps,
        const Sequence< ScriptEventDescriptor >& _rEvents)
        :OPropertyExport(_rContext, _rxProps)
        ,m_aEvents(_rEvents)
        ,m_pXMLElement(NULL)
    {
    }

    //---------------------------------------------------------------------
    OElementExport::~OElementExport()
    {
        implEndElement();
    }

    //---------------------------------------------------------------------
    void OElementExport::doExport()
    {
        // collect some general information about the element
        examine();

        // first add the attributes necessary for the element
        m_rContext.getGlobalContext().ClearAttrList();

        // add the attributes
        exportAttributes();

        // start the XML element
        implStartElement(getXMLElementName());

        // the sub elements (mostly control type dependent)
        exportSubTags();

        implEndElement();
    }

    //---------------------------------------------------------------------
    void OElementExport::examine()
    {
        // nothing to do here
    }

    //---------------------------------------------------------------------
    void OElementExport::exportAttributes()
    {
        // nothing to do here
    }

    //---------------------------------------------------------------------
    void OElementExport::exportSubTags()
    {
        // the properties which where not exported 'til now
        exportRemainingProperties();

        // the script:events sub tags
        exportEvents();
    }

    //---------------------------------------------------------------------
    void OElementExport::implStartElement(const sal_Char* _pName)
    {
        m_pXMLElement = new SvXMLElementExport(m_rContext.getGlobalContext(), XML_NAMESPACE_FORM, _pName, sal_True, sal_True);
    }

    //---------------------------------------------------------------------
    void OElementExport::implEndElement()
    {
        delete m_pXMLElement;
        m_pXMLElement = NULL;
    }

    //---------------------------------------------------------------------
    void OElementExport::exportServiceNameAttribute()
    {
        Reference< XPersistObject > xPersistence(m_xProps, UNO_QUERY);
        if (!xPersistence.is())
        {
            OSL_ENSURE(sal_False, "OElementExport::exportServiceNameAttribute: no XPersistObject!");
            return;
        }

        ::rtl::OUString sServiceName = xPersistence->getServiceName();
        // we don't want to write the old service name directly: it's a name used for compatibility reasons, but
        // as we start some kind of new file format here (with this xml export), we don't care about
        // compatibility ...
        // So we translate the old persistence service name into new ones, if possible

        ::rtl::OUString sToWriteServiceName = sServiceName;
#define CHECK_N_TRANSLATE( name )	\
        else if (0 == sServiceName.compareToAscii(SERVICE_PERSISTENT_COMPONENT_##name))	\
            sToWriteServiceName = SERVICE_##name

        if (sal_False)
            ;
        CHECK_N_TRANSLATE( FORM );
        CHECK_N_TRANSLATE( FORM );
        CHECK_N_TRANSLATE( LISTBOX );
        CHECK_N_TRANSLATE( COMBOBOX );
        CHECK_N_TRANSLATE( RADIOBUTTON );
        CHECK_N_TRANSLATE( GROUPBOX );
        CHECK_N_TRANSLATE( FIXEDTEXT );
        CHECK_N_TRANSLATE( COMMANDBUTTON );
        CHECK_N_TRANSLATE( CHECKBOX );
        CHECK_N_TRANSLATE( GRID );
        CHECK_N_TRANSLATE( IMAGEBUTTON );
        CHECK_N_TRANSLATE( FILECONTROL );
        CHECK_N_TRANSLATE( TIMEFIELD );
        CHECK_N_TRANSLATE( DATEFIELD );
        CHECK_N_TRANSLATE( NUMERICFIELD );
        CHECK_N_TRANSLATE( CURRENCYFIELD );
        CHECK_N_TRANSLATE( PATTERNFIELD );
        CHECK_N_TRANSLATE( HIDDENCONTROL );
        CHECK_N_TRANSLATE( IMAGECONTROL );
        CHECK_N_TRANSLATE( FORMATTEDFIELD );
        else if (0 == sServiceName.compareToAscii(SERVICE_PERSISTENT_COMPONENT_EDIT))
        {	// special handling for the edit field: we have two controls using this as persistence service name
            sToWriteServiceName = SERVICE_EDIT;
            Reference< XServiceInfo > xSI(m_xProps, UNO_QUERY);
            if (xSI.is() && xSI->supportsService(SERVICE_FORMATTEDFIELD))
                sToWriteServiceName = SERVICE_FORMATTEDFIELD;
        }
#ifdef DBG_UTIL
        Reference< XServiceInfo > xSI(m_xProps, UNO_QUERY);
        OSL_ENSURE(xSI.is() && xSI->supportsService(sToWriteServiceName),
            "OElementExport::exportServiceNameAttribute: wrong service name translation!");

#endif

        // now write this
        AddAttribute(
            getCommonControlAttributeNamespace(CCA_SERVICE_NAME),
            getCommonControlAttributeName(CCA_SERVICE_NAME),
            sToWriteServiceName);
    }

    //---------------------------------------------------------------------
    void OElementExport::exportEvents()
    {
        if (!m_aEvents.getLength())
            // nothing to do
            return;

        Reference< XNameReplace > xWrapper = new OEventDescriptorMapper(m_aEvents);
        m_rContext.getGlobalContext().GetEventExport().Export(xWrapper);
    }

    //=====================================================================
    //= OControlExport
    //=====================================================================
    //---------------------------------------------------------------------
    OControlExport::OControlExport(IFormsExportContext& _rContext,  const Reference< XPropertySet >& _rxControl,
        const ::rtl::OUString& _rControlId, const ::rtl::OUString& _rReferringControls,
        const Sequence< ScriptEventDescriptor >& _rEvents)
        :OElementExport(_rContext, _rxControl, _rEvents)
        ,m_sControlId(_rControlId)
        ,m_sReferringControls(_rReferringControls)
        ,m_nClassId(FormComponentType::CONTROL)
        ,m_nIncludeCommon(0)
        ,m_nIncludeDatabase(0)
        ,m_nIncludeSpecial(0)
        ,m_nIncludeEvents(0)
        ,m_nIncludeBindings(0)
        ,m_pOuterElement(NULL)
    {
        OSL_ENSURE(m_xProps.is(), "OControlExport::OControlExport: invalid arguments!");
    }

    //---------------------------------------------------------------------
    OControlExport::~OControlExport()
    {
        implEndElement();
    }

    //---------------------------------------------------------------------
    void OControlExport::exportOuterAttributes()
    {
        // the control id
        if (CCA_NAME & m_nIncludeCommon)
        {
            exportStringPropertyAttribute(
                getCommonControlAttributeNamespace(CCA_NAME),
                getCommonControlAttributeName(CCA_NAME),
                PROPERTY_NAME
                );
        #ifdef DBG_UTIL
            //  reset the bit for later checking
            m_nIncludeCommon = m_nIncludeCommon & ~CCA_NAME;
        #endif
        }

        // the service name
        if (m_nIncludeCommon & CCA_SERVICE_NAME)
        {
            exportServiceNameAttribute();
        #ifdef DBG_UTIL
            //  reset the bit for later checking
            m_nIncludeCommon = m_nIncludeCommon & ~CCA_SERVICE_NAME;
        #endif
        }

        // the control id
        if (CCA_CONTROL_ID & m_nIncludeCommon)
        {
            OSL_ENSURE(m_sControlId.getLength(), "OControlExport::exportCommonControlAttributes: have no control id for the control!");
            AddAttribute(
                getCommonControlAttributeNamespace(CCA_CONTROL_ID),
                getCommonControlAttributeName(CCA_CONTROL_ID),
                m_sControlId);
        #ifdef DBG_UTIL
            //  reset the bit for later checking
            m_nIncludeCommon = m_nIncludeCommon & ~CCA_CONTROL_ID;
        #endif
        }
    }

    //---------------------------------------------------------------------
    void OControlExport::exportInnerAttributes()
    {
        // common control attributes
        exportCommonControlAttributes();

        // common database attributes
        exportDatabaseAttributes();

        // attributes related to external bindings
        exportBindingAtributes();

        // attributes special to the respective control type
        exportSpecialAttributes();

        // add the style references to the attributes
        flagStyleProperties();
    }

    //---------------------------------------------------------------------
    void OControlExport::exportAttributes()
    {
        exportOuterAttributes();
    }

    //---------------------------------------------------------------------
    void OControlExport::exportSubTags() throw (Exception)
    {
        // the ListSource related properties do not need to be exported in a generic way, exportListSourceAsElements
        // will handle this (if necessary)
        exportedProperty(PROPERTY_STRING_ITEM_LIST);
        exportedProperty(PROPERTY_VALUE_SEQ);
        exportedProperty(PROPERTY_SELECT_SEQ);
        exportedProperty(PROPERTY_DEFAULT_SELECT_SEQ);
        exportedProperty(PROPERTY_LISTSOURCE);

        // for the upcoming exportRemainingProperties:
        // if a control has the LabelControl property, this is not stored with the control itself, but instead with
        // the control which is referenced by this property. As the base class' exportRemainingProperties doesn't
        // know anything about this, we need to prevent that it tries to export this property
        exportedProperty(PROPERTY_CONTROLLABEL);

        // let the base class export the remaining properties and the events
        OElementExport::exportSubTags();

        // special sub tags for some controls
        switch (m_eType)
        {
            case LISTBOX:
                // a list box description has sub elements: the options
                exportListSourceAsElements();
                break;
            case GRID:
            {	// a grid control requires us to store all columns as sub elements
                Reference< XIndexAccess > xColumnContainer(m_xProps, UNO_QUERY);
                OSL_ENSURE(xColumnContainer.is(), "OControlExport::exportSubTags: a grid control which is no IndexAccess?!!");
                if (xColumnContainer.is())
                    m_rContext.exportCollectionElements(xColumnContainer);
            }
            break;
            case COMBOBOX:
            {	// a combox box description has sub elements: the items
                DBG_CHECK_PROPERTY( PROPERTY_STRING_ITEM_LIST, Sequence< ::rtl::OUString > );

                // get the item list
                Sequence< ::rtl::OUString > aListItems;
                m_xProps->getPropertyValue(PROPERTY_STRING_ITEM_LIST) >>= aListItems;
                // loop through it and write the sub elements
                const ::rtl::OUString* pListItems = aListItems.getConstArray();
                for (sal_Int32 i=0; i<aListItems.getLength(); ++i, ++pListItems)
                {
                    m_rContext.getGlobalContext().ClearAttrList();
                    AddAttribute(
                        getCommonControlAttributeNamespace(CCA_LABEL),
                        getCommonControlAttributeName(CCA_LABEL),
                        *pListItems);
                    SvXMLElementExport aFormElement(m_rContext.getGlobalContext(), XML_NAMESPACE_FORM, "item", sal_True, sal_True);
                }
            }
            break;
            default:
            break;
        }
    }

    //---------------------------------------------------------------------
    void OControlExport::exportCommonControlAttributes()
    {
        // I decided to handle all the properties here with some static arrays describing the property-attribute
        // relations. This leads to somewhat ugly code :), but the only alternative I can think of right now
        // would require maps and O(log n) searches, which seems somewhat expensive as this code is used
        // very frequently.

        // the extra indents for the respective blocks are to ensure that there is no copy'n'paste error, using
        // map identifiers from the wrong block

        // --------------------------------------------------------------------
        // some string properties
        {
            // the attribute ids of all properties which are expected to be of type string
            static sal_Int32 nStringPropertyAttributeIds[] =
            {
                CCA_LABEL, CCA_TITLE
            };
            // the names of all properties which are expected to be of type string
            static ::rtl::OUString aStringPropertyNames[] =
            {
                PROPERTY_LABEL, PROPERTY_TITLE
            };
            OSL_ENSURE( SAL_N_ELEMENTS(aStringPropertyNames) == SAL_N_ELEMENTS(nStringPropertyAttributeIds),
                        "OControlExport::exportCommonControlAttributes: somebody tampered with the maps (1)!");

            for (size_t i = 0; i < SAL_N_ELEMENTS(nStringPropertyAttributeIds); ++i)
                if (nStringPropertyAttributeIds[i] & m_nIncludeCommon)
                {
                    exportStringPropertyAttribute(
                        getCommonControlAttributeNamespace(nStringPropertyAttributeIds[i]),
                        getCommonControlAttributeName(nStringPropertyAttributeIds[i]),
                        aStringPropertyNames[i]
                        );
                #ifdef DBG_UTIL
                    //  reset the bit for later checking
                    m_nIncludeCommon = m_nIncludeCommon & ~nStringPropertyAttributeIds[i];
                #endif
                }
        }

        // --------------------------------------------------------------------
        // some boolean properties
        {
            static sal_Int32 nBooleanPropertyAttributeIds[] =
            {	// attribute flags
                CCA_CURRENT_SELECTED, CCA_DISABLED, CCA_DROPDOWN, CCA_PRINTABLE, CCA_READONLY, CCA_SELECTED, CCA_TAB_STOP
            };
            static const ::rtl::OUString* pBooleanPropertyNames[] =
            {	// property names
                &PROPERTY_STATE, &PROPERTY_ENABLED, &PROPERTY_DROPDOWN, &PROPERTY_PRINTABLE, &PROPERTY_READONLY, &PROPERTY_DEFAULT_STATE, &PROPERTY_TABSTOP
            };
            static sal_Bool nBooleanPropertyAttrFlags[] =
            {	// attribute defaults
                BOOLATTR_DEFAULT_FALSE, BOOLATTR_DEFAULT_FALSE | BOOLATTR_INVERSE_SEMANTICS, BOOLATTR_DEFAULT_FALSE, BOOLATTR_DEFAULT_TRUE, BOOLATTR_DEFAULT_FALSE, BOOLATTR_DEFAULT_FALSE, BOOLATTR_DEFAULT_VOID
            };
        #ifdef DBG_UTIL
            sal_Int32 nIdCount = SAL_N_ELEMENTS(nBooleanPropertyAttributeIds);
            sal_Int32 nNameCount = SAL_N_ELEMENTS(pBooleanPropertyNames);
            sal_Int32 nFlagsCount = SAL_N_ELEMENTS(nBooleanPropertyAttrFlags);
            OSL_ENSURE((nIdCount == nNameCount) && (nNameCount == nFlagsCount),
                "OControlExport::exportCommonControlAttributes: somebody tampered with the maps (2)!");
        #endif
            for (size_t i=0; i<SAL_N_ELEMENTS(nBooleanPropertyAttributeIds); ++i)
                if (nBooleanPropertyAttributeIds[i] & m_nIncludeCommon)
                {
                    exportBooleanPropertyAttribute(
                        getCommonControlAttributeNamespace(nBooleanPropertyAttributeIds[i]),
                        getCommonControlAttributeName(nBooleanPropertyAttributeIds[i]),
                        *(pBooleanPropertyNames[i]),
                        nBooleanPropertyAttrFlags[i]);
        #ifdef DBG_UTIL
                    //  reset the bit for later checking
                    m_nIncludeCommon = m_nIncludeCommon & ~nBooleanPropertyAttributeIds[i];
        #endif
                }
        }


        // --------------------------------------------------------------------
        // some integer properties
        {
            // now the common handling
            static sal_Int32 nIntegerPropertyAttributeIds[] =
            {	// attribute flags
                CCA_SIZE, CCA_TAB_INDEX
            };
            static const ::rtl::OUString* pIntegerPropertyNames[] =
            {	// property names
                &PROPERTY_LINECOUNT, &PROPERTY_TABINDEX
            };
            static const sal_Int16 nIntegerPropertyAttrDefaults[] =
            {	// attribute defaults
                5, 0
            };

            if ( m_nIncludeCommon & CCA_MAX_LENGTH )
                exportedProperty(PROPERTY_MAXTEXTLENGTH);

        #ifdef DBG_UTIL
            sal_Int32 nIdCount = SAL_N_ELEMENTS(nIntegerPropertyAttributeIds);
            sal_Int32 nNameCount = SAL_N_ELEMENTS(pIntegerPropertyNames);
            sal_Int32 nDefaultCount = SAL_N_ELEMENTS(nIntegerPropertyAttrDefaults);
            OSL_ENSURE((nIdCount == nNameCount) && (nNameCount == nDefaultCount),
                "OControlExport::exportCommonControlAttributes: somebody tampered with the maps (3)!");
        #endif
            for (size_t i=0; i<SAL_N_ELEMENTS(nIntegerPropertyAttributeIds); ++i)
                if (nIntegerPropertyAttributeIds[i] & m_nIncludeCommon)
                {
                    exportInt16PropertyAttribute(
                        getCommonControlAttributeNamespace(nIntegerPropertyAttributeIds[i]),
                        getCommonControlAttributeName(nIntegerPropertyAttributeIds[i]),
                        *(pIntegerPropertyNames[i]),
                        nIntegerPropertyAttrDefaults[i]);
        #ifdef DBG_UTIL
                    //  reset the bit for later checking
                    m_nIncludeCommon = m_nIncludeCommon & ~nIntegerPropertyAttributeIds[i];
        #endif
                }


        }

        // --------------------------------------------------------------------
        // some enum properties
        {
            // (only one a at the moment)
            if (m_nIncludeCommon & CCA_BUTTON_TYPE)
            {
                exportEnumPropertyAttribute(
                    getCommonControlAttributeNamespace(CCA_BUTTON_TYPE),
                    getCommonControlAttributeName(CCA_BUTTON_TYPE),
                    PROPERTY_BUTTONTYPE,
                    OEnumMapper::getEnumMap(OEnumMapper::epButtonType),
                    FormButtonType_PUSH);
        #ifdef DBG_UTIL
                //  reset the bit for later checking
                m_nIncludeCommon = m_nIncludeCommon & ~CCA_BUTTON_TYPE;
        #endif
            }
        }

        // --------------------------------------------------------------------
        // some properties which require a special handling

        // the target frame
        if (m_nIncludeCommon & CCA_TARGET_FRAME)
        {
            exportTargetFrameAttribute();
        #ifdef DBG_UTIL
            //  reset the bit for later checking
            m_nIncludeCommon = m_nIncludeCommon & ~CCA_TARGET_FRAME;
        #endif
        }

        // max text length
        if ( m_nIncludeCommon & CCA_MAX_LENGTH )
        {
            // normally, the respective property would be "MaxTextLen"
            // However, if the model has a property "PersistenceMaxTextLength", then we prefer this

            // determine the name of the property to export
            ::rtl::OUString sTextLenPropertyName = PROPERTY_MAXTEXTLENGTH;
            if ( m_xPropertyInfo->hasPropertyByName( PROPERTY_PERSISTENCE_MAXTEXTLENGTH ) )
                sTextLenPropertyName = PROPERTY_PERSISTENCE_MAXTEXTLENGTH;

            // export it
            exportInt16PropertyAttribute(
                getCommonControlAttributeNamespace( CCA_MAX_LENGTH ),
                getCommonControlAttributeName( CCA_MAX_LENGTH ),
                sTextLenPropertyName,
                0
            );

            // in either way, both properties count as "exported"
            exportedProperty( PROPERTY_MAXTEXTLENGTH );
            exportedProperty( PROPERTY_PERSISTENCE_MAXTEXTLENGTH );

        #ifdef DBG_UTIL
            //  reset the bit for later checking
            m_nIncludeCommon = m_nIncludeCommon & ~CCA_MAX_LENGTH;
        #endif
        }

        if (m_nIncludeCommon & CCA_TARGET_LOCATION)
        {
            exportTargetLocationAttribute();
        #ifdef DBG_UTIL
            //  reset the bit for later checking
            m_nIncludeCommon = m_nIncludeCommon & ~CCA_TARGET_LOCATION;
        #endif
        }

        // OJ #99721#
        if (m_nIncludeCommon & CCA_IMAGE_DATA)
        {
            exportImageDataAttribute();
        #ifdef DBG_UTIL
            //  reset the bit for later checking
            m_nIncludeCommon = m_nIncludeCommon & ~CCA_IMAGE_DATA;
        #endif
        }

        // the for attribute
        // the target frame
        if (m_nIncludeCommon & CCA_FOR)
        {
            if (m_sReferringControls.getLength())
            {	// there is at least one control referring to the one we're handling currently
                AddAttribute(
                    getCommonControlAttributeNamespace(CCA_FOR),
                    getCommonControlAttributeName(CCA_FOR),
                    m_sReferringControls);
            }
        #ifdef DBG_UTIL
            //  reset the bit for later checking
            m_nIncludeCommon = m_nIncludeCommon & ~CCA_FOR;
        #endif
        }

        if ((CCA_CURRENT_VALUE | CCA_VALUE) & m_nIncludeCommon)
        {
            const sal_Char* pCurrentValuePropertyName = NULL;
            const sal_Char* pValuePropertyName = NULL;

            // get the property names
            getValuePropertyNames(m_eType, m_nClassId, pCurrentValuePropertyName, pValuePropertyName);

            static const sal_Char* pCurrentValueAttributeName = getCommonControlAttributeName(CCA_CURRENT_VALUE);
            static const sal_Char* pValueAttributeName = getCommonControlAttributeName(CCA_VALUE);
            static const sal_uInt16 nCurrentValueAttributeNamespaceKey = getCommonControlAttributeNamespace(CCA_CURRENT_VALUE);
            static const sal_uInt16 nValueAttributeNamespaceKey = getCommonControlAttributeNamespace(CCA_VALUE);

            // add the atrtributes if necessary and possible
            if (pCurrentValuePropertyName && (CCA_CURRENT_VALUE & m_nIncludeCommon))
                exportGenericPropertyAttribute(
                    nCurrentValueAttributeNamespaceKey,
                    pCurrentValueAttributeName,
                    pCurrentValuePropertyName);

            if (pValuePropertyName && (CCA_VALUE & m_nIncludeCommon))
                exportGenericPropertyAttribute(
                    nValueAttributeNamespaceKey,
                    pValueAttributeName,
                    pValuePropertyName);

            OSL_ENSURE((NULL == pValuePropertyName) == (0 == (CCA_VALUE & m_nIncludeCommon)),
                "OControlExport::exportCommonControlAttributes: no property found for the value attribute!");
            OSL_ENSURE((NULL == pCurrentValuePropertyName ) == (0 == (CCA_CURRENT_VALUE & m_nIncludeCommon)),
                "OControlExport::exportCommonControlAttributes: no property found for the current-value attribute!");

        #ifdef DBG_UTIL
            //  reset the bit for later checking
            m_nIncludeCommon = m_nIncludeCommon & ~(CCA_CURRENT_VALUE | CCA_VALUE);
        #endif
        }

        OSL_ENSURE(0 == m_nIncludeCommon,
            "OControlExport::exportCommonControlAttributes: forgot some flags!");
            // in the dbg_util version, we should have removed every bit we handled from the mask, so it should
            // be 0 now ...
    }

    //---------------------------------------------------------------------
    void OControlExport::exportDatabaseAttributes()
    {
#if OSL_DEBUG_LEVEL > 0
        sal_Int32 nIncludeDatabase = m_nIncludeDatabase;
#endif
        // the only string property: DataField
        if (DA_DATA_FIELD & m_nIncludeDatabase)
        {
            exportStringPropertyAttribute(
                getDatabaseAttributeNamespace(DA_DATA_FIELD),
                getDatabaseAttributeName(DA_DATA_FIELD),
                PROPERTY_DATAFIELD);
        #if OSL_DEBUG_LEVEL > 0
            //  reset the bit for later checking
            nIncludeDatabase = nIncludeDatabase & ~DA_DATA_FIELD;
        #endif
        }

        // the only int16 property: BoundColumn
        if (DA_BOUND_COLUMN & m_nIncludeDatabase)
        {
            exportInt16PropertyAttribute(
                getDatabaseAttributeNamespace(DA_BOUND_COLUMN),
                getDatabaseAttributeName(DA_BOUND_COLUMN),
                PROPERTY_BOUNDCOLUMN,
                0);
        #if OSL_DEBUG_LEVEL > 0
            //  reset the bit for later checking
            nIncludeDatabase = nIncludeDatabase & ~DA_BOUND_COLUMN;
        #endif
        }

        // the only boolean property: ConvertEmptyToNull
        if (DA_CONVERT_EMPTY & m_nIncludeDatabase)
        {
            exportBooleanPropertyAttribute(
                getDatabaseAttributeNamespace(DA_CONVERT_EMPTY),
                getDatabaseAttributeName(DA_CONVERT_EMPTY),
                PROPERTY_EMPTY_IS_NULL,
                BOOLATTR_DEFAULT_FALSE
                );
        #if OSL_DEBUG_LEVEL > 0
            //  reset the bit for later checking
            nIncludeDatabase = nIncludeDatabase & ~DA_CONVERT_EMPTY;
        #endif
        }

        // the only enum property: ListSourceType
        if (DA_LIST_SOURCE_TYPE & m_nIncludeDatabase)
        {
            exportEnumPropertyAttribute(
                getDatabaseAttributeNamespace(DA_LIST_SOURCE_TYPE),
                getDatabaseAttributeName(DA_LIST_SOURCE_TYPE),
                PROPERTY_LISTSOURCETYPE,
                OEnumMapper::getEnumMap(OEnumMapper::epListSourceType),
                ListSourceType_VALUELIST
                );
        #if OSL_DEBUG_LEVEL > 0
            //  reset the bit for later checking
            nIncludeDatabase = nIncludeDatabase & ~DA_LIST_SOURCE_TYPE;
        #endif
        }

        if (m_nIncludeDatabase & DA_LIST_SOURCE)
        {
            exportListSourceAsAttribute();
        #if OSL_DEBUG_LEVEL > 0
            //  reset the bit for later checking
            nIncludeDatabase = nIncludeDatabase & ~DA_LIST_SOURCE;
        #endif
        }

#if OSL_DEBUG_LEVEL > 0
        OSL_ENSURE(0 == nIncludeDatabase,
            "OControlExport::exportDatabaseAttributes: forgot some flags!");
            // in the dbg_util version, we should have removed every bit we handled from the mask, so it should
            // be 0 now ...
#endif
    }

    //---------------------------------------------------------------------
    void OControlExport::exportBindingAtributes()
    {
#if OSL_DEBUG_LEVEL > 0
        sal_Int32 nIncludeBinding = m_nIncludeBindings;
#endif

        // ....................................................
        if ( m_nIncludeBindings & BA_LINKED_CELL )
        {
            exportCellBindingAttributes( ( m_nIncludeBindings & BA_LIST_LINKING_TYPE ) != 0 );
        #if OSL_DEBUG_LEVEL > 0
            //  reset the bit for later checking
            nIncludeBinding = nIncludeBinding & ~( BA_LINKED_CELL | BA_LIST_LINKING_TYPE );
        #endif
        }

        // ....................................................
        if ( m_nIncludeBindings & BA_LIST_CELL_RANGE )
        {
            exportCellListSourceRange();
        #if OSL_DEBUG_LEVEL > 0
            //  reset the bit for later checking
            nIncludeBinding = nIncludeBinding & ~BA_LIST_CELL_RANGE;
        #endif
        }


        OSL_ENSURE( 0 == nIncludeBinding,
            "OControlExport::exportBindingAtributes: forgot some flags!");
            // in the debug version, we should have removed every bit we handled from the mask, so it should
            // be 0 now ...
    }

    //---------------------------------------------------------------------
    void OControlExport::exportSpecialAttributes()
    {
        sal_Int32 i=0;

        // ----------------------
        // the boolean properties
        {
            static sal_Int32 nBooleanPropertyAttributeIds[] =
            {	// attribute flags
                SCA_VALIDATION, SCA_MULTI_LINE, SCA_AUTOMATIC_COMPLETION, SCA_MULTIPLE, SCA_DEFAULT_BUTTON, SCA_IS_TRISTATE
            };
            static const ::rtl::OUString* pBooleanPropertyNames[] =
            {	// property names
                &PROPERTY_STRICTFORMAT, &PROPERTY_MULTILINE, &PROPERTY_AUTOCOMPLETE, &PROPERTY_MULTISELECTION, &PROPERTY_DEFAULTBUTTON, &PROPERTY_TRISTATE
            };
            sal_Int32 nIdCount = SAL_N_ELEMENTS(nBooleanPropertyAttributeIds);
        #ifdef DBG_UTIL
            sal_Int32 nNameCount = SAL_N_ELEMENTS(pBooleanPropertyNames);
            OSL_ENSURE((nIdCount == nNameCount),
                "OControlExport::exportSpecialAttributes: somebody tampered with the maps (1)!");
        #endif
            for (i=0; i<nIdCount; ++i)
                if (nBooleanPropertyAttributeIds[i] & m_nIncludeSpecial)
                {
                    exportBooleanPropertyAttribute(
                        getSpecialAttributeNamespace(nBooleanPropertyAttributeIds[i]),
                        getSpecialAttributeName(nBooleanPropertyAttributeIds[i]),
                        *(pBooleanPropertyNames[i]),
                        BOOLATTR_DEFAULT_FALSE	// all of the attributes are defaulted to "false"
                    );
            #ifdef DBG_UTIL
                //  reset the bit for later checking
                m_nIncludeSpecial = m_nIncludeSpecial & ~nBooleanPropertyAttributeIds[i];
            #endif
                }
        }

        // -------------------
        // the enum properties
        {
            if (SCA_STATE & m_nIncludeSpecial)
            {
                exportEnumPropertyAttribute(
                    getSpecialAttributeNamespace(SCA_STATE),
                    getSpecialAttributeName(SCA_STATE),
                    PROPERTY_DEFAULT_STATE,
                    OEnumMapper::getEnumMap(OEnumMapper::epCheckState),
                    STATE_NOCHECK);
            #ifdef DBG_UTIL
                //  reset the bit for later checking
                m_nIncludeSpecial = m_nIncludeSpecial & ~SCA_STATE;
            #endif
            }

            if (SCA_CURRENT_STATE & m_nIncludeSpecial)
            {
                exportEnumPropertyAttribute(
                    getSpecialAttributeNamespace(SCA_CURRENT_STATE),
                    getSpecialAttributeName(SCA_CURRENT_STATE),
                    PROPERTY_STATE,
                    OEnumMapper::getEnumMap(OEnumMapper::epCheckState),
                    STATE_NOCHECK);
            #ifdef DBG_UTIL
                //  reset the bit for later checking
                m_nIncludeSpecial = m_nIncludeSpecial & ~SCA_CURRENT_STATE;
            #endif
            }
        }

        // ----------------------------------
        // the EchoChar property needs special handling, cause it's a Int16, but must be stored as one-character-string
        {
            if (SCA_ECHO_CHAR & m_nIncludeSpecial)
            {
                DBG_CHECK_PROPERTY( PROPERTY_ECHO_CHAR, sal_Int16 );
                sal_Int16 nValue(0);
                m_xProps->getPropertyValue(PROPERTY_ECHO_CHAR) >>= nValue;
                if (nValue)
                {
                    ::rtl::OUString sCharacter(reinterpret_cast<const sal_Unicode*>(&nValue), 1);
                    AddAttribute(
                        getSpecialAttributeNamespace(SCA_ECHO_CHAR),
                        getSpecialAttributeName(SCA_ECHO_CHAR),
                        sCharacter);
                }
                exportedProperty(PROPERTY_ECHO_CHAR);
            #ifdef DBG_UTIL
                //  reset the bit for later checking
                m_nIncludeSpecial = m_nIncludeSpecial & ~SCA_ECHO_CHAR;
            #endif
            }
        }

        // ----------------------------------
        if ((SCA_MIN_VALUE | SCA_MAX_VALUE) & m_nIncludeSpecial)
        {
            // need to export the min value and the max value as attributes
            // It depends on the real type (FormComponentType) of the control, which properties hold these
            // values
            const sal_Char* pMinValuePropertyName = NULL;
            const sal_Char* pMaxValuePropertyName = NULL;
            getValueLimitPropertyNames(m_nClassId, pMinValuePropertyName, pMaxValuePropertyName);

            OSL_ENSURE((NULL == pMinValuePropertyName) == (0 == (SCA_MIN_VALUE & m_nIncludeSpecial)),
                "OControlExport::exportCommonControlAttributes: no property found for the min value attribute!");
            OSL_ENSURE((NULL == pMaxValuePropertyName) == (0 == (SCA_MAX_VALUE & m_nIncludeSpecial)),
                "OControlExport::exportCommonControlAttributes: no property found for the min value attribute!");

            // add the two attributes
            static const sal_Char* pMinValueAttributeName = getSpecialAttributeName(SCA_MIN_VALUE);
            static const sal_Char* pMaxValueAttributeName = getSpecialAttributeName(SCA_MAX_VALUE);
            static const sal_uInt16 nMinValueNamespaceKey = getSpecialAttributeNamespace(SCA_MIN_VALUE);
            static const sal_uInt16 nMaxValueNamespaceKey = getSpecialAttributeNamespace(SCA_MAX_VALUE);

            if (pMinValuePropertyName && (SCA_MIN_VALUE & m_nIncludeSpecial))
                exportGenericPropertyAttribute(
                    nMinValueNamespaceKey,
                    pMinValueAttributeName,
                    pMinValuePropertyName);

            if (pMaxValuePropertyName && (SCA_MAX_VALUE & m_nIncludeSpecial))
                exportGenericPropertyAttribute(
                    nMaxValueNamespaceKey,
                    pMaxValueAttributeName,
                    pMaxValuePropertyName);
        #ifdef DBG_UTIL
            //  reset the bit for later checking
            m_nIncludeSpecial = m_nIncludeSpecial & ~(SCA_MIN_VALUE | SCA_MAX_VALUE);
        #endif
        }

        OSL_ENSURE(0 == m_nIncludeSpecial,
            "OControlExport::exportSpecialAttributes: forgot some flags!");
            // in the dbg_util version, we should have removed every bit we handled from the mask, so it should
            // be 0 now ...
    }

    //---------------------------------------------------------------------
    void OControlExport::exportListSourceAsAttribute()
    {
        // DA_LIST_SOURCE needs some special handling
        DBG_CHECK_PROPERTY_NO_TYPE( PROPERTY_LISTSOURCE );

        ::rtl::OUString sListSource;
        Any aListSource = m_xProps->getPropertyValue(PROPERTY_LISTSOURCE);
        if (!(aListSource >>= sListSource))
        {
            Sequence< ::rtl::OUString > aListSourceSequence;
            aListSource >>= aListSourceSequence;
            if (aListSourceSequence.getLength())
                sListSource = aListSourceSequence[0];
        }

        if (sListSource.getLength())
        {	// the ListSource property needs to be exported as attribute, and it is not empty
            AddAttribute(
                getDatabaseAttributeNamespace(DA_LIST_SOURCE),
                getDatabaseAttributeName(DA_LIST_SOURCE),
                sListSource);
        }
    }

    //---------------------------------------------------------------------
    void OControlExport::getSequenceInt16PropertyAsSet(const ::rtl::OUString& _rPropertyName, Int16Set& _rOut)
    {
        Sequence< sal_Int16 > aValueSequence;
        DBG_CHECK_PROPERTY(_rPropertyName, Sequence< sal_Int16 >);
        m_xProps->getPropertyValue(_rPropertyName) >>= aValueSequence;

        const sal_Int16* pValues = aValueSequence.getConstArray();
        for (sal_Int32 i=0; i<aValueSequence.getLength(); ++i, ++pValues)
            _rOut.insert(*pValues);
    }

    //---------------------------------------------------------------------
    void OControlExport::exportListSourceAsElements()
    {
        // the string lists
        Sequence< ::rtl::OUString > aItems, aValues;
        DBG_CHECK_PROPERTY( PROPERTY_STRING_ITEM_LIST, Sequence< ::rtl::OUString > );
        m_xProps->getPropertyValue(PROPERTY_STRING_ITEM_LIST) >>= aItems;

        DBG_CHECK_PROPERTY( PROPERTY_LISTSOURCE, Sequence< ::rtl::OUString > );
        if ( 0 == ( m_nIncludeDatabase & DA_LIST_SOURCE ) )
            m_xProps->getPropertyValue(PROPERTY_LISTSOURCE) >>= aValues;
        // if we exported the list source as attribute, we do not repeat it as sub elements

        // the selection lists
        Int16Set aSelection, aDefaultSelection;
        getSequenceInt16PropertyAsSet(PROPERTY_SELECT_SEQ, aSelection);
        getSequenceInt16PropertyAsSet(PROPERTY_DEFAULT_SELECT_SEQ, aDefaultSelection);

        // the string for "true" and "false"
        ::rtl::OUString sTrue;
        ::rtl::OUStringBuffer sBuffer;
        m_rContext.getGlobalContext().GetMM100UnitConverter().convertBool(sBuffer, sal_True);
        sTrue = sBuffer.makeStringAndClear();

        // loop through both lists ('til the maximum of both lengths)
        const ::rtl::OUString* pItems = aItems.getConstArray();
        const ::rtl::OUString* pValues = aValues.getConstArray();

        sal_Int32 nItems = aItems.getLength();
        sal_Int32 nValues = aValues.getLength();

        sal_Int16 nMaxLen = (sal_Int16)std::max(nItems, nValues);

        for	(sal_Int16 i=0; i<nMaxLen; ++i )
        {
            m_rContext.getGlobalContext().ClearAttrList();
            if (i < nItems)
            {
                // there is an item at this position
                AddAttribute(
                    getCommonControlAttributeNamespace(CCA_LABEL),
                    getCommonControlAttributeName(CCA_LABEL),
                    *pItems);
                ++pItems;
            }
            if (i < nValues)
            {
                // there is an value at this position
                AddAttribute(
                    getCommonControlAttributeNamespace(CCA_VALUE),
                    getCommonControlAttributeName(CCA_VALUE),
                    *pValues);
                ++pValues;
            }

            Int16SetIterator aSelectedPos = aSelection.find(i);
            if (aSelection.end() != aSelectedPos)
            {	// the item at this position is selected
                AddAttribute(
                    getCommonControlAttributeNamespace(CCA_CURRENT_SELECTED),
                    getCommonControlAttributeName(CCA_CURRENT_SELECTED),
                    sTrue
                    );
                aSelection.erase(aSelectedPos);
            }

            Int16SetIterator aDefaultSelectedPos = aDefaultSelection.find(i);
            if (aDefaultSelection.end() != aDefaultSelectedPos)
            {	// the item at this position is selected as default
                AddAttribute(
                    getCommonControlAttributeNamespace(CCA_SELECTED),
                    getCommonControlAttributeName(CCA_SELECTED),
                    sTrue
                    );
                aDefaultSelection.erase(aDefaultSelectedPos);
            }
            SvXMLElementExport aFormElement(m_rContext.getGlobalContext(), XML_NAMESPACE_FORM, "option", sal_True, sal_True);
        }

        // There may be more "selected" or "default-selected" items than there are in the lists in real,
        // so we need to store some additional "form:option" items which have no name and no label, but
        // one or both of the selected flags.
        // 21.05.2001 - 85388 - frank.schoenheit@germany.sun.com

        if (aSelection.size() || aDefaultSelection.size())
        {
            sal_Int16 nLastSelected = -1;
            if (aSelection.size())
                nLastSelected = *(--aSelection.end());

            sal_Int16 nLastDefaultSelected = -1;
            if (aDefaultSelection.size())
                nLastDefaultSelected = *(--aDefaultSelection.end());

            // the maximum element in both sets
            sal_Int16 nLastReferredEntry = ::std::max(nLastSelected, nLastDefaultSelected);
            OSL_ENSURE(nLastReferredEntry >= nMaxLen, "OControlExport::exportListSourceAsElements: inconsistence!");
                // if the maximum (selected or default selected) entry number is less than the maximum item count
                // in both lists, the entry number should have been removed from the set

            for (sal_Int16 i=nMaxLen; i<=nLastReferredEntry; ++i)
            {
                if (aSelection.end() != aSelection.find(i))
                {	// the (not existent) item at this position is selected
                    AddAttribute(
                        getCommonControlAttributeNamespace(CCA_CURRENT_SELECTED),
                        getCommonControlAttributeName(CCA_CURRENT_SELECTED),
                        sTrue
                        );
                }

                if (aDefaultSelection.end() != aDefaultSelection.find(i))
                {	// the (not existent) item at this position is selected as default
                    AddAttribute(
                        getCommonControlAttributeNamespace(CCA_SELECTED),
                        getCommonControlAttributeName(CCA_SELECTED),
                        sTrue
                        );
                }
                SvXMLElementExport aFormElement(m_rContext.getGlobalContext(), XML_NAMESPACE_FORM, "option", sal_True, sal_True);
            }
        }
    }

    //---------------------------------------------------------------------
    void OControlExport::implStartElement(const sal_Char* _pName)
    {
        // before we let the base class start it's outer element, we add a wrapper element
        m_pOuterElement = new SvXMLElementExport(m_rContext.getGlobalContext(), XML_NAMESPACE_FORM, getOuterXMLElementName(), sal_True, sal_True);

        // add the attributes for the inner element
        exportInnerAttributes();

        // and start the inner element
        OElementExport::implStartElement(_pName);
    }

    //---------------------------------------------------------------------
    void OControlExport::implEndElement()
    {
        // end the inner element
        OElementExport::implEndElement();

        // end the outer element
        delete m_pOuterElement;
        m_pOuterElement = NULL;
    }

    //---------------------------------------------------------------------
    const sal_Char* OControlExport::getOuterXMLElementName() const
    {
        return "control";
    }

    //---------------------------------------------------------------------
    const sal_Char* OControlExport::getXMLElementName() const
    {
        return getElementName(m_eType);
    }

    //---------------------------------------------------------------------
    void OControlExport::examine()
    {
        // get the class id to decide which kind of element we need in the XML stream
        m_nClassId = FormComponentType::CONTROL;
        DBG_CHECK_PROPERTY( PROPERTY_CLASSID, sal_Int16 );
        m_xProps->getPropertyValue(PROPERTY_CLASSID) >>= m_nClassId;
        switch (m_nClassId)
        {
            case FormComponentType::DATEFIELD:
            case FormComponentType::TIMEFIELD:
            case FormComponentType::NUMERICFIELD:
            case FormComponentType::CURRENCYFIELD:
            case FormComponentType::PATTERNFIELD:
                m_eType = FORMATTED_TEXT;
                // NO BREAK
            case FormComponentType::TEXTFIELD:
            {	// it's some kind of edit. To know which type we need further investigation

                if (FORMATTED_TEXT != m_eType)
                {	// not coming from the previous cases which had a class id .ne. TEXTFIELD

                    // check if it's a formatted field
                    if (m_xPropertyInfo->hasPropertyByName(PROPERTY_FORMATKEY))
                    {
                        m_eType = FORMATTED_TEXT;
                    }
                    else
                    {
                        // all other controls are represented by an ordinary edit control, but which XML control type
                        // it is depends on the current values of some properties

                        // if the EchoChar string is not empty, it is a password field
                        sal_Int16 nEchoChar = 0;
                        if (m_xPropertyInfo->hasPropertyByName(PROPERTY_ECHOCHAR))
                            // grid columns do not have this property ....
                            m_xProps->getPropertyValue(PROPERTY_ECHOCHAR) >>= nEchoChar;
                        if (nEchoChar)
                        {
                            m_eType = PASSWORD;
                            m_nIncludeSpecial |= SCA_ECHO_CHAR;
                        }
                        else
                        {
                            // if the MultiLine property is sal_True, it is a TextArea
                            sal_Bool bMultiLine = sal_False;
                            if (m_xPropertyInfo->hasPropertyByName(PROPERTY_MULTILINE))
                                // grid columns do not have this property ....
                                bMultiLine = ::cppu::any2bool(m_xProps->getPropertyValue(PROPERTY_MULTILINE));
                            if (bMultiLine)
                                m_eType = TEXT_AREA;
                            else
                                // the only case left is represented by a Text element
                                m_eType = TEXT;
                        }
                    }
                }

                // attributes which are common to all the four types:
                // common attributes
                m_nIncludeCommon =
                    CCA_NAME | CCA_SERVICE_NAME | CCA_DISABLED |
                    CCA_PRINTABLE | CCA_TAB_INDEX | CCA_TAB_STOP | CCA_TITLE |
                    CCA_VALUE;
                // database attributes
                m_nIncludeDatabase = DA_DATA_FIELD;
                // event attributes
                m_nIncludeEvents = EA_CONTROL_EVENTS | EA_ON_CHANGE | EA_ON_SELECT;

                // only text and pattern fields have a ConvertEmptyToNull property
                if ((m_nClassId == FormComponentType::TEXTFIELD) || (m_nClassId == FormComponentType::PATTERNFIELD))
                    m_nIncludeDatabase |= DA_CONVERT_EMPTY;

                // all controls but the file control fields have a readonly property
                if (m_nClassId != FormComponentType::FILECONTROL)
                    m_nIncludeCommon |= CCA_READONLY;

                // a text field has a max text len
                if (m_nClassId == FormComponentType::TEXTFIELD)
                    m_nIncludeCommon |= CCA_MAX_LENGTH;

                // max and min values and validation:
                if (FORMATTED_TEXT == m_eType)
                {	// in general all control represented as formatted-text have these props
                    if (FormComponentType::PATTERNFIELD != m_nClassId)
                        // but the PatternField does not have value limits
                        m_nIncludeSpecial |= SCA_MAX_VALUE | SCA_MIN_VALUE;

                    if (FormComponentType::TEXTFIELD != m_nClassId)
                        // and the FormattedField does not have a validation flag
                        m_nIncludeSpecial |= SCA_VALIDATION;
                }

                // if it's not a password field, the CurrentValue needs to be stored, too
                if (PASSWORD != m_eType)
                    m_nIncludeCommon |= CCA_CURRENT_VALUE;
            }
            break;

            case FormComponentType::FILECONTROL:
                m_eType = FILE;
                m_nIncludeCommon =
                    CCA_NAME | CCA_SERVICE_NAME | CCA_CURRENT_VALUE | CCA_DISABLED |
                    CCA_PRINTABLE | CCA_TAB_INDEX | CCA_TAB_STOP | CCA_TITLE |
                    CCA_VALUE;
                m_nIncludeEvents = EA_CONTROL_EVENTS | EA_ON_CHANGE | EA_ON_SELECT;
                break;

            case FormComponentType::FIXEDTEXT:
                m_eType = FIXED_TEXT;
                m_nIncludeCommon =
                    CCA_NAME | CCA_SERVICE_NAME | CCA_DISABLED | CCA_LABEL |
                    CCA_PRINTABLE | CCA_TITLE | CCA_FOR;
                m_nIncludeSpecial = SCA_MULTI_LINE;
                m_nIncludeEvents = EA_CONTROL_EVENTS;
                break;

            case FormComponentType::COMBOBOX:
                m_eType = COMBOBOX;
                m_nIncludeCommon =
                    CCA_NAME | CCA_SERVICE_NAME | CCA_CURRENT_VALUE |
                    CCA_DISABLED | CCA_DROPDOWN | CCA_MAX_LENGTH | CCA_PRINTABLE | CCA_READONLY | CCA_SIZE |
                    CCA_TAB_INDEX | CCA_TAB_STOP | CCA_TITLE | CCA_VALUE;
                m_nIncludeSpecial = SCA_AUTOMATIC_COMPLETION;
                m_nIncludeDatabase = DA_CONVERT_EMPTY | DA_DATA_FIELD | DA_LIST_SOURCE | DA_LIST_SOURCE_TYPE;
                m_nIncludeEvents = EA_CONTROL_EVENTS | EA_ON_CHANGE | EA_ON_SELECT;
                break;

            case FormComponentType::LISTBOX:
                m_eType = LISTBOX;
                m_nIncludeCommon =
                    CCA_NAME | CCA_SERVICE_NAME | CCA_DISABLED | CCA_DROPDOWN |
                    CCA_PRINTABLE | CCA_SIZE | CCA_TAB_INDEX | CCA_TAB_STOP | CCA_TITLE;
                m_nIncludeSpecial = SCA_MULTIPLE;
                m_nIncludeDatabase = DA_BOUND_COLUMN | DA_DATA_FIELD | DA_LIST_SOURCE_TYPE;
                m_nIncludeEvents = EA_CONTROL_EVENTS | EA_ON_CHANGE | EA_ON_CLICK	| EA_ON_DBLCLICK;
                // check if we need to export the ListSource as attribute
                {
                    // for a list box, if the ListSourceType is VALUE_LIST, no ListSource is stored, but instead
                    // a sequence of pairs which is build from the StringItemList and the ValueList
                    ListSourceType eListSourceType = ListSourceType_VALUELIST;
                #if OSL_DEBUG_LEVEL > 0
                    sal_Bool bSuccess =
                #endif
                    m_xProps->getPropertyValue(PROPERTY_LISTSOURCETYPE) >>= eListSourceType;
                    OSL_ENSURE(bSuccess, "OControlExport::examineControl: could not retrieve the ListSourceType!");
                    if (ListSourceType_VALUELIST != eListSourceType)
                    {
                        m_nIncludeDatabase |= DA_LIST_SOURCE;
                    }
                }

                break;

            case FormComponentType::COMMANDBUTTON:
                m_eType = BUTTON;
                m_nIncludeCommon |= CCA_TAB_STOP | CCA_LABEL;
                m_nIncludeSpecial = SCA_DEFAULT_BUTTON;
                // NO BREAK !
            case FormComponentType::IMAGEBUTTON:
                if (BUTTON != m_eType)
                    // not coming from the previous case
                    m_eType = IMAGE;
                m_nIncludeCommon |=
                    CCA_NAME | CCA_SERVICE_NAME | CCA_BUTTON_TYPE | CCA_DISABLED |
                    CCA_IMAGE_DATA | CCA_PRINTABLE | CCA_TAB_INDEX | CCA_TARGET_FRAME |
                    CCA_TARGET_LOCATION | CCA_TITLE;
                m_nIncludeEvents = EA_CONTROL_EVENTS | EA_ON_CLICK	| EA_ON_DBLCLICK;
                break;

            case FormComponentType::CHECKBOX:
                m_eType = CHECKBOX;
                m_nIncludeSpecial = SCA_CURRENT_STATE | SCA_IS_TRISTATE | SCA_STATE;
                // NO BREAK !
            case FormComponentType::RADIOBUTTON:
                m_nIncludeCommon =
                    CCA_NAME | CCA_SERVICE_NAME | CCA_DISABLED | CCA_LABEL |
                    CCA_PRINTABLE | CCA_TAB_INDEX | CCA_TAB_STOP | CCA_TITLE | CCA_VALUE;
                if (CHECKBOX != m_eType)
                {	// not coming from the previous case
                    m_eType = RADIO;
                    m_nIncludeCommon |= CCA_CURRENT_SELECTED | CCA_SELECTED;
                }
                m_nIncludeDatabase = DA_DATA_FIELD;
                m_nIncludeEvents = EA_CONTROL_EVENTS | EA_ON_CHANGE;
                break;

            case FormComponentType::GROUPBOX:
                m_eType = FRAME;
                m_nIncludeCommon =
                    CCA_NAME | CCA_SERVICE_NAME | CCA_DISABLED | CCA_LABEL |
                    CCA_PRINTABLE | CCA_TITLE | CCA_FOR;
                m_nIncludeEvents = EA_CONTROL_EVENTS;
                break;

            case FormComponentType::IMAGECONTROL:
                m_eType = IMAGE_FRAME;
                m_nIncludeCommon =
                    CCA_NAME | CCA_SERVICE_NAME | CCA_DISABLED | CCA_IMAGE_DATA |
                    CCA_PRINTABLE | CCA_READONLY | CCA_TITLE;
                m_nIncludeDatabase = DA_DATA_FIELD;
                m_nIncludeEvents = EA_CONTROL_EVENTS;
                break;

            case FormComponentType::HIDDENCONTROL:
                m_eType = HIDDEN;
                m_nIncludeCommon =
                    CCA_NAME | CCA_SERVICE_NAME | CCA_VALUE;
                break;

            case FormComponentType::GRIDCONTROL:
                m_eType = GRID;
                m_nIncludeCommon =
                    CCA_NAME | CCA_SERVICE_NAME | CCA_DISABLED | CCA_PRINTABLE |
                    CCA_TAB_INDEX | CCA_TAB_STOP | CCA_TITLE;
                m_nIncludeEvents = EA_CONTROL_EVENTS;
                break;

            case FormComponentType::CONTROL:
                m_eType = GENERIC_CONTROL;
                // unknown control type
                m_nIncludeCommon = CCA_NAME | CCA_SERVICE_NAME;
                    // at least a name should be there, 'cause without a name the control could never have been
                    // inserted into it's parent container
                    // In addition, the service name is absolutely necessary to create the control upon reading.
                m_nIncludeEvents = EA_CONTROL_EVENTS;
                    // we always should be able to export events - this is not control type dependent
                break;

            default:
                OSL_ENSURE(sal_False, "OControlExport::examineControl: unknown control type (class id)!");
                break;
        }

        // in general, all control types need to export the control id
        m_nIncludeCommon |= CCA_CONTROL_ID;

        // is is a control bound to a calc cell?
        if ( FormCellBindingHelper::livesInSpreadsheetDocument( m_xProps ) )
        {
            FormCellBindingHelper aHelper( m_xProps, NULL );
            {
                if ( aHelper.isCellBinding( aHelper.getCurrentBinding( ) ) )
                {
                    m_nIncludeBindings |= BA_LINKED_CELL;
                    if ( m_nClassId == FormComponentType::LISTBOX )
                        m_nIncludeBindings |= BA_LIST_LINKING_TYPE;
                }
            }

            // is it a list-like control which uses a calc cell range as list source?
            {
                if ( aHelper.isCellRangeListSource( aHelper.getCurrentListSource( ) ) )
                    m_nIncludeBindings |= BA_LIST_CELL_RANGE;
            }
        }
    }

    //---------------------------------------------------------------------
    void OControlExport::exportCellBindingAttributes( bool _bIncludeListLinkageType )
    {
        try
        {
            FormCellBindingHelper aHelper( m_xProps, NULL );
            Reference< XValueBinding > xBinding( aHelper.getCurrentBinding() );
            OSL_ENSURE( xBinding.is(), "OControlExport::exportCellBindingAttributes: invalid bindable or invalid binding!" );
            if ( xBinding.is() )
            {
                // ....................................................
                AddAttribute(
                    getBindingAttributeNamespace( BA_LINKED_CELL ),
                    getBindingAttributeName( BA_LINKED_CELL ),
                    aHelper.getStringAddressFromCellBinding( xBinding )
                );

                // ....................................................
                if ( _bIncludeListLinkageType )
                {
                    sal_Int16 nLinkageType = aHelper.isCellIntegerBinding( xBinding ) ? 1 : 0;

                    ::rtl::OUStringBuffer sBuffer;
                    m_rContext.getGlobalContext().GetMM100UnitConverter().convertEnum(
                        sBuffer,
                        (sal_uInt16)nLinkageType,
                        OEnumMapper::getEnumMap( OEnumMapper::epListLinkageType )
                    );

                    AddAttribute(
                        getBindingAttributeNamespace( BA_LIST_LINKING_TYPE ),
                        getBindingAttributeName( BA_LIST_LINKING_TYPE ),
                        sBuffer.makeStringAndClear()
                    );
                }

            }
        }
        catch( const Exception& )
        {
            OSL_ENSURE( sal_False, "OControlExport::exportCellBindingAttributes: caught an exception!" );
        }
    }

    //---------------------------------------------------------------------
    void OControlExport::exportCellListSourceRange( )
    {
        try
        {
            Reference< XListEntrySink > xSink( m_xProps, UNO_QUERY );
            Reference< XListEntrySource > xSource;
            if ( xSink.is() )
                xSource = xSource.query( xSink->getListEntrySource() );
            OSL_ENSURE( xSource.is(), "OControlExport::exportCellListSourceRange: list source or sink!" );
            if ( xSource.is() )
            {
                FormCellBindingHelper aHelper( m_xProps, NULL );

                AddAttribute(
                    getBindingAttributeNamespace( BA_LIST_CELL_RANGE ),
                    getBindingAttributeName( BA_LIST_CELL_RANGE ),
                    aHelper.getStringAddressFromCellListSource( xSource )
                );
            }
        }
        catch( const Exception& )
        {
            OSL_ENSURE( sal_False, "OControlExport::exportCellListSourceRange: caught an exception!" );
        }
    }

    //=====================================================================
    //= OColumnExport
    //=====================================================================
    //---------------------------------------------------------------------
    OColumnExport::OColumnExport(IFormsExportContext& _rContext, const Reference< XPropertySet >& _rxControl,
        const Sequence< ScriptEventDescriptor >& _rEvents)
        :OControlExport(_rContext, _rxControl, ::rtl::OUString(), ::rtl::OUString(), _rEvents)
    {
    }

    //---------------------------------------------------------------------
    OColumnExport::~OColumnExport()
    {
        implEndElement();
    }

    //---------------------------------------------------------------------
    void OColumnExport::exportServiceNameAttribute()
    {
        // the attribute "service name" (which has a slightly different meaning for columns
        DBG_CHECK_PROPERTY( PROPERTY_COLUMNSERVICENAME, ::rtl::OUString );
        ::rtl::OUString sColumnServiceName;
        m_xProps->getPropertyValue(PROPERTY_COLUMNSERVICENAME) >>= sColumnServiceName;
        // the service name is a full qualified one (i.e. com.sun.star.form.TextField), but the
        // real service name for the column (for use with the XGridColumnFactory) is only the last
        // token of this complete name.
        sal_Int32 nLastSep = sColumnServiceName.lastIndexOf('.');
        OSL_ENSURE(-1 != nLastSep, "OColumnExport::startExportElement: invalid service name!");
        sColumnServiceName = sColumnServiceName.copy(nLastSep + 1);
        // add the attribute
        AddAttribute(getCommonControlAttributeNamespace(CCA_SERVICE_NAME), getCommonControlAttributeName(CCA_SERVICE_NAME), sColumnServiceName);
        // flag the property as "handled"
        exportedProperty(PROPERTY_COLUMNSERVICENAME);

    }

    //---------------------------------------------------------------------
    const sal_Char* OColumnExport::getOuterXMLElementName() const
    {
        return "column";
    }

    //---------------------------------------------------------------------
    void OColumnExport::exportAttributes()
    {
        OControlExport::exportAttributes();

        // the attribute "label"
        exportStringPropertyAttribute(
            getCommonControlAttributeNamespace(CCA_LABEL),
            getCommonControlAttributeName(CCA_LABEL),
            PROPERTY_LABEL);

        // the style attribute
        ::rtl::OUString sStyleName = m_rContext.getObjectStyleName( m_xProps );
        if ( sStyleName.getLength() )
        {
            AddAttribute(
                getSpecialAttributeNamespace( SCA_COLUMN_STYLE_NAME ),
                getSpecialAttributeName( SCA_COLUMN_STYLE_NAME ),
                sStyleName
            );
        }
    }

    //---------------------------------------------------------------------
    void OColumnExport::examine()
    {
        OControlExport::examine();

        // grid columns miss some properties of the controls they're representing
        m_nIncludeCommon &= ~(CCA_CONTROL_ID | CCA_FOR | CCA_PRINTABLE | CCA_TAB_INDEX | CCA_TAB_STOP | CCA_LABEL);
        m_nIncludeSpecial &= ~(SCA_ECHO_CHAR | SCA_AUTOMATIC_COMPLETION | SCA_MULTIPLE | SCA_MULTI_LINE | SCA_IS_TRISTATE);

        if (FormComponentType::DATEFIELD != m_nClassId)
            // except date fields, no column has the DropDown property
            m_nIncludeCommon &= ~CCA_DROPDOWN;
    }

    //=====================================================================
    //= OFormExport
    //=====================================================================
    //---------------------------------------------------------------------
    OFormExport::OFormExport(IFormsExportContext& _rContext, const Reference< XPropertySet >& _rxForm,
        const Sequence< ScriptEventDescriptor >& _rEvents)
        :OElementExport(_rContext, _rxForm, _rEvents)
    {
        OSL_ENSURE(m_xProps.is(), "OFormExport::OFormExport: invalid arguments!");
    }

    //---------------------------------------------------------------------
    const sal_Char* OFormExport::getXMLElementName() const
    {
        return "form";
    }

    //---------------------------------------------------------------------
    void OFormExport::exportSubTags()
    {
        // let the base class export the remaining properties and the events
        OElementExport::exportSubTags();

        // loop through all children
        Reference< XIndexAccess > xCollection(m_xProps, UNO_QUERY);
        OSL_ENSURE(xCollection.is(), "OFormLayerXMLExport::implExportForm: a form which is not an index access? Suspic�ous!");

        if (xCollection.is())
            m_rContext.exportCollectionElements(xCollection);
    }

    //---------------------------------------------------------------------
    void OFormExport::exportAttributes()
    {
        sal_Int32 i=0;

        // ---------------------
        // the string properties
        {
            static FormAttributes eStringPropertyIds[] =
            {
                faName, /*faAction,*/ faCommand, faDatasource, faFilter, faOrder
            };
            static ::rtl::OUString aStringPropertyNames[] =
            {
                PROPERTY_NAME, /*PROPERTY_TARGETURL,*/ PROPERTY_COMMAND, PROPERTY_DATASOURCENAME, PROPERTY_FILTER, PROPERTY_ORDER
            };
            sal_Int32 nIdCount = SAL_N_ELEMENTS(eStringPropertyIds);
        #ifdef DBG_UTIL
            sal_Int32 nNameCount = SAL_N_ELEMENTS(aStringPropertyNames);
            OSL_ENSURE((nIdCount == nNameCount),
                "OFormExport::exportAttributes: somebody tampered with the maps (1)!");
        #endif
            for (i=0; i<nIdCount; ++i)
                exportStringPropertyAttribute(
                    getFormAttributeNamespace(eStringPropertyIds[i]),
                    getFormAttributeName(eStringPropertyIds[i]),
                    aStringPropertyNames[i]);
        }

        // ----------------------
        // the boolean properties
        {
            static FormAttributes eBooleanPropertyIds[] =
            {
                faAllowDeletes, faAllowInserts, faAllowUpdates, faApplyFilter, faEscapeProcessing, faIgnoreResult
            };
            static const ::rtl::OUString* pBooleanPropertyNames[] =
            {
                &PROPERTY_ALLOWDELETES, &PROPERTY_ALLOWINSERTS, &PROPERTY_ALLOWUPDATES, &PROPERTY_APPLYFILTER, &PROPERTY_ESCAPEPROCESSING, &PROPERTY_IGNORERESULT
            };
            static sal_Int8 nBooleanPropertyAttrFlags[] =
            {
                BOOLATTR_DEFAULT_TRUE, BOOLATTR_DEFAULT_TRUE, BOOLATTR_DEFAULT_TRUE, BOOLATTR_DEFAULT_FALSE, BOOLATTR_DEFAULT_TRUE, BOOLATTR_DEFAULT_FALSE
            };
            sal_Int32 nIdCount = SAL_N_ELEMENTS(eBooleanPropertyIds);
        #ifdef DBG_UTIL
            sal_Int32 nNameCount = SAL_N_ELEMENTS(pBooleanPropertyNames);
            sal_Int32 nFlagsCount = SAL_N_ELEMENTS(nBooleanPropertyAttrFlags);
            OSL_ENSURE((nIdCount == nNameCount) && (nNameCount == nFlagsCount),
                "OFormExport::exportAttributes: somebody tampered with the maps (2)!");
        #endif
            for (i=0; i<nIdCount; ++i)
                exportBooleanPropertyAttribute(
                    getFormAttributeNamespace(eBooleanPropertyIds[i]),
                    getFormAttributeName(eBooleanPropertyIds[i]),
                    *(pBooleanPropertyNames[i]),
                    nBooleanPropertyAttrFlags[i]
                );
        }

        // -------------------
        // the enum properties
        {
            static FormAttributes eEnumPropertyIds[] =
            {
                faEnctype, faMethod, faCommandType, faNavigationMode, faTabbingCycle
            };
            static const sal_Char* pEnumPropertyNames[] =
            {
                PROPERTY_SUBMIT_ENCODING, PROPERTY_SUBMIT_METHOD, PROPERTY_COMMAND_TYPE, PROPERTY_NAVIGATION, PROPERTY_CYCLE
            };
            static OEnumMapper::EnumProperties eEnumPropertyMaps[] =
            {
                OEnumMapper::epSubmitEncoding, OEnumMapper::epSubmitMethod, OEnumMapper::epCommandType, OEnumMapper::epNavigationType, OEnumMapper::epTabCyle
            };
            static sal_Int32 nEnumPropertyAttrDefaults[] =
            {
                FormSubmitEncoding_URL, FormSubmitMethod_GET, CommandType::COMMAND, NavigationBarMode_CURRENT, TabulatorCycle_RECORDS
            };
            static sal_Bool nEnumPropertyAttrDefaultFlags[] =
            {
                sal_False, sal_False, sal_False, sal_False, sal_True
            };
            sal_Int32 nIdCount = SAL_N_ELEMENTS(eEnumPropertyIds);
        #ifdef DBG_UTIL
            sal_Int32 nNameCount = SAL_N_ELEMENTS(pEnumPropertyNames);
            sal_Int32 nDefaultCount = SAL_N_ELEMENTS(nEnumPropertyAttrDefaults);
            sal_Int32 nDefaultFlagCount = SAL_N_ELEMENTS(nEnumPropertyAttrDefaultFlags);
            sal_Int32 nMapCount = SAL_N_ELEMENTS(eEnumPropertyMaps);
            OSL_ENSURE((nIdCount == nNameCount) && (nNameCount == nDefaultCount) && (nDefaultCount == nDefaultFlagCount) && (nDefaultFlagCount == nMapCount),
                "OFormExport::exportAttributes: somebody tampered with the maps (3)!");
        #endif
            for (i=0; i<nIdCount; ++i)
                exportEnumPropertyAttribute(
                    getFormAttributeNamespace(eEnumPropertyIds[i]),
                    getFormAttributeName(eEnumPropertyIds[i]),
                    pEnumPropertyNames[i],
                    OEnumMapper::getEnumMap(eEnumPropertyMaps[i]),
                    nEnumPropertyAttrDefaults[i],
                    nEnumPropertyAttrDefaultFlags[i]
                );
        }

        // the service name
        exportServiceNameAttribute();
        // the target frame
        exportTargetFrameAttribute();
        // the target URL
        exportTargetLocationAttribute();

        // master fields
        exportStringSequenceAttribute(
            getFormAttributeNamespace(faMasterFields),
            getFormAttributeName(faMasterFields),
            PROPERTY_MASTERFIELDS);
        // detail fields
        exportStringSequenceAttribute(
            getFormAttributeNamespace(faDetailFiels),
            getFormAttributeName(faDetailFiels),
            PROPERTY_DETAILFIELDS);
    }

//.........................................................................
}	// namespace xmloff
//.........................................................................
}//end of namespace binfilter

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
