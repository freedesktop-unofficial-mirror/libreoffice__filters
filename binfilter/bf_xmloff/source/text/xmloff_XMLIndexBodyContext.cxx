/*************************************************************************
 *
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER.
 * 
 * Copyright 2008 by Sun Microsystems, Inc.
 *
 * OpenOffice.org - a multi-platform office productivity suite
 *
 * $RCSfile: xmloff_XMLIndexBodyContext.cxx,v $
 * $Revision: 1.5 $
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


#ifndef _XMLOFF_XMLINDEXBODYCONTEXT_HXX_
#include "XMLIndexBodyContext.hxx"
#endif


#ifndef _XMLOFF_XMLIMP_HXX
#include "xmlimp.hxx"
#endif



namespace binfilter {

using ::rtl::OUString;
using ::com::sun::star::uno::Reference;
using ::com::sun::star::xml::sax::XAttributeList;


TYPEINIT1( XMLIndexBodyContext, SvXMLImportContext);

XMLIndexBodyContext::XMLIndexBodyContext(
    SvXMLImport& rImport, 
    sal_uInt16 nPrfx,
    const ::rtl::OUString& rLocalName ) :
        SvXMLImportContext(rImport, nPrfx, rLocalName),
        bHasContent(sal_False)
{
}

XMLIndexBodyContext::~XMLIndexBodyContext()
{
}

SvXMLImportContext* XMLIndexBodyContext::CreateChildContext( 
    sal_uInt16 nPrefix,
    const OUString& rLocalName,
    const Reference<XAttributeList> & xAttrList)
{
    SvXMLImportContext* pContext = NULL;

    // return text content (if possible)
    pContext = GetImport().GetTextImport()->CreateTextChildContext(
        GetImport(), nPrefix, rLocalName, xAttrList, XML_TEXT_TYPE_SECTION );
    if (NULL == pContext)
    {
        pContext = new SvXMLImportContext( GetImport(), nPrefix, rLocalName );
    }
    else
        bHasContent = sal_True;

    return pContext;
}
}//end of namespace binfilter
