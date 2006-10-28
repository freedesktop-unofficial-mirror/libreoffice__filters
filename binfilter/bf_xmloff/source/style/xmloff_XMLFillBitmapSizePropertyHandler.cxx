/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: xmloff_XMLFillBitmapSizePropertyHandler.cxx,v $
 *
 *  $Revision: 1.4 $
 *
 *  last change: $Author: rt $ $Date: 2006-10-28 01:58:43 $
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


#ifndef _XMLOFF_XMLUCONV_HXX
#include "xmluconv.hxx"
#endif

#ifndef _RTL_USTRBUF_HXX_
#include <rtl/ustrbuf.hxx>
#endif

#ifndef _XMLOFF_XMLFILLBITMAPSIZEPROPERTYHANDLER_HXX
#include "XMLFillBitmapSizePropertyHandler.hxx"
#endif

namespace binfilter {

using namespace ::com::sun::star;
using namespace ::com::sun::star::uno;
using namespace ::rtl;

XMLFillBitmapSizePropertyHandler::XMLFillBitmapSizePropertyHandler()
{
}

XMLFillBitmapSizePropertyHandler::~XMLFillBitmapSizePropertyHandler()
{
}

sal_Bool XMLFillBitmapSizePropertyHandler::importXML(
    const OUString& rStrImpValue,
    Any& rValue,
    const SvXMLUnitConverter& rUnitConverter ) const
{
    sal_Int32 nValue;
    sal_Bool bRet;

    if( rStrImpValue.indexOf( sal_Unicode('%') ) != -1 )
    {
        bRet = rUnitConverter.convertPercent( nValue, rStrImpValue );
        nValue *= -1;
    }
    else
    {
        bRet = rUnitConverter.convertMeasure( nValue, rStrImpValue );
    }

    if( bRet )
        rValue <<= nValue;

    return bRet;
}

sal_Bool XMLFillBitmapSizePropertyHandler::exportXML(
    OUString& rStrExpValue,
    const Any& rValue,
    const SvXMLUnitConverter& rUnitConverter ) const
{
    OUStringBuffer aOut;

    sal_Int32 nValue;
    if( rValue >>= nValue )
    {
        if( nValue < 0 )
        {
            rUnitConverter.convertPercent( aOut, -nValue );
        }
        else
        {
            rUnitConverter.convertMeasure( aOut, nValue );
        }

        rStrExpValue = aOut.makeStringAndClear();
        return sal_True;
    }

    return sal_False;
}

}//end of namespace binfilter
