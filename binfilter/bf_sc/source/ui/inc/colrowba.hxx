/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: colrowba.hxx,v $
 *
 *  $Revision: 1.4 $
 *
 *  last change: $Author: rt $ $Date: 2005-09-07 19:36:08 $
 *
 *  The Contents of this file are made available subject to
 *  the terms of GNU Lesser General Public License Version 2.1.
 *
 *
 *    GNU Lesser General Public License Version 2.1
 *    =============================================
 *    Copyright 2005 by Sun Microsystems, Inc.
 *    901 San Antonio Road, Palo Alto, CA 94303, USA
 *
 *    This library is free software; you can redistribute it and/or
 *    modify it under the terms of the GNU Lesser General Public
 *    License version 2.1, as published by the Free Software Foundation.
 *
 *    This library is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *    Lesser General Public License for more details.
 *
 *    You should have received a copy of the GNU Lesser General Public
 *    License along with this library; if not, write to the Free Software
 *    Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 *    MA  02111-1307  USA
 *
 ************************************************************************/

#ifndef SC_COLROWBAR_HXX
#define SC_COLROWBAR_HXX

#ifndef SC_HDRCONT_HXX
#include "hdrcont.hxx"
#endif

#ifndef SC_VIEWDATA_HXX
#include "viewdata.hxx"
#endif
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
    virtual String 		GetEntryText( USHORT nEntryNo ){DBG_BF_ASSERT(0, "STRIP");String aStr; return aStr;} //STRIP001 virtual String 		GetEntryText( USHORT nEntryNo );

    virtual void		SetEntrySize( USHORT nPos, USHORT nNewSize ){DBG_BF_ASSERT(0, "STRIP");} //STRIP001 virtual void		SetEntrySize( USHORT nPos, USHORT nNewSize );
    virtual void		HideEntries( USHORT nStart, USHORT nEnd ){DBG_BF_ASSERT(0, "STRIP");} //STRIP001 virtual void		HideEntries( USHORT nStart, USHORT nEnd );

    virtual void		SetMarking( BOOL bSet );
    virtual void		SelectWindow(){DBG_BF_ASSERT(0, "STRIP");} //STRIP001 virtual void		SelectWindow();
    virtual BOOL		IsDisabled(){DBG_BF_ASSERT(0, "STRIP");return FALSE;} //STRIP001 virtual BOOL		IsDisabled();
    virtual BOOL		ResizeAllowed(){DBG_BF_ASSERT(0, "STRIP");return FALSE;} //STRIP001 virtual BOOL		ResizeAllowed();

    virtual void		DrawInvert( long nDragPos ){DBG_BF_ASSERT(0, "STRIP");} //STRIP001 virtual void		DrawInvert( long nDragPos );

    virtual String		GetDragHelp( long nVal ){DBG_BF_ASSERT(0, "STRIP"); String aStr; return aStr;}//STRIP001 virtual String		GetDragHelp( long nVal );
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
    virtual String 		GetEntryText( USHORT nEntryNo ){DBG_BF_ASSERT(0, "STRIP"); String s; return s;}//STRIP001 virtual String 		GetEntryText( USHORT nEntryNo );

    virtual USHORT		GetHiddenCount( USHORT nEntryNo ){DBG_BF_ASSERT(0, "STRIP"); return 0;}//STRIP001 virtual USHORT		GetHiddenCount( USHORT nEntryNo );	// nur fuer Zeilen

    virtual void		SetEntrySize( USHORT nPos, USHORT nNewSize ){DBG_BF_ASSERT(0, "STRIP");} //STRIP001 virtual void		SetEntrySize( USHORT nPos, USHORT nNewSize );
    virtual void		HideEntries( USHORT nStart, USHORT nEnd ){DBG_BF_ASSERT(0, "STRIP");} //STRIP001 virtual void		HideEntries( USHORT nStart, USHORT nEnd );

    virtual void		SetMarking( BOOL bSet );
    virtual void		SelectWindow(){DBG_BF_ASSERT(0, "STRIP");} //STRIP001 virtual void		SelectWindow();
    virtual BOOL		IsDisabled(){DBG_BF_ASSERT(0, "STRIP"); return FALSE;}//STRIP001 virtual BOOL		IsDisabled();
    virtual BOOL		ResizeAllowed(){DBG_BF_ASSERT(0, "STRIP"); return FALSE;}//STRIP001 virtual BOOL		ResizeAllowed();

    virtual void		DrawInvert( long nDragPos ){DBG_BF_ASSERT(0, "STRIP");} //STRIP001 virtual void		DrawInvert( long nDragPos );

    virtual String		GetDragHelp( long nVal ){DBG_BF_ASSERT(0, "STRIP"); String s; return s;}//STRIP001 virtual String		GetDragHelp( long nVal );
};



} //namespace binfilter
#endif


