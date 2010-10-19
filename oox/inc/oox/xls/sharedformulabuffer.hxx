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

#ifndef OOX_XLS_SHAREDFORMULABUFFER_HXX
#define OOX_XLS_SHAREDFORMULABUFFER_HXX

#include <map>
#include <memory>
#include "oox/xls/worksheethelper.hxx"

namespace com { namespace sun { namespace star {
    namespace sheet { class XFormulaTokens; }
    namespace sheet { class XNamedRange; }
} } }

namespace oox {
namespace xls {

// ============================================================================

/** Formula context that supports shared formulas. */
class ExtCellFormulaContext : public SimpleFormulaContext, public WorksheetHelper
{
public:
    explicit            ExtCellFormulaContext(
                            const WorksheetHelper& rHelper,
                            const ::com::sun::star::uno::Reference< ::com::sun::star::sheet::XFormulaTokens >& rxTokens,
                            const ::com::sun::star::table::CellAddress& rCellPos );

    virtual void        setSharedFormula( const ::com::sun::star::table::CellAddress& rBaseAddr );
};

// ============================================================================

class SharedFormulaBuffer : public WorksheetHelper
{
public:
    explicit            SharedFormulaBuffer( const WorksheetHelper& rHelper );

    /** Imports a shared formula from a OOXML formula string. */
    void                importSharedFmla( const ::rtl::OUString& rFormula,
                            const ::rtl::OUString& rSharedRange, sal_Int32 nId,
                            const ::com::sun::star::table::CellAddress& rBaseAddr );
    /** Imports a shared formula from a SHAREDFORMULA record in the passed stream */
    void                importSharedFmla( RecordInputStream& rStrm,
                            const ::com::sun::star::table::CellAddress& rBaseAddr );
    /** Imports a shared formula from a SHAREDFMLA record in the passed stream. */
    void                importSharedFmla( BiffInputStream& rStrm,
                            const ::com::sun::star::table::CellAddress& rBaseAddr );

    /** Inserts a shared formula with the passed base address into a cell
        described by the passed formula context. */
    void                setSharedFormulaCell(
                            ExtCellFormulaContext& rContext,
                            const ::com::sun::star::table::CellAddress& rBaseAddr );
    /** Inserts a shared formula with the passed base address into a cell
        described by the passed formula context. */
    void                setSharedFormulaCell(
                            ExtCellFormulaContext& rContext,
                            sal_Int32 nSharedId );

private:
    ::com::sun::star::uno::Reference< ::com::sun::star::sheet::XNamedRange >
                        createDefinedName( const BinAddress& rMapKey );

    bool                implSetSharedFormulaCell(
                            ExtCellFormulaContext& rContext,
                            const BinAddress& rMapKey );

    void                updateCachedCell(
                            const ::com::sun::star::table::CellAddress& rBaseAddr,
                            const BinAddress& rMapKey );

private:
    typedef ::std::map< BinAddress, sal_Int32 >         TokenIndexMap;
    typedef ::std::auto_ptr< ExtCellFormulaContext >    ContextPtr;

    TokenIndexMap       maIndexMap;         /// Maps shared formula base address to defined name identifier.
    ContextPtr          mxLastContext;      /// Cached formula context for leading formula cell.
};

// ============================================================================

} // namespace xls
} // namespace oox

#endif
