/*************************************************************************
 *
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER.
 * 
 * Copyright 2008 by Sun Microsystems, Inc.
 *
 * OpenOffice.org - a multi-platform office productivity suite
 *
 * $RCSfile: XMLEmbeddedObjectImportContext.hxx,v $
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

#ifndef _XMLOFF_XMLEMBEDDEDOBJECTIMPORTCONTEXT_HXX
#define _XMLOFF_XMLEMBEDDEDOBJECTIMPORTCONTEXT_HXX

#ifndef _COM_SUN_STAR_XML_SAX_XDOCUMENTHANDLER_HPP_
#include <com/sun/star/xml/sax/XDocumentHandler.hpp>
#endif

#ifndef _XMLOFF_XMLICTXT_HXX
#include "xmlictxt.hxx"
#endif
namespace com { namespace sun { namespace star { namespace lang {
    class XComponent; } } } }
namespace binfilter {


class XMLEmbeddedObjectImportContext : public SvXMLImportContext
{
    ::com::sun::star::uno::Reference<
        ::com::sun::star::xml::sax::XDocumentHandler > xHandler;
    ::com::sun::star::uno::Reference<
        ::com::sun::star::lang::XComponent > xComp;

    ::rtl::OUString sFilterService;
    // #100592#
    ::rtl::OUString sCLSID;

    // #i55761#
    bool bNeedToUnlockControllers;

public:
    TYPEINFO();

    const ::rtl::OUString& GetFilterServiceName() const { return sFilterService; }
    // #100592#
    const ::rtl::OUString& GetFilterCLSID() const { return sCLSID; }

    XMLEmbeddedObjectImportContext( SvXMLImport& rImport, USHORT nPrfx,
                                    const ::rtl::OUString& rLName,
        const ::com::sun::star::uno::Reference<
            ::com::sun::star::xml::sax::XAttributeList >& xAttrList );

    virtual ~XMLEmbeddedObjectImportContext();

    virtual SvXMLImportContext *CreateChildContext( USHORT nPrefix,
                                   const ::rtl::OUString& rLocalName,
                                   const ::com::sun::star::uno::Reference< ::com::sun::star::xml::sax::XAttributeList >& xAttrList );

    virtual void StartElement( const ::com::sun::star::uno::Reference< ::com::sun::star::xml::sax::XAttributeList >& xAttrList );

    virtual void EndElement();

    virtual void Characters( const ::rtl::OUString& rChars );

    sal_Bool SetComponent(
        ::com::sun::star::uno::Reference<
            ::com::sun::star::lang::XComponent >& rComp );

};

}//end of namespace binfilter
#endif	//  _XMLOFF_XMLEMBEDDEDOBJECTIMPORTCONTEXT_HXX

