/*************************************************************************
 *
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER.
 *
 * Copyright 2008 by Sun Microsystems, Inc.
 *
 * OpenOffice.org - a multi-platform office productivity suite
 *
 * $RCSfile: worksheetbuffer.hxx,v $
 * $Revision: 1.4.10.1 $
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

#ifndef OOX_XLS_WORKSHEETBUFFER_HXX
#define OOX_XLS_WORKSHEETBUFFER_HXX

#include <vector>
#include <map>
#include <utility>
#include "oox/xls/workbookhelper.hxx"

namespace com { namespace sun { namespace star {
    namespace i18n { class XCharacterClassification; }
} } }

namespace oox {
namespace xls {

// ============================================================================

/** Contains data from the 'sheet' element describing a sheet in the workbook. */
struct OoxSheetInfo
{
    ::rtl::OUString     maRelId;        /// Relation identifier for the sheet substream.
    ::rtl::OUString     maName;         /// Original name of the sheet.
    ::rtl::OUString     maFinalName;    /// Final (converted) name of the sheet.
    sal_Int32           mnSheetId;      /// Sheet identifier.
    sal_Int32           mnState;        /// Visibility state.

    explicit            OoxSheetInfo();
};

// ============================================================================

/** Stores information about all sheets in a spreadsheet document.

    Information about sheets includes the sheet name, the visibility state, and
    for the OOX filter, the relation identifier of the sheet used to obtain the
    related worksheet fragment.
 */
class WorksheetBuffer : public WorkbookHelper
{
public:
    explicit            WorksheetBuffer( const WorkbookHelper& rHelper );

    /** Initializes the buffer for single sheet files (BIFF2-BIFF4). */
    void                initializeSingleSheet();

    /** Imports the attributes of a sheet element. */
    void                importSheet( const AttributeList& rAttribs );
    /** Imports the SHEET record from the passed OOBIN stream. */
    void                importSheet( RecordInputStream& rStrm );
    /** Imports the SHEET record from the passed BIFF stream. */
    void                importSheet( BiffInputStream& rStrm );

    /** Returns the number of sheets contained in the workbook. */
    sal_Int32           getSheetCount() const;
    /** Returns the OOX relation identifier of the specified sheet. */
    ::rtl::OUString     getSheetRelId( sal_Int32 nSheet ) const;
    /** Returns the finalized name of the specified sheet. */
    ::rtl::OUString     getFinalSheetName( sal_Int32 nSheet ) const;
    /** Returns the finalized name of the sheet with the passed original name. */
    ::rtl::OUString     getFinalSheetName( const ::rtl::OUString& rName ) const;
    /** Returns the index of the sheet with the passed original name. */
    sal_Int32           getFinalSheetIndex( const ::rtl::OUString& rName ) const;

private:
    const OoxSheetInfo* getSheetInfo( sal_Int32 nSheet ) const;

    ::rtl::OUString     insertSheet( const ::rtl::OUString& rName, sal_Int16 nSheet, bool bVisible );
    void                insertSheet( const OoxSheetInfo& rSheetInfo );

private:
    typedef ::std::vector< OoxSheetInfo > SheetInfoVec;

    const ::rtl::OUString maIsVisibleProp;
    SheetInfoVec        maSheetInfos;
};

// ============================================================================

} // namespace xls
} // namespace oox

#endif

