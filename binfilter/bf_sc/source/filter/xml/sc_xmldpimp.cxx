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

#ifdef PCH
#endif

#ifdef _MSC_VER
#pragma hdrstop
#endif

// INCLUDE ---------------------------------------------------------------

#include "xmlimprt.hxx"
#include "xmlfilti.hxx"
#include "document.hxx"
#include "dpshttab.hxx"
#include "dpsdbtab.hxx"
#include "attrib.hxx"

#include "XMLConverter.hxx"

#include <bf_xmloff/nmspmap.hxx>
namespace binfilter {

//#include <com/sun/star/sheet/DataPilotFieldOrientation.hpp>

using namespace ::com::sun::star;
using namespace xmloff::token;

//------------------------------------------------------------------

ScXMLDataPilotTablesContext::ScXMLDataPilotTablesContext( ScXMLImport& rImport,
                                      USHORT nPrfx,
                                      const ::rtl::OUString& rLName,
                                      const ::com::sun::star::uno::Reference<
                                      ::com::sun::star::xml::sax::XAttributeList>& xAttrList) :
    SvXMLImportContext( rImport, nPrfx, rLName )
{
    // has no Attributes
    rImport.LockSolarMutex();
}

ScXMLDataPilotTablesContext::~ScXMLDataPilotTablesContext()
{
    GetScImport().UnlockSolarMutex();
}

SvXMLImportContext *ScXMLDataPilotTablesContext::CreateChildContext( USHORT nPrefix,
                                            const ::rtl::OUString& rLName,
                                            const ::com::sun::star::uno::Reference<
                                          ::com::sun::star::xml::sax::XAttributeList>& xAttrList )
{
    SvXMLImportContext *pContext = 0;

    const SvXMLTokenMap& rTokenMap = GetScImport().GetDataPilotTablesElemTokenMap();
    switch( rTokenMap.Get( nPrefix, rLName ) )
    {
        case XML_TOK_DATA_PILOT_TABLE :
        {
            pContext = new ScXMLDataPilotTableContext( GetScImport(), nPrefix,
                                                          rLName, xAttrList);
        }
        break;
    }

    if( !pContext )
        pContext = new SvXMLImportContext( GetImport(), nPrefix, rLName );

    return pContext;
}

void ScXMLDataPilotTablesContext::EndElement()
{
}

ScXMLDataPilotTableContext::ScXMLDataPilotTableContext( ScXMLImport& rImport,
                                      USHORT nPrfx,
                                      const ::rtl::OUString& rLName,
                                      const ::com::sun::star::uno::Reference<
                                      ::com::sun::star::xml::sax::XAttributeList>& xAttrList) :
    SvXMLImportContext( rImport, nPrfx, rLName ),
    sDataPilotTableName(),
    sApplicationData(),
    sGrandTotal(GetXMLToken(XML_BOTH)),
    bIsNative(sal_True),
    bIgnoreEmptyRows(sal_False),
    bIdentifyCategories(sal_False),
    bTargetRangeAddress(sal_False),
    bSourceCellRange(sal_False),
    pDoc(GetScImport().GetDocument()),
    pDPObject(NULL),
    pDPSave(NULL)
{
    sal_Int16 nAttrCount = xAttrList.is() ? xAttrList->getLength() : 0;
    const SvXMLTokenMap& rAttrTokenMap = GetScImport().GetDataPilotTableAttrTokenMap();
    for( sal_Int16 i=0; i < nAttrCount; i++ )
    {
        ::rtl::OUString sAttrName = xAttrList->getNameByIndex( i );
        ::rtl::OUString aLocalName;
        USHORT nPrefix = GetScImport().GetNamespaceMap().GetKeyByAttrName(
                                            sAttrName, &aLocalName );
        ::rtl::OUString sValue = xAttrList->getValueByIndex( i );

        switch( rAttrTokenMap.Get( nPrefix, aLocalName ) )
        {
            case XML_TOK_DATA_PILOT_TABLE_ATTR_NAME :
            {
                sDataPilotTableName = sValue;
            }
            break;
            case XML_TOK_DATA_PILOT_TABLE_ATTR_APPLICATION_DATA :
            {
                sApplicationData = sValue;
            }
            break;
            case XML_TOK_DATA_PILOT_TABLE_ATTR_GRAND_TOTAL :
            {
                sGrandTotal = sValue;
            }
            break;
            case XML_TOK_DATA_PILOT_TABLE_ATTR_IGNORE_EMPTY_ROWS :
            {
                bIgnoreEmptyRows = IsXMLToken(sValue, XML_TRUE);
            }
            break;
            case XML_TOK_DATA_PILOT_TABLE_ATTR_IDENTIFY_CATEGORIES :
            {
                bIdentifyCategories = IsXMLToken(sValue, XML_TRUE);
            }
            break;
            case XML_TOK_DATA_PILOT_TABLE_ATTR_TARGET_RANGE_ADDRESS :
            {
                sal_Int32 nOffset(0);
                bTargetRangeAddress = ScXMLConverter::GetRangeFromString( aTargetRangeAddress, sValue, pDoc, nOffset );
            }
            break;
            case XML_TOK_DATA_PILOT_TABLE_ATTR_BUTTONS :
            {
                sButtons = sValue;
            }
            break;
        }
    }

    pDPObject = new ScDPObject(pDoc);
     pDPSave = new ScDPSaveData();
}

ScXMLDataPilotTableContext::~ScXMLDataPilotTableContext()
{
}

SvXMLImportContext *ScXMLDataPilotTableContext::CreateChildContext( USHORT nPrefix,
                                            const ::rtl::OUString& rLName,
                                            const ::com::sun::star::uno::Reference<
                                          ::com::sun::star::xml::sax::XAttributeList>& xAttrList )
{
    SvXMLImportContext *pContext = 0;

    const SvXMLTokenMap& rTokenMap = GetScImport().GetDataPilotTableElemTokenMap();
    switch( rTokenMap.Get( nPrefix, rLName ) )
    {
        case XML_TOK_DATA_PILOT_TABLE_ELEM_SOURCE_SQL :
        {
            pContext = new ScXMLDPSourceSQLContext(GetScImport(), nPrefix, rLName, xAttrList, this);
            nSourceType = SQL;
        }
        break;
        case XML_TOK_DATA_PILOT_TABLE_ELEM_SOURCE_TABLE :
        {
            pContext = new ScXMLDPSourceTableContext(GetScImport(), nPrefix, rLName, xAttrList, this);
            nSourceType = TABLE;
        }
        break;
        case XML_TOK_DATA_PILOT_TABLE_ELEM_SOURCE_QUERY :
        {
            pContext = new ScXMLDPSourceQueryContext(GetScImport(), nPrefix, rLName, xAttrList, this);
            nSourceType = QUERY;
        }
        break;
        case XML_TOK_DATA_PILOT_TABLE_ELEM_SOURCE_SERVICE :
        {
            pContext = new ScXMLSourceServiceContext(GetScImport(), nPrefix, rLName, xAttrList, this);
            nSourceType = SERVICE;
        }
        break;
        case XML_TOK_DATA_PILOT_TABLE_ELEM_SOURCE_CELL_RANGE :
        {
            pContext = new ScXMLSourceCellRangeContext(GetScImport(), nPrefix, rLName, xAttrList, this);
            nSourceType = CELLRANGE;
        }
        break;
        case XML_TOK_DATA_PILOT_TABLE_ELEM_DATA_PILOT_FIELD :
            pContext = new ScXMLDataPilotFieldContext(GetScImport(), nPrefix, rLName, xAttrList, this);
        break;
    }

    if( !pContext )
        pContext = new SvXMLImportContext( GetImport(), nPrefix, rLName );

    return pContext;
}

void ScXMLDataPilotTableContext::SetButtons()
{
    OUString sAddress;
    sal_Int32 nOffset = 0;
    while( nOffset >= 0 )
    {
        ScXMLConverter::GetTokenByOffset( sAddress, sButtons, nOffset );
        if( nOffset >= 0 )
        {
            ScAddress aScAddress;
            sal_Int32 nOffset(0);
            if (pDoc && ScXMLConverter::GetAddressFromString( aScAddress, sAddress, pDoc, nOffset ))
            {
                ScMergeFlagAttr aAttr( SC_MF_BUTTON );
                pDoc->ApplyAttr( aScAddress.Col(), aScAddress.Row(), aScAddress.Tab(), aAttr );
            }
        }
    }
}

void ScXMLDataPilotTableContext::AddDimension(ScDPSaveDimension* pDim)
{
    if (pDPSave)
    {
        //	#91045# if a dimension with that name has already been inserted,
        //	mark the new one as duplicate
        if ( !pDim->IsDataLayout() &&
                pDPSave->GetExistingDimensionByName(pDim->GetName()) )
            pDim->SetDupFlag( TRUE );

        pDPSave->AddDimension(pDim);
    }
}

void ScXMLDataPilotTableContext::EndElement()
{
    if (bTargetRangeAddress)
    {
        pDPObject->SetName(sDataPilotTableName);
        pDPObject->SetTag(sApplicationData);
        pDPObject->SetOutRange(aTargetRangeAddress);
        switch (nSourceType)
        {
            case SQL :
            {
                ScImportSourceDesc aImportDesc;
                aImportDesc.aDBName = sDatabaseName;
                aImportDesc.aObject = sSourceObject;
                aImportDesc.nType = sheet::DataImportMode_SQL;
                aImportDesc.bNative = bIsNative;
                pDPObject->SetImportDesc(aImportDesc);
            }
            break;
            case TABLE :
            {
                ScImportSourceDesc aImportDesc;
                aImportDesc.aDBName = sDatabaseName;
                aImportDesc.aObject = sSourceObject;
                aImportDesc.nType = sheet::DataImportMode_TABLE;
                pDPObject->SetImportDesc(aImportDesc);
            }
            break;
            case QUERY :
            {
                ScImportSourceDesc aImportDesc;
                aImportDesc.aDBName = sDatabaseName;
                aImportDesc.aObject = sSourceObject;
                aImportDesc.nType = sheet::DataImportMode_QUERY;
                pDPObject->SetImportDesc(aImportDesc);
            }
            break;
            case SERVICE :
            {
                ScDPServiceDesc aServiceDesk(sServiceName, sServiceSourceObject, sServiceSourceName,
                                    sServiceUsername, sServicePassword);
                pDPObject->SetServiceData(aServiceDesk);
            }
            break;
            case CELLRANGE :
            {
                if (bSourceCellRange)
                {
                    ScSheetSourceDesc aSheetDesc;
                    aSheetDesc.aSourceRange = aSourceCellRangeAddress;
                    aSheetDesc.aQueryParam = aSourceQueryParam;
                    pDPObject->SetSheetDesc(aSheetDesc);
                }
            }
            break;
        }
        if (IsXMLToken(sGrandTotal, XML_BOTH))
        {
            pDPSave->SetRowGrand(sal_True);
            pDPSave->SetColumnGrand(sal_True);
        }
        else if (IsXMLToken(sGrandTotal, XML_ROW))
        {
            pDPSave->SetRowGrand(sal_True);
            pDPSave->SetColumnGrand(sal_False);
        }
        else if (IsXMLToken(sGrandTotal, XML_COLUMN))
        {
            pDPSave->SetRowGrand(sal_False);
            pDPSave->SetColumnGrand(sal_True);
        }
        else
        {
            pDPSave->SetRowGrand(sal_False);
            pDPSave->SetColumnGrand(sal_False);
        }
        pDPSave->SetIgnoreEmptyRows(bIgnoreEmptyRows);
        pDPSave->SetRepeatIfEmpty(bIdentifyCategories);
        pDPObject->SetSaveData(*pDPSave);
        if (pDoc)
        {
            ScDPCollection* pDPCollection = pDoc->GetDPCollection();
            pDPObject->SetAlive(sal_True);
            pDPCollection->Insert(pDPObject);
        }
        SetButtons();
    }
}

ScXMLDPSourceSQLContext::ScXMLDPSourceSQLContext( ScXMLImport& rImport,
                                      USHORT nPrfx,
                                      const ::rtl::OUString& rLName,
                                      const ::com::sun::star::uno::Reference<
                                      ::com::sun::star::xml::sax::XAttributeList>& xAttrList,
                                        ScXMLDataPilotTableContext* pTempDataPilotTable) :
    SvXMLImportContext( rImport, nPrfx, rLName )
{
    pDataPilotTable = pTempDataPilotTable;
    sal_Int16 nAttrCount = xAttrList.is() ? xAttrList->getLength() : 0;
    const SvXMLTokenMap& rAttrTokenMap = GetScImport().GetDatabaseRangeSourceSQLAttrTokenMap();
    for( sal_Int16 i=0; i < nAttrCount; i++ )
    {
        ::rtl::OUString sAttrName = xAttrList->getNameByIndex( i );
        ::rtl::OUString aLocalName;
        USHORT nPrefix = GetScImport().GetNamespaceMap().GetKeyByAttrName(
                                            sAttrName, &aLocalName );
        ::rtl::OUString sValue = xAttrList->getValueByIndex( i );

        switch( rAttrTokenMap.Get( nPrefix, aLocalName ) )
        {
            case XML_TOK_SOURCE_SQL_ATTR_DATABASE_NAME :
            {
                pDataPilotTable->SetDatabaseName(sValue);
            }
            break;
            case XML_TOK_SOURCE_SQL_ATTR_SQL_STATEMENT :
            {
                pDataPilotTable->SetSourceObject(sValue);
            }
            break;
            case XML_TOK_SOURCE_SQL_ATTR_PARSE_SQL_STATEMENT :
            {
                pDataPilotTable->SetNative(!IsXMLToken(sValue, XML_TRUE));
            }
            break;
        }
    }
}

ScXMLDPSourceSQLContext::~ScXMLDPSourceSQLContext()
{
}

SvXMLImportContext *ScXMLDPSourceSQLContext::CreateChildContext( USHORT nPrefix,
                                            const ::rtl::OUString& rLName,
                                            const ::com::sun::star::uno::Reference<
                                          ::com::sun::star::xml::sax::XAttributeList>& xAttrList )
{
    SvXMLImportContext *pContext = 0;

    if( !pContext )
        pContext = new SvXMLImportContext( GetImport(), nPrefix, rLName );

    return pContext;
}

void ScXMLDPSourceSQLContext::EndElement()
{
}

ScXMLDPSourceTableContext::ScXMLDPSourceTableContext( ScXMLImport& rImport,
                                      USHORT nPrfx,
                                      const ::rtl::OUString& rLName,
                                      const ::com::sun::star::uno::Reference<
                                      ::com::sun::star::xml::sax::XAttributeList>& xAttrList,
                                        ScXMLDataPilotTableContext* pTempDataPilotTable) :
    SvXMLImportContext( rImport, nPrfx, rLName )
{
    pDataPilotTable = pTempDataPilotTable;
    sal_Int16 nAttrCount = xAttrList.is() ? xAttrList->getLength() : 0;
    const SvXMLTokenMap& rAttrTokenMap = GetScImport().GetDatabaseRangeSourceTableAttrTokenMap();
    for( sal_Int16 i=0; i < nAttrCount; i++ )
    {
        ::rtl::OUString sAttrName = xAttrList->getNameByIndex( i );
        ::rtl::OUString aLocalName;
        USHORT nPrefix = GetScImport().GetNamespaceMap().GetKeyByAttrName(
                                            sAttrName, &aLocalName );
        ::rtl::OUString sValue = xAttrList->getValueByIndex( i );

        switch( rAttrTokenMap.Get( nPrefix, aLocalName ) )
        {
            case XML_TOK_SOURCE_TABLE_ATTR_DATABASE_NAME :
            {
                pDataPilotTable->SetDatabaseName(sValue);
            }
            break;
            case XML_TOK_SOURCE_TABLE_ATTR_TABLE_NAME :
            {
                pDataPilotTable->SetSourceObject(sValue);
            }
            break;
        }
    }
}

ScXMLDPSourceTableContext::~ScXMLDPSourceTableContext()
{
}

SvXMLImportContext *ScXMLDPSourceTableContext::CreateChildContext( USHORT nPrefix,
                                            const ::rtl::OUString& rLName,
                                            const ::com::sun::star::uno::Reference<
                                          ::com::sun::star::xml::sax::XAttributeList>& xAttrList )
{
    SvXMLImportContext *pContext = 0;

    if( !pContext )
        pContext = new SvXMLImportContext( GetImport(), nPrefix, rLName );

    return pContext;
}

void ScXMLDPSourceTableContext::EndElement()
{
}

ScXMLDPSourceQueryContext::ScXMLDPSourceQueryContext( ScXMLImport& rImport,
                                      USHORT nPrfx,
                                      const ::rtl::OUString& rLName,
                                      const ::com::sun::star::uno::Reference<
                                      ::com::sun::star::xml::sax::XAttributeList>& xAttrList,
                                        ScXMLDataPilotTableContext* pTempDataPilotTable) :
    SvXMLImportContext( rImport, nPrfx, rLName )
{
    pDataPilotTable = pTempDataPilotTable;
    sal_Int16 nAttrCount = xAttrList.is() ? xAttrList->getLength() : 0;
    const SvXMLTokenMap& rAttrTokenMap = GetScImport().GetDatabaseRangeSourceQueryAttrTokenMap();
    for( sal_Int16 i=0; i < nAttrCount; i++ )
    {
        ::rtl::OUString sAttrName = xAttrList->getNameByIndex( i );
        ::rtl::OUString aLocalName;
        USHORT nPrefix = GetScImport().GetNamespaceMap().GetKeyByAttrName(
                                            sAttrName, &aLocalName );
        ::rtl::OUString sValue = xAttrList->getValueByIndex( i );

        switch( rAttrTokenMap.Get( nPrefix, aLocalName ) )
        {
            case XML_TOK_SOURCE_QUERY_ATTR_DATABASE_NAME :
            {
                pDataPilotTable->SetDatabaseName(sValue);
            }
            break;
            case XML_TOK_SOURCE_QUERY_ATTR_QUERY_NAME :
            {
                pDataPilotTable->SetSourceObject(sValue);
            }
            break;
        }
    }
}

ScXMLDPSourceQueryContext::~ScXMLDPSourceQueryContext()
{
}

SvXMLImportContext *ScXMLDPSourceQueryContext::CreateChildContext( USHORT nPrefix,
                                            const ::rtl::OUString& rLName,
                                            const ::com::sun::star::uno::Reference<
                                          ::com::sun::star::xml::sax::XAttributeList>& xAttrList )
{
    SvXMLImportContext *pContext = 0;

    if( !pContext )
        pContext = new SvXMLImportContext( GetImport(), nPrefix, rLName );

    return pContext;
}

void ScXMLDPSourceQueryContext::EndElement()
{
}

ScXMLSourceServiceContext::ScXMLSourceServiceContext( ScXMLImport& rImport,
                                      USHORT nPrfx,
                                      const ::rtl::OUString& rLName,
                                      const ::com::sun::star::uno::Reference<
                                      ::com::sun::star::xml::sax::XAttributeList>& xAttrList,
                                        ScXMLDataPilotTableContext* pTempDataPilotTable) :
    SvXMLImportContext( rImport, nPrfx, rLName )
{
    pDataPilotTable = pTempDataPilotTable;
    sal_Int16 nAttrCount = xAttrList.is() ? xAttrList->getLength() : 0;
    const SvXMLTokenMap& rAttrTokenMap = GetScImport().GetDataPilotTableSourceServiceAttrTokenMap();
    for( sal_Int16 i=0; i < nAttrCount; i++ )
    {
        ::rtl::OUString sAttrName = xAttrList->getNameByIndex( i );
        ::rtl::OUString aLocalName;
        USHORT nPrefix = GetScImport().GetNamespaceMap().GetKeyByAttrName(
                                            sAttrName, &aLocalName );
        ::rtl::OUString sValue = xAttrList->getValueByIndex( i );

        switch( rAttrTokenMap.Get( nPrefix, aLocalName ) )
        {
            case XML_TOK_SOURCE_SERVICE_ATTR_NAME :
            {
                pDataPilotTable->SetServiceName(sValue);
            }
            break;
            case XML_TOK_SOURCE_SERVICE_ATTR_SOURCE_NAME :
            {
                pDataPilotTable->SetServiceSourceName(sValue);
            }
            break;
            case XML_TOK_SOURCE_SERVICE_ATTR_OBJECT_NAME :
            {
                pDataPilotTable->SetServiceSourceObject(sValue);
            }
            break;
            case XML_TOK_SOURCE_SERVICE_ATTR_USERNAME :
            {
                pDataPilotTable->SetServiceUsername(sValue);
            }
            break;
            case XML_TOK_SOURCE_SERVICE_ATTR_PASSWORD :
            {
                pDataPilotTable->SetServicePassword(sValue);
            }
            break;
        }
    }
}

ScXMLSourceServiceContext::~ScXMLSourceServiceContext()
{
}

SvXMLImportContext *ScXMLSourceServiceContext::CreateChildContext( USHORT nPrefix,
                                            const ::rtl::OUString& rLName,
                                            const ::com::sun::star::uno::Reference<
                                          ::com::sun::star::xml::sax::XAttributeList>& xAttrList )
{
    SvXMLImportContext *pContext = 0;

    if( !pContext )
        pContext = new SvXMLImportContext( GetImport(), nPrefix, rLName );

    return pContext;
}

void ScXMLSourceServiceContext::EndElement()
{
}

ScXMLSourceCellRangeContext::ScXMLSourceCellRangeContext( ScXMLImport& rImport,
                                      USHORT nPrfx,
                                      const ::rtl::OUString& rLName,
                                      const ::com::sun::star::uno::Reference<
                                      ::com::sun::star::xml::sax::XAttributeList>& xAttrList,
                                        ScXMLDataPilotTableContext* pTempDataPilotTable) :
    SvXMLImportContext( rImport, nPrfx, rLName )
{
    pDataPilotTable = pTempDataPilotTable;
    sal_Int16 nAttrCount = xAttrList.is() ? xAttrList->getLength() : 0;
    const SvXMLTokenMap& rAttrTokenMap = GetScImport().GetDataPilotTableSourceCellRangeAttrTokenMap();
    for( sal_Int16 i=0; i < nAttrCount; i++ )
    {
        ::rtl::OUString sAttrName = xAttrList->getNameByIndex( i );
        ::rtl::OUString aLocalName;
        USHORT nPrefix = GetScImport().GetNamespaceMap().GetKeyByAttrName(
                                            sAttrName, &aLocalName );
        ::rtl::OUString sValue = xAttrList->getValueByIndex( i );

        switch( rAttrTokenMap.Get( nPrefix, aLocalName ) )
        {
            case XML_TOK_SOURCE_CELL_RANGE_ATTR_CELL_RANGE_ADDRESS :
            {
                ScRange aSourceRangeAddress;
                sal_Int32 nOffset(0);
                if (ScXMLConverter::GetRangeFromString( aSourceRangeAddress, sValue, GetScImport().GetDocument(), nOffset ))
                    pDataPilotTable->SetSourceCellRangeAddress(aSourceRangeAddress);
            }
            break;
        }
    }
}

ScXMLSourceCellRangeContext::~ScXMLSourceCellRangeContext()
{
}

SvXMLImportContext *ScXMLSourceCellRangeContext::CreateChildContext( USHORT nPrefix,
                                            const ::rtl::OUString& rLName,
                                            const ::com::sun::star::uno::Reference<
                                          ::com::sun::star::xml::sax::XAttributeList>& xAttrList )
{
    SvXMLImportContext *pContext = 0;

    const SvXMLTokenMap& rTokenMap = GetScImport().GetDataPilotTableSourceCellRangeElemTokenMap();
    switch( rTokenMap.Get( nPrefix, rLName ) )
    {
        case XML_TOK_SOURCE_CELL_RANGE_ELEM_FILTER :
            pContext = new ScXMLDPFilterContext(GetScImport(), nPrefix, rLName, xAttrList, pDataPilotTable);
        break;
    }

    if( !pContext )
        pContext = new SvXMLImportContext( GetImport(), nPrefix, rLName );

    return pContext;
}

void ScXMLSourceCellRangeContext::EndElement()
{
}

ScXMLDataPilotFieldContext::ScXMLDataPilotFieldContext( ScXMLImport& rImport,
                                      USHORT nPrfx,
                                      const ::rtl::OUString& rLName,
                                      const ::com::sun::star::uno::Reference<
                                      ::com::sun::star::xml::sax::XAttributeList>& xAttrList,
                                        ScXMLDataPilotTableContext* pTempDataPilotTable) :
    SvXMLImportContext( rImport, nPrfx, rLName ),
    pDim(NULL)
{
    pDataPilotTable = pTempDataPilotTable;
    ::rtl::OUString sName;
    sal_Bool bHasName(sal_False);
    sal_Bool bDataLayout(sal_False);
    nUsedHierarchy = 1;
    sal_Int16 nAttrCount = xAttrList.is() ? xAttrList->getLength() : 0;
    const SvXMLTokenMap& rAttrTokenMap = GetScImport().GetDataPilotFieldAttrTokenMap();
    for( sal_Int16 i=0; i < nAttrCount; i++ )
    {
        ::rtl::OUString sAttrName = xAttrList->getNameByIndex( i );
        ::rtl::OUString aLocalName;
        USHORT nPrefix = GetScImport().GetNamespaceMap().GetKeyByAttrName(
                                            sAttrName, &aLocalName );
        ::rtl::OUString sValue = xAttrList->getValueByIndex( i );

        switch( rAttrTokenMap.Get( nPrefix, aLocalName ) )
        {
            case XML_TOK_DATA_PILOT_FIELD_ATTR_SOURCE_FIELD_NAME :
            {
                sName = sValue;
                bHasName = sal_True;
            }
            break;
            case XML_TOK_DATA_PILOT_FIELD_ATTR_IS_DATA_LAYOUT_FIELD :
            {
                bDataLayout = IsXMLToken(sValue, XML_TRUE);
            }
            break;
            case XML_TOK_DATA_PILOT_FIELD_ATTR_FUNCTION :
            {
                nFunction = (sal_Int16) ScXMLConverter::GetFunctionFromString( sValue );
            }
            break;
            case XML_TOK_DATA_PILOT_FIELD_ATTR_ORIENTATION :
            {
                nOrientation = (sal_Int16) ScXMLConverter::GetOrientationFromString( sValue );
            }
            break;
            case XML_TOK_DATA_PILOT_FIELD_ATTR_USED_HIERARCHY :
            {
                nUsedHierarchy = sValue.toInt32();
            }
            break;
        }
    }
    if (bHasName)
        pDim = new ScDPSaveDimension(String(sName), bDataLayout);
}

ScXMLDataPilotFieldContext::~ScXMLDataPilotFieldContext()
{
}

SvXMLImportContext *ScXMLDataPilotFieldContext::CreateChildContext( USHORT nPrefix,
                                            const ::rtl::OUString& rLName,
                                            const ::com::sun::star::uno::Reference<
                                          ::com::sun::star::xml::sax::XAttributeList>& xAttrList )
{
    SvXMLImportContext *pContext = 0;

    const SvXMLTokenMap& rTokenMap = GetScImport().GetDataPilotFieldElemTokenMap();
    switch( rTokenMap.Get( nPrefix, rLName ) )
    {
        case XML_TOK_DATA_PILOT_FIELD_ELEM_DATA_PILOT_LEVEL :
            pContext = new ScXMLDataPilotLevelContext(GetScImport(), nPrefix, rLName, xAttrList, this);
        break;
    }

    if( !pContext )
        pContext = new SvXMLImportContext( GetImport(), nPrefix, rLName );

    return pContext;
}

void ScXMLDataPilotFieldContext::EndElement()
{
    if (pDim)
    {
        pDim->SetUsedHierarchy(nUsedHierarchy);
        pDim->SetFunction(nFunction);
        pDim->SetOrientation(nOrientation);
        pDataPilotTable->AddDimension(pDim);
    }
}

ScXMLDataPilotLevelContext::ScXMLDataPilotLevelContext( ScXMLImport& rImport,
                                      USHORT nPrfx,
                                      const ::rtl::OUString& rLName,
                                      const ::com::sun::star::uno::Reference<
                                      ::com::sun::star::xml::sax::XAttributeList>& xAttrList,
                                        ScXMLDataPilotFieldContext* pTempDataPilotField) :
    SvXMLImportContext( rImport, nPrfx, rLName )
{
    pDataPilotField = pTempDataPilotField;
    sal_Int16 nAttrCount = xAttrList.is() ? xAttrList->getLength() : 0;
    const SvXMLTokenMap& rAttrTokenMap = GetScImport().GetDataPilotLevelAttrTokenMap();
    for( sal_Int16 i=0; i < nAttrCount; i++ )
    {
        ::rtl::OUString sAttrName = xAttrList->getNameByIndex( i );
        ::rtl::OUString aLocalName;
        USHORT nPrefix = GetScImport().GetNamespaceMap().GetKeyByAttrName(
                                            sAttrName, &aLocalName );
        ::rtl::OUString sValue = xAttrList->getValueByIndex( i );

        switch( rAttrTokenMap.Get( nPrefix, aLocalName ) )
        {
            case XML_TOK_DATA_PILOT_LEVEL_ATTR_DISPLAY_EMPTY :
            {
                pDataPilotField->SetShowEmpty(IsXMLToken(sValue, XML_TRUE));
            }
            break;
        }
    }
}

ScXMLDataPilotLevelContext::~ScXMLDataPilotLevelContext()
{
}

SvXMLImportContext *ScXMLDataPilotLevelContext::CreateChildContext( USHORT nPrefix,
                                            const ::rtl::OUString& rLName,
                                            const ::com::sun::star::uno::Reference<
                                          ::com::sun::star::xml::sax::XAttributeList>& xAttrList )
{
    SvXMLImportContext *pContext = 0;

    const SvXMLTokenMap& rTokenMap = GetScImport().GetDataPilotLevelElemTokenMap();
    switch( rTokenMap.Get( nPrefix, rLName ) )
    {
        case XML_TOK_DATA_PILOT_LEVEL_ELEM_DATA_PILOT_SUBTOTALS :
            pContext = new ScXMLDataPilotSubTotalsContext(GetScImport(), nPrefix, rLName, xAttrList, pDataPilotField);
        break;
        case XML_TOK_DATA_PILOT_LEVEL_ELEM_DATA_PILOT_MEMBERS :
            pContext = new ScXMLDataPilotMembersContext(GetScImport(), nPrefix, rLName, xAttrList, pDataPilotField);
        break;
    }

    if( !pContext )
        pContext = new SvXMLImportContext( GetImport(), nPrefix, rLName );

    return pContext;
}

void ScXMLDataPilotLevelContext::EndElement()
{
}

ScXMLDataPilotSubTotalsContext::ScXMLDataPilotSubTotalsContext( ScXMLImport& rImport,
                                      USHORT nPrfx,
                                      const ::rtl::OUString& rLName,
                                      const ::com::sun::star::uno::Reference<
                                      ::com::sun::star::xml::sax::XAttributeList>& xAttrList,
                                        ScXMLDataPilotFieldContext* pTempDataPilotField) :
    SvXMLImportContext( rImport, nPrfx, rLName ),
    pFunctions(NULL),
    nFunctionCount(0)
{
    pDataPilotField = pTempDataPilotField;

    // has no attributes
}

ScXMLDataPilotSubTotalsContext::~ScXMLDataPilotSubTotalsContext()
{
}

SvXMLImportContext *ScXMLDataPilotSubTotalsContext::CreateChildContext( USHORT nPrefix,
                                            const ::rtl::OUString& rLName,
                                            const ::com::sun::star::uno::Reference<
                                          ::com::sun::star::xml::sax::XAttributeList>& xAttrList )
{
    SvXMLImportContext *pContext = 0;

    const SvXMLTokenMap& rTokenMap = GetScImport().GetDataPilotSubTotalsElemTokenMap();
    switch( rTokenMap.Get( nPrefix, rLName ) )
    {
        case XML_TOK_DATA_PILOT_SUBTOTALS_ELEM_DATA_PILOT_SUBTOTAL :
            pContext = new ScXMLDataPilotSubTotalContext(GetScImport(), nPrefix, rLName, xAttrList, this);
        break;
    }

    if( !pContext )
        pContext = new SvXMLImportContext( GetImport(), nPrefix, rLName );

    return pContext;
}

void ScXMLDataPilotSubTotalsContext::EndElement()
{
    pDataPilotField->SetSubTotals(pFunctions, nFunctionCount);
}

void ScXMLDataPilotSubTotalsContext::AddFunction(sal_Int16 nFunction)
{
    if (nFunctionCount)
    {
        nFunctionCount++;
        sal_uInt16* pTemp = new sal_uInt16[nFunctionCount];
        for (sal_Int16 i = 0; i < nFunctionCount - 1; i++)
            pTemp[i] = pFunctions[i];
        pTemp[nFunctionCount - 1] = nFunction;
        delete[] pFunctions;
        pFunctions = pTemp;
    }
    else
    {
        nFunctionCount = 1;
        pFunctions = new sal_uInt16[nFunctionCount];
        pFunctions[0] = nFunction;
    }
}

ScXMLDataPilotSubTotalContext::ScXMLDataPilotSubTotalContext( ScXMLImport& rImport,
                                      USHORT nPrfx,
                                      const ::rtl::OUString& rLName,
                                      const ::com::sun::star::uno::Reference<
                                      ::com::sun::star::xml::sax::XAttributeList>& xAttrList,
                                        ScXMLDataPilotSubTotalsContext* pTempDataPilotSubTotals) :
    SvXMLImportContext( rImport, nPrfx, rLName )
{
    pDataPilotSubTotals = pTempDataPilotSubTotals;
    sal_Int16 nAttrCount = xAttrList.is() ? xAttrList->getLength() : 0;
    const SvXMLTokenMap& rAttrTokenMap = GetScImport().GetDataPilotSubTotalAttrTokenMap();
    for( sal_Int16 i=0; i < nAttrCount; i++ )
    {
        ::rtl::OUString sAttrName = xAttrList->getNameByIndex( i );
        ::rtl::OUString aLocalName;
        USHORT nPrefix = GetScImport().GetNamespaceMap().GetKeyByAttrName(
                                            sAttrName, &aLocalName );
        ::rtl::OUString sValue = xAttrList->getValueByIndex( i );

        switch( rAttrTokenMap.Get( nPrefix, aLocalName ) )
        {
            case XML_TOK_DATA_PILOT_SUBTOTAL_ATTR_FUNCTION :
            {
                pDataPilotSubTotals->AddFunction( ScXMLConverter::GetFunctionFromString( sValue ) );
            }
            break;
        }
    }
}

ScXMLDataPilotSubTotalContext::~ScXMLDataPilotSubTotalContext()
{
}

SvXMLImportContext *ScXMLDataPilotSubTotalContext::CreateChildContext( USHORT nPrefix,
                                            const ::rtl::OUString& rLName,
                                            const ::com::sun::star::uno::Reference<
                                          ::com::sun::star::xml::sax::XAttributeList>& xAttrList )
{
    SvXMLImportContext *pContext = 0;

    if( !pContext )
        pContext = new SvXMLImportContext( GetImport(), nPrefix, rLName );

    return pContext;
}

void ScXMLDataPilotSubTotalContext::EndElement()
{
}

ScXMLDataPilotMembersContext::ScXMLDataPilotMembersContext( ScXMLImport& rImport,
                                      USHORT nPrfx,
                                      const ::rtl::OUString& rLName,
                                      const ::com::sun::star::uno::Reference<
                                      ::com::sun::star::xml::sax::XAttributeList>& xAttrList,
                                        ScXMLDataPilotFieldContext* pTempDataPilotField) :
    SvXMLImportContext( rImport, nPrfx, rLName )
{
    pDataPilotField = pTempDataPilotField;

    // has no attributes
}

ScXMLDataPilotMembersContext::~ScXMLDataPilotMembersContext()
{
}

SvXMLImportContext *ScXMLDataPilotMembersContext::CreateChildContext( USHORT nPrefix,
                                            const ::rtl::OUString& rLName,
                                            const ::com::sun::star::uno::Reference<
                                          ::com::sun::star::xml::sax::XAttributeList>& xAttrList )
{
    SvXMLImportContext *pContext = 0;

    const SvXMLTokenMap& rTokenMap = GetScImport().GetDataPilotMembersElemTokenMap();
    switch( rTokenMap.Get( nPrefix, rLName ) )
    {
        case XML_TOK_DATA_PILOT_MEMBERS_ELEM_DATA_PILOT_MEMBER :
            pContext = new ScXMLDataPilotMemberContext(GetScImport(), nPrefix, rLName, xAttrList, pDataPilotField);
        break;
    }

    if( !pContext )
        pContext = new SvXMLImportContext( GetImport(), nPrefix, rLName );

    return pContext;
}

void ScXMLDataPilotMembersContext::EndElement()
{
}

ScXMLDataPilotMemberContext::ScXMLDataPilotMemberContext( ScXMLImport& rImport,
                                      USHORT nPrfx,
                                      const ::rtl::OUString& rLName,
                                      const ::com::sun::star::uno::Reference<
                                      ::com::sun::star::xml::sax::XAttributeList>& xAttrList,
                                        ScXMLDataPilotFieldContext* pTempDataPilotField) :
    SvXMLImportContext( rImport, nPrfx, rLName )
{
    pDataPilotField = pTempDataPilotField;
    sal_Int16 nAttrCount = xAttrList.is() ? xAttrList->getLength() : 0;
    const SvXMLTokenMap& rAttrTokenMap = GetScImport().GetDataPilotMemberAttrTokenMap();
    for( sal_Int16 i=0; i < nAttrCount; i++ )
    {
        ::rtl::OUString sAttrName = xAttrList->getNameByIndex( i );
        ::rtl::OUString aLocalName;
        USHORT nPrefix = GetScImport().GetNamespaceMap().GetKeyByAttrName(
                                            sAttrName, &aLocalName );
        ::rtl::OUString sValue = xAttrList->getValueByIndex( i );

        switch( rAttrTokenMap.Get( nPrefix, aLocalName ) )
        {
            case XML_TOK_DATA_PILOT_MEMBER_ATTR_NAME :
            {
                sName = sValue;
            }
            break;
            case XML_TOK_DATA_PILOT_MEMBER_ATTR_DISPLAY :
            {
                bDisplay = IsXMLToken(sValue, XML_TRUE);
            }
            break;
            case XML_TOK_DATA_PILOT_MEMBER_ATTR_DISPLAY_DETAILS :
            {
                bDisplayDetails = IsXMLToken(sValue, XML_TRUE);
            }
            break;
        }
    }
}

ScXMLDataPilotMemberContext::~ScXMLDataPilotMemberContext()
{
}

SvXMLImportContext *ScXMLDataPilotMemberContext::CreateChildContext( USHORT nPrefix,
                                            const ::rtl::OUString& rLName,
                                            const ::com::sun::star::uno::Reference<
                                          ::com::sun::star::xml::sax::XAttributeList>& xAttrList )
{
    SvXMLImportContext *pContext = 0;

    if( !pContext )
        pContext = new SvXMLImportContext( GetImport(), nPrefix, rLName );

    return pContext;
}

void ScXMLDataPilotMemberContext::EndElement()
{
    if (sName.getLength())
    {
        ScDPSaveMember* pMember = new ScDPSaveMember(String(sName));
        pMember->SetIsVisible(bDisplay);
        pMember->SetShowDetails(bDisplayDetails);
        pDataPilotField->AddMember(pMember);
    }
}


}
