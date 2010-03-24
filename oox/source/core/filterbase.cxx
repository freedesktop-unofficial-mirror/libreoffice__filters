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

#include "oox/core/filterbase.hxx"
#include <set>
#include <com/sun/star/awt/XDevice.hpp>
#include <com/sun/star/frame/XFramesSupplier.hpp>
#include <com/sun/star/frame/XModel.hpp>
#include <com/sun/star/task/XStatusIndicator.hpp>
#include <com/sun/star/task/XInteractionHandler.hpp>
#include <osl/mutex.hxx>
#include <rtl/instance.hxx>
#include <rtl/uri.hxx>
#include <comphelper/docpasswordhelper.hxx>
#include <comphelper/mediadescriptor.hxx>
#include "tokens.hxx"
#include "oox/helper/binaryinputstream.hxx"
#include "oox/helper/binaryoutputstream.hxx"
#include "oox/helper/graphichelper.hxx"
#include "oox/helper/modelobjecthelper.hxx"
#include "oox/ole/oleobjecthelper.hxx"

using ::rtl::OUString;
using ::com::sun::star::uno::Any;
using ::com::sun::star::uno::Reference;
using ::com::sun::star::uno::Sequence;
using ::com::sun::star::uno::Exception;
using ::com::sun::star::uno::RuntimeException;
using ::com::sun::star::uno::UNO_QUERY;
using ::com::sun::star::uno::UNO_QUERY_THROW;
using ::com::sun::star::uno::UNO_SET_THROW;
using ::com::sun::star::lang::IllegalArgumentException;
using ::com::sun::star::lang::XMultiServiceFactory;
using ::com::sun::star::lang::XComponent;
using ::com::sun::star::beans::PropertyValue;
using ::com::sun::star::awt::DeviceInfo;
using ::com::sun::star::awt::XDevice;
using ::com::sun::star::frame::XFrame;
using ::com::sun::star::frame::XFramesSupplier;
using ::com::sun::star::frame::XModel;
using ::com::sun::star::io::XInputStream;
using ::com::sun::star::io::XOutputStream;
using ::com::sun::star::io::XStream;
using ::com::sun::star::task::XStatusIndicator;
using ::com::sun::star::task::XInteractionHandler;
using ::com::sun::star::graphic::XGraphic;
using ::comphelper::MediaDescriptor;
using ::comphelper::SequenceAsHashMap;
using ::oox::ole::OleObjectHelper;

namespace oox {
namespace core {

// ============================================================================

namespace {

/** This guard prevents recursive loading/saving of the same document. */
class DocumentOpenedGuard : public ::osl::Mutex
{
public:
    explicit            DocumentOpenedGuard( const OUString& rUrl );
                        ~DocumentOpenedGuard();

    inline bool         isValid() const { return mbValid; }

private:
                        DocumentOpenedGuard( const DocumentOpenedGuard& );
    DocumentOpenedGuard& operator=( const DocumentOpenedGuard& );

    typedef ::std::set< OUString > UrlSet;
    struct UrlPool : public ::rtl::Static< UrlSet, UrlPool > {};

    UrlSet&             mrUrls;
    OUString            maUrl;
    bool                mbValid;
};

DocumentOpenedGuard::DocumentOpenedGuard( const OUString& rUrl ) :
    mrUrls( UrlPool::get() )
{
    ::osl::MutexGuard aGuard( *this );
    mbValid = (rUrl.getLength() == 0) || (mrUrls.count( rUrl ) == 0);
    if( mbValid && (rUrl.getLength() > 0) )
    {
        mrUrls.insert( rUrl );
        maUrl = rUrl;
    }
}

DocumentOpenedGuard::~DocumentOpenedGuard()
{
    ::osl::MutexGuard aGuard( *this );
    if( maUrl.getLength() > 0 )
        mrUrls.erase( maUrl );
}

} // namespace

// ============================================================================

/** Specifies whether this filter is an import or export filter. */
enum FilterDirection
{
    FILTERDIRECTION_UNKNOWN,
    FILTERDIRECTION_IMPORT,
    FILTERDIRECTION_EXPORT
};

// ----------------------------------------------------------------------------

struct FilterBaseImpl
{
    typedef ::boost::shared_ptr< GraphicHelper >            GraphicHelperRef;
    typedef ::boost::shared_ptr< ModelObjectHelper >        ModelObjHelperRef;
    typedef ::boost::shared_ptr< OleObjectHelper >          OleObjHelperRef;
    typedef ::std::map< OUString, Reference< XGraphic > >   EmbeddedGraphicMap;
    typedef ::std::map< sal_Int32, sal_Int32 >              SystemPalette;

    FilterDirection     meDirection;
    SequenceAsHashMap   maArguments;
    MediaDescriptor     maMediaDesc;
    DeviceInfo          maDeviceInfo;
    OUString            maFileUrl;
    StorageRef          mxStorage;

    GraphicHelperRef    mxGraphicHelper;        /// Graphic and graphic object handling.
    ModelObjHelperRef   mxModelObjHelper;       /// Tables to create new named drawing objects.
    OleObjHelperRef     mxOleObjHelper;         /// OLE object handling.
    EmbeddedGraphicMap  maEmbeddedGraphics;     /// Maps all imported embedded graphics by their path.
    SystemPalette       maSystemPalette;        /// Maps system colors (XML tokens) to RGB color values.

    Reference< XMultiServiceFactory >   mxGlobalFactory;
    Reference< XModel >                 mxModel;
    Reference< XMultiServiceFactory >   mxModelFactory;
    Reference< XInputStream >           mxInStream;
    Reference< XStream >                mxOutStream;
    Reference< XStatusIndicator >       mxStatusIndicator;
    Reference< XInteractionHandler >    mxInteractionHandler;

    explicit            FilterBaseImpl( const Reference< XMultiServiceFactory >& rxGlobalFactory );

    void                setDocumentModel( const Reference< XComponent >& rxComponent );
    bool                hasDocumentModel() const;

    void                initializeFilter();
    void                finalizeFilter();
};

// ----------------------------------------------------------------------------

FilterBaseImpl::FilterBaseImpl( const Reference< XMultiServiceFactory >& rxGlobalFactory ) :
    meDirection( FILTERDIRECTION_UNKNOWN ),
    mxGlobalFactory( rxGlobalFactory )
{
    OSL_ENSURE( mxGlobalFactory.is(), "FilterBaseImpl::FilterBaseImpl - missing service factory" );
    if( mxGlobalFactory.is() )
    {
        // get the metric of the output device
        try
        {
            Reference< XFramesSupplier > xFramesSupp( mxGlobalFactory->createInstance( CREATE_OUSTRING( "com.sun.star.frame.Desktop" ) ), UNO_QUERY_THROW );
            Reference< XFrame > xFrame( xFramesSupp->getActiveFrame(), UNO_SET_THROW );
            Reference< XDevice > xDevice( xFrame->getContainerWindow(), UNO_QUERY_THROW );
            maDeviceInfo = xDevice->getInfo();
        }
        catch( Exception& )
        {
            OSL_ENSURE( false, "FilterBaseImpl::FilterBaseImpl - cannot get output device info" );
        }
    }

    //! TODO: get colors from system
    maSystemPalette[ XML_3dDkShadow ]               = 0x716F64;
    maSystemPalette[ XML_3dLight ]                  = 0xF1EFE2;
    maSystemPalette[ XML_activeBorder ]             = 0xD4D0C8;
    maSystemPalette[ XML_activeCaption ]            = 0x0054E3;
    maSystemPalette[ XML_appWorkspace ]             = 0x808080;
    maSystemPalette[ XML_background ]               = 0x004E98;
    maSystemPalette[ XML_btnFace ]                  = 0xECE9D8;
    maSystemPalette[ XML_btnHighlight ]             = 0xFFFFFF;
    maSystemPalette[ XML_btnShadow ]                = 0xACA899;
    maSystemPalette[ XML_btnText ]                  = 0x000000;
    maSystemPalette[ XML_captionText ]              = 0xFFFFFF;
    maSystemPalette[ XML_gradientActiveCaption ]    = 0x3D95FF;
    maSystemPalette[ XML_gradientInactiveCaption ]  = 0xD8E4F8;
    maSystemPalette[ XML_grayText ]                 = 0xACA899;
    maSystemPalette[ XML_highlight ]                = 0x316AC5;
    maSystemPalette[ XML_highlightText ]            = 0xFFFFFF;
    maSystemPalette[ XML_hotLight ]                 = 0x000080;
    maSystemPalette[ XML_inactiveBorder ]           = 0xD4D0C8;
    maSystemPalette[ XML_inactiveCaption ]          = 0x7A96DF;
    maSystemPalette[ XML_inactiveCaptionText ]      = 0xD8E4F8;
    maSystemPalette[ XML_infoBk ]                   = 0xFFFFE1;
    maSystemPalette[ XML_infoText ]                 = 0x000000;
    maSystemPalette[ XML_menu ]                     = 0xFFFFFF;
    maSystemPalette[ XML_menuBar ]                  = 0xECE9D8;
    maSystemPalette[ XML_menuHighlight ]            = 0x316AC5;
    maSystemPalette[ XML_menuText ]                 = 0x000000;
    maSystemPalette[ XML_scrollBar ]                = 0xD4D0C8;
    maSystemPalette[ XML_window ]                   = 0xFFFFFF;
    maSystemPalette[ XML_windowFrame ]              = 0x000000;
    maSystemPalette[ XML_windowText ]               = 0x000000;
}

void FilterBaseImpl::setDocumentModel( const Reference< XComponent >& rxComponent )
{
    mxModel.set( rxComponent, UNO_QUERY );
    mxModelFactory.set( rxComponent, UNO_QUERY );
}

bool FilterBaseImpl::hasDocumentModel() const
{
    return mxGlobalFactory.is() && mxModel.is() && mxModelFactory.is();
}

void FilterBaseImpl::initializeFilter()
{
    try
    {
        // lock the model controllers
        mxModel->lockControllers();
    }
    catch( Exception& )
    {
    }
}

void FilterBaseImpl::finalizeFilter()
{
    try
    {
        // clear the 'ComponentData' property in the descriptor
        MediaDescriptor::iterator aIt = maMediaDesc.find( MediaDescriptor::PROP_COMPONENTDATA() );
        if( aIt != maMediaDesc.end() )
            aIt->second.clear();
        // write the descriptor back to the document model (adds the password)
        mxModel->attachResource( maFileUrl, maMediaDesc.getAsConstPropertyValueList() );
        // unlock the model controllers
        mxModel->unlockControllers();
    }
    catch( Exception& )
    {
    }
}

// ============================================================================

FilterBase::FilterBase( const Reference< XMultiServiceFactory >& rxGlobalFactory ) :
    mxImpl( new FilterBaseImpl( rxGlobalFactory ) )
{
}

FilterBase::~FilterBase()
{
}

bool FilterBase::isImportFilter() const
{
    return mxImpl->meDirection == FILTERDIRECTION_IMPORT;
}

bool FilterBase::isExportFilter() const
{
    return mxImpl->meDirection == FILTERDIRECTION_EXPORT;
}

// ----------------------------------------------------------------------------

Any FilterBase::getArgument( const OUString& rArgName ) const
{
    SequenceAsHashMap::const_iterator aIt = mxImpl->maArguments.find( rArgName );
    return (aIt == mxImpl->maArguments.end()) ? Any() : aIt->second;
}

const Reference< XMultiServiceFactory >& FilterBase::getGlobalFactory() const
{
    return mxImpl->mxGlobalFactory;
}

MediaDescriptor& FilterBase::getMediaDescriptor() const
{
    return mxImpl->maMediaDesc;
}

const Reference< XModel >& FilterBase::getModel() const
{
    return mxImpl->mxModel;
}

const Reference< XMultiServiceFactory >& FilterBase::getModelFactory() const
{
    return mxImpl->mxModelFactory;
}

const Reference< XStatusIndicator >& FilterBase::getStatusIndicator() const
{
    return mxImpl->mxStatusIndicator;
}

const Reference< XInteractionHandler >& FilterBase::getInteractionHandler() const
{
    return mxImpl->mxInteractionHandler;
}

const OUString& FilterBase::getFileUrl() const
{
    return mxImpl->maFileUrl;
}

namespace {

inline bool lclIsDosDrive( const OUString& rUrl, sal_Int32 nPos = 0 )
{
    return
        (rUrl.getLength() >= nPos + 3) &&
        ((('A' <= rUrl[ nPos ]) && (rUrl[ nPos ] <= 'Z')) || (('a' <= rUrl[ nPos ]) && (rUrl[ nPos ] <= 'z'))) &&
        (rUrl[ nPos + 1 ] == ':') &&
        (rUrl[ nPos + 2 ] == '/');
}

} // namespace

OUString FilterBase::getAbsoluteUrl( const OUString& rUrl ) const
{
    // handle some special cases before calling ::rtl::Uri::convertRelToAbs()

    const OUString aFileSchema = CREATE_OUSTRING( "file:" );
    const OUString aFilePrefix = CREATE_OUSTRING( "file:///" );
    const sal_Int32 nFilePrefixLen = aFilePrefix.getLength();
    const OUString aUncPrefix = CREATE_OUSTRING( "//" );

    /*  (1) convert all backslashes to slashes, and check that passed URL is
        not empty. */
    OUString aUrl = rUrl.replace( '\\', '/' );
    if( aUrl.getLength() == 0 )
        return aUrl;

    /*  (2) add 'file:///' to absolute Windows paths, e.g. convert
        'C:/path/file' to 'file:///c:/path/file'. */
    if( lclIsDosDrive( aUrl ) )
        return aFilePrefix + aUrl;

    /*  (3) add 'file:' to UNC paths, e.g. convert '//server/path/file' to
        'file://server/path/file'. */
    if( aUrl.match( aUncPrefix ) )
        return aFileSchema + aUrl;

    /*  (4) remove additional slashes from UNC paths, e.g. convert
        'file://///server/path/file' to 'file://server/path/file'. */
    if( (aUrl.getLength() >= nFilePrefixLen + 2) &&
        aUrl.match( aFilePrefix ) &&
        aUrl.match( aUncPrefix, nFilePrefixLen ) )
    {
        return aFileSchema + aUrl.copy( nFilePrefixLen );
    }

    /*  (5) handle URLs relative to current drive, e.g. the URL '/path1/file1'
        relative to the base URL 'file:///C:/path2/file2' does not result in
        the expected 'file:///C:/path1/file1', but in 'file:///path1/file1'. */
    if( (aUrl.getLength() >= 1) && (aUrl[ 0 ] == '/') &&
        mxImpl->maFileUrl.match( aFilePrefix ) &&
        lclIsDosDrive( mxImpl->maFileUrl, nFilePrefixLen ) )
    {
        return mxImpl->maFileUrl.copy( 0, nFilePrefixLen + 3 ) + aUrl.copy( 1 );
    }

    try
    {
        return ::rtl::Uri::convertRelToAbs( mxImpl->maFileUrl, aUrl );
    }
    catch( ::rtl::MalformedUriException& )
    {
    }
    return aUrl;
}

StorageRef FilterBase::getStorage() const
{
    return mxImpl->mxStorage;
}

StorageRef FilterBase::openSubStorage( const OUString& rStorageName, bool bCreate ) const
{
    return mxImpl->mxStorage->openSubStorage( rStorageName, bCreate );
}

Reference< XInputStream > FilterBase::openInputStream( const OUString& rStreamName ) const
{
    return mxImpl->mxStorage->openInputStream( rStreamName );
}

Reference< XOutputStream > FilterBase::openOutputStream( const OUString& rStreamName ) const
{
    return mxImpl->mxStorage->openOutputStream( rStreamName );
}

void FilterBase::commitStorage() const
{
    mxImpl->mxStorage->commit();
}

// helpers --------------------------------------------------------------------

GraphicHelper& FilterBase::getGraphicHelper() const
{
    if( !mxImpl->mxGraphicHelper )
        mxImpl->mxGraphicHelper.reset( new GraphicHelper( mxImpl->mxGlobalFactory ) );
    return *mxImpl->mxGraphicHelper;
}

ModelObjectHelper& FilterBase::getModelObjectHelper() const
{
    if( !mxImpl->mxModelObjHelper )
        mxImpl->mxModelObjHelper.reset( new ModelObjectHelper( mxImpl->mxModelFactory ) );
    return *mxImpl->mxModelObjHelper;
}

OleObjectHelper& FilterBase::getOleObjectHelper() const
{
    if( !mxImpl->mxOleObjHelper )
        mxImpl->mxOleObjHelper.reset( new OleObjectHelper( mxImpl->mxModelFactory ) );
    return *mxImpl->mxOleObjHelper;
}

const DeviceInfo& FilterBase::getDeviceInfo() const
{
    return mxImpl->maDeviceInfo;
}

sal_Int32 FilterBase::convertScreenPixelX( double fPixelX ) const
{
    return (mxImpl->maDeviceInfo.PixelPerMeterX > 0) ?
        static_cast< sal_Int32 >( (fPixelX * 100000.0) / mxImpl->maDeviceInfo.PixelPerMeterX ) : 0;
}

sal_Int32 FilterBase::convertScreenPixelY( double fPixelY ) const
{
    return (mxImpl->maDeviceInfo.PixelPerMeterY > 0) ?
        static_cast< sal_Int32 >( (fPixelY * 100000.0) / mxImpl->maDeviceInfo.PixelPerMeterY ) : 0;
}

sal_Int32 FilterBase::getSystemColor( sal_Int32 nToken, sal_Int32 nDefaultRgb ) const
{
    FilterBaseImpl::SystemPalette::const_iterator aIt = mxImpl->maSystemPalette.find( nToken );
    OSL_ENSURE( aIt != mxImpl->maSystemPalette.end(), "FilterBase::getSystemColor - invalid token identifier" );
    return (aIt == mxImpl->maSystemPalette.end()) ? nDefaultRgb : aIt->second;
}

sal_Int32 FilterBase::getSchemeColor( sal_Int32 /*nToken*/ ) const
{
    OSL_ENSURE( false, "FilterBase::getSchemeColor - scheme colors not implemented" );
    return API_RGB_TRANSPARENT;
}

sal_Int32 FilterBase::getPaletteColor( sal_Int32 /*nPaletteIdx*/ ) const
{
    OSL_ENSURE( false, "FilterBase::getPaletteColor - palette colors not implemented" );
    return API_RGB_TRANSPARENT;
}

OUString FilterBase::requestPassword( ::comphelper::IDocPasswordVerifier& rVerifier ) const
{
    ::std::vector< OUString > aDefaultPasswords;
    aDefaultPasswords.push_back( CREATE_OUSTRING( "VelvetSweatshop" ) );
    return ::comphelper::DocPasswordHelper::requestAndVerifyDocPassword(
        rVerifier, mxImpl->maMediaDesc, ::comphelper::DocPasswordRequestType_MS, &aDefaultPasswords );
}

bool FilterBase::importBinaryData( StreamDataSequence& orDataSeq, const OUString& rStreamName )
{
    OSL_ENSURE( rStreamName.getLength() > 0, "FilterBase::importBinaryData - empty stream name" );
    if( rStreamName.getLength() == 0 )
        return false;

    // try to open the stream (this may fail - do not assert)
    BinaryXInputStream aInStrm( openInputStream( rStreamName ), true );
    if( aInStrm.isEof() )
        return false;

    // copy the entire stream to the passed sequence
    SequenceOutputStream aOutStrm( orDataSeq );
    aOutStrm.copyStream( aInStrm );
    return true;
}

Reference< XGraphic > FilterBase::importEmbeddedGraphic( const OUString& rStreamName ) const
{
    Reference< XGraphic > xGraphic;
    OSL_ENSURE( rStreamName.getLength() > 0, "FilterBase::importEmbeddedGraphic - empty stream name" );
    if( rStreamName.getLength() > 0 )
    {
        FilterBaseImpl::EmbeddedGraphicMap::const_iterator aIt = mxImpl->maEmbeddedGraphics.find( rStreamName );
        if( aIt == mxImpl->maEmbeddedGraphics.end() )
        {
            xGraphic = getGraphicHelper().importGraphic( openInputStream( rStreamName ) );
            if( xGraphic.is() )
                mxImpl->maEmbeddedGraphics[ rStreamName ] = xGraphic;
        }
        else
            xGraphic = aIt->second;
    }
    return xGraphic;
}

OUString FilterBase::importEmbeddedGraphicObject( const OUString& rStreamName ) const
{
    Reference< XGraphic > xGraphic = importEmbeddedGraphic( rStreamName );
    return xGraphic.is() ? getGraphicHelper().createGraphicObject( xGraphic ) : OUString();
}

// com.sun.star.lang.XServiceInfo interface -----------------------------------

OUString SAL_CALL FilterBase::getImplementationName() throw( RuntimeException )
{
    return implGetImplementationName();
}

sal_Bool SAL_CALL FilterBase::supportsService( const OUString& rServiceName ) throw( RuntimeException )
{
    return
        (rServiceName == CREATE_OUSTRING( "com.sun.star.document.ImportFilter" )) ||
        (rServiceName == CREATE_OUSTRING( "com.sun.star.document.ExportFilter" ));
}

Sequence< OUString > SAL_CALL FilterBase::getSupportedServiceNames() throw( RuntimeException )
{
    Sequence< OUString > aServiceNames( 2 );
    aServiceNames[ 0 ] = CREATE_OUSTRING( "com.sun.star.document.ImportFilter" );
    aServiceNames[ 1 ] = CREATE_OUSTRING( "com.sun.star.document.ExportFilter" );
    return aServiceNames;
}

// com.sun.star.lang.XInitialization interface --------------------------------

void SAL_CALL FilterBase::initialize( const Sequence< Any >& rArgs ) throw( Exception, RuntimeException )
{
    if( rArgs.getLength() >= 2 ) try
    {
        mxImpl->maArguments << rArgs[ 1 ];
    }
    catch( Exception& )
    {
    }
}

// com.sun.star.document.XImporter interface ----------------------------------

void SAL_CALL FilterBase::setTargetDocument( const Reference< XComponent >& rxDocument ) throw( IllegalArgumentException, RuntimeException )
{
    mxImpl->setDocumentModel( rxDocument );
    if( !mxImpl->hasDocumentModel() )
        throw IllegalArgumentException();
    mxImpl->meDirection = FILTERDIRECTION_IMPORT;
}

// com.sun.star.document.XExporter interface ----------------------------------

void SAL_CALL FilterBase::setSourceDocument( const Reference< XComponent >& rxDocument ) throw( IllegalArgumentException, RuntimeException )
{
    mxImpl->setDocumentModel( rxDocument );
    if( !mxImpl->hasDocumentModel() )
        throw IllegalArgumentException();
    mxImpl->meDirection = FILTERDIRECTION_EXPORT;
}

// com.sun.star.document.XFilter interface ------------------------------------

sal_Bool SAL_CALL FilterBase::filter( const Sequence< PropertyValue >& rMediaDescSeq ) throw( RuntimeException )
{
    sal_Bool bRet = sal_False;
    if( mxImpl->hasDocumentModel() && (mxImpl->meDirection != FILTERDIRECTION_UNKNOWN) )
    {
        setMediaDescriptor( rMediaDescSeq );
        DocumentOpenedGuard aOpenedGuard( mxImpl->maFileUrl );
        if( aOpenedGuard.isValid() || !mxImpl->maFileUrl.getLength() )
        {
            mxImpl->initializeFilter();
            switch( mxImpl->meDirection )
            {
                case FILTERDIRECTION_UNKNOWN:
                break;
                case FILTERDIRECTION_IMPORT:
                    if( mxImpl->mxInStream.is() )
                    {
                        mxImpl->mxStorage = implCreateStorage( mxImpl->mxInStream );
                        bRet = mxImpl->mxStorage.get() && importDocument();
                    }
                break;
                case FILTERDIRECTION_EXPORT:
                    if( mxImpl->mxOutStream.is() )
                    {
                        mxImpl->mxStorage = implCreateStorage( mxImpl->mxOutStream );
                        bRet = mxImpl->mxStorage.get() && exportDocument();
                    }
                break;
            }
            mxImpl->finalizeFilter();
        }
    }
    return bRet;
}

void SAL_CALL FilterBase::cancel() throw( RuntimeException )
{
}

// protected ------------------------------------------------------------------

Reference< XInputStream > FilterBase::implGetInputStream( MediaDescriptor& rMediaDesc ) const
{
    return rMediaDesc.getUnpackedValueOrDefault( MediaDescriptor::PROP_INPUTSTREAM(), Reference< XInputStream >() );
}

Reference< XStream > FilterBase::implGetOutputStream( MediaDescriptor& rMediaDesc ) const
{
    return rMediaDesc.getUnpackedValueOrDefault( MediaDescriptor::PROP_STREAMFOROUTPUT(), Reference< XStream >() );
}

// private --------------------------------------------------------------------

void FilterBase::setMediaDescriptor( const Sequence< PropertyValue >& rMediaDescSeq )
{
    mxImpl->maMediaDesc = rMediaDescSeq;

    switch( mxImpl->meDirection )
    {
        case FILTERDIRECTION_UNKNOWN:
            OSL_ENSURE( false, "FilterBase::setMediaDescriptor - invalid filter direction" );
        break;
        case FILTERDIRECTION_IMPORT:
            mxImpl->maMediaDesc.addInputStream();
            mxImpl->mxInStream = implGetInputStream( mxImpl->maMediaDesc );
            OSL_ENSURE( mxImpl->mxInStream.is(), "FilterBase::setMediaDescriptor - missing input stream" );
        break;
        case FILTERDIRECTION_EXPORT:
            mxImpl->mxOutStream = implGetOutputStream( mxImpl->maMediaDesc );
            OSL_ENSURE( mxImpl->mxOutStream.is(), "FilterBase::setMediaDescriptor - missing output stream" );
        break;
    }

    mxImpl->maFileUrl = mxImpl->maMediaDesc.getUnpackedValueOrDefault( MediaDescriptor::PROP_URL(), OUString() );
    mxImpl->mxStatusIndicator = mxImpl->maMediaDesc.getUnpackedValueOrDefault( MediaDescriptor::PROP_STATUSINDICATOR(), Reference< XStatusIndicator >() );
    mxImpl->mxInteractionHandler = mxImpl->maMediaDesc.getUnpackedValueOrDefault( MediaDescriptor::PROP_INTERACTIONHANDLER(), Reference< XInteractionHandler >() );
}


// ============================================================================

} // namespace core
} // namespace oox

