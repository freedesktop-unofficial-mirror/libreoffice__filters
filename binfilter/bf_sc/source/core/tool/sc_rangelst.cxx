/*************************************************************************
 *
 *  $RCSfile: sc_rangelst.cxx,v $
 *
 *  $Revision: 1.3 $
 *
 *  last change: $Author: er $ $Date: 2004-03-30 13:22:06 $
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

#ifdef PCH
#include "core_pch.hxx"
#endif

#pragma hdrstop

//------------------------------------------------------------------------

#define SC_RANGELST_CXX			//fuer ICC

#include <tools/debug.hxx>
#include <stdlib.h>				// qsort
#include <unotools/collatorwrapper.hxx>

#include "rangelst.hxx"
#include "document.hxx"
#include "refupdat.hxx"
#include "rechead.hxx"
namespace binfilter {


// === ScRangeList ====================================================

/*N*/ ScRangeList::~ScRangeList()
/*N*/ {
/*N*/ 	for ( ScRangePtr pR = First(); pR; pR = Next() )
/*N*/ 		delete pR;
/*N*/ }

/*N*/ void ScRangeList::RemoveAll()
/*N*/ {
/*N*/ 	for ( ScRangePtr pR = First(); pR; pR = Next() )
/*N*/ 		delete pR;
/*N*/ 	Clear();
/*N*/ }

/*N*/ USHORT ScRangeList::Parse( const String& rStr, ScDocument* pDoc, USHORT nMask )
/*N*/ {
/*N*/ 	if ( rStr.Len() )
/*N*/ 	{
/*N*/ 		nMask |= SCA_VALID;				// falls das jemand vergessen sollte
/*N*/ 		USHORT nResult = (USHORT)~0;	// alle Bits setzen
/*N*/ 		ScRange	aRange;
/*N*/ 		String aOne;
/*N*/ 		USHORT nTab = 0;
/*N*/ 		if ( pDoc )
/*N*/ 		{
/*N*/ 			//!	erste markierte Tabelle gibts nicht mehr am Dokument
/*N*/ 			//!	-> uebergeben? oder spaeter an den Ranges setzen
/*N*/ 		}
/*N*/ 		else
/*N*/ 			nTab = 0;
/*N*/ 		USHORT nTCount = rStr.GetTokenCount();
/*N*/ 		for ( USHORT i=0; i<nTCount; i++ )
/*N*/ 		{
/*N*/ 			aOne = rStr.GetToken(i);
/*N*/ 			if ( aOne.Search( ':' ) == STRING_NOTFOUND )
/*N*/ 			{	// Range muss es sein
/*N*/ 				String aStrTmp( aOne );
/*N*/ 				aOne += ':';
/*N*/ 				aOne += aStrTmp;
/*N*/ 			}
/*N*/ 			aRange.aStart.SetTab( nTab );	// Default Tab wenn nicht angegeben
/*N*/ 			USHORT nRes = aRange.Parse( aOne, pDoc );
/*N*/ 			if ( (nRes & nMask) == nMask )
/*N*/ 				Append( aRange );
/*N*/ 			nResult &= nRes;		// alle gemeinsamen Bits bleiben erhalten
/*N*/ 		}
/*N*/ 		return nResult;				// SCA_VALID gesetzt wenn alle ok
/*N*/ 	}
/*N*/ 	else
/*N*/ 		return 0;
/*N*/ }


/*N*/ void ScRangeList::Format( String& rStr, USHORT nFlags, ScDocument* pDoc ) const
/*N*/ {
/*N*/ 	rStr.Erase();
/*N*/ 	ULONG nCnt = Count();
/*N*/ 	for ( ULONG nIdx = 0; nIdx < nCnt; nIdx++ )
/*N*/ 	{
/*N*/ 		String aStr;
/*N*/ 		GetObject( nIdx )->Format( aStr, nFlags, pDoc );
/*N*/ 		if ( nIdx )
/*N*/ 			rStr += ';';
/*N*/ 		rStr += aStr;
/*N*/ 	}
/*N*/ }


/*N*/ void ScRangeList::Join( const ScRange& r, BOOL bIsInList )
/*N*/ {
/*N*/ 	if ( !Count() )
/*N*/ 	{
/*N*/ 		Append( r );
/*N*/ 		return ;
/*N*/ 	}
/*N*/ 	USHORT nCol1 = r.aStart.Col();
/*N*/ 	USHORT nRow1 = r.aStart.Row();
/*N*/ 	USHORT nTab1 = r.aStart.Tab();
/*N*/ 	USHORT nCol2 = r.aEnd.Col();
/*N*/ 	USHORT nRow2 = r.aEnd.Row();
/*N*/ 	USHORT nTab2 = r.aEnd.Tab();
/*N*/ 	ScRangePtr pOver = (ScRangePtr) &r;		// fies aber wahr wenn bInList
/*N*/ 	ULONG nOldPos;
/*N*/ 	if ( bIsInList )
/*N*/ 	{	// merken um ggbf. zu loeschen bzw. wiederherzustellen
/*N*/ 		nOldPos = GetPos( pOver );
/*N*/ 	}
/*N*/ 	BOOL bJoinedInput = FALSE;
/*N*/ 	for ( ScRangePtr p = First(); p && pOver; p = Next() )
/*N*/ 	{
/*N*/ 		if ( p == pOver )
/*N*/ 			continue;			// derselbe, weiter mit dem naechsten
/*N*/ 		BOOL bJoined = FALSE;
/*N*/ 		if ( p->In( r ) )
/*N*/ 		{	// Range r in Range p enthalten oder identisch
/*N*/ 			if ( bIsInList )
/*N*/ 				bJoined = TRUE;		// weg mit Range r
/*N*/ 			else
/*N*/ 			{	// das war's dann
/*N*/ 				bJoinedInput = TRUE;	// nicht anhaengen
/*N*/ 				break;	// for
/*N*/ 			}
/*N*/ 		}
/*N*/ 		else if ( r.In( *p ) )
/*N*/ 		{	// Range p in Range r enthalten, r zum neuen Range machen
/*N*/ 			*p = r;
/*N*/ 			bJoined = TRUE;
/*N*/ 		}
/*N*/ 		if ( !bJoined && p->aStart.Tab() == nTab1 && p->aEnd.Tab() == nTab2 )
/*N*/ 		{	// 2D
/*N*/ 			if ( p->aStart.Col() == nCol1 && p->aEnd.Col() == nCol2 )
/*N*/ 			{
/*N*/ 				if ( p->aStart.Row() == nRow2+1 )
/*N*/ 				{	// oben
/*?*/ 					p->aStart.SetRow( nRow1 );
/*?*/ 					bJoined = TRUE;
/*N*/ 				}
/*N*/ 				else if ( p->aEnd.Row() == nRow1-1 )
/*N*/ 				{	// unten
/*N*/ 					p->aEnd.SetRow( nRow2 );
/*N*/ 					bJoined = TRUE;
/*N*/ 				}
/*N*/ 			}
/*N*/ 			else if ( p->aStart.Row() == nRow1 && p->aEnd.Row() == nRow2 )
/*N*/ 			{
/*N*/ 				if ( p->aStart.Col() == nCol2+1 )
/*N*/ 				{	// links
/*?*/ 					p->aStart.SetCol( nCol1 );
/*?*/ 					bJoined = TRUE;
/*N*/ 				}
/*N*/ 				else if ( p->aEnd.Col() == nCol1-1 )
/*N*/ 				{	// rechts
/*N*/ 					p->aEnd.SetCol( nCol2 );
/*N*/ 					bJoined = TRUE;
/*N*/ 				}
/*N*/ 			}
/*N*/ 		}
/*N*/ 		if ( bJoined )
/*N*/ 		{
/*N*/ 			if ( bIsInList )
/*N*/ 			{	// innerhalb der Liste Range loeschen
/*N*/ 				Remove( nOldPos );
/*N*/ 				delete pOver;
/*N*/ 				pOver = NULL;
/*N*/ 				if ( nOldPos )
/*N*/ 					nOldPos--;			// Seek richtig aufsetzen
/*N*/ 			}
/*N*/ 			bJoinedInput = TRUE;
/*N*/ 			Join( *p, TRUE );			// rekursiv!
/*N*/ 		}
/*N*/ 	}
/*N*/ 	if ( bIsInList )
/*N*/ 		Seek( nOldPos );
/*N*/ 	else if ( !bJoinedInput )
/*N*/ 		Append( r );
/*N*/ }


//STRIP001 BOOL ScRangeList::operator==( const ScRangeList& r ) const
//STRIP001 {
//STRIP001 	if ( this == &r )
//STRIP001 		return TRUE;				// identische Referenz
//STRIP001 	if ( Count() != r.Count() )
//STRIP001 		return FALSE;
//STRIP001 	ULONG nCnt = Count();
//STRIP001 	for ( ULONG nIdx = 0; nIdx < nCnt; nIdx++ )
//STRIP001 	{
//STRIP001 		if ( *GetObject( nIdx ) != *r.GetObject( nIdx ) )
//STRIP001 			return FALSE;			// auch andere Reihenfolge ist ungleich
//STRIP001 	}
//STRIP001 	return TRUE;
//STRIP001 }


/*N*/ BOOL ScRangeList::Store( SvStream& rStream ) const
/*N*/ {
/*N*/ 	BOOL bOk = TRUE;
/*N*/ 	ULONG nCount = Count();
/*N*/ 	ULONG nBytes = sizeof(UINT32) + nCount * sizeof(ScRange);
/*N*/ 	ScWriteHeader aHdr( rStream, nBytes );
/*N*/ 	rStream << (UINT32) nCount;
/*N*/ 	for ( ULONG j = 0; j < nCount && bOk; j++ )
/*N*/ 	{
/*N*/ 		rStream << *GetObject( j );
/*N*/ 		if( rStream.GetError() != SVSTREAM_OK )
/*N*/ 			bOk = FALSE;
/*N*/ 	}
/*N*/ 	return bOk;
/*N*/ }


/*N*/ BOOL ScRangeList::Load( SvStream& rStream, USHORT nVer )
/*N*/ {
/*N*/ 	BOOL bOk = TRUE;
/*N*/ 	ScReadHeader aHdr( rStream );
/*N*/ 	ScRange aRange;
/*N*/ 	UINT32 n;
/*N*/ 	rStream >> n;
/*N*/ 	ULONG nCount = n;
/*N*/ 	for ( ULONG j = 0; j < nCount && bOk; j++ )
/*N*/ 	{
/*N*/ 		rStream >> aRange;
/*N*/ 		Append( aRange );
/*N*/ 		if( rStream.GetError() != SVSTREAM_OK )
/*N*/ 			bOk = FALSE;
/*N*/ 	}
/*N*/ 	return bOk;
/*N*/ }


/*N*/ BOOL ScRangeList::UpdateReference( UpdateRefMode eUpdateRefMode,
/*N*/ 									ScDocument* pDoc, const ScRange& rWhere,
/*N*/ 									short nDx, short nDy, short nDz )
/*N*/ {
/*N*/ 	BOOL bChanged = FALSE;
/*N*/ 	if ( Count() )
/*N*/ 	{
/*N*/ 		USHORT nCol1, nRow1, nTab1, nCol2, nRow2, nTab2;
/*N*/ 		rWhere.GetVars( nCol1, nRow1, nTab1, nCol2, nRow2, nTab2 );
/*N*/ 		for ( ScRange* pR = First(); pR; pR = Next() )
/*N*/ 		{
/*N*/ 			USHORT theCol1, theRow1, theTab1, theCol2, theRow2, theTab2;
/*N*/ 			pR->GetVars( theCol1, theRow1, theTab1, theCol2, theRow2, theTab2 );
/*N*/ 			if ( ScRefUpdate::Update( pDoc, eUpdateRefMode,
/*N*/ 					nCol1, nRow1, nTab1, nCol2, nRow2, nTab2,
/*N*/ 					nDx, nDy, nDz,
/*N*/ 					theCol1, theRow1, theTab1, theCol2, theRow2, theTab2 )
/*N*/ 					!= UR_NOTHING )
/*N*/ 			{
/*?*/ 				bChanged = TRUE;
/*?*/ 				pR->aStart.Set( theCol1, theRow1, theTab1 );
/*?*/ 				pR->aEnd.Set( theCol2, theRow2, theTab2 );
/*N*/ 			}
/*N*/ 		}
/*N*/ 	}
/*N*/ 	return bChanged;
/*N*/ }


//STRIP001 ScRange* ScRangeList::Find( const ScAddress& rAdr ) const
//STRIP001 {
//STRIP001 	ULONG nCount = Count();
//STRIP001 	for ( ULONG j = 0; j < nCount; j++ )
//STRIP001 	{
//STRIP001 		ScRange* pR = GetObject( j );
//STRIP001 		if ( pR->In( rAdr ) )
//STRIP001 			return pR;
//STRIP001 	}
//STRIP001 	return NULL;
//STRIP001 }


//STRIP001 ScRange* ScRangeList::Find( const ScRange& rRange ) const
//STRIP001 {
//STRIP001 	ULONG nCount = Count();
//STRIP001 	for ( ULONG j = 0; j < nCount; j++ )
//STRIP001 	{
//STRIP001 		ScRange* pR = GetObject( j );
//STRIP001 		if ( *pR == rRange )
//STRIP001 			return pR;
//STRIP001 	}
//STRIP001 	return NULL;
//STRIP001 }


/*N*/ ScRangeList::ScRangeList( const ScRangeList& rList )
/*N*/ {
/*N*/ 	ULONG nCount = rList.Count();
/*N*/ 	for ( ULONG j = 0; j < nCount; j++ )
/*N*/ 		Append( *rList.GetObject( j ) );
/*N*/ }


//STRIP001 ScRangeList* ScRangeList::Clone() const
//STRIP001 {
//STRIP001 	return new ScRangeList( *this );
//STRIP001 }


/*N*/ ScRangeList& ScRangeList::operator=(const ScRangeList& rList)
/*N*/ {
/*N*/ 	RemoveAll();
/*N*/ 
/*N*/ 	ULONG nCount = rList.Count();
/*N*/ 	for ( ULONG j = 0; j < nCount; j++ )
/*N*/ 		Append( *rList.GetObject( j ) );
/*N*/ 
/*N*/ 	return *this;
/*N*/ }


//STRIP001 BOOL ScRangeList::Intersects( const ScRange& rRange ) const
//STRIP001 {
//STRIP001 	ULONG nCount = Count();
//STRIP001 	for ( ULONG j = 0; j < nCount; j++ )
//STRIP001 		if ( GetObject(j)->Intersects( rRange ) )
//STRIP001 			return TRUE;
//STRIP001 
//STRIP001 	return FALSE;
//STRIP001 }


//STRIP001 BOOL ScRangeList::In( const ScRange& rRange ) const
//STRIP001 {
//STRIP001 	ULONG nCount = Count();
//STRIP001 	for ( ULONG j = 0; j < nCount; j++ )
//STRIP001 		if ( GetObject(j)->In( rRange ) )
//STRIP001 			return TRUE;
//STRIP001 
//STRIP001 	return FALSE;
//STRIP001 }


//STRIP001 ULONG ScRangeList::GetCellCount() const
//STRIP001 {
//STRIP001 	ULONG nCellCount = 0;
//STRIP001 	ULONG nCount = Count();
//STRIP001 	for ( ULONG j = 0; j < nCount; j++ )
//STRIP001 	{
//STRIP001 		ScRange* pR = GetObject( j );
//STRIP001 		nCellCount += ULONG(pR->aEnd.Col() - pR->aStart.Col() + 1)
//STRIP001 			* ULONG(pR->aEnd.Row() - pR->aStart.Row() + 1)
//STRIP001 			* ULONG(pR->aEnd.Tab() - pR->aStart.Tab() + 1);
//STRIP001 	}
//STRIP001 	return nCellCount;
//STRIP001 }


// === ScRangePairList ====================================================

/*N*/ ScRangePairList::~ScRangePairList()
/*N*/ {
/*N*/ 	for ( ScRangePair* pR = First(); pR; pR = Next() )
/*?*/ 		delete pR;
/*N*/ }


/*N*/ void ScRangePairList::Join( const ScRangePair& r, BOOL bIsInList )
/*N*/ {
/*N*/ 	if ( !Count() )
/*N*/ 	{
/*N*/ 		Append( r );
/*N*/ 		return ;
/*N*/ 	}
/*N*/ 	const ScRange& r1 = r.GetRange(0);
/*N*/ 	const ScRange& r2 = r.GetRange(1);
/*N*/ 	USHORT nCol1 = r1.aStart.Col();
/*N*/ 	USHORT nRow1 = r1.aStart.Row();
/*N*/ 	USHORT nTab1 = r1.aStart.Tab();
/*N*/ 	USHORT nCol2 = r1.aEnd.Col();
/*N*/ 	USHORT nRow2 = r1.aEnd.Row();
/*N*/ 	USHORT nTab2 = r1.aEnd.Tab();
/*N*/ 	ScRangePair* pOver = (ScRangePair*) &r;		// fies aber wahr wenn bInList
/*N*/ 	ULONG nOldPos;
/*N*/ 	if ( bIsInList )
/*N*/ 	{	// merken um ggbf. zu loeschen bzw. wiederherzustellen
/*N*/ 		nOldPos = GetPos( pOver );
/*N*/ 	}
/*N*/ 	BOOL bJoinedInput = FALSE;
/*N*/ 	for ( ScRangePair* p = First(); p && pOver; p = Next() )
/*N*/ 	{
/*N*/ 		if ( p == pOver )
/*N*/ 			continue;			// derselbe, weiter mit dem naechsten
/*N*/ 		BOOL bJoined = FALSE;
/*N*/ 		ScRange& rp1 = p->GetRange(0);
/*N*/ 		ScRange& rp2 = p->GetRange(1);
/*N*/ 		if ( rp2 == r2 )
/*N*/ 		{	// nur wenn Range2 gleich ist
/*N*/ 			if ( rp1.In( r1 ) )
/*N*/ 			{	// RangePair r in RangePair p enthalten oder identisch
/*N*/ 				if ( bIsInList )
/*N*/ 					bJoined = TRUE;		// weg mit RangePair r
/*N*/ 				else
/*N*/ 				{	// das war's dann
/*N*/ 					bJoinedInput = TRUE;	// nicht anhaengen
/*N*/ 					break;	// for
/*N*/ 				}
/*N*/ 			}
/*N*/ 			else if ( r1.In( rp1 ) )
/*N*/ 			{	// RangePair p in RangePair r enthalten, r zum neuen RangePair machen
/*N*/ 				*p = r;
/*N*/ 				bJoined = TRUE;
/*N*/ 			}
/*N*/ 		}
/*N*/ 		if ( !bJoined && rp1.aStart.Tab() == nTab1 && rp1.aEnd.Tab() == nTab2
/*N*/ 		  && rp2.aStart.Tab() == r2.aStart.Tab()
/*N*/ 		  && rp2.aEnd.Tab() == r2.aEnd.Tab() )
/*N*/ 		{	// 2D, Range2 muss genauso nebeneinander liegen wie Range1
/*N*/ 			if ( rp1.aStart.Col() == nCol1 && rp1.aEnd.Col() == nCol2
/*N*/ 			  && rp2.aStart.Col() == r2.aStart.Col()
/*N*/ 			  && rp2.aEnd.Col() == r2.aEnd.Col() )
/*N*/ 			{
/*N*/ 				if ( rp1.aStart.Row() == nRow2+1
/*N*/ 				  && rp2.aStart.Row() == r2.aEnd.Row()+1 )
/*N*/ 				{	// oben
/*N*/ 					rp1.aStart.SetRow( nRow1 );
/*N*/ 					rp2.aStart.SetRow( r2.aStart.Row() );
/*N*/ 					bJoined = TRUE;
/*N*/ 				}
/*N*/ 				else if ( rp1.aEnd.Row() == nRow1-1
/*N*/ 				  && rp2.aEnd.Row() == r2.aStart.Row()-1 )
/*N*/ 				{	// unten
/*N*/ 					rp1.aEnd.SetRow( nRow2 );
/*N*/ 					rp2.aEnd.SetRow( r2.aEnd.Row() );
/*N*/ 					bJoined = TRUE;
/*N*/ 				}
/*N*/ 			}
/*N*/ 			else if ( rp1.aStart.Row() == nRow1 && rp1.aEnd.Row() == nRow2
/*N*/ 			  && rp2.aStart.Row() == r2.aStart.Row()
/*N*/ 			  && rp2.aEnd.Row() == r2.aEnd.Row() )
/*N*/ 			{
/*N*/ 				if ( rp1.aStart.Col() == nCol2+1
/*N*/ 				  && rp2.aStart.Col() == r2.aEnd.Col()+1 )
/*N*/ 				{	// links
/*N*/ 					rp1.aStart.SetCol( nCol1 );
/*N*/ 					rp2.aStart.SetCol( r2.aStart.Col() );
/*N*/ 					bJoined = TRUE;
/*N*/ 				}
/*N*/ 				else if ( rp1.aEnd.Col() == nCol1-1
/*N*/ 				  && rp2.aEnd.Col() == r2.aEnd.Col()-1 )
/*N*/ 				{	// rechts
/*N*/ 					rp1.aEnd.SetCol( nCol2 );
/*N*/ 					rp2.aEnd.SetCol( r2.aEnd.Col() );
/*N*/ 					bJoined = TRUE;
/*N*/ 				}
/*N*/ 			}
/*N*/ 		}
/*N*/ 		if ( bJoined )
/*N*/ 		{
/*N*/ 			if ( bIsInList )
/*N*/ 			{	// innerhalb der Liste RangePair loeschen
/*N*/ 				Remove( nOldPos );
/*N*/ 				delete pOver;
/*N*/ 				pOver = NULL;
/*N*/ 				if ( nOldPos )
/*N*/ 					nOldPos--;			// Seek richtig aufsetzen
/*N*/ 			}
/*N*/ 			bJoinedInput = TRUE;
/*N*/ 			Join( *p, TRUE );			// rekursiv!
/*N*/ 		}
/*N*/ 	}
/*N*/ 	if ( bIsInList )
/*N*/ 		Seek( nOldPos );
/*N*/ 	else if ( !bJoinedInput )
/*N*/ 		Append( r );
/*N*/ }


//STRIP001 BOOL ScRangePairList::operator==( const ScRangePairList& r ) const
//STRIP001 {
//STRIP001 	if ( this == &r )
//STRIP001 		return TRUE;				// identische Referenz
//STRIP001 	if ( Count() != r.Count() )
//STRIP001 		return FALSE;
//STRIP001 	ULONG nCnt = Count();
//STRIP001 	for ( ULONG nIdx = 0; nIdx < nCnt; nIdx++ )
//STRIP001 	{
//STRIP001 		if ( *GetObject( nIdx ) != *r.GetObject( nIdx ) )
//STRIP001 			return FALSE;			// auch andere Reihenfolge ist ungleich
//STRIP001 	}
//STRIP001 	return TRUE;
//STRIP001 }


/*N*/ BOOL ScRangePairList::Store( SvStream& rStream ) const
/*N*/ {
/*N*/ 	BOOL bOk = TRUE;
/*N*/ 	ULONG nCount = Count();
/*N*/ 	ULONG nBytes = sizeof(UINT32) + nCount * sizeof(ScRangePair);
/*N*/ 	ScWriteHeader aHdr( rStream, nBytes );
/*N*/ 	rStream << (UINT32) nCount;
/*N*/ 	for ( ULONG j = 0; j < nCount && bOk; j++ )
/*N*/ 	{
/*N*/ 		rStream << *GetObject( j );
/*N*/ 		if( rStream.GetError() != SVSTREAM_OK )
/*N*/ 			bOk = FALSE;
/*N*/ 	}
/*N*/ 	return bOk;
/*N*/ }


/*N*/ BOOL ScRangePairList::Load( SvStream& rStream, USHORT nVer )
/*N*/ {
/*N*/ 	BOOL bOk = TRUE;
/*N*/ 	ScReadHeader aHdr( rStream );
/*N*/ 	ScRangePair aRangePair;
/*N*/ 	ScRange aRange;
/*N*/ 	UINT32 n;
/*N*/ 	rStream >> n;
/*N*/ 	ULONG nCount = n;
/*N*/ 	for ( ULONG j = 0; j < nCount && bOk; j++ )
/*N*/ 	{
/*N*/ 		if ( nVer < SC_COLROWNAME_RANGEPAIR )
/*N*/ 		{	// aus technical Beta 4.0 versuchen mit altem Verhalten zu uebernehmen
/*N*/ 			rStream >> aRange;
/*N*/ 			aRangePair.GetRange(0) = aRange;
/*N*/ 			ScRange& r = aRangePair.GetRange(1);
/*N*/ 			r = aRange;
/*N*/ 			USHORT nCol2 = aRange.aEnd.Col();
/*N*/ 			USHORT nRow2 = aRange.aEnd.Row();
/*N*/ 			if ( nCol2 - aRange.aStart.Col() >= nRow2 - aRange.aStart.Row() )
/*N*/ 			{	// ColNames
/*N*/ 				r.aStart.SetRow( (USHORT) Min( (ULONG)nRow2 + 1, (ULONG)MAXROW ) );
/*N*/ 				r.aEnd.SetRow( MAXROW );
/*N*/ 			}
/*N*/ 			else
/*N*/ 			{	// RowNames
/*N*/ 				r.aStart.SetCol( (USHORT) Min( (ULONG)(nCol2 + 1), (ULONG)MAXCOL ) );
/*N*/ 				r.aEnd.SetCol( MAXCOL );
/*N*/ 			}
/*N*/ 		}
/*N*/ 		else
/*N*/ 			rStream >> aRangePair;
/*N*/ 		Append( aRangePair );
/*N*/ 		if( rStream.GetError() != SVSTREAM_OK )
/*N*/ 			bOk = FALSE;
/*N*/ 	}
/*N*/ 	return bOk;
/*N*/ }


/*N*/ BOOL ScRangePairList::UpdateReference( UpdateRefMode eUpdateRefMode,
/*N*/ 									ScDocument* pDoc, const ScRange& rWhere,
/*N*/ 									short nDx, short nDy, short nDz )
/*N*/ {
/*N*/ 	BOOL bChanged = FALSE;
/*N*/ 	if ( Count() )
/*N*/ 	{
/*?*/ 		USHORT nCol1, nRow1, nTab1, nCol2, nRow2, nTab2;
/*?*/ 		rWhere.GetVars( nCol1, nRow1, nTab1, nCol2, nRow2, nTab2 );
/*?*/ 		for ( ScRangePair* pR = First(); pR; pR = Next() )
/*?*/ 		{
/*?*/ 			for ( USHORT j=0; j<2; j++ )
/*?*/ 			{
/*?*/ 				ScRange& rRange = pR->GetRange(j);
/*?*/ 				USHORT theCol1, theRow1, theTab1, theCol2, theRow2, theTab2;
/*?*/ 				rRange.GetVars( theCol1, theRow1, theTab1, theCol2, theRow2, theTab2 );
/*?*/ 				if ( ScRefUpdate::Update( pDoc, eUpdateRefMode,
/*?*/ 						nCol1, nRow1, nTab1, nCol2, nRow2, nTab2,
/*?*/ 						nDx, nDy, nDz,
/*?*/ 						theCol1, theRow1, theTab1, theCol2, theRow2, theTab2 )
/*?*/ 						!= UR_NOTHING )
/*?*/ 				{
/*?*/ 					bChanged = TRUE;
/*?*/ 					rRange.aStart.Set( theCol1, theRow1, theTab1 );
/*?*/ 					rRange.aEnd.Set( theCol2, theRow2, theTab2 );
/*?*/ 				}
/*?*/ 			}
/*?*/ 		}
/*N*/ 	}
/*N*/ 	return bChanged;
/*N*/ }


/*N*/ ScRangePair* ScRangePairList::Find( const ScAddress& rAdr ) const
/*N*/ {
/*N*/ 	ULONG nCount = Count();
/*N*/ 	for ( ULONG j = 0; j < nCount; j++ )
/*N*/ 	{
/*N*/ 		ScRangePair* pR = GetObject( j );
/*N*/ 		if ( pR->GetRange(0).In( rAdr ) )
/*N*/ 			return pR;
/*N*/ 	}
/*N*/ 	return NULL;
/*N*/ }


/*N*/ ScRangePair* ScRangePairList::Find( const ScRange& rRange ) const
/*N*/ {
/*N*/ 	ULONG nCount = Count();
/*N*/ 	for ( ULONG j = 0; j < nCount; j++ )
/*N*/ 	{
/*N*/ 		ScRangePair* pR = GetObject( j );
/*N*/ 		if ( pR->GetRange(0) == rRange )
/*N*/ 			return pR;
/*N*/ 	}
/*N*/ 	return NULL;
/*N*/ }


/*N*/ ScRangePairList* ScRangePairList::Clone() const
/*N*/ {
/*N*/ 	ScRangePairList* pNew = new ScRangePairList;
/*N*/ 	ULONG nCount = Count();
/*N*/ 	for ( ULONG j = 0; j < nCount; j++ )
/*N*/ 	{
/*N*/ 		pNew->Append( *GetObject( j ) );
/*N*/ 	}
/*N*/ 	return pNew;
/*N*/ }


struct ScRangePairNameSort
{
    ScRangePair*	pPair;
    ScDocument*		pDoc;
};


//STRIP001 int
//STRIP001 #ifdef WNT
//STRIP001 __cdecl
//STRIP001 #endif
//STRIP001 ScRangePairList::QsortNameCompare( const void* p1, const void* p2 )
//STRIP001 {
//STRIP001 	const ScRangePairNameSort* ps1 = (const ScRangePairNameSort*)p1;
//STRIP001 	const ScRangePairNameSort* ps2 = (const ScRangePairNameSort*)p2;
//STRIP001 	const ScAddress& rPos1 = ps1->pPair->GetRange(0).aStart;
//STRIP001 	const ScAddress& rPos2 = ps2->pPair->GetRange(0).aStart;
//STRIP001 	String aStr1, aStr2;
//STRIP001 	sal_Int32 nComp;
//STRIP001 	if ( rPos1.Tab() == rPos2.Tab() )
//STRIP001 		nComp = COMPARE_EQUAL;
//STRIP001 	else
//STRIP001 	{
//STRIP001 		ps1->pDoc->GetName( rPos1.Tab(), aStr1 );
//STRIP001 		ps2->pDoc->GetName( rPos2.Tab(), aStr2 );
//STRIP001 		nComp = ScGlobal::pCollator->compareString( aStr1, aStr2 );
//STRIP001 	}
//STRIP001 	switch ( nComp )
//STRIP001 	{
//STRIP001 		case COMPARE_LESS:
//STRIP001 			return -1;
//STRIP001 		break;
//STRIP001 		case COMPARE_GREATER:
//STRIP001 			return 1;
//STRIP001 		break;
//STRIP001 		default:
//STRIP001 			// gleiche Tabs
//STRIP001 			if ( rPos1.Col() < rPos2.Col() )
//STRIP001 				return -1;
//STRIP001 			if ( rPos1.Col() > rPos2.Col() )
//STRIP001 				return 1;
//STRIP001 			// gleiche Cols
//STRIP001 			if ( rPos1.Row() < rPos2.Row() )
//STRIP001 				return -1;
//STRIP001 			if ( rPos1.Row() > rPos2.Row() )
//STRIP001 				return 1;
//STRIP001 			// erste Ecke gleich, zweite Ecke
//STRIP001 			{
//STRIP001 				const ScAddress& rPos1 = ps1->pPair->GetRange(0).aEnd;
//STRIP001 				const ScAddress& rPos2 = ps2->pPair->GetRange(0).aEnd;
//STRIP001 				if ( rPos1.Tab() == rPos2.Tab() )
//STRIP001 					nComp = COMPARE_EQUAL;
//STRIP001 				else
//STRIP001 				{
//STRIP001 					ps1->pDoc->GetName( rPos1.Tab(), aStr1 );
//STRIP001 					ps2->pDoc->GetName( rPos2.Tab(), aStr2 );
//STRIP001 					nComp = ScGlobal::pCollator->compareString( aStr1, aStr2 );
//STRIP001 				}
//STRIP001 				switch ( nComp )
//STRIP001 				{
//STRIP001 					case COMPARE_LESS:
//STRIP001 						return -1;
//STRIP001 					break;
//STRIP001 					case COMPARE_GREATER:
//STRIP001 						return 1;
//STRIP001 					break;
//STRIP001 					default:
//STRIP001 						// gleiche Tabs
//STRIP001 						if ( rPos1.Col() < rPos2.Col() )
//STRIP001 							return -1;
//STRIP001 						if ( rPos1.Col() > rPos2.Col() )
//STRIP001 							return 1;
//STRIP001 						// gleiche Cols
//STRIP001 						if ( rPos1.Row() < rPos2.Row() )
//STRIP001 							return -1;
//STRIP001 						if ( rPos1.Row() > rPos2.Row() )
//STRIP001 							return 1;
//STRIP001 						return 0;
//STRIP001 				}
//STRIP001 			}
//STRIP001 			return 0;
//STRIP001 	}
//STRIP001 }


//STRIP001 ScRangePair** ScRangePairList::CreateNameSortedArray( ULONG& nCount,
//STRIP001 		ScDocument* pDoc ) const
//STRIP001 {
//STRIP001 	nCount = Count();
//STRIP001 	DBG_ASSERT( nCount * sizeof(ScRangePairNameSort) <= (size_t)~0x1F,
//STRIP001 		"ScRangePairList::CreateNameSortedArray nCount * sizeof(ScRangePairNameSort) > (size_t)~0x1F" );
//STRIP001 	ScRangePairNameSort* pSortArray = (ScRangePairNameSort*)
//STRIP001 		new BYTE [ nCount * sizeof(ScRangePairNameSort) ];
//STRIP001 	ULONG j;
//STRIP001 	for ( j=0; j < nCount; j++ )
//STRIP001 	{
//STRIP001 		pSortArray[j].pPair = GetObject( j );
//STRIP001 		pSortArray[j].pDoc = pDoc;
//STRIP001 	}
//STRIP001 #if !(defined(ICC ) && defined(OS2))
//STRIP001 	qsort( (void*)pSortArray, nCount, sizeof(ScRangePairNameSort), &ScRangePairList::QsortNameCompare );
//STRIP001 #else
//STRIP001 	qsort( (void*)pSortArray, nCount, sizeof(ScRangePairNameSort), ICCQsortRPairCompare );
//STRIP001 #endif
//STRIP001 	// ScRangePair Pointer aufruecken
//STRIP001 	ScRangePair** ppSortArray = (ScRangePair**)pSortArray;
//STRIP001 	for ( j=0; j < nCount; j++ )
//STRIP001 	{
//STRIP001 		ppSortArray[j] = pSortArray[j].pPair;
//STRIP001 	}
//STRIP001 	return ppSortArray;
//STRIP001 }




}
