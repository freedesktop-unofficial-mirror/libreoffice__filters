/*************************************************************************
 *
 *  $RCSfile: sc_dbdocimp.cxx,v $
 *
 *  $Revision: 1.1.1.1 $
 *
 *  last change: $Author: hjs $ $Date: 2003-10-01 12:18:20 $
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

#ifdef PCH
#include "ui_pch.hxx"
#endif

#pragma hdrstop

// INCLUDE ---------------------------------------------------------

#include <comphelper/processfactory.hxx>
#include <comphelper/types.hxx>
#include <vcl/msgbox.hxx>
#include <tools/debug.hxx>
#include <bf_offmgr/sbaitems.hxx>	// SbaSelectionList
#include <bf_svx/dataaccessdescriptor.hxx>

#include <com/sun/star/sdb/CommandType.hpp>
#include <com/sun/star/sdb/XCompletedExecution.hpp>
#include <com/sun/star/sdbc/XRow.hpp>
#include <com/sun/star/sdbc/XRowSet.hpp>
#include <com/sun/star/sdbc/XResultSetMetaDataSupplier.hpp>
#include <com/sun/star/lang/XMultiServiceFactory.hpp>
#include <com/sun/star/beans/XPropertySet.hpp>
#include <com/sun/star/frame/XDispatchProvider.hpp>
#include <com/sun/star/frame/FrameSearchFlag.hpp>
#include <com/sun/star/view/XSelectionSupplier.hpp>


#include "dbdocfun.hxx"
#include "docsh.hxx"
#include "globstr.hrc"
#include "scerrors.hxx"
#include "dbcolect.hxx"
#include "markdata.hxx"
#include "undodat.hxx"
#include "progress.hxx"
#include "patattr.hxx"
#include "docpool.hxx"
#include "attrib.hxx"
#include "dbdocutl.hxx"
#include "editable.hxx"
#ifndef _LEGACYBINFILTERMGR_HXX
#include <legacysmgr/legacy_binfilters_smgr.hxx>	//STRIP002 
#endif
using namespace com::sun::star;

#define SC_SERVICE_ROWSET			"com.sun.star.sdb.RowSet"
#define SC_SERVICE_INTHANDLER		"com.sun.star.sdb.InteractionHandler"

//!	move to a header file?
#define SC_DBPROP_DATASOURCENAME	"DataSourceName"
#define SC_DBPROP_COMMAND			"Command"
#define SC_DBPROP_COMMANDTYPE		"CommandType"
#define SC_DBPROP_SELECTION			"Selection"
#define SC_DBPROP_CURSOR			"Cursor"

// -----------------------------------------------------------------

// static
//STRIP001 void ScDBDocFunc::ShowInBeamer( const ScImportParam& rParam, SfxViewFrame* pFrame )
//STRIP001 {
//STRIP001 	//	called after opening the database beamer
//STRIP001 
//STRIP001 	if ( !pFrame || !rParam.bImport )
//STRIP001 		return;
//STRIP001 
//STRIP001 	uno::Reference<frame::XFrame> xFrame = pFrame->GetFrame()->GetFrameInterface();
//STRIP001 	uno::Reference<frame::XDispatchProvider> xDP(xFrame, uno::UNO_QUERY);
//STRIP001 
//STRIP001 	uno::Reference<frame::XFrame> xBeamerFrame = xFrame->findFrame(
//STRIP001 										rtl::OUString::createFromAscii("_beamer"),
//STRIP001 										frame::FrameSearchFlag::CHILDREN);
//STRIP001 	if (xBeamerFrame.is())
//STRIP001 	{
//STRIP001 		uno::Reference<frame::XController> xController = xBeamerFrame->getController();
//STRIP001 		uno::Reference<view::XSelectionSupplier> xControllerSelection(xController, uno::UNO_QUERY);
//STRIP001 		if (xControllerSelection.is())
//STRIP001 		{
//STRIP001 			sal_Int32 nType = rParam.bSql ? sdb::CommandType::COMMAND :
//STRIP001 						( (rParam.nType == ScDbQuery) ? sdb::CommandType::QUERY :
//STRIP001 														sdb::CommandType::TABLE );
//STRIP001 
//STRIP001             ::svx::ODataAccessDescriptor aSelection;
//STRIP001             aSelection[svx::daDataSource]   <<= rtl::OUString( rParam.aDBName );
//STRIP001             aSelection[svx::daCommand]      <<= rtl::OUString( rParam.aStatement );
//STRIP001             aSelection[svx::daCommandType]  <<= nType;
//STRIP001 
//STRIP001 			xControllerSelection->select(uno::makeAny(aSelection.createPropertyValueSequence()));
//STRIP001 		}
//STRIP001 		else
//STRIP001 			DBG_ERROR("no selection supplier in the beamer!");
//STRIP001 	}
//STRIP001 }

// -----------------------------------------------------------------

/*M*/ BOOL ScDBDocFunc::DoImportUno( const ScAddress& rPos,
/*M*/ 								const uno::Sequence<beans::PropertyValue>& aArgs )
/*M*/ {
/*M*/ 	BOOL bDone = FALSE;
/*M*/ 
/*M*/ 	ScImportParam aImParam;
/*M*/ 	aImParam.nCol1 = aImParam.nCol2 = rPos.Col();
/*M*/ 	aImParam.nRow1 = aImParam.nRow2 = rPos.Row();
/*M*/ 	aImParam.bImport = TRUE;
/*M*/ 
/*M*/ 	uno::Reference<sdbc::XResultSet> xResSet;
/*M*/ 	uno::Sequence<uno::Any> aSelection;
/*M*/ 
/*M*/ 	rtl::OUString aStrVal;
/*M*/ 	const beans::PropertyValue* pPropArray = aArgs.getConstArray();
/*M*/ 	long nPropCount = aArgs.getLength();
/*M*/ 	long i;
/*M*/ 	for (i = 0; i < nPropCount; i++)
/*M*/ 	{
/*M*/ 		const beans::PropertyValue& rProp = pPropArray[i];
/*M*/ 		String aPropName = rProp.Name;
/*M*/ 
/*M*/ 		if ( aPropName.EqualsAscii( SC_DBPROP_DATASOURCENAME ))
/*M*/ 		{
/*M*/ 			if ( rProp.Value >>= aStrVal )
/*M*/ 				aImParam.aDBName = aStrVal;
/*M*/ 		}
/*M*/ 		else if ( aPropName.EqualsAscii( SC_DBPROP_COMMAND ))
/*M*/ 		{
/*M*/ 			if ( rProp.Value >>= aStrVal )
/*M*/ 				aImParam.aStatement = aStrVal;
/*M*/ 		}
/*M*/ 		else if ( aPropName.EqualsAscii( SC_DBPROP_COMMANDTYPE ))
/*M*/ 		{
/*M*/ 			sal_Int32 nType;
/*M*/ 			if ( rProp.Value >>= nType )
/*M*/ 			{
/*M*/ 				aImParam.bSql = ( nType == sdb::CommandType::COMMAND );
/*M*/ 				aImParam.nType = ( nType == sdb::CommandType::QUERY ) ? ScDbQuery : ScDbTable;
/*M*/ 				// nType is ignored if bSql is set
/*M*/ 			}
/*M*/ 		}
/*M*/ 		else if ( aPropName.EqualsAscii( SC_DBPROP_SELECTION ))
/*M*/ 		{
/*M*/ 			rProp.Value >>= aSelection;
/*M*/ 		}
/*M*/ 		else if ( aPropName.EqualsAscii( SC_DBPROP_CURSOR ))
/*M*/ 		{
/*M*/ 			rProp.Value >>= xResSet;
/*M*/ 		}
/*M*/ 	}
/*M*/ 
/*M*/ 	SbaSelectionList aList;
/*M*/ 	long nSelLen = aSelection.getLength();
/*M*/ 	for (i = 0; i < nSelLen; i++)
/*M*/ 	{
/*M*/ 		sal_Int32 nEntry;
/*M*/ 		if ( aSelection[i] >>= nEntry )
/*M*/ 			aList.Insert( (void*)nEntry, LIST_APPEND );
/*M*/ 	}
/*M*/ 
/*M*/ 	BOOL bAddrInsert = FALSE;		//!???
/*M*/ 	if ( bAddrInsert )
/*M*/ 	{
/*M*/ 		bDone = DoImport( rPos.Tab(), aImParam, xResSet, &aList, TRUE, bAddrInsert );
/*M*/ 	}
/*M*/ 	else
/*M*/ 	{
/*M*/ 		//	create database range
/*M*/ 		//!	merge this with SID_SBA_IMPORT execute in docsh4.cxx
/*M*/ 
/*M*/ 		ScDBData* pDBData = rDocShell.GetDBData( ScRange(rPos), SC_DB_IMPORT, FALSE );
/*M*/ 		DBG_ASSERT(pDBData, "can't create DB data");
/*M*/ 		String sTarget = pDBData->GetName();
/*M*/ 
/*M*/ 		//!	change UpdateImport to use only one of rTableName, rStatement
/*M*/ 
/*M*/ 		String aTableName, aStatement;
/*M*/ 		if ( aImParam.bSql )
/*M*/ 			aStatement = aImParam.aStatement;
/*M*/ 		else
/*M*/ 			aTableName = aImParam.aStatement;
/*M*/ 
/*M*/         UpdateImport( sTarget, aImParam.aDBName, aTableName, aStatement,
/*M*/                 aImParam.bNative, aImParam.nType, xResSet, &aList );
/*M*/ 		bDone = TRUE;
/*M*/ 	}
/*M*/ 
/*M*/ 	return bDone;
/*M*/ }

// -----------------------------------------------------------------

/*M*/ BOOL ScDBDocFunc::DoImport( USHORT nTab, const ScImportParam& rParam,
/*M*/         const uno::Reference< sdbc::XResultSet >& xResultSet,
/*M*/         const SbaSelectionList* pSelection, BOOL bRecord, BOOL bAddrInsert )
/*M*/ {
/*M*/ 	ScDocument* pDoc = rDocShell.GetDocument();
/*M*/ 
/*M*/ 	if (bRecord && !pDoc->IsUndoEnabled())
/*M*/ 		bRecord = FALSE;
/*M*/ 
/*M*/ 	ScDBData* pDBData = 0;
/*M*/ 	if ( !bAddrInsert )
/*M*/ 	{
/*M*/ 		pDBData = pDoc->GetDBAtArea( nTab, rParam.nCol1, rParam.nRow1,
/*M*/ 											rParam.nCol2, rParam.nRow2 );
/*M*/ 		if (!pDBData)
/*M*/ 		{
/*M*/ 			DBG_ERROR( "DoImport: no DBData" );
/*M*/ 			return FALSE;
/*M*/ 		}
/*M*/ 	}
/*M*/ 
/*M*/ 	Window* pWaitWin = rDocShell.GetDialogParent();
/*M*/ 	if (pWaitWin)
/*M*/ 		pWaitWin->EnterWait();
/*M*/ 	ScDocShellModificator aModificator( rDocShell );
/*M*/ 
/*M*/ 	BOOL bSuccess = FALSE;
/*M*/ 	BOOL bApi = FALSE;						//! pass as argument
/*M*/ 	BOOL bTruncated = FALSE;				// for warning
/*M*/ 	USHORT nErrStringId = 0;
/*M*/ 	String aErrorMessage;
/*M*/ 
/*M*/ 	USHORT nCol = rParam.nCol1;
/*M*/ 	USHORT nRow = rParam.nRow1;
/*M*/ 	USHORT nEndCol = nCol;					// end of resulting database area
/*M*/ 	USHORT nEndRow = nRow;
/*M*/ 	long i;
/*M*/ 
/*M*/ 	BOOL bDoSelection = FALSE;
/*M*/ 	BOOL bRealSelection = FALSE;			// TRUE if not everything is selected
/*M*/ 	ULONG nListPos = 0;
/*M*/ 	ULONG nRowsRead = 0;
/*M*/ 	ULONG nListCount = 0;
/*M*/ 
/*M*/ 	//	-1 is special
/*M*/ 	if ( pSelection && pSelection->Count() && (long)pSelection->GetObject(0) != -1L )
/*M*/ 	{
/*M*/ 		bDoSelection = TRUE;
/*M*/ 		nListCount = pSelection->Count();
/*M*/ 	}
/*M*/ 
/*M*/ 	// ImportDoc - also used for Redo
/*M*/ 	ScDocument* pImportDoc = new ScDocument( SCDOCMODE_UNDO );
/*M*/ 	pImportDoc->InitUndo( pDoc, nTab, nTab );
/*M*/ 	ScColumn::bDoubleAlloc = TRUE;
/*M*/ 
/*M*/ 	//
/*M*/ 	//	get data from database into import document
/*M*/ 	//
/*M*/ 
/*M*/ 	try
/*M*/ 	{
/*M*/ 		//	progress bar
/*M*/ 		//	only text (title is still needed, for the cancel button)
/*M*/ 		ScProgress aProgress( &rDocShell, ScGlobal::GetRscString(STR_UNDO_IMPORTDATA), 0 );
/*M*/ 		USHORT nInserted = 0;
/*M*/ 
/*M*/         uno::Reference<sdbc::XRowSet> xRowSet = uno::Reference<sdbc::XRowSet>(
/*M*/                 xResultSet, uno::UNO_QUERY );
/*M*/         sal_Bool bDispose = sal_False;
/*M*/         if ( !xRowSet.is() )
/*M*/         {
/*M*/             bDispose = sal_True;
/*M*/             xRowSet = uno::Reference<sdbc::XRowSet>(
/*M*/                     ::legacy_binfilters::getLegacyProcessServiceFactory()->createInstance(
/*M*/                         rtl::OUString::createFromAscii( SC_SERVICE_ROWSET ) ),
/*M*/                     uno::UNO_QUERY);
/*M*/             uno::Reference<beans::XPropertySet> xRowProp( xRowSet, uno::UNO_QUERY );
/*M*/             DBG_ASSERT( xRowProp.is(), "can't get RowSet" );
/*M*/             if ( xRowProp.is() )
/*M*/             {
/*M*/                 //
/*M*/                 //	set source parameters
/*M*/                 //
/*M*/ 
/*M*/                 sal_Int32 nType = rParam.bSql ? sdb::CommandType::COMMAND :
/*M*/                             ( (rParam.nType == ScDbQuery) ? sdb::CommandType::QUERY :
/*M*/                                                             sdb::CommandType::TABLE );
/*M*/                 uno::Any aAny;
/*M*/ 
/*M*/                 aAny <<= rtl::OUString( rParam.aDBName );
/*M*/                 xRowProp->setPropertyValue(
/*M*/                             rtl::OUString::createFromAscii(SC_DBPROP_DATASOURCENAME), aAny );
/*M*/ 
/*M*/                 aAny <<= rtl::OUString( rParam.aStatement );
/*M*/                 xRowProp->setPropertyValue(
/*M*/                             rtl::OUString::createFromAscii(SC_DBPROP_COMMAND), aAny );
/*M*/ 
/*M*/                 aAny <<= nType;
/*M*/                 xRowProp->setPropertyValue(
/*M*/                             rtl::OUString::createFromAscii(SC_DBPROP_COMMANDTYPE), aAny );
/*M*/ 
/*M*/                 uno::Reference<sdb::XCompletedExecution> xExecute( xRowSet, uno::UNO_QUERY );
/*M*/                 if ( xExecute.is() )
/*M*/                 {
/*M*/                     uno::Reference<task::XInteractionHandler> xHandler(
/*M*/                             ::legacy_binfilters::getLegacyProcessServiceFactory()->createInstance(
/*M*/                                 rtl::OUString::createFromAscii( SC_SERVICE_INTHANDLER ) ),
/*M*/                             uno::UNO_QUERY);
/*M*/                     xExecute->executeWithCompletion( xHandler );
/*M*/                 }
/*M*/                 else
/*M*/                     xRowSet->execute();
/*M*/             }
/*M*/         }
/*M*/         if ( xRowSet.is() )
/*M*/         {
/*M*/ 			//
/*M*/ 			//	get column descriptions
/*M*/ 			//
/*M*/ 
/*M*/ 			long nColCount = 0;
/*M*/ 			uno::Reference<sdbc::XResultSetMetaData> xMeta;
/*M*/ 			uno::Reference<sdbc::XResultSetMetaDataSupplier> xMetaSupp( xRowSet, uno::UNO_QUERY );
/*M*/ 			if ( xMetaSupp.is() )
/*M*/ 				xMeta = xMetaSupp->getMetaData();
/*M*/ 			if ( xMeta.is() )
/*M*/ 				nColCount = xMeta->getColumnCount();	// this is the number of real columns
/*M*/ 
/*M*/ 			if ( rParam.nCol1 + nColCount - 1 > MAXCOL )
/*M*/ 			{
/*M*/ 				nColCount = 0;
/*M*/ 				//!	error message
/*M*/ 			}
/*M*/ 
/*M*/ 			uno::Reference<sdbc::XRow> xRow( xRowSet, uno::UNO_QUERY );
/*M*/ 			if ( nColCount > 0 && xRow.is() )
/*M*/ 			{
/*M*/ 				nEndCol = (USHORT)( rParam.nCol1 + nColCount - 1 );
/*M*/ 
/*M*/ 				uno::Sequence<sal_Int32> aColTypes( nColCount );	// column types
/*M*/ 				uno::Sequence<sal_Bool> aColCurr( nColCount );		// currency flag is not in types
/*M*/ 				sal_Int32* pTypeArr = aColTypes.getArray();
/*M*/ 				sal_Bool* pCurrArr = aColCurr.getArray();
/*M*/ 				for (i=0; i<nColCount; i++)
/*M*/ 				{
/*M*/ 					pTypeArr[i] = xMeta->getColumnType( i+1 );
/*M*/ 					pCurrArr[i] = xMeta->isCurrency( i+1 );
/*M*/ 				}
/*M*/ 
/*M*/ 				if ( !bAddrInsert )					// read column names
/*M*/ 				{
/*M*/ 					nCol = rParam.nCol1;
/*M*/ 					for (i=0; i<nColCount; i++)
/*M*/ 					{
/*M*/ 						pImportDoc->SetString( nCol, nRow, nTab,
/*M*/ 												xMeta->getColumnLabel( i+1 ) );
/*M*/ 						++nCol;
/*M*/ 					}
/*M*/ 					++nRow;
/*M*/ 				}
/*M*/ 
/*M*/ 				BOOL bEnd = FALSE;
/*M*/                 xRowSet->beforeFirst();
/*M*/ 				while ( !bEnd && xRowSet->next() )
/*M*/ 				{
/*M*/ 					//	skip rows that are not selected
/*M*/ 
/*M*/ 					if (bDoSelection)
/*M*/ 					{
/*M*/ 						if (nListPos < nListCount)
/*M*/ 						{
/*M*/ 							ULONG nNextRow = (ULONG) pSelection->GetObject(nListPos);
/*M*/ 							while (nRowsRead+1 < nNextRow && !bEnd)
/*M*/ 							{
/*M*/ 								bRealSelection = TRUE;
/*M*/ 								if ( !xRowSet->next() )
/*M*/ 									bEnd = TRUE;
/*M*/ 								++nRowsRead;
/*M*/ 							}
/*M*/ 							++nListPos;
/*M*/ 						}
/*M*/ 						else
/*M*/ 						{
/*M*/ 							bRealSelection = TRUE;	// more data available but not used
/*M*/ 							bEnd = TRUE;
/*M*/ 						}
/*M*/ 					}
/*M*/ 
/*M*/ 					if ( !bEnd )
/*M*/ 					{
/*M*/ 						if ( nRow <= MAXROW )
/*M*/ 						{
/*M*/ 							nCol = rParam.nCol1;
/*M*/ 							for (i=0; i<nColCount; i++)
/*M*/ 							{
/*M*/ 								ScDatabaseDocUtil::PutData( pImportDoc, nCol, nRow, nTab,
/*M*/ 												xRow, i+1, pTypeArr[i], pCurrArr[i] );
/*M*/ 								++nCol;
/*M*/ 							}
/*M*/ 							nEndRow = nRow;
/*M*/ 							++nRow;
/*M*/ 
/*M*/ 							//	progress bar
/*M*/ 
/*M*/ 							++nInserted;
/*M*/ 							if (!(nInserted & 15))
/*M*/ 							{DBG_ASSERT(0, "STRIP"); //STRIP001 
//STRIP001 /*M*/ 								String aPict = ScGlobal::GetRscString( STR_PROGRESS_IMPORT );
//STRIP001 /*M*/ 								String aText = aPict.GetToken(0,'#');
//STRIP001 /*M*/ 								aText += String::CreateFromInt32( nInserted );
//STRIP001 /*M*/ 								aText += aPict.GetToken(1,'#');
//STRIP001 /*M*/ 
//STRIP001 /*M*/ 								if (!aProgress.SetStateText( 0, aText ))	// stopped by user?
//STRIP001 /*M*/ 								{
//STRIP001 /*M*/ 									bEnd = TRUE;
//STRIP001 /*M*/ 									bSuccess = FALSE;
//STRIP001 /*M*/ 									nErrStringId = STR_DATABASE_ABORTED;
//STRIP001 /*M*/ 								}
/*M*/ 							}
/*M*/ 						}
/*M*/ 						else		// past the end of the spreadsheet
/*M*/ 						{
/*M*/ 							bEnd = TRUE;			// don't continue
/*M*/ 							bTruncated = TRUE;		// warning flag
/*M*/ 						}
/*M*/ 					}
/*M*/ 
/*M*/ 					++nRowsRead;
/*M*/ 				}
/*M*/ 
/*M*/ 				bSuccess = TRUE;
/*M*/ 			}
/*M*/ 
/*M*/             if ( bDispose )
/*M*/                 ::comphelper::disposeComponent( xRowSet );
/*M*/ 		}
/*M*/ 	}
/*M*/ 	catch ( sdbc::SQLException& rError )
/*M*/ 	{
/*M*/ 		aErrorMessage = rError.Message;
/*M*/ 	}
/*M*/ 	catch ( uno::Exception& )
/*M*/ 	{
/*M*/ 		DBG_ERROR("Unexpected exception in database");
/*M*/ 	}
/*M*/ 
/*M*/ 	ScColumn::bDoubleAlloc = FALSE;
/*M*/ 	pImportDoc->DoColResize( nTab, rParam.nCol1,nEndCol, 0 );
/*M*/ 
/*M*/ 	//
/*M*/ 	//	test for cell protection
/*M*/ 	//
/*M*/ 
/*M*/ 	BOOL bKeepFormat = !bAddrInsert && pDBData->IsKeepFmt();
/*M*/ 	BOOL bMoveCells = !bAddrInsert && pDBData->IsDoSize();
/*M*/ 	USHORT nFormulaCols = 0;	// columns to be filled with formulas
/*M*/ 	if (bMoveCells && nEndCol == rParam.nCol2)
/*M*/ 	{
/*M*/ 		//	if column count changes, formulas would become invalid anyway
/*M*/ 		//	-> only set nFormulaCols for unchanged column count
/*M*/ 
/*M*/ 		USHORT nTestCol = rParam.nCol2 + 1;		// right of the data
/*M*/ 		USHORT nTestRow = rParam.nRow1 + 1;		// below the title row
/*M*/ 		while ( nTestCol <= MAXCOL &&
/*M*/ 				pDoc->GetCellType(ScAddress( nTestCol, nTestRow, nTab )) == CELLTYPE_FORMULA )
/*M*/ 			++nTestCol, ++nFormulaCols;
/*M*/ 	}
/*M*/ 
/*M*/ 	if (bSuccess)
/*M*/ 	{
/*M*/ 		//	old and new range editable?
/*N*/ 		ScEditableTester aTester;
/*N*/ 		aTester.TestBlock( pDoc, nTab, rParam.nCol1,rParam.nRow1,rParam.nCol2,rParam.nRow2 );
/*N*/ 		aTester.TestBlock( pDoc, nTab, rParam.nCol1,rParam.nRow1,nEndCol,nEndRow );
/*N*/ 		if ( !aTester.IsEditable() )
/*N*/ 		{
/*N*/ 			nErrStringId = aTester.GetMessageId();
/*N*/ 			bSuccess = FALSE;
/*N*/ 		}
/*N*/ 		else if ( pDoc->GetChangeTrack() != NULL )
/*M*/ 		{
/*M*/ 			nErrStringId = STR_PROTECTIONERR;
/*M*/ 			bSuccess = FALSE;
/*M*/ 		}
/*M*/ 	}
/*M*/ 
/*M*/ 	if ( bSuccess && bMoveCells )
/*M*/ 	{
/*M*/ 		ScRange aOld( rParam.nCol1, rParam.nRow1, nTab,
/*M*/ 						rParam.nCol2+nFormulaCols, rParam.nRow2, nTab );
/*M*/ 		ScRange aNew( rParam.nCol1, rParam.nRow1, nTab,
/*M*/ 						nEndCol+nFormulaCols, nEndRow, nTab );
/*M*/ 		if (!pDoc->CanFitBlock( aOld, aNew ))
/*M*/ 		{
/*M*/ 			nErrStringId = STR_MSSG_DOSUBTOTALS_2;		// can't insert cells
/*M*/ 			bSuccess = FALSE;
/*M*/ 		}
/*M*/ 	}
/*M*/ 
/*M*/ 	//
/*M*/ 	//	copy data from import doc into real document
/*M*/ 	//
/*M*/ 
/*M*/ 	if ( bSuccess )
/*M*/ 	{
/*M*/ 		if (bKeepFormat)
/*M*/ 		{
/*M*/ 			//	keep formatting of title and first data row from the document
/*M*/ 			//	CopyToDocument also copies styles, Apply... needs separate calls
/*M*/ 
/*M*/ 			USHORT nMinEndCol = Min( rParam.nCol2, nEndCol );	// not too much
/*M*/ 			nMinEndCol += nFormulaCols;							// only if column count unchanged
/*M*/ 			pImportDoc->DeleteAreaTab( 0,0, MAXCOL,MAXROW, nTab, IDF_ATTRIB );
/*M*/ 			pDoc->CopyToDocument( rParam.nCol1, rParam.nRow1, nTab,
/*M*/ 									nMinEndCol, rParam.nRow1, nTab,
/*M*/ 									IDF_ATTRIB, FALSE, pImportDoc );
/*M*/ 
/*M*/ 			USHORT nDataStartRow = rParam.nRow1+1;
/*M*/ 			for (USHORT nCopyCol=rParam.nCol1; nCopyCol<=nMinEndCol; nCopyCol++)
/*M*/ 			{
/*M*/ 				const ScPatternAttr* pSrcPattern = pDoc->GetPattern(
/*M*/ 													nCopyCol, nDataStartRow, nTab );
/*M*/ 				pImportDoc->ApplyPatternAreaTab( nCopyCol, nDataStartRow, nCopyCol, nEndRow,
/*M*/ 													nTab, *pSrcPattern );
/*M*/ 				const ScStyleSheet* pStyle = pSrcPattern->GetStyleSheet();
/*M*/ 				if (pStyle)
/*M*/ 					pImportDoc->ApplyStyleAreaTab( nCopyCol, nDataStartRow, nCopyCol, nEndRow,
/*M*/ 													nTab, *pStyle );
/*M*/ 			}
/*M*/ 		}
/*M*/ 
/*M*/ 		//	don't set cell protection attribute if table is protected
/*M*/ 		if (pDoc->IsTabProtected(nTab))
/*M*/ 		{
/*M*/ 			ScPatternAttr aPattern(pImportDoc->GetPool());
/*M*/ 			aPattern.GetItemSet().Put( ScProtectionAttr( FALSE,FALSE,FALSE,FALSE ) );
/*M*/ 			pImportDoc->ApplyPatternAreaTab( 0,0,MAXCOL,MAXROW, nTab, aPattern );
/*M*/ 		}
/*M*/ 
/*M*/ 		//
/*M*/ 		//	copy old data for undo
/*M*/ 		//
/*M*/ 
/*M*/ 		USHORT nUndoEndCol = Max( nEndCol, rParam.nCol2 );		// rParam = old end
/*M*/ 		USHORT nUndoEndRow = Max( nEndRow, rParam.nRow2 );
/*M*/ 
/*M*/ 		ScDocument* pUndoDoc = NULL;
/*M*/ 		ScDBData* pUndoDBData = NULL;
/*M*/ 		if ( bRecord )
/*M*/ 		{
/*M*/ 			pUndoDoc = new ScDocument( SCDOCMODE_UNDO );
/*M*/ 			pUndoDoc->InitUndo( pDoc, nTab, nTab );
/*M*/ 
/*M*/ 			if ( !bAddrInsert )
/*M*/ 				pUndoDBData = new ScDBData( *pDBData );
/*M*/ 		}
/*M*/ 
/*M*/ 		ScMarkData aNewMark;
/*M*/ 		aNewMark.SelectOneTable( nTab );
/*M*/ 
/*M*/ 		if (bRecord)
/*M*/ 		{
/*M*/ 			//	nFormulaCols is set only if column count is unchanged
/*M*/ 			pDoc->CopyToDocument( rParam.nCol1, rParam.nRow1, nTab,
/*M*/ 									nEndCol+nFormulaCols, nEndRow, nTab,
/*M*/ 									IDF_ALL, FALSE, pUndoDoc );
/*M*/ 			if ( rParam.nCol2 > nEndCol )
/*M*/ 				pDoc->CopyToDocument( nEndCol+1, rParam.nRow1, nTab,
/*M*/ 										nUndoEndCol, nUndoEndRow, nTab,
/*M*/ 										IDF_ALL, FALSE, pUndoDoc );
/*M*/ 			if ( rParam.nRow2 > nEndRow )
/*M*/ 				pDoc->CopyToDocument( rParam.nCol1, nEndRow+1, nTab,
/*M*/ 										nUndoEndCol+nFormulaCols, nUndoEndRow, nTab,
/*M*/ 										IDF_ALL, FALSE, pUndoDoc );
/*M*/ 		}
/*M*/ 
/*M*/ 		//
/*M*/ 		//	move new data
/*M*/ 		//
/*M*/ 
/*M*/ 		if (bMoveCells)
/*M*/ 		{
/*M*/ 			//	clear only the range without the formulas,
/*M*/ 			//	so the formula title and first row are preserved
/*M*/ 
/*M*/ 			ScRange aDelRange( rParam.nCol1, rParam.nRow1, nTab,
/*M*/ 								rParam.nCol2, rParam.nRow2, nTab );
/*M*/ 			pDoc->DeleteAreaTab( aDelRange, IDF_ALL );	// ohne die Formeln
/*M*/ 
/*M*/ 			ScRange aOld( rParam.nCol1, rParam.nRow1, nTab,
/*M*/ 							rParam.nCol2+nFormulaCols, rParam.nRow2, nTab );
/*M*/ 			ScRange aNew( rParam.nCol1, rParam.nRow1, nTab,
/*M*/ 							nEndCol+nFormulaCols, nEndRow, nTab );
/*M*/ 			pDoc->FitBlock( aOld, aNew, FALSE );		// Formeln nicht loeschen
/*M*/ 		}
/*M*/ 		else if ( nEndCol < rParam.nCol2 )		// DeleteArea calls PutInOrder
/*M*/ 			pDoc->DeleteArea( nEndCol+1, rParam.nRow1, rParam.nCol2, rParam.nRow2,
/*M*/ 								aNewMark, IDF_CONTENTS );
/*M*/ 
/*M*/ 		//	CopyToDocument doesn't remove contents
/*M*/ 		pDoc->DeleteAreaTab( rParam.nCol1, rParam.nRow1, nEndCol, nEndRow, nTab, IDF_CONTENTS );
/*M*/ 
/*M*/ 		//	#41216# remove each column from ImportDoc after copying to reduce memory usage
/*M*/ 		BOOL bOldAutoCalc = pDoc->GetAutoCalc();
/*M*/ 		pDoc->SetAutoCalc( FALSE );				// outside of the loop
/*M*/ 		for (USHORT nCopyCol = rParam.nCol1; nCopyCol <= nEndCol; nCopyCol++)
/*M*/ 		{
/*M*/ 			pImportDoc->CopyToDocument( nCopyCol, rParam.nRow1, nTab, nCopyCol, nEndRow, nTab,
/*M*/ 										IDF_ALL, FALSE, pDoc );
/*M*/ 			pImportDoc->DeleteAreaTab( nCopyCol, rParam.nRow1, nCopyCol, nEndRow, nTab, IDF_CONTENTS );
/*M*/ 			pImportDoc->DoColResize( nTab, nCopyCol, nCopyCol, 0 );
/*M*/ 		}
/*M*/ 		pDoc->SetAutoCalc( bOldAutoCalc );
/*M*/ 
/*M*/ 		if (nFormulaCols)				// copy formulas
/*M*/ 		{
/*M*/ 			if (bKeepFormat)			// formats for formulas
/*M*/ 				pImportDoc->CopyToDocument( nEndCol+1, rParam.nRow1, nTab,
/*M*/ 											nEndCol+nFormulaCols, nEndRow, nTab,
/*M*/ 											IDF_ATTRIB, FALSE, pDoc );
/*M*/ 			// fill formulas
/*M*/ 			ScMarkData aMark;
/*M*/ 			aMark.SelectOneTable(nTab);
/*M*/ 			pDoc->Fill( nEndCol+1, rParam.nRow1+1, nEndCol+nFormulaCols, rParam.nRow1+1,
/*M*/ 							aMark, nEndRow-rParam.nRow1-1, FILL_TO_BOTTOM, FILL_SIMPLE );
/*M*/ 		}
/*M*/ 
/*M*/ 		//	if new range is smaller, clear old contents
/*M*/ 
/*M*/ 		if (!bMoveCells)		// move has happened above
/*M*/ 		{
/*M*/ 			if ( rParam.nCol2 > nEndCol )
/*M*/ 				pDoc->DeleteArea( nEndCol+1, rParam.nRow1, rParam.nCol2, rParam.nRow2,
/*M*/ 									aNewMark, IDF_CONTENTS );
/*M*/ 			if ( rParam.nRow2 > nEndRow )
/*M*/ 				pDoc->DeleteArea( rParam.nCol1, nEndRow+1, rParam.nCol2, rParam.nRow2,
/*M*/ 									aNewMark, IDF_CONTENTS );
/*M*/ 		}
/*M*/ 
/*M*/ 		if( !bAddrInsert )		// update database range
/*M*/ 		{
/*M*/ 			DBG_ASSERT(0, "STRIP"); //STRIP001 pDBData->SetImportParam( rParam );
//STRIP001 /*M*/ 			pDBData->SetHeader( TRUE );
//STRIP001 /*M*/ 			pDBData->SetByRow( TRUE );
//STRIP001 /*M*/ 			pDBData->SetArea( nTab, rParam.nCol1,rParam.nRow1, nEndCol,nEndRow );
//STRIP001 /*M*/ 			pDBData->SetImportSelection( bRealSelection );
//STRIP001 /*M*/ 			pDoc->CompileDBFormula();
/*M*/ 		}
/*M*/ 
/*M*/ 		if (bRecord)
/*M*/ 		{
/*M*/ 			DBG_ASSERT(0, "STRIP"); //STRIP001 ScDocument* pRedoDoc = pImportDoc;
//STRIP001 /*M*/ 			pImportDoc = NULL;
//STRIP001 /*M*/ 
//STRIP001 /*M*/ 			if (nFormulaCols)						// include filled formulas for redo
//STRIP001 /*M*/ 				pDoc->CopyToDocument( rParam.nCol1, rParam.nRow1, nTab,
//STRIP001 /*M*/ 										nEndCol+nFormulaCols, nEndRow, nTab,
//STRIP001 /*M*/ 										IDF_ALL, FALSE, pRedoDoc );
//STRIP001 /*M*/ 
//STRIP001 /*M*/ 			ScDBData* pRedoDBData = pDBData ? new ScDBData( *pDBData ) : NULL;
//STRIP001 /*M*/ 
//STRIP001 /*M*/ 			rDocShell.GetUndoManager()->AddUndoAction(
//STRIP001 /*M*/ 				new ScUndoImportData( &rDocShell, nTab,
//STRIP001 /*M*/ 										rParam, nUndoEndCol, nUndoEndRow,
//STRIP001 /*M*/ 										nFormulaCols,
//STRIP001 /*M*/ 										pUndoDoc, pRedoDoc, pUndoDBData, pRedoDBData ) );
/*M*/ 		}
/*M*/ 
/*M*/ 		pDoc->SetDirty();
/*M*/ 		rDocShell.PostPaint( 0,0,nTab, MAXCOL,MAXROW,nTab, PAINT_GRID );
/*M*/ 		aModificator.SetDocumentModified();
/*M*/ 
/*M*/ 		if (pWaitWin)
/*M*/ 			pWaitWin->LeaveWait();
/*M*/ 
/*M*/ 		if ( bTruncated && !bApi )			// show warning
/*M*/ 			ErrorHandler::HandleError(SCWARN_IMPORT_RANGE_OVERFLOW);
/*M*/ 	}
/*M*/ 	else if ( !bApi )
/*M*/ 	{
/*M*/ 		if (pWaitWin)
/*M*/ 			pWaitWin->LeaveWait();
/*M*/ 
/*M*/ 		if (!aErrorMessage.Len())
/*M*/ 		{
/*M*/ 			if (!nErrStringId)
/*M*/ 				nErrStringId = STR_MSSG_IMPORTDATA_0;
/*M*/ 			aErrorMessage = ScGlobal::GetRscString( nErrStringId );
/*M*/ 		}
/*M*/ 		InfoBox aInfoBox( rDocShell.GetDialogParent(), aErrorMessage );
/*M*/ 		aInfoBox.Execute();
/*M*/ 	}
/*M*/ 
/*M*/ 	delete pImportDoc;
/*M*/ 
/*M*/ 	return bSuccess;
/*M*/ }




