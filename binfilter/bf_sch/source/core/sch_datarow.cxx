/*************************************************************************
 *
 *  $RCSfile: sch_datarow.cxx,v $
 *
 *  $Revision: 1.1 $
 *
 *  last change: $Author: aw $ $Date: 2003-10-02 14:56:02 $
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
#include <bf_svx/svditer.hxx>

#include "datarow.hxx"
#include "glob.hxx"
#ifndef _TOOLS_DEBUG_HXX
#include <tools/debug.hxx>
#endif
/*************************************************************************
|*
|* Datenreihen-Index ermitteln
|*
\************************************************************************/

/*N*/ SchDataRow* GetDataRow(const SdrObject& rObj)
/*N*/ {
/*N*/ 	USHORT i=rObj.GetUserDataCount();//#63904 2x Schleife (15%), 50% pData, 18% id
/*N*/ 	while(i--)
/*N*/ 	{
/*N*/ 		SdrObjUserData *pData = rObj.GetUserData(i);
/*N*/ 		if (pData && pData->GetId() == SCH_DATAROW_ID)
/*N*/ 			return (SchDataRow*)pData;
/*N*/ 	}
/*N*/ 
/*N*/ 	return NULL;
/*N*/ }

/*************************************************************************
|*
|* Objekt mit Datenreihen-Index suchen;
|* liefert NULL, wenn kein Objekt gefunden wurde.
|*
\************************************************************************/

/*N*/ SdrObject* GetObjWithRow(short nRow, const SdrObjList& rObjList,
/*N*/ 						 ULONG* pIndex)
/*N*/ {
/*N*/ 	ULONG nIndex = 0;
/*N*/ 
/*N*/ 	SdrObjListIter aIterator(rObjList, IM_FLAT);
/*N*/ 	while (aIterator.IsMore())
/*N*/ 	{
/*N*/ 		SdrObject* pObj = aIterator.Next();
/*N*/ 		SchDataRow* pDataRow = GetDataRow(*pObj);
/*N*/ 		if (pDataRow && pDataRow->GetRow() == nRow)
/*N*/ 		{
/*N*/ 			if (pIndex)
/*N*/ 				*pIndex = nIndex;
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
|* Konstruktor
|*
\************************************************************************/

/*N*/ SchDataRow::SchDataRow() :
/*N*/ 	SdrObjUserData(SchInventor, SCH_DATAROW_ID, 0),
/*N*/ 	nRow(0)
/*N*/ {
/*N*/ }

/*************************************************************************
|*
|* Konstruktor
|*
\************************************************************************/

/*N*/ SchDataRow::SchDataRow(short nR) :
/*N*/ 	SdrObjUserData(SchInventor, SCH_DATAROW_ID, 0),
/*N*/ 	nRow(nR)
/*N*/ {
/*N*/ }

/*************************************************************************
|*
|* Kopier-Konstruktor
|*
\************************************************************************/

//STRIP001 SchDataRow::SchDataRow(const SchDataRow& rDataRow) :
//STRIP001 	SdrObjUserData(rDataRow),
//STRIP001 	nRow(rDataRow.nRow)
//STRIP001 {
//STRIP001 }

/*************************************************************************
|*
|* Kopie erzeugen
|*
\************************************************************************/

/*N*/ SdrObjUserData* SchDataRow::Clone(SdrObject *pObj) const
/*N*/ {
/*?*/  	DBG_ASSERT(0, "STRIP"); return NULL;//STRIP001 return new SchDataRow(*this);
/*N*/ }

/*************************************************************************
|*
|* Daten in Stream schreiben
|*
\************************************************************************/

/*N*/ void SchDataRow::WriteData(SvStream& rOut)
/*N*/ {
/*N*/ 	SdrObjUserData::WriteData(rOut);
/*N*/ 
/*N*/ 	rOut << (INT16)nRow;
/*N*/ }

/*************************************************************************
|*
|* Daten aus Stream lesen
|*
\************************************************************************/

/*N*/ void SchDataRow::ReadData(SvStream& rIn)
/*N*/ {
/*N*/ 	SdrObjUserData::ReadData(rIn);
/*N*/ 
/*N*/ 	INT16 nInt16;
/*N*/ 
/*N*/ 	rIn >> nInt16; nRow = (short)nInt16;
/*N*/ }



