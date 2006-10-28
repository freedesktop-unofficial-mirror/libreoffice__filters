/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: xmloff_XMLIndexTableSourceContext.cxx,v $
 *
 *  $Revision: 1.4 $
 *
 *  last change: $Author: rt $ $Date: 2006-10-28 02:14:10 $
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


#ifndef _XMLOFF_XMLINDEXTABLESOURCECONTEXT_HXX_
#include "XMLIndexTableSourceContext.hxx"
#endif



#ifndef _COM_SUN_STAR_TEXT_REFERENCEFIELD_PART_HPP
#include <com/sun/star/text/ReferenceFieldPart.hpp>
#endif

#ifndef _XMLOFF_XMLINDEXTEMPLATECONTEXT_HXX_
#include "XMLIndexTemplateContext.hxx"
#endif






#ifndef _XMLOFF_XMLNMSPE_HXX
#include "xmlnmspe.hxx"
#endif



#ifndef _XMLOFF_XMLUCONV_HXX
#include "xmluconv.hxx"
#endif


namespace binfilter {


using namespace ::com::sun::star::text;
using namespace ::binfilter::xmloff::token;

using ::rtl::OUString;
using ::com::sun::star::beans::XPropertySet;
using ::com::sun::star::uno::Reference;
using ::com::sun::star::uno::Any;
using ::com::sun::star::xml::sax::XAttributeList;

const sal_Char sAPI_CreateFromLabels[] = "CreateFromLabels";
const sal_Char sAPI_LabelCategory[] = "LabelCategory";
const sal_Char sAPI_LabelDisplayType[] = "LabelDisplayType";


TYPEINIT1(XMLIndexTableSourceContext, XMLIndexSourceBaseContext);


XMLIndexTableSourceContext::XMLIndexTableSourceContext(
    SvXMLImport& rImport, 
    sal_uInt16 nPrfx,
    const OUString& rLocalName,
    Reference<XPropertySet> & rPropSet) :
        XMLIndexSourceBaseContext(rImport, nPrfx, rLocalName, 
                                  rPropSet, sal_False),
        sCreateFromLabels(RTL_CONSTASCII_USTRINGPARAM(sAPI_CreateFromLabels)),
        sLabelCategory(RTL_CONSTASCII_USTRINGPARAM(sAPI_LabelCategory)),
        sLabelDisplayType(RTL_CONSTASCII_USTRINGPARAM(sAPI_LabelDisplayType)),
        bSequenceOK(sal_False),
        bDisplayFormatOK(sal_False),
        bUseCaption(sal_True)
{
}

XMLIndexTableSourceContext::~XMLIndexTableSourceContext()
{
}

static SvXMLEnumMapEntry __READONLY_DATA lcl_aReferenceTypeTokenMap[] =
{
    
    { XML_TEXT,			        ReferenceFieldPart::TEXT },
    { XML_CATEGORY_AND_VALUE,	ReferenceFieldPart::CATEGORY_AND_NUMBER },
    { XML_CAPTION, 		        ReferenceFieldPart::ONLY_CAPTION },

    // wrong values that previous versions wrote:
    { XML_CHAPTER, 		        ReferenceFieldPart::CATEGORY_AND_NUMBER },
    { XML_PAGE,			        ReferenceFieldPart::ONLY_CAPTION },

    { XML_TOKEN_INVALID, 		0 }
};

void XMLIndexTableSourceContext::ProcessAttribute(
    enum IndexSourceParamEnum eParam, 
    const OUString& rValue)
{
    sal_Bool bTmp;

    switch (eParam)
    {
        case XML_TOK_INDEXSOURCE_USE_CAPTION:
            if (SvXMLUnitConverter::convertBool(bTmp, rValue))
            {
                bUseCaption = bTmp;
            }
            break;

        case XML_TOK_INDEXSOURCE_SEQUENCE_NAME:
            sSequence = rValue;
            bSequenceOK = sal_True;
            break;

        case XML_TOK_INDEXSOURCE_SEQUENCE_FORMAT:
        {
             sal_uInt16 nTmp;
             if (SvXMLUnitConverter::convertEnum(nTmp, rValue, 
                                                 lcl_aReferenceTypeTokenMap))
            {
                 nDisplayFormat = nTmp;
                 bDisplayFormatOK = sal_True;
             }
            break;
        }

        default:
            XMLIndexSourceBaseContext::ProcessAttribute(eParam, rValue);
            break;
    }
}


void XMLIndexTableSourceContext::EndElement()
{
    Any aAny;

    aAny.setValue(&bUseCaption, ::getBooleanCppuType());
    rIndexPropertySet->setPropertyValue(sCreateFromLabels, aAny);

    if (bSequenceOK)
    {
        aAny <<= sSequence;
        rIndexPropertySet->setPropertyValue(sLabelCategory, aAny);
    }

    if (bDisplayFormatOK)
    {
        aAny <<= nDisplayFormat;
        rIndexPropertySet->setPropertyValue(sLabelDisplayType, aAny);
    }

    XMLIndexSourceBaseContext::EndElement();
}


SvXMLImportContext* XMLIndexTableSourceContext::CreateChildContext( 
    sal_uInt16 nPrefix,
    const OUString& rLocalName,
    const Reference<XAttributeList> & xAttrList )
{
    if ( ( XML_NAMESPACE_TEXT == nPrefix ) &&
         ( IsXMLToken( rLocalName, XML_TABLE_INDEX_ENTRY_TEMPLATE ) ) )
    {
        return new XMLIndexTemplateContext(GetImport(), rIndexPropertySet, 
                                           nPrefix, rLocalName,
                                           aLevelNameTableMap,
                                           XML_TOKEN_INVALID, // no outline-level attr
                                           aLevelStylePropNameTableMap,
                                           aAllowedTokenTypesTable);
    }
    else 
    {
        return XMLIndexSourceBaseContext::CreateChildContext(nPrefix, 
                                                             rLocalName,
                                                             xAttrList);
    }

}
}//end of namespace binfilter
