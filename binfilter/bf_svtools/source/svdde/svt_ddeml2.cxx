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

#define INCL_DOS
#include <stdlib.h>

#include "ddemlimp.hxx"
#define LOGFILE
#define STATUSFILE
#define DDEDATAFILE
#include "ddemldeb.hxx"

#if defined (OS2) && defined (__BORLANDC__)
#pragma option -w-par
#endif

namespace binfilter
{

// ************************************************************************
// Hilfsfunktionen Speicherverwaltung
// ************************************************************************

//
//  AllocAtomName
//

PSZ ImpDdeMgr::AllocAtomName( ATOM hString, ULONG& rBufLen )
{
    HATOMTBL hAtomTable = WinQuerySystemAtomTable();
    ULONG nLen = WinQueryAtomLength( hAtomTable, hString );
    nLen++;
    PSZ pBuf = 0;
    if ( !MyDosAllocMem( (PPVOID)&pBuf, nLen, PAG_READ|PAG_WRITE|PAG_COMMIT | OBJ_ANY,"Atom" ) )
    {
        WinQueryAtomName( hAtomTable, hString, pBuf, nLen );
        rBufLen = nLen;
    }
    return pBuf;
}


//
//  MakeDDEObject
//

PDDESTRUCT ImpDdeMgr::MakeDDEObject( HWND hwnd, ATOM hItemName,
    USHORT fsStatus, USHORT usFormat, PVOID pabData, ULONG usDataLen )
{
    PDDESTRUCT	pddes = 0;
    ULONG		usItemLen;
    PULONG		pulSharedObj;

    PSZ pItemName = 0;
    if( hItemName != NULL )
        pItemName = AllocAtomName( hItemName, usItemLen );
    else
        usItemLen = 1;

    ULONG nTotalSize = sizeof(DDESTRUCT) + usItemLen + usDataLen;

    if( !(MyDosAllocSharedMem((PPVOID)&pulSharedObj, NULL,
            nTotalSize,
            PAG_COMMIT | PAG_READ | PAG_WRITE | OBJ_GETTABLE | OBJ_GIVEABLE | OBJ_ANY,
            "MakeDDEObject")))
    {
        pddes = (PDDESTRUCT) pulSharedObj;
        // siehe "Glenn Puchtel, DDE for OS/2" p.60
        pddes->cbData = (ULONG)usDataLen;
        pddes->fsStatus = fsStatus;
        pddes->usFormat = usFormat;
        pddes->offszItemName = sizeof( DDESTRUCT );
        if( (usDataLen) && (pabData != NULL ) )
            pddes->offabData = sizeof(DDESTRUCT) + usItemLen;
        else
            pddes->offabData = 0;

        if( pItemName != NULL )
            memcpy(DDES_PSZITEMNAME(pddes), pItemName, usItemLen );
        else
            *(DDES_PSZITEMNAME(pddes)) = '\0';

        if( pabData != NULL )
            memcpy( DDES_PABDATA(pddes), pabData, usDataLen );
    }

    if ( pItemName )
    {
        MyDosFreeMem( pItemName,"MakeDDEObject" );
    }
    return pddes;
}

//
//  AllocNamedSharedMem
//

APIRET ImpDdeMgr::AllocNamedSharedMem( PPVOID ppBaseAddress, PSZ pName,
    ULONG nElementSize, ULONG nElementCount )
{
    ULONG nObjSize = (ULONG)(nElementSize * nElementCount );
    nObjSize += sizeof( ULONG );	// fuer ElementCount am Anfang des Blocks

    *ppBaseAddress = 0;
    APIRET nRet = MyDosAllocSharedMem( ppBaseAddress, pName, nObjSize,
                    PAG_READ | PAG_WRITE | PAG_COMMIT | OBJ_ANY,
                    "AllocNamedSharedMem" );
    if ( !nRet )
    {
        memset( *ppBaseAddress, 0, nObjSize );
        ULONG* pULONG = (ULONG*)*ppBaseAddress;
        *pULONG = nObjSize;
    }
    return nRet;
}

void ImpDdeMgr::CreateServerWnd()
{
    hWndServer = WinCreateWindow( HWND_DESKTOP, WC_FRAME, "DDEServer", 0,
        0,0,0,0, HWND_DESKTOP, HWND_BOTTOM, 0, 0,  0 );
    WinSetWindowULong( hWndServer, 0, (ULONG)this );
    WinSubclassWindow( hWndServer, ::ServerWndProc );
    TID tidDummy;
    WinQueryWindowProcess( hWndServer, &pidThis, &tidDummy );
}

void ImpDdeMgr::DestroyServerWnd()
{
    WinDestroyWindow( hWndServer );
    hWndServer = NULLHANDLE;
}

HWND ImpDdeMgr::CreateConversationWnd()
{
    HWND hWnd = WinCreateWindow( HWND_OBJECT, WC_FRAME, "DDEConvWnd", 0,
        0,0,0,0, HWND_DESKTOP, HWND_BOTTOM, 0, 0,  0 );
    if ( hWnd )
    {
        ImpConvWndData* pWndData = new ImpConvWndData;
        pWndData->pThis = this;
        pWndData->nRefCount = 0;
        WinSetWindowULong( hWnd, 0, (ULONG)pWndData );
        WinSubclassWindow( hWnd, ::ConvWndProc );
    }
    else
        nLastErrInstance = DMLERR_SYS_ERROR;

    return hWnd;
}

// static
void ImpDdeMgr::DestroyConversationWnd( HWND hWnd )
{
    ImpConvWndData* pObj = (ImpConvWndData*)WinQueryWindowULong( hWnd, 0 );
    if( pObj )
    {
        pObj->nRefCount--;
        if( pObj->nRefCount == 0
            // auch Windows mit Refcount vonm loeschen, da dieser in initial
            // auf 0 gesetzt wird
            || pObj->nRefCount == (USHORT)-1 )
        {
            delete pObj;
            WinDestroyWindow( hWnd );
        }
    }
#if defined( OV_DEBUG )
    else
    {
        WRITELOG("DestroyCnvWnd:Already destroyed/No win data/Partner died")
    }
#endif
}

// static
USHORT ImpDdeMgr::GetConversationWndRefCount( HWND hWnd )
{
    ImpConvWndData* pObj = (ImpConvWndData*)WinQueryWindowULong( hWnd, 0 );
    DBG_ASSERT(pObj,"Dde:ConvWnd has no data");
    if( pObj )
        return pObj->nRefCount;
    return 0;
}

// static
USHORT ImpDdeMgr::IncConversationWndRefCount( HWND hWnd )
{
    ImpConvWndData* pObj = (ImpConvWndData*)WinQueryWindowULong( hWnd, 0 );
    DBG_ASSERT(pObj,"Dde:ConvWnd has no data");
    if( pObj )
    {
        pObj->nRefCount++;
        return pObj->nRefCount;
    }
    return 0;
}

ImpDdeMgrData* ImpDdeMgr::InitAll()
{
    ImpDdeMgrData* pBase = 0;
    // nur dann neu anlegen, wenn die Tabelle nicht existiert
    APIRET nRet=DosGetNamedSharedMem((PPVOID)&pBase,DDEMLDATA,PAG_READ| PAG_WRITE);
    if ( nRet )
    {
        if ( nRet == 2 ) // ERROR_FILE_NOT_FOUND )
        {
            // DDECONVERSATIONCOUNT=4096
            USHORT nConvTransCount = 128;
            PSZ pResult;
            nRet = DosScanEnv( "SOMAXDDECONN", (const char**)&pResult );
            if( !nRet )
            {
                int nTemp = 0;
                nTemp = atoi( pResult );
                nTemp++; // der nullte Eintrag wird nicht benutzt
                if( nTemp > 128 )
                    nConvTransCount = (USHORT)nTemp;
            }
            ULONG nSize = sizeof(ImpDdeMgrData);
            nSize += sizeof(ImpHCONV) * nConvTransCount;
            nSize += sizeof(Transaction) * nConvTransCount;
            nSize += sizeof(HWND) * DDEMLAPPCOUNT;

            nRet = ImpDdeMgr::AllocNamedSharedMem( (PPVOID)&pBase,
                DDEMLDATA, nSize, 1 );
            if ( !nRet )
            {
                pBase->nTotalSize = nSize;
                ULONG nAppTable = (ULONG)&(pBase->aAppTable);
                ULONG nCharBase = (ULONG)pBase;
                pBase->nOffsAppTable =  nAppTable - nCharBase;
                pBase->nOffsConvTable = pBase->nOffsAppTable;
                pBase->nOffsConvTable += sizeof(HWND) * DDEMLAPPCOUNT;
                pBase->nOffsTransTable = pBase->nOffsConvTable;
                pBase->nOffsTransTable += sizeof(ImpHCONV) * nConvTransCount;

                pBase->nMaxAppCount = DDEMLAPPCOUNT;
                pBase->nMaxConvCount = nConvTransCount;
                pBase->nMaxTransCount = nConvTransCount;
            }
        }
    }

    if( pBase )
    {
        pConvTable	= ImpDdeMgr::GetConvTable( pBase );
        pTransTable = ImpDdeMgr::GetTransTable( pBase );
        pAppTable	= ImpDdeMgr::GetAppTable( pBase );
    }

    memset( &aDefaultContext, 0, sizeof(CONVCONTEXT) );
    aDefaultContext.cb = sizeof(CONVCONTEXT);
    aDefaultContext.idCountry = 49;  // ??
    aDefaultContext.usCodepage = 850;  // ??

    return pBase;
}

// static
HCONV ImpDdeMgr::CreateConvHandle( ImpDdeMgrData* pData,
    PID pidOwner,
    HWND hWndMe, HWND hWndPartner,
    HSZ hszPartner, HSZ hszServiceReq, HSZ hszTopic,
    HCONV hPrevHCONV )
{
    DBG_ASSERT(pData,"DDE:Invalid data");
    if( !pData )
        return (HCONV)0;

    ImpHCONV* pPtr = ImpDdeMgr::GetConvTable( pData );
    USHORT nCount = pData->nMaxConvCount;
    pPtr++;
    nCount--;  // ersten Handle (NULLHANDLE) ueberspringen
    USHORT nIdx = 1;
    DBG_ASSERT(pPtr,"No ConvTable");
    if( !pPtr )
        return (HCONV)0;

    while( nCount && pPtr->hWndThis != (HWND)NULL )
    {
        nCount--;
        pPtr++;
        nIdx++;
    }
    if( !nCount )
        return (HCONV)0;

    DdeKeepStringHandle( hszPartner );
    DdeKeepStringHandle( hszServiceReq );
    DdeKeepStringHandle( hszTopic );
    pPtr->hszPartner	= hszPartner;
    pPtr->hszServiceReq = hszServiceReq;
    pPtr->hszTopic		= hszTopic;

    pPtr->hWndThis		= hWndMe;
    pPtr->hWndPartner	= hWndPartner;
    pPtr->pidOwner		= pidOwner;
    pPtr->hConvPartner	= (HCONV)0;
    pPtr->nPrevHCONV	= (USHORT)hPrevHCONV;
    pPtr->nNextHCONV	= 0;
    pPtr->nStatus		= ST_CONNECTED;

    pData->nCurConvCount++;

    return (HCONV)nIdx;
}

// static
void ImpDdeMgr::FreeConvHandle( ImpDdeMgrData* pBase, HCONV hConv,
    BOOL bDestroyHWndThis )
{
    DBG_ASSERT(pBase,"DDE:No data");
    if( !pBase )
    {
        WRITELOG("FreeConvHandle: FAIL");
        return;
    }
    DBG_ASSERT(hConv&&hConv<pBase->nMaxConvCount,"DDE:Invalid Conv-Handle");
    if( hConv && hConv < pBase->nMaxConvCount )
    {
        ImpHCONV* pTable = ImpDdeMgr::GetConvTable( pBase );
        ImpHCONV* pPtr = pTable + (USHORT)hConv;
        if( pPtr->nStatus & ST_INLIST )
        {
            // Verkettung umsetzen
            USHORT nPrev = pPtr->nPrevHCONV;
            USHORT nNext = pPtr->nNextHCONV;
            if( nPrev )
            {
                pPtr = pTable + nPrev;
                pPtr->nNextHCONV = nNext;
            }
            if( nNext )
            {
                pPtr = pTable + nNext;
                pPtr->nPrevHCONV = nPrev;
            }
            pPtr = pTable + (USHORT)hConv;
        }

        DdeFreeStringHandle( pPtr->hszPartner );
        DdeFreeStringHandle( pPtr->hszServiceReq );
        DdeFreeStringHandle( pPtr->hszTopic	);
        if( bDestroyHWndThis )
            DestroyConversationWnd( pPtr->hWndThis );
        memset( pPtr, 0, sizeof(ImpHCONV) );
        DBG_ASSERT(pBase->nCurConvCount,"Dde:Invalid Trans. count");
        pBase->nCurConvCount--;
    }
#if defined(OV_DEBUG)
    else
    {
        WRITELOG("FreeConvHandle: FAIL");
    }
#endif
}

// static
HCONV ImpDdeMgr::IsConvHandleAvailable( ImpDdeMgrData* pBase )
{
    DBG_ASSERT(pBase,"DDE:No data");
    if( !pBase )
        return 0;

    ImpHCONV* pPtr = ImpDdeMgr::GetConvTable( pBase );
    USHORT nCurPos = pBase->nMaxConvCount - 1;
    pPtr += nCurPos;  // von hinten aufrollen
    while( nCurPos >= 1 )
    {
        if( pPtr->hWndThis == 0 )
            return TRUE;
         pPtr--;
         nCurPos--;
    }
    return FALSE;
}

// static
HCONV ImpDdeMgr::GetConvHandle( ImpDdeMgrData* pBase, HWND hWndThis,
    HWND hWndPartner )
{
    DBG_ASSERT(pBase,"DDE:No data");
    if( !pBase )
        return 0;
    ImpHCONV* pPtr = ImpDdeMgr::GetConvTable( pBase );
    USHORT nCurPos = 1;
    pPtr++;  // ersten Handle ueberspringen
    USHORT nCurConvCount = pBase->nCurConvCount;
    while( nCurConvCount && nCurPos < pBase->nMaxConvCount )
    {
        if( pPtr->hWndThis )
        {
            if(pPtr->hWndThis == hWndThis && pPtr->hWndPartner == hWndPartner)
                return (HCONV)nCurPos;
            nCurConvCount--;
            if( !nCurConvCount )
                return (HCONV)0;
        }
        nCurPos++;
        pPtr++;
    }
    return (HCONV)0;
}



// static
ULONG ImpDdeMgr::CreateTransaction( ImpDdeMgrData* pBase, HCONV hOwner,
    HSZ hszItem, USHORT nFormat, USHORT nTransactionType )
{
    DBG_ASSERT(pBase,"DDE:No Data");
    DBG_ASSERT(hOwner!=0,"DDE:No Owner");

    if( pBase && hOwner )
    {
        Transaction* pPtr = ImpDdeMgr::GetTransTable( pBase );
        DBG_ASSERT(pPtr->hConvOwner==0,"DDE:Data corrupted");
        USHORT nId = 1;
        pPtr++;
        while( nId < pBase->nMaxTransCount )
        {
            if( pPtr->hConvOwner == (HCONV)0 )
            {
                pPtr->hConvOwner = hOwner;
                DdeKeepStringHandle( hszItem );
                pPtr->hszItem = hszItem;
                pPtr->nType = nTransactionType;
                pPtr->nConvst = XST_CONNECTED;
                pPtr->nFormat = nFormat;
                pBase->nCurTransCount++;
                return (ULONG)nId;
            }
            nId++;
            pPtr++;
        }
    }
    return 0;
}

// static
void ImpDdeMgr::FreeTransaction( ImpDdeMgrData* pBase, ULONG nTransId )
{
    DBG_ASSERT(pBase,"DDE:No Data");
    if( !pBase )
        return;

    DBG_ASSERT(nTransId<pBase->nMaxTransCount,"DDE:Invalid TransactionId");
    if( nTransId >= pBase->nMaxTransCount )
        return;

    Transaction* pPtr = ImpDdeMgr::GetTransTable( pBase );
    pPtr += nTransId;
    DBG_ASSERT(pPtr->hConvOwner!=0,"DDE:TransId has no owner");
    if( pPtr->hConvOwner )
    {
        DdeFreeStringHandle( pPtr->hszItem );
        memset( pPtr, 0, sizeof(Transaction) );
        DBG_ASSERT(pBase->nCurTransCount,"Dde:Invalid Trans. count");
        pBase->nCurTransCount--;
    }
}

// static
ULONG ImpDdeMgr::GetTransaction( ImpDdeMgrData* pBase,
    HCONV hOwner, HSZ hszItem, USHORT nFormat )
{
    DBG_ASSERT(pBase,"DDE:No Data");
    if( !pBase || !hOwner )
        return 0;

    Transaction* pTrans = ImpDdeMgr::GetTransTable( pBase );
    DBG_ASSERT(pTrans,"DDE:No TransactionTable");
    if( !pTrans )
        return 0;
    pTrans++; // NULLHANDLE ueberspringen

    ImpHCONV* pConv = ImpDdeMgr::GetConvTable( pBase );
    pConv += (USHORT)hOwner;
    HCONV hConvPartner = pConv->hConvPartner;

    USHORT nCurTransCount = pBase->nCurTransCount;
    for( USHORT nTrans=1; nTrans< pBase->nMaxTransCount; nTrans++, pTrans++ )
    {
        if( pTrans->hConvOwner )
        {
            if(( pTrans->hConvOwner == hOwner ||
                 pTrans->hConvOwner == hConvPartner)	&&
                 pTrans->nFormat == nFormat 			&&
                 pTrans->hszItem == hszItem )
            {
                // gefunden!
                return (ULONG)nTrans;
            }
            nCurTransCount--;
            if( !nCurTransCount )
                return 0;
        }
    }
    return 0;  // narda
}

// static
HSZ ImpDdeMgr::DdeCreateStringHandle( PSZ pszString, int iCodePage)
{
    if( !pszString || *pszString == '\0' )
        return (HSZ)0;
    // Atom-Table beachtet Gross/Kleinschreibung, DDEML aber nicht

    HATOMTBL hAtomTable = WinQuerySystemAtomTable();
    ATOM aAtom = WinAddAtom( hAtomTable, pszString );
    return (HSZ)aAtom;
}

// static
ULONG ImpDdeMgr::DdeQueryString( HSZ hszStr, PSZ pszStr, ULONG cchMax, int iCodePage)
{
    HATOMTBL hAtomTable = WinQuerySystemAtomTable();
    if ( !pszStr )
        return WinQueryAtomLength( hAtomTable, (ATOM)hszStr);
    else
    {
        *pszStr = 0;
        return WinQueryAtomName( hAtomTable, (ATOM)hszStr, pszStr, cchMax );
    }
}

// static
BOOL ImpDdeMgr::DdeFreeStringHandle( HSZ hsz )
{
    if( !hsz )
        return FALSE;
    ATOM aResult = WinDeleteAtom( WinQuerySystemAtomTable(),(ATOM)hsz );
    return (BOOL)(aResult==0);
}

// static
BOOL ImpDdeMgr::DdeKeepStringHandle( HSZ hsz )
{
    if( !hsz )
        return TRUE;
    HATOMTBL hAtomTable = WinQuerySystemAtomTable();
#ifdef DBG_UTIL
    ULONG nUsageCount=WinQueryAtomUsage(hAtomTable,(ATOM)hsz);
#endif
    ULONG nAtom = 0xFFFF0000;
    ULONG nPar = (ULONG)hsz;
    nAtom |= nPar;
    ATOM aAtom = WinAddAtom( hAtomTable, (PSZ)nAtom );
#ifdef DBG_UTIL
    if ( aAtom )
        DBG_ASSERT(WinQueryAtomUsage(hAtomTable,(ATOM)hsz)==nUsageCount+1,"Keep failed");
#endif
    return (BOOL)(aAtom!=0);
}


// static
int ImpDdeMgr::DdeCmpStringHandles(HSZ hsz1, HSZ hsz2)
{
    if ( hsz1 == hsz2 )
        return 0;
    if ( hsz1 < hsz2 )
        return -1;
    return 1;
}

HDDEDATA ImpDdeMgr::DdeCreateDataHandle( void* pSrc, ULONG cb,
    ULONG cbOff, HSZ hszItem, USHORT wFmt, USHORT afCmd)
{
    char* pData = (char*)pSrc;
    pData += cbOff;
    USHORT nStatus;
    if( afCmd & HDATA_APPOWNED )
        nStatus = IMP_HDATAAPPOWNED;
    else
        nStatus = 0;
    PDDESTRUCT hData=MakeDDEObject(0,(ATOM)hszItem,nStatus,wFmt,pData,cb);
//	WRITEDATA(hData)
    if ( !hData )
        ImpDdeMgr::nLastErrInstance = DMLERR_INVALIDPARAMETER;
    return (HDDEDATA)hData;
}

// static
BYTE* ImpDdeMgr::DdeAccessData(HDDEDATA hData, ULONG* pcbDataSize)
{
    BYTE* pRet = 0;
    *pcbDataSize = 0;
    if ( hData )
    {
        pRet = (BYTE*)hData;
        pRet += hData->offabData;
        ULONG nLen = hData->cbData;
        // nLen -= hData->offabData;
        *pcbDataSize = nLen;
    }
    else
        ImpDdeMgr::nLastErrInstance = DMLERR_INVALIDPARAMETER;
    return pRet;
}

// static
BOOL ImpDdeMgr::DdeUnaccessData(HDDEDATA hData)
{
    return TRUE; // nothing to do for us
}

// static
BOOL ImpDdeMgr::DdeFreeDataHandle(HDDEDATA hData)
{
    DdeUnaccessData( hData );
    MyDosFreeMem( (PSZ)hData, "DdeFreeDataHandle" );
    return TRUE;
}

// static
HDDEDATA ImpDdeMgr::DdeAddData(HDDEDATA hData,void* pSrc,ULONG cb,ULONG cbOff)
{
    return (HDDEDATA)0;
}

// static
ULONG ImpDdeMgr::DdeGetData(HDDEDATA hData,void* pDst,ULONG cbMax,ULONG cbOff)
{
    return 0;
}

BOOL ImpDdeMgr::DisconnectAll()
{
    //WRITESTATUS("Before DisconnectAll()")
    USHORT nCurConvCount = pData->nCurConvCount;
    if( !nCurConvCount )
        return TRUE;

    BOOL bRet = TRUE;
    ImpHCONV* pPtr = pConvTable;
    pPtr++;

    for( USHORT nPos=1; nPos < pData->nMaxConvCount; nPos++, pPtr++ )
    {
        if( pPtr->hWndThis )
        {
            if( !DdeDisconnect( (HCONV)nPos ) )
                bRet = FALSE;
            nCurConvCount--;
            if( !nCurConvCount )
                break;
        }
    }
    return bRet;
}

// static
void ImpDdeMgr::FreeTransactions( ImpDdeMgrData* pData,HWND hWndThis,
    HWND hWndPartner )
{
    USHORT nCurTransCount = pData->nCurTransCount;
    if( !nCurTransCount )
        return;

    Transaction* pTrans = GetTransTable( pData );
    ImpHCONV* pConvTable = GetConvTable( pData );
    pTrans++;
    for( USHORT nPos=1; nPos < pData->nMaxTransCount; nPos++, pTrans++ )
    {
        if( pTrans->hConvOwner )
        {
            ImpHCONV* pConv = pConvTable + (USHORT)(pTrans->hConvOwner);
            if((pConv->hWndThis==hWndThis&& pConv->hWndPartner==hWndPartner)||
               (pConv->hWndThis==hWndPartner && pConv->hWndPartner==hWndThis))
            {
                FreeTransaction( pData, (ULONG)nPos );
            }
            nCurTransCount--;
            if( !nCurTransCount )
                return;
        }
    }
}

// static
void ImpDdeMgr::FreeTransactions( ImpDdeMgrData* pData, HCONV hConvOwner )
{
    USHORT nCurTransCount = pData->nCurTransCount;
    if( !nCurTransCount )
        return;

    Transaction* pTrans = GetTransTable( pData );
    pTrans++;
    for( USHORT nPos=1; nPos < pData->nMaxTransCount; nPos++, pTrans++ )
    {
        if( pTrans->hConvOwner == hConvOwner )
        {
            FreeTransaction( pData, (ULONG)nPos );
            nCurTransCount--;
            if( !nCurTransCount )
                return;
        }
    }
}

// static
void ImpDdeMgr::FreeConversations( ImpDdeMgrData* pData, HWND hWndThis,
    HWND hWndPartner )
{
    USHORT nCurCount = pData->nCurConvCount;
    if( !nCurCount )
        return;

    ImpHCONV* pPtr = GetConvTable( pData );
    pPtr++;
    for( USHORT nPos=1; nPos < pData->nMaxConvCount; nPos++, pPtr++ )
    {
        if( pPtr->hWndThis )
        {
            if( hWndThis && pPtr->hWndPartner==hWndPartner )
                FreeConvHandle( pData, (HCONV)nPos );
            nCurCount--;
            if( !nCurCount )
                return;
        }
    }
}


BOOL ImpDdeMgr::OwnsConversationHandles()
{
    ImpHCONV* pPtr = GetConvTable( pData );
    for( USHORT nCur = 1; nCur < pData->nMaxConvCount; nCur++, pPtr++ )
    {
        if( pPtr->hWndThis && pPtr->pidOwner == pidThis )
        {
            return TRUE;
        }
    }
    return FALSE;
}

// *********************************************************************

USHORT DdeInitialize(ULONG* pidInst, PFNCALLBACK pfnCallback,
    ULONG afCmd, ULONG ulRes)
{
    if( (*pidInst)!=0 )
    {
        // Reinitialize wird noch nicht unterstuetzt
        DBG_ASSERT(0,"DDEML:Reinitialize not supported");
        return DMLERR_INVALIDPARAMETER;
    }

    ImpDdeMgr* pMgr = new ImpDdeMgr;
    *pidInst = (ULONG)pMgr;
    return pMgr->DdeInitialize( pfnCallback, afCmd );
}

BOOL DdeUninitialize(ULONG idInst)
{
    if( !idInst )
        return FALSE;
    ImpDdeMgr* pMgr = (ImpDdeMgr*)idInst;
    // nur loeschen, wenn wir nicht mehr benutzt werden!
    if( !pMgr->OwnsConversationHandles() )
    {
        WRITELOG("DdeUninitialize: TRUE");
        delete pMgr;
        return TRUE;
    }
    WRITELOG("DdeUninitialize: FALSE");
    return FALSE;
}


HCONVLIST DdeConnectList(ULONG idInst, HSZ hszService, HSZ hszTopic,
    HCONVLIST hConvList, CONVCONTEXT* pCC)
{
    if( !idInst )
        return 0;
    return ((ImpDdeMgr*)idInst)->DdeConnectList(hszService,hszTopic,
                hConvList, pCC );
}

HCONV DdeQueryNextServer(HCONVLIST hConvList, HCONV hConvPrev)
{
    return ImpDdeMgr::DdeQueryNextServer( hConvList, hConvPrev );
}

BOOL DdeDisconnectList(HCONVLIST hConvList)
{
    return ImpDdeMgr::DdeDisconnectList( hConvList );
}

HCONV DdeConnect(ULONG idInst, HSZ hszService, HSZ hszTopic,
    CONVCONTEXT* pCC)
{
    if( !idInst )
        return 0;
    return ((ImpDdeMgr*)idInst)->DdeConnect( hszService, hszTopic, pCC );
}

BOOL DdeDisconnect(HCONV hConv)
{
    return ImpDdeMgr::DdeDisconnect( hConv );
}

HCONV DdeReconnect(HCONV hConv)
{
    return ImpDdeMgr::DdeReconnect( hConv );
}


USHORT DdeQueryConvInfo(HCONV hConv, ULONG idTransact, CONVINFO* pCI )
{
    return ImpDdeMgr::DdeQueryConvInfo( hConv, idTransact, pCI );
}

BOOL DdeSetUserHandle(HCONV hConv, ULONG id, ULONG hUser)
{
    return ImpDdeMgr::DdeSetUserHandle( hConv, id, hUser );
}

BOOL DdeAbandonTransaction(ULONG idInst, HCONV hConv, ULONG idTransaction)
{
    if( !idInst )
        return FALSE;
    return ((ImpDdeMgr*)idInst)->DdeAbandonTransaction(hConv,idTransaction);
}

BOOL DdePostAdvise(ULONG idInst, HSZ hszTopic, HSZ hszItem)
{
    if( !idInst )
        return FALSE;
    return ((ImpDdeMgr*)idInst)->DdePostAdvise( hszTopic, hszItem );
}

BOOL DdeEnableCallback(ULONG idInst, HCONV hConv, USHORT wCmd)
{
    if( !idInst )
        return FALSE;
    return ((ImpDdeMgr*)idInst)->DdeEnableCallback( hConv, wCmd );
}

HDDEDATA DdeClientTransaction(void* pData, ULONG cbData,
        HCONV hConv, HSZ hszItem, USHORT wFmt, USHORT wType,
        ULONG dwTimeout, ULONG* pdwResult)
{
    return ImpDdeMgr::DdeClientTransaction( pData, cbData,
        hConv, hszItem, wFmt, wType, dwTimeout, pdwResult );
}

HDDEDATA DdeCreateDataHandle(ULONG idInst, void* pSrc, ULONG cb,
    ULONG cbOff, HSZ hszItem, USHORT wFmt, USHORT afCmd)
{
    if( !idInst )
        return 0;
    return ((ImpDdeMgr*)idInst)->DdeCreateDataHandle( pSrc, cb,
        cbOff, hszItem, wFmt, afCmd );
}

HDDEDATA DdeAddData(HDDEDATA hData, void* pSrc, ULONG cb, ULONG cbOff)
{
    return ImpDdeMgr::DdeAddData( hData, pSrc, cb, cbOff );
}

ULONG DdeGetData(HDDEDATA hData, void* pDst, ULONG cbMax, ULONG cbOff)
{
    return ImpDdeMgr::DdeGetData( hData, pDst, cbMax, cbOff );
}

BYTE* DdeAccessData(HDDEDATA hData, ULONG* pcbDataSize)
{
    return ImpDdeMgr::DdeAccessData( hData, pcbDataSize );
}

BOOL DdeUnaccessData(HDDEDATA hData)
{
    return ImpDdeMgr::DdeUnaccessData( hData );
}

BOOL DdeFreeDataHandle(HDDEDATA hData)
{
    return ImpDdeMgr::DdeFreeDataHandle( hData );
}

USHORT DdeGetLastError(ULONG idInst)
{
    if( !idInst )
        return DMLERR_DLL_NOT_INITIALIZED;
    return ((ImpDdeMgr*)idInst)->DdeGetLastError();
}

HSZ DdeCreateStringHandle(ULONG idInst, PSZ pszString,int iCodePage )
{
    if( !idInst )
        return 0;
    return ((ImpDdeMgr*)idInst)->DdeCreateStringHandle(pszString,iCodePage);
}

ULONG DdeQueryString( ULONG idInst, HSZ hsz, PSZ pBuf,
    ULONG cchMax, int iCodePage )
{
    if( !idInst )
        return 0;
    return ((ImpDdeMgr*)idInst)->DdeQueryString( hsz,pBuf,cchMax,iCodePage);
}

BOOL DdeFreeStringHandle( ULONG idInst, HSZ hsz)
{
    if( !idInst )
        return FALSE;
    return ((ImpDdeMgr*)idInst)->DdeFreeStringHandle( hsz );
}

BOOL DdeKeepStringHandle( ULONG idInst, HSZ hsz )
{
    if( !idInst )
        return FALSE;
    return ((ImpDdeMgr*)idInst)->DdeKeepStringHandle( hsz );
}

int DdeCmpStringHandles(HSZ hsz1, HSZ hsz2)
{
    return ImpDdeMgr::DdeCmpStringHandles( hsz1, hsz2 );
}

HDDEDATA DdeNameService( ULONG idInst, HSZ hsz1, HSZ hszRes, USHORT afCmd )
{
    if( !idInst )
        return 0;
    return ((ImpDdeMgr*)idInst)->DdeNameService( hsz1, afCmd );
}


}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
