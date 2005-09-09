/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: xmloff_XMLTextOrientationHdl.cxx,v $
 *
 *  $Revision: 1.3 $
 *
 *  last change: $Author: rt $ $Date: 2005-09-09 07:40:37 $
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
#include "XMLTextOrientationHdl.hxx"

#ifndef _XMLOFF_XMLUCONV_HXX
#include "xmluconv.hxx"
#endif
// auto strip #ifndef _XMLOFF_XMLTOKEN_HXX
// auto strip #include "xmltoken.hxx"
// auto strip #endif
namespace binfilter {

using namespace ::com::sun::star;
using namespace ::binfilter::xmloff::token;

XMLTextOrientationHdl::~XMLTextOrientationHdl()
{
}

sal_Bool XMLTextOrientationHdl::importXML(
    const ::rtl::OUString& rStrImpValue,
    ::com::sun::star::uno::Any& rValue,
    const SvXMLUnitConverter& rUnitConverter ) const
{
    sal_Bool bRetval( sal_False );

    if( IsXMLToken( rStrImpValue, XML_LTR ))
    {
        rValue <<= static_cast< sal_Bool >( sal_False );
        bRetval = sal_True;
    }
    else if( IsXMLToken( rStrImpValue, XML_TTB ))
    {
        rValue <<= static_cast< sal_Bool >( sal_True );
        bRetval = sal_True;
    }

    return bRetval;
}

sal_Bool XMLTextOrientationHdl::exportXML(
    ::rtl::OUString& rStrExpValue,
    const ::com::sun::star::uno::Any& rValue,
    const SvXMLUnitConverter& rUnitConverter ) const
{
    sal_Bool bVal;
    sal_Bool bRetval( sal_False );

    if( rValue >>= bVal )
    {
        if( bVal )
            rStrExpValue = GetXMLToken( XML_TTB );
        else
            rStrExpValue = GetXMLToken( XML_LTR );
        bRetval = sal_True;
    }

    return bRetval;
}
}//end of namespace binfilter
