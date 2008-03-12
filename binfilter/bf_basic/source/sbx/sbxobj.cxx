/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: sbxobj.cxx,v $
 *
 *  $Revision: 1.3 $
 *
 *  last change: $Author: rt $ $Date: 2008-03-12 06:42:45 $
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
#include <vcl/sound.hxx>
#include "sbx.hxx"
#include "sbxbase.hxx"
#include "sbxres.hxx"

#ifndef _SFXBRDCST_HXX //autogen
#include <bf_svtools/brdcst.hxx>
#endif

namespace binfilter {

TYPEINIT1(SbxMethod,SbxVariable)
TYPEINIT1(SbxProperty,SbxVariable)
TYPEINIT2(SbxObject,SbxVariable,SfxListener)

static const char* pNameProp;				// Name-Property
static const char* pParentProp;				// Parent-Property

static USHORT nNameHash = 0, nParentHash = 0;

/////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////

SbxObject::SbxObject( const XubString& rClass )
         : SbxVariable( SbxOBJECT ), aClassName( rClass )
{
    aData.pObj = this;
    if( !nNameHash )
    {
        pNameProp = GetSbxRes( STRING_NAMEPROP );
        pParentProp = GetSbxRes( STRING_PARENTPROP );
        nNameHash = MakeHashCode( String::CreateFromAscii( pNameProp ) );
        nParentHash = MakeHashCode( String::CreateFromAscii( pParentProp ) );
    }
    SbxObject::Clear();
    SbxObject::SetName( rClass );
}

SbxObject::SbxObject( const SbxObject& rObj )
    : SvRefBase( rObj ), SbxVariable( rObj.GetType() ),
      SfxListener( rObj )
{
    *this = rObj;
}

SbxObject& SbxObject::operator=( const SbxObject& r )
{
    if( &r != this )
    {
        SbxVariable::operator=( r );
        aClassName = r.aClassName;
        pMethods   = new SbxArray;
        pProps     = new SbxArray;
        pObjs      = new SbxArray( SbxOBJECT );
        // Die Arrays werden kopiert, die Inhalte uebernommen
        *pMethods  = *r.pMethods;
        *pProps    = *r.pProps;
        *pObjs     = *r.pObjs;
        // Da die Variablen uebernommen wurden, ist dies OK
        pDfltProp  = r.pDfltProp;
        SetName( r.GetName() );
        SetFlags( r.GetFlags() );
        SetModified( TRUE );
    }
    return *this;
}

static void CheckParentsOnDelete( SbxObject* pObj, SbxArray* p )
{
    for( USHORT i = 0; i < p->Count(); i++ )
    {
        SbxVariableRef& rRef = p->GetRef( i );
        if( rRef->IsBroadcaster() )
            pObj->EndListening( rRef->GetBroadcaster(), TRUE );
        // Hat das Element mehr als eine Referenz und noch einen Listener?
        if( rRef->GetRefCount() > 1 )
        {
            rRef->SetParent( NULL );
            DBG_ASSERT( !rRef->IsBroadcaster() || rRef->GetBroadcaster().GetListenerCount(), "Object element with dangling parent" );
        }
    }
}

SbxObject::~SbxObject()
{
    CheckParentsOnDelete( this, pProps );
    CheckParentsOnDelete( this, pMethods );
    CheckParentsOnDelete( this, pObjs );
}

SbxDataType SbxObject::GetType() const
{
    return SbxOBJECT;
}

SbxClassType SbxObject::GetClass() const
{
    return SbxCLASS_OBJECT;
}

void SbxObject::Clear()
{
    pMethods   = new SbxArray;
    pProps     = new SbxArray;
    pObjs      = new SbxArray( SbxOBJECT );
    SbxVariable* p;
    p = Make( String::CreateFromAscii( pNameProp ), SbxCLASS_PROPERTY, SbxSTRING );
    p->SetFlag( SBX_DONTSTORE );
    p = Make( String::CreateFromAscii( pParentProp ), SbxCLASS_PROPERTY, SbxOBJECT );
    p->ResetFlag( SBX_WRITE );
    p->SetFlag( SBX_DONTSTORE );
    pDfltProp  = NULL;
    SetModified( FALSE );
}

void SbxObject::SFX_NOTIFY( SfxBroadcaster&, const TypeId&,
                            const SfxHint& rHint, const TypeId& )
{
    const SbxHint* p = PTR_CAST(SbxHint,&rHint);
    if( p )
    {
        ULONG nId = p->GetId();
        BOOL bRead  = BOOL( nId == SBX_HINT_DATAWANTED );
        BOOL bWrite = BOOL( nId == SBX_HINT_DATACHANGED );
        SbxVariable* pVar = p->GetVar();
        if( bRead || bWrite )
        {
            XubString aVarName( pVar->GetName() );
            USHORT nHash_ = MakeHashCode( aVarName );
            if( nHash_ == nNameHash
             && aVarName.EqualsIgnoreCaseAscii( pNameProp ) )
            {
                if( bRead )
                    pVar->PutString( GetName() );
                else
                    SetName( pVar->GetString() );
            }
            else if( nHash_ == nParentHash
             && aVarName.EqualsIgnoreCaseAscii( pParentProp ) )
            {
                SbxObject* p_ = GetParent();
                if( !p_ )
                    p_ = this;
                pVar->PutObject( p_ );
            }
        }
    }
}

BOOL SbxObject::IsClass( const XubString& rName ) const
{
    return BOOL( aClassName.EqualsIgnoreCaseAscii( rName ) );
}

SbxVariable* SbxObject::FindUserData( UINT32 nData )
{
    if( !GetAll( SbxCLASS_DONTCARE ) )
        return NULL;

    SbxVariable* pRes = pMethods->FindUserData( nData );
    if( !pRes )
        pRes = pProps->FindUserData( nData );
    if( !pRes )
        pRes = pObjs->FindUserData( nData );
    // Search in den Parents?
    if( !pRes && IsSet( SBX_GBLSEARCH ) )
    {
        SbxObject* pCur = this;
        while( !pRes && pCur->pParent )
        {
            // Ich selbst bin schon durchsucht worden!
            USHORT nOwn = pCur->GetFlags();
            pCur->ResetFlag( SBX_EXTSEARCH );
            // Ich suche bereits global!
            USHORT nPar = pCur->pParent->GetFlags();
            pCur->pParent->ResetFlag( SBX_GBLSEARCH );
            pRes = pCur->pParent->FindUserData( nData );
            pCur->SetFlags( nOwn );
            pCur->pParent->SetFlags( nPar );
            pCur = pCur->pParent;
        }
    }
    return pRes;
}

SbxVariable* SbxObject::Find( const XubString& rName, SbxClassType t )
{
#ifdef DBG_UTIL
    static USHORT nLvl = 0;
    static const char* pCls[] =
    { "DontCare","Array","Value","Variable","Method","Property","Object" };
    ByteString aNameStr1( (const UniString&)rName, RTL_TEXTENCODING_ASCII_US );
    ByteString aNameStr2( (const UniString&)SbxVariable::GetName(), RTL_TEXTENCODING_ASCII_US );
    DbgOutf( "SBX: Search %.*s %s %s in %s",
        nLvl++, "                              ",
        ( t >= SbxCLASS_DONTCARE && t <= SbxCLASS_OBJECT )
         ? pCls[ t-1 ] : "Unknown class", aNameStr1.GetBuffer(), aNameStr1.GetBuffer() );
#endif

    if( !GetAll( t ) )
        return NULL;
    SbxVariable* pRes = NULL;
    pObjs->SetFlag( SBX_EXTSEARCH );
    if( t == SbxCLASS_DONTCARE )
    {
        pRes = pMethods->Find( rName, SbxCLASS_METHOD );
        if( !pRes )
            pRes = pProps->Find( rName, SbxCLASS_PROPERTY );
        if( !pRes )
            pRes = pObjs->Find( rName, t );
    }
    else
    {
        SbxArray* pArray = NULL;
        switch( t )
        {
            case SbxCLASS_VARIABLE:
            case SbxCLASS_PROPERTY: pArray = pProps;	break;
            case SbxCLASS_METHOD: 	pArray = pMethods;	break;
            case SbxCLASS_OBJECT: 	pArray = pObjs;		break;
            default:
                DBG_ASSERT( !this, "Ungueltige SBX-Klasse" );
        }
        if( pArray )
            pRes = pArray->Find( rName, t );
    }
    // Extended Search im Objekt-Array?
    // Fuer Objekte und DontCare ist das Objektarray bereits
    // durchsucht worden
    if( !pRes && ( t == SbxCLASS_METHOD || t == SbxCLASS_PROPERTY ) )
        pRes = pObjs->Find( rName, t );
    // Search in den Parents?
    if( !pRes && IsSet( SBX_GBLSEARCH ) )
    {
        SbxObject* pCur = this;
        while( !pRes && pCur->pParent )
        {
            // Ich selbst bin schon durchsucht worden!
            USHORT nOwn = pCur->GetFlags();
            pCur->ResetFlag( SBX_EXTSEARCH );
            // Ich suche bereits global!
            USHORT nPar = pCur->pParent->GetFlags();
            pCur->pParent->ResetFlag( SBX_GBLSEARCH );
            pRes = pCur->pParent->Find( rName, t );
            pCur->SetFlags( nOwn );
            pCur->pParent->SetFlags( nPar );
            pCur = pCur->pParent;
        }
    }
#ifdef DBG_UTIL
    nLvl--;
    if( pRes )
    {
        ByteString aNameStr3( (const UniString&)rName, RTL_TEXTENCODING_ASCII_US );
        ByteString aNameStr4( (const UniString&)SbxVariable::GetName(), RTL_TEXTENCODING_ASCII_US );
        DbgOutf( "SBX: Found %.*s %s in %s",
            nLvl, "                              ", aNameStr3.GetBuffer(), aNameStr4.GetBuffer() );
    }
#endif
    return pRes;
}

// Kurzform: Die Parent-Kette wird durchsucht
// Das ganze rekursiv, da Call() ueberladen sein kann
// Qualified Names sind zugelassen

BOOL SbxObject::Call( const XubString& rName, SbxArray* pParam )
{
    SbxVariable* pMeth = FindQualified( rName, SbxCLASS_DONTCARE);
    if( pMeth && pMeth->ISA(SbxMethod) )
    {
        // FindQualified() koennte schon zugeschlagen haben!
        if( pParam )
            pMeth->SetParameters( pParam );
        pMeth->Broadcast( SBX_HINT_DATAWANTED );
        pMeth->SetParameters( NULL );
        return TRUE;
    }
    SetError( SbxERR_NO_METHOD );
    return FALSE;
}

SbxProperty* SbxObject::GetDfltProperty() 
{
    if ( !pDfltProp && aDfltPropName.Len() )
    {
        pDfltProp = (SbxProperty*) Find( aDfltPropName, SbxCLASS_PROPERTY );
        if( !pDfltProp )
            pDfltProp = (SbxProperty*) Make( aDfltPropName, SbxCLASS_PROPERTY, SbxVARIANT );
    }
    return pDfltProp;
}
void SbxObject::SetDfltProperty( const XubString& rName )
{
    if ( rName != aDfltPropName )
        pDfltProp = NULL; 
    aDfltPropName = rName;
    SetModified( TRUE );
}

void SbxObject::SetDfltProperty( SbxProperty* p )
{
    if( p )
    {
        USHORT n;
        SbxArray* pArray = FindVar( p, n );
        pArray->Put( p, n );
        if( p->GetParent() != this )
            p->SetParent( this );
        Broadcast( SBX_HINT_OBJECTCHANGED );
    }
    pDfltProp = p;
    SetModified( TRUE );
}

// Suchen einer bereits vorhandenen Variablen. Falls sie gefunden wurde,
// wird der Index gesetzt, sonst wird der Count des Arrays geliefert.
// In jedem Fall wird das korrekte Array geliefert.

SbxArray* SbxObject::FindVar( SbxVariable* pVar, USHORT& nArrayIdx )
{
    SbxArray* pArray = NULL;
    if( pVar ) switch( pVar->GetClass() )
    {
        case SbxCLASS_VARIABLE:
        case SbxCLASS_PROPERTY: pArray = pProps;	break;
        case SbxCLASS_METHOD: 	pArray = pMethods;	break;
        case SbxCLASS_OBJECT: 	pArray = pObjs;		break;
        default:
            DBG_ASSERT( !this, "Ungueltige SBX-Klasse" );
    }
    if( pArray )
    {
        nArrayIdx = pArray->Count();
        // ist die Variable per Name vorhanden?
        pArray->ResetFlag( SBX_EXTSEARCH );
        SbxVariable* pOld = pArray->Find( pVar->GetName(), pVar->GetClass() );
        if( pOld )
          for( USHORT i = 0; i < pArray->Count(); i++ )
        {
            SbxVariableRef& rRef = pArray->GetRef( i );
            if( (SbxVariable*) rRef == pOld )
            {
                nArrayIdx = i; break;
            }
        }
    }
    return pArray;
}

// Falls ein neues Objekt eingerichtet wird, wird es, falls es bereits
// eines mit diesem Namen gibt, indiziert.

SbxVariable* SbxObject::Make( const XubString& rName, SbxClassType ct, SbxDataType dt )
{
    // Ist das Objekt bereits vorhanden?
    SbxArray* pArray = NULL;
    switch( ct )
    {
        case SbxCLASS_VARIABLE:
        case SbxCLASS_PROPERTY: pArray = pProps;	break;
        case SbxCLASS_METHOD: 	pArray = pMethods;	break;
        case SbxCLASS_OBJECT: 	pArray = pObjs;		break;
        default:
            DBG_ASSERT( !this, "Ungueltige SBX-Klasse" );
    }
    if( !pArray )
        return NULL;
    // Collections duerfen gleichnamige Objekte enthalten
    if( !( ct == SbxCLASS_OBJECT && ISA(SbxCollection) ) )
    {
        SbxVariable* pRes = pArray->Find( rName, ct );
        if( pRes )
        {
/* Wegen haeufiger Probleme (z.B. #67000) erstmal ganz raus
#ifdef DBG_UTIL
            if( pRes->GetHashCode() != nNameHash
             && pRes->GetHashCode() != nParentHash )
            {
                XubString aMsg( "SBX-Element \"" );
                aMsg += pRes->GetName();
                aMsg += "\"\n in Objekt \"";
                aMsg += GetName();
                aMsg += "\" bereits vorhanden";
                DbgError( (const char*)aMsg.GetStr() );
            }
#endif
*/
            return pRes;
        }
    }
    SbxVariable* pVar = NULL;
    switch( ct )
    {
        case SbxCLASS_VARIABLE:
        case SbxCLASS_PROPERTY:
            pVar = new SbxProperty( rName, dt );
            break;
        case SbxCLASS_METHOD:
            pVar = new SbxMethod( rName, dt );
            break;
        case SbxCLASS_OBJECT:
            pVar = CreateObject( rName );
            break;
        default: break;
    }
    pVar->SetParent( this );
    pArray->Put( pVar, pArray->Count() );
    SetModified( TRUE );
    // Das Objekt lauscht immer
    StartListening( pVar->GetBroadcaster(), TRUE );
    Broadcast( SBX_HINT_OBJECTCHANGED );
    return pVar;
}

SbxObject* SbxObject::MakeObject( const XubString& rName, const XubString& rClass )
{
    // Ist das Objekt bereits vorhanden?
    if( !ISA(SbxCollection) )
    {
        SbxVariable* pRes = pObjs->Find( rName, SbxCLASS_OBJECT );
        if( pRes )
        {
/* Wegen haeufiger Probleme (z.B. #67000) erstmal ganz raus
#ifdef DBG_UTIL
            if( pRes->GetHashCode() != nNameHash
             && pRes->GetHashCode() != nParentHash )
            {
                XubString aMsg( "SBX-Objekt \"" );
                aMsg += pRes->GetName();
                aMsg += "\"\n in Objekt \"";
                aMsg += GetName();
                aMsg += "\" bereits vorhanden";
                DbgError( (const char*)aMsg.GetStr() );
            }
#endif
*/
            return PTR_CAST(SbxObject,pRes);
        }
    }
    SbxObject* pVar = CreateObject( rClass );
    if( pVar )
    {
        pVar->SetName( rName );
        pVar->SetParent( this );
        pObjs->Put( pVar, pObjs->Count() );
        SetModified( TRUE );
        // Das Objekt lauscht immer
        StartListening( pVar->GetBroadcaster(), TRUE );
        Broadcast( SBX_HINT_OBJECTCHANGED );
    }
    return pVar;
}

void SbxObject::Insert( SbxVariable* pVar )
{
    USHORT nIdx;
    SbxArray* pArray = FindVar( pVar, nIdx );
    if( pArray )
    {
        // Hinein damit. Man sollte allerdings auf die Pointer aufpassen!
        if( nIdx < pArray->Count() )
        {
            // dann gibt es dieses Element bereits
            // Bei Collections duerfen gleichnamige Objekte hinein
            if( pArray == pObjs && ISA(SbxCollection) )
                nIdx = pArray->Count();
            else
            {
                SbxVariable* pOld = pArray->Get( nIdx );
                // schon drin: ueberschreiben
                if( pOld == pVar )
                    return;

/* Wegen haeufiger Probleme (z.B. #67000) erstmal ganz raus
#ifdef DBG_UTIL
                if( pOld->GetHashCode() != nNameHash
                 && pOld->GetHashCode() != nParentHash )
                {
                    XubString aMsg( "SBX-Element \"" );
                    aMsg += pVar->GetName();
                    aMsg += "\"\n in Objekt \"";
                    aMsg += GetName();
                    aMsg += "\" bereits vorhanden";
                    DbgError( (const char*)aMsg.GetStr() );
                }
#endif
*/
                EndListening( pOld->GetBroadcaster(), TRUE );
                if( pVar->GetClass() == SbxCLASS_PROPERTY )
                {
                    if( pOld == pDfltProp )
                        pDfltProp = (SbxProperty*) pVar;
                }
            }
        }
        StartListening( pVar->GetBroadcaster(), TRUE );
        pArray->Put( pVar, nIdx );
        if( pVar->GetParent() != this )
            pVar->SetParent( this );
        SetModified( TRUE );
        Broadcast( SBX_HINT_OBJECTCHANGED );
#ifdef DBG_UTIL
    static const char* pCls[] =
    { "DontCare","Array","Value","Variable","Method","Property","Object" };
    XubString aVarName( pVar->GetName() );
    if ( !aVarName.Len() && pVar->ISA(SbxObject) )
        aVarName = PTR_CAST(SbxObject,pVar)->GetClassName();
    ByteString aNameStr1( (const UniString&)aVarName, RTL_TEXTENCODING_ASCII_US );
    ByteString aNameStr2( (const UniString&)SbxVariable::GetName(), RTL_TEXTENCODING_ASCII_US );
    DbgOutf( "SBX: Insert %s %s in %s",
        ( pVar->GetClass() >= SbxCLASS_DONTCARE &&
          pVar->GetClass() <= SbxCLASS_OBJECT )
            ? pCls[ pVar->GetClass()-1 ] : "Unknown class", aNameStr1.GetBuffer(), aNameStr1.GetBuffer() );
#endif
    }
}

// AB 23.4.1997, Optimierung, Einfuegen ohne Ueberpruefung auf doppelte
// Eintraege und ohne Broadcasts, wird nur in SO2/auto.cxx genutzt
void SbxObject::QuickInsert( SbxVariable* pVar )
{
    SbxArray* pArray = NULL;
    if( pVar )
    {
        switch( pVar->GetClass() )
        {
            case SbxCLASS_VARIABLE:
            case SbxCLASS_PROPERTY: pArray = pProps;	break;
            case SbxCLASS_METHOD: 	pArray = pMethods;	break;
            case SbxCLASS_OBJECT: 	pArray = pObjs;		break;
            default:
                DBG_ASSERT( !this, "Ungueltige SBX-Klasse" );
        }
    }
    if( pArray )
    {
        StartListening( pVar->GetBroadcaster(), TRUE );
        pArray->Put( pVar, pArray->Count() );
        if( pVar->GetParent() != this )
            pVar->SetParent( this );
        SetModified( TRUE );
#ifdef DBG_UTIL
    static const char* pCls[] =
    { "DontCare","Array","Value","Variable","Method","Property","Object" };
    XubString aVarName( pVar->GetName() );
    if ( !aVarName.Len() && pVar->ISA(SbxObject) )
        aVarName = PTR_CAST(SbxObject,pVar)->GetClassName();
    ByteString aNameStr1( (const UniString&)aVarName, RTL_TEXTENCODING_ASCII_US );
    ByteString aNameStr2( (const UniString&)SbxVariable::GetName(), RTL_TEXTENCODING_ASCII_US );
    DbgOutf( "SBX: Insert %s %s in %s",
        ( pVar->GetClass() >= SbxCLASS_DONTCARE &&
          pVar->GetClass() <= SbxCLASS_OBJECT )
            ? pCls[ pVar->GetClass()-1 ] : "Unknown class", aNameStr1.GetBuffer(), aNameStr1.GetBuffer() );
#endif
    }
}

// AB 23.3.1997, Spezial-Methode, gleichnamige Controls zulassen
void SbxObject::VCPtrInsert( SbxVariable* pVar )
{
    SbxArray* pArray = NULL;
    if( pVar )
    {
        switch( pVar->GetClass() )
        {
            case SbxCLASS_VARIABLE:
            case SbxCLASS_PROPERTY: pArray = pProps;	break;
            case SbxCLASS_METHOD: 	pArray = pMethods;	break;
            case SbxCLASS_OBJECT: 	pArray = pObjs;		break;
            default:
                DBG_ASSERT( !this, "Ungueltige SBX-Klasse" );
        }
    }
    if( pArray )
    {
        StartListening( pVar->GetBroadcaster(), TRUE );
        pArray->Put( pVar, pArray->Count() );
        if( pVar->GetParent() != this )
            pVar->SetParent( this );
        SetModified( TRUE );
        Broadcast( SBX_HINT_OBJECTCHANGED );
    }
}

void SbxObject::Remove( const XubString& rName, SbxClassType t )
{
    Remove( SbxObject::Find( rName, t ) );
}

void SbxObject::Remove( SbxVariable* pVar )
{
    USHORT nIdx;
    SbxArray* pArray = FindVar( pVar, nIdx );
    if( pArray && nIdx < pArray->Count() )
    {
#ifdef DBG_UTIL
    XubString aVarName( pVar->GetName() );
    if ( !aVarName.Len() && pVar->ISA(SbxObject) )
        aVarName = PTR_CAST(SbxObject,pVar)->GetClassName();
    ByteString aNameStr1( (const UniString&)aVarName, RTL_TEXTENCODING_ASCII_US );
    ByteString aNameStr2( (const UniString&)SbxVariable::GetName(), RTL_TEXTENCODING_ASCII_US );
#endif
        SbxVariableRef pVar_ = pArray->Get( nIdx );
        if( pVar_->IsBroadcaster() )
            EndListening( pVar_->GetBroadcaster(), TRUE );
        if( (SbxVariable*) pVar_ == pDfltProp )
            pDfltProp = NULL;
        pArray->Remove( nIdx );
        if( pVar_->GetParent() == this )
            pVar_->SetParent( NULL );
        SetModified( TRUE );
        Broadcast( SBX_HINT_OBJECTCHANGED );
    }
}

// AB 23.3.1997, Loeschen per Pointer fuer Controls (doppelte Namen!)
void SbxObject::VCPtrRemove( SbxVariable* pVar )
{
    USHORT nIdx;
    // Neu FindVar-Methode, sonst identisch mit normaler Methode
    SbxArray* pArray = VCPtrFindVar( pVar, nIdx );
    if( pArray && nIdx < pArray->Count() )
    {
        SbxVariableRef xVar = pArray->Get( nIdx );
        if( xVar->IsBroadcaster() )
            EndListening( xVar->GetBroadcaster(), TRUE );
        if( (SbxVariable*) xVar == pDfltProp )
            pDfltProp = NULL;
        pArray->Remove( nIdx );
        if( xVar->GetParent() == this )
            xVar->SetParent( NULL );
        SetModified( TRUE );
        Broadcast( SBX_HINT_OBJECTCHANGED );
    }
}

// AB 23.3.1997, Zugehoerige Spezial-Methode, nur ueber Pointer suchen
SbxArray* SbxObject::VCPtrFindVar( SbxVariable* pVar, USHORT& nArrayIdx )
{
    SbxArray* pArray = NULL;
    if( pVar ) switch( pVar->GetClass() )
    {
        case SbxCLASS_VARIABLE:
        case SbxCLASS_PROPERTY: pArray = pProps;	break;
        case SbxCLASS_METHOD: 	pArray = pMethods;	break;
        case SbxCLASS_OBJECT: 	pArray = pObjs;		break;
        default:
            DBG_ASSERT( !this, "Ungueltige SBX-Klasse" );
    }
    if( pArray )
    {
        nArrayIdx = pArray->Count();
        for( USHORT i = 0; i < pArray->Count(); i++ )
        {
            SbxVariableRef& rRef = pArray->GetRef( i );
            if( (SbxVariable*) rRef == pVar )
            {
                nArrayIdx = i; break;
            }
        }
    }
    return pArray;
}



void SbxObject::SetPos( SbxVariable* pVar, USHORT nPos )
{
    USHORT nIdx;
    SbxArray* pArray = FindVar( pVar, nIdx );
    if( pArray )
    {
        if( nPos >= pArray->Count() )
            nPos = pArray->Count() - 1;
        if( nIdx < ( pArray->Count() - 1 ) )
        {
            SbxVariableRef refVar = pArray->Get( nIdx );
            pArray->Remove( nIdx );
            pArray->Insert( refVar, nPos );
        }
    }
//	SetModified( TRUE );
//	Broadcast( SBX_HINT_OBJECTCHANGED );
}

static BOOL LoadArray( SvStream& rStrm, SbxObject* pThis, SbxArray* pArray )
{
    SbxArrayRef p = (SbxArray*) SbxBase::Load( rStrm );
    if( !p.Is() )
        return FALSE;
    for( USHORT i = 0; i < p->Count(); i++ )
    {
        SbxVariableRef& r = p->GetRef( i );
        SbxVariable* pVar = r;
        if( pVar )
        {
            pVar->SetParent( pThis );
            pThis->StartListening( pVar->GetBroadcaster(), TRUE );
        }
    }
    pArray->Merge( p );
    return TRUE;
}

// Der Load eines Objekts ist additiv!

BOOL SbxObject::LoadData( SvStream& rStrm, USHORT nVer )
{
    // Hilfe fuer das Einlesen alter Objekte: einfach TRUE zurueck,
    // LoadPrivateData() muss Default-Zustand herstellen
    if( !nVer )
        return TRUE;

    pDfltProp = NULL;
    if( !SbxVariable::LoadData( rStrm, nVer ) )
        return FALSE;
    // Wenn kein fremdes Objekt enthalten ist, uns selbst eintragen
    if( aData.eType == SbxOBJECT && !aData.pObj )
        aData.pObj = this;
    sal_uInt32 nSize;
    XubString aDfltProp;
    rStrm.ReadByteString( aClassName, RTL_TEXTENCODING_ASCII_US );
    rStrm.ReadByteString( aDfltProp, RTL_TEXTENCODING_ASCII_US );
    ULONG nPos = rStrm.Tell();
    rStrm >> nSize;
    if( !LoadPrivateData( rStrm, nVer ) )
        return FALSE;
    ULONG nNewPos = rStrm.Tell();
    nPos += nSize;
    DBG_ASSERT( nPos >= nNewPos, "SBX: Zu viele Daten eingelesen" );
    if( nPos != nNewPos )
        rStrm.Seek( nPos );
    if( !LoadArray( rStrm, this, pMethods )
     || !LoadArray( rStrm, this, pProps )
     || !LoadArray( rStrm, this, pObjs ) )
        return FALSE;
    // Properties setzen
    if( aDfltProp.Len() )
        pDfltProp = (SbxProperty*) pProps->Find( aDfltProp, SbxCLASS_PROPERTY );
    SetModified( FALSE );
    return TRUE;
}

BOOL SbxObject::StoreData( SvStream& rStrm ) const
{
    if( !SbxVariable::StoreData( rStrm ) )
        return FALSE;
    XubString aDfltProp;
    if( pDfltProp )
        aDfltProp = pDfltProp->GetName();
    rStrm.WriteByteString( aClassName, RTL_TEXTENCODING_ASCII_US );
    rStrm.WriteByteString( aDfltProp, RTL_TEXTENCODING_ASCII_US );
    ULONG nPos = rStrm.Tell();
    rStrm << (UINT32) 0L;
    if( !StorePrivateData( rStrm ) )
        return FALSE;
    ULONG nNew = rStrm.Tell();
    rStrm.Seek( nPos );
    rStrm << (UINT32) ( nNew - nPos );
    rStrm.Seek( nNew );
    if( !pMethods->Store( rStrm ) )
        return FALSE;
    if( !pProps->Store( rStrm ) )
        return FALSE;
    if( !pObjs->Store( rStrm ) )
        return FALSE;
    ((SbxObject*) this)->SetModified( FALSE );
    return TRUE;
}

XubString SbxObject::GenerateSource( const XubString &rLinePrefix,
                                  const SbxObject* )
{
    // Properties in einem String einsammeln
    XubString aSource;
    SbxArrayRef xProps( GetProperties() );
    FASTBOOL bLineFeed = FALSE;
    for ( USHORT nProp = 0; nProp < xProps->Count(); ++nProp )
    {
        SbxPropertyRef xProp = (SbxProperty*) xProps->Get(nProp);
        XubString aPropName( xProp->GetName() );
        if ( xProp->CanWrite()
         && !( xProp->GetHashCode() == nNameHash
            && aPropName.EqualsIgnoreCaseAscii( pNameProp ) ) )
        {
            // ausser vor dem ersten Property immer einen Umbruch einfuegen
            if ( bLineFeed )
                aSource.AppendAscii( "\n" );
            else
                bLineFeed = TRUE;

            aSource += rLinePrefix;
            aSource += '.';
            aSource += aPropName;
            aSource.AppendAscii( " = " );

            // den Property-Wert textuell darstellen
            switch ( xProp->GetType() )
            {
                case SbxEMPTY:
                case SbxNULL:
                    // kein Wert
                    break;

                case SbxSTRING:
                {
                    // Strings in Anf"uhrungszeichen
                    aSource.AppendAscii( "\"" );
                    aSource += xProp->GetString();
                    aSource.AppendAscii( "\"" );
                    break;
                }

                default:
                {
                    // sonstiges wie z.B. Zahlen direkt
                    aSource += xProp->GetString();
                    break;
                }
            }
        }
    }
    return aSource;
}

static BOOL CollectAttrs( const SbxBase* p, XubString& rRes )
{
    XubString aAttrs;
    if( p->IsHidden() )
        aAttrs.AssignAscii( "Hidden" );
    if( p->IsSet( SBX_EXTSEARCH ) )
    {
        if( aAttrs.Len() )
            aAttrs += ',';
        aAttrs.AppendAscii( "ExtSearch" );
    }
    if( !p->IsVisible() )
    {
        if( aAttrs.Len() )
            aAttrs += ',';
        aAttrs.AppendAscii( "Invisible" );
    }
    if( p->IsSet( SBX_DONTSTORE ) )
    {
        if( aAttrs.Len() )
            aAttrs += ',';
        aAttrs.AppendAscii( "DontStore" );
    }
    if( aAttrs.Len() )
    {
        rRes.AssignAscii( " (" );
        rRes += aAttrs;
        rRes += ')';
        return TRUE;
    }
    else
    {
        rRes.Erase();
        return FALSE;
    }
}

void SbxObject::Dump( SvStream& rStrm, BOOL bFill )
{
    // Einr"uckung
    static USHORT nLevel = 0;
    if ( nLevel > 10 )
    {
        rStrm << "<too deep>" << endl;
        return;
    }
    ++nLevel;
    String aIndent;
    for ( USHORT n = 1; n < nLevel; ++n )
        aIndent.AppendAscii( "    " );

    // ggf. Objekt vervollst"andigen
    if ( bFill )
        GetAll( SbxCLASS_DONTCARE );

    // Daten des Objekts selbst ausgeben
    ByteString aNameStr( (const UniString&)GetName(), RTL_TEXTENCODING_ASCII_US );
    ByteString aClassNameStr( (const UniString&)aClassName, RTL_TEXTENCODING_ASCII_US );
    rStrm << "Object( "
          << ByteString::CreateFromInt64( (ULONG) this ).GetBuffer() << "=='"
          << ( aNameStr.Len() ? aNameStr.GetBuffer() : "<unnamed>" ) << "', "
          << "of class '" << aClassNameStr.GetBuffer() << "', "
          << "counts "
          << ByteString::CreateFromInt64( GetRefCount() ).GetBuffer()
          << " refs, ";
    if ( GetParent() )
    {
        ByteString aParentNameStr( (const UniString&)GetName(), RTL_TEXTENCODING_ASCII_US );
        rStrm << "in parent "
              << ByteString::CreateFromInt64( (ULONG) GetParent() ).GetBuffer()
              << "=='" << ( aParentNameStr.Len() ? aParentNameStr.GetBuffer() : "<unnamed>" ) << "'";
    }
    else
        rStrm << "no parent ";
    rStrm << " )" << endl;
    ByteString aIndentNameStr( (const UniString&)aIndent, RTL_TEXTENCODING_ASCII_US );
    rStrm << aIndentNameStr.GetBuffer() << "{" << endl;

    // Flags
    XubString aAttrs;
    if( CollectAttrs( this, aAttrs ) )
    {
        ByteString aAttrStr( (const UniString&)aAttrs, RTL_TEXTENCODING_ASCII_US );
        rStrm << aIndentNameStr.GetBuffer() << "- Flags: " << aAttrStr.GetBuffer() << endl;
    }

    // Methods
    rStrm << aIndentNameStr.GetBuffer() << "- Methods:" << endl;
    for( USHORT i = 0; i < pMethods->Count(); i++ )
    {
        SbxVariableRef& r = pMethods->GetRef( i );
        SbxVariable* pVar = r;
        if( pVar )
        {
            XubString aLine( aIndent );
            aLine.AppendAscii( "  - " );
            aLine += pVar->GetName( SbxNAME_SHORT_TYPES );
            XubString aAttrs2;
            if( CollectAttrs( pVar, aAttrs2 ) )
                aLine += aAttrs2;
            if( !pVar->IsA( TYPE(SbxMethod) ) )
                aLine.AppendAscii( "  !! Not a Method !!" );
            rStrm.WriteByteString( aLine, RTL_TEXTENCODING_ASCII_US );

            // bei Object-Methods auch das Object ausgeben
            if ( pVar->GetValues_Impl().eType == SbxOBJECT &&
                    pVar->GetValues_Impl().pObj &&
                    pVar->GetValues_Impl().pObj != this &&
                    pVar->GetValues_Impl().pObj != GetParent() )
            {
                rStrm << " contains ";
                ((SbxObject*) pVar->GetValues_Impl().pObj)->Dump( rStrm, bFill );
            }
            else
                rStrm << endl;
        }
    }

    // Properties
    rStrm << aIndentNameStr.GetBuffer() << "- Properties:" << endl;
    {
        for( USHORT i = 0; i < pProps->Count(); i++ )
        {
            SbxVariableRef& r = pProps->GetRef( i );
            SbxVariable* pVar = r;
            if( pVar )
            {
                XubString aLine( aIndent );
                aLine.AppendAscii( "  - " );
                aLine += pVar->GetName( SbxNAME_SHORT_TYPES );
                XubString aAttrs3;
                if( CollectAttrs( pVar, aAttrs3 ) )
                    aLine += aAttrs3;
                if( !pVar->IsA( TYPE(SbxProperty) ) )
                    aLine.AppendAscii( "  !! Not a Property !!" );
                rStrm.WriteByteString( aLine, RTL_TEXTENCODING_ASCII_US );

                // bei Object-Properties auch das Object ausgeben
                if ( pVar->GetValues_Impl().eType == SbxOBJECT &&
                        pVar->GetValues_Impl().pObj &&
                        pVar->GetValues_Impl().pObj != this &&
                        pVar->GetValues_Impl().pObj != GetParent() )
                {
                    rStrm << " contains ";
                    ((SbxObject*) pVar->GetValues_Impl().pObj)->Dump( rStrm, bFill );
                }
                else
                    rStrm << endl;
            }
        }
    }

    // Objects
    rStrm << aIndentNameStr.GetBuffer() << "- Objects:" << endl;
    {
        for( USHORT i = 0; i < pObjs->Count(); i++ )
        {
            SbxVariableRef& r = pObjs->GetRef( i );
            SbxVariable* pVar = r;
            if ( pVar )
            {
                rStrm << aIndentNameStr.GetBuffer() << "  - Sub";
                if ( pVar->ISA(SbxObject) )
                    ((SbxObject*) pVar)->Dump( rStrm, bFill );
                else if ( pVar->ISA(SbxVariable) )
                    ((SbxVariable*) pVar)->Dump( rStrm, bFill );
            }
        }
    }

    rStrm << aIndentNameStr.GetBuffer() << "}" << endl << endl;
    --nLevel;
}

SvDispatch* SbxObject::GetSvDispatch()
{
    return NULL;
}

BOOL SbxMethod::Run( SbxValues* pValues )
{
    SbxValues aRes;
    if( !pValues )
        pValues = &aRes;
    pValues->eType = SbxVARIANT;
    return Get( *pValues );
}

SbxClassType SbxMethod::GetClass() const
{
    return SbxCLASS_METHOD;
}

SbxClassType SbxProperty::GetClass() const
{
    return SbxCLASS_PROPERTY;
}

void SbxObject::GarbageCollection( ULONG nObjects )

/*	[Beschreibung]

    Diese statische Methode durchsucht die n"achsten 'nObjects' der zur Zeit
    existierenden <SbxObject>-Instanzen nach zyklischen Referenzen, die sich
    nur noch selbst am Leben erhalten. Ist 'nObjects==0', dann werden
    alle existierenden durchsucht.

    zur Zeit nur implementiert: Object -> Parent-Property -> Parent -> Object
*/

{
    (void)nObjects;
    
    static BOOL bInGarbageCollection = FALSE;
    if ( bInGarbageCollection )
        return;
    bInGarbageCollection = TRUE;

#if 0
    // erstes Object dieser Runde anspringen
    BOOL bAll = !nObjects;
    if ( bAll )
        rObjects.First();
    SbxObject *pObj = rObjects.GetCurObject();
    if ( !pObj )
        pObj = rObjects.First();

    while ( pObj && 0 != nObjects-- )
    {
        // hat der Parent nur noch 1 Ref-Count?
        SbxObject *pParent = PTR_CAST( SbxObject, pObj->GetParent() );
        if ( pParent && 1 == pParent->GetRefCount() )
        {
            // dann alle Properies des Objects durchsuchen
            SbxArray *pProps = pObj->GetProperties();
            for ( USHORT n = 0; n < pProps->Count(); ++n )
            {
                // verweist die Property auf den Parent des Object?
                SbxVariable *pProp = pProps->Get(n);
                const SbxValues &rValues = pProp->GetValues_Impl();
                if ( SbxOBJECT == rValues.eType &&
                     pParent == rValues.pObj )
                {
#ifdef DBG_UTIL
                    DbgOutf( "SBX: %s.%s with Object %s was garbage",
                             pObj->GetName().GetStr(),
                             pProp->GetName().GetStr(),
                             pParent->GetName().GetStr() );
#endif
                    // dann freigeben
                    pProp->SbxValue::Clear();
                    Sound::Beep();
                    break;
                }
            }
        }

        // zum n"achsten
        pObj = rObjects.Next();
        if ( !bAll && !pObj )
            pObj = rObjects.First();
    }
#endif

// AB 28.10. Zur 507a vorerst raus, da SfxBroadcaster::Enable() wegfaellt
#if 0
#ifdef DBG_UTIL
    SbxVarList_Impl &rVars = GetSbxData_Impl()->aVars;
    DbgOutf( "SBX: garbage collector done, %lu objects remainding",
             rVars.Count() );
    if ( rVars.Count() > 200 && rVars.Count() < 210 )
    {
        SvFileStream aStream( "d:\\tmp\\dump.sbx", STREAM_STD_WRITE );
        SfxBroadcaster::Enable(FALSE);
        for ( ULONG n = 0; n < rVars.Count(); ++n )
        {
            SbxVariable *pVar = rVars.GetObject(n);
            SbxObject *pObj = PTR_CAST(SbxObject, pVar);
            USHORT nFlags = pVar->GetFlags();
            pVar->SetFlag(SBX_NO_BROADCAST);
            if ( pObj )
                pObj->Dump(aStream);
            else if ( !pVar->GetParent() || !pVar->GetParent()->ISA(SbxObject) )
                pVar->Dump(aStream);
            pVar->SetFlags(nFlags);
        }
        SfxBroadcaster::Enable(TRUE);
    }
#endif
#endif
    bInGarbageCollection = FALSE;
}

}
