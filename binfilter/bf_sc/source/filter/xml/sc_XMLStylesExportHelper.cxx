/*************************************************************************
 *
 *  $RCSfile: sc_XMLStylesExportHelper.cxx,v $
 *
 *  $Revision: 1.3 $
 *
 *  last change: $Author: aw $ $Date: 2003-12-05 15:10:18 $
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

#ifdef PCH
#include "filt_pch.hxx"
#endif

#pragma hdrstop

// INCLUDE ---------------------------------------------------------------

#ifndef _SC_XMLSTYLESEXPORTHELPER_HXX
#include "XMLStylesExportHelper.hxx"
#endif

#ifndef SC_SCGLOB_HXX
#include "global.hxx"
#endif
#ifndef SC_UNONAMES_HXX
#include "unonames.hxx"
#endif
#ifndef _SC_XMLCONVERTER_HXX
#include "XMLConverter.hxx"
#endif
#ifndef SC_XMLEXPRT_HXX
#include "xmlexprt.hxx"
#endif
#ifndef SC_DOCUMENT_HXX
#include "document.hxx"
#endif

#ifndef _XMLOFF_XMLTOKEN_HXX
#include <bf_xmloff/xmltoken.hxx>
#endif
#ifndef _XMLOFF_XMLNMSPE_HXX
#include <bf_xmloff/xmlnmspe.hxx>
#endif
#ifndef _XMLOFF_XMLEVENTEXPORT_HXX
#include <bf_xmloff/XMLEventExport.hxx>
#endif

#ifndef _TOOLS_DEBUG_HXX
#include <tools/debug.hxx>
#endif
#ifndef _COM_SUN_STAR_UNO_REFERENCE_H_
#include <com/sun/star/uno/Reference.h>
#endif
#ifndef _COM_SUN_STAR_BEANS_XPROPERTYSET_HPP_
#include <com/sun/star/beans/XPropertySet.hpp>
#endif
#ifndef _COM_SUN_STAR_SHEET_XSHEETCONDITION_HPP_
#include <com/sun/star/sheet/XSheetCondition.hpp>
#endif

#include <algorithm>
namespace binfilter {

using namespace ::com::sun::star;
using namespace xmloff::token;

ScMyValidation::ScMyValidation()
    : sName(),
    sErrorMessage(),
    sErrorTitle(),
    sImputMessage(),
    sImputTitle(),
    sFormula1(),
    sFormula2(),
    bShowErrorMessage(sal_False),
    bShowImputMessage(sal_False),
    bIgnoreBlanks(sal_False)
{
}

ScMyValidation::~ScMyValidation()
{
}

sal_Bool ScMyValidation::IsEqual(const ScMyValidation& aVal) const
{
    if (aVal.bIgnoreBlanks == bIgnoreBlanks &&
        aVal.bShowImputMessage == bShowImputMessage &&
        aVal.bShowErrorMessage == bShowErrorMessage &&
        aVal.aBaseCell.Sheet == aBaseCell.Sheet &&
        aVal.aBaseCell.Column == aBaseCell.Column &&
        aVal.aBaseCell.Row == aBaseCell.Row &&
        aVal.aAlertStyle == aAlertStyle &&
        aVal.aValidationType == aValidationType &&
        aVal.aOperator == aOperator &&
        aVal.sErrorTitle == sErrorTitle &&
        aVal.sImputTitle == sImputTitle &&
        aVal.sErrorMessage == sErrorMessage &&
        aVal.sImputMessage == sImputMessage &&
        aVal.sFormula1 == sFormula1 &&
        aVal.sFormula2 == sFormula2)
        return sal_True;
    else
        return sal_False;
}

ScMyValidationsContainer::ScMyValidationsContainer()
    : aValidationVec(),
    sEmptyString(),
    sERRALSTY(RTL_CONSTASCII_USTRINGPARAM(SC_UNONAME_ERRALSTY)),
    sIGNOREBL(RTL_CONSTASCII_USTRINGPARAM(SC_UNONAME_IGNOREBL)),
    sTYPE(RTL_CONSTASCII_USTRINGPARAM(SC_UNONAME_TYPE)),
    sSHOWINP(RTL_CONSTASCII_USTRINGPARAM(SC_UNONAME_SHOWINP)),
    sSHOWERR(RTL_CONSTASCII_USTRINGPARAM(SC_UNONAME_SHOWERR)),
    sINPTITLE(RTL_CONSTASCII_USTRINGPARAM(SC_UNONAME_INPTITLE)),
    sINPMESS(RTL_CONSTASCII_USTRINGPARAM(SC_UNONAME_INPMESS)),
    sERRTITLE(RTL_CONSTASCII_USTRINGPARAM(SC_UNONAME_ERRTITLE)),
    sERRMESS(RTL_CONSTASCII_USTRINGPARAM(SC_UNONAME_ERRMESS)),
    sOnError(RTL_CONSTASCII_USTRINGPARAM("OnError")),
    sEventType(RTL_CONSTASCII_USTRINGPARAM("EventType")),
    sStarBasic(RTL_CONSTASCII_USTRINGPARAM("StarBasic")),
    sLibrary(RTL_CONSTASCII_USTRINGPARAM("Library")),
    sMacroName(RTL_CONSTASCII_USTRINGPARAM("MacroName"))
{
}

ScMyValidationsContainer::~ScMyValidationsContainer()
{
}

sal_Bool ScMyValidationsContainer::AddValidation(const uno::Any& aTempAny,
    sal_Int32& nValidationIndex)
{
    sal_Bool bAdded(sal_False);
    uno::Reference<beans::XPropertySet> xPropertySet;
    if (aTempAny >>= xPropertySet)
    {
        uno::Any aAny = xPropertySet->getPropertyValue(sERRMESS);
        ::rtl::OUString sErrorMessage;
        aAny >>= sErrorMessage;
        aAny = xPropertySet->getPropertyValue(sERRTITLE);
        ::rtl::OUString sErrorTitle;
        aAny >>= sErrorTitle;
        aAny = xPropertySet->getPropertyValue(sINPMESS);
        ::rtl::OUString sImputMessage;
        aAny >>= sImputMessage;
        aAny = xPropertySet->getPropertyValue(sINPTITLE);
        ::rtl::OUString sImputTitle;
        aAny >>= sImputTitle;
        aAny = xPropertySet->getPropertyValue(sSHOWERR);
        sal_Bool bShowErrorMessage;
        aAny >>= bShowErrorMessage;
        aAny = xPropertySet->getPropertyValue(sSHOWINP);
        sal_Bool bShowImputMessage;
        aAny >>= bShowImputMessage;
        aAny = xPropertySet->getPropertyValue(sTYPE);
        sheet::ValidationType aValidationType;
        aAny >>= aValidationType;
        if (bShowErrorMessage || bShowImputMessage || aValidationType != sheet::ValidationType_ANY ||
            sErrorMessage.getLength() || sErrorTitle.getLength() || sImputMessage.getLength() || sImputTitle.getLength())
        {
            ScMyValidation aValidation;
            aValidation.sErrorMessage = sErrorMessage;
            aValidation.sErrorTitle = sErrorTitle;
            aValidation.sImputMessage = sImputMessage;
            aValidation.sImputTitle = sImputTitle;
            aValidation.bShowErrorMessage = bShowErrorMessage;
            aValidation.bShowImputMessage = bShowImputMessage;
            aValidation.aValidationType = aValidationType;
            aAny = xPropertySet->getPropertyValue(sIGNOREBL);
            sal_Bool bIgnoreBlanks(sal_False);
            aAny >>= bIgnoreBlanks;
            aValidation.bIgnoreBlanks = bIgnoreBlanks;
            aAny = xPropertySet->getPropertyValue(sERRALSTY);
            aAny >>= aValidation.aAlertStyle;
            uno::Reference<sheet::XSheetCondition> xCondition(xPropertySet, uno::UNO_QUERY);
            if (xCondition.is())
            {
                aValidation.sFormula1 = xCondition->getFormula1();
                aValidation.sFormula2 = xCondition->getFormula2();
                aValidation.aOperator = xCondition->getOperator();
                aValidation.aBaseCell = xCondition->getSourcePosition();
            }
            //ScMyValidationRange aValidationRange;
            sal_Bool bEqualFound(sal_False);
            sal_Int32 i = 0;
            sal_Int32 nCount = aValidationVec.size();
            while (i < nCount && !bEqualFound)
            {
                bEqualFound = aValidationVec[i].IsEqual(aValidation);
                if (!bEqualFound)
                    i++;
            }
            if (bEqualFound)
                nValidationIndex = i;
            else
            {
                sal_Int32 nNameIndex = nCount + 1;
                ::rtl::OUString sCount = ::rtl::OUString::valueOf(nNameIndex);
                ::rtl::OUString sPrefix(RTL_CONSTASCII_USTRINGPARAM("val"));
                aValidation.sName += sPrefix;
                aValidation.sName += sCount;
                aValidationVec.push_back(aValidation);
                nValidationIndex = nCount;
                bAdded = sal_True;
            }
        }
    }
    return bAdded;
}

rtl::OUString ScMyValidationsContainer::GetCondition(const ScMyValidation& aValidation)
{
    ::rtl::OUString sCondition;
    if (aValidation.aValidationType != sheet::ValidationType_ANY)
    {
        switch (aValidation.aValidationType)
        {
            //case sheet::ValidationType_CUSTOM
            case sheet::ValidationType_DATE :
                sCondition += ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("cell-content-is-date()"));
            break;
            case sheet::ValidationType_DECIMAL :
                sCondition += ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("cell-content-is-decimal-number()"));
            break;
            //case sheet::ValidationType_LIST :
            case sheet::ValidationType_TEXT_LEN :
                if (aValidation.aOperator != sheet::ConditionOperator_BETWEEN &&
                    aValidation.aOperator != sheet::ConditionOperator_NOT_BETWEEN)
                    sCondition += ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("cell-content-text-length()"));
            break;
            case sheet::ValidationType_TIME :
                sCondition += ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("cell-content-is-time()"));
            break;
            case sheet::ValidationType_WHOLE :
                sCondition += ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("cell-content-is-whole-number()"));
            break;
        }
        if (aValidation.sFormula1.getLength() ||
            (aValidation.aOperator == sheet::ConditionOperator_BETWEEN &&
            aValidation.aOperator == sheet::ConditionOperator_NOT_BETWEEN &&
            aValidation.sFormula2.getLength()))
        {
            if (aValidation.aValidationType != sheet::ValidationType_TEXT_LEN)
                sCondition += ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM(" and "));
            if (aValidation.aOperator != sheet::ConditionOperator_BETWEEN &&
                aValidation.aOperator != sheet::ConditionOperator_NOT_BETWEEN)
            {
                if (aValidation.aValidationType != sheet::ValidationType_TEXT_LEN)
                    sCondition += ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("cell-content()"));
                switch (aValidation.aOperator)
                {
                    case sheet::ConditionOperator_EQUAL :
                        sCondition += ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("="));
                    break;
                    case sheet::ConditionOperator_GREATER :
                        sCondition += ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM(">"));
                    break;
                    case sheet::ConditionOperator_GREATER_EQUAL :
                        sCondition += ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM(">="));
                    break;
                    case sheet::ConditionOperator_LESS :
                        sCondition += ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("<"));
                    break;
                    case sheet::ConditionOperator_LESS_EQUAL :
                        sCondition += ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("<="));
                    break;
                    case sheet::ConditionOperator_NOT_EQUAL :
                        sCondition += ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("!="));
                    break;
                }
                sCondition += aValidation.sFormula1;
            }
            else
            {
                if (aValidation.aValidationType == sheet::ValidationType_TEXT_LEN)
                {
                    if (aValidation.aOperator == sheet::ConditionOperator_BETWEEN)
                        sCondition += ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("cell-content-text-length-is-between("));
                    else
                        sCondition += ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("cell-content-text-length-is-not-between("));
                }
                else
                {
                    if (aValidation.aOperator == sheet::ConditionOperator_BETWEEN)
                        sCondition += ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("cell-content-is-between("));
                    else
                        sCondition += ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("cell-content-is-not-between("));
                }
                sCondition += aValidation.sFormula1;
                sCondition += ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM(","));
                sCondition += aValidation.sFormula2;
                sCondition += ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM(")"));
            }
        }
        else
            if (aValidation.aValidationType == sheet::ValidationType_TEXT_LEN)
                sCondition = ::rtl::OUString();
    }
    return sCondition;
}

rtl::OUString ScMyValidationsContainer::GetBaseCellAddress(ScDocument* pDoc, const table::CellAddress& aCell)
{
    ::rtl::OUString sAddress;
    ScXMLConverter::GetStringFromAddress( sAddress, aCell, pDoc );
    return sAddress;
}

void ScMyValidationsContainer::WriteMessage(ScXMLExport& rExport,
    const ::rtl::OUString& sTitle, const ::rtl::OUString& sOUMessage,
    const sal_Bool bShowMessage, const sal_Bool bIsHelpMessage)
{
    if (sTitle.getLength())
        rExport.AddAttribute(XML_NAMESPACE_TABLE, XML_TITLE, sTitle);
    if (bShowMessage)
        rExport.AddAttribute(XML_NAMESPACE_TABLE, XML_DISPLAY, XML_TRUE);
    else
        rExport.AddAttribute(XML_NAMESPACE_TABLE, XML_DISPLAY, XML_FALSE);
    SvXMLElementExport* pMessage = NULL;
    if (bIsHelpMessage)
        pMessage = new SvXMLElementExport(rExport, XML_NAMESPACE_TABLE, XML_HELP_MESSAGE, sal_True, sal_True);
    else
        pMessage = new SvXMLElementExport(rExport, XML_NAMESPACE_TABLE, XML_ERROR_MESSAGE, sal_True, sal_True);
    if (sOUMessage.getLength())
    {
        sal_Int32 i = 0;
        ::rtl::OUStringBuffer sTemp;
        String sMessage(sOUMessage);
        ::rtl::OUString sText (sMessage.ConvertLineEnd(LINEEND_LF));
        sal_Bool bPrevCharWasSpace(sal_True);
        while(i < sText.getLength())
        {
            if ((sText[i] == '\n'))
            {
                SvXMLElementExport aElemP(rExport, XML_NAMESPACE_TEXT, XML_P, sal_True, sal_False);
                rExport.GetTextParagraphExport()->exportText(sTemp.makeStringAndClear(), bPrevCharWasSpace);
            }
            else
                sTemp.append(sText[i]);
            i++;
        }
        if (sTemp.getLength())
        {
            SvXMLElementExport aElemP(rExport, XML_NAMESPACE_TEXT, XML_P, sal_True, sal_False);
            rExport.GetTextParagraphExport()->exportText(sTemp.makeStringAndClear(), bPrevCharWasSpace);
        }
    }
    if (pMessage)
        delete pMessage;
}

void ScMyValidationsContainer::WriteValidations(ScXMLExport& rExport)
{
    if (aValidationVec.size())
    {
        SvXMLElementExport aElemVs(rExport, XML_NAMESPACE_TABLE, XML_CONTENT_VALIDATIONS, sal_True, sal_True);
        ScMyValidationVec::iterator aItr = aValidationVec.begin();
        while (aItr != aValidationVec.end())
        {
            rExport.AddAttribute(XML_NAMESPACE_TABLE, XML_NAME, aItr->sName);
            ::rtl::OUString sCondition = GetCondition(*aItr);
            if (sCondition.getLength())
            {
                rExport.AddAttribute(XML_NAMESPACE_TABLE, XML_CONDITION, sCondition);
                if (aItr->bIgnoreBlanks)
                    rExport.AddAttribute(XML_NAMESPACE_TABLE, XML_ALLOW_EMPTY_CELL, XML_FALSE);
                else
                    rExport.AddAttribute(XML_NAMESPACE_TABLE, XML_ALLOW_EMPTY_CELL, XML_TRUE);
            }
            rExport.AddAttribute(XML_NAMESPACE_TABLE, XML_BASE_CELL_ADDRESS, GetBaseCellAddress(rExport.GetDocument(), aItr->aBaseCell));
            SvXMLElementExport aElemV(rExport, XML_NAMESPACE_TABLE, XML_CONTENT_VALIDATION, sal_True, sal_True);
            if (aItr->bShowImputMessage || aItr->sImputMessage.getLength() || aItr->sImputTitle.getLength())
            {
                WriteMessage(rExport, aItr->sImputTitle, aItr->sImputMessage, aItr->bShowImputMessage, sal_True);
            }
            if (aItr->bShowErrorMessage || aItr->sErrorMessage.getLength() || aItr->sErrorTitle.getLength())
            {
                switch (aItr->aAlertStyle)
                {
                    case sheet::ValidationAlertStyle_INFO :
                    {
                        rExport.AddAttribute(XML_NAMESPACE_TABLE, XML_MESSAGE_TYPE, XML_INFORMATION);
                        WriteMessage(rExport, aItr->sErrorTitle, aItr->sErrorMessage, aItr->bShowErrorMessage, sal_False);
                    }
                    break;
                    case sheet::ValidationAlertStyle_WARNING :
                    {
                        rExport.AddAttribute(XML_NAMESPACE_TABLE, XML_MESSAGE_TYPE, XML_WARNING);
                        WriteMessage(rExport, aItr->sErrorTitle, aItr->sErrorMessage, aItr->bShowErrorMessage, sal_False);
                    }
                    break;
                    case sheet::ValidationAlertStyle_STOP :
                    {
                        rExport.AddAttribute(XML_NAMESPACE_TABLE, XML_MESSAGE_TYPE, XML_STOP);
                        WriteMessage(rExport, aItr->sErrorTitle, aItr->sErrorMessage, aItr->bShowErrorMessage, sal_False);
                    }
                    break;
                    case sheet::ValidationAlertStyle_MACRO :
                    {
                        rExport.AddAttribute(XML_NAMESPACE_TABLE, XML_NAME, aItr->sErrorTitle);
                        if (aItr->bShowErrorMessage)
                            rExport.AddAttribute(XML_NAMESPACE_TABLE, XML_EXECUTE, XML_TRUE);
                        else
                            rExport.AddAttribute(XML_NAMESPACE_TABLE, XML_EXECUTE, XML_FALSE);
                        SvXMLElementExport(rExport, XML_NAMESPACE_TABLE, XML_ERROR_MACRO, sal_True, sal_True);
                        {
                            uno::Sequence<beans::PropertyValue> aSeq(3);
                            beans::PropertyValue* pArr = aSeq.getArray();
                            pArr[0].Name = sEventType;
                            pArr[0].Value <<= sStarBasic;
                            pArr[1].Name = sLibrary;
                            pArr[1].Value <<= sEmptyString;
                            pArr[2].Name = sMacroName;
                            pArr[2].Value <<= aItr->sErrorTitle;

                            // 2) export the sequence
                            rExport.GetEventExport().ExportSingleEvent( aSeq, sOnError);
                        }
                    }
                    break;
                }
            }
            aItr++;
        }
    }
}

const ::rtl::OUString& ScMyValidationsContainer::GetValidationName(const sal_Int32 nIndex)
{
    DBG_ASSERT( static_cast<sal_uInt32>(nIndex) < aValidationVec.size(), "out of range" );
    return aValidationVec[nIndex].sName;
}

//==============================================================================

sal_Int32 ScMyDefaultStyles::GetStyleNameIndex(const ScFormatRangeStyles* pCellStyles,
    const sal_uInt16 nTable, const sal_Int32 nPos,
    const sal_Int32 i, const sal_Bool bRow, sal_Bool& bIsAutoStyle)
{
    if (bRow)
        return pCellStyles->GetStyleNameIndex(nTable, nPos, i,
                                bIsAutoStyle);
    else
        return pCellStyles->GetStyleNameIndex(nTable, i, nPos,
                                bIsAutoStyle);
}

void ScMyDefaultStyles::FillDefaultStyles(const sal_uInt16 nTable,
    const sal_Int32 nLastRow, const sal_Int32 nLastCol,
    const ScFormatRangeStyles* pCellStyles, ScDocument* pDoc,
    const sal_Bool bRow)
{
    if (pDoc)
    {
        sal_uInt16 nPos;
        sal_Int32 nLast;
        ScMyDefaultStyleList* pDefaults;
        if (bRow)
        {
            pDefaults = pRowDefaults;
            nLast = nLastRow;
        }
        else
        {
            pDefaults = pColDefaults;
            nLast = nLastCol;
        }
        sal_Bool bPrevAutoStyle;
        sal_Bool bIsAutoStyle;
        sal_Bool bResult;
        sal_Int32 nPrevIndex;
        sal_Int32 nIndex;
        sal_Int32 nRepeat(0);
        sal_Int32 nEmptyRepeat(0);
        for (sal_Int32 i = nLast; i >= 0; i--)
        {
            if (bRow)
                bResult = pDoc->GetRowDefault(nTable,
                    static_cast<sal_uInt16>(i), static_cast<sal_uInt16>(nLastCol), nPos);
            else
                bResult = pDoc->GetColDefault(nTable,
                    static_cast<sal_uInt16>(i), static_cast<sal_uInt16>(nLastRow), nPos);
            if (bResult)
            {
                nEmptyRepeat = 0;
                if (!nRepeat)
                {
                    nPrevIndex = GetStyleNameIndex(pCellStyles, nTable, static_cast<sal_Int32>(nPos), i,
                                                bRow, bPrevAutoStyle);
                    (*pDefaults)[i].nIndex = nPrevIndex;
                    (*pDefaults)[i].bIsAutoStyle = bPrevAutoStyle;
                    nRepeat = 1;
                }
                else
                {
                    nIndex = GetStyleNameIndex(pCellStyles, nTable, static_cast<sal_Int32>(nPos), i,
                                            bRow, bIsAutoStyle);
                    if ((nIndex != nPrevIndex) || (bIsAutoStyle != bPrevAutoStyle))
                    {
                        nRepeat = 1;
                        nPrevIndex = GetStyleNameIndex(pCellStyles, nTable, static_cast<sal_Int32>(nPos), i,
                                                bRow, bPrevAutoStyle);
                        (*pDefaults)[i].nIndex = nPrevIndex;
                        (*pDefaults)[i].bIsAutoStyle = bPrevAutoStyle;
                    }
                    else
                    {
                        (*pDefaults)[i].nIndex = nPrevIndex;
                        (*pDefaults)[i].bIsAutoStyle = bPrevAutoStyle;
                        nRepeat++;
                        if (nRepeat > 1)
                            (*pDefaults)[i].nRepeat = nRepeat;
                    }
                }
            }
            else
            {
                nRepeat = 0;
                if (!nEmptyRepeat)
                    nEmptyRepeat = 1;
                else
                {
                    nEmptyRepeat++;
                    if (nEmptyRepeat > 1)
                        (*pDefaults)[i].nRepeat = nEmptyRepeat;
                }
            }
        }
    }
}

void ScMyDefaultStyles::FillDefaultStyles(const sal_uInt16 nTable,
    const sal_Int32 nLastRow, const sal_Int32 nLastCol,
    const ScFormatRangeStyles* pCellStyles, ScDocument* pDoc)
{
    if (pRowDefaults)
        delete pRowDefaults;
    pRowDefaults = new ScMyDefaultStyleList(nLastRow + 1);
     FillDefaultStyles(nTable, nLastRow, nLastCol, pCellStyles, pDoc, sal_True);
    if (pColDefaults)
        delete pColDefaults;
    pColDefaults = new ScMyDefaultStyleList(nLastCol + 1);
     FillDefaultStyles(nTable, nLastRow, nLastCol, pCellStyles, pDoc, sal_False);
}

ScMyDefaultStyles::~ScMyDefaultStyles()
{
    if (pRowDefaults)
        delete pRowDefaults;
    if (pColDefaults)
        delete pColDefaults;
}

ScMyRowFormatRange::ScMyRowFormatRange()
    : nStartColumn(0),
    nRepeatColumns(0),
    nRepeatRows(0),
    nIndex(-1),
    nValidationIndex(-1),
    bIsAutoStyle(sal_True)
{
}

sal_Bool ScMyRowFormatRange::operator< (const ScMyRowFormatRange& rRange) const
{
    return (nStartColumn < rRange.nStartColumn);
}

ScRowFormatRanges::ScRowFormatRanges()
    : pRowDefaults(NULL),
    pColDefaults(NULL),
    aRowFormatRanges(),
    nSize(0)
{
}

ScRowFormatRanges::ScRowFormatRanges(const ScRowFormatRanges* pRanges)
    : pRowDefaults(pRanges->pRowDefaults),
    pColDefaults(pRanges->pColDefaults),
    aRowFormatRanges(pRanges->aRowFormatRanges),
    nSize(pRanges->nSize)
{
}

ScRowFormatRanges::~ScRowFormatRanges()
{
}

void ScRowFormatRanges::Clear()
{
    aRowFormatRanges.clear();
    nSize = 0;
}

void ScRowFormatRanges::AddRange(const sal_Int32 nPrevStartCol, const sal_Int32 nRepeat, const sal_Int32 nPrevIndex,
    const sal_Bool bPrevAutoStyle, const ScMyRowFormatRange& rFormatRange)
{
    sal_Int32 nIndex(-1);
    if ((nPrevIndex != rFormatRange.nIndex) ||
        (bPrevAutoStyle != rFormatRange.bIsAutoStyle))
        nIndex = rFormatRange.nIndex;

    sal_Bool bInserted(sal_False);
    if (!aRowFormatRanges.empty())
    {
        ScMyRowFormatRange* pRange = &aRowFormatRanges.back();
        if (pRange)
        {
            if ((nPrevStartCol == (pRange->nStartColumn + pRange->nRepeatColumns)) &&
                (pRange->bIsAutoStyle == rFormatRange.bIsAutoStyle) &&
                (pRange->nIndex == nIndex) &&
                (pRange->nValidationIndex == rFormatRange.nValidationIndex))
            {
                if (rFormatRange.nRepeatRows < pRange->nRepeatRows)
                    pRange->nRepeatRows = rFormatRange.nRepeatRows;
                pRange->nRepeatColumns += nRepeat;
                bInserted = sal_True;
            }
        }
    }
    if (!bInserted)
    {
        ScMyRowFormatRange aRange;
        aRange.nStartColumn = nPrevStartCol;
        aRange.nRepeatColumns = nRepeat;
        aRange.nRepeatRows = rFormatRange.nRepeatRows;
        aRange.nValidationIndex = rFormatRange.nValidationIndex;
        aRange.bIsAutoStyle = rFormatRange.bIsAutoStyle;
        aRange.nIndex = nIndex;
        aRowFormatRanges.push_back(aRange);
        nSize++;
    }
}

void ScRowFormatRanges::AddRange(ScMyRowFormatRange& rFormatRange,
    const sal_Int32 nRow)
{
    DBG_ASSERT(pRowDefaults, "no row defaults");
    DBG_ASSERT(pColDefaults, "no column defaults");
    sal_uInt32 nEnd (rFormatRange.nRepeatRows + nRow - 1);
    sal_Int32 nPrevIndex((*pRowDefaults)[nRow].nIndex);
    sal_Bool bPrevAutoStyle((*pRowDefaults)[nRow].bIsAutoStyle);
    sal_uInt32 i(nRow + 1);
    sal_Bool bReady(sal_False);
    while ((i < nEnd) && !bReady && (i < pRowDefaults->size()))
    {
        if ((nPrevIndex != (*pRowDefaults)[i].nIndex) ||
            (bPrevAutoStyle != (*pRowDefaults)[i].bIsAutoStyle))
            bReady = sal_True;
        else
            i += (*pRowDefaults)[i].nRepeat;
    }
    if (i > nEnd)
        i = nEnd;
    if (bReady)
        rFormatRange.nRepeatRows = i - nRow + 1;
    if (nPrevIndex == -1)
    {
        nPrevIndex = (*pColDefaults)[rFormatRange.nStartColumn].nIndex;
        bPrevAutoStyle = (*pColDefaults)[rFormatRange.nStartColumn].bIsAutoStyle;
        sal_uInt32 nPrevStartCol(rFormatRange.nStartColumn);
        sal_uInt32 nRepeat((*pColDefaults)[rFormatRange.nStartColumn].nRepeat);
        nEnd = rFormatRange.nStartColumn + rFormatRange.nRepeatColumns;
        for(i = nPrevStartCol + nRepeat; i < nEnd; i += (*pColDefaults)[i].nRepeat)
        {
            DBG_ASSERT(sal_uInt32(nPrevStartCol + nRepeat) <= nEnd, "something wents wrong");
            if ((nPrevIndex != (*pColDefaults)[i].nIndex) ||
                (bPrevAutoStyle != (*pColDefaults)[i].bIsAutoStyle))
            {
                AddRange(nPrevStartCol, nRepeat, nPrevIndex, bPrevAutoStyle, rFormatRange);
                nPrevStartCol = i;
                nRepeat = (*pColDefaults)[i].nRepeat;
                nPrevIndex = (*pColDefaults)[i].nIndex;
                bPrevAutoStyle = (*pColDefaults)[i].bIsAutoStyle;
            }
            else
                nRepeat += (*pColDefaults)[i].nRepeat;
        }
        if (sal_uInt32(nPrevStartCol + nRepeat) > nEnd)
            nRepeat = nEnd - nPrevStartCol;
        AddRange(nPrevStartCol, nRepeat, nPrevIndex, bPrevAutoStyle, rFormatRange);
    }
    else if ((nPrevIndex == rFormatRange.nIndex) &&
        (bPrevAutoStyle == rFormatRange.bIsAutoStyle))
    {
        rFormatRange.nIndex = -1;
        aRowFormatRanges.push_back(rFormatRange);
        nSize++;
    }
}

sal_Bool ScRowFormatRanges::GetNext(ScMyRowFormatRange& aFormatRange)
{
    ScMyRowFormatRangesList::iterator aItr = aRowFormatRanges.begin();
    if (aItr != aRowFormatRanges.end())
    {
        aFormatRange = (*aItr);
        aRowFormatRanges.erase(aItr);
        nSize--;
        return sal_True;
    }
    return sal_False;
}

sal_Int32 ScRowFormatRanges::GetMaxRows()
{
    ScMyRowFormatRangesList::iterator aItr = aRowFormatRanges.begin();
    sal_Int32 nMaxRows = MAXROW + 1;
    if (aItr != aRowFormatRanges.end())
        while (aItr != aRowFormatRanges.end())
        {
            if ((*aItr).nRepeatRows < nMaxRows)
                nMaxRows = (*aItr).nRepeatRows;
            aItr++;
        }
    else
        DBG_ERROR("no ranges found");
    return nMaxRows;
}

sal_Int32 ScRowFormatRanges::GetSize()
{
    return nSize;
}

void ScRowFormatRanges::Sort()
{
    aRowFormatRanges.sort();
}

// ============================================================================
ScMyFormatRange::ScMyFormatRange()
    : nStyleNameIndex(-1),
    nValidationIndex(-1),
    bIsAutoStyle(sal_True)
{
}

sal_Bool ScMyFormatRange::operator<(const ScMyFormatRange& rRange) const
{
    if (aRangeAddress.StartRow < rRange.aRangeAddress.StartRow)
        return sal_True;
    else
        if (aRangeAddress.StartRow == rRange.aRangeAddress.StartRow)
            return (aRangeAddress.StartColumn < rRange.aRangeAddress.StartColumn);
        else
            return sal_False;
}

ScFormatRangeStyles::ScFormatRangeStyles()
    : aTables(),
    aStyleNames(),
    aAutoStyleNames()
{
}

ScFormatRangeStyles::~ScFormatRangeStyles()
{
    ScMyOUStringVec::iterator i = aStyleNames.begin();
    while (i != aStyleNames.end())
    {
        delete *i;
        i++;
    }
    i = aAutoStyleNames.begin();
    while (i != aAutoStyleNames.end())
    {
        delete *i;
        i++;
    }
    ScMyFormatRangeListVec::iterator j = aTables.begin();
    while (j != aTables.end())
    {
        delete *j;
        j++;
    }
}

void ScFormatRangeStyles::AddNewTable(const sal_Int16 nTable)
{
    sal_Int16 nSize = aTables.size() - 1;
    if (nTable > nSize)
        for (sal_Int16 i = nSize; i < nTable; i++)
        {
            ScMyFormatRangeAddresses* aRangeAddresses = new ScMyFormatRangeAddresses;
            aTables.push_back(aRangeAddresses);
        }
}

sal_Bool ScFormatRangeStyles::AddStyleName(::rtl::OUString* rpString, sal_Int32& rIndex, const sal_Bool bIsAutoStyle)
{
    if (bIsAutoStyle)
    {
        aAutoStyleNames.push_back(rpString);
        rIndex = aAutoStyleNames.size() - 1;
        return sal_True;
    }
    else
    {
        sal_Int32 nCount = aStyleNames.size();
        sal_Bool bFound(sal_False);
        sal_Int32 i = nCount - 1;
        while ((i >= 0) && (!bFound))
        {
            if (aStyleNames.at(i)->equals(*rpString))
                bFound = sal_True;
            else
                i--;
        }
        if (bFound)
        {
            rIndex = i;
            return sal_False;
        }
        else
        {
            aStyleNames.push_back(rpString);
            rIndex = aStyleNames.size() - 1;
            return sal_True;
        }
    }
}

sal_Int32 ScFormatRangeStyles::GetIndexOfStyleName(const ::rtl::OUString& rString, const ::rtl::OUString& rPrefix, sal_Bool& bIsAutoStyle)
{
    sal_Int32 nPrefixLength = rPrefix.getLength();
    ::rtl::OUString sTemp = rString.copy(nPrefixLength);
    sal_Int32 nIndex = sTemp.toInt32();
    if (aAutoStyleNames.at(nIndex - 1)->equals(rString))
    {
        bIsAutoStyle = sal_True;
        return nIndex - 1;
    }
    else
    {
        sal_Int32 i = 0;
        sal_Bool bFound(sal_False);
        while (!bFound && static_cast<sal_uInt32>(i) < aStyleNames.size())
        {
            if (aStyleNames[i]->equals(rString))
                bFound = sal_True;
            else
                i++;
        }
        if (bFound)
        {
            bIsAutoStyle = sal_False;
            return i;
        }
        else
        {
            i = 0;
            while (!bFound && static_cast<sal_uInt32>(i) < aAutoStyleNames.size())
            {
                if (aAutoStyleNames[i]->equals(rString))
                    bFound = sal_True;
                else
                    i++;
            }
            if (bFound)
            {
                bIsAutoStyle = sal_True;
                return i;
            }
            else
                return -1;
        }
    }
}

sal_Int32 ScFormatRangeStyles::GetStyleNameIndex(const sal_uInt16 nTable,
    const sal_Int32 nColumn, const sal_Int32 nRow, sal_Bool& bIsAutoStyle) const
{
    DBG_ASSERT(static_cast<sal_uInt32>(nTable) < aTables.size(), "wrong table");
    ScMyFormatRangeAddresses* pFormatRanges = aTables[nTable];
    ScMyFormatRangeAddresses::iterator aItr = pFormatRanges->begin();
    while (aItr != pFormatRanges->end())
    {
        if (((*aItr).aRangeAddress.StartColumn <= nColumn) &&
            ((*aItr).aRangeAddress.EndColumn >= nColumn) &&
            ((*aItr).aRangeAddress.StartRow <= nRow) &&
            ((*aItr).aRangeAddress.EndRow >= nRow))
        {
            bIsAutoStyle = aItr->bIsAutoStyle;
            return (*aItr).nStyleNameIndex;
        }
        else
            aItr++;
    }
    return -1;
}

sal_Int32 ScFormatRangeStyles::GetStyleNameIndex(const sal_uInt16 nTable, const sal_Int32 nColumn, const sal_Int32 nRow,
    sal_Bool& bIsAutoStyle, sal_Int32& nValidationIndex, sal_Int32& nNumberFormat, const sal_Bool bRemoveRange)
{
    DBG_ASSERT(static_cast<sal_uInt32>(nTable) < aTables.size(), "wrong table");
    ScMyFormatRangeAddresses* pFormatRanges = aTables[nTable];
    ScMyFormatRangeAddresses::iterator aItr = pFormatRanges->begin();
    while (aItr != pFormatRanges->end())
    {
        if (((*aItr).aRangeAddress.StartColumn <= nColumn) &&
            ((*aItr).aRangeAddress.EndColumn >= nColumn) &&
            ((*aItr).aRangeAddress.StartRow <= nRow) &&
            ((*aItr).aRangeAddress.EndRow >= nRow))
        {
            bIsAutoStyle = aItr->bIsAutoStyle;
            nValidationIndex = aItr->nValidationIndex;
            nNumberFormat = aItr->nNumberFormat;
            if (((*pRowDefaults)[nRow].nIndex != -1))
            {
                if (((*pRowDefaults)[nRow].nIndex == (*aItr).nStyleNameIndex) &&
                    ((*pRowDefaults)[nRow].bIsAutoStyle == (*aItr).bIsAutoStyle))
                    return -1;
                else
                    return (*aItr).nStyleNameIndex;
            }
            else if (((*pColDefaults)[nColumn].nIndex != -1) &&
                ((*pColDefaults)[nColumn].nIndex == (*aItr).nStyleNameIndex) &&
                ((*pColDefaults)[nColumn].bIsAutoStyle == (*aItr).bIsAutoStyle))
                return -1;
            else
                return (*aItr).nStyleNameIndex;
        }
        else
        {
            if (bRemoveRange && (*aItr).aRangeAddress.EndRow < nRow)
                aItr = pFormatRanges->erase(aItr);
            else
                aItr++;
        }
    }
    return -1;
}

void ScFormatRangeStyles::GetFormatRanges(const sal_Int32 nStartColumn, const sal_Int32 nEndColumn, const sal_Int32 nRow,
                    const sal_Int16 nTable, ScRowFormatRanges* pRowFormatRanges)
{
    sal_Int32 nTotalColumns = nEndColumn - nStartColumn + 1;
    DBG_ASSERT(static_cast<sal_uInt32>(nTable) < aTables.size(), "wrong table");
    ScMyFormatRangeAddresses* pFormatRanges = aTables[nTable];
    ScMyFormatRangeAddresses::iterator aItr = pFormatRanges->begin();
    sal_Int32 nColumns = 0;
    while (aItr != pFormatRanges->end() && nColumns < nTotalColumns)
    {
#if OSL_DEBUG_LEVEL > 1
        table::CellRangeAddress aTempRangeAddress = (*aItr).aRangeAddress;
#endif
        if (((*aItr).aRangeAddress.StartRow <= nRow) &&
            ((*aItr).aRangeAddress.EndRow >= nRow))
        {
            if ((((*aItr).aRangeAddress.StartColumn <= nStartColumn) &&
                ((*aItr).aRangeAddress.EndColumn >= nStartColumn)) ||
                (((*aItr).aRangeAddress.StartColumn <= nEndColumn) &&
                ((*aItr).aRangeAddress.EndColumn >= nEndColumn)) ||
                (((*aItr).aRangeAddress.StartColumn >= nStartColumn) &&
                ((*aItr).aRangeAddress.EndColumn <= nEndColumn)))
            {
                ScMyRowFormatRange aRange;
                aRange.nIndex = aItr->nStyleNameIndex;
                aRange.nValidationIndex = aItr->nValidationIndex;
                aRange.bIsAutoStyle = aItr->bIsAutoStyle;
                if ((aItr->aRangeAddress.StartColumn < nStartColumn) &&
                    (aItr->aRangeAddress.EndColumn >= nStartColumn))
                {
                    if (aItr->aRangeAddress.EndColumn >= nEndColumn)
                        aRange.nRepeatColumns = nTotalColumns;
                    else
                        aRange.nRepeatColumns = aItr->aRangeAddress.EndColumn - nStartColumn + 1;
                    aRange.nStartColumn = nStartColumn;
                }
                else if ((aItr->aRangeAddress.StartColumn >= nStartColumn) &&
                    (aItr->aRangeAddress.EndColumn <= nEndColumn))
                {
                    aRange.nRepeatColumns = aItr->aRangeAddress.EndColumn - aItr->aRangeAddress.StartColumn + 1;
                    aRange.nStartColumn = aItr->aRangeAddress.StartColumn;
                }
                else if ((aItr->aRangeAddress.StartColumn >= nStartColumn) &&
                    (aItr->aRangeAddress.StartColumn <= nEndColumn) &&
                    (aItr->aRangeAddress.EndColumn > nEndColumn))
                {
                    aRange.nRepeatColumns = nEndColumn - aItr->aRangeAddress.StartColumn + 1;
                    aRange.nStartColumn = aItr->aRangeAddress.StartColumn;
                }
                aRange.nRepeatRows = aItr->aRangeAddress.EndRow - nRow + 1;
                pRowFormatRanges->AddRange(aRange, nRow);
                nColumns += aRange.nRepeatColumns;
            }
            aItr++;
        }
        else
            if(aItr->aRangeAddress.EndRow < nRow)
                aItr = pFormatRanges->erase(aItr);
            else
                aItr++;
    }
    pRowFormatRanges->Sort();
}

void ScFormatRangeStyles::AddRangeStyleName(const table::CellRangeAddress aCellRangeAddress,
    const sal_Int32 nStringIndex, const sal_Bool bIsAutoStyle, const sal_Int32 nValidationIndex,
    const sal_Int32 nNumberFormat)
{
    ScMyFormatRange aFormatRange;
    aFormatRange.aRangeAddress = aCellRangeAddress;
    aFormatRange.nStyleNameIndex = nStringIndex;
    aFormatRange.nValidationIndex = nValidationIndex;
    aFormatRange.nNumberFormat = nNumberFormat;
    aFormatRange.bIsAutoStyle = bIsAutoStyle;
    DBG_ASSERT(static_cast<sal_uInt32>(aCellRangeAddress.Sheet) < aTables.size(), "wrong table");
    ScMyFormatRangeAddresses* pFormatRanges = aTables[aCellRangeAddress.Sheet];
    pFormatRanges->push_back(aFormatRange);
}

rtl::OUString* ScFormatRangeStyles::GetStyleNameByIndex(const sal_Int32 nIndex, const sal_Bool bIsAutoStyle)
{
    if (bIsAutoStyle)
        return aAutoStyleNames[nIndex];
    else
        return aStyleNames[nIndex];
}

void ScFormatRangeStyles::Sort()
{
    sal_Int16 nTables = aTables.size();
    for (sal_Int16 i = 0; i < nTables; i++)
        if (!aTables[i]->empty())
            aTables[i]->sort();
}

//===========================================================================

ScColumnRowStylesBase::ScColumnRowStylesBase()
    : aStyleNames()
{
}

ScColumnRowStylesBase::~ScColumnRowStylesBase()
{
    ScMyOUStringVec::iterator i = aStyleNames.begin();
    while (i != aStyleNames.end())
    {
        delete *i;
        i++;
    }
}

sal_Int32 ScColumnRowStylesBase::AddStyleName(::rtl::OUString* pString)
{
    aStyleNames.push_back(pString);
    return aStyleNames.size() - 1;
}

sal_Int32 ScColumnRowStylesBase::GetIndexOfStyleName(const ::rtl::OUString& rString, const ::rtl::OUString& rPrefix)
{
    sal_Int32 nPrefixLength = rPrefix.getLength();
    ::rtl::OUString sTemp = rString.copy(nPrefixLength);
    sal_Int32 nIndex = sTemp.toInt32();
    if (aStyleNames.at(nIndex - 1)->equals(rString))
        return nIndex - 1;
    else
    {
        sal_Int32 i = 0;
        sal_Bool bFound(sal_False);
        while (!bFound && static_cast<sal_uInt32>(i) < aStyleNames.size())
        {
            if (aStyleNames.at(i)->equals(rString))
                bFound = sal_True;
            else
                i++;
        }
        if (bFound)
            return i;
        else
            return -1;
    }
}

rtl::OUString* ScColumnRowStylesBase::GetStyleNameByIndex(const sal_Int32 nIndex)
{
    return aStyleNames[nIndex];
}

//===========================================================================

ScColumnStyles::ScColumnStyles()
    : ScColumnRowStylesBase(),
    aTables()
{
}

ScColumnStyles::~ScColumnStyles()
{
}

void ScColumnStyles::AddNewTable(const sal_Int16 nTable, const sal_Int32 nFields)
{
    sal_Int16 nSize = aTables.size() - 1;
    if (nTable > nSize)
        for (sal_Int32 i = nSize; i < nTable; i++)
        {
            ScMyColumnStyleVec aFieldsVec(nFields + 1, ScColumnStyle());
            aTables.push_back(aFieldsVec);
        }
}

sal_Int32 ScColumnStyles::GetStyleNameIndex(const sal_Int16 nTable, const sal_Int32 nField,
    sal_Bool& bIsVisible)
{
    DBG_ASSERT(static_cast<sal_uInt32>(nTable) < aTables.size(), "wrong table");
    if (static_cast<sal_uInt32>(nField) < aTables[nTable].size())
    {
        bIsVisible = aTables[nTable][nField].bIsVisible;
        return aTables[nTable][nField].nIndex;
    }
    else
    {
        bIsVisible = aTables[nTable][aTables[nTable].size() - 1].bIsVisible;
        return aTables[nTable][aTables[nTable].size() - 1].nIndex;
    }
}

void ScColumnStyles::AddFieldStyleName(const sal_Int16 nTable, const sal_Int32 nField,
    const sal_Int32 nStringIndex, const sal_Bool bIsVisible)
{
    DBG_ASSERT(static_cast<sal_uInt32>(nTable) < aTables.size(), "wrong table");
    DBG_ASSERT(aTables[nTable].size() >= static_cast<sal_uInt32>(nField), "wrong field");
    ScColumnStyle aStyle;
    aStyle.nIndex = nStringIndex;
    aStyle.bIsVisible = bIsVisible;
    if (aTables[nTable].size() == static_cast<sal_uInt32>(nField))
        aTables[nTable].push_back(aStyle);
    aTables[nTable][nField] = aStyle;
}

rtl::OUString* ScColumnStyles::GetStyleName(const sal_Int16 nTable, const sal_Int32 nField)
{
    sal_Bool bTemp;
    return GetStyleNameByIndex(GetStyleNameIndex(nTable, nField, bTemp));
}

//===========================================================================

ScRowStyles::ScRowStyles()
    : ScColumnRowStylesBase(),
    aTables()
{
}

ScRowStyles::~ScRowStyles()
{
}

void ScRowStyles::AddNewTable(const sal_Int16 nTable, const sal_Int32 nFields)
{
    sal_Int16 nSize = aTables.size() - 1;
    if (nTable > nSize)
        for (sal_Int32 i = nSize; i < nTable; i++)
        {
            ScMysalInt32Vec aFieldsVec(nFields + 1, -1);
            aTables.push_back(aFieldsVec);
        }
}

sal_Int32 ScRowStyles::GetStyleNameIndex(const sal_Int16 nTable, const sal_Int32 nField)
{
    DBG_ASSERT(static_cast<sal_uInt32>(nTable) < aTables.size(), "wrong table");
    if (static_cast<sal_uInt32>(nField) < aTables[nTable].size())
        return aTables[nTable][nField];
    else
        return aTables[nTable][aTables[nTable].size() - 1];
}

void ScRowStyles::AddFieldStyleName(const sal_Int16 nTable, const sal_Int32 nField,
    const sal_Int32 nStringIndex)
{
    DBG_ASSERT(static_cast<sal_uInt32>(nTable) < aTables.size(), "wrong table");
    DBG_ASSERT(aTables[nTable].size() >= static_cast<sal_uInt32>(nField), "wrong field");
    if (aTables[nTable].size() == static_cast<sal_uInt32>(nField))
        aTables[nTable].push_back(nStringIndex);
    aTables[nTable][nField] = nStringIndex;
}

rtl::OUString* ScRowStyles::GetStyleName(const sal_Int16 nTable, const sal_Int32 nField)
{
    return GetStyleNameByIndex(GetStyleNameIndex(nTable, nField));
}
}
