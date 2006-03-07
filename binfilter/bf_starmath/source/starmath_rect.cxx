/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: starmath_rect.cxx,v $
 *
 *  $Revision: 1.8 $
 *
 *  last change: $Author: rt $ $Date: 2006-03-07 10:13:35 $
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

#pragma hdrstop

// auto strip #ifndef _STRING_HXX //autogen
// auto strip #include <tools/string.hxx>
// auto strip #endif
// auto strip #ifndef _TOOLS_DEBUG_HXX //autogen
// auto strip #include <tools/debug.hxx>
// auto strip #endif
#ifndef _SV_SVAPP_HXX //autogen
#include <vcl/svapp.hxx>
#endif
// auto strip #ifndef _SV_WRKWIN_HXX //autogen
// auto strip #include <vcl/wrkwin.hxx>
// auto strip #endif
#ifndef _SV_VIRDEV_HXX //autogen
#include <vcl/virdev.hxx>
#endif


#include "rect.hxx"
// auto strip #include "types.hxx"
// auto strip #include "utility.hxx"
#include "smmod.hxx"
namespace binfilter {


////////////////////////////////////////////////////////////////////////////////


// '\0' terminiertes Array mit Zeichen, die im StarMath Font als Buchstaben
// betrachtet werden sollen, (um im Gegensatz zu den anderen Operatoren
// und Symbolen ein "normales"(ungecliptes) SmRect zu erhalten).
static xub_Unicode __READONLY_DATA aMathAlpha[] =
{
    MS_ALEPH,               MS_IM,                  MS_RE,
    MS_WP,                  xub_Unicode(0xE070),    MS_EMPTYSET,
    xub_Unicode(0x2113),    xub_Unicode(0xE0D6),    xub_Unicode(0x2107),
    xub_Unicode(0x2127),    xub_Unicode(0x210A),    MS_HBAR,
    MS_LAMBDABAR,           MS_SETN,                MS_SETZ,
    MS_SETQ,                MS_SETR,                MS_SETC,
    xub_Unicode(0x2373),    xub_Unicode(0xE0A5),    xub_Unicode(0x2112),
    xub_Unicode(0x2130),    xub_Unicode(0x2131),
    xub_Unicode('\0')
};

/*N*/ BOOL SmIsMathAlpha(const XubString &rText)
/*N*/ 	// ergibt genau dann TRUE, wenn das Zeichen (aus dem StarMath Font) wie ein
/*N*/ 	// Buchstabe behandelt werden soll.
/*N*/ {
/*N*/ 	if (rText.Len() == 0)
/*N*/ 		return FALSE;
/*N*/
/*N*/   DBG_ASSERT(rText.Len() == 1, "Sm : String enthaelt nicht genau ein Zeichen");
/*N*/ 	xub_Unicode cChar = rText.GetChar(0);
/*N*/
/*N*/ 	// ist es ein griechisches Zeichen ?
/*N*/     if (xub_Unicode(0xE0AC) <= cChar  &&  cChar <= xub_Unicode(0xE0D4))
/*N*/ 		return TRUE;
/*N*/ 	else
/*N*/ 	{
/*N*/ 		// kommt es in 'aMathAlpha' vor ?
/*N*/ 		const xub_Unicode *pChar = aMathAlpha;
/*N*/ 		while (*pChar  &&  *pChar != cChar)
/*N*/ 			pChar++;
/*N*/ 		return *pChar != xub_Unicode('\0');
/*N*/ 	}
/*N*/ }


////////////////////////////////////////
//
// SmRect members
//


/*N*/ SmRect::SmRect()
/*N*/ 	// constructs empty rectangle at (0, 0) with width and height 0.
/*N*/ {
/*N*/ 	DBG_ASSERT(aTopLeft == Point(0, 0), "Sm: ooops...");
/*N*/ 	DBG_ASSERT(aSize == Size(0, 0), "Sm: ooops...");
/*N*/
/*N*/ 	bHasBaseline = bHasAlignInfo = FALSE;
/*N*/ 	nBaseline = nAlignT = nAlignM = nAlignB =
/*N*/ 	nGlyphTop = nGlyphBottom =
/*N*/ 	nItalicLeftSpace = nItalicRightSpace =
/*N*/ 	nLoAttrFence = nHiAttrFence = 0;
/*N*/   nBorderWidth = 0;
/*N*/ }


/*N*/ SmRect::SmRect(const SmRect &rRect)
/*N*/ :	aTopLeft(rRect.aTopLeft),
/*N*/ 	aSize(rRect.aSize)
/*N*/ {
/*N*/ 	bHasBaseline  = rRect.bHasBaseline;
/*N*/ 	nBaseline	  = rRect.nBaseline;
/*N*/ 	nAlignT		  = rRect.nAlignT;
/*N*/ 	nAlignM		  = rRect.nAlignM;
/*N*/ 	nAlignB		  = rRect.nAlignB;
/*N*/ 	nGlyphTop	  = rRect.nGlyphTop;
/*N*/ 	nGlyphBottom  = rRect.nGlyphBottom;
/*N*/ 	nHiAttrFence  = rRect.nHiAttrFence;
/*N*/ 	nLoAttrFence  = rRect.nLoAttrFence;
/*N*/ 	bHasAlignInfo = rRect.bHasAlignInfo;
/*N*/ 	nItalicLeftSpace  = rRect.nItalicLeftSpace;
/*N*/ 	nItalicRightSpace = rRect.nItalicRightSpace;
/*N*/     nBorderWidth  = rRect.nBorderWidth;
/*N*/ }


/*N*/ void SmRect::CopyAlignInfo(const SmRect &rRect)
/*N*/ {
/*N*/ 	nBaseline	  = rRect.nBaseline;
/*N*/ 	bHasBaseline  =	rRect.bHasBaseline;
/*N*/ 	nAlignT		  =	rRect.nAlignT;
/*N*/ 	nAlignM		  =	rRect.nAlignM;
/*N*/ 	nAlignB		  =	rRect.nAlignB;
/*N*/ 	bHasAlignInfo = rRect.bHasAlignInfo;
/*N*/ 	nLoAttrFence  =	rRect.nLoAttrFence;
/*N*/ 	nHiAttrFence  =	rRect.nHiAttrFence;
/*N*/ }


/*N*/ void SmRect::BuildRect(const OutputDevice &rDev, const SmFormat *pFormat,
/*N*/                        const XubString &rText, USHORT nBorder)
/*N*/ {
/*N*/ #ifndef PRODUCT
/*N*/ 	if (rDev.GetOutDevType() != OUTDEV_PRINTER)
/*N*/ 		DBG_WARNING("Sm :  Referenz-Device ist kein Drucker");
/*N*/ #endif
/*N*/
/*N*/ 	DBG_ASSERT(aTopLeft == Point(0, 0), "Sm: Ooops...");
/*N*/
/*N*/ 	aSize = Size(rDev.GetTextWidth(rText), rDev.GetTextHeight());
/*N*/
/*N*/ 	const FontMetric  aFM (rDev.GetFontMetric());
/*N*/     BOOL              bIsMath  = aFM.GetName().EqualsIgnoreCaseAscii( FONTNAME_MATH ) ||
/*N*/                                  aFM.GetName().EqualsIgnoreCaseAscii( FONTNAME_MATH2 );
/*N*/ 	BOOL			  bAllowSmaller = bIsMath && !SmIsMathAlpha(rText);
/*N*/ 	const long		  nFontHeight = rDev.GetFont().GetSize().Height();
/*N*/
/*N*/   nBorderWidth  = nBorder;
/*N*/ 	bHasAlignInfo = TRUE;
/*N*/ 	bHasBaseline  = TRUE;
/*N*/ 	nBaseline	  = aFM.GetAscent();
/*N*/ 	nAlignT		  = nBaseline - nFontHeight * 750L / 1000L;
/*N*/ 	nAlignM 	  = nBaseline - nFontHeight * 121L / 422L;
/*N*/ 		// that's where the horizontal bars of '+', '-', ... are
/*N*/ 		// (1/3 of ascent over baseline)
/*N*/ 		// (121 = 1/3 of 12pt ascent, 422 = 12pt fontheight)
/*N*/ 	nAlignB		  = nBaseline;
/*N*/
/*N*/ 	// workaround for printer fonts with very small (possible 0 or even
/*N*/ 	// negative(!)) leading
/*N*/ 	if (aFM.GetIntLeading() < 5  &&  rDev.GetOutDevType() == OUTDEV_PRINTER)
/*N*/ 	{
/*?*/ 		OutputDevice	*pWindow = Application::GetDefaultDevice();
/*?*/
/*?*/ 		pWindow->Push(PUSH_MAPMODE | PUSH_FONT);
/*?*/
/*?*/ 		pWindow->SetMapMode(rDev.GetMapMode());
/*?*/ 		pWindow->SetFont(rDev.GetFontMetric());
/*?*/
/*?*/ 		long  nDelta = pWindow->GetFontMetric().GetIntLeading();
/*?*/ 		if (nDelta == 0)
/*?*/ 		{ 	// dieser Wert entspricht etwa einem Leading von 80 bei einer
/*?*/           // Fonthoehe von 422 (12pt)
/*?*/ 			nDelta = nFontHeight * 8L / 43;
/*?*/ 		}
/*?*/ 		SetTop(GetTop() - nDelta);
/*?*/
/*?*/ 		pWindow->Pop();
/*N*/ 	}
/*N*/
/*N*/ 	// get GlyphBoundRect
/*N*/ 	Rectangle  aGlyphRect;
/*N*/ 	BOOL       bSuccess = SmGetGlyphBoundRect(rDev, rText, aGlyphRect);
/*N*/ 	DBG_ASSERT(bSuccess, "Sm : Ooops... (fehlt evtl. der Font?)");
/*N*/
/*N*/ 	nItalicLeftSpace  = GetLeft() - aGlyphRect.Left() + nBorderWidth;
/*N*/ 	nItalicRightSpace = aGlyphRect.Right() - GetRight() + nBorderWidth;
/*N*/ 	if (nItalicLeftSpace  < 0  &&  !bAllowSmaller)
/*N*/ 		nItalicLeftSpace  = 0;
/*N*/ 	if (nItalicRightSpace < 0  &&  !bAllowSmaller)
/*N*/ 		nItalicRightSpace = 0;
/*N*/
/*N*/ 	long  nDist = 0;
/*N*/ 	if (pFormat)
/*N*/ 		nDist = (rDev.GetFont().GetSize().Height()
/*N*/ 				* pFormat->GetDistance(DIS_ORNAMENTSIZE)) / 100L;
/*N*/
/*N*/ 	nHiAttrFence = aGlyphRect.TopLeft().Y() - 1 - nBorderWidth - nDist;
/*N*/ 	nLoAttrFence = SmFromTo(GetAlignB(), GetBottom(), 0.0);
/*N*/
/*N*/ 	nGlyphTop    = aGlyphRect.Top() - nBorderWidth;
/*N*/ 	nGlyphBottom = aGlyphRect.Bottom() + nBorderWidth;
/*N*/
/*N*/ 	if (bAllowSmaller)
/*N*/ 	{
/*N*/       // fuer Symbole und Operatoren aus dem StarMath Font passen wir den
/*N*/ 		// oberen und unteren Rand dem Zeichen an.
/*N*/ 		SetTop(nGlyphTop);
/*N*/ 		SetBottom(nGlyphBottom);
/*N*/ 	}
/*N*/
/*N*/ 	if (nHiAttrFence < GetTop())
/*N*/ 		nHiAttrFence = GetTop();
/*N*/
/*N*/ 	if (nLoAttrFence > GetBottom())
/*N*/ 		nLoAttrFence = GetBottom();
/*N*/
/*N*/ 	DBG_ASSERT(rText.Len() == 0  ||  !IsEmpty(),
/*N*/ 			   "Sm: leeres Rechteck erzeugt");
/*N*/ }


/*N*/ void SmRect::Init(const OutputDevice &rDev, const SmFormat *pFormat,
/*N*/                   const XubString &rText, USHORT nBorderWidth)
/*N*/ 	// get rectangle fitting for drawing 'rText' on OutputDevice 'rDev'
/*N*/ {
/*N*/ 	SmRectCache *pRectCache = SM_MOD1()->GetRectCache();
/*N*/ 	DBG_ASSERT(pRectCache, "Sm : NULL pointer");
/*N*/
/*N*/ 	// build key for rectangle (to look up in cache for)
/*N*/ 	const SmRectCache::Key  aKey (rText, rDev.GetFont());
/*N*/
/*N*/ 	const SmRect *pResult = pRectCache->Search(aKey);
/*N*/ 	if (pResult)
/*?*/ 		*this = *pResult;
/*N*/ 	else
/*N*/ 	{	// build rectangle and put it in cache
/*N*/ 		BuildRect(rDev, pFormat, rText, nBorderWidth);
/*N*/ 		pResult = pRectCache->Add(aKey, *this);
/*N*/ 	}
/*N*/ 	DBG_ASSERT(pResult, "Sm : NULL pointer");
/*N*/ }


/*N*/ SmRect::SmRect(const OutputDevice &rDev, const SmFormat *pFormat,
/*N*/                const XubString &rText, long nBorderWidth)
/*N*/ {
/*N*/     DBG_ASSERT( nBorderWidth >= 0, "BorderWidth negativ" );
/*N*/     if (nBorderWidth < 0)
/*N*/         nBorderWidth = 0;
/*N*/     Init(rDev, pFormat, rText, (USHORT) nBorderWidth);
/*N*/ }


/*N*/ SmRect::SmRect(long nWidth, long nHeight)
/*N*/ 	// this constructor should never be used for anything textlike because
/*N*/ 	// it will not provide useful values for baseline, AlignT and AlignB!
/*N*/ 	// It's purpose is to get a 'SmRect' for the horizontal line in fractions
/*N*/ 	// as used in 'SmBinVerNode'.
/*N*/ :	aSize(nWidth, nHeight)
/*N*/ {
/*N*/ 	DBG_ASSERT(aTopLeft == Point(0, 0), "Sm: ooops...");
/*N*/
/*N*/ 	bHasBaseline  = FALSE;
/*N*/ 	bHasAlignInfo = TRUE;
/*N*/ 	nBaseline	  = 0;
/*N*/ 	nAlignT		  = GetTop();
/*N*/ 	nAlignB		  = GetBottom();
/*N*/ 	nAlignM		  = (nAlignT + nAlignB) / 2;		// this is the default
/*N*/ 	nItalicLeftSpace = nItalicRightSpace = 0;
/*N*/ 	nGlyphTop    = nHiAttrFence  = GetTop();
/*N*/ 	nGlyphBottom = nLoAttrFence  = GetBottom();
/*N*/     nBorderWidth  = 0;
/*N*/ }


/*N*/ void SmRect::SetLeft(long nLeft)
/*N*/ {
/*N*/ 	if (nLeft <= GetRight())
/*N*/ 	{	aSize.Width() = GetRight() - nLeft + 1;
/*N*/ 		aTopLeft.X()  = nLeft;
/*N*/ 	}
/*N*/ }


/*N*/ void SmRect::SetRight(long nRight)
/*N*/ {
/*N*/ 	if (nRight >= GetLeft())
/*N*/ 		aSize.Width() = nRight - GetLeft() + 1;
/*N*/ }


/*N*/ void SmRect::SetBottom(long nBottom)
/*N*/ {
/*N*/ 	if (nBottom >= GetTop())
/*N*/ 		aSize.Height() = nBottom - GetTop() + 1;
/*N*/ }


/*N*/ void SmRect::SetTop(long nTop)
/*N*/ {
/*N*/ 	if (nTop <= GetBottom())
/*N*/ 	{	aSize.Height()	 = GetBottom() - nTop + 1;
/*N*/ 		aTopLeft.Y() = nTop;
/*N*/ 	}
/*N*/ }


/*N*/ void SmRect::Move(const Point &rPosition)
/*N*/ 	// move rectangle by position 'rPosition'.
/*N*/ {
/*N*/ 	aTopLeft  += rPosition;
/*N*/
/*N*/ 	long  nDelta = rPosition.Y();
/*N*/ 	nBaseline += nDelta;
/*N*/ 	nAlignT   += nDelta;
/*N*/ 	nAlignM	  += nDelta;
/*N*/ 	nAlignB   += nDelta;
/*N*/ 	nGlyphTop    += nDelta;
/*N*/ 	nGlyphBottom += nDelta;
/*N*/ 	nHiAttrFence += nDelta;
/*N*/ 	nLoAttrFence += nDelta;
/*N*/ }


/*N*/ const Point SmRect::AlignTo(const SmRect &rRect, RectPos ePos,
/*N*/ 							RectHorAlign eHor, RectVerAlign eVer) const
/*N*/ {	Point  aPos (GetTopLeft());
/*N*/ 		// will become the topleft point of the new rectangle position
/*N*/
/*N*/ 	// set horizontal or vertical new rectangle position depending on
/*N*/ 	// 'ePos' is one of 'RP_LEFT', 'RP_RIGHT' or 'RP_TOP', 'RP_BOTTOM'
/*N*/ 	switch (ePos)
/*N*/ 	{	case RP_LEFT :
/*N*/ 			aPos.X() = rRect.GetItalicLeft() - GetItalicRightSpace()
/*N*/ 					   - GetWidth();
/*N*/ 			break;
/*N*/ 		case RP_RIGHT :
/*N*/ 			aPos.X() = rRect.GetItalicRight() + 1 + GetItalicLeftSpace();
/*N*/ 			break;
/*N*/ 		case RP_TOP :
/*N*/ 			aPos.Y() = rRect.GetTop() - GetHeight();
/*N*/ 			break;
/*N*/ 		case RP_BOTTOM :
/*N*/ 			aPos.Y() = rRect.GetBottom() + 1;
/*N*/ 			break;
/*N*/ 		case RP_ATTRIBUT :
/*N*/ 			aPos.X() = rRect.GetItalicCenterX() - GetItalicWidth() / 2
/*N*/ 					   + GetItalicLeftSpace();
/*N*/ 			break;
/*N*/ 		default :
/*N*/ 			DBG_ASSERT(FALSE, "Sm: unbekannter Fall");
/*N*/ 	}
/*N*/
/*N*/ 	// check if horizontal position is already set
/*N*/ 	if (ePos == RP_LEFT  ||  ePos == RP_RIGHT  ||  ePos == RP_ATTRIBUT)
/*N*/ 		// correct error in current vertical position
/*N*/ 		switch (eVer)
/*N*/ 		{	case RVA_TOP :
/*N*/ 				aPos.Y() += rRect.GetAlignT() - GetAlignT();
/*N*/ 				break;
/*N*/ 			case RVA_MID :
/*N*/ 				aPos.Y() += rRect.GetAlignM() - GetAlignM();
/*N*/ 				break;
/*N*/ 			case RVA_BASELINE :
/*N*/ 				// align baselines if possible else align mid's
/*N*/ 				if (HasBaseline() && rRect.HasBaseline())
/*N*/ 					aPos.Y() += rRect.GetBaseline() - GetBaseline();
/*N*/ 				else
/*N*/ 					aPos.Y() += rRect.GetAlignM() - GetAlignM();
/*N*/ 				break;
/*N*/ 			case RVA_BOTTOM :
/*N*/ 				aPos.Y() += rRect.GetAlignB() - GetAlignB();
/*N*/ 				break;
/*N*/ 			case RVA_CENTERY :
/*N*/ 				aPos.Y() += rRect.GetCenterY() - GetCenterY();
/*N*/ 				break;
/*N*/ 			case RVA_ATTRIBUT_HI:
/*N*/ 				aPos.Y() += rRect.GetHiAttrFence() - GetBottom();
/*N*/ 				break;
/*N*/ 			case RVA_ATTRIBUT_MID :
/*?*/ 				aPos.Y() += SmFromTo(rRect.GetAlignB(), rRect.GetAlignT(), 0.4)
/*?*/ 							- GetCenterY();
/*?*/ 				break;
/*?*/ 			case RVA_ATTRIBUT_LO :
/*?*/ 				aPos.Y() += rRect.GetLoAttrFence() - GetTop();
/*?*/ 				break;
/*?*/ 		default :
/*N*/ 				DBG_ASSERT(FALSE, "Sm: unbekannter Fall");
/*N*/ 		}
/*N*/
/*N*/ 	// check if vertical position is already set
/*N*/ 	if (ePos == RP_TOP	||	ePos == RP_BOTTOM)
/*N*/ 		// correct error in current horizontal position
/*N*/ 		switch (eHor)
/*N*/ 		{	case RHA_LEFT :
/*N*/ 				aPos.X() += rRect.GetItalicLeft() - GetItalicLeft();
/*N*/ 				break;
/*N*/ 			case RHA_CENTER :
/*N*/ 				aPos.X() += rRect.GetItalicCenterX() - GetItalicCenterX();
/*N*/ 				break;
/*N*/ 			case RHA_RIGHT :
/*?*/ 				aPos.X() += rRect.GetItalicRight() - GetItalicRight();
/*?*/ 				break;
/*N*/ 			default :
/*N*/ 				DBG_ASSERT(FALSE, "Sm: unbekannter Fall");
/*N*/ 		}
/*N*/
/*N*/ 	return aPos;
/*N*/ }


/*N*/ SmRect & SmRect::Union(const SmRect &rRect)
/*N*/ 	// rectangle union of current one with 'rRect'. The result is to be the
/*N*/ 	// smallest rectangles that covers the space of both rectangles.
/*N*/ 	// (empty rectangles cover no space)
/*N*/ 	//! Italic correction is NOT taken into account here!
/*N*/ {
/*N*/ 	if (rRect.IsEmpty())
/*N*/ 		return *this;
/*N*/
/*N*/ 	long  nL  = rRect.GetLeft(),
/*N*/ 		  nR  = rRect.GetRight(),
/*N*/ 		  nT  = rRect.GetTop(),
/*N*/ 		  nB  = rRect.GetBottom(),
/*N*/ 		  nGT = rRect.nGlyphTop,
/*N*/ 		  nGB = rRect.nGlyphBottom;
/*N*/ 	if (!IsEmpty())
/*N*/ 	{	long  nTmp;
/*N*/
/*N*/ 		if ((nTmp = GetLeft()) < nL)
/*N*/ 			nL = nTmp;
/*N*/ 		if ((nTmp = GetRight()) > nR)
/*N*/ 			nR = nTmp;
/*N*/ 		if ((nTmp = GetTop()) < nT)
/*N*/ 			nT = nTmp;
/*N*/ 		if ((nTmp = GetBottom()) > nB)
/*N*/ 			nB = nTmp;
/*N*/ 		if ((nTmp = nGlyphTop) < nGT)
/*N*/ 			nGT = nTmp;
/*N*/ 		if ((nTmp = nGlyphBottom) > nGB)
/*N*/ 			nGB = nTmp;
/*N*/ 	}
/*N*/
/*N*/ 	SetLeft(nL);
/*N*/ 	SetRight(nR);
/*N*/ 	SetTop(nT);
/*N*/ 	SetBottom(nB);
/*N*/ 	nGlyphTop    = nGT;
/*N*/ 	nGlyphBottom = nGB;
/*N*/
/*N*/ 	return *this;
/*N*/ }


/*N*/ SmRect & SmRect::ExtendBy(const SmRect &rRect, RectCopyMBL eCopyMode)
/*N*/ 	// let current rectangle be the union of itself and 'rRect'
/*N*/ 	// (the smallest rectangle surrounding both). Also adapt values for
/*N*/ 	// 'AlignT', 'AlignM', 'AlignB', baseline and italic-spaces.
/*N*/ 	// The baseline is set according to 'eCopyMode'.
/*N*/ 	// If one of the rectangles has no relevant info the other one is copied.
/*N*/ {
/*N*/ 	// get some values used for (italic) spaces adaption
/*N*/ 	// ! (need to be done before changing current SmRect) !
/*N*/ 	long  nL = Min(GetItalicLeft(),  rRect.GetItalicLeft()),
/*N*/ 		  nR = Max(GetItalicRight(), rRect.GetItalicRight());
/*N*/
/*N*/ 	Union(rRect);
/*N*/
/*N*/ 	SetItalicSpaces(GetLeft() - nL, nR - GetRight());
/*N*/
/*N*/ 	if (!HasAlignInfo())
/*N*/ 		CopyAlignInfo(rRect);
/*N*/ 	else if (rRect.HasAlignInfo())
/*N*/ 	{	nAlignT = Min(GetAlignT(), rRect.GetAlignT());
/*N*/ 		nAlignB = Max(GetAlignB(), rRect.GetAlignB());
/*N*/ 		nHiAttrFence = Min(GetHiAttrFence(), rRect.GetHiAttrFence());
/*N*/ 		nLoAttrFence = Max(GetLoAttrFence(), rRect.GetLoAttrFence());
/*N*/ 		DBG_ASSERT(HasAlignInfo(), "Sm: ooops...");
/*N*/
/*N*/ 		switch (eCopyMode)
/*N*/ 		{	case RCP_THIS:
/*N*/ 				// already done
/*N*/ 				break;
/*N*/ 			case RCP_ARG:
/*N*/ 				CopyMBL(rRect);
/*N*/ 				break;
/*N*/ 			case RCP_NONE:
/*N*/ 				ClearBaseline();
/*N*/ 				nAlignM = (nAlignT + nAlignB) / 2;
/*N*/ 				break;
/*N*/ 			case RCP_XOR:
/*N*/ 				if (!HasBaseline())
/*N*/ 					CopyMBL(rRect);
/*N*/ 				break;
/*N*/ 			default :
/*N*/ 				DBG_ASSERT(FALSE, "Sm: unbekannter Fall");
/*N*/ 		}
/*N*/ 	}
/*N*/
/*N*/ 	return *this;
/*N*/ }


/*N*/ SmRect & SmRect::ExtendBy(const SmRect &rRect, RectCopyMBL eCopyMode,
/*N*/ 						  long nNewAlignM)
/*N*/ 	// as 'ExtendBy' but sets AlignM value to 'nNewAlignM'.
/*N*/ 	// (this version will be used in 'SmBinVerNode' to provide means to
/*N*/ 	// align eg "{a over b} over c" correctly where AlignM should not
/*N*/ 	// be (AlignT + AlignB) / 2)
/*N*/ {
/*N*/ 	DBG_ASSERT(HasAlignInfo(), "Sm: keine Align Info");
/*N*/
/*N*/ 	ExtendBy(rRect, eCopyMode);
/*N*/ 	nAlignM = nNewAlignM;
/*N*/
/*N*/ 	return *this;
/*N*/ }


/*N*/ SmRect & SmRect::ExtendBy(const SmRect &rRect, RectCopyMBL eCopyMode,
/*N*/ 						  BOOL bKeepVerAlignParams)
/*N*/ 	// as 'ExtendBy' but keeps original values for AlignT, -M and -B and
/*N*/ 	// baseline.
/*N*/ 	// (this is used in 'SmSupSubNode' where the sub-/supscripts shouldn't
/*N*/ 	// be allowed to modify these values.)
/*N*/ {
/*N*/ 	long  nOldAlignT   = GetAlignT(),
/*N*/ 		  nOldAlignM   = GetAlignM(),
/*N*/ 		  nOldAlignB   = GetAlignB(),
/*N*/ 		  nOldBaseline = nBaseline;		//! depends not on 'HasBaseline'
/*N*/ 	BOOL  bOldHasAlignInfo = HasAlignInfo();
/*N*/
/*N*/ 	ExtendBy(rRect, eCopyMode);
/*N*/
/*N*/ 	if (bKeepVerAlignParams)
/*N*/ 	{	nAlignT	  = nOldAlignT;
/*N*/ 		nAlignM	  = nOldAlignM;
/*N*/ 		nAlignB	  = nOldAlignB;
/*N*/ 		nBaseline = nOldBaseline;
/*N*/ 		bHasAlignInfo = bOldHasAlignInfo;
/*N*/ 	}
/*N*/
/*N*/ 	return *this;
/*N*/ }


//SmRect & SmRect::ExtendBy(const Point &rPoint)
//    // extend current rectangle to include 'rPoint'.
//    // The effect should be similar to
//    //      "ExtendBy(rRect, RCP_THIS, (BOOL) TRUE)"
//    // where 'rRect' is a SmRect of size and width 1 with no italic spaces
//    // (as by "SmRect (1, 1)") and position at 'rPoint'.
//{
//    // get some values used for italic spaces adaption
//    // ! (need to be done before changing current SmRect) !
//    long  nL = Min(GetItalicLeft(),  rPoint.X()),
//          nR = Max(GetItalicRight(), rPoint.X());
//
//    // this is the adaption of rectangle union
//    if (rPoint.X() < GetLeft())
//        SetLeft(rPoint.X());
//    if (rPoint.X() > GetRight())
//        SetRight(rPoint.X());
//    if (rPoint.Y() < GetTop())
//        SetTop(rPoint.Y());
//    if (rPoint.Y() > GetBottom())
//        SetBottom(rPoint.Y());
//
//    SetItalicSpaces(GetLeft() - nL, nR - GetRight());
//
//    return *this;
//}


//long SmRect::OrientedDist(const Point &rPoint) const
//    // return oriented distance of rPoint to the current rectangle,
//    // especially the return value is <= 0 iff the point is inside the
//    // rectangle.
//    // For simplicity the maximum-norm is used.
//{
//    BOOL  bIsInside = IsInsideItalicRect(rPoint);
//
//    // build reference point to define the distance
//    Point  aRef;
//    if (bIsInside)
//    {   Point  aIC (GetItalicCenterX(), GetCenterY());
//
//        aRef.X() = rPoint.X() >= aIC.X() ? GetItalicRight() : GetItalicLeft();
//        aRef.Y() = rPoint.Y() >= aIC.Y() ? GetBottom() : GetTop();
//    }
//    else
//    {
//        // x-coordinate
//        if (rPoint.X() > GetItalicRight())
//            aRef.X() = GetItalicRight();
//        else if (rPoint.X() < GetItalicLeft())
//            aRef.X() = GetItalicLeft();
//        else
//            aRef.X() = rPoint.X();
//        // y-coordinate
//        if (rPoint.Y() > GetBottom())
//            aRef.Y() = GetBottom();
//        else if (rPoint.Y() < GetTop())
//            aRef.Y() = GetTop();
//        else
//            aRef.Y() = rPoint.Y();
//    }
//
//    // build distance vector
//    Point  aDist (aRef - rPoint);
//
//    long nAbsX = labs(aDist.X()),
//         nAbsY = labs(aDist.Y());
//
//    return bIsInside ? - Min(nAbsX, nAbsY) : Max (nAbsX, nAbsY);
//}


//BOOL SmRect::IsInsideRect(const Point &rPoint) const
//{
//    return     rPoint.Y() >= GetTop()
//           &&  rPoint.Y() <= GetBottom()
//           &&  rPoint.X() >= GetLeft()
//           &&  rPoint.X() <= GetRight();
//}


//BOOL SmRect::IsInsideItalicRect(const Point &rPoint) const
//{
//    return     rPoint.Y() >= GetTop()
//           &&  rPoint.Y() <= GetBottom()
//           &&  rPoint.X() >= GetItalicLeft()
//           &&  rPoint.X() <= GetItalicRight();
//}

SmRect SmRect::AsGlyphRect() const
{
    SmRect aRect (*this);
    aRect.SetTop(nGlyphTop);
    aRect.SetBottom(nGlyphBottom);
    return aRect;
}


// forward declaration
//STRIP001 void SmDrawFrame(OutputDevice &rDev, const Rectangle &rRec,
//STRIP001 				 const Color aCol = COL_BLACK);

//STRIP001 void SmRect::Draw(OutputDevice &rDev, const Point &rPosition, int nFlags) const
//STRIP001 {
//STRIP001 	if (IsEmpty())
//STRIP001 		return;
//STRIP001
//STRIP001 	rDev.Push(PUSH_LINECOLOR);
//STRIP001
//STRIP001 	if (nFlags & SM_RECT_LINES)
//STRIP001 	{	long   nLeftSpace  = 0,
//STRIP001 			   nRightSpace = 0;
//STRIP001
//STRIP001 		if (nFlags & SM_RECT_ITALIC)
//STRIP001 		{	nLeftSpace	= GetItalicLeftSpace();
//STRIP001 			nRightSpace = GetItalicRightSpace();
//STRIP001 		}
//STRIP001
//STRIP001 		long  nLeft  = GetLeft()  - nLeftSpace,
//STRIP001 			  nRight = GetRight() + nRightSpace;
//STRIP001
//STRIP001 		Point aOffset (rPosition - GetTopLeft());
//STRIP001
//STRIP001 		rDev.SetLineColor(COL_LIGHTBLUE);
//STRIP001 		rDev.DrawLine(Point(nLeft,	GetAlignB()) += aOffset,
//STRIP001 					  Point(nRight, GetAlignB()) += aOffset);
//STRIP001 		rDev.DrawLine(Point(nLeft,	GetAlignT()) += aOffset,
//STRIP001 					  Point(nRight, GetAlignT()) += aOffset);
//STRIP001 		if (HasBaseline())
//STRIP001 			rDev.DrawLine(Point(nLeft,	GetBaseline()) += aOffset,
//STRIP001 						  Point(nRight, GetBaseline()) += aOffset);
//STRIP001
//STRIP001 		rDev.SetLineColor(COL_GRAY);
//STRIP001 		rDev.DrawLine(Point(nLeft,	GetHiAttrFence()) += aOffset,
//STRIP001 					  Point(nRight, GetHiAttrFence()) += aOffset);
//STRIP001 	}
//STRIP001
//STRIP001 	if (nFlags & SM_RECT_MID)
//STRIP001 	{	Point	aCenter = rPosition
//STRIP001 						  + (Point(GetItalicCenterX(), GetAlignM()) -= GetTopLeft()),
//STRIP001 				aLenX	  (GetWidth() / 5, 0),
//STRIP001 				aLenY	  (0, GetHeight() / 16);
//STRIP001
//STRIP001 		rDev.SetLineColor(COL_LIGHTGREEN);
//STRIP001 		rDev.DrawLine(aCenter - aLenX, aCenter + aLenX);
//STRIP001 		rDev.DrawLine(aCenter - aLenY, aCenter + aLenY);
//STRIP001 	}
//STRIP001
//STRIP001 	if (nFlags & SM_RECT_ITALIC)
//STRIP001 		SmDrawFrame(rDev, Rectangle(rPosition - Point(GetItalicLeftSpace(), 0),
//STRIP001 				GetItalicSize()));
//STRIP001
//STRIP001 	if (nFlags & SM_RECT_CORE)
//STRIP001 		SmDrawFrame(rDev, Rectangle(rPosition, GetSize()), COL_LIGHTRED);
//STRIP001
//STRIP001 	rDev.Pop();
//STRIP001 }



////////////////////////////////////////
// misc functions
//


//STRIP001 void SmDrawFrame(OutputDevice &rDev, const Rectangle &rRec,
//STRIP001 				 const Color aCol)
//STRIP001 {
//STRIP001 	rDev.Push(PUSH_LINECOLOR);
//STRIP001
//STRIP001 	rDev.SetLineColor(aCol);
//STRIP001
//STRIP001 	rDev.DrawLine(rRec.TopLeft(),	  rRec.BottomLeft());
//STRIP001 	rDev.DrawLine(rRec.BottomLeft(),  rRec.BottomRight());
//STRIP001 	rDev.DrawLine(rRec.BottomRight(), rRec.TopRight());
//STRIP001 	rDev.DrawLine(rRec.TopRight(),	  rRec.TopLeft());
//STRIP001
//STRIP001 	rDev.Pop();
//STRIP001 }


/*N*/ BOOL SmGetGlyphBoundRect(const OutputDevice &rDev,
/*N*/ 						 const XubString &rText, Rectangle &rRect)
/*N*/     // basically the same as 'GetTextBoundRect' (in class 'OutputDevice')
/*N*/ 	// but with a string as argument.
/*N*/ {
/*N*/ 	// handle special case first
/*N*/ 	xub_StrLen nLen = rText.Len();
/*N*/ 	if (nLen == 0)
/*N*/ 	{	rRect.SetEmpty();
/*N*/ 		return TRUE;
/*N*/ 	}
/*N*/
/*N*/     // get a device where 'OutputDevice::GetTextBoundRect' will be successful
/*N*/ 	OutputDevice *pGlyphDev;
/*N*/ 	if (rDev.GetOutDevType() != OUTDEV_PRINTER)
/*?*/ 		pGlyphDev = (OutputDevice *) &rDev;
/*N*/ 	else
/*N*/ 	{
/*N*/         // since we format for the printer (where GetTextBoundRect will fail)
/*N*/ 		// we need a virtual device here.
/*N*/ 		pGlyphDev = SM_MOD1()->GetRectCache()->GetVirDev();
/*N*/ 	}
/*N*/
/*N*/ 	const FontMetric  aDevFM (rDev.GetFontMetric());
/*N*/
/*N*/     pGlyphDev->Push(PUSH_FONT | PUSH_MAPMODE);
/*N*/     Font aFnt(rDev.GetFont());
/*N*/     aFnt.SetAlign(ALIGN_TOP);
/*N*/
/*N*/     // use scale factor when calling GetTextBoundRect to counter
/*N*/     // negative effects from antialiasing which may otherwise result
/*N*/     // in significant incorrect bounding rectangles for some charcters.
/*N*/     long nScaleFactor = 16;
/*N*/ 	Size aFntSize = aFnt.GetSize();
/*N*/     aFnt.SetSize( Size( aFntSize.Width() * nScaleFactor, aFntSize.Height() * nScaleFactor ) );
/*N*/     pGlyphDev->SetFont(aFnt);
/*N*/
/*N*/     long nTextWidth = rDev.GetTextWidth(rText);
/*N*/     Point aPoint;
/*N*/     Rectangle   aResult (aPoint, Size(nTextWidth, rDev.GetTextHeight())),
/*N*/ 				aTmp;
/*N*/
/*N*/     BOOL bSuccess = pGlyphDev->GetTextBoundRect(aTmp, rText, 0, 0);
/*N*/     DBG_ASSERT( bSuccess, "GetTextBoundRect failed" );
/*N*/
/*N*/
/*N*/     if (!aTmp.IsEmpty())
/*N*/     {
/*N*/         aResult = Rectangle(aTmp.Left() / nScaleFactor, aTmp.Top() / nScaleFactor,
/*N*/                             aTmp.Right() / nScaleFactor, aTmp.Bottom() / nScaleFactor);
/*N*/         if (&rDev != pGlyphDev) /* only when rDev is a printer... */
/*N*/         {
/*N*/             long nGDTextWidth  = pGlyphDev->GetTextWidth(rText);
/*N*/             if (nGDTextWidth != 0  &&
/*N*/                 nTextWidth != nGDTextWidth)
/*N*/             {
/*N*/                 aResult.Right() *= nTextWidth;
/*N*/                 aResult.Right() /= nGDTextWidth / nScaleFactor;
/*N*/             }
/*N*/         }
/*N*/     }
/*N*/
/*N*/ 	// move rectangle to match possibly different baselines
/*N*/ 	// (because of different devices)
/*N*/     long nDelta = aDevFM.GetAscent() - pGlyphDev->GetFontMetric().GetAscent() / nScaleFactor;
/*N*/ 	aResult.Move(0, nDelta);
/*N*/
/*N*/ 	pGlyphDev->Pop();
/*N*/
/*N*/     rRect = aResult;
/*N*/ 	return bSuccess;
/*N*/ }


}
