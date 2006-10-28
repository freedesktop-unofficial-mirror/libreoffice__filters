/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: swcrsr.hxx,v $
 *
 *  $Revision: 1.5 $
 *
 *  last change: $Author: rt $ $Date: 2006-10-28 04:54:11 $
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
#ifndef _SWCRSR_HXX
#define _SWCRSR_HXX

#ifndef _PAM_HXX //autogen
#include <pam.hxx>
#endif
#ifndef _TBLSEL_HXX //autogen
#include <tblsel.hxx>
#endif
#ifndef _CSHTYP_HXX //autogen
#include <cshtyp.hxx>
#endif
namespace com { namespace sun { namespace star { namespace util {
    struct SearchOptions;
} } } }

namespace binfilter {


class SwShellCrsr;
class SwShellTableCrsr;
class SwTableCursor;
class SwUnoCrsr;
class SwUnoTableCrsr;
struct _SwCursor_SavePos;

//STRIP008 namespace com { namespace sun { namespace star { namespace util {
//STRIP008 	struct SearchOptions;
//STRIP008 } } } }


// ein Basis-Struktur fuer die Parameter der Find-Methoden
// return - Werte vom Found-Aufruf.
const int FIND_NOT_FOUND	= 0;
const int FIND_FOUND		= 1;
const int FIND_NO_RING		= 2;

struct SwFindParas
{
    virtual int Find( SwPaM*, SwMoveFn, const SwPaM*, FASTBOOL ) = 0;
    virtual int IsReplaceMode() const = 0;
};

enum SwCursorSelOverFlags
{
    SELOVER_NONE				= 0x00,
    SELOVER_CHECKNODESSECTION 	= 0x01,
    SELOVER_TOGGLE				= 0x02,
    SELOVER_ENABLEREVDIREKTION	= 0x04,
    SELOVER_CHANGEPOS			= 0x08
};

class SwCursor : public SwPaM
{
    friend class SwCrsrSaveState;

    _SwCursor_SavePos* pSavePos;
    BYTE nCursorBidiLevel;              // bidi level of the cursor

    ULONG FindAll( SwFindParas& , SwDocPositions, SwDocPositions, FindRanges, BOOL& bCancel );

protected:
    virtual _SwCursor_SavePos* CreateNewSavePos() const;
    void SaveState();
    void RestoreState();

    const _SwCursor_SavePos* GetSavePos() const { return pSavePos; }

public:
    SwCursor( const SwPosition &rPos, SwPaM* pRing = 0 );
    virtual ~SwCursor();


    virtual operator SwShellCrsr* ();
    virtual operator SwShellTableCrsr* ();
    virtual operator SwTableCursor* ();
    virtual operator SwUnoCrsr* ();
    virtual operator SwUnoTableCrsr* ();

    inline operator const SwShellCrsr* () const;
    inline operator const SwShellTableCrsr* () const;
    inline operator const SwTableCursor* () const;
    inline operator const SwUnoCrsr* () const;
    inline operator const SwUnoTableCrsr* () const;

    virtual void SaveTblBoxCntnt( const SwPosition* pPos = 0 );


    ULONG Find( const ::com::sun::star::util::SearchOptions& rSearchOpt,
                SwDocPositions nStart, SwDocPositions nEnde,
                BOOL& bCancel,
                FindRanges = FND_IN_BODY,
                int bReplace = FALSE );

    ULONG Find( const SwTxtFmtColl& rFmtColl,
                SwDocPositions nStart, SwDocPositions nEnde,
                BOOL& bCancel,
                FindRanges = FND_IN_BODY,
                const SwTxtFmtColl* pReplFmt = 0 );

    ULONG Find( const SfxItemSet& rSet, FASTBOOL bNoCollections,
                SwDocPositions nStart, SwDocPositions nEnde,
                BOOL& bCancel,
                FindRanges = FND_IN_BODY,
                const ::com::sun::star::util::SearchOptions* pSearchOpt = 0,
                const SfxItemSet* rReplSet = 0 );

    FASTBOOL IsStartWord()const;
    FASTBOOL IsEndWord() const;
    FASTBOOL GoStartWord();
    FASTBOOL GoEndWord();
    FASTBOOL GoNextWord();
    FASTBOOL GoPrevWord();

    enum SentenceMoveType
    {
        NEXT_SENT,
        PREV_SENT,
        START_SENT,
        END_SENT
    };
     FASTBOOL GoSentence(SentenceMoveType eMoveType);
    FASTBOOL GoNextSentence(){DBG_BF_ASSERT(0, "STRIP"); return FALSE;}//STRIP001 return GoSentence(NEXT_SENT);}
    FASTBOOL GoPrevSentence(){DBG_BF_ASSERT(0, "STRIP"); return FALSE;}//STRIP001 return GoSentence(PREV_SENT);}

    FASTBOOL LeftRight( BOOL bLeft, USHORT nCnt, USHORT nMode, BOOL bAllowVisual,
                        BOOL bInsertCrsr );
    FASTBOOL UpDown( BOOL bUp, USHORT nCnt = 1,
                    Point* pPt = 0, long nUpDownX = 0 );
    FASTBOOL IsAtLeftRightMargin( BOOL bLeftMargin, BOOL bAPI = FALSE ) const;

    FASTBOOL Left( USHORT nCnt, USHORT nMode, BOOL bAllowVisual = FALSE )
                                    { return LeftRight( TRUE, nCnt, nMode, bAllowVisual, FALSE ); }
    FASTBOOL Right( USHORT nCnt, USHORT nMode, BOOL bAllowVisual = FALSE )
                                    { return LeftRight( FALSE, nCnt, nMode, bAllowVisual, FALSE ); }
    FASTBOOL Up( USHORT nCnt = 1 )		{ return UpDown( TRUE, nCnt ); }
    FASTBOOL Down( USHORT nCnt = 1 )	{ return UpDown( FALSE, nCnt ); }
    FASTBOOL LeftMargin()				{ DBG_BF_ASSERT(0, "STRIP"); return FALSE;} //STRIP001 { return LeftRightMargin( TRUE ); }
    FASTBOOL RightMargin()				{ DBG_BF_ASSERT(0, "STRIP"); return FALSE;} //STRIP001 { return LeftRightMargin( FALSE ); }
    FASTBOOL SttDoc()					{ DBG_BF_ASSERT(0, "STRIP"); return FALSE;} //STRIP001 { return SttEndDoc( TRUE ); }
    FASTBOOL EndDoc()					{ DBG_BF_ASSERT(0, "STRIP"); return FALSE;} //STRIP001 { return SttEndDoc( FALSE ); }
    FASTBOOL GoNextCell( USHORT nCnt = 1 )	{ DBG_BF_ASSERT(0, "STRIP"); return FALSE;} //STRIP001 { return GoPrevNextCell( TRUE, nCnt ); }
    FASTBOOL GoPrevCell( USHORT nCnt = 1 )	{ DBG_BF_ASSERT(0, "STRIP"); return FALSE;} //STRIP001 { return GoPrevNextCell( FALSE, nCnt ); }
    FASTBOOL GotoTblBox( const String& rName );

    FASTBOOL MovePara( SwWhichPara, SwPosPara );
    FASTBOOL MoveSection( SwWhichSection, SwPosSection );
    FASTBOOL MoveTable( SwWhichTable, SwPosTable );
    FASTBOOL MoveRegion( SwWhichRegion, SwPosRegion );


    // gibt es eine Selection vom Content in die Tabelle
    // Return Wert gibt an, ob der Crsr auf der alten Position verbleibt
    virtual FASTBOOL IsSelOvr( int eFlags =
                                ( SELOVER_CHECKNODESSECTION |
                                  SELOVER_TOGGLE | SELOVER_CHANGEPOS ));
    virtual FASTBOOL IsInProtectTable( FASTBOOL bMove = FALSE,
                                        FASTBOOL bChgCrsr = TRUE );


    // TRUE: an die Position kann der Cursor gesetzt werden
    virtual FASTBOOL IsAtValidPos( BOOL bPoint = TRUE ) const;

    // darf der Cursor in ReadOnlyBereiche?
    FASTBOOL IsReadOnlyAvailable() const;

    BYTE GetCrsrBidiLevel() const { return nCursorBidiLevel; }
    void SetCrsrBidiLevel( BYTE nNewLevel ) { nCursorBidiLevel = nNewLevel; }

    DECL_FIXEDMEMPOOL_NEWDEL( SwCursor )
};


class SwCrsrSaveState
{
    SwCursor& rCrsr;
public:
    SwCrsrSaveState( SwCursor& rC ) : rCrsr( rC ) { rC.SaveState(); }
    ~SwCrsrSaveState() { rCrsr.RestoreState(); }
};

struct _SwCursor_SavePos
{
    ULONG nNode;
    xub_StrLen nCntnt;
    _SwCursor_SavePos* pNext;

    _SwCursor_SavePos( const SwCursor& rCrsr )
        : nNode( rCrsr.GetPoint()->nNode.GetIndex() ),
        nCntnt( rCrsr.GetPoint()->nContent.GetIndex() ),
        pNext( 0 )
    {}
    virtual ~_SwCursor_SavePos() {}

    DECL_FIXEDMEMPOOL_NEWDEL( _SwCursor_SavePos )
};



class SwTableCursor : public virtual SwCursor
{

protected:
    ULONG nTblPtNd, nTblMkNd;
    xub_StrLen nTblPtCnt, nTblMkCnt;
    SwSelBoxes aSelBoxes;
    BOOL bChg : 1;
    BOOL bParked : 1;		// Tabellen-Cursor wurde geparkt

public:
    SwTableCursor( const SwPosition &rPos, SwPaM* pRing = 0 );
    SwTableCursor( SwTableCursor& );
    virtual ~SwTableCursor();

    virtual operator SwTableCursor* ();

     void InsertBox( const SwTableBox& rTblBox );
    void DeleteBox( USHORT nPos ) { aSelBoxes.Remove( nPos ); bChg = TRUE; }
     USHORT GetBoxesCount() const { return aSelBoxes.Count(); }
     const SwSelBoxes& GetBoxes() const { return aSelBoxes; }

        // Baut fuer alle Boxen die Cursor auf
    SwCursor* MakeBoxSels( SwCursor* pAktCrsr );
        // sind irgendwelche Boxen mit einem Schutz versehen?

        // wurde der TabelleCursor veraendert ? Wenn ja speicher gleich
        // die neuen Werte.
        // wurde der TabelleCursor veraendert ?


    // Parke den Tabellen-Cursor auf dem StartNode der Boxen.

};


// --------------------------- inline Methoden ----------------------

inline SwCursor::operator const SwShellCrsr* () const
{
    return (SwShellCrsr*)*((SwCursor*)this);
}

inline SwCursor::operator const SwShellTableCrsr* () const
{
    return (SwShellTableCrsr*)*((SwCursor*)this);
}

inline SwCursor::operator const SwTableCursor* () const
{
    return (SwTableCursor*)*((SwCursor*)this);
}

inline SwCursor::operator const SwUnoCrsr* () const
{
    return (SwUnoCrsr*)*((SwCursor*)this);
}

inline SwCursor::operator const SwUnoTableCrsr* () const
{
    return (SwUnoTableCrsr*)*((SwCursor*)this);
}


} //namespace binfilter
#endif

