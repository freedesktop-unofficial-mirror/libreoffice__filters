/*************************************************************************
 *
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER.
 * 
 * Copyright 2008 by Sun Microsystems, Inc.
 *
 * OpenOffice.org - a multi-platform office productivity suite
 *
 * $RCSfile: unopolyhelper.hxx,v $
 * $Revision: 1.4 $
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

#ifndef _SVX_UNOPOLYHELPER_HXX
#define _SVX_UNOPOLYHELPER_HXX

#ifndef _COM_SUN_STAR_LANG_ILLEGALARGUMENTEXCEPTION_HPP_ 
#include <com/sun/star/lang/IllegalArgumentException.hpp>
#endif
namespace binfilter {

namespace com { namespace sun { namespace star { namespace drawing {
    struct PolyPolygonBezierCoords;
} } } }

class XPolygon;

/** convert a drawing::PolyPolygonBezierCoords to a XPolygon
*/
void SvxConvertPolyPolygonBezierToXPolygon( const ::com::sun::star::drawing::PolyPolygonBezierCoords* pSourcePolyPolygon, XPolygon& rNewPolygon )
    throw( ::com::sun::star::lang::IllegalArgumentException );

/** convert a XPolygon to a drawing::PolyPolygonBezierCoords
*/
void SvxConvertXPolygonToPolyPolygonBezier( const XPolygon& rPolygon, ::com::sun::star::drawing::PolyPolygonBezierCoords& rRetval )
    throw();

}//end of namespace binfilter
#endif


