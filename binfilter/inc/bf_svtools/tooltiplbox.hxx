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

#ifndef SVTOOLS_TOOLTIPLBOX_HXX
#define SVTOOLS_TOOLTIPLBOX_HXX

#ifndef INCLUDED_SVTDLLAPI_H
#include "bf_svtools/svtdllapi.h"
#endif

#ifndef _SV_LSTBOX_HXX
#include <vcl/lstbox.hxx>
#endif

namespace binfilter
{

// ============================================================================

/** ListBox with tool tips for long entries. */
class ToolTipListBox : public ListBox
{
public:
                                ToolTipListBox( Window* pParent, WinBits nStyle = WB_BORDER );
                                ToolTipListBox( Window* pParent, const ResId& rResId );

protected:
    virtual void                RequestHelp( const HelpEvent& rHEvt );
};

// ----------------------------------------------------------------------------

/** MultiListBox with tool tips for long entries. */
class  ToolTipMultiListBox : public MultiListBox
{
public:
                                ToolTipMultiListBox( Window* pParent, WinBits nStyle = WB_BORDER );
                                ToolTipMultiListBox( Window* pParent, const ResId& rResId );

protected:
    virtual void                RequestHelp( const HelpEvent& rHEvt );
};

// ============================================================================

}

#endif

