/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: cntnrsrt.hxx,v $
 *
 *  $Revision: 1.2 $
 *
 *  last change: $Author: rt $ $Date: 2008-03-12 11:53:13 $
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
#ifndef _CNTRSRT_HXX
#define _CNTRSRT_HXX

#ifndef _CONTNR_HXX //autogen
#include <tools/contnr.hxx>
#endif

namespace binfilter {

#define DECLARE_CONTAINER_SORT_COMMON( ClassName, Type )						\
    ClassName( const ClassName& );											\
    ClassName& operator =( const ClassName& );								\
public:                                       								\
    using Container::Count;                    								\
                                                                            \
    ClassName( USHORT  InitSize, USHORT  ReSize ) :							\
        Container( CONTAINER_MAXBLOCKSIZE, InitSize, ReSize )	{}			\
                                                                            \
    BOOL Insert( Type* pObj );												\
                                                                               \
    Type *Remove( ULONG nPos ) 												\
        { return (Type *)Container::Remove( nPos ); }						\
                                                                            \
    Type *Remove( Type* pObj );												\
                                                                               \
    void DeleteAndDestroy( ULONG nPos )										\
    {                                  										\
        Type *pObj = Remove( nPos );   										\
        if( pObj )                     										\
            delete pObj;               										\
    }                                  										\
                                                                               \
    void DeleteAndDestroy()													\
        { while( Count() ) DeleteAndDestroy( 0 ); }							\
                                                                            \
    Type* GetObject( ULONG nPos ) const										\
        { return (Type *)Container::GetObject( nPos ); }					\
                                                                            \
    Type* operator[]( ULONG nPos ) const 									\
        { return GetObject(nPos); }											\
                                                                            \
    BOOL Seek_Entry( const Type *pObj, ULONG* pPos ) const;					\
                                                                            \
    ULONG GetPos( const Type* pObj ) const;									\


#define DECLARE_CONTAINER_SORT( ClassName, Type )							\
class ClassName : private Container											\
{																			\
    DECLARE_CONTAINER_SORT_COMMON( ClassName, Type )						\
    ~ClassName() {} 														\
};																			\


#define DECLARE_CONTAINER_SORT_DEL( ClassName, Type )							\
class ClassName : private Container											\
{																			\
    DECLARE_CONTAINER_SORT_COMMON( ClassName, Type )							\
    ~ClassName() { DeleteAndDestroy(); }									\
};																			\


#define IMPL_CONTAINER_SORT( ClassName, Type, SortFunc )					\
BOOL ClassName::Insert( Type *pObj )                                        \
{                                                                           \
    ULONG nPos;                                                             \
    BOOL bExist = Seek_Entry( pObj, &nPos );                                \
    if( !bExist )                                                           \
        Container::Insert( pObj, nPos );                                    \
    return !bExist;                                                         \
}                                                                           \
                                                                            \
Type *ClassName::Remove( Type* pObj )                                       \
{                                                                           \
    ULONG nPos;                                                             \
    if( Seek_Entry( pObj, &nPos ) )                                         \
        return Remove( nPos );                                              \
    else                                                                    \
        return 0;                                                           \
}                                                                           \
                                                                            \
ULONG ClassName::GetPos( const Type* pObj ) const                           \
{                                                                           \
    ULONG nPos;                                                             \
    if( Seek_Entry( pObj, &nPos ) )                                         \
        return nPos;                                                        \
    else                                                                    \
        return CONTAINER_ENTRY_NOTFOUND;                                    \
}                                                                           \
                                                                            \
BOOL ClassName::Seek_Entry( const Type* pObj, ULONG* pPos ) const           \
{                                                                           \
    register ULONG nO  = Count(),                                           \
            nM,                                                             \
            nU = 0;                                                         \
    if( nO > 0 )                                                            \
    {                                                                       \
        nO--;                                                               \
        while( nU <= nO )                                                   \
        {                                                                   \
            nM = nU + ( nO - nU ) / 2;                                      \
            int nCmp = SortFunc( *GetObject(nM), *pObj );				    \
                                                                            \
            if( 0 == nCmp )                              					\
            {                                                               \
                if( pPos ) *pPos = nM;                                      \
                return TRUE;                                                \
            }                                                               \
            else if( nCmp < 0 )                       						\
                nU = nM + 1;                                                \
            else if( nM == 0 )                                              \
            {                                                               \
                if( pPos ) *pPos = nU;                                      \
                return FALSE;                                               \
            }                                                               \
            else                                                            \
                nO = nM - 1;                                                \
        }                                                                   \
    }                                                                       \
    if( pPos ) *pPos = nU;                                                  \
    return FALSE;                                                           \
}                                                                           \

}

#endif
