/*************************************************************************
 *
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER.
 * 
 * Copyright 2008 by Sun Microsystems, Inc.
 *
 * OpenOffice.org - a multi-platform office productivity suite
 *
 * $RCSfile: bmpwin.hxx,v $
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

#ifndef _BMPWIN_HXX
#define _BMPWIN_HXX

#ifndef _GRAPH_HXX //autogen
#include <vcl/graph.hxx>
#endif
#ifndef _WINDOW_HXX //autogen
#include <vcl/window.hxx>
#endif
namespace binfilter {


/*--------------------------------------------------------------------
    Beschreibung:	Extended Page fuer Grafiken
 --------------------------------------------------------------------*/

class BmpWindow : public Window
{
    void Paint(const Rectangle& rRect);
    Graphic	aGraphic;
    Bitmap 	aBmp;
    BOOL  	bHorz : 1;
    BOOL  	bVert : 1;
    BOOL 	bGraphic : 1;
    BOOL  	bLeftAlign : 1;

public:
    BmpWindow(Window* pPar, USHORT nId,
                const Graphic& rGraphic, const Bitmap& rBmp);
    BmpWindow(Window* pParent, const ResId rResId) :
        Window(pParent, rResId), bLeftAlign(TRUE),
        bHorz(FALSE), bVert(FALSE),bGraphic(FALSE){}
    ~BmpWindow();
    void MirrorVert(BOOL bMirror) { bVert = bMirror; Invalidate(); }
    void MirrorHorz(BOOL bMirror) { bHorz = bMirror; Invalidate(); }
    void SetGraphic(const Graphic& rGrf);

};

} //namespace binfilter
#endif
