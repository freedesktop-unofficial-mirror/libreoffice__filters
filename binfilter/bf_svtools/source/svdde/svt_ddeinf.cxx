/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: svt_ddeinf.cxx,v $
 *
 *  $Revision: 1.2 $
 *
 *  last change: $Author: rt $ $Date: 2008-03-12 09:13:35 $
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


#define UNICODE

#include <string.h>
#include "ddeimp.hxx"
#include <bf_svtools/svdde.hxx>

namespace binfilter
{

// --- DdeInternal::InfCallback() ----------------------------------

#ifdef WNT
HDDEDATA CALLBACK DdeInternal::InfCallback(
                WORD, WORD, HCONV, HSZ, HSZ, HDDEDATA, DWORD, DWORD )
#else
#if defined ( MTW ) || ( defined ( GCC ) && defined ( OS2 )) || defined( ICC )
HDDEDATA CALLBACK __EXPORT DdeInternal::InfCallback(
                WORD, WORD, HCONV, HSZ, HSZ, HDDEDATA, DWORD, DWORD )
#else
HDDEDATA CALLBACK _export DdeInternal::InfCallback(
                WORD, WORD, HCONV, HSZ, HSZ, HDDEDATA, DWORD, DWORD )
#endif
#endif
{
    return (HDDEDATA)DDE_FNOTPROCESSED;
}

// --- DdeServiceList::DdeServiceList() ----------------------------

DdeServiceList::DdeServiceList( const String* pTopic )
{
    DWORD       hDdeInst = NULL;
    HCONVLIST   hConvList = NULL;
    HCONV       hConv = NULL;
    UINT        nStatus = DMLERR_NO_ERROR;
    HSZ         hTopic = NULL;

#ifndef OS2 // YD FIXME

    nStatus = DdeInitialize( &hDdeInst, (PFNCALLBACK) DdeInternal::InfCallback,
                             APPCLASS_STANDARD | APPCMD_CLIENTONLY |
                             CBF_FAIL_ALLSVRXACTIONS |
                             CBF_SKIP_ALLNOTIFICATIONS, 0L );

    if ( nStatus == DMLERR_NO_ERROR )
    {
        if ( pTopic )
        {
            LPCTSTR p = reinterpret_cast<LPCTSTR>(pTopic->GetBuffer());
#ifdef __MINGW32__
            hTopic = DdeCreateStringHandle( hDdeInst, const_cast<LPTSTR>(p), CP_WINUNICODE );
#else
            hTopic = DdeCreateStringHandle( hDdeInst, p, CP_WINUNICODE );
#endif
        }

        hConvList = DdeConnectList( hDdeInst, NULL, hTopic, NULL, NULL );
        nStatus = DdeGetLastError( hDdeInst );
    }

    if ( nStatus == DMLERR_NO_ERROR )
    {
        while ( ( hConv = DdeQueryNextServer( hConvList, hConv ) ) != NULL)
        {
            CONVINFO    aInf;
            TCHAR       buf[256], *p;
            HSZ         h;
#ifdef OS2
            aInf.nSize = sizeof( aInf );
#else
            aInf.cb = sizeof( aInf );
#endif
            if( DdeQueryConvInfo( hConv, QID_SYNC, &aInf))
            {
                h = aInf.hszServiceReq;
                if ( !h )
#ifndef OS2
                    h = aInf.hszSvcPartner;
#else
                    h = aInf.hszPartner;
#endif
                DdeQueryString( hDdeInst, h, buf, sizeof(buf) / sizeof(TCHAR), CP_WINUNICODE );
                p = buf + lstrlen( buf );
                *p++ = '|'; *p = 0;
                DdeQueryString( hDdeInst, aInf.hszTopic, p, sizeof(buf)/sizeof(TCHAR)-lstrlen( buf ),
                                CP_WINUNICODE );
                aServices.Insert( new String( reinterpret_cast<const sal_Unicode*>(buf) ) );
            }
        }
        DdeDisconnectList( hConvList );
    }

    if ( hTopic)
        DdeFreeStringHandle( hDdeInst, hTopic );
    if ( hDdeInst )
        DdeUninitialize( hDdeInst );

#endif

}

// --- DdeServiceList::~DdeServiceList() ---------------------------

DdeServiceList::~DdeServiceList()
{
    String* s;
    while ( ( s = aServices.First() ) != NULL )
    {
        aServices.Remove( s );
        delete s;
    }
}

// --- DdeTopicList::DdeTopicList() --------------------------------

DdeTopicList::DdeTopicList( const String& rService )
{
    DdeConnection aSys( rService, String( reinterpret_cast<const sal_Unicode*>(SZDDESYS_TOPIC) ) );

    if ( !aSys.GetError() )
    {
        DdeRequest aReq( aSys, String( reinterpret_cast<const sal_Unicode*>(SZDDESYS_ITEM_TOPICS) ), 500 );
        aReq.SetDataHdl( LINK( this, DdeTopicList, Data ) );
        aReq.Execute();
    }
}

// --- DdeTopicList::~DdeTopicList() -------------------------------

DdeTopicList::~DdeTopicList()
{
    String* s;
    while ( ( s = aTopics.First() ) != NULL )
    {
        aTopics.Remove( s );
        delete s;
    }
}

// --- DdeTopicList::Data() --------------------------------------------

IMPL_LINK( DdeTopicList, Data, DdeData*, pData )
{
    char*   p = (char*) (const void *) *pData;
    char*   q = p;
    short   i;
    char    buf[256];

    while ( *p && *p != '\r' && *p != '\n' )
    {
        q = buf; i = 0;
        while ( i < 255 && *p && *p != '\r' && *p != '\n' && *p != '\t' )
            *q++ = *p++, i++;
        *q = 0;
        while ( *p && *p != '\r' && *p != '\n' && *p != '\t' )
            p++;
        aTopics.Insert( new String( String::CreateFromAscii(buf) ) );
        if ( *p == '\t' )
            p++;
    }
    return 0;
}

}
