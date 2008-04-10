/*************************************************************************
 *
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER.
 * 
 * Copyright 2008 by Sun Microsystems, Inc.
 *
 * OpenOffice.org - a multi-platform office productivity suite
 *
 * $RCSfile: outstrm.hxx,v $
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

#ifndef SVTOOLS_OUTSTRM_HXX
#define SVTOOLS_OUTSTRM_HXX

#ifndef INCLUDED_SVLDLLAPI_H

#endif

#ifndef _COM_SUN_STAR_UNO_REFERENCE_H_
#include <com/sun/star/uno/Reference.h>
#endif
#ifndef _STREAM_HXX
#include <tools/stream.hxx>
#endif

namespace com { namespace sun { namespace star { namespace io {
    class XOutputStream;
} } } }

namespace binfilter
{

//============================================================================
class  SvOutputStream: public SvStream
{
    com::sun::star::uno::Reference< com::sun::star::io::XOutputStream >
        m_xStream;

     virtual ULONG GetData(void *, ULONG);

     virtual ULONG PutData(void const * pData, ULONG nSize);

     virtual ULONG SeekPos(ULONG);

     virtual void FlushData();

     virtual void SetSize(ULONG);

public:
    SvOutputStream(com::sun::star::uno::Reference<
                           com::sun::star::io::XOutputStream > const &
                       rTheStream);

    virtual ~SvOutputStream();

    virtual USHORT IsA() const;
};

}

#endif // SVTOOLS_OUTSTRM_HXX

