/*************************************************************************
 *
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER.
 * 
 * Copyright 2008 by Sun Microsystems, Inc.
 *
 * OpenOffice.org - a multi-platform office productivity suite
 *
 * $RCSfile: dialmgr.hxx,v $
 * $Revision: 1.8 $
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
#ifndef _SVX_DIALMGR_HXX
#define _SVX_DIALMGR_HXX

// include ---------------------------------------------------------------

class ResMgr;
namespace binfilter {

class GraphicFilter;
// forward ---------------------------------------------------------------


// struct DialogsResMgr --------------------------------------------------

struct DialogsResMgr
{
    DialogsResMgr();
    ~DialogsResMgr();

    ResMgr*		pResMgr;

            // impl. steht impgrf.cxx !!
    GraphicFilter* GetGrfFilter_Impl();

private:
    // fuers LoadGraphic und Konsorten
    GraphicFilter* pGrapicFilter;
};

#define DIALOG_MGR()	*(*(DialogsResMgr**)GetAppData(BF_SHL_SVX))->pResMgr
#define SVX_RES(i)		ResId(i,DIALOG_MGR())
#define SVX_RESSTR(i)	UniString(ResId(i,DIALOG_MGR()))
#define SVX_RESSSTR(i)	String(ResId(i,DIALOG_MGR()))

}//end of namespace binfilter
#endif

