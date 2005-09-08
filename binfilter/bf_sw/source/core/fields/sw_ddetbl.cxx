/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: sw_ddetbl.cxx,v $
 *
 *  $Revision: 1.5 $
 *
 *  last change: $Author: rt $ $Date: 2005-09-08 09:09:41 $
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

// auto strip #ifndef _FRMFMT_HXX //autogen
// auto strip #include <frmfmt.hxx>
// auto strip #endif

#ifndef _HORIORNT_HXX
#include <horiornt.hxx>
#endif

// auto strip #ifndef _DOC_HXX
// auto strip #include <doc.hxx>
// auto strip #endif
// auto strip #ifndef _INDEX_HXX
// auto strip #include <index.hxx>
// auto strip #endif

#ifndef _ERRHDL_HXX
#include <errhdl.hxx>
#endif

#ifndef _NDTXT_HXX
#include <ndtxt.hxx>
#endif
// auto strip #ifndef _SWTABLE_HXX
// auto strip #include <swtable.hxx>
// auto strip #endif
#ifndef _SWDDETBL_HXX
#include <swddetbl.hxx>
#endif
// auto strip #ifndef _DDEFLD_HXX
// auto strip #include <ddefld.hxx>			// fuer den FieldType
// auto strip #endif
// auto strip #ifndef _NDINDEX_HXX
// auto strip #include <ndindex.hxx>
// auto strip #endif
// auto strip #ifndef _FLDUPDE_HXX
// auto strip #include <fldupde.hxx>
// auto strip #endif
// auto strip #ifndef _SWTBLFMT_HXX
// auto strip #include <swtblfmt.hxx>
// auto strip #endif
namespace binfilter {


/*N*/ TYPEINIT1( SwDDETable, SwTable );

    // Constructor movet alle Lines/Boxen aus der SwTable zu sich.
    // Die SwTable ist danach Leer und muss geloescht werden.
//STRIP001 SwDDETable::SwDDETable( SwTable& rTable, SwDDEFieldType* pDDEType, 
//STRIP001 						BOOL bUpdate )
//STRIP001 	: SwTable( rTable ), aDepend( this, pDDEType )
//STRIP001 {
//STRIP001 	// Kopiere/move die Daten der Tabelle
//STRIP001 	aSortCntBoxes.Insert( &rTable.GetTabSortBoxes(), 0,
//STRIP001 						  rTable.GetTabSortBoxes().Count()  ); // move die Inh. Boxen
//STRIP001 	rTable.GetTabSortBoxes().Remove( (USHORT)0, rTable.GetTabSortBoxes().Count() );
//STRIP001 
//STRIP001 	aLines.Insert( &rTable.GetTabLines(),0 );						// move die Lines
//STRIP001 	rTable.GetTabLines().Remove( 0, rTable.GetTabLines().Count() );
//STRIP001 
//STRIP001 	if( aLines.Count() )
//STRIP001 	{
//STRIP001 		SwDoc* pDoc = GetFrmFmt()->GetDoc();
//STRIP001 		const SwNode& rNd = *GetTabSortBoxes()[0]->GetSttNd();
//STRIP001 		if( rNd.GetNodes().IsDocNodes() )
//STRIP001 		{
//STRIP001 			// "aktivieren der Updates" (Modify nicht noch mal rufen)
//STRIP001 			aDepend.LockModify();
//STRIP001 			pDDEType->IncRefCnt();
//STRIP001 			aDepend.UnlockModify();
//STRIP001 
//STRIP001 			// Setzen der Werte in die einzelnen Boxen
//STRIP001 			// update box content only if update flag is set (false in import)
//STRIP001 			if (bUpdate)
//STRIP001 				ChangeContent();
//STRIP001 		}
//STRIP001 	}
//STRIP001 }

//STRIP001 __EXPORT SwDDETable::~SwDDETable()
//STRIP001 {
//STRIP001 	SwDDEFieldType* pFldTyp = (SwDDEFieldType*)aDepend.GetRegisteredIn();
//STRIP001 	SwDoc* pDoc = GetFrmFmt()->GetDoc();
//STRIP001 	if( !pDoc->IsInDtor() && aLines.Count() &&
//STRIP001 		GetTabSortBoxes()[0]->GetSttNd()->GetNodes().IsDocNodes() )
//STRIP001 		pFldTyp->DecRefCnt();
//STRIP001 
//STRIP001 	// sind wir der letzte Abhaengige vom "geloeschten Feld" dann loesche dieses
//STRIP001 	if( pFldTyp->IsDeleted() && pFldTyp->IsLastDepend() )
//STRIP001 	{
//STRIP001 		pFldTyp->Remove( &aDepend );
//STRIP001 		delete pFldTyp;
//STRIP001 	}
//STRIP001 }

//STRIP001 void SwDDETable::Modify( SfxPoolItem* pOld, SfxPoolItem* pNew )
//STRIP001 {
//STRIP001 	if( pNew && RES_UPDATEDDETBL == pNew->Which() )
//STRIP001 		ChangeContent();
//STRIP001 	else
//STRIP001 		SwTable::Modify( pOld, pNew );
//STRIP001 }

//STRIP001 void SwDDETable::ChangeContent()
//STRIP001 {
//STRIP001 	ASSERT( GetFrmFmt(), "Kein FrameFormat" );
//STRIP001 	SwDoc* pDoc = GetFrmFmt()->GetDoc();
//STRIP001 
//STRIP001 	// Stehen wir im richtigen NodesArray (Wegen UNDO)
//STRIP001 	if( !aLines.Count() )
//STRIP001 		return;
//STRIP001 	ASSERT( GetTabSortBoxes().Count(), "Tabelle ohne Inhalt?" );
//STRIP001 	if( !GetTabSortBoxes()[0]->GetSttNd()->GetNodes().IsDocNodes() )
//STRIP001 		return;
//STRIP001 
//STRIP001 	// zugriff auf den DDEFldType
//STRIP001 	SwDDEFieldType* pDDEType = (SwDDEFieldType*)aDepend.GetRegisteredIn();
//STRIP001 
//STRIP001 	String aExpand = pDDEType->GetExpansion();
//STRIP001 	aExpand.EraseAllChars( '\r' );
//STRIP001 
//STRIP001 	for( USHORT n = 0; n < aLines.Count(); ++n )
//STRIP001 	{
//STRIP001 		String aLine = aExpand.GetToken( n, '\n' );
//STRIP001 		SwTableLine* pLine = aLines[ n ];
//STRIP001 		for( USHORT i = 0; i < pLine->GetTabBoxes().Count(); ++i )
//STRIP001 		{
//STRIP001 			SwTableBox* pBox = pLine->GetTabBoxes()[ i ];
//STRIP001 			ASSERT( pBox->GetSttIdx(), "keine InhaltsBox" );
//STRIP001 			SwNodeIndex aNdIdx( *pBox->GetSttNd(), 1 );
//STRIP001 			SwTxtNode* pTxtNode = aNdIdx.GetNode().GetTxtNode();
//STRIP001 			ASSERT( pTxtNode, "Kein Node" );
//STRIP001 			SwIndex aCntIdx( pTxtNode, 0 );
//STRIP001 			pTxtNode->Erase( aCntIdx );
//STRIP001 			pTxtNode->Insert( aLine.GetToken( i, '\t' ), aCntIdx );
//STRIP001 
//STRIP001 			SwTableBoxFmt* pBoxFmt = (SwTableBoxFmt*)pBox->GetFrmFmt();
//STRIP001 			pBoxFmt->LockModify();
//STRIP001 			pBoxFmt->ResetAttr( RES_BOXATR_VALUE );
//STRIP001 			pBoxFmt->UnlockModify();
//STRIP001 		}
//STRIP001 	}
//STRIP001 
//STRIP001 	if( AUTOUPD_FIELD_AND_CHARTS == pDoc->GetFldUpdateFlags() )
//STRIP001 		pDoc->SetFieldsDirty( TRUE );
//STRIP001 }

/*N*/ SwDDEFieldType* SwDDETable::GetDDEFldType()
/*N*/ {
DBG_BF_ASSERT(0, "STRIP"); return NULL;//STRIP001 //STRIP001 	return (SwDDEFieldType*)aDepend.GetRegisteredIn();
/*N*/ }

//STRIP001 BOOL SwDDETable::NoDDETable()
//STRIP001 {
//STRIP001 	// suche den TabellenNode
//STRIP001 	ASSERT( GetFrmFmt(), "Kein FrameFormat" );
//STRIP001 	SwDoc* pDoc = GetFrmFmt()->GetDoc();
//STRIP001 
//STRIP001 	// Stehen wir im richtigen NodesArray (Wegen UNDO)
//STRIP001 	if( !aLines.Count() )
//STRIP001 		return FALSE;
//STRIP001 	ASSERT( GetTabSortBoxes().Count(), "Tabelle ohne Inhalt?" );
//STRIP001 	SwNode* pNd = (SwNode*)GetTabSortBoxes()[0]->GetSttNd();
//STRIP001 	if( !pNd->GetNodes().IsDocNodes() )
//STRIP001 		return FALSE;
//STRIP001 
//STRIP001 	SwTableNode* pTblNd = pNd->FindTableNode();
//STRIP001 	ASSERT( pTblNd, "wo steht denn die Tabelle ?");
//STRIP001 
//STRIP001 	SwTable* pNewTbl = new SwTable( *this );
//STRIP001 
//STRIP001 	// Kopiere/move die Daten der Tabelle
//STRIP001 	pNewTbl->GetTabSortBoxes().Insert( &GetTabSortBoxes(), 0,
//STRIP001 						  GetTabSortBoxes().Count()  ); // move die Inh. Boxen
//STRIP001 	GetTabSortBoxes().Remove( (USHORT)0, GetTabSortBoxes().Count() );
//STRIP001 
//STRIP001 	pNewTbl->GetTabLines().Insert( &GetTabLines(),0 );                      // move die Lines
//STRIP001 	GetTabLines().Remove( 0, GetTabLines().Count() );
//STRIP001 
//STRIP001 	if( pDoc->GetRootFrm() )
//STRIP001 		((SwDDEFieldType*)aDepend.GetRegisteredIn())->DecRefCnt();
//STRIP001 
//STRIP001 	pTblNd->SetNewTable( pNewTbl );       // setze die Tabelle
//STRIP001 
//STRIP001 	return TRUE;
//STRIP001 }


}
