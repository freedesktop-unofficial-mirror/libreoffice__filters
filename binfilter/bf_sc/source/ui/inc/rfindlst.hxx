/*************************************************************************
 *
 *  $RCSfile: rfindlst.hxx,v $
 *
 *  $Revision: 1.3 $
 *
 *  last change: $Author: aw $ $Date: 2004-02-13 14:30:18 $
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
//STRIP001 	void	Insert( ScRangeFindData* pNew )		{ aEntries.Insert(pNew, LIST_APPEND); }
    ScRangeFindData* GetObject( ULONG nIndex ) const
                        { return (ScRangeFindData*)aEntries.GetObject(nIndex); }
//STRIP001 
//STRIP001 	void	SetHidden( BOOL bSet )				{ bHidden = bSet; }
//STRIP001 
    const String&	GetDocName() const			{ return aDocName; }
    BOOL			IsHidden() const			{ return bHidden; }
//STRIP001 
//STRIP001 	static ColorData GetColorName( USHORT nIndex );
};



} //namespace binfilter
#endif


