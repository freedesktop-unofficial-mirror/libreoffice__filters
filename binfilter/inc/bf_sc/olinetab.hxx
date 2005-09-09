/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: olinetab.hxx,v $
 *
 *  $Revision: 1.4 $
 *
 *  last change: $Author: rt $ $Date: 2005-09-09 11:20:17 $
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

#ifndef SC_OUTLINETAB_HXX
#define SC_OUTLINETAB_HXX


#ifndef SC_COLLECT_HXX
#include "collect.hxx"
#endif
class SvStream;
namespace binfilter {


#define SC_OL_MAXDEPTH		7

class ScMultipleReadHeader;
class ScMultipleWriteHeader;


class ScOutlineEntry : public DataObject
{
    USHORT		nStart;
    USHORT		nSize;
    BOOL		bHidden;
    BOOL		bVisible;

public:
                            ScOutlineEntry( USHORT nNewStart, USHORT nNewSize,
                                                 BOOL bNewHidden = FALSE );
                            ScOutlineEntry( const ScOutlineEntry& rEntry );
                            ScOutlineEntry( SvStream& rStream, ScMultipleReadHeader& rHdr );

    void					Store( SvStream& rStream, ScMultipleWriteHeader& rHdr );
//STRIP001 
    virtual	DataObject*		Clone() const;
//STRIP001 
    USHORT					GetStart() const	{ return nStart; }
/*N*/ 	USHORT					GetSize() const		{ return nSize; }
    USHORT					GetEnd() const		{ return nStart+nSize-1; }
    BOOL					IsHidden() const	{ return bHidden; }				// Gruppe versteckt
//STRIP001 	BOOL					IsVisible() const	{ return bVisible; }			// Control sichtbar?
//STRIP001 
/*N*/ 	void					Move( short nDelta );
/*N*/ 	void					SetSize( USHORT nNewSize );
/*N*/ 	void					SetPosSize( USHORT nNewPos, USHORT nNewSize );
/*N*/ 	void					SetHidden( BOOL bNewHidden );
    void					SetVisible( BOOL bNewVisible );
};


class ScOutlineCollection : public SortedCollection
{
public:
                            ScOutlineCollection();
 
    virtual	short			Compare(DataObject* pKey1, DataObject* pKey2) const;

//STRIP001 	USHORT					FindStart( USHORT nMinStart );
};


class ScOutlineArray
{
friend class ScSubOutlineIterator;
 
private:
    USHORT					nDepth;
    ScOutlineCollection		aCollections[SC_OL_MAXDEPTH];
 
/*N*/ 	BOOL					DecDepth();
    void					FindEntry( USHORT nSearchPos, USHORT& rFindLevel, USHORT& rFindIndex,
                                        USHORT nMaxLevel = SC_OL_MAXDEPTH );
//STRIP001 	void					RemoveSub( USHORT nStartPos, USHORT nEndPos, USHORT nLevel );
//STRIP001 	void					PromoteSub( USHORT nStartPos, USHORT nEndPos, USHORT nStartLevel );
//STRIP001 
public:
                            ScOutlineArray();
                             ScOutlineArray( const ScOutlineArray& rArray );

    USHORT					GetDepth() const		 { return nDepth; }

//STRIP001 	BOOL					FindTouchedLevel( USHORT nBlockStart, USHORT nBockEnd,
//STRIP001                                                 USHORT& rFindLevel ) const;

    BOOL					Insert( USHORT nStartCol, USHORT nEndCol, BOOL& rSizeChanged,
                                    BOOL bHidden = FALSE, BOOL bVisible = TRUE );
//STRIP001 	BOOL					Remove( USHORT nBlockStart, USHORT nBlockEnd, BOOL& rSizeChanged );

    ScOutlineEntry*         GetEntry( USHORT nLevel, USHORT nIndex ) const;
    USHORT                  GetCount( USHORT nLevel ) const;
//STRIP001     ScOutlineEntry*         GetEntryByPos( USHORT nLevel, USHORT nPos ) const;

    BOOL                    GetEntryIndex( USHORT nLevel, USHORT nPos, USHORT& rnIndex ) const;
    BOOL                    GetEntryIndexInRange(
                                USHORT nLevel, USHORT nBlockStart, USHORT nBlockEnd,
                                USHORT& rnIndex ) const;

    void					SetVisibleBelow( USHORT nLevel, USHORT nEntry, BOOL bValue,
                                                BOOL bSkipHidden = FALSE );

//STRIP001     void                    GetRange( USHORT& rStart, USHORT& rEnd ) const;
//STRIP001 	void					ExtendBlock( USHORT nLevel, USHORT& rBlkStart, USHORT& rBlkEnd );

/*N*/    BOOL                    TestInsertSpace( USHORT nSize, USHORT nMaxVal ) const;
/*N*/ 	void					InsertSpace( USHORT nStartPos, USHORT nSize );
/*N*/ 	BOOL					DeleteSpace( USHORT nStartPos, USHORT nSize );

    BOOL					ManualAction( USHORT nStartPos, USHORT nEndPos,
                                            BOOL bShow, BYTE* pHiddenFlags );
//STRIP001 
     void					Load( SvStream& rStream );
    void					Store( SvStream& rStream );
//STRIP001 
//STRIP001 	void					RemoveAll();
};


class ScOutlineTable
{
private:
    ScOutlineArray			aColOutline;
    ScOutlineArray			aRowOutline;
 
public:
                            ScOutlineTable();
                            ScOutlineTable( const ScOutlineTable& rOutline );
  
    const ScOutlineArray*	GetColArray() const		{ return &aColOutline; }
    ScOutlineArray*			GetColArray()			{ return &aColOutline; }
    const ScOutlineArray*	GetRowArray() const		{ return &aRowOutline; }
     ScOutlineArray*			GetRowArray()			{ return &aRowOutline; }

/*N*/ 	BOOL					TestInsertCol( USHORT nSize );
/*N*/ 	void					InsertCol( USHORT nStartCol, USHORT nSize );
/*N*/ 	BOOL					DeleteCol( USHORT nStartCol, USHORT nSize );	// TRUE: Undo nur ueber Original
/*N*/ 	BOOL					TestInsertRow( USHORT nSize );
/*N*/ 	void					InsertRow( USHORT nStartRow, USHORT nSize );
/*N*/ 	BOOL					DeleteRow( USHORT nStartRow, USHORT nSize );
//STRIP001 
    void					Load( SvStream& rStream );
     void					Store( SvStream& rStream );
};


class ScSubOutlineIterator
{
private:
    ScOutlineArray*			pArray;
    USHORT					nStart;
    USHORT					nEnd;
    USHORT					nSubLevel;
    USHORT					nSubEntry;
    USHORT					nCount;
    USHORT					nDepth;

public:
                            ScSubOutlineIterator( ScOutlineArray* pOutlineArray );
//STRIP001 							ScSubOutlineIterator( ScOutlineArray* pOutlineArray,
//STRIP001 													USHORT nLevel, USHORT nEntry );
    ScOutlineEntry*			GetNext();
//STRIP001 	USHORT					LastLevel() const;
//STRIP001 	USHORT					LastEntry() const;
/*N*/ 	void					DeleteLast();
};

} //namespace binfilter
#endif


