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

#ifndef _XMLOFF_DOCUMENTSETTINGSCONTEXT_HXX
#include "DocumentSettingsContext.hxx"
#endif
#ifndef _XMLOFF_XMLIMP_HXX
#include "xmlimp.hxx"
#endif
#ifndef _XMLOFF_XMLNMSPE_HXX
#include "xmlnmspe.hxx"
#endif
#ifndef _XMLOFF_NMSPMAP_HXX
#include "nmspmap.hxx"
#endif
#ifndef _XMLOFF_XMLUCONV_HXX
#include "xmluconv.hxx"
#endif
#ifndef _TOOLS_DEBUG_HXX
#include <tools/debug.hxx>
#endif

#ifndef __SGI_STL_LIST
#include <list>
#endif

#ifndef _COM_SUN_STAR_I18N_XFORBIDDENCHARACTERS_HPP_
#include <com/sun/star/i18n/XForbiddenCharacters.hpp>
#endif
#ifndef _COM_SUN_STAR_CONTAINER_XINDEXCONTAINER_HPP_
#include <com/sun/star/container/XIndexContainer.hpp>
#endif
#ifndef _COM_SUN_STAR_FORMULA_SYMBOLDESCRIPTOR_HPP_
#include <com/sun/star/formula/SymbolDescriptor.hpp>
#endif

// #110680#
//#ifndef _COMPHELPER_PROCESSFACTORY_HXX_
//#include <comphelper/processfactory.hxx>
//#endif

#ifndef _COM_SUN_STAR_UTIL_DATETIME_HPP_
#include <com/sun/star/util/DateTime.hpp>
#endif
#ifndef _COM_SUN_STAR_DOCUMENT_XVIEWDATASUPPLIER_HPP_
#include <com/sun/star/document/XViewDataSupplier.hpp>
#endif
#ifndef _COM_SUN_STAR_DOCUMENT_PRINTERINDEPENDENTLAYOUT_HPP_
#include <com/sun/star/document/PrinterIndependentLayout.hpp>
#endif
#ifndef _XMLENUMS_HXX_
#include <xmlenums.hxx>
#endif
namespace binfilter {

using namespace ::com::sun::star;
using namespace ::binfilter::xmloff::token;


//------------------------------------------------------------------

class XMLMyList
{
    std::list<beans::PropertyValue>	aProps;
    sal_uInt32						nCount;

    // #110680#
    ::com::sun::star::uno::Reference< ::com::sun::star::lang::XMultiServiceFactory > mxServiceFactory;

public:
    // #110680#
    XMLMyList(const uno::Reference<lang::XMultiServiceFactory>& xServiceFactory);
    ~XMLMyList();

    void push_back(beans::PropertyValue& aProp) { aProps.push_back(aProp); nCount++; }
    uno::Sequence<beans::PropertyValue> GetSequence();
    uno::Reference<container::XNameContainer> GetNameContainer();
    uno::Reference<container::XIndexContainer> GetIndexContainer();
};

// #110680#
XMLMyList::XMLMyList(const uno::Reference<lang::XMultiServiceFactory>& xServiceFactory)
:	nCount(0),
    mxServiceFactory(xServiceFactory)
{
    DBG_ASSERT( mxServiceFactory.is(), "got no service manager" );
}

// #110680#
XMLMyList::~XMLMyList() 
{
}

uno::Sequence<beans::PropertyValue> XMLMyList::GetSequence()
{
    uno::Sequence<beans::PropertyValue> aSeq;
    if(nCount)
    {
        DBG_ASSERT(nCount == aProps.size(), "wrong count of PropertyValue");
        aSeq.realloc(nCount);
        beans::PropertyValue* pProps = aSeq.getArray();
        std::list<beans::PropertyValue>::iterator aItr = aProps.begin();
        while (aItr != aProps.end())
        {
            *pProps = *aItr;
            pProps++;
            aItr++;
        }
    }
    return aSeq;
}

uno::Reference<container::XNameContainer> XMLMyList::GetNameContainer()
{
    uno::Reference<container::XNameContainer> xNameContainer;
    
    // #110680#
    // uno::Reference<lang::XMultiServiceFactory> xServiceFactory = comphelper::getProcessServiceFactory();
    // DBG_ASSERT( xServiceFactory.is(), "got no service manager" );

    if( mxServiceFactory.is() )
    {
        ::rtl::OUString sName(RTL_CONSTASCII_USTRINGPARAM("com.sun.star.document.NamedPropertyValues"));
        xNameContainer = uno::Reference<container::XNameContainer>(mxServiceFactory->createInstance(sName), uno::UNO_QUERY);
        if (xNameContainer.is())
        {
            std::list<beans::PropertyValue>::iterator aItr = aProps.begin();
            while (aItr != aProps.end())
            {
                xNameContainer->insertByName(aItr->Name, aItr->Value);
                aItr++;
            }
        }
    }
    return xNameContainer;
}

uno::Reference<container::XIndexContainer> XMLMyList::GetIndexContainer()
{
    uno::Reference<container::XIndexContainer> xIndexContainer;
    // #110680#
    // uno::Reference<lang::XMultiServiceFactory> xServiceFactory = comphelper::getProcessServiceFactory();
    // DBG_ASSERT( xServiceFactory.is(), "got no service manager" );

    if( mxServiceFactory.is() )
    {
        ::rtl::OUString sName(RTL_CONSTASCII_USTRINGPARAM("com.sun.star.document.IndexedPropertyValues"));
        xIndexContainer = uno::Reference<container::XIndexContainer>(mxServiceFactory->createInstance(sName), uno::UNO_QUERY);
        if (xIndexContainer.is())
        {
            std::list<beans::PropertyValue>::iterator aItr = aProps.begin();
            sal_uInt32 i(0);
            while (aItr != aProps.end())
            {
                xIndexContainer->insertByIndex(i, aItr->Value);
                aItr++;
                i++;
            }
        }
    }
    return xIndexContainer;
}

//=============================================================================

class XMLConfigBaseContext : public SvXMLImportContext
{
protected:
    XMLMyList					aProps;
    beans::PropertyValue		aProp;
    ::com::sun::star::uno::Any&	rAny;
    XMLConfigBaseContext*		pBaseContext;
public:
    XMLConfigBaseContext(SvXMLImport& rImport, USHORT nPrfx, const ::rtl::OUString& rLName,
                                    ::com::sun::star::uno::Any& rAny,
                                    XMLConfigBaseContext* pBaseContext);
    virtual ~XMLConfigBaseContext();

    void AddPropertyValue() { aProps.push_back(aProp); }
};

//=============================================================================

class XMLConfigItemContext : public SvXMLImportContext
{
    ::rtl::OUString				sType;
    ::rtl::OUString				sValue;
    uno::Sequence<sal_Int8>		aDecoded;
    ::com::sun::star::uno::Any&	rAny;
    const ::rtl::OUString         rItemName;
    XMLConfigBaseContext*		pBaseContext;

public:
    XMLConfigItemContext(SvXMLImport& rImport, USHORT nPrfx, const ::rtl::OUString& rLName,
                                    const ::com::sun::star::uno::Reference<
                                    ::com::sun::star::xml::sax::XAttributeList>& xAttrList,
                                    ::com::sun::star::uno::Any& rAny,
                                    const ::rtl::OUString& rItemName,
                                    XMLConfigBaseContext* pBaseContext);
    virtual ~XMLConfigItemContext();

    virtual SvXMLImportContext *CreateChildContext( USHORT nPrefix,
                                                    const ::rtl::OUString& rLocalName,
                                                    const ::com::sun::star::uno::Reference<
                                          ::com::sun::star::xml::sax::XAttributeList>& xAttrList );
    virtual void Characters( const ::rtl::OUString& rChars );

    virtual void EndElement();

    virtual void ManipulateConfigItem();
};

//=============================================================================

class XMLConfigItemSetContext : public XMLConfigBaseContext
{
public:
    XMLConfigItemSetContext(SvXMLImport& rImport, USHORT nPrfx, const ::rtl::OUString& rLName,
                                    const ::com::sun::star::uno::Reference<
                                    ::com::sun::star::xml::sax::XAttributeList>& xAttrList,
                                    ::com::sun::star::uno::Any& rAny,
                                    XMLConfigBaseContext* pBaseContext);
    virtual ~XMLConfigItemSetContext();

    virtual SvXMLImportContext *CreateChildContext( USHORT nPrefix,
                                                    const ::rtl::OUString& rLocalName,
                                                    const ::com::sun::star::uno::Reference<
                                          ::com::sun::star::xml::sax::XAttributeList>& xAttrList );

    virtual void EndElement();
};

//=============================================================================

class XMLConfigItemMapNamedContext : public XMLConfigBaseContext
{
public:
    XMLConfigItemMapNamedContext(SvXMLImport& rImport, USHORT nPrfx, const ::rtl::OUString& rLName,
                                    const ::com::sun::star::uno::Reference<
                                    ::com::sun::star::xml::sax::XAttributeList>& xAttrList,
                                    ::com::sun::star::uno::Any& rAny,
                                    XMLConfigBaseContext* pBaseContext);
    virtual ~XMLConfigItemMapNamedContext();

    virtual SvXMLImportContext *CreateChildContext( USHORT nPrefix,
                                                    const ::rtl::OUString& rLocalName,
                                                    const ::com::sun::star::uno::Reference<
                                          ::com::sun::star::xml::sax::XAttributeList>& xAttrList );

    virtual void EndElement();
};

//=============================================================================

class XMLConfigItemMapIndexedContext : public XMLConfigBaseContext
{
private:
    ::rtl::OUString maConfigItemName;

public:
    XMLConfigItemMapIndexedContext(SvXMLImport& rImport, USHORT nPrfx,
                                    const ::rtl::OUString& rLName,
                                    const ::com::sun::star::uno::Reference<
                                    ::com::sun::star::xml::sax::XAttributeList>& xAttrList,
                                    ::com::sun::star::uno::Any& rAny,
                                    const ::rtl::OUString& rConfigItemName,
                                    XMLConfigBaseContext* pBaseContext);
    virtual ~XMLConfigItemMapIndexedContext();

    virtual SvXMLImportContext *CreateChildContext( USHORT nPrefix,
                                                    const ::rtl::OUString& rLocalName,
                                                    const ::com::sun::star::uno::Reference<
                                        ::com::sun::star::xml::sax::XAttributeList>& xAttrList );

    virtual void EndElement();
};

//=============================================================================

SvXMLImportContext *CreateSettingsContext(SvXMLImport& rImport, USHORT nPrefix,
                        const ::rtl::OUString& rLocalName,
                        const uno::Reference<xml::sax::XAttributeList>& xAttrList,
                        beans::PropertyValue& rProp, XMLConfigBaseContext* pBaseContext)
{
    SvXMLImportContext *pContext = 0;

    rProp.Name = ::rtl::OUString();
    sal_Int16 nAttrCount = xAttrList.is() ? xAttrList->getLength() : 0;
    for( sal_Int16 i=0; i < nAttrCount; i++ )
    {
        ::rtl::OUString sAttrName = xAttrList->getNameByIndex( i );
        ::rtl::OUString aLocalName;
        USHORT nPrefix = rImport.GetNamespaceMap().GetKeyByAttrName(
                                            sAttrName, &aLocalName );
        ::rtl::OUString sValue = xAttrList->getValueByIndex( i );

        if (nPrefix == XML_NAMESPACE_CONFIG)
        {
            if (IsXMLToken(aLocalName, XML_NAME))
                rProp.Name = sValue;
        }
    }

    if (nPrefix == XML_NAMESPACE_CONFIG)
    {
        if (IsXMLToken(rLocalName, XML_CONFIG_ITEM))
            pContext = new XMLConfigItemContext(rImport, nPrefix, rLocalName, xAttrList, rProp.Value, rProp.Name, pBaseContext);
        else if((IsXMLToken(rLocalName, XML_CONFIG_ITEM_SET)) ||
                (IsXMLToken(rLocalName, XML_CONFIG_ITEM_MAP_ENTRY)) )
            pContext = new XMLConfigItemSetContext(rImport, nPrefix, rLocalName, xAttrList, rProp.Value, pBaseContext);
        else if(IsXMLToken(rLocalName, XML_CONFIG_ITEM_MAP_NAMED))
            pContext = new XMLConfigItemMapNamedContext(rImport, nPrefix, rLocalName, xAttrList, rProp.Value, pBaseContext);
        else if(IsXMLToken(rLocalName, XML_CONFIG_ITEM_MAP_INDEXED))
            pContext = new XMLConfigItemMapIndexedContext(rImport, nPrefix, rLocalName, xAttrList, rProp.Value, rProp.Name, pBaseContext);
    }

    if( !pContext )
        pContext = new SvXMLImportContext( rImport, nPrefix, rLocalName );

    return pContext;
}

//=============================================================================

XMLDocumentSettingsContext::XMLDocumentSettingsContext(SvXMLImport& rImport, USHORT nPrfx, const ::rtl::OUString& rLName,
                    const uno::Reference<xml::sax::XAttributeList>& xAttrList )
    : SvXMLImportContext( rImport, nPrfx, rLName )
{
    // here are no attributes
}

XMLDocumentSettingsContext::~XMLDocumentSettingsContext()
{
}

SvXMLImportContext *XMLDocumentSettingsContext::CreateChildContext( USHORT nPrefix,
                                     const ::rtl::OUString& rLocalName,
                                     const ::com::sun::star::uno::Reference<
                                          ::com::sun::star::xml::sax::XAttributeList>& xAttrList )
{
    SvXMLImportContext *pContext = 0;
    ::rtl::OUString sName;

    sal_Int16 nAttrCount = xAttrList.is() ? xAttrList->getLength() : 0;
    for( sal_Int16 i=0; i < nAttrCount; i++ )
    {
        ::rtl::OUString sAttrName = xAttrList->getNameByIndex( i );
        ::rtl::OUString aLocalName;
        USHORT nPrefix = GetImport().GetNamespaceMap().GetKeyByAttrName(
                                            sAttrName, &aLocalName );
        ::rtl::OUString sValue = xAttrList->getValueByIndex( i );

        if (nPrefix == XML_NAMESPACE_CONFIG)
        {
            if (IsXMLToken(aLocalName, XML_NAME))
                sName = sValue;
        }
    }

    if (nPrefix == XML_NAMESPACE_CONFIG)
    {
        if (IsXMLToken(rLocalName, XML_CONFIG_ITEM_SET))
        {
            if (IsXMLToken(sName, XML_VIEW_SETTINGS))
                pContext = new XMLConfigItemSetContext(GetImport(), nPrefix, rLocalName, xAttrList, aViewProps, NULL);
            else if (IsXMLToken(sName, XML_CONFIGURATION_SETTINGS))
                pContext = new XMLConfigItemSetContext(GetImport(), nPrefix, rLocalName, xAttrList, aConfigProps, NULL);
        }
    }

    if( !pContext )
        pContext = new SvXMLImportContext( GetImport(), nPrefix, rLocalName );

    return pContext;
}

void XMLDocumentSettingsContext::EndElement()
{
    uno::Sequence<beans::PropertyValue> aSeqViewProps;
    if (aViewProps >>= aSeqViewProps)
    {
        GetImport().SetViewSettings(aSeqViewProps);
        sal_Int32 i(aSeqViewProps.getLength() - 1);
        sal_Bool bFound(sal_False);
        while((i >= 0) && !bFound)
        {
            if (aSeqViewProps[i].Name.compareToAscii("Views") == 0)
            {
                bFound = sal_True;
                uno::Reference<container::XIndexAccess> xIndexAccess;
                if (aSeqViewProps[i].Value >>= xIndexAccess)
                {
                    uno::Reference<document::XViewDataSupplier> xViewDataSupplier(GetImport().GetModel(), uno::UNO_QUERY);
                    if (xViewDataSupplier.is())
                        xViewDataSupplier->setViewData(xIndexAccess);
                }
            }
            else
                i--;
        }
    }
    uno::Sequence<beans::PropertyValue> aSeqConfigProps;
    if (aConfigProps >>= aSeqConfigProps)
        GetImport().SetConfigurationSettings(aSeqConfigProps);
}

//=============================================================================

XMLConfigBaseContext::XMLConfigBaseContext(SvXMLImport& rImport, USHORT nPrfx,
        const ::rtl::OUString& rLName, ::com::sun::star::uno::Any& rTempAny,
        XMLConfigBaseContext* pTempBaseContext)
    : SvXMLImportContext( rImport, nPrfx, rLName ),
    rAny(rTempAny),
    // #110680#
    //aProps(),
    aProps(rImport.getServiceFactory()),
    aProp(),
    pBaseContext(pTempBaseContext)
{
}

XMLConfigBaseContext::~XMLConfigBaseContext()
{
}

//=============================================================================

XMLConfigItemSetContext::XMLConfigItemSetContext(SvXMLImport& rImport, USHORT nPrfx,
                                    const ::rtl::OUString& rLName,
                                    const ::com::sun::star::uno::Reference<
                                    ::com::sun::star::xml::sax::XAttributeList>& xAttrList,
                                    ::com::sun::star::uno::Any& rAny,
                                    XMLConfigBaseContext* pBaseContext)
    : XMLConfigBaseContext( rImport, nPrfx, rLName, rAny, pBaseContext )
{
    // here are no attributes
}

XMLConfigItemSetContext::~XMLConfigItemSetContext()
{
}

SvXMLImportContext *XMLConfigItemSetContext::CreateChildContext( USHORT nPrefix,
                                     const ::rtl::OUString& rLocalName,
                                     const ::com::sun::star::uno::Reference<
                                          ::com::sun::star::xml::sax::XAttributeList>& xAttrList )
{
    return CreateSettingsContext(GetImport(), nPrefix, rLocalName, xAttrList, aProp, this);
}

void XMLConfigItemSetContext::EndElement()
{
    rAny <<= aProps.GetSequence();
    if (pBaseContext)
        pBaseContext->AddPropertyValue();
}

//=============================================================================

XMLConfigItemContext::XMLConfigItemContext(SvXMLImport& rImport, USHORT nPrfx, const ::rtl::OUString& rLName,
                                    const ::com::sun::star::uno::Reference<
                                    ::com::sun::star::xml::sax::XAttributeList>& xAttrList,
                                    ::com::sun::star::uno::Any& rTempAny,
                                    const ::rtl::OUString& rTempItemName,
                                    XMLConfigBaseContext* pTempBaseContext)
    : SvXMLImportContext(rImport, nPrfx, rLName),
    rAny(rTempAny),
    pBaseContext(pTempBaseContext),
    sType(),
    sValue(),
    rItemName(rTempItemName)
{
    sal_Int16 nAttrCount = xAttrList.is() ? xAttrList->getLength() : 0;
    for( sal_Int16 i=0; i < nAttrCount; i++ )
    {
        ::rtl::OUString sAttrName = xAttrList->getNameByIndex( i );
        ::rtl::OUString aLocalName;
        USHORT nPrefix = GetImport().GetNamespaceMap().GetKeyByAttrName(
                                            sAttrName, &aLocalName );
        ::rtl::OUString sValue = xAttrList->getValueByIndex( i );

        if (nPrefix == XML_NAMESPACE_CONFIG)
        {
            if (IsXMLToken(aLocalName, XML_TYPE))
                sType = sValue;
        }
    }
}

XMLConfigItemContext::~XMLConfigItemContext()
{
}

SvXMLImportContext *XMLConfigItemContext::CreateChildContext( USHORT nPrefix,
                                                    const ::rtl::OUString& rLocalName,
                                                    const ::com::sun::star::uno::Reference<
                                          ::com::sun::star::xml::sax::XAttributeList>& xAttrList )
{
    SvXMLImportContext* pContext = new SvXMLImportContext(GetImport(), nPrefix, rLocalName);
    return pContext;
}

void XMLConfigItemContext::Characters( const ::rtl::OUString& rChars )
{
    if (IsXMLToken(sType, XML_BASE64BINARY))
    {
        ::rtl::OUString sTrimmedChars( rChars.trim() );
        if( sTrimmedChars.getLength() )
        {
            ::rtl::OUString sChars;
            if( sValue )
            {
                sChars = sValue;
                sChars += sTrimmedChars;
                sValue = ::rtl::OUString();
            }
            else
            {
                sChars = sTrimmedChars;
            }
            uno::Sequence<sal_Int8> aBuffer((sChars.getLength() / 4) * 3 );
            sal_Int32 nCharsDecoded =
                GetImport().GetMM100UnitConverter().
                    decodeBase64SomeChars( aBuffer, sChars );
            sal_uInt32 nStartPos(aDecoded.getLength());
            sal_uInt32 nCount(aBuffer.getLength());
            aDecoded.realloc(nStartPos + nCount);
            sal_Int8* pDecoded = aDecoded.getArray();
            sal_Int8* pBuffer = aBuffer.getArray();
            for (sal_uInt32 i = 0; i < nCount; i++, pBuffer++)
                pDecoded[nStartPos + i] = *pBuffer;
            if( nCharsDecoded != sChars.getLength() )
                sValue = sChars.copy( nCharsDecoded );
        }
    }
    else
        sValue += rChars;
}


void XMLConfigItemContext::EndElement()
{
    if (pBaseContext)
    {
        if (IsXMLToken(sType, XML_BOOLEAN))
        {
            sal_Bool bValue(sal_False);
            if (IsXMLToken(sValue, XML_TRUE))
                bValue = sal_True;
            rAny <<= bValue;
        }
        else if (IsXMLToken(sType, XML_BYTE))
        {
            sal_Int32 nValue(0);
            SvXMLUnitConverter::convertNumber(nValue, sValue);
            rAny <<= static_cast<sal_Int8>(nValue);
        }
        else if (IsXMLToken(sType, XML_SHORT))
        {
            sal_Int32 nValue(0);
            SvXMLUnitConverter::convertNumber(nValue, sValue);
            rAny <<= static_cast<sal_Int16>(nValue);
        }
        else if (IsXMLToken(sType, XML_INT))
        {
            sal_Int32 nValue(0);
            SvXMLUnitConverter::convertNumber(nValue, sValue);
            rAny <<= nValue;
        }
        else if (IsXMLToken(sType, XML_LONG))
        {
            sal_Int64 nValue(sValue.toInt64());
            rAny <<= nValue;
        }
        else if (IsXMLToken(sType, XML_DOUBLE))
        {
            double fValue(0.0);
            SvXMLUnitConverter::convertDouble(fValue, sValue);
            rAny <<= fValue;
        }
        else if (IsXMLToken(sType, XML_STRING))
        {
            rAny <<= sValue;
        }
        else if (IsXMLToken(sType, XML_DATETIME))
        {
            util::DateTime aDateTime;
            SvXMLUnitConverter::convertDateTime(aDateTime, sValue);
            rAny <<= aDateTime;
        }
        else if (IsXMLToken(sType, XML_BASE64BINARY))
        {
            rAny <<= aDecoded;
        }
        else
            DBG_ERROR("wrong type");

        ManipulateConfigItem();

        pBaseContext->AddPropertyValue();
    }
    else
        DBG_ERROR("no BaseContext");
}

/** There are some instances where there is a mismatch between API and
 * XML mapping of a setting. In this case, this method allows us to
 * manipulate the values accordingly. */
void XMLConfigItemContext::ManipulateConfigItem()
{
    if( rItemName.equalsAsciiL( 
            RTL_CONSTASCII_STRINGPARAM( "PrinterIndependentLayout" ) ) )
    {
        ::rtl::OUString sValue;
        rAny >>= sValue;

        sal_Int16 nTmp = document::PrinterIndependentLayout::HIGH_RESOLUTION;

        if( sValue.equalsAsciiL(RTL_CONSTASCII_STRINGPARAM("enabled")) ||
            sValue.equalsAsciiL(RTL_CONSTASCII_STRINGPARAM("low-resolution")) )
        {
            nTmp = document::PrinterIndependentLayout::LOW_RESOLUTION;
        }
        else if( sValue.equalsAsciiL(RTL_CONSTASCII_STRINGPARAM("disabled")) )
        {
            nTmp = document::PrinterIndependentLayout::DISABLED;
        }
        // else: default to high_resolution

        rAny <<= nTmp;
    }
}


//=============================================================================

XMLConfigItemMapNamedContext::XMLConfigItemMapNamedContext(SvXMLImport& rImport, USHORT nPrfx, const ::rtl::OUString& rLName,
                                    const ::com::sun::star::uno::Reference<
                                    ::com::sun::star::xml::sax::XAttributeList>& xAttrList,
                                    ::com::sun::star::uno::Any& rAny,
                                    XMLConfigBaseContext* pBaseContext)
    : XMLConfigBaseContext(rImport, nPrfx, rLName, rAny, pBaseContext)
{
}

XMLConfigItemMapNamedContext::~XMLConfigItemMapNamedContext()
{
}

SvXMLImportContext *XMLConfigItemMapNamedContext::CreateChildContext( USHORT nPrefix,
                                                    const ::rtl::OUString& rLocalName,
                                                    const ::com::sun::star::uno::Reference<
                                          ::com::sun::star::xml::sax::XAttributeList>& xAttrList )
{
    return CreateSettingsContext(GetImport(), nPrefix, rLocalName, xAttrList, aProp, this);
}

void XMLConfigItemMapNamedContext::EndElement()
{
    if (pBaseContext)
    {
        rAny <<= aProps.GetNameContainer();
        pBaseContext->AddPropertyValue();
    }
    else
        DBG_ERROR("no BaseContext");
}

//=============================================================================

XMLConfigItemMapIndexedContext::XMLConfigItemMapIndexedContext(SvXMLImport& rImport, USHORT nPrfx,
                                    const ::rtl::OUString& rLName,
                                    const ::com::sun::star::uno::Reference<
                                    ::com::sun::star::xml::sax::XAttributeList>& xAttrList,
                                    ::com::sun::star::uno::Any& rAny,
                                    const ::rtl::OUString& rConfigItemName,
                                    XMLConfigBaseContext* pBaseContext)
    : XMLConfigBaseContext(rImport, nPrfx, rLName, rAny, pBaseContext),
      maConfigItemName( rConfigItemName )
{
}

XMLConfigItemMapIndexedContext::~XMLConfigItemMapIndexedContext()
{
}

SvXMLImportContext *XMLConfigItemMapIndexedContext::CreateChildContext( USHORT nPrefix,
                                                    const ::rtl::OUString& rLocalName,
                                                    const ::com::sun::star::uno::Reference<
                                        ::com::sun::star::xml::sax::XAttributeList>& xAttrList )
{
    return CreateSettingsContext(GetImport(), nPrefix, rLocalName, xAttrList, aProp, this);
}

void XMLConfigItemMapIndexedContext::EndElement()
{
    if (pBaseContext)
    {
        if( maConfigItemName.equalsAsciiL( RTL_CONSTASCII_STRINGPARAM( "ForbiddenCharacters" ) ) )
        {
            uno::Reference< i18n::XForbiddenCharacters > xForbChars;

            // get the forbidden characters from the document
            uno::Reference< lang::XMultiServiceFactory > xFac( GetImport().GetModel(), uno::UNO_QUERY );
            if( xFac.is() )
            {
                uno::Reference< beans::XPropertySet > xProps( xFac->createInstance( ::rtl::OUString( RTL_CONSTASCII_USTRINGPARAM( "com.sun.star.document.Settings" ) ) ), uno::UNO_QUERY );
                if( xProps.is() && xProps->getPropertySetInfo()->hasPropertyByName( maConfigItemName ) )
                {
                    xProps->getPropertyValue( maConfigItemName ) >>= xForbChars;
                }
            }

            if( xForbChars.is() )
            {

                uno::Reference< container::XIndexAccess > xIndex( aProps.GetIndexContainer(), uno::UNO_QUERY );

                const sal_Int32 nCount = xIndex->getCount();
                uno::Sequence < beans::PropertyValue > aProps;
                for (sal_Int32 i = 0; i < nCount; i++)
                {
                    if ((xIndex->getByIndex( i ) >>= aProps) && (aProps.getLength() == XML_FORBIDDEN_CHARACTER_MAX ) )
                    {
                        beans::PropertyValue *pForChar = aProps.getArray();
                        i18n::ForbiddenCharacters aForbid;
                        lang::Locale aLocale;
                        const ::rtl::OUString sLanguage  ( RTL_CONSTASCII_USTRINGPARAM ( "Language" ) );
                        const ::rtl::OUString sCountry   ( RTL_CONSTASCII_USTRINGPARAM ( "Country" ) );
                        const ::rtl::OUString sVariant   ( RTL_CONSTASCII_USTRINGPARAM ( "Variant" ) );
                        const ::rtl::OUString sBeginLine ( RTL_CONSTASCII_USTRINGPARAM ( "BeginLine" ) );
                        const ::rtl::OUString sEndLine   ( RTL_CONSTASCII_USTRINGPARAM ( "EndLine" ) );
                        sal_Bool bHaveLanguage = sal_False, bHaveCountry = sal_False, bHaveVariant = sal_False,
                                 bHaveBegin = sal_False, bHaveEnd = sal_False;

                        for ( sal_Int32 j = 0 ; j < XML_FORBIDDEN_CHARACTER_MAX ; j++ )
                        {
                            if (pForChar->Name.equals (sLanguage ) )
                            {
                                pForChar->Value >>= aLocale.Language;
                                bHaveLanguage = sal_True;
                            }
                            else if (pForChar->Name.equals (sCountry ) )
                            {
                                pForChar->Value >>= aLocale.Country;
                                bHaveCountry = sal_True;
                            }
                            else if (pForChar->Name.equals (sVariant ) )
                            {
                                pForChar->Value >>= aLocale.Variant;
                                bHaveVariant = sal_True;
                            }
                            else if (pForChar->Name.equals (sBeginLine ) )
                            {
                                pForChar->Value >>= aForbid.beginLine;
                                bHaveBegin = sal_True;
                            }
                            else if (pForChar->Name.equals (sEndLine ) )
                            {
                                pForChar->Value >>= aForbid.endLine;
                                bHaveEnd = sal_True;
                            }
                            pForChar++;
                        }

                        if ( bHaveLanguage && bHaveCountry && bHaveVariant && bHaveBegin && bHaveEnd )
                        {
                            try
                            {
                                xForbChars->setForbiddenCharacters( aLocale, aForbid );
                            }
                            catch( uno::Exception& )
                            {
//								DBG_ERROR( "Exception while importing forbidden characters" );
                            }
                        }
                    }
                }
            }
            else
            {
                DBG_ERROR( "could not get the XForbiddenCharacters from document!" );
                rAny <<= aProps.GetIndexContainer();
            }
        }
        else if( maConfigItemName.equalsAsciiL( RTL_CONSTASCII_STRINGPARAM( "Symbols" ) ) )
        {
            uno::Reference< container::XIndexAccess > xIndex( aProps.GetIndexContainer(), uno::UNO_QUERY );

            const sal_Int32 nCount = xIndex->getCount();
            uno::Sequence < beans::PropertyValue > aProps;
            uno::Sequence < formula::SymbolDescriptor > aSymbolList ( nCount );

            formula::SymbolDescriptor *pDescriptor = aSymbolList.getArray();

            const ::rtl::OUString sName     ( RTL_CONSTASCII_USTRINGPARAM ( "Name" ) );
            const ::rtl::OUString sExportName ( RTL_CONSTASCII_USTRINGPARAM ( "ExportName" ) );
            const ::rtl::OUString sFontName ( RTL_CONSTASCII_USTRINGPARAM ( "FontName" ) );
            const ::rtl::OUString sSymbolSet ( RTL_CONSTASCII_USTRINGPARAM ( "SymbolSet" ) );
            const ::rtl::OUString sCharacter ( RTL_CONSTASCII_USTRINGPARAM ( "Character" ) );
            const ::rtl::OUString sCharSet  ( RTL_CONSTASCII_USTRINGPARAM ( "CharSet" ) );
            const ::rtl::OUString sFamily   ( RTL_CONSTASCII_USTRINGPARAM ( "Family" ) );
            const ::rtl::OUString sPitch    ( RTL_CONSTASCII_USTRINGPARAM ( "Pitch" ) );
            const ::rtl::OUString sWeight   ( RTL_CONSTASCII_USTRINGPARAM ( "Weight" ) );
            const ::rtl::OUString sItalic   ( RTL_CONSTASCII_USTRINGPARAM ( "Italic" ) );
            sal_Int16 nNumFullEntries = 0;

            for ( sal_Int32 i = 0; i < nCount; i++ )
            {
                if ((xIndex->getByIndex( i ) >>= aProps) && (aProps.getLength() == XML_SYMBOL_DESCRIPTOR_MAX ) )
                {
                    sal_Bool bHaveName = sal_False, bHaveExportName = sal_False, bHaveCharSet = sal_False,
                              bHaveFontName = sal_False, bHaveFamily = sal_False, bHavePitch = sal_False,
                              bHaveWeight = sal_False, bHaveItalic = sal_False, bHaveSymbolSet = sal_False,
                             bHaveCharacter = sal_False;
                    beans::PropertyValue *pSymbol = aProps.getArray();

                    for ( sal_Int32 j = 0 ; j < XML_SYMBOL_DESCRIPTOR_MAX ; j++ )
                    {
                        if (pSymbol->Name.equals ( sName ) )
                        {
                            pSymbol->Value >>= pDescriptor[nNumFullEntries].sName;
                            bHaveName = sal_True;
                        }
                        else if (pSymbol->Name.equals (sExportName ) )
                        {
                            pSymbol->Value >>= pDescriptor[nNumFullEntries].sExportName;
                            bHaveExportName = sal_True;
                        }
                        else if (pSymbol->Name.equals (sFontName ) )
                        {
                            pSymbol->Value >>= pDescriptor[nNumFullEntries].sFontName;
                            bHaveFontName = sal_True;
                        }
                        else if (pSymbol->Name.equals (sCharSet ) )
                        {
                            pSymbol->Value >>= pDescriptor[nNumFullEntries].nCharSet;
                            bHaveCharSet = sal_True;
                        }
                        else if (pSymbol->Name.equals (sFamily ) )
                        {
                            pSymbol->Value >>= pDescriptor[nNumFullEntries].nFamily;
                            bHaveFamily = sal_True;
                        }
                        else if (pSymbol->Name.equals (sPitch ) )
                        {
                            pSymbol->Value >>= pDescriptor[nNumFullEntries].nPitch;
                            bHavePitch = sal_True;
                        }
                        else if (pSymbol->Name.equals (sWeight ) )
                        {
                            pSymbol->Value >>= pDescriptor[nNumFullEntries].nWeight;
                            bHaveWeight = sal_True;
                        }
                        else if (pSymbol->Name.equals (sItalic ) )
                        {
                            pSymbol->Value >>= pDescriptor[nNumFullEntries].nItalic;
                            bHaveItalic = sal_True;
                        }
                        else if (pSymbol->Name.equals (sSymbolSet ) )
                        {
                            pSymbol->Value >>= pDescriptor[nNumFullEntries].sSymbolSet;
                            bHaveSymbolSet = sal_True;
                        }
                        else if (pSymbol->Name.equals (sCharacter ) )
                        {
                            pSymbol->Value >>= pDescriptor[nNumFullEntries].nCharacter;
                            bHaveCharacter = sal_True;
                        }
                        pSymbol++;
                    }
                    if ( bHaveName && bHaveExportName && bHaveCharSet && bHaveFontName && bHaveCharacter
                         && bHaveFamily && bHavePitch && bHaveWeight && bHaveItalic && bHaveSymbolSet)
                        nNumFullEntries++;
                }
            }
            aSymbolList.realloc (nNumFullEntries);
            rAny <<= aSymbolList;
        }
        else
        {
            rAny <<= aProps.GetIndexContainer();
        }
        pBaseContext->AddPropertyValue();
    }
    else
        DBG_ERROR("no BaseContext");
}

}//end of namespace binfilter
