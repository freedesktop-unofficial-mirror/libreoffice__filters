/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: xmloff_NamedBoolPropertyHdl.cxx,v $
 *
 *  $Revision: 1.4 $
 *
 *  last change: $Author: hr $ $Date: 2006-06-19 10:12:28 $
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

#ifndef _XMLOFF_NAMEDBOOLPROPERTYHANDLER_HXX
#include <NamedBoolPropertyHdl.hxx>
#endif

// auto strip #ifndef _XMLOFF_XMLUCONV_HXX
// auto strip #include "xmluconv.hxx"
// auto strip #endif

#ifndef _COMPHELPER_EXTRACT_HXX_
#include <comphelper/extract.hxx>
#endif

#include "rtl/ustring.hxx"

// auto strip #ifndef _RTL_USTRBUF_HXX_
// auto strip #include <rtl/ustrbuf.hxx>
// auto strip #endif

// auto strip #ifndef _COM_SUN_STAR_UNO_ANY_HXX_
// auto strip #include <com/sun/star/uno/Any.hxx>
// auto strip #endif
namespace binfilter {

using namespace ::rtl;
using namespace ::com::sun::star::uno;

///////////////////////////////////////////////////////////////////////////////
//
// class XMLNamedBoolPropertyHdl
//

XMLNamedBoolPropertyHdl::~XMLNamedBoolPropertyHdl()
{
    // Nothing to do
}

sal_Bool XMLNamedBoolPropertyHdl::importXML( const OUString& rStrImpValue, Any& rValue, const SvXMLUnitConverter& rUnitConverter ) const
{
    if( rStrImpValue == maTrueStr )
    {
        rValue = ::cppu::bool2any( sal_True );
        return sal_True;
    }

    if( rStrImpValue == maFalseStr )
    {
        rValue = ::cppu::bool2any( sal_False );
        return sal_True;
    }

    return sal_False;
}

sal_Bool XMLNamedBoolPropertyHdl::exportXML( OUString& rStrExpValue, const Any& rValue, const SvXMLUnitConverter& rUnitConverter ) const
{
    if( ::cppu::any2bool( rValue ) )
    {
        rStrExpValue = maTrueStr;
    }
    else
    {
        rStrExpValue = maFalseStr;
    }

    return sal_True;
}

}//end of namespace binfilter
