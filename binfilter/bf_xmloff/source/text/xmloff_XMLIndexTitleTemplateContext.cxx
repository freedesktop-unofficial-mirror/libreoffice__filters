/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: xmloff_XMLIndexTitleTemplateContext.cxx,v $
 *
 *  $Revision: 1.3 $
 *
 *  last change: $Author: rt $ $Date: 2005-09-09 10:25:40 $
 *
 *  The Contents of this file are made available subject to
 *  the terms of GNU Lesser General Public License Version 2.1.
 *
 *
 *    GNU Lesser General Public License Version 2.1
 *    =============================================
 *    Copyright 2005 by Sun Microsystems, Inc.
 *    901 San Antonio Road, Palo Alto, CA 94303, USA
 *
 *    This library is free software; you can redistribute it and/or
 *    modify it under the terms of the GNU Lesser General Public
 *    License version 2.1, as published by the Free Software Foundation.
 *
 *    This library is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *    Lesser General Public License for more details.
 *
 *    You should have received a copy of the GNU Lesser General Public
 *    License along with this library; if not, write to the Free Software
 *    Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 *    MA  02111-1307  USA
 *
 ************************************************************************/

#ifndef _XMLOFF_XMLINDEXTITLETEMPLATECONTEXT_HXX_
#include "XMLIndexTitleTemplateContext.hxx"
#endif

// auto strip #ifndef _XMLOFF_XMLICTXT_HXX 
// auto strip #include "xmlictxt.hxx"
// auto strip #endif

#ifndef _XMLOFF_XMLIMP_HXX
#include "xmlimp.hxx"
#endif

#ifndef _XMLOFF_NMSPMAP_HXX 
#include "nmspmap.hxx"
#endif

#ifndef _XMLOFF_XMLNMSPE_HXX
#include "xmlnmspe.hxx"
#endif

// auto strip #ifndef _XMLOFF_XMLTOKEN_HXX
// auto strip #include "xmltoken.hxx"
// auto strip #endif
namespace binfilter {


using ::rtl::OUString;
using ::rtl::OUStringBuffer;
using ::com::sun::star::beans::XPropertySet;
using ::com::sun::star::uno::Any;
using ::com::sun::star::uno::Reference;
using ::com::sun::star::xml::sax::XAttributeList;
using ::binfilter::xmloff::token::IsXMLToken;
using ::binfilter::xmloff::token::XML_STYLE_NAME;


const sal_Char sAPI_Title[] = "Title";
const sal_Char sAPI_ParaStyleHeading[] = "ParaStyleHeading";


TYPEINIT1( XMLIndexTitleTemplateContext, SvXMLImportContext );

XMLIndexTitleTemplateContext::XMLIndexTitleTemplateContext(
    SvXMLImport& rImport, 
    Reference<XPropertySet> & rPropSet,
    sal_uInt16 nPrfx,
    const OUString& rLocalName) :
        SvXMLImportContext(rImport, nPrfx, rLocalName),
        sStyleName(),
        bStyleNameOK(sal_False),
        sContent(),
        rTOCPropertySet(rPropSet),
        sTitle(RTL_CONSTASCII_USTRINGPARAM(sAPI_Title)),
        sParaStyleHeading(RTL_CONSTASCII_USTRINGPARAM(sAPI_ParaStyleHeading))
{
}


XMLIndexTitleTemplateContext::~XMLIndexTitleTemplateContext()
{
}

void XMLIndexTitleTemplateContext::StartElement(
    const Reference<XAttributeList> & xAttrList)
{
    // there's only one attribute: style-name
    sal_Int16 nLength = xAttrList->getLength();
    for(sal_Int16 nAttr = 0; nAttr < nLength; nAttr++)
    {
        OUString sLocalName;
        sal_uInt16 nPrefix = GetImport().GetNamespaceMap().
            GetKeyByAttrName( xAttrList->getNameByIndex(nAttr), 
                              &sLocalName );
        if ( (XML_NAMESPACE_TEXT == nPrefix) &&
             (IsXMLToken(sLocalName, XML_STYLE_NAME)) )
        {
            sStyleName = xAttrList->getValueByIndex(nAttr);
            bStyleNameOK = sal_True;
        }
    }
}

void XMLIndexTitleTemplateContext::EndElement()
{
    Any aAny;

    aAny <<= sContent.makeStringAndClear();
    rTOCPropertySet->setPropertyValue(sTitle, aAny);

    if (bStyleNameOK)
    {
        aAny <<= sStyleName;
        rTOCPropertySet->setPropertyValue(sParaStyleHeading, aAny);
    }
}

void XMLIndexTitleTemplateContext::Characters(
    const OUString& sString)
{
    sContent.append(sString);
}
}//end of namespace binfilter
