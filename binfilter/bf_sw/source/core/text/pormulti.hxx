/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: pormulti.hxx,v $
 *
 *  $Revision: 1.7 $
 *
 *  last change: $Author: rt $ $Date: 2008-03-12 10:17:53 $
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

#ifndef _PORMULTI_HXX
#define _PORMULTI_HXX

#include "porlay.hxx"
#include "porexp.hxx"
namespace binfilter {

class SfxPoolItem; 
class SwTxtFormatInfo;
class SwFldPortion;
class SwTxtCursor;
class SwLineLayout;
class SwBlankPortion;
class SwTxtPaintInfo;
class SwTxtAttr;
 
class SwFont;

/*-----------------02.02.01 15:01-------------------
 * SwMultiCreator is a small structur to create a multiportion.
 * It contains the kind of multiportion and a textattribute
 * or a poolitem.
 * The GetMultiCreator-function fills this structur and
 * the Ctor of the SwMultiPortion uses it.
 * --------------------------------------------------*/

#define SW_MC_DOUBLE	0
#define SW_MC_RUBY		1
#define SW_MC_ROTATE	2
#ifdef BIDI
#define SW_MC_BIDI      3
#endif

struct SwMultiCreator
{
    const SwTxtAttr* pAttr;
    const SfxPoolItem* pItem;
    BYTE nId;
#ifdef BIDI
    BYTE nLevel;
#endif
};

/*-----------------25.10.00 16:19-------------------
 * A two-line-portion (SwMultiPortion) could have surrounding brackets,
 * in this case the structur SwBracket will be used.
 * --------------------------------------------------*/

struct SwBracket
{
    xub_StrLen nStart;		// Start of text attribute determins the font
    KSHORT nAscent;         // Ascent of the brackets
    KSHORT nHeight;			// Height of them
    KSHORT nPreWidth;		// Width of the opening bracket
    KSHORT nPostWidth;      // Width of the closing bracket
    sal_Unicode cPre;       // Initial character, e.g. '('
    sal_Unicode cPost;      // Final character, e.g. ')'
    BYTE nPreScript;		// Script of the initial character
    BYTE nPostScript;       // Script of the final character
};

/*-----------------16.10.00 12:45-------------------
 * The SwMultiPortion is line portion inside a line portion,
 * it's a group of portions,
 * e.g. a double line portion in a line
 * or phonetics (ruby)
 * or combined characters
 * or a rotated portion.
 * --------------------------------------------------*/

class SwMultiPortion : public SwLinePortion
{
     SwLineLayout aRoot;		// One or more lines
     SwFldPortion *pFldRest;	// Field rest from the previous line
     sal_Bool bTab1		:1; // First line tabulator
     sal_Bool bTab2		:1; // Second line includes tabulator
     sal_Bool bDouble	:1; // Double line
     sal_Bool bRuby		:1; // Phonetics
 #ifdef BIDI
    sal_Bool bBidi      :1;
 #endif
     sal_Bool bTop		:1; // Phonetic position
     sal_Bool bFormatted :1; // Already formatted
    sal_Bool bFollowFld :1; // Field follow inside
    sal_uInt8 nDirection:2; // Direction (0/90/180/270 degrees)
    sal_Bool bFlyInCntnt:1; // Fly as character inside
protected:
SwMultiPortion( xub_StrLen nEnd ) : pFldRest( 0 ), bTab1( sal_False ),
 #ifdef BIDI
         bTab2( sal_False ), bDouble( sal_False ), bRuby( sal_False ),
         bBidi( sal_False ), bFormatted( sal_False ), bFollowFld( sal_False ),
         nDirection( 0 ), bFlyInCntnt( sal_False )
 #else
         bTab2( sal_False ),	bDouble( sal_False ), bRuby( sal_False ),
         bFormatted( sal_False ), bFollowFld( sal_False ), nDirection( 0 ),
         bFlyInCntnt( sal_False )
 #endif
         { SetWhichPor( POR_MULTI ); SetLen( nEnd ); }
public:
     const SwLineLayout& GetRoot() const { return aRoot; }
     SwLineLayout& GetRoot() { return aRoot; }
    inline sal_Bool HasTabulator() const{DBG_BF_ASSERT(0, "STRIP"); return FALSE;} //STRIP001 	inline sal_Bool HasTabulator() const { return bTab1 || bTab2; }
    inline sal_Bool IsFollowFld() const { return bFollowFld; }
    inline sal_Bool HasFlyInCntnt() const { return bFlyInCntnt; }
    inline sal_Bool IsDouble() const{DBG_BF_ASSERT(0, "STRIP"); return FALSE;} //STRIP001 	inline sal_Bool IsDouble() const { return bDouble; }
#ifdef BIDI
    inline sal_Bool IsBidi() const { return bBidi; }
#endif
    inline sal_Bool HasRotation() const { return 0 != (1 & nDirection); }
    OUTPUT_OPERATOR
};

/*************************************************************************
 *					inline - Implementations
 *************************************************************************/

#ifndef BIDI
inline sal_Bool SwMultiPortion::ChgSpaceAdd(SwLineLayout* pCurr,short nSpaceAdd)
    { return IsDouble() ? ((SwDoubleLinePortion*)this)->ChangeSpaceAdd( pCurr,
                            nSpaceAdd ) : sal_False; }
#endif


CLASSIO( SwMultiPortion )

} //namespace binfilter
#endif
