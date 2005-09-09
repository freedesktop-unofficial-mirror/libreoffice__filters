/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: xmloff_numehelp.cxx,v $
 *
 *  $Revision: 1.3 $
 *
 *  last change: $Author: rt $ $Date: 2005-09-09 09:51:48 $
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

#include "numehelp.hxx"

#include "nmspmap.hxx"
// auto strip #include "xmlnmspe.hxx"
#include "xmluconv.hxx"

// auto strip #ifndef _XMLOFF_XMLTOKEN_HXX
// auto strip #include "xmltoken.hxx"
// auto strip #endif
#ifndef _XMLOFF_XMLEXP_HXX
#include "xmlexp.hxx"
#endif
#ifndef _COM_SUN_STAR_UNO_REFERENCE_H_
#include <com/sun/star/uno/Reference.h>
#endif
// auto strip #ifndef _RTL_USTRING_HXX_
// auto strip #include <rtl/ustring.hxx>
// auto strip #endif
// auto strip #ifndef _TOOLS_INTN_HXX
// auto strip #include <tools/intn.hxx>
// auto strip #endif
#ifndef _ZFORLIST_HXX
#include <svtools/zforlist.hxx>
#endif
#ifndef _COM_SUN_STAR_UTIL_NUMBERFORMAT_HPP_
#include <com/sun/star/util/NumberFormat.hpp>
#endif
#ifndef INCLUDED_RTL_MATH_HXX
#include <rtl/math.hxx>
#endif
#ifndef _TOOLS_DEBUG_HXX
#include <tools/debug.hxx>
#endif
// auto strip #ifndef _RTL_USTRBUF_HXX_
// auto strip #include <rtl/ustrbuf.hxx>
// auto strip #endif
namespace binfilter {

using namespace ::com::sun::star;
using namespace xmloff::token;

#define XML_TYPE "Type"
#define XML_CURRENCYSYMBOL "CurrencySymbol"
#define XML_CURRENCYABBREVIATION "CurrencyAbbreviation"
#define XML_STANDARDFORMAT "StandardFormat"

XMLNumberFormatAttributesExportHelper::XMLNumberFormatAttributesExportHelper(
            ::com::sun::star::uno::Reference< ::com::sun::star::util::XNumberFormatsSupplier >& xTempNumberFormatsSupplier)
    : pExport(NULL),
    xNumberFormats(xTempNumberFormatsSupplier.is() ? xTempNumberFormatsSupplier->getNumberFormats() : ::com::sun::star::uno::Reference< ::com::sun::star::util::XNumberFormats > ()),
    aNumberFormats(),
    sStandardFormat(RTL_CONSTASCII_USTRINGPARAM(XML_STANDARDFORMAT)),
    sType(RTL_CONSTASCII_USTRINGPARAM(XML_TYPE))
{
}

XMLNumberFormatAttributesExportHelper::XMLNumberFormatAttributesExportHelper(
            ::com::sun::star::uno::Reference< ::com::sun::star::util::XNumberFormatsSupplier >& xTempNumberFormatsSupplier,
            SvXMLExport& rTempExport, sal_uInt16 nTempNamespace)
      : pExport(&rTempExport),
    xNumberFormats(xTempNumberFormatsSupplier.is() ? xTempNumberFormatsSupplier->getNumberFormats() : ::com::sun::star::uno::Reference< ::com::sun::star::util::XNumberFormats > ()),
    aNumberFormats(),
    nNamespace(nTempNamespace),
    sAttrValueType(rTempExport.GetNamespaceMap().GetQNameByKey( nTempNamespace, GetXMLToken(XML_VALUE_TYPE))),
    sAttrValue(rTempExport.GetNamespaceMap().GetQNameByKey( nTempNamespace, GetXMLToken(XML_VALUE))),
    sAttrDateValue(rTempExport.GetNamespaceMap().GetQNameByKey( nTempNamespace, GetXMLToken(XML_DATE_VALUE))),
    sAttrTimeValue(rTempExport.GetNamespaceMap().GetQNameByKey( nTempNamespace, GetXMLToken(XML_TIME_VALUE))),
    sAttrBooleanValue(rTempExport.GetNamespaceMap().GetQNameByKey( nTempNamespace, GetXMLToken(XML_BOOLEAN_VALUE))),
    sAttrStringValue(rTempExport.GetNamespaceMap().GetQNameByKey( nTempNamespace, GetXMLToken(XML_STRING_VALUE))),
    sAttrCurrency(rTempExport.GetNamespaceMap().GetQNameByKey( nTempNamespace, GetXMLToken(XML_CURRENCY))),
    sStandardFormat(RTL_CONSTASCII_USTRINGPARAM(XML_STANDARDFORMAT)),
    sType(RTL_CONSTASCII_USTRINGPARAM(XML_TYPE))
{
}

XMLNumberFormatAttributesExportHelper::~XMLNumberFormatAttributesExportHelper()
{
}

sal_Int16 XMLNumberFormatAttributesExportHelper::GetCellType(const sal_Int32 nNumberFormat, ::rtl::OUString& sCurrency, sal_Bool& bIsStandard)
{
    XMLNumberFormat aFormat(sEmpty, nNumberFormat, 0);
    XMLNumberFormatSet::iterator aItr = aNumberFormats.find(aFormat);
    if (aItr != aNumberFormats.end())
    {
        bIsStandard = aItr->bIsStandard;
        sCurrency = aItr->sCurrency;
        return aItr->nType;
    }
    else
    {
        aFormat.nType = GetCellType(nNumberFormat, bIsStandard);
        aFormat.bIsStandard = bIsStandard;
        if ((aFormat.nType & ~util::NumberFormat::DEFINED) == util::NumberFormat::CURRENCY)
            if (GetCurrencySymbol(nNumberFormat, aFormat.sCurrency))
                sCurrency = aFormat.sCurrency;
        aNumberFormats.insert(aFormat);
        return aFormat.nType;
    }
    return 0;
}

void XMLNumberFormatAttributesExportHelper::SetNumberFormatAttributes(
    const sal_Int32 nNumberFormat, const double& rValue, sal_uInt16 nNamespace, sal_Bool bExportValue)
{
    if (pExport)
    {
        sal_Bool bIsStandard;
        ::rtl::OUString sCurrency;
        sal_Int16 nTypeKey = GetCellType(nNumberFormat, sCurrency, bIsStandard);
        WriteAttributes(*pExport, nTypeKey, rValue, sCurrency, nNamespace, bExportValue);
    }
    else
        DBG_ERROR("no SvXMLExport given");
}

void XMLNumberFormatAttributesExportHelper::SetNumberFormatAttributes(
    const ::rtl::OUString& rValue, const ::rtl::OUString& rCharacters, sal_uInt16 nNamespace,
    sal_Bool bExportValue, sal_Bool bExportTypeAttribute)
{
    if (pExport)
        SetNumberFormatAttributes(*pExport, rValue, rCharacters, nNamespace, bExportValue, bExportTypeAttribute);
    else
        DBG_ERROR("no SvXMLExport given");
}

void XMLNumberFormatAttributesExportHelper::WriteAttributes(SvXMLExport& rXMLExport,
                                const sal_Int16 nTypeKey,
                                const double& rValue,
                                const ::rtl::OUString& rCurrency,
                                sal_uInt16 nNamespace,
                                sal_Bool bExportValue)
{
    sal_Bool bWasSetTypeAttribute = sal_False;
    switch(nTypeKey & ~util::NumberFormat::DEFINED)
    {
    case 0:
    case util::NumberFormat::NUMBER:
    case util::NumberFormat::SCIENTIFIC:
    case util::NumberFormat::FRACTION:
        {
            if (!bWasSetTypeAttribute)
            {
                rXMLExport.AddAttribute(nNamespace, XML_VALUE_TYPE, XML_FLOAT);
                bWasSetTypeAttribute = sal_True;
            }
        }		// No Break
    case util::NumberFormat::PERCENT:
        {
            if (!bWasSetTypeAttribute)
            {
                rXMLExport.AddAttribute(nNamespace, XML_VALUE_TYPE, XML_PERCENTAGE);
                bWasSetTypeAttribute = sal_True;
            }
        }		// No Break
    case util::NumberFormat::CURRENCY:
        {
            if (!bWasSetTypeAttribute)
            {
                rXMLExport.AddAttribute(nNamespace, XML_VALUE_TYPE, XML_CURRENCY);
                if (rCurrency.getLength() > 0)
                    rXMLExport.AddAttribute(nNamespace, XML_CURRENCY, rCurrency);
                bWasSetTypeAttribute = sal_True;
            }

            if (bExportValue)
            {
                ::rtl::OUString sValue( ::rtl::math::doubleToUString( rValue,
                            rtl_math_StringFormat_Automatic,
                            rtl_math_DecimalPlaces_Max, '.', sal_True));
                rXMLExport.AddAttribute(nNamespace, XML_VALUE, sValue);
            }
        }
        break;
    case util::NumberFormat::DATE:
    case util::NumberFormat::DATETIME:
        {
            if (!bWasSetTypeAttribute)
            {
                rXMLExport.AddAttribute(nNamespace, XML_VALUE_TYPE, XML_DATE);
                bWasSetTypeAttribute = sal_True;
            }
            if (bExportValue)
            {
                if ( rXMLExport.GetMM100UnitConverter().setNullDate(rXMLExport.GetModel()) )
                {
                    ::rtl::OUStringBuffer sBuffer;
                    rXMLExport.GetMM100UnitConverter().convertDateTime(sBuffer, rValue);
                    rXMLExport.AddAttribute(nNamespace, XML_DATE_VALUE, sBuffer.makeStringAndClear());
                }
            }
        }
        break;
    case util::NumberFormat::TIME:
        {
            if (!bWasSetTypeAttribute)
            {
                rXMLExport.AddAttribute(nNamespace, XML_VALUE_TYPE, XML_TIME);
                bWasSetTypeAttribute = sal_True;
            }
            if (bExportValue)
            {
                ::rtl::OUStringBuffer sBuffer;
                rXMLExport.GetMM100UnitConverter().convertTime(sBuffer, rValue);
                rXMLExport.AddAttribute(nNamespace, XML_TIME_VALUE, sBuffer.makeStringAndClear());
            }
        }
        break;
    case util::NumberFormat::LOGICAL:
        {
            if (!bWasSetTypeAttribute)
            {
                rXMLExport.AddAttribute(nNamespace, XML_VALUE_TYPE, XML_BOOLEAN);
                bWasSetTypeAttribute = sal_True;
            }
            if (bExportValue)
            {
                double fTempValue = rValue;
                if (::rtl::math::approxEqual( fTempValue, 1.0 ))
                {
                    rXMLExport.AddAttribute(nNamespace, XML_BOOLEAN_VALUE, XML_TRUE);
                }
                else
                {
                    if (::rtl::math::approxEqual( rValue, 0.0 ))
                    {
                        rXMLExport.AddAttribute(nNamespace, XML_BOOLEAN_VALUE, XML_FALSE);
                    }
                    else
                    {
                        ::rtl::OUString sValue( ::rtl::math::doubleToUString(
                                    fTempValue,
                                    rtl_math_StringFormat_Automatic,
                                    rtl_math_DecimalPlaces_Max, '.',
                                    sal_True));
                        rXMLExport.AddAttribute(nNamespace, XML_BOOLEAN_VALUE, sValue);
                    }
                }
            }
        }
        break;
    case util::NumberFormat::TEXT:
        {
            if (!bWasSetTypeAttribute)
            {
                rXMLExport.AddAttribute(nNamespace, XML_VALUE_TYPE, XML_FLOAT);
                bWasSetTypeAttribute = sal_True;
                if (bExportValue)
                {
                    ::rtl::OUString sValue( ::rtl::math::doubleToUString( rValue,
                                rtl_math_StringFormat_Automatic,
                                rtl_math_DecimalPlaces_Max, '.', sal_True));
                    rXMLExport.AddAttribute(nNamespace, XML_VALUE, sValue);
                }
            }
        }
        break;
    }
}

sal_Bool XMLNumberFormatAttributesExportHelper::GetCurrencySymbol(const sal_Int32 nNumberFormat, ::rtl::OUString& sCurrencySymbol,
    uno::Reference <util::XNumberFormatsSupplier>& xNumberFormatsSupplier)
{
    if (xNumberFormatsSupplier.is())
    {
        uno::Reference <util::XNumberFormats> xNumberFormats = xNumberFormatsSupplier->getNumberFormats();
        if (xNumberFormats.is())
        {
            try
            {
                uno::Reference <beans::XPropertySet> xNumberPropertySet = xNumberFormats->getByKey(nNumberFormat);
                uno::Any aCurrencySymbol = xNumberPropertySet->getPropertyValue( ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM(XML_CURRENCYSYMBOL)));
                if ( aCurrencySymbol >>= sCurrencySymbol)
                {
                    ::rtl::OUString sCurrencyAbbreviation;
                    uno::Any aCurrencyAbbreviation = xNumberPropertySet->getPropertyValue( ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM(XML_CURRENCYABBREVIATION)));
                    if ( aCurrencyAbbreviation >>= sCurrencyAbbreviation)
                    {
                        if ( sCurrencyAbbreviation.getLength() != 0 )
                            sCurrencySymbol = sCurrencyAbbreviation;
                        else
                        {
                            if ( sCurrencySymbol.getLength() == 1 && sCurrencySymbol.toChar() == NfCurrencyEntry::GetEuroSymbol() )
                                sCurrencySymbol = ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("EUR"));
                        }
                    }
                    return sal_True;
                }
            }
            catch ( uno::Exception& )
            {
                DBG_ERROR("Numberformat not found");
            }
        }
    }
    return sal_False;
}


sal_Int16 XMLNumberFormatAttributesExportHelper::GetCellType(const sal_Int32 nNumberFormat, sal_Bool& bIsStandard,
    uno::Reference <util::XNumberFormatsSupplier>& xNumberFormatsSupplier)
{
    if (xNumberFormatsSupplier.is())
    {
        uno::Reference <util::XNumberFormats> xNumberFormats = xNumberFormatsSupplier->getNumberFormats();
        if (xNumberFormats.is())
        {
            try
            {
                uno::Reference <beans::XPropertySet> xNumberPropertySet = xNumberFormats->getByKey(nNumberFormat);
                uno::Any aIsStandardFormat = xNumberPropertySet->getPropertyValue( ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM(XML_STANDARDFORMAT)));
                aIsStandardFormat >>= bIsStandard;
                uno::Any aNumberType = xNumberPropertySet->getPropertyValue( ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM(XML_TYPE)));
                sal_Int16 nNumberType;
                if ( aNumberType >>= nNumberType )
                {
                    return nNumberType;
                }
            }
            catch ( uno::Exception& )
            {
                DBG_ERROR("Numberformat not found");
            }
        }
    }
    return 0;
}

void XMLNumberFormatAttributesExportHelper::SetNumberFormatAttributes(SvXMLExport& rXMLExport,
    const sal_Int32 nNumberFormat, const double& rValue, sal_uInt16 nNamespace, sal_Bool bExportValue)
{
    sal_Bool bIsStandard;
    sal_Int16 nTypeKey = GetCellType(nNumberFormat, bIsStandard, rXMLExport.GetNumberFormatsSupplier());
    ::rtl::OUString sCurrency;
    if ((nTypeKey & ~util::NumberFormat::DEFINED) == util::NumberFormat::CURRENCY)
        GetCurrencySymbol(nNumberFormat, sCurrency, rXMLExport.GetNumberFormatsSupplier());
    WriteAttributes(rXMLExport, nTypeKey, rValue, sCurrency, nNamespace, bExportValue);
}

void XMLNumberFormatAttributesExportHelper::SetNumberFormatAttributes(SvXMLExport& rXMLExport,
    const ::rtl::OUString& rValue, const ::rtl::OUString& rCharacters, sal_uInt16 nNamespace,
    sal_Bool bExportValue, sal_Bool bExportTypeAttribute)
{
    if (bExportTypeAttribute)
        rXMLExport.AddAttribute(nNamespace, XML_VALUE_TYPE, XML_STRING);
    if (bExportValue && rValue.getLength() && (rValue != rCharacters))
        rXMLExport.AddAttribute(nNamespace, XML_STRING_VALUE, rValue);
}

sal_Bool XMLNumberFormatAttributesExportHelper::GetCurrencySymbol(const sal_Int32 nNumberFormat, ::rtl::OUString& sCurrencySymbol)
{
    if (!xNumberFormats.is() && pExport && pExport->GetNumberFormatsSupplier().is())
        xNumberFormats = pExport->GetNumberFormatsSupplier()->getNumberFormats();

    if (xNumberFormats.is())
    {
        try
        {
            uno::Reference <beans::XPropertySet> xNumberPropertySet = xNumberFormats->getByKey(nNumberFormat);
            uno::Any aCurrencySymbol = xNumberPropertySet->getPropertyValue( ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM(XML_CURRENCYSYMBOL)));
            if ( aCurrencySymbol >>= sCurrencySymbol)
            {
                ::rtl::OUString sCurrencyAbbreviation;
                uno::Any aCurrencyAbbreviation = xNumberPropertySet->getPropertyValue( ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM(XML_CURRENCYABBREVIATION)));
                if ( aCurrencyAbbreviation >>= sCurrencyAbbreviation)
                {
                    if ( sCurrencyAbbreviation.getLength() != 0 )
                        sCurrencySymbol = sCurrencyAbbreviation;
                    else
                    {
                        if ( sCurrencySymbol.getLength() == 1 && sCurrencySymbol.toChar() == NfCurrencyEntry::GetEuroSymbol() )
                            sCurrencySymbol = ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("EUR"));
                    }
                }
                return sal_True;
            }
        }
        catch ( uno::Exception& )
        {
            DBG_ERROR("Numberformat not found");
        }
    }
    return sal_False;
}

sal_Int16 XMLNumberFormatAttributesExportHelper::GetCellType(const sal_Int32 nNumberFormat, sal_Bool& bIsStandard)
{
    if (!xNumberFormats.is() && pExport && pExport->GetNumberFormatsSupplier().is())
        xNumberFormats = pExport->GetNumberFormatsSupplier()->getNumberFormats();

    if (xNumberFormats.is())
    {
        try
        {
            uno::Reference <beans::XPropertySet> xNumberPropertySet = xNumberFormats->getByKey(nNumberFormat);
            uno::Any aIsStandardFormat = xNumberPropertySet->getPropertyValue(sStandardFormat);
            aIsStandardFormat >>= bIsStandard;
            uno::Any aNumberType = xNumberPropertySet->getPropertyValue(sType);
            sal_Int16 nNumberType;
            if ( aNumberType >>= nNumberType )
            {
                return nNumberType;
            }
        }
        catch ( uno::Exception& )
        {
            DBG_ERROR("Numberformat not found");
        }
    }
    return 0;
}

void XMLNumberFormatAttributesExportHelper::WriteAttributes(
                                const sal_Int16 nTypeKey,
                                const double& rValue,
                                const ::rtl::OUString& rCurrency,
                                sal_Bool bExportValue)
{
    if (!pExport)
        return;

    sal_Bool bWasSetTypeAttribute = sal_False;
    switch(nTypeKey & ~util::NumberFormat::DEFINED)
    {
    case 0:
    case util::NumberFormat::NUMBER:
    case util::NumberFormat::SCIENTIFIC:
    case util::NumberFormat::FRACTION:
        {
            if (!bWasSetTypeAttribute)
            {
                pExport->AddAttribute(sAttrValueType, XML_FLOAT);
                bWasSetTypeAttribute = sal_True;
            }
        }		// No Break
    case util::NumberFormat::PERCENT:
        {
            if (!bWasSetTypeAttribute)
            {
                pExport->AddAttribute(sAttrValueType, XML_PERCENTAGE);
                bWasSetTypeAttribute = sal_True;
            }
        }		// No Break
    case util::NumberFormat::CURRENCY:
        {
            if (!bWasSetTypeAttribute)
            {
                pExport->AddAttribute(sAttrValueType, XML_CURRENCY);
                if (rCurrency.getLength() > 0)
                    pExport->AddAttribute(sAttrCurrency, rCurrency);
                bWasSetTypeAttribute = sal_True;
            }

            if (bExportValue)
            {
                ::rtl::OUString sValue( ::rtl::math::doubleToUString( rValue,
                            rtl_math_StringFormat_Automatic,
                            rtl_math_DecimalPlaces_Max, '.', sal_True));
                pExport->AddAttribute(sAttrValue, sValue);
            }
        }
        break;
    case util::NumberFormat::DATE:
    case util::NumberFormat::DATETIME:
        {
            if (!bWasSetTypeAttribute)
            {
                pExport->AddAttribute(sAttrValueType, XML_DATE);
                bWasSetTypeAttribute = sal_True;
            }
            if (bExportValue)
            {
                if ( pExport->GetMM100UnitConverter().setNullDate(pExport->GetModel()) )
                {
                    ::rtl::OUStringBuffer sBuffer;
                    pExport->GetMM100UnitConverter().convertDateTime(sBuffer, rValue);
                    pExport->AddAttribute(sAttrDateValue, sBuffer.makeStringAndClear());
                }
            }
        }
        break;
    case util::NumberFormat::TIME:
        {
            if (!bWasSetTypeAttribute)
            {
                pExport->AddAttribute(sAttrValueType, XML_TIME);
                bWasSetTypeAttribute = sal_True;
            }
            if (bExportValue)
            {
                ::rtl::OUStringBuffer sBuffer;
                pExport->GetMM100UnitConverter().convertTime(sBuffer, rValue);
                pExport->AddAttribute(sAttrTimeValue, sBuffer.makeStringAndClear());
            }
        }
        break;
    case util::NumberFormat::LOGICAL:
        {
            if (!bWasSetTypeAttribute)
            {
                pExport->AddAttribute(sAttrValueType, XML_BOOLEAN);
                bWasSetTypeAttribute = sal_True;
            }
            if (bExportValue)
            {
                ::rtl::OUString sOUValue;
                double fTempValue = rValue;
                if (::rtl::math::approxEqual( fTempValue, 1.0 ))
                {
                    pExport->AddAttribute(sAttrBooleanValue, XML_TRUE);
                }
                else
                {
                    if (::rtl::math::approxEqual( rValue, 0.0 ))
                    {
                        pExport->AddAttribute(nNamespace, XML_BOOLEAN_VALUE, XML_FALSE);
                    }
                    else
                    {
                        ::rtl::OUString sValue( ::rtl::math::doubleToUString(
                                    fTempValue,
                                    rtl_math_StringFormat_Automatic,
                                    rtl_math_DecimalPlaces_Max, '.',
                                    sal_True));
                        pExport->AddAttribute(sAttrBooleanValue, sValue);
                    }
                }
            }
        }
        break;
    case util::NumberFormat::TEXT:
        {
            if (!bWasSetTypeAttribute)
            {
                pExport->AddAttribute(sAttrValueType, XML_FLOAT);
                bWasSetTypeAttribute = sal_True;
                if (bExportValue)
                {
                    ::rtl::OUString sValue( ::rtl::math::doubleToUString( rValue,
                                rtl_math_StringFormat_Automatic,
                                rtl_math_DecimalPlaces_Max, '.', sal_True));
                    pExport->AddAttribute(sAttrValue, sValue);
                }
            }
        }
        break;
    }
}

void XMLNumberFormatAttributesExportHelper::SetNumberFormatAttributes(
    const sal_Int32 nNumberFormat, const double& rValue, sal_Bool bExportValue)
{
    if (pExport)
    {
        sal_Bool bIsStandard;
        ::rtl::OUString sCurrency;
        sal_Int16 nTypeKey = GetCellType(nNumberFormat, sCurrency, bIsStandard);
        WriteAttributes(nTypeKey, rValue, sCurrency, bExportValue);
    }
    else
        DBG_ERROR("no SvXMLExport given");
}

void XMLNumberFormatAttributesExportHelper::SetNumberFormatAttributes(
    const ::rtl::OUString& rValue, const ::rtl::OUString& rCharacters,
    sal_Bool bExportValue, sal_Bool bExportTypeAttribute)
{
    if (pExport)
    {
        if (bExportTypeAttribute)
            pExport->AddAttribute(sAttrValueType, XML_STRING);
        if (bExportValue && rValue.getLength() && (rValue != rCharacters))
            pExport->AddAttribute(sAttrStringValue, rValue);
    }
    else
        DBG_ERROR("no SvXMLExport given");
}
}//end of namespace binfilter
