/*************************************************************************
 *
 *  $RCSfile: xmloff_XMLLineNumberingSeparatorImportContext.cxx,v $
 *
 *  $Revision: 1.2 $
 *
 *  last change: $Author: hr $ $Date: 2004-08-03 20:28:36 $
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

#ifndef _XMLOFF_XMLLINENUMBERINGSEPARATORIMPORTCONTEXT_HXX_
#include "XMLLineNumberingSeparatorImportContext.hxx"
#endif

#ifndef _XMLOFF_XMLLINENUMBERINGIMPORTCONTEXT_HXX_
#include "XMLLineNumberingImportContext.hxx"
#endif

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

#ifndef _XMLOFF_XMLUCONV_HXX
#include "xmluconv.hxx"
#endif
namespace binfilter {


using namespace ::com::sun::star::uno;

using ::com::sun::star::xml::sax::XAttributeList;
using ::rtl::OUString;
using ::rtl::OUStringBuffer;
using ::binfilter::xmloff::token::IsXMLToken;
using ::binfilter::xmloff::token::XML_INCREMENT;

TYPEINIT1( XMLLineNumberingSeparatorImportContext, SvXMLImportContext );

XMLLineNumberingSeparatorImportContext::XMLLineNumberingSeparatorImportContext(
    SvXMLImport& rImport, 
    sal_uInt16 nPrfx,
    const OUString& rLocalName,
    XMLLineNumberingImportContext& rLineNumbering) :
        SvXMLImportContext(rImport, nPrfx, rLocalName),
        rLineNumberingContext(rLineNumbering)
{
}

XMLLineNumberingSeparatorImportContext::~XMLLineNumberingSeparatorImportContext()
{
}

void XMLLineNumberingSeparatorImportContext::StartElement(
    const Reference<XAttributeList> & xAttrList)
{
    sal_Int16 nLength = xAttrList->getLength();
    for(sal_Int16 i=0; i<nLength; i++) 
    {
        OUString sLocalName;
        sal_uInt16 nPrefix = GetImport().GetNamespaceMap().
            GetKeyByAttrName( xAttrList->getNameByIndex(i), &sLocalName );

        if ( (nPrefix == XML_NAMESPACE_TEXT) &&
             IsXMLToken(sLocalName, XML_INCREMENT) )
        {
            sal_Int32 nTmp;
            if (SvXMLUnitConverter::convertNumber(
                nTmp, xAttrList->getValueByIndex(i), 0))
            {
                rLineNumberingContext.SetSeparatorIncrement((sal_Int16)nTmp);
            }
            // else: invalid number -> ignore
        }
        // else: unknown attribute -> ignore
    }
}

void XMLLineNumberingSeparatorImportContext::Characters(
    const OUString& rChars )
{
    sSeparatorBuf.append(rChars);
}

void XMLLineNumberingSeparatorImportContext::EndElement()
{
    rLineNumberingContext.SetSeparatorText(sSeparatorBuf.makeStringAndClear());
}
}//end of namespace binfilter
