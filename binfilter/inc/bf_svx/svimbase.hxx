/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: svimbase.hxx,v $
 *
 *  $Revision: 1.3 $
 *
 *  last change: $Author: rt $ $Date: 2005-09-09 14:49:48 $
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

#ifndef _SVIMBASE_HXX
#define _SVIMBASE_HXX

#ifndef _SV_BITMAP_HXX //autogen
#include <vcl/bitmap.hxx>
#endif
#ifndef _SV_SALBTYPE_HXX //autogen
#include <vcl/salbtype.hxx>
#endif
namespace binfilter {

// -----------
// - Defines -
// -----------

#ifdef WIN
#define _SVHUGE huge
#else
#define _SVHUGE
#endif

// ----------------
// - SimDepthType -
// ----------------

enum SimDepthType
{
    SIM_DEPTH_1,
    SIM_DEPTH_4,
    SIM_DEPTH_8,
    SIM_DEPTH_24
};

// ------------
// - SimColor -
// ------------

struct SimColor
{
    BYTE cBlue;
    BYTE cGreen;
    BYTE cRed;
};

// ------------------------------------------------------------------------

inline BOOL operator==( const SimColor& rCol1, const SimColor& rCol2 )
{
    return ( ( rCol1.cRed == rCol2.cRed ) &&
             ( rCol1.cGreen == rCol2.cGreen ) &&
             ( rCol1.cBlue == rCol2.cBlue ) );
}

// --------------
// - SimPalette -
// --------------

struct SimPalette
{
    ULONG		nColors;
    SimColor	aColorArray[ 256 ];
};

// ---------------
// - SvImageBase -
// ---------------

class SfxViewFrame;
class SfxProgress;

class SvImageBase
{
private:

    Bitmap				aOutBitmap;
    HPBYTE				pArray1;
    HPBYTE				pArray2;
    HPBYTE				pArray3;
    HPBYTE				pArray4;
    HPBYTE				pOrgArray;
    HPBYTE				pDestArray;
    SimPalette*			pPal1;
    SimPalette*			pPal2;
    SimPalette*			pPal3;
    SimPalette*			pPal4;
    ULONG				nWidth1;
    ULONG				nWidth2;
    ULONG				nWidth3;
    ULONG				nWidth4;
    ULONG				nHeight1;
    ULONG				nHeight2;
    ULONG				nHeight3;
    ULONG				nHeight4;
    ULONG				nAlignedWidth1;
    ULONG				nAlignedWidth2;
    ULONG				nAlignedWidth3;
    ULONG				nAlignedWidth4;
    ULONG				nWhichOrg;
    SimDepthType		eOrgDepth;
    SimDepthType		eUndoDepth;
    SimDepthType		eRedoDepth;
    BOOL				bIsUndo;
    BOOL				bIsRedo;
    BOOL				bCreateUndo;
    BOOL				bValid;
    BOOL				bDitherAll;

    HPBYTE				BitmapToArray24( const Bitmap& rBitmap, ULONG* pWidth,
                                         ULONG* pHeight, ULONG* pAlignedWidth,
                                         SfxViewFrame *pFrame = NULL );
    BOOL				Array24ToBitmap( HPBYTE pArray, Bitmap &rBitmap,
                                         const ULONG nWidth, const ULONG nHeight,
                                         const ULONG nColorCount = 256,
                                         ULONG nLast = 0, SfxProgress* pProgress = NULL );

    Bitmap				CreateSaveBitmap( const SimDepthType eDepth, SfxViewFrame *pFrame = NULL );

    HPBYTE				CreateArray24( ULONG nWidth, ULONG nHeight );
    void				DeleteArray( HPBYTE pArray );

                        SvImageBase(const SvImageBase& rSvImageBase);
    const SvImageBase&  operator=(const SvImageBase& rSvImageBase);

public:

                        SvImageBase();
                        SvImageBase( const Bitmap& rBitmap,
                                     const ULONG nColorCount = 256,
                                     ULONG nLast = 0, SfxProgress* pProgress = NULL );
                        ~SvImageBase();

    BOOL				IsValid() { return bValid; }

    ULONG				GetOrgWidth() const { return nWhichOrg == 1 ? nWidth1 : nWidth2; }
    ULONG				GetDestWidth() const { return nWhichOrg == 1 ? nWidth2 : nWidth1; }

    ULONG				GetOrgHeight() const { return nWhichOrg == 1 ? nHeight1 : nHeight2; }
    ULONG				GetDestHeight() const { return nWhichOrg == 1 ? nHeight2 : nHeight1; }

    ULONG				GetOrgAlignedWidth() const { return nWhichOrg == 1 ? nAlignedWidth1 : nAlignedWidth2; }
    ULONG				GetDestAlignedWidth() const { return nWhichOrg == 1 ? nAlignedWidth2 : nAlignedWidth1; }

    ULONG				GetOrgAlignedSize() const { return GetOrgAlignedWidth() * GetOrgHeight(); }
    ULONG				GetDestAlignedSize() const { return GetDestAlignedWidth() * GetDestHeight(); }

    // Farbtiefe des Ausgangsbildes ermitteln und setzen
    SimDepthType		GetDepth() const { return eOrgDepth; }
    void				SetDepth( const SimDepthType eDepth ) { eOrgDepth = eDepth; }

    // Farbtiefen nach Undo und Redo ermitteln und setzen
    SimDepthType		GetUndoDepth() const { return eUndoDepth; }
    void				SetUndoDepth(const SimDepthType eDepth) { eUndoDepth = eDepth; }

    SimDepthType		GetRedoDepth() const { return eRedoDepth; }
    void				SetRedoDepth(const SimDepthType eDepth) { eRedoDepth = eDepth; }

    // Vor- und Ruecklauf der Bildverarbeitung
    BOOL				BeginProcessing( BOOL bUndo = TRUE );
    void				EndProcessing();

    BOOL				BeginProcessingExt(ULONG nWidth, ULONG nHeight, BOOL bUndo = TRUE);
    void				EndProcessingExt() { EndProcessing(); }

    // Zeiger auf Arrays zur Verfuegung stellen
    HPBYTE				GetOrgPointer() { return pOrgArray; }
    HPBYTE				GetDestPointer() { return pDestArray; }

    // DIB-Erzeugung fuer Anzeige
    BOOL				CreateOutBitmap( const ULONG nColorCount = 256, ULONG nLast = 0,
                                         SfxProgress* pProgress = NULL );

    // Undo-Verwaltung
    BOOL				DoUndo( SfxProgress* pProgress = NULL );
    BOOL				DoRedo( SfxProgress* pProgress = NULL );

    // DIB-Rueckgabe fuer Anzeige
    const Bitmap&		GetOutBitmap() const;

    // DIB-Rueckgabe fuer Speicherung
    Bitmap				GetSaveBitmap();

    // Palette besorgen
    SimPalette*			GetOrgPalette() const { return nWhichOrg == 1 ? pPal1 : pPal2; }
    SimPalette*			GetDestPalette() const { return nWhichOrg == 1 ? pPal2 : pPal1; }
};

// ----------------
// - DitherBitmap -
// ----------------

BOOL DitherBitmap( Bitmap& rBitmap, BOOL bDitherAlways = FALSE );

}//end of namespace binfilter
#endif // _SVIMBASE_HXX
