/*************************************************************************
 *
 *  $RCSfile: module.hxx,v $
 *
 *  $Revision: 1.1.1.1 $
 *
 *  last change: $Author: hjs $ $Date: 2003-10-01 12:23:31 $
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
#ifndef _SFXMODULE_HXX
#define _SFXMODULE_HXX	// intern
#define _SFXMOD_HXX		// extern

#ifndef _SFX_SHELL_HXX
#include <bf_sfx2/shell.hxx>
#endif

#ifndef _SFX_IMGDEF_HXX
#include <bf_sfx2/imgdef.hxx>
#endif
#ifndef _SAL_TYPES_H_
#include <sal/types.h>
#endif
class ImageList;

class SfxAcceleratorManager;
class SfxMenuBarManager;
class SfxBindings;
class SfxObjectFactory;
class ModalDialog;
class SfxObjectFactory;
class SfxModuleArr_Impl;
class SfxModule_Impl;
class SfxSlotPool;
struct SfxChildWinContextFactory;
struct SfxChildWinFactory;
struct SfxMenuCtrlFactory;
struct SfxStbCtrlFactory;
struct SfxTbxCtrlFactory;
class SfxTbxCtrlFactArr_Impl;
class SfxChildWinFactArr_Impl;
class SfxMenuCtrlFactArr_Impl;
class SfxStbCtrlFactArr_Impl;
class SfxTabPage;
class Window;

class ISfxModule
{
public:
    virtual ModalDialog*	CreateAboutDialog() = 0;
    virtual					~ISfxModule(){};
    virtual ResMgr*			GetResMgr() = 0;
};

//====================================================================

class SfxModule : public SfxShell, public ISfxModule
{
private:
    ResMgr*                     pResMgr;
    sal_Bool                    bDummy : 1;
    SfxModule_Impl*             pImpl;

#if _SOLAR__PRIVATE
    void 						Construct_Impl();
#endif

protected:
    virtual sal_Bool                QueryUnload();

public:
                                TYPEINFO();
                                SFX_DECL_INTERFACE(SFX_INTERFACE_SFXMODULE);

                                SfxModule( ResMgr* pMgrP, sal_Bool bDummy,
                                    SfxObjectFactory* pFactoryP, ... );
                                ~SfxModule();

    virtual	SfxModule*			Load();
    virtual void            	Free();
    sal_Bool						IsLoaded() const { return !bDummy; }

    virtual ModalDialog*		CreateAboutDialog();
    virtual ResMgr*             GetResMgr();
    SfxSlotPool*				GetSlotPool() const;

    void						RegisterToolBoxControl(SfxTbxCtrlFactory*);
    void                        RegisterChildWindow(SfxChildWinFactory*);
//STRIP001 	void                        RegisterChildWindowContext( sal_uInt16,	SfxChildWinContextFactory* );
    void                        RegisterStatusBarControl(SfxStbCtrlFactory*);
    void                        RegisterMenuControl(SfxMenuCtrlFactory*);

    virtual SfxTabPage*			CreateTabPage( sal_uInt16 nId,
                                               Window* pParent,
                                               const SfxItemSet& rSet );
    virtual void                Invalidate(USHORT nId = 0);

#if _SOLAR__PRIVATE
    static SfxModuleArr_Impl&   GetModules_Impl();
    SfxTbxCtrlFactArr_Impl* 	GetTbxCtrlFactories_Impl() const;
    SfxStbCtrlFactArr_Impl* 	GetStbCtrlFactories_Impl() const;
    SfxMenuCtrlFactArr_Impl* 	GetMenuCtrlFactories_Impl() const;
    SfxChildWinFactArr_Impl*	GetChildWinFactories_Impl() const;
//STRIP001     ImageList*                  GetImageList_Impl( BOOL bBig );
    ImageList*                  GetImageList_Impl( BOOL bBig, BOOL bHiContrast );
#endif
};

#define SFX_IMPL_MODULE_LIBRARY( LibName )									\
                                                                            \
        extern "C" void _CDECLARE_ Init##LibName##Dll()                     \
        {																	\
            LibName##DLL::Init();											\
        }																	\
        extern "C" void _CDECLARE_ DeInit##LibName##Dll()                   \
        {																	\
            LibName##DLL::Exit();											\
        }

#endif

