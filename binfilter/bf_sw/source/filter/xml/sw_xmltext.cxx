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

#include <bf_xmloff/xmlnmspe.hxx>
#include "xmlimp.hxx"
namespace binfilter {

using namespace ::com::sun::star;
using namespace ::com::sun::star::uno;
using namespace ::com::sun::star::text;

using rtl::OUString;

// ---------------------------------------------------------------------

class SwXMLBodyContext_Impl : public SvXMLImportContext
{
    SwXMLImport& GetSwImport() { return (SwXMLImport&)GetImport(); }

public:

    SwXMLBodyContext_Impl( SwXMLImport& rInImport, sal_uInt16 nPrfx,
                             const OUString& rLName );
    virtual ~SwXMLBodyContext_Impl();

    virtual SvXMLImportContext *CreateChildContext(
            sal_uInt16 nInPrefix, const OUString& rLocalName,
            const Reference< xml::sax::XAttributeList > & xAttrList );

    virtual void EndElement();
};

SwXMLBodyContext_Impl::SwXMLBodyContext_Impl( SwXMLImport& rInImport,
                                              sal_uInt16 nPrfx,
                                                   const OUString& rLName ) :
    SvXMLImportContext( rInImport, nPrfx, rLName )
{
}

SwXMLBodyContext_Impl::~SwXMLBodyContext_Impl()
{
}

SvXMLImportContext *SwXMLBodyContext_Impl::CreateChildContext(
        sal_uInt16 nInPrefix, const OUString& rLocalName,
        const Reference< xml::sax::XAttributeList > & xAttrList )
{
    SvXMLImportContext *pContext = 0;

    pContext = GetSwImport().GetTextImport()->CreateTextChildContext(
            GetImport(), nInPrefix, rLocalName, xAttrList,
               XML_TEXT_TYPE_BODY );
    if( !pContext )
        pContext = new SvXMLImportContext( GetImport(), nInPrefix, rLocalName );

    return pContext;
}

void SwXMLBodyContext_Impl::EndElement()
{
    /* #108146# Code moved to SwXMLOmport::endDocument */
    GetImport().GetTextImport()->SetOutlineStyles();
}

SvXMLImportContext *SwXMLImport::CreateBodyContext(
                                       const OUString& rLocalName )
{
    SvXMLImportContext *pContext = 0;

    if( !IsStylesOnlyMode() )
         pContext = new SwXMLBodyContext_Impl( *this, XML_NAMESPACE_OFFICE,
                                              rLocalName );
    else
        pContext = new SvXMLImportContext( *this, XML_NAMESPACE_OFFICE,
                                           rLocalName );

    return pContext;
}
}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
