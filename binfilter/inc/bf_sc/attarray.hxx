/*************************************************************************
 *
 *  $RCSfile: attarray.hxx,v $
 *
 *  $Revision: 1.3 $
 *
 *  last change: $Author: er $ $Date: 2004-03-25 14:46:23 $
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

#ifndef SC_ATRARR_HXX
#define SC_ATRARR_HXX

#ifndef SC_SCGLOB_HXX
#include "global.hxx"
#endif

#ifndef SC_SCATTR_HXX
#include "attrib.hxx"
#endif
class Rectangle;
class SfxItemPoolCache;
class SfxStyleSheetBase;
namespace binfilter {

class ScDocument;
class ScMarkArray;
class ScPatternAttr;
class ScStyleSheet;

class SvxBorderLine;
class SvxBoxItem;
class SvxBoxInfoItem;

#define SC_LINE_EMPTY			0
#define SC_LINE_SET				1
#define SC_LINE_DONTCARE		2

#define SC_ATTRARRAY_DELTA      4

struct ScLineFlags
{
    BYTE	nLeft;
    BYTE	nRight;
    BYTE	nTop;
    BYTE	nBottom;
    BYTE	nHori;
    BYTE	nVert;

    ScLineFlags() : nLeft(SC_LINE_EMPTY),nRight(SC_LINE_EMPTY),nTop(SC_LINE_EMPTY),
                    nBottom(SC_LINE_EMPTY),nHori(SC_LINE_EMPTY),nVert(SC_LINE_EMPTY) {}
};

struct ScAttrEntry
{
    USHORT					nRow;
    const ScPatternAttr*	pPattern;
};


class ScAttrArray
{
private:
    USHORT			nCol;
    USHORT			nTab;
    ScDocument*		pDocument;

    USHORT			nCount;
    USHORT          nLimit;
    ScAttrEntry*	pData;

friend class ScDocument;				// fuer FillInfo
friend class ScDocumentIterator;
friend class ScAttrIterator;
//STRIP001 friend class ScHorizontalAttrIterator;
friend void lcl_IterGetNumberFormat( ULONG& nFormat,
        const ScAttrArray*& rpArr, USHORT& nAttrEndRow,
        const ScAttrArray* pNewArr, USHORT nRow, ScDocument* pDoc );

//STRIP001 	BOOL	ApplyFrame( const SvxBoxItem* pLineOuter, const SvxBoxInfoItem* pLineInner,
//STRIP001 							USHORT nStartRow, USHORT nEndRow,
//STRIP001 							BOOL bLeft, USHORT nDistRight, BOOL bTop, USHORT nDistBottom );

public:
            ScAttrArray( USHORT nNewCol, USHORT nNewTab, ScDocument* pDoc );
            ~ScAttrArray();

    void	SetTab(USHORT nNewTab)	{ nTab = nNewTab; }
    void	SetCol(USHORT nNewCol)	{ nCol = nNewCol; }

    void	TestData() const;
    void	Reset( const ScPatternAttr* pPattern, BOOL bAlloc = TRUE );
    BOOL	Concat(USHORT nPos);

    const ScPatternAttr* GetPattern( USHORT nRow ) const;
//STRIP001 	const ScPatternAttr* GetPatternRange( USHORT& rStartRow, USHORT& rEndRow, USHORT nRow ) const;
    void	MergePatternArea( USHORT nStartRow, USHORT nEndRow, SfxItemSet** ppSet, BOOL bDeep ) const;

//STRIP001 	void	MergeBlockFrame( SvxBoxItem* pLineOuter, SvxBoxInfoItem* pLineInner, ScLineFlags& rFlags,
//STRIP001 							USHORT nStartRow, USHORT nEndRow, BOOL bLeft, USHORT nDistRight ) const;
//STRIP001 	void	ApplyBlockFrame( const SvxBoxItem* pLineOuter, const SvxBoxInfoItem* pLineInner,
//STRIP001 							USHORT nStartRow, USHORT nEndRow, BOOL bLeft, USHORT nDistRight );

    void	SetPattern( USHORT nRow, const ScPatternAttr* pPattern, BOOL bPutToPool = FALSE );
    void	SetPatternArea( USHORT nStartRow, USHORT nEndRow, const ScPatternAttr* pPattern, BOOL bPutToPool = FALSE);
    void	ApplyStyleArea( USHORT nStartRow, USHORT nEndRow, ScStyleSheet* pStyle );
    void	ApplyCacheArea( USHORT nStartRow, USHORT nEndRow, SfxItemPoolCache* pCache );
//STRIP001 	void	ApplyLineStyleArea( USHORT nStartRow, USHORT nEndRow,
//STRIP001 								const SvxBorderLine* pLine, BOOL bColorOnly );

/*N*/ 	void	ClearItems( USHORT nStartRow, USHORT nEndRow, const USHORT* pWhich );
//STRIP001 	void	ChangeIndent( USHORT nStartRow, USHORT nEndRow, BOOL bIncrement );

//STRIP001 	short	GetNextUnprotected( short nRow, BOOL bUp ) const;	// inkl. aktuelle

//STRIP001 	short	SearchStyle( short nRow, const ScStyleSheet* pSearchStyle,
//STRIP001 							BOOL bUp, ScMarkArray* pMarkArray = NULL );
//STRIP001 	BOOL	SearchStyleRange( short& rRow, short& rEndRow, const ScStyleSheet* pSearchStyle,
//STRIP001 							BOOL bUp, ScMarkArray* pMarkArray = NULL );

    BOOL	ApplyFlags( USHORT nStartRow, USHORT nEndRow, INT16 nFlags );
/*N*/ 	BOOL	RemoveFlags( USHORT nStartRow, USHORT nEndRow, INT16 nFlags );

    BOOL 	Search( USHORT nRow, short& nIndex ) const;

//STRIP001 	BOOL	HasLines( USHORT nRow1, USHORT nRow2, Rectangle& rSizes,
//STRIP001 						BOOL bLeft, BOOL bRight ) const;
    BOOL	HasAttrib( USHORT nRow1, USHORT nRow2, USHORT nMask ) const;
    BOOL	ExtendMerge( USHORT nThisCol, USHORT nStartRow, USHORT nEndRow,
                                USHORT& rPaintCol, USHORT& rPaintRow,
                                BOOL bRefresh, BOOL bAttrs );
    BOOL	RemoveAreaMerge( USHORT nStartRow, USHORT nEndRow );

    void	FindStyleSheet( const SfxStyleSheetBase* pStyleSheet, BOOL* pUsed, BOOL bReset );
    BOOL	IsStyleSheetUsed( const ScStyleSheet& rStyle, BOOL bGatherAllStyles ) const;

    void	DeleteAreaSafe(USHORT nStartRow, USHORT nEndRow);
//STRIP001 	void	SetPatternAreaSafe( USHORT nStartRow, USHORT nEndRow,
//STRIP001 									const ScPatternAttr* pWantedPattern, BOOL bDefault );
//STRIP001 	void	CopyAreaSafe( USHORT nStartRow, USHORT nEndRow, short nDy, ScAttrArray& rAttrArray );

    BOOL	IsEmpty() const;

//STRIP001 	USHORT	GetFirstEntryPos() const;
//STRIP001 	USHORT	GetLastEntryPos( BOOL bIncludeBottom ) const;

    BOOL	HasVisibleAttr( USHORT& rFirstRow, USHORT& rLastRow, BOOL bSkipFirst ) const;
//STRIP001 	BOOL	HasVisibleAttrIn( USHORT nStartRow, USHORT nEndRow ) const;
    BOOL	IsVisibleEqual( const ScAttrArray& rOther,
                            USHORT nStartRow, USHORT nEndRow ) const;
    BOOL	IsAllEqual( const ScAttrArray& rOther, USHORT nStartRow, USHORT nEndRow ) const;

/*N*/ 	BOOL	TestInsertCol( USHORT nStartRow, USHORT nEndRow) const;
/*N*/ 	BOOL	TestInsertRow( USHORT nSize ) const;
/*N*/ 	void	InsertRow( USHORT nStartRow, USHORT nSize );
/*N*/ 	void	DeleteRow( USHORT nStartRow, USHORT nSize );
/*N*/ 	void	DeleteRange( USHORT nStartIndex, USHORT nEndIndex );
    void	DeleteArea( USHORT nStartRow, USHORT nEndRow );
/*N*/ 	void	MoveTo( USHORT nStartRow, USHORT nEndRow, ScAttrArray& rAttrArray );
    void	CopyArea( USHORT nStartRow, USHORT nEndRow, short nDy, ScAttrArray& rAttrArray,
                        INT16 nStripFlags = 0 );

    void	DeleteHardAttr( USHORT nStartRow, USHORT nEndRow );

    void	Save( SvStream& rStream ) const;
    void	Load( SvStream& rStream );
    void    ConvertFontsAfterLoad();     // old binary file format
};


//	------------------------------------------------------------------------------
//								Iterator fuer Attribute
//	------------------------------------------------------------------------------

/*N*/ class ScAttrIterator
/*N*/ {
/*N*/ 	const ScAttrArray*	pArray;
/*N*/ 	short				nPos;
/*N*/ 	USHORT				nRow;
/*N*/ 	USHORT				nEndRow;
/*N*/ public:
/*N*/ 	inline				ScAttrIterator( const ScAttrArray* pNewArray, USHORT nStart, USHORT nEnd );
/*N*/ 	inline const ScPatternAttr*	Next( USHORT& rTop, USHORT& rBottom );
/*N*/ 	USHORT				GetNextRow() const { return nRow; }
/*N*/ };
/*N*/ 
/*N*/ 
/*N*/ inline ScAttrIterator::ScAttrIterator( const ScAttrArray* pNewArray, USHORT nStart, USHORT nEnd ) :
/*N*/ 	pArray( pNewArray ),
/*N*/ 	nRow( nStart ),
/*N*/ 	nEndRow( nEnd )
/*N*/ {
/*N*/ 	if ( nStart )
/*N*/ 		pArray->Search( nStart, nPos );
/*N*/ 	else
/*N*/ 		nPos = 0;
/*N*/ }
/*N*/ 
/*N*/ inline const ScPatternAttr*	ScAttrIterator::Next( USHORT& rTop, USHORT& rBottom )
/*N*/ {
/*N*/ 	const ScPatternAttr* pRet;
/*N*/ 	if ( nPos < (short) pArray->nCount && nRow <= nEndRow )
/*N*/ 	{
/*N*/ 		rTop = nRow;
/*N*/ 		rBottom = Min( pArray->pData[nPos].nRow, nEndRow );
/*N*/ 		pRet = pArray->pData[nPos].pPattern;
/*N*/ 		nRow = rBottom + 1;
/*N*/ 		++nPos;
/*N*/ 	}
/*N*/ 	else
/*N*/ 		pRet = NULL;
/*N*/ 	return pRet;
/*N*/ }



} //namespace binfilter
#endif


