/*************************************************************************
 *
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER.
 * 
 * Copyright 2008 by Sun Microsystems, Inc.
 *
 * OpenOffice.org - a multi-platform office productivity suite
 *
 * $RCSfile: clipfmtitem.hxx,v $
 * $Revision: 1.9 $
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
#ifndef _SVX_CLIPFMTITEM_HXX
#define _SVX_CLIPFMTITEM_HXX

// include ---------------------------------------------------------------

#ifndef _SFXPOOLITEM_HXX
#include <bf_svtools/poolitem.hxx>
#endif
namespace binfilter {

// class SvxClipboardFmtItem ----------------------------------------------
struct SvxClipboardFmtItem_Impl;

class SvxClipboardFmtItem : public SfxPoolItem
{
    SvxClipboardFmtItem_Impl* pImpl;
protected:

    virtual int 			 operator==( const SfxPoolItem& ) const;
    virtual SfxPoolItem*	 Clone( SfxItemPool *pPool = 0 ) const;

public:
    TYPEINFO();
    SvxClipboardFmtItem( const SvxClipboardFmtItem& );
    virtual ~SvxClipboardFmtItem();
};

}//end of namespace binfilter
#endif

