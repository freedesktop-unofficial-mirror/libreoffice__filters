/*************************************************************************
 *
 *  $RCSfile: sw_ndhints.cxx,v $
 *
 *  $Revision: 1.3 $
 *
 *  last change: $Author: aw $ $Date: 2004-04-19 10:23:03 $
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

#include "txatbase.hxx"
#include "ndhints.hxx"
namespace binfilter {

/*N*/ _SV_IMPL_SORTAR_ALG( SwpHtStart, SwTxtAttr* )
/*N*/ _SV_IMPL_SORTAR_ALG( SwpHtEnd, SwTxtAttr* )

#ifdef NIE

/*N*/ void DumpHints( const SwpHtStart &rHtStart,
/*N*/ 				const SwpHtEnd &rHtEnd )
/*N*/ {
#ifndef PRODUCT
        DBG_ASSERT(0, "STRIP");//STRIP001 	aDbstream << "DumpHints:" << endl;
//STRIP001 	(aDbstream << "\tStarts:" ).WriteNumber(rHtStart.Count()) << endl;
//STRIP001 	for( USHORT i = 0; i < rHtStart.Count(); ++i )
//STRIP001 	{
//STRIP001 		const SwTxtAttr *pHt = rHtStart[i];
//STRIP001 		((((aDbstream << '\t').WriteNumber( i )<< " [").WriteNumber( pHt->Which() )
//STRIP001 			<< ']' << '\t').WriteNumber( long( pHt ) )
//STRIP001 				  << '\t').WriteNumber( *pHt->GetStart() );
//STRIP001 		if( pHt->GetEnd() )
//STRIP001 			(aDbstream << " -> " ).WriteNumber( *pHt->GetEnd() );
//STRIP001 		aDbstream << endl;
//STRIP001 	}
//STRIP001 	(aDbstream << "\tEnds:").WriteNumber( rHtEnd.Count() )<< endl;
//STRIP001 	for( i = 0; i < rHtEnd.Count(); ++i )
//STRIP001 	{
//STRIP001 		const SwTxtAttr *pHt = rHtEnd[i];
//STRIP001 		(((aDbstream << '\t').WriteNumber( i )<< " [").WriteNumber( pHt->Which() )
//STRIP001 			<< ']' << '\t' ).WriteNumber( long( pHt ) );
//STRIP001 		if( pHt->GetEnd() )
//STRIP001 			(aDbstream << '\t').WriteNumber( *pHt->GetEnd() )<< " <- ";
//STRIP001 		aDbstream.WriteNumber( *pHt->GetStart() )<< endl;
//STRIP001 	}
//STRIP001 	aDbstream << endl;
/*N*/ #endif
/*N*/ }
/*N*/ #else
/*N*/ inline void DumpHints(const SwpHtStart &, const SwpHtEnd &) { }
/*N*/ #endif

/*************************************************************************
 *                        inline IsEqual()
 *************************************************************************/

/*N*/ inline BOOL IsEqual( const SwTxtAttr &rHt1, const SwTxtAttr &rHt2 )
/*N*/ {
/*N*/ 	return (long)(&rHt1) == (long)(&rHt2);
/*N*/ }

/*************************************************************************
 *                      IsLessStart()
 *************************************************************************/

// SV_IMPL_OP_PTRARR_SORT( SwpHtStart, SwTxtAttr* )
// kein SV_IMPL_PTRARR_SORT( name,ArrElement )
// unser SEEK_PTR_TO_OBJECT_NOTL( name,ArrElement )

// Sortierreihenfolge: Start, Ende (umgekehrt!), Which-Wert (umgekehrt!),
// 					   als letztes die Adresse selbst

/*N*/ BOOL lcl_IsLessStart( const SwTxtAttr &rHt1, const SwTxtAttr &rHt2 )
/*N*/ {
/*N*/ 	if ( *rHt1.GetStart() == *rHt2.GetStart() )
/*N*/ 	{
/*N*/ 		xub_StrLen nHt1 = *rHt1.GetAnyEnd();
/*N*/ 		xub_StrLen nHt2 = *rHt2.GetAnyEnd();
/*N*/ 		if ( nHt1 == nHt2 )
/*N*/ 		{
/*N*/ 			nHt1 = rHt1.Which();
/*N*/ 			nHt2 = rHt2.Which();
/*N*/ 			return nHt1 > nHt2 ||
/*N*/ 				(nHt1 == nHt2 && (long)&rHt1 < (long)&rHt2);
/*N*/ 		}
/*N*/ 		else
/*N*/ 			return ( nHt1 > nHt2 );
/*N*/ 	}
/*N*/ 	return ( *rHt1.GetStart() < *rHt2.GetStart() );
/*N*/ }

/*************************************************************************
 *                      inline IsLessEnd()
 *************************************************************************/

// Zuerst nach Ende danach nach Ptr
/*N*/ #ifdef HP9000
/*N*/ BOOL lcl_IsLessEnd( const SwTxtAttr &rHt1, const SwTxtAttr &rHt2 )
/*N*/ #else
/*N*/ inline BOOL lcl_IsLessEnd( const SwTxtAttr &rHt1, const SwTxtAttr &rHt2 )
/*N*/ #endif
/*N*/ {
/*N*/ 	xub_StrLen nHt1 = *rHt1.GetAnyEnd();
/*N*/ 	xub_StrLen nHt2 = *rHt2.GetAnyEnd();
/*N*/ 	if ( nHt1 == nHt2 )
/*N*/ 	{
/*N*/ 		if ( *rHt1.GetStart() == *rHt2.GetStart() )
/*N*/ 		{
/*N*/ 			nHt1 = rHt1.Which();
/*N*/ 			nHt2 = rHt2.Which();
/*N*/ 			return nHt1 < nHt2 ||
/*N*/ 				(nHt1 == nHt2 && (long)&rHt1 > (long)&rHt2);
/*N*/ 		}
/*N*/ 		else
/*N*/ 			return ( *rHt1.GetStart() > *rHt2.GetStart() );
/*N*/ 	}
/*N*/ 	return ( nHt1 < nHt2 );
/*N*/ }

/*************************************************************************
 *                      SwpHtStart::Seek_Entry()
 *************************************************************************/

/*N*/ BOOL SwpHtStart::Seek_Entry( const SwTxtAttr *pElement, USHORT *pPos ) const
/*N*/ {
/*N*/ 	register USHORT nOben = Count(), nMitte, nUnten = 0;
/*N*/ 	if( nOben > 0 )
/*N*/ 	{
/*N*/ 		nOben--;
/*N*/ 		while( nUnten <= nOben )
/*N*/ 		{
/*N*/ 			nMitte = nUnten + ( nOben - nUnten ) / 2;
/*N*/ 			const SwTxtAttr *pMitte = (*this)[nMitte];
/*N*/ 			if( IsEqual( *pMitte, *pElement ) )
/*N*/ 			{
/*N*/ 				*pPos = nMitte;
/*N*/ 				return TRUE;
/*N*/ 			}
/*N*/ 			else
/*N*/ 				if( lcl_IsLessStart( *pMitte, *pElement ) )
/*N*/ 					nUnten = nMitte + 1;
/*N*/ 				else
/*N*/ 					if( nMitte == 0 )
/*N*/ 					{
/*N*/ 						*pPos = nUnten;
/*N*/ 						return FALSE;
/*N*/ 					}
/*N*/ 					else
/*N*/ 						nOben = nMitte - 1;
/*N*/ 		}
/*N*/ 	}
/*N*/ 	*pPos = nUnten;
/*N*/ 	return FALSE;
/*N*/ }

/*************************************************************************
 *                      SwpHtEnd::Seek_Entry()
 *************************************************************************/

/*N*/ BOOL SwpHtEnd::Seek_Entry( const SwTxtAttr *pElement, USHORT *pPos ) const
/*N*/ {
/*N*/ 	register USHORT nOben = Count(), nMitte, nUnten = 0;
/*N*/ 	if( nOben > 0 )
/*N*/ 	{
/*N*/ 		nOben--;
/*N*/ 		while( nUnten <= nOben )
/*N*/ 		{
/*N*/ 			nMitte = nUnten + ( nOben - nUnten ) / 2;
/*N*/ 			const SwTxtAttr *pMitte = (*this)[nMitte];
/*N*/ 			if( IsEqual( *pMitte, *pElement ) )
/*N*/ 			{
/*N*/ 				*pPos = nMitte;
/*N*/ 				return TRUE;
/*N*/ 			}
/*N*/ 			else
/*N*/ 				if( lcl_IsLessEnd( *pMitte, *pElement ) )
/*N*/ 					nUnten = nMitte + 1;
/*N*/ 				else
/*N*/ 					if( nMitte == 0 )
/*N*/ 					{
/*N*/ 						*pPos = nUnten;
/*N*/ 						return FALSE;
/*N*/ 					}
/*N*/ 					else
/*N*/ 						nOben = nMitte - 1;
/*N*/ 		}
/*N*/ 	}
/*N*/ 	*pPos = nUnten;
/*N*/ 	return FALSE;
/*N*/ }

/*************************************************************************
 *                      class SwpHintsArr
 *************************************************************************/

/*N*/ void SwpHintsArr::Insert( const SwTxtAttr *pHt )
/*N*/ {
/*N*/ 	Resort();
/*N*/ #ifndef PRODUCT
/*N*/ 	USHORT nPos;
/*N*/ 	ASSERT(!SwpHtStart::Seek_Entry( pHt, &nPos ), "Insert: hint already in HtStart");
/*N*/ 	ASSERT(!aHtEnd.Seek_Entry( pHt, &nPos ), "Insert: hint already in HtEnd");
/*N*/ #endif
/*N*/ 	SwpHtStart::Insert( pHt );
/*N*/ 	aHtEnd.Insert( pHt );
/*N*/ #ifndef PRODUCT
/*N*/ #ifdef NIE
/*N*/ 	(aDbstream << "Insert: " ).WriteNumber( long( pHt ) )<< endl;
/*N*/ 	DumpHints( *this, aHtEnd );
/*N*/ #endif
/*N*/ #endif
/*N*/ }

/*N*/ void SwpHintsArr::DeleteAtPos( const USHORT nPos )
/*N*/ {
/*N*/ 	// Optimierung: nPos bezieht sich auf die Position im StartArray, also:
/*N*/ 	const SwTxtAttr *pHt = SwpHtStart::operator[]( nPos );
/*N*/ 	SwpHtStart::Remove( nPos );
/*N*/ 
/*N*/ 	Resort();
/*N*/ 
/*N*/ 	USHORT nEndPos;
/*N*/ 	aHtEnd.Seek_Entry( pHt, &nEndPos );
/*N*/ 	aHtEnd.Remove( nEndPos );
/*N*/ #ifndef PRODUCT
/*N*/ #ifdef NIE
/*N*/ 	(aDbstream << "DeleteAtPos: " ).WriteNumber( long( pHt ) )<< endl;
/*N*/ 	DumpHints( *this, aHtEnd );
/*N*/ #endif
/*N*/ #endif
/*N*/ }

#ifndef PRODUCT

/*************************************************************************
 *                      SwpHintsArr::Check()
 *************************************************************************/


/*N*/ #define CHECK_ERR(cond, text) \
/*N*/         if(!(cond)) \
/*N*/         { \
/*N*/             ASSERT(!this, text); \
/*N*/             DumpHints(*(SwpHtStart*)this,aHtEnd); \
/*N*/             const BOOL bErr = 0 == (cond); /* fuer den CV */ \
/*N*/             return !((SwpHintsArr*)this)->Resort(); \
/*N*/         }
/*N*/ 
/*N*/ BOOL SwpHintsArr::Check() const
/*N*/ {
/*N*/ 	// 1) gleiche Anzahl in beiden Arrays
/*N*/ 	CHECK_ERR( Count() == aHtEnd.Count(), "HintsCheck: wrong sizes" );
/*N*/ 	xub_StrLen nLastStart = 0;
/*N*/ 	xub_StrLen nLastEnd   = 0;
/*N*/ 
/*N*/ 	const SwTxtAttr *pLastStart = 0;
/*N*/ 	const SwTxtAttr *pLastEnd = 0;
/*N*/ 
/*N*/ 	for( USHORT i = 0; i < Count(); ++i )
/*N*/ 	{
/*N*/ 		// --- Start-Kontrolle ---
/*N*/ 
/*N*/ 		// 2a) gueltiger Pointer? vgl. DELETEFF
/*N*/ 		const SwTxtAttr *pHt = (*this)[i];
/*N*/ 		CHECK_ERR( 0xFF != *(char*)pHt, "HintsCheck: start ptr was deleted" );
/*N*/ 
/*N*/ 		// 3a) Stimmt die Start-Sortierung?
/*N*/ 		xub_StrLen nIdx = *pHt->GetStart();
/*N*/ 		CHECK_ERR( nIdx >= nLastStart, "HintsCheck: starts are unsorted" );
/*N*/ 
/*N*/ 		// 4a) IsLessStart-Konsistenz
/*N*/ 		if( pLastStart )
/*N*/ 			CHECK_ERR( lcl_IsLessStart( *pLastStart, *pHt ), "HintsCheck: IsLastStart" );
/*N*/ 
/*N*/ 		nLastStart = nIdx;
/*N*/ 		pLastStart = pHt;
/*N*/ 
/*N*/ 		// --- End-Kontrolle ---
/*N*/ 
/*N*/ 		// 2b) gueltiger Pointer? vgl. DELETEFF
/*N*/ 		const SwTxtAttr *pHtEnd = aHtEnd[i];
/*N*/ 		CHECK_ERR( 0xFF != *(char*)pHtEnd, "HintsCheck: end ptr was deleted" );
/*N*/ 
/*N*/ 		// 3b) Stimmt die End-Sortierung?
/*N*/ 		nIdx = *pHtEnd->GetAnyEnd();
/*N*/ 		CHECK_ERR( nIdx >= nLastEnd, "HintsCheck: ends are unsorted" );
/*N*/ 		nLastEnd = nIdx;
/*N*/ 
/*N*/ 		// 4b) IsLessEnd-Konsistenz
/*N*/ 		if( pLastEnd )
/*N*/ 			CHECK_ERR( lcl_IsLessEnd( *pLastEnd, *pHtEnd ), "HintsCheck: IsLastEnd" );
/*N*/ 
/*N*/ 		nLastEnd = nIdx;
/*N*/ 		pLastEnd = pHtEnd;
/*N*/ 
/*N*/ 		// --- Ueberkreuzungen ---
/*N*/ 
/*N*/ 		// 5) gleiche Pointer in beiden Arrays
/*N*/ 		nIdx = GetStartOf( pHtEnd );
/*N*/ 		CHECK_ERR( STRING_LEN != nIdx, "HintsCheck: no GetStartOf" );
/*N*/ 
/*N*/ 		// 6) gleiche Pointer in beiden Arrays
/*N*/ 		nIdx = GetEndOf( pHt );
/*N*/ 		CHECK_ERR( STRING_LEN != nIdx, "HintsCheck: no GetEndOf" );
/*N*/ 	}
/*N*/ 	return TRUE;
/*N*/ }

#endif      /* PRODUCT */

/*************************************************************************
 *                          SwpHintsArr::Resort()
 *************************************************************************/

// Resort() wird vor jedem Insert und Delete gerufen.
// Wenn Textmasse geloescht wird, so werden die Indizes in
// ndtxt.cxx angepasst. Leider erfolgt noch keine Neusortierung
// auf gleichen Positionen.

/*N*/ BOOL SwpHintsArr::Resort()
/*N*/ {
/*N*/ 	BOOL bResort = FALSE;
/*N*/ 	const SwTxtAttr *pLast = 0;
        USHORT i=0;
/*N*/ 	for( i = 0; i < SwpHtStart::Count(); ++i )
/*N*/ 	{
/*N*/ 		const SwTxtAttr *pHt = (*this)[i];
/*N*/ 		if( pLast && !lcl_IsLessStart( *pLast, *pHt ) )
/*N*/ 		{
/*N*/ #ifdef NIE
/*N*/ #ifndef PRODUCT
/*N*/ //            ASSERT( bResort, "!Resort/Start: correcting hints-array" );
/*N*/ 			aDbstream << "Resort: Starts" << endl;
/*N*/ 			DumpHints( *this, aHtEnd );
/*N*/ #endif
/*N*/ #endif
/*N*/ 			// Aufpassen: nicht die unsere SwpHintsArr-Methoden rufen,
/*N*/ 			// weil dort ein Resort steht!
/*N*/ 			// AMA: Bisher ( -> USED ) wurde ein Arrayinhalt [3,4,4,3] nur in
/*N*/ 			// 		[3,4,3,4] sortiert, nicht in [3,3,4,4]
/*N*/ #ifdef USED
/*N*/ 			SwpHtStart::Delete( i - 1 );
/*N*/ 			SwpHtStart::Insert( pLast );
/*N*/ 			USHORT nPos;
/*N*/ 			if( SwpHtStart::Seek_Entry( pLast, &nPos ) && nPos > i )
/*N*/ 				--i;
/*N*/ #else
/*N*/ 			SwpHtStart::Remove( i );
/*N*/ 			SwpHtStart::Insert( pHt );
/*N*/ 			pHt = (*this)[i];
/*N*/ 			if ( pHt != pLast )
/*N*/ 				--i;
/*N*/ #endif //!USED
/*N*/ 			bResort = TRUE;
/*N*/ 		}
/*N*/ 		pLast = pHt;
/*N*/ 	}
/*N*/ 
/*N*/ 	pLast = 0;
/*N*/ 	for( i = 0; i < aHtEnd.Count(); ++i )
/*N*/ 	{
/*N*/ 		const SwTxtAttr *pHt = aHtEnd[i];
/*N*/ 		if( pLast && !lcl_IsLessEnd( *pLast, *pHt ) )
/*N*/ 		{
/*N*/ #ifdef NIE
/*N*/ #ifndef PRODUCT
/*N*/ //            ASSERT( bResort, "!Resort/Ends: correcting hints-array" );
/*N*/ 			aDbstream << "Resort: Ends" << endl;
/*N*/ 			DumpHints( *this, aHtEnd );
/*N*/ #endif
/*N*/ #endif
/*N*/ // AMA: siehe oben
/*N*/ #ifdef USED
/*N*/ 			aHtEnd.Delete( i - 1 );
/*N*/ 			aHtEnd.Insert( pLast );
/*N*/ 			USHORT nPos;
/*N*/ 			if( aHtEnd.Seek_Entry( pLast, &nPos ) && nPos > i )
/*N*/ 				--i;
/*N*/ #else
/*N*/ 			aHtEnd.Remove( i );
/*N*/ 			aHtEnd.Insert( pHt );
/*N*/ 			pHt = aHtEnd[i]; // normalerweise == pLast
/*N*/ 			// Wenn die Unordnung etwas groesser ist (24200),
/*N*/ 			// muessen wir Position i erneut vergleichen.
/*N*/ 			if ( pLast != pHt )
/*N*/ 				--i;
/*N*/ #endif //!USED
/*N*/ 			bResort = TRUE;
/*N*/ 		}
/*N*/ 		pLast = pHt;
/*N*/ 	}
/*N*/ #ifndef PRODUCT
/*N*/ #ifdef NIE
/*N*/ 	aDbstream << "Resorted:" << endl;
/*N*/ 	DumpHints( *this, aHtEnd );
/*N*/ #endif
/*N*/ #endif
/*N*/ 	return bResort;
/*N*/ }


}
