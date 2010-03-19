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

#ifndef SVTOOLS_INSTRM_HXX
#define SVTOOLS_INSTRM_HXX


#ifndef _COM_SUN_STAR_UNO_REFERENCE_H_
#include <com/sun/star/uno/Reference.h>
#endif
#ifndef _STREAM_HXX
#include <tools/stream.hxx>
#endif

namespace com { namespace sun { namespace star { namespace io {
    class XInputStream;
    class XSeekable;
} } } }

namespace binfilter
{

class SvDataPipe_Impl;

//============================================================================
class  SvInputStream: public SvStream
{
    com::sun::star::uno::Reference< com::sun::star::io::XInputStream >
        m_xStream;
    com::sun::star::uno::Reference< com::sun::star::io::XSeekable >
        m_xSeekable;
    SvDataPipe_Impl * m_pPipe;
    ULONG m_nSeekedFrom;

     bool open();

     virtual ULONG GetData(void * pData, ULONG nSize);

     virtual ULONG PutData(void const *, ULONG);

     virtual ULONG SeekPos(ULONG nPos);

     virtual void FlushData();

     virtual void SetSize(ULONG);

public:
    SvInputStream(
        com::sun::star::uno::Reference< com::sun::star::io::XInputStream >
                const &
            rTheStream);

    virtual ~SvInputStream();

    virtual USHORT IsA() const;

    virtual void AddMark(ULONG nPos);

    virtual void RemoveMark(ULONG nPos);
};

}

#endif // SVTOOLS_INSTRM_HXX

