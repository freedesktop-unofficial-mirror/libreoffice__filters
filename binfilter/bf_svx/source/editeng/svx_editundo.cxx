/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: svx_editundo.cxx,v $
 *
 *  $Revision: 1.7 $
 *
 *  last change: $Author: rt $ $Date: 2006-10-27 20:43:58 $
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


#ifndef _SV_WINDOW_HXX
#include <vcl/window.hxx>
#endif

#include <impedit.hxx>
#include <editeng.hxx>
namespace binfilter {

DBG_NAME( EditUndo )

#define MAX_UNDOS	100		// ab dieser Menge darf geloescht werden....
#define MIN_UNDOS	50		// soviel muss stehen bleiben...

#define NO_UNDO			0xFFFF
#define GROUP_NOTFOUND	0xFFFF

/*N*/ TYPEINIT1( EditUndoInsertChars, EditUndo );


// -----------------------------------------------------------------------
// EditUndoManager
// ------------------------------------------------------------------------
/*N*/ EditUndoManager::EditUndoManager( ImpEditEngine* p )
/*N*/ {
/*N*/ 	pImpEE = p;
/*N*/ }



// -----------------------------------------------------------------------
// EditUndo
// ------------------------------------------------------------------------
/*N*/ EditUndo::EditUndo( USHORT nI, ImpEditEngine* p )
/*N*/ {
/*N*/ 	DBG_CTOR( EditUndo, 0 );
/*N*/ 	nId = nI;
/*N*/ 	pImpEE = p;
/*N*/ }

/*N*/ EditUndo::~EditUndo()
/*N*/ {
/*N*/ 	DBG_DTOR( EditUndo, 0 );
/*N*/ }

/*N*/ USHORT __EXPORT EditUndo::GetId() const
/*N*/ {
/*N*/ 	DBG_CHKTHIS( EditUndo, 0 );
/*N*/ 	return nId;
/*N*/ }


/*N*/ XubString __EXPORT EditUndo::GetComment() const
/*N*/ {
/*N*/ 	XubString aComment;
/*N*/ 	if ( pImpEE )
/*N*/ 	{
/*N*/ 		EditEngine* pEditEng = pImpEE->GetEditEnginePtr();
/*N*/ 		aComment = pEditEng->GetUndoComment( GetId() );
/*N*/ 	}
/*N*/ 	return aComment;
/*N*/ }

// -----------------------------------------------------------------------
// EditUndoDelContent
// ------------------------------------------------------------------------





// -----------------------------------------------------------------------
// EditUndoConnectParas
// ------------------------------------------------------------------------





// -----------------------------------------------------------------------
// EditUndoSplitPara
// ------------------------------------------------------------------------
/*N*/ EditUndoSplitPara::EditUndoSplitPara( ImpEditEngine* pImpEE, USHORT nN, USHORT nSP )
/*N*/ 					: EditUndo( EDITUNDO_SPLITPARA, pImpEE )
/*N*/ {
/*N*/ 	nNode	= nN;
/*N*/ 	nSepPos	= nSP;
/*N*/ }

/*N*/ EditUndoSplitPara::~EditUndoSplitPara()
/*N*/ {
/*N*/ }

/*N*/ void __EXPORT EditUndoSplitPara::Undo()
/*N*/ {DBG_BF_ASSERT(0, "STRIP"); //STRIP001 
/*N*/ }

/*N*/ void __EXPORT EditUndoSplitPara::Redo()
/*N*/ {DBG_BF_ASSERT(0, "STRIP"); //STRIP001 
/*N*/ }

/*N*/ void __EXPORT EditUndoSplitPara::Repeat()
/*N*/ {
/*N*/ 	DBG_ERROR( "EditUndoSplitPara::Repeat nicht implementiert!" );
/*N*/ }

// -----------------------------------------------------------------------
// EditUndoInsertChars
// ------------------------------------------------------------------------
/*N*/ EditUndoInsertChars::EditUndoInsertChars( ImpEditEngine* pImpEE, const EPaM& rEPaM, const XubString& rStr )
/*N*/ 					: EditUndo( EDITUNDO_INSERTCHARS, pImpEE ),
/*N*/ 						aEPaM( rEPaM ), aText( rStr )
/*N*/ {
/*N*/ }

/*N*/ void __EXPORT EditUndoInsertChars::Undo()
/*N*/ {DBG_BF_ASSERT(0, "STRIP"); //STRIP001 
/*N*/ }

/*N*/ void __EXPORT EditUndoInsertChars::Redo()
/*N*/ {DBG_BF_ASSERT(0, "STRIP"); //STRIP001 
/*N*/ }

/*N*/ BOOL __EXPORT EditUndoInsertChars::Merge( SfxUndoAction* pNextAction )
/*N*/ {
/*N*/ 	if ( !pNextAction->ISA( EditUndoInsertChars ) )
/*N*/ 		return FALSE;
/*N*/ 
/*N*/ 	EditUndoInsertChars* pNext = (EditUndoInsertChars*)pNextAction;
/*N*/ 
/*N*/ 	if ( aEPaM.nPara != pNext->aEPaM.nPara )
/*N*/ 		return FALSE;
/*N*/ 
/*N*/ 	if ( ( aEPaM.nIndex + aText.Len() ) == pNext->aEPaM.nIndex )
/*N*/ 	{
/*N*/ 		aText += pNext->aText;
/*N*/ 		return TRUE;
/*N*/ 	}
/*N*/ 	return FALSE;
/*N*/ }

/*N*/ void __EXPORT EditUndoInsertChars::Repeat()
/*N*/ {
/*N*/ 	DBG_ERROR( "EditUndoInsertChars::Repeat nicht implementiert!" );
/*N*/ }

// -----------------------------------------------------------------------
// EditUndoRemoveChars
// ------------------------------------------------------------------------




// -----------------------------------------------------------------------
// EditUndoInsertFeature
// ------------------------------------------------------------------------
/*N*/ EditUndoInsertFeature::EditUndoInsertFeature( ImpEditEngine* pImpEE, const EPaM& rEPaM, const SfxPoolItem& rFeature)
/*N*/ 					: EditUndo( EDITUNDO_INSERTFEATURE, pImpEE ), aEPaM( rEPaM )
/*N*/ {
/*N*/ 	pFeature = rFeature.Clone();
/*N*/ 	DBG_ASSERT( pFeature, "Feature konnte nicht dupliziert werden: EditUndoInsertFeature" );
/*N*/ }

/*N*/ EditUndoInsertFeature::~EditUndoInsertFeature()
/*N*/ {
/*N*/ 	delete pFeature;
/*N*/ }

/*N*/ void __EXPORT EditUndoInsertFeature::Undo()
/*N*/ {DBG_BF_ASSERT(0, "STRIP"); //STRIP001 
/*N*/ }

/*N*/ void __EXPORT EditUndoInsertFeature::Redo()
/*N*/ {DBG_BF_ASSERT(0, "STRIP"); //STRIP001 
/*N*/ }

/*N*/ void __EXPORT EditUndoInsertFeature::Repeat()
/*N*/ {
/*N*/ 	DBG_ERROR( "EditUndoInsertFeature::Repeat nicht implementiert!" );
/*N*/ }

// -----------------------------------------------------------------------
// EditUndoMoveParagraphs
// ------------------------------------------------------------------------





// -----------------------------------------------------------------------
// EditUndoSetStyleSheet
// ------------------------------------------------------------------------
/*N*/ EditUndoSetStyleSheet::EditUndoSetStyleSheet( ImpEditEngine* pImpEE, USHORT nP,
/*N*/ 						const XubString& rPrevName, SfxStyleFamily ePrevFam,
/*N*/ 						const XubString& rNewName, SfxStyleFamily eNewFam,
/*N*/ 						const SfxItemSet& rPrevParaAttribs )
/*N*/ 	: EditUndo( EDITUNDO_STYLESHEET, pImpEE ), aPrevName( rPrevName ), aNewName( rNewName ),
/*N*/ 	  aPrevParaAttribs( rPrevParaAttribs )
/*N*/ {
/*N*/ 	ePrevFamily = ePrevFam;
/*N*/ 	eNewFamily = eNewFam;
/*N*/ 	nPara = nP;
/*N*/ }

/*N*/ EditUndoSetStyleSheet::~EditUndoSetStyleSheet()
/*N*/ {
/*N*/ }

/*N*/ void __EXPORT EditUndoSetStyleSheet::Undo()
/*N*/ {DBG_BF_ASSERT(0, "STRIP"); //STRIP001 
/*N*/ }

/*N*/ void __EXPORT EditUndoSetStyleSheet::Redo()
/*N*/ {DBG_BF_ASSERT(0, "STRIP"); //STRIP001 
/*N*/ }

/*N*/ void __EXPORT EditUndoSetStyleSheet::Repeat()
/*N*/ {
/*N*/ 	DBG_ERROR( "EditUndoSetStyleSheet::Repeat nicht implementiert!" );
/*N*/ }

// -----------------------------------------------------------------------
// EditUndoSetParaAttribs
// ------------------------------------------------------------------------
/*N*/ EditUndoSetParaAttribs::EditUndoSetParaAttribs( ImpEditEngine* pImpEE, USHORT nP, const SfxItemSet& rPrevItems, const SfxItemSet& rNewItems )
/*N*/ 	: EditUndo( EDITUNDO_PARAATTRIBS, pImpEE ), 
/*N*/ 	  aPrevItems( rPrevItems ),
/*N*/ 	  aNewItems(rNewItems )
/*N*/ {
/*N*/ 	nPara = nP;
/*N*/ }

/*N*/ EditUndoSetParaAttribs::~EditUndoSetParaAttribs()
/*N*/ {
/*N*/ }

/*N*/ void __EXPORT EditUndoSetParaAttribs::Undo()
/*N*/ {DBG_BF_ASSERT(0, "STRIP"); //STRIP001 
/*N*/ }

/*N*/ void __EXPORT EditUndoSetParaAttribs::Redo()
/*N*/ {DBG_BF_ASSERT(0, "STRIP"); //STRIP001 
/*N*/ }

/*N*/ void __EXPORT EditUndoSetParaAttribs::Repeat()
/*N*/ {
/*N*/ 	DBG_ERROR( "EditUndoSetParaAttribs::Repeat nicht implementiert!" );
/*N*/ }

// -----------------------------------------------------------------------
// EditUndoSetAttribs
// ------------------------------------------------------------------------






// -----------------------------------------------------------------------
// EditUndoTransliteration
// ------------------------------------------------------------------------





// -----------------------------------------------------------------------
// EditUndoMarkSelection
// ------------------------------------------------------------------------





}
