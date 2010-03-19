/*************************************************************************
 *
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER.
 *
 * Copyright 2000, 2010 Oracle and/or its affiliates.
 *
 * OpenOffice.org - a multi-platform office productivity suite
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
#ifndef _SFXGENLINK_HXX
#define _SFXGENLINK_HXX

#ifndef _LINK_HXX //autogen
#include <tools/link.hxx>
#endif
namespace binfilter {
typedef long (*CFuncPtr)(void*);

class GenLink
{
    Link        aLink;
    CFuncPtr    pFunc;

public:
    GenLink(): pFunc(0) {}
    GenLink( CFuncPtr pCFunc ): pFunc(pCFunc) {}
    GenLink( const Link& rLink ): aLink(rLink), pFunc(0) {}
    GenLink( const GenLink& rOrig ):
        pFunc(rOrig.pFunc), aLink(rOrig.aLink) {}

    GenLink& operator = ( const GenLink& rOrig )
        { pFunc = rOrig.pFunc; aLink = rOrig.aLink; return *this; }

    BOOL operator!() const { return !aLink && !pFunc; }
    BOOL IsSet() const { return aLink.IsSet() || pFunc; }

    long Call( void* pCaller )
         { return pFunc ? (*pFunc)(pCaller) : aLink.Call(pCaller); }
};

}//end of namespace binfilter
#endif
