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

#ifndef SC_HTMLIMP_HXX
#define SC_HTMLIMP_HXX

#include <bf_svtools/bf_solar.h>

#include "eeimport.hxx"
namespace binfilter {

class ScHTMLParser;

class ScHTMLImport : public ScEEImport
{
private:
    static void			InsertRangeName( ScDocument* pDoc, const String& rName, const ScRange& rRange );

public:
                        ScHTMLImport( ScDocument* pDoc, const ScRange& rRange, BOOL bCalcWidthHeight = TRUE );
                        ~ScHTMLImport();
    const ScHTMLParser*	GetParser() const { return (ScHTMLParser*)pParser; }

    virtual void		WriteToDocument( BOOL bSizeColsRows = FALSE, double nOutputFactor = 1.0 );

    static String		GetHTMLRangeNameList( ScDocument* pDoc, const String& rOrigName );
};


} //namespace binfilter
#endif
