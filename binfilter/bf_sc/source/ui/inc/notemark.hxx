/*************************************************************************
 *
 *  $RCSfile: notemark.hxx,v $
 *
 *  $Revision: 1.2 $
 *
 *  last change: $Author: mwu $ $Date: 2003-11-06 07:29:57 $
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

#ifndef SC_NOTEMARK_HXX
#define SC_NOTEMARK_HXX

#ifndef _MAPMOD_HXX //autogen
#include <vcl/mapmod.hxx>
#endif
#ifndef _TIMER_HXX //autogen
#include <vcl/timer.hxx>
#endif

#ifndef SC_SCGLOB_HXX
#include "global.hxx"
#endif
namespace binfilter {

//STRIP001 class SdrModel;
//STRIP001 class SdrObject;
//STRIP001 
class ScNoteMarker
{
//STRIP001 private:
//STRIP001 	Window*		pWindow;
//STRIP001 	Window*		pRightWin;
//STRIP001 	Window*		pBottomWin;
//STRIP001 	Window*		pDiagWin;
//STRIP001 	ScDocument*	pDoc;
//STRIP001 	ScAddress	aDocPos;
//STRIP001 	String		aUserText;
//STRIP001 	Timer		aTimer;
//STRIP001 	MapMode		aMapMode;
//STRIP001 	BOOL		bLeft;
//STRIP001 	BOOL		bByKeyboard;
//STRIP001 
//STRIP001 	Rectangle		aRect;
//STRIP001 	SdrModel*		pModel;
//STRIP001 	SdrObject*		pObject;
//STRIP001 	BOOL			bVisible;
//STRIP001 
//STRIP001 	DECL_LINK( TimeHdl, Timer* );
//STRIP001 
public:
    ScNoteMarker( Window* pWin,							//STRIP001 				ScNoteMarker( Window* pWin,
        Window* pRight, Window* pBottom, Window* pDiagonal,//STRIP001 								Window* pRight, Window* pBottom, Window* pDiagonal,
        ScDocument* pD, ScAddress aPos,						//STRIP001 								ScDocument* pD, ScAddress aPos,
        const String& rUser, const MapMode& rMap,			//STRIP001 								const String& rUser, const MapMode& rMap,
        BOOL bLeftEdge, BOOL bForce, BOOL bKeyboard ){DBG_ASSERT(0, "STRIP");} //STRIP001 								BOOL bLeftEdge, BOOL bForce, BOOL bKeyboard );
//STRIP001 				~ScNoteMarker();
//STRIP001 
//STRIP001 	void		Draw();
//STRIP001 	void		InvalidateWin();
//STRIP001 
//STRIP001 	ScAddress	GetDocPos() const		{ return aDocPos; }
//STRIP001 	BOOL		IsByKeyboard() const	{ return bByKeyboard; }
};



} //namespace binfilter
#endif

