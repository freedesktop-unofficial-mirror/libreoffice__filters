/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: chwindow.hxx,v $
 *
 *  $Revision: 1.4 $
 *
 *  last change: $Author: rt $ $Date: 2005-09-09 11:44:35 $
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

#ifndef _SCH_SDWINDOW_HXX
#define _SCH_SDWINDOW_HXX


#ifndef _GEN_HXX //autogen
#include <tools/gen.hxx>
#endif
#ifndef _SV_WINDOW_HXX //autogen
#include <vcl/window.hxx>
#endif
#ifndef _SV_EVENT_HXX //autogen
#include <vcl/event.hxx>
#endif
// auto strip #ifndef _SVDOBJ_HXX //autogen wg. SdrObject
// auto strip #include <bf_svx/svdobj.hxx>
// auto strip #endif
#ifndef _TRANSFER_HXX //autogen
#include <svtools/transfer.hxx>
#endif
namespace com { namespace sun { namespace star {
    namespace accessibility {
        class XAccessible;
    }
}}}
namespace binfilter {

class SchViewShell;
class ChartModel;

//STRIP008 namespace com { namespace sun { namespace star {
//STRIP008 	namespace accessibility {
//STRIP008 		class XAccessible;
//STRIP008 	}
//STRIP008 }}}

namespace accessibility 
{
    class AccessibleDocumentView;
}

/*************************************************************************
|*
|* SchWindow beinhaltet den eigentlichen Arbeitsbereich von
|* SchViewShell
|*
\************************************************************************/
class SchWindow : public Window, public DropTargetHelper
{
protected:
    Point	aWinPos;
    Point	aViewOrigin;
    Size	aViewSize;

    SchViewShell* pViewShell;

//STRIP001 	virtual void Paint(const Rectangle& rRect);
//STRIP001 	virtual void KeyInput(const KeyEvent& rKEvt);
//STRIP001 	virtual void MouseMove(const MouseEvent& rMEvt);
//STRIP001 	virtual void MouseButtonUp(const MouseEvent& rMEvt);
//STRIP001 	virtual void MouseButtonDown(const MouseEvent& rMEvt);
//STRIP001 	virtual void Command(const CommandEvent& rCEvt);

    // for quick help
//STRIP001 	virtual void RequestHelp( const HelpEvent& );

    /** Create an accessibility object that makes this window accessible.
        
        @return
            The returned reference is empty if no accessible object could be
            created.
    */
//STRIP001     virtual ::com::sun::star::uno::Reference<
//STRIP001         ::com::sun::star::accessibility::XAccessible > 
//STRIP001         CreateAccessible( void );

private:
    // for quick help
//STRIP001 	SdrObject *GetHitObject( SdrObjList*, Point& );
//STRIP001 	String GetQuickHelpText( SdrObject*, ChartModel*, BOOL bVerbose=FALSE );

    /// attention: this pointer is only valid, if the weak reference below is valid
    ::binfilter::accessibility::AccessibleDocumentView * m_pAccDocumentView;
    ::com::sun::star::uno::WeakReference< ::com::sun::star::accessibility::XAccessible >
        m_xAccDocumentView;

public:
    SchWindow(Window* pParent);
    virtual ~SchWindow();

    void SetViewShell(SchViewShell* pViewSh) { pViewShell=pViewSh; };

//STRIP001 	void ShareViewArea(const SchWindow* pOtherWin);

    void SetZoom(long nZoom);
//STRIP001 	long SetZoomRect(const Rectangle& rZoomRect);
    long SetZoomFactor(long nZoom);

    long GetZoom() const
        { return GetMapMode().GetScaleX().GetNumerator() * 100L /
                 GetMapMode().GetScaleX().GetDenominator(); }

    void SetWinPos(const Point& rPos) { aWinPos = rPos; }
    const Point& GetWinPos() { return aWinPos; }
    void SetViewOrigin(const Point& rPos) { aViewOrigin = rPos; }
    const Point& GetViewOrigin() { return aViewOrigin; }
    void SetViewSize(const Size& rSize) { aViewSize = rSize; }
    const Size& GetViewSize() { return aViewSize; }

//STRIP001 	void UpdateMapOrigin();
//STRIP001 	virtual void DataChanged( const DataChangedEvent& rDCEvt );

    // DropTargetHelper
//STRIP001 	virtual sal_Int8 AcceptDrop( const AcceptDropEvent& rEvt );
//STRIP001 	virtual sal_Int8 ExecuteDrop( const ExecuteDropEvent& rEvt );

//STRIP001     String GetQuickHelpText( UINT16 nObjId, ChartModel* pModel, BOOL bVerbose,
//STRIP001                              UINT16 nSeriesIndex = 0, UINT16 nDataPointIndex = 0 );

//STRIP001     SchViewShell * GetViewShell();

//STRIP001     ::accessibility::AccessibleDocumentView * GetAccessibleDocumentView() const;
};

} //namespace binfilter
#endif		// _SCH_SDWINDOW_HXX
