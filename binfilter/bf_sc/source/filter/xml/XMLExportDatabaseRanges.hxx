/*************************************************************************
 *
 *  $RCSfile: XMLExportDatabaseRanges.hxx,v $
 *
 *  $Revision: 1.3 $
 *
 *  last change: $Author: hr $ $Date: 2004-08-03 11:24:24 $
 *
 *  The Contents of this file are made available subject to the terms of
 *  either of the following licenses
 *
 *         - GNU Lesser General Public License Version 2.1
 *         - Sun Industry Standards Source License Version 1.1
 *
 *  Sun Microsystems Inc., October, 2000
 *
 *  GNU Lesser General Public License Version 2.1
 *  =============================================
 *  Copyright 2000 by Sun Microsystems, Inc.
 *  901 San Antonio Road, Palo Alto, CA 94303, USA
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public
 *  License version 2.1, as published by the Free Software Foundation.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public
 *  License along with this library; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 *  MA  02111-1307  USA
 *
 *
 *  Sun Industry Standards Source License Version 1.1
 *  =================================================
 *  The contents of this file are subject to the Sun Industry Standards
 *  Source License Version 1.1 (the "License"); You may not use this file
 *  except in compliance with the License. You may obtain a copy of the
 *  License at http://www.openoffice.org/license.html.
 *
 *  Software provided under this License is provided on an "AS IS" basis,
 *  WITHOUT WARRANTY OF ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING,
 *  WITHOUT LIMITATION, WARRANTIES THAT THE SOFTWARE IS FREE OF DEFECTS,
 *  MERCHANTABLE, FIT FOR A PARTICULAR PURPOSE, OR NON-INFRINGING.
 *  See the License for the specific provisions governing your rights and
 *  obligations concerning the Software.
 *
 *  The Initial Developer of the Original Code is: Sun Microsystems, Inc.
 *
 *  Copyright: 2000 by Sun Microsystems, Inc.
 *
 *  All Rights Reserved.
 *
 *  Contributor(s): _______________________________________
 *
 *
 ************************************************************************/

#ifndef SC_XMLEXPORTDATABASERANGES_HXX
#define SC_XMLEXPORTDATABASERANGES_HXX

#ifndef _COM_SUN_STAR_UNO_SEQUENCE_H_
#include <com/sun/star/uno/Sequence.h>
#endif
#ifndef _COM_SUN_STAR_BEANS_PROPERTYVALUE_HPP_
#include <com/sun/star/beans/PropertyValue.hpp>
#endif
// auto strip #ifndef _COM_SUN_STAR_SHEET_FILTEROPERATOR_HPP_
// auto strip #include <com/sun/star/sheet/FilterOperator.hpp>
// auto strip #endif
// auto strip #ifndef _COM_SUN_STAR_SHEET_TABLEFILTERFIELD_HPP_
// auto strip #include <com/sun/star/sheet/TableFilterField.hpp>
// auto strip #endif
#ifndef _COM_SUN_STAR_SHEET_XSHEETFILTERDESCRIPTOR_HPP_
#include <com/sun/star/sheet/XSheetFilterDescriptor.hpp>
#endif
#ifndef _COM_SUN_STAR_SHEET_XSUBTOTALDESCRIPTOR_HPP_
#include <com/sun/star/sheet/XSubTotalDescriptor.hpp>
#endif
#ifndef _COM_SUN_STAR_SHEET_XSPREADSHEETDOCUMENT_HPP_
#include <com/sun/star/sheet/XSpreadsheetDocument.hpp>
#endif
namespace binfilter {

class ScXMLExport;
class ScDocument;
class ScMyEmptyDatabaseRangesContainer;

class ScXMLExportDatabaseRanges
{
    ScXMLExport&	rExport;
    ScDocument*		pDoc;

    void WriteImportDescriptor(const ::com::sun::star::uno::Sequence < ::com::sun::star::beans::PropertyValue> aImportDescriptor);
    ::rtl::OUString getOperatorXML(const ::com::sun::star::sheet::FilterOperator aFilterOperator, const sal_Bool bUseRegularExpressions) const;
    void WriteCondition(const ::com::sun::star::sheet::TableFilterField& aFilterField, sal_Bool bIsCaseSensitive, sal_Bool bUseRegularExpressions);
    void WriteFilterDescriptor(const ::com::sun::star::uno::Reference < ::com::sun::star::sheet::XSheetFilterDescriptor>& xSheetFilterDescriptor, const ::rtl::OUString sDatabaseRangeName);
    void WriteSortDescriptor(const ::com::sun::star::uno::Sequence < ::com::sun::star::beans::PropertyValue> aSortProperties);
    void WriteSubTotalDescriptor(const ::com::sun::star::uno::Reference < ::com::sun::star::sheet::XSubTotalDescriptor> xSubTotalDescriptor, const ::rtl::OUString sDatabaseRangeName);
public:
    ScXMLExportDatabaseRanges(ScXMLExport& rExport);
    ~ScXMLExportDatabaseRanges();
    ScMyEmptyDatabaseRangesContainer GetEmptyDatabaseRanges();
    void WriteDatabaseRanges(const ::com::sun::star::uno::Reference < ::com::sun::star::sheet::XSpreadsheetDocument>& xSpreadDoc);
};

} //namespace binfilter
#endif

