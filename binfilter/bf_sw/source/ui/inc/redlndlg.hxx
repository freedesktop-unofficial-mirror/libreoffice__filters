/*************************************************************************
 *
 *  $RCSfile: redlndlg.hxx,v $
 *
 *  $Revision: 1.2 $
 *
 *  last change: $Author: mwu $ $Date: 2003-11-06 07:55:35 $
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
#ifndef _SWREDLNDLG_HXX
#define _SWREDLNDLG_HXX

#include "chldwrap.hxx"

#ifndef _BASEDLGS_HXX //autogen
#include <bf_sfx2/basedlgs.hxx>
#endif
namespace binfilter {

class SwChildWinWrapper;
//STRIP001 class SwRedlineAcceptDlg;

/*------------------------------------------------------------------------
    Beschreibung:
------------------------------------------------------------------------*/

//STRIP001 class SwModelessRedlineAcceptDlg : public SfxModelessDialog
//STRIP001 {
//STRIP001 	SwRedlineAcceptDlg*		pImplDlg;
//STRIP001 	SwChildWinWrapper*		pChildWin;
//STRIP001 
//STRIP001 	virtual void	Resize();
//STRIP001 
//STRIP001 public:
//STRIP001 	SwModelessRedlineAcceptDlg(SfxBindings*, SwChildWinWrapper*, Window *pParent);
//STRIP001 	~SwModelessRedlineAcceptDlg();
//STRIP001 
//STRIP001 	virtual void	Activate();
//STRIP001 	virtual void	FillInfo(SfxChildWinInfo&) const;
//STRIP001 	void			Initialize (SfxChildWinInfo* pInfo);
//STRIP001 };

/*------------------------------------------------------------------------
    Beschreibung:
------------------------------------------------------------------------*/

//STRIP001 class SwModalRedlineAcceptDlg : public SfxModalDialog
//STRIP001 {
//STRIP001 	SwRedlineAcceptDlg*		pImplDlg;
//STRIP001 
//STRIP001 	virtual void	Resize();
//STRIP001 
//STRIP001 public:
//STRIP001 	SwModalRedlineAcceptDlg(Window *pParent);
//STRIP001 	~SwModalRedlineAcceptDlg();
//STRIP001 
//STRIP001 	void			AcceptAll( BOOL bAccept );
//STRIP001 	virtual void	Activate();
//STRIP001 };

/*------------------------------------------------------------------------
    Beschreibung:
------------------------------------------------------------------------*/

class SwRedlineAcceptChild : public SwChildWinWrapper
{
public:
    SwRedlineAcceptChild(	Window* pParent,USHORT nId, SfxBindings*, SfxChildWinInfo* ):SwChildWinWrapper( pParent, nId ){DBG_ASSERT(0, "STRIP");}; //STRIP001 	SwRedlineAcceptChild(	Window* ,
//STRIP001 							USHORT nId,
//STRIP001 							SfxBindings*,
//STRIP001 							SfxChildWinInfo*  );

    SFX_DECL_CHILDWINDOW( SwRedlineAcceptChild );

//STRIP001 	virtual BOOL	ReInitDlg(SwDocShell *pDocSh);
};


} //namespace binfilter
#endif


