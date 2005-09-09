/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: drwlayer.hxx,v $
 *
 *  $Revision: 1.3 $
 *
 *  last change: $Author: rt $ $Date: 2005-09-09 11:12:53 $
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

#ifndef SC_DRWLAYER_HXX
#define SC_DRWLAYER_HXX

#ifndef _SV_GRAPH_HXX //autogen
#include <vcl/graph.hxx>
#endif
#ifndef _FM_FMMODEL_HXX
#include <bf_svx/fmmodel.hxx>
#endif
#ifndef _SVSTOR_HXX
#include <so3/svstor.hxx>
#endif
#ifndef SC_SCGLOB_HXX
#include "global.hxx"
#endif
namespace binfilter {

class ScDocument;
class SfxViewShell;
class ScDrawObjData;
class ScIMapInfo;
class IMapObject;
class ScMarkData;
class SdrOle2Obj;

// -----------------------------------------------------------------------

class ScTabDeletedHint : public SfxHint
{
private:
    USHORT	nTab;
public:
            TYPEINFO();
            ScTabDeletedHint( USHORT nTabNo = USHRT_MAX );
    virtual	~ScTabDeletedHint();

    USHORT	GetTab()	{ return nTab; }
};

class ScTabSizeChangedHint : public SfxHint
{
private:
    USHORT	nTab;
public:
            TYPEINFO();
            ScTabSizeChangedHint( USHORT nTabNo = USHRT_MAX );
    virtual	~ScTabSizeChangedHint();

    USHORT	GetTab()	{ return nTab; }
};

// -----------------------------------------------------------------------


class ScDrawLayer: public FmFormModel
{
private:
    SvStorageRef	xPictureStorage;
    String			aName;
    ScDocument*		pDoc;
    SdrUndoGroup*	pUndoGroup;
    BOOL			bRecording;
    BOOL			bAdjustEnabled;
    BOOL			bHyphenatorSet;

private:
    void			MoveAreaTwips( USHORT nTab, const Rectangle& rArea, const Point& rMove,
                                const Point& rTopLeft );
//STRIP001 	void			MoveCells( USHORT nTab, USHORT nCol1,USHORT nRow1, USHORT nCol2,USHORT nRow2,
//STRIP001 								short nDx,short nDy );
//STRIP001 	void			RecalcPos( SdrObject* pObj, ScDrawObjData* pData );

public:
                    ScDrawLayer( ScDocument* pDocument, const String& rName );
    virtual			~ScDrawLayer();

    virtual SdrPage*  AllocPage(FASTBOOL bMasterPage);
//STRIP001 	virtual SdrModel* AllocModel() const;
    virtual void	SetChanged( FASTBOOL bFlg = TRUE );

//STRIP001 	virtual Window* GetCurDocViewWin();
    virtual SvStream* GetDocumentStream(SdrDocumentStreamInfo& rStreamInfo) const;

//STRIP001 	virtual SdrLayerID GetControlExportLayerId( const SdrObject & ) const;

    void			ReleasePictureStorage();

//STRIP001 	BOOL			HasObjects() const;

    void			ScAddPage( USHORT nTab );
//STRIP001 	void			ScRemovePage( USHORT nTab );
    void			ScRenamePage( USHORT nTab, const String& rNewName );
//STRIP001 	void			ScMovePage( USHORT nOldPos, USHORT nNewPos );
                    // inkl. Inhalt, bAlloc=FALSE -> nur Inhalt
//STRIP001 	void			ScCopyPage( USHORT nOldPos, USHORT nNewPos, BOOL bAlloc );

    ScDocument*		GetDocument() const { return pDoc; }

    void			UpdateBasic();				// DocShell-Basic in DrawPages setzen
//STRIP001 	void			UseHyphenator();

    void			Load( SvStream& rStream );
    void			Store( SvStream& rStream ) const;

    BOOL			GetPrintArea( ScRange& rRange, BOOL bSetHor, BOOL bSetVer ) const;

                    //		automatische Anpassungen

    void			EnableAdjust( BOOL bSet = TRUE )	{ bAdjustEnabled = bSet; }

    void			BeginCalcUndo();
    SdrUndoGroup*	GetCalcUndo();
    BOOL			IsRecording()			{ return bRecording; }
    void			AddCalcUndo( SdrUndoAction* pUndo );

//STRIP001 	void			MoveArea( USHORT nTab, USHORT nCol1,USHORT nRow1, USHORT nCol2,USHORT nRow2,
//STRIP001 								short nDx,short nDy, BOOL bInsDel );
    void			WidthChanged( USHORT nTab, USHORT nCol, long nDifTwips );
    void			HeightChanged( USHORT nTab, USHORT nRow, long nDifTwips );

    BOOL			HasObjectsInRows( USHORT nTab, USHORT nStartRow, USHORT nEndRow );

//STRIP001 	void			DeleteObjectsInArea( USHORT nTab, USHORT nCol1,USHORT nRow1,
//STRIP001 											USHORT nCol2,USHORT nRow2 );
//STRIP001 	void			DeleteObjectsInSelection( const ScMarkData& rMark );
//STRIP001 	void			DeleteObjects( USHORT nTab );

//STRIP001 	void			CopyToClip( ScDocument* pClipDoc, USHORT nTab, const Rectangle& rRange );
//STRIP001 	void			CopyFromClip( ScDrawLayer* pClipModel,
//STRIP001 									USHORT nSourceTab, const Rectangle& rSourceRange,
//STRIP001 									const ScAddress& rDestPos, const Rectangle& rDestRange );

    void			SetPageSize( USHORT nPageNo, const Size& rSize );
//STRIP001 	ULONG			GetDefTextHeight() const;

                    //	GetVisibleName: name for navigator etc: GetPersistName or GetName
                    //	(ChartListenerCollection etc. must use GetPersistName directly)
//STRIP001 	static String	GetVisibleName( SdrObject* pObj );

    SdrObject*		GetNamedObject( const String& rName, USHORT nId, USHORT& rFoundTab ) const;
                    // if pnCounter != NULL, the search for a name starts with this index + 1,
                    // and the index really used is returned.
//STRIP001     String          GetNewGraphicName( long* pnCounter = NULL ) const;
//STRIP001 	void			EnsureGraphicNames();

    // Verankerung setzen und ermitteln
    static void		SetAnchor( SdrObject*, ScAnchorType );
    static ScAnchorType	GetAnchor( const SdrObject* );

    // Positionen fuer Detektivlinien
    static ScDrawObjData* GetObjData( SdrObject* pObj, BOOL bCreate=FALSE );

    // Image-Map
    static ScIMapInfo* GetIMapInfo( SdrObject* pObj );

//STRIP001 	static Graphic	GetGraphicFromOle2Obj( const SdrOle2Obj* pOle2Obj );
//STRIP001 	static IMapObject* GetHitIMapObject( SdrObject* pObject,
//STRIP001 							const Point& rWinPoint, const Window& rCmpWnd );

private:
    static SvPersist* pGlobalDrawPersist;			// fuer AllocModel
public:
//STRIP001 	static void		SetGlobalDrawPersist(SvPersist* pPersist);
};


} //namespace binfilter
#endif


