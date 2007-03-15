/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: sbxcoll.cxx,v $
 *
 *  $Revision: 1.2 $
 *
 *  last change: $Author: obo $ $Date: 2007-03-15 15:12:11 $
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

#ifndef _STREAM_HXX //autogen
#include <tools/stream.hxx>
#endif

#include "sbx.hxx"
#include "sbxres.hxx"

namespace binfilter {

TYPEINIT1(SbxCollection,SbxObject)
TYPEINIT1(SbxStdCollection,SbxCollection)

static const char* pCount;
static const char* pAdd;
static const char* pItem;
static const char* pRemove;
static USHORT nCountHash = 0, nAddHash, nItemHash, nRemoveHash;

/////////////////////////////////////////////////////////////////////////

SbxCollection::SbxCollection( const XubString& rClass )
             : SbxObject( rClass )
{
    if( !nCountHash )
    {
        pCount  = GetSbxRes( STRING_COUNTPROP );
        pAdd    = GetSbxRes( STRING_ADDMETH );
        pItem   = GetSbxRes( STRING_ITEMMETH );
        pRemove = GetSbxRes( STRING_REMOVEMETH );
        nCountHash  = MakeHashCode( String::CreateFromAscii( pCount ) );
        nAddHash    = MakeHashCode( String::CreateFromAscii( pAdd ) );
        nItemHash   = MakeHashCode( String::CreateFromAscii( pItem ) );
        nRemoveHash = MakeHashCode( String::CreateFromAscii( pRemove ) );
    }
    Initialize();
    // Fuer Zugriffe auf sich selbst
    StartListening( GetBroadcaster(), TRUE );
}

SbxCollection::SbxCollection( const SbxCollection& rColl )
    : SvRefBase( rColl ), SbxObject( rColl )
{}

SbxCollection& SbxCollection::operator=( const SbxCollection& r )
{
    if( &r != this )
        SbxObject::operator=( r );
    return *this;
}

SbxCollection::~SbxCollection()
{}

void SbxCollection::Clear()
{
    SbxObject::Clear();
    Initialize();
}

void SbxCollection::Initialize()
{
    SetType( SbxOBJECT );
    SetFlag( SBX_FIXED );
    ResetFlag( SBX_WRITE );
    SbxVariable* p;
    p = Make( String::CreateFromAscii( pCount ), SbxCLASS_PROPERTY, SbxINTEGER );
    p->ResetFlag( SBX_WRITE );
    p->SetFlag( SBX_DONTSTORE );
    p = Make( String::CreateFromAscii( pAdd ), SbxCLASS_METHOD, SbxEMPTY );
    p->SetFlag( SBX_DONTSTORE );
    p = Make( String::CreateFromAscii( pItem ), SbxCLASS_METHOD, SbxOBJECT );
    p->SetFlag( SBX_DONTSTORE );
    p = Make( String::CreateFromAscii( pRemove ), SbxCLASS_METHOD, SbxEMPTY );
    p->SetFlag( SBX_DONTSTORE );
}

SbxVariable* SbxCollection::FindUserData( UINT32 nData )
{
    if( GetParameters() )
    {
        SbxObject* pObj = (SbxObject*) GetObject();
        return pObj ? pObj->FindUserData( nData ) : NULL;
    }
    else
        return SbxObject::FindUserData( nData );
}

SbxVariable* SbxCollection::Find( const XubString& rName, SbxClassType t )
{
    if( GetParameters() )
    {
        SbxObject* pObj = (SbxObject*) GetObject();
        return pObj ? pObj->Find( rName, t ) : NULL;
    }
    else
        return SbxObject::Find( rName, t );
}

void SbxCollection::SFX_NOTIFY( SfxBroadcaster& rCst, const TypeId& rId1,
                                const SfxHint& rHint, const TypeId& rId2 )
{
    const SbxHint* p = PTR_CAST(SbxHint,&rHint);
    if( p )
    {
        ULONG nId = p->GetId();
        BOOL bRead  = BOOL( nId == SBX_HINT_DATAWANTED );
        BOOL bWrite = BOOL( nId == SBX_HINT_DATACHANGED );
        SbxVariable* pVar = p->GetVar();
        SbxArray* pArg = pVar->GetParameters();
        if( bRead || bWrite )
        {
            XubString aVarName( pVar->GetName() );
            if( pVar == this )
                CollItem( pArg );
            else if( pVar->GetHashCode() == nCountHash
                  && aVarName.EqualsIgnoreCaseAscii( pCount ) )
                pVar->PutLong( pObjs->Count() );
            else if( pVar->GetHashCode() == nAddHash
                  && aVarName.EqualsIgnoreCaseAscii( pAdd ) )
                CollAdd( pArg );
            else if( pVar->GetHashCode() == nItemHash
                  && aVarName.EqualsIgnoreCaseAscii( pItem ) )
                CollItem( pArg );
            else if( pVar->GetHashCode() == nRemoveHash
                  && aVarName.EqualsIgnoreCaseAscii( pRemove ) )
                CollRemove( pArg );
            else
                SbxObject::SFX_NOTIFY( rCst, rId1, rHint, rId2 );
            return;
        }
    }
    SbxObject::SFX_NOTIFY( rCst, rId1, rHint, rId2 );
}

// Default: Argument ist Objekt

void SbxCollection::CollAdd( SbxArray* pPar_ )
{
    if( pPar_->Count() != 2 )
        SetError( SbxERR_WRONG_ARGS );
    else
    {
        SbxBase* pObj = pPar_->Get( 1 )->GetObject();
        if( !pObj || !( pObj->ISA(SbxObject) ) )
            SetError( SbxERR_NOTIMP );
        else
            Insert( (SbxObject*) pObj );
    }
}

// Default: Index ab 1 oder der Objektname

void SbxCollection::CollItem( SbxArray* pPar_ )
{
    if( pPar_->Count() != 2 )
        SetError( SbxERR_WRONG_ARGS );
    else
    {
        SbxVariable* pRes = NULL;
        SbxVariable* p = pPar_->Get( 1 );
        if( p->GetType() == SbxSTRING )
            pRes = Find( p->GetString(), SbxCLASS_OBJECT );
        else
        {
            short n = p->GetInteger();
            if( n >= 1 && n <= (short) pObjs->Count() )
                pRes = pObjs->Get( (USHORT) n - 1 );
        }
        if( !pRes )
            SetError( SbxERR_BAD_INDEX );
        pPar_->Get( 0 )->PutObject( pRes );
    }
}

// Default: Index ab 1

void SbxCollection::CollRemove( SbxArray* pPar_ )
{
    if( pPar_->Count() != 2 )
        SetError( SbxERR_WRONG_ARGS );
    else
    {
        short n = pPar_->Get( 1 )->GetInteger();
        if( n < 1 || n > (short) pObjs->Count() )
            SetError( SbxERR_BAD_INDEX );
        else
            Remove( pObjs->Get( (USHORT) n - 1 ) );
    }
}

BOOL SbxCollection::LoadData( SvStream& rStrm, USHORT nVer )
{
    BOOL bRes = SbxObject::LoadData( rStrm, nVer );
    Initialize();
    return bRes;
}

/////////////////////////////////////////////////////////////////////////

SbxStdCollection::SbxStdCollection
                    ( const XubString& rClass, const XubString& rElem, BOOL b )
                  : SbxCollection( rClass ), aElemClass( rElem ),
                    bAddRemoveOk( b )
{}

SbxStdCollection::SbxStdCollection( const SbxStdCollection& r )
                  : SvRefBase( r ), SbxCollection( r ),
                    aElemClass( r.aElemClass ), bAddRemoveOk( r.bAddRemoveOk )
{}

SbxStdCollection& SbxStdCollection::operator=( const SbxStdCollection& r )
{
    if( &r != this )
    {
        if( !r.aElemClass.EqualsIgnoreCaseAscii( aElemClass ) )
            SetError( SbxERR_CONVERSION );
        else
            SbxCollection::operator=( r );
    }
    return *this;
}

SbxStdCollection::~SbxStdCollection()
{}

// Default: Fehler, wenn falsches Objekt

void SbxStdCollection::Insert( SbxVariable* p )
{
    SbxObject* pObj = PTR_CAST(SbxObject,p);
    if( pObj && !pObj->IsClass( aElemClass ) )
        SetError( SbxERR_BAD_ACTION );
    else
        SbxCollection::Insert( p );
}

void SbxStdCollection::CollAdd( SbxArray* pPar_ )
{
    if( !bAddRemoveOk )
        SetError( SbxERR_BAD_ACTION );
    else
        SbxCollection::CollAdd( pPar_ );
}

void SbxStdCollection::CollRemove( SbxArray* pPar_ )
{
    if( !bAddRemoveOk )
        SetError( SbxERR_BAD_ACTION );
    else
        SbxCollection::CollRemove( pPar_ );
}

BOOL SbxStdCollection::LoadData( SvStream& rStrm, USHORT nVer )
{
    BOOL bRes = SbxCollection::LoadData( rStrm, nVer );
    if( bRes )
    {
        rStrm.ReadByteString( aElemClass, RTL_TEXTENCODING_ASCII_US );
        rStrm >> bAddRemoveOk;
    }
    return bRes;
}

BOOL SbxStdCollection::StoreData( SvStream& rStrm ) const
{
    BOOL bRes = SbxCollection::StoreData( rStrm );
    if( bRes )
    {
        rStrm.WriteByteString( aElemClass, RTL_TEXTENCODING_ASCII_US );
        rStrm << bAddRemoveOk;
    }
    return bRes;
}

}
