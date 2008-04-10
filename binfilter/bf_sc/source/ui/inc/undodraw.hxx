/*************************************************************************
 *
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER.
 * 
 * Copyright 2008 by Sun Microsystems, Inc.
 *
 * OpenOffice.org - a multi-platform office productivity suite
 *
 * $RCSfile: undodraw.hxx,v $
 * $Revision: 1.6 $
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

#ifndef SC_UNDODRAW_HXX
#define SC_UNDODRAW_HXX

#ifndef _UNDO_HXX //autogen
#include <bf_svtools/undo.hxx>
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

};



} //namespace binfilter
#endif

