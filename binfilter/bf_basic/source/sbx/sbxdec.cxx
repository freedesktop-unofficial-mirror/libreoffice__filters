/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: sbxdec.cxx,v $
 *
 *  $Revision: 1.2 $
 *
 *  last change: $Author: obo $ $Date: 2007-03-15 15:13:22 $
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

#ifndef _ERRCODE_HXX //autogen
#include <tools/errcode.hxx>
#endif

#include "sbx.hxx"
#include "sbxconv.hxx"

#include <com/sun/star/bridge/oleautomation/Decimal.hpp>

namespace binfilter {

// int GnDecCounter = 0;

// Implementation SbxDecimal
SbxDecimal::SbxDecimal( void )
{
    setInt( 0 );
    mnRefCount = 0;
    // GnDecCounter++;
}

SbxDecimal::SbxDecimal( const SbxDecimal& rDec )
{
#ifdef WIN32
    maDec = rDec.maDec;
#else
    (void)rDec;
#endif
    mnRefCount = 0;
    // GnDecCounter++;
}

SbxDecimal::SbxDecimal
    ( const com::sun::star::bridge::oleautomation::Decimal& rAutomationDec )
{
#ifdef WIN32
    maDec.scale = rAutomationDec.Scale;
    maDec.sign  = rAutomationDec.Sign;
    maDec.Lo32 = rAutomationDec.LowValue;
    maDec.Mid32 = rAutomationDec.MiddleValue;
    maDec.Hi32 = rAutomationDec.HighValue;
#else
    (void)rAutomationDec;
#endif
    mnRefCount = 0;
    // GnDecCounter++;
}

void SbxDecimal::fillAutomationDecimal
    ( com::sun::star::bridge::oleautomation::Decimal& rAutomationDec )
{
#ifdef WIN32
    rAutomationDec.Scale = maDec.scale;
    rAutomationDec.Sign = maDec.sign;
    rAutomationDec.LowValue = maDec.Lo32;
    rAutomationDec.MiddleValue = maDec.Mid32;
    rAutomationDec.HighValue = maDec.Hi32;
#else
    (void)rAutomationDec;
#endif
}

SbxDecimal::~SbxDecimal()
{
    // GnDecCounter--;
}

void releaseDecimalPtr( SbxDecimal*& rpDecimal )
{
    if( rpDecimal )
    {
        rpDecimal->mnRefCount--;
        if( rpDecimal->mnRefCount == 0 )
        {
            delete rpDecimal;
            rpDecimal = NULL;
        }
    }
}

#ifdef WIN32

bool SbxDecimal::operator -= ( const SbxDecimal &r )
{
    HRESULT hResult = VarDecSub( &maDec, (LPDECIMAL)&r.maDec, &maDec );
    bool bRet = ( hResult == S_OK );
    return bRet;
}

bool SbxDecimal::operator += ( const SbxDecimal &r )
{
    HRESULT hResult = VarDecAdd( &maDec, (LPDECIMAL)&r.maDec, &maDec );
    bool bRet = ( hResult == S_OK );
    return bRet;
}

bool SbxDecimal::operator /= ( const SbxDecimal &r )
{
    HRESULT hResult = VarDecDiv( &maDec, (LPDECIMAL)&r.maDec, &maDec );
    bool bRet = ( hResult == S_OK );
    return bRet;
}

bool SbxDecimal::operator *= ( const SbxDecimal &r )
{
    HRESULT hResult = VarDecMul( &maDec, (LPDECIMAL)&r.maDec, &maDec );
    bool bRet = ( hResult == S_OK );
    return bRet;
}

bool SbxDecimal::neg( void )
{
    HRESULT hResult = VarDecNeg( &maDec, &maDec );
    bool bRet = ( hResult == S_OK );
    return bRet;
}

bool SbxDecimal::isZero( void )
{
    SbxDecimal aZeroDec;
    aZeroDec.setLong( 0 );
    bool bZero = ( EQ == compare( *this, aZeroDec ) );
    return bZero;
}

SbxDecimal::CmpResult compare( const SbxDecimal &rLeft, const SbxDecimal &rRight )
{
    HRESULT hResult = VarDecCmp( (LPDECIMAL)&rLeft.maDec, (LPDECIMAL)&rRight.maDec );
    SbxDecimal::CmpResult eRes = (SbxDecimal::CmpResult)hResult;
    return eRes;
}

void SbxDecimal::setChar( sal_Unicode val )
{
    VarDecFromUI2( (USHORT)val, &maDec );
}

void SbxDecimal::setByte( BYTE val )
{
    VarDecFromUI1( (BYTE)val, &maDec );
}

void SbxDecimal::setShort( INT16 val )
{
    VarDecFromI2( (short)val, &maDec );
}

void SbxDecimal::setLong( INT32 val )
{
    VarDecFromI4( (long)val, &maDec );
}

void SbxDecimal::setUShort( UINT16 val )
{
    VarDecFromUI2( (USHORT)val, &maDec );
}

void SbxDecimal::setULong( UINT32 val )
{
    VarDecFromUI4( (ULONG)val, &maDec );
}

bool SbxDecimal::setSingle( float val )
{
    bool bRet = ( VarDecFromR4( val, &maDec ) == S_OK );
    return bRet;
}

bool SbxDecimal::setDouble( double val )
{
    bool bRet = ( VarDecFromR8( val, &maDec ) == S_OK );
    return bRet;
}

void SbxDecimal::setInt( int val )
{
    setLong( (INT32)val );
}

void SbxDecimal::setUInt( unsigned int val )
{
    setULong( (UINT32)val );
}

// sbxscan.cxx
void ImpGetIntntlSep( sal_Unicode& rcDecimalSep, sal_Unicode& rcThousandSep );

bool SbxDecimal::setString( String* pString )
{
    static LCID nLANGID = MAKELANGID( LANG_ENGLISH, SUBLANG_ENGLISH_US );

    // Convert delimiter
    sal_Unicode cDecimalSep;
    sal_Unicode cThousandSep;
    ImpGetIntntlSep( cDecimalSep, cThousandSep );

    bool bRet = false;
    HRESULT hResult;
    if( cDecimalSep != '.' || cThousandSep != ',' )
    {
        int nLen = pString->Len();
        sal_Unicode* pBuffer = new sal_Unicode[nLen +  1];
        pBuffer[nLen] = 0;

        const sal_Unicode* pSrc = pString->GetBuffer();
        int i;
        for( i = 0 ; i < nLen ; ++i )
            pBuffer[i] = pSrc[i];

        sal_Unicode c;
        i = 0;
        while( (c = pBuffer[i]) != 0 )
        {
            if( c == cDecimalSep )
                pBuffer[i] = '.';
            else if( c == cThousandSep )
                pBuffer[i] = ',';
            i++;
        }
        hResult = VarDecFromStr( (OLECHAR*)pBuffer, nLANGID, 0, &maDec );
        delete pBuffer;
    }
    else
    {
        hResult = VarDecFromStr( (OLECHAR*)pString->GetBuffer(), nLANGID, 0, &maDec );
    }
    bRet = ( hResult == S_OK );
    return bRet;
}


bool SbxDecimal::getChar( sal_Unicode& rVal )
{
    bool bRet = ( VarUI2FromDec( &maDec, &rVal ) == S_OK );
    return bRet;
}

bool SbxDecimal::getByte( BYTE& rVal )
{
    bool bRet = ( VarUI1FromDec( &maDec, &rVal ) == S_OK );
    return bRet;
}

bool SbxDecimal::getShort( INT16& rVal )
{
    bool bRet = ( VarI2FromDec( &maDec, &rVal ) == S_OK );
    return bRet;
}

bool SbxDecimal::getLong( INT32& rVal )
{
    bool bRet = ( VarI4FromDec( &maDec, &rVal ) == S_OK );
    return bRet;
}

bool SbxDecimal::getUShort( UINT16& rVal )
{
    bool bRet = ( VarUI2FromDec( &maDec, &rVal ) == S_OK );
    return bRet;
}

bool SbxDecimal::getULong( UINT32& rVal )
{
    bool bRet = ( VarUI4FromDec( &maDec, &rVal ) == S_OK );
    return bRet;
}

bool SbxDecimal::getSingle( float& rVal )
{
    bool bRet = ( VarR4FromDec( &maDec, &rVal ) == S_OK );
    return bRet;
}

bool SbxDecimal::getDouble( double& rVal )
{
    bool bRet = ( VarR8FromDec( &maDec, &rVal ) == S_OK );
    return bRet;
}

bool SbxDecimal::getInt( int& rVal )
{
    INT32 TmpVal;
    bool bRet = getLong( TmpVal );
    rVal = TmpVal;
    return bRet;
}

bool SbxDecimal::getUInt( unsigned int& rVal )
{
    UINT32 TmpVal;
    bool bRet = getULong( TmpVal );
    rVal = TmpVal;
    return bRet;
}

#else
// !WIN32

bool SbxDecimal::operator -= ( const SbxDecimal &r )
{
    (void)r;
    return false;
}

bool SbxDecimal::operator += ( const SbxDecimal &r )
{
    (void)r;
    return false;
}

bool SbxDecimal::operator /= ( const SbxDecimal &r )
{
    (void)r;
    return false;
}

bool SbxDecimal::operator *= ( const SbxDecimal &r )
{
    (void)r;
    return false;
}

bool SbxDecimal::neg( void )
{
    return false;
}

bool SbxDecimal::isZero( void )
{
    return false;
}

SbxDecimal::CmpResult compare( const SbxDecimal &rLeft, const SbxDecimal &rRight )
{
    (void)rLeft;
    (void)rRight;
    return (SbxDecimal::CmpResult)0;
}

void SbxDecimal::setChar( sal_Unicode val )		{ (void)val; }
void SbxDecimal::setByte( BYTE val )			{ (void)val; }
void SbxDecimal::setShort( INT16 val )			{ (void)val; }
void SbxDecimal::setLong( INT32 val )			{ (void)val; }
void SbxDecimal::setUShort( UINT16 val )		{ (void)val; }
void SbxDecimal::setULong( UINT32 val )			{ (void)val; }
bool SbxDecimal::setSingle( float val )			{ (void)val; return false; }
bool SbxDecimal::setDouble( double val )		{ (void)val; return false; }
void SbxDecimal::setInt( int val )				{ (void)val; }
void SbxDecimal::setUInt( unsigned int val )	{ (void)val; }
bool SbxDecimal::setString( String* pString )	{ (void)pString;  return false; }

bool SbxDecimal::getChar( sal_Unicode& rVal )	{ (void)rVal; return false; }
bool SbxDecimal::getByte( BYTE& rVal )			{ (void)rVal; return false; }
bool SbxDecimal::getShort( INT16& rVal )		{ (void)rVal; return false; }
bool SbxDecimal::getLong( INT32& rVal )			{ (void)rVal; return false; }
bool SbxDecimal::getUShort( UINT16& rVal )		{ (void)rVal; return false; }
bool SbxDecimal::getULong( UINT32& rVal )		{ (void)rVal; return false; }
bool SbxDecimal::getSingle( float& rVal )		{ (void)rVal; return false; }
bool SbxDecimal::getDouble( double& rVal )		{ (void)rVal; return false; }
bool SbxDecimal::getInt( int& rVal )			{ (void)rVal; return false; }
bool SbxDecimal::getUInt( unsigned int& rVal )	{ (void)rVal; return false; }

#endif

bool SbxDecimal::getString( String& rString )
{
#ifdef WIN32
    static LCID nLANGID = MAKELANGID( LANG_ENGLISH, SUBLANG_ENGLISH_US );

    bool bRet = false;

    OLECHAR sz[100];
    BSTR aBStr = SysAllocString( sz );
    if( aBStr != NULL )
    {
        HRESULT hResult = VarBstrFromDec( &maDec, nLANGID, 0, &aBStr );
        bRet = ( hResult == S_OK );
        if( bRet )
        {
            // Convert delimiter
            sal_Unicode cDecimalSep;
            sal_Unicode cThousandSep;
            ImpGetIntntlSep( cDecimalSep, cThousandSep );

            if( cDecimalSep != '.' || cThousandSep != ',' )
            {
                sal_Unicode c;
                int i = 0;
                while( (c = aBStr[i]) != 0 )
                {
                    if( c == '.' )
                        aBStr[i] = cDecimalSep;
                    else if( c == ',' )
                        aBStr[i] = cThousandSep;
                    i++;
                }
            }
            rString = aBStr;
        }

        SysFreeString( aBStr );
    }
    return bRet;
#else
    (void)rString;
    return false;
#endif
}

SbxDecimal* ImpCreateDecimal( SbxValues* p )
{
#ifdef WIN32
    if( !p )
        return NULL;

    SbxDecimal*& rpDecimal = p->pDecimal;
    if( rpDecimal == NULL )
    {
        rpDecimal = new SbxDecimal();
        rpDecimal->addRef();
    }
    return rpDecimal;
#else
    (void)p;
    return NULL;
#endif
}

SbxDecimal* ImpGetDecimal( const SbxValues* p )
{
#ifdef WIN32
    SbxValues aTmp;
    SbxDecimal* pnDecRes;

    SbxDataType eType = p->eType;
    if( eType == SbxDECIMAL && p->pDecimal )
    {
        pnDecRes = new SbxDecimal( *p->pDecimal );
        pnDecRes->addRef();
        return pnDecRes;
    }
    pnDecRes = new SbxDecimal();
    pnDecRes->addRef();

start:
    switch( eType )
    {
        case SbxNULL:
            SbxBase::SetError( SbxERR_CONVERSION );
        case SbxEMPTY:
            pnDecRes->setShort( 0 ); break;
        case SbxCHAR:
            pnDecRes->setChar( p->nChar ); break;
        case SbxBYTE:
            pnDecRes->setByte( p->nByte ); break;
        case SbxINTEGER:
        case SbxBOOL:
            pnDecRes->setInt( p->nInteger ); break;
        case SbxERROR:
        case SbxUSHORT:
            pnDecRes->setUShort( p->nUShort ); break;
        case SbxLONG:
            pnDecRes->setLong( p->nLong ); break;
        case SbxULONG:
            pnDecRes->setULong( p->nULong ); break;
        case SbxSINGLE:
            if( !pnDecRes->setSingle( p->nSingle ) )
                SbxBase::SetError( SbxERR_OVERFLOW );
            break;
        case SbxSALINT64:
            {
                double d = (double)p->nInt64;
                pnDecRes->setDouble( d );
                break;
            }
        case SbxSALUINT64:
            {
                double d = ImpSalUInt64ToDouble( p->uInt64 );
                pnDecRes->setDouble( d );
                break;
            }
        case SbxDATE:
        case SbxDOUBLE:
        case SbxLONG64:
        case SbxULONG64:
        case SbxCURRENCY:
            {
            double dVal;
            if( p->eType ==	SbxCURRENCY )
                dVal = ImpCurrencyToDouble( p->nLong64 );
            else if( p->eType == SbxLONG64 )
                dVal = ImpINT64ToDouble( p->nLong64 );
            else if( p->eType == SbxULONG64 )
                dVal = ImpUINT64ToDouble( p->nULong64 );
            else
                dVal = p->nDouble;

            if( !pnDecRes->setDouble( dVal ) )
                SbxBase::SetError( SbxERR_OVERFLOW );
            break;
            }
        case SbxLPSTR:
        case SbxSTRING:
        case SbxBYREF | SbxSTRING:
            pnDecRes->setString( p->pString ); break;
        case SbxOBJECT:
        {
            SbxValue* pVal = PTR_CAST(SbxValue,p->pObj);
            if( pVal )
                pnDecRes->setDecimal( pVal->GetDecimal() );
            else
            {
                SbxBase::SetError( SbxERR_NO_OBJECT );
                pnDecRes->setShort( 0 );
            }
            break;
        }

        case SbxBYREF | SbxCHAR:
            pnDecRes->setChar( *p->pChar ); break;
        case SbxBYREF | SbxBYTE:
            pnDecRes->setByte( *p->pByte ); break;
        case SbxBYREF | SbxINTEGER:
        case SbxBYREF | SbxBOOL:
            pnDecRes->setInt( *p->pInteger ); break;
        case SbxBYREF | SbxLONG:
            pnDecRes->setLong( *p->pLong ); break;
        case SbxBYREF | SbxULONG:
            pnDecRes->setULong( *p->pULong ); break;
        case SbxBYREF | SbxERROR:
        case SbxBYREF | SbxUSHORT:
            pnDecRes->setUShort( *p->pUShort ); break;

        // ab hier muss getestet werden
        case SbxBYREF | SbxSINGLE:
            aTmp.nSingle = *p->pSingle; goto ref;
        case SbxBYREF | SbxDATE:
        case SbxBYREF | SbxDOUBLE:
            aTmp.nDouble = *p->pDouble; goto ref;
        case SbxBYREF | SbxULONG64:
            aTmp.nULong64 = *p->pULong64; goto ref;
        case SbxBYREF | SbxLONG64:
        case SbxBYREF | SbxCURRENCY:
            aTmp.nLong64 = *p->pLong64; goto ref;
        case SbxBYREF | SbxSALINT64:
            aTmp.nInt64 = *p->pnInt64; goto ref;
        case SbxBYREF | SbxSALUINT64:
            aTmp.uInt64 = *p->puInt64; goto ref;
        ref:
            aTmp.eType = SbxDataType( p->eType & 0x0FFF );
            p = &aTmp; goto start;

        default:
            SbxBase::SetError( SbxERR_CONVERSION ); pnDecRes->setShort( 0 );
    }
    return pnDecRes;
#else
    (void)p;
    return NULL;
#endif
}


void ImpPutDecimal( SbxValues* p, SbxDecimal* pDec )
{
#ifdef WIN32
    if( !pDec )
        return;

    SbxValues aTmp;
start:
    switch( p->eType )
    {
        // hier muss getestet werden
        case SbxCHAR:
            aTmp.pChar = &p->nChar; goto direct;
        case SbxBYTE:
            aTmp.pByte = &p->nByte; goto direct;
        case SbxULONG:
            aTmp.pULong = &p->nULong; goto direct;
        case SbxERROR:
        case SbxUSHORT:
            aTmp.pUShort = &p->nUShort; goto direct;
        case SbxSALUINT64:
            aTmp.puInt64 = &p->uInt64; goto direct;
        case SbxINTEGER:
        case SbxBOOL:
            aTmp.pInteger = &p->nInteger; goto direct;
        case SbxLONG:
            aTmp.pLong = &p->nLong; goto direct;
        case SbxSALINT64:
            aTmp.pnInt64 = &p->nInt64; goto direct;
        case SbxCURRENCY:
            aTmp.pLong64 = &p->nLong64; goto direct;
        direct:
            aTmp.eType = SbxDataType( p->eType | SbxBYREF );
            p = &aTmp; goto start;

        // ab hier nicht mehr
        case SbxDECIMAL:
        case SbxBYREF | SbxDECIMAL:
        {
            if( pDec != p->pDecimal )
            {
                releaseDecimalPtr( p->pDecimal );
                // if( p->pDecimal )
                    // p->pDecimal->ReleaseRef();
                p->pDecimal = pDec;
                if( pDec )
                    pDec->addRef();
            }
            break;
        }
        case SbxSINGLE:
        {
            float f;
            pDec->getSingle( f );
            p->nSingle = f;
            break;
        }
        case SbxDATE:
        case SbxDOUBLE:
        {
            double d;
            pDec->getDouble( d );
            p->nDouble = d;
            break;
        }
        case SbxULONG64:
        {
            double d;
            pDec->getDouble( d );
            p->nULong64 = ImpDoubleToUINT64( d );
            break;
        }
        case SbxLONG64:
        {
            double d;
            pDec->getDouble( d );
            p->nLong64 = ImpDoubleToINT64( d );
            break;
        }

        case SbxLPSTR:
        case SbxSTRING:
        case SbxBYREF | SbxSTRING:
            if( !p->pString )
                p->pString = new XubString;
            // ImpCvtNum( (double) n, 0, *p->pString );
            pDec->getString( *p->pString );
            break;
        case SbxOBJECT:
        {
            SbxValue* pVal = PTR_CAST(SbxValue,p->pObj);
            if( pVal )
                pVal->PutDecimal( pDec );
            else
                SbxBase::SetError( SbxERR_NO_OBJECT );
            break;
        }

        case SbxBYREF | SbxCHAR:
            if( !pDec->getChar( *p->pChar ) )
            {
                SbxBase::SetError( SbxERR_OVERFLOW );
                *p->pChar = 0;
            }
            break;
        case SbxBYREF | SbxBYTE:
            if( !pDec->getChar( *p->pChar ) )
            {
                SbxBase::SetError( SbxERR_OVERFLOW );
                *p->pByte = 0;
            }
            break;
        case SbxBYREF | SbxINTEGER:
        case SbxBYREF | SbxBOOL:
            if( !pDec->getShort( *p->pInteger ) )
            {
                SbxBase::SetError( SbxERR_OVERFLOW );
                *p->pInteger = 0;
            }
            break;
            // *p->pInteger = n; break;
        case SbxBYREF | SbxERROR:
        case SbxBYREF | SbxUSHORT:
            if( !pDec->getUShort( *p->pUShort ) )
            {
                SbxBase::SetError( SbxERR_OVERFLOW );
                *p->pUShort = 0;
            }
            break;
        case SbxBYREF | SbxLONG:
            if( !pDec->getLong( *p->pLong ) )
            {
                SbxBase::SetError( SbxERR_OVERFLOW );
                *p->pLong = 0;
            }
            break;
        case SbxBYREF | SbxULONG:
            if( !pDec->getULong( *p->pULong ) )
            {
                SbxBase::SetError( SbxERR_OVERFLOW );
                *p->pULong = 0;
            }
            break;
        case SbxBYREF | SbxSALINT64:
            {
            double d;
            if( !pDec->getDouble( d ) )
                SbxBase::SetError( SbxERR_OVERFLOW );
            else
                *p->pnInt64 = ImpDoubleToSalInt64( d );
            break;
            }
        case SbxBYREF | SbxSALUINT64:
            {
            double d;
            if( !pDec->getDouble( d ) )
                SbxBase::SetError( SbxERR_OVERFLOW );
            else
                *p->puInt64 = ImpDoubleToSalUInt64( d );
            break;
            }
        case SbxBYREF | SbxSINGLE:
            if( !pDec->getSingle( *p->pSingle ) )
            {
                SbxBase::SetError( SbxERR_OVERFLOW ); 
                *p->pSingle = 0;
            }
            break;
            // *p->pSingle = (float) n; break;
        case SbxBYREF | SbxDATE:
        case SbxBYREF | SbxDOUBLE:
            if( !pDec->getDouble( *p->pDouble ) )
            {
                SbxBase::SetError( SbxERR_OVERFLOW ); 
                *p->pDouble = 0;
            }
            break;
        case SbxBYREF | SbxULONG64:
        {
            double d;
            pDec->getDouble( d );
            *p->pULong64 = ImpDoubleToUINT64( d ); 
            break;
        }
        case SbxBYREF | SbxLONG64:
        {
            double d;
            pDec->getDouble( d );
            *p->pLong64 = ImpDoubleToINT64( d ); 
            break;
        }
        case SbxBYREF | SbxCURRENCY:
        {
            double d;
            pDec->getDouble( d );
            *p->pLong64 = ImpDoubleToCurrency( d );
            break;
        }

        default:
            SbxBase::SetError( SbxERR_CONVERSION );
    }
#else
    (void)p;
    (void)pDec;
#endif
}

}

