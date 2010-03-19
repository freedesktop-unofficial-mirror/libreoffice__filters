/*************************************************************************
 *
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER.
 *
 * Copyright 2000, 2010 Oracle and/or its affiliates.
 *
 * OpenOffice.org - a multi-platform office productivity suite
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


#ifdef _MSC_VER
#pragma hdrstop
#endif

#ifndef _EEITEM_HXX
#include "eeitem.hxx"
#endif
#ifndef _EEITEMID_HXX
#include "eeitemid.hxx"
#endif





#ifndef _SV_WINDOW_HXX
#include <vcl/window.hxx>
#endif

#include <editdoc.hxx>
namespace binfilter {

#if defined( DBG_UTIL ) || ( OSL_DEBUG_LEVEL > 1 )









/*N*/ BOOL CheckOrderedList( CharAttribArray& rAttribs, BOOL bStart )
/*N*/ {
/*N*/ 	USHORT nPrev = 0;
/*N*/ 	for ( USHORT nAttr = 0; nAttr < rAttribs.Count(); nAttr++ )
/*N*/ 	{
/*N*/ 		EditCharAttrib* pAttr = rAttribs[nAttr];
/*N*/ 		USHORT nCur = bStart ? pAttr->GetStart() : pAttr->GetEnd();
/*N*/ 		if ( nCur < nPrev )
/*N*/ 			return FALSE;
/*N*/ 
/*N*/ 		nPrev = nCur;
/*N*/ 	}
/*N*/ 	return TRUE;
/*N*/ }

#endif

}
