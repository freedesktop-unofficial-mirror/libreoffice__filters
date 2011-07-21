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

#include "oox/xls/sheetdatabuffer.hxx"

#include <algorithm>
#include <com/sun/star/sheet/XArrayFormulaTokens.hpp>
#include <com/sun/star/sheet/XCellRangeData.hpp>
#include <com/sun/star/sheet/XFormulaTokens.hpp>
#include <com/sun/star/sheet/XMultipleOperation.hpp>
#include <com/sun/star/table/XCell.hpp>
#include <com/sun/star/text/XText.hpp>
#include <com/sun/star/util/DateTime.hpp>
#include <com/sun/star/util/NumberFormat.hpp>
#include <com/sun/star/util/XMergeable.hpp>
#include <com/sun/star/util/XNumberFormatTypes.hpp>
#include <com/sun/star/util/XNumberFormatsSupplier.hpp>
#include <rtl/ustrbuf.hxx>
#include "oox/helper/containerhelper.hxx"
#include "oox/helper/propertymap.hxx"
#include "oox/helper/propertyset.hxx"
#include "oox/token/tokens.hxx"
#include "oox/xls/addressconverter.hxx"
#include "oox/xls/biffinputstream.hxx"
#include "oox/xls/formulaparser.hxx"
#include "oox/xls/sharedstringsbuffer.hxx"
#include "oox/xls/unitconverter.hxx"

namespace oox {
namespace xls {

// ============================================================================

using namespace ::com::sun::star::lang;
using namespace ::com::sun::star::sheet;
using namespace ::com::sun::star::table;
using namespace ::com::sun::star::text;
using namespace ::com::sun::star::uno;
using namespace ::com::sun::star::util;

using ::rtl::OUString;
using ::rtl::OUStringBuffer;

// ============================================================================

CellModel::CellModel() :
    mnCellType( XML_TOKEN_INVALID ),
    mnXfId( -1 ),
    mbShowPhonetic( false )
{
}

// ----------------------------------------------------------------------------

CellFormulaModel::CellFormulaModel() :
    mnFormulaType( XML_TOKEN_INVALID ),
    mnSharedId( -1 )
{
}

bool CellFormulaModel::isValidArrayRef( const CellAddress& rCellAddr )
{
    return
        (maFormulaRef.Sheet == rCellAddr.Sheet) &&
        (maFormulaRef.StartColumn == rCellAddr.Column) &&
        (maFormulaRef.StartRow == rCellAddr.Row);
}

bool CellFormulaModel::isValidSharedRef( const CellAddress& rCellAddr )
{
    return
        (maFormulaRef.Sheet == rCellAddr.Sheet) &&
        (maFormulaRef.StartColumn <= rCellAddr.Column) && (rCellAddr.Column <= maFormulaRef.EndColumn) &&
        (maFormulaRef.StartRow <= rCellAddr.Row) && (rCellAddr.Row <= maFormulaRef.EndRow);
}

// ----------------------------------------------------------------------------

DataTableModel::DataTableModel() :
    mb2dTable( false ),
    mbRowTable( false ),
    mbRef1Deleted( false ),
    mbRef2Deleted( false )
{
}

// ============================================================================

namespace {

const sal_Int32 CELLBLOCK_MAXROWS  = 16;    /// Number of rows in a cell block.

} // namespace

CellBlock::CellBlock( const WorksheetHelper& rHelper, const ValueRange& rColSpan, sal_Int32 nRow ) :
    WorksheetHelper( rHelper ),
    maRange( rHelper.getSheetIndex(), rColSpan.mnFirst, nRow, rColSpan.mnLast, nRow ),
    mnRowLength( rColSpan.mnLast - rColSpan.mnFirst + 1 ),
    mnFirstFreeIndex( 0 )
{
    maCellArray.realloc( 1 );
    maCellArray[ 0 ].realloc( mnRowLength );
    mpCurrCellRow = maCellArray[ 0 ].getArray();
}

bool CellBlock::isExpandable( const ValueRange& rColSpan ) const
{
    return (maRange.StartColumn == rColSpan.mnFirst) && (maRange.EndColumn == rColSpan.mnLast);
}

bool CellBlock::isBefore( const ValueRange& rColSpan ) const
{
    return (maRange.EndColumn < rColSpan.mnLast) ||
        ((maRange.EndColumn == rColSpan.mnLast) && (maRange.StartColumn != rColSpan.mnFirst));
}

bool CellBlock::contains( sal_Int32 nCol ) const
{
    return (maRange.StartColumn <= nCol) && (nCol <= maRange.EndColumn);
}

void CellBlock::insertRichString( const CellAddress& rAddress, const RichStringRef& rxString, const Font* pFirstPortionFont )
{
    maRichStrings.push_back( RichStringCell( rAddress, rxString, pFirstPortionFont ) );
}

void CellBlock::startNextRow()
{
    // fill last cells in current row with empty strings (placeholder for empty cells)
    fillUnusedCells( mnRowLength );
    // flush if the cell block reaches maximum size
    if( maCellArray.getLength() == CELLBLOCK_MAXROWS )
    {
        finalizeImport();
        maRange.StartRow = ++maRange.EndRow;
        maCellArray.realloc( 1 );
        mpCurrCellRow = maCellArray[ 0 ].getArray();
    }
    else
    {
        // prepare next row
        ++maRange.EndRow;
        sal_Int32 nRowCount = maCellArray.getLength();
        maCellArray.realloc( nRowCount + 1 );
        maCellArray[ nRowCount ].realloc( mnRowLength );
        mpCurrCellRow = maCellArray[ nRowCount ].getArray();
    }
    mnFirstFreeIndex = 0;
}

Any& CellBlock::getCellAny( sal_Int32 nCol )
{
    OSL_ENSURE( contains( nCol ), "CellBlock::getCellAny - invalid column" );
    // fill cells before passed column with empty strings (the placeholder for empty cells)
    sal_Int32 nIndex = nCol - maRange.StartColumn;
    fillUnusedCells( nIndex );
    mnFirstFreeIndex = nIndex + 1;
    return mpCurrCellRow[ nIndex ];
}

void CellBlock::finalizeImport()
{
    // fill last cells in last row with empty strings (placeholder for empty cells)
    fillUnusedCells( mnRowLength );
    // insert all buffered cells into the Calc sheet
    try
    {
        Reference< XCellRangeData > xRangeData( getCellRange( maRange ), UNO_QUERY_THROW );
        xRangeData->setDataArray( maCellArray );
    }
    catch( Exception& )
    {
    }
    // insert uncacheable cells separately
    for( RichStringCellList::const_iterator aIt = maRichStrings.begin(), aEnd = maRichStrings.end(); aIt != aEnd; ++aIt )
        putRichString( aIt->maCellAddr, *aIt->mxString, aIt->mpFirstPortionFont );
}

// private --------------------------------------------------------------------

CellBlock::RichStringCell::RichStringCell( const CellAddress& rCellAddr, const RichStringRef& rxString, const Font* pFirstPortionFont ) :
    maCellAddr( rCellAddr ),
    mxString( rxString ),
    mpFirstPortionFont( pFirstPortionFont )
{
}

void CellBlock::fillUnusedCells( sal_Int32 nIndex )
{
    if( mnFirstFreeIndex < nIndex )
    {
        Any* pCellEnd = mpCurrCellRow + nIndex;
        for( Any* pCell = mpCurrCellRow + mnFirstFreeIndex; pCell < pCellEnd; ++pCell )
            *pCell <<= OUString();
    }
}

// ============================================================================

CellBlockBuffer::CellBlockBuffer( const WorksheetHelper& rHelper ) :
    WorksheetHelper( rHelper ),
    mnCurrRow( -1 )
{
    maCellBlockIt = maCellBlocks.end();
}

void CellBlockBuffer::setColSpans( sal_Int32 nRow, const ValueRangeSet& rColSpans )
{
    OSL_ENSURE( maColSpans.count( nRow ) == 0, "CellBlockBuffer::setColSpans - multiple column spans for the same row" );
    OSL_ENSURE( (mnCurrRow < nRow) && (maColSpans.empty() || (maColSpans.rbegin()->first < nRow)), "CellBlockBuffer::setColSpans - rows are unsorted" );
    if( (mnCurrRow < nRow) && (maColSpans.count( nRow ) == 0) )
        maColSpans[ nRow ] = rColSpans.getRanges();
}

CellBlock* CellBlockBuffer::getCellBlock( const CellAddress& rCellAddr )
{
    // Temporarily disabled. TODO: Fix this.
    return NULL;

    OSL_ENSURE( rCellAddr.Row >= mnCurrRow, "CellBlockBuffer::getCellBlock - passed row out of order" );
    // prepare cell blocks, if row changes
    if( rCellAddr.Row != mnCurrRow )
    {
        // find colspans for the new row
        ColSpanVectorMap::iterator aIt = maColSpans.find( rCellAddr.Row );

        /*  Gap between rows, or rows out of order, or no colspan
            information for the new row found: flush all open cell blocks. */
        if( (aIt == maColSpans.end()) || (rCellAddr.Row != mnCurrRow + 1) )
        {
            finalizeImport();
            maCellBlocks.clear();
            maCellBlockIt = maCellBlocks.end();
        }

        /*  Prepare matching cell blocks, create new cell blocks, finalize
            unmatching cell blocks, if colspan information is available. */
        if( aIt != maColSpans.end() )
        {
            /*  The colspan vector aIt points to is sorted by columns, as well
                as the cell block map. In the folloing, this vector and the
                list of cell blocks can be iterated simultanously. */
            CellBlockMap::iterator aMIt = maCellBlocks.begin();
            const ValueRangeVector& rColRanges = aIt->second;
            for( ValueRangeVector::const_iterator aVIt = rColRanges.begin(), aVEnd = rColRanges.end(); aVIt != aVEnd; ++aVIt, ++aMIt )
            {
                const ValueRange& rColSpan = *aVIt;
                /*  Finalize and remove all cell blocks up to end of the column
                    range (cell blocks are keyed by end column index).
                    CellBlock::isBefore() returns true, if the end index of the
                    passed colspan is greater than the column end index of the
                    cell block, or if the passed range has the same end index
                    but the start indexes do not match. */
                while( (aMIt != maCellBlocks.end()) && aMIt->second->isBefore( rColSpan ) )
                {
                    aMIt->second->finalizeImport();
                    maCellBlocks.erase( aMIt++ );
                }
                /*  If the current cell block (aMIt) fits to the colspan, start
                    a new row there, otherwise create and insert a new cell block. */
                if( (aMIt != maCellBlocks.end()) && aMIt->second->isExpandable( rColSpan ) )
                    aMIt->second->startNextRow();
                else
                    aMIt = maCellBlocks.insert( aMIt, CellBlockMap::value_type( rColSpan.mnLast,
                        CellBlockMap::mapped_type( new CellBlock( *this, rColSpan, rCellAddr.Row ) ) ) );
            }
            // finalize and remove all remaining cell blocks
            CellBlockMap::iterator aMEnd = maCellBlocks.end();
            for( CellBlockMap::iterator aMIt2 = aMIt; aMIt2 != aMEnd; ++aMIt2 )
                aMIt2->second->finalizeImport();
            maCellBlocks.erase( aMIt, aMEnd );

            // remove cached colspan information (including current one aIt points to)
            maColSpans.erase( maColSpans.begin(), ++aIt );
        }
        maCellBlockIt = maCellBlocks.begin();
        mnCurrRow = rCellAddr.Row;
    }

    // try to find a valid cell block (update maCellBlockIt)
    if( ((maCellBlockIt != maCellBlocks.end()) && maCellBlockIt->second->contains( rCellAddr.Column )) ||
        (((maCellBlockIt = maCellBlocks.lower_bound( rCellAddr.Column )) != maCellBlocks.end()) && maCellBlockIt->second->contains( rCellAddr.Column )) )
    {
        // maCellBlockIt points to valid cell block
        return maCellBlockIt->second.get();
    }

    // no valid cell block found
    return 0;
}

void CellBlockBuffer::finalizeImport()
{
    maCellBlocks.forEachMem( &CellBlock::finalizeImport );
}

// ============================================================================

SheetDataBuffer::SheetDataBuffer( const WorksheetHelper& rHelper ) :
    WorksheetHelper( rHelper ),
    maCellBlocks( rHelper ),
    mbPendingSharedFmla( false )
{
}

void SheetDataBuffer::setColSpans( sal_Int32 nRow, const ValueRangeSet& rColSpans )
{
    maCellBlocks.setColSpans( nRow, rColSpans );
}

void SheetDataBuffer::setBlankCell( const CellModel& rModel )
{
    setCellFormat( rModel );
}

void SheetDataBuffer::setValueCell( const CellModel& rModel, double fValue )
{
    if( CellBlock* pCellBlock = maCellBlocks.getCellBlock( rModel.maCellAddr ) )
        pCellBlock->getCellAny( rModel.maCellAddr.Column ) <<= fValue;
    else
        putValue( rModel.maCellAddr, fValue );
    setCellFormat( rModel );
}

void SheetDataBuffer::setStringCell( const CellModel& rModel, const OUString& rText )
{
    if( CellBlock* pCellBlock = maCellBlocks.getCellBlock( rModel.maCellAddr ) )
        pCellBlock->getCellAny( rModel.maCellAddr.Column ) <<= rText;
    else
        putString( rModel.maCellAddr, rText );
    setCellFormat( rModel );
}

void SheetDataBuffer::setStringCell( const CellModel& rModel, const RichStringRef& rxString )
{
    OSL_ENSURE( rxString.get(), "SheetDataBuffer::setStringCell - missing rich string object" );
    const Font* pFirstPortionFont = getStyles().getFontFromCellXf( rModel.mnXfId ).get();
    OUString aText;
    if( rxString->extractPlainString( aText, pFirstPortionFont ) )
    {
        setStringCell( rModel, aText );
    }
    else
    {
        if( CellBlock* pCellBlock = maCellBlocks.getCellBlock( rModel.maCellAddr ) )
            pCellBlock->insertRichString( rModel.maCellAddr, rxString, pFirstPortionFont );
        else
            putRichString( rModel.maCellAddr, *rxString, pFirstPortionFont );
        setCellFormat( rModel );
    }
}

void SheetDataBuffer::setStringCell( const CellModel& rModel, sal_Int32 nStringId )
{
    RichStringRef xString = getSharedStrings().getString( nStringId );
    if( xString.get() )
        setStringCell( rModel, xString );
    else
        setBlankCell( rModel );
}

void SheetDataBuffer::setDateTimeCell( const CellModel& rModel, const DateTime& rDateTime )
{
    // write serial date/time value into the cell
    double fSerial = getUnitConverter().calcSerialFromDateTime( rDateTime );
    setValueCell( rModel, fSerial );
    // set appropriate number format
    using namespace ::com::sun::star::util::NumberFormat;
    sal_Int16 nStdFmt = (fSerial < 1.0) ? TIME : (((rDateTime.Hours > 0) || (rDateTime.Minutes > 0) || (rDateTime.Seconds > 0)) ? DATETIME : DATE);
    setStandardNumFmt( rModel.maCellAddr, nStdFmt );
}

void SheetDataBuffer::setBooleanCell( const CellModel& rModel, bool bValue )
{
    setCellFormula( rModel.maCellAddr, getFormulaParser().convertBoolToFormula( bValue ) );
    // #108770# set 'Standard' number format for all Boolean cells
    setCellFormat( rModel, 0 );
}

void SheetDataBuffer::setErrorCell( const CellModel& rModel, const OUString& rErrorCode )
{
    setErrorCell( rModel, getUnitConverter().calcBiffErrorCode( rErrorCode ) );
}

void SheetDataBuffer::setErrorCell( const CellModel& rModel, sal_uInt8 nErrorCode )
{
    setCellFormula( rModel.maCellAddr, getFormulaParser().convertErrorToFormula( nErrorCode ) );
    setCellFormat( rModel );
}

void SheetDataBuffer::setFormulaCell( const CellModel& rModel, const ApiTokenSequence& rTokens )
{
    mbPendingSharedFmla = false;
    ApiTokenSequence aTokens;

    /*  Detect special token passed as placeholder for array formulas, shared
        formulas, and table operations. In BIFF, these formulas are represented
        by a single tExp resp. tTbl token. If the formula parser finds these
        tokens, it puts a single OPCODE_BAD token with the base address and
        formula type into the token sequence. This information will be
        extracted here, and in case of a shared formula, the shared formula
        buffer will generate the resulting formula token array. */
    ApiSpecialTokenInfo aTokenInfo;
    if( rTokens.hasElements() && getFormulaParser().extractSpecialTokenInfo( aTokenInfo, rTokens ) )
    {
        /*  The second member of the token info is set to true, if the formula
            represents a table operation, which will be skipped. In BIFF12 it
            is not possible to distinguish array and shared formulas
            (BIFF5/BIFF8 provide this information with a special flag in the
            FORMULA record). */
        if( !aTokenInfo.Second )
        {
            /*  Construct the token array representing the shared formula. If
                the returned sequence is empty, the definition of the shared
                formula has not been loaded yet, or the cell is part of an
                array formula. In this case, the cell will be remembered. After
                reading the formula definition it will be retried to insert the
                formula via retryPendingSharedFormulaCell(). */
            BinAddress aBaseAddr( aTokenInfo.First );
            aTokens = resolveSharedFormula( aBaseAddr );
            if( !aTokens.hasElements() )
            {
                maSharedFmlaAddr = rModel.maCellAddr;
                maSharedBaseAddr = aBaseAddr;
                mbPendingSharedFmla = true;
            }
        }
    }
    else
    {
        // simple formula, use the passed token array
        aTokens = rTokens;
    }

    setCellFormula( rModel.maCellAddr, aTokens );
    setCellFormat( rModel );
}

void SheetDataBuffer::setFormulaCell( const CellModel& rModel, sal_Int32 nSharedId )
{
    setCellFormula( rModel.maCellAddr, resolveSharedFormula( BinAddress( nSharedId, 0 ) ) );
    setCellFormat( rModel );
}

void SheetDataBuffer::createArrayFormula( const CellRangeAddress& rRange, const ApiTokenSequence& rTokens )
{
    /*  Array formulas will be inserted later in finalizeImport(). This is
        needed to not disturb collecting all the cells, which will be put into
        the sheet in large blocks to increase performance. */
    maArrayFormulas.push_back( ArrayFormula( rRange, rTokens ) );
}

void SheetDataBuffer::createTableOperation( const CellRangeAddress& rRange, const DataTableModel& rModel )
{
    /*  Table operations will be inserted later in finalizeImport(). This is
        needed to not disturb collecting all the cells, which will be put into
        the sheet in large blocks to increase performance. */
    maTableOperations.push_back( TableOperation( rRange, rModel ) );
}

void SheetDataBuffer::createSharedFormula( sal_Int32 nSharedId, const ApiTokenSequence& rTokens )
{
    createSharedFormula( BinAddress( nSharedId, 0 ), rTokens );
}

void SheetDataBuffer::createSharedFormula( const CellAddress& rCellAddr, const ApiTokenSequence& rTokens )
{
    createSharedFormula( BinAddress( rCellAddr ), rTokens );
}

void SheetDataBuffer::setRowFormat( sal_Int32 nRow, sal_Int32 nXfId, bool bCustomFormat )
{
    // set row formatting
    if( bCustomFormat )
    {
        // try to expand cached row range, if formatting is equal
        if( (maXfIdRowRange.maRowRange.mnLast < 0) || !maXfIdRowRange.tryExpand( nRow, nXfId ) )
        {
            writeXfIdRowRangeProperties( maXfIdRowRange );
            maXfIdRowRange.set( nRow, nXfId );
        }
    }
    else if( maXfIdRowRange.maRowRange.mnLast >= 0 )
    {
        // finish last cached row range
        writeXfIdRowRangeProperties( maXfIdRowRange );
        maXfIdRowRange.set( -1, -1 );
    }
}

void SheetDataBuffer::setMergedRange( const CellRangeAddress& rRange )
{
    maMergedRanges.push_back( MergedRange( rRange ) );
}

void SheetDataBuffer::setStandardNumFmt( const CellAddress& rCellAddr, sal_Int16 nStdNumFmt )
{
    try
    {
        Reference< XNumberFormatsSupplier > xNumFmtsSupp( getDocument(), UNO_QUERY_THROW );
        Reference< XNumberFormatTypes > xNumFmtTypes( xNumFmtsSupp->getNumberFormats(), UNO_QUERY_THROW );
        sal_Int32 nIndex = xNumFmtTypes->getStandardFormat( nStdNumFmt, Locale() );
        PropertySet aPropSet( getCell( rCellAddr ) );
        aPropSet.setProperty( PROP_NumberFormat, nIndex );
    }
    catch( Exception& )
    {
    }
}

void SheetDataBuffer::finalizeImport()
{
    // insert all cells of all open cell blocks
    maCellBlocks.finalizeImport();

    // create all array formulas
    for( ArrayFormulaList::iterator aIt = maArrayFormulas.begin(), aEnd = maArrayFormulas.end(); aIt != aEnd; ++aIt )
        finalizeArrayFormula( aIt->first, aIt->second );

    // create all table operations
    for( TableOperationList::iterator aIt = maTableOperations.begin(), aEnd = maTableOperations.end(); aIt != aEnd; ++aIt )
        finalizeTableOperation( aIt->first, aIt->second );

    // write default formatting of remaining row range
    writeXfIdRowRangeProperties( maXfIdRowRange );

    for( XfIdRangeListMap::const_iterator aIt = maXfIdRangeLists.begin(), aEnd = maXfIdRangeLists.end(); aIt != aEnd; ++aIt )
        writeXfIdRangeListProperties( aIt->first.first, aIt->first.second, aIt->second );

    // merge all cached merged ranges and update right/bottom cell borders
    for( MergedRangeList::iterator aIt = maMergedRanges.begin(), aEnd = maMergedRanges.end(); aIt != aEnd; ++aIt )
        finalizeMergedRange( aIt->maRange );
    for( MergedRangeList::iterator aIt = maCenterFillRanges.begin(), aEnd = maCenterFillRanges.end(); aIt != aEnd; ++aIt )
        finalizeMergedRange( aIt->maRange );
}

// private --------------------------------------------------------------------

SheetDataBuffer::XfIdRowRange::XfIdRowRange() :
    maRowRange( -1 ),
    mnXfId( -1 )
{
}

bool SheetDataBuffer::XfIdRowRange::intersects( const CellRangeAddress& rRange ) const
{
    return (rRange.StartRow <= maRowRange.mnLast) && (maRowRange.mnFirst <= rRange.EndRow);
}

void SheetDataBuffer::XfIdRowRange::set( sal_Int32 nRow, sal_Int32 nXfId )
{
    maRowRange = ValueRange( nRow );
    mnXfId = nXfId;
}

bool SheetDataBuffer::XfIdRowRange::tryExpand( sal_Int32 nRow, sal_Int32 nXfId )
{
    if( mnXfId == nXfId )
    {
        if( maRowRange.mnLast + 1 == nRow )
        {
            ++maRowRange.mnLast;
            return true;
        }
        if( maRowRange.mnFirst == nRow + 1 )
        {
            --maRowRange.mnFirst;
            return true;
        }
    }
    return false;
}

void SheetDataBuffer::XfIdRange::set( const CellAddress& rCellAddr, sal_Int32 nXfId, sal_Int32 nNumFmtId )
{
    maRange.Sheet = rCellAddr.Sheet;
    maRange.StartColumn = maRange.EndColumn = rCellAddr.Column;
    maRange.StartRow = maRange.EndRow = rCellAddr.Row;
    mnXfId = nXfId;
    mnNumFmtId = nNumFmtId;
}

bool SheetDataBuffer::XfIdRange::tryExpand( const CellAddress& rCellAddr, sal_Int32 nXfId, sal_Int32 nNumFmtId )
{
    if( (mnXfId == nXfId) && (mnNumFmtId == nNumFmtId) &&
        (maRange.StartRow == rCellAddr.Row) &&
        (maRange.EndRow == rCellAddr.Row) &&
        (maRange.EndColumn + 1 == rCellAddr.Column) )
    {
        ++maRange.EndColumn;
        return true;
    }
    return false;
}

bool SheetDataBuffer::XfIdRange::tryMerge( const XfIdRange& rXfIdRange )
{
    if( (mnXfId == rXfIdRange.mnXfId) &&
        (mnNumFmtId == rXfIdRange.mnNumFmtId) &&
        (maRange.EndRow + 1 == rXfIdRange.maRange.StartRow) &&
        (maRange.StartColumn == rXfIdRange.maRange.StartColumn) &&
        (maRange.EndColumn == rXfIdRange.maRange.EndColumn) )
    {
        maRange.EndRow = rXfIdRange.maRange.EndRow;
        return true;
    }
    return false;
}


SheetDataBuffer::MergedRange::MergedRange( const CellRangeAddress& rRange ) :
    maRange( rRange ),
    mnHorAlign( XML_TOKEN_INVALID )
{
}

SheetDataBuffer::MergedRange::MergedRange( const CellAddress& rAddress, sal_Int32 nHorAlign ) :
    maRange( rAddress.Sheet, rAddress.Column, rAddress.Row, rAddress.Column, rAddress.Row ),
    mnHorAlign( nHorAlign )
{
}

bool SheetDataBuffer::MergedRange::tryExpand( const CellAddress& rAddress, sal_Int32 nHorAlign )
{
    if( (mnHorAlign == nHorAlign) && (maRange.StartRow == rAddress.Row) &&
        (maRange.EndRow == rAddress.Row) && (maRange.EndColumn + 1 == rAddress.Column) )
    {
        ++maRange.EndColumn;
        return true;
    }
    return false;
}

// ----------------------------------------------------------------------------

void SheetDataBuffer::setCellFormula( const CellAddress& rCellAddr, const ApiTokenSequence& rTokens )
{
    if( rTokens.hasElements() )
    {
        if( CellBlock* pCellBlock = maCellBlocks.getCellBlock( rCellAddr ) )
            pCellBlock->getCellAny( rCellAddr.Column ) <<= rTokens;
        else
            putFormulaTokens( rCellAddr, rTokens );
    }
}

void SheetDataBuffer::createSharedFormula( const BinAddress& rMapKey, const ApiTokenSequence& rTokens )
{
    // create the defined name that will represent the shared formula
    OUString aName = OUStringBuffer().appendAscii( RTL_CONSTASCII_STRINGPARAM( "__shared_" ) ).
        append( static_cast< sal_Int32 >( getSheetIndex() + 1 ) ).
        append( sal_Unicode( '_' ) ).append( rMapKey.mnRow ).
        append( sal_Unicode( '_' ) ).append( rMapKey.mnCol ).makeStringAndClear();
    Reference< XNamedRange > xNamedRange = createNamedRangeObject( aName );
    OSL_ENSURE( xNamedRange.is(), "SheetDataBuffer::createSharedFormula - cannot create shared formula" );
    PropertySet aNameProps( xNamedRange );
    aNameProps.setProperty( PROP_IsSharedFormula, true );

    // get and store the token index of the defined name
    OSL_ENSURE( maSharedFormulas.count( rMapKey ) == 0, "SheetDataBuffer::createSharedFormula - shared formula exists already" );
    sal_Int32 nTokenIndex = 0;
    if( aNameProps.getProperty( nTokenIndex, PROP_TokenIndex ) && (nTokenIndex >= 0) ) try
    {
        // store the token index in the map
        maSharedFormulas[ rMapKey ] = nTokenIndex;
        // set the formula definition
        Reference< XFormulaTokens > xTokens( xNamedRange, UNO_QUERY_THROW );
        xTokens->setTokens( rTokens );
        // retry to insert a pending shared formula cell
        if( mbPendingSharedFmla )
            setCellFormula( maSharedFmlaAddr, resolveSharedFormula( maSharedBaseAddr ) );
    }
    catch( Exception& )
    {
    }
    mbPendingSharedFmla = false;
}

ApiTokenSequence SheetDataBuffer::resolveSharedFormula( const BinAddress& rMapKey ) const
{
    sal_Int32 nTokenIndex = ContainerHelper::getMapElement( maSharedFormulas, rMapKey, -1 );
    return (nTokenIndex >= 0) ? getFormulaParser().convertNameToFormula( nTokenIndex ) : ApiTokenSequence();
}

void SheetDataBuffer::finalizeArrayFormula( const CellRangeAddress& rRange, const ApiTokenSequence& rTokens ) const
{
    Reference< XArrayFormulaTokens > xTokens( getCellRange( rRange ), UNO_QUERY );
    OSL_ENSURE( xTokens.is(), "SheetDataBuffer::finalizeArrayFormula - missing formula token interface" );
    if( xTokens.is() )
        xTokens->setArrayTokens( rTokens );
}

void SheetDataBuffer::finalizeTableOperation( const CellRangeAddress& rRange, const DataTableModel& rModel ) const
{
    sal_Int16 nSheet = getSheetIndex();
    bool bOk = false;
    if( !rModel.mbRef1Deleted && (rModel.maRef1.getLength() > 0) && (rRange.StartColumn > 0) && (rRange.StartRow > 0) )
    {
        CellRangeAddress aOpRange = rRange;
        CellAddress aRef1;
        if( getAddressConverter().convertToCellAddress( aRef1, rModel.maRef1, nSheet, true ) ) try
        {
            if( rModel.mb2dTable )
            {
                CellAddress aRef2;
                if( !rModel.mbRef2Deleted && getAddressConverter().convertToCellAddress( aRef2, rModel.maRef2, nSheet, true ) )
                {
                    // API call expects input values inside operation range
                    --aOpRange.StartColumn;
                    --aOpRange.StartRow;
                    // formula range is top-left cell of operation range
                    CellRangeAddress aFormulaRange( nSheet, aOpRange.StartColumn, aOpRange.StartRow, aOpRange.StartColumn, aOpRange.StartRow );
                    // set multiple operation
                    Reference< XMultipleOperation > xMultOp( getCellRange( aOpRange ), UNO_QUERY_THROW );
                    xMultOp->setTableOperation( aFormulaRange, TableOperationMode_BOTH, aRef2, aRef1 );
                    bOk = true;
                }
            }
            else if( rModel.mbRowTable )
            {
                // formula range is column to the left of operation range
                CellRangeAddress aFormulaRange( nSheet, aOpRange.StartColumn - 1, aOpRange.StartRow, aOpRange.StartColumn - 1, aOpRange.EndRow );
                // API call expects input values (top row) inside operation range
                --aOpRange.StartRow;
                // set multiple operation
                Reference< XMultipleOperation > xMultOp( getCellRange( aOpRange ), UNO_QUERY_THROW );
                xMultOp->setTableOperation( aFormulaRange, TableOperationMode_ROW, aRef1, aRef1 );
                bOk = true;
            }
            else
            {
                // formula range is row above operation range
                CellRangeAddress aFormulaRange( nSheet, aOpRange.StartColumn, aOpRange.StartRow - 1, aOpRange.EndColumn, aOpRange.StartRow - 1 );
                // API call expects input values (left column) inside operation range
                --aOpRange.StartColumn;
                // set multiple operation
                Reference< XMultipleOperation > xMultOp( getCellRange( aOpRange ), UNO_QUERY_THROW );
                xMultOp->setTableOperation( aFormulaRange, TableOperationMode_COLUMN, aRef1, aRef1 );
                bOk = true;
            }
        }
        catch( Exception& )
        {
        }
    }

    // on error: fill cell range with #REF! error codes
    if( !bOk ) try
    {
        Reference< XCellRangeData > xCellRangeData( getCellRange( rRange ), UNO_QUERY_THROW );
        size_t nWidth = static_cast< size_t >( rRange.EndColumn - rRange.StartColumn + 1 );
        size_t nHeight = static_cast< size_t >( rRange.EndRow - rRange.StartRow + 1 );
        Matrix< Any > aErrorCells( nWidth, nHeight, Any( getFormulaParser().convertErrorToFormula( BIFF_ERR_REF ) ) );
        xCellRangeData->setDataArray( ContainerHelper::matrixToSequenceSequence( aErrorCells ) );
    }
    catch( Exception& )
    {
    }
}

void SheetDataBuffer::setCellFormat( const CellModel& rModel, sal_Int32 nNumFmtId )
{
    if( (rModel.mnXfId >= 0) || (nNumFmtId >= 0) )
    {
        ApiCellRangeList::reverse_iterator aIt = maXfIdRangeLists[ XfIdNumFmtKey( rModel.mnXfId, nNumFmtId ) ].rbegin();
        ApiCellRangeList::reverse_iterator aItEnd = maXfIdRangeLists[ XfIdNumFmtKey( rModel.mnXfId, nNumFmtId ) ].rend();
        /* The xlsx sheet data contains row wise information.
         * It is sufficient to check if the row range size is one
         */
        if(     aIt                 != aItEnd &&
                aIt->Sheet          == rModel.maCellAddr.Sheet &&
                aIt->StartRow       == aIt->EndRow &&
                aIt->StartRow       == rModel.maCellAddr.Row &&
                (aIt->EndColumn+1)  == rModel.maCellAddr.Column )
        {
            aIt->EndColumn++;       // Expand Column
        }
        else
        {
            maXfIdRangeLists[ XfIdNumFmtKey (rModel.mnXfId, nNumFmtId ) ].push_back(
                              CellRangeAddress( rModel.maCellAddr.Sheet, rModel.maCellAddr.Column, rModel.maCellAddr.Row,
                              rModel.maCellAddr.Column, rModel.maCellAddr.Row ) );
        }

        aIt = maXfIdRangeLists[ XfIdNumFmtKey( rModel.mnXfId, nNumFmtId ) ].rbegin();
        aItEnd = maXfIdRangeLists[ XfIdNumFmtKey( rModel.mnXfId, nNumFmtId ) ].rend();
        ApiCellRangeList::reverse_iterator aItM = aIt+1;
        while( aItM != aItEnd )
        {
            if( aIt->Sheet == aItM->Sheet )
            {
                /* Try to merge this with the previous range */
                if( aIt->StartRow == (aItM->EndRow + 1) &&
                        aIt->StartColumn == aItM->StartColumn &&
                        aIt->EndColumn == aItM->EndColumn)
                {
                    aItM->EndRow = aIt->EndRow;
                    maXfIdRangeLists[ XfIdNumFmtKey( rModel.mnXfId, nNumFmtId ) ].pop_back();
                    break;
                }
                else if( aIt->StartRow > aItM->EndRow + 1 )
                    break; // Un-necessary to check with any other rows
            }
            else
                break;
            ++aItM;
        }

        // update merged ranges for 'center across selection' and 'fill'
        if( const Xf* pXf = getStyles().getCellXf( rModel.mnXfId ).get() )
        {
            sal_Int32 nHorAlign = pXf->getAlignment().getModel().mnHorAlign;
            if( (nHorAlign == XML_centerContinuous) || (nHorAlign == XML_fill) )
            {
                /*  start new merged range, if cell is not empty (#108781#),
                    or try to expand last range with empty cell */
                if( rModel.mnCellType != XML_TOKEN_INVALID )
                    maCenterFillRanges.push_back( MergedRange( rModel.maCellAddr, nHorAlign ) );
                else if( !maCenterFillRanges.empty() )
                    maCenterFillRanges.rbegin()->tryExpand( rModel.maCellAddr, nHorAlign );
            }
        }
    }
}

void SheetDataBuffer::writeXfIdRowRangeProperties( const XfIdRowRange& rXfIdRowRange ) const
{
    if( (rXfIdRowRange.maRowRange.mnLast >= 0) && (rXfIdRowRange.mnXfId >= 0) )
    {
        AddressConverter& rAddrConv = getAddressConverter();
        CellRangeAddress aRange( getSheetIndex(), 0, rXfIdRowRange.maRowRange.mnFirst, rAddrConv.getMaxApiAddress().Column, rXfIdRowRange.maRowRange.mnLast );
        if( rAddrConv.validateCellRange( aRange, true, false ) )
        {
            PropertySet aPropSet( getCellRange( aRange ) );
            getStyles().writeCellXfToPropertySet( aPropSet, rXfIdRowRange.mnXfId );
        }
    }
}

void SheetDataBuffer::writeXfIdRangeListProperties( sal_Int32 nXfId, sal_Int32 nNumFmtId, const ApiCellRangeList& rRanges ) const
{
    StylesBuffer& rStyles = getStyles();
    PropertyMap aPropMap;
    if( nXfId >= 0 )
        rStyles.writeCellXfToPropertyMap( aPropMap, nXfId );
    if( nNumFmtId >= 0 )
        rStyles.writeNumFmtToPropertyMap( aPropMap, nNumFmtId );
    PropertySet aPropSet( getCellRangeList( rRanges ) );
    aPropSet.setProperties( aPropMap );
}

void SheetDataBuffer::finalizeMergedRange( const CellRangeAddress& rRange )
{
    bool bMultiCol = rRange.StartColumn < rRange.EndColumn;
    bool bMultiRow = rRange.StartRow < rRange.EndRow;

    if( bMultiCol || bMultiRow ) try
    {
        // merge the cell range
        Reference< XMergeable > xMerge( getCellRange( rRange ), UNO_QUERY_THROW );
        xMerge->merge( sal_True );

        // if merging this range worked (no overlapping merged ranges), update cell borders
        Reference< XCell > xTopLeft( getCell( CellAddress( getSheetIndex(), rRange.StartColumn, rRange.StartRow ) ), UNO_SET_THROW );
        PropertySet aTopLeftProp( xTopLeft );

        // copy right border of top-right cell to right border of top-left cell
        if( bMultiCol )
        {
            PropertySet aTopRightProp( getCell( CellAddress( getSheetIndex(), rRange.EndColumn, rRange.StartRow ) ) );
            BorderLine aLine;
            if( aTopRightProp.getProperty( aLine, PROP_RightBorder ) )
                aTopLeftProp.setProperty( PROP_RightBorder, aLine );
        }

        // copy bottom border of bottom-left cell to bottom border of top-left cell
        if( bMultiRow )
        {
            PropertySet aBottomLeftProp( getCell( CellAddress( getSheetIndex(), rRange.StartColumn, rRange.EndRow ) ) );
            BorderLine aLine;
            if( aBottomLeftProp.getProperty( aLine, PROP_BottomBorder ) )
                aTopLeftProp.setProperty( PROP_BottomBorder, aLine );
        }

        // #i93609# merged range in a single row: test if manual row height is needed
        if( !bMultiRow )
        {
            bool bTextWrap = aTopLeftProp.getBoolProperty( PROP_IsTextWrapped );
            if( !bTextWrap && (xTopLeft->getType() == CellContentType_TEXT) )
            {
                Reference< XText > xText( xTopLeft, UNO_QUERY );
                bTextWrap = xText.is() && (xText->getString().indexOf( '\x0A' ) >= 0);
            }
            if( bTextWrap )
                setManualRowHeight( rRange.StartRow );
        }
    }
    catch( Exception& )
    {
    }
}

// ============================================================================

} // namespace xls
} // namespace oox
