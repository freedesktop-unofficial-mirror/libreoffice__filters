/*************************************************************************
 *
 *  $RCSfile: xmloff_XMLIndexSourceBaseContext.cxx,v $
 *
 *  $Revision: 1.1 $
 *
 *  last change: $Author: aw $ $Date: 2003-12-05 09:37:59 $
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


#ifndef _XMLOFF_XMLINDEXSOURCEBASECONTEXT_HXX_
#include "XMLIndexSourceBaseContext.hxx"
#endif

#ifndef _COM_SUN_STAR_BEANS_XPROPERTYSET_HPP_
#include <com/sun/star/beans/XPropertySet.hpp>
#endif

#ifndef _COM_SUN_STAR_CONTAINER_XINDEXREPLACE_HPP_
#include <com/sun/star/container/XIndexReplace.hpp>
#endif

#ifndef _XMLOFF_XMLINDEXTEMPLATECONTEXT_HXX_
#include "XMLIndexTemplateContext.hxx"
#endif

#ifndef _XMLOFF_XMLINDEXTITLETEMPLATECONTEXT_HXX_
#include "XMLIndexTitleTemplateContext.hxx"
#endif

#ifndef _XMLOFF_XMLINDEXTOCSTYLESCONTEXT_HXX_
#include "XMLIndexTOCStylesContext.hxx"
#endif

#ifndef _XMLOFF_XMLICTXT_HXX 
#include "xmlictxt.hxx"
#endif

#ifndef _XMLOFF_XMLIMP_HXX
#include "xmlimp.hxx"
#endif

#ifndef _XMLOFF_TEXTIMP_HXX_
#include "txtimp.hxx"
#endif

#ifndef _XMLOFF_XMLNMSPE_HXX
#include "xmlnmspe.hxx"
#endif

#ifndef _XMLOFF_NMSPMAP_HXX 
#include "nmspmap.hxx"
#endif

#ifndef _XMLOFF_XMLTOKEN_HXX
#include "xmltoken.hxx"
#endif

#ifndef _XMLOFF_XMLUCONV_HXX
#include "xmluconv.hxx"
#endif

#ifndef _TOOLS_DEBUG_HXX 
#include <tools/debug.hxx>
#endif

#ifndef _RTL_USTRING_HXX_
#include <rtl/ustring.hxx>
#endif
namespace binfilter {



using namespace ::binfilter::xmloff::token;

using ::rtl::OUString;
using ::com::sun::star::beans::XPropertySet;
using ::com::sun::star::uno::Reference;
using ::com::sun::star::uno::Any;
using ::com::sun::star::xml::sax::XAttributeList;

const sal_Char sAPI_CreateFromChapter[] = "CreateFromChapter";
const sal_Char sAPI_IsRelativeTabstops[] = "IsRelativeTabstops";

static __FAR_DATA SvXMLTokenMapEntry aIndexSourceTokenMap[] =
{
    { XML_NAMESPACE_TEXT, 
          XML_OUTLINE_LEVEL, 
          XML_TOK_INDEXSOURCE_OUTLINE_LEVEL},
    { XML_NAMESPACE_TEXT, 
          XML_USE_INDEX_MARKS, 
          XML_TOK_INDEXSOURCE_USE_INDEX_MARKS },
    { XML_NAMESPACE_TEXT, 
          XML_INDEX_SCOPE, 
          XML_TOK_INDEXSOURCE_INDEX_SCOPE },
    { XML_NAMESPACE_TEXT, 
          XML_RELATIVE_TAB_STOP_POSITION, 
          XML_TOK_INDEXSOURCE_RELATIVE_TABS } ,
    { XML_NAMESPACE_TEXT,
          XML_USE_OTHER_OBJECTS,
          XML_TOK_INDEXSOURCE_USE_OTHER_OBJECTS },
    { XML_NAMESPACE_TEXT,
          XML_USE_SPREADSHEET_OBJECTS,
          XML_TOK_INDEXSOURCE_USE_SHEET },
    { XML_NAMESPACE_TEXT,
          XML_USE_CHART_OBJECTS,
          XML_TOK_INDEXSOURCE_USE_CHART },
    { XML_NAMESPACE_TEXT,
          XML_USE_DRAW_OBJECTS,
          XML_TOK_INDEXSOURCE_USE_DRAW },
    { XML_NAMESPACE_TEXT,
          XML_USE_IMAGE_OBJECTS,
          XML_TOK_INDEXSOURCE_USE_IMAGE },
    { XML_NAMESPACE_TEXT,
          XML_USE_MATH_OBJECTS,
          XML_TOK_INDEXSOURCE_USE_MATH },
    { XML_NAMESPACE_TEXT,
          XML_MAIN_ENTRY_STYLE_NAME,
          XML_TOK_INDEXSOURCE_MAIN_ENTRY_STYLE },
    { XML_NAMESPACE_TEXT,
          XML_IGNORE_CASE, 
          XML_TOK_INDEXSOURCE_IGNORE_CASE },
    { XML_NAMESPACE_TEXT,
          XML_ALPHABETICAL_SEPARATORS, 
          XML_TOK_INDEXSOURCE_SEPARATORS },
    { XML_NAMESPACE_TEXT,
          XML_COMBINE_ENTRIES,
          XML_TOK_INDEXSOURCE_COMBINE_ENTRIES },
    { XML_NAMESPACE_TEXT,
          XML_COMBINE_ENTRIES_WITH_DASH,
          XML_TOK_INDEXSOURCE_COMBINE_WITH_DASH },
    { XML_NAMESPACE_TEXT,
          XML_USE_KEYS_AS_ENTRIES,
          XML_TOK_INDEXSOURCE_KEYS_AS_ENTRIES },
    { XML_NAMESPACE_TEXT,
          XML_COMBINE_ENTRIES_WITH_PP,
          XML_TOK_INDEXSOURCE_COMBINE_WITH_PP },
    { XML_NAMESPACE_TEXT,
          XML_CAPITALIZE_ENTRIES,
          XML_TOK_INDEXSOURCE_CAPITALIZE },
    { XML_NAMESPACE_TEXT,
          XML_USE_OBJECTS,
          XML_TOK_INDEXSOURCE_USE_OBJECTS },
    { XML_NAMESPACE_TEXT,
          XML_USE_GRAPHICS,
          XML_TOK_INDEXSOURCE_USE_GRAPHICS },
    { XML_NAMESPACE_TEXT,
          XML_USE_TABLES, 
          XML_TOK_INDEXSOURCE_USE_TABLES },
    { XML_NAMESPACE_TEXT,
          XML_USE_FLOATING_FRAMES, 
          XML_TOK_INDEXSOURCE_USE_FRAMES },
    { XML_NAMESPACE_TEXT,
          XML_COPY_OUTLINE_LEVELS,
          XML_TOK_INDEXSOURCE_COPY_OUTLINE_LEVELS },
    { XML_NAMESPACE_TEXT,
          XML_USE_CAPTION,
          XML_TOK_INDEXSOURCE_USE_CAPTION },
    { XML_NAMESPACE_TEXT,
          XML_CAPTION_SEQUENCE_NAME,
          XML_TOK_INDEXSOURCE_SEQUENCE_NAME },
    { XML_NAMESPACE_TEXT,
          XML_CAPTION_SEQUENCE_FORMAT,
          XML_TOK_INDEXSOURCE_SEQUENCE_FORMAT },
    { XML_NAMESPACE_TEXT,
          XML_COMMA_SEPARATED,
          XML_TOK_INDEXSOURCE_COMMA_SEPARATED },
    { XML_NAMESPACE_TEXT,
          XML_USE_INDEX_SOURCE_STYLES,
          XML_TOK_INDEXSOURCE_USE_INDEX_SOURCE_STYLES },
    { XML_NAMESPACE_TEXT, XML_SORT_ALGORITHM, 
          XML_TOK_INDEXSOURCE_SORT_ALGORITHM },
    { XML_NAMESPACE_FO, XML_LANGUAGE, XML_TOK_INDEXSOURCE_LANGUAGE },
    { XML_NAMESPACE_FO, XML_COUNTRY, XML_TOK_INDEXSOURCE_COUNTRY },
    { XML_NAMESPACE_TEXT, XML_INDEX_NAME, XML_TOK_INDEXSOURCE_USER_INDEX_NAME },
    { XML_NAMESPACE_TEXT, 
          XML_USE_OUTLINE_LEVEL, 
          XML_TOK_INDEXSOURCE_USE_OUTLINE_LEVEL},

    XML_TOKEN_MAP_END
};


TYPEINIT1( XMLIndexSourceBaseContext, SvXMLImportContext );

XMLIndexSourceBaseContext::XMLIndexSourceBaseContext(
    SvXMLImport& rImport, 
    sal_uInt16 nPrfx,
    const OUString& rLocalName,
    Reference<XPropertySet> & rPropSet,
    sal_Bool bLevelFormats) :
        SvXMLImportContext(rImport, nPrfx, rLocalName),
        rIndexPropertySet(rPropSet),
        bChapterIndex(sal_False),
        bRelativeTabs(sal_True),
        bUseLevelFormats(bLevelFormats),
       sCreateFromChapter(RTL_CONSTASCII_USTRINGPARAM(sAPI_CreateFromChapter)),
      sIsRelativeTabstops(RTL_CONSTASCII_USTRINGPARAM(sAPI_IsRelativeTabstops))
{
}

XMLIndexSourceBaseContext::~XMLIndexSourceBaseContext()
{
}

void XMLIndexSourceBaseContext::StartElement(
    const Reference<XAttributeList> & xAttrList)
{
    SvXMLTokenMap aTokenMap(aIndexSourceTokenMap);

    // process attributes
    sal_Int16 nLength = xAttrList->getLength();
    for(sal_Int16 i=0; i<nLength; i++) 
    {
        // map to IndexSourceParamEnum
        OUString sLocalName;
        sal_uInt16 nPrefix = GetImport().GetNamespaceMap().
            GetKeyByAttrName( xAttrList->getNameByIndex(i), &sLocalName );
        sal_uInt16 nToken = aTokenMap.Get(nPrefix, sLocalName);

        // process attribute
        ProcessAttribute((enum IndexSourceParamEnum)nToken, 
                         xAttrList->getValueByIndex(i));
    }
}

void XMLIndexSourceBaseContext::ProcessAttribute(
    enum IndexSourceParamEnum eParam, 
    const OUString& rValue)
{
    switch (eParam)
    {
        case XML_TOK_INDEXSOURCE_INDEX_SCOPE:
            if ( IsXMLToken( rValue, XML_CHAPTER ) )
            {
                bChapterIndex = sal_True;
            }
            break;

        case XML_TOK_INDEXSOURCE_RELATIVE_TABS:
        {
            sal_Bool bTmp;
            if (SvXMLUnitConverter::convertBool(bTmp, rValue))
            {
                bRelativeTabs = bTmp;
            }
            break;
        }

        default:
            // unknown attribute -> ignore
            break;
    }
}

void XMLIndexSourceBaseContext::EndElement()
{
    Any aAny;

    aAny.setValue(&bRelativeTabs, ::getBooleanCppuType());
    rIndexPropertySet->setPropertyValue(sIsRelativeTabstops, aAny);

    aAny.setValue(&bChapterIndex, ::getBooleanCppuType());
    rIndexPropertySet->setPropertyValue(sCreateFromChapter, aAny);
}

SvXMLImportContext* XMLIndexSourceBaseContext::CreateChildContext( 
    sal_uInt16 nPrefix,
    const OUString& rLocalName,
    const Reference<XAttributeList> & xAttrList )
{
    SvXMLImportContext* pContext = NULL;

    if (XML_NAMESPACE_TEXT == nPrefix)
    {
        if ( IsXMLToken( rLocalName, XML_INDEX_TITLE_TEMPLATE ) )
        {
            pContext = new XMLIndexTitleTemplateContext(GetImport(),
                                                        rIndexPropertySet,
                                                        nPrefix, rLocalName);
        }
        else if ( bUseLevelFormats && 
                  IsXMLToken( rLocalName, XML_INDEX_SOURCE_STYLES ) )
        {
            pContext = new XMLIndexTOCStylesContext(GetImport(),
                                                    rIndexPropertySet,
                                                    nPrefix, rLocalName);
        }
        // else: unknown element in text namespace -> ignore
    }
    // else: unknown namespace -> ignore

    // use default context
    if (pContext == NULL)
    {
        pContext = SvXMLImportContext::CreateChildContext(nPrefix, rLocalName, 
                                                          xAttrList);
    }

    return pContext;
}
}//end of namespace binfilter
