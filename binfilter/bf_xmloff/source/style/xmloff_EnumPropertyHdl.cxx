/* -*- Mode: C++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */
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

#include <tools/debug.hxx>

#include <EnumPropertyHdl.hxx>

#include "xmluconv.hxx"

#include <comphelper/extract.hxx>

#include "rtl/ustring.hxx"

#include <rtl/ustrbuf.hxx>

/*

#include <bf_svtools/bf_solar.h>

#ifndef _INC_LIMITS
#include <limits.h>
#endif


*/

namespace binfilter {

using namespace ::rtl;
using namespace ::com::sun::star::uno;

///////////////////////////////////////////////////////////////////////////////
//
// class XMLEnumPropertyHdl
//

XMLEnumPropertyHdl::~XMLEnumPropertyHdl()
{
    // Nothing to do
}

sal_Bool XMLEnumPropertyHdl::importXML( const OUString& rStrImpValue, Any& rValue, const SvXMLUnitConverter& /*rUnitConverter*/ ) const
{
    USHORT nValue = 0;

    if( SvXMLUnitConverter::convertEnum( nValue, rStrImpValue, mpEnumMap ) )
    {
        switch( mrType.getTypeClass() )
        {
        case TypeClass_ENUM:
            rValue = ::cppu::int2enum( nValue, mrType );
            break;
        case TypeClass_LONG:
            rValue <<= (sal_Int32) nValue;
            break;
        case TypeClass_SHORT:
            rValue <<= (sal_Int16) nValue;
            break;
        case TypeClass_BYTE:
            rValue <<= (sal_Int8) nValue;
            break;
        default:
            OSL_FAIL( "Wrong type for enum property handler!" );
            return sal_False;
        }
        return sal_True;
    }

    return sal_False;
}

sal_Bool XMLEnumPropertyHdl::exportXML( OUString& rStrExpValue, const Any& rValue, const SvXMLUnitConverter& /*rUnitConverter*/ ) const
{
    sal_Int32 nValue(0);
    if(!(rValue >>= nValue ))
        if(!::cppu::enum2int(nValue, rValue) )
            return sal_False;

    OUStringBuffer aOut;

    if(!SvXMLUnitConverter::convertEnum( aOut, nValue, mpEnumMap ))
        return sal_False;

    rStrExpValue = aOut.makeStringAndClear();
    return sal_True;
}

}//end of namespace binfilter

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
