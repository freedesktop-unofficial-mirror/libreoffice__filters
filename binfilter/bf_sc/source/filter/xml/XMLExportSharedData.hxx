/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: XMLExportSharedData.hxx,v $
 *
 *  $Revision: 1.3 $
 *
 *  last change: $Author: rt $ $Date: 2005-09-07 18:17:03 $
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

#ifndef SC_XMLEXPORTSHAREDDATA_HXX
#define SC_XMLEXPORTSHAREDDATA_HXX

#ifndef _COM_SUN_STAR_DRAWING_XDRAWPAGE_HPP_
#include <com/sun/star/drawing/XDrawPage.hpp>
#endif

#ifndef __SGI_STL_VECTOR
#include <vector>
#endif
#ifndef __SGI_STL_LIST
#include <list>
#endif
namespace binfilter {

struct ScMyDrawPage
{
    ::com::sun::star::uno::Reference< ::com::sun::star::drawing::XDrawPage> xDrawPage;
    sal_Bool bHasForms : 1;

    ScMyDrawPage() : bHasForms(sal_False) {}
};

typedef std::list< ::com::sun::star::uno::Reference< ::com::sun::star::drawing::XShape> > ScMyTableXShapes;
typedef std::vector<ScMyTableXShapes> ScMyTableShapes;
typedef std::vector<ScMyDrawPage> ScMyDrawPages;

class ScMyShapesContainer;
class ScMyDetectiveObjContainer;
struct ScMyShape;

class ScMySharedData
{
    std::vector<sal_Int32>		nLastColumns;
    std::vector<sal_Int32>		nLastRows;
    ScMyTableShapes*			pTableShapes;
    ScMyDrawPages*				pDrawPages;
    ScMyShapesContainer*		pShapesContainer;
    ScMyDetectiveObjContainer*	pDetectiveObjContainer;
    sal_Int32					nTableCount;
public:
    ScMySharedData(const sal_Int32 nTableCount);
    ~ScMySharedData();

    void SetLastColumn(const sal_Int32 nTable, const sal_Int32 nCol);
    void SetLastRow(const sal_Int32 nTable, const sal_Int32 nRow);
    sal_Int32 GetLastColumn(const sal_Int32 nTable);
    sal_Int32 GetLastRow(const sal_Int32 nTable);
    void AddDrawPage(const ScMyDrawPage& aDrawPage, const sal_Int32 nTable);
    void SetDrawPageHasForms(const sal_Int32 nTable, sal_Bool bHasForms);
    ::com::sun::star::uno::Reference< ::com::sun::star::drawing::XDrawPage> GetDrawPage(const sal_Int32 nTable);
    sal_Bool HasDrawPage() { return pDrawPages != NULL; }
    sal_Bool HasForm(const sal_Int32 nTable, ::com::sun::star::uno::Reference< ::com::sun::star::drawing::XDrawPage>& xDrawPage);
    void AddNewShape(const ScMyShape& aMyShape);
    void SortShapesContainer();
    ScMyShapesContainer* GetShapesContainer() { return pShapesContainer; }
    sal_Bool HasShapes();
    void AddTableShape(const sal_Int32 nTable, const ::com::sun::star::uno::Reference< ::com::sun::star::drawing::XShape>& xShape);
    ScMyTableShapes* GetTableShapes() { return pTableShapes; }
    ScMyDetectiveObjContainer* GetDetectiveObjContainer() { return pDetectiveObjContainer; }
};

} //namespace binfilter
#endif

