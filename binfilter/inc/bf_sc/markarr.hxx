/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: markarr.hxx,v $
 *
 *  $Revision: 1.4 $
 *
 *  last change: $Author: rt $ $Date: 2006-10-28 02:37:24 $
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

#ifndef SC_MARKARR_HXX
#define SC_MARKARR_HXX

#ifndef _SOLAR_H
#include <tools/solar.h>
#endif
namespace binfilter {

#define SC_MARKARRAY_DELTA    4

struct ScMarkEntry
{
    USHORT			nRow;
    BOOL			bMarked;
};

class ScMarkArray
{
    USHORT			nCount;
    USHORT          nLimit;
    ScMarkEntry*	pData;

friend class ScMarkArrayIter;
friend class ScDocument;				// fuer FillInfo

public:
            ScMarkArray();
            ~ScMarkArray();
    void	Reset( BOOL bMarked = FALSE );
    BOOL	GetMark( USHORT nRow ) const;
    void	SetMarkArea( USHORT nStartRow, USHORT nEndRow, BOOL bMarked );
    BOOL	IsAllMarked( USHORT nStartRow, USHORT nEndRow ) const;
    BOOL	HasOneMark( USHORT& rStartRow, USHORT& rEndRow ) const;
    BOOL	HasMarks() const;
    void	CopyMarksTo( ScMarkArray& rDestMarkArray ) const;

    BOOL 	Search( USHORT nRow, short& nIndex ) const;

    short	GetNextMarked( short nRow, BOOL bUp ) const;		// inkl. aktuelle
    USHORT	GetMarkEnd( USHORT nRow, BOOL bUp ) const;
};


class ScMarkArrayIter					// selektierte Bereiche durchgehen
{
    const ScMarkArray*	pArray;
    USHORT				nPos;
public:
                ScMarkArrayIter( const ScMarkArray* pNewArray );
                ~ScMarkArrayIter();

    BOOL		Next( USHORT& rTop, USHORT& rBottom );
};



} //namespace binfilter
#endif

