/*************************************************************************
 *
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER.
 * 
 * Copyright 2008 by Sun Microsystems, Inc.
 *
 * OpenOffice.org - a multi-platform office productivity suite
 *
 * $RCSfile: XMLIndexUserSourceContext.hxx,v $
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

#ifndef _XMLOFF_XMLINDEXUSERSOURCECONTEXT_HXX_
#define _XMLOFF_XMLINDEXUSERSOURCECONTEXT_HXX_

#ifndef _XMLOFF_XMLINDEXSOURCEBASECONTEXT_HXX_
#include "XMLIndexSourceBaseContext.hxx"
#endif

#ifndef _COM_SUN_STAR_UNO_REFERENCE_H_ 
#include <com/sun/star/uno/Reference.h>
#endif


namespace com { namespace sun { namespace star {
    namespace xml { namespace sax { class XAttributeList; } }
    namespace beans { class XPropertySet; }
} } }
namespace rtl {	class OUString; }
namespace binfilter {


/**
 * Import user defined index source element
 */
class XMLIndexUserSourceContext : public XMLIndexSourceBaseContext
{
    const ::rtl::OUString sCreateFromEmbeddedObjects;
    const ::rtl::OUString sCreateFromGraphicObjects; 
    const ::rtl::OUString sCreateFromMarks;
    const ::rtl::OUString sCreateFromTables;
    const ::rtl::OUString sCreateFromTextFrames;
    const ::rtl::OUString sUseLevelFromSource;
    const ::rtl::OUString sCreateFromLevelParagraphStyles;
    const ::rtl::OUString sUserIndexName;

    sal_Bool bUseObjects;
    sal_Bool bUseGraphic; 
    sal_Bool bUseMarks;
    sal_Bool bUseTables;
    sal_Bool bUseFrames;
    sal_Bool bUseLevelFromSource;
    sal_Bool bUseLevelParagraphStyles;
    ::rtl::OUString sIndexName;

public:

    TYPEINFO();

    XMLIndexUserSourceContext(
        SvXMLImport& rImport, 
        sal_uInt16 nPrfx,
        const ::rtl::OUString& rLocalName,
        ::com::sun::star::uno::Reference< 
            ::com::sun::star::beans::XPropertySet> & rPropSet);

    ~XMLIndexUserSourceContext();

protected:

    virtual void ProcessAttribute(
        enum IndexSourceParamEnum eParam, 
        const ::rtl::OUString& rValue);

    virtual void EndElement();

    virtual SvXMLImportContext* CreateChildContext( 
        sal_uInt16 nPrefix,
        const ::rtl::OUString& rLocalName,
        const ::com::sun::star::uno::Reference< 
            ::com::sun::star::xml::sax::XAttributeList> & xAttrList );
};

}//end of namespace binfilter
#endif
