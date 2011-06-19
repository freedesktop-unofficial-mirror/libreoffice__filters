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

#include <bf_svtools/cntnrsrt.hxx>

#include "xmlnmspe.hxx"
#include "fonthdl.hxx"

#include "xmlexp.hxx"
namespace binfilter {

using namespace ::rtl;
using namespace ::com::sun::star::uno;
using namespace ::binfilter::xmloff::token;

int XMLFontAutoStylePoolNameCmp_Impl( const OUString& r1,
                                      const OUString& r2 )
{
    return (int)r1.compareTo( r2 );
}

DECLARE_CONTAINER_SORT_DEL( XMLFontAutoStylePoolNames_Impl,
                            OUString )
IMPL_CONTAINER_SORT( XMLFontAutoStylePoolNames_Impl,
                     OUString,
                     XMLFontAutoStylePoolNameCmp_Impl )

class XMLFontAutoStylePoolEntry_Impl
{
    OUString	sName;
    OUString	sFamilyName;
    OUString	sStyleName;
    sal_Int16	nFamily;
    sal_Int16	nPitch;
    rtl_TextEncoding eEnc;

public:

    inline XMLFontAutoStylePoolEntry_Impl(
            const ::rtl::OUString& rName,
            const ::rtl::OUString& rFamilyName,
            const ::rtl::OUString& rStyleName,
            sal_Int16 nFamily,
            sal_Int16 nPitch,
            rtl_TextEncoding eEnc );

    inline XMLFontAutoStylePoolEntry_Impl(
            const ::rtl::OUString& rFamilyName,
            const ::rtl::OUString& rStyleName,
            sal_Int16 nFamily,
            sal_Int16 nPitch,
            rtl_TextEncoding eEnc );

    const OUString&	GetName() const { return sName; }
    const OUString&	GetFamilyName() const { return sFamilyName; }
    const OUString&	GetStyleName() const { return sStyleName; }
    sal_Int16 GetFamily() const {	return nFamily; }
    sal_Int16 GetPitch() const { return nPitch; }
    rtl_TextEncoding GetEncoding() const { return eEnc; }
};


inline XMLFontAutoStylePoolEntry_Impl::XMLFontAutoStylePoolEntry_Impl(
        const ::rtl::OUString& rName,
        const ::rtl::OUString& rFamilyName,
        const ::rtl::OUString& rStyleName,
        sal_Int16 nFam,
        sal_Int16 nP,
        rtl_TextEncoding eE ) :
    sName( rName ),
    sFamilyName( rFamilyName ),
    sStyleName( rStyleName ),
    nFamily( nFam ),
    nPitch( nP ),
    eEnc( eE )
{
}

inline XMLFontAutoStylePoolEntry_Impl::XMLFontAutoStylePoolEntry_Impl(
        const ::rtl::OUString& rFamilyName,
        const ::rtl::OUString& rStyleName,
        sal_Int16 nFam,
        sal_Int16 nP,
        rtl_TextEncoding eE ) :
    sFamilyName( rFamilyName ),
    sStyleName( rStyleName ),
    nFamily( nFam ),
    nPitch( nP ),
    eEnc( eE )
{
}
int XMLFontAutoStylePoolEntryCmp_Impl(
        const XMLFontAutoStylePoolEntry_Impl& r1,
        const XMLFontAutoStylePoolEntry_Impl& r2 )
{
    sal_Int8 nEnc1(r1.GetEncoding() != RTL_TEXTENCODING_SYMBOL);
    sal_Int8 nEnc2(r2.GetEncoding() != RTL_TEXTENCODING_SYMBOL);
    if( nEnc1 != nEnc2 )
        return nEnc1 - nEnc2;
    else if( r1.GetPitch() != r2.GetPitch() )
        return (int)r1.GetPitch() - (int)r2.GetPitch();
    else if( r1.GetFamily() != r2.GetFamily() )
        return (int)r1.GetFamily() - (int)r2.GetFamily();
    else
    {
        sal_Int32 nCmp = r1.GetFamilyName().compareTo( r2.GetFamilyName() );
        if( 0 == nCmp )
            return (int)r1.GetStyleName().compareTo( r2.GetStyleName() );
        else
            return (int)nCmp;
    }
}

typedef XMLFontAutoStylePoolEntry_Impl *XMLFontAutoStylePoolEntryPtr;
DECLARE_CONTAINER_SORT_DEL( XMLFontAutoStylePool_Impl,
                            XMLFontAutoStylePoolEntry_Impl )
IMPL_CONTAINER_SORT( XMLFontAutoStylePool_Impl,
                     XMLFontAutoStylePoolEntry_Impl,
                     XMLFontAutoStylePoolEntryCmp_Impl )

XMLFontAutoStylePool::XMLFontAutoStylePool( SvXMLExport& rExp ) :
    rExport( rExp ),
    pPool( new XMLFontAutoStylePool_Impl( 5, 5 ) ),
    pNames( new XMLFontAutoStylePoolNames_Impl( 5, 5 ) )
{
}

XMLFontAutoStylePool::~XMLFontAutoStylePool()
{
    delete pPool;
    delete pNames;
}

OUString XMLFontAutoStylePool::Add(
            const OUString& rFamilyName,
            const OUString& rStyleName,
            sal_Int16 nFamily,
            sal_Int16 nPitch,
            rtl_TextEncoding eEnc )
{
    OUString sName;
    XMLFontAutoStylePoolEntry_Impl aTmp( rFamilyName, rStyleName, nFamily,
                                          nPitch, eEnc );
    ULONG nPos;
    if( pPool->Seek_Entry( &aTmp, &nPos ) )
    {
        sName = pPool->GetObject( nPos )->GetName();
    }
    else
    {
        OUString sLclName;
        sal_Int32 nLen = rFamilyName.indexOf( sal_Unicode(';'), 0 );
        if( -1 == nLen )
        {
            sLclName = rFamilyName;
        }
        else if( nLen > 0 )
        {
            sLclName = rFamilyName.copy( 0, nLen );
            sLclName.trim();
        }

        if( !sLclName.getLength() )
            sLclName = OUString::valueOf( sal_Unicode( 'F' ) );

        if( pNames->Seek_Entry( &sLclName, 0 ) )
        {
            sal_Int32 nCount = 1;
            OUString sPrefix( sLclName );
            sLclName += OUString::valueOf( nCount );
            while( pNames->Seek_Entry( &sLclName, 0 ) )
            {
                sLclName = sPrefix;
                sLclName += OUString::valueOf( ++nCount );
            }
        }

        XMLFontAutoStylePoolEntry_Impl *pEntry =
            new XMLFontAutoStylePoolEntry_Impl( sLclName, rFamilyName, rStyleName,
                                                nFamily, nPitch, eEnc );
        pPool->Insert( pEntry );
        pNames->Insert( new OUString( sLclName ) );
    }

    return sName;
}

::rtl::OUString XMLFontAutoStylePool::Find(
            const OUString& rFamilyName,
            const OUString& rStyleName,
            sal_Int16 nFamily,
            sal_Int16 nPitch,
            rtl_TextEncoding eEnc ) const
{
    OUString sName;
    XMLFontAutoStylePoolEntry_Impl aTmp( rFamilyName, rStyleName, nFamily,
                                          nPitch, eEnc );
    ULONG nPos;
    if( pPool->Seek_Entry( &aTmp, &nPos ) )
    {
        sName = pPool->GetObject( nPos )->GetName();
    }

    return sName;
}


void XMLFontAutoStylePool::exportXML()
{
    SvXMLElementExport aElem( GetExport(), XML_NAMESPACE_OFFICE,
                              XML_FONT_DECLS,
                              sal_True, sal_True );
    Any aAny;
    OUString sTmp;
    XMLFontFamilyNamePropHdl aFamilyNameHdl;
    XMLFontFamilyPropHdl aFamilyHdl;
    XMLFontPitchPropHdl aPitchHdl;
    XMLFontEncodingPropHdl aEncHdl;
    const SvXMLUnitConverter& rUnitConv = GetExport().GetMM100UnitConverter();

    sal_uInt32 nCount = pPool->Count();
    for( sal_uInt32 i=0; i<nCount; i++ )
    {
        const XMLFontAutoStylePoolEntry_Impl *pEntry = pPool->GetObject( i );

        GetExport().AddAttribute( XML_NAMESPACE_STYLE,
                                  XML_NAME, pEntry->GetName() );

        aAny <<= pEntry->GetFamilyName();
        if( aFamilyNameHdl.exportXML( sTmp, aAny, rUnitConv ) )
            GetExport().AddAttribute( XML_NAMESPACE_FO,
                                      XML_FONT_FAMILY, sTmp );

        const OUString& rStyleName = pEntry->GetStyleName();
        if( rStyleName.getLength() )
            GetExport().AddAttribute( XML_NAMESPACE_STYLE,
                                      XML_FONT_STYLE_NAME,
                                      rStyleName );

        aAny <<= (sal_Int16)pEntry->GetFamily();
        if( aFamilyHdl.exportXML( sTmp, aAny, rUnitConv  ) )
            GetExport().AddAttribute( XML_NAMESPACE_STYLE,
                                      XML_FONT_FAMILY_GENERIC, sTmp );

        aAny <<= (sal_Int16)pEntry->GetPitch();
        if( aPitchHdl.exportXML( sTmp, aAny, rUnitConv  ) )
            GetExport().AddAttribute( XML_NAMESPACE_STYLE,
                                      XML_FONT_PITCH, sTmp );

        aAny <<= (sal_Int16)pEntry->GetEncoding();
        if( aEncHdl.exportXML( sTmp, aAny, rUnitConv  ) )
            GetExport().AddAttribute( XML_NAMESPACE_STYLE,
                                      XML_FONT_CHARSET, sTmp );

        SvXMLElementExport aAnotherElem( GetExport(), XML_NAMESPACE_STYLE,
                                  XML_FONT_DECL,
                                  sal_True, sal_True );
    }
}


}//end of namespace binfilter

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
