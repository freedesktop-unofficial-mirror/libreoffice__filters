/*************************************************************************
 *
 *  $RCSfile: sw_reffld.cxx,v $
 *
 *  $Revision: 1.4 $
 *
 *  last change: $Author: rt $ $Date: 2004-05-05 16:40:57 $
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

#define _SVSTDARR_USHORTSSORT
#define _SVSTDARR_USHORTS
#include <svtools/svstdarr.hxx>

#ifndef _COM_SUN_STAR_TEXT_REFERENCEFIELDPART_HPP_
#include <com/sun/star/text/ReferenceFieldPart.hpp>
#endif
#ifndef _COM_SUN_STAR_TEXT_REFERENCEFIELDSOURCE_HPP_
#include <com/sun/star/text/ReferenceFieldSource.hpp>
#endif
#ifndef _UNOTOOLS_LOCALEDATAWRAPPER_HXX
#include <unotools/localedatawrapper.hxx>
#endif
#ifndef _COM_SUN_STAR_LANG_XMULTISERVICEFACTORY_HPP_
#include <com/sun/star/lang/XMultiServiceFactory.hpp>
#endif
#ifndef _COMPHELPER_PROCESSFACTORY_HXX_
#include <comphelper/processfactory.hxx>
#endif
#ifndef _UNO_LINGU_HXX
#include <bf_svx/unolingu.hxx>
#endif

#ifndef _DOC_HXX
#include <doc.hxx>
#endif
#ifndef _PAM_HXX
#include <pam.hxx>
#endif
#ifndef _CNTFRM_HXX
#include <cntfrm.hxx>
#endif
#ifndef _PAGEFRM_HXX
#include <pagefrm.hxx>
#endif
#ifndef _DOCARY_HXX
#include <docary.hxx>
#endif
#ifndef _FMTFLD_HXX //autogen
#include <fmtfld.hxx>
#endif
#ifndef _TXTFLD_HXX //autogen
#include <txtfld.hxx>
#endif
#ifndef _TXTFTN_HXX //autogen
#include <txtftn.hxx>
#endif
#ifndef _FMTRFMRK_HXX //autogen
#include <fmtrfmrk.hxx>
#endif
#ifndef _TXTRFMRK_HXX //autogen
#include <txtrfmrk.hxx>
#endif
#ifndef _FMTFTN_HXX //autogen
#include <fmtftn.hxx>
#endif
#ifndef _NDTXT_HXX
#include <ndtxt.hxx>
#endif
#ifndef _CHPFLD_HXX
#include <chpfld.hxx>
#endif
#ifndef _REFFLD_HXX
#include <reffld.hxx>
#endif
#ifndef _EXPFLD_HXX
#include <expfld.hxx>
#endif
#ifndef _TXTFRM_HXX
#include <txtfrm.hxx>
#endif
#ifndef _FLYFRM_HXX
#include <flyfrm.hxx>
#endif
#ifndef _PAGEDESC_HXX
#include <pagedesc.hxx>
#endif
#ifndef _BOOKMRK_HXX
#include <bookmrk.hxx>
#endif
#ifndef _FTNIDX_HXX
#include <ftnidx.hxx>
#endif
#ifndef _VIEWSH_HXX
#include <viewsh.hxx>
#endif
#ifndef _UNOFLDMID_H
#include <unofldmid.h>
#endif
#ifndef _SWSTYLENAMEMAPPER_HXX
#include <SwStyleNameMapper.hxx>
#endif
#ifndef _SHELLRES_HXX
#include <shellres.hxx>
#endif
#ifndef _POOLFMT_HXX
#include <poolfmt.hxx>
#endif
#ifndef _POOLFMT_HRC
#include <poolfmt.hrc>
#endif
#ifndef _LEGACYBINFILTERMGR_HXX
#include <legacysmgr/legacy_binfilters_smgr.hxx>	//STRIP002 
#endif
namespace binfilter {
extern String& GetString( const ::com::sun::star::uno::Any& rAny, String& rStr ); //STRIP008
using namespace ::com::sun::star;
using namespace ::com::sun::star::text;
using namespace ::com::sun::star::lang;
using namespace ::rtl;

//STRIP001 extern void InsertSort( SvUShorts& rArr, USHORT nIdx, USHORT* pInsPos = 0 );

/*N*/ void lcl_GetLayTree( const SwFrm* pFrm, SvPtrarr& rArr )
/*N*/ {
/*N*/ 	while( pFrm )
/*N*/ 	{
/*N*/ 		if( pFrm->IsBodyFrm() )		// soll uns nicht weiter interessieren
/*N*/ 			pFrm = pFrm->GetUpper();
/*N*/ 		else
/*N*/ 		{
/*N*/ 			void* p = (void*)pFrm;
/*N*/ 			rArr.Insert( p, rArr.Count() );
/*N*/ 
/*N*/ 			// bei der Seite ist schluss
/*N*/ 			if( pFrm->IsPageFrm() )
/*N*/ 				break;
/*N*/ 
/*N*/ 			if( pFrm->IsFlyFrm() )
/*N*/ 				pFrm = ((SwFlyFrm*)pFrm)->GetAnchor();
/*N*/ 			else
/*N*/ 				pFrm = pFrm->GetUpper();
/*N*/ 		}
/*N*/ 	}
/*N*/ }


/*N*/ BOOL IsFrameBehind( const SwTxtNode& rMyNd, USHORT nMySttPos,
/*N*/ 					const SwTxtNode& rBehindNd, USHORT nSttPos )
/*N*/ {
/*N*/ 	const SwTxtFrm *pMyFrm = (SwTxtFrm*)rMyNd.GetFrm(0,0,FALSE),
/*N*/ 				   *pFrm = (SwTxtFrm*)rBehindNd.GetFrm(0,0,FALSE);
/*N*/ 
/*N*/ 	while( pFrm && !pFrm->IsInside( nSttPos ) )
/*N*/ 		pFrm = (SwTxtFrm*)pFrm->GetFollow();
/*N*/ 	while( pMyFrm && !pMyFrm->IsInside( nMySttPos ) )
/*N*/ 		pMyFrm = (SwTxtFrm*)pMyFrm->GetFollow();
/*N*/ 
/*N*/ 	if( !pFrm || !pMyFrm || pFrm == pMyFrm )
/*N*/ 		return FALSE;
/*N*/ 
/*N*/ 	SvPtrarr aRefArr( 10, 10 ), aArr( 10, 10 );
/*N*/ 	::binfilter::lcl_GetLayTree( pFrm, aRefArr );
/*N*/ 	::binfilter::lcl_GetLayTree( pMyFrm, aArr );
/*N*/ 
/*N*/ 	USHORT nRefCnt = aRefArr.Count() - 1, nCnt = aArr.Count() - 1;
/*N*/ #ifdef VERTICAL_LAYOUT
/*N*/     BOOL bVert = FALSE;
/*N*/     BOOL bR2L = FALSE;
/*N*/ #endif
/*N*/ 
/*N*/ 	// solange bis ein Frame ungleich ist ?
/*N*/ 	while( nRefCnt && nCnt && aRefArr[ nRefCnt ] == aArr[ nCnt ] )
/*N*/     {
/*N*/ #ifdef VERTICAL_LAYOUT
/*N*/         const SwFrm* pFrm = (const SwFrm*)aArr[ nCnt ];
/*N*/         bVert = pFrm->IsVertical();
/*N*/         bR2L = pFrm->IsRightToLeft();
/*N*/ #endif
/*N*/ 		--nCnt, --nRefCnt;
/*N*/     }
/*N*/ 
/*N*/ 	// sollte einer der Counter ueberlaeufen?
/*N*/ 	if( aRefArr[ nRefCnt ] == aArr[ nCnt ] )
/*N*/ 	{
/*N*/ 		if( nCnt )
/*N*/ 			--nCnt;
/*N*/ 		else
/*N*/ 			--nRefCnt;
/*N*/ 	}
/*N*/ 
/*N*/ 	const SwFrm* pRefFrm = (const SwFrm*)aRefArr[ nRefCnt ];
/*N*/ 	const SwFrm* pFldFrm = (const SwFrm*)aArr[ nCnt ];
/*N*/ 
/*N*/ 	// unterschiedliche Frames, dann ueberpruefe deren Y-/X-Position
/*N*/ 	BOOL bRefIsLower;
/*N*/ 	if( ( FRM_COLUMN | FRM_CELL ) & pFldFrm->GetType() ||
/*N*/ 		( FRM_COLUMN | FRM_CELL ) & pRefFrm->GetType() )
/*N*/ 	{
/*?*/ 		if( pFldFrm->GetType() == pRefFrm->GetType() )
/*?*/ 		{
/*?*/ 			// hier ist die X-Pos wichtiger!
/*?*/ #ifdef VERTICAL_LAYOUT
/*?*/             if( bVert )
/*?*/             {
/*?*/                 if( bR2L )
/*?*/                     bRefIsLower = pRefFrm->Frm().Top() < pFldFrm->Frm().Top() ||
/*?*/                             ( pRefFrm->Frm().Top() == pFldFrm->Frm().Top() &&
/*?*/                               pRefFrm->Frm().Left() < pFldFrm->Frm().Left() );
/*?*/                 else
/*?*/                     bRefIsLower = pRefFrm->Frm().Top() < pFldFrm->Frm().Top() ||
/*?*/                             ( pRefFrm->Frm().Top() == pFldFrm->Frm().Top() &&
/*?*/                               pRefFrm->Frm().Left() > pFldFrm->Frm().Left() );
/*?*/             }
/*?*/             else if( bR2L )
/*?*/                 bRefIsLower = pRefFrm->Frm().Left() > pFldFrm->Frm().Left() ||
/*?*/                             ( pRefFrm->Frm().Left() == pFldFrm->Frm().Left() &&
/*?*/                               pRefFrm->Frm().Top() < pFldFrm->Frm().Top() );
/*?*/             else
/*?*/                 bRefIsLower = pRefFrm->Frm().Left() < pFldFrm->Frm().Left() ||
/*?*/                             ( pRefFrm->Frm().Left() == pFldFrm->Frm().Left() &&
/*?*/                               pRefFrm->Frm().Top() < pFldFrm->Frm().Top() );
/*?*/ #else
/*?*/ 			bRefIsLower = pRefFrm->Frm().Left() < pFldFrm->Frm().Left() ||
/*?*/ 					( pRefFrm->Frm().Left() == pFldFrm->Frm().Left() &&
/*?*/ 						pRefFrm->Frm().Top() < pFldFrm->Frm().Top() );
/*?*/ #endif
/*?*/ 			pRefFrm = 0;
/*?*/ 		}
/*?*/ 		else if( ( FRM_COLUMN | FRM_CELL ) & pFldFrm->GetType() )
/*?*/ 			pFldFrm = (const SwFrm*)aArr[ nCnt - 1 ];
/*?*/ 		else
/*?*/ 			pRefFrm = (const SwFrm*)aRefArr[ nRefCnt - 1 ];
/*N*/ 	}
/*N*/ 
/*N*/ 	if( pRefFrm ) 				// als Flag missbrauchen
/*N*/ #ifdef VERTICAL_LAYOUT
/*N*/     {
/*N*/         if( bVert )
/*N*/         {
/*?*/             if( bR2L )
/*?*/                 bRefIsLower = pRefFrm->Frm().Left() < pFldFrm->Frm().Left() ||
/*?*/                             ( pRefFrm->Frm().Left() == pFldFrm->Frm().Left() &&
/*?*/                                 pRefFrm->Frm().Top() < pFldFrm->Frm().Top() );
/*?*/             else
/*?*/                 bRefIsLower = pRefFrm->Frm().Left() > pFldFrm->Frm().Left() ||
/*?*/                             ( pRefFrm->Frm().Left() == pFldFrm->Frm().Left() &&
/*?*/                                 pRefFrm->Frm().Top() < pFldFrm->Frm().Top() );
/*N*/         }
/*N*/         else if( bR2L )
/*N*/             bRefIsLower = pRefFrm->Frm().Top() < pFldFrm->Frm().Top() ||
/*N*/                         ( pRefFrm->Frm().Top() == pFldFrm->Frm().Top() &&
/*N*/                             pRefFrm->Frm().Left() > pFldFrm->Frm().Left() );
/*N*/         else
/*N*/             bRefIsLower = pRefFrm->Frm().Top() < pFldFrm->Frm().Top() ||
/*N*/                         ( pRefFrm->Frm().Top() == pFldFrm->Frm().Top() &&
/*N*/                             pRefFrm->Frm().Left() < pFldFrm->Frm().Left() );
/*N*/     }
/*N*/ #else
/*N*/ 		bRefIsLower = pRefFrm->Frm().Top() < pFldFrm->Frm().Top() ||
/*N*/ 					( pRefFrm->Frm().Top() == pFldFrm->Frm().Top() &&
/*N*/ 						pRefFrm->Frm().Left() < pFldFrm->Frm().Left() );
/*N*/ #endif
/*N*/ 	return bRefIsLower;
/*N*/ }

/*--------------------------------------------------------------------
    Beschreibung: Referenzen holen
 --------------------------------------------------------------------*/


/*N*/ SwGetRefField::SwGetRefField( SwGetRefFieldType* pFldType,
/*N*/ 							  const String& rSetRef, USHORT nSubTyp,
/*N*/ 							  USHORT nSeqenceNo, ULONG nFmt )
/*N*/ 	: SwField( pFldType, nFmt ), sSetRefName( rSetRef ),
/*N*/ 	nSubType( nSubTyp ), nSeqNo( nSeqenceNo )
/*N*/ {
/*N*/ }

/*N*/ USHORT SwGetRefField::GetSubType() const
/*N*/ {
/*N*/ 	return nSubType;
/*N*/ }

void SwGetRefField::SetSubType( USHORT n )
{
    nSubType = n;
}

/*N*/ String SwGetRefField::Expand() const
/*N*/ {
/*N*/ 	return sTxt;
/*N*/ }


/*N*/ String SwGetRefField::GetCntnt(BOOL bName) const
/*N*/ {
/*N*/ 	if( !bName )
/*N*/ 		return Expand();
/*N*/ 
/*?*/ 	String aStr(GetTyp()->GetName());
/*?*/ 	aStr += ' ';
/*?*/ 	aStr += sSetRefName;
/*?*/ 	return aStr;
/*N*/ }


/*N*/ void SwGetRefField::UpdateField()
/*N*/ {
/*N*/ 	sTxt.Erase();
/*N*/ 
/*N*/ 	SwDoc* pDoc = ((SwGetRefFieldType*)GetTyp())->GetDoc();
/*N*/ 	USHORT nStt, nEnd;
/*N*/ 	SwTxtNode* pTxtNd = SwGetRefFieldType::FindAnchor( pDoc, sSetRefName,
/*N*/ 										nSubType, nSeqNo, &nStt, &nEnd );
/*N*/ 	if( !pTxtNd )
/*N*/ 		return ;
/*N*/ 
/*N*/ 	switch( GetFormat() )
/*N*/ 	{
/*N*/ 	case REF_CONTENT:
/*N*/ 	case REF_ONLYNUMBER:
/*N*/ 	case REF_ONLYCAPTION:
/*N*/ 	case REF_ONLYSEQNO:
/*N*/ 		{
/*N*/ 			switch( nSubType )
/*N*/ 			{
/*N*/ 			case REF_SEQUENCEFLD:
/*N*/ 				nEnd = pTxtNd->GetTxt().Len();
/*N*/ 				switch( GetFormat() )
/*N*/ 				{
/*N*/ 				case REF_ONLYNUMBER:
/*N*/ 					if( nStt + 1 < nEnd )
/*N*/ 						nEnd = nStt + 1;
/*N*/ 					nStt = 0;
/*N*/ 					break;
/*N*/ 
/*N*/ 				case REF_ONLYCAPTION:
/*N*/ 					{
/*N*/ 						const SwTxtAttr* pTxtAttr = pTxtNd->GetTxtAttr( nStt,
/*N*/ 														RES_TXTATR_FIELD );
/*N*/ 						if( pTxtAttr )
/*N*/ 							nStt = SwGetExpField::GetReferenceTextPos(
/*N*/ 												pTxtAttr->GetFld(), *pDoc );
/*N*/ 						else if( nStt + 1 < nEnd )
/*N*/ 							++nStt;
/*N*/ 					}
/*N*/ 					break;
/*N*/ 
/*N*/ 				case REF_ONLYSEQNO:
/*N*/ 					if( nStt + 1 < nEnd )
/*N*/ 						nEnd = nStt + 1;
/*N*/ 					break;
/*N*/ 
/*N*/ 				default:
/*N*/ 					nStt = 0;
/*N*/ 					break;
/*N*/ 				}
/*N*/ 				break;
/*N*/ 
/*N*/ 			case REF_BOOKMARK:
/*N*/ 				if( USHRT_MAX == nEnd )
/*N*/ 				{
/*N*/ 					// Text steht ueber verschiedene Nodes verteilt.
/*N*/ 					// Gesamten Text oder nur bis zum Ende vom Node?
/*N*/ 					nEnd = pTxtNd->GetTxt().Len();
/*N*/ 				}
/*N*/ 				break;
/*N*/ 
/*N*/ 			case REF_OUTLINE:
/*N*/ 				break;
/*N*/ 
/*N*/ 			case REF_FOOTNOTE:
/*N*/ 			case REF_ENDNOTE:
/*N*/ 				{
/*N*/ 					// die Nummer oder den NumString besorgen
/*N*/ 					USHORT n, nFtnCnt = pDoc->GetFtnIdxs().Count();
/*N*/ 					SwTxtFtn* pFtnIdx;
/*N*/ 					for( n = 0; n < nFtnCnt; ++n )
/*N*/ 						if( nSeqNo == (pFtnIdx = pDoc->GetFtnIdxs()[ n ])->GetSeqRefNo() )
/*N*/ 						{
/*N*/ 							sTxt = pFtnIdx->GetFtn().GetViewNumStr( *pDoc );
/*N*/ 							break;
/*N*/ 						}
/*N*/ 					nStt = nEnd;		// kein Bereich, der String ist fertig
/*N*/ 				}
/*N*/ 				break;
/*N*/ 			}
/*N*/ 
/*N*/ 			if( nStt != nEnd )		// ein Bereich?
/*N*/ 			{
/*N*/ 				sTxt = pTxtNd->GetExpandTxt( nStt, nEnd - nStt, FALSE );
/*N*/ 
/*N*/ 				// alle Sonderzeichen entfernen (durch Blanks ersetzen):
/*N*/ 				if( sTxt.Len() )
/*N*/                 {
/*N*/                     sTxt.EraseAllChars( 0xad );
/*N*/                     for( sal_Unicode* p = sTxt.GetBufferAccess(); *p; ++p )
/*N*/ 					{
/*N*/ 						if( *p < 0x20 )
/*N*/ 							*p = 0x20;
/*N*/                         else if(*p == 0x2011)
/*N*/ 							*p = '-';
/*N*/ 					}
/*N*/                 }
/*N*/ 			}
/*N*/ 		}
/*N*/ 		break;
/*N*/ 
/*N*/ 	case REF_PAGE:
/*N*/ 	case REF_PAGE_PGDESC:
/*N*/ 		{
/*N*/ 			const SwTxtFrm* pFrm = (SwTxtFrm*)pTxtNd->GetFrm(0,0,FALSE),
/*N*/ 						*pSave = pFrm;
/*N*/ 			while( pFrm && !pFrm->IsInside( nStt ) )
/*N*/ 				pFrm = (SwTxtFrm*)pFrm->GetFollow();
/*N*/ 
/*N*/ 			if( pFrm || 0 != ( pFrm = pSave ))
/*N*/ 			{
/*N*/ 				USHORT nPageNo = pFrm->GetVirtPageNum();
/*N*/ 				const SwPageFrm *pPage;
/*N*/ 				if( REF_PAGE_PGDESC == GetFormat() &&
/*N*/ 					0 != ( pPage = pFrm->FindPageFrm() ) &&
/*N*/ 					pPage->GetPageDesc() )
/*N*/ 					sTxt = pPage->GetPageDesc()->GetNumType().GetNumStr( nPageNo );
/*N*/ 				else
/*N*/ 					sTxt = String::CreateFromInt32(nPageNo);
/*N*/ 			}
/*N*/ 		}
/*N*/ 		break;
/*N*/ 
/*N*/ 	case REF_CHAPTER:
/*N*/ 		{
/*N*/ 			// ein bischen trickreich: suche irgend einen Frame
/*N*/ 			const SwFrm* pFrm = pTxtNd->GetFrm();
/*N*/ 			if( pFrm )
/*N*/ 			{
/*N*/ 				SwChapterFieldType aFldTyp;
/*N*/ 				SwChapterField aFld( &aFldTyp, 0 );
/*N*/ 				aFld.SetLevel( MAXLEVEL - 1 );
/*N*/ 				aFld.ChangeExpansion( pFrm, pTxtNd, TRUE );
/*N*/ 				sTxt = aFld.GetNumber();
/*N*/ 			}
/*N*/ 		}
/*N*/ 		break;
/*N*/ 
/*N*/ 	case REF_UPDOWN:
/*N*/ 		{
/*N*/ 			const SwTxtFld* pTFld = 0;
/*N*/ 
/*N*/ 			{
/*N*/ 				SwClientIter aIter( *GetTyp() );
/*N*/ 				for( SwFmtFld* pFld = (SwFmtFld*)aIter.First( TYPE(SwFmtFld) );
/*N*/ 						pFld; pFld = (SwFmtFld*)aIter.Next() )
/*N*/ 					if( pFld->GetFld() == this )
/*N*/ 					{
/*N*/ 						pTFld = pFld->GetTxtFld();
/*N*/ 						break;
/*N*/ 					}
/*N*/ 			}
/*N*/ 
/*N*/ 			if( !pTFld || !pTFld->GetpTxtNode() )	// noch nicht im Node gestezt?
/*N*/ 				break;
/*N*/ 
/*N*/ 			LocaleDataWrapper aLocaleData(
/*N*/ 							::legacy_binfilters::getLegacyProcessServiceFactory(),
/*N*/ 							SvxCreateLocale( GetLanguage() ) );
/*N*/ 
/*N*/ 			// erstmal ein "Kurz" - Test - falls beide im selben
/*N*/ 			// Node stehen!
/*N*/ 			if( pTFld->GetpTxtNode() == pTxtNd )
/*N*/ 			{
/*N*/ 				sTxt = nStt < *pTFld->GetStart()
/*N*/ 							? aLocaleData.getAboveWord()
/*N*/ 							: aLocaleData.getBelowWord();
/*N*/ 				break;
/*N*/ 			}
/*N*/ 
/*N*/ 			sTxt = ::binfilter::IsFrameBehind( *pTFld->GetpTxtNode(), *pTFld->GetStart(),
/*N*/ 									*pTxtNd, nStt )
/*N*/ 						? aLocaleData.getAboveWord()
/*N*/ 						: aLocaleData.getBelowWord();
/*N*/ 		}
/*N*/ 		break;
/*N*/ 	}
/*N*/ }


/*N*/ SwField* SwGetRefField::Copy() const
/*N*/ {
/*N*/ 	SwGetRefField* pFld = new SwGetRefField( (SwGetRefFieldType*)GetTyp(),
/*N*/ 												sSetRefName, nSubType,
/*N*/ 												nSeqNo, GetFormat() );
/*N*/ 	pFld->sTxt = sTxt;
/*N*/ 	return pFld;
/*N*/ }

/*--------------------------------------------------------------------
    Beschreibung: ReferenzName holen
 --------------------------------------------------------------------*/


/*N*/ const String& SwGetRefField::GetPar1() const
/*N*/ {
/*N*/ 	return sSetRefName;
/*N*/ }


void SwGetRefField::SetPar1( const String& rName )
{
    sSetRefName = rName;
}


String SwGetRefField::GetPar2() const
{
    return Expand();
}

/*-----------------06.03.98 13:34-------------------

--------------------------------------------------*/
/*N*/ BOOL SwGetRefField::QueryValue( uno::Any& rAny, BYTE nMId ) const
/*N*/ {
/*N*/     nMId &= ~CONVERT_TWIPS;
/*N*/ 	switch( nMId )
/*N*/ 	{
/*N*/ 	case FIELD_PROP_USHORT1:
/*N*/ 		{
/*N*/ 			sal_Int16 nPart = 0;
/*N*/ 			switch(GetFormat())
/*N*/ 			{
/*N*/ 			case REF_PAGE		: nPart = ReferenceFieldPart::PAGE 				  ; break;
/*N*/ 			case REF_CHAPTER	: nPart = ReferenceFieldPart::CHAPTER	 		  ; break;
/*N*/ 			case REF_CONTENT	: nPart = ReferenceFieldPart::TEXT 				  ; break;
/*N*/ 			case REF_UPDOWN		: nPart = ReferenceFieldPart::UP_DOWN 			  ; break;
/*?*/ 			case REF_PAGE_PGDESC: nPart = ReferenceFieldPart::PAGE_DESC 		  ; break;
/*N*/ 			case REF_ONLYNUMBER	: nPart = ReferenceFieldPart::CATEGORY_AND_NUMBER ; break;
/*N*/ 			case REF_ONLYCAPTION: nPart = ReferenceFieldPart::ONLY_CAPTION 		  ; break;
/*N*/ 			case REF_ONLYSEQNO	: nPart = ReferenceFieldPart::ONLY_SEQUENCE_NUMBER; break;
/*N*/ 			}
/*N*/ 			rAny <<= nPart;
/*N*/ 		}
/*N*/ 		break;
/*N*/ 	case FIELD_PROP_USHORT2:
/*N*/ 		{
/*N*/ 			sal_Int16 nSource = 0;
/*N*/ 			switch(nSubType)
/*N*/ 			{
/*N*/ 			case  REF_SETREFATTR : nSource = ReferenceFieldSource::REFERENCE_MARK; break;
/*N*/ 			case  REF_SEQUENCEFLD: nSource = ReferenceFieldSource::SEQUENCE_FIELD; break;
/*?*/ 			case  REF_BOOKMARK   : nSource = ReferenceFieldSource::BOOKMARK; break;
/*?*/ 			case  REF_OUTLINE    : DBG_ERROR("not implemented"); break;
/*?*/ 			case  REF_FOOTNOTE   : nSource = ReferenceFieldSource::FOOTNOTE; break;
/*?*/ 			case  REF_ENDNOTE    : nSource = ReferenceFieldSource::ENDNOTE; break;
/*N*/ 			}
/*N*/ 			rAny <<= nSource;
/*N*/ 		}
/*N*/ 		break;
/*N*/ 	case FIELD_PROP_PAR1:
/*N*/     {
/*N*/         String  sTmp(GetPar1());
/*N*/         if(REF_SEQUENCEFLD == nSubType)
/*N*/         {
/*N*/             sal_uInt16 nPoolId = SwStyleNameMapper::GetPoolIdFromUIName( sTmp, GET_POOLID_TXTCOLL );
/*N*/             switch( nPoolId )
/*N*/             {
/*N*/                 case RES_POOLCOLL_LABEL_ABB:
/*N*/                 case RES_POOLCOLL_LABEL_TABLE:
/*N*/                 case RES_POOLCOLL_LABEL_FRAME:
/*N*/                 case RES_POOLCOLL_LABEL_DRAWING:
/*?*/                     SwStyleNameMapper::FillProgName(nPoolId, sTmp) ;
/*N*/                 break;
/*N*/             }
/*N*/         }
/*N*/         rAny <<= ::rtl::OUString(sTmp);
/*N*/     }
/*N*/     break;
/*N*/ 	case FIELD_PROP_PAR3:
/*?*/ 		rAny <<= ::rtl::OUString(Expand());
/*?*/ 		break;
/*N*/ 	case FIELD_PROP_SHORT1:
/*N*/ 		rAny <<= (sal_Int16)nSeqNo;
/*N*/ 		break;
/*N*/ 	default:
/*?*/ 		DBG_ERROR("illegal property");
/*N*/ 	}
/*N*/ 	return TRUE;
/*N*/ }
/*-----------------06.03.98 13:34-------------------

--------------------------------------------------*/
/*N*/ BOOL SwGetRefField::PutValue( const uno::Any& rAny, BYTE nMId )
/*N*/ {
/*N*/ 	String sTmp;
/*N*/     nMId &= ~CONVERT_TWIPS;
/*N*/ 	switch( nMId )
/*N*/ 	{
/*N*/ 	case FIELD_PROP_USHORT1:
/*N*/ 		{
/*N*/ 			sal_Int16 nPart;
/*N*/ 			rAny >>= nPart;
/*N*/ 			switch(nPart)
/*N*/ 			{
/*N*/ 			case ReferenceFieldPart::PAGE: 					nPart = REF_PAGE; break;
/*N*/ 			case ReferenceFieldPart::CHAPTER:	 			nPart = REF_CHAPTER; break;
/*N*/ 			case ReferenceFieldPart::TEXT: 					nPart = REF_CONTENT; break;
/*N*/ 			case ReferenceFieldPart::UP_DOWN: 				nPart = REF_UPDOWN; break;
/*?*/ 			case ReferenceFieldPart::PAGE_DESC: 			nPart = REF_PAGE_PGDESC; break;
/*N*/ 			case ReferenceFieldPart::CATEGORY_AND_NUMBER: 	nPart = REF_ONLYNUMBER; break;
/*N*/ 			case ReferenceFieldPart::ONLY_CAPTION: 			nPart = REF_ONLYCAPTION; break;
/*N*/ 			case ReferenceFieldPart::ONLY_SEQUENCE_NUMBER : nPart = REF_ONLYSEQNO; break;
/*?*/ 			default: return FALSE;
/*N*/ 			}
/*N*/ 			SetFormat(nPart);
/*N*/ 		}
/*N*/ 		break;
/*N*/ 	case FIELD_PROP_USHORT2:
/*N*/ 		{
/*N*/ 			sal_Int16 nSource;
/*N*/ 			rAny >>= nSource;
/*N*/ 			switch(nSource)
/*N*/ 			{
/*N*/ 			case ReferenceFieldSource::REFERENCE_MARK : nSubType = REF_SETREFATTR ; break;
/*N*/             case ReferenceFieldSource::SEQUENCE_FIELD :
/*N*/             {
/*N*/                 if(REF_SEQUENCEFLD == nSubType)
/*?*/                     break;
/*N*/                 nSubType = REF_SEQUENCEFLD;
/*N*/                 ConvertProgrammaticToUIName();
/*N*/             }
/*N*/             break;
/*?*/ 			case ReferenceFieldSource::BOOKMARK		  : nSubType = REF_BOOKMARK   ; break;
/*?*/ 			case ReferenceFieldSource::FOOTNOTE		  : nSubType = REF_FOOTNOTE   ; break;
/*?*/ 			case ReferenceFieldSource::ENDNOTE		  : nSubType = REF_ENDNOTE    ; break;
/*N*/ 			}
/*N*/ 		}
/*N*/ 		break;
/*N*/ 	case FIELD_PROP_PAR1:
/*?*/     {
/*?*/         DBG_BF_ASSERT(0, "STRIP"); //STRIP001 OUString sTmp;
//STRIP001 /*?*/         rAny >>= sTmp;
//STRIP001 /*?*/         SetPar1(sTmp);
//STRIP001 /*?*/         ConvertProgrammaticToUIName();
/*?*/     }
/*?*/     break;
/*?*/ 	case FIELD_PROP_PAR3:
/*?*/ 		SetExpand( ::binfilter::GetString( rAny, sTmp ));
/*?*/ 		break;
/*N*/ 	case FIELD_PROP_SHORT1:
/*N*/ 		{
/*N*/ 			sal_Int16 nSetSeq;
/*N*/ 			rAny >>= nSetSeq;
/*N*/ 			if(nSetSeq >= 0)
/*N*/ 				nSeqNo = nSetSeq;
/*N*/ 		}
/*N*/ 		break;
/*N*/ 	default:
/*?*/ 		DBG_ERROR("illegal property");
/*N*/ 	}
/*N*/ 	return TRUE;
/*N*/ }
/* -----------------------------11.01.2002 12:50------------------------------

 ---------------------------------------------------------------------------*/
/*N*/ void SwGetRefField::ConvertProgrammaticToUIName()
/*N*/ {
/*N*/     if(GetTyp() && REF_SEQUENCEFLD == nSubType)
/*N*/     {
/*N*/         SwDoc* pDoc = ((SwGetRefFieldType*)GetTyp())->GetDoc();
/*N*/         const String& rPar1 = GetPar1();
/*N*/         //don't convert when the name points to an existing field type
/*N*/         if(!pDoc->GetFldType(RES_SETEXPFLD, rPar1))
/*N*/         {
/*N*/             sal_uInt16 nPoolId = SwStyleNameMapper::GetPoolIdFromProgName( rPar1, GET_POOLID_TXTCOLL );
/*N*/             USHORT nResId = USHRT_MAX;
/*N*/             switch( nPoolId )
/*N*/             {
/*?*/                 case RES_POOLCOLL_LABEL_ABB:
/*?*/                     nResId = STR_POOLCOLL_LABEL_ABB;
/*?*/                 break;
/*?*/                 case RES_POOLCOLL_LABEL_TABLE:
/*?*/                     nResId = STR_POOLCOLL_LABEL_TABLE;
/*?*/                 break;
/*?*/                 case RES_POOLCOLL_LABEL_FRAME:
/*?*/                     nResId = STR_POOLCOLL_LABEL_FRAME;
/*?*/                 break;
/*?*/                 case RES_POOLCOLL_LABEL_DRAWING:
/*?*/                     nResId = STR_POOLCOLL_LABEL_DRAWING;
/*?*/                 break;
/*N*/             }
/*N*/             if( nResId != USHRT_MAX )
/*?*/             {DBG_BF_ASSERT(0, "STRIP");} //STRIP001     SetPar1(SW_RESSTR( nResId ));
/*N*/         }
/*N*/     }
/*N*/ }
/*-----------------JP: 18.06.93 -------------------
 Get-Referenz-Type
 --------------------------------------------------*/


/*N*/ SwGetRefFieldType::SwGetRefFieldType( SwDoc* pDc )
/*N*/ 	: SwFieldType( RES_GETREFFLD ), pDoc( pDc )
/*N*/ {}


/*N*/ SwFieldType* SwGetRefFieldType::Copy() const
/*N*/ {
DBG_BF_ASSERT(0, "STRIP");return NULL; //STRIP001 //STRIP001 	return new SwGetRefFieldType( pDoc );
/*N*/ }


/*N*/ void SwGetRefFieldType::Modify( SfxPoolItem* pOld, SfxPoolItem* pNew )
/*N*/ {
/*N*/ 	// Update auf alle GetReferenz-Felder
/*N*/ 	if( !pNew && !pOld )
/*N*/ 	{
/*N*/ 		SwClientIter aIter( *this );
/*N*/ 		for( SwFmtFld* pFld = (SwFmtFld*)aIter.First( TYPE(SwFmtFld) );
/*N*/ 						pFld; pFld = (SwFmtFld*)aIter.Next() )
/*N*/ 		{
/*N*/ 			// nur die GetRef-Felder Updaten
/*N*/ 			//JP 3.4.2001: Task 71231 - we need the correct language
/*N*/ 			SwGetRefField* pGRef = (SwGetRefField*)pFld->GetFld();
/*N*/ 			const SwTxtFld* pTFld;
/*N*/ 			if( !pGRef->GetLanguage() &&
/*N*/ 				0 != ( pTFld = pFld->GetTxtFld()) &&
/*N*/ 				pTFld->GetpTxtNode() )
/*N*/ 				pGRef->SetLanguage( pTFld->GetpTxtNode()->GetLang(
/*N*/ 												*pTFld->GetStart() ) );
/*N*/ 
/*N*/ 			pGRef->UpdateField();
/*N*/ 		}
/*N*/ 	}
/*N*/ 	// weiter an die Text-Felder, diese "Expandieren" den Text
/*N*/ 	SwModify::Modify( pOld, pNew );
/*N*/ }

/*N*/ SwTxtNode* SwGetRefFieldType::FindAnchor( SwDoc* pDoc, const String& rRefMark,
/*N*/ 										USHORT nSubType, USHORT nSeqNo,
/*N*/ 										USHORT* pStt, USHORT* pEnd )
/*N*/ {
/*N*/ 	ASSERT( pStt, "warum wird keine StartPos abgefragt?" );
/*N*/ 
/*N*/ 	SwTxtNode* pTxtNd = 0;
/*N*/ 	switch( nSubType )
/*N*/ 	{
/*N*/ 	case REF_SETREFATTR:
/*N*/ 		{
/*N*/ 			const SwFmtRefMark *pRef = pDoc->GetRefMark( rRefMark );
/*N*/ 			if( pRef && pRef->GetTxtRefMark() )
/*N*/ 			{
/*N*/ 				pTxtNd = (SwTxtNode*)&pRef->GetTxtRefMark()->GetTxtNode();
/*N*/ 				*pStt = *pRef->GetTxtRefMark()->GetStart();
/*N*/ 				if( pEnd )
/*N*/ 					*pEnd = *pRef->GetTxtRefMark()->GetAnyEnd();
/*N*/ 			}
/*N*/ 		}
/*N*/ 		break;
/*N*/ 
/*N*/ 	case REF_SEQUENCEFLD:
/*?*/ 		{
/*?*/ 			SwFieldType* pFldType = pDoc->GetFldType( RES_SETEXPFLD, rRefMark );
/*?*/ 			if( pFldType && pFldType->GetDepends() &&
/*?*/ 				GSE_SEQ & ((SwSetExpFieldType*)pFldType)->GetType() )
/*?*/ 			{
/*?*/ 				SwClientIter aIter( *pFldType );
/*?*/ 				for( SwFmtFld* pFld = (SwFmtFld*)aIter.First( TYPE(SwFmtFld) );
/*?*/ 								pFld; pFld = (SwFmtFld*)aIter.Next() )
/*?*/ 				{
/*?*/ 					if( pFld->GetTxtFld() && nSeqNo ==
/*?*/ 						((SwSetExpField*)pFld->GetFld())->GetSeqNumber() )
/*?*/ 					{
/*?*/ 						SwTxtFld* pTxtFld = pFld->GetTxtFld();
/*?*/ 						pTxtNd = (SwTxtNode*)pTxtFld->GetpTxtNode();
/*?*/ 						*pStt = *pTxtFld->GetStart();
/*?*/ 						if( pEnd )
/*?*/ 							*pEnd = (*pStt) + 1;
/*?*/ 						break;
/*?*/ 					}
/*?*/ 				}
/*?*/ 			}
/*?*/ 		}
/*?*/ 		break;
/*?*/ 
/*?*/ 	case REF_BOOKMARK:
/*?*/ 		{
/*?*/ 			USHORT nPos = pDoc->FindBookmark( rRefMark );
/*?*/ 			if( USHRT_MAX != nPos )
/*?*/ 			{
/*?*/ 				const SwBookmark& rBkmk = *pDoc->GetBookmarks()[ nPos ];
/*?*/ 				const SwPosition* pPos = &rBkmk.GetPos();
/*?*/ 				if( rBkmk.GetOtherPos() && *pPos > *rBkmk.GetOtherPos() )
/*?*/ 					pPos = rBkmk.GetOtherPos();
/*?*/ 
/*?*/ 				pTxtNd = pDoc->GetNodes()[ pPos->nNode ]->GetTxtNode();
/*?*/ 				*pStt = pPos->nContent.GetIndex();
/*?*/ 				if( pEnd )
/*?*/ 				{
/*?*/ 					if( !rBkmk.GetOtherPos() )
/*?*/ 						*pEnd = *pStt;
/*?*/ 					else if( rBkmk.GetOtherPos()->nNode == rBkmk.GetPos().nNode )
/*?*/ 					{
/*?*/ 						*pEnd = rBkmk.GetOtherPos() == pPos
/*?*/ 								? rBkmk.GetPos().nContent.GetIndex()
/*?*/ 								: rBkmk.GetOtherPos()->nContent.GetIndex();
/*?*/ 					}
/*?*/ 					else
/*?*/ 						*pEnd = USHRT_MAX;
/*?*/ 				}
/*?*/ 			}
/*?*/ 		}
/*?*/ 		break;
/*?*/ 
/*?*/ 	case REF_OUTLINE:
/*?*/ 		break;
/*?*/ 
/*?*/ 	case REF_FOOTNOTE:
/*?*/ 	case REF_ENDNOTE:
/*?*/ 		{
/*?*/ 			USHORT n, nFtnCnt = pDoc->GetFtnIdxs().Count();
/*?*/ 			SwTxtFtn* pFtnIdx;
/*?*/ 			for( n = 0; n < nFtnCnt; ++n )
/*?*/ 				if( nSeqNo == (pFtnIdx = pDoc->GetFtnIdxs()[ n ])->GetSeqRefNo() )
/*?*/ 				{
/*?*/ 					SwNodeIndex* pIdx = pFtnIdx->GetStartNode();
/*?*/ 					if( pIdx )
/*?*/ 					{
/*?*/ 						SwNodeIndex aIdx( *pIdx, 1 );
/*?*/ 						if( 0 == ( pTxtNd = aIdx.GetNode().GetTxtNode()))
/*?*/ 							pTxtNd = (SwTxtNode*)pDoc->GetNodes().GoNext( &aIdx );
/*?*/ 					}
/*?*/ 					*pStt = 0;
/*?*/ 					if( pEnd )
/*?*/ 						*pEnd = 0;
/*?*/ 					break;
/*?*/ 				}
/*?*/ 		}
/*?*/ 		break;
/*N*/ 	}
/*N*/ 
/*N*/ 	return pTxtNd;
/*N*/ }


//STRIP001 struct _RefIdsMap
//STRIP001 {
//STRIP001 	String aName;
//STRIP001 	SvUShortsSort aIds, aDstIds, aIdsMap;
//STRIP001 	SvUShorts aMap;
//STRIP001 	BOOL bInit;
//STRIP001 
//STRIP001 	_RefIdsMap( const String& rName )
//STRIP001 		: aName( rName ), aIds( 16, 16 ), aIdsMap( 16, 16 ), aMap( 16, 16 ),
//STRIP001 		bInit( FALSE )
//STRIP001 	{}
//STRIP001 
//STRIP001 	void Check( SwDoc& rDoc, SwDoc& rDestDoc, SwGetRefField& rFld,
//STRIP001 					BOOL bField = TRUE );
//STRIP001 
//STRIP001 	BOOL IsInit() const { return bInit; }
//STRIP001 };

//STRIP001 SV_DECL_PTRARR_DEL( _RefIdsMaps, _RefIdsMap*, 5, 5 )
//STRIP001 SV_IMPL_PTRARR( _RefIdsMaps, _RefIdsMap* )

//STRIP001 void _RefIdsMap::Check( SwDoc& rDoc, SwDoc& rDestDoc, SwGetRefField& rFld,
//STRIP001 						BOOL bField )
//STRIP001 {
//STRIP001 
//STRIP001 	if( !bInit )
//STRIP001 	{
//STRIP001 		if( bField )
//STRIP001 		{
//STRIP001 			const SwTxtNode* pNd;
//STRIP001 			SwModify* pMod;
//STRIP001 			if( 0 != ( pMod = rDestDoc.GetFldType( RES_SETEXPFLD, aName ) ))
//STRIP001 			{
//STRIP001 				SwClientIter aIter( *pMod );
//STRIP001 				for( SwFmtFld* pF = (SwFmtFld*)aIter.First( TYPE( SwFmtFld )); pF;
//STRIP001 					pF = (SwFmtFld*)aIter.Next() )
//STRIP001 					if( pF->GetTxtFld() &&
//STRIP001 						0 != ( pNd = pF->GetTxtFld()->GetpTxtNode() ) &&
//STRIP001 						pNd->GetNodes().IsDocNodes() )
//STRIP001 						aIds.Insert( ((SwSetExpField*)pF->GetFld())->GetSeqNumber() );
//STRIP001 			}
//STRIP001 			if( 0 != ( pMod = rDoc.GetFldType( RES_SETEXPFLD, aName ) ))
//STRIP001 			{
//STRIP001 				SwClientIter aIter( *pMod );
//STRIP001 				for( SwFmtFld* pF = (SwFmtFld*)aIter.First( TYPE( SwFmtFld )); pF;
//STRIP001 						pF = (SwFmtFld*)aIter.Next() )
//STRIP001 					if( pF->GetTxtFld() &&
//STRIP001 						0 != ( pNd = pF->GetTxtFld()->GetpTxtNode() ) &&
//STRIP001 						pNd->GetNodes().IsDocNodes() )
//STRIP001 						aDstIds.Insert( ((SwSetExpField*)pF->GetFld())->GetSeqNumber() );
//STRIP001 			}
//STRIP001 		}
//STRIP001 		else
//STRIP001 		{
//STRIP001 			for( USHORT n = rDestDoc.GetFtnIdxs().Count(); n; )
//STRIP001 				aIds.Insert( rDestDoc.GetFtnIdxs()[ --n ]->GetSeqRefNo() );
//STRIP001 			for( n = rDoc.GetFtnIdxs().Count(); n; )
//STRIP001 				aDstIds.Insert( rDoc.GetFtnIdxs()[ --n ]->GetSeqRefNo() );
//STRIP001 		}
//STRIP001 		bInit = TRUE;
//STRIP001 	}
//STRIP001 
//STRIP001 	// dann teste mal, ob die Nummer schon vergeben ist
//STRIP001 	// oder ob eine neue bestimmt werden muss.
//STRIP001 	USHORT nPos, nSeqNo = rFld.GetSeqNo();
//STRIP001 	if( aIds.Seek_Entry( nSeqNo ) && aDstIds.Seek_Entry( nSeqNo ))
//STRIP001 	{
//STRIP001 		// ist schon vergeben, also muss eine neue
//STRIP001 		// erzeugt werden.
//STRIP001 		if( aIdsMap.Seek_Entry( nSeqNo, &nPos ))
//STRIP001 			rFld.SetSeqNo( aMap[ nPos ] );
//STRIP001 		else
//STRIP001 		{
//STRIP001 			for( USHORT n = 0; n < aIds.Count(); ++n )
//STRIP001 				if( n != aIds[ n ] )
//STRIP001 					break;
//STRIP001 
//STRIP001 			// die neue SeqNo eintragen, damit die "belegt" ist
//STRIP001 			aIds.Insert( n );
//STRIP001 			aIdsMap.Insert( nSeqNo, nPos );
//STRIP001 			aMap.Insert( n, nPos );
//STRIP001 			rFld.SetSeqNo( n );
//STRIP001 
//STRIP001 			// und noch die Felder oder Fuss-/EndNote auf die neue
//STRIP001 			// Id umsetzen
//STRIP001 			if( bField )
//STRIP001 			{
//STRIP001 				SwModify* pMod = rDoc.GetFldType( RES_SETEXPFLD, aName );
//STRIP001 				if( pMod )
//STRIP001 				{
//STRIP001 					SwClientIter aIter( *pMod );
//STRIP001 					for( SwFmtFld* pF = (SwFmtFld*)aIter.First( TYPE( SwFmtFld )); pF;
//STRIP001 							pF = (SwFmtFld*)aIter.Next() )
//STRIP001 						if( pF->GetTxtFld() && nSeqNo ==
//STRIP001 							((SwSetExpField*)pF->GetFld())->GetSeqNumber() )
//STRIP001 							((SwSetExpField*)pF->GetFld())->SetSeqNumber( n );
//STRIP001 				}
//STRIP001 			}
//STRIP001 			else
//STRIP001 			{
//STRIP001 				SwTxtFtn* pFtnIdx;
//STRIP001 				for( USHORT i = 0, nCnt = rDoc.GetFtnIdxs().Count(); i < nCnt; ++i )
//STRIP001 					if( nSeqNo == (pFtnIdx = rDoc.GetFtnIdxs()[ i ])->GetSeqRefNo() )
//STRIP001 					{
//STRIP001 						pFtnIdx->SetSeqNo( n );
//STRIP001 						break;
//STRIP001 					}
//STRIP001 			}
//STRIP001 		}
//STRIP001 	}
//STRIP001 	else
//STRIP001 	{
//STRIP001 		aIds.Insert( nSeqNo );
//STRIP001 		aIdsMap.Insert( nSeqNo, nPos );
//STRIP001 		aMap.Insert( nSeqNo, nPos );
//STRIP001 	}
//STRIP001 }


/*N*/ void SwGetRefFieldType::MergeWithOtherDoc( SwDoc& rDestDoc )
/*N*/ {
/*N*/ 	if( &rDestDoc != pDoc &&
/*N*/ 		rDestDoc.GetSysFldType( RES_GETREFFLD )->GetDepends() )
/*N*/ 	{
/*?*/ 		// dann gibt es im DestDoc RefFelder, also muessen im SourceDoc
/*?*/ 		// alle RefFelder auf einduetige Ids in beiden Docs umgestellt
/*?*/ 		// werden.
/*?*/ 		DBG_BF_ASSERT(0, "STRIP"); //STRIP001 _RefIdsMap aFntMap( aEmptyStr );
//STRIP001 /*?*/ 		_RefIdsMaps aFldMap;
//STRIP001 /*?*/ 
//STRIP001 /*?*/ 		SwClientIter aIter( *this );
//STRIP001 /*?*/ 		for( SwClient* pFld = aIter.First( TYPE( SwFmtFld ));
//STRIP001 /*?*/ 				pFld; pFld = aIter.Next() )
//STRIP001 /*?*/ 		{
//STRIP001 /*?*/ 			SwGetRefField& rRefFld = *(SwGetRefField*)((SwFmtFld*)pFld)->GetFld();
//STRIP001 /*?*/ 			switch( rRefFld.GetSubType() )
//STRIP001 /*?*/ 			{
//STRIP001 /*?*/ 			case REF_SEQUENCEFLD:
//STRIP001 /*?*/ 				{
//STRIP001 /*?*/ 					_RefIdsMap* pMap = 0;
//STRIP001 /*?*/ 					for( USHORT n = aFldMap.Count(); n; )
//STRIP001 /*?*/ 						if( aFldMap[ --n ]->aName == rRefFld.GetSetRefName() )
//STRIP001 /*?*/ 						{
//STRIP001 /*?*/ 							pMap = aFldMap[ n ];
//STRIP001 /*?*/ 							break;
//STRIP001 /*?*/ 						}
//STRIP001 /*?*/ 					if( !pMap )
//STRIP001 /*?*/ 					{
//STRIP001 /*?*/ 						pMap = new _RefIdsMap( rRefFld.GetSetRefName() );
//STRIP001 /*?*/ 						aFldMap.C40_INSERT( _RefIdsMap, pMap, aFldMap.Count() );
//STRIP001 /*?*/ 					}
//STRIP001 /*?*/ 
//STRIP001 /*?*/ 					pMap->Check( *pDoc, rDestDoc, rRefFld, TRUE );
//STRIP001 /*?*/ 				}
//STRIP001 /*?*/ 				break;
//STRIP001 /*?*/ 
//STRIP001 /*?*/ 			case REF_FOOTNOTE:
//STRIP001 /*?*/ 			case REF_ENDNOTE:
//STRIP001 /*?*/ 				aFntMap.Check( *pDoc, rDestDoc, rRefFld, FALSE );
//STRIP001 /*?*/ 				break;
//STRIP001 /*?*/ 			}
//STRIP001 /*?*/ 		}
/*N*/ 	}
/*N*/ }

}
