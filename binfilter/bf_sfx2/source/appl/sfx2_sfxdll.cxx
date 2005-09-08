/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: sfx2_sfxdll.cxx,v $
 *
 *  $Revision: 1.4 $
 *
 *  last change: $Author: rt $ $Date: 2005-09-08 02:29:09 $
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

#ifdef WIN
#ifndef _SVWIN_H
#include <svwin.h>
#endif
#endif

#pragma hdrstop

#ifdef WIN
// auto strip #include "segmentc.hxx"
namespace binfilter {

// Statische DLL-Verwaltungs-Variablen
static HINSTANCE hDLLInst = 0;

SEG_EOFGLOBALS()

//==========================================================================
#pragma SEG_SEGCLASS(DLLINIT_SEG,DLLINITEXIT_CODE)

/*N*/ extern "C" int CALLBACK LibMain( HINSTANCE hDLL, WORD, WORD nHeap, LPSTR )
/*N*/ {
/*N*/ #ifndef WNT
/*N*/ 	if ( nHeap )
/*N*/ 		UnlockData( 0 );
/*N*/ #endif
/*N*/ 
/*N*/ 	hDLLInst = hDLL;
/*N*/ 
/*N*/ 	return TRUE;
/*N*/ }


//--------------------------------------------------------------------------
#pragma SEG_SEGCLASS(DLLEXIT_SEG,DLLINITEXIT_CODE)

/*N*/ extern "C" int CALLBACK WEP( int )
/*N*/ {
/*N*/ 	return 1;
/*N*/ }



//==========================================================================
}
#endif



