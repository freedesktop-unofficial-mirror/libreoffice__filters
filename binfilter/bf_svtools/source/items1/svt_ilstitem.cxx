/* -*- Mode: C++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */
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

// MARKER(update_precomp.py): autogen include statement, do not remove


#include <com/sun/star/script/XTypeConverter.hpp>
#include <com/sun/star/lang/XMultiServiceFactory.hpp>

#include <comphelper/processfactory.hxx>

#include <bf_svtools/ilstitem.hxx>

#define _SVSTDARR_ULONGS
#include <bf_svtools/svstdarr.hxx>

namespace binfilter
{

TYPEINIT1_AUTOFACTORY(SfxIntegerListItem, SfxPoolItem);

SfxIntegerListItem::SfxIntegerListItem()
{
}

SfxIntegerListItem::SfxIntegerListItem( const SfxIntegerListItem& rItem )
    : SfxPoolItem( rItem )
{
    m_aList = rItem.m_aList;
}

SfxIntegerListItem::~SfxIntegerListItem()
{
}

int SfxIntegerListItem::operator==( const SfxPoolItem& rPoolItem ) const
{
    if ( !rPoolItem.ISA( SfxIntegerListItem ) )
        return FALSE;

    const SfxIntegerListItem rItem = (const SfxIntegerListItem&) rPoolItem;
    return rItem.m_aList == m_aList;
}

SfxPoolItem* SfxIntegerListItem::Clone( SfxItemPool * ) const
{
    return new SfxIntegerListItem( *this );
}

bool SfxIntegerListItem::PutValue  ( const com::sun::star::uno::Any& rVal, BYTE )
{
    ::com::sun::star::uno::Reference < ::com::sun::star::script::XTypeConverter > xConverter
            ( ::comphelper::getProcessServiceFactory()->createInstance(::rtl::OUString( RTL_CONSTASCII_USTRINGPARAM( "com.sun.star.script.Converter" ))),
            ::com::sun::star::uno::UNO_QUERY );
    ::com::sun::star::uno::Any aNew;
    try { aNew = xConverter->convertTo( rVal, ::getCppuType((const ::com::sun::star::uno::Sequence < sal_Int32 >*)0) ); }
    catch (::com::sun::star::uno::Exception&)
    {
        return false;
    }

    return ( aNew >>= m_aList );
}

bool SfxIntegerListItem::QueryValue( com::sun::star::uno::Any& rVal, BYTE ) const
{
    rVal <<= m_aList;
    return true;
}

}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
