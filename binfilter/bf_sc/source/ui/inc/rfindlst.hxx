/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: rfindlst.hxx,v $
 *
 *  $Revision: 1.5 $
 *
 *  last change: $Author: rt $ $Date: 2006-10-27 16:23:25 $
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

#ifndef SC_RFINDLST_HXX
#define SC_RFINDLST_HXX

#ifndef _COLOR_HXX //autogen
#include <tools/color.hxx>
#endif

#ifndef SC_SCGLOB_HXX
#include "global.hxx"
#endif
namespace binfilter {

//==================================================================

struct ScRangeFindData
{
    ScRange		aRef;
    USHORT		nFlags;
    xub_StrLen	nSelStart;
    xub_StrLen	nSelEnd;

    ScRangeFindData( const ScRange& rR, USHORT nF, xub_StrLen nS, xub_StrLen nE ) :
        aRef(rR), nFlags(nF), nSelStart(nS), nSelEnd(nE) {}
};

class ScRangeFindList
{
    List		aEntries;
    String		aDocName;
    BOOL		bHidden;

public:
            ScRangeFindList(const String& rName);
            ~ScRangeFindList();

    ULONG	Count() const						{ return aEntries.Count(); }
    ScRangeFindData* GetObject( ULONG nIndex ) const
                        { return (ScRangeFindData*)aEntries.GetObject(nIndex); }
    const String&	GetDocName() const			{ return aDocName; }
    BOOL			IsHidden() const			{ return bHidden; }
};



} //namespace binfilter
#endif


