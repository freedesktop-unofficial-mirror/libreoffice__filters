/*************************************************************************
 *
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER.
 * 
 * Copyright 2008 by Sun Microsystems, Inc.
 *
 * OpenOffice.org - a multi-platform office productivity suite
 *
 * $RCSfile: DomainMapperTableHandler.hxx,v $
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
#ifndef INCLUDED_DOMAIN_MAPPER_TABLE_HANDLER_HXX
#define INCLUDED_DOMAIN_MAPPER_TABLE_HANDLER_HXX

#include <resourcemodel/TableManager.hxx>
#include "PropertyMap.hxx"

#include <com/sun/star/text/XTextAppendAndConvert.hpp>

namespace writerfilter {
namespace dmapper {

typedef ::com::sun::star::text::XTextRange TextRange_t;
typedef ::com::sun::star::uno::Reference< TextRange_t > Handle_t;
typedef ::com::sun::star::uno::Sequence< Handle_t> CellSequence_t;
typedef boost::shared_ptr<CellSequence_t> CellSequencePointer_t;
typedef ::com::sun::star::uno::Sequence< CellSequence_t > RowSequence_t;
typedef boost::shared_ptr<RowSequence_t> RowSequencePointer_t;
typedef ::com::sun::star::uno::Sequence< RowSequence_t> TableSequence_t;
typedef boost::shared_ptr<TableSequence_t> TableSequencePointer_t;
typedef ::com::sun::star::text::XTextAppendAndConvert Text_t;
typedef ::com::sun::star::uno::Reference<Text_t> TextReference_t;

typedef ::com::sun::star::beans::PropertyValues                     TablePropertyValues_t;
typedef ::com::sun::star::uno::Sequence< TablePropertyValues_t >    RowPropertyValuesSeq_t;
typedef ::com::sun::star::uno::Sequence< RowPropertyValuesSeq_t>    CellPropertyValuesSeq_t;

typedef std::vector<PropertyMapPtr>     PropertyMapVector1;
typedef std::vector<PropertyMapVector1> PropertyMapVector2;

class DomainMapperTableHandler : public TableDataHandler<Handle_t , PropertyMapPtr >
{
    TextReference_t         m_xText;
    CellSequencePointer_t   m_pCellSeq;
    RowSequencePointer_t    m_pRowSeq;
    TableSequencePointer_t  m_pTableSeq;

    // properties
    PropertyMapVector2      m_aCellProperties;
    PropertyMapVector1      m_aRowProperties;
    PropertyMapPtr          m_aTableProperties;
    
    sal_Int32 m_nCellIndex;
    sal_Int32 m_nRowIndex;

public:
    typedef boost::shared_ptr<DomainMapperTableHandler> Pointer_t;

    DomainMapperTableHandler(TextReference_t xText)
    : m_xText(xText),
        m_nCellIndex(0),
        m_nRowIndex(0)
    {
    }
    virtual ~DomainMapperTableHandler() {}

    virtual void startTable(unsigned int nRows, unsigned int nDepth,
                            PropertyMapPtr pProps);
    virtual void endTable();
    virtual void startRow(unsigned int nCells, PropertyMapPtr pProps);
    virtual void endRow();
    virtual void startCell(const Handle_t & start, PropertyMapPtr pProps);
    virtual void endCell(const Handle_t & end);
};

}}

#endif // INCLUDED_DOMAIN_MAPPER_TABLE_HANDLER_HXX
