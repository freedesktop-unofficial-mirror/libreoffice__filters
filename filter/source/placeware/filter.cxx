/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: filter.cxx,v $
 *
 *  $Revision: 1.4 $
 *
 *  last change: $Author: rt $ $Date: 2005-09-08 21:52:09 $
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

#ifndef _COM_SUN_STAR_DOCUMENT_XFILTER_HPP_
#include <com/sun/star/document/XFilter.hpp>
#endif
#ifndef _COM_SUN_STAR_DOCUMENT_XEXPORTER_HPP_
#include <com/sun/star/document/XExporter.hpp>
#endif
#ifndef _COM_SUN_STAR_LANG_XINITIALIZATION_HPP_
#include <com/sun/star/lang/XInitialization.hpp>
#endif
#ifndef _COM_SUN_STAR_LANG_XSERVICEINFO_HPP_
#include <com/sun/star/lang/XServiceInfo.hpp>
#endif

#ifndef _CPPUHELPER_IMPLBASE4_HXX_
#include <cppuhelper/implbase4.hxx>
#endif

#include "exporter.hxx"

using namespace ::com::sun::star::uno;
using namespace ::com::sun::star::lang;

using ::rtl::OUString;
using ::com::sun::star::lang::XComponent;
using ::com::sun::star::beans::PropertyValue;
using ::com::sun::star::io::XOutputStream;
using ::com::sun::star::task::XStatusIndicator;

namespace pwp {

// -----------------------------------------------------------------------------

class PlaceWareExportFilter : public cppu::WeakImplHelper4 
< 
    com::sun::star::document::XFilter,
    com::sun::star::document::XExporter,
    com::sun::star::lang::XInitialization,
    com::sun::star::lang::XServiceInfo
>
{
    Reference< XComponent > mxDoc;
    Reference< XMultiServiceFactory > mxMSF;

public:
    PlaceWareExportFilter( const Reference< XMultiServiceFactory > &rxMSF);

    // XFilter
    virtual sal_Bool SAL_CALL filter( const Sequence< PropertyValue >& aDescriptor ) throw(RuntimeException);
    virtual void SAL_CALL cancel( ) throw (RuntimeException);

    // XExporter
    virtual void SAL_CALL setSourceDocument( const Reference< XComponent >& xDoc ) throw(IllegalArgumentException, RuntimeException);

    // XInitialization
    virtual void SAL_CALL initialize( const Sequence< Any >& aArguments ) throw(Exception, RuntimeException);

    // XServiceInfo
    virtual OUString SAL_CALL getImplementationName() throw(RuntimeException);
    virtual sal_Bool SAL_CALL supportsService( const OUString& ServiceName ) throw(RuntimeException);
    virtual Sequence< OUString > SAL_CALL getSupportedServiceNames()  throw(RuntimeException);
};

// -----------------------------------------------------------------------------

PlaceWareExportFilter::PlaceWareExportFilter(const Reference< XMultiServiceFactory > &rxMSF)
:	mxMSF( rxMSF )
{
}

// -----------------------------------------------------------------------------

sal_Bool SAL_CALL PlaceWareExportFilter::filter( const ::com::sun::star::uno::Sequence< ::com::sun::star::beans::PropertyValue >& aDescriptor ) 
    throw (RuntimeException)
{
    sal_Int32 nLength = aDescriptor.getLength();
    const PropertyValue * pValue = aDescriptor.getConstArray();
    OUString sFileName, sURL;
    Reference < XInterface > xInteractionHandler;
    Reference < XOutputStream > xOutputStream;
    Reference < XStatusIndicator > xStatusIndicator;
    for ( sal_Int32 i = 0 ; i < nLength; i++)
    {
        if ( pValue[i].Name.equalsAsciiL ( RTL_CONSTASCII_STRINGPARAM ( "OutputStream" ) ) )
        {
            pValue[i].Value >>= xOutputStream;
        }
        else if( pValue[i].Name.equalsAsciiL ( RTL_CONSTASCII_STRINGPARAM ( "URL" ) ) )
        {
            pValue[i].Value >>= sURL;
        }
        else if( pValue[i].Name.equalsAsciiL ( RTL_CONSTASCII_STRINGPARAM ( "InteractionHandler" ) ) )
        {
            pValue[i].Value >>= xInteractionHandler;
        }
        else if ( pValue[i].Name.equalsAsciiL( RTL_CONSTASCII_STRINGPARAM ( "StatusIndicator" ) ) )
        {
            pValue[i].Value >>= xStatusIndicator;
        }
    }
    if ( !xOutputStream.is() )
    {
        OSL_ASSERT ( 0 );
        return sal_False;
    }

    PlaceWareExporter aExporter( mxMSF );
    return aExporter.doExport( mxDoc, xOutputStream, sURL, xInteractionHandler, xStatusIndicator );
}

// -----------------------------------------------------------------------------

void SAL_CALL PlaceWareExportFilter::cancel(  ) 
    throw (RuntimeException)
{
}

// -----------------------------------------------------------------------------

// XExporter
void SAL_CALL PlaceWareExportFilter::setSourceDocument( const ::com::sun::star::uno::Reference< ::com::sun::star::lang::XComponent >& xDoc ) 
    throw (::com::sun::star::lang::IllegalArgumentException, RuntimeException)
{
    mxDoc = xDoc;
}

// -----------------------------------------------------------------------------

// XInitialization
void SAL_CALL PlaceWareExportFilter::initialize( const ::com::sun::star::uno::Sequence< ::com::sun::star::uno::Any >& aArguments ) 
    throw (Exception, RuntimeException)
{
}

// -----------------------------------------------------------------------------

OUString PlaceWareExportFilter_getImplementationName ()
    throw (RuntimeException)
{
    return OUString ( RTL_CONSTASCII_USTRINGPARAM ( "com.sun.star.comp.Impress.PlaceWareExportFilter" ) );
}

// -----------------------------------------------------------------------------

#define SERVICE_NAME "com.sun.star.document.ExportFilter"

sal_Bool SAL_CALL PlaceWareExportFilter_supportsService( const OUString& ServiceName ) 
    throw (RuntimeException)
{
    return ServiceName.equalsAsciiL( RTL_CONSTASCII_STRINGPARAM ( SERVICE_NAME ) );
}

// -----------------------------------------------------------------------------

Sequence< OUString > SAL_CALL PlaceWareExportFilter_getSupportedServiceNames(  ) 
    throw (RuntimeException)
{
    Sequence < OUString > aRet(1);
    OUString* pArray = aRet.getArray();
    pArray[0] =  OUString ( RTL_CONSTASCII_USTRINGPARAM ( SERVICE_NAME ) );
    return aRet;
}
#undef SERVICE_NAME

// -----------------------------------------------------------------------------

Reference< XInterface > SAL_CALL PlaceWareExportFilter_createInstance( const Reference< XMultiServiceFactory > & rSMgr)
    throw( Exception )
{
    return (cppu::OWeakObject*) new PlaceWareExportFilter( rSMgr );
}

// -----------------------------------------------------------------------------

// XServiceInfo
OUString SAL_CALL PlaceWareExportFilter::getImplementationName(  ) 
    throw (RuntimeException)
{
    return PlaceWareExportFilter_getImplementationName();
}

// -----------------------------------------------------------------------------

sal_Bool SAL_CALL PlaceWareExportFilter::supportsService( const OUString& rServiceName ) 
    throw (RuntimeException)
{
    return PlaceWareExportFilter_supportsService( rServiceName );
}

// -----------------------------------------------------------------------------

::com::sun::star::uno::Sequence< OUString > SAL_CALL PlaceWareExportFilter::getSupportedServiceNames(  ) 
    throw (RuntimeException)
{
    return PlaceWareExportFilter_getSupportedServiceNames();
}

// -----------------------------------------------------------------------------

}
