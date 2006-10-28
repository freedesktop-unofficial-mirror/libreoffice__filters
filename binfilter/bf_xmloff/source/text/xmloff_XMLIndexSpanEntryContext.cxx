/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: xmloff_XMLIndexSpanEntryContext.cxx,v $
 *
 *  $Revision: 1.5 $
 *
 *  last change: $Author: rt $ $Date: 2006-10-28 02:13:11 $
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

#ifndef _XMLOFF_XMLINDEXSPANENTRYCONTEXT_HXX_
#include "XMLIndexSpanEntryContext.hxx"
#endif

#include "rtl/ustring.hxx"

#ifndef _XMLOFF_XMLINDEXTEMPLATECONTEXT_HXX_
#include "XMLIndexTemplateContext.hxx"
#endif

namespace binfilter {


using ::rtl::OUString;
using ::com::sun::star::uno::Sequence;
using ::com::sun::star::uno::Any;
using ::com::sun::star::beans::PropertyValue;


TYPEINIT1( XMLIndexSpanEntryContext, XMLIndexSimpleEntryContext);

XMLIndexSpanEntryContext::XMLIndexSpanEntryContext(
    SvXMLImport& rImport, 
    XMLIndexTemplateContext& rTemplate,
    sal_uInt16 nPrfx,
    const OUString& rLocalName ) :
        XMLIndexSimpleEntryContext(rImport, rTemplate.sTokenText, 
                                   rTemplate, nPrfx, rLocalName)
{
    nValues++;	// one more for the text string
}

XMLIndexSpanEntryContext::~XMLIndexSpanEntryContext()
{
}

void XMLIndexSpanEntryContext::Characters(const OUString& sString)
{
    sContent.append(sString);
}

void XMLIndexSpanEntryContext::FillPropertyValues(
    Sequence<PropertyValue> & rValues)
{
    // call superclass for token type, stylename, 
    XMLIndexSimpleEntryContext::FillPropertyValues(rValues);

    // content
    Any aAny;
    aAny <<= sContent.makeStringAndClear();
    rValues[nValues-1].Name = rTemplateContext.sText;
    rValues[nValues-1].Value = aAny;
}

}//end of namespace binfilter
