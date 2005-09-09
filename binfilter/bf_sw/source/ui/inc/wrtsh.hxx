/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: wrtsh.hxx,v $
 *
 *  $Revision: 1.4 $
 *
 *  last change: $Author: rt $ $Date: 2005-09-09 06:04:17 $
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
#ifndef _WRTSH_HXX
#define _WRTSH_HXX

#ifndef _FESH_HXX
#include <fesh.hxx>
#endif
#ifndef _SORTOPT_HXX
#include <sortopt.hxx>
#endif
#ifndef _SWURL_HXX
#include <swurl.hxx>
#endif
#include <tools/debug.hxx>
namespace com { namespace sun { namespace star { namespace util {
    struct SearchOptions;
} } } }
class Window; 
class SbxArray; 
class SvInPlaceObjectRef; 
class SvEmbeddedObjectRef; 
class SvGlobalName; 
class Timer; 
class SvxMacro; 

namespace binfilter {
class SwDoc;
class SpellCheck;
class SwViewOption;
class SwFlyFrmAttrMgr;
class SwField;
class SwTOXBase;
class SdrView;
class SwView;
class SwInputFieldList;
class SwSection;
class SwFmtINetFmt;
class SvxINetBookmark;
class SvxAutoCorrect;
class NaviContentBookmark;
struct SwCallMouseEvent;
class DropEvent;
struct ChartSelectionInfo;
class SfxStringListItem;

//STRIP008 namespace com { namespace sun { namespace star { namespace util {
//STRIP008 	struct SearchOptions;
//STRIP008 } } } }


class SwWrtShell: public SwFEShell
{
public:
    typedef long (SwWrtShell::*SELECTFUNC)(const Point *, BOOL bProp );

    SELECTFUNC	fnDrag;
    SELECTFUNC	fnSetCrsr;
    SELECTFUNC	fnEndDrag;
    SELECTFUNC	fnKillSel;

    // Alle Selektionen aufheben
//STRIP001 	long ResetSelect( const Point *, BOOL );

    //setzt den Cursorstack nach dem Bewegen mit PageUp/-Down
    //zurueck, falls ein Stack aufgebaut ist
    inline void ResetCursorStack();

    enum SelectionType
    {
        SEL_TXT 	  = CNT_TXT, // Text, niemals auch Rahmen	0x0001
        SEL_GRF 	  = CNT_GRF, // Grafik						0x0002
        SEL_OLE 	  = CNT_OLE, // OLE 						0x0010
        SEL_FRM 	  = 0x0020,	// Rahmen, keine Inhaltsform
        SEL_NUM 	  = 0x0040,	// NumListe
        SEL_TBL 	  = 0x0080,	// Cursor steht in Tabelle
        SEL_TBL_CELLS = 0x0100,	// Tabellenzellen sind selektiert
        SEL_DRW 	  = 0x0200,	// Zeichenobjekte (Rechteck, Kreis...)
        SEL_DRW_TXT   = 0x0400,	// Draw-Textobjekte im Editmode
        SEL_BEZ       = 0x0800,	// Bezierobjekte editieren
        SEL_DRW_FORM  = 0x1000	// Zeichenobjekte: DB-Forms
    };
    int 	GetSelectionType() const;

    BOOL	IsModePushed() const { return 0 != pModeStack; }
//STRIP001 	void	PushMode();
//STRIP001 	void	PopMode();

//STRIP001 	void	SttSelect();
//STRIP001 	void	EndSelect();
    BOOL	IsInSelect() const { return bInSelect; }
    void	SetInSelect(BOOL bSel = TRUE) { bInSelect = bSel; }
        // Liegt eine Text- oder Rahmenselektion vor?
    BOOL    HasSelection() const { return SwCrsrShell::HasSelection() || 
                                        IsMultiSelection() || IsSelFrmMode() || IsObjSelected(); }
//STRIP001 	FASTBOOL Pop( BOOL bOldCrsr = TRUE );

    void	EnterStdMode();
    BOOL	IsStdMode() const { return !bExtMode && !bAddMode; }

//STRIP001 	void	EnterExtMode();
//STRIP001 	void	LeaveExtMode();
//STRIP001 	long	ToggleExtMode();
    BOOL	IsExtMode() const { return bExtMode; }

//STRIP001 	void	EnterAddMode();
//STRIP001 	void	LeaveAddMode();
//STRIP001 	long	ToggleAddMode();
    BOOL	IsAddMode() const { return bAddMode; }

//STRIP001 	void	SetInsMode( BOOL bOn = TRUE );
//STRIP001 	void	ToggleInsMode() { SetInsMode( !bIns ); }
    BOOL	IsInsMode() const { return bIns; }

    void	EnterSelFrmMode(const Point *pStartDrag = 0);
    void	LeaveSelFrmMode();
    BOOL	IsSelFrmMode() const { return bLayoutMode; }
        // Selektion von Rahmen aufheben
    void	UnSelectFrm();

    // Tabellenzellen selektieren fuer Bearbeiten von Formeln in der Ribbonbar
    inline void SelTblCells( const Link &rLink, BOOL bMark = TRUE );
    inline void	EndSelTblCells();

    //Wortweisen oder zeilenweisen Selektionsmodus verlassen. Wird
    //in der Regel in MB-Up gerufen.
    BOOL	IsExtSel() const { return bSelWrd || bSelLn; }

    // erfrage, ob der akt. fnDrag - Pointer auf BeginDrag gesetzt ist
    // Wird fuer MouseMove gebraucht, um die Bugs 55592/55931 zu umgehen.
//STRIP001 	inline BOOL	Is_FnDragEQBeginDrag() const;

    //Basisabfragen
//STRIP001 	BOOL	IsInWrd() 			{ return IsInWord(); }
//STRIP001 	BOOL	IsSttWrd()			{ return IsStartWord(); }
//STRIP001 	BOOL	IsEndWrd();
//STRIP001 	BOOL	IsSttOfPara() const { return IsSttPara(); }
//STRIP001 	BOOL	IsEndOfPara() const { return IsEndPara(); }

    //Word bzw. Satz selektieren.
//STRIP001 	BOOL	SelNearestWrd();
//STRIP001 	BOOL	SelWrd		(const Point * = 0, BOOL bProp=FALSE );
//STRIP001 	BOOL	SelSentence (const Point * = 0, BOOL bProp=FALSE );
//STRIP001 	void	SelLine		(const Point * = 0, BOOL bProp=FALSE );
//STRIP001 	long	SelAll();

    //Basiscursortravelling
typedef FASTBOOL (SwWrtShell:: *FNSimpleMove)();
//STRIP001 	FASTBOOL SimpleMove( FNSimpleMove, FASTBOOL bSelect );

    FASTBOOL Left		( USHORT nMode, FASTBOOL bSelect,
                            USHORT nCount, BOOL bBasicCall, BOOL bVisual = FALSE );
    FASTBOOL Right		( USHORT nMode, FASTBOOL bSelect,
                            USHORT nCount, BOOL bBasicCall, BOOL bVisual = FALSE );
    FASTBOOL Up			( FASTBOOL bSelect = FALSE, USHORT nCount = 1,
                            BOOL bBasicCall = FALSE );
     FASTBOOL Down		( FASTBOOL bSelect = FALSE, USHORT nCount = 1,
                             BOOL bBasicCall = FALSE );
//STRIP001 	FASTBOOL NxtWrd		( FASTBOOL bSelect = FALSE ) { return SimpleMove( &SwWrtShell::_NxtWrd, bSelect ); }
//STRIP001 	FASTBOOL PrvWrd		( FASTBOOL bSelect = FALSE ) { return SimpleMove( &SwWrtShell::_PrvWrd, bSelect ); }
    FASTBOOL LeftMargin	( FASTBOOL bSelect = FALSE, FASTBOOL bBasicCall = FALSE );
    FASTBOOL RightMargin( FASTBOOL bSelect = FALSE, FASTBOOL bBasicCall = FALSE );
    FASTBOOL SttDoc		( FASTBOOL bSelect = FALSE );
    FASTBOOL EndDoc		( FASTBOOL bSelect = FALSE );

    FASTBOOL SttNxtPg	( FASTBOOL bSelect = FALSE );
//STRIP001 	FASTBOOL SttPrvPg	( FASTBOOL bSelect = FALSE );
//STRIP001 	FASTBOOL EndNxtPg	( FASTBOOL bSelect = FALSE );
    FASTBOOL EndPrvPg	( FASTBOOL bSelect = FALSE );
    FASTBOOL SttPg		( FASTBOOL bSelect = FALSE );
    FASTBOOL EndPg		( FASTBOOL bSelect = FALSE );
//STRIP001 	FASTBOOL SttPara	( FASTBOOL bSelect = FALSE );
//STRIP001 	FASTBOOL EndPara	( FASTBOOL bSelect = FALSE );
//STRIP001 	FASTBOOL FwdPara	( FASTBOOL bSelect = FALSE )
//STRIP001 				{ return SimpleMove( &SwWrtShell::_FwdPara, bSelect ); }
//STRIP001 	FASTBOOL BwdPara	( FASTBOOL bSelect = FALSE )
//STRIP001 				{ return SimpleMove( &SwWrtShell::_BwdPara, bSelect ); }
//STRIP001 	FASTBOOL FwdSentence( FASTBOOL bSelect = FALSE )
//STRIP001 				{ return SimpleMove( &SwWrtShell::_FwdSentence, bSelect ); }
//STRIP001 	FASTBOOL BwdSentence( FASTBOOL bSelect = FALSE )
//STRIP001 				{ return SimpleMove( &SwWrtShell::_BwdSentence, bSelect ); }

//STRIP001 	FASTBOOL SelectTableRow();
//STRIP001 	FASTBOOL SelectTableCol();
//STRIP001 	FASTBOOL SelectTxtAttr( USHORT nWhich, const SwTxtAttr* pAttr = 0 );

    // Spaltenweise Spruenge
//STRIP001 	FASTBOOL StartOfColumn		( FASTBOOL bSelect = FALSE );
//STRIP001 	FASTBOOL EndOfColumn		( FASTBOOL bSelect = FALSE );
//STRIP001 	FASTBOOL StartOfNextColumn	( FASTBOOL bSelect = FALSE );
//STRIP001 	FASTBOOL EndOfNextColumn	( FASTBOOL bSelect = FALSE );
//STRIP001 	FASTBOOL StartOfPrevColumn	( FASTBOOL bSelect = FALSE );
//STRIP001 	FASTBOOL EndOfPrevColumn	( FASTBOOL bSelect = FALSE );

    // setze den Cursor auf die Seite "nPage" an den Anfang
    // zusaetzlich zu der gleichnamigen Implementierung in crsrsh.hxx
    // werden hier alle bestehenden Selektionen vor dem Setzen des
    // Cursors aufgehoben
    BOOL	GotoPage(USHORT nPage, BOOL bRecord = TRUE);

    //setzen des Cursors; merken der alten Position fuer Zurueckblaettern.
    DECL_LINK( ExecFlyMac, void * );

//STRIP001 	BOOL	PageCrsr(SwTwips lOffset, BOOL bSelect);

    // Felder Update
//STRIP001 	void	UpdateInputFlds( SwInputFieldList* pLst = 0, BOOL bOnlyInSel = FALSE );

//STRIP001 	void	NoEdit(BOOL bHideCrsr = TRUE);
//STRIP001 	void	Edit();
    BOOL	IsNoEdit() const { return bNoEdit; }

    // change current data base and notify
    void ChgDBData(const SwDBData& SwDBData);

    // Loeschen
//STRIP001 	long	DelToEndOfLine();
//STRIP001 	long	DelToStartOfLine();
//STRIP001 	long	DelLine();
//STRIP001 	long	DelLeft();

    // loescht auch Rahmen bzw. setzt den Cursor in den Rahmen,
    // wenn bDelFrm == FALSE ist
//STRIP001 	long	DelRight( BOOL bDelFrm = FALSE );
//STRIP001 	long	DelToEndOfPara();
//STRIP001 	long	DelToStartOfPara();
//STRIP001 	long	DelToEndOfSentence();
//STRIP001 	long	DelToStartOfSentence();
//STRIP001 	long	DelNxtWord();
//STRIP001 	long	DelPrvWord();

    // Prueft, ob eine Wortselektion vorliegt.
    // Gemaess den Regeln fuer intelligentes Cut / Paste
    // werden umgebende Spaces rausgeschnitten.
    // Liefert Art der Wortselektion zurueck (siehe enum)
    enum {
            NO_WORD = 0,
            WORD_SPACE_BEFORE = 1,
            WORD_SPACE_AFTER = 2,
            WORD_NO_SPACE = 3
        };
//STRIP001 	int 	IntelligentCut(int nSelectionType, BOOL bCut = TRUE);

    // Editieren
//STRIP001 	void	Insert(SwField &);
//STRIP001 	void	Insert(const String &);
//STRIP001 	void 	InsertByWord( const String & );
//STRIP001 	void	InsertPageBreak(const String *pPageDesc = 0, USHORT nPgNum = 0 );
//STRIP001 	void	InsertLineBreak();
//STRIP001 	void	InsertColumnBreak();
//STRIP001 	void	InsertFootnote(const String &, BOOL bEndNote = FALSE, BOOL bEdit = TRUE );
//STRIP001 	void	SplitNode( BOOL bAutoFormat = FALSE, BOOL bCheckTableStart = TRUE );
//STRIP001 	BOOL	CanInsert();

    // Verzeichnisse
//STRIP001 	void	InsertTableOf(const SwTOXBase& rTOX, const SfxItemSet* pSet = 0);
//STRIP001 	BOOL	UpdateTableOf(const SwTOXBase& rTOX, const SfxItemSet* pSet = 0);

    // Numerierung und Bullets
//STRIP001 	void	NumOn();
//STRIP001 	void	BulletOn();

    // Graphic
//STRIP001 	void	Insert( const String &rPath, const String &rFilter,
//STRIP001 					const Graphic &, SwFlyFrmAttrMgr * = 0,
//STRIP001 					BOOL bRule = FALSE );
    //OLE
//STRIP001 	void	Insert	 	( SvInPlaceObjectRef *pObj,		// != 0 fuer Clipboard
//STRIP001 						  SvGlobalName *pName = 0,		// != 0 entspr. Object erzeugen.
//STRIP001 						  BOOL bActivate = TRUE,
//STRIP001 						  USHORT nSlotId = 0);			// SlotId fuer Dialog
//STRIP001 	BOOL	InsertOle	( SvInPlaceObjectRef aRef  );	// In die Core einfuegen.
//STRIP001 	void	LaunchOLEObj( long nVerb = 0 );				// Server starten
    BOOL	IsOLEObj() const { return GetCntType() == CNT_OLE;}
    virtual void CalcAndSetScale( SvEmbeddedObjectRef xObj,
                                  const SwRect *pFlyPrtRect = 0,
                                  const SwRect *pFlyFrmRect = 0 );
    virtual void ConnectObj( SvInPlaceObjectRef xIPObj, const SwRect &rPrt,
                        const SwRect &rFrm );
//STRIP001 	DECL_LINK( ChartSelectionHdl, ChartSelectionInfo * );

    // Vorlagen und Formate

    // enum gibt an, was geschehen soll, wenn das Style nicht gefunden wurde
    enum GetStyle { GETSTYLE_NOCREATE, 			// keins anlegen
                    GETSTYLE_CREATESOME,        // falls auf PoolId mapt anlegen
                    GETSTYLE_CREATEANY };		// ggfs Standard returnen

//STRIP001 	SwTxtFmtColl*	GetParaStyle(const String &rCollName,
//STRIP001 									GetStyle eCreate = GETSTYLE_NOCREATE);
//STRIP001 	SwCharFmt*		GetCharStyle(const String &rFmtName,
//STRIP001 									GetStyle eCreate = GETSTYLE_NOCREATE);
//STRIP001 	SwFrmFmt*		GetTblStyle(const String &rFmtName);

//STRIP001 	void	SetPageStyle(const String &rCollName);

    String	GetCurPageStyle( const BOOL bCalcFrm = TRUE ) const;

    // Aktuelle Vorlage anhand der geltenden Attribute aendern
//STRIP001 	void	QuickUpdateStyle();

    enum DoType { UNDO, REDO, REPEAT };

//STRIP001 	void	Do( DoType eDoType, USHORT nCnt = 1 );
    String	GetDoString( DoType eDoType ) const;
//STRIP001 	String	GetRepeatString() const;
//STRIP001 	USHORT 	GetDoStrings( DoType eDoType, SfxStringListItem& rStrLstItem ) const;

    //Suchen oder Ersetzen
//STRIP001 	ULONG SearchPattern(const ::com::sun::star::util::SearchOptions& rSearchOpt,
//STRIP001 						 SwDocPositions eStart, SwDocPositions eEnde,
//STRIP001 						 FindRanges eFlags = FND_IN_BODY,
//STRIP001 						 int bReplace = FALSE );

//STRIP001 	ULONG SearchTempl  (const String &rTempl,
//STRIP001 						 SwDocPositions eStart, SwDocPositions eEnde,
//STRIP001 						 FindRanges eFlags = FND_IN_BODY,
//STRIP001 						 const String* pReplTempl = 0 );

//STRIP001 	ULONG SearchAttr   (const SfxItemSet& rFindSet,
//STRIP001 						 BOOL bNoColls,
//STRIP001 						 SwDocPositions eStart,SwDocPositions eEnde,
//STRIP001 						 FindRanges eFlags = FND_IN_BODY,
//STRIP001 						 const ::com::sun::star::util::SearchOptions* pSearchOpt = 0,
//STRIP001 						 const SfxItemSet* pReplaceSet = 0);

//STRIP001 	void AutoCorrect( SvxAutoCorrect& rACorr, sal_Unicode cChar = ' ' );

    // Aktion vor Cursorbewegung
    // Hebt gfs. Selektionen auf, triggert Timer und GCAttr()
//STRIP001 	void	MoveCrsr( FASTBOOL bWithSelect = FALSE );

    // Eingabefelder updaten
//STRIP001     BOOL    StartInputFldDlg(SwField*, BOOL bNextButton, ByteString* pWindowState = 0);
//STRIP001     // update DropDown fields
//STRIP001     BOOL    StartDropDownFldDlg(SwField*, BOOL bNextButton, ByteString* pWindowState = 0);

    //"Handler" fuer Anederungen an der DrawView - fuer Controls.
    virtual void DrawSelChanged( SdrView * );

    // springe zum Bookmark und setze die "Selections-Flags" wieder richtig
    FASTBOOL GotoBookmark( USHORT nPos );
//STRIP001 	FASTBOOL GotoBookmark( USHORT nPos, BOOL bSelect, BOOL bStart );
//STRIP001 	FASTBOOL GotoBookmark( const String& rName );
//STRIP001 	FASTBOOL GoNextBookmark(); // TRUE, wenn's noch eine gab
//STRIP001 	FASTBOOL GoPrevBookmark();

    // jump to the next / previous hyperlink - inside text and also
    // on graphics
//STRIP001 	FASTBOOL SelectNextPrevHyperlink( BOOL bNext = TRUE );

    // Zugehoerige SwView ermitteln
    const SwView&		GetView() const { return rView; }
    SwView&				GetView() { return rView; }

    //Weil es sonst keiner macht, gibt es hier eine ExecMacro()
//STRIP001 	void ExecMacro( const SvxMacro& rMacro, String* pRet = 0, SbxArray* pArgs = 0 );
    // rufe ins dunkle Basic/JavaScript
//STRIP001 	USHORT CallEvent( USHORT nEvent, const SwCallMouseEvent& rCallEvent,
//STRIP001 						BOOL bCheckPtr = FALSE, SbxArray* pArgs = 0,
//STRIP001 						const Link* pCallBack = 0 );

//STRIP001 	void 	StartBasicAction();
//STRIP001 	void 	EndBasicAction();
//STRIP001 	void 	SetBasicActionCount(USHORT nSet);
//STRIP001 	USHORT 	EndAllBasicActions();

    // ein Klick aus das angegebene Feld. Der Cursor steht auf diesem.
    // Fuehre die vor definierten Aktionen aus.
//STRIP001 	void ClickToField( const SwField& rFld, USHORT nFilter = URLLOAD_NOFILTER );
//STRIP001 	void ClickToINetAttr( const SwFmtINetFmt& rItem, USHORT nFilter = URLLOAD_NOFILTER );
//STRIP001 	BOOL ClickToINetGrf( const Point& rDocPt, USHORT nFilter = URLLOAD_NOFILTER );
    inline BOOL IsInClickToEdit() const ;

    // fall ein URL-Button selektiert ist, dessen URL returnen, ansonsten
    // einen LeerString
//STRIP001 	BOOL GetURLFromButton( String& rURL, String& rDescr ) const;
//STRIP001 	BOOL SetURLToButton( const String& rURL, const String& rDescr );

//STRIP001 	void NavigatorPaste( const NaviContentBookmark& rBkmk,
//STRIP001 						 const USHORT nAction );

    // die Core erzeugt eine Selektion, das SttSelect muss gerufen werden
//STRIP001 	virtual void NewCoreSelection();

    // autom. Update von Vorlagen
//STRIP001 	void AutoUpdateFrame(SwFrmFmt* pFmt, const SfxItemSet& rStyleSet);
//STRIP001 	void AutoUpdatePara(SwTxtFmtColl* pColl, const SfxItemSet& rStyleSet);

    // Link fuers einfuegen von Bereichen uebers Drag&Drop/Clipboard
//STRIP001 	DECL_STATIC_LINK( SwWrtShell, InsertRegionDialog, SwSection* );


    //ctoren, der erstere ist eine Art kontrollierter copy ctor fuer weitere
    //Sichten auf ein Dokument
    SwWrtShell( SwWrtShell&, Window *pWin, SwView &rShell);
    SwWrtShell( SwDoc& rDoc, Window *pWin, SwView &rShell,
                SwRootFrm* pMaster = 0, const SwViewOption *pViewOpt = 0);
    virtual ~SwWrtShell();

private:

//STRIP001 	void	OpenMark();
//STRIP001 	void	CloseMark( BOOL bOkFlag );

    String	GetWrdDelim();
    String	GetSDelim();
    String	GetBothDelim();

    struct ModeStack
    {
        ModeStack	*pNext;
        BOOL		bAdd,
                    bExt,
                    bIns;
        ModeStack(ModeStack *pNextMode, BOOL _bIns, BOOL _bExt, BOOL _bAdd):
            pNext(pNextMode),
            bIns(_bIns),
            bExt(_bExt),
            bAdd(_bAdd) {}
    } *pModeStack;

    // Cursor bei PageUp / -Down mitnehmen
    enum PageMove
    {
        MV_NO,
        MV_PAGE_UP,
        MV_PAGE_DOWN
    }  ePageMove;

    struct CrsrStack
    {
        Point aDocPos;
        CrsrStack *pNext;
        BOOL bValidCurPos : 1;
        BOOL bIsFrmSel : 1;
        SwTwips lOffset;

        CrsrStack( BOOL bValid, BOOL bFrmSel, const Point &rDocPos,
                    SwTwips lOff, CrsrStack *pN )
            : aDocPos(rDocPos), lOffset(lOff), pNext(pN)
        {
            bValidCurPos = bValid;
            bIsFrmSel = bFrmSel;
        }

    } *pCrsrStack;

    SwView	&rView;

    Point	aDest;
    BOOL	bDestOnStack;
    BOOL	HasCrsrStack() const { return 0 != pCrsrStack; }
//STRIP001 	BOOL	PushCrsr(SwTwips lOffset, BOOL bSelect);
    BOOL	PopCrsr(BOOL bUpdate, BOOL bSelect = FALSE);

    // ENDE Cursor bei PageUp / -Down mitnehmen
//STRIP001 	FASTBOOL _SttWrd();
//STRIP001 	FASTBOOL _EndWrd();
//STRIP001 	FASTBOOL _NxtWrd();
//STRIP001 	FASTBOOL _PrvWrd();
//STRIP001 	FASTBOOL _FwdSentence();
//STRIP001 	FASTBOOL _BwdSentence();
//STRIP001 	FASTBOOL _FwdPara();
//STRIP001 	FASTBOOL _BwdPara();

        //	Selektionen
    BOOL	bIns			:1;
    BOOL	bInSelect		:1;
    BOOL	bExtMode		:1;
    BOOL	bAddMode		:1;
    BOOL	bLayoutMode		:1;
    BOOL	bNoEdit			:1;
    BOOL	bCopy			:1;
    BOOL	bSelWrd			:1;
    BOOL	bSelLn			:1;
    BOOL	bIsInClickToEdit:1;
    BOOL 	bClearMark		:1;		// Selektion fuer ChartAutoPilot nicht loeschen

    Point	aStart;
    Link	aSelTblLink;

    SELECTFUNC	fnLeaveSelect;

    //setzt den Cursorstack nach dem Bewegen mit PageUp/-Down zurueck.
//STRIP001 	void	_ResetCursorStack();

    void	SttDragDrop(Timer *);
    long	SetCrsr(const Point *, BOOL bProp=FALSE );
//STRIP001 	long	SetCrsrKillSel(const Point *, BOOL bProp=FALSE );

    long	StdSelect(const Point *, BOOL bProp=FALSE );
    long	BeginDrag(const Point *, BOOL bProp=FALSE );
//STRIP001 	long	Drag(const Point *, BOOL bProp=FALSE );
     long	EndDrag(const Point *, BOOL bProp=FALSE );

//STRIP001 	long	ExtSelWrd(const Point *, BOOL bProp=FALSE );
//STRIP001 	long	ExtSelLn(const Point *, BOOL bProp=FALSE );

    //Verschieben von Text aus Drag and Drop; Point ist
    //Destination fuer alle Selektionen.
//STRIP001 	long	MoveText(const Point *, BOOL bProp=FALSE );

//STRIP001 	long	BeginFrmDrag(const Point *, BOOL bProp=FALSE );

    //nach SSize/Move eines Frames Update; Point ist Destination.
//STRIP001 	long	UpdateLayoutFrm(const Point *, BOOL bProp=FALSE );

    long	SttLeaveSelect(const Point *, BOOL bProp=FALSE );
//STRIP001 	long	AddLeaveSelect(const Point *, BOOL bProp=FALSE );
    long	Ignore(const Point *, BOOL bProp=FALSE );

    void	LeaveExtSel() { bSelWrd = bSelLn = FALSE;}
//STRIP001 	BOOL	_CanInsert();

//STRIP001 	BOOL	GoStart(BOOL KeepArea = FALSE, BOOL * = 0,
//STRIP001 			BOOL bSelect = FALSE, BOOL bDontMoveRegion = FALSE);
//STRIP001 	BOOL	GoEnd(BOOL KeepArea = FALSE, BOOL * = 0);

    enum BookMarkMove
    {
        BOOKMARK_INDEX,
        BOOKMARK_NEXT,
        BOOKMARK_PREV,
        BOOKMARK_LAST_LAST_ENTRY
    };

//STRIP001 	FASTBOOL MoveBookMark( 	BookMarkMove eFuncId,
//STRIP001 							USHORT nPos = 0,
//STRIP001 							BOOL bStart = TRUE );

};

 inline void SwWrtShell::ResetCursorStack()
 {
     if ( HasCrsrStack() )
    {DBG_BF_ASSERT(0, "STRIP"); }//STRIP001 _ResetCursorStack();
 }

inline void SwWrtShell::SelTblCells(const Link &rLink, BOOL bMark )
{
    SetSelTblCells( TRUE );
    bClearMark = bMark;
    aSelTblLink = rLink;
}
inline void SwWrtShell::EndSelTblCells()
{
    SetSelTblCells( FALSE );
    bClearMark = TRUE;
}

inline BOOL SwWrtShell::IsInClickToEdit() const { return bIsInClickToEdit; }

//STRIP001 inline BOOL	SwWrtShell::Is_FnDragEQBeginDrag() const
//STRIP001 {
//STRIP001 #ifdef GCC
//STRIP001 	SELECTFUNC	fnTmp = &SwWrtShell::BeginDrag;
//STRIP001 	return fnDrag == fnTmp;
//STRIP001 #else
//STRIP001 	return fnDrag == &SwWrtShell::BeginDrag;
//STRIP001 #endif
//STRIP001 }

} //namespace binfilter
#endif
