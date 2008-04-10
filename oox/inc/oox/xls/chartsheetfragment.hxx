/*************************************************************************
 *
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER.
 * 
 * Copyright 2008 by Sun Microsystems, Inc.
 *
 * OpenOffice.org - a multi-platform office productivity suite
 *
 * $RCSfile: chartsheetfragment.hxx,v $
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

#ifndef OOX_XLS_CHARTSHEETFRAGMENT_HXX
#define OOX_XLS_CHARTSHEETFRAGMENT_HXX

#include "oox/xls/bifffragmenthandler.hxx"
#include "oox/xls/excelhandlers.hxx"

namespace oox {
namespace xls {

// ============================================================================

class OoxChartsheetFragment : public OoxWorksheetFragmentBase
{
public:
    explicit            OoxChartsheetFragment(
                            const WorkbookHelper& rHelper,
                            const ::rtl::OUString& rFragmentPath,
                            ISegmentProgressBarRef xProgressBar,
                            sal_Int32 nSheet );

protected:
    // oox.core.ContextHandler2Helper interface -------------------------------

    virtual ContextWrapper onCreateContext( sal_Int32 nElement, const AttributeList& rAttribs );
    virtual void        onStartElement( const AttributeList& rAttribs );
    virtual void        onEndElement( const ::rtl::OUString& rChars );

    virtual ContextWrapper onCreateRecordContext( sal_Int32 nRecId, RecordInputStream& rStrm );
    virtual void        onStartRecord( RecordInputStream& rStrm );

    // oox.core.FragmentHandler2 interface ------------------------------------

    virtual const ::oox::core::RecordInfo* getRecordInfos() const;
    virtual void        initializeImport();
    virtual void        finalizeImport();

private:
    /** Imports the the relation identifier for the DrawingML part. */
    void                importDrawing( const AttributeList& rAttribs );
    /** Imports the DRAWING record containing the relation identifier for the DrawingML part. */
    void                importDrawing( RecordInputStream& rStrm );
};

// ============================================================================

class BiffChartsheetFragment : public BiffWorksheetFragmentBase
{
public:
    explicit            BiffChartsheetFragment(
                            const WorkbookHelper& rHelper,
                            ISegmentProgressBarRef xProgressBar,
                            sal_Int32 nSheet );

    /** Imports the entire sheet fragment, returns true, if EOF record has been reached. */
    virtual bool        importFragment( BiffInputStream& rStrm );
};

// ============================================================================

} // namespace xls
} // namespace oox

#endif

