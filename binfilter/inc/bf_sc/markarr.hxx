/*************************************************************************
 *
 *  $RCSfile: markarr.hxx,v $
 *
 *  $Revision: 1.2 $
 *
 *  last change: $Author: mwu $ $Date: 2003-11-06 07:59:54 $
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
//STRIP001 	void	SetMark( USHORT nRow, BOOL bMarked );
    void	SetMarkArea( USHORT nStartRow, USHORT nEndRow, BOOL bMarked );
    BOOL	IsAllMarked( USHORT nStartRow, USHORT nEndRow ) const;
    BOOL	HasOneMark( USHORT& rStartRow, USHORT& rEndRow ) const;
    BOOL	HasMarks() const;
    void	CopyMarksTo( ScMarkArray& rDestMarkArray ) const;

    BOOL 	Search( USHORT nRow, short& nIndex ) const;
//STRIP001 	void	DeleteArea(USHORT nStartRow, USHORT nEndRow);
//STRIP001 	void	SwapCol(ScMarkArray& rMarkArray);
//STRIP001 	void	MoveTo(USHORT nStartRow, USHORT nEndRow, ScMarkArray& rMarkArray);

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

