/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: so2dll.cxx,v $
 *
 *  $Revision: 1.2 $
 *
 *  last change: $Author: vg $ $Date: 2007-10-23 13:49:37 $
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

#ifndef _SYSDEP_HXX
#include <sysdep.hxx>
#endif

#endif

#ifdef WIN
// Statische DLL-Verwaltungs-Variablen
static HINSTANCE hDLLInst = 0;      // HANDLE der DLL

/***************************************************************************
|*    LibMain()
|*
|*    Beschreibung       Initialisierungsfunktion der DLL
***************************************************************************/
extern "C" int CALLBACK LibMain( HINSTANCE hDLL, WORD, WORD nHeap, LPSTR )
{
#ifndef WNT
    if ( nHeap )
        UnlockData( 0 );
#endif

    hDLLInst = hDLL;

    return TRUE;
}

/***************************************************************************
|*    WEP()
|*
|*    Beschreibung      DLL-Deinitialisierung
***************************************************************************/
extern "C" int CALLBACK WEP( int )
{
    return 1;
}

#endif

#ifdef WNT
void ResourceDummy (void )
{

}
#endif

#ifdef OS2

#ifndef _SVWIN_H
#include <tools/svpm.h>
#endif

#ifndef _SYSDEP_HXX
#include <vcl/sysdep.hxx>
#endif

// Statische DLL-Verwaltungs-Variablen
static hDLLInst = 0;      // HANDLE der DLL


/***************************************************************************
|*    LibMain()
|*
|*    Beschreibung       Initialisierungsfunktion der DLL
***************************************************************************/
extern "C" int LibDummy()
{
    return TRUE;
}

/***************************************************************************
|*    WEP()
|*
|*    Beschreibung      DLL-Deinitialisierung
***************************************************************************/
extern "C" int WEPDummy( int )
{
    return 1;
}

#endif

