/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: sw_fntcap.cxx,v $
 *
 *  $Revision: 1.5 $
 *
 *  last change: $Author: rt $ $Date: 2005-09-09 02:39:56 $
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


#pragma hdrstop

#ifndef _HINTIDS_HXX
#include <hintids.hxx>
#endif

// auto strip #ifndef _SVX_CMAPITEM_HXX //autogen
// auto strip #include <bf_svx/cmapitem.hxx>
// auto strip #endif

// auto strip #ifndef _OUTDEV_HXX //autogen
// auto strip #include <vcl/outdev.hxx>
// auto strip #endif
#ifndef _COM_SUN_STAR_I18N_CHARTYPE_HDL
#include <com/sun/star/i18n/CharType.hdl>
#endif
#ifndef _COM_SUN_STAR_I18N_WORDTYPE_HDL
#include <com/sun/star/i18n/WordType.hdl>
#endif

#ifndef _PRINT_HXX //autogen
#include <vcl/print.hxx>
#endif

// auto strip #ifndef _ERRHDL_HXX
// auto strip #include <errhdl.hxx>
// auto strip #endif
#ifndef _FNTCACHE_HXX
#include <fntcache.hxx>
#endif
#ifndef _SWFONT_HXX
#include <swfont.hxx>
#endif
// auto strip #ifndef _DRAWFONT_HXX
// auto strip #include <drawfont.hxx>
// auto strip #endif
#ifndef _BREAKIT_HXX
#include <breakit.hxx>
#endif
// auto strip #ifndef _TXTFRM_HXX
// auto strip #include <txtfrm.hxx>       // SwTxtFrm
// auto strip #endif
namespace binfilter {

using namespace ::com::sun::star::i18n;


#define KAPITAELCHENPROP 66

/*************************************************************************
 *						class SwCapitalInfo
 *
 * The information encapsulated in SwCapitalInfo is required
 * by the ::Do functions. They contain the information about
 * the original string, whereas rDo.GetInf() contains information
 * about the display string.
 *************************************************************************/

class SwCapitalInfo
{
public:
    explicit SwCapitalInfo( const XubString& rOrigText ) :
        rString( rOrigText ), nIdx( 0 ), nLen( 0 ) {};
    const XubString& rString;
    xub_StrLen nIdx;
    xub_StrLen nLen;
};

/*************************************************************************
 *						xub_StrLen lcl_CalcCaseMap()
 *
 * rFnt: required for CalcCaseMap
 * rOrigString: The original string
 * nOfst: Position of the substring in rOrigString
 * nLen: Length if the substring in rOrigString
 * nIdx: Referes to a position in the display string and should be mapped
 *       to a position in rOrigString
 *************************************************************************/

xub_StrLen lcl_CalcCaseMap( const SwFont& rFnt,
                            const XubString& rOrigString,
                            xub_StrLen nOfst,
                            xub_StrLen nLen,
                            xub_StrLen nIdx )
{
    int j = 0;
    const xub_StrLen nEnd = nOfst + nLen;
    ASSERT( nEnd <= rOrigString.Len(), "lcl_CalcCaseMap: Wrong parameters" )

    // special case for title case:
    const bool bTitle = SVX_CASEMAP_TITEL == rFnt.GetCaseMap() &&
                        pBreakIt->xBreak.is();
    for ( int i = nOfst; i < nEnd; ++i )
    {
        XubString aTmp( rOrigString, i, 1 );

        if ( !bTitle ||
             pBreakIt->xBreak->isBeginWord(
                 rOrigString, i,
                 pBreakIt->GetLocale( rFnt.GetLanguage() ), 
                 WordType::ANYWORD_IGNOREWHITESPACES ) )
            aTmp = rFnt.GetActualFont().CalcCaseMap( aTmp );
    
        j += aTmp.Len();

        if ( j > nIdx )
            return i;
    }

    return nOfst + nLen;
}

/*************************************************************************
 *						class SwDoCapitals
 *************************************************************************/

class SwDoCapitals
{
protected:
    SwDrawTextInfo &rInf;
    SwCapitalInfo* pCapInf; // referes to additional information
                           // required by the ::Do function
public:
    SwDoCapitals ( SwDrawTextInfo &rInfo ) : rInf( rInfo ), pCapInf( 0 ) { }
    virtual void Init( SwFntObj *pUpperFont, SwFntObj *pLowerFont ) = 0;
    virtual void Do() = 0;
    inline OutputDevice *GetOut() { return rInf.GetpOut(); }
    inline SwDrawTextInfo& GetInf() { return rInf; }
    inline SwCapitalInfo* GetCapInf() const { return pCapInf; }
    inline void SetCapInf( SwCapitalInfo& rNew ) { pCapInf = &rNew; }
};

/*************************************************************************
 *					  class SwDoGetCapitalSize
 *************************************************************************/

class SwDoGetCapitalSize : public SwDoCapitals
{
protected:
    Size aTxtSize;
public:
    SwDoGetCapitalSize( SwDrawTextInfo &rInfo ) : SwDoCapitals ( rInfo ) { }
    virtual void Init( SwFntObj *pUpperFont, SwFntObj *pLowerFont );
    virtual void Do();
    const Size &GetSize() const { return aTxtSize; }
};

/*N*/ void SwDoGetCapitalSize::Init( SwFntObj *pUpperFont, SwFntObj *pLowerFont )
/*N*/ {
/*N*/ 	aTxtSize.Height() = 0;
/*N*/ 	aTxtSize.Width() = 0;
/*N*/ }

/*N*/ void SwDoGetCapitalSize::Do()
/*N*/ {
/*N*/ 	aTxtSize.Width() += rInf.GetSize().Width();
/*N*/ 	if( rInf.GetUpper() )
/*N*/ 		aTxtSize.Height() = rInf.GetSize().Height();
/*N*/ }

/*************************************************************************
 *					  SwSubFont::GetCapitalSize()
 *************************************************************************/

/*N*/ Size SwSubFont::GetCapitalSize( SwDrawTextInfo& rInf )
/*N*/ {
/*N*/ 	// Start:
/*N*/ 	short nOldKern = rInf.GetKern();
/*N*/ 	rInf.SetKern( CheckKerning() );
/*N*/ 	Point aPos;
/*N*/ 	rInf.SetPos( aPos );
/*N*/ 	rInf.SetSpace( 0 );
/*N*/ 	rInf.SetDrawSpace( FALSE );
/*N*/ 	SwDoGetCapitalSize aDo( rInf );
/*N*/ 	DoOnCapitals( aDo );
/*N*/ 	Size aTxtSize( aDo.GetSize() );
/*N*/ 
/*N*/ 	// End:
/*N*/ 	if( !aTxtSize.Height() )
/*N*/ 	{
/*N*/ 		SV_STAT( nGetTextSize );
/*N*/ 		aTxtSize.Height() = short ( rInf.GetpOut()->GetTextHeight() );
/*N*/ 	}
/*N*/ 	rInf.SetKern( nOldKern );
/*N*/ 	return aTxtSize;
/*N*/ }

/*************************************************************************
 *					  class SwDoGetCapitalBreak
 *************************************************************************/

class SwDoGetCapitalBreak : public SwDoCapitals
{
protected:
    xub_StrLen *pExtraPos;
    long nTxtWidth;
    xub_StrLen nBreak;
public:
    SwDoGetCapitalBreak( SwDrawTextInfo &rInfo, long nWidth, xub_StrLen *pExtra)
        :	SwDoCapitals ( rInfo ), nTxtWidth( nWidth ),
            nBreak( STRING_LEN ), pExtraPos( pExtra )
        { }
//STRIP001 	virtual void Init( SwFntObj *pUpperFont, SwFntObj *pLowerFont );
//STRIP001 	virtual void Do();
    const xub_StrLen GetBreak() const { return nBreak; }
};

//STRIP001 void SwDoGetCapitalBreak::Init( SwFntObj *pUpperFont, SwFntObj *pLowerFont )
//STRIP001 {
//STRIP001 }

//STRIP001 void SwDoGetCapitalBreak::Do()
//STRIP001 {
//STRIP001 	if ( nTxtWidth )
//STRIP001 	{
//STRIP001 		if ( rInf.GetSize().Width() < nTxtWidth )
//STRIP001 			nTxtWidth -= rInf.GetSize().Width();
//STRIP001 		else
//STRIP001 		{
//STRIP001 			xub_StrLen nEnd = rInf.GetEnd();
//STRIP001 			if( pExtraPos )
//STRIP001 			{
//STRIP001 				nBreak = GetOut()->GetTextBreak( rInf.GetText(), nTxtWidth, '-',
//STRIP001 					 *pExtraPos, rInf.GetIdx(), rInf.GetLen(), rInf.GetKern() );
//STRIP001 				if( *pExtraPos > nEnd )
//STRIP001 					*pExtraPos = nEnd;
//STRIP001 			}
//STRIP001 			else
//STRIP001 				nBreak = GetOut()->GetTextBreak( rInf.GetText(), nTxtWidth,
//STRIP001 							   rInf.GetIdx(), rInf.GetLen(), rInf.GetKern() );
//STRIP001 
//STRIP001 			if( nBreak > nEnd )
//STRIP001 				nBreak = nEnd;
//STRIP001 
//STRIP001             // nBreak may be relative to the display string. It has to be
//STRIP001             // calculated relative to the original string:
//STRIP001             if ( GetCapInf()  )
//STRIP001             {
//STRIP001                 if ( GetCapInf()->nLen != rInf.GetLen() )
//STRIP001                     nBreak = lcl_CalcCaseMap( *rInf.GetFont(),
//STRIP001                                               GetCapInf()->rString,
//STRIP001                                               GetCapInf()->nIdx,
//STRIP001                                               GetCapInf()->nLen, nBreak );
//STRIP001                 else
//STRIP001                     nBreak += GetCapInf()->nIdx;
//STRIP001             }
//STRIP001 
//STRIP001 			nTxtWidth = 0;
//STRIP001 		}
//STRIP001 	}
//STRIP001 }

/*************************************************************************
 *					  SwFont::GetCapitalBreak()
 *************************************************************************/

//STRIP001 xub_StrLen SwFont::GetCapitalBreak( ViewShell *pSh, const OutputDevice *pOut,
//STRIP001 	const SwScriptInfo* pScript, const XubString &rTxt, long nTextWidth,
//STRIP001 	xub_StrLen *pExtra,	const xub_StrLen nIdx, const xub_StrLen nLen )
//STRIP001 {
//STRIP001 	// Start:
//STRIP001 	Point aPos( 0, 0 );
//STRIP001 	SwDrawTextInfo aInfo(pSh, *(OutputDevice*)pOut, pScript, rTxt, nIdx, nLen,
//STRIP001 		0, FALSE);
//STRIP001 	aInfo.SetPos( aPos );
//STRIP001 	aInfo.SetSpace( 0 );
//STRIP001 	aInfo.SetWrong( NULL );
//STRIP001 	aInfo.SetDrawSpace( FALSE );
//STRIP001 	aInfo.SetKern( CheckKerning() );
//STRIP001 	aInfo.SetKanaComp( pScript ? 0 : 100 );
//STRIP001     aInfo.SetFont( this );
//STRIP001 
//STRIP001 	SwDoGetCapitalBreak aDo( aInfo, nTextWidth, pExtra );
//STRIP001 	DoOnCapitals( aDo );
//STRIP001 	return aDo.GetBreak();
//STRIP001 }

/*************************************************************************
 *					   class SwDoDrawCapital
 *************************************************************************/

class SwDoDrawCapital : public SwDoCapitals
{
protected:
    SwFntObj *pUpperFnt;
    SwFntObj *pLowerFnt;
public:
    SwDoDrawCapital( SwDrawTextInfo &rInfo ) :
        SwDoCapitals( rInfo )
        { }
//STRIP001 	virtual void Init( SwFntObj *pUpperFont, SwFntObj *pLowerFont );
//STRIP001 	virtual void Do();
//STRIP001 	void DrawSpace( Point &rPos );
};

//STRIP001 void SwDoDrawCapital::Init( SwFntObj *pUpperFont, SwFntObj *pLowerFont )
//STRIP001 {
//STRIP001 	pUpperFnt = pUpperFont;
//STRIP001 	pLowerFnt = pLowerFont;
//STRIP001 }

//STRIP001 void SwDoDrawCapital::Do()
//STRIP001 {
//STRIP001 	SV_STAT( nDrawText );
//STRIP001 	USHORT nOrgWidth = rInf.GetWidth();
//STRIP001 	rInf.SetWidth( USHORT(rInf.GetSize().Width()) );
//STRIP001 	if ( rInf.GetUpper() )
//STRIP001 		pUpperFnt->DrawText( rInf );
//STRIP001 	else
//STRIP001 	{
//STRIP001 		BOOL bOldBullet = rInf.GetBullet();
//STRIP001 		rInf.SetBullet( FALSE );
//STRIP001 		pLowerFnt->DrawText( rInf );
//STRIP001 		rInf.SetBullet( bOldBullet );
//STRIP001 	}
//STRIP001 
//STRIP001     ASSERT( pUpperFnt, "No upper font, dying soon!");
//STRIP001     rInf.Shift( pUpperFnt->GetFont()->GetOrientation() );
//STRIP001 	rInf.SetWidth( nOrgWidth );
//STRIP001 }

/*************************************************************************
 *					  SwDoDrawCapital::DrawSpace()
 *************************************************************************/

//STRIP001 void SwDoDrawCapital::DrawSpace( Point &rPos )
//STRIP001 {
//STRIP001 	static sal_Char __READONLY_DATA sDoubleSpace[] = "  ";
//STRIP001 
//STRIP001     long nDiff = rInf.GetPos().X() - rPos.X();
//STRIP001 
//STRIP001     Point aPos( rPos );
//STRIP001 #ifdef BIDI
//STRIP001     if ( rInf.GetFrm()->IsRightToLeft() )
//STRIP001     {
//STRIP001        rInf.GetFrm()->SwitchLTRtoRTL( aPos );
//STRIP001        nDiff = -nDiff;
//STRIP001     }
//STRIP001 #endif
//STRIP001 
//STRIP001     if ( rInf.GetFrm()->IsVertical() )
//STRIP001         rInf.GetFrm()->SwitchHorizontalToVertical( aPos );
//STRIP001 
//STRIP001 	if ( nDiff )
//STRIP001     {
//STRIP001         rInf.ApplyAutoColor();
//STRIP001         GetOut()->DrawStretchText( aPos, nDiff,
//STRIP001 			XubString( sDoubleSpace, RTL_TEXTENCODING_MS_1252 ), 0, 2 );
//STRIP001     }
//STRIP001 	rPos.X() = rInf.GetPos().X() + rInf.GetWidth();
//STRIP001 }

/*************************************************************************
 *					  SwSubFont::DrawCapital()
 *************************************************************************/

//STRIP001 void SwSubFont::DrawCapital( SwDrawTextInfo &rInf )
//STRIP001 {
//STRIP001 	// Es wird vorausgesetzt, dass rPos bereits kalkuliert ist!
//STRIP001 	// hochgezogen in SwFont: const Point aPos( CalcPos(rPos) );
//STRIP001 	rInf.SetDrawSpace( GetUnderline() != UNDERLINE_NONE ||
//STRIP001 					   GetStrikeout() != STRIKEOUT_NONE );
//STRIP001 	SwDoDrawCapital aDo( rInf );
//STRIP001 	DoOnCapitals( aDo );
//STRIP001 }

/*************************************************************************
 *					   class SwDoDrawCapital
 *************************************************************************/

class SwDoCapitalCrsrOfst : public SwDoCapitals
{
protected:
    SwFntObj *pUpperFnt;
    SwFntObj *pLowerFnt;
    xub_StrLen nCrsr;
    USHORT nOfst;
public:
    SwDoCapitalCrsrOfst( SwDrawTextInfo &rInfo, const USHORT nOfs ) :
        SwDoCapitals( rInfo ), nOfst( nOfs ), nCrsr( 0 )
        { }
//STRIP001 	virtual void Init( SwFntObj *pUpperFont, SwFntObj *pLowerFont );
//STRIP001 	virtual void Do();

    void DrawSpace( const Point &rPos );
    inline xub_StrLen GetCrsr(){ return nCrsr; }
};

//STRIP001 void SwDoCapitalCrsrOfst::Init( SwFntObj *pUpperFont, SwFntObj *pLowerFont )
//STRIP001 {
//STRIP001 	pUpperFnt = pUpperFont;
//STRIP001 	pLowerFnt = pLowerFont;
//STRIP001 }

//STRIP001 void SwDoCapitalCrsrOfst::Do()
//STRIP001 {
//STRIP001 	if ( nOfst )
//STRIP001 	{
//STRIP001 		if ( nOfst > rInf.GetSize().Width() )
//STRIP001 		{
//STRIP001 			nOfst -= USHORT(rInf.GetSize().Width());
//STRIP001 			nCrsr += rInf.GetLen();
//STRIP001 		}
//STRIP001 		else
//STRIP001 		{
//STRIP001 #ifdef OLD
//STRIP001 			if ( rInf.GetUpper() )
//STRIP001 				nCrsr += pUpperFnt->GetCrsrOfst( rInf.GetpOut(),
//STRIP001 							rInf.GetScriptInfo(), rInf.GetText(), nOfst,
//STRIP001 							rInf.GetIdx(), rInf.GetLen(), rInf.GetKern(),
//STRIP001 							0, rInf.GetKanaComp() );
//STRIP001 			else
//STRIP001 				nCrsr += pLowerFnt->GetCrsrOfst( rInf.GetpOut(),
//STRIP001 					rInf.GetScriptInfo(), rInf.GetText(), nOfst, rInf.GetIdx(),
//STRIP001 					rInf.GetLen(), rInf.GetKern(), rInf.GetSpace(),
//STRIP001 					rInf.GetKanaComp() );
//STRIP001 #else
//STRIP001             SwDrawTextInfo aDrawInf( 0, *rInf.GetpOut(),
//STRIP001                                      rInf.GetScriptInfo(),
//STRIP001                                      rInf.GetText(),
//STRIP001                                      rInf.GetIdx(),
//STRIP001                                      rInf.GetLen(), 0, FALSE );
//STRIP001             aDrawInf.SetOfst( nOfst );
//STRIP001             aDrawInf.SetKern( rInf.GetKern() );
//STRIP001             aDrawInf.SetKanaComp( rInf.GetKanaComp() );
//STRIP001             aDrawInf.SetFrm( rInf.GetFrm() );
//STRIP001             aDrawInf.SetFont( rInf.GetFont() );
//STRIP001 
//STRIP001 			if ( rInf.GetUpper() )
//STRIP001             {
//STRIP001                 aDrawInf.SetSpace( 0 );
//STRIP001                 nCrsr += pUpperFnt->GetCrsrOfst( aDrawInf );
//STRIP001             }
//STRIP001 			else
//STRIP001             {
//STRIP001                 aDrawInf.SetSpace( rInf.GetSpace() );
//STRIP001                 nCrsr += pLowerFnt->GetCrsrOfst( aDrawInf );
//STRIP001             }
//STRIP001 #endif
//STRIP001 			nOfst = 0;
//STRIP001 		}
//STRIP001 	}
//STRIP001 }

/*************************************************************************
 *					  SwSubFont::GetCapitalCrsrOfst()
 *************************************************************************/

//STRIP001 xub_StrLen SwSubFont::GetCapitalCrsrOfst( SwDrawTextInfo& rInf )
//STRIP001 {
//STRIP001 	short nOldKern = rInf.GetKern();
//STRIP001 	rInf.SetKern( CheckKerning() );
//STRIP001 	SwDoCapitalCrsrOfst aDo( rInf, rInf.GetOfst() );
//STRIP001 	Point aPos;
//STRIP001 	rInf.SetPos( aPos );
//STRIP001 	rInf.SetDrawSpace( FALSE );
//STRIP001 	DoOnCapitals( aDo );
//STRIP001 	rInf.SetKern( nOldKern );
//STRIP001 	return aDo.GetCrsr();
//STRIP001 }

/*************************************************************************
 *					  class SwDoDrawStretchCapital
 *************************************************************************/

class SwDoDrawStretchCapital : public SwDoDrawCapital
{
    const xub_StrLen nStrLen;
    const USHORT nCapWidth;
    const USHORT nOrgWidth;
public:
//STRIP001 	virtual void Do();

    SwDoDrawStretchCapital( SwDrawTextInfo &rInfo, const USHORT nCapWidth )
            : SwDoDrawCapital( rInfo ),
              nCapWidth( nCapWidth ),
              nOrgWidth( rInfo.GetWidth() ),
              nStrLen( rInfo.GetLen() )
        { }
};

/*************************************************************************
 *					  SwDoDrawStretchCapital
 *************************************************************************/

//STRIP001 void SwDoDrawStretchCapital::Do()
//STRIP001 {
//STRIP001 	SV_STAT( nDrawStretchText );
//STRIP001 	USHORT nPartWidth = USHORT(rInf.GetSize().Width());
//STRIP001 
//STRIP001 	if( rInf.GetLen() )
//STRIP001 	{
//STRIP001 		// 4023: Kapitaelchen und Kerning.
//STRIP001 		long nDiff = long(nOrgWidth) - long(nCapWidth);
//STRIP001 		if( nDiff )
//STRIP001 		{
//STRIP001 			nDiff *= rInf.GetLen();
//STRIP001 			nDiff /= (long) nStrLen;
//STRIP001 			nDiff += nPartWidth;
//STRIP001 			if( 0 < nDiff )
//STRIP001 				nPartWidth = USHORT(nDiff);
//STRIP001 		}
//STRIP001 
//STRIP001         rInf.ApplyAutoColor();
//STRIP001 
//STRIP001         // Optimierung:
//STRIP001 
//STRIP001 		if( 1 >= rInf.GetLen() )
//STRIP001 			GetOut()->DrawText( rInf.GetPos(), rInf.GetText(), rInf.GetIdx(),
//STRIP001 				rInf.GetLen() );
//STRIP001 		else
//STRIP001 			GetOut()->DrawStretchText( rInf.GetPos(), nPartWidth,
//STRIP001 								rInf.GetText(), rInf.GetIdx(), rInf.GetLen() );
//STRIP001 	}
//STRIP001 	((Point&)rInf.GetPos()).X() += nPartWidth;
//STRIP001 }

/*************************************************************************
 *					  SwSubFont::DrawStretchCapital()
 *************************************************************************/

//STRIP001 void SwSubFont::DrawStretchCapital( SwDrawTextInfo &rInf )
//STRIP001 {
//STRIP001 	// Es wird vorausgesetzt, dass rPos bereits kalkuliert ist!
//STRIP001 	// hochgezogen in SwFont: const Point aPos( CalcPos(rPos) );
//STRIP001 
//STRIP001 	if( rInf.GetLen() == STRING_LEN )
//STRIP001 		rInf.SetLen( rInf.GetText().Len() );
//STRIP001 
//STRIP001     const Point& rOldPos = rInf.GetPos();
//STRIP001 	const USHORT nCapWidth = (USHORT)( GetCapitalSize( rInf ).Width() );
//STRIP001     rInf.SetPos( rOldPos );
//STRIP001 
//STRIP001 	rInf.SetDrawSpace( GetUnderline() != UNDERLINE_NONE ||
//STRIP001 					   GetStrikeout() != STRIKEOUT_NONE );
//STRIP001 	SwDoDrawStretchCapital aDo( rInf, nCapWidth );
//STRIP001 	DoOnCapitals( aDo );
//STRIP001 }

/*************************************************************************
 *					SwSubFont::DoOnCapitals() const
 *************************************************************************/

// JP 22.8.2001 - global optimization off - Bug 91245 / 91223
#if defined( WNT ) && defined( MSC )
#pragma optimize("g",off)
#endif

/*N*/ void SwSubFont::DoOnCapitals( SwDoCapitals &rDo )
/*N*/ {
/*N*/ 	ASSERT( pLastFont, "SwFont::DoOnCapitals: No LastFont?!" );
/*N*/ 
/*N*/ 	Size aPartSize;
/*N*/ 	long nKana = 0;
/*N*/ 	const XubString aTxt( CalcCaseMap( rDo.GetInf().GetText() ) );
/*N*/ 	xub_StrLen nMaxPos = Min( USHORT(rDo.GetInf().GetText().Len()
/*N*/ 							- rDo.GetInf().GetIdx()), rDo.GetInf().GetLen() );
/*N*/ 	rDo.GetInf().SetLen( nMaxPos );
/*N*/ 
/*N*/ 	const XubString& rOldText = rDo.GetInf().GetText();
/*N*/ 	rDo.GetInf().SetText( aTxt );
/*N*/ 	rDo.GetInf().SetSize( aPartSize );
/*N*/ 	xub_StrLen nPos = rDo.GetInf().GetIdx();
/*N*/ 	xub_StrLen nOldPos = nPos;
/*N*/ 	nMaxPos += nPos;
/*N*/ 
/*N*/ 	// #107816#
/*N*/ 	// Look if the length of the original text and the ToUpper-converted
/*N*/ 	// text is different. If yes, do special handling.
/*N*/ 	XubString aNewText;
/*N*/     SwCapitalInfo aCapInf( rOldText );
/*N*/     sal_Bool bCaseMapLengthDiffers( aTxt.Len() != rOldText.Len() );
/*N*/     if ( bCaseMapLengthDiffers )
/*N*/         rDo.SetCapInf( aCapInf );
/*N*/ 
/*N*/ 	SwFntObj *pOldLast = pLastFont;
/*N*/ 	SwFntAccess *pBigFontAccess = NULL;
/*N*/ 	SwFntObj *pBigFont;
/*N*/ 	SwFntAccess *pSpaceFontAccess = NULL;
/*N*/ 	SwFntObj *pSpaceFont = NULL;
/*N*/ 
/*N*/ 	const void *pMagic2 = NULL;
/*N*/ 	USHORT nIndex2 = 0;
/*N*/ 	SwSubFont aFont( *this );
/*N*/ 	Point aStartPos( rDo.GetInf().GetPos() );
/*N*/ 
/*N*/ 	const BOOL bUnderStriked = aFont.GetUnderline() != UNDERLINE_NONE
/*N*/ 							|| aFont.GetStrikeout() != STRIKEOUT_NONE;
/*N*/ 	const BOOL bWordWise = bUnderStriked && aFont.IsWordLineMode() &&
/*N*/ 						   rDo.GetInf().GetDrawSpace();
/*N*/ 	const short nKern = rDo.GetInf().GetKern();
/*N*/ 
/*N*/ 	if ( bUnderStriked )
/*N*/ 	{
/*N*/ 		if ( bWordWise )
/*N*/ 		{
/*?*/ 			aFont.SetWordLineMode( FALSE );
/*?*/ 			pSpaceFontAccess = new SwFntAccess( pMagic2, nIndex2, &aFont,
/*?*/ 												rDo.GetInf().GetShell() );
/*?*/ 			pSpaceFont = pSpaceFontAccess->Get();
/*N*/ 		}
/*N*/ 		else
/*N*/ 			pSpaceFont = pLastFont;
/*N*/ 
/*N*/ 		// Wir basteln uns einen Font fuer die Grossbuchstaben:
/*N*/ 		aFont.SetUnderline( UNDERLINE_NONE );
/*N*/ 		aFont.SetStrikeout( STRIKEOUT_NONE );
/*N*/ 		pMagic2 = NULL;
/*N*/ 		nIndex2 = 0;
/*N*/ 		pBigFontAccess = new SwFntAccess( pMagic2, nIndex2, &aFont,
/*N*/ 										  rDo.GetInf().GetShell() );
/*N*/ 		pBigFont = pBigFontAccess->Get();
/*N*/ 	}
/*N*/ 	else
/*N*/ 		pBigFont = pLastFont;
/*N*/ 
/*N*/ 	// Hier entsteht der Kleinbuchstabenfont:
/*N*/ 	aFont.SetProportion( BYTE( (aFont.GetPropr()*KAPITAELCHENPROP) / 100L) );
/*N*/ 	pMagic2 = NULL;
/*N*/ 	nIndex2 = 0;
/*N*/ 	SwFntAccess *pSmallFontAccess = new SwFntAccess( pMagic2, nIndex2, &aFont,
/*N*/ 													 rDo.GetInf().GetShell() );
/*N*/ 	SwFntObj *pSmallFont = pSmallFontAccess->Get();
/*N*/ 
/*N*/ 	rDo.Init( pBigFont, pSmallFont );
/*N*/ 	OutputDevice* pOutSize = pSmallFont->GetPrt();
/*N*/ 	if( !pOutSize )
/*N*/ 		pOutSize = rDo.GetOut();
/*N*/ 	OutputDevice* pOldOut = rDo.GetOut();
/*N*/ 
/*N*/ 	const LanguageType eLng = LANGUAGE_DONTKNOW == GetLanguage()
/*N*/ 							? LANGUAGE_SYSTEM : GetLanguage();
/*N*/ 
/*N*/ 	if( nPos < nMaxPos )
/*N*/ 	{
/*N*/ 		nPos = (xub_StrLen)pBreakIt->xBreak->endOfCharBlock( rOldText, nPos,
/*N*/ 			pBreakIt->GetLocale( eLng ), CharType::LOWERCASE_LETTER);
/*N*/ 		if( nPos == STRING_LEN )
/*N*/ 			nPos = nOldPos;
/*N*/ 		else if( nPos > nMaxPos )
/*N*/ 			nPos = nMaxPos;
/*N*/ 	}
/*N*/ 
/*N*/ 	while( nOldPos < nMaxPos )
/*N*/ 	{
/*N*/ 
/*N*/ 		//  The lower ones...
/*N*/ 		if( nOldPos != nPos )
/*N*/ 		{
/*N*/ 			SV_STAT( nGetTextSize );
/*N*/ 			pLastFont = pSmallFont;
/*N*/ 			pLastFont->SetDevFont( rDo.GetInf().GetShell(), rDo.GetOut() );
/*N*/ 
/*N*/ 			// #107816#, #i14820#
/*N*/             if( bCaseMapLengthDiffers )
/*N*/             {
/*N*/                 // Build an own 'changed' string for the given part of the
/*N*/                 // source string and use it. That new string may differ in length
/*N*/                 // from the source string.
/*N*/                 const XubString aSnippet( rOldText, nOldPos, nPos - nOldPos);
/*N*/                 aNewText = CalcCaseMap( aSnippet );
/*N*/                 aCapInf.nIdx = nOldPos;
/*N*/                 aCapInf.nLen = nPos - nOldPos;
/*N*/                 rDo.GetInf().SetIdx( 0 );
/*N*/                 rDo.GetInf().SetLen( aNewText.Len() );
/*N*/                 rDo.GetInf().SetText( aNewText );
/*N*/             }
/*N*/ 			else
/*N*/ 			{
/*N*/ 				rDo.GetInf().SetIdx( nOldPos );
/*N*/ 				rDo.GetInf().SetLen( nPos - nOldPos );
/*N*/ 			}
/*N*/ 
/*N*/ 			rDo.GetInf().SetUpper( FALSE );
/*N*/ 			rDo.GetInf().SetOut( *pOutSize );
/*N*/ 			aPartSize = pSmallFont->GetTextSize( rDo.GetInf() );
/*N*/ 			nKana += rDo.GetInf().GetKanaDiff();
/*N*/ 			rDo.GetInf().SetOut( *pOldOut );
/*N*/ 			if( nKern && nPos < nMaxPos )
/*?*/ 				aPartSize.Width() += nKern;
/*N*/ 			rDo.Do();
/*N*/ 			nOldPos = nPos;
/*N*/ 		}
/*N*/ 		nPos = (xub_StrLen)pBreakIt->xBreak->nextCharBlock( rOldText, nPos,
/*N*/ 			   pBreakIt->GetLocale( eLng ), CharType::LOWERCASE_LETTER);
/*N*/ 		if( nPos == STRING_LEN || nPos > nMaxPos )
/*N*/ 			nPos = nMaxPos;
/*N*/ 		ASSERT( nPos, "nextCharBlock not implemented?" );
/*N*/ #ifndef PRODUCT
/*N*/ 		if( !nPos )
/*N*/ 			nPos = nMaxPos;
/*N*/ #endif
/*N*/ 		// The upper ones...
/*N*/ 		if( nOldPos != nPos )
/*N*/ 		{
/*N*/ 			do
/*N*/ 			{
/*N*/ 				rDo.GetInf().SetUpper( TRUE );
/*N*/ 				pLastFont = pBigFont;
/*N*/ 				pLastFont->SetDevFont( rDo.GetInf().GetShell(), rDo.GetOut() );
/*N*/ 				xub_StrLen nTmp;
/*N*/ 				if( bWordWise )
/*N*/ 				{
/*?*/ 					nTmp = nOldPos;
/*?*/ 					while( nTmp < nPos && CH_BLANK == rOldText.GetChar( nTmp ) )
/*?*/ 						++nTmp;
/*?*/ 					if( nOldPos < nTmp )
/*?*/ 					{
                            DBG_BF_ASSERT(0, "STRIP"); //STRIP001 /*?*/ 						pLastFont = pSpaceFont;
//STRIP001 /*?*/ 						pLastFont->SetDevFont( rDo.GetInf().GetShell(),
//STRIP001 /*?*/ 											   rDo.GetOut() );
//STRIP001 /*?*/ 						((SwDoDrawCapital&)rDo).DrawSpace( aStartPos );
//STRIP001 /*?*/ 						pLastFont = pBigFont;
//STRIP001 /*?*/ 						pLastFont->SetDevFont( rDo.GetInf().GetShell(),
//STRIP001 /*?*/ 											   rDo.GetOut() );
//STRIP001 /*?*/ 
//STRIP001 /*?*/ 			            // #107816#, #i14820#
//STRIP001 /*?*/                         if( bCaseMapLengthDiffers )
//STRIP001 /*?*/                         {
//STRIP001 /*?*/                             // Build an own 'changed' string for the given part of the
//STRIP001 /*?*/                             // source string and use it. That new string may differ in length
//STRIP001 /*?*/                             // from the source string.
//STRIP001 /*?*/                             const XubString aSnippet( rOldText, nOldPos, nTmp - nOldPos);
//STRIP001 /*?*/                             aNewText = CalcCaseMap( aSnippet );
//STRIP001 /*?*/                             aCapInf.nIdx = nOldPos;
//STRIP001 /*?*/                             aCapInf.nLen = nTmp - nOldPos;
//STRIP001 /*?*/                             rDo.GetInf().SetIdx( 0 );
//STRIP001 /*?*/                             rDo.GetInf().SetLen( aNewText.Len() );
//STRIP001 /*?*/                             rDo.GetInf().SetText( aNewText );
//STRIP001 /*?*/                         }
//STRIP001 /*?*/                         else
//STRIP001 /*?*/                         {
//STRIP001 /*?*/                             rDo.GetInf().SetIdx( nOldPos );
//STRIP001 /*?*/                             rDo.GetInf().SetLen( nPos - nOldPos );
//STRIP001 /*?*/                         }
//STRIP001 /*?*/ 
//STRIP001 /*?*/ 						rDo.GetInf().SetOut( *pOutSize );
//STRIP001 /*?*/ 						aPartSize = pBigFont->GetTextSize( rDo.GetInf() );
//STRIP001 /*?*/ 						nKana += rDo.GetInf().GetKanaDiff();
//STRIP001 /*?*/ 						rDo.GetInf().SetOut( *pOldOut );
//STRIP001 /*?*/ 						if( rDo.GetInf().GetSpace() )
//STRIP001 /*?*/ 							aPartSize.Width() += rDo.GetInf().GetSpace() *
//STRIP001 /*?*/ 												 ( nTmp - nOldPos );
//STRIP001 /*?*/ 						if( nKern && nPos < nMaxPos )
//STRIP001 /*?*/ 							aPartSize.Width() += nKern;
//STRIP001 /*?*/ 						rDo.Do();
//STRIP001 /*?*/ 						aStartPos = rDo.GetInf().GetPos();
//STRIP001 /*?*/ 						nOldPos = nTmp;
/*?*/ 					}
/*?*/ 					while( nTmp < nPos && CH_BLANK != rOldText.GetChar( nTmp ) )
/*?*/ 						++nTmp;
/*N*/ 				}
/*N*/ 				else
/*N*/ 					nTmp = nPos;
/*N*/ 				if( nTmp > nOldPos )
/*N*/ 				{
/*N*/           			// #107816#, #i14820#
/*N*/                     if( bCaseMapLengthDiffers )
/*N*/                     {
/*N*/                         // Build an own 'changed' string for the given part of the
/*N*/                         // source string and use it. That new string may differ in length
/*N*/                         // from the source string.
/*N*/                         const XubString aSnippet( rOldText, nOldPos, nTmp - nOldPos);
/*N*/                         aNewText = CalcCaseMap( aSnippet );
/*N*/                         aCapInf.nIdx = nOldPos;
/*N*/                         aCapInf.nLen = nTmp - nOldPos;
/*N*/                         rDo.GetInf().SetIdx( 0 );
/*N*/                         rDo.GetInf().SetLen( aNewText.Len() );
/*N*/                         rDo.GetInf().SetText( aNewText );
/*N*/                     }
/*N*/                     else
/*N*/                     {
/*N*/                         rDo.GetInf().SetIdx( nOldPos );
/*N*/                         rDo.GetInf().SetLen( nPos - nOldPos );
/*N*/                     }
/*N*/ 
/*N*/ 					rDo.GetInf().SetOut( *pOutSize );
/*N*/ 					aPartSize = pBigFont->GetTextSize( rDo.GetInf() );
/*N*/ 					nKana += rDo.GetInf().GetKanaDiff();
/*N*/ 					rDo.GetInf().SetOut( *pOldOut );
/*N*/ 					if( !bWordWise && rDo.GetInf().GetSpace() )
/*?*/ 						for( xub_StrLen nI = nOldPos; nI < nPos; ++nI )
/*?*/ 							if( CH_BLANK == rOldText.GetChar( nI ) )
/*?*/ 							aPartSize.Width() += rDo.GetInf().GetSpace();
/*N*/ 					if( nKern && nPos < nMaxPos )
/*?*/ 						aPartSize.Width() += nKern;
/*N*/ 					rDo.Do();
/*N*/ 					nOldPos = nTmp;
/*N*/ 				}
/*N*/ 			} while( nOldPos != nPos );
/*N*/ 		}
/*N*/ 		nPos = (xub_StrLen)pBreakIt->xBreak->endOfCharBlock( rOldText, nPos,
/*N*/ 			   pBreakIt->GetLocale( eLng ), CharType::LOWERCASE_LETTER);
/*N*/ 		if( nPos == STRING_LEN || nPos > nMaxPos )
/*N*/ 			nPos = nMaxPos;
/*N*/ 		ASSERT( nPos, "endOfCharBlock not implemented?" );
/*N*/ #ifndef PRODUCT
/*N*/ 		if( !nPos )
/*N*/ 			nPos = nMaxPos;
/*N*/ #endif
/*N*/ 	}
/*N*/ 
/*N*/ 	// Aufraeumen:
/*N*/ 	if( pBigFont != pOldLast )
/*N*/ 		delete pBigFontAccess;
/*N*/ 
/*N*/ 	if( bUnderStriked )
/*N*/ 	{
/*N*/ 		if( rDo.GetInf().GetDrawSpace() )
/*N*/ 		{
                DBG_BF_ASSERT(0, "STRIP"); //STRIP001 /*?*/ 			pLastFont = pSpaceFont;
//STRIP001 /*?*/ 			pLastFont->SetDevFont( rDo.GetInf().GetShell(), rDo.GetOut() );
//STRIP001 /*?*/ 			( (SwDoDrawCapital&) rDo ).DrawSpace( aStartPos );
/*N*/ 		}
/*N*/ 		if ( bWordWise )
/*?*/ 			delete pSpaceFontAccess;
/*N*/ 	}
/*N*/ 	pLastFont =	pOldLast;
/*N*/ 	pLastFont->SetDevFont( rDo.GetInf().GetShell(), rDo.GetOut() );
/*N*/ 
/*N*/ 	delete pSmallFontAccess;
/*N*/ 	rDo.GetInf().SetText( rOldText );
/*N*/ 	rDo.GetInf().SetKanaDiff( nKana );
/*N*/ }

// JP 22.8.2001 - global optimization off - Bug 91245 / 91223
#if defined( WNT ) && defined( MSC )
#pragma optimize("g",on)
#endif


}
