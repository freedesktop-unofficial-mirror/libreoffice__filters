/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: fesh.hxx,v $
 *
 *  $Revision: 1.3 $
 *
 *  last change: $Author: rt $ $Date: 2005-09-09 15:58:58 $
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
#ifndef _FESH_HXX
#define _FESH_HXX

#ifndef _EDITSH_HXX
#include <editsh.hxx>
#endif
#ifndef _ORNTENUM_HXX
#include <orntenum.hxx>
#endif
#ifndef _FLYENUM_HXX
#include <flyenum.hxx>
#endif

// OD 25.06.2003 #108784#
#ifndef _SVDTYPES_HXX
#include <bf_svx/svdtypes.hxx>
#endif

#include <vector>
class SvEmbeddedObject; 
class SvEmbeddedObjectRef; 
class SvInPlaceObject; 
class Color; 
namespace binfilter {

class SwFlyFrm;

class SwTabCols;
class SvxBrushItem;
class SwTableAutoFmt;
class SwFrm;
class SwTabFrm;
class SwFmtFrmSize;
class SvxBorderLine;
class SvStorageStream;
class SdrObject;

class Outliner;
class SotDataObject;
class SdrViewUserMarker;
class SwFrmFmt;
struct SwSortOptions;
class SdrMarkList;

enum FrmType
{
    //Fuer GetFrmType() und GetSelFrmType(). Der Return-Wert ist eine
    //Veroderung.
    FRMTYPE_NONE	= 0,
    FRMTYPE_PAGE	= 1,
    FRMTYPE_HEADER	= 2,
    FRMTYPE_FOOTER	= 4,
    FRMTYPE_BODY	= 8,
    FRMTYPE_COLUMN	= 16,
    FRMTYPE_TABLE	= 32,
    FRMTYPE_FLY_FREE	= 64,
    FRMTYPE_FLY_ATCNT	= 128,
    FRMTYPE_FLY_INCNT	= 256,
    FRMTYPE_FOOTNOTE	= 512,
    FRMTYPE_FTNPAGE		= 1024,
    FRMTYPE_FLY_ANY		= 2048,
    FRMTYPE_DRAWOBJ		= 4096,
    FRMTYPE_COLSECT		= 8192,
    FRMTYPE_COLSECTOUTTAB = 16384
};

#define FRMTYPE_ANYCOLSECT ( FRMTYPE_COLSECT | FRMTYPE_COLSECTOUTTAB )

enum GotoObjType
{
    DRAW_CONTROL = 1,
    DRAW_SIMPLE = 2,
    DRAW_ANY = 3,
    FLY_FRM = 4,
    FLY_GRF = 8,
    FLY_OLE = 16,
    FLY_ANY = 28,
    GOTO_ANY = 31
};

enum FlyProtectType
{
     FLYPROTECT_CONTENT		= 1,		// kann verodert werden!
     FLYPROTECT_SIZE		= 2,
     FLYPROTECT_POS			= 4,
     FLYPROTECT_PARENT 		= 8,		// nur Parents untersuchen
     FLYPROTECT_FIXED		= 16		// nur nicht aufhebbarer Schutz
                                        // z.B. durch OLE-Server, gilt auch
                                        // fuer Dialog
};

enum ObjCntType		//Fuer das Ermitteln des Cntnts per Positon (D&D)
{
    OBJCNT_NONE,
    OBJCNT_FLY,
    OBJCNT_GRF,
    OBJCNT_OLE,
    OBJCNT_SIMPLE,
    OBJCNT_CONTROL,
    OBJCNT_URLBUTTON,

    OBJCNT_GROUPOBJ,
    OBJCNT_DONTCARE		// nicht bestimmbar - unterschiedliche Objecte selektiert
};

//fuer GetAnyCurRect
enum CurRectType
{
    RECT_PAGE,					//Rect der aktuellen Seite.
    RECT_PAGE_CALC,				//... Seite wird ggf. Formatiert
    RECT_PAGE_PRT,              //Rect der aktuellen PrtArea der Seite
    RECT_FRM,                   //Rect des aktuellen Rahmen
    RECT_FLY_EMBEDDED,          //Rect des aktuellen FlyFrm
    RECT_FLY_PRT_EMBEDDED,      //Rect der PrtArea des FlyFrm
    RECT_SECTION,				//Rect des aktuellen Bereichs
    RECT_OUTTABSECTION,			//Rect des aktuellen Bereichs,
                                // aber ausserhalb der Tabelle
    RECT_SECTION_PRT,  			//Rect der aktuellen PrtArea des Bereichs
    RECT_OUTTABSECTION_PRT, 	//Rect der aktuellen PrtArea des Bereichs,
                                // aber ausserhalb der Tabelle
    RECT_HEADERFOOTER,     		//Rect des aktuellen Headers/Footer
    RECT_HEADERFOOTER_PRT 		//Rect der PrtArea des aktuellen Headers/Footers
};

struct SwGetCurColNumPara
{
    const SwFrmFmt* pFrmFmt;
    const SwRect* pPrtRect, *pFrmRect;
    SwGetCurColNumPara() : pFrmFmt( 0 ), pPrtRect( 0 ), pFrmRect( 0 ) {}
};

#define SW_PASTESDR_INSERT		1
#define SW_PASTESDR_REPLACE		2
#define SW_PASTESDR_SETATTR		3

#define SW_ADD_SELECT   1
#define SW_ENTER_GROUP  2
#define SW_LEAVE_FRAME  4

#define SW_MOVE_UP      0
#define SW_MOVE_DOWN    1
#define SW_MOVE_LEFT    2
#define SW_MOVE_RIGHT   3

#define SW_TABCOL_NONE  0
#define SW_TABCOL_HORI  1
#define SW_TABCOL_VERT  2

class SwFEShell : public SwEditShell
{
    SdrViewUserMarker *pChainFrom,
                      *pChainTo;
    BOOL bCheckForOLEInCaption;

    SwFlyFrm *FindFlyFrm() const;
    SwFlyFrm *FindFlyFrm( const SvEmbeddedObject *pObj ) const;

    //Actions fuer alle Shells beenden und ChangeLink rufen.
//STRIP001 	void EndAllActionAndCall();

//STRIP001 	void Scroll( const Point &rPt );

//STRIP001     // OD 25.06.2003 #108784# - correct type of 1st parameter
//STRIP001     void ChangeOpaque( SdrLayerID nLayerId );

//STRIP001 	void GetStartEndCell( SwLayoutFrm *&prStart, SwLayoutFrm *&prEnd );

//STRIP001 	const SwFrm *GetBox( const Point &rPt ) const;

    //0 == in keiner Spalte
    USHORT _GetCurColNum( const SwFrm *pFrm,
                          SwGetCurColNumPara* pPara ) const;

//STRIP001 	void _GetTabCols( SwTabCols &rToFill, const SwFrm *pBox ) const;

//STRIP001 	BOOL ImpEndCreate();

//STRIP001 	ObjCntType GetObjCntType( const SdrObject& rObj ) const;

    // Methoden fuers kopieren von DrawObjecten
//STRIP001 	BOOL CopyDrawSel( SwFEShell* pDestShell, const Point& rSttPt,
//STRIP001 								const Point& rInsPt, BOOL bIsMove,
//STRIP001 								BOOL bSelectInsert );

        // get list of marked SdrObjects; 
    // helper method for GetSelFrmType, IsSelContainsControl
    const SdrMarkList* _GetMarkList() const;


public:
    TYPEINFO();
    SwFEShell( SwDoc& rDoc, Window *pWin,
               SwRootFrm *pMaster = 0, const SwViewOption *pOpt = 0 );
    SwFEShell( SwEditShell& rShell, Window *pWin );
    virtual ~SwFEShell();

    // Copy und Paste Methoden fuer das interne Clipboard
//STRIP001 	BOOL Copy( SwDoc* pClpDoc, const String* pNewClpTxt = 0 );
//STRIP001 	BOOL Paste( SwDoc* pClpDoc );
    // Copy-Methode fuer Drag&Drop
//STRIP001 	BOOL Copy( SwFEShell*, const Point& rSttPt, const Point& rInsPt,
//STRIP001 				BOOL bIsMove = FALSE, BOOL bSelectInsert = TRUE );

//STRIP001 	void SelectFlyFrm( SwFlyFrm& rFrm, BOOL bNew = FALSE );

    // befindet sich der selektierte Rahmen innerhalb eines anderen?
//STRIP001 	const SwFrmFmt* IsFlyInFly();
    // Innerhalb eines des sichtbaren Ankers?
//STRIP001 	Rectangle *IsAnchorAtPos( const Point &rPt ) const;

//SS fuer DrawObjekte und Rahmen-----------------------------

    //Wenn ein Objekt angegeben wurde, so wird genau diese Markiert (anstatt
    //ueber die Position zu suchen.
    BOOL SelectObj( const Point& rSelPt, BYTE nFlag = 0, SdrObject *pObj = 0 );
//STRIP001 	void DelSelectedObj();

    //Selektion nach oben unten bewegen (Z-Order).
    //TRUE	== ganz nach oben/unten
    //FALSE == einen ueberholen
//STRIP001 	void SelectionToTop   ( BOOL bTop = TRUE );
//STRIP001 	void SelectionToBottom( BOOL bBottom = TRUE );

//STRIP001 	short GetLayerId() const;	//1 Heaven, 0 Hell, -1 Uneindeutig
//STRIP001 	void  SelectionToHeaven();	//Ueber dem Dokument
//STRIP001 	void  SelectionToHell();	//Unter dem Dokument

    // folgende zwei Methoden returnen den enum SdrHdlKind, um sich ein
    // includen von SVDRAW.HXX zu ersparen als int deklariert.
//STRIP001 	int IsObjSelectable( const Point& rPt );
//STRIP001 	int IsInsideSelectedObj( const Point& rPt );

    // #107513#
    // Test if there is a draw object at that position and if it should be selected.
    // The 'should' is aimed at Writer text fly frames which may be in front of
    // the draw object.
    sal_Bool ShouldObjectBeSelected(const Point& rPt);

//STRIP001     sal_Bool MoveAnchor( USHORT nDir );
    // Returns if Upper of frame at current position is section frame
    // Currently only used by the rules. To be replaced by something more
    // sophisticated one day.
    bool IsDirectlyInSection() const;

    //Returnwerte siehe oben FrmType.
    //pPt: Crsr bzw. DocPos; bStopAtFly: Bei Flys anhalten oder ueber den Anchor weitergehen
    // Obgleich (0,TRUE) eine Art Standard ist, sind die Parameter nicht defaultet, damit
    // bei jeder Benutzung insbesondere das bStopAtFly bewusst genutzt wird.
    USHORT GetFrmType( const Point *pPt, BOOL bStopAtFly ) const;
    USHORT GetSelFrmType() const;				//Selektion (Drawing)
    
    /** #108784# check whether selected frame contains a control;
     * companion method to GetSelFrmType, used for preventing
     * drag&drop of controls into header */
    bool IsSelContainsControl() const;

//STRIP001 	ObjCntType GetObjCntType( const Point &rPt, SdrObject *&rpObj ) const;
    ObjCntType GetObjCntTypeOfSelection( SdrObject** ppObj = 0 ) const;

    //Zum Anpassen der PosAttr bei Ankerwechseln.
//STRIP001 	SwRect  GetObjRect() const;
    //Zum Verschieben von Flys mit der Tastatur
//STRIP001 	SwRect  GetFlyRect() const;
//STRIP001 	void CalcBoundRect( SwRect &rRect, RndStdIds nAnchorId,
//STRIP001 						SwRelationOrient eRelOrient = FRAME,
//STRIP001 						BOOL bMirror = FALSE,
//STRIP001 						Point* pRef = NULL,
//STRIP001 						Size* pPercent = NULL ) const;

    // Groesse von Drawobjekten setzen
//STRIP001 	void SetObjRect( const SwRect& rRect );

//STRIP001 	long BeginDrag( const Point *pPt, BOOL bProp );
//STRIP001 	long Drag	  ( const Point *pPt, BOOL bProp );
//STRIP001 	long EndDrag  ( const Point *pPt, BOOL bProp );
//STRIP001 	void BreakDrag();

    //Methoden fuer die Statuszeile.
//STRIP001 	Point GetAnchorObjDiff() const;	//Abstand zum Anker
//STRIP001 	Point GetObjAbsPos()	 const; //Absolute Position
//STRIP001 	Size  GetObjSize()	     const;	//Groesse, ggf. die umschliessende

    //SS fuer die BriefUmschlaege: hole alle Seitengebundenen Objekte
    //und setze diese auf eine neue Seite.
//STRIP001 	void GetPageObjs( SvPtrarr& rFillArr );
//STRIP001 	void SetPageObjsNewPage( SvPtrarr& rFillArr, int nOffset = 1 );

    // zeige die aktuelle Selektion an ( ggfs. den Rahmen/DrawObject)
    virtual void MakeSelVisible();

    // returne das FrmFmt von dem evt. unter dem Point stehenden Object.
    // Das Object wird nicht selektiert!
//STRIP001 	const SwFrmFmt* GetFmtFromObj( const Point& rPt, SwRect** pRectToFill = 0 ) const;
    // returns a format too, if the point is over the text of any fly
//STRIP001 	const SwFrmFmt* GetFmtFromAnyObj( const Point& rPt ) const;

    //Welcher Schutz ist am selektierten Objekt gesetzt?
    BYTE IsSelObjProtected( FlyProtectType eType ) const;

    //Liefert neben der Grafik in rName bei gelinkten Grafiken den Namen mit
    //Pfad und sonst den Grafiknamen. rbLink ist TRU bei gelinkten Grafiken.
//STRIP001 	const Graphic *GetGrfAtPos( const Point &rDocPos,
//STRIP001 								String &rName, BOOL &rbLink ) const;

//SS fuer Rahmen --------------------------------------------

    BOOL IsFrmSelected() const;
//STRIP001 	BOOL GetFlyFrmAttr( SfxItemSet &rSet ) const;
//STRIP001 	BOOL SetFlyFrmAttr( SfxItemSet &rSet );
//STRIP001 	BOOL ResetFlyFrmAttr( USHORT nWhich, const SfxItemSet* pSet = 0 );
//STRIP001 	const SwFrmFmt *NewFlyFrm( const SfxItemSet &rSet, BOOL bAnchValid = FALSE,
//STRIP001 						 SwFrmFmt *pParent = 0 );
//STRIP001 	void SetFlyPos( const Point &rAbsPos);
//STRIP001 	Point FindAnchorPos( const Point &rAbsPos, BOOL bMoveIt = FALSE );
    // determines whether a frame or its environment is vertically formatted and right-to-left
    BOOL IsFrmVertical(BOOL bEnvironment, BOOL& bRightToLeft) const;

    SwFrmFmt* GetCurFrmFmt() const;	//Wenn Rahmen, dann Rahmenvorlage, sonst 0
//STRIP001 	void SetFrmFmt( SwFrmFmt *pFmt, BOOL bKeepOrient = FALSE, Point* pDocPos = 0 );	//Wenn Rahmen, dann Rahmenvorlage setzen
#ifdef ACCESSIBLE_LAYOUT
    const SwFlyFrm *GetCurrFlyFrm() const { return FindFlyFrm(); }
#endif

    // finde/loeschen den Fly, in dem der Cursor steht
//STRIP001 	SwFrmFmt* WizzardGetFly();
//STRIP001 	BOOL WizzardDelFly();

    //Selebstaendiges selektieren von Flys
//STRIP001     BOOL GotoNextFly(GotoObjType eType = FLY_ANY)
//STRIP001                                 { return GotoObj( TRUE, eType ); }
//STRIP001     BOOL GotoPrevFly(GotoObjType eType = FLY_ANY)
//STRIP001                                 { return GotoObj( FALSE, eType); }

    //iterieren ueber Flys - fuer Basic-Collections
//STRIP001 	USHORT GetFlyCount(FlyCntType eType = FLYCNTTYPE_ALL) const;
//STRIP001 	const SwFrmFmt* GetFlyNum(USHORT nIdx, FlyCntType eType = FLYCNTTYPE_ALL) const;

    //Wenn ein fly selectiert ist, zieht er den Crsr in den ersten CntntFrm
//STRIP001 	const SwFrmFmt* SelFlyGrabCrsr();

    //Get FlyFrameFormat; fuer UI Macro Anbindung an Flys
    const SwFrmFmt* GetFlyFrmFmt() const;
          SwFrmFmt* GetFlyFrmFmt();

    //OLE, Server fordert neue Groesse an, die gewuenschten Werte werden
    //als Rahmenattribute eingestellt. Wenn die Werte nicht erlaubt sind,
    //so wird von der Formatierung geclippt und eine Scalierung eingestellt.
    //siehe CalcAndSetScale().
    void RequestObjectResize( const SwRect &rRect, SvEmbeddedObject *pIPObj );

    //Der Client fuer das OleObject muss bezueglich der Scalierung auf dem
    //neuesten Stand gehalten werden. Impl in der WrtShell.
    //Wird ein Pointer auf eine Size uebergeben, so ist diese die aktuelle
    //Core-Groesse des Objectes. Anderfalls wird die Groesse per GetCurFlyRect()
    //besorgt.
    virtual void CalcAndSetScale( SvEmbeddedObjectRef xIPObj,
                                  const SwRect *pFlyPrtRect = 0,
                                  const SwRect *pFlyFrmRect = 0 ) = 0;

    //Objekte mit ActivateWhenVisible werden beim Paint Connected.
    //gerufen von notxtfrm::Paint, impl in wrtsh
    virtual void ConnectObj( SvInPlaceObjectRef xIPObj, const SwRect &rPrt,
                             const SwRect &rFrm ) = 0;

    //Sichbaren Bereich auf das Object setzen, wenn es noch nicht sichtbar ist.
//STRIP001 	void MakeObjVisible( const SvEmbeddedObject *pIPObj ) const;

    // check resize of OLE-Object
    BOOL IsCheckForOLEInCaption() const 		{ return bCheckForOLEInCaption; }
    void SetCheckForOLEInCaption( BOOL bFlag )	{ bCheckForOLEInCaption = bFlag; }

    // setze am selektierten FlyFrame einen Namen
//STRIP001 	void SetFlyName( const String& rName );
//STRIP001 	const String& GetFlyName() const;

    // erezeuge eindeutige Namen fuer Rahmen
//STRIP001 	String GetUniqueGrfName() const;
//STRIP001 	String GetUniqueOLEName() const;
//STRIP001 	String GetUniqueFrameName() const;

    // springe zum benannten Rahmen (Grafik/OLE)
    BOOL GotoFly( const String& rName, FlyCntType eType = FLYCNTTYPE_ALL,
                    BOOL bSelFrame = TRUE );
    // steht an der Position eine Grafik mit einer URL ?
//STRIP001 	const SwFrmFmt* IsURLGrfAtPos( const Point& rPt, String* pURL = 0,
//STRIP001 									String *pTargetFrameName = 0,
//STRIP001 									String *pURLDescription = 0 ) const;

    //Fuer das Chain wird immer der durch das Format spezifizierte Fly
    //mit dem durch den Point getroffenen verbunden.
    //In rRect wird das Rect des Flys geliefert (fuer Highlight desselben)
//STRIP001 	int Chainable( SwRect &rRect, const SwFrmFmt &rSource, const Point &rPt ) const;
//STRIP001 	int Chain( SwFrmFmt &rSource, const Point &rPt );
        int Chain( SwFrmFmt &rSource, const SwFrmFmt &rDest );
//STRIP001 	void Unchain( SwFrmFmt &rFmt );
    void HideChainMarker();
    void SetChainMarker();

//STRIP001 	Size GetGraphicDefaultSize() const;

//SS fuer DrawObjekte ---------------------

    //Temporaer um Bug zu umgehen.
//STRIP001 	void CheckUnboundObjects();

    //Achtung: Uneindeutikeiten bei Mehrfachselektionen.
//STRIP001 	BOOL GetObjAttr( SfxItemSet &rSet ) const;
//STRIP001 	BOOL SetObjAttr( const SfxItemSet &rSet );

//STRIP001     BOOL GotoObj( BOOL bNext, GotoObjType eType = DRAW_ANY);

//STRIP001 	ULONG ControlCount() const;
//STRIP001 	BOOL  GotoControl( ULONG nIndex );

    //Setzen vom DragMode (z.B. Rotate), tut nix bei Rahmenselektion.
//STRIP001 	void SetDragMode( UINT16 eSdrDragMode );

    USHORT IsObjSelected() const;	//Liefert gleich die Anzahl der Objekte,
                                    //zaehlt aber nicht die Objekte in Gruppen.
#ifdef ACCESSIBLE_LAYOUT
//STRIP001 	sal_Bool IsObjSelected( const SdrObject& rObj ) const;
#endif

//STRIP001 	void EndTextEdit();				//Loescht ggf. das Objekt.

    //Ankertyp des selektierten Objektes, -1 bei Uneindeutigkeit oder
    //Rahmenselektion; FLY_PAGE bzw. FLY_AT_CNTNT aus frmatr.hxx sonst.
//STRIP001 	short GetAnchorId() const;

    //Erzeugen von DrawObjekten, beim Begin wird der Objekttyp mitgegeben.
    //Beim End kann ein Cmd mitgegeben werden, hier ist ggf.
    //SDRCREATE_RESTRAINTEND fuer Ende oder SDRCREATE_NEXTPOINT fuer ein
    //Polygon relevant. Nach dem RESTRAINTEND ist das Objekt erzeugt und
    //selektiert.
    //Mit BreakCreate wird der Vorgang abgebrochen, dann ist kein Objekt
    //mehr selektiert.
//STRIP001     BOOL BeginCreate( UINT16 eSdrObjectKind, const Point &rPos );
//STRIP001 	BOOL BeginCreate( UINT16 eSdrObjectKind, UINT32 eObjInventor, const Point &);
//STRIP001 	void MoveCreate ( const Point &rPos );
//STRIP001 	BOOL EndCreate	( UINT16 eSdrCreateCmd );
//STRIP001 	void BreakCreate();
//STRIP001 	BOOL IsDrawCreate() const;
//STRIP001     void CreateDefaultShape(UINT16 eSdrObjectKind, const Rectangle& rRect, USHORT nSlotId);

    // Funktionen f�r Rubberbox, um Draw-Objekte zu selektieren
//STRIP001 	BOOL BeginMark( const Point &rPos );
//STRIP001 	void MoveMark ( const Point &rPos );
//STRIP001 	BOOL EndMark  ();
//STRIP001 	void BreakMark();

    //Gruppe erzeugen, aufloesen, nix bei Rahmenselektion.
//STRIP001 	BOOL IsGroupSelected();		//Kann auch eine Mischselektion sein!
//STRIP001 	void GroupSelection();		//Hinterher ist die Gruppe selektiert.
//STRIP001 	void UnGroupSelection();	//Die Einzelobjekte sind Selektiert
                                //Es koennen noch immer Gruppen dabei sein.

// OD 27.06.2003 #108784# - change return type.
//STRIP001 	BOOL IsGroupAllowed() const;

//STRIP001 	void MirrorSelection( BOOL bHorizontal );	//Bei FALSE Vertikal

    //Umankern. erlaubt sind: FLY_PAGE und FLY_AT_CNTNT des enum RndStdIds aus
    //frmatr.hxx. Hier kein enum wg. Abhaengigkeiten
    //Der BOOL ist nur fuer internen Gebrauch! Anker wird nur - anhand der
    //aktuellen Dokumentposition - neu gesetzt aber nicht umgesetzt.
//STRIP001 	void ChgAnchor( int eAnchorId, BOOL bSameOnly = FALSE,
//STRIP001 								   BOOL bPosCorr = TRUE );

    // hole die selectierten DrawObj als Grafik (MetaFile/Bitmap)
    // Return-Wert besagt ob konvertiert wurde!!
//STRIP001 	BOOL GetDrawObjGraphic( ULONG nFmt, Graphic& rGrf ) const;

//STRIP001 	void Paste( SvStream& rStm, USHORT nAction, const Point* pPt = 0 );
//STRIP001 	BOOL Paste( const Graphic &rGrf );
//STRIP001 	BOOL Paste( SotDataObject& rObj, const Point& rPt );

//STRIP001 	BOOL IsAlignPossible() const;
//STRIP001 	void SetCalcFieldValueHdl(Outliner* pOutliner);

        //Einfuegen eines DrawObjectes. Das Object muss bereits im DrawModel
        // angemeldet sein.
//STRIP001 	void Insert( SdrObject& rDrawObj, const SfxItemSet* pFlyAttrSet = 0,
//STRIP001 				SwFrmFmt* = 0, const Point* = 0 );

//STRIP001 	BOOL ReplaceSdrObj( const String& rGrfName, const String& rFltName,
//STRIP001 						const Graphic* pGrf = 0 );

//------------------------------------------

    //Auskunft ueber naechstliegenden Inhalt zum uebergebenen Point
//STRIP001 	Point GetCntntPos( const Point& rPoint, BOOL bNext ) const;

    //convert document position into position relative to the current page
    Point GetRelativePagePosition(const Point& rDocPos);
    
    //Layout-Selektion Hiden/Zeigen und aufruf an die CrsrSh weiterreichen.
//STRIP001 	void ShLooseFcs();
    void ShGetFcs( BOOL bUpdate = TRUE );

    //PageDescriptor-Schnittstelle
//STRIP001 	void   ChgCurPageDesc( const SwPageDesc& );
    USHORT GetCurPageDesc( const BOOL bCalcFrm = TRUE ) const;
    USHORT GetMousePageDesc( const Point &rPt ) const;
    USHORT GetPageDescCnt() const;
//STRIP001 	SwPageDesc* FindPageDescByName( const String& rName,
//STRIP001 									BOOL bGetFromPool = FALSE,
//STRIP001 									USHORT* pPos = 0 );

    const SwPageDesc& GetPageDesc( USHORT i ) const;
//STRIP001 	void  ChgPageDesc( USHORT i, const SwPageDesc& );
    // if inside all selection only one PageDesc, return this.
    // Otherwise return 0 pointer
//STRIP001 	const SwPageDesc* GetSelectedPageDescs() const;

    const SwRect& GetAnyCurRect( CurRectType eType,
                                 const Point* pPt = 0,
                                 const SvEmbeddedObject *pObj = 0 ) const;

    //Seitennummer der Seite in der der Point liegt, 0 wenn keine
    //getroffen ist.
//STRIP001 	USHORT GetPageNumber( const Point &rPoint ) const;
    BOOL GetPageNumber( long nYPos, BOOL bAtCrsrPos, USHORT& rPhyNum, USHORT& rVirtNum, String &rDisplay ) const;


//STRIP001 	void Insert(const String& rGrfName,
//STRIP001 				const String& rFltName,
//STRIP001 				const Graphic* pGraphic = 0,
//STRIP001 				const SfxItemSet* pFlyAttrSet = 0,
//STRIP001 				const SfxItemSet* pGrfAttrSet = 0,
//STRIP001 				SwFrmFmt* = 0 );

//STRIP001 	void Insert(SvInPlaceObject *,
//STRIP001 				const SfxItemSet* pFlyAttrSet = 0,
//STRIP001 				const SfxItemSet* pGrfAttrSet = 0,
//STRIP001 				SwFrmFmt* = 0 );
    BOOL 	FinishOLEObj();								// Server wird beendet

    //Attribute der Tabelle besorgen/setzen.
//STRIP001 	void GetTblAttr( SfxItemSet & ) const;
//STRIP001 	void SetTblAttr( const SfxItemSet & );

    //Tabelle vollstaendig selektiert?
//STRIP001 	BOOL HasWholeTabSelection() const;
    //Ist der Inhalt einer Tabellenzelle oder mindestens eine Tabellenzelle
    //vollstaendig selektiert ist
//STRIP001 	BOOL HasBoxSelection() const;

//STRIP001 	BOOL InsertRow( USHORT nCnt, BOOL bBehind );
//STRIP001 	BOOL InsertCol( USHORT nCnt, BOOL bBehind );  // 0 == am Ende
//STRIP001 	BOOL DeleteCol();
//STRIP001 	BOOL DeleteRow();

//STRIP001 	BOOL DeleteTblSel();		//Aktuelle Selektion, ggf. die ganze Tabelle.

//STRIP001 	USHORT MergeTab();			//Merged selektierte Tabellenteile zusammen
                                //Fehler ueber enum zurueck
    // Zelle Vertikal oder Horizontal splitten.
//STRIP001     BOOL SplitTab( BOOL nVert = TRUE, USHORT nCnt = 1, BOOL bSameHeight = FALSE );
//STRIP001 	BOOL Sort(const SwSortOptions&);	//Sortieren.

//STRIP001 	void SetRowHeight( const SwFmtFrmSize &rSz );
    //Der Pointer muss vom Aufrufer zerstoert werden wenn != 0
//STRIP001 	void GetRowHeight( SwFmtFrmSize *&rpSz ) const;

//STRIP001 	void   SetBoxAlign( USHORT nOrient );
    USHORT GetBoxAlign() const;			//USHRT_MAX fuer uneindeutig!

    //Ausgleichen der Zeilenhoehen. Mit bTstOnly festellen ob mehr als eine
    //Zeile markiert ist.
    BOOL BalanceRowHeight( BOOL bTstOnly );

//STRIP001 	void SetTabBorders( const SfxItemSet& rSet );
    void GetTabBorders( 	  SfxItemSet& rSet) const;
//STRIP001 	void SetTabLineStyle(const Color* pColor, BOOL bSetLine = FALSE, const SvxBorderLine* pBorderLine = NULL);

//STRIP001 	void SetTabBackground( const SvxBrushItem &rNew );
//STRIP001 	void GetTabBackground( SvxBrushItem &rToFill ) const;

//STRIP001 	void SetBoxBackground( const SvxBrushItem &rNew );
//STRIP001 	BOOL GetBoxBackground( SvxBrushItem &rToFill ) const; //FALSE uneindeutig

//STRIP001 	void SetRowBackground( const SvxBrushItem &rNew );
//STRIP001 	BOOL GetRowBackground( SvxBrushItem &rToFill ) const; //FALSE uneindeutig

//STRIP001     BYTE WhichMouseTabCol( const Point &rPt ) const;
//STRIP001 	void GetMouseTabCols( SwTabCols &ToFill, const Point &rPt ) const;
//STRIP001 	void SetMouseTabCols( const SwTabCols &rNew, BOOL bCurRowOnly,
//STRIP001 						  const Point &rPt );
//STRIP001 	void GetTabCols( SwTabCols &rToFill ) const; //Spalten- und Randinfo.
//STRIP001 	void SetTabCols( const SwTabCols &rNew, BOOL bCurRowOnly = TRUE );

//STRIP001 	void ProtectCells();	//Falls eine Tabselektion besteht, wird sie ver-
                            // nichtet, wenn der Cursor nicht in Readonly darf
//STRIP001 	void UnProtectCells();	// auf die Tabellenselektin
//STRIP001 	void UnProtectCells( const String& rTblName ); 	// diese Tabelle
//STRIP001 	void UnProtectTbls();	//bei allen Tabellen in der Selektion den Schutz aufheben
//STRIP001 	BOOL HasTblAnyProtection( const String* pTblName = 0,
//STRIP001 								BOOL* pFullTblProtection = 0 );
//STRIP001 	BOOL CanUnProtectCells() const;

//STRIP001 	void SetHeadlineRepeat( BOOL bSet );//TRUE: Headline soll widerholt werden.
//STRIP001 	BOOL IsHeadlineRepeat() const;
    BOOL IsInRepeatedHeadline() const;
//STRIP001 	BOOL IsInHeadline() const;

    //Stellt die Breiten der Zellen so ein, dass der Inhalt moeglichst
    //nicht umgebrochen werden muss.
    //bBalance sorgt fuer einen Ausgleich der markierten Spalten.
//STRIP001 	void AdjustCellWidth( BOOL bBalance = FALSE );
    //Nicht erlaubt, wenn nur  leere Zellen selektiert sind.
    BOOL IsAdjustCellWidthAllowed( BOOL bBalance = FALSE ) const;

    //Ausgleich der Zellenbreiten, mit bTstOnly feststellen, ob mehr als
    //eine Zelle markiert ist.
    BOOL BalanceCellWidth( BOOL bTstOnly );

        // AutoFormat fuer die Tabelle/TabellenSelection
//STRIP001 	BOOL SetTableAutoFmt( const SwTableAutoFmt& rNew );
        // Erfrage wie attributiert ist
//STRIP001 	BOOL GetTableAutoFmt( SwTableAutoFmt& rGet );
        // aender eine  Zellenbreite/-Hoehe/Spaltenbreite/Zeilenhoehe
//STRIP001 	BOOL SetColRowWidthHeight( USHORT eType, USHORT nDiff = 283 );
        // Autosumme
//STRIP001 	BOOL GetAutoSum( String& rFml ) const;

    //Phy:	Tatsaechliche Seitenanzahl.
    //Virt: Vom User evtl. gesetzten Offset mit einbeziehen.
//STRIP001 	USHORT	GetPhyPageNum();
//STRIP001 	USHORT	GetVirtPageNum( const BOOL bCalcFrm = TRUE );

    // Setzt an der aktuellen Postion einen neuen Page Offset
//STRIP001 	void SetNewPageOffset( USHORT nOffset );
//STRIP001 	void SetPageOffset( USHORT nOffset );	//Aendert den letzten Page Offset
//STRIP001 	USHORT GetPageOffset() const;			//Liefert den letzten Page Offset

    //SS fuer Beschriftungen
//STRIP001 	void InsertLabel( const SwLabelType eType, const String &rTxt,
//STRIP001 					  const BOOL bBefore, const USHORT nId,
//STRIP001 					  const BOOL bCpyBrd = TRUE );

    //Das Lineal will auch noch etwas von uns wissen.
    USHORT GetCurColNum( SwGetCurColNumPara* pPara = 0 ) const;	//0 == in keiner Spalte
//STRIP001 	USHORT GetCurMouseColNum( const Point &rPt,
//STRIP001 							SwGetCurColNumPara* pPara = 0 ) const;
//STRIP001 	USHORT GetCurTabColNum() const;		//0 == in keiner Tabelle
//STRIP001 	USHORT GetCurMouseTabColNum( const Point &rPt ) const;
//STRIP001 	USHORT GetCurOutColNum( SwGetCurColNumPara* pPara = 0 ) const;	// aktuelle aeussere Spalte
    BOOL IsTableRightToLeft()const;
    BOOL IsLastCellInRow() const;
    BOOL IsMouseTableRightToLeft(const Point &rPt) const;
    // Die Breite des aktuellen Bereichs fuer Spaltendialog
//STRIP001 	long GetSectionWidth( SwFmt& rFmt ) const;
    
    void GetConnectableFrmFmts
    (SwFrmFmt & rFmt, const String & rReference, BOOL bSuccessors,
     ::std::vector< String > & aPrevPageVec,
     ::std::vector< String > & aThisPageVec,
     ::std::vector< String > & aNextPageVec,
     ::std::vector< String > & aRestVec);

    /** SwFEShell::GetShapeBackgrd

        OD 02.09.2002 for #102450#:
        method determines background color of the page the selected drawing
        object is on and returns this color.
        If no color is found, because no drawing object is selected or ...,
        color COL_BLACK (default color on constructing object of class Color)
        is returned.

        @author OD

        @returns an object of class Color
    */
    const Color GetShapeBackgrd() const;

    /** Is default horizontal text direction for selected drawing object right-to-left

        OD 09.12.2002 #103045#
        Because drawing objects only painted for each page only, the default
        horizontal text direction of a drawing object is given by the corresponding
        page property.

        @author OD

        @returns boolean, indicating, if the horizontal text direction of the
        page, the selected drawing object is on, is right-to-left.
    */
    const bool IsShapeDefaultHoriTextDirR2L() const;

    void ParkCursorInTab();
};

} //namespace binfilter
#endif
