/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: sbx.hxx,v $
 *
 *  $Revision: 1.3 $
 *
 *  last change: $Author: rt $ $Date: 2008-03-12 11:07:07 $
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

#ifndef _SBXCLASS_HXX
#define _SBXCLASS_HXX

#ifndef _REF_HXX
#include "tools/ref.hxx"
#endif

#ifndef _SVARRAY_HXX
#include "bf_svtools/svarray.hxx"
#endif
#ifndef _SFXSMPLHINT_HXX
#include "bf_svtools/smplhint.hxx"
#endif
#ifndef _SFXLSTNER_HXX
#include "bf_svtools/lstner.hxx"
#endif

#ifndef _SBXDEF_HXX
#include "sbxdef.hxx"
#endif

#ifndef _SBXFORM_HXX
#include "sbxform.hxx"
#endif

#ifndef __SBX_SBXOBJECT_HXX
#include "sbxobj.hxx"
#endif
#ifndef __SBX_SBXPROPERTY_HXX
#include "sbxprop.hxx"
#endif
#ifndef __SBX_SBXMETHOD_HXX
#include "sbxmeth.hxx"
#endif

class BigInt;
class String;
class UniString;
class SvStream;

class SvDispatch;

///////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////


namespace binfilter {

class SfxBroadcaster;

#ifndef __SBX_SBXPARAMINFO
#define __SBX_SBXPARAMINFO

class SbxBase;
class SbxVariable;
class SbxProperty;
class SbxMethod;
class SbxObject;
class SbxArray;
class SbxDimArray;
class SbxFactory;
struct SbxINT64;
struct SbxUINT64;

// Informationen ueber einen Parameter

struct SbxParamInfo
{
    const String aName;	  			// Name des Parameters
    SbxBaseRef   aTypeRef;			// Objekt, falls Objekttyp
    SbxDataType  eType;  	 		// Datentyp
    UINT16       nFlags;			// Flag-Bits
    UINT32		 nUserData;			// IDs etc.
    SbxParamInfo( const String& s, SbxDataType t, USHORT n, SbxBase* b = NULL )
    : aName( s ), aTypeRef( b ), eType( t ), nFlags( n ), nUserData( 0 ) {}
    ~SbxParamInfo() {}
};

#if _SOLAR__PRIVATE
SV_DECL_PTRARR_DEL(SbxParams,SbxParamInfo*,4,4)
#else
typedef SvPtrarr SbxParams;
#endif

#endif

#ifndef __SBX_SBXINFO
#define __SBX_SBXINFO

class SbxInfo : public SvRefBase
{
    friend class SbxVariable;
    friend class SbMethod;

    String			aComment;
    String			aHelpFile;
    UINT32			nHelpId;
    SbxParams		aParams;

protected:
    BOOL LoadData( SvStream&, USHORT );
    BOOL StoreData( SvStream& ) const;
    virtual ~SbxInfo();
public:
    SbxInfo();
    SbxInfo( const String&, UINT32 );

    void				AddParam( const String&, SbxDataType, USHORT=SBX_READ );
    void				AddParam( const SbxParamInfo& );
    const SbxParamInfo*	GetParam( USHORT n ) const;	// ab 1!
    const String&		GetComment() const				{ return aComment; }
    const String&		GetHelpFile() const    			{ return aHelpFile; }
    UINT32				GetHelpId() const				{ return nHelpId;   }

    void				SetComment( const String& r )	{ aComment = r; }
    void				SetHelpFile( const String& r )	{ aHelpFile = r; }
    void				SetHelpId( UINT32 nId )			{ nHelpId = nId; }
};

#endif

#ifndef __SBX_SBXHINT_HXX
#define __SBX_SBXHINT_HXX

class SbxHint : public SfxSimpleHint
{
    SbxVariable* pVar;
public:
    TYPEINFO();
    SbxHint( ULONG n, SbxVariable* v ) : SfxSimpleHint( n ), pVar( v ) {}
    SbxVariable* GetVar() const { return pVar; }
};

#endif

#ifndef __SBX_SBXALIAS_HXX
#define __SBX_SBXALIAS_HXX

// SbxAlias ist ein Alias fuer eine Variable oder ein Objekt

class SbxAlias : public SbxVariable, public SfxListener
{
    SbxVariableRef xAlias;
    virtual ~SbxAlias();
    virtual void Broadcast( ULONG );
    virtual void SFX_NOTIFY( SfxBroadcaster& rBC, const TypeId& rBCType,
                             const SfxHint& rHint, const TypeId& rHintType );
public:
    SbxAlias( const String& rName, SbxVariable* pOriginal );
    SbxAlias( const SbxAlias& );
    SbxAlias& operator=( const SbxAlias& );
};

#endif


#ifndef __SBX_SBXARRAY
#define __SBX_SBXARRAY

// SbxArray ist ein eindimensionales, dynamisches Array
// von SbxVariablen. Put()/Insert() konvertieren die Variablen in den
// angegebenen Datentyp, falls er nicht SbxVARIANT ist.

class SbxVarRefs;
class SbxVariableRef;

class SbxArrayImpl;

class SbxArray : public SbxBase
{
// #100883 Method to set method directly to parameter array
    friend class SbMethod;
    friend class SbTypeFactory;
    friend class SbClassModuleObject;
    void PutDirect( SbxVariable* pVar, UINT32 nIdx );

    SbxArrayImpl* mpSbxArrayImpl;	// Impl data
    SbxVarRefs* pData;				// Die Variablen

protected:
    SbxDataType eType;              // Datentyp des Arrays
    virtual ~SbxArray();
    virtual BOOL LoadData( SvStream&, USHORT );
    virtual BOOL StoreData( SvStream& ) const;

public:
    SBX_DECL_PERSIST_NODATA(SBXCR_SBX,SBXID_ARRAY,1);
    TYPEINFO();
    SbxArray( SbxDataType=SbxVARIANT );
    SbxArray( const SbxArray& );
    SbxArray& operator=( const SbxArray& );
    virtual void Clear();
    USHORT Count() const;
    virtual SbxDataType GetType() const;
    virtual SbxClassType GetClass() const;
    SbxVariableRef& GetRef( USHORT );
    SbxVariable* Get( USHORT );
    void Put( SbxVariable*, USHORT );
    void Insert( SbxVariable*, USHORT );
    void Remove( USHORT );
    void Remove( SbxVariable* );
    void Merge( SbxArray* );
    const String& GetAlias( USHORT );
    void PutAlias( const String&, USHORT );
    SbxVariable* FindUserData( UINT32 nUserData );
    virtual SbxVariable* Find( const String&, SbxClassType );

    // Additional methods for 32-bit indices
    UINT32 Count32() const;
    SbxVariableRef& GetRef32( UINT32 );
    SbxVariable* Get32( UINT32 );
    void Put32( SbxVariable*, UINT32 );
    void Insert32( SbxVariable*, UINT32 );
    void Remove32( UINT32 );
};

#endif

#ifndef __SBX_SBXDIMARRAY_HXX
#define __SBX_SBXDIMARRAY_HXX

// SbxDimArray ist ein Array, was nach BASIC-Konventionen
// dimensioniert werden kann.

struct SbxDim;

class SbxDimArrayImpl;

class SbxDimArray : public SbxArray
{
    SbxDimArrayImpl* mpSbxDimArrayImpl;		// Impl data

    SbxDim* pFirst, *pLast;         // Links fuer Dimension-Tabelle
    short   nDim;                   // Anzahl Dimensionen
    void   AddDimImpl32( INT32, INT32, BOOL bAllowSize0 );
protected:
    USHORT  Offset( const short* );
    UINT32  Offset32( const INT32* );
    USHORT  Offset( SbxArray* );
    UINT32  Offset32( SbxArray* );
    virtual BOOL LoadData( SvStream&, USHORT );
    virtual BOOL StoreData( SvStream& ) const;
    virtual ~SbxDimArray();
public:
    SBX_DECL_PERSIST_NODATA(SBXCR_SBX,SBXID_DIMARRAY,1);
    TYPEINFO();
    SbxDimArray( SbxDataType=SbxVARIANT );
    SbxDimArray( const SbxDimArray& );
    SbxDimArray& operator=( const SbxDimArray& );
    virtual void Clear();
    using SbxArray::GetRef;
    SbxVariableRef& GetRef( const short* );
    using SbxArray::Get;
    SbxVariable* Get( const short* );
    using SbxArray::Put;
    void Put( SbxVariable*, const short* );
    SbxVariableRef& GetRef( SbxArray* );
    SbxVariable* Get( SbxArray* );
    void Put( SbxVariable*, SbxArray* );

    short  GetDims() const { return nDim;  }
    void   AddDim( short, short );
    void   unoAddDim( short, short );
    BOOL   GetDim( short, short&, short& ) const;

    using SbxArray::GetRef32;
    SbxVariableRef& GetRef32( const INT32* );
    using SbxArray::Get32;
    SbxVariable* Get32( const INT32* );
    using SbxArray::Put32;
    void Put32( SbxVariable*, const INT32* );
    void   AddDim32( INT32, INT32 );
    void   unoAddDim32( INT32, INT32 );
    BOOL   GetDim32( INT32, INT32&, INT32& ) const;
};

#endif

#ifndef __SBX_SBXCOLLECTION_HXX
#define __SBX_SBXCOLLECTION_HXX

class SbxCollection : public SbxObject
{
    void Initialize();
protected:
    virtual ~SbxCollection();
    virtual BOOL LoadData( SvStream&, USHORT );
    virtual void SFX_NOTIFY( SfxBroadcaster& rBC, const TypeId& rBCType,
                             const SfxHint& rHint, const TypeId& rHintType );
    // ueberladbare Methoden:
    virtual void CollAdd( SbxArray* pPar );
    virtual void CollItem( SbxArray* pPar );
    virtual void CollRemove( SbxArray* pPar );

public:
    SBX_DECL_PERSIST_NODATA(SBXCR_SBX,SBXID_COLLECTION,1);
    TYPEINFO();
    SbxCollection( const String& rClassname );
    SbxCollection( const SbxCollection& );
    SbxCollection& operator=( const SbxCollection& );
    virtual SbxVariable* FindUserData( UINT32 nUserData );
    virtual SbxVariable* Find( const String&, SbxClassType );
    virtual void Clear();
};

#endif

#ifndef __SBX_SBXSTDCOLLECTION_HXX
#define __SBX_SBXSTDCOLLECTION_HXX

class SbxStdCollection : public SbxCollection
{
protected:
    String aElemClass;
    BOOL   bAddRemoveOk;
    virtual ~SbxStdCollection();
    virtual BOOL LoadData( SvStream&, USHORT );
    virtual BOOL StoreData( SvStream& ) const;
    virtual void CollAdd( SbxArray* pPar );
    virtual void CollRemove( SbxArray* pPar );
public:
    SBX_DECL_PERSIST_NODATA(SBXCR_SBX,SBXID_FIXCOLLECTION,1);
    TYPEINFO();
    SbxStdCollection
        ( const String& rClassname, const String& rElemClass, BOOL=TRUE );
    SbxStdCollection( const SbxStdCollection& );
    SbxStdCollection& operator=( const SbxStdCollection& );
    virtual void Insert( SbxVariable* );
    const String& GetElementClass() const { return aElemClass; }
};

#endif


#ifndef __SBX_SBXREFS_HXX
#define __SBX_SBXREFS_HXX

SV_IMPL_REF(SbxBase)

SV_IMPL_REF(SbxVariable)

#ifndef SBX_ARRAY_DECL_DEFINED
#define SBX_ARRAY_DECL_DEFINED
SV_DECL_REF(SbxArray)
#endif
#ifndef SBX_ARRAY_IMPL_DEFINED
#define SBX_ARRAY_IMPL_DEFINED
SV_IMPL_REF(SbxArray)
#endif

#ifndef SBX_INFO_DECL_DEFINED
#define SBX_INFO_DECL_DEFINED
SV_DECL_REF(SbxInfo)
#endif
#ifndef SBX_INFO_IMPL_DEFINED
#define SBX_INFO_IMPL_DEFINED
SV_IMPL_REF(SbxInfo)
#endif

#ifndef SBX_DIMARRAY_DECL_DEFINED
#define SBX_DIMARRAY_DECL_DEFINED
SV_DECL_REF(SbxDimArray)
#endif
SV_IMPL_REF(SbxDimArray)

#endif

}

#endif
