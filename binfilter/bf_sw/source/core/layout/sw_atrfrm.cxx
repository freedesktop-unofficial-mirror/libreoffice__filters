/*************************************************************************
 *
 *  $RCSfile: sw_atrfrm.cxx,v $
 *
 *  $Revision: 1.2 $
 *
 *  last change: $Author: mwu $ $Date: 2003-11-06 07:50:22 $
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

#ifndef _HINTIDS_HXX
#include <hintids.hxx>
#endif

#ifndef _COM_SUN_STAR_TEXT_RELORIENTATION_HPP_
#include <com/sun/star/text/RelOrientation.hpp>
#endif
#ifndef _COM_SUN_STAR_TEXT_VERTORIENTATION_HPP_
#include <com/sun/star/text/VertOrientation.hpp>
#endif
#ifndef _COM_SUN_STAR_TEXT_HORIZONTALADJUST_HPP_
#include <com/sun/star/text/HorizontalAdjust.hpp>
#endif
#ifndef _COM_SUN_STAR_TEXT_DOCUMENTSTATISTIC_HPP_
#include <com/sun/star/text/DocumentStatistic.hpp>
#endif
#ifndef _COM_SUN_STAR_TEXT_HORIORIENTATION_HPP_
#include <com/sun/star/text/HoriOrientation.hpp>
#endif
#ifndef _COM_SUN_STAR_TEXT_HORIORIENTATIONFORMAT_HPP_
#include <com/sun/star/text/HoriOrientationFormat.hpp>
#endif
#ifndef _COM_SUN_STAR_TEXT_NOTEPRINTMODE_HPP_
#include <com/sun/star/text/NotePrintMode.hpp>
#endif
#ifndef _COM_SUN_STAR_TEXT_SIZETYPE_HPP_
#include <com/sun/star/text/SizeType.hpp>
#endif
#ifndef _COM_SUN_STAR_TEXT_VERTORIENTATIONFORMAT_HPP_
#include <com/sun/star/text/VertOrientationFormat.hpp>
#endif
#ifndef _COM_SUN_STAR_TEXT_WRAPTEXTMODE_HPP_
#include <com/sun/star/text/WrapTextMode.hpp>
#endif
#ifndef _COM_SUN_STAR_TEXT_XTEXTFRAME_HPP_
#include <com/sun/star/text/XTextFrame.hpp>
#endif
#ifndef _COM_SUN_STAR_TEXT_TEXTCONTENTANCHORTYPE_HPP_
#include <com/sun/star/text/TextContentAnchorType.hpp>
#endif
#ifndef _COM_SUN_STAR_TEXT_INVALIDTEXTCONTENTEXCEPTION_HPP_
#include <com/sun/star/text/InvalidTextContentException.hpp>
#endif
#ifndef _COM_SUN_STAR_TEXT_XTEXTCONTENT_HPP_
#include <com/sun/star/text/XTextContent.hpp>
#endif
#ifndef _COM_SUN_STAR_CONTAINER_XINDEXCONTAINER_HPP_
#include <com/sun/star/container/XIndexContainer.hpp>
#endif
#ifndef _COM_SUN_STAR_TEXT_TEXTGRIDMODE_HPP_
#include <com/sun/star/text/TextGridMode.hpp>
#endif
#ifndef _COM_SUN_STAR_AWT_SIZE_HPP_
#include <com/sun/star/awt/Size.hpp>
#endif
#ifndef _SVTOOLS_UNOIMAP_HXX
#include <svtools/unoimap.hxx>
#endif
#ifndef _SVTOOLS_UNOEVENT_HXX_
#include <svtools/unoevent.hxx>
#endif
#ifndef __SBX_SBXVARIABLE_HXX //autogen
#include <svtools/sbxvar.hxx>
#endif
#ifndef _IMAP_HXX //autogen
#include <svtools/imap.hxx>
#endif
#ifndef _GOODIES_IMAPOBJ_HXX //autogen
#include <svtools/imapobj.hxx>
#endif
#ifndef _SVX_ULSPITEM_HXX //autogen
#include <bf_svx/ulspitem.hxx>
#endif
#ifndef _SVX_LRSPITEM_HXX //autogen
#include <bf_svx/lrspitem.hxx>
#endif
#ifndef _SVDMODEL_HXX //autogen
#include <bf_svx/svdmodel.hxx>
#endif
#ifndef _SVDPAGE_HXX //autogen
#include <bf_svx/svdpage.hxx>
#endif

#ifndef _UNOSETT_HXX
#include <unosett.hxx>
#endif
#ifndef _UNOSTYLE_HXX
#include <unostyle.hxx>
#endif
#ifndef _FMTCLDS_HXX //autogen
#include <fmtclds.hxx>
#endif
#ifndef _FMTORNT_HXX //autogen
#include <fmtornt.hxx>
#endif
#ifndef _FMTHDFT_HXX //autogen
#include <fmthdft.hxx>
#endif
#ifndef _FMTPDSC_HXX //autogen
#include <fmtpdsc.hxx>
#endif
#ifndef _FMTCNTNT_HXX //autogen
#include <fmtcntnt.hxx>
#endif
#ifndef _FMTFSIZE_HXX //autogen
#include <fmtfsize.hxx>
#endif
#ifndef _FMTFORDR_HXX //autogen
#include <fmtfordr.hxx>
#endif
#ifndef _FMTSRND_HXX //autogen
#include <fmtsrnd.hxx>
#endif
#ifndef _FMTANCHR_HXX //autogen
#include <fmtanchr.hxx>
#endif
#ifndef _FMTTSPLT_HXX //autogen
#include <fmtlsplt.hxx>
#endif
#ifndef _FMTFTNTX_HXX //autogen
#include <fmtftntx.hxx>
#endif
#ifndef _FMTEIRO_HXX //autogen
#include <fmteiro.hxx>
#endif
#ifndef _FMTURL_HXX //autogen
#include <fmturl.hxx>
#endif
#ifndef _FMTCNCT_HXX //autogen
#include <fmtcnct.hxx>
#endif
#ifndef _NODE_HXX //autogen
#include <node.hxx>
#endif
#ifndef _SECTION_HXX //autogen
#include <section.hxx>
#endif
#ifndef _FMTLINE_HXX
#include <fmtline.hxx>
#endif
#ifndef SW_TGRDITEM_HXX
#include <tgrditem.hxx>
#endif
#ifndef _SW_HF_EAT_SPACINGITEM_HXX
#include <hfspacingitem.hxx>
#endif
#ifndef _SWTYPES_HXX
#include <swtypes.hxx>
#endif
#ifndef _DOC_HXX
#include <doc.hxx>
#endif
#ifndef _PAGEFRM_HXX
#include <pagefrm.hxx>
#endif
#ifndef _ROOTFRM_HXX
#include <rootfrm.hxx>
#endif
#ifndef _CNTFRM_HXX
#include <cntfrm.hxx>
#endif
#ifndef _CRSRSH_HXX
#include <crsrsh.hxx>
#endif
#ifndef _ERRHDL_HXX
#include <errhdl.hxx>
#endif
#ifndef _CALBCK_HXX
#include <calbck.hxx>
#endif
#ifndef _PAM_HXX
#include <pam.hxx>
#endif
#ifndef _DFLYOBJ_HXX
#include <dflyobj.hxx>
#endif
#ifndef _DCONTACT_HXX
#include <dcontact.hxx>
#endif
#ifndef _FLYFRM_HXX
#include <flyfrm.hxx>
#endif
#ifndef _FRMTOOL_HXX
#include <frmtool.hxx>
#endif
#ifndef _HINTS_HXX
#include <hints.hxx>
#endif
#ifndef _FLYFRMS_HXX
#include <flyfrms.hxx>
#endif
#ifndef _PAGEDESC_HXX
#include <pagedesc.hxx>
#endif
#ifndef _GRFATR_HXX
#include <grfatr.hxx>
#endif
#ifndef _NDNOTXT_HXX
#include <ndnotxt.hxx>
#endif
#ifndef _DOCARY_HXX
#include <docary.hxx>
#endif
#ifndef _NODE2LAY_HXX
#include <node2lay.hxx>
#endif
#ifndef _FMTCLBL_HXX
#include <fmtclbl.hxx>
#endif
#ifndef _SWUNOHELPER_HXX
#include <swunohelper.hxx>
#endif
#ifndef _UNOCOLL_HXX
#include <unocoll.hxx>
#endif
#ifndef _UNOFRAME_HXX
#include <unoframe.hxx>
#endif
#ifndef _SWSTYLENAMEMAPPER_HXX
#include <SwStyleNameMapper.hxx>
#endif
/// OD 22.08.2002 #99657#
///     include definition of class SvxBrushItem and GraphicObject
///     in order to determine, if background is transparent.
#ifndef _SVX_BRSHITEM_HXX
#include <bf_svx/brshitem.hxx>
#endif
#ifndef _GRFMGR_HXX
#include <goodies/grfmgr.hxx>
#endif

#ifndef _CMDID_H
#include <cmdid.h>
#endif
#ifndef _UNOMID_H
#include <unomid.h>
#endif
#ifndef _UNOOBJ_HXX
#include <unoobj.hxx>
#endif
namespace binfilter {

using namespace ::com::sun::star;
using namespace ::com::sun::star::text;
using namespace ::com::sun::star::uno;
using namespace ::com::sun::star::container;
using namespace ::rtl;

/*N*/ SV_IMPL_PTRARR(SwColumns,SwColumn*)

/*N*/ TYPEINIT1(SwFrmFmt, 	SwFmt );  //rtti fuer SwFrmFmt
/*N*/ TYPEINIT1(SwFlyFrmFmt,  SwFrmFmt);
/*N*/ TYPEINIT1(SwDrawFrmFmt, SwFrmFmt);
/*N*/ TYPEINIT1(SwFmtVertOrient, SfxPoolItem);
/*N*/ TYPEINIT1(SwFmtHoriOrient, SfxPoolItem);
/*N*/ TYPEINIT2(SwFmtHeader,  SfxPoolItem, SwClient );
/*N*/ TYPEINIT2(SwFmtFooter,  SfxPoolItem, SwClient );
/*N*/ TYPEINIT2(SwFmtPageDesc,  SfxPoolItem, SwClient );
/*N*/ TYPEINIT1_AUTOFACTORY(SwFmtLineNumber, SfxPoolItem);

/* -----------------19.05.98 09:26-------------------
 * 	Umwandlung fuer QueryValue
 * --------------------------------------------------*/
/*N*/ sal_Int16 lcl_RelToINT(SwRelationOrient eRelation)
/*N*/ {
/*N*/ 	sal_Int16 nRet = text::RelOrientation::FRAME;
/*N*/ 	switch(eRelation)
/*N*/ 	{
/*N*/ 	case  PRTAREA:			nRet = text::RelOrientation::PRINT_AREA; break;
/*?*/ 	case  REL_CHAR:			nRet = text::RelOrientation::CHAR; break;
/*?*/ 	case  REL_PG_LEFT:		nRet = text::RelOrientation::PAGE_LEFT; break;
/*N*/ 	case  REL_PG_RIGHT:		nRet = text::RelOrientation::PAGE_RIGHT; break;
/*?*/ 	case  REL_FRM_LEFT:		nRet = text::RelOrientation::FRAME_LEFT; break;
/*?*/ 	case  REL_FRM_RIGHT:	nRet = text::RelOrientation::FRAME_RIGHT; break;
/*N*/ 	case  REL_PG_FRAME:		nRet = text::RelOrientation::PAGE_FRAME; break;
/*N*/ 	case  REL_PG_PRTAREA:	nRet = text::RelOrientation::PAGE_PRINT_AREA; break;
/*N*/ 	}
/*N*/ 	return nRet;
/*N*/ }
/*N*/ SwRelationOrient	lcl_IntToRelation(const uno::Any& rVal)
/*N*/ {
/*N*/ 	SwRelationOrient eRet = FRAME;
/*N*/     sal_Int16 nVal;
/*N*/     rVal >>= nVal;
/*N*/     switch(nVal)
/*N*/ 	{
/*N*/ 		case  text::RelOrientation::PRINT_AREA: 	eRet =   PRTAREA           ; break;
/*?*/ 		case  text::RelOrientation::CHAR:    	eRet =   REL_CHAR          ; break;
/*?*/ 		case  text::RelOrientation::PAGE_LEFT:    eRet =   REL_PG_LEFT       ; break;
/*?*/ 		case  text::RelOrientation::PAGE_RIGHT:    eRet =   REL_PG_RIGHT      ; break;
/*?*/ 		case  text::RelOrientation::FRAME_LEFT:    eRet =   REL_FRM_LEFT      ; break;
/*?*/ 		case  text::RelOrientation::FRAME_RIGHT:    eRet =   REL_FRM_RIGHT     ; break;
/*N*/ 		case  text::RelOrientation::PAGE_FRAME:    eRet =   REL_PG_FRAME      ; break;
/*N*/ 		case  text::RelOrientation::PAGE_PRINT_AREA:    eRet =   REL_PG_PRTAREA    ; break;
/*N*/ 	}
/*N*/ 	return eRet;
/*N*/ }

/*N*/ void DelHFFormat( SwClient *pToRemove, SwFrmFmt *pFmt )
/*N*/ {
/*N*/ 	//Wenn der Client der letzte ist der das Format benutzt, so muss dieses
/*N*/ 	//vernichtet werden. Zuvor muss jedoch ggf. die Inhaltssection vernichtet
/*N*/ 	//werden.
/*N*/ 	SwDoc* pDoc = pFmt->GetDoc();
/*N*/ 	pFmt->Remove( pToRemove );
/*N*/ 	if( pDoc->IsInDtor() )
/*N*/ 	{
/*N*/ 		delete pFmt;
/*N*/ 		return;
/*N*/ 	}
/*N*/ 
/*N*/ 	//Nur noch Frms angemeldet?
/*N*/ 	sal_Bool bDel = sal_True;
/*N*/ 	{
/*N*/ 		// Klammer, weil im DTOR SwClientIter das Flag bTreeChg zurueck
/*N*/ 		// gesetzt wird. Unguenstig, wenn das Format vorher zerstoert wird.
/*N*/ 		SwClientIter aIter( *pFmt );
/*N*/ 		SwClient *pLast = aIter.GoStart();
/*N*/ 		if( pLast )
/*N*/ 			do {
/*M*/ 				bDel = pLast->IsA( TYPE(SwFrm) )|| pLast->IsA(TYPE(SwXHeadFootText));
/*N*/ 			} while( bDel && 0 != ( pLast = aIter++ ));
/*N*/ 	}
/*N*/ 
/*N*/ 	if ( bDel )
/*N*/ 	{
/*?*/ 		//Wenn in einem der Nodes noch ein Crsr angemeldet ist, muss das
/*?*/ 		//ParkCrsr einer (beliebigen) Shell gerufen werden.
/*?*/ 		SwFmtCntnt& rCnt = (SwFmtCntnt&)pFmt->GetCntnt();
/*?*/ 		if ( rCnt.GetCntntIdx() )
/*?*/ 		{
/*?*/ 			SwNode *pNode = 0;
/*?*/ 			{
/*?*/ 				SwNodeIndex aIdx( *rCnt.GetCntntIdx(), 1 );
/*?*/ 				//Wenn in einem der Nodes noch ein Crsr angemeldet ist, muss das
/*?*/ 				//ParkCrsr einer (beliebigen) Shell gerufen werden.
/*?*/ 				pNode = pDoc->GetNodes()[ aIdx ];
/*?*/ 				sal_uInt32 nEnd = pNode->EndOfSectionIndex();
/*?*/ 				while ( aIdx < nEnd )
/*?*/ 				{
/*?*/ 					if ( pNode->IsCntntNode() &&
/*?*/ 						 ((SwCntntNode*)pNode)->GetDepends() )
/*?*/ 					{
/*?*/ 						SwClientIter aIter( *(SwCntntNode*)pNode );
/*?*/ 						do
/*?*/ 						{
/*?*/ 							if( aIter()->ISA( SwCrsrShell ) )
/*?*/ 							{
/*?*/ 								DBG_ASSERT(0, "STRIP"); //STRIP001 ((SwCrsrShell*)aIter())->ParkCrsr( aIdx );
//STRIP001 /*?*/ 								aIdx = nEnd-1;
//STRIP001 /*?*/ 								break;
/*?*/ 							}
/*?*/ 						} while ( aIter++ );
/*?*/ 					}
/*?*/ 					aIdx++;
/*?*/ 					pNode = pDoc->GetNodes()[ aIdx ];
/*?*/ 				}
/*?*/ 			}
/*?*/ 			rCnt.SetNewCntntIdx( (const SwNodeIndex*)0 );
/*?*/ 
/*?*/ 			// beim Loeschen von Header/Footer-Formaten IMMER das Undo
/*?*/ 			// abschalten! (Bug 31069)
/*?*/ 			sal_Bool bDoesUndo = pDoc->DoesUndo();
/*?*/ 			pDoc->DoUndo( sal_False );
/*?*/ 
/*?*/ 			ASSERT( pNode, "Ein grosses Problem." );
/*?*/ 			pDoc->DeleteSection( pNode );
/*?*/ 
/*?*/ 			if( bDoesUndo )
/*?*/ 			{
/*?*/ 				pDoc->DelAllUndoObj();
/*?*/ 				pDoc->DoUndo( sal_True );
/*?*/ 			}
/*?*/ 		}
/*?*/ 		delete pFmt;
/*N*/ 	}
/*N*/ }

//	class SwFmtFrmSize
//	Implementierung teilweise inline im hxx

/*N*/ SwFmtFrmSize::SwFmtFrmSize( SwFrmSize eSize, SwTwips nWidth, SwTwips nHeight )
/*N*/ 	: SfxPoolItem( RES_FRM_SIZE ),
/*N*/ 	aSize( nWidth, nHeight ),
/*N*/ 	eFrmSize( eSize )
/*N*/ {
/*N*/ 	nWidthPercent = nHeightPercent = 0;
/*N*/ }

/*N*/ SwFmtFrmSize& SwFmtFrmSize::operator=( const SwFmtFrmSize& rCpy )
/*N*/ {
/*N*/ 	aSize = rCpy.GetSize();
/*N*/ 	eFrmSize = rCpy.GetSizeType();
/*N*/ 	nHeightPercent = rCpy.GetHeightPercent();
/*N*/ 	nWidthPercent  = rCpy.GetWidthPercent();
/*N*/ 	return *this;
/*N*/ }

/*N*/ int  SwFmtFrmSize::operator==( const SfxPoolItem& rAttr ) const
/*N*/ {
/*N*/ 	ASSERT( SfxPoolItem::operator==( rAttr ), "keine gleichen Attribute" );
/*N*/ 	return( eFrmSize 		== ((SwFmtFrmSize&)rAttr).eFrmSize &&
/*N*/ 			aSize    		== ((SwFmtFrmSize&)rAttr).GetSize()&&
/*N*/ 			nWidthPercent	== ((SwFmtFrmSize&)rAttr).GetWidthPercent() &&
/*N*/ 			nHeightPercent	== ((SwFmtFrmSize&)rAttr).GetHeightPercent() );
/*N*/ }

/*N*/ SfxPoolItem*  SwFmtFrmSize::Clone( SfxItemPool* ) const
/*N*/ {
/*N*/ 	return new SwFmtFrmSize( *this );
/*N*/ }


/* -----------------24.04.98 11:36-------------------
 *
 * --------------------------------------------------*/
/*N*/ BOOL SwFmtFrmSize::QueryValue( uno::Any& rVal, BYTE nMemberId ) const
/*N*/ {
/*N*/ 	// hier wird immer konvertiert!
/*N*/ 	nMemberId &= ~CONVERT_TWIPS;
/*N*/ 	switch ( nMemberId )
/*N*/ 	{
/*N*/ 		case MID_FRMSIZE_SIZE:
/*N*/ 		{
/*?*/ 			awt::Size aTmp;
/*?*/ 			aTmp.Height = TWIP_TO_MM100(aSize.Height());
/*?*/ 			aTmp.Width = TWIP_TO_MM100(aSize.Width());
/*?*/ 			rVal.setValue(&aTmp, ::getCppuType((const awt::Size*)0));
/*N*/ 		}
/*N*/ 		break;
/*N*/ 		case MID_FRMSIZE_REL_HEIGHT:
/*N*/ 			rVal <<= (sal_Int16)(GetHeightPercent() != 0xFF ? GetHeightPercent() : 0);
/*N*/ 		break;
/*N*/ 		case MID_FRMSIZE_REL_WIDTH:
/*N*/ 			rVal <<= (sal_Int16)(GetWidthPercent() != 0xFF ? GetWidthPercent() : 0);
/*N*/ 		break;
/*N*/         case MID_FRMSIZE_IS_SYNC_HEIGHT_TO_WIDTH:
/*N*/ 		{
/*N*/ 			BOOL bTmp = 0xFF == GetHeightPercent();
/*N*/ 			rVal.setValue(&bTmp, ::getBooleanCppuType());
/*N*/ 		}
/*N*/ 		break;
/*N*/ 		case MID_FRMSIZE_IS_SYNC_WIDTH_TO_HEIGHT:
/*N*/ 		{
/*N*/ 			BOOL bTmp = 0xFF == GetWidthPercent();
/*N*/ 			rVal.setValue(&bTmp, ::getBooleanCppuType());
/*N*/ 		}
/*N*/ 		break;
/*N*/ 		case MID_FRMSIZE_WIDTH :
/*N*/ 			rVal <<= (sal_Int32)TWIP_TO_MM100(aSize.Width());
/*N*/ 		break;
/*N*/         case MID_FRMSIZE_HEIGHT:
/*N*/             // #95848# returned size should never be zero.
/*N*/             // (there was a bug that allowed for setting height to 0.
/*N*/             // Thus there some documents existing with that not allowed
/*N*/             // attribut value which may cause problems on import.)
/*N*/             rVal <<= (sal_Int32)TWIP_TO_MM100(aSize.Height() < MINLAY ? MINLAY : aSize.Height() );
/*N*/         break;
/*N*/         case MID_FRMSIZE_SIZE_TYPE:
/*N*/ 			rVal <<= (sal_Int16)GetSizeType();
/*N*/ 		break;
/*N*/ 		case MID_FRMSIZE_IS_AUTO_HEIGHT:
/*N*/ 		{
/*?*/ 			BOOL bTmp = ATT_FIX_SIZE != GetSizeType();
/*?*/ 			rVal.setValue(&bTmp, ::getBooleanCppuType());
/*N*/ 		}
/*N*/ 		break;
/*N*/ 	}
/*N*/ 	return sal_True;
/*N*/ }

/* -----------------24.04.98 11:36-------------------
 *
 * --------------------------------------------------*/
/*N*/ BOOL SwFmtFrmSize::PutValue( const uno::Any& rVal, BYTE nMemberId )
/*N*/ {
/*N*/ 	sal_Bool bConvert = 0 != (nMemberId&CONVERT_TWIPS);
/*N*/ 	nMemberId &= ~CONVERT_TWIPS;
/*N*/ 	sal_Bool bRet = sal_True;
/*N*/ 	switch ( nMemberId )
/*N*/ 	{
/*N*/ 		case MID_FRMSIZE_SIZE:
/*N*/ 		{
/*?*/             awt::Size aVal;
/*?*/             if(!(rVal >>= aVal))
/*?*/                 bRet = sal_False;
/*?*/             else
/*?*/             {
/*?*/                 Size aTmp(aVal.Width, aVal.Height);
/*?*/                 if(bConvert)
/*?*/                 {
/*?*/                     aTmp.Height() = MM100_TO_TWIP(aTmp.Height());
/*?*/                     aTmp.Width() = MM100_TO_TWIP(aTmp.Width());
/*?*/                 }
/*?*/                 if(aTmp.Height() && aTmp.Width())
/*?*/                     aSize = aTmp;
/*?*/                 else
/*?*/                     bRet = sal_False;
/*?*/             }
/*N*/ 		}
/*N*/ 		break;
/*N*/ 		case MID_FRMSIZE_REL_HEIGHT:
/*N*/ 		{
/*N*/ 			sal_Int16 nSet;
/*N*/ 			rVal >>= nSet;
/*N*/           if(nSet >= 0 && nSet <= 0xfe)
/*N*/ 				SetHeightPercent((BYTE)nSet);
/*N*/ 			else
/*?*/ 				bRet = sal_False;
/*N*/ 		}
/*N*/ 		break;
/*N*/ 		case MID_FRMSIZE_REL_WIDTH:
/*N*/ 		{
/*N*/ 			sal_Int16 nSet;
/*N*/ 			rVal >>= nSet;
/*N*/             if(nSet >= 0 && nSet <= 0xfe)
/*N*/ 				SetWidthPercent((BYTE)nSet);
/*N*/ 			else
/*?*/ 				bRet = sal_False;
/*N*/ 		}
/*N*/ 		break;
/*N*/ 		case MID_FRMSIZE_IS_SYNC_HEIGHT_TO_WIDTH:
/*N*/ 		{
/*N*/ 			sal_Bool bSet = *(sal_Bool*)rVal.getValue();
/*N*/ 			if(bSet)
/*?*/ 				SetHeightPercent(0xff);
/*N*/ 			else if( 0xff == GetHeightPercent() )
/*?*/ 				SetHeightPercent( 0 );
/*N*/ 		}
/*N*/ 		break;
/*N*/ 		case MID_FRMSIZE_IS_SYNC_WIDTH_TO_HEIGHT:
/*N*/ 		{
/*N*/ 			sal_Bool bSet = *(sal_Bool*)rVal.getValue();
/*N*/ 			if(bSet)
/*?*/ 				SetWidthPercent(0xff);
/*N*/ 			else if( 0xff == GetWidthPercent() )
/*?*/ 				SetWidthPercent(0);
/*N*/ 		}
/*N*/ 		break;
/*N*/ 		case MID_FRMSIZE_WIDTH :
/*N*/ 		{
/*N*/             sal_Int32 nWd;
/*N*/             if(rVal >>= nWd)
/*N*/             {
/*N*/                 if(bConvert)
/*N*/                     nWd = MM100_TO_TWIP(nWd);
/*N*/                 if(nWd > 0)
/*N*/                     aSize.Width() = nWd;
/*N*/                 else
/*?*/                     bRet = sal_False;
/*N*/             }
/*N*/             else
/*?*/                 bRet = sal_False;
/*N*/         }
/*N*/ 		break;
/*N*/ 		case MID_FRMSIZE_HEIGHT:
/*N*/ 		{
/*N*/             sal_Int32 nHg;
/*N*/             if(rVal >>= nHg)
/*N*/             {
/*N*/                 if(bConvert)
/*N*/                     nHg = MM100_TO_TWIP(nHg);
/*N*/                 if(nHg > 0)
/*N*/                     aSize.Height() = nHg;
/*N*/                 else
/*?*/                     bRet = sal_False;
/*N*/             }
/*N*/             else
/*?*/                 bRet = sal_False;
/*N*/         }
/*N*/ 		break;
/*N*/ 		case MID_FRMSIZE_SIZE_TYPE:
/*N*/ 		{
/*N*/             sal_Int16 nType;
/*N*/             if((rVal >>= nType) && nType >= 0 && nType <= ATT_MIN_SIZE )
/*N*/ 			{
/*N*/ 				SetSizeType((SwFrmSize)nType);
/*N*/ 			}
/*N*/             else
/*?*/                 bRet = sal_False;
/*N*/         }
/*N*/ 		break;
/*N*/ 		case MID_FRMSIZE_IS_AUTO_HEIGHT:
/*N*/ 		{
/*?*/ 			sal_Bool bSet = *(sal_Bool*)rVal.getValue();
/*?*/ 			SetSizeType(bSet ? ATT_VAR_SIZE : ATT_FIX_SIZE);
/*?*/  		}
/*?*/ 		break;
/*?*/ 		default:
/*?*/ 			bRet = sal_False;
/*N*/ 	}
/*N*/ 	return bRet;
/*N*/ }

/*N*/ Size  SwFmtFrmSize::GetSizeConvertedToSw31(
/*N*/ 				const SvxLRSpaceItem *pLRSpace,
/*N*/ 				const SvxULSpaceItem *pULSpace ) const
/*N*/ {
/*N*/ 	// Sw4.0: Groesse enthaelt keine Raender
/*N*/ 	// Sw3.x: Groesse enthaelt Raender
/*N*/ 	// ==> Raender addieren
/*N*/ 	Size aNewSize = GetSize();
/*N*/ 	if( pLRSpace )
/*N*/ 	{
/*N*/ 		aNewSize.Width() += pLRSpace->GetLeft();
/*N*/ 		aNewSize.Width() += pLRSpace->GetRight();
/*N*/ 	}
/*N*/ 	if( pULSpace )
/*N*/ 	{
/*N*/ 		aNewSize.Height() += pULSpace->GetUpper();
/*N*/ 		aNewSize.Height() +=  pULSpace->GetLower();
/*N*/ 	}
/*N*/ 	return aNewSize;
/*N*/ }

/*N*/ Size  SwFmtFrmSize::GetSizeConvertedFromSw31(
/*N*/ 				const SvxLRSpaceItem *pLRSpace,
/*N*/ 				const SvxULSpaceItem *pULSpace ) const
/*N*/ {
/*N*/ 	// Sw4.0: Groesse enthaelt keine Raender
/*N*/ 	// Sw3.x: Groesse enthaelt Raender
/*N*/ 	// ==> Raender subtrahieren
/*N*/ 	Size aNewSize = GetSize();
/*N*/ 	if( pLRSpace )
/*N*/ 	{
/*N*/ 		aNewSize.Width() -= pLRSpace->GetLeft();
/*N*/ 		aNewSize.Width() -= pLRSpace->GetRight();
/*N*/ 	}
/*N*/ 	if( pULSpace )
/*N*/ 	{
/*N*/ 		aNewSize.Height() -= pULSpace->GetUpper();
/*N*/ 		aNewSize.Height() -=  pULSpace->GetLower();
/*N*/ 	}
/*N*/ 	return aNewSize;
/*N*/ }


//	class SwFmtFillOrder
//	Implementierung teilweise inline im hxx

/*N*/ SwFmtFillOrder::SwFmtFillOrder( SwFillOrder nFO )
/*N*/ 	: SfxEnumItem( RES_FILL_ORDER, sal_uInt16(nFO) )
/*N*/ {}

/*N*/ SfxPoolItem*  SwFmtFillOrder::Clone( SfxItemPool* ) const
/*N*/ {
/*N*/ 	return new SwFmtFillOrder( GetFillOrder() );
/*N*/ }

//STRIP001 sal_uInt16  SwFmtFillOrder::GetValueCount() const
//STRIP001 {
//STRIP001 	return SW_FILL_ORDER_END - SW_FILL_ORDER_BEGIN;
//STRIP001 }

//	class SwFmtHeader
//	Implementierung teilweise inline im hxx

/*N*/ SwFmtHeader::SwFmtHeader( SwFrmFmt *pHeaderFmt )
/*N*/ 	: SfxPoolItem( RES_HEADER ),
/*N*/ 	SwClient( pHeaderFmt ),
/*N*/ 	bActive( pHeaderFmt ? sal_True : sal_False )
/*N*/ {
/*N*/ }

/*N*/ SwFmtHeader::SwFmtHeader( const SwFmtHeader &rCpy )
/*N*/ 	: SfxPoolItem( RES_HEADER ),
/*N*/ 	SwClient( (SwModify*)rCpy.GetRegisteredIn() ),
/*N*/ 	bActive( rCpy.IsActive() )
/*N*/ {
/*N*/ }

/*N*/ SwFmtHeader::SwFmtHeader( sal_Bool bOn )
/*N*/ 	: SfxPoolItem( RES_HEADER ),
/*N*/ 	SwClient( 0 ),
/*N*/ 	bActive( bOn )
/*N*/ {
/*N*/ }

/*N*/  SwFmtHeader::~SwFmtHeader()
/*N*/ {
/*N*/ 	if ( GetHeaderFmt() )
/*N*/ 		DelHFFormat( this, GetHeaderFmt() );
/*N*/ }

/*N*/ int  SwFmtHeader::operator==( const SfxPoolItem& rAttr ) const
/*N*/ {
/*N*/ 	ASSERT( SfxPoolItem::operator==( rAttr ), "keine gleichen Attribute" );
/*N*/ 	return ( pRegisteredIn == ((SwFmtHeader&)rAttr).GetRegisteredIn() &&
/*N*/ 			 bActive == ((SwFmtHeader&)rAttr).IsActive() );
/*N*/ }

/*N*/ SfxPoolItem*  SwFmtHeader::Clone( SfxItemPool* ) const
/*N*/ {
/*N*/ 	return new SwFmtHeader( *this );
/*N*/ }

//	class SwFmtFooter
//	Implementierung teilweise inline im hxx

/*N*/ SwFmtFooter::SwFmtFooter( SwFrmFmt *pFooterFmt )
/*N*/ 	: SfxPoolItem( RES_FOOTER ),
/*N*/ 	SwClient( pFooterFmt ),
/*N*/ 	bActive( pFooterFmt ? sal_True : sal_False )
/*N*/ {
/*N*/ }

/*N*/ SwFmtFooter::SwFmtFooter( const SwFmtFooter &rCpy )
/*N*/ 	: SfxPoolItem( RES_FOOTER ),
/*N*/ 	SwClient( (SwModify*)rCpy.GetRegisteredIn() ),
/*N*/ 	bActive( rCpy.IsActive() )
/*N*/ {
/*N*/ }

/*N*/ SwFmtFooter::SwFmtFooter( sal_Bool bOn )
/*N*/ 	: SfxPoolItem( RES_FOOTER ),
/*N*/ 	SwClient( 0 ),
/*N*/ 	bActive( bOn )
/*N*/ {
/*N*/ }

/*N*/  SwFmtFooter::~SwFmtFooter()
/*N*/ {
/*N*/ 	if ( GetFooterFmt() )
/*N*/ 		DelHFFormat( this, GetFooterFmt() );
/*N*/ }

/*N*/ int  SwFmtFooter::operator==( const SfxPoolItem& rAttr ) const
/*N*/ {
/*N*/ 	ASSERT( SfxPoolItem::operator==( rAttr ), "keine gleichen Attribute" );
/*N*/ 	return ( pRegisteredIn == ((SwFmtFooter&)rAttr).GetRegisteredIn() &&
/*N*/ 			 bActive == ((SwFmtFooter&)rAttr).IsActive() );
/*N*/ }

/*N*/ SfxPoolItem*  SwFmtFooter::Clone( SfxItemPool* ) const
/*N*/ {
/*N*/ 	return new SwFmtFooter( *this );
/*N*/ }

//	class SwFmtCntnt
//	Implementierung teilweise inline im hxx

/*N*/ SwFmtCntnt::SwFmtCntnt( const SwFmtCntnt &rCpy )
/*N*/ 	: SfxPoolItem( RES_CNTNT )
/*N*/ {
/*N*/ 	pStartNode = rCpy.GetCntntIdx() ?
/*N*/ 					new SwNodeIndex( *rCpy.GetCntntIdx() ) : 0;
/*N*/ }

/*N*/ SwFmtCntnt::SwFmtCntnt( const SwStartNode *pStartNd )
/*N*/ 	: SfxPoolItem( RES_CNTNT )
/*N*/ {
/*N*/ 	pStartNode = pStartNd ? new SwNodeIndex( *pStartNd ) : 0;
/*N*/ }

/*N*/  SwFmtCntnt::~SwFmtCntnt()
/*N*/ {
/*N*/ 	delete pStartNode;
/*N*/ }

/*N*/ void SwFmtCntnt::SetNewCntntIdx( const SwNodeIndex *pIdx )
/*N*/ {
/*N*/ 	delete pStartNode;
/*N*/ 	pStartNode = pIdx ? new SwNodeIndex( *pIdx ) : 0;
/*N*/ }

/*N*/ int  SwFmtCntnt::operator==( const SfxPoolItem& rAttr ) const
/*N*/ {
/*N*/ 	ASSERT( SfxPoolItem::operator==( rAttr ), "keine gleichen Attribute" );
/*N*/ 	if( (long)pStartNode ^ (long)((SwFmtCntnt&)rAttr).pStartNode )
/*N*/ 		return 0;
/*?*/ 	if( pStartNode )
/*?*/ 		return ( *pStartNode == *((SwFmtCntnt&)rAttr).GetCntntIdx() );
/*?*/ 	return 1;
/*N*/ }

/*N*/ SfxPoolItem*  SwFmtCntnt::Clone( SfxItemPool* ) const
/*N*/ {
/*N*/ 	return new SwFmtCntnt( *this );
/*N*/ }

//	class SwFmtPageDesc
//	Implementierung teilweise inline im hxx

/*N*/ SwFmtPageDesc::SwFmtPageDesc( const SwFmtPageDesc &rCpy )
/*N*/ 	: SfxPoolItem( RES_PAGEDESC ),
/*N*/ 	SwClient( (SwPageDesc*)rCpy.GetPageDesc() ),
/*N*/ 	pDefinedIn( 0 ),
/*N*/ 	nNumOffset( rCpy.nNumOffset ),
/*N*/ 	nDescNameIdx( rCpy.nDescNameIdx )
/*N*/ {
/*N*/ }

/*N*/ SwFmtPageDesc::SwFmtPageDesc( const SwPageDesc *pDesc )
/*N*/ 	: SfxPoolItem( RES_PAGEDESC ),
/*N*/ 	SwClient( (SwPageDesc*)pDesc ),
/*N*/ 	pDefinedIn( 0 ),
/*N*/ 	nNumOffset( 0 ),
/*N*/ 	nDescNameIdx( 0xFFFF )	// IDX_NO_VALUE
/*N*/ {
/*N*/ }

/*N*/  SwFmtPageDesc::~SwFmtPageDesc() {}

/*N*/ int  SwFmtPageDesc::operator==( const SfxPoolItem& rAttr ) const
/*N*/ {
/*N*/ 	ASSERT( SfxPoolItem::operator==( rAttr ), "keine gleichen Attribute" );
/*N*/ 	return	( pDefinedIn == ((SwFmtPageDesc&)rAttr).pDefinedIn ) &&
/*N*/ 			( nNumOffset == ((SwFmtPageDesc&)rAttr).nNumOffset ) &&
/*N*/ 			( GetPageDesc() == ((SwFmtPageDesc&)rAttr).GetPageDesc() );
/*N*/ }

/*N*/ SfxPoolItem*  SwFmtPageDesc::Clone( SfxItemPool* ) const
/*N*/ {
/*N*/ 	return new SwFmtPageDesc( *this );
/*N*/ }

/*N*/ void SwFmtPageDesc::Modify( SfxPoolItem* pOld, SfxPoolItem* pNew )
/*N*/ {
/*N*/ 	if( !pDefinedIn )
/*N*/ 		return;
/*N*/ 
/*N*/ 	sal_uInt16 nWhich = pOld ? pOld->Which() : pNew ? pNew->Which() : 0;
/*N*/ 	switch( nWhich )
/*N*/ 	{
/*N*/ 		case RES_OBJECTDYING:
/*N*/ 				//Der Pagedesc, bei dem ich angemeldet bin stirbt, ich trage
/*N*/ 				//mich also bei meinem Format aus.
/*N*/ 				//Dabei werden ich Deletet!!!
/*N*/ 			if( IS_TYPE( SwFmt, pDefinedIn ))
/*N*/ #ifndef PRODUCT
/*N*/ 			{
/*?*/ 				sal_Bool bDel = ((SwFmt*)pDefinedIn)->ResetAttr( RES_PAGEDESC );
/*?*/ 				ASSERT( bDel, ";-) FmtPageDesc nicht zerstoert." );
/*N*/ 			}
/*N*/ #else
/*N*/ 				((SwFmt*)pDefinedIn)->ResetAttr( RES_PAGEDESC );
/*N*/ #endif
/*N*/ 			else if( IS_TYPE( SwCntntNode, pDefinedIn ))
/*N*/ #ifndef PRODUCT
/*N*/ 			{
/*?*/ 				sal_Bool bDel = ((SwCntntNode*)pDefinedIn)->ResetAttr( RES_PAGEDESC );
/*?*/ 				ASSERT( bDel, ";-) FmtPageDesc nicht zerstoert." );
/*N*/ 			}
/*N*/ #else
/*N*/ 				((SwCntntNode*)pDefinedIn)->ResetAttr( RES_PAGEDESC );
/*N*/ #endif
/*N*/ 			break;
/*N*/ 
/*N*/ 		default:
/*N*/ 			/* do nothing */;
/*N*/ 	}
/*N*/ }

/*N*/ BOOL SwFmtPageDesc::QueryValue( uno::Any& rVal, BYTE nMemberId ) const
/*N*/ {
/*N*/ 	// hier wird immer konvertiert!
/*N*/ 	nMemberId &= ~CONVERT_TWIPS;
/*N*/ 	sal_Bool	bRet = sal_True;
/*N*/ 	switch ( nMemberId )
/*N*/ 	{
/*N*/ 		case MID_PAGEDESC_PAGENUMOFFSET:
/*N*/ 			rVal <<= (sal_Int16)GetNumOffset();
/*N*/ 			break;
/*N*/ 
/*N*/ 		case MID_PAGEDESC_PAGEDESCNAME:
/*N*/ 			{
/*N*/ 				const SwPageDesc* pDesc = GetPageDesc();
/*N*/ 				if( pDesc )
/*N*/ 				{
/*N*/ 					String aString;
/*N*/ 					SwStyleNameMapper::FillProgName(pDesc->GetName(), aString, GET_POOLID_PAGEDESC, sal_True );
/*N*/ 					rVal <<= OUString( aString );
/*N*/ 				}
/*N*/ 				else
/*N*/ 					rVal.clear();
/*N*/ 			}
/*N*/ 			break;
/*N*/ 		default:
/*?*/ 			ASSERT( !this, "unknown MemberId" );
/*?*/ 			bRet = sal_False;
/*N*/ 	}
/*N*/ 	return bRet;
/*N*/ }

/*N*/ BOOL SwFmtPageDesc::PutValue( const uno::Any& rVal, BYTE nMemberId )
/*N*/ {
/*N*/ 	// hier wird immer konvertiert!
/*N*/ 	nMemberId &= ~CONVERT_TWIPS;
/*N*/ 	sal_Bool bRet = sal_True;
/*N*/ 	switch ( nMemberId )
/*N*/ 	{
/*N*/ 		case MID_PAGEDESC_PAGENUMOFFSET:
/*N*/         {
/*N*/             sal_Int16 nOffset;
/*N*/             if(rVal >>= nOffset)
/*N*/                 SetNumOffset( nOffset );
/*N*/             else
/*?*/                 bRet = sal_False;
/*N*/         }
/*N*/         break;
/*N*/ 
/*N*/ 		case MID_PAGEDESC_PAGEDESCNAME:
            /* geht nicht, weil das Attribut eigentlich nicht den Namen
             * sondern einen Pointer auf den PageDesc braucht (ist Client davon).
             * Der Pointer waere aber ueber den Namen nur vom Dokument zu erfragen.
             */
/*N*/ 		default:
/*?*/ 			ASSERT( !this, "unknown MemberId" );
/*?*/ 			bRet = sal_False;
/*N*/ 	}
/*N*/ 	return bRet;
/*N*/ }


//	class SwFmtCol
//	Implementierung teilweise inline im hxx

/*N*/ SwColumn::SwColumn() :
/*N*/ 	nUpper( 0 ),
/*N*/ 	nLower( 0 ),
/*N*/ 	nLeft ( 0 ),
/*N*/ 	nRight( 0 ),
/*N*/ 	nWish ( 0 )
/*N*/ {
/*N*/ }

/*N*/ sal_Bool SwColumn::operator==( const SwColumn &rCmp )
/*N*/ {
/*N*/ 	return (nWish    == rCmp.GetWishWidth() &&
/*N*/ 			GetLeft()  == rCmp.GetLeft() &&
/*N*/ 			GetRight() == rCmp.GetRight() &&
/*N*/ 			GetUpper() == rCmp.GetUpper() &&
/*N*/ 			GetLower() == rCmp.GetLower()) ? sal_True : sal_False;
/*N*/ }

/*N*/ SwFmtCol::SwFmtCol( const SwFmtCol& rCpy )
/*N*/ 	: SfxPoolItem( RES_COL ),
/*N*/ 	nLineWidth( rCpy.nLineWidth),
/*N*/ 	aLineColor( rCpy.aLineColor),
/*N*/ 	nLineHeight( rCpy.GetLineHeight() ),
/*N*/ 	eAdj( rCpy.GetLineAdj() ),
/*N*/ 	nWidth( rCpy.GetWishWidth() ),
/*N*/ 	bOrtho( rCpy.IsOrtho() ),
/*N*/ 	aColumns( (sal_Int8)rCpy.GetNumCols(), 1 )
/*N*/ {
/*N*/ 	for ( sal_uInt16 i = 0; i < rCpy.GetNumCols(); ++i )
/*N*/ 	{
/*N*/ 		SwColumn *pCol = new SwColumn( *rCpy.GetColumns()[i] );
/*N*/ 		aColumns.Insert( pCol, aColumns.Count() );
/*N*/ 	}
/*N*/ }

/*N*/ SwFmtCol::~SwFmtCol() {}

//STRIP001 SwFmtCol& SwFmtCol::operator=( const SwFmtCol& rCpy )
//STRIP001 {
//STRIP001 	nLineWidth  = rCpy.nLineWidth;
//STRIP001 	aLineColor  = rCpy.aLineColor;
//STRIP001 	nLineHeight	= rCpy.GetLineHeight();
//STRIP001 	eAdj		= rCpy.GetLineAdj();
//STRIP001 	nWidth		= rCpy.GetWishWidth();
//STRIP001 	bOrtho		= rCpy.IsOrtho();
//STRIP001 
//STRIP001 	if ( aColumns.Count() )
//STRIP001 		aColumns.DeleteAndDestroy( 0, aColumns.Count() );
//STRIP001 	for ( sal_uInt16 i = 0; i < rCpy.GetNumCols(); ++i )
//STRIP001 	{
//STRIP001 		SwColumn *pCol = new SwColumn( *rCpy.GetColumns()[i] );
//STRIP001 		aColumns.Insert( pCol, aColumns.Count() );
//STRIP001 	}
//STRIP001 	return *this;
//STRIP001 }

/*N*/ SwFmtCol::SwFmtCol()
/*N*/ 	: SfxPoolItem( RES_COL ),
/*N*/ 	nLineHeight( 100 ),
/*N*/ 	eAdj( COLADJ_NONE ),
/*N*/ 	nWidth( USHRT_MAX ),
/*N*/ 	bOrtho( sal_True ),
/*N*/ 	nLineWidth(0)
/*N*/ {
/*N*/ }

/*N*/ int SwFmtCol::operator==( const SfxPoolItem& rAttr ) const
/*N*/ {
/*N*/ 	ASSERT( SfxPoolItem::operator==( rAttr ), "keine gleichen Attribute" );
/*N*/ 	const SwFmtCol &rCmp = (const SwFmtCol&)rAttr;
/*N*/ 	if( !(nLineWidth		== rCmp.nLineWidth  &&
/*N*/ 		  aLineColor        == rCmp.aLineColor	&&
/*N*/ 		  nLineHeight  		 == rCmp.GetLineHeight() &&
/*N*/ 		  eAdj		 		 == rCmp.GetLineAdj() &&
/*N*/ 		  nWidth  	 		 == rCmp.GetWishWidth() &&
/*N*/ 		  bOrtho  			 == rCmp.IsOrtho() &&
/*N*/ 		  aColumns.Count() == rCmp.GetNumCols()) )
/*N*/ 		return 0;
/*N*/ 
/*N*/ 	for ( sal_uInt16 i = 0; i < aColumns.Count(); ++i )
/*N*/ 		if ( !(*aColumns[i] == *rCmp.GetColumns()[i]) )
/*?*/ 			return 0;
/*N*/ 
/*N*/ 	return 1;
/*N*/ }

/*N*/ SfxPoolItem*  SwFmtCol::Clone( SfxItemPool* ) const
/*N*/ {
/*N*/ 	return new SwFmtCol( *this );
/*N*/ }

/*N*/ sal_uInt16 SwFmtCol::GetGutterWidth( sal_Bool bMin ) const
/*N*/ {
/*N*/ 	sal_uInt16 nRet = 0;
/*N*/ 	if ( aColumns.Count() == 2 )
/*N*/ 		nRet = aColumns[0]->GetRight() + aColumns[1]->GetLeft();
/*N*/ 	else if ( aColumns.Count() > 2 )
/*N*/ 	{
/*N*/ 		sal_Bool bSet = sal_False;
/*N*/ 		for ( sal_uInt16 i = 1; i < aColumns.Count()-1; ++i )
/*N*/ 		{
/*N*/ 			const sal_uInt16 nTmp = aColumns[i]->GetRight() + aColumns[i+1]->GetLeft();
/*N*/ 			if ( bSet )
/*N*/ 			{
/*N*/ 				if ( nTmp != nRet )
/*N*/ 				{
/*?*/ 					if ( !bMin )
/*?*/ 						return USHRT_MAX;
/*?*/ 					if ( nRet > nTmp )
/*?*/ 						nRet = nTmp;
/*N*/ 				}
/*N*/ 			}
/*N*/ 			else
/*N*/ 			{	bSet = sal_True;
/*N*/ 				nRet = nTmp;
/*N*/ 			}
/*N*/ 		}
/*N*/ 	}
/*N*/ 	return nRet;
/*N*/ }

//STRIP001 void SwFmtCol::SetGutterWidth( sal_uInt16 nNew, sal_uInt16 nAct )
//STRIP001 {
//STRIP001 	if ( bOrtho )
//STRIP001 		Calc( nNew, nAct );
//STRIP001 	else
//STRIP001 	{
//STRIP001 		sal_uInt16 nHalf = nNew / 2;
//STRIP001 		for ( sal_uInt16 i = 0; i < aColumns.Count(); ++i )
//STRIP001 		{	SwColumn *pCol = aColumns[i];
//STRIP001 			pCol->SetLeft ( nHalf );
//STRIP001 			pCol->SetRight( nHalf );
//STRIP001 			if ( i == 0 )
//STRIP001 				pCol->SetLeft( 0 );
//STRIP001 			else if ( i == (aColumns.Count() - 1) )
//STRIP001 				pCol->SetRight( 0 );
//STRIP001 		}
//STRIP001 	}
//STRIP001 }

//STRIP001 void SwFmtCol::Init( sal_uInt16 nNumCols, sal_uInt16 nGutterWidth, sal_uInt16 nAct )
//STRIP001 {
//STRIP001 	//Loeschen scheint hier auf den erste Blick vielleicht etwas zu heftig;
//STRIP001 	//anderfalls muessten allerdings alle Werte der verbleibenden SwColumn's
//STRIP001 	//initialisiert werden.
//STRIP001 	if ( aColumns.Count() )
//STRIP001 		aColumns.DeleteAndDestroy( 0, aColumns.Count() );
//STRIP001 	for ( sal_uInt16 i = 0; i < nNumCols; ++i )
//STRIP001 	{	SwColumn *pCol = new SwColumn;
//STRIP001 		aColumns.Insert( pCol, i );
//STRIP001 	}
//STRIP001 	bOrtho = sal_True;
//STRIP001 	nWidth = USHRT_MAX;
//STRIP001 	if( nNumCols )
//STRIP001 		Calc( nGutterWidth, nAct );
//STRIP001 }

//STRIP001 void SwFmtCol::SetOrtho( sal_Bool bNew, sal_uInt16 nGutterWidth, sal_uInt16 nAct )
//STRIP001 {
//STRIP001 	bOrtho = bNew;
//STRIP001 	if ( bNew && aColumns.Count() )
//STRIP001 		Calc( nGutterWidth, nAct );
//STRIP001 }

/*N*/ sal_uInt16 SwFmtCol::CalcColWidth( sal_uInt16 nCol, sal_uInt16 nAct ) const
/*N*/ {
/*N*/ 	ASSERT( nCol < aColumns.Count(), ":-( ColumnsArr ueberindiziert." );
/*N*/ 	if ( nWidth != nAct )
/*N*/ 	{
/*N*/ 		long nW = aColumns[nCol]->GetWishWidth();
/*N*/ 		nW *= nAct;
/*N*/ 		nW /= nWidth;
/*N*/ 		return sal_uInt16(nW);
/*N*/ 	}
/*N*/ 	else
/*?*/ 		return aColumns[nCol]->GetWishWidth();
/*N*/ }

//STRIP001 sal_uInt16 SwFmtCol::CalcPrtColWidth( sal_uInt16 nCol, sal_uInt16 nAct ) const
//STRIP001 {
//STRIP001 	ASSERT( nCol < aColumns.Count(), ":-( ColumnsArr ueberindiziert." );
//STRIP001 	sal_uInt16 nRet = CalcColWidth( nCol, nAct );
//STRIP001 	SwColumn *pCol = aColumns[nCol];
//STRIP001 	nRet -= pCol->GetLeft();
//STRIP001 	nRet -= pCol->GetRight();
//STRIP001 	return nRet;
//STRIP001 }

//STRIP001 void SwFmtCol::Calc( sal_uInt16 nGutterWidth, sal_uInt16 nAct )
//STRIP001 {
//STRIP001 	//Erstmal die Spalten mit der Aktuellen Breite einstellen, dann die
//STRIP001 	//Wunschbreite der Spalten anhand der Gesamtwunschbreite hochrechnen.
//STRIP001 
//STRIP001 	const sal_uInt16 nGutterHalf = nGutterWidth ? nGutterWidth / 2 : 0;
//STRIP001 
//STRIP001 	//Breite der PrtAreas ist Gesamtbreite - Zwischenraeume / Anzahl
//STRIP001 	const sal_uInt16 nPrtWidth =
//STRIP001 				(nAct - ((GetNumCols()-1) * nGutterWidth)) / GetNumCols();
//STRIP001 	sal_uInt16 nAvail = nAct;
//STRIP001 
//STRIP001 	//Die erste Spalte ist PrtBreite + (Zwischenraumbreite/2)
//STRIP001 	const sal_uInt16 nLeftWidth = nPrtWidth + nGutterHalf;
//STRIP001 	SwColumn *pCol = aColumns[0];
//STRIP001 	pCol->SetWishWidth( nLeftWidth );
//STRIP001 	pCol->SetRight( nGutterHalf );
//STRIP001 	pCol->SetLeft ( 0 );
//STRIP001 	nAvail -= nLeftWidth;
//STRIP001 
//STRIP001 	//Spalte 2 bis n-1 ist PrtBreite + Zwischenraumbreite
//STRIP001 	const sal_uInt16 nMidWidth = nPrtWidth + nGutterWidth;
//STRIP001 	for ( sal_uInt16 i = 1; i < GetNumCols()-1; ++i )
//STRIP001 	{
//STRIP001 		pCol = aColumns[i];
//STRIP001 		pCol->SetWishWidth( nMidWidth );
//STRIP001 		pCol->SetLeft ( nGutterHalf );
//STRIP001 		pCol->SetRight( nGutterHalf );
//STRIP001 		nAvail -= nMidWidth;
//STRIP001 	}
//STRIP001 
//STRIP001 	//Die Letzte Spalte entspricht wieder der ersten, um Rundungsfehler
//STRIP001 	//auszugleichen wird der letzten Spalte alles zugeschlagen was die
//STRIP001 	//anderen nicht verbraucht haben.
//STRIP001 	pCol = aColumns[aColumns.Count()-1];
//STRIP001 	pCol->SetWishWidth( nAvail );
//STRIP001 	pCol->SetLeft ( nGutterHalf );
//STRIP001 	pCol->SetRight( 0 );
//STRIP001 
//STRIP001 	//Umrechnen der aktuellen Breiten in Wunschbreiten.
//STRIP001 	for ( i = 0; i < aColumns.Count(); ++i )
//STRIP001 	{
//STRIP001 		pCol = aColumns[i];
//STRIP001 		long nTmp = pCol->GetWishWidth();
//STRIP001 		nTmp *= GetWishWidth();
//STRIP001 		nTmp /= nAct;
//STRIP001 		pCol->SetWishWidth( sal_uInt16(nTmp) );
//STRIP001 	}
//STRIP001 }

/*N*/ BOOL SwFmtCol::QueryValue( uno::Any& rVal, BYTE nMemberId ) const
/*N*/ {
/*N*/ 	// hier wird immer konvertiert!
/*N*/ 	nMemberId &= ~CONVERT_TWIPS;
/*N*/ 	if(MID_COLUMN_SEPARATOR_LINE == nMemberId)
/*N*/ 	{
/*?*/ 		DBG_ERROR("not implemented")
/*N*/ 	}
/*N*/ 	else
/*N*/ 	{
/*N*/ 		uno::Reference< text::XTextColumns >  xCols = new SwXTextColumns(*this);
/*N*/ 		rVal.setValue(&xCols, ::getCppuType((uno::Reference< text::XTextColumns>*)0));
/*N*/ 	}
/*N*/ 	return sal_True;
/*N*/ }

/*M*/ BOOL SwFmtCol::PutValue( const uno::Any& rVal, BYTE nMemberId )
/*M*/ {
/*M*/ 	// hier wird immer konvertiert!
/*M*/ 	nMemberId &= ~CONVERT_TWIPS;
/*M*/ 	sal_Bool bRet = sal_False;
/*M*/ 	if(MID_COLUMN_SEPARATOR_LINE == nMemberId)
/*M*/ 	{
/*M*/ 		DBG_ERROR("not implemented")
/*M*/ 	}
/*M*/ 	else
/*M*/ 	{
/*M*/         uno::Reference< text::XTextColumns > xCols;
/*M*/         rVal >>= xCols;
/*M*/         if(xCols.is())
/*M*/ 		{
/*M*/             uno::Sequence<text::TextColumn> aSetColumns = xCols->getColumns();
/*M*/ 			const text::TextColumn* pArray = aSetColumns.getConstArray();
/*M*/ 			aColumns.DeleteAndDestroy(0, aColumns.Count());
/*M*/ 			//max. Count ist hier 64K - das kann das Array aber nicht
/*M*/ 			sal_uInt16 nCount = Min( (sal_uInt16)aSetColumns.getLength(),
/*M*/ 									 (sal_uInt16) 0x3fff );
/*M*/ 			sal_uInt16 nWidthSum = 0;
/*M*/             // #101224# one column is no column
/*M*/             //
/*M*/             if(nCount > 1)
/*M*/                 for(sal_uInt16 i = 0; i < nCount; i++)
/*M*/                 {
/*M*/                     SwColumn* pCol = new SwColumn;
/*M*/                     pCol->SetWishWidth( pArray[i].Width );
/*M*/                     nWidthSum += pArray[i].Width;
/*M*/                     pCol->SetLeft ( MM100_TO_TWIP(pArray[i].LeftMargin) );
/*M*/                     pCol->SetRight( MM100_TO_TWIP(pArray[i].RightMargin) );
/*M*/                     aColumns.Insert(pCol, i);
/*M*/                 }
/*M*/ 			bRet = sal_True;
/*M*/ 			nWidth = nWidthSum;
/*M*/             bOrtho = sal_False;
/*M*/ 
/*M*/             uno::Reference<lang::XUnoTunnel> xNumTunnel(xCols, uno::UNO_QUERY);
/*M*/ 			SwXTextColumns* pSwColums = 0;
/*M*/ 			if(xNumTunnel.is())
/*M*/ 			{
/*M*/ 				pSwColums = (SwXTextColumns*)
/*M*/ 					xNumTunnel->getSomething( SwXTextColumns::getUnoTunnelId() );
/*M*/ 			}
/*M*/ 			if(pSwColums)
/*M*/ 			{
/*M*/                 bOrtho = pSwColums->IsAutomaticWidth();
/*M*/                 nLineWidth = pSwColums->GetSepLineWidth();
/*M*/ 				aLineColor.SetColor(pSwColums->GetSepLineColor());
/*M*/ 				nLineHeight = pSwColums->GetSepLineHeightRelative();
/*M*/ 				if(!pSwColums->GetSepLineIsOn())
/*M*/ 					eAdj = COLADJ_NONE;
/*M*/ 				else switch(pSwColums->GetSepLineVertAlign())
/*M*/ 				{
/*M*/ 					case 0: eAdj = COLADJ_TOP;	break;	//VerticalAlignment_TOP
/*M*/ 					case 1: eAdj = COLADJ_CENTER;break; //VerticalAlignment_MIDDLE
/*M*/ 					case 2: eAdj = COLADJ_BOTTOM;break;	//VerticalAlignment_BOTTOM
/*M*/ 				}
/*M*/ 			}
/*M*/ 		}
/*M*/ 	}
/*M*/ 	return bRet;
/*M*/ }


//	class SwFmtSurround
//	Implementierung teilweise inline im hxx

/*N*/ SwFmtSurround::SwFmtSurround( SwSurround eFly ) :
/*N*/ 	SfxEnumItem( RES_SURROUND, sal_uInt16( eFly ) )
/*N*/ {
/*N*/ 	bAnchorOnly = bContour = bOutside = sal_False;
/*N*/ }

/*N*/ SwFmtSurround::SwFmtSurround( const SwFmtSurround &rCpy ) :
/*N*/ 	SfxEnumItem( RES_SURROUND, rCpy.GetValue() )
/*N*/ {
/*N*/ 	bAnchorOnly = rCpy.bAnchorOnly;
/*N*/ 	bContour = rCpy.bContour;
/*N*/ 	bOutside = rCpy.bOutside;
/*N*/ }

/*N*/ int  SwFmtSurround::operator==( const SfxPoolItem& rAttr ) const
/*N*/ {
/*N*/ 	ASSERT( SfxPoolItem::operator==( rAttr ), "keine gleichen Attribute" );
/*N*/ 	return ( GetValue() == ((SwFmtSurround&)rAttr).GetValue() &&
/*N*/ 			 bAnchorOnly== ((SwFmtSurround&)rAttr).bAnchorOnly &&
/*N*/ 			 bContour== ((SwFmtSurround&)rAttr).bContour &&
/*N*/ 			 bOutside== ((SwFmtSurround&)rAttr).bOutside );
/*N*/ }

/*N*/ SfxPoolItem*  SwFmtSurround::Clone( SfxItemPool* ) const
/*N*/ {
/*N*/ 	return new SwFmtSurround( *this );
/*N*/ }

//STRIP001 sal_uInt16  SwFmtSurround::GetValueCount() const
//STRIP001 {
//STRIP001 	return SURROUND_END - SURROUND_BEGIN;
//STRIP001 }


/*N*/ BOOL SwFmtSurround::QueryValue( uno::Any& rVal, BYTE nMemberId ) const
/*N*/ {
/*N*/ 	// hier wird immer konvertiert!
/*N*/ 	nMemberId &= ~CONVERT_TWIPS;
/*N*/ 	sal_Bool bRet = sal_True;
/*N*/ 	switch ( nMemberId )
/*N*/ 	{
/*N*/ 		case MID_SURROUND_SURROUNDTYPE:
/*N*/ 				rVal <<= (text::WrapTextMode)GetSurround();
/*N*/ 		break;
/*N*/ 		case MID_SURROUND_ANCHORONLY:
/*N*/ 		{
/*N*/ 			BOOL bTmp = IsAnchorOnly();
/*N*/ 			rVal.setValue(&bTmp, ::getBooleanCppuType());
/*N*/ 		}
/*N*/ 				break;
/*N*/ 		case MID_SURROUND_CONTOUR:
/*N*/ 		{
/*N*/ 			BOOL bTmp = IsContour();
/*N*/ 			rVal.setValue(&bTmp, ::getBooleanCppuType());
/*N*/ 		}
/*N*/ 				break;
/*N*/ 		case MID_SURROUND_CONTOUROUTSIDE:
/*N*/ 		{
/*N*/ 			BOOL bTmp = IsOutside();
/*N*/ 			rVal.setValue(&bTmp, ::getBooleanCppuType());
/*N*/ 		}
/*N*/ 				break;
/*N*/ 		default:
/*?*/ 			ASSERT( !this, "unknown MemberId" );
/*?*/ 			bRet = sal_False;
/*N*/ 	}
/*N*/ 	return bRet;
/*N*/ }

/*N*/ BOOL SwFmtSurround::PutValue( const uno::Any& rVal, BYTE nMemberId )
/*N*/ {
/*N*/ 	// hier wird immer konvertiert!
/*N*/ 	nMemberId &= ~CONVERT_TWIPS;
/*N*/ 	sal_Bool bRet = sal_True;
/*N*/ 	switch ( nMemberId )
/*N*/ 	{
/*N*/ 		case MID_SURROUND_SURROUNDTYPE:
/*N*/ 		{
/*N*/ 			sal_Int32 eVal = SWUnoHelper::GetEnumAsInt32( rVal );
/*N*/ 			if( eVal >= 0 && eVal < (sal_Int16)SURROUND_END )
/*N*/ 				SetValue( eVal );
/*N*/ 			else
/*N*/ 				//exception
/*N*/ 				;
/*N*/ 		}
/*N*/ 		break;
/*N*/ 
/*N*/ 		case MID_SURROUND_ANCHORONLY:
/*N*/ 			SetAnchorOnly( *(sal_Bool*)rVal.getValue() );
/*N*/ 			break;
/*N*/ 		case MID_SURROUND_CONTOUR:
/*N*/ 			SetContour( *(sal_Bool*)rVal.getValue() );
/*N*/ 			break;
/*N*/ 		case MID_SURROUND_CONTOUROUTSIDE:
/*N*/ 			SetOutside( *(sal_Bool*)rVal.getValue() );
/*N*/ 			break;
/*N*/ 		default:
/*?*/ 			ASSERT( !this, "unknown MemberId" );
/*?*/ 			bRet = sal_False;
/*N*/ 	}
/*N*/ 	return bRet;
/*N*/ }

//	class SwFmtVertOrient
//	Implementierung teilweise inline im hxx

/*N*/ SwFmtVertOrient::SwFmtVertOrient( SwTwips nY, SwVertOrient eVert,
/*N*/ 								  SwRelationOrient eRel )
/*N*/ 	: SfxPoolItem( RES_VERT_ORIENT ),
/*N*/ 	nYPos( nY ),
/*N*/ 	eOrient( eVert ),
/*N*/ 	eRelation( eRel )
/*N*/ {}

/*N*/ int  SwFmtVertOrient::operator==( const SfxPoolItem& rAttr ) const
/*N*/ {
/*N*/ 	ASSERT( SfxPoolItem::operator==( rAttr ), "keine gleichen Attribute" );
/*N*/ 	return ( nYPos     == ((SwFmtVertOrient&)rAttr).nYPos &&
/*N*/ 			 eOrient   == ((SwFmtVertOrient&)rAttr).eOrient &&
/*N*/ 			 eRelation == ((SwFmtVertOrient&)rAttr).eRelation );
/*N*/ }

/*N*/ SfxPoolItem*  SwFmtVertOrient::Clone( SfxItemPool* ) const
/*N*/ {
/*N*/ 	return new SwFmtVertOrient( nYPos, eOrient, eRelation );
/*N*/ }


/*N*/ SwTwips  SwFmtVertOrient::GetPosConvertedToSw31(
/*N*/ 	const SvxULSpaceItem *pULSpace ) const
/*N*/ {
/*N*/ 	SwTwips nNewPos = GetPos();
/*N*/ 
/*N*/ 	if( VERT_NONE==GetVertOrient() && pULSpace )
/*N*/ 	{
/*N*/ 		nNewPos -= pULSpace->GetUpper();
/*N*/ 	}
/*N*/ 
/*N*/ 	return nNewPos;
/*N*/ }

/*N*/ SwTwips  SwFmtVertOrient::GetPosConvertedFromSw31(
/*N*/ 	const SvxULSpaceItem *pULSpace ) const
/*N*/ {
/*N*/ 	SwTwips nNewPos = GetPos();
/*N*/ 
/*N*/ 	if( VERT_NONE==GetVertOrient() && pULSpace )
/*N*/ 	{
/*N*/ 		nNewPos += pULSpace->GetUpper();
/*N*/ 	}
/*N*/ 
/*N*/ 	return nNewPos;
/*N*/ }


/*N*/ BOOL SwFmtVertOrient::QueryValue( uno::Any& rVal, BYTE nMemberId ) const
/*N*/ {
/*N*/ 	// hier wird immer konvertiert!
/*N*/ 	nMemberId &= ~CONVERT_TWIPS;
/*N*/ 	sal_Bool bRet = sal_True;
/*N*/ 	switch ( nMemberId )
/*N*/ 	{
/*N*/ 		case MID_VERTORIENT_ORIENT:
/*N*/ 		{
/*N*/ 			sal_Int16 nRet = text::VertOrientation::NONE;
/*N*/ 			switch( eOrient )
/*N*/ 			{
/*N*/ 				case VERT_TOP		 :	nRet = text::VertOrientation::TOP		 ;break;
/*N*/ 				case VERT_CENTER     : 	nRet = text::VertOrientation::CENTER     ;break;
/*N*/ 				case VERT_BOTTOM     : 	nRet = text::VertOrientation::BOTTOM     ;break;
/*?*/ 				case VERT_CHAR_TOP   : 	nRet = text::VertOrientation::CHAR_TOP   ;break;
/*N*/ 				case VERT_CHAR_CENTER: 	nRet = text::VertOrientation::CHAR_CENTER;break;
/*?*/ 				case VERT_CHAR_BOTTOM: 	nRet = text::VertOrientation::CHAR_BOTTOM;break;
/*N*/ 				case VERT_LINE_TOP	 : 	nRet = text::VertOrientation::LINE_TOP   ;break;
/*N*/ 				case VERT_LINE_CENTER: 	nRet = text::VertOrientation::LINE_CENTER;break;
/*?*/ 				case VERT_LINE_BOTTOM: 	nRet = text::VertOrientation::LINE_BOTTOM;break;
/*N*/ 			}
/*N*/ 			rVal <<= nRet;
/*N*/ 		}
/*N*/ 		break;
/*N*/ 		case MID_VERTORIENT_RELATION:
/*N*/ 				rVal <<= lcl_RelToINT(eRelation);
/*N*/ 		break;
/*N*/ 		case MID_VERTORIENT_POSITION:
/*N*/ 				rVal <<= (sal_Int32)TWIP_TO_MM100(GetPos());
/*N*/ 				break;
/*N*/ 		default:
/*?*/ 			ASSERT( !this, "unknown MemberId" );
/*?*/ 			bRet = sal_False;
/*N*/ 	}
/*N*/ 	return bRet;
/*N*/ }

/*N*/ BOOL SwFmtVertOrient::PutValue( const uno::Any& rVal, BYTE nMemberId )
/*N*/ {
/*N*/ 	sal_Bool bConvert = 0 != (nMemberId&CONVERT_TWIPS);
/*N*/ 	nMemberId &= ~CONVERT_TWIPS;
/*N*/ 	sal_Bool bRet = sal_True;
/*N*/ 	switch ( nMemberId )
/*N*/ 	{
/*N*/ 		case MID_VERTORIENT_ORIENT:
/*N*/ 		{
/*N*/ 			sal_uInt16 nVal;
/*N*/ 			rVal >>= nVal;
/*N*/ 			switch( nVal )
/*N*/ 			{
/*N*/ 				case text::VertOrientation::NONE:			eOrient = VERT_NONE;	break;
/*N*/ 				case text::VertOrientation::TOP		   :	eOrient = VERT_TOP;		break;
/*N*/ 				case text::VertOrientation::CENTER     : 	eOrient = VERT_CENTER;     break;
/*N*/ 				case text::VertOrientation::BOTTOM     : 	eOrient = VERT_BOTTOM;     break;
/*?*/ 				case text::VertOrientation::CHAR_TOP   : 	eOrient = VERT_CHAR_TOP;   break;
/*N*/ 				case text::VertOrientation::CHAR_CENTER: 	eOrient = VERT_CHAR_CENTER;break;
/*?*/ 				case text::VertOrientation::CHAR_BOTTOM:  	eOrient = VERT_CHAR_BOTTOM;break;
/*N*/ 				case text::VertOrientation::LINE_TOP   :  	eOrient = VERT_LINE_TOP;	break;
/*N*/ 				case text::VertOrientation::LINE_CENTER:  	eOrient = VERT_LINE_CENTER;break;
/*?*/ 				case text::VertOrientation::LINE_BOTTOM:  	eOrient = VERT_LINE_BOTTOM;break;
/*N*/ 			}
/*N*/ 		}
/*N*/ 		break;
/*N*/ 		case MID_VERTORIENT_RELATION:
/*N*/ 		{
/*N*/ 			eRelation = lcl_IntToRelation(rVal);
/*N*/ 		}
/*N*/ 		break;
/*N*/ 		case MID_VERTORIENT_POSITION:
/*N*/ 		{
/*N*/ 			sal_Int32 nVal;
/*N*/ 			rVal >>= nVal;
/*N*/ 			if(bConvert)
/*N*/ 				nVal = MM100_TO_TWIP(nVal);
/*N*/ 			SetPos( nVal );
/*N*/ 		}
/*N*/ 		break;
/*N*/ 		default:
/*?*/ 			ASSERT( !this, "unknown MemberId" );
/*?*/ 			bRet = sal_False;
/*N*/ 	}
/*N*/ 	return bRet;
/*N*/ }



//	class SwFmtHoriOrient
//	Implementierung teilweise inline im hxx

/*N*/ SwFmtHoriOrient::SwFmtHoriOrient( SwTwips nX, SwHoriOrient eHori,
/*N*/ 							  SwRelationOrient eRel, sal_Bool bPos )
/*N*/ 	: SfxPoolItem( RES_HORI_ORIENT ),
/*N*/ 	nXPos( nX ),
/*N*/ 	eOrient( eHori ),
/*N*/ 	eRelation( eRel ),
/*N*/ 	bPosToggle( bPos )
/*N*/ {}

/*N*/ int  SwFmtHoriOrient::operator==( const SfxPoolItem& rAttr ) const
/*N*/ {
/*N*/ 	ASSERT( SfxPoolItem::operator==( rAttr ), "keine gleichen Attribute" );
/*N*/ 	return ( nXPos == ((SwFmtHoriOrient&)rAttr).nXPos &&
/*N*/ 			 eOrient == ((SwFmtHoriOrient&)rAttr).eOrient &&
/*N*/ 			 eRelation == ((SwFmtHoriOrient&)rAttr).eRelation &&
/*N*/ 			 bPosToggle == ((SwFmtHoriOrient&)rAttr).bPosToggle );
/*N*/ }

/*N*/ SfxPoolItem*  SwFmtHoriOrient::Clone( SfxItemPool* ) const
/*N*/ {
/*N*/ 	return new SwFmtHoriOrient( nXPos, eOrient, eRelation, bPosToggle );
/*N*/ }


/*N*/ SwTwips  SwFmtHoriOrient::GetPosConvertedToSw31(
/*N*/ 	const SvxLRSpaceItem *pLRSpace ) const
/*N*/ {
/*N*/ 	SwTwips nNewPos = GetPos();
/*N*/ 
/*N*/ 	if( HORI_NONE==GetHoriOrient() && pLRSpace )
/*N*/ 	{
/*N*/ 		nNewPos -= pLRSpace->GetLeft();
/*N*/ 	}
/*N*/ 
/*N*/ 	return nNewPos;
/*N*/ }

/*N*/ SwTwips  SwFmtHoriOrient::GetPosConvertedFromSw31(
/*N*/ 	const SvxLRSpaceItem *pLRSpace ) const
/*N*/ {
/*N*/ 	SwTwips nNewPos = GetPos();
/*N*/ 
/*N*/ 	if( HORI_NONE==GetHoriOrient() && pLRSpace )
/*N*/ 	{
/*N*/ 		nNewPos += pLRSpace->GetLeft();
/*N*/ 	}
/*N*/ 
/*N*/ 	return nNewPos;
/*N*/ }

/*N*/ BOOL SwFmtHoriOrient::QueryValue( uno::Any& rVal, BYTE nMemberId ) const
/*N*/ {
/*N*/ 	// hier wird immer konvertiert!
/*N*/ 	nMemberId &= ~CONVERT_TWIPS;
/*N*/ 	sal_Bool bRet = sal_True;
/*N*/ 	switch ( nMemberId )
/*N*/ 	{
/*N*/ 		case MID_HORIORIENT_ORIENT:
/*N*/ 		{
/*N*/ 			sal_Int16 nRet = text::HoriOrientation::NONE;
/*N*/ 			switch( eOrient )
/*N*/ 			{
/*N*/ 				case HORI_RIGHT:	nRet = text::HoriOrientation::RIGHT; break;
/*N*/ 				case HORI_CENTER : 	nRet = text::HoriOrientation::CENTER; break;
/*N*/ 				case HORI_LEFT   : 	nRet = text::HoriOrientation::LEFT; break;
/*?*/ 				case HORI_INSIDE : 	nRet = text::HoriOrientation::INSIDE; break;
/*?*/ 				case HORI_OUTSIDE: 	nRet = text::HoriOrientation::OUTSIDE; break;
/*?*/ 				case HORI_FULL:    	nRet = text::HoriOrientation::FULL; break;
/*?*/ 				case HORI_LEFT_AND_WIDTH :
/*?*/ 					nRet = text::HoriOrientation::LEFT_AND_WIDTH;
/*N*/ 				break;
/*N*/ 			}
/*N*/ 			rVal <<= nRet;
/*N*/ 		}
/*N*/ 		break;
/*N*/ 		case MID_HORIORIENT_RELATION:
/*N*/ 			rVal <<= lcl_RelToINT(eRelation);
/*N*/ 		break;
/*N*/ 		case MID_HORIORIENT_POSITION:
/*N*/ 				rVal <<= (sal_Int32)TWIP_TO_MM100(GetPos());
/*N*/ 				break;
/*N*/ 		case MID_HORIORIENT_PAGETOGGLE:
/*N*/ 		{
/*N*/ 			BOOL bTmp = IsPosToggle();
/*N*/ 			rVal.setValue(&bTmp, ::getBooleanCppuType());
/*N*/ 		}
/*N*/ 				break;
/*N*/ 		default:
/*?*/ 			ASSERT( !this, "unknown MemberId" );
/*?*/ 			bRet = sal_False;
/*N*/ 	}
/*N*/ 	return bRet;
/*N*/ }

/*N*/ BOOL SwFmtHoriOrient::PutValue( const uno::Any& rVal, BYTE nMemberId )
/*N*/ {
/*N*/ 	sal_Bool bConvert = 0 != (nMemberId&CONVERT_TWIPS);
/*N*/ 	nMemberId &= ~CONVERT_TWIPS;
/*N*/ 	sal_Bool bRet = sal_True;
/*N*/ 	switch ( nMemberId )
/*N*/ 	{
/*N*/ 		case MID_HORIORIENT_ORIENT:
/*N*/ 		{
/*N*/             sal_Int16 nVal;
/*N*/             rVal >>= nVal;
/*N*/             switch( nVal )
/*N*/ 			{
/*N*/ 				case text::HoriOrientation::NONE:   	eOrient = HORI_NONE ;	break;
/*N*/ 				case text::HoriOrientation::RIGHT: 	eOrient = HORI_RIGHT; 	break;
/*N*/ 				case text::HoriOrientation::CENTER : 	eOrient = HORI_CENTER;	break;
/*N*/ 				case text::HoriOrientation::LEFT   : 	eOrient = HORI_LEFT;  	break;
/*?*/ 				case text::HoriOrientation::INSIDE : 	eOrient = HORI_INSIDE;	break;
/*?*/ 				case text::HoriOrientation::OUTSIDE: 	eOrient = HORI_OUTSIDE;	break;
/*?*/ 				case text::HoriOrientation::FULL:      eOrient = HORI_FULL; 	break;
/*?*/ 				case text::HoriOrientation::LEFT_AND_WIDTH:
/*?*/ 					eOrient = HORI_LEFT_AND_WIDTH;
/*N*/ 				break;
/*N*/ 			}
/*N*/ 		}
/*N*/ 		break;
/*N*/ 		case MID_HORIORIENT_RELATION:
/*N*/ 		{
/*N*/ 			eRelation = lcl_IntToRelation(rVal);
/*N*/ 		}
/*N*/ 		break;
/*N*/ 		case MID_HORIORIENT_POSITION:
/*N*/ 		{
/*N*/             sal_Int32 nVal;
/*N*/             if(!(rVal >>= nVal))
/*?*/                 bRet = sal_False;
/*N*/ 			if(bConvert)
/*N*/ 				nVal = MM100_TO_TWIP(nVal);
/*N*/ 			SetPos( nVal );
/*N*/ 		}
/*N*/ 		break;
/*N*/ 		case MID_HORIORIENT_PAGETOGGLE:
/*N*/ 				SetPosToggle( *(sal_Bool*)rVal.getValue());
/*N*/ 			break;
/*N*/ 		default:
/*?*/ 			ASSERT( !this, "unknown MemberId" );
/*?*/ 			bRet = sal_False;
/*N*/ 	}
/*N*/ 	return bRet;
/*N*/ }



//	class SwFmtAnchor
//	Implementierung teilweise inline im hxx

/*N*/ SwFmtAnchor::SwFmtAnchor( RndStdIds nRnd, sal_uInt16 nPage )
/*N*/ 	: SfxPoolItem( RES_ANCHOR ),
/*N*/ 	pCntntAnchor( 0 ),
/*N*/ 	nAnchorId( nRnd ),
/*N*/ 	nPageNum( nPage )
/*N*/ {}

/*N*/ SwFmtAnchor::SwFmtAnchor( const SwFmtAnchor &rCpy )
/*N*/ 	: SfxPoolItem( RES_ANCHOR ),
/*N*/ 	nAnchorId( rCpy.GetAnchorId() ),
/*N*/ 	nPageNum( rCpy.GetPageNum() )
/*N*/ {
/*N*/ 	pCntntAnchor = rCpy.GetCntntAnchor() ?
/*N*/ 						new SwPosition( *rCpy.GetCntntAnchor() ) : 0;
/*N*/ }

/*N*/  SwFmtAnchor::~SwFmtAnchor()
/*N*/ {
/*N*/ 	delete pCntntAnchor;
/*N*/ }

/*N*/ void SwFmtAnchor::SetAnchor( const SwPosition *pPos )
/*N*/ {
/*N*/ 	if ( pCntntAnchor )
/*N*/ 		delete pCntntAnchor;
/*N*/ 	pCntntAnchor = pPos ? new SwPosition( *pPos ) : 0;
/*N*/ 		//AM Absatz gebundene Flys sollten nie in den Absatz hineinzeigen.
/*N*/ 	if ( pCntntAnchor && ( FLY_AT_CNTNT == nAnchorId ||
/*N*/ 						   FLY_AT_FLY == nAnchorId ))
/*N*/ 		pCntntAnchor->nContent.Assign( 0, 0 );
/*N*/ }

/*N*/ SwFmtAnchor& SwFmtAnchor::operator=(const SwFmtAnchor& rAnchor)
/*N*/ {
/*N*/ 	nAnchorId  = rAnchor.GetAnchorId();
/*N*/ 	nPageNum   = rAnchor.GetPageNum();
/*N*/ 
/*N*/ 	delete pCntntAnchor;
/*N*/ 	pCntntAnchor = rAnchor.pCntntAnchor ?
/*N*/ 									new SwPosition(*(rAnchor.pCntntAnchor)) : 0;
/*N*/ 	return *this;
/*N*/ }

/*N*/ int  SwFmtAnchor::operator==( const SfxPoolItem& rAttr ) const
/*N*/ {
/*N*/ 	ASSERT( SfxPoolItem::operator==( rAttr ), "keine gleichen Attribute" );
/*N*/ 	return ( nAnchorId == ((SwFmtAnchor&)rAttr).GetAnchorId() &&
/*N*/ 			 nPageNum == ((SwFmtAnchor&)rAttr).GetPageNum()   &&
/*N*/ 					//Anker vergleichen. Entweder zeigen beide auf das gleiche
/*N*/ 					//Attribut bzw. sind 0 oder die SwPosition* sind beide
/*N*/ 					//gueltig und die SwPositions sind gleich.
/*N*/ 			 (pCntntAnchor == ((SwFmtAnchor&)rAttr).GetCntntAnchor() ||
/*N*/ 			  (pCntntAnchor && ((SwFmtAnchor&)rAttr).GetCntntAnchor() &&
/*N*/ 			   *pCntntAnchor == *((SwFmtAnchor&)rAttr).GetCntntAnchor())));
/*N*/ }

/*N*/ SfxPoolItem*  SwFmtAnchor::Clone( SfxItemPool* ) const
/*N*/ {
/*N*/ 	return new SwFmtAnchor( *this );
/*N*/ }

/*-----------------16.02.98 15:21-------------------

--------------------------------------------------*/
/*N*/ BOOL SwFmtAnchor::QueryValue( uno::Any& rVal, BYTE nMemberId ) const
/*N*/ {
/*N*/ 	// hier wird immer konvertiert!
/*N*/ 	nMemberId &= ~CONVERT_TWIPS;
/*N*/ 	sal_Bool bRet = sal_True;
/*N*/ 	switch ( nMemberId )
/*N*/ 	{
/*N*/ 		case MID_ANCHOR_ANCHORTYPE:
/*N*/ 
/*N*/ 			text::TextContentAnchorType eRet;
/*N*/ 			switch((sal_Int16)GetAnchorId())
/*N*/ 			{
/*?*/ 				case  FLY_AUTO_CNTNT : eRet = text::TextContentAnchorType_AT_CHARACTER;break;
/*N*/ 				case  FLY_PAGE    	 : eRet = text::TextContentAnchorType_AT_PAGE;		break;
/*?*/ 				case  FLY_AT_FLY     : eRet = text::TextContentAnchorType_AT_FRAME;    break;
/*N*/ 				case  FLY_IN_CNTNT   : eRet = text::TextContentAnchorType_AS_CHARACTER;break;
/*N*/ 				//case  FLY_AT_CNTNT  :
/*N*/ 				default: eRet = text::TextContentAnchorType_AT_PARAGRAPH;
/*N*/ 			}
/*N*/ 			rVal <<= eRet;
/*N*/ 		break;
/*N*/ 		case MID_ANCHOR_PAGENUM:
/*N*/ 			rVal <<= (sal_Int16)GetPageNum();
/*N*/         break;
/*N*/         case MID_ANCHOR_ANCHORFRAME:
/*N*/         {
/*?*/             if(pCntntAnchor && FLY_AT_FLY == nAnchorId)
/*?*/             {
/*?*/                 SwFrmFmt* pFmt = pCntntAnchor->nNode.GetNode().GetFlyFmt();
/*?*/                 if(pFmt)
/*?*/                 {
/*?*/                     Reference<XNamed> xNamed = SwXFrames::GetObject( *pFmt, FLYCNTTYPE_FRM );
/*?*/                     Reference<XTextFrame> xRet(xNamed, UNO_QUERY);
/*?*/                     rVal <<= xRet;
/*?*/                 }
/*?*/             }
/*?*/         }
/*?*/         break;
/*?*/         default:
/*?*/ 			ASSERT( !this, "unknown MemberId" );
/*?*/ 			bRet = sal_False;
/*N*/ 	}
/*N*/ 	return bRet;
/*N*/ }

/*N*/ BOOL SwFmtAnchor::PutValue( const uno::Any& rVal, BYTE nMemberId )
/*N*/ {
/*N*/ 	// hier wird immer konvertiert!
/*N*/ 	nMemberId &= ~CONVERT_TWIPS;
/*N*/ 	sal_Bool bRet = sal_True;
/*N*/ 	switch ( nMemberId )
/*N*/ 	{
/*N*/ 		case MID_ANCHOR_ANCHORTYPE:
/*N*/ 		{
/*N*/ 			RndStdIds	eAnchor;
/*N*/ 			switch( SWUnoHelper::GetEnumAsInt32( rVal ) )
/*N*/ 			{
/*N*/ 				case  text::TextContentAnchorType_AS_CHARACTER:
/*N*/ 					eAnchor = FLY_IN_CNTNT;
/*N*/ 					break;
/*N*/ 				case  text::TextContentAnchorType_AT_PAGE:
/*N*/ 					eAnchor = FLY_PAGE;
/*N*/ 					if( GetPageNum() > 0 && pCntntAnchor )
/*N*/ 					{
/*?*/ 						// If the anchor type is page and a valid page number
/*?*/ 						// has been set, the content position isn't required
/*?*/ 						// any longer.
/*?*/ 						delete pCntntAnchor;
/*?*/ 						pCntntAnchor = 0;
/*N*/ 					}
/*N*/ 					break;
/*N*/ 				case  text::TextContentAnchorType_AT_FRAME:
/*?*/ 					eAnchor = FLY_AT_FLY;
/*?*/ 					break;
/*?*/ 				case  text::TextContentAnchorType_AT_CHARACTER:
/*?*/ 					eAnchor = FLY_AUTO_CNTNT;
/*?*/ 					break;
/*N*/ 				//case  text::TextContentAnchorType_AT_PARAGRAPH:
/*N*/ 				default:
/*N*/ 					eAnchor = FLY_AT_CNTNT;
/*N*/ 					break;
/*N*/ 			}
/*N*/ 			SetType( eAnchor );
/*N*/ 		}
/*N*/ 		break;
/*N*/ 		case MID_ANCHOR_PAGENUM:
/*N*/ 		{
/*N*/             sal_Int16 nVal;
/*N*/             if((rVal >>= nVal) && nVal > 0)
/*N*/ 			{
/*N*/ 				SetPageNum( nVal );
/*N*/ 				if( FLY_PAGE == GetAnchorId() && pCntntAnchor )
/*N*/ 				{
/*N*/ 					// If the anchor type is page and a valid page number
/*N*/ 					// is set, the content paoition has to be deleted to not
/*N*/ 					// confuse the layout (frmtool.cxx). However, if the
/*N*/ 					// anchor type is not page, any content position will
/*N*/ 					// be kept.
/*N*/ 					delete pCntntAnchor;
/*N*/ 					pCntntAnchor = 0;
/*N*/ 				}
/*N*/ 			}
/*N*/ 			else
/*?*/ 				bRet = sal_False;
/*N*/ 		}
/*N*/ 		break;
/*N*/         case MID_ANCHOR_ANCHORFRAME:
/*N*/         //no break here!;
/*N*/ 		default:
/*?*/ 			ASSERT( !this, "unknown MemberId" );
/*?*/ 			bRet = sal_False;
/*N*/ 	}
/*N*/ 	return bRet;
/*N*/ }

//	class SwFmtURL
//	Implementierung teilweise inline im hxx

/*N*/ SwFmtURL::SwFmtURL() :
/*N*/ 	SfxPoolItem( RES_URL ),
/*N*/ 	pMap( 0 ),
/*N*/ 	bIsServerMap( sal_False )
/*N*/ {
/*N*/ }

/*N*/ SwFmtURL::SwFmtURL( const SwFmtURL &rURL) :
/*N*/ 	SfxPoolItem( RES_URL ),
/*N*/ 	sURL( rURL.GetURL() ),
/*N*/ 	sTargetFrameName( rURL.GetTargetFrameName() ),
/*N*/ 	sName( rURL.GetName() ),
/*N*/ 	bIsServerMap( rURL.IsServerMap() )
/*N*/ {
/*N*/ 	pMap = rURL.GetMap() ? new ImageMap( *rURL.GetMap() ) : 0;
/*N*/ }

/*N*/ SwFmtURL::~SwFmtURL()
/*N*/ {
/*N*/ 	if ( pMap )
/*?*/ 		delete pMap;
/*N*/ }

/*N*/ int SwFmtURL::operator==( const SfxPoolItem &rAttr ) const
/*N*/ {
/*N*/ 	ASSERT( SfxPoolItem::operator==( rAttr ), "keine gleichen Attribute" );
/*N*/ 	const SwFmtURL &rCmp = (SwFmtURL&)rAttr;
/*N*/ 	sal_Bool bRet = bIsServerMap  	 == rCmp.IsServerMap() &&
/*N*/ 				sURL			 == rCmp.GetURL() &&
/*N*/ 				sTargetFrameName == rCmp.GetTargetFrameName() &&
/*N*/ 				sName 			 == rCmp.GetName();
/*N*/ 	if ( bRet )
/*N*/ 	{
/*N*/ 		if ( pMap && rCmp.GetMap() )
/*?*/ 			bRet = *pMap == *rCmp.GetMap();
/*N*/ 		else
/*N*/ 			bRet = pMap == rCmp.GetMap();
/*N*/ 	}
/*N*/ 	return bRet;
/*N*/ }

/*N*/ SfxPoolItem* SwFmtURL::Clone( SfxItemPool* pPool ) const
/*N*/ {
/*N*/ 	return new SwFmtURL( *this );
/*N*/ }

/*N*/ void SwFmtURL::SetURL( const XubString &rURL, sal_Bool bServerMap )
/*N*/ {
/*N*/ 	sURL = rURL;
/*N*/ 	bIsServerMap = bServerMap;
/*N*/ }

/*N*/ void SwFmtURL::SetMap( const ImageMap *pM )
/*N*/ {
/*N*/ 	if ( pMap )
/*?*/ 		delete pMap;
/*N*/ 	pMap = pM ? new ImageMap( *pM ) : 0;
/*N*/ }
/*N*/ extern const SvEventDescription* lcl_GetSupportedMacroItems();

/*N*/ BOOL SwFmtURL::QueryValue( uno::Any& rVal, BYTE nMemberId ) const
/*N*/ {
/*N*/ 	// hier wird immer konvertiert!
/*N*/ 	nMemberId &= ~CONVERT_TWIPS;
/*N*/ 	sal_Bool bRet = sal_True;
/*N*/ 	switch ( nMemberId )
/*N*/ 	{
/*N*/ 		case MID_URL_URL:
/*N*/ 		{
/*N*/ 			OUString sRet = GetURL();
/*N*/ 			rVal <<= sRet;
/*N*/ 		}
/*N*/ 		break;
/*N*/ 		case MID_URL_TARGET:
/*N*/ 		{
/*N*/ 			OUString sRet = GetTargetFrameName();
/*N*/ 			rVal <<= sRet;
/*N*/ 		}
/*N*/ 		break;
/*N*/ 		case MID_URL_HYPERLINKNAME:
/*N*/ 			rVal <<= OUString( GetName() );
/*N*/ 			break;
/*N*/ 		case MID_URL_CLIENTMAP:
/*N*/         {
/*N*/             Reference< XInterface > xInt;
/*N*/             if(pMap)
/*N*/             {
/*?*/                 xInt = SvUnoImageMap_createInstance( *pMap, lcl_GetSupportedMacroItems() );
/*N*/             }
/*N*/             else
/*N*/             {
/*N*/                 ImageMap aEmptyMap;
/*N*/                 xInt = SvUnoImageMap_createInstance( aEmptyMap, lcl_GetSupportedMacroItems() );
/*N*/             }
/*N*/             Reference< XIndexContainer > xCont(xInt, UNO_QUERY);
/*N*/             rVal <<= xCont;
/*N*/         }
/*N*/         break;
/*N*/ 		case MID_URL_SERVERMAP:
/*N*/ 		{
/*N*/ 			BOOL bTmp = IsServerMap();
/*N*/ 			rVal.setValue(&bTmp, ::getBooleanCppuType());
/*N*/ 		}
/*N*/ 			break;
/*N*/ 		default:
/*?*/ 			ASSERT( !this, "unknown MemberId" );
/*?*/ 			bRet = sal_False;
/*N*/ 	}
/*N*/ 	return bRet;
/*N*/ }

/*N*/ BOOL SwFmtURL::PutValue( const uno::Any& rVal, BYTE nMemberId )
/*N*/ {
/*N*/ 	// hier wird immer konvertiert!
/*N*/ 	nMemberId &= ~CONVERT_TWIPS;
/*N*/ 	sal_Bool bRet = sal_True;
/*N*/ 	switch ( nMemberId )
/*N*/ 	{
/*N*/ 		case MID_URL_URL:
/*N*/         {
/*N*/             OUString sTmp;
/*N*/             rVal >>= sTmp;
/*N*/             SetURL( sTmp, bIsServerMap );
/*N*/         }
/*N*/ 		break;
/*N*/ 		case MID_URL_TARGET:
/*N*/         {
/*N*/             OUString sTmp;
/*N*/             rVal >>= sTmp;
/*N*/             SetTargetFrameName( sTmp );
/*N*/         }
/*N*/ 		break;
/*N*/ 		case MID_URL_HYPERLINKNAME:
/*N*/         {
/*N*/             OUString sTmp;
/*N*/             rVal >>= sTmp;
/*N*/             SetName( sTmp );
/*N*/         }
/*N*/ 		break;
/*N*/ 		case MID_URL_CLIENTMAP:
/*N*/         {
/*N*/             Reference<XIndexContainer> xCont;
/*N*/             if(!rVal.hasValue())
/*N*/                 DELETEZ(pMap);
/*N*/             else if(rVal >>= xCont)
/*N*/             {
/*N*/                 if(!pMap)
/*N*/                     pMap = new ImageMap;
/*N*/                 bRet = SvUnoImageMap_fillImageMap( xCont, *pMap );
/*N*/             }
/*N*/             else
/*N*/                 bRet = FALSE;
/*N*/         }
/*N*/         break;
/*N*/ 		case MID_URL_SERVERMAP:
/*N*/ 			bIsServerMap = *(sal_Bool*)rVal.getValue();
/*N*/ 			break;
/*N*/ 		default:
/*N*/ 			ASSERT( !this, "unknown MemberId" );
/*N*/ 			bRet = sal_False;
/*N*/ 	}
/*N*/ 	return bRet;
/*N*/ }


// class SwNoReadOnly

//STRIP001 SfxPoolItem* SwFmtEditInReadonly::Clone( SfxItemPool* pPool ) const
//STRIP001 {
//STRIP001 	return new SwFmtEditInReadonly( Which(), GetValue() );
//STRIP001 }

// class SwFmtLayoutSplit

//STRIP001 SfxPoolItem* SwFmtLayoutSplit::Clone( SfxItemPool* pPool ) const
//STRIP001 {
//STRIP001 	return new SwFmtLayoutSplit( GetValue() );
//STRIP001 }

// class SwFmtNoBalancedColumns

/*N*/ SfxPoolItem* SwFmtNoBalancedColumns::Clone( SfxItemPool* pPool ) const
/*N*/ {
/*N*/ 	return new SwFmtNoBalancedColumns( GetValue() );
/*N*/ }

// class SwFmtFtnEndAtTxtEnd

//STRIP001 sal_uInt16 SwFmtFtnEndAtTxtEnd::GetValueCount() const
//STRIP001 {
//STRIP001 	return sal_uInt16( FTNEND_ATTXTEND_END );
//STRIP001 }

//STRIP001 SwFmtFtnEndAtTxtEnd& SwFmtFtnEndAtTxtEnd::operator=(
//STRIP001 						const SwFmtFtnEndAtTxtEnd& rAttr )
//STRIP001 {
//STRIP001 	SfxEnumItem::SetValue( rAttr.GetValue() );
//STRIP001 	aFmt = rAttr.aFmt;
//STRIP001 	nOffset = rAttr.nOffset;
//STRIP001 	sPrefix = rAttr.sPrefix;
//STRIP001 	sSuffix = rAttr.sSuffix;
//STRIP001 	return *this;
//STRIP001 }

//STRIP001 int SwFmtFtnEndAtTxtEnd::operator==( const SfxPoolItem& rItem ) const
//STRIP001 {
//STRIP001 	const SwFmtFtnEndAtTxtEnd& rAttr = (SwFmtFtnEndAtTxtEnd&)rItem;
//STRIP001 	return SfxEnumItem::operator==( rAttr ) &&
//STRIP001 			aFmt.GetNumberingType() == rAttr.aFmt.GetNumberingType() &&
//STRIP001 			nOffset == rAttr.nOffset &&
//STRIP001 			sPrefix == rAttr.sPrefix &&
//STRIP001 			sSuffix == rAttr.sSuffix;
//STRIP001 }

//STRIP001 BOOL SwFmtFtnEndAtTxtEnd::QueryValue( uno::Any& rVal, BYTE nMemberId ) const
//STRIP001 {
//STRIP001 	nMemberId &= ~CONVERT_TWIPS;
//STRIP001 	switch(nMemberId)
//STRIP001 	{
//STRIP001 		case MID_COLLECT	 :
//STRIP001 		{
//STRIP001 			sal_Bool bVal = GetValue() >= FTNEND_ATTXTEND;
//STRIP001 			rVal.setValue(&bVal, ::getBooleanCppuType());
//STRIP001 		}
//STRIP001 		break;
//STRIP001 		case MID_RESTART_NUM :
//STRIP001 		{
//STRIP001 			sal_Bool bVal = GetValue() >= FTNEND_ATTXTEND_OWNNUMSEQ;
//STRIP001 			rVal.setValue(&bVal, ::getBooleanCppuType());
//STRIP001 		}
//STRIP001 		break;
//STRIP001 		case MID_NUM_START_AT: rVal <<= (sal_Int16) nOffset; break;
//STRIP001 		case MID_OWN_NUM     :
//STRIP001 		{
//STRIP001 			sal_Bool bVal = GetValue() >= FTNEND_ATTXTEND_OWNNUMANDFMT;
//STRIP001 			rVal.setValue(&bVal, ::getBooleanCppuType());
//STRIP001 		}
//STRIP001 		break;
//STRIP001 		case MID_NUM_TYPE    : rVal <<= aFmt.GetNumberingType(); break;
//STRIP001 		case MID_PREFIX      : rVal <<= OUString(sPrefix); break;
//STRIP001 		case MID_SUFFIX      : rVal <<= OUString(sSuffix); break;
//STRIP001 		default: return FALSE;
//STRIP001 	}
//STRIP001 	return TRUE;
//STRIP001 }

//STRIP001 BOOL SwFmtFtnEndAtTxtEnd::PutValue( const uno::Any& rVal, BYTE nMemberId )
//STRIP001 {
//STRIP001 	BOOL bRet = TRUE;
//STRIP001 	nMemberId &= ~CONVERT_TWIPS;
//STRIP001 	switch(nMemberId)
//STRIP001 	{
//STRIP001 		case MID_COLLECT	 :
//STRIP001 		{
//STRIP001 			sal_Bool bVal = *(sal_Bool*)rVal.getValue();
//STRIP001 			if(!bVal && GetValue() >= FTNEND_ATTXTEND)
//STRIP001 				SetValue(FTNEND_ATPGORDOCEND);
//STRIP001 			else if(bVal && GetValue() < FTNEND_ATTXTEND)
//STRIP001 				SetValue(FTNEND_ATTXTEND);
//STRIP001 		}
//STRIP001 		break;
//STRIP001 		case MID_RESTART_NUM :
//STRIP001 		{
//STRIP001 			sal_Bool bVal = *(sal_Bool*)rVal.getValue();
//STRIP001 			if(!bVal && GetValue() >= FTNEND_ATTXTEND_OWNNUMSEQ)
//STRIP001 				SetValue(FTNEND_ATTXTEND);
//STRIP001 			else if(bVal && GetValue() < FTNEND_ATTXTEND_OWNNUMSEQ)
//STRIP001 				SetValue(FTNEND_ATTXTEND_OWNNUMSEQ);
//STRIP001 		}
//STRIP001 		break;
//STRIP001 		case MID_NUM_START_AT:
//STRIP001 		{
//STRIP001 			sal_Int16 nVal;
//STRIP001 			rVal >>= nVal;
//STRIP001 			if(nVal >= 0)
//STRIP001 				nOffset = nVal;
//STRIP001 			else
//STRIP001 				bRet = FALSE;
//STRIP001 		}
//STRIP001 		break;
//STRIP001 		case MID_OWN_NUM     :
//STRIP001 		{
//STRIP001 			sal_Bool bVal = *(sal_Bool*)rVal.getValue();
//STRIP001 			if(!bVal && GetValue() >= FTNEND_ATTXTEND_OWNNUMANDFMT)
//STRIP001 				SetValue(FTNEND_ATTXTEND_OWNNUMSEQ);
//STRIP001 			else if(bVal && GetValue() < FTNEND_ATTXTEND_OWNNUMANDFMT)
//STRIP001 				SetValue(FTNEND_ATTXTEND_OWNNUMANDFMT);
//STRIP001 		}
//STRIP001 		break;
//STRIP001 		case MID_NUM_TYPE    :
//STRIP001 		{
//STRIP001 			sal_Int16 nVal;
//STRIP001 			rVal >>= nVal;
//STRIP001 			if(nVal >= 0 &&
//STRIP001 				(nVal <= SVX_NUM_ARABIC ||
//STRIP001 					SVX_NUM_CHARS_UPPER_LETTER_N == nVal ||
//STRIP001 						SVX_NUM_CHARS_LOWER_LETTER_N == nVal ))
//STRIP001 				aFmt.SetNumberingType(nVal);
//STRIP001 			else
//STRIP001 				bRet = FALSE;
//STRIP001 		}
//STRIP001 		break;
//STRIP001 		case MID_PREFIX      :
//STRIP001 		{
//STRIP001 			OUString sVal; rVal >>= sVal;
//STRIP001 			sPrefix = sVal;
//STRIP001 		}
//STRIP001 		break;
//STRIP001 		case MID_SUFFIX      :
//STRIP001 		{
//STRIP001 			OUString sVal; rVal >>= sVal;
//STRIP001 			sSuffix = sVal;
//STRIP001 		}
//STRIP001 		break;
//STRIP001 		default: bRet = FALSE;
//STRIP001 	}
//STRIP001 	return bRet;
//STRIP001 }


// class SwFmtFtnAtTxtEnd

//STRIP001 SfxPoolItem* SwFmtFtnAtTxtEnd::Clone( SfxItemPool* pPool ) const
//STRIP001 {
//STRIP001 	SwFmtFtnAtTxtEnd* pNew = new SwFmtFtnAtTxtEnd;
//STRIP001 	*pNew = *this;
//STRIP001 	return pNew;
//STRIP001 }

// class SwFmtEndAtTxtEnd

//STRIP001 SfxPoolItem* SwFmtEndAtTxtEnd::Clone( SfxItemPool* pPool ) const
//STRIP001 {
//STRIP001 	SwFmtEndAtTxtEnd* pNew = new SwFmtEndAtTxtEnd;
//STRIP001 	*pNew = *this;
//STRIP001 	return pNew;
//STRIP001 }

//class SwFmtChain


//STRIP001 int SwFmtChain::operator==( const SfxPoolItem &rAttr ) const
//STRIP001 {
//STRIP001 	ASSERT( SfxPoolItem::operator==( rAttr ), "keine gleichen Attribute" );
//STRIP001 
//STRIP001 	return GetPrev() == ((SwFmtChain&)rAttr).GetPrev() &&
//STRIP001 		   GetNext() == ((SwFmtChain&)rAttr).GetNext();
//STRIP001 }

//STRIP001 SwFmtChain::SwFmtChain( const SwFmtChain &rCpy ) :
//STRIP001 	SfxPoolItem( RES_CHAIN )
//STRIP001 {
//STRIP001 	SetPrev( rCpy.GetPrev() );
//STRIP001 	SetNext( rCpy.GetNext() );
//STRIP001 }

//STRIP001 SfxPoolItem* SwFmtChain::Clone( SfxItemPool* pPool ) const
//STRIP001 {
//STRIP001 	SwFmtChain *pRet = new SwFmtChain;
//STRIP001 	pRet->SetPrev( GetPrev() );
//STRIP001 	pRet->SetNext( GetNext() );
//STRIP001 	return pRet;
//STRIP001 }

//STRIP001 void SwFmtChain::SetPrev( SwFlyFrmFmt *pFmt )
//STRIP001 {
//STRIP001 	if ( pFmt )
//STRIP001 		pFmt->Add( &aPrev );
//STRIP001 	else if ( aPrev.GetRegisteredIn() )
//STRIP001 		((SwModify*)aPrev.GetRegisteredIn())->Remove( &aPrev );
//STRIP001 }

//STRIP001 void SwFmtChain::SetNext( SwFlyFrmFmt *pFmt )
//STRIP001 {
//STRIP001 	if ( pFmt )
//STRIP001 		pFmt->Add( &aNext );
//STRIP001 	else if ( aNext.GetRegisteredIn() )
//STRIP001 		((SwModify*)aNext.GetRegisteredIn())->Remove( &aNext );
//STRIP001 }

/*N*/ BOOL SwFmtChain::QueryValue( uno::Any& rVal, BYTE nMemberId ) const
/*N*/ {
/*N*/ 	// hier wird immer konvertiert!
/*N*/ 	nMemberId &= ~CONVERT_TWIPS;
/*N*/ 	sal_Bool   bRet = sal_True;
/*N*/ 	XubString aRet;
/*N*/ 	switch ( nMemberId )
/*N*/ 	{
/*N*/ 		case MID_CHAIN_PREVNAME:
/*?*/ 			if ( GetPrev() )
/*?*/ 				aRet = GetPrev()->GetName();
/*?*/ 			break;
/*N*/ 		case MID_CHAIN_NEXTNAME:
/*N*/ 			if ( GetNext() )
/*?*/ 				aRet = GetNext()->GetName();
/*N*/ 			break;
/*N*/ 		default:
/*?*/ 			ASSERT( !this, "unknown MemberId" );
/*?*/ 			bRet = sal_False;
/*N*/ 	}
/*N*/ 	rVal <<= OUString(aRet);
/*N*/ 	return bRet;
/*N*/ }




//class SwFmtLineNumber

/*N*/ SwFmtLineNumber::SwFmtLineNumber() :
/*N*/ 	SfxPoolItem( RES_LINENUMBER )
/*N*/ {
/*N*/ 	nStartValue = 0;
/*N*/ 	bCountLines = sal_True;
/*N*/ }

/*N*/ SwFmtLineNumber::~SwFmtLineNumber()
/*N*/ {
/*N*/ }

/*N*/ int SwFmtLineNumber::operator==( const SfxPoolItem &rAttr ) const
/*N*/ {
/*N*/ 	ASSERT( SfxPoolItem::operator==( rAttr ), "keine gleichen Attribute" );
/*N*/ 
/*N*/ 	return nStartValue	== ((SwFmtLineNumber&)rAttr).GetStartValue() &&
/*N*/ 		   bCountLines	== ((SwFmtLineNumber&)rAttr).IsCount();
/*N*/ }

/*N*/ SfxPoolItem* SwFmtLineNumber::Clone( SfxItemPool* pPool ) const
/*N*/ {
/*N*/ 	return new SwFmtLineNumber( *this );
/*N*/ }

/*N*/ BOOL SwFmtLineNumber::QueryValue( uno::Any& rVal, BYTE nMemberId ) const
/*N*/ {
/*N*/ 	// hier wird immer konvertiert!
/*N*/ 	nMemberId &= ~CONVERT_TWIPS;
/*N*/ 	sal_Bool bRet = sal_True;
/*N*/ 	switch ( nMemberId )
/*N*/ 	{
/*N*/ 		case MID_LINENUMBER_COUNT:
/*N*/ 		{
/*N*/ 			BOOL bTmp = IsCount();
/*N*/ 			rVal.setValue(&bTmp, ::getBooleanCppuType());
/*N*/ 		}
/*N*/ 		break;
/*N*/ 		case MID_LINENUMBER_STARTVALUE:
/*N*/ 			rVal <<= (sal_Int32)GetStartValue();
/*N*/ 			break;
/*N*/ 		default:
/*?*/ 			ASSERT( !this, "unknown MemberId" );
/*?*/ 			bRet = sal_False;
/*N*/ 	}
/*N*/ 	return bRet;
/*N*/ }

/*N*/ BOOL SwFmtLineNumber::PutValue( const uno::Any& rVal, BYTE nMemberId )
/*N*/ {
/*N*/ 	// hier wird immer konvertiert!
/*N*/ 	nMemberId &= ~CONVERT_TWIPS;
/*N*/ 	sal_Bool bRet = sal_True;
/*N*/ 	switch ( nMemberId )
/*N*/ 	{
/*N*/ 		case MID_LINENUMBER_COUNT:
/*N*/ 			SetCountLines( *(sal_Bool*)rVal.getValue() );
/*N*/ 			break;
/*N*/ 		case MID_LINENUMBER_STARTVALUE:
/*N*/         {
/*N*/             sal_Int32 nVal;
/*N*/             if(rVal >>= nVal)
/*N*/                 SetStartValue( nVal );
/*N*/             else
/*?*/                 bRet = sal_False;
/*N*/         }
/*N*/         break;
/*N*/ 		default:
/*?*/ 			ASSERT( !this, "unknown MemberId" );
/*?*/ 			bRet = sal_False;
/*N*/ 	}
/*N*/ 	return bRet;
/*N*/ }

/*************************************************************************
 *    class SwTextGridItem
 *************************************************************************/

/*N*/ SwTextGridItem::SwTextGridItem()
/*N*/     : SfxPoolItem( RES_TEXTGRID ), aColor( COL_LIGHTGRAY ), nLines( 20 ),
/*N*/       nBaseHeight( 400 ), nRubyHeight( 200 ), eGridType( GRID_NONE ),
/*N*/       bRubyTextBelow( 0 ), bPrintGrid( 1 ), bDisplayGrid( 1 )
/*N*/ {
/*N*/ }

/*N*/ SwTextGridItem::~SwTextGridItem()
/*N*/ {
/*N*/ }

//STRIP001 int SwTextGridItem::operator==( const SfxPoolItem& rAttr ) const
//STRIP001 {
//STRIP001 	ASSERT( SfxPoolItem::operator==( rAttr ), "keine gleichen Attribute" );
//STRIP001     return eGridType == ((SwTextGridItem&)rAttr).GetGridType() &&
//STRIP001            nLines == ((SwTextGridItem&)rAttr).GetLines() &&
//STRIP001            nBaseHeight == ((SwTextGridItem&)rAttr).GetBaseHeight() &&
//STRIP001            nRubyHeight == ((SwTextGridItem&)rAttr).GetRubyHeight() &&
//STRIP001            bRubyTextBelow == ((SwTextGridItem&)rAttr).GetRubyTextBelow() &&
//STRIP001            bDisplayGrid == ((SwTextGridItem&)rAttr).GetDisplayGrid() &&
//STRIP001            bPrintGrid == ((SwTextGridItem&)rAttr).GetPrintGrid() &&
//STRIP001            aColor == ((SwTextGridItem&)rAttr).GetColor();
//STRIP001 }

//STRIP001 SfxPoolItem* SwTextGridItem::Clone( SfxItemPool* pPool ) const
//STRIP001 {
//STRIP001     return new SwTextGridItem( *this );
//STRIP001 }

//STRIP001 SwTextGridItem& SwTextGridItem::operator=( const SwTextGridItem& rCpy )
//STRIP001 {
//STRIP001     aColor = rCpy.GetColor();
//STRIP001     nLines = rCpy.GetLines();
//STRIP001     nBaseHeight = rCpy.GetBaseHeight();
//STRIP001     nRubyHeight = rCpy.GetRubyHeight();
//STRIP001     eGridType = rCpy.GetGridType();
//STRIP001     bRubyTextBelow = rCpy.GetRubyTextBelow();
//STRIP001     bPrintGrid = rCpy.GetPrintGrid();
//STRIP001     bDisplayGrid = rCpy.GetDisplayGrid();
//STRIP001 
//STRIP001 	return *this;
//STRIP001 }

//STRIP001 BOOL SwTextGridItem::QueryValue( ::com::sun::star::uno::Any& rVal,
//STRIP001                                  BYTE nMemberId ) const
//STRIP001 {
//STRIP001     BOOL bRet = TRUE;
//STRIP001 
//STRIP001     switch( nMemberId & ~CONVERT_TWIPS )
//STRIP001     {
//STRIP001         case MID_GRID_COLOR:
//STRIP001             rVal <<= GetColor().GetColor();
//STRIP001             break;
//STRIP001         case MID_GRID_LINES:
//STRIP001             rVal <<= GetLines();
//STRIP001             break;
//STRIP001         case MID_GRID_RUBY_BELOW:
//STRIP001             rVal.setValue( &bRubyTextBelow, ::getBooleanCppuType() );
//STRIP001             break;
//STRIP001         case MID_GRID_PRINT:
//STRIP001             rVal.setValue( &bPrintGrid, ::getBooleanCppuType() );
//STRIP001             break;
//STRIP001         case MID_GRID_DISPLAY:
//STRIP001             rVal.setValue( &bDisplayGrid, ::getBooleanCppuType() );
//STRIP001             break;
//STRIP001         case MID_GRID_BASEHEIGHT:
//STRIP001             DBG_ASSERT( (nMemberId & CONVERT_TWIPS) != 0,
//STRIP001                         "This value needs TWIPS-MM100 conversion" );
//STRIP001             rVal <<= (sal_Int32) TWIP_TO_MM100(nBaseHeight);
//STRIP001             break;
//STRIP001         case MID_GRID_RUBYHEIGHT:
//STRIP001             DBG_ASSERT( (nMemberId & CONVERT_TWIPS) != 0,
//STRIP001                         "This value needs TWIPS-MM100 conversion" );
//STRIP001             rVal <<= (sal_Int32)TWIP_TO_MM100(nRubyHeight);
//STRIP001             break;
//STRIP001         case MID_GRID_TYPE:
//STRIP001             switch( GetGridType() )
//STRIP001             {
//STRIP001                 case GRID_NONE:
//STRIP001                     rVal <<= TextGridMode::NONE;
//STRIP001                     break;
//STRIP001                 case GRID_LINES_ONLY:
//STRIP001                     rVal <<= TextGridMode::LINES;
//STRIP001                     break;
//STRIP001                 case GRID_LINES_CHARS:
//STRIP001                     rVal <<= TextGridMode::LINES_AND_CHARS;
//STRIP001                     break;
//STRIP001                 default:
//STRIP001                     DBG_ERROR("unknown SwTextGrid value");
//STRIP001                     bRet = FALSE;
//STRIP001                     break;
//STRIP001             }
//STRIP001             break;
//STRIP001         default:
//STRIP001             DBG_ERROR("Unknown SwTextGridItem member");
//STRIP001             bRet = FALSE;
//STRIP001             break;
//STRIP001     }
//STRIP001 
//STRIP001 	return bRet;
//STRIP001 }

//STRIP001 BOOL SwTextGridItem::PutValue( const ::com::sun::star::uno::Any& rVal,
//STRIP001                                BYTE nMemberId )
//STRIP001 {
//STRIP001 	BOOL bRet = TRUE;
//STRIP001     switch( nMemberId & ~CONVERT_TWIPS )
//STRIP001     {
//STRIP001         case MID_GRID_COLOR:
//STRIP001         {
//STRIP001             sal_Int32 nTmp;
//STRIP001             bRet = (rVal >>= nTmp);
//STRIP001             if( bRet )
//STRIP001                 SetColor( Color(nTmp) );
//STRIP001         }
//STRIP001         break;
//STRIP001         case MID_GRID_LINES:
//STRIP001         {
//STRIP001             sal_Int16 nTmp;
//STRIP001             bRet = (rVal >>= nTmp);
//STRIP001             if( bRet && (nTmp >= 0) )
//STRIP001                 SetLines( (sal_uInt16)nTmp );
//STRIP001             else
//STRIP001                 bRet = FALSE;
//STRIP001         }
//STRIP001         break;
//STRIP001         case MID_GRID_RUBY_BELOW:
//STRIP001             SetRubyTextBelow( *(sal_Bool*)rVal.getValue() );
//STRIP001             break;
//STRIP001         case MID_GRID_PRINT:
//STRIP001             SetPrintGrid( *(sal_Bool*)rVal.getValue() );
//STRIP001             break;
//STRIP001         case MID_GRID_DISPLAY:
//STRIP001             SetDisplayGrid( *(sal_Bool*)rVal.getValue() );
//STRIP001             break;
//STRIP001         case MID_GRID_BASEHEIGHT:
//STRIP001         case MID_GRID_RUBYHEIGHT:
//STRIP001         {
//STRIP001             DBG_ASSERT( (nMemberId & CONVERT_TWIPS) != 0,
//STRIP001                         "This value needs TWIPS-MM100 conversion" );
//STRIP001             sal_Int32 nTmp;
//STRIP001             bRet = (rVal >>= nTmp);
//STRIP001             nTmp = MM100_TO_TWIP( nTmp );
//STRIP001             if( bRet && (nTmp >= 0) && ( nTmp <= USHRT_MAX) )
//STRIP001                 if( (nMemberId & ~CONVERT_TWIPS) == MID_GRID_BASEHEIGHT )
//STRIP001                     SetBaseHeight( (USHORT)nTmp );
//STRIP001                 else
//STRIP001                     SetRubyHeight( (USHORT)nTmp );
//STRIP001             else
//STRIP001                 bRet = FALSE;
//STRIP001         }
//STRIP001         break;
//STRIP001         case MID_GRID_TYPE:
//STRIP001             sal_Int16 nTmp;
//STRIP001             bRet = (rVal >>= nTmp);
//STRIP001             if( bRet )
//STRIP001             {
//STRIP001                 switch( nTmp )
//STRIP001                 {
//STRIP001                     case TextGridMode::NONE:
//STRIP001                         SetGridType( GRID_NONE );
//STRIP001                         break;
//STRIP001                     case TextGridMode::LINES:
//STRIP001                         SetGridType( GRID_LINES_ONLY );
//STRIP001                         break;
//STRIP001                     case TextGridMode::LINES_AND_CHARS:
//STRIP001                         SetGridType( GRID_LINES_CHARS );
//STRIP001                         break;
//STRIP001                     default:
//STRIP001                         bRet = FALSE;
//STRIP001                         break;
//STRIP001                 }
//STRIP001             }
//STRIP001             break;
//STRIP001         default:
//STRIP001             DBG_ERROR("Unknown SwTextGridItem member");
//STRIP001             bRet = FALSE;
//STRIP001     }
//STRIP001 
//STRIP001     return bRet;
//STRIP001 }

// class SwHeaderAndFooterEatSpacingItem

/*M*/ SfxPoolItem* SwHeaderAndFooterEatSpacingItem::Clone( SfxItemPool* pPool ) const
/*M*/ {
/*M*/     return new SwHeaderAndFooterEatSpacingItem( Which(), GetValue() );
/*M*/ }


//  class SwFrmFmt
//	Implementierung teilweise inline im hxx

/*N*/ void SwFrmFmt::Modify( SfxPoolItem* pOld, SfxPoolItem* pNew )
/*N*/ {
/*N*/ 	SwFmtHeader *pH = 0;
/*N*/ 	SwFmtFooter *pF = 0;
/*N*/ 
/*N*/ 	sal_uInt16 nWhich = pNew ? pNew->Which() : 0;
/*N*/ 
/*N*/ 	if( RES_ATTRSET_CHG == nWhich )
/*N*/ 	{
/*N*/ 		((SwAttrSetChg*)pNew)->GetChgSet()->GetItemState(
/*N*/ 			RES_HEADER, sal_False, (const SfxPoolItem**)&pH );
/*N*/ 		((SwAttrSetChg*)pNew)->GetChgSet()->GetItemState(
/*N*/ 			RES_FOOTER, sal_False, (const SfxPoolItem**)&pF );
/*N*/ 	}
/*N*/ 	else if( RES_HEADER == nWhich )
/*?*/ 		pH = (SwFmtHeader*)pNew;
/*N*/ 	else if( RES_FOOTER == nWhich )
/*?*/ 		pF = (SwFmtFooter*)pNew;
/*N*/ 
/*N*/ 	if( pH && pH->IsActive() && !pH->GetHeaderFmt() )
/*N*/ 	{	//Hat er keinen, mach ich ihm einen
/*N*/ 		SwFrmFmt *pFmt = GetDoc()->MakeLayoutFmt( RND_STD_HEADER );
/*N*/ 		pFmt->Add( pH );
/*N*/ 	}
/*N*/ 
/*N*/ 	if( pF && pF->IsActive() && !pF->GetFooterFmt() )
/*N*/ 	{	//Hat er keinen, mach ich ihm einen
/*N*/ 		SwFrmFmt *pFmt = GetDoc()->MakeLayoutFmt( RND_STD_FOOTER );
/*N*/ 		pFmt->Add( pF );
/*N*/ 	}
/*N*/ 
/*N*/ 	// MIB 24.3.98: Modify der Basisklasse muss immer gerufen werden, z.B.
/*N*/ 	// wegen RESET_FMTWRITTEN.
/*N*/ //	if ( GetDepends() )
/*N*/ 		SwFmt::Modify( pOld, pNew );
/*N*/ }

//Vernichtet alle Frms, die in aDepend angemeldet sind.

/*N*/ void SwFrmFmt::DelFrms()
/*N*/ {
/*N*/ 	SwClientIter aIter( *this );
/*N*/ 	SwClient * pLast = aIter.GoStart();
/*N*/ 	if( pLast )
/*N*/ 		do {
/*N*/ 			if ( pLast->ISA(SwFrm) )
/*N*/ 			{
/*N*/ 				((SwFrm*)pLast)->Cut();
/*N*/ 				delete pLast;
/*N*/ 			}
/*N*/ 		} while( 0 != ( pLast = aIter++ ));
/*N*/ }

//STRIP001 void SwFrmFmt::MakeFrms()
//STRIP001 {
//STRIP001 	ASSERT( !this, "Sorry not implemented." );
//STRIP001 }



/*N*/ SwRect SwFrmFmt::FindLayoutRect( const sal_Bool bPrtArea, const Point* pPoint,
/*N*/ 								 const sal_Bool bCalcFrm ) const
/*N*/ {
/*N*/ 	SwRect aRet;
/*N*/ 	SwFrm *pFrm = 0;
/*N*/ 	if( ISA( SwSectionFmt ) )
/*N*/ 	{
/*?*/ 		// dann den ::com::sun::star::frame::Frame per Node2Layout besorgen
/*?*/ 		SwSectionNode* pSectNd = ((SwSectionFmt*)this)->GetSectionNode();
/*?*/ 		if( pSectNd )
/*?*/ 		{
/*?*/ 			SwNode2Layout aTmp( *pSectNd, pSectNd->GetIndex() - 1 );
/*?*/ 			pFrm = aTmp.NextFrm();
/*?*/ 
/*?*/ 			if( pFrm && pFrm->GetRegisteredIn() != this )
/*?*/ 			{
/*?*/ 				// die Section hat keinen eigenen ::com::sun::star::frame::Frame, also falls
/*?*/ 				// jemand die tatsaechliche Groe�e braucht, so muss das
/*?*/ 				// noch implementier werden, in dem sich vom Ende noch
/*?*/ 				// der entsprechende ::com::sun::star::frame::Frame besorgt wird.
/*?*/ 				// PROBLEM: was passiert bei SectionFrames, die auf unter-
/*?*/ 				//			schiedlichen Seiten stehen??
/*?*/ 				if( bPrtArea )
/*?*/ 					aRet = pFrm->Prt();
/*?*/ 				else
/*?*/ 				{
/*?*/ 					aRet = pFrm->Frm();
/*?*/ 					--aRet.Pos().Y();
/*?*/ 				}
/*?*/ 				pFrm = 0;		// das Rect ist ja jetzt fertig
/*?*/ 			}
/*?*/ 		}
/*N*/ 	}
/*N*/ 	else
/*N*/ 	{
/*N*/ 		sal_uInt16 nFrmType = RES_FLYFRMFMT == Which() ? FRM_FLY : USHRT_MAX;
/*N*/ 		pFrm = ::binfilter::GetFrmOfModify( *(SwModify*)this, nFrmType, pPoint,
/*N*/ 									0, bCalcFrm );
/*N*/ 	}
/*N*/ 
/*N*/ 	if( pFrm )
/*N*/ 	{
/*N*/ 		if( bPrtArea )
/*N*/ 			aRet = pFrm->Prt();
/*N*/ 		else
/*?*/ 			aRet = pFrm->Frm();
/*N*/ 	}
/*N*/ 	return aRet;
/*N*/ }

/*N*/ SwContact* SwFrmFmt::FindContactObj()
/*N*/ {
/*N*/ 	SwClientIter aIter( *this );
/*N*/ 	return (SwContact*)aIter.First( TYPE( SwContact ) );
/*N*/ }

/*N*/ SdrObject* SwFrmFmt::FindSdrObject()
/*N*/ {
/*N*/ 	SwClientIter aIter( *this );
/*N*/ 	SwClient* pFnd = aIter.First( TYPE( SwContact ) );
/*N*/ 	return pFnd ? ((SwContact*)pFnd)->GetMaster() : 0;
/*N*/ }

/*N*/ SdrObject* SwFrmFmt::FindRealSdrObject()
/*N*/ {
/*N*/ 	if( RES_FLYFRMFMT == Which() )
/*N*/ 	{
/*N*/ 		Point aNullPt;
/*N*/ 		SwFlyFrm* pFly = (SwFlyFrm*)::binfilter::GetFrmOfModify( *this, FRM_FLY,
/*N*/ 													&aNullPt, 0, sal_False );
/*N*/ 		return pFly ? pFly->GetVirtDrawObj() : 0;
/*N*/ 	}
/*?*/ 	return FindSdrObject();
/*N*/ }


//STRIP001 sal_Bool SwFrmFmt::IsLowerOf( const SwFrmFmt& rFmt ) const
//STRIP001 {
//STRIP001 	//Auch eine Verkettung von Innen nach aussen oder von aussen
//STRIP001 	//nach innen ist nicht zulaessig.
//STRIP001 	SwClientIter aIter( *(SwModify*)this );
//STRIP001 	SwFlyFrm *pSFly = (SwFlyFrm*)aIter.First( TYPE(SwFlyFrm) );
//STRIP001 	if( pSFly )
//STRIP001 	{
//STRIP001 		SwClientIter aOtherIter( (SwModify&)rFmt );
//STRIP001 		SwFlyFrm *pAskFly = (SwFlyFrm*)aOtherIter.First( TYPE(SwFlyFrm) );
//STRIP001 		if( pAskFly )
//STRIP001 			return pSFly->IsLowerOf( pAskFly );
//STRIP001 	}
//STRIP001 
//STRIP001 	// dann mal ueber die Node-Positionen versuchen
//STRIP001 	const SwFmtAnchor* pAnchor = &rFmt.GetAnchor();
//STRIP001 	if( FLY_PAGE != pAnchor->GetAnchorId() && pAnchor->GetCntntAnchor() )
//STRIP001 	{
//STRIP001 		const SwSpzFrmFmts& rFmts = *GetDoc()->GetSpzFrmFmts();
//STRIP001 		const SwNode* pFlyNd = pAnchor->GetCntntAnchor()->nNode.GetNode().
//STRIP001 								FindFlyStartNode();
//STRIP001 		while( pFlyNd )
//STRIP001 		{
//STRIP001 			// dann ueber den Anker nach oben "hangeln"
//STRIP001 			for( sal_uInt16 n = 0; n < rFmts.Count(); ++n )
//STRIP001 			{
//STRIP001 				const SwFrmFmt* pFmt = rFmts[ n ];
//STRIP001 				const SwNodeIndex* pIdx = pFmt->GetCntnt().GetCntntIdx();
//STRIP001 				if( pIdx && pFlyNd == &pIdx->GetNode() )
//STRIP001 				{
//STRIP001 					if( pFmt == this )
//STRIP001 						return sal_True;
//STRIP001 
//STRIP001 					pAnchor = &pFmt->GetAnchor();
//STRIP001 					if( FLY_PAGE == pAnchor->GetAnchorId() ||
//STRIP001 						!pAnchor->GetCntntAnchor() )
//STRIP001 						return sal_False;
//STRIP001 
//STRIP001 					pFlyNd = pAnchor->GetCntntAnchor()->nNode.GetNode().
//STRIP001 								FindFlyStartNode();
//STRIP001 					break;
//STRIP001 				}
//STRIP001 			}
//STRIP001 			if( n >= rFmts.Count() )
//STRIP001 			{
//STRIP001 				ASSERT( !this, "Fly-Section aber kein Format gefunden" );
//STRIP001 				return sal_False;
//STRIP001 			}
//STRIP001 		}
//STRIP001 	}
//STRIP001 	return sal_False;
//STRIP001 }

//	class SwFlyFrmFmt
//	Implementierung teilweise inline im hxx

/*N*/ SwFlyFrmFmt::~SwFlyFrmFmt()
/*N*/ {
/*N*/ 	SwClientIter aIter( *this );
/*N*/ 	SwClient * pLast = aIter.GoStart();
/*N*/ 	if( pLast )
/*N*/ 		do {
/*N*/ 			if ( pLast->ISA( SwFlyFrm ) )
/*?*/ 				delete pLast;
/*N*/ 
/*N*/ 		} while( 0 != ( pLast = aIter++ ));
/*N*/ 
/*N*/ 	pLast = aIter.GoStart();
/*N*/ 	if( pLast )
/*N*/ 		do {
/*N*/ 			if ( pLast->ISA( SwFlyDrawContact ) )
/*N*/ 				delete pLast;
/*N*/ 
/*N*/ 		} while( 0 != ( pLast = aIter++ ));
/*N*/ }

//Erzeugen der Frms wenn das Format einen Absatzgebundenen Rahmen beschreibt.
//MA: 14. Feb. 94, Erzeugen der Frms auch fuer Seitengebundene Rahmen.

void SwFlyFrmFmt::MakeFrms()
{
    // gibts ueberhaupt ein Layout ??
    if( !GetDoc()->GetRootFrm() )
        return;

    SwModify *pModify = 0;
    // OD 24.07.2003 #111032# - create local copy of anchor attribute for possible changes.
    SwFmtAnchor aAnchorAttr( GetAnchor() );
    switch( aAnchorAttr.GetAnchorId() )
    {
    case FLY_IN_CNTNT:
    case FLY_AT_CNTNT:
    case FLY_AUTO_CNTNT:
        if( aAnchorAttr.GetCntntAnchor() )
            pModify = aAnchorAttr.GetCntntAnchor()->nNode.GetNode().GetCntntNode();
        break;

    case FLY_AT_FLY:
        if( aAnchorAttr.GetCntntAnchor() )
        {
            //Erst einmal ueber den Inhalt suchen, weil konstant schnell. Kann
            //Bei verketteten Rahmen aber auch schief gehen, weil dann evtl.
            //niemals ein ::com::sun::star::frame::Frame zu dem Inhalt existiert. Dann muss leider noch
            //die Suche vom StartNode zum FrameFormat sein.
            SwNodeIndex aIdx( aAnchorAttr.GetCntntAnchor()->nNode );
            SwCntntNode *pCNd = GetDoc()->GetNodes().GoNext( &aIdx );
            SwClientIter aIter( *pCNd );
            if ( aIter.First( TYPE(SwFrm) ) )
                pModify = pCNd;
            else
            {
                const SwNodeIndex &rIdx = aAnchorAttr.GetCntntAnchor()->nNode;
                SwSpzFrmFmts& rFmts = *GetDoc()->GetSpzFrmFmts();
                for( sal_uInt16 i = 0; i < rFmts.Count(); ++i )
                {
                    SwFrmFmt* pFlyFmt = rFmts[i];
                    if( pFlyFmt->GetCntnt().GetCntntIdx() &&
                        rIdx == *pFlyFmt->GetCntnt().GetCntntIdx() )
                    {
                        pModify = pFlyFmt;
                        break;
                    }
                }
            }
        }
        break;

    case FLY_PAGE:
        {
            sal_uInt16 nPgNum = aAnchorAttr.GetPageNum();
            SwPageFrm *pPage = (SwPageFrm*)GetDoc()->GetRootFrm()->Lower();
            if( !nPgNum && aAnchorAttr.GetCntntAnchor() )
            {
                SwCntntNode *pCNd =
                    aAnchorAttr.GetCntntAnchor()->nNode.GetNode().GetCntntNode();
                SwClientIter aIter( *pCNd );
                do
                {
                    if( aIter()->ISA( SwFrm ) )
                    {
                        pPage = ((SwFrm*)aIter())->FindPageFrm();
                        if( pPage )
                        {
                            nPgNum = pPage->GetPhyPageNum();
                            // OD 24.07.2003 #111032# - update anchor attribute
                            aAnchorAttr.SetPageNum( nPgNum );
                            aAnchorAttr.SetAnchor( 0 );
                            SetAttr( aAnchorAttr );
                        }
                        break;
                    }
                } while ( aIter++ );
            }
            while ( pPage )
            {
                if ( pPage->GetPhyPageNum() == nPgNum )
                {
                    pPage->PlaceFly( 0, this, &aAnchorAttr );
                    break;
                }
                pPage = (SwPageFrm*)pPage->GetNext();
            }
        }
        break;
    }

    if( pModify )
    {
        SwClientIter aIter( *pModify );
        for( SwFrm *pFrm = (SwFrm*)aIter.First( TYPE(SwFrm) );
             pFrm;
             pFrm = (SwFrm*)aIter.Next() )
        {
            FASTBOOL bAdd = !pFrm->IsCntntFrm() ||
                            !((SwCntntFrm*)pFrm)->IsFollow();

            if ( FLY_AT_FLY == aAnchorAttr.GetAnchorId() && !pFrm->IsFlyFrm() )
                pFrm = pFrm->FindFlyFrm();

            if( pFrm->GetDrawObjs() )
            {
                SwDrawObjs &rObjs = *pFrm->GetDrawObjs();
                for( sal_uInt16 i = 0; i < rObjs.Count(); ++i)
                {
                    SdrObject *pO = rObjs[i];
                    if( pO->ISA( SwVirtFlyDrawObj ) &&
                        ((SwVirtFlyDrawObj*)pO)->GetFmt() == this )
                    {
                        bAdd = sal_False;
                        break;
                    }
                }
            }

            if( bAdd )
            {
                SwFlyFrm *pFly = 0;
                switch( aAnchorAttr.GetAnchorId() )
                {
                case FLY_AT_FLY:
                    pFly = new SwFlyLayFrm( this, pFrm );
                    break;

                case FLY_AT_CNTNT:
                case FLY_AUTO_CNTNT:
                    pFly = new SwFlyAtCntFrm( this, pFrm );
                    break;

                case FLY_IN_CNTNT:
                    pFly = new SwFlyInCntFrm( this, pFrm );
                    break;
#ifndef PRODUCT
                default:
                    ASSERT( !this, "Neuer Ankertyp" );
#endif
                }
                pFrm->AppendFly( pFly );
                SwPageFrm *pPage = pFly->FindPageFrm();
                if( pPage )
                    ::binfilter::RegistFlys( pPage, pFly );
            }
        }
    }
}

/*N*/ SwFlyFrm* SwFlyFrmFmt::GetFrm( const Point* pPoint, const sal_Bool bCalcFrm ) const
/*N*/ {
/*N*/ 	return (SwFlyFrm*)::binfilter::GetFrmOfModify( *(SwModify*)this, FRM_FLY,
/*N*/ 											pPoint, 0, bCalcFrm );
/*N*/ }

/*N*/ sal_Bool SwFlyFrmFmt::GetInfo( SfxPoolItem& rInfo ) const
/*N*/ {
/*N*/ 	switch( rInfo.Which() )
/*N*/ 	{
/*N*/ 	case RES_CONTENT_VISIBLE:
/*?*/ 		{
/*?*/ 			((SwPtrMsgPoolItem&)rInfo).pObject =
/*?*/ 				SwClientIter( *(SwFlyFrmFmt*)this ).First( TYPE(SwFrm) );
/*?*/ 		}
/*?*/ 		return sal_False;
/*N*/ 
/*N*/ 	default:
/*N*/ 		return SwFrmFmt::GetInfo( rInfo );
/*N*/ 	}
/*N*/ 	return sal_True;
/*N*/ }

/** SwFlyFrmFmt::IsBackgroundTransparent - for #99657#

    OD 22.08.2002 - overloading virtual method and its default implementation,
    because format of fly frame provides transparent backgrounds.
    Method determines, if background of fly frame is transparent.

    @author OD

    @return true, if background color is transparent, but not "no fill"
    or the transparency of a existing background graphic is set.
*/
/*M*/ const sal_Bool SwFlyFrmFmt::IsBackgroundTransparent() const
/*M*/ {
/*M*/     sal_Bool bReturn = sal_False;
/*M*/ 
/*N*/     /// NOTE: If background color is "no fill"/"auto fill" (COL_TRANSPARENT)
/*N*/     ///     and there is no background graphic, it "inherites" the background
/*N*/     ///     from its anchor.
/*M*/     if ( (GetBackground().GetColor().GetTransparency() != 0) &&
/*M*/          (GetBackground().GetColor() != COL_TRANSPARENT)
/*M*/        )
/*M*/     {
/*M*/         bReturn = sal_True;
/*M*/     }
/*M*/     else
/*M*/     {
/*N*/         const GraphicObject *pTmpGrf =
/*N*/                 static_cast<const GraphicObject*>(GetBackground().GetGraphicObject());
/*M*/         if ( (pTmpGrf) &&
/*M*/              (pTmpGrf->GetAttr().GetTransparency() != 0)
/*M*/            )
/*M*/         {
/*M*/             bReturn = sal_True;
/*M*/         }
/*M*/     }
/*M*/ 
/*M*/     return bReturn;
/*M*/ }

/** SwFlyFrmFmt::IsBackgroundBrushInherited - for #103898#

    OD 08.10.2002 - method to determine, if the brush for drawing the
    background is "inherited" from its parent/grandparent.
    This is the case, if no background graphic is set and the background
    color is "no fill"/"auto fill"
    NOTE: condition is "copied" from method <SwFrm::GetBackgroundBrush(..).

    @author OD

    @return true, if background brush is "inherited" from parent/grandparent
*/
//STRIP001 const sal_Bool SwFlyFrmFmt::IsBackgroundBrushInherited() const
//STRIP001 {
//STRIP001     sal_Bool bReturn = sal_False;
//STRIP001 
//STRIP001     if ( (GetBackground().GetColor() == COL_TRANSPARENT) &&
//STRIP001          !(GetBackground().GetGraphicObject()) )
//STRIP001     {
//STRIP001         bReturn = sal_True;
//STRIP001     }
//STRIP001 
//STRIP001     return bReturn;
//STRIP001 }


//	class SwDrawFrmFmt
//	Implementierung teilweise inline im hxx

/*N*/ #pragma optimize( "e", off )

/*N*/ SwDrawFrmFmt::~SwDrawFrmFmt()
/*N*/ {
/*N*/ 	SwContact *pContact = FindContactObj();
/*N*/ 	delete pContact;
/*N*/ }

/*N*/ #pragma optimize( "e", on )

/*N*/ void SwDrawFrmFmt::MakeFrms()
/*N*/ {
/*N*/ 	SwDrawContact *pContact = (SwDrawContact*)FindContactObj();
/*N*/     if ( pContact )
/*N*/          pContact->ConnectToLayout();
/*N*/ }

/*N*/ void SwDrawFrmFmt::DelFrms()
/*N*/ {
/*N*/ 	SwDrawContact *pContact = (SwDrawContact *)FindContactObj();
/*N*/ 	if ( pContact ) //fuer den Reader und andere Unabwaegbarkeiten.
/*N*/ 		pContact->DisconnectFromLayout();
/*N*/ }


//STRIP001 IMapObject* SwFrmFmt::GetIMapObject( const Point& rPoint,
//STRIP001 										const SwFlyFrm *pFly ) const
//STRIP001 {
//STRIP001 	const SwFmtURL &rURL = GetURL();
//STRIP001 	if( !rURL.GetMap() )
//STRIP001 		return 0;
//STRIP001 
//STRIP001 	if( !pFly )
//STRIP001 	{
//STRIP001 		pFly = (SwFlyFrm*) SwClientIter( *(SwFrmFmt*)this ).First( TYPE( SwFlyFrm ));
//STRIP001 		if( !pFly )
//STRIP001 			return 0;
//STRIP001 	}
//STRIP001 
//STRIP001 	//Orignialgroesse fuer OLE und Grafik ist die TwipSize,
//STRIP001 	//ansonsten die Groesse vom FrmFmt des Fly.
//STRIP001 	const SwFrm *pRef;
//STRIP001 	SwNoTxtNode *pNd;
//STRIP001 	Size aOrigSz;
//STRIP001 	if( pFly->Lower() && pFly->Lower()->IsNoTxtFrm() )
//STRIP001 	{
//STRIP001 		pRef = pFly->Lower();
//STRIP001 		pNd = ((SwCntntFrm*)pRef)->GetNode()->GetNoTxtNode();
//STRIP001 		aOrigSz = pNd->GetTwipSize();
//STRIP001 	}
//STRIP001 	else
//STRIP001 	{
//STRIP001 		pRef = pFly;
//STRIP001 		aOrigSz = pFly->GetFmt()->GetFrmSize().GetSize();
//STRIP001 	}
//STRIP001 
//STRIP001 	if( aOrigSz.Width() != 0 && aOrigSz.Height() != 0 )
//STRIP001 	{
//STRIP001 		Point aPos( rPoint );
//STRIP001 		Size aActSz ( pRef == pFly ? pFly->Frm().SSize() : pRef->Prt().SSize() );
//STRIP001 		const MapMode aSrc ( MAP_TWIP );
//STRIP001 		const MapMode aDest( MAP_100TH_MM );
//STRIP001 		aOrigSz = OutputDevice::LogicToLogic( aOrigSz, aSrc, aDest );
//STRIP001 		aActSz  = OutputDevice::LogicToLogic( aActSz,  aSrc, aDest );
//STRIP001 		aPos -= pRef->Frm().Pos();
//STRIP001 		aPos -= pRef->Prt().Pos();
//STRIP001 		aPos    = OutputDevice::LogicToLogic( aPos, aSrc, aDest );
//STRIP001 		sal_uInt32 nFlags = 0;
//STRIP001 		if ( pFly != pRef && pNd->IsGrfNode() )
//STRIP001 		{
//STRIP001 			const sal_uInt16 nMirror = pNd->GetSwAttrSet().
//STRIP001 										GetMirrorGrf().GetValue();
//STRIP001 			if ( RES_MIRROR_GRF_BOTH == nMirror )
//STRIP001 				nFlags = IMAP_MIRROR_HORZ | IMAP_MIRROR_VERT;
//STRIP001 			else if ( RES_MIRROR_GRF_VERT == nMirror )
//STRIP001 				nFlags = IMAP_MIRROR_VERT;
//STRIP001 			else if ( RES_MIRROR_GRF_HOR == nMirror )
//STRIP001 				nFlags = IMAP_MIRROR_HORZ;
//STRIP001 
//STRIP001 		}
//STRIP001 		return ((ImageMap*)rURL.GetMap())->GetHitIMapObject( aOrigSz,
//STRIP001 												aActSz, aPos, nFlags );
//STRIP001 	}
//STRIP001 
//STRIP001 	return 0;
//STRIP001 }

}
