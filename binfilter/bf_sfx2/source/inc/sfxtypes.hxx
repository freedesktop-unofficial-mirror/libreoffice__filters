/*************************************************************************
 *
 *  $RCSfile: sfxtypes.hxx,v $
 *
 *  $Revision: 1.4 $
 *
 *  last change: $Author: hr $ $Date: 2004-08-03 14:59:13 $
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
#ifndef _SFX_SFXTYPES_HXX
#define _SFX_SFXTYPES_HXX

// auto strip #ifndef _DEBUG_HXX //autogen
// auto strip #include <tools/debug.hxx>
// auto strip #endif
// auto strip #ifndef _RC_HXX //autogen
// auto strip #include <tools/rc.hxx>
// auto strip #endif
#ifndef _RCID_H //autogen
#include <tools/rcid.h>
#endif
// auto strip #ifndef _RESID_HXX //autogen
// auto strip #include <tools/resid.hxx>
// auto strip #endif
// auto strip #ifndef _LINK_HXX //autogen
// auto strip #include <tools/link.hxx>
// auto strip #endif
// auto strip #ifndef _APP_HXX //autogen
// auto strip #include <vcl/svapp.hxx>
// auto strip #endif
#ifndef _SV_WRKWIN_HXX
#include <vcl/wrkwin.hxx>
#endif

// auto strip #ifndef _VOS_MUTEX_HXX //autogen
// auto strip #include <vos/mutex.hxx>
// auto strip #endif
class Timer;
namespace binfilter {

#ifndef DELETEZ
#define DELETEZ(pPtr) ( delete pPtr, pPtr = 0 )
#endif

#ifndef DELETEX
#ifdef DBG_UTIL
#define DELETEX(pPtr) ( delete pPtr, (void*&) pPtr = (void*) 0xFFFFFFFF )
#else
#define DELETEX(pPtr) delete pPtr
#endif
#endif

class SfxShell;

#if !defined(_SFX_APPCTOR_CXX) && defined(WNT)
#ifndef _DLL_
#error _DLL_ mal wieder nicht defined => GetpApp() == 0
#endif
#endif

//------------------------------------------------------------------------

// Macro fuer den Call-Profiler unter WinNT
// mit S_CAP kann eine Messung gestarted, mit E_CAP wieder gestoppt werden
#if defined( WNT ) && defined( PROFILE )

extern "C" {
    void StartCAP();
    void StopCAP();
    void DumpCAP();
};

#define S_CAP()   StartCAP();
#define E_CAP()   StopCAP(); DumpCAP();

struct _Capper
{
    _Capper() { S_CAP(); }
    ~_Capper() { E_CAP(); }
};

#define CAP _Capper _aCap_

#else

#define S_CAP()
#define E_CAP()
#define CAP

#endif

#ifdef DBG_UTIL
#ifndef DBG
#define DBG(statement) statement
#endif
#define DBG_OUTF(x) DbgOutf x
#else
#ifndef DBG
#define DBG(statement)
#endif
#define DBG_OUTF(x)
#endif

#define TRIM(s) s.EraseLeadingChars().EraseTrailingChars()

//------------------------------------------------------------------------

String SfxShellIdent_Impl( const SfxShell *pSh );

//------------------------------------------------------------------------

#if defined(DBG_UTIL) && ( defined(WNT) || defined(OS2) )

class SfxStack
{
    static unsigned nLevel;

public:
    SfxStack( const char *pName )
    {
        ++nLevel;
        DbgOutf( "STACK: enter %3d %s", nLevel, pName );
    }
    ~SfxStack()
    {
        DbgOutf( "STACK: leave %3d", nLevel );
        --nLevel;
    }
};

#define SFX_STACK(s) SfxStack aSfxStack_( #s )
#else
#define SFX_STACK(s)
#endif

//------------------------------------------------------------------------

String SearchAndReplace( const String &rSource,
                         const String &rToReplace,
                         const String &rReplacement );

#define SFX_PASSWORD_CODE "_:;*?()/&[&"
String SfxStringEncode( const String &rSource,
                       const char *pKey = SFX_PASSWORD_CODE );
String SfxStringDecode( const String &rSource,
                        const char *pKey = SFX_PASSWORD_CODE );


struct StringList_Impl : private Resource
{

    ResId aResId;

    StringList_Impl( const ResId& rErrIdP,  USHORT nId)
        : Resource( rErrIdP ),aResId(nId){}
    ~StringList_Impl() { FreeResource(); }

    String GetString(){ return String( aResId ); }
    operator BOOL(){return IsAvailableRes(aResId.SetRT(RSC_STRING));}

};

#define SFX_DEL_PTRARR(pArr) 									\
            {                                                   \
                for ( USHORT n = (pArr)->Count(); n--; )        \
                    delete (pArr)->GetObject(n);                \
                DELETEX(pArr);                                  \
            }

class SfxBoolResetter
{
    BOOL&				_rVar;
    BOOL				_bOld;

public:
                        SfxBoolResetter( BOOL &rVar )
                        :	_rVar( rVar ),
                            _bOld( rVar )
                        {}

                        ~SfxBoolResetter()
                        { _rVar = _bOld; }
};

#define GPF() *(int*)0 = 0

}//end of namespace binfilter
#endif // #ifndef _SFX_SFXTYPES_HXX


