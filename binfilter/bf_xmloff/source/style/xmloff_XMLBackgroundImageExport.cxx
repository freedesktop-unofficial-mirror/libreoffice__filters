/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: xmloff_XMLBackgroundImageExport.cxx,v $
 *
 *  $Revision: 1.3 $
 *
 *  last change: $Author: rt $ $Date: 2005-09-09 09:42:35 $
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

#ifndef _COM_SUN_STAR_STYLE_GRAPHICLOCATION_HPP_ 
#include <com/sun/star/style/GraphicLocation.hpp>
#endif

#include <xmlnmspe.hxx>

// auto strip #ifndef _XMLOFF_XMLTOKEN_HXX
// auto strip #include <xmltoken.hxx>
// auto strip #endif

// auto strip #ifndef _RTL_USTRBUF_HXX_ 
// auto strip #include <rtl/ustrbuf.hxx>
// auto strip #endif
#ifndef _XMLOFF_XMLEXP_HXX 
#include "xmlexp.hxx"
#endif
#ifndef _XMLBACKGROUNDIMAGEEXPORT_HXX
#include "XMLBackgroundImageExport.hxx"
#endif
#ifndef _XMLOFF_XMLUCONV_HXX
#include "xmluconv.hxx"
#endif
namespace binfilter {

using namespace ::rtl;
using namespace ::com::sun::star;
using namespace ::com::sun::star::uno;
using namespace ::com::sun::star::style;
using namespace ::binfilter::xmloff::token;

XMLBackgroundImageExport::XMLBackgroundImageExport( SvXMLExport& rExp ) :
    rExport( rExp )
{
}

XMLBackgroundImageExport::~XMLBackgroundImageExport()
{
}

void XMLBackgroundImageExport::exportXML( const Any& rURL,
            const Any *pPos,
            const Any *pFilter,
            const Any *pTransparency,
            sal_uInt16 nPrefix,
            const ::rtl::OUString& rLocalName )
{
    GraphicLocation ePos;
    if( !(pPos && ((*pPos) >>= ePos)) )
        ePos = GraphicLocation_AREA;

    OUString sURL;
    rURL >>= sURL;
    if( sURL.getLength() && GraphicLocation_NONE != ePos )
    {
        OUString sTempURL( GetExport().AddEmbeddedGraphicObject( sURL ) );
        if( sTempURL.getLength() )
        {
            GetExport().AddAttribute( XML_NAMESPACE_XLINK, XML_HREF, sTempURL );
            GetExport().AddAttribute( XML_NAMESPACE_XLINK, XML_TYPE, 
                                      XML_SIMPLE );
            GetExport().AddAttribute( XML_NAMESPACE_XLINK, XML_ACTUATE,
                                      XML_ONLOAD );
        }
        
        OUStringBuffer aOut;
        switch( ePos )
        {
        case GraphicLocation_LEFT_TOP:
        case GraphicLocation_MIDDLE_TOP:
        case GraphicLocation_RIGHT_TOP:
            aOut.append( GetXMLToken(XML_TOP) );
            break;
        case GraphicLocation_LEFT_MIDDLE:
        case GraphicLocation_MIDDLE_MIDDLE:
        case GraphicLocation_RIGHT_MIDDLE:
            aOut.append( GetXMLToken(XML_CENTER) );
            break;
        case GraphicLocation_LEFT_BOTTOM:
        case GraphicLocation_MIDDLE_BOTTOM:
        case GraphicLocation_RIGHT_BOTTOM:
            aOut.append( GetXMLToken(XML_BOTTOM) );
            break;
        }

        if( aOut.getLength() )
        {
            aOut.append( sal_Unicode( ' ' ) );

            switch( ePos )
            {
            case GraphicLocation_LEFT_TOP:
            case GraphicLocation_LEFT_BOTTOM:
            case GraphicLocation_LEFT_MIDDLE:
                aOut.append( GetXMLToken(XML_LEFT) );
                break;
            case GraphicLocation_MIDDLE_TOP:
            case GraphicLocation_MIDDLE_MIDDLE:
            case GraphicLocation_MIDDLE_BOTTOM:
                aOut.append( GetXMLToken(XML_CENTER) );
                break;
            case GraphicLocation_RIGHT_MIDDLE:
            case GraphicLocation_RIGHT_TOP:
            case GraphicLocation_RIGHT_BOTTOM:
                aOut.append( GetXMLToken(XML_RIGHT) );
                break;
            }
        }
        if( aOut.getLength() )
            GetExport().AddAttribute( XML_NAMESPACE_STYLE,
                                  XML_POSITION, aOut.makeStringAndClear() );

        if( GraphicLocation_AREA == ePos )
        {
            aOut.append( GetXMLToken(XML_BACKGROUND_STRETCH) );
        }
        else if( GraphicLocation_NONE != ePos && GraphicLocation_TILED != ePos  )
        {
            aOut.append( GetXMLToken(XML_BACKGROUND_NO_REPEAT) );
        }
        if( aOut.getLength() )
            GetExport().AddAttribute( XML_NAMESPACE_STYLE, XML_REPEAT,
                          aOut.makeStringAndClear() );

        if( pFilter )
        {
            OUString sFilter;
            (*pFilter) >>= sFilter;
            if( sFilter.getLength() )
                GetExport().AddAttribute( XML_NAMESPACE_STYLE, XML_FILTER_NAME,
                                          sFilter );
        }

        if( pTransparency )
        {
            sal_Int8 nTransparency;
            if( (*pTransparency) >>= nTransparency )
            {
                OUStringBuffer aOut;
                SvXMLUnitConverter::convertPercent( aOut, nTransparency );
                GetExport().AddAttribute( XML_NAMESPACE_DRAW, XML_TRANSPARENCY,
                                          aOut.makeStringAndClear() );
            }
        }
    }

    {
        SvXMLElementExport aElem( GetExport(), nPrefix, rLocalName, sal_True, sal_True );
        if( sURL.getLength() && GraphicLocation_NONE != ePos )
        {
            // optional office:binary-data
            GetExport().AddEmbeddedGraphicObjectAsBase64( sURL );
        }
    }
}
}//end of namespace binfilter
