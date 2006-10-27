/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: gridwin.hxx,v $
 *
 *  $Revision: 1.4 $
 *
 *  last change: $Author: rt $ $Date: 2006-10-27 16:12:01 $
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

#ifndef SC_GRIDWIN_HXX
#define SC_GRIDWIN_HXX

#ifndef _STRING_HXX //autogen
#include <tools/string.hxx>
#endif

#ifndef _TRANSFER_HXX
#include <svtools/transfer.hxx>
#endif

// nur auf dem MAC Auto-Filter per Popup
#ifdef MAC
#define AUTOFILTER_POPUP
#else
#undef AUTOFILTER_POPUP
#endif

#ifndef SC_VIEWUTIL_HXX
#include "viewutil.hxx"
#endif

#ifndef SC_VIEWDATA_HXX
#include "viewdata.hxx"
#endif

#ifndef SC_CBUTTON_HXX
#include "cbutton.hxx"
#endif
class FloatingWindow;
namespace binfilter {

// ---------------------------------------------------------------------------

struct RowInfo;
class ScViewSelectionEngine;
class ScPivot;
class ScDPObject;
class ScOutputData;
class ScFilterListBox;
class AutoFilterPopup;
class SdrObject;
class SdrEditView;
class ScNoteMarker;
class SdrHdlList;
class ScTransferObj;

        //	Maus-Status (nMouseStatus)

#define SC_GM_NONE			0
#define SC_GM_TABDOWN		1
#define SC_GM_DBLDOWN		2
#define SC_GM_FILTER		3
#define SC_GM_IGNORE		4
#define SC_GM_WATERUNDO		5
#define SC_GM_URLDOWN		6

        //	Page-Drag-Modus

#define SC_PD_NONE			0
#define SC_PD_RANGE_L		1
#define SC_PD_RANGE_R		2
#define SC_PD_RANGE_T		4
#define SC_PD_RANGE_B		8
#define SC_PD_RANGE_TL		(SC_PD_RANGE_T|SC_PD_RANGE_L)
#define SC_PD_RANGE_TR		(SC_PD_RANGE_T|SC_PD_RANGE_R)
#define SC_PD_RANGE_BL		(SC_PD_RANGE_B|SC_PD_RANGE_L)
#define SC_PD_RANGE_BR		(SC_PD_RANGE_B|SC_PD_RANGE_R)
#define SC_PD_BREAK_H		16
#define SC_PD_BREAK_V		32




class ScGridWindow : public Window, public DropTargetHelper, public DragSourceHelper
{
    //	ScFilterListBox wird immer fuer Auswahlliste benutzt
    friend class ScFilterListBox;
#ifdef AUTOFILTER_POPUP
    friend class AutoFilterPopup;
#endif

private:
    ScViewData*				pViewData;
    ScSplitPos				eWhich;
    ScHSplitPos				eHWhich;
    ScVSplitPos				eVWhich;

    ScNoteMarker*			pNoteMarker;

    ScFilterListBox*		pFilterBox;
    USHORT					nFilterBoxCol;
    USHORT					nFilterBoxRow;
    FloatingWindow*			pFilterFloat;

    USHORT					nCursorHideCount;

    BOOL					bMarking;

    USHORT					nButtonDown;
    BOOL					bEEMouse;				// Edit-Engine hat Maus
    BYTE					nMouseStatus;

    BOOL					bPivotMouse;			// Pivot-D&D (alte Pivottabellen)
    ScPivot*				pDragPivot;
    BOOL					bPivotColField;
    USHORT					nPivotCol;
    USHORT					nPivotField;

    BOOL					bDPMouse;				// DataPilot-D&D (neue Pivottabellen)
    long					nDPField;
    ScDPObject*				pDragDPObj;	//! name?

    BOOL					bRFMouse;				// RangeFinder-Drag
    BOOL					bRFSize;
    USHORT					nRFIndex;
    short					nRFAddX;
    short					nRFAddY;

    USHORT					nPagebreakMouse;		// Pagebreak-Modus Drag
    USHORT					nPagebreakBreak;
    USHORT					nPagebreakPrev;
    ScRange					aPagebreakSource;
    ScRange					aPagebreakDrag;
    BOOL					bPagebreakDrawn;

    BYTE					nPageScript;

    long					nLastClickX;
    long					nLastClickY;

    BOOL					bDragRect;
    USHORT					nDragStartX;
    USHORT					nDragStartY;
    USHORT					nDragEndX;
    USHORT					nDragEndY;

    USHORT					nCurrentPointer;

    BOOL					bIsInScroll;
    BOOL					bIsInPaint;

    ScDDComboBoxButton		aComboButton;

    Point					aCurMousePos;

    USHORT					nPaintCount;
    Rectangle				aRepaintPixel;
    BOOL					bNeedsRepaint;

    BOOL					bAutoMarkVisible;
    ScAddress				aAutoMarkPos;

    Rectangle				aInvertRect;













    void			DrawEndAction();
    SdrObject*		GetEditObject();
    void			DrawStartTimer();

    void			DrawRedraw( ScOutputData& rOutputData, const Rectangle& rDrawingRect,
                                        ScUpdateMode eMode, ULONG nLayer );
    void			DrawSdrGrid( const Rectangle& rDrawingRect );
    void			DrawMarks();
    BOOL			NeedDrawMarks();





#ifdef AUTOFILTER_POPUP
#endif


protected:



public:
    ScGridWindow( Window* pParent, ScViewData* pData, ScSplitPos eWhichPos );
    ~ScGridWindow();






    void			ClickExtern();




    void			UpdateFormulas();


    void			DrawButtons( USHORT nX1, USHORT nY1, USHORT nX2, USHORT nY2,
                                    RowInfo* pRowInfo, USHORT nArrCount );

    void			Draw( USHORT nX1, USHORT nY1, USHORT nX2, USHORT nY2,
                        ScUpdateMode eMode = SC_UPDATE_ALL );





    void			HideCursor();
    void			ShowCursor();
    void 			DrawCursor();
    void			DrawAutoFillMark();
     void			UpdateAutoFillMark(BOOL bMarked, const ScRange& rMarkRange);

    void			HideNoteMarker();

    MapMode			GetDrawMapMode( BOOL bForce = FALSE );

    void			ContinueDrag();

    void			StopMarking();

    void			CheckInverted()		{ if (nPaintCount) bNeedsRepaint = TRUE; }


    void			CheckNeedsRepaint();
};



} //namespace binfilter
#endif

