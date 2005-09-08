/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: sw_edundo.cxx,v $
 *
 *  $Revision: 1.4 $
 *
 *  last change: $Author: rt $ $Date: 2005-09-08 09:02:59 $
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


#pragma hdrstop

// auto strip #ifndef _SVDVIEW_HXX //autogen wg. SdrView
// auto strip #include <bf_svx/svdview.hxx>
// auto strip #endif

#ifndef _HORIORNT_HXX
#include <horiornt.hxx>
#endif

// auto strip #ifndef _EDITSH_HXX
// auto strip #include <editsh.hxx>
// auto strip #endif
#ifndef _FESH_HXX
#include <fesh.hxx>
#endif
#ifndef _DOC_HXX
#include <doc.hxx>
#endif
// auto strip #ifndef _PAM_HXX
// auto strip #include <pam.hxx>
// auto strip #endif
// auto strip #ifndef _UNDOBJ_HXX
// auto strip #include <undobj.hxx>
// auto strip #endif
// auto strip #ifndef _SWUNDO_HXX
// auto strip #include <swundo.hxx>
// auto strip #endif
// auto strip #ifndef _DCONTACT_HXX
// auto strip #include <dcontact.hxx>
// auto strip #endif
// auto strip #ifndef _FLYFRM_HXX
// auto strip #include <flyfrm.hxx>
// auto strip #endif
// auto strip #ifndef _FRMFMT_HXX
// auto strip #include <frmfmt.hxx>
// auto strip #endif
// auto strip #ifndef _VIEWIMP_HXX
// auto strip #include <viewimp.hxx>
// auto strip #endif
namespace binfilter {


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
}
