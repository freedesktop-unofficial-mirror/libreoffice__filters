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

#ifndef OOX_XLS_COMMENTSBUFFER_HXX
#define OOX_XLS_COMMENTSBUFFER_HXX

#include "oox/xls/richstring.hxx"
#include "oox/xls/worksheethelper.hxx"

namespace oox {
namespace xls {

// ============================================================================

struct CommentModel
{
    ::com::sun::star::table::CellRangeAddress
                        maRange;            /// Position of the comment in the worksheet.
    RichStringRef       mxText;             /// Formatted text of the comment.
    sal_Int32           mnAuthorId;         /// Identifier of the comment's author.

    explicit            CommentModel();
};

// ----------------------------------------------------------------------------

class Comment : public WorksheetHelper
{
public:
    explicit            Comment( const WorksheetHelper& rHelper );

    /** Imports a cell comment from the passed attributes of the comment element. */
    void                importComment( const AttributeList& rAttribs );
    /** Imports a cell comment from the passed stream of a COMMENT record. */
    void                importComment( RecordInputStream& rStrm );

    /** Creates and returns a new rich-string object for the comment text. */
    RichStringRef       createText();

    /** Finalizes the formatted string of the comment. */
    void                finalizeImport();

private:
    CommentModel        maModel;
};

typedef ::boost::shared_ptr< Comment > CommentRef;

// ============================================================================

class CommentsBuffer : public WorksheetHelper
{
public:
    explicit            CommentsBuffer( const WorksheetHelper& rHelper );

    /** Appends a new author to the list of comment authors. */
    void                appendAuthor( const ::rtl::OUString& rAuthor );
    /** Creates and returns a new comment. */
    CommentRef          createComment();

    /** Finalizes the formatted string of all comments. */
    void                finalizeImport();

private:
    typedef ::std::vector< ::rtl::OUString >    OUStringVector;
    typedef RefVector< Comment >                CommentVector;

    OUStringVector      maAuthors;
    CommentVector       maComments;
};

// ============================================================================

} // namespace xls
} // namespace oox

#endif

