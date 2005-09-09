/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: xmloff_xmltabi.cxx,v $
 *
 *  $Revision: 1.3 $
 *
 *  last change: $Author: rt $ $Date: 2005-09-09 09:59:50 $
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

// auto strip #ifndef _COM_SUN_STAR_STYLE_TABALIGN_HPP_
// auto strip #include <com/sun/star/style/TabAlign.hpp>
// auto strip #endif

// auto strip #ifndef _RTL_USTRBUF_HXX_
// auto strip #include <rtl/ustrbuf.hxx>
// auto strip #endif

// auto strip #ifndef _XMLOFF_XMLTKMAP_HXX
// auto strip #include "xmltkmap.hxx"
// auto strip #endif
#ifndef _XMLOFF_NMSPMAP_HXX
#include "nmspmap.hxx"
#endif
#ifndef _XMLOFF_XMLNMSPE_HXX
#include "xmlnmspe.hxx"
#endif
#ifndef _XMLOFF_XMLIMP_HXX
#include "xmlimp.hxx"
#endif

#ifndef _COM_SUN_STAR_STYLE_TABSTOP_HPP_
#include <com/sun/star/style/TabStop.hpp>
#endif

// auto strip #ifndef _XMLOFF_XMLTOKEN_HXX
// auto strip #include "xmltoken.hxx"
// auto strip #endif
// auto strip #ifndef _XMLOFF_I18NMAP_HXX
// auto strip #include "i18nmap.hxx"
// auto strip #endif
#ifndef _XMLOFF_XMLUCONV_HXX
#include "xmluconv.hxx"
#endif

#include "xmltabi.hxx"

#define _SVSTDARR_USHORTS
#include <svtools/svstdarr.hxx>
namespace binfilter {

using namespace ::rtl;
using namespace ::com::sun::star;
using namespace ::binfilter::xmloff::token;

// ---

enum SvXMLTokenMapAttrs
{
    XML_TOK_TABSTOP_POSITION,
    XML_TOK_TABSTOP_TYPE,
    XML_TOK_TABSTOP_CHAR,
    XML_TOK_TABSTOP_LEADER,
    XML_TOK_TABSTOP_END=XML_TOK_UNKNOWN
};

static __FAR_DATA SvXMLTokenMapEntry aTabsAttributesAttrTokenMap[] =
{
    { XML_NAMESPACE_STYLE, XML_POSITION,	 XML_TOK_TABSTOP_POSITION },
    { XML_NAMESPACE_STYLE, XML_TYPE,	  	 XML_TOK_TABSTOP_TYPE },
    { XML_NAMESPACE_STYLE, XML_CHAR,	  	 XML_TOK_TABSTOP_CHAR },
    { XML_NAMESPACE_STYLE, XML_LEADER_CHAR,  XML_TOK_TABSTOP_LEADER },
    XML_TOKEN_MAP_END 
};

// ---

class SvxXMLTabStopContext_Impl : public SvXMLImportContext
{
private:
     style::TabStop	aTabStop;

public:
    TYPEINFO();

    SvxXMLTabStopContext_Impl( SvXMLImport& rImport, sal_uInt16 nPrfx,
                               const OUString& rLName,
                               const uno::Reference< xml::sax::XAttributeList > & xAttrList );

    virtual ~SvxXMLTabStopContext_Impl();

    virtual SvXMLImportContext *CreateChildContext( sal_uInt16 nPrefix,
                                   const OUString& rLocalName,
                                   const uno::Reference< xml::sax::XAttributeList > & xAttrList );

    const style::TabStop& getTabStop() const { return aTabStop; }
};

TYPEINIT1( SvxXMLTabStopContext_Impl, SvXMLImportContext );

SvxXMLTabStopContext_Impl::SvxXMLTabStopContext_Impl(
                               SvXMLImport& rImport, sal_uInt16 nPrfx,
                               const OUString& rLName,
                               const uno::Reference< xml::sax::XAttributeList > & xAttrList )
: SvXMLImportContext( rImport, nPrfx, rLName )
{
    aTabStop.Position = 0;
    aTabStop.Alignment = style::TabAlign_LEFT;
    aTabStop.DecimalChar = sal_Unicode( ',' );
    aTabStop.FillChar = sal_Unicode( ' ' );

    SvXMLTokenMap aTokenMap( aTabsAttributesAttrTokenMap );

    sal_Int16 nAttrCount = xAttrList.is() ? xAttrList->getLength() : 0;
    for( sal_Int16 i=0; i < nAttrCount; i++ )
    {
        const OUString& rAttrName = xAttrList->getNameByIndex( i );
        OUString aLocalName;
        sal_uInt16 nPrefix =
            GetImport().GetNamespaceMap().GetKeyByAttrName( rAttrName,
                                                            &aLocalName );
        const OUString& rValue = xAttrList->getValueByIndex( i );

        sal_Int32 nVal;
        switch( aTokenMap.Get( nPrefix, aLocalName ) )
        {
        case XML_TOK_TABSTOP_POSITION:
            if( GetImport().GetMM100UnitConverter().convertMeasure( nVal,
                                                                    rValue ) )
                aTabStop.Position = nVal;
            break;
        case XML_TOK_TABSTOP_TYPE:
            if( IsXMLToken( rValue, XML_LEFT ) )
            {
                aTabStop.Alignment = style::TabAlign_LEFT;
            }
            else if( IsXMLToken( rValue, XML_RIGHT ) )
            {
                aTabStop.Alignment = style::TabAlign_RIGHT;
            }
            else if( IsXMLToken( rValue, XML_CENTER ) )
            {
                aTabStop.Alignment = style::TabAlign_CENTER;
            }
            else if( IsXMLToken( rValue, XML_CHAR ) )
            {
                aTabStop.Alignment = style::TabAlign_DECIMAL;
            }
            else if( IsXMLToken( rValue, XML_DEFAULT ) )
            {
                aTabStop.Alignment = style::TabAlign_DEFAULT;
            }
            break;
        case XML_TOK_TABSTOP_CHAR:
            if( 0 != rValue.getLength() )
                aTabStop.DecimalChar = rValue[0];
            break;
        case XML_TOK_TABSTOP_LEADER:
            if( 0 != rValue.getLength() )
                aTabStop.FillChar = rValue[0];
            break;
        }
    }
}

SvxXMLTabStopContext_Impl::~SvxXMLTabStopContext_Impl()
{
}

SvXMLImportContext *SvxXMLTabStopContext_Impl::CreateChildContext(
                                   sal_uInt16 nPrefix,
                                   const OUString& rLocalName,
                                   const uno::Reference< xml::sax::XAttributeList > & xAttrList )
{
    return new SvXMLImportContext( GetImport(), nPrefix, rLocalName );
}




typedef SvxXMLTabStopContext_Impl *SvxXMLTabStopContext_Impl_ImplPtr;
SV_DECL_PTRARR( SvxXMLTabStopArray_Impl, SvxXMLTabStopContext_Impl_ImplPtr,	20, 5 )


// ---

TYPEINIT1( SvxXMLTabStopImportContext, XMLElementPropertyContext );

SvxXMLTabStopImportContext::SvxXMLTabStopImportContext(
                                SvXMLImport& rImport, sal_uInt16 nPrfx,
                                const OUString& rLName,
                                const XMLPropertyState& rProp,
                                 ::std::vector< XMLPropertyState > &rProps )
: XMLElementPropertyContext( rImport, nPrfx, rLName, rProp, rProps ),
  mpTabStops( NULL )
{
}

SvxXMLTabStopImportContext::~SvxXMLTabStopImportContext()
{
    if( mpTabStops )
    {
        sal_uInt16 nCount = mpTabStops->Count();
        while( nCount )
        {
            nCount--;
            SvxXMLTabStopContext_Impl *pTabStop = (*mpTabStops)[nCount];
            mpTabStops->Remove( nCount, 1 );
            pTabStop->ReleaseRef();
        }
    }

    delete mpTabStops;
}

SvXMLImportContext *SvxXMLTabStopImportContext::CreateChildContext(
                                   sal_uInt16 nPrefix,
                                   const OUString& rLocalName,
                                   const uno::Reference< xml::sax::XAttributeList > & xAttrList )
{
    SvXMLImportContext *pContext = 0;

    if( XML_NAMESPACE_STYLE == nPrefix && IsXMLToken( rLocalName, XML_TAB_STOP ) )
    {
        // create new tabstop import context
        SvxXMLTabStopContext_Impl *pTabStopContext =
            new SvxXMLTabStopContext_Impl( GetImport(), nPrefix, rLocalName,
                                           xAttrList );

        // add new tabstop to array of tabstops
        if( !mpTabStops )
            mpTabStops = new SvxXMLTabStopArray_Impl;

        mpTabStops->Insert( pTabStopContext, mpTabStops->Count() );
        pTabStopContext->AddRef();
        
        pContext = pTabStopContext;
    }
    else
    {
        pContext = new SvXMLImportContext( GetImport(), nPrefix, rLocalName );
    }
    
    return pContext;
}

void SvxXMLTabStopImportContext::EndElement( )
{	
    sal_uInt16 nCount = mpTabStops ? mpTabStops->Count() : 0;
    uno::Sequence< style::TabStop> aSeq( nCount );
        
    if( mpTabStops )
    {
        sal_uInt16 nNewCount = 0;

        style::TabStop* pTabStops = aSeq.getArray();
        for( sal_uInt16 i=0; i < nCount; i++ )
        {
            SvxXMLTabStopContext_Impl *pTabStopContext = (*mpTabStops)[i];
            const style::TabStop& rTabStop = pTabStopContext->getTabStop();
            sal_Bool bDflt = style::TabAlign_DEFAULT == rTabStop.Alignment;
            if( !bDflt || 0==i )
            {
                *pTabStops++ = pTabStopContext->getTabStop();
                nNewCount++;
            }
            if( bDflt && 0==i )
                break;
        }

        if( nCount != nNewCount )
            aSeq.realloc( nNewCount );
    }
    aProp.maValue <<= aSeq;

    SetInsert( sal_True );
    XMLElementPropertyContext::EndElement();

}




}//end of namespace binfilter
