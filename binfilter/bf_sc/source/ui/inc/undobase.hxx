/*************************************************************************
 *
 *  $RCSfile: undobase.hxx,v $
 *
 *  $Revision: 1.2 $
 *
 *  last change: $Author: mwu $ $Date: 2003-11-06 07:30:16 $
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

#ifndef SC_UNDOBASE_HXX
#define SC_UNDOBASE_HXX

#ifndef _UNDO_HXX //autogen
#include <svtools/undo.hxx>
#endif

#ifndef SC_SCGLOB_HXX
#include "global.hxx"
#endif
namespace binfilter {

class ScDocument;
class ScDocShell;
class SdrUndoAction;
class ScRefUndoData;

//----------------------------------------------------------------------------

class ScSimpleUndo: public SfxUndoAction
{
public:
//STRIP001 					TYPEINFO();
                    ScSimpleUndo( ScDocShell* pDocSh );
    virtual 		~ScSimpleUndo();

    virtual BOOL	Merge( SfxUndoAction *pNextAction );

protected:
    ScDocShell*		pDocShell;
    SfxUndoAction*	pDetectiveUndo;

//STRIP001 	void			BeginUndo();
//STRIP001 	void			EndUndo();
//STRIP001 	void			BeginRedo();
//STRIP001 	void			EndRedo();
//STRIP001 
//STRIP001 	static void		ShowTable( USHORT nTab );
//STRIP001 	static void		ShowTable( const ScRange& rRange );
};

//----------------------------------------------------------------------------

enum ScBlockUndoMode { SC_UNDO_SIMPLE, SC_UNDO_MANUALHEIGHT, SC_UNDO_AUTOHEIGHT };

class ScBlockUndo: public ScSimpleUndo
{
public:
//STRIP001 					TYPEINFO();
                    ScBlockUndo( ScDocShell* pDocSh, const ScRange& rRange,
                                 ScBlockUndoMode eBlockMode );
    virtual 		~ScBlockUndo();

protected:
    ScRange			aBlockRange;
    SdrUndoAction*	pDrawUndo;
    ScBlockUndoMode	eMode;

//STRIP001 	void			BeginUndo();
//STRIP001 	void			EndUndo();
//	void			BeginRedo();
//STRIP001 	void			EndRedo();

//STRIP001 	BOOL			AdjustHeight();
//STRIP001 	void			ShowBlock();
};

//----------------------------------------------------------------------------

//STRIP001 enum ScMoveUndoMode { SC_UNDO_REFFIRST, SC_UNDO_REFLAST };

//STRIP001 class ScMoveUndo: public ScSimpleUndo				// mit Referenzen
//STRIP001 {
//STRIP001 public:
//STRIP001 					TYPEINFO();
//STRIP001 					ScMoveUndo( ScDocShell* pDocSh,
//STRIP001 								ScDocument* pRefDoc, ScRefUndoData* pRefData,
//STRIP001 								ScMoveUndoMode eRefMode );
//STRIP001 	virtual			~ScMoveUndo();
//STRIP001 
//STRIP001 protected:
//STRIP001 	SdrUndoAction*	pDrawUndo;
//STRIP001 	ScDocument*		pRefUndoDoc;
//STRIP001 	ScRefUndoData*	pRefUndoData;
//STRIP001 	ScMoveUndoMode	eMode;
//STRIP001 
//STRIP001 	void			BeginUndo();
//STRIP001 	void			EndUndo();
//STRIP001 //	void			BeginRedo();
//STRIP001 //	void			EndRedo();
//STRIP001 
//STRIP001 private:
//STRIP001 	void			UndoRef();
//STRIP001 };

//----------------------------------------------------------------------------

class ScUndoWrapper: public SfxUndoAction           // for manual merging of actions
{
    SfxUndoAction*  pWrappedUndo;

public:
                            TYPEINFO();
                            ScUndoWrapper( SfxUndoAction* pUndo );
    virtual                 ~ScUndoWrapper();

    SfxUndoAction*          GetWrappedUndo()        { return pWrappedUndo; }
    void                    ForgetWrappedUndo();

    virtual BOOL            IsLinked();
    virtual void            SetLinked( BOOL bIsLinked );
    virtual void            Undo();
    virtual void            Redo();
    virtual void            Repeat(SfxRepeatTarget& rTarget);
    virtual BOOL            CanRepeat(SfxRepeatTarget& rTarget) const;
    virtual BOOL            Merge( SfxUndoAction *pNextAction );
    virtual String          GetComment() const;
    virtual String          GetRepeatComment(SfxRepeatTarget&) const;
    virtual USHORT          GetId() const;
};


} //namespace binfilter
#endif

