/*************************************************************************
 *
 *  $RCSfile: sw_globdoc.cxx,v $
 *
 *  $Revision: 1.2 $
 *
 *  last change: $Author: aw $ $Date: 2003-10-16 17:12:29 $
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

#ifndef _SO_CLSIDS_HXX
#include <so3/clsids.hxx>
#endif

#include "swtypes.hxx"


#include "shellio.hxx"
#include "globdoc.hxx"
#include "globdoc.hrc"

/*--------------------------------------------------------------------
    Beschreibung:	Alle Filter registrieren
 --------------------------------------------------------------------*/

// 4.0: {340AC970-E30D-11d0-A53F-00A0249D57B1}
// 4.0:	0x340ac970, 0xe30d, 0x11d0, 0xa5, 0x3f, 0x0, 0xa0, 0x24, 0x9d, 0x57, 0xb1
// 5.0: 0xc20cf9d3, 0x85ae, 0x11d1, 0xaa, 0xb4, 0x0, 0x60, 0x97, 0xda, 0x56, 0x1a
/*N*/ SFX_IMPL_OBJECTFACTORY_LOD(SwGlobalDocShell, SFXOBJECTSHELL_STD_NORMAL|SFXOBJECTSHELL_HASMENU, /*swriter4/GlobalDocument,*/ \
/*N*/ 		SvGlobalName(BF_SO3_SWGLOB_CLASSID) , Sw)

/*N*/ TYPEINIT1(SwGlobalDocShell, SwDocShell);

/*N*/ SwGlobalDocShell::SwGlobalDocShell(SfxObjectCreateMode eMode ) :
/*N*/ 		SwDocShell(eMode)
/*N*/ {
/*N*/ }

/*N*/ SwGlobalDocShell::~SwGlobalDocShell()
/*N*/ {
/*N*/ }

/*N*/ void SwGlobalDocShell::FillClass( SvGlobalName * pClassName,
/*N*/ 								   ULONG * pClipFormat,
/*N*/ 								   String * pAppName,
/*N*/ 								   String * pLongUserName,
/*N*/ 								   String * pUserName,
/*N*/ 								   long nVersion ) const
/*N*/ {
/*N*/ 	SfxInPlaceObject::FillClass(pClassName, pClipFormat, pAppName, pLongUserName,
/*N*/ 								pUserName, nVersion);
/*N*/ 
/*N*/ 	if (nVersion == SOFFICE_FILEFORMAT_40)
/*N*/ 	{
/*?*/ 		*pClassName = SvGlobalName( BF_SO3_SWGLOB_CLASSID_40 );
/*?*/ 		*pClipFormat = SOT_FORMATSTR_ID_STARWRITERGLOB_40;
/*?*/ 		*pAppName = String::CreateFromAscii("StarWriter 4.0/GlobalDocument");
/*?*/ 
/*?*/ 		*pLongUserName = SW_RESSTR(STR_WRITER_GLOBALDOC_FULLTYPE_40);
/*N*/ 	}
/*N*/ 	else if (nVersion == SOFFICE_FILEFORMAT_50)
/*N*/ 	{
/*N*/ 		*pClassName = SvGlobalName( BF_SO3_SWGLOB_CLASSID_50 );
/*N*/ 		*pClipFormat = SOT_FORMATSTR_ID_STARWRITERGLOB_50;
/*N*/ 		*pLongUserName = SW_RESSTR(STR_WRITER_GLOBALDOC_FULLTYPE_50);
/*N*/ 	}
/*N*/ 	else if (nVersion == SOFFICE_FILEFORMAT_60)
/*N*/ 	{
/*N*/ 		*pLongUserName = SW_RESSTR(STR_WRITER_GLOBALDOC_FULLTYPE);

            // for binfilter, we need the FormatIDs to be set. Not setting them
            // has always been an error (!)
            *pClassName = SvGlobalName( BF_SO3_SWGLOB_CLASSID_60 );
            *pClipFormat = SOT_FORMATSTR_ID_STARWRITERGLOB_60;

/*N*/ 	}
/*N*/ 
/*N*/ 	*pUserName = SW_RESSTR(STR_HUMAN_SWGLOBDOC_NAME);
/*N*/ }



