/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: iface.hxx,v $
 *
 *  $Revision: 1.3 $
 *
 *  last change: $Author: rt $ $Date: 2008-03-12 11:42:27 $
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

#ifndef _IFACE_HXX
#define _IFACE_HXX

#ifndef _SFXHINT_HXX //autogen
#include <bf_svtools/hint.hxx>
#endif
#ifndef _GEN_HXX //autogen
#include <tools/gen.hxx>
#endif
#ifndef _SVBORDER_HXX
#include <tools/svborder.hxx>
#endif
#ifndef _SHL_HXX //autogen
#include <tools/shl.hxx>
#endif
#include <bf_so3/factory.hxx>
#include <bf_so3/so2dll.hxx>

#include <sot/object.hxx>


#ifndef INCLUDED_SO3DLLAPI_H
#include "bf_so3/so3dllapi.h"
#endif

struct ::IUnknown;

namespace binfilter {

/*************************************************************************
*************************************************************************/
class  SvSoIPCClient;
class  SvSoIPCService;

// Zugriff auf Dlldaten
#define SOAPP  SoDll::GetOrCreate()

/**************************************************************************
**************************************************************************/
#define SO2_DECL_INTERFACE()                                              \
    virtual ::IUnknown *        GetInterface( const SvGlobalName & );       \
    ::IUnknown *                GetMemberInterface(  const SvGlobalName & );\


#define SO2_DECL_STANDARD_CLASS_DLL(ClassName,FacName)                    \
    SO2_DECL_BASIC_CLASS_DLL(ClassName,FacName)                           \
    SO2_DECL_INTERFACE()                                                  \
    SO2_DECL_INVARIANT()

#define SO2_DECL_STANDARD_CLASS(ClassName)                                \
    SO2_DECL_BASIC_CLASS(ClassName)                                       \
    SO2_DECL_INTERFACE()                                                  \
    SO2_DECL_INVARIANT()

/**************************************************************************
**************************************************************************/
#define SO2_IMPL_INTERFACE(ClassName)                                     \
::IUnknown * __EXPORT ClassName::GetInterface( const SvGlobalName & rName ) \
{                                                                         \
    ::IUnknown * p = GetMemberInterface( rName );                           \
    return p;                                                             \
}                                                                         \


#define SO2_IMPL_CLASS_DLL(ClassName,FactoryName,GlobalName)              \
SO2_IMPL_BASIC_CLASS_DLL(ClassName,FactoryName,GlobalName)                \
SO2_IMPL_INTERFACE(ClassName)                                             \
SO2_IMPL_INVARIANT(ClassName)

#define SO2_IMPL_CLASS(ClassName,FactoryName,GlobalName)                  \
SotFactory * ClassName::pFactory = NULL;                                   \
    SO2_IMPL_CLASS_DLL(ClassName,FactoryName,GlobalName)

/**************************************************************************
**************************************************************************/
#define SO2_IMPL_INTERFACE1(ClassName,Super1)                             \
::IUnknown * __EXPORT ClassName::GetInterface( const SvGlobalName & rName ) \
{                                                                         \
    ::IUnknown * p = GetMemberInterface( rName );                           \
    if( !p )                                                              \
        p = Super1::GetInterface( rName );                                \
    return p;                                                             \
}                                                                         \

#define SO2_IMPL_CLASS1_DLL(ClassName,FactoryName,Super1,GlobalName)      \
SO2_IMPL_BASIC_CLASS1_DLL(ClassName,FactoryName,Super1,GlobalName)        \
SO2_IMPL_INTERFACE1(ClassName,Super1)                                     \
SO2_IMPL_INVARIANT1(ClassName,Super1)

#define SO2_IMPL_CLASS1(ClassName,FactoryName,Super1,GlobalName)          \
SotFactory * ClassName::pFactory = NULL;                                   \
    SO2_IMPL_CLASS1_DLL(ClassName,FactoryName,Super1,GlobalName)

#define SO2_IMPL_STANDARD_CLASS1_DLL(ClassName,FactoryName,Super1,n1,n2,n3,b8,b9,b10,b11,b12,b13,b14,b15)  \
SO2_IMPL_CLASS1_DLL(ClassName,FactoryName,Super1,                     \
                        SvGlobalName(n1,n2,n3,b8,b9,b10,b11,b12,b13,b14,b15))

#define SO2_IMPL_STANDARD_CLASS1(ClassName,FactoryName,Super1,n1,n2,n3,b8,b9,b10,b11,b12,b13,b14,b15)  \
    SO2_IMPL_CLASS1(ClassName,FactoryName,Super1,            \
                            SvGlobalName(n1,n2,n3,b8,b9,b10,b11,b12,b13,b14,b15))

/**************************************************************************
**************************************************************************/
#define SO2_IMPL_INTERFACE2(ClassName,Super1,Super2)                          \
::IUnknown * __EXPORT ClassName::GetInterface( const SvGlobalName & rName ) \
{                                                                         \
    ::IUnknown * p = GetMemberInterface( rName );                           \
    if( !p )                                                              \
        p = Super1::GetInterface( rName );                                \
    if( !p )                                                              \
        p = Super2::GetInterface( rName );                                \
    return p;                                                             \
}                                                                         \

#define SO2_IMPL_CLASS2_DLL(ClassName,FactoryName,Super1,Super2,GlobalName)  \
SO2_IMPL_BASIC_CLASS2_DLL(ClassName,FactoryName,Super1,Super2,GlobalName)  \
SO2_IMPL_INTERFACE2(ClassName,Super1,Super2)                              \
SO2_IMPL_INVARIANT2(ClassName,Super1,Super2)

#define SO2_IMPL_CLASS2(ClassName,FactoryName,Super1,Super2,GlobalName)   \
SotFactory * ClassName::pFactory = NULL;                                   \
    SO2_IMPL_CLASS2_DLL(ClassName,FactoryName,Super1,Super2,GlobalName)

#define SO2_IMPL_STANDARD_CLASS2(ClassName,FactoryName,Super1,Super2,n1,n2,n3,b8,b9,b10,b11,b12,b13,b14,b15)  \
    SO2_IMPL_CLASS2(ClassName,FactoryName,Super1,Super2,              \
                        SvGlobalName(n1,n2,n3,b8,b9,b10,b11,b12,b13,b14,b15))

#define SO2_IMPL_STANDARD_CLASS2_DLL(ClassName,FactoryName,Super1,Super2,n1,n2,n3,b8,b9,b10,b11,b12,b13,b14,b15)  \
    SO2_IMPL_CLASS2_DLL(ClassName,FactoryName,Super1,Super2,                  \
                        SvGlobalName(n1,n2,n3,b8,b9,b10,b11,b12,b13,b14,b15))

/**************************************************************************
**************************************************************************/
#define SO2_IMPL_INTERFACE3(ClassName,Super1,Super2,Super3)               \
::IUnknown * __EXPORT ClassName::GetInterface( const SvGlobalName & rName ) \
{                                                                         \
    ::IUnknown * p = GetMemberInterface( rName );                           \
    if( !p )                                                              \
        p = Super1::GetInterface( rName );                                \
    if( !p )                                                              \
        p = Super2::GetInterface( rName );                                \
    if( !p )                                                              \
        p = Super3::GetInterface( rName );                                \
    return p;                                                             \
}                                                                         \

#define SO2_IMPL_CLASS3_DLL(ClassName,FactoryName,Super1,Super2,Super3,GlobalName)    \
SO2_IMPL_BASIC_CLASS3_DLL(ClassName,FactoryName,Super1,Super2,Super3,GlobalName)  \
SO2_IMPL_INTERFACE3(ClassName,Super1,Super2,Super3)                       \
SO2_IMPL_INVARIANT3(ClassName,Super1,Super2,Super3)

#define SO2_IMPL_CLASS3(ClassName,FactoryName,Super1,Super2,Super3,GlobalName)  \
SotFactory * ClassName::pFactory = NULL;                                   \
    SO2_IMPL_CLASS3_DLL(ClassName,FactoryName,Super1,Super2,Super3,GlobalName)

#define SO2_IMPL_STANDARD_CLASS3(ClassName,FactoryName,Super1,Super2,Super3,n1,n2,n3,b8,b9,b10,b11,b12,b13,b14,b15)  \
    SO2_IMPL_CLASS3(ClassName,FactoryName,Super1,Super2,Super3,           \
                    SvGlobalName(n1,n2,n3,b8,b9,b10,b11,b12,b13,b14,b15))

#define SO2_IMPL_STANDARD_CLASS3_DLL(ClassName,FactoryName,Super1,Super2,Super3,n1,n2,n3,b8,b9,b10,b11,b12,b13,b14,b15)  \
    SO2_IMPL_CLASS3_DLL(ClassName,FactoryName,Super1,Super2,Super3,       \
                        SvGlobalName(n1,n2,n3,b8,b9,b10,b11,b12,b13,b14,b15)

/**************************************************************************
**************************************************************************/
#define SO2_IMPL_INTERFACE4(ClassName,Super1,Super2,Super3,Super4)        \
::IUnknown * __EXPORT ClassName::GetInterface( const SvGlobalName & rName ) \
{                                                                         \
    ::IUnknown * p = GetMemberInterface( rName );                           \
    if( !p )                                                              \
        p = Super1::GetInterface( rName );                                \
    if( !p )                                                              \
        p = Super2::GetInterface( rName );                                \
    if( !p )                                                              \
        p = Super3::GetInterface( rName );                                \
    if( !p )                                                              \
        p = Super4::GetInterface( rName );                                \
    return p;                                                             \
}                                                                         \

#define SO2_IMPL_CLASS4_DLL(ClassName,FactoryName,Super1,Super2,Super3,Super4,GlobalName )  \
SO2_IMPL_BASIC_CLASS4_DLL(ClassName,FactoryName,Super1,Super2,Super3,Super4,GlobalName )  \
SO2_IMPL_INTERFACE4(ClassName,Super1,Super2,Super3,Super4)                \
SO2_IMPL_INVARIANT4(ClassName,Super1,Super2,Super3,Super4)

#define SO2_IMPL_CLASS4(ClassName,FactoryName,Super1,Super2,Super3,Super4,GlobalName)  \
SotFactory * ClassName::pFactory = NULL;                                   \
    SO2_IMPL_CLASS4_DLL(ClassName,FactoryName,Super1,Super2,Super3,Super4,GlobalName)

#define SO2_IMPL_STANDARD_CLASS4(ClassName,FactoryName,Super1,Super2,Super3,Super4,n1,n2,n3,b8,b9,b10,b11,b12,b13,b14,b15)  \
    SO2_IMPL_CLASS4(ClassName,FactoryName,Super1,Super2,Super3,Super4,\
                    SvGlobalName(n1,n2,n3,b8,b9,b10,b11,b12,b13,b14,b15))

#define SO2_IMPL_STANDARD_CLASS4_DLL(ClassName,FactoryName,Super1,Super2,Super3,Super4,n1,n2,n3,b8,b9,b10,b11,b12,b13,b14,b15)  \
    SO2_IMPL_CLASS4_DLL(ClassName,FactoryName,Super1,Super2,Super3,Super4,\
                        SvGlobalName(n1,n2,n3,b8,b9,b10,b11,b12,b13,b14,b15))


//==================class SvObject========================================
#ifdef MSC
#pragma warning(disable: 4250)
#endif

class SO3_DLLPUBLIC SvObject : virtual public SotObject
{
friend struct IUnknown;
friend class SvSoIPCService;
friend class SvSoIPCClient;
friend class SvFactory;

private:
    SO3_DLLPRIVATE union
    {
        ::IUnknown *      pObj;       // IUnknown Interface
        SvSoIPCClient * pClient;    // Client, falls !Owner()
        SvSoIPCService * pService;  // Service Punkt, falls Owner()
    };
    USHORT      nExtCount;          // externer Referenzzaehler

#if defined (GCC) && (defined(C281) || defined(C290) || defined(C291))
public:
#else
protected:
#endif
    virtual             ~SvObject();
    SO3_DLLPRIVATE void                DeInit( ::IUnknown * );
    SO3_DLLPRIVATE void                DeInit( SvSoIPCService * );
    SO3_DLLPRIVATE void                DeInit( SvSoIPCClient * );
    virtual void        MakeUnknown();
public:
                        SvObject();
                        SO2_DECL_STANDARD_CLASS_DLL(SvObject,SOAPP)
    void                Init( SvSoIPCClient * pObj );
    void                OwnerInit( SvSoIPCService * pObj );
    SvSoIPCService *    GetIPCService() const;
    SvSoIPCClient  *    GetIPCClient() const;

    ::IUnknown *          DownAggInterface( const SvGlobalName & rName );
    ::IUnknown *          AggInterface( const SvGlobalName & rName );

    USHORT              GetExtRefCount() const { return nExtCount; }
    UINT32              AddExtRef();
    UINT32				ReleaseExt();
    UINT32				ReleaseRef(); // Nur fur DBG_UTIL
private:
    // Kopieren und Zuweisen dieses Objekttyps ist nicht erlaubt
    SO3_DLLPRIVATE SvObject & operator = ( const SvObject & );
    SO3_DLLPRIVATE SvObject( const SvObject & );
};

//==================class SvObjectRef======================================
#ifndef SO2_DECL_SVOBJECT_DEFINED
#define SO2_DECL_SVOBJECT_DEFINED
class SO3_DLLPUBLIC SvObjectRef
{
    PRV_SV_DECL_REF(SvObject)
};
#endif
SO2_IMPL_REF(SvObject)

//==================class SvObject*List====================================
#if !defined( SO_EXTERN ) || defined( SO2_SVOBJECTLIST )
SV_DECL_REF_LIST(SvObject,SvObject*)
SV_IMPL_REF_LIST(SvObject,SvObject*)
#endif

//==================class SvFactory_Impl===================================
#if !defined( SO_EXTERN )
struct IClassFactory;
class SO3_DLLPRIVATE SvFactory_Impl : public SvObject
/*  [Beschreibung]

*/
{
friend class ImpFactory;
friend class SvFactory;
private:
    IClassFactory * pObjI;
    SvFactory *     pFact;
public:
    SO3_DLLPRIVATE			SvFactory_Impl();
    SO3_DLLPRIVATE			SvFactory_Impl( SvFactory * );
    SO3_DLLPRIVATE			~SvFactory_Impl();

    SO2_DECL_STANDARD_CLASS_DLL( SvFactory_Impl, SOAPP )

    SO3_DLLPRIVATE IClassFactory * GetClassFactory() const;
};
#endif

//=========================================================================
#define OLE2_MAPMODE    MAP_100TH_MM

#if defined (_INC_WINDOWS) || defined (_WINDOWS_)
RECT GetSysRect( const Rectangle & rRect );
Rectangle GetSvRect( const RECT & rRect );
#endif

#ifdef DBG_UTIL
ByteString  SvPrint( const SvBorder & );
ByteString  SvPrint( const Rectangle & );
ByteString  SvPrint( const Point & );
ByteString  SvPrint( const Size & );
#endif

//=========================================================================

DECL_PTRHINT(/*empty*/, SvObjectDyingHint, SvObject);

}

#endif // _IFACE_HXX
