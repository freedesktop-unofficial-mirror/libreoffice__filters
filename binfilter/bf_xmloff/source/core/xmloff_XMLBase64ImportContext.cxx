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

#include "xmlimp.hxx"
#include "xmluconv.hxx"

#include <com/sun/star/io/XOutputStream.hpp>

#include "XMLBase64ImportContext.hxx"
namespace binfilter {

using namespace ::com::sun::star::uno;
using namespace ::com::sun::star::xml::sax;
using namespace ::com::sun::star::io;

using rtl::OUString;

//-----------------------------------------------------------------------------

TYPEINIT1( XMLBase64ImportContext, SvXMLImportContext );


XMLBase64ImportContext::XMLBase64ImportContext(
        SvXMLImport& rInImport, USHORT nPrfx, const OUString& rLName,
        const Reference< XAttributeList >& /*xAttrList*/,
        const Reference< XOutputStream >& rOut ) :
    SvXMLImportContext( rInImport, nPrfx, rLName ),
    xOut( rOut )
{
}

XMLBase64ImportContext::~XMLBase64ImportContext()
{
}


void XMLBase64ImportContext::EndElement()
{
    xOut->closeOutput();
}

void XMLBase64ImportContext::Characters( const ::rtl::OUString& rChars )
{
    OUString sTrimmedChars( rChars. trim() );
    if( sTrimmedChars.getLength() )
    {
        OUString sChars;
        if( sBase64CharsLeft.getLength() )
        {
            sChars = sBase64CharsLeft;
            sChars += sTrimmedChars;
            sBase64CharsLeft = OUString();
        }
        else
        {
            sChars = sTrimmedChars;
        }
        Sequence< sal_Int8 > aBuffer( (sChars.getLength() / 4) * 3 );
        sal_Int32 nCharsDecoded = 
            GetImport().GetMM100UnitConverter().
                decodeBase64SomeChars( aBuffer, sChars );
        xOut->writeBytes( aBuffer );	
        if( nCharsDecoded != sChars.getLength() )
            sBase64CharsLeft = sChars.copy( nCharsDecoded );
    }
}
    
}//end of namespace binfilter

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
