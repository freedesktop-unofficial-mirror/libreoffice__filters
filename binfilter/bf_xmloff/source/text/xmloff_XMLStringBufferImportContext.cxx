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

#include "XMLStringBufferImportContext.hxx"

#include "xmltoken.hxx"

#include "xmlnmspe.hxx"
namespace binfilter {


using ::rtl::OUString;
using ::rtl::OUStringBuffer;
using ::com::sun::star::uno::Reference;
using ::com::sun::star::xml::sax::XAttributeList;
using ::binfilter::xmloff::token::IsXMLToken;
using ::binfilter::xmloff::token::XML_P;


TYPEINIT1(XMLStringBufferImportContext, SvXMLImportContext);

XMLStringBufferImportContext::XMLStringBufferImportContext(
    SvXMLImport& rInImport, 
    sal_uInt16 nInPrefix,
    const OUString& sLocalName,
    OUStringBuffer& rBuffer) :
    SvXMLImportContext(rInImport, nInPrefix, sLocalName),
    rTextBuffer(rBuffer)
{
}

XMLStringBufferImportContext::~XMLStringBufferImportContext()
{
}

SvXMLImportContext *XMLStringBufferImportContext::CreateChildContext(
    USHORT nInPrefix,
    const OUString& rLocalName,
    const Reference<XAttributeList> & /*xAttrList*/)
{
    return new XMLStringBufferImportContext(GetImport(), nInPrefix, 
                                            rLocalName, rTextBuffer);
}

void XMLStringBufferImportContext::Characters( 
    const OUString& rChars )
{
    rTextBuffer.append(rChars);
}

void XMLStringBufferImportContext::EndElement()
{
    // add return for paragraph elements
    if ( (XML_NAMESPACE_TEXT == GetPrefix()) &&
         (IsXMLToken(GetLocalName(), XML_P))    )
    {
        rTextBuffer.append(sal_Unicode(0x0a));
    }
}

}//end of namespace binfilter

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
