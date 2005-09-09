/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: xmloff_XMLBitmapRepeatOffsetPropertyHandler.cxx,v $
 *
 *  $Revision: 1.3 $
 *
 *  last change: $Author: rt $ $Date: 2005-09-09 09:43:11 $
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

// auto strip #ifndef _XMLOFF_XMLTOKEN_HXX
// auto strip #include "xmltoken.hxx"
// auto strip #endif

#ifndef _XMLOFF_XMLUCONV_HXX 
#include "xmluconv.hxx"
#endif

#ifndef _RTL_USTRBUF_HXX_ 
#include <rtl/ustrbuf.hxx>
#endif

// auto strip #ifndef _COM_SUN_STAR_UNO_ANY_HXX_
// auto strip #include <com/sun/star/uno/Any.hxx>
// auto strip #endif

#ifndef _XMLOFF_XMLBITMAPREPEATOFFSETPROPERTYHANDLER_HXX
#include "XMLBitmapRepeatOffsetPropertyHandler.hxx"
#endif
namespace binfilter {

using namespace ::com::sun::star;
using namespace ::com::sun::star::uno;
using namespace ::rtl;

using ::binfilter::xmloff::token::GetXMLToken;
using ::binfilter::xmloff::token::XML_VERTICAL;
using ::binfilter::xmloff::token::XML_HORIZONTAL;


XMLBitmapRepeatOffsetPropertyHandler::XMLBitmapRepeatOffsetPropertyHandler( sal_Bool bX )
:	mbX( bX ),
    msVertical( GetXMLToken(XML_VERTICAL) ),
    msHorizontal( GetXMLToken(XML_HORIZONTAL) )
{
}

XMLBitmapRepeatOffsetPropertyHandler::~XMLBitmapRepeatOffsetPropertyHandler() 
{
}

sal_Bool XMLBitmapRepeatOffsetPropertyHandler::importXML(
    const OUString& rStrImpValue,
    Any& rValue,
    const SvXMLUnitConverter& rUnitConverter ) const
{ 
    SvXMLTokenEnumerator aTokenEnum( rStrImpValue );
    OUString aToken;
    if( aTokenEnum.getNextToken( aToken ) )
    {
        sal_Int32 nValue;
        if( SvXMLUnitConverter::convertPercent( nValue, aToken ) )
        {
            if( aTokenEnum.getNextToken( aToken ) )
            {
                if( ( mbX && ( aToken == msHorizontal ) ) || ( !mbX && ( aToken == msVertical ) ) )
                {
                    rValue <<= nValue;
                    return sal_True;
                }
            }
        }
    }

    return sal_False;
    
}

sal_Bool XMLBitmapRepeatOffsetPropertyHandler::exportXML( 
    OUString& rStrExpValue,
    const Any& rValue,
    const SvXMLUnitConverter& rUnitConverter ) const
{ 
    OUStringBuffer aOut;
    
    sal_Int32 nValue;
    if( rValue >>= nValue )
    {
        SvXMLUnitConverter::convertPercent( aOut, nValue );
        aOut.append( sal_Unicode( ' ' ) );
        aOut.append( mbX ? msHorizontal : msVertical );
        rStrExpValue = aOut.makeStringAndClear();

        return sal_True;
    }

    return sal_False;
}

}//end of namespace binfilter
