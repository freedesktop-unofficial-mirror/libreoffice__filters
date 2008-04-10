/*************************************************************************
 *
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER.
 * 
 * Copyright 2008 by Sun Microsystems, Inc.
 *
 * OpenOffice.org - a multi-platform office productivity suite
 *
 * $RCSfile: dinfobj.hxx,v $
 * $Revision: 1.5 $
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
#ifndef _SFX_DINFOBJ_HXX
#define _SFX_DINFOBJ_HXX


#ifndef _AUTO_HXX //autogen
#include <bf_so3/auto.hxx>
#endif
#include "docinf.hxx"
#include "dinfdlg.hxx"
namespace binfilter {

class SfxMedium;

//=========================================================================

class SfxDocumentInfoObject_Impl: public SvDispatch
{
    SfxDocumentInfoItem 	aDocInfo;
    SfxMedium*				pMedium;

protected:
    SvGlobalName			GetTypeName() const;
    BOOL					FillTypeLibInfo( String * pName,
                                     USHORT * pMajor, USHORT * pMinor ) const;

public:
                            SfxDocumentInfoObject_Impl();
                            ~SfxDocumentInfoObject_Impl();

    virtual void 			SFX_NOTIFY( SfxBroadcaster& rBC, const TypeId& rBCType,
                                    const SfxHint& rHint, const TypeId& rHintType );
};


}//end of namespace binfilter
#endif

