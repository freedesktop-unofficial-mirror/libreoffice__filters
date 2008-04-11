/*************************************************************************
 *
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER.
 * 
 * Copyright 2008 by Sun Microsystems, Inc.
 *
 * OpenOffice.org - a multi-platform office productivity suite
 *
 * $RCSfile: xmlmetai.hxx,v $
 * $Revision: 1.4 $
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

#ifndef _XMLOFF_XMLMETAI_HXX
#define _XMLOFF_XMLMETAI_HXX

#ifndef _XMLOFF_XMLICTXT_HXX
#include <bf_xmloff/xmlictxt.hxx>
#endif

#ifndef _RTL_USTRBUF_HXX_
#include <rtl/ustrbuf.hxx>
#endif

#ifndef _COM_SUN_STAR_DOCUMENT_XDOCUMENTINFO_HPP_
#include <com/sun/star/document/XDocumentInfo.hpp>
#endif
#ifndef _COM_SUN_STAR_BEANS_XPROPERTYSET_HPP_
#include <com/sun/star/beans/XPropertySet.hpp>
#endif
namespace com { namespace sun { namespace star { namespace lang {
    struct Locale;
}}}}
namespace com { namespace sun { namespace star { namespace frame {
    class XModel;
}}}}
namespace binfilter {

class SvXMLTokenMap;


class SfxXMLMetaContext : public SvXMLImportContext
{
private:
    ::com::sun::star::uno::Reference<
        ::com::sun::star::document::XDocumentInfo>	xDocInfo;
    ::com::sun::star::uno::Reference<
        ::com::sun::star::beans::XPropertySet>		xInfoProp;
    ::com::sun::star::uno::Reference<
        ::com::sun::star::beans::XPropertySet>		xDocProp;
    SvXMLTokenMap*									pTokenMap;
    sal_Int32										nUserKeys;
    ::rtl::OUStringBuffer							sKeywords;

public:
    SfxXMLMetaContext( SvXMLImport& rImport, sal_uInt16 nPrfx,
                        const ::rtl::OUString& rLName,
                        const ::com::sun::star::uno::Reference<
                            ::com::sun::star::frame::XModel>& rDocModel );
    SfxXMLMetaContext( SvXMLImport& rImport, sal_uInt16 nPrfx,
                        const ::rtl::OUString& rLName,
                        const ::com::sun::star::uno::Reference<
                            ::com::sun::star::document::XDocumentInfo>&	rDocInfo );
    virtual ~SfxXMLMetaContext();

    // Create child element.
    virtual SvXMLImportContext *CreateChildContext( sal_uInt16 nPrefix,
                const ::rtl::OUString& rLocalName,
                const ::com::sun::star::uno::Reference<
                    ::com::sun::star::xml::sax::XAttributeList>& xAttrList );

    virtual void EndElement();

    const ::com::sun::star::uno::Reference<
        ::com::sun::star::beans::XPropertySet>& GetInfoProp() const
            { return xInfoProp; }
    const ::com::sun::star::uno::Reference<
        ::com::sun::star::beans::XPropertySet>& GetDocProp() const
            { return xDocProp; }

    void	AddKeyword( const ::rtl::OUString& rKW );
    void	AddUserField( const ::rtl::OUString& rName,
                            const ::rtl::OUString& rContent );
};

}//end of namespace binfilter
#endif // _XMLOFF_XMLMETAI_HXX

