/*************************************************************************
 *
 *  $RCSfile: XMLTableShapeResizer.hxx,v $
 *
 *  $Revision: 1.3 $
 *
 *  last change: $Author: hr $ $Date: 2004-08-03 11:24:37 $
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

#ifndef _SC_XMLTABLESHAPERESIZER_HXX
#define _SC_XMLTABLESHAPERESIZER_HXX

#ifndef _COM_SUN_STAR_DRAWING_XSHAPE_HPP_
#include <com/sun/star/drawing/XShape.hpp>
#endif
#ifndef _COM_SUN_STAR_TABLE_CELLADDRESS_HPP_
#include <com/sun/star/table/CellAddress.hpp>
#endif
// auto strip #ifndef _COM_SUN_STAR_SHEET_XSPREADSHEET_HPP_
// auto strip #include <com/sun/star/sheet/XSpreadsheet.hpp>
// auto strip #endif
#ifndef __SGI_STL_LIST
#include <list>
#endif
class Rectangle;
namespace binfilter {

class ScXMLImport;
class ScChartListenerCollection;
class ScDocument;

struct ScMyToResizeShape
{
    ::com::sun::star::uno::Reference < ::com::sun::star::drawing::XShape> xShape;
    ::rtl::OUString* pRangeList;
    ::com::sun::star::table::CellAddress	aEndCell;
    ::com::sun::star::table::CellAddress	aStartCell;
    sal_Int32 nEndX;
    sal_Int32 nEndY;

    ScMyToResizeShape() : pRangeList(NULL) {}
};

typedef std::list<ScMyToResizeShape> ScMyToResizeShapes;

class ScMyShapeResizer
{
    ScXMLImport&				rImport;
    ScMyToResizeShapes			aShapes;
    ScChartListenerCollection*	pCollection;

    sal_Bool IsOLE(::com::sun::star::uno::Reference< ::com::sun::star::drawing::XShape >& rShape) const;
    void CreateChartListener(ScDocument* pDoc,
        const ::rtl::OUString& rName,
        const ::rtl::OUString* pRangeList);
    void GetNewShapeSizePos(ScDocument* pDoc, const Rectangle& rStartRect, 
                            const ::com::sun::star::table::CellAddress& rEndCell, 
                            ::com::sun::star::awt::Point& rPoint, ::com::sun::star::awt::Size& rSize,
                            sal_Int32& rEndX, sal_Int32& rEndY) const;
public:
    ScMyShapeResizer(ScXMLImport& rImport);
    ~ScMyShapeResizer();

    void	AddShape(::com::sun::star::uno::Reference < ::com::sun::star::drawing::XShape>& rShape,
                    ::rtl::OUString* pRangeList,
                    ::com::sun::star::table::CellAddress& rStartAddress,
                    ::com::sun::star::table::CellAddress& rEndAddress,
                    sal_Int32 nEndX, sal_Int32 nEndY);
    void	ResizeShapes();
};

} //namespace binfilter
#endif
