/*************************************************************************
 *
 *  $RCSfile: sw_wrtasc.cxx,v $
 *
 *  $Revision: 1.2 $
 *
 *  last change: $Author: mwu $ $Date: 2003-11-06 07:52:14 $
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

#ifndef _STREAM_HXX
#include <tools/stream.hxx>
#endif

#ifndef _PAM_HXX
#include <pam.hxx>
#endif
#ifndef _DOC_HXX
#include <doc.hxx>
#endif
#ifndef _NDTXT_HXX
#include <ndtxt.hxx>
#endif
#ifndef _MDIEXP_HXX
#include <mdiexp.hxx>			// ...Percent()
#endif
#ifndef _DOCARY_HXX
#include <docary.hxx>
#endif
#ifndef _FMTCNTNT_HXX //autogen
#include <fmtcntnt.hxx>
#endif
#ifndef _FRMFMT_HXX //autogen
#include <frmfmt.hxx>
#endif
#ifndef _WRTASC_HXX
#include <wrtasc.hxx>
#endif

#ifndef _STATSTR_HRC
#include <statstr.hrc>			// ResId fuer Statusleiste
#endif
namespace binfilter {

//-----------------------------------------------------------------

/*N*/ SwASCWriter::SwASCWriter( const String& rFltNm )
/*N*/ {
/*N*/ 	SwAsciiOptions aNewOpts;
/*N*/ 
/*N*/ 	switch( 5 <= rFltNm.Len() ? rFltNm.GetChar( 4 ) : 0 )
/*N*/ 	{
/*?*/ 	case 'D':
/*?*/ #if !defined(PM2)
/*?*/ 				aNewOpts.SetCharSet( RTL_TEXTENCODING_IBM_850 );
/*?*/ 				aNewOpts.SetParaFlags( LINEEND_CRLF );
/*?*/ #endif
/*?*/ 				if( 5 < rFltNm.Len() )
/*?*/ 					switch( rFltNm.Copy( 5 ).ToInt32() )
/*?*/ 					{
/*?*/ 					case 437: aNewOpts.SetCharSet( RTL_TEXTENCODING_IBM_437 );	break;
/*?*/ 					case 850: aNewOpts.SetCharSet( RTL_TEXTENCODING_IBM_850 );	break;
/*?*/ 					case 860: aNewOpts.SetCharSet( RTL_TEXTENCODING_IBM_860 );	break;
/*?*/ 					case 861: aNewOpts.SetCharSet( RTL_TEXTENCODING_IBM_861 );	break;
/*?*/ 					case 863: aNewOpts.SetCharSet( RTL_TEXTENCODING_IBM_863 );	break;
/*?*/ 					case 865: aNewOpts.SetCharSet( RTL_TEXTENCODING_IBM_865 );	break;
/*?*/ 					}
/*?*/ 				break;
/*?*/ 
/*?*/ 	case 'A':
/*?*/ #if !defined(WIN) && !defined(WNT)
/*?*/ 				aNewOpts.SetCharSet( RTL_TEXTENCODING_MS_1252 );
/*?*/ 				aNewOpts.SetParaFlags( LINEEND_CRLF );
/*?*/ #endif
/*?*/ 				break;
/*?*/ 
/*?*/ 	case 'M':
/*?*/ #if !defined(MAC)
/*?*/ 				aNewOpts.SetCharSet( RTL_TEXTENCODING_APPLE_ROMAN );
/*?*/ 				aNewOpts.SetParaFlags( LINEEND_CR );
/*?*/ #endif
/*?*/ 				break;
/*?*/ 
/*?*/ 	case 'X':
/*?*/ #if !defined(UNX)
/*?*/ 				aNewOpts.SetCharSet( RTL_TEXTENCODING_MS_1252 );
/*?*/ 				aNewOpts.SetParaFlags( LINEEND_LF );
/*?*/ #endif
/*?*/ 				break;
/*?*/ 
/*N*/ 	default:
/*N*/ 		if( rFltNm.Copy( 4 ).EqualsAscii( "_DLG" ))
/*N*/ 		{
/*N*/ 			// use the options
/*N*/ 			aNewOpts = GetAsciiOptions();
/*N*/ 		}
/*N*/ 	}
/*N*/ 	SetAsciiOptions( aNewOpts );
/*N*/ }

/*N*/ SwASCWriter::~SwASCWriter() {}

/*N*/ ULONG SwASCWriter::WriteStream()
/*N*/ {
/*N*/ 	sal_Char cLineEnd[ 3 ];
/*N*/ 	sal_Char* pCEnd = cLineEnd;
/*N*/ 	if( bASCII_ParaAsCR )			// falls vorgegeben ist.
/*?*/ 		*pCEnd++ = '\015';
/*N*/ 	else if( bASCII_ParaAsBlanc )
/*?*/ 		*pCEnd++ = ' ';
/*N*/ 	else
/*N*/ 		switch( GetAsciiOptions().GetParaFlags() )
/*N*/ 		{
/*?*/ 		case LINEEND_CR:    *pCEnd++ = '\015'; break;
/*?*/ 		case LINEEND_LF:	*pCEnd++ = '\012'; break;
/*N*/ 		case LINEEND_CRLF:	*pCEnd++ = '\015', *pCEnd++ = '\012'; break;
/*N*/ 		}
/*N*/ 	*pCEnd = 0;
/*N*/ 
/*N*/ 	sLineEnd.AssignAscii( cLineEnd );
/*N*/ 
/*N*/ 	long nMaxNode = pDoc->GetNodes().Count();
/*N*/ 
/*N*/ 	if( bShowProgress )
/*N*/ 		::binfilter::StartProgress( STR_STATSTR_W4WWRITE, 0, nMaxNode, pDoc->GetDocShell() );
/*N*/ 
/*N*/ 	SwPaM* pPam = pOrigPam;
/*N*/ 
/*N*/ 	BOOL bWriteSttTag = bUCS2_WithStartChar &&
/*M*/         (RTL_TEXTENCODING_UCS2 == GetAsciiOptions().GetCharSet() ||
/*M*/ 		RTL_TEXTENCODING_UTF8 == GetAsciiOptions().GetCharSet());
/*N*/ 
/*N*/ 	rtl_TextEncoding eOld = Strm().GetStreamCharSet();
/*N*/ 	Strm().SetStreamCharSet( GetAsciiOptions().GetCharSet() );
/*N*/ 
/*N*/ 	// gebe alle Bereich des Pams in das ASC-File aus.
/*N*/ 	do {
/*N*/ 		BOOL bTstFly = TRUE;
/*N*/ 		while( pCurPam->GetPoint()->nNode.GetIndex() < pCurPam->GetMark()->nNode.GetIndex() ||
/*N*/ 			  (pCurPam->GetPoint()->nNode.GetIndex() == pCurPam->GetMark()->nNode.GetIndex() &&
/*N*/ 			   pCurPam->GetPoint()->nContent.GetIndex() <= pCurPam->GetMark()->nContent.GetIndex()) )
/*N*/ 		{
/*N*/ 			SwTxtNode* pNd = pCurPam->GetPoint()->nNode.GetNode().GetTxtNode();
/*N*/ 			if( pNd )
/*N*/ 			{
/*N*/ 				// sollten nur Rahmen vorhanden sein?
/*N*/ 				// (Moeglich, wenn Rahmen-Selektion ins Clipboard
/*N*/ 				// gestellt wurde)
/*N*/ 				if( bTstFly && bWriteAll &&
/*N*/ 					// keine Laenge
/*N*/ 					!pNd->GetTxt().Len() &&
/*N*/ 					// Rahmen vorhanden
/*N*/ 					pDoc->GetSpzFrmFmts()->Count() &&
/*N*/ 					// nur ein Node im Array
/*N*/ 					pDoc->GetNodes().GetEndOfExtras().GetIndex() + 3 ==
/*N*/ 					pDoc->GetNodes().GetEndOfContent().GetIndex() &&
/*N*/ 					// und genau der ist selektiert
/*N*/ 					pDoc->GetNodes().GetEndOfContent().GetIndex() - 1 ==
/*N*/ 					pCurPam->GetPoint()->nNode.GetIndex() )
/*N*/ 				{
/*N*/ 					// dann den Inhalt vom Rahmen ausgeben.
/*N*/ 					// dieser steht immer an Position 0 !!
/*?*/ 					SwFrmFmt* pFmt = (*pDoc->GetSpzFrmFmts())[ 0 ];
/*?*/ 					const SwNodeIndex* pIdx = pFmt->GetCntnt().GetCntntIdx();
/*?*/ 					if( pIdx )
/*?*/ 					{
/*?*/ 						DBG_ASSERT(0, "STRIP"); //STRIP001 delete pCurPam;
//STRIP001 /*?*/ 						pCurPam = NewSwPaM( *pDoc, pIdx->GetIndex(),
//STRIP001 /*?*/ 									pIdx->GetNode().EndOfSectionIndex() );
//STRIP001 /*?*/ 						pCurPam->Exchange();
//STRIP001 /*?*/ 						continue;		// while-Schleife neu aufsetzen !!
/*N*/ 					}
/*N*/ 				}
/*N*/ 				else
/*M*/ 				{
/*M*/ 					if (bWriteSttTag)
/*M*/ 					{
/*M*/                         switch(GetAsciiOptions().GetCharSet())
/*M*/                         {
/*M*/                             case RTL_TEXTENCODING_UTF8:
/*M*/                                 Strm() << BYTE(0xEF) << BYTE(0xBB) << 
/*M*/                                     BYTE(0xBF);
/*M*/                                 break;
/*M*/                             case RTL_TEXTENCODING_UCS2:
/*M*/ 						        //Strm().StartWritingUnicodeText();
/*M*/                                 Strm().SetEndianSwap(FALSE);
/*M*/ #ifdef __LITTLEENDIAN
/*M*/                                 Strm() << BYTE(0xFF) << BYTE(0xFE);
/*M*/ #else
/*M*/                                 Strm() << BYTE(0xFE) << BYTE(0xFF);
/*M*/ #endif
/*M*/                                 break;
/*M*/ 
/*M*/                         }
/*?*/ 						bWriteSttTag = FALSE;
/*N*/ 					}
/*N*/ 					Out( aASCNodeFnTab, *pNd, *this );
/*N*/ 				}
/*N*/ 				bTstFly = FALSE;		// eimal Testen reicht
/*N*/ 			}
/*N*/ 
/*N*/ 			if( !pCurPam->Move( fnMoveForward, fnGoNode ) )
/*N*/ 				break;
/*N*/ 
/*N*/ 			if( bShowProgress )
/*N*/ 				::binfilter::SetProgressState( pCurPam->GetPoint()->nNode.GetIndex(),
/*N*/ 									pDoc->GetDocShell() );   // Wie weit ?
/*N*/ 
/*N*/ 		}
/*N*/ 	} while( CopyNextPam( &pPam ) );		// bis alle Pam bearbeitet
/*N*/ 
/*N*/ 	Strm().SetStreamCharSet( eOld );
/*N*/ 
/*N*/ 	if( bShowProgress )
/*N*/ 		::binfilter::EndProgress( pDoc->GetDocShell() );
/*N*/ 
/*N*/ 	return 0;
/*N*/ }


/*N*/ void GetASCWriter( const String& rFltNm, WriterRef& xRet )
/*N*/ {
/*N*/   xRet = new SwASCWriter( rFltNm );
/*N*/ }


}
