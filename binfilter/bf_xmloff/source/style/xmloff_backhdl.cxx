/*************************************************************************
 *
 *  $RCSfile: xmloff_backhdl.cxx,v $
 *
 *  $Revision: 1.2 $
 *
 *  last change: $Author: hr $ $Date: 2004-08-03 20:12:31 $
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

#ifndef _TOOLS_DEBUG_HXX 
#include <tools/debug.hxx>
#endif

#ifndef _XMLOFF_PROPERTYHANDLER_BRUSHTYPES_HXX
#include <backhdl.hxx>
#endif

// auto strip #ifndef _XMLOFF_XMLTOKEN_HXX
// auto strip #include "xmltoken.hxx"
// auto strip #endif

#ifndef _XMLOFF_XMLUCONV_HXX 
#include "xmluconv.hxx"
#endif

// auto strip #ifndef _COM_SUN_STAR_UNO_ANY_HXX_
// auto strip #include <com/sun/star/uno/Any.hxx>
// auto strip #endif

#ifndef _RTL_USTRBUF_HXX_ 
#include <rtl/ustrbuf.hxx>
#endif

// auto strip #ifndef _XMLOFF_XMLEMENT_HXX
// auto strip #include "xmlelement.hxx"
// auto strip #endif
namespace binfilter {

using namespace ::rtl;
using namespace ::com::sun::star;
using namespace ::binfilter::xmloff::token;

SvXMLEnumMapEntry pXML_BrushHorizontalPos[] =
{
    { XML_LEFT,		        style::GraphicLocation_LEFT_MIDDLE	 },
    { XML_RIGHT,		    style::GraphicLocation_RIGHT_MIDDLE },
    { XML_TOKEN_INVALID,    0		}
};

SvXMLEnumMapEntry pXML_BrushVerticalPos[] =
{
    { XML_TOP,			    style::GraphicLocation_MIDDLE_TOP	},
    { XML_BOTTOM,		    style::GraphicLocation_MIDDLE_BOTTOM	},
    { XML_TOKEN_INVALID,    0		}
};

///////////////////////////////////////////////////////////////////////////////
//
// class XMLBackGraphicPositionPropHdl
//

XMLBackGraphicPositionPropHdl::~XMLBackGraphicPositionPropHdl()
{
    // Nothing to do
}

sal_Bool XMLBackGraphicPositionPropHdl::importXML( const OUString& rStrImpValue, uno::Any& rValue, const SvXMLUnitConverter& rUnitConverter )
{ 
    sal_Bool bRet = sal_True;
    style::GraphicLocation ePos = style::GraphicLocation_NONE, eTmp;
    sal_uInt16 nTmp;
    SvXMLTokenEnumerator aTokenEnum( rStrImpValue );
    OUString aToken;
    sal_Bool bHori = sal_False, bVert = sal_False;

    while( bRet && aTokenEnum.getNextToken( aToken ) )
    {
        if( bHori && bVert )
        {
            bRet = sal_False;
        }
        else if( -1 != aToken.indexOf( sal_Unicode('%') ) )
        {
            long nPrc = 50;
            if( rUnitConverter.convertPercent( nPrc, aToken ) )
            {
                if( !bHori )
                {
                    ePos = nPrc < 25 ? style::GraphicLocation_LEFT_TOP : 
                                       (nPrc < 75 ? style::GraphicLocation_MIDDLE_MIDDLE : 
                                                    style::GraphicLocation_RIGHT_BOTTOM);
                    bHori = sal_True;
                }
                else
                {
                    eTmp = nPrc < 25 ? style::GraphicLocation_LEFT_TOP: 
                                       (nPrc < 75 ? style::GraphicLocation_LEFT_MIDDLE : 
                                                    style::GraphicLocation_LEFT_BOTTOM);
                    MergeXMLVertPos( ePos, eTmp );
                    bVert = sal_True;
                }
            }
            else
            {
                // wrong percentage
                bRet = sal_False;
            }
        }
        else if( IsXMLToken( aToken, XML_CENTER ) )
        {
            if( bHori )
                MergeXMLVertPos( ePos, style::GraphicLocation_MIDDLE_MIDDLE );
            else if ( bVert )
                MergeXMLHoriPos( ePos, style::GraphicLocation_MIDDLE_MIDDLE );
            else
                ePos = style::GraphicLocation_MIDDLE_MIDDLE;
        }
        else if( rUnitConverter.convertEnum( nTmp, aToken, pXML_BrushHorizontalPos ) )
        {
            if( bVert )
                MergeXMLHoriPos( ePos, (style::GraphicLocation)nTmp );
            else if( !bHori )
                ePos = (style::GraphicLocation)nTmp;
            else
                bRet = sal_False;

            bHori = sal_True;
        }
        else if( rUnitConverter.convertEnum( nTmp, aToken, pXML_BrushVerticalPos ) )
        {
            if( bHori )
                MergeXMLVertPos( ePos, (style::GraphicLocation)nTmp );
            else if( !bVert )
                ePos = (style::GraphicLocation)nTmp;
            else
                bRet = sal_False;
            bVert = sal_True;
        }
        else
        {
            bRet = sal_False;
        }
    }

    bRet &= style::GraphicLocation_NONE != ePos;
    if( bRet )
        rValue <<= (style::GraphicLocation)(sal_uInt16)ePos;

    return bRet; 
}

sal_Bool XMLBackGraphicPositionPropHdl::exportXML( OUString& rStrExpValue, const uno::Any& rValue, const SvXMLUnitConverter& rUnitConverter ) const
{ 
    sal_Bool bRet = sal_True;
    OUStringBuffer aOut;

    style::GraphicLocation eLocation;
    if( !( rValue >>= eLocation ) )
    {
        sal_Int32 nValue;
        if( rValue >>= nValue )
            eLocation = (style::GraphicLocation)nValue;
        else
            bRet = sal_False;
    }

    if( bRet )
    {
        bRet = sal_False;

        switch( eLocation )
        {
        case style::GraphicLocation_LEFT_TOP:
        case style::GraphicLocation_MIDDLE_TOP:
        case style::GraphicLocation_RIGHT_TOP:
            aOut.append( GetXMLToken(XML_TOP) );
            bRet = sal_True;
            break;
        case style::GraphicLocation_LEFT_MIDDLE:
        case style::GraphicLocation_MIDDLE_MIDDLE:
        case style::GraphicLocation_RIGHT_MIDDLE:
            aOut.append( GetXMLToken(XML_CENTER) );
            bRet = sal_True;
            break;
        case style::GraphicLocation_LEFT_BOTTOM:
        case style::GraphicLocation_MIDDLE_BOTTOM:
        case style::GraphicLocation_RIGHT_BOTTOM:
            aOut.append( GetXMLToken(XML_BOTTOM) );
            bRet = sal_True;
            break;
        }

        if( bRet )
        {
            aOut.append( sal_Unicode( ' ' ) );

            switch( eLocation )
            {
            case style::GraphicLocation_LEFT_TOP:
            case style::GraphicLocation_LEFT_BOTTOM:
            case style::GraphicLocation_LEFT_MIDDLE:
                aOut.append( GetXMLToken(XML_LEFT) );
                break;
            case style::GraphicLocation_MIDDLE_TOP:
            case style::GraphicLocation_MIDDLE_MIDDLE:
            case style::GraphicLocation_MIDDLE_BOTTOM:
                aOut.append( GetXMLToken(XML_CENTER) );
                break;
            case style::GraphicLocation_RIGHT_MIDDLE:
            case style::GraphicLocation_RIGHT_TOP:
            case style::GraphicLocation_RIGHT_BOTTOM:
                aOut.append( GetXMLToken(XML_RIGHT) );
                break;
            }
        }
    }

    rStrExpValue = aOut.makeStringAndClear();

    return bRet;
}

void XMLBackGraphicPositionPropHdl::MergeXMLVertPos( style::GraphicLocation& ePos, style::GraphicLocation eVert )
{
    switch( ePos )
    {
    case style::GraphicLocation_LEFT_TOP:
    case style::GraphicLocation_LEFT_MIDDLE:
    case style::GraphicLocation_LEFT_BOTTOM:
        ePos = style::GraphicLocation_MIDDLE_TOP==eVert ? 
               style::GraphicLocation_LEFT_TOP : 
              (style::GraphicLocation_MIDDLE_MIDDLE==eVert ? 
               style::GraphicLocation_LEFT_MIDDLE : 
               style::GraphicLocation_LEFT_BOTTOM);
        ePos = eVert;
        break;

    case style::GraphicLocation_MIDDLE_TOP:
    case style::GraphicLocation_MIDDLE_MIDDLE:
    case style::GraphicLocation_MIDDLE_BOTTOM:
        ePos = eVert;
        break;

    case style::GraphicLocation_RIGHT_TOP:
    case style::GraphicLocation_RIGHT_MIDDLE:
    case style::GraphicLocation_RIGHT_BOTTOM:
        ePos = style::GraphicLocation_MIDDLE_TOP==eVert ? 
               style::GraphicLocation_RIGHT_TOP : 
              (style::GraphicLocation_MIDDLE_MIDDLE==eVert ? 
               style::GraphicLocation_RIGHT_MIDDLE : 
               style::GraphicLocation_RIGHT_BOTTOM);
        break;
    }
}

void XMLBackGraphicPositionPropHdl::MergeXMLHoriPos( style::GraphicLocation& ePos, style::GraphicLocation eHori )
{
    DBG_ASSERT( style::GraphicLocation_LEFT_MIDDLE==eHori || style::GraphicLocation_MIDDLE_MIDDLE==eHori || style::GraphicLocation_RIGHT_MIDDLE==eHori,
                "lcl_frmitems_MergeXMLHoriPos: vertical pos must be middle" );

    switch( ePos )
    {
    case style::GraphicLocation_LEFT_TOP:
    case style::GraphicLocation_MIDDLE_TOP:
    case style::GraphicLocation_RIGHT_TOP:
        ePos = style::GraphicLocation_LEFT_MIDDLE==eHori ? 
               style::GraphicLocation_LEFT_TOP : 
              (style::GraphicLocation_MIDDLE_MIDDLE==eHori ? 
               style::GraphicLocation_MIDDLE_TOP : 
               style::GraphicLocation_RIGHT_TOP);
        break;

    case style::GraphicLocation_LEFT_MIDDLE:
    case style::GraphicLocation_MIDDLE_MIDDLE:
    case style::GraphicLocation_RIGHT_MIDDLE:
        ePos = eHori;
        break;

    case style::GraphicLocation_LEFT_BOTTOM:
    case style::GraphicLocation_MIDDLE_BOTTOM:
    case style::GraphicLocation_RIGHT_BOTTOM:
        ePos = style::GraphicLocation_LEFT_MIDDLE==eHori ? 
               style::GraphicLocation_LEFT_BOTTOM : 
              (style::GraphicLocation_MIDDLE_MIDDLE==eHori ? 
               style::GraphicLocation_MIDDLE_BOTTOM : 
               style::GraphicLocation_RIGHT_BOTTOM);
        break;
    }
}

}//end of namespace binfilter
