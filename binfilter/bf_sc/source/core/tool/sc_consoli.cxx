/*************************************************************************
 *
 *  $RCSfile: sc_consoli.cxx,v $
 *
 *  $Revision: 1.1 $
 *
 *  last change: $Author: aw $ $Date: 2003-10-02 14:43:04 $
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

// INCLUDE ---------------------------------------------------------------

#include <tools/debug.hxx>
#include <math.h>
#include <string.h>
#include "consoli.hxx"
#include "document.hxx"
#include "olinetab.hxx"
#include "globstr.hrc"
#include "subtotal.hxx"
#include "compiler.hxx"					// fuer errNoValue
#include "cell.hxx"

#define SC_CONS_NOTFOUND	0xFFFF

// STATIC DATA -----------------------------------------------------------

/*	Strings bei Gelegenheit ganz raus...
static USHORT nFuncRes[] = {				//	Reihenfolge wie bei enum ScSubTotalFunc
        0,									//	none
        STR_PIVOTFUNC_AVG,
        STR_PIVOTFUNC_COUNT,
        STR_PIVOTFUNC_COUNT2,
        STR_PIVOTFUNC_MAX,
        STR_PIVOTFUNC_MIN,
        STR_PIVOTFUNC_PROD,
        STR_PIVOTFUNC_STDDEV,
        STR_PIVOTFUNC_STDDEV2,
        STR_PIVOTFUNC_SUM,
        STR_PIVOTFUNC_VAR,
        STR_PIVOTFUNC_VAR2 };
*/

/*N*/ static OpCode eOpCodeTable[] = {			//	Reihenfolge wie bei enum ScSubTotalFunc
/*N*/ 		ocBad,								//	none
/*N*/ 		ocAverage,
/*N*/ 		ocCount,
/*N*/ 		ocCount2,
/*N*/ 		ocMax,
/*N*/ 		ocMin,
/*N*/ 		ocProduct,
/*N*/ 		ocStDev,
/*N*/ 		ocStDevP,
/*N*/ 		ocSum,
/*N*/ 		ocVar,
/*N*/ 		ocVarP };

// -----------------------------------------------------------------------

/*N*/ void ScReferenceList::AddEntry( USHORT nCol, USHORT nRow, USHORT nTab )
/*N*/ {
/*N*/ 	ScReferenceEntry* pOldData = pData;
/*N*/ 	pData = new ScReferenceEntry[ nFullSize+1 ];
/*N*/ 	if (pOldData)
/*N*/ 	{
/*N*/ 		memmove( pData, pOldData, nCount * sizeof(ScReferenceEntry) );
/*N*/ 		delete[] pOldData;
/*N*/ 	}
/*N*/ 	while (nCount < nFullSize)
/*N*/ 	{
/*N*/ 		pData[nCount].nCol = SC_CONS_NOTFOUND;
/*N*/ 		pData[nCount].nRow = SC_CONS_NOTFOUND;
/*N*/ 		pData[nCount].nTab = SC_CONS_NOTFOUND;
/*N*/ 		++nCount;
/*N*/ 	}
/*N*/ 	pData[nCount].nCol = nCol;
/*N*/ 	pData[nCount].nRow = nRow;
/*N*/ 	pData[nCount].nTab = nTab;
/*N*/ 	++nCount;
/*N*/ 	nFullSize = nCount;
/*N*/ }

/*N*/ void lcl_AddString( String**& pData, USHORT& nCount, const String& rInsert )
/*N*/ {
/*N*/ 	String** pOldData = pData;
/*N*/ 	pData = new String*[ nCount+1 ];
/*N*/ 	if (pOldData)
/*N*/ 	{
/*N*/ 		memmove( pData, pOldData, nCount * sizeof(String*) );
/*N*/ 		delete[] pOldData;
/*N*/ 	}
/*N*/ 	pData[nCount] = new String(rInsert);
/*N*/ 	++nCount;
/*N*/ }

// -----------------------------------------------------------------------

/*N*/ ScConsData::ScConsData() :
/*N*/ 	eFunction(SUBTOTAL_FUNC_SUM),
/*N*/ 	bReference(FALSE),
/*N*/ 	bColByName(FALSE),
/*N*/ 	bRowByName(FALSE),
/*N*/ 	bSubTitles(FALSE),
/*N*/ 	nColCount(0),
/*N*/ 	ppColHeaders(NULL),
/*N*/ 	nRowCount(0),
/*N*/ 	ppRowHeaders(NULL),
/*N*/ 	ppCount(NULL),
/*N*/ 	ppSum(NULL),
/*N*/ 	ppSumSqr(NULL),
/*N*/ 	ppRefs(NULL),
/*N*/ 	ppUsed(NULL),
/*N*/ 	nDataCount(0),
/*N*/ 	nTitleCount(0),
/*N*/ 	ppTitles(NULL),
/*N*/ 	ppTitlePos(NULL),
/*N*/ 	bCornerUsed(FALSE)
/*N*/ {
/*N*/ }

/*N*/ ScConsData::~ScConsData()
/*N*/ {
/*N*/ 	DeleteData();
/*N*/ }


/*N*/ #define DELETEARR(ppArray,nCount)	\
/*N*/ {									\
/*N*/ 	USHORT i; 						\
/*N*/ 	if (ppArray) 					\
/*N*/ 		for(i=0; i<nCount; i++)		\
/*N*/ 			delete[] ppArray[i];	\
/*N*/ 	delete[] ppArray;				\
/*N*/ 	ppArray = NULL;					\
/*N*/ }
/*N*/ 
/*N*/ #define DELETESTR(ppArray,nCount)	\
/*N*/ {									\
/*N*/ 	USHORT i; 						\
/*N*/ 	if (ppArray) 					\
/*N*/ 		for(i=0; i<nCount; i++)		\
/*N*/ 			delete ppArray[i];		\
/*N*/ 	delete[] ppArray;				\
/*N*/ 	ppArray = NULL;					\
/*N*/ }

/*N*/ void ScConsData::DeleteData()
/*N*/ {
/*N*/ 	USHORT i;
/*N*/ 
/*N*/ 	if (ppRefs)
/*N*/ 		for (i=0; i<nColCount; i++)
/*N*/ 		{
/*N*/ 			for (USHORT j=0; j<nRowCount; j++)
/*N*/ 				if (ppUsed[i][j])
/*N*/ 					ppRefs[i][j].Clear();
/*N*/ 			delete[] ppRefs[i];
/*N*/ 		}
/*N*/ 	delete[] ppRefs;
/*N*/ 	ppRefs = NULL;
/*N*/ 
/*N*/ //	DELETEARR( ppData1, nColCount );
/*N*/ //	DELETEARR( ppData2, nColCount );
/*N*/ 	DELETEARR( ppCount, nColCount );
/*N*/ 	DELETEARR( ppSum,   nColCount );
/*N*/ 	DELETEARR( ppSumSqr,nColCount );
/*N*/ 	DELETEARR( ppUsed,  nColCount );				// erst nach ppRefs !!!
/*N*/ 	DELETEARR( ppTitlePos, nRowCount );
/*N*/ 	DELETESTR( ppColHeaders, nColCount );
/*N*/ 	DELETESTR( ppRowHeaders, nRowCount );
/*N*/ 	DELETESTR( ppTitles, nTitleCount );
/*N*/ 	nTitleCount = 0;
/*N*/ 	nDataCount = 0;
/*N*/ 
/*N*/ 	if (bColByName) nColCount = 0;					// sonst stimmt ppColHeaders nicht
/*N*/ 	if (bRowByName) nRowCount = 0;
/*N*/ 
/*N*/ 	bCornerUsed = FALSE;
/*N*/ 	aCornerText.Erase();
/*N*/ }

/*N*/ #undef DELETEARR
/*N*/ #undef DELETESTR

/*N*/ void ScConsData::InitData( BOOL bDelete )
/*N*/ {
/*N*/ 	USHORT i;
/*N*/ 	if (bDelete)
/*N*/ 		DeleteData();
/*N*/ 
/*N*/ 	if (bReference && nColCount && !ppRefs)
/*N*/ 	{
/*N*/ 		ppRefs = new ScReferenceList*[nColCount];
/*N*/ 		for (i=0; i<nColCount; i++)
/*N*/ 			ppRefs[i] = new ScReferenceList[nRowCount];
/*N*/ 	}
/*N*/ 	else if (nColCount && !ppCount)
/*N*/ 	{
/*N*/ 		ppCount  = new double*[nColCount];
/*N*/ 		ppSum    = new double*[nColCount];
/*N*/ 		ppSumSqr = new double*[nColCount];
/*N*/ 		for (i=0; i<nColCount; i++)
/*N*/ 		{
/*N*/ 			ppCount[i]  = new double[nRowCount];
/*N*/ 			ppSum[i]    = new double[nRowCount];
/*N*/ 			ppSumSqr[i] = new double[nRowCount];
/*N*/ 		}
/*N*/ 	}
/*N*/ 
/*N*/ 	if (nColCount && !ppUsed)
/*N*/ 	{
/*N*/ 		ppUsed = new BOOL*[nColCount];
/*N*/ 		for (i=0; i<nColCount; i++)
/*N*/ 		{
/*N*/ 			ppUsed[i] = new BOOL[nRowCount];
/*N*/ 			memset( ppUsed[i], 0, nRowCount * sizeof(BOOL) );
/*N*/ 		}
/*N*/ 	}
/*N*/ 
/*N*/ 	if (nRowCount && nDataCount && !ppTitlePos)
/*N*/ 	{
/*N*/ 		ppTitlePos = new USHORT*[nRowCount];
/*N*/ 		for (i=0; i<nRowCount; i++)
/*N*/ 		{
/*N*/ 			ppTitlePos[i] = new USHORT[nDataCount];
/*N*/ 			memset( ppTitlePos[i], 0, nDataCount * sizeof(USHORT) );	//! unnoetig ?
/*N*/ 		}
/*N*/ 	}
/*N*/ 
/*N*/ 	//	CornerText: einzelner String
/*N*/ }

/*N*/ void ScConsData::DoneFields()
/*N*/ {
/*N*/ 	InitData(FALSE);
/*N*/ }

/*N*/ void ScConsData::SetSize( USHORT nCols, USHORT nRows )
/*N*/ {
/*N*/ 	DeleteData();
/*N*/ 	nColCount = nCols;
/*N*/ 	nRowCount = nRows;
/*N*/ }

/*N*/ void ScConsData::GetSize( USHORT& rCols, USHORT& rRows ) const
/*N*/ {
/*N*/ 	rCols = nColCount;
/*N*/ 	rRows = nRowCount;
/*N*/ }

/*N*/ void ScConsData::SetFlags( ScSubTotalFunc eFunc, BOOL bColName, BOOL bRowName, BOOL bRef )
/*N*/ {
/*N*/ 	DeleteData();
/*N*/ 	bReference = bRef;
/*N*/ 	bColByName = bColName;
/*N*/ 	if (bColName) nColCount = 0;
/*N*/ 	bRowByName = bRowName;
/*N*/ 	if (bRowName) nRowCount = 0;
/*N*/ 	eFunction = eFunc;
/*N*/ }

/*N*/ void ScConsData::AddFields( ScDocument* pSrcDoc, USHORT nTab,
/*N*/ 							USHORT nCol1, USHORT nRow1, USHORT nCol2, USHORT nRow2 )
/*N*/ {
/*N*/ 	++nDataCount;
/*N*/ 
/*N*/ 	String aTitle;
/*N*/ 
/*N*/ 	USHORT nStartCol = nCol1;
/*N*/ 	USHORT nStartRow = nRow1;
/*N*/ 	if (bColByName)	++nStartRow;
/*N*/ 	if (bRowByName)	++nStartCol;
/*N*/ 
/*N*/ 	if (bColByName)
/*N*/ 	{
/*N*/ 		for (USHORT nCol=nStartCol; nCol<=nCol2; nCol++)
/*N*/ 		{
/*N*/ 			pSrcDoc->GetString( nCol, nRow1, nTab, aTitle );
/*N*/ 			if (aTitle.Len())
/*N*/ 			{
/*N*/ 				BOOL bFound = FALSE;
/*N*/ 				for (USHORT i=0; i<nColCount && !bFound; i++)
/*N*/ 					if ( *ppColHeaders[i] == aTitle )
/*N*/ 						bFound = TRUE;
/*N*/ 				if (!bFound)
/*N*/ 					lcl_AddString( ppColHeaders, nColCount, aTitle );
/*N*/ 			}
/*N*/ 		}
/*N*/ 	}
/*N*/ 
/*N*/ 	if (bRowByName)
/*N*/ 	{
/*N*/ 		for (USHORT nRow=nStartRow; nRow<=nRow2; nRow++)
/*N*/ 		{
/*N*/ 			pSrcDoc->GetString( nCol1, nRow, nTab, aTitle );
/*N*/ 			if (aTitle.Len())
/*N*/ 			{
/*N*/ 				BOOL bFound = FALSE;
/*N*/ 				for (USHORT i=0; i<nRowCount && !bFound; i++)
/*N*/ 					if ( *ppRowHeaders[i] == aTitle )
/*N*/ 						bFound = TRUE;
/*N*/ 				if (!bFound)
/*N*/ 					lcl_AddString( ppRowHeaders, nRowCount, aTitle );
/*N*/ 			}
/*N*/ 		}
/*N*/ 	}
/*N*/ }

/*N*/ void ScConsData::AddName( const String& rName )
/*N*/ {
/*N*/ 	USHORT nArrX;
/*N*/ 	USHORT nArrY;
/*N*/ 
/*N*/ 	if (bReference)
/*N*/ 	{
/*N*/ 		lcl_AddString( ppTitles, nTitleCount, rName );
/*N*/ 
/*N*/ 		for (nArrY=0; nArrY<nRowCount; nArrY++)
/*N*/ 		{
/*N*/ 			//	Daten auf gleiche Laenge bringen
/*N*/ 
/*N*/ 			USHORT nMax = 0;
/*N*/ 			for (nArrX=0; nArrX<nColCount; nArrX++)
/*N*/ 				if (ppUsed[nArrX][nArrY])
/*N*/ 					nMax = Max( nMax, ppRefs[nArrX][nArrY].GetCount() );
/*N*/ 
/*N*/ 			for (nArrX=0; nArrX<nColCount; nArrX++)
/*N*/ 			{
/*N*/ 				if (!ppUsed[nArrX][nArrY])
/*N*/ 				{
/*N*/ 					ppUsed[nArrX][nArrY] = TRUE;
/*N*/ 					ppRefs[nArrX][nArrY].Init();
/*N*/ 				}
/*N*/ 				ppRefs[nArrX][nArrY].SetFullSize(nMax);
/*N*/ 			}
/*N*/ 
/*N*/ 			//	Positionen eintragen
/*N*/ 
/*N*/ 			if (ppTitlePos)
/*N*/ 				if (nTitleCount < nDataCount)
/*N*/ 					ppTitlePos[nArrY][nTitleCount] = nMax;
/*N*/ 		}
/*N*/ 	}
/*N*/ }

/*N*/ 								// rCount < 0 <=> Fehler aufgetreten

/*N*/ void lcl_UpdateArray( ScSubTotalFunc eFunc,
/*N*/ 						 double& rCount, double& rSum, double& rSumSqr, double nVal )
/*N*/ {
/*N*/ 	if (rCount < 0.0)
/*N*/ 		return;
/*N*/ 	switch (eFunc)
/*N*/ 	{
/*N*/ 		case SUBTOTAL_FUNC_SUM:
/*N*/ 			if (!SubTotal::SafePlus(rSum, nVal))
/*N*/ 				rCount = -MAXDOUBLE;
/*N*/ 			break;
/*N*/ 		case SUBTOTAL_FUNC_PROD:
/*N*/ 			if (!SubTotal::SafeMult(rSum, nVal))
/*N*/ 				rCount = -MAXDOUBLE;
/*N*/ 			break;
/*N*/ 		case SUBTOTAL_FUNC_CNT:
/*N*/ 		case SUBTOTAL_FUNC_CNT2:
/*N*/ 			rCount += 1.0;
/*N*/ 			break;
/*N*/ 		case SUBTOTAL_FUNC_AVE:
/*N*/ 			if (!SubTotal::SafePlus(rSum, nVal))
/*N*/ 				rCount = -MAXDOUBLE;
/*N*/ 			else
/*N*/ 				rCount += 1.0;
/*N*/ 			break;
/*N*/ 		case SUBTOTAL_FUNC_MAX:
/*N*/ 			if (nVal > rSum)
/*N*/ 				rSum = nVal;
/*N*/ 			break;
/*N*/ 		case SUBTOTAL_FUNC_MIN:
/*N*/ 			if (nVal < rSum)
/*N*/ 				rSum = nVal;
/*N*/ 			break;
/*N*/ 		case SUBTOTAL_FUNC_STD:
/*N*/ 		case SUBTOTAL_FUNC_STDP:
/*N*/ 		case SUBTOTAL_FUNC_VAR:
/*N*/ 		case SUBTOTAL_FUNC_VARP:
/*N*/ 		{
/*N*/ 			BOOL bOk = SubTotal::SafePlus(rSum, nVal);
/*N*/ 			bOk = bOk && SubTotal::SafeMult(nVal, nVal);
/*N*/ 			bOk = bOk && SubTotal::SafePlus(rSumSqr, nVal);
/*N*/ 			if (!bOk)
/*N*/ 				rCount = -MAXDOUBLE;
/*N*/ 			else
/*N*/ 				rCount += 1.0;
/*N*/ 			break;
/*N*/ 		}
/*N*/ 	}
/*N*/ }

/*N*/ void lcl_InitArray( ScSubTotalFunc eFunc,
/*N*/ 					   double& rCount, double& rSum, double& rSumSqr, double nVal )
/*N*/ {
/*N*/ 	rCount = 1.0;
/*N*/ 	switch (eFunc)
/*N*/ 	{
/*N*/ 		case SUBTOTAL_FUNC_SUM:
/*N*/ 		case SUBTOTAL_FUNC_MAX:
/*N*/ 		case SUBTOTAL_FUNC_MIN:
/*N*/ 		case SUBTOTAL_FUNC_PROD:
/*N*/ 		case SUBTOTAL_FUNC_AVE:
/*N*/ 			rSum = nVal;
/*N*/ 			break;
/*N*/ 		case SUBTOTAL_FUNC_STD:
/*N*/ 		case SUBTOTAL_FUNC_STDP:
/*N*/ 		case SUBTOTAL_FUNC_VAR:
/*N*/ 		case SUBTOTAL_FUNC_VARP:
/*N*/ 		{
/*N*/ 			rSum = nVal;
/*N*/ 			BOOL bOk = SubTotal::SafeMult(nVal, nVal);
/*N*/ 			if (bOk)
/*N*/ 				rSumSqr = nVal;
/*N*/ 			else
/*N*/ 				rCount = -MAXDOUBLE;
/*N*/ 		}
/*N*/ 			break;
/*N*/ 		default:
/*N*/ 			break;
/*N*/ 	}
/*N*/ }

/*N*/ double lcl_CalcData( ScSubTotalFunc eFunc,
/*N*/ 						double fCount, double fSum, double fSumSqr)
/*N*/ {
/*N*/ 	if (fCount < 0.0)
/*N*/ 		return 0.0;
/*N*/ 	double fVal = 0.0;
/*N*/ 	switch (eFunc)
/*N*/ 	{
/*N*/ 		case SUBTOTAL_FUNC_CNT:
/*N*/ 		case SUBTOTAL_FUNC_CNT2:
/*N*/ 			fVal = fCount;
/*N*/ 			break;
/*N*/ 		case SUBTOTAL_FUNC_SUM:
/*N*/ 		case SUBTOTAL_FUNC_MAX:
/*N*/ 		case SUBTOTAL_FUNC_MIN:
/*N*/ 		case SUBTOTAL_FUNC_PROD:
/*N*/ 			fVal = fSum;
/*N*/ 			break;
/*N*/ 		case SUBTOTAL_FUNC_AVE:
/*N*/ 			if (fCount > 0.0)
/*N*/ 				fVal = fSum / fCount;
/*N*/ 			else
/*N*/ 				fCount = -MAXDOUBLE;
/*N*/ 			break;
/*N*/ 		case SUBTOTAL_FUNC_STD:
/*N*/ 		{
/*N*/ 			if (fCount > 1 && SubTotal::SafeMult(fSum, fSum))
/*N*/ 				fVal = sqrt((fSumSqr - fSum/fCount)/(fCount-1.0));
/*N*/ 			else
/*N*/ 				fCount = -MAXDOUBLE;
/*N*/ 		}
/*N*/ 			break;
/*N*/ 		case SUBTOTAL_FUNC_STDP:
/*N*/ 		{
/*N*/ 			if (fCount > 0 && SubTotal::SafeMult(fSum, fSum))
/*N*/ 				fVal = sqrt((fSumSqr - fSum/fCount)/fCount);
/*N*/ 			else
/*N*/ 				fCount = -MAXDOUBLE;
/*N*/ 		}
/*N*/ 			break;
/*N*/ 		case SUBTOTAL_FUNC_VAR:
/*N*/ 		{
/*N*/ 			if (fCount > 1 && SubTotal::SafeMult(fSum, fSum))
/*N*/ 				fVal = (fSumSqr - fSum/fCount)/(fCount-1.0);
/*N*/ 			else
/*N*/ 				fCount = -MAXDOUBLE;
/*N*/ 		}
/*N*/ 			break;
/*N*/ 		case SUBTOTAL_FUNC_VARP:
/*N*/ 		{
/*N*/ 			if (fCount > 0 && SubTotal::SafeMult(fSum, fSum))
/*N*/ 				fVal = (fSumSqr - fSum/fCount)/fCount;
/*N*/ 			else
/*N*/ 				fCount = -MAXDOUBLE;
/*N*/ 		}
/*N*/ 			break;
/*N*/ 		default:
/*N*/ 		{
/*N*/ 			DBG_ERROR("unbekannte Funktion bei Consoli::CalcData");
/*N*/ 			fCount = -MAXDOUBLE;
/*N*/ 		}
/*N*/ 			break;
/*N*/ 	}
/*N*/ 	return fVal;
/*N*/ }

/*N*/ void ScConsData::AddData( ScDocument* pSrcDoc, USHORT nTab,
/*N*/ 							USHORT nCol1, USHORT nRow1, USHORT nCol2, USHORT nRow2 )
/*N*/ {
/*N*/ 	PutInOrder(nCol1,nCol2);
/*N*/ 	PutInOrder(nRow1,nRow2);
/*N*/ 	if ( nCol2 >= nCol1 + nColCount && !bColByName )
/*N*/ 	{
/*N*/ 		DBG_ASSERT(0,"Bereich zu gross");
/*N*/ 		nCol2 = nCol1 + nColCount - 1;
/*N*/ 	}
/*N*/ 	if ( nRow2 >= nRow1 + nRowCount && !bRowByName )
/*N*/ 	{
/*N*/ 		DBG_ASSERT(0,"Bereich zu gross");
/*N*/ 		nRow2 = nRow1 + nRowCount - 1;
/*N*/ 	}
/*N*/ 
/*N*/ 	USHORT nCol;
/*N*/ 	USHORT nRow;
/*N*/ 
/*N*/ 	//		Ecke links oben
/*N*/ 
/*N*/ 	if ( bColByName && bRowByName )
/*N*/ 	{
/*N*/ 		String aThisCorner;
/*N*/ 		pSrcDoc->GetString(nCol1,nRow1,nTab,aThisCorner);
/*N*/ 		if (bCornerUsed)
/*N*/ 		{
/*N*/ 			if (aCornerText != aThisCorner)
/*N*/ 				aCornerText.Erase();
/*N*/ 		}
/*N*/ 		else
/*N*/ 		{
/*N*/ 			aCornerText = aThisCorner;
/*N*/ 			bCornerUsed = TRUE;
/*N*/ 		}
/*N*/ 	}
/*N*/ 
/*N*/ 	//		Titel suchen
/*N*/ 
/*N*/ 	USHORT nStartCol = nCol1;
/*N*/ 	USHORT nStartRow = nRow1;
/*N*/ 	if (bColByName)	++nStartRow;
/*N*/ 	if (bRowByName)	++nStartCol;
/*N*/ 	String aTitle;
/*N*/ 	USHORT*	pDestCols = NULL;
/*N*/ 	USHORT*	pDestRows = NULL;
/*N*/ 	if (bColByName)
/*N*/ 	{
/*N*/ 		pDestCols = new USHORT[nCol2-nStartCol+1];
/*N*/ 		for (nCol=nStartCol; nCol<=nCol2; nCol++)
/*N*/ 		{
/*N*/ 			pSrcDoc->GetString(nCol,nRow1,nTab,aTitle);
/*N*/ 			USHORT nPos = SC_CONS_NOTFOUND;
/*N*/ 			if (aTitle.Len())
/*N*/ 			{
/*N*/ 				BOOL bFound = FALSE;
/*N*/ 				for (USHORT i=0; i<nColCount && !bFound; i++)
/*N*/ 					if ( *ppColHeaders[i] == aTitle )
/*N*/ 					{
/*N*/ 						nPos = i;
/*N*/ 						bFound = TRUE;
/*N*/ 					}
/*N*/ 				DBG_ASSERT(bFound, "Spalte nicht gefunden");
/*N*/ 			}
/*N*/ 			pDestCols[nCol-nStartCol] = nPos;
/*N*/ 		}
/*N*/ 	}
/*N*/ 	if (bRowByName)
/*N*/ 	{
/*N*/ 		pDestRows = new USHORT[nRow2-nStartRow+1];
/*N*/ 		for (nRow=nStartRow; nRow<=nRow2; nRow++)
/*N*/ 		{
/*N*/ 			pSrcDoc->GetString(nCol1,nRow,nTab,aTitle);
/*N*/ 			USHORT nPos = SC_CONS_NOTFOUND;
/*N*/ 			if (aTitle.Len())
/*N*/ 			{
/*N*/ 				BOOL bFound = FALSE;
/*N*/ 				for (USHORT i=0; i<nRowCount && !bFound; i++)
/*N*/ 					if ( *ppRowHeaders[i] == aTitle )
/*N*/ 					{
/*N*/ 						nPos = i;
/*N*/ 						bFound = TRUE;
/*N*/ 					}
/*N*/ 				DBG_ASSERT(bFound, "Zeile nicht gefunden");
/*N*/ 			}
/*N*/ 			pDestRows[nRow-nStartRow] = nPos;
/*N*/ 		}
/*N*/ 	}
/*N*/ 	nCol1 = nStartCol;
/*N*/ 	nRow1 = nStartRow;
/*N*/ 
/*N*/ 	//		Daten
/*N*/ 
/*N*/ 	BOOL bAnyCell = ( eFunction == SUBTOTAL_FUNC_CNT2 );
/*N*/ 	for (nCol=nCol1; nCol<=nCol2; nCol++)
/*N*/ 	{
/*N*/ 		USHORT nArrX = nCol-nCol1;
/*N*/ 		if (bColByName)	nArrX = pDestCols[nArrX];
/*N*/ 		if (nArrX != SC_CONS_NOTFOUND)
/*N*/ 		{
/*?*/ 			DBG_ASSERT(0, "STRIP"); //STRIP001 for (nRow=nRow1; nRow<=nRow2; nRow++)
//STRIP001 /*?*/ 			{
//STRIP001 /*?*/ 				USHORT nArrY = nRow-nRow1;
//STRIP001 /*?*/ 				if (bRowByName)	nArrY = pDestRows[nArrY];
//STRIP001 /*?*/ 				if ( nArrY != SC_CONS_NOTFOUND && (
//STRIP001 /*?*/ 						bAnyCell ? pSrcDoc->HasData( nCol, nRow, nTab )
//STRIP001 /*?*/ 								 : pSrcDoc->HasValueData( nCol, nRow, nTab ) ) )
//STRIP001 /*?*/ 				{
//STRIP001 /*?*/ 					if (bReference)
//STRIP001 /*?*/ 					{
//STRIP001 /*?*/ 						if (ppUsed[nArrX][nArrY])
//STRIP001 /*?*/ 							ppRefs[nArrX][nArrY].AddEntry( nCol, nRow, nTab );
//STRIP001 /*?*/ 						else
//STRIP001 /*?*/ 						{
//STRIP001 /*?*/ 							ppUsed[nArrX][nArrY] = TRUE;
//STRIP001 /*?*/ 							ppRefs[nArrX][nArrY].Init();
//STRIP001 /*?*/ 							ppRefs[nArrX][nArrY].AddEntry( nCol, nRow, nTab );
//STRIP001 /*?*/ 						}
//STRIP001 /*?*/ 					}
//STRIP001 /*?*/ 					else
//STRIP001 /*?*/ 					{
//STRIP001 /*?*/ 						double nVal;
//STRIP001 /*?*/ 						pSrcDoc->GetValue( nCol, nRow, nTab, nVal );
//STRIP001 /*?*/ 						if (ppUsed[nArrX][nArrY])
//STRIP001 /*?*/ 							lcl_UpdateArray( eFunction, ppCount[nArrX][nArrY],
//STRIP001 /*?*/ 										 ppSum[nArrX][nArrY], ppSumSqr[nArrX][nArrY],
//STRIP001 /*?*/ 										 nVal);
//STRIP001 /*?*/ 						else
//STRIP001 /*?*/ 						{
//STRIP001 /*?*/ 							ppUsed[nArrX][nArrY] = TRUE;
//STRIP001 /*?*/ 							lcl_InitArray( eFunction, ppCount[nArrX][nArrY],
//STRIP001 /*?*/ 												  ppSum[nArrX][nArrY],
//STRIP001 /*?*/ 												  ppSumSqr[nArrX][nArrY], nVal );
//STRIP001 /*?*/ 						}
//STRIP001 /*?*/ 					}
//STRIP001 /*?*/ 				}
//STRIP001 /*?*/ 			}
/*N*/ 		}
/*N*/ 	}
/*N*/ 
/*N*/ 	delete[] pDestCols;
/*N*/ 	delete[] pDestRows;
/*N*/ }

//	vorher testen, wieviele Zeilen eingefuegt werden (fuer Undo)

/*N*/ USHORT ScConsData::GetInsertCount() const
/*N*/ {
/*N*/ 	USHORT nInsert = 0;
/*N*/ 	USHORT nArrX;
/*N*/ 	USHORT nArrY;
/*N*/ 	if ( ppRefs && ppUsed )
/*N*/ 	{
/*N*/ 		for (nArrY=0; nArrY<nRowCount; nArrY++)
/*N*/ 		{
/*N*/ 			USHORT nNeeded = 0;
/*N*/ 			for (nArrX=0; nArrX<nColCount; nArrX++)
/*N*/ 				if (ppUsed[nArrX][nArrY])
/*N*/ 					nNeeded = Max( nNeeded, ppRefs[nArrX][nArrY].GetCount() );
/*N*/ 
/*N*/ 			nInsert += nNeeded;
/*N*/ 		}
/*N*/ 	}
/*N*/ 	return nInsert;
/*N*/ }

//	fertige Daten ins Dokument schreiben
//!	optimieren nach Spalten?

/*N*/ void ScConsData::OutputToDocument( ScDocument* pDestDoc, USHORT nCol, USHORT nRow, USHORT nTab )
/*N*/ {
/*N*/ 	OpCode eOpCode = eOpCodeTable[eFunction];
/*N*/ 
/*N*/ 	USHORT nArrX;
/*N*/ 	USHORT nArrY;
/*N*/ 	USHORT nCount;
/*N*/ 	USHORT nPos;
/*N*/ 	USHORT i;
/*N*/ 
/*N*/ 	//	Ecke links oben
/*N*/ 
/*N*/ 	if ( bColByName && bRowByName && aCornerText.Len() )
/*N*/ 		pDestDoc->SetString( nCol, nRow, nTab, aCornerText );
/*N*/ 
/*N*/ 	//	Titel
/*N*/ 
/*N*/ 	USHORT nStartCol = nCol;
/*N*/ 	USHORT nStartRow = nRow;
/*N*/ 	if (bColByName)	++nStartRow;
/*N*/ 	if (bRowByName)	++nStartCol;
/*N*/ 
/*N*/ 	if (bColByName)
/*N*/ 		for (i=0; i<nColCount; i++)
/*N*/ 			pDestDoc->SetString( nStartCol+i, nRow, nTab, *ppColHeaders[i] );
/*N*/ 	if (bRowByName)
/*N*/ 		for (i=0; i<nRowCount; i++)
/*N*/ 			pDestDoc->SetString( nCol, nStartRow+i, nTab, *ppRowHeaders[i] );
/*N*/ 
/*N*/ 	nCol = nStartCol;
/*N*/ 	nRow = nStartRow;
/*N*/ 
/*N*/ 	//	Daten
/*N*/ 
/*N*/ 	if ( ppCount && ppUsed )							// Werte direkt einfuegen
/*N*/ 	{
/*N*/ 		for (nArrX=0; nArrX<nColCount; nArrX++)
/*N*/ 			for (nArrY=0; nArrY<nRowCount; nArrY++)
/*N*/ 				if (ppUsed[nArrX][nArrY])
/*N*/ 				{
/*N*/ 					double fVal = lcl_CalcData( eFunction, ppCount[nArrX][nArrY],
/*N*/ 												ppSum[nArrX][nArrY],
/*N*/ 												ppSumSqr[nArrX][nArrY]);
/*N*/ 					if (ppCount[nArrX][nArrY] < 0.0)
/*N*/ 						pDestDoc->SetError( nCol+nArrX, nRow+nArrY, nTab, errNoValue );
/*N*/ 					else
/*N*/ 						pDestDoc->SetValue( nCol+nArrX, nRow+nArrY, nTab, fVal );
/*N*/ 				}
/*N*/ 	}
/*N*/ 
/*N*/ 	if ( ppRefs && ppUsed )								// Referenzen einfuegen
/*N*/ 	{
/*N*/ 								//! unterscheiden, ob nach Kategorien aufgeteilt
/*N*/ 		String aString;
/*N*/ 
/*N*/ 		SingleRefData aSRef;		// Daten fuer Referenz-Formelzellen
/*N*/ 		aSRef.InitFlags();
/*N*/ 		aSRef.SetFlag3D(TRUE);
/*N*/ 
/*N*/ 		ComplRefData aCRef;			// Daten fuer Summen-Zellen
/*N*/ 		aCRef.InitFlags();
/*N*/ 		aCRef.Ref1.SetColRel(TRUE); aCRef.Ref1.SetRowRel(TRUE); aCRef.Ref1.SetTabRel(TRUE);
/*N*/ 		aCRef.Ref2.SetColRel(TRUE); aCRef.Ref2.SetRowRel(TRUE); aCRef.Ref2.SetTabRel(TRUE);
/*N*/ 
/*N*/ 		for (nArrY=0; nArrY<nRowCount; nArrY++)
/*N*/ 		{
/*N*/ 			USHORT nNeeded = 0;
/*N*/ 			for (nArrX=0; nArrX<nColCount; nArrX++)
/*N*/ 				if (ppUsed[nArrX][nArrY])
/*N*/ 					nNeeded = Max( nNeeded, ppRefs[nArrX][nArrY].GetCount() );
/*N*/ 
/*N*/ 			if (nNeeded)
/*N*/ 			{
/*?*/ 				DBG_ASSERT(0, "STRIP"); //STRIP001 pDestDoc->InsertRow( 0,nTab, MAXCOL,nTab, nRow+nArrY, nNeeded );
//STRIP001 /*?*/ 
//STRIP001 /*?*/ 				for (nArrX=0; nArrX<nColCount; nArrX++)
//STRIP001 /*?*/ 					if (ppUsed[nArrX][nArrY])
//STRIP001 /*?*/ 					{
//STRIP001 /*?*/ 						ScReferenceList& rList = ppRefs[nArrX][nArrY];
//STRIP001 /*?*/ 						nCount = rList.GetCount();
//STRIP001 /*?*/ 						if (nCount)
//STRIP001 /*?*/ 						{
//STRIP001 /*?*/ 							for (nPos=0; nPos<nCount; nPos++)
//STRIP001 /*?*/ 							{
//STRIP001 /*?*/ 								ScReferenceEntry aRef = rList.GetEntry(nPos);
//STRIP001 /*?*/ 								if (aRef.nTab != SC_CONS_NOTFOUND)
//STRIP001 /*?*/ 								{
//STRIP001 /*?*/ 									//	Referenz einfuegen (absolut, 3d)
//STRIP001 /*?*/ 
//STRIP001 /*?*/ 									aSRef.nCol = aRef.nCol;
//STRIP001 /*?*/ 									aSRef.nRow = aRef.nRow;
//STRIP001 /*?*/ 									aSRef.nTab = aRef.nTab;
//STRIP001 /*?*/ 
//STRIP001 /*?*/ 									ScTokenArray aRefArr;
//STRIP001 /*?*/ 									aRefArr.AddSingleReference(aSRef);
//STRIP001 /*?*/ 									aRefArr.AddOpCode(ocStop);
//STRIP001 /*?*/ 									ScAddress aDest( nCol+nArrX, nRow+nArrY+nPos, nTab );
//STRIP001 /*?*/ 									ScBaseCell* pCell = new ScFormulaCell( pDestDoc, aDest, &aRefArr );
//STRIP001 /*?*/ 									pDestDoc->PutCell( aDest.Col(), aDest.Row(), aDest.Tab(), pCell );
//STRIP001 /*?*/ 								}
//STRIP001 /*?*/ 							}
//STRIP001 /*?*/ 
//STRIP001 /*?*/ 							//	Summe einfuegen (relativ, nicht 3d)
//STRIP001 /*?*/ 
//STRIP001 /*?*/ 							ScAddress aDest( nCol+nArrX, nRow+nArrY+nNeeded, nTab );
//STRIP001 /*?*/ 
//STRIP001 /*?*/ 							aCRef.Ref1.nTab = aCRef.Ref2.nTab = nTab;
//STRIP001 /*?*/ 							aCRef.Ref1.nCol = aCRef.Ref2.nCol = nCol+nArrX;
//STRIP001 /*?*/ 							aCRef.Ref1.nRow = nRow+nArrY;
//STRIP001 /*?*/ 							aCRef.Ref2.nRow = nRow+nArrY+nNeeded-1;
//STRIP001 /*?*/ 							aCRef.CalcRelFromAbs( aDest );
//STRIP001 /*?*/ 
//STRIP001 /*?*/ 							ScTokenArray aArr;
//STRIP001 /*?*/ 							aArr.AddOpCode(eOpCode);			// ausgewaehlte Funktion
//STRIP001 /*?*/ 							aArr.AddOpCode(ocOpen);
//STRIP001 /*?*/ 							aArr.AddDoubleReference(aCRef);
//STRIP001 /*?*/ 							aArr.AddOpCode(ocClose);
//STRIP001 /*?*/ 							aArr.AddOpCode(ocStop);
//STRIP001 /*?*/ 							ScBaseCell* pCell = new ScFormulaCell( pDestDoc, aDest, &aArr );
//STRIP001 /*?*/ 							pDestDoc->PutCell( aDest.Col(), aDest.Row(), aDest.Tab(), pCell );
//STRIP001 /*?*/ 						}
//STRIP001 /*?*/ 					}
//STRIP001 /*?*/ 
//STRIP001 /*?*/ 				//	Gliederung einfuegen
//STRIP001 /*?*/ 
//STRIP001 /*?*/ 				ScOutlineArray* pOutArr = pDestDoc->GetOutlineTable( nTab, TRUE )->GetRowArray();
//STRIP001 /*?*/ 				USHORT nOutStart = nRow+nArrY;
//STRIP001 /*?*/ 				USHORT nOutEnd = nRow+nArrY+nNeeded-1;
//STRIP001 /*?*/ 				BOOL bSize = FALSE;
//STRIP001 /*?*/ 				pOutArr->Insert( nOutStart, nOutEnd, bSize );
//STRIP001 /*?*/ 				for (USHORT nOutRow=nOutStart; nOutRow<=nOutEnd; nOutRow++)
//STRIP001 /*?*/ 					pDestDoc->ShowRow( nOutRow, nTab, FALSE );
//STRIP001 /*?*/ 				pDestDoc->UpdateOutlineRow( nOutStart, nOutEnd, nTab, FALSE );
//STRIP001 /*?*/ 
//STRIP001 /*?*/ 				//	Zwischentitel
//STRIP001 /*?*/ 
//STRIP001 /*?*/ 				if (ppTitlePos && ppTitles && ppRowHeaders)
//STRIP001 /*?*/ 				{
//STRIP001 /*?*/ 					String aDelim( RTL_CONSTASCII_USTRINGPARAM(" / ") );
//STRIP001 /*?*/ 					for (nPos=0; nPos<nDataCount; nPos++)
//STRIP001 /*?*/ 					{
//STRIP001 /*?*/ 						USHORT nTPos = ppTitlePos[nArrY][nPos];
//STRIP001 /*?*/ 						BOOL bDo = TRUE;
//STRIP001 /*?*/ 						if (nPos+1<nDataCount)
//STRIP001 /*?*/ 							if (ppTitlePos[nArrY][nPos+1] == nTPos)
//STRIP001 /*?*/ 								bDo = FALSE;									// leer
//STRIP001 /*?*/ 						if ( bDo && nTPos < nNeeded )
//STRIP001 /*?*/ 						{
//STRIP001 /*?*/ 							aString =  *ppRowHeaders[nArrY];
//STRIP001 /*?*/ 							aString += aDelim;
//STRIP001 /*?*/ 							aString += *ppTitles[nPos];
//STRIP001 /*?*/ 							pDestDoc->SetString( nCol-1, nRow+nArrY+nTPos, nTab, aString );
//STRIP001 /*?*/ 						}
//STRIP001 /*?*/ 					}
//STRIP001 /*?*/ 				}
//STRIP001 /*?*/ 
//STRIP001 /*?*/ 				nRow += nNeeded;
/*N*/ 			}
/*N*/ 		}
/*N*/ 	}
/*N*/ }





