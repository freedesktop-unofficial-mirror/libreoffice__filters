/* -*- Mode: C++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */
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

#ifndef SC_COLROWBAR_HXX
#define SC_COLROWBAR_HXX

#include "hdrcont.hxx"

#include "viewdata.hxx"
namespace binfilter {

class ScHeaderFunctionSet;
class ScHeaderSelectionEngine;

// ---------------------------------------------------------------------------


class ScColBar : public ScHeaderControl
{
    ScViewData*				 pViewData;
    ScHSplitPos				 eWhich;
    ScHeaderFunctionSet*	 pFuncSet;
    ScHeaderSelectionEngine* pSelEngine;

public:
                ScColBar( Window* pParent, ScViewData* pData, ScHSplitPos eWhichPos,
                            ScHeaderFunctionSet* pFunc, ScHeaderSelectionEngine* pEng );
                ~ScColBar();

    virtual USHORT		GetPos();
    virtual USHORT		GetEntrySize( USHORT nEntryNo );
    virtual String 		GetEntryText( USHORT nEntryNo ){DBG_BF_ASSERT(0, "STRIP");String aStr; return aStr;}

    virtual void		SetEntrySize( USHORT nPos, USHORT nNewSize ){DBG_BF_ASSERT(0, "STRIP");}
    virtual void		HideEntries( USHORT nStart, USHORT nEnd ){DBG_BF_ASSERT(0, "STRIP");}

    virtual void		SetMarking( BOOL bSet );
    virtual void		SelectWindow(){DBG_BF_ASSERT(0, "STRIP");}
    virtual BOOL		IsDisabled(){DBG_BF_ASSERT(0, "STRIP");return FALSE;}
    virtual BOOL		ResizeAllowed(){DBG_BF_ASSERT(0, "STRIP");return FALSE;}

    virtual void		DrawInvert( long nDragPos ){DBG_BF_ASSERT(0, "STRIP");}

    virtual String		GetDragHelp( long nVal ){DBG_BF_ASSERT(0, "STRIP"); String aStr; return aStr;}
};


class ScRowBar : public ScHeaderControl
{
    ScViewData*				 pViewData;
    ScVSplitPos				 eWhich;
    ScHeaderFunctionSet*	 pFuncSet;
    ScHeaderSelectionEngine* pSelEngine;

public:
                ScRowBar( Window* pParent, ScViewData* pData, ScVSplitPos eWhichPos,
                            ScHeaderFunctionSet* pFunc, ScHeaderSelectionEngine* pEng );
                ~ScRowBar();

    virtual USHORT		GetPos();
    virtual USHORT		GetEntrySize( USHORT nEntryNo );
    virtual String 		GetEntryText( USHORT nEntryNo ){DBG_BF_ASSERT(0, "STRIP"); String s; return s;}

    virtual USHORT		GetHiddenCount( USHORT nEntryNo ){DBG_BF_ASSERT(0, "STRIP"); return 0;}

    virtual void		SetEntrySize( USHORT nPos, USHORT nNewSize ){DBG_BF_ASSERT(0, "STRIP");}
    virtual void		HideEntries( USHORT nStart, USHORT nEnd ){DBG_BF_ASSERT(0, "STRIP");}

    virtual void		SetMarking( BOOL bSet );
    virtual void		SelectWindow(){DBG_BF_ASSERT(0, "STRIP");}
    virtual BOOL		IsDisabled(){DBG_BF_ASSERT(0, "STRIP"); return FALSE;}
    virtual BOOL		ResizeAllowed(){DBG_BF_ASSERT(0, "STRIP"); return FALSE;}

    virtual void		DrawInvert( long nDragPos ){DBG_BF_ASSERT(0, "STRIP");}

    virtual String		GetDragHelp( long nVal ){DBG_BF_ASSERT(0, "STRIP"); String s; return s;}
};



} //namespace binfilter
#endif


/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
