/*************************************************************************
 *
 *  $RCSfile: sw_txtfrm.cxx,v $
 *
 *  $Revision: 1.3 $
 *
 *  last change: $Author: rt $ $Date: 2004-05-05 16:41:08 $
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


#pragma hdrstop

#ifndef _HINTIDS_HXX
#include <hintids.hxx>
#endif

#ifndef _SFX_PRINTER_HXX //autogen
#include <bf_sfx2/printer.hxx>
#endif
#ifndef _SFX_SFXUNO_HXX
#include <bf_sfx2/sfxuno.hxx>
#endif
#ifndef _SVX_LANGITEM_HXX //autogen
#include <bf_svx/langitem.hxx>
#endif
#ifndef _SVX_LSPCITEM_HXX //autogen
#include <bf_svx/lspcitem.hxx>
#endif
#ifndef _SVX_LRSPITEM_HXX //autogen
#include <bf_svx/lrspitem.hxx>
#endif
#ifndef _SVX_ULSPITEM_HXX //autogen
#include <bf_svx/ulspitem.hxx>
#endif
#ifndef _SVX_BRSHITEM_HXX //autogen
#include <bf_svx/brshitem.hxx>
#endif
#ifndef _SVX_PGRDITEM_HXX
#include <bf_svx/pgrditem.hxx>
#endif

#ifndef _DOC_HXX
#include <doc.hxx>		// GetDoc()
#endif
#ifndef _PAGEFRM_HXX
#include <pagefrm.hxx>	// InvalidateSpelling
#endif
#ifndef _VIEWSH_HXX
#include <viewsh.hxx>	// ViewShell
#endif
#ifndef _PAM_HXX
#include <pam.hxx>		// SwPosition
#endif
#ifndef _NDTXT_HXX
#include <ndtxt.hxx>		// SwTxtNode
#endif
#ifndef _TXTATR_HXX
#include <txtatr.hxx>
#endif
#ifndef _PARATR_HXX
#include <paratr.hxx>
#endif
#ifndef _HINTS_HXX
#include <hints.hxx>		// SwInsChr
#endif
#ifndef _VIEWOPT_HXX
#include <viewopt.hxx>
#endif
#ifndef _DFLYOBJ_HXX
#include <dflyobj.hxx>
#endif
#ifndef _FLYFRM_HXX
#include <flyfrm.hxx>
#endif
#ifndef _TABFRM_HXX
#include <tabfrm.hxx>
#endif
#ifndef _FRMTOOL_HXX
#include <frmtool.hxx>
#endif
#ifndef _PAGEDESC_HXX
#include <pagedesc.hxx> // SwPageDesc
#endif
#ifndef SW_TGRDITEM_HXX
#include <tgrditem.hxx>
#endif
#ifndef _DBG_LAY_HXX
#include <dbg_lay.hxx>
#endif
#ifndef _FMTFLD_HXX //autogen
#include <fmtfld.hxx>
#endif
#ifndef _FMTFTN_HXX //autogen
#include <fmtftn.hxx>
#endif
#ifndef _TXTFLD_HXX //autogen
#include <txtfld.hxx>
#endif
#ifndef _TXTFTN_HXX //autogen
#include <txtftn.hxx>
#endif
#ifndef _FRMATR_HXX
#include <frmatr.hxx>
#endif
#ifndef _CHARATR_HXX
#include <charatr.hxx>
#endif
#ifndef _FTNINFO_HXX //autogen
#include <ftninfo.hxx>
#endif
#ifndef _FMTLINE_HXX
#include <fmtline.hxx>
#endif
#ifndef _TXTFRM_HXX
#include <txtfrm.hxx>		// SwTxtFrm
#endif
#ifndef _SECTFRM_HXX
#include <sectfrm.hxx>		// SwSectFrm
#endif
#ifndef _TXTCFG_HXX
#include <txtcfg.hxx>		// DBG_LOOP
#endif
#ifndef _ITRFORM2_HXX
#include <itrform2.hxx> 	  // Iteratoren
#endif
#ifndef _WIDORP_HXX
#include <widorp.hxx>		// SwFrmBreak
#endif
#ifndef _TXTCACHE_HXX
#include <txtcache.hxx>
#endif
#ifndef _SWFONT_HXX
#include <swfont.hxx>       // GetLineSpace benutzt SwFonts
#endif
#ifndef _FNTCACHE_HXX
#include <fntcache.hxx>     // GetLineSpace benutzt pLastFont
#endif
#ifndef _FRMSH_HXX
#include <frmsh.hxx>
#endif
#ifndef _WRONG_HXX
#include <wrong.hxx>		// SwWrongList
#endif
#ifndef _LINEINFO_HXX
#include <lineinfo.hxx>
#endif
#ifndef _SW_PORTIONHANDLER_HXX
#include <SwPortionHandler.hxx>
#endif

#if OSL_DEBUG_LEVEL > 1
#ifndef _TXTPAINT_HXX
#include <txtpaint.hxx> 	// DbgRect
#endif
namespace binfilter {
extern const sal_Char *GetPrepName( const enum PrepareHint ePrep );
} //STRIP008
#endif
namespace binfilter {
/*N*/ TYPEINIT1( SwTxtFrm, SwCntntFrm );

// Switches width and height of the text frame
/*N*/ void SwTxtFrm::SwapWidthAndHeight()
/*N*/ {
/*N*/     if ( ! bIsSwapped )
/*N*/     {
/*N*/         const long nPrtOfstX = Prt().Pos().X();
/*N*/         Prt().Pos().X() = Prt().Pos().Y();
/*N*/         Prt().Pos().Y() = Frm().Width() - ( nPrtOfstX + Prt().Width() );
/*N*/     }
/*N*/     else
/*N*/     {
/*N*/         const long nPrtOfstY = Prt().Pos().Y();
/*N*/         Prt().Pos().Y() = Prt().Pos().X();
/*N*/         Prt().Pos().X() = Frm().Height() - ( nPrtOfstY + Prt().Height() );
/*N*/     }
/*N*/ 
/*N*/     const long nFrmWidth = Frm().Width();
/*N*/     Frm().Width( Frm().Height() );
/*N*/     Frm().Height( nFrmWidth );
/*N*/     const long nPrtWidth = Prt().Width();
/*N*/     Prt().Width( Prt().Height() );
/*N*/     Prt().Height( nPrtWidth );
/*N*/ 
/*N*/     bIsSwapped = ! bIsSwapped;
/*N*/ }

// Calculates the coordinates of a rectangle when switching from
// horizontal to vertical layout.
//STRIP001 void SwTxtFrm::SwitchHorizontalToVertical( SwRect& rRect ) const
//STRIP001 {
//STRIP001     // calc offset inside frame
//STRIP001     const long nOfstX = rRect.Left() - Frm().Left();
//STRIP001     const long nOfstY = rRect.Top() + rRect.Height() - Frm().Top();
//STRIP001     const long nWidth = rRect.Width();
//STRIP001     const long nHeight = rRect.Height();
//STRIP001 
//STRIP001     if ( bIsSwapped )
//STRIP001         rRect.Left( Frm().Left() + Frm().Height() - nOfstY );
//STRIP001     else
//STRIP001         // frame is rotated
//STRIP001         rRect.Left( Frm().Left() + Frm().Width() - nOfstY );
//STRIP001 
//STRIP001     rRect.Top( Frm().Top() + nOfstX );
//STRIP001     rRect.Width( nHeight );
//STRIP001     rRect.Height( nWidth );
//STRIP001 }

// Calculates the coordinates of a point when switching from
// horizontal to vertical layout.
//STRIP001 void SwTxtFrm::SwitchHorizontalToVertical( Point& rPoint ) const
//STRIP001 {
//STRIP001     // calc offset inside frame
//STRIP001     const long nOfstX = rPoint.X() - Frm().Left();
//STRIP001     const long nOfstY = rPoint.Y() - Frm().Top();
//STRIP001 
//STRIP001     if ( bIsSwapped )
//STRIP001         rPoint.X() = Frm().Left() + Frm().Height() - nOfstY;
//STRIP001     else
//STRIP001         // calc rotated coords
//STRIP001         rPoint.X() = Frm().Left() + Frm().Width() - nOfstY;
//STRIP001 
//STRIP001     rPoint.Y() = Frm().Top() + nOfstX;
//STRIP001 }

// Calculates the a limit value when switching from
// horizontal to vertical layout.
//STRIP001 long SwTxtFrm::SwitchHorizontalToVertical( long nLimit ) const
//STRIP001 {
//STRIP001     Point aTmp( 0, nLimit );
//STRIP001     SwitchHorizontalToVertical( aTmp );
//STRIP001     return aTmp.X();
//STRIP001 }

// Calculates the coordinates of a rectangle when switching from
// vertical to horizontal layout.
/*N*/ void SwTxtFrm::SwitchVerticalToHorizontal( SwRect& rRect ) const
/*N*/ {
/*N*/     long nOfstX;
/*N*/ 
/*N*/     // calc offset inside frame
/*N*/     if ( bIsSwapped )
/*N*/         nOfstX = Frm().Left() + Frm().Height() - ( rRect.Left() + rRect.Width() );
/*N*/     else
/*N*/         nOfstX = Frm().Left() + Frm().Width() - ( rRect.Left() + rRect.Width() );
/*N*/ 
/*N*/     const long nOfstY = rRect.Top() - Frm().Top();
/*N*/     const long nWidth = rRect.Height();
/*N*/     const long nHeight = rRect.Width();
/*N*/ 
/*N*/     // calc rotated coords
/*N*/     rRect.Left( Frm().Left() + nOfstY );
/*N*/     rRect.Top( Frm().Top() + nOfstX );
/*N*/     rRect.Width( nWidth );
/*N*/     rRect.Height( nHeight );
/*N*/ }

// Calculates the coordinates of a point when switching from
// vertical to horizontal layout.
/*N*/ void SwTxtFrm::SwitchVerticalToHorizontal( Point& rPoint ) const
/*N*/ {
/*N*/     long nOfstX;
/*N*/ 
/*N*/     // calc offset inside frame
/*N*/     if ( bIsSwapped )
/*N*/         nOfstX = Frm().Left() + Frm().Height() - rPoint.X();
/*N*/     else
/*N*/         nOfstX = Frm().Left() + Frm().Width() - rPoint.X();
/*N*/ 
/*N*/     const long nOfstY = rPoint.Y() - Frm().Top();
/*N*/ 
/*N*/     // calc rotated coords
/*N*/     rPoint.X() = Frm().Left() + nOfstY;
/*N*/     rPoint.Y() = Frm().Top() + nOfstX;
/*N*/ }
/*N*/ 
/*N*/ // Calculates the a limit value when switching from
/*N*/ // vertical to horizontal layout.
/*N*/ long SwTxtFrm::SwitchVerticalToHorizontal( long nLimit ) const
/*N*/ {
/*N*/     Point aTmp( nLimit, 0 );
/*N*/     SwitchVerticalToHorizontal( aTmp );
/*N*/     return aTmp.Y();
/*N*/ }

/*N*/ SwFrmSwapper::SwFrmSwapper( const SwTxtFrm* pTxtFrm, sal_Bool bSwapIfNotSwapped )
/*N*/     : pFrm( pTxtFrm ), bUndo( sal_False )
/*N*/ {
/*N*/     if ( pFrm->IsVertical() &&
/*N*/         ( (   bSwapIfNotSwapped && ! pFrm->IsSwapped() ) ||
/*N*/           ( ! bSwapIfNotSwapped && pFrm->IsSwapped() ) ) )
/*N*/     {
/*?*/         bUndo = sal_True;
/*?*/         ((SwTxtFrm*)pFrm)->SwapWidthAndHeight();
/*N*/     }
/*N*/ }

/*N*/ SwFrmSwapper::~SwFrmSwapper()
/*N*/ {
/*N*/     if ( bUndo )
/*?*/         ((SwTxtFrm*)pFrm)->SwapWidthAndHeight();
/*N*/ }

#ifdef BIDI

/*N*/ void SwTxtFrm::SwitchLTRtoRTL( SwRect& rRect ) const
/*N*/ {
/*N*/     SWAP_IF_NOT_SWAPPED( this )
/*N*/ 
/*N*/     long nWidth = rRect.Width();
/*N*/     rRect.Left( 2 * ( Frm().Left() + Prt().Left() ) +
/*N*/                 Prt().Width() - rRect.Right() - 1 );
/*N*/ 
/*N*/     rRect.Width( nWidth );
/*N*/ 
/*N*/     UNDO_SWAP( this )
/*N*/ }

/*N*/ void SwTxtFrm::SwitchLTRtoRTL( Point& rPoint ) const
/*N*/ {
/*N*/     SWAP_IF_NOT_SWAPPED( this )
/*N*/ 
/*N*/     rPoint.X() = 2 * ( Frm().Left() + Prt().Left() ) + Prt().Width() - rPoint.X() - 1;
/*N*/ 
/*N*/     UNDO_SWAP( this )
/*N*/ }

/*N*/ SwLayoutModeModifier::SwLayoutModeModifier( const OutputDevice& rOutp ) :
/*N*/         rOut( rOutp ), nOldLayoutMode( rOutp.GetLayoutMode() )
/*N*/ {
/*N*/ }
/*N*/ 
/*N*/ SwLayoutModeModifier::~SwLayoutModeModifier()
/*N*/ {
/*N*/     ((OutputDevice&)rOut).SetLayoutMode( nOldLayoutMode );
/*N*/ }

//STRIP001 void SwLayoutModeModifier::Modify( sal_Bool bChgToRTL )
//STRIP001 {
//STRIP001     ((OutputDevice&)rOut).SetLayoutMode( bChgToRTL ?
//STRIP001                                          TEXT_LAYOUT_BIDI_STRONG | TEXT_LAYOUT_BIDI_RTL :
//STRIP001                                          TEXT_LAYOUT_BIDI_STRONG );
//STRIP001 }

/*N*/ void SwLayoutModeModifier::SetAuto()
/*N*/ {
/*N*/     const ULONG nNewLayoutMode = nOldLayoutMode & ~TEXT_LAYOUT_BIDI_STRONG;
/*N*/     ((OutputDevice&)rOut).SetLayoutMode( nNewLayoutMode );
/*N*/ }

#endif

/*************************************************************************
 *						SwTxtFrm::Init()
 *************************************************************************/

/*N*/ void SwTxtFrm::Init()
/*N*/ {
/*N*/ 	ASSERT( !IsLocked(), "+SwTxtFrm::Init: this ist locked." );
/*N*/ 	if( !IsLocked() )
/*N*/ 	{
/*N*/ 		ClearPara();
/*N*/ 		ResetBlinkPor();
/*N*/ 		//Die Flags direkt setzen um ResetPreps und damit ein unnuetzes GetPara
/*N*/ 		//einzusparen.
/*N*/ 		// Nicht bOrphan, bLocked oder bWait auf sal_False setzen !
/*N*/ 		// bOrphan = bFlag7 = bFlag8 = sal_False;
/*N*/ 	}
/*N*/ }

/*************************************************************************
|*	SwTxtFrm::CTORen/DTOR
|*************************************************************************/

/*N*/ void SwTxtFrm::InitCtor()
/*N*/ {
/*N*/ 	nCacheIdx = MSHRT_MAX;
/*N*/ 	nOfst = 0;
/*N*/ 	nAllLines = 0;
/*N*/ 	nThisLines = 0;
/*N*/   mnFlyAnchorOfst = 0;
/*N*/   mnFlyAnchorOfstNoWrap = 0;
/*N*/ 
/*N*/   nType = FRMC_TXT;
/*N*/ 	bLocked = bFormatted = bWidow = bUndersized = bJustWidow =
/*N*/ 		bEmpty = bInFtnConnect = bFtn = bRepaint = bBlinkPor =
/*N*/         bFieldFollow = bHasAnimation = bIsSwapped = sal_False;
    // OD 14.03.2003 #i11760#
/*N*/     mbFollowFormatAllowed = sal_True;
/*N*/ }


/*N*/ SwTxtFrm::SwTxtFrm(SwTxtNode * const pNode)
/*N*/ 	: SwCntntFrm(pNode)
/*N*/ {
/*N*/ 	InitCtor();
/*N*/ }
/*N*/ 
/*N*/ const XubString& SwTxtFrm::GetTxt() const
/*N*/ {
/*N*/ 	return GetTxtNode()->GetTxt();
/*N*/ }
/*N*/ 
/*N*/ void SwTxtFrm::ResetPreps()
/*N*/ {
/*N*/ 	if ( GetCacheIdx() != MSHRT_MAX )
/*N*/ 	{
/*N*/ 		SwParaPortion *pPara;
/*N*/ 		if( 0 != (pPara = GetPara()) )
/*N*/ 			pPara->ResetPreps();
/*N*/ 	}
/*N*/ }

/*************************************************************************
 *						  SwTxtFrm::IsHiddenNow()
 *************************************************************************/
// liefert nur sal_True zurueck, wenn das Outputdevice ein Printer ist
// und bHidden gesetzt ist.

/*N*/ sal_Bool SwTxtFrm::IsHiddenNow() const
/*N*/ {
/*N*/     SwFrmSwapper aSwapper( this, sal_True );
/*N*/ 
/*N*/ 	if( !Frm().Width() && IsValid() && GetUpper()->IsValid() )
/*N*/ 									   //bei Stackueberlauf (StackHack) invalid!
/*N*/ 	{
/*N*/         ASSERT( Frm().Width(), "SwTxtFrm::IsHiddenNow: thin frame" );
/*N*/ 		return sal_True;
/*N*/ 	}
/*N*/ 
/*N*/     if( !GetTxtNode()->IsVisible() )
/*N*/ 	{
/*N*/ 		const ViewShell *pVsh = GetShell();
/*N*/ 		if ( !pVsh )
/*N*/ 			return sal_False;
/*N*/ 
/*N*/         return ! pVsh->GetWin() ||
/*N*/                (!pVsh->GetViewOptions()->IsShowHiddenPara()      &&
/*N*/ 				!pVsh->GetViewOptions()->IsFldName());
/*N*/ 	}
/*N*/ 	else
/*N*/ 		return sal_False;
/*N*/ }


/*************************************************************************
 *						  SwTxtFrm::HideHidden()
 *************************************************************************/
// Entfernt die Anhaengsel des Textfrms wenn dieser hidden ist

/*N*/ void SwTxtFrm::HideHidden()
/*N*/ {DBG_BF_ASSERT(0, "STRIP"); //STRIP001 
//STRIP001 	ASSERT( IsHiddenNow(), "HideHidden on visible frame" );
//STRIP001 
//STRIP001 	//Erst die Fussnoten
//STRIP001 	const SwpHints *pHints = GetTxtNode()->GetpSwpHints();
//STRIP001 	if( pHints )
//STRIP001 	{
//STRIP001 		const MSHORT nSize = pHints->Count();
//STRIP001 		const xub_StrLen nEnd = GetFollow() ? GetFollow()->GetOfst():STRING_LEN;
//STRIP001 		SwPageFrm *pPage = 0;
//STRIP001 		for( MSHORT i = 0; i < nSize; ++i )
//STRIP001 		{
//STRIP001 			const SwTxtAttr *pHt = (*pHints)[i];
//STRIP001 			if ( pHt->Which() == RES_TXTATR_FTN )
//STRIP001 			{
//STRIP001 				const xub_StrLen nIdx = *pHt->GetStart();
//STRIP001 				if ( nEnd < nIdx )
//STRIP001 					break;
//STRIP001 				if( GetOfst() <= nIdx )
//STRIP001 				{
//STRIP001 					if( !pPage )
//STRIP001 						pPage = FindPageFrm();
//STRIP001 					pPage->RemoveFtn( this, (SwTxtFtn*)pHt );
//STRIP001 				}
//STRIP001 			}
//STRIP001 		}
//STRIP001 	}
//STRIP001 	//Dann die zeichengebundenen Rahmen
//STRIP001 	if ( GetDrawObjs() )
//STRIP001 	{
//STRIP001 		for ( int i = GetDrawObjs()->Count()-1; i >= 0; --i )
//STRIP001 		{
//STRIP001 			SdrObject *pObj = (*GetDrawObjs())[i];
//STRIP001 			SwFlyFrm *pFly;
//STRIP001 			if ( pObj->IsWriterFlyFrame() &&
//STRIP001 				 (pFly = ((SwVirtFlyDrawObj*)pObj)->GetFlyFrm())->IsFlyInCntFrm())
//STRIP001 			{
//STRIP001 				pFly->GetAnchor()->RemoveFly( pFly );
//STRIP001 				delete pFly;
//STRIP001 			}
//STRIP001 		}
//STRIP001 	}
//STRIP001 	//Die Formatinfos sind jetzt obsolete
//STRIP001 	ClearPara();
/*N*/ }


/*************************************************************************
 *						SwTxtFrm::FindBrk()
 *
 * Liefert die erste Trennmoeglichkeit in der aktuellen Zeile zurueck.
 * Die Methode wird in SwTxtFrm::Format() benutzt, um festzustellen, ob
 * die Vorgaengerzeile mitformatiert werden muss.
 * nFound ist <= nEndLine.
 *************************************************************************/

/*N*/ xub_StrLen SwTxtFrm::FindBrk( const XubString &rTxt,
/*N*/ 						  const xub_StrLen nStart, const xub_StrLen nEnd ) const
/*N*/ {
/*N*/ 	xub_StrLen nFound = nStart;
/*N*/ 	const xub_StrLen nEndLine = Min( nEnd, rTxt.Len() );
/*N*/ 
/*N*/ 	// Wir ueberlesen erst alle Blanks am Anfang der Zeile (vgl. Bug 2235).
/*N*/ 	while( nFound <= nEndLine && ' ' == rTxt.GetChar( nFound ) )
/*N*/ 		 ++nFound;
/*N*/ 
/*N*/ 	// Eine knifflige Sache mit den TxtAttr-Dummy-Zeichen (hier "$"):
/*N*/ 	// "Dr.$Meyer" am Anfang der zweiten Zeile. Dahinter ein Blank eingegeben
/*N*/ 	// und das Wort rutscht nicht in die erste Zeile, obwohl es ginge.
/*N*/ 	// Aus diesem Grund nehmen wir das Dummy-Zeichen noch mit.
/*N*/ 	while( nFound <= nEndLine && ' ' != rTxt.GetChar( nFound ) )
/*N*/ 		++nFound;
/*N*/ 
/*N*/ 	return nFound;
/*N*/ }

/*************************************************************************
 *						SwTxtFrm::IsIdxInside()
 *************************************************************************/

/*N*/ sal_Bool SwTxtFrm::IsIdxInside( const xub_StrLen nPos, const xub_StrLen nLen ) const
/*N*/ {
/*N*/ 	if( GetOfst() > nPos + nLen ) // d.h., der Bereich liegt komplett vor uns.
/*N*/ 		return sal_False;
/*N*/ 
/*N*/ 	if( !GetFollow() )		   // der Bereich liegt nicht komplett vor uns,
/*N*/ 		return sal_True;		   // nach uns kommt niemand mehr.
/*N*/ 
/*N*/ 	const xub_StrLen nMax = GetFollow()->GetOfst();
/*N*/ 
/*N*/ 	// der Bereich liegt nicht komplett hinter uns bzw.
/*N*/ 	// unser Text ist geloescht worden.
/*N*/ 	if( nMax > nPos || nMax > GetTxt().Len() )
/*N*/ 		return sal_True;
/*N*/ 
/*N*/     // changes made in the first line of a follow can modify the master
/*N*/     const SwParaPortion* pPara = GetFollow()->GetPara();
/*N*/     return pPara && ( nPos <= nMax + pPara->GetLen() );
/*N*/ }

/*************************************************************************
 *						SwTxtFrm::InvalidateRange()
 *************************************************************************/
/*N*/ inline void SwTxtFrm::InvalidateRange(const SwCharRange &aRange, const long nD)
/*N*/ {
/*N*/ 	if ( IsIdxInside( aRange.Start(), aRange.Len() ) )
/*N*/ 		_InvalidateRange( aRange, nD );
/*N*/ }

/*************************************************************************
 *						SwTxtFrm::_InvalidateRange()
 *************************************************************************/

/*N*/ void SwTxtFrm::_InvalidateRange( const SwCharRange &aRange, const long nD)
/*N*/ {
/*N*/ 	if ( !HasPara() )
/*N*/ 	{	InvalidateSize();
/*N*/ 		return;
/*N*/ 	}
/*N*/ 
/*N*/ 	SetWidow( sal_False );
/*N*/ 	SwParaPortion *pPara = GetPara();
/*N*/ 
/*N*/ 	sal_Bool bInv = sal_False;
/*N*/ 	if( 0 != nD )
/*N*/ 	{
/*N*/ 		//Auf nDelta werden die Differenzen zwischen alter und
/*N*/ 		//neuer Zeilenlaenge aufaddiert, deshalb ist es negativ,
/*N*/ 		//wenn Zeichen eingefuegt wurden, positiv, wenn Zeichen
/*N*/ 		//geloescht wurden.
/*N*/ 		*(pPara->GetDelta()) += nD;
/*N*/ 		bInv = sal_True;
/*N*/ 	}
/*N*/ 	SwCharRange &rReformat = *(pPara->GetReformat());
/*N*/ 	if(aRange != rReformat) {
/*N*/ 		if( STRING_LEN == rReformat.Len() )
/*N*/ 			rReformat = aRange;
/*N*/ 		else
/*N*/ 			rReformat += aRange;
/*N*/ 		bInv = sal_True;
/*N*/ 	}
/*N*/ 	if(bInv)
/*N*/ 	{
/*N*/ // 90365: nD is passed to a follow two times
/*N*/ //        if( GetFollow() )
/*N*/ //            ((SwTxtFrm*)GetFollow())->InvalidateRange( aRange, nD );
/*N*/ 		InvalidateSize();
/*N*/ 	}
/*N*/ }

/*************************************************************************
 *						SwTxtFrm::CalcLineSpace()
 *************************************************************************/

/*N*/ void SwTxtFrm::CalcLineSpace()
/*N*/ {
/*N*/     ASSERT( ! IsVertical() || ! IsSwapped(),
/*N*/             "SwTxtFrm::CalcLineSpace with swapped frame!" )
/*N*/ 
/*N*/ 	if( IsLocked() || !HasPara() )
/*N*/ 		return;
/*N*/ 
/*N*/ 	SwParaPortion *pPara;
/*N*/ 	if( GetDrawObjs() ||
/*N*/ 		GetTxtNode()->GetSwAttrSet().GetLRSpace().IsAutoFirst() ||
/*N*/ 		( pPara = GetPara() )->IsFixLineHeight() )
/*N*/ 	{
/*?*/ 		Init();
/*?*/ 		return;
/*N*/ 	}
/*N*/ 
/*N*/ 	Size aNewSize( Prt().SSize() );
/*N*/ 
/*N*/ 	SwTxtFormatInfo aInf( this );
/*N*/ 	SwTxtFormatter aLine( this, &aInf );
/*N*/ 	if( aLine.GetDropLines() )
/*N*/ 	{
/*N*/ 		Init();
/*N*/ 		return;
/*N*/ 	}
/*N*/ 
/*N*/ 	aLine.Top();
/*N*/ 	aLine.RecalcRealHeight();
/*N*/ 
/*N*/ 	aNewSize.Height() = (aLine.Y() - Frm().Top()) + aLine.GetLineHeight();
/*N*/ 
/*N*/ 	SwTwips nDelta = aNewSize.Height() - Prt().Height();
/*N*/ 	// 4291: Unterlauf bei Flys
/*N*/ 	if( aInf.GetTxtFly()->IsOn() )
/*N*/ 	{
/*N*/ 		SwRect aFrm( Frm() );
/*N*/ 		if( nDelta < 0 )
/*N*/ 			aFrm.Height( Prt().Height() );
/*N*/ 		else
/*N*/ 			aFrm.Height( aNewSize.Height() );
/*N*/ 		if( aInf.GetTxtFly()->Relax( aFrm ) )
/*N*/ 		{
/*?*/ 			Init();
/*?*/ 			return;
/*N*/ 		}
/*N*/ 	}
/*N*/ 
/*N*/ 	if( nDelta )
/*N*/ 	{
/*N*/ 		SwTxtFrmBreak aBreak( this );
/*N*/ 		if( GetFollow() || aBreak.IsBreakNow( aLine ) )
/*N*/ 		{
/*N*/ 			// Wenn es einen Follow() gibt, oder wenn wir an dieser
/*N*/ 			// Stelle aufbrechen muessen, so wird neu formatiert.
/*N*/ 			Init();
/*N*/ 		}
/*N*/ 		else
/*N*/ 		{
/*N*/ 			// Alles nimmt seinen gewohnten Gang ...
/*N*/ 			pPara->SetPrepAdjust();
/*N*/ 			pPara->SetPrep();
/*N*/ #ifdef USED
/*N*/ 			if (nDelta > 0)
/*N*/ 				Grow(nDelta,pHeight);
/*N*/ 			else
/*N*/ 				Shrink(-nDelta,pHeight);
/*N*/ 			ASSERT( GetPara(), "+SwTxtFrm::CalcLineSpace: missing format information" );
/*N*/ 			if( pPara )
/*N*/ 				pPara->GetRepaint()->SSize( Prt().SSize() );
/*N*/ #endif
/*N*/ 		}
/*N*/ 	}
/*N*/ }

#define SET_WRONG( nPos, nCnt, fnFunc ) \
{ \
    if ( !IsFollow() ) \
    { \
        if( GetTxtNode()->GetWrong() ) \
            GetTxtNode()->GetWrong()->fnFunc( nPos, nCnt ); \
        else if ( ! GetTxtNode()->IsWrongDirty() ) \
        { \
            GetTxtNode()->SetWrong( new SwWrongList() ); \
            GetTxtNode()->GetWrong()->SetInvalid( nPos, nPos + ( nCnt > 0 ? nCnt : 1 ) ); \
        } \
        GetNode()->SetWrongDirty( sal_True ); \
        GetNode()->SetAutoCompleteWordDirty( sal_True ); \
    } \
    SwPageFrm *pPage = FindPageFrm(); \
    if( pPage ) \
    { \
        pPage->InvalidateSpelling(); \
        pPage->InvalidateAutoCompleteWords(); \
    } \
}

#define SET_SCRIPT_INVAL( nPos )\
{ \
    if( GetPara() ) \
        GetPara()->GetScriptInfo().SetInvalidity( nPos ); \
}

/*N*/ void lcl_ModifyOfst( SwTxtFrm* pFrm, xub_StrLen nPos, xub_StrLen nLen )
/*N*/ {
/*N*/ 	if( nLen < 0 )
/*N*/ 		nPos -= nLen;
/*N*/ 	while( pFrm && pFrm->GetOfst() <= nPos )
/*N*/ 		pFrm = pFrm->GetFollow();
/*N*/ 	while( pFrm )
/*N*/ 	{
/*N*/ 		pFrm->ManipOfst( pFrm->GetOfst() + nLen );
/*N*/ 		pFrm = pFrm->GetFollow();
/*N*/ 	}
/*N*/ }

/*************************************************************************
 *						SwTxtFrm::Modify()
 *************************************************************************/

/*M*/ void SwTxtFrm::Modify( SfxPoolItem *pOld, SfxPoolItem *pNew )
/*M*/ {
/*M*/ 	const MSHORT nWhich = pOld ? pOld->Which() : pNew ? pNew->Which() : 0;
/*M*/ 
/*M*/ 	//Wuensche die FrmAttribute betreffen werden von der Basisklasse
/*M*/ 	//verarbeitet.
/*M*/ 	if( IsInRange( aFrmFmtSetRange, nWhich ) || RES_FMT_CHG == nWhich )
/*M*/ 	{
/*M*/ 		SwCntntFrm::Modify( pOld, pNew );
/*M*/ 		if( nWhich == RES_FMT_CHG && GetShell() )
/*M*/ 		{
/*M*/ 			// Collection hat sich geaendert
/*M*/ 			Prepare( PREP_CLEAR );
/*M*/ 			_InvalidatePrt();
/*M*/             SET_WRONG( 0, STRING_LEN, Invalidate );
/*N*/             SetDerivedR2L( sal_False );
/*N*/             CheckDirChange();
/*N*/             // OD 09.12.2002 #105576# - Force complete paint due to existing
/*N*/             // indents.
/*N*/             SetCompletePaint();
/*M*/ 			InvalidateLineNum();
/*M*/ 		}
/*M*/ 		return;
/*M*/ 	}
/*M*/ 
/*M*/ 	// Im gelockten Zustand werden keine Bestellungen angenommen.
/*M*/ 	if( IsLocked() )
/*M*/ 		return;
/*M*/ 
/*M*/ 	// Dies spart Stack, man muss nur aufpassen,
/*M*/ 	// dass sie Variablen gesetzt werden.
/*M*/ 	xub_StrLen nPos, nLen;
/*M*/ 	sal_Bool bSetFldsDirty = sal_False;
/*M*/ 	sal_Bool bRecalcFtnFlag = sal_False;
/*M*/ 
/*M*/ 	switch( nWhich )
/*M*/ 	{
/*M*/ 		case RES_LINENUMBER:
/*M*/ 		{
/*M*/ 			InvalidateLineNum();
/*M*/ 		}
/*M*/ 		break;
/*M*/ 		case RES_INS_CHR:
/*M*/ 		{
/*M*/ 			nPos = ((SwInsChr*)pNew)->nPos;
/*M*/ 			InvalidateRange( SwCharRange( nPos, 1 ), 1 );
/*M*/ 			SET_WRONG( nPos, 1, Move )
/*M*/ 			SET_SCRIPT_INVAL( nPos )
/*M*/ 			bSetFldsDirty = sal_True;
/*M*/ 			if( HasFollow() )
/*M*/ 				lcl_ModifyOfst( this, nPos, 1 );
/*M*/ 		}
/*M*/ 		break;
/*M*/ 		case RES_INS_TXT:
/*M*/ 		{
/*M*/ 			nPos = ((SwInsTxt*)pNew)->nPos;
/*M*/ 			nLen = ((SwInsTxt*)pNew)->nLen;
/*M*/ 			if( IsIdxInside( nPos, nLen ) )
/*M*/ 			{
/*M*/ 				if( !nLen )
/*M*/ 				{
/*M*/ 					// 6969: Aktualisierung der NumPortions auch bei leeren Zeilen!
/*M*/ 					if( nPos )
/*M*/ 						InvalidateSize();
/*M*/ 					else
/*M*/ 						Prepare( PREP_CLEAR );
/*M*/ 				}
/*M*/ 				else
/*M*/ 					_InvalidateRange( SwCharRange( nPos, nLen ), nLen );
/*M*/ 			}
/*M*/ 			SET_WRONG( nPos, nLen, Move )
/*M*/ 			SET_SCRIPT_INVAL( nPos )
/*M*/ 			bSetFldsDirty = sal_True;
/*M*/ 			if( HasFollow() )
/*M*/ 				lcl_ModifyOfst( this, nPos, nLen );
/*M*/ 		}
/*M*/ 		break;
/*M*/ 		case RES_DEL_CHR:
/*M*/ 		{
/*M*/ 			nPos = ((SwDelChr*)pNew)->nPos;
/*M*/ 			InvalidateRange( SwCharRange( nPos, 1 ), -1 );
/*M*/ 			SET_WRONG( nPos, -1, Move )
/*M*/ 			SET_SCRIPT_INVAL( nPos )
/*M*/ 			bSetFldsDirty = bRecalcFtnFlag = sal_True;
/*M*/ 			if( HasFollow() )
/*M*/ 				lcl_ModifyOfst( this, nPos, -1 );
/*M*/ 		}
/*M*/ 		break;
/*M*/ 		case RES_DEL_TXT:
/*M*/ 		{
/*M*/ 			nPos = ((SwDelTxt*)pNew)->nStart;
/*M*/ 			nLen = ((SwDelTxt*)pNew)->nLen;
/*M*/ 			long m = nLen;
/*M*/ 			m *= -1;
/*M*/ 			if( IsIdxInside( nPos, nLen ) )
/*M*/ 			{
/*M*/ 				if( !nLen )
/*M*/ 					InvalidateSize();
/*M*/ 				else
/*M*/ 					InvalidateRange( SwCharRange( nPos, 1 ), m );
/*M*/ 			}
/*M*/ 			SET_WRONG( nPos, m, Move )
/*M*/ 			SET_SCRIPT_INVAL( nPos )
/*M*/ 			bSetFldsDirty = bRecalcFtnFlag = sal_True;
/*M*/ 			if( HasFollow() )
/*M*/ 				lcl_ModifyOfst( this, nPos, nLen );
/*M*/ 		}
/*M*/ 		break;
/*M*/ 		case RES_UPDATE_ATTR:
/*M*/ 		{
/*M*/ 			nPos = ((SwUpdateAttr*)pNew)->nStart;
/*M*/ 			nLen = ((SwUpdateAttr*)pNew)->nEnd - nPos;
/*M*/ 			if( IsIdxInside( nPos, nLen ) )
/*M*/ 			{
/*M*/ 				// Es muss in jedem Fall neu formatiert werden,
/*M*/ 				// auch wenn der invalidierte Bereich null ist.
/*M*/ 				// Beispiel: leere Zeile, 14Pt einstellen !
/*M*/ 				// if( !nLen ) nLen = 1;
/*M*/ 
/*M*/ 				// 6680: FtnNummern muessen formatiert werden.
/*M*/ 				if( !nLen )
/*M*/ 					nLen = 1;
/*M*/ 
/*M*/ 				_InvalidateRange( SwCharRange( nPos, nLen) );
/*M*/ 				MSHORT nTmp = ((SwUpdateAttr*)pNew)->nWhichAttr;
/*M*/ 
/*M*/                 if( ! nTmp || RES_TXTATR_CHARFMT == nTmp ||
/*M*/                     RES_FMT_CHG == nTmp || RES_ATTRSET_CHG == nTmp )
/*M*/                 {
/*M*/                     SET_WRONG( nPos, nPos + nLen, Invalidate )
/*M*/                     SET_SCRIPT_INVAL( nPos )
/*M*/                 }
/*N*/                 else if ( RES_CHRATR_LANGUAGE == nTmp ||
/*N*/                           RES_CHRATR_CJK_LANGUAGE == nTmp ||
/*N*/                           RES_CHRATR_CTL_LANGUAGE == nTmp )
/*M*/                     SET_WRONG( nPos, nPos + nLen, Invalidate )
/*M*/                 else if ( RES_CHRATR_FONT == nTmp || RES_CHRATR_CJK_FONT == nTmp ||
/*M*/                           RES_CHRATR_CTL_FONT == nTmp )
/*M*/                     SET_SCRIPT_INVAL( nPos )
/*M*/ 			}
/*M*/ 		}
/*M*/ 		break;
/*M*/ 		case RES_OBJECTDYING:
/*M*/ 		break;
/*M*/ 
/*M*/ 		case RES_PARATR_LINESPACING:
/*M*/ 			{
/*M*/ 				CalcLineSpace();
/*M*/ 				InvalidateSize();
/*M*/ 				_InvalidatePrt();
/*M*/ 				if( IsInSct() && !GetPrev() )
/*M*/ 				{
/*M*/ 					SwSectionFrm *pSect = FindSctFrm();
/*M*/ 					if( pSect->ContainsAny() == this )
/*M*/ 						pSect->InvalidatePrt();
/*M*/ 				}
/*M*/ 				SwFrm* pNxt;
/*M*/ 				if ( 0 != ( pNxt = GetIndNext() ) )
/*M*/ 				{
/*M*/ 					pNxt->_InvalidatePrt();
/*M*/ 					if ( pNxt->IsLayoutFrm() )
/*M*/ 						pNxt->InvalidatePage();
/*M*/ 				}
/*M*/ 				SetCompletePaint();
/*M*/ 			}
/*M*/ 			break;
/*M*/ 		case RES_TXTATR_FIELD:
/*M*/ 		{
/*M*/ 			nPos = *((SwFmtFld*)pNew)->GetTxtFld()->GetStart();
/*M*/ 			if( IsIdxInside( nPos, 1 ) )
/*M*/ 			{
/*M*/ 				if( pNew == pOld )
/*M*/ 				{
/*M*/ 					// Nur repainten
/*M*/ 					// opt: invalidate aufs Window ?
/*M*/ 					InvalidatePage();
/*M*/ 					SetCompletePaint();
/*M*/ 				}
/*M*/ 				else
/*M*/ 					_InvalidateRange( SwCharRange( nPos, 1 ) );
/*M*/ 			}
/*M*/ 			bSetFldsDirty = sal_True;
/*M*/ 		}
/*M*/ 		break;
/*M*/ 		case RES_TXTATR_FTN :
/*M*/ 		{
/*M*/ 			nPos = *((SwFmtFtn*)pNew)->GetTxtFtn()->GetStart();
/*M*/ 			if( IsInFtn() || IsIdxInside( nPos, 1 ) )
/*M*/ 				Prepare( PREP_FTN, ((SwFmtFtn*)pNew)->GetTxtFtn() );
/*M*/ 			break;
/*M*/ 		}
/*M*/ 
/*M*/ 		case RES_ATTRSET_CHG:
/*M*/ 		{
/*M*/ 			InvalidateLineNum();
/*M*/ 
/*M*/ 			SwAttrSet& rNewSet = *((SwAttrSetChg*)pNew)->GetChgSet();
/*M*/ 			const SfxPoolItem* pItem;
/*M*/ 			int nClear = 0;
/*M*/ 			MSHORT nCount = rNewSet.Count();
/*M*/ 
/*M*/ 			if( SFX_ITEM_SET == rNewSet.GetItemState( RES_TXTATR_FTN,
/*M*/ 				sal_False, &pItem ))
/*M*/ 			{
/*M*/ 				nPos = *((SwFmtFtn*)pItem)->GetTxtFtn()->GetStart();
/*M*/ 				if( IsIdxInside( nPos, 1 ) )
/*M*/ 					Prepare( PREP_FTN, pNew );
/*M*/ 				nClear = 0x01;
/*M*/ 				--nCount;
/*M*/ 			}
/*M*/ 
/*M*/ 			if( SFX_ITEM_SET == rNewSet.GetItemState( RES_TXTATR_FIELD,
/*M*/ 				sal_False, &pItem ))
/*M*/ 			{
/*M*/ 				nPos = *((SwFmtFld*)pItem)->GetTxtFld()->GetStart();
/*M*/ 				if( IsIdxInside( nPos, 1 ) )
/*M*/ 				{
/*M*/ 					const SfxPoolItem& rOldItem = ((SwAttrSetChg*)pOld)->
/*M*/ 										GetChgSet()->Get( RES_TXTATR_FIELD );
/*M*/ 					if( pItem == &rOldItem )
/*M*/ 					{
/*M*/ 						// Nur repainten
/*M*/ 						// opt: invalidate aufs Window ?
/*M*/ 						InvalidatePage();
/*M*/ 						SetCompletePaint();
/*M*/ 					}
/*M*/ 					else
/*M*/ 						_InvalidateRange( SwCharRange( nPos, 1 ) );
/*M*/ 				}
/*M*/ 				nClear |= 0x02;
/*M*/ 				--nCount;
/*M*/ 			}
/*M*/ 			sal_Bool bLineSpace = SFX_ITEM_SET == rNewSet.GetItemState(
/*M*/ 											RES_PARATR_LINESPACING, sal_False ),
/*M*/ 					 bRegister	= SFX_ITEM_SET == rNewSet.GetItemState(
/*M*/ 											RES_PARATR_REGISTER, sal_False );
/*M*/ 			if ( bLineSpace || bRegister )
/*M*/ 			{
/*M*/ 				Prepare( bRegister ? PREP_REGISTER : PREP_ADJUST_FRM );
/*M*/ 				CalcLineSpace();
/*M*/ 				InvalidateSize();
/*M*/ 				_InvalidatePrt();
/*M*/ 				SwFrm* pNxt;
/*M*/ 				if ( 0 == ( pNxt = GetIndNext() ) &&
/*M*/ 					 bLineSpace && IsInFtn() )
/*M*/ 					pNxt = FindNext();
/*M*/ 				if( pNxt )
/*M*/ 				{
/*M*/ 					pNxt->_InvalidatePrt();
/*M*/ 					if ( pNxt->IsLayoutFrm() )
/*M*/ 					{
/*M*/ 						if( pNxt->IsSctFrm() )
/*M*/ 						{
/*M*/ 							SwFrm* pCnt = ((SwSectionFrm*)pNxt)->ContainsAny();
/*M*/ 							if( pCnt )
/*M*/ 								pCnt->_InvalidatePrt();
/*M*/ 						}
/*M*/ 						pNxt->InvalidatePage();
/*M*/ 					}
/*M*/ 				}
/*M*/ 
/*M*/ 				SetCompletePaint();
/*M*/ 				nClear |= 0x04;
/*M*/ 				if ( bLineSpace )
/*M*/ 				{
/*M*/ 					--nCount;
/*M*/ 					if( IsInSct() && !GetPrev() )
/*M*/ 					{
/*M*/ 						SwSectionFrm *pSect = FindSctFrm();
/*M*/ 						if( pSect->ContainsAny() == this )
/*M*/ 							pSect->InvalidatePrt();
/*M*/ 					}
/*M*/ 				}
/*M*/ 				if ( bRegister )
/*M*/ 					--nCount;
/*M*/ 			}
/*M*/ 			if ( SFX_ITEM_SET == rNewSet.GetItemState( RES_PARATR_SPLIT,
/*M*/ 													   sal_False ))
/*M*/ 			{
/*M*/ 				if ( GetPrev() )
/*M*/ 					CheckKeep();
/*M*/ 				Prepare( PREP_CLEAR );
/*M*/ 				InvalidateSize();
/*M*/ 				nClear |= 0x08;
/*M*/ 				--nCount;
/*M*/ 			}
/*M*/ 
/*M*/             if( SFX_ITEM_SET == rNewSet.GetItemState( RES_BACKGROUND, sal_False)
/*M*/                 && !IsFollow() && GetDrawObjs() )
/*M*/             {
/*M*/                 SwDrawObjs *pObjs = GetDrawObjs();
/*M*/                 for ( int i = 0; GetDrawObjs() && i < int(pObjs->Count()); ++i )
/*M*/                 {
/*M*/                     SdrObject *pO = (*pObjs)[MSHORT(i)];
/*M*/                     if ( pO->IsWriterFlyFrame() )
/*M*/                     {
/*M*/                         SwFlyFrm *pFly = ((SwVirtFlyDrawObj*)pO)->GetFlyFrm();
/*M*/                         if( !pFly->IsFlyInCntFrm() )
/*M*/                         {
/*M*/                             const SvxBrushItem &rBack =
/*M*/                                 pFly->GetAttrSet()->GetBackground();
/*M*/                             /// OD 20.08.2002 #99657# #GetTransChg#
/*M*/                             ///     following condition determines, if the fly frame
/*M*/                             ///     "inherites" the background color of text frame.
/*M*/                             ///     This is the case, if fly frame background
/*M*/                             ///     color is "no fill"/"auto fill" and if the fly frame
/*M*/                             ///     has no background graphic.
/*M*/                             ///     Thus, check complete fly frame background
/*M*/                             ///     color and *not* only its transparency value
/*M*/                             if ( (rBack.GetColor() == COL_TRANSPARENT)  &&
/*M*/                             ///if( rBack.GetColor().GetTransparency() &&
/*M*/                                 rBack.GetGraphicPos() == GPOS_NONE )
/*M*/                             {
/*M*/                                 pFly->SetCompletePaint();
/*M*/                                 pFly->InvalidatePage();
/*M*/                             }
/*M*/                         }
/*M*/                     }
/*M*/                 }
/*M*/             }
/*M*/ 
/*M*/             if ( SFX_ITEM_SET ==
/*M*/                  rNewSet.GetItemState( RES_TXTATR_CHARFMT, sal_False ) )
/*M*/             {
/*M*/                 SET_WRONG( 0, STRING_LEN, Invalidate )
/*M*/                 SET_SCRIPT_INVAL( 0 )
/*M*/             }
/*M*/             else if ( SFX_ITEM_SET ==
/*N*/                       rNewSet.GetItemState( RES_CHRATR_LANGUAGE, sal_False ) ||
/*N*/                       SFX_ITEM_SET ==
/*N*/                       rNewSet.GetItemState( RES_CHRATR_CJK_LANGUAGE, sal_False ) ||
/*N*/                       SFX_ITEM_SET ==
/*N*/                       rNewSet.GetItemState( RES_CHRATR_CTL_LANGUAGE, sal_False ) )
/*M*/                 SET_WRONG( 0, STRING_LEN, Invalidate )
/*M*/             else if ( SFX_ITEM_SET ==
/*M*/                       rNewSet.GetItemState( RES_CHRATR_FONT, sal_False ) ||
/*M*/                       SFX_ITEM_SET ==
/*M*/                       rNewSet.GetItemState( RES_CHRATR_CJK_FONT, sal_False ) ||
/*M*/                       SFX_ITEM_SET ==
/*M*/                       rNewSet.GetItemState( RES_CHRATR_CTL_FONT, sal_False ) )
/*M*/                 SET_SCRIPT_INVAL( 0 )
/*M*/             else if ( SFX_ITEM_SET ==
/*M*/                       rNewSet.GetItemState( RES_FRAMEDIR, sal_False ) )
/*M*/             {
/*M*/                 SetDerivedR2L( sal_False );
/*M*/                 CheckDirChange();
/*N*/                 // OD 09.12.2002 #105576# - Force complete paint due to existing
/*N*/                 // indents.
/*N*/                 SetCompletePaint();
/*M*/             }
/*M*/ 
/*M*/ 
/*M*/             if( nCount )
/*M*/ 			{
/*M*/ 				if( GetShell() )
/*M*/ 				{
/*M*/ 					Prepare( PREP_CLEAR );
/*M*/ 					_InvalidatePrt();
/*M*/ 				}
/*M*/ 
/*M*/ 				if( nClear )
/*M*/ 				{
/*M*/ 					SwAttrSetChg aOldSet( *(SwAttrSetChg*)pOld );
/*M*/ 					SwAttrSetChg aNewSet( *(SwAttrSetChg*)pNew );
/*M*/ 
/*M*/ 					if( 0x01 & nClear )
/*M*/ 					{
/*M*/ 						aOldSet.ClearItem( RES_TXTATR_FTN );
/*M*/ 						aNewSet.ClearItem( RES_TXTATR_FTN );
/*M*/ 					}
/*M*/ 					if( 0x02 & nClear )
/*M*/ 					{
/*M*/ 						aOldSet.ClearItem( RES_TXTATR_FIELD );
/*M*/ 						aNewSet.ClearItem( RES_TXTATR_FIELD );
/*M*/ 					}
/*M*/ 					if ( 0x04 & nClear )
/*M*/ 					{
/*M*/ 						if ( bLineSpace )
/*M*/ 						{
/*M*/ 							aOldSet.ClearItem( RES_PARATR_LINESPACING );
/*M*/ 							aNewSet.ClearItem( RES_PARATR_LINESPACING );
/*M*/ 						}
/*M*/ 						if ( bRegister )
/*M*/ 						{
/*M*/ 							aOldSet.ClearItem( RES_PARATR_REGISTER );
/*M*/ 							aNewSet.ClearItem( RES_PARATR_REGISTER );
/*M*/ 						}
/*M*/ 					}
/*M*/ 					if ( 0x08 & nClear )
/*M*/ 					{
/*M*/ 						aOldSet.ClearItem( RES_PARATR_SPLIT );
/*M*/ 						aNewSet.ClearItem( RES_PARATR_SPLIT );
/*M*/ 					}
/*M*/ 					SwCntntFrm::Modify( &aOldSet, &aNewSet );
/*M*/ 				}
/*M*/ 				else
/*M*/ 					SwCntntFrm::Modify( pOld, pNew );
/*M*/ 			}
/*M*/ 		}
/*M*/ 		break;
/*M*/ 
/* Seit dem neuen Blocksatz muessen wir immer neu formatieren:
         case RES_PARATR_ADJUST:
        {
             if( GetShell() )
            {
                Prepare( PREP_CLEAR );
            }
            break;
        }
*/
/*M*/ 		// 6870: SwDocPosUpdate auswerten.
/*M*/ 		case RES_DOCPOS_UPDATE:
/*M*/ 		{
/*M*/ 			if( pOld && pNew )
/*M*/ 			{
/*M*/ 				const SwDocPosUpdate *pDocPos = (const SwDocPosUpdate*)pOld;
/*M*/ 				if( pDocPos->nDocPos <= aFrm.Top() )
/*M*/ 				{
/*M*/ 					const SwFmtFld *pFld = (const SwFmtFld *)pNew;
/*M*/ 					InvalidateRange(
/*M*/ 						SwCharRange( *pFld->GetTxtFld()->GetStart(), 1 ) );
/*M*/ 				}
/*M*/ 			}
/*M*/ 			break;
/*M*/ 		}
/*M*/ 		case RES_PARATR_SPLIT:
/*M*/ 			if ( GetPrev() )
/*M*/ 				CheckKeep();
/*M*/ 			Prepare( PREP_CLEAR );
/*M*/ 			bSetFldsDirty = sal_True;
/*M*/ 			break;
/*M*/         case RES_FRAMEDIR :
/*M*/             SetDerivedR2L( sal_False );
/*M*/             CheckDirChange();
/*M*/             break;
/*M*/ 		default:
/*M*/ 		{
/*M*/ 			Prepare( PREP_CLEAR );
/*M*/ 			_InvalidatePrt();
/*M*/ 			if ( !nWhich )
/*M*/ 			{
/*M*/ 				//Wird z.B. bei HiddenPara mit 0 gerufen.
/*M*/ 				SwFrm *pNxt;
/*M*/ 				if ( 0 != (pNxt = FindNext()) )
/*M*/ 					pNxt->InvalidatePrt();
/*M*/ 			}
/*M*/ 		}
/*M*/ 	} // switch
/*M*/ 
/*M*/ 	if( bSetFldsDirty )
/*M*/ 		GetNode()->GetDoc()->SetFieldsDirty( sal_True, GetNode(), 1 );
/*M*/ 
/*M*/ 	if ( bRecalcFtnFlag )
/*M*/ 		CalcFtnFlag();
/*M*/ }

/*M*/ sal_Bool SwTxtFrm::GetInfo( SfxPoolItem &rHnt ) const
/*M*/ {
/*M*/     if ( RES_VIRTPAGENUM_INFO == rHnt.Which() && IsInDocBody() && ! IsFollow() )
/*M*/ 	{
/*M*/ 		SwVirtPageNumInfo &rInfo = (SwVirtPageNumInfo&)rHnt;
/*M*/ 		const SwPageFrm *pPage = FindPageFrm();
/*M*/         if ( pPage )
/*M*/ 		{
/*M*/             if ( pPage == rInfo.GetOrigPage() && !GetPrev() )
/*M*/ 			{
/*M*/ 				//Das sollte er sein (kann allenfalls temporaer anders sein,
/*M*/ 				//					  sollte uns das beunruhigen?)
/*M*/ 				rInfo.SetInfo( pPage, this );
/*M*/ 				return sal_False;
/*M*/ 			}
/*M*/ 			if ( pPage->GetPhyPageNum() < rInfo.GetOrigPage()->GetPhyPageNum() &&
/*M*/ 				 (!rInfo.GetPage() || pPage->GetPhyPageNum() > rInfo.GetPage()->GetPhyPageNum()))
/*M*/ 			{
/*M*/ 				//Das koennte er sein.
/*M*/ 				rInfo.SetInfo( pPage, this );
/*M*/ 			}
/*M*/ 		}
/*M*/ 	}
/*M*/ 	return sal_True;
/*M*/ }

/*************************************************************************
 *						SwTxtFrm::PrepWidows()
 *************************************************************************/

/*M*/ void SwTxtFrm::PrepWidows( const MSHORT nNeed, sal_Bool bNotify )
/*M*/ {
/*M*/ 	ASSERT(GetFollow() && nNeed, "+SwTxtFrm::Prepare: lost all friends");
/*M*/ 
/*M*/ 	SwParaPortion *pPara = GetPara();
/*M*/ 	if ( !pPara )
/*M*/ 		return;
/*M*/ 	pPara->SetPrepWidows( sal_True );
/*M*/ 
/*M*/     // These two lines of code have been deleted for #102340#.
/*M*/     // Obviously the widow control does not work if we have a
/*M*/     // pMaster->pFollow->pFollow situation:
/*M*/ 
/*M*/ 	// returnen oder nicht ist hier die Frage.
/*M*/ 	// Ohne IsLocked() ist 5156 gefaehrlich,
/*M*/ 	// ohne IsFollow() werden die Orphans unterdrueckt: 6968.
/*M*/ 	// Abfrage auf IsLocked erst hier, weil das Flag gesetzt werden soll.
/*M*/ //  if( IsLocked() && IsFollow() )
/*M*/ //      return;
/*M*/ 
/*M*/ 	MSHORT nHave = nNeed;
/*M*/ 
/*M*/ 	// Wir geben ein paar Zeilen ab und schrumpfen im CalcPreps()
/*M*/     SWAP_IF_NOT_SWAPPED( this )
/*M*/ 
/*M*/ 	SwTxtSizeInfo aInf( this );
/*M*/ 	SwTxtMargin aLine( this, &aInf );
/*M*/ 	aLine.Bottom();
/*M*/ 	xub_StrLen nTmpLen = aLine.GetCurr()->GetLen();
/*M*/ 	while( nHave && aLine.PrevLine() )
/*M*/ 	{
/*M*/ 		if( nTmpLen )
/*M*/ 			--nHave;
/*M*/ 		nTmpLen = aLine.GetCurr()->GetLen();
/*M*/ 	}
/*M*/ 	// In dieser Ecke tummelten sich einige Bugs: 7513, 7606.
/*M*/ 	// Wenn feststeht, dass Zeilen abgegeben werden koennen,
/*M*/ 	// muss der Master darueber hinaus die Widow-Regel ueberpruefen.
/*M*/ 	if( !nHave )
/*M*/ 	{
/*M*/ 		sal_Bool bSplit;
/*M*/ 		if( !IsFollow() )	//Nur ein Master entscheidet ueber Orphans
/*M*/ 		{
/*M*/ 			const WidowsAndOrphans aWidOrp( this );
/*M*/ 			bSplit = ( aLine.GetLineNr() >= aWidOrp.GetOrphansLines() &&
/*M*/ 					   aLine.GetLineNr() >= aLine.GetDropLines() );
/*M*/ 		}
/*M*/ 		else
/*M*/ 			bSplit = sal_True;
/*M*/ 
/*M*/ 		if( bSplit )
/*M*/ 		{
/*M*/ 			GetFollow()->SetOfst( aLine.GetEnd() );
/*M*/ 			aLine.TruncLines( sal_True );
/*M*/ 			if( pPara->IsFollowField() )
/*M*/ 				GetFollow()->SetFieldFollow( sal_True );
/*M*/ 		}
/*M*/ 	}
/*M*/ 	if ( bNotify )
/*M*/ 	{
/*M*/ 		_InvalidateSize();
/*M*/ 		InvalidatePage();
/*M*/ 	}
/*M*/ 
/*M*/     UNDO_SWAP( this )
/*M*/ }

/*************************************************************************
 *						SwTxtFrm::Prepare
 *************************************************************************/

/*N*/ sal_Bool lcl_ErgoVadis( SwTxtFrm* pFrm, xub_StrLen &rPos, const PrepareHint ePrep )
/*N*/ {
/*N*/ 	const SwFtnInfo &rFtnInfo = pFrm->GetNode()->GetDoc()->GetFtnInfo();
/*N*/ 	if( ePrep == PREP_ERGOSUM )
/*N*/ 	{
/*?*/ 		if( !rFtnInfo.aErgoSum.Len() )
/*?*/ 			return sal_False;;
/*?*/ 		rPos = pFrm->GetOfst();
/*N*/ 	}
/*N*/ 	else
/*N*/ 	{
/*N*/ 		if( !rFtnInfo.aQuoVadis.Len() )
/*N*/ 			return sal_False;
/*?*/ 		if( pFrm->HasFollow() )
/*?*/ 			rPos = pFrm->GetFollow()->GetOfst();
/*?*/ 		else
/*?*/ 			rPos = pFrm->GetTxt().Len();
/*?*/ 		if( rPos )
/*?*/ 			--rPos; // unser letztes Zeichen
/*N*/ 	}
/*N*/ 	return sal_True;
/*N*/ }

/*N*/ void SwTxtFrm::Prepare( const PrepareHint ePrep, const void* pVoid,
/*N*/ 						sal_Bool bNotify )
/*N*/ {
/*N*/     SwFrmSwapper aSwapper( this, sal_False );
/*N*/ 
/*N*/ #if OSL_DEBUG_LEVEL > 1
/*N*/ 	const SwTwips nDbgY = Frm().Top();
/*N*/ #endif
/*N*/ 
/*N*/ 	if ( IsEmpty() )
/*N*/ 	{
/*N*/ 		switch ( ePrep )
/*N*/ 		{
/*N*/ 			case PREP_BOSS_CHGD:
/*N*/                 SetInvalidVert( TRUE );  // Test
/*N*/ 			case PREP_WIDOWS_ORPHANS:
/*N*/ 			case PREP_WIDOWS:
/*N*/ 			case PREP_FTN_GONE :	return;
/*N*/ 
/*N*/ 			case PREP_POS_CHGD :
/*N*/             {
/*N*/                 // Auch in (spaltigen) Bereichen ist ein InvalidateSize notwendig,
/*N*/                 // damit formatiert wird und ggf. das bUndersized gesetzt wird.
/*N*/ 				if( IsInFly() || IsInSct() )
/*N*/ 				{
/*N*/ 					SwTwips nTmpBottom = GetUpper()->Frm().Top() +
/*N*/ 						GetUpper()->Prt().Bottom();
/*N*/ 					if( nTmpBottom < Frm().Bottom() )
/*N*/ 						break;
/*N*/ 				}
/*N*/ 				// Gibt es ueberhaupt Flys auf der Seite ?
/*N*/ 				SwTxtFly aTxtFly( this );
/*N*/ 				if( aTxtFly.IsOn() )
/*N*/ 				{
/*N*/ 					// Ueberlappt irgendein Fly ?
/*N*/ 					aTxtFly.Relax();
/*N*/ 					if ( aTxtFly.IsOn() || IsUndersized() )
/*N*/ 						break;
/*N*/ 				}
/*N*/ 				if( GetTxtNode()->GetSwAttrSet().GetRegister().GetValue())
/*N*/ 					break;
/*N*/ 
/*N*/                 GETGRID( FindPageFrm() )
/*N*/                 if ( pGrid && GetTxtNode()->GetSwAttrSet().GetParaGrid().GetValue() )
/*N*/                     break;
/*N*/ 
/*N*/ 				return;
/*N*/ 			}
/*N*/ 		}
/*N*/ 	}
/*N*/ 
/*N*/ 	if( !HasPara() && PREP_MUST_FIT != ePrep )
/*N*/ 	{
/*N*/         SetInvalidVert( TRUE );  // Test
/*N*/ 		ASSERT( !IsLocked(), "SwTxtFrm::Prepare: three of a perfect pair" );
/*N*/ 		if ( bNotify )
/*N*/ 			InvalidateSize();
/*N*/ 		else
/*N*/ 			_InvalidateSize();
/*N*/ 		return;
/*N*/ 	}
/*N*/ 
/*N*/ 	//Objekt mit Locking aus dem Cache holen.
/*N*/ 	SwTxtLineAccess aAccess( this );
/*N*/ 	SwParaPortion *pPara = aAccess.GetPara();
/*N*/ 
/*N*/ 	switch( ePrep )
/*N*/ 	{
/*?*/ 		case PREP_MOVEFTN :     Frm().Height(0);
/*?*/ 								Prt().Height(0);
/*?*/ 								_InvalidatePrt();
/*?*/ 								_InvalidateSize();
/*N*/ 								// KEIN break
/*N*/ 		case PREP_ADJUST_FRM :	pPara->SetPrepAdjust( sal_True );
/*N*/ 								if( IsFtnNumFrm() != pPara->IsFtnNum() ||
/*N*/ 									IsUndersized() )
/*N*/ 								{
/*N*/ 									InvalidateRange( SwCharRange( 0, 1 ), 1);
/*N*/ 									if( GetOfst() && !IsFollow() )
/*?*/ 										_SetOfst( 0 );
/*N*/ 								}
/*N*/ 								break;
/*?*/ 		case PREP_MUST_FIT :		pPara->SetPrepMustFit( sal_True );
/*N*/ 			/* no break here */
/*N*/ 		case PREP_WIDOWS_ORPHANS :	pPara->SetPrepAdjust( sal_True );
/*N*/ 									break;
/*N*/ 
/*N*/ 		case PREP_WIDOWS :
/*N*/ 			// MustFit ist staerker als alles anderes
/*N*/ 			if( pPara->IsPrepMustFit() )
/*N*/ 				return;
/*N*/ 			// Siehe Kommentar in WidowsAndOrphans::FindOrphans und CalcPreps()
/*N*/ 			PrepWidows( *(const MSHORT *)pVoid, bNotify );
/*N*/ 			break;
/*N*/ 
/*N*/ 		case PREP_FTN :
/*N*/ 		{
/*N*/ 			SwTxtFtn *pFtn = (SwTxtFtn *)pVoid;
/*N*/ 			if( IsInFtn() )
/*N*/ 			{
/*N*/ 				// Bin ich der erste TxtFrm einer Fussnote ?
/*N*/ 				if( !GetPrev() )
/*N*/ 					// Wir sind also ein TxtFrm der Fussnote, die
/*N*/ 					// die Fussnotenzahl zur Anzeige bringen muss.
/*N*/ 					// Oder den ErgoSum-Text...
/*N*/ 					InvalidateRange( SwCharRange( 0, 1 ), 1);
/*N*/ 
/*N*/ 				if( !GetNext() )
/*N*/ 				{
/*N*/ 					// Wir sind der letzte Ftn, jetzt muessten die
/*N*/ 					// QuoVadis-Texte geupdated werden.
/*N*/ 					const SwFtnInfo &rFtnInfo = GetNode()->GetDoc()->GetFtnInfo();
/*N*/ 					if( !pPara->UpdateQuoVadis( rFtnInfo.aQuoVadis ) )
/*N*/ 					{
/*N*/ 						xub_StrLen nPos = pPara->GetParLen();
/*N*/ 						if( nPos )
/*N*/ 							--nPos;
/*N*/ 						InvalidateRange( SwCharRange( nPos, 1 ), 1);
/*N*/ 					}
/*N*/ 				}
/*N*/ 			}
/*N*/ 			else
/*N*/ 			{
/*N*/ 				// Wir sind also der TxtFrm _mit_ der Fussnote
/*N*/ 				const xub_StrLen nPos = *pFtn->GetStart();
/*N*/ 				InvalidateRange( SwCharRange( nPos, 1 ), 1);
/*N*/ 			}
/*N*/ 			break;
/*N*/ 		}
/*N*/ 		case PREP_BOSS_CHGD :
/*N*/ 		{
/*N*/     // Test
/*N*/             {
/*N*/                 SetInvalidVert( FALSE );
/*N*/                 BOOL bOld = IsVertical();
/*N*/                 SetInvalidVert( TRUE );
/*N*/                 if( bOld != IsVertical() )
/*?*/                     InvalidateRange( SwCharRange( GetOfst(), STRING_LEN ) );
/*N*/             }
/*N*/ 
/*N*/ 			if( HasFollow() )
/*N*/ 			{
/*N*/ 				xub_StrLen nNxtOfst = GetFollow()->GetOfst();
/*N*/ 				if( nNxtOfst )
/*N*/ 					--nNxtOfst;
/*N*/ 				InvalidateRange( SwCharRange( nNxtOfst, 1 ), 1);
/*N*/ 			}
/*N*/ 			if( IsInFtn() )
/*N*/ 			{
/*N*/ 				xub_StrLen nPos;
/*?*/ 				if( lcl_ErgoVadis( this, nPos, PREP_QUOVADIS ) )
/*?*/ 					InvalidateRange( SwCharRange( nPos, 1 ), 0 );
/*?*/ 				if( lcl_ErgoVadis( this, nPos, PREP_ERGOSUM ) )
/*?*/ 					InvalidateRange( SwCharRange( nPos, 1 ), 0 );
/*N*/ 			}
/*N*/ 			// 4739: Wenn wir ein Seitennummernfeld besitzen, muessen wir
/*N*/ 			// die Stellen invalidieren.
/*N*/ 			SwpHints *pHints = GetTxtNode()->GetpSwpHints();
/*N*/ 			if( pHints )
/*N*/ 			{
/*N*/ 				const MSHORT nSize = pHints->Count();
/*N*/ 				const xub_StrLen nEnd = GetFollow() ?
/*N*/ 									GetFollow()->GetOfst() : STRING_LEN;
/*N*/ 				for( MSHORT i = 0; i < nSize; ++i )
/*N*/ 				{
/*N*/ 					const SwTxtAttr *pHt = (*pHints)[i];
/*N*/ 					const xub_StrLen nStart = *pHt->GetStart();
/*N*/ 					if( nStart >= GetOfst() )
/*N*/ 					{
/*N*/ 						if( nStart >= nEnd )
/*N*/ 							i = nSize;			// fuehrt das Ende herbei
/*N*/ 						else
/*N*/ 						{
/*N*/ 				// 4029: wenn wir zurueckfliessen und eine Ftn besitzen, so
/*N*/ 				// fliesst die Ftn in jedem Fall auch mit. Damit sie nicht im
/*N*/ 				// Weg steht, schicken wir uns ein ADJUST_FRM.
/*N*/ 				// pVoid != 0 bedeutet MoveBwd()
/*N*/ 							const MSHORT nWhich = pHt->Which();
/*N*/ 							if( RES_TXTATR_FIELD == nWhich ||
/*N*/ 								(HasFtn() && pVoid && RES_TXTATR_FTN == nWhich))
/*N*/ 							InvalidateRange( SwCharRange( nStart, 1 ), 1 );
/*N*/ 						}
/*N*/ 					}
/*N*/ 				}
/*N*/ 			}
/*N*/ 			// A new boss, a new chance for growing
/*N*/ 			if( IsUndersized() )
/*N*/ 			{
/*?*/ 				_InvalidateSize();
/*?*/ 				InvalidateRange( SwCharRange( GetOfst(), 1 ), 1);
/*N*/ 			}
/*N*/ 			break;
/*N*/ 		}
/*N*/ 
/*N*/ 		case PREP_POS_CHGD :
/*N*/ 		{
/*N*/             if ( GetValidPrtAreaFlag() )
/*N*/             {
/*N*/                 GETGRID( FindPageFrm() )
/*N*/                 if ( pGrid && GetTxtNode()->GetSwAttrSet().GetParaGrid().GetValue() )
/*?*/                     InvalidatePrt();
/*N*/             }
/*N*/ 
/*N*/             // Falls wir mit niemandem ueberlappen:
/*N*/ 			// Ueberlappte irgendein Fly _vor_ der Positionsaenderung ?
/*N*/ 			sal_Bool bFormat = pPara->HasFly();
/*N*/ 			if( !bFormat )
/*N*/ 			{
/*N*/ 				if( IsInFly() )
/*N*/ 				{
/*N*/ 					SwTwips nTmpBottom = GetUpper()->Frm().Top() +
/*N*/ 						GetUpper()->Prt().Bottom();
/*N*/ 					if( nTmpBottom < Frm().Bottom() )
/*N*/ 						bFormat = sal_True;
/*N*/ 				}
/*N*/ 				if( !bFormat )
/*N*/ 				{
/*N*/ 					if ( GetDrawObjs() )
/*N*/ 					{
/*N*/ 						MSHORT nCnt = GetDrawObjs()->Count();
/*N*/ 						for ( MSHORT i = 0; i < nCnt; ++i )
/*N*/ 						{
/*N*/ 							SdrObject *pO = (*GetDrawObjs())[i];
/*N*/ 							if ( pO->IsWriterFlyFrame() )
/*N*/ 							{
/*N*/ 								SwFlyFrm *pFly = ((SwVirtFlyDrawObj*)pO)->GetFlyFrm();
/*N*/ 								if( pFly->IsAutoPos() )
/*N*/ 								{
/*?*/ 									bFormat = sal_True;
/*?*/ 									break;
/*N*/ 								}
/*N*/ 							}
/*N*/ 						}
/*N*/ 					}
/*N*/ 					if( !bFormat )
/*N*/ 					{
/*N*/ 						// Gibt es ueberhaupt Flys auf der Seite ?
/*N*/ 						SwTxtFly aTxtFly( this );
/*N*/ 						if( aTxtFly.IsOn() )
/*N*/ 						{
/*N*/ 							// Ueberlappt irgendein Fly ?
/*N*/ 							aTxtFly.Relax();
/*N*/ 							bFormat = aTxtFly.IsOn() || IsUndersized();
/*N*/ 						}
/*N*/ 					}
/*N*/ 				}
/*N*/ 			}
/*N*/ 
/*N*/ 			if( bFormat )
/*N*/ 			{
/*N*/ 				if( !IsLocked() )
/*N*/ 				{
/*N*/ 					if( pPara->GetRepaint()->HasArea() )
/*N*/ 						SetCompletePaint();
/*N*/ 					Init();
/*N*/ 					pPara = 0;
/*N*/ 					_InvalidateSize();
/*N*/ 				}
/*N*/ 			}
/*N*/ 			else
/*N*/ 			{
/*N*/ 				if( GetTxtNode()->GetSwAttrSet().GetRegister().GetValue() )
/*N*/ 					Prepare( PREP_REGISTER, 0, bNotify );
/*N*/ 				// Durch Positionsverschiebungen mit Ftns muessen die
/*N*/ 				// Frames neu adjustiert werden.
/*N*/ 				else if( HasFtn() )
/*N*/ 				{
/*N*/ 					Prepare( PREP_ADJUST_FRM, 0, bNotify );
/*N*/ 					_InvalidateSize();
/*N*/ 				}
/*N*/ 				else
/*N*/ 					return; 	// damit kein SetPrep() erfolgt.
/*N*/ 			}
/*N*/ 			break;
/*N*/ 		}
/*N*/ 		case PREP_REGISTER:
/*N*/ 			if( GetTxtNode()->GetSwAttrSet().GetRegister().GetValue() )
/*N*/ 			{
/*N*/ 				pPara->SetPrepAdjust( sal_True );
/*N*/ 				CalcLineSpace();
/*N*/ 				InvalidateSize();
/*N*/ 				_InvalidatePrt();
/*N*/ 				SwFrm* pNxt;
/*N*/ 				if ( 0 != ( pNxt = GetIndNext() ) )
/*N*/ 				{
/*N*/ 					pNxt->_InvalidatePrt();
/*N*/ 					if ( pNxt->IsLayoutFrm() )
/*N*/ 						pNxt->InvalidatePage();
/*N*/ 				}
/*N*/ 				SetCompletePaint();
/*N*/ 			}
/*N*/ 			break;
/*?*/ 		case PREP_FTN_GONE :
/*?*/ 			{
/*?*/ 				// Wenn ein Follow uns ruft, weil eine Fussnote geloescht wird, muss unsere
/*?*/ 				// letzte Zeile formatiert werden, damit ggf. die erste Zeile des Follows
/*?*/ 				// hochrutschen kann, die extra auf die naechste Seite gerutscht war, um mit
/*?*/ 				// der Fussnote zusammen zu sein, insbesondere bei spaltigen Bereichen.
/*?*/ 				ASSERT( GetFollow(), "PREP_FTN_GONE darf nur vom Follow gerufen werden" );
/*?*/ 				xub_StrLen nPos = GetFollow()->GetOfst();
/*?*/ 				if( IsFollow() && GetOfst() == nPos )       // falls wir gar keine Textmasse besitzen,
/*?*/ 					FindMaster()->Prepare( PREP_FTN_GONE ); // rufen wir das Prepare unseres Masters
/*?*/ 				if( nPos )
/*?*/ 					--nPos; // das Zeichen vor unserem Follow
/*?*/ 				InvalidateRange( SwCharRange( nPos, 1 ), 0 );
/*?*/ 				return;
/*?*/ 			}
/*N*/ 		case PREP_ERGOSUM:
/*N*/ 		case PREP_QUOVADIS:
/*N*/ 			{
/*N*/ 				xub_StrLen nPos;
/*N*/ 				if( lcl_ErgoVadis( this, nPos, ePrep ) )
/*?*/ 					InvalidateRange( SwCharRange( nPos, 1 ), 0 );
/*N*/ 			}
/*N*/ 			break;
/*N*/ 		case PREP_FLY_ATTR_CHG:
/*N*/ 		{
/*N*/ 			if( pVoid )
/*N*/ 			{
/*N*/ 				xub_StrLen nWhere = CalcFlyPos( (SwFrmFmt*)pVoid );
/*N*/ 				ASSERT( STRING_LEN != nWhere, "Prepare: Why me?" );
/*N*/ 				InvalidateRange( SwCharRange( nWhere, 1 ) );
/*N*/ 				return;
/*N*/ 			}
/*N*/ 			// else ... Laufe in den Default-Switch
/*N*/ 		}
/*N*/ 		case PREP_CLEAR:
/*N*/ 		default:
/*N*/ 		{
/*N*/ 			if( IsLocked() )
/*N*/ 			{
/*N*/ 				if( PREP_FLY_ARRIVE == ePrep || PREP_FLY_LEAVE == ePrep )
/*N*/ 				{
/*N*/ 					xub_StrLen nLen = ( GetFollow() ? GetFollow()->GetOfst() :
/*N*/ 									  STRING_LEN ) - GetOfst();
/*N*/ 					InvalidateRange( SwCharRange( GetOfst(), nLen ), 0 );
/*N*/ 				}
/*N*/ 			}
/*N*/ 			else
/*N*/ 			{
/*N*/ 				if( pPara->GetRepaint()->HasArea() )
/*N*/ 					SetCompletePaint();
/*N*/ 				Init();
/*N*/ 				pPara = 0;
/*N*/ 				if( GetOfst() && !IsFollow() )
/*?*/ 					_SetOfst( 0 );
/*N*/ 				if ( bNotify )
/*N*/ 					InvalidateSize();
/*N*/ 				else
/*N*/ 					_InvalidateSize();
/*N*/ 			}
/*N*/ 			return; 	// damit kein SetPrep() erfolgt.
/*N*/ 		}
/*N*/ 	}
/*N*/ 	if( pPara )
/*N*/ 		pPara->SetPrep( sal_True );
/*N*/ }

/* -----------------11.02.99 17:56-------------------
 * Kleine Hilfsklasse mit folgender Funktion:
 * Sie soll eine Probeformatierung vorbereiten.
 * Der Frame wird in Groesse und Position angepasst, sein SwParaPortion zur Seite
 * gestellt und eine neue erzeugt, dazu wird formatiert mit gesetztem bTestFormat.
 * Im Dtor wird der TxtFrm wieder in seinen alten Zustand zurueckversetzt.
 *
 * --------------------------------------------------*/

class SwTestFormat
{
    SwTxtFrm *pFrm;
    SwParaPortion *pOldPara;
    SwRect aOldFrm, aOldPrt;
public:
    SwTestFormat( SwTxtFrm* pTxtFrm, const SwFrm* pPrv, SwTwips nMaxHeight );
    ~SwTestFormat();
};

/*N*/ SwTestFormat::SwTestFormat( SwTxtFrm* pTxtFrm, const SwFrm* pPre, SwTwips nMaxHeight )
/*N*/ 	: pFrm( pTxtFrm )
/*N*/ {
/*N*/ 	aOldFrm = pFrm->Frm();
/*N*/ 	aOldPrt = pFrm->Prt();
/*N*/ 
/*N*/     SWRECTFN( pFrm )
/*N*/     SwTwips nLower = (pFrm->*fnRect->fnGetBottomMargin)();
/*N*/ 
/*N*/     pFrm->Frm() = pFrm->GetUpper()->Prt();
/*N*/ 	pFrm->Frm() += pFrm->GetUpper()->Frm().Pos();
/*N*/ 
/*N*/     (pFrm->Frm().*fnRect->fnSetHeight)( nMaxHeight );
/*N*/ 	if( pFrm->GetPrev() )
/*N*/         (pFrm->Frm().*fnRect->fnSetPosY)(
/*N*/                 (pFrm->GetPrev()->Frm().*fnRect->fnGetBottom)() -
/*N*/                 ( bVert ? nMaxHeight + 1 : 0 ) );
/*N*/ 
/*N*/     SwBorderAttrAccess aAccess( SwFrm::GetCache(), pFrm );
/*N*/ 	const SwBorderAttrs &rAttrs = *aAccess.Get();
/*N*/     (pFrm->Prt().*fnRect->fnSetPosX)( rAttrs.CalcLeft( pFrm ) );
/*N*/ 
/*N*/     if( pPre )
/*N*/ 	{
/*N*/ 		SwTwips nUpper = pFrm->CalcUpperSpace( &rAttrs, pPre );
/*N*/         (pFrm->Prt().*fnRect->fnSetPosY)( nUpper );
/*N*/ 	}
/*N*/     (pFrm->Prt().*fnRect->fnSetHeight)(
/*N*/         Max( 0L , (pFrm->Frm().*fnRect->fnGetHeight)() -
/*N*/                   (pFrm->Prt().*fnRect->fnGetTop)() - nLower ) );
/*N*/     (pFrm->Prt().*fnRect->fnSetWidth)(
/*N*/         (pFrm->Frm().*fnRect->fnGetWidth)() -
/*N*/         // OD 23.01.2003 #106895# - add 1st param to <SwBorderAttrs::CalcRight(..)>
/*N*/         ( rAttrs.CalcLeft( pFrm ) + rAttrs.CalcRight( pFrm ) ) );
/*N*/ 	pOldPara = pFrm->HasPara() ? pFrm->GetPara() : NULL;
/*N*/ 	pFrm->SetPara( new SwParaPortion(), sal_False );
/*N*/ 
/*N*/     ASSERT( ! pFrm->IsSwapped(), "A frame is swapped before _Format" );
/*N*/ 
/*N*/     if ( pFrm->IsVertical() )
/*?*/         pFrm->SwapWidthAndHeight();
/*N*/ 
/*N*/ 	SwTxtFormatInfo aInf( pFrm, sal_False, sal_True, sal_True );
/*N*/ 	SwTxtFormatter	aLine( pFrm, &aInf );
/*N*/ 
/*N*/ 	pFrm->_Format( aLine, aInf );
/*N*/ 
/*N*/     if ( pFrm->IsVertical() )
/*?*/         pFrm->SwapWidthAndHeight();
/*N*/ 
/*N*/     ASSERT( ! pFrm->IsSwapped(), "A frame is swapped after _Format" );
/*N*/ }

/*N*/ SwTestFormat::~SwTestFormat()
/*N*/ {
/*N*/ 	pFrm->Frm() = aOldFrm;
/*N*/ 	pFrm->Prt() = aOldPrt;
/*N*/ 	pFrm->SetPara( pOldPara );
/*N*/ }

/*N*/ sal_Bool SwTxtFrm::TestFormat( const SwFrm* pPrv, SwTwips &rMaxHeight, sal_Bool &bSplit )
/*N*/ {
/*N*/ 	PROTOCOL_ENTER( this, PROT_TESTFORMAT, 0, 0 )
/*N*/ 
/*N*/     if( IsLocked() && GetUpper()->Prt().Width() <= 0 )
/*N*/ 		return sal_False;
/*N*/ 
/*N*/ 	SwTestFormat aSave( this, pPrv, rMaxHeight );
/*N*/ 
/*N*/ 	return SwTxtFrm::WouldFit( rMaxHeight, bSplit );
/*N*/ }


/*************************************************************************
 *						SwTxtFrm::WouldFit()
 *************************************************************************/

/* SwTxtFrm::WouldFit()
 * sal_True: wenn ich aufspalten kann.
 * Es soll und braucht nicht neu formatiert werden.
 * Wir gehen davon aus, dass bereits formatiert wurde und dass
 * die Formatierungsdaten noch aktuell sind.
 * Wir gehen davon aus, dass die Framebreiten des evtl. Masters und
 * Follows gleich sind. Deswegen wird kein FindBreak() mit FindOrphans()
 * gerufen.
 * Die benoetigte Hoehe wird von nMaxHeight abgezogen!
 */

/*N*/ sal_Bool SwTxtFrm::WouldFit( SwTwips &rMaxHeight, sal_Bool &bSplit )
/*N*/ {
/*N*/     ASSERT( ! IsVertical() || ! IsSwapped(),
/*N*/             "SwTxtFrm::WouldFit with swapped frame" );
/*N*/     SWRECTFN( this );
/*N*/ 
/*N*/     if( IsLocked() )
/*N*/ 		return sal_False;
/*N*/ 
/*N*/ 	//Kann gut sein, dass mir der IdleCollector mir die gecachten
/*N*/ 	//Informationen entzogen hat.
/*N*/ 	if( !IsEmpty() )
/*N*/ 		GetFormatted();
/*N*/ 
/*N*/ 	if ( IsEmpty() )
/*N*/ 	{
/*N*/ 		bSplit = sal_False;
/*N*/         SwTwips nHeight = bVert ? Prt().SSize().Width() : Prt().SSize().Height();
/*N*/ 		if( rMaxHeight < nHeight )
/*N*/ 			return sal_False;
/*N*/ 		else
/*N*/ 		{
/*N*/ 			rMaxHeight -= nHeight;
/*N*/ 			return sal_True;
/*N*/ 		}
/*N*/ 	}
/*N*/ 
/*N*/ 	// In sehr unguenstigen Faellen kann GetPara immer noch 0 sein.
/*N*/ 	// Dann returnen wir sal_True, um auf der neuen Seite noch einmal
/*N*/ 	// anformatiert zu werden.
/*N*/ 	ASSERT( HasPara() || IsHiddenNow(), "WouldFit: GetFormatted() and then !HasPara()" );
/*N*/     if( !HasPara() || ( !(Frm().*fnRect->fnGetHeight)() && IsHiddenNow() ) )
/*N*/ 		return sal_True;
/*N*/ 
/*N*/ 	// Da das Orphan-Flag nur sehr fluechtig existiert, wird als zweite
/*N*/ 	// Bedingung  ueberprueft, ob die Rahmengroesse durch CalcPreps
/*N*/ 	// auf riesengross gesetzt wird, um ein MoveFwd zu erzwingen.
/*N*/     if( IsWidow() || ( bVert ?
/*N*/                        ( 0 == Frm().Left() ) :
/*N*/                        ( LONG_MAX - 20000 < Frm().Bottom() ) ) )
/*N*/ 	{
/*?*/ 		SetWidow(sal_False);
/*?*/ 		if ( GetFollow() )
/*?*/ 		{
/*?*/ 			// Wenn wir hier durch eine Widow-Anforderung unseres Follows gelandet
/*?*/ 			// sind, wird ueberprueft, ob es ueberhaupt einen Follow mit einer
/*?*/ 			// echten Hoehe gibt, andernfalls (z.B. in neu angelegten SctFrms)
/*?*/ 			// ignorieren wir das IsWidow() und pruefen doch noch, ob wir
/*?*/ 			// genung Platz finden.
/*?*/             if( ( ( ! bVert && LONG_MAX - 20000 >= Frm().Bottom() ) ||
/*?*/                   (   bVert && 0 < Frm().Left() ) ) &&
/*?*/                   ( GetFollow()->IsVertical() ?
/*?*/                     !GetFollow()->Frm().Width() :
/*?*/                     !GetFollow()->Frm().Height() ) )
/*?*/ 			{
/*?*/ 				SwTxtFrm* pFoll = GetFollow()->GetFollow();
/*?*/                 while( pFoll &&
/*?*/                         ( pFoll->IsVertical() ?
/*?*/                          !pFoll->Frm().Width() :
/*?*/                          !pFoll->Frm().Height() ) )
/*?*/ 					pFoll = pFoll->GetFollow();
/*?*/ 				if( pFoll )
/*?*/ 					return sal_False;
/*?*/ 			}
/*?*/ 			else
/*?*/ 				return sal_False;
/*?*/ 		}
/*N*/ 	}
/*N*/ 
/*N*/     SWAP_IF_NOT_SWAPPED( this );
/*N*/ 
/*N*/     SwTxtSizeInfo aInf( this );
/*N*/ 	SwTxtMargin aLine( this, &aInf );
/*N*/ 
/*N*/ 	WidowsAndOrphans aFrmBreak( this, rMaxHeight, bSplit );
/*N*/ 
/*N*/ 	register sal_Bool bRet = sal_True;
/*N*/ 
/*N*/ 	aLine.Bottom();
/*N*/ 	// Ist Aufspalten ueberhaupt notwendig?
/*N*/ 	if ( 0 != ( bSplit = !aFrmBreak.IsInside( aLine ) ) )
/*N*/ 		bRet = !aFrmBreak.IsKeepAlways() && aFrmBreak.WouldFit( aLine, rMaxHeight );
/*N*/ 	else
/*N*/ 	{
/*N*/ 		//Wir brauchen die Gesamthoehe inklusive der aktuellen Zeile
/*N*/ 		aLine.Top();
/*N*/ 		do
/*N*/ 		{
/*N*/ 			rMaxHeight -= aLine.GetLineHeight();
/*N*/ 		} while ( aLine.Next() );
/*N*/ 	}
/*N*/ 
/*N*/     UNDO_SWAP( this )
/*N*/ 
/*N*/     return bRet;
/*N*/ }


/*************************************************************************
 *						SwTxtFrm::GetParHeight()
 *************************************************************************/

/*N*/ KSHORT SwTxtFrm::GetParHeight() const
/*N*/ {
/*N*/     ASSERT( ! IsVertical() || ! IsSwapped(),
/*N*/             "SwTxtFrm::GetParHeight with swapped frame" )
/*N*/ 
/*N*/ 	if( !HasPara() )
/*N*/ 	{   // Fuer nichtleere Absaetze ist dies ein Sonderfall, da koennen wir
/*N*/ 		// bei UnderSized ruhig nur 1 Twip mehr anfordern.
/*N*/         KSHORT nRet = (KSHORT)Prt().SSize().Height();
/*N*/ 		if( IsUndersized() )
/*N*/ 		{
/*N*/ 			if( IsEmpty() )
/*N*/                 nRet = (KSHORT)EmptyHeight();
/*N*/ 			else
/*N*/ 				++nRet;
/*N*/ 		}
/*N*/ 		return nRet;
/*N*/ 	}
/*N*/ 
/*N*/     SWAP_IF_NOT_SWAPPED( this )
/*N*/ 
/*N*/ 	SwTxtFrm *pThis = (SwTxtFrm*)this;
/*N*/ 	SwTxtSizeInfo aInf( pThis );
/*N*/ 	SwTxtIter aLine( pThis, &aInf );
/*N*/ 	KSHORT nHeight = aLine.GetLineHeight();
/*N*/ 	if( GetOfst() && !IsFollow() )			// Ist dieser Absatz gescrollt? Dann ist unsere
/*?*/ 		nHeight += aLine.GetLineHeight();	// bisherige Hoehe mind. eine Zeilenhoehe zu gering
/*N*/ 	while( aLine.Next() )
/*N*/ 		nHeight += aLine.GetLineHeight();
/*N*/ 
/*N*/     UNDO_SWAP( this )
/*N*/ 
/*N*/ 	return nHeight;
/*N*/ }


/*************************************************************************
 *						SwTxtFrm::GetFormatted()
 *************************************************************************/

// returnt this _immer_ im formatierten Zustand!
/*N*/ SwTxtFrm *SwTxtFrm::GetFormatted()
/*N*/ {
/*N*/     SWAP_IF_SWAPPED( this )
/*N*/ 
/*N*/ 	//Kann gut sein, dass mir der IdleCollector mir die gecachten
/*N*/ 	//Informationen entzogen hat. Calc() ruft unser Format.
/*N*/ 					  //Nicht bei leeren Absaetzen!
/*N*/ 	if( !HasPara() && !(IsValid() && IsEmpty()) )
/*N*/ 	{
/*N*/ 		// Calc() muss gerufen werden, weil unsere Frameposition
/*N*/ 		// nicht stimmen muss.
/*N*/ 		const sal_Bool bFormat = GetValidSizeFlag();
/*N*/ 		Calc();
/*N*/ 		// Es kann durchaus sein, dass Calc() das Format()
/*N*/ 		// nicht anstiess (weil wir einst vom Idle-Zerstoerer
/*N*/ 		// aufgefordert wurden unsere Formatinformationen wegzuschmeissen).
/*N*/ 		// 6995: Optimierung mit FormatQuick()
/*N*/ 		if( bFormat && !FormatQuick() )
/*N*/ 			Format();
/*N*/ 	}
/*N*/ 
/*N*/     UNDO_SWAP( this )
/*N*/ 
/*N*/     return this;
/*N*/ }

/*************************************************************************
 *						SwTxtFrm::CalcFitToContent()
 *************************************************************************/

//STRIP001 KSHORT SwTxtFrm::CalcFitToContent( )
//STRIP001 {
//STRIP001 	sal_Bool bNoPara = !HasPara();
//STRIP001 	if ( bNoPara )
//STRIP001 	{
//STRIP001 		SwParaPortion *pDummy = new SwParaPortion();
//STRIP001 		SetPara( pDummy );
//STRIP001 	}
//STRIP001 
//STRIP001 	SwTxtFormatInfo aInf( this );
//STRIP001 	aInf.Right( KSHRT_MAX );
//STRIP001 	aInf.Width( KSHRT_MAX );
//STRIP001 	aInf.RealWidth( KSHRT_MAX );
//STRIP001 	aInf.SetIgnoreFly( sal_True );
//STRIP001 
//STRIP001 	SwTxtFormatter	aLine( this, &aInf );
//STRIP001 
//STRIP001     SwHookOut aHook( aInf );
//STRIP001 	KSHORT nMax = aLine._CalcFitToContent( );
//STRIP001 	if ( nMax )
//STRIP001 		nMax -= KSHORT( GetLeftMargin() );
//STRIP001 
//STRIP001 	if ( bNoPara )
//STRIP001 		ClearPara( );  // Dummy-Paraportion wieder loeschen
//STRIP001 	else
//STRIP001 		SetPara( NULL ); // Die Einzeilen-Formatinformation wegwerfen!
//STRIP001 
//STRIP001 	return nMax;
//STRIP001 }

/*************************************************************************
 *						SwTxtFrm::GetLineSpace()
 *************************************************************************/

/*N*/ KSHORT SwTxtFrm::GetLineSpace() const
/*N*/ {
/*N*/ 	KSHORT nRet = 0;
/*N*/ 	long nTmp;
/*N*/ 
/*N*/ 	const SwAttrSet* pSet = GetAttrSet();
/*N*/ 	const SvxLineSpacingItem &rSpace = pSet->GetLineSpacing();
/*N*/ 
/*N*/ 	switch( rSpace.GetInterLineSpaceRule() )
/*N*/ 	{
/*N*/ 		case SVX_INTER_LINE_SPACE_PROP:
/*N*/ 		{
/*N*/ 			ViewShell* pVsh = (ViewShell*)GetShell();
/*N*/ 			if ( !pVsh )
/*N*/ 				break;
/*N*/ 			OutputDevice *pOut = pVsh->GetOut();
/*N*/ 			if( !pVsh->GetDoc()->IsBrowseMode() ||
/*N*/ 				pVsh->GetViewOptions()->IsPrtFormat() )
/*N*/ 			{
/*N*/                 pOut = &GetTxtNode()->GetDoc()->GetRefDev();
/*N*/ 			}
/*N*/             SwFont aFont( pSet, GetTxtNode()->GetDoc() );
/*N*/ 			// Wir muessen dafuer sorgen, dass am OutputDevice der Font
/*N*/ 			// korrekt restauriert wird, sonst droht ein Last!=Owner.
/*N*/ 			if ( pLastFont )
/*N*/ 			{
/*N*/ 				SwFntObj *pOldFont = pLastFont;
/*N*/ 				pLastFont = NULL;
/*N*/ 				aFont.SetFntChg( sal_True );
/*N*/ 				aFont.ChgPhysFnt( pVsh, pOut );
/*N*/ 				nRet = aFont.GetHeight( pVsh, pOut );
/*N*/ 				pLastFont->Unlock();
/*N*/ 				pLastFont = pOldFont;
/*N*/ 				pLastFont->SetDevFont( pVsh, pOut );
/*N*/ 			}
/*N*/ 			else
/*N*/ 			{
/*?*/ 				Font aOldFont = pOut->GetFont();
/*?*/ 				aFont.SetFntChg( sal_True );
/*?*/ 				aFont.ChgPhysFnt( pVsh, pOut );
/*?*/ 				nRet = aFont.GetHeight( pVsh, pOut );
/*?*/ 				pLastFont->Unlock();
/*?*/ 				pLastFont = NULL;
/*?*/ 				pOut->SetFont( aOldFont );
/*N*/ 			}
/*N*/ 			nTmp = nRet;
/*N*/ 			nTmp *= rSpace.GetPropLineSpace();
/*N*/ 			nTmp /= 100;
/*N*/ 			nTmp -= nRet;
/*N*/ 			if ( nTmp > 0 )
/*N*/ 				nRet = (KSHORT)nTmp;
/*N*/ 			else
/*N*/ 				nRet = 0;
/*N*/ 		}
/*N*/ 			break;
/*?*/ 		case SVX_INTER_LINE_SPACE_FIX:
/*?*/ 			if ( rSpace.GetInterLineSpace() > 0 )
/*?*/ 				nRet = (KSHORT)rSpace.GetInterLineSpace();
/*N*/ 	}
/*N*/ 	return nRet;
/*N*/ }

/*************************************************************************
 *						SwTxtFrm::FirstLineHeight()
 *************************************************************************/

/*N*/ KSHORT SwTxtFrm::FirstLineHeight() const
/*N*/ {
/*N*/ 	if ( !HasPara() )
/*N*/ 	{
/*N*/ 		if( IsEmpty() && IsValid() )
/*?*/             return IsVertical() ? (KSHORT)Prt().Width() : (KSHORT)Prt().Height();
/*N*/ 		return KSHRT_MAX;
/*N*/ 	}
/*N*/ 	const SwParaPortion *pPara = GetPara();
/*N*/ 	if ( !pPara )
/*N*/ 		return KSHRT_MAX;
/*N*/ 
/*N*/ 	return pPara->Height();
/*N*/ }

//STRIP001 MSHORT SwTxtFrm::GetLineCount( xub_StrLen nPos )
//STRIP001 {
//STRIP001 	MSHORT nRet = 0;
//STRIP001     SwTxtFrm *pFrm = this;
//STRIP001     do
//STRIP001     {
//STRIP001         pFrm->GetFormatted();
//STRIP001         if( !pFrm->HasPara() )
//STRIP001             break;
//STRIP001         SwTxtSizeInfo aInf( pFrm );
//STRIP001         SwTxtMargin aLine( pFrm, &aInf );
//STRIP001         if( STRING_LEN == nPos )
//STRIP001             aLine.Bottom();
//STRIP001         else
//STRIP001             aLine.CharToLine( nPos );
//STRIP001         nRet += aLine.GetLineNr();
//STRIP001         pFrm = pFrm->GetFollow();
//STRIP001     } while ( pFrm && pFrm->GetOfst() <= nPos );
//STRIP001 	return nRet;
//STRIP001 }

/*N*/ void SwTxtFrm::ChgThisLines()
/*N*/ {
/*N*/ 	//not necassary to format here (GerFormatted etc.), because we have to come from there!
/*N*/ 
/*N*/ 	ULONG nNew = 0;
/*N*/ 	const SwLineNumberInfo &rInf = GetNode()->GetDoc()->GetLineNumberInfo();
/*N*/ 	if ( GetTxt().Len() && HasPara() )
/*N*/ 	{
/*N*/ 		SwTxtSizeInfo aInf( this );
/*N*/ 		SwTxtMargin aLine( this, &aInf );
/*N*/ 		if ( rInf.IsCountBlankLines() )
/*N*/ 		{
/*N*/ 			aLine.Bottom();
/*N*/ 			nNew = (ULONG)aLine.GetLineNr();
/*N*/ 		}
/*N*/ 		else
/*N*/ 		{
/*N*/ 			do
/*N*/ 			{
/*?*/ 				if( aLine.GetCurr()->HasCntnt() )
/*?*/ 					++nNew;
/*N*/ 			} while ( aLine.NextLine() );
/*N*/ 		}
/*N*/ 	}
/*N*/ 	else if ( rInf.IsCountBlankLines() )
/*N*/ 		nNew = 1;
/*N*/ 
/*N*/ 	if ( nNew != nThisLines )
/*N*/ 	{
/*N*/         if ( !IsInTab() && GetAttrSet()->GetLineNumber().IsCount() )
/*N*/ 		{
/*N*/ 			nAllLines -= nThisLines;
/*N*/ 			nThisLines = nNew;
/*N*/ 			nAllLines  += nThisLines;
/*N*/ 			SwFrm *pNxt = GetNextCntntFrm();
/*N*/ 			while( pNxt && pNxt->IsInTab() )
/*N*/ 			{
/*N*/ 				if( 0 != (pNxt = pNxt->FindTabFrm()) )
/*N*/ 					pNxt = pNxt->FindNextCnt();
/*N*/ 			}
/*N*/ 			if( pNxt )
/*N*/ 				pNxt->InvalidateLineNum();
/*N*/ 
/*N*/ 			//Extend repaint to the bottom.
/*N*/ 			if ( HasPara() )
/*N*/ 			{
/*N*/ 				SwRepaint *pRepaint = GetPara()->GetRepaint();
/*N*/ 				pRepaint->Bottom( Max( pRepaint->Bottom(),
/*N*/ 									   Frm().Top()+Prt().Bottom()));
/*N*/ 			}
/*N*/ 		}
/*N*/ 		else //Paragraphs which are not counted should not manipulate the AllLines.
/*N*/ 			nThisLines = nNew;
/*N*/ 	}
/*N*/ }


/*N*/ void SwTxtFrm::RecalcAllLines()
/*N*/ {
/*N*/ 	ValidateLineNum();
/*N*/ 
/*N*/ 	const SwAttrSet *pAttrSet = GetAttrSet();
/*N*/ 
/*N*/ 	if ( !IsInTab() )
/*N*/ 	{
/*N*/ 		const ULONG nOld = GetAllLines();
/*N*/ 		const SwFmtLineNumber &rLineNum = pAttrSet->GetLineNumber();
/*N*/ 		ULONG nNewNum;
/*N*/ 
/*N*/ 		if ( !IsFollow() && rLineNum.GetStartValue() && rLineNum.IsCount() )
/*?*/ 			nNewNum = rLineNum.GetStartValue() - 1;
/*N*/ 		//If it is a follow or not has not be considered if it is a restart at each page; the
/*N*/ 		//restart should also take affekt at follows.
/*N*/ 		else if ( pAttrSet->GetDoc()->GetLineNumberInfo().IsRestartEachPage() &&
/*N*/ 				  FindPageFrm()->FindFirstBodyCntnt() == this )
/*N*/ 		{
/*N*/ 			nNewNum = 0;
/*N*/ 		}
/*N*/ 		else
/*N*/ 		{
/*N*/ 			SwCntntFrm *pPrv = GetPrevCntntFrm();
/*N*/ 			while ( pPrv &&
/*N*/ 					(pPrv->IsInTab() || pPrv->IsInDocBody() != IsInDocBody()) )
/*N*/ 				pPrv = pPrv->GetPrevCntntFrm();
/*N*/ 
/*N*/ 			nNewNum = pPrv ? ((SwTxtFrm*)pPrv)->GetAllLines() : 0;
/*N*/ 		}
/*N*/ 		if ( rLineNum.IsCount() )
/*N*/ 			nNewNum += GetThisLines();
/*N*/ 
/*N*/ 		if ( nOld != nNewNum )
/*N*/ 		{
/*N*/ 			nAllLines = nNewNum;
/*N*/ 			SwCntntFrm *pNxt = GetNextCntntFrm();
/*N*/ 			while ( pNxt &&
/*N*/ 					(pNxt->IsInTab() || pNxt->IsInDocBody() != IsInDocBody()) )
/*N*/ 				pNxt = pNxt->GetNextCntntFrm();
/*N*/ 			if ( pNxt )
/*N*/ 			{
/*N*/ 				if ( pNxt->GetUpper() != GetUpper() )
/*N*/ 					pNxt->InvalidateLineNum();
/*N*/ 				else
/*N*/ 					pNxt->_InvalidateLineNum();
/*N*/ 			}
/*N*/ 		}
/*N*/ 	}
/*N*/ }

//STRIP001 void SwTxtFrm::VisitPortions( SwPortionHandler& rPH ) const
//STRIP001 {
//STRIP001     const SwParaPortion* pPara = GetPara();
//STRIP001 
//STRIP001     if( pPara )
//STRIP001     {
//STRIP001         if ( IsFollow() )
//STRIP001             rPH.Skip( GetOfst() );
//STRIP001 
//STRIP001         const SwLineLayout* pLine = pPara;
//STRIP001         while ( pLine )
//STRIP001         {
//STRIP001             const SwLinePortion* pPor = pLine->GetFirstPortion();
//STRIP001             while ( pPor )
//STRIP001             {
//STRIP001                 pPor->HandlePortion( rPH );
//STRIP001                 pPor = pPor->GetPortion();
//STRIP001             }
//STRIP001 
//STRIP001             rPH.LineBreak();
//STRIP001             pLine = pLine->GetNext();
//STRIP001         }
//STRIP001     }
//STRIP001 
//STRIP001     rPH.Finish();
//STRIP001 }


/*************************************************************************
 *                      SwTxtFrm::GetScriptInfo()
 *************************************************************************/

/*N*/ const SwScriptInfo* SwTxtFrm::GetScriptInfo() const
/*N*/ {
/*N*/     const SwParaPortion* pPara = GetPara();
/*N*/     return pPara ? &pPara->GetScriptInfo() : 0;
/*N*/ }

/*************************************************************************
 *                      lcl_CalcFlyBasePos()
 * Helper function for SwTxtFrm::CalcBasePosForFly()
 *************************************************************************/

SwTwips lcl_CalcFlyBasePos( const SwTxtFrm& rFrm, SwRect aFlyRect,
                            SwTxtFly& rTxtFly )
{
    SWRECTFN( (&rFrm) )
    SwTwips nRet = rFrm.IsRightToLeft() ?
                   (rFrm.Frm().*fnRect->fnGetRight)() :
                   (rFrm.Frm().*fnRect->fnGetLeft)();

    do
    {
        SwRect aRect = rTxtFly.GetFrm( aFlyRect );
        if ( 0 != (aRect.*fnRect->fnGetWidth)() )
        {
            if ( rFrm.IsRightToLeft() )
            {
                if ( (aRect.*fnRect->fnGetRight)() -
                     (aFlyRect.*fnRect->fnGetRight)() >= 0 )
                {
                    (aFlyRect.*fnRect->fnSetRight)(
                        (aRect.*fnRect->fnGetLeft)() );
                    nRet = (aRect.*fnRect->fnGetLeft)();
                }
                else
                    break;
            }
            else
            {
                if ( (aFlyRect.*fnRect->fnGetLeft)() -
                     (aRect.*fnRect->fnGetLeft)() >= 0 )
                {
                    (aFlyRect.*fnRect->fnSetLeft)(
                        (aRect.*fnRect->fnGetRight)() + 1 );
                    nRet = (aRect.*fnRect->fnGetRight)();
                }
                else
                    break;
            }
        }
        else
            break;
    }
    while ( sal_True );

    return nRet;
}

/*************************************************************************
 *                      SwTxtFrm::CalcBasePosForFly()
 *************************************************************************/

void SwTxtFrm::CalcBaseOfstForFly()
{
    ASSERT( !IsVertical() || !IsSwapped(),
            "SwTxtFrm::CalcBasePosForFly with swapped frame!" )

    const SwNode* pNode = GetTxtNode();
    const SwDoc* pDoc = pNode->GetDoc();
    if ( !pDoc->IsAddFlyOffsets() )
        return;

    SWRECTFN( this )

    SwTwips nTop = 0;
    SwTwips nLineHeight = 200;
    SwRect aFlyRect( Frm().Pos() + Prt().Pos(), Prt().SSize() );

    // Get first 'real' line
    const SwLineLayout* pLay = GetPara();
    while( pLay && pLay->IsDummy() )
    {
        nTop += pLay->Height();
        pLay = pLay->GetNext();
    }
    if ( pLay )
        nLineHeight = pLay->Height();

    SwTwips nNewTop = (aFlyRect.*fnRect->fnGetTop)() +
                      ( bVert ? -nTop : nTop );
    (aFlyRect.*fnRect->fnSetTopAndHeight)( nNewTop, nLineHeight );

    SwTxtFly aTxtFly( this );
    aTxtFly.SetIgnoreCurrentFrame( sal_True );
    aTxtFly.SetIgnoreContour( sal_True );
    SwTwips nRet1 = lcl_CalcFlyBasePos( *this, aFlyRect, aTxtFly );
    aTxtFly.SetIgnoreCurrentFrame( sal_False );
    SwTwips nRet2 = lcl_CalcFlyBasePos( *this, aFlyRect, aTxtFly );

    // make values relative to frame start position
    SwTwips nLeft = IsRightToLeft() ?
                    (Frm().*fnRect->fnGetRight)() :
                    (Frm().*fnRect->fnGetLeft)();

    mnFlyAnchorOfst = nRet1 - nLeft;
    mnFlyAnchorOfstNoWrap = nRet2 - nLeft;
}

}
