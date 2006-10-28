/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: brdcst.hxx,v $
 *
 *  $Revision: 1.5 $
 *
 *  last change: $Author: rt $ $Date: 2006-10-28 02:28:19 $
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
#ifndef _SC_BRDCST_HXX
#define _SC_BRDCST_HXX

#ifndef SC_SCGLOB_HXX
#include "global.hxx"
#endif

#ifndef _SFXSMPLHINT_HXX //autogen
#include <svtools/smplhint.hxx>
#endif
namespace binfilter {
class ScBaseCell;

#define SC_HINT_DYING		SFX_HINT_DYING
#define SC_HINT_DATACHANGED	SFX_HINT_DATACHANGED
#define SC_HINT_TABLEOPDIRTY	SFX_HINT_USER00

class ScHint : public SfxSimpleHint
{
private:
    ScAddress	aAddress;
    ScBaseCell* pCell;

public:
    TYPEINFO();
                        ScHint( ULONG n, const ScAddress& a, ScBaseCell* p )
                            : SfxSimpleHint( n ), aAddress( a ), pCell( p ) {}
    ScBaseCell*			GetCell() const { return pCell; }
    void                SetCell( ScBaseCell* p )    { pCell = p; }
    const ScAddress&	GetAddress() const { return aAddress; }
          ScAddress&    GetAddress()       { return aAddress; }
    void                SetAddress( const ScAddress& rAdr ) { aAddress = rAdr; }
};

class ScAreaChangedHint : public SfxHint
{
private:
    ScRange	aNewRange;
public:
                    TYPEINFO();
                    ScAreaChangedHint(const ScRange& rRange) : aNewRange(rRange) {}
    const ScRange&	GetRange() const { return aNewRange; }
};


} //namespace binfilter
#endif
