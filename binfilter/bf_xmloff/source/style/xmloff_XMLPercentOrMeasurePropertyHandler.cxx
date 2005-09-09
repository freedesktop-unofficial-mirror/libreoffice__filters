/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: xmloff_XMLPercentOrMeasurePropertyHandler.cxx,v $
 *
 *  $Revision: 1.3 $
 *
 *  last change: $Author: rt $ $Date: 2005-09-09 09:46:25 $
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

// auto strip #ifndef _TOOLS_DEBUG_HXX 
// auto strip #include <tools/debug.hxx>
// auto strip #endif

// auto strip #ifndef _COM_SUN_STAR_UNO_ANY_HXX_
// auto strip #include <com/sun/star/uno/Any.hxx>
// auto strip #endif

#ifndef _RTL_USTRBUF_HXX_
#include <rtl/ustrbuf.hxx>
#endif

#ifndef _XMLOFF_XMLPERCENTORMEASUREPROPERTYHANDLER_HXX
#include "XMLPercentOrMeasurePropertyHandler.hxx"
#endif

#ifndef _XMLOFF_XMLUCONV_HXX 
#include "xmluconv.hxx"
#endif
namespace binfilter {

using namespace ::com::sun::star;
using namespace ::com::sun::star::uno;
using namespace ::rtl;

XMLPercentOrMeasurePropertyHandler::XMLPercentOrMeasurePropertyHandler( sal_Bool bPercent )
: mbPercent( bPercent )
{
}

XMLPercentOrMeasurePropertyHandler::~XMLPercentOrMeasurePropertyHandler()
{
}

sal_Bool XMLPercentOrMeasurePropertyHandler::importXML(
    const OUString& rStrImpValue,
    Any& rValue,
    const SvXMLUnitConverter& rUnitConverter ) const
{
    if( (rStrImpValue.indexOf( sal_Unicode('%') ) != -1) != mbPercent )
        return sal_False;

    sal_Int32 nValue;

    if( mbPercent )
    {
        if( !rUnitConverter.convertPercent( nValue, rStrImpValue ) )
            return sal_False;
    }
    else
    {
        if( !rUnitConverter.convertMeasure( nValue, rStrImpValue ) )
            return sal_False;
    }

    rValue <<= nValue;
    return sal_True;
}

sal_Bool XMLPercentOrMeasurePropertyHandler::exportXML(
    OUString& rStrExpValue,
    const Any& rValue,
    const SvXMLUnitConverter& rUnitConverter ) const
{
      OUStringBuffer aOut;

    sal_Int32 nValue;
    if( !(rValue >>= nValue ) )
        return sal_False;

    if( mbPercent )
    {
         rUnitConverter.convertPercent( aOut, nValue );
    }
    else
    {
         rUnitConverter.convertMeasure( aOut, nValue );
    }

    rStrExpValue = aOut.makeStringAndClear();
    return sal_True;
}
}//end of namespace binfilter
