/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: linkmgr.hxx,v $
 *
 *  $Revision: 1.2 $
 *
 *  last change: $Author: vg $ $Date: 2007-10-23 14:25:26 $
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
#ifndef _LINKMGR_HXX
#define _LINKMGR_HXX

#ifndef _LINKSRC_HXX
#include <bf_so3/linksrc.hxx>
#endif
#ifndef _TOOLS_STRING_HXX
#include <tools/string.hxx>
#endif
#ifndef _SVARRAY_HXX
#include <svtools/svarray.hxx>
#endif

#ifndef INCLUDED_SO3DLLAPI_H
#include "bf_so3/so3dllapi.h"
#endif

class SvPersist;

namespace so3
{
class SvBaseLink;
class SvBaseLinkRef;

typedef SvBaseLinkRef* SvBaseLinkRefPtr;
SV_DECL_PTRARR( SvBaseLinks, SvBaseLinkRefPtr, 1, 1 )

typedef SvLinkSource* SvLinkSourcePtr;
SV_DECL_PTRARR( SvLinkSources, SvLinkSourcePtr, 1, 1 )

class SO3_DLLPUBLIC SvLinkManager
{
private:
    SvBaseLinks		aLinkTbl;
    SvLinkSources    aServerTbl;
    SvPersist	    *pPersist; // LinkMgr muss vor SvPersist freigegeben werden
protected:
    BOOL 		InsertLink( SvBaseLink* pLink, USHORT nObjType, USHORT nUpdateType,
                            const String* pName = 0 );
public:
                SvLinkManager();
                virtual ~SvLinkManager();

    SvPersist*	GetPersist() const 				{ return pPersist; }
    void        SetPersist( SvPersist * p ) 	{ pPersist = p; }

    void		Remove( SvBaseLink *pLink );
    void		Remove( USHORT nPos, USHORT nCnt = 1 );
    BOOL		Insert( SvBaseLink* pLink );

                // den Link mit einem SvLinkSource verbinden und in die Liste eintragen
    BOOL 		InsertDDELink( SvBaseLink*,
                        const String& rServer,
                        const String& rTopic,
                        const String& rItem );

                // falls am Link schon alles eingestellt ist !
    BOOL 		InsertDDELink( SvBaseLink* );

                // erfrage die Strings fuer den Dialog
    virtual BOOL GetDisplayNames( const SvBaseLink *,
                                    String* pType,
                                    String* pFile = 0,
                                    String* pLink = 0,
                                    String* pFilter = 0 ) const;

    virtual SvLinkSourceRef CreateObj( SvBaseLink * );

    void 		UpdateAllLinks( BOOL bCallErrHdl,
                                BOOL bUpdateGrfLinks );

                // Liste aller Links erfragen (z.B. fuer Verknuepfungs-Dialog)
    const 		SvBaseLinks& GetLinks() const { return aLinkTbl; }

    // ----------------- Serverseitige Verwaltung --------------------

                // Liste der zu serviereden Links erfragen
    const SvLinkSources& GetServers() const { return aServerTbl; }
                // einen zu servierenden Link eintragen/loeschen
    BOOL 		InsertServer( SvLinkSource* rObj );
    void 		RemoveServer( SvLinkSource* rObj );
    void 		RemoveServer( USHORT nPos, USHORT nCnt = 1 )
                {	aServerTbl.Remove( nPos, nCnt ); }

private:
                // diese Methoden gibts nicht!
    SO3_DLLPRIVATE 			SvLinkManager( const SvLinkManager& );
    SO3_DLLPRIVATE 			SvLinkManager& operator=( const SvLinkManager& );
};

// Trenner im LinkName fuer die DDE-/File-/Grafik- Links
// (nur wer es braucht, um einen SvLinkName zusammenzubasteln)
const sal_Char cTokenSeperator = '\xff';

// erzeuge einen String fuer den SvLinkName. Fuer
// - DDE die ersten 3 Strings, (Server, Topic, Item)
// - File-/Grf-LinkNms die letzen 3 Strings (FileName, Bereich, Filter)
void SO3_DLLPUBLIC MakeLnkName( String& rName,
                 const String* pType,		// kann auch 0 sein !!
                 const String& rFile,
                 const String& rLink,
                 const String* pFilter = 0 );

}

#endif

