/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: sbxmeth.hxx,v $
 *
 *  $Revision: 1.2 $
 *
 *  last change: $Author: obo $ $Date: 2007-03-15 15:32:35 $
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


#ifndef __SBX_SBXMETHOD_HXX
#define __SBX_SBXMETHOD_HXX

#ifndef _SBXVAR_HXX
#include "sbxvar.hxx"
#endif

namespace binfilter {

class SbxMethodImpl;

class SbxMethod : public SbxVariable
{
    SbxMethodImpl* mpSbxMethodImpl;	// Impl data

public:
    SBX_DECL_PERSIST_NODATA(SBXCR_SBX,SBXID_METHOD,1);
    TYPEINFO();
    SbxMethod( const String& r, SbxDataType t )
    : SbxVariable( t ) { SetName( r ); }
    SbxMethod( const SbxMethod& r ) : SvRefBase( r ), SbxVariable( r ) {}
    SbxMethod& operator=( const SbxMethod& r )
    { SbxVariable::operator=( r ); return *this; }
    BOOL Run( SbxValues* pValues = NULL );
    virtual SbxClassType GetClass() const;
};

#ifndef __SBX_SBXMETHODREF_HXX
#define __SBX_SBXMETHODREF_HXX

#ifndef SBX_METHOD_DECL_DEFINED
#define SBX_METHOD_DECL_DEFINED
SV_DECL_REF(SbxMethod)
#endif
SV_IMPL_REF(SbxMethod)

#endif

}

#endif

