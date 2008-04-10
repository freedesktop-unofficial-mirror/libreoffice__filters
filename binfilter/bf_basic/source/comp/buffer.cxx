/*************************************************************************
 *
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER.
 * 
 * Copyright 2008 by Sun Microsystems, Inc.
 *
 * OpenOffice.org - a multi-platform office productivity suite
 *
 * $RCSfile: buffer.cxx,v $
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

/*?*/ // #include "sbcomp.hxx"
#include "buffer.hxx"
#include <string.h>

namespace binfilter {

const static UINT32 UP_LIMIT=0xFFFFFF00L;

// Der SbiBuffer wird in Inkrements von mindestens 16 Bytes erweitert.
// Dies ist notwendig, da viele Klassen von einer Pufferlaenge
// von x*16 Bytes ausgehen.

SbiBuffer::SbiBuffer( SbiParser* p, short n )
{
    pParser = p;
    n = ( (n + 15 ) / 16 ) * 16;
    if( !n ) n = 16;
    pBuf  = NULL;
    pCur  = NULL;
    nInc  = n;
    nSize =
    nOff  = 0;
}

SbiBuffer::~SbiBuffer()
{
    delete[] pBuf;
}

// Rausreichen des Puffers
// Dies fuehrt zur Loeschung des Puffers!

char* SbiBuffer::GetBuffer()
{
    char* p = pBuf;
    pBuf = NULL;
    pCur = NULL;
    return p;
}

// Test, ob der Puffer n Bytes aufnehmen kann.
// Im Zweifelsfall wird er vergroessert

BOOL SbiBuffer::Check( USHORT n )
{
    if( !n ) return TRUE;
    if( ( static_cast<UINT32>( nOff )+ n ) >  static_cast<UINT32>( nSize ) )
    {
        if( nInc == 0 )
            return FALSE;
        USHORT nn = 0;
        while( nn < n ) nn = nn + nInc;
        char* p;
        if( ( static_cast<UINT32>( nSize ) + nn ) > UP_LIMIT ) p = NULL;
        else p = new char [nSize + nn];
        if( !p )
        {
/*?*/ // 			pParser->Error( SbERR_PROG_TOO_LARGE );
            nInc = 0;
            delete[] pBuf; pBuf = NULL;
            return FALSE;
        }
        else
        {
            if( nSize ) memcpy( p, pBuf, nSize );
            delete[] pBuf;
            pBuf = p;
            pCur = pBuf + nOff;
            nSize = nSize + nn;
        }
    }
    return TRUE;
}

// Angleich des Puffers auf die uebergebene Byte-Grenze

void SbiBuffer::Align( INT32 n )
{
    if( nOff % n ) {
        UINT32 nn =( ( nOff + n ) / n ) * n;
        if( nn <= UP_LIMIT )
        {
            nn = nn - nOff;
            if( Check( static_cast<USHORT>(nn) ) )
            {
                memset( pCur, 0, nn );
                pCur += nn;
                nOff = nOff + nn;
            }
        }
    }
}

// Patch einer Location

void SbiBuffer::Patch( UINT32 off, UINT32 val )
{
    if( ( off + sizeof( UINT32 ) ) < nOff )
    {
        UINT16 val1 = static_cast<UINT16>( val & 0xFFFF );
        UINT16 val2 = static_cast<UINT16>( val >> 16 );
        BYTE* p = (BYTE*) pBuf + off;
        *p++ = (char) ( val1 & 0xFF );
        *p++ = (char) ( val1 >> 8 );
        *p++ = (char) ( val2 & 0xFF );
        *p   = (char) ( val2 >> 8 );
    }
}

// Forward References auf Labels und Prozeduren
// bauen eine Kette auf. Der Anfang der Kette ist beim uebergebenen
// Parameter, das Ende der Kette ist 0.

void SbiBuffer::Chain( UINT32 off )
{
    if( off && pBuf )
    {
        BYTE *ip;
        UINT32 i = off;
        UINT32 val1 = (nOff & 0xFFFF);
        UINT32 val2 = (nOff >> 16);
        do
        {
            ip = (BYTE*) pBuf + i;
            BYTE* pTmp = ip;
                     i =  *pTmp++; i |= *pTmp++ << 8; i |= *pTmp++ << 16; i |= *pTmp++ << 24;

            if( i >= nOff )
            {
/*?*/ // 				pParser->Error( SbERR_INTERNAL_ERROR, "BACKCHAIN" );
                break;
            }
            *ip++ = (char) ( val1 & 0xFF );
            *ip++ = (char) ( val1 >> 8 );
            *ip++ = (char) ( val2 & 0xFF );
            *ip   = (char) ( val2 >> 8 );
        } while( i );
    }
}

BOOL SbiBuffer::operator +=( INT8 n )
{
    if( Check( 1 ) )
    {
        *pCur++ = (char) n; nOff++; return TRUE;
    } else return FALSE;
}

BOOL SbiBuffer::operator +=( UINT8 n )
{
    if( Check( 1 ) )
    {
        *pCur++ = (char) n; nOff++; return TRUE;
    } else return FALSE;
}

BOOL SbiBuffer::operator +=( INT16 n )
{
    if( Check( 2 ) )
    {
        *pCur++ = (char) ( n & 0xFF );
        *pCur++ = (char) ( n >> 8 );
        nOff += 2; return TRUE;
    } else return FALSE;
}

BOOL SbiBuffer::operator +=( UINT16 n )
{
    if( Check( 2 ) )
    {
        *pCur++ = (char) ( n & 0xFF );
        *pCur++ = (char) ( n >> 8 );
        nOff += 2; return TRUE;
    } else return FALSE;
}

BOOL SbiBuffer::operator +=( UINT32 n )
{
    if( Check( 4 ) )
    {
        UINT16 n1 = static_cast<UINT16>( n & 0xFFFF );
        UINT16 n2 = static_cast<UINT16>( n >> 16 );
        if ( operator +=( n1 ) && operator +=( n2 ) )
            return TRUE;
        return TRUE;
    } 
    return FALSE;
}

BOOL SbiBuffer::operator +=( INT32 n )
{
    return operator +=( (UINT32) n );
}


BOOL SbiBuffer::operator +=( const String& n )
{
    USHORT l = n.Len() + 1;
    if( Check( l ) )
    {
        ByteString aByteStr( n, gsl_getSystemTextEncoding() );
        memcpy( pCur, aByteStr.GetBuffer(), l );
        pCur += l;
        nOff = nOff + l;
        return TRUE;
    }
    else return FALSE;
}

BOOL SbiBuffer::Add( const void* p, USHORT len )
{
    if( Check( len ) )
    {
        memcpy( pCur, p, len );
        pCur += len;
        nOff = nOff + len;
        return TRUE;
    } else return FALSE;
}


}
