/*************************************************************************
 *
 *  $RCSfile: arrdecl.hxx,v $
 *
 *  $Revision: 1.2 $
 *
 *  last change: $Author: mwu $ $Date: 2003-11-06 08:26:07 $
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
#ifndef _SFX_ARRDECL_HXX
#define _SFX_ARRDECL_HXX

#include <tools/list.hxx>

#ifndef _SVARRAY_HXX
#include <svtools/svarray.hxx>
#endif
#include "bf_sfx2/minarray.hxx"
namespace binfilter {

struct CntUpdateResult;

SV_DECL_PTRARR_DEL(CntUpdateResults_Impl, CntUpdateResult*, 4, 4)//STRIP008 ;

class SfxObjectShell;
SV_DECL_PTRARR( SfxObjectShellArr_Impl, SfxObjectShell*, 4, 4 )//STRIP008 ;

class SfxViewFrame;
SV_DECL_PTRARR( SfxViewFrameArr_Impl, SfxViewFrame*, 4, 4 )//STRIP008 ;

class SfxViewShell;
SV_DECL_PTRARR( SfxViewShellArr_Impl, SfxViewShell*, 4, 4 )//STRIP008 ;

class SfxObjectFactory;
typedef SfxObjectFactory* SfxObjectFactoryPtr;
SV_DECL_PTRARR( SfxObjectFactoryArr_Impl, SfxObjectFactoryPtr, 3, 3 )//STRIP008 ;

struct SfxTbxCtrlFactory;
SV_DECL_PTRARR_DEL( SfxTbxCtrlFactArr_Impl, SfxTbxCtrlFactory*, 8, 4 )//STRIP008 ;

struct SfxStbCtrlFactory;
SV_DECL_PTRARR_DEL( SfxStbCtrlFactArr_Impl, SfxStbCtrlFactory*, 8, 4 )//STRIP008 ;

struct SfxMenuCtrlFactory;
SV_DECL_PTRARR_DEL( SfxMenuCtrlFactArr_Impl, SfxMenuCtrlFactory*, 2, 2 )//STRIP008 ;

struct SfxChildWinFactory;
SV_DECL_PTRARR_DEL( SfxChildWinFactArr_Impl, SfxChildWinFactory*, 2, 2 )//STRIP008 ;

class SfxModule;
SV_DECL_PTRARR( SfxModuleArr_Impl, SfxModule*, 2, 2 )//STRIP008 ;

class SfxFilter;
DECL_PTRARRAY( SfxFilterArr_Impl, SfxFilter*, 4, 4 )//STRIP008 ;

class SfxFrame;
typedef SfxFrame* SfxFramePtr;
SV_DECL_PTRARR( SfxFrameArr_Impl, SfxFramePtr, 4, 4 )//STRIP008 ;

DECLARE_LIST( SfxFilterList_Impl, SfxFilter* )//STRIP008 DECLARE_LIST( SfxFilterList_Impl, SfxFilter* );

struct SfxExternalLib_Impl;
typedef SfxExternalLib_Impl* SfxExternalLibPtr;
SV_DECL_PTRARR_DEL( SfxExternalLibArr_Impl, SfxExternalLibPtr, 2, 2 )//STRIP008 ;

//class XEventListenerRef;
//typedef XEventListenerRef* XEventListenerPtr;
//SV_DECL_PTRARR_DEL( XEventListenerArr_Impl, XEventListenerPtr, 4, 4 )//STRIP008 ;

//class XFrameRef;
//typedef XFrameRef* XFramePtr;
//SV_DECL_PTRARR_DEL( XFrameArr_Impl, XFramePtr, 4, 4 )//STRIP008 ;

class SfxSlot;
typedef SfxSlot* SfxSlotPtr;
SV_DECL_PTRARR( SfxSlotArr_Impl, SfxSlotPtr, 20, 20 )//STRIP008 ;

}//end of namespace binfilter
#endif
