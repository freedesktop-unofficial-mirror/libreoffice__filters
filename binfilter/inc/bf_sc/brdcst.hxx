/*************************************************************************
 *
 *  $RCSfile: brdcst.hxx,v $
 *
 *  $Revision: 1.2 $
 *
 *  last change: $Author: mwu $ $Date: 2003-11-06 07:59:31 $
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
#ifndef _SC_BRDCST_HXX
#define _SC_BRDCST_HXX

#ifndef SC_SCGLOB_HXX
#include "global.hxx"
#endif

#ifndef _RTTI_HXX //autogen
#include <tools/rtti.hxx>
#endif
#ifndef _SFXHINT_HXX //autogen
#include <svtools/hint.hxx>
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
