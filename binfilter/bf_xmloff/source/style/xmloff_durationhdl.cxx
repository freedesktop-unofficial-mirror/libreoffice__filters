/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: xmloff_durationhdl.cxx,v $
 *
 *  $Revision: 1.3 $
 *
 *  last change: $Author: rt $ $Date: 2005-09-09 09:49:16 $
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

#ifndef _XMLOFF_PROPERTYHANDLER_DURATIONS_HXX
#include "durationhdl.hxx"
#endif

// auto strip #ifndef _COM_SUN_STAR_UNO_ANY_HXX_
// auto strip #include <com/sun/star/uno/Any.hxx>
// auto strip #endif

#ifndef _COM_SUN_STAR_UTIL_DATETIME_HPP_
#include <com/sun/star/util/DateTime.hpp>
#endif

#ifndef _RTL_USTRBUF_HXX_ 
#include <rtl/ustrbuf.hxx>
#endif

#ifndef _XMLOFF_XMLUCONV_HXX
#include "xmluconv.hxx"
#endif
namespace binfilter {

using namespace ::rtl;
using namespace ::com::sun::star::uno;
using namespace ::com::sun::star::util;

// ---------------------------------------------------------------------------


sal_Bool XMLDurationMS16PropHdl_Impl::importXML(
        const OUString& rStrImpValue,
           Any& rValue,
        const SvXMLUnitConverter& rUnitConverter ) const
{
    DateTime aTime;
    if( !SvXMLUnitConverter::convertTime( aTime,  rStrImpValue ) )
        return false;

    const sal_Int16 nMS = ( ( aTime.Hours * 60 + aTime.Minutes ) * 60 + aTime.Seconds ) * 100 + aTime.HundredthSeconds;
    rValue <<= nMS;

    return sal_True;
}

sal_Bool XMLDurationMS16PropHdl_Impl::exportXML(
        OUString& rStrExpValue,
        const Any& rValue,
        const SvXMLUnitConverter& rUnitConverter ) const
{
    sal_Int16 nMS;

    if(rValue >>= nMS)
    {
        OUStringBuffer aOut;
        DateTime aTime( nMS, 0, 0, 0, 0, 0, 0 );
        SvXMLUnitConverter::convertTime( aOut, aTime );
        rStrExpValue = aOut.makeStringAndClear();
        return sal_True;
    }

    return sal_False;
}

XMLDurationMS16PropHdl_Impl::~XMLDurationMS16PropHdl_Impl()
{
}
}//end of namespace binfilter
