/*************************************************************************
 *
 *  $RCSfile: sch_objid.cxx,v $
 *
 *  $Revision: 1.3 $
 *
 *  last change: $Author: rt $ $Date: 2004-05-05 16:39:54 $
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

#include "objid.hxx"
#include "glob.hxx"

#include "defines.hxx"

#include <tools/debug.hxx> //STRIP001
namespace binfilter {
/*************************************************************************
|*
|* Objekt-Id ermitteln;
|* Liefert -1, wenn das Objekt keine Id hat
|*
\************************************************************************/

/*N*/ SchObjectId* GetObjectId(const SdrObject& rObj)
/*N*/ {
/*N*/ 	for (USHORT i = 0; i < rObj.GetUserDataCount(); i++)
/*N*/ 	{
/*N*/ 		SdrObjUserData *pData = rObj.GetUserData(i);
/*N*/ 		if (pData && pData->GetId() == SCH_OBJECTID_ID)
/*N*/ 			return (SchObjectId*)pData;
/*N*/ 	}
/*N*/ 
/*N*/ 	return NULL;
/*N*/ }

//STRIP001 UINT16 GetObjectIdNum( const SdrObject& rObj )
//STRIP001 {
//STRIP001     UINT16 nId = CHOBJID_ANY;
//STRIP001     SchObjectId *  pId = GetObjectId( rObj );
//STRIP001     if( pId != NULL )
//STRIP001         nId = pId->GetObjId();
//STRIP001     return nId;
//STRIP001 }

/*************************************************************************
|*
|* Objekt mit Id suchen;
|* liefert NULL, wenn kein Objekt gefunden wurde.
|*
\************************************************************************/

/*N*/ SdrObject* GetObjWithId(UINT16 nObjId, const SdrObjList& rObjList,
/*N*/ 						ULONG* pIndex, SdrIterMode eMode)
/*N*/ {
/*N*/ 	ULONG nIndex = 0;
/*N*/ 
/*N*/ 	SdrObjListIter aIterator(rObjList, eMode);
/*N*/ 	while (aIterator.IsMore())
/*N*/ 	{
/*N*/ 		SdrObject* pObj = aIterator.Next();
/*N*/ 		SchObjectId* pObjId = GetObjectId(*pObj);
/*N*/ 		if (pObjId && pObjId->GetObjId() == nObjId)
/*N*/ 		{
/*N*/ 			if (pIndex)
/*?*/ 				*pIndex = nIndex;
/*N*/ 			return pObj;
/*N*/ 		}
/*N*/ 
/*N*/ 		nIndex++;
/*N*/ 	}
/*N*/ 
/*N*/ 	return NULL;
/*N*/ }

/*************************************************************************
|*
|* Alle Objekt mit Id=nObjId Attributieren,
|*
\************************************************************************/
//STRIP001 void SetAttrWithId(UINT16 nObjId, const SdrObjList& rObjList,
//STRIP001 						const SfxItemSet& rAttr, SdrIterMode eMode)
//STRIP001 {
//STRIP001 	ULONG nIndex = 0;
//STRIP001 
//STRIP001 	SdrObjListIter aIterator(rObjList, eMode);
//STRIP001 	while (aIterator.IsMore())
//STRIP001 	{
//STRIP001 		SdrObject* pObj = aIterator.Next();
//STRIP001 		SchObjectId* pObjId = GetObjectId(*pObj);
//STRIP001 		if (pObjId && pObjId->GetObjId() == nObjId)
//STRIP001 		{
//STRIP001 
//STRIP001 //-/			pObj->NbcSetAttributes(rAttr,FALSE);
//STRIP001 			pObj->SetItemSet(rAttr);
//STRIP001 
//STRIP001 		}
//STRIP001 		nIndex++;
//STRIP001 	}
//STRIP001 }
/*************************************************************************
|*
|* Konstruktor
|*
\************************************************************************/

/*N*/ SchObjectId::SchObjectId() :
/*N*/ 	SdrObjUserData(SchInventor, SCH_OBJECTID_ID, 0),
/*N*/ 	nObjId(0)
/*N*/ {
/*N*/ }

/*************************************************************************
|*
|* Konstruktor
|*
\************************************************************************/

/*N*/ SchObjectId::SchObjectId(UINT16 nId) :
/*N*/ 	SdrObjUserData(SchInventor, SCH_OBJECTID_ID, 0),
/*N*/ 	nObjId(nId)
/*N*/ {
/*N*/ }

/*************************************************************************
|*
|* Kopier-Konstruktor
|*
\************************************************************************/

//STRIP001 SchObjectId::SchObjectId(const SchObjectId& rObjectId) :
//STRIP001 	SdrObjUserData(rObjectId),
//STRIP001 	nObjId(rObjectId.nObjId)
//STRIP001 {
//STRIP001 }

/*************************************************************************
|*
|* Kopie erzeugen
|*
\************************************************************************/

/*N*/ SdrObjUserData* SchObjectId::Clone(SdrObject *pObj) const
/*N*/ {
/*?*/  	DBG_BF_ASSERT(0, "STRIP"); return NULL;//STRIP001 return new SchObjectId(*this);
/*N*/ }

/*************************************************************************
|*
|* Daten in Stream schreiben
|*
\************************************************************************/

/*N*/ void SchObjectId::WriteData(SvStream& rOut)
/*N*/ {
/*N*/ 	SdrObjUserData::WriteData(rOut);
/*N*/ 
/*N*/ 	rOut << nObjId;
/*N*/ }


/*************************************************************************
|*
|* Daten aus Stream lesen
|*
\************************************************************************/

/*N*/ void SchObjectId::ReadData(SvStream& rIn)
/*N*/ {
/*N*/ 	SdrObjUserData::ReadData(rIn);
/*N*/ 
/*N*/ 	rIn >> nObjId;
/*N*/ }

/*N*/ #ifdef DBG_UTIL

// this function is for debugging only
// therefore it is ok to use char* instead of UniString
/*N*/ char* GetCHOBJIDName( const long id )
/*N*/ {
/*N*/ 	switch( id )
/*N*/ 	{
/*?*/ 		case CHOBJID_ANY:						return "CHOBJID_ANY";
/*?*/ 		case CHOBJID_TEXT:						return "CHOBJID_TEXT";
/*?*/ 		case CHOBJID_AREA:						return "CHOBJID_AREA";
/*?*/ 		case CHOBJID_LINE:						return "CHOBJID_LINE";
/*?*/ 		case CHOBJID_DIAGRAM_AREA:				return "CHOBJID_DIAGRAM_AREA";
/*?*/ 		case CHOBJID_TITLE_MAIN:				return "CHOBJID_TITLE_MAIN";
/*?*/ 		case CHOBJID_TITLE_SUB:					return "CHOBJID_TITLE_SUB";
/*?*/ 		case CHOBJID_DIAGRAM:					return "CHOBJID_DIAGRAM";
/*?*/ 		case CHOBJID_DIAGRAM_WALL:				return "CHOBJID_DIAGRAM_WALL";
/*?*/ 		case CHOBJID_DIAGRAM_FLOOR:				return "CHOBJID_DIAGRAM_FLOOR";
/*?*/ 		case CHOBJID_DIAGRAM_TITLE_X_AXIS:		return "CHOBJID_DIAGRAM_TITLE_X_AXIS";
/*?*/ 		case CHOBJID_DIAGRAM_TITLE_Y_AXIS:		return "CHOBJID_DIAGRAM_TITLE_Y_AXIS";
/*N*/ 		case CHOBJID_DIAGRAM_TITLE_Z_AXIS:		return "CHOBJID_DIAGRAM_TITLE_Z_AXIS";
/*?*/ 		case CHOBJID_DIAGRAM_X_AXIS:			return "CHOBJID_DIAGRAM_X_AXIS";
/*?*/ 		case CHOBJID_DIAGRAM_Y_AXIS:			return "CHOBJID_DIAGRAM_Y_AXIS";
/*?*/ 		case CHOBJID_DIAGRAM_Z_AXIS:			return "CHOBJID_DIAGRAM_Z_AXIS";
/*?*/ 		case CHOBJID_DIAGRAM_A_AXIS:			return "CHOBJID_DIAGRAM_A_AXIS";
/*?*/ 		case CHOBJID_DIAGRAM_B_AXIS:			return "CHOBJID_DIAGRAM_B_AXIS";
/*?*/ 		case CHOBJID_DIAGRAM_C_AXIS:			return "CHOBJID_DIAGRAM_C_AXIS";
/*?*/ 		case CHOBJID_DIAGRAM_X_GRID_MAIN:		return "CHOBJID_DIAGRAM_X_GRID_MAIN";
/*?*/ 		case CHOBJID_DIAGRAM_Y_GRID_MAIN:		return "CHOBJID_DIAGRAM_Y_GRID_MAIN";
/*?*/ 		case CHOBJID_DIAGRAM_Z_GRID_MAIN:		return "CHOBJID_DIAGRAM_Z_GRID_MAIN";
/*?*/ 		case CHOBJID_DIAGRAM_Y_GRID_HELP:		return "CHOBJID_DIAGRAM_Y_GRID_HELP";
/*?*/ 		case CHOBJID_DIAGRAM_Z_GRID_HELP:		return "CHOBJID_DIAGRAM_Z_GRID_HELP";
/*?*/ 		case CHOBJID_DIAGRAM_ROWGROUP:			return "CHOBJID_DIAGRAM_ROWGROUP";
/*?*/ 		case CHOBJID_DIAGRAM_ROWS:				return "CHOBJID_DIAGRAM_ROWS";
/*?*/ 		case CHOBJID_DIAGRAM_ROWSLINE:			return "CHOBJID_DIAGRAM_ROWSLINE";
/*?*/ 		case CHOBJID_DIAGRAM_DATA:				return "CHOBJID_DIAGRAM_DATA";
/*?*/ 		case CHOBJID_DIAGRAM_DESCRGROUP:		return "CHOBJID_DIAGRAM_DESCRGROUP";
/*?*/ 		case CHOBJID_DIAGRAM_DESCR_ROW:			return "CHOBJID_DIAGRAM_DESCR_ROW";
/*?*/ 		case CHOBJID_DIAGRAM_DESCR_COL:			return "CHOBJID_DIAGRAM_DESCR_COL";
/*?*/ 		case CHOBJID_DIAGRAM_DESCR_SYMBOL:		return "CHOBJID_DIAGRAM_DESCR_SYMBOL";
/*?*/ 		case CHOBJID_LEGEND:					return "CHOBJID_LEGEND";
/*?*/ 		case CHOBJID_LEGEND_BACK:				return "CHOBJID_LEGEND_BACK";
/*?*/ 		case CHOBJID_LEGEND_SYMBOL_ROW:			return "CHOBJID_LEGEND_SYMBOL_ROW";
/*?*/ 		case CHOBJID_LEGEND_SYMBOL_COL:			return "CHOBJID_LEGEND_SYMBOL_COL";
/*?*/ 		case CHOBJID_DIAGRAM_Z_AXIS_GROUP:		return "CHOBJID_DIAGRAM_Z_AXIS_GROUP";
/*?*/ 		case CHOBJID_DIAGRAM_NET:				return "CHOBJID_DIAGRAM_NET";
/*?*/ 		case CHOBJID_DIAGRAM_AVERAGEVALUE:		return "CHOBJID_DIAGRAM_AVERAGEVALUE";
/*?*/ 		case CHOBJID_DIAGRAM_ERROR:				return "CHOBJID_DIAGRAM_ERROR";
/*?*/ 		case CHOBJID_DIAGRAM_REGRESSION:		return "CHOBJID_DIAGRAM_REGRESSION";
/*?*/ 		case CHOBJID_DIAGRAM_STACKEDGROUP:		return "CHOBJID_DIAGRAM_STACKEDGROUP";
/*?*/ 		case CHOBJID_DIAGRAM_STATISTICS_GROUP:	return "CHOBJID_DIAGRAM_STATISTICS_GROUP";
/*?*/ 		case CHOBJID_DIAGRAM_X_GRID_MAIN_GROUP:	return "CHOBJID_DIAGRAM_X_GRID_MAIN_GROUP";
/*?*/ 		case CHOBJID_DIAGRAM_Y_GRID_MAIN_GROUP:	return "CHOBJID_DIAGRAM_Y_GRID_MAIN_GROUP";
/*?*/ 		case CHOBJID_DIAGRAM_Z_GRID_MAIN_GROUP:	return "CHOBJID_DIAGRAM_Z_GRID_MAIN_GROUP";
/*?*/ 		case CHOBJID_DIAGRAM_X_GRID_HELP_GROUP:	return "CHOBJID_DIAGRAM_X_GRID_HELP_GROUP";
/*?*/ 		case CHOBJID_DIAGRAM_Y_GRID_HELP_GROUP:	return "CHOBJID_DIAGRAM_Y_GRID_HELP_GROUP";
/*?*/ 		case CHOBJID_DIAGRAM_Z_GRID_HELP_GROUP:	return "CHOBJID_DIAGRAM_Z_GRID_HELP_GROUP";
/*?*/ 		case CHOBJID_DIAGRAM_SPECIAL_GROUP:		return "CHOBJID_DIAGRAM_SPECIAL_GROUP";
/*?*/ 		case CHOBJID_DIAGRAM_STOCKLINE_GROUP:	return "CHOBJID_DIAGRAM_STOCKLINE_GROUP";
/*?*/ 		case CHOBJID_DIAGRAM_STOCKLOSS_GROUP:	return "CHOBJID_DIAGRAM_STOCKLOSS_GROUP";
/*?*/ 		case CHOBJID_DIAGRAM_STOCKPLUS_GROUP:	return "CHOBJID_DIAGRAM_STOCKPLUS_GROUP";
/*?*/ 
/*?*/ 		default:
/*?*/ 			return "unknown Id";
/*N*/ 	}
/*N*/ }

/*N*/ #endif	// DBG_UTIL



}
