/*************************************************************************
 *
 *  $RCSfile: sw_hints.cxx,v $
 *
 *  $Revision: 1.1 $
 *
 *  last change: $Author: aw $ $Date: 2003-10-02 15:03:58 $
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

#ifndef _COM_SUN_STAR_I18N_SCRIPTTYPE_HDL_
#include <com/sun/star/i18n/ScriptType.hdl>
#endif
#ifndef _SVX_SCRIPTTYPEITEM_HXX
#include <bf_svx/scripttypeitem.hxx>
#endif

#ifndef _HINTIDS_HXX
#include <hintids.hxx>
#endif
#ifndef _SWTYPES_HXX
#include <swtypes.hxx>
#endif
#ifndef _NDTXT_HXX
#include <ndtxt.hxx>
#endif
#ifndef _ERRHDL_HXX
#include <errhdl.hxx>
#endif
#ifndef _HINTS_HXX
#include <hints.hxx>
#endif
#ifndef _SWERROR_H
#include <error.h>
#endif



/*N*/ SwFmtChg::SwFmtChg( SwFmt *pFmt )
/*N*/ 	: SwMsgPoolItem( RES_FMT_CHG ),
/*N*/ 	pChangedFmt( pFmt )
/*N*/ {}


/*N*/ SwInsChr::SwInsChr( xub_StrLen nP )
/*N*/ 	: SwMsgPoolItem( RES_INS_CHR ),
/*N*/ 	nPos( nP )
/*N*/ {}



/*N*/ SwInsTxt::SwInsTxt( xub_StrLen nP, xub_StrLen nL )
/*N*/ 	: SwMsgPoolItem( RES_INS_TXT ),
/*N*/ 	nPos( nP ),
/*N*/ 	nLen( nL )
/*N*/ {}



/*N*/ SwDelChr::SwDelChr( xub_StrLen nP )
/*N*/ 	: SwMsgPoolItem( RES_DEL_CHR ),
/*N*/ 	nPos( nP )
/*N*/ {}



/*N*/ SwDelTxt::SwDelTxt( xub_StrLen nS, xub_StrLen nL )
/*N*/ 	: SwMsgPoolItem( RES_DEL_TXT ),
/*N*/ 	nStart( nS ),
/*N*/ 	nLen( nL )
/*N*/ {}



/*N*/ SwUpdateAttr::SwUpdateAttr( xub_StrLen nS, xub_StrLen nE, USHORT nW )
/*N*/ 	: SwMsgPoolItem( RES_UPDATE_ATTR ),
/*N*/ 	nStart( nS ),
/*N*/ 	nEnd( nE ),
/*N*/ 	nWhichAttr( nW )
/*N*/ {}


// SwRefMarkFldUpdate wird verschickt, wenn sich die ReferenzMarkierungen
// Updaten sollen. Um Seiten-/KapitelNummer feststellen zu koennen, muss
// der akt. Frame befragt werden. Dafuer wird das akt. OutputDevice benoetigt.


//STRIP001 SwRefMarkFldUpdate::SwRefMarkFldUpdate( const OutputDevice* pOutput )
//STRIP001 	: SwMsgPoolItem( RES_REFMARKFLD_UPDATE ),
//STRIP001 	pOut( pOutput )
//STRIP001 {
//STRIP001 	ASSERT( pOut, "es muss ein OutputDevice-Pointer gesetzt werden!" );
//STRIP001 }


/*N*/ SwDocPosUpdate::SwDocPosUpdate( const SwTwips nDocPos )
/*N*/ 	: SwMsgPoolItem( RES_DOCPOS_UPDATE ),
/*N*/ 	nDocPos(nDocPos)
/*N*/ {}



// SwTableFmlUpdate wird verschickt, wenn sich die Tabelle neu berechnen soll
/*N*/ SwTableFmlUpdate::SwTableFmlUpdate( const SwTable* pNewTbl )
/*N*/ 	: SwMsgPoolItem( RES_TABLEFML_UPDATE ),
/*N*/ 	pTbl( pNewTbl ), pHistory( 0 ), eFlags( TBL_CALC ),
/*N*/ 	nSplitLine( USHRT_MAX )
/*N*/ {
/*N*/ 	DATA.pDelTbl = 0;
/*N*/ 	bModified = bBehindSplitLine = FALSE;
/*N*/ 	ASSERT( pTbl, "es muss ein Table-Pointer gesetzt werden!" );
/*N*/ }


/*N*/ SwAutoFmtGetDocNode::SwAutoFmtGetDocNode( const SwNodes* pNds )
/*N*/ 	: SwMsgPoolItem( RES_AUTOFMT_DOCNODE ),
/*N*/ 	pCntntNode( 0 ), pNodes( pNds )
/*N*/ {}


/*N*/ SwAttrSetChg::SwAttrSetChg( const SwAttrSet& rTheSet, SwAttrSet& rSet )
/*N*/ 	: SwMsgPoolItem( RES_ATTRSET_CHG ),
/*N*/ 	pTheChgdSet( &rTheSet ),
/*N*/ 	pChgSet( &rSet ),
/*N*/ 	bDelSet( FALSE )
/*N*/ {}


/*N*/ SwAttrSetChg::SwAttrSetChg( const SwAttrSetChg& rChgSet )
/*N*/ 	: SwMsgPoolItem( RES_ATTRSET_CHG ),
/*N*/ 	pTheChgdSet( rChgSet.pTheChgdSet ),
/*N*/ 	bDelSet( TRUE )
/*N*/ {
/*N*/ 	pChgSet = new SwAttrSet( *rChgSet.pChgSet );
/*N*/ }


/*N*/ SwAttrSetChg::~SwAttrSetChg()
/*N*/ {
/*N*/ 	if( bDelSet )
/*N*/ 		delete pChgSet;
/*N*/ }


#ifndef PRODUCT

/*N*/ void SwAttrSetChg::ClearItem( USHORT nWhich )
/*N*/ {
/*N*/ 	ASSERT( bDelSet, "der Set darf nicht veraendert werden!" );
/*N*/ 	pChgSet->ClearItem( nWhich );
/*N*/ }

#endif


/*N*/ SwMsgPoolItem::SwMsgPoolItem( USHORT nWhich )
/*N*/ 	: SfxPoolItem( nWhich )
/*N*/ {}


// "Overhead" vom SfxPoolItem
/*N*/ int SwMsgPoolItem::operator==( const SfxPoolItem& ) const
/*N*/ {
/*N*/ 	ASSERT( FALSE, "SwMsgPoolItem kennt kein ==" );
/*N*/ 	return 0;
/*N*/ }


/*N*/ SfxPoolItem* SwMsgPoolItem::Clone( SfxItemPool* ) const
/*N*/ {
/*N*/ 	ASSERT( FALSE, "SwMsgPoolItem kennt kein Clone" );
/*N*/ 	return 0;
/*N*/ }

/******************************************************************************
 * hole aus der Default-Attribut Tabelle ueber den Which-Wert
 * das entsprechende default Attribut.
 * Ist keines vorhanden, returnt ein 0-Pointer !!!
 * inline (hintids.hxx) im PRODUCT.
 ******************************************************************************/
#ifndef PRODUCT


/*N*/ const SfxPoolItem* GetDfltAttr( USHORT nWhich )
/*N*/ {
/*N*/ 	ASSERT_ID( nWhich < POOLATTR_END && nWhich >= POOLATTR_BEGIN,
/*N*/ 			   ERR_OUTOFSCOPE );
/*N*/ 
/*N*/ 	SfxPoolItem *pHt = aAttrTab[ nWhich - POOLATTR_BEGIN ];
/*N*/ 	ASSERT( pHt, "GetDfltFmtAttr(): Dflt == 0" );
/*N*/ 	return pHt;
/*N*/ }

#endif



/*N*/ SwCondCollCondChg::SwCondCollCondChg( SwFmt *pFmt )
/*N*/ 	: SwMsgPoolItem( RES_CONDCOLL_CONDCHG ), pChangedFmt( pFmt )
/*N*/ {
/*N*/ }


/*N*/ SwVirtPageNumInfo::SwVirtPageNumInfo( const SwPageFrm *pPg ) :
/*N*/ 	SwMsgPoolItem( RES_VIRTPAGENUM_INFO ),
/*N*/ 	pPage( 0 ),
/*N*/ 	pOrigPage( pPg ),
/*N*/ 	pFrm( 0 )
/*N*/ {
/*N*/ }

/*N*/ SwNumRuleInfo::SwNumRuleInfo( const String& rRuleName )
/*N*/ 	: SwMsgPoolItem( RES_GETNUMNODES ), rName( rRuleName )
/*N*/ {
/*N*/ }

/*N*/ void SwNumRuleInfo::AddNode( SwTxtNode& rNd )
/*N*/ {
/*N*/ 	aList.Insert( rNd.GetIndex(), &rNd );
/*N*/ }

//STRIP001 SwNRuleLowerLevel::SwNRuleLowerLevel( const String& rRuleName, BYTE nSrchLvl )
//STRIP001 	: SwMsgPoolItem( RES_GETLOWERNUMLEVEL ), rName( rRuleName ),
//STRIP001 	nLvl(nSrchLvl)
//STRIP001 {
//STRIP001 }


//STRIP001 SwFindNearestNode::SwFindNearestNode( const SwNode& rNd )
//STRIP001 	: SwMsgPoolItem( RES_FINDNEARESTNODE ), pNd( &rNd ), pFnd( 0 )
//STRIP001 {
//STRIP001 }

//STRIP001 void SwFindNearestNode::CheckNode( const SwNode& rNd )
//STRIP001 {
//STRIP001 	if( &pNd->GetNodes() == &rNd.GetNodes() )
//STRIP001 	{
//STRIP001 		ULONG nIdx = rNd.GetIndex();
//STRIP001 		if( nIdx < pNd->GetIndex() &&
//STRIP001 			( !pFnd || nIdx > pFnd->GetIndex() ) &&
//STRIP001 			nIdx > rNd.GetNodes().GetEndOfExtras().GetIndex() )
//STRIP001 			pFnd = &rNd;
//STRIP001 	}
//STRIP001 }



/*N*/ USHORT GetWhichOfScript( USHORT nWhich, USHORT nScript )
/*N*/ {
/*N*/ 	static const USHORT aLangMap[3] =
/*N*/ 		{ RES_CHRATR_LANGUAGE, RES_CHRATR_CJK_LANGUAGE, RES_CHRATR_CTL_LANGUAGE };
/*N*/ 	static const USHORT aFontMap[3] =
/*N*/ 		{ RES_CHRATR_FONT, RES_CHRATR_CJK_FONT,  RES_CHRATR_CTL_FONT};
/*N*/ 	static const USHORT aFontSizeMap[3] =
/*N*/ 		{ RES_CHRATR_FONTSIZE, RES_CHRATR_CJK_FONTSIZE,  RES_CHRATR_CTL_FONTSIZE };
/*N*/ 	static const USHORT aWeightMap[3] =
/*N*/ 		{ RES_CHRATR_WEIGHT, RES_CHRATR_CJK_WEIGHT,  RES_CHRATR_CTL_WEIGHT};
/*N*/ 	static const USHORT aPostureMap[3] =
/*N*/ 		{ RES_CHRATR_POSTURE, RES_CHRATR_CJK_POSTURE,  RES_CHRATR_CTL_POSTURE};
/*N*/ 
/*N*/ 	const USHORT* pM;
/*N*/ 	switch( nWhich )
/*N*/ 	{
/*N*/ 	case RES_CHRATR_LANGUAGE:
/*N*/ 	case RES_CHRATR_CJK_LANGUAGE:
/*N*/ 	case RES_CHRATR_CTL_LANGUAGE:
/*N*/ 		pM = aLangMap;
/*N*/ 		break;
/*N*/ 
/*N*/ 	case RES_CHRATR_FONT:
/*N*/ 	case RES_CHRATR_CJK_FONT:
/*N*/ 	case RES_CHRATR_CTL_FONT:
/*N*/ 		pM = aFontMap;
/*N*/ 		break;
/*N*/ 
/*N*/ 	case RES_CHRATR_FONTSIZE:
/*N*/ 	case RES_CHRATR_CJK_FONTSIZE:
/*N*/ 	case RES_CHRATR_CTL_FONTSIZE:
/*N*/ 		pM = aFontSizeMap;
/*N*/ 		break;
/*N*/ 
/*N*/ 	case  RES_CHRATR_WEIGHT:
/*N*/ 	case  RES_CHRATR_CJK_WEIGHT:
/*N*/ 	case  RES_CHRATR_CTL_WEIGHT:
/*N*/ 		pM = aWeightMap;
/*N*/ 		break;
/*N*/ 	case RES_CHRATR_POSTURE:
/*N*/ 	case RES_CHRATR_CJK_POSTURE:
/*N*/ 	case RES_CHRATR_CTL_POSTURE:
/*N*/ 		pM = aPostureMap;
/*N*/ 		break;
/*N*/ 
/*N*/ 	default:
/*N*/ 		pM = 0;
/*N*/ 	}
/*N*/ 
/*N*/ 	USHORT nRet;
/*N*/ 	if( pM )
/*N*/ 	{
/*N*/ 		using namespace ::com::sun::star::i18n;
/*N*/ 		{
/*N*/ 			if( ScriptType::WEAK == nScript )
/*N*/ 			   nScript = GetI18NScriptTypeOfLanguage( (USHORT)GetAppLanguage() );
/*N*/ 			switch( nScript)
/*N*/ 			{
/*N*/ 			case ScriptType::COMPLEX:	++pM;  // no break;
/*N*/ 			case ScriptType::ASIAN:		++pM;  // no break;
/*N*/ 			default:					nRet = *pM;
/*N*/ 			}
/*N*/ 		}
/*N*/ 	}
/*N*/ 	else
/*N*/ 		nRet = nWhich;
/*N*/ 	return nRet;
/*N*/ }
