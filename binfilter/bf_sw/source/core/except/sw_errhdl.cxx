/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: sw_errhdl.cxx,v $
 *
 *  $Revision: 1.6 $
 *
 *  last change: $Author: kz $ $Date: 2007-09-06 12:11:36 $
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
#define _ERRHDL_CXX


#ifdef _MSC_VER
#pragma hdrstop
#endif

#include "stdlib.h"
#ifdef WIN
#include <svwin.h>				// fuer die Goodies der Windows User
#include <dos.h>
#endif

#ifndef _TOOLS_DEBUG_HXX //autogen
#include <tools/debug.hxx>
#endif
#ifndef _SV_SVAPP_HXX //autogen
#include <vcl/svapp.hxx>
#endif
#ifndef _SV_SOUND_HXX //autogen
#include <vcl/sound.hxx>
#endif

#ifndef _SWERROR_H
#include <error.h>				// fuer die defines von ERR_SW6MSG_ ...
#endif
namespace binfilter {

// break into CodeView
#if defined(ZTC) && defined(WIN)
#define CVBREAK 	asm( 0xCC );
#endif
#if defined(MSC) && defined(WIN)
#define CVBREAK 	__asm int 3;
#endif
#ifndef CVBREAK
#define CVBREAK
#endif

BOOL bAssertFail = FALSE;			// ist gerade eine Assertbox oben ?
BOOL bAssert = FALSE;				// TRUE, wenn mal ein ASSERT kam.

/*------------------------------------------------------------------------
    Ausgabe einer Fehlermeldung inkl. Bedingung, Dateiname und Zeilennummer
    wo der Fehler auftrat.
    Die Funktion wird durch das ASSERT Makro gerufen!
    Parameter:
                char	*pError		Fehlermeldung
                char	*pFileName	Filename in dem der Fehler auftrat
                USHORT	nLine		Zeilennummer in dem der Fehler auftrat
------------------------------------------------------------------------*/

/*N*/ void AssertFail( const sal_Char* pError, const sal_Char* pFileName, USHORT nLine )
/*N*/ {
/*N*/ 	CVBREAK;
/*N*/ 	// NOTE4("ASSERT: %s at %d: %s\n", pFileName, nLine, pError);
/*N*/ 	bAssert = TRUE;
/*N*/ 
/*N*/ 	if( !bAssertFail && GetpApp() && GetpApp()->IsInMain() )
/*N*/ 	{
/*N*/ 		bAssertFail = TRUE;
/*N*/ 		ByteString	aErr;
/*N*/ 		aErr = "Assertion failed\n==================\nFILE      :  ";
/*N*/ 		aErr += pFileName;
/*N*/ 		aErr += " at line ";
/*N*/ 		aErr += ByteString::CreateFromInt32( nLine );
/*N*/ 		aErr += "\nERROR :  ";
/*N*/ 		aErr += pError;
/*N*/ 
/*N*/ 		ByteString aTmp( getenv( "SW_NOBEEP" ) );
/*N*/ 		if ( aTmp != "TRUE" )
/*N*/ 			Sound::Beep(SOUND_ERROR);
/*N*/ 
/*N*/ #if defined( UNX ) && !defined( DBG_UTIL )
/*N*/ 		DBG_ERROR( aErr.GetBuffer() ); // DbgErr ist in UNIX-nicht Produkt-Versionen nicht definiert
/*N*/ #else
/*N*/ 		DbgError( aErr.GetBuffer() );
/*N*/ #endif
/*N*/ 		bAssertFail = FALSE;
/*N*/ 	}
/*N*/ 	else
/*N*/ 	{
/*N*/ 		Sound::Beep(SOUND_ERROR);
/*N*/ 		Sound::Beep(SOUND_ERROR);
/*N*/ 		Sound::Beep(SOUND_ERROR);
/*N*/ 		if( !bAssertFail )
/*N*/ #if defined( MAC )
/*N*/ 		if( !bAssertFail )
/*N*/ 			*(short *)1 = 4711; 		// odd address error erzeugen
/*N*/ #endif
/*N*/ 		if( !bAssertFail )
/*N*/ 			*(short *)0 = 4711; 		// UAE ausloesen
/*N*/ 	}
/*N*/ }

/*------------------------------------------------------------------------
    Ausgabe einer Fehlermeldung inkl. Bedingung, Dateiname und Zeilennummer
    wo der Fehler auftrat.
    Die Funktion wird durch das ASSERT Makro gerufen!
    Parameter:
                USHORT	nErrorId	Id fuer Fehlermeldung
                char	*pFileName	Filename in dem der Fehler auftrat
                USHORT	nLine		Zeilennummer in dem der Fehler auftrat
------------------------------------------------------------------------*/

/*N*/ void AssertFail( USHORT nErrorId, const sal_Char* pFileName, USHORT nLine )
/*N*/ {
/*N*/ 	// Umsetzung der ErrorId in eine Fehlermeldung
/*N*/ 	static const sal_Char
/*N*/ 		/* Error Fehlermeldungen zugriffe ausserhalb eines Bereiches */
/*N*/ 		sERR_VAR_IDX[]		= "Op[]",
/*N*/ 		sERR_OUTOFSCOPE[]	= "Zugriff ausserhalb des Bereiches",
/*N*/ 		/* Error Codes fuer Numerierungsregeln */
/*N*/ 		sERR_NUMLEVEL[] 	= "Falscher Num-Level",
/*N*/ 		/* Error Codes fuer TxtNode */
/*N*/ 		sERR_NOHINTS[]		= "Zugriff auf ungueltiges HintsArray",
/*N*/ 		sERR_UNKNOWN[]		= "???";
/*N*/ 
/*N*/ 	static const sal_Char* aErrStrTab[ ERR_SWGMSG_END - ERR_SWGMSG_START +1 ] =
/*N*/ 	{
/*N*/ 		sERR_VAR_IDX, sERR_OUTOFSCOPE, sERR_NUMLEVEL, sERR_NOHINTS
/*N*/ 	};
/*N*/ 
/*N*/ 	const sal_Char* pMsg;
/*N*/ 	if( nErrorId >= ERR_SWGMSG_START && nErrorId < ERR_SWGMSG_END )
/*N*/ 		pMsg = aErrStrTab[ nErrorId - ERR_SWGMSG_START ];
/*N*/ 	else
/*N*/ 		pMsg = sERR_UNKNOWN;
/*N*/ 
/*N*/ 	AssertFail( pMsg, pFileName, nLine );
/*N*/ }


}
