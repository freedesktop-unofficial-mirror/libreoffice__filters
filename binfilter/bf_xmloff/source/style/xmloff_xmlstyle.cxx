/*************************************************************************
 *
 *  $RCSfile: xmloff_xmlstyle.cxx,v $
 *
 *  $Revision: 1.2 $
 *
 *  last change: $Author: aw $ $Date: 2004-04-19 10:23:11 $
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

#ifndef _COM_SUN_STAR_XML_SAX_SAXPARSEEXCEPTION_HPP_
#include <com/sun/star/xml/sax/SAXParseException.hpp>
#endif
#ifndef _COM_SUN_STAR_XML_SAX_XEXTENDEDDOCUMENTHANDLER_HPP_
#include <com/sun/star/xml/sax/XExtendedDocumentHandler.hpp>
#endif
#ifndef _COM_SUN_STAR_XML_SAX_SAXEXCEPTION_HPP_
#include <com/sun/star/xml/sax/SAXException.hpp>
#endif
#ifndef _COM_SUN_STAR_XML_SAX_XDOCUMENTHANDLER_HPP_
#include <com/sun/star/xml/sax/XDocumentHandler.hpp>
#endif
#ifndef _COM_SUN_STAR_XML_SAX_XATTRIBUTELIST_HPP_
#include <com/sun/star/xml/sax/XAttributeList.hpp>
#endif
#ifndef _COM_SUN_STAR_XML_SAX_XLOCATOR_HPP_
#include <com/sun/star/xml/sax/XLocator.hpp>
#endif
#ifndef _COM_SUN_STAR_CONTAINER_XNAMECONTAINER_HPP_
#include <com/sun/star/container/XNameContainer.hpp>
#endif
#ifndef _COM_SUN_STAR_STYLE_XSTYLEFAMILIESSUPPLIER_HPP_
#include <com/sun/star/style/XStyleFamiliesSupplier.hpp>
#endif
#ifndef _XMLOFF_PAGEMASTERPROPMAPPER_HXX
#include "PageMasterPropMapper.hxx"
#endif

#ifndef _TOOLS_DEBUG_HXX //autogen wg. DBG_ASSERT
#include <tools/debug.hxx>
#endif
#ifndef _LIST_HXX
#include <tools/list.hxx>
#endif
#ifndef _URLOBJ_HXX
#include <tools/urlobj.hxx>
#endif

#ifndef _CNTRSRT_HXX
#include <svtools/cntnrsrt.hxx>
#endif
#ifndef _SFXITEMSET_HXX //autogen wg. SfxItemSet
#include <svtools/itemset.hxx>
#endif

#ifndef _XMLOFF_NMSPMAP_HXX
#include "nmspmap.hxx"
#endif

#ifndef _XMLOFF_XMLNMSPE_HXX
#include "xmlnmspe.hxx"
#endif

#ifndef _XMLOFF_XMLTOKEN_HXX
#include "xmltoken.hxx"
#endif

#ifndef _XMLOFF_FAMILIES_HXX
#include "families.hxx"
#endif

#ifndef _XMLOFF_XMLIMP_HXX
#include "xmlimp.hxx"
#endif
#ifndef _XMLOFF_XMLNUMI_HXX
#include "xmlnumi.hxx"
#endif

#ifndef _XMLOFF_XMLIMPPR_HXX
#include "xmlimppr.hxx"
#endif
#ifndef _XMLOFF_XMLSTYLE_HXX
#include "xmlstyle.hxx"
#endif
#ifndef _XMLOFF_TXTSTYLI_HXX
#include "txtstyli.hxx"
#endif
#ifndef _XMLOFF_TXTPRMAP_HXX
#include "txtprmap.hxx"
#endif
#ifndef _XMLOFF_XMLNUMFI_HXX
#include "xmlnumfi.hxx"
#endif
#ifndef _XMLOFF_XMLCHARTSTYLECONTEXT_HXX_
#include "XMLChartStyleContext.hxx"
#endif
#ifndef _XMLOFF_CHARTPROPERTYSETMAPPER_HXX_
#include "XMLChartPropertySetMapper.hxx"
#endif

#ifndef _XMLOFF_XMLSHAPESTYLECONTEXT_HXX
#include "XMLShapeStyleContext.hxx"
#endif

#ifndef _XMLOFF_FILLSTYLECONTEXTS_HXX_
#include "FillStyleContext.hxx"
#endif

#ifndef _XMLOFF_XMLFOOTNOTECONFIGURATIONIMPORTCONTEXT_HXX
#include "XMLFootnoteConfigurationImportContext.hxx"
#endif
#ifndef _XMLOFF_XMLINDEXBIBLIOGRAPHYCONFIGURATIONCONTEXT_HXX_
#include "XMLIndexBibliographyConfigurationContext.hxx"
#endif
#ifndef _XMLOFF_XMLLINENUMBERINGIMPORTCONTEXT_HXX_
#include "XMLLineNumberingImportContext.hxx"
#endif
#ifndef _XMLOFF_PAGEMASTERIMPORTCONTEXT_HXX
#include "PageMasterImportContext.hxx"
#endif
#ifndef _XMLOFF_PAGEMASTERIMPORTPROPMAPPER_HXX
#include "PageMasterImportPropMapper.hxx"
#endif
namespace binfilter {

using namespace ::rtl;
using namespace ::com::sun::star;
using namespace ::com::sun::star::uno;
using namespace ::com::sun::star::container;
using namespace ::com::sun::star::style;
using namespace ::binfilter::xmloff::token;

// ---------------------------------------------------------------------

static __FAR_DATA SvXMLTokenMapEntry aStyleStylesElemTokenMap[] =
{
    { XML_NAMESPACE_STYLE,	XML_STYLE,			XML_TOK_STYLE_STYLE                },
    { XML_NAMESPACE_STYLE,	XML_PAGE_MASTER,	XML_TOK_STYLE_PAGE_MASTER          },
    { XML_NAMESPACE_TEXT,	XML_LIST_STYLE, 	XML_TOK_TEXT_LIST_STYLE            },
    { XML_NAMESPACE_TEXT,	XML_OUTLINE_STYLE,	XML_TOK_TEXT_OUTLINE               },
    { XML_NAMESPACE_STYLE,	XML_DEFAULT_STYLE,	XML_TOK_STYLE_DEFAULT_STYLE        },
    { XML_NAMESPACE_DRAW,	XML_GRADIENT,		XML_TOK_STYLES_GRADIENTSTYLES      },
    { XML_NAMESPACE_DRAW,	XML_HATCH,			XML_TOK_STYLES_HATCHSTYLES         },
    { XML_NAMESPACE_DRAW,	XML_FILL_IMAGE,	    XML_TOK_STYLES_BITMAPSTYLES        },
    { XML_NAMESPACE_DRAW,	XML_TRANSPARENCY,	XML_TOK_STYLES_TRANSGRADIENTSTYLES },
    { XML_NAMESPACE_DRAW,	XML_MARKER,		    XML_TOK_STYLES_MARKERSTYLES        },
    { XML_NAMESPACE_DRAW,	XML_STROKE_DASH,	XML_TOK_STYLES_DASHSTYLES        },
    { XML_NAMESPACE_TEXT,	XML_FOOTNOTES_CONFIGURATION,    XML_TOK_TEXT_FOOTNOTE_CONFIG },
    { XML_NAMESPACE_TEXT,	XML_ENDNOTES_CONFIGURATION,     XML_TOK_TEXT_ENDNOTE_CONFIG },
    { XML_NAMESPACE_TEXT,	XML_BIBLIOGRAPHY_CONFIGURATION, XML_TOK_TEXT_BIBLIOGRAPHY_CONFIG },
    { XML_NAMESPACE_TEXT,   XML_LINENUMBERING_CONFIGURATION,XML_TOK_TEXT_LINENUMBERING_CONFIG },
    XML_TOKEN_MAP_END
};

const SvXMLTokenMap& SvXMLStylesContext::GetStyleStylesElemTokenMap()
{
    if( !pStyleStylesElemTokenMap )
        pStyleStylesElemTokenMap =
            new SvXMLTokenMap( aStyleStylesElemTokenMap );

    return *pStyleStylesElemTokenMap;
}

// ---------------------------------------------------------------------

void SvXMLStyleContext::SetAttribute( sal_uInt16 nPrefixKey,
                                      const OUString& rLocalName,
                                         const OUString& rValue )
{
    // TODO: use a map here
    if( XML_NAMESPACE_STYLE == nPrefixKey )
    {
        if( IsXMLToken( rLocalName, XML_FAMILY ) )
        {
            if( IsXMLToken( rValue, XML_PARAGRAPH ) )
                nFamily = (sal_uInt16)SFX_STYLE_FAMILY_PARA;
            else if( IsXMLToken( rValue, XML_TEXT ) )
                nFamily = (sal_uInt16)SFX_STYLE_FAMILY_CHAR;
        }
        else if( IsXMLToken( rLocalName, XML_NAME ) )
        {
            aName = rValue;
        }
        else if( IsXMLToken( rLocalName, XML_PARENT_STYLE_NAME ) )
        {
            aParent = rValue;
        }
        else if( IsXMLToken( rLocalName, XML_NEXT_STYLE_NAME ) )
        {
            aFollow = rValue;
        }
        else if( IsXMLToken( rLocalName, XML_HELP_FILE_NAME ) )
        {
            aHelpFile = rValue;
        }
        else if( IsXMLToken( rLocalName, XML_HELP_ID ) )
        {
            sal_Int32 nTmp = rValue.toInt32();
            nHelpId =
                (nTmp < 0L) ? 0U : ( (nTmp > USHRT_MAX) ? USHRT_MAX
                                                        : (sal_uInt16)nTmp );
        }
    }
}

TYPEINIT1( SvXMLStyleContext, SvXMLImportContext );

SvXMLStyleContext::SvXMLStyleContext(
        SvXMLImport& rImp, sal_uInt16 nPrfx,
        const OUString& rLName,
        const uno::Reference< xml::sax::XAttributeList >&,
        sal_uInt16 nFam, sal_Bool bDefault ) :
    SvXMLImportContext( rImp, nPrfx, rLName ),
    nHelpId( UCHAR_MAX ),
    nFamily( nFam ),
    bValid( sal_True ),
    bNew( sal_True ),
    bDefaultStyle( bDefault )
{
}

SvXMLStyleContext::~SvXMLStyleContext()
{
}

SvXMLImportContext *SvXMLStyleContext::CreateChildContext( sal_uInt16 nPrefix,
                                            const OUString& rLocalName,
                                            const uno::Reference< xml::sax::XAttributeList > & xAttrList )
{
    return new SvXMLImportContext( GetImport(), nPrefix, rLocalName );;
}

void SvXMLStyleContext::StartElement( const uno::Reference< xml::sax::XAttributeList > & xAttrList )
{
    sal_Int16 nAttrCount = xAttrList.is() ? xAttrList->getLength() : 0;
    for( sal_Int16 i=0; i < nAttrCount; i++ )
    {
        const OUString& rAttrName = xAttrList->getNameByIndex( i );
        OUString aLocalName;
        sal_uInt16 nPrefix = GetImport().GetNamespaceMap().GetKeyByAttrName( rAttrName,	&aLocalName );
        const OUString& rValue = xAttrList->getValueByIndex( i );

        SetAttribute( nPrefix, aLocalName, rValue );
    }
}

void SvXMLStyleContext::SetDefaults()
{
}

void SvXMLStyleContext::CreateAndInsert( sal_Bool bOverwrite )
{
}

void SvXMLStyleContext::CreateAndInsertLate( sal_Bool bOverwrite )
{
}

void SvXMLStyleContext::Finish( sal_Bool bOverwrite )
{
}

BOOL SvXMLStyleContext::IsTransient() const
{
    return sal_False;
}

// ---------------------------------------------------------------------

class SvXMLStyleIndex_Impl
{
    OUString 			  sName;
    sal_uInt16 			  nFamily;
    const SvXMLStyleContext *pStyle;

public:

    SvXMLStyleIndex_Impl( sal_uInt16 nFam, const OUString& rName ) :
        sName( rName ),
        nFamily( nFam ),
        pStyle ( 0 )
    {
    }

    SvXMLStyleIndex_Impl( const SvXMLStyleContext *pStl ) :
        sName( pStl->GetName() ),
        nFamily( pStl->GetFamily() ),
        pStyle ( pStl )
    {
    }

    const OUString& GetName() const { return sName; }
    sal_uInt16 GetFamily() const { return nFamily; }
    const SvXMLStyleContext *GetStyle() const { return pStyle; }
};

int SvXMLStyleIndexCmp_Impl( const SvXMLStyleIndex_Impl& r1,
                              const SvXMLStyleIndex_Impl& r2 )
{
    int nRet;
    if( (sal_uInt16)r1.GetFamily() < (sal_uInt16)r2.GetFamily() )
        nRet = -1;
    else if( (sal_uInt16)r1.GetFamily() > (sal_uInt16)r2.GetFamily() )
        nRet = 1;
    else
        nRet = (int)r1.GetName().compareTo( r2.GetName() );

    return nRet;
}

// ---------------------------------------------------------------------

typedef SvXMLStyleContext *SvXMLStyleContextPtr;
DECLARE_LIST( SvXMLStyleContexts_Impl, SvXMLStyleContextPtr )

DECLARE_CONTAINER_SORT_DEL( SvXMLStyleIndices_Impl, SvXMLStyleIndex_Impl )
IMPL_CONTAINER_SORT( SvXMLStyleIndices_Impl, SvXMLStyleIndex_Impl,
                       SvXMLStyleIndexCmp_Impl )


class SvXMLStylesContext_Impl
{
    SvXMLStyleContexts_Impl	aStyles;
    SvXMLStyleIndices_Impl	*pIndices;

    OUString	sId;
    OUString	sParentHRef;

#ifndef PRODUCT
    sal_uInt32 nIndexCreated;
#endif

    void FlushIndex() { delete pIndices; pIndices = 0; }

public:
    SvXMLStylesContext_Impl();
    ~SvXMLStylesContext_Impl();

    sal_uInt32 GetStyleCount() const { return aStyles.Count(); }

    const SvXMLStyleContext *GetStyle( sal_uInt32 i ) const
    {
        return i < aStyles.Count() ? aStyles.GetObject(i) : 0;
    }

    SvXMLStyleContext *GetStyle( sal_uInt32 i )
    {
        return i < aStyles.Count() ? aStyles.GetObject(i) : 0;
    }

    inline void AddStyle( SvXMLStyleContext *pStyle );
    void Clear();

    const SvXMLStyleContext *FindStyleChildContext( sal_uInt16 nFamily,
                                      const OUString& rName,
                                      sal_Bool bCreateIndex ) const;

    void SetId( const OUString& rId ) { sId = rId; }
    const OUString& GetId() { return sId; }

    void SetParentHRef( const OUString& rHRef ) { sParentHRef = rHRef; }
    const OUString& GetParentHRef() { return sParentHRef; }
};

SvXMLStylesContext_Impl::SvXMLStylesContext_Impl() :
#ifndef PRODUCT
    nIndexCreated( 0 ),
#endif
    aStyles( 20, 5 ),
    pIndices( 0 )
{}

SvXMLStylesContext_Impl::~SvXMLStylesContext_Impl()
{
    delete pIndices;

    while( aStyles.Count() )
    {
        SvXMLStyleContext *pStyle = aStyles.GetObject(0);
        aStyles.Remove( 0UL );
        pStyle->ReleaseRef();
    }
}

inline void SvXMLStylesContext_Impl::AddStyle( SvXMLStyleContext *pStyle )
{
    aStyles.Insert( pStyle, aStyles.Count() );
    pStyle->AddRef();

    FlushIndex();
}

void SvXMLStylesContext_Impl::Clear()
{
    FlushIndex();

    while( aStyles.Count() )
    {
        SvXMLStyleContext *pStyle = aStyles.GetObject(0);
        aStyles.Remove( 0UL );
        pStyle->ReleaseRef();
    }
}

const SvXMLStyleContext *SvXMLStylesContext_Impl::FindStyleChildContext(
                                  sal_uInt16 nFamily,
                                  const OUString& rName,
                                  sal_Bool bCreateIndex ) const
{
    const SvXMLStyleContext *pStyle = 0;

    if( !pIndices && bCreateIndex && aStyles.Count() > 0 )
    {
#ifndef PRODUCT
        DBG_ASSERT( 0==nIndexCreated,
                    "Performance warning: sdbcx::Index created multiple times" );
#endif
        ((SvXMLStylesContext_Impl *)this)->pIndices =
            new SvXMLStyleIndices_Impl( aStyles.Count(), 5 );
        for( sal_uInt32 i=0; i < aStyles.Count(); i++ )
        {
            SvXMLStyleIndex_Impl* pStyleIndex = new SvXMLStyleIndex_Impl( aStyles.GetObject(i));
            if (!pIndices->Insert( pStyleIndex ))
            {
                DBG_ERROR("Here is a double Style");
                delete pStyleIndex;
            }
        }
#ifndef PRODUCT
        ((SvXMLStylesContext_Impl *)this)->nIndexCreated++;
#endif
    }

    if( pIndices )
    {
        SvXMLStyleIndex_Impl aIndex( nFamily, rName );
        sal_uInt32 nPos = 0;
        if( pIndices->Seek_Entry( &aIndex, &nPos ) )
            pStyle = pIndices->GetObject( nPos )->GetStyle();
    }
    else
    {
        for( sal_uInt32 i=0; !pStyle && i < aStyles.Count(); i++ )
        {
            const SvXMLStyleContext *pS = aStyles.GetObject( i );
            if( pS->GetFamily() == nFamily &&
                pS->GetName() == rName )
                pStyle = pS;
        }
    }

    return pStyle;
}

// ---------------------------------------------------------------------

TYPEINIT1( SvXMLStylesContext, SvXMLImportContext );

sal_uInt32 SvXMLStylesContext::GetStyleCount() const
{
    return pImpl->GetStyleCount();
}

SvXMLStyleContext *SvXMLStylesContext::GetStyle( sal_uInt32 i )
{
    return pImpl->GetStyle( i );
}

const SvXMLStyleContext *SvXMLStylesContext::GetStyle( sal_uInt32 i ) const
{
    return pImpl->GetStyle( i );
}

SvXMLStyleContext *SvXMLStylesContext::CreateStyleChildContext(
        sal_uInt16 nPrefix,
        const OUString& rLocalName,
        const uno::Reference< xml::sax::XAttributeList > & xAttrList )
{
    SvXMLStyleContext *pStyle = NULL;

    if(GetImport().GetDataStylesImport())
    {
        pStyle = GetImport().GetDataStylesImport()->CreateChildContext(GetImport(), nPrefix,
                                               rLocalName, xAttrList, *this);
    }

    if (!pStyle)
    {
        const SvXMLTokenMap& rTokenMap = GetStyleStylesElemTokenMap();
        sal_uInt16 nToken = rTokenMap.Get( nPrefix, rLocalName );
        switch( nToken  )
        {
            case XML_TOK_STYLE_STYLE:
            case XML_TOK_STYLE_DEFAULT_STYLE:
            {
                sal_uInt16 nFamily = 0;
                sal_Int16 nAttrCount = xAttrList.is() ? xAttrList->getLength() : 0;
                for( sal_Int16 i=0; i < nAttrCount; i++ )
                {
                    const OUString& rAttrName = xAttrList->getNameByIndex( i );
                    OUString aLocalName;
                    sal_uInt16 nPrefix =
                        GetImport().GetNamespaceMap().GetKeyByAttrName( rAttrName,
                                                                    &aLocalName );
                    if( XML_NAMESPACE_STYLE == nPrefix &&
                        IsXMLToken( aLocalName, XML_FAMILY ) )
                    {
                        const OUString& rValue = xAttrList->getValueByIndex( i );
                        nFamily = GetFamily( rValue );
                        break;
                    }
                }
                pStyle = XML_TOK_STYLE_STYLE==nToken
                    ? CreateStyleStyleChildContext( nFamily, nPrefix,
                                                    rLocalName, xAttrList )
                    : CreateDefaultStyleStyleChildContext( nFamily, nPrefix,
                                                    rLocalName, xAttrList );
            }
            break;
            case XML_TOK_STYLE_PAGE_MASTER:
            {
                pStyle = new PageStyleContext( GetImport(), nPrefix,
                                                    rLocalName, xAttrList, *this );
            }
            break;
            case XML_TOK_TEXT_LIST_STYLE:
                pStyle = new SvxXMLListStyleContext( GetImport(), nPrefix,
                                                    rLocalName, xAttrList );
                break;
            case XML_TOK_TEXT_OUTLINE:
                pStyle = new SvxXMLListStyleContext( GetImport(), nPrefix,
                                                    rLocalName, xAttrList, sal_True );
                break;
            case XML_TOK_TEXT_FOOTNOTE_CONFIG:
#ifndef SVX_LIGHT
                pStyle = new XMLFootnoteConfigurationImportContext(GetImport(),
                                                                   nPrefix,
                                                                   rLocalName,
                                                                   xAttrList,
                                                                   sal_False);
#else
                // create default context to skip content
                pStyle = new SvXMLStyleContext( GetImport(), nPrefix, rLocalName, xAttrList );
#endif // #ifndef SVX_LIGHT
                break;

            case XML_TOK_TEXT_ENDNOTE_CONFIG:
#ifndef SVX_LIGHT
                pStyle = new XMLFootnoteConfigurationImportContext(GetImport(),
                                                                   nPrefix,
                                                                   rLocalName,
                                                                   xAttrList,
                                                                   sal_True);
#else
                // create default context to skip content
                pStyle = new SvXMLStyleContext( GetImport(), nPrefix, rLocalName, xAttrList );
#endif // #ifndef SVX_LIGHT
                break;

            case XML_TOK_TEXT_BIBLIOGRAPHY_CONFIG:
#ifndef SVX_LIGHT
                pStyle = new XMLIndexBibliographyConfigurationContext(
                    GetImport(), nPrefix, rLocalName, xAttrList);
#else
                // create default context to skip content
                pStyle = new SvXMLStyleContext( GetImport(), nPrefix, rLocalName, xAttrList );
#endif // #ifndef SVX_LIGHT
                break;

            case XML_TOK_TEXT_LINENUMBERING_CONFIG:
#ifndef SVX_LIGHT
                pStyle = new XMLLineNumberingImportContext(
                    GetImport(), nPrefix, rLocalName, xAttrList);
#else
                // create default context to skip content
                pStyle = new SvXMLStyleContext( GetImport(), nPrefix, rLocalName, xAttrList );
#endif // #ifndef SVX_LIGHT
                break;

            //
            // FillStyles
            //
            case XML_TOK_STYLES_GRADIENTSTYLES:
            {
                pStyle = new XMLGradientStyleContext( GetImport(), nPrefix, rLocalName, xAttrList );
                break;
            }
            case XML_TOK_STYLES_HATCHSTYLES:
            {
                pStyle = new XMLHatchStyleContext( GetImport(), nPrefix, rLocalName, xAttrList );
                break;
            }
            case XML_TOK_STYLES_BITMAPSTYLES:
            {
                pStyle = new XMLBitmapStyleContext( GetImport(), nPrefix, rLocalName, xAttrList );
                break;
            }
            case XML_TOK_STYLES_TRANSGRADIENTSTYLES:
            {
                pStyle = new XMLTransGradientStyleContext( GetImport(), nPrefix, rLocalName, xAttrList );
                break;
            }
            case XML_TOK_STYLES_MARKERSTYLES:
            {
                pStyle = new XMLMarkerStyleContext( GetImport(), nPrefix, rLocalName, xAttrList );
                break;
            }
            case XML_TOK_STYLES_DASHSTYLES:
            {
                pStyle = new XMLDashStyleContext( GetImport(), nPrefix, rLocalName, xAttrList );
                break;
            }
        }
    }

    return pStyle;
}

SvXMLStyleContext *SvXMLStylesContext::CreateStyleStyleChildContext(
        sal_uInt16 nFamily, sal_uInt16 nPrefix, const OUString& rLocalName,
        const uno::Reference< xml::sax::XAttributeList > & xAttrList )
{
    SvXMLStyleContext *pStyle = 0;

    switch( nFamily )
    {
        case XML_STYLE_FAMILY_TEXT_PARAGRAPH:
        case XML_STYLE_FAMILY_TEXT_TEXT:
        case XML_STYLE_FAMILY_TEXT_SECTION:
            pStyle = new XMLTextStyleContext( GetImport(), nPrefix, rLocalName,
                                              xAttrList, *this, nFamily );
            break;

        case XML_STYLE_FAMILY_CONTROL_ID:
            pStyle = const_cast< SvXMLImport& >( GetImport() ).GetFormImport()->createControlStyleContext(
                nPrefix, rLocalName, xAttrList, *this, nFamily );
            break;

        case XML_STYLE_FAMILY_TEXT_RUBY:
            pStyle = new XMLPropStyleContext( GetImport(), nPrefix, rLocalName,
                                              xAttrList, *this, nFamily );
            break;
        case XML_STYLE_FAMILY_SCH_CHART_ID:
#ifndef SVX_LIGHT
            pStyle = new XMLChartStyleContext( GetImport(), nPrefix, rLocalName,
                                               xAttrList, *this, nFamily );
#else
            // create default context to skip content
            pStyle = new SvXMLStyleContext( GetImport(), nPrefix, rLocalName, xAttrList, nFamily );
#endif
            break;

        case XML_STYLE_FAMILY_SD_GRAPHICS_ID:
        case XML_STYLE_FAMILY_SD_PRESENTATION_ID:
        case XML_STYLE_FAMILY_SD_POOL_ID:
            pStyle = new XMLShapeStyleContext( GetImport(), nPrefix, rLocalName,
                                               xAttrList, *this, nFamily );
    }

    return pStyle;
}

SvXMLStyleContext *SvXMLStylesContext::CreateDefaultStyleStyleChildContext(
        sal_uInt16 nFamily, sal_uInt16 nPrefix, const OUString& rLocalName,
        const uno::Reference< xml::sax::XAttributeList > & xAttrList )
{
    return 0;
}


sal_Bool SvXMLStylesContext::InsertStyleFamily( sal_uInt16 ) const
{
    return sal_True;
}

sal_uInt16 SvXMLStylesContext::GetFamily(
        const ::rtl::OUString& rValue ) const
{
    sal_uInt16 nFamily = 0U;
    if( IsXMLToken( rValue, XML_PARAGRAPH ) )
    {
        nFamily = XML_STYLE_FAMILY_TEXT_PARAGRAPH;
    }
    else if( IsXMLToken( rValue, XML_TEXT ) )
    {
        nFamily = XML_STYLE_FAMILY_TEXT_TEXT;
    }
    else if( IsXMLToken( rValue, XML_DATA_STYLE ) )
    {
        nFamily = XML_STYLE_FAMILY_DATA_STYLE;
    }
    else if ( IsXMLToken( rValue, XML_SECTION ) )
    {
        nFamily = XML_STYLE_FAMILY_TEXT_SECTION;
    }
    else if( IsXMLToken( rValue, XML_TABLE ) )
    {
        nFamily = XML_STYLE_FAMILY_TABLE_TABLE;
    }
    else if( IsXMLToken( rValue, XML_TABLE_COLUMN ) )
        nFamily = XML_STYLE_FAMILY_TABLE_COLUMN;
    else if( IsXMLToken( rValue, XML_TABLE_ROW ) )
        nFamily = XML_STYLE_FAMILY_TABLE_ROW;
    else if( IsXMLToken( rValue, XML_TABLE_CELL ) )
        nFamily = XML_STYLE_FAMILY_TABLE_CELL;
    else if( rValue.equalsAsciiL( RTL_CONSTASCII_STRINGPARAM(XML_STYLE_FAMILY_SD_GRAPHICS_NAME)))
    {
        nFamily = XML_STYLE_FAMILY_SD_GRAPHICS_ID;
    }
    else if( rValue.equalsAsciiL( RTL_CONSTASCII_STRINGPARAM(XML_STYLE_FAMILY_SD_PRESENTATION_NAME)))
    {
        nFamily = XML_STYLE_FAMILY_SD_PRESENTATION_ID;
    }
    else if( rValue.equalsAsciiL( RTL_CONSTASCII_STRINGPARAM(XML_STYLE_FAMILY_SD_POOL_NAME)))
    {
        nFamily = XML_STYLE_FAMILY_SD_POOL_ID;
    }
    else if( rValue.equalsAsciiL( RTL_CONSTASCII_STRINGPARAM(XML_STYLE_FAMILY_SD_DRAWINGPAGE_NAME)))
    {
        nFamily = XML_STYLE_FAMILY_SD_DRAWINGPAGE_ID;
    }
    else if( rValue.equalsAsciiL( RTL_CONSTASCII_STRINGPARAM( XML_STYLE_FAMILY_SCH_CHART_NAME )))
    {
        nFamily = XML_STYLE_FAMILY_SCH_CHART_ID;
    }
    else if ( IsXMLToken( rValue, XML_RUBY ) )
    {
        nFamily = XML_STYLE_FAMILY_TEXT_RUBY;
    }
    else if ( rValue.equalsAsciiL( RTL_CONSTASCII_STRINGPARAM(XML_STYLE_FAMILY_CONTROL_NAME) ) )
    {
        nFamily = XML_STYLE_FAMILY_CONTROL_ID;
    }

    return nFamily;
}

UniReference < SvXMLImportPropertyMapper > SvXMLStylesContext::GetImportPropertyMapper(
                        sal_uInt16 nFamily ) const
{
    UniReference < SvXMLImportPropertyMapper > xMapper;

    switch( nFamily )
    {
    case XML_STYLE_FAMILY_TEXT_PARAGRAPH:
        if( !xParaImpPropMapper.is() )
        {
            SvXMLStylesContext * pThis = (SvXMLStylesContext *)this;
            pThis->xParaImpPropMapper =
                pThis->GetImport().GetTextImport()
                     ->GetParaImportPropertySetMapper();
        }
        xMapper = xParaImpPropMapper;
        break;
    case XML_STYLE_FAMILY_TEXT_TEXT:
        if( !xTextImpPropMapper.is() )
        {
            SvXMLStylesContext * pThis = (SvXMLStylesContext *)this;
            pThis->xTextImpPropMapper =
                pThis->GetImport().GetTextImport()
                     ->GetTextImportPropertySetMapper();
        }
        xMapper = xTextImpPropMapper;
        break;

    case XML_STYLE_FAMILY_TEXT_SECTION:
        // don't cache section mapper, as it's rarely used
        // *sigh*, cast to non-const, because this is a const method,
        // but SvXMLImport::GetTextImport() isn't.
        xMapper = ((SvXMLStylesContext*)this)->GetImport().GetTextImport()->
            GetSectionImportPropertySetMapper();
        break;

    case XML_STYLE_FAMILY_TEXT_RUBY:
        // don't cache section mapper, as it's rarely used
        // *sigh*, cast to non-const, because this is a const method,
        // but SvXMLImport::GetTextImport() isn't.
        xMapper = ((SvXMLStylesContext*)this)->GetImport().GetTextImport()->
            GetRubyImportPropertySetMapper();
        break;

    case XML_STYLE_FAMILY_SD_GRAPHICS_ID:
    case XML_STYLE_FAMILY_SD_PRESENTATION_ID:
    case XML_STYLE_FAMILY_SD_POOL_ID:
        if(!xShapeImpPropMapper.is())
        {
            UniReference< XMLShapeImportHelper > aImpHelper = ((SvXMLImport&)GetImport()).GetShapeImport();
            ((SvXMLStylesContext*)this)->xShapeImpPropMapper =
                aImpHelper->GetPropertySetMapper();
        }
        xMapper = xShapeImpPropMapper;
        break;
#ifndef SVX_LIGHT
    case XML_STYLE_FAMILY_SCH_CHART_ID:
        if( ! xChartImpPropMapper.is() )
        {
            XMLPropertySetMapper *pPropMapper = new XMLChartPropertySetMapper();
            xChartImpPropMapper = new XMLChartImportPropertyMapper( pPropMapper, GetImport() );
        }
        xMapper = xChartImpPropMapper;
        break;
#endif
    case XML_STYLE_FAMILY_PAGE_MASTER:
        if( ! xPageImpPropMapper.is() )
        {
            XMLPropertySetMapper *pPropMapper =
                new XMLPageMasterPropSetMapper();
            xPageImpPropMapper =
                new PageMasterImportPropertyMapper( pPropMapper,
                                    ((SvXMLStylesContext*)this)->GetImport() );
        }
        xMapper = xPageImpPropMapper;
        break;
#ifndef SVX_LIGHT
#if SUPD>615 || defined(PRIV_DEBUG)
    case XML_STYLE_FAMILY_CONTROL_ID:
        xMapper = const_cast<SvXMLImport&>(GetImport()).GetFormImport()->getStylePropertyMapper().getBodyPtr();
        break;
#endif
#endif // #ifndef SVX_LIGHT
    }

    return xMapper;
}

Reference < XNameContainer > SvXMLStylesContext::GetStylesContainer(
                                                sal_uInt16 nFamily ) const
{
    Reference < XNameContainer > xStyles;
    OUString sName;
    switch( nFamily )
    {
    case XML_STYLE_FAMILY_TEXT_PARAGRAPH:
        if( xParaStyles.is() )
            xStyles = xParaStyles;
        else
            sName =
                OUString( RTL_CONSTASCII_USTRINGPARAM( "ParagraphStyles" ) );
        break;

    case XML_STYLE_FAMILY_TEXT_TEXT:
        if( xTextStyles.is() )
            xStyles = xTextStyles;
        else
            sName =
                OUString( RTL_CONSTASCII_USTRINGPARAM( "CharacterStyles" ) );
        break;
    }
    if( !xStyles.is() && sName.getLength() )
    {
        Reference< XStyleFamiliesSupplier > xFamiliesSupp(
                                        GetImport().GetModel(), UNO_QUERY );
        Reference< XNameAccess > xFamilies = xFamiliesSupp->getStyleFamilies();
        if (xFamilies->hasByName(sName))
        {
            Any aAny = xFamilies->getByName( sName );

            xStyles = *(Reference<XNameContainer>*)aAny.getValue();
            switch( nFamily )
            {
            case XML_STYLE_FAMILY_TEXT_PARAGRAPH:
                ((SvXMLStylesContext *)this)->xParaStyles = xStyles;
                break;

            case XML_STYLE_FAMILY_TEXT_TEXT:
                ((SvXMLStylesContext *)this)->xTextStyles = xStyles;
                break;
            }
        }
    }

    return xStyles;
}

OUString SvXMLStylesContext::GetServiceName( sal_uInt16 nFamily ) const
{
    String sServiceName;
    switch( nFamily )
    {
    case XML_STYLE_FAMILY_TEXT_PARAGRAPH:
        sServiceName = sParaStyleServiceName;
        break;
    case XML_STYLE_FAMILY_TEXT_TEXT:
        sServiceName = sTextStyleServiceName;
        break;
    }

    return sServiceName;
}


SvXMLStylesContext::SvXMLStylesContext( SvXMLImport& rImport, sal_uInt16 nPrfx,
                                        const OUString& rLName,
                                        const uno::Reference< xml::sax::XAttributeList > & xAttrList) :
    SvXMLImportContext( rImport, nPrfx, rLName ),
    pImpl( new SvXMLStylesContext_Impl ),
    pStyleStylesElemTokenMap( 0 ),
    sParaStyleServiceName( RTL_CONSTASCII_USTRINGPARAM( "com.sun.star.style.ParagraphStyle" ) ),
    sTextStyleServiceName( RTL_CONSTASCII_USTRINGPARAM( "com.sun.star.style.CharacterStyle" ) )
{
    sal_Int16 nAttrCount = xAttrList.is() ? xAttrList->getLength() : 0;
    for( sal_Int16 i=0; i < nAttrCount; i++ )
    {
        const OUString& rAttrName = xAttrList->getNameByIndex( i );
        OUString aLocalName;
        sal_uInt16 nPrefix =
            GetImport().GetNamespaceMap().GetKeyByAttrName( rAttrName,
                                                            &aLocalName );
        if( XML_NAMESPACE_NONE == nPrefix &&
            IsXMLToken( aLocalName, XML_ID ) )
        {
            pImpl->SetId( xAttrList->getValueByIndex( i ) );
        }
    }
}


SvXMLStylesContext::~SvXMLStylesContext()
{
    delete pStyleStylesElemTokenMap;
    delete pImpl;
}

SvXMLImportContext *SvXMLStylesContext::CreateChildContext( sal_uInt16 nPrefix,
                                         const OUString& rLocalName,
                                         const uno::Reference< xml::sax::XAttributeList > & xAttrList )
{
    SvXMLImportContext *pContext = 0;

    if( XML_NAMESPACE_OFFICE == nPrefix &&
        IsXMLToken( rLocalName, XML_USE_STYLES ) )
    {
        OUString sHRef;
        pContext = new SvXMLUseStylesContext( GetImport(), nPrefix, rLocalName,
                                              xAttrList, sHRef );
        pImpl->SetParentHRef( sHRef );
    }
    else
    {
        SvXMLStyleContext *pStyle =
            CreateStyleChildContext( nPrefix, rLocalName, xAttrList );
//		DBG_ASSERT( pStyle->GetFamily(), "Style without a family" );
        if( pStyle )
        {
            if( !pStyle->IsTransient() )
                pImpl->AddStyle( pStyle );
            pContext = pStyle;
        }
        else
        {
            pContext = new SvXMLImportContext( GetImport(), nPrefix,
                                               rLocalName );
        }
    }

    return pContext;
}

void SvXMLStylesContext::EndElement()
{
}

void SvXMLStylesContext::AddStyle(SvXMLStyleContext& rNew)
{
    pImpl->AddStyle( &rNew );
}

void SvXMLStylesContext::Clear()
{
    pImpl->Clear();
}

void SvXMLStylesContext::CopyStylesToDoc( sal_Bool bOverwrite,
                                          sal_Bool bFinish )
{
    // pass 1: create text, paragraph and frame styles
    sal_uInt32 nCount = GetStyleCount();
    sal_uInt32 i;

    for( i=0; i<nCount; i++ )
    {
        SvXMLStyleContext *pStyle = GetStyle( i );
        if( !pStyle )
            continue;

        if (pStyle->IsDefaultStyle())
            pStyle->SetDefaults();
        else if( InsertStyleFamily( pStyle->GetFamily() ) )
            pStyle->CreateAndInsert( bOverwrite );
    }

    // pass 2: create list styles (they require char styles)
    for( i=0; i<nCount; i++ )
    {
        SvXMLStyleContext *pStyle = GetStyle( i );
        if( !pStyle || pStyle->IsDefaultStyle())
            continue;

        if( InsertStyleFamily( pStyle->GetFamily() ) )
            pStyle->CreateAndInsertLate( bOverwrite );
    }

    // pass3: finish creation of styles
    if( bFinish )
        FinishStyles( bOverwrite );
}

void SvXMLStylesContext::FinishStyles( sal_Bool bOverwrite )
{
    sal_uInt32 nCount = GetStyleCount();
    for( sal_uInt32 i=0; i<nCount; i++ )
    {
        SvXMLStyleContext *pStyle = GetStyle( i );
        if( !pStyle || !pStyle->IsValid() || pStyle->IsDefaultStyle() )
            continue;

        if( InsertStyleFamily( pStyle->GetFamily() ) )
            pStyle->Finish( bOverwrite );
    }
}


const OUString& SvXMLStylesContext::GetId() const
{
    return pImpl->GetId();
}

const OUString& SvXMLStylesContext::GetParentHRef() const
{
    return pImpl->GetParentHRef();
}

const SvXMLStyleContext *SvXMLStylesContext::FindStyleChildContext(
                                  sal_uInt16 nFamily,
                                  const OUString& rName,
                                  sal_Bool bCreateIndex ) const
{
    return pImpl->FindStyleChildContext( nFamily, rName, bCreateIndex );
}

// ---------------------------------------------------------------------

SvXMLUseStylesContext::SvXMLUseStylesContext(
        SvXMLImport& rImp, sal_uInt16 nPrfx, const OUString& rLName,
        const uno::Reference< xml::sax::XAttributeList > & xAttrList,
        OUString& rHRef ) :
    SvXMLImportContext( rImp, nPrfx, rLName )
{
    sal_Int16 nAttrCount = xAttrList.is() ? xAttrList->getLength() : 0;
    for( sal_Int16 i=0; i < nAttrCount; i++ )
    {
        const OUString& rAttrName = xAttrList->getNameByIndex( i );
        OUString aLocalName;
        sal_uInt16 nPrefix =
            GetImport().GetNamespaceMap().GetKeyByAttrName( rAttrName,
                                                            &aLocalName );
        if( XML_NAMESPACE_XLINK == nPrefix &&
            IsXMLToken( aLocalName, XML_HREF ) )
        {
            rHRef = xAttrList->getValueByIndex( i );
            // TODO: Hack!
            if( rImp.GetLocator().is() )
            {
                // RelToAbs leaves "#foo" util::URL's untouched
                INetURLObject aBaseURL( rImp.GetLocator()->getSystemId() );
                INetURLObject aURL;
                if( aBaseURL.GetNewAbsURL( rHRef, &aURL ) )
                    rHRef = aURL.GetMainURL(INetURLObject::DECODE_TO_IURI);
            }
        }
    }
}

SvXMLUseStylesContext::~SvXMLUseStylesContext()
{
}


}//end of namespace binfilter
