/*************************************************************************
 *
 *  $RCSfile: sc_collect.cxx,v $
 *
 *  $Revision: 1.5 $
 *
 *  last change: $Author: hr $ $Date: 2004-08-03 11:14:48 $
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
// auto strip #include "core_pch.hxx"
#endif

#pragma hdrstop

#include <string.h>

// auto strip #ifndef _STREAM_HXX //autogen
// auto strip #include <tools/stream.hxx>
// auto strip #endif
// auto strip #ifndef _UNOTOOLS_TRANSLITERATIONWRAPPER_HXX
// auto strip #include <unotools/transliterationwrapper.hxx>
// auto strip #endif

#include "rechead.hxx"
#include "collect.hxx"
#include "document.hxx"	
#include <tools/debug.hxx>// fuer TypedStrData Konstruktor
namespace binfilter {

// -----------------------------------------------------------------------

/*N*/ DataObject::~DataObject()
/*N*/ {
/*N*/ }

//------------------------------------------------------------------------
// Collection
//------------------------------------------------------------------------

/*N*/ void lcl_DeleteDataObjects( DataObject** p, USHORT nCount )
/*N*/ {
/*N*/ 	if ( p )
/*N*/ 	{
/*N*/ 		for (USHORT i = 0; i < nCount; i++) delete p[i];
/*N*/ 		delete[] p;
/*N*/ 		p = NULL;
/*N*/ 	}
/*N*/ }

/*N*/ Collection::Collection(USHORT nLim, USHORT nDel) :
/*N*/ 	nCount ( 0 ),
/*N*/ 	nLimit ( nLim ),
/*N*/ 	nDelta ( nDel ),
/*N*/ 	pItems ( NULL )
/*N*/ {
/*N*/ 	if (nDelta > MAXDELTA)
/*N*/ 		nDelta = MAXDELTA;
/*N*/ 	else if (nDelta == 0)
/*N*/ 		nDelta = 1;
/*N*/ 	if (nLimit > MAXCOLLECTIONSIZE)
/*N*/ 		nLimit = MAXCOLLECTIONSIZE;
/*N*/ 	else if (nLimit < nDelta)
/*N*/ 		nLimit = nDelta;
/*N*/ 	pItems = new DataObject*[nLimit];
/*N*/ }

/*N*/ Collection::Collection(const Collection& rCollection)
/*N*/ 	:	nCount ( 0 ),
/*N*/ 		nLimit ( 0 ),
/*N*/ 		nDelta ( 0 ),
/*N*/ 		pItems ( NULL )
/*N*/ {
/*N*/ 	*this = rCollection;
/*N*/ }

//------------------------------------------------------------------------

/*N*/ Collection::~Collection()
/*N*/ {
/*N*/ 	lcl_DeleteDataObjects( pItems, nCount );
/*N*/ }

//------------------------------------------------------------------------

/*N*/ void Collection::AtFree(USHORT nIndex)
/*N*/ {
/*N*/ 	if ((pItems) && (nIndex < nCount))
/*N*/ 	{
/*N*/ 		delete pItems[nIndex];
/*N*/ 		--nCount;				// before memmove
/*N*/ 		memmove ( &pItems[nIndex], &pItems[nIndex + 1], (nCount - nIndex) * sizeof(DataObject*));
/*N*/ 		pItems[nCount] = NULL;
/*N*/ 	}
/*N*/ }

//------------------------------------------------------------------------

/*N*/ void Collection::Free(DataObject* pDataObject)
/*N*/ {
/*N*/ 	AtFree(IndexOf(pDataObject));
/*N*/ }

//------------------------------------------------------------------------

/*N*/ void Collection::FreeAll()
/*N*/ {
/*N*/ 	lcl_DeleteDataObjects( pItems, nCount );
/*N*/ 	nCount = 0;
/*N*/ 	pItems = new DataObject*[nLimit];
/*N*/ }

//------------------------------------------------------------------------

/*N*/ BOOL Collection::AtInsert(USHORT nIndex, DataObject* pDataObject)
/*N*/ {
/*N*/ 	if ((nCount < MAXCOLLECTIONSIZE) && (nIndex <= nCount) && pItems)
/*N*/ 	{
/*N*/ 		if (nCount == nLimit)
/*N*/ 		{
/*N*/ 			DataObject** pNewItems = new DataObject*[nLimit + nDelta];
/*N*/ 			if (!pNewItems)
/*N*/ 				return FALSE;
/*N*/ 			nLimit += nDelta;
/*N*/ 			memmove(pNewItems, pItems, nCount * sizeof(DataObject*));
/*N*/ 			delete[] pItems;
/*N*/ 			pItems = pNewItems;
/*N*/ 		}
/*N*/ 		if (nCount > nIndex)
/*N*/ 			memmove(&pItems[nIndex + 1], &pItems[nIndex], (nCount - nIndex) * sizeof(DataObject*));
/*N*/ 		pItems[nIndex] = pDataObject;
/*N*/ 		nCount++;
/*N*/ 		return TRUE;
/*N*/ 	}
/*N*/ 	return FALSE;
/*N*/ }

//------------------------------------------------------------------------

/*N*/ BOOL Collection::Insert(DataObject* pDataObject)
/*N*/ {
/*N*/ 	return AtInsert(nCount, pDataObject);
/*N*/ }

//------------------------------------------------------------------------

/*N*/ DataObject* Collection::At(USHORT nIndex) const
/*N*/ {
/*N*/ 	if (nIndex < nCount)
/*N*/ 		return pItems[nIndex];
/*N*/ 	else
/*N*/ 		return NULL;
/*N*/ }

//------------------------------------------------------------------------

/*N*/ USHORT Collection::IndexOf(DataObject* pDataObject) const
/*N*/ {
/*N*/ 	USHORT nIndex = 0xffff;
/*N*/ 	for (USHORT i = 0; ((i < nCount) && (nIndex == 0xffff)); i++)
/*N*/ 	{
/*N*/ 		if (pItems[i] == pDataObject) nIndex = i;
/*N*/ 	}
/*N*/ 	return nIndex;
/*N*/ }

//------------------------------------------------------------------------

/*N*/ Collection& Collection::operator=( const Collection& r )
/*N*/ {
/*N*/ 	lcl_DeleteDataObjects( pItems, nCount );
/*N*/ 
/*N*/ 	nCount = r.nCount;
/*N*/ 	nLimit = r.nLimit;
/*N*/ 	nDelta = r.nDelta;
/*N*/ 	pItems = new DataObject*[nLimit];
/*N*/ 	for ( USHORT i=0; i<nCount; i++ )
/*N*/ 		pItems[i] = r.pItems[i]->Clone();
/*N*/ 
/*N*/ 	return *this;
/*N*/ }

//------------------------------------------------------------------------

/*N*/ DataObject*	Collection::Clone() const
/*N*/ {
        DBG_BF_ASSERT(0, "STRIP"); return NULL; //STRIP001 	return new Collection(*this);
/*N*/ }

//------------------------------------------------------------------------
// SortedCollection
//------------------------------------------------------------------------

/*N*/ SortedCollection::SortedCollection(USHORT nLim, USHORT nDel, BOOL bDup) :
/*N*/ 	Collection (nLim, nDel),
/*N*/ 	bDuplicates ( bDup)
/*N*/ {
/*N*/ }

//------------------------------------------------------------------------

//STRIP001 USHORT SortedCollection::IndexOf(DataObject* pDataObject) const
//STRIP001 {
//STRIP001 	USHORT nIndex;
//STRIP001 	if (Search(pDataObject, nIndex))
//STRIP001 		return nIndex;
//STRIP001 	else
//STRIP001 		return 0xffff;
//STRIP001 }

//------------------------------------------------------------------------

/*N*/ BOOL SortedCollection::Search(DataObject* pDataObject, USHORT& rIndex) const
/*N*/ {
/*N*/ 	rIndex = nCount;
/*N*/ 	BOOL bFound = FALSE;
/*N*/ 	short nLo = 0;
/*N*/ 	short nHi = nCount - 1;
/*N*/ 	short nIndex;
/*N*/ 	short nCompare;
/*N*/ 	while (nLo <= nHi)
/*N*/ 	{
/*N*/ 		nIndex = (nLo + nHi) / 2;
/*N*/ 		nCompare = Compare(pItems[nIndex], pDataObject);
/*N*/ 		if (nCompare < 0)
/*N*/ 			nLo = nIndex + 1;
/*N*/ 		else
/*N*/ 		{
/*N*/ 			nHi = nIndex - 1;
/*N*/ 			if (nCompare == 0)
/*N*/ 			{
/*N*/ 				bFound = TRUE;
/*N*/ 				nLo = nIndex;
/*N*/ 			}
/*N*/ 		}
/*N*/ 	}
/*N*/ 	rIndex = nLo;
/*N*/ 	return bFound;
/*N*/ }

//------------------------------------------------------------------------

/*N*/ BOOL SortedCollection::Insert(DataObject* pDataObject)
/*N*/ {
/*N*/ 	USHORT nIndex;
/*N*/ 	BOOL bFound = Search(pDataObject, nIndex);
/*N*/ 	if (bFound)
/*N*/ 	{
/*N*/ 		if (bDuplicates)
/*N*/ 			return AtInsert(nIndex, pDataObject);
/*N*/ 		else
/*N*/ 			return FALSE;
/*N*/ 	}
/*N*/ 	else
/*N*/ 		return AtInsert(nIndex, pDataObject);
/*N*/ }

//------------------------------------------------------------------------

//STRIP001 BOOL SortedCollection::InsertPos(DataObject* pDataObject, USHORT& nIndex)
//STRIP001 {
//STRIP001 	BOOL bFound = Search(pDataObject, nIndex);
//STRIP001 	if (bFound)
//STRIP001 	{
//STRIP001 		if (bDuplicates)
//STRIP001 			return AtInsert(nIndex, pDataObject);
//STRIP001 		else
//STRIP001 			return FALSE;
//STRIP001 	}
//STRIP001 	else
//STRIP001 		return AtInsert(nIndex, pDataObject);
//STRIP001 }

//------------------------------------------------------------------------

//STRIP001 BOOL SortedCollection::operator==(const SortedCollection& rCmp) const
//STRIP001 {
//STRIP001 	if ( nCount != rCmp.nCount )
//STRIP001 		return FALSE;
//STRIP001 	for (USHORT i=0; i<nCount; i++)
//STRIP001 		if ( !IsEqual(pItems[i],rCmp.pItems[i]) )
//STRIP001 			return FALSE;
//STRIP001 	return TRUE;
//STRIP001 }

//------------------------------------------------------------------------

//	IsEqual - komplette Inhalte vergleichen

//STRIP001 BOOL SortedCollection::IsEqual(DataObject* pKey1, DataObject* pKey2) const
//STRIP001 {
//STRIP001 	return ( Compare(pKey1, pKey2) == 0 );		// Default: nur Index vergleichen
//STRIP001 }

//------------------------------------------------------------------------

/*N*/ DataObject*	StrData::Clone() const
/*N*/ {
        DBG_BF_ASSERT(0, "STRIP");return NULL; //STRIP001 //STRIP001 	return new StrData(*this);
/*N*/ }

//------------------------------------------------------------------------

/*N*/ short StrCollection::Compare(DataObject* pKey1, DataObject* pKey2) const
/*N*/ {
/*N*/ 	StringCompare eComp = ((StrData*)pKey1)->aStr.CompareTo(((StrData*)pKey2)->aStr);
/*N*/ 	if (eComp == COMPARE_EQUAL)
/*N*/ 		return 0;
/*N*/ 	else if (eComp == COMPARE_LESS)
/*N*/ 		return -1;
/*N*/ 	else
/*N*/ 		return 1;
/*N*/ }

//------------------------------------------------------------------------

/*N*/ DataObject*	StrCollection::Clone() const
/*N*/ {
            DBG_BF_ASSERT(0, "STRIP"); return NULL;//STRIP001 	return new StrCollection(*this);
/*N*/ }

//------------------------------------------------------------------------

/*N*/ void StrCollection::Load( SvStream& rStream ) // Changetracking.sdc
/*N*/ {
/*N*/ 	ScReadHeader aHdr( rStream );
/*N*/ 	lcl_DeleteDataObjects( pItems, nCount );
/*N*/ 	BOOL bDups;
/*N*/ 	rStream >> bDups;
/*N*/ 	SetDups( bDups );
/*N*/ 	rStream >> nCount >> nLimit >> nDelta;
/*N*/ 	pItems = new DataObject*[nLimit];
/*N*/ 	String aStr;
/*N*/ 	rtl_TextEncoding eSet = rStream.GetStreamCharSet();
/*N*/ 	for ( USHORT i=0; i<nCount; i++ )
/*N*/ 	{
/*N*/ 		rStream.ReadByteString( aStr, eSet );
/*N*/ 		pItems[i] = new StrData( aStr );
/*N*/ 	}
/*N*/ }

/*N*/ void StrCollection::Store( SvStream& rStream ) const
/*N*/ {
/*N*/ 	ScWriteHeader aHdr( rStream );
/*N*/ 	BOOL bDups = IsDups();
/*N*/ 	rStream << bDups << nCount << nLimit << nDelta;
/*N*/ 	rtl_TextEncoding eSet = rStream.GetStreamCharSet();
/*N*/ 	for ( USHORT i=0; i<nCount; i++ )
/*N*/ 	{
/*N*/ 		rStream.WriteByteString( ((StrData*)pItems[i])->GetString(), eSet );
/*N*/ 	}
/*N*/ }

//------------------------------------------------------------------------
// TypedStrCollection
//------------------------------------------------------------------------

/*N*/ TypedStrData::TypedStrData( ScDocument* pDoc, USHORT nCol, USHORT nRow, USHORT nTab,
/*N*/ 								BOOL bAllStrings )
/*N*/ {
/*N*/ 	if ( pDoc->HasValueData( nCol, nRow, nTab ) )
/*N*/ 	{
/*?*/ 		pDoc->GetValue( nCol, nRow, nTab, nValue );
/*?*/ 		if (bAllStrings)
/*?*/ 			pDoc->GetString( nCol, nRow, nTab, aStrValue );
/*?*/ 		nStrType = 0;
/*N*/ 	}
/*N*/ 	else
/*N*/ 	{
/*N*/ 		pDoc->GetString( nCol, nRow, nTab, aStrValue );
/*N*/ 		nValue = 0.0;
/*N*/ 		nStrType = 1;		//! Typ uebergeben ?
/*N*/ 	}
/*N*/ }

/*N*/ DataObject*	TypedStrData::Clone() const
/*N*/ {
/*N*/ 	return new TypedStrData(*this);
/*N*/ }

//STRIP001 DataObject* TypedStrCollection::Clone() const
//STRIP001 {
//STRIP001 	return new TypedStrCollection(*this);
//STRIP001 }

/*N*/ short TypedStrCollection::Compare( DataObject* pKey1, DataObject* pKey2 ) const
/*N*/ {
/*N*/ 	short nResult = 0;
//STRIP001 
DBG_BF_ASSERT(0, "STRIP"); //STRIP001 //STRIP001 	if ( pKey1 && pKey2 )
//STRIP001 	{
//STRIP001 		TypedStrData& rData1 = (TypedStrData&)*pKey1;
//STRIP001 		TypedStrData& rData2 = (TypedStrData&)*pKey2;
//STRIP001 
//STRIP001 		if ( rData1.nStrType > rData2.nStrType )
//STRIP001 			nResult = 1;
//STRIP001 		else if ( rData1.nStrType < rData2.nStrType )
//STRIP001 			nResult = -1;
//STRIP001 		else if ( !rData1.nStrType /* && !rData2.nStrType */ )
//STRIP001 		{
//STRIP001 			//--------------------
//STRIP001 			// Zahlen vergleichen:
//STRIP001 			//--------------------
//STRIP001 			if ( rData1.nValue == rData2.nValue )
//STRIP001 				nResult = 0;
//STRIP001 			else if ( rData1.nValue < rData2.nValue )
//STRIP001 				nResult = -1;
//STRIP001 			else
//STRIP001 				nResult = 1;
//STRIP001 		}
//STRIP001 		else /* if ( rData1.nStrType && rData2.nStrType ) */
//STRIP001 		{
//STRIP001 			//---------------------
//STRIP001 			// Strings vergleichen:
//STRIP001 			//---------------------
//STRIP001 			if ( bCaseSensitive )
//STRIP001                 nResult = (short) ScGlobal::pCaseTransliteration->compareString(
//STRIP001 					rData1.aStrValue, rData2.aStrValue );
//STRIP001 			else
//STRIP001                 nResult = (short) ScGlobal::pTransliteration->compareString(
//STRIP001 					rData1.aStrValue, rData2.aStrValue );
//STRIP001 		}
//STRIP001 	}
//STRIP001 
/*N*/ return nResult;
/*N*/ }

//STRIP001 BOOL TypedStrCollection::FindText( const String& rStart, String& rResult,
//STRIP001 									USHORT& rPos, BOOL bBack ) const
//STRIP001 {
//STRIP001 	//	Die Collection ist nach String-Vergleichen sortiert, darum muss hier
//STRIP001 	//	alles durchsucht werden
//STRIP001 
//STRIP001 	BOOL bFound = FALSE;
//STRIP001 
//STRIP001 	String aOldResult;
//STRIP001 	if ( rPos != SCPOS_INVALID && rPos < nCount )
//STRIP001 	{
//STRIP001 		TypedStrData* pData = (TypedStrData*) pItems[rPos];
//STRIP001 		if (pData->nStrType)
//STRIP001 			aOldResult = pData->aStrValue;
//STRIP001 	}
//STRIP001 
//STRIP001 	if ( bBack )									// rueckwaerts
//STRIP001 	{
//STRIP001 		USHORT nStartPos = nCount;
//STRIP001 		if ( rPos != SCPOS_INVALID )
//STRIP001 			nStartPos = rPos;						// weitersuchen...
//STRIP001 
//STRIP001 		for ( USHORT i=nStartPos; i>0; )
//STRIP001 		{
//STRIP001 			--i;
//STRIP001 			TypedStrData* pData = (TypedStrData*) pItems[i];
//STRIP001 			if (pData->nStrType)
//STRIP001 			{
//STRIP001                 if ( ScGlobal::pTransliteration->isMatch( rStart, pData->aStrValue ) )
//STRIP001 				{
//STRIP001 					//	If the collection is case sensitive, it may contain several entries
//STRIP001 					//	that are equal when compared case-insensitive. They are skipped here.
//STRIP001 					if ( !bCaseSensitive || !aOldResult.Len() ||
//STRIP001                             !ScGlobal::pTransliteration->isEqual(
//STRIP001                             pData->aStrValue, aOldResult ) )
//STRIP001 					{
//STRIP001 						rResult = pData->aStrValue;
//STRIP001 						rPos = i;
//STRIP001 						bFound = TRUE;
//STRIP001 						break;
//STRIP001 					}
//STRIP001 				}
//STRIP001 			}
//STRIP001 		}
//STRIP001 	}
//STRIP001 	else											// vorwaerts
//STRIP001 	{
//STRIP001 		USHORT nStartPos = 0;
//STRIP001 		if ( rPos != SCPOS_INVALID )
//STRIP001 			nStartPos = rPos + 1;					// weitersuchen...
//STRIP001 
//STRIP001 		for ( USHORT i=nStartPos; i<nCount; i++ )
//STRIP001 		{
//STRIP001 			TypedStrData* pData = (TypedStrData*) pItems[i];
//STRIP001 			if (pData->nStrType)
//STRIP001 			{
//STRIP001                 if ( ScGlobal::pTransliteration->isMatch( rStart, pData->aStrValue ) )
//STRIP001 				{
//STRIP001 					//	If the collection is case sensitive, it may contain several entries
//STRIP001 					//	that are equal when compared case-insensitive. They are skipped here.
//STRIP001 					if ( !bCaseSensitive || !aOldResult.Len() ||
//STRIP001                             !ScGlobal::pTransliteration->isEqual(
//STRIP001                             pData->aStrValue, aOldResult ) )
//STRIP001 					{
//STRIP001 						rResult = pData->aStrValue;
//STRIP001 						rPos = i;
//STRIP001 						bFound = TRUE;
//STRIP001 						break;
//STRIP001 					}
//STRIP001 				}
//STRIP001 			}
//STRIP001 		}
//STRIP001 	}
//STRIP001 
//STRIP001 	return bFound;
//STRIP001 }

        // Gross-/Kleinschreibung anpassen

//STRIP001 BOOL TypedStrCollection::GetExactMatch( String& rString ) const
//STRIP001 {
//STRIP001 	for (USHORT i=0; i<nCount; i++)
//STRIP001 	{
//STRIP001 		TypedStrData* pData = (TypedStrData*) pItems[i];
//STRIP001         if ( pData->nStrType && ScGlobal::pTransliteration->isEqual(
//STRIP001                 pData->aStrValue, rString ) )
//STRIP001 		{
//STRIP001 			rString = pData->aStrValue;							// String anpassen
//STRIP001 			return TRUE;
//STRIP001 		}
//STRIP001 	}
//STRIP001 
//STRIP001 	return FALSE;
//STRIP001 }



}
