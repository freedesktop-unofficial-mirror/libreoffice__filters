/*************************************************************************
 *
 *  $RCSfile: sw_edundo.cxx,v $
 *
 *  $Revision: 1.1 $
 *
 *  last change: $Author: aw $ $Date: 2003-10-02 15:16:45 $
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


#pragma hdrstop

#ifndef _SVDVIEW_HXX //autogen wg. SdrView
#include <bf_svx/svdview.hxx>
#endif

#ifndef _EDITSH_HXX
#include <editsh.hxx>
#endif
#ifndef _FESH_HXX
#include <fesh.hxx>
#endif
#ifndef _DOC_HXX
#include <doc.hxx>
#endif
#ifndef _PAM_HXX
#include <pam.hxx>
#endif
#ifndef _UNDOBJ_HXX
#include <undobj.hxx>
#endif
#ifndef _SWUNDO_HXX
#include <swundo.hxx>
#endif
#ifndef _DCONTACT_HXX
#include <dcontact.hxx>
#endif
#ifndef _FLYFRM_HXX
#include <flyfrm.hxx>
#endif
#ifndef _FRMFMT_HXX
#include <frmfmt.hxx>
#endif
#ifndef _VIEWIMP_HXX
#include <viewimp.hxx>
#endif


/** helper function to select all objects in an SdrMarkList; 
 * implementation: see below */
//STRIP001 void lcl_SelectSdrMarkList( SwEditShell* pShell, 
//STRIP001                             const SdrMarkList* pSdrMarkList );
//STRIP001 
//STRIP001 BOOL SwEditShell::Undo( USHORT nUndoId, USHORT nCnt )
//STRIP001 {
//STRIP001 	SET_CURR_SHELL( this );
//STRIP001 
//STRIP001     // #105332# current undo state was not saved
//STRIP001 	BOOL bRet = FALSE;
//STRIP001     BOOL bSaveDoesUndo = GetDoc()->DoesUndo();
//STRIP001 
//STRIP001 	GetDoc()->DoUndo( FALSE );
//STRIP001 	StartAllAction();
//STRIP001 	{
//STRIP001 		// eigentlich muesste ja nur der aktuelle Cursor berarbeitet
//STRIP001 		// werden, d.H. falls ein Ring besteht, diesen temporaer aufheben,
//STRIP001 		// damit nicht bei Einfuge-Operationen innerhalb von Undo
//STRIP001 		// an allen Bereichen eingefuegt wird.
//STRIP001 		KillPams();
//STRIP001 		SetMark();          // Bound1 und Bound2 in den gleichen Node
//STRIP001 		ClearMark();
//STRIP001 
//STRIP001 		// JP 02.04.98: Cursor merken - beim Auto-Format/-Korrektur
//STRIP001 		// 				soll dieser wieder an die Position
//STRIP001 		USHORT nLastUndoId = GetDoc()->GetUndoIds();
//STRIP001 		BOOL bRestoreCrsr = 1 == nCnt && ( UNDO_AUTOFORMAT == nLastUndoId ||
//STRIP001 										   UNDO_AUTOCORRECT == nLastUndoId );
//STRIP001 		Push();
//STRIP001 
//STRIP001 		//JP 18.09.97: gesicherten TabellenBoxPtr zerstoeren, eine autom.
//STRIP001 		//			Erkennung darf nur noch fuer die neue "Box" erfolgen!
//STRIP001 		ClearTblBoxCntnt();
//STRIP001 
//STRIP001 		SwRedlineMode eOld = GetDoc()->GetRedlineMode();
//STRIP001 
//STRIP001 		SwUndoIter aUndoIter( GetCrsr(), nUndoId );
//STRIP001 		while( nCnt-- )
//STRIP001 		{
//STRIP001 			do {
//STRIP001 
//STRIP001 				bRet |= GetDoc()->Undo( aUndoIter );
//STRIP001 
//STRIP001 				if( !aUndoIter.IsNextUndo() )
//STRIP001 					break;
//STRIP001 
//STRIP001 				// es geht weiter, also erzeuge einen neuen Cursor wenn
//STRIP001 				// der alte schon eine Selection hat
//STRIP001 				// JP 02.04.98: aber nicht wenns ein Autoformat ist
//STRIP001 				if( !bRestoreCrsr && HasSelection() )
//STRIP001 				{
//STRIP001 					CreateCrsr();
//STRIP001 					aUndoIter.pAktPam = GetCrsr();
//STRIP001 				}
//STRIP001 			} while( TRUE );
//STRIP001 		}
//STRIP001 
//STRIP001 		Pop( !bRestoreCrsr );
//STRIP001 
//STRIP001 		if( aUndoIter.pSelFmt )		// dann erzeuge eine Rahmen-Selection
//STRIP001 		{
//STRIP001 			if( RES_DRAWFRMFMT == aUndoIter.pSelFmt->Which() )
//STRIP001 			{
//STRIP001 				SdrObject* pSObj = aUndoIter.pSelFmt->FindSdrObject();
//STRIP001 				((SwFEShell*)this)->SelectObj( pSObj->GetBoundRect().Center() );
//STRIP001 			}
//STRIP001 			else
//STRIP001 			{
//STRIP001 				Point aPt;
//STRIP001 				SwFlyFrm* pFly = ((SwFlyFrmFmt*)aUndoIter.pSelFmt)->GetFrm(
//STRIP001 															&aPt, FALSE );
//STRIP001 				if( pFly )
//STRIP001 					((SwFEShell*)this)->SelectFlyFrm( *pFly, TRUE );
//STRIP001 			}
//STRIP001 		}
//STRIP001 		else if( aUndoIter.pMarkList )
//STRIP001 		{
//STRIP001             lcl_SelectSdrMarkList( this, aUndoIter.pMarkList );
//STRIP001 		}
//STRIP001 		else if( GetCrsr()->GetNext() != GetCrsr() )	// gehe nach einem
//STRIP001 			GoNextCrsr();				// Undo zur alten Undo-Position !!
//STRIP001 
//STRIP001 		GetDoc()->SetRedlineMode( eOld );
//STRIP001 		GetDoc()->CompressRedlines();
//STRIP001 
//STRIP001 		//JP 18.09.97: autom. Erkennung  fuer die neue "Box"
//STRIP001 		SaveTblBoxCntnt();
//STRIP001 	}
//STRIP001 	EndAllAction();
//STRIP001 
//STRIP001     // #105332# undo state was not restored but set to FALSE everytime
//STRIP001 	GetDoc()->DoUndo( bSaveDoesUndo );
//STRIP001 	return bRet;
//STRIP001 }
//STRIP001 
//STRIP001 USHORT SwEditShell::Redo( USHORT nCnt )
//STRIP001 {
//STRIP001 	SET_CURR_SHELL( this );
//STRIP001 
//STRIP001 	BOOL bRet = FALSE;
//STRIP001 
//STRIP001     // #105332# undo state was not saved
//STRIP001     BOOL bSaveDoesUndo = GetDoc()->DoesUndo();
//STRIP001 
//STRIP001 	GetDoc()->DoUndo( FALSE );
//STRIP001 	StartAllAction();
//STRIP001 
//STRIP001 	{
//STRIP001 		// eigentlich muesste ja nur der aktuelle Cursor berarbeitet
//STRIP001 		// werden, d.H. falls ein Ring besteht, diesen temporaer aufheben,
//STRIP001 		// damit nicht bei Einfuge-Operationen innerhalb von Undo
//STRIP001 		// an allen Bereichen eingefuegt wird.
//STRIP001 		KillPams();
//STRIP001 		SetMark();          // Bound1 und Bound2 in den gleichen Node
//STRIP001 		ClearMark();
//STRIP001 
//STRIP001 		//JP 18.09.97: gesicherten TabellenBoxPtr zerstoeren, eine autom.
//STRIP001 		//			Erkennung darf nur noch fuer die neue "Box" erfolgen!
//STRIP001 		ClearTblBoxCntnt();
//STRIP001 
//STRIP001 		SwRedlineMode eOld = GetDoc()->GetRedlineMode();
//STRIP001 
//STRIP001 		SwUndoIter aUndoIter( GetCrsr(), 0 );
//STRIP001 		while( nCnt-- )
//STRIP001 		{
//STRIP001 			do {
//STRIP001 
//STRIP001 				bRet |= GetDoc()->Redo( aUndoIter );
//STRIP001 
//STRIP001 				if( !aUndoIter.IsNextUndo() )
//STRIP001 					break;
//STRIP001 
//STRIP001 				// es geht weiter, also erzeugen einen neuen Cursor wenn
//STRIP001 				// der alte schon eine SSelection hat
//STRIP001 				if( HasSelection() )
//STRIP001 				{
//STRIP001 					CreateCrsr();
//STRIP001 					aUndoIter.pAktPam = GetCrsr();
//STRIP001 				}
//STRIP001 			} while( TRUE );
//STRIP001 		}
//STRIP001 
//STRIP001 		if( aUndoIter.IsUpdateAttr() )
//STRIP001 			UpdateAttr();
//STRIP001 
//STRIP001 		if( aUndoIter.pSelFmt )		// dann erzeuge eine Rahmen-Selection
//STRIP001 		{
//STRIP001 			if( RES_DRAWFRMFMT == aUndoIter.pSelFmt->Which() )
//STRIP001 			{
//STRIP001 				SdrObject* pSObj = aUndoIter.pSelFmt->FindSdrObject();
//STRIP001 				((SwFEShell*)this)->SelectObj( pSObj->GetBoundRect().Center() );
//STRIP001 			}
//STRIP001 			else
//STRIP001 			{
//STRIP001 				Point aPt;
//STRIP001 				SwFlyFrm* pFly = ((SwFlyFrmFmt*)aUndoIter.pSelFmt)->GetFrm(
//STRIP001 															&aPt, FALSE );
//STRIP001 				if( pFly )
//STRIP001 					((SwFEShell*)this)->SelectFlyFrm( *pFly, TRUE );
//STRIP001 			}
//STRIP001 		}
//STRIP001 		else if( aUndoIter.pMarkList )
//STRIP001 		{
//STRIP001             lcl_SelectSdrMarkList( this, aUndoIter.pMarkList );
//STRIP001 		}
//STRIP001 		else if( GetCrsr()->GetNext() != GetCrsr() )	// gehe nach einem
//STRIP001 			GoNextCrsr();					// Redo zur alten Undo-Position !!
//STRIP001 
//STRIP001 		GetDoc()->SetRedlineMode( eOld );
//STRIP001 		GetDoc()->CompressRedlines();
//STRIP001 
//STRIP001 		//JP 18.09.97: autom. Erkennung  fuer die neue "Box"
//STRIP001 		SaveTblBoxCntnt();
//STRIP001 	}
//STRIP001 
//STRIP001 	EndAllAction();
//STRIP001 
//STRIP001     // #105332# undo state was not restored but set FALSE everytime
//STRIP001 	GetDoc()->DoUndo( bSaveDoesUndo );
//STRIP001 	return bRet;
//STRIP001 }
//STRIP001 
//STRIP001 
//STRIP001 USHORT SwEditShell::Repeat( USHORT nCount )
//STRIP001 {
//STRIP001 	SET_CURR_SHELL( this );
//STRIP001 
//STRIP001 	BOOL bRet = FALSE;
//STRIP001 	StartAllAction();
//STRIP001 
//STRIP001 		SwUndoIter aUndoIter( GetCrsr(), 0 );
//STRIP001 		bRet |= GetDoc()->Repeat( aUndoIter, nCount );
//STRIP001 
//STRIP001 	EndAllAction();
//STRIP001 	return bRet;
//STRIP001 }

        // abfragen/setzen der Anzahl von wiederherstellbaren Undo-Actions

/*N*/ USHORT SwEditShell::GetUndoActionCount()
/*N*/ {
/*N*/ 	return SwDoc::GetUndoActionCount();
/*N*/ }


/*N*/ void SwEditShell::SetUndoActionCount( USHORT nNew )
/*N*/ {
/*N*/ 	SwDoc::SetUndoActionCount( nNew );
/*N*/ }




//STRIP001 void lcl_SelectSdrMarkList( SwEditShell* pShell,
//STRIP001                             const SdrMarkList* pSdrMarkList )
//STRIP001 {
//STRIP001     ASSERT( pShell != NULL, "need shell!" );
//STRIP001     ASSERT( pSdrMarkList != NULL, "need mark list" );
//STRIP001 
//STRIP001     if( pShell->ISA( SwFEShell ) )
//STRIP001     {
//STRIP001         SwFEShell* pFEShell = static_cast<SwFEShell*>( pShell );
//STRIP001         for( USHORT i = 0; i < pSdrMarkList->GetMarkCount(); ++i )
//STRIP001             pFEShell->SelectObj( Point(), 
//STRIP001                                  (i==0) ? 0 : SW_ADD_SELECT, 
//STRIP001                                  pSdrMarkList->GetMark( i )->GetObj() );
//STRIP001 
//STRIP001         // the old implementation would always unselect
//STRIP001         // objects, even if no new ones were selected. If this
//STRIP001         // is a problem, we need to re-work this a little.
//STRIP001         ASSERT( pSdrMarkList->GetMarkCount() != 0, "empty mark list" );
//STRIP001     }
//STRIP001 }
