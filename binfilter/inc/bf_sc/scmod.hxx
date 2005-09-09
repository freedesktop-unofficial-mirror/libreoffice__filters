/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: scmod.hxx,v $
 *
 *  $Revision: 1.4 $
 *
 *  last change: $Author: rt $ $Date: 2005-09-09 11:28:01 $
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

#ifndef SC_SCMOD_HXX
#define SC_SCMOD_HXX

#ifndef SC_SCDLL_HXX
#include "scdll.hxx"
#endif

#ifndef _TIMER_HXX //autogen
#include <vcl/timer.hxx>
#endif

#ifndef _SFXLSTNER_HXX //autogen
#include <svtools/lstner.hxx>
#endif

#ifndef SC_SCGLOB_HXX
#include "global.hxx"		// ScInputMode
#endif

#ifndef SC_MARKDATA_HXX     //@05.01.98
#include "markdata.hxx"		//ScMarkData
#endif

#ifndef SC_SHELLIDS_HXX
#include "shellids.hxx"
#endif
namespace svtools { class ColorConfig; }
class KeyEvent;
class SfxErrorHandler;
class SvtAccessibilityOptions;
class SvtCTLOptions;
namespace binfilter {

class SdrModel;
class SdrView;
class EditView;
class SvxErrorHandler;

//STRIP008 namespace svtools { class ColorConfig; }

class ScRange;
class ScDocument;
class ScViewCfg;
class ScDocCfg;
class ScAppCfg;
class ScInputCfg;
class ScPrintCfg;
class ScViewOptions;
class ScDocOptions;
class ScAppOptions;
class ScInputOptions;
class ScPrintOptions;
class ScInputHandler;
class ScInputWindow;
class ScTabViewShell;
class ScFunctionDlg;
class ScArgDlgBase;
class ScTeamDlg;
class ScEditFunctionDlg;
class ScMessagePool;
class EditFieldInfo;
class ScNavipiCfg;
class ScFormEditData;
class ScTransferObj;
class ScDrawTransferObj;
class ScSelectionTransferObj;

//==================================================================

//		for internal Drag&Drop:

#define SC_DROP_NAVIGATOR		1
#define SC_DROP_TABLE			2

struct ScDragData
{
    ScTransferObj*		pCellTransfer;
    ScDrawTransferObj*	pDrawTransfer;

    String				aLinkDoc;
    String				aLinkTable;
    String				aLinkArea;
    ScDocument*			pJumpLocalDoc;
    String				aJumpTarget;
    String				aJumpText;
};

struct ScClipData
{
    ScTransferObj*		pCellClipboard;
    ScDrawTransferObj*	pDrawClipboard;
};

//==================================================================


class ScModule: public ScModuleDummy, public SfxListener
{
    Timer				aIdleTimer;
    Timer				aSpellTimer;
    ScDragData			aDragData;
    ScClipData			aClipData;
    ScSelectionTransferObj* pSelTransfer;
    ScMessagePool*      pMessagePool;
    //	globalen InputHandler gibt's nicht mehr, jede View hat einen
    ScInputHandler*     pRefInputHandler;
    ScTeamDlg*			pTeamDlg;
    ScViewCfg*			pViewCfg;
    ScDocCfg*			pDocCfg;
    ScAppCfg*           pAppCfg;
    ScInputCfg*			pInputCfg;
    ScPrintCfg*			pPrintCfg;
    ScNavipiCfg*		pNavipiCfg;
    ::svtools::ColorConfig*   pColorConfig;
    SvtAccessibilityOptions* pAccessOptions;
    SvtCTLOptions*		pCTLOptions;
    SfxErrorHandler*	pErrorHdl;
    SvxErrorHandler* 	pSvxErrorHdl;
    ScFormEditData*		pFormEditData;
    USHORT				nCurRefDlgId;
    BOOL				bIsWaterCan;
    BOOL				bIsInEditCommand;

public:
                    SFX_DECL_INTERFACE(SCID_APP);

                    ScModule( SfxObjectFactory* pFact );
    virtual			~ScModule();

    virtual SfxModule*	Load();
    virtual void    	FillStatusBar(StatusBar &rBar);

    virtual void		Notify( SfxBroadcaster& rBC, const SfxHint& rHint );

    void				DeleteCfg();
//STRIP001 	void				CloseDialogs();

                        // von der Applikation verschoben:

    DECL_LINK( IdleHandler,		Timer* );	// Timer statt idle
    DECL_LINK( SpellTimerHdl,	Timer* );
    DECL_LINK( CalcFieldValueHdl, EditFieldInfo* );

     void				Execute( SfxRequest& rReq ){DBG_BF_ASSERT(0, "STRIP");}; //STRIP001 void				Execute( SfxRequest& rReq );
    void 				GetState( SfxItemSet& rSet );

    void				AnythingChanged();

    //	Drag & Drop:
    const ScDragData&	GetDragData() const		{ return aDragData; }
//STRIP001 	void				SetDragObject( ScTransferObj* pCellObj, ScDrawTransferObj* pDrawObj );
    void				ResetDragObject();
//STRIP001 	void				SetDragLink( const String& rDoc, const String& rTab, const String& rArea );
//STRIP001 	void				SetDragJump( ScDocument* pLocalDoc,
//STRIP001 									const String& rTarget, const String& rText );

    //	clipboard:
    const ScClipData&	GetClipData() const		{ return aClipData; }
    void				SetClipObject( ScTransferObj* pCellObj, ScDrawTransferObj* pDrawObj );

    ScDocument*			GetClipDoc();		// called from document - should be removed later

    //	X selection:
    ScSelectionTransferObj*	GetSelectionTransfer() const	{ return pSelTransfer; }
//STRIP001 	void				SetSelectionTransfer( ScSelectionTransferObj* pNew );

    void				SetWaterCan( BOOL bNew )	{ bIsWaterCan = bNew; }
    BOOL				GetIsWaterCan() const 		{ return bIsWaterCan; }

    void				SetInEditCommand( BOOL bNew )	{ bIsInEditCommand = bNew; }
    BOOL				IsInEditCommand() const 		{ return bIsInEditCommand; }

    // Options:
    const ScViewOptions&	GetViewOptions	();
    const ScDocOptions&		GetDocOptions	();
    const ScAppOptions&		GetAppOptions	();
    const ScInputOptions&	GetInputOptions	();
    const ScPrintOptions&	GetPrintOptions	();
//STRIP001 	void					SetViewOptions	( const ScViewOptions& rOpt );
//STRIP001 	void					SetDocOptions	( const ScDocOptions& rOpt );
    void					SetAppOptions	( const ScAppOptions& rOpt );
    void					SetInputOptions	( const ScInputOptions& rOpt );
    void					SetPrintOptions	( const ScPrintOptions& rOpt );
//STRIP001 	void					InsertEntryToLRUList(USHORT nFIndex);
    void					RecentFunctionsChanged();

    static void			GetSpellSettings( USHORT& rDefLang, USHORT& rCjkLang, USHORT& rCtlLang,
                                        BOOL& rAutoSpell, BOOL& rHideAuto );
//STRIP001 	static void			SetAutoSpellProperty( BOOL bSet );
//STRIP001 	static void			SetHideAutoProperty( BOOL bSet );
//STRIP001 	static BOOL			HasThesaurusLanguage( USHORT nLang );

    USHORT				GetOptDigitLanguage();		// from CTL options

    ScNavipiCfg&		GetNavipiCfg();
    ::svtools::ColorConfig&   GetColorConfig();
    SvtAccessibilityOptions& GetAccessOptions();
    SvtCTLOptions&		GetCTLOptions();

//STRIP001 	void				ModifyOptions( const SfxItemSet& rOptSet );

    //	InputHandler:
//STRIP001 	BOOL                IsEditMode();	// nicht bei SC_INPUT_TYPE
//STRIP001 	BOOL                IsInputMode();	// auch bei SC_INPUT_TYPE
//STRIP001 	void                SetInputMode( ScInputMode eMode );
//STRIP001 	BOOL                InputKeyEvent( const KeyEvent& rKEvt, BOOL bStartEdit = FALSE );
    void                InputEnterHandler( BYTE nBlockMode = 0 );
//STRIP001 	void                InputCancelHandler();
//STRIP001 	void                InputSelection( EditView* pView );
//STRIP001 	void                InputChanged( EditView* pView );
    ScInputHandler*		GetInputHdl( ScTabViewShell* pViewSh = NULL, BOOL bUseRef = TRUE );

//STRIP001 	void				SetRefInputHdl( ScInputHandler* pNew );
    ScInputHandler*		GetRefInputHdl();

//STRIP001 	void				SetInputWindow( ScInputWindow* pWin );
    void				ViewShellGone(ScTabViewShell* pViewSh);
//STRIP001 	void				ViewShellChanged();
    // Kommunikation mit Funktionsautopilot
//STRIP001 	void				InputGetSelection( xub_StrLen& rStart, xub_StrLen& rEnd );
//STRIP001 	void			 	InputSetSelection( xub_StrLen nStart, xub_StrLen nEnd );
//STRIP001 	void			 	InputReplaceSelection( const String& rStr );
//STRIP001 	String				InputGetFormulaStr();
//STRIP001 	void				ActivateInputWindow( const String* pStr = NULL,
//STRIP001 												BOOL bMatrix = FALSE );

//STRIP001 	void				InitFormEditData();
//STRIP001 	void				ClearFormEditData();
    ScFormEditData*		GetFormEditData()		{ return pFormEditData; }

    //	Referenzeingabe:
//STRIP001 	void				SetRefDialog( USHORT nId, BOOL bVis, SfxViewFrame* pViewFrm = NULL );
//STRIP001 	BOOL                IsModalMode(SfxObjectShell* pDocSh = NULL);
    BOOL                IsFormulaMode();
//STRIP001 	BOOL                IsRefDialogOpen();
//STRIP001 	BOOL				IsTableLocked();
//STRIP001 	void				OpenTeamDlg();
    void				SetTeamDlg( ScTeamDlg* pDlg )			{ pTeamDlg = pDlg; }
    ScTeamDlg*			GetTeamDlg() const						{ return pTeamDlg; }
//STRIP001 	void				SetReference( const ScRange& rRef, ScDocument* pDoc,
//STRIP001 										const ScMarkData* pMarkData = NULL );
//STRIP001 	void				AddRefEntry();
//STRIP001 	void                EndReference();
    USHORT				GetCurRefDlgId() const					{ return nCurRefDlgId; }

    //virtuelle Methoden fuer den Optionendialog
//STRIP001 	virtual SfxItemSet*	 CreateItemSet( USHORT nId );
//STRIP001 	virtual void		 ApplyItemSet( USHORT nId, const SfxItemSet& rSet );
//STRIP001 	virtual	SfxTabPage*	 CreateTabPage( USHORT nId, Window* pParent, const SfxItemSet& rSet );
};

#define SC_MOD() ( *(ScModule**) GetAppData(BF_SHL_CALC) )

} //namespace binfilter
#endif


