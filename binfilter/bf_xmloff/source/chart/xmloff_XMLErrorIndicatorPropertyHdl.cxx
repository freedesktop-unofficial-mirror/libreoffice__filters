/*************************************************************************
 *
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER.
 *
 * Copyright 2000, 2010 Oracle and/or its affiliates.
 *
 * OpenOffice.org - a multi-platform office productivity suite
 *
 * This file is part of OpenOffice.org.
 *
 * OpenOffice.org is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License version 3
 * only, as published by the Free Software Foundation.
 *
 * OpenOffice.org is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License version 3 for more details
 * (a copy is included in the LICENSE file that accompanied this code).
 *
 * You should have received a copy of the GNU Lesser General Public License
 * version 3 along with OpenOffice.org.  If not, see
 * <http://www.openoffice.org/license.html>
 * for a copy of the LGPLv3 License.
 *
 ************************************************************************/
#include "XMLErrorIndicatorPropertyHdl.hxx"

#ifndef _XMLOFF_XMLUCONV_HXX
#include "xmluconv.hxx"
#endif
#ifndef _COM_SUN_STAR_CHART_CHARTERRORINDICATORTYPE_HPP_
#include <com/sun/star/chart/ChartErrorIndicatorType.hpp>
#endif
#ifndef _RTL_USTRBUF_HXX_
#include <rtl/ustrbuf.hxx>
#endif
namespace binfilter {

using namespace ::com::sun::star;

XMLErrorIndicatorPropertyHdl::~XMLErrorIndicatorPropertyHdl()
{}

sal_Bool XMLErrorIndicatorPropertyHdl::importXML( const ::rtl::OUString& rStrImpValue,
                                                  uno::Any& rValue, const SvXMLUnitConverter& rUnitConverter ) const
{
    sal_Bool bValue;
    SvXMLUnitConverter::convertBool( bValue, rStrImpValue );

    // modify existing value
    chart::ChartErrorIndicatorType eType = chart::ChartErrorIndicatorType_NONE;
    if( rValue.hasValue())
        rValue >>= eType;

    if( bValue )	// enable flag
    {
        if( eType != chart::ChartErrorIndicatorType_TOP_AND_BOTTOM )
        {
            if( mbUpperIndicator )
                eType = ( eType == chart::ChartErrorIndicatorType_LOWER )
                    ? chart::ChartErrorIndicatorType_TOP_AND_BOTTOM
                    : chart::ChartErrorIndicatorType_UPPER;
            else
                eType = ( eType == chart::ChartErrorIndicatorType_UPPER )
                    ? chart::ChartErrorIndicatorType_TOP_AND_BOTTOM
                    : chart::ChartErrorIndicatorType_LOWER;
        }
    }
    else			// disable flag
    {
        if( eType != chart::ChartErrorIndicatorType_NONE )
        {
            if( mbUpperIndicator )
                eType = ( eType == chart::ChartErrorIndicatorType_UPPER )
                    ? chart::ChartErrorIndicatorType_NONE
                    : chart::ChartErrorIndicatorType_LOWER;
            else
                eType = ( eType == chart::ChartErrorIndicatorType_LOWER )
                    ? chart::ChartErrorIndicatorType_NONE
                    : chart::ChartErrorIndicatorType_UPPER;
        }
    }

    rValue <<= eType;

    return sal_True;
}

sal_Bool XMLErrorIndicatorPropertyHdl::exportXML( ::rtl::OUString& rStrExpValue,
                                                  const uno::Any& rValue, const SvXMLUnitConverter& rUnitConverter ) const
{
    ::rtl::OUStringBuffer aBuffer;
    chart::ChartErrorIndicatorType eType;

    rValue >>= eType;
    sal_Bool bValue = ( eType == chart::ChartErrorIndicatorType_TOP_AND_BOTTOM ||
                        ( mbUpperIndicator
                          ? ( eType == chart::ChartErrorIndicatorType_UPPER )
                          : ( eType == chart::ChartErrorIndicatorType_LOWER )));

    if( bValue )
    {
        SvXMLUnitConverter::convertBool( aBuffer, bValue );
        rStrExpValue = aBuffer.makeStringAndClear();
    }

    // only export if set to true
    return bValue;
}
}//end of namespace binfilter
