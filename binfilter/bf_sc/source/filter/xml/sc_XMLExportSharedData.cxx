/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: sc_XMLExportSharedData.cxx,v $
 *
 *  $Revision: 1.6 $
 *
 *  last change: $Author: kz $ $Date: 2007-09-06 10:55:16 $
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

#ifdef PCH
#endif

#ifdef _MSC_VER
#pragma hdrstop
#endif

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
namespace binfilter {

using namespace ::com::sun::star;

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
}
