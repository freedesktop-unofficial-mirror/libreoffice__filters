/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: xmloff_XMLTextMasterStylesContext.cxx,v $
 *
 *  $Revision: 1.4 $
 *
 *  last change: $Author: rt $ $Date: 2006-10-28 02:19:00 $
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



#ifndef _XMLOFF_XMLIMP_HXX 
#include "xmlimp.hxx"
#endif
#ifndef _XMLOFF_XMLNMSPE_HXX 
#include "xmlnmspe.hxx"
#endif

#ifndef _XMLTEXTMASTERPAGECONTEXT_HXX
#include "XMLTextMasterPageContext.hxx"
#endif
#ifndef _XMLTEXTMASTERSTYLESCONTEXT_HXX
#include "XMLTextMasterStylesContext.hxx"
#endif
namespace binfilter {

using namespace ::rtl;
using namespace ::com::sun::star::uno;
using namespace ::com::sun::star::xml::sax;

using ::binfilter::xmloff::token::IsXMLToken;
using ::binfilter::xmloff::token::XML_MASTER_PAGE;

// ------------------------------------------------------------------------

TYPEINIT1( XMLTextMasterStylesContext, SvXMLStylesContext );

sal_Bool XMLTextMasterStylesContext::InsertStyleFamily( sal_uInt16 ) const
{
    return sal_True;
}

XMLTextMasterStylesContext::XMLTextMasterStylesContext(
        SvXMLImport& rImport,
        sal_uInt16 nPrfx, const OUString& rLName,
        const Reference< XAttributeList > & xAttrList ) :
    SvXMLStylesContext( rImport, nPrfx, rLName, xAttrList )
{
}

XMLTextMasterStylesContext::~XMLTextMasterStylesContext()
{
}

SvXMLStyleContext *XMLTextMasterStylesContext::CreateStyleChildContext(
        sal_uInt16 nPrefix,
        const OUString& rLocalName,
        const Reference< XAttributeList > & xAttrList )
{
    SvXMLStyleContext *pContext = 0;

    if( XML_NAMESPACE_STYLE == nPrefix &&
        IsXMLToken( rLocalName, XML_MASTER_PAGE ) &&
         InsertStyleFamily( XML_STYLE_FAMILY_MASTER_PAGE ) )
        pContext = new XMLTextMasterPageContext(
                        GetImport(), nPrefix, rLocalName,
                          xAttrList,
                        !GetImport().GetTextImport()->IsInsertMode() );

    // any other style will be ignored here!

    return pContext;
}

SvXMLStyleContext *XMLTextMasterStylesContext::CreateStyleStyleChildContext(
        sal_uInt16 nFamily,
        sal_uInt16 nPrefix,
        const OUString& rLocalName,
        const Reference< XAttributeList > & xAttrList )
{
    return 0;
}
}//end of namespace binfilter
