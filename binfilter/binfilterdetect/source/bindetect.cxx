/*************************************************************************
 *
 *  $RCSfile: bindetect.cxx,v $
 *
 *  $Revision: 1.3 $
 *
 *  last change: $Author: hr $ $Date: 2004-08-03 20:37:19 $
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

#include "bindetect.hxx"

// auto strip #include <framework/interaction.hxx>

// auto strip #ifndef _COM_SUN_STAR_LANG_XMULTISERVICEFACTORY_HPP_
// auto strip #include <com/sun/star/lang/XMultiServiceFactory.hpp>
// auto strip #endif
// auto strip #ifndef _COM_SUN_STAR_BEANS_PROPERTYVALUE_HPP_
// auto strip #include <com/sun/star/beans/PropertyValue.hpp>
// auto strip #endif
// auto strip #ifndef _COM_SUN_STAR_FRAME_XFRAME_HPP_
// auto strip #include <com/sun/star/frame/XFrame.hpp>
// auto strip #endif
// auto strip #ifndef _COM_SUN_STAR_FRAME_XMODEL_HPP_
// auto strip #include <com/sun/star/frame/XModel.hpp>
// auto strip #endif
// auto strip #ifndef _COM_SUN_STAR_AWT_XWINDOW_HPP_
// auto strip #include <com/sun/star/awt/XWindow.hpp>
// auto strip #endif
// auto strip #ifndef _COM_SUN_STAR_LANG_XUNOTUNNEL_HPP_
// auto strip #include <com/sun/star/lang/XUnoTunnel.hpp>
// auto strip #endif
// auto strip #ifndef _UNOTOOLS_PROCESSFACTORY_HXX
// auto strip #include <comphelper/processfactory.hxx>
// auto strip #endif
// auto strip #ifndef _COM_SUN_STAR_BEANS_PROPERTYVALUE_HPP_
// auto strip #include <com/sun/star/beans/PropertyValue.hpp>
// auto strip #endif
// auto strip #ifndef _COM_SUN_STAR_CONTAINER_XNAMEACCESS_HPP_
// auto strip #include <com/sun/star/container/XNameAccess.hpp>
// auto strip #endif
#ifndef _COM_SUN_STAR_IO_XINPUTSTREAM_HPP_
#include <com/sun/star/io/XInputStream.hpp>
#endif
// auto strip #ifndef _COM_SUN_STAR_TASK_XINTERACTIONHANDLER_HPP_
// auto strip #include <com/sun/star/task/XInteractionHandler.hpp>
// auto strip #endif
// auto strip #ifndef _COM_SUN_STAR_LANG_WRAPPEDTARGETRUNTIMEEXCEPTION_HPP_
// auto strip #include <com/sun/star/lang/WrappedTargetRuntimeException.hpp>
// auto strip #endif
// auto strip #ifndef _COM_SUN_STAR_UCB_COMMANDABORTEDEXCEPTION_HPP_
// auto strip #include <com/sun/star/ucb/CommandAbortedException.hpp>
// auto strip #endif
// auto strip #ifndef _COM_SUN_STAR_UCB_INTERACTIVEAPPEXCEPTION_HPP_
// auto strip #include <com/sun/star/ucb/InteractiveAppException.hpp>
// auto strip #endif

// auto strip #ifndef _COM_SUN_STAR_REGISTRY_REGISTRYVALUETYPE_HPP_
// auto strip #include <com/sun/star/registry/RegistryValueType.hpp>
// auto strip #endif
// auto strip #include <com/sun/star/registry/XRegistryKey.hpp>

// auto strip #ifndef __FRAMEWORK_DISPATCH_INTERACTION_HXX_
// auto strip #include <framework/interaction.hxx>
// auto strip #endif

// auto strip #ifndef _TOOLKIT_UNOHLP_HXX
// auto strip #include <toolkit/helper/vclunohelper.hxx>
// auto strip #endif

#ifndef _UCBHELPER_SIMPLEINTERACTIONREQUEST_HXX
#include <ucbhelper/simpleinteractionrequest.hxx>
#endif

#include <rtl/ustring.h>
// auto strip #include <rtl/logfile.hxx>
// auto strip #include <svtools/itemset.hxx>
// auto strip #include <vcl/window.hxx>
#include <svtools/eitem.hxx>
// auto strip #include <svtools/stritem.hxx>
#include <tools/urlobj.hxx>
#include <vos/mutex.hxx>
#include <svtools/sfxecode.hxx>
#include <svtools/ehdl.hxx>
// auto strip #include <sot/storinfo.hxx>

using namespace ::com::sun::star::registry;
using namespace ::com::sun::star::uno;
using namespace ::com::sun::star::io;
using namespace ::com::sun::star::frame;
using namespace ::com::sun::star::task;
using namespace ::com::sun::star::beans;
using namespace ::com::sun::star::lang;
using namespace ::com::sun::star::ucb;
using namespace ::rtl;
using namespace ::binfilter;

// auto strip #include <bf_sfx2/app.hxx>
#include <bf_sfx2/request.hxx>
#include <bf_sfx2/sfxsids.hrc>
#include <bf_sfx2/dispatch.hxx>
// auto strip #include <bf_sfx2/sfxuno.hxx>
// auto strip #include <bf_sfx2/viewfrm.hxx>
// auto strip #include <bf_sfx2/topfrm.hxx>
// auto strip #include <bf_sfx2/frame.hxx>
// auto strip #include <bf_sfx2/docfac.hxx>
#include <bf_sfx2/fcontnr.hxx>
//#include <bf_sfx2/loadenv.hxx>
#include <bf_sfx2/docfile.hxx>
// auto strip #include <bf_sfx2/docfilt.hxx>
//#include <bf_sfx2/brokenpackageint.hxx>

#ifndef _LEGACYBINFILTERMGR_HXX
#include <legacysmgr/legacy_binfilters_smgr.hxx>
#endif
namespace binfilter {
BinFilterDetect::BinFilterDetect( const REFERENCE < ::com::sun::star::lang::XMultiServiceFactory >& xFactory )
{
    ::com::sun::star::uno::Reference< ::com::sun::star::lang::XMultiServiceFactory > mxLegServFact;   
    mxLegServFact = ::legacy_binfilters::getLegacyProcessServiceFactory();
    ::com::sun::star::uno::Reference < XComponent > xWrapper( mxLegServFact->createInstance( 
        ::rtl::OUString( RTL_CONSTASCII_USTRINGPARAM( "com.sun.star.office.OfficeWrapper" ))), UNO_QUERY );
}

BinFilterDetect::~BinFilterDetect()
{
}

::rtl::OUString SAL_CALL BinFilterDetect::detect( ::com::sun::star::uno::Sequence< ::com::sun::star::beans::PropertyValue >& lDescriptor ) throw( ::com::sun::star::uno::RuntimeException )
{
    REFERENCE< XInputStream > xStream;
    REFERENCE< XContent > xContent;
    REFERENCE< XInteractionHandler > xInteraction;
    String aURL;
    ::rtl::OUString sTemp;
    rtl::OUString aTypeName;            // a name describing the type (from MediaDescriptor, usually from flat detection)
    String aPreselectedFilterName;      // a name describing the filter to use (from MediaDescriptor, usually from UI action)
    const SfxFilter* pFilter = NULL, *pExternalFilter = NULL;

    // opening as template is done when a parameter tells to do so and a template filter can be detected
    // (otherwise no valid filter would be found) or if the detected filter is a template filter and
    // there is no parameter that forbids to open as template
    sal_Bool bOpenAsTemplate = sal_False;
    sal_Bool bWasReadOnly = sal_False, bReadOnly = sal_False;

    // now some parameters that can already be in the array, but may be overwritten or new inserted here
    // remember their indices in the case new values must be added to the array
    sal_Int32 nPropertyCount = lDescriptor.getLength();
    sal_Int32 nIndexOfFilterName = -1;
    sal_Int32 nIndexOfInputStream = -1;
    sal_Int32 nIndexOfContent = -1;
    sal_Int32 nIndexOfReadOnlyFlag = -1;
    sal_Int32 nIndexOfTemplateFlag = -1;
    for( sal_Int32 nProperty=0; nProperty<nPropertyCount; ++nProperty )
    {
        // extract properties
        if( lDescriptor[nProperty].Name == OUString(RTL_CONSTASCII_USTRINGPARAM("URL")) )
        {
            lDescriptor[nProperty].Value >>= sTemp;
            aURL = sTemp;
        }
        else if( !aURL.Len() && lDescriptor[nProperty].Name == OUString(RTL_CONSTASCII_USTRINGPARAM("FileName")) )
        {
            lDescriptor[nProperty].Value >>= sTemp;
            aURL = sTemp;
        }
        else if( lDescriptor[nProperty].Name == OUString(RTL_CONSTASCII_USTRINGPARAM("TypeName")) )
        {
            lDescriptor[nProperty].Value >>= sTemp;
            aTypeName = sTemp;
        }
        else if( lDescriptor[nProperty].Name == OUString(RTL_CONSTASCII_USTRINGPARAM("FilterName")) )
        {
            lDescriptor[nProperty].Value >>= sTemp;
            aPreselectedFilterName = sTemp;

            // if the preselected filter name is not correct, it must be erased after detection
            // remember index of property to get access to it later
            nIndexOfFilterName = nProperty;
        }
        else if( lDescriptor[nProperty].Name == OUString(RTL_CONSTASCII_USTRINGPARAM("InputStream")) )
            nIndexOfInputStream = nProperty;
        else if( lDescriptor[nProperty].Name == OUString(RTL_CONSTASCII_USTRINGPARAM("ReadOnly")) )
            nIndexOfReadOnlyFlag = nProperty;
        else if( lDescriptor[nProperty].Name == OUString(RTL_CONSTASCII_USTRINGPARAM("UCBContent")) )
            nIndexOfContent = nProperty;
        else if( lDescriptor[nProperty].Name == OUString(RTL_CONSTASCII_USTRINGPARAM("AsTemplate")) )
        {
            lDescriptor[nProperty].Value >>= bOpenAsTemplate;
            nIndexOfTemplateFlag = nProperty;
        }
        else if( lDescriptor[nProperty].Name == OUString(RTL_CONSTASCII_USTRINGPARAM("InteractionHandler")) )
            lDescriptor[nProperty].Value >>= xInteraction;
    }

    // can't check the type for external filters, so set the "dont" flag accordingly
    ::vos::OGuard aGuard( Application::GetSolarMutex() );
    SfxFilterFlags nMust = SFX_FILTER_IMPORT, nDont = SFX_FILTER_NOTINSTALLED;
    SfxFilterMatcher& rMatcher = SFX_APP()->GetFilterMatcher();

    SfxErrorContext aCtx( ERRCTX_SFX_OPENDOC, aURL );

    // transform parameters into an SfxItemSet
    SfxApplication* pApp = SFX_APP();
    SfxAllItemSet *pSet = new SfxAllItemSet( pApp->GetPool() );
    TransformParameters( SID_OPENDOC, lDescriptor, *pSet );
    SFX_ITEMSET_ARG( pSet, pItem, SfxBoolItem, SID_DOC_READONLY, FALSE );

    bWasReadOnly = pItem && pItem->GetValue();

    // ctor of SfxMedium uses owner transition of ItemSet
    SfxMedium aMedium( aURL, bWasReadOnly ? STREAM_STD_READ : STREAM_STD_READWRITE, FALSE, NULL, pSet );
    aMedium.UseInteractionHandler( TRUE );

    BOOL bIsStorage = aMedium.IsStorage();
    String aFilterName;
    if ( aMedium.GetErrorCode() == ERRCODE_NONE && bIsStorage )
    {
        // remember input stream and content and put them into the descriptor later
        // should be done here since later the medium can switch to a version
        xStream = aMedium.GetInputStream();
        xContent = aMedium.GetContent();

        if ( aMedium.GetErrorCode() == ERRCODE_NONE )
        {
            bReadOnly = aMedium.IsReadOnly();
            SvStorageRef aStor = aMedium.GetStorage();

            if ( INetURLObject( aURL ).GetExtension().CompareToAscii("vor") == COMPARE_EQUAL )
                nMust |= SFX_FILTER_TEMPLATEPATH;

            // check the preselected filter
            if ( aPreselectedFilterName.Len() )
                pFilter = rMatcher.GetFilter4FilterName( aPreselectedFilterName, nMust, SFX_FILTER_NOTINSTALLED );
            else if ( aTypeName.getLength() )
                pFilter = rMatcher.GetFilter4EA( aTypeName, nMust, nDont );

            if ( pFilter )
            {
                // preselected filter or type name matched to a valid filter detectable with this service
                SfxFilterFlags nFlags = pFilter->GetFilterFlags();
                if ( ( nFlags & nMust ) != nMust || ( nFlags & nDont ) != 0 || pFilter->GetFormat() != aStor->GetFormat() )
                    // the filter exists, but filter flags or Clipboard Id don't match
                    pFilter = 0;
            }

            if ( !pFilter )
            {
                // if the filter we just tried was the preselected filter and
                // it doesn't fit, erase the filter name from the media descriptor
                if ( aPreselectedFilterName.Len() )
                    lDescriptor[nIndexOfFilterName].Value <<= ::rtl::OUString();

                // try general detection using clipboard Id
                 pFilter = rMatcher.GetFilter4ClipBoardId( aStor->GetFormat(), nMust, nDont );
            }
        }
    }

    if ( pFilter )
    {
        // successful detection, get the filter name (without prefix)
        aTypeName = pFilter->GetTypeName();
        aFilterName = pFilter->GetFilterName();
        if ( nIndexOfFilterName != -1 )
            // convert to format with factory ( makes load more easy to implement )
            lDescriptor[nIndexOfFilterName].Value <<= ::rtl::OUString( aFilterName );
        else
        {
            lDescriptor.realloc( nPropertyCount + 1 );
            lDescriptor[nPropertyCount].Name = ::rtl::OUString::createFromAscii("FilterName");
            lDescriptor[nPropertyCount].Value <<= ::rtl::OUString( aFilterName );
            nPropertyCount++;
        }

        if ( pFilter->IsOwnTemplateFormat() && nIndexOfTemplateFlag == -1 )
        {
            lDescriptor.realloc( nPropertyCount + 1 );
            lDescriptor[nPropertyCount].Name = ::rtl::OUString::createFromAscii("AsTemplate");
            lDescriptor[nPropertyCount].Value <<= sal_True;
            nPropertyCount++;
        }
    }
    else
    {
        aFilterName.Erase();
        aTypeName = ::rtl::OUString();
    }

    if ( nIndexOfInputStream == -1 && xStream.is() )
    {
        // if input stream wasn't part of the descriptor, now it should be, otherwise the content would be opend twice
        lDescriptor.realloc( nPropertyCount + 1 );
        lDescriptor[nPropertyCount].Name = ::rtl::OUString::createFromAscii("InputStream");
        lDescriptor[nPropertyCount].Value <<= xStream;
        nPropertyCount++;
    }

    if ( nIndexOfContent == -1 && xContent.is() )
    {
        // if input stream wasn't part of the descriptor, now it should be, otherwise the content would be opend twice
        lDescriptor.realloc( nPropertyCount + 1 );
        lDescriptor[nPropertyCount].Name = ::rtl::OUString::createFromAscii("UCBContent");
        lDescriptor[nPropertyCount].Value <<= xContent;
        nPropertyCount++;
    }

    if ( bReadOnly != bWasReadOnly )
    {
        if ( nIndexOfReadOnlyFlag == -1 )
        {
            lDescriptor.realloc( nPropertyCount + 1 );
            lDescriptor[nPropertyCount].Name = ::rtl::OUString::createFromAscii("ReadOnly");
            lDescriptor[nPropertyCount].Value <<= bReadOnly;
            nPropertyCount++;
        }
        else
            lDescriptor[nIndexOfReadOnlyFlag].Value <<= bReadOnly;
    }

    return aTypeName;
}

SFX_IMPL_SINGLEFACTORY( BinFilterDetect )

/* XServiceInfo */
UNOOUSTRING SAL_CALL BinFilterDetect::getImplementationName() throw( UNORUNTIMEEXCEPTION )
{
    return impl_getStaticImplementationName();
}
                                                                                                                                \
/* XServiceInfo */
sal_Bool SAL_CALL BinFilterDetect::supportsService( const UNOOUSTRING& sServiceName ) throw( UNORUNTIMEEXCEPTION )
{
    UNOSEQUENCE< UNOOUSTRING >  seqServiceNames =   getSupportedServiceNames();
    const UNOOUSTRING*          pArray          =   seqServiceNames.getConstArray();
    for ( sal_Int32 nCounter=0; nCounter<seqServiceNames.getLength(); nCounter++ )
    {
        if ( pArray[nCounter] == sServiceName )
        {
            return sal_True ;
        }
    }
    return sal_False ;
}

/* XServiceInfo */
UNOSEQUENCE< UNOOUSTRING > SAL_CALL BinFilterDetect::getSupportedServiceNames() throw( UNORUNTIMEEXCEPTION )
{
    return impl_getStaticSupportedServiceNames();
}

/* Helper for XServiceInfo */
UNOSEQUENCE< UNOOUSTRING > BinFilterDetect::impl_getStaticSupportedServiceNames()
{
    UNOMUTEXGUARD aGuard( UNOMUTEX::getGlobalMutex() );
    UNOSEQUENCE< UNOOUSTRING > seqServiceNames( 1 );
    seqServiceNames.getArray() [0] = UNOOUSTRING::createFromAscii( "com.sun.star.frame.ExtendedTypeDetection"  );
    return seqServiceNames ;
}

/* Helper for XServiceInfo */
UNOOUSTRING BinFilterDetect::impl_getStaticImplementationName()
{
    return UNOOUSTRING::createFromAscii( "com.sun.star.comp.sfx2.BinaryFormatDetector" );
}

/* Helper for registry */
UNOREFERENCE< UNOXINTERFACE > SAL_CALL BinFilterDetect::impl_createInstance( const UNOREFERENCE< UNOXMULTISERVICEFACTORY >& xServiceManager ) throw( UNOEXCEPTION )
{
    return UNOREFERENCE< UNOXINTERFACE >( *new BinFilterDetect( xServiceManager ) );
}

}
extern "C" {

void SAL_CALL component_getImplementationEnvironment(	const	sal_Char**			ppEnvironmentTypeName	,
                                                                uno_Environment**	ppEnvironment			)
{
    *ppEnvironmentTypeName = CPPU_CURRENT_LANGUAGE_BINDING_NAME ;
}

sal_Bool SAL_CALL component_writeInfo(	void*	pServiceManager	,
                                        void*	pRegistryKey	)
{
    ::com::sun::star::uno::Reference< XRegistryKey >	 xKey( reinterpret_cast< XRegistryKey* >( pRegistryKey ) )	;

    // Eigentliche Implementierung und ihre Services registrieren
    ::rtl::OUString aImpl;
    ::rtl::OUString aTempStr;
    ::rtl::OUString aKeyStr;
    REFERENCE< XRegistryKey > xNewKey;
    REFERENCE< XRegistryKey > xLoaderKey;

    // frame loader
    aImpl = ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("/"));
    aImpl += BinFilterDetect::impl_getStaticImplementationName();

    aTempStr = aImpl;
    aTempStr += ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("/UNO/SERVICES"));
    xNewKey = xKey->createKey( aTempStr );
    Sequence < ::rtl::OUString > aServices = BinFilterDetect::impl_getStaticSupportedServiceNames();
    sal_Int32 nCount = aServices.getLength();
    for ( sal_Int16 i=0; i<nCount; i++ )
        xNewKey->createKey( aServices.getConstArray()[i] );

    return sal_True;
}

void* SAL_CALL component_getFactory(	const	sal_Char*	pImplementationName	,
                                                void*		pServiceManager		,
                                                void*		pRegistryKey		)
{
    // Set default return value for this operation - if it failed.
    void* pReturn = NULL ;

    if	(
            ( pImplementationName	!=	NULL ) &&
            ( pServiceManager		!=	NULL )
        )
    {
        // Define variables which are used in following macros.
        ::com::sun::star::uno::Reference< ::com::sun::star::lang::XSingleServiceFactory >	xFactory																								;
        ::com::sun::star::uno::Reference< ::com::sun::star::lang::XMultiServiceFactory >	xServiceManager( reinterpret_cast< ::com::sun::star::lang::XMultiServiceFactory* >( pServiceManager ) )	;

        //=============================================================================
        //  Add new macro line to handle new service.
        //
        //	!!! ATTENTION !!!
        //		Write no ";" at end of line and dont forget "else" ! (see macro)
        //=============================================================================
        IF_NAME_CREATECOMPONENTFACTORY( BinFilterDetect )

        // Factory is valid - service was found.
        if ( xFactory.is() )
        {
            xFactory->acquire();
            pReturn = xFactory.get();
        }
        legacysmgr_component_getFactory( 
            pImplementationName, 
            reinterpret_cast< XMultiServiceFactory *>(pServiceManager),
            reinterpret_cast<XRegistryKey*> (pRegistryKey) );
    }
    // Return with result of this operation.
    return pReturn ;
}
} // extern "C"


