/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: sw_paminit.cxx,v $
 *
 *  $Revision: 1.5 $
 *
 *  last change: $Author: kz $ $Date: 2007-09-06 11:55:11 $
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

#ifndef _ERRHDL_HXX
#include <errhdl.hxx>
#endif

#ifndef _PAMTYP_HXX
#include <pamtyp.hxx>
#endif
namespace binfilter {


/*N*/ static SwMoveFnCollection aFwrd = {
/*N*/ 	/* fnNd			*/  &GoNext,
/*N*/ 	/* fnNds 		*/  &GoNextNds,
/*N*/ 	/* fnDoc 		*/  &GoEndDoc,
/*N*/ 	/* fnSections	*/  &GoEndSection,
/*N*/ 	/* fnCmpOp		*/  &SwPosition::operator<,
/*N*/ 	/* fnGetHint 	*/  &GetFrwrdTxtHint,
/*N*/ 	/* fnSearch		*/  &::utl::TextSearch::SearchFrwrd,
/*N*/ 	/* fnSection 	*/  &SwNodes::GoStartOfSection
/*N*/ };

/*N*/ static SwMoveFnCollection aBwrd = {
/*N*/ 	/* fnNd			*/  &GoPrevious,
/*N*/ 	/* fnNds 		*/  &GoPreviousNds,
/*N*/ 	/* fnDoc 		*/  &GoStartDoc,
/*N*/ 	/* fnSections	*/  &GoStartSection,
/*N*/ 	/* fnCmpOp		*/  &SwPosition::operator>,
/*N*/ 	/* fnGetHint 	*/  &GetBkwrdTxtHint,
/*N*/ 	/* fnSearch		*/  &::utl::TextSearch::SearchBkwrd,
/*N*/ 	/* fnSection 	*/  &SwNodes::GoEndOfSection
/*N*/ };

/*N*/ SwGoInDoc fnGoDoc 		= &GoInDoc;
/*N*/ SwGoInDoc fnGoSection	= &GoInSection;
/*N*/ SwGoInDoc fnGoNode		= &GoInNode;
/*N*/ SwGoInDoc fnGoCntnt		= &GoInCntnt;
/*N*/ SwGoInDoc fnGoCntntCells= &GoInCntntCells;

/*N*/ SwWhichPara fnParaPrev	= &GoPrevPara;
/*N*/ SwWhichPara fnParaCurr	= &GoCurrPara;
/*N*/ SwWhichPara fnParaNext	= &GoNextPara;
/*N*/ SwPosPara fnParaStart	= &aFwrd;
/*N*/ SwPosPara fnParaEnd		= &aBwrd;

/*N*/ SwWhichSection fnSectionPrev	= &GoPrevSection;
/*N*/ SwWhichSection fnSectionCurr	= &GoCurrSection;
/*N*/ SwWhichSection fnSectionNext	= &GoNextSection;
/*N*/ SwPosSection fnSectionStart		= &aFwrd;
/*N*/ SwPosSection fnSectionEnd		= &aBwrd;

// Travelling in Tabellen
/*N*/ FASTBOOL GotoPrevTable( SwPaM&, SwPosTable, FASTBOOL bInReadOnly );
/*N*/ FASTBOOL GotoCurrTable( SwPaM&, SwPosTable, FASTBOOL bInReadOnly );
/*N*/ FASTBOOL GotoNextTable( SwPaM&, SwPosTable, FASTBOOL bInReadOnly );

/*N*/ SwWhichTable fnTablePrev = &GotoPrevTable;
/*N*/ SwWhichTable fnTableCurr = &GotoCurrTable;
/*N*/ SwWhichTable fnTableNext = &GotoNextTable;
/*N*/ SwPosTable fnTableStart = &aFwrd;
/*N*/ SwPosTable fnTableEnd = &aBwrd;

// Travelling in Bereichen
/*N*/ FASTBOOL GotoPrevRegion( SwPaM&, SwPosRegion, FASTBOOL bInReadOnly );
/*N*/ FASTBOOL GotoCurrRegion( SwPaM&, SwPosRegion, FASTBOOL bInReadOnly );
/*N*/ FASTBOOL GotoCurrRegionAndSkip( SwPaM&, SwPosRegion, FASTBOOL bInReadOnly );
/*N*/ FASTBOOL GotoNextRegion( SwPaM&, SwPosRegion, FASTBOOL bInReadOnly );

/*N*/ SwWhichRegion fnRegionPrev = &GotoPrevRegion;
/*N*/ SwWhichRegion fnRegionCurr = &GotoCurrRegion;
/*N*/ SwWhichRegion fnRegionCurrAndSkip = &GotoCurrRegionAndSkip;
/*N*/ SwWhichRegion fnRegionNext = &GotoNextRegion;
/*N*/ SwPosRegion fnRegionStart = &aFwrd;
/*N*/ SwPosRegion fnRegionEnd = &aBwrd;
/*N*/ 
/*N*/ SwMoveFn fnMoveBackward	= &aBwrd;
/*N*/ SwMoveFn fnMoveForward	= &aFwrd;


#ifdef USED

// JP 30.11.95:
//  war fuer die CFRONT-Compiler noetig, jetzt sollte das nicht mehr
//	benoetigt werden.

/*N*/ void _InitPam()
/*N*/ {
/*N*/  	aBwrd.fnNd		=  &GoPrevious;
/*N*/ 	aBwrd.fnNds 	=  &GoPreviousNds;
/*N*/ 	aBwrd.fnDoc 	=  &GoStartDoc;
/*N*/ 	aBwrd.fnSections=  &GoStartSection;
/*N*/ 	aBwrd.fnCmpOp	=  &SwPosition::operator>;
/*N*/ 	aBwrd.fnGetHint =  &GetBkwrdTxtHint;
/*N*/ 	aBwrd.fnSearch	=  &SearchText::SearchBkwrd;
/*N*/ 	aBwrd.fnSection =  &SwNodes::GoEndOfSection;
/*N*/ 
/*N*/ 	aFwrd.fnNd		=  &GoNext;
/*N*/ 	aFwrd.fnNds 	=  &GoNextNds;
/*N*/ 	aFwrd.fnDoc 	=  &GoEndDoc;
/*N*/ 	aFwrd.fnSections=  &GoEndSection;
/*N*/ 	aFwrd.fnCmpOp	=  &SwPosition::operator<;
/*N*/ 	aFwrd.fnGetHint =  &GetFrwrdTxtHint;
/*N*/ 	aFwrd.fnSearch	=  &SearchText::SearchFrwrd;
/*N*/ 	aFwrd.fnSection =  &SwNodes::GoStartOfSection;
/*N*/ }
#endif


}
