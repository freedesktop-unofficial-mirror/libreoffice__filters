/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: dialmgr.hxx,v $
 *
 *  $Revision: 1.7 $
 *
 *  last change: $Author: rt $ $Date: 2008-03-12 12:47:36 $
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

