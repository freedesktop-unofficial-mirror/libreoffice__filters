/*************************************************************************
 *
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER.
 * 
 * Copyright 2008 by Sun Microsystems, Inc.
 *
 * OpenOffice.org - a multi-platform office productivity suite
 *
 * $RCSfile: StyleSheetTable.hxx,v $
 * $Revision: 1.16 $
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
#ifndef INCLUDED_STYLESHEETTABLE_HXX
#define INCLUDED_STYLESHEETTABLE_HXX

#include <WriterFilterDllApi.hxx>
#include <dmapper/DomainMapper.hxx>
#include <com/sun/star/lang/XComponent.hpp>
#include <PropertyMap.hxx>
#include <FontTable.hxx>
#include <resourcemodel/WW8ResourceModel.hxx>

namespace com{ namespace sun { namespace star { namespace text{
    class XTextDocument;
}}}}

namespace writerfilter {
namespace dmapper
{


enum StyleType
{
    STYLE_TYPE_UNKNOWN,
    STYLE_TYPE_PARA,
    STYLE_TYPE_CHAR,
    STYLE_TYPE_TABLE,
    STYLE_LIST
};

struct StyleSheetTable_Impl;
struct StyleSheetEntry
{
    ::rtl::OUString sStyleIdentifierI;
    ::rtl::OUString sStyleIdentifierD;
    bool            bIsDefaultStyle;
    bool            bInvalidHeight;
    bool            bHasUPE; //universal property expansion
    StyleType       nStyleTypeCode; //sgc
    ::rtl::OUString sBaseStyleIdentifier;
    ::rtl::OUString sNextStyleIdentifier;
    ::rtl::OUString sStyleName;
    ::rtl::OUString sStyleName1;
    PropertyMapPtr  pProperties;
    ::rtl::OUString sConvertedStyleName;
    StyleSheetEntry();
};
class DomainMapper;
class WRITERFILTER_DLLPRIVATE StyleSheetTable :
        public Properties,
        public Table
{
    StyleSheetTable_Impl   *m_pImpl;

public:
    StyleSheetTable( DomainMapper& rDMapper,
                        ::com::sun::star::uno::Reference< ::com::sun::star::text::XTextDocument> xTextDocument );
    virtual ~StyleSheetTable();

    // Properties
    virtual void attribute(Id Name, Value & val);
    virtual void sprm(Sprm & sprm);

    // Table
    virtual void entry(int pos, writerfilter::Reference<Properties>::Pointer_t ref);

    void ApplyStyleSheets( FontTablePtr rFontTable );
    const StyleSheetEntry* FindStyleSheetByISTD(const ::rtl::OUString& sIndex);
    const StyleSheetEntry* FindStyleSheetByStyleName(const ::rtl::OUString& rIndex);
    const StyleSheetEntry* FindStyleSheetByConvertedStyleName(const ::rtl::OUString& rIndex);
    // returns the parent of the one with the given name - if empty the parent of the current style sheet is returned
    const StyleSheetEntry* FindParentStyleSheet(::rtl::OUString sBaseStyle);

    ::rtl::OUString ConvertStyleName( const ::rtl::OUString& rWWName, bool bExtendedSearch = false );
    ::rtl::OUString GetStyleIdFromIndex(const sal_uInt32 sti);

    ::rtl::OUString getOrCreateCharStyle( PropertyValueVector_t& rCharProperties );

private:
    void resolveAttributeProperties(Value & val);
    void resolveSprmProps(Sprm & sprm_);
    void applyDefaults(bool bParaProperties); 
};
typedef boost::shared_ptr< StyleSheetTable >    StyleSheetTablePtr;

}}

#endif //
