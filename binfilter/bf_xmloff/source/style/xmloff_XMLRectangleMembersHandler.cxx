/*************************************************************************
 *
 *  $RCSfile: xmloff_XMLRectangleMembersHandler.cxx,v $
 *
 *  $Revision: 1.2 $
 *
 *  last change: $Author: hr $ $Date: 2004-08-03 20:12:10 $
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

#ifndef _XMLOFF_XMLUCONV_HXX
#include "xmluconv.hxx"
#endif

#ifndef _RTL_USTRBUF_HXX_
#include <rtl/ustrbuf.hxx>
#endif

// auto strip #ifndef _COM_SUN_STAR_UNO_ANY_HXX_
// auto strip #include <com/sun/star/uno/Any.hxx>
// auto strip #endif

#ifndef _COM_SUN_STAR_AWT_RECTANGLE_HDL_ 
#include <com/sun/star/awt/Rectangle.hdl>
#endif

#ifndef _XMLOFF_XMLRECTANGLEMEMBERSHANDLER_HXX
#include "XMLRectangleMembersHandler.hxx"
#endif

#ifndef _XMLOFF_XMLTYPES_HXX
#include "xmltypes.hxx"
#endif
namespace binfilter {

using namespace ::com::sun::star;
using namespace ::com::sun::star::uno;
using namespace ::rtl;

XMLRectangleMembersHdl::XMLRectangleMembersHdl( sal_Int32 nType )
: mnType( nType )
{
}

    sal_Int32 X;
    sal_Int32 Y;
    sal_Int32 Width;
    sal_Int32 Height;

XMLRectangleMembersHdl::~XMLRectangleMembersHdl()
{
}

sal_Bool XMLRectangleMembersHdl::importXML(
    const OUString& rStrImpValue,
    Any& rValue,
    const SvXMLUnitConverter& rUnitConverter ) const
{
    awt::Rectangle aRect( 0, 0, 0, 0 );
    if( rValue.hasValue() )
        rValue >>= aRect;

    sal_Int32 nValue;

    if( rUnitConverter.convertMeasure( nValue, rStrImpValue ) )
    {
        switch( mnType )
        {
            case XML_TYPE_RECTANGLE_LEFT :
                aRect.X = nValue;
                break;
            case XML_TYPE_RECTANGLE_TOP :
                aRect.Y = nValue;
                break;
            case XML_TYPE_RECTANGLE_WIDTH :
                aRect.Width = nValue;
                break;
            case XML_TYPE_RECTANGLE_HEIGHT :
                aRect.Height = nValue;
                break;
        }

        rValue <<= aRect;
        return sal_True;
    }

    return sal_False;
}

sal_Bool XMLRectangleMembersHdl::exportXML(
    OUString& rStrExpValue,
    const Any& rValue,
    const SvXMLUnitConverter& rUnitConverter ) const
{
    awt::Rectangle aRect( 0, 0, 0, 0 );
    rValue >>= aRect;

    sal_Int32 nValue;

    switch( mnType )
    {
        case XML_TYPE_RECTANGLE_LEFT :
            nValue = aRect.X;
            break;
        case XML_TYPE_RECTANGLE_TOP :
            nValue = aRect.Y;
            break;
        case XML_TYPE_RECTANGLE_WIDTH :
            nValue = aRect.Width;
            break;
        case XML_TYPE_RECTANGLE_HEIGHT :
            nValue = aRect.Height;
            break;
    }

    ::rtl::OUStringBuffer sBuffer;
    rUnitConverter.convertMeasure( sBuffer, nValue );
    rStrExpValue = sBuffer.makeStringAndClear();
    return sal_True;
}

}//end of namespace binfilter
