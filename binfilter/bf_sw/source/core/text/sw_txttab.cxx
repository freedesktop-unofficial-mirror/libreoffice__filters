/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: sw_txttab.cxx,v $
 *
 *  $Revision: 1.5 $
 *
 *  last change: $Author: rt $ $Date: 2005-09-09 02:34:28 $
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

#include "hintids.hxx"

#ifndef _SVX_LRSPITEM_HXX //autogen
#include <bf_svx/lrspitem.hxx>
#endif
#ifndef _SVX_TSTPITEM_HXX //autogen
#include <bf_svx/tstpitem.hxx>
#endif

#ifndef _FRMATR_HXX
#include <frmatr.hxx>
#endif
// auto strip #ifndef _SW_PORTIONHANDLER_HXX
// auto strip #include <SwPortionHandler.hxx>
// auto strip #endif

// auto strip #include "viewopt.hxx"	// SwViewOptions
#include "txtcfg.hxx"
#include "portab.hxx"
// auto strip #include "inftxt.hxx"
#include "itrform2.hxx"
// auto strip #include "txtfrm.hxx"
namespace binfilter {


/*************************************************************************
 *                    SwLineInfo::GetTabStop()
 *************************************************************************/

/* Die Werte in SvxTabStop::nTabPos liegen immer relativ zum linken PrtRand
 * vor. Tabs, die im Bereich des Erstzeileneinzugs liegen, sind also negativ.
 * nLeft  ist der linke PrtRand
 * nRight ist der rechte PrtRand
 * nLinePos die aktuelle Position.
 * Es wird der erste Tabstop returnt, der groesser ist als nLinePos.
 */



/*N*/ const SvxTabStop *SwLineInfo::GetTabStop( const SwTwips nLinePos,
/*N*/ 	const SwTwips nLeft, const SwTwips nRight ) const
/*N*/ {
/*N*/ 	// Mit den KSHORTs aufpassen, falls nLinePos < nLeft
/*N*/ 	SwTwips nPos = nLinePos;
/*N*/ 	nPos -= nLeft;
/*N*/ 	for( MSHORT i = 0; i < pRuler->Count(); ++i )
/*N*/ 	{
/*N*/ 		const SvxTabStop &rTabStop = pRuler->operator[](i);
/*N*/ 		if( rTabStop.GetTabPos() > SwTwips(nRight) )
/*N*/ 		{
/*N*/ 			if ( i )
/*N*/ 				return 0;
/*N*/ 			else
/*N*/ 				return &rTabStop;
/*N*/ 		}
/*N*/ 		if( rTabStop.GetTabPos() > nPos )
/*N*/ 			return &rTabStop;
/*N*/ 	}
/*N*/ 	return 0;
/*N*/ }

/*************************************************************************
 *                      SwTxtFormatter::NewTabPortion()
 *************************************************************************/



/*N*/ SwTabPortion *SwTxtFormatter::NewTabPortion( SwTxtFormatInfo &rInf ) const
/*N*/ {
/*N*/ 	SwTabPortion *pTabPor;
/*N*/ 	SwTabPortion  *pLastTab = rInf.GetLastTab();
/*N*/ 	if( pLastTab && pLastTab->IsTabCntPortion() )
/*N*/ 		if( pLastTab->PostFormat( rInf ) )
/*N*/ 			return 0;
/*N*/ 
/*N*/ 	// Wir suchen den naechsten Tab. Wenn gerade ein rechts-Tab unterwegs
/*N*/ 	// ist, so koennen wir uns nicht auf rInf.X() beziehen.
/*N*/ 	KSHORT nTabPos = rInf.GetLastTab() ? rInf.GetLastTab()->GetTabPos() : 0;
/*N*/ 	if( nTabPos < rInf.X() )
/*N*/ 		nTabPos = rInf.X();
/*N*/ 
/*N*/ 	xub_Unicode cFill, cDec;
/*N*/ 	SvxTabAdjust eAdj;
/*N*/ 
/*N*/ 	KSHORT nNewTabPos;
/*N*/ 	{
        /*
         nPos ist der Offset in der Zeile.
         Die Tabulatoren haben ihren 0-Punkt bei Frm().Left().
         Die Zeilen beginnen ab Frm.Left() + Prt.Left().
         In dieser Methode wird zwischen beiden Koordinatensystemen
         konvertiert (vgl. rInf.GetTabPos).
        */
/*N*/ 		const SwTwips nTabLeft = pFrm->Frm().Left() +
/*N*/                                  ( pFrm->IsRightToLeft() ?
/*N*/                                    pFrm->GetAttrSet()->GetLRSpace().GetRight() :
/*N*/                                    pFrm->GetAttrSet()->GetLRSpace().GetTxtLeft() );
/*N*/ 
/*N*/ 		const SwTwips nLinePos = GetLeftMargin();
/*N*/ 		const SwTwips nLineTab = nLinePos + nTabPos;
/*N*/         SwTwips nRight = Right();
/*N*/ 
/*N*/         if ( pFrm->IsVertical() )
/*N*/         {
/*N*/             Point aRightTop( nRight, pFrm->Frm().Top() );
/*N*/             pFrm->SwitchHorizontalToVertical( aRightTop );
/*N*/             nRight = aRightTop.Y();
/*N*/         }
/*N*/ 
/*N*/ 		SwTwips nNextPos;
/*N*/ 		const SvxTabStop* pTabStop =
/*N*/ 			aLineInf.GetTabStop( nLineTab, nTabLeft, nRight );
/*N*/ 		if( pTabStop )
/*N*/ 		{
/*N*/ 			cFill = ' ' != pTabStop->GetFill() ? pTabStop->GetFill() : 0;
/*N*/ 			cDec = pTabStop->GetDecimal();
/*N*/ 			eAdj = pTabStop->GetAdjustment();
/*N*/ 			nNextPos = pTabStop->GetTabPos();
/*N*/ 		}
/*N*/ 		else
/*N*/ 		{
/*N*/ 			KSHORT nDefTabDist = aLineInf.GetDefTabStop();
/*N*/ 			if( KSHRT_MAX == nDefTabDist )
/*N*/ 			{
/*N*/ 				const SvxTabStopItem& rTab =
/*N*/ 					(const SvxTabStopItem &)pFrm->GetAttrSet()->
/*N*/ 					GetPool()->GetDefaultItem( RES_PARATR_TABSTOP );
/*N*/ 				if( rTab.Count() )
/*N*/ 					nDefTabDist = (KSHORT)rTab.GetStart()->GetTabPos();
/*N*/ 				else
/*N*/ 					nDefTabDist = SVX_TAB_DEFDIST;
/*N*/ 				aLineInf.SetDefTabStop( nDefTabDist );
/*N*/ 			}
/*N*/ 			SwTwips	nCount = nLineTab;
/*N*/ 			nCount -= nTabLeft;
/*N*/ 			// Bei negativen Werten rundet "/" auf, "%" liefert negative Reste,
/*N*/ 			// bei positiven Werten rundet "/" ab, "%" liefert positvie Reste!
/*N*/ 			KSHORT nPlus = nCount < 0 ? 0 : 1;
/*N*/ 			nCount /= nDefTabDist;
/*N*/ 			nNextPos = ( nCount + nPlus ) * nDefTabDist ;
/*N*/ 			if( nNextPos + nTabLeft <= nLineTab + 50 )
/*N*/ 				nNextPos += nDefTabDist;
/*N*/ 			cFill = 0;
/*N*/ 			eAdj = SVX_TAB_ADJUST_LEFT;
/*N*/ 		}
/*N*/ 		long nForced = 0;
/*N*/ 		if( pCurr->HasForcedLeftMargin() )
/*N*/ 		{
/*?*/ 			SwLinePortion* pPor = pCurr->GetPortion();
/*?*/ 			while( pPor && !pPor->IsFlyPortion() )
/*?*/ 				pPor = pPor->GetPortion();
/*?*/ 			if( pPor )
/*?*/ 				nForced = pPor->Width();
/*N*/ 		}
/*N*/ 		if( nTabLeft + nForced > nLineTab && nNextPos > 0 )
/*N*/ 		{
/*N*/ 			eAdj = SVX_TAB_ADJUST_DEFAULT;
/*N*/ 			cFill = 0;
/*N*/ 			nNextPos = nForced;
/*N*/ 		}
/*N*/ 		nNextPos += nTabLeft;
/*N*/ 		nNextPos -= nLinePos;
/*N*/ 		ASSERT( nNextPos >= 0, "GetTabStop: Don't go back!" );
/*N*/ 		nNewTabPos = KSHORT(nNextPos);
/*N*/ 	}
/*N*/ 
/*N*/ 	switch( eAdj )
/*N*/ 	{
/*N*/ 		case SVX_TAB_ADJUST_RIGHT :
/*N*/ 		{
/*N*/ 			pTabPor = new SwTabRightPortion( nNewTabPos, cFill );
/*N*/ 			break;
/*N*/ 		}
/*N*/ 		case SVX_TAB_ADJUST_CENTER :
/*N*/ 		{
/*N*/ 			pTabPor = new SwTabCenterPortion( nNewTabPos, cFill );
/*N*/ 			break;
/*N*/ 		}
/*N*/ 		case SVX_TAB_ADJUST_DECIMAL :
/*N*/ 		{
/*?*/ 			pTabPor = new SwTabDecimalPortion( nNewTabPos, cDec, cFill );
/*?*/ 			break;
/*N*/ 		}
/*N*/ 		default:
/*N*/ 		{
/*N*/ 			ASSERT( SVX_TAB_ADJUST_LEFT == eAdj || SVX_TAB_ADJUST_DEFAULT == eAdj,
/*N*/ 					"+SwTxtFormatter::NewTabPortion: unknown adjustment" );
/*N*/ 			pTabPor = new SwTabLeftPortion( nNewTabPos, cFill );
/*N*/ 			break;
/*N*/ 		}
/*N*/ 	}
/*N*/ 
/*N*/ 	// Vorhandensein von Tabulatoren anzeigen ... ist nicht mehr noetig
/*N*/ 	// pCurr->SetTabulation();
/*N*/ 	// Aus Sicherheitsgruenden lassen wir uns die Daten errechnen
/*N*/ 	// pTabPor->Height( pLast->Height() );
/*N*/ 	// pTabPor->SetAscent( pLast->GetAscent() );
/*N*/ 	return pTabPor;
/*N*/ }

/*************************************************************************
 *                SwTabPortion::SwTabPortion()
 *************************************************************************/

// Die Basisklasse wird erstmal ohne alles initialisiert.


/*N*/ SwTabPortion::SwTabPortion( const KSHORT nTabPos, const xub_Unicode cFill )
/*N*/ 	: SwFixPortion( 0, 0 ), nTabPos(nTabPos), cFill(cFill)
/*N*/ {
/*N*/ 	nLineLength = 1;
/*N*/ #ifndef PRODUCT
/*N*/ 	if( IsFilled() )
/*N*/ 	{
/*N*/ 		ASSERT( ' ' != cFill, "SwTabPortion::CTOR: blanks ?!" );
/*N*/ 	}
/*N*/ #endif
/*N*/ 	SetWhichPor( POR_TAB );
/*N*/ }

/*************************************************************************
 *                 virtual SwTabPortion::Format()
 *************************************************************************/



/*N*/ sal_Bool SwTabPortion::Format( SwTxtFormatInfo &rInf )
/*N*/ {
/*N*/ 	SwTabPortion *pLastTab = rInf.GetLastTab();
/*N*/ 	if( pLastTab == this )
/*?*/ 		return PostFormat( rInf );
/*N*/ 	if( pLastTab )
/*?*/ 		pLastTab->PostFormat( rInf );
/*N*/ 	return PreFormat( rInf );
/*N*/ }

/*************************************************************************
 *                 virtual SwTabPortion::FormatEOL()
 *************************************************************************/



/*N*/ void SwTabPortion::FormatEOL( SwTxtFormatInfo &rInf )
/*N*/ {
/*N*/ 	if( rInf.GetLastTab() == this && !IsTabLeftPortion() )
/*N*/ 		PostFormat( rInf );
/*N*/ }

/*************************************************************************
 *                    SwTabPortion::PreFormat()
 *************************************************************************/



/*M*/ sal_Bool SwTabPortion::PreFormat( SwTxtFormatInfo &rInf )
/*M*/ {
/*M*/ 	ASSERT( rInf.X() <= GetTabPos(), "SwTabPortion::PreFormat: rush hour" );
/*M*/ 
/*M*/ 	// Hier lassen wir uns nieder...
/*M*/ 	Fix( rInf.X() );
/*M*/ 
/*M*/ 	// Die Mindestbreite eines Tabs ist immer mindestens ein Blank
/*M*/ 	{
/*M*/ 		XubString aTmp( ' ' );
/*M*/ 		SwTxtSizeInfo aInf( rInf, aTmp );
/*M*/ 		PrtWidth( aInf.GetTxtSize().Width() );
/*M*/ 	}
/*M*/ 
/*M*/ 	// 8532: CenterTabs, deren Blankbreite nicht mehr in die Zeile passt
/*M*/ 	sal_Bool bFull = rInf.Width() <= rInf.X() + PrtWidth();
/*M*/ 
/*M*/     // #95477# Rotated tab stops get the width of one blank
/*N*/     const USHORT nDir = rInf.GetFont()->GetOrientation( rInf.GetTxtFrm()->IsVertical() );
/*M*/ 
/*M*/     if( ! bFull && 0 == nDir )
/*M*/ 	{
/*M*/ 		const MSHORT nWhich = GetWhichPor();
/*M*/ 		switch( nWhich )
/*M*/ 		{
/*M*/ 			case POR_TABRIGHT:
/*M*/ 			case POR_TABDECIMAL:
/*M*/ 			case POR_TABCENTER:
/*M*/ 			{
/*M*/ 				if( POR_TABDECIMAL == nWhich )
/*M*/ 					rInf.SetTabDecimal(
/*M*/ 						((SwTabDecimalPortion*)this)->GetTabDecimal());
/*M*/ 				rInf.SetLastTab( this );
/*M*/ 				break;
/*M*/ 			}
/*M*/ 			case POR_TABLEFT:
/*M*/ 			{
/*M*/                 PrtWidth( GetTabPos() - rInf.X() );
/*M*/ 				bFull = rInf.Width() <= rInf.X() + PrtWidth();
/*M*/ 				break;
/*M*/ 			}
/*M*/ 			default: ASSERT( !this, "SwTabPortion::PreFormat: unknown adjustment" );
/*M*/ 		}
/*M*/ 	}
/*M*/ 
/*M*/ 	if( bFull )
/*M*/ 	{
/*M*/ 		// Wir muessen aufpassen, dass wir nicht endlos schleifen,
/*M*/ 		// wenn die Breite kleiner ist, als ein Blank ...
/*M*/ 		if( rInf.GetIdx() == rInf.GetLineStart() )
/*M*/ 		{
/*M*/ 			PrtWidth( rInf.Width() - rInf.X() );
/*M*/ 			SetFixWidth( PrtWidth() );
/*M*/ 		}
/*M*/ 		else
/*M*/ 		{
/*M*/ 			Height( 0 );
/*M*/ 			Width( 0 );
/*M*/ 			SetLen( 0 );
/*M*/ 			SetAscent( 0 );
/*M*/ 			SetPortion( NULL ); //?????
/*M*/ 		}
/*M*/ 		return sal_True;
/*M*/ 	}
/*M*/ 	else
/*M*/ 	{
/*M*/ 		// Ein Kunstgriff mit Effekt: Die neuen Tabportions verhalten sich nun
/*M*/ 		// so, wie FlyFrms, die in der Zeile stehen - inklusive Adjustment !
/*M*/ 		SetFixWidth( PrtWidth() );
/*M*/ 		return sal_False;
/*M*/ 	}
/*M*/ }

/*************************************************************************
 *                      SwTabPortion::PostFormat()
 *************************************************************************/



/*N*/ sal_Bool SwTabPortion::PostFormat( SwTxtFormatInfo &rInf )
/*N*/ {
/*N*/ 	const KSHORT nRight = Min( GetTabPos(), rInf.Width() );
/*N*/ 	const SwLinePortion *pPor = GetPortion();
/*N*/ 	KSHORT nPorWidth = 0;
/*N*/ 	while( pPor )
/*N*/ 	{
///*N*/ 		DBG_LOOP;
/*N*/ 		nPorWidth += pPor->Width();
/*N*/ 		pPor = pPor->GetPortion();
/*N*/ 	}
/*N*/ 
/*N*/ 	const MSHORT nWhich = GetWhichPor();
/*N*/ 	ASSERT( POR_TABLEFT != nWhich, "SwTabPortion::PostFormat: already formatted" );
/*N*/ 	const KSHORT nDiffWidth = nRight - Fix();
/*N*/ 
/*N*/ 	if( POR_TABCENTER == nWhich )
/*N*/ 	{
/*N*/ 		// zentrierte Tabs bereiten Probleme:
/*N*/ 		// Wir muessen den Anteil herausfinden, der noch auf die Zeile passt.
/*N*/ 		KSHORT nNewWidth = nPorWidth /2;
/*N*/ 		if( nNewWidth > rInf.Width() - nRight )
/*?*/ 			nNewWidth = nPorWidth - (rInf.Width() - nRight);
/*N*/ 		nPorWidth = nNewWidth;
/*N*/ 	}
/*N*/ 
/*N*/ 	if( nDiffWidth > nPorWidth )
/*N*/ 	{
/*N*/ 		const KSHORT nOldWidth = GetFixWidth();
/*N*/ 		const KSHORT nAdjDiff = nDiffWidth - nPorWidth;
/*N*/ 		if( nAdjDiff > GetFixWidth() )
/*N*/ 			PrtWidth( nAdjDiff );
/*N*/ 		// Nicht erschrecken: wir muessen rInf weiterschieben.
/*N*/ 		// Immerhin waren wir als Rechtstab bislang nur ein Blank breit.
/*N*/ 		// Da wir uns jetzt aufgespannt haben, muss der Differenzbetrag
/*N*/ 		// auf rInf.X() addiert werden !
/*N*/ 		rInf.X( rInf.X() + PrtWidth() - nOldWidth );
/*N*/ 	}
/*N*/ 	SetFixWidth( PrtWidth() );
/*N*/ 	// letzte Werte zuruecksetzen
/*N*/ 	rInf.SetLastTab(0);
/*N*/ 	if( POR_TABDECIMAL == nWhich )
/*?*/ 		rInf.SetTabDecimal(0);
/*N*/ 
/*N*/ 	return rInf.Width() <= rInf.X();
/*N*/ }

/*************************************************************************
 *                virtual SwTabPortion::Paint()
 *
 * Ex: LineIter::DrawTab()
 *************************************************************************/



//STRIP001 void SwTabPortion::Paint( const SwTxtPaintInfo &rInf ) const
//STRIP001 {
//STRIP001 #ifndef PRODUCT
//STRIP001 	// Wir wollen uns die Fixbreite anzeigen
//STRIP001     if( rInf.OnWin() && OPTDBG( rInf ) &&
//STRIP001         !rInf.GetOpt().IsPagePreview() && \
//STRIP001         !rInf.GetOpt().IsReadonly() && \
//STRIP001         SwViewOption::IsFieldShadings()    )
//STRIP001 	{
//STRIP001 		const KSHORT nWidth = PrtWidth();
//STRIP001 		((SwTabPortion*)this)->PrtWidth( GetFixWidth() );
//STRIP001 		rInf.DrawViewOpt( *this, POR_TAB );
//STRIP001 		((SwTabPortion*)this)->PrtWidth( nWidth );
//STRIP001 	}
//STRIP001 #endif
//STRIP001 
//STRIP001 	rInf.DrawBackBrush( *this );
//STRIP001 
//STRIP001     // do we have to repaint a post it portion?
//STRIP001     if( rInf.OnWin() && pPortion && !pPortion->Width() )
//STRIP001         pPortion->PrePaint( rInf, this );
//STRIP001 
//STRIP001     // Darstellung von Sonderzeichen
//STRIP001 	if( rInf.OnWin() && rInf.GetOpt().IsTab() )
//STRIP001 	{
//STRIP001 		// gefuellte Tabs werden grau hinterlegt.
//STRIP001 		if( IsFilled() )
//STRIP001 			rInf.DrawViewOpt( *this, POR_TAB );
//STRIP001 		else
//STRIP001 			rInf.DrawTab( *this );
//STRIP001 	}
//STRIP001 
//STRIP001 	// 6842: Tabs sollen auf einmal wieder unterstrichen werden.
//STRIP001 	if( rInf.GetFont()->IsPaintBlank() )
//STRIP001 	{
//STRIP001 		// Tabs mit Fuellung
//STRIP001 		XubString aTxt( ' ' );
//STRIP001 		const KSHORT nCharWidth = rInf.GetTxtSize( aTxt ).Width();
//STRIP001 		// robust:
//STRIP001 		if( nCharWidth )
//STRIP001 		{
//STRIP001 			// 6864: immer mit Kerning, auch auf dem Drucker!
//STRIP001 			KSHORT nChar = Width() / nCharWidth;
//STRIP001 			rInf.DrawText( aTxt.Fill( nChar, ' ' ), *this, 0, nChar, sal_True );
//STRIP001 		}
//STRIP001 	}
//STRIP001 
//STRIP001 	// Ausgabe von Fuellzeichen
//STRIP001 	if( IsFilled() )
//STRIP001 	{
//STRIP001 		// Tabs mit Fuellung
//STRIP001 		XubString aTxt( cFill );
//STRIP001 		const KSHORT nCharWidth = rInf.GetTxtSize( aTxt ).Width();
//STRIP001 #if OSL_DEBUG_LEVEL > 1
//STRIP001 		ASSERT( nCharWidth, "!SwTabPortion::Paint: sophisticated tabchar" );
//STRIP001 #endif
//STRIP001 		// robust:
//STRIP001 		if( nCharWidth )
//STRIP001 		{
//STRIP001 			// 6864: immer mit Kerning, auch auf dem Drucker!
//STRIP001 			KSHORT nChar = Width() / nCharWidth;
//STRIP001 			if ( cFill == '_' )
//STRIP001 				++nChar; // damit keine Luecken entstehen (Bug 13430)
//STRIP001 			rInf.DrawText( aTxt.Fill( nChar, cFill ), *this, 0, nChar, sal_True );
//STRIP001 		}
//STRIP001 	}
//STRIP001 }

/*************************************************************************
 *              virtual SwTabPortion::HandlePortion()
 *************************************************************************/

//STRIP001 void SwTabPortion::HandlePortion( SwPortionHandler& rPH ) const
//STRIP001 {
//STRIP001     rPH.Text( GetLen(), GetWhichPor() );
//STRIP001 }

}
