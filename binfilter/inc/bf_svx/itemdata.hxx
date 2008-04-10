/*************************************************************************
 *
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER.
 * 
 * Copyright 2008 by Sun Microsystems, Inc.
 *
 * OpenOffice.org - a multi-platform office productivity suite
 *
 * $RCSfile: itemdata.hxx,v $
 * $Revision: 1.4 $
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
#ifndef _SVX_ITEMDATA_HXX
#define _SVX_ITEMDATA_HXX

#ifndef _SHL_HXX //autogen
#include <tools/shl.hxx>
#endif
#ifndef _PSTM_HXX //autogen
#include <tools/pstm.hxx>
#endif
namespace binfilter {

class SvxGlobalItemData
{
private:
    SvClassManager*	pClassMgr;

public:
                    SvxGlobalItemData();
                    ~SvxGlobalItemData() 	{ delete pClassMgr; }

    SvClassManager&	GetClassManager();
};

#define ITEMDATA() (*(SvxGlobalItemData**)GetAppData( BF_SHL_ITEM ) )

inline SvxGlobalItemData::SvxGlobalItemData()
{
    pClassMgr = 0;
    *(SvxGlobalItemData**)GetAppData(BF_SHL_ITEM) = this;
}

inline SvClassManager& SvxGlobalItemData::GetClassManager()
{
    if ( !pClassMgr )
        pClassMgr = new SvClassManager;
    return *pClassMgr;
}

}//end of namespace binfilter
#endif

