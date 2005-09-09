/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: scdll.hxx,v $
 *
 *  $Revision: 1.3 $
 *
 *  last change: $Author: rt $ $Date: 2005-09-09 11:26:07 $
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

#ifndef SC_SCDLL_HXX
#define SC_SCDLL_HXX

class ResMgr;
class SvFactory; 
class SotFactory;
class StatusBar;
class SfxMedium;
class SfxFilter;

#ifndef _SFXDEFS_HXX //autogen
#include <bf_sfx2/sfxdefs.hxx>
#endif
#ifndef _SFXMODULE_HXX //autogen
#include <bf_sfx2/module.hxx>
#endif
#ifndef _SFX_OBJFAC_HXX
#include <bf_sfx2/docfac.hxx>
#endif
namespace binfilter {

//-------------------------------------------------------------------------

class ScDLL

/*	[Description]

    This class is a wrapper for a Load-On-Demand-DLL. One instance
    per SfxApplication will be created for the runtime of
    SfxApplication-subclass::Main().

    Remember: Do export this class! It is used by the application.
*/

{
public:
                    // Ctor/Dtor must be linked to the application
                    ScDLL();
                    ~ScDLL();

                    // static-init/exit-code must be linked to the application
    static void 	LibInit();	// called from SfxApplication-subclass::Init()
    static void 	LibExit();	// called from SfxApplication-subclass::Exit()
    static void 	PreExit();	// muss vor LibExit gerufen werden

                    // DLL-init/exit-code must be linked to the DLL only
    static void 	Init(); 	// called directly after loading the DLL
    static void 	Exit(); 	// called directly befor unloading the DLL

//STRIP001 	static void 	FillStatusBar(StatusBar &rBar);

    static ULONG	DetectFilter( SfxMedium& rMedium, const SfxFilter** ppFilter,
                                    SfxFilterFlags nMust, SfxFilterFlags nDont );
};

//-------------------------------------------------------------------------

class ScModuleDummy: public SfxModule

/*	[Description]

    This tricky class keeps pointers to the SvFactories while
    the DLL isn`t loaded. A pointer to the one instance is available
    through SXX_MOD() (shared-lib-app-data).
*/

{
public:
                    // SvFactory name convention:
                    // 'p' + SfxObjectShell-subclass + 'Factory'
    SotFactory* 	pScDocShellFactory;

                    ScModuleDummy( ResMgr *pResMgr, BOOL bDummy, SfxObjectFactory* pFact )
                    :	SfxModule(pResMgr, bDummy, pFact, NULL),
                        pScDocShellFactory(pFact)
                    {}

    virtual SfxModule* Load();

    static SvGlobalName GetID(USHORT nFileFormat);
    static USHORT		HasID(const SvGlobalName& rName);
};

//-------------------------------------------------------------------------

#define SC_DLL() ( *(ScModuleDummy**) GetAppData(BF_SHL_CALC) )

} //namespace binfilter
#endif

