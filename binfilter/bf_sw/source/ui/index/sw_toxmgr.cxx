/*************************************************************************
 *
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER.
 * 
 * Copyright 2008 by Sun Microsystems, Inc.
 *
 * OpenOffice.org - a multi-platform office productivity suite
 *
 * $RCSfile: sw_toxmgr.cxx,v $
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

#ifndef _HORIORNT_HXX
#include <horiornt.hxx>
#endif

#ifndef _WRTSH_HXX
#include <wrtsh.hxx>
#endif
#ifndef _SHELLRES_HXX
#include <shellres.hxx>
#endif

#ifndef _GLOBALS_HRC
#include <globals.hrc>
#endif

#include <tox.hxx>

namespace binfilter {

/*-----------------23.01.98 07:41-------------------
    Standard - Verzeichnisnamen herausreichen
--------------------------------------------------*/
/*N*/ const String&	SwTOXBase::GetTOXName(TOXTypes eType)
/*N*/ {
/*N*/ 	const String* pRet;
/*N*/ 	ShellResource* pShellRes = ViewShell::GetShellRes();
/*N*/ 	switch(eType)
/*N*/ 	{
/*N*/ 		case  TOX_CONTENT 	   :	pRet = &pShellRes->aTOXContentName;		  break;
/*N*/ 		case  TOX_INDEX 	   :    pRet = &pShellRes->aTOXIndexName;         break;
/*?*/ 		case  TOX_USER 		   :    pRet = &pShellRes->aTOXUserName;       	  break;
/*?*/ 		case  TOX_ILLUSTRATIONS:    pRet = &pShellRes->aTOXIllustrationsName; break;
/*?*/ 		case  TOX_OBJECTS	   :    pRet = &pShellRes->aTOXObjectsName;       break;
/*?*/ 		case  TOX_TABLES	   :    pRet = &pShellRes->aTOXTablesName;        break;
/*?*/ 		case  TOX_AUTHORITIES :     pRet = &pShellRes->aTOXAuthoritiesName;   break;
/*N*/ 	}
/*N*/ 	return *pRet;
/*N*/ }

}
