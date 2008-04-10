/*************************************************************************
 *
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER.
 * 
 * Copyright 2008 by Sun Microsystems, Inc.
 *
 * OpenOffice.org - a multi-platform office productivity suite
 *
 * $RCSfile: svx_unomlstr.cxx,v $
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

#ifndef _SVDOBJ_HXX
#include <svdobj.hxx>
#endif

#include "unomlstr.hxx"
namespace binfilter {

using namespace ::com::sun::star;

SvxUnoShapeModifyListener::SvxUnoShapeModifyListener( SdrObject* pObj ) throw()
{
    mpObj = pObj;
}

SvxUnoShapeModifyListener::~SvxUnoShapeModifyListener() throw()
{
}

// ::com::sun::star::util::XModifyListener
void SAL_CALL SvxUnoShapeModifyListener::modified(const lang::EventObject& aEvent) throw( uno::RuntimeException )
{
    if( mpObj )
        mpObj->SendRepaintBroadcast();
}

// ::com::sun::star::lang::XEventListener  
void SvxUnoShapeModifyListener::disposing(const lang::EventObject& Source) throw( uno::RuntimeException )
{
    invalidate();
}
 
// internal
void SvxUnoShapeModifyListener::invalidate() throw()
{
    mpObj = NULL;
}


}
