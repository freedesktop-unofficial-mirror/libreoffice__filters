/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: csvcontrol.hxx,v $
 *
 *  $Revision: 1.3 $
 *
 *  last change: $Author: rt $ $Date: 2005-09-07 19:39:09 $
 *
 *  The Contents of this file are made available subject to
 *  the terms of GNU Lesser General Public License Version 2.1.
 *
 *
 *    GNU Lesser General Public License Version 2.1
 *    =============================================
 *    Copyright 2005 by Sun Microsystems, Inc.
 *    901 San Antonio Road, Palo Alto, CA 94303, USA
 *
 *    This library is free software; you can redistribute it and/or
 *    modify it under the terms of the GNU Lesser General Public
 *    License version 2.1, as published by the Free Software Foundation.
 *
 *    This library is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *    Lesser General Public License for more details.
 *
 *    You should have received a copy of the GNU Lesser General Public
 *    License along with this library; if not, write to the Free Software
 *    Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 *    MA  02111-1307  USA
 *
 ************************************************************************/

// ============================================================================

#ifndef _SC_CSVCONTROL_HXX
#define _SC_CSVCONTROL_HXX

#ifndef _SV_CTRL_HXX
#include <vcl/ctrl.hxx>
#endif

#ifndef SC_SCGLOB_HXX
#include "global.hxx"
#endif
#ifndef _SC_CSVSPLITS_HXX
#include "csvsplits.hxx"
#endif

#ifndef _COM_SUN_STAR_UNO_REFERENCE_HXX_
#include <com/sun/star/uno/Reference.hxx>
#endif
namespace binfilter {


class ScAccessibleCsvControl;
} //namespace binfilter
namespace com { namespace sun { namespace star { namespace accessibility {
    class XAccessible;
} } } }
namespace binfilter {//STRIP009

// ============================================================================

/** Minimum character count for a column in separators mode. */
const sal_Int32 CSV_MINCOLWIDTH         = 8;
/** Maximum length of a cell string. */
const xub_StrLen CSV_MAXSTRLEN          = 0x7FFF;
/** Transparency for header color of selected columns. */
const sal_uInt16 CSV_HDR_TRANSPARENCY   = 85;
/** Minimum distance to border for auto scroll. */
const sal_Int32 CSV_SCROLL_DIST         = 3;

//! TODO make string array dynamic
const sal_Int32 CSV_PREVIEW_LINES       = 32; // maximum count of preview lines
/** Maximum count of columns. */
const sal_Int32 CSV_MAXCOLCOUNT         = MAXCOL + 1;

/** Default column data type. */
const sal_Int32 CSV_TYPE_DEFAULT        = 0;
/** Multi selection with different types. */
const sal_Int32 CSV_TYPE_MULTI          = -1;
/** No column selected. */
const sal_Int32 CSV_TYPE_NOSELECTION    = -2;

// External used column types.
const sal_uInt8 SC_COL_STANDARD         = 1;
const sal_uInt8 SC_COL_TEXT             = 2;
const sal_uInt8 SC_COL_MDY              = 3;
const sal_uInt8 SC_COL_DMY              = 4;
const sal_uInt8 SC_COL_YMD              = 5;
const sal_uInt8 SC_COL_SKIP             = 9;
const sal_uInt8 SC_COL_ENGLISH          = 10;


// ============================================================================

/** Exported data of a column (data used in the dialog). */
struct ScCsvExpData
{
    xub_StrLen                  mnIndex;        /// Index of a column.
    sal_uInt8                   mnType;         /// External type of the column.

    inline                      ScCsvExpData() : mnIndex( 0 ), mnType( SC_COL_STANDARD ) {}
    inline                      ScCsvExpData( xub_StrLen nIndex, sal_uInt8 nType ) :
                                    mnIndex( nIndex ), mnType( nType ) {}
};

typedef ::std::vector< ScCsvExpData > ScCsvExpDataVec;


// ============================================================================

/** Specifies which element should be used to perform an action. */
enum ScMoveMode
{
    MOVE_NONE,                  /// No action.
    MOVE_FIRST,                 /// First element in current context.
    MOVE_LAST,                  /// Last element in current context.
    MOVE_PREV,                  /// Predecessor of current element in current context.
    MOVE_NEXT,                  /// Successor of current element in current context.
    MOVE_PREVPAGE,              /// Previous page relative to current context.
    MOVE_NEXTPAGE               /// Next page relative to current context.
};


// ============================================================================

/** Flags for comparison of old and new control layout data. */
typedef sal_uInt32 ScCsvDiff;

const ScCsvDiff CSV_DIFF_EQUAL          = 0x00000000;
const ScCsvDiff CSV_DIFF_POSCOUNT       = 0x00000001;
const ScCsvDiff CSV_DIFF_POSOFFSET      = 0x00000002;
const ScCsvDiff CSV_DIFF_HDRWIDTH       = 0x00000004;
const ScCsvDiff CSV_DIFF_CHARWIDTH      = 0x00000008;
const ScCsvDiff CSV_DIFF_LINECOUNT      = 0x00000010;
const ScCsvDiff CSV_DIFF_LINEOFFSET     = 0x00000020;
const ScCsvDiff CSV_DIFF_HDRHEIGHT      = 0x00000040;
const ScCsvDiff CSV_DIFF_LINEHEIGHT     = 0x00000080;
const ScCsvDiff CSV_DIFF_RULERCURSOR    = 0x00000100;
const ScCsvDiff CSV_DIFF_GRIDCURSOR     = 0x00000200;

const ScCsvDiff CSV_DIFF_HORIZONTAL     = CSV_DIFF_POSCOUNT | CSV_DIFF_POSOFFSET | CSV_DIFF_HDRWIDTH | CSV_DIFF_CHARWIDTH;
const ScCsvDiff CSV_DIFF_VERTICAL       = CSV_DIFF_LINECOUNT | CSV_DIFF_LINEOFFSET | CSV_DIFF_HDRHEIGHT | CSV_DIFF_LINEHEIGHT;
const ScCsvDiff CSV_DIFF_CURSOR         = CSV_DIFF_RULERCURSOR | CSV_DIFF_GRIDCURSOR;


// ----------------------------------------------------------------------------

/** A structure containing all layout data valid for both ruler and data grid
    (i.e. scroll position or column width). */
struct ScCsvLayoutData
{
    // horizontal settings
    sal_Int32                   mnPosCount;         /// Number of positions.
    sal_Int32                   mnPosOffset;        /// Horizontal scroll offset.

    sal_Int32                   mnWinWidth;         /// Width of ruler and data grid.
    sal_Int32                   mnHdrWidth;         /// Width of the header column.
    sal_Int32                   mnCharWidth;        /// Pixel width of one character.

    // vertical settings
    sal_Int32                   mnLineCount;        /// Number of data lines.
    sal_Int32                   mnLineOffset;       /// Index of first visible line (0-based).

    sal_Int32                   mnWinHeight;        /// Height of entire data grid (incl. header).
    sal_Int32                   mnHdrHeight;        /// Height of the header line.
    sal_Int32                   mnLineHeight;       /// Height of a data line.

    // cursor settings
    sal_Int32                   mnPosCursor;        /// Position of ruler cursor.
    sal_Int32                   mnColCursor;        /// Position of grid column cursor.

    mutable sal_Int32           mnNoRepaint;        /// >0 = no repaint.
    bool                        mbAppRTL;           /// true = application in RTL mode.

    explicit                    ScCsvLayoutData();

//STRIP001     /** Returns differences to rData.
//STRIP001         @descr  For each difference the appropriate bit is set in the returned value. */
//STRIP001     ScCsvDiff                   GetDiff( const ScCsvLayoutData& rData ) const;
};

//STRIP001 inline bool operator==( const ScCsvLayoutData& rData1, const ScCsvLayoutData& rData2 )
//STRIP001 {
//STRIP001     return rData1.GetDiff( rData2 ) == CSV_DIFF_EQUAL;
//STRIP001 }

//STRIP001 inline bool operator!=( const ScCsvLayoutData& rData1, const ScCsvLayoutData& rData2 )
//STRIP001 {
//STRIP001     return !(rData1 == rData2);
//STRIP001 }


// ============================================================================

/** Enumeration of possible commands to change any settings of the CSV controls.
    @descr  Controls have to send commands instead of changing their settings directly.
    This helps to keep the different controls consistent to each other.
    A command can contain 0 to 2 sal_Int32 parameters. In the description of each
    command the required parameters are swown in brackets. [-] means no parameter. */
enum ScCsvCmdType
{
    // misc
    CSVCMD_NONE,                /// No command. [-]
    CSVCMD_REPAINT,             /// Repaint all controls. [-]

    // modify horizontal dimensions
    CSVCMD_SETPOSCOUNT,         /// Change position/column count. [character count]
    CSVCMD_SETPOSOFFSET,        /// Change position offset (scroll pos). [position]
    CSVCMD_SETHDRWIDTH,         /// Change width of the header column. [width in pixel]
    CSVCMD_SETCHARWIDTH,        /// Change character pixel width. [width in pixel]

    // modify vertical dimensions
    CSVCMD_SETLINECOUNT,        /// Change number of data lines. [line count]
    CSVCMD_SETLINEOFFSET,       /// Change first visible line. [line index]
    CSVCMD_SETHDRHEIGHT,        /// Change height of top header line. [height in pixel]
    CSVCMD_SETLINEHEIGHT,       /// Change data line pixel height. [height in pixel}

    // cursors/positions
    CSVCMD_MOVERULERCURSOR,     /// Move ruler cursor to new position. [position]
    CSVCMD_MOVEGRIDCURSOR,      /// Move data grid cursor to new column. [position]
    CSVCMD_MAKEPOSVISIBLE,      /// Move to make passed position visible (for mouse tracking). [position]

    // table contents
    CSVCMD_NEWCELLTEXTS,        /// Recalculate splits and cell texts. [-]
    CSVCMD_UPDATECELLTEXTS,     /// Update cell texts with current split settings. [-]
    CSVCMD_SETCOLUMNTYPE,       /// Change data type of selected columns. [column type]
    CSVCMD_EXPORTCOLUMNTYPE,    /// Send selected column type to external controls. [-]
    CSVCMD_SETFIRSTIMPORTLINE,  /// Set number of first imported line. [line index]

    // splits
    CSVCMD_INSERTSPLIT,         /// Insert a split. [position]
    CSVCMD_REMOVESPLIT,         /// Remove a split. [position]
    CSVCMD_TOGGLESPLIT,         /// Inserts or removes a split. [position]
    CSVCMD_MOVESPLIT,           /// Move a split. [old position, new position]
    CSVCMD_REMOVEALLSPLITS      /// Remove all splits. [-]
};


// ----------------------------------------------------------------------------

/** Data for a CSV control command. The stored position data is aways character based,
    it's never a column index (required for internal consistency). */
class ScCsvCmd
{
private:
    ScCsvCmdType                meType;         /// The command.
    sal_Int32                   mnParam1;       /// First parameter.
    sal_Int32                   mnParam2;       /// Second parameter.

public:
    inline explicit             ScCsvCmd() : meType( CSVCMD_NONE ),
                                    mnParam1( CSV_POS_INVALID ), mnParam2( CSV_POS_INVALID ) {}

    inline void                 Set( ScCsvCmdType eType, sal_Int32 nParam1, sal_Int32 nParam2 );

    inline ScCsvCmdType         GetType() const     { return meType; }
    inline sal_Int32            GetParam1() const   { return mnParam1; }
    inline sal_Int32            GetParam2() const   { return mnParam2; }
};

inline void ScCsvCmd::Set( ScCsvCmdType eType, sal_Int32 nParam1, sal_Int32 nParam2 )
{
    meType = eType; mnParam1 = nParam1; mnParam2 = nParam2;
}


// ============================================================================

/** Base class for the CSV ruler and the data grid control. Implements command handling. */
class ScCsvControl : public Control
{
protected:
    typedef ::std::vector< String >     StringVec;
    typedef ::std::vector< StringVec >  StringVecVec;

    typedef ::com::sun::star::uno::Reference<
        ::com::sun::star::accessibility::XAccessible > XAccessibleRef;

private:
    Link                        maCmdHdl;           /// External command handler.
    ScCsvCmd                    maCmd;              /// Data of last command.
    const ScCsvLayoutData&      mrData;             /// Shared layout data.

    XAccessibleRef              mxAccessible;       /// The accessible object of the control.
    ScAccessibleCsvControl*     mpAccessible;       /// Pointer to the accessible implementation object.
    bool                        mbValidGfx;         /// Content of virtual devices valid?

    // ------------------------------------------------------------------------
public:
    explicit                    ScCsvControl( ScCsvControl& rParent );
    explicit                    ScCsvControl( Window* pParent, const ScCsvLayoutData& rData, WinBits nStyle = 0 );
    explicit                    ScCsvControl( Window* pParent, const ScCsvLayoutData& rData, const ResId& rResId );
    virtual                     ~ScCsvControl();

    // event handling ---------------------------------------------------------

    virtual void                GetFocus();
    virtual void                LoseFocus();

    /** Sends a GetFocus or LoseFocus event to the accessibility object. */
    void                        AccSendFocusEvent( bool bFocused );
    /** Sends a caret changed event to the accessibility object. */
    void                        AccSendCaretEvent();
    /** Sends a visible area changed event to the accessibility object. */
    void                        AccSendVisibleEvent();
    /** Sends a selection changed event to the accessibility object. */
    void                        AccSendSelectionEvent();
    /** Sends a table model changed event for changed cell contents to the accessibility object. */
    void                        AccSendTableUpdateEvent( sal_uInt32 nFirstColumn, sal_uInt32 nLastColumn, bool bAllRows = true );
    /** Sends a table model changed event for an inserted column to the accessibility object. */
    void                        AccSendInsertColumnEvent( sal_uInt32 nFirstColumn, sal_uInt32 nLastColumn );
    /** Sends a table model changed event for a removed column to the accessibility object. */
    void                        AccSendRemoveColumnEvent( sal_uInt32 nFirstColumn, sal_uInt32 nLastColumn );

    // repaint helpers --------------------------------------------------------

//STRIP001     /** Sets the graphic invalid (next Redraw() will not use cached graphic). */
//STRIP001     inline void                 InvalidateGfx() { mbValidGfx = false; }
//STRIP001     /** Sets the graphic valid (next Redraw() will use cached graphic). */
//STRIP001     inline void                 ValidateGfx() { mbValidGfx = true; }
//STRIP001     /** Returns true, if cached graphic is valid. */
//STRIP001     inline bool                 IsValidGfx() const { return mbValidGfx; }
//STRIP001 
//STRIP001     /** Repaints all controls.
//STRIP001         @param bInvalidate  true = invalidates graphics of this control (not all). */
//STRIP001     void                        Repaint( bool bInvalidate = false );
//STRIP001     /** Increases no-repaint counter (controls do not repaint until the last EnableRepaint()). */
//STRIP001     void                        DisableRepaint();
//STRIP001     /** Decreases no-repaint counter and repaints if counter reaches 0.
//STRIP001         @param bInvalidate  true = invalidates graphics of this control (not all). */
//STRIP001     void                        EnableRepaint( bool bInvalidate = false );
//STRIP001     /** Returns true, if controls will not repaint. */
//STRIP001     inline bool                 IsNoRepaint() const { return mrData.mnNoRepaint > 0; }

    // command handling -------------------------------------------------------

    /** Sets a new command handler. */
    inline void                 SetCmdHdl( const Link& rHdl ) { maCmdHdl = rHdl; }
    /** Returns the current command handler. */
    inline const Link&          GetCmdHdl() const { return maCmdHdl; }
    /** Returns data of the last command. */
    inline const ScCsvCmd&      GetCmd() const { return maCmd; }

    /** Executes a command by calling command handler. */
    void                        Execute(
                                    ScCsvCmdType eType,
                                    sal_Int32 nParam1 = CSV_POS_INVALID,
                                    sal_Int32 nParam2 = CSV_POS_INVALID );

    // layout helpers ---------------------------------------------------------

    /** Returns a reference to the current layout data. */
    inline const ScCsvLayoutData& GetLayoutData() const { return mrData; }
    /** Returns true, if the Right-to-Left layout mode is active. */
    inline bool                 IsRTL() const { return mrData.mbAppRTL; }

//STRIP001     /** Returns the number of available positions. */
//STRIP001     inline sal_Int32            GetPosCount() const { return mrData.mnPosCount; }
//STRIP001     /** Returns the number of visible positions. */
//STRIP001     sal_Int32                   GetVisPosCount() const;
//STRIP001     /** Returns the first visible position. */
//STRIP001     inline sal_Int32            GetFirstVisPos() const { return mrData.mnPosOffset; }
//STRIP001     /** Returns the last visible position. */
//STRIP001     inline sal_Int32            GetLastVisPos() const { return GetFirstVisPos() + GetVisPosCount(); }
//STRIP001     /** Returns highest possible position for first visible character. */
//STRIP001     sal_Int32                   GetMaxPosOffset() const;
//STRIP001 
//STRIP001     /** Returns true, if it is allowed to set a split at nPos. */
//STRIP001     bool                        IsValidSplitPos( sal_Int32 nPos ) const;
//STRIP001     /** Returns true, if nPos is an allowed AND visible split position. */
//STRIP001     bool                        IsVisibleSplitPos( sal_Int32 nPos ) const;
//STRIP001 
//STRIP001     /** Returns the width of the header column. */
//STRIP001     inline sal_Int32            GetHdrWidth() const { return mrData.mnHdrWidth; }
//STRIP001     /** Returns the width of one character column. */
//STRIP001     inline sal_Int32            GetCharWidth() const { return mrData.mnCharWidth; }
//STRIP001     /** Returns the start position of the header column. */
//STRIP001     sal_Int32                   GetHdrX() const;
//STRIP001     /** Returns the X position of the first pixel of the data area. */
//STRIP001     sal_Int32                   GetFirstX() const;
//STRIP001     /** Returns the X position of the last pixel of the data area. */
//STRIP001     sal_Int32                   GetLastX() const;
//STRIP001     /** Returns output X coordinate of the specified position. */
//STRIP001     sal_Int32                   GetX( sal_Int32 nPos ) const;
//STRIP001     /** Returns position from output coordinate. */
//STRIP001     sal_Int32                   GetPosFromX( sal_Int32 nX ) const;
//STRIP001 
//STRIP001     /** Returns the number of data lines. */
//STRIP001     inline sal_Int32            GetLineCount() const { return mrData.mnLineCount; }
//STRIP001     /** Returns the number of visible lines (including partly visible bottom line). */
//STRIP001     sal_Int32                   GetVisLineCount() const;
//STRIP001     /** Returns index of first visible line. */
//STRIP001     inline sal_Int32            GetFirstVisLine() const { return mrData.mnLineOffset; }
//STRIP001     /** Returns index of last visible line. */
//STRIP001     sal_Int32                   GetLastVisLine() const;
//STRIP001     /** Returns highest possible index for first line. */
//STRIP001     sal_Int32                   GetMaxLineOffset() const;
//STRIP001 
//STRIP001     /** Returns true, if nLine is a valid line index. */
//STRIP001     bool                        IsValidLine( sal_Int32 nLine ) const;
//STRIP001     /** Returns true, if nLine is a valid and visible line index. */
//STRIP001     bool                        IsVisibleLine( sal_Int32 nLine ) const;
//STRIP001 
//STRIP001     /** Returns the height of the header line. */
//STRIP001     inline sal_Int32            GetHdrHeight() const { return mrData.mnHdrHeight; }
//STRIP001     /** Returns the height of one line. */
//STRIP001     inline sal_Int32            GetLineHeight() const { return mrData.mnLineHeight; }
//STRIP001     /** Returns output Y coordinate of the specified line. */
//STRIP001     sal_Int32                   GetY( sal_Int32 nLine ) const;
//STRIP001     /** Returns line index from output coordinate. */
//STRIP001     sal_Int32                   GetLineFromY( sal_Int32 nY ) const;
//STRIP001 
//STRIP001     /** Returns the ruler cursor position. */
//STRIP001     inline sal_Int32            GetRulerCursorPos() const { return mrData.mnPosCursor; }
//STRIP001     /** Returns the data grid cursor position (not column index!). */
//STRIP001     inline sal_Int32            GetGridCursorPos() const { return mrData.mnColCursor; }

    // static helpers ---------------------------------------------------------

//STRIP001     /** Inverts a rectangle in the specified output device. */
//STRIP001     static void                 ImplInvertRect( OutputDevice& rOutDev, const Rectangle& rRect );

//STRIP001     /** Returns direction code for the keys LEFT, RIGHT, HOME, END.
//STRIP001         @param bHomeEnd  false = ignore HOME and END key. */
//STRIP001     static ScMoveMode           GetHorzDirection( sal_uInt16 nCode, bool bHomeEnd );
//STRIP001     /** Returns direction code for the keys UP, DOWN, HOME, END, PAGE UP, PAGE DOWN.
//STRIP001         @param bHomeEnd  false = ignore HOME and END key. */
//STRIP001     static ScMoveMode           GetVertDirection( sal_uInt16 nCode, bool bHomeEnd );

    // accessibility ----------------------------------------------------------
//STRIP001 public:
//STRIP001     /** Creates and returns the accessible object of this control. Do not overwrite in
//STRIP001         derived classes, use ImplCreateAccessible() instead. */
//STRIP001     virtual XAccessibleRef     CreateAccessible();
//STRIP001 
//STRIP001 protected:
//STRIP001     /** Derived classes create a new accessible object here. */
//STRIP001     virtual ScAccessibleCsvControl* ImplCreateAccessible() = NULL;
};


// ============================================================================

} //namespace binfilter
#endif

