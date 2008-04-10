/*************************************************************************
 *
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER.
 * 
 * Copyright 2008 by Sun Microsystems, Inc.
 *
 * OpenOffice.org - a multi-platform office productivity suite
 *
 * $RCSfile: formenums.hxx,v $
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

#ifndef _XMLOFF_FORMENUMS_HXX_
#define _XMLOFF_FORMENUMS_HXX_

#ifndef _XMLOFF_XMLEMENT_HXX
#include "xmlement.hxx"
#endif
namespace binfilter {

//.........................................................................
namespace xmloff
{
//.........................................................................

    //=====================================================================
    //= OEnumMapper
    //=====================================================================
    class OEnumMapper
    {
    public:
        enum EnumProperties
        {
            epSubmitEncoding = 0,
            epSubmitMethod,
            epCommandType,
            epNavigationType,
            epTabCyle,
            epButtonType,
            epListSourceType,
            epCheckState,
            epTextAlign,
            epBorderWidth,
            epFontEmphasis,
            epFontRelief,
            epListLinkageType,

            KNOWN_ENUM_PROPERTIES
        };

    private:
        static const SvXMLEnumMapEntry*	s_pEnumMap[KNOWN_ENUM_PROPERTIES];

    public:
        static const SvXMLEnumMapEntry*	getEnumMap(EnumProperties _eProperty);
    };

//.........................................................................
}	// namespace xmloff
//.........................................................................

}//end of namespace binfilter
#endif // _XMLOFF_FORMENUMS_HXX_

