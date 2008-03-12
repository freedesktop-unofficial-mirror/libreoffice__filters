/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: svt_inethist.cxx,v $
 *
 *  $Revision: 1.2 $
 *
 *  last change: $Author: rt $ $Date: 2008-03-12 09:02:50 $
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

#include <bf_svtools/inethist.hxx>

#ifndef INCLUDED_ALGORITHM
#include <algorithm>
#define INCLUDED_ALGORITHM
#endif

#ifndef INCLUDED_RTL_INSTANCE_HXX
#include "rtl/instance.hxx"
#endif

#ifndef _RTL_CRC_H_
#include "rtl/crc.h"
#endif

#ifndef _RTL_MEMORY_H_
#include "rtl/memory.h"
#endif

#ifndef _SOLAR_H
#include <tools/solar.h>
#endif

#ifndef _TOOLS_DEBUG_HXX
#include <tools/debug.hxx>
#endif

#ifndef _STRING_HXX
#include <tools/string.hxx>
#endif

#ifndef _URLOBJ_HXX
#include <tools/urlobj.hxx>
#endif

namespace binfilter
{

/*========================================================================
 *
 * INetURLHistory internals.
 *
 *======================================================================*/
#define INETHIST_DEF_FTP_PORT    21
#define INETHIST_DEF_HTTP_PORT   80
#define INETHIST_DEF_HTTPS_PORT 443

#define INETHIST_SIZE_LIMIT   1024
#define INETHIST_MAGIC_HEAD   0x484D4849UL

/*
 * INetURLHistoryHint implementation.
 */
IMPL_PTRHINT (INetURLHistoryHint, const INetURLObject);

/*========================================================================
 *
 * INetURLHistory_Impl interface.
 *
 *======================================================================*/
class INetURLHistory_Impl
{
    /** head_entry.
    */
    struct head_entry
    {
        /** Representation.
        */
        UINT32 m_nMagic;
        UINT16 m_nNext;
        UINT16 m_nMBZ;

        /** Initialization.
        */
        void initialize (void)
        {
            m_nMagic = INETHIST_MAGIC_HEAD;
            m_nNext  = 0;
            m_nMBZ   = 0;
        }
    };

    /** hash_entry.
    */
    struct hash_entry
    {
        /** Representation.
        */
        UINT32 m_nHash;
        UINT16 m_nLru;
        UINT16 m_nMBZ;

        /** Initialization.
        */
        void initialize (UINT16 nLru, UINT32 nHash = 0)
        {
            m_nHash = nHash;
            m_nLru  = nLru;
            m_nMBZ  = 0;
        }

        /** Comparison.
        */
        BOOL operator== (const hash_entry &rOther) const
        {
            return (m_nHash == rOther.m_nHash);
        }
        BOOL operator< (const hash_entry &rOther) const
        {
            return (m_nHash < rOther.m_nHash);
        }

        BOOL operator== (UINT32 nHash) const
        {
            return (m_nHash == nHash);
        }
        BOOL operator< (UINT32 nHash) const
        {
            return (m_nHash < nHash);
        }
    };

    /** lru_entry.
    */
    struct lru_entry
    {
        /** Representation.
        */
        UINT32 m_nHash;
        UINT16 m_nNext;
        UINT16 m_nPrev;

        /** Initialization.
        */
        void initialize (UINT16 nThis, UINT32 nHash = 0)
        {
            m_nHash = nHash;
            m_nNext = nThis;
            m_nPrev = nThis;
        }
    };

    /** Representation.
    */
    head_entry m_aHead;
    hash_entry m_pHash[INETHIST_SIZE_LIMIT];
    lru_entry  m_pList[INETHIST_SIZE_LIMIT];

    /** Initialization.
    */
    void initialize (void);

    void downheap (hash_entry a[], UINT16 n, UINT16 k);
    void heapsort (hash_entry a[], UINT16 n);

    /** capacity.
    */
    UINT16 capacity (void) const
    {
        return (UINT16)(INETHIST_SIZE_LIMIT);
    }

    /** crc32.
    */
    UINT32 crc32 (UniString const & rData) const
    {
        return rtl_crc32 (0, rData.GetBuffer(), rData.Len() * sizeof(sal_Unicode));
    }

    /** find.
    */
    UINT16 find (UINT32 nHash) const;

    /** move.
    */
    void move (UINT16 nSI, UINT16 nDI);

    /** backlink.
    */
    void backlink (UINT16 nThis, UINT16 nTail)
    {
        register lru_entry &rThis = m_pList[nThis];
        register lru_entry &rTail = m_pList[nTail];

        rTail.m_nNext = nThis;
        rTail.m_nPrev = rThis.m_nPrev;
        rThis.m_nPrev = nTail;
        m_pList[rTail.m_nPrev].m_nNext = nTail;
    }

    /** unlink.
    */
    void unlink (UINT16 nThis)
    {
        register lru_entry &rThis = m_pList[nThis];

        m_pList[rThis.m_nPrev].m_nNext = rThis.m_nNext;
        m_pList[rThis.m_nNext].m_nPrev = rThis.m_nPrev;
        rThis.m_nNext = nThis;
        rThis.m_nPrev = nThis;
    }

    /** Not implemented.
    */
    INetURLHistory_Impl (const INetURLHistory_Impl&);
    INetURLHistory_Impl& operator= (const INetURLHistory_Impl&);

public:
    INetURLHistory_Impl (void);
    ~INetURLHistory_Impl (void);

    /** putUrl/queryUrl.
    */
    void putUrl   (const String &rUrl);
    BOOL queryUrl (const String &rUrl);
};

/*========================================================================
 *
 * INetURLHistory_Impl implementation.
 *
 *======================================================================*/
/*
 * INetURLHistory_Impl.
 */
INetURLHistory_Impl::INetURLHistory_Impl (void)
{
    initialize();
}

/*
 * ~INetURLHistory_Impl.
 */
INetURLHistory_Impl::~INetURLHistory_Impl (void)
{
}

/*
 * initialize.
 */
void INetURLHistory_Impl::initialize (void)
{
    m_aHead.initialize();

    USHORT i, n = capacity();
    for (i = 0; i < n; i++)
        m_pHash[i].initialize(i);
    for (i = 0; i < n; i++)
        m_pList[i].initialize(i);
    for (i = 1; i < n; i++)
        backlink (m_aHead.m_nNext, i);
}

/*
 * downheap.
 */
void INetURLHistory_Impl::downheap (hash_entry a[], UINT16 n, UINT16 k)
{
    hash_entry h = a[k];
    while (k < n / 2)
    {
        UINT16 i = k + k + 1;
        if (((i + 1) < n) && (a[i] < a[i + 1])) i++;
        if (!(h < a[i])) break;
        a[k] = a[i];
        k = i;
    }
    a[k] = h;
}

/*
 * heapsort.
 */
void INetURLHistory_Impl::heapsort (hash_entry a[], UINT16 n)
{
    hash_entry h;

    for (UINT16 k = (n - 1) / 2 + 1; k > 0; k--)
        downheap (a, n, k - 1);

    while (n > 0)
    {
        h        = a[0    ];
        a[0    ] = a[n - 1];
        a[n - 1] = h;
        downheap (a, --n, 0);
    }
}

/*
 * find.
 */
UINT16 INetURLHistory_Impl::find (UINT32 nHash) const
{
    UINT16 l = 0;
    UINT16 r = capacity() - 1;
    UINT16 c = capacity();

    while ((l < r) && (r < c))
    {
        UINT16 m = (l + r) / 2;
        if (m_pHash[m] == nHash)
            return m;

        if (m_pHash[m] < nHash)
            l = m + 1;
        else
            r = m - 1;
    }
    return l;
}

/*
 * move.
 */
void INetURLHistory_Impl::move (UINT16 nSI, UINT16 nDI)
{
    hash_entry e = m_pHash[nSI];
    if (nSI < nDI)
    {
        // shift left.
        rtl_moveMemory (
            &m_pHash[nSI    ],
            &m_pHash[nSI + 1],
            (nDI - nSI) * sizeof(hash_entry));
    }
    if (nSI > nDI)
    {
        // shift right.
        rtl_moveMemory (
            &m_pHash[nDI + 1],
            &m_pHash[nDI    ],
            (nSI - nDI) * sizeof(hash_entry));
    }
    m_pHash[nDI] = e;
}

/*
 * putUrl.
 */
void INetURLHistory_Impl::putUrl (const String &rUrl)
{
    UINT32 h = crc32 (rUrl);
    UINT16 k = find (h);
    if ((k < capacity()) && (m_pHash[k] == h))
    {
        // Cache hit.
        UINT16 nMRU = m_pHash[k].m_nLru;
        if (nMRU != m_aHead.m_nNext)
        {
            // Update LRU chain.
            unlink (nMRU);
            backlink (m_aHead.m_nNext, nMRU);

            // Rotate LRU chain.
            m_aHead.m_nNext = m_pList[m_aHead.m_nNext].m_nPrev;
        }
    }
    else
    {
        // Cache miss. Obtain least recently used.
        UINT16 nLRU = m_pList[m_aHead.m_nNext].m_nPrev;

        UINT16 nSI = find (m_pList[nLRU].m_nHash);
        if (!(nLRU == m_pHash[nSI].m_nLru))
        {
            // Update LRU chain.
            nLRU = m_pHash[nSI].m_nLru;
            unlink (nLRU);
            backlink (m_aHead.m_nNext, nLRU);
        }

        // Rotate LRU chain.
        m_aHead.m_nNext = m_pList[m_aHead.m_nNext].m_nPrev;

        // Check source and destination.
        UINT16 nDI = std::min (k, UINT16(capacity() - 1));
        if (nSI < nDI)
        {
            if (!(m_pHash[nDI] < h))
                nDI -= 1;
        }
        if (nDI < nSI)
        {
            if (m_pHash[nDI] < h)
                nDI += 1;
        }

        // Assign data.
        m_pList[m_aHead.m_nNext].m_nHash = m_pHash[nSI].m_nHash = h;
        move (nSI, nDI);
    }
}

/*
 * queryUrl.
 */
BOOL INetURLHistory_Impl::queryUrl (const String &rUrl)
{
    UINT32 h = crc32 (rUrl);
    UINT16 k = find (h);
    if ((k < capacity()) && (m_pHash[k] == h))
    {
        // Cache hit.
        return TRUE;
    }
    else
    {
        // Cache miss.
        return FALSE;
    }
}

/*========================================================================
 *
 * INetURLHistory::StaticInstance implementation.
 *
 *======================================================================*/
INetURLHistory * INetURLHistory::StaticInstance::operator ()()
{
    static INetURLHistory g_aInstance;
    return &g_aInstance;
}

/*========================================================================
 *
 * INetURLHistory implementation.
 *
 *======================================================================*/
/*
 * INetURLHistory.
 */
INetURLHistory::INetURLHistory() : m_pImpl (new INetURLHistory_Impl())
{
}

/*
 * ~INetURLHistory.
 */
INetURLHistory::~INetURLHistory()
{
    DELETEZ (m_pImpl);
}

/*
 * GetOrCreate.
 */
INetURLHistory* INetURLHistory::GetOrCreate()
{
    return rtl_Instance<
        INetURLHistory, StaticInstance,
        osl::MutexGuard, osl::GetGlobalMutex >::create (
            StaticInstance(), osl::GetGlobalMutex());
}

/*
 * NormalizeUrl_Impl.
 */
void INetURLHistory::NormalizeUrl_Impl (INetURLObject &rUrl)
{
    switch (rUrl.GetProtocol())
    {
        case INET_PROT_FILE:
            if (!rUrl.IsCaseSensitive())
            {
                String aPath (rUrl.GetURLPath(INetURLObject::NO_DECODE));
                aPath.ToLowerAscii();
                rUrl.SetURLPath (aPath, INetURLObject::NOT_CANONIC);
            }
            break;

        case INET_PROT_FTP:
            if (!rUrl.HasPort())
                rUrl.SetPort (INETHIST_DEF_FTP_PORT);
            break;

        case INET_PROT_HTTP:
            if (!rUrl.HasPort())
                rUrl.SetPort (INETHIST_DEF_HTTP_PORT);
            if (!rUrl.HasURLPath())
                rUrl.SetURLPath ("/");
            break;

        case INET_PROT_HTTPS:
            if (!rUrl.HasPort())
                rUrl.SetPort (INETHIST_DEF_HTTPS_PORT);
            if (!rUrl.HasURLPath())
                rUrl.SetURLPath ("/");
            break;

        default:
            break;
    }
}

/*
 * PutUrl_Impl.
 */
void INetURLHistory::PutUrl_Impl (const INetURLObject &rUrl)
{
    DBG_ASSERT (m_pImpl, "PutUrl_Impl(): no Implementation");
    if (m_pImpl)
    {
        INetURLObject aHistUrl (rUrl);
        NormalizeUrl_Impl (aHistUrl);

        m_pImpl->putUrl (aHistUrl.GetMainURL(INetURLObject::NO_DECODE));
        Broadcast (INetURLHistoryHint (&rUrl));

        if (aHistUrl.HasMark())
        {
            aHistUrl.SetURL (aHistUrl.GetURLNoMark(INetURLObject::NO_DECODE),
                             INetURLObject::NOT_CANONIC);

            m_pImpl->putUrl (aHistUrl.GetMainURL(INetURLObject::NO_DECODE));
            Broadcast (INetURLHistoryHint (&aHistUrl));
        }
    }
}

/*
 * QueryUrl_Impl.
 */
BOOL INetURLHistory::QueryUrl_Impl (const INetURLObject &rUrl)
{
    DBG_ASSERT (m_pImpl, "QueryUrl_Impl(): no Implementation");
    if (m_pImpl)
    {
        INetURLObject aHistUrl (rUrl);
        NormalizeUrl_Impl (aHistUrl);

        return m_pImpl->queryUrl (aHistUrl.GetMainURL(INetURLObject::NO_DECODE));
    }
    return FALSE;
}


}
