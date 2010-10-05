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


#ifndef _XMLOFF_XMLCHANGEDREGIONIMPORTCONTEXT_HXX
#define _XMLOFF_XMLCHANGEDREGIONIMPORTCONTEXT_HXX

#include "xmlictxt.hxx"

#include <com/sun/star/uno/Reference.h>


namespace com { namespace sun { namespace star {
    namespace text {
        class XTextCursor;
    }
    namespace xml { namespace sax {
        class XAttributeList;
    } }
} } }
namespace rtl {
    class OUString;
}
namespace binfilter {


class XMLChangedRegionImportContext : public SvXMLImportContext
{
    const ::rtl::OUString sEmpty;

    /// if we replace the current XTextCursor/XText by the ones for
    /// the redline, we remeber the old cursor here.
    ::com::sun::star::uno::Reference<
        ::com::sun::star::text::XTextCursor> xOldCursor;

    ::rtl::OUString sID;        /// redline-ID

    sal_Bool bMergeLastPara;    /// merge-last-paragraph flag

public:
    
    TYPEINFO();

    XMLChangedRegionImportContext(
        SvXMLImport& rImport,
        sal_uInt16 nPrefix,
        const ::rtl::OUString& rLocalName);

    ~XMLChangedRegionImportContext();

    virtual void StartElement(
        const ::com::sun::star::uno::Reference<
            ::com::sun::star::xml::sax::XAttributeList> & xAttrList);

    virtual SvXMLImportContext* CreateChildContext(
        sal_uInt16 nPrefix,
        const ::rtl::OUString& rLocalName,
         const ::com::sun::star::uno::Reference<
            ::com::sun::star::xml::sax::XAttributeList> & xAttrList);

    virtual void EndElement();


    /// change info: To be called from change-info context
    void SetChangeInfo(const ::rtl::OUString& rType,
                       const ::rtl::OUString& rAuthor,
                       const ::rtl::OUString& rComment,
                       const ::rtl::OUString& rDate);

    /// create redline XText/XTextCursor on demand and register with
    /// XMLTextImportHelper
    void UseRedlineText();
};


}//end of namespace binfilter
#endif
