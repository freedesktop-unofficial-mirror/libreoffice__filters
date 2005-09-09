/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: xmloff_ximpbody.cxx,v $
 *
 *  $Revision: 1.3 $
 *
 *  last change: $Author: rt $ $Date: 2005-09-09 09:01:17 $
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

#pragma hdrstop

#ifndef _XIMPBODY_HXX
#include "ximpbody.hxx"
#endif

#ifndef _XMLOFF_PRSTYLEI_HXX_
#include "prstylei.hxx"
#endif

#ifndef _XIMPNOTES_HXX
#include "ximpnote.hxx"
#endif

// auto strip #ifndef _COM_SUN_STAR_DRAWING_XDRAWPAGE_HPP_
// auto strip #include <com/sun/star/drawing/XDrawPage.hpp>
// auto strip #endif

#ifndef _COM_SUN_STAR_DRAWING_XDRAWPAGES_HPP_
#include <com/sun/star/drawing/XDrawPages.hpp>
#endif

// auto strip #ifndef _COM_SUN_STAR_CONTAINER_XNAMED_HPP_
// auto strip #include <com/sun/star/container/XNamed.hpp>
// auto strip #endif

#ifndef _COM_SUN_STAR_PRESENTATION_XPRESENTATIONPAGE_HPP_ 
#include <com/sun/star/presentation/XPresentationPage.hpp>
#endif

#ifndef _XIMPSTYLE_HXX
#include "ximpstyl.hxx"
#endif

#ifndef _COM_SUN_STAR_DRAWING_XMASTERPAGETARGET_HPP_
#include <com/sun/star/drawing/XMasterPageTarget.hpp>
#endif

// auto strip #ifndef _COM_SUN_STAR_BEANS_XPROPERTYSET_HPP_
// auto strip #include <com/sun/star/beans/XPropertySet.hpp>
// auto strip #endif

#ifndef _XMLOFF_XMLUCONV_HXX 
#include "xmluconv.hxx"
#endif

// auto strip #ifndef _XMLOFF_PROPERTYSETMAPPER_HXX
// auto strip #include "xmlprmap.hxx"
// auto strip #endif

// auto strip #ifndef _XMLOFF_FAMILIES_HXX_
// auto strip #include "families.hxx"
// auto strip #endif

#ifndef _XMLOFF_XIMPSHOW_HXX
#include "ximpshow.hxx"
#endif

#ifndef _XMLOFF_PROPERTYSETMERGER_HXX_
#include "PropertySetMerger.hxx"
#endif
namespace binfilter {

using namespace ::rtl;
using namespace ::com::sun::star;

//////////////////////////////////////////////////////////////////////////////

SdXMLDrawPageContext::SdXMLDrawPageContext( SdXMLImport& rImport,
    USHORT nPrfx, const OUString& rLocalName,
    const ::com::sun::star::uno::Reference< ::com::sun::star::xml::sax::XAttributeList>& xAttrList,
    uno::Reference< drawing::XShapes >& rShapes) 
:	SdXMLGenericPageContext( rImport, nPrfx, rLocalName, xAttrList, rShapes )
{
    sal_Int32 nPageId = -1;

    sal_Int16 nAttrCount = xAttrList.is() ? xAttrList->getLength() : 0;

    for(sal_Int16 i=0; i < nAttrCount; i++)
    {
        OUString sAttrName = xAttrList->getNameByIndex( i );
        OUString aLocalName;
        USHORT nPrefix = GetSdImport().GetNamespaceMap().GetKeyByAttrName( sAttrName, &aLocalName );
        OUString sValue = xAttrList->getValueByIndex( i );
        const SvXMLTokenMap& rAttrTokenMap = GetSdImport().GetDrawPageAttrTokenMap();

        switch(rAttrTokenMap.Get(nPrefix, aLocalName))
        {
            case XML_TOK_DRAWPAGE_NAME:
            {
                maName = sValue;
                break;
            }
            case XML_TOK_DRAWPAGE_STYLE_NAME:
            {
                maStyleName = sValue;
                break;
            }
            case XML_TOK_DRAWPAGE_MASTER_PAGE_NAME:
            {
                maMasterPageName = sValue;
                break;
            }
            case XML_TOK_DRAWPAGE_PAGE_LAYOUT_NAME:
            {
                maPageLayoutName = sValue;
                break;
            }
            case XML_TOK_DRAWPAGE_ID:
            {
                sal_Int32 nId;
                if( SvXMLUnitConverter::convertNumber( nId, sValue ) )
                    nPageId = nId;
                break;
            }
            case XML_TOK_DRAWPAGE_HREF:
            {
                maHREF = sValue;
                break;
            }
        }
    }

    GetImport().GetShapeImport()->startPage( rShapes );

    uno::Reference< drawing::XDrawPage > xDrawPage(rShapes, uno::UNO_QUERY);

    // set an id?
    if( nPageId != -1 && xDrawPage.is() )
        rImport.setDrawPageId( nPageId, xDrawPage ); 

    // set PageName?
    if(maName.getLength())
    {
        if(xDrawPage.is())
        {
            uno::Reference < container::XNamed > xNamed(xDrawPage, uno::UNO_QUERY);
            if(xNamed.is())
                xNamed->setName(maName);
        }
    }

    // set MasterPage?
    if(maMasterPageName.getLength())
    {
        // #85906# Code for setting masterpage needs complete rework
        // since GetSdImport().GetMasterStylesContext() gives always ZERO
        // because of content/style file split. Now the nechanism is to
        // compare the wanted masterpage-name with the existing masterpages
        // which were loaded and created in the styles section loading.
        uno::Reference< drawing::XDrawPages > xMasterPages(GetSdImport().GetLocalMasterPages(), uno::UNO_QUERY);
        uno::Reference < drawing::XMasterPageTarget > xDrawPage(rShapes, uno::UNO_QUERY);
        uno::Reference< drawing::XDrawPage > xMasterPage;

        if(xDrawPage.is() && xMasterPages.is())
        {
            sal_Bool bDone(FALSE);

            for(sal_Int32 a = 0; !bDone && a < xMasterPages->getCount(); a++)
            {
                uno::Any aAny(xMasterPages->getByIndex(a));
                aAny >>= xMasterPage;

                if(xMasterPage.is())
                {
                    uno::Reference < container::XNamed > xMasterNamed(xMasterPage, uno::UNO_QUERY);
                    if(xMasterNamed.is())
                    {
                        OUString sMasterPageName = xMasterNamed->getName();

                        if(sMasterPageName.getLength() && sMasterPageName.equals(maMasterPageName))
                        {
                            xDrawPage->setMasterPage(xMasterPage);
                            bDone = TRUE;
                        }
                    }
                }
            }
        }
    }

    // set PageProperties?
    if(maStyleName.getLength())
    {	
        const SvXMLImportContext* pContext = GetSdImport().GetShapeImport()->GetAutoStylesContext();

        if( pContext && pContext->ISA( SvXMLStyleContext ) )
        {
            const SdXMLStylesContext* pStyles = (SdXMLStylesContext*)pContext;
            if(pStyles)
            {
                const SvXMLStyleContext* pStyle = pStyles->FindStyleChildContext(
                    XML_STYLE_FAMILY_SD_DRAWINGPAGE_ID, maStyleName);

                if(pStyle && pStyle->ISA(XMLPropStyleContext))
                {
                    XMLPropStyleContext* pPropStyle = (XMLPropStyleContext*)pStyle;

                    
                    uno::Reference <beans::XPropertySet> xPropSet1(rShapes, uno::UNO_QUERY);
                    if(xPropSet1.is())
                    {
                        // since the background items are in a different propertyset
                        // which itself is a property of the pages property set
                        // we now merge these two propertysets if possible to simulate
                        // a single propertyset with all draw page properties
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
                            pPropStyle->FillPropertySet(xPropSet);
                        }

                        if( xPropSet2.is() )
                        {
                            uno::Any aAny;
                            aAny <<= xPropSet2;
                            xPropSet1->setPropertyValue( aBackground, aAny );
                        }
                    }
                }
            }
        }
    }

    if( maHREF.getLength() )
    {
        uno::Reference< beans::XPropertySet > xProps( xDrawPage, uno::UNO_QUERY );
        if( xProps.is() )
        {
            sal_Int32 nIndex = maHREF.lastIndexOf( (sal_Unicode)'#' );
            if( nIndex != -1 )
            {
                OUString aFileName( maHREF.copy( 0, nIndex ) );
                OUString aBookmarkName( maHREF.copy( nIndex+1 ) );

                maHREF = GetImport().GetAbsoluteReference( aFileName );
                maHREF += OUString( (sal_Unicode)'#' );
                maHREF += aBookmarkName;
            }

            xProps->setPropertyValue( OUString( RTL_CONSTASCII_USTRINGPARAM( "BookmarkURL" ) ), uno::makeAny( maHREF ) );
        }
    }

    SetLayout();

    DeleteAllShapes();
}

//////////////////////////////////////////////////////////////////////////////

SdXMLDrawPageContext::~SdXMLDrawPageContext()
{
}

//////////////////////////////////////////////////////////////////////////////

SvXMLImportContext *SdXMLDrawPageContext::CreateChildContext( USHORT nPrefix,
    const OUString& rLocalName,
    const ::com::sun::star::uno::Reference< ::com::sun::star::xml::sax::XAttributeList>& xAttrList )
{
    SvXMLImportContext *pContext = 0L;
    const SvXMLTokenMap& rTokenMap = GetSdImport().GetDrawPageElemTokenMap();

    // some special objects inside draw:page context
    switch(rTokenMap.Get(nPrefix, rLocalName))
    {
        case XML_TOK_DRAWPAGE_NOTES:
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
                            // presentation:notes inside draw:page context
                            pContext = new SdXMLNotesContext( GetSdImport(), nPrefix, rLocalName, xAttrList, xNewShapes);
                        }
                    }
                }
            }
        }
    }

    // call parent when no own context was created
    if(!pContext)
        pContext = SdXMLGenericPageContext::CreateChildContext(nPrefix, rLocalName, xAttrList);

    return pContext;
}

void SdXMLDrawPageContext::EndElement()
{
    SdXMLGenericPageContext::EndElement();
    GetImport().GetShapeImport()->endPage(GetLocalShapesContext());
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

SdXMLBodyContext::SdXMLBodyContext( SdXMLImport& rImport,
    USHORT nPrfx, const OUString& rLocalName ) 
:	SvXMLImportContext( rImport, nPrfx, rLocalName )
{
}

//////////////////////////////////////////////////////////////////////////////

SdXMLBodyContext::~SdXMLBodyContext()
{
}

//////////////////////////////////////////////////////////////////////////////

SvXMLImportContext *SdXMLBodyContext::CreateChildContext( 
    USHORT nPrefix, 
    const OUString& rLocalName,
    const uno::Reference< xml::sax::XAttributeList>& xAttrList )
{
    SvXMLImportContext *pContext = 0L;
    const SvXMLTokenMap& rTokenMap = GetSdImport().GetBodyElemTokenMap();

    switch(rTokenMap.Get(nPrefix, rLocalName))
    {
        case XML_TOK_BODY_PAGE:
        {
            // only read the first page in preview mode
            if( (GetSdImport().GetNewPageCount() == 0) || !GetSdImport().IsPreview() )
            {
                // import this page
                uno::Reference< drawing::XDrawPage > xNewDrawPage;
                uno::Reference< drawing::XDrawPages > xDrawPages(GetSdImport().GetLocalDrawPages(), uno::UNO_QUERY);

                if(GetSdImport().GetNewPageCount() + 1 > xDrawPages->getCount())
                {
                    // new page, create and insert
                    xNewDrawPage = xDrawPages->insertNewByIndex(xDrawPages->getCount());
                }
                else
                {
                    // existing page, use it
                    uno::Any aAny(xDrawPages->getByIndex(GetSdImport().GetNewPageCount()));
                    aAny >>= xNewDrawPage;
                }

                // increment global import page counter
                GetSdImport().IncrementNewPageCount();

                if(xNewDrawPage.is())
                {
                    uno::Reference< drawing::XShapes > xNewShapes(xNewDrawPage, uno::UNO_QUERY);
                    if(xNewShapes.is())
                    {
                        // draw:page inside office:body context
                        pContext = new SdXMLDrawPageContext(GetSdImport(), nPrefix, rLocalName, xAttrList, 
                            xNewShapes);
                    }
                }
            }
            break;
        }
        case XML_TOK_BODY_SETTINGS:
        {
            pContext = new SdXMLShowsContext( GetSdImport(), nPrefix, rLocalName, xAttrList );
        }
    }

    // call parent when no own context was created
    if(!pContext)
        pContext = SvXMLImportContext::CreateChildContext(nPrefix, rLocalName, xAttrList);

    return pContext;
}
}//end of namespace binfilter
