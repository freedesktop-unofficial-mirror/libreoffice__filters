/*************************************************************************
 *
 *  $RCSfile: srcedtw.hxx,v $
 *
 *  $Revision: 1.3 $
 *
 *  last change: $Author: hr $ $Date: 2004-08-03 19:05:53 $
 *
 *  The Contents of this file are made available subject to the terms of
 *  either of the following licenses
 *
 *         - GNU Lesser General Public License Version 2.1
 *         - Sun Industry Standards Source License Version 1.1
 *
 *  Sun Microsystems Inc., October, 2000
 *
 *  GNU Lesser General Public License Version 2.1
 *  =============================================
 *  Copyright 2000 by Sun Microsystems, Inc.
 *  901 San Antonio Road, Palo Alto, CA 94303, USA
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public
 *  License version 2.1, as published by the Free Software Foundation.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public
 *  License along with this library; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 *  MA  02111-1307  USA
 *
 *
 *  Sun Industry Standards Source License Version 1.1
 *  =================================================
 *  The contents of this file are subject to the Sun Industry Standards
 *  Source License Version 1.1 (the "License"); You may not use this file
 *  except in compliance with the License. You may obtain a copy of the
 *  License at http://www.openoffice.org/license.html.
 *
 *  Software provided under this License is provided on an "AS IS" basis,
 *  WITHOUT WARRANTY OF ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING,
 *  WITHOUT LIMITATION, WARRANTIES THAT THE SOFTWARE IS FREE OF DEFECTS,
 *  MERCHANTABLE, FIT FOR A PARTICULAR PURPOSE, OR NON-INFRINGING.
 *  See the License for the specific provisions governing your rights and
 *  obligations concerning the Software.
 *
 *  The Initial Developer of the Original Code is: Sun Microsystems, Inc.
 *
 *  Copyright: 2000 by Sun Microsystems, Inc.
 *
 *  All Rights Reserved.
 *
 *  Contributor(s): _______________________________________
 *
 *
 ************************************************************************/
#ifndef _SRCEDTW_HXX
#define _SRCEDTW_HXX

#ifndef _WINDOW_HXX //autogen
#include <vcl/window.hxx>
#endif

// auto strip #ifndef _SFXLSTNER_HXX //autogen
// auto strip #include <svtools/lstner.hxx>
// auto strip #endif

// auto strip #ifndef _TIMER_HXX //autogen
// auto strip #include <vcl/timer.hxx>
// auto strip #endif

// auto strip #ifndef _TABLE_HXX //autogen
// auto strip #include <tools/table.hxx>
// auto strip #endif

// auto strip #ifndef _XTEXTEDT_HXX //autogen
// auto strip #include <svtools/xtextedt.hxx>
// auto strip #endif
class ScrollBar; 
namespace binfilter {


class SwSrcView;
//STRIP001 class SwSrcEditWindow;
class TextEngine;
class ExtTextView;
class DataChangedEvent;

class TextViewOutWin : public Window
{
    ExtTextView*	pTextView;

protected:
    virtual void	Paint( const Rectangle& );
    virtual void	KeyInput( const KeyEvent& rKeyEvt );
    virtual void	MouseMove( const MouseEvent& rMEvt );
    virtual void	MouseButtonDown( const MouseEvent& rMEvt );
    virtual void	MouseButtonUp( const MouseEvent& rMEvt );
    virtual void	Command( const CommandEvent& rCEvt );
    virtual void	DataChanged( const DataChangedEvent& );

public:
        TextViewOutWin(Window* pParent, WinBits nBits) :
            Window(pParent, nBits), pTextView(0){}

    void	SetTextView( ExtTextView* pView ) {pTextView = pView;}

};

//------------------------------------------------------------
namespace svt{ class SourceViewConfig;}
//STRIP001 class SwSrcEditWindow : public Window, public SfxListener
//STRIP001 {
//STRIP001 private:
//STRIP001 	ExtTextView*	pTextView;
//STRIP001 	ExtTextEngine*	pTextEngine;
//STRIP001 
//STRIP001 	TextViewOutWin*	pOutWin;
//STRIP001 	ScrollBar	   	*pHScrollbar,
//STRIP001 					*pVScrollbar;
//STRIP001 
//STRIP001 	SwSrcView* 		pSrcView;
//STRIP001     svt::SourceViewConfig* pSourceViewConfig;
//STRIP001 
//STRIP001 	long			nCurTextWidth;
//STRIP001 	USHORT			nStartLine;
//STRIP001     rtl_TextEncoding eSourceEncoding;
//STRIP001 	BOOL			bReadonly;
//STRIP001 	BOOL			bDoSyntaxHighlight;
//STRIP001 	BOOL			bHighlighting;
//STRIP001 
//STRIP001 	Timer			aSyntaxIdleTimer;
//STRIP001 	Table			aSyntaxLineTable;
//STRIP001 
//STRIP001 	void			ImpDoHighlight( const String& rSource, USHORT nLineOff );
//STRIP001     void            SetFont();
//STRIP001 
//STRIP001 	DECL_LINK( SyntaxTimerHdl, Timer * );
//STRIP001 	DECL_LINK( TimeoutHdl, Timer * );
//STRIP001 
//STRIP001 protected:
//STRIP001 
//STRIP001 	virtual void	Resize();
//STRIP001 	virtual void	DataChanged( const DataChangedEvent& );
//STRIP001 	virtual void 	GetFocus();
//STRIP001 //	virtual void 	LoseFocus();
//STRIP001 
//STRIP001 	void 			CreateTextEngine();
//STRIP001 	void			DoSyntaxHighlight( USHORT nPara );
//STRIP001 
//STRIP001 	virtual void	Notify( SfxBroadcaster& rBC, const SfxHint& rHint );
//STRIP001 
//STRIP001 	DECL_LINK(ScrollHdl, ScrollBar*);
//STRIP001 
//STRIP001 public:
//STRIP001 					SwSrcEditWindow( Window* pParent, SwSrcView* pParentView );
//STRIP001 					~SwSrcEditWindow();
//STRIP001 
//STRIP001 	void			SetScrollBarRanges();
//STRIP001 	void			InitScrollBars();
//STRIP001 	ULONG			Read( SvStream& rInput)
//STRIP001 						{return pTextEngine->Read(rInput);}
//STRIP001 	ULONG			Write( SvStream& rOutput)
//STRIP001 						{return pTextEngine->Write(rOutput);}
//STRIP001 
//STRIP001 	ExtTextView*	GetTextView()
//STRIP001 						{return pTextView;}
//STRIP001 	TextEngine*		GetTextEngine()
//STRIP001 						{return pTextEngine;}
//STRIP001 	SwSrcView* 		GetSrcView() {return pSrcView;}
//STRIP001 
//STRIP001 	TextViewOutWin*	GetOutWin() {return pOutWin;}
//STRIP001 	void			Invalidate();
//STRIP001 
//STRIP001 	void			ClearModifyFlag()
//STRIP001 						{ pTextEngine->SetModified(FALSE); }
//STRIP001 	BOOL			IsModified() const
//STRIP001 						{ return pTextEngine->IsModified();}
//STRIP001 	void			CreateScrollbars();
//STRIP001 
//STRIP001 	void			SetReadonly(BOOL bSet){bReadonly = bSet;}
//STRIP001 	BOOL			IsReadonly(){return bReadonly;}
//STRIP001 
//STRIP001 	void			DoDelayedSyntaxHighlight( USHORT nPara );
//STRIP001 
//STRIP001 	void			SyntaxColorsChanged();
//STRIP001 
//STRIP001 	void			SetStartLine(USHORT nLine){nStartLine = nLine;}
//STRIP001 
//STRIP001 	virtual void	Command( const CommandEvent& rCEvt );
//STRIP001 	void 			HandleWheelCommand( const CommandEvent& rCEvt );
//STRIP001 
//STRIP001     void            SetTextEncoding(rtl_TextEncoding eEncoding);
//STRIP001 };

} //namespace binfilter
#endif
