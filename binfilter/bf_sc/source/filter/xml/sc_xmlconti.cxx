/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: sc_xmlconti.cxx,v $
 *
 *  $Revision: 1.6 $
 *
 *  last change: $Author: rt $ $Date: 2006-10-27 15:29:03 $
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

#ifdef PCH
#endif

#pragma hdrstop

// INCLUDE ---------------------------------------------------------------

#include "xmlconti.hxx"
#include "xmlimprt.hxx"

#include <bf_xmloff/nmspmap.hxx>
#ifndef _XMLOFF_XMLNMSPE_HXX
#include <bf_xmloff/xmlnmspe.hxx>
#endif
namespace binfilter {

using namespace xmloff::token;

//------------------------------------------------------------------

ScXMLContentContext::ScXMLContentContext( ScXMLImport& rImport,
                                      USHORT nPrfx,
                                      const ::rtl::OUString& rLName,
                                      const ::com::sun::star::uno::Reference<
                                      ::com::sun::star::xml::sax::XAttributeList>& xAttrList,
                                      ::rtl::OUStringBuffer& sTempValue) :
    SvXMLImportContext( rImport, nPrfx, rLName ),
    sOUText(),
    sValue(sTempValue)
{
}

ScXMLContentContext::~ScXMLContentContext()
{
}

SvXMLImportContext *ScXMLContentContext::CreateChildContext( USHORT nPrefix,
                                            const ::rtl::OUString& rLName,
                                            const ::com::sun::star::uno::Reference<
                                          ::com::sun::star::xml::sax::XAttributeList>& xAttrList )
{
    SvXMLImportContext *pContext = 0;

    if ((nPrefix == XML_NAMESPACE_TEXT) && IsXMLToken(rLName, XML_S))
    {
        sal_Int32 nRepeat(0);
        sal_Int16 nAttrCount = xAttrList.is() ? xAttrList->getLength() : 0;
        for( sal_Int16 i=0; i < nAttrCount; i++ )
        {
            ::rtl::OUString sAttrName = xAttrList->getNameByIndex( i );
            ::rtl::OUString sValue = xAttrList->getValueByIndex( i );
            ::rtl::OUString aLocalName;
            USHORT nPrfx = GetScImport().GetNamespaceMap().GetKeyByAttrName(
                                                sAttrName, &aLocalName );
            if ((nPrfx == XML_NAMESPACE_TEXT) && IsXMLToken(aLocalName, XML_C))
                nRepeat = sValue.toInt32();
        }
        if (nRepeat)
            for (sal_Int32 j = 0; j < nRepeat; j++)
                sOUText.append(static_cast<sal_Unicode>(' '));
        else
            sOUText.append(static_cast<sal_Unicode>(' '));
    }

    if( !pContext )
        pContext = new SvXMLImportContext( GetImport(), nPrefix, rLName );

    return pContext;
}

void ScXMLContentContext::Characters( const ::rtl::OUString& rChars )
{
    sOUText.append(rChars);
}

void ScXMLContentContext::EndElement()
{
    sValue.append(sOUText);
}
}
