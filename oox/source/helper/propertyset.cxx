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

#include "oox/helper/propertyset.hxx"
#include <rtl/strbuf.hxx>
#include <osl/diagnose.h>
#include "oox/helper/propertymap.hxx"

using ::rtl::OUString;
using ::rtl::OStringBuffer;
using ::rtl::OUStringToOString;
using ::com::sun::star::uno::Any;
using ::com::sun::star::uno::Reference;
using ::com::sun::star::uno::Sequence;
using ::com::sun::star::uno::Exception;
using ::com::sun::star::uno::UNO_QUERY;
using ::com::sun::star::beans::XPropertySet;

namespace oox {

// ============================================================================

void PropertySet::set( const Reference< XPropertySet >& rxPropSet )
{
    mxPropSet = rxPropSet;
    mxMultiPropSet.set( mxPropSet, UNO_QUERY );
}

// Get properties -------------------------------------------------------------

Any PropertySet::getAnyProperty( sal_Int32 nPropId ) const
{
    Any aValue;
    return implGetPropertyValue( aValue, PropertyMap::getPropertyName( nPropId ) ) ? aValue : Any();
}

void PropertySet::getProperties( Sequence< Any >& orValues, const Sequence< OUString >& rPropNames ) const
{
    if( mxMultiPropSet.is() ) try
    {
        orValues = mxMultiPropSet->getPropertyValues( rPropNames );
        return;
    }
    catch( Exception& )
    {
        OSL_ENSURE( false, "PropertySet::getProperties - cannot get all property values - fallback to single mode" );
    }

    if( mxPropSet.is() )
    {
        sal_Int32 nLen = rPropNames.getLength();
        const OUString* pPropName = rPropNames.getConstArray();
        const OUString* pPropNameEnd = pPropName + nLen;
        orValues.realloc( nLen );
        Any* pValue = orValues.getArray();
        for( ; pPropName != pPropNameEnd; ++pPropName, ++pValue )
            implGetPropertyValue( *pValue, *pPropName );
    }
}

// Set properties -------------------------------------------------------------

bool PropertySet::setAnyProperty( sal_Int32 nPropId, const Any& rValue )
{
    return implSetPropertyValue( PropertyMap::getPropertyName( nPropId ), rValue );
}

void PropertySet::setProperties( const Sequence< OUString >& rPropNames, const Sequence< Any >& rValues )
{
    OSL_ENSURE( rPropNames.getLength() == rValues.getLength(),
        "PropertySet::setProperties - length of sequences different" );

    if( mxMultiPropSet.is() ) try
    {
        mxMultiPropSet->setPropertyValues( rPropNames, rValues );
        return;
    }
    catch( Exception& )
    {
        OSL_ENSURE( false, "PropertySet::setProperties - cannot set all property values, fallback to single mode" );
    }

    if( mxPropSet.is() )
    {
        const OUString* pPropName = rPropNames.getConstArray();
        const OUString* pPropNameEnd = pPropName + rPropNames.getLength();
        const Any* pValue = rValues.getConstArray();
        for( ; pPropName != pPropNameEnd; ++pPropName, ++pValue )
            implSetPropertyValue( *pPropName, *pValue );
    }
}

void PropertySet::setProperties( const PropertyMap& rPropertyMap )
{
    if( !rPropertyMap.empty() )
    {
        Sequence< OUString > aPropNames;
        Sequence< Any > aValues;
        rPropertyMap.fillSequences( aPropNames, aValues );
        setProperties( aPropNames, aValues );
    }
}

// private --------------------------------------------------------------------

bool PropertySet::implGetPropertyValue( Any& orValue, const OUString& rPropName ) const
{
    if( mxPropSet.is() ) try
    {
        orValue = mxPropSet->getPropertyValue( rPropName );
        return true;
    }
    catch( Exception& )
    {
        OSL_ENSURE( false, OStringBuffer( "PropertySet::implGetPropertyValue - cannot get property \"" ).
            append( OUStringToOString( rPropName, RTL_TEXTENCODING_ASCII_US ) ).append( '"' ).getStr() );
    }
    return false;
}

bool PropertySet::implSetPropertyValue( const OUString& rPropName, const Any& rValue )
{
    if( mxPropSet.is() ) try
    {
        mxPropSet->setPropertyValue( rPropName, rValue );
        return true;
    }
    catch( Exception& )
    {
        OSL_ENSURE( false, OStringBuffer( "PropertySet::implSetPropertyValue - cannot set property \"" ).
            append( OUStringToOString( rPropName, RTL_TEXTENCODING_ASCII_US ) ).append( '"' ).getStr() );
    }
    return false;
}

#if OSL_DEBUG_LEVEL > 0
void PropertySet::dump()
{
    PropertyMap::dump( Reference< XPropertySet >( getXPropertySet(), UNO_QUERY ) );
}
#endif

// ============================================================================

} // namespace oox

