/*************************************************************************
 *
 *  $RCSfile: sc_document.cxx,v $
 *
 *  $Revision: 1.6 $
 *
 *  last change: $Author: rt $ $Date: 2004-05-05 16:39:30 $
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
#include "core_pch.hxx"
#endif

#pragma hdrstop

// INCLUDE ---------------------------------------------------------------

#define _ZFORLIST_DECLARE_TABLE
#include "scitems.hxx"
#include <bf_svx/eeitem.hxx>
#define ITEMID_FIELD EE_FEATURE_FIELD

#include <bf_svx/boxitem.hxx>
#include <bf_svx/frmdiritem.hxx>
#include <bf_svx/pageitem.hxx>
#include <bf_svx/editeng.hxx>
#include <bf_sfx2/app.hxx>
#include <bf_sfx2/objsh.hxx>
#include <svtools/poolcach.hxx>
#include <svtools/saveopt.hxx>
#include <svtools/zforlist.hxx>
#include <unotools/charclass.hxx>
#ifndef _UNOTOOLS_TRANSLITERATIONWRAPPER_HXX
#include <unotools/transliterationwrapper.hxx>
#endif
#ifndef _TOOLS_TENCCVT_HXX
#include <tools/tenccvt.hxx>
#endif

#include "document.hxx"
#include "table.hxx"
#include "attrib.hxx"
#include "attarray.hxx"
#include "markarr.hxx"
#include "patattr.hxx"
#include "rangenam.hxx"
#include "poolhelp.hxx"
#include "docpool.hxx"
#include "stlpool.hxx"
#include "stlsheet.hxx"
#include "globstr.hrc"
#include "rechead.hxx"
#include "dbcolect.hxx"
#include "pivot.hxx"
#include "chartlis.hxx"
#include "rangelst.hxx"
#include "markdata.hxx"
#include "drwlayer.hxx"
#include "conditio.hxx"
#include "validat.hxx"
#include "prnsave.hxx"
#include "chgtrack.hxx"
#include "bf_sc.hrc"
#include "scresid.hxx"
#include "hints.hxx"
#include "detdata.hxx"
#include "cell.hxx"
#include "dpobject.hxx"
#include "indexmap.hxx"
#include "detfunc.hxx"		// for UpdateAllComments
#include "scmod.hxx"
#ifndef SC_DOCITER_HXX
#include "dociter.hxx"
#endif
#include "progress.hxx"
#ifndef __SGI_STL_SET
#include <set>
#endif
namespace binfilter {

/*N*/ struct ScDefaultAttr
/*N*/ {
/*N*/ 	const ScPatternAttr*	pAttr;
/*N*/ 	USHORT					nFirst;
/*N*/ 	USHORT					nCount;
/*N*/ 	ScDefaultAttr(const ScPatternAttr* pPatAttr) : pAttr(pPatAttr), nFirst(0), nCount(0) {}
/*N*/ };

/*N*/ struct ScLessDefaultAttr
/*N*/ {
/*N*/ 	sal_Bool operator() (const ScDefaultAttr& rValue1, const ScDefaultAttr& rValue2) const
/*N*/ 	{
/*N*/ 		return rValue1.pAttr < rValue2.pAttr;
/*N*/ 	}
/*N*/ };

/*N*/ typedef std::set<ScDefaultAttr, ScLessDefaultAttr>	ScDefaultAttrSet;

/*N*/ void ScDocument::MakeTable( USHORT nTab )
/*N*/ {
/*N*/ 	if ( nTab<=MAXTAB && !pTab[nTab] )
/*N*/ 	{
/*N*/ 		String aString = ScGlobal::GetRscString(STR_TABLE_DEF); //"Tabelle"
/*N*/ 		aString += String::CreateFromInt32(nTab+1);
/*N*/ 		CreateValidTabName( aString );	// keine doppelten
/*N*/ 
/*N*/ 		pTab[nTab] = new ScTable(this, nTab, aString);
/*N*/ 		++nMaxTableNumber;
/*N*/ 	}
/*N*/ }


/*N*/ BOOL ScDocument::HasTable( USHORT nTab ) const
/*N*/ {
/*N*/ 	if (VALIDTAB(nTab))
/*N*/ 		if (pTab[nTab])
/*N*/ 			return TRUE;
/*N*/ 
/*N*/ 	return FALSE;
/*N*/ }


/*N*/ BOOL ScDocument::GetName( USHORT nTab, String& rName ) const
/*N*/ {
/*N*/ 	if (VALIDTAB(nTab))
/*N*/ 		if (pTab[nTab])
/*N*/ 		{
/*N*/ 			pTab[nTab]->GetName( rName );
/*N*/ 			return TRUE;
/*N*/ 		}
/*N*/ 	rName.Erase();
/*N*/ 	return FALSE;
/*N*/ }


/*N*/ BOOL ScDocument::GetTable( const String& rName, USHORT& rTab ) const
/*N*/ {
/*N*/ 	String aUpperName = rName;
/*N*/ 	ScGlobal::pCharClass->toUpper(aUpperName);
/*N*/ 	String aCompName;
/*N*/ 
/*N*/ 	for (USHORT i=0; i<=MAXTAB; i++)
/*N*/ 		if (pTab[i])
/*N*/ 		{
/*N*/ 			pTab[i]->GetName( aCompName );
/*N*/ 			ScGlobal::pCharClass->toUpper(aCompName);
/*N*/ 			if (aUpperName == aCompName)
/*N*/ 			{
/*N*/ 				rTab = i;
/*N*/ 				return TRUE;
/*N*/ 			}
/*N*/ 		}
/*N*/ 	rTab = 0;
/*N*/ 	return FALSE;
/*N*/ }


/*N*/ BOOL ScDocument::ValidTabName( const String& rName ) const
/*N*/ {
    /*  If changed, ScfTools::ConvertToScSheetName (sc/source/filter/ftools/ftools.cxx)
        needs to be changed too. */
/*N*/ 	using namespace ::com::sun::star::i18n;
/*N*/ 	sal_Int32 nStartFlags = KParseTokens::ANY_LETTER_OR_NUMBER |
/*N*/ 		KParseTokens::ASC_UNDERSCORE;
/*N*/ 	sal_Int32 nContFlags = nStartFlags;
/*N*/ 	String aContChars( RTL_CONSTASCII_USTRINGPARAM(" ") );
/*N*/ 	ParseResult rRes = ScGlobal::pCharClass->parsePredefinedToken( KParseType::IDENTNAME, rName, 0,
/*N*/ 		nStartFlags, EMPTY_STRING, nContFlags, aContChars );
/*N*/ 	return (rRes.TokenType & KParseType::IDENTNAME) && rRes.EndPos == rName.Len();
/*N*/ }


/*N*/ BOOL ScDocument::ValidNewTabName( const String& rName ) const
/*N*/ {
/*N*/ 	BOOL bValid = ValidTabName(rName);
/*N*/ 	for (USHORT i=0; (i<=MAXTAB) && bValid; i++)
/*N*/ 		if (pTab[i])
/*N*/ 		{
/*N*/ 			String aOldName;
/*N*/ 			pTab[i]->GetName(aOldName);
/*N*/             bValid = !ScGlobal::pTransliteration->isEqual( rName, aOldName );
/*N*/ 		}
/*N*/ 	return bValid;
/*N*/ }


/*N*/ void ScDocument::CreateValidTabName(String& rName) const
/*N*/ {
/*N*/ 	if ( !ValidTabName(rName) )
/*N*/ 	{
/*?*/ 		// neu erzeugen
/*?*/ 
/*?*/ 		const String aStrTable( ScResId(SCSTR_TABLE) );
/*?*/ 		BOOL		 bOk   = FALSE;
/*?*/ 
/*?*/ 		//	vorneweg testen, ob der Prefix als gueltig erkannt wird
/*?*/ 		//	wenn nicht, nur doppelte vermeiden
/*?*/ 		BOOL bPrefix = ValidTabName( aStrTable );
/*?*/ 		DBG_ASSERT(bPrefix, "ungueltiger Tabellenname");
/*?*/ 		USHORT nDummy;
/*?*/ 
/*?*/ 		USHORT nLoops = 0;		// "zur Sicherheit"
/*?*/ 		for ( USHORT i = nMaxTableNumber+1; !bOk && nLoops <= MAXTAB; i++ )
/*?*/ 		{
/*?*/ 			rName  = aStrTable;
/*?*/ 			rName += String::CreateFromInt32(i);
/*?*/ 			if (bPrefix)
/*?*/ 				bOk = ValidNewTabName( rName );
/*?*/ 			else
/*?*/ 				bOk = !GetTable( rName, nDummy );
/*?*/ 			++nLoops;
/*?*/ 		}
/*?*/ 
/*?*/ 		DBG_ASSERT(bOk, "kein gueltiger Tabellenname gefunden");
/*?*/ 		if ( !bOk )
/*?*/ 			rName = aStrTable;
/*N*/ 	}
/*N*/ 	else
/*N*/ 	{
/*N*/ 		// uebergebenen Namen ueberpruefen
/*N*/ 
/*N*/ 		if ( !ValidNewTabName(rName) )
/*N*/ 		{
/*N*/ 			USHORT i = 1;
/*N*/ 			String aName;
/*N*/ 			do
/*N*/ 			{
/*N*/ 				i++;
/*N*/ 				aName = rName;
/*N*/ 				aName += '_';
/*N*/ 				aName += String::CreateFromInt32(i);
/*N*/ 			}
/*N*/ 			while (!ValidNewTabName(aName) && (i < MAXTAB+1));
/*N*/ 			rName = aName;
/*N*/ 		}
/*N*/ 	}
/*N*/ }


/*N*/ BOOL ScDocument::InsertTab( USHORT nPos, const String& rName,
/*N*/ 			BOOL bExternalDocument )
/*N*/ {
/*N*/ 	USHORT	nTabCount = GetTableCount();
/*N*/ 	BOOL	bValid = (nTabCount <= MAXTAB);
/*N*/ 	if ( !bExternalDocument )	// sonst rName == "'Doc'!Tab", vorher pruefen
/*N*/ 		bValid = (bValid && ValidNewTabName(rName));
/*N*/ 	if (bValid)
/*N*/ 	{
/*N*/ 		if (nPos == SC_TAB_APPEND || nPos == nTabCount)
/*N*/ 		{
/*?*/ 			pTab[nTabCount] = new ScTable(this, nTabCount, rName);
/*?*/ 			++nMaxTableNumber;
/*?*/ 			if ( bExternalDocument )
/*?*/ 				pTab[nTabCount]->SetVisible( FALSE );
/*N*/ 		}
/*N*/ 		else
/*N*/ 		{
/*N*/ 			if (VALIDTAB(nPos) && (nPos < nTabCount))
/*N*/ 			{
/*N*/ 				ScRange aRange( 0,0,nPos, MAXCOL,MAXROW,MAXTAB );
/*N*/ 				xColNameRanges->UpdateReference( URM_INSDEL, this, aRange, 0,0,1 );
/*N*/ 				xRowNameRanges->UpdateReference( URM_INSDEL, this, aRange, 0,0,1 );
/*N*/ 				pRangeName->UpdateTabRef( nPos, 1 );
/*N*/ 				pDBCollection->UpdateReference(
/*N*/ 									URM_INSDEL, 0,0,nPos, MAXCOL,MAXROW,MAXTAB, 0,0,1 );
/*N*/ 				if (pPivotCollection)
/*N*/ 					pPivotCollection->UpdateReference(
/*N*/ 									URM_INSDEL, 0,0,nPos, MAXCOL,MAXROW,MAXTAB, 0,0,1 );
/*N*/ 				if (pDPCollection)
/*?*/ 					pDPCollection->UpdateReference( URM_INSDEL, aRange, 0,0,1 );
/*N*/ 				if (pDetOpList)
/*?*/ 					{DBG_BF_ASSERT(0, "STRIP");} //STRIP001 pDetOpList->UpdateReference( this, URM_INSDEL, aRange, 0,0,1 );
/*N*/ 				UpdateChartRef( URM_INSDEL, 0,0,nPos, MAXCOL,MAXROW,MAXTAB, 0,0,1 );
/*N*/ 				UpdateRefAreaLinks( URM_INSDEL, aRange, 0,0,1 );
/*N*/ 				if ( pUnoBroadcaster )
/*N*/ 					pUnoBroadcaster->Broadcast( ScUpdateRefHint( URM_INSDEL, aRange, 0,0,1 ) );
/*N*/ 
/*N*/ 				USHORT i;
/*N*/ 				for (i = 0; i <= MAXTAB; i++)
/*N*/ 					if (pTab[i])
/*N*/ 						pTab[i]->UpdateInsertTab(nPos);
/*N*/ 				for (i = nTabCount; i > nPos; i--)
/*N*/ 					pTab[i] = pTab[i - 1];
/*N*/ 				pTab[nPos] = new ScTable(this, nPos, rName);
/*N*/ 				++nMaxTableNumber;
/*N*/ 				for (i = 0; i <= MAXTAB; i++)
/*N*/ 					if (pTab[i])
/*N*/ 						pTab[i]->UpdateCompile();
/*N*/ 				for (i = 0; i <= MAXTAB; i++)
/*N*/ 					if (pTab[i])
/*N*/ 						pTab[i]->StartAllListeners();
/*N*/ 
/*N*/ 				//	update conditional formats after table is inserted
/*N*/ 				if ( pCondFormList )
/*N*/ 					pCondFormList->UpdateReference( URM_INSDEL, aRange, 0,0,1 );
/*N*/ 				// #81844# sheet names of references are not valid until sheet is inserted
/*N*/ 				if ( pChartListenerCollection )
/*N*/ 					pChartListenerCollection->UpdateScheduledSeriesRanges();
/*N*/ 
/*N*/ 				SetDirty();
/*N*/ 				bValid = TRUE;
/*N*/ 			}
/*N*/ 			else
/*N*/ 				bValid = FALSE;
/*N*/ 		}
/*N*/ 	}
/*N*/ 	return bValid;
/*N*/ }


/*N*/ BOOL ScDocument::DeleteTab( USHORT nTab, ScDocument* pRefUndoDoc )
/*N*/ {
/*N*/ 	BOOL bValid = FALSE;
/*N*/ 	if (VALIDTAB(nTab))
/*N*/ 	{
/*N*/ 		if (pTab[nTab])
/*N*/ 		{
/*N*/ 			USHORT nTabCount = GetTableCount();
/*N*/ 			if (nTabCount > 1)
/*N*/ 			{
/*N*/ 				BOOL bOldAutoCalc = GetAutoCalc();
/*N*/ 				SetAutoCalc( FALSE );	// Mehrfachberechnungen vermeiden
/*N*/ 				ScRange aRange( 0, 0, nTab, MAXCOL, MAXROW, nTab );
/*N*/ 				DelBroadcastAreasInRange( aRange );
/*N*/ 
/*N*/ 				aRange.aEnd.SetTab( MAXTAB );
/*N*/ 				xColNameRanges->UpdateReference( URM_INSDEL, this, aRange, 0,0,-1 );
/*N*/ 				xRowNameRanges->UpdateReference( URM_INSDEL, this, aRange, 0,0,-1 );
/*N*/ 				pRangeName->UpdateTabRef( nTab, 2 );
/*N*/ 				pDBCollection->UpdateReference(
/*N*/ 									URM_INSDEL, 0,0,nTab, MAXCOL,MAXROW,MAXTAB, 0,0,-1 );
/*N*/ 				if (pPivotCollection)
/*N*/ 					pPivotCollection->UpdateReference(
/*N*/ 									URM_INSDEL, 0,0,nTab, MAXCOL,MAXROW,MAXTAB, 0,0,-1 );
/*N*/ 				if (pDPCollection)
/*N*/ 					pDPCollection->UpdateReference( URM_INSDEL, aRange, 0,0,-1 );
/*N*/ 				if (pDetOpList)
/*N*/ 					pDetOpList->UpdateReference( this, URM_INSDEL, aRange, 0,0,-1 );
/*N*/ 				UpdateChartRef( URM_INSDEL, 0,0,nTab, MAXCOL,MAXROW,MAXTAB, 0,0,-1 );
/*N*/ 				UpdateRefAreaLinks( URM_INSDEL, aRange, 0,0,-1 );
/*N*/ 				if ( pCondFormList )
/*N*/ 					pCondFormList->UpdateReference( URM_INSDEL, aRange, 0,0,-1 );
/*N*/ 				if ( pUnoBroadcaster )
/*N*/ 					pUnoBroadcaster->Broadcast( ScUpdateRefHint( URM_INSDEL, aRange, 0,0,-1 ) );
/*N*/ 
/*N*/ 				USHORT i;
/*N*/ 				for (i=0; i<=MAXTAB; i++)
/*N*/ 					if (pTab[i])
/*N*/ 						pTab[i]->UpdateDeleteTab(nTab,FALSE,
/*N*/ 									pRefUndoDoc ? pRefUndoDoc->pTab[i] : 0);
/*N*/ 				delete pTab[nTab];
/*N*/ 				for (i=nTab + 1; i < nTabCount; i++)
/*N*/ 					pTab[i - 1] = pTab[i];
/*N*/ 				pTab[nTabCount - 1] = NULL;
/*N*/ 				--nMaxTableNumber;
/*N*/ 				for (i = 0; i <= MAXTAB; i++)
/*N*/ 					if (pTab[i])
/*N*/ 						pTab[i]->UpdateCompile();
/*N*/ 				// Excel-Filter loescht einige Tables waehrend des Ladens,
/*N*/ 				// Listener werden erst nach dem Laden aufgesetzt
/*N*/ 				if ( !bInsertingFromOtherDoc )
/*N*/ 				{
/*N*/ 					for (i = 0; i <= MAXTAB; i++)
/*N*/ 						if (pTab[i])
/*N*/ 							pTab[i]->StartAllListeners();
/*N*/ 					SetDirty();
/*N*/ 				}
/*N*/ 				// #81844# sheet names of references are not valid until sheet is deleted
/*N*/ 				pChartListenerCollection->UpdateScheduledSeriesRanges();
/*N*/ 				SetAutoCalc( bOldAutoCalc );
/*N*/ 				bValid = TRUE;
/*N*/ 			}
/*N*/ 		}
/*N*/ 	}
/*N*/ 	return bValid;
/*N*/ }


/*N*/ BOOL ScDocument::RenameTab( USHORT nTab, const String& rName, BOOL bUpdateRef,
/*N*/ 		BOOL bExternalDocument )
/*N*/ {
/*N*/ 	BOOL	bValid = FALSE;
/*N*/ 	USHORT	i;
/*N*/ 	if VALIDTAB(nTab)
/*N*/ 		if (pTab[nTab])
/*N*/ 		{
/*N*/ 			if ( bExternalDocument )
/*N*/ 				bValid = TRUE;		// zusammengesetzter Name
/*N*/ 			else
/*N*/ 				bValid = ValidTabName(rName);
/*N*/ 			for (i=0; (i<=MAXTAB) && bValid; i++)
/*N*/ 				if (pTab[i] && (i != nTab))
/*N*/ 				{
/*N*/ 					String aOldName;
/*N*/ 					pTab[i]->GetName(aOldName);
/*N*/                     bValid = !ScGlobal::pTransliteration->isEqual( rName, aOldName );
/*N*/ 				}
/*N*/ 			if (bValid)
/*N*/ 			{
/*N*/ 				pTab[nTab]->SetName(rName);
/*N*/ 				if ( pChartListenerCollection )
/*N*/ 					pChartListenerCollection->UpdateSeriesRangesContainingTab( nTab );
/*N*/ 			}
/*N*/ 		}
/*N*/ 	return bValid;
/*N*/ }


/*N*/ void ScDocument::SetVisible( USHORT nTab, BOOL bVisible )
/*N*/ {
/*N*/ 	if (VALIDTAB(nTab))
/*N*/ 		if (pTab[nTab])
/*N*/ 			pTab[nTab]->SetVisible(bVisible);
/*N*/ }


/*N*/ BOOL ScDocument::IsVisible( USHORT nTab ) const
/*N*/ {
/*N*/ 	if (VALIDTAB(nTab))
/*N*/ 		if (pTab[nTab])
/*N*/ 			return pTab[nTab]->IsVisible();
/*N*/ 
/*N*/ 	return FALSE;
/*N*/ }

/* ----------------------------------------------------------------------------
    benutzten Bereich suchen:

    GetCellArea	 - nur Daten
    GetTableArea - Daten / Attribute
    GetPrintArea - beruecksichtigt auch Zeichenobjekte,
                    streicht Attribute bis ganz rechts / unten
---------------------------------------------------------------------------- */


/*N*/ BOOL ScDocument::GetCellArea( USHORT nTab, USHORT& rEndCol, USHORT& rEndRow ) const
/*N*/ {
/*N*/ 	if (VALIDTAB(nTab))
/*N*/ 		if (pTab[nTab])
/*N*/ 			return pTab[nTab]->GetCellArea( rEndCol, rEndRow );
/*N*/ 
/*N*/ 	rEndCol = 0;
/*N*/ 	rEndRow = 0;
/*N*/ 	return FALSE;
/*N*/ }


/*N*/ BOOL ScDocument::GetTableArea( USHORT nTab, USHORT& rEndCol, USHORT& rEndRow ) const
/*N*/ {
/*N*/ 	if (VALIDTAB(nTab))
/*N*/ 		if (pTab[nTab])
/*N*/ 			return pTab[nTab]->GetTableArea( rEndCol, rEndRow );
/*N*/ 
/*N*/ 	rEndCol = 0;
/*N*/ 	rEndRow = 0;
/*N*/ 	return FALSE;
/*N*/ }


//	zusammenhaengender Bereich

/*N*/ void ScDocument::GetDataArea( USHORT nTab, USHORT& rStartCol, USHORT& rStartRow,
/*N*/ 								USHORT& rEndCol, USHORT& rEndRow, BOOL bIncludeOld )
/*N*/ {
/*N*/ 	if (VALIDTAB(nTab))
/*N*/ 		if (pTab[nTab])
/*N*/ 			pTab[nTab]->GetDataArea( rStartCol, rStartRow, rEndCol, rEndRow, bIncludeOld );
/*N*/ }


//STRIP001 void ScDocument::LimitChartArea( USHORT nTab, USHORT& rStartCol, USHORT& rStartRow,
//STRIP001 									USHORT& rEndCol, USHORT& rEndRow )
//STRIP001 {
//STRIP001 	if (VALIDTAB(nTab))
//STRIP001 		if (pTab[nTab])
//STRIP001 			pTab[nTab]->LimitChartArea( rStartCol, rStartRow, rEndCol, rEndRow );
//STRIP001 }


//STRIP001 void ScDocument::LimitChartIfAll( ScRangeListRef& rRangeList )
//STRIP001 {
//STRIP001 	ScRangeListRef aNew = new ScRangeList;
//STRIP001 	if (rRangeList.Is())
//STRIP001 	{
//STRIP001 		ULONG nCount = rRangeList->Count();
//STRIP001 		for (ULONG i=0; i<nCount; i++)
//STRIP001 		{
//STRIP001 			ScRange aRange(*rRangeList->GetObject( i ));
//STRIP001 			if ( ( aRange.aStart.Col() == 0 && aRange.aEnd.Col() == MAXCOL ) ||
//STRIP001 				 ( aRange.aStart.Row() == 0 && aRange.aEnd.Row() == MAXROW ) )
//STRIP001 			{
//STRIP001 				USHORT nStartCol = aRange.aStart.Col();
//STRIP001 				USHORT nStartRow = aRange.aStart.Row();
//STRIP001 				USHORT nEndCol = aRange.aEnd.Col();
//STRIP001 				USHORT nEndRow = aRange.aEnd.Row();
//STRIP001 				USHORT nTab = aRange.aStart.Tab();
//STRIP001 				if (pTab[nTab])
//STRIP001 					pTab[nTab]->LimitChartArea(nStartCol, nStartRow, nEndCol, nEndRow);
//STRIP001 				aRange.aStart.SetCol( nStartCol );
//STRIP001 				aRange.aStart.SetRow( nStartRow );
//STRIP001 				aRange.aEnd.SetCol( nEndCol );
//STRIP001 				aRange.aEnd.SetRow( nEndRow );
//STRIP001 			}
//STRIP001 			aNew->Append(aRange);
//STRIP001 		}
//STRIP001 	}
//STRIP001 	else
//STRIP001 		DBG_ERROR("LimitChartIfAll: Ref==0");
//STRIP001 	rRangeList = aNew;
//STRIP001 }


/*N*/ BOOL ScDocument::CanInsertRow( const ScRange& rRange ) const
/*N*/ {
/*N*/ 	USHORT nStartCol = rRange.aStart.Col();
/*N*/ 	USHORT nStartRow = rRange.aStart.Row();
/*N*/ 	USHORT nStartTab = rRange.aStart.Tab();
/*N*/ 	USHORT nEndCol = rRange.aEnd.Col();
/*N*/ 	USHORT nEndRow = rRange.aEnd.Row();
/*N*/ 	USHORT nEndTab = rRange.aEnd.Tab();
/*N*/ 	PutInOrder( nStartCol, nEndCol );
/*N*/ 	PutInOrder( nStartRow, nEndRow );
/*N*/ 	PutInOrder( nStartTab, nEndTab );
/*N*/ 	USHORT nSize = nEndRow - nStartRow + 1;
/*N*/ 
/*N*/ 	BOOL bTest = TRUE;
/*N*/ 	for (USHORT i=nStartTab; i<=nEndTab && bTest; i++)
/*N*/ 		if (pTab[i])
/*N*/ 			bTest &= pTab[i]->TestInsertRow( nStartCol, nEndCol, nSize );
/*N*/ 
/*N*/ 	return bTest;
/*N*/ }


/*N*/ BOOL ScDocument::InsertRow( USHORT nStartCol, USHORT nStartTab,
/*N*/ 							USHORT nEndCol,   USHORT nEndTab,
/*N*/ 							USHORT nStartRow, USHORT nSize, ScDocument* pRefUndoDoc )
/*N*/ {
/*N*/ 	PutInOrder( nStartCol, nEndCol );
/*N*/ 	PutInOrder( nStartTab, nEndTab );
/*N*/ 
/*N*/ 	BOOL bTest = TRUE;
/*N*/ 	BOOL bRet = FALSE;
/*N*/ 	BOOL bOldAutoCalc = GetAutoCalc();
/*N*/ 	SetAutoCalc( FALSE );	// Mehrfachberechnungen vermeiden
/*N*/ 	USHORT i = 0;
/*N*/ 	for (i=nStartTab; i<=nEndTab && bTest; i++)
/*N*/ 		if (pTab[i])
/*N*/ 			bTest &= pTab[i]->TestInsertRow( nStartCol, nEndCol, nSize );
/*N*/ 	if (bTest)
/*N*/ 	{
/*N*/ 		// UpdateBroadcastAreas muss vor UpdateReference gerufen werden, damit nicht
/*N*/ 		// Eintraege verschoben werden, die erst bei UpdateReference neu erzeugt werden
/*N*/ 
/*N*/ 		UpdateBroadcastAreas( URM_INSDEL, ScRange(
/*N*/ 			ScAddress( nStartCol, nStartRow, nStartTab ),
/*N*/ 			ScAddress( nEndCol, MAXROW, nEndTab )), 0, nSize, 0 );
/*N*/ 		UpdateReference( URM_INSDEL, nStartCol, nStartRow, nStartTab,
/*N*/ 						 nEndCol, MAXROW, nEndTab,
/*N*/ 						 0, nSize, 0, pRefUndoDoc, FALSE );		// without drawing objects
/*N*/ 		for (i=nStartTab; i<=nEndTab; i++)
/*N*/ 			if (pTab[i])
/*N*/ 				pTab[i]->InsertRow( nStartCol, nEndCol, nStartRow, nSize );
/*N*/ 
/*N*/ 		//	#82991# UpdateRef for drawing layer must be after inserting,
/*N*/ 		//	when the new row heights are known.
/*N*/ 		for (i=nStartTab; i<=nEndTab; i++)
/*N*/ 			if (pTab[i])
/*N*/ 				pTab[i]->UpdateDrawRef( URM_INSDEL,
/*N*/ 							nStartCol, nStartRow, nStartTab, nEndCol, MAXROW, nEndTab,
/*N*/ 							0, nSize, 0 );
/*N*/ 
/*N*/ 		if ( pChangeTrack && pChangeTrack->IsInDeleteUndo() )
/*N*/ 		{	// durch Restaurierung von Referenzen auf geloeschte Bereiche ist
/*N*/ 			// ein neues Listening faellig, bisherige Listener wurden in
/*N*/ 			// FormulaCell UpdateReference abgehaengt
/*N*/ 			StartAllListeners();
/*N*/ 		}
/*N*/ 		else
/*N*/         {   // RelName listeners have been removed in UpdateReference
/*N*/ 			for (i=0; i<=MAXTAB; i++)
/*N*/ 				if (pTab[i])
/*N*/                     pTab[i]->StartNameListeners( TRUE );
/*N*/             // #69592# at least all cells using range names pointing relative
/*N*/             // to the moved range must recalculate
/*N*/ 			for (i=0; i<=MAXTAB; i++)
/*N*/ 				if (pTab[i])
/*N*/ 					pTab[i]->SetRelNameDirty();
/*N*/ 		}
/*N*/ 		bRet = TRUE;
/*N*/ 	}
/*N*/ 	SetAutoCalc( bOldAutoCalc );
/*N*/ 	if ( bRet )
/*N*/ 		pChartListenerCollection->UpdateDirtyCharts();
/*N*/ 	return bRet;
/*N*/ }


/*N*/ BOOL ScDocument::InsertRow( const ScRange& rRange, ScDocument* pRefUndoDoc )
/*N*/ {
/*N*/ 	return InsertRow( rRange.aStart.Col(), rRange.aStart.Tab(),
/*N*/ 					  rRange.aEnd.Col(),   rRange.aEnd.Tab(),
/*N*/ 					  rRange.aStart.Row(), rRange.aEnd.Row()-rRange.aStart.Row()+1,
/*N*/ 					  pRefUndoDoc );
/*N*/ }


/*N*/ void ScDocument::DeleteRow( USHORT nStartCol, USHORT nStartTab,
/*N*/ 							USHORT nEndCol,   USHORT nEndTab,
/*N*/ 							USHORT nStartRow, USHORT nSize,
/*N*/ 							ScDocument* pRefUndoDoc, BOOL* pUndoOutline )
/*N*/ {
/*N*/ 	PutInOrder( nStartCol, nEndCol );
/*N*/ 	PutInOrder( nStartTab, nEndTab );
/*N*/ 
/*N*/ 	BOOL bOldAutoCalc = GetAutoCalc();
/*N*/ 	SetAutoCalc( FALSE );	// Mehrfachberechnungen vermeiden
/*N*/ 
/*N*/ 	if ( nStartRow+nSize <= MAXROW )
/*N*/ 	{
/*N*/ 		DelBroadcastAreasInRange( ScRange(
/*N*/ 			ScAddress( nStartCol, nStartRow, nStartTab ),
/*N*/ 			ScAddress( nEndCol, nStartRow+nSize-1, nEndTab ) ) );
/*N*/ 		UpdateBroadcastAreas( URM_INSDEL, ScRange(
/*N*/ 			ScAddress( nStartCol, nStartRow+nSize, nStartTab ),
/*N*/ 			ScAddress( nEndCol, MAXROW, nEndTab )), 0, -(short) nSize, 0 );
/*N*/ 	}
/*N*/ 	else
/*N*/ 		DelBroadcastAreasInRange( ScRange(
/*N*/ 			ScAddress( nStartCol, nStartRow, nStartTab ),
/*N*/ 			ScAddress( nEndCol, MAXROW, nEndTab ) ) );
/*N*/ 
/*N*/ 	if ( nStartRow+nSize <= MAXROW )
/*N*/ 	{
/*N*/ 		UpdateReference( URM_INSDEL, nStartCol, nStartRow+nSize, nStartTab,
/*N*/ 						 nEndCol, MAXROW, nEndTab,
/*N*/ 						 0, -(short) nSize, 0, pRefUndoDoc );
/*N*/ 	}
/*N*/ 
/*N*/ 	if (pUndoOutline)
/*N*/ 		*pUndoOutline = FALSE;
/*N*/ 
/*N*/ 	USHORT i=0;
/*N*/ 	for (i=nStartTab; i<=nEndTab; i++)
/*N*/ 		if (pTab[i])
/*N*/ 			pTab[i]->DeleteRow( nStartCol, nEndCol, nStartRow, nSize, pUndoOutline );
/*N*/ 
/*N*/ 	if ( nStartRow+nSize <= MAXROW )
/*N*/     {   // Name listeners have been removed in UpdateReference
/*N*/ 		for (i=0; i<=MAXTAB; i++)
/*N*/ 			if (pTab[i])
/*N*/                 pTab[i]->StartNameListeners( FALSE );
/*N*/         // #69592# at least all cells using range names pointing relative to
/*N*/         // the moved range must recalculate
/*N*/ 		for (i=0; i<=MAXTAB; i++)
/*N*/ 			if (pTab[i])
/*N*/ 				pTab[i]->SetRelNameDirty();
/*N*/ 	}
/*N*/ 
/*N*/ 	SetAutoCalc( bOldAutoCalc );
/*N*/ 	pChartListenerCollection->UpdateDirtyCharts();
/*N*/ }


/*N*/ void ScDocument::DeleteRow( const ScRange& rRange, ScDocument* pRefUndoDoc, BOOL* pUndoOutline )
/*N*/ {
/*N*/ 	DeleteRow( rRange.aStart.Col(), rRange.aStart.Tab(),
/*N*/ 			   rRange.aEnd.Col(),   rRange.aEnd.Tab(),
/*N*/ 			   rRange.aStart.Row(), rRange.aEnd.Row()-rRange.aStart.Row()+1,
/*N*/ 			   pRefUndoDoc, pUndoOutline );
/*N*/ }


/*N*/ BOOL ScDocument::CanInsertCol( const ScRange& rRange ) const
/*N*/ {
/*N*/ 	USHORT nStartCol = rRange.aStart.Col();
/*N*/ 	USHORT nStartRow = rRange.aStart.Row();
/*N*/ 	USHORT nStartTab = rRange.aStart.Tab();
/*N*/ 	USHORT nEndCol = rRange.aEnd.Col();
/*N*/ 	USHORT nEndRow = rRange.aEnd.Row();
/*N*/ 	USHORT nEndTab = rRange.aEnd.Tab();
/*N*/ 	PutInOrder( nStartCol, nEndCol );
/*N*/ 	PutInOrder( nStartRow, nEndRow );
/*N*/ 	PutInOrder( nStartTab, nEndTab );
/*N*/ 	USHORT nSize = nEndCol - nStartCol + 1;
/*N*/ 
/*N*/ 	BOOL bTest = TRUE;
/*N*/ 	for (USHORT i=nStartTab; i<=nEndTab && bTest; i++)
/*N*/ 		if (pTab[i])
/*N*/ 			bTest &= pTab[i]->TestInsertCol( nStartRow, nEndRow, nSize );
/*N*/ 
/*N*/ 	return bTest;
/*N*/ }


/*N*/ BOOL ScDocument::InsertCol( USHORT nStartRow, USHORT nStartTab,
/*N*/ 							USHORT nEndRow,   USHORT nEndTab,
/*N*/ 							USHORT nStartCol, USHORT nSize, ScDocument* pRefUndoDoc )
/*N*/ {
/*N*/ 	PutInOrder( nStartRow, nEndRow );
/*N*/ 	PutInOrder( nStartTab, nEndTab );
/*N*/ 
/*N*/ 	BOOL bTest = TRUE;
/*N*/ 	BOOL bRet = FALSE;
/*N*/ 	BOOL bOldAutoCalc = GetAutoCalc();
/*N*/ 	SetAutoCalc( FALSE );	// Mehrfachberechnungen vermeiden
/*N*/ 	USHORT i=0;
/*N*/ 	for (i=nStartTab; i<=nEndTab && bTest; i++)
/*N*/ 		if (pTab[i])
/*N*/ 			bTest &= pTab[i]->TestInsertCol( nStartRow, nEndRow, nSize );
/*N*/ 	if (bTest)
/*N*/ 	{
/*N*/ 		UpdateBroadcastAreas( URM_INSDEL, ScRange(
/*N*/ 			ScAddress( nStartCol, nStartRow, nStartTab ),
/*N*/ 			ScAddress( MAXCOL, nEndRow, nEndTab )), nSize, 0, 0 );
/*N*/ 		UpdateReference( URM_INSDEL, nStartCol, nStartRow, nStartTab,
/*N*/ 						 MAXCOL, nEndRow, nEndTab,
/*N*/ 						 nSize, 0, 0, pRefUndoDoc );
/*N*/ 		for (i=nStartTab; i<=nEndTab; i++)
/*N*/ 			if (pTab[i])
/*N*/ 				pTab[i]->InsertCol( nStartCol, nStartRow, nEndRow, nSize );
/*N*/ 
/*N*/ 		if ( pChangeTrack && pChangeTrack->IsInDeleteUndo() )
/*N*/ 		{	// durch Restaurierung von Referenzen auf geloeschte Bereiche ist
/*N*/ 			// ein neues Listening faellig, bisherige Listener wurden in
/*N*/ 			// FormulaCell UpdateReference abgehaengt
/*N*/ 			StartAllListeners();
/*N*/ 		}
/*N*/ 		else
/*N*/         {   // RelName listeners have been removed in UpdateReference
/*N*/ 			for (i=0; i<=MAXTAB; i++)
/*N*/ 				if (pTab[i])
/*N*/                     pTab[i]->StartNameListeners( TRUE );
/*N*/             // #69592# at least all cells using range names pointing relative
/*N*/             // to the moved range must recalculate
/*N*/ 			for (i=0; i<=MAXTAB; i++)
/*N*/ 				if (pTab[i])
/*N*/ 					pTab[i]->SetRelNameDirty();
/*N*/ 		}
/*N*/ 		bRet = TRUE;
/*N*/ 	}
/*N*/ 	SetAutoCalc( bOldAutoCalc );
/*N*/ 	if ( bRet )
/*N*/ 		pChartListenerCollection->UpdateDirtyCharts();
/*N*/ 	return bRet;
/*N*/ }


/*N*/ BOOL ScDocument::InsertCol( const ScRange& rRange, ScDocument* pRefUndoDoc )
/*N*/ {
/*N*/ 	return InsertCol( rRange.aStart.Row(), rRange.aStart.Tab(),
/*N*/ 					  rRange.aEnd.Row(),   rRange.aEnd.Tab(),
/*N*/ 					  rRange.aStart.Col(), rRange.aEnd.Col()-rRange.aStart.Col()+1,
/*N*/ 					  pRefUndoDoc );
/*N*/ }


/*N*/ void ScDocument::DeleteCol(USHORT nStartRow, USHORT nStartTab, USHORT nEndRow, USHORT nEndTab,
/*N*/ 								USHORT nStartCol, USHORT nSize, ScDocument* pRefUndoDoc,
/*N*/ 								BOOL* pUndoOutline )
/*N*/ {
/*N*/ 	PutInOrder( nStartRow, nEndRow );
/*N*/ 	PutInOrder( nStartTab, nEndTab );
/*N*/ 
/*N*/ 	BOOL bOldAutoCalc = GetAutoCalc();
/*N*/ 	SetAutoCalc( FALSE );	// Mehrfachberechnungen vermeiden
/*N*/ 
/*N*/ 	if ( nStartCol+nSize <= MAXCOL )
/*N*/ 	{
/*N*/ 		DelBroadcastAreasInRange( ScRange(
/*N*/ 			ScAddress( nStartCol, nStartRow, nStartTab ),
/*N*/ 			ScAddress( nStartCol+nSize-1, nEndRow, nEndTab ) ) );
/*N*/ 		UpdateBroadcastAreas( URM_INSDEL, ScRange(
/*N*/ 			ScAddress( nStartCol+nSize, nStartRow, nStartTab ),
/*N*/ 			ScAddress( MAXCOL, nEndRow, nEndTab )), -(short) nSize, 0, 0 );
/*N*/ 	}
/*N*/ 	else
/*N*/ 		DelBroadcastAreasInRange( ScRange(
/*N*/ 			ScAddress( nStartCol, nStartRow, nStartTab ),
/*N*/ 			ScAddress( MAXCOL, nEndRow, nEndTab ) ) );
/*N*/ 
/*N*/ 	if ( nStartCol+nSize <= MAXCOL )
/*N*/ 	{
/*N*/ 		UpdateReference( URM_INSDEL, nStartCol+nSize, nStartRow, nStartTab,
/*N*/ 						 MAXCOL, nEndRow, nEndTab,
/*N*/ 						 -(short) nSize, 0, 0, pRefUndoDoc );
/*N*/ 	}
/*N*/ 
/*N*/ 	if (pUndoOutline)
/*N*/ 		*pUndoOutline = FALSE;
/*N*/ 
/*N*/ 	USHORT i=0;
/*N*/ 	for (i=nStartTab; i<=nEndTab; i++)
/*N*/ 		if (pTab[i])
/*N*/ 			pTab[i]->DeleteCol( nStartCol, nStartRow, nEndRow, nSize, pUndoOutline );
/*N*/ 
/*N*/ 	if ( nStartCol+nSize <= MAXCOL )
/*N*/     {   // Name listeners have been removed in UpdateReference
/*N*/ 		for (i=0; i<=MAXTAB; i++)
/*N*/ 			if (pTab[i])
/*N*/                 pTab[i]->StartNameListeners( FALSE );
/*N*/         // #69592# at least all cells using range names pointing relative to
/*N*/         // the moved range must recalculate
/*N*/ 		for (i=0; i<=MAXTAB; i++)
/*N*/ 			if (pTab[i])
/*N*/ 				pTab[i]->SetRelNameDirty();
/*N*/ 	}
/*N*/ 
/*N*/ 	SetAutoCalc( bOldAutoCalc );
/*N*/ 	pChartListenerCollection->UpdateDirtyCharts();
/*N*/ }


/*N*/ void ScDocument::DeleteCol( const ScRange& rRange, ScDocument* pRefUndoDoc, BOOL* pUndoOutline )
/*N*/ {
/*N*/ 	DeleteCol( rRange.aStart.Row(), rRange.aStart.Tab(),
/*N*/ 			   rRange.aEnd.Row(),   rRange.aEnd.Tab(),
/*N*/ 			   rRange.aStart.Col(), rRange.aEnd.Col()-rRange.aStart.Col()+1,
/*N*/ 			   pRefUndoDoc, pUndoOutline );
/*N*/ }


//	fuer Area-Links: Zellen einuegen/loeschen, wenn sich der Bereich veraendert
//	(ohne Paint)


//STRIP001 void lcl_GetInsDelRanges( const ScRange& rOld, const ScRange& rNew,
//STRIP001 							ScRange& rColRange, BOOL& rInsCol, BOOL& rDelCol,
//STRIP001 							ScRange& rRowRange, BOOL& rInsRow, BOOL& rDelRow )
//STRIP001 {
//STRIP001 	DBG_ASSERT( rOld.aStart == rNew.aStart, "FitBlock: Anfang unterschiedlich" );
//STRIP001 
//STRIP001 	rInsCol = rDelCol = rInsRow = rDelRow = FALSE;
//STRIP001 
//STRIP001 	USHORT nStartX = rOld.aStart.Col();
//STRIP001 	USHORT nStartY = rOld.aStart.Row();
//STRIP001 	USHORT nOldEndX = rOld.aEnd.Col();
//STRIP001 	USHORT nOldEndY = rOld.aEnd.Row();
//STRIP001 	USHORT nNewEndX = rNew.aEnd.Col();
//STRIP001 	USHORT nNewEndY = rNew.aEnd.Row();
//STRIP001 	USHORT nTab = rOld.aStart.Tab();
//STRIP001 
//STRIP001 	//	wenn es mehr Zeilen werden, werden Spalten auf der alten Hoehe eingefuegt/geloescht
//STRIP001 	BOOL bGrowY = ( nNewEndY > nOldEndY );
//STRIP001 	USHORT nColEndY = bGrowY ? nOldEndY : nNewEndY;
//STRIP001 	USHORT nRowEndX = bGrowY ? nNewEndX : nOldEndX;
//STRIP001 
//STRIP001 	//	Spalten
//STRIP001 
//STRIP001 	if ( nNewEndX > nOldEndX )			// Spalten einfuegen
//STRIP001 	{
//STRIP001 		rColRange = ScRange( nOldEndX+1, nStartY, nTab, nNewEndX, nColEndY, nTab );
//STRIP001 		rInsCol = TRUE;
//STRIP001 	}
//STRIP001 	else if ( nNewEndX < nOldEndX )		// Spalten loeschen
//STRIP001 	{
//STRIP001 		rColRange = ScRange( nNewEndX+1, nStartY, nTab, nOldEndX, nColEndY, nTab );
//STRIP001 		rDelCol = TRUE;
//STRIP001 	}
//STRIP001 
//STRIP001 	//	Zeilen
//STRIP001 
//STRIP001 	if ( nNewEndY > nOldEndY )			// Zeilen einfuegen
//STRIP001 	{
//STRIP001 		rRowRange = ScRange( nStartX, nOldEndY+1, nTab, nRowEndX, nNewEndY, nTab );
//STRIP001 		rInsRow = TRUE;
//STRIP001 	}
//STRIP001 	else if ( nNewEndY < nOldEndY )		// Zeilen loeschen
//STRIP001 	{
//STRIP001 		rRowRange = ScRange( nStartX, nNewEndY+1, nTab, nRowEndX, nOldEndY, nTab );
//STRIP001 		rDelRow = TRUE;
//STRIP001 	}
//STRIP001 }


//STRIP001 BOOL ScDocument::HasPartOfMerged( const ScRange& rRange )
//STRIP001 {
//STRIP001 	BOOL bPart = FALSE;
//STRIP001 	USHORT nTab = rRange.aStart.Tab();
//STRIP001 
//STRIP001 	USHORT nStartX = rRange.aStart.Col();
//STRIP001 	USHORT nStartY = rRange.aStart.Row();
//STRIP001 	USHORT nEndX = rRange.aEnd.Col();
//STRIP001 	USHORT nEndY = rRange.aEnd.Row();
//STRIP001 
//STRIP001 	if (HasAttrib( nStartX, nStartY, nTab, nEndX, nEndY, nTab,
//STRIP001 						HASATTR_MERGED | HASATTR_OVERLAPPED ))
//STRIP001 	{
//STRIP001 		ExtendMerge( nStartX, nStartY, nEndX, nEndY, nTab );
//STRIP001 		ExtendOverlapped( nStartX, nStartY, nEndX, nEndY, nTab );
//STRIP001 
//STRIP001 		bPart = ( nStartX != rRange.aStart.Col() || nEndX != rRange.aEnd.Col() ||
//STRIP001 				  nStartY != rRange.aStart.Row() || nEndY != rRange.aEnd.Row() );
//STRIP001 	}
//STRIP001 	return bPart;
//STRIP001 }


/*N*/ BOOL ScDocument::CanFitBlock( const ScRange& rOld, const ScRange& rNew )
/*N*/ {
/*?*/ 	DBG_BF_ASSERT(0, "STRIP"); return FALSE; //STRIP001 if ( rOld == rNew )
//STRIP001 /*?*/ 		return TRUE;
//STRIP001 /*?*/ 
//STRIP001 /*?*/ 	USHORT nTab = rOld.aStart.Tab();
//STRIP001 /*?*/ 	BOOL bOk = TRUE;
//STRIP001 /*?*/ 	BOOL bInsCol,bDelCol,bInsRow,bDelRow;
//STRIP001 /*?*/ 	ScRange aColRange,aRowRange;
//STRIP001 /*?*/ 	lcl_GetInsDelRanges( rOld, rNew, aColRange,bInsCol,bDelCol, aRowRange,bInsRow,bDelRow );
//STRIP001 /*?*/ 
//STRIP001 /*?*/ 	if ( bInsCol && !CanInsertCol( aColRange ) )			// Zellen am Rand ?
//STRIP001 /*?*/ 		bOk = FALSE;
//STRIP001 /*?*/ 	if ( bInsRow && !CanInsertRow( aRowRange ) )			// Zellen am Rand ?
//STRIP001 /*?*/ 		bOk = FALSE;
//STRIP001 /*?*/ 
//STRIP001 /*?*/ 	if ( bInsCol || bDelCol )
//STRIP001 /*?*/ 	{
//STRIP001 /*?*/ 		aColRange.aEnd.SetCol(MAXCOL);
//STRIP001 /*?*/ 		if ( HasPartOfMerged(aColRange) )
//STRIP001 /*?*/ 			bOk = FALSE;
//STRIP001 /*?*/ 	}
//STRIP001 /*?*/ 	if ( bInsRow || bDelRow )
//STRIP001 /*?*/ 	{
//STRIP001 /*?*/ 		aRowRange.aEnd.SetRow(MAXROW);
//STRIP001 /*?*/ 		if ( HasPartOfMerged(aRowRange) )
//STRIP001 /*?*/ 			bOk = FALSE;
//STRIP001 /*?*/ 	}
//STRIP001 /*?*/ 
//STRIP001 /*?*/ 	return bOk;
/*N*/ }


/*N*/ void ScDocument::FitBlock( const ScRange& rOld, const ScRange& rNew, BOOL bClear )
/*N*/ {
/*?*/ 	DBG_BF_ASSERT(0, "STRIP"); //STRIP001 if (bClear)
//STRIP001 /*?*/ 		DeleteAreaTab( rOld, IDF_ALL );
//STRIP001 /*?*/ 
//STRIP001 /*?*/ 	BOOL bInsCol,bDelCol,bInsRow,bDelRow;
//STRIP001 /*?*/ 	ScRange aColRange,aRowRange;
//STRIP001 /*?*/ 	lcl_GetInsDelRanges( rOld, rNew, aColRange,bInsCol,bDelCol, aRowRange,bInsRow,bDelRow );
//STRIP001 /*?*/ 
//STRIP001 /*?*/ 	if ( bInsCol )
//STRIP001 /*?*/ 		InsertCol( aColRange );			// Spalten zuerst einfuegen
//STRIP001 /*?*/ 	if ( bInsRow )
//STRIP001 /*?*/ 		InsertRow( aRowRange );
//STRIP001 /*?*/ 
//STRIP001 /*?*/ 	if ( bDelRow )
//STRIP001 /*?*/ 		DeleteRow( aRowRange );			// Zeilen zuerst loeschen
//STRIP001 /*?*/ 	if ( bDelCol )
//STRIP001 /*?*/ 		DeleteCol( aColRange );
//STRIP001 /*?*/ 
//STRIP001 /*?*/ 	//	Referenzen um eingefuegte Zeilen erweitern
//STRIP001 /*?*/ 
//STRIP001 /*?*/ 	if ( bInsCol || bInsRow )
//STRIP001 /*?*/ 	{
//STRIP001 /*?*/ 		ScRange aGrowSource = rOld;
//STRIP001 /*?*/ 		aGrowSource.aEnd.SetCol(Min( rOld.aEnd.Col(), rNew.aEnd.Col() ));
//STRIP001 /*?*/ 		aGrowSource.aEnd.SetRow(Min( rOld.aEnd.Row(), rNew.aEnd.Row() ));
//STRIP001 /*?*/ 		USHORT nGrowX = bInsCol ? ( rNew.aEnd.Col() - rOld.aEnd.Col() ) : 0;
//STRIP001 /*?*/ 		USHORT nGrowY = bInsRow ? ( rNew.aEnd.Row() - rOld.aEnd.Row() ) : 0;
//STRIP001 /*?*/ 		UpdateGrow( aGrowSource, nGrowX, nGrowY );
//STRIP001 /*?*/ 	}
/*N*/ }


/*N*/ void ScDocument::DeleteArea(USHORT nCol1, USHORT nRow1,
/*N*/ 							USHORT nCol2, USHORT nRow2,
/*N*/ 							const ScMarkData& rMark, USHORT nDelFlag)
/*N*/ {
/*N*/ 	PutInOrder( nCol1, nCol2 );
/*N*/ 	PutInOrder( nRow1, nRow2 );
/*N*/ 	BOOL bOldAutoCalc = GetAutoCalc();
/*N*/ 	SetAutoCalc( FALSE );	// Mehrfachberechnungen vermeiden
/*N*/ 	for (USHORT i = 0; i <= MAXTAB; i++)
/*N*/ 		if (pTab[i])
/*N*/ 			if ( rMark.GetTableSelect(i) || bIsUndo )
/*N*/ 				pTab[i]->DeleteArea(nCol1, nRow1, nCol2, nRow2, nDelFlag);
/*N*/ 	SetAutoCalc( bOldAutoCalc );
/*N*/ }


/*N*/ void ScDocument::DeleteAreaTab(USHORT nCol1, USHORT nRow1,
/*N*/ 								USHORT nCol2, USHORT nRow2,
/*N*/ 								USHORT nTab, USHORT nDelFlag)
/*N*/ {
/*N*/ 	PutInOrder( nCol1, nCol2 );
/*N*/ 	PutInOrder( nRow1, nRow2 );
/*N*/ 	if ( VALIDTAB(nTab) && pTab[nTab] )
/*N*/ 	{
/*N*/ 		BOOL bOldAutoCalc = GetAutoCalc();
/*N*/ 		SetAutoCalc( FALSE );	// Mehrfachberechnungen vermeiden
/*N*/ 		pTab[nTab]->DeleteArea(nCol1, nRow1, nCol2, nRow2, nDelFlag);
/*N*/ 		SetAutoCalc( bOldAutoCalc );
/*N*/ 	}
/*N*/ }


/*N*/ void ScDocument::DeleteAreaTab( const ScRange& rRange, USHORT nDelFlag )
/*N*/ {
/*N*/ 	for ( USHORT nTab = rRange.aStart.Tab(); nTab <= rRange.aEnd.Tab(); nTab++ )
/*N*/ 		DeleteAreaTab( rRange.aStart.Col(), rRange.aStart.Row(),
/*N*/ 					   rRange.aEnd.Col(),   rRange.aEnd.Row(),
/*N*/ 					   nTab, nDelFlag );
/*N*/ }


/*N*/ void ScDocument::InitUndo( ScDocument* pSrcDoc, USHORT nTab1, USHORT nTab2,
/*N*/ 								BOOL bColInfo, BOOL bRowInfo )
/*N*/ {
/*N*/ 	if (bIsUndo)
/*N*/ 	{
/*N*/ 		Clear();
/*N*/ 
/*N*/ 		xPoolHelper = pSrcDoc->xPoolHelper;
/*N*/ 
/*N*/ 		String aString;
/*N*/ 		for (USHORT nTab = nTab1; nTab <= nTab2; nTab++)
/*N*/ 			pTab[nTab] = new ScTable(this, nTab, aString, bColInfo, bRowInfo);
/*N*/ 
/*N*/ 		nMaxTableNumber = nTab2 + 1;
/*N*/ 	}
/*N*/ 	else
/*N*/ 		DBG_ERROR("InitUndo");
/*N*/ }


/*N*/ void ScDocument::AddUndoTab( USHORT nTab1, USHORT nTab2, BOOL bColInfo, BOOL bRowInfo )
/*N*/ {
/*N*/ 	if (bIsUndo)
/*N*/ 	{
/*N*/ 		String aString;
/*N*/ 		for (USHORT nTab = nTab1; nTab <= nTab2; nTab++)
/*N*/ 			if (!pTab[nTab])
/*N*/ 				pTab[nTab] = new ScTable(this, nTab, aString, bColInfo, bRowInfo);
/*N*/ 
/*N*/ 		if ( nMaxTableNumber <= nTab2 )
/*N*/ 			nMaxTableNumber = nTab2 + 1;
/*N*/ 	}
/*N*/ 	else
/*N*/ 		DBG_ERROR("InitUndo");
/*N*/ }


//STRIP001 void ScDocument::SetCutMode( BOOL bVal )
//STRIP001 {
//STRIP001 	if (bIsClip)
//STRIP001 		bCutMode = bVal;
//STRIP001 	else
//STRIP001 	{
//STRIP001 		DBG_ERROR("SetCutMode without bIsClip");
//STRIP001 	}
//STRIP001 }


//STRIP001 BOOL ScDocument::IsCutMode()
//STRIP001 {
//STRIP001 	if (bIsClip)
//STRIP001 		return bCutMode;
//STRIP001 	else
//STRIP001 	{
//STRIP001 		DBG_ERROR("IsCutMode ohne bIsClip");
//STRIP001 		return FALSE;
//STRIP001 	}
//STRIP001 }


/*N*/ void ScDocument::CopyToDocument(USHORT nCol1, USHORT nRow1, USHORT nTab1,
/*N*/ 							USHORT nCol2, USHORT nRow2, USHORT nTab2,
/*N*/ 							USHORT nFlags, BOOL bOnlyMarked, ScDocument* pDestDoc,
/*N*/ 							const ScMarkData* pMarks, BOOL bColRowFlags )
/*N*/ {
/*N*/ 	PutInOrder( nCol1, nCol2 );
/*N*/ 	PutInOrder( nRow1, nRow2 );
/*N*/ 	PutInOrder( nTab1, nTab2 );
/*N*/ 	if( !pDestDoc->aDocName.Len() )
/*N*/ 		pDestDoc->aDocName = aDocName;
/*N*/ 	if (VALIDTAB(nTab1) && VALIDTAB(nTab2))
/*N*/ 	{
/*N*/ 		BOOL bOldAutoCalc = pDestDoc->GetAutoCalc();
/*N*/ 		pDestDoc->SetAutoCalc( FALSE );		// Mehrfachberechnungen vermeiden
/*N*/ 		for (USHORT i = nTab1; i <= nTab2; i++)
/*N*/ 		{
/*N*/ 			if (pTab[i] && pDestDoc->pTab[i])
/*N*/ 				pTab[i]->CopyToTable( nCol1, nRow1, nCol2, nRow2, nFlags,
/*N*/ 									  bOnlyMarked, pDestDoc->pTab[i], pMarks,
/*N*/ 									  FALSE, bColRowFlags );
/*N*/ 		}
/*N*/ 		pDestDoc->SetAutoCalc( bOldAutoCalc );
/*N*/ 	}
/*N*/ }


//STRIP001 void ScDocument::UndoToDocument(USHORT nCol1, USHORT nRow1, USHORT nTab1,
//STRIP001 							USHORT nCol2, USHORT nRow2, USHORT nTab2,
//STRIP001 							USHORT nFlags, BOOL bOnlyMarked, ScDocument* pDestDoc,
//STRIP001 							const ScMarkData* pMarks)
//STRIP001 {
//STRIP001 	PutInOrder( nCol1, nCol2 );
//STRIP001 	PutInOrder( nRow1, nRow2 );
//STRIP001 	PutInOrder( nTab1, nTab2 );
//STRIP001 	if (VALIDTAB(nTab1) && VALIDTAB(nTab2))
//STRIP001 	{
//STRIP001 		BOOL bOldAutoCalc = pDestDoc->GetAutoCalc();
//STRIP001 		pDestDoc->SetAutoCalc( FALSE );		// Mehrfachberechnungen vermeiden
//STRIP001 		if (nTab1 > 0)
//STRIP001 			CopyToDocument( 0,0,0, MAXCOL,MAXROW,nTab1-1, IDF_FORMULA, FALSE, pDestDoc, pMarks );
//STRIP001 
//STRIP001 		for (USHORT i = nTab1; i <= nTab2; i++)
//STRIP001 		{
//STRIP001 			if (pTab[i] && pDestDoc->pTab[i])
//STRIP001 				pTab[i]->UndoToTable(nCol1, nRow1, nCol2, nRow2, nFlags,
//STRIP001 									bOnlyMarked, pDestDoc->pTab[i], pMarks);
//STRIP001 		}
//STRIP001 
//STRIP001 		if (nTab2 < MAXTAB)
//STRIP001 			CopyToDocument( 0,0,nTab2+1, MAXCOL,MAXROW,MAXTAB, IDF_FORMULA, FALSE, pDestDoc, pMarks );
//STRIP001 		pDestDoc->SetAutoCalc( bOldAutoCalc );
//STRIP001 	}
//STRIP001 }


/*N*/ void ScDocument::CopyToDocument(const ScRange& rRange,
/*N*/ 							USHORT nFlags, BOOL bOnlyMarked, ScDocument* pDestDoc,
/*N*/ 							const ScMarkData* pMarks, BOOL bColRowFlags)
/*N*/ {
/*N*/ 	ScRange aNewRange = rRange;
/*N*/ 	aNewRange.Justify();
/*N*/ 
/*N*/ 	if( !pDestDoc->aDocName.Len() )
/*N*/ 		pDestDoc->aDocName = aDocName;
/*N*/ 	BOOL bOldAutoCalc = pDestDoc->GetAutoCalc();
/*N*/ 	pDestDoc->SetAutoCalc( FALSE );		// Mehrfachberechnungen vermeiden
/*N*/ 	for (USHORT i = aNewRange.aStart.Tab(); i <= aNewRange.aEnd.Tab(); i++)
/*N*/ 		if (pTab[i] && pDestDoc->pTab[i])
/*N*/ 			pTab[i]->CopyToTable(aNewRange.aStart.Col(), aNewRange.aStart.Row(),
/*N*/ 								 aNewRange.aEnd.Col(), aNewRange.aEnd.Row(),
/*N*/ 								 nFlags, bOnlyMarked, pDestDoc->pTab[i],
/*N*/ 								 pMarks, FALSE, bColRowFlags);
/*N*/ 	pDestDoc->SetAutoCalc( bOldAutoCalc );
/*N*/ }


//STRIP001 void ScDocument::UndoToDocument(const ScRange& rRange,
//STRIP001 							USHORT nFlags, BOOL bOnlyMarked, ScDocument* pDestDoc,
//STRIP001 							const ScMarkData* pMarks)
//STRIP001 {
//STRIP001 	ScRange aNewRange = rRange;
//STRIP001 	aNewRange.Justify();
//STRIP001 	USHORT nTab1 = aNewRange.aStart.Tab();
//STRIP001 	USHORT nTab2 = aNewRange.aEnd.Tab();
//STRIP001 
//STRIP001 	BOOL bOldAutoCalc = pDestDoc->GetAutoCalc();
//STRIP001 	pDestDoc->SetAutoCalc( FALSE );		// Mehrfachberechnungen vermeiden
//STRIP001 	if (nTab1 > 0)
//STRIP001 		CopyToDocument( 0,0,0, MAXCOL,MAXROW,nTab1-1, IDF_FORMULA, FALSE, pDestDoc, pMarks );
//STRIP001 
//STRIP001 	for (USHORT i = nTab1; i <= nTab2; i++)
//STRIP001 	{
//STRIP001 		if (pTab[i] && pDestDoc->pTab[i])
//STRIP001 			pTab[i]->UndoToTable(aNewRange.aStart.Col(), aNewRange.aStart.Row(),
//STRIP001 									aNewRange.aEnd.Col(), aNewRange.aEnd.Row(),
//STRIP001 									nFlags, bOnlyMarked, pDestDoc->pTab[i], pMarks);
//STRIP001 	}
//STRIP001 
//STRIP001 	if (nTab2 < MAXTAB)
//STRIP001 		CopyToDocument( 0,0,nTab2+1, MAXCOL,MAXROW,MAXTAB, IDF_FORMULA, FALSE, pDestDoc, pMarks );
//STRIP001 	pDestDoc->SetAutoCalc( bOldAutoCalc );
//STRIP001 }


/*N*/ void ScDocument::CopyToClip(USHORT nCol1, USHORT nRow1,
/*N*/ 							USHORT nCol2, USHORT nRow2,
/*N*/ 							BOOL bCut, ScDocument* pClipDoc,
/*N*/ 							BOOL bAllTabs, const ScMarkData* pMarks,
/*N*/ 							BOOL bKeepScenarioFlags, BOOL bIncludeObjects)
/*N*/ {
/*N*/ 	DBG_ASSERT( bAllTabs || pMarks, "CopyToClip: ScMarkData fehlt" );
/*N*/ 
/*N*/ 	if (!bIsClip)
/*N*/ 	{
/*N*/ 		PutInOrder( nCol1, nCol2 );
/*N*/ 		PutInOrder( nRow1, nRow2 );
/*N*/ 		if (!pClipDoc)
/*N*/ 		{
DBG_BF_ASSERT(0, "STRIP"); //STRIP001 /*?*/ 			DBG_ERROR("CopyToClip: no ClipDoc");
//STRIP001 /*?*/ 			pClipDoc = SC_MOD()->GetClipDoc();
/*N*/ 		}
/*N*/ 
/*N*/ 		pClipDoc->aDocName = aDocName;
/*N*/ 		pClipDoc->aClipRange = ScRange( nCol1,nRow1,0, nCol2,nRow2,0 );
/*N*/ 		pClipDoc->ResetClip( this, pMarks );
/*N*/ 		USHORT i, j;
/*N*/ 		pClipDoc->pRangeName->FreeAll();
/*N*/ 		for (i = 0; i < pRangeName->GetCount(); i++)		//! DB-Bereiche Pivot-Bereiche auch !!!
/*N*/ 		{
/*N*/ 			USHORT nIndex = ((ScRangeData*)((*pRangeName)[i]))->GetIndex();
/*N*/ 			BOOL bInUse = FALSE;
/*N*/ 			for (j = 0; !bInUse && (j <= MAXTAB); j++)
/*N*/ 			{
/*N*/ 				if (pTab[j])
/*N*/ 					bInUse = pTab[j]->IsRangeNameInUse(nCol1, nRow1, nCol2, nRow2,
/*N*/ 													   nIndex);
/*N*/ 			}
/*N*/ 			if (bInUse)
/*N*/ 			{
/*N*/ 				ScRangeData* pData = new ScRangeData(*((*pRangeName)[i]));
/*N*/ 				if (!pClipDoc->pRangeName->Insert(pData))
/*N*/ 					delete pData;
/*N*/ 				else
/*N*/ 					pData->SetIndex(nIndex);
/*N*/ 			}
/*N*/ 		}
/*N*/ 		for (i = 0; i <= MAXTAB; i++)
/*N*/ 			if (pTab[i] && pClipDoc->pTab[i])
/*N*/ 				if ( bAllTabs || !pMarks || pMarks->GetTableSelect(i) )
/*N*/ 				{
DBG_BF_ASSERT(0, "STRIP"); //STRIP001 /*?*/ 					pTab[i]->CopyToClip(nCol1, nRow1, nCol2, nRow2, pClipDoc->pTab[i], bKeepScenarioFlags);
/*N*/ 
/*N*/ 					if ( pDrawLayer && bIncludeObjects )
/*N*/ 					{
/*N*/ 						//	also copy drawing objects
/*N*/ 
DBG_BF_ASSERT(0, "STRIP"); //STRIP001 /*?*/ 						Rectangle aObjRect = GetMMRect( nCol1, nRow1, nCol2, nRow2, i );
//STRIP001 /*?*/ 						pDrawLayer->CopyToClip( pClipDoc, i, aObjRect );
/*N*/ 					}
/*N*/ 				}
/*N*/ 
/*N*/ 		pClipDoc->bCutMode = bCut;
/*N*/ 	}
/*N*/ }


//STRIP001 void ScDocument::CopyTabToClip(USHORT nCol1, USHORT nRow1,
//STRIP001 								USHORT nCol2, USHORT nRow2,
//STRIP001 								USHORT nTab, ScDocument* pClipDoc)
//STRIP001 {
//STRIP001 	if (!bIsClip)
//STRIP001 	{
//STRIP001 		PutInOrder( nCol1, nCol2 );
//STRIP001 		PutInOrder( nRow1, nRow2 );
//STRIP001 		if (!pClipDoc)
//STRIP001 		{
//STRIP001 			DBG_ERROR("CopyTabToClip: no ClipDoc");
//STRIP001 			pClipDoc = SC_MOD()->GetClipDoc();
//STRIP001 		}
//STRIP001 
//STRIP001 		pClipDoc->aDocName = aDocName;
//STRIP001 		pClipDoc->aClipRange = ScRange( nCol1,nRow1,0, nCol2,nRow2,0 );
//STRIP001 		pClipDoc->ResetClip( this, nTab );
//STRIP001 
//STRIP001 		if (pTab[nTab] && pClipDoc->pTab[nTab])
//STRIP001 			pTab[nTab]->CopyToClip(nCol1, nRow1, nCol2, nRow2, pClipDoc->pTab[nTab], FALSE);
//STRIP001 
//STRIP001 		pClipDoc->bCutMode = FALSE;
//STRIP001 	}
//STRIP001 }


//STRIP001 void ScDocument::TransposeClip( ScDocument* pTransClip, USHORT nFlags, BOOL bAsLink )
//STRIP001 {
//STRIP001 	USHORT i;
//STRIP001 	DBG_ASSERT( bIsClip && pTransClip && pTransClip->bIsClip,
//STRIP001 					"TransposeClip mit falschem Dokument" );
//STRIP001 
//STRIP001 		//	initialisieren
//STRIP001 		//	-> pTransClip muss vor dem Original-Dokument geloescht werden!
//STRIP001 
//STRIP001 	pTransClip->ResetClip(this, (ScMarkData*)NULL);		// alle
//STRIP001 
//STRIP001 		//	Bereiche uebernehmen
//STRIP001 
//STRIP001 	pTransClip->pRangeName->FreeAll();
//STRIP001 	for (i = 0; i < pRangeName->GetCount(); i++)		//! DB-Bereiche Pivot-Bereiche auch !!!
//STRIP001 	{
//STRIP001 		USHORT nIndex = ((ScRangeData*)((*pRangeName)[i]))->GetIndex();
//STRIP001 		ScRangeData* pData = new ScRangeData(*((*pRangeName)[i]));
//STRIP001 		if (!pTransClip->pRangeName->Insert(pData))
//STRIP001 			delete pData;
//STRIP001 		else
//STRIP001 			pData->SetIndex(nIndex);
//STRIP001 	}
//STRIP001 
//STRIP001 		//	Daten
//STRIP001 
//STRIP001 	if ( aClipRange.aEnd.Row()-aClipRange.aStart.Row() <= MAXCOL )
//STRIP001 	{
//STRIP001 		for (i=0; i<=MAXTAB; i++)
//STRIP001 			if (pTab[i])
//STRIP001 			{
//STRIP001 				DBG_ASSERT( pTransClip->pTab[i], "TransposeClip: Tabelle nicht da" );
//STRIP001 				pTab[i]->TransposeClip( aClipRange.aStart.Col(), aClipRange.aStart.Row(),
//STRIP001 											aClipRange.aEnd.Col(), aClipRange.aEnd.Row(),
//STRIP001 											pTransClip->pTab[i], nFlags, bAsLink );
//STRIP001 
//STRIP001 				if ( pDrawLayer && ( nFlags & IDF_OBJECTS ) )
//STRIP001 				{
//STRIP001 					//	Drawing objects are copied to the new area without transposing.
//STRIP001 					//	CopyFromClip is used to adjust the objects to the transposed block's
//STRIP001 					//	cell range area.
//STRIP001 					//	(pDrawLayer in the original clipboard document is set only if there
//STRIP001 					//	are drawing objects to copy)
//STRIP001 
//STRIP001 					pTransClip->InitDrawLayer();
//STRIP001 					Rectangle aSourceRect = GetMMRect( aClipRange.aStart.Col(), aClipRange.aStart.Row(),
//STRIP001 														aClipRange.aEnd.Col(), aClipRange.aEnd.Row(), i );
//STRIP001 					Rectangle aDestRect = pTransClip->GetMMRect( 0, 0,
//STRIP001 													aClipRange.aEnd.Row() - aClipRange.aStart.Row(),
//STRIP001 													aClipRange.aEnd.Col() - aClipRange.aStart.Col(), i );
//STRIP001 					pTransClip->pDrawLayer->CopyFromClip( pDrawLayer, i, aSourceRect, ScAddress(0,0,i), aDestRect );
//STRIP001 				}
//STRIP001 			}
//STRIP001 
//STRIP001 		pTransClip->aClipRange = ScRange( 0, 0, aClipRange.aStart.Tab(),
//STRIP001 									aClipRange.aEnd.Row() - aClipRange.aStart.Row(),
//STRIP001 									aClipRange.aEnd.Col() - aClipRange.aStart.Col(),
//STRIP001 									aClipRange.aEnd.Tab() );
//STRIP001 	}
//STRIP001 	else
//STRIP001 		DBG_ERROR("TransposeClip: zu gross");
//STRIP001 
//STRIP001 		//	Dies passiert erst beim Einfuegen...
//STRIP001 
//STRIP001 	bCutMode = FALSE;
//STRIP001 }


/*N*/ BOOL ScDocument::IsClipboardSource() const
/*N*/ {
/*N*/ 	ScDocument* pClipDoc = SC_MOD()->GetClipDoc();
/*N*/ 	return pClipDoc && pClipDoc->xPoolHelper.isValid() &&
/*N*/ 			xPoolHelper->GetDocPool() == pClipDoc->xPoolHelper->GetDocPool();
/*N*/ }


/*N*/ void ScDocument::StartListeningFromClip( USHORT nCol1, USHORT nRow1,
/*N*/ 										USHORT nCol2, USHORT nRow2,
/*N*/ 										const ScMarkData& rMark, USHORT nInsFlag )
/*N*/ {
DBG_BF_ASSERT(0, "STRIP"); //STRIP001 	if (nInsFlag & IDF_CONTENTS)
//STRIP001 	{
//STRIP001 		for (USHORT i = 0; i <= MAXTAB; i++)
//STRIP001 			if (pTab[i])
//STRIP001 				if (rMark.GetTableSelect(i))
//STRIP001 					pTab[i]->StartListeningInArea( nCol1, nRow1, nCol2, nRow2 );
//STRIP001 	}
/*N*/ }


/*N*/ void ScDocument::BroadcastFromClip( USHORT nCol1, USHORT nRow1,
/*N*/ 								USHORT nCol2, USHORT nRow2,
/*N*/ 									const ScMarkData& rMark, USHORT nInsFlag )
/*N*/ {
DBG_BF_ASSERT(0, "STRIP"); //STRIP001 //STRIP001 	if (nInsFlag & IDF_CONTENTS)
//STRIP001 	{
//STRIP001 		USHORT nClipTab = 0;
//STRIP001 		for (USHORT i = 0; i <= MAXTAB; i++)
//STRIP001 			if (pTab[i])
//STRIP001 				if (rMark.GetTableSelect(i))
//STRIP001 					pTab[i]->BroadcastInArea( nCol1, nRow1, nCol2, nRow2 );
//STRIP001 	}
/*N*/ }


/*N*/ void ScDocument::CopyBlockFromClip( USHORT nCol1, USHORT nRow1,
/*N*/ 									USHORT nCol2, USHORT nRow2,
/*N*/ 									const ScMarkData& rMark,
/*N*/ 									short nDx, short nDy,
/*N*/ 									const ScCopyBlockFromClipParams* pCBFCP )
/*N*/ {
DBG_BF_ASSERT(0, "STRIP"); //STRIP001 //STRIP001 	ScTable** ppClipTab = pCBFCP->pClipDoc->pTab;
//STRIP001 	USHORT nTabEnd = pCBFCP->nTabEnd;
//STRIP001 	USHORT i;
//STRIP001 	USHORT nClipTab = 0;
//STRIP001 	for (i = pCBFCP->nTabStart; i <= nTabEnd; i++)
//STRIP001     {
//STRIP001         if (pTab[i] && rMark.GetTableSelect(i) )
//STRIP001         {
//STRIP001             while (!ppClipTab[nClipTab]) nClipTab = (nClipTab+1) % (MAXTAB+1);
//STRIP001 
//STRIP001             pTab[i]->CopyFromClip( nCol1, nRow1, nCol2, nRow2, nDx, nDy,
//STRIP001                 pCBFCP->nInsFlag, pCBFCP->bAsLink, pCBFCP->bSkipAttrForEmpty, ppClipTab[nClipTab] );
//STRIP001 
//STRIP001 			if ( pCBFCP->pClipDoc->pDrawLayer && ( pCBFCP->nInsFlag & IDF_OBJECTS ) )
//STRIP001 			{
//STRIP001 				//	also copy drawing objects
//STRIP001 
//STRIP001 				// drawing layer must be created before calling CopyFromClip
//STRIP001 				// (ScDocShell::MakeDrawLayer also does InitItems etc.)
//STRIP001 				DBG_ASSERT( pDrawLayer, "CopyBlockFromClip: No drawing layer" );
//STRIP001 				if ( pDrawLayer )
//STRIP001 				{
//STRIP001 					//	For GetMMRect, the row heights in the target document must already be valid
//STRIP001 					//	(copied in an extra step before pasting, or updated after pasting cells, but
//STRIP001 					//	before pasting objects).
//STRIP001 
//STRIP001 					Rectangle aSourceRect = pCBFCP->pClipDoc->GetMMRect(
//STRIP001 									nCol1-nDx, nRow1-nDy, nCol2-nDx, nRow2-nDy, nClipTab );
//STRIP001 					Rectangle aDestRect = GetMMRect( nCol1, nRow1, nCol2, nRow2, i );
//STRIP001 					pDrawLayer->CopyFromClip( pCBFCP->pClipDoc->pDrawLayer, nClipTab, aSourceRect,
//STRIP001 												ScAddress( nCol1, nRow1, i ), aDestRect );
//STRIP001 				}
//STRIP001 			}
//STRIP001 
//STRIP001             nClipTab = (nClipTab+1) % (MAXTAB+1);
//STRIP001         }
//STRIP001     }
//STRIP001     if ( pCBFCP->nInsFlag & IDF_CONTENTS )
//STRIP001 	{
//STRIP001 		nClipTab = 0;
//STRIP001 		for (i = pCBFCP->nTabStart; i <= nTabEnd; i++)
//STRIP001         {
//STRIP001             if (pTab[i] && rMark.GetTableSelect(i) )
//STRIP001             {
//STRIP001                 while (!ppClipTab[nClipTab]) nClipTab = (nClipTab+1) % (MAXTAB+1);
//STRIP001                 short nDz = ((short)i) - nClipTab;
//STRIP001 
//STRIP001                 //  #89081# ranges of consecutive selected tables (in clipboard and dest. doc)
//STRIP001                 //  must be handled in one UpdateReference call
//STRIP001                 USHORT nFollow = 0;
//STRIP001                 while ( i + nFollow < nTabEnd
//STRIP001                         && rMark.GetTableSelect( i + nFollow + 1 )
//STRIP001                         && nClipTab + nFollow < MAXTAB
//STRIP001                         && ppClipTab[nClipTab + nFollow + 1] )
//STRIP001                     ++nFollow;
//STRIP001 
//STRIP001                 if ( pCBFCP->pClipDoc->bCutMode )
//STRIP001                     UpdateReference( URM_MOVE,
//STRIP001                         nCol1, nRow1, i, nCol2, nRow2, i+nFollow,
//STRIP001                         nDx, nDy, nDz, pCBFCP->pRefUndoDoc );
//STRIP001                 else
//STRIP001                     UpdateReference( URM_COPY,
//STRIP001                         nCol1, nRow1, i, nCol2, nRow2, i+nFollow,
//STRIP001                         nDx, nDy, nDz, pCBFCP->pRefUndoDoc, FALSE );
//STRIP001 
//STRIP001                 nClipTab = (nClipTab+nFollow+1) % (MAXTAB+1);
//STRIP001                 i += nFollow;
//STRIP001             }
//STRIP001         }
//STRIP001 	}
/*N*/ }


/*N*/ void ScDocument::CopyNonFilteredFromClip( USHORT nCol1, USHORT nRow1,
/*N*/ 									USHORT nCol2, USHORT nRow2,
/*N*/ 									const ScMarkData& rMark,
/*N*/ 									short nDx, short nDy,
/*N*/ 									const ScCopyBlockFromClipParams* pCBFCP )
/*N*/ {
DBG_BF_ASSERT(0, "STRIP"); //STRIP001 //STRIP001 	//	call CopyBlockFromClip for ranges of consecutive non-filtered rows
//STRIP001 	//	nCol1/nRow1 etc. is in target doc
//STRIP001 	
//STRIP001 	//	filtered state is taken from first used table in clipboard (as in GetClipArea)
//STRIP001 	USHORT nFlagTab = 0;
//STRIP001 	ScTable** ppClipTab = pCBFCP->pClipDoc->pTab;
//STRIP001 	while ( nFlagTab < MAXTAB && !ppClipTab[nFlagTab] )
//STRIP001 		++nFlagTab;
//STRIP001 
//STRIP001 	USHORT nSourceRow = pCBFCP->pClipDoc->aClipRange.aStart.Row();
//STRIP001 	USHORT nSourceEnd = pCBFCP->pClipDoc->aClipRange.aEnd.Row();
//STRIP001 	USHORT nDestRow = nRow1;
//STRIP001 
//STRIP001 	while ( nSourceRow <= nSourceEnd && nDestRow <= nRow2 )
//STRIP001 	{
//STRIP001 		// skip filtered rows
//STRIP001 		while ( nSourceRow <= nSourceEnd &&
//STRIP001 				( pCBFCP->pClipDoc->GetRowFlags( nSourceRow, nFlagTab ) & CR_FILTERED ) != 0 )
//STRIP001 			++nSourceRow;
//STRIP001 
//STRIP001 		if ( nSourceRow <= nSourceEnd )
//STRIP001 		{
//STRIP001 			// look for more non-filtered rows following
//STRIP001 			USHORT nFollow = 0;
//STRIP001 			while ( nSourceRow + nFollow < nSourceEnd && nDestRow + nFollow < nRow2 &&
//STRIP001 					( pCBFCP->pClipDoc->GetRowFlags( nSourceRow + nFollow + 1, nFlagTab ) & CR_FILTERED ) == 0 )
//STRIP001 				++nFollow;
//STRIP001 
//STRIP001 			short nNewDy = ((short)nDestRow) - nSourceRow;
//STRIP001 			CopyBlockFromClip( nCol1, nDestRow, nCol2, nDestRow + nFollow, rMark, nDx, nNewDy, pCBFCP );
//STRIP001 
//STRIP001 			nSourceRow += nFollow + 1;
//STRIP001 			nDestRow += nFollow + 1;
//STRIP001 		}
//STRIP001 	}
/*N*/ }


/*N*/ void ScDocument::CopyFromClip( const ScRange& rDestRange, const ScMarkData& rMark,
/*N*/ 								USHORT nInsFlag,
/*N*/ 								ScDocument* pRefUndoDoc, ScDocument* pClipDoc, BOOL bResetCut,
/*N*/ 								BOOL bAsLink, BOOL bIncludeFiltered, BOOL bSkipAttrForEmpty )
/*N*/ {
/*N*/ 	if (!bIsClip)
/*N*/ 	{
/*N*/ 		if (!pClipDoc)
/*N*/ 		{
/*N*/ 			DBG_ERROR("CopyFromClip: no ClipDoc");
/*N*/ 			pClipDoc = SC_MOD()->GetClipDoc();
/*N*/ 		}
/*N*/ 		if (pClipDoc->bIsClip && pClipDoc->GetTableCount())
/*N*/ 		{
/*N*/ 			BOOL bOldAutoCalc = GetAutoCalc();
/*N*/ 			SetAutoCalc( FALSE );	// avoid multiple recalculations
/*N*/ 
/*N*/ 			SvNumberFormatter* pThisFormatter = xPoolHelper->GetFormTable();
/*N*/ 			SvNumberFormatter* pOtherFormatter = pClipDoc->xPoolHelper->GetFormTable();
/*N*/ 			if (pOtherFormatter && pOtherFormatter != pThisFormatter)
/*N*/ 			{
/*N*/ 				SvULONGTable* pExchangeList =
/*N*/ 						 pThisFormatter->MergeFormatter(*(pOtherFormatter));
/*N*/ 				if (pExchangeList->Count() > 0)
/*N*/ 					pFormatExchangeList = pExchangeList;
/*N*/ 			}
/*N*/ 
/*N*/ 			USHORT nClipRangeNames = pClipDoc->pRangeName->GetCount();
/*N*/ 			// array containing range names which might need update of indices
/*N*/ 			ScRangeData** pClipRangeNames = nClipRangeNames ? new ScRangeData* [nClipRangeNames] : NULL;
/*N*/ 			// the index mapping thereof
/*N*/ 			ScIndexMap aClipRangeMap( nClipRangeNames );
/*N*/ 			BOOL bRangeNameReplace = FALSE;
/*N*/ 
/*N*/ 			USHORT i, k;
/*N*/ 			for (i = 0; i < nClipRangeNames; i++)		//! DB-Bereiche Pivot-Bereiche auch
/*N*/ 			{
                /*	Copy only if the name doesn't exist in this document.
                 If it exists we use the already existing name instead,
                    another possibility could be to create new names if
                    documents differ.
                    A proper solution would ask the user how to proceed.
                    The adjustment of the indices in the formulas is done later.
                */
/*N*/ 				ScRangeData* pClipData = (*pClipDoc->pRangeName)[i];
/*N*/ 				if ( pRangeName->SearchName( pClipData->GetName(), k ) )
/*N*/ 				{
/*N*/ 					pClipRangeNames[i] = NULL;	// range name not inserted
/*N*/ 					USHORT nOldIndex = pClipData->GetIndex();
/*N*/ 					USHORT nNewIndex = ((*pRangeName)[k])->GetIndex();
/*N*/ 					aClipRangeMap.SetPair( i, nOldIndex, nNewIndex );
/*N*/ 					if ( !bRangeNameReplace )
/*N*/ 						bRangeNameReplace = ( nOldIndex != nNewIndex );
/*N*/ 				}
/*N*/ 				else
/*N*/ 				{
/*N*/ 					ScRangeData* pData = new ScRangeData( *pClipData );
/*N*/ 					pData->SetDocument(this);
/*N*/ 					if ( pRangeName->FindIndex( pData->GetIndex() ) )
/*N*/ 						pData->SetIndex(0);		// need new index, done in Insert
/*N*/ 					if ( pRangeName->Insert( pData ) )
/*N*/ 					{
/*N*/ 						pClipRangeNames[i] = pData;
/*N*/ 						USHORT nOldIndex = pClipData->GetIndex();
/*N*/ 						USHORT nNewIndex = pData->GetIndex();
/*N*/ 						aClipRangeMap.SetPair( i, nOldIndex, nNewIndex );
/*N*/ 						if ( !bRangeNameReplace )
/*N*/ 							bRangeNameReplace = ( nOldIndex != nNewIndex );
/*N*/ 					}
/*N*/ 					else
/*N*/ 					{	// must be an overflow
/*N*/ 						delete pData;
/*N*/ 						pClipRangeNames[i] = NULL;
/*N*/ 						aClipRangeMap.SetPair( i, pClipData->GetIndex(), 0 );
/*N*/ 						bRangeNameReplace = TRUE;
/*N*/ 					}
/*N*/ 				}
/*N*/ 			}
/*N*/ 			USHORT nCol1 = rDestRange.aStart.Col();
/*N*/ 			USHORT nRow1 = rDestRange.aStart.Row();
/*N*/ 			USHORT nCol2 = rDestRange.aEnd.Col();
/*N*/ 			USHORT nRow2 = rDestRange.aEnd.Row();
/*N*/ 
/*N*/ 			USHORT nXw = pClipDoc->aClipRange.aEnd.Col();
/*N*/ 			USHORT nYw = pClipDoc->aClipRange.aEnd.Row();
/*N*/ 			pClipDoc->ExtendMerge( pClipDoc->aClipRange.aStart.Col(),
/*N*/ 									pClipDoc->aClipRange.aStart.Row(),
/*N*/ 									nXw, nYw, 0 );
/*N*/ 			nXw -= pClipDoc->aClipRange.aEnd.Col();
/*N*/ 			nYw -= pClipDoc->aClipRange.aEnd.Row();			// only extra value from ExtendMerge
/*N*/ 			USHORT nDestAddX, nDestAddY;
/*N*/ 			pClipDoc->GetClipArea( nDestAddX, nDestAddY, bIncludeFiltered );
/*N*/ 			nXw += nDestAddX;
/*N*/ 			nYw += nDestAddY;								// ClipArea, plus ExtendMerge value
/*N*/ 
/*N*/ 			//	Inhalte entweder komplett oder gar nicht loeschen:
/*N*/ 			USHORT nDelFlag = IDF_NONE;
/*N*/ 			if ( nInsFlag & IDF_CONTENTS )
/*N*/ 				nDelFlag |= IDF_CONTENTS;
/*N*/ 			//	With bSkipAttrForEmpty, don't remove attributes, copy
/*N*/ 			//	on top of existing attributes instead.
/*N*/ 			if ( ( nInsFlag & IDF_ATTRIB ) && !bSkipAttrForEmpty )
/*N*/ 				nDelFlag |= IDF_ATTRIB;
/*N*/ 			DeleteArea(nCol1, nRow1, nCol2, nRow2, rMark, nDelFlag);
/*N*/ 
/*N*/ 			bInsertingFromOtherDoc = TRUE;	// kein Broadcast/Listener aufbauen bei Insert
/*N*/ 			USHORT nC1 = nCol1;
/*N*/ 			USHORT nR1 = nRow1;
/*N*/ 			USHORT nC2 = nC1 + nXw;
/*N*/ 			USHORT nR2 = nR1 + nYw;
/*N*/ 			USHORT nClipStartCol = pClipDoc->aClipRange.aStart.Col();
/*N*/ 			USHORT nClipStartRow = pClipDoc->aClipRange.aStart.Row();
/*N*/ 
/*N*/ 			ScCopyBlockFromClipParams aCBFCP;
/*N*/ 			aCBFCP.pRefUndoDoc = pRefUndoDoc;
/*N*/ 			aCBFCP.pClipDoc = pClipDoc;
/*N*/ 			aCBFCP.nInsFlag = nInsFlag;
/*N*/ 			aCBFCP.bAsLink	= bAsLink;
/*N*/ 			aCBFCP.bSkipAttrForEmpty = bSkipAttrForEmpty;
/*N*/ 			aCBFCP.nTabStart = MAXTAB;		// wird in der Schleife angepasst
/*N*/ 			aCBFCP.nTabEnd = 0;				// wird in der Schleife angepasst
/*N*/ 
/*N*/ 			//	Inc/DecRecalcLevel einmal aussen, damit nicht fuer jeden Block
/*N*/ 			//	die Draw-Seitengroesse neu berechnet werden muss
/*N*/ 			//!	nur wenn ganze Zeilen/Spalten kopiert werden?
/*N*/ 
/*N*/ 			for (i = 0; i <= MAXTAB; i++)
/*N*/ 				if (pTab[i] && rMark.GetTableSelect(i))
/*N*/ 				{
/*N*/ 					if ( i < aCBFCP.nTabStart )
/*N*/ 						aCBFCP.nTabStart = i;
/*N*/ 					aCBFCP.nTabEnd = i;
/*N*/ 					pTab[i]->IncRecalcLevel();
/*N*/ 				}
/*N*/ 
/*N*/ 			// bei mindestens 64 Zeilen wird in ScColumn::CopyFromClip voralloziert
/*N*/ 			BOOL bDoDouble = ( nYw < 64 && nRow2 - nRow1 > 64);
/*N*/ 			BOOL bOldDouble = ScColumn::bDoubleAlloc;
/*N*/ 			if (bDoDouble)
/*N*/ 				ScColumn::bDoubleAlloc = TRUE;
/*N*/ 
/*N*/ 			do
/*N*/ 			{
/*N*/ 				do
/*N*/ 				{
/*N*/ 					short nDx = ((short)nC1) - nClipStartCol;
/*N*/ 					short nDy = ((short)nR1) - nClipStartRow;
/*N*/ 					if ( bIncludeFiltered )
/*N*/ 						CopyBlockFromClip( nC1, nR1, nC2, nR2, rMark, nDx, nDy, &aCBFCP );
/*N*/ 					else
/*N*/ 						CopyNonFilteredFromClip( nC1, nR1, nC2, nR2, rMark, nDx, nDy, &aCBFCP );
/*N*/ 					nC1 = nC2 + 1;
/*N*/ 					nC2 = Min((USHORT)(nC1 + nXw), nCol2);
/*N*/ 				}
/*N*/ 				while (nC1 <= nCol2);
/*N*/ 				nC1 = nCol1;
/*N*/ 				nC2 = nC1 + nXw;
/*N*/ 				nR1 = nR2 + 1;
/*N*/ 				nR2 = Min((USHORT)(nR1 + nYw), nRow2);
/*N*/ 			}
/*N*/ 			while (nR1 <= nRow2);
/*N*/ 
/*N*/ 			ScColumn::bDoubleAlloc = bOldDouble;
/*N*/ 
/*N*/ 			for (i = 0; i <= MAXTAB; i++)
/*N*/ 				if (pTab[i] && rMark.GetTableSelect(i))
/*N*/ 					pTab[i]->DecRecalcLevel();
/*N*/ 
/*N*/ 			bInsertingFromOtherDoc = FALSE;
/*N*/ 			pFormatExchangeList = NULL;
/*N*/ 			if ( bRangeNameReplace )
/*N*/ 			{
/*N*/ 				// first update all inserted named formulas if they contain other
/*N*/ 				// range names and used indices changed
/*N*/ 				for (i = 0; i < nClipRangeNames; i++)		//! DB-Bereiche Pivot-Bereiche auch
/*N*/ 				{
/*N*/ 					if ( pClipRangeNames[i] )
/*N*/ 						pClipRangeNames[i]->ReplaceRangeNamesInUse( aClipRangeMap );
/*N*/ 				}
/*N*/ 				// then update the formulas, they might need the just updated range names
/*N*/ 				USHORT nC1 = nCol1;
/*N*/ 				USHORT nR1 = nRow1;
/*N*/ 				USHORT nC2 = nC1 + nXw;
/*N*/ 				USHORT nR2 = nR1 + nYw;
/*N*/ 				do
/*N*/ 				{
/*N*/ 					do
/*N*/ 					{
/*N*/ 						for (k = 0; k <= MAXTAB; k++)
/*N*/ 						{
/*N*/ 							if ( pTab[k] && rMark.GetTableSelect(k) )
/*N*/ 								pTab[k]->ReplaceRangeNamesInUse(nC1, nR1,
/*N*/ 									nC2, nR2, aClipRangeMap );
/*N*/ 						}
/*N*/ 						nC1 = nC2 + 1;
/*N*/ 						nC2 = Min((USHORT)(nC1 + nXw), nCol2);
/*N*/ 					} while (nC1 <= nCol2);
/*N*/ 					nC1 = nCol1;
/*N*/ 					nC2 = nC1 + nXw;
/*N*/ 					nR1 = nR2 + 1;
/*N*/ 					nR2 = Min((USHORT)(nR1 + nYw), nRow2);
/*N*/ 				} while (nR1 <= nRow2);
/*N*/ 			}
/*N*/ 			if ( pClipRangeNames )
/*N*/ 				delete [] pClipRangeNames;
/*N*/ 			// Listener aufbauen nachdem alles inserted wurde
/*N*/ 			StartListeningFromClip( nCol1, nRow1, nCol2, nRow2, rMark, nInsFlag );
/*N*/ 			// nachdem alle Listener aufgebaut wurden, kann gebroadcastet werden
/*N*/ 			BroadcastFromClip( nCol1, nRow1, nCol2, nRow2, rMark, nInsFlag );
/*N*/ 			if (bResetCut)
/*N*/ 				pClipDoc->bCutMode = FALSE;
/*N*/ 			SetAutoCalc( bOldAutoCalc );
/*N*/ 		}
/*N*/ 	}
/*N*/ }


//STRIP001 void ScDocument::SetClipArea( const ScRange& rArea, BOOL bCut )
//STRIP001 {
//STRIP001 	if (bIsClip)
//STRIP001 	{
//STRIP001 		aClipRange = rArea;
//STRIP001 		bCutMode = bCut;
//STRIP001 	}
//STRIP001 	else
//STRIP001 		DBG_ERROR("SetClipArea: kein Clip");
//STRIP001 }


/*N*/ void ScDocument::GetClipArea(USHORT& nClipX, USHORT& nClipY, BOOL bIncludeFiltered)
/*N*/ {
DBG_BF_ASSERT(0, "STRIP"); //STRIP001 //STRIP001 	if (bIsClip)
//STRIP001 	{
//STRIP001 		nClipX = aClipRange.aEnd.Col() - aClipRange.aStart.Col();
//STRIP001 
//STRIP001 		if ( bIncludeFiltered )
//STRIP001 			nClipY = aClipRange.aEnd.Row() - aClipRange.aStart.Row();
//STRIP001 		else
//STRIP001 		{
//STRIP001 			//	count non-filtered rows
//STRIP001 			//	count on first used table in clipboard
//STRIP001 			USHORT nCountTab = 0;
//STRIP001 			while ( nCountTab < MAXTAB && !pTab[nCountTab] )
//STRIP001 				++nCountTab;
//STRIP001 
//STRIP001 			USHORT nEndRow = aClipRange.aEnd.Row();
//STRIP001 			USHORT nResult = 0;
//STRIP001 			for (USHORT nRow = aClipRange.aStart.Row(); nRow <= nEndRow; nRow++)
//STRIP001 				if ( ( GetRowFlags( nRow, nCountTab ) & CR_FILTERED ) == 0 )
//STRIP001 					++nResult;
//STRIP001 
//STRIP001 			if ( nResult > 0 )
//STRIP001 				nClipY = nResult - 1;
//STRIP001 			else
//STRIP001 				nClipY = 0;					// always return at least 1 row
//STRIP001 		}
//STRIP001 	}
//STRIP001 	else
//STRIP001 		DBG_ERROR("GetClipArea: kein Clip");
/*N*/ }


//STRIP001 void ScDocument::GetClipStart(USHORT& nClipX, USHORT& nClipY)
//STRIP001 {
//STRIP001 	if (bIsClip)
//STRIP001 	{
//STRIP001 		nClipX = aClipRange.aStart.Col();
//STRIP001 		nClipY = aClipRange.aStart.Row();
//STRIP001 	}
//STRIP001 	else
//STRIP001 		DBG_ERROR("GetClipStart: kein Clip");
//STRIP001 }


//STRIP001 BOOL ScDocument::HasClipFilteredRows()
//STRIP001 {
//STRIP001 	//	count on first used table in clipboard
//STRIP001 	USHORT nCountTab = 0;
//STRIP001 	while ( nCountTab < MAXTAB && !pTab[nCountTab] )
//STRIP001 		++nCountTab;
//STRIP001 
//STRIP001 	USHORT nEndRow = aClipRange.aEnd.Row();
//STRIP001 	for (USHORT nRow = aClipRange.aStart.Row(); nRow <= nEndRow; nRow++)
//STRIP001 		if ( ( GetRowFlags( nRow, nCountTab ) & CR_FILTERED ) != 0 )
//STRIP001 			return TRUE;
//STRIP001 
//STRIP001 	return FALSE;
//STRIP001 }


//STRIP001 void ScDocument::MixDocument( const ScRange& rRange, USHORT nFunction, BOOL bSkipEmpty,
//STRIP001 									ScDocument* pSrcDoc )
//STRIP001 {
//STRIP001 	USHORT nTab1 = rRange.aStart.Tab();
//STRIP001 	USHORT nTab2 = rRange.aEnd.Tab();
//STRIP001 	for (USHORT i = nTab1; i <= nTab2; i++)
//STRIP001 		if (pTab[i] && pSrcDoc->pTab[i])
//STRIP001 			pTab[i]->MixData( rRange.aStart.Col(), rRange.aStart.Row(),
//STRIP001 								rRange.aEnd.Col(), rRange.aEnd.Row(),
//STRIP001 								nFunction, bSkipEmpty, pSrcDoc->pTab[i] );
//STRIP001 }


//STRIP001 void ScDocument::FillTab( const ScRange& rSrcArea, const ScMarkData& rMark,
//STRIP001 								USHORT nFlags, USHORT nFunction,
//STRIP001 								BOOL bSkipEmpty, BOOL bAsLink )
//STRIP001 {
//STRIP001 	USHORT nDelFlags = nFlags;
//STRIP001 	if (nDelFlags & IDF_CONTENTS)
//STRIP001 		nDelFlags |= IDF_CONTENTS;			// immer alle Inhalte oder keine loeschen!
//STRIP001 
//STRIP001 	USHORT nSrcTab = rSrcArea.aStart.Tab();
//STRIP001 
//STRIP001 	if (nSrcTab <= MAXTAB && pTab[nSrcTab])
//STRIP001 	{
//STRIP001 		USHORT nStartCol = rSrcArea.aStart.Col();
//STRIP001 		USHORT nStartRow = rSrcArea.aStart.Row();
//STRIP001 		USHORT nEndCol = rSrcArea.aEnd.Col();
//STRIP001 		USHORT nEndRow = rSrcArea.aEnd.Row();
//STRIP001 		ScDocument* pMixDoc = NULL;
//STRIP001 		BOOL bDoMix = ( bSkipEmpty || nFunction ) && ( nFlags & IDF_CONTENTS );
//STRIP001 
//STRIP001 		BOOL bOldAutoCalc = GetAutoCalc();
//STRIP001 		SetAutoCalc( FALSE );					// Mehrfachberechnungen vermeiden
//STRIP001 
//STRIP001 		USHORT nCount = GetTableCount();
//STRIP001 		for (USHORT i=0; i<nCount; i++)
//STRIP001 			if ( i!=nSrcTab && pTab[i] && rMark.GetTableSelect(i) )
//STRIP001 			{
//STRIP001 				if (bDoMix)
//STRIP001 				{
//STRIP001 					if (!pMixDoc)
//STRIP001 					{
//STRIP001 						pMixDoc = new ScDocument( SCDOCMODE_UNDO );
//STRIP001 						pMixDoc->InitUndo( this, i, i );
//STRIP001 					}
//STRIP001 					else
//STRIP001 						pMixDoc->AddUndoTab( i, i );
//STRIP001 					pTab[i]->CopyToTable( nStartCol,nStartRow, nEndCol,nEndRow,
//STRIP001 											IDF_CONTENTS, FALSE, pMixDoc->pTab[i] );
//STRIP001 				}
//STRIP001 				pTab[i]->DeleteArea( nStartCol,nStartRow, nEndCol,nEndRow, nDelFlags);
//STRIP001 				pTab[nSrcTab]->CopyToTable( nStartCol,nStartRow, nEndCol,nEndRow,
//STRIP001 												 nFlags, FALSE, pTab[i], NULL, bAsLink );
//STRIP001 
//STRIP001 				if (bDoMix)
//STRIP001 					pTab[i]->MixData( nStartCol,nStartRow, nEndCol,nEndRow,
//STRIP001 										nFunction, bSkipEmpty, pMixDoc->pTab[i] );
//STRIP001 			}
//STRIP001 
//STRIP001 		delete pMixDoc;
//STRIP001 
//STRIP001 		SetAutoCalc( bOldAutoCalc );
//STRIP001 	}
//STRIP001 	else
//STRIP001 		DBG_ERROR("falsche Tabelle");
//STRIP001 }


//STRIP001 void ScDocument::FillTabMarked( USHORT nSrcTab, const ScMarkData& rMark,
//STRIP001 								USHORT nFlags, USHORT nFunction,
//STRIP001 								BOOL bSkipEmpty, BOOL bAsLink )
//STRIP001 {
//STRIP001 	USHORT nDelFlags = nFlags;
//STRIP001 	if (nDelFlags & IDF_CONTENTS)
//STRIP001 		nDelFlags |= IDF_CONTENTS;			// immer alle Inhalte oder keine loeschen!
//STRIP001 
//STRIP001 	if (nSrcTab <= MAXTAB && pTab[nSrcTab])
//STRIP001 	{
//STRIP001 		ScDocument* pMixDoc = NULL;
//STRIP001 		BOOL bDoMix = ( bSkipEmpty || nFunction ) && ( nFlags & IDF_CONTENTS );
//STRIP001 
//STRIP001 		BOOL bOldAutoCalc = GetAutoCalc();
//STRIP001 		SetAutoCalc( FALSE );					// Mehrfachberechnungen vermeiden
//STRIP001 
//STRIP001 		ScRange aArea;
//STRIP001 		rMark.GetMultiMarkArea( aArea );
//STRIP001 		USHORT nStartCol = aArea.aStart.Col();
//STRIP001 		USHORT nStartRow = aArea.aStart.Row();
//STRIP001 		USHORT nEndCol = aArea.aEnd.Col();
//STRIP001 		USHORT nEndRow = aArea.aEnd.Row();
//STRIP001 
//STRIP001 		USHORT nCount = GetTableCount();
//STRIP001 		for (USHORT i=0; i<nCount; i++)
//STRIP001 			if ( i!=nSrcTab && pTab[i] && rMark.GetTableSelect(i) )
//STRIP001 			{
//STRIP001 				if (bDoMix)
//STRIP001 				{
//STRIP001 					if (!pMixDoc)
//STRIP001 					{
//STRIP001 						pMixDoc = new ScDocument( SCDOCMODE_UNDO );
//STRIP001 						pMixDoc->InitUndo( this, i, i );
//STRIP001 					}
//STRIP001 					else
//STRIP001 						pMixDoc->AddUndoTab( i, i );
//STRIP001 					pTab[i]->CopyToTable( nStartCol,nStartRow, nEndCol,nEndRow,
//STRIP001 											IDF_CONTENTS, TRUE, pMixDoc->pTab[i], &rMark );
//STRIP001 				}
//STRIP001 
//STRIP001 				pTab[i]->DeleteSelection( nDelFlags, rMark );
//STRIP001 				pTab[nSrcTab]->CopyToTable( nStartCol,nStartRow, nEndCol,nEndRow,
//STRIP001 											 nFlags, TRUE, pTab[i], &rMark, bAsLink );
//STRIP001 
//STRIP001 				if (bDoMix)
//STRIP001 					pTab[i]->MixMarked( rMark, nFunction, bSkipEmpty, pMixDoc->pTab[i] );
//STRIP001 			}
//STRIP001 
//STRIP001 		delete pMixDoc;
//STRIP001 
//STRIP001 		SetAutoCalc( bOldAutoCalc );
//STRIP001 	}
//STRIP001 	else
//STRIP001 		DBG_ERROR("falsche Tabelle");
//STRIP001 }


/*N*/ void ScDocument::PutCell( USHORT nCol, USHORT nRow, USHORT nTab, ScBaseCell* pCell, BOOL bForceTab )
/*N*/ {
/*N*/ 	if (VALIDTAB(nTab))
/*N*/ 	{
/*N*/ 		if ( bForceTab && !pTab[nTab] )
/*N*/ 		{
/*N*/ 			BOOL bExtras = !bIsUndo;		// Spaltenbreiten, Zeilenhoehen, Flags
/*N*/ 
/*N*/ 			pTab[nTab] = new ScTable(this, nTab,
/*N*/ 							String::CreateFromAscii(RTL_CONSTASCII_STRINGPARAM("temp")),
/*N*/ 							bExtras, bExtras);
/*N*/ 			++nMaxTableNumber;
/*N*/ 		}
/*N*/ 
/*N*/ 		if (pTab[nTab])
/*N*/ 			pTab[nTab]->PutCell( nCol, nRow, pCell );
/*N*/ 	}
/*N*/ }


/*N*/ void ScDocument::PutCell( const ScAddress& rPos, ScBaseCell* pCell, BOOL bForceTab )
/*N*/ {
/*N*/ 	USHORT nTab = rPos.Tab();
/*N*/ 	if ( bForceTab && !pTab[nTab] )
/*N*/ 	{
/*?*/ 		BOOL bExtras = !bIsUndo;		// Spaltenbreiten, Zeilenhoehen, Flags
/*?*/ 
/*?*/ 		pTab[nTab] = new ScTable(this, nTab,
/*?*/ 						String::CreateFromAscii(RTL_CONSTASCII_STRINGPARAM("temp")),
/*?*/ 						bExtras, bExtras);
/*?*/ 		++nMaxTableNumber;
/*N*/ 	}
/*N*/ 
/*N*/ 	if (pTab[nTab])
/*N*/ 		pTab[nTab]->PutCell( rPos, pCell );
/*N*/ }


/*N*/ BOOL ScDocument::SetString( USHORT nCol, USHORT nRow, USHORT nTab, const String& rString )
/*N*/ {
/*N*/ 	if ( nTab<=MAXTAB && pTab[nTab] )
/*N*/ 		return pTab[nTab]->SetString( nCol, nRow, nTab, rString );
/*N*/ 	else
/*N*/ 		return FALSE;
/*N*/ }


/*N*/ void ScDocument::SetValue( USHORT nCol, USHORT nRow, USHORT nTab, const double& rVal )
/*N*/ {
/*N*/ 	if (VALIDTAB(nTab))
/*N*/ 		if (pTab[nTab])
/*N*/ 			pTab[nTab]->SetValue( nCol, nRow, rVal );
/*N*/ }


/*N*/ void ScDocument::SetNote( USHORT nCol, USHORT nRow, USHORT nTab, const ScPostIt& rNote )
/*N*/ {
/*N*/ 	if (VALIDTAB(nTab))
/*N*/ 		if (pTab[nTab])
/*N*/ 			pTab[nTab]->SetNote( nCol, nRow, rNote );
/*N*/ }


/*N*/ void ScDocument::GetString( USHORT nCol, USHORT nRow, USHORT nTab, String& rString )
/*N*/ {
/*N*/ 	if ( VALIDTAB(nTab) && pTab[nTab] )
/*N*/ 		pTab[nTab]->GetString( nCol, nRow, rString );
/*N*/ 	else
/*N*/ 		rString.Erase();
/*N*/ }


/*N*/ void ScDocument::GetInputString( USHORT nCol, USHORT nRow, USHORT nTab, String& rString )
/*N*/ {
/*N*/ 	if ( VALIDTAB(nTab) && pTab[nTab] )
/*N*/ 		pTab[nTab]->GetInputString( nCol, nRow, rString );
/*N*/ 	else
/*N*/ 		rString.Erase();
/*N*/ }


/*N*/ void ScDocument::GetValue( USHORT nCol, USHORT nRow, USHORT nTab, double& rValue )
/*N*/ {
/*N*/ 	if ( VALIDTAB(nTab) && pTab[nTab] )
/*N*/ 		rValue = pTab[nTab]->GetValue( nCol, nRow );
/*N*/ 	else
/*N*/ 		rValue = 0.0;
/*N*/ }


/*N*/ double ScDocument::GetValue( const ScAddress& rPos )
/*N*/ {
/*N*/ 	USHORT nTab = rPos.Tab();
/*N*/ 	if ( pTab[nTab] )
/*N*/ 		return pTab[nTab]->GetValue( rPos );
/*N*/ 	return 0.0;
/*N*/ }


/*N*/ void ScDocument::GetNumberFormat( USHORT nCol, USHORT nRow, USHORT nTab,
/*N*/ 								  ULONG& rFormat )
/*N*/ {
/*N*/ 	if (VALIDTAB(nTab))
/*N*/ 		if (pTab[nTab])
/*N*/ 		{
/*N*/ 			rFormat = pTab[nTab]->GetNumberFormat( nCol, nRow );
/*N*/ 			return ;
/*N*/ 		}
/*N*/ 	rFormat = 0;
/*N*/ }


/*N*/ ULONG ScDocument::GetNumberFormat( const ScAddress& rPos ) const
/*N*/ {
/*N*/ 	USHORT nTab = rPos.Tab();
/*N*/ 	if ( pTab[nTab] )
/*N*/ 		return pTab[nTab]->GetNumberFormat( rPos );
/*N*/ 	return 0;
/*N*/ }


/*N*/ void ScDocument::GetNumberFormatInfo( short& nType, ULONG& nIndex,
/*N*/ 			const ScAddress& rPos, const ScFormulaCell& rFCell ) const
/*N*/ {
/*N*/ 	USHORT nTab = rPos.Tab();
/*N*/ 	if ( pTab[nTab] )
/*N*/ 	{
/*N*/ 		nIndex = pTab[nTab]->GetNumberFormat( rPos );
/*N*/ 		if ( (nIndex % SV_COUNTRY_LANGUAGE_OFFSET) == 0 )
/*N*/ 			rFCell.GetFormatInfo( nType, nIndex );
/*N*/ 		else
/*N*/ 			nType = GetFormatTable()->GetType( nIndex );
/*N*/ 	}
/*N*/ 	else
/*N*/ 	{
/*N*/ 		nType = NUMBERFORMAT_UNDEFINED;
/*N*/ 		nIndex = 0;
/*N*/ 	}
/*N*/ }


/*N*/ void ScDocument::GetFormula( USHORT nCol, USHORT nRow, USHORT nTab, String& rFormula,
/*N*/ 							 BOOL bAsciiExport ) const
/*N*/ {
/*N*/ 	if ( VALIDTAB(nTab) && pTab[nTab] )
/*N*/ 			pTab[nTab]->GetFormula( nCol, nRow, rFormula, bAsciiExport );
/*N*/ 	else
/*N*/ 		rFormula.Erase();
/*N*/ }


/*N*/ BOOL ScDocument::GetNote( USHORT nCol, USHORT nRow, USHORT nTab, ScPostIt& rNote )
/*N*/ {
/*N*/ 	BOOL bHasNote = FALSE;
/*N*/ 
/*N*/ 	if ( VALIDTAB(nTab) && pTab[nTab] )
/*N*/ 		bHasNote = pTab[nTab]->GetNote( nCol, nRow, rNote );
/*N*/ 	else
/*?*/ 		rNote.Clear();
/*N*/ 
/*N*/ 	return bHasNote;
/*N*/ }


/*N*/ CellType ScDocument::GetCellType( const ScAddress& rPos ) const
/*N*/ {
/*N*/ 	USHORT nTab = rPos.Tab();
/*N*/ 	if ( pTab[nTab] )
/*N*/ 		return pTab[nTab]->GetCellType( rPos );
/*N*/ 	return CELLTYPE_NONE;
/*N*/ }


/*N*/ void ScDocument::GetCellType( USHORT nCol, USHORT nRow, USHORT nTab,
/*N*/ 		CellType& rCellType ) const
/*N*/ {
/*N*/ 	if (nTab<=MAXTAB && pTab[nTab])
/*N*/ 		rCellType = pTab[nTab]->GetCellType( nCol, nRow );
/*N*/ 	else
/*N*/ 		rCellType = CELLTYPE_NONE;
/*N*/ }


/*N*/ void ScDocument::GetCell( USHORT nCol, USHORT nRow, USHORT nTab,
/*N*/ 		ScBaseCell*& rpCell ) const
/*N*/ {
/*N*/ 	if (nTab<=MAXTAB && pTab[nTab])
/*N*/ 		rpCell = pTab[nTab]->GetCell( nCol, nRow );
/*N*/ 	else
/*N*/ 	{
/*N*/ 		DBG_ERROR("GetCell ohne Tabelle");
/*N*/ 		rpCell = NULL;
/*N*/ 	}
/*N*/ }


/*N*/ ScBaseCell* ScDocument::GetCell( const ScAddress& rPos ) const
/*N*/ {
/*N*/ 	USHORT nTab = rPos.Tab();
/*N*/ 	if ( pTab[nTab] )
/*N*/ 		return pTab[nTab]->GetCell( rPos );
/*N*/ 
/*N*/ 	DBG_ERROR("GetCell ohne Tabelle");
/*N*/ 	return NULL;
/*N*/ }


/*N*/ BOOL ScDocument::HasStringData( USHORT nCol, USHORT nRow, USHORT nTab ) const
/*N*/ {
/*N*/ 	if ( VALIDTAB(nTab) && pTab[nTab] )
/*N*/ 			return pTab[nTab]->HasStringData( nCol, nRow );
/*N*/ 	else
/*N*/ 		return FALSE;
/*N*/ }


/*N*/ BOOL ScDocument::HasValueData( USHORT nCol, USHORT nRow, USHORT nTab ) const
/*N*/ {
/*N*/ 	if ( VALIDTAB(nTab) && pTab[nTab] )
/*N*/ 			return pTab[nTab]->HasValueData( nCol, nRow );
/*N*/ 	else
/*N*/ 		return FALSE;
/*N*/ }


//STRIP001 BOOL ScDocument::HasStringCells( const ScRange& rRange ) const
//STRIP001 {
//STRIP001 	//	TRUE, wenn String- oder Editzellen im Bereich
//STRIP001 
//STRIP001 	USHORT nStartCol = rRange.aStart.Col();
//STRIP001 	USHORT nStartRow = rRange.aStart.Row();
//STRIP001 	USHORT nStartTab = rRange.aStart.Tab();
//STRIP001 	USHORT nEndCol = rRange.aEnd.Col();
//STRIP001 	USHORT nEndRow = rRange.aEnd.Row();
//STRIP001 	USHORT nEndTab = rRange.aEnd.Tab();
//STRIP001 
//STRIP001 	for ( USHORT nTab=nStartTab; nTab<=nEndTab; nTab++ )
//STRIP001 		if ( pTab[nTab] && pTab[nTab]->HasStringCells( nStartCol, nStartRow, nEndCol, nEndRow ) )
//STRIP001 			return TRUE;
//STRIP001 
//STRIP001 	return FALSE;
//STRIP001 }


//STRIP001 void ScDocument::SetDirtyVar()
//STRIP001 {
//STRIP001 	for (USHORT i=0; i<=MAXTAB; i++)
//STRIP001 		if (pTab[i]) pTab[i]->SetDirtyVar();
//STRIP001 }


/*N*/ void ScDocument::SetDirty()
/*N*/ {
/*N*/ 	BOOL bOldAutoCalc = GetAutoCalc();
/*N*/ 	bAutoCalc = FALSE;		// keine Mehrfachberechnung
/*N*/ 	for (USHORT i=0; i<=MAXTAB; i++)
/*N*/ 		if (pTab[i]) pTab[i]->SetDirty();
/*N*/ 
/*N*/ 	//	Charts werden zwar auch ohne AutoCalc im Tracking auf Dirty gesetzt,
/*N*/ 	//	wenn alle Formeln dirty sind, werden die Charts aber nicht mehr erwischt
/*N*/ 	//	(#45205#) - darum alle Charts nochmal explizit
/*N*/ 	if (pChartListenerCollection)
/*N*/ 		pChartListenerCollection->SetDirty();
/*N*/ 
/*N*/ 	SetAutoCalc( bOldAutoCalc );
/*N*/ }


/*N*/ void ScDocument::SetDirty( const ScRange& rRange )
/*N*/ {
/*N*/ 	BOOL bOldAutoCalc = GetAutoCalc();
/*N*/ 	bAutoCalc = FALSE;		// keine Mehrfachberechnung
/*N*/ 	USHORT nTab2 = rRange.aEnd.Tab();
/*N*/ 	for (USHORT i=rRange.aStart.Tab(); i<=nTab2; i++)
/*N*/ 		if (pTab[i]) pTab[i]->SetDirty( rRange );
/*N*/ 	SetAutoCalc( bOldAutoCalc );
/*N*/ }


/*N*/  void ScDocument::SetTableOpDirty( const ScRange& rRange )
/*N*/  {
/*N*/  	BOOL bOldAutoCalc = GetAutoCalc();
/*N*/  	bAutoCalc = FALSE;		// no multiple recalculation
/*N*/  	USHORT nTab2 = rRange.aEnd.Tab();
/*N*/  	for (USHORT i=rRange.aStart.Tab(); i<=nTab2; i++)
/*N*/  		if (pTab[i]) pTab[i]->SetTableOpDirty( rRange );
/*N*/  	SetAutoCalc( bOldAutoCalc );
/*N*/  }


/*N*/  void ScDocument::AddTableOpFormulaCell( ScFormulaCell* pCell )
/*N*/  {
/*N*/      ScInterpreterTableOpParams* p = aTableOpList.Last();
/*N*/      if ( p && p->bCollectNotifications )
/*N*/      {
/*N*/          if ( p->bRefresh )
/*N*/          {   // refresh pointers only
/*N*/              p->aNotifiedFormulaCells.push_back( pCell );
/*N*/          }
/*N*/          else
/*N*/          {   // init both, address and pointer
/*N*/              p->aNotifiedFormulaCells.push_back( pCell );
/*N*/              p->aNotifiedFormulaPos.push_back( pCell->aPos );
/*N*/          }
/*N*/      }
/*N*/  }


/*N*/ void ScDocument::CalcAll()
/*N*/ {
/*N*/ 	BOOL bOldAutoCalc = GetAutoCalc();
/*N*/ 	SetAutoCalc( TRUE );
/*N*/ 	USHORT i;
/*N*/ 	for (i=0; i<=MAXTAB; i++)
/*N*/ 		if (pTab[i]) pTab[i]->SetDirtyVar();
/*N*/ 	for (i=0; i<=MAXTAB; i++)
/*N*/ 		if (pTab[i]) pTab[i]->CalcAll();
/*N*/ 	ClearFormulaTree();
/*N*/ 	SetAutoCalc( bOldAutoCalc );
/*N*/ }


//STRIP001 void ScDocument::CompileAll()
//STRIP001 {
//STRIP001 	if ( pCondFormList )
//STRIP001 		pCondFormList->CompileAll();
//STRIP001 
//STRIP001 	for (USHORT i=0; i<=MAXTAB; i++)
//STRIP001 		if (pTab[i]) pTab[i]->CompileAll();
//STRIP001 	SetDirty();
//STRIP001 }


/*N*/ void ScDocument::CompileXML()
/*N*/ {
/*N*/ 	BOOL bOldAutoCalc = GetAutoCalc();
/*N*/ 	SetAutoCalc( FALSE );
/*N*/     ScProgress aProgress( GetDocumentShell(), ScGlobal::GetRscString(
/*N*/                 STR_PROGRESS_CALCULATING ), GetXMLImportedFormulaCount() );
/*N*/ 
/*N*/ 	for (USHORT i=0; i<=MAXTAB; i++)
/*N*/ 		if (pTab[i]) pTab[i]->CompileXML( aProgress );
/*N*/ 
/*N*/ 	if ( pCondFormList )
/*N*/ 		pCondFormList->CompileXML();
/*N*/ 	if ( pValidationList )
/*N*/ 		pValidationList->CompileXML();
/*N*/ 
/*N*/ 	SetDirty();
/*N*/ 	SetAutoCalc( bOldAutoCalc );
/*N*/ }


/*N*/ void ScDocument::CalcAfterLoad()
/*N*/ {
/*N*/ 	if (bIsClip)	// Excel-Dateien werden aus dem Clipboard in ein Clip-Doc geladen
/*N*/ 		return;		// dann wird erst beim Einfuegen in das richtige Doc berechnet
/*N*/ 
/*N*/ 	bCalcingAfterLoad = TRUE;
/*N*/ 	USHORT i=0;
/*N*/ 	for (i=0; i<=MAXTAB; i++)
/*N*/ 		if (pTab[i]) pTab[i]->CalcAfterLoad();
/*N*/ 	for (i=0; i<=MAXTAB; i++)
/*N*/ 		if (pTab[i]) pTab[i]->SetDirtyAfterLoad();
/*N*/ 	bCalcingAfterLoad = FALSE;
/*N*/ 
/*N*/ 	SetDetectiveDirty(FALSE);	// noch keine wirklichen Aenderungen
/*N*/ }


/*N*/ void ScDocument::GetErrCode( USHORT nCol, USHORT nRow, USHORT nTab, USHORT& rErrCode )
/*N*/ {
/*N*/ 	if ( VALIDTAB(nTab) && pTab[nTab] )
/*N*/ 		rErrCode = pTab[nTab]->GetErrCode( nCol, nRow );
/*N*/ 	else
/*N*/ 		rErrCode = 0;
/*N*/ }


/*N*/ USHORT ScDocument::GetErrCode( const ScAddress& rPos ) const
/*N*/ {
/*N*/ 	USHORT nTab = rPos.Tab();
/*N*/ 	if ( pTab[nTab] )
/*N*/ 		return pTab[nTab]->GetErrCode( rPos );
/*N*/ 	return 0;
/*N*/ }


/*N*/ void ScDocument::ResetChanged( const ScRange& rRange )
/*N*/ {
/*N*/ 	USHORT nStartTab = rRange.aStart.Tab();
/*N*/ 	USHORT nEndTab = rRange.aEnd.Tab();
/*N*/ 	for (USHORT nTab=nStartTab; nTab<=nEndTab; nTab++)
/*N*/ 		if (pTab[nTab])
/*N*/ 			pTab[nTab]->ResetChanged( rRange );
/*N*/ }

//
//	Spaltenbreiten / Zeilenhoehen	--------------------------------------
//


/*N*/ void ScDocument::SetColWidth( USHORT nCol, USHORT nTab, USHORT nNewWidth )
/*N*/ {
/*N*/ 	if ( nTab<=MAXTAB && pTab[nTab] )
/*N*/ 		pTab[nTab]->SetColWidth( nCol, nNewWidth );
/*N*/ }


//STRIP001 void ScDocument::SetRowHeight( USHORT nRow, USHORT nTab, USHORT nNewHeight )
//STRIP001 {
//STRIP001 	if ( nTab<=MAXTAB && pTab[nTab] )
//STRIP001 		pTab[nTab]->SetRowHeight( nRow, nNewHeight );
//STRIP001 }


/*N*/ void ScDocument::SetRowHeightRange( USHORT nStartRow, USHORT nEndRow, USHORT nTab, USHORT nNewHeight )
/*N*/ {
/*N*/ 	if ( nTab<=MAXTAB && pTab[nTab] )
/*N*/ 		pTab[nTab]->SetRowHeightRange
/*N*/ 			( nStartRow, nEndRow, nNewHeight, 1.0, 1.0 );
/*N*/ }


/*N*/ void ScDocument::SetManualHeight( USHORT nStartRow, USHORT nEndRow, USHORT nTab, BOOL bManual )
/*N*/ {
/*N*/ 	if ( nTab<=MAXTAB && pTab[nTab] )
/*N*/ 		pTab[nTab]->SetManualHeight( nStartRow, nEndRow, bManual );
/*N*/ }


/*N*/ USHORT ScDocument::GetColWidth( USHORT nCol, USHORT nTab ) const
/*N*/ {
/*N*/ 	if ( nTab<=MAXTAB && pTab[nTab] )
/*N*/ 		return pTab[nTab]->GetColWidth( nCol );
/*N*/ 	DBG_ERROR("Falsche Tabellennummer");
/*N*/ 	return 0;
/*N*/ }


/*N*/ USHORT ScDocument::GetOriginalWidth( USHORT nCol, USHORT nTab ) const
/*N*/ {
/*N*/ 	if ( nTab<=MAXTAB && pTab[nTab] )
/*N*/ 		return pTab[nTab]->GetOriginalWidth( nCol );
/*N*/ 	DBG_ERROR("Falsche Tabellennummer");
/*N*/ 	return 0;
/*N*/ }


//STRIP001 USHORT ScDocument::GetCommonWidth( USHORT nEndCol, USHORT nTab ) const
//STRIP001 {
//STRIP001 	if ( nTab<=MAXTAB && pTab[nTab] )
//STRIP001 		return pTab[nTab]->GetCommonWidth( nEndCol );
//STRIP001 	DBG_ERROR("Wrong table number");
//STRIP001 	return 0;
//STRIP001 }


/*N*/ USHORT ScDocument::GetOriginalHeight( USHORT nRow, USHORT nTab ) const
/*N*/ {
/*N*/ 	if ( nTab<=MAXTAB && pTab[nTab] )
/*N*/ 		return pTab[nTab]->GetOriginalHeight( nRow );
/*N*/ 	DBG_ERROR("Wrong table number");
/*N*/ 	return 0;
/*N*/ }


/*N*/ USHORT ScDocument::GetRowHeight( USHORT nRow, USHORT nTab ) const
/*N*/ {
/*N*/ 	if ( nTab<=MAXTAB && pTab[nTab] )
/*N*/ 		return pTab[nTab]->GetRowHeight( nRow );
/*N*/ 	DBG_ERROR("Falsche Tabellennummer");
/*N*/ 	return 0;
/*N*/ }


/*N*/ USHORT ScDocument::GetHiddenRowCount( USHORT nRow, USHORT nTab ) const
/*N*/ {
/*N*/ 	if ( nTab<=MAXTAB && pTab[nTab] )
/*N*/ 		return pTab[nTab]->GetHiddenRowCount( nRow );
/*N*/ 	DBG_ERROR("Falsche Tabellennummer");
/*N*/ 	return 0;
/*N*/ }


//STRIP001 ULONG ScDocument::GetColOffset( USHORT nCol, USHORT nTab ) const
//STRIP001 {
//STRIP001 	if ( nTab<=MAXTAB && pTab[nTab] )
//STRIP001 		return pTab[nTab]->GetColOffset( nCol );
//STRIP001 	DBG_ERROR("Falsche Tabellennummer");
//STRIP001 	return 0;
//STRIP001 }


//STRIP001 ULONG ScDocument::GetRowOffset( USHORT nRow, USHORT nTab ) const
//STRIP001 {
//STRIP001 	if ( nTab<=MAXTAB && pTab[nTab] )
//STRIP001 		return pTab[nTab]->GetRowOffset( nRow );
//STRIP001 	DBG_ERROR("Falsche Tabellennummer");
//STRIP001 	return 0;
//STRIP001 }


/*N*/ USHORT ScDocument::GetOptimalColWidth( USHORT nCol, USHORT nTab, OutputDevice* pDev,
/*N*/ 										double nPPTX, double nPPTY,
/*N*/ 										const Fraction& rZoomX, const Fraction& rZoomY,
/*N*/ 										BOOL bFormula, const ScMarkData* pMarkData,
/*N*/ 										BOOL bSimpleTextImport )
/*N*/ {
/*N*/ 	if ( nTab<=MAXTAB && pTab[nTab] )
/*N*/ 		return pTab[nTab]->GetOptimalColWidth( nCol, pDev, nPPTX, nPPTY,
/*N*/ 			rZoomX, rZoomY, bFormula, pMarkData, bSimpleTextImport );
/*N*/ 	DBG_ERROR("Falsche Tabellennummer");
/*N*/ 	return 0;
/*N*/ }


//STRIP001 long ScDocument::GetNeededSize( USHORT nCol, USHORT nRow, USHORT nTab,
//STRIP001 									OutputDevice* pDev,
//STRIP001 									double nPPTX, double nPPTY,
//STRIP001 									const Fraction& rZoomX, const Fraction& rZoomY,
//STRIP001 									BOOL bWidth, BOOL bTotalSize )
//STRIP001 {
//STRIP001 	if ( nTab<=MAXTAB && pTab[nTab] )
//STRIP001 		return pTab[nTab]->GetNeededSize
//STRIP001 				( nCol, nRow, pDev, nPPTX, nPPTY, rZoomX, rZoomY, bWidth, bTotalSize );
//STRIP001 	DBG_ERROR("Falsche Tabellennummer");
//STRIP001 	return 0;
//STRIP001 }


/*N*/ BOOL ScDocument::SetOptimalHeight( USHORT nStartRow, USHORT nEndRow, USHORT nTab, USHORT nExtra,
/*N*/ 									OutputDevice* pDev,
/*N*/ 									double nPPTX, double nPPTY,
/*N*/ 									const Fraction& rZoomX, const Fraction& rZoomY,
/*N*/ 									BOOL bShrink )
/*N*/ {
/*N*/ //!	MarkToMulti();
/*N*/ 	if ( nTab<=MAXTAB && pTab[nTab] )
/*N*/ 		return pTab[nTab]->SetOptimalHeight( nStartRow, nEndRow, nExtra,
/*N*/ 												pDev, nPPTX, nPPTY, rZoomX, rZoomY, bShrink );
/*N*/ 	DBG_ERROR("Falsche Tabellennummer");
/*N*/ 	return FALSE;
/*N*/ }


//
//	Spalten-/Zeilen-Flags	----------------------------------------------
//

/*N*/ void ScDocument::ShowCol(USHORT nCol, USHORT nTab, BOOL bShow)
/*N*/ {
/*N*/ 	if ( nTab<=MAXTAB && pTab[nTab] )
/*N*/ 		pTab[nTab]->ShowCol( nCol, bShow );
/*N*/ }


/*N*/ void ScDocument::ShowRow(USHORT nRow, USHORT nTab, BOOL bShow)
/*N*/ {
/*N*/ 	if ( nTab<=MAXTAB && pTab[nTab] )
/*N*/ 		pTab[nTab]->ShowRow( nRow, bShow );
/*N*/ }


/*N*/ void ScDocument::ShowRows(USHORT nRow1, USHORT nRow2, USHORT nTab, BOOL bShow)
/*N*/ {
/*N*/ 	if ( nTab<=MAXTAB && pTab[nTab] )
/*N*/ 		pTab[nTab]->ShowRows( nRow1, nRow2, bShow );
/*N*/ }


//STRIP001 void ScDocument::SetColFlags( USHORT nCol, USHORT nTab, BYTE nNewFlags )
//STRIP001 {
//STRIP001 	if ( nTab<=MAXTAB && pTab[nTab] )
//STRIP001 		pTab[nTab]->SetColFlags( nCol, nNewFlags );
//STRIP001 }


/*N*/ void ScDocument::SetRowFlags( USHORT nRow, USHORT nTab, BYTE nNewFlags )
/*N*/ {
/*N*/ 	if ( nTab<=MAXTAB && pTab[nTab] )
/*N*/ 		pTab[nTab]->SetRowFlags( nRow, nNewFlags );
/*N*/ }


/*N*/ BYTE ScDocument::GetColFlags( USHORT nCol, USHORT nTab ) const
/*N*/ {
/*N*/ 	if ( nTab<=MAXTAB && pTab[nTab] )
/*N*/ 		return pTab[nTab]->GetColFlags( nCol );
/*N*/ 	DBG_ERROR("Falsche Tabellennummer");
/*N*/ 	return 0;
/*N*/ }

/*N*/ BYTE ScDocument::GetRowFlags( USHORT nRow, USHORT nTab ) const
/*N*/ {
/*N*/ 	if ( nTab<=MAXTAB && pTab[nTab] )
/*N*/ 		return pTab[nTab]->GetRowFlags( nRow );
/*N*/ 	DBG_ERROR("Falsche Tabellennummer");
/*N*/ 	return 0;
/*N*/ }


//STRIP001 USHORT ScDocument::GetLastFlaggedCol( USHORT nTab ) const
//STRIP001 {
//STRIP001 	if ( nTab<=MAXTAB && pTab[nTab] )
//STRIP001 		return pTab[nTab]->GetLastFlaggedCol();
//STRIP001 	return 0;
//STRIP001 }

//STRIP001 USHORT ScDocument::GetLastFlaggedRow( USHORT nTab ) const
//STRIP001 {
//STRIP001 	if ( nTab<=MAXTAB && pTab[nTab] )
//STRIP001 		return pTab[nTab]->GetLastFlaggedRow();
//STRIP001 	return 0;
//STRIP001 }


/*N*/ USHORT ScDocument::GetLastChangedCol( USHORT nTab ) const
/*N*/ {
/*N*/ 	if ( nTab<=MAXTAB && pTab[nTab] )
/*N*/         return pTab[nTab]->GetLastChangedCol();
/*N*/ 	return 0;
/*N*/ }

/*N*/ USHORT ScDocument::GetLastChangedRow( USHORT nTab ) const
/*N*/ {
/*N*/ 	if ( nTab<=MAXTAB && pTab[nTab] )
/*N*/         return pTab[nTab]->GetLastChangedRow();
/*N*/ 	return 0;
/*N*/ }


/*N*/ USHORT ScDocument::GetNextDifferentChangedCol( USHORT nTab, USHORT nStart) const
/*N*/ {
/*N*/ 	if ( nTab<=MAXTAB && pTab[nTab] )
/*N*/ 	{
/*N*/ 		BYTE nStartFlags = pTab[nTab]->GetColFlags(nStart);
/*N*/ 		USHORT nStartWidth = pTab[nTab]->GetOriginalWidth(nStart);
/*N*/ 		for (USHORT nCol = nStart + 1; nCol <= MAXCOL; nCol++)
/*N*/ 		{
/*N*/ 			if (((nStartFlags & CR_MANUALBREAK) != (pTab[nTab]->GetColFlags(nCol) & CR_MANUALBREAK)) ||
/*N*/ 				(nStartWidth != pTab[nTab]->GetOriginalWidth(nCol)) ||
/*N*/ 				((nStartFlags & CR_HIDDEN) != (pTab[nTab]->GetColFlags(nCol) & CR_HIDDEN)) )
/*N*/ 				return nCol;
/*N*/ 		}
/*N*/ 		return MAXCOL;
/*N*/ 	}
/*N*/ 	return 0;
/*N*/ }

/*N*/ USHORT ScDocument::GetNextDifferentChangedRow( USHORT nTab, USHORT nStart, bool bCareManualSize) const
/*N*/ {
/*N*/ 	if ( nTab<=MAXTAB && pTab[nTab] )
/*N*/ 	{
/*N*/ 		BYTE nStartFlags = pTab[nTab]->GetRowFlags(nStart);
/*N*/ 		USHORT nStartHeight = pTab[nTab]->GetOriginalHeight(nStart);
/*N*/ 		for (USHORT nRow = nStart + 1; nRow <= MAXROW; nRow++)
/*N*/ 		{
/*N*/ 			if (((nStartFlags & CR_MANUALBREAK) != (pTab[nTab]->GetRowFlags(nRow) & CR_MANUALBREAK)) ||
/*N*/ 				((nStartFlags & CR_MANUALSIZE) != (pTab[nTab]->GetRowFlags(nRow) & CR_MANUALSIZE)) ||
/*N*/ 				(bCareManualSize && (nStartFlags & CR_MANUALSIZE) && (nStartHeight != pTab[nTab]->GetOriginalHeight(nRow))) ||
/*N*/                 (!bCareManualSize && ((nStartHeight != pTab[nTab]->GetOriginalHeight(nRow)))))
/*N*/ 				return nRow;
/*N*/ 		}
/*N*/ 		return MAXROW;
/*N*/ 	}
/*N*/ 	return 0;
/*N*/ }

/*N*/ BOOL ScDocument::GetColDefault( USHORT nTab, USHORT nCol, USHORT nLastRow, USHORT& nDefault)
/*N*/ {
/*N*/ 	BOOL bRet(FALSE);
/*N*/ 	nDefault = 0;
/*N*/ 	ScDocAttrIterator aDocAttrItr(this, nTab, nCol, 0, nCol, nLastRow);
/*N*/ 	USHORT nColumn, nStartRow, nEndRow;
/*N*/ 	const ScPatternAttr* pAttr = aDocAttrItr.GetNext(nColumn, nStartRow, nEndRow);
/*N*/ 	if (nEndRow < nLastRow)
/*N*/ 	{
/*N*/ 		ScDefaultAttrSet aSet;
/*N*/ 		ScDefaultAttrSet::iterator aItr = aSet.end();
/*N*/ 		while (pAttr)
/*N*/ 		{
/*N*/ 			ScDefaultAttr aAttr(pAttr);
/*N*/ 			aItr = aSet.find(aAttr);
/*N*/ 			if (aItr == aSet.end())
/*N*/ 			{
/*N*/ 				aAttr.nCount = nEndRow - nStartRow + 1;
/*N*/ 				aAttr.nFirst = nStartRow;
/*N*/ 				aSet.insert(aAttr);
/*N*/ 			}
/*N*/ 			else
/*N*/ 			{
/*N*/ 				aAttr.nCount = aItr->nCount + nEndRow - nStartRow + 1;
/*N*/ 				aAttr.nFirst = aItr->nFirst;
/*N*/ 				aSet.erase(aItr);
/*N*/ 				aSet.insert(aAttr);
/*N*/ 			}
/*N*/ 			pAttr = aDocAttrItr.GetNext(nColumn, nStartRow, nEndRow);
/*N*/ 		}
/*N*/ 		ScDefaultAttrSet::iterator aDefaultItr = aSet.begin();
/*N*/ 		aItr = aDefaultItr;
/*N*/ 		aItr++;
/*N*/ 		while (aItr != aSet.end())
/*N*/ 		{
/*N*/ 			if (aItr->nCount > aDefaultItr->nCount)
/*N*/ 				aDefaultItr = aItr;
/*N*/ 			aItr++;
/*N*/ 		}
/*N*/ 		nDefault = aDefaultItr->nFirst;
/*N*/ 		bRet = TRUE;
/*N*/ 	}
/*N*/ 	else
/*N*/ 		bRet = TRUE;
/*N*/ 	return bRet;
/*N*/ }

/*N*/ BOOL ScDocument::GetRowDefault( USHORT nTab, USHORT nRow, USHORT nLastCol, USHORT& nDefault)
/*N*/ {
/*N*/ 	BOOL bRet(FALSE);
/*N*/ 	return bRet;
/*N*/ }

/*N*/ void ScDocument::StripHidden( USHORT& rX1, USHORT& rY1, USHORT& rX2, USHORT& rY2, USHORT nTab )
/*N*/ {
/*N*/ 	if ( nTab<=MAXTAB && pTab[nTab] )
/*N*/ 		pTab[nTab]->StripHidden( rX1, rY1, rX2, rY2 );
/*N*/ }


/*N*/ void ScDocument::ExtendHidden( USHORT& rX1, USHORT& rY1, USHORT& rX2, USHORT& rY2, USHORT nTab )
/*N*/ {
/*N*/ 	if ( nTab<=MAXTAB && pTab[nTab] )
/*N*/ 		pTab[nTab]->ExtendHidden( rX1, rY1, rX2, rY2 );
/*N*/ }

//
//	Attribute	----------------------------------------------------------
//

/*N*/ const SfxPoolItem* ScDocument::GetAttr( USHORT nCol, USHORT nRow, USHORT nTab, USHORT nWhich ) const
/*N*/ {
/*N*/ 	if ( nTab <= MAXTAB && pTab[nTab] )
/*N*/ 	{
/*N*/ 		const SfxPoolItem* pTemp = pTab[nTab]->GetAttr( nCol, nRow, nWhich );
/*N*/ 		if (pTemp)
/*N*/ 			return pTemp;
/*N*/ 		else
/*N*/ 			DBG_ERROR( "Attribut Null" );
/*N*/ 	}
/*N*/ 	return &xPoolHelper->GetDocPool()->GetDefaultItem( nWhich );
/*N*/ }


/*N*/ const ScPatternAttr* ScDocument::GetPattern( USHORT nCol, USHORT nRow, USHORT nTab ) const
/*N*/ {
/*N*/ 	if ( nTab <= MAXTAB && pTab[nTab] )
/*N*/ 		return pTab[nTab]->GetPattern( nCol, nRow );
/*N*/ 	return NULL;
/*N*/ }


/*N*/ void ScDocument::ApplyAttr( USHORT nCol, USHORT nRow, USHORT nTab, const SfxPoolItem& rAttr )
/*N*/ {
/*N*/ 	if ( nTab <= MAXTAB && pTab[nTab] )
/*N*/ 		pTab[nTab]->ApplyAttr( nCol, nRow, rAttr );
/*N*/ }


//STRIP001 void ScDocument::ApplyPattern( USHORT nCol, USHORT nRow, USHORT nTab, const ScPatternAttr& rAttr )
//STRIP001 {
//STRIP001 	if ( nTab <= MAXTAB && pTab[nTab] )
//STRIP001 		pTab[nTab]->ApplyPattern( nCol, nRow, rAttr );
//STRIP001 }


/*N*/ void ScDocument::ApplyPatternArea( USHORT nStartCol, USHORT nStartRow,
/*N*/ 						USHORT nEndCol, USHORT nEndRow,
/*N*/ 						const ScMarkData& rMark,
/*N*/ 						const ScPatternAttr& rAttr )
/*N*/ {
/*N*/ 	for (USHORT i=0; i <= MAXTAB; i++)
/*N*/ 		if (pTab[i])
/*N*/ 			if (rMark.GetTableSelect(i))
/*N*/ 				pTab[i]->ApplyPatternArea( nStartCol, nStartRow, nEndCol, nEndRow, rAttr );
/*N*/ }


/*N*/ void ScDocument::ApplyPatternAreaTab( USHORT nStartCol, USHORT nStartRow,
/*N*/ 						USHORT nEndCol, USHORT nEndRow, USHORT nTab, const ScPatternAttr& rAttr )
/*N*/ {
/*N*/ 	if (VALIDTAB(nTab))
/*N*/ 		if (pTab[nTab])
/*N*/ 			pTab[nTab]->ApplyPatternArea( nStartCol, nStartRow, nEndCol, nEndRow, rAttr );
/*N*/ }

//STRIP001 void ScDocument::ApplyPatternIfNumberformatIncompatible( const ScRange& rRange,
//STRIP001 		const ScMarkData& rMark, const ScPatternAttr& rPattern, short nNewType )
//STRIP001 {
//STRIP001 	for (USHORT i=0; i <= MAXTAB; i++)
//STRIP001 		if (pTab[i])
//STRIP001 			if (rMark.GetTableSelect(i))
//STRIP001 				pTab[i]->ApplyPatternIfNumberformatIncompatible( rRange, rPattern, nNewType );
//STRIP001 }


//STRIP001 void ScDocument::ApplyStyle( USHORT nCol, USHORT nRow, USHORT nTab, const ScStyleSheet& rStyle)
//STRIP001 {
//STRIP001 	if (VALIDTAB(nTab))
//STRIP001 		if (pTab[nTab])
//STRIP001 			pTab[nTab]->ApplyStyle( nCol, nRow, rStyle );
//STRIP001 }


/*N*/ void ScDocument::ApplyStyleArea( USHORT nStartCol, USHORT nStartRow,
/*N*/ 						USHORT nEndCol, USHORT nEndRow,
/*N*/ 						const ScMarkData& rMark,
/*N*/ 						const ScStyleSheet& rStyle)
/*N*/ {
/*N*/ 	for (USHORT i=0; i <= MAXTAB; i++)
/*N*/ 		if (pTab[i])
/*N*/ 			if (rMark.GetTableSelect(i))
/*N*/ 				pTab[i]->ApplyStyleArea( nStartCol, nStartRow, nEndCol, nEndRow, rStyle );
/*N*/ }


/*N*/ void ScDocument::ApplyStyleAreaTab( USHORT nStartCol, USHORT nStartRow,
/*N*/ 						USHORT nEndCol, USHORT nEndRow, USHORT nTab, const ScStyleSheet& rStyle)
/*N*/ {
/*N*/ 	if (VALIDTAB(nTab))
/*N*/ 		if (pTab[nTab])
/*N*/ 			pTab[nTab]->ApplyStyleArea( nStartCol, nStartRow, nEndCol, nEndRow, rStyle );
/*N*/ }


/*N*/ void ScDocument::ApplySelectionStyle(const ScStyleSheet& rStyle, const ScMarkData& rMark)
/*N*/ {
/*N*/ 	// ApplySelectionStyle needs multi mark
/*N*/ 	if ( rMark.IsMarked() && !rMark.IsMultiMarked() )
/*N*/ 	{
/*N*/ 		ScRange aRange;
/*N*/ 		rMark.GetMarkArea( aRange );
/*N*/ 		ApplyStyleArea( aRange.aStart.Col(), aRange.aStart.Row(),
/*N*/ 						  aRange.aEnd.Col(), aRange.aEnd.Row(), rMark, rStyle );
/*N*/ 	}
/*N*/ 	else
/*N*/ 	{
/*N*/ 		for (USHORT i=0; i<=MAXTAB; i++)
/*N*/ 			if ( pTab[i] && rMark.GetTableSelect(i) )
/*N*/ 					pTab[i]->ApplySelectionStyle( rStyle, rMark );
/*N*/ 	}
/*N*/ }


//STRIP001 void ScDocument::ApplySelectionLineStyle( const ScMarkData& rMark,
//STRIP001 					const SvxBorderLine* pLine, BOOL bColorOnly )
//STRIP001 {
//STRIP001 	if ( bColorOnly && !pLine )
//STRIP001 		return;
//STRIP001 
//STRIP001 	for (USHORT i=0; i<=MAXTAB; i++)
//STRIP001 		if (pTab[i])
//STRIP001 			if (rMark.GetTableSelect(i))
//STRIP001 				pTab[i]->ApplySelectionLineStyle( rMark, pLine, bColorOnly );
//STRIP001 }


/*N*/ const ScStyleSheet*	ScDocument::GetStyle( USHORT nCol, USHORT nRow, USHORT nTab ) const
/*N*/ {
/*N*/ 	if ( VALIDTAB(nTab) && pTab[nTab] )
/*N*/ 		return pTab[nTab]->GetStyle(nCol, nRow);
/*N*/ 	else
/*N*/ 		return NULL;
/*N*/ }


/*N*/ const ScStyleSheet*	ScDocument::GetSelectionStyle( const ScMarkData& rMark ) const
/*N*/ {
/*N*/ 	BOOL	bEqual = TRUE;
/*N*/ 	BOOL	bFound;
/*N*/ 	USHORT	i;
/*N*/ 
/*N*/ 	const ScStyleSheet* pStyle = NULL;
/*N*/ 	const ScStyleSheet* pNewStyle;
/*N*/ 
/*N*/ 	if ( rMark.IsMultiMarked() )
/*N*/ 		for (i=0; i<=MAXTAB && bEqual; i++)
/*N*/ 			if (pTab[i] && rMark.GetTableSelect(i))
/*N*/ 			{
/*N*/ 				pNewStyle = pTab[i]->GetSelectionStyle( rMark, bFound );
/*N*/ 				if (bFound)
/*N*/ 				{
/*N*/ 					if ( !pNewStyle || ( pStyle && pNewStyle != pStyle ) )
/*N*/ 						bEqual = FALSE;												// unterschiedliche
/*N*/ 					pStyle = pNewStyle;
/*N*/ 				}
/*N*/ 			}
/*N*/ 	if ( rMark.IsMarked() )
/*N*/ 	{
/*N*/ 		ScRange aRange;
/*N*/ 		rMark.GetMarkArea( aRange );
/*N*/ 		for (i=aRange.aStart.Tab(); i<=aRange.aEnd.Tab() && bEqual; i++)
/*N*/ 			if (pTab[i] && rMark.GetTableSelect(i))
/*N*/ 			{
/*N*/ 				pNewStyle = pTab[i]->GetAreaStyle( bFound,
/*N*/ 										aRange.aStart.Col(), aRange.aStart.Row(),
/*N*/ 										aRange.aEnd.Col(),   aRange.aEnd.Row()   );
/*N*/ 				if (bFound)
/*N*/ 				{
/*N*/ 					if ( !pNewStyle || ( pStyle && pNewStyle != pStyle ) )
/*N*/ 						bEqual = FALSE;												// unterschiedliche
/*N*/ 					pStyle = pNewStyle;
/*N*/ 				}
/*N*/ 			}
/*N*/ 	}
/*N*/ 
/*N*/ 	return bEqual ? pStyle : NULL;
/*N*/ }


/*N*/ void ScDocument::StyleSheetChanged( const SfxStyleSheetBase* pStyleSheet, BOOL bRemoved,
/*N*/ 									OutputDevice* pDev,
/*N*/ 									double nPPTX, double nPPTY,
/*N*/ 									const Fraction& rZoomX, const Fraction& rZoomY )
/*N*/ {
/*N*/ 	for (USHORT i=0; i <= MAXTAB; i++)
/*N*/ 		if (pTab[i])
/*N*/ 			pTab[i]->StyleSheetChanged
/*N*/ 				( pStyleSheet, bRemoved, pDev, nPPTX, nPPTY, rZoomX, rZoomY );
/*N*/ 
/*N*/ 	if ( pStyleSheet && pStyleSheet->GetName() == ScGlobal::GetRscString(STR_STYLENAME_STANDARD) )
/*N*/ 	{
/*N*/ 		//	update attributes for all note objects
/*N*/ 
/*N*/ 		ScDetectiveFunc aFunc( this, 0 );
/*N*/ 		aFunc.UpdateAllComments();
/*N*/ 	}
/*N*/ }


/*N*/ BOOL ScDocument::IsStyleSheetUsed( const ScStyleSheet& rStyle, BOOL bGatherAllStyles ) const
/*N*/ {DBG_BF_ASSERT(0, "STRIP"); return FALSE; //STRIP001 
//STRIP001     if ( bStyleSheetUsageInvalid || rStyle.GetUsage() == ScStyleSheet::UNKNOWN )
//STRIP001     {
//STRIP001         if ( bGatherAllStyles )
//STRIP001         {
//STRIP001             SfxStyleSheetIterator aIter( xPoolHelper->GetStylePool(),
//STRIP001                     SFX_STYLE_FAMILY_PARA );
//STRIP001             for ( const SfxStyleSheetBase* pStyle = aIter.First(); pStyle; 
//STRIP001                                            pStyle = aIter.Next() )
//STRIP001             {
//STRIP001                 const ScStyleSheet* pScStyle = PTR_CAST( ScStyleSheet, pStyle );
//STRIP001                 if ( pScStyle )
//STRIP001                     pScStyle->SetUsage( ScStyleSheet::NOTUSED );
//STRIP001             }
//STRIP001         }
//STRIP001 
//STRIP001         BOOL bIsUsed = FALSE;
//STRIP001 
//STRIP001         for ( USHORT i=0; i<=MAXTAB; i++ )
//STRIP001         {
//STRIP001             if ( pTab[i] )
//STRIP001             {
//STRIP001                 if ( pTab[i]->IsStyleSheetUsed( rStyle, bGatherAllStyles ) )
//STRIP001                 {
//STRIP001                     if ( !bGatherAllStyles )
//STRIP001                         return TRUE;
//STRIP001                     bIsUsed = TRUE;
//STRIP001                 }
//STRIP001             }
//STRIP001         }
//STRIP001 
//STRIP001         if ( bGatherAllStyles )
//STRIP001             bStyleSheetUsageInvalid = FALSE;
//STRIP001 
//STRIP001         return bIsUsed;
//STRIP001     }
//STRIP001     
//STRIP001     return rStyle.GetUsage() == ScStyleSheet::USED;
/*N*/ }



//STRIP001 BOOL ScDocument::ApplyFlags( USHORT nStartCol, USHORT nStartRow,
//STRIP001 						USHORT nEndCol, USHORT nEndRow,
//STRIP001 						const ScMarkData& rMark,
//STRIP001 						INT16 nFlags )
//STRIP001 {
//STRIP001 	BOOL bChanged = FALSE;
//STRIP001 	for (USHORT i=0; i <= MAXTAB; i++)
//STRIP001 		if (pTab[i])
//STRIP001 			if (rMark.GetTableSelect(i))
//STRIP001 				bChanged |= pTab[i]->ApplyFlags( nStartCol, nStartRow, nEndCol, nEndRow, nFlags );
//STRIP001 	return bChanged;
//STRIP001 }


/*N*/ BOOL ScDocument::ApplyFlagsTab( USHORT nStartCol, USHORT nStartRow,
/*N*/ 						USHORT nEndCol, USHORT nEndRow, USHORT nTab, INT16 nFlags )
/*N*/ {
/*N*/ 	if (VALIDTAB(nTab))
/*N*/ 		if (pTab[nTab])
/*N*/ 			return pTab[nTab]->ApplyFlags( nStartCol, nStartRow, nEndCol, nEndRow, nFlags );
/*N*/ 
/*N*/ 	DBG_ERROR("ApplyFlags: falsche Tabelle");
/*N*/ 	return FALSE;
/*N*/ }


//STRIP001 BOOL ScDocument::RemoveFlags( USHORT nStartCol, USHORT nStartRow,
//STRIP001 						USHORT nEndCol, USHORT nEndRow,
//STRIP001 						const ScMarkData& rMark,
//STRIP001 						INT16 nFlags )
//STRIP001 {
//STRIP001 	BOOL bChanged = FALSE;
//STRIP001 	for (USHORT i=0; i <= MAXTAB; i++)
//STRIP001 		if (pTab[i])
//STRIP001 			if (rMark.GetTableSelect(i))
//STRIP001 				bChanged |= pTab[i]->RemoveFlags( nStartCol, nStartRow, nEndCol, nEndRow, nFlags );
//STRIP001 	return bChanged;
//STRIP001 }


/*N*/ BOOL ScDocument::RemoveFlagsTab( USHORT nStartCol, USHORT nStartRow,
/*N*/ 						USHORT nEndCol, USHORT nEndRow, USHORT nTab, INT16 nFlags )
/*N*/ {DBG_BF_ASSERT(0, "STRIP"); //STRIP001 
//STRIP001 	if (VALIDTAB(nTab))
//STRIP001 		if (pTab[nTab])
//STRIP001 			return pTab[nTab]->RemoveFlags( nStartCol, nStartRow, nEndCol, nEndRow, nFlags );
//STRIP001 
//STRIP001 	DBG_ERROR("RemoveFlags: falsche Tabelle");
/*N*/ 	return FALSE;
/*N*/ }


//STRIP001 void ScDocument::SetPattern( USHORT nCol, USHORT nRow, USHORT nTab, const ScPatternAttr& rAttr,
//STRIP001 								BOOL bPutToPool )
//STRIP001 {
//STRIP001 	if (VALIDTAB(nTab))
//STRIP001 		if (pTab[nTab])
//STRIP001 			pTab[nTab]->SetPattern( nCol, nRow, rAttr, bPutToPool );
//STRIP001 }


//STRIP001 void ScDocument::SetPattern( const ScAddress& rPos, const ScPatternAttr& rAttr,
//STRIP001 								BOOL bPutToPool )
//STRIP001 {
//STRIP001 	USHORT nTab = rPos.Tab();
//STRIP001 	if (pTab[nTab])
//STRIP001 		pTab[nTab]->SetPattern( rPos, rAttr, bPutToPool );
//STRIP001 }


/*N*/ ScPatternAttr* ScDocument::CreateSelectionPattern( const ScMarkData& rMark, BOOL bDeep )
/*N*/ {
/*N*/ 	SfxItemSet* pSet = NULL;
/*N*/ 	USHORT i;
/*N*/ 
/*N*/ 	if ( rMark.IsMultiMarked() )								// multi selection
/*N*/ 	{
/*N*/ 		for (i=0; i<=MAXTAB; i++)
/*N*/ 			if (pTab[i] && rMark.GetTableSelect(i))
/*N*/ 				pTab[i]->MergeSelectionPattern( &pSet, rMark, bDeep );
/*N*/ 	}
/*N*/ 	if ( rMark.IsMarked() )										// simle selection
/*N*/ 	{
/*N*/ 		ScRange aRange;
/*N*/ 		rMark.GetMarkArea(aRange);
/*N*/ 		for (i=0; i<=MAXTAB; i++)
/*N*/ 			if (pTab[i] && rMark.GetTableSelect(i))
/*N*/ 				pTab[i]->MergePatternArea( &pSet,
/*N*/ 								aRange.aStart.Col(), aRange.aStart.Row(),
/*N*/ 								aRange.aEnd.Col(), aRange.aEnd.Row(), bDeep );
/*N*/ 	}
/*N*/ 
/*N*/ 	DBG_ASSERT( pSet, "SelectionPattern Null" );
/*N*/ 	if (pSet)
/*N*/ 		return new ScPatternAttr( pSet );
/*N*/ 	else
/*?*/ 		return new ScPatternAttr( GetPool() );		// empty
/*N*/ }


/*N*/ const ScPatternAttr* ScDocument::GetSelectionPattern( const ScMarkData& rMark, BOOL bDeep )
/*N*/ {
/*N*/ 	delete pSelectionAttr;
/*N*/ 	pSelectionAttr = CreateSelectionPattern( rMark, bDeep );
/*N*/ 	return pSelectionAttr;
/*N*/ }


/*N*/ void ScDocument::GetSelectionFrame( const ScMarkData& rMark,
/*N*/ 									SvxBoxItem&		rLineOuter,
/*N*/ 									SvxBoxInfoItem&	rLineInner )
/*N*/ {
/*N*/ 	rLineOuter.SetLine(NULL, BOX_LINE_TOP);
/*N*/ 	rLineOuter.SetLine(NULL, BOX_LINE_BOTTOM);
/*N*/ 	rLineOuter.SetLine(NULL, BOX_LINE_LEFT);
/*N*/ 	rLineOuter.SetLine(NULL, BOX_LINE_RIGHT);
/*N*/ 	rLineOuter.SetDistance(0);
/*N*/ 
/*N*/ 	rLineInner.SetLine(NULL, BOXINFO_LINE_HORI);
/*N*/ 	rLineInner.SetLine(NULL, BOXINFO_LINE_VERT);
/*N*/ 	rLineInner.SetTable(TRUE);
/*N*/ 	rLineInner.SetDist((BOOL)FALSE);
/*N*/ 	rLineInner.SetMinDist(FALSE);
/*N*/ 
/*N*/ 	ScLineFlags aFlags;
/*N*/ 
/*N*/ 	if (rMark.IsMarked())
/*N*/ 	{
/*N*/ 		ScRange aRange;
/*N*/ 		rMark.GetMarkArea(aRange);
/*N*/ 		rLineInner.SetTable(aRange.aStart!=aRange.aEnd);
/*N*/ 		for (USHORT i=0; i<=MAXTAB; i++)
/*N*/ 			if (pTab[i] && rMark.GetTableSelect(i))
/*N*/ 				pTab[i]->MergeBlockFrame( &rLineOuter, &rLineInner, aFlags,
/*N*/ 										  aRange.aStart.Col(), aRange.aStart.Row(),
/*N*/ 										  aRange.aEnd.Col(),   aRange.aEnd.Row() );
/*N*/ 	}
/*N*/ 
/*N*/ 		//	Don't care Status auswerten
/*N*/ 
/*N*/ 	rLineInner.SetValid( VALID_LEFT,   ( aFlags.nLeft != SC_LINE_DONTCARE ) );
/*N*/ 	rLineInner.SetValid( VALID_RIGHT,  ( aFlags.nRight != SC_LINE_DONTCARE ) );
/*N*/ 	rLineInner.SetValid( VALID_TOP,    ( aFlags.nTop != SC_LINE_DONTCARE ) );
/*N*/ 	rLineInner.SetValid( VALID_BOTTOM, ( aFlags.nBottom != SC_LINE_DONTCARE ) );
/*N*/ 	rLineInner.SetValid( VALID_HORI,   ( aFlags.nHori != SC_LINE_DONTCARE ) );
/*N*/ 	rLineInner.SetValid( VALID_VERT,   ( aFlags.nVert != SC_LINE_DONTCARE ) );
/*N*/ }


/*N*/ BOOL ScDocument::HasAttrib( USHORT nCol1, USHORT nRow1, USHORT nTab1,
/*N*/ 							USHORT nCol2, USHORT nRow2, USHORT nTab2, USHORT nMask )
/*N*/ {
/*N*/ 	if ( nMask & HASATTR_ROTATE )
/*N*/ 	{
/*N*/ 		//	Attribut im Dokument ueberhaupt verwendet?
/*N*/ 		//	(wie in fillinfo)
/*N*/ 
/*N*/ 		ScDocumentPool* pPool = xPoolHelper->GetDocPool();
/*N*/ 
/*N*/ 		BOOL bAnyItem = FALSE;
/*N*/ 		USHORT nRotCount = pPool->GetItemCount( ATTR_ROTATE_VALUE );
/*N*/ 		for (USHORT nItem=0; nItem<nRotCount; nItem++)
/*N*/ 			if (pPool->GetItem( ATTR_ROTATE_VALUE, nItem ))
/*N*/ 			{
/*N*/ 				bAnyItem = TRUE;
/*N*/ 				break;
/*N*/ 			}
/*N*/ 		if (!bAnyItem)
/*N*/ 			nMask &= ~HASATTR_ROTATE;
/*N*/ 	}
/*N*/ 
/*N*/ 	if ( nMask & HASATTR_RTL )
/*N*/ 	{
/*?*/ 		//	first check if right-to left is in the pool at all
/*?*/ 		//	(the same item is used in cell and page format)
/*?*/ 
/*?*/ 		ScDocumentPool* pPool = xPoolHelper->GetDocPool();
/*?*/ 
/*?*/ 		BOOL bHasRtl = FALSE;
/*?*/ 		USHORT nDirCount = pPool->GetItemCount( ATTR_WRITINGDIR );
/*?*/ 		for (USHORT nItem=0; nItem<nDirCount; nItem++)
/*?*/ 		{
/*?*/ 			const SfxPoolItem* pItem = pPool->GetItem( ATTR_WRITINGDIR, nItem );
/*?*/ 			if ( pItem && ((const SvxFrameDirectionItem*)pItem)->GetValue() == FRMDIR_HORI_RIGHT_TOP )
/*?*/ 			{
/*?*/ 				bHasRtl = TRUE;
/*?*/ 				break;
/*?*/ 			}
/*?*/ 		}
/*?*/ 		if (!bHasRtl)
/*?*/ 			nMask &= ~HASATTR_RTL;
/*N*/ 	}
/*N*/ 
/*N*/ 	if (!nMask)
/*N*/ 		return FALSE;
/*N*/ 
/*N*/ 	BOOL bFound = FALSE;
/*N*/ 	for (USHORT i=nTab1; i<=nTab2 && !bFound; i++)
/*N*/ 		if (pTab[i])
/*N*/ 		{
/*N*/ 			if ( nMask & HASATTR_RTL )
/*N*/ 			{
/*?*/ 				if ( GetEditTextDirection(i) == EE_HTEXTDIR_R2L )		// sheet default
/*?*/ 					bFound = TRUE;
/*N*/ 			}
/*N*/ 
/*N*/ 			bFound |= pTab[i]->HasAttrib( nCol1, nRow1, nCol2, nRow2, nMask );
/*N*/ 		}
/*N*/ 
/*N*/ 	return bFound;
/*N*/ }

/*N*/ BOOL ScDocument::HasAttrib( const ScRange& rRange, USHORT nMask )
/*N*/ {
/*N*/ 	return HasAttrib( rRange.aStart.Col(), rRange.aStart.Row(), rRange.aStart.Tab(),
/*N*/ 					  rRange.aEnd.Col(),   rRange.aEnd.Row(),   rRange.aEnd.Tab(),
/*N*/ 					  nMask );
/*N*/ }

/*N*/ void ScDocument::FindMaxRotCol( USHORT nTab, RowInfo* pRowInfo, USHORT nArrCount,
/*N*/ 								USHORT nX1, USHORT nX2 ) const
/*N*/ {
/*N*/ 	if ( nTab <= MAXTAB && pTab[nTab] )
/*N*/ 		pTab[nTab]->FindMaxRotCol( pRowInfo, nArrCount, nX1, nX2 );
/*N*/ 	else
/*N*/ 		DBG_ERRORFILE("FindMaxRotCol: falsche Tabelle");
/*N*/ }

//STRIP001 BOOL ScDocument::HasLines( const ScRange& rRange, Rectangle& rSizes ) const
//STRIP001 {
//STRIP001 	USHORT nTab1 = rRange.aStart.Tab();
//STRIP001 	USHORT nTab2 = rRange.aEnd.Tab();
//STRIP001 	PutInOrder( nTab1, nTab2 );
//STRIP001 	BOOL bFound = FALSE;
//STRIP001 	rSizes = Rectangle(0,0,0,0);
//STRIP001 
//STRIP001 	for (USHORT i=nTab1; i<=nTab2; i++)
//STRIP001 		if (pTab[i])
//STRIP001 			if (pTab[i]->HasLines( rRange, rSizes ))
//STRIP001 				bFound = TRUE;
//STRIP001 
//STRIP001 	return bFound;
//STRIP001 }

//STRIP001 void ScDocument::GetBorderLines( USHORT nCol, USHORT nRow, USHORT nTab,
//STRIP001 						const SvxBorderLine** ppLeft, const SvxBorderLine** ppTop,
//STRIP001 						const SvxBorderLine** ppRight, const SvxBorderLine** ppBottom ) const
//STRIP001 {
//STRIP001 	//!	Seitengrenzen fuer Druck beruecksichtigen !!!!!
//STRIP001 
//STRIP001 	const SvxBoxItem* pThisAttr = (const SvxBoxItem*) GetEffItem( nCol, nRow, nTab, ATTR_BORDER );
//STRIP001 	DBG_ASSERT(pThisAttr,"wo ist das Attribut?");
//STRIP001 
//STRIP001 	const SvxBorderLine* pLeftLine   = pThisAttr->GetLeft();
//STRIP001 	const SvxBorderLine* pTopLine    = pThisAttr->GetTop();
//STRIP001 	const SvxBorderLine* pRightLine  = pThisAttr->GetRight();
//STRIP001 	const SvxBorderLine* pBottomLine = pThisAttr->GetBottom();
//STRIP001 
//STRIP001 	if ( nCol > 0 )
//STRIP001 	{
//STRIP001 		const SvxBorderLine* pOther = ((const SvxBoxItem*)
//STRIP001 								GetEffItem( nCol-1, nRow, nTab, ATTR_BORDER ))->GetRight();
//STRIP001 		if ( HasPriority( pOther, pLeftLine ) )
//STRIP001 			pLeftLine = pOther;
//STRIP001 	}
//STRIP001 	if ( nRow > 0 )
//STRIP001 	{
//STRIP001 		const SvxBorderLine* pOther = ((const SvxBoxItem*)
//STRIP001 								GetEffItem( nCol, nRow-1, nTab, ATTR_BORDER ))->GetBottom();
//STRIP001 		if ( HasPriority( pOther, pTopLine ) )
//STRIP001 			pTopLine = pOther;
//STRIP001 	}
//STRIP001 	if ( nCol < MAXCOL )
//STRIP001 	{
//STRIP001 		const SvxBorderLine* pOther = ((const SvxBoxItem*)
//STRIP001 								GetEffItem( nCol+1, nRow, nTab, ATTR_BORDER ))->GetLeft();
//STRIP001 		if ( HasPriority( pOther, pRightLine ) )
//STRIP001 			pRightLine = pOther;
//STRIP001 	}
//STRIP001 	if ( nRow < MAXROW )
//STRIP001 	{
//STRIP001 		const SvxBorderLine* pOther = ((const SvxBoxItem*)
//STRIP001 								GetEffItem( nCol, nRow+1, nTab, ATTR_BORDER ))->GetTop();
//STRIP001 		if ( HasPriority( pOther, pBottomLine ) )
//STRIP001 			pBottomLine = pOther;
//STRIP001 	}
//STRIP001 
//STRIP001 	if (ppLeft)
//STRIP001 		*ppLeft = pLeftLine;
//STRIP001 	if (ppTop)
//STRIP001 		*ppTop = pTopLine;
//STRIP001 	if (ppRight)
//STRIP001 		*ppRight = pRightLine;
//STRIP001 	if (ppBottom)
//STRIP001 		*ppBottom = pBottomLine;
//STRIP001 }

/*N*/ BOOL ScDocument::IsBlockEmpty( USHORT nTab, USHORT nStartCol, USHORT nStartRow,
/*N*/ 										USHORT nEndCol, USHORT nEndRow ) const
/*N*/ {
/*?*/ 	DBG_BF_ASSERT(0, "STRIP"); //STRIP001 if (VALIDTAB(nTab))
//STRIP001 /*?*/ 		if (pTab[nTab])
//STRIP001 /*?*/ 			return pTab[nTab]->IsBlockEmpty( nStartCol, nStartRow, nEndCol, nEndRow );
//STRIP001 /*?*/ 
//STRIP001 /*?*/ 	DBG_ERROR("Falsche Tabellennummer");
/*N*/ 	return FALSE;
/*N*/ }


/*N*/ void ScDocument::LockTable(USHORT nTab)
/*N*/ {
/*N*/ 	if ( nTab <= MAXTAB && pTab[nTab] )
/*N*/ 		pTab[nTab]->LockTable();
/*N*/ 	else
/*N*/ 		DBG_ERROR("Falsche Tabellennummer");
/*N*/ }


/*N*/ void ScDocument::UnlockTable(USHORT nTab)
/*N*/ {
/*N*/ 	if ( nTab <= MAXTAB && pTab[nTab] )
/*N*/ 		pTab[nTab]->UnlockTable();
/*N*/ 	else
/*N*/ 		DBG_ERROR("Falsche Tabellennummer");
/*N*/ }


/*N*/ BOOL ScDocument::IsBlockEditable( USHORT nTab, USHORT nStartCol, USHORT nStartRow,
/*N*/ 										USHORT nEndCol, USHORT nEndRow,
/*N*/ 										BOOL* pOnlyNotBecauseOfMatrix /* = NULL */ ) const
/*N*/ {
/*N*/ 	// import into read-only document is possible - must be extended if other filters use api
/*N*/ 	if ( pShell && pShell->IsReadOnly() && !bImportingXML )
/*N*/ 	{
/*N*/ 		if ( pOnlyNotBecauseOfMatrix )
/*N*/ 			*pOnlyNotBecauseOfMatrix = FALSE;
/*N*/ 		return FALSE;
/*N*/ 	}
/*N*/ 
/*N*/ 	if (VALIDTAB(nTab))
/*N*/ 		if (pTab[nTab])
/*N*/ 			return pTab[nTab]->IsBlockEditable( nStartCol, nStartRow, nEndCol,
/*N*/ 				nEndRow, pOnlyNotBecauseOfMatrix );
/*N*/ 
/*N*/ 	DBG_ERROR("Falsche Tabellennummer");
/*N*/ 	if ( pOnlyNotBecauseOfMatrix )
/*N*/ 		*pOnlyNotBecauseOfMatrix = FALSE;
/*N*/ 	return FALSE;
/*N*/ }


/*N*/ BOOL ScDocument::IsSelectedBlockEditable( USHORT nStartCol, USHORT nStartRow,
/*N*/ 											USHORT nEndCol, USHORT nEndRow,
/*N*/ 											const ScMarkData& rMark ) const
/*N*/ {
/*N*/ 	// import into read-only document is possible - must be extended if other filters use api
/*N*/ 	if ( pShell && pShell->IsReadOnly() && !bImportingXML )
/*N*/ 		return FALSE;
/*N*/ 
/*N*/ 	BOOL bOk = TRUE;
/*N*/ 	for (USHORT i=0; i<=MAXTAB && bOk; i++)
/*N*/ 		if (pTab[i])
/*N*/ 			if (rMark.GetTableSelect(i))
/*N*/ 				if (!pTab[i]->IsBlockEditable( nStartCol, nStartRow, nEndCol, nEndRow ))
/*N*/ 					bOk = FALSE;
/*N*/ 
/*N*/ 	return bOk;
/*N*/ }


/*N*/ BOOL ScDocument::IsSelectionEditable( const ScMarkData& rMark,
/*N*/ 			BOOL* pOnlyNotBecauseOfMatrix /* = NULL */ ) const
/*N*/ {
/*N*/ 	// import into read-only document is possible - must be extended if other filters use api
/*N*/ 	if ( pShell && pShell->IsReadOnly() && !bImportingXML )
/*N*/ 	{
/*N*/ 		if ( pOnlyNotBecauseOfMatrix )
/*N*/ 			*pOnlyNotBecauseOfMatrix = FALSE;
/*N*/ 		return FALSE;
/*N*/ 	}
/*N*/ 
/*N*/ 	ScRange aRange;
/*N*/ 	rMark.GetMarkArea(aRange);
/*N*/ 
/*N*/ 	BOOL bOk = TRUE;
/*N*/ 	BOOL bMatrix = ( pOnlyNotBecauseOfMatrix != NULL );
/*N*/ 	for ( USHORT i=0; i<=MAXTAB && (bOk || bMatrix); i++ )
/*N*/ 	{
/*N*/ 		if ( pTab[i] && rMark.GetTableSelect(i) )
/*N*/ 		{
/*N*/ 			if (rMark.IsMarked())
/*N*/ 			{
/*N*/ 				if ( !pTab[i]->IsBlockEditable( aRange.aStart.Col(),
/*N*/ 						aRange.aStart.Row(), aRange.aEnd.Col(),
/*N*/ 						aRange.aEnd.Row(), pOnlyNotBecauseOfMatrix ) )
/*N*/ 				{
/*N*/ 					bOk = FALSE;
/*N*/ 					if ( pOnlyNotBecauseOfMatrix )
/*N*/ 						bMatrix = *pOnlyNotBecauseOfMatrix;
/*N*/ 				}
/*N*/ 			}
/*N*/ 			if (rMark.IsMultiMarked())
/*N*/ 			{
/*N*/ 				if ( !pTab[i]->IsSelectionEditable( rMark, pOnlyNotBecauseOfMatrix ) )
/*N*/ 				{
/*N*/ 					bOk = FALSE;
/*N*/ 					if ( pOnlyNotBecauseOfMatrix )
/*N*/ 						bMatrix = *pOnlyNotBecauseOfMatrix;
/*N*/ 				}
/*N*/ 			}
/*N*/ 		}
/*N*/ 	}
/*N*/ 
/*N*/ 	if ( pOnlyNotBecauseOfMatrix )
/*N*/ 		*pOnlyNotBecauseOfMatrix = ( !bOk && bMatrix );
/*N*/ 
/*N*/ 	return bOk;
/*N*/ }


//STRIP001 BOOL ScDocument::IsSelectionOrBlockEditable( USHORT nTab, USHORT nStartCol, USHORT nStartRow,
//STRIP001 										USHORT nEndCol, USHORT nEndRow,
//STRIP001 										const ScMarkData& rMark ) const
//STRIP001 {
//STRIP001 	// import into read-only document is possible - must be extended if other filters use api
//STRIP001 	if ( pShell && pShell->IsReadOnly() && !bImportingXML )
//STRIP001 		return FALSE;
//STRIP001 
//STRIP001 	BOOL bOk = TRUE;
//STRIP001 	if (VALIDTAB(nTab))
//STRIP001 	{
//STRIP001 		if (pTab[nTab])
//STRIP001 		{
//STRIP001 			if (rMark.IsMarked())
//STRIP001 			{
//STRIP001 				ScRange aRange;
//STRIP001 				rMark.GetMarkArea(aRange);
//STRIP001 				bOk = pTab[nTab]->IsBlockEditable( aRange.aStart.Col(), aRange.aStart.Row(),
//STRIP001 												   aRange.aEnd.Col(),   aRange.aEnd.Row() );
//STRIP001 			}
//STRIP001 
//STRIP001 			if (bOk && rMark.IsMultiMarked())
//STRIP001 				bOk = pTab[nTab]->IsSelectionEditable( rMark );
//STRIP001 			if ( bOk && !rMark.IsMarked() && !rMark.IsMultiMarked() )
//STRIP001 				bOk = pTab[nTab]->IsBlockEditable( nStartCol, nStartRow, nEndCol, nEndRow );
//STRIP001 			return bOk;
//STRIP001 		}
//STRIP001 	}
//STRIP001 	DBG_ERROR("Falsche Tabellennummer");
//STRIP001 	return FALSE;
//STRIP001 }


//STRIP001 BOOL ScDocument::IsSelectedOrBlockEditable( USHORT nStartCol, USHORT nStartRow,
//STRIP001 											USHORT nEndCol, USHORT nEndRow,
//STRIP001 											const ScMarkData& rMark ) const
//STRIP001 {
//STRIP001 	// import into read-only document is possible - must be extended if other filters use api
//STRIP001 	if ( pShell && pShell->IsReadOnly() && !bImportingXML )
//STRIP001 		return FALSE;
//STRIP001 
//STRIP001 	BOOL bOk = TRUE;
//STRIP001 	for (USHORT i=0; i<=MAXTAB && bOk; i++)
//STRIP001 		if (pTab[i])
//STRIP001 			if (rMark.GetTableSelect(i))
//STRIP001 			{
//STRIP001 				if (rMark.IsMarked())
//STRIP001 				{
//STRIP001 					ScRange aRange;
//STRIP001 					rMark.GetMarkArea(aRange);
//STRIP001 					bOk = pTab[i]->IsBlockEditable( aRange.aStart.Col(), aRange.aStart.Row(),
//STRIP001 													aRange.aEnd.Col(),   aRange.aEnd.Row() );
//STRIP001 				}
//STRIP001 				if ( bOk && !rMark.IsMarked() )
//STRIP001 					bOk = pTab[i]->IsBlockEditable( nStartCol, nStartRow, nEndCol, nEndRow );
//STRIP001 			}
//STRIP001 
//STRIP001 	return bOk;
//STRIP001 }


//STRIP001 BOOL ScDocument::HasSelectedBlockMatrixFragment( USHORT nStartCol, USHORT nStartRow,
//STRIP001 								USHORT nEndCol, USHORT nEndRow,
//STRIP001 								const ScMarkData& rMark ) const
//STRIP001 {
//STRIP001 	BOOL bOk = TRUE;
//STRIP001 	for (USHORT i=0; i<=MAXTAB && bOk; i++)
//STRIP001 		if (pTab[i])
//STRIP001 			if (rMark.GetTableSelect(i))
//STRIP001 				if (pTab[i]->HasBlockMatrixFragment( nStartCol, nStartRow, nEndCol, nEndRow ))
//STRIP001 					bOk = FALSE;
//STRIP001 
//STRIP001 	return !bOk;
//STRIP001 }


/*N*/ BOOL ScDocument::GetMatrixFormulaRange( const ScAddress& rCellPos, ScRange& rMatrix )
/*N*/ {
/*N*/ 	//	if rCell is part of a matrix formula, return its complete range
/*N*/ 
/*N*/ 	BOOL bRet = FALSE;
/*N*/ 	ScBaseCell* pCell = GetCell( rCellPos );
/*N*/ 	if (pCell && pCell->GetCellType() == CELLTYPE_FORMULA)
/*N*/ 	{
/*N*/ 		ScAddress aOrigin = rCellPos;
/*N*/ 		if ( ((ScFormulaCell*)pCell)->GetMatrixOrigin( aOrigin ) )
/*N*/ 		{
/*N*/ 			if ( aOrigin != rCellPos )
/*N*/ 				pCell = GetCell( aOrigin );
/*N*/ 			if (pCell && pCell->GetCellType() == CELLTYPE_FORMULA)
/*N*/ 			{
/*N*/ 				USHORT nSizeX, nSizeY;
/*N*/ 				((ScFormulaCell*)pCell)->GetMatColsRows(nSizeX,nSizeY);
/*N*/ 				if ( !(nSizeX && nSizeY) )
/*N*/ 				{
/*?*/ 					// GetMatrixEdge computes also dimensions of the matrix
/*?*/ 					// if not already done (may occur if document is loaded
/*?*/ 					// from old file format).
/*?*/ 					// Needs an "invalid" initialized address.
/*?*/ 					aOrigin = UINT32(0xffffffff);
/*?*/ 					((ScFormulaCell*)pCell)->GetMatrixEdge(aOrigin);
/*?*/ 					((ScFormulaCell*)pCell)->GetMatColsRows(nSizeX,nSizeY);
/*N*/ 				}
/*N*/ 				if ( nSizeX && nSizeY )
/*N*/ 				{
/*N*/ 					ScAddress aEnd( aOrigin.Col() + nSizeX - 1,
/*N*/ 									aOrigin.Row() + nSizeY - 1,
/*N*/ 									aOrigin.Tab() );
/*N*/ 
/*N*/ 					rMatrix.aStart = aOrigin;
/*N*/ 					rMatrix.aEnd = aEnd;
/*N*/ 					bRet = TRUE;
/*N*/ 				}
/*N*/ 			}
/*N*/ 		}
/*N*/ 	}
/*N*/ 	return bRet;
/*N*/ }


/*N*/ BOOL ScDocument::ExtendOverlapped( USHORT& rStartCol, USHORT& rStartRow,
/*N*/ 								USHORT nEndCol, USHORT nEndRow, USHORT nTab )
/*N*/ {
/*N*/ 	BOOL bFound = FALSE;
/*N*/ 	if ( ValidColRow(rStartCol,rStartRow) && ValidColRow(nEndCol,nEndRow) && nTab<=MAXTAB )
/*N*/ 	{
/*N*/ 		if (pTab[nTab])
/*N*/ 		{
/*N*/ 			USHORT nCol;
/*N*/ 			USHORT nOldCol = rStartCol;
/*N*/ 			USHORT nOldRow = rStartRow;
/*N*/ 			for (nCol=nOldCol; nCol<=nEndCol; nCol++)
/*N*/ 				while (((ScMergeFlagAttr*)GetAttr(nCol,rStartRow,nTab,ATTR_MERGE_FLAG))->
/*N*/ 							IsVerOverlapped())
/*N*/ 					--rStartRow;
/*N*/ 
/*N*/ 			//!		weiterreichen ?
/*N*/ 
/*N*/ 			ScAttrArray* pAttrArray = pTab[nTab]->aCol[nOldCol].pAttrArray;
/*N*/ 			short nIndex;
/*N*/ 			pAttrArray->Search( nOldRow, nIndex );
/*N*/ 			USHORT nAttrPos = nOldRow;
/*N*/ 			while (nAttrPos<=nEndRow)
/*N*/ 			{
/*N*/ 				DBG_ASSERT( nIndex < (short) pAttrArray->nCount, "Falscher Index im AttrArray" );
/*N*/ 
/*N*/ 				if (((ScMergeFlagAttr&)pAttrArray->pData[nIndex].pPattern->
/*N*/ 						GetItem(ATTR_MERGE_FLAG)).IsHorOverlapped())
/*N*/ 				{
/*N*/ 					USHORT nLoopEndRow = Min( nEndRow, pAttrArray->pData[nIndex].nRow );
/*N*/ 					for (USHORT nAttrRow = nAttrPos; nAttrRow <= nLoopEndRow; nAttrRow++)
/*N*/ 					{
/*N*/ 						USHORT nTempCol = nOldCol;
/*N*/ 						do
/*N*/ 							--nTempCol;
/*N*/ 						while (((ScMergeFlagAttr*)GetAttr(nTempCol,nAttrRow,nTab,ATTR_MERGE_FLAG))
/*N*/ 								->IsHorOverlapped());
/*N*/ 						if (nTempCol < rStartCol)
/*N*/ 							rStartCol = nTempCol;
/*N*/ 					}
/*N*/ 				}
/*N*/ 				nAttrPos = pAttrArray->pData[nIndex].nRow + 1;
/*N*/ 				++nIndex;
/*N*/ 			}
/*N*/ 		}
/*N*/ 	}
/*N*/ 	else
/*N*/ 		DBG_ERROR("ExtendOverlapped: falscher Bereich");
/*N*/ 
/*N*/ 	return bFound;
/*N*/ }


/*N*/ BOOL ScDocument::ExtendMerge( USHORT nStartCol, USHORT nStartRow,
/*N*/ 							  USHORT& rEndCol,  USHORT& rEndRow,
/*N*/ 							  USHORT nTab, BOOL bRefresh, BOOL bAttrs )
/*N*/ {
/*N*/ 	BOOL bFound = FALSE;
/*N*/ 	if ( ValidColRow(nStartCol,nStartRow) && ValidColRow(rEndCol,rEndRow) && nTab<=MAXTAB )
/*N*/ 	{
/*N*/ 		if (pTab[nTab])
/*N*/ 			bFound = pTab[nTab]->ExtendMerge( nStartCol, nStartRow, rEndCol, rEndRow, bRefresh, bAttrs );
/*N*/ 
/*N*/ 		if (bRefresh)
DBG_BF_ASSERT(0, "STRIP"); //STRIP001 /*?*/ 			RefreshAutoFilter( nStartCol, nStartRow, rEndCol, rEndRow, nTab );
/*N*/ 	}
/*N*/ 	else
/*N*/ 		DBG_ERROR("ExtendMerge: falscher Bereich");
/*N*/ 
/*N*/ 	return bFound;
/*N*/ }


/*N*/ BOOL ScDocument::ExtendMerge( ScRange& rRange, BOOL bRefresh, BOOL bAttrs )
/*N*/ {
/*N*/ 	BOOL bFound = FALSE;
/*N*/ 	USHORT nStartTab = rRange.aStart.Tab();
/*N*/ 	USHORT nEndTab   = rRange.aEnd.Tab();
/*N*/ 	USHORT nEndCol   = rRange.aEnd.Col();
/*N*/ 	USHORT nEndRow   = rRange.aEnd.Row();
/*N*/ 
/*N*/ 	PutInOrder( nStartTab, nEndTab );
/*N*/ 	for (USHORT nTab = nStartTab; nTab <= nEndTab; nTab++ )
/*N*/ 	{
/*N*/ 		USHORT nExtendCol = rRange.aEnd.Col();
/*N*/ 		USHORT nExtendRow = rRange.aEnd.Row();
/*N*/ 		if (ExtendMerge( rRange.aStart.Col(), rRange.aStart.Row(),
/*N*/ 						 nExtendCol,          nExtendRow,
/*N*/ 						 nTab, bRefresh, bAttrs ) )
/*N*/ 		{
/*N*/ 			bFound = TRUE;
/*N*/ 			if (nExtendCol > nEndCol) nEndCol = nExtendCol;
/*N*/ 			if (nExtendRow > nEndRow) nEndRow = nExtendRow;
/*N*/ 		}
/*N*/ 	}
/*N*/ 
/*N*/ 	rRange.aEnd.SetCol(nEndCol);
/*N*/ 	rRange.aEnd.SetRow(nEndRow);
/*N*/ 
/*N*/ 	return bFound;
/*N*/ }

//STRIP001 BOOL ScDocument::ExtendTotalMerge( ScRange& rRange )
//STRIP001 {
//STRIP001 	//	Bereich genau dann auf zusammengefasste Zellen erweitern, wenn
//STRIP001 	//	dadurch keine neuen nicht-ueberdeckten Zellen getroffen werden
//STRIP001 
//STRIP001 	BOOL bRet = FALSE;
//STRIP001 	ScRange aExt = rRange;
//STRIP001 	if (ExtendMerge(aExt))
//STRIP001 	{
//STRIP001 		if ( aExt.aEnd.Row() > rRange.aEnd.Row() )
//STRIP001 		{
//STRIP001 			ScRange aTest = aExt;
//STRIP001 			aTest.aStart.SetRow( rRange.aEnd.Row() + 1 );
//STRIP001 			if ( HasAttrib( aTest, HASATTR_NOTOVERLAPPED ) )
//STRIP001 				aExt.aEnd.SetRow(rRange.aEnd.Row());
//STRIP001 		}
//STRIP001 		if ( aExt.aEnd.Col() > rRange.aEnd.Col() )
//STRIP001 		{
//STRIP001 			ScRange aTest = aExt;
//STRIP001 			aTest.aStart.SetCol( rRange.aEnd.Col() + 1 );
//STRIP001 			if ( HasAttrib( aTest, HASATTR_NOTOVERLAPPED ) )
//STRIP001 				aExt.aEnd.SetCol(rRange.aEnd.Col());
//STRIP001 		}
//STRIP001 
//STRIP001 		bRet = ( aExt.aEnd != rRange.aEnd );
//STRIP001 		rRange = aExt;
//STRIP001 	}
//STRIP001 	return bRet;
//STRIP001 }

/*N*/ BOOL ScDocument::ExtendOverlapped( ScRange& rRange )
/*N*/ {
/*N*/ 	BOOL bFound = FALSE;
/*N*/ 	USHORT nStartTab = rRange.aStart.Tab();
/*N*/ 	USHORT nEndTab   = rRange.aEnd.Tab();
/*N*/ 	USHORT nStartCol = rRange.aStart.Col();
/*N*/ 	USHORT nStartRow = rRange.aStart.Row();
/*N*/ 
/*N*/ 	PutInOrder( nStartTab, nEndTab );
/*N*/ 	for (USHORT nTab = nStartTab; nTab <= nEndTab; nTab++ )
/*N*/ 	{
/*N*/ 		USHORT nExtendCol = rRange.aStart.Col();
/*N*/ 		USHORT nExtendRow = rRange.aStart.Row();
/*N*/ 		ExtendOverlapped( nExtendCol, nExtendRow,
/*N*/ 								rRange.aEnd.Col(), rRange.aEnd.Row(), nTab );
/*N*/ 		if (nExtendCol < nStartCol)
/*N*/ 		{
/*N*/ 			nStartCol = nExtendCol;
/*N*/ 			bFound = TRUE;
/*N*/ 		}
/*N*/ 		if (nExtendRow < nStartRow)
/*N*/ 		{
/*N*/ 			nStartRow = nExtendRow;
/*N*/ 			bFound = TRUE;
/*N*/ 		}
/*N*/ 	}
/*N*/ 
/*N*/ 	rRange.aStart.SetCol(nStartCol);
/*N*/ 	rRange.aStart.SetRow(nStartRow);
/*N*/ 
/*N*/ 	return bFound;
/*N*/ }

//STRIP001 BOOL ScDocument::RefreshAutoFilter( USHORT nStartCol, USHORT nStartRow,
//STRIP001 									USHORT nEndCol, USHORT nEndRow, USHORT nTab )
//STRIP001 {
//STRIP001 	USHORT nCount = pDBCollection->GetCount();
//STRIP001 	USHORT i;
//STRIP001 	ScDBData* pData;
//STRIP001 	USHORT nDBTab;
//STRIP001 	USHORT nDBStartCol;
//STRIP001 	USHORT nDBStartRow;
//STRIP001 	USHORT nDBEndCol;
//STRIP001 	USHORT nDBEndRow;
//STRIP001 
//STRIP001 	//		Autofilter loeschen
//STRIP001 
//STRIP001 	BOOL bChange = RemoveFlagsTab( nStartCol,nStartRow, nEndCol,nEndRow, nTab, SC_MF_AUTO );
//STRIP001 
//STRIP001 	//		Autofilter setzen
//STRIP001 
//STRIP001 	for (i=0; i<nCount; i++)
//STRIP001 	{
//STRIP001 		pData = (*pDBCollection)[i];
//STRIP001 		if (pData->HasAutoFilter())
//STRIP001 		{
//STRIP001 			pData->GetArea( nDBTab, nDBStartCol,nDBStartRow, nDBEndCol,nDBEndRow );
//STRIP001 			if ( nDBTab==nTab && nDBStartRow<=nEndRow && nDBEndRow>=nStartRow &&
//STRIP001 									nDBStartCol<=nEndCol && nDBEndCol>=nStartCol )
//STRIP001 			{
//STRIP001 				if (ApplyFlagsTab( nDBStartCol,nDBStartRow, nDBEndCol,nDBStartRow,
//STRIP001 									nDBTab, SC_MF_AUTO ))
//STRIP001 					bChange = TRUE;
//STRIP001 			}
//STRIP001 		}
//STRIP001 	}
//STRIP001 	return bChange;
//STRIP001 }


/*N*/ void ScDocument::SetAutoFilterFlags()
/*N*/ {
/*N*/ 	USHORT nCount = pDBCollection->GetCount();
/*N*/ 	for (USHORT i=0; i<nCount; i++)
/*N*/ 	{
/*N*/ 		ScDBData* pData = (*pDBCollection)[i];
/*N*/ 		USHORT nDBTab;
/*N*/ 		USHORT nDBStartCol;
/*N*/ 		USHORT nDBStartRow;
/*N*/ 		USHORT nDBEndCol;
/*N*/ 		USHORT nDBEndRow;
/*N*/ 		pData->GetArea( nDBTab, nDBStartCol,nDBStartRow, nDBEndCol,nDBEndRow );
/*N*/ 		pData->SetAutoFilter( HasAttrib( nDBStartCol,nDBStartRow,nDBTab,
/*N*/ 								nDBEndCol,nDBStartRow,nDBTab, HASATTR_AUTOFILTER ) );
/*N*/ 	}
/*N*/ }


//STRIP001 BOOL ScDocument::IsOverlapped( USHORT nCol, USHORT nRow, USHORT nTab ) const
//STRIP001 {
//STRIP001 	const ScMergeFlagAttr* pAttr = (const ScMergeFlagAttr*)
//STRIP001 										GetAttr( nCol, nRow, nTab, ATTR_MERGE_FLAG );
//STRIP001 	if (pAttr)
//STRIP001 		return pAttr->IsOverlapped();
//STRIP001 	else
//STRIP001 	{
//STRIP001 		DBG_ERROR("Overlapped: Attr==0");
//STRIP001 		return FALSE;
//STRIP001 	}
//STRIP001 }


//STRIP001 BOOL ScDocument::IsHorOverlapped( USHORT nCol, USHORT nRow, USHORT nTab ) const
//STRIP001 {
//STRIP001 	const ScMergeFlagAttr* pAttr = (const ScMergeFlagAttr*)
//STRIP001 										GetAttr( nCol, nRow, nTab, ATTR_MERGE_FLAG );
//STRIP001 	if (pAttr)
//STRIP001 		return pAttr->IsHorOverlapped();
//STRIP001 	else
//STRIP001 	{
//STRIP001 		DBG_ERROR("Overlapped: Attr==0");
//STRIP001 		return FALSE;
//STRIP001 	}
//STRIP001 }


//STRIP001 BOOL ScDocument::IsVerOverlapped( USHORT nCol, USHORT nRow, USHORT nTab ) const
//STRIP001 {
//STRIP001 	const ScMergeFlagAttr* pAttr = (const ScMergeFlagAttr*)
//STRIP001 										GetAttr( nCol, nRow, nTab, ATTR_MERGE_FLAG );
//STRIP001 	if (pAttr)
//STRIP001 		return pAttr->IsVerOverlapped();
//STRIP001 	else
//STRIP001 	{
//STRIP001 		DBG_ERROR("Overlapped: Attr==0");
//STRIP001 		return FALSE;
//STRIP001 	}
//STRIP001 }


/*N*/ void ScDocument::ApplySelectionFrame( const ScMarkData& rMark,
/*N*/ 									  const SvxBoxItem* pLineOuter,
/*N*/ 									  const SvxBoxInfoItem* pLineInner )
/*N*/ {
/*N*/ 	if (rMark.IsMarked())
/*N*/ 	{
/*N*/ 		ScRange aRange;
/*N*/ 		rMark.GetMarkArea(aRange);
/*N*/ 		for (USHORT i=0; i<=MAXTAB; i++)
/*N*/ 			if (pTab[i])
/*N*/ 				if (rMark.GetTableSelect(i))
/*N*/ 					pTab[i]->ApplyBlockFrame( pLineOuter, pLineInner,
/*N*/ 												aRange.aStart.Col(), aRange.aStart.Row(),
/*N*/ 												aRange.aEnd.Col(),   aRange.aEnd.Row() );
/*N*/ 	}
/*N*/ }


//STRIP001 void ScDocument::ApplyFrameAreaTab( const ScRange& rRange,
//STRIP001 									const SvxBoxItem* pLineOuter,
//STRIP001 									const SvxBoxInfoItem* pLineInner )
//STRIP001 {
//STRIP001 	USHORT nStartTab = rRange.aStart.Tab();
//STRIP001 	USHORT nEndTab = rRange.aStart.Tab();
//STRIP001 	for (USHORT nTab=nStartTab; nTab<=nEndTab; nTab++)
//STRIP001 		if (pTab[nTab])
//STRIP001 			pTab[nTab]->ApplyBlockFrame( pLineOuter, pLineInner,
//STRIP001 										 rRange.aStart.Col(), rRange.aStart.Row(),
//STRIP001 										 rRange.aEnd.Col(),   rRange.aEnd.Row() );
//STRIP001 }


/*N*/ void ScDocument::ApplySelectionPattern( const ScPatternAttr& rAttr, const ScMarkData& rMark )
/*N*/ {
/*N*/ 	const SfxItemSet* pSet = &rAttr.GetItemSet();
/*N*/ 	BOOL bSet = FALSE;
/*N*/ 	USHORT i;
/*N*/ 	for (i=ATTR_PATTERN_START; i<=ATTR_PATTERN_END && !bSet; i++)
/*N*/ 		if (pSet->GetItemState(i) == SFX_ITEM_SET)
/*N*/ 			bSet = TRUE;
/*N*/ 
/*N*/ 	if (bSet)
/*N*/ 	{
/*N*/ 		// ApplySelectionCache needs multi mark
/*N*/ 		if ( rMark.IsMarked() && !rMark.IsMultiMarked() )
/*N*/ 		{
/*N*/ 			ScRange aRange;
/*N*/ 			rMark.GetMarkArea( aRange );
/*N*/ 			ApplyPatternArea( aRange.aStart.Col(), aRange.aStart.Row(),
/*N*/ 							  aRange.aEnd.Col(), aRange.aEnd.Row(), rMark, rAttr );
/*N*/ 		}
/*N*/ 		else
/*N*/ 		{
/*N*/ 			SfxItemPoolCache aCache( xPoolHelper->GetDocPool(), pSet );
/*N*/ 			for (USHORT i=0; i<=MAXTAB; i++)
/*N*/ 				if (pTab[i])
/*N*/ 					if (rMark.GetTableSelect(i))
/*N*/ 						pTab[i]->ApplySelectionCache( &aCache, rMark );
/*N*/ 		}
/*N*/ 	}
/*N*/ }


/*N*/ void ScDocument::ChangeSelectionIndent( BOOL bIncrement, const ScMarkData& rMark )
/*N*/ {
/*?*/ 	DBG_BF_ASSERT(0, "STRIP"); //STRIP001 for (USHORT i=0; i<=MAXTAB; i++)
//STRIP001 /*?*/ 		if (pTab[i] && rMark.GetTableSelect(i))
//STRIP001 /*?*/ 			pTab[i]->ChangeSelectionIndent( bIncrement, rMark );
/*N*/ }


/*N*/ void ScDocument::ClearSelectionItems( const USHORT* pWhich, const ScMarkData& rMark )
/*N*/ {
/*?*/ 	DBG_BF_ASSERT(0, "STRIP"); //STRIP001 for (USHORT i=0; i<=MAXTAB; i++)
//STRIP001 /*?*/ 		if (pTab[i] && rMark.GetTableSelect(i))
//STRIP001 /*?*/ 			pTab[i]->ClearSelectionItems( pWhich, rMark );
/*N*/ }


//STRIP001 void ScDocument::DeleteSelection( USHORT nDelFlag, const ScMarkData& rMark )
//STRIP001 {
//STRIP001 	for (USHORT i=0; i<=MAXTAB; i++)
//STRIP001 		if (pTab[i] && rMark.GetTableSelect(i))
//STRIP001 			pTab[i]->DeleteSelection( nDelFlag, rMark );
//STRIP001 }


//STRIP001 void ScDocument::DeleteSelectionTab( USHORT nTab, USHORT nDelFlag, const ScMarkData& rMark )
//STRIP001 {
//STRIP001 	if (nTab <= MAXTAB && pTab[nTab])
//STRIP001 		pTab[nTab]->DeleteSelection( nDelFlag, rMark );
//STRIP001 	else
//STRIP001 		DBG_ERROR("Falsche Tabelle");
//STRIP001 }


/*N*/ ScPatternAttr* ScDocument::GetDefPattern() const
/*N*/ {
/*N*/ 	return (ScPatternAttr*) &xPoolHelper->GetDocPool()->GetDefaultItem(ATTR_PATTERN);
/*N*/ }


/*N*/ ScDocumentPool* ScDocument::GetPool()
/*N*/ {
/*N*/ 	return xPoolHelper->GetDocPool();
/*N*/ }



/*N*/ ScStyleSheetPool* ScDocument::GetStyleSheetPool() const
/*N*/ {
/*N*/ 	return xPoolHelper->GetStylePool();
/*N*/ }


//STRIP001 USHORT ScDocument::GetEmptyLinesInBlock( USHORT nStartCol, USHORT nStartRow, USHORT nStartTab,
//STRIP001 							USHORT nEndCol, USHORT nEndRow, USHORT nEndTab, ScDirection eDir )
//STRIP001 {
//STRIP001 	PutInOrder(nStartCol, nEndCol);
//STRIP001 	PutInOrder(nStartRow, nEndRow);
//STRIP001 	PutInOrder(nStartTab, nEndTab);
//STRIP001 	if (VALIDTAB(nStartTab))
//STRIP001 	{
//STRIP001 		if (pTab[nStartTab])
//STRIP001 			return pTab[nStartTab]->GetEmptyLinesInBlock(nStartCol, nStartRow, nEndCol, nEndRow, eDir);
//STRIP001 		else
//STRIP001 			return 0;
//STRIP001 	}
//STRIP001 	else
//STRIP001 		return 0;
//STRIP001 }


//STRIP001 void ScDocument::FindAreaPos( USHORT& rCol, USHORT& rRow, USHORT nTab, short nMovX, short nMovY )
//STRIP001 {
//STRIP001 	if (nTab<=MAXTAB && pTab[nTab])
//STRIP001 		pTab[nTab]->FindAreaPos( rCol, rRow, nMovX, nMovY );
//STRIP001 }


/*N*/ void ScDocument::GetNextPos( USHORT& rCol, USHORT& rRow, USHORT nTab, short nMovX, short nMovY,
/*N*/ 								BOOL bMarked, BOOL bUnprotected, const ScMarkData& rMark )
/*N*/ {
/*N*/ 	DBG_ASSERT( !nMovX || !nMovY, "GetNextPos: nur X oder Y" );
/*N*/ 
/*N*/ 	ScMarkData aCopyMark = rMark;
/*N*/ 	aCopyMark.SetMarking(FALSE);
/*N*/ 	aCopyMark.MarkToMulti();
/*N*/ 
/*N*/ 	if (nTab<=MAXTAB && pTab[nTab])
/*N*/ 		pTab[nTab]->GetNextPos( rCol, rRow, nMovX, nMovY, bMarked, bUnprotected, aCopyMark );
/*N*/ }

//
//	Datei-Operationen
//


/*N*/ void ScDocument::UpdStlShtPtrsFrmNms()
/*N*/ {
/*N*/ 	ScPatternAttr::pDoc = this;
/*N*/ 
/*N*/ 	ScDocumentPool* pPool = xPoolHelper->GetDocPool();
/*N*/ 
/*N*/ 	USHORT nCount = pPool->GetItemCount(ATTR_PATTERN);
/*N*/ 	ScPatternAttr* pPattern;
/*N*/ 	for (USHORT i=0; i<nCount; i++)
/*N*/ 	{
/*N*/ 		pPattern = (ScPatternAttr*)pPool->GetItem(ATTR_PATTERN, i);
/*N*/ 		if (pPattern)
/*N*/ 			pPattern->UpdateStyleSheet();
/*N*/ 	}
/*N*/ 	((ScPatternAttr&)pPool->GetDefaultItem(ATTR_PATTERN)).UpdateStyleSheet();
/*N*/ }


//STRIP001 void ScDocument::StylesToNames()
//STRIP001 {
//STRIP001 	ScPatternAttr::pDoc = this;
//STRIP001 
//STRIP001 	ScDocumentPool* pPool = xPoolHelper->GetDocPool();
//STRIP001 
//STRIP001 	USHORT nCount = pPool->GetItemCount(ATTR_PATTERN);
//STRIP001 	ScPatternAttr* pPattern;
//STRIP001 	for (USHORT i=0; i<nCount; i++)
//STRIP001 	{
//STRIP001 		pPattern = (ScPatternAttr*)pPool->GetItem(ATTR_PATTERN, i);
//STRIP001 		if (pPattern)
//STRIP001 			pPattern->StyleToName();
//STRIP001 	}
//STRIP001 	((ScPatternAttr&)pPool->GetDefaultItem(ATTR_PATTERN)).StyleToName();
//STRIP001 }


/*N*/ void lcl_RemoveMergeFromStyles( ScStyleSheetPool* pStylePool )
/*N*/ {
/*N*/ 	pStylePool->SetSearchMask( SFX_STYLE_FAMILY_ALL );
/*N*/ 
/*N*/ 	USHORT nCount = pStylePool->Count();
/*N*/ 	for (USHORT i=0; i<nCount; i++)
/*N*/ 	{
/*N*/ 		//	in alten Versionen wurden statt SFXSTYLEBIT_USERDEF alle Bits gesetzt
/*N*/ 		SfxStyleSheetBase* pStyle = (*pStylePool)[i];
/*N*/ 		if ( pStyle->GetMask() & SFXSTYLEBIT_READONLY )
/*N*/ 			pStyle->SetMask( pStyle->GetMask() & ~SFXSTYLEBIT_READONLY );
/*N*/ 
/*N*/ 		SfxItemSet& rSet = pStyle->GetItemSet();
/*N*/ 		rSet.ClearItem( ATTR_MERGE );
/*N*/ 		rSet.ClearItem( ATTR_MERGE_FLAG );
/*N*/ 
/*N*/ 		//	Das SvxBoxInfoItem wurde bis zur 358 falsch geladen, so dass
/*N*/ 		//	Seitenvorlagen falsche Items mit bDist = FALSE enthalten koennen
/*N*/ 		if ( pStyle->GetFamily() == SFX_STYLE_FAMILY_PAGE )
/*N*/ 		{
/*N*/ 			const SvxBoxInfoItem& rPageInfo = (const SvxBoxInfoItem&)rSet.Get(ATTR_BORDER_INNER);
/*N*/ 			if ( !rPageInfo.IsDist() )
/*N*/ 			{
/*N*/ 				DBG_WARNING("altes SvxBoxInfoItem muss korrigiert werden");
/*N*/ 				SvxBoxInfoItem aNew( rPageInfo );
/*N*/ 				aNew.SetDist( TRUE );
/*N*/ 				rSet.Put( aNew );
/*N*/ 			}
/*N*/ 			//	Das gilt fuer alle Hdr/Ftr-SetItems, darum kann das SetItem auch
/*N*/ 			//	direkt im Pool geaendert werden (const weggecastet):
/*N*/ 			SfxItemSet& rHdrSet = ((SvxSetItem&)rSet.Get(ATTR_PAGE_HEADERSET)).GetItemSet();
/*N*/ 			const SvxBoxInfoItem& rHdrInfo = (const SvxBoxInfoItem&)rHdrSet.Get(ATTR_BORDER_INNER);
/*N*/ 			if ( !rHdrInfo.IsDist() )
/*N*/ 			{
/*N*/ 				DBG_WARNING("altes SvxBoxInfoItem muss korrigiert werden");
/*N*/ 				SvxBoxInfoItem aNew( rHdrInfo );
/*N*/ 				aNew.SetDist( TRUE );
/*N*/ 				rHdrSet.Put( aNew );
/*N*/ 			}
/*N*/ 			SfxItemSet& rFtrSet = ((SvxSetItem&)rSet.Get(ATTR_PAGE_FOOTERSET)).GetItemSet();
/*N*/ 			const SvxBoxInfoItem& rFtrInfo = (const SvxBoxInfoItem&)rFtrSet.Get(ATTR_BORDER_INNER);
/*N*/ 			if ( !rFtrInfo.IsDist() )
/*N*/ 			{
/*N*/ 				DBG_WARNING("altes SvxBoxInfoItem muss korrigiert werden");
/*N*/ 				SvxBoxInfoItem aNew( rFtrInfo );
/*N*/ 				aNew.SetDist( TRUE );
/*N*/ 				rFtrSet.Put( aNew );
/*N*/ 			}
/*N*/ 			const SfxUInt16Item& rScaleItem = (const SfxUInt16Item&)rSet.Get(ATTR_PAGE_SCALE);
/*N*/ 			USHORT nScale = rScaleItem.GetValue();
/*N*/ 			//! Extra-Konstanten fuer Seitenformat?
/*N*/ 			//	0 ist erlaubt (wird gesetzt bei Scale To Pages)
/*N*/ 			if ( nScale != 0 && ( nScale < MINZOOM || nScale > MAXZOOM ) )
/*N*/ 			{
/*?*/ 				//	konnte anscheinend mal irgendwie kaputtgehen (#34508#)
/*?*/ 				DBG_WARNING("kaputter Zoom im Seitenformat muss korrigiert werden");
/*?*/ 				rSet.Put( SfxUInt16Item( ATTR_PAGE_SCALE, 100 ) );
/*N*/ 			}
/*N*/ 		}
/*N*/ 	}
/*N*/ }


/*N*/ BOOL ScDocument::LoadPool( SvStream& rStream, BOOL bLoadRefCounts )
/*N*/ {
/*N*/ 	//	bLoadingDone wird beim Laden des StylePools (ScStyleSheet::GetItemSet) gebraucht
/*N*/ 	bLoadingDone = FALSE;
/*N*/ 
/*N*/ 	USHORT nOldBufSize = rStream.GetBufferSize();
/*N*/ 	rStream.SetBufferSize( 32768 );
/*N*/ 	CharSet eOldSet = rStream.GetStreamCharSet();
/*N*/ 
/*N*/ 	SetPrinter( NULL );
/*N*/ 
/*N*/ 	ScPatternAttr::pDoc = this;
/*N*/ 
/*N*/ 	if ( xPoolHelper.isValid() && !bIsClip )
/*N*/ 		xPoolHelper->SourceDocumentGone();
/*N*/ 
/*N*/ 	xPoolHelper = new ScPoolHelper( this );
/*N*/ 
/*N*/ 	xPoolHelper->GetDocPool()->SetFileFormatVersion( (USHORT)rStream.GetVersion() );
/*N*/ 	BOOL bStylesFound = FALSE;
/*N*/ 
/*N*/ 	BOOL bRet = FALSE;
/*N*/ 	USHORT nID;
/*N*/ 	rStream >> nID;
/*N*/ 	if (nID == SCID_POOLS || nID == SCID_NEWPOOLS)
/*N*/ 	{
/*N*/ 		ScReadHeader aHdr( rStream );
/*N*/ 		while (aHdr.BytesLeft())
/*N*/ 		{
/*N*/ 			USHORT nSubID;
/*N*/ 			rStream >> nSubID;
/*N*/ 			ScReadHeader aSubHdr( rStream );
/*N*/ 			switch (nSubID)
/*N*/ 			{
/*N*/ 				case SCID_CHARSET:
/*N*/ 					{
/*N*/ 						BYTE cSet, cGUI;	// cGUI is dummy, old GUIType
/*N*/ 						rStream >> cGUI >> cSet;
/*N*/ 						eSrcSet = (CharSet) cSet;
/*N*/                         rStream.SetStreamCharSet( ::GetSOLoadTextEncoding(
/*N*/                             eSrcSet, (USHORT)rStream.GetVersion() ) );
/*N*/ 					}
/*N*/ 					break;
/*N*/ 				case SCID_DOCPOOL:
/*N*/ 					xPoolHelper->GetDocPool()->Load( rStream );
/*N*/ 					break;
/*N*/ 				case SCID_STYLEPOOL:
/*N*/ 					{
/*N*/ 						//	StylePool konvertiert beim Laden selber
/*N*/ 						CharSet eOld = rStream.GetStreamCharSet();
/*N*/ 						rStream.SetStreamCharSet( gsl_getSystemTextEncoding() );	//! ???
/*N*/ 						xPoolHelper->GetStylePool()->Load( rStream );
/*N*/ 						rStream.SetStreamCharSet( eOld );
/*N*/ 						lcl_RemoveMergeFromStyles( xPoolHelper->GetStylePool() );	// setzt auch ReadOnly zurueck
/*N*/ 						bStylesFound = TRUE;
/*N*/ 					}
/*N*/ 					break;
/*N*/ 				case SCID_EDITPOOL :
/*N*/ 					xPoolHelper->GetEditPool()->Load( rStream );
/*N*/ 					break;
/*?*/ 				default:
/*?*/ 					DBG_ERROR("unbekannter Sub-Record in ScDocument::LoadPool");
/*N*/ 			}
/*N*/ 		}
/*N*/ 
/*N*/ 		UpdStlShtPtrsFrmNms();
/*N*/ 		bRet = TRUE;
/*N*/ 	}
/*N*/ 	else
/*?*/ 		DBG_ERROR("LoadPool: SCID_POOLS nicht gefunden");
/*N*/ 
/*N*/ 	if (!bStylesFound)
/*?*/ 		xPoolHelper->GetStylePool()->CreateStandardStyles();
/*N*/ 
/*N*/ 	rStream.SetStreamCharSet( eOldSet );
/*N*/ 	rStream.SetBufferSize( nOldBufSize );
/*N*/ 
/*N*/ 	bLoadingDone = TRUE;
/*N*/ 
/*N*/ 	//	Das Uno-Objekt merkt sich einen Pointer auf den NumberFormatter
/*N*/ 	//	-> mitteilen, dass der alte Pointer ungueltig geworden ist
/*N*/ 	BroadcastUno( ScPointerChangedHint(SC_POINTERCHANGED_NUMFMT) );
/*N*/ 
/*N*/ 	return bRet;
/*N*/ }


/*N*/ BOOL ScDocument::SavePool( SvStream& rStream ) const
/*N*/ {
/*N*/ 	xPoolHelper->GetDocPool()->SetFileFormatVersion( (USHORT)rStream.GetVersion() );
/*N*/ 
/*N*/ 	USHORT nOldBufSize = rStream.GetBufferSize();
/*N*/ 	rStream.SetBufferSize( 32768 );
/*N*/ 	CharSet eOldSet = rStream.GetStreamCharSet();
/*N*/     CharSet eStoreCharSet = ::GetSOStoreTextEncoding(
/*N*/         gsl_getSystemTextEncoding(), (USHORT)rStream.GetVersion() );
/*N*/     rStream.SetStreamCharSet( eStoreCharSet );
/*N*/ 
/*N*/ 	//	::com::press-Mode fuer Grafiken in Brush-Items (Hintergrund im Seitenformat)
/*N*/ 
/*N*/ 	USHORT nComprMode = rStream.GetCompressMode() & ~(COMPRESSMODE_ZBITMAP | COMPRESSMODE_NATIVE);
/*N*/ 	SvtSaveOptions aSaveOpt;
/*N*/ 	SvtSaveOptions::SaveGraphicsMode eMode = aSaveOpt.GetSaveGraphicsMode();
/*N*/ 	BOOL bNative = ( eMode == SvtSaveOptions::SaveGraphicsOriginal );
/*N*/ 	BOOL bCompr = bNative || ( eMode == SvtSaveOptions::SaveGraphicsCompressed );
/*N*/ 
/*N*/ 	if ( rStream.GetVersion() >= SOFFICE_FILEFORMAT_40 && bCompr )
/*N*/ 		nComprMode |= COMPRESSMODE_ZBITMAP;				//	komprimiert ab 4.0
/*N*/ 	if ( rStream.GetVersion() > SOFFICE_FILEFORMAT_40 && bNative )
/*N*/ 		nComprMode |= COMPRESSMODE_NATIVE;				//	Originalformat ab 5.0
/*N*/ 	rStream.SetCompressMode( nComprMode );
/*N*/ 
/*N*/ 	{
/*N*/ 		rStream << (USHORT) SCID_NEWPOOLS;
/*N*/ 		ScWriteHeader aHdr( rStream );
/*N*/ 
/*N*/ 		{
/*N*/ 			rStream << (USHORT) SCID_CHARSET;
/*N*/ 			ScWriteHeader aSetHdr( rStream, 2 );
/*N*/ 			rStream << (BYTE) 0		// dummy, old System::GetGUIType()
/*N*/                     << (BYTE) eStoreCharSet;
/*N*/ 		}
/*N*/ 
/*N*/ 		//	Force the default style's name to be "Standard" for all languages in the file.
/*N*/ 		//	This is needed for versions up to 5.1, to find the default pattern's style in
/*N*/ 		//	the UpdateStyleSheet call.
/*N*/ 		//	#89078# this has to be set for the DocPool save, too, so the default style name
/*N*/ 		//	is adjusted for the patterns, or a wrong style would be used if other styles
/*N*/ 		//	match the default style's name after CharacterSet conversion.
/*N*/ 
/*N*/ 		String aFileStdName = String::CreateFromAscii(RTL_CONSTASCII_STRINGPARAM(STRING_STANDARD));
/*N*/ 		if ( aFileStdName != ScGlobal::GetRscString(STR_STYLENAME_STANDARD) )
/*N*/ 			xPoolHelper->GetStylePool()->SetForceStdName( &aFileStdName );
/*N*/ 
/*N*/ 		{
/*N*/ 			rStream << (USHORT) SCID_DOCPOOL;
/*N*/ 			ScWriteHeader aDocPoolHdr( rStream );
/*N*/ 			xPoolHelper->GetDocPool()->Store( rStream );
/*N*/ 		}
/*N*/ 
/*N*/ 		{
/*N*/ 			rStream << (USHORT) SCID_STYLEPOOL;
/*N*/ 			ScWriteHeader aStylePoolHdr( rStream );
/*N*/ 			xPoolHelper->GetStylePool()->SetSearchMask( SFX_STYLE_FAMILY_ALL );
/*N*/ 
/*N*/ 			xPoolHelper->GetStylePool()->Store( rStream, FALSE );
/*N*/ 		}
/*N*/ 
/*N*/ 		xPoolHelper->GetStylePool()->SetForceStdName( NULL );
/*N*/ 
/*N*/ 		if ( rStream.GetVersion() >= SOFFICE_FILEFORMAT_50 )
/*N*/ 		{
/*N*/ 			rStream << (USHORT) SCID_EDITPOOL;
/*N*/ 			ScWriteHeader aEditPoolHdr( rStream );
/*N*/ 			xPoolHelper->GetEditPool()->SetFileFormatVersion( (USHORT)rStream.GetVersion() );
/*N*/ 			xPoolHelper->GetEditPool()->Store( rStream );
/*N*/ 		}
/*N*/ 	}
/*N*/ 
/*N*/ 	rStream.SetStreamCharSet( eOldSet );
/*N*/ 	rStream.SetBufferSize( nOldBufSize );
/*N*/ 	return TRUE;
/*N*/ }


/*N*/ long ScDocument::GetCellCount() const
/*N*/ {
/*N*/ 	long nCellCount = 0L;
/*N*/ 
/*N*/ 	for ( USHORT nTab=0; nTab<=MAXTAB; nTab++ )
/*N*/ 		if ( pTab[nTab] )
/*N*/ 			nCellCount += pTab[nTab]->GetCellCount();
/*N*/ 
/*N*/ 	return nCellCount;
/*N*/ }


/*N*/  ULONG ScDocument::GetCodeCount() const
/*N*/  {
/*N*/  	ULONG nCodeCount = 0;
/*N*/  
/*N*/  	for ( USHORT nTab=0; nTab<=MAXTAB; nTab++ )
/*N*/  		if ( pTab[nTab] )
/*N*/  			nCodeCount += pTab[nTab]->GetCodeCount();
/*N*/  
/*N*/  	return nCodeCount;
/*N*/  }


/*N*/ long ScDocument::GetWeightedCount() const
/*N*/ {
/*N*/ 	long nCellCount = 0L;
/*N*/ 
/*N*/ 	for ( USHORT nTab=0; nTab<=MAXTAB; nTab++ )
/*N*/ 		if ( pTab[nTab] )
/*N*/ 			nCellCount += pTab[nTab]->GetWeightedCount();
/*N*/ 
/*N*/ 	return nCellCount;
/*N*/ }


//STRIP001 void ScDocument::PageStyleModified( USHORT nTab, const String& rNewName )
//STRIP001 {
//STRIP001 	if ( nTab <= MAXTAB && pTab[nTab] )
//STRIP001 		pTab[nTab]->PageStyleModified( rNewName );
//STRIP001 }


/*N*/ void ScDocument::SetPageStyle( USHORT nTab, const String& rName )
/*N*/ {
/*N*/ 	if ( nTab <= MAXTAB && pTab[nTab] )
/*N*/ 		pTab[nTab]->SetPageStyle( rName );
/*N*/ }


/*N*/ const String& ScDocument::GetPageStyle( USHORT nTab ) const
/*N*/ {
/*N*/ 	if ( nTab <= MAXTAB && pTab[nTab] )
/*N*/ 		return pTab[nTab]->GetPageStyle();
/*N*/ 
/*N*/ 	return EMPTY_STRING;
/*N*/ }


/*N*/ void ScDocument::SetPageSize( USHORT nTab, const Size& rSize )
/*N*/ {
/*N*/ 	if ( nTab <= MAXTAB && pTab[nTab] )
/*N*/ 		pTab[nTab]->SetPageSize( rSize );
/*N*/ }

/*N*/ Size ScDocument::GetPageSize( USHORT nTab ) const
/*N*/ {
/*N*/ 	if ( nTab <= MAXTAB && pTab[nTab] )
/*N*/ 		return pTab[nTab]->GetPageSize();
/*N*/ 
/*N*/ 	DBG_ERROR("falsche Tab");
/*N*/ 	return Size();
/*N*/ }


/*N*/ void ScDocument::SetRepeatArea( USHORT nTab, USHORT nStartCol, USHORT nEndCol, USHORT nStartRow, USHORT nEndRow )
/*N*/ {
/*N*/ 	if ( nTab <= MAXTAB && pTab[nTab] )
/*N*/ 		pTab[nTab]->SetRepeatArea( nStartCol, nEndCol, nStartRow, nEndRow );
/*N*/ }


/*N*/ void ScDocument::UpdatePageBreaks()
/*N*/ {
/*N*/ 	for (USHORT i=0; i<=MAXTAB; i++)
/*N*/ 		if (pTab[i])
/*N*/ 			pTab[i]->UpdatePageBreaks( NULL );
/*N*/ }


/*N*/ void ScDocument::UpdatePageBreaks( USHORT nTab, const ScRange* pUserArea )
/*N*/ {
/*N*/ 	if ( nTab <= MAXTAB && pTab[nTab] )
/*N*/ 		pTab[nTab]->UpdatePageBreaks( pUserArea );
/*N*/ }

/*N*/ void ScDocument::RemoveManualBreaks( USHORT nTab )
/*N*/ {
/*N*/ 	if ( nTab <= MAXTAB && pTab[nTab] )
/*N*/ 		pTab[nTab]->RemoveManualBreaks();
/*N*/ }

//STRIP001 BOOL ScDocument::HasManualBreaks( USHORT nTab ) const
//STRIP001 {
//STRIP001 	if ( nTab <= MAXTAB && pTab[nTab] )
//STRIP001 		return pTab[nTab]->HasManualBreaks();
//STRIP001 
//STRIP001 	DBG_ERROR("falsche Tab");
//STRIP001 	return FALSE;
//STRIP001 }


//STRIP001 void ScDocument::GetDocStat( ScDocStat& rDocStat )
//STRIP001 {
//STRIP001 	rDocStat.nTableCount = GetTableCount();
//STRIP001 	rDocStat.aDocName	 = aDocName;
//STRIP001 	rDocStat.nCellCount	 = GetCellCount();
//STRIP001 }


/*N*/ BOOL ScDocument::HasPrintRange()
/*N*/ {
/*N*/ 	BOOL bResult = FALSE;
/*N*/ 
/*N*/ 	for ( USHORT i=0; !bResult && i<nMaxTableNumber; i++ )
/*N*/ 		if ( pTab[i] )
/*N*/ 			bResult = ( pTab[i]->GetPrintRangeCount() > 0 );
/*N*/ 
/*N*/ 	return bResult;
/*N*/ }


/*N*/ USHORT ScDocument::GetPrintRangeCount( USHORT nTab )
/*N*/ {
/*N*/ 	if (nTab<=MAXTAB && pTab[nTab])
/*N*/ 		return pTab[nTab]->GetPrintRangeCount();
/*N*/ 
/*N*/ 	return 0;
/*N*/ }


/*N*/ const ScRange* ScDocument::GetPrintRange( USHORT nTab, USHORT nPos )
/*N*/ {
/*N*/ 	if (nTab<=MAXTAB && pTab[nTab])
/*N*/ 		return pTab[nTab]->GetPrintRange(nPos);
/*N*/ 
/*N*/ 	return NULL;
/*N*/ }


/*N*/ const ScRange* ScDocument::GetRepeatColRange( USHORT nTab )
/*N*/ {
/*N*/ 	if (nTab<=MAXTAB && pTab[nTab])
/*N*/ 		return pTab[nTab]->GetRepeatColRange();
/*N*/ 
/*N*/ 	return NULL;
/*N*/ }


/*N*/ const ScRange* ScDocument::GetRepeatRowRange( USHORT nTab )
/*N*/ {
/*N*/ 	if (nTab<=MAXTAB && pTab[nTab])
/*N*/ 		return pTab[nTab]->GetRepeatRowRange();
/*N*/ 
/*N*/ 	return NULL;
/*N*/ }


// #42845# zeroptimiert
/*N*/ #if defined(WIN) && defined(MSC)
/*N*/ #pragma optimize("",off)
/*N*/ #endif
/*N*/ void ScDocument::SetPrintRangeCount( USHORT nTab, USHORT nNew )
/*N*/ {
/*N*/ 	if (nTab<=MAXTAB && pTab[nTab])
/*N*/ 		pTab[nTab]->SetPrintRangeCount( nNew );
/*N*/ }
/*N*/ #if defined(WIN) && defined(MSC)
/*N*/ #pragma optimize("",on)
/*N*/ #endif


/*N*/ void ScDocument::SetPrintRange( USHORT nTab, USHORT nPos, const ScRange& rNew )
/*N*/ {
/*N*/ 	if (nTab<=MAXTAB && pTab[nTab])
/*N*/ 		pTab[nTab]->SetPrintRange( nPos, rNew );
/*N*/ }


/*N*/ void ScDocument::SetRepeatColRange( USHORT nTab, const ScRange* pNew )
/*N*/ {
/*N*/ 	if (nTab<=MAXTAB && pTab[nTab])
/*N*/ 		pTab[nTab]->SetRepeatColRange( pNew );
/*N*/ }


/*N*/ void ScDocument::SetRepeatRowRange( USHORT nTab, const ScRange* pNew )
/*N*/ {
/*N*/ 	if (nTab<=MAXTAB && pTab[nTab])
/*N*/ 		pTab[nTab]->SetRepeatRowRange( pNew );
/*N*/ }


/*N*/ ScPrintRangeSaver* ScDocument::CreatePrintRangeSaver() const
/*N*/ {
/*N*/ 	USHORT nCount = GetTableCount();
/*N*/ 	ScPrintRangeSaver* pNew = new ScPrintRangeSaver( nCount );
/*N*/ 	for (USHORT i=0; i<nCount; i++)
/*N*/ 		if (pTab[i])
/*N*/ 			pTab[i]->FillPrintSaver( pNew->GetTabData(i) );
/*N*/ 	return pNew;
/*N*/ }


//STRIP001 void ScDocument::RestorePrintRanges( const ScPrintRangeSaver& rSaver )
//STRIP001 {
//STRIP001 	USHORT nCount = rSaver.GetTabCount();
//STRIP001 	for (USHORT i=0; i<nCount; i++)
//STRIP001 		if (pTab[i])
//STRIP001 			pTab[i]->RestorePrintRanges( rSaver.GetTabData(i) );
//STRIP001 }


//STRIP001 BOOL ScDocument::NeedPageResetAfterTab( USHORT nTab ) const
//STRIP001 {
//STRIP001 	//	Die Seitennummern-Zaehlung f�ngt bei einer Tabelle neu an, wenn eine
//STRIP001 	//	andere Vorlage als bei der vorherigen gesetzt ist (nur Namen vergleichen)
//STRIP001 	//	und eine Seitennummer angegeben ist (nicht 0)
//STRIP001 
//STRIP001 	if ( nTab < MAXTAB && pTab[nTab] && pTab[nTab+1] )
//STRIP001 	{
//STRIP001 		String aNew = pTab[nTab+1]->GetPageStyle();
//STRIP001 		if ( aNew != pTab[nTab]->GetPageStyle() )
//STRIP001 		{
//STRIP001 			SfxStyleSheetBase* pStyle = xPoolHelper->GetStylePool()->Find( aNew, SFX_STYLE_FAMILY_PAGE );
//STRIP001 			if ( pStyle )
//STRIP001 			{
//STRIP001 				const SfxItemSet& rSet = pStyle->GetItemSet();
//STRIP001 				USHORT nFirst = ((const SfxUInt16Item&)rSet.Get(ATTR_PAGE_FIRSTPAGENO)).GetValue();
//STRIP001 				if ( nFirst != 0 )
//STRIP001 					return TRUE;		// Seitennummer in neuer Vorlage angegeben
//STRIP001 			}
//STRIP001 		}
//STRIP001 	}
//STRIP001 
//STRIP001 	return FALSE;		// sonst nicht
//STRIP001 }



}
