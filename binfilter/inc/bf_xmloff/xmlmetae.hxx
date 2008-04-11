/*************************************************************************
 *
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER.
 * 
 * Copyright 2008 by Sun Microsystems, Inc.
 *
 * OpenOffice.org - a multi-platform office productivity suite
 *
 * $RCSfile: xmlmetae.hxx,v $
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

#ifndef _XMLOFF_XMLMETAE_HXX
#define _XMLOFF_XMLMETAE_HXX

#ifndef _COM_SUN_STAR_DOCUMENT_XDOCUMENTINFO_HPP_
#include <com/sun/star/document/XDocumentInfo.hpp>
#endif
#ifndef _COM_SUN_STAR_XML_SAX_XDOCUMENTHANDLER_HPP_
#include <com/sun/star/xml/sax/XDocumentHandler.hpp>
#endif
#ifndef _COM_SUN_STAR_XML_SAX_XATTRIBUTELIST_HPP_
#include <com/sun/star/xml/sax/XAttributeList.hpp>
#endif
#ifndef _COM_SUN_STAR_BEANS_XPROPERTYSET_HPP_
#include <com/sun/star/beans/XPropertySet.hpp>
#endif
#ifndef _COM_SUN_STAR_UTIL_DATETIME_HPP_
#include <com/sun/star/util/DateTime.hpp>
#endif
#ifndef _COM_SUN_STAR_LANG_LOCALE_HPP_
#include <com/sun/star/lang/Locale.hpp>
#endif
#ifndef _XMLOFF_XMLTOKEN_HXX
#include <bf_xmloff/xmltoken.hxx>
#endif
class Time;

namespace com { namespace sun { namespace star { namespace frame {
    class XModel;
} } } }
namespace binfilter {

class SvXMLNamespaceMap;
class SvXMLAttributeList;
class SvXMLExport;

class SfxXMLMetaExport
{
private:
    SvXMLExport&                                        rExport;
    ::com::sun::star::uno::Reference<
        ::com::sun::star::document::XDocumentInfo>		xDocInfo;
    ::com::sun::star::uno::Reference<
        ::com::sun::star::beans::XPropertySet>			xInfoProp;
    ::com::sun::star::lang::Locale						aLocale;

    void	SimpleStringElement( const ::rtl::OUString& rPropertyName,
                                 sal_uInt16 nNamespace,
                             enum ::binfilter::xmloff::token::XMLTokenEnum eElementName );
    void	SimpleDateTimeElement( const ::rtl::OUString& rPropertyName,
                                   sal_uInt16 nNamespace,
                             enum ::binfilter::xmloff::token::XMLTokenEnum eElementName );

public:
    SfxXMLMetaExport( SvXMLExport& rExport,
                      const ::com::sun::star::uno::Reference<
                        ::com::sun::star::frame::XModel>& rDocModel );

    virtual ~SfxXMLMetaExport();

    // core API
    void Export();

    static ::rtl::OUString GetISODateTimeString(
                        const ::com::sun::star::util::DateTime& rDateTime );
    static ::rtl::OUString GetISODurationString( const Time& rTime );
};

}//end of namespace binfilter
#endif // _XMLOFF_XMLMETAE_HXX

