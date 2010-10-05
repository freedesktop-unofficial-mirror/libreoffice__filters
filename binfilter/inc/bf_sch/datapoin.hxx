/*************************************************************************
 *
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER.
 * 
 * Copyright 2000, 2010 Oracle and/or its affiliates.
 *
 * OpenOffice.org - a multi-platform office productivity suite
 *
 * This file is part of OpenOffice.org.
 *
 * OpenOffice.org is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License version 3
 * only, as published by the Free Software Foundation.
 *
 * OpenOffice.org is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License version 3 for more details
 * (a copy is included in the LICENSE file that accompanied this code).
 *
 * You should have received a copy of the GNU Lesser General Public License
 * version 3 along with OpenOffice.org.  If not, see
 * <http://www.openoffice.org/license.html>
 * for a copy of the LGPLv3 License.
 *
 ************************************************************************/

#ifndef _SCH_DATAPOIN_HXX
#define _SCH_DATAPOIN_HXX

#include <bf_svx/svdobj.hxx>
#include <tools/stream.hxx>
namespace binfilter {

/*************************************************************************
|*
|* Datenpunkt
|*
\************************************************************************/

class SchDataPoint : public SdrObjUserData
{
    short nCol;
    short nRow;

public:
    SchDataPoint();
    SchDataPoint(short nC, short nR);

        virtual SdrObjUserData* Clone(SdrObject *pObj) const;

    virtual void WriteData(SvStream& rOut);
    virtual void ReadData(SvStream& rIn);

    void SetCol(short nC) { nCol = nC; }
    void SetRow(short nR) { nRow = nR; }
    short GetCol() { return nCol; }
    short GetRow() { return nRow; }
};

/*************************************************************************
|*
|* Tool-Funktion fuer Datenpunkt
|*
\************************************************************************/

extern SchDataPoint* GetDataPoint(const SdrObject& rObj);
extern SdrObject* GetObjWithColRow(short nCol, short nRow,
                                   const SdrObjList& rObjList,
                                   ULONG* pIndex = NULL);

} //namespace binfilter
#endif	// _SCH_DATAPOIN_HXX


