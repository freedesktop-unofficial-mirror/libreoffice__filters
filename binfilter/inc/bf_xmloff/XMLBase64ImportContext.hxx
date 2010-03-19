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

#ifndef _XMLOFF_XMLBASE64IMPORTCONTEXT_HXX
#define _XMLOFF_XMLBASE64IMPORTCONTEXT_HXX

#ifndef _COM_SUN_STAR_XML_SAX_XDOCUMENTHANDLER_HPP_
#include <com/sun/star/xml/sax/XDocumentHandler.hpp>
#endif

#ifndef _XMLOFF_XMLICTXT_HXX
#include <bf_xmloff/xmlictxt.hxx>
#endif

namespace com { namespace sun { namespace star { namespace io {
    class XOutputStream; } } } }
namespace binfilter {

class XMLBase64ImportContext : public SvXMLImportContext
{
    ::com::sun::star::uno::Reference<
        ::com::sun::star::io::XOutputStream > xOut;
    ::rtl::OUString sBase64CharsLeft;

public:
    TYPEINFO();

    XMLBase64ImportContext( SvXMLImport& rImport, USHORT nPrfx,
                            const ::rtl::OUString& rLName,
        const ::com::sun::star::uno::Reference<
            ::com::sun::star::xml::sax::XAttributeList >& xAttrList,
        const ::com::sun::star::uno::Reference<
            ::com::sun::star::io::XOutputStream >& rOut );

    virtual ~XMLBase64ImportContext();

    virtual void EndElement();

    virtual void Characters( const ::rtl::OUString& rChars );

};

}//end of namespace binfilter
#endif	//  _XMLOFF_XMLBASE64IMPORTCONTEXT_HXX

