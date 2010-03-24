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


#ifndef _COM_SUN_STAR_XML_ATTRIBUTEDATA_HPP_
#include <com/sun/star/xml/AttributeData.hpp>
#endif

#ifndef _RTL_USTRBUF_HXX_
#include <rtl/ustrbuf.hxx>
#endif

#ifndef _RTL_UUID_H_
#include <rtl/uuid.h>
#endif

#ifndef _RTL_MEMORY_H_
#include <rtl/memory.h>
#endif

#include "xmlcnimp.hxx"

#include "unoatrcn.hxx"
namespace binfilter {

using namespace ::rtl;
using namespace ::com::sun::star;

// --------------------------------------------------------------------
// Interface implementation
// --------------------------------------------------------------------

#define IMPL	((AttrContainerImpl*)mpData)

uno::Reference< uno::XInterface >  SvUnoAttributeContainer_CreateInstance()
{
    return *(new SvUnoAttributeContainer);
}

SvUnoAttributeContainer::SvUnoAttributeContainer( SvXMLAttrContainerData* pContainer)
: mpContainer( pContainer )
{
    if( mpContainer == NULL )
        mpContainer = new SvXMLAttrContainerData;
}

SvUnoAttributeContainer::~SvUnoAttributeContainer()
{
    delete mpContainer;
}

// container::XElementAccess
uno::Type SAL_CALL SvUnoAttributeContainer::getElementType(void)
    throw( uno::RuntimeException )
{
    return ::getCppuType((const xml::AttributeData*)0);
}

sal_Bool SAL_CALL SvUnoAttributeContainer::hasElements(void)
    throw( uno::RuntimeException )
{
    return mpContainer->GetAttrCount();
}

sal_uInt16 SvUnoAttributeContainer::getIndexByName(const OUString& aName ) const
{
    const sal_uInt16 nAttrCount = mpContainer->GetAttrCount();

    sal_Int32 nPos = aName.indexOf( sal_Unicode(':') );
    if( nPos == -1L )
    {
        for( sal_uInt16 nAttr = 0; nAttr < nAttrCount; nAttr++ )
        {
            if( mpContainer->GetAttrLName(nAttr) == aName &&
                mpContainer->GetAttrPrefix(nAttr).getLength() == 0L )
                return nAttr;
        }
    }
    else
    {
        const OUString aPrefix( aName.copy( 0L, nPos ) );
        const OUString aLName( aName.copy( nPos+1L ) );

        for( sal_uInt16 nAttr = 0; nAttr < nAttrCount; nAttr++ )
        {
            if( mpContainer->GetAttrLName(nAttr) == aLName &&
                mpContainer->GetAttrPrefix(nAttr) == aPrefix )
                return nAttr;
        }
    }

    return USHRT_MAX;
}

const ::com::sun::star::uno::Sequence< sal_Int8 > & SvUnoAttributeContainer::getUnoTunnelId() throw()
{
    static ::com::sun::star::uno::Sequence< sal_Int8 > * pSeq = 0;
    if( !pSeq )
    {
        ::osl::Guard< ::osl::Mutex > aGuard( ::osl::Mutex::getGlobalMutex() );
        if( !pSeq )
        {
            static ::com::sun::star::uno::Sequence< sal_Int8 > aSeq( 16 );
            rtl_createUuid( (sal_uInt8*)aSeq.getArray(), 0, sal_True );
            pSeq = &aSeq;
        }
    }
    return *pSeq;
}

sal_Int64 SAL_CALL SvUnoAttributeContainer::getSomething( const ::com::sun::star::uno::Sequence< sal_Int8 >& rId ) throw(::com::sun::star::uno::RuntimeException)
{
    if( rId.getLength() == 16 && 0 == rtl_compareMemory( getUnoTunnelId().getConstArray(),
                                                         rId.getConstArray(), 16 ) )
    {
        return (sal_Int64)this;
    }
    return 0;
}

// container::XNameAccess
uno::Any SAL_CALL SvUnoAttributeContainer::getByName(const OUString& aName)
    throw( container::NoSuchElementException, lang::WrappedTargetException, uno::RuntimeException )
{
    sal_uInt16 nAttr = getIndexByName(aName );

    if( nAttr == USHRT_MAX )
        throw container::NoSuchElementException();

    xml::AttributeData aData;
    aData.Namespace = mpContainer->GetAttrNamespace(nAttr);
    aData.Type = OUString::createFromAscii("CDATA");
    aData.Value = mpContainer->GetAttrValue(nAttr);

    uno::Any aAny;
    aAny <<= aData;
    return aAny;
}

uno::Sequence< OUString > SAL_CALL SvUnoAttributeContainer::getElementNames(void) throw( uno::RuntimeException )
{
    const sal_uInt16 nAttrCount = mpContainer->GetAttrCount();

    uno::Sequence< OUString > aElementNames( (sal_Int32)nAttrCount );
    OUString *pNames = aElementNames.getArray();

    for( sal_uInt16 nAttr = 0; nAttr < nAttrCount; nAttr++ )
    {
        OUStringBuffer sBuffer( mpContainer->GetAttrPrefix(nAttr) );
        if( sBuffer.getLength() != 0L )
            sBuffer.append( (sal_Unicode)':' );
        sBuffer.append( mpContainer->GetAttrLName(nAttr) );
        *pNames++ = sBuffer.makeStringAndClear();
    }

    return aElementNames;
}

sal_Bool SAL_CALL SvUnoAttributeContainer::hasByName(const OUString& aName) throw( uno::RuntimeException )
{
    return getIndexByName(aName ) != USHRT_MAX;
}

// container::XNameReplace
void SAL_CALL SvUnoAttributeContainer::replaceByName(const OUString& aName, const uno::Any& aElement)
    throw( lang::IllegalArgumentException, container::NoSuchElementException, lang::WrappedTargetException, uno::RuntimeException )
{
    if( aElement.hasValue() && aElement.getValueType() == ::getCppuType((const xml::AttributeData*)0) )
    {
        sal_uInt16 nAttr = getIndexByName(aName );
        if( nAttr == USHRT_MAX )
            throw container::NoSuchElementException();

        xml::AttributeData* pData = (xml::AttributeData*)aElement.getValue();

        sal_Int32 nPos = aName.indexOf( sal_Unicode(':') );
        if( nPos != -1L )
        {
            const OUString aPrefix( aName.copy( 0L, nPos ));
            const OUString aLName( aName.copy( nPos+1L ));

            if( pData->Namespace.getLength() == 0L )
            {
                if( mpContainer->SetAt( nAttr, aPrefix, aLName, pData->Value ) )
                    return;
            }
            else
            {
                if( mpContainer->SetAt( nAttr, aPrefix, pData->Namespace, aLName, pData->Value ) )
                    return;
            }
        }
        else
        {
            if( pData->Namespace.getLength() == 0L )
            {
                if( mpContainer->SetAt( nAttr, aName, pData->Value ) )
                    return;
            }
        }
    }

    throw lang::IllegalArgumentException();
}

// container::XNameContainer
void SAL_CALL SvUnoAttributeContainer::insertByName(const OUString& aName, const uno::Any& aElement)
throw( lang::IllegalArgumentException, container::ElementExistException, lang::WrappedTargetException, uno::RuntimeException )
{
    if( !aElement.hasValue() || aElement.getValueType() != ::getCppuType((const xml::AttributeData*)0) )
        throw lang::IllegalArgumentException();

    sal_uInt16 nAttr = getIndexByName(aName );
    if( nAttr != USHRT_MAX )
        throw container::ElementExistException();

    xml::AttributeData* pData = (xml::AttributeData*)aElement.getValue();

    sal_Int32 nPos = aName.indexOf( sal_Unicode(':') );
    if( nPos != -1L )
    {
        const OUString aPrefix( aName.copy( 0L, nPos ));
        const OUString aLName( aName.copy( nPos+1L ));

        if( pData->Namespace.getLength() == 0L )
        {
            if( mpContainer->AddAttr( aPrefix, aLName, pData->Value ) )
                return;
        }
        else
        {
            if( mpContainer->AddAttr( aPrefix, pData->Namespace, aLName, pData->Value ) )
                return;
        }
    }
    else
    {
        if( pData->Namespace.getLength() == 0L )
        {
            if( mpContainer->AddAttr( aName, pData->Value ) )
                return;
        }
    }
}

void SAL_CALL SvUnoAttributeContainer::removeByName(const OUString& Name)
    throw( container::NoSuchElementException, lang::WrappedTargetException, uno::RuntimeException )
{
    sal_uInt16 nAttr = getIndexByName(Name);
    if( nAttr == USHRT_MAX )
        throw container::NoSuchElementException();

    mpContainer->Remove( nAttr );
}

//XServiceInfo
OUString SAL_CALL SvUnoAttributeContainer::getImplementationName(void) throw( uno::RuntimeException )
{
    return OUString::createFromAscii( "SvUnoAttributeContainer" );
}

uno::Sequence< OUString > SvUnoAttributeContainer::getSupportedServiceNames(void)
    throw( uno::RuntimeException )
{
    OUString aSN( OUString::createFromAscii( "com.sun.star.xml.AttributeContainer" ) );
    uno::Sequence< OUString > aNS( &aSN, 1L );
    return aNS;
}

sal_Bool SvUnoAttributeContainer::supportsService(const OUString& ServiceName)
    throw( uno::RuntimeException )
{
    const uno::Sequence < OUString > aServiceNames( getSupportedServiceNames() );
    const OUString* pNames = aServiceNames.getConstArray();
    sal_Int32 nCount = aServiceNames.getLength();
    while( nCount-- )
    {
        if( *pNames++ == ServiceName )
            return sal_True;
    }

    return sal_False;
}


}//end of namespace binfilter
