/*************************************************************************
 *
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER.
 * 
 * Copyright 2008 by Sun Microsystems, Inc.
 *
 * OpenOffice.org - a multi-platform office productivity suite
 *
 * $RCSfile: listenerbase.hxx,v $
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
#ifndef _SVT_LISTENERBASE_HXX
#define _SVT_LISTENERBASE_HXX

namespace binfilter
{

class SvtBroadcaster;
class SvtListener;

class SvtListenerBase
{
    SvtListenerBase *pNext;
    SvtListenerBase *pLeft, *pRight;
    SvtBroadcaster *pBroadcaster;
    SvtListener *pListener;

public:

    SvtListenerBase( SvtListener& rLst, SvtBroadcaster& rBroadcaster );
    ~SvtListenerBase();

    SvtListenerBase* GetNext() const  		{ return pNext; }
    void SetNext( SvtListenerBase* p ) 		{ pNext = p; }

    SvtBroadcaster* GetBroadcaster() const	{ return pBroadcaster; }
    SvtListener* GetListener() const 		{ return pListener; }

    SvtListenerBase* GetLeft() const  		{ return pLeft; }
    SvtListenerBase* GetRight() const  		{ return pRight; }
};

}

#endif

