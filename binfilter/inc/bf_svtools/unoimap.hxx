/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: unoimap.hxx,v $
 *
 *  $Revision: 1.2 $
 *
 *  last change: $Author: rt $ $Date: 2008-03-12 12:37:26 $
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

#ifndef _SVTOOLS_UNOIMAP_HXX
#define _SVTOOLS_UNOIMAP_HXX

#ifndef INCLUDED_SVTDLLAPI_H
#include "bf_svtools/svtdllapi.h"
#endif

#ifndef _COM_SUN_STAR_UNO_XINTERFACE_HPP_ 
#include <com/sun/star/uno/XInterface.hpp>
#endif

namespace binfilter
{

class ImageMap;
struct SvEventDescription;

 com::sun::star::uno::Reference< com::sun::star::uno::XInterface > SvUnoImageMapRectangleObject_createInstance( const SvEventDescription* pSupportedMacroItems );
 com::sun::star::uno::Reference< com::sun::star::uno::XInterface > SvUnoImageMapCircleObject_createInstance( const SvEventDescription* pSupportedMacroItems );
 com::sun::star::uno::Reference< com::sun::star::uno::XInterface > SvUnoImageMapPolygonObject_createInstance( const SvEventDescription* pSupportedMacroItems );

 com::sun::star::uno::Reference< com::sun::star::uno::XInterface > SvUnoImageMap_createInstance( const SvEventDescription* pSupportedMacroItems );
 com::sun::star::uno::Reference< com::sun::star::uno::XInterface > SvUnoImageMap_createInstance( const ImageMap& rMap, const SvEventDescription* pSupportedMacroItems );
 sal_Bool SvUnoImageMap_fillImageMap( com::sun::star::uno::Reference< com::sun::star::uno::XInterface > xImageMap, ImageMap& rMap );

}

#endif
