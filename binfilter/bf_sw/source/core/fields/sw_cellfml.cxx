/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: sw_cellfml.cxx,v $
 *
 *  $Revision: 1.9 $
 *
 *  last change: $Author: kz $ $Date: 2007-09-06 12:12:01 $
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


#ifdef _MSC_VER
#pragma hdrstop
#endif

#include <float.h>

#ifndef _FMTFLD_HXX //autogen
#include <fmtfld.hxx>
#endif
#ifndef _TXTFLD_HXX //autogen
#include <txtfld.hxx>
#endif
#ifndef _FRMFMT_HXX //autogen
#include <frmfmt.hxx>
#endif
#ifndef _CNTFRM_HXX
#include <cntfrm.hxx>
#endif
#ifndef _TABFRM_HXX
#include <tabfrm.hxx>
#endif

#ifndef _HORIORNT_HXX
#include <horiornt.hxx>
#endif

#ifndef _DOC_HXX
#include <doc.hxx>
#endif
#ifndef _NDTXT_HXX
#include <ndtxt.hxx>
#endif
#ifndef _TBLSEL_HXX
#include <tblsel.hxx>
#endif
#ifndef _CELLFML_HXX
#include <cellfml.hxx>
#endif
#ifndef _CALC_HXX
#include <calc.hxx>
#endif
#ifndef _EXPFLD_HXX
#include <expfld.hxx>
#endif
#ifndef _USRFLD_HXX
#include <usrfld.hxx>
#endif
#ifndef _FLDDAT_HXX
#include <flddat.hxx>
#endif
#ifndef _CELLATR_HXX
#include <cellatr.hxx>
#endif
#ifndef _NDINDEX_HXX
#include <ndindex.hxx>
#endif
#ifndef _HINTS_HXX
#include <hints.hxx>
#endif
namespace binfilter {

const sal_Unicode cRelTrenner = ',';
const sal_Unicode cRelKennung = '';		// CTRL-R

const USHORT cMAXSTACKSIZE = 50;

/*N*/ const SwFrm* lcl_GetBoxFrm( const SwTableBox& rBox );
String lcl_BoxNmToRel( const SwTable&, const SwTableNode&,
                        const String& , const String& , BOOL );


/*************************************************************************
|*
|*	double SwTableBox::GetValue() const
|*		gebe den Wert dieser Box zurueck. Der Wert ergibt sich aus dem 1.
|*		TextNode. Beginnt dieser mit einer Zahl/Formel, so berechne diese;
|*		oder mit einem Feld, dann hole den Wert.
|*		Alle anderen Bedingungen returnen einen Fehler (oder 0 ?)
|*
|*	Ersterstellung		JP 30. Jun. 93
|*	Letzte Aenderung	JP 30. Jun. 93
|*
|*************************************************************************/

/*N*/ double SwTableBox::GetValue( SwTblCalcPara& rCalcPara ) const
/*N*/ {
/*N*/ 	double nRet = 0;
/*N*/
/*N*/ 	if( rCalcPara.rCalc.IsCalcError() )
/*?*/ 		return nRet;			// schon ein Fehler in der Berechnung
/*N*/
/*N*/ 	rCalcPara.rCalc.SetCalcError( CALC_SYNTAX );	// default immer Fehler
/*N*/
/*N*/ 	// keine Content Box ?
/*N*/ 	if( !pSttNd  )
/*?*/ 		return nRet;
/*N*/
/*N*/ 	if( rCalcPara.IncStackCnt() )
/*?*/ 		return nRet;
/*N*/
/*N*/ 	rCalcPara.SetLastTblBox( this );
/*N*/
/*N*/ 	// wird eine Rekursion erzeugt ?
/*N*/ 	SwTableBox* pBox = (SwTableBox*)this;
/*N*/ 	if( rCalcPara.pBoxStk->Seek_Entry( pBox ))
/*?*/ 		return nRet;			// steht schon auf dem Stack: FEHLER
/*N*/
/*N*/ 	// bei dieser Box nochmal aufsetzen
/*N*/ 	rCalcPara.SetLastTblBox( this );
/*N*/
/*N*/ 	rCalcPara.pBoxStk->Insert( pBox );		// eintragen
/*N*/ 	do {		// Middle-Check-Loop, damit aus dieser gesprungen werden kann
/*N*/ 				// hier aufgespannt, damit am Ende der Box-Pointer aus dem
/*N*/ 				// Stack ausgetragen wird
/*N*/ 		SwDoc* pDoc = GetFrmFmt()->GetDoc();
/*N*/
/*N*/ 		const SfxPoolItem* pItem;
/*N*/ 		if( SFX_ITEM_SET == GetFrmFmt()->GetItemState(
/*N*/ 								RES_BOXATR_FORMULA, FALSE, &pItem ) )
/*N*/ 		{
/*?*/ 			rCalcPara.rCalc.SetCalcError( CALC_NOERR );	// wieder zuruecksetzen
/*?*/ 			if( !((SwTblBoxFormula*)pItem)->IsValid() )
/*?*/ 			{
/*?*/ 				// dann berechnen
/*?*/ 				DBG_BF_ASSERT(0, "STRIP"); //STRIP001 const SwTable* pTmp = rCalcPara.pTbl;
/*?*/ 			}
/*?*/ 			else
/*?*/ 				nRet = GetFrmFmt()->GetTblBoxValue().GetValue();
/*?*/ 			break;
/*N*/ 		}
/*N*/ 		else if( SFX_ITEM_SET == pBox->GetFrmFmt()->GetItemState(
/*N*/ 								RES_BOXATR_VALUE, FALSE, &pItem ) )
/*N*/ 		{
/*?*/ 			rCalcPara.rCalc.SetCalcError( CALC_NOERR );	// wieder zuruecksetzen
/*?*/ 			nRet = ((SwTblBoxValue*)pItem)->GetValue();
/*?*/ 			break;
/*N*/ 		}
/*N*/
/*N*/ 		SwTxtNode* pTxtNd = pDoc->GetNodes()[ pSttNd->GetIndex() + 1 ]->GetTxtNode();
/*N*/ 		if( !pTxtNd )
/*?*/ 			break;
/*N*/
/*N*/ 		xub_StrLen nSttPos = 0;
/*N*/ 		const String& rTxt = pTxtNd->GetTxt();
/*N*/ 		while( nSttPos < rTxt.Len() &&
/*N*/ 				( ' ' ==  rTxt.GetChar( nSttPos ) || '\t' ==  rTxt.GetChar( nSttPos ) ) )
/*?*/ 			++nSttPos;
/*N*/
/*N*/ 		// beginnt an erster Position ein "RechenFeld", dann erfrage den Wert
/*N*/ 		// von diesem
/*N*/ 		sal_Unicode cChr;
/*N*/ 		if( nSttPos < rTxt.Len() &&
/*N*/ 			( CH_TXTATR_BREAKWORD == ( cChr = rTxt.GetChar(nSttPos)) ||
/*N*/ 			  CH_TXTATR_INWORD == cChr ))
/*N*/ 		{
/*N*/ 			SwIndex aIdx( pTxtNd, nSttPos );
/*N*/ 			SwTxtFld* pTxtFld = pTxtNd->GetTxtFld( aIdx );
/*N*/ 			if( !pTxtFld )
/*?*/ 				break;
/*N*/
/*N*/ 			rCalcPara.rCalc.SetCalcError( CALC_NOERR );	// wieder zuruecksetzen
/*N*/
/*N*/ 			const SwField* pFld = pTxtFld->GetFld().GetFld();
/*N*/ 			switch( pFld->GetTyp()->Which()  )
/*N*/ 			{
/*N*/ 			case RES_SETEXPFLD:
/*?*/ 				nRet = ((SwSetExpField*)pFld)->GetValue();
/*?*/ 				break;
/*?*/ 			case RES_USERFLD:
/*?*/ 				nRet = ((SwUserFieldType*)pFld)->GetValue();
/*?*/ 				break;
/*N*/ 			case RES_TABLEFLD:
/*N*/ 				{
/*N*/ 					SwTblField* pTblFld = (SwTblField*)pFld;
/*N*/ 					if( !pTblFld->IsValid() )		// ist der Wert gueltig ??
/*N*/ 					{
/*N*/ 						// die richtige Tabelle mitgeben!
/*N*/ 						const SwTable* pTmp = rCalcPara.pTbl;
/*N*/ 						rCalcPara.pTbl = &pTxtNd->FindTableNode()->GetTable();
/*N*/ 						pTblFld->CalcField( rCalcPara );
/*N*/ 						rCalcPara.pTbl = pTmp;
/*N*/ 					}
/*N*/ 					nRet = pTblFld->GetValue();
/*N*/ 				}
/*N*/ 				break;
/*N*/
/*N*/ 			case RES_DATETIMEFLD:
/*?*/ 				nRet = ((SwDateTimeField*)pFld)->GetValue();
/*?*/ 				break;
/*?*/
/*?*/ 			case RES_JUMPEDITFLD:
/*?*/ 				//JP 14.09.98: Bug 56112 - der Platzhalter kann nie einen
/*?*/ 				//				gueltigen Inhalt haben!
/*?*/ 				nRet = 0;
/*?*/ 				break;
/*?*/
/*?*/ 			default:
/*?*/ 				nRet = rCalcPara.rCalc.Calculate( pFld->Expand() ).GetDouble();
/*N*/ 			}
/*N*/ 		}
/*N*/ 		else
/*N*/ 		{
/*N*/ 			// Ergebnis ist 0 und kein Fehler!
/*N*/ 			rCalcPara.rCalc.SetCalcError( CALC_NOERR );	// wieder zuruecksetzen
/*N*/
/*N*/ 			double aNum;
/*N*/ 			String sTxt( rTxt.Copy( nSttPos ) );
/*N*/ 			sal_uInt32 nFmtIndex = GetFrmFmt()->GetTblBoxNumFmt().GetValue();
/*N*/
/*N*/ 			SvNumberFormatter* pNumFmtr = pDoc->GetNumberFormatter();
/*N*/
/*N*/ 			if( NUMBERFORMAT_TEXT == nFmtIndex )
/*N*/ 				nFmtIndex = 0;
/*N*/ 			// JP 22.04.98: Bug 49659 - Sonderbehandlung fuer Prozent
/*?*/ 			else if( sTxt.Len() &&
/*?*/ 					NUMBERFORMAT_PERCENT == pNumFmtr->GetType( nFmtIndex ))
/*?*/ 			{
/*?*/ 				sal_uInt32 nTmpFmt = 0;
/*?*/ 				if( pNumFmtr->IsNumberFormat( sTxt, nTmpFmt, aNum ) &&
/*?*/ 					NUMBERFORMAT_NUMBER == pNumFmtr->GetType( nTmpFmt ))
/*?*/ 					sTxt += '%';
/*?*/ 			}
/*N*/
/*N*/ 			if( pNumFmtr->IsNumberFormat( sTxt, nFmtIndex, aNum ))
/*N*/ 				nRet = aNum;
/*N*/ 		}
/*N*/
/*N*/ // ?? sonst ist das ein Fehler
/*N*/ 	} while( FALSE );
/*N*/
/*N*/ 	if( !rCalcPara.IsStackOverFlow() )
/*N*/ 	{
/*N*/ 		rCalcPara.pBoxStk->Remove( pBox );		// raus aus dem Stack
/*N*/ 		rCalcPara.DecStackCnt();
/*N*/ 	}
/*N*/
/*N*/ 	//JP 12.01.99: mit Fehlererkennung, Bug 60794
/*N*/ 	if( DBL_MAX == nRet )
/*?*/ 		rCalcPara.rCalc.SetCalcError( CALC_SYNTAX );	// Fehler setzen
/*N*/
/*N*/ 	return nRet;
/*N*/ }

/*  */

// Struktur, die zum TabelleRechnen benoetigt wird

/*N*/ SwTblCalcPara::SwTblCalcPara( SwCalc& rCalculator, const SwTable& rTable )
/*N*/ 	: rCalc( rCalculator ), pTbl( &rTable ), nStackCnt( 0 ),
/*N*/ 	nMaxSize( cMAXSTACKSIZE ), pLastTblBox( 0 )
/*N*/ {
/*N*/ 	pBoxStk = new SwTableSortBoxes;
/*N*/ }

/*N*/ SwTblCalcPara::~SwTblCalcPara()
/*N*/ {
/*N*/ 	delete pBoxStk;
/*N*/ }


/*  */

/*N*/ SwTableFormula::SwTableFormula( const String& rFormel )
/*N*/ 	: sFormel( rFormel )
/*N*/ {
/*N*/ 	eNmType = EXTRNL_NAME;
/*N*/ 	bValidValue = FALSE;
/*N*/ }

/*N*/ void SwTableFormula::_MakeFormel( const SwTable& rTbl, String& rNewStr,
/*N*/ 					String& rFirstBox, String* pLastBox, void* pPara ) const
/*N*/ {
/*N*/ 	SwTblCalcPara* pCalcPara = (SwTblCalcPara*)pPara;
/*N*/ 	if( pCalcPara->rCalc.IsCalcError() )		// ist schon Fehler gesetzt ?
/*?*/ 		return;
/*N*/
/*N*/ 	SwTableBox* pSttBox, *pEndBox = 0;
/*N*/
/*N*/ 	rFirstBox.Erase(0,1);		// Kennung fuer Box loeschen
/*N*/ 	// ein Bereich in dieser Klammer ?
/*N*/ 	if( pLastBox )
/*N*/ 	{
/*N*/ 	//TODOUNICODE: does it work?
/*N*/ //		pEndBox = (SwTableBox*)(long)(*pLastBox);
/*N*/ 		pEndBox = (SwTableBox*)pLastBox->ToInt32();
/*N*/
/*N*/ 		// ist das ueberhaupt ein gueltiger Pointer ??
/*N*/ 		if( !rTbl.GetTabSortBoxes().Seek_Entry( pEndBox ))
/*?*/ 			pEndBox = 0;
/*N*/ 		rFirstBox.Erase( 0, pLastBox->Len()+1 );
/*N*/ 	}
/*N*/ 	//TODOUNICODE: does it work?
/*N*/ //	pSttBox = (SwTableBox*)(long)rFirstBox;
/*N*/ 	pSttBox = (SwTableBox*)rFirstBox.ToInt32();
/*N*/ 	// ist das ueberhaupt ein gueltiger Pointer ??
/*N*/ 	if( !rTbl.GetTabSortBoxes().Seek_Entry( pSttBox ))
/*?*/ 		pSttBox = 0;
/*N*/
/*N*/ 	rNewStr += ' ';
/*N*/ 	if( pEndBox && pSttBox )	// Bereich ?
/*N*/ 	{
/*N*/ 		// hole ueber das Layout alle "selectierten" Boxen und berechne
/*N*/ 		// deren Werte
/*N*/ 		SwSelBoxes aBoxes;
/*N*/ 		GetBoxes( *pSttBox, *pEndBox, aBoxes );
/*N*/
/*N*/ 		rNewStr += '(';
/*N*/ 		for( USHORT n = 0; n < aBoxes.Count() &&
/*N*/ 						   !pCalcPara->rCalc.IsCalcError(); ++n )
/*N*/ 		{
/*N*/ 			if( n )
/*N*/ 				rNewStr += cListDelim;
/*N*/ 			rNewStr += pCalcPara->rCalc.GetStrResult(
/*N*/ 						aBoxes[n]->GetValue( *pCalcPara ), FALSE );
/*N*/ 		}
/*N*/ 		rNewStr += ')';
/*N*/ 	}
/*N*/ 	else if( pSttBox && !pLastBox )			// nur die StartBox ?
/*N*/ 							//JP 12.01.99: und keine EndBox in der Formel!
/*N*/ 		// Berechne den Wert der Box
/*N*/ 		rNewStr += pCalcPara->rCalc.GetStrResult(
/*N*/ 							pSttBox->GetValue( *pCalcPara ), FALSE );
/*N*/ 	else
/*?*/ 		pCalcPara->rCalc.SetCalcError( CALC_SYNTAX );	// Fehler setzen
/*N*/ 	rNewStr += ' ';
/*N*/ }

void SwTableFormula::BoxNmsToRelNm( const SwTable& rTbl, String& rNewStr,
                    String& rFirstBox, String* pLastBox, void* pPara ) const
{
    // Box-Namen (externe Darstellung) zu relativen Namen
    SwNode* pNd = (SwNode*)pPara;
    ASSERT( pNd, "Feld steht in keinem Node" );
    const SwTableNode* pTblNd = pNd->FindTableNode();

    String sRefBoxNm;
    if( &pTblNd->GetTable() == &rTbl )
    {
        const SwTableBox *pBox = rTbl.GetTblBox(
                pNd->FindTableBoxStartNode()->GetIndex() );
        ASSERT( pBox, "Feld steht in keiner Tabelle" );
        sRefBoxNm = pBox->GetName();
    }

    rNewStr += rFirstBox.Copy(0,1);     // Kennung fuer Box erhalten
    rFirstBox.Erase(0,1);
    if( pLastBox )
    {
        rNewStr += lcl_BoxNmToRel( rTbl, *pTblNd, sRefBoxNm, *pLastBox,
                                eNmType == EXTRNL_NAME );
        rNewStr += ':';
        rFirstBox.Erase( 0, pLastBox->Len()+1 );
    }

    rNewStr += lcl_BoxNmToRel( rTbl, *pTblNd, sRefBoxNm, rFirstBox,
                            eNmType == EXTRNL_NAME );

    // Kennung fuer Box erhalten
    rNewStr += rFirstBox.GetChar( rFirstBox.Len() - 1 );
}


/*N*/ void SwTableFormula::PtrToBoxNms( const SwTable& rTbl, String& rNewStr,
/*N*/ 						String& rFirstBox, String* pLastBox, void* ) const
/*N*/ {
/*N*/ 	// ein Bereich in dieser Klammer ?
/*N*/ 	SwTableBox* pBox;
/*N*/
/*N*/ 	rNewStr += rFirstBox.Copy(0,1);		// Kennung fuer Box erhalten
/*N*/ 	rFirstBox.Erase(0,1);
/*N*/ 	if( pLastBox )
/*N*/ 	{
/*N*/ //		pBox = (SwTableBox*)(long)(*pLastBox);
/*N*/ 		pBox = (SwTableBox*)pLastBox->ToInt32();
/*N*/
/*N*/ 		// ist das ueberhaupt ein gueltiger Pointer ??
/*N*/ 		if( rTbl.GetTabSortBoxes().Seek_Entry( pBox ))
/*N*/ 			rNewStr += pBox->GetName();
/*N*/ 		else
/*N*/ 			rNewStr += '?';
/*N*/ 		rNewStr += ':';
/*N*/ 		rFirstBox.Erase( 0, pLastBox->Len()+1 );
/*N*/ 	}
/*N*/
/*N*/ //	pBox = (SwTableBox*)(long)rFirstBox;
/*N*/ 	pBox = (SwTableBox*)rFirstBox.ToInt32();
/*N*/ 	// ist das ueberhaupt ein gueltiger Pointer ??
/*N*/ 	if( rTbl.GetTabSortBoxes().Seek_Entry( pBox ))
/*N*/ 		rNewStr += pBox->GetName();
/*N*/ 	else
/*N*/ 		rNewStr += '?';
/*N*/
/*N*/ 	// Kennung fuer Box erhalten
/*N*/ 	rNewStr += rFirstBox.GetChar( rFirstBox.Len() - 1 );
/*N*/ }

/*N*/ void SwTableFormula::BoxNmsToPtr( const SwTable& rTbl, String& rNewStr,
/*N*/ 						String& rFirstBox, String* pLastBox, void* ) const
/*N*/ {
/*N*/ 	// ein Bereich in dieser Klammer ?
/*N*/ 	const SwTableBox* pBox;
/*N*/
/*N*/ 	rNewStr += rFirstBox.Copy(0,1);		// Kennung fuer Box erhalten
/*N*/ 	rFirstBox.Erase(0,1);
/*N*/ 	if( pLastBox )
/*N*/ 	{
/*N*/ 		pBox = rTbl.GetTblBox( *pLastBox );
/*N*/ 		rNewStr += String::CreateFromInt32( (long)pBox );
/*N*/ 		rNewStr += ':';
/*N*/ 		rFirstBox.Erase( 0, pLastBox->Len()+1 );
/*N*/ 	}
/*N*/
/*N*/ 	pBox = rTbl.GetTblBox( rFirstBox );
/*N*/ 	rNewStr += String::CreateFromInt32( (long)pBox );
/*N*/
/*N*/ 	// Kennung fuer Box erhalten
/*N*/ 	rNewStr += rFirstBox.GetChar( rFirstBox.Len() - 1 );
/*N*/ }

    // erzeuge die externe (fuer UI) Formel
/*N*/ void SwTableFormula::PtrToBoxNm( const SwTable* pTbl )
/*N*/ {
/*N*/ 	const SwNode* pNd = 0;
/*N*/ 	FnScanFormel fnFormel = 0;
/*N*/ 	switch( eNmType)
/*N*/ 	{
/*N*/ 	case INTRNL_NAME:
/*N*/ 		if( pTbl )
/*N*/ 			fnFormel = &SwTableFormula::PtrToBoxNms;
/*N*/ 		break;
/*N*/ 	case REL_NAME:
/*?*/ 		if( pTbl )
/*?*/ 		{
/*?*/ 			DBG_BF_ASSERT(0, "STRIP"); //STRIP001 fnFormel = &SwTableFormula::RelNmsToBoxNms;
/*?*/ 		}
/*?*/ 		break;
/*N*/ 	case EXTRNL_NAME:
/*N*/ 		return;
/*N*/ 	}
/*?*/ 	sFormel = ScanString( fnFormel, *pTbl, (void*)pNd );
/*?*/ 	eNmType = EXTRNL_NAME;
/*N*/ }

    // erzeuge die interne (in CORE) Formel
/*N*/ void SwTableFormula::BoxNmToPtr( const SwTable* pTbl )
/*N*/ {
/*N*/ 	const SwNode* pNd = 0;
/*N*/ 	FnScanFormel fnFormel = 0;
/*N*/ 	switch( eNmType)
/*N*/ 	{
/*N*/ 	case EXTRNL_NAME:
/*?*/ 		if( pTbl )
/*?*/ 			fnFormel = &SwTableFormula::BoxNmsToPtr;
/*?*/ 		break;
/*?*/ 	case REL_NAME:
/*?*/ 		if( pTbl )
/*?*/ 		{
/*?*/ 			DBG_BF_ASSERT(0, "STRIP"); //STRIP001 fnFormel = &SwTableFormula::RelBoxNmsToPtr;
/*?*/ 		}
/*?*/ 		break;
/*?*/ 	case INTRNL_NAME:
/*?*/ 		return;
/*N*/ 	}
/*N*/ 	sFormel = ScanString( fnFormel, *pTbl, (void*)pNd );
/*N*/ 	eNmType = INTRNL_NAME;
/*N*/ }

    // erzeuge die relative (fuers Kopieren) Formel
 void SwTableFormula::ToRelBoxNm( const SwTable* pTbl )
 {
    const SwNode* pNd = 0;
    FnScanFormel fnFormel = 0;
    switch( eNmType)
    {
    case INTRNL_NAME:
    case EXTRNL_NAME:
        if( pTbl )
        {
            fnFormel = &SwTableFormula::BoxNmsToRelNm;
            pNd = GetNodeOfFormula();
        }
        break;
    case REL_NAME:
        return;
    }
    sFormel = ScanString( fnFormel, *pTbl, (void*)pNd );
    eNmType = REL_NAME;
 }


/*N*/ String SwTableFormula::ScanString( FnScanFormel fnFormel, const SwTable& rTbl,
/*N*/ 									void* pPara ) const
/*N*/ {
/*N*/ 	String aStr;
/*N*/ 	USHORT nFml = 0, nStt = 0, nEnd = 0, nTrenner;
/*N*/
/*N*/ 	do {
/*N*/ 		// falls der Formel ein Name vorangestellt ist, diese Tabelle
/*N*/ 		// benutzen !!
/*N*/ 		const SwTable* pTbl = &rTbl;
/*N*/
/*N*/ 		nStt = sFormel.Search( '<', nFml );
/*N*/ 		if( STRING_NOTFOUND != nStt )
/*N*/ 		{
/*N*/ 			while( STRING_NOTFOUND != nStt &&
/*N*/ 				( ' ' == sFormel.GetChar( nStt + 1 ) ||
/*N*/ 				  '=' == sFormel.GetChar( nStt + 1 ) ) )
/*?*/ 				nStt = sFormel.Search( '<', nStt + 1 );
/*N*/
/*N*/ 			if( STRING_NOTFOUND != nStt )
/*N*/ 				nEnd = sFormel.Search( '>', nStt+1 );
/*N*/ 		}
/*N*/ 		if( STRING_NOTFOUND == nStt || STRING_NOTFOUND == nEnd )
/*N*/ 		{
/*N*/ 			// den Rest setzen und beenden
/*N*/ 			aStr.Insert( sFormel, nFml, sFormel.Len() - nFml );
/*N*/ 			break;
/*N*/ 		}
/*N*/ 		aStr.Insert( sFormel, nFml, nStt - nFml );	// Anfang schreiben
/*N*/
/*N*/ 		if( fnFormel != NULL )
/*N*/ 		{
/*N*/ 			// ist ein TabellenName vorangestellt ??
/*N*/ 			// JP 16.02.99: SplitMergeBoxNm behandeln den Namen selbst
/*N*/ 			// JP 22.02.99: der CAST muss fuer den Linux-Compiler sein
/*N*/ 			// JP 28.06.99: rel. BoxName have no preceding tablename!
/*N*/ 			if( fnFormel != (FnScanFormel)&SwTableFormula::_SplitMergeBoxNm &&
/*N*/ 				1 < sFormel.Len() && cRelKennung != sFormel.GetChar( 1 ) &&
/*N*/ 				STRING_NOTFOUND != ( nTrenner = sFormel.Search( '.', nStt ))
/*N*/ 				&& nTrenner < nEnd )
/*N*/ 			{
/*?*/ 				String sTblNm( sFormel.Copy( nStt, nEnd - nStt ));
/*?*/
/*?*/ 				// falls im Namen schon die Punkte enthalten sind,
/*?*/ 				// treten diese immer paarig auf!!! (A1.1.1 !!)
/*?*/ 				if( (sTblNm.GetTokenCount( '.' ) - 1 ) & 1 )
/*?*/ 				{
/*?*/ 					sTblNm.Erase( nTrenner - nStt );
/*?*/
/*?*/ 					// beim Bauen der Formel ist der TabellenName unerwuenscht
/*?*/ 					//JP 22.02.99: der CAST muss fuer den Linux-Compiler sein
/*?*/ 					if( fnFormel != (FnScanFormel)&SwTableFormula::_MakeFormel )
/*?*/ 						aStr += sTblNm;
/*?*/ 					nStt = nTrenner;
/*?*/
/*?*/ 					sTblNm.Erase( 0, 1 );	// Trenner loeschen
/*?*/ 					if( sTblNm != rTbl.GetFrmFmt()->GetName() )
/*?*/ 					{
/*?*/ 						// dann suchen wir uns mal unsere Tabelle:
/*?*/ 						DBG_BF_ASSERT(0, "STRIP"); //STRIP001 const SwTable* pFnd = FindTable(
/*?*/ 					}
/*?*/ 				}
/*N*/ 			}
/*N*/
/*N*/ 			String sBox( sFormel.Copy( nStt, nEnd - nStt + 1 ));
/*N*/ 			// ein Bereich in dieser Klammer ?
/*N*/ 			if( STRING_NOTFOUND != ( nTrenner = sFormel.Search( ':', nStt ))
/*N*/ 				&& nTrenner < nEnd )
/*N*/ 			{
/*N*/ 				// ohne die Anfangsklammer
/*N*/ 				String aFirstBox( sFormel.Copy( nStt+1, nTrenner - nStt - 1 ));
/*N*/ 				(this->*fnFormel)( *pTbl, aStr, sBox, &aFirstBox, pPara );
/*N*/ 			}
/*N*/ 			else
/*N*/ 				(this->*fnFormel)( *pTbl, aStr, sBox, 0, pPara );
/*N*/ 		}
/*N*/
/*N*/ 		nFml = nEnd+1;
/*N*/ 	} while( TRUE );
/*N*/ 	return aStr;
/*N*/ }


/*  */

/*N*/ const SwFrm* lcl_GetBoxFrm( const SwTableBox& rBox )
/*N*/ {
/*

    // oder besser ueber die Box den Frame suchen

    SwClientIter aIter( *pBox->GetFrmFmt() );
    ULONG nMinPos = ULONG_MAX;
    const SwFrm* pFnd = 0;
    for( SwFrm* pF = (SwFrm*)aIter.First( TYPE( SwCellFrm )); pF;
            pF = (SwFrm*)aIter.Next() )
    {
        if( pF->Frm().Y() <
    }
*/
/*N*/
/*N*/ 	SwNodeIndex aIdx( *rBox.GetSttNd() );
/*N*/ 	SwCntntNode* pCNd = aIdx.GetNodes().GoNext( &aIdx );
/*N*/ 	ASSERT( pCNd, "Box hat keinen TextNode" );
/*N*/ 	Point aPt;		// den im Layout 1. Frame returnen - Tab.Kopfzeile !!
/*N*/ 	return pCNd->GetFrm( &aPt, NULL, FALSE );
/*N*/ }

String lcl_BoxNmToRel( const SwTable& rTbl, const SwTableNode& rTblNd,
                            const String& rRefBoxNm, const String& rGetStr,
                            BOOL bExtrnlNm )
{
    String sCpy( rRefBoxNm );
    String sTmp( rGetStr );
    if( !bExtrnlNm )
    {
        // in die Externe Darstellung umwandeln.
//      SwTableBox* pBox = (SwTableBox*)(long)sTmp;
        SwTableBox* pBox = (SwTableBox*)sTmp.ToInt32();
        if( !rTbl.GetTabSortBoxes().Seek_Entry( pBox ))
            return '?';
        sTmp = pBox->GetName();
    }

    // sollte die es eine Tabellen uebergreifende Formel sein, dann behalte
    // die externe Darstellung bei:
    if( &rTbl == &rTblNd.GetTable() )
    {
        long nBox = SwTable::_GetBoxNum( sTmp, TRUE );
        nBox -= SwTable::_GetBoxNum( sCpy, TRUE );
        long nLine = SwTable::_GetBoxNum( sTmp );
        nLine -= SwTable::_GetBoxNum( sCpy );

        sCpy = sTmp;        //JP 01.11.95: den Rest aus dem BoxNamen anhaengen

        sTmp = cRelKennung;
        sTmp += String::CreateFromInt32( nBox );
        sTmp += cRelTrenner;
        sTmp += String::CreateFromInt32( nLine );

        if( sCpy.Len() )
        {
            sTmp += cRelTrenner;
            sTmp += sCpy;
        }
    }

    if( sTmp.Len() && '>' == sTmp.GetChar( sTmp.Len() - 1 ))
        sTmp.Erase( sTmp.Len()-1 );

    return sTmp;
}

/*N*/ void SwTableFormula::GetBoxes( const SwTableBox& rSttBox,
/*N*/ 								const SwTableBox& rEndBox,
/*N*/ 								SwSelBoxes& rBoxes ) const
/*N*/ {
/*N*/ 	// hole ueber das Layout alle "selektierten" Boxen
/*N*/ 	const SwLayoutFrm *pStt, *pEnd;
/*N*/ 	const SwFrm* pFrm = lcl_GetBoxFrm( rSttBox );
/*N*/ 	pStt = pFrm ? pFrm->GetUpper() : 0;
/*N*/ 	pEnd = ( 0 != (pFrm = lcl_GetBoxFrm( rEndBox ))) ? pFrm->GetUpper() : 0;
/*N*/ 	if( !pStt || !pEnd )
/*?*/ 		return ;			            // no valid selection
/*N*/
/*N*/ 	GetTblSel( pStt, pEnd, rBoxes );
/*N*/
/*N*/ 	const SwTable* pTbl = pStt->FindTabFrm()->GetTable();
/*N*/
/*N*/ 	// filter die Kopfzeilen-Boxen heraus:
/*N*/ 	if( pTbl->IsHeadlineRepeat() )
/*N*/ 		do {	// middle-check loop
/*N*/ 			const SwTableLine* pHeadLine = pTbl->GetTabLines()[0];
/*N*/ 			const SwTableLine* pLine = rSttBox.GetUpper();
/*N*/ 			while( pLine->GetUpper() )
/*?*/ 				pLine = pLine->GetUpper()->GetUpper();
/*N*/
/*N*/ 			if( pLine == pHeadLine )
/*?*/ 				break;		// Headline mit im Bereich !
/*N*/ 			// vielleicht ist ja Start und Ende vertauscht
/*N*/ 			pLine = rEndBox.GetUpper();
/*N*/ 			while ( pLine->GetUpper() )
/*?*/ 				pLine = pLine->GetUpper()->GetUpper();
/*N*/ 			if( pLine == pHeadLine )
/*?*/ 				break;		// Headline mit im Bereich !
/*N*/
/*N*/ 			const SwTabFrm *pTable = pStt->FindTabFrm();
/*N*/ 			const SwTabFrm *pEndTable = pEnd->FindTabFrm();
/*N*/ 			if( pTable == pEndTable )		// keine gespl. Tabelle
/*N*/ 				break;
/*N*/
/*N*/ 			// dann mal die Tabellenkoepfe raus:
/*?*/ 			for( USHORT n = 0; n < rBoxes.Count(); ++n )
/*?*/ 			{
/*?*/ 				while( (pLine = rBoxes[n]->GetUpper())->GetUpper() )
/*?*/ 					pLine = pLine->GetUpper()->GetUpper();
/*?*/
/*?*/ 				if( pLine == pHeadLine )
/*?*/ 					rBoxes.Remove( n--, 1 );
/*?*/ 			}
/*?*/ 		} while( FALSE );
/*N*/ }

    // sind alle Boxen gueltig, auf die sich die Formel bezieht?

USHORT SwTableFormula::GetLnPosInTbl( const SwTable& rTbl, const SwTableBox* pBox )
{
    USHORT nRet = USHRT_MAX;
    if( pBox )
    {
        const SwTableLine* pLn = pBox->GetUpper();
        while( pLn->GetUpper() )
            pLn = pLn->GetUpper()->GetUpper();
        nRet = rTbl.GetTabLines().GetPos( pLn );
    }
    return nRet;
}


    // erzeuge die externe Formel, beachte aber das die Formel
    // in einer gesplitteten/gemergten Tabelle landet
void SwTableFormula::ToSplitMergeBoxNm( SwTableFmlUpdate& rTblUpd )
{
    const SwTable* pTbl;
    const SwNode* pNd = GetNodeOfFormula();
    if( pNd && 0 != ( pNd = pNd->FindTableNode() ))
        pTbl = &((SwTableNode*)pNd)->GetTable();
    else
        pTbl = rTblUpd.pTbl;

    sFormel = ScanString( &SwTableFormula::_SplitMergeBoxNm, *pTbl, (void*)&rTblUpd );
    eNmType = INTRNL_NAME;
}

}
