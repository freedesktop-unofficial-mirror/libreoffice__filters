/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: DomainMapperTableHandler.hxx,v $
 *
 *  $Revision: 1.3 $
 *
 *  last change: $Author: os $ $Date: 2006-11-02 12:37:24 $
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
#ifndef INCLUDED_DOMAIN_MAPPER_TABLE_HANDLER_HXX
#define INCLUDED_DOMAIN_MAPPER_TABLE_HANDLER_HXX

#ifndef INCLUDED_TABLE_MANAGER_HXX
#include <doctok/TableManager.hxx>
#endif
#ifndef INCLUDED_DMAPPER_PROPERTYMAP_HXX
#include "PropertyMap.hxx"
#endif

#include <com/sun/star/text/XTextAppendAndConvert.hpp>

namespace dmapper {

typedef ::com::sun::star::text::XTextRange TextRange_t;
typedef ::com::sun::star::uno::Reference< TextRange_t > Handle_t;
typedef ::com::sun::star::uno::Sequence< Handle_t> HandleSequence_t;
typedef boost::shared_ptr<HandleSequence_t> HandleSequencePointer_t;
typedef ::com::sun::star::uno::Sequence< HandleSequence_t> HandleSequence2_t;
typedef boost::shared_ptr<HandleSequence2_t> HandleSequence2Pointer_t;
typedef ::com::sun::star::uno::Sequence< HandleSequence2_t> HandleSequence3_t;
typedef boost::shared_ptr<HandleSequence3_t> HandleSequence3Pointer_t;
typedef ::com::sun::star::text::XTextAppendAndConvert Text_t;
typedef ::com::sun::star::uno::Reference<Text_t> TextReference_t;

typedef ::com::sun::star::beans::PropertyValues PropertyValues_t;
typedef ::com::sun::star::uno::Sequence< PropertyValues_t > PropertyValuesSeq_t;
typedef ::com::sun::star::uno::Sequence< PropertyValuesSeq_t>
PropertyValuesSeq2_t;

class DomainMapperTableHandler : public doctok::TableDataHandler<Handle_t , PropertyMapPtr >
{
    TextReference_t m_xText;
    HandleSequencePointer_t m_pHandleSeq;
    HandleSequence2Pointer_t m_pHandleSeq2;
    HandleSequence3Pointer_t m_pHandleSeq3;
    sal_Int32 m_nHandleIndex;
    sal_Int32 m_nHandle2Index;
    sal_Int32 m_nHandle3Index;

public:
    typedef boost::shared_ptr<DomainMapperTableHandler> Pointer_t;

    DomainMapperTableHandler(TextReference_t xText)
    : m_xText(xText)
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

}

#endif // INCLUDED_DOMAIN_MAPPER_TABLE_HANDLER_HXX
