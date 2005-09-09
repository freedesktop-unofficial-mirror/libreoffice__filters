/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: svddrgv.hxx,v $
 *
 *  $Revision: 1.3 $
 *
 *  last change: $Author: rt $ $Date: 2005-09-09 14:33:20 $
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

#ifndef _SVDDRGV_HXX
#define _SVDDRGV_HXX

// HACK to avoid too deep includes and to have some
// levels free in svdmark itself (MS compiler include depth limit)
#ifndef _SVDHDL_HXX
#include <bf_svx/svdhdl.hxx>
#endif

#include <bf_svx/svdxcgv.hxx>
namespace binfilter {

//************************************************************
//   Vorausdeklarationen
//************************************************************

class SdrUndoGeoObj;

////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  @@@@@  @@@@@   @@@@   @@@@   @@ @@ @@ @@@@@ @@   @@
//  @@  @@ @@  @@ @@  @@ @@  @@  @@ @@ @@ @@    @@   @@
//  @@  @@ @@  @@ @@  @@ @@      @@ @@ @@ @@    @@ @ @@
//  @@  @@ @@@@@  @@@@@@ @@ @@@  @@@@@ @@ @@@@  @@@@@@@
//  @@  @@ @@  @@ @@  @@ @@  @@   @@@  @@ @@    @@@@@@@
//  @@  @@ @@  @@ @@  @@ @@  @@   @@@  @@ @@    @@@ @@@
//  @@@@@  @@  @@ @@  @@  @@@@@    @   @@ @@@@@ @@   @@
//
////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////

class SdrDragView: public SdrExchangeView
{
    friend class				SdrPageView;
    friend class				SdrDragMethod;

protected:
    SdrHdl*						pDragHdl;
    SdrDragMethod*				pDragBla;
    SdrUndoGeoObj*				pInsPointUndo;

    Rectangle					aDragLimit;
    XubString					aInsPointUndoStr;
    SdrMarkList					aFollowingEdges; // Wenn Knoten gedraggd werden, sollen alle Kanten als Xor folgen

    SdrHdlKind					eDragHdl;

    ULONG						nDragXorPolyLimit;
    ULONG						nDragXorPointLimit;
    USHORT						nRubberEdgeDraggingLimit;
    USHORT						nDetailedEdgeDraggingLimit;

    unsigned					bFramDrag : 1;        // z.Zt. FrameDrag
    unsigned					bDragSpecial : 1;     // z.Zt. Special Obj-Dragging
    unsigned					bMarkedHitMovesAlways : 1; // Persistent
    unsigned					bDragLimit : 1;      // Limit auf SnapRect statt BoundRect
    unsigned					bDragHdl : 1;        // TRUE: RefPt wird verschoben
    unsigned					bDragStripes : 1;    // Persistent
    unsigned					bNoDragHdl : 1;      // Persistent - Handles waehrend des Draggens verstecken
    unsigned					bMirrRefDragObj : 1; // Persistent - Waehrend des Draggens der Spiegelachse die gespiegelten Objekte als Xor zeigen
    unsigned					bSolidDragging : 1;  // Dragging und Create in Echtzeit erlaubt
    unsigned					bSolidDrgNow : 1;    // SolidDragging laeuft gerade (z.Zt. noch FALSE bei 3D (LibObjs))
    unsigned					bSolidDrgChk : 1;    // SolidDragging gecheckt
    unsigned					bMouseHideWhileDraggingPoints : 1;
    unsigned					bResizeAtCenter : 1;
    unsigned					bCrookAtCenter : 1;
    unsigned					bDragWithCopy : 1;
    unsigned					bInsAfter : 1;       // Parameter zum Einfuegen von Folgepunkten
    unsigned					bInsGluePoint : 1;
    unsigned					bInsObjPointMode : 1;
    unsigned					bInsGluePointMode : 1;
    unsigned					bNoDragXorPolys : 1;
    unsigned					bAutoVertexCon : 1;  // Automatische Konnektorgenerierung an den Scheitelpunkten
    unsigned					bAutoCornerCon : 1;  // Automatische Konnektorgenerierung an den Eckpunkten
    unsigned					bRubberEdgeDragging : 1;
    unsigned					bDetailedEdgeDragging : 1;

private:
    void ImpClearVars();
    void ImpMakeDragAttr();
    void ImpDelDragAttr();

protected:
    // aDragPoly0 an den PageViews setzen
//STRIP001 	void ImpDrawEdgeXor(ExtOutputDevice& rXOut, BOOL bFull) const;
//STRIP001 	void SetDragPolys(BOOL bReset=FALSE, BOOL bSeparate=FALSE);
//STRIP001 	virtual void ShowDragObj(OutputDevice* pOut);
//STRIP001 	virtual void HideDragObj(OutputDevice* pOut);
//STRIP001 	virtual void DrawDragObj(OutputDevice* pOut, BOOL bFull) const;
    BOOL BegInsObjPoint(BOOL bIdxZwang, USHORT nIdx, const Point& rPnt, BOOL bNewObj, OutputDevice* pOut, short nMinMov);
    virtual void WriteRecords(SvStream& rOut) const;
    virtual BOOL ReadRecord(const SdrIOHeader& rViewHead, const SdrNamedSubRecord& rSubHead, SvStream& rIn);

public:
    SdrDragView(SdrModel* pModel1, OutputDevice* pOut=NULL);
    SdrDragView(SdrModel* pModel1, ExtOutputDevice* pXOut);
    virtual ~SdrDragView();

    virtual void ToggleShownXor(OutputDevice* pOut, const Region* pRegion) const;
    virtual BOOL IsAction() const;
//STRIP001 	virtual void MovAction(const Point& rPnt);
//STRIP001 	virtual void EndAction();
//STRIP001 	virtual void BckAction();
    virtual void BrkAction();
//STRIP001 	virtual void TakeActionRect(Rectangle& rRect) const;

    // Spezialimplementation fuer den Writer:
    // TakeDragObjAnchorPos() liefert die Position an der ein Objekt
    // beim Draggen einer Einfachselektion ungefaehr landet wenn es
    // "losgelassen" wird (EndDrag).
    // In der Regel ist das die linke obere Ecke des zu erwartenden neuen
    // SnapRects. Ausnahme: CaptionObj. Dort ist es die Position des
    // "Schwanzendes".
    // Bei Returncode FALSE konnte ich die Position nicht bestimmen
    // (z.B. Punktverschiebung, Mehrfachselektion, Schieben der
    // Spiegelschse, ...)
//STRIP001     BOOL TakeDragObjAnchorPos(Point& rPos, BOOL bTopRight = FALSE ) const;

    // Wird pForcedMeth uebergeben, so wird pHdl, ... nicht ausgewerten, sondern diese
    // Drag-Methode verwendet. Die Instanz geht dabei ins Eigentum der View ueber und
    // wird zum Ende des Draggings destruiert.
//STRIP001 	virtual BOOL BegDragObj(const Point& rPnt, OutputDevice* pOut=NULL, SdrHdl* pHdl=NULL, short nMinMov=-3, SdrDragMethod* pForcedMeth=NULL);
//STRIP001 	void MovDragObj(const Point& rPnt);
//STRIP001 	BOOL EndDragObj(BOOL bCopy=FALSE);
    void BrkDragObj();
    BOOL IsDragObj() const { return pDragBla!=NULL && !bInsPolyPoint && !bInsGluePoint; }
    SdrHdl* GetDragHdl() const { return pDragHdl; }
    SdrDragMethod* GetDragMethod() const { return pDragBla; }
//STRIP001 	BOOL IsMoveOnlyDragObj(BOOL bAskRTTI=FALSE) const;
    BOOL IsDraggingPoints() const { return eDragHdl==HDL_POLY; }
    BOOL IsDraggingGluePoints() const { return eDragHdl==HDL_GLUE; }

    // Wer das beim BegDrag oder mittendrin schon festlegen will.
    // (Wird bei jedem BegDrag auf FALSE zurueckgesetzt, also nach
    // BegDrag setzen.)
    void SetDragWithCopy(BOOL bOn) { bDragWithCopy = bOn; }
    BOOL IsDragWithCopy() const { return bDragWithCopy; }

    void SetInsertAfter(BOOL bOn) { bInsAfter = bOn; }
    BOOL IsInsertAfter() const { return bInsAfter; }

    void SetInsertGluePoint(BOOL bOn) { bInsGluePoint = bOn; }
    BOOL IsInsertGluePoint() const { return bInsGluePoint; }

    // Interaktives einfuegen eines neuen Punktes. nIdx=0 => vor dem ersten Punkt.
    BOOL IsInsObjPointPossible() const;
    BOOL IsInsPointPossible() const { return IsInsObjPointPossible(); }
    BOOL BegInsObjPoint(USHORT nIdx, const Point& rPnt, BOOL bNewObj, OutputDevice* pOut=NULL, short nMinMov=-3) { return BegInsObjPoint(TRUE,nIdx,rPnt,bNewObj,pOut,nMinMov); }
    BOOL BegInsObjPoint(const Point& rPnt, BOOL bNewObj, OutputDevice* pOut=NULL, short nMinMov=-3) { return BegInsObjPoint(FALSE,0,rPnt,bNewObj,pOut,nMinMov); }
//STRIP001 	void MovInsObjPoint(const Point& rPnt) { MovDragObj(rPnt); }
//STRIP001 	BOOL EndInsObjPoint(SdrCreateCmd eCmd);
    void BrkInsObjPoint() { BrkDragObj(); }
    BOOL IsInsObjPoint() const { return pDragBla!=NULL && bInsPolyPoint; }

    // Fuer die App zum Verwalten des Status. GetPreferedPointer() wird
    // spaeter vielleicht einen passenden Pointer dafuer liefern
    void SetInsObjPointMode(BOOL bOn) { bInsObjPointMode = bOn; }
    BOOL IsInsObjPointMode() const { return bInsObjPointMode; }

    BOOL IsInsGluePointPossible() const;
//STRIP001 	BOOL BegInsGluePoint(const Point& rPnt);
//STRIP001 	void MovInsGluePoint(const Point& rPnt) { MovDragObj(rPnt); }
//STRIP001 	BOOL EndInsGluePoint() { return EndDragObj(); }
    void BrkInsGluePoint() { BrkDragObj(); }
    BOOL IsInsGluePoint() const { return pDragBla!=NULL && bInsGluePoint; }

    // Fuer die App zum Verwalten des Status. GetPreferedPointer() wird
    // spaeter vielleicht einen passenden Pointer dafuer liefern
    void SetInsGluePointMode(BOOL bOn) { bInsGluePointMode = bOn; }
    BOOL IsInsGluePointMode() const { return bInsGluePointMode; }

    // Begrenzungslinien ueber's gesamte Win waehrend des Draggens
    // Persistent. Default=FALSE.
    void SetDragStripes(BOOL bOn);
    BOOL IsDragStripes() const { return bDragStripes; }

    // Handles waehrend des Draggens verstecken
//STRIP001 	void SetDragHdlHide(BOOL bOn);
    BOOL IsDragHdlHide() const { return bNoDragHdl; }

    // Beim Draggen von Polygonpunkten und Klebepunkten
    // die Maus verstecken. Default=FALSE
    void SetMouseHideWhileDraggingPoints(BOOL bOn) { bMouseHideWhileDraggingPoints = bOn; }
    BOOL IsMouseHideWhileDraggingPoints() const { return bMouseHideWhileDraggingPoints; }

    // Beim Draggen werden i.d.R. die Konturen der markierten Objekte
    // als Xor-Polygone dargestellt. Wird dieses Flag hier gesetzt,
    // wird (z.B. bei Mehrfachselektion) nur ein Xor-Frame gezeichnet.
    // Bei objektspeziefischem Dragging (Polygonpunkte,Eckenradius,...
    // hat diese Einstellung keine Auswirkung.
    // Auch waerend des Draggens umschaltbar.
    // Default=Off
    void SetNoDragXorPolys(BOOL bOn);
    BOOL IsNoDragXorPolys() const { return bNoDragXorPolys; }

    // Uebersteigt die Anzahl der markierten Objekte den hier eingestellten
    // Wert, wird implizit (temporaer) auf NoDragPolys geschaltet.
    // PolyPolygone etc werden entsprechend als mehrere Objekte gewertet.
    // Default=100
    void  SetDragXorPolyLimit(ULONG nObjAnz) { nDragXorPolyLimit=nObjAnz; }
    ULONG GetDragXorPolyLimit() const { return nDragXorPolyLimit; }

    // Wie DragXorPolyLimit, jedoch bezogen auf die Gesamtpunktanzahl
    // aller Polygone. Default=500.
    // Auf NoDragPolys wird (temporaer) geschaltet, wenn eins der Limits
    // ueberstiegen wird.
    void  SetDragXorPointLimit(ULONG nPntAnz) { nDragXorPointLimit=nPntAnz; }
    ULONG GetDragXorPointLimit() const { return nDragXorPointLimit; }

    void SetSolidDragging(BOOL bOn) { bSolidDragging = bOn; }
    BOOL IsSolidDragging() const { return bSolidDragging; }

    void SetSolidDraggingNow(BOOL bOn) { bSolidDrgNow = bOn; }
    BOOL IsSolidDraggingNow() const { return bSolidDrgNow; }

    void SetSolidDraggingCheck(BOOL bOn) { bSolidDrgChk = bOn; }
    BOOL IsSolidDraggingCheck() const { return bSolidDrgChk; }

    // Dragging/Creating von Verbindern:
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // Verbinder an Objektscheitelpunkte ankleben
    // Default=TRUE=Ja
    void SetAutoVertexConnectors(BOOL bOn) { bAutoVertexCon = bOn; }
    BOOL IsAutoVertexConnectors() const { return bAutoVertexCon; }

    // Verbinder an Objektecken ankleben
    // Default=FALSE=Nein
    void SetAutoCornerConnectors(BOOL bOn) { bAutoCornerCon = bOn; }
    BOOL IsAutoCornerConnectors() const { return bAutoCornerCon; }

    // Dragging von verbundenen Objekten (Nodes):
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // DetailedEdgeDraggingLimit: Wie RubberEdgeDraggingLimit, jedoch bezieht
    // sich dieses Limit auf die detalierte Darstellung, d.h. nicht nur
    // Gummibaender sondern komplette Neuberechnunen sind beim Draggen sichtbar.
    // Diese detalierte Darstellung ist eh nur beim MoveDrag moeglich.
    // Defaultwert ist 10
//STRIP001 	void SetDetailedEdgeDragging(BOOL bOn); // Default an
    BOOL IsDetailedEdgeDragging() const { return bDetailedEdgeDragging; }

//STRIP001 	void SetDetailedEdgeDraggingLimit(USHORT nEdgeObjAnz);
    USHORT GetDetailedEdgeDraggingLimit() const { return nDetailedEdgeDraggingLimit; }

    // EdgeDraggingLimit: Sind mehr als nEdgeObjAnz Kanten betroffen, werden
    // diese beim interaktiven Draggen nicht mit angezeigt.
    // Gemeint sind hier die "Gummibaender", die weniger Rechenzeit benoetigen
    // als die kompletten Neuberechnungen beim DetailedEdgeDragging.
    // Defaultwert ist 100
//STRIP001 	void SetRubberEdgeDragging(BOOL bOn);  // Default an
    BOOL IsRubberEdgeDragging() const { return bRubberEdgeDragging; }

//STRIP001 	void SetRubberEdgeDraggingLimit(USHORT nEdgeObjAnz);
    USHORT GetRubberEdgeDraggingLimit() const { return nRubberEdgeDraggingLimit; }

    // Verbinderhandling also zu deutsch wie folgt (bei Defaulteinstellungen):
    // - Sind bis max 10 Verbinder betroffen werden diese bei jedem
    //   MouseMove neu berechnet
    // - Sind zwischen 11 und 100 Verbinder betroffen werden die
    //   Verbindungen beim Draggen als gerade Linien dargestellt.
    // - Bei mehr als 100 betroffenen Verbindern wird beim Draggen nichts
    //   mehr gezeichnet was auf Verbinder hinweist.

    // Ist ein spezieller Dragmode eingeschaltet, wie Rotate, Mirror oder Crook,
    // dann leitet ein Hit auf das markierte Objekt genau dieses Dragging ein.
    // Setzt man MarkedHitMovesAlways auf TRUE, so leitet ein Hit auf das
    // markierte Objekt immer ein Moven ein, unabhaengig vom gesetzten DragMode.
    // Dieses Flag ist persistent und sollte von der App fuer den Anwender
    // konfigurierbar sein!
    void SetMarkedHitMovesAlways(BOOL bOn) { bMarkedHitMovesAlways = bOn; }
    BOOL IsMarkedHitMovesAlways() const { return bMarkedHitMovesAlways; }

    // Beim Draggen der Spiegelachse das Spiegelbild der markierten Objekte
    // als Xor darstellen? Persistent. Noch nicht implementiert. Default TRUE.
    void SetMirrRefDragObj(BOOL bOn) { bMirrRefDragObj = bOn; }
    BOOL IsMirrRefDragObj() const { return bMirrRefDragObj; }

//STRIP001 	BOOL IsOrthoDesired() const;

    // Beim Resize die Mitte als Referenz
    // Default=FALSE.
    BOOL IsResizeAtCenter() const { return bResizeAtCenter; }
    void SetResizeAtCenter(BOOL bOn) { bResizeAtCenter = bOn; SnapMove(); }

    // Symmetrisches Crook
    // Default=FALSE.
    BOOL IsCrookAtCenter() const { return bCrookAtCenter; }
    void SetCrookAtCenter(BOOL bOn) { bCrookAtCenter = bOn; SnapMove(); }

    // Begrenzung des Arbeitsbereichs. Die Begrenzung bezieht sich auf die
    // View, nicht auf die einzelnen PageViews. Von der View wird diese
    // Begrenzung nur bei Interaktionen wie Dragging und Create ausgewertet.
    // Bei von der App algorithmisch oder UI-gesteuerte Aktionen (SetGeoAttr,
    // MoveMarkedObj, ...) muss die App dieses Limit selbst beruecksichtigen.
    // Ferner ist dieses Limit als Grob-Limit zu sehen. U.U. koennen Objekte
    // (z.B. beim Drehen) nicht exakt bis an dieses Limit herangedraggt werden,
    // koennen Objekte durch Rundungsfehler doch etwas ueberstehen, ... .
    // Default=EmptyRect=keine Begrenzung.
    // erst z.T. impl.
    // (besser in die DragView?)
    void SetWorkArea(const Rectangle& rRect) { aMaxWorkArea=rRect; }
    const Rectangle& GetWorkArea() const { return aMaxWorkArea; }

    // Das DragLimit ist bezogen auf die Page des Objekts.
    // (Oder auf die View??? Muss ich mal^^^^recherchieren. Joe.)
    // FALSE=Kein Limit.
    // Das Rueckgabe-Rect muss absolute Koordinaten enthalten. Der Maximale
    // Dragbereich wird von der View dann so gewaehlt, dass das SnapRect des
    // Objekts bis Maximal auf die Kante des LimitRects gemoved bzw. gesized
    // wird. Bei Objekten wie Bezierkurven, gedrehten Rechtecken ist zu beachten
    // das durch anschliessende Neuberechnung des SnapRects (bei Resize)
    // Rundungsfehler auftreten koennen, wodurch das LimitRect minnimal
    // ueberschritten werden koennte...
    // Implementiert fuer Move und Resize.
//STRIP001 	virtual BOOL TakeDragLimit(SdrDragMode eMode, Rectangle& rRect) const;
};

}//end of namespace binfilter
#endif //_SVDDRGV_HXX

