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

// INCLUDE ---------------------------------------------------------------

#include "XMLTextPContext.hxx"
#include "xmlimprt.hxx"
#include "xmlcelli.hxx"

#include <bf_xmloff/xmlnmspe.hxx>
#include <bf_xmloff/nmspmap.hxx>

namespace binfilter {

using namespace ::com::sun::star;
using namespace xmloff::token;

class ScXMLTextTContext : public SvXMLImportContext
{
    const ScXMLImport& GetScImport() const { return (const ScXMLImport&)GetImport(); }
    ScXMLImport& GetScImport() { return (ScXMLImport&)GetImport(); }
public:
    ScXMLTextTContext( ScXMLImport& rImport, USHORT nPrfx,
                        const ::rtl::OUString& rLName,
                        const ::com::sun::star::uno::Reference<
                                        ::com::sun::star::xml::sax::XAttributeList>& xAttrList,
                        ScXMLTextPContext* pTextPContext);

    virtual ~ScXMLTextTContext();
};


ScXMLTextTContext::ScXMLTextTContext( ScXMLImport& rInImport,
                                      USHORT nPrfx,
                                      const ::rtl::OUString& rLName,
                                      const ::com::sun::star::uno::Reference<
                                      ::com::sun::star::xml::sax::XAttributeList>& xAttrList,
                                      ScXMLTextPContext* pTextPContext) :
    SvXMLImportContext( rInImport, nPrfx, rLName )
{
    if (pTextPContext)
    {
        sal_Int16 nAttrCount = xAttrList.is() ? xAttrList->getLength() : 0;
        ::rtl::OUString aLclLocalName;
        ::rtl::OUString sValue;
        sal_Int32 nCount(1);
        for( sal_Int16 i=0; i < nAttrCount; i++ )
        {
            sal_uInt16 nLclPrefix = GetScImport().GetNamespaceMap().GetKeyByAttrName(
                                                xAttrList->getNameByIndex( i ), &aLclLocalName );
            sValue = xAttrList->getValueByIndex( i );

            if ((nLclPrefix == XML_NAMESPACE_TEXT) && IsXMLToken(aLclLocalName, XML_C))
                nCount = sValue.toInt32();
        }
        pTextPContext->AddSpaces(nCount);
    }
}

ScXMLTextTContext::~ScXMLTextTContext()
{
}

//------------------------------------------------------------------

ScXMLTextPContext::ScXMLTextPContext( ScXMLImport& rInImport,
                                      USHORT nPrfx,
                                      const ::rtl::OUString& rLName,
                                      const ::com::sun::star::uno::Reference<
                                      ::com::sun::star::xml::sax::XAttributeList>& xTempAttrList,
                                      ScXMLTableRowCellContext* pTempCellContext) :
    SvXMLImportContext( rInImport, nPrfx, rLName ),
    xAttrList(xTempAttrList),
    pTextPContext(NULL),
    pCellContext(pTempCellContext),
    sLName(rLName),
    sOUText(),
    nPrefix(nPrfx),
    bIsOwn(sal_True)
{
    // here are no attributes
}

ScXMLTextPContext::~ScXMLTextPContext()
{
    if (pTextPContext)
        delete pTextPContext;
}

void ScXMLTextPContext::AddSpaces(sal_Int32 nSpaceCount)
{
    sal_Char* pChars = new sal_Char[nSpaceCount];
    memset(pChars, ' ', nSpaceCount);
    sOUText.appendAscii(pChars, nSpaceCount);
}

SvXMLImportContext *ScXMLTextPContext::CreateChildContext( USHORT nTempPrefix,
                                            const ::rtl::OUString& rLName,
                                            const ::com::sun::star::uno::Reference<
                                          ::com::sun::star::xml::sax::XAttributeList>& xTempAttrList )
{
    SvXMLImportContext *pContext = NULL;
    if (!pTextPContext &&
        (nTempPrefix == XML_NAMESPACE_TEXT) &&
        IsXMLToken(rLName, XML_S))
        pContext = new ScXMLTextTContext( GetScImport(), nTempPrefix, rLName, xTempAttrList, this);
    else
    {
        if (!pTextPContext)
        {
            pCellContext->SetCursorOnTextImport(sOUText.makeStringAndClear());
            pTextPContext = GetScImport().GetTextImport()->CreateTextChildContext(
                                    GetScImport(), nPrefix, sLName, xAttrList);
        }
        if (pTextPContext)
            pContext = pTextPContext->CreateChildContext(nTempPrefix, rLName, xTempAttrList);
    }

    if( !pContext )
        pContext = new SvXMLImportContext( GetScImport(), nTempPrefix, rLName );

    return pContext;
}

void ScXMLTextPContext::Characters( const ::rtl::OUString& rChars )
{
    if (!pTextPContext)
        sOUText.append(rChars);
    else
        pTextPContext->Characters(rChars);
}

void ScXMLTextPContext::EndElement()
{
    if (!pTextPContext)
        pCellContext->SetString(sOUText.makeStringAndClear());
//		GetScImport().GetTextImport()->GetCursor()->setString(sOUText.makeStringAndClear());
    else
    {
        pTextPContext->EndElement();
        GetScImport().SetRemoveLastChar(sal_True);
    }
}

}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
