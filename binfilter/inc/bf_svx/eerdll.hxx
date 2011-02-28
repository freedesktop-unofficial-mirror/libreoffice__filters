/*************************************************************************
 *
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER.
 * 
 * Copyright 2000, 2010 Oracle and/or its affiliates.
 *
 * OpenOffice.org - a multi-platform office productivity suite
 *
 * This file is part of OpenOffice.org.
 *
 * OpenOffice.org is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License version 3
 * only, as published by the Free Software Foundation.
 *
 * OpenOffice.org is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License version 3 for more details
 * (a copy is included in the LICENSE file that accompanied this code).
 *
 * You should have received a copy of the GNU Lesser General Public License
 * version 3 along with OpenOffice.org.  If not, see
 * <http://www.openoffice.org/license.html>
 * for a copy of the LGPLv3 License.
 *
 ************************************************************************/

#ifndef _EERDLL_HXX
#define _EERDLL_HXX

#include <bf_svtools/bf_solar.h>

namespace binfilter {
class GlobalEditData;
}//end of namespace binfilter
#ifndef _TOOLS_RESID_HXX //autogen
#include <tools/resid.hxx>
#endif

namespace binfilter {

class EditResId: public ResId
{
public:
    EditResId( USHORT nId );
};

class EditDLL
{
    ResMgr*			pResMgr;
    GlobalEditData*	pGlobalData;

public:
                    EditDLL();
                    ~EditDLL();

    ResMgr*			GetResMgr() const 		{ return pResMgr; }
    GlobalEditData*	GetGlobalData() const	{ return pGlobalData; }
};

#define EE_DLL() (*(EditDLL**)GetAppData( BF_SHL_EDIT ) )

}//end of namespace binfilter
#endif //_EERDLL_HXX
