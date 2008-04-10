/*************************************************************************
 *
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER.
 * 
 * Copyright 2008 by Sun Microsystems, Inc.
 *
 * OpenOffice.org - a multi-platform office productivity suite
 *
 * $RCSfile: sdgcpitm.hxx,v $
 * $Revision: 1.4 $
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

#ifndef _SDGCPITM_HXX
#define _SDGCPITM_HXX

#ifndef _SVX_GRFCROP_HXX
#include <bf_svx/grfcrop.hxx>
#endif
#ifndef _SVDDEF_HXX
#include <bf_svx/svddef.hxx>
#endif
namespace binfilter {

//------------------
// SdrGrafCropItem -
//------------------

class SdrGrafCropItem : public SvxGrfCrop
{
public:

                            TYPEINFO();

                            SdrGrafCropItem( sal_Int32 nLeftCrop = 0, sal_Int32 nTopCrop = 0,
                                             sal_Int32 nRightCrop = 0, sal_Int32 nBottomCrop = 0,
                                             USHORT nWhichId = SDRATTR_GRAFCROP ) :
                                SvxGrfCrop( nLeftCrop, nRightCrop, nTopCrop, nBottomCrop, nWhichId ) {}

    virtual SfxPoolItem*	Clone( SfxItemPool* pPool = NULL ) const;
    virtual SfxPoolItem*	Create( SvStream& rIn, USHORT nVer ) const;
    virtual USHORT			GetVersion( USHORT nFileVersion ) const;
};

}//end of namespace binfilter
#endif // _SDGCPITM_HXX
