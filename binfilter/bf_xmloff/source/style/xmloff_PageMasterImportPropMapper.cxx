/*************************************************************************
 *
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER.
 *
 * Copyright 2000, 2010 Oracle and/or its affiliates.
 *
 * OpenOffice.org - a multi-platform office productivity suite
 *
 * This file is part of OpenOffice.org.
 *
 * OpenOffice.org is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License version 3
 * only, as published by the Free Software Foundation.
 *
 * OpenOffice.org is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License version 3 for more details
 * (a copy is included in the LICENSE file that accompanied this code).
 *
 * You should have received a copy of the GNU Lesser General Public License
 * version 3 along with OpenOffice.org.  If not, see
 * <http://www.openoffice.org/license.html>
 * for a copy of the LGPLv3 License.
 *
 ************************************************************************/

#ifdef _MSC_VER
#pragma hdrstop
#endif

#ifndef _XMLOFF_PAGEMASTERIMPORTPROPMAPPER_HXX
#include "PageMasterImportPropMapper.hxx"
#endif
#ifndef _XMLOFF_PAGEMASTERPROPMAPPER_HXX
#include "PageMasterPropMapper.hxx"
#endif
#ifndef _XMLOFF_PAGEMASTERSTYLEMAP_HXX
#include "PageMasterStyleMap.hxx"
#endif

#ifndef _COM_SUN_STAR_TABLE_BORDERLINE_HPP_
#include <com/sun/star/table/BorderLine.hpp>
#endif
#ifndef _XMLOFF_XMLIMP_HXX
#include "xmlimp.hxx"
#endif
namespace binfilter {

#define XML_LINE_LEFT 0
#define XML_LINE_RIGHT 1
#define XML_LINE_TOP 2
#define XML_LINE_BOTTOM 3

using namespace ::com::sun::star;
using namespace ::com::sun::star::uno;
using namespace ::com::sun::star::container;

PageMasterImportPropertyMapper::PageMasterImportPropertyMapper(
        const UniReference< XMLPropertySetMapper >& rMapper,
        SvXMLImport& rImp ) :
    SvXMLImportPropertyMapper( rMapper, rImp ),
    rImport( rImp )
{
}

PageMasterImportPropertyMapper::~PageMasterImportPropertyMapper()
{
}

sal_Bool PageMasterImportPropertyMapper::handleSpecialItem(
        XMLPropertyState& rProperty,
        ::std::vector< XMLPropertyState >& rProperties,
        const ::rtl::OUString& rValue,
        const SvXMLUnitConverter& rUnitConverter,
        const SvXMLNamespaceMap& rNamespaceMap ) const
{
    sal_Bool bRet = sal_False;
    sal_Int16 nContextID =
            getPropertySetMapper()->GetEntryContextId(rProperty.mnIndex);

    if( CTF_PM_REGISTER_STYLE==nContextID )
    {
        Reference < XNameContainer > xParaStyles = 
            rImport.GetTextImport()->GetParaStyles();
        if( xParaStyles.is() && xParaStyles->hasByName( rValue ) )
        {
            rProperty.maValue <<= rValue;
            bRet = sal_True;
        }
    }
    else
    {
        bRet = SvXMLImportPropertyMapper::handleSpecialItem( 
                    rProperty, rProperties, rValue,
                    rUnitConverter, rNamespaceMap );
    }

    return bRet;
}


void PageMasterImportPropertyMapper::finished(::std::vector< XMLPropertyState >& rProperties, sal_Int32 nStartIndex, sal_Int32 nEndIndex ) const
{
    SvXMLImportPropertyMapper::finished(rProperties, nStartIndex, nEndIndex);
    XMLPropertyState* pAllPaddingProperty = NULL;
    XMLPropertyState* pPadding[4] = { NULL, NULL, NULL, NULL };
    XMLPropertyState* pNewPadding[4] = { NULL, NULL, NULL, NULL };
    XMLPropertyState* pAllBorderProperty = NULL;
    XMLPropertyState* pBorders[4] = { NULL, NULL, NULL, NULL };
    XMLPropertyState* pNewBorders[4] = { NULL, NULL, NULL, NULL };
    XMLPropertyState* pAllBorderWidthProperty = NULL;
    XMLPropertyState* pBorderWidths[4] = { NULL, NULL, NULL, NULL };
    XMLPropertyState* pAllHeaderPaddingProperty = NULL;
    XMLPropertyState* pHeaderPadding[4] = { NULL, NULL, NULL, NULL };
    XMLPropertyState* pHeaderNewPadding[4] = { NULL, NULL, NULL, NULL };
    XMLPropertyState* pAllHeaderBorderProperty = NULL;
    XMLPropertyState* pHeaderBorders[4] = { NULL, NULL, NULL, NULL };
    XMLPropertyState* pHeaderNewBorders[4] = { NULL, NULL, NULL, NULL };
    XMLPropertyState* pAllHeaderBorderWidthProperty = NULL;
    XMLPropertyState* pHeaderBorderWidths[4] = { NULL, NULL, NULL, NULL };
    XMLPropertyState* pAllFooterPaddingProperty = NULL;
    XMLPropertyState* pFooterPadding[4] = { NULL, NULL, NULL, NULL };
    XMLPropertyState* pFooterNewPadding[4] = { NULL, NULL, NULL, NULL };
    XMLPropertyState* pAllFooterBorderProperty = NULL;
    XMLPropertyState* pFooterBorders[4] = { NULL, NULL, NULL, NULL };
    XMLPropertyState* pFooterNewBorders[4] = { NULL, NULL, NULL, NULL };
    XMLPropertyState* pAllFooterBorderWidthProperty = NULL;
    XMLPropertyState* pFooterBorderWidths[4] = { NULL, NULL, NULL, NULL };
    XMLPropertyState* pHeaderHeight = NULL;
    XMLPropertyState* pHeaderMinHeight = NULL;
    XMLPropertyState* pHeaderDynamic = NULL;
    XMLPropertyState* pFooterHeight = NULL;
    XMLPropertyState* pFooterMinHeight = NULL;
    XMLPropertyState* pFooterDynamic = NULL;
    ::std::vector< XMLPropertyState >::iterator property = rProperties.begin();
    for (property; property != rProperties.end(); property++)
    {
        sal_Int16 nContextID = getPropertySetMapper()->GetEntryContextId(property->mnIndex);
        if (property->mnIndex >= nStartIndex && property->mnIndex < nEndIndex)
        {
            switch (nContextID)
            {
                case CTF_PM_PADDINGALL					: pAllPaddingProperty = &(*property); break;
                case CTF_PM_PADDINGLEFT					: pPadding[XML_LINE_LEFT] = &(*property); break;
                case CTF_PM_PADDINGRIGHT				: pPadding[XML_LINE_RIGHT] = &(*property); break;
                case CTF_PM_PADDINGTOP					: pPadding[XML_LINE_TOP] = &(*property); break;
                case CTF_PM_PADDINGBOTTOM				: pPadding[XML_LINE_BOTTOM] = &(*property); break;
                case CTF_PM_BORDERALL					: pAllBorderProperty = &(*property); break;
                case CTF_PM_BORDERLEFT					: pBorders[XML_LINE_LEFT] = &(*property); break;
                case CTF_PM_BORDERRIGHT					: pBorders[XML_LINE_RIGHT] = &(*property); break;
                case CTF_PM_BORDERTOP					: pBorders[XML_LINE_TOP] = &(*property); break;
                case CTF_PM_BORDERBOTTOM				: pBorders[XML_LINE_BOTTOM] = &(*property); break;
                case CTF_PM_BORDERWIDTHALL				: pAllBorderWidthProperty = &(*property); break;
                case CTF_PM_BORDERWIDTHLEFT				: pBorderWidths[XML_LINE_LEFT] = &(*property); break;
                case CTF_PM_BORDERWIDTHRIGHT			: pBorderWidths[XML_LINE_RIGHT] = &(*property); break;
                case CTF_PM_BORDERWIDTHTOP				: pBorderWidths[XML_LINE_TOP] = &(*property); break;
                case CTF_PM_BORDERWIDTHBOTTOM			: pBorderWidths[XML_LINE_BOTTOM] = &(*property); break;
                case CTF_PM_HEADERPADDINGALL			: pAllHeaderPaddingProperty = &(*property); break;
                case CTF_PM_HEADERPADDINGLEFT			: pHeaderPadding[XML_LINE_LEFT] = &(*property); break;
                case CTF_PM_HEADERPADDINGRIGHT			: pHeaderPadding[XML_LINE_RIGHT] = &(*property); break;
                case CTF_PM_HEADERPADDINGTOP			: pHeaderPadding[XML_LINE_TOP] = &(*property); break;
                case CTF_PM_HEADERPADDINGBOTTOM			: pHeaderPadding[XML_LINE_BOTTOM] = &(*property); break;
                case CTF_PM_HEADERBORDERALL				: pAllHeaderBorderProperty = &(*property); break;
                case CTF_PM_HEADERBORDERLEFT			: pHeaderBorders[XML_LINE_LEFT] = &(*property); break;
                case CTF_PM_HEADERBORDERRIGHT			: pHeaderBorders[XML_LINE_RIGHT] = &(*property); break;
                case CTF_PM_HEADERBORDERTOP				: pHeaderBorders[XML_LINE_TOP] = &(*property); break;
                case CTF_PM_HEADERBORDERBOTTOM			: pHeaderBorders[XML_LINE_BOTTOM] = &(*property); break;
                case CTF_PM_HEADERBORDERWIDTHALL		: pAllHeaderBorderWidthProperty = &(*property); break;
                case CTF_PM_HEADERBORDERWIDTHLEFT		: pHeaderBorderWidths[XML_LINE_LEFT] = &(*property); break;
                case CTF_PM_HEADERBORDERWIDTHRIGHT		: pHeaderBorderWidths[XML_LINE_RIGHT] = &(*property); break;
                case CTF_PM_HEADERBORDERWIDTHTOP		: pHeaderBorderWidths[XML_LINE_TOP] = &(*property); break;
                case CTF_PM_HEADERBORDERWIDTHBOTTOM		: pHeaderBorderWidths[XML_LINE_BOTTOM] = &(*property); break;
                case CTF_PM_FOOTERPADDINGALL			: pAllFooterPaddingProperty = &(*property); break;
                case CTF_PM_FOOTERPADDINGLEFT			: pFooterPadding[XML_LINE_LEFT] = &(*property); break;
                case CTF_PM_FOOTERPADDINGRIGHT			: pFooterPadding[XML_LINE_RIGHT] = &(*property); break;
                case CTF_PM_FOOTERPADDINGTOP			: pFooterPadding[XML_LINE_TOP] = &(*property); break;
                case CTF_PM_FOOTERPADDINGBOTTOM			: pFooterPadding[XML_LINE_BOTTOM] = &(*property); break;
                case CTF_PM_FOOTERBORDERALL				: pAllFooterBorderProperty = &(*property); break;
                case CTF_PM_FOOTERBORDERLEFT			: pFooterBorders[XML_LINE_LEFT] = &(*property); break;
                case CTF_PM_FOOTERBORDERRIGHT			: pFooterBorders[XML_LINE_RIGHT] = &(*property); break;
                case CTF_PM_FOOTERBORDERTOP				: pFooterBorders[XML_LINE_TOP] = &(*property); break;
                case CTF_PM_FOOTERBORDERBOTTOM			: pFooterBorders[XML_LINE_BOTTOM] = &(*property); break;
                case CTF_PM_FOOTERBORDERWIDTHALL		: pAllFooterBorderWidthProperty = &(*property); break;
                case CTF_PM_FOOTERBORDERWIDTHLEFT		: pFooterBorderWidths[XML_LINE_LEFT] = &(*property); break;
                case CTF_PM_FOOTERBORDERWIDTHRIGHT		: pFooterBorderWidths[XML_LINE_RIGHT] = &(*property); break;
                case CTF_PM_FOOTERBORDERWIDTHTOP		: pFooterBorderWidths[XML_LINE_TOP] = &(*property); break;
                case CTF_PM_FOOTERBORDERWIDTHBOTTOM		: pFooterBorderWidths[XML_LINE_BOTTOM] = &(*property); break;
                case CTF_PM_HEADERHEIGHT				: pHeaderHeight = &(*property); break;
                case CTF_PM_HEADERMINHEIGHT				: pHeaderMinHeight = &(*property); break;
                case CTF_PM_FOOTERHEIGHT				: pFooterHeight = &(*property); break;
                case CTF_PM_FOOTERMINHEIGHT				: pFooterMinHeight = &(*property); break;
            }
        }
    }

    sal_uInt16 i;
    for (i = 0; i < 4; i++)
    {
        if (pAllPaddingProperty && !pPadding[i])
            pNewPadding[i] = new XMLPropertyState(pAllPaddingProperty->mnIndex + 1 + i, pAllPaddingProperty->maValue);
        if (pAllBorderProperty && !pBorders[i])
        {
            pNewBorders[i] = new XMLPropertyState(pAllBorderProperty->mnIndex + 1 + i, pAllBorderProperty->maValue);
            pBorders[i] = pNewBorders[i];
        }
        if( !pBorderWidths[i] )
            pBorderWidths[i] = pAllBorderWidthProperty;
        else
            pBorderWidths[i]->mnIndex = -1;
        if( pBorders[i] )
        {
            table::BorderLine aBorderLine;
            pBorders[i]->maValue >>= aBorderLine;
             if( pBorderWidths[i] )
            {
                table::BorderLine aBorderLineWidth;
                pBorderWidths[i]->maValue >>= aBorderLineWidth;
                aBorderLine.OuterLineWidth = aBorderLineWidth.OuterLineWidth;
                aBorderLine.InnerLineWidth = aBorderLineWidth.InnerLineWidth;
                aBorderLine.LineDistance = aBorderLineWidth.LineDistance;
                pBorders[i]->maValue <<= aBorderLine;
            }
        }
        if (pAllHeaderPaddingProperty && !pHeaderPadding[i])
            pHeaderNewPadding[i] = new XMLPropertyState(pAllHeaderPaddingProperty->mnIndex + 1 + i, pAllHeaderPaddingProperty->maValue);
        if (pAllHeaderBorderProperty && !pHeaderBorders[i])
            pHeaderNewBorders[i] = new XMLPropertyState(pAllHeaderBorderProperty->mnIndex + 1 + i, pAllHeaderBorderProperty->maValue);
        if( !pHeaderBorderWidths[i] )
            pHeaderBorderWidths[i] = pAllHeaderBorderWidthProperty;
        else
            pHeaderBorderWidths[i]->mnIndex = -1;
        if( pHeaderBorders[i] )
        {
            table::BorderLine aBorderLine;
            pHeaderBorders[i]->maValue >>= aBorderLine;
             if( pHeaderBorderWidths[i] )
            {
                table::BorderLine aBorderLineWidth;
                pHeaderBorderWidths[i]->maValue >>= aBorderLineWidth;
                aBorderLine.OuterLineWidth = aBorderLineWidth.OuterLineWidth;
                aBorderLine.InnerLineWidth = aBorderLineWidth.InnerLineWidth;
                aBorderLine.LineDistance = aBorderLineWidth.LineDistance;
                pHeaderBorders[i]->maValue <<= aBorderLine;
            }
        }
        if (pAllFooterPaddingProperty && !pFooterPadding[i])
            pFooterNewPadding[i] = new XMLPropertyState(pAllFooterPaddingProperty->mnIndex + 1 + i, pAllFooterPaddingProperty->maValue);
        if (pAllFooterBorderProperty && !pFooterBorders[i])
            pFooterNewBorders[i] = new XMLPropertyState(pAllFooterBorderProperty->mnIndex + 1 + i, pAllFooterBorderProperty->maValue);
        if( !pFooterBorderWidths[i] )
            pFooterBorderWidths[i] = pAllFooterBorderWidthProperty;
        else
            pFooterBorderWidths[i]->mnIndex = -1;
        if( pFooterBorders[i] )
        {
            table::BorderLine aBorderLine;
            pFooterBorders[i]->maValue >>= aBorderLine;
             if( pFooterBorderWidths[i] )
            {
                table::BorderLine aBorderLineWidth;
                pFooterBorderWidths[i]->maValue >>= aBorderLineWidth;
                aBorderLine.OuterLineWidth = aBorderLineWidth.OuterLineWidth;
                aBorderLine.InnerLineWidth = aBorderLineWidth.InnerLineWidth;
                aBorderLine.LineDistance = aBorderLineWidth.LineDistance;
                pFooterBorders[i]->maValue <<= aBorderLine;
            }
        }
    }

    if (pHeaderHeight)
    {
        sal_Bool bValue(sal_False);
        uno::Any aAny;
        aAny.setValue( &bValue, ::getBooleanCppuType() );
        pHeaderDynamic = new XMLPropertyState(pHeaderHeight->mnIndex + 2, aAny);
    }
    if (pHeaderMinHeight)
    {
        sal_Bool bValue(sal_True);
        uno::Any aAny;
        aAny.setValue( &bValue, ::getBooleanCppuType() );
        pHeaderDynamic = new XMLPropertyState(pHeaderMinHeight->mnIndex + 1, aAny);
    }
    if (pFooterHeight)
    {
        sal_Bool bValue(sal_False);
        uno::Any aAny;
        aAny.setValue( &bValue, ::getBooleanCppuType() );
        pFooterDynamic = new XMLPropertyState(pFooterHeight->mnIndex + 2, aAny);
    }
    if (pFooterMinHeight)
    {
        sal_Bool bValue(sal_True);
        uno::Any aAny;
        aAny.setValue( &bValue, ::getBooleanCppuType() );
        pFooterDynamic = new XMLPropertyState(pFooterMinHeight->mnIndex + 1, aAny);
    }
    for (i = 0; i < 4; i++)
    {
        if (pNewPadding[i])
        {
            rProperties.push_back(*pNewPadding[i]);
            delete pNewPadding[i];
        }
        if (pNewBorders[i])
        {
            rProperties.push_back(*pNewBorders[i]);
            delete pNewBorders[i];
        }
        if (pHeaderNewPadding[i])
        {
            rProperties.push_back(*pHeaderNewPadding[i]);
            delete pHeaderNewPadding[i];
        }
        if (pHeaderNewBorders[i])
        {
            rProperties.push_back(*pHeaderNewBorders[i]);
            delete pHeaderNewBorders[i];
        }
        if (pFooterNewPadding[i])
        {
            rProperties.push_back(*pFooterNewPadding[i]);
            delete pFooterNewPadding[i];
        }
        if (pFooterNewBorders[i])
        {
            rProperties.push_back(*pFooterNewBorders[i]);
            delete pFooterNewBorders[i];
        }
    }
    if(pHeaderDynamic)
    {
        rProperties.push_back(*pHeaderDynamic);
        delete pHeaderDynamic;
    }
    if(pFooterDynamic)
    {
        rProperties.push_back(*pFooterDynamic);
        delete pFooterDynamic;
    }
}

}//end of namespace binfilter
