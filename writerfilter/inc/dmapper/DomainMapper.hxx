/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: DomainMapper.hxx,v $
 *
 *  $Revision: 1.8 $
 *
 *  last change: $Author: fridrich_strba $ $Date: 2007-03-30 15:35:34 $
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
#ifndef INCLUDED_DOMAINMAPPER_HXX
#define INCLUDED_DOMAINMAPPER_HXX

#ifndef INCLUDED_WRITERFILTERDLLAPI_H
#include <WriterFilterDllApi.hxx>
#endif
#include <doctok/WW8ResourceModel.hxx>
#include <com/sun/star/lang/XComponent.hpp>

namespace com{ namespace sun {namespace star{
    namespace uno{
        class XComponentContext;
    }
}}}
namespace dmapper
{
using namespace std;

class PropertyMap;
class FontTable;
class ListTable;

class DomainMapper_Impl;

// different context types require different sprm handling (e.g. names)
enum SprmType
{
    SPRM_DEFAULT,
    SPRM_LIST
};
class WRITERFILTER_DLLPUBLIC DomainMapper : public doctok::Properties, public doctok::Table,
                    public doctok::BinaryObj, public doctok::Stream
{
    DomainMapper_Impl   *m_pImpl;

public:
    DomainMapper(const ::com::sun::star::uno::Reference< ::com::sun::star::uno::XComponentContext >& xContext,
                                ::com::sun::star::uno::Reference< ::com::sun::star::lang::XComponent > xModel);
    virtual ~DomainMapper();

    // Properties
    virtual void attribute(doctok::Id Name, doctok::Value & val);
    virtual void sprm(doctok::Sprm & sprm);

    // Table
    virtual void entry(int pos, doctok::Reference<Properties>::Pointer_t ref);

    // BinaryObj
    virtual void data(const sal_uInt8* buf, size_t len,
                      doctok::Reference<Properties>::Pointer_t ref);

    // Stream
    virtual void startSectionGroup();
    virtual void endSectionGroup();
    virtual void startParagraphGroup();
    virtual void endParagraphGroup();
    virtual void startCharacterGroup();
    virtual void endCharacterGroup();
    virtual void text(const sal_uInt8 * data, size_t len);
    virtual void utext(const sal_uInt8 * data, size_t len);
    virtual void props(doctok::Reference<Properties>::Pointer_t ref);
    virtual void table(doctok::Id name,
                       doctok::Reference<Table>::Pointer_t ref);
    virtual void substream(doctok::Id name,
                           ::doctok::Reference<Stream>::Pointer_t ref);
    virtual void info(const string & info);

    void sprm( doctok::Sprm& sprm, ::boost::shared_ptr<PropertyMap> pContext, SprmType = SPRM_DEFAULT );
    
private:
    void handleUnderlineType(const sal_Int32 nIntValue, const ::boost::shared_ptr<PropertyMap> pContext);
    void handleParaJustification(const sal_Int32 nIntValue, const ::boost::shared_ptr<PropertyMap> pContext, const bool bExchangeLeftRight);
    bool getColorFromIndex(const sal_Int32 nIndex, sal_Int32 nColor);
    void resolveSprmProps(doctok::Sprm & sprm_);
    sal_Int32 mnHpsMeasure, mnTwipsMeasure;
};

} // namespace dmapper

#endif //
