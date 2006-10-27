/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: fudraw.hxx,v $
 *
 *  $Revision: 1.4 $
 *
 *  last change: $Author: rt $ $Date: 2006-10-27 17:53:20 $
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

#ifndef _SCH_FUDRAW_HXX
#define _SCH_FUDRAW_HXX

#include "fupoor.hxx"
namespace binfilter {

/*************************************************************************
|*
|* Basisklasse fuer alle Drawmodul-spezifischen Funktionen
|*
\************************************************************************/

class SdrObject;

class SchFuDraw : public SchFuPoor
{
protected:
    Pointer aNewPointer;
    Pointer aOldPointer;
    BOOL	bMBDown;

    /** possible directions in which to select objects
     */
    enum lcl_Selection_Direction
    {
        lcl_SELECT_PREVIOUS,
        lcl_SELECT_NEXT,
        lcl_SELECT_FIRST,
        lcl_SELECT_LAST
    };

    /** possible directions in which to move an object
     */
    enum lcl_Movement_Direction
    {
        lcl_MOVE_LEFT,
        lcl_MOVE_RIGHT,
        lcl_MOVE_UP,
        lcl_MOVE_DOWN
    };

    /** marks the next/previous/first or last object in the current
        group of chart objects.

        @param eDirection determines in which direction to travel

        @param nDepth is to prevent a loop in recursion.  When
               selecting a new object, this may be invalid.  In this
               case the method tries the next object.  If the last
               object is reached without success, the first is
               selected using a recursive call.  If no valid objects
               are available at all this parameter avoids a loop
               (which should normally never occur).

        @param bEnterDiagram determines if during navigation the
               diagram should be ignored as group and its content
               rather be treated as top-level objects.  This parameter
               is especially needed so that the diagram can still be
               selected (without entering).

        @returns TRUE, if an object could be marked
     */

    /** moves an object in one of the four directions given in
        lcl_Movement_Direction.  This is only possible for top-level
        chart objects, i.e., titles, legend and diagram

        @param eDirection the direction in which to move.  If an
               object is too close to the edge, the object is not
               moved.

        @param nAmount the amount of units to be moved about.  The
               unit can be 100th of a mm or pixels depending on what
               bPixel is set to.

        @param bPixel If true, the amount nAmount is treated as pixels
               in the current window, otherwise the current logical
               unit is used, which in a chart is always 100th of a mm.

        @returns TRUE, if the object could be moved
     */

    /** resizes an object by the amount given into the larger of width
        and height.  In the smaller extent the amount is calculated
        such that the resize is proportional.

        @param nAmount the amount by which the object will be resized.
               The amount will be added to the larger extent (width or
               height).  The resize is proportional in the other
               direction.

        @param bPixel If true, the amount nAmount is treated as pixels
               in the current window for the larger of width and
               height.  Otherwise the current logical unit is used,
               which in a chart is always 100th of a mm.

        @returns TRUE, if the object could be resized
     */

    /** moves a pie segment by the given amount in percent

        @param bOut if true increases the offset, otherwise decreases
               the offset.  The offset stays always between 0 and 100.

        @param nAmount the amount of percent by which the pie segment
               is dragged.

        @returns TRUE, if the object was a pie and could be moved
     */

    /** determines if the object currently selected is valid, i.e. it
        may be selected in the UI for making changes.

        @returns true, if a valid object is selected.
     */

    /** For some objects only the 8 green handles of the group are
        shown, for others a special handling is required, e.g. bars in
        a bar chart.  This is done here for the currently selected
        object.
     */

    /** Some groups in a chart may not be entered, e.g. an axis
        object.  Otherwise you would be able to select all tick-mark
        objects or labels.

        @returns true, if the currently selected object is a group
                 that may be entered, e.g. a data series object.
     */

    /** get the object which is currently selected in the UI.  In the
        chart this can only be one object at a time.
     */

    /** after move or resize there have to be some things set at chart
        objects and the model.  It is called by MoveMarkedObject.
     */

public:

    SchFuDraw(SchViewShell* pViewSh, SchWindow* pWin, SchView* pView,
              ChartModel* pDoc, SfxRequest& rReq);
    virtual ~SchFuDraw();


    virtual void Activate();

    virtual void ForcePointer(const MouseEvent* pMEvt = NULL);

};

} //namespace binfilter
#endif	// _SCH_FUDRAW_HXX


