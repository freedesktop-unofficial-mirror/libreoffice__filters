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
#ifndef _DOCFUNC_HXX
#define _DOCFUNC_HXX

#include <bf_svtools/bf_solar.h>


// Diese Klasse wird von der Editshell benutz um fuer belibige
// Doc-Aktionen ueber eine definierte Schnittstelle alle Cursor/
// Bookmarks/usw. aus dem Loeschbereich zu verschieben, mit einem
// anschliessenden Join-Node.
// Das wird zur Zeit vom
//		- Delete
//		- Replace
// benotigt.


#ifndef _STRING_HXX //autogen
#include <tools/string.hxx>
#endif
namespace binfilter {
class SwPaM;

enum DocFNType { DOC_DELETE, DOC_REPLACE };

class SwCallDocFunction
{
    // Parameter fuers Replace	(leider kein union moeglich; Str-Klasse !!)
    const String aRplStr;
    DocFNType eDocFnType;
    BOOL bRplRegExp;

public:
    // fuer parameterlose Methoden
    SwCallDocFunction( DocFNType eDocFn ) : eDocFnType( eDocFn ), aRplStr() {}
    // fuer das Replace
    SwCallDocFunction( const String& rStr, BOOL bFlag );

    BOOL Call( SwPaM& );

    // ALLE Methoden stehen im eddel.cxx !!
};


} //namespace binfilter
#endif
    //_DOCFUNC_HXX


