/* -*- Mode: C++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */
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

#include "ximpstyl.hxx"
#include "XMLShapeStyleContext.hxx"
#include "xmlnmspe.hxx"
#include "xmluconv.hxx"
#include "ximpnote.hxx"

#include <tools/debug.hxx>
#include <com/sun/star/presentation/XPresentationPage.hpp>
#include <com/sun/star/drawing/XDrawPages.hpp>
#include <com/sun/star/beans/XPropertyState.hpp>
#include <comphelper/namecontainer.hxx>
#include <com/sun/star/presentation/XHandoutMasterSupplier.hpp>

#include "xmlprcon.hxx"

#include <bf_svtools/zforlist.hxx>

#include "PropertySetMerger.hxx"
#include "sdpropls.hxx"
#include "layerimp.hxx"

#include "XMLGraphicsDefaultStyle.hxx"
#include "XMLNumberStylesImport.hxx"

namespace binfilter {

using namespace ::com::sun::star;
using namespace ::com::sun::star::uno;
using namespace ::com::sun::star::xml::sax;
using namespace ::binfilter::xmloff::token;

using rtl::OUString;

//////////////////////////////////////////////////////////////////////////////

class SdXMLDrawingPagePropertySetContext : public SvXMLPropertySetContext
{
public:

    TYPEINFO();

    SdXMLDrawingPagePropertySetContext( SvXMLImport& rInImport, sal_uInt16 nPrfx,
                const ::rtl::OUString& rLName,
                 const ::com::sun::star::uno::Reference<
                         ::com::sun::star::xml::sax::XAttributeList >& xAttrList,
                 ::std::vector< XMLPropertyState > &rProps,
                 const UniReference < SvXMLImportPropertyMapper > &rMap );

    virtual ~SdXMLDrawingPagePropertySetContext();

    virtual SvXMLImportContext *CreateChildContext( USHORT nInPrefix,
                                   const ::rtl::OUString& rLocalName,
                                   const ::com::sun::star::uno::Reference< ::com::sun::star::xml::sax::XAttributeList >& xAttrList,
                                   ::std::vector< XMLPropertyState > &rInProperties,
                                   const XMLPropertyState& rProp);
};

TYPEINIT1( SdXMLDrawingPagePropertySetContext, SvXMLPropertySetContext );

SdXMLDrawingPagePropertySetContext::SdXMLDrawingPagePropertySetContext(
                 SvXMLImport& rInImport, sal_uInt16 nPrfx,
                 const OUString& rLName,
                 const uno::Reference< xml::sax::XAttributeList > & xAttrList,
                 ::std::vector< XMLPropertyState > &rProps,
                 const UniReference < SvXMLImportPropertyMapper > &rMap ) :
    SvXMLPropertySetContext( rInImport, nPrfx, rLName, xAttrList, rProps, rMap )
{
}

SdXMLDrawingPagePropertySetContext::~SdXMLDrawingPagePropertySetContext()
{
}

SvXMLImportContext *SdXMLDrawingPagePropertySetContext::CreateChildContext(
                   sal_uInt16 nInPrefix,
                   const OUString& rLocalName,
                   const uno::Reference< xml::sax::XAttributeList > & xAttrList,
                   ::std::vector< XMLPropertyState > &rInProperties,
                   const XMLPropertyState& rProp )
{
    SvXMLImportContext *pContext = 0;

    switch( xMapper->getPropertySetMapper()->GetEntryContextId( rProp.mnIndex ) )
    {
    case CTF_PAGE_SOUND_URL:
    {
        const sal_Int16 nAttrCount = xAttrList.is() ? xAttrList->getLength() : 0;
        for(sal_Int16 i=0; i < nAttrCount; i++)
        {
            OUString aLclLocalName;
            sal_uInt16 nLclPrefix = GetImport().GetNamespaceMap().GetKeyByAttrName(xAttrList->getNameByIndex(i), &aLclLocalName);

            if( (nLclPrefix == XML_NAMESPACE_XLINK) && IsXMLToken( aLclLocalName, XML_HREF ) )
            {
                uno::Any aAny;
                aAny <<= GetImport().GetAbsoluteReference( xAttrList->getValueByIndex(i) );
                XMLPropertyState aPropState( rProp.mnIndex, aAny );
                rInProperties.push_back( aPropState );
            }
        }
        break;
    }
    }

    if( !pContext )
        pContext = SvXMLPropertySetContext::CreateChildContext( nInPrefix, rLocalName,
                                                            xAttrList,
                                                            rInProperties, rProp );

    return pContext;
}

//////////////////////////////////////////////////////////////////////////////

class SdXMLDrawingPageStyleContext : public XMLPropStyleContext
{
public:
    TYPEINFO();

    SdXMLDrawingPageStyleContext(
        SvXMLImport& rInImport,
        sal_uInt16 nPrfx,
        const ::rtl::OUString& rLName,
        const ::com::sun::star::uno::Reference< ::com::sun::star::xml::sax::XAttributeList >& xAttrList,
        SvXMLStylesContext& rStyles,
        sal_uInt16 nFamily = XML_STYLE_FAMILY_SD_DRAWINGPAGE_ID);
    virtual ~SdXMLDrawingPageStyleContext();

    SvXMLImportContext * CreateChildContext(
        sal_uInt16 nPrefix,
        const ::rtl::OUString& rLocalName,
        const ::com::sun::star::uno::Reference< ::com::sun::star::xml::sax::XAttributeList > & xAttrList );
};

TYPEINIT1( SdXMLDrawingPageStyleContext, XMLPropStyleContext );

SdXMLDrawingPageStyleContext::SdXMLDrawingPageStyleContext(
    SvXMLImport& rInImport,
    sal_uInt16 nPrfx,
    const OUString& rLName,
    const uno::Reference< xml::sax::XAttributeList >& xAttrList,
    SvXMLStylesContext& rStyles,
    sal_uInt16 nInFamily)
:	XMLPropStyleContext(rInImport, nPrfx, rLName, xAttrList, rStyles, nInFamily )
{
}

SdXMLDrawingPageStyleContext::~SdXMLDrawingPageStyleContext()
{
}

SvXMLImportContext *SdXMLDrawingPageStyleContext::CreateChildContext(
        sal_uInt16 nInPrefix,
        const OUString& rLocalName,
        const uno::Reference< xml::sax::XAttributeList > & xAttrList )
{
    SvXMLImportContext *pContext = 0;

    if( XML_NAMESPACE_STYLE == nInPrefix &&
        IsXMLToken( rLocalName, XML_PROPERTIES ) )
    {
        UniReference < SvXMLImportPropertyMapper > xImpPrMap =
            GetStyles()->GetImportPropertyMapper( GetFamily() );
        if( xImpPrMap.is() )
            pContext = new SdXMLDrawingPagePropertySetContext( GetImport(), nInPrefix,
                                                    rLocalName, xAttrList,
                                                    GetProperties(),
                                                    xImpPrMap );
    }

    if( !pContext )
        pContext = XMLPropStyleContext::CreateChildContext( nInPrefix, rLocalName,
                                                          xAttrList );

    return pContext;
}

//////////////////////////////////////////////////////////////////////////////

TYPEINIT1( SdXMLPageMasterStyleContext, SvXMLStyleContext );

SdXMLPageMasterStyleContext::SdXMLPageMasterStyleContext(
    SdXMLImport& rInImport,
    sal_uInt16 nPrfx,
    const OUString& rLName,
    const uno::Reference< xml::sax::XAttributeList>& xAttrList)
:	SvXMLStyleContext(rInImport, nPrfx, rLName, xAttrList, XML_STYLE_FAMILY_SD_PAGEMASTERSTYLECONEXT_ID),
    mnBorderBottom( 0L ),
    mnBorderLeft( 0L ),
    mnBorderRight( 0L ),
    mnBorderTop( 0L ),
    mnWidth( 0L ),
    mnHeight( 0L ),
    meOrientation(GetSdImport().IsDraw() ? view::PaperOrientation_PORTRAIT : view::PaperOrientation_LANDSCAPE)
{
    // set family to something special at SvXMLStyleContext
    // for differences in search-methods

    sal_Int16 nAttrCount = xAttrList.is() ? xAttrList->getLength() : 0;
    for(sal_Int16 i=0; i < nAttrCount; i++)
    {
        OUString sAttrName = xAttrList->getNameByIndex(i);
        OUString aLclLocalName;
        sal_uInt16 nLclPrefix = GetSdImport().GetNamespaceMap().GetKeyByAttrName(sAttrName, &aLclLocalName);
        OUString sValue = xAttrList->getValueByIndex(i);
        const SvXMLTokenMap& rAttrTokenMap = GetSdImport().GetPageMasterStyleAttrTokenMap();

        switch(rAttrTokenMap.Get(nLclPrefix, aLclLocalName))
        {
            case XML_TOK_PAGEMASTERSTYLE_MARGIN_TOP:
            {
                GetSdImport().GetMM100UnitConverter().convertMeasure(mnBorderTop, sValue);
                break;
            }
            case XML_TOK_PAGEMASTERSTYLE_MARGIN_BOTTOM:
            {
                GetSdImport().GetMM100UnitConverter().convertMeasure(mnBorderBottom, sValue);
                break;
            }
            case XML_TOK_PAGEMASTERSTYLE_MARGIN_LEFT:
            {
                GetSdImport().GetMM100UnitConverter().convertMeasure(mnBorderLeft, sValue);
                break;
            }
            case XML_TOK_PAGEMASTERSTYLE_MARGIN_RIGHT:
            {
                GetSdImport().GetMM100UnitConverter().convertMeasure(mnBorderRight, sValue);
                break;
            }
            case XML_TOK_PAGEMASTERSTYLE_PAGE_WIDTH:
            {
                GetSdImport().GetMM100UnitConverter().convertMeasure(mnWidth, sValue);
                break;
            }
            case XML_TOK_PAGEMASTERSTYLE_PAGE_HEIGHT:
            {
                GetSdImport().GetMM100UnitConverter().convertMeasure(mnHeight, sValue);
                break;
            }
            case XML_TOK_PAGEMASTERSTYLE_PAGE_ORIENTATION:
            {
                if( IsXMLToken( sValue, XML_PORTRAIT ) )
                    meOrientation = view::PaperOrientation_PORTRAIT;
                else
                    meOrientation = view::PaperOrientation_LANDSCAPE;
                break;
            }
        }
    }
}

//////////////////////////////////////////////////////////////////////////////

SdXMLPageMasterStyleContext::~SdXMLPageMasterStyleContext()
{
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

TYPEINIT1( SdXMLPageMasterContext, SvXMLStyleContext );

SdXMLPageMasterContext::SdXMLPageMasterContext(
    SdXMLImport& rInImport,
    sal_uInt16 nPrfx,
    const OUString& rLName,
    const uno::Reference< xml::sax::XAttributeList>& xAttrList)
:	SvXMLStyleContext(rInImport, nPrfx, rLName, xAttrList, XML_STYLE_FAMILY_SD_PAGEMASTERCONEXT_ID),
    mpPageMasterStyle( 0L )
{
    // set family to something special at SvXMLStyleContext
    // for differences in search-methods

    sal_Int16 nAttrCount = xAttrList.is() ? xAttrList->getLength() : 0;
    for(sal_Int16 i=0; i < nAttrCount; i++)
    {
        OUString sAttrName = xAttrList->getNameByIndex(i);
        OUString aLclLocalName;
        sal_uInt16 nLclPrefix = GetSdImport().GetNamespaceMap().GetKeyByAttrName(sAttrName, &aLclLocalName);
        OUString sValue = xAttrList->getValueByIndex(i);
        const SvXMLTokenMap& rAttrTokenMap = GetSdImport().GetPageMasterAttrTokenMap();

        switch(rAttrTokenMap.Get(nLclPrefix, aLclLocalName))
        {
            case XML_TOK_PAGEMASTER_NAME:
            {
                msName = sValue;
                break;
            }
        }
    }
}

//////////////////////////////////////////////////////////////////////////////

SdXMLPageMasterContext::~SdXMLPageMasterContext()
{
    // release remembered contexts, they are no longer needed
    if(mpPageMasterStyle)
    {
        mpPageMasterStyle->ReleaseRef();
        mpPageMasterStyle = 0L;
    }
}

//////////////////////////////////////////////////////////////////////////////

SvXMLImportContext *SdXMLPageMasterContext::CreateChildContext(
    sal_uInt16 nInPrefix,
    const OUString& rLocalName,
    const uno::Reference< xml::sax::XAttributeList >& xAttrList )
{
    SvXMLImportContext* pContext = 0;

    if(nInPrefix == XML_NAMESPACE_STYLE && IsXMLToken( rLocalName, XML_PROPERTIES) )
    {
        pContext = new SdXMLPageMasterStyleContext(GetSdImport(), nInPrefix, rLocalName, xAttrList);

        // remember SdXMLPresentationPlaceholderContext for later evaluation
        if(pContext)
        {
            pContext->AddRef();
            DBG_ASSERT(!mpPageMasterStyle, "PageMasterStyle is set, there seem to be two of them (!)");
            mpPageMasterStyle = (SdXMLPageMasterStyleContext*)pContext;
        }
    }

    // call base class
    if(!pContext)
        pContext = SvXMLStyleContext::CreateChildContext(nInPrefix, rLocalName, xAttrList);

    return pContext;
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

TYPEINIT1( SdXMLPresentationPageLayoutContext, SvXMLStyleContext );

SdXMLPresentationPageLayoutContext::SdXMLPresentationPageLayoutContext(
    SdXMLImport& rInImport,
    sal_uInt16 nPrfx,
    const OUString& rLName,
    const uno::Reference< xml::sax::XAttributeList >& xAttrList)
:	SvXMLStyleContext(rInImport, nPrfx, rLName, xAttrList, XML_STYLE_FAMILY_SD_PRESENTATIONPAGELAYOUT_ID),
    mnTypeId( 20 ) // AUTOLAYOUT_NONE
{
    // set family to somethiong special at SvXMLStyleContext
    // for differences in search-methods

    sal_Int16 nAttrCount = xAttrList.is() ? xAttrList->getLength() : 0;
    for( sal_Int16 i=0; i < nAttrCount; i++ )
    {
        const OUString& rAttrName = xAttrList->getNameByIndex( i );
        OUString aLclLocalName;
        sal_uInt16 nLclPrefix = GetImport().GetNamespaceMap().GetKeyByAttrName( rAttrName,	&aLclLocalName );

        if(nLclPrefix == XML_NAMESPACE_STYLE && IsXMLToken( aLclLocalName, XML_NAME ) )
        {
            msName = xAttrList->getValueByIndex( i );
        }
    }
}

SdXMLPresentationPageLayoutContext::~SdXMLPresentationPageLayoutContext()
{
}

SvXMLImportContext *SdXMLPresentationPageLayoutContext::CreateChildContext(
    sal_uInt16 nInPrefix,
    const OUString& rLocalName,
    const uno::Reference< xml::sax::XAttributeList >& xAttrList )
{
    SvXMLImportContext* pContext = 0;

    if(nInPrefix == XML_NAMESPACE_PRESENTATION && IsXMLToken( rLocalName, XML_PLACEHOLDER ) )
    {
        // presentation:placeholder inside style:presentation-page-layout context
        pContext = new SdXMLPresentationPlaceholderContext(
            GetSdImport(), nInPrefix, rLocalName, xAttrList);

        // remember SdXMLPresentationPlaceholderContext for later evaluation
        if(pContext)
        {
            pContext->AddRef();
            maList.push_back( (SdXMLPresentationPlaceholderContext*)pContext );
        }
    }

    // call base class
    if(!pContext)
        pContext = SvXMLStyleContext::CreateChildContext(nInPrefix, rLocalName, xAttrList);

    return pContext;
}

void SdXMLPresentationPageLayoutContext::EndElement()
{
    // build presentation page layout type here
    // calc mnTpeId due to content of maList
    // at the moment only use number of types used there
    if( !maList.empty() )
    {
        SdXMLPresentationPlaceholderContext* pObj0 = maList[ 0 ];
        if(pObj0->GetName().equals(OUString(RTL_CONSTASCII_USTRINGPARAM("handout"))))
        {
            switch( maList.size() )
            {
            case 1:
                mnTypeId = 22; // AUTOLAYOUT_HANDOUT1
                break;
            case 2:
                mnTypeId = 23; // AUTOLAYOUT_HANDOUT2
                break;
            case 3:
                mnTypeId = 24; // AUTOLAYOUT_HANDOUT3
                break;
            case 4:
                mnTypeId = 25; // AUTOLAYOUT_HANDOUT4
                break;
            default:
                mnTypeId = 26; // AUTOLAYOUT_HANDOUT6
            }
        }
        else
        {
            switch( maList.size() )
            {
                case 1:
                {
                    mnTypeId = 19; // AUTOLAYOUT_ONLY_TITLE
                    break;
                }
                case 2:
                {
                    SdXMLPresentationPlaceholderContext* pObj1 = maList[ 1 ];

                    if(pObj1->GetName().equals(
                        OUString(RTL_CONSTASCII_USTRINGPARAM("subtitle"))))
                    {
                        mnTypeId = 0; // AUTOLAYOUT_TITLE
                    }
                    else if(pObj1->GetName().equals(
                        OUString(RTL_CONSTASCII_USTRINGPARAM("outline"))))
                    {
                        mnTypeId = 1; // AUTOLAYOUT_ENUM
                    }
                    else if(pObj1->GetName().equals(
                        OUString(RTL_CONSTASCII_USTRINGPARAM("chart"))))
                    {
                        mnTypeId = 2; // AUTOLAYOUT_CHART
                    }
                    else if(pObj1->GetName().equals(
                        OUString(RTL_CONSTASCII_USTRINGPARAM("table"))))
                    {
                        mnTypeId = 8; // AUTOLAYOUT_TAB
                    }
                    else if(pObj1->GetName().equals(
                        OUString(RTL_CONSTASCII_USTRINGPARAM("object"))))
                    {
                        mnTypeId = 11; // AUTOLAYOUT_OBJ
                    }
                    else if(pObj1->GetName().equals(
                        OUString(RTL_CONSTASCII_USTRINGPARAM("vertical_outline"))))
                    {
                        if(pObj0->GetName().equals(OUString(RTL_CONSTASCII_USTRINGPARAM("vertical_title"))))
                        {
                            // AUTOLAYOUT_VERTICAL_TITLE_VERTICAL_OUTLINE
                            mnTypeId = 28;
                        }
                        else
                        {
                            // AUTOLAYOUT_TITLE_VERTICAL_OUTLINE
                            mnTypeId = 29;
                        }
                    }
                    else
                    {
                        mnTypeId = 21; // AUTOLAYOUT_NOTES
                    }
                    break;
                }
                case 3:
                {
                    SdXMLPresentationPlaceholderContext* pObj1 = maList[ 1 ];
                    SdXMLPresentationPlaceholderContext* pObj2 = maList[ 2 ];

                    if(pObj1->GetName().equals(
                        OUString(RTL_CONSTASCII_USTRINGPARAM("outline"))))
                    {
                        if(pObj2->GetName().equals(
                            OUString(RTL_CONSTASCII_USTRINGPARAM("outline"))))
                        {
                            mnTypeId = 3; // AUTOLAYOUT_2TEXT
                        }
                        else if(pObj2->GetName().equals(
                            OUString(RTL_CONSTASCII_USTRINGPARAM("chart"))))
                        {
                            mnTypeId = 4; // AUTOLAYOUT_TEXTCHART
                        }
                        else if(pObj2->GetName().equals(
                            OUString(RTL_CONSTASCII_USTRINGPARAM("graphic"))))
                        {
                            mnTypeId = 6; // AUTOLAYOUT_TEXTCLIP
                        }
                        else
                        {
                            if(pObj1->GetX() < pObj2->GetX())
                            {
                                mnTypeId = 10; // AUTOLAYOUT_TEXTOBJ -> outline left, object right
                            }
                            else
                            {
                                mnTypeId = 17; // AUTOLAYOUT_TEXTOVEROBJ -> outline top, object right
                            }
                        }
                    }
                    else if(pObj1->GetName().equals(
                        OUString(RTL_CONSTASCII_USTRINGPARAM("chart"))))
                    {
                        mnTypeId = 7; // AUTOLAYOUT_CHARTTEXT
                    }
                    else if(pObj1->GetName().equals(
                        OUString(RTL_CONSTASCII_USTRINGPARAM("graphic"))))
                    {
                        if(pObj2->GetName().equals(OUString(RTL_CONSTASCII_USTRINGPARAM("vertical_outline"))))
                        {
                            // AUTOLAYOUT_TITLE_VERTICAL_OUTLINE_CLIPART
                            mnTypeId = 30;
                        }
                        else
                        {
                            mnTypeId = 9; // AUTOLAYOUT_CLIPTEXT
                        }
                    }
                    else if(pObj1->GetName().equals(
                        OUString(RTL_CONSTASCII_USTRINGPARAM("vertical_outline"))))
                    {
                        // AUTOLAYOUT_VERTICAL_TITLE_TEXT_CHART
                        mnTypeId = 27;
                    }
                    else
                    {
                        if(pObj1->GetX() < pObj2->GetX())
                        {
                            mnTypeId = 13; // AUTOLAYOUT_OBJTEXT -> left, right
                        }
                        else
                        {
                            mnTypeId = 14; // AUTOLAYOUT_OBJOVERTEXT -> top, bottom
                        }
                    }
                    break;
                }
                case 4:
                {
                    SdXMLPresentationPlaceholderContext* pObj1 = maList[ 1 ];
                    SdXMLPresentationPlaceholderContext* pObj2 = maList[ 2 ];

                    if(pObj1->GetName().equals(
                        OUString(RTL_CONSTASCII_USTRINGPARAM("object"))))
                    {
                        if(pObj1->GetX() < pObj2->GetX())
                        {
                            mnTypeId = 16; // AUTOLAYOUT_2OBJOVERTEXT
                        }
                        else
                        {
                            mnTypeId = 15; // AUTOLAYOUT_2OBJTEXT
                        }
                    }
                    else
                    {
                        mnTypeId = 12; // AUTOLAYOUT_TEXT2OBJ
                    }
                    break;
                }
                default: // 5 items
                {
                    mnTypeId = 18; // AUTOLAYOUT_4OBJ
                    break;
                }
            }
        }

        // release remembered contexts, they are no longer needed
        for ( size_t i = 0, n = maList.size(); i < n; ++i )
            maList[ i ]->ReleaseRef();
        maList.clear();
    }
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

SdXMLPresentationPlaceholderContext::SdXMLPresentationPlaceholderContext(
    SdXMLImport& rInImport,
    sal_uInt16 nPrfx, const
    OUString& rLName,
    const uno::Reference< xml::sax::XAttributeList>& xAttrList)
:	SvXMLImportContext( rInImport, nPrfx, rLName),
    mnX(0L),
    mnY(0L),
    mnWidth(1L),
    mnHeight(1L)
{
    sal_Int16 nAttrCount = xAttrList.is() ? xAttrList->getLength() : 0;
    for(sal_Int16 i=0; i < nAttrCount; i++)
    {
        OUString sAttrName = xAttrList->getNameByIndex(i);
        OUString aLclLocalName;
        sal_uInt16 nLclPrefix = GetSdImport().GetNamespaceMap().GetKeyByAttrName(sAttrName, &aLclLocalName);
        OUString sValue = xAttrList->getValueByIndex(i);
        const SvXMLTokenMap& rAttrTokenMap = GetSdImport().GetPresentationPlaceholderAttrTokenMap();

        switch(rAttrTokenMap.Get(nLclPrefix, aLclLocalName))
        {
            case XML_TOK_PRESENTATIONPLACEHOLDER_OBJECTNAME:
            {
                msName = sValue;
                break;
            }
            case XML_TOK_PRESENTATIONPLACEHOLDER_X:
            {
                GetSdImport().GetMM100UnitConverter().convertMeasure(mnX, sValue);
                break;
            }
            case XML_TOK_PRESENTATIONPLACEHOLDER_Y:
            {
                GetSdImport().GetMM100UnitConverter().convertMeasure(mnY, sValue);
                break;
            }
            case XML_TOK_PRESENTATIONPLACEHOLDER_WIDTH:
            {
                GetSdImport().GetMM100UnitConverter().convertMeasure(mnWidth, sValue);
                break;
            }
            case XML_TOK_PRESENTATIONPLACEHOLDER_HEIGHT:
            {
                GetSdImport().GetMM100UnitConverter().convertMeasure(mnHeight, sValue);
                break;
            }
        }
    }
}

//////////////////////////////////////////////////////////////////////////////

SdXMLPresentationPlaceholderContext::~SdXMLPresentationPlaceholderContext()
{
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

TYPEINIT1( SdXMLMasterPageContext, SdXMLGenericPageContext );

SdXMLMasterPageContext::SdXMLMasterPageContext(
    SdXMLImport& rInImport,
    sal_uInt16 nPrfx,
    const OUString& rLName,
    const uno::Reference< xml::sax::XAttributeList>& xAttrList,
    uno::Reference< drawing::XShapes >& rShapes)
:	SdXMLGenericPageContext( rInImport, nPrfx, rLName, xAttrList, rShapes )
{
    const sal_Bool bHandoutMaster = IsXMLToken( rLName, XML_HANDOUT_MASTER );

    const sal_Int16 nAttrCount = xAttrList.is() ? xAttrList->getLength() : 0;
    for(sal_Int16 i=0; i < nAttrCount; i++)
    {
        OUString sAttrName = xAttrList->getNameByIndex( i );
        OUString aLclLocalName;
        sal_uInt16 nLclPrefix = GetSdImport().GetNamespaceMap().GetKeyByAttrName( sAttrName, &aLclLocalName );
        OUString sValue = xAttrList->getValueByIndex( i );
        const SvXMLTokenMap& rAttrTokenMap = GetSdImport().GetMasterPageAttrTokenMap();

        switch(rAttrTokenMap.Get(nLclPrefix, aLclLocalName))
        {
            case XML_TOK_MASTERPAGE_NAME:
            {
                msName = sValue;
                break;
            }
            case XML_TOK_MASTERPAGE_PAGE_MASTER_NAME:
            {
                msPageMasterName = sValue;
                break;
            }
            case XML_TOK_MASTERPAGE_STYLE_NAME:
            {
                msStyleName = sValue;
                break;
            }
            case XML_TOK_MASTERPAGE_PAGE_LAYOUT_NAME:
            {
                maPageLayoutName = sValue;
                break;
            }
        }
    }

    GetImport().GetShapeImport()->startPage( GetLocalShapesContext() );

    // set page name?
    if(!bHandoutMaster && msName.getLength() && GetLocalShapesContext().is())
    {
        uno::Reference < container::XNamed > xNamed(GetLocalShapesContext(), uno::UNO_QUERY);
        if(xNamed.is())
            xNamed->setName(msName);
    }

    // set page-master?
    if(msPageMasterName.getLength())
    {
        SetPageMaster( msPageMasterName );
    }

    // set PageProperties?
    if(!bHandoutMaster && msStyleName.getLength())
    {
        const SvXMLImportContext* pContext = GetSdImport().GetShapeImport()->GetAutoStylesContext();

        if( pContext && pContext->ISA( SvXMLStyleContext ) )
        {
            const SdXMLStylesContext* pStyles = (SdXMLStylesContext*)pContext;
            if(pStyles)
            {
                const SvXMLStyleContext* pStyle = pStyles->FindStyleChildContext(
                    XML_STYLE_FAMILY_SD_DRAWINGPAGE_ID, msStyleName);

                if(pStyle && pStyle->ISA(XMLPropStyleContext))
                {
                    XMLPropStyleContext* pPropStyle = (XMLPropStyleContext*)pStyle;

                    uno::Reference <beans::XPropertySet> xPropSet1(rShapes, uno::UNO_QUERY);
                    if(xPropSet1.is())
                    {
                        const OUString aBackground(RTL_CONSTASCII_USTRINGPARAM("Background"));
                        uno::Reference< beans::XPropertySet > xPropSet2;
                        uno::Reference< beans::XPropertySetInfo > xInfo( xPropSet1->getPropertySetInfo() );
                        if( xInfo.is() && xInfo->hasPropertyByName( aBackground ) )
                        {
                            uno::Reference< lang::XMultiServiceFactory > xServiceFact(GetSdImport().GetModel(), uno::UNO_QUERY);
                            if(xServiceFact.is())
                            {
                                uno::Reference< beans::XPropertySet > xTempSet(
                                    xServiceFact->createInstance(
                                    OUString(RTL_CONSTASCII_USTRINGPARAM("com.sun.star.drawing.Background"))),
                                    uno::UNO_QUERY);

                                xPropSet2 = xTempSet;
                            }
                        }

                        uno::Reference< beans::XPropertySet > xPropSet;
                        if( xPropSet2.is() )
                            xPropSet = PropertySetMerger_CreateInstance( xPropSet1, xPropSet2 );
                        else
                            xPropSet = xPropSet1;

                        if(xPropSet.is())
                        {
                            try
                            {
                                pPropStyle->FillPropertySet(xPropSet);

                                uno::Any aAny;
                                aAny <<= xPropSet2;
                                xPropSet1->setPropertyValue( aBackground, aAny );
                            }
                            catch( uno::Exception )
                            {
                                DBG_ERROR( "uno::Exception catched!" );
                            }
                        }
                    }
                }
            }
        }
    }

    SetLayout();

    DeleteAllShapes();
}

//////////////////////////////////////////////////////////////////////////////

SdXMLMasterPageContext::~SdXMLMasterPageContext()
{
}

//////////////////////////////////////////////////////////////////////////////

void SdXMLMasterPageContext::EndElement()
{
    // set styles on master-page
    if(msName.getLength() && GetSdImport().GetShapeImport()->GetStylesContext())
    {
        SvXMLImportContext* pContext = GetSdImport().GetShapeImport()->GetStylesContext();
        if( pContext && pContext->ISA( SvXMLStyleContext ) )
            ((SdXMLStylesContext*)pContext)->SetMasterPageStyles(*this);
    }

    SdXMLGenericPageContext::EndElement();
    GetImport().GetShapeImport()->endPage(GetLocalShapesContext());
}

//////////////////////////////////////////////////////////////////////////////

SvXMLImportContext* SdXMLMasterPageContext::CreateChildContext(
    sal_uInt16 nInPrefix,
    const OUString& rLocalName,
    const uno::Reference< xml::sax::XAttributeList>& xAttrList )
{
    SvXMLImportContext* pContext = 0;
    const SvXMLTokenMap& rTokenMap = GetSdImport().GetMasterPageElemTokenMap();

    // some special objects inside style:masterpage context
    switch(rTokenMap.Get(nInPrefix, rLocalName))
    {
        case XML_TOK_MASTERPAGE_STYLE:
        {
            if(GetSdImport().GetShapeImport()->GetStylesContext())
            {
                // style:style inside master-page context -> presentation style
                XMLShapeStyleContext* pNew = new XMLShapeStyleContext(
                    GetSdImport(), nInPrefix, rLocalName, xAttrList,
                    *GetSdImport().GetShapeImport()->GetStylesContext(),
                    XML_STYLE_FAMILY_SD_PRESENTATION_ID);

                // add this style to the outer StylesContext class for later processing
                if(pNew)
                {
                    pContext = pNew;
                    GetSdImport().GetShapeImport()->GetStylesContext()->AddStyle(*pNew);
                }
            }
            break;
        }
        case XML_TOK_MASTERPAGE_NOTES:
        {
            if( GetSdImport().IsImpress() )
            {
                // get notes page
                uno::Reference< presentation::XPresentationPage > xPresPage(GetLocalShapesContext(), uno::UNO_QUERY);
                if(xPresPage.is())
                {
                    uno::Reference< drawing::XDrawPage > xNotesDrawPage(xPresPage->getNotesPage(), uno::UNO_QUERY);
                    if(xNotesDrawPage.is())
                    {
                        uno::Reference< drawing::XShapes > xNewShapes(xNotesDrawPage, uno::UNO_QUERY);
                        if(xNewShapes.is())
                        {
                            // presentation:notes inside master-page context
                            pContext = new SdXMLNotesContext( GetSdImport(), nInPrefix, rLocalName, xAttrList, xNewShapes);
                        }
                    }
                }
            }
        }
    }

    // call base class
    if(!pContext)
        pContext = SdXMLGenericPageContext::CreateChildContext(nInPrefix, rLocalName, xAttrList);

    return pContext;
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

TYPEINIT1( SdXMLStylesContext, SvXMLStyleContext );

SdXMLStylesContext::SdXMLStylesContext(
    SdXMLImport& rInImport,
    sal_uInt16 nPrfx,
    const OUString& rLName,
    const uno::Reference< xml::sax::XAttributeList >& xAttrList,
    sal_Bool bIsAutoStyle)
:	SvXMLStylesContext(rInImport, nPrfx, rLName, xAttrList),
    mbIsAutoStyle(bIsAutoStyle)
{
    Reference< lang::XMultiServiceFactory > xMSF = rInImport.getServiceFactory();

    mpNumFormatter = new SvNumberFormatter( xMSF, LANGUAGE_SYSTEM );

    mpNumFmtHelper = new SvXMLNumFmtHelper( mpNumFormatter, xMSF );
}

//////////////////////////////////////////////////////////////////////////////

SdXMLStylesContext::~SdXMLStylesContext()
{
    delete mpNumFmtHelper;
    delete mpNumFormatter;
}

//////////////////////////////////////////////////////////////////////////////

SvXMLStyleContext* SdXMLStylesContext::CreateStyleChildContext(
    sal_uInt16 nInPrefix,
    const OUString& rLocalName,
    const uno::Reference< xml::sax::XAttributeList >& xAttrList)
{
    SvXMLStyleContext* pContext = 0;
    const SvXMLTokenMap& rTokenMap = GetSdImport().GetStylesElemTokenMap();

    switch(rTokenMap.Get(nInPrefix, rLocalName))
    {
        case XML_TOK_STYLES_PAGE_MASTER:
        {
            // style:page-master inside office:styles context
            pContext = new SdXMLPageMasterContext(GetSdImport(), nInPrefix, rLocalName, xAttrList);
            break;
        }
        case XML_TOK_STYLES_PRESENTATION_PAGE_LAYOUT:
        {
            // style:presentation-page-layout inside office:styles context
            pContext = new SdXMLPresentationPageLayoutContext(GetSdImport(), nInPrefix, rLocalName, xAttrList);
            break;
        }
    }

    if(!pContext)
    {
        const SvXMLTokenMap& rLclTokenMap = mpNumFmtHelper->GetStylesElemTokenMap();
        sal_uInt16 nToken = rLclTokenMap.Get( nInPrefix, rLocalName );
        switch (nToken)
        {
            case XML_TOK_STYLES_DATE_STYLE:
            case XML_TOK_STYLES_TIME_STYLE:
                // number:date-style or number:time-style
                pContext = new SdXMLNumberFormatImportContext( GetSdImport(), nInPrefix, rLocalName, mpNumFmtHelper->getData(), nToken, xAttrList, *this );
                break;

            case XML_TOK_STYLES_NUMBER_STYLE:
            case XML_TOK_STYLES_CURRENCY_STYLE:
            case XML_TOK_STYLES_PERCENTAGE_STYLE:
            case XML_TOK_STYLES_BOOLEAN_STYLE:
            case XML_TOK_STYLES_TEXT_STYLE:
                pContext = new SvXMLNumFormatContext( GetSdImport(), nInPrefix, rLocalName,
                                                        mpNumFmtHelper->getData(), nToken, xAttrList, *this );
                break;
        }
    }

    // call base class
    if(!pContext)
        pContext = SvXMLStylesContext::CreateStyleChildContext(nInPrefix, rLocalName, xAttrList);

    return pContext;
}

//////////////////////////////////////////////////////////////////////////////

SvXMLStyleContext* SdXMLStylesContext::CreateStyleStyleChildContext(
    sal_uInt16 nFamily,
    sal_uInt16 nInPrefix,
    const OUString& rLocalName,
    const uno::Reference< ::com::sun::star::xml::sax::XAttributeList >& xAttrList)
{
    SvXMLStyleContext* pContext = 0;

    switch( nFamily )
    {
    case XML_STYLE_FAMILY_SD_DRAWINGPAGE_ID:
        pContext = new SdXMLDrawingPageStyleContext(GetSdImport(), nInPrefix, rLocalName, xAttrList, *this );
        break;
    }

    // call base class
    if(!pContext)
        pContext = SvXMLStylesContext::CreateStyleStyleChildContext(nFamily, nInPrefix, rLocalName, xAttrList);

    return pContext;
}

//////////////////////////////////////////////////////////////////////////////

SvXMLStyleContext* SdXMLStylesContext::CreateDefaultStyleStyleChildContext(
    sal_uInt16 nFamily,
    sal_uInt16 nInPrefix,
    const OUString& rLocalName,
    const Reference< XAttributeList > & xAttrList )
{
    SvXMLStyleContext* pContext = 0;

    switch( nFamily )
    {
    case XML_STYLE_FAMILY_SD_GRAPHICS_ID:
        pContext = new XMLGraphicsDefaultStyle(GetSdImport(), nInPrefix, rLocalName, xAttrList, *this );
        break;
    }

    // call base class
    if(!pContext)
        pContext = SvXMLStylesContext::CreateDefaultStyleStyleChildContext(nFamily, nInPrefix, rLocalName, xAttrList);

    return pContext;
}

//////////////////////////////////////////////////////////////////////////////

sal_uInt16 SdXMLStylesContext::GetFamily( const OUString& rFamily ) const
{
//	if(rFamily.getLength())
//	{
//		if(rFamily.equals(OUString(RTL_CONSTASCII_USTRINGPARAM(XML_STYLE_FAMILY_SD_GRAPHICS_NAME))))
//			return XML_STYLE_FAMILY_SD_GRAPHICS_ID;
//
//		if(rFamily.equals(OUString(RTL_CONSTASCII_USTRINGPARAM(XML_STYLE_FAMILY_SD_PRESENTATION_NAME))))
//			return XML_STYLE_FAMILY_SD_PRESENTATION_ID;
//
//		if(rFamily.equals(OUString(RTL_CONSTASCII_USTRINGPARAM(XML_STYLE_FAMILY_SD_POOL_NAME))))
//			return XML_STYLE_FAMILY_SD_POOL_ID;
//
//		if(rFamily.equals(OUString(RTL_CONSTASCII_USTRINGPARAM(XML_STYLE_FAMILY_SD_DRAWINGPAGE_NAME))))
//			return XML_STYLE_FAMILY_SD_DRAWINGPAGE_ID;
//	}

    // call base class
    return SvXMLStylesContext::GetFamily(rFamily);
}

//////////////////////////////////////////////////////////////////////////////

UniReference< SvXMLImportPropertyMapper > SdXMLStylesContext::GetImportPropertyMapper(
    sal_uInt16 nFamily) const
{
    UniReference < SvXMLImportPropertyMapper > xMapper;

//	if(XML_STYLE_FAMILY_SD_GRAPHICS_ID == nFamily
//		|| XML_STYLE_FAMILY_SD_PRESENTATION_ID == nFamily
//		|| XML_STYLE_FAMILY_SD_POOL_ID == nFamily)
//	{
//		if(!xPropImpPropMapper.is())
//		{
//			UniReference< XMLShapeImportHelper > aImpHelper = ((SvXMLImport&)GetImport()).GetShapeImport();
//			((SdXMLStylesContext*)this)->xPropImpPropMapper =
//				new SvXMLImportPropertyMapper(aImpHelper->GetPropertySetMapper());
//		}
//		xMapper = xPropImpPropMapper;
//		return xMapper;
//	}

    if(XML_STYLE_FAMILY_SD_DRAWINGPAGE_ID == nFamily)
    {
        if(!xPresImpPropMapper.is())
        {
            UniReference< XMLShapeImportHelper > aImpHelper = ((SvXMLImport&)GetImport()).GetShapeImport();
            ((SdXMLStylesContext*)this)->xPresImpPropMapper =
                aImpHelper->GetPresPagePropsMapper();
        }
        xMapper = xPresImpPropMapper;
        return xMapper;
    }

    // call base class
    return SvXMLStylesContext::GetImportPropertyMapper(nFamily);
}

//////////////////////////////////////////////////////////////////////////////
// Process all style and object info
//
void SdXMLStylesContext::EndElement()
{
    if(mbIsAutoStyle)
    {
        // AutoStyles for text import
        GetImport().GetTextImport()->SetAutoStyles( this );

        // AutoStyles for chart
        GetImport().GetChartImport()->SetAutoStylesContext( this );

        // AutoStyles for forms
        GetImport().GetFormImport()->setAutoStyleContext( this );

        // associate AutoStyles with styles in preparation to setting Styles on shapes
        for(sal_uInt32 a(0L); a < GetStyleCount(); a++)
        {
            const SvXMLStyleContext* pStyle = GetStyle(a);
            if(pStyle && pStyle->ISA(XMLShapeStyleContext))
            {
                XMLShapeStyleContext* pDocStyle = (XMLShapeStyleContext*)pStyle;
//				pDocStyle->Filter();

                SvXMLStylesContext* pStylesContext = GetSdImport().GetShapeImport()->GetStylesContext();
                if( pStylesContext )
                {
                    pStyle = pStylesContext->FindStyleChildContext(pStyle->GetFamily(), pStyle->GetParent());

                    if(pStyle && pStyle->ISA(XMLShapeStyleContext))
                    {
                        XMLShapeStyleContext* pParentStyle = (XMLShapeStyleContext*)pStyle;
                        if(pParentStyle->GetStyle().is())
                        {
                            pDocStyle->SetStyle(pParentStyle->GetStyle());
                        }
                    }
                }
            }
        }

        FinishStyles( false );
    }
    else
    {
        // Process styles list
        ImpSetGraphicStyles();

        // put style infos in the info set for other components ( content import f.e. )
        uno::Reference< beans::XPropertySet > xInfoSet( GetImport().getImportInfo() );
        if( xInfoSet.is() )
        {
            uno::Reference< beans::XPropertySetInfo > xInfoSetInfo( xInfoSet->getPropertySetInfo() );

            if( xInfoSetInfo->hasPropertyByName( OUString( RTL_CONSTASCII_USTRINGPARAM( "PageLayouts" ) ) ) )
                xInfoSet->setPropertyValue( OUString( RTL_CONSTASCII_USTRINGPARAM( "PageLayouts" ) ), uno::makeAny( getPageLayouts() ) );
        }

    }
}

//////////////////////////////////////////////////////////////////////////////
// set master-page styles (all with family="presentation" and a special
// prefix) on given master-page.
//
void SdXMLStylesContext::SetMasterPageStyles(SdXMLMasterPageContext& rMaster) const
{
    UniString sPrefix(rMaster.GetName());
    sPrefix += sal_Unicode('-');

    if(GetSdImport().GetLocalDocStyleFamilies().is() && GetSdImport().GetLocalDocStyleFamilies()->hasByName(rMaster.GetName()))
    {
        uno::Any aAny(GetSdImport().GetLocalDocStyleFamilies()->getByName(rMaster.GetName()));
        uno::Reference< container::XNameAccess > xMasterPageStyles;
        aAny >>= xMasterPageStyles;

        if(xMasterPageStyles.is())
        {
            ImpSetGraphicStyles(xMasterPageStyles, XML_STYLE_FAMILY_SD_PRESENTATION_ID, sPrefix);
        }
    }
}

//////////////////////////////////////////////////////////////////////////////
// Process styles list:
// set graphic styles (all with family="graphics"). Remember xStyle at list element.
//
void SdXMLStylesContext::ImpSetGraphicStyles() const
{
    if(GetSdImport().GetLocalDocStyleFamilies().is())
    {
        const OUString sGraphicStyleName(OUString(RTL_CONSTASCII_USTRINGPARAM(XML_STYLE_FAMILY_SD_GRAPHICS_NAME)));
        uno::Any aAny(GetSdImport().GetLocalDocStyleFamilies()->getByName(sGraphicStyleName));
        uno::Reference< container::XNameAccess > xGraphicPageStyles;
        aAny >>= xGraphicPageStyles;

        if(xGraphicPageStyles.is())
        {
            UniString aPrefix;
            ImpSetGraphicStyles(xGraphicPageStyles, XML_STYLE_FAMILY_SD_GRAPHICS_ID, aPrefix);
        }
    }
}

//////////////////////////////////////////////////////////////////////////////
// help function used by ImpSetGraphicStyles() and ImpSetMasterPageStyles()
//
void SdXMLStylesContext::ImpSetGraphicStyles(
    uno::Reference< container::XNameAccess >& xPageStyles,
    sal_uInt16 nFamily,
    const UniString& rPrefix) const
{
    xub_StrLen nPrefLen(rPrefix.Len());
    uno::Any aAny;

    sal_uInt32 a;

    // set defaults
    for( a = 0; a < GetStyleCount(); a++)
    {
        const SvXMLStyleContext* pStyle = GetStyle(a);

        if(nFamily == pStyle->GetFamily() && pStyle->IsDefaultStyle())
        {
            ((SvXMLStyleContext*)pStyle)->SetDefaults();
        }
    }

    // create all styles and set properties
    for( a = 0; a < GetStyleCount(); a++)
    {
        const SvXMLStyleContext* pStyle = GetStyle(a);

        if(nFamily == pStyle->GetFamily() && !pStyle->IsDefaultStyle())
        {
            const UniString aStyleName(pStyle->GetName());
            sal_uInt16 nStylePrefLen = aStyleName.SearchBackward( sal_Unicode('-') ) + 1;

            if(!nPrefLen || ((nPrefLen == nStylePrefLen) && aStyleName.Equals(rPrefix, 0, nPrefLen)))
            {
                uno::Reference< style::XStyle > xStyle;
                const OUString aPureStyleName = nPrefLen ?
                    pStyle->GetName().copy((sal_Int32)nPrefLen) : pStyle->GetName();

                if(xPageStyles->hasByName(aPureStyleName))
                {
                    aAny = xPageStyles->getByName(aPureStyleName);
                    aAny >>= xStyle;

                    // set properties of existing styles to default
                    uno::Reference< beans::XPropertySet > xPropSet( xStyle, uno::UNO_QUERY );
                    uno::Reference< beans::XPropertySetInfo > xPropSetInfo;
                    if( xPropSet.is() )
                        xPropSetInfo = xPropSet->getPropertySetInfo();

                    uno::Reference< beans::XPropertyState > xPropState( xStyle, uno::UNO_QUERY );

                    if( xPropState.is() )
                    {
                        UniReference < XMLPropertySetMapper > xPrMap;
                        UniReference < SvXMLImportPropertyMapper > xImpPrMap = GetImportPropertyMapper( nFamily );
                        DBG_ASSERT( xImpPrMap.is(), "There is the import prop mapper" );
                        if( xImpPrMap.is() )
                            xPrMap = xImpPrMap->getPropertySetMapper();
                        if( xPrMap.is() )
                        {
                            const sal_Int32 nCount = xPrMap->GetEntryCount();
                            for( sal_Int32 i = 0; i < nCount; i++ )
                            {
                                const OUString& rName = xPrMap->GetEntryAPIName( i );
                                if( xPropSetInfo->hasPropertyByName( rName ) && beans::PropertyState_DIRECT_VALUE == xPropState->getPropertyState( rName ) )
                                {
                                    xPropState->setPropertyToDefault( rName );
                                }
                            }
                        }
                    }
                }
                else
                {
                    // graphics style does not exist, create and add it
                    uno::Reference< lang::XMultiServiceFactory > xServiceFact(GetSdImport().GetModel(), uno::UNO_QUERY);
                    if(xServiceFact.is())
                    {
                        uno::Reference< style::XStyle > xNewStyle(
                            xServiceFact->createInstance(
                            OUString(RTL_CONSTASCII_USTRINGPARAM("com.sun.star.style.Style"))),
                            uno::UNO_QUERY);

                        if(xNewStyle.is())
                        {
                            // remember style
                            xStyle = xNewStyle;

                            // add new style to graphics style pool
                            uno::Reference< container::XNameContainer > xInsertContainer(xPageStyles, uno::UNO_QUERY);
                            if(xInsertContainer.is())
                            {
                                aAny <<= xStyle;
                                xInsertContainer->insertByName(aPureStyleName, aAny);
                            }
                        }
                    }
                }

                if(xStyle.is())
                {
                    // set properties at style
                    XMLShapeStyleContext* pPropStyle =
                        (pStyle->ISA(XMLShapeStyleContext)) ? (XMLShapeStyleContext*)pStyle : 0L;
                    uno::Reference< beans::XPropertySet > xPropSet(xStyle, uno::UNO_QUERY);

                    if(xPropSet.is() && pPropStyle)
                    {
                        pPropStyle->FillPropertySet(xPropSet);
                        pPropStyle->SetStyle(xStyle);
                    }
                }
            }
        }
    }

    // now set parents for all styles (when necessary)
    for(a = 0L; a < GetStyleCount(); a++)
    {
        const SvXMLStyleContext* pStyle = GetStyle(a);

        if(pStyle && nFamily == pStyle->GetFamily())
        {
            const UniString aStyleName(pStyle->GetName());
            sal_uInt16 nStylePrefLen = aStyleName.SearchBackward( sal_Unicode('-') ) + 1;

            if(pStyle->GetName().getLength() && (!nPrefLen || ((nPrefLen == nStylePrefLen) && aStyleName.Equals(rPrefix, 0, nPrefLen))))
            {
                try
                {

                    uno::Reference< style::XStyle > xStyle;
                    const OUString aPureStyleName = nPrefLen ? pStyle->GetName().copy((sal_Int32)nPrefLen) : pStyle->GetName();
                    xPageStyles->getByName(aPureStyleName) >>= xStyle;

                    if(xStyle.is())
                    {
                            // set parent style name
                            xStyle->setParentStyle(pStyle->GetParent());
                    }
                }
                catch( container::NoSuchElementException e )
                {
                }
            }
        }
    }
}

////////////////////////////////////////////////////////////////////////////////
// helper function to create the uno component that hold the mappings from
// xml auto layout name to internal autolayout id

uno::Reference< container::XNameAccess > SdXMLStylesContext::getPageLayouts() const
{
    uno::Reference< container::XNameContainer > xLayouts( comphelper::NameContainer_createInstance( ::getCppuType((const sal_Int32*)0)) );

    for(sal_uInt32 a(0L); a < GetStyleCount(); a++)
    {
        const SvXMLStyleContext* pStyle = GetStyle(a);
        if(pStyle && pStyle->ISA(SdXMLPresentationPageLayoutContext))
        {
            xLayouts->insertByName( pStyle->GetName(), uno::makeAny(
            (sal_Int32)((SdXMLPresentationPageLayoutContext*)pStyle)->GetTypeId() ) );
        }
    }

    return uno::Reference< container::XNameAccess >::query( xLayouts );
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//
TYPEINIT1( SdXMLMasterStylesContext, SvXMLImportContext );

SdXMLMasterStylesContext::SdXMLMasterStylesContext(
    SdXMLImport& rInImport,
    sal_uInt16 nPrfx,
    const ::rtl::OUString& rLName)
:	SvXMLImportContext( rInImport, nPrfx, rLName)
{
}

SdXMLMasterStylesContext::~SdXMLMasterStylesContext()
{
    for ( size_t i = 0, n = maMasterPageList.size(); i < n; ++i )
        maMasterPageList[ i ]->ReleaseRef();
    maMasterPageList.clear();
}

SvXMLImportContext* SdXMLMasterStylesContext::CreateChildContext(
    sal_uInt16 nInPrefix,
    const ::rtl::OUString& rLocalName,
    const uno::Reference< xml::sax::XAttributeList >& xAttrList)
{
    SvXMLImportContext* pContext = 0;

    if(nInPrefix == XML_NAMESPACE_STYLE
       && IsXMLToken( rLocalName, XML_MASTER_PAGE ) )
    {
        // style:masterpage inside office:styles context
        uno::Reference< drawing::XDrawPage > xNewMasterPage;
        uno::Reference< drawing::XDrawPages > xMasterPages(GetSdImport().GetLocalMasterPages(), uno::UNO_QUERY);

        if( xMasterPages.is() )
        {
            if(GetSdImport().GetNewMasterPageCount() + 1 > xMasterPages->getCount())
            {
                // new page, create and insert
                xNewMasterPage = xMasterPages->insertNewByIndex(xMasterPages->getCount());
            }
            else
            {
                // existing page, use it
                uno::Any aAny(xMasterPages->getByIndex(GetSdImport().GetNewMasterPageCount()));
                aAny >>= xNewMasterPage;
            }

            // increment global import page counter
            GetSdImport().IncrementNewMasterPageCount();

            if(xNewMasterPage.is())
            {
                uno::Reference< drawing::XShapes > xNewShapes(xNewMasterPage, uno::UNO_QUERY);
                if(xNewShapes.is() && GetSdImport().GetShapeImport()->GetStylesContext())
                {
                    pContext = new SdXMLMasterPageContext(GetSdImport(),
                        nInPrefix, rLocalName, xAttrList, xNewShapes);

                    if(pContext)
                    {
                        pContext->AddRef();
                        maMasterPageList.push_back( (SdXMLMasterPageContext*)pContext );
                    }
                }
            }
        }
    }
    else	if(nInPrefix == XML_NAMESPACE_STYLE
        && IsXMLToken( rLocalName, XML_HANDOUT_MASTER ) )
    {
        uno::Reference< presentation::XHandoutMasterSupplier > xHandoutSupp( GetSdImport().GetModel(), uno::UNO_QUERY );
        if( xHandoutSupp.is() )
        {
            uno::Reference< drawing::XShapes > xHandoutPage( xHandoutSupp->getHandoutMasterPage(), uno::UNO_QUERY );
            if(xHandoutPage.is() && GetSdImport().GetShapeImport()->GetStylesContext())
            {
                pContext = new SdXMLMasterPageContext(GetSdImport(),
                    nInPrefix, rLocalName, xAttrList, xHandoutPage);
            }
        }
    }
    else if( nInPrefix == XML_NAMESPACE_DRAW
        && IsXMLToken( rLocalName, XML_LAYER_SET ) )
    {
        pContext = new SdXMLLayerSetContext( GetImport(), nInPrefix, rLocalName, xAttrList );
    }

    // call base class
    if(!pContext)
        pContext = SvXMLImportContext::CreateChildContext(nInPrefix, rLocalName, xAttrList);

    return pContext;
}


}//end of namespace binfilter

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
