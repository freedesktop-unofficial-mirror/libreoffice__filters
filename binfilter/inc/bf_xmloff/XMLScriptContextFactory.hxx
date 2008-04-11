/*************************************************************************
 *
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER.
 * 
 * Copyright 2008 by Sun Microsystems, Inc.
 *
 * OpenOffice.org - a multi-platform office productivity suite
 *
 * $RCSfile: XMLScriptContextFactory.hxx,v $
 * $Revision: 1.6 $
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

#ifndef _XMLOFF_XMLSCRIPTCONTEXTFACTORY_HXX
#define _XMLOFF_XMLSCRIPTCONTEXTFACTORY_HXX


#ifndef _XMLOFF_XMLEVENT_HXX
#include "xmlevent.hxx"
#endif


namespace com { namespace sun { namespace star {
    namespace xml { namespace sax {	class XAttributeList; } }
} } }
namespace rtl {	class OUString; }
namespace binfilter {
class SvXMLImport;
class XMLEventsImportContext;

class XMLScriptContextFactory : public XMLEventContextFactory
{
    const ::rtl::OUString sEventType;
    const ::rtl::OUString sScript;
    const ::rtl::OUString sURL;

public:
    XMLScriptContextFactory();
    virtual ~XMLScriptContextFactory();

    virtual SvXMLImportContext * 
    CreateContext(SvXMLImport & rImport, /// import context
                  sal_uInt16 nPrefix,    /// element: namespace prefix
                  const ::rtl::OUString & rLocalName, /// element: local name
                  /// attribute list
                  const ::com::sun::star::uno::Reference< 
                  ::com::sun::star::xml::sax::XAttributeList> & xAttrList,
                  /// the context for the enclosing <script:events> element
                  XMLEventsImportContext * rEvents,
                  /// the event name (as understood by the API)
                  const ::rtl::OUString & rApiEventName,
                  /// the event type name (as registered)
                  const ::rtl::OUString & rLanguage);
};

}//end of namespace binfilter
#endif // _XMLOFF_XMLSCRIPTCONTEXTFACTORY_HXX
