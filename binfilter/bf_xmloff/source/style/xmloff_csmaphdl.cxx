/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: xmloff_csmaphdl.cxx,v $
 *
 *  $Revision: 1.3 $
 *
 *  last change: $Author: rt $ $Date: 2005-09-09 09:49:01 $
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

#ifndef _XMLOFF_PROPERTYHANDLER_CASEMAPTYPES_HXX
#include <csmaphdl.hxx>
#endif

// auto strip #ifndef _XMLOFF_XMLTOKEN_HXX
// auto strip #include "xmltoken.hxx"
// auto strip #endif

#ifndef _XMLOFF_XMLUCONV_HXX 
#include "xmluconv.hxx"
#endif

#ifndef _RTL_USTRBUF_HXX_ 
#include <rtl/ustrbuf.hxx>
#endif

#ifndef _COM_SUN_STAR_STYLE_CASEMAP_HPP_
#include <com/sun/star/style/CaseMap.hpp>
#endif


// auto strip #ifndef _COM_SUN_STAR_UNO_ANY_HXX_
// auto strip #include <com/sun/star/uno/Any.hxx>
// auto strip #endif

// auto strip #ifndef _XMLOFF_XMLEMENT_HXX
// auto strip #include "xmlelement.hxx"
// auto strip #endif
namespace binfilter {

using namespace ::rtl;
using namespace ::com::sun::star;
using namespace ::binfilter::xmloff::token;

static SvXMLEnumMapEntry pXML_Casemap_Enum[] =
{
    { XML_NONE,				    style::CaseMap::NONE },
    { XML_CASEMAP_LOWERCASE,	style::CaseMap::LOWERCASE },
    { XML_CASEMAP_UPPERCASE,	style::CaseMap::UPPERCASE },
    { XML_CASEMAP_CAPITALIZE,	style::CaseMap::TITLE },
    { XML_TOKEN_INVALID,        0 }
};

///////////////////////////////////////////////////////////////////////////////
//
// class XMLPosturePropHdl
//

XMLCaseMapPropHdl::~XMLCaseMapPropHdl()
{
    // nothing to do
}

sal_Bool XMLCaseMapPropHdl::importXML( const OUString& rStrImpValue, uno::Any& rValue, const SvXMLUnitConverter& rUnitConverter ) const
{ 
    sal_Bool bRet = sal_False;
    sal_uInt16 nVal;

    if( ( bRet = rUnitConverter.convertEnum( nVal, rStrImpValue, pXML_Casemap_Enum ) ) )
        rValue <<= nVal;

    return bRet; 
}

sal_Bool XMLCaseMapPropHdl::exportXML( OUString& rStrExpValue, const uno::Any& rValue, const SvXMLUnitConverter& rUnitConverter ) const
{ 
    sal_Bool bRet = sal_False;
    sal_uInt16 nValue;
    OUStringBuffer aOut;

    if( rValue >>= nValue )
    {
        if( ( bRet = rUnitConverter.convertEnum( aOut, nValue, pXML_Casemap_Enum ) ) )
            rStrExpValue = aOut.makeStringAndClear();
    }
    
    return bRet;
}

///////////////////////////////////////////////////////////////////////////////
//
// class XMLCaseMapVariantHdl
//

XMLCaseMapVariantHdl::~XMLCaseMapVariantHdl()
{
    // nothing to do
}

sal_Bool XMLCaseMapVariantHdl::importXML( const OUString& rStrImpValue, uno::Any& rValue, const SvXMLUnitConverter& rUnitConverter ) const
{ 
    sal_Bool bRet = sal_False;

    if( IsXMLToken( rStrImpValue, XML_CASEMAP_SMALL_CAPS ) )
    {
        rValue <<= (sal_Int16)style::CaseMap::SMALLCAPS;
        bRet = sal_True;
    }
    else if( IsXMLToken( rStrImpValue, XML_CASEMAP_NORMAL ) )
    {
        rValue <<= (sal_Int16)style::CaseMap::NONE;
        bRet = sal_True;
    }

    return bRet; 
}

sal_Bool XMLCaseMapVariantHdl::exportXML( OUString& rStrExpValue, const uno::Any& rValue, const SvXMLUnitConverter& rUnitConverter ) const
{ 
    sal_uInt16 nValue;
    OUStringBuffer aOut;

    if( rValue >>= nValue )
    {
        switch( nValue )
        {
        case style::CaseMap::NONE:
            aOut.append( GetXMLToken(XML_CASEMAP_NORMAL) );
            break;
        case style::CaseMap::SMALLCAPS:
            aOut.append( GetXMLToken(XML_CASEMAP_SMALL_CAPS) );
            break;
        }
    }

    rStrExpValue = aOut.makeStringAndClear();
    return rStrExpValue.getLength();
}
}//end of namespace binfilter
