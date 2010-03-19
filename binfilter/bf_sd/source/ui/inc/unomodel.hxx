/*************************************************************************
 *
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER.
 *
 * Copyright 2000, 2010 Oracle and/or its affiliates.
 *
 * OpenOffice.org - a multi-platform office productivity suite
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
#ifndef _UNOMODEL_HXX
#define _UNOMODEL_HXX

#ifndef _COM_SUN_STAR_STYLE_XSTYLEFAMILIESSUPPLIER_HPP_
#include <com/sun/star/style/XStyleFamiliesSupplier.hpp>
#endif
#ifndef _COM_SUN_STAR_DOCUMENT_XLINKTARGETSUPPLIER_HPP_
#include <com/sun/star/document/XLinkTargetSupplier.hpp>
#endif
#ifndef _COM_SUN_STAR_DRAWING_XDRAWPAGESSUPPLIER_HPP_
#include <com/sun/star/drawing/XDrawPagesSupplier.hpp>
#endif
#ifndef _COM_SUN_STAR_DRAWING_XDRAWPAGESUMMARIZER_HPP_
#include <com/sun/star/drawing/XDrawPageSummarizer.hpp>
#endif
#ifndef _COM_SUN_STAR_DRAWING_XDRAWPAGEDUPLICATOR_HPP_
#include <com/sun/star/drawing/XDrawPageDuplicator.hpp>
#endif
#ifndef _COM_SUN_STAR_DRAWING_XLAYERSUPPLIER_HPP_
#include <com/sun/star/drawing/XLayerSupplier.hpp>
#endif
#ifndef _COM_SUN_STAR_DRAWING_XMASTERPAGESSUPPLIER_HPP_
#include <com/sun/star/drawing/XMasterPagesSupplier.hpp>
#endif
#ifndef _COM_SUN_STAR_PRESENTATION_XPRESENTATIONSUPPLIER_HPP_
#include <com/sun/star/presentation/XPresentationSupplier.hpp>
#endif
#ifndef _COM_SUN_STAR_PRESENTATION_XCUSTOMPRESENTATIONSUPPLIER_HPP_
#include <com/sun/star/presentation/XCustomPresentationSupplier.hpp>
#endif
#ifndef _COM_SUN_STAR_DRAWING_XLAYERMANAGER_HPP_
#include <com/sun/star/drawing/XLayerManager.hpp>
#endif
#ifndef _COM_SUN_STAR_CONTAINER_XNAMECONTAINER_HPP_
#include <com/sun/star/container/XNameContainer.hpp>
#endif
#ifndef _COM_SUN_STAR_PRESENTATION_XPRESENTATION_HPP_
#include <com/sun/star/presentation/XPresentation.hpp>
#endif
#ifndef _COM_SUN_STAR_LANG_XSERVICEINFO_HPP_
#include <com/sun/star/lang/XServiceInfo.hpp>
#endif
#ifndef _COM_SUN_STAR_DRAWING_XDRAWPAGES_HPP_
#include <com/sun/star/drawing/XDrawPages.hpp>
#endif
#ifndef _COM_SUN_STAR_LANG_XUNOTUNNEL_HPP_ 
#include <com/sun/star/lang/XUnoTunnel.hpp>
#endif
#ifndef _COM_SUN_STAR_UCB_XANYCOMPAREFACTORY_HPP_ 
#include <com/sun/star/ucb/XAnyCompareFactory.hpp>
#endif
#ifndef _COM_SUN_STAR_I18N_XFORBIDDENCHARACTERS_HPP_ 
#include <com/sun/star/i18n/XForbiddenCharacters.hpp>
#endif
#ifndef _COM_SUN_STAR_PRESENTATION_XHANDOUTMASTERSUPPLIER_HPP_
#include <com/sun/star/presentation/XHandoutMasterSupplier.hpp>
#endif
#ifndef _COM_SUN_STAR_VIEW_XRENDERABLE_HPP_
#include <com/sun/star/view/XRenderable.hpp>
#endif
#ifndef _COM_SUN_STAR_UTIL_MEASUREUNIT_HPP_
#include <com/sun/star/util/MeasureUnit.hpp>
#endif

#ifndef _SFXLSTNER_HXX //autogen
#include <bf_svtools/lstner.hxx>
#endif

#ifndef _SFX_SFXBASEMODEL_HXX_
#include <bf_sfx2/sfxbasemodel.hxx>
#endif
#ifndef _SVX_FMDMOD_HXX
#include <bf_svx/fmdmod.hxx>
#endif

#include <bf_svx/unoipset.hxx>

#include <comphelper/servicehelper.hxx>
class List;
namespace binfilter {

class SdDrawDocShell;
class SdDrawDocument;
class SdPage;
class SdXCustomPresentations;

/***********************************************************************
*                                                                      *
***********************************************************************/
class SdXImpressDocument : public SfxBaseModel, // implements SfxListener, OWEAKOBJECT & other
                           public SvxFmMSFactory,
                           public ::com::sun::star::drawing::XDrawPageDuplicator,
                           public ::com::sun::star::drawing::XLayerSupplier,
                           public ::com::sun::star::drawing::XMasterPagesSupplier,
                           public ::com::sun::star::drawing::XDrawPagesSupplier,
                           public ::com::sun::star::presentation::XPresentationSupplier,
                           public ::com::sun::star::presentation::XCustomPresentationSupplier,
                           public ::com::sun::star::document::XLinkTargetSupplier,
                           public ::com::sun::star::beans::XPropertySet,
                           public ::com::sun::star::style::XStyleFamiliesSupplier,
                           public ::com::sun::star::lang::XServiceInfo,
                           public ::com::sun::star::lang::XUnoTunnel,
                           public ::com::sun::star::ucb::XAnyCompareFactory,
                           public ::com::sun::star::presentation::XHandoutMasterSupplier,
                           public ::com::sun::star::view::XRenderable
{
    friend class SdDrawPagesAccess;
    friend class SdMasterPagesAccess;
    friend class SdLayerManager;

private:
    SdDrawDocShell* pDocShell;
    SdDrawDocument* pDoc;

    SdPage* InsertSdPage( sal_uInt16 nPage, sal_Bool bDuplicate = sal_False ) throw();

    sal_Bool mbImpressDoc;
    sal_Bool mbClipBoard;

    ::com::sun::star::uno::WeakReference< ::com::sun::star::drawing::XDrawPages > mxDrawPagesAccess;
    ::com::sun::star::uno::WeakReference< ::com::sun::star::drawing::XDrawPages > mxMasterPagesAccess;
    ::com::sun::star::uno::WeakReference< ::com::sun::star::container::XNameAccess > mxLayerManager;
    ::com::sun::star::uno::WeakReference< ::com::sun::star::container::XNameContainer > mxCustomPresentationAccess;
    ::com::sun::star::uno::WeakReference< ::com::sun::star::presentation::XPresentation > mxPresentation;
    ::com::sun::star::uno::WeakReference< ::com::sun::star::container::XNameAccess > mxStyleFamilies;
    ::com::sun::star::uno::WeakReference< ::com::sun::star::i18n::XForbiddenCharacters > mxForbidenCharacters;

    ::com::sun::star::uno::Reference< ::com::sun::star::uno::XInterface > mxDashTable;
    ::com::sun::star::uno::Reference< ::com::sun::star::uno::XInterface > mxGradientTable;
    ::com::sun::star::uno::Reference< ::com::sun::star::uno::XInterface > mxHatchTable;
    ::com::sun::star::uno::Reference< ::com::sun::star::uno::XInterface > mxBitmapTable;
    ::com::sun::star::uno::Reference< ::com::sun::star::uno::XInterface > mxTransGradientTable;
    ::com::sun::star::uno::Reference< ::com::sun::star::uno::XInterface > mxMarkerTable;
    ::com::sun::star::uno::Reference< ::com::sun::star::uno::XInterface > mxDrawingPool;

    SvxItemPropertySet	aPropSet;

    ::com::sun::star::uno::Sequence< ::com::sun::star::uno::Type > maTypeSequence;

    void initializeDocument();
public:
    SdXImpressDocument( SdDrawDocShell* pShell ) throw();
    virtual ~SdXImpressDocument() throw();

    // intern
    virtual int	operator==( const SdXImpressDocument& rModel ) const { return pDoc == rModel.pDoc; }
    virtual int	operator!=( const SdXImpressDocument& rModel ) const { return pDoc != rModel.pDoc; }

    SdDrawDocShell* GetDocShell() const { return pDocShell; }
    SdDrawDocument* GetDoc() const { return pDoc; }
    sal_Bool IsImpressDocument() const { return mbImpressDoc; }

    void SetModified( sal_Bool bModified = sal_True ) throw();

    ::com::sun::star::uno::Reference< ::com::sun::star::i18n::XForbiddenCharacters > getForbiddenCharsTable();

    // SfxListener
    virtual void			Notify( SfxBroadcaster& rBC, const SfxHint& rHint );

    UNO3_GETIMPLEMENTATION_DECL(SdXImpressDocument)

    // XInterface
    virtual ::com::sun::star::uno::Any SAL_CALL queryInterface( const ::com::sun::star::uno::Type & rType ) throw(::com::sun::star::uno::RuntimeException);
    virtual void SAL_CALL acquire() throw();
    virtual void SAL_CALL release() throw();

    // XModel
    virtual void SAL_CALL lockControllers(  ) throw(::com::sun::star::uno::RuntimeException);
    virtual void SAL_CALL unlockControllers(  ) throw(::com::sun::star::uno::RuntimeException);
    virtual sal_Bool SAL_CALL hasControllersLocked(  ) throw(::com::sun::star::uno::RuntimeException);
    virtual ::com::sun::star::uno::Reference < ::com::sun::star::container::XIndexAccess > SAL_CALL getViewData() throw(::com::sun::star::uno::RuntimeException);
    virtual void SAL_CALL setViewData( const ::com::sun::star::uno::Reference < ::com::sun::star::container::XIndexAccess >& aData ) throw(::com::sun::star::uno::RuntimeException);

    // XTypeProvider
    virtual ::com::sun::star::uno::Sequence< ::com::sun::star::uno::Type > SAL_CALL getTypes(  ) throw(::com::sun::star::uno::RuntimeException);
    virtual ::com::sun::star::uno::Sequence< sal_Int8 > SAL_CALL getImplementationId(  ) throw(::com::sun::star::uno::RuntimeException);

    // XDrawPageDuplicator
    virtual ::com::sun::star::uno::Reference< ::com::sun::star::drawing::XDrawPage > SAL_CALL duplicate( const ::com::sun::star::uno::Reference< ::com::sun::star::drawing::XDrawPage >& xPage ) throw(::com::sun::star::uno::RuntimeException);

    // XDrawPagesSupplier
    virtual ::com::sun::star::uno::Reference< ::com::sun::star::drawing::XDrawPages > SAL_CALL getDrawPages(  ) throw(::com::sun::star::uno::RuntimeException);

    // XMasterPagesSupplier
    virtual ::com::sun::star::uno::Reference< ::com::sun::star::drawing::XDrawPages > SAL_CALL getMasterPages(  ) throw(::com::sun::star::uno::RuntimeException);

    // XLayerManagerSupplier
    virtual ::com::sun::star::uno::Reference< ::com::sun::star::container::XNameAccess > SAL_CALL getLayerManager(  ) throw(::com::sun::star::uno::RuntimeException);

    // XCustomPresentationSupplier
    virtual ::com::sun::star::uno::Reference< ::com::sun::star::container::XNameContainer > SAL_CALL getCustomPresentations(  ) throw(::com::sun::star::uno::RuntimeException);

    // XHandoutMasterSupplier
    virtual ::com::sun::star::uno::Reference< ::com::sun::star::drawing::XDrawPage > SAL_CALL getHandoutMasterPage(  ) throw (::com::sun::star::uno::RuntimeException);

    // XPresentationSupplier
    virtual ::com::sun::star::uno::Reference< ::com::sun::star::presentation::XPresentation > SAL_CALL getPresentation(  ) throw(::com::sun::star::uno::RuntimeException);

    // XMultiServiceFactory ( SvxFmMSFactory )
    virtual ::com::sun::star::uno::Reference< ::com::sun::star::uno::XInterface > SAL_CALL createInstance( const ::rtl::OUString& aServiceSpecifier ) throw(::com::sun::star::uno::Exception, ::com::sun::star::uno::RuntimeException);
    virtual ::com::sun::star::uno::Sequence< ::rtl::OUString > SAL_CALL getAvailableServiceNames(  ) throw(::com::sun::star::uno::RuntimeException);

    // XServiceInfo
    virtual ::rtl::OUString SAL_CALL getImplementationName() throw(::com::sun::star::uno::RuntimeException);
    virtual sal_Bool SAL_CALL supportsService( const ::rtl::OUString& ServiceName ) throw(::com::sun::star::uno::RuntimeException);
    virtual ::com::sun::star::uno::Sequence< ::rtl::OUString > SAL_CALL getSupportedServiceNames() throw(::com::sun::star::uno::RuntimeException);

    // XPropertySet
    virtual ::com::sun::star::uno::Reference< ::com::sun::star::beans::XPropertySetInfo > SAL_CALL getPropertySetInfo(  ) throw(::com::sun::star::uno::RuntimeException);
    virtual void SAL_CALL setPropertyValue( const ::rtl::OUString& aPropertyName, const ::com::sun::star::uno::Any& aValue ) throw(::com::sun::star::beans::UnknownPropertyException, ::com::sun::star::beans::PropertyVetoException, ::com::sun::star::lang::IllegalArgumentException, ::com::sun::star::lang::WrappedTargetException, ::com::sun::star::uno::RuntimeException);
    virtual ::com::sun::star::uno::Any SAL_CALL getPropertyValue( const ::rtl::OUString& PropertyName ) throw(::com::sun::star::beans::UnknownPropertyException, ::com::sun::star::lang::WrappedTargetException, ::com::sun::star::uno::RuntimeException); 
    virtual void SAL_CALL addPropertyChangeListener( const ::rtl::OUString& aPropertyName, const ::com::sun::star::uno::Reference< ::com::sun::star::beans::XPropertyChangeListener >& xListener ) throw(::com::sun::star::beans::UnknownPropertyException, ::com::sun::star::lang::WrappedTargetException, ::com::sun::star::uno::RuntimeException);
    virtual void SAL_CALL removePropertyChangeListener( const ::rtl::OUString& aPropertyName, const ::com::sun::star::uno::Reference< ::com::sun::star::beans::XPropertyChangeListener >& aListener ) throw(::com::sun::star::beans::UnknownPropertyException, ::com::sun::star::lang::WrappedTargetException, ::com::sun::star::uno::RuntimeException); 
    virtual void SAL_CALL addVetoableChangeListener( const ::rtl::OUString& PropertyName, const ::com::sun::star::uno::Reference< ::com::sun::star::beans::XVetoableChangeListener >& aListener ) throw(::com::sun::star::beans::UnknownPropertyException, ::com::sun::star::lang::WrappedTargetException, ::com::sun::star::uno::RuntimeException);
    virtual void SAL_CALL removeVetoableChangeListener( const ::rtl::OUString& PropertyName, const ::com::sun::star::uno::Reference< ::com::sun::star::beans::XVetoableChangeListener >& aListener ) throw(::com::sun::star::beans::UnknownPropertyException, ::com::sun::star::lang::WrappedTargetException, ::com::sun::star::uno::RuntimeException);

    // XLinkTargetSupplier
    virtual ::com::sun::star::uno::Reference< ::com::sun::star::container::XNameAccess > SAL_CALL getLinks(  ) throw(::com::sun::star::uno::RuntimeException);

    // XStyleFamiliesSupplier
    virtual ::com::sun::star::uno::Reference< ::com::sun::star::container::XNameAccess > SAL_CALL getStyleFamilies(  ) throw(::com::sun::star::uno::RuntimeException);

    // XAnyCompareFactory
    virtual ::com::sun::star::uno::Reference< ::com::sun::star::ucb::XAnyCompare > SAL_CALL createAnyCompareByName( const ::rtl::OUString& PropertyName ) throw(::com::sun::star::uno::RuntimeException);

    // XRenderable
    virtual sal_Int32 SAL_CALL getRendererCount( const ::com::sun::star::uno::Any& aSelection, const ::com::sun::star::uno::Sequence< ::com::sun::star::beans::PropertyValue >& xOptions ) throw (::com::sun::star::lang::IllegalArgumentException, ::com::sun::star::uno::RuntimeException);
    virtual ::com::sun::star::uno::Sequence< ::com::sun::star::beans::PropertyValue > SAL_CALL getRenderer( sal_Int32 nRenderer, const ::com::sun::star::uno::Any& aSelection, const ::com::sun::star::uno::Sequence< ::com::sun::star::beans::PropertyValue >& xOptions ) throw (::com::sun::star::lang::IllegalArgumentException, ::com::sun::star::uno::RuntimeException);
    virtual void SAL_CALL render( sal_Int32 nRenderer, const ::com::sun::star::uno::Any& aSelection, const ::com::sun::star::uno::Sequence< ::com::sun::star::beans::PropertyValue >& xOptions ) throw (::com::sun::star::lang::IllegalArgumentException, ::com::sun::star::uno::RuntimeException);

    // XComponent
    virtual void SAL_CALL dispose() throw (::com::sun::star::uno::RuntimeException);

    // XPrintable
    virtual void SAL_CALL setPrinter( const ::com::sun::star::uno::Sequence< ::com::sun::star::beans::PropertyValue >& seqPrinter )
        throw (::com::sun::star::lang::IllegalArgumentException, ::com::sun::star::uno::RuntimeException);
};
} //namespace binfilter
/***********************************************************************
*                                                                      *
***********************************************************************/

#include <cppuhelper/implbase3.hxx>
namespace binfilter {//STRIP009
class SdDrawPagesAccess : public ::cppu::WeakImplHelper3< ::com::sun::star::drawing::XDrawPages, ::com::sun::star::container::XNameAccess, ::com::sun::star::lang::XServiceInfo >
{
private:
    SdXImpressDocument&	rModel;

public:
    SdDrawPagesAccess( SdXImpressDocument&	rMyModel ) throw();
    virtual ~SdDrawPagesAccess() throw();

    // XDrawPages
    virtual ::com::sun::star::uno::Reference< ::com::sun::star::drawing::XDrawPage > SAL_CALL insertNewByIndex( sal_Int32 nIndex ) throw(::com::sun::star::uno::RuntimeException);
    virtual void SAL_CALL remove( const ::com::sun::star::uno::Reference< ::com::sun::star::drawing::XDrawPage >& xPage ) throw(::com::sun::star::uno::RuntimeException);

    // XNameAccess
    virtual ::com::sun::star::uno::Any SAL_CALL getByName( const ::rtl::OUString& aName ) throw(::com::sun::star::container::NoSuchElementException, ::com::sun::star::lang::WrappedTargetException, ::com::sun::star::uno::RuntimeException);
    virtual ::com::sun::star::uno::Sequence< ::rtl::OUString > SAL_CALL getElementNames() throw(::com::sun::star::uno::RuntimeException);
    virtual sal_Bool SAL_CALL hasByName( const ::rtl::OUString& aName ) throw(::com::sun::star::uno::RuntimeException);

    // XIndexAccess
    virtual sal_Int32 SAL_CALL getCount() throw(::com::sun::star::uno::RuntimeException) ;
    virtual ::com::sun::star::uno::Any SAL_CALL getByIndex( sal_Int32 Index ) throw(::com::sun::star::lang::IndexOutOfBoundsException, ::com::sun::star::lang::WrappedTargetException, ::com::sun::star::uno::RuntimeException);

    // XElementAccess
    virtual ::com::sun::star::uno::Type SAL_CALL getElementType() throw(::com::sun::star::uno::RuntimeException);
    virtual sal_Bool SAL_CALL hasElements() throw(::com::sun::star::uno::RuntimeException);

    // XServiceInfo
    virtual ::rtl::OUString SAL_CALL getImplementationName(  ) throw(::com::sun::star::uno::RuntimeException);
    virtual sal_Bool SAL_CALL supportsService( const ::rtl::OUString& ServiceName ) throw(::com::sun::star::uno::RuntimeException);
    virtual ::com::sun::star::uno::Sequence< ::rtl::OUString > SAL_CALL getSupportedServiceNames(  ) throw(::com::sun::star::uno::RuntimeException);
};
} //namespace binfilter
/***********************************************************************
*                                                                      *
***********************************************************************/

#include <cppuhelper/implbase2.hxx>
namespace binfilter {//STRIP009
class SdMasterPagesAccess : public ::cppu::WeakImplHelper2< ::com::sun::star::drawing::XDrawPages, ::com::sun::star::lang::XServiceInfo >
{
private:
    SdXImpressDocument&	rModel;

public:
    SdMasterPagesAccess( SdXImpressDocument& rMyModel ) throw();
    virtual ~SdMasterPagesAccess() throw();

    // XDrawPages
    virtual ::com::sun::star::uno::Reference< ::com::sun::star::drawing::XDrawPage > SAL_CALL insertNewByIndex( sal_Int32 nIndex ) throw(::com::sun::star::uno::RuntimeException);
    virtual void SAL_CALL remove( const ::com::sun::star::uno::Reference< ::com::sun::star::drawing::XDrawPage >& xPage ) throw(::com::sun::star::uno::RuntimeException);

    // XIndexAccess
    virtual sal_Int32 SAL_CALL getCount() throw(::com::sun::star::uno::RuntimeException) ;
    virtual ::com::sun::star::uno::Any SAL_CALL getByIndex( sal_Int32 Index ) throw(::com::sun::star::lang::IndexOutOfBoundsException, ::com::sun::star::lang::WrappedTargetException, ::com::sun::star::uno::RuntimeException);

    // XElementAccess
    virtual ::com::sun::star::uno::Type SAL_CALL getElementType() throw(::com::sun::star::uno::RuntimeException);
    virtual sal_Bool SAL_CALL hasElements() throw(::com::sun::star::uno::RuntimeException);

    // XServiceInfo
    virtual ::rtl::OUString SAL_CALL getImplementationName(  ) throw(::com::sun::star::uno::RuntimeException);
    virtual sal_Bool SAL_CALL supportsService( const ::rtl::OUString& ServiceName ) throw(::com::sun::star::uno::RuntimeException);
    virtual ::com::sun::star::uno::Sequence< ::rtl::OUString > SAL_CALL getSupportedServiceNames(  ) throw(::com::sun::star::uno::RuntimeException);
};
} //namespace binfilter
/***********************************************************************
*                                                                      *
***********************************************************************/
#include <cppuhelper/implbase2.hxx>
namespace binfilter {//STRIP009
class SdDocLinkTargets : public ::cppu::WeakImplHelper2< ::com::sun::star::container::XNameAccess,
                                                         ::com::sun::star::lang::XServiceInfo >
{
private:
    SdXImpressDocument&	rModel;

public:
    SdDocLinkTargets( SdXImpressDocument&	rMyModel ) throw();
    virtual ~SdDocLinkTargets() throw();

    // XNameAccess
    virtual ::com::sun::star::uno::Any SAL_CALL getByName( const ::rtl::OUString& aName ) throw(::com::sun::star::container::NoSuchElementException, ::com::sun::star::lang::WrappedTargetException, ::com::sun::star::uno::RuntimeException);
    virtual ::com::sun::star::uno::Sequence< ::rtl::OUString > SAL_CALL getElementNames() throw(::com::sun::star::uno::RuntimeException);
    virtual sal_Bool SAL_CALL hasByName( const ::rtl::OUString& aName ) throw(::com::sun::star::uno::RuntimeException);

    // XElementAccess
    virtual ::com::sun::star::uno::Type SAL_CALL getElementType() throw(::com::sun::star::uno::RuntimeException);
    virtual sal_Bool SAL_CALL hasElements() throw(::com::sun::star::uno::RuntimeException);

    // XServiceInfo
    virtual ::rtl::OUString SAL_CALL getImplementationName() throw(::com::sun::star::uno::RuntimeException);
    virtual sal_Bool SAL_CALL supportsService( const ::rtl::OUString& ServiceName ) throw(::com::sun::star::uno::RuntimeException);
    virtual ::com::sun::star::uno::Sequence< ::rtl::OUString > SAL_CALL getSupportedServiceNames() throw(::com::sun::star::uno::RuntimeException);

    // intern
    SdPage* FindPage( const ::rtl::OUString& rName ) const throw();
};

} //namespace binfilter
#endif


