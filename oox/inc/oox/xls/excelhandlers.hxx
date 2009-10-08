/*************************************************************************
 *
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER.
 *
 * Copyright 2008 by Sun Microsystems, Inc.
 *
 * OpenOffice.org - a multi-platform office productivity suite
 *
 * $RCSfile: excelhandlers.hxx,v $
 * $Revision: 1.4.20.2 $
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

#ifndef OOX_XLS_EXCELHANDLERS_HXX
#define OOX_XLS_EXCELHANDLERS_HXX

#include "oox/core/fragmenthandler2.hxx"
#include "oox/xls/worksheethelper.hxx"

#define XML_TOKEN( token )          (::oox::NMSP_XML | XML_##token)
#define R_TOKEN( token )            (::oox::NMSP_RELATIONSHIPS | XML_##token)
#define XLS_TOKEN( token )          (::oox::NMSP_XLS | XML_##token)
#define XDR_TOKEN( token )          (::oox::NMSP_XDR | XML_##token)
#define XM_TOKEN( token )           (::oox::NMSP_XM | XML_##token)

namespace oox {
namespace xls {

typedef ::oox::core::ContextHandler2    OoxContextHandler;
typedef ::oox::core::FragmentHandler2   OoxFragmentHandler;

typedef ::oox::core::ContextWrapper     ContextWrapper;

// ============================================================================
// ============================================================================

/** Context handler derived from the WorkbookHelper helper class.

    Used to import contexts in global workbook fragments.
 */
class OoxWorkbookContextBase : public OoxContextHandler, public WorkbookHelper
{
public:
    template< typename ParentType >
    explicit            OoxWorkbookContextBase( ParentType& rParent );
};

// ----------------------------------------------------------------------------

template< typename ParentType >
OoxWorkbookContextBase::OoxWorkbookContextBase( ParentType& rParent ) :
    OoxContextHandler( rParent ),
    WorkbookHelper( rParent )
{
}

// ============================================================================

/** Context handler derived from the WorksheetHelper helper class.

    Used to import contexts in sheet fragments.
 */
class OoxWorksheetContextBase : public OoxContextHandler, public WorksheetHelperRoot
{
public:
    template< typename ParentType >
    explicit            OoxWorksheetContextBase(
                            ParentType& rParent,
                            ISegmentProgressBarRef xProgressBar,
                            WorksheetType eSheetType,
                            sal_Int32 nSheet );

    template< typename ParentType >
    explicit            OoxWorksheetContextBase( ParentType& rParent );
};

// ----------------------------------------------------------------------------

template< typename ParentType >
OoxWorksheetContextBase::OoxWorksheetContextBase( ParentType& rParent,
        ISegmentProgressBarRef xProgressBar, WorksheetType eSheetType, sal_Int32 nSheet ) :
    OoxContextHandler( rParent ),
    WorksheetHelperRoot( rParent, xProgressBar, eSheetType, nSheet )
{
}

template< typename ParentType >
OoxWorksheetContextBase::OoxWorksheetContextBase( ParentType& rParent ) :
    OoxContextHandler( rParent ),
    WorksheetHelperRoot( rParent )
{
}

// ============================================================================

/** Fragment handler derived from the WorkbookHelper helper class.

    Used to import global workbook fragments.
 */
class OoxWorkbookFragmentBase : public OoxFragmentHandler, public WorkbookHelper
{
public:
    explicit            OoxWorkbookFragmentBase(
                            const WorkbookHelper& rHelper,
                            const ::rtl::OUString& rFragmentPath );
};

// ============================================================================

/** Fragment handler derived from the WorksheetHelper helper class.

    Used to import sheet fragments.
 */
class OoxWorksheetFragmentBase : public OoxFragmentHandler, public WorksheetHelperRoot
{
public:
    explicit            OoxWorksheetFragmentBase(
                            const WorkbookHelper& rHelper,
                            const ::rtl::OUString& rFragmentPath,
                            ISegmentProgressBarRef xProgressBar,
                            WorksheetType eSheetType,
                            sal_Int32 nSheet );

    explicit            OoxWorksheetFragmentBase(
                            const WorksheetHelper& rHelper,
                            const ::rtl::OUString& rFragmentPath );
};

// ============================================================================
// ============================================================================

/** An enumeration for all types of fragments in a BIFF workbook stream. */
enum BiffFragmentType
{
    BIFF_FRAGMENT_GLOBALS,      /// Workbook globals fragment.
    BIFF_FRAGMENT_WORKSHEET,    /// Worksheet fragment.
    BIFF_FRAGMENT_CHARTSHEET,   /// Chart sheet fragment.
    BIFF_FRAGMENT_MACROSHEET,   /// Macro sheet fragment.
    BIFF_FRAGMENT_MODULESHEET,  /// BIFF5 VB module fragment.
    BIFF_FRAGMENT_EMPTYSHEET,   /// Sheet fragment of unsupported type.
    BIFF_FRAGMENT_WORKSPACE,    /// BIFF4 workspace/workbook globals.
    BIFF_FRAGMENT_UNKNOWN       /// Unknown fragment/error.
};

// ============================================================================

/** Base class for all BIFF context handlers and fragment handlers.

    This base class holds a reference to the BIFF input stream which can be
    accessed in all derived classes.
 */
class BiffHandlerBase
{
protected:
    inline explicit     BiffHandlerBase( BiffInputStream& rStrm ) : mrStrm( rStrm ) {}
    virtual             ~BiffHandlerBase();

    /** Skips a block of records up to the specified end record.

        Skips all records until next end record. When this function returns,
        stream points to the end record, and the next call of startNextRecord()
        at the stream will start the record following the end record.

        The identifier of the record that is active while this function is
        called is used as start record identifier. This identifier is used to
        correctly skip embedded record blocks with the same start and end
        record identifier.

        @return  True = stream points to the end record.
     */
    bool                skipRecordBlock( sal_uInt16 nEndRecId );

    /** @return  True = current record identifier is a BOF record. */
    bool                isBofRecord() const;

protected:
    BiffInputStream&    mrStrm;
};

// ============================================================================

/** Base class for all BIFF context handlers.

    Derived handlers have to implement the importRecord() function that has to
    import the record the BIFF input stream currently points to.
 */
class BiffContextHandler : public BiffHandlerBase
{
public:
    /** Derived classes have to implement importing the current record. */
    virtual void        importRecord() = 0;

protected:
    explicit            BiffContextHandler( const BiffHandlerBase& rParent );
};

// ============================================================================

/** Context handler derived from the WorkbookHelper helper class.

    Used to import contexts in global workbook fragments.
 */
class BiffWorkbookContextBase : public BiffContextHandler, public WorkbookHelper
{
protected:
    template< typename ParentType >
    explicit            BiffWorkbookContextBase( const ParentType& rParent );
};

// ----------------------------------------------------------------------------

template< typename ParentType >
BiffWorkbookContextBase::BiffWorkbookContextBase( const ParentType& rParent ) :
    BiffContextHandler( rParent ),
    WorkbookHelper( rParent )
{
}

// ============================================================================

/** Context handler derived from the WorksheetHelper helper class.

    Used to import contexts in sheet fragments.
 */
class BiffWorksheetContextBase : public BiffContextHandler, public WorksheetHelperRoot
{
protected:
    template< typename ParentType >
    explicit            BiffWorksheetContextBase(
                            const ParentType& rParent,
                            ISegmentProgressBarRef xProgressBar,
                            WorksheetType eSheetType,
                            sal_Int32 nSheet );

    template< typename ParentType >
    explicit            BiffWorksheetContextBase( const ParentType& rParent );
};

// ----------------------------------------------------------------------------

template< typename ParentType >
BiffWorksheetContextBase::BiffWorksheetContextBase( const ParentType& rParent,
        ISegmentProgressBarRef xProgressBar, WorksheetType eSheetType, sal_Int32 nSheet ) :
    BiffContextHandler( rParent ),
    WorksheetHelperRoot( rParent, xProgressBar, eSheetType, nSheet )
{
}

template< typename ParentType >
BiffWorksheetContextBase::BiffWorksheetContextBase( const ParentType& rParent ) :
    BiffContextHandler( rParent ),
    WorksheetHelperRoot( rParent )
{
}

// ============================================================================

class BiffFragmentHandler : public BiffHandlerBase
{
public:
    /** Imports the fragment, returns true, if EOF record has been reached. */
    virtual bool        importFragment() = 0;

protected:
    explicit            BiffFragmentHandler( BiffInputStream& rStrm );

    /** Starts a new fragment in a workbbok stream and returns the fragment type.

        The passed stream must point before a BOF record. The function will
        try to start the next record and read the contents of the BOF record,
        if extant.

        @return  Fragment type according to the imported BOF record.
     */
    BiffFragmentType    startFragment( BiffType eBiff );

    /** Skips the current fragment up to its trailing EOF record.

        Skips all records until next EOF record. When this function returns,
        stream points to the EOF record, and the next call of startNextRecord()
        at the stream will start the record following the EOF record.

        Embedded fragments enclosed in BOF/EOF records (e.g. embedded chart
        objects) are skipped correctly.

        @return  True = stream points to the EOF record of the current fragment.
     */
    bool                skipFragment();
};

// ============================================================================

/** Fragment handler derived from the WorkbookHelper helper class.

    Used to import global workbook fragments.
 */
class BiffWorkbookFragmentBase : public BiffFragmentHandler, public WorkbookHelper
{
protected:
    explicit            BiffWorkbookFragmentBase(
                            const WorkbookHelper& rHelper,
                            BiffInputStream& rStrm );
};

// ============================================================================

/** Fragment handler derived from the WorksheetHelper helper class.

    Used to import sheet fragments.
 */
class BiffWorksheetFragmentBase : public BiffFragmentHandler, public WorksheetHelperRoot
{
protected:
    explicit            BiffWorksheetFragmentBase(
                            const BiffWorkbookFragmentBase& rParent,
                            ISegmentProgressBarRef xProgressBar,
                            WorksheetType eSheetType,
                            sal_Int32 nSheet );

    explicit            BiffWorksheetFragmentBase(
                            const WorksheetHelper& rHelper,
                            BiffInputStream& rStrm );
};

// ============================================================================

class BiffSkipWorksheetFragment : public BiffWorksheetFragmentBase
{
public:
    explicit            BiffSkipWorksheetFragment(
                            const BiffWorkbookFragmentBase& rParent,
                            ISegmentProgressBarRef xProgressBar,
                            sal_Int32 nSheet );

    virtual bool        importFragment();
};

// ============================================================================
// ============================================================================

} // namespace xls
} // namespace oox

#endif

