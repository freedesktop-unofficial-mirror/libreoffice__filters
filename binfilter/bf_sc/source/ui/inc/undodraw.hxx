/*************************************************************************
 *
 *  $RCSfile: undodraw.hxx,v $
 *
 *  $Revision: 1.1.1.1 $
 *
 *  last change: $Author: hjs $ $Date: 2003-10-01 12:18:27 $
 *
 *  The Contents of this file are made available subject to the terms of
 *  either of the following licenses
 *
 *         - GNU Lesser General Public License Version 2.1
 *         - Sun Industry Standards Source License Version 1.1
 *
 *  Sun Microsystems Inc., October, 2000
 *
 *  GNU Lesser General Public License Version 2.1
 *  =============================================
 *  Copyright 2000 by Sun Microsystems, Inc.
 *  901 San Antonio Road, Palo Alto, CA 94303, USA
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public
 *  License version 2.1, as published by the Free Software Foundation.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public
 *  License along with this library; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 *  MA  02111-1307  USA
 *
 *
 *  Sun Industry Standards Source License Version 1.1
 *  =================================================
 *  The contents of this file are subject to the Sun Industry Standards
 *  Source License Version 1.1 (the "License"); You may not use this file
 *  except in compliance with the License. You may obtain a copy of the
 *  License at http://www.openoffice.org/license.html.
 *
 *  Software provided under this License is provided on an "AS IS" basis,
 *  WITHOUT WARRANTY OF ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING,
 *  WITHOUT LIMITATION, WARRANTIES THAT THE SOFTWARE IS FREE OF DEFECTS,
 *  MERCHANTABLE, FIT FOR A PARTICULAR PURPOSE, OR NON-INFRINGING.
 *  See the License for the specific provisions governing your rights and
 *  obligations concerning the Software.
 *
 *  The Initial Developer of the Original Code is: Sun Microsystems, Inc.
 *
 *  Copyright: 2000 by Sun Microsystems, Inc.
 *
 *  All Rights Reserved.
 *
 *  Contributor(s): _______________________________________
 *
 *
 ************************************************************************/

#ifndef SC_UNDODRAW_HXX
#define SC_UNDODRAW_HXX

#ifndef _UNDO_HXX //autogen
#include <svtools/undo.hxx>
#endif

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



#endif

