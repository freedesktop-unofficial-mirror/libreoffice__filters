/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: workctrl.hxx,v $
 *
 *  $Revision: 1.4 $
 *
 *  last change: $Author: rt $ $Date: 2006-10-28 01:00:26 $
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
#ifndef _WORKCTRL_HXX
#define _WORKCTRL_HXX

#ifndef _SFXTBXCTRL_HXX //autogen
#include <bf_sfx2/tbxctrl.hxx>
#endif

#ifndef _SV_TOOLBOX_HXX
#include <vcl/toolbox.hxx>
#endif
#ifndef _STDCTRL_HXX
#include <svtools/stdctrl.hxx>
#endif
#ifndef _IMAGEBTN_HXX //autogen
#include <vcl/imagebtn.hxx>
#endif
class PopupMenu; 
namespace binfilter {


class SwView;

// doppelter Eintrag! hrc und hxx
// diese Ids bestimmen, was die Buttons unter dem Scrollbar tun
#define NID_START   20000
#define NID_NEXT 	20000
#define NID_PREV	20001
#define NID_TBL     20002
#define NID_FRM     20003
#define NID_PGE     20004
#define NID_DRW     20005
#define NID_CTRL    20006
#define NID_REG     20007
#define NID_BKM     20008
#define NID_GRF    	20009
#define NID_OLE    	20010
#define NID_OUTL   	20011
#define NID_SEL    	20012
#define NID_FTN   	20013
#define NID_MARK	20014
#define NID_POSTIT  20015
#define NID_SRCH_REP 20016
#define NID_INDEX_ENTRY  20017
#define NID_TABLE_FORMULA	20018
#define NID_TABLE_FORMULA_ERROR		20019
#define NID_COUNT  20



//----------------------------------------------------------------------------
//
//----------------------------------------------------------------------------

class SwTbxInsertCtrl : public SfxToolBoxControl
{
    USHORT 					nLastSlotId;


public:
    SFX_DECL_TOOLBOX_CONTROL();

    SwTbxInsertCtrl( USHORT nId, ToolBox& rTbx, SfxBindings& rBind );
    ~SwTbxInsertCtrl();

    virtual void				StateChanged( USHORT nSID,
                                              SfxItemState eState,
                                              const SfxPoolItem* pState );

};

//----------------------------------------------------------------------------
//
//----------------------------------------------------------------------------

class SwTbxAutoTextCtrl : public SfxToolBoxControl
{
    PopupMenu*				pPopup;
    SwView* 				pView;


    void					DelPopup();
public:
    SFX_DECL_TOOLBOX_CONTROL();

    SwTbxAutoTextCtrl( USHORT nId, ToolBox& rTbx, SfxBindings& rBind );
    ~SwTbxAutoTextCtrl();

    virtual void				StateChanged( USHORT nSID,
                                              SfxItemState eState,
                                              const SfxPoolItem* pState );

};


//----------------------------------------------------------------------------
//
//----------------------------------------------------------------------------

class SwScrollNaviToolBox : public ToolBox
{
    virtual void	MouseButtonUp( const MouseEvent& rMEvt );
    virtual void	RequestHelp( const HelpEvent& rHEvt );

    public:
        SwScrollNaviToolBox(Window* pParent, WinBits nWinStyle ) :
             ToolBox(pParent, nWinStyle ) {}
};

class SwScrollNaviPopup : public SfxPopupWindow
{
    SwScrollNaviToolBox    aToolBox;
    FixedLine       aSeparator;
    FixedInfo       aInfoField;
    ImageList		aIList;
    ImageList       aIListH;

    String			sQuickHelp[2 * NID_COUNT];

    USHORT			nFwdId;
    USHORT			nBackId;

    void            ApplyImageList();
    protected:

    public:
        SwScrollNaviPopup( USHORT nId, SfxBindings & );
        ~SwScrollNaviPopup();

};

//----------------------------------------------------------------------------
//
//----------------------------------------------------------------------------


//----------------------------------------------------------------------------
//	Die ImageButtons muessen sich bei Bedarf den HelpText selbst setzen
//----------------------------------------------------------------------------

class SwHlpImageButton : public ImageButton
{
    BOOL		bUp;
public:
         SwHlpImageButton(Window* pParent, const ResId& rResId, BOOL bUpBtn) :
            ImageButton(pParent, rResId), bUp(bUpBtn){}


};
/* -----------------26.11.2002 09:25-----------------
 * 
 * --------------------------------------------------*/
class SwPreviewZoomControl : public SfxToolBoxControl
{
public:
    SFX_DECL_TOOLBOX_CONTROL();

    SwPreviewZoomControl( USHORT nId, ToolBox& rTbx, SfxBindings& rBind );
    ~SwPreviewZoomControl();


};
} //namespace binfilter
#endif



