/*************************************************************************
 *
 *  $RCSfile: drtxtob.hxx,v $
 *
 *  $Revision: 1.2 $
 *
 *  last change: $Author: mwu $ $Date: 2003-11-06 07:29:42 $
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

#ifndef SC_DRTXTOB_HXX
#define SC_DRTXTOB_HXX

#ifndef _SFX_HXX
#endif

#ifndef _SFX_SHELL_HXX //autogen
#include <bf_sfx2/shell.hxx>
#endif
#ifndef _SFXMODULE_HXX //autogen
#include <bf_sfx2/module.hxx>
#endif
#ifndef _LINK_HXX 
#include <tools/link.hxx>
#endif

#include "shellids.hxx"
class TransferableDataHelper;
class TransferableClipboardListener;
namespace binfilter {

USHORT ScGetFontWorkId();		// statt SvxFontWorkChildWindow::GetChildWindowId()

class ScViewData;

class ScDrawTextObjectBar : public SfxShell
{
//STRIP001 	ScViewData*			pViewData;
//STRIP001 	TransferableClipboardListener* pClipEvtLstnr;
//STRIP001 	BOOL				bPastePossible;
//STRIP001 
//STRIP001 	DECL_LINK( ClipboardChanged, TransferableDataHelper* );

public:
//STRIP001 	TYPEINFO();
    SFX_DECL_INTERFACE(SCID_DRAW_TEXT_SHELL);

    ScDrawTextObjectBar(ScViewData* pData){DBG_ASSERT(0, "STRIP"); }
//STRIP001 		~ScDrawTextObjectBar();

    void StateDisableItems( SfxItemSet &rSet ){DBG_ASSERT(0, "STRIP");} //STRIP001 //STRIP001 	void StateDisableItems( SfxItemSet &rSet );

    void Execute( SfxRequest &rReq ){DBG_ASSERT(0, "STRIP");} //STRIP001 //STRIP001 	void Execute( SfxRequest &rReq );
    void ExecuteTrans( SfxRequest& rReq ){DBG_ASSERT(0, "STRIP");} //STRIP001 //STRIP001 	void ExecuteTrans( SfxRequest& rReq );
    void GetState( SfxItemSet& rSet ){DBG_ASSERT(0, "STRIP");} //STRIP001 //STRIP001 	void GetState( SfxItemSet& rSet );
    void GetClipState( SfxItemSet& rSet ){DBG_ASSERT(0, "STRIP");} //STRIP001 //STRIP001 	void GetClipState( SfxItemSet& rSet );

    void ExecuteAttr( SfxRequest &rReq ){DBG_ASSERT(0, "STRIP");} //STRIP001 //STRIP001 //STRIP001 	void ExecuteAttr( SfxRequest &rReq );
    void GetAttrState( SfxItemSet& rSet ){DBG_ASSERT(0, "STRIP");} //STRIP001 //STRIP001 	void GetAttrState( SfxItemSet& rSet );
    void ExecuteToggle( SfxRequest &rReq ){DBG_ASSERT(0, "STRIP");} //STRIP001 //STRIP001 	void ExecuteToggle( SfxRequest &rReq );
//STRIP001 
//STRIP001 	BOOL ExecuteCharDlg( const SfxItemSet& rArgs, SfxItemSet& rOutSet );
//STRIP001 	BOOL ExecuteParaDlg( const SfxItemSet& rArgs, SfxItemSet& rOutSet );
//STRIP001 
    void ExecuteExtra( SfxRequest &rReq ){DBG_ASSERT(0, "STRIP");} //STRIP001 //STRIP001 	void ExecuteExtra( SfxRequest &rReq );
    void ExecFormText(SfxRequest& rReq){DBG_ASSERT(0, "STRIP");} //STRIP001 //STRIP001 	void ExecFormText(SfxRequest& rReq);		// StarFontWork
    void GetFormTextState(SfxItemSet& rSet){DBG_ASSERT(0, "STRIP");} //STRIP001 //STRIP001 	void GetFormTextState(SfxItemSet& rSet);
//STRIP001 
//STRIP001 private:
//STRIP001 	void ExecuteGlobal( SfxRequest &rReq );			// von Execute gerufen fuer ganze Objekte
//STRIP001 	void GetGlobalClipState( SfxItemSet& rSet );
//STRIP001 	void ExecutePasteContents( SfxRequest &rReq );
//STRIP001 	BOOL IsNoteEdit();
};



} //namespace binfilter
#endif

