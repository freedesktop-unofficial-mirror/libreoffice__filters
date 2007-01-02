/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: dociter.hxx,v $
 *
 *  $Revision: 1.5 $
 *
 *  last change: $Author: hr $ $Date: 2007-01-02 18:26:05 $
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

#ifndef SC_DOCITER_HXX
#define SC_DOCITER_HXX

#ifndef _SOLAR_H
#include <tools/solar.h>
#endif

#ifndef SC_SCGLOB_HXX
#include "global.hxx"
#endif
namespace binfilter {

class ScDocument;
class ScBaseCell;
class ScPatternAttr;
class ScAttrArray;
class ScAttrIterator;

class ScValueIterator            // alle Zahlenwerte in einem Bereich durchgehen
{
private:
    double			fNextValue;
    ScDocument*		pDoc;
    const ScAttrArray*	pAttrArray;
    ULONG			nNumFormat;		// fuer CalcAsShown
    ULONG			nNumFmtIndex;
    USHORT			nStartCol;
    USHORT			nStartRow;
    USHORT			nStartTab;
    USHORT			nEndCol;
    USHORT			nEndRow;
    USHORT			nEndTab;
    USHORT 			nCol;
    USHORT			nRow;
    USHORT			nTab;
    USHORT			nColRow;
    USHORT			nNextRow;
    USHORT			nAttrEndRow;
    short			nNumFmtType;
    BOOL			bNumValid;
    BOOL			bSubTotal;
    BOOL			bNextValid;
    BOOL			bCalcAsShown;
    BOOL			bTextAsZero;

    BOOL			GetThis(double& rValue, USHORT& rErr);
public:
                    ScValueIterator(ScDocument* pDocument,
                                    USHORT nSCol, USHORT nSRow, USHORT nSTab,
                                    USHORT nECol, USHORT nERow, USHORT nETab,
                                    BOOL bSTotal = FALSE, BOOL bTextAsZero = FALSE);
                    ScValueIterator(ScDocument* pDocument,
                                    const ScRange& rRange, BOOL bSTotal = FALSE,
                                    BOOL bTextAsZero = FALSE );
    void			GetCurNumFmtInfo( short& nType, ULONG& nIndex );
    BOOL			GetFirst(double& rValue, USHORT& rErr);
    BOOL			GetNext(double& rValue, USHORT& rErr)
                    {
                        return bNextValid ? ( bNextValid = FALSE, rValue = fNextValue,
                                                rErr = 0, nRow = nNextRow,
                                                ++nColRow, bNumValid = FALSE, TRUE )
                                          : ( ++nRow, GetThis(rValue, rErr) );
                    }
};

 class ScQueryValueIterator            // alle Zahlenwerte in einem Bereich durchgehen
 {
 private:
     ScQueryParam	aParam;
     ScDocument*		pDoc;
     ScAttrArray*	pAttrArray;
     ULONG			nNumFormat;		// fuer CalcAsShown
     ULONG			nNumFmtIndex;
     USHORT 			nCol;
     USHORT			nRow;
     USHORT			nColRow;
     USHORT			nAttrEndRow;
     USHORT			nTab;
     short			nNumFmtType;
     BOOL			bCalcAsShown;
 
     BOOL			GetThis(double& rValue, USHORT& rErr);
 public:
                     ScQueryValueIterator(ScDocument* pDocument, USHORT nTable,
                                          const ScQueryParam& aParam);
     BOOL			GetFirst(double& rValue, USHORT& rErr);
     BOOL			GetNext(double& rValue, USHORT& rErr);
     void			GetCurNumFmtInfo( short& nType, ULONG& nIndex )
                         { nType = nNumFmtType; nIndex = nNumFmtIndex; }
 };

class ScCellIterator            // alle Zellen in einem Bereich durchgehen
{								// bei SubTotal aber keine ausgeblendeten und
private:						// SubTotalZeilen
    ScDocument*		pDoc;
    USHORT			nStartCol;
    USHORT			nStartRow;
    USHORT			nStartTab;
    USHORT			nEndCol;
    USHORT			nEndRow;
    USHORT			nEndTab;
    USHORT 			nCol;
    USHORT			nRow;
    USHORT			nTab;
    USHORT			nColRow;
    BOOL			bSubTotal;

    ScBaseCell*		GetThis();
public:
                    ScCellIterator(ScDocument* pDocument,
                                   USHORT nSCol, USHORT nSRow, USHORT nSTab,
                                   USHORT nECol, USHORT nERow, USHORT nETab,
                                   BOOL bSTotal = FALSE);
                    ScCellIterator(ScDocument* pDocument,
                                   const ScRange& rRange, BOOL bSTotal = FALSE);
    ScBaseCell*		GetFirst();
    ScBaseCell*		GetNext();
    USHORT          GetCol() { return nCol; }
    USHORT          GetRow() { return nRow; }
    USHORT          GetTab() { return nTab; }
};

class ScQueryCellIterator           // alle nichtleeren Zellen in einem Bereich
{									// durchgehen
    enum StopOnMismatchBits
    {
        nStopOnMismatchDisabled = 0x00,
        nStopOnMismatchEnabled  = 0x01,
        nStopOnMismatchOccured  = 0x02,
        nStopOnMismatchExecuted = nStopOnMismatchEnabled | nStopOnMismatchOccured
    };

    enum TestEqualConditionBits
    {
        nTestEqualConditionDisabled = 0x00,
        nTestEqualConditionEnabled  = 0x01,
        nTestEqualConditionMatched  = 0x02,
        nTestEqualConditionFulfilled = nTestEqualConditionEnabled | nTestEqualConditionMatched
    };

private:
    ScQueryParam	aParam;
    ScDocument*		pDoc;
    ScAttrArray*	pAttrArray;
    ULONG			nNumFormat;
    USHORT			nTab;
    USHORT 			nCol;
    USHORT			nRow;
    USHORT			nColRow;
    USHORT			nAttrEndRow;
    BYTE            nStopOnMismatch;
    BYTE            nTestEqualCondition;
    BOOL			bAdvanceQuery;

    ScBaseCell*		GetThis();
public:
                    ScQueryCellIterator(ScDocument* pDocument, USHORT nTable,
                                        const ScQueryParam& aParam, BOOL bMod = TRUE);
                                        // fuer bMod = FALSE muss der QueryParam
                                        // weiter aufgefuellt sein (bIsString)
    ScBaseCell*		GetFirst();
    ScBaseCell*		GetNext();
    USHORT          GetCol() { return nCol; }
    USHORT          GetRow() { return nRow; }
     ULONG			GetNumberFormat();

                    // setzt alle Entry.nField einen weiter, wenn Spalte
                    // wechselt, fuer ScInterpreter ScHLookup()
    void			SetAdvanceQueryParamEntryField( BOOL bVal )
                        { bAdvanceQuery = bVal; }
     void			AdvanceQueryParamEntryField();

                    /** If set, iterator stops on first non-matching cell
                        content. May be used in SC_LESS_EQUAL queries where a
                        cell range is assumed to be sorted; stops on first
                        value being greater than the queried value and
                        GetFirst()/GetNext() return NULL. StoppedOnMismatch()
                        returns TRUE then.
                        However, the iterator's conditions are not set to end
                        all queries, GetCol() and GetRow() return values for
                        the non-matching cell, further GetNext() calls may be
                        executed. */
    void            SetStopOnMismatch( BOOL bVal )
                        {
                            nStopOnMismatch = (bVal ? nStopOnMismatchEnabled :
                                nStopOnMismatchDisabled);
                        }
    BOOL            StoppedOnMismatch() const
                        { return nStopOnMismatch == nStopOnMismatchExecuted; }

                    /** If set, an additional test for SC_EQUAL condition is
                        executed in ScTable::ValidQuery() if SC_LESS_EQUAL or
                        SC_GREATER_EQUAL conditions are to be tested. May be
                        used where a cell range is assumed to be sorted to stop
                        if an equal match is found. */
    void            SetTestEqualCondition( BOOL bVal )
                        {
                            nTestEqualCondition = (bVal ?
                                nTestEqualConditionEnabled :
                                nTestEqualConditionDisabled);
                        }
    BOOL            IsEqualConditionFulfilled() const
                        { return nTestEqualCondition == nTestEqualConditionFulfilled; }

                    /** In a range assumed to be sorted find either the first
                        equal entry or the last being less than (or greater
                        than) the queried value. Continues searching for an
                        equal entry even if the last entry matching the range
                        is found, in case the data is not sorted. Used by the
                        interpreter for LOOKUP() and similar. Column and row
                        position of the found entry are returned, otherwise
                        invalid.
                        @ATTENTION! StopOnMismatch, TestEqualCondition and
                        the internal query params are in an undefined state
                        upon return! */
    BOOL            FindEqualOrSortedLastInRange( USHORT& nFoundCol, USHORT& nFoundRow );
};

class ScDocAttrIterator				// alle Attribut-Bereiche
{
private:
    ScDocument*		pDoc;
    USHORT			nTab;
    USHORT			nEndCol;
    USHORT			nStartRow;
    USHORT			nEndRow;
    USHORT			nCol;
    ScAttrIterator*	pColIter;

public:
                    ScDocAttrIterator(ScDocument* pDocument, USHORT nTable,
                                    USHORT nCol1, USHORT nRow1, USHORT nCol2, USHORT nRow2);
                    ~ScDocAttrIterator();

    const ScPatternAttr*	GetNext( USHORT& rCol, USHORT& rRow1, USHORT& rRow2 );
};

class ScAttrRectIterator			// alle Attribut-Bereiche, auch Bereiche ueber mehrere Spalten
{
private:
    ScDocument*		pDoc;
    USHORT			nTab;
    USHORT			nEndCol;
    USHORT			nStartRow;
    USHORT			nEndRow;
    USHORT			nIterStartCol;
    USHORT			nIterEndCol;
    ScAttrIterator*	pColIter;

public:
                    ScAttrRectIterator(ScDocument* pDocument, USHORT nTable,
                                    USHORT nCol1, USHORT nRow1, USHORT nCol2, USHORT nRow2);
                    ~ScAttrRectIterator();

    void 					DataChanged();
    const ScPatternAttr*	GetNext( USHORT& rCol1, USHORT& rCol2, USHORT& rRow1, USHORT& rRow2 );
};

class ScHorizontalCellIterator		// alle nichtleeren Zellen in einem Bereich
{									// zeilenweise durchgehen
private:
    ScDocument*		pDoc;
    USHORT			nTab;
    USHORT			nStartCol;
    USHORT			nEndCol;
    USHORT			nEndRow;
    USHORT*			pNextRows;
    USHORT*			pNextIndices;
    USHORT			nCol;
    USHORT			nRow;
    BOOL			bMore;

public:
                    ScHorizontalCellIterator(ScDocument* pDocument, USHORT nTable,
                                    USHORT nCol1, USHORT nRow1, USHORT nCol2, USHORT nRow2);
                    ~ScHorizontalCellIterator();

    ScBaseCell*		GetNext( USHORT& rCol, USHORT& rRow );
    BOOL			ReturnNext( USHORT& rCol, USHORT& rRow );

private:
    void			Advance();
};


//
//	gibt alle Bereiche mit nicht-Default-Formatierung zurueck (horizontal)
//


//
//	gibt nichtleere Zellen und Bereiche mit Formatierung zurueck (horizontal)
//


} //namespace binfilter
#endif


