/*************************************************************************
 *
 *  $RCSfile: sw_docdesc.cxx,v $
 *
 *  $Revision: 1.4 $
 *
 *  last change: $Author: hr $ $Date: 2004-08-04 14:45:00 $
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
#ifndef _SV_VIRDEV_HXX //autogen
#include <vcl/virdev.hxx>
#endif
#ifndef _SFX_PRINTER_HXX //autogen
#include <bf_sfx2/printer.hxx>
#endif
#ifndef _SVDMODEL_HXX //autogen
#include <bf_svx/svdmodel.hxx>
#endif
#ifndef _SVX_ULSPITEM_HXX //autogen
#include <bf_svx/ulspitem.hxx>
#endif
#ifndef _SVX_LRSPITEM_HXX //autogen
#include <bf_svx/lrspitem.hxx>
#endif
#ifndef _SVX_PAPERINF_HXX //autogen
#include <bf_svx/paperinf.hxx>
#endif
#ifndef _SVX_FRMDIRITEM_HXX
#include "bf_svx/frmdiritem.hxx"
#endif
#ifndef _URLOBJ_HXX //autogen
#include <tools/urlobj.hxx>
#endif
#ifndef _SFXDOCFILE_HXX //autogen
#include <bf_sfx2/docfile.hxx>
#endif
// auto strip #ifndef _GLOBNAME_HXX //autogen
// auto strip #include <tools/globname.hxx>
// auto strip #endif
#ifndef _UNOTOOLS_LOCALEDATAWRAPPER_HXX
#include <unotools/localedatawrapper.hxx>
#endif

#ifndef _FMTFSIZE_HXX //autogen
#include <fmtfsize.hxx>
#endif
#ifndef _FMTHDFT_HXX //autogen
#include <fmthdft.hxx>
#endif
#ifndef _FMTCNTNT_HXX //autogen
#include <fmtcntnt.hxx>
#endif
// auto strip #ifndef _FMTPDSC_HXX //autogen
// auto strip #include <fmtpdsc.hxx>
// auto strip #endif
// auto strip #ifndef _FTNINFO_HXX //autogen
// auto strip #include <ftninfo.hxx>
// auto strip #endif

#ifndef _HORIORNT_HXX
#include <horiornt.hxx>
#endif
#ifndef _ERRHDL_HXX
#include <errhdl.hxx>
#endif
#ifndef _VISCRS_HXX
#include <viscrs.hxx>
#endif
#ifndef _FESH_HXX //autogen
#include <fesh.hxx>
#endif
#ifndef _NDOLE_HXX //autogen
#include <ndole.hxx>
#endif
#ifndef _MDIEXP_HXX
#include <mdiexp.hxx>
#endif
// auto strip #ifndef _SWTYPES_HXX
// auto strip #include <swtypes.hxx>
// auto strip #endif
#ifndef _DOC_HXX
#include <doc.hxx>
#endif
#ifndef _DOCARY_HXX
#include <docary.hxx>
#endif
// auto strip #ifndef _PAGEFRM_HXX
// auto strip #include <pagefrm.hxx>	//Fuer DelPageDesc
// auto strip #endif
#ifndef _ROOTFRM_HXX
#include <rootfrm.hxx>	//Fuer DelPageDesc
#endif
#ifndef _HINTS_HXX
#include <hints.hxx>
#endif
// auto strip #ifndef _NDTXT_HXX
// auto strip #include <ndtxt.hxx>
// auto strip #endif
// auto strip #ifndef _FRMTOOL_HXX
// auto strip #include <frmtool.hxx>
// auto strip #endif
#ifndef _PAGEDESC_HXX
#include <pagedesc.hxx>
#endif
#ifndef _POOLFMT_HXX
#include <poolfmt.hxx>
#endif
#ifndef _DOCSH_HXX
#include <docsh.hxx>
#endif
#ifndef _NDINDEX_HXX
#include <ndindex.hxx>
#endif
#ifndef _FTNIDX_HXX
#include <ftnidx.hxx>
#endif
#ifndef _FMTFTN_HXX
#include <fmtftn.hxx>
#endif
#ifndef _TXTFTN_HXX
#include <txtftn.hxx>
#endif
#ifndef _FNTCACHE_HXX
#include <fntcache.hxx>
#endif
// auto strip #ifndef _VIEWSH_HXX
// auto strip #include <viewsh.hxx>
// auto strip #endif
#ifndef _VIEWOPT_HXX
#include <viewopt.hxx>
#endif
#ifndef _FLDBAS_HXX
#include <fldbas.hxx>
#endif
#ifndef _SWWAIT_HXX
#include <swwait.hxx>
#endif
#ifndef _GETMETRICVAL_HXX
#include <GetMetricVal.hxx>
#endif

#ifndef _STATSTR_HRC
#include <statstr.hrc>
#endif
namespace binfilter {

/*N*/ void lcl_DefaultPageFmt( sal_uInt16 nPoolFmtId, SwFrmFmt &rFmt1, 
/*N*/ 						 SwFrmFmt &rFmt2, SfxPrinter *pPrt, BOOL bCheck )
/*N*/ {
/*N*/ 	//Einstellung von Seitengroesse und Seitenraendern. Dazu wird
/*N*/ 	//der Default-Printer benutzt.
/*N*/ 	//Die Physikalische Seitengroesse ist die des Printers
/*N*/ 	//oder DIN-A4 wenn der Printer eine Groesse von 0 liefert.
/*N*/ 	//Der Seitenrand ergibt sich aus der Seitengroesse, der Output-
/*N*/ 	//SSize des Printers und einem Offset der die linke obere Ecke
/*N*/ 	//der Output-SSize relativ zur Physikalischen Pagesize angibt.
/*N*/ 	//Wenn der Offset 0 ist, werden eingestellt.
/*N*/ 	//!!!Die Seitengroesse wird hier im Attribut eingestellt,
/*N*/ 	//dies wird im Ctor des SwPageFrm beachtet.
/*N*/ 
/*N*/ 	SvxLRSpaceItem aLR;
/*N*/ 	SvxULSpaceItem aUL;
/*N*/ 	SwFmtFrmSize aFrmSize( ATT_FIX_SIZE );
/*N*/ 	BOOL bSetFmt1 = TRUE,
/*N*/ 		 bSetFmt2 = TRUE;
/*N*/ 	if ( pPrt )
/*N*/ 	{
/*N*/ 		if ( bCheck )
/*N*/ 		{
/*N*/ 			const SwFmtFrmSize &rFrmSize = rFmt1.GetFrmSize();
/*N*/ 			const SwFmtFrmSize &rFrmSize2 = rFmt2.GetFrmSize();
/*N*/ 			bSetFmt1 = LONG_MAX == rFrmSize.GetWidth() ||
/*N*/ 					   LONG_MAX == rFrmSize.GetHeight();
/*N*/ 			bSetFmt2 = LONG_MAX == rFrmSize2.GetWidth() ||
/*N*/ 					   LONG_MAX == rFrmSize2.GetHeight();
/*N*/ 			if ( !bSetFmt1 && !bSetFmt2 )
/*N*/ 				return;
/*N*/ 		}
/*N*/ 
/*N*/ 		//Seitengrosse
/*N*/ 		//fuer das Erfragen von SV, ob ein Drucker angeschlossen ist,
/*N*/ 		//werden die SV'ler noch eine Methode anbieten.
/*N*/ 		const Size aPhysSize( SvxPaperInfo::GetPaperSize( (Printer*)pPrt ));
/*N*/ 
/*N*/ 		//if ( aPhysSize.Width() <= 0 )
/*N*/ 		//	aPhysSize.Width() = lA4Width;
/*N*/ 		//if ( aPhysSize.Height() <= 0 )
/*N*/ 		//	aPhysSize.Height() = lA4Height;
/*N*/ 		aFrmSize.SetSize( aPhysSize );
/*N*/ 
/*N*/ 		//Raender
/*N*/ 		Point	aOffst(	pPrt->GetPageOffset() );
/*N*/         aOffst += pPrt->GetMapMode().GetOrigin();
/*N*/ 
/*N*/ 		//Auf Default-Raender vorbereiten.
/*N*/ 		//Raender haben eine defaultmaessige Mindestgroesse.
/*N*/ 		//wenn der Drucker einen groesseren Rand vorgibt, so
/*N*/ 		//ist mir dass auch recht.
/*N*/ 		// MIB 06/25/2002, #99397#: The HTML page desc had A4 as page size
/*N*/ 		// always. This has been changed to take the page size from the printer.
/*N*/ 		// Unfortunately, the margins of the HTML page desc are smaller than
/*N*/ 		// the margins used here in general, so one extra case is required.
/*N*/ 		// In the long term, this needs to be changed to always keep the
/*N*/ 		// margins from the page desc.
/*N*/ 		sal_Int32 nMinTop, nMinBottom, nMinLeft, nMinRight;
/*N*/ 		if( RES_POOLPAGE_HTML == nPoolFmtId )
/*N*/ 		{
/*N*/ 			nMinRight = nMinTop = nMinBottom = GetMetricVal( CM_1 );
/*N*/ 			nMinLeft = nMinRight * 2;
/*N*/ 		}
/*N*/ 		else if( MEASURE_METRIC == GetAppLocaleData().getMeasurementSystemEnum() )
/*N*/ 		{
/*N*/ 			nMinTop = nMinBottom = nMinLeft = nMinRight = 1134;	//2 Zentimeter
/*N*/ 		}
/*N*/ 		else
/*N*/ 		{
/*N*/ 			nMinTop = nMinBottom = 1440;	//al la WW: 1Inch
/*N*/ 			nMinLeft = nMinRight = 1800;	//			1,25 Inch
/*N*/ 		}
/*N*/ 
/*N*/ 		//Raender einstellen.
/*N*/ 		aUL.SetUpper( static_cast< sal_uInt16 >( 
/*N*/ 						nMinTop > aOffst.Y() ? nMinTop : aOffst.Y() ) );
/*N*/ 		aUL.SetLower( static_cast< sal_uInt16 >( 
/*N*/ 						nMinBottom > aOffst.Y() ? nMinBottom : aOffst.Y() ));
/*N*/ 		aLR.SetRight( nMinRight > aOffst.X() ? nMinRight : aOffst.X() );
/*N*/ 		aLR.SetLeft(  nMinLeft > aOffst.X() ? nMinLeft : aOffst.X());
/*N*/ 	}
/*N*/ 	else
/*N*/ 	{
/*N*/ 		aFrmSize.SetWidth( LONG_MAX );
/*N*/ 		aFrmSize.SetHeight( LONG_MAX );
/*N*/ 		aUL.SetUpper( 0 );
/*N*/ 		aUL.SetLower( 0 );
/*N*/ 		aLR.SetRight( 0 );
/*N*/ 		aLR.SetLeft(  0 );
/*N*/ 	}
/*N*/ 
/*N*/ 	if ( bSetFmt1 )
/*N*/ 	{
/*N*/ 		rFmt1.SetAttr( aFrmSize );
/*N*/ 		rFmt1.SetAttr( aLR );
/*N*/ 		rFmt1.SetAttr( aUL );
/*N*/ 	}
/*N*/ 	if ( bSetFmt2 )
/*N*/ 	{
/*N*/ 		rFmt2.SetAttr( aFrmSize );
/*N*/ 		rFmt2.SetAttr( aLR );
/*N*/ 		rFmt2.SetAttr( aUL );
/*N*/ 	}
/*N*/ }

/*************************************************************************
|*
|*	SwDoc::ChgPageDesc()
|*
|*	Ersterstellung		MA 25. Jan. 93
|*	Letzte Aenderung	MA 01. Mar. 95
|*
|*************************************************************************/

/*N*/ void lcl_DescSetAttr( const SwFrmFmt &rSource, SwFrmFmt &rDest,
/*N*/ 						 const BOOL bPage = TRUE )
/*N*/ {
/*N*/ /////////////// !!!!!!!!!!!!!!!!
/*N*/ //JP 03.03.99:
/*N*/ // eigentlich sollte hier das Intersect von ItemSet benutzt werden, aber das
/*N*/ // funktioniert nicht richtig, wenn man unterschiedliche WhichRanges hat.
/*N*/ /////////////// !!!!!!!!!!!!!!!!
/*N*/ 	//Die interressanten Attribute uebernehmen.
/*N*/ 	USHORT __READONLY_DATA aIdArr[] = { RES_FRM_SIZE, RES_UL_SPACE,
/*N*/ 										RES_BACKGROUND, RES_SHADOW,
/*N*/ 										RES_COL, RES_COL,
/*N*/ 										RES_FRAMEDIR, RES_FRAMEDIR,
/*N*/                                         RES_TEXTGRID, RES_TEXTGRID,
/*N*/                                         RES_UNKNOWNATR_CONTAINER,
/*N*/ 												RES_UNKNOWNATR_CONTAINER,
/*N*/ 										0 };
/*N*/ 	const SfxPoolItem* pItem;
/*N*/ 	for( USHORT n = 0; aIdArr[ n ]; n += 2 )
/*N*/ 	{
/*N*/ 		for( USHORT nId = aIdArr[ n ]; nId <= aIdArr[ n+1]; ++nId )
/*N*/ 		{
/*N*/ 			if( bPage || ( RES_COL != nId && RES_PAPER_BIN != nId ))
/*N*/ 			{
/*N*/ 				if( SFX_ITEM_SET == rSource.GetItemState( nId, FALSE, &pItem ))
/*N*/ 					rDest.SetAttr( *pItem );
/*N*/ 				else
/*N*/ 					rDest.ResetAttr( nId );
/*N*/ 			}
/*N*/ 		}
/*N*/ 	}
/*N*/ 
/*N*/ 	// auch Pool-, Hilfe-Id's uebertragen
/*N*/ 	rDest.SetPoolFmtId( rSource.GetPoolFmtId() );
/*N*/ 	rDest.SetPoolHelpId( rSource.GetPoolHelpId() );
/*N*/ 	rDest.SetPoolHlpFileId( rSource.GetPoolHlpFileId() );
/*N*/ }


/*N*/ void SwDoc::ChgPageDesc( USHORT i, const SwPageDesc &rChged )
/*N*/ {
/*N*/ 	ASSERT( i < aPageDescs.Count(), "PageDescs ueberindiziert." );
/*N*/ 
/*N*/ 	SwPageDesc *pDesc = aPageDescs[i];
/*N*/ 
/*N*/ 	//Als erstes wird ggf. gespiegelt.
/*N*/ 	if ( rChged.GetUseOn() == PD_MIRROR )
/*N*/ 		((SwPageDesc&)rChged).Mirror();
/*N*/ 	else
/*N*/ 		//sonst Werte aus Master nach Left uebertragen.
/*N*/ 		::binfilter::lcl_DescSetAttr( ((SwPageDesc&)rChged).GetMaster(),
/*N*/ 					   ((SwPageDesc&)rChged).GetLeft() );
/*N*/ 
/*N*/ 	//NumType uebernehmen.
/*N*/ 	if( rChged.GetNumType().GetNumberingType() != pDesc->GetNumType().GetNumberingType() )
/*N*/ 	{
/*?*/ 		pDesc->SetNumType( rChged.GetNumType() );
/*?*/ 		// JP 30.03.99: Bug 64121 - den Seitennummernfeldern bescheid sagen,
/*?*/ 		//		das sich das Num-Format geaendert hat
/*?*/ 		GetSysFldType( RES_PAGENUMBERFLD )->UpdateFlds();
/*?*/ 		GetSysFldType( RES_REFPAGEGETFLD )->UpdateFlds();
/*?*/ 
/*?*/ 		// Wenn sich die Numerierungsart geaendert hat, koennte es QuoVadis/
/*?*/ 		// ErgoSum-Texte geben, die sich auf eine geaenderte Seite beziehen,
/*?*/ 		// deshalb werden die Fussnoten invalidiert
/*?*/ 		SwFtnIdxs& rFtnIdxs = GetFtnIdxs();
/*?*/ 		for( USHORT nPos = 0; nPos < rFtnIdxs.Count(); ++nPos )
/*?*/ 		{
/*?*/ 			SwTxtFtn *pTxtFtn = rFtnIdxs[ nPos ];
/*?*/ 			const SwFmtFtn &rFtn = pTxtFtn->GetFtn();
/*?*/ 			pTxtFtn->SetNumber( rFtn.GetNumber(), &rFtn.GetNumStr());
/*?*/ 		}
/*N*/ 	}
/*N*/ 
/*N*/ 	//Orientierung uebernehmen
/*N*/ 	pDesc->SetLandscape( rChged.GetLandscape() );
/*N*/ 
/*N*/ 	//Header abgleichen.
/*N*/ 	const SwFmtHeader &rHead = rChged.GetMaster().GetHeader();
/*N*/ 	if( DoesUndo() )
/*N*/ 	{
/*N*/ 		// hat sich an den Nodes etwas veraendert ?
/*N*/ 		//JP erstmal ein Hack, solange keine Headers/Footers Undofaehig sind
/*N*/ 		const SwFmtHeader &rOldHead = pDesc->GetMaster().GetHeader();
/*N*/ 		if( rHead.IsActive() != rOldHead.IsActive() ||
/*N*/ 			rChged.IsHeaderShared() != pDesc->IsHeaderShared() )
/*N*/ 		{
/*N*/ 			// erstmal werden alle Undo - Objecte geloescht.
/*N*/ 			ClearRedo();
/*N*/ 			DelAllUndoObj();
/*N*/ 		}
/*N*/ 	}
/*N*/ 	pDesc->GetMaster().SetAttr( rHead );
/*N*/ 	if ( rChged.IsHeaderShared() || !rHead.IsActive() )
/*N*/ 	{
/*N*/ 		//Left teilt sich den Header mit dem Master.
/*N*/ 		pDesc->GetLeft().SetAttr( pDesc->GetMaster().GetHeader() );
/*N*/ 	}
/*N*/ 	else if ( rHead.IsActive() )
/*N*/ 	{	//Left bekommt einen eigenen Header verpasst wenn das Format nicht
/*N*/ 		//bereits einen hat.
/*N*/ 		//Wenn er bereits einen hat und dieser auf die gleiche Section
/*N*/ 		//wie der Rechte zeigt, so muss er einen eigenen bekommen. Der
/*N*/ 		//Inhalt wird sinnigerweise kopiert.
/*N*/ 		const SwFmtHeader &rLeftHead = pDesc->GetLeft().GetHeader();
/*N*/ 		if ( !rLeftHead.IsActive() )
/*N*/ 		{
/*?*/ 			SwFmtHeader aHead( MakeLayoutFmt( RND_STD_HEADERL ) );
/*?*/ 			pDesc->GetLeft().SetAttr( aHead );
/*?*/ 			//Weitere Attribute (Raender, Umrandung...) uebernehmen.
/*?*/ 			::binfilter::lcl_DescSetAttr( *rHead.GetHeaderFmt(), *aHead.GetHeaderFmt(), FALSE);
/*N*/ 		}
/*N*/ 		else
/*N*/ 		{
/*N*/ 			const SwFrmFmt *pRight = rHead.GetHeaderFmt();
/*N*/ 			const SwFmtCntnt &aRCnt = pRight->GetCntnt();
/*N*/ 			const SwFmtCntnt &aLCnt = rLeftHead.GetHeaderFmt()->GetCntnt();
/*N*/ 			if ( (*aRCnt.GetCntntIdx()) == (*aLCnt.GetCntntIdx()) )
/*N*/ 			{
/*N*/ 				SwFrmFmt *pFmt = new SwFrmFmt( GetAttrPool(), "Header",
/*N*/ 												GetDfltFrmFmt() );
/*N*/ 				::binfilter::lcl_DescSetAttr( *pRight, *pFmt, FALSE );
/*N*/ 				//Der Bereich auf den das rechte Kopfattribut zeigt wird
/*N*/ 				//kopiert und der Index auf den StartNode in das linke
/*N*/ 				//Kopfattribut gehaengt.
/*N*/ 				SwNodeIndex aTmp( GetNodes().GetEndOfAutotext() );
/*N*/ 				SwStartNode* pSttNd = GetNodes().MakeEmptySection( aTmp, SwHeaderStartNode );
/*N*/ 				SwNodeRange aRange( aRCnt.GetCntntIdx()->GetNode(), 0,
/*N*/ 							*aRCnt.GetCntntIdx()->GetNode().EndOfSectionNode() );
/*N*/ 				aTmp = *pSttNd->EndOfSectionNode();
/*N*/ 				GetNodes()._Copy( aRange, aTmp, FALSE );
/*N*/ 
/*N*/ 				pFmt->SetAttr( SwFmtCntnt( pSttNd ) );
/*N*/ 				pDesc->GetLeft().SetAttr( SwFmtHeader( pFmt ) );
/*N*/ 			}
/*N*/ 			else
/*N*/ 				::binfilter::lcl_DescSetAttr( *pRight,
/*N*/ 							   *(SwFrmFmt*)rLeftHead.GetHeaderFmt(), FALSE );
/*N*/ 
/*N*/ 		}
/*N*/ 	}
/*N*/ 	pDesc->ChgHeaderShare( rChged.IsHeaderShared() );
/*N*/ 
/*N*/ 	//Footer abgleichen.
/*N*/ 	const SwFmtFooter &rFoot = rChged.GetMaster().GetFooter();
/*N*/ 	if( DoesUndo() )
/*N*/ 	{
/*N*/ 		// hat sich an den Nodes etwas veraendert ?
/*N*/ 		//JP erstmal ein Hack, solange keine Headers/Footers Undofaehig sind
/*N*/ 		const SwFmtFooter &rOldFoot = pDesc->GetMaster().GetFooter();
/*N*/ 		if( rFoot.IsActive() != rOldFoot.IsActive() ||
/*N*/ 			rChged.IsFooterShared() != pDesc->IsFooterShared() )
/*N*/ 		{
/*N*/ 			// erstmal werden alle Undo - Objecte geloescht.
/*N*/ 			ClearRedo();
/*N*/ 			DelAllUndoObj();
/*N*/ 		}
/*N*/ 	}
/*N*/ 	pDesc->GetMaster().SetAttr( rFoot );
/*N*/ 	if ( rChged.IsFooterShared() || !rFoot.IsActive() )
/*N*/ 		//Left teilt sich den Header mit dem Master.
/*N*/ 		pDesc->GetLeft().SetAttr( pDesc->GetMaster().GetFooter() );
/*N*/ 	else if ( rFoot.IsActive() )
/*N*/ 	{	//Left bekommt einen eigenen Footer verpasst wenn das Format nicht
/*?*/ 		//bereits einen hat.
/*?*/ 		//Wenn er bereits einen hat und dieser auf die gleiche Section
/*?*/ 		//wie der Rechte zeigt, so muss er einen eigenen bekommen. Der
/*?*/ 		//Inhalt wird sinnigerweise kopiert.
/*?*/ 		const SwFmtFooter &rLeftFoot = pDesc->GetLeft().GetFooter();
/*?*/ 		if ( !rLeftFoot.IsActive() )
/*?*/ 		{
/*?*/ 			SwFmtFooter aFoot( MakeLayoutFmt( RND_STD_FOOTER ) );
/*?*/ 			pDesc->GetLeft().SetAttr( aFoot );
/*?*/ 			//Weitere Attribute (Raender, Umrandung...) uebernehmen.
/*?*/ 			::binfilter::lcl_DescSetAttr( *rFoot.GetFooterFmt(), *aFoot.GetFooterFmt(), FALSE);
/*?*/ 		}
/*?*/ 		else
/*?*/ 		{
/*?*/ 			const SwFrmFmt *pRight = rFoot.GetFooterFmt();
/*?*/ 			const SwFmtCntnt &aRCnt = pRight->GetCntnt();
/*?*/ 			const SwFmtCntnt &aLCnt = rLeftFoot.GetFooterFmt()->GetCntnt();
/*?*/ 			if ( (*aRCnt.GetCntntIdx()) == (*aLCnt.GetCntntIdx()) )
/*?*/ 			{
/*?*/ 				SwFrmFmt *pFmt = new SwFrmFmt( GetAttrPool(), "Footer",
/*?*/ 												GetDfltFrmFmt() );
/*?*/ 				::binfilter::lcl_DescSetAttr( *pRight, *pFmt, FALSE );
/*?*/ 				//Der Bereich auf den das rechte Kopfattribut zeigt wird
/*?*/ 				//kopiert und der Index auf den StartNode in das linke
/*?*/ 				//Kopfattribut gehaengt.
/*?*/ 				SwNodeIndex aTmp( GetNodes().GetEndOfAutotext() );
/*?*/ 				SwStartNode* pSttNd = GetNodes().MakeEmptySection( aTmp, SwFooterStartNode );
/*?*/ 				SwNodeRange aRange( aRCnt.GetCntntIdx()->GetNode(), 0,
/*?*/ 							*aRCnt.GetCntntIdx()->GetNode().EndOfSectionNode() );
/*?*/ 				aTmp = *pSttNd->EndOfSectionNode();
/*?*/ 				GetNodes()._Copy( aRange, aTmp, FALSE );
/*?*/ 
/*?*/ 				pFmt->SetAttr( SwFmtCntnt( pSttNd ) );
/*?*/ 				pDesc->GetLeft().SetAttr( SwFmtFooter( pFmt ) );
/*?*/ 			}
/*?*/ 			else
/*?*/ 				::binfilter::lcl_DescSetAttr( *pRight,
/*?*/ 							   *(SwFrmFmt*)rLeftFoot.GetFooterFmt(), FALSE );
/*?*/ 		}
/*N*/ 	}
/*N*/ 	pDesc->ChgFooterShare( rChged.IsFooterShared() );
/*N*/ 
/*N*/ 	if ( pDesc->GetName() != rChged.GetName() )
/*?*/ 		pDesc->SetName( rChged.GetName() );
/*N*/ 
/*N*/ 	// Dadurch wird ein RegisterChange ausgeloest, wenn notwendig
/*N*/ 	pDesc->SetRegisterFmtColl( rChged.GetRegisterFmtColl() );
/*N*/ 
/*N*/ 	//Wenn sich das UseOn oder der Follow aendern muessen die
/*N*/ 	//Absaetze das erfahren.
/*N*/ 	BOOL bUseOn  = FALSE;
/*N*/ 	BOOL bFollow = FALSE;
/*N*/ 	if ( pDesc->GetUseOn() != rChged.GetUseOn() )
/*N*/ 	{   pDesc->SetUseOn( rChged.GetUseOn() );
/*N*/ 		bUseOn = TRUE;
/*N*/ 	}
/*N*/ 	if ( pDesc->GetFollow() != rChged.GetFollow() )
/*N*/ 	{	if ( rChged.GetFollow() == &rChged )
/*N*/ 		{	if ( pDesc->GetFollow() != pDesc )
/*?*/ 			{	pDesc->SetFollow( pDesc );
/*?*/ 				bFollow = TRUE;
/*?*/ 			}
/*N*/ 		}
/*N*/ 		else
/*N*/ 		{	pDesc->SetFollow( rChged.pFollow );
/*N*/ 			bFollow = TRUE;
/*N*/ 		}
/*N*/ 	}
/*N*/ 
/*N*/ 	if ( (bUseOn || bFollow) && GetRootFrm() )
/*N*/ 		//Layot benachrichtigen!
/*N*/ 		GetRootFrm()->CheckPageDescs( (SwPageFrm*)GetRootFrm()->Lower() );
/*N*/ 
/*N*/ 	//Jetzt noch die Seiten-Attribute uebernehmen.
/*N*/ 	::binfilter::lcl_DescSetAttr( rChged.GetMaster(), pDesc->GetMaster() );
/*N*/ 	::binfilter::lcl_DescSetAttr( rChged.GetLeft(), pDesc->GetLeft() );
/*N*/ 
/*N*/ 	//Wenn sich FussnotenInfo veraendert, so werden die Seiten
/*N*/ 	//angetriggert.
/*N*/ 	if( !(pDesc->GetFtnInfo() == rChged.GetFtnInfo()) )
/*N*/ 	{
/*?*/ 		pDesc->SetFtnInfo( rChged.GetFtnInfo() );
/*?*/ 		SwMsgPoolItem  aInfo( RES_PAGEDESC_FTNINFO );
/*?*/ 		{
/*?*/ 			SwClientIter aIter( pDesc->GetMaster() );
/*?*/ 			for( SwClient* pLast = aIter.First(TYPE(SwFrm)); pLast;
/*?*/ 					pLast = aIter.Next() )
/*?*/ 				pLast->Modify( &aInfo, 0 );
/*?*/ 		}
/*?*/ 		{
/*?*/ 			SwClientIter aIter( pDesc->GetLeft() );
/*?*/ 			for( SwClient* pLast = aIter.First(TYPE(SwFrm)); pLast;
/*?*/ 					pLast = aIter.Next() )
/*?*/ 				pLast->Modify( &aInfo, 0 );
/*?*/ 		}
/*N*/ 	}
/*N*/ 	SetModified();
/*N*/ }

/*************************************************************************
|*
|*	SwDoc::DelPageDesc()
|*
|* 	Beschreibung		Alle Descriptoren, deren Follow auf den zu loeschenden
|*		zeigen muessen angepasst werden.
|*	Ersterstellung		MA 25. Jan. 93
|*	Letzte Aenderung	JP 04.09.95
|*
|*************************************************************************/

//STRIP001 void lcl_RemoveFrms( SwFrmFmt& rFmt, FASTBOOL& rbFtnsRemoved )
//STRIP001 {
//STRIP001 	SwClientIter aIter( rFmt );
//STRIP001 	SwFrm *pFrm;
//STRIP001 	for( pFrm = (SwFrm*)aIter.First(TYPE(SwFrm)); pFrm;
//STRIP001 			pFrm = (SwFrm*)aIter.Next() )
//STRIP001 		if ( !rbFtnsRemoved && pFrm->IsPageFrm() &&
//STRIP001 				((SwPageFrm*)pFrm)->IsFtnPage() )
//STRIP001 		{
//STRIP001 			rFmt.GetDoc()->GetRootFrm()->RemoveFtns( 0, FALSE, TRUE );
//STRIP001 			rbFtnsRemoved = TRUE;
//STRIP001 		}
//STRIP001 		else
//STRIP001 		{
//STRIP001 			pFrm->Cut();
//STRIP001 			delete pFrm;
//STRIP001 		}
//STRIP001 }


//STRIP001 void SwDoc::DelPageDesc( USHORT i )
//STRIP001 {
//STRIP001 	ASSERT( i < aPageDescs.Count(), "PageDescs ueberindiziert." );
//STRIP001 	ASSERT( i != 0, "Default Pagedesc loeschen is nicht." );
//STRIP001 	if ( i == 0 )
//STRIP001 		return;
//STRIP001 
//STRIP001 	SwPageDesc *pDel = aPageDescs[i];
//STRIP001 
//STRIP001 	SwFmtPageDesc aDfltDesc( aPageDescs[0] );
//STRIP001 	SwClientIter aIter( *pDel );
//STRIP001 	SwClient* pLast;
//STRIP001 	while( 0 != ( pLast = aIter.GoRoot() ))
//STRIP001 	{
//STRIP001 		if( pLast->ISA( SwFmtPageDesc ) )
//STRIP001 		{
//STRIP001 			const SwModify* pMod = ((SwFmtPageDesc*)pLast)->GetDefinedIn();
//STRIP001 			if ( pMod )
//STRIP001 			{
//STRIP001 				if( pMod->ISA( SwCntntNode ) )
//STRIP001 					((SwCntntNode*)pMod)->SetAttr( aDfltDesc );
//STRIP001 				else if( pMod->ISA( SwFmt ))
//STRIP001 					((SwFmt*)pMod)->SetAttr( aDfltDesc );
//STRIP001 				else
//STRIP001 				{
//STRIP001 					ASSERT( !this, "was ist das fuer ein Mofify-Obj?" );
//STRIP001 					aPageDescs[0]->Add( pLast );
//STRIP001 				}
//STRIP001 			}
//STRIP001 			else	//Es kann noch eine Undo-Kopie existieren
//STRIP001 				aPageDescs[0]->Add( pLast );
//STRIP001 		}
//STRIP001 
//STRIP001 		BOOL bFtnInf = FALSE;
//STRIP001 		if ( TRUE == (bFtnInf = pLast == pFtnInfo->GetPageDescDep()) ||
//STRIP001 			 pLast == pEndNoteInfo->GetPageDescDep() )
//STRIP001 		{
//STRIP001 			aPageDescs[0]->Add( pLast );
//STRIP001 			if ( GetRootFrm() )
//STRIP001 				GetRootFrm()->CheckFtnPageDescs( !bFtnInf );
//STRIP001 		}
//STRIP001 	}
//STRIP001 
//STRIP001 	for ( USHORT j = 0; j < aPageDescs.Count(); ++j )
//STRIP001 	{
//STRIP001 		if ( aPageDescs[j]->GetFollow() == pDel )
//STRIP001 		{
//STRIP001 			aPageDescs[j]->SetFollow( 0 );
//STRIP001 			//Clients des PageDesc sind die Attribute, denen sagen wir bescheid.
//STRIP001 			//die Attribute wiederum reichen die Meldung an die Absaetze weiter.
//STRIP001 
//STRIP001 			//Layot benachrichtigen!
//STRIP001 			if( GetRootFrm() )  // ist nicht immer vorhanden!! (Orginizer)
//STRIP001 				GetRootFrm()->CheckPageDescs( (SwPageFrm*)GetRootFrm()->Lower() );
//STRIP001 		}
//STRIP001 	}
//STRIP001 
//STRIP001 	if( GetRootFrm() )        // ist nicht immer vorhanden!! (Orginizer)
//STRIP001 	{
//STRIP001 		//Wenn jetzt noch irgendwelche Seiten auf die FrmFmt'e (Master und Left)
//STRIP001 		//Zeigen (z.B. irgendwelche Fussnotenseiten), so muessen die Seiten
//STRIP001 		//vernichtet werden.
//STRIP001 
//STRIP001 		// Wenn wir auf Endnotenseiten stossen, schmeissen wir alle Fussnoten weg,
//STRIP001 		// anders kann die Reihenfolge der Seiten (FollowsPageDescs usw.)
//STRIP001 		// nicht garantiert werden.
//STRIP001 		FASTBOOL bFtnsRemoved = FALSE;
//STRIP001 
//STRIP001 		::lcl_RemoveFrms( pDel->GetMaster(), bFtnsRemoved );
//STRIP001 		::lcl_RemoveFrms( pDel->GetLeft(), bFtnsRemoved );
//STRIP001 	}
//STRIP001 
//STRIP001 	aPageDescs.Remove( i );
//STRIP001 	delete pDel;
//STRIP001 	SetModified();
//STRIP001 }



/*************************************************************************
|*
|*	SwDoc::MakePageDesc()
|*
|*	Ersterstellung		MA 25. Jan. 93
|*	Letzte Aenderung	MA 20. Aug. 93
|*
|*************************************************************************/

/*N*/ USHORT SwDoc::MakePageDesc( const String &rName, const SwPageDesc *pCpy,
/*N*/                             BOOL bRegardLanguage)
/*N*/ {
/*N*/ 	SwPageDesc *pNew;
/*N*/ 	if( pCpy )
/*N*/ 	{
/*?*/ 		pNew = new SwPageDesc( *pCpy );
/*?*/ 		pNew->SetName( rName );
/*?*/ 		if( rName != pCpy->GetName() )
/*?*/ 		{
/*?*/ 			pNew->SetPoolFmtId( USHRT_MAX );
/*?*/ 			pNew->SetPoolHelpId( USHRT_MAX );
/*?*/ 			pNew->SetPoolHlpFileId( UCHAR_MAX );
/*?*/ 		}
/*?*/ 	}
/*N*/ 	else
/*N*/ 	{
/*N*/ 		pNew = new SwPageDesc( rName, GetDfltFrmFmt(), this );
/*N*/ 		//Default-Seitenformat einstellen.
/*N*/ 		::binfilter::lcl_DefaultPageFmt( USHRT_MAX, pNew->GetMaster(), pNew->GetLeft(), 
/*N*/ 							  GetPrt(), FALSE );
/*N*/ 
/*N*/         SvxFrameDirection aFrameDirection = bRegardLanguage ?
/*N*/             GetDefaultFrameDirection(GetAppLanguage())
/*N*/             : FRMDIR_HORI_LEFT_TOP;
/*N*/ 
/*N*/ 		pNew->GetMaster().SetAttr( SvxFrameDirectionItem(aFrameDirection) );
/*N*/ 		pNew->GetLeft().SetAttr( SvxFrameDirectionItem(aFrameDirection) );
/*N*/ 
/*N*/     	if( GetPrt() )
/*N*/ 			pNew->SetLandscape( ORIENTATION_LANDSCAPE ==
/*N*/ 								GetPrt()->GetOrientation() );
/*N*/ 	}
/*N*/ 	aPageDescs.Insert( pNew, aPageDescs.Count() );
/*N*/ 	SetModified();
/*N*/ 	return (aPageDescs.Count()-1);
/*N*/ }

/*N*/ SwPageDesc* SwDoc::FindPageDescByName( const String& rName, USHORT* pPos ) const
/*N*/ {
/*N*/ 	SwPageDesc* pRet = 0;
/*N*/ 	if( pPos ) *pPos = USHRT_MAX;
/*N*/ 
/*N*/ 	for( USHORT n = 0, nEnd = aPageDescs.Count(); n < nEnd; ++n )
/*N*/ 		if( aPageDescs[ n ]->GetName() == rName )
/*N*/ 		{
/*N*/ 			pRet = aPageDescs[ n ];
/*N*/ 			if( pPos )
/*N*/ 				*pPos = n;
/*N*/ 			break;
/*N*/ 		}
/*N*/ 	return pRet;
/*N*/ }

/******************************************************************************
 *	Methode		:	void SwDoc::SetPrt( SfxPrinter *pP )
 *	Beschreibung:
 *	Erstellt	:	OK 27.10.94 10:20
 *	Aenderung	:	MA 26. Mar. 98
 ******************************************************************************/

/*N*/ void SwDoc::PrtDataChanged()
/*N*/ {
/*N*/ //!!!!!!!! Bei Aenderungen hier bitte ggf. InJobSetup im Sw3io mitpflegen
/*N*/ 
/*N*/ 	SwWait *pWait = 0;
/*N*/ 	BOOL bEndAction = FALSE;
/*N*/ 
/*N*/ 	if( GetDocShell() )
/*N*/ 		GetDocShell()->UpdateFontList();
/*N*/ 
/*N*/ 	BOOL bDraw = TRUE;
/*N*/ 	if ( GetRootFrm() )
/*N*/ 	{
/*?*/ 		ViewShell *pSh = GetRootFrm()->GetCurrShell();
/*?*/ 		if( !IsBrowseMode() || ( pSh && pSh->GetViewOptions()->IsPrtFormat() ) )
/*?*/ 		{
/*?*/ 			if ( GetDocShell() )
/*?*/ 				pWait = new SwWait( *GetDocShell(), TRUE );
/*?*/ 
/*?*/ 			GetRootFrm()->StartAllAction();
/*?*/ 			bEndAction = TRUE;
/*?*/ 
/*?*/ 			bDraw = FALSE;
/*?*/ 			if( pDrawModel )
/*?*/ 			    pDrawModel->SetRefDevice( _GetRefDev() );
/*?*/ 
/*?*/ 			pFntCache->Flush();
/*?*/ 			GetRootFrm()->InvalidateAllCntnt();
/*?*/ 
/*?*/ 			if ( pSh )
/*?*/ 			{
/*?*/ 				do
/*?*/ 			                {
/*?*/                     pSh->InitPrt( pPrt );
/*?*/ 					pSh = (ViewShell*)pSh->GetNext();
/*?*/                 }
/*?*/                 while ( pSh != GetRootFrm()->GetCurrShell() );
/*?*/ 			}
/*?*/ 
/*?*/ 		}
/*N*/ 	}
/*N*/     if ( bDraw && pDrawModel && _GetRefDev() != pDrawModel->GetRefDevice() )
/*N*/         pDrawModel->SetRefDevice( _GetRefDev() );
/*N*/ 
/*N*/ 	PrtOLENotify( TRUE );
/*N*/ 
/*N*/ 	if ( bEndAction )
/*?*/ 		GetRootFrm()->EndAllAction();
/*N*/ 	delete pWait;
/*N*/ }

//Zur Laufzeit sammeln wir die GlobalNames der Server, die keine
//Benachrichtigung zu Druckerwechseln wuenschen. Dadurch sparen wir
//das Laden vieler Objekte (gluecklicherweise werden obendrein alle
//Fremdobjekte unter einer ID abgebuildet). Init und DeInit vom Array
//ist in init.cxx zu finden.
extern SvPtrarr *pGlobalOLEExcludeList;

/*N*/ void SwDoc::PrtOLENotify( BOOL bAll )
/*N*/ {
/*N*/ 	SwFEShell *pShell = 0;
/*N*/ 	if ( GetRootFrm() && GetRootFrm()->GetCurrShell() )
/*N*/ 	{
/*N*/ 		ViewShell *pSh = GetRootFrm()->GetCurrShell();
/*N*/ 		if ( !pSh->ISA(SwFEShell) )
/*N*/ 			do
/*?*/ 			{	pSh = (ViewShell*)pSh->GetNext();
/*?*/ 			} while ( !pSh->ISA(SwFEShell) &&
/*?*/ 					  pSh != GetRootFrm()->GetCurrShell() );
/*N*/ 
/*N*/ 		if ( pSh->ISA(SwFEShell) )
/*N*/ 			pShell = (SwFEShell*)pSh;
/*N*/ 	}
/*N*/ 	if ( !pShell )
/*N*/ 	{
/*N*/ 		//Das hat ohne Shell und damit ohne Client keinen Sinn, weil nur darueber
/*N*/ 		//die Kommunikation bezueglich der Groessenaenderung implementiert ist.
/*N*/ 		//Da wir keine Shell haben, merken wir uns diesen unguenstigen
/*N*/ 		//Zustand am Dokument, dies wird dann beim Erzeugen der ersten Shell
/*N*/ 		//nachgeholt.
/*N*/ 		bOLEPrtNotifyPending = TRUE;
/*N*/ 		if ( bAll )
/*N*/ 			bAllOLENotify = TRUE;
/*N*/ 	}
/*N*/ 	else
/*N*/ 	{
/*N*/ 		if ( bAllOLENotify )
/*N*/ 			bAll = TRUE;
/*N*/ 
/*N*/ 		bOLEPrtNotifyPending = bAllOLENotify = FALSE;
/*N*/ 
/*N*/ 
/*N*/ 		SwOLENodes *pNodes = 0;
/*N*/ 		SwClientIter aIter( *(SwModify*)GetDfltGrfFmtColl() );
/*N*/ 		for( SwCntntNode* pNd = (SwCntntNode*)aIter.First( TYPE( SwCntntNode ) );
/*N*/ 			 pNd;
/*N*/ 			 pNd = (SwCntntNode*)aIter.Next() )
/*N*/ 		{
/*N*/ 			SwOLENode *pONd;
/*N*/ 			if ( 0 != (pONd = pNd->GetOLENode()) &&
/*N*/ 				 (bAll || pONd->IsOLESizeInvalid()) )
/*N*/ 			{
/*N*/ 				if ( !pNodes  )
/*N*/ 					pNodes = new SwOLENodes;
/*N*/ 				pNodes->Insert( pONd, pNodes->Count() );
/*N*/ 			}
/*N*/ 		}
/*N*/ 
/*N*/ 		if ( pNodes )
/*N*/ 		{
/*N*/ 			::binfilter::StartProgress( STR_STATSTR_SWGPRTOLENOTIFY,
/*N*/ 							 0, pNodes->Count(), GetDocShell());
/*N*/ 			GetRootFrm()->StartAllAction();
/*N*/ 
/*N*/ 			for( USHORT i = 0; i < pNodes->Count(); ++i )
/*N*/ 			{
/*N*/ 				::binfilter::SetProgressState( i, GetDocShell() );
/*N*/ 
/*N*/ 				SwOLENode* pOLENd = (*pNodes)[i];
/*N*/ 				pOLENd->SetOLESizeInvalid( FALSE );
/*N*/ 
/*N*/ 				//Ersteinmal die Infos laden und festellen ob das Teil nicht
/*N*/ 				//schon in der Exclude-Liste steht
/*N*/ 				SvGlobalName aName;
/*N*/ 
/*N*/ 				if ( !pOLENd->GetOLEObj().IsOleRef() )	//Noch nicht geladen
/*N*/ 				{
/*N*/ 					String sBaseURL( INetURLObject::GetBaseURL() );
/*N*/ 					const SfxMedium *pMedium;
/*N*/ 					if( 0 != (pMedium = GetDocShell()->GetMedium()) &&
/*N*/ 						pMedium->GetName() != sBaseURL )
/*N*/ 						INetURLObject::SetBaseURL( pMedium->GetName() );
/*N*/ 					SvInfoObjectRef xInfo = GetPersist()->Find( pOLENd->GetOLEObj().GetName() );
/*N*/ 					if ( xInfo.Is() )	//Muss normalerweise gefunden werden
/*N*/ 						aName = xInfo->GetClassName();
/*N*/ 					INetURLObject::SetBaseURL( sBaseURL );
/*N*/ 				}
/*N*/ 				else
/*?*/ 					aName = pOLENd->GetOLEObj().GetOleRef()->GetClassName();
/*N*/ 
/*N*/ 				BOOL bFound = FALSE;
/*N*/ 				for ( USHORT i = 0;
/*N*/ 					  i < pGlobalOLEExcludeList->Count() && !bFound;
/*N*/ 					  ++i )
/*N*/ 				{
/*N*/ 					bFound = *(SvGlobalName*)(*pGlobalOLEExcludeList)[i] ==
/*N*/ 									aName;
/*N*/ 				}
/*N*/ 				if ( bFound )
/*N*/ 					continue;
/*N*/ 
/*N*/ 				//Kennen wir nicht, also muss das Objekt geladen werden.
/*N*/ 				//Wenn es keine Benachrichtigung wuenscht
/*N*/ 				SvEmbeddedObjectRef xRef( (SvInPlaceObject*) pOLENd->GetOLEObj().GetOleRef() );
/*N*/ 				if ( xRef ) //Kaputt?
/*N*/ 				{
/*N*/ 					if ( SVOBJ_MISCSTATUS_RESIZEONPRINTERCHANGE & xRef->GetMiscStatus())
/*N*/ 					{
/*N*/ 						if ( pOLENd->GetFrm() )
/*N*/ 						{
/*N*/ 							xRef->OnDocumentPrinterChanged( pPrt );
/*N*/ 							pShell->CalcAndSetScale( xRef );//Client erzeugen lassen.
/*N*/ 						}
/*N*/ 						else
/*N*/ 							pOLENd->SetOLESizeInvalid( TRUE );
/*N*/ 					}
/*N*/ 					else
/*N*/ 						pGlobalOLEExcludeList->Insert(
/*N*/ 								new SvGlobalName( xRef->GetClassName()),
/*N*/ 								pGlobalOLEExcludeList->Count() );
/*N*/ 				}
/*N*/ 			}
/*N*/ 			delete pNodes;
/*N*/ 			GetRootFrm()->EndAllAction();
/*N*/ 			::binfilter::EndProgress( GetDocShell() );
/*N*/ 		}
/*N*/ 	}
/*N*/ }

/*N*/ void SwDoc::SetVirDev( VirtualDevice* pVd, sal_Bool bCallVirDevDataChanged )
/*N*/ {
/*N*/     if ( (ULONG)pVirDev != (ULONG)pVd )
/*N*/     {
/*N*/         delete pVirDev;
/*N*/         pVirDev = pVd;
/*N*/     }
/*N*/ }

/*N*/ void SwDoc::SetPrt( SfxPrinter *pP, sal_Bool bCallPrtDataChanged )
/*N*/ {
/*N*/ 	ASSERT( pP, "Kein Drucker!" );
/*N*/ 
/*N*/ 	const BOOL bInitPageDesc = pPrt == 0;
/*N*/ 
/*N*/ 	if ( (ULONG) pP != (ULONG) pPrt)
/*N*/ 	{
/*N*/ 		delete pPrt;
/*N*/ 		pPrt = pP;
/*N*/ 	}
/*N*/     // OD 05.03.2003 #107870# - first adjust page description, before trigger formatting.
/*N*/     if( bInitPageDesc )
/*N*/     {
/*N*/         // JP 17.04.97: Bug 38924 - falls noch kein Drucker gesetzt war
/*N*/         //              und der PageDesc nicht eingelesen wurde
/*N*/         //      -> passe an den Drucker an
/*N*/         if( pPrt && LONG_MAX == _GetPageDesc( 0 ).GetMaster().GetFrmSize().GetWidth() )
/*N*/             _GetPageDesc( 0 ).SetLandscape( ORIENTATION_LANDSCAPE ==
/*N*/                                             pPrt->GetOrientation() );
/*N*/ 
/*N*/         //MA 11. Mar. 97: Das sollten wir fuer alle Formate tun, weil die
/*N*/         //Werte auf LONG_MAX initalisiert sind (spaetes anlegen des Druckers)
/*N*/         //und die Reader u.U. "unfertige" Formate stehenlassen.
/*N*/         for ( USHORT i = 0; i < GetPageDescCnt(); ++i )
/*N*/         {
/*N*/             SwPageDesc& rDesc = _GetPageDesc( i );
/*N*/             ::binfilter::lcl_DefaultPageFmt( rDesc.GetPoolFmtId(), rDesc.GetMaster(),
/*N*/                                   rDesc.GetLeft(), pPrt, TRUE );
/*N*/         }
/*N*/     }
/*N*/ 
/*N*/     if ( bCallPrtDataChanged )
/*N*/ 		PrtDataChanged();
/*N*/ }

/*N*/ void SwDoc::SetUseVirtualDevice( sal_Bool bFlag )
/*N*/ {
/*N*/     if ( !IsUseVirtualDevice() != !bFlag )
/*N*/     {
/*N*/         _SetUseVirtualDevice( bFlag );
/*N*/         PrtDataChanged();
/*N*/         SetModified();
/*N*/     }
/*N*/ 
/*N*/ }

/*
 *	Kleiner Hack;
 *
const SwPageDesc& SwDoc::GetPageDesc( USHORT i ) const
{
    if( !i && !aPageDescs.Count() )            // noch keiner vorhanden?
        ((SwDoc*)this)->InitPageDescs();		//Default PageDescriptor
    return *aPageDescs[i];
}

SwPageDesc& SwDoc::_GetPageDesc( USHORT i ) const
{
    if( !i && !aPageDescs.Count() )			// noch keiner vorhanden?
        ((SwDoc*)this)->InitPageDescs();		//Default PageDescriptor
    return *aPageDescs[i];
}
*/



/*N*/ IMPL_LINK( SwDoc, DoUpdateModifiedOLE, Timer *, pTimer )
/*N*/ {
/*N*/ 	SwFEShell* pSh = (SwFEShell*)GetEditShell();
/*N*/ 	if( pSh )
/*N*/ 	{
/*N*/ 		bOLEPrtNotifyPending = bAllOLENotify = FALSE;
/*N*/ 
/*N*/ 		SwOLENodes aOLENodes;
/*N*/ 		SwClientIter aIter( *(SwModify*)GetDfltGrfFmtColl() );
/*N*/ 		for( SwCntntNode* pNd = (SwCntntNode*)aIter.First( TYPE( SwCntntNode ) );
/*N*/ 			 pNd;
/*N*/ 			 pNd = (SwCntntNode*)aIter.Next() )
/*N*/ 		{
/*N*/ 			SwOLENode *pONd = pNd->GetOLENode();
/*N*/ 			if( pONd && pONd->IsOLESizeInvalid() )
/*N*/ 			{
/*N*/ 				aOLENodes.Insert( pONd, aOLENodes.Count() );
/*N*/ 			}
/*N*/ 		}
/*N*/ 
/*N*/ 		if( aOLENodes.Count() )
/*N*/ 		{
/*N*/ 			::binfilter::StartProgress( STR_STATSTR_SWGPRTOLENOTIFY,
/*N*/ 							 0, aOLENodes.Count(), GetDocShell());
/*N*/ 			GetRootFrm()->StartAllAction();
/*N*/ 			SwMsgPoolItem aMsgHint( RES_UPDATE_ATTR );
/*N*/ 
/*N*/ 			for( USHORT i = 0; i < aOLENodes.Count(); ++i )
/*N*/ 			{
/*N*/ 				::binfilter::SetProgressState( i, GetDocShell() );
/*N*/ 
/*N*/ 				SwOLENode* pOLENd = aOLENodes[i];
/*N*/ 				pOLENd->SetOLESizeInvalid( FALSE );
/*N*/ 
/*N*/ 				//Kennen wir nicht, also muss das Objekt geladen werden.
/*N*/ 				//Wenn es keine Benachrichtigung wuenscht
/*N*/ 				SvEmbeddedObjectRef xRef( (SvInPlaceObject*)
/*N*/ 										pOLENd->GetOLEObj().GetOleRef() );
/*N*/ 				if( xRef ) //Kaputt?
/*N*/ 				{
/*N*/ 					if( SVOBJ_MISCSTATUS_RESIZEONPRINTERCHANGE &
/*N*/ 							xRef->GetMiscStatus() )
/*N*/ 					{
/*N*/ 						if( pOLENd->GetFrm() )
/*N*/ 						{
/*N*/ 							xRef->OnDocumentPrinterChanged( pPrt );
/*N*/ 							pSh->CalcAndSetScale( xRef );//Client erzeugen lassen.
/*N*/ 						}
/*N*/ 						else
/*?*/ 							pOLENd->SetOLESizeInvalid( TRUE );
/*N*/ 					}
/*N*/ 					// repaint it
/*N*/ 					pOLENd->Modify( &aMsgHint, &aMsgHint );
/*N*/ 				}
/*N*/ 			}
/*N*/ 			GetRootFrm()->EndAllAction();
/*N*/ 			::binfilter::EndProgress( GetDocShell() );
/*N*/ 		}
/*N*/ 	}
/*N*/ 	return 0;
/*N*/ }




}
