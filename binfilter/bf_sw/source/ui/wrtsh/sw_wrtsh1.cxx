/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: sw_wrtsh1.cxx,v $
 *
 *  $Revision: 1.12 $
 *
 *  last change: $Author: rt $ $Date: 2008-03-12 10:55:38 $
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


#ifdef _MSC_VER
#pragma hdrstop
#endif


#if STLPORT_VERSION>=321
#include <math.h>	// prevent conflict between exception and std::exception
#endif

#ifndef _HINTIDS_HXX
#include <hintids.hxx>
#endif

#ifndef _SVDVIEW_HXX //autogen
#include <bf_svx/svdview.hxx>
#endif
#ifndef _IPENV_HXX //autogen
#include <bf_so3/ipenv.hxx>
#endif

#ifndef _WDOCSH_HXX
#include <wdocsh.hxx>
#endif

#ifndef _HORIORNT_HXX
#include <horiornt.hxx>
#endif

#ifndef _WRTSH_HXX
#include <wrtsh.hxx>
#endif
#ifndef _CMDID_H
#include <cmdid.h>
#endif
#ifndef _PAGEDESC_HXX
#include <pagedesc.hxx>
#endif
#ifndef _VISCRS_HXX //autogen wg. SwSelPaintRects
#include <viscrs.hxx>
#endif
#ifndef _SWDTFLVR_HXX
#include <swdtflvr.hxx>
#endif
#ifndef _SWERROR_H
#include <swerror.h>
#endif
#ifndef _WRTSH_HRC
#include <wrtsh.hrc>
#endif
namespace binfilter {

#define COMMON_INI_LIST \
        rView(rShell),\
        ePageMove(MV_NO),\
        pCrsrStack(0),	\
        fnLeaveSelect(&SwWrtShell::SttLeaveSelect),\
        fnDrag(&SwWrtShell::BeginDrag),\
        fnEndDrag(&SwWrtShell::EndDrag),\
        fnSetCrsr(&SwWrtShell::SetCrsr),\
        fnKillSel(&SwWrtShell::Ignore),\
        bDestOnStack(FALSE),\
        pModeStack(0)

#define BITFLD_INI_LIST \
        bClearMark = \
        bIns = TRUE;\
        bAddMode = \
        bExtMode = \
        bInSelect = \
        bCopy = \
        bLayoutMode = \
        bNoEdit = \
        bSelWrd = \
        bSelLn = \
        bIsInClickToEdit = FALSE;



/*------------------------------------------------------------------------
 Beschreibung:	 Object in die Core einfuegen.
                 Vom ClipBoard oder Insert
------------------------------------------------------------------------*/


/*------------------------------------------------------------------------
    Beschreibung: Das aktuelle selektierte OLE-Objekt wird mit dem
                  Verb in den Server geladen.
------------------------------------------------------------------------*/





/*N*/ void SwWrtShell::CalcAndSetScale( SvEmbeddedObjectRef xObj,
/*N*/ 							 const SwRect *pFlyPrtRect,
/*N*/ 							 const SwRect *pFlyFrmRect )
/*N*/ {
            DBG_ERROR("Split!");
/*N*/ }

/*N*/ SwWrtShell::SwWrtShell( SwDoc& rDoc, Window *pWin, SwView &rShell,
/*N*/                                          SwRootFrm *pRoot, const SwViewOption *pViewOpt )
/*N*/  : SwFEShell( rDoc, pWin, pRoot, pViewOpt),
/*N*/    COMMON_INI_LIST
/*N*/ {
/*N*/  BITFLD_INI_LIST
/*N*/  SET_CURR_SHELL( this );
/*N*/  SetSfxViewShell( (SfxViewShell *)&rShell );
/*N*/  SetFlyMacroLnk( LINK(this, SwWrtShell, ExecFlyMac) );
/*N*/ }

    void SwWrtShell::ConnectObj( SvInPlaceObjectRef, const SwRect &, const SwRect & )
    {
    }

    SwWrtShell::~SwWrtShell()
    {
        SET_CURR_SHELL( this );
        while(IsModePushed())
        {
            DBG_BF_ASSERT(0, "STRIP");
        };
        while(PopCrsr(FALSE));
    }
}
