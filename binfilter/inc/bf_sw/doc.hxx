/* -*- Mode: C++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */
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
#ifndef _DOC_HXX
#define _DOC_HXX

#define _SVSTDARR_STRINGSDTOR
#include <bf_svtools/svstdarr.hxx>

#include <vcl/timer.hxx>
#include <swtypes.hxx>
#include <ndarr.hxx>
#include <swatrset.hxx>
#include <toxe.hxx>   	  		// enums
#include <redlenum.hxx>   	  	// enums
#include <bkmrke.hxx>
#include <flyenum.hxx>
#include <itabenum.hxx>
#include <swdbdata.hxx>
#include <chcmprse.hxx>
#include <horiornt.hxx>
#include <com/sun/star/linguistic2/XSpellChecker1.hpp>
#include <com/sun/star/linguistic2/XHyphenatedWord.hpp>
#include <rtl/ref.hxx>

// OD 25.06.2003 #108784#
#include <bf_svx/svdtypes.hxx>
namespace com { namespace sun { namespace star {
namespace i18n {
    struct ForbiddenCharacters;    // comes from the I18N UNO interface
}
namespace uno {
    template < class > class Sequence;
}
}}}

namespace utl {
    class TransliterationWrapper;
}
namespace binfilter {
    class SvLinkSource;
}
class DateTime;
class JobSetup;
class Color;
class KeyCode;
class OutputDevice;
class Point;
class SbxArray;
class VirtualDevice;

namespace binfilter {
class SvEmbeddedObjectRef;
class SvStrings;
class SvxMacro;
class SvxMacroTableDtor;
class SvPersist;
class SvStorage;
class SvUShorts;
class SvUShortsSort;
class SvNumberFormatter;
class BfGraphicObject;

class SvxForbiddenCharactersTable;
class SwExtTextInput;

class EditFieldInfo;
class Outliner;
class SdrModel;
class SdrObject;
class SfxDocumentInfo;

class SfxPrinter;
class SvData;
class SvStringsSort;
class SvxAutoCorrDoc;
class SvxLinkManager;
class SvxBorderLine;
class SwAutoCompleteWord;
class SwAutoCorrExceptWord;
class SwBookmark;
class SwBookmarks;
class SwCalc;
class SwCellFrm;
class SwCharFmt;
class SwCharFmts;
class SwClient;
class SwConditionTxtFmtColl;
class SwCrsrShell;
class SwCursor;
class SwDBNameInfField;
class SwDocShell;
class SwDocUpdtFld;
class SwDrawFrmFmt;
class SwDrawView;
class SwEditShell;
class SwFieldType;
class SwFldTypes;
class SwFlyFrm;
class SwFlyFrmFmt;
class SwFmt;
class SwFmtCol;
class SwFmtINetFmt;
class SwFmtRefMark;
class SwFrmFmt;
class SwFrmFmts;
class SwFtnIdxs;
class SwFtnInfo;
class SwEndNoteInfo;

class SwGrfFmtColl;
class SwGrfFmtColls;
class SwLineNumberInfo;
class SwNewDBMgr;
class SwNoTxtNode;
class SwNodeIndex;
class SwNodeRange;
class SwNumRule;
class SwNumRuleTbl;
class SwPageDesc;
class SwPosFlyFrms;
class SwPagePreViewPrtData;
class SwRedline;
class SwRedlineTbl;
class SwRootFrm;
class SwRubyList;
class SwRubyListEntry;
class SwSectionFmt;
class SwSectionFmts;
class SwSelBoxes;
class SwSpzFrmFmts;
class SwTOXBase;
class SwTOXBaseSection;
class SwTOXMark;
class SwTOXMarks;
class SwTOXType;
class SwTOXTypes;
class SwTabCols;
class SwTable;
class SwTableAutoFmt;
class SwTableBox;
class SwTableBoxFmt;
class SwTableFmt;
class SwTableLineFmt;
class SwTableNode;
class SwTextBlocks;
class SwTxtFld;
class SwTxtFmtColl;
class SwTxtFmtColls;
class SwURLStateChanged;
class SwUnoCrsr;
class SwUnoCrsrTbl;
class ViewShell;
class _SetGetExpFld;
class SwDrawContact;
class SwLayouter;
class SdrView;
class SdrMarkList;
class SwAuthEntry;
class SwUnoCallBack;
class SwLayoutCache;
struct SwCallMouseEvent;
struct SwDocStat;
struct SwHash;
struct SwSortOptions;
struct SwDefTOXBase_Impl;
struct SwPrintData;
struct SwTableEntry;
// OD 26.06.2003 #108784#
class SdrPageView;


//PageDescriptor-Schnittstelle, Array hier wegen inlines.
typedef SwPageDesc* SwPageDescPtr;
SV_DECL_PTRARR_DEL( SwPageDescs, SwPageDescPtr, 4, 4 )

enum SwMoveFlags
{
   DOC_MOVEDEFAULT		= 0x00,
   DOC_MOVEALLFLYS		= 0x01,
   DOC_CREATEUNDOOBJ	= 0x02,
   DOC_MOVEREDLINES 	= 0x04
};

#define DUMMY_PARASPACEMAX 			0x04
#define DUMMY_PARASPACEMAX_AT_PAGES 0x20
#define DUMMY_TAB_COMPAT            0x40
#define DUMMY_USE_VIRTUAL_DEVICE    0x80
#define DUMMY_ADD_FLY_OFFSETS       0x01


#define SW_HYPH_ERROR		0
#define SW_HYPH_OK			1
#define SW_HYPH_ABORTED     2
#define SW_HYPH_CONTINUE	3

// forward declartion
void SetAllScriptItem( SfxItemSet& rSet, const SfxPoolItem& rItem );


class SwDoc
{
    friend class SwReader;	  // fuers Undo von Insert(SwDoc)
    friend class SwSwgReader; // Zugriff auf bDtor-Flag (wg. Loeschen v.Frames)
    friend class Sw3IoImp;	  // Zugriff u.a. auf den Drawing Layer

    friend void _InitCore();
    friend void _FinitCore();

    //Fuer das Loeschen der Header-/Footer-Formate
    //Implementierung und Benutzung in frmatr.cxx
    friend void DelHFFormat( SwClient *, SwFrmFmt * );

    //---------------- private Member --------------------------------

    // -------------------------------------------------------------------
    // die Objecte
    SwNodes		aNodes;   	  	  	  	// Inhalt des Dokumentes
    SwAttrPool	aAttrPool;				// der Attribut Pool
    SwPageDescs	aPageDescs;				// PageDescriptoren
    Link 		aOle2Link;				// OLE 2.0-Benachrichtigung
    AutoTimer	aIdleTimer; 			// der eigene IdleTimer
    Timer		aChartTimer; 			// der Timer fuers Update aller Charts
    Timer		aOLEModifiedTimer; 		// Timer for update modified OLE-Objecs
    SwDBData	aDBData;				// database descriptor
    ::com::sun::star::uno::Sequence <sal_Int8 > aRedlinePasswd;
    String		sTOIAutoMarkURL; 		// ::com::sun::star::util::URL of table of index AutoMark file
    SvStringsDtor aPatternNms;			// Array fuer die Namen der Dokument-Vorlagen


    // -------------------------------------------------------------------
    // die Pointer
                                //Defaultformate
    SwFrmFmt		*pDfltFrmFmt;
    SwFrmFmt		*pEmptyPageFmt;		// Format fuer die Default-Leerseite.
    SwFrmFmt		*pColumnContFmt; 	// Format fuer Spaltencontainer
    SwCharFmt		*pDfltCharFmt;
    SwTxtFmtColl	*pDfltTxtFmtColl;	// Defaultformatcollections
    SwGrfFmtColl	*pDfltGrfFmtColl;

    SwFrmFmts		*pFrmFmtTbl;		// Formattabellen
    SwCharFmts		*pCharFmtTbl;
    SwSpzFrmFmts	*pSpzFrmFmtTbl;
    SwSectionFmts	*pSectionFmtTbl;
    SwFrmFmts		*pTblFrmFmtTbl;		// spz. fuer Tabellen
    SwTxtFmtColls	*pTxtFmtCollTbl;	// FormatCollections
    SwGrfFmtColls	*pGrfFmtCollTbl;

    SwBookmarks 	*pBookmarkTbl;		//Bookmarks

    SwTOXTypes		*pTOXTypes;			// Verzeichnisse
    SwDefTOXBase_Impl * pDefTOXBases;	// defaults of SwTOXBase's

    SwRootFrm		*pLayout;			// Rootframe des spezifischen Layouts.
    SdrModel		*pDrawModel;		// StarView Drawing

    SwDocUpdtFld 	*pUpdtFlds;			// Struktur zum Field-Update
    SwFldTypes		*pFldTypes;			// Feldtypen
    SwNewDBMgr 		*pNewDBMgr;			// Pointer auf den neuen DBMgr fuer
                                        // Evaluierung der DB-Fields

    VirtualDevice   *pVirDev;           // can be used for formatting
    SfxPrinter      *pPrt;              // can be used for formatting
    SwPrintData     *pPrtData;          // Print configuration

    SwDoc			*pGlossaryDoc;		// Pointer auf das Glossary-Dokument. Dieses

    SwNumRule		*pOutlineRule;
    SwFtnInfo		*pFtnInfo;
    SwEndNoteInfo 	*pEndNoteInfo;
    SwLineNumberInfo *pLineNumberInfo;
    SwFtnIdxs		*pFtnIdxs;
    SwDocStat		*pDocStat;			// Statistic Informationen
    SfxDocumentInfo *pSwgInfo;			// Dokumentinformationen
    SvxMacroTableDtor *pMacroTable; 	// Tabelle der dokumentglobalen Macros

    SwDocShell		*pDocShell;			// Ptr auf die SfxDocShell vom Doc
    SvEmbeddedObjectRef* pDocShRef; 	// fuers Kopieren von OLE-Nodes (wenn keine
                                        // DocShell gesetzt ist, muss dieser
                                        // Ref-Pointer gesetzt sein!!!!)
    SvxLinkManager	*pLinkMgr;			// Liste von Verknuepften (Grafiken/DDE/OLE)

    SwAutoCorrExceptWord *pACEWord;		// fuer die automatische Uebernahme von
                                        // autokorrigierten Woertern, die "zurueck"
                                        // verbessert werden
    SwURLStateChanged *pURLStateChgd;	// SfxClient fuer Aenderungen in der
                                        // INetHistory
    SvNumberFormatter *pNumberFormatter;	// NumFormatter fuer die Tabellen/Felder
    SwNumRuleTbl 	*pNumRuleTbl;			// Liste aller benannten NumRules
    SwRedlineTbl	*pRedlineTbl;			// Liste aller Redlines
    String			*pAutoFmtRedlnComment;	// Kommentar fuer Redlines, die
                                        // uebers Autoformat eingefuegt werden
    SwUnoCrsrTbl	*pUnoCrsrTbl;

    SwPagePreViewPrtData *pPgPViewPrtData;		// Einzuege/Abstaende fuers
                                        // Drucken der Seitenansicht
    SwPaM			*pExtInputRing;

    SwLayouter		*pLayouter;		// ::com::sun::star::frame::Controller for complex layout formatting
                                    // like footnote/endnote in sections
    SwLayoutCache   *pLayoutCache;  // Layout cache to read and save with the
                                    // document for a faster formatting

    SwUnoCallBack	*pUnoCallBack;

    // table of forbidden characters of this document
    ::rtl::Reference<SvxForbiddenCharactersTable>	xForbiddenCharsTable;

    // -------------------------------------------------------------------
    // sonstige
    sal_uInt16 nAutoFmtRedlnCommentNo;	// SeqNo fuers UI-seitige zusammenfassen
                                    // von AutoFmt-Redlines. Wird vom SwAutoFmt
                                    // verwaltet!
    sal_uInt16	nLinkUpdMode;		// UpdateMode fuer Links
    sal_uInt16	nFldUpdMode;		// Mode fuer Felder/Charts automatisch aktualisieren

    SwRedlineMode eRedlineMode;		// aktueller Redline Modus
    SwCharCompressType eChrCmprType;	// for ASIAN: compress punctuation/kana

    sal_Int8	nLinkCt;			// wieviele kennen das Dokument
    sal_Int8	nLockExpFld;		// Wenn != 0 hat UpdateExpFlds() keine Wirkung

    SdrLayerID  nHeaven;            // LayerIds, Heaven == ueber dem Dokument
    SdrLayerID  nHell;              //           Hell   == unter dem Dokument
    SdrLayerID  nControls;          //           Controls == ganz oben
    // OD 25.06.2003 #108784# - Layer IDs for invisible 'heaven', 'hell' and 'controls'.
    // The corresponding layers will be permanently invisible and are corresponding
    // to the visible ones.
    // Needed for support of drawing objects in hidden header/footer and drawing
    // objects in other hidden area, e.g. hidden section.
    SdrLayerID  nInvisibleHeaven;
    SdrLayerID  nInvisibleHell;
    SdrLayerID  nInvisibleControls;

    sal_Bool	bGlossDoc		: 1;	//TRUE: ist ein Textbaustein Dokument
    sal_Bool	bModified		: 1;	//TRUE: Dokument ist veraendert
    sal_Bool	bDtor			: 1;	//TRUE: ist im SwDoc DTOR
                                        // leider auch temporaer von
                                        // SwSwgReader::InLayout(), wenn fehlerhafte
                                        //Frames geloescht werden muessen
    sal_Bool	bPageNums		: 1;	// TRUE: es gibt virtuelle Seitennummern
    sal_Bool	bLoaded 		: 1;	// TRUE: ein geladenes Doc
    sal_Bool	bUpdateExpFld	: 1;	// TRUE: Expression-Felder updaten
    sal_Bool	bNewDoc 		: 1;	// TRUE: neues Doc
    sal_Bool	bNewFldLst		: 1;	// TRUE: Felder-Liste neu aufbauen
    sal_Bool	bCopyIsMove 	: 1;	// TRUE: Copy ist ein verstecktes Move
    sal_Bool	bVisibleLinks	: 1;	// TRUE: Links werden sichtbar eingefuegt
    sal_Bool  	bBrowseMode		: 1;	// TRUE: Dokument im BrowseModus anzeigen
    sal_Bool  	bInReading		: 1;	// TRUE: Dokument wird gerade gelesen
    sal_Bool  	bUpdateTOX		: 1;	// TRUE: nach Dokument laden die TOX Updaten
    sal_Bool 	bInLoadAsynchron: 1;	// TRUE: Dokument wird gerade asynchron geladen
    sal_Bool 	bHTMLMode		: 1;	// TRUE: Dokument ist im HTMLMode
    sal_Bool	bHeadInBrowse	: 1;	// TRUE: Header sind im BrowseMode aktiviert
    sal_Bool	bFootInBrowse	: 1;	// TRUE: Footer sind im BrowseMode aktiviert
    sal_Bool 	bFrmBeepEnabled : 1;	// TRUE: Frames beepen wenn der Inhalt zu gross wird
    sal_Bool	bInCallModified : 1;	// TRUE: im Set/Reset-Modified Link
    sal_Bool	bIsGlobalDoc 	: 1;	// TRUE: es ist ein GlobalDokument
    sal_Bool   	bGlblDocSaveLinks : 1;	// TRUE: im GlobalDoc. gelinkte Sect. mit speichern
    sal_Bool	bIsLabelDoc 	: 1;	// TRUE: es ist ein Etiketten-Dokument
    sal_Bool 	bIsAutoFmtRedline : 1;	// TRUE: die Redlines werden vom Autoformat aufgezeichnet
    sal_Bool	bOLEPrtNotifyPending:1;	// TRUE: Printer  ist geaendert und beim
                                    // 		 Erzeugen der ::com::sun::star::sdbcx::View ist eine Benachrichtigung
                                    //		 der OLE-Objekte PrtOLENotify() notwendig.
    sal_Bool	bAllOLENotify		:1;	// True: Benachrichtigung aller Objekte ist notwendig
    sal_Bool 	bIsRedlineMove : 1;		// True: die Redlines werden in/aus der Section verschoben
    sal_Bool 	bInsOnlyTxtGlssry : 1;	// True: insert 'only text' glossary into doc
    sal_Bool 	bContains_MSVBasic : 1;	// True: MS-VBasic exist is in our storage
    sal_Bool 	bPurgeOLE : 1;			// TRUE: Purge OLE-Objects
    sal_Bool	bKernAsianPunctuation : 1;  // TRUE: kerning also for ASIAN punctuation
    sal_Bool	bReadlineChecked	: 1;  // TRUE: if the query was already shown
#ifdef DBG_UTIL
    sal_Bool	bXMLExport : 1;         // TRUE: during XML export
#endif

    // -------------------------------------------------------------------

    // -------------------------------------------------------------------
    // Dummies Members fuers FileFormat
    String sDummy1;				// Dummy-Member.
    String sDummy2;
    sal_uInt32  n32Dummy1;
    sal_uInt32  n32Dummy2;
    sal_Int8   n8Dummy1;
    sal_Int8   n8Dummy2;


    //---------------- private Methoden ------------------------------
    void checkRedlining(SwRedlineMode& _rReadlineMode);

        // nur fuer den internen Gebrauch deshalb privat.
        // Kopieren eines Bereiches im oder in ein anderes Dokument !
        // Die Position darf nicht im Bereich liegen !!

    SwFlyFrmFmt* _MakeFlySection( const SwPosition& rAnchPos,
                                const SwCntntNode& rNode, RndStdIds eRequestId,
                                const SfxItemSet* pFlyAttrSet,
                                SwFrmFmt* = 0 );

    SwFlyFrmFmt* _InsNoTxtNode( const SwPosition&rPos, SwNoTxtNode*,
                                const SfxItemSet* pFlyAttrSet,
                                const SfxItemSet* pGrfAttrSet,
                                SwFrmFmt* = 0 );

    void _CopyFlyInFly( const SwNodeRange& rRg, const SwNodeIndex& rSttIdx,
                        sal_Bool bCopyFlyAtFly = sal_False ) const;	// steht im ndcopy.cxx
    sal_Int8 SetFlyFrmAnchor( SwFrmFmt& rFlyFmt, SfxItemSet& rSet, sal_Bool bNewFrms );

    typedef SwFmt* (SwDoc:: *FNCopyFmt)( const String&, SwFmt* );
    SwFmt* CopyFmt( const SwFmt& rFmt, const SvPtrarr& rFmtArr,
                        FNCopyFmt fnCopyFmt, const SwFmt& rDfltFmt );
    SwFmt* FindFmtByName( const SvPtrarr& rFmtArr,
                                    const String& rName ) const;

    VirtualDevice& _GetVirDev() const;
    SfxPrinter& _GetPrt() const;
    void		PrtDataChanged();	//Printer oder JobSetup geandert, es muss
                                    //fuer entsprechende Invalidierungen und
                                    //Benachrichtigungen gesorgt werden.

    // gcc: aFtnInfo::CopyCtor ist private, also muessen wir uns auch schuetzen
    SwDoc( const SwDoc &);

    //wird nur von SwSwgReader::InlayoutFrames() verwendet!
    inline void SetInDtor( sal_Bool b ) { bDtor = b; }

    // fuer Felder:
    void _InitFieldTypes(); 	// wird vom CTOR gerufen!!
    void _MakeFldList( int eMode );
    // Datenbankfelder:
     void UpdateDBNumFlds( SwDBNameInfField& rDBFld, SwCalc& rCalc );
    void AddUsedDBToList( SvStringsDtor& rDBNameList,
                          const SvStringsDtor& rUsedDBNames );
    void AddUsedDBToList( SvStringsDtor& rDBNameList, const String& rDBName );
    void GetAllDBNames( SvStringsDtor& rAllDBNames );
    SvStringsDtor& FindUsedDBs( const SvStringsDtor& rAllDBNames,
                                const String& rFormel,
                                SvStringsDtor& rUsedDBNames );

    void InitDrawModel();
    void ReleaseDrawModel();

    void _CreateNumberFormatter();


    // erzeuge Anhand der vorgebenen Collection Teildokumente
    // falls keine angegeben ist, nehme die Kapitelvorlage der 1. Ebene

    // Charts der angegebenen Tabelle updaten
    void _UpdateCharts( const SwTable& rTbl, ViewShell& rVSh ) const;

    // unser eigener 'IdlTimer' ruft folgende Methode
    DECL_LINK( DoIdleJobs, Timer * );
    // der CharTimer ruft diese Methode
    DECL_LINK( DoUpdateAllCharts, Timer * );
    DECL_LINK( DoUpdateModifiedOLE, Timer * );

public:
    SwDoc();
    ~SwDoc();

          SwNodes& GetNodes() 	  	  	  	  	{ return aNodes; }
    const SwNodes& GetNodes() const				{ return aNodes; }

    DECL_LINK(CalcFieldValueHdl, EditFieldInfo*);

    // Links un-/sichtbar in LinkManager einfuegen (gelinkte Bereiche)
    sal_Bool IsVisibleLinks() const					 { return bVisibleLinks; }
    void SetVisibleLinks( sal_Bool bFlag )			 { bVisibleLinks = bFlag; }

          SvxLinkManager& GetLinkManager()		 { return *pLinkMgr; }
    const SvxLinkManager& GetLinkManager() const { return *pLinkMgr; }

        // erfrage das spezifische Layout
    const SwRootFrm* GetRootFrm() const { return pLayout; }
          SwRootFrm* GetRootFrm()		{ return pLayout; }
        // der alte muss !! von der Shell geloescht werden !!
    void SetRootFrm( SwRootFrm* pNew )	{ pLayout = pNew; }

    void StartIdleTimer()				{ aIdleTimer.Start(); }
    void StopIdleTimer()				{ aIdleTimer.Stop();  }
    sal_Bool IsIdleTimerActive() const	{ return aIdleTimer.IsActive(); }

    sal_Bool IsOLEPrtNotifyPending() const  { return bOLEPrtNotifyPending; }
    inline void SetOLEPrtNotifyPending( sal_Bool bSet=sal_True );
    void PrtOLENotify( sal_Bool bAll );	//Alle oder nur Markierte

    sal_Bool IsPurgeOLE() const				{ return bPurgeOLE; }
    void SetPurgeOLE( sal_Bool bFlag )		{ bPurgeOLE = bFlag; }

    sal_Bool IsKernAsianPunctuation() const			{ return bKernAsianPunctuation; }
    void SetKernAsianPunctuation( sal_Bool bFlag )	{ bKernAsianPunctuation = bFlag; }

#ifdef DBG_UTIL
    sal_Bool InXMLExport() const			{ return bXMLExport; }
    void SetXMLExport( sal_Bool bFlag )		{ bXMLExport = bFlag; }
#endif

        // das Dokument im Browse-Modus anzeigen
    void SetBrowseMode( sal_Bool bFlag = sal_True )		{ bBrowseMode = bFlag; }
    sal_Bool IsBrowseMode() const 	  	  	  	  		{ return bBrowseMode; }
    void SetHTMLMode( sal_Bool bFlag = sal_True ) 		{ bHTMLMode = bFlag; }
    sal_Bool IsHTMLMode() const   	  	  	  	  		{ return bHTMLMode; }
    void SetHeadInBrowse( sal_Bool bFlag = sal_True )	{ bHeadInBrowse = bFlag; }
    sal_Bool IsHeadInBrowse() const						{ return bHeadInBrowse; }
    void SetFootInBrowse( sal_Bool bFlag = sal_True )	{ bFootInBrowse = bFlag; }
    sal_Bool IsFootInBrowse() const						{ return bFootInBrowse; }
    void SetFrmBeepEnabled( sal_Bool bFlag = sal_True )	{ bFrmBeepEnabled = bFlag; }
    sal_Bool IsFrmBeepEnabled() const					{ return bFrmBeepEnabled; }

    void SetGlobalDoc( sal_Bool bFlag = sal_True )		{ bIsGlobalDoc = bFlag; }
    sal_Bool IsGlobalDoc() const						{ return bIsGlobalDoc; }
    void SetGlblDocSaveLinks( sal_Bool bFlag=sal_True )	{ bGlblDocSaveLinks = bFlag; }
    sal_Bool IsGlblDocSaveLinks() const					{ return bGlblDocSaveLinks; }

    void SetLabelDoc( sal_Bool bFlag = sal_True )		{ bIsLabelDoc = bFlag; }
    sal_Bool IsLabelDoc() const							{ return bIsLabelDoc; }

    sal_uInt16 GetLinkUpdMode() const;
    void SetLinkUpdMode( sal_uInt16 nMode )				{ nLinkUpdMode = nMode; }
    // nur fuer den Writer, weil dieser das richtige Enum schreiben muss!
    sal_uInt16 _GetLinkUpdMode() const					{ return nLinkUpdMode; }

    SwCharCompressType GetCharCompressType() const		{ return eChrCmprType; }
    void SetCharCompressType( SwCharCompressType n );

    inline sal_Bool IsInDtor() const { return bDtor; }

    // SS fuer das Drawing, Model und LayerId's
    const SdrModel* GetDrawModel() const 	{ return pDrawModel; }
          SdrModel* GetDrawModel()		 	{ return pDrawModel; }
    SdrLayerID GetHeavenId() const           { return nHeaven; }
    SdrLayerID GetHellId() const             { return nHell;   }
    SdrLayerID GetControlsId() const         { return nControls;   }
    // OD 25.06.2003 #108784# - accessor for layer IDs of invisible layers.
    inline SdrLayerID GetInvisibleHeavenId() const    { return nInvisibleHeaven; }
    inline SdrLayerID GetInvisibleHellId() const      { return nInvisibleHell; }
    inline SdrLayerID GetInvisibleControlsId() const  { return nInvisibleControls; }

    /** method to determine, if a layer ID belongs to the visible ones.

        OD 25.06.2003 #108784#
        Note: If given layer ID is unknown, method asserts and returns <false>.

        @author OD

        @param _nLayerId
        input parameter - layer ID, which has to be checked, if it belongs to
        the visible ones.

        @return bool, indicating, if given layer ID belongs to the visible ones.
    */
    bool IsVisibleLayerId( const SdrLayerID& _nLayerId );

    /** method to determine, if the corresponding visible layer ID for a invisible one.

        OD 25.06.2003 #108784#
        Note: If given layer ID is a visible one, method returns given layer ID.
        Note: If given layer ID is unknown, method returns given layer ID.

        @author OD

        @param _nInvisibleLayerId
        input parameter - invisible layer ID for which the corresponding
        visible one has to be returned.

        @return sal_Int8, visible layer ID corresponding to given layer ID
    */
    SdrLayerID GetVisibleLayerIdByInvisibleOne( const SdrLayerID& _nInvisibleLayerId );

    /** method to determine, if the corresponding invisible layer ID for a visible one.

        OD 25.06.2003 #108784#
        Note: If given layer ID is a invisible one, method returns given layer ID.
        Note: If given layer ID is unknown, method returns given layer ID.

        @author OD

        @param _nVisibleLayerId
        input parameter - visible layer ID for which the corresponding
        invisible one has to be returned.

        @return sal_Int8, invisible layer ID corresponding to given layer ID
    */
    SdrLayerID GetInvisibleLayerIdByVisibleOne( const SdrLayerID& _nVisibleLayerId );

    // liefert zu allen fliegenden Rahmen die Position im Dokument.
    // Wird ein Pam-Pointer uebergeben, muessen die absatzgebundenen
    // FlyFrames von der ::com::sun::star::awt::Selection vollstaendig umschlossen sein
    // ( Start < Pos < End ) !!!
    // (wird fuer die Writer benoetigt)
    void GetAllFlyFmts( SwPosFlyFrms& rPosFlyFmts, const SwPaM* = 0,
                        sal_Bool bDrawAlso = sal_False ) const;

        // dokumentglobale Macros
  void SetGlobalMacro(sal_uInt16 nEvent, const SvxMacro&);
    const SvxMacroTableDtor& GetMacroTable() const { return *pMacroTable; }

    // Fussnoten Informationen
    const SwFtnInfo& GetFtnInfo() const			{ return *pFtnInfo; }
    void SetFtnInfo(const SwFtnInfo& rInfo);
    const SwEndNoteInfo& GetEndNoteInfo() const { return *pEndNoteInfo; }
    void SetEndNoteInfo(const SwEndNoteInfo& rInfo);

    // Zeilennummerierung
    const SwLineNumberInfo& GetLineNumberInfo() const { return *pLineNumberInfo; }
    void SetLineNumberInfo(const SwLineNumberInfo& rInfo);

          SwFtnIdxs& GetFtnIdxs() 		{ return *pFtnIdxs; }
    const SwFtnIdxs& GetFtnIdxs() const { return *pFtnIdxs; }
    // Fussnoten im Bereich aendern
    sal_Bool SetCurFtn( const SwPaM& rPam, const String& rNumStr,
                        sal_uInt16 nNumber, sal_Bool bIsEndNote );

    // wegen swrtf.cxx und define private public, jetzt hier
    SwFlyFrmFmt  *MakeFlyFrmFmt (const String &rFmtName, SwFrmFmt *pDerivedFrom);
    SwDrawFrmFmt *MakeDrawFrmFmt(const String &rFmtName, SwFrmFmt *pDerivedFrom);

          SwLayouter* GetLayouter() 	  { return pLayouter; }
    const SwLayouter* GetLayouter() const { return pLayouter; }
    void SetLayouter( SwLayouter* pNew )  { pLayouter = pNew; }

    // used for spell checking and text conversion


    const SwBookmarks& GetBookmarks() const { return *pBookmarkTbl; }
    SwBookmark* MakeBookmark( const SwPaM& rPaM, const KeyCode&,
            const String& rName, const String& rShortName, BOOKMARK_TYPE eMark = BOOKMARK);
    void DelBookmark( sal_uInt16 nPos );
    void DelBookmark( const String& rName );
    sal_uInt16 FindBookmark( const String& rName );
        // erzeugt einen eindeutigen Namen. Der Name selbst muss vorgegeben
        // werden, es wird dann bei gleichen Namen nur durchnumeriert.
    void MakeUniqueBookmarkName( String& rNm );
    // Anzahl der ::com::sun::star::text::Bookmarks, gfs. nur "echte"
    sal_uInt16 GetBookmarkCnt(sal_Bool bBkmrk = sal_False) const;
    SwBookmark& GetBookmark( sal_uInt16, sal_Bool bBkmrk = sal_False);

    // Textbaustein Dokument?
    void SetGlossDoc( sal_Bool bGlssDc = sal_True ) { bGlossDoc = bGlssDc; }
    sal_Bool IsGlossDoc() const 				{ return bGlossDoc; }
    sal_Bool IsInsOnlyTextGlossary() const 		{ return bInsOnlyTxtGlssry; }

    //Bei Formataenderungen muss das zu Fuss gerufen werden!
    void SetModified();
    void ResetModified();
    sal_Bool IsModified() const { return bModified; }	//Dokumentaenderungen?

    sal_Bool IsInCallModified() const		{ return bInCallModified; }

        //Die neuen (hoffentlich bestaendigen) Schnittstellen fuer alles,
        //was mit dem Layout zu tun hat.
    SwFrmFmt *MakeLayoutFmt( RndStdIds eRequest,
                             SwFrmFmt* = 0,
                             const SfxItemSet* pSet = 0 );
        // JP 08.05.98: fuer Flys muss jetzt diese Schnittstelle benutzt
        //				werden. pAnchorPos muss gesetzt sein, wenn keine
        //				Seitenbindung vorliegt UND der ::com::sun::star::chaos::Anchor nicht schon
        //				im FlySet/FrmFmt mit gueltiger CntntPos gesetzt ist
        /* #109161# new parameter bCalledFromShell

       TRUE: An existing adjust item at pAnchorPos is propagated to
       the content node of the new fly section. That propagation only
       takes place if there is no adjust item in the paragraph style
       for the new fly section.

       FALSE: no propagation
    */
    SwFlyFrmFmt* MakeFlySection( RndStdIds eAnchorType,
                                 const SwPosition* pAnchorPos,
                                 const SfxItemSet* pSet = 0,
                                 SwFrmFmt *pParent = 0,
                                 BOOL bCalledFromShell = FALSE );

    void	  DelLayoutFmt( SwFrmFmt *pFmt );
    SwFrmFmt *CopyLayoutFmt( const SwFrmFmt& rSrc,
                            const SwFmtAnchor& rNewAnchor,
                            sal_Bool bSetTxtFlyAtt = sal_True, sal_Bool bMakeFrms = sal_True );
    void CopyWithFlyInFly( const SwNodeRange& rRg,
                            const SwNodeIndex& rInsPos,
                            sal_Bool bMakeNewFrms = sal_True,
                            sal_Bool bDelRedlines = sal_True,
                            sal_Bool bCopyFlyAtFly = sal_False ) const;
    sal_Bool IsInHeaderFooter( const SwNodeIndex& rIdx ) const;

    sal_Bool SetFlyFrmAttr( SwFrmFmt& rFlyFmt, SfxItemSet& rSet );
    sal_Bool SetFrmFmtToFly( SwFrmFmt& rFlyFmt, SwFrmFmt& rNewFmt,
                        SfxItemSet* pSet = 0, sal_Bool bKeepOrient = sal_False );

    // Abstakt fuellen

    /* Verwaltet SwDoc::nLinkCt, sollte (paarig!) von allen benutzt werden,
     * die einen Pointer auf dieses Dokument halten, denn wenn Remove() 0
     * liefert, wird das Dokument zerstoert! Oder anders: Jeder bei dem
     * Remove() 0 liefert, muss das Dokument zerstoeren.
     */
    sal_Int8 AddLink()	  				{ return nLinkCt++; }
    sal_Int8 RemoveLink() 				{ return nLinkCt ? --nLinkCt : nLinkCt; }
    sal_Int8 GetLinkCnt() const 		{ return nLinkCt; }

    /* Felder */
    const SwFldTypes *GetFldTypes() const { return pFldTypes; }
    SwFieldType *InsertFldType(const SwFieldType &);
    SwFieldType *GetSysFldType( const sal_uInt16 eWhich ) const;
    SwFieldType* GetFldType(sal_uInt16 nResId, const String& rName) const;
    void RemoveFldType(sal_uInt16 nFld);
    void UpdateFlds( SfxPoolItem* pNewHt = 0, sal_Bool bCloseDB = sal_False );

        // rufe das Update der Expression Felder auf; alle Ausdruecke werden
        // neu berechnet.
    void UpdateRefFlds( SfxPoolItem* pHt = 0);
    void UpdateTblFlds( SfxPoolItem* pHt = 0);
    void UpdateExpFlds( SwTxtFld* pFld = 0, sal_Bool bUpdateRefFlds = sal_True );
    void UpdatePageFlds( SfxPoolItem* );
    void LockExpFlds()					{ ++nLockExpFld; }
    void UnlockExpFlds()				{ if( nLockExpFld ) --nLockExpFld; }
    sal_Bool IsExpFldsLocked() const		{ return 0 != nLockExpFld; }
    SwDocUpdtFld& GetUpdtFlds() const 	{ return *pUpdtFlds; }
    sal_Bool SetFieldsDirty( sal_Bool b, const SwNode* pChk = 0, ULONG nLen = 0 );

    sal_uInt16 GetFldUpdateFlags() const;
    void SetFldUpdateFlags( sal_uInt16 eMode )			{ nFldUpdMode = eMode; }
    // nur fuer den Writer, weil dieser das richtige Enum schreiben muss!
    sal_uInt16 _GetFldUpdateFlags() const				{ return nFldUpdMode; }


    // Zustaende ueber Ladezustand
    // frueher DocInfo
    //
    sal_Bool IsPageNums() const 						{ return bPageNums; 	}
    sal_Bool IsLoaded() const							{ return bLoaded;		}
    sal_Bool IsUpdateExpFld() const 					{ return bUpdateExpFld; }
    sal_Bool IsNewDoc() const							{ return bNewDoc;		}

    void SetPageNums(sal_Bool b = sal_True)					{ bPageNums = b; 		}
    void SetNewDoc(sal_Bool b = sal_True)					{ bNewDoc = b;			}
    void SetUpdateExpFldStat(sal_Bool b = sal_True)			{ bUpdateExpFld = b;	}
    void SetLoaded(sal_Bool b = sal_True)					{ bLoaded = b;			}

        // Setze im Calculator alle SetExpresion Felder, die bis zur
        // angegebenen Position (Node [ + ::com::sun::star::ucb::Content]) gueltig sind. Es kann
        // eine erzeugte Liste aller Felder mit uebergegeben werden.
        // (ist die Adresse != 0, und der Pointer == 0 wird eine neue
        // Liste returnt.)
    void FldsToCalc( SwCalc& rCalc, const _SetGetExpFld& rToThisFld );
    sal_Bool IsNewFldLst() const { return bNewFldLst; }
    void SetNewFldLst( sal_Bool bFlag = sal_True ) { bNewFldLst = bFlag; }
    void InsDelFldInFldLst( sal_Bool bIns, const SwTxtFld& rFld );

    /*	Datenbank &&  DB-Manager */
    void SetNewDBMgr( SwNewDBMgr* pNewMgr )		{ pNewDBMgr = pNewMgr; }
    SwNewDBMgr* GetNewDBMgr() const 			{ return pNewDBMgr; }
    void SetInitDBFields(sal_Bool b);
    // Von Feldern verwendete Datenbanken herausfinden
    void GetAllUsedDB( SvStringsDtor& rDBNameList,
                       const SvStringsDtor* pAllDBNames = 0 );

    void ChgDBData( const SwDBData& rNewData );
    SwDBData GetDBData();
    const SwDBData& GetDBDesc();
    const SwDBData& _GetDBDesc() const { return aDBData; }


        // Kopieren eines Bereiches im oder in ein anderes Dokument !
        // Die Position kann auch im Bereich liegen !!
    sal_Bool Copy( SwPaM&, SwPosition& ) const;	// in ndcopy.cxx

        // Loesche die Section, in der der Node steht.
    void DeleteSection( SwNode *pNode );

    sal_Bool Delete( SwPaM& );			  	//loeschen eines Bereiches
    sal_Bool DelFullPara( SwPaM& );			//loeschen gesamter Absaetze
    sal_Bool DeleteAndJoin( SwPaM& );		//komplett loeschen eines Bereiches

        //Ueberschreiben eines einzelnen Zeichens. rRg.Start() bezeichnet
        //den Node und die Position in dem Node, an der eingefuegt wird,
        //Ueberschreiben eines Strings in einem bestehenden Textnode.
        //Einfuegen eines einzelnen Zeichens. rRg.Start() bezeichnet
        //den Node und die Position in dem Node, an der eingefuegt wird.
    sal_Bool Insert(const SwPaM &rRg, sal_Unicode c );
        //Einfuegen eines Strings in einen bestehenden
        //Textnode. Der Text wird kopiert.
    sal_Bool Insert( const SwPaM &rRg, const String &,
                     sal_Bool bHintExpand = sal_True );

    // change text to Upper/Lower/Hiragana/Katagana/...

        //Einfuegen einer Grafik, Formel. Die XXXX werden kopiert.
    SwFlyFrmFmt* Insert(const SwPaM &rRg,
                        const String& rGrfName,
                        const String& rFltName,
                        const Graphic* pGraphic = 0,
                        const SfxItemSet* pFlyAttrSet = 0,
                        const SfxItemSet* pGrfAttrSet = 0,
                        SwFrmFmt* = 0 );
    SwFlyFrmFmt* Insert(const SwPaM &rRg,
                        const BfGraphicObject& rGrfObj,
                        const SfxItemSet* pFlyAttrSet = 0,
                        const SfxItemSet* pGrfAttrSet = 0,
                        SwFrmFmt* = 0 );
        // austauschen einer Grafik (mit Undo)
    void ReRead( SwPaM&, const String& rGrfName, const String& rFltName,
                const Graphic* pGraphic, const BfGraphicObject* pGrfObj );

        //Einfuegen eines DrawObjectes. Das Object muss bereits im DrawModel
        // angemeldet sein.
    SwDrawFrmFmt* Insert( const SwPaM &rRg,
                          SdrObject& rDrawObj,
                          const SfxItemSet* pFlyAttrSet = 0,
                          SwFrmFmt* = 0 );
    String GetUniqueGrfName() const;

        //Einfuegen von OLE-Objecten.
    SwFlyFrmFmt* Insert( const SwPaM &rRg, SvInPlaceObject *,
                        const SfxItemSet* pFlyAttrSet = 0,
                        const SfxItemSet* pGrfAttrSet = 0,
                        SwFrmFmt* = 0 );
    SwFlyFrmFmt* InsertOLE( const SwPaM &rRg, String& rObjName,
                        const SfxItemSet* pFlyAttrSet = 0,
                        const SfxItemSet* pGrfAttrSet = 0,
                        SwFrmFmt* = 0 );
    String GetUniqueOLEName() const;

    // ein bischen wa fuer die benannten FlyFrames
    String GetUniqueFrameName() const;
    void SetFlyName( SwFlyFrmFmt& rFmt, const String& rName );
    const SwFlyFrmFmt* FindFlyByName( const String& rName, sal_Int8 nNdTyp = 0 ) const;

    void GetGrfNms( const SwFlyFrmFmt& rFmt, String* pGrfName,
                    String* pFltName ) const;

    // setze bei allen Flys ohne Namen einen gueltigen (Wird von den Readern
    // nach dem Einlesen gerufen )
    void SetAllUniqueFlyNames();

        //Aufspalten eines Nodes an rPos (nur fuer den TxtNode implementiert)
    sal_Bool SplitNode(const SwPosition &rPos, sal_Bool bChkTableStart = sal_False );
    sal_Bool AppendTxtNode( SwPosition& rPos ); // nicht const!

    // Ersetz einen selektierten Bereich in einem TextNode mit dem
    // String. Ist fuers Suchen&Ersetzen gedacht.
    // bRegExpRplc - ersetze Tabs (\\t) und setze den gefundenen String
    //				 ein ( nicht \& )
    //				z.B.: Fnd: "zzz", Repl: "xx\t\\t..&..\&"
    //						--> "xx\t<Tab>..zzz..&"
    sal_Bool Replace( SwPaM& rPam, const String& rNewStr,
                    sal_Bool bRegExpRplc = sal_False );

    /*
     * Einfuegen eines Attributs. Erstreckt sich rRg ueber
     * mehrere Nodes, wird das Attribut aufgespaltet, sofern
     * dieses Sinn macht. Nodes, in denen dieses Attribut keinen
     * Sinn macht, werden ignoriert.  In vollstaendig in der
     * Selektion eingeschlossenen Nodes wird das Attribut zu
     * harter Formatierung, in den anderen (Text-)Nodes wird das
     * Attribut in das Attributearray eingefuegt. Bei einem
     * Zeichenattribut wird ein "leerer" Hint eingefuegt,
     * wenn keine Selektion
     * vorliegt; andernfalls wird das Attribut als harte
     * Formatierung dem durch rRg.Start() bezeichneten Node
     * hinzugefuegt.  Wenn das Attribut nicht eingefuegt werden
     * konnte, liefert die Methode sal_False.
     */
    sal_Bool Insert( const SwPaM &rRg, const SfxPoolItem&, sal_uInt16 nFlags = 0  );
    sal_Bool Insert( const SwPaM &rRg, const SfxItemSet&, sal_uInt16 nFlags = 0 );

        //Zuruecksetzen der Attribute; es werden alle TxtHints und bei
        //vollstaendiger Selektion harte Formatierung (AUTO-Formate) entfernt
    void ResetAttr(const SwPaM &rRg, sal_Bool bTxtAttr = sal_True,
                        const SvUShortsSort* = 0 );

        // Setze das Attribut im angegebenen Format. Ist Undo aktiv, wird
        // das alte in die Undo-History aufgenommen
    void SetAttr( const SfxPoolItem&, SwFmt& );
    void SetAttr( const SfxItemSet&, SwFmt& );

        // Setze das Attribut als neues default Attribut in diesem Dokument.
        // Ist Undo aktiv, wird das alte in die Undo-History aufgenommen
    void SetDefault( const SfxPoolItem& );
    void SetDefault( const SfxItemSet& );

    // Erfrage das Default Attribut in diesem Dokument.
    const SfxPoolItem& GetDefault( sal_uInt16 nFmtHint ) const;
    // TextAttribute nicht mehr aufspannen lassen

    /* Formate */
    const SwFrmFmts* GetFrmFmts() const 	{ return pFrmFmtTbl; }
          SwFrmFmts* GetFrmFmts()			{ return pFrmFmtTbl; }
    const SwCharFmts* GetCharFmts() const	{ return pCharFmtTbl;}

    /* LayoutFormate (Rahmen, DrawObjecte), mal const mal nicht */
    const SwSpzFrmFmts* GetSpzFrmFmts() const	{ return pSpzFrmFmtTbl; }
          SwSpzFrmFmts* GetSpzFrmFmts() 		{ return pSpzFrmFmtTbl; }

    const SwFrmFmt *GetDfltFrmFmt() const	{ return pDfltFrmFmt; }
          SwFrmFmt *GetDfltFrmFmt() 		{ return pDfltFrmFmt; }
    const SwFrmFmt *GetEmptyPageFmt() const { return pEmptyPageFmt; }
          SwFrmFmt *GetEmptyPageFmt()		{ return pEmptyPageFmt; }
    const SwFrmFmt *GetColumnContFmt() const{ return pColumnContFmt; }
          SwFrmFmt *GetColumnContFmt()		{ return pColumnContFmt; }
    const SwCharFmt *GetDfltCharFmt() const { return pDfltCharFmt;}
          SwCharFmt *GetDfltCharFmt()		{ return pDfltCharFmt;}

      // Remove all language dependencies from all existing formats
    void RemoveAllFmtLanguageDependencies();

    SwFrmFmt  *MakeFrmFmt(const String &rFmtName, SwFrmFmt *pDerivedFrom);
    void	   DelFrmFmt( SwFrmFmt *pFmt );
    SwFrmFmt* FindFrmFmtByName( const String& rName ) const
        {	return (SwFrmFmt*)FindFmtByName( (SvPtrarr&)*pFrmFmtTbl, rName ); }
    SwFrmFmt* FindSpzFrmFmtByName( const String& rName ) const
        {	return (SwFrmFmt*)FindFmtByName( (SvPtrarr&)*pSpzFrmFmtTbl, rName ); }

    SwCharFmt *MakeCharFmt(const String &rFmtName, SwCharFmt *pDerivedFrom);
    void       DelCharFmt(sal_uInt16 nFmt);
    void       DelCharFmt(SwCharFmt* pFmt);
    SwCharFmt* FindCharFmtByName( const String& rName ) const
        {	return (SwCharFmt*)FindFmtByName( (SvPtrarr&)*pCharFmtTbl, rName ); }

    /* Formatcollections (Vorlagen) */
    // TXT
    const SwTxtFmtColl* GetDfltTxtFmtColl() const { return pDfltTxtFmtColl; }
    const SwTxtFmtColls *GetTxtFmtColls() const { return pTxtFmtCollTbl; }
    SwTxtFmtColl *MakeTxtFmtColl( const String &rFmtName,
                                  SwTxtFmtColl *pDerivedFrom );
/*NBFF*/	SwConditionTxtFmtColl* MakeCondTxtFmtColl( const String &rFmtName,
/*NBFF*/											   SwTxtFmtColl *pDerivedFrom );
    sal_Bool SetTxtFmtColl( const SwPaM &rRg, SwTxtFmtColl *pFmt,
                        sal_Bool bReset = sal_True);
    SwTxtFmtColl* FindTxtFmtCollByName( const String& rName ) const
        {	return (SwTxtFmtColl*)FindFmtByName( (SvPtrarr&)*pTxtFmtCollTbl, rName ); }

        // GRF
    const SwGrfFmtColl* GetDfltGrfFmtColl() const	{ return pDfltGrfFmtColl; }
    const SwGrfFmtColls *GetGrfFmtColls() const		{ return pGrfFmtCollTbl; }
    SwGrfFmtColl* FindGrfFmtCollByName( const String& rName ) const
        {	return (SwGrfFmtColl*)FindFmtByName( (SvPtrarr&)*pGrfFmtCollTbl, rName ); }

        // Tabellen-Formate
    const SwFrmFmts* GetTblFrmFmts() const	{ return pTblFrmFmtTbl; }
          SwFrmFmts* GetTblFrmFmts()		{ return pTblFrmFmtTbl; }
    sal_uInt16 GetTblFrmFmtCount( sal_Bool bUsed ) const;
    SwFrmFmt& GetTblFrmFmt(sal_uInt16 nFmt, sal_Bool bUsed ) const;
    SwTableFmt* MakeTblFrmFmt(const String &rFmtName, SwFrmFmt *pDerivedFrom);
    void	    DelTblFrmFmt( SwTableFmt* pFmt );
    SwTableFmt* FindTblFmtByName( const String& rName, sal_Bool bAll = sal_False ) const;

    //Rahmenzugriff
    //iterieren ueber Flys - fuer Basic-Collections
    sal_uInt16 GetFlyCount(FlyCntType eType = FLYCNTTYPE_ALL) const;
    SwFrmFmt* GetFlyNum(sal_uInt16 nIdx, FlyCntType eType = FLYCNTTYPE_ALL);


    // kopiere die Formate in die eigenen Arrays und returne diese
    SwFrmFmt  *CopyFrmFmt ( const SwFrmFmt& );
    SwCharFmt *CopyCharFmt( const SwCharFmt& );
    SwTxtFmtColl* CopyTxtColl( const SwTxtFmtColl& rColl );
    SwGrfFmtColl* CopyGrfColl( const SwGrfFmtColl& rColl );

        // ersetze alle Formate mit denen aus rSource

        // Gebe die "Auto-Collection" mit der Id zurueck. Existiert
        // sie noch nicht, dann erzuege sie
        // Ist der String-Pointer definiert, dann erfrage nur die
        // Beschreibung der Attribute, !! es legt keine Vorlage an !!
    // ...Simple to prevent ambiguity with GetPageDescFromPool
    SwTxtFmtColl* GetTxtCollFromPoolSimple(sal_uInt16 nId,
                                           BOOL bRegardLanguage)
    {
        return GetTxtCollFromPool
            ( nId, 0, SFX_ITEM_PRESENTATION_COMPLETE, SFX_MAPUNIT_TWIP,
              SFX_MAPUNIT_TWIP, bRegardLanguage);
    }
    SwTxtFmtColl* GetTxtCollFromPool( sal_uInt16 nId, String* pDescription = 0,
        SfxItemPresentation ePres = SFX_ITEM_PRESENTATION_COMPLETE,
        SfxMapUnit eCoreMetric = SFX_MAPUNIT_TWIP,
        SfxMapUnit ePresMetric = SFX_MAPUNIT_TWIP,
        BOOL bRegardLanguage = TRUE );
        // return das geforderte automatische  Format - Basis-Klasse !
    SwFmt* GetFmtFromPool( sal_uInt16 nId, String* pDescription = 0,
        SfxItemPresentation ePres = SFX_ITEM_PRESENTATION_COMPLETE,
        SfxMapUnit eCoreMetric = SFX_MAPUNIT_TWIP,
        SfxMapUnit ePresMetric = SFX_MAPUNIT_TWIP );
        // returne das geforderte automatische Format
    SwFrmFmt* GetFrmFmtFromPool( sal_uInt16 nId, String* pDescription = 0 )
        { return (SwFrmFmt*)GetFmtFromPool( nId, pDescription ); }
    SwCharFmt* GetCharFmtFromPool( sal_uInt16 nId, String* pDescription = 0 )
        { return (SwCharFmt*)GetFmtFromPool( nId, pDescription ); }
        // returne die geforderte automatische Seiten-Vorlage
    SwPageDesc* GetPageDescFromPool( sal_uInt16 nId, String* pDescription = 0,
        SfxItemPresentation ePres = SFX_ITEM_PRESENTATION_COMPLETE,
        SfxMapUnit eCoreMetric = SFX_MAPUNIT_TWIP,
        SfxMapUnit ePresMetric = SFX_MAPUNIT_TWIP,
        BOOL bRegardLanguage = TRUE );
    // ...Simple to prevent ambiguity with GetPageDescFromPool
    SwPageDesc* GetPageDescFromPoolSimple( sal_uInt16 nId,
                                           BOOL bRegardLanguage)
    {
        return GetPageDescFromPool
            ( nId, 0, SFX_ITEM_PRESENTATION_COMPLETE, SFX_MAPUNIT_TWIP,
              SFX_MAPUNIT_TWIP, bRegardLanguage);
    }
    SwNumRule* GetNumRuleFromPool( sal_uInt16 nId, String* pDescription = 0,
        SfxItemPresentation ePres = SFX_ITEM_PRESENTATION_COMPLETE,
        SfxMapUnit eCoreMetric = SFX_MAPUNIT_TWIP,
        SfxMapUnit ePresMetric = SFX_MAPUNIT_TWIP );

        // pruefe, ob diese "Auto-Collection" in Dokument schon/noch
        // benutzt wird

    // erfrage ob die Absatz-/Zeichen-/Rahmen-/Seiten - Vorlage benutzt wird
    sal_Bool IsUsed( const SwModify& ) const;
    sal_Bool IsUsed( const SwNumRule& ) const;

        // setze den Namen der neu geladenen Dokument-Vorlage
    sal_uInt16 SetDocPattern( const String& rPatternName );
        // gebe die Anzahl von geladenen Dok-VorlagenNamen zurueck.
        // !! Die nicht mehr benutzten sind 0-Pointer !!
    sal_uInt16 GetDocPatternCnt() const { return aPatternNms.Count(); }
        // gebe den Dok-VorlagenNamen zurueck. !!! Kann auch 0 sein !!!
    String* GetDocPattern( sal_uInt16 nPos ) const { return aPatternNms[nPos]; }
    // loeche die nicht mehr benutzten Pattern-Namen aus dem Array.

    // alle nicht mehr referenzierten Namen werden durch 0-Pointer
    // ersetzt. Diese Positionen koennen wieder vergeben werden.


        // Loesche alle nicht referenzierten FeldTypen

        // akt. Dokument mit Textbausteindokument verbinden/erfragen
    void SetGlossaryDoc( SwDoc* pDoc ) { pGlossaryDoc = pDoc; }
    SwDoc* GetGlossaryDoc() const { return pGlossaryDoc; }
        // jetzt mit einem verkappten Reader/Writer/Dokument

    //  JobSetup und Freunde

    OutputDevice& GetRefDev() const;
    OutputDevice* _GetRefDev() const;

    VirtualDevice* GetVirDev( sal_Bool bCreate ) const
        { if ( !bCreate || pVirDev ) return pVirDev; else return &_GetVirDev(); }
    VirtualDevice* GetVirDev() const { return pVirDev; }

    void SetVirDev( VirtualDevice* pVd, sal_Bool bCallVirDevDataChanged );

    SfxPrinter* GetPrt( sal_Bool bCreate ) const
        { if( !bCreate || pPrt ) return pPrt; else return &_GetPrt(); }
    SfxPrinter* GetPrt() const { return pPrt; }

    inline void _SetPrt( SfxPrinter *pP )   { pPrt = pP; }
    void		SetPrt( SfxPrinter *pP, sal_Bool bCallPrtDataChanged = sal_True );

    // sets the flag at the document and invalidates the layout if flag has changed
    void SetUseVirtualDevice( sal_Bool bFlag );

    void		SetJobsetup( const JobSetup& rJobSetup );

    SwPrintData*    GetPrintData() const;
    void            SetPrintData(SwPrintData& rPrtData);

        // Dokument - Info
            // legt sie auf jedenfall an!
    const SfxDocumentInfo* GetInfo();
            // kann auch 0 sein !!!
    const SfxDocumentInfo* GetpInfo() const { return pSwgInfo; }

        // setze ueber die DocShell in den entsp. Storage-Stream. Hier wird
        // jetzt die DocInfo verwaltet. Fuer die Felder ist am Doc eine Kopie
        // der Info, um einen schnellen Zugriff zu ermoeglichen.
        // (impl. in docsh2.cxx)
    void SetInfo( const SfxDocumentInfo& rInfo );
        // die DocInfo hat siche geaendert (Notify ueber die DocShell)
        // stosse die entsp. Felder zum Updaten an.
    void DocInfoChgd( const SfxDocumentInfo& rInfo );

        //	Dokument - Statistics
    inline const SwDocStat	&GetDocStat() const { return *pDocStat; }
    void SetDocStat( const SwDocStat& rStat );
    void UpdateDocStat( SwDocStat& rStat );

        sal_uInt16 GetPageCount() const;
    const Size GetPageSize( sal_uInt16 nPageNum ) const;

        //PageDescriptor-Schnittstelle
    sal_uInt16 GetPageDescCnt() const { return aPageDescs.Count(); }
    const SwPageDesc& GetPageDesc( sal_uInt16 i ) const { return *aPageDescs[i]; }
    SwPageDesc* FindPageDescByName( const String& rName,
                                    sal_uInt16* pPos = 0 ) const;

        // kopiere die Kopzeile (mit dem Inhalt!) aus dem SrcFmt
        // ins DestFmt ( auch ueber Doc grenzen hinaus!)
    void CopyHeader( const SwFrmFmt& /*rSrcFmt*/, SwFrmFmt& /*rDestFmt*/ )
    { DBG_BF_ASSERT(0, "STRIP"); }
        // kopiere die Fusszeile (mit dem Inhalt!) aus dem SrcFmt
        // ins DestFmt ( auch ueber Doc grenzen hinaus!)
    void CopyFooter( const SwFrmFmt& /*rSrcFmt*/, SwFrmFmt& /*rDestFmt*/ )
    { DBG_BF_ASSERT(0, "STRIP"); }

        //fuer Reader
    SwPageDesc& _GetPageDesc( sal_uInt16 i ) const { return *aPageDescs[i]; }
    void ChgPageDesc( sal_uInt16 i, const SwPageDesc& );
    void DelPageDesc( sal_uInt16 i );
    sal_uInt16 MakePageDesc( const String &rName, const SwPageDesc* pCpy = 0,
                             BOOL bRegardLanguage = TRUE);

        // Methoden fuer die Verzeichnisse:
        // - Verzeichnismarke einfuegen loeschen travel
     void Delete( SwTOXMark* pTOXMark );

        // - Verzeichnis einfuegen, und bei Bedarf erneuern
    const SwTOXBaseSection* InsertTableOf( const SwPosition& rPos,
                                            const SwTOXBase& rTOX,
                                            const SfxItemSet* pSet = 0,
                                            sal_Bool bExpand = sal_False );
    const SwTOXBaseSection* InsertTableOf( ULONG nSttNd, ULONG nEndNd,
                                            const SwTOXBase& rTOX,
                                            const SfxItemSet* pSet = 0											);
    const SwTOXBase* GetCurTOX( const SwPosition& rPos ) const;
    const SwAttrSet& GetTOXBaseAttrSet(const SwTOXBase& rTOX) const;

    sal_Bool DeleteTOX( const SwTOXBase& rTOXBase, sal_Bool bDelNodes = sal_False );
    String GetUniqueTOXBaseName( const SwTOXType& rType,
                                const String* pChkStr = 0 ) const;

    sal_Bool SetTOXBaseName(const SwTOXBase& rTOXBase, const String& rName);

    // nach einlesen einer Datei alle Verzeichnisse updaten
    void SetUpdateTOX( sal_Bool bFlag = sal_True )		{ bUpdateTOX = bFlag; }
    sal_Bool IsUpdateTOX() const					{ return bUpdateTOX; }

    const String&	GetTOIAutoMarkURL() const {return sTOIAutoMarkURL;}
    void			SetTOIAutoMarkURL(const String& rSet)  {sTOIAutoMarkURL = rSet;}
    void 			ApplyAutoMark();

    sal_Bool IsInReading() const					{ return bInReading; }

    // - Verzeichnis-Typen verwalten
    sal_uInt16 GetTOXTypeCount( TOXTypes eTyp ) const;
    const SwTOXType* GetTOXType( TOXTypes eTyp, sal_uInt16 nId ) const;
    const SwTOXType* InsertTOXType( const SwTOXType& rTyp );
    const SwTOXTypes& GetTOXTypes() const { return *pTOXTypes; }


    // - Schluessel fuer die Indexverwaltung

    // Sortieren Tabellen Text
    sal_Bool SortTbl(const SwSelBoxes& rBoxes, const SwSortOptions&);
    sal_Bool SortText(const SwPaM&, const SwSortOptions&);

        // korrigiere die im Dokument angemeldeten SwPosition-Objecte,
        // wie z.B. die ::com::sun::star::text::Bookmarks oder die Verzeichnisse.
        // JP 22.06.95: ist bMoveCrsr gesetzt, verschiebe auch die Crsr

        // Setzt alles in rOldNode auf rNewPos + Offset
    void CorrAbs( const SwNodeIndex& rOldNode, const SwPosition& rNewPos,
                    const xub_StrLen nOffset = 0, sal_Bool bMoveCrsr = sal_False );
        // Setzt alles im Bereich von [rStartNode, rEndNode] nach rNewPos
    void CorrAbs( const SwNodeIndex& rStartNode, const SwNodeIndex& rEndNode,
                    const SwPosition& rNewPos, sal_Bool bMoveCrsr = sal_False );
        // Setzt alles im Bereich von rRange nach rNewPos
        // Setzt alles in rOldNode auf relative Pos
    void CorrRel( const SwNodeIndex& rOldNode, const SwPosition& rNewPos,
                    const xub_StrLen nOffset = 0, sal_Bool bMoveCrsr = sal_False );

        // GliederungsRegeln erfragen / setzen
    const SwNumRule* GetOutlineNumRule() const { return pOutlineRule; }
    void SetOutlineNumRule( const SwNumRule& rRule );
    // Gliederung - hoch-/runterstufen
    // Gliederung - hoch-/runtermoven
        // zu diesem Gliederungspunkt
    // die Aenderungen an den Gliederungsvorlagen in die OutlineRule uebernehmen
    void SetOutlineLSpace( sal_uInt8 nLevel, short nFirstLnOfst, sal_uInt16 nLSpace );

        // setzt, wenn noch keine Numerierung, sonst wird geaendert
        // arbeitet mit alten und neuen Regeln, nur Differenzen aktualisieren
    /** #109308# new parameter
        @param bCalledFromShell
        - sal_True called from shel
        - sal_False else
    */
    void SetNumRule( const SwPaM&, const SwNumRule&,
                     sal_Bool bSetAbsLSpace = sal_True,
                     sal_Bool bCalledFromShell = sal_False );
        // ab hier neu starten lassen oder den Start wieder aufheben
    void SetNumRuleStart( const SwPosition& rPos, sal_Bool bFlag = sal_True );
    void SetNodeNumStart( const SwPosition& rPos, sal_uInt16 nStt = USHRT_MAX );

    SwNumRule* GetCurrNumRule( const SwPosition& rPos ) const;
    SwNumRuleTbl& GetNumRuleTbl() { return *pNumRuleTbl; }
    const SwNumRuleTbl& GetNumRuleTbl() const { return *pNumRuleTbl; }
    sal_uInt16 MakeNumRule( const String &rName, const SwNumRule* pCpy = 0 );
    sal_uInt16 FindNumRule( const String& rName ) const;
    SwNumRule* FindNumRulePtr( const String& rName ) const;
    // loeschen geht nur, wenn die ::com::sun::star::chaos::Rule niemand benutzt!
    sal_Bool DelNumRule( const String& rName );
    String GetUniqueNumRuleName( const String* pChkStr = 0, sal_Bool bAutoNum = sal_True ) const;
    void UpdateNumRule( const String& rName, ULONG nUpdPos );
    void UpdateNumRule();	// alle invaliden Updaten
    void ChgNumRuleFmts( const SwNumRule& rRule );

        // zum naechsten/vorhergehenden Punkt auf gleicher Ebene

        // Absaetze ohne Numerierung, aber mit Einzuegen
        // Loeschen, Splitten der Aufzaehlungsliste
    sal_Bool DelNumRules( const SwPaM& );
        // Hoch-/Runterstufen
    sal_Bool NumUpDown( const SwPaM&, sal_Bool bDown = sal_True );
        // Bewegt selektierte Absaetze (nicht nur Numerierungen)
        // entsprechend des Offsets. (negativ: zum Doc-Anf.)
        // No-/Numerierung ueber Delete/Backspace ein/abschalten
        // Animation der Grafiken stoppen
    void StopNumRuleAnimations( OutputDevice* );

        // fuege eine neue Tabelle auf der Position rPos ein. (es
        // wird vor dem Node eingefuegt !!)
        //JP 28.10.96:
        // 	fuer AutoFormat bei der Eingabe: dann muessen die Spalten
        //	auf die vordefinierten Breite gesetzt werden. Im Array stehen die
        // 	Positionen der Spalten!! (nicht deren Breite!)
    /* #109161# new parameter bCalledFromShell:

       TRUE: called from shell -> propagate existing adjust item at
       rPos to every new cell. A existing adjust item in the table
       heading or table contents paragraph style prevent that
       propagation.

       FALSE: do not propagate
    */
    const SwTable* InsertTable( const SwPosition& rPos, sal_uInt16 nRows,
                                sal_uInt16 nCols, SwHoriOrient eAdjust,
                                sal_uInt16 nInsert = HEADLINE_NO_BORDER,
                                const SwTableAutoFmt* pTAFmt = 0,
                                const SvUShorts* pColArr = 0,
                                BOOL bCalledFromShell = FALSE );

        // steht der Index in einer Tabelle, dann returne den TableNode sonst 0
                 SwTableNode* IsIdxInTbl( const SwNodeIndex& rIdx );
    inline const SwTableNode* IsIdxInTbl( const SwNodeIndex& rIdx ) const;

        // erzeuge aus dem makierten Bereich eine ausgeglichene Tabelle
        // erzeuge aus der Tabelle wieder normalen Text
        // einfuegen von Spalten/Zeilen in der Tabelle
    sal_Bool InsertCol( const SwCursor& /*rCursor*/,
                        sal_uInt16 nCnt = 1, sal_Bool bBehind = sal_True ){DBG_BF_ASSERT(0, "STRIP"); (void)nCnt; (void)bBehind; return FALSE;}
    sal_Bool InsertRow( const SwCursor& /*rCursor*/,
                    sal_uInt16 nCnt = 1, sal_Bool bBehind = sal_True ){DBG_BF_ASSERT(0, "STRIP"); (void)nCnt; (void)bBehind; return FALSE;}
    sal_Bool DeleteRow( const SwCursor& /*rCursor*/ ){DBG_BF_ASSERT(0, "STRIP"); return FALSE;}
    sal_Bool DeleteCol( const SwCursor& /*rCursor*/ ){DBG_BF_ASSERT(0, "STRIP"); return FALSE;}
        // teilen / zusammenfassen von Boxen in der Tabelle
    sal_Bool SplitTbl( const SwSelBoxes& rBoxes, sal_Bool bVert = sal_True,
                       sal_uInt16 nCnt = 1, sal_Bool bSameHeight = sal_False );
        // returnt den enum TableMergeErr
    sal_uInt16 MergeTbl( SwPaM& /*rPam*/ ){DBG_BF_ASSERT(0, "STRIP"); return 0;}
    String GetUniqueTblName() const;

        // aus der FEShell wg.. Undo und bModified

    // Direktzugriff fuer Uno
    void SetTabCols(SwTable& /*rTab*/, const SwTabCols& /*rNew*/, SwTabCols& /*rOld*/,
                                    const SwTableBox* /*pStart*/, sal_Bool /*bCurRowOnly*/){DBG_BF_ASSERT(0, "STRIP");}

    void SetHeadlineRepeat( SwTable& /*rTable*/, sal_Bool /*bSet*/ ){DBG_BF_ASSERT(0, "STRIP");}
        // AutoFormat fuer die Tabelle/TabellenSelection
    sal_Bool SetTableAutoFmt( const SwSelBoxes& /*rBoxes*/, const SwTableAutoFmt& /*rNew*/ ){DBG_BF_ASSERT(0, "STRIP"); return FALSE;}
        // Erfrage wie attributiert ist
        // setze das TabelleAttribut Undo auf:
        // setze das InsertDB als Tabelle Undo auf:
        // setze die Spalten/Zeilen/ZTellen Breite/Hoehe
    SwTableBoxFmt* MakeTableBoxFmt();
    SwTableLineFmt* MakeTableLineFmt();
    // teste ob die Box ein numerischen Wert darstellt und aender dann ggfs.
    // das Format der Box
    void SetTblBoxFormulaAttrs( SwTableBox& /*rBox*/, const SfxItemSet& /*rSet*/ ){DBG_BF_ASSERT(0, "STRIP");}
    void ClearBoxNumAttrs( const SwNodeIndex& rNode );



    // Tabelle an der Position in der GrundLine aufsplitten, sprich eine
    // neue Tabelle erzeugen.
    // und die Umkehrung davon. rPos muss in der Tabelle stehen, die bestehen
    // bleibt. Das Flag besagt ob die aktuelle mit der davor oder dahinter
    // stehenden vereint wird.

    // Raeume die Umrandung innerhalb der Tabelle ein wenig auf (doppelte
    // an einer Kante erkennen und beseitigen)
    // Charts der angegebenen Tabelle zum Update bewegen
    // update all charts, for that exists any table
    void UpdateAllCharts() 			{ DoUpdateAllCharts( 0 ); }
    // Tabelle wird umbenannt und aktualisiert die Charts
    void SetTableName( SwFrmFmt& rTblFmt, const String &rNewName );

    // returne zum Namen die im Doc gesetzte Referenz
    const SwFmtRefMark* GetRefMark( const String& rName ) const;
    // returne die RefMark per Index - fuer Uno
    // returne die Namen aller im Doc gesetzten Referenzen.
    // 	Ist der ArrayPointer 0 dann returne nur, ob im Doc. eine RefMark
    //	gesetzt ist
    sal_uInt16 GetRefMarks( SvStringsDtor* = 0 ) const;

    //Einfuegen einer Beschriftung - falls ein FlyFormat erzeugt wird, so
    // returne dieses.

    // erfrage den Attribut Pool
    const SwAttrPool& GetAttrPool() const	{ return aAttrPool; }
          SwAttrPool& GetAttrPool() 		{ return aAttrPool; }

    // suche ueber das Layout eine EditShell und ggfs. eine ViewShell
    SwEditShell* GetEditShell( ViewShell** ppSh = 0 ) const;

    // OLE 2.0-Benachrichtung
    inline		 void  SetOle2Link(const Link& rLink) {aOle2Link = rLink;}
    inline const Link& GetOle2Link() const {return aOle2Link;}

    // SS fuer Bereiche
    SwSection* Insert( const SwPaM& rRange, const SwSection& rNew,
                        const SfxItemSet* pAttr = 0, sal_Bool bUpdate = sal_True );
    sal_uInt16 IsInsRegionAvailable( const SwPaM& rRange,
                                const SwNode** ppSttNd = 0 ) const;
    SwSection* GetCurrSection( const SwPosition& rPos ) const;
    SwSectionFmts& GetSections() { return *pSectionFmtTbl; }
    const SwSectionFmts& GetSections() const { return *pSectionFmtTbl; }
    SwSectionFmt *MakeSectionFmt( SwSectionFmt *pDerivedFrom );
    void DelSectionFmt( SwSectionFmt *pFmt, sal_Bool bDelNodes = sal_False );
    void ChgSection( sal_uInt16 nSect, const SwSection&, const SfxItemSet* = 0, sal_Bool bPreventLinkUpdate = FALSE);
    String GetUniqueSectionName( const String* pChkStr = 0 ) const;


    // Pointer auf die SfxDocShell vom Doc, kann 0 sein !!!
          SwDocShell* GetDocShell() 		{ return pDocShell; }
    const SwDocShell* GetDocShell() const	{ return pDocShell; }
    void SetDocShell( SwDocShell* pDSh );

    // falls beim Kopieren von OLE-Nodes eine DocShell angelegt werden muss,
    // dann MUSS der Ref-Pointer besetzt sein!!!!
    SvEmbeddedObjectRef* GetRefForDocShell()			{ return pDocShRef; }
    void SetRefForDocShell( SvEmbeddedObjectRef* p )	{ pDocShRef = p; }

        // fuer die TextBausteine - diese habe nur ein SvPersist zur
        // Verfuegung
         SvPersist* GetPersist() const;

    // Pointer auf den Storage des SfxDocShells, kann 0 sein !!!
    SvStorage* GetDocStorage();

        // abfrage/setze Flag, ob das Dokument im asynchronen Laden ist
    sal_Bool IsInLoadAsynchron() const				{ return bInLoadAsynchron; }
    void SetInLoadAsynchron( sal_Bool bFlag )		{ bInLoadAsynchron = bFlag; }

    // SS fuers Linken von Dokumentteilen
    ::binfilter::SvLinkSource* CreateLinkSource( const String& rItem );
    // erzeuge um das zu Servende Object eine Selektion
    sal_Bool SelectServerObj( const String& rStr, SwPaM*& rpPam,
                            SwNodeRange*& rpRange ) const;
    // erfage alle zu servendenen Objecte

    // fuer Drag&Move: ( z.B. RefMarks "verschieben" erlauben )
    sal_Bool IsCopyIsMove() const 				{ return bCopyIsMove; }
    void SetCopyIsMove( sal_Bool bFlag )		{ bCopyIsMove = bFlag; }

     SwDrawContact* GroupSelection( SdrView& );
    void UnGroupSelection( SdrView& );

    SdrModel* _MakeDrawModel();
    inline SdrModel* MakeDrawModel()
    { return GetDrawModel() ? GetDrawModel() : _MakeDrawModel(); }
    void SetCalcFieldValueHdl(Outliner* pOutliner);

    // erfrage ob die ::com::sun::star::util::URL besucht war. Uebers Doc, falls nur ein ::com::sun::star::text::Bookmark
    // angegeben ist. Dann muss der Doc. Name davor gesetzt werden!
    sal_Bool IsVisitedURL( const String& rURL ) const;

    // speicher die akt. Werte fuer die automatische Aufnahme von Ausnahmen
    // in die Autokorrektur
    SwAutoCorrExceptWord* GetAutoCorrExceptWord()		{ return pACEWord; }


    // rufe ins dunkle Basic, mit evt. Return String
    // rufe ins dunkle Basic/JavaScript

    // linken Rand ueber Objectleiste einstellen (aenhlich dem Stufen von
    // Numerierungen), optional kann man "um" den Offset stufen oder "auf"
    // die Position gestuft werden (bModulus = sal_True)

    // Numberformatter erfragen
    inline	  	 SvNumberFormatter* GetNumberFormatter( sal_Bool bCreate = sal_True );
    inline const SvNumberFormatter* GetNumberFormatter( sal_Bool bCreate = sal_True ) const;

    // loesche den nicht sichtbaren ::com::sun::star::ucb::Content aus dem Document, wie z.B.:
    // versteckte Bereiche, versteckte Absaetze
    // embedded alle lokalen Links (Bereiche/Grafiken)
    // erzeuge Anhand der vorgebenen Collection Teildokumente
    // falls keine angegeben ist, nehme die Kapitelvorlage der 1. Ebene


    // alles fuers Redlining
    SwRedlineMode GetRedlineMode() const { return eRedlineMode; }
    sal_Bool IsRedlineOn() const { return ::binfilter::IsRedlineOn( eRedlineMode ); }
    sal_Bool IsIgnoreRedline() const { return REDLINE_IGNORE & eRedlineMode; }
    void SetRedlineMode_intern( sal_uInt16 eMode ) { eRedlineMode = (SwRedlineMode)eMode; }
    void SetRedlineMode( sal_uInt16 eMode );

    const SwRedlineTbl& GetRedlineTbl() const { return *pRedlineTbl; }
    sal_Bool AppendRedline( SwRedline* pPtr, sal_Bool bCallDelete = sal_True );
    sal_Bool DeleteRedline( const SwPaM& rPam, sal_Bool bSaveInUndo = sal_True,
                        sal_uInt16 nDelType = USHRT_MAX );
    sal_Bool DeleteRedline( const SwStartNode& rSection, sal_Bool bSaveInUndo = sal_True,
                        sal_uInt16 nDelType = USHRT_MAX );
    sal_uInt16 GetRedlinePos( const SwNode& rNd, sal_uInt16 nType = USHRT_MAX ) const;
    const SwRedline* GetRedline( const SwPosition& rPos,
                                sal_uInt16* pFndPos = 0 ) const;

    sal_Bool IsRedlineMove() const 				{ return bIsRedlineMove; }
    void SetRedlineMove( sal_Bool bFlag )		{ bIsRedlineMove = bFlag; }


    // alle Redline invalidieren, die Darstellung hat sich geaendert
    // legt gegebenenfalls einen neuen Author an
    sal_uInt16 GetRedlineAuthor();
    // fuer die Reader usw. - neuen Author in die Tabelle eintragen
    sal_uInt16 InsertRedlineAuthor( const String& );
    // Kommentar am Redline an der Position setzen

        // Passwords for Redline ask/set
    const ::com::sun::star::uno::Sequence <sal_Int8>&
            GetRedlinePasswd() const 			{ return aRedlinePasswd; }
    void SetRedlinePasswd(
            const ::com::sun::star::uno::Sequence <sal_Int8>& rNew );

    //  vergleiche zwei Dokument miteinander
    // merge zweier Dokumente
    // setze Kommentar-Text fuers Redline, das dann per AppendRedline
    // hereinkommt. Wird vom Autoformat benutzt. 0-Pointer setzt den Modus
    // wieder zurueck. Die SequenceNummer ist fuers UI-seitige zusammen-
    // fassen von Redlines.

    sal_Bool IsAutoFmtRedline() const			{ return bIsAutoFmtRedline; }
    void SetAutoFmtRedline( sal_Bool bFlag ) 	{ bIsAutoFmtRedline = bFlag; }

    // fuer AutoFormat: mit Undo/Redlining - Behandlung

    // !!!NUR fuer die SW-Textblocks!! beachtet kein LAYOUT!!!

    // erfrage / setze die Daten fuer die PagePreView
    const SwPagePreViewPrtData* GetPreViewPrtData() const { return pPgPViewPrtData; }
    // wenn der Pointer == 0 ist, dann wird im Doc der Pointer zerstoert,
    // ansonsten wird das Object kopiert.
    // Der Pointer geht NICHT in den Besitz des Doc's!!
    void SetPreViewPrtData( const SwPagePreViewPrtData* pData );

    // update all modified OLE-Objects. The modification is called over the
    // StarOne - Interface				--> Bug 67026
    void SetOLEObjModified()
    {	if( GetRootFrm() ) aOLEModifiedTimer.Start(); }

    // -------------------- Uno - Schnittstellen ---------------------------
    const SwUnoCrsrTbl& GetUnoCrsrTbl() const 		{ return *pUnoCrsrTbl; }
    SwUnoCrsr* CreateUnoCrsr( const SwPosition& rPos, sal_Bool bTblCrsr = sal_False );
    // -------------------- Uno - Schnittstellen ---------------------------

    // -------------------- FeShell - Schnittstellen -----------------------
    // !!!!! diese gehen immer davon aus, das ein Layout existiert  !!!!
    sal_Bool ChgAnchor( const SdrMarkList &rMrkList, int eAnchorId,
                        sal_Bool bSameOnly, sal_Bool bPosCorr );

    void SetTabBorders( const SwCursor& /*rCursor*/, const SfxItemSet& /*rSet*/ ){DBG_BF_ASSERT(0, "STRIP");}
    void GetTabBorders( const SwCursor& rCursor, SfxItemSet& rSet ) const;
    void SetBoxAttr( const SwCursor& /*rCursor*/, const SfxPoolItem& /*rNew*/ ){DBG_BF_ASSERT(0, "STRIP");}
    sal_Bool GetBoxBackground( const SwCursor& /*rCursor*/, SvxBrushItem& /*rToFill*/ ) const{DBG_BF_ASSERT(0, "STRIP"); return FALSE;}

    int Chain( SwFrmFmt &rSource, const SwFrmFmt &rDest );
    void Unchain( SwFrmFmt &rFmt );

    // fuers Copy/Move aus der FrmShell
    SdrObject* CloneSdrObj( const SdrObject&, sal_Bool bMoveWithinDoc = sal_False,
                            sal_Bool bInsInPage = sal_True );

    //
    // -------------------- FeShell - Schnittstellen Ende ------------------


    // Schnittstelle fuer die TextInputDaten - ( fuer die Texteingabe
    // von japanischen/chinesischen Zeichen)
    SwExtTextInput* GetExtTextInput( const SwNode& rNd,
                                xub_StrLen nCntntPos = STRING_NOTFOUND) const;

    sal_Bool ContainsMSVBasic() const 			{ return bContains_MSVBasic; }
    void SetContainsMSVBasic( sal_Bool bFlag )	{ bContains_MSVBasic = bFlag; }

    // Interface for the forbidden characters of any asian/.. languages
    const ::com::sun::star::i18n::
        ForbiddenCharacters* GetForbiddenCharacters( USHORT nLang,
                                                    BOOL bLocaleData ) const;
    const rtl::Reference<SvxForbiddenCharactersTable>& GetForbiddenCharacterTbl() const
            { return xForbiddenCharsTable; }
    rtl::Reference<SvxForbiddenCharactersTable>& GetForbiddenCharacterTbl();

    // ------------------- Zugriff auf Dummy-Member --------------------

    sal_Bool IsParaSpaceMax() const { return n8Dummy1 & DUMMY_PARASPACEMAX; }
    sal_Bool IsParaSpaceMaxAtPages() const { return n8Dummy1 & DUMMY_PARASPACEMAX_AT_PAGES; }
    void SetParaSpaceMax( sal_Bool bNew, sal_Bool bAtPages )
    {
        if( bNew ) n8Dummy1 |= DUMMY_PARASPACEMAX; else n8Dummy1 &= ~DUMMY_PARASPACEMAX;
        if( bAtPages ) n8Dummy1 |= DUMMY_PARASPACEMAX_AT_PAGES; else n8Dummy1 &= ~DUMMY_PARASPACEMAX_AT_PAGES;
    }

    sal_Bool IsTabCompat() const { return n8Dummy1 & DUMMY_TAB_COMPAT; }
    void SetTabCompat( sal_Bool bNew )
    {
        if( bNew ) n8Dummy1 |= DUMMY_TAB_COMPAT; else n8Dummy1 &= ~DUMMY_TAB_COMPAT;
    }

    sal_Bool IsUseVirtualDevice() const { return n8Dummy1 & DUMMY_USE_VIRTUAL_DEVICE; }
    void _SetUseVirtualDevice( sal_Bool bNew )
    {
        if( bNew ) n8Dummy1 |= DUMMY_USE_VIRTUAL_DEVICE;
        else n8Dummy1 &= ~DUMMY_USE_VIRTUAL_DEVICE;
    }

    sal_Bool IsAddFlyOffsets() const { return n8Dummy2 & DUMMY_ADD_FLY_OFFSETS; }
    void SetAddFlyOffsets( sal_Bool bNew )
    {
        if( bNew ) n8Dummy2 |= DUMMY_ADD_FLY_OFFSETS;
        else n8Dummy2 &= ~DUMMY_ADD_FLY_OFFSETS;
    }

    void ReadLayoutCache( SvStream& rStream );
    void WriteLayoutCache( SvStream& rStream );
    SwLayoutCache* GetLayoutCache() const { return pLayoutCache; }

    void SetULongDummy1( sal_uInt32 n ) { n32Dummy1 = n; }
    void SetULongDummy2( sal_uInt32 n ) { n32Dummy2 = n; }
    void SetByteDummy1( sal_Int8 n ) { n8Dummy1 = n; }
    void SetByteDummy2( sal_Int8 n ) { n8Dummy2 = n; }
    void SetStringDummy1( const String& r ) { sDummy1 = r; }
    void SetStringDummy2( const String& r ) { sDummy2 = r; }
    sal_uInt32 GetULongDummy1() const { return n32Dummy1; }
    sal_uInt32 GetULongDummy2() const { return n32Dummy2; }
    sal_Int8 GetByteDummy1() const { return n8Dummy1; }
    sal_Int8 GetByteDummy2() const { return n8Dummy2; }
    const String& GetStringDummy1() const { return sDummy1; }
    const String& GetStringDummy2() const { return sDummy2; }

    // #102505# ->
    /**
       Append a new temporary auto correction.

       @param aWrong the wrong word
       @param aCorrect the correct word
    */
    void AppendTmpCorr(const String & aWrong, const String & aCorrect);

    /** Remove a temporary auto correction.

        @param aWrong the wrong word whose correction shall be removed
    */
    void RemoveTmpCorr(const String & aWrong);
    // <- #102505#

    // call back for API wrapper
    SwModify*	GetUnoCallBack() const;
};


// Diese Methode wird im Dtor vom SwDoc gerufen und loescht den Cache
// der Konturobjekte
void ClrContourCache();


//------------------ inline impl. ---------------------------------

inline const SwTableNode* SwDoc::IsIdxInTbl( const SwNodeIndex& rIdx ) const
{
    return ((SwDoc*)this)->IsIdxInTbl( rIdx );
}

inline SvNumberFormatter* SwDoc::GetNumberFormatter( sal_Bool bCreate )
{
    if( bCreate && !pNumberFormatter )
        _CreateNumberFormatter();
    return pNumberFormatter;
}

inline const SvNumberFormatter* SwDoc::GetNumberFormatter( sal_Bool bCreate ) const
{
    return ((SwDoc*)this)->GetNumberFormatter( bCreate );
}


// ist das NodesArray das normale vom Doc? (nicht das UndoNds, .. )
// Implementierung steht hier, weil man dazu Doc kennen muss!
inline sal_Bool SwNodes::IsDocNodes() const
{
    return this == &pMyDoc->GetNodes();
}

inline void SwDoc::SetOLEPrtNotifyPending( sal_Bool bSet )
{
    bOLEPrtNotifyPending = bSet;
    if( !bSet )
        bAllOLENotify = sal_False;
}


} //namespace binfilter
#endif	//_DOC_HXX

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
