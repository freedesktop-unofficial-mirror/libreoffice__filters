/*************************************************************************
 *
 *  $RCSfile: crsrsh.hxx,v $
 *
 *  $Revision: 1.1.1.1 $
 *
 *  last change: $Author: hjs $ $Date: 2003-10-01 12:23:56 $
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
#ifndef _CRSRSH_HXX
#define _CRSRSH_HXX

#ifndef _STRING_HXX //autogen
#include <tools/string.hxx>
#endif
#ifndef _LINK_HXX //autogen
#include <tools/link.hxx>
#endif
#ifndef _RTTI_HXX //autogen
#include <tools/rtti.hxx>
#endif

#ifndef _SWTYPES_HXX
#include <swtypes.hxx>			// fuer SWPOSDOC
#endif
#ifndef _VIEWSH_HXX
#include <viewsh.hxx>			// fuer ViewShell
#endif
#ifndef _CALBCK_HXX
#include <calbck.hxx>			// fuer SwClient
#endif
#ifndef _CSHTYP_HXX
#include <cshtyp.hxx>        	// fuer die CursorShell Typen
#endif
#ifndef _CRSTATE_HXX
#include <crstate.hxx>			// fuer die CursorMove-Staties
#endif
#ifndef _BKMRKE_HXX //autogen
#include <bkmrke.hxx>
#endif
#ifndef _TOXE_HXX
#include <toxe.hxx>				// SwTOXSearchDir
#endif

#if defined(PRODUCT) && !defined(WIN)
// fuer die Inline-Methoden
#ifndef _VISCRS_HXX
#include <viscrs.hxx>
#endif
#ifndef _NODE_HXX
#include <node.hxx>
#endif
#define CRSR_INLINE inline
#else
#define CRSR_INLINE
#endif

// einige Forward Deklarationen

class KeyCode;
class Region;
class SfxItemSet;
class SfxPoolItem;
class SpellCheck;
class SwBookmark;
class SwCntntFrm;
class SwCrsrShell;
class SwCursor;
class SwField;
class SwFieldType;
class SwFmt;
class SwFmtFld;
class SwIndex;
class SwNodeIndex;
class SwNode;
class SwNodes;
class SwPaM;
class SwSelBoxes;
class SwShellCrsr;
class SwShellTableCrsr;
class SwTableNode;
class SwTxtFmtColl;
class SwVisCrsr;
class SwTxtINetFmt;
class SwFmtINetFmt;
class SwTxtAttr;
class SwTableBox;
class SwCellFrms;
class SwTOXMark;
class SwRedline;
struct SwPosition;

namespace com { namespace sun { namespace star { namespace util {
    struct SearchOptions;
} } } }


// enum und struktur, um ueber die Doc-Position Informationen zu erfragen

struct SwContentAtPos
{
    enum IsAttrAtPos
    {
        SW_NOTHING 		= 0x0000,
        SW_FIELD		= 0x0001,
        SW_CLICKFIELD	= 0x0002,
        SW_FTN			= 0x0004,
        SW_INETATTR		= 0x0008,
        SW_TABLEBOXFML	= 0x0010,
        SW_REDLINE		= 0x0020,
        SW_OUTLINE		= 0x0040,
        SW_TOXMARK		= 0x0080,
        SW_REFMARK		= 0x0100
#ifndef PRODUCT
        ,SW_CURR_ATTRS 		= 0x4000		// nur zum Debuggen
        ,SW_TABLEBOXVALUE	= 0x8000		// nur zum Debuggen
#endif
    } eCntntAtPos;

    union {
        const SwField* pFld;
        const SfxPoolItem* pAttr;
        const SwRedline* pRedl;
    } aFnd;

    String sStr;
    const SwTxtAttr* pFndTxtAttr;

    SwContentAtPos( int eGetAtPos = 0xffff )
        : eCntntAtPos( (IsAttrAtPos)eGetAtPos )
    {
        aFnd.pFld = 0;
        pFndTxtAttr = 0;
    }

    // befindet sich der Node in einem geschuetzten Bereich?
//STRIP001 	FASTBOOL IsInProtectSect() const;
};


// defines fuers GetCharCount
#define GETCHARCOUNT_NONE		0
#define GETCHARCOUNT_PARA 		1
#define GETCHARCOUNT_SECTION 	2


// ReturnWerte von SetCrsr (werden verodert)
const int 	CRSR_NOERROR =	0x00,
            CRSR_POSOLD =	0x01,	// Cursor bleibt an alter Doc-Position
            CRSR_POSCHG =	0x02;	// Position vom Layout veraendert




// die Cursor - Shell
class SwCrsrShell : public ViewShell, public SwModify
{
    friend class SwCallLink;
    friend class SwVisCrsr;
    friend class SwSelPaintRects;
    friend class SwChgLinkFlag;

    //Braucht den Crsr als IntrnlCrsr.
    friend void GetTblSel( const SwCrsrShell&, SwSelBoxes& rBoxes,
                           const SwTblSearchType );
    friend BOOL GetAutoSumSel( const SwCrsrShell&, SwCellFrms& );

public:     // public, damit defaultet werden kann !!

    /* ein enum fuer den Aufruf von UpdateCrsr */
    enum CrsrFlag {
        UPDOWN		= (1 << 0),     // Up/Down auf Spalte halten
        SCROLLWIN	= (1 << 1),     // Window Scrollen
        CHKRANGE	= (1 << 2),     // ueberpruefen von ueberlappenden PaM's
        NOCALRECT 	= (1 << 3),		// CharRect nicht neu berechnen
        READONLY	= (1 << 4)		// Sichtbar machen trotz Readonly
    };

private:

    SwRect	aCharRect;			// Char-SRectangle auf dem der Cursor steht
    Point	aCrsrHeight;     	// Hohe&Offset von sichtbaren Cursor
    Point 	aOldRBPos;			// Right/Bottom von letzter VisArea
                                // (wird im Invalidate vom Cursor benutzt)


    // um event. Macro was anhaengt auszufuehren.
    Link aFlyMacroLnk;			// Link will be called, if the Crsr is set
                                // into a fly. A macro can be then becalled
    Link aChgLnk;				// link will be called by every attribut/
                                // format changes at cursor position.
    Link aGrfArrivedLnk;		// Link calls to UI if a grafik is arrived


    SwShellCrsr* pCurCrsr; 		// der aktuelle Cursor
    SwShellCrsr* pCrsrStk;		// Stack fuer den Cursor
    SwVisCrsr *pVisCrsr;        // der Sichtbare-Cursor

    SwShellTableCrsr* pTblCrsr;	// Tabellen-Crsr; nur in Tabellen, wenn
                                // die Selection ueber 2 Spalten liegt

    SwNodeIndex* pBoxIdx;		// fuers erkennen der veraenderten
    SwTableBox* pBoxPtr;		// Tabellen-Zelle

    long nUpDownX;				// versuche den Cursor bei Up/Down immer in
                                // der gleichen Spalte zu bewegen
    long nLeftFrmPos;
    ULONG nAktNode;				// save CursorPos at Start-Action
    xub_StrLen nAktCntnt;
    USHORT nAktNdTyp;
    bool bAktSelection;

    /*
     * Mit den Methoden SttCrsrMove und EndCrsrMove wird dieser Zaehler
     * Inc-/Decrementiert. Solange der Zaehler ungleich 0 ist, erfolgt
     * auf den akt. Cursor kein Update. Dadurch koennen "komplizierte"
     * Cursorbewegungen (ueber Find()) realisiert werden.
     */
    USHORT nCrsrMove;
    USHORT nBasicActionCnt;		// Actions, die vom Basic geklammert wurden
    CrsrMoveState eMvState;		// Status fuers Crsr-Travelling - GetCrsrOfst

    BOOL bHasFocus : 1;         // Shell ist in einem Window "aktiv"
    BOOL bSVCrsrVis : 1;		// SV-Cursor Un-/Sichtbar
    BOOL bChgCallFlag : 1;		// Attributaenderung innerhalb von
                                // Start- und EndAction
    BOOL bVisPortChgd : 1;		// befindet sich im VisPortChg-Aufruf
                                // (wird im Invalidate vom Cursor benutzt)

    BOOL bCallChgLnk : 1;		// Flag fuer abgeleitete Klassen:
                                // TRUE -> ChgLnk callen
                                // Zugriff nur ueber SwChgLinkFlag
    BOOL bAllProtect : 1;		// Flag fuer Bereiche
                                // TRUE -> alles geschuetzt / versteckt
    BOOL bInCMvVisportChgd : 1;	// Flag fuer CrsrMoves
                                // TRUE -> die Sicht wurde verschoben
    BOOL bGCAttr : 1;			// TRUE -> es existieren nichtaufgespannte Attr.
    BOOL bIgnoreReadonly : 1;	// TRUE -> Beim naechsten EndAction trotz
                                // Readonly den Crsr sichtbar machen.
    BOOL bSelTblCells : 1;		// TRUE -> Zellen uebers InputWin selektieren
    BOOL bAutoUpdateCells : 1;	// TRUE -> Zellen werden autoformatiert
    BOOL bBasicHideCrsr : 1;	// TRUE -> HideCrsr vom Basic
    BOOL bSetCrsrInReadOnly : 1;// TRUE -> Cursor darf in ReadOnly-Bereiche
    BOOL bOverwriteCrsr : 1;	// TRUE -> show Overwrite Crsr
    // OD 11.02.2003 #100556# - flag to allow/avoid execution of marcos (default: true)
    bool mbMacroExecAllowed : 1;

    void UpdateCrsr( USHORT eFlags
                            =SwCrsrShell::SCROLLWIN|SwCrsrShell::CHKRANGE,
                     BOOL bIdleEnd = FALSE );

//STRIP001 	void _ParkPams( SwPaM* pDelRg, SwShellCrsr** ppDelRing );

//STRIP001     FASTBOOL LeftRight( BOOL, USHORT, USHORT, BOOL );
//STRIP001 	FASTBOOL UpDown( BOOL, USHORT );
//STRIP001 	FASTBOOL LRMargin( BOOL, BOOL bAPI = FALSE );
    FASTBOOL IsAtLRMargin( BOOL, BOOL bAPI = FALSE ) const;
     FASTBOOL SttEndDoc( BOOL bStt );

#ifdef BIDI
    short GetTextDirection( const Point* pPt = 0 ) const;
#endif

typedef FASTBOOL (SwCursor:: *FNCrsr)();
//STRIP001 	FASTBOOL CallCrsrFN( FNCrsr );

//STRIP001 	const SwRedline* _GotoRedline( USHORT nArrPos, BOOL bSelect );

protected:

    CRSR_INLINE SwMoveFnCollection* MakeFindRange( USHORT, USHORT, SwPaM* ) const;

    /*
     * Compare-Methode for the StackCursor and the current Cursor.
     * The Methods return -1, 0, 1 for lower, equal, greater. The enum
     * CrsrCompareType says which position is compared.
     */
    enum CrsrCompareType {
        StackPtStackMk,
        StackPtCurrPt,
        StackPtCurrMk,
        StackMkCurrPt,
        StackMkCurrMk,
        CurrPtCurrMk
    };
//STRIP001 	int CompareCursor( CrsrCompareType eType ) const;

    USHORT IncBasicAction()				{ return ++nBasicActionCnt; }
    USHORT DecBasicAction()				{ return --nBasicActionCnt; }

    // Setzt alle PaMs in OldNode auf NewPos + Offset
//STRIP001 	void PaMCorrAbs(const SwNodeIndex &rOldNode, const SwPosition &rNewPos,
//STRIP001 					const xub_StrLen nOffset = 0 );
    // Setzt alle PaMs im Bereich von [StartNode, EndNode] nach NewPos
//STRIP001 	void PaMCorrAbs(const SwNodeIndex &rStartNode, const SwNodeIndex &rEndNode,
//STRIP001 					const SwPosition &rNewPos );

public:
    TYPEINFO();
    SwCrsrShell( SwDoc& rDoc, Window *pWin,
                SwRootFrm * = 0, const SwViewOption *pOpt = 0 );
    // verkleideter Copy-Constructor
    SwCrsrShell( SwCrsrShell& rShell, Window *pWin );
    virtual ~SwCrsrShell();

    virtual void Modify( SfxPoolItem *pOld, SfxPoolItem *pNew);

    // neuen Cusror erzeugen und den alten anhaengen
    SwPaM * CreateCrsr();
    // loesche den aktuellen Cursor und der folgende wird zum Aktuellen
//STRIP001 	FASTBOOL DestroyCrsr();
    // TableCursor in normale Cursor verwandeln, Tablemode aufheben
//STRIP001 	void TblCrsrToCursor();

    SwPaM* GetCrsr( FASTBOOL bMakeTblCrsr = TRUE ) const;
    CRSR_INLINE SwCursor* GetSwCrsr( FASTBOOL bMakeTblCrsr = TRUE ) const;
    // nur den akt. Cursor returnen
          SwShellCrsr* _GetCrsr()  						{ return pCurCrsr; }
    const SwShellCrsr* _GetCrsr() const 				{ return pCurCrsr; }

    // uebergebenen Cursor anzeigen - fuer UNO
    void	SetSelection(const SwPaM& rCrsr);

    // alle Cursor aus den ContentNodes entfernen und auf 0 setzen.
    // Wurde aus der FEShell hierher verschoben.
//STRIP001 	void ParkCrsr( const SwNodeIndex &rIdx );

    // gebe den akt. Cursor-Stack zurueck.
    // ( Wird in der EditShell beim Loeschen von Inhalten benoetigt! )
    CRSR_INLINE SwPaM* GetStkCrsr() const;

    // Start der Klammerung, SV-Cursor und selektierte Bereiche hiden
    void StartAction();
    // Ende der Klammerung, SV-Cursor und selektierte Bereiche anzeigen
    void EndAction( const BOOL bIdleEnd = FALSE );

    USHORT GetBasicActionCnt() const 	{ return nBasicActionCnt; }

    // Basiscursortravelling
    long GetUpDownX() const 			{ return nUpDownX; }

//STRIP001     FASTBOOL Left( USHORT nCnt, USHORT nMode, BOOL bAllowVisual = FALSE )
//STRIP001                                 { return LeftRight( TRUE, nCnt, nMode, bAllowVisual ); }
//STRIP001     FASTBOOL Right( USHORT nCnt, USHORT nMode, BOOL bAllowVisual = FALSE )
//STRIP001                                 { return LeftRight( FALSE, nCnt, nMode, bAllowVisual ); }
//STRIP001 	FASTBOOL Up( USHORT nCnt = 1 )		{ return UpDown( TRUE, nCnt ); }
//STRIP001 	FASTBOOL Down( USHORT nCnt = 1 )	{ return UpDown( FALSE, nCnt ); }
//STRIP001 	FASTBOOL LeftMargin()				{ return LRMargin( TRUE ); }
//STRIP001 	FASTBOOL RightMargin(BOOL bAPI = FALSE)	{ return LRMargin( FALSE, bAPI ); }
    FASTBOOL SttDoc()					{ return SttEndDoc( TRUE ); }
    FASTBOOL EndDoc()					{ return SttEndDoc( FALSE ); }

//STRIP001 	FASTBOOL MovePage( SwWhichPage, SwPosPage );
//STRIP001 	FASTBOOL MovePara( SwWhichPara, SwPosPara );
//STRIP001 	FASTBOOL MoveSection( SwWhichSection, SwPosSection );
//STRIP001 	FASTBOOL MoveTable( SwWhichTable, SwPosTable );
//STRIP001 	FASTBOOL MoveColumn( SwWhichColumn, SwPosColumn );
//STRIP001 	FASTBOOL MoveRegion( SwWhichRegion, SwPosRegion );

    // die Suchfunktionen
//STRIP001 	ULONG Find( const com::sun::star::util::SearchOptions& rSearchOpt,
//STRIP001 				SwDocPositions eStart, SwDocPositions eEnde,
//STRIP001 	                BOOL& bCancel,
//STRIP001 				FindRanges eRng, int bReplace = FALSE );

//STRIP001 	ULONG Find( const SwTxtFmtColl& rFmtColl,
//STRIP001 				SwDocPositions eStart, SwDocPositions eEnde,
//STRIP001 	            BOOL& bCancel,
//STRIP001 				FindRanges eRng, const SwTxtFmtColl* pReplFmt = 0 );

//STRIP001 	ULONG Find( const SfxItemSet& rSet, FASTBOOL bNoCollections,
//STRIP001 				SwDocPositions eStart, SwDocPositions eEnde,
//STRIP001 	                BOOL& bCancel,
//STRIP001 				FindRanges eRng,
//STRIP001 				const com::sun::star::util::SearchOptions* pSearchOpt = 0,
//STRIP001 				const SfxItemSet* rReplSet = 0 );

    // Positionieren des Cursors
    // returnt
    //	CRSR_POSCHG: wenn der ob der SPoint vom Layout korrigiert wurde.
    //	CRSR_POSOLD: wenn der Crsr nicht veraendert wurde
    int SetCrsr( const Point &rPt, BOOL bOnlyText = FALSE );

    /*
     * Benachrichtung, dass der sichtbare Bereich sich geaendert
     * hat. aVisArea wird neu gesetzt, anschliessend wird
     * gescrollt. Das uebergebene Rectangle liegt auf
     * Pixelgrenzen, um Pixelfehler beim Scrollen zu vermeiden.
     */
//STRIP001 	virtual void VisPortChgd( const SwRect & );

    /*
     * Virtuelle PaintMethode, damit die Selection nach dem Paint wieder
     * sichtbar wird.
     */
//STRIP001 	void Paint( const Rectangle & rRect );

    // Bereiche
//STRIP001 	CRSR_INLINE void SetMark();
//STRIP001 	CRSR_INLINE FASTBOOL HasMark();

//STRIP001 	void ClearMark();

    /**
       Ensure point and mark of the current PaM are in a specific order.

       @param bPointFirst TRUE: If the point is behind the mark then
       swap the PaM. FALSE: If the mark is behind the point then swap
       the PaM.
    */
    void NormalizePam(BOOL bPointFirst = TRUE);

//STRIP001 	void SwapPam();
//STRIP001 	FASTBOOL ChgCurrPam( const Point & rPt,
//STRIP001 					 BOOL bTstOnly = TRUE,		//Nur testen, nicht setzen
//STRIP001 					 BOOL bTstHit  = FALSE );	//Nur genaue Treffer
//STRIP001 	void KillPams();

    // erzeuge eine Kopie vom Cursor und speicher diese im Stack
//STRIP001 	void Push();
    /*
     *  Loescht einen Cursor (gesteuert durch bOldCrsr)
     * 		- vom Stack oder	( bOldCrsr = TRUE )
     * 		- den aktuellen und der auf dem Stack stehende wird zum aktuellen
     *
     * 	Return:  es war auf dem Stack noch einer vorhanden
     */
//STRIP001 	FASTBOOL Pop( BOOL bOldCrsr = TRUE );
    /*
     * Verbinde zwei Cursor miteinander.
     * Loesche vom Stack den obersten und setzen dessen Mark im Aktuellen.
     */
//STRIP001 	void Combine();

#if defined( PRODUCT )
    void SttCrsrMove() { ++nCrsrMove; StartAction(); }
    void EndCrsrMove( const BOOL bIdleEnd = FALSE )
            { EndAction( bIdleEnd ); --nCrsrMove; }
#else
    void SttCrsrMove();
    void EndCrsrMove( const BOOL bIdleEnd = FALSE );
#endif

    /*
     * Beim Abgeben des Focuses werden die selektierten Bereiche nicht mehr
     * angezeigt; andererseits beim Erhalten des Focuses, werden alle selek-
     * tierten Bereiche wieder angezeigt. (Bereiche muessen neu berechnet
     * werden!)
     */
    BOOL HasShFcs() const { return bHasFocus; }
//STRIP001 	void ShLooseFcs();
    void ShGetFcs( BOOL bUpdate = TRUE );

    // Methoden zum Anzeigen bzw. Verstecken des sichtbaren Text-Cursors
    void ShowCrsr();
    void HideCrsr();
    // Methoden zum Anzeigen bzw. Verstecken der selektierten Bereiche mit
    // dem sichtbaren Cursor
    void ShowCrsrs( BOOL bCrsrVis );
//STRIP001 	void HideCrsrs();
    // Methoden zum Anzeigen bzw. Verstecken der selektierten Bereiche mit
    // dem sichtbaren Cursor
//STRIP001 	void BasicShowCrsrs()
//STRIP001 		{ bBasicHideCrsr = FALSE; bSVCrsrVis = TRUE; ShowCrsrs(TRUE); }
//STRIP001 	void BasicHideCrsrs()
//STRIP001 		{ HideCrsrs(); bBasicHideCrsr = TRUE; bSVCrsrVis = FALSE; }
//STRIP001 	FASTBOOL IsBasicHideCrsr() const { return bBasicHideCrsr; }

    FASTBOOL IsOverwriteCrsr() const { return bOverwriteCrsr; }
    void SetOverwriteCrsr( FASTBOOL bFlag ) { bOverwriteCrsr = bFlag; }

    // gebe den aktuellen Frame, in dem der Cursor steht, zurueck
    SwCntntFrm *GetCurrFrm( const BOOL bCalcFrm = TRUE ) const;

    //TRUE wenn der Crsr wenn der Crsr wegen Readonly gehidet ist,
    //FALSE wenn der arbeitet (trotz Readonly).
    FASTBOOL IsCrsrReadonly() const;
    // Cursor steht in etwas geschuetztem oder in die Selektion umspannt
    // etwas geschuetztes.
    FASTBOOL HasReadonlySel() const;
    // darf der Cursor in ReadOnlyBereiche?
    FASTBOOL IsReadOnlyAvailable() const { return bSetCrsrInReadOnly; }
    void SetReadOnlyAvailable( BOOL bFlag );
//STRIP001 	FASTBOOL IsOverReadOnlyPos( const Point& rPt ) const;

    // Methoden fuer aFlyMacroLnk
    void 		SetFlyMacroLnk( const Link& rLnk ) { aFlyMacroLnk = rLnk; }
    const Link& GetFlyMacroLnk() const 			   { return aFlyMacroLnk; }

    // Methoden geben/aendern den Link fuer die Attribut/Format-Aenderungen
    void 		SetChgLnk( const Link &rLnk ) { aChgLnk = rLnk; }
    const Link& GetChgLnk() const 			  { return aChgLnk; }

    // Methoden geben/aendern den Link fuers "Grafik vollstaendig geladen"
    void 		SetGrfArrivedLnk( const Link &rLnk ) { aGrfArrivedLnk = rLnk; }
    const Link& GetGrfArrivedLnk() const 			 { return aGrfArrivedLnk; }

    //ChgLink callen, innerhalb einer Action wird der Ruf verzoegert.
    void CallChgLnk();

    // Abfrage, ob der aktuelle Cursor eine Selektion aufspannt,
    // also, ob Mark gesetzt und SPoint und Mark unterschiedlich sind.
    FASTBOOL HasSelection() const;

    // Abfrage, ob ueberhaupt eine Selektion existiert, sprich der akt. Cursor
    // aufgespannt oder nicht der einzigste ist.
    CRSR_INLINE FASTBOOL IsSelection() const;
        // returns if multiple cursors are available
    CRSR_INLINE FASTBOOL IsMultiSelection() const;

    // Abfrage, ob ein kompletter Absatz selektiert wurde
//STRIP001 	FASTBOOL IsSelFullPara() const;
    // Abfrage, ob die Selektion in einem Absatz ist
    CRSR_INLINE FASTBOOL IsSelOnePara() const;

    //Sollte fuer das Clipboard der WaitPtr geschaltet werden.
//STRIP001 	FASTBOOL ShouldWait() const;

    /*
     * liefert das SRectangle, auf dem der Cursor steht.
     */
    const SwRect &GetCharRect() const { return aCharRect; }
    /*
     * liefert zurueck, ob der Cursor sich ganz oder teilweise im
     * sichtbaren Bereich befindet.
     */
    FASTBOOL IsCrsrVisible() const { return VisArea().IsOver( GetCharRect() ); }

    // gebe die aktuelle Seitennummer zurueck:
    // TRUE:  in der der Cursor steht
    // FALSE: die am oberen Rand sichtbar ist
    void GetPageNum( USHORT &rnPhyNum, USHORT &rnVirtNum,
                     BOOL bAtCrsrPos = TRUE, const BOOL bCalcFrm = TRUE );
    // bestimme in welche Richtung "leere Seiten" behandelt werden!
    // (wird benutzt im PhyPage.. )
//STRIP001 	USHORT GetNextPrevPageNum( BOOL bNext = TRUE );

    // setze den Cursor auf die Seite "nPage" an den Anfang
//STRIP001 	FASTBOOL GotoPage( USHORT nPage );

    // gebe alle Dokumentseiten zurueck
    USHORT GetPageCnt();

    // Gehe zur naechsten Selection
//STRIP001 	FASTBOOL GoNextCrsr();
    // gehe zur vorherigen Selection
//STRIP001 	FASTBOOL GoPrevCrsr();

    // am CurCrsr.SPoint
//STRIP001 	FASTBOOL SetBookmark( const KeyCode&, const String& rName,
//STRIP001 				const String& rShortName, BOOKMARK_TYPE eMark  = BOOKMARK );
//STRIP001 	FASTBOOL GotoBookmark( USHORT );	// setzt CurCrsr.SPoint
//STRIP001 	FASTBOOL GotoBookmark( USHORT nPos, BOOL bAtStart ); //
//STRIP001 	FASTBOOL GoNextBookmark(); // TRUE, wenn's noch eine gab
//STRIP001 	FASTBOOL GoPrevBookmark();
//STRIP001 	USHORT GetBookmarkCnt(BOOL bBkmrk = FALSE) const;
//STRIP001 	SwBookmark& GetBookmark( USHORT, BOOL bBkmrk = FALSE );
//STRIP001 	void DelBookmark( USHORT );
//STRIP001 	void DelBookmark( const String& rName );
    USHORT FindBookmark( const String& rName );
        // erzeugt einen eindeutigen Namen. Der Name selbst muss vorgegeben
        // werden, es wird dann bei gleichen Namen nur durchnumeriert.
//STRIP001 	void MakeUniqueBookmarkName( String& rNm );

    // aktualisiere den Crsrs, d.H. setze ihn wieder in den Content.
    // Das sollte nur aufgerufen werden, wenn der Cursor z.B. beim
    // Loeschen von Rahmen irgendwohin gesetzt wurde. Die Position
    // ergibt sich aus seiner aktuellen Position im Layout !!
    void UpdateCrsrPos();

    // returne den am akt. Cursor selektierten Text. Dieser wird mit
    // Felder etc. aufgefuellt!!
//STRIP001 	String GetSelTxt() const;
    // gebe nur den Text ab der akt. Cursor Position zurueck (bis zum NodeEnde)
//STRIP001 	String GetText() const;
    // retrurne die Anzahl der selektierten Zeichen.
    // Falls keine Selektion vorliegt entscheided nType was selektiert wird
    // bIntrnlChar besagt ob interne Zeichen erhalten bleiben (TRUE) oder
    // ob sie expandiert werden (z.B Felder/...)
//STRIP001 	ULONG GetCharCount( USHORT nType, BOOL bIntrnlChrs = TRUE ) const;

    // pruefe ob vom aktuellen Crsr der SPoint/Mark in einer Tabelle stehen
    CRSR_INLINE const SwTableNode* IsCrsrInTbl( BOOL bIsPtInTbl = TRUE ) const;
    // erfrage die Document - Layout - Position vom akt. Crsr
    CRSR_INLINE Point& GetCrsrDocPos( BOOL bPoint = TRUE ) const;
    CRSR_INLINE FASTBOOL IsCrsrPtAtEnd() const;

    CRSR_INLINE const 	SwPaM* GetTblCrs() const;
     CRSR_INLINE 		SwPaM* GetTblCrs();

//STRIP001 	FASTBOOL IsTblComplex() const;
//STRIP001 	FASTBOOL IsTblComplexForChart();
    // erfrage die akt. TabellenSelektion als Text
    String GetBoxNms() const;

    // setze Crsr in die naechsten/vorherigen Celle
//STRIP001 	FASTBOOL GoNextCell( BOOL bAppendLine = TRUE );
//STRIP001 	FASTBOOL GoPrevCell();
    // gehe zu dieser Box (wenn vorhanden und in Tabelle!)
//STRIP001 	FASTBOOL GotoTblBox( const String& rName );
    FASTBOOL GotoTable( const String& rName );

    // select a table row, column or box (based on the current cursor)
//STRIP001 	FASTBOOL SelTblRow();
//STRIP001 	FASTBOOL SelTblCol();
//STRIP001     FASTBOOL SelTblBox();

    // zum naechsten/vorhergehenden Punkt auf gleicher Ebene
//STRIP001 	FASTBOOL GotoNextNum();
//STRIP001 	FASTBOOL GotoPrevNum();

        // zu diesem Gliederungspunkt
//STRIP001 	FASTBOOL GotoOutline( const String& rName );
        // zum naechsten/vorhergehenden oder angegebenen OultineNode
//STRIP001 	void GotoOutline( USHORT nIdx );
        // suche die "Outline-Position" im Nodes-Array vom akt. Kaiptel
//STRIP001 	USHORT GetOutlinePos( BYTE nLevel = UCHAR_MAX );
        // selektiere den angeben Bereich von OutlineNodes. Optional
        // inclusive der Childs. Die USHORT sind die Positionen im
        // OutlineNds-Array!! (EditShell)
//STRIP001 	FASTBOOL MakeOutlineSel( USHORT nSttPos, USHORT nEndPos,
//STRIP001 						BOOL bWithChilds = FALSE );

//STRIP001 	FASTBOOL GotoNextOutline();			// naechster Node mit Outline-Num.
//STRIP001 	FASTBOOL GotoPrevOutline();			// vorheriger Node mit Outline-Num.

        // ist der Crsr in einer Tabelle und ist die Selection ueber
        // zwei Spalten
    FASTBOOL IsTableMode() const { return 0 != pTblCrsr; }

        // erfrage den Tabellen Crsr; ausserhalb von Tabellen immer 0
    const SwShellTableCrsr* GetTableCrsr() const { return pTblCrsr; }
    SwShellTableCrsr* GetTableCrsr() { return pTblCrsr; }
//STRIP001 	USHORT UpdateTblSelBoxes();

//STRIP001 	FASTBOOL GotoFtnTxt();		// springe aus dem Content zur Fussnote
//STRIP001 	FASTBOOL GotoFtnAnchor();	// springe aus der Fussnote zum Anker
//STRIP001 	FASTBOOL GotoNextFtnAnchor();
//STRIP001 	FASTBOOL GotoPrevFtnAnchor();
//STRIP001 	FASTBOOL GotoNextFtnCntnt();
//STRIP001 	FASTBOOL GotoPrevFtnCntnt();

//STRIP001 	FASTBOOL GotoFlyTxt();			// springe aus dem Content zum "naechsten" Rahmen
//STRIP001 	FASTBOOL GotoFlyAnchor();		// springe aus dem Rahmen zum Anker
//STRIP001 	FASTBOOL GotoHeaderTxt();		// springe aus dem Content zum Header
//STRIP001 	FASTBOOL GotoFooterTxt();		// springe aus dem Content zum Footer
    // springe in den Header/Footer des angegebenen oder akt. PageDesc
//STRIP001 	FASTBOOL SetCrsrInHdFt( USHORT nDescNo = USHRT_MAX,
//STRIP001 							FASTBOOL bInHeader = TRUE );
    // is point of cursor in header/footer. pbInHeader return TRUE if it is
    // in a headerframe otherwise in a footerframe
//STRIP001 	FASTBOOL IsInHeaderFooter( FASTBOOL* pbInHeader = 0 ) const;

    // springe zum naechsten Verzeichnis [mit dem Namen]
//STRIP001 	FASTBOOL GotoNextTOXBase( const String* = 0 );
    // springe zum vorherigen Verzeichnis [mit dem Namen]
//STRIP001 	FASTBOOL GotoPrevTOXBase( const String* = 0 );
//STRIP001 	FASTBOOL GotoTOXMarkBase();		// springe zum Verzeichnis vom TOXMark
    // springe zum naechsten (vorherigen) Verzeichniseintrag
//STRIP001 	FASTBOOL GotoNxtPrvTOXMark( BOOL bNext = TRUE );
    // Zur naechsten/ vorherigen Verzeichnismarke dieses Typs traveln
//STRIP001 	const SwTOXMark& GotoTOXMark( const SwTOXMark& rStart, SwTOXSearch eDir );

    // springe zum naechsten (vorherigen) Tabellenformel
    // optional auch nur zu kaputten Formeln springen
//STRIP001 	FASTBOOL GotoNxtPrvTblFormula( BOOL bNext = TRUE,
//STRIP001 									BOOL bOnlyErrors = FALSE );
    // jump to the next / previous hyperlink - inside text and also
    // on graphics
//STRIP001 	FASTBOOL SelectNxtPrvHyperlink( BOOL bNext = TRUE );

    // springe zu dieser Refmark
//STRIP001 	FASTBOOL GotoRefMark( const String& rRefMark, USHORT nSubType = 0,
//STRIP001 							USHORT nSeqNo = 0 );

    // hole vom Start/Ende der akt. Selection das nte Zeichen
//STRIP001 	sal_Unicode GetChar( BOOL bEnd = TRUE, long nOffset = 0 );
    // erweiter die akt. Selection am Anfang/Ende um n Zeichen
//STRIP001 	FASTBOOL ExtendSelection( BOOL bEnd = TRUE, xub_StrLen nCount = 1 );
    // setze nur den sichtbaren Cursor an die angegebene Dokument-Pos.
    // returnt FALSE: wenn der ob der SPoint vom Layout korrigiert wurde.
    // (wird zum Anzeigen von Drag&Drop/Copy-Cursor benoetigt)
//STRIP001 	FASTBOOL SetVisCrsr( const Point &rPt );
    CRSR_INLINE void UnSetVisCrsr();

    // springe zum nachsten/vorherigen Feld des entsprechenden Types
//STRIP001 	FASTBOOL MoveFldType( const SwFieldType* pFldType, BOOL bNext,
//STRIP001 											USHORT nSubType = USHRT_MAX,
//STRIP001 											USHORT nResType = USHRT_MAX );
    // springe genau zu diesem Feld
//STRIP001 	FASTBOOL GotoFld( const SwFmtFld& rFld );

    // returne die Anzahl der Cursor im Ring (Flag besagt ob man nur
    // aufgepspannte haben will - sprich etwas selektiert ist (Basic))
    USHORT GetCrsrCnt( BOOL bAll = TRUE ) const;

    // Char Travelling - Methoden (in crstrvl1.cxx)
//STRIP001 	FASTBOOL IsStartWord()const;
//STRIP001 	FASTBOOL IsEndWord() const;
//STRIP001 	FASTBOOL IsInWord() const;
//STRIP001 	FASTBOOL GoStartWord();
//STRIP001 	FASTBOOL GoEndWord();
//STRIP001 	FASTBOOL GoNextWord();
//STRIP001 	FASTBOOL GoPrevWord();
//STRIP001 	FASTBOOL GoNextSentence();
//STRIP001 	FASTBOOL GoPrevSentence();
//STRIP001 	FASTBOOL SelectWord( const Point* pPt = 0 );

    // Abfrage vom CrsrTravelling Status
    CrsrMoveState GetMoveState() const { return eMvState; }

    // Position vom akt. Cursor erfragen
//STRIP001 	FASTBOOL IsStartOfDoc() const;
//STRIP001 	FASTBOOL IsEndOfDoc() const;
//STRIP001 	FASTBOOL IsSttPara() const;
//STRIP001 	FASTBOOL IsEndPara() const;
    FASTBOOL IsAtLeftMargin()	const		{ return IsAtLRMargin( TRUE ); }
    FASTBOOL IsAtRightMargin(BOOL bAPI = FALSE) const	{ return IsAtLRMargin( FALSE, bAPI ); }

    // loesche alle erzeugten Crsr, setze den Tabellen-Crsr und den letzten
    // Cursor auf seinen TextNode (oder StartNode?).
    // Beim naechsten ::GetCrsr werden sie wieder alle erzeugt.
    // Wird fuers Drag&Drop/ClipBorad-Paste in Tabellen benoetigt.
//STRIP001 	FASTBOOL ParkTblCrsr();

    // erfrage die selektierte "Region" aller Cursor (fuer D&D auf Mac)
    Region GetCrsrRegion() const;

    // gibt es nicht aufgespannte Attribute?
    FASTBOOL IsGCAttr() const { return bGCAttr; }
    void	ClearGCAttr() {	bGCAttr = FALSE; }
    void	UpdateAttr() {	bGCAttr = TRUE; }

    // ist das gesamte Dokument geschuetzt/versteckt?? (fuer UI,..)
    FASTBOOL IsAllProtect() const { return bAllProtect; }

#ifdef SW_CRSR_TIMER
    // setze das Flag am VisCrsr, ob dieser ueber Timer getriggert (TRUE)
    // oder direkt (FALSE) angezeigt wird. (default ist Timer getriggert)
//STRIP001 	FASTBOOL ChgCrsrTimerFlag( BOOL bTimerOn = TRUE );
#endif

    // steht der Curor auf einem "Symbol"-Zeichen
//STRIP001 	FASTBOOL IsInSymbolFont() const;

    BOOL BasicActionPend() const 	{ return nBasicActionCnt != nStartAction; }

        // springe zum benannten Bereich
//STRIP001 	FASTBOOL GotoRegion( const String& rName );

    // zeige die aktuelle Selektion an
    virtual void MakeSelVisible();

    // setzte den Cursor auf einen NICHT geschuetzten/versteckten Node
//STRIP001 	FASTBOOL FindValidCntntNode( BOOL bOnlyText = FALSE );

//STRIP001 	FASTBOOL GetContentAtPos( const Point& rPt,
//STRIP001 							SwContentAtPos& rCntntAtPos,
//STRIP001 							FASTBOOL bSetCrsr = FALSE,
//STRIP001 							SwRect* pFldRect = 0 );

//STRIP001     FASTBOOL IsPageAtPos( const Point &rPt ) const;

        // Attribut selelktieren
//STRIP001 	FASTBOOL SelectTxtAttr( USHORT nWhich, BOOL bExpand = FALSE,
//STRIP001 							const SwTxtAttr* pAttr = 0 );
//STRIP001 	FASTBOOL GotoINetAttr( const SwTxtINetFmt& rAttr );
//STRIP001 	const SwFmtINetFmt* FindINetAttr( const String& rName ) const;

    FASTBOOL CheckTblBoxCntnt( const SwPosition* pPos = 0 );
    void SaveTblBoxCntnt( const SwPosition* pPos = 0 );
    void ClearTblBoxCntnt();
    FASTBOOL EndAllTblBoxEdit();

    // wird gerufen, wenn eine Tabellenselektion im UpdateCrsr erzeugt wird,
    // ohne das die UI davon etaws weiss
//STRIP001 	virtual void NewCoreSelection();

    void SetSelTblCells( BOOL bFlag )			{ bSelTblCells = bFlag; }
    BOOL IsSelTblCells() const 					{ return bSelTblCells; }

    BOOL IsAutoUpdateCells() const 				{ return bAutoUpdateCells; }
    void SetAutoUpdateCells( BOOL bFlag ) 		{ bAutoUpdateCells = bFlag; }

//STRIP001 	FASTBOOL GetShadowCrsrPos( const Point& rPt, SwFillMode eFillMode,
//STRIP001 							SwRect& rRect, SwHoriOrient& rOrient );
//STRIP001 	FASTBOOL SetShadowCrsrPos( const Point& rPt, SwFillMode eFillMode );

//STRIP001 	const SwRedline* SelNextRedline();
//STRIP001 	const SwRedline* SelPrevRedline();
//STRIP001 	const SwRedline* GotoRedline( USHORT nArrPos, BOOL bSelect = FALSE );

    // is cursor or the point in/over a vertical formatted text?
    FASTBOOL IsInVerticalText( const Point* pPt = 0 ) const;
#ifdef BIDI
    // is cursor or the point in/over a right to left formatted text?
    FASTBOOL IsInRightToLeftText( const Point* pPt = 0 ) const;
#endif

    // remove all invalid cursors
    void ClearUpCrsrs();

    // OD 11.02.2003 #100556# - set/get flag to allow/avoid execution of macros
    inline void SetMacroExecAllowed( const bool _bMacroExecAllowed )
    {
        mbMacroExecAllowed = _bMacroExecAllowed;
    }
    inline bool IsMacroExecAllowed()
    {
        return mbMacroExecAllowed;
    }
};


class SwChgLinkFlag
{
    BOOL bOldFlag;
    SwCrsrShell& rCrsrShell;
    long nLeftFrmPos;
public:
    SwChgLinkFlag( SwCrsrShell& rShell );
    ~SwChgLinkFlag();
};



// Cursor Inlines:

#if defined(PRODUCT) && !defined(WIN)

inline SwMoveFnCollection* SwCrsrShell::MakeFindRange(
            USHORT nStt, USHORT nEnd, SwPaM* pPam ) const
{
    DBG_ASSERT(0, "STRIP"); return NULL;//STRIP001 return pCurCrsr->MakeFindRange( (SwDocPositions)nStt, (SwDocPositions)nEnd, pPam );
}

inline SwCursor* SwCrsrShell::GetSwCrsr( FASTBOOL bMakeTblCrsr ) const
{
    return (SwCursor*)GetCrsr( bMakeTblCrsr );
}

inline SwPaM* SwCrsrShell::GetStkCrsr() const { return pCrsrStk; }

//STRIP001 inline void SwCrsrShell::SetMark() { pCurCrsr->SetMark(); }

//STRIP001 inline FASTBOOL SwCrsrShell::HasMark() { return( pCurCrsr->HasMark() ); }

/*N*/ inline FASTBOOL SwCrsrShell::IsSelection() const
/*N*/ {
/*N*/ 	return IsTableMode() || pCurCrsr->HasMark() ||
/*N*/ 			pCurCrsr->GetNext() != pCurCrsr;
/*N*/ }
inline FASTBOOL SwCrsrShell::IsMultiSelection() const
{
    return pCurCrsr->GetNext() != pCurCrsr;
}        

inline FASTBOOL SwCrsrShell::IsSelOnePara() const
{
    return pCurCrsr == pCurCrsr->GetNext() &&
           pCurCrsr->GetPoint()->nNode == pCurCrsr->GetMark()->nNode;
}

inline const SwTableNode* SwCrsrShell::IsCrsrInTbl( BOOL bIsPtInTbl ) const
{
    return pCurCrsr->GetNode( bIsPtInTbl )->FindTableNode();
}

inline FASTBOOL SwCrsrShell::IsCrsrPtAtEnd() const
{
    return pCurCrsr->End() == pCurCrsr->GetPoint();
}

inline Point& SwCrsrShell::GetCrsrDocPos( BOOL bPoint ) const
{
    return bPoint ? pCurCrsr->GetPtPos() : pCurCrsr->GetMkPos();
}

inline const SwPaM* SwCrsrShell::GetTblCrs() const
{
    return pTblCrsr;
}

inline SwPaM* SwCrsrShell::GetTblCrs()
{
    return pTblCrsr;
}

inline void SwCrsrShell::UnSetVisCrsr()
{
    pVisCrsr->Hide();
    pVisCrsr->SetDragCrsr( FALSE );
}

#endif


#endif 	// _CRSRSH_HXX
