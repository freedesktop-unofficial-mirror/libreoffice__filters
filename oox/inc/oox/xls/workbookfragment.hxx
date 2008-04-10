/*************************************************************************
 *
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER.
 * 
 * Copyright 2008 by Sun Microsystems, Inc.
 *
 * OpenOffice.org - a multi-platform office productivity suite
 *
 * $RCSfile: workbookfragment.hxx,v $
 * $Revision: 1.4 $
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

#ifndef OOX_XLS_WORKBOOKFRAGMENT_HXX
#define OOX_XLS_WORKBOOKFRAGMENT_HXX

#include "oox/xls/bifffragmenthandler.hxx"
#include "oox/xls/defnamesbuffer.hxx"
#include "oox/xls/excelhandlers.hxx"

namespace oox {
namespace xls {

class ExternalLink;

// ============================================================================

class OoxWorkbookFragment : public OoxWorkbookFragmentBase
{
public:
    explicit            OoxWorkbookFragment(
                            const WorkbookHelper& rHelper,
                            const ::rtl::OUString& rFragmentPath );

protected:
    // oox.core.ContextHandler2Helper interface -------------------------------

    virtual ContextWrapper onCreateContext( sal_Int32 nElement, const AttributeList& rAttribs );
    virtual void        onStartElement( const AttributeList& rAttribs );
    virtual void        onEndElement( const ::rtl::OUString& rChars );

    virtual ContextWrapper onCreateRecordContext( sal_Int32 nRecId, RecordInputStream& rStrm );
    virtual void        onStartRecord( RecordInputStream& rStrm );

    // oox.core.FragmentHandler2 interface ------------------------------------

    virtual const ::oox::core::RecordInfo* getRecordInfos() const;
    virtual void        finalizeImport();

private:
    void                importExternalReference( const AttributeList& rAttribs );
    void                importDefinedName( const AttributeList& rAttribs );
    void                importPivotCache( const AttributeList& rAttribs );

    void                importExternalRef( RecordInputStream& rStrm );

    void                importExternalLinkFragment( ExternalLink& rExtLink );

private:
    DefinedNameRef      mxCurrName;
};

// ============================================================================

class BiffWorkbookFragment : public BiffWorkbookFragmentBase
{
public:
    explicit            BiffWorkbookFragment( const WorkbookHelper& rHelper );

    /** Imports the entire workbook stream, including all contained worksheets. */
    virtual bool        importFragment( BiffInputStream& rStrm );

private:
    /** Imports a complete BIFF4 workspace fragment (with embedded sheets). */
    bool                importWorkspaceFragment( BiffInputStream& rStrm );
    /** Imports the workbook globals fragment from current stream position. */
    bool                importGlobalsFragment(
                            BiffInputStream& rStrm,
                            ISegmentProgressBar& rProgressBar );
    /** Imports a sheet fragment with passed type from current stream position. */
    bool                importSheetFragment(
                            BiffInputStream& rStrm,
                            ISegmentProgressBar& rProgressBar,
                            BiffFragmentType eFragment, sal_Int32 nSheet );

    /** Imports the FILEPASS record and sets a decoder at the passed stream. */
    bool                importFilePass( BiffInputStream& rStrm );
};

// ============================================================================

} // namespace xls
} // namespace oox

#endif

