/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: undobj.hxx,v $
 *
 *  $Revision: 1.5 $
 *
 *  last change: $Author: rt $ $Date: 2006-10-28 05:00:21 $
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
#ifndef _UNDOBJ_HXX
#define _UNDOBJ_HXX

#ifndef _SVMEMPOOL_HXX //autogen
#include <tools/mempool.hxx>
#endif
#ifndef _SVSTDARR_HXX
#define _SVSTDARR_USHORTS
#define _SVSTDARR_ULONGS
#define _SVSTDARR_BOOLS
#define _SVSTDARR_BYTES
#define _SVSTDARR_USHORTSSORT
#include <svtools/svstdarr.hxx>
#endif
#ifndef _SFXITEMSET_HXX //autogen
#include <svtools/itemset.hxx>
#endif
#ifndef _COM_SUN_STAR_UNO_SEQUENCE_H_
#include <com/sun/star/uno/Sequence.h>
#endif
#ifndef _NUMRULE_HXX
#include <numrule.hxx>
#endif
#ifndef _REDLENUM_HXX
#include <redlenum.hxx>
#endif
class Graphic; 
namespace binfilter {

class SwUndoIter;
class SwHistory;
class SwIndex;
class SwPaM;
struct SwPosition;
class SwDoc;
class SwNodes;
class SwFmt;
class SwFmtColl;
class SwTxtFmtColl;
class SwTxtNode;
class SwpHints;
class SwBookmark;
class SwTableNode;
class SwTable;
class SwTableBox;
struct SwSortOptions;
class SwFrmFmt;
class SwHstryBookmark;
class SwSection;
class SwSectionFmt;
class SvxTabStopItem;
class SwNumSection;
class SwDDEFieldType;

class SwGrfNode;
class SwUndos;
class SwUndoRange;
class SwFtnInfo;
class SwEndNoteInfo;
class SwNodeIndex;
class SwNodeRange;
class SwFmtAnchor;
struct SwUndoGroupObjImpl;
class SdrMark;
class SdrMarkList;
class SdrObject;
class SdrObjGroup;
class SdrUndoAction;
class SwDrawFrmFmt;
class SwTableAutoFmt;
class SwSelBoxes;
class SwTableSortBoxes;
class SwUndoSaveSections;
class SwUndoMoves;
class SwStartNode;
class _SaveFlyArr;
class SwTblToTxtSaves;
class SwRedlineData;
class SwRedlineSaveData;
class SwRedline;
class SwSectionNode;

namespace utl {
    class TransliterationWrapper;
}//STRIP008 ;

#ifndef PRODUCT
class Writer;
class SwUndo;
#define OUT_UNDOBJ( name )	\
    friend Writer& OutUndo_ ## name( Writer&, const SwUndo& );
#else
#define OUT_UNDOBJ( name )
#endif


typedef SwRedlineSaveData* SwRedlineSaveDataPtr;
SV_DECL_PTRARR_DEL( SwRedlineSaveDatas, SwRedlineSaveDataPtr, 8, 8 )

class SwUndo
{
    USHORT nId;
    USHORT nOrigRedlineMode;
protected:

    void SetId( USHORT nNew ) { nId = nNew; }

public:
    SwUndo( USHORT nI ) { nId = nI; nOrigRedlineMode = REDLINE_NONE; }
    virtual ~SwUndo();

    USHORT GetId() const { return nId; }

        // das UndoObject merkt sich, welcher Mode eingeschaltet war.
        // In Undo/Redo/Repeat wird dann immer auf diesen zurueck geschaltet
    USHORT GetRedlineMode() const { return nOrigRedlineMode; }
    void SetRedlineMode( USHORT eMode ) { nOrigRedlineMode = eMode; }

        // sicher und setze die RedlineDaten
    static BOOL FillSaveData( const SwPaM& rRange, SwRedlineSaveDatas& rSData,
                            BOOL bDelRange = TRUE, BOOL bCopyNext = TRUE );
};


// diese Klasse muss in ein Undo-Object vererbt werden, wenn dieses Inhalt
// fuers Redo/Undo ... speichert
class SwUndoSaveCntnt
{
protected:

    SwHistory* pHistory;

    // wird fuer das loeschen von Inhalt benoetigt. Fuer das ReDo werden
    // Inhalte in das UndoNodesArray verschoben. Diese Methoden fuegen
    // am Ende eines TextNodes ein Trenner fuer die Attribute. Damit werden
    // Attribute nicht expandiert.
    // MoveTo.. 	verschiebt aus dem NodesArray in das UndoNodesArray
    // MoveFrom..	verschiebt aus dem UndoNodesArray in das NodesArray
    void MoveToUndoNds( SwPaM& rPam,
                        SwNodeIndex* pNodeIdx = 0, SwIndex* pCntIdx = 0,
                        ULONG* pEndNdIdx = 0, xub_StrLen * pEndCntIdx = 0 );

    // diese beiden Methoden bewegen den SPoint vom Pam zurueck/vor. Damit
    // kann fuer ein Undo/Redo ein Bereich aufgespannt werden. (Der
    // SPoint liegt dann vor dem manipuliertem Bereich !!)
    // Das Flag gibt an, ob noch vorm SPoint Inhalt steht.

    // vor dem Move ins UndoNodes-Array muss dafuer gesorgt werden, das
    // die Inhaltstragenden Attribute aus dem Nodes-Array entfernt werden.
    enum DelCntntType{	DELCNT_FTN = 0x01,
                        DELCNT_FLY = 0x02,
                        DELCNT_TOC = 0x04,
                        DELCNT_BKM = 0x08,
                        DELCNT_ALL = 0x0F,
                        DELCNT_CHKNOCNTNT = 0x80 	// nur den NodeIndex beachten
                    };
    void DelCntntIndex( const SwPosition& pMark, const SwPosition& pPoint,
                        DelCntntType nDelCntntType = DELCNT_ALL );

public:
    SwUndoSaveCntnt();
    ~SwUndoSaveCntnt();
    OUT_UNDOBJ( SaveCntnt )
};


// sicher eine vollstaendige Section im Nodes-Array
class SwUndoSaveSection : private SwUndoSaveCntnt
{
    SwNodeIndex *pMvStt;
    SwRedlineSaveDatas* pRedlSaveData;
    ULONG nMvLen;			// Index ins UndoNodes-Array
    ULONG nStartPos;

protected:
    SwNodeIndex* GetMvSttIdx() const { return pMvStt; }
    ULONG GetMvNodeCnt() const { return nMvLen; }

public:
    SwUndoSaveSection();
    ~SwUndoSaveSection();

    void SaveSection( SwDoc* pDoc, const SwNodeIndex& rSttIdx );
    void SaveSection( SwDoc* pDoc, const SwNodeRange& rRange );

    const SwHistory* GetHistory() const { return pHistory; }
          SwHistory* GetHistory() 		{ return pHistory; }
    OUT_UNDOBJ( SaveSection )
};


// Diese Klasse speichert den Pam als USHORT's und kann diese wieder zu
// einem PaM zusammensetzen
class SwUndRng
{
public:
    ULONG nSttNode, nEndNode;
    xub_StrLen nSttCntnt, nEndCntnt;

    SwUndRng();
    SwUndRng( const SwPaM& );

    void SetValues( const SwPaM& rPam );
};


class SwUndoStart: public SwUndo
{
    // Um innerhalb von Undo zuerkennen, wann ein Start vorliegt, gibt
    // GetId() immer die UNDO_START zurueck. Die UserId kann ueber
    // GetUserId() erfragt werden.
    USHORT nUserId;
    // fuer die "Verpointerung" von Start- und End-Undos
    USHORT nEndOffset;
public:
    SwUndoStart( USHORT nId );
    USHORT GetUserId() const { return nUserId; }
    // Setzen vom End-Undo-Offset geschieht im Doc::EndUndo
    USHORT GetEndOffset() const { return nEndOffset; }
    void SetEndOffset( USHORT n ) { nEndOffset = n; }
    OUT_UNDOBJ( Start )
};

class SwUndoEnd: public SwUndo
{
    // Um innerhalb von Undo zuerkennen, wann ein Ende vorliegt, gibt
    // GetId() immer die UNDO_END zurueck. Die UserId kann ueber
    // GetUserId() erfragt werden.
    USHORT nUserId;
    // fuer die "Verpointerung" von Start- und End-Undos
    USHORT nSttOffset;
public:
    SwUndoEnd( USHORT nId );
    USHORT GetUserId() const { return nUserId; }
    // Setzen vom Start-Undo-Offset geschieht im Doc::EndUndo
    USHORT GetSttOffset() const { return nSttOffset; }
    void SetSttOffset( USHORT n ) { nSttOffset = n; }
    OUT_UNDOBJ( End )
};

class SwUndoInsert: public SwUndo, private SwUndoSaveCntnt
{
    SwPosition *pPos; 					// Inhalt fuers Redo
    String* pTxt;
    SwRedlineData* pRedlData;
    ULONG nNode;
    xub_StrLen nCntnt, nLen;
    BOOL bIsWordDelim : 1;
    BOOL bIsAppend : 1;

    friend class SwDoc;		// eigentlich nur SwDoc::Insert( String )
    BOOL CanGrouping( sal_Unicode cIns );
    BOOL CanGrouping( const SwPosition& rPos );

public:
    SwUndoInsert( const SwNodeIndex& rNode, xub_StrLen nCntnt, xub_StrLen nLen,
                  BOOL bWDelim = TRUE );
    SwUndoInsert( const SwNodeIndex& rNode );
    virtual ~SwUndoInsert();

    BOOL CanGrouping( const SwPosition&, sal_Unicode cIns );
    OUT_UNDOBJ( Insert )

    DECL_FIXEDMEMPOOL_NEWDEL(SwUndoInsert)
};


class SwUndoDelete: public SwUndo, private SwUndRng, private SwUndoSaveCntnt
{
    SwNodeIndex* pMvStt;			// Position der Nodes im UndoNodes-Array
    String *pSttStr, *pEndStr;
    SwRedlineData* pRedlData;
    SwRedlineSaveDatas* pRedlSaveData;

    ULONG nNode;
    ULONG nNdDiff;				// Differenz von Nodes vor-nach Delete
    ULONG nSectDiff;			// Diff. von Nodes vor/nach Move mit SectionNodes
    USHORT nSetPos;

    BOOL bGroup : 1; 	// TRUE: ist schon eine Gruppe; wird in CanGrouping() ausgwertet !!
    BOOL bBackSp : 1;	// TRUE: wenn Gruppierung und der Inhalt davor geloescht wird
    BOOL bJoinNext: 1;	// TRUE: wenn der Bereich von Oben nach unten geht
    BOOL bSectNdFnd : 1;	// TRUE: Sonderbehandlung fuer SectionNodes
    BOOL bMvAroundSectNd :1;// TRUE: Sonderbehandlung fuer SectionNodes
    BOOL bTblDelLastNd : 1;	// TRUE: TextNode hinter der Tabelle einf./loeschen
    BOOL bDelFullPara : 1;	// TRUE: gesamte Nodes wurden geloescht
    BOOL bResetPgDesc : 1;	// TRUE: am nachfolgenden Node das PgDsc zuruecksetzen
    BOOL bResetPgBrk : 1;	// TRUE: am nachfolgenden Node das PgBreak zuruecksetzen

    BOOL SaveCntnt( const SwPosition* pStt, const SwPosition* pEnd,
                    SwTxtNode* pSttTxtNd, SwTxtNode* pEndTxtNd );
public:
    SwUndoDelete( SwPaM&, BOOL bFullPara = FALSE );
    virtual ~SwUndoDelete();
    BOOL CanGrouping( SwDoc*, const SwPaM& );

    void SetTblDelLastNd() 		{ bTblDelLastNd = TRUE; }

    // fuer die PageDesc/PageBreak Attribute einer Tabelle
    void SetPgBrkFlags( BOOL bPageBreak, BOOL bPageDesc )
        { bResetPgDesc = bPageDesc; bResetPgBrk = bPageBreak; }

    OUT_UNDOBJ( Delete )

    DECL_FIXEDMEMPOOL_NEWDEL(SwUndoDelete)
};




class SwUndoSplitNode: public SwUndo
{
    SwHistory* pHistory;
    SwRedlineData* pRedlData;
    ULONG nNode;
    xub_StrLen nCntnt;
    BOOL bTblFlag : 1;
    BOOL bChkTblStt : 1;
public:
    SwUndoSplitNode( SwDoc* pDoc, const SwPosition& rPos, BOOL bChkTbl );
    virtual ~SwUndoSplitNode();
    void SetTblFlag() 		{ bTblFlag = TRUE; }
    OUT_UNDOBJ( SplitNode )
};




class SwUndoAttr : public SwUndo, private SwUndRng
{
    SfxItemSet aSet;				// Attribute fuers Redo
    SwHistory* pHistory;			// History fuers Undo
    SwRedlineData* pRedlData;		// Redlining
    SwRedlineSaveDatas* pRedlSaveData;
    ULONG nNdIdx;					// fuers Redlining - Offset
    USHORT nInsFlags;				// Einfuege Flags

public:
    SwUndoAttr( const SwPaM&, const SfxItemSet&, USHORT nFlags = 0  );
    SwUndoAttr( const SwPaM&, const SfxPoolItem&, USHORT nFlags = 0 );
    virtual ~SwUndoAttr();
    SwHistory* GetHistory() { return pHistory; }

    OUT_UNDOBJ( InsAttr )
};



class SwUndoFmtAttr : public SwUndo
{
    friend class SwUndoDefaultAttr;
    SwFmt* pFmt;
    SfxItemSet* pOldSet;			// die alten Attribute
    ULONG nNode;
    USHORT nFmtWhich;
    BOOL bSaveDrawPt;

    void SaveFlyAnchor( BOOL bSaveDrawPt = FALSE );
    void Init();

public:
    // meldet sich im Format an und sichert sich die alten Attribute
    SwUndoFmtAttr( const SfxItemSet& rOldSet, SwFmt& rFmt,
                    BOOL bSaveDrawPt = TRUE );
    SwUndoFmtAttr( const SfxPoolItem& rItem, SwFmt& rFmt,
                    BOOL bSaveDrawPt = TRUE );
    virtual ~SwUndoFmtAttr();
    OUT_UNDOBJ( InsFmtAttr )

};


// Hilfs-Klasse, um die geaenderten Sets zu "empfangen"
struct _UndoFmtAttr : public SwClient
{
    SwUndoFmtAttr* pUndo;
    BOOL bSaveDrawPt;

    _UndoFmtAttr( SwFmt& rFmt, BOOL bSaveDrawPt = TRUE );
    virtual void Modify( SfxPoolItem*, SfxPoolItem* );
};


class SwUndoFmtColl : public SwUndo, private SwUndRng
{
    SwHistory* pHistory;
    SwFmtColl* pFmtColl;
public:
    SwUndoFmtColl( const SwPaM&, SwFmtColl* );
    virtual ~SwUndoFmtColl();
    SwHistory* GetHistory() { return pHistory; }
    OUT_UNDOBJ( SetFmtColl )
};



// Basis-Klasse fuer Insert von Dokument, Glossaries und Kopieren

class SwUndoInsDoc //STRIP001 : public SwUndoInserts
{
public:
    SwUndoInsDoc( const SwPaM& ){DBG_BF_ASSERT(0, "STRIP");} //STRIP001 SwUndoInsDoc( const SwPaM& );
};


class SwUndoInsTbl : public SwUndo
{
    String sTblNm;
    SwDDEFieldType* pDDEFldType;
    SvUShorts* pColWidth;
    SwRedlineData* 	pRedlData;
    SwTableAutoFmt* pAutoFmt;
    ULONG nSttNode;
    USHORT nRows, nCols;
    USHORT nAdjust;
    USHORT nInsTblFlags;

public:
    SwUndoInsTbl( const SwPosition&, USHORT nCols, USHORT nRows,
                    USHORT eAdjust, USHORT nInsert,
                    const SwTableAutoFmt* pTAFmt, const SvUShorts* pColArr );
    virtual ~SwUndoInsTbl();
    OUT_UNDOBJ( InsTable )
};

class SwUndoTxtToTbl : public SwUndo, public SwUndRng
{
     String sTblNm;
     SvULongs* pDelBoxes;
     SwTableAutoFmt* pAutoFmt;
     SwHistory* pHistory;
     sal_Unicode cTrenner;
     USHORT nAdjust;
     USHORT nInsTblFlags;
     BOOL bSplitEnd : 1;

public:
    SwUndoTxtToTbl( const SwPaM&, sal_Unicode , USHORT, USHORT nInsert,
                    const SwTableAutoFmt* pAFmt );
    virtual ~SwUndoTxtToTbl();
 
};





 class SwUndoTblMerge : public SwUndo, private SwUndRng
 {
    SwHistory* pHistory;

public:
    SwUndoTblMerge( const SwPaM& rTblSel );
    virtual ~SwUndoTblMerge();
};



class _UndoTblCpyTbl_Entries;


class SwUndoCpyTbl : public SwUndo
{
    SwUndoDelete* pDel;
    ULONG nTblNode;
public:
    SwUndoCpyTbl();
    virtual ~SwUndoCpyTbl();
    virtual void Undo( SwUndoIter& );
    virtual void Redo( SwUndoIter& );

    void SetTableSttIdx( ULONG nIdx )			{ nTblNode = nIdx; }
    OUT_UNDOBJ( CpyTbl )
};




class SwUndoBookmark : public SwUndo
{
    SwHstryBookmark* pHBookmark;
protected:
    SwUndoBookmark( USHORT nUndoId, const SwBookmark& );


public:
    virtual ~SwUndoBookmark();
};



class SwUndoInsBookmark : public SwUndoBookmark
{
public:
    SwUndoInsBookmark( const SwBookmark& );
    OUT_UNDOBJ( InsBookmark )
};


/*--------------------------------------------------------------------
    Beschreibung: Undo auf Sorting
 --------------------------------------------------------------------*/






//--------------------------------------------------------------------

class SwUndoFlyBase : public SwUndo, private SwUndoSaveSection
{
protected:
    SwFrmFmt* pFrmFmt;					// das gespeicherte FlyFormat
    ULONG nNdPgPos;
    xub_StrLen nCntPos;	 				// Seite/am Absatz/im Absatz
    USHORT nRndId;
    BOOL bDelFmt;						// loesche das gespeicherte Format


    SwUndoFlyBase( SwFrmFmt* pFormat, USHORT nUndoId );

    SwNodeIndex* GetMvSttIdx() const { return SwUndoSaveSection::GetMvSttIdx(); }
    ULONG GetMvNodeCnt() const { return SwUndoSaveSection::GetMvNodeCnt(); }

public:
    virtual ~SwUndoFlyBase();

    OUT_UNDOBJ( FlyBase )
};

class SwUndoInsLayFmt : public SwUndoFlyBase
{
public:
    SwUndoInsLayFmt( SwFrmFmt* pFormat );

    OUT_UNDOBJ( InsLayFmt )
};

class SwUndoDelLayFmt : public SwUndoFlyBase
{
    BOOL bShowSelFrm;
public:
    SwUndoDelLayFmt( SwFrmFmt* pFormat );


};


class SwUndoSetFlyFmt : public SwUndo, public SwClient
{
    SwFrmFmt* pFrmFmt;					// das gespeicherte FlyFormat
    SwFrmFmt* pOldFmt;					// die alte Fly Vorlage
    SwFrmFmt* pNewFmt;					// die neue Fly Vorlage
    SfxItemSet* pItemSet;				// die zurueck-/ gesetzten Attribute
    ULONG nOldNode, nNewNode;
    xub_StrLen nOldCntnt, nNewCntnt;
    USHORT nOldAnchorTyp, nNewAnchorTyp;
    BOOL bAnchorChgd;


public:
    SwUndoSetFlyFmt( SwFrmFmt& rFlyFmt, SwFrmFmt& rNewFrmFmt );
    virtual ~SwUndoSetFlyFmt();

};

//--------------------------------------------------------------------

class _UnReplaceData;
SV_DECL_PTRARR_DEL( _UnReplaceDatas, _UnReplaceData*, 10, 25 )//STRIP008 ;



//--------------------------------------------------------------------




//------------ Undo von Insert-/Delete-Sections ----------------------

class SwUndoInsSection : public SwUndo, private SwUndRng
{
    SwHistory* pHistory;
    SwSection* pSection;
    SwRedlineData* pRedlData;
    SfxItemSet* pAttr;
    ULONG nSectNodePos;
    BOOL bSplitAtStt : 1;
    BOOL bSplitAtEnd : 1;
    BOOL bUpdateFtn : 1;


public:
    SwUndoInsSection( const SwPaM&, const SwSection&,
                        const SfxItemSet* pSet );
    virtual ~SwUndoInsSection();
    OUT_UNDOBJ( SwUndoInsSection )

    void SetSectNdPos( ULONG nPos ) 		{ nSectNodePos = nPos; }
    void SaveSplitNode( SwTxtNode* pTxtNd, BOOL bAtStt );
    void SetUpdtFtnFlag( BOOL bFlag )		{ bUpdateFtn = bFlag; }
};


class SwUndoChgSection : public SwUndo
{
    ULONG nSttNd;
    SwSection* pSection;
    SfxItemSet* pAttr;
    BOOL bOnlyAttrChgd;
public:
    SwUndoChgSection( const SwSectionFmt&, BOOL bOnlyAttrChgd );
    virtual ~SwUndoChgSection();
};

class SwUndoChgSectPsswd : public SwUndo
{
    ::com::sun::star::uno::Sequence <sal_Int8> aPasswd;
    ULONG nSectNd;
public:
    SwUndoChgSectPsswd(
                const ::com::sun::star::uno::Sequence <sal_Int8> & rOld,
                const SwSectionNode* pSectNd = 0 );
    virtual void Undo( SwUndoIter& );
    virtual void Redo( SwUndoIter& );
    OUT_UNDOBJ( SwUndoChgSectPsswd )
};

//------------ Undo von verschieben/stufen von Gliederung ----------------


//--------------------------------------------------------------------

class SwUndoDefaultAttr : public SwUndo
{
    SfxItemSet* pOldSet;			// die alten Attribute
    SvxTabStopItem* pTabStop;
public:
    // meldet sich im Format an und sichert sich die alten Attribute
    SwUndoDefaultAttr( const SfxItemSet& rOldSet );
    virtual ~SwUndoDefaultAttr();
    OUT_UNDOBJ( DefaultAttr )
};

//--------------------------------------------------------------------
// ---------- Undo fuer Numerierung ----------------------------------

class SwUndoInsNum : public SwUndo, private SwUndRng
{
    SwNumRule aNumRule;
    SwHistory* pHistory;
    ULONG nSttSet;
    SwNumRule* pOldNumRule;
    String sReplaceRule;
    USHORT nLRSavePos;
public:
    SwUndoInsNum( const SwPaM& rPam, const SwNumRule& rRule );
    SwUndoInsNum( const SwNumRule& rOldRule, const SwNumRule& rNewRule );
    SwUndoInsNum( const SwPosition& rPos, const SwNumRule& rRule,
                            const String& rReplaceRule );
    virtual ~SwUndoInsNum();

    void SetSttNum( ULONG nNdIdx ) { nSttSet = nNdIdx; }


    OUT_UNDOBJ( InsNum )
};



class SwUndoNumUpDown : public SwUndo, private SwUndRng
{
    short nOffset;
public:
    SwUndoNumUpDown( const SwPaM& rPam, short nOffset );
    OUT_UNDOBJ( NumUpDown )
};


class SwUndoNumRuleStart : public SwUndo
{
    ULONG nIdx;
    USHORT nOldStt, nNewStt;
    BOOL bSetSttValue : 1;
    BOOL bFlag : 1;
public:
    SwUndoNumRuleStart( const SwPosition& rPos, BOOL bDelete );
    SwUndoNumRuleStart( const SwPosition& rPos, USHORT nStt );
    OUT_UNDOBJ( NumRuleStart )
};

//--------------------------------------------------------------------
// ---------- Undo fuer DrawObjecte ----------------------------------





//--------------------------------------------------------------------


//--------------------------------------------------------------------


//--------------------------------------------------------------------

class SwUndoChgFtn : public SwUndo, private SwUndRng
{
    SwHistory* pHistory;
    String sTxt;
    USHORT nNo;
    BOOL bEndNote;
public:
    SwUndoChgFtn( const SwPaM& rRange, const String& rTxt,
                    USHORT nNum, BOOL bIsEndNote );
    virtual ~SwUndoChgFtn();


    SwHistory* GetHistory() { return pHistory; }
};




//--------------------------------------------------------------------


//--------------------------------------------------------------------






//--------------------------------------------------------------------



//--------------------------------------------------------------------

// Object der als Iterator durch die Undo-Liste laeuft, bis die
// letze oder die angegebene Klammerung/Id erreicht ist.





}
#endif
