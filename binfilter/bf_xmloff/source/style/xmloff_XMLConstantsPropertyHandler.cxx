/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: xmloff_XMLConstantsPropertyHandler.cxx,v $
 *
 *  $Revision: 1.4 $
 *
 *  last change: $Author: rt $ $Date: 2006-10-28 01:58:26 $
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

#ifndef _TOOLS_DEBUG_HXX 
#include <tools/debug.hxx>
#endif

#ifndef _XMLOFF_XMLUCONV_HXX 
#include "xmluconv.hxx"
#endif

#ifndef _RTL_USTRBUF_HXX_ 
#include <rtl/ustrbuf.hxx>
#endif


#ifndef _XMLOFF_XMLCONSTANTSPROPERTYHANDLER_HXX
#include "XMLConstantsPropertyHandler.hxx"
#endif
namespace binfilter {

using namespace ::com::sun::star::uno;
using namespace ::rtl;
using ::binfilter::xmloff::token::XMLTokenEnum;

XMLConstantsPropertyHandler::XMLConstantsPropertyHandler(
    const SvXMLEnumMapEntry *pM,
    enum XMLTokenEnum eDflt ) :
        pMap( pM ),
        eDefault( eDflt )
{
}

XMLConstantsPropertyHandler::~XMLConstantsPropertyHandler() 
{
}

sal_Bool XMLConstantsPropertyHandler::importXML(
    const OUString& rStrImpValue,
    Any& rValue,
    const SvXMLUnitConverter& rUnitConverter ) const
{ 
    sal_uInt16 nEnum;
    sal_Bool bRet = rUnitConverter.convertEnum( nEnum, rStrImpValue, pMap );

    if( bRet )
        rValue <<= (sal_Int16)nEnum;

    return bRet; 
}

sal_Bool XMLConstantsPropertyHandler::exportXML( 
    OUString& rStrExpValue,
    const Any& rValue,
    const SvXMLUnitConverter& rUnitConverter ) const
{ 
    OUStringBuffer aOut;
    
    sal_Bool bRet = false;

    sal_Int32 nEnum;

    if( rValue.hasValue() && (rValue.getValueTypeClass() == TypeClass_ENUM))
    {
        nEnum = *((sal_Int32*)rValue.getValue());
        bRet = true;
    }
    else 
    {
        bRet = (rValue >>= nEnum );
    }

    if( bRet )
    {
        if( (nEnum >= 0) && (nEnum <= 0xffff) )
        {
            sal_uInt16 nConst = static_cast<sal_uInt16>( nEnum );

            bRet = rUnitConverter.convertEnum( aOut, nConst, pMap, eDefault ); 

            rStrExpValue = aOut.makeStringAndClear();
        }
        else
        {
            DBG_ERROR("XMLConstantsPropertyHandler::exportXML() constant is out of range for implementation using sal_uInt16");
        }
    }
    else
    {
        DBG_ERROR("XMLConstantsPropertyHandler::exportXML() could not convert any to sal_Int32");
    }

    return bRet;
}

}//end of namespace binfilter
