/*************************************************************************
 *
 *  $RCSfile: minarray.hxx,v $
 *
 *  $Revision: 1.2 $
 *
 *  last change: $Author: mwu $ $Date: 2003-11-06 08:26:18 $
 *
 *  The Contents of this file are made available subject to the terms of
 *  either of the following licenses
 *
 *         - GNU Lesser General Public License Version 2.1
 *         - Sun Industry Standards Source License Version 1.1
 *
 *  Sun Microsystems Inc., October, 2000
 *
 *  GNU Lesser General Public License Version 2.1
 *  =============================================
 *  Copyright 2000 by Sun Microsystems, Inc.
 *  901 San Antonio Road, Palo Alto, CA 94303, USA
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public
 *  License version 2.1, as published by the Free Software Foundation.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public
 *  License along with this library; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 *  MA  02111-1307  USA
 *
 *
 *  Sun Industry Standards Source License Version 1.1
 *  =================================================
 *  The contents of this file are subject to the Sun Industry Standards
 *  Source License Version 1.1 (the "License"); You may not use this file
 *  except in compliance with the License. You may obtain a copy of the
 *  License at http://www.openoffice.org/license.html.
 *
 *  Software provided under this License is provided on an "AS IS" basis,
 *  WITHOUT WARRANTY OF ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING,
 *  WITHOUT LIMITATION, WARRANTIES THAT THE SOFTWARE IS FREE OF DEFECTS,
 *  MERCHANTABLE, FIT FOR A PARTICULAR PURPOSE, OR NON-INFRINGING.
 *  See the License for the specific provisions governing your rights and
 *  obligations concerning the Software.
 *
 *  The Initial Developer of the Original Code is: Sun Microsystems, Inc.
 *
 *  Copyright: 2000 by Sun Microsystems, Inc.
 *
 *  All Rights Reserved.
 *
 *  Contributor(s): _______________________________________
 *
 *
 ************************************************************************/
#ifndef _SFXVARARR_HXX
#define _SFXVARARR_HXX

#include <limits.h>
#include <string.h>

#ifndef _SOLAR_H
#include <tools/solar.h>
#endif

#ifndef _DEBUG_HXX //autogen
#include <tools/debug.hxx>
#endif
namespace binfilter {
//#include "typecast.hxx"

#if defined (ALPHA) && defined (UNX)
#define DEL_ARRAY( X )
#else
#define DEL_ARRAY( X ) X
#endif

#define DECL_OBJARRAY( ARR, T, nI, nG ) \
class ARR\
{\
private:\
    T*	 pData;\
    USHORT  nUsed;\
    BYTE	nGrow;\
    BYTE    nUnused;\
public:\
    ARR( BYTE nInitSize = nI, BYTE nGrowSize = nG );\
    ARR( const ARR& rOrig );\
    ~ARR();\
\
    ARR& operator= ( const ARR& rOrig );\
\
    const T& GetObject( USHORT nPos ) const; \
    T& GetObject( USHORT nPos ); \
\
    void Insert( USHORT nPos, ARR& rIns, USHORT nStart = 0, USHORT nEnd = USHRT_MAX );\
    void Insert( USHORT nPos, const T& rElem );\
    void Insert( USHORT nPos, const T& rElems, USHORT nLen );\
    void Append( const T& rElem );\
\
    BOOL Remove( const T& rElem );\
    USHORT Remove( USHORT nPos, USHORT nLen );\
\
    USHORT Count() const { return nUsed; }\
    T* operator*();\
    const T& operator[]( USHORT nPos ) const;\
    T& operator[]( USHORT nPos );\
\
    BOOL Contains( const T& rItem ) const;\
    void Clear() { Remove( 0, Count() ); }\
};\
\
inline void ARR::Insert( USHORT nPos, ARR& rIns, USHORT nStart, USHORT nEnd )\
{\
    Insert( nPos, *(rIns.pData+(sizeof(T)*nStart)), nStart-nEnd+1 );\
}\
\
inline void ARR::Insert( USHORT nPos, const T& rElem )\
{\
    Insert( nPos, rElem, 1 );\
}\
\
inline T* ARR::operator*()\
{\
    return ( nUsed==0 ? 0 : pData );\
} \
inline const T& ARR::operator[]( USHORT nPos ) const\
{\
    DBG_ASSERT( nPos < nUsed, "" ); \
    return *(pData+nPos);\
} \
inline T& ARR::operator [] (USHORT nPos) \
{\
    DBG_ASSERT( nPos < nUsed, "" ); \
    return *(pData+nPos); \
} \
inline const T& ARR::GetObject( USHORT nPos ) const { return operator[](nPos); } \
inline T& ARR::GetObject( USHORT nPos ) { return operator[](nPos); } \

#ifndef _lint
// String too long

#define IMPL_OBJARRAY( ARR, T ) \
ARR::ARR( BYTE nInitSize, BYTE nGrowSize ): \
    nUsed(0), \
    nUnused(nInitSize), \
    nGrow( nGrowSize ? nGrowSize : 1 ) \
{ \
    if ( nInitSize != 0 ) \
    { \
        size_t nBytes = nInitSize * sizeof(T); \
        pData = (T*) new char[ nBytes ]; \
        memset( pData, 0, nBytes ); \
    } \
    else \
        pData = 0; \
} \
\
ARR::ARR( const ARR& rOrig ) \
{ \
    nUsed = rOrig.nUsed; \
    nGrow = rOrig.nGrow; \
    nUnused = rOrig.nUnused; \
\
    if ( rOrig.pData != 0 ) \
    { \
        size_t nBytes = (nUsed + nUnused) * sizeof(T); \
        pData = (T*) new char [ nBytes ]; \
        memset( pData, 0, nBytes ); \
        for ( USHORT n = 0; n < nUsed; ++n ) \
            *(pData+n) = *(rOrig.pData+n); \
    } \
    else \
        pData = 0; \
} \
\
ARR::~ARR() \
{ \
    for ( USHORT n = 0; n < nUsed; ++n ) \
        ( pData+n )->T::~T(); \
    delete[] (char*) pData;\
} \
\
ARR& ARR::operator= ( const ARR& rOrig )\
{ \
    for ( USHORT n = 0; n < nUsed; ++n ) \
        ( pData+n )->T::~T(); \
    delete[] (char*) pData;\
\
    nUsed = rOrig.nUsed; \
    nGrow = rOrig.nGrow; \
    nUnused = rOrig.nUnused; \
\
    if ( rOrig.pData != 0 ) \
    { \
        size_t nBytes = (nUsed + nUnused) * sizeof(T); \
        pData = (T*) new char[ nBytes ]; \
        memset( pData, 0, nBytes ); \
        for ( USHORT n = 0; n < nUsed; ++n ) \
            *(pData+n) = *(rOrig.pData+n); \
    } \
    else \
        pData = 0; \
    return *this; \
} \
\
void ARR::Append( const T& aElem ) \
{ \
     \
    if ( nUnused == 0 ) \
    { \
        USHORT nNewSize = (nUsed == 1) ? (nGrow==1 ? 2 : nGrow) : nUsed+nGrow; \
        size_t nBytes = nNewSize * sizeof(T); \
        T* pNewData = (T*) new char[ nBytes ]; \
        memset( pNewData, 0, nBytes ); \
        if ( pData ) \
        { \
            memcpy( pNewData, pData, nUsed * sizeof(T) ); \
            delete[] (char*) pData;\
        } \
        nUnused = (BYTE)(nNewSize-nUsed); \
        pData = pNewData; \
    } \
\
     \
    pData[nUsed] = aElem; \
    ++nUsed; \
    --nUnused; \
} \
\
USHORT ARR::Remove( USHORT nPos, USHORT nLen ) \
{ \
    DBG_ASSERT( (nPos+nLen) < (nUsed+1), "" ); \
    DBG_ASSERT( nLen > 0, "" ); \
\
    nLen = Min( (USHORT)(nUsed-nPos), (USHORT)nLen ); \
\
    if ( nLen == 0 ) \
        return 0; \
\
    for ( USHORT n = nPos; n < (nPos+nLen); ++n ) \
        ( pData+n )->T::~T(); \
\
    if ( (nUsed-nLen) == 0 ) \
    { \
        delete[] (char*) pData;\
        pData = 0; \
        nUsed = 0; \
        nUnused = 0; \
        return nLen; \
    } \
\
    if ( (nUnused+nLen) >= nGrow ) \
    { \
        USHORT nNewUsed = nUsed-nLen; \
        USHORT nNewSize = (nNewUsed+nGrow-1)/nGrow; nNewSize *= nGrow; \
        DBG_ASSERT( nNewUsed <= nNewSize && nNewUsed+nGrow > nNewSize, \
                    "shrink size computation failed" ); \
        size_t nBytes = nNewSize * sizeof(T); \
        T* pNewData = (T*) new char[ nBytes ]; \
        memset( pNewData, 0, nBytes ); \
        if ( nPos > 0 ) \
            memcpy( pNewData, pData, nPos * sizeof(T) ); \
        if ( nNewUsed != nPos ) \
            memcpy(pNewData+nPos, pData+nPos+nLen, (nNewUsed-nPos) * sizeof(T) ); \
        delete[] (char*) pData;\
        pData = pNewData; \
        nUsed = nNewUsed; \
        nUnused = (BYTE)(nNewSize - nNewUsed); \
        return nLen; \
    } \
\
     \
    if ( nUsed-nPos-nLen > 0 ) \
    { \
        memmove(pData+nPos, pData+nPos+nLen, (nUsed-nPos-nLen) * sizeof(T));\
    } \
    nUsed -= (BYTE)nLen; \
    nUnused += (BYTE)nLen; \
    return nLen; \
} \
\
BOOL ARR::Remove( const T& aElem ) \
{ \
    if ( nUsed == 0 ) \
        return FALSE; \
\
    const T *pIter = pData + nUsed - 1; \
    for ( USHORT n = 0; n < nUsed; ++n, --pIter ) \
        if ( *pIter == aElem ) \
        { \
            Remove(nUsed-n-1, 1); \
            return TRUE; \
        } \
    return FALSE; \
} \
\
BOOL ARR::Contains( const T& rItem ) const \
{ \
    if ( !nUsed ) \
        return FALSE; \
    for ( USHORT n = 0; n < nUsed; ++n ) \
    { \
        const T& r2ndItem = GetObject(n); \
        if ( r2ndItem == rItem ) \
            return TRUE; \
    } \
    return FALSE; \
} \
\
void ARR::Insert( USHORT nPos, const T& rElems, USHORT nLen ) \
{ \
    DBG_ASSERT( nPos <= nUsed, "" ); \
     \
    if ( nUnused == 0 ) \
    { \
        \
        /* auf die naechste Grow-Grenze aufgerundet vergroeszern */ \
        USHORT nNewSize; \
        for ( nNewSize = nUsed+nGrow; nNewSize < (nUsed + nLen); ++nNewSize ) \
            /* empty loop */; \
        size_t nBytes = nNewSize * sizeof(T); \
        T* pNewData = (T*) new char[ nBytes ]; \
        memset( pNewData, 0, nBytes ); \
        \
        if ( pData ) \
        { \
            DBG_ASSERT( nUsed < nNewSize, "" ); \
            memcpy( pNewData, pData, nUsed * sizeof(T) ); \
            delete (char*) pData;\
        } \
        nUnused = (BYTE)(nNewSize-nUsed); \
        pData = pNewData; \
    } \
\
     \
    if ( nPos < nUsed ) \
    { \
        memmove(pData+nPos+nLen-1, pData+nPos-1, sizeof(T) * (nUsed-nPos));	\
    } \
\
    memmove(pData+nPos, &rElems, sizeof(T) * nLen);	\
    nUsed += nLen; \
    nUnused -= nLen; \
}

// _lint
#endif

class SfxPtrArr
{
private:
    void** pData;
    USHORT nUsed;
    BYTE nGrow;
    BYTE nUnused;
public:
    SfxPtrArr( BYTE nInitSize = 0, BYTE nGrowSize = 8 );
    SfxPtrArr( const SfxPtrArr& rOrig );
    ~SfxPtrArr();
//STRIP001 	SfxPtrArr& operator= ( const SfxPtrArr& rOrig );
    void* GetObject( USHORT nPos ) const { return operator[](nPos); }
    void*& GetObject( USHORT nPos ) { return operator[](nPos); }
    void Insert( USHORT nPos, void* rElem );
    void Append( void* rElem );
    BOOL Replace( void* pOldElem, void* pNewElem );
    BOOL Remove( void* rElem );
    USHORT Remove( USHORT nPos, USHORT nLen );
    USHORT Count() const { return nUsed; }
    inline void** operator*();
    inline void* operator[]( USHORT nPos ) const;
    inline void*& operator[]( USHORT nPos );
    BOOL Contains( const void* rItem ) const;
    void Clear() { Remove( 0, Count() ); }
};

inline void** SfxPtrArr::operator*()
{
    return ( nUsed==0 ? 0 : pData );
}

inline void* SfxPtrArr::operator[]( USHORT nPos ) const
{
    DBG_ASSERT( nPos < nUsed, "" );
    return *(pData+nPos);
}

inline void*& SfxPtrArr::operator [] (USHORT nPos)
{
    DBG_ASSERT( nPos < nUsed, "" );
    return *(pData+nPos);
}

#define DECL_PTRARRAY(ARR, T, nI, nG)\
class ARR: public SfxPtrArr\
{\
public:\
   ARR( BYTE nIni=nI, BYTE nGrow=nG ):\
       SfxPtrArr(nIni,nGrow) \
   {}\
   ARR( const ARR& rOrig ):\
       SfxPtrArr(rOrig) \
   {}\
   T GetObject( USHORT nPos ) const { return operator[](nPos); } \
   T& GetObject( USHORT nPos ) { return operator[](nPos); } \
   void Insert( USHORT nPos, T aElement ) {\
       SfxPtrArr::Insert(nPos,(void *)aElement);\
   }\
   void Append( T aElement ) {\
       SfxPtrArr::Append((void *)aElement);\
   }\
   BOOL Replace( T aOldElem, T aNewElem ) {\
       return SfxPtrArr::Replace((void *)aOldElem, (void*) aNewElem);\
   }\
   void Remove( T aElement ) {\
       SfxPtrArr::Remove((void*)aElement);\
   }\
   void Remove( USHORT nPos, USHORT nLen = 1 ) {\
       SfxPtrArr::Remove( nPos, nLen ); \
   }\
   T* operator *() {\
       return (T*) SfxPtrArr::operator*();\
   }\
   T operator[]( USHORT nPos ) const { \
       return (T) SfxPtrArr::operator[](nPos); } \
   T& operator[]( USHORT nPos ) { \
       return (T&) SfxPtrArr::operator[](nPos); } \
   void Clear() { Remove( 0, Count() ); }\
};

//STRIP001 class ByteArr
//STRIP001 {
//STRIP001 private:
//STRIP001 	char* pData;
//STRIP001 	USHORT nUsed;
//STRIP001 	BYTE nGrow;
//STRIP001 	BYTE nUnused;
//STRIP001 public:
//STRIP001 	ByteArr( BYTE nInitSize = 0, BYTE nGrowSize = 8 );
//STRIP001 	ByteArr( const ByteArr& rOrig );
//STRIP001 	~ByteArr();
//STRIP001 	ByteArr& operator= ( const ByteArr& rOrig );
//STRIP001 	char GetObject( USHORT nPos ) const { return operator[](nPos); }
//STRIP001 	char& GetObject( USHORT nPos ) { return operator[](nPos); }
//STRIP001 	void Insert( USHORT nPos, char rElem );
//STRIP001 	void Append( char rElem );
//STRIP001 	BOOL Remove( char rElem );
//STRIP001 	USHORT Remove( USHORT nPos, USHORT nLen );
//STRIP001 	USHORT Count() const { return nUsed; }
//STRIP001 	char* operator*();
//STRIP001 	char operator[]( USHORT nPos ) const;
//STRIP001 	char& operator[]( USHORT nPos );
//STRIP001 	BOOL Contains( const char rItem ) const;
//STRIP001 	void Clear() { Remove( 0, Count() ); }
//STRIP001 };

//STRIP001 inline char* ByteArr::operator*()
//STRIP001 {
//STRIP001 	return ( nUsed==0 ? 0 : pData );
//STRIP001 }

#define DECL_1BYTEARRAY(ARR, T, nI, nG)\
class ARR: public ByteArr\
{\
public:\
        ARR( BYTE nIni=nI, BYTE nGrow=nG ):\
            ByteArr(nIni,nGrow) \
        {}\
        ARR( const ARR& rOrig ):\
            ByteArr(rOrig) \
        {}\
        T GetObject( USHORT nPos ) const { return operator[](nPos); } \
        T& GetObject( USHORT nPos ) { return operator[](nPos); } \
        void Insert( USHORT nPos, T aElement ) {\
            ByteArr::Insert(nPos,(char)aElement);\
        }\
        void Append( T aElement ) {\
            ByteArr::Append((char)aElement);\
        }\
        void Remove( T aElement ) {\
            ByteArr::Remove((char)aElement);\
        }\
        void Remove( USHORT nPos, USHORT nLen = 1 ) {\
            ByteArr::Remove( nPos, nLen ); \
        }\
        T* operator *() {\
            return (T*) ByteArr::operator*();\
        }\
        T operator[]( USHORT nPos ) const { \
            return (T) ByteArr::operator[](nPos); } \
        T& operator[]( USHORT nPos ) { \
            return (T&) ByteArr::operator[](nPos); } \
        void Clear() { Remove( 0, Count() ); }\
};

class WordArr
{
private:
    short* pData;
    USHORT nUsed;
    BYTE nGrow;
    BYTE nUnused;
public:
    WordArr( BYTE nInitSize = 0, BYTE nGrowSize = 8 );
//STRIP001 	WordArr( const WordArr& rOrig );
    ~WordArr();
//STRIP001 	WordArr& operator= ( const WordArr& rOrig );
    short GetObject( USHORT nPos ) const { return operator[](nPos); }
    short& GetObject( USHORT nPos ) { return operator[](nPos); }
    void Insert( USHORT nPos, short rElem );
    void Append( short rElem );
    BOOL Remove( short rElem );
    USHORT Remove( USHORT nPos, USHORT nLen );
    USHORT Count() const { return nUsed; }
    short* operator*();
    short operator[]( USHORT nPos ) const;
    short& operator[]( USHORT nPos );
    BOOL Contains( const short rItem ) const;
//STRIP001 	void Clear() { Remove( 0, Count() ); }
};

inline short* WordArr::operator*()
{
    return ( nUsed==0 ? 0 : pData );
}

#define DECL_2BYTEARRAY(ARR, T, nI, nG)\
class ARR: public WordArr\
{\
public:\
        ARR( BYTE nIni=nI, BYTE nGrow=nG ):\
            WordArr(nIni,nGrow) \
        {}\
        ARR( const ARR& rOrig ):\
            WordArr(rOrig) \
        {}\
        T GetObject( USHORT nPos ) const { return operator[](nPos); } \
        T& GetObject( USHORT nPos ) { return operator[](nPos); } \
        void Insert( USHORT nPos, T aElement ) {\
            WordArr::Insert(nPos,(short)aElement);\
        }\
        void Append( T aElement ) {\
            WordArr::Append((short)aElement);\
        }\
        void Remove( T aElement ) {\
            WordArr::Remove((short)aElement);\
        }\
        void Remove( USHORT nPos, USHORT nLen = 1 ) {\
            WordArr::Remove( nPos, nLen ); \
        }\
        T* operator *() {\
            return (T*) WordArr::operator*();\
        }\
        T operator[]( USHORT nPos ) const { \
            return (T) WordArr::operator[](nPos); } \
        T& operator[]( USHORT nPos ) { \
            return (T&) WordArr::operator[](nPos); } \
        void Clear() { Remove( 0, Count() ); }\
};

}//end of namespace binfilter
#endif
