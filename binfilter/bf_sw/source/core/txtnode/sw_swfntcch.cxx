/*************************************************************************
 *
 *  $RCSfile: sw_swfntcch.cxx,v $
 *
 *  $Revision: 1.3 $
 *
 *  last change: $Author: hr $ $Date: 2004-08-03 18:01:52 $
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

#ifndef _VIEWSH_HXX
#include <viewsh.hxx>
#endif
#include "swfntcch.hxx"
#include "fmtcol.hxx"
// auto strip #include "swfont.hxx"
namespace binfilter {

// aus atrstck.cxx
extern const BYTE StackPos[];

// globale Variablen, werden in SwFntCch.Hxx bekanntgegeben
// Der FontCache wird in TxtInit.Cxx _TXTINIT erzeugt und in _TXTEXIT geloescht
SwFontCache *pSwFontCache = NULL;

/*************************************************************************
|*
|*	SwFontObj::SwFontObj(), ~SwFontObj()
|*
|*	Ersterstellung		AMA 25. Jun. 95
|*	Letzte Aenderung	AMA 25. Jun. 95
|*
|*************************************************************************/

/*N*/ SwFontObj::SwFontObj( const void *pOwner, ViewShell *pSh ) :
/*N*/ 	SwCacheObj( (void*)pOwner ),
/*N*/ 	aSwFont( &((SwTxtFmtColl *)pOwner)->GetAttrSet(), pSh ? pSh->GetDoc() : 0 )
/*N*/ {
/*N*/ 	aSwFont.GoMagic( pSh, aSwFont.GetActual() );
/*N*/     const SwAttrSet& rAttrSet = ((SwTxtFmtColl *)pOwner)->GetAttrSet();
/*N*/     for (USHORT i = RES_CHRATR_BEGIN; i < RES_CHRATR_END; i++)
/*N*/         pDefaultArray[ StackPos[ i ] ] = &rAttrSet.Get( i, TRUE );
/*N*/ }

/*N*/ SwFontObj::~SwFontObj()
/*N*/ {
/*N*/ }

/*************************************************************************
|*
|*	SwFontAccess::SwFontAccess()
|*
|*	Ersterstellung		AMA 25. Jun. 95
|*	Letzte Aenderung	AMA 25. Jun. 95
|*
|*************************************************************************/

/*N*/ SwFontAccess::SwFontAccess( const void *pOwner, ViewShell *pSh ) :
/*N*/ 	SwCacheAccess( *pSwFontCache, pOwner,
/*N*/ 			(BOOL) ((SwTxtFmtColl*)pOwner)->IsInSwFntCache() ),
/*N*/ 	pShell( pSh )
/*N*/ {
/*N*/ }

/*N*/ SwFontObj *SwFontAccess::Get( )
/*N*/ {
/*N*/ 	return (SwFontObj *) SwCacheAccess::Get( );
/*N*/ }

/*N*/ SwCacheObj *SwFontAccess::NewObj( )
/*N*/ {
/*N*/ 	((SwTxtFmtColl*)pOwner)->SetInSwFntCache( TRUE );
/*N*/ 	return new SwFontObj( pOwner, pShell );
/*N*/ }


}
