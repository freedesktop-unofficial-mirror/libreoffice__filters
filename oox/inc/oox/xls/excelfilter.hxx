/*************************************************************************
 *
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER.
 *
 * Copyright 2008 by Sun Microsystems, Inc.
 *
 * OpenOffice.org - a multi-platform office productivity suite
 *
 * $RCSfile: excelfilter.hxx,v $
 * $Revision: 1.7 $
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

#ifndef OOX_XLS_EXCELFILTER_HXX
#define OOX_XLS_EXCELFILTER_HXX

#include "oox/core/xmlfilterbase.hxx"
#include "oox/core/binaryfilterbase.hxx"

namespace oox {
namespace xls {

// ============================================================================

class WorkbookHelper;

class ExcelFilter : public ::oox::core::XmlFilterBase
{
public:
    explicit            ExcelFilter(
                            const ::com::sun::star::uno::Reference< ::com::sun::star::lang::XMultiServiceFactory >& rxFactory );
    virtual             ~ExcelFilter();

    virtual bool        importDocument() throw();
    virtual bool        exportDocument() throw();

    virtual const ::oox::drawingml::Theme* getCurrentTheme() const;
    virtual sal_Int32   getSchemeClr( sal_Int32 nColorSchemeToken ) const;

    virtual const ::oox::vml::DrawingPtr getDrawings();
    virtual const ::oox::drawingml::table::TableStyleListPtr getTableStyles();
    virtual ::oox::drawingml::chart::ChartConverter& getChartConverter();

private:
    virtual ::rtl::OUString implGetImplementationName() const;

private:
    WorkbookHelper*     mpHelper;       /// Nonowning pointer to helper base.
};

// ============================================================================

class ExcelBiffFilter : public ::oox::core::BinaryFilterBase
{
public:
    explicit            ExcelBiffFilter(
                            const ::com::sun::star::uno::Reference< ::com::sun::star::lang::XMultiServiceFactory >& rxFactory );
    virtual             ~ExcelBiffFilter();

    virtual bool        importDocument() throw();
    virtual bool        exportDocument() throw();

private:
    virtual ::rtl::OUString implGetImplementationName() const;
};

// ============================================================================

} // namespace xls
} // namespace oox

#endif

