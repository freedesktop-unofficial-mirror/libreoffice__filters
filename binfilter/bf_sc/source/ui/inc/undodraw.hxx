/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: undodraw.hxx,v $
 *
 *  $Revision: 1.3 $
 *
 *  last change: $Author: rt $ $Date: 2005-09-07 20:27:03 $
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

#ifndef SC_UNDODRAW_HXX
#define SC_UNDODRAW_HXX

#ifndef _UNDO_HXX //autogen
#include <svtools/undo.hxx>
#endif
namespace binfilter {

class ScDocShell;

class ScUndoDraw: public SfxUndoAction
{
    SfxUndoAction*	pDrawUndo;
    ScDocShell*		pDocShell;

public:
                            TYPEINFO();
                            ScUndoDraw( SfxUndoAction* pUndo, ScDocShell* pDocSh );
    virtual 				~ScUndoDraw();

    SfxUndoAction*			GetDrawUndo()		{ return pDrawUndo; }
    void					ForgetDrawUndo();

//STRIP001 	virtual BOOL			IsLinked();
//STRIP001 	virtual void			SetLinked( BOOL bIsLinked );
//STRIP001 	virtual void			Undo();
//STRIP001 	virtual void			Redo();
//STRIP001 	virtual void			Repeat(SfxRepeatTarget& rTarget);
//STRIP001 	virtual BOOL			CanRepeat(SfxRepeatTarget& rTarget) const;
//STRIP001 	virtual BOOL			Merge( SfxUndoAction *pNextAction );
//STRIP001 	virtual String          GetComment() const;
//STRIP001 	virtual String			GetRepeatComment(SfxRepeatTarget&) const;
//STRIP001 	virtual USHORT			GetId() const;
};



} //namespace binfilter
#endif

