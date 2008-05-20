/*************************************************************************
 *
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER.
 * 
 * Copyright 2008 by Sun Microsystems, Inc.
 *
 * OpenOffice.org - a multi-platform office productivity suite
 *
 * $RCSfile: broadcast.hxx,v $
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
#ifndef _SVT_BROADCAST_HXX
#define _SVT_BROADCAST_HXX

#ifndef _RTTI_HXX //autogen
#include <tools/rtti.hxx>
#endif

namespace binfilter {

class SvtListener;
class SfxHint;
class SvtListenerBase;

//-------------------------------------------------------------------------

class  SvtBroadcaster
{
friend class SvtListener;
friend class SvtListenerBase;
friend class SvtListenerIter;
    SvtListenerBase* pRoot;

    const SvtBroadcaster&	operator=(const SvtBroadcaster &); // verboten

protected:
    virtual void			ListenersGone();

public:
                            TYPEINFO();

                            SvtBroadcaster();
                            SvtBroadcaster( const SvtBroadcaster &rBC );
    virtual 				~SvtBroadcaster();

    void					Broadcast( const SfxHint &rHint );

    BOOL					HasListeners() const { return 0 != pRoot; }
};

}

#endif

