/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: xmloff_SchXMLParagraphContext.cxx,v $
 *
 *  $Revision: 1.3 $
 *
 *  last change: $Author: rt $ $Date: 2005-09-09 07:38:04 $
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

// auto strip #include "SchXMLImport.hxx"
#include "SchXMLParagraphContext.hxx"

#ifndef _XMLOFF_XMLNMSPE_HXX
#include "xmlnmspe.hxx"
#endif
#ifndef _XMLOFF_XMLTOKEN_HXX
#include "xmltoken.hxx"
#endif
namespace binfilter {

using namespace rtl;
using namespace ::com::sun::star;

SchXMLParagraphContext::SchXMLParagraphContext( SvXMLImport& rImport,
                                                const OUString& rLocalName,
                                                OUString& rText ) :
        SvXMLImportContext( rImport, XML_NAMESPACE_TEXT, rLocalName ),
        mrText( rText )
{
}

SchXMLParagraphContext::~SchXMLParagraphContext()
{}

void SchXMLParagraphContext::EndElement()
{
    mrText = maBuffer.makeStringAndClear();
}

SvXMLImportContext* SchXMLParagraphContext::CreateChildContext(
    USHORT nPrefix,
    const OUString& rLocalName,
    const uno::Reference< xml::sax::XAttributeList >& xAttrList )
{
    if( nPrefix == XML_NAMESPACE_TEXT )
    {
        if( rLocalName.equals( ::binfilter::xmloff::token::GetXMLToken( ::binfilter::xmloff::token::XML_TAB_STOP )))
        {
            maBuffer.append( sal_Unicode( 0x0009 ));  // tabulator
        }
        else if( rLocalName.equals( ::binfilter::xmloff::token::GetXMLToken( ::binfilter::xmloff::token::XML_LINE_BREAK )))
        {
            maBuffer.append( sal_Unicode( 0x000A ));  // linefeed
        }
    }

    return new SvXMLImportContext( GetImport(), nPrefix, rLocalName );
}

void SchXMLParagraphContext::Characters( const OUString& rChars )
{
    maBuffer.append( rChars );
}
}//end of namespace binfilter
