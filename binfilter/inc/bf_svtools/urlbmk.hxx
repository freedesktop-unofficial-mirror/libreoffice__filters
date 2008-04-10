/*************************************************************************
 *
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER.
 * 
 * Copyright 2008 by Sun Microsystems, Inc.
 *
 * OpenOffice.org - a multi-platform office productivity suite
 *
 * $RCSfile: urlbmk.hxx,v $
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

#ifndef _URLBMK_HXX
#define _URLBMK_HXX


#ifndef _STRING_HXX //autogen
#include <tools/string.hxx>
#endif

namespace binfilter
{

//=========================================================================

class INetBookmark

/*	[Beschreibung]

    Diese Klasse stellt ein Bookmark dar, welches aus einer URL und
    einem dazuge"horigen Beschreibungstext besteht.

    Es gibt ein eigenes Clipboardformat und Hilfsmethoden zum Kopieren
    und Einf"ugen in und aus Clipboard und DragServer.
*/

{
    String			aUrl;
    String			aDescr;

protected:

    void 			SetURL( const String& rS )			{ aUrl = rS; }
    void 			SetDescription( const String& rS )	{ aDescr = rS; }

public:
                    INetBookmark( const String &rUrl, const String &rDescr )
                        : aUrl( rUrl ), aDescr( rDescr )
                    {}
                    INetBookmark()
                    {}

    const String&	GetURL() const 			{ return aUrl; }
    const String&	GetDescription() const	{ return aDescr; }
};

}

#endif

