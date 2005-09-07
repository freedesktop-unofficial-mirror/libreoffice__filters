/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: editable.hxx,v $
 *
 *  $Revision: 1.3 $
 *
 *  last change: $Author: rt $ $Date: 2005-09-07 19:45:16 $
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

#ifndef SC_EDITABLE_HXX
#define SC_EDITABLE_HXX

#ifndef _SOLAR_H
#include <tools/solar.h>
#endif
namespace binfilter {

class ScDocument;
class ScViewFunc;
class ScMarkData;
class ScRange;


class ScEditableTester
{
    BOOL	bIsEditable;
    BOOL	bOnlyMatrix;

public:
            // no test in ctor
            ScEditableTester();

            // calls TestBlock
            ScEditableTester( ScDocument* pDoc, USHORT nTab,
                        USHORT nStartCol, USHORT nStartRow, USHORT nEndCol, USHORT nEndRow );

            // calls TestSelectedBlock
            ScEditableTester( ScDocument* pDoc, 
                        USHORT nStartCol, USHORT nStartRow, USHORT nEndCol, USHORT nEndRow,
                        const ScMarkData& rMark );

            // calls TestRange
            ScEditableTester( ScDocument* pDoc, const ScRange& rRange );

            // calls TestSelection
            ScEditableTester( ScDocument* pDoc, const ScMarkData& rMark );

            // calls TestView
//STRIP001 			ScEditableTester( ScViewFunc* pView );

            ~ScEditableTester() {}

            // Several calls to the Test... methods check if *all* of the ranges
            // are editable. For several independent checks, Reset() has to be used.
    void	TestBlock( ScDocument* pDoc, USHORT nTab,
                        USHORT nStartCol, USHORT nStartRow, USHORT nEndCol, USHORT nEndRow );
    void	TestSelectedBlock( ScDocument* pDoc, 
                        USHORT nStartCol, USHORT nStartRow, USHORT nEndCol, USHORT nEndRow,
                        const ScMarkData& rMark );
//STRIP001 	void	TestRange( ScDocument* pDoc, const ScRange& rRange );
//STRIP001 	void	TestSelection( ScDocument* pDoc, const ScMarkData& rMark );
//STRIP001 	void	TestView( ScViewFunc* pView );

//STRIP001 	void	Reset();

    BOOL	IsEditable() const			{ return bIsEditable; }
    BOOL	IsFormatEditable() const	{ return bIsEditable || bOnlyMatrix; }
    USHORT	GetMessageId() const;
};

} //namespace binfilter
#endif

