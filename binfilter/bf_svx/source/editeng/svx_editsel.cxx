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


#ifdef _MSC_VER
#pragma hdrstop
#endif




#include <vcl/window.hxx>

#include <impedit.hxx>
#include <editview.hxx>
namespace binfilter {

//	----------------------------------------------------------------------
//	class EditSelFunctionSet
//	----------------------------------------------------------------------
/*N*/ EditSelFunctionSet::EditSelFunctionSet()
/*N*/ {
/*N*/ 	pCurView = NULL;
/*N*/ }

/*N*/ void EditSelFunctionSet::CreateAnchor()
/*N*/ {DBG_BF_ASSERT(0, "STRIP");
/*N*/ }

/*N*/ void EditSelFunctionSet::DestroyAnchor()
/*N*/ {
/*N*/ 	// Nur bei Mehrfachselektion
/*N*/ }

/*N*/ BOOL EditSelFunctionSet::SetCursorAtPoint( const Point& /*rPointPixel*/, BOOL )
/*N*/ {DBG_BF_ASSERT(0, "STRIP");
/*N*/ 	return FALSE;
/*N*/ }

/*N*/ BOOL EditSelFunctionSet::IsSelectionAtPoint( const Point& /*rPointPixel*/ )
/*N*/ {DBG_BF_ASSERT(0, "STRIP");
/*N*/     return FALSE;
/*N*/ }

/*N*/ void EditSelFunctionSet::DeselectAtPoint( const Point& )
/*N*/ {
/*N*/ // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
/*N*/ // !  Implementieren, wenn Mehrfachselektion moeglich  !
/*N*/ // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
/*N*/ }

/*N*/ void EditSelFunctionSet::BeginDrag()
/*N*/ {
/*N*/ 	// Nur bei Mehrfachselektion
/*N*/ }


/*N*/ void EditSelFunctionSet::DeselectAll()
/*N*/ {DBG_BF_ASSERT(0, "STRIP");
/*N*/ }

//	----------------------------------------------------------------------
//	class EditSelectionEngine
//	----------------------------------------------------------------------
/*N*/ EditSelectionEngine::EditSelectionEngine() : SelectionEngine( (Window*)0 )
/*N*/ {
/*N*/ 	// Wegen Bug OV: (1994)
/*N*/ 	// 1995: RangeSelection lassen, SingleSelection nur fuer ListBoxen geeignet!
/*N*/ 	SetSelectionMode( RANGE_SELECTION );
/*N*/ 	EnableDrag( TRUE );
/*N*/ }

/*N*/ void EditSelectionEngine::SetCurView( EditView* pNewView )
/*N*/ {
/*N*/ 	if ( GetFunctionSet() )
/*N*/ 		((EditSelFunctionSet*)GetFunctionSet())->SetCurView( pNewView );
/*N*/ 
/*N*/ 	if ( pNewView )
/*?*/ 		SetWindow( pNewView->GetWindow() );
/*N*/ 	else
/*N*/ 		SetWindow( (Window*)0 );
/*N*/ }


}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
