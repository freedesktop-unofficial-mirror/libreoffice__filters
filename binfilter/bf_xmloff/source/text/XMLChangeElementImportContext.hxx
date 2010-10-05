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


#ifndef _XMLOFF_XMLCHANGEELEMENTIMPORTCONTEXT_HXX
#define _XMLOFF_XMLCHANGEELEMENTIMPORTCONTEXT_HXX

#include "xmlictxt.hxx"

#include <com/sun/star/uno/Reference.h>


namespace com { namespace sun { namespace star {
    namespace xml { namespace sax {
        class XAttributeList;
    } }
} } }
namespace rtl {
    class OUString;
}
namespace binfilter {

class XMLChangedRegionImportContext;



/**
 * Import <text:deletion> and <text:insertion> elements contained in a 
 * <text:changed-region> element.
 */
class XMLChangeElementImportContext : public SvXMLImportContext
{
    sal_Bool bAcceptContent;
    XMLChangedRegionImportContext& rChangedRegion;

public:

    TYPEINFO();

    XMLChangeElementImportContext(
        SvXMLImport& rImport,
        sal_uInt16 nPrefix,
        const ::rtl::OUString& rLocalName,
        /// accept text content (paragraphs) in element as redline content?
        sal_Bool bAcceptContent,
        /// context of enclosing <text:changed-region> element
        XMLChangedRegionImportContext& rParent);

    virtual SvXMLImportContext* CreateChildContext(
        sal_uInt16 nPrefix,
        const ::rtl::OUString& rLocalName,
        const ::com::sun::star::uno::Reference<
            ::com::sun::star::xml::sax::XAttributeList> & xAttrList);

    // #107848#
    // Start- and EndElement are needed here to set the inside_deleted_section
    // flag at the corresponding TextImportHelper
    virtual void StartElement( const ::com::sun::star::uno::Reference< ::com::sun::star::xml::sax::XAttributeList >& xAttrList );

    // #107848#
    virtual void EndElement();
};

}//end of namespace binfilter
#endif
