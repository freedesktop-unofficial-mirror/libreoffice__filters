/*************************************************************************
 *
 *  $RCSfile: sch_datalog.cxx,v $
 *
 *  $Revision: 1.3 $
 *
 *  last change: $Author: rt $ $Date: 2004-05-05 16:39:53 $
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
#include "datalog.hxx"
namespace binfilter {

#define SCHLOGBOOK_DEFOVERHEAD 20

#define MAX(a,b)   ((a>b)?(a):(b))


//STRIP001 BOOL SchDataLogBook::IsValid() const
//STRIP001 {
//STRIP001 	return mbValid;
//STRIP001 }
//STRIP001 BOOL SchDataLogBook::IsChanged() const
//STRIP001 {
//STRIP001 	if(mbGetCol)return mbColChanged;
//STRIP001 	return(mbRowChanged);
//STRIP001 }
//STRIP001 BOOL SchDataLogBook::IsRowChanged() const
//STRIP001 {
//STRIP001 	return mbRowChanged;
//STRIP001 }
//STRIP001 BOOL SchDataLogBook::IsColChanged() const
//STRIP001 {
//STRIP001 	return mbColChanged;
//STRIP001 }
/*N*/ SchDataLogBook::SchDataLogBook(const SchMemChart& aMemChart)
/*N*/ {DBG_BF_ASSERT(0, "STRIP"); //STRIP001 
//STRIP001 	mnColsAdded=0;
//STRIP001 	mnRowsAdded=0;
//STRIP001 	mbGetCol=TRUE; //Achtung, nur damit es ueberhaupt definiert ist!
//STRIP001 	mbValid=TRUE;
//STRIP001 	mbColChanged=FALSE;
//STRIP001 	mbRowChanged=FALSE;
//STRIP001 
//STRIP001 	//Zusaetzlich allozierter Speicher, um Fragmentierung klein zu halten
//STRIP001 	mnRowsLeft=SCHLOGBOOK_DEFOVERHEAD;
//STRIP001 	mnColsLeft=SCHLOGBOOK_DEFOVERHEAD;
//STRIP001 
//STRIP001 	mnRows=aMemChart.GetRowCount();
//STRIP001 	mnCols=aMemChart.GetColCount();
//STRIP001 
//STRIP001 	mnRowsInitial=mnRows;
//STRIP001 	mnColsInitial=mnCols;
//STRIP001 
//STRIP001 	mpRowCoordinates=new long[mnRows+mnRowsLeft];
//STRIP001 	mpColCoordinates=new long[mnCols+mnColsLeft];
//STRIP001 
//STRIP001 	if(!mpRowCoordinates || !mpColCoordinates)
//STRIP001 	{
//STRIP001 		mbValid=FALSE;
//STRIP001 	}
//STRIP001 	else   //initialisieren
//STRIP001 	{
//STRIP001 		long n;
//STRIP001 		for(n=0;n<mnRows;n++)
//STRIP001 			mpRowCoordinates[n]=n;
//STRIP001 		for(n=0;n<mnCols;n++)
//STRIP001 			mpColCoordinates[n]=n;
//STRIP001 	}
/*N*/ }
/*N*/ SchDataLogBook::~SchDataLogBook()
/*N*/ {DBG_BF_ASSERT(0, "STRIP"); //STRIP001 
//STRIP001 	if(mpColCoordinates)
//STRIP001 		delete [] mpColCoordinates;
//STRIP001 
//STRIP001 	if(mpRowCoordinates)
//STRIP001 		delete [] mpRowCoordinates;
/*N*/ }

//STRIP001 void SchDataLogBook::Reset()
//STRIP001 {
//STRIP001 	mbValid=TRUE;
//STRIP001 	mbColChanged=FALSE;
//STRIP001 	mbRowChanged=FALSE;
//STRIP001 
//STRIP001 	mnColsAdded=0;
//STRIP001 	mnRowsAdded=0;
//STRIP001 
//STRIP001 	mnRowsInitial=mnRows;
//STRIP001 	mnColsInitial=mnCols;
//STRIP001 
//STRIP001 
//STRIP001 	if(!mpRowCoordinates || !mpColCoordinates)
//STRIP001 	{
//STRIP001 		mbValid=FALSE;
//STRIP001 	}
//STRIP001 	else   //initialisieren
//STRIP001 	{
//STRIP001 		long n;
//STRIP001 		for(n=0;n<mnRows;n++)
//STRIP001 			mpRowCoordinates[n]=n;
//STRIP001 		for(n=0;n<mnCols;n++)
//STRIP001 			mpColCoordinates[n]=n;
//STRIP001 	}
//STRIP001 }


//STRIP001 void SchDataLogBook::DeleteRow(const long nRow)
//STRIP001 {
//STRIP001 	if( (nRow<mnRows) && mbValid)
//STRIP001 	{
//STRIP001 		long n;
//STRIP001 
//STRIP001 		//Speicher freigeben
//STRIP001 		mnRows--;
//STRIP001 		mnRowsLeft++;
//STRIP001 
//STRIP001 		if(mpRowCoordinates[nRow]==SCH_DATALOG_ANY)
//STRIP001 			mnRowsAdded--;
//STRIP001 
//STRIP001 		//loeschen der CoordinatenInformation
//STRIP001 		for(n=nRow;n<mnRows;n++)
//STRIP001 			mpRowCoordinates[n]=mpRowCoordinates[n+1];
//STRIP001 
//STRIP001 		mbRowChanged=TRUE;
//STRIP001 	}
//STRIP001 }

//STRIP001 void SchDataLogBook::DeleteCol(const long nCol)
//STRIP001 {
//STRIP001 	if( (nCol<mnCols)  && mbValid)
//STRIP001 	{
//STRIP001 		long n;
//STRIP001 
//STRIP001 		//Speicher freigeben
//STRIP001 		mnCols--;
//STRIP001 		mnColsLeft++;
//STRIP001 		if(mpColCoordinates[nCol]==SCH_DATALOG_ANY)
//STRIP001 			mnColsAdded--;
//STRIP001 
//STRIP001 		//loeschen der CoordinatenInformation
//STRIP001 		for(n=nCol;n<mnCols;n++)
//STRIP001 			mpColCoordinates[n]=mpColCoordinates[n+1];
//STRIP001 
//STRIP001 		mbColChanged=TRUE;
//STRIP001 	}
//STRIP001 }

//STRIP001 void SchDataLogBook::SwapRows(long nRow1,long nRow2)
//STRIP001 {
//STRIP001 
//STRIP001 	if (nRow1 > nRow2)
//STRIP001 	{
//STRIP001 		long nTemp = nRow1;
//STRIP001 
//STRIP001 		nRow1 = nRow2;
//STRIP001 		nRow2 = nTemp;
//STRIP001 	}
//STRIP001 
//STRIP001 	if (nRow1 >= mnRows - 1) nRow1 = mnRows - 2;
//STRIP001 	if (nRow2 >= mnRows)     nRow2 = mnRows - 1;
//STRIP001 
//STRIP001 	nRow1 = MAX(nRow1, 0);
//STRIP001 	nRow2 = MAX(nRow2, 0);
//STRIP001 
//STRIP001 
//STRIP001 
//STRIP001 	if(  (nRow1<mnRows) && (nRow2<mnRows) && mbValid )
//STRIP001 	{
//STRIP001 		long tmp=mpRowCoordinates[nRow1];
//STRIP001 
//STRIP001 		mpRowCoordinates[nRow1]=mpRowCoordinates[nRow2];
//STRIP001 		mpRowCoordinates[nRow2]=tmp;
//STRIP001 		mbRowChanged=TRUE;
//STRIP001 	}
//STRIP001 }
//STRIP001 void SchDataLogBook::SwapCols(long nCol1,long nCol2)
//STRIP001 {
//STRIP001 
//STRIP001 
//STRIP001 	//Wie im MemChart die Args korrigieren:
//STRIP001 	if (nCol1 > nCol2)
//STRIP001 	{
//STRIP001 		long nTemp = nCol1;
//STRIP001 
//STRIP001 		nCol1 = nCol2;
//STRIP001 		nCol2 = nTemp;
//STRIP001 	}
//STRIP001 	if (nCol1 >= mnCols - 1) nCol1 = mnCols - 2;
//STRIP001 	if (nCol2 >= mnCols)     nCol2 = mnCols - 1;
//STRIP001 	nCol1 = MAX(nCol1, 0);
//STRIP001 	nCol2 = MAX(nCol2, 0);
//STRIP001 
//STRIP001 
//STRIP001 	if(  (nCol1<mnCols) && (nCol2<mnCols) && mbValid )
//STRIP001 	{
//STRIP001 		long tmp=mpColCoordinates[nCol1];
//STRIP001 
//STRIP001 		mpColCoordinates[nCol1]=mpColCoordinates[nCol2];
//STRIP001 		mpColCoordinates[nCol2]=tmp;
//STRIP001 		mbColChanged=TRUE;
//STRIP001 	}
//STRIP001 }
//STRIP001 void SchDataLogBook::IncreaseRowCount()
//STRIP001 {
//STRIP001 	long *pNewCoord;
//STRIP001 
//STRIP001 	pNewCoord= new long[mnRows+SCHLOGBOOK_DEFOVERHEAD];
//STRIP001 	if(pNewCoord)
//STRIP001 	{
//STRIP001 		mnRowsLeft=SCHLOGBOOK_DEFOVERHEAD;
//STRIP001 		memcpy(pNewCoord,mpRowCoordinates,sizeof(long)*mnRows);
//STRIP001 		delete [] mpRowCoordinates;
//STRIP001 		mpRowCoordinates=pNewCoord;
//STRIP001 	}
//STRIP001 	else
//STRIP001 	{
//STRIP001 		mbValid=FALSE;
//STRIP001 	}
//STRIP001 }
//STRIP001 void SchDataLogBook::IncreaseColCount()
//STRIP001 {
//STRIP001 	long *pNewCoord;
//STRIP001 
//STRIP001 	pNewCoord= new long[mnCols+SCHLOGBOOK_DEFOVERHEAD];
//STRIP001 	if(pNewCoord)
//STRIP001 	{
//STRIP001 		mnColsLeft=SCHLOGBOOK_DEFOVERHEAD;
//STRIP001 		memcpy(pNewCoord,mpColCoordinates,sizeof(long)*mnCols);
//STRIP001 		delete [] mpColCoordinates;
//STRIP001 		mpColCoordinates=pNewCoord;
//STRIP001 	}
//STRIP001 	else
//STRIP001 	{
//STRIP001 		mbValid=FALSE;
//STRIP001 	}
//STRIP001 }



//STRIP001 void SchDataLogBook::InsertRow(const long nRow)
//STRIP001 {
//STRIP001 	if(mbValid && (nRow >= 0) )
//STRIP001 	{
//STRIP001 		if(mnRowsLeft == 0)
//STRIP001 			IncreaseRowCount();//Buffer vergr��ern
//STRIP001 
//STRIP001 		//Einfuegen:
//STRIP001 		if(mbValid)
//STRIP001 		{
//STRIP001 			mnRows++;
//STRIP001 			mnRowsLeft--;
//STRIP001 			mnRowsAdded++;
//STRIP001 			long n=mnRows-1;
//STRIP001 			while(n > nRow)
//STRIP001 			{
//STRIP001 				mpRowCoordinates[n]=mpRowCoordinates[n-1];
//STRIP001 				n--;
//STRIP001 			}
//STRIP001 			mbRowChanged=TRUE;
//STRIP001 			mpRowCoordinates[nRow]=SCH_DATALOG_ANY;
//STRIP001 		}
//STRIP001 	}
//STRIP001 }

//STRIP001 void SchDataLogBook::InsertCol(const long nCol)
//STRIP001 {
//STRIP001 	if(mbValid && (nCol >= 0) )
//STRIP001 	{
//STRIP001 		if(mnColsLeft == 0)
//STRIP001 			IncreaseColCount();
//STRIP001 
//STRIP001 		//Einfuegen:
//STRIP001 		if(mbValid)
//STRIP001 		{
//STRIP001 			mnCols++;
//STRIP001 			mnColsLeft--;
//STRIP001 			mnColsAdded++;
//STRIP001 			long n=mnCols-1;
//STRIP001 			while(n > nCol)
//STRIP001 			{
//STRIP001 				mpColCoordinates[n]=mpColCoordinates[n-1];
//STRIP001 				n--;
//STRIP001 			}
//STRIP001 			mbColChanged=TRUE;
//STRIP001 			mpColCoordinates[nCol]=SCH_DATALOG_ANY;
//STRIP001 		}
//STRIP001 	}
//STRIP001 }

}
