/*************************************************************************
 *
 *  $RCSfile: xmloff_XMLIndexSpanEntryContext.cxx,v $
 *
 *  $Revision: 1.1 $
 *
 *  last change: $Author: aw $ $Date: 2003-12-05 09:38:00 $
 *
 *  The Contents of this file are made available subject to the terms of
 *  either of the following licenses
 *
 *         - GNU Lesser General Public License Version 2.1
 *         - Sun Industry Standards Source License Version 1.1
 *
 *  Sun Microsystems Inc., October, 2000
 *
 *  GNU Lesser General Public License Version 2.1
 *  =============================================
 *  Copyright 2000 by Sun Microsystems, Inc.
 *  901 San Antonio Road, Palo Alto, CA 94303, USA
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public
 *  License version 2.1, as published by the Free Software Foundation.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public
 *  License along with this library; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 *  MA  02111-1307  USA
 *
 *
 *  Sun Industry Standards Source License Version 1.1
 *  =================================================
 *  The contents of this file are subject to the Sun Industry Standards
 *  Source License Version 1.1 (the "License"); You may not use this file
 *  except in compliance with the License. You may obtain a copy of the
 *  License at http://www.openoffice.org/license.html.
 *
 *  Software provided under this License is provided on an "AS IS" basis,
 *  WITHOUT WARRANTY OF ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING,
 *  WITHOUT LIMITATION, WARRANTIES THAT THE SOFTWARE IS FREE OF DEFECTS,
 *  MERCHANTABLE, FIT FOR A PARTICULAR PURPOSE, OR NON-INFRINGING.
 *  See the License for the specific provisions governing your rights and
 *  obligations concerning the Software.
 *
 *  The Initial Developer of the Original Code is: Sun Microsystems, Inc.
 *
 *  Copyright: 2000 by Sun Microsystems, Inc.
 *
 *  All Rights Reserved.
 *
 *  Contributor(s): _______________________________________
 *
 *
 ************************************************************************/

#ifndef _XMLOFF_XMLINDEXSPANENTRYCONTEXT_HXX_
#include "XMLIndexSpanEntryContext.hxx"
#endif

#ifndef _RTL_USTRING_
#include <rtl/ustring>
#endif

#ifndef _XMLOFF_XMLINDEXTEMPLATECONTEXT_HXX_
#include "XMLIndexTemplateContext.hxx"
#endif

#ifndef _XMLOFF_XMLICTXT_HXX 
#include "xmlictxt.hxx"
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
