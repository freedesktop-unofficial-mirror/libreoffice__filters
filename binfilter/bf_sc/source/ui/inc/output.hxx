/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: output.hxx,v $
 *
 *  $Revision: 1.6 $
 *
 *  last change: $Author: rt $ $Date: 2008-03-12 07:09:26 $
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

#ifndef SC_OUTPUT_HXX
#define SC_OUTPUT_HXX

#ifndef _LIST_HXX //autogen
#include <tools/list.hxx>
#endif
#ifndef _TOOLS_COLOR_HXX
#include <tools/color.hxx>
#endif
#ifndef _FRACT_HXX //autogen
#include <tools/fract.hxx>
#endif
class Rectangle;
class Font;
class OutputDevice;
class Window;
namespace binfilter {

class SvInPlaceObjectRef;
class EditEngine;
class ScDocument;
class ScBaseCell;
class ScPatternAttr;
class SvxMarginItem;
class SdrObject;
class SdrOle2Obj;
struct RowInfo;
class ScTabViewShell;
class ScPageBreakData;

// ---------------------------------------------------------------------------

#define SC_SCENARIO_HSPACE		60
#define SC_SCENARIO_VSPACE		50

//	Twips (Hoehe wird passend in Pixeln berechnet)
#define SC_CLIPMARK_SIZE	64

// ---------------------------------------------------------------------------

#define SC_OBJECTS_NONE			0
#define SC_OBJECTS_DRAWING		1
#define SC_OBJECTS_OLE			2
#define SC_OBJECTS_CHARTS		4
#define SC_OBJECTS_ALL			( SC_OBJECTS_DRAWING | SC_OBJECTS_OLE | SC_OBJECTS_CHARTS )

enum ScOutputType { OUTTYPE_WINDOW, OUTTYPE_PRINTER };

class ScOutputData
{
friend class ScDrawStringsVars;
private:
    OutputDevice* pDev;			// Device
    OutputDevice* pRefDevice;	// printer if used for preview
    OutputDevice* pFmtDevice;	// reference for text formatting
    RowInfo* pRowInfo;			// Info-Block
    USHORT nArrCount;			// belegte Zeilen im Info-Block
    ScDocument* pDoc;			// Dokument
    USHORT nTab;				// Tabelle
    long nScrX; 				// Ausgabe Startpos. (Pixel)
    long nScrY;
    long nScrW; 				// Ausgabe Groesse (Pixel)
    long nScrH;
    USHORT nX1;					// Start-/Endkoordinaten
    USHORT nY1;					//	( incl. versteckte )
    USHORT nX2;
    USHORT nY2;
    USHORT nVisX1; 				// Start-/Endkoordinaten
    USHORT nVisY1;				//	( sichtbarer Bereich )
    USHORT nVisX2;
    USHORT nVisY2;
    ScOutputType eType;			// Bildschirm/Drucker ...
    double nPPTX;				// Pixel per Twips
    double nPPTY;
//	USHORT nZoom;				// Zoom-Faktor (Prozent) - fuer GetFont
    Fraction aZoomX;
    Fraction aZoomY;

    SdrObject* pEditObj;		// beim Painten auslassen

    ScTabViewShell* pViewShell;	// zum Connecten von sichtbaren Plug-Ins

    BOOL bEditMode;				// InPlace editierte Zelle - nicht ausgeben
    USHORT nEditCol;
    USHORT nEditRow;

    BOOL bMetaFile;				// Ausgabe auf Metafile (nicht in Pixeln!)
    BOOL bSingleGrid;			// beim Gitter bChanged auswerten

    BOOL bPagebreakMode;		// Seitenumbruch-Vorschau
    BOOL bSolidBackground;		// weiss statt transparent

    BOOL bUseStyleColor;
    BOOL bForceAutoColor;

    BOOL bSyntaxMode;			// Syntax-Highlighting
    Color* pValueColor;
    Color* pTextColor;
    Color* pFormulaColor;

    Color	aGridColor;

    BOOL	bShowNullValues;
    BOOL	bShowFormulas;
    BOOL	bShowSpellErrors;	// Spell-Errors in EditObjekten anzeigen
    BOOL	bMarkClipped;

    BOOL	bSnapPixel;

    BOOL	bAnyRotated;		// intern
    BOOL	bAnyClipped;		// intern
    BOOL	bTabProtected;
    BYTE	nTabTextDirection;	// EEHorizontalTextDirection values

                            // private Methoden

    BOOL			IsEmptyCellText( RowInfo* pThisRowInfo, USHORT nX, USHORT nY );
    void			GetVisibleCell( USHORT nCol, USHORT nRow, USHORT nTab, ScBaseCell*& rpCell );

    BOOL			IsAvailable( USHORT nX, USHORT nY );
    long			GetAvailableWidth( USHORT nX, USHORT nY, long nNeeded );




    void			DrawRotatedFrame( const Color* pForceColor ){DBG_BF_ASSERT(0, "STRIP");} //STRIP001 void			DrawRotatedFrame( const Color* pForceColor );		// pixel

public:
                    ScOutputData( OutputDevice* pNewDev, ScOutputType eNewType,
                                    RowInfo* pNewRowInfo, USHORT nNewCount,
                                    ScDocument* pNewDoc,
                                    USHORT nNewTab, long nNewScrX, long nNewScrY,
                                    USHORT nNewX1, USHORT nNewY1, USHORT nNewX2, USHORT nNewY2,
                                    double nPixelPerTwipsX, double nPixelPerTwipsY,
                                    const Fraction* pZoomX = NULL,
                                    const Fraction* pZoomY = NULL );

                    ~ScOutputData();

    void	SetRefDevice( OutputDevice* pRDev ) { pRefDevice = pFmtDevice = pRDev; }
    void	SetFmtDevice( OutputDevice* pRDev ) { pFmtDevice = pRDev; }
    void	SetEditObject( SdrObject* pObj )	{ pEditObj = pObj; }
    void	SetViewShell( ScTabViewShell* pSh ) { pViewShell = pSh; }

    void	SetSolidBackground( BOOL bSet )		{ bSolidBackground = bSet; }
    void	SetUseStyleColor( BOOL bSet )		{ bUseStyleColor = bSet; }

    void	SetSyntaxMode( BOOL bNewMode );
    void	SetSingleGrid( BOOL bNewMode );
    void	SetGridColor( const Color& rColor );
    void	SetMarkClipped( BOOL bSet );
    void	SetShowNullValues ( BOOL bSet = TRUE );
    void	SetShowFormulas   ( BOOL bSet = TRUE );
    void	SetShowSpellErrors( BOOL bSet = TRUE );
    long	GetScrW() const		{ return nScrW; }
    long	GetScrH() const		{ return nScrH; }


    void	DrawGrid( BOOL bGrid, BOOL bPage );
    void	DrawStrings( BOOL bPixelToLogic = FALSE );
    void	DrawBackground();
    void	DrawShadow();
    void	DrawFrame();

                    // with logic MapMode set!
    void	DrawEdit(BOOL bPixelToLogic);

    void	FindRotated();


                                                    // nur Bildschirm:

    void	DrawingSingle( USHORT nLayer, USHORT nObjectFlags, USHORT nDummyFlags );


    BOOL	SetChangedClip();		// FALSE = nix

    void	FindChanged();
    void	DrawMark( Window* pWin );
    void	DrawClipMarks();

    void	DrawNoteMarks();
};



} //namespace binfilter
#endif

