/*************************************************************************
 *
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER.
 * 
 * Copyright 2008 by Sun Microsystems, Inc.
 *
 * OpenOffice.org - a multi-platform office productivity suite
 *
 * $RCSfile: isethint.hxx,v $
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
#ifndef _SFXISETHINT_HXX
#define _SFXISETHINT_HXX

#ifndef INCLUDED_SVLDLLAPI_H

#endif

#ifndef _HINT_HXX
#include <bf_svtools/hint.hxx>
#endif

namespace binfilter
{

class SfxItemSet;

//--------------------------------------------------------------------

class  SfxItemSetHint: public SfxHint
{
    SfxItemSet*			_pItemSet;

public:
                        TYPEINFO();

                        SfxItemSetHint( SfxItemSet *pItemSet );
                        SfxItemSetHint( const SfxItemSet &rItemSet );
    virtual				~SfxItemSetHint();

    const SfxItemSet&	GetItemSet() const { return *_pItemSet; }
};

}

#endif

