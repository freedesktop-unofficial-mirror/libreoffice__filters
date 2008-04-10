/*************************************************************************
 *
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER.
 * 
 * Copyright 2008 by Sun Microsystems, Inc.
 *
 * OpenOffice.org - a multi-platform office productivity suite
 *
 * $RCSfile: XMLIndexTOCStylesContext.hxx,v $
 * $Revision: 1.3 $
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

#ifndef _XMLOFF_XMLINDEXTOCSTYLESCONTEXT_HXX_
#define _XMLOFF_XMLINDEXTOCSTYLESCONTEXT_HXX_

#ifndef _XMLOFF_XMLICTXT_HXX 
#include "xmlictxt.hxx"
#endif

#ifndef _COM_SUN_STAR_UNO_REFERENCE_H_ 
#include <com/sun/star/uno/Reference.h>
#endif

#ifndef __SGI_STL_VECTOR
#include <vector>
#endif


namespace com { namespace sun { namespace star {
    namespace xml { namespace sax { class XAttributeList; } }
    namespace beans { class XPropertySet; }
} } }
namespace rtl {	class OUString; }
namespace binfilter {


/**
 * Import <test:index-source-styles> elements and their children
 *
 * (Small hackery here: Because there's only one type of child
 * elements with only one interesting attribute, we completely handle
 * them inside the CreateChildContext method, rather than creating a
 * new import class for them. This must be changed if children become
 * more complex in future versions.)
 */
class XMLIndexTOCStylesContext : public SvXMLImportContext
{
    const ::rtl::OUString sLevelParagraphStyles;

    /// XPropertySet of the index
    ::com::sun::star::uno::Reference<
        ::com::sun::star::beans::XPropertySet> & rTOCPropertySet;

    /// style names for this level
    ::std::vector< ::rtl::OUString > aStyleNames;

    /// outline level
    sal_Int32 nOutlineLevel;

public:

    TYPEINFO();

    XMLIndexTOCStylesContext(
        SvXMLImport& rImport, 
        ::com::sun::star::uno::Reference<
            ::com::sun::star::beans::XPropertySet> & rPropSet,
        sal_uInt16 nPrfx,
        const ::rtl::OUString& rLocalName );

    ~XMLIndexTOCStylesContext();

protected:

    virtual void StartElement(
        const ::com::sun::star::uno::Reference< 
            ::com::sun::star::xml::sax::XAttributeList> & xAttrList);

    virtual void EndElement();

    virtual SvXMLImportContext *CreateChildContext( 
        sal_uInt16 nPrefix,
        const ::rtl::OUString& rLocalName,
        const ::com::sun::star::uno::Reference< 
            ::com::sun::star::xml::sax::XAttributeList> & xAttrList );
};

}//end of namespace binfilter
#endif
