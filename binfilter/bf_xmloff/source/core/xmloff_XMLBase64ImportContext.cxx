/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: xmloff_XMLBase64ImportContext.cxx,v $
 *
 *  $Revision: 1.2 $
 *
 *  last change: $Author: rt $ $Date: 2005-09-09 07:43:38 $
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

#ifndef _XMLOFF_XMLIMP_HXX
#include "xmlimp.hxx"
#endif
#ifndef _XMLOFF_XMLUCONV_HXX 
#include "xmluconv.hxx"
#endif

#ifndef _COM_SUN_STAR_IO_XOUTPUTSTREAM_HPP_ 
#include <com/sun/star/io/XOutputStream.hpp>
#endif

#ifndef _XMLOFF_XMLBASE64IMPORTCONTEXT_HXX
#include "XMLBase64ImportContext.hxx"
#endif
namespace binfilter {

using namespace ::rtl;
using namespace ::com::sun::star::uno;
using namespace ::com::sun::star::xml::sax;
using namespace ::com::sun::star::io;

//-----------------------------------------------------------------------------

TYPEINIT1( XMLBase64ImportContext, SvXMLImportContext );


XMLBase64ImportContext::XMLBase64ImportContext(
        SvXMLImport& rImport, USHORT nPrfx, const OUString& rLName,
        const Reference< XAttributeList >& xAttrList,
        const Reference< XOutputStream >& rOut ) :
    SvXMLImportContext( rImport, nPrfx, rLName ),
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
        if( sBase64CharsLeft )
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
