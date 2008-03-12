/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: ximpstyl.hxx,v $
 *
 *  $Revision: 1.3 $
 *
 *  last change: $Author: rt $ $Date: 2008-03-12 10:57:46 $
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

#ifndef _XIMPSTYLE_HXX
#define _XIMPSTYLE_HXX

#ifndef _XMLOFF_XMLICTXT_HXX
#include "xmlictxt.hxx"
#endif

#ifndef _SDXMLIMP_IMPL_HXX
#include "sdxmlimp_impl.hxx"
#endif

#ifndef _XIMPPAGE_HXX
#include "ximppage.hxx"
#endif

#ifndef _XMLOFF_XMLSTYLE_HXX
#include "xmlstyle.hxx"
#endif

#ifndef _COM_SUN_STAR_VIEW_PAPERORIENTATION_HPP_
#include <com/sun/star/view/PaperOrientation.hpp>
#endif
namespace binfilter {

class SvNumberFormatter;
class SvXMLNumFmtHelper;

//////////////////////////////////////////////////////////////////////////////
// special style:style context inside style:page-master context

class SdXMLPageMasterStyleContext: public SvXMLStyleContext
{
    sal_Int32					mnBorderBottom;
    sal_Int32					mnBorderLeft;
    sal_Int32					mnBorderRight;
    sal_Int32					mnBorderTop;
    sal_Int32					mnWidth;
    sal_Int32					mnHeight;
    ::com::sun::star::view::PaperOrientation meOrientation;

    const SdXMLImport& GetSdImport() const { return (const SdXMLImport&)GetImport(); }
    SdXMLImport& GetSdImport() { return (SdXMLImport&)GetImport(); }

public:
    TYPEINFO();

    SdXMLPageMasterStyleContext( 
        SdXMLImport& rImport, 
        sal_uInt16 nPrfx,
        const ::rtl::OUString& rLName, 
        const ::com::sun::star::uno::Reference< ::com::sun::star::xml::sax::XAttributeList >& xAttrList);
    virtual ~SdXMLPageMasterStyleContext();

    sal_Int32 GetBorderBottom() const { return mnBorderBottom; }
    sal_Int32 GetBorderLeft() const { return mnBorderLeft; }
    sal_Int32 GetBorderRight() const { return mnBorderRight; }
    sal_Int32 GetBorderTop() const { return mnBorderTop; }
    sal_Int32 GetWidth() const { return mnWidth; }
    sal_Int32 GetHeight() const { return mnHeight; }
    ::com::sun::star::view::PaperOrientation GetOrientation() const { return meOrientation; }
};

//////////////////////////////////////////////////////////////////////////////
// style:page-master context

class SdXMLPageMasterContext: public SvXMLStyleContext
{
    ::rtl::OUString				msName;
    SdXMLPageMasterStyleContext*mpPageMasterStyle;

    const SdXMLImport& GetSdImport() const { return (const SdXMLImport&)GetImport(); }
    SdXMLImport& GetSdImport() { return (SdXMLImport&)GetImport(); }

public:
    TYPEINFO();

    SdXMLPageMasterContext( 
        SdXMLImport& rImport, 
        sal_uInt16 nPrfx,
        const ::rtl::OUString& rLName, 
        const ::com::sun::star::uno::Reference< ::com::sun::star::xml::sax::XAttributeList >& xAttrList);
    virtual ~SdXMLPageMasterContext();

    virtual SvXMLImportContext *CreateChildContext( 
        sal_uInt16 nPrefix, const ::rtl::OUString& rLocalName,
        const ::com::sun::star::uno::Reference< ::com::sun::star::xml::sax::XAttributeList >& xAttrList );

    const ::rtl::OUString& GetName() const { return msName; }
    const SdXMLPageMasterStyleContext* GetPageMasterStyle() const { return mpPageMasterStyle; }
};

//////////////////////////////////////////////////////////////////////////////
// style:masterpage context

class SdXMLMasterPageContext: public SdXMLGenericPageContext
{
    ::rtl::OUString				msPageMasterName;
    ::rtl::OUString				msName;
    ::rtl::OUString				msStyleName;

public:
    TYPEINFO();

    SdXMLMasterPageContext( 
        SdXMLImport& rImport, 
        sal_uInt16 nPrfx,
        const ::rtl::OUString& rLName, 
        const ::com::sun::star::uno::Reference< ::com::sun::star::xml::sax::XAttributeList >& xAttrList,
        ::com::sun::star::uno::Reference< ::com::sun::star::drawing::XShapes >& rShapes);
    virtual ~SdXMLMasterPageContext();

    virtual SvXMLImportContext *CreateChildContext( 
        sal_uInt16 nPrefix, const ::rtl::OUString& rLocalName,
        const ::com::sun::star::uno::Reference< ::com::sun::star::xml::sax::XAttributeList >& xAttrList );

    virtual void EndElement();

    const ::rtl::OUString& GetPageMasterName() const { return msPageMasterName; }
    const ::rtl::OUString& GetName() const { return msName; }
};
DECLARE_LIST(ImpMasterPageList, SdXMLMasterPageContext*)//STRIP008 ;

//////////////////////////////////////////////////////////////////////////////
// presentation:placeholder context

class SdXMLPresentationPlaceholderContext: public SvXMLImportContext
{
    ::rtl::OUString				msName;
    sal_Int32					mnX;
    sal_Int32					mnY;
    sal_Int32					mnWidth;
    sal_Int32					mnHeight;

    const SdXMLImport& GetSdImport() const { return (const SdXMLImport&)GetImport(); }
    SdXMLImport& GetSdImport() { return (SdXMLImport&)GetImport(); }

public:
    SdXMLPresentationPlaceholderContext( 
        SdXMLImport& rImport, 
        sal_uInt16 nPrfx,
        const ::rtl::OUString& rLName, 
        const ::com::sun::star::uno::Reference< ::com::sun::star::xml::sax::XAttributeList >& xAttrList);
    virtual ~SdXMLPresentationPlaceholderContext();

    const ::rtl::OUString& GetName() const { return msName; }
    sal_Int32 GetX() const { return mnX; }
    sal_Int32 GetY() const { return mnY; }
    sal_Int32 GetWidth() const { return mnWidth; }
    sal_Int32 GetHeight() const { return mnHeight; }
};
DECLARE_LIST(ImpPlaceholderList, SdXMLPresentationPlaceholderContext*)//STRIP008 ;

//////////////////////////////////////////////////////////////////////////////
// style:presentation-page-layout context

class SdXMLPresentationPageLayoutContext: public SvXMLStyleContext
{
    ::rtl::OUString				msName;
    ImpPlaceholderList			maList;
    sal_uInt16					mnTypeId;

    const SdXMLImport& GetSdImport() const { return (const SdXMLImport&)GetImport(); }
    SdXMLImport& GetSdImport() { return (SdXMLImport&)GetImport(); }

public:
    TYPEINFO();

    SdXMLPresentationPageLayoutContext(
        SdXMLImport& rImport, 
        sal_uInt16 nPrfx, 
        const ::rtl::OUString& rLName, 
        const ::com::sun::star::uno::Reference< ::com::sun::star::xml::sax::XAttributeList >& xAttrList);
    virtual ~SdXMLPresentationPageLayoutContext();

    virtual SvXMLImportContext *CreateChildContext( 
        sal_uInt16 nPrefix, const ::rtl::OUString& rLocalName,
        const ::com::sun::star::uno::Reference< ::com::sun::star::xml::sax::XAttributeList >& xAttrList );

    virtual void EndElement();
    sal_uInt16 GetTypeId() const { return mnTypeId; }
};

//////////////////////////////////////////////////////////////////////////////
// office:styles context

class SdXMLStylesContext : public SvXMLStylesContext
{
    UniReference< SvXMLImportPropertyMapper > xPresImpPropMapper;
    sal_Bool					mbIsAutoStyle;
    SvXMLNumFmtHelper*			mpNumFmtHelper;
    SvNumberFormatter*			mpNumFormatter;

    const SdXMLImport& GetSdImport() const { return (const SdXMLImport&)GetImport(); }
    SdXMLImport& GetSdImport() { return (SdXMLImport&)GetImport(); }

    void ImpSetGraphicStyles() const;
    void ImpSetGraphicStyles( ::com::sun::star::uno::Reference< ::com::sun::star::container::XNameAccess >& xPageStyles, 
        sal_uInt16 nFamily, const UniString& rPrefix) const;

protected:
    virtual SvXMLStyleContext* CreateStyleChildContext( 
        sal_uInt16 nPrefix, 
        const ::rtl::OUString& rLocalName,
        const ::com::sun::star::uno::Reference< ::com::sun::star::xml::sax::XAttributeList >& xAttrList);

    virtual SvXMLStyleContext *CreateStyleStyleChildContext( 
        sal_uInt16 nFamily,
        sal_uInt16 nPrefix, 
        const ::rtl::OUString& rLocalName,
        const ::com::sun::star::uno::Reference< ::com::sun::star::xml::sax::XAttributeList >& xAttrList);

    virtual SvXMLStyleContext *CreateDefaultStyleStyleChildContext(
        sal_uInt16 nFamily, sal_uInt16 nPrefix,
        const ::rtl::OUString& rLocalName,
        const ::com::sun::star::uno::Reference<
            ::com::sun::star::xml::sax::XAttributeList > & xAttrList );
public:
    TYPEINFO();

    SdXMLStylesContext(
        SdXMLImport& rImport, 
        sal_uInt16 nPrfx, 
        const ::rtl::OUString& rLName,
        const ::com::sun::star::uno::Reference< ::com::sun::star::xml::sax::XAttributeList >& xAttrList,
        sal_Bool bIsAutoStyle);
    virtual ~SdXMLStylesContext();

    virtual sal_uInt16 GetFamily( const ::rtl::OUString& rFamily ) const;
    virtual void EndElement();
    virtual UniReference< SvXMLImportPropertyMapper > GetImportPropertyMapper(sal_uInt16 nFamily) const;

    void SetMasterPageStyles(SdXMLMasterPageContext& rMaster) const;

    ::com::sun::star::uno::Reference< ::com::sun::star::container::XNameAccess > getPageLayouts() const;
};

//////////////////////////////////////////////////////////////////////////////
// office:master-styles context
//
class SdXMLMasterStylesContext : public SvXMLImportContext
{
    ImpMasterPageList			maMasterPageList;

    const SdXMLImport& GetSdImport() const { return (const SdXMLImport&)GetImport(); }
    SdXMLImport& GetSdImport() { return (SdXMLImport&)GetImport(); }
    
public:
    TYPEINFO();

    SdXMLMasterStylesContext( 
        SdXMLImport& rImport, 
        sal_uInt16 nPrfx,
        const ::rtl::OUString& rLName);
    virtual ~SdXMLMasterStylesContext();

    virtual SvXMLImportContext* CreateChildContext( 
        sal_uInt16 nPrefix, 
        const ::rtl::OUString& rLocalName, 
        const ::com::sun::star::uno::Reference< ::com::sun::star::xml::sax::XAttributeList >& xAttrList );

    const ImpMasterPageList& GetMasterPageList() const { return maMasterPageList; }
};


}//end of namespace binfilter
#endif	//  _XIMPSTYLE_HXX
