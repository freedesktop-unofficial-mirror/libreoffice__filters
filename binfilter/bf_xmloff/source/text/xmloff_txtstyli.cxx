/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: xmloff_txtstyli.cxx,v $
 *
 *  $Revision: 1.3 $
 *
 *  last change: $Author: rt $ $Date: 2005-09-09 10:39:18 $
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

// auto strip #ifndef _COM_SUN_STAR_FRAME_XMODEL_HPP_
// auto strip #include <com/sun/star/frame/XModel.hpp>
// auto strip #endif
// auto strip #ifndef _COM_SUN_STAR_STYLE_XSTYLE_HPP_
// auto strip #include <com/sun/star/style/XStyle.hpp>
// auto strip #endif
// auto strip #ifndef _COM_SUN_STAR_CONTAINER_XNAMECONTAINER_HPP_
// auto strip #include <com/sun/star/container/XNameContainer.hpp>
// auto strip #endif

// auto strip #ifndef _COM_SUN_STAR_LANG_XMULTISERVICEFACTORY_HPP_
// auto strip #include <com/sun/star/lang/XMultiServiceFactory.hpp>
// auto strip #endif
#ifndef _COM_SUN_STAR_STYLE_PARAGRAPHSTYLECATEGORY_HPP_
#include <com/sun/star/style/ParagraphStyleCategory.hpp>
#endif
#ifndef _COM_SUN_STAR_DOCUMENT_XEVENTSSUPPLIER_HPP
#include <com/sun/star/document/XEventsSupplier.hpp>
#endif
// auto strip #ifndef _COM_SUN_STAR_BEANS_XMULTIPROPERTYSET_HPP_
// auto strip #include <com/sun/star/beans/XMultiPropertySet.hpp>
// auto strip #endif
#ifndef _XMLOFF_XMLNMSPE_HXX
#include "xmlnmspe.hxx"
#endif
// auto strip #ifndef _XMLOFF_XMLTOKEN_HXX
// auto strip #include "xmltoken.hxx"
// auto strip #endif
// auto strip #ifndef _XMLOFF_FAMILIES_HXX
// auto strip #include "families.hxx"
// auto strip #endif
#ifndef _XMLOFF_XMLTEXTPROPERTYSETCONTEXT_HXX
#include "XMLTextPropertySetContext.hxx"
#endif
// auto strip #ifndef _XMLOFF_XMLTKMAP_HXX
// auto strip #include "xmltkmap.hxx"
// auto strip #endif
#ifndef _XMLOFF_XMLIMP_HXX
#include "xmlimp.hxx"
#endif
#ifndef _XMLOFF_XMLUCONV_HXX
#include "xmluconv.hxx"
#endif

#ifndef _XMLOFF_TXTPRMAP_HXX
#include "txtprmap.hxx"
#endif
#ifndef _XMLOFF_TXTSTYLI_HXX
#include "txtstyli.hxx"
#endif
// auto strip #ifndef _XMLOFF_ATTRLIST_HXX 
// auto strip #include "attrlist.hxx"
// auto strip #endif

#ifndef _XMLOFF_XMLEVENTSIMPORTCONTEXT_HXX
#include "XMLEventsImportContext.hxx"
#endif

#ifndef _TOOLS_DEBUG_HXX 
#include <tools/debug.hxx>
#endif

// STL includes
#include <algorithm>
#include <functional>
#include <utility>
#include <vector>
namespace binfilter {

using namespace ::rtl;
using namespace ::std;
using namespace ::com::sun::star;
using namespace ::com::sun::star::uno;
using namespace ::com::sun::star::xml::sax;
using namespace ::com::sun::star::style;
using namespace ::com::sun::star::frame;
using namespace ::com::sun::star::beans;
using namespace ::com::sun::star::lang;
using namespace ::com::sun::star::container;
//using namespace ::com::sun::star::text;
using namespace ::binfilter::xmloff::token;

static __FAR_DATA SvXMLEnumMapEntry aCategoryMap[] =
{
    { XML_TEXT,     ParagraphStyleCategory::TEXT },
    { XML_CHAPTER,  ParagraphStyleCategory::CHAPTER },
    { XML_LIST,     ParagraphStyleCategory::LIST },
    { XML_INDEX,    ParagraphStyleCategory::INDEX },
    { XML_EXTRA,    ParagraphStyleCategory::EXTRA },
    { XML_HTML,     ParagraphStyleCategory::HTML },
    { XML_TOKEN_INVALID, 0 }
};

void XMLTextStyleContext::SetAttribute( sal_uInt16 nPrefixKey,
                                        const OUString& rLocalName,
                                        const OUString& rValue )
{
    if( XML_NAMESPACE_STYLE == nPrefixKey )
    {
        // TODO: use a map here
        if( IsXMLToken( rLocalName, XML_AUTO_UPDATE ) )
        {
            if( IsXMLToken( rValue, XML_TRUE ) )
                bAutoUpdate = sal_True;
        }
        else if( IsXMLToken( rLocalName, XML_LIST_STYLE_NAME ) )
        {
            sListStyleName = rValue;
        }
        else if( IsXMLToken( rLocalName, XML_MASTER_PAGE_NAME ) )
        {
            sMasterPageName = rValue;
            bHasMasterPageName = sal_True;
        }
        else if( IsXMLToken( rLocalName, XML_CLASS ) )
        {
            sCategoryVal = rValue;
        }
        else
        {
            XMLPropStyleContext::SetAttribute( nPrefixKey, rLocalName, rValue );
        }
    }
    else
    {
        XMLPropStyleContext::SetAttribute( nPrefixKey, rLocalName, rValue );
    }
}

TYPEINIT1( XMLTextStyleContext, XMLPropStyleContext );

XMLTextStyleContext::XMLTextStyleContext( SvXMLImport& rImport,
        sal_uInt16 nPrfx, const OUString& rLName,
        const Reference< XAttributeList > & xAttrList,
        SvXMLStylesContext& rStyles, sal_uInt16 nFamily,
        sal_Bool bDefaultStyle ) :
    XMLPropStyleContext( rImport, nPrfx, rLName, xAttrList, rStyles,
                         nFamily, bDefaultStyle ),
    bAutoUpdate( sal_False ),
    bHasMasterPageName( sal_False ),
    bHasCombinedCharactersLetter( sal_False ),
    pEventContext( NULL ),
    sIsAutoUpdate( RTL_CONSTASCII_USTRINGPARAM( "IsAutoUpdate" ) ),
    sCategory( RTL_CONSTASCII_USTRINGPARAM( "Category" ) ),
    sNumberingStyleName( RTL_CONSTASCII_USTRINGPARAM( "NumberingStyleName" ) ),
    sPageDescName( RTL_CONSTASCII_USTRINGPARAM( "PageDescName" ) ),
    sDropCapCharStyleName( RTL_CONSTASCII_USTRINGPARAM( "DropCapCharStyleName" ) )
{
}

XMLTextStyleContext::~XMLTextStyleContext()
{
}

SvXMLImportContext *XMLTextStyleContext::CreateChildContext(
        sal_uInt16 nPrefix,
        const OUString& rLocalName,
        const Reference< XAttributeList > & xAttrList )
{
    SvXMLImportContext *pContext = 0;

    if( XML_NAMESPACE_STYLE == nPrefix &&
        IsXMLToken( rLocalName, XML_PROPERTIES ) )
    {
        UniReference < SvXMLImportPropertyMapper > xImpPrMap =
            GetStyles()->GetImportPropertyMapper( GetFamily() );
        if( xImpPrMap.is() )
            pContext = new XMLTextPropertySetContext( GetImport(), nPrefix,
                                                    rLocalName, xAttrList,
                                                    GetProperties(),
                                                    xImpPrMap,
                                                    sDropCapTextStyleName );
    }
    else if ( (XML_NAMESPACE_OFFICE == nPrefix) &&
              IsXMLToken( rLocalName, XML_EVENTS ) )
    {
        // create and remember events import context 
        // (for delayed processing of events)
        pEventContext = new XMLEventsImportContext( GetImport(), nPrefix,
                                                   rLocalName);
        pEventContext->AddRef();
        pContext = pEventContext;
    }
        
    if( !pContext )
        pContext = XMLPropStyleContext::CreateChildContext( nPrefix, rLocalName,
                                                          xAttrList );

    return pContext;
}

void XMLTextStyleContext::CreateAndInsert( sal_Bool bOverwrite )
{
    XMLPropStyleContext::CreateAndInsert( bOverwrite );
    Reference < XStyle > xStyle = GetStyle();
    if( !xStyle.is() || !(bOverwrite || IsNew()) )
        return;
    
    Reference < XPropertySet > xPropSet( xStyle, UNO_QUERY );
    Reference< XPropertySetInfo > xPropSetInfo =
                xPropSet->getPropertySetInfo();
    if( xPropSetInfo->hasPropertyByName( sIsAutoUpdate ) )
    {
        Any aAny;
        sal_Bool bTmp = bAutoUpdate;
        aAny.setValue( &bTmp, ::getBooleanCppuType() );
        xPropSet->setPropertyValue( sIsAutoUpdate, aAny );
    }

    sal_uInt16 nCategory = ParagraphStyleCategory::TEXT;
    if(  XML_STYLE_FAMILY_TEXT_PARAGRAPH == GetFamily() &&
         sCategoryVal.getLength() && xStyle->isUserDefined() &&
         xPropSetInfo->hasPropertyByName( sCategory ) &&
          SvXMLUnitConverter::convertEnum( nCategory, sCategoryVal, aCategoryMap ) )
    {
        Any aAny;
        aAny <<= (sal_Int16)nCategory;
        xPropSet->setPropertyValue( sCategory, aAny );
    }

    // tell the style about it's events (if applicable)
    if (NULL != pEventContext)
    {
        // set event suppplier and release reference to context
        Reference<document::XEventsSupplier> xEventsSupplier(xStyle,UNO_QUERY);
        pEventContext->SetEvents(xEventsSupplier);
        pEventContext->ReleaseRef();
    }
}

void XMLTextStyleContext::SetDefaults( )
{
    if (GetFamily() == XML_STYLE_FAMILY_TEXT_PARAGRAPH )
    {
        Reference < XMultiServiceFactory > xFactory ( GetImport().GetModel(), UNO_QUERY); 
        if (xFactory.is())
        {
            Reference < XInterface > xInt = xFactory->createInstance ( 
                OUString ( RTL_CONSTASCII_USTRINGPARAM ( "com.sun.star.text.Defaults" ) ) );
            Reference < XPropertySet > xProperties ( xInt, UNO_QUERY );
            if ( xProperties.is() )
                FillPropertySet ( xProperties );
        }
    }
}

void XMLTextStyleContext::Finish( sal_Bool bOverwrite )
{
    XMLPropStyleContext::Finish( bOverwrite );

    Reference < XStyle > xStyle = GetStyle();
    if( !(sListStyleName.getLength() || sDropCapTextStyleName.getLength() ||
        bHasMasterPageName) ||
        !xStyle.is() || !(bOverwrite || IsNew()) )
        return;

    Reference < XPropertySet > xPropSet( xStyle, UNO_QUERY );
    Reference< XPropertySetInfo > xPropSetInfo =
                xPropSet->getPropertySetInfo();

    if( sListStyleName.getLength() )
    {
        // The families cointaner must exist
        const Reference < XNameContainer >& rNumStyles =
            GetImport().GetTextImport()->GetNumberingStyles();
        if( rNumStyles.is() && rNumStyles->hasByName( sListStyleName ) &&
            xPropSetInfo->hasPropertyByName( sNumberingStyleName ) )
        {
            Any aAny;
            aAny <<= sListStyleName;
            xPropSet->setPropertyValue( sNumberingStyleName, aAny );
        }
    }

    if( sDropCapTextStyleName.getLength() )
    {
        // The families cointaner must exist
        const Reference < XNameContainer >& rTextStyles =
            GetImport().GetTextImport()->GetTextStyles();
        if( rTextStyles.is() &&
            rTextStyles->hasByName( sDropCapTextStyleName ) &&
            xPropSetInfo->hasPropertyByName( sDropCapCharStyleName ) )
        {
            Any aAny;
            aAny <<= sDropCapTextStyleName;
            xPropSet->setPropertyValue( sDropCapCharStyleName, aAny );
        }
    }

    if( bHasMasterPageName )
    {
        // The families cointaner must exist
        const Reference < XNameContainer >& rPageStyles =
            GetImport().GetTextImport()->GetPageStyles();
        if( ( !sMasterPageName.getLength() ||
              (rPageStyles.is() && 
               rPageStyles->hasByName( sMasterPageName )) ) &&
            xPropSetInfo->hasPropertyByName( sPageDescName ) )
        {
            Any aAny;
            aAny <<= sMasterPageName;
            xPropSet->setPropertyValue( sPageDescName, aAny );
        }
    }
}

void XMLTextStyleContext::FillPropertySet(
    const Reference<XPropertySet > & rPropSet )
{
    // imitate the FillPropertySet of the super class, so we get a chance to 
    // catch the combined characters attribute

    // imitate XMLPropStyleContext::FillPropertySet(...)
    UniReference < SvXMLImportPropertyMapper > xImpPrMap =
        ((SvXMLStylesContext *)GetStyles())->GetImportPropertyMapper(GetFamily());
    DBG_ASSERT( xImpPrMap.is(), "Where is the import prop mapper?" );
    if( xImpPrMap.is() )
    {

        // get property set mapper
        UniReference<XMLPropertySetMapper> rPropMapper =
            xImpPrMap->getPropertySetMapper();

        // imitate SvXMLImportPropertyMapper::FillPropertySet(...)

        // The reason for this is that we have no other way to
        // efficiently intercept the value of combined characters. To
        // get that value, we could iterate through the map once more,
        // but instead we chose to insert the code into this
        // iteration. I haven't been able to come up with a much more
        // intelligent solution.


        struct _ContextID_Index_Pair aContextIDs[] =
        {
            { CTF_COMBINED_CHARACTERS_FIELD, -1 },
#ifdef CONV_STAR_FONTS
            { CTF_FONTFAMILYNAME, -1 },
            { CTF_FONTFAMILYNAME_CJK, -1 },
            { CTF_FONTFAMILYNAME_CTL, -1 },
#endif
            { -1, -1 }
        };

        // get property set info
        Reference< XPropertySetInfo > xInfo = rPropSet->getPropertySetInfo();

        // check for multi-property set
        Reference<XMultiPropertySet> xMultiPropSet( rPropSet, UNO_QUERY );
        if ( xMultiPropSet.is() )
        {
            // Try XMultiPropertySet. If that fails, try the regular route.
            sal_Bool bSet = SvXMLImportPropertyMapper::_FillMultiPropertySet( 
                GetProperties(), xMultiPropSet, xInfo, rPropMapper,
                aContextIDs );
            if ( !bSet )
                SvXMLImportPropertyMapper::_FillPropertySet( 
                    GetProperties(), rPropSet, xInfo, rPropMapper, 
                    GetImport(), aContextIDs );
        }
        else
            SvXMLImportPropertyMapper::_FillPropertySet( 
                    GetProperties(), rPropSet, xInfo, rPropMapper,
                    GetImport(), aContextIDs );

        // have we found a combined characters
        sal_Int32 nIndex = aContextIDs[0].nIndex;
        if ( nIndex != -1 )
        {
            Any& rAny = GetProperties()[nIndex].maValue;
            sal_Bool bVal = *(sal_Bool*)rAny.getValue();
            bHasCombinedCharactersLetter = bVal;
        }

#ifdef CONV_STAR_FONTS
        // check for StarBats and StarMath fonts

        // iterate over aContextIDs entries 1..3
        for ( sal_Int32 i = 1; i < 4; i++ )
        {
            nIndex = aContextIDs[i].nIndex;
            if ( nIndex != -1 )
            {
                // Found!
                struct XMLPropertyState& rState = GetProperties()[nIndex];
                Any rAny = rState.maValue;
                sal_Int32 nMapperIndex = rState.mnIndex;

                // Now check for font name in rState and set corrected value,
                // if necessary.
                OUString sFontName;
                rAny >>= sFontName;
                if ( sFontName.getLength() > 0 )
                {
                    OUString sStarBats( RTL_CONSTASCII_USTRINGPARAM("StarBats" ) );
                    OUString sStarMath( RTL_CONSTASCII_USTRINGPARAM("StarMath" ) );
                    if ( sFontName.equalsIgnoreAsciiCase( sStarBats ) ||
                         sFontName.equalsIgnoreAsciiCase( sStarMath ) )
                    {
                        // construct new value
                        sFontName = OUString( 
                            RTL_CONSTASCII_USTRINGPARAM("StarSymbol") );
                        Any aAny( rAny );
                        aAny <<= sFontName;

                        // set property
                        OUString rPropertyName( 
                            rPropMapper->GetEntryAPIName(nMapperIndex) );
                        if ( xInfo->hasPropertyByName( rPropertyName ) )
                        {
                            rPropSet->setPropertyValue( rPropertyName, aAny );
                        }
                    }
                    // else: "normal" style name -> no correction is necessary
                }
                // else: no style name found -> illegal value -> ignore
            }
        }
#endif
    }
}
}//end of namespace binfilter
