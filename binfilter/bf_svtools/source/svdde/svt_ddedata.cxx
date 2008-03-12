/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: svt_ddedata.cxx,v $
 *
 *  $Revision: 1.2 $
 *
 *  last change: $Author: rt $ $Date: 2008-03-12 09:12:53 $
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

// MARKER(update_precomp.py): autogen include statement, do not remove


// ACHTUNG: es wird angenommen, dass StarView-Clipboard-Foamatnummern
// und Windows-Formatnummern identisch sind! Ist dies einmal nicht der
// Fall, muessen die Routinen hier angepasst werden. Die Implementation
// verwendet die hier defineirten Konversionen.

#define UNICODE

#include <string.h>
#include "ddeimp.hxx"
#include <bf_svtools/svdde.hxx>

#include <osl/thread.h>

#if defined( WIN ) && defined( MSC )
#pragma code_seg( "SVDDE_MISC_CODE" )
#endif

namespace binfilter
{

// --- DdeData::DdeData() ------------------------------------------

DdeData::DdeData()
{
    pImp = new DdeDataImp;
    pImp->hData = NULL;
    pImp->nData = 0;
    pImp->pData = NULL;
    pImp->nFmt  = CF_TEXT;
}

// --- DdeData::DdeData() ------------------------------------------

DdeData::DdeData( const void* p, long n, ULONG f )
{
    pImp = new DdeDataImp;
    pImp->hData = NULL;
    pImp->pData = (LPBYTE)p;
    pImp->nData = n;
    pImp->nFmt  = f;
}

// --- DdeData::DdeData() ------------------------------------------

DdeData::DdeData( const String& s )
{
    pImp = new DdeDataImp;
    pImp->hData = NULL;
    pImp->pData = (LPBYTE)s.GetBuffer();
    pImp->nData = s.Len()+1;
    pImp->nFmt  = CF_TEXT;
}

// --- DdeData::DdeData() ------------------------------------------

DdeData::DdeData( const DdeData& rData )
{
    pImp = new DdeDataImp;
    pImp->hData = rData.pImp->hData;
    pImp->nData = rData.pImp->nData;
    pImp->pData = rData.pImp->pData;
    pImp->nFmt  = rData.pImp->nFmt;
    Lock();
}

// --- DdeData::~DdeData() -----------------------------------------

DdeData::~DdeData()
{
    if ( pImp && pImp->hData )
        DdeUnaccessData( pImp->hData );
    delete pImp;
}

// --- DdeData::Lock() ---------------------------------------------

void DdeData::Lock()
{
    if ( pImp->hData )
        pImp->pData = DdeAccessData( pImp->hData, (LPDWORD) &pImp->nData );
}

// --- DdeData::GetFormat() ----------------------------------------

ULONG DdeData::GetFormat() const
{
    return pImp->nFmt;
}

void DdeData::SetFormat( ULONG nFmt )
{
    pImp->nFmt = nFmt;
}

// --- DdeData::operator const char*() -----------------------------

DdeData::operator const void*() const
{
    return pImp->pData;
}

// --- DdeData::operator long() ------------------------------------

DdeData::operator long() const
{
    return pImp->nData;
}

// --- DdeData::operator =() ---------------------------------------

DdeData& DdeData::operator = ( const DdeData& rData )
{
    if ( &rData != this )
    {
        DdeData tmp( rData );
        delete pImp;
        pImp = tmp.pImp;
        tmp.pImp = NULL;
    }

    return *this;
}

ULONG DdeData::GetExternalFormat( ULONG nFmt )
{
    switch( nFmt )
    {
    case FORMAT_STRING:
        nFmt = CF_TEXT;
        break;
    case FORMAT_BITMAP:
        nFmt = CF_BITMAP;
        break;
    case FORMAT_GDIMETAFILE:
        nFmt = CF_METAFILEPICT;
        break;

    default:
        {
#if defined(WNT) || defined(WIN) || defined( PM2 )
            String aName( SotExchange::GetFormatName( nFmt ) );

#if defined(WNT) || defined(WIN)

            if( aName.Len() )
                nFmt = RegisterClipboardFormat( reinterpret_cast<LPCWSTR>(aName.GetBuffer()) );
#endif
#if defined( PM2 )

            if( aName.Len() )
            {
                HATOMTBL hSysTable = WinQuerySystemAtomTable();
                nFmt = (ULONG)WinAddAtom( hSysTable, (PSZ)aName.GetBuffer() );
            }
#endif
#endif
        }
    }
    return nFmt;
}

ULONG DdeData::GetInternalFormat( ULONG nFmt )
{
    switch( nFmt )
    {
    case CF_TEXT:
        nFmt = FORMAT_STRING;
        break;

    case CF_BITMAP:
        nFmt = FORMAT_BITMAP;
        break;

    case CF_METAFILEPICT:
        nFmt = FORMAT_GDIMETAFILE;
        break;

    default:
#if defined(WIN) || defined(WNT)
        if( nFmt >= CF_MAX )
        {
            TCHAR szName[ 256 ];

            if( GetClipboardFormatName( nFmt, szName, sizeof(szName) ) )
                nFmt = SotExchange::RegisterFormatName( String(reinterpret_cast<const sal_Unicode*>(szName)) );
        }
#endif
#if defined(PM2)
        if( nFmt > CF_PALETTE )
        {
            char szName[ 256 ];

            HATOMTBL hSysTable = WinQuerySystemAtomTable();
            WinQueryAtomName( hSysTable, (ATOM)nFmt, (PSZ)szName,
                                sizeof( szName ) );
            nFmt = SotExchange::RegisterFormatName( String( szName ) );
        }
#endif
        break;
    }
    return nFmt;
}
}

