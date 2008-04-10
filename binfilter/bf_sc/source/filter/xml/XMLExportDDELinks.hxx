/*************************************************************************
 *
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER.
 * 
 * Copyright 2008 by Sun Microsystems, Inc.
 *
 * OpenOffice.org - a multi-platform office productivity suite
 *
 * $RCSfile: XMLExportDDELinks.hxx,v $
 * $Revision: 1.5 $
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

#ifndef _SC_XMLEXPORTDDELINKS_HXX
#define _SC_XMLEXPORTDDELINKS_HXX

#ifndef _COM_SUN_STAR_SHEET_XSPREADSHEETDOCUMENT_HPP_
#include <com/sun/star/sheet/XSpreadsheetDocument.hpp>
#endif

class String;

namespace binfilter {

class ScXMLExport;

class ScXMLExportDDELinks
{
    ScXMLExport&		rExport;

    sal_Bool			CellsEqual(const sal_Bool bPrevEmpty, const sal_Bool bPrevString, const String& sPrevValue, const double& fPrevValue,
                                    const sal_Bool bEmpty, const sal_Bool bString, const String& sValue, const double& fValue);
    void 				WriteCell(const sal_Bool bEmpty, const sal_Bool bString, const String& sValue, const double& fValue, const sal_Int32 nRepeat);
    void				WriteTable(const sal_Int32 nPos);
public:
    ScXMLExportDDELinks(ScXMLExport& rExport);
    ~ScXMLExportDDELinks();
    void WriteDDELinks(::com::sun::star::uno::Reference < ::com::sun::star::sheet::XSpreadsheetDocument >& xSpreadDoc);
};

} //namespace binfilter
#endif


