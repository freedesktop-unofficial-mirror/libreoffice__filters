/*************************************************************************
 *
 *  $RCSfile: sw_swdll.cxx,v $
 *
 *  $Revision: 1.2 $
 *
 *  last change: $Author: mwu $ $Date: 2003-11-06 07:53:59 $
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


#pragma hdrstop

#ifndef _SVDOBJ_HXX //autogen
#include <bf_svx/svdobj.hxx>
#endif
#ifndef _RTL_LOGFILE_HXX_
#include <rtl/logfile.hxx>
#endif

#ifndef _GLOBDOC_HRC
#include "globdoc.hrc"
#endif

#ifndef _SWDLL_HXX
#include <swdll.hxx>
#endif
#ifndef _SWWDOCSH_HXX
#include <wdocsh.hxx>
#endif
#ifndef _SWGLOBDOCSH_HXX
#include <globdoc.hxx>
#endif
#ifndef _INITUI_HXX
#include <initui.hxx>
#endif
#ifndef _SWMODULE_HXX
#include <swmodule.hxx>
#endif
#ifndef _SWTYPES_HXX
#include <swtypes.hxx>
#endif
#ifndef _INIT_HXX
#include <init.hxx>
#endif
#ifndef _DOBJFAC_HXX
#include <dobjfac.hxx>
#endif
#ifndef _CFGID_H
#include <cfgid.h>
#endif
namespace binfilter {

/*************************************************************************
|*
|* Init
|*
\************************************************************************/

/*N*/ void SwDLL::Init()
/*N*/ {
/*N*/ 	RTL_LOGFILE_CONTEXT_AUTHOR( aLog, "SW", "JP93722",  "SwDLL" );
/*N*/ 
/*N*/ 	// called directly after loading the DLL
/*N*/ 	// do whatever you want, you may use Sw-DLL too
/*N*/ 
/*N*/ 	// the SdModule must be created
/*N*/ 	SwModuleDummy** ppShlPtr = (SwModuleDummy**) GetAppData(BF_SHL_WRITER);
/*N*/ 
/*N*/ 	SvFactory* pDocFact     = (SvFactory*)(*ppShlPtr)->pSwDocShellFactory;
/*N*/ 	SvFactory* pWDocFact    = (SvFactory*)(*ppShlPtr)->pSwWebDocShellFactory;
/*N*/ 	SvFactory* pGlobDocFact = (SvFactory*)(*ppShlPtr)->pSwGlobalDocShellFactory;
/*N*/ 	delete (*ppShlPtr);
/*N*/     SwModule* pModule = new SwModule( pWDocFact, pDocFact, pGlobDocFact );
/*N*/ 	(*ppShlPtr) = pModule;
/*N*/ 	(*ppShlPtr)->pSwDocShellFactory    		= pDocFact    ;
/*N*/ 	(*ppShlPtr)->pSwWebDocShellFactory     	= pWDocFact   ;
/*N*/ 	(*ppShlPtr)->pSwGlobalDocShellFactory 	= pGlobDocFact;
/*N*/ 
/*N*/     if ( pDocFact )
/*N*/     {
/*N*/         SwDocShell::Factory().RegisterPluginMenuBar( SW_RES(CFG_SW_MENU_PORTAL));
/*N*/         SwDocShell::Factory().RegisterMenuBar(SW_RES(CFG_SW_MENU));
/*N*/         SwDocShell::Factory().RegisterAccel(SW_RES(CFG_SW_ACCEL));
/*N*/         SwGlobalDocShell::Factory().RegisterMenuBar(SW_RES(CFG_SWGLOBAL_MENU));
/*N*/         SwGlobalDocShell::Factory().RegisterAccel(SW_RES(CFG_SW_ACCEL));
/*N*/         SwGlobalDocShell::Factory().RegisterPluginMenuBar( SW_RES(CFG_SWGLOBAL_MENU_PORTAL));
/*N*/     }
/*N*/ 
/*N*/ 	SwWebDocShell::Factory().RegisterPluginMenuBar( SW_RES(CFG_SWWEB_MENU_PORTAL));
/*N*/ 	SwWebDocShell::Factory().RegisterMenuBar(SW_RES(CFG_SWWEB_MENU));
/*N*/ 	SwWebDocShell::Factory().RegisterAccel(SW_RES(CFG_SWWEB_ACCEL));
/*N*/ 
/*N*/ 	SdrObjFactory::InsertMakeObjectHdl( LINK( &aSwObjectFactory, SwObjectFactory, MakeObject ) );
/*N*/ 
/*N*/ 	RTL_LOGFILE_CONTEXT_TRACE( aLog, "Init Core/UI/Filter" );
/*N*/ 
/*N*/ 	//Initialisierung der Statics
/*N*/ 	::binfilter::_InitCore();
/*N*/ 	::binfilter::_InitFilter();
/*N*/ 	::binfilter::_InitUI();
/*N*/ 
/*N*/ 	pModule->InitAttrPool();
/*N*/ 	//jetzt darf das SwModule seinen Pool anlegen
/*N*/ 
/*N*/ 	// register your view-factories here
/*N*/ 	RegisterFactories();
/*N*/ 
/*N*/ 	// register your shell-interfaces here
/*N*/ 	RegisterInterfaces();
/*N*/ 
/*N*/ 	// register your controllers here
/*N*/ 	RegisterControls();
/*N*/ }



/*************************************************************************
|*
|* Exit
|*
\************************************************************************/

/*N*/ void SwDLL::Exit()
/*N*/ {
/*N*/ 	// called directly befor unloading the DLL
/*N*/ 	// do whatever you want, Sw-DLL is accessible
/*N*/ 
/*N*/ 	// der Pool muss vor den statics geloescht werden
/*N*/ 	SW_MOD()->RemoveAttrPool();
/*N*/ 
/*N*/ 	::binfilter::_FinitUI();
/*N*/ 	::binfilter::_FinitFilter();
/*N*/ 	::binfilter::_FinitCore();
/*N*/ 	// Objekt-Factory austragen
/*N*/ 	SdrObjFactory::RemoveMakeObjectHdl(LINK(&aSwObjectFactory, SwObjectFactory, MakeObject ));
/*N*/    // the SwModule must be destroyed
/*N*/ 	SwModuleDummy** ppShlPtr = (SwModuleDummy**) GetAppData(BF_SHL_WRITER);
/*N*/ 	delete (*ppShlPtr);
/*N*/ 	(*ppShlPtr) = NULL;
/*N*/ }

}
