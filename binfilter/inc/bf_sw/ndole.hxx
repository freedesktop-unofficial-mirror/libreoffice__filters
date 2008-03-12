/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: ndole.hxx,v $
 *
 *  $Revision: 1.6 $
 *
 *  last change: $Author: rt $ $Date: 2008-03-12 13:44:42 $
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
#ifndef _NDOLE_HXX
#define _NDOLE_HXX

#ifndef _NDNOTXT_HXX
#include <ndnotxt.hxx>
#endif

namespace binfilter {

class SvInPlaceObjectRef; 
class SvInPlaceObject; 

class SwGrfFmtColl;
class SwDoc;
class SwOLENode;
class SwOLELink;
class SwOLELRUCache;


class SwOLEObj
{
    friend class SwOLENode;

    static SwOLELRUCache* pOLELRU_Cache;

    const SwOLENode* pOLENd;

    //Entweder Ref oder Name sind bekannt, wenn nur der Name bekannt ist, wird
    //dir Ref bei Anforderung durch GetOleRef() vom Sfx besorgt.
    SvInPlaceObjectRef *pOLERef;	//new/delete, damit so2.hxx wegfaellt.
    String aName;

    SwOLEObj( const SwOLEObj& rObj );	//nicht erlaubt.
    SwOLEObj();

    void SetNode( SwOLENode* pNode );

public:
    SwOLEObj( SvInPlaceObject *pObj );
    SwOLEObj( const String &rName );
    ~SwOLEObj();

     BOOL RemovedFromLRU();

#ifndef _FESHVIEW_ONLY_INLINE_NEEDED
    SvInPlaceObjectRef GetOleRef();
    const String &GetName() const { return aName; }

    BOOL IsOleRef() const;	//Damit das Objekt nicht unnoetig geladen werden muss.
#endif
};


// --------------------
// SwOLENode
// --------------------

struct SwPersistentOleData;

class SwOLENode: public SwNoTxtNode
{
    friend class SwNodes;
    SwOLEObj aOLEObj;
    SwPersistentOleData* pSavedData;
    String sChartTblName;		// bei Chart Objecten: Name der ref. Tabelle
    BOOL   bOLESizeInvalid;		//Soll beim SwDoc::PrtOLENotify beruecksichtig
                                //werden (zum Beispiel kopiert). Ist nicht
                                //Persistent.

    SwOLENode(	const SwNodeIndex &rWhere,
                SvInPlaceObject *,
                SwGrfFmtColl *pGrfColl,
                SwAttrSet* pAutoAttr = 0 );

    SwOLENode(	const SwNodeIndex &rWhere,
                const String &rName,
                SwGrfFmtColl *pGrfColl,
                SwAttrSet* pAutoAttr = 0 );

    // aOLEObj besitzt einen privaten Copy-CTOR, wir brauchen auch einen:
    SwOLENode( const SwOLENode & );

public:
    const SwOLEObj& GetOLEObj() const { return aOLEObj; }
          SwOLEObj& GetOLEObj()		  { return aOLEObj; }

    virtual SwCntntNode *SplitNode( const SwPosition & );
        // steht in ndcopy.cxx
    virtual SwCntntNode* MakeCopy( SwDoc*, const SwNodeIndex& ) const;

    virtual Size GetTwipSize() const;


    BOOL IsInGlobalDocSection() const;
    BOOL IsOLEObjectDeleted() const;

    BOOL IsOLESizeInvalid() const	{ return bOLESizeInvalid; }
    void SetOLESizeInvalid( BOOL b ){ bOLESizeInvalid = b; }

#ifndef _FESHVIEW_ONLY_INLINE_NEEDED
    const String& GetChartTblName() const 		{ return sChartTblName; }
    void SetChartTblName( const String& rNm ) 	{ sChartTblName = rNm; }
#endif
};


// Inline Metoden aus Node.hxx - erst hier ist der TxtNode bekannt !!
#if !(defined(MACOSX) && ( __GNUC__ < 3 ))
// GrP moved to gcc_outl.cxx; revisit with gcc3
inline SwOLENode *SwNode::GetOLENode()
{
     return ND_OLENODE == nNodeType ? (SwOLENode*)this : 0;
}
inline const SwOLENode *SwNode::GetOLENode() const
{
     return ND_OLENODE == nNodeType ? (const SwOLENode*)this : 0;
}
#endif

} //namespace binfilter
#endif	// _NDOLE_HXX

