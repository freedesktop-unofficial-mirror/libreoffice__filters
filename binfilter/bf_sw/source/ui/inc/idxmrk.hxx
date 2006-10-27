/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: idxmrk.hxx,v $
 *
 *  $Revision: 1.4 $
 *
 *  last change: $Author: rt $ $Date: 2006-10-28 00:43:40 $
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
#ifndef _IDXMRK_HXX
#define _IDXMRK_HXX

#ifndef _COM_SUN_STAR_CONTAINER_XNAMEACCESS_HPP_
#include <com/sun/star/container/XNameAccess.hpp>
#endif
#ifndef _BASEDLGS_HXX
#include <bf_sfx2/basedlgs.hxx>
#endif

#ifndef _FIXED_HXX //autogen
#include <vcl/fixed.hxx>
#endif

#ifndef _SV_LSTBOX_HXX
#include <vcl/lstbox.hxx>
#endif
#ifndef _COMBOBOX_HXX //autogen
#include <vcl/combobox.hxx>
#endif
#ifndef _SVX_STDDLG_HXX
#include <bf_svx/stddlg.hxx>
#endif

#ifndef _FIELD_HXX //autogen
#include <vcl/field.hxx>
#endif

#ifndef _GROUP_HXX //autogen
#include <vcl/group.hxx>
#endif

#ifndef _BUTTON_HXX //autogen
#include <vcl/button.hxx>
#endif

#ifndef _IMAGEBTN_HXX //autogen
#include <vcl/imagebtn.hxx>
#endif
#ifndef _SFX_CHILDWIN_HXX //autogen
#include <bf_sfx2/childwin.hxx>
#endif
#ifndef _TOXE_HXX
#include "toxe.hxx"
#endif
#ifndef _STDCTRL_HXX
#include <svtools/stdctrl.hxx>
#endif
#ifndef  _COM_SUN_STAR_I18N_XEXTENDEDINDEXENTRYSUPPLIER_HPP_
#include <com/sun/star/i18n/XExtendedIndexEntrySupplier.hpp>
#endif
namespace binfilter {
class SwWrtShell;
class SwTOXMgr;
class SwTOXMark;
/*--------------------------------------------------------------------
     Beschreibung:	Markierung fuer Verzeichniseintrag einfuegen
 --------------------------------------------------------------------*/
class SwIndexMarkFloatDlg;
class SwIndexMarkModalDlg;
/* -----------------06.10.99 10:11-------------------

 --------------------------------------------------*/
/* -----------------06.10.99 10:33-------------------

 --------------------------------------------------*/

/* -----------------07.09.99 08:02-------------------

 --------------------------------------------------*/
class SwInsertIdxMarkWrapper : public SfxChildWindow
{
protected:
    SwInsertIdxMarkWrapper(	Window *pParentWindow,
                            sal_uInt16 nId,
                            SfxBindings* pBindings,
                            SfxChildWinInfo* pInfo );

    SFX_DECL_CHILDWINDOW(SwInsertIdxMarkWrapper);

public:

};

/* -----------------15.09.99 08:39-------------------

 --------------------------------------------------*/
class SwAuthMarkModalDlg;
/* -----------------07.09.99 08:02-------------------

 --------------------------------------------------*/
class SwInsertAuthMarkWrapper : public SfxChildWindow
{
protected:
    SwInsertAuthMarkWrapper(	Window *pParentWindow,
                            sal_uInt16 nId,
                            SfxBindings* pBindings,
                            SfxChildWinInfo* pInfo );

    SFX_DECL_CHILDWINDOW(SwInsertAuthMarkWrapper);

public:
};
/* -----------------06.10.99 10:11-------------------

 --------------------------------------------------*/
/* -----------------06.10.99 10:33-------------------

 --------------------------------------------------*/


} //namespace binfilter
#endif // _IDXMRK_HXX

