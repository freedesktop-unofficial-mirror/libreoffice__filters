/*************************************************************************
 *
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER.
 * 
 * Copyright 2008 by Sun Microsystems, Inc.
 *
 * OpenOffice.org - a multi-platform office productivity suite
 *
 * $RCSfile: fstathelper.hxx,v $
 * $Revision: 1.3 $
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

#ifndef _SVTOOLS_FSTATHELPER_HXX
#define _SVTOOLS_FSTATHELPER_HXX

#ifndef _SOLAR_H
#include <tools/solar.h>
#endif

class UniString;
class Date;
class Time;

namespace binfilter
{

/** Return the modified time and date stamp for this URL.

    @param URL	the asking URL

    @param pDate if unequal 0, the function set the date stamp

    @param pTime if unequal 0, the function set the time stamp

    @return 	it was be able to get the date/time stamp
*/
 sal_Bool GetModifiedDateTimeOfFile( const UniString& rURL,
                                    Date* pDate, Time* pTime );

/** Return if under the URL a document exist. This is only a wrapper for the
    UCB.IsContent.
*/
 sal_Bool IsDocument( const UniString& rURL );

/** Return if under the URL a folder exist. This is only a wrapper for the
    UCB.isFolder.
*/
 sal_Bool IsFolder( const UniString& rURL );

}

#endif
