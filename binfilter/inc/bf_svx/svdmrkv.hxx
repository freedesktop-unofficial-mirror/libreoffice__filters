/*************************************************************************
 *
 *  $RCSfile: svdmrkv.hxx,v $
 *
 *  $Revision: 1.1.1.1 $
 *
 *  last change: $Author: hjs $ $Date: 2003-10-01 12:23:48 $
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

#ifndef _SVDMRKV_HXX
#define _SVDMRKV_HXX

#ifndef _SVDMARK_HXX
#include <bf_svx/svdmark.hxx>
#endif

#ifndef _SVDHDL_HXX
#include <bf_svx/svdhdl.hxx>
#endif

#include <bf_svx/svdsnpv.hxx>

#ifndef _SVDTYPES_HXX
#include <bf_svx/svdtypes.hxx>
#endif

//************************************************************
//   Defines 
//************************************************************

// folgendes ist noch nicht bzw. erst zum Teil implementiert:
#define SDRSEARCH_DEEP         0x0001 /* rekursiv in Gruppenobjekte hinein */
#define SDRSEARCH_ALSOONMASTER 0x0002 /* MasterPages werden auch durchsucht */
#define SDRSEARCH_WHOLEPAGE    0x0004 /* Nicht nur die ObjList der PageView */
#define SDRSEARCH_TESTMARKABLE 0x0008 /* nur markierbare Objekte/Punkte/Handles/... */
#define SDRSEARCH_TESTMACRO    0x0010 /* Nur Objekte mit Macro */
#define SDRSEARCH_TESTTEXTEDIT 0x0020 /* Nur TextEdit-faehige Objekte */
#define SDRSEARCH_WITHTEXT     0x0040 /* Nur Objekte mit Text */
#define SDRSEARCH_TESTTEXTAREA 0x0080 /* Den Textbereich von Objekten mit Text (TextEditHit) */
#define SDRSEARCH_BACKWARD     0x0100 /* Rueckwaertssuche */
#define SDRSEARCH_NEXT         0x0200 /* Suche startet hinter dem uebergebenen Objekt/Punkt/... */
#define SDRSEARCH_MARKED       0x0400 /* Nur markierte Objekte/Punkte/... */
#define SDRSEARCH_PASS2BOUND   0x0800 /* Wenn nix gefunden, dann neuer 2. Versuch mit BoundRectHit */
#define SDRSEARCH_PASS3NEAREST 0x1000 /* Wenn nix gefunden, dann neuer 3. Versuch mit NearestBoundRectHit */

#define SDRSEARCH_PICKMARKABLE (SDRSEARCH_TESTMARKABLE)
#define SDRSEARCH_PICKTEXTEDIT (SDRSEARCH_DEEP|SDRSEARCH_TESTMARKABLE|SDRSEARCH_TESTTEXTEDIT)
#define SDRSEARCH_PICKMACRO    (SDRSEARCH_DEEP|SDRSEARCH_ALSOONMASTER|SDRSEARCH_WHOLEPAGE|SDRSEARCH_TESTMACRO)

// SDRSEARCHPASS_... ist Rueckgabeparameterwert bei PickObj().
#define SDRSEARCHPASS_DIRECT       0x0000 /* Objekt durch direkten Hit getroffen     */
#define SDRSEARCHPASS_INACTIVELIST 0x0001 /* Obj auf der Page, nicht jedoch in der AktGroup (bei WHOLEPAGE) */
#define SDRSEARCHPASS_MASTERPAGE   0x0002 /* Objekt auf der MasterPage gefunden      */
#define SDRSEARCHPASS_BOUND        0x0010 /* Objekt erst beim Bound-Check gefunden   */
#define SDRSEARCHPASS_NEAREST      0x0020 /* Objekt erst beim Nearest-Check gefunden */

enum SdrHitKind {SDRHIT_NONE,      // Nicht getroffen, Schnaps gesoffen
                 SDRHIT_OBJECT,    // Treffer versenkt
                 SDRHIT_BOUNDRECT, // Treffer am BoundRect
                 SDRHIT_BOUNDTL,   // Treffer am BoundRect TopLeft
                 SDRHIT_BOUNDTC,   // Treffer am BoundRect TopCenter
                 SDRHIT_BOUNDTR,   // Treffer am BoundRect TopRight
                 SDRHIT_BOUNDCL,   // Treffer am BoundRect CenterLeft
                 SDRHIT_BOUNDCR,   // Treffer am BoundRect CenterRight
                 SDRHIT_BOUNDBL,   // Treffer am BoundRect BottomLeft
                 SDRHIT_BOUNDBC,   // Treffer am BoundRect BottomCenter
                 SDRHIT_BOUNDBR,/*,*/ // Treffer am BoundRect BottomRight
                 /*SDRHIT_REFPOINT*/ // Referenzpunkt (Rotationsachse,Spiegelachse) getroffen
                 // ab hier neu am 01-07-1996:
                 SDRHIT_HANDLE,          // Markierungshandle
                 SDRHIT_HELPLINE,        // Hilfslinie
                 SDRHIT_GLUEPOINT,       // Klebepunkt
                 SDRHIT_TEXTEDIT,        // Offene OutlinerView getroffen
                 SDRHIT_TEXTEDITOBJ,     // Objekt fuer BegTextEdit (Textbereich)
                 SDRHIT_URLFIELD,        // Feld im TextObj getroffen (wird gerade nicht editiert)
                 SDRHIT_MACRO,           // Objekt fuer BegMacroObj
                 SDRHIT_MARKEDOBJECT,    // Markiertes Objekt (z.B. zum Draggen)
                 SDRHIT_UNMARKEDOBJECT}; // nichtmarkiertes Objekt (z.B. zum markieren)

enum SdrViewEditMode {SDREDITMODE_EDIT,           // Auch bekannt aus Pfeil- oder Zeigermodus
                      SDREDITMODE_CREATE,         // Objekterzeugungswerkzeug
                      SDREDITMODE_GLUEPOINTEDIT}; // Klebepunkteditiermodus

#define IMPSDR_MARKOBJDESCRIPTION    0x0000
#define IMPSDR_POINTSDESCRIPTION     0x0001
#define IMPSDR_GLUEPOINTSDESCRIPTION 0x0002

////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  @@   @@  @@@@  @@@@@  @@  @@  @@ @@ @@ @@@@@ @@   @@
//  @@@ @@@ @@  @@ @@  @@ @@  @@  @@ @@ @@ @@    @@   @@
//  @@@@@@@ @@  @@ @@  @@ @@ @@   @@ @@ @@ @@    @@ @ @@
//  @@@@@@@ @@@@@@ @@@@@  @@@@    @@@@@ @@ @@@@  @@@@@@@
//  @@ @ @@ @@  @@ @@  @@ @@ @@    @@@  @@ @@    @@@@@@@
//  @@   @@ @@  @@ @@  @@ @@  @@   @@@  @@ @@    @@@ @@@
//  @@   @@ @@  @@ @@  @@ @@  @@    @   @@ @@@@@ @@   @@
//
////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////

class SdrMarkView: public SdrSnapView 
{
    friend class				SdrPageView;

protected:
    SdrObject*					pMarkedObj;       // Wenn nur ein Objekt markiert ist.
    SdrPageView*				pMarkedPV;        // Wenn alle markierten Objekt auf derselben PageView liegen.

    Point						aRef1;            // Persistent - Drehmittelpunkt/Spiegelachse
    Point						aRef2;            // Persistent
    Point						aLastCrookCenter; // Persistent
    SdrHdlList					aHdl;
    SdrMarkList					aMark;            // Persistent (ni)
    SdrMarkList					aEdgesOfMarkedNodes;        // EdgeObjekte der markierten Objekte
    SdrMarkList					aMarkedEdgesOfMarkedNodes;  // Markierte EdgeObjekte der markierten Objekte

    // #i13033#
    // New mechanism to hold the transitive hull of all selected objects
    List						maAllMarkedObjects;

    Rectangle					aMarkedObjRect;
    Rectangle					aMarkedPointsRect;
    Rectangle					aMarkedGluePointsRect;

    USHORT						nFrameHandlesLimit;
    USHORT						nSpecialCnt;
    USHORT						nInsPointNum;      // Nummer des InsPoint
    ULONG						nMarkableObjCount;

    SdrDragMode					eDragMode;        // Persistent
    SdrViewEditMode				eEditMode;      // Persistent
    SdrViewEditMode				eEditMode0;     // Persistent

    unsigned					bHdlShown : 1;
    unsigned					bRefHdlShownOnly : 1; // Spiegelachse waerend Dragging (ni)
    unsigned					bDesignMode : 1;      // DesignMode fuer SdrUnoObj
    unsigned					bMarking : 1;         // Selektionsrahmen fuer Objekte
    unsigned					bMarkingPoints : 1;   // Selektionsrahmen fuer Punkte
    unsigned					bMarkingGluePoints : 1;// Selektionsrahmen fuer Klebepunkte
    unsigned					bUnmarking : 1;
    unsigned					bForceFrameHandles : 1; // Persistent - FrameDrag auch bei Einzelobjekten
    unsigned					bPlusHdlAlways : 1;   // Persistent
    unsigned					bMarkHdlWhenTextEdit : 1; // Persistent, default=FALSE
//    unsigned					bSolidHdlBackgroundInvalid : 1; // Hintergrund der Handles ungueltig?
    unsigned					bInsPolyPoint : 1;     // z.Zt InsPolyPointDragging
    unsigned					bEdgesOfMarkedNodesDirty : 1;
    unsigned					bMarkedObjRectDirty : 1;
    unsigned					bMrkPntDirty : 1;
    unsigned					bMarkedPointsRectsDirty : 1;
    unsigned					bMarkableObjCountDirty : 1;
    unsigned					bHdlHidden : 1;

private:
    void ImpClearVars();
//STRIP001     void ImpSetPointsRects() const;
    void UndirtyMrkPnt() const;

protected:
    virtual void SFX_NOTIFY(SfxBroadcaster& rBC, const TypeId& rBCType, const SfxHint& rHint, const TypeId& rHintType);
    virtual void ModelHasChanged(); // Wird von der PaintView gerufen

//STRIP001     void ShowMarkObjOrPoints(OutputDevice* pOut);
//STRIP001     void HideMarkObjOrPoints(OutputDevice* pOut);
//STRIP001     void DrawMarkObjOrPoints(OutputDevice* pOut) const;

    virtual void SetMarkHandles();                                           // aHdl (Liste der Handles) fuellen
//    virtual void DrawMarkHdl(OutputDevice* pOut, BOOL bNoRefHdl) const;  // Togglen der Handles
    virtual void SetMarkRects();                                             // Rects an den PageViews
    virtual void CheckMarked();                                              // MarkList nach Del und Lock Layer durchsuchen...

    virtual void AddDragModeHdl(SdrDragMode eMode);

    // add custom handles (used by other apps, e.g. AnchorPos)
    virtual void AddCustomHdl();

//STRIP001     void ForceRefToMarked();
//STRIP001     void ForceEdgesOfMarkedNodes();
    void ForceUndirtyMrkPnt() const                                       { if (bMrkPntDirty) UndirtyMrkPnt(); }

    void ImpShowMarkHdl(OutputDevice* pOut, const Region* pRegion, BOOL bNoRefHdl);
    SdrObject* ImpCheckObjHit(const Point& rPnt, USHORT nTol, SdrObject* pObj, SdrPageView* pPV, ULONG nOptions, const SetOfByte* pMVisLay) const;
    SdrObject* ImpCheckObjHit(const Point& rPnt, USHORT nTol, SdrObjList* pOL, SdrPageView* pPV, ULONG nOptions, const SetOfByte* pMVisLay, SdrObject*& rpRootObj) const;
    BOOL ImpIsObjHit(const Point& rPnt, USHORT nTol, SdrObject* pObj, SdrPageView* pPV, ULONG nOptions) const { return ImpCheckObjHit(rPnt,nTol,pObj,pPV,nOptions,NULL)!=NULL; }
    BOOL ImpIsFrameHandles() const;

//STRIP001     void ImpTakeDescriptionStr(const SdrMarkList& rML, USHORT nStrCacheID, String& rStr, USHORT nVal=0, USHORT nOpt=0) const;
//STRIP001     void ImpTakeDescriptionStr(USHORT nStrCacheID, String& rStr, USHORT nVal=0, USHORT nOpt=0) const;

    // Macht aus einer Winkelangabe in 1/100deg einen String inkl. Grad-Zeichen
//STRIP001     BOOL ImpMarkPoint(SdrHdl* pHdl, SdrMark* pMark, BOOL bUnmark);
    BOOL MarkPoints(const Rectangle* pRect, BOOL bUnmark);
    BOOL MarkGluePoints(const Rectangle* pRect, BOOL bUnmark);

    virtual void WriteRecords(SvStream& rOut) const;
    virtual BOOL ReadRecord(const SdrIOHeader& rViewHead, const SdrNamedSubRecord& rSubHead, SvStream& rIn);

    void SetMoveOutside(BOOL bOn);
    BOOL IsMoveOutside() const;

public:
//STRIP001     void ImpAfterPaint(); // Wird vom AfterPaintHandler der PaintView gerufen
//STRIP001 	void AfterInitRedraw(USHORT nWinNum); // Wird von InitRedraw der PaintView gerufen

    SdrMarkView(SdrModel* pModel1, OutputDevice* pOut=NULL);
    SdrMarkView(SdrModel* pModel1, ExtOutputDevice* pXOut);

    virtual void ToggleShownXor(OutputDevice* pOut, const Region* pRegion) const;
    virtual BOOL IsAction() const;
//STRIP001     virtual void MovAction(const Point& rPnt);
//STRIP001     virtual void EndAction();
//STRIP001     virtual void BckAction();
    virtual void BrkAction();
//STRIP001     virtual void TakeActionRect(Rectangle& rRect) const;

    virtual void ClearPageViews();
    virtual void HidePage(SdrPageView* pPV);
//STRIP001     virtual void SetPagePos(SdrPageView* pPV, const Point& rOffs);

    virtual BOOL IsObjMarkable(SdrObject* pObj, SdrPageView* pPV) const;

    // for SW and their rearranged painting; this method forces the
    // actual IAO-Handles to throw away saved contents 
    void ForceInvalidateMarkHandles();

    // Liefert TRUE wenn Objekte, Punkte oder Klebepunkte durch Rahmenaufziehen
    // selektiert werden (solange wie der Rahmen aufgezogen wird).
    BOOL IsMarking() const { return bMarking || bMarkingPoints || bMarkingGluePoints; }

    // Liefert TRUE wenn das Rahmenaufziehen nicht Objekte/Punkte/Klebepunkte
    // markieren sondern markierte deselektieren soll.
    BOOL IsUnmarking() const { return bUnmarking; }
    void SetUnmarking(BOOL bOn) { bUnmarking=bOn; }

    // Objekte durch Aufziehen eines Selektionsrahmens markieren
//STRIP001     BOOL BegMarkObj(const Point& rPnt, OutputDevice* pOut);
//STRIP001     BOOL BegMarkObj(const Point& rPnt, BOOL bUnmark=FALSE);
//STRIP001     void MovMarkObj(const Point& rPnt);
//STRIP001     BOOL EndMarkObj();
    void BrkMarkObj();
    BOOL IsMarkObj() const { return bMarking; }

    // DragModes: SDRDRAG_CREATE,SDRDRAG_MOVE,SDRDRAG_RESIZE,SDRDRAG_ROTATE,SDRDRAG_MIRROR,SDRDRAG_SHEAR,SDRDRAG_CROOK
    // Move==Resize
    // Das Interface wird hier evtl noch geaendert wg. Ortho-Drag
    void SetDragMode(SdrDragMode eMode);
    SdrDragMode GetDragMode() const { return eDragMode; }
    BOOL ChkDragMode(SdrDragMode eMode) const;
    void SetFrameHandles(BOOL bOn);
    BOOL IsFrameHandles() const { return bForceFrameHandles; }

    // Limit, ab wann implizit auf FrameHandles umgeschaltet wird. default=50.
    void SetFrameHandlesLimit(USHORT nAnz) { nFrameHandlesLimit=nAnz; }
    USHORT GetFrameHandlesLimit() const { return nFrameHandlesLimit; }

    void SetEditMode(SdrViewEditMode eMode);
    SdrViewEditMode GetEditMode() const { return eEditMode; }

    void SetEditMode(BOOL bOn=TRUE) { SetEditMode(bOn?SDREDITMODE_EDIT:SDREDITMODE_CREATE); }
    BOOL IsEditMode() const { return eEditMode==SDREDITMODE_EDIT; }
    void SetCreateMode(BOOL bOn=TRUE) { SetEditMode(bOn?SDREDITMODE_CREATE:SDREDITMODE_EDIT); }
    BOOL IsCreateMode() const { return eEditMode==SDREDITMODE_CREATE; }
    void SetGluePointEditMode(BOOL bOn=TRUE) { SetEditMode(bOn?SDREDITMODE_GLUEPOINTEDIT:eEditMode0); }
    BOOL IsGluePointEditMode() const { return eEditMode==SDREDITMODE_GLUEPOINTEDIT;; }

    void SetDesignMode(BOOL bOn=TRUE);
    BOOL IsDesignMode() const { return bDesignMode; }

    void SetFrameDragSingles(BOOL bOn=TRUE) { SetFrameHandles(bOn); }
    BOOL IsFrameDragSingles() const { return IsFrameHandles(); }

    // Feststellen, ob und wo ein Objekt bzw. ob ein Referenzpunkt
    // (Rotationsmittelpunkt,Spiegelachse) getroffen wird (SW special).
//STRIP001     SdrHitKind PickSomething(const Point& rPnt, short nTol=-2) const;
//STRIP001     BOOL HasMarkableObj() const;
//STRIP001     ULONG GetMarkableObjCount() const;
    BOOL HasMarkedObj() const { return aMark.GetMarkCount()!=0; }
    ULONG GetMarkedObjCount() const { return aMark.GetMarkCount(); }
    virtual void ShowMarkHdl(OutputDevice* pOut, BOOL bNoRefHdl=FALSE);
    virtual void HideMarkHdl(OutputDevice* pOut, BOOL bNoRefHdl=FALSE);
    BOOL IsMarkHdlShown() const { return bHdlShown; }

    // Mit MarkHdlHidden(TRUE) wird das Anzeigen der Handles
    // massiv unterdrueckt, auch bei ShowHarkHdl().
    // Show/HideMarkHdl() wird dann zwar immernoch von der Engine
    // gerufen, setzt auch den Status um (der mit IsMarkHdlShown()
    // abgefragt werden kann), Painted jedoch die Handles nicht.
    void SetMarkHdlHidden(BOOL bOn);
    BOOL IsMarkHdlHidden() const { return bHdlHidden; }
//    void SetMarkHdlBackgroundInvalid(BOOL bOn) { bSolidHdlBackgroundInvalid=bOn; }
//    BOOL IsMarkHdlBackgroundInvalid() const { return bSolidHdlBackgroundInvalid && bHdlShown && !bHdlHidden && aHdl.IsSolidHdl(); }
//STRIP001     BOOL IsMarkedHit(const Point& rPnt, short nTol=-2) const { return IsMarkedObjHit(rPnt,nTol); }
//STRIP001     BOOL IsMarkedObjHit(const Point& rPnt, short nTol=-2) const;
    SdrHdl* HitHandle(const Point& rPnt, const OutputDevice& rOut) const { return PickHandle(rPnt,rOut,0,NULL); }

    // Pick: Unterstuetzte Optionen fuer nOptions sind SEARCH_NEXT, SEARCH_BACKWARD (ni)
    SdrHdl* PickHandle(const Point& rPnt, const OutputDevice& rOut, ULONG nOptions=0, SdrHdl* pHdl0=NULL) const;
    SdrHdl* PickHandle(const Point& rPnt, ULONG nOptions=0, SdrHdl* pHdl0=NULL) const { return PickHandle(rPnt,*(const OutputDevice*)pActualOutDev,nOptions,pHdl0); }

    // Pick: Unterstuetzte Optionen fuer nOptions sind:
    // SDRSEARCH_DEEP SDRSEARCH_ALSOONMASTER SDRSEARCH_TESTMARKABLE SDRSEARCH_TESTTEXTEDIT
    // SDRSEARCH_WITHTEXT SDRSEARCH_TESTTEXTAREA SDRSEARCH_BACKWARD SDRSEARCH_MARKED
    // SDRSEARCH_WHOLEPAGE
    BOOL PickObj(const Point& rPnt, short nTol, SdrObject*& rpObj, SdrPageView*& rpPV, ULONG nOptions, SdrObject** ppRootObj, ULONG* pnMarkNum=NULL, USHORT* pnPassNum=NULL) const;
    BOOL PickObj(const Point& rPnt, short nTol, SdrObject*& rpObj, SdrPageView*& rpPV, ULONG nOptions=0) const;
    BOOL PickObj(const Point& rPnt, SdrObject*& rpObj, SdrPageView*& rpPV, ULONG nOptions=0) const { return PickObj(rPnt,nHitTolLog,rpObj,rpPV,nOptions); }
//STRIP001     BOOL MarkObj(const Point& rPnt, short nTol=-2, BOOL bToggle=FALSE, BOOL bDeep=FALSE);

    // Pick: Unterstuetzte Optionen fuer nOptions sind SDRSEARCH_PASS2BOUND und SDRSEARCH_PASS3NEAREST
//STRIP001     BOOL PickMarkedObj(const Point& rPnt, SdrObject*& rpObj, SdrPageView*& rpPV, ULONG* pnMarkNum=NULL, ULONG nOptions=0) const;

    // Sucht sich das Oberste der markierten Objekte (O1) und sucht von dort
    // aus in Richtung nach Unten dann das erste nichtmarkierte Objekt (O2).
    // Bei Erfolg wird die Markierung von O1 entfernt, an O2 gesetzt und TRUE
    // returniert. Mit dem Parameter bPrev=TRUE geht die Suche genau in die
    // andere Richtung.
//STRIP001     BOOL MarkNextObj(BOOL bPrev=FALSE);

    // Sucht sich das Oberste der markierten Objekte (O1) das von rPnt/nTol
    // getroffen wird und sucht von dort aus in Richtung nach Unten dann das
    // erste nichtmarkierte Objekt (O2). Bei Erfolg wird die Markierung von
    // O1 entfernt, an O2 gesetzt und TRUE returniert.
    // Mit dem Parameter bPrev=TRUE geht die Suche genau in die andere Richtung.
//STRIP001     BOOL MarkNextObj(const Point& rPnt, short nTol=-2, BOOL bPrev=FALSE);

    // Alle Objekte innerhalb eines rechteckigen Bereichs markieren
    // Markiert werden nur Objekte, die vollstaendig eingeschlossen sind.
//STRIP001     BOOL MarkObj(const Rectangle& rRect, BOOL bUnmark=FALSE);
    void MarkObj(SdrObject* pObj, SdrPageView* pPV, BOOL bUnmark=FALSE, BOOL bImpNoSetMarkHdl=FALSE);
//STRIP001     void MarkAllObj(SdrPageView* pPV=NULL); // pPage=NULL => alle angezeigten Seiten
    void UnmarkAllObj(SdrPageView* pPV=NULL); // pPage=NULL => alle angezeigten Seiten

    // Diese Funktion kostet etwas Zeit, da die MarkList durchsucht werden muss.
//STRIP001     BOOL IsObjMarked(SdrObject* pObj) const;
//STRIP001     void MarkAll(SdrPageView* pPV=NULL) { MarkAllObj(pPV); }
    void UnMarkAll(SdrPageView* pPV=NULL) { UnmarkAllObj(pPV); }
    const SdrMarkList& GetMarkList() const { return aMark; }
    void SortMarkList() { aMark.ForceSort(); }

    // Eine Liste aller an markierten Knoten gebundenen Kanten holen,
    // die selbst jedoch nicht markiert sind.
//STRIP001     const SdrMarkList& GetEdgesOfMarkedNodes() { ForceEdgesOfMarkedNodes(); return aEdgesOfMarkedNodes; }

    // Eine Beschreibung der z.Zt. markierten Objekte abholen.
    // Z.B. "3 Rechtecke" oder "252 Objekte" oder "Bitmap", ...
//STRIP001     String GetMarkDescription() const { return aMark.GetMarkDescription(); }

    // Groesse der Markierungs-Handles abfragen/setzen. Angabe in Pixel.
    // Der Wert ist als Kantenlaenge zu betrachten. Gerade Werte werden
    // auf Ungerade aufgerundet: 3->3, 4->5, 5->5, 6->7, 7->7, ...
    // Defaultwert ist 7, Mindestwert 3 Pixel.
    USHORT GetMarkHdlSizePixel() const;
    void SetMarkHdlSizePixel(USHORT nSiz);

    // Die Groesse der Markierungs-Handles wird ueber die jeweilige Aufloesung
    // und die Groesse des Bereichs der markierten Objekte so angepasst, dass
    // sie sich bei einer Frame-Selektion moeglichst nicht ueberschneiden.
    // Dazu muessen die Handles ggf. verkleinert dargestellt werden. Mit der
    // MinMarkHdlSize kann man hierfuer eine Mindestgroesse angeben.
    // Defaultwert ist 3, Mindestwert 3 Pixel.
    BOOL IsSolidMarkHdl() const { return aHdl.IsFineHdl(); }
    void SetSolidMarkHdl(BOOL bOn);

    BOOL HasMarkablePoints() const;
//STRIP001     ULONG GetMarkablePointCount() const;
    BOOL HasMarkedPoints() const;
//STRIP001     ULONG GetMarkedPointCount() const;

    // Nicht alle Punkte lassen sich markieren:
//STRIP001     BOOL IsPointMarkable(const SdrHdl& rHdl) const;
    BOOL MarkPoint(SdrHdl& rHdl, BOOL bUnmark=FALSE);

    // alle Punkte innerhalb dieses Rechtecks markieren (Viewkoordinaten)
    BOOL MarkPoints(const Rectangle& rRect, BOOL bUnmark=FALSE) { return MarkPoints(&rRect,bUnmark); }
//STRIP001     BOOL UnmarkPoint(SdrHdl& rHdl) { return MarkPoint(rHdl,TRUE); }
//STRIP001     BOOL UnMarkPoint(SdrHdl& rHdl) { return MarkPoint(rHdl,TRUE); }
//STRIP001     BOOL IsPointMarked(const SdrHdl& rHdl) const { ForceUndirtyMrkPnt(); return &rHdl!=NULL && rHdl.IsSelected(); }
//STRIP001     BOOL MarkAllPoints() { return MarkPoints(NULL,FALSE); }
    BOOL UnmarkAllPoints() { return MarkPoints(NULL,TRUE); }
    BOOL UnMarkAllPoints() { return MarkPoints(NULL,TRUE); }

    // Sucht sich den ersten markierten Punkt (P1) und sucht von dort
    // aus in den ersten nichtmarkierte Punkt (P2).
    // Bei Erfolg wird die Markierung von P1 entfernt, an P2 gesetzt und TRUE
    // returniert. Mit dem Parameter bPrev=TRUE geht die Suche genau in die
    // andere Richtung.
//STRIP001     BOOL MarkNextPoint(BOOL bPrev=FALSE);

    // Sucht sich den ersten markierten Punkt (P1) das von rPnt
    // getroffen wird und sucht von dort aus den
    // ersten nichtmarkierten Punkt (P2). Bei Erfolg wird die Markierung von
    // P1 entfernt, an P2 gesetzt und TRUE returniert.
    // Mit dem Parameter bPrev=TRUE geht die Suche genau in die andere Richtung.
//STRIP001     BOOL MarkNextPoint(const Point& rPnt, BOOL bPrev=FALSE);

    // Die Nummer des passenden Handles raussuchen. Nicht gefunden
    // liefert CONTAINER_ENTRY_NOTFOUND.
//STRIP001     ULONG GetHdlNum(SdrHdl* pHdl) const { return aHdl.GetHdlNum(pHdl); }
    SdrHdl* GetHdl(ULONG nHdlNum)  const { return aHdl.GetHdl(nHdlNum); }
    const SdrHdlList& GetHdlList() const { return aHdl; }

    // Selektionsrahmen fuer Punktmarkierung aufziehen.
    // Wird nur gestartet, wenn HasMarkablePoints() TRUE liefert.
//STRIP001     BOOL BegMarkPoints(const Point& rPnt, OutputDevice* pOut);
//STRIP001     BOOL BegMarkPoints(const Point& rPnt, BOOL bUnmark=FALSE);
//STRIP001     void MovMarkPoints(const Point& rPnt);
//STRIP001     BOOL EndMarkPoints();
    void BrkMarkPoints();
    BOOL IsMarkPoints() const { return bMarkingPoints; }

    // Zusatzhandles dauerhaft sichtbar schalten
    void SetPlusHandlesAlwaysVisible(BOOL bOn);
    BOOL IsPlusHandlesAlwaysVisible() const { return bPlusHdlAlways; }

    // Handles sichrbar waerend TextEdit (in doppelter Groesse)?
    // Persistent, default=FALSE
    void SetMarkHdlWhenTextEdit(BOOL bOn) { bMarkHdlWhenTextEdit=bOn; }
    BOOL IsMarkHdlWhenTextEdit() const { return bMarkHdlWhenTextEdit; }

//STRIP001     BOOL HasMarkableGluePoints() const;
//STRIP001     ULONG GetMarkableGluePointCount() const;
    BOOL HasMarkedGluePoints() const;
//STRIP001     ULONG GetMarkedGluePointCount() const;

    // Ein Klebepunkt wird eindeutig identifiziert durch das SdrObject
    // (dem er zugehoert) sowie einem USHORT nId (da jedes SdrObject je
    // mehrere Klebepunkte haben kann. Hier an der View kommt zudem noch
    // eine SdrPageView, die stets korrekt gesetzt sein sollte.
    // Alternativ kann ein Klebepunkt durch ein SdrHdl bezeichnet werden.
    // Die SdrHdl-Instanz beinhaltet dann aller erforderlichen Informationen.
    // Der Klebepunkt ist in diesem Fall dann zwangslaeufig markiert (nur auf
    // markierten Klebepunkten sitzen Anfasser).
    // Achtung: Bei jeder Aenderung des Klebepunktmarkierungsstatus wird die
    // Handleliste erneut berechnet. Alle vorher gemerkten SdrHdl* sind
    // damit ungueltig, ebenso die Punkt-Id's!
    // Pick: Unterstuetzte Optionen fuer nOptions sind SEARCH_NEXT, SEARCH_BACKWARD
    BOOL PickGluePoint(const Point& rPnt, SdrObject*& rpObj, USHORT& rnId, SdrPageView*& rpPV, ULONG nOptions=0) const;
//STRIP001     BOOL MarkGluePoint(const SdrObject* pObj, USHORT nId, const SdrPageView* pPV, BOOL bUnmark=FALSE);
//STRIP001     BOOL UnmarkGluePoint(const SdrObject* pObj, USHORT nId, const SdrPageView* pPV) { return MarkGluePoint(pObj,nId,pPV,TRUE); }
//STRIP001     BOOL IsGluePointMarked(const SdrObject* pObj, USHORT nId) const;
//STRIP001     BOOL UnmarkGluePoint(const SdrHdl& rHdl);

    // Hdl eines markierten GluePoints holen. Nicht markierte
    // GluePoints haben keine Handles
//STRIP001     SdrHdl* GetGluePointHdl(const SdrObject* pObj, USHORT nId) const;
//STRIP001     BOOL IsGluePoint(const SdrHdl& rHdl) const { return &rHdl!=NULL && rHdl.GetKind()==HDL_GLUE; }

    // alle Punkte innerhalb dieses Rechtecks markieren (Viewkoordinaten)
//STRIP001     BOOL MarkGluePoints(const Rectangle& rRect) { return MarkGluePoints(&rRect,FALSE); }
//STRIP001     BOOL UnmarkGluePoints(const Rectangle& rRect) { return MarkGluePoints(&rRect,TRUE); }
//STRIP001     BOOL MarkAllGluePoints() { return MarkGluePoints(NULL,FALSE); }
    BOOL UnmarkAllGluePoints() { return MarkGluePoints(NULL,TRUE); }

    // Sucht sich den ersten markierten Klebepunkt (P1) und sucht von dort
    // aus in den ersten nichtmarkierte Klebepunkt (P2).
    // Bei Erfolg wird die Markierung von P1 entfernt, an P2 gesetzt und TRUE
    // returniert. Mit dem Parameter bPrev=TRUE geht die Suche genau in die
    // andere Richtung.
//STRIP001     BOOL MarkNextGluePoint(BOOL bPrev=FALSE);

    // Sucht sich den ersten markierten Klebepunkt (P1) das von rPnt
    // getroffen wird und sucht von dort aus den
    // ersten nichtmarkierten Klebepunkt (P2). Bei Erfolg wird die Markierung
    // von P1 entfernt, an P2 gesetzt und TRUE returniert.
    // Mit dem Parameter bPrev=TRUE geht die Suche genau in die andere Richtung.
//STRIP001     BOOL MarkNextGluePoint(const Point& rPnt, BOOL bPrev=FALSE);

    // Selektionsrahmen fuer Klebepunktmarkierung aufziehen.
    // Wird nur gestartet, wenn HasMarkableGluePoints() TRUE liefert.
    // Der GlueEditMode TRUE wird nicht abgefragt.
//STRIP001     BOOL BegMarkGluePoints(const Point& rPnt, OutputDevice* pOut);
//STRIP001     BOOL BegMarkGluePoints(const Point& rPnt, BOOL bUnmark=FALSE);
//STRIP001     void MovMarkGluePoints(const Point& rPnt);
//STRIP001     BOOL EndMarkGluePoints();
    void BrkMarkGluePoints();
    BOOL IsMarkGluePoints() const { return bMarkingGluePoints; }

    // bRestraintPaint=FALSE bewirkt, dass die Handles nicht sofort wieder gemalt werden.
    // AdjustMarkHdl wird eh' nur gerufen, wenn was geaendert wurde; was idR ein Invalidate
    // zur Folge hat. Am Ende von des Redraw werden die Handles automatisch gezeichnet.
    // Der Zweck ist, unnoetiges Flackern zu vermeiden. -> Funkt noch nich, deshalb TRUE!
    void AdjustMarkHdl(BOOL bRestraintPaint=TRUE);

    const Rectangle& GetMarkedObjRect() const; // SnapRects der Objekte, ohne Strichstaerke
//STRIP001     Rectangle GetMarkedObjBoundRect() const;   // inkl. Strichstaerke, ueberstehende Fetzen, ...
//STRIP001     const Rectangle& GetMarkedPointsRect() const;     // Umschliessendes Rechteck aller markierten Punkte
//STRIP001     const Rectangle& GetMarkedGluePointsRect() const; // Umschliessendes Rechteck aller markierten Klebepunkte
//STRIP001     const Rectangle& GetAllMarkedRect() const { return GetMarkedObjRect(); }
//STRIP001     Rectangle GetAllMarkedBoundRect() const { return GetMarkedObjBoundRect(); }
//STRIP001     const Rectangle& GetAllMarkedPointsRect() const  { return GetMarkedPointsRect(); }

    // Wird immer dann gerufen, wenn sich die Liste der markierten Objekte
    // moeglicherweise geaendert hat. Wer ueberlaed muss unbedingt auch die
    // Methode der Basisklasse rufen!
    virtual void MarkListHasChanged();

    // Betreten (Editieren) einer evtl markierten Objektgruppe. Sind mehrere
    // Objektgruppen markiert, so wird die Oberste genommen. Anschliessend
    // liegen alle Memberobjekte der Gruppe im direkten Zugriff. Alle anderen
    // Objekte koennen waerendessen nicht bearbeitet werden (bis zum naechsten
    // LeaveGroup()). Bei einer seitenuebergreifenden Markierung wird jede Page
    // separat abgearbeitet. Die Methode liefert TRUE, wenn wenigstens eine
    // Gruppe betreten wurde.
//STRIP001     BOOL EnterMarkedGroup();

    // Den Mittelpunkt des letzten Crook-Dragging abholen. Den kann man
    // bei einem anschliessenden Rotate sinnvoll als Drehmittelpunkt setzen.
    const Point& GetLastCrookCenter() const { return aLastCrookCenter; }

    // Wird automatisch von der DragView beim beenden eines Crook-Drag gesetzt.
    void SetLastCrookCenter(const Point& rPt) { aLastCrookCenter=rPt; }

    // Rotationsmittelpunkt bzw. Startpunkt der Spiegelachse
    const Point& GetRef1() const { return aRef1; }
//STRIP001     void SetRef1(const Point& rPt);

    // Endpunkt der Spiegelachse
    const Point& GetRef2() const { return aRef1; }
    void SetRef2(const Point& rPt);

private:
    // #i13033#
    // Build transitive hull of complete selection in maAllMarkedObjects
    void ImplCollectCompleteSelection(SdrObject* pObj);
};

////////////////////////////////////////////////////////////////////////////////////////////////////
// 
// - Hit-Toleranzen:
//   Die muessen natuerlich immer in logischen Koordinaten angegeben werden. Also
//   immer brav den gewuenschten Pixelwert mit PixelToLogic in Logischen umrechnen.
//   Angenommen ein Wert 100 (logisch)
//   - Bei einer waagerechten Haarlinie (Objekt mit Hoehe 0) waere dann +/-100,
//     also ein vertikaler Bereich von 200 logischen Einheiten sensitiv.
//   - Bei Polygonen wird ein Rect mit der Groesse (200,200) generiert und ein
//     Touch-Test zwischen Poly und diesem Rect durchgefuehrt.
//   - Eine Sonderbehandlung erfahren Objekte, die bei SdrObject::HasEdit()==TRUE
//     liefern (z.B. Textrahmen). Hierbei wird ein weiterer sensitiver Bereich mit
//     einer Breite von 2*Tol (in diesem Beispiel also 200 Einheiten) um das Objekt
//     herumgelegt. Waerend ein Hit direkt ins Objekt die Edit-Methode ruft,
//     ermoeglicht ein Hit in den umliegenden sensitiven Bereich ein Dragging.
// 
////////////////////////////////////////////////////////////////////////////////////////////////////

#endif //_SVDMRKV_HXX

