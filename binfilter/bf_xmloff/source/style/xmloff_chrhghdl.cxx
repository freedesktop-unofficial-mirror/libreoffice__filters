/*************************************************************************
 *
 *  $RCSfile: xmloff_chrhghdl.cxx,v $
 *
 *  $Revision: 1.2 $
 *
 *  last change: $Author: hr $ $Date: 2004-08-03 20:13:28 $
 *
 *  The Contents of this file are made available subject to the terms of
 *  either of the following licenses
 *
 *         - GNU Lesser General Public License Version 2.1
 *         - Sun Industry Standards Source License Version 1.1
 *
 *  Sun Microsystems Inc., October, 2000
 *
 *  GNU Lesser General Public License Version 2.1
 *  =============================================
 *  Copyright 2000 by Sun Microsystems, Inc.
 *  901 San Antonio Road, Palo Alto, CA 94303, USA
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public
 *  License version 2.1, as published by the Free Software Foundation.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public
 *  License along with this library; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 *  MA  02111-1307  USA
 *
 *
 *  Sun Industry Standards Source License Version 1.1
 *  =================================================
 *  The contents of this file are subject to the Sun Industry Standards
 *  Source License Version 1.1 (the "License"); You may not use this file
 *  except in compliance with the License. You may obtain a copy of the
 *  License at http://www.openoffice.org/license.html.
 *
 *  Software provided under this License is provided on an "AS IS" basis,
 *  WITHOUT WARRANTY OF ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING,
 *  WITHOUT LIMITATION, WARRANTIES THAT THE SOFTWARE IS FREE OF DEFECTS,
 *  MERCHANTABLE, FIT FOR A PARTICULAR PURPOSE, OR NON-INFRINGING.
 *  See the License for the specific provisions governing your rights and
 *  obligations concerning the Software.
 *
 *  The Initial Developer of the Original Code is: Sun Microsystems, Inc.
 *
 *  Copyright: 2000 by Sun Microsystems, Inc.
 *
 *  All Rights Reserved.
 *
 *  Contributor(s): _______________________________________
 *
 *
 ************************************************************************/


#ifndef _XMLOFF_PROPERTYHANDLER_CHARHEIGHTTYPES_HXX
#include <chrhghdl.hxx>
#endif

#ifndef _XMLOFF_XMLUCONV_HXX 
#include "xmluconv.hxx"
#endif

#ifndef _XMLOFF_XMLEHELP_HXX
#include "xmlehelp.hxx"
#endif

#ifndef _RTL_USTRBUF_HXX_ 
#include <rtl/ustrbuf.hxx>
#endif

// auto strip #ifndef _COM_SUN_STAR_UNO_ANY_HXX_
// auto strip #include <com/sun/star/uno/Any.hxx>
// auto strip #endif

// auto strip #ifndef _XMLOFF_XMLEMENT_HXX
// auto strip #include "xmlelement.hxx"
// auto strip #endif
namespace binfilter {

using namespace ::rtl;
using namespace ::com::sun::star;

// this is a copy of defines in svx/inc/escpitem.hxx
#define DFLT_ESC_PROP	 58
#define DFLT_ESC_AUTO_SUPER	101
#define DFLT_ESC_AUTO_SUB  -101

///////////////////////////////////////////////////////////////////////////////
//
// class XMLEscapementPropHdl
//

XMLCharHeightHdl::~XMLCharHeightHdl()
{
    // nothing to do
}

sal_Bool XMLCharHeightHdl::importXML( const OUString& rStrImpValue, uno::Any& rValue, const SvXMLUnitConverter& rUnitConverter ) const
{ 
    double fSize;

    if( rStrImpValue.indexOf( sal_Unicode('%') ) == -1 )
    {
        MapUnit eSrcUnit = SvXMLExportHelper::GetUnitFromString( rStrImpValue, MAP_POINT );
        if( SvXMLUnitConverter::convertDouble( fSize, rStrImpValue, eSrcUnit, MAP_POINT ))
        {
            rValue <<= (float)fSize;
            return sal_True; 
        }
    }

    return sal_False;
}

sal_Bool XMLCharHeightHdl::exportXML( OUString& rStrExpValue, const uno::Any& rValue, const SvXMLUnitConverter& rUnitConverter ) const
{ 
    OUStringBuffer aOut;

    float fSize = 0;
    if( rValue >>= fSize )
    {
        SvXMLUnitConverter::convertDouble( aOut, (double)fSize, TRUE, MAP_POINT, MAP_POINT );
        aOut.append( sal_Unicode('p'));
        aOut.append( sal_Unicode('t'));
    }
    
    rStrExpValue = aOut.makeStringAndClear();
    return rStrExpValue.getLength() != 0;
}

///////////////////////////////////////////////////////////////////////////////
//
// class XMLEscapementHeightPropHdl
//

XMLCharHeightPropHdl::~XMLCharHeightPropHdl()
{
    // nothing to do
}

sal_Bool XMLCharHeightPropHdl::importXML( const OUString& rStrImpValue, uno::Any& rValue, const SvXMLUnitConverter& rUnitConverter ) const
{ 
    sal_Int32 nPrc = 100;

    if( rStrImpValue.indexOf( sal_Unicode('%') ) != -1 )
    {
        if( rUnitConverter.convertPercent( nPrc, rStrImpValue ) )
        {
            rValue <<= (sal_Int16)nPrc;
            return sal_True; 
        }
    }

    return sal_False;
}

sal_Bool XMLCharHeightPropHdl::exportXML( OUString& rStrExpValue, const uno::Any& rValue, const SvXMLUnitConverter& rUnitConverter ) const
{ 
    OUStringBuffer aOut( rStrExpValue );

    sal_Int16 nValue;
    if( rValue >>= nValue )
    {
        rUnitConverter.convertPercent( aOut, nValue );
    }

    rStrExpValue = aOut.makeStringAndClear();
    return rStrExpValue.getLength() != 0;
}

///////////////////////////////////////////////////////////////////////////////
//
// class XMLEscapementPropHdl
//

XMLCharHeightDiffHdl::~XMLCharHeightDiffHdl()
{
    // nothing to do
}

sal_Bool XMLCharHeightDiffHdl::importXML( const OUString& rStrImpValue, uno::Any& rValue, const SvXMLUnitConverter& rUnitConverter ) const
{ 
    sal_Int32 nRel = 0;

    if( SvXMLUnitConverter::convertMeasure( nRel, rStrImpValue, MAP_POINT ) )
    {
        rValue <<= (float)nRel;
        return sal_True; 
    }

    return sal_False;
}

sal_Bool XMLCharHeightDiffHdl::exportXML( OUString& rStrExpValue, const uno::Any& rValue, const SvXMLUnitConverter& rUnitConverter ) const
{ 
    OUStringBuffer aOut;

    float nRel = 0;
    if( (rValue >>= nRel) && (nRel != 0) )
    {
        SvXMLUnitConverter::convertMeasure( aOut, nRel, MAP_POINT, MAP_POINT );
        rStrExpValue = aOut.makeStringAndClear();
    }
    
    return rStrExpValue.getLength() != 0;
}

}//end of namespace binfilter
