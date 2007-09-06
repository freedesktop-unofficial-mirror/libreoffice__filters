/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: sw_redlnitr.cxx,v $
 *
 *  $Revision: 1.6 $
 *
 *  last change: $Author: kz $ $Date: 2007-09-06 12:37:14 $
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


#ifndef _COM_SUN_STAR_I18N_SCRIPTTYPE_HDL_
#include <com/sun/star/i18n/ScriptType.hdl>
#endif


#ifndef _ERRHDL_HXX
#include <errhdl.hxx>
#endif

#ifndef _ITRATR_HXX
#include <itratr.hxx>		// SwAttrIter
#endif
#ifndef _NDTXT_HXX
#include <ndtxt.hxx>		// SwTxtNode
#endif

#ifndef _HORIORNT_HXX
#include <horiornt.hxx>
#endif

#ifndef _DOC_HXX
#include <doc.hxx>			// SwDoc
#endif
#ifndef _FRMSH_HXX
#include <frmsh.hxx>
#endif
#ifndef _BREAKIT_HXX
#include <breakit.hxx>
#endif

//////////////////////////



#ifndef _TXTFRM_HXX
#include <txtfrm.hxx>		// SwTxtFrm
#endif
#ifndef _REDLNITR_HXX
#include <redlnitr.hxx>
#endif
#ifndef _EXTINPUT_HXX
#include <extinput.hxx>
#endif

namespace binfilter {

using namespace ::com::sun::star;

extern BYTE WhichFont( xub_StrLen nIdx, const String* pTxt,
                       const SwScriptInfo* pSI );

/*************************************************************************
 *						SwAttrIter::CtorInit()
 *************************************************************************/
/*N*/ void SwAttrIter::CtorInit( SwTxtNode& rTxtNode, SwScriptInfo& rScrInf, SwTxtFrm* pFrm )
/*N*/ {
/*N*/ 	// Beim HTML-Import kann es vorkommen, dass kein Layout existiert.
/*N*/ 	SwRootFrm *pRootFrm = rTxtNode.GetDoc()->GetRootFrm();
/*N*/ 	pShell = pRootFrm ? pRootFrm->GetShell() : 0;
/*N*/ 
/*N*/     pScriptInfo = &rScrInf;
/*N*/ 	pAttrSet = &rTxtNode.GetSwAttrSet();
/*N*/     pHints = rTxtNode.GetpSwpHints();
/*N*/ 
/*N*/     SwFontAccess aFontAccess( &rTxtNode.GetAnyFmtColl(), pShell );
/*N*/ 
/*N*/     delete pFnt;
/*N*/     pFnt = new SwFont( *aFontAccess.Get()->GetFont() );
/*N*/ 
/*N*/     // set font to vertical if frame layout is vertical
/*N*/     sal_Bool bVertLayout = sal_False;
/*N*/     sal_Bool bRTL = sal_False;
/*N*/     if ( pFrm )
/*N*/     {
/*N*/         if ( pFrm->IsVertical() )
/*N*/         {
/*N*/             bVertLayout = sal_True;
/*N*/             pFnt->SetVertical( pFnt->GetOrientation(), sal_True );
/*N*/         }
/*N*/         bRTL = pFrm->IsRightToLeft();
/*N*/     }
/*N*/ 
/*N*/     // Initialize the default attribute of the attribute handler
/*N*/     // based on the attribute array cached together with the font.
/*N*/     // If any further attributes for the paragraph are given in pAttrSet
/*N*/     // consider them during construction of the default array, and apply
/*N*/     // them to the font
/*N*/     aAttrHandler.Init( aFontAccess.Get()->GetDefault(),
/*N*/                        rTxtNode.HasSwAttrSet() ? pAttrSet : 0,
/*N*/                        *rTxtNode.GetDoc(), pShell, *pFnt, bVertLayout );
/*N*/ 
/*N*/ 	aMagicNo[SW_LATIN] = aMagicNo[SW_CJK] = aMagicNo[SW_CTL] = NULL;
/*N*/ 
/*N*/ 	// determine script changes if not already done for current paragraph
/*N*/ 	ASSERT( pScriptInfo, "No script info available");
/*N*/     if ( pScriptInfo->GetInvalidity() != STRING_LEN )
/*N*/          pScriptInfo->InitScriptInfo( rTxtNode, bRTL );
/*N*/ 
/*N*/ 	if ( pBreakIt->xBreak.is() )
/*N*/ 	{
/*N*/         pFnt->SetActual( WhichFont( 0, 0, pScriptInfo ) );
/*N*/ 
/*N*/         xub_StrLen nChg = 0;
/*N*/ 		USHORT nCnt = 0;
/*N*/ 
/*N*/         do
/*N*/ 		{
/*N*/ 			nChg = pScriptInfo->GetScriptChg( nCnt );
/*N*/             USHORT nScript = pScriptInfo->GetScriptType( nCnt++ );
/*N*/ 			BYTE nTmp = 4;
/*N*/ 			switch ( nScript ) {
/*N*/ 				case i18n::ScriptType::ASIAN :
/*N*/ 					if( !aMagicNo[SW_CJK] ) nTmp = SW_CJK; break;
/*N*/ 				case i18n::ScriptType::COMPLEX :
/*N*/ 					if( !aMagicNo[SW_CTL] ) nTmp = SW_CTL; break;
/*N*/ 				default:
/*N*/ 					if( !aMagicNo[SW_LATIN ] ) nTmp = SW_LATIN;
/*N*/ 			}
/*N*/ 			if( nTmp < 4 )
/*N*/ 			{
/*N*/ 				pFnt->ChkMagic( pShell, nTmp );
/*N*/ 				pFnt->GetMagic( aMagicNo[ nTmp ], aFntIdx[ nTmp ], nTmp );
/*N*/ 			}
/*N*/ 		} while( nChg < rTxtNode.GetTxt().Len() );
/*N*/ 	}
/*N*/ 	else
/*N*/ 	{
/*N*/ 		pFnt->ChkMagic( pShell, SW_LATIN );
/*N*/ 		pFnt->GetMagic( aMagicNo[ SW_LATIN ], aFntIdx[ SW_LATIN ], SW_LATIN );
/*N*/ 	}
/*N*/ 
/*N*/     nStartIndex = nEndIndex = nPos = nChgCnt = 0;
/*N*/ 	nPropFont = 0;
/*N*/ 	SwDoc* pDoc = rTxtNode.GetDoc();
/*N*/ 
/*N*/ 	const SwExtTextInput* pExtInp = pDoc->GetExtTextInput( rTxtNode );
/*N*/ 	sal_Bool bShow = ::binfilter::IsShowChanges( pDoc->GetRedlineMode() );
/*N*/     if( pExtInp || bShow )
/*N*/ 	{
/*N*/ 		MSHORT nRedlPos = pDoc->GetRedlinePos( rTxtNode );
/*N*/ 		if( pExtInp || MSHRT_MAX != nRedlPos )
/*N*/ 		{
/*N*/ 			const SvUShorts* pArr = 0;
/*N*/ 			xub_StrLen nInputStt = 0;
/*N*/ 			if( pExtInp )
/*N*/ 			{
/*N*/ 				pArr = &pExtInp->GetAttrs();
/*N*/ 				nInputStt = pExtInp->Start()->nContent.GetIndex();
/*N*/                 Seek( 0 );
/*N*/ 			}
/*N*/ 
/*N*/             pRedln = new SwRedlineItr( rTxtNode, *pFnt, aAttrHandler, nRedlPos,
/*N*/                                         bShow, pArr, nInputStt );
/*N*/ 
/*N*/ 			if( pRedln->IsOn() )
/*N*/ 				++nChgCnt;
/*N*/ 		}
/*N*/ 	}
/*N*/ }

/*************************************************************************
 * SwRedlineItr - Der Redline-Iterator
 *
 * Folgende Informationen/Zustaende gibt es im RedlineIterator:
 *
 * nFirst ist der erste Index der RedlineTbl, der mit dem Absatz ueberlappt.
 *
 * nAct ist der zur Zeit aktive ( wenn bOn gesetzt ist ) oder der naechste
 * in Frage kommende Index.
 * nStart und nEnd geben die Grenzen des Objekts innerhalb des Absatzes an.
 *
 * Wenn bOn gesetzt ist, ist der Font entsprechend manipuliert worden.
 *
 * Wenn nAct auf MSHRT_MAX gesetzt wurde ( durch Reset() ), so ist zur Zeit
 * kein Redline aktiv, nStart und nEnd sind invalid.
 *************************************************************************/



// Der Return-Wert von SwRedlineItr::Seek gibt an, ob der aktuelle Font
// veraendert wurde durch Verlassen (-1) oder Betreten eines Bereichs (+1)











}
