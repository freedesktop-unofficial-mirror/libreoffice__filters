/*************************************************************************
 *
 *  $RCSfile: sw_numpara.cxx,v $
 *
 *  $Revision: 1.2 $
 *
 *  last change: $Author: mwu $ $Date: 2003-11-06 07:49:06 $
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

#include "hintids.hxx"
#include "doc.hxx"
#include "docsh.hxx"
#include "ndtxt.hxx"

#ifndef _SVX_BRSHITEM_HXX //autogen
#include <bf_svx/brshitem.hxx>
#endif
#ifndef _SVX_LRSPITEM_HXX //autogen
#include <bf_svx/lrspitem.hxx>
#endif
#include "numpara.hxx"
#include "number.hxx"



#ifdef JP_DEBUG

#ifndef _SVWINDOW_HXX
#include <svwindow.hxx>
#endif
namespace binfilter {

class GrfWindow : public WorkWindow, public Timer
{
    Graphic aGrf;
    Size aSz;
    virtual void Timeout();
    virtual void Paint( const Rectangle& );
public:
    GrfWindow( const Graphic& rGrf );
    virtual ~GrfWindow();
};

GrfWindow::GrfWindow( const Graphic& rGrf )
    : WorkWindow( GetpApp()->GetAppWindow() ), aGrf( rGrf )
{
    SetTimeout( 10000 );

    aSz = ::GetGraphicSizeTwip( &rGrf );
    SetMapMode( MapMode( MAP_TWIP ));
    SetPosSizePixel( Point( 100, 0 ), LogicToPixel( aSz ));
    Show();
    Invalidate();
    Update();
    Start();
}
SEXPORT GrfWindow::~GrfWindow()
{
}
void SEXPORT GrfWindow::Timeout()
{
    delete this;
}
void SEXPORT GrfWindow::Paint( const Rectangle& )
{
    aGrf.Draw( this, Point(0,0), PixelToLogic( GetSizePixel() ) );
}

#endif

// waehrend des Nummerierens ist das Undo am Doc abgeschaltet !!!


_NumPara::_NumPara( char nOffset, const SwNodeIndex& rNdIdx,
                    const SwNumSection& rSect, ULONG nCntNodes )
    : aNdIdx( rNdIdx ),
    rNumSection( rSect ),
    aNum( 0, rSect.pRules ),
    nCnt( nCntNodes ),
    nDiff( nOffset )
{
    bInitNum = rNdIdx.GetIndex() <= rNumSection.aStart.GetIndex();
    _Init();
}


_NumPara::_NumPara( const SwNodeIndex& rNdIdx, const SwNumSection& rSect )
    : aNdIdx( rNdIdx ),
    rNumSection( rSect ),
    aNum( 0, rSect.pRules ),
    nCnt( 0 ),
    nDiff( 0 )
{
    bInitNum = rNdIdx.GetIndex() <= rNumSection.aStart.GetIndex();
    _Init();
}


BOOL lcl_GoPrevNd( SwNodeIndex* pIdx )
{
    // ACHTUNG: Tabellen ueberspringen !
    BOOL bRet = TRUE;
    SwEndNode* pEndNd;
    SwNodeIndex aIdx( *pIdx, -1 );
    while( 0 != ( pEndNd = aIdx.GetNode().GetEndNode() ) &&
            pEndNd->FindStartNode()->IsTableNode() )
    {
        aIdx = *pEndNd->StartOfSectionNode();
        bRet = 0 != pEndNd->GetNodes().GoPrevious( &aIdx );
        if( !bRet )
            break;		// weiter gehts nicht
    }
    if( bRet )
        *pIdx = aIdx;
    return bRet;
}


void _NumPara::_Init()
{
    bOverTbl = FALSE;
    SwDoc* pDoc = aNdIdx.GetNodes().GetDoc();
    bWasUndo = pDoc->DoesUndo();
    pDoc->DoUndo( FALSE );


    if( !bInitNum )		// hole vom Vorgaenger die aktuelle Nummerierung
    {
        const SwNodes& rNds = aNdIdx.GetNodes();
        SwTxtNode* pTxtNd = 0;
        SwNodeIndex aIdx( aNdIdx );
        while( lcl_GoPrevNd( &aIdx ) && ( !pTxtNd ||
                (NO_NUM == pTxtNd->GetpSwpHints()->GetNum().nMyLevel ||
                 NO_NUMLEVEL & pTxtNd->GetpSwpHints()->GetNum().nMyLevel ))  &&
                rNumSection.aStart.GetIndex() <= aIdx.GetIndex() )
            pTxtNd = rNds[ aIdx ]->GetTxtNode();

        ASSERT( pTxtNd, "NumSection ohne Start-TextNode? " );
        aNum = pTxtNd->GetpSwpHints()->GetNum();
        aNum.pRules = rNumSection.pRules;
        if( NO_NUM == aNum.nMyLevel || NO_NUMLEVEL & aNum.nMyLevel )
        {
            aNum.nMyLevel = 0;
            aNum.nLevelVal[ 0 ] = aNum.pRules->Get( 0 ).GetStartValue();
            bInitNum = TRUE;
        }
    }
    else
        aNum.nLevelVal[ 0 ] = aNum.pRules->Get( 0 ).GetStartValue();

    nOldLevel = aNum.nMyLevel;
}


_NumPara::~_NumPara()
{
    SwDoc* pDoc = aNdIdx.GetNodes().GetDoc();
    pDoc->DoUndo( bWasUndo );
}


void _NumPara::UpdateNum( SwTxtNode& rTxtNd )
{
    BYTE nLevel = aNum.nMyLevel;
    BYTE nNdOldLvl = MAXLEVEL;
    if( rTxtNd.GetpSwpHints() )
    {
        const SwNum& rNum = rTxtNd.GetpSwpHints()->GetNum();
        if( NO_NUMBERING != rNum.nMyLevel &&
            (!rNum.pRules || NUM_RULES == rNum.pRules->GetRulesType() ))
            nNdOldLvl = nLevel = rNum.nMyLevel;
    }

    if( NO_NUMLEVEL & nLevel )		// NoNum mit Ebene
    {
        if( ( -1 == nDiff && NO_NUMLEVEL < nLevel ) ||
            ( 1 == nDiff && ( NO_NUMLEVEL + MAXLEVEL - 1 ) > nLevel ) )
            nLevel += nDiff;
        aNum.nMyLevel = nLevel;

        rTxtNd.UpdateNum( aNum );
    }
    else if( NO_NUM != nLevel )
    {
        if( ( -1 == nDiff && 0 < nLevel ) || ( 1 == nDiff && MAXLEVEL-1 > nLevel ))
            nLevel += nDiff;

        BYTE nTmpLvl = aNum.nMyLevel & ~NO_NUMLEVEL;
        if( nTmpLvl < nLevel )
        {
            // Erfrage wie geloescht werden soll:
            // z.B von Stufe 0 -> 1: 1 -> 0.1 ; wenn nStart = 1
            // 	aber Stufe 1 -> 2: 1.1 -> 1.1.1 !!, nur 0.1 -> 0.0.1
            if( !bInitNum )
                ++nTmpLvl;

            memset( aNum.nLevelVal + nTmpLvl, 0,
                    (MAXLEVEL - nTmpLvl) * sizeof( aNum.nLevelVal[0]) );
            aNum.nLevelVal[ nLevel ] = aNum.pRules->Get( nLevel ).GetStartValue();
        }
        else if( !aNum.nLevelVal[ nLevel ] )
            aNum.nLevelVal[ nLevel ] = aNum.pRules->Get( nLevel ).GetStartValue();
        else if( !bInitNum )
            aNum.nLevelVal[ nLevel ]++;

        bInitNum = FALSE;
        aNum.nMyLevel = nLevel;

        // beim Format mit Bitmap die Graphicen schon mal anfordern
        const SwNumFmt* pNumFmt = aNum.GetNumFmt();
        if( pNumFmt && USER_BITMAP == pNumFmt->eType )
        {
            SwDoc* pDoc = aNdIdx.GetNodes().GetDoc();
            const Graphic* pGrf = pNumFmt->GetGrfBrush()->
                        GetGraphic( pDoc->GetDocShell() );

#ifdef JP_DEBUG
            new GrfWindow( *pGrf );
#endif
        }

        rTxtNd.UpdateNum( aNum );
    }
    else
        ((SwNum&)rTxtNd.GetpSwpHints()->GetNum()).pRules = aNum.pRules;

    // falls keine Nummerierung mehr gueltig ist, steht in "nOldLevel"
    // der letze gueltiege (0..MAXLEVEL) Level.
    if( NO_NUM != nLevel )
        nOldLevel = nLevel & ~NO_NUMLEVEL;

//FEATURE::CONDCOLL
    BOOL bCheck = TRUE;
    if( RES_CONDTXTFMTCOLL == rTxtNd.GetFmtColl()->Which() )
    {
        SwFmtColl* pChgColl = rTxtNd.GetCondFmtColl();
        rTxtNd.ChkCondColl();
        if( rTxtNd.GetCondFmtColl() )
        {
            // es gab eine Aenderung -> harte Einzuege entfernen
            if( pChgColl != rTxtNd.GetCondFmtColl() )
                rTxtNd.ResetAttr( RES_LR_SPACE );
            bCheck = FALSE;
        }
    }
//FEATURE::CONDCOLL

    // hat sich eine Level - Aenderung ergeben, so setze jetzt die
    // gueltigen Einzuege
    if( bCheck && ( nLevel != nNdOldLvl || rTxtNd.IsSetNumLSpace() ) &&
        (nLevel & ~NO_NUMLEVEL) < MAXLEVEL )
    {
        SvxLRSpaceItem aLR( ((SvxLRSpaceItem&)rTxtNd.SwCntntNode::GetAttr(
                            RES_LR_SPACE )) );

        const SwNumFmt& rNFmt = aNum.pRules->Get( nLevel & ~NO_NUMLEVEL );

        // ohne Nummer immer ohne FirstLineOffset!!!!
        aLR.SetTxtFirstLineOfstValue( ( nLevel & NO_NUMLEVEL )
                                ? 0 : rNFmt.GetFirstLineOffset() );
        aLR.SetTxtLeft( rNFmt.GetAbsLSpace() );

        rTxtNd.SwCntntNode::SetAttr( aLR );
    }
    // Flag immer loeschen!
    rTxtNd.SetNumLSpace( FALSE );


    aNdIdx++;
}




}
