/*************************************************************************
 *
 *  $RCSfile: xmloff_XMLIndexTOCSourceContext.cxx,v $
 *
 *  $Revision: 1.2 $
 *
 *  last change: $Author: hr $ $Date: 2004-08-03 20:26:35 $
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


#ifndef _XMLOFF_XMLINDEXTOCSOURCECONTEXT_HXX_
#include "XMLIndexTOCSourceContext.hxx"
#endif

// auto strip #ifndef _COM_SUN_STAR_BEANS_XPROPERTYSET_HPP_
// auto strip #include <com/sun/star/beans/XPropertySet.hpp>
// auto strip #endif

#ifndef _COM_SUN_STAR_CONTAINER_XINDEXREPLACE_HPP_
#include <com/sun/star/container/XIndexReplace.hpp>
#endif

#ifndef _XMLOFF_XMLINDEXTEMPLATECONTEXT_HXX_
#include "XMLIndexTemplateContext.hxx"
#endif

// auto strip #ifndef _XMLOFF_XMLINDEXTITLETEMPLATECONTEXT_HXX_
// auto strip #include "XMLIndexTitleTemplateContext.hxx"
// auto strip #endif

// auto strip #ifndef _XMLOFF_XMLINDEXTOCSTYLESCONTEXT_HXX_
// auto strip #include "XMLIndexTOCStylesContext.hxx"
// auto strip #endif

// auto strip #ifndef _XMLOFF_XMLICTXT_HXX 
// auto strip #include "xmlictxt.hxx"
// auto strip #endif

#ifndef _XMLOFF_XMLIMP_HXX
#include "xmlimp.hxx"
#endif

// auto strip #ifndef _XMLOFF_TEXTIMP_HXX_
// auto strip #include "txtimp.hxx"
// auto strip #endif

#ifndef _XMLOFF_XMLNMSPE_HXX
#include "xmlnmspe.hxx"
#endif

// auto strip #ifndef _XMLOFF_NMSPMAP_HXX 
// auto strip #include "nmspmap.hxx"
// auto strip #endif

// auto strip #ifndef _XMLOFF_XMLTOKEN_HXX
// auto strip #include "xmltoken.hxx"
// auto strip #endif

#ifndef _XMLOFF_XMLUCONV_HXX
#include "xmluconv.hxx"
#endif

// auto strip #ifndef _TOOLS_DEBUG_HXX 
// auto strip #include <tools/debug.hxx>
// auto strip #endif

// auto strip #ifndef _RTL_USTRING_HXX_
// auto strip #include <rtl/ustring.hxx>
// auto strip #endif
namespace binfilter {



using namespace ::binfilter::xmloff::token;

using ::rtl::OUString;
using ::com::sun::star::beans::XPropertySet;
using ::com::sun::star::uno::Reference;
using ::com::sun::star::uno::Any;
using ::com::sun::star::xml::sax::XAttributeList;

const sal_Char sAPI_CreateFromChapter[] = "CreateFromChapter";
const sal_Char sAPI_CreateFromOutline[] = "CreateFromOutline";
const sal_Char sAPI_CreateFromMarks[] = "CreateFromMarks";
const sal_Char sAPI_Level[] = "Level";
const sal_Char sAPI_CreateFromLevelParagraphStyles[] = "CreateFromLevelParagraphStyles";


TYPEINIT1( XMLIndexTOCSourceContext, XMLIndexSourceBaseContext );

XMLIndexTOCSourceContext::XMLIndexTOCSourceContext(
    SvXMLImport& rImport, 
    sal_uInt16 nPrfx,
    const OUString& rLocalName,
    Reference<XPropertySet> & rPropSet) :
        XMLIndexSourceBaseContext(rImport, nPrfx, rLocalName, 
                                  rPropSet, sal_True),
        // use all chapters by default
        nOutlineLevel(rImport.GetTextImport()->GetChapterNumbering()->
                                                                  getCount()),
        bUseOutline(sal_True),
        bUseMarks(sal_True),
        sCreateFromMarks(RTL_CONSTASCII_USTRINGPARAM(sAPI_CreateFromMarks)),
        sLevel(RTL_CONSTASCII_USTRINGPARAM(sAPI_Level)),
       sCreateFromOutline(RTL_CONSTASCII_USTRINGPARAM(sAPI_CreateFromOutline)),
        sCreateFromLevelParagraphStyles(RTL_CONSTASCII_USTRINGPARAM(
            sAPI_CreateFromLevelParagraphStyles)),
        bUseParagraphStyles(sal_False)
{
}

XMLIndexTOCSourceContext::~XMLIndexTOCSourceContext()
{
}

void XMLIndexTOCSourceContext::ProcessAttribute(
    enum IndexSourceParamEnum eParam, 
    const OUString& rValue)
{
    switch (eParam)
    {
        case XML_TOK_INDEXSOURCE_OUTLINE_LEVEL:
            if ( IsXMLToken( rValue, XML_NONE ) )
            {
                // #104651# use OUTLINE_LEVEL and USE_OUTLINE_LEVEL instead of
                // OUTLINE_LEVEL with values none|1..10. For backwards
                // compatibility, 'none' must still be read.
                bUseOutline = sal_False;
            }
            else
            {
                sal_Int32 nTmp;
                if (SvXMLUnitConverter::convertNumber(
                    nTmp, rValue, 1, GetImport().GetTextImport()->
                    GetChapterNumbering()->getCount()))
                {
                    bUseOutline = sal_True;
                    nOutlineLevel = nTmp;
                }
            }
            break;
            
        case XML_TOK_INDEXSOURCE_USE_OUTLINE_LEVEL:
        {
            sal_Bool bTmp;
            if (SvXMLUnitConverter::convertBool(bTmp, rValue))
            {
                bUseOutline = bTmp;
            }
            break;
        }


        case XML_TOK_INDEXSOURCE_USE_INDEX_MARKS:
        {
            sal_Bool bTmp;
            if (SvXMLUnitConverter::convertBool(bTmp, rValue))
            {
                bUseMarks = bTmp;
            }
            break;
        }

        case XML_TOK_INDEXSOURCE_USE_INDEX_SOURCE_STYLES:
        {
            sal_Bool bTmp;
            if (SvXMLUnitConverter::convertBool(bTmp, rValue))
            {
                bUseParagraphStyles = bTmp;
            }
            break;
        }

        default:
            // default: ask superclass
            XMLIndexSourceBaseContext::ProcessAttribute(eParam, rValue);
            break;
    }
}

void XMLIndexTOCSourceContext::EndElement()
{
    Any aAny;

    aAny.setValue(&bUseMarks, ::getBooleanCppuType());
    rIndexPropertySet->setPropertyValue(sCreateFromMarks, aAny);

    aAny.setValue(&bUseOutline, ::getBooleanCppuType());
    rIndexPropertySet->setPropertyValue(sCreateFromOutline, aAny);

    aAny.setValue(&bUseParagraphStyles, ::getBooleanCppuType());
    rIndexPropertySet->setPropertyValue(sCreateFromLevelParagraphStyles, aAny);

    aAny <<= (sal_Int16)nOutlineLevel;
    rIndexPropertySet->setPropertyValue(sLevel, aAny);

    // process common attributes
    XMLIndexSourceBaseContext::EndElement();
}


SvXMLImportContext* XMLIndexTOCSourceContext::CreateChildContext( 
    sal_uInt16 nPrefix,
    const OUString& rLocalName,
    const Reference<XAttributeList> & xAttrList )
{
    if ( (XML_NAMESPACE_TEXT == nPrefix) &&
         IsXMLToken(rLocalName, XML_TABLE_OF_CONTENT_ENTRY_TEMPLATE) )
    {
        return new XMLIndexTemplateContext(GetImport(), rIndexPropertySet, 
                                           nPrefix, rLocalName,
                                           aLevelNameTOCMap,
                                           XML_OUTLINE_LEVEL,
                                           aLevelStylePropNameTOCMap,
                                           aAllowedTokenTypesTOC);
    }
    else 
    {
        return XMLIndexSourceBaseContext::CreateChildContext(nPrefix, 
                                                             rLocalName,
                                                             xAttrList);
    }
}
}//end of namespace binfilter
