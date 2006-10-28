/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: xmloff_XMLClipPropertyHandler.cxx,v $
 *
 *  $Revision: 1.4 $
 *
 *  last change: $Author: rt $ $Date: 2006-10-28 01:58:14 $
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

#ifndef _XMLOFF_XMLCLIPPROPERTYHANDLER_HXX
#include "XMLClipPropertyHandler.hxx"
#endif


#ifndef _RTL_USTRBUF_HXX_ 
#include <rtl/ustrbuf.hxx>
#endif

#ifndef _COM_SUN_STAR_TEXT_GRAPHICCROP_HPP_
#include <com/sun/star/text/GraphicCrop.hpp>
#endif

#ifndef _XMLOFF_XMLUCONV_HXX 
#include "xmluconv.hxx"
#endif

#ifndef _XMLOFF_XMLKYWD_HXX
#include <xmlkywd.hxx>
#endif
namespace binfilter {

using namespace ::rtl;
using namespace ::com::sun::star;
using namespace ::com::sun::star::uno;
using namespace ::com::sun::star::text;
using namespace ::binfilter::xmloff::token;

///////////////////////////////////////////////////////////////////////////////
//
// class XMLMeasurePropHdl
//

XMLClipPropertyHandler::~XMLClipPropertyHandler()
{
    // nothing to do
}

sal_Bool XMLClipPropertyHandler::equals(
        const Any& r1,
        const Any& r2 ) const
{
    GraphicCrop aCrop1, aCrop2;
    r1 >>= aCrop1;
    r2 >>= aCrop2;
    
    return aCrop1.Top == aCrop2.Top &&
           aCrop1.Bottom == aCrop2.Bottom &&
           aCrop1.Left == aCrop2.Left &&
           aCrop1.Right == aCrop2.Right;
}

sal_Bool XMLClipPropertyHandler::importXML( const OUString& rStrImpValue, uno::Any& rValue, const SvXMLUnitConverter& rUnitConverter ) const
{ 
    sal_Bool bRet = sal_False;
    sal_Int32 nLen = rStrImpValue.getLength();
    if( nLen > 6 &&
        0 == rStrImpValue.compareToAscii( sXML_rect, 4 ) &&
        rStrImpValue[4] == '(' &&
        rStrImpValue[nLen-1] == ')' )
    {
        GraphicCrop aCrop;
        OUString sTmp( rStrImpValue.copy( 5, nLen-6 ) );
        SvXMLTokenEnumerator aTokenEnum( sTmp );

        sal_uInt16 nPos = 0;
        OUString aToken;
        while( aTokenEnum.getNextToken( aToken ) )
        {
            sal_Int32 nVal = 0;
            if( !IsXMLToken(aToken, XML_AUTO) &&
                 !rUnitConverter.convertMeasure( nVal, aToken ) )
                break;

            switch( nPos )
            {
            case 0: aCrop.Top = nVal;	break;
            case 1: aCrop.Right = nVal;	break;
            case 2: aCrop.Bottom = nVal;	break;
            case 3: aCrop.Left = nVal;	break;
            }
            nPos++;
        }

        bRet = (4 == nPos );
        if( bRet )
            rValue <<= aCrop;
    }

    return bRet; 
}

sal_Bool XMLClipPropertyHandler::exportXML( OUString& rStrExpValue, const uno::Any& rValue, const SvXMLUnitConverter& rUnitConverter ) const
{ 
    sal_Bool bRet = sal_False;
      OUStringBuffer aOut(30);
    GraphicCrop aCrop;

    if( rValue >>= aCrop )
    {
        aOut.append( GetXMLToken(XML_RECT) );
        aOut.append( (sal_Unicode)'(' );
        rUnitConverter.convertMeasure( aOut, aCrop.Top );
        aOut.append( (sal_Unicode)' ' );
        rUnitConverter.convertMeasure( aOut, aCrop.Right );
        aOut.append( (sal_Unicode)' ' );
        rUnitConverter.convertMeasure( aOut, aCrop.Bottom );
        aOut.append( (sal_Unicode)' ' );
        rUnitConverter.convertMeasure( aOut, aCrop.Left );
        aOut.append( (sal_Unicode)')' );
        rStrExpValue = aOut.makeStringAndClear();

        bRet = sal_True;
    }

    return bRet;
}
}//end of namespace binfilter
