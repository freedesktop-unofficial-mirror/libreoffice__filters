/*************************************************************************
 *
 *  $RCSfile: sw_sw3doc.cxx,v $
 *
 *  $Revision: 1.2 $
 *
 *  last change: $Author: mwu $ $Date: 2003-11-06 07:50:50 $
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

#include "hintids.hxx"          //Damit "unsere" Attribute angezogen werden.

#ifndef _SVSTOR_HXX //autogen
#include <so3/svstor.hxx>
#endif
#ifndef _SFXAPP_HXX //autogen
#include <bf_sfx2/app.hxx>
#endif
#ifndef _SFXECODE_HXX //autogen
#include <svtools/sfxecode.hxx>
#endif
#ifndef _SVX_LRSPITEM_HXX //autogen
#include <bf_svx/lrspitem.hxx>
#endif
#ifndef _TOOLS_TENCCVT_HXX //autogen
#include <tools/tenccvt.hxx>
#endif
#ifndef _SWMODULE_HXX //autogen
#include <swmodule.hxx>
#endif

#ifndef _FMTCNTNT_HXX //autogen
#include <fmtcntnt.hxx>
#endif
#ifndef _FRMATR_HXX
#include <frmatr.hxx>
#endif

#include "doc.hxx"
#include "docary.hxx"
#include "swrect.hxx"
#include "swerror.h"
#include "pam.hxx"
#include "fldbas.hxx"
#include "rootfrm.hxx"
#include "pagedesc.hxx"
#include "ndtxt.hxx"
#include "ndole.hxx"
#include "sw3imp.hxx"
#include "poolfmt.hxx"
namespace binfilter {


extern String GetSWGVersion();

// Wird von der GUI-Seite gesetzt, wenn Layouts ignoriert werden sollen

//////////////////////////////////////////////////////////////////////////////


//STRIP001 void lcl_sw3doc_ChgChartName( SwDoc* pDoc )
//STRIP001 {
//STRIP001 	// bei "alten" Dokumenten muss das an eine Tabelle gebundene
//STRIP001 	// Chart-Object sonderbehandelt werden. Die Verbindung von
//STRIP001 	// Tabelle zum ChartObject erfolgt weiterhin ueber den Namen,
//STRIP001 	// aber der wird nicht mehr im FlyFormat, sondern direkt
//STRIP001 	// beim OLE-Node gespeichert. FlyFrames koennen jetzt benannt
//STRIP001 	// werden (Name steht im FlyFormat!)
//STRIP001 
//STRIP001 	// durch alle Tabellen
//STRIP001 	for( USHORT n = pDoc->GetTblFrmFmts()->Count(); n; )
//STRIP001 	{
//STRIP001 		const String& rTblNm = (*pDoc->GetTblFrmFmts())[ --n ]->GetName();
//STRIP001 		for( USHORT i = pDoc->GetSpzFrmFmts()->Count(); i; )
//STRIP001 		{
//STRIP001 			// und durch alle Flys
//STRIP001 			SwFmt *pFmt = (*pDoc->GetSpzFrmFmts())[ --i ];
//STRIP001 			if( RES_FLYFRMFMT == pFmt->Which() && pFmt->GetName() == rTblNm )
//STRIP001 			{
//STRIP001 				const SwNodeIndex* pIdx = pFmt->GetCntnt().GetCntntIdx();
//STRIP001 				SwOLENode* pNd;
//STRIP001 				if( pIdx && 0 != ( pNd =
//STRIP001 					pDoc->GetNodes()[ pIdx->GetIndex() + 1 ]->GetOLENode() ))
//STRIP001 				{
//STRIP001 					pNd->SetChartTblName( rTblNm );
//STRIP001 					pFmt->SetName( pDoc->GetUniqueOLEName() );
//STRIP001 				}
//STRIP001 			}
//STRIP001 		}
//STRIP001 	}
//STRIP001 }

//////////////////////////////////////////////////////////////////////////////

// Laden eines Dokumentinhalts. Das kann ein Textbaustein oder ein
// normales Dokument sein. Die Vorlagen sind bereits eingelesen.


/*N*/ void Sw3IoImp::LoadDocContents( SwPaM* pPaM )
/*N*/ {
/*N*/ 	// Wenn ein PaM angegeben ist, wird an einer bestimmten
/*N*/ 	// Position eingefuegt, also ist Insert = TRUE
/*N*/ 	short nDiff = 0;
/*N*/ 	BYTE nInsFirstPara = 0;
/*N*/ 	if( pPaM )
/*N*/ 	{
/*?*/ 		bInsert = TRUE;
/*?*/ 		SwTxtNode *pTxtNode=pDoc->GetNodes()[pPaM->GetPoint()->nNode]->GetTxtNode();
/*?*/ 		// Ist das ein SwPaM auf einen TextNode?
/*?*/ 		if( !pTxtNode )
/*?*/ 		{
/*?*/ 			// Ist keiner, dann machen wir uns einen
/*?*/ 			pTxtNode=pDoc->GetNodes().MakeTxtNode(pPaM->GetPoint()->nNode,
/*?*/ 					 (SwTxtFmtColl*) pDoc->GetDfltTxtFmtColl() );
/*?*/ 			// Da zeigt jetzt auch der StartIdx hin
/*?*/ 			nDiff = -1;
/*?*/ 		}
/*?*/ 		else if( pTxtNode->GetTxt().Len() )
/*?*/ 			nInsFirstPara = 1;
/*N*/ 	}
/*N*/ 
/*N*/ 	// aktuelles Passwort retten
/*N*/ 	sal_Char cOldPass[ 16 ];
/*N*/ 	memcpy( cOldPass, cPasswd, 16 );
/*N*/ 	InHeader( TRUE );
/*N*/ 	if( nFileFlags & SWGF_BAD_FILE )
/*N*/ 	{
/*?*/ 		Error( ERR_SWG_READ_ERROR );
/*?*/ 		return;
/*N*/ 	}
/*N*/ 
/*N*/ 	BOOL bUndo = pDoc->DoesUndo();
/*N*/ 	// Kein Undo bei neuem Dokument!
/*N*/ 	if( !bInsert )
/*N*/ 		pDoc->DoUndo( FALSE );
/*N*/ 
/*N*/ 	// Auf gehts:
/*N*/ 	BOOL bNode1 = TRUE;
/*N*/ 	BOOL bDone = BOOL( !Good() );
/*N*/ 	xub_StrLen nOffset = 0;
/*N*/ 	SwNodeIndex aPos( pDoc->GetNodes().GetEndOfContent(), -1 );
/*N*/ 	if( pPaM )
/*?*/ 		aPos = pPaM->GetPoint()->nNode.GetIndex() + nDiff,
/*?*/ 		nOffset = pPaM->GetPoint()->nContent.GetIndex();
/*N*/ 	pCurPaM = pPaM;
/*N*/ 
/*N*/ 	SwDBData aOldData(pDoc->_GetDBDesc());
/*N*/ 
/*N*/ 	// Normales Lesen?
/*N*/ 	while( !bDone )
/*N*/ 	{
/*N*/ 		BYTE cType = Peek();
/*N*/ 		if( !Good() || pStrm->IsEof() )
/*N*/ 			bDone = TRUE;
/*N*/ 		else switch( cType )
/*N*/ 		{
/*N*/ 			case SWG_EOF:
/*N*/ 				bDone = TRUE; break;
/*N*/ 			case SWG_DBNAME:
/*N*/ 				// der DatenbankName
/*N*/ 				if( bNormal && !bInsert )
/*N*/ 					InDBName();
/*N*/ 				else if( bInsert &&
/*N*/ 						 !IsVersion( SWG_MULTIDB, SWG_EXPORT31, SWG_DESKTOP40 ) )
/*N*/ 				{
/*?*/ 					// in Versionen ohne mehrfache Datenbanken wird hier
/*?*/ 					// der DB-Name gelesen. Warum nicht auch das
/*?*/ 					// SQL-Statemement?
/*?*/ 					OpenRec( SWG_DBNAME );
/*?*/ 
/*?*/ 					// TODO: unicode: what about 0xff?
/*?*/ 					String sStr;
/*?*/ 					InString( *pStrm, sStr );
/*?*/ 					SwDBData aData;
/*?*/ 					aData.sDataSource = sStr.GetToken(0, DB_DELIM);
/*?*/ 					aData.sCommand = sStr.GetToken(1, DB_DELIM);
/*?*/ 					pDoc->ChgDBData( aData );
/*?*/ 
/*?*/ 					ULONG nSaveWarn = nWarn;
/*?*/ 					CloseRec( SWG_DBNAME );
/*?*/ 					nWarn = nSaveWarn;
/*N*/ 				}
/*N*/ 				else
/*?*/ 					SkipRec();
/*N*/ 				break;
/*N*/ 			case SWG_STRINGPOOL:
/*N*/ 				InStringPool( cType, aStringPool );
/*N*/ 				break;
/*N*/ 			case SWG_PASSWORD:
                    {DBG_ASSERT(0, "STRIP");} //STRIP001 /*?*/ 				InPasswd(); break;
/*N*/ 			case SWG_JOBSETUP:
/*N*/ 				if( bNormal && !bInsert ) InJobSetup();
/*N*/ 				else SkipRec(); break;
/*N*/ 			case SWG_CONFIG:
/*N*/ 				SkipRec();
/*N*/ 				break;
/*?*/ 			case SWG_PGPREVIEWPRTDATA:
/*?*/ 				if( bNormal && !bInsert )
                        {DBG_ASSERT(0, "STRIP");} //STRIP001 /*?*/ 					InPagePreViewPrintData();
/*?*/ 				else
/*?*/ 					SkipRec();
/*?*/ 				break;
/*N*/ 
/*N*/ //			case SWG_NUMRULE:
/*N*/ 				// Der 4.0-SW kommt hier auch schon mit NumRules
/*N*/ 				// zurecht, ignoriert sie aber. Es weiss zwar keiner
/*N*/ 				// warum das so ist, aber wir behalten es mal lieber bei.
/*N*/ 			case SWG_OUTLINE:
/*N*/ 				if( bNormal && !(bInsert || bBlock) )
/*N*/ 				{
/*N*/ 					// Dieser Record steht nur in der 3.1 und 4.0 hier.
/*N*/ 					// Ab der 5.0 steht er in einem eigenen Stream.
/*N*/ 					SwNumRule* pRule = InNumRule( cType );
/*N*/ 					if( pRule )
/*N*/ 					{
/*N*/ //JP 10.03.96: und wieder alles zurueck
/*N*/ #if 0
/*N*/ 						if( nVersion < SWG_DELETEOLE )
/*N*/ 						{
/*N*/ 							//JP 18.01.96: Alle Ueberschriften sind normalerweise
/*N*/ 							//	ohne Kapitelnummer. Darum hier explizit abschalten
/*N*/ 							//	weil das Default jetzt wieder auf AN ist.
/*N*/ 							// und UeberschirftBasis ohne Einrueckung!
/*N*/ 							SwTxtFmtColl* pCol = pDoc->GetTxtCollFromPool(
/*N*/ 												RES_POOLCOLL_HEADLINE_BASE );
/*N*/ 							pCol->ResetAttr( RES_LR_SPACE );
/*N*/ 
/*N*/ 							for( short i = 0; i < MAXLEVEL; i++ )
/*N*/ 							{
/*N*/ 								if( !pRule->GetNumFmt( i ) )
/*N*/ 								{
/*N*/ 									SwNumFmt aFmt( pRule->Get( i ) );
/*N*/ 									aFmt.eType = NUMBER_NONE;
/*N*/ 									pRule->Set( i, aFmt );
/*N*/ 								}
/*N*/ 							}
/*N*/ 						}
/*N*/ #endif
/*N*/ 						pDoc->SetOutlineNumRule( *pRule );
/*N*/ 					}
/*N*/ 					delete pRule;
/*N*/ 				}
/*N*/ 				else
/*N*/ 				{
/*?*/ 					SkipRec();
/*N*/ 				}
/*N*/ 				break;
/*?*/ 			case SWG_MACROTBL:
                    {DBG_ASSERT(0, "STRIP");} //STRIP001 /*?*/ 				if( bNormal ) InMacroTbl(); else SkipRec();
/*?*/ 				break;
/*N*/ 			case SWG_DICTIONARY:
/*N*/ 				if( bNormal && IsVersion( SWG_DESKTOP40 ) )
/*N*/ 					InDictionary();
/*N*/ 				else
/*?*/ 					SkipRec();
/*N*/ 				break;
/*N*/ 			case SWG_FIELDTYPE:
/*N*/ 				if( bNormal ) InFieldType(); else SkipRec();
/*N*/ 				break;
/*N*/ 			case SWG_FLYFRAMES:
/*N*/ 				if( bNormal ) InFlyFrames(); else SkipRec();
/*N*/ 				break;
/*N*/ 			case SWG_FOOTINFO:
/*N*/ 				// globale Fussnoten-Info
/*N*/ 				if( bNormal && !(bInsert || bBlock) )
/*N*/ 					InFtnInfo();
/*N*/ 				else
/*?*/ 					SkipRec();
/*N*/ 				break;
/*N*/ 			case SWG_ENDNOTEINFO:
/*N*/ 				// globale Endnoten-Info
/*N*/ 				if( bNormal && !(bInsert || bBlock) )
/*N*/ 					InEndNoteInfo();
/*N*/ 				else
/*?*/ 					SkipRec();
/*N*/ 				break;
/*N*/ 			case SWG_LINENUMBERINFO:
/*N*/ 				// Zeilennumer-Info
/*N*/ 				if( bNormal && !(bInsert || bBlock) )
/*N*/ 					InLineNumberInfo();
/*N*/ 				else
/*N*/ 					SkipRec();
/*N*/ 				break;
/*N*/ 			case SWG_TOXDESCS51:
/*N*/ 				if( !IsVersion(SWG_NEWTOX) )
/*N*/ 					InTOXs51();
/*N*/ 				else
/*N*/ 					SkipRec();
/*N*/ 				break;
/*N*/ 			case SWG_TOXDESCS:
/*N*/ 				ASSERT( IsVersion(SWG_NEWTOX),
/*N*/ 						"new tox descs within a old doc" );
/*N*/ 				InTOXs();
/*N*/ 				break;
/*N*/ 			case SWG_BOOKMARKS:
/*N*/ 				InBookmarks();
/*N*/ 				break;
/*N*/ 			case SWG_REDLINES:
                    {DBG_ASSERT(0, "STRIP");} //STRIP001 /*?*/ 				InRedlines();
/*?*/ 				break;
/*N*/ 			case SWG_CONTENTS:
/*N*/ 				if( bNormal )
/*N*/ 					InContents( aPos, nOffset, bNode1, nInsFirstPara );
/*N*/ 				else
/*?*/ 					SkipRec();
/*N*/ 				bNode1 = FALSE; nOffset = 0;
/*N*/ 				nInsFirstPara = 0;
/*N*/ 				break;
/*N*/ 			case SWG_DOCSTAT:
/*N*/ 				if( bNormal && !bInsert )
/*N*/ 					InDocStat();
/*N*/ 				else
/*?*/ 					SkipRec();
/*N*/ 				break;
/*N*/ 			case SWG_NUMBERFORMATTER:
/*?*/ 				InNumberFormatter();
/*?*/ 				break;
/*N*/ 			case SWG_DOCDUMMIES:
/*N*/ 				if( bNormal && !bInsert )
/*N*/ 					InDocDummies();
/*N*/ 				else
/*?*/ 					SkipRec();
/*N*/ 				break;
/*N*/ 			case SWG_LAYOUTINFO:
/*N*/ 				SkipRec();
/*N*/ 				break;
/*N*/ 
/*N*/ #ifdef TEST_HUGE_DOCS
/*N*/ 			case SWG_TESTHUGEDOCS:
/*N*/ 				InHugeRecord();
/*N*/ #endif
/*N*/ 			default:
/*N*/ 				SkipRec();
/*N*/ 		}
/*N*/ 	}
/*N*/ 
/*N*/ 	// Insert TOXs if not done this already.
/*N*/ 	ConnectPageDescAttrs();
/*N*/ 	ConnectTOXs();
/*N*/ 
/*N*/ 	Cleanup( FALSE );
/*N*/ 
/*N*/ 	if( !IsVersion(SWG_LONGIDX) && pCurNumRange )
/*?*/ 		CloseNumRange40( aPos );
/*N*/ 
/*N*/ 	if( bInsert && !IsVersion( SWG_MULTIDB, SWG_EXPORT31, SWG_DESKTOP40 ) )
/*?*/ 		pDoc->ChgDBData( aOldData );
/*N*/ 
/*N*/ 	pDoc->DoUndo( bUndo );
/*N*/ 	if( !nRes )
/*N*/ 	{
/*N*/ 		if( bNormal )
/*N*/ 		{
/*N*/ 			// Neues Doc gelesen
/*N*/ 			if( !bInsert )
/*N*/ 			{
/*N*/ 				// bei "alten" Dokumenten muss das an eine Tabelle gebundene
/*N*/ 				// Chart-Object sonderbehandelt werden. Die Verbindung von
/*N*/ 				// Tabelle zum ChartObject erfolgt weiterhin ueber den Namen,
/*N*/ 				// aber der wird nicht mehr im FlyFormat, sondern direkt
/*N*/ 				// beim OLE-Node gespeichert. FlyFrames koennen jetzt benannt
/*N*/ 				// werden (Name steht im FlyFormat!)
/*N*/ 				if( nVersion < SWG_OLENAME && pDoc->GetTblFrmFmts()->Count() &&
/*N*/ 					pDoc->GetSpzFrmFmts()->Count() )
                        {DBG_ASSERT(0, "STRIP");} //STRIP001 /*?*/ 						::lcl_sw3doc_ChgChartName( pDoc );
/*N*/ 
/*N*/ 				pDoc->SetLoaded( TRUE );
/*N*/ 			}
/*N*/ 		}
/*N*/ 		else
/*N*/ 		{
/*N*/ 			// Nachladen von Vorlagen etc.
/*N*/ 			// falls wir die OutlineLevel veraendert haben (Vorlagen geladen),
/*N*/ 			// dann muss am Doc ein Update auf die neuen Nummern erfolgen !!
/*?*/ 			if( !bAdditive && pDoc->GetOutlineNumRule() )
/*?*/ 				pDoc->SetOutlineNumRule( *pDoc->GetOutlineNumRule() );
/*?*/ 			pDoc->SetModified();
/*N*/ 		}
/*N*/ 	}
/*N*/ 	pDoc->SetNewDoc( FALSE );
/*N*/ 	if ( nVersion < SWG_OLEVIS2PAGE )
/*N*/ 	{
/*N*/ 		//Bei alten Dokumenten schaetzen wir: Wenn die Standardpage
/*N*/ 		//Seitenraender von 0 hat, so wirds wohl ein Ole sein.
/*N*/ 		//MA: Ole wird jetzt per Browse dargestellt.
/*?*/ 		SwPageDesc &rDesc = pDoc->_GetPageDesc( 0 );
/*?*/ 		const SvxLRSpaceItem &rLR = rDesc.GetMaster().GetLRSpace();
/*?*/ 		if ( !rLR.GetLeft() && !rLR.GetRight() )
/*?*/ 			pDoc->SetBrowseMode( TRUE );
/*N*/ 	}
/*N*/ }


// Doc-Header
// SWG_COMMENT		Build des Writers (opt.)
// SWG_STRINGPOOL	Stringpool
// SWG_PASSWORD 	Passwort fuer Bereiche (opt.)
// SWG_OUTLINE		Outline-Numerierung (nicht bei Textbausteinen)
// SWG_NUMRULE		Default-Numerierung (nicht bei Textbausteinen)
// SWG_MACROTBL 	Makro-Tabelle (nicht bei Textbausteinen)
// SWG_DICTIONARY	Woerterbuecher des Onlinespellings
// SWG_FOOTINFO 	globale Fu�noten-Infos (nicht bei Textbausteinen)
// SWG_FLYFRAMES	Seitengebundene Frames (nicht bei Textbausteinen)
// SWG_FIELDTYPES	Feldtypen
// SWG_TOXDESCS 	Verzeichnisbereiche
// SWG_BOOKMARKS	Bookmarks
// SWG_CONTENTS 	Dokumentinhalt
// SWG_FRAMEINFO	Layout-Frames
// SWG_STRINGPOOL	Liste aller Namen von embedded-Grafiken
// SWG_JOBSETUP 	Job-Setup (nicht bei Textbausteinen)
// SWG_EOF			Streamende

/*N*/ void Sw3IoImp::SaveDocContents( SwPaM& rPaM, const String* pBlockName )
/*N*/ {
/*N*/ 	if( pBlockName )
/*?*/ 		bBlock = TRUE, aBlkName = *pBlockName;
/*N*/ 	OutHeader();
/*N*/ 	// Alle FlyFrames am Doc sammeln
/*N*/ 	CollectFlyFrms( &rPaM );
/*N*/ 	aStringPool.Setup( *pDoc, pStrm->GetVersion(), pExportInfo );
/*N*/ 	// Ausgabe des Versions-Textes, falls vorhanden
/*N*/ 	String aVersion = GetSWGVersion();
/*N*/ 	if( aVersion.Len() )
/*N*/ 	{
/*N*/ 		ByteString sTmp( aVersion, eSrcSet );
/*N*/ 		OpenRec( SWG_COMMENT );
/*N*/ 		*pStrm << sTmp.GetBuffer();
/*N*/ 		CloseRec( SWG_COMMENT );
/*N*/ 	}
/*N*/ 	// der DatenbankName
/*N*/ 	OutDBName();
/*N*/ 
/*N*/ 	// Der String-Pool
/*N*/ 	OutStringPool( SWG_STRINGPOOL, aStringPool );
/*N*/ 	if( !bBlock )
/*N*/ 	{
/*N*/ 		if( !nRes )
/*N*/ 		{
/*N*/ 			aStat.Reset();
/*N*/ 			aStat.nPara = 0;			// default ist auf 1
/*N*/ 			OutDocStat( TRUE );
/*N*/ 			aDefWordDelim = SW_MOD()->GetDocStatWordDelim();
/*N*/ 		}
/*N*/ 
/*N*/ 		// Outline-Numerierung, falls vorhanden
/*N*/ 		if( pDoc->GetOutlineNumRule() && IsSw31Or40Export() )
/*N*/ 			OutNumRule( SWG_OUTLINE, *pDoc->GetOutlineNumRule() );
/*N*/ 
/*N*/ 		// globale Fussnoten-Info
/*N*/ 		if( !nRes )
/*N*/ 			OutFtnInfo();
/*N*/ 		if( !nRes && !IsSw31Or40Export() )
/*N*/ 			OutEndNoteInfo();
/*N*/ 		if( !nRes && !IsSw31Or40Export() )
/*N*/ 			OutLineNumberInfo();
/*N*/ 	}
/*N*/ 
/*N*/ 	// Woerterbuecher des Onlinespellings
/*N*/ 	if( !nRes && !IsSw31Export() ) OutDictionary();
/*N*/ 	// Numberformatter schreiben bei Textbausteinen. Bei normalen
/*N*/ 	// Dokumenten erfolgt es schon bei den PageDescs
/*N*/ 	if( !nRes && !IsSw31Export() && bBlock ) OutNumberFormatter();
/*N*/ 
/*N*/ 	// Makro-Tabellen
/*N*/ 	if( !nRes ) OutMacroTbl();
/*N*/ 	// Nicht-Systemfeldtypen
/*N*/ 	if( !nRes ) OutFieldTypes();
/*N*/ 	// Verzeichnisbereiche
/*N*/ 	if( !nRes )
/*N*/ 	{
/*N*/ 		OutTOXs51();
/*N*/ 		if( !nRes && !IsSw31Or40Export() )
/*N*/ 			OutTOXs();
/*N*/ 	}
/*N*/ 
/*N*/ 	// Bookmarks (nicht, wenn ein SW2-TextBlockDoc konvertiert wird)
/*N*/ // JP 16.10.95: werden jetzt im OutPageDesc geschrieben
/*N*/ // MIB 11.12.96: es werden jetzt die Bookmarks der Seiten-Vorlagen und
/*N*/ //               im Dok jeweils getrennt in die Streams geschrieben
/*N*/ 	if( !nRes && !( nGblFlags & SW3F_CONVBLOCK ) && !IsSw31Export() )
/*N*/ 		OutBookmarks( FALSE );
/*N*/ 
/*N*/ 	// Solange Textbausteine ueber Zwischen-Dokumente geladen und
/*N*/ 	// gespeichert werden, kann es dort keine Redlines geben. Also
/*N*/ 	// muss man dies nirgendwo abfangen (nicht nur hier nicht).
/*N*/ 	if( !nRes && !IsSw31Or40Export() )
/*N*/ 		OutRedlines( FALSE );
/*N*/ 
/*N*/ 	// Einstellungen der PagePreView speichern
/*N*/ 	if( !nRes && !bBlock && !IsSw31Or40Export() )
/*N*/ 		OutPagePreViewPrintData();
/*N*/ 
/*N*/ 	// Eine handvoll persistenten Dummy-Member
/*N*/ 	if( !nRes && !IsSw31Or40Export() )
/*N*/ 		OutDocDummies();
/*N*/ 
/*N*/ 	// Der Inhalt
/*N*/ 	SwPaM* pPaM = &rPaM;
/*N*/ 	while( !nRes )
/*N*/ 	{
/*N*/ 		pCurPaM = pPaM;
/*N*/ 		// seitengebundene FlyFrames
/*N*/ 		if( !pBlockName ) OutFlyFrames( *pPaM );
/*N*/ 		OutContents( pPaM );
/*N*/ 		if( (SwPaM*) pPaM->GetNext() != &rPaM )
/*N*/ 		{
/*?*/ 			pPaM = (SwPaM*) pPaM->GetNext();
/*N*/ 		}
/*N*/ 		else break;
/*N*/ 	}
/*N*/ 	// der Job-Setup. Vor dem Layout, damit das Layout bei veraendertem Drucker
/*N*/ 	// gleich geeignet invalidiert werden kann.
/*N*/ 	if( !bBlock && !nRes )
/*N*/ 		OutJobSetup();
/*N*/ 
/*N*/ #ifdef TEST_HUGE_DOCS
/*N*/ 	BOOL b = FALSE;
/*N*/ 	if( b )
/*N*/ 		OutHugeRecord( 1024, 32*1024 );
/*N*/ #endif
/*N*/ 
/*N*/ 	ULONG nRecSzPos = 0;
/*N*/ 	if( !nRes && HasRecSizes() && !IsSw31Or40Export() )
            {DBG_ASSERT(0, "STRIP");} //STRIP001 /*?*/ 		nRecSzPos = OutRecSizes();
/*N*/ 
/*N*/ 	OpenRec( SWG_EOF );
/*N*/ 	CloseRec( SWG_EOF );
/*N*/ 	// Ggf. Fehlerflag schreiben
/*N*/ 	if( nRes )
/*N*/ 	{
/*?*/ 		nFileFlags |= SWGF_BAD_FILE;
/*N*/ 	}
/*N*/ 	// Datei-Flags noch einmal schreiben
/*N*/ 	pStrm->Seek( 0L );
/*N*/ 	OutHeader( nRecSzPos );
/*N*/ 	// Temporaere Namenserweiterungen entfernen
/*N*/ 	aStringPool.RemoveExtensions( *pDoc );
/*N*/ 	FreeFlyFrms();
/*N*/ 	// Die gesammelte Statistik am Doc setzen
/*N*/ 	if( !bBlock )
/*N*/ 	{
/*N*/ 		// Bis das Layout gespeichert wird, die Seiten uebernehmen
/*N*/ 		if( pDoc->GetRootFrm() )
/*N*/ 			aStat.nPage = pDoc->GetRootFrm()->GetPageNum();
/*N*/ 		pDoc->SetDocStat( aStat );
/*N*/ 		OutDocStat( FALSE );
/*N*/ 	}
/*N*/ }

// Laden des Textes eines Dokuments. Der Text wird an den uebergebenen
// String angefuegt.


//STRIP001 void Sw3IoImp::LoadDocText( String& rText )
//STRIP001 {
//STRIP001 	rText.Erase();
//STRIP001 	Reset2();
//STRIP001 	pStrm->Seek( 0 );
//STRIP001 	OutputMode( FALSE );
//STRIP001 	InHeader( TRUE );
//STRIP001 	if( ( nFileFlags & SWGF_BAD_FILE )
//STRIP001 	 || ( nVersion < SWG_DDESEP ) )
//STRIP001 		Error( ERR_SWG_READ_ERROR );
//STRIP001 
//STRIP001 	BOOL bDone = BOOL( !Good() );
//STRIP001 	while( !bDone )
//STRIP001 	{
//STRIP001 		BYTE cType = Peek();
//STRIP001 		if( !Good() || pStrm->IsEof() )
//STRIP001 			bDone = TRUE;
//STRIP001 		else switch( cType )
//STRIP001 		{
//STRIP001 			case SWG_EOF:
//STRIP001 				bDone = TRUE; break;
//STRIP001 			case SWG_CONTENTS:
//STRIP001 				rText += InContentsText();
//STRIP001 				break;
//STRIP001 			default:
//STRIP001 				SkipRec();
//STRIP001 		}
//STRIP001 	}
//STRIP001 }

//////////////////////////////////////////////////////////////////////////////

// Laden des Doc-Headers.

// BYTE[6]		Signatur fuer den harten Patch
// BYTE 		0
// BYTE 		Laenge der globalen Daten (z.Zt. 48 oder 112)
// INT16		Format-Version
// INT16		Globale Flags
// INT32		Persistente Flags vom Document
//				0x0001 == bOleVis2Page, MA 20. Mar. 98 gibt es nicht mehr, wird
//										auf BrowseMode gemappt.
// INT32 x 3	Dummys
// BYTE x 16	Passwort
// BYTE 		CharSet letzter Save
// BYTE 		GUIType letzer Save (Info)
// INT32		Datum letzter Save (Info)
// INT32		Uhrzeit letzter Save (Info)
// BYTE[64] 	Langer Name des Textbausteins, falls SWGF_BLOCKNAME aktiv

/*N*/ BOOL Sw3IoImp::CheckHeader( sal_Char *sHeader )
/*N*/ {
/*N*/ 	return strcmp( sHeader, SW5HEADER ) == 0 ||
/*N*/ 		   strcmp( sHeader, SW4HEADER ) == 0 ||
/*N*/ 		   strcmp( sHeader, SW3HEADER ) == 0;
/*N*/ }

/*N*/ void Sw3IoImp::InHeader( BOOL bReadRecSizes )
/*N*/ {
/*N*/ 	BYTE cLen, cSet, cGUI;
/*N*/ 	sal_Char cHdrSign[ 8 ];
/*N*/ 	Reset2();
/*N*/ 	OutputMode( FALSE );
/*N*/ 	pStrm->Seek( 0L );
/*N*/ 	if( pStrm->Read( cHdrSign, 7 ) == 7 )
/*N*/ 	{
/*N*/ 		if( !CheckHeader(cHdrSign) )
/*N*/ 		{
/*N*/ 			Error( ERR_SW6_NOWRITER_FILE );
/*N*/ 			return;
/*N*/ 		}
/*N*/ 	}
/*N*/ 	else
/*N*/ 		return;
/*N*/ 
/*N*/ 	*pStrm >> cLen;
/*N*/ 	ULONG nOld = pStrm->Tell();
/*N*/ 
/*N*/ 	UINT32 nRecSzPos;
/*N*/ 	INT32 nDocFlags,
/*N*/ 		  nDummy;
/*N*/ 	BYTE cRedlineMode;
/*N*/ 	INT8 nCompatVer,
/*N*/ 		 nDummy8;
/*N*/ 
/*N*/ 	*pStrm >> nVersion >> nFileFlags >> nDocFlags >> nRecSzPos >> nDummy
/*N*/ 		   >> nDummy8 >> nDummy8 >> cRedlineMode >> nCompatVer;
/*N*/ 	// Ist die daeti von einem zu neuen SW und laesst sich nicht mehr lesen?
/*N*/ 	// Die Kompatibilitaets-Version von aelteren File-Formaten muss
/*N*/ 	// natuerlich ignoriert werden.
/*N*/ 	if( IsVersion(SWG_MAJORVERSION) && nCompatVer > SWG_CVERSION )
/*N*/ 	{
/*N*/ 		Error( ERR_SWG_NEW_VERSION ); return; // Datei ist von neuerem SW
/*N*/ 	}
/*N*/ 	pStrm->Read( cPasswd, 16L );
/*N*/ 	*pStrm >> cSet >> cGUI >> nDate >> nTime;
/*N*/ 	eSrcSet = GetSOLoadTextEncoding( (rtl_TextEncoding) cSet,
/*N*/ 								  	 pStrm->GetVersion() );
/*N*/ 	pStrm->SetStreamCharSet( eSrcSet );
/*N*/ 	if( nFileFlags & SWGF_BLOCKNAME )
/*N*/ 	{
/*?*/ 		sal_Char cBuf[ 64 ];
/*?*/ 		if( pStrm->Read( cBuf, 64 ) != 64 )
/*?*/ 			pStrm->SetError( SVSTREAM_FILEFORMAT_ERROR );
/*?*/ 		aBlkName = String( cBuf, eSrcSet );
/*N*/ 	}
/*N*/ 	ULONG nNew = pStrm->Tell();
/*N*/ 	nOld += cLen;
/*N*/ 	if( nOld != nNew )
/*?*/ 		pStrm->Seek( nOld );
/*N*/ 
/*N*/ #ifdef MAC
/*N*/ 	if( pStrm != &pPageStyles && pStrm != &pNumRules )
/*N*/ #else
/*N*/ 	if( pStrm != pPageStyles && pStrm != &pNumRules )
/*N*/ #endif
/*N*/ 	{
/*N*/ 		// Flags werden nur gesetzt, wenn der
/*N*/ 		// Contents-Stream eingelesen wird.
/*N*/ 		if( nFileFlags & SWGF_HAS_PGNUMS )
/*?*/ 			pDoc->SetPageNums();
/*N*/ 		if( !bInsert )
/*N*/ 		{
/*N*/ 			if( IsVersion(SWG_OLEVIS2PAGE) )
/*N*/ 				pDoc->SetBrowseMode ( 0 != (nDocFlags & 0x0001) ||
/*N*/ 									  0 != (nDocFlags & 0x0002) );
/*N*/ 
/*N*/ 			pDoc->SetHTMLMode( 0 != (nDocFlags & 0x0004) );
/*N*/ 			pDoc->SetHeadInBrowse( 0 != (nDocFlags & 0x0008) );
/*N*/ 			pDoc->SetFootInBrowse( 0 != (nDocFlags & 0x0010) );
/*N*/ 			pDoc->SetGlobalDoc( 0 != (nDocFlags & 0x0020) );
/*N*/ 			pDoc->SetGlblDocSaveLinks( 0 != (nDocFlags & 0x0040) );
/*N*/ 			pDoc->SetLabelDoc( 0 != (nDocFlags & 0x0080) );
/*N*/ 		}
/*N*/ 	}
/*N*/ 	if( bNormal && !bInsert && IsVersion(SWG_LONGIDX) )
/*N*/ 		pDoc->SetRedlineMode_intern( (SwRedlineMode)cRedlineMode );
/*N*/ 	if( !CheckPasswd() )
/*?*/ 		Error( ERRCODE_SFX_WRONGPASSWORD );
/*N*/ 
/*N*/ 	// MIB: Das <= fuer das 40-FF ist korrekt, denn es gab eine Weile
/*N*/ 	// 4.0-Storages mit 5.0-Streams.
/*N*/ #ifndef PRODUCT
/*N*/ 	if( !bBlock )
/*N*/ 		ASSERT( ( pRoot->GetVersion() == SOFFICE_FILEFORMAT_31 &&
/*N*/ 				  nVersion >= SWG_MAJORVERSION_30 &&
/*N*/ 				  nVersion < SWG_MAJORVERSION_40 ) ||
/*N*/ 				( pRoot->GetVersion() == SOFFICE_FILEFORMAT_40 &&
/*N*/ 				  nVersion >= SWG_MAJORVERSION_40 &&
/*N*/ 				  nVersion < SWG_MAJORVERSION_50 ) ||
/*N*/ 				( pRoot->GetVersion() == SOFFICE_FILEFORMAT_50 &&
/*N*/ 				  nVersion >= SWG_MAJORVERSION_50 ),
/*N*/ 				"Beim Lesen stimmt die FF-Version am Storage nicht!" );
/*N*/ #endif
/*N*/ 
/*N*/ 	if( nRecSzPos!= 0 && bReadRecSizes && !nRes && IsVersion(SWG_RECSIZES) )
            {DBG_ASSERT(0, "STRIP");} //STRIP001 /*?*/ 		InRecSizes( nRecSzPos );
/*N*/ }


/*N*/ void Sw3IoImp::OutHeader( ULONG nRecSzPos )
/*N*/ {
/*N*/ 	Reset2();
/*N*/ 	nFileFlags |= SWGF_NO_FRAMES;
/*N*/ 	if( aBlkName.Len() )
/*N*/ 		nFileFlags |= SWGF_BLOCKNAME;
/*N*/ 
/*N*/ 	INT32 nDocFlags = 0;
/*N*/ 	if ( pDoc->IsBrowseMode() )
/*N*/ 		nDocFlags |= 0x0002;
/*N*/ 	if ( pDoc->IsHTMLMode() )
/*N*/ 		nDocFlags |= 0x0004;
/*N*/ 	if ( pDoc->IsHeadInBrowse() )
/*N*/ 		nDocFlags |= 0x0008;
/*N*/ 	if ( pDoc->IsFootInBrowse() )
/*N*/ 		nDocFlags |= 0x0010;
/*N*/ 	if( pDoc->IsGlobalDoc() )
/*N*/ 		nDocFlags |= 0x0020;
/*N*/ 	if( pDoc->IsGlblDocSaveLinks() )
/*N*/ 		nDocFlags |= 0x0040;
/*N*/ 	if( !bBlock && !IsSw31Or40Export() && pDoc->IsLabelDoc() )
/*N*/ 		nDocFlags |= 0x0080;
/*N*/ 
/*N*/ 	BYTE cRedlineMode = 0;
/*N*/ 	if( !bBlock && !IsSw31Or40Export() )
/*N*/ 		cRedlineMode = (BYTE)pDoc->GetRedlineMode();
/*N*/ 
/*N*/ 	UINT16 nVers = SWG_VERSION;
/*N*/ 	const sal_Char *sHeader = SW5HEADER;
/*N*/ 
/*N*/ 	switch( pStrm->GetVersion() )
/*N*/ 	{
/*N*/ 	case SOFFICE_FILEFORMAT_40:
/*N*/ 		nVers = SWG_EXPORT40;
/*N*/ 		sHeader = SW4HEADER;
/*N*/ 		break;
/*N*/ 	case SOFFICE_FILEFORMAT_31:
/*N*/ 		nVers = SWG_EXPORT31;
/*N*/ 		sHeader = SW3HEADER;
/*N*/ 		break;
/*N*/ 	}
/*N*/ 
/*N*/ 	ASSERT( !nRecSzPos || !IsSw31Or40Export(),
/*N*/ 			"Lange Records gibt's erst ab der 5.0" );
/*N*/ 	ASSERT( GetSOStoreTextEncoding( gsl_getSystemTextEncoding(), 
/*N*/ 									pStrm->GetVersion() ) == eSrcSet,
/*N*/ 			"wrong encoding while writing" );
/*N*/ 	ASSERT( pStrm->GetStreamCharSet() == eSrcSet,
/*N*/ 			"wrong encoding at stream while writing" );
/*N*/ 
/*N*/ 	OutputMode( TRUE );
/*N*/ 	pStrm->Seek( 0L );
/*N*/ 	*pStrm << sHeader
/*N*/ 		   << (BYTE)   0
/*N*/ 		   << (BYTE)   ( aBlkName.Len() ? 46+64 : 46 )	// Laenge der Daten
/*N*/ 		   << (UINT16) nVers
/*N*/ 		   << (UINT16) nFileFlags
/*N*/ 		   << (INT32)  nDocFlags
/*N*/ 		   << (UINT32) nRecSzPos
/*N*/ 		   << (INT32)  0
/*N*/ 		   << (INT8)   0
/*N*/ 		   << (INT8)   0
/*N*/ 		   << (BYTE)   cRedlineMode
/*N*/ 		   << (INT8)   SWG_CVERSION;
/*N*/ 	pStrm->Write( cPasswd, 16 );
/*N*/ 	*pStrm << (BYTE)   eSrcSet
/*N*/ 		   << (BYTE)   0				// OLD: eSysType
/*N*/ 		   << (UINT32) nDate			// fuer Passwortcheck wichtig
/*N*/ 		   << (UINT32) nTime;
/*N*/ 	if( aBlkName.Len() )
/*N*/ 	{
/*N*/ 		// den langen Blocknamen rausschreiben
/*?*/ 		ByteString sTmp( aBlkName, eSrcSet );
/*?*/ 		sal_Char cBuf[ 64 ];
/*?*/ 		sTmp.Erase( 63 );
/*?*/ 		memset( cBuf, 0, 64 );
/*?*/ 		memcpy( cBuf, sTmp.GetBuffer(), sTmp.Len() );
/*?*/ 		pStrm->Write( cBuf, 64 );
/*N*/ 	}
/*N*/ }

//STRIP001 void Sw3IoImp::OutRecordSizesPos( ULONG nRecSzPos )
//STRIP001 {
//STRIP001 	ULONG nPos = pStrm->Tell();
//STRIP001 
//STRIP001 	pStrm->Seek( 16UL );
//STRIP001 	*pStrm << (UINT32)nRecSzPos;
//STRIP001 
//STRIP001 	pStrm->Seek( nPos );
//STRIP001 }

/*#pragma SEG_FUNCDEF(sw3doc_0b)

void Sw3IoImp::GetBlockName( String& rName )
{
    InHeader();
    rName = aBlkName;
} */

}
