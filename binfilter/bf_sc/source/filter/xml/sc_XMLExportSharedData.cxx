/*************************************************************************
 *
 *  $RCSfile: sc_XMLExportSharedData.cxx,v $
 *
 *  $Revision: 1.1.1.1 $
 *
 *  last change: $Author: hjs $ $Date: 2003-10-01 12:18:07 $
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

#ifdef PCH
#include "filt_pch.hxx"
#endif

#pragma hdrstop

// INCLUDE ---------------------------------------------------------------
#ifndef SC_XMLEXPORTSHAREDDATA_HXX
#include "XMLExportSharedData.hxx"
#endif
#ifndef _SC_XMLEXPORTITERATOR_HXX
#include "XMLExportIterator.hxx"
#endif

#ifndef _TOOLS_DEBUG_HXX
#include <tools/debug.hxx>
#endif

using namespace com::sun::star;

ScMySharedData::ScMySharedData(const sal_Int32 nTempTableCount) :
    nLastColumns(nTempTableCount, 0),
    nLastRows(nTempTableCount, 0),
    pTableShapes(NULL),
    pDrawPages(NULL),
    pShapesContainer(NULL),
    pDetectiveObjContainer(NULL),
    nTableCount(nTempTableCount)
{
    pDetectiveObjContainer = new ScMyDetectiveObjContainer();
}

ScMySharedData::~ScMySharedData()
{
    if (pShapesContainer)
        delete pShapesContainer;
    if (pTableShapes)
        delete pTableShapes;
    if (pDrawPages)
        delete pDrawPages;
    if (pDetectiveObjContainer)
        delete pDetectiveObjContainer;
}

void ScMySharedData::SetLastColumn(const sal_Int32 nTable, const sal_Int32 nCol)
{
    if(nCol > nLastColumns[nTable]) nLastColumns[nTable] = nCol;
}

sal_Int32 ScMySharedData::GetLastColumn(const sal_Int32 nTable)
{
    return nLastColumns[nTable];
}

void ScMySharedData::SetLastRow(const sal_Int32 nTable, const sal_Int32 nRow)
{
    if(nRow > nLastRows[nTable]) nLastRows[nTable] = nRow;
}

sal_Int32 ScMySharedData::GetLastRow(const sal_Int32 nTable)
{
    return nLastRows[nTable];
}

void ScMySharedData::AddDrawPage(const ScMyDrawPage& aDrawPage, const sal_Int32 nTable)
{
    if (!pDrawPages)
        pDrawPages = new ScMyDrawPages(nTableCount, ScMyDrawPage());
    (*pDrawPages)[nTable] = aDrawPage;
}

void ScMySharedData::SetDrawPageHasForms(const sal_Int32 nTable, sal_Bool bHasForms)
{
    DBG_ASSERT(pDrawPages, "DrawPages not collected");
    if (pDrawPages)
        (*pDrawPages)[nTable].bHasForms = bHasForms;
}

uno::Reference<drawing::XDrawPage> ScMySharedData::GetDrawPage(const sal_Int32 nTable)
{
    DBG_ASSERT(pDrawPages, "DrawPages not collected");
    if (pDrawPages)
        return (*pDrawPages)[nTable].xDrawPage;
    else
        return uno::Reference<drawing::XDrawPage>();
}

sal_Bool ScMySharedData::HasForm(const sal_Int32 nTable, uno::Reference<drawing::XDrawPage>& xDrawPage)
{
    sal_Bool bResult(sal_False);
    if (pDrawPages)
    {
        if ((*pDrawPages)[nTable].bHasForms)
        {
            bResult = sal_True;
            xDrawPage = (*pDrawPages)[nTable].xDrawPage;
        }
    }
    return bResult;
}

void ScMySharedData::AddNewShape(const ScMyShape& aMyShape)
{
    if (!pShapesContainer)
        pShapesContainer = new ScMyShapesContainer();
    pShapesContainer->AddNewShape(aMyShape);
}

void ScMySharedData::SortShapesContainer()
{
    if (pShapesContainer)
        pShapesContainer->Sort();
}

sal_Bool ScMySharedData::HasShapes()
{
    return ((pShapesContainer && pShapesContainer->HasShapes()) ||
            (pTableShapes && !pTableShapes->empty()));
}

void ScMySharedData::AddTableShape(const sal_Int32 nTable, const uno::Reference<drawing::XShape>& xShape)
{
    if (!pTableShapes)
        pTableShapes = new ScMyTableShapes(nTableCount);
    (*pTableShapes)[nTable].push_back(xShape);
}
