/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: inidef.hxx,v $
 *
 *  $Revision: 1.2 $
 *
 *  last change: $Author: rt $ $Date: 2008-03-12 12:12:03 $
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

#ifndef _SFXINIDEF_HXX
#define _SFXINIDEF_HXX

#ifndef _INIMGR_HXX
#include <iniman.hxx>
#endif

namespace binfilter
{

class SfxIniEntry;
class SfxIniDefaulterList;
class SfxIniDefaultManager;
}

#if _SOLAR__PRIVATE
#include <bf_svtools/svarray.hxx>

namespace binfilter
{
class SfxIniDefaulter;
SV_DECL_PTRARR( SfxIniDefaulterList, SfxIniDefaulter*, 0, 2 );
}
#endif

namespace binfilter
{

//========================================================================

class SfxIniDefaulter

/*	[Beschreibung]

    Instanzen dieser Klasse k"onnen (f"ur die Laufzeit eines Moduls, z.B.
    einer DLL-Nutzung oder einer Applikation) angelegt werden, um Defaults
    f"ur eine Anzahl von ini-Eintr"agen zu liefern. Diese Defaults werden
    erfragt, wenn ein <SfxIniManager> einen Eintrag nicht in den ini-Files
    finden kann.

    Defaults verschiedener <SfxIniDefaulter>-Instanzen d"urfen sich nicht
    unterscheiden, da die Reihenfolge der Abarbeitung nicht definiert ist.

    Die Instanzen brauchen nicht zerst"ort zu werden, au\ser wenn der
    dazugeh"orige Code entladen wird (load-on-demand DLLs). Sonst geschieht
    dies automatisch beim Zerst"oren des <SfxIniDefaultManager>.
*/

{
    SfxIniDefaultManager*	_pManager;

public:
                            SfxIniDefaulter( SfxIniDefaultManager *pManager );
                            ~SfxIniDefaulter();

    virtual BOOL			QueryDefault( String &aValue,
                                          const SfxIniEntry &rEntry ) = 0;
};

//========================================================================

class SfxIniDefaultManager

/*	[Beschreibung]

    Genau eine Instanz dieser Klasse mu\s in jeder Application-Subklasse,
    die diesen Mechanismus nutzen m"ochte, in deren Ctor angelegt werden
    und sollte in deren Dtor zerst"ort werden.
*/

{
    SfxIniDefaulterList*	_pList;

public:
                            SfxIniDefaultManager();
                            ~SfxIniDefaultManager();

#if _SOLAR__PRIVATE
    void					Insert( SfxIniDefaulter *pDefaulter )
                            { _pList->C40_INSERT( SfxIniDefaulter, pDefaulter, _pList->Count() ); }
    void					Remove( SfxIniDefaulter *pDefaulter )
                            { _pList->Remove( _pList->C40_GETPOS( SfxIniDefaulter, pDefaulter ) ); }
    BOOL					QueryDefault( String &aValue,
                                          const SfxIniEntry &rEntry );
#endif
};

//========================================================================

class SfxIniEntry

/*	[Beschreibung]

    Instanzen dieser Klasse beschreiben einen Eintrag eines Ini-Files,
    um mit der Klasse <SfxIniDefaulter> erfragt werden zu k"onnen, falls
    der <SfxIniManager> einen Eintrag nicht in den Ini-Files auffindet.
*/

{
friend class SfxIniManager;

    const String&   		_aGroup;
    const String&			_aKey;
    SfxIniGroup 			_eGroup;
    SfxIniKey				_eKey;
    USHORT					_nIndex;

private:
                            SfxIniEntry( const String&  aGroup,
                                         const String&	aKey,
                                         SfxIniGroup	eGroup,
                                         SfxIniKey		eKey,
                                         USHORT		 	nIndex );
                            SfxIniEntry( const SfxIniEntry & ); // n.i.
    SfxIniEntry&			operator=( const SfxIniEntry & ); // n.i.

public:
    const String&			GetGroupName() const { return _aGroup; }
    SfxIniGroup 			GetGroup() const { return _eGroup; }
    const String&			GetKeyName() const { return _aKey; }
    SfxIniKey				GetKey() const { return _eKey; }
    USHORT 					GetIndex() const { return _nIndex; }
};

}

#endif

