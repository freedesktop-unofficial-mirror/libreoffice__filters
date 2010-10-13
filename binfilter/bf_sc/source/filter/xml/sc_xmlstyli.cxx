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

#ifdef _MSC_VER
#pragma hdrstop
#endif

#include "xmlstyli.hxx"
#include <bf_xmloff/nmspmap.hxx>
#include <bf_xmloff/xmlnmspe.hxx>
#include <bf_xmloff/xmlnumfi.hxx>
#include <bf_xmloff/XMLGraphicsDefaultStyle.hxx>

#include <com/sun/star/sheet/XSheetConditionalEntries.hpp>
#include <com/sun/star/table/BorderLine.hpp>
#include <comphelper/extract.hxx>
#include "XMLTableHeaderFooterContext.hxx"
#include "XMLConverter.hxx"

#include "docuno.hxx"
#include "unonames.hxx"
namespace binfilter {

//#define SC_NUMBERFORMAT "NumberFormat"
#define SC_CONDITIONALFORMAT "ConditionalFormat"

#define XML_LINE_LEFT 0
#define XML_LINE_RIGHT 1
#define XML_LINE_TOP 2
#define XML_LINE_BOTTOM 3

using namespace ::rtl;
using namespace ::com::sun::star;
using namespace ::com::sun::star::uno;
using namespace ::com::sun::star::xml::sax;
using namespace ::com::sun::star::style;
using namespace ::com::sun::star::frame;
using namespace ::com::sun::star::beans;
using namespace ::com::sun::star::container;
using namespace xmloff::token;
//using namespace ::com::sun::star::text;

ScXMLCellImportPropertyMapper::ScXMLCellImportPropertyMapper(
        const UniReference< XMLPropertySetMapper >& rMapper,
        SvXMLImport& rImport) :
    SvXMLImportPropertyMapper( rMapper, rImport )
{
}

ScXMLCellImportPropertyMapper::~ScXMLCellImportPropertyMapper()
{
}

void ScXMLCellImportPropertyMapper::finished(::std::vector< XMLPropertyState >& rProperties, sal_Int32 nStartIndex, sal_Int32 nEndIndex ) const
{
    static const sal_Int16 aPaddingCTF[4] = { CTF_SC_LEFTPADDING, CTF_SC_RIGHTPADDING,
                                            CTF_SC_TOPPADDING, CTF_SC_BOTTOMPADDING };
    static const sal_Int16 aBorderCTF[4] = { CTF_SC_LEFTBORDER, CTF_SC_RIGHTBORDER,
                                            CTF_SC_TOPBORDER, CTF_SC_BOTTOMBORDER };

    SvXMLImportPropertyMapper::finished(rProperties, nStartIndex, nEndIndex);
    XMLPropertyState* pAllPaddingProperty = NULL;
    XMLPropertyState* pPadding[4] = { NULL, NULL, NULL, NULL };
    XMLPropertyState* pNewPadding[4] = { NULL, NULL, NULL, NULL };
    XMLPropertyState* pAllBorderProperty = NULL;
    XMLPropertyState* pBorders[4] = { NULL, NULL, NULL, NULL };
    XMLPropertyState* pNewBorders[4] = { NULL, NULL, NULL, NULL };
    XMLPropertyState* pAllBorderWidthProperty = NULL;
    XMLPropertyState* pBorderWidths[4] = { NULL, NULL, NULL, NULL };
    for (::std::vector< XMLPropertyState >::iterator aIter = rProperties.begin(); aIter != rProperties.end(); ++aIter)
    {
        XMLPropertyState *property = &(*aIter);
        sal_Int16 nContextID = getPropertySetMapper()->GetEntryContextId(property->mnIndex);
        switch (nContextID)
        {
            case CTF_SC_ALLPADDING					: pAllPaddingProperty = property; break;
            case CTF_SC_LEFTPADDING					: pPadding[XML_LINE_LEFT] = property; break;
            case CTF_SC_RIGHTPADDING				: pPadding[XML_LINE_RIGHT] = property; break;
            case CTF_SC_TOPPADDING					: pPadding[XML_LINE_TOP] = property; break;
            case CTF_SC_BOTTOMPADDING				: pPadding[XML_LINE_BOTTOM] = property; break;
            case CTF_SC_ALLBORDER					: pAllBorderProperty = property; break;
            case CTF_SC_LEFTBORDER					: pBorders[XML_LINE_LEFT] = property; break;
            case CTF_SC_RIGHTBORDER					: pBorders[XML_LINE_RIGHT] = property; break;
            case CTF_SC_TOPBORDER					: pBorders[XML_LINE_TOP] = property; break;
            case CTF_SC_BOTTOMBORDER				: pBorders[XML_LINE_BOTTOM] = property; break;
            case CTF_SC_ALLBORDERWIDTH				: pAllBorderWidthProperty = property; break;
            case CTF_SC_LEFTBORDERWIDTH				: pBorderWidths[XML_LINE_LEFT] = property; break;
            case CTF_SC_RIGHTBORDERWIDTH			: pBorderWidths[XML_LINE_RIGHT] = property; break;
            case CTF_SC_TOPBORDERWIDTH				: pBorderWidths[XML_LINE_TOP] = property; break;
            case CTF_SC_BOTTOMBORDERWIDTH			: pBorderWidths[XML_LINE_BOTTOM] = property; break;
        }
    }
    sal_uInt16 i;
    for (i = 0; i < 4; i++)
    {
        if (pAllPaddingProperty && !pPadding[i])
            pNewPadding[i] = new XMLPropertyState(maPropMapper->FindEntryIndex(aPaddingCTF[i]), pAllPaddingProperty->maValue);
        if (pAllBorderProperty && !pBorders[i])
        {
            pNewBorders[i] = new XMLPropertyState(maPropMapper->FindEntryIndex(aBorderCTF[i]), pAllBorderProperty->maValue);
            pBorders[i] = pNewBorders[i];
        }
        if( !pBorderWidths[i] )
            pBorderWidths[i] = pAllBorderWidthProperty;
        else
            pBorderWidths[i]->mnIndex = -1;
        if( pBorders[i] )
        {
            table::BorderLine aBorderLine;
            pBorders[i]->maValue >>= aBorderLine;
             if( pBorderWidths[i] )
            {
                table::BorderLine aBorderLineWidth;
                pBorderWidths[i]->maValue >>= aBorderLineWidth;
                aBorderLine.OuterLineWidth = aBorderLineWidth.OuterLineWidth;
                aBorderLine.InnerLineWidth = aBorderLineWidth.InnerLineWidth;
                aBorderLine.LineDistance = aBorderLineWidth.LineDistance;
                pBorders[i]->maValue <<= aBorderLine;
            }
        }
    }
    for (i = 0; i < 4; i++)
    {
        if (pNewPadding[i])
        {
            rProperties.push_back(*pNewPadding[i]);
            delete pNewPadding[i];
        }
        if (pNewBorders[i])
        {
            rProperties.push_back(*pNewBorders[i]);
            delete pNewBorders[i];
        }
    }
}

ScXMLRowImportPropertyMapper::ScXMLRowImportPropertyMapper(
        const UniReference< XMLPropertySetMapper >& rMapper,
        SvXMLImport& rImport) :
    SvXMLImportPropertyMapper( rMapper, rImport )
{
}

ScXMLRowImportPropertyMapper::~ScXMLRowImportPropertyMapper()
{
}

void ScXMLRowImportPropertyMapper::finished(::std::vector< XMLPropertyState >& rProperties, sal_Int32 nStartIndex, sal_Int32 nEndIndex ) const
{
    SvXMLImportPropertyMapper::finished(rProperties, nStartIndex, nEndIndex);
    XMLPropertyState* pHeight = NULL;
    XMLPropertyState* pOptimalHeight = NULL;
    XMLPropertyState* pPageBreak = NULL;
    for (::std::vector< XMLPropertyState >::iterator aIter = rProperties.begin(); aIter != rProperties.end(); ++aIter)
    {
        XMLPropertyState *property = &(*aIter);
        sal_Int16 nContextID = getPropertySetMapper()->GetEntryContextId(property->mnIndex);
        switch (nContextID)
        {
            case CTF_SC_ROWHEIGHT					: pHeight = property; break;
            case CTF_SC_ROWOPTIMALHEIGHT			: pOptimalHeight = property; break;
            case CTF_SC_ROWBREAKBEFORE				: pPageBreak = property; break;
        }
    }
    if (pPageBreak)
    {
        if(!(::cppu::any2bool(pPageBreak->maValue)))
            pPageBreak->mnIndex = -1;
    }
    if (pOptimalHeight)
    {
        sal_Bool bOptimalHeight = ::cppu::any2bool(pOptimalHeight->maValue);
        if (bOptimalHeight)
        {
            if (pHeight)
                pHeight->mnIndex = -1;
            pOptimalHeight->mnIndex = -1;
        }
    }
    else if (pHeight)
    {
        pOptimalHeight = new XMLPropertyState(maPropMapper->FindEntryIndex(CTF_SC_ROWOPTIMALHEIGHT), ::cppu::bool2any( sal_False ));
        rProperties.push_back(*pOptimalHeight);
        delete pOptimalHeight;
    }
    // don't access pointers to rProperties elements after push_back!
}

class ScXMLMapContext : public SvXMLImportContext
{
    ::rtl::OUString sApplyStyle;
    ::rtl::OUString sCondition;
    ::rtl::OUString sBaseCell;
public:

    ScXMLMapContext(
            SvXMLImport& rImport, sal_uInt16 nPrfx,
            const ::rtl::OUString& rLName,
            const Reference< xml::sax::XAttributeList > & xAttrList );
    virtual ~ScXMLMapContext();

    const ::rtl::OUString& GetApplyStyle() const { return sApplyStyle; }
    const ::rtl::OUString& GetCondition() const { return sCondition; }
    const ::rtl::OUString& GetBaseCell() const { return sBaseCell; }
};

ScXMLMapContext::ScXMLMapContext(SvXMLImport& rImport, sal_uInt16 nPrfx,
            const OUString& rLName,	const Reference< xml::sax::XAttributeList > & xAttrList )
    : SvXMLImportContext( rImport, nPrfx, rLName ),
    sCondition(),
    sApplyStyle(),
    sBaseCell()
{
    sal_Int16 nAttrCount = xAttrList.is() ? xAttrList->getLength() : 0;
    for( sal_Int16 i=0; i < nAttrCount; i++ )
    {
        const OUString& rAttrName = xAttrList->getNameByIndex( i );
        OUString aLocalName;
        sal_uInt16 nPrefix =
            GetImport().GetNamespaceMap().GetKeyByAttrName( rAttrName,
                                                            &aLocalName );
        const OUString& rValue = xAttrList->getValueByIndex( i );

        // TODO: use a map here
        if( XML_NAMESPACE_STYLE == nPrefix )
        {
            if( IsXMLToken(aLocalName, XML_CONDITION ) )
                sCondition = rValue;
            else if( IsXMLToken(aLocalName, XML_APPLY_STYLE_NAME ) )
                sApplyStyle = rValue;
            else if ( IsXMLToken(aLocalName, XML_BASE_CELL_ADDRESS ) )
                sBaseCell = rValue;
        }
    }
}

ScXMLMapContext::~ScXMLMapContext()
{
}

void XMLTableStyleContext::SetOperator(::com::sun::star::uno::Sequence<beans::PropertyValue>& aProps,
        const ::com::sun::star::sheet::ConditionOperator aOp) const
{
    aProps.realloc(aProps.getLength() + 1);
    beans::PropertyValue aProp;
    aProp.Name = ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM(SC_UNONAME_OPERATOR));
    uno::Any aAnyOp;
    aAnyOp <<= aOp;
    aProp.Value = aAnyOp;
    aProps[aProps.getLength() - 1] = aProp;
}

void XMLTableStyleContext::SetBaseCellAddress(::com::sun::star::uno::Sequence<beans::PropertyValue>& aProps,
    const ::rtl::OUString& sBaseCell) const
{
    aProps.realloc(aProps.getLength() + 1);
    beans::PropertyValue aProp;
    table::CellAddress aBaseAddress;
    sal_Int32 nOffset(0);
    if ( ScXMLConverter::GetAddressFromString( aBaseAddress, sBaseCell, GetScImport().GetDocument(), nOffset ))
    {
        uno::Any aAnyBase;
        aAnyBase <<= aBaseAddress;
        aProp.Value = aAnyBase;
        aProp.Name = ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM(SC_UNONAME_SOURCEPOS));
        aProps[aProps.getLength() - 1] = aProp;
    }
}

void XMLTableStyleContext::SetStyle(::com::sun::star::uno::Sequence<beans::PropertyValue>& aProps,
    const ::rtl::OUString& sApplyStyle) const
{
    aProps.realloc(aProps.getLength() + 1);
    beans::PropertyValue aProp;
    aProp.Name = ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM(SC_UNONAME_STYLENAME));
    uno::Any aAnyApplyStyle;
    aAnyApplyStyle <<= sApplyStyle;
    aProp.Value = aAnyApplyStyle;
    aProps[aProps.getLength() - 1] = aProp;
}

void XMLTableStyleContext::SetFormula1(::com::sun::star::uno::Sequence< ::com::sun::star::beans::PropertyValue>& aProps,
    const ::rtl::OUString& sFormula) const
{
    aProps.realloc(aProps.getLength() + 1);
    beans::PropertyValue aProp;
    aProp.Name = ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM(SC_UNONAME_FORMULA1));
    ::rtl::OUString sRealFormula(sFormula);
    ScXMLConverter::ParseFormula(sRealFormula);
    uno::Any aAnyFormula;
    aAnyFormula <<= sRealFormula;
    aProp.Value = aAnyFormula;
    aProps[aProps.getLength() - 1] = aProp;
}

void XMLTableStyleContext::SetFormula2(::com::sun::star::uno::Sequence< ::com::sun::star::beans::PropertyValue>& aProps,
    const ::rtl::OUString& sFormula) const
{
    aProps.realloc(aProps.getLength() + 1);
    beans::PropertyValue aProp;
    aProp.Name = ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM(SC_UNONAME_FORMULA2));
    ::rtl::OUString sRealFormula(sFormula);
    ScXMLConverter::ParseFormula(sRealFormula);
    uno::Any aAnyFormula;
    aAnyFormula <<= sRealFormula;
    aProp.Value = aAnyFormula;
    aProps[aProps.getLength() - 1] = aProp;
}

void XMLTableStyleContext::SetFormulas(::com::sun::star::uno::Sequence< ::com::sun::star::beans::PropertyValue>& aProps,
    const ::rtl::OUString& sFormulas) const
{
    sal_Int32 i = 0;
    sal_Bool bString = sal_False;
    sal_Int32 nBrakes = 0;
    while ((sFormulas[i] != ',' || nBrakes > 0 || bString) && i < sFormulas.getLength())
    {
        if (sFormulas[i] == '(')
            nBrakes++;
        if (sFormulas[i] == ')')
            nBrakes--;
        if (sFormulas[i] == '"')
            bString = !bString;
        i++;
    }
    if (sFormulas[i] == ',')
    {
        ::rtl::OUString sFormula1 = sFormulas.copy(0, i);
        ::rtl::OUString sFormula2 = sFormulas.copy(i + 1);
        SetFormula1(aProps, sFormula1);
        SetFormula2(aProps, sFormula2);
    }
}

void XMLTableStyleContext::GetConditionalFormat(uno::Any& aAny,
        const ::rtl::OUString& sTempCondition,
        const ::rtl::OUString& sApplyStyle, const ::rtl::OUString& sBaseCell) const
{
    ::rtl::OUString sCondition = sTempCondition;
    if (sCondition.getLength() && sApplyStyle.getLength())
    {
        uno::Reference<sheet::XSheetConditionalEntries> xConditionalEntries;
        if (aAny >>= xConditionalEntries)
        {
            // ToDo: erase all blanks in the condition, but not in formulas or strings
            ::rtl::OUString scell_content(RTL_CONSTASCII_USTRINGPARAM("cell_content"));
            ::rtl::OUString scell_content_is_between(RTL_CONSTASCII_USTRINGPARAM("cell_content_is_between"));
            ::rtl::OUString scell_content_is_not_between(RTL_CONSTASCII_USTRINGPARAM("cell_content_is_not_between"));
            ::rtl::OUString sis_true_formula(RTL_CONSTASCII_USTRINGPARAM("is_true_formula"));
            uno::Sequence<beans::PropertyValue> aProps;
            if (sBaseCell.getLength())
                SetBaseCellAddress(aProps, sBaseCell);
            SetStyle(aProps, sApplyStyle);
            sal_Int32 i = 0;
            while (sCondition[i] != '(' && i < sCondition.getLength())
                i++;
            if (sCondition[i] == '(')
            {
                sCondition = sCondition.copy(i + 1);
                if (i == scell_content.getLength())
                {
                    sCondition = sCondition.copy(1);
                    switch (sCondition[0])
                    {
                        case '<' :
                        {
                            if (sCondition[1] == '=')
                            {
                                SetOperator(aProps, sheet::ConditionOperator_LESS_EQUAL);
                                sCondition = sCondition.copy(2);
                            }
                            else
                            {
                                SetOperator(aProps, sheet::ConditionOperator_LESS);
                                sCondition = sCondition.copy(1);
                            }
                        }
                        break;
                        case '>' :
                        {
                            if (sCondition[1] == '=')
                            {
                                SetOperator(aProps, sheet::ConditionOperator_GREATER_EQUAL);
                                sCondition = sCondition.copy(2);
                            }
                            else
                            {
                                SetOperator(aProps, sheet::ConditionOperator_GREATER);
                                sCondition = sCondition.copy(1);
                            }
                        }
                        break;
                        case '=' :
                        {
                            SetOperator(aProps, sheet::ConditionOperator_EQUAL);
                            sCondition = sCondition.copy(1);
                        }
                        break;
                        case '!' :
                        {
                            SetOperator(aProps, sheet::ConditionOperator_NOT_EQUAL);
                            sCondition = sCondition.copy(1);
                        }
                        break;
                    }
                    SetFormula1(aProps, sCondition);
                }
                else if (i == scell_content_is_between.getLength())
                {
                    SetOperator(aProps, sheet::ConditionOperator_BETWEEN);
                    sCondition = sCondition.copy(0, sCondition.getLength() - 1);
                    SetFormulas(aProps, sCondition);
                }
                else if (i == scell_content_is_not_between.getLength())
                {
                    SetOperator(aProps, sheet::ConditionOperator_NOT_BETWEEN);
                    sCondition = sCondition.copy(0, sCondition.getLength() - 1);
                    SetFormulas(aProps, sCondition);
                }
                else if (i == sis_true_formula.getLength())
                {
                    SetOperator(aProps, sheet::ConditionOperator_FORMULA);
                    sCondition = sCondition.copy(0, sCondition.getLength() - 1);
                    SetFormula1(aProps, sCondition);
                }
            }
            xConditionalEntries->addNew(aProps);
            aAny <<= xConditionalEntries;
        }
    }
}

void XMLTableStyleContext::SetAttribute( sal_uInt16 nPrefixKey,
                                        const OUString& rLocalName,
                                        const OUString& rValue )
{
    // TODO: use a map here
    if( IsXMLToken(rLocalName, XML_DATA_STYLE_NAME ) )
        sDataStyleName = rValue;
    else if ( IsXMLToken(rLocalName, XML_MASTER_PAGE_NAME ) )
        sPageStyle = rValue;
    else
        XMLPropStyleContext::SetAttribute( nPrefixKey, rLocalName, rValue );
}

struct ScXMLMapContent
{
    ::rtl::OUString sCondition;
    ::rtl::OUString sApplyStyle;
    ::rtl::OUString sBaseCell;
};

TYPEINIT1( XMLTableStyleContext, XMLPropStyleContext );

XMLTableStyleContext::XMLTableStyleContext( ScXMLImport& rImport,
        sal_uInt16 nPrfx, const OUString& rLName,
        const Reference< XAttributeList > & xAttrList,
        SvXMLStylesContext& rStyles, sal_uInt16 nFamily, sal_Bool bDefaultStyle ) :
    XMLPropStyleContext( rImport, nPrfx, rLName, xAttrList, rStyles, nFamily, bDefaultStyle ),
    sNumberFormat(::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("NumberFormat"))),
    sDataStyleName(),
    pStyles(&rStyles),
    nNumberFormat(-1),
    bParentSet(sal_False),
    bConditionalFormatCreated(sal_False)
{
}

XMLTableStyleContext::~XMLTableStyleContext()
{
}

SvXMLImportContext *XMLTableStyleContext::CreateChildContext(
        sal_uInt16 nPrefix,
        const OUString& rLocalName,
        const Reference< XAttributeList > & xAttrList )
{
    SvXMLImportContext *pContext = NULL;

    if( (XML_NAMESPACE_STYLE == nPrefix) &&
        IsXMLToken(rLocalName, XML_MAP ) )
    {
        pContext = new ScXMLMapContext(GetImport(), nPrefix, rLocalName, xAttrList);

        ScXMLMapContent aMap;
        aMap.sCondition = ((ScXMLMapContext*)pContext)->GetCondition();
        aMap.sApplyStyle = ((ScXMLMapContext*)pContext)->GetApplyStyle();
        aMap.sBaseCell = ((ScXMLMapContext*)pContext)->GetBaseCell();
        aMaps.push_back(aMap);
    }
    if (!pContext)
        pContext = XMLPropStyleContext::CreateChildContext( nPrefix, rLocalName,
                                                           xAttrList );
    return pContext;
}

void XMLTableStyleContext::FillPropertySet(
            const Reference< XPropertySet > & rPropSet )
{
    if (!IsDefaultStyle())
    {
        if (GetFamily() == XML_STYLE_FAMILY_TABLE_CELL)
        {
            if (!bParentSet)
            {
                ::rtl::OUString sParentName = GetParent();
                uno::Any aStyleName;
                aStyleName <<= sParentName;
                AddProperty(CTF_SC_CELLSTYLE, aStyleName);
                bParentSet = sal_True;
            }
            if ((nNumberFormat == -1) && sDataStyleName.getLength())
            {
                SvXMLNumFormatContext* pStyle = (SvXMLNumFormatContext *)pStyles->FindStyleChildContext(
                    XML_STYLE_FAMILY_DATA_STYLE, sDataStyleName, sal_True);
                if (!pStyle)
                {
                    XMLTableStylesContext* pMyStyles = (XMLTableStylesContext *)GetScImport().GetStyles();
                    if (pMyStyles)
                        pStyle = (SvXMLNumFormatContext *)pMyStyles->
                            FindStyleChildContext(XML_STYLE_FAMILY_DATA_STYLE, sDataStyleName, sal_True);
                    else
                        DBG_ERROR("not possible to get style");
                }
                if (pStyle)
                {
                    uno::Any aNumberFormat;
                    nNumberFormat = pStyle->GetKey();
                    aNumberFormat <<= nNumberFormat;
                    //rPropSet->setPropertyValue(::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM(SC_NUMBERFORMAT)), aNumberFormat);
                    AddProperty(CTF_SC_NUMBERFORMAT, aNumberFormat);
                }
            }
            if (!bConditionalFormatCreated && (aMaps.size() > 0))
            {
                aConditionalFormat = rPropSet->getPropertyValue(::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM(SC_CONDITIONALFORMAT)));
                std::vector<ScXMLMapContent>::iterator aItr = aMaps.begin();
                while(aItr != aMaps.end())
                {
                    //rPropSet->setPropertyValue(::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM(SC_CONDITIONALFORMAT)),
                    GetConditionalFormat(aConditionalFormat, aItr->sCondition, aItr->sApplyStyle, aItr->sBaseCell);

                    aItr++;
                }
                AddProperty(CTF_SC_IMPORT_MAP, aConditionalFormat);
                bConditionalFormatCreated = sal_True;
            }
        }
        else if (GetFamily() == XML_STYLE_FAMILY_TABLE_TABLE)
        {
            if (sPageStyle.getLength())
            {
                uno::Any aAny;
                aAny <<= sPageStyle;
                AddProperty(CTF_SC_MASTERPAGENAME, aAny);
            }
        }
    }
    XMLPropStyleContext::FillPropertySet(rPropSet);
}

void XMLTableStyleContext::SetDefaults()
{
    if ((GetFamily() == XML_STYLE_FAMILY_TABLE_CELL) && GetImport().GetModel().is())
    {
        uno::Reference <lang::XMultiServiceFactory> xMultiServiceFactory(GetImport().GetModel(), uno::UNO_QUERY);
        if (xMultiServiceFactory.is())
        {
            uno::Reference <uno::XInterface> xInterface = xMultiServiceFactory->createInstance(::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("com.sun.star.sheet.Defaults")));
            uno::Reference <beans::XPropertySet> xProperties(xInterface, uno::UNO_QUERY);
            if (xProperties.is())
                FillPropertySet(xProperties);
        }
    }
}

void XMLTableStyleContext::AddProperty(const sal_Int16 nContextID, const uno::Any& rValue)
{
    sal_Int32 nIndex(static_cast<XMLTableStylesContext *>(pStyles)->GetIndex(nContextID));
    DBG_ASSERT(nIndex != -1, "Property not found in Map");
    XMLPropertyState aPropState(nIndex, rValue);
    GetProperties().push_back(aPropState); // has to be insertes in a sort order later
}

// ----------------------------------------------------------------------------

SvXMLStyleContext *XMLTableStylesContext::CreateStyleStyleChildContext(
        sal_uInt16 nFamily, sal_uInt16 nPrefix, const OUString& rLocalName,
        const Reference< xml::sax::XAttributeList > & xAttrList )
{
    SvXMLStyleContext *pStyle = SvXMLStylesContext::CreateStyleStyleChildContext( nFamily, nPrefix,
                                                            rLocalName,
                                                            xAttrList );
    if (!pStyle)
    {
        switch( nFamily )
        {
        case XML_STYLE_FAMILY_TABLE_CELL:
        case XML_STYLE_FAMILY_TABLE_COLUMN:
        case XML_STYLE_FAMILY_TABLE_ROW:
        case XML_STYLE_FAMILY_TABLE_TABLE:
            pStyle = new XMLTableStyleContext( GetScImport(), nPrefix, rLocalName,
                                               xAttrList, *this, nFamily );
            break;
        }
    }

    return pStyle;
}

SvXMLStyleContext *XMLTableStylesContext::CreateDefaultStyleStyleChildContext(
        sal_uInt16 nFamily, sal_uInt16 nPrefix, const OUString& rLocalName,
        const uno::Reference< xml::sax::XAttributeList > & xAttrList )
{
    SvXMLStyleContext *pStyle = SvXMLStylesContext::CreateDefaultStyleStyleChildContext( nFamily, nPrefix,
                                                            rLocalName,
                                                            xAttrList );
    if (!pStyle)
    {
        switch( nFamily )
        {
            case XML_STYLE_FAMILY_TABLE_CELL:
                pStyle = new XMLTableStyleContext( GetScImport(), nPrefix, rLocalName,
                                            xAttrList, *this, nFamily, sal_True);
            break;
            case XML_STYLE_FAMILY_SD_GRAPHICS_ID:
                pStyle = new XMLGraphicsDefaultStyle( GetScImport(), nPrefix, rLocalName,
                                            xAttrList, *this);
            break;
        }
    }

    return pStyle;
}

XMLTableStylesContext::XMLTableStylesContext( SvXMLImport& rImport,
        sal_uInt16 nPrfx ,
        const OUString& rLName ,
        const Reference< XAttributeList > & xAttrList,
        const sal_Bool bTempAutoStyles ) :
    SvXMLStylesContext( rImport, nPrfx, rLName, xAttrList ),
    sCellStyleServiceName( ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM( "com.sun.star.style.CellStyle" ) )),
    sColumnStyleServiceName( ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM( XML_STYLE_FAMILY_TABLE_COLUMN_STYLES_NAME ))),
    sRowStyleServiceName( ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM( XML_STYLE_FAMILY_TABLE_ROW_STYLES_NAME ))),
    sTableStyleServiceName( ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM( XML_STYLE_FAMILY_TABLE_TABLE_STYLES_NAME ))),
    nNumberFormatIndex(-1),
    nConditionalFormatIndex(-1),
    nCellStyleIndex(-1),
    nMasterPageNameIndex(-1),
    bAutoStyles(bTempAutoStyles)
{
}

XMLTableStylesContext::~XMLTableStylesContext()
{
}

void XMLTableStylesContext::EndElement()
{
    SvXMLStylesContext::EndElement();
    if (bAutoStyles)
        GetImport().GetTextImport()->SetAutoStyles( this );
    else
        ((ScXMLImport&)GetImport()).InsertStyles();
}

UniReference < SvXMLImportPropertyMapper >
    XMLTableStylesContext::GetImportPropertyMapper(
                    sal_uInt16 nFamily ) const
{
    UniReference < SvXMLImportPropertyMapper > xMapper =
        SvXMLStylesContext::GetImportPropertyMapper(nFamily);

    if (!xMapper.is())
    {
        switch( nFamily )
        {
            case XML_STYLE_FAMILY_TABLE_CELL:
            {
                if( !xCellImpPropMapper.is() )
                {
                    ((XMLTableStylesContext *)this)->xCellImpPropMapper =
                        new ScXMLCellImportPropertyMapper( GetScImport().GetCellStylesPropertySetMapper(), const_cast<SvXMLImport&>(GetImport()) );
                    xCellImpPropMapper->ChainImportMapper(XMLTextImportHelper::CreateCharExtPropMapper(const_cast<SvXMLImport&>(GetImport()), const_cast<XMLFontStylesContext*>(GetScImport().GetFontDecls())));
                }
                xMapper = xCellImpPropMapper;
            }
            break;
            case XML_STYLE_FAMILY_TABLE_COLUMN:
            {
                if( !xColumnImpPropMapper.is() )
                    ((XMLTableStylesContext *)this)->xColumnImpPropMapper =
                        new SvXMLImportPropertyMapper( GetScImport().GetColumnStylesPropertySetMapper(), const_cast<SvXMLImport&>(GetImport()) );
                xMapper = xColumnImpPropMapper;
            }
             break;
            case XML_STYLE_FAMILY_TABLE_ROW:
            {
                if( !xRowImpPropMapper.is() )
                    ((XMLTableStylesContext *)this)->xRowImpPropMapper =
                        new ScXMLRowImportPropertyMapper( GetScImport().GetRowStylesPropertySetMapper(), const_cast<SvXMLImport&>(GetImport()) );
                xMapper = xRowImpPropMapper;
            }
             break;
            case XML_STYLE_FAMILY_TABLE_TABLE:
            {
                if( !xTableImpPropMapper.is() )
                    ((XMLTableStylesContext *)this)->xTableImpPropMapper =
                        new SvXMLImportPropertyMapper( GetScImport().GetTableStylesPropertySetMapper(), const_cast<SvXMLImport&>(GetImport()) );
                xMapper = xTableImpPropMapper;
            }
             break;
        }
    }

    return xMapper;
}

Reference < XNameContainer >
        XMLTableStylesContext::GetStylesContainer( sal_uInt16 nFamily ) const
{
    Reference < XNameContainer > xStyles = SvXMLStylesContext::GetStylesContainer(nFamily);
    if (!xStyles.is())
    {
        OUString sName;
        switch( nFamily )
        {
            case XML_STYLE_FAMILY_TABLE_TABLE:
            {
                if( xTableStyles.is() )
                    xStyles = xTableStyles;
                else
                    sName =
                        OUString( ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM( "TableStyles" ) ));
            }
            break;
            case XML_STYLE_FAMILY_TABLE_CELL:
            {
                if( xCellStyles.is() )
                    xStyles = xCellStyles;
                else
                    sName =
                        OUString( ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM( "CellStyles" ) ));
            }
            break;
            case XML_STYLE_FAMILY_TABLE_COLUMN:
            {
                if( xColumnStyles.is() )
                    xStyles = xColumnStyles;
                else
                    sName =
                        OUString( ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM( "ColumnStyles" ) ));
            }
            break;
            case XML_STYLE_FAMILY_TABLE_ROW:
            {
                if( xRowStyles.is() )
                    xStyles = xRowStyles;
                else
                    sName =
                        OUString( ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM( "RowStyles" ) ));
            }
            break;
        }
        if( !xStyles.is() && sName.getLength() && GetScImport().GetModel().is() )
        {
            Reference< XStyleFamiliesSupplier > xFamiliesSupp(
                                            GetScImport().GetModel(), UNO_QUERY );
            if (xFamiliesSupp.is())
            {
                Reference< XNameAccess > xFamilies = xFamiliesSupp->getStyleFamilies();
                Any aAny = xFamilies->getByName( sName );

                xStyles = *(Reference<XNameContainer>*)aAny.getValue();
                switch( nFamily )
                {
                case XML_STYLE_FAMILY_TABLE_TABLE:
                    ((XMLTableStylesContext *)this)->xTableStyles = xStyles;
                    break;
                case XML_STYLE_FAMILY_TABLE_CELL:
                    ((XMLTableStylesContext *)this)->xCellStyles = xStyles;
                    break;
                case XML_STYLE_FAMILY_TABLE_COLUMN:
                    ((XMLTableStylesContext *)this)->xColumnStyles = xStyles;
                    break;
                case XML_STYLE_FAMILY_TABLE_ROW:
                    ((XMLTableStylesContext *)this)->xRowStyles = xStyles;
                    break;
                }
            }
        }
    }

    return xStyles;
}

OUString XMLTableStylesContext::GetServiceName( sal_uInt16 nFamily ) const
{
    ::rtl::OUString sServiceName = SvXMLStylesContext::GetServiceName(nFamily);
    if (!sServiceName.getLength())
    {
        switch( nFamily )
        {
        case XML_STYLE_FAMILY_TABLE_COLUMN:
            sServiceName = sColumnStyleServiceName;
            break;
        case XML_STYLE_FAMILY_TABLE_ROW:
            sServiceName = sRowStyleServiceName;
            break;
        case XML_STYLE_FAMILY_TABLE_CELL:
            sServiceName = sCellStyleServiceName;
            break;
        case XML_STYLE_FAMILY_TABLE_TABLE:
            sServiceName = sTableStyleServiceName;
            break;
        }
    }
    return sServiceName;
}

sal_Int32 XMLTableStylesContext::GetIndex(const sal_Int16 nContextID)
{
    if (nContextID == CTF_SC_CELLSTYLE)
    {
        if (nCellStyleIndex == -1)
            nCellStyleIndex =
                GetImportPropertyMapper(XML_STYLE_FAMILY_TABLE_CELL)->getPropertySetMapper()->FindEntryIndex(nContextID);
        return nCellStyleIndex;
    }
    else if (nContextID == CTF_SC_NUMBERFORMAT)
    {
        if (nNumberFormatIndex == -1)
            nNumberFormatIndex =
                GetImportPropertyMapper(XML_STYLE_FAMILY_TABLE_CELL)->getPropertySetMapper()->FindEntryIndex(nContextID);
        return nNumberFormatIndex;
    }
    else if (nContextID == CTF_SC_IMPORT_MAP)
    {
        if (nConditionalFormatIndex == -1)
            nConditionalFormatIndex =
                GetImportPropertyMapper(XML_STYLE_FAMILY_TABLE_CELL)->getPropertySetMapper()->FindEntryIndex(nContextID);
        return nConditionalFormatIndex;
    }
    else if (nContextID == CTF_SC_MASTERPAGENAME)
    {
        if (nMasterPageNameIndex == -1)
                nMasterPageNameIndex =
                GetImportPropertyMapper(XML_STYLE_FAMILY_TABLE_TABLE)->getPropertySetMapper()->FindEntryIndex(nContextID);
        return nMasterPageNameIndex;
    }
    else
        return -1;
}

// ---------------------------------------------------------------------------
TYPEINIT1( ScXMLMasterStylesContext, SvXMLStylesContext );

sal_Bool ScXMLMasterStylesContext::InsertStyleFamily( sal_uInt16 ) const
{
    return sal_True;
}

ScXMLMasterStylesContext::ScXMLMasterStylesContext(
        SvXMLImport& rImport,
        sal_uInt16 nPrfx, const OUString& rLName,
        const Reference< XAttributeList > & xAttrList ) :
    SvXMLStylesContext( rImport, nPrfx, rLName, xAttrList )
{
}

ScXMLMasterStylesContext::~ScXMLMasterStylesContext()
{
}

SvXMLStyleContext *ScXMLMasterStylesContext::CreateStyleChildContext(
        sal_uInt16 nPrefix,
        const OUString& rLocalName,
        const Reference< XAttributeList > & xAttrList )
{
    SvXMLStyleContext *pContext = 0;

    if( (XML_NAMESPACE_STYLE == nPrefix) &&
        IsXMLToken(rLocalName, XML_MASTER_PAGE) &&
         InsertStyleFamily( XML_STYLE_FAMILY_MASTER_PAGE ) )
        pContext = new ScMasterPageContext(
                        GetImport(), nPrefix, rLocalName, xAttrList,
                        !GetImport().GetTextImport()->IsInsertMode() );

    // any other style will be ignored here!

    return pContext;
}

SvXMLStyleContext *ScXMLMasterStylesContext::CreateStyleStyleChildContext(
        sal_uInt16 nFamily,
        sal_uInt16 nPrefix,
        const OUString& rLocalName,
        const Reference< XAttributeList > & xAttrList )
{
    return 0;
}

void ScXMLMasterStylesContext::EndElement()
{
    FinishStyles(sal_True);
}

TYPEINIT1( ScMasterPageContext, XMLTextMasterPageContext );

ScMasterPageContext::ScMasterPageContext( SvXMLImport& rImport,
        sal_uInt16 nPrfx, const OUString& rLName,
        const Reference< XAttributeList > & xAttrList,
        sal_Bool bOverwrite ) :
    XMLTextMasterPageContext( rImport, nPrfx, rLName, xAttrList, bOverwrite ),
    bContainsRightHeader(sal_False),
    bContainsRightFooter(sal_False)
{
}

ScMasterPageContext::~ScMasterPageContext()
{
}

SvXMLImportContext *ScMasterPageContext::CreateChildContext(
        sal_uInt16 nPrefix,
        const OUString& rLocalName,
        const Reference< XAttributeList > & xAttrList )
{
    SvXMLImportContext *pContext = XMLTextMasterPageContext::CreateChildContext( nPrefix, rLocalName,
                                                          xAttrList );
    return pContext;
}

SvXMLImportContext *ScMasterPageContext::CreateHeaderFooterContext(
            sal_uInt16 nPrefix,
            const ::rtl::OUString& rLocalName,
            const ::com::sun::star::uno::Reference< ::com::sun::star::xml::sax::XAttributeList > & xAttrList,
            const sal_Bool bFooter,
            const sal_Bool bLeft )
{
    if (!bLeft)
        if (bFooter)
            bContainsRightFooter = sal_True;
        else
            bContainsRightHeader = sal_True;
    if (!xPropSet.is())
        xPropSet = Reference < XPropertySet > ( GetStyle(), UNO_QUERY );
    return new XMLTableHeaderFooterContext( GetImport(),
                                                nPrefix, rLocalName,
                                                xAttrList,
                                                xPropSet,
                                                bFooter, bLeft );
}

void ScMasterPageContext::ClearContent(const ::rtl::OUString& rContent)
{
    if (!xPropSet.is())
        xPropSet = Reference < XPropertySet > ( GetStyle(), UNO_QUERY );

    Any aAny;
    aAny = xPropSet->getPropertyValue( rContent );
    Reference < sheet::XHeaderFooterContent > xHeaderFooterContent;
    if (aAny >>= xHeaderFooterContent)
    {
        xHeaderFooterContent->getLeftText()->setString(sEmpty);
        xHeaderFooterContent->getCenterText()->setString(sEmpty);
        xHeaderFooterContent->getRightText()->setString(sEmpty);
        aAny <<= xHeaderFooterContent;
        xPropSet->setPropertyValue( rContent, aAny );
    }
}

void ScMasterPageContext::Finish( sal_Bool bOverwrite )
{
    XMLTextMasterPageContext::Finish(bOverwrite);
    if (!bContainsRightFooter)
        ClearContent(::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM(SC_UNO_PAGE_RIGHTFTRCON)));
    if (!bContainsRightHeader)
        ClearContent(::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM(SC_UNO_PAGE_RIGHTHDRCON)));
}
}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
