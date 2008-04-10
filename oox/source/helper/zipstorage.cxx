/*************************************************************************
 *
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER.
 * 
 * Copyright 2008 by Sun Microsystems, Inc.
 *
 * OpenOffice.org - a multi-platform office productivity suite
 *
 * $RCSfile: zipstorage.cxx,v $
 * $Revision: 1.3 $
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

#include "oox/helper/zipstorage.hxx"
#include <com/sun/star/lang/XMultiServiceFactory.hpp>
#include <com/sun/star/embed/XStorage.hpp>
#include <com/sun/star/io/XInputStream.hpp>
#include <com/sun/star/io/XOutputStream.hpp>
#include <comphelper/storagehelper.hxx>
#include "oox/helper/helper.hxx"

using ::rtl::OUString;
using ::com::sun::star::uno::Any;
using ::com::sun::star::uno::Reference;
using ::com::sun::star::uno::Sequence;
using ::com::sun::star::uno::Exception;
using ::com::sun::star::uno::UNO_QUERY;
using ::com::sun::star::lang::XMultiServiceFactory;
using ::com::sun::star::embed::XStorage;
using ::com::sun::star::io::XInputStream;
using ::com::sun::star::io::XOutputStream;

namespace oox {

// ============================================================================

ZipStorage::ZipStorage(
        const Reference< XMultiServiceFactory >& rxFactory,
        const Reference< XInputStream >& rxInStream ) :
    StorageBase( rxInStream, false )
{
    OSL_ENSURE( rxFactory.is(), "ZipStorage::ZipStorage - missing service factory" );
    // create base storage object
    try
    {
        mxStorage = ::comphelper::OStorageHelper::GetStorageFromInputStream( rxInStream, rxFactory );
    }
    catch( Exception& )
    {
        OSL_ENSURE( false, "ZipStorage::ZipStorage - cannot open input storage" );
    }
}

ZipStorage::ZipStorage(
        const Reference< XMultiServiceFactory >& rxFactory,
        const Reference< XOutputStream >& rxOutStream ) :
    StorageBase( rxOutStream, false )
{
    OSL_ENSURE( rxFactory.is(), "ZipStorage::ZipStorage - missing service factory" );
    (void)rxFactory;   // prevent compiler warning
    OSL_ENSURE( false, "ZipStorage::ZipStorage - not implemented" );
}

ZipStorage::ZipStorage( const ZipStorage& rParentStorage, const Reference< XStorage >& rxStorage, const OUString& rElementName ) :
    StorageBase( rParentStorage, rElementName ),
    mxStorage( rxStorage )
{
    OSL_ENSURE( mxStorage.is(), "ZipStorage::ZipStorage - missing storage" );
}

ZipStorage::~ZipStorage()
{
}

bool ZipStorage::implIsStorage() const
{
    return mxStorage.is();
}

Reference< XStorage > ZipStorage::implGetXStorage() const
{
    return mxStorage;
}

void ZipStorage::implGetElementNames( ::std::vector< OUString >& orElementNames ) const
{
    Sequence< OUString > aNames;
    if( mxStorage.is() ) try
    {
        aNames = mxStorage->getElementNames();
        if( aNames.getLength() > 0 )
            orElementNames.insert( orElementNames.end(), aNames.getConstArray(), aNames.getConstArray() + aNames.getLength() );
    }
    catch( Exception& )
    {
    }
}

StorageRef ZipStorage::implOpenSubStorage( const OUString& rElementName, bool bCreate )
{
    OSL_ENSURE( !bCreate, "ZipStorage::implOpenSubStorage - creating new sub storages not implemented" );
    (void)bCreate;  // prevent compiler warning

    Reference< XStorage > xSubXStorage;
    try
    {
        // XStorage::isStorageElement may throw various exceptions...
        if( mxStorage->isStorageElement( rElementName ) )
            xSubXStorage = mxStorage->openStorageElement(
                rElementName, ::com::sun::star::embed::ElementModes::READ );
    }
    catch( Exception& )
    {
    }

    StorageRef xSubStorage;
    if( xSubXStorage.is() )
        xSubStorage.reset( new ZipStorage( *this, xSubXStorage, rElementName ) );
    return xSubStorage;
}

Reference< XInputStream > ZipStorage::implOpenInputStream( const OUString& rElementName )
{
    Reference< XInputStream > xInStream;
    if( mxStorage.is() ) try
    {
        xInStream.set( mxStorage->openStreamElement( rElementName, ::com::sun::star::embed::ElementModes::READ ), UNO_QUERY );
    }
    catch( Exception& )
    {
    }
    return xInStream;
}

Reference< XOutputStream > ZipStorage::implOpenOutputStream( const OUString& rElementName )
{
    Reference< XOutputStream > xOutStream;
    if( mxStorage.is() ) try
    {
        (void)rElementName;
        OSL_ENSURE( false, "ZipStorage::implOpenOutputStream - not implemented" );
    }
    catch( Exception& )
    {
    }
    return xOutStream;
}

// ============================================================================

} // namespace oox

