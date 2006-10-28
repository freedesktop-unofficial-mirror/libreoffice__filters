/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: eeitemid.hxx,v $
 *
 *  $Revision: 1.5 $
 *
 *  last change: $Author: rt $ $Date: 2006-10-28 03:30:42 $
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

#ifndef _EEITEMID_HXX
#define _EEITEMID_HXX

namespace binfilter {

#ifdef ITEMID_FONT
#undef ITEMID_FONT
#endif
#ifdef ITEMID_FONTHEIGHT
#undef ITEMID_FONTHEIGHT
#endif
#ifdef ITEMID_COLOR
#undef ITEMID_COLOR
#endif
#ifdef ITEMID_WEIGHT
#undef ITEMID_WEIGHT
#endif
#ifdef ITEMID_POSTURE
#undef ITEMID_POSTURE
#endif
#ifdef ITEMID_SHADOWED
#undef ITEMID_SHADOWED
#endif
#ifdef ITEMID_CONTOUR
#undef ITEMID_CONTOUR
#endif
#ifdef ITEMID_CROSSEDOUT
#undef ITEMID_CROSSEDOUT
#endif
#ifdef ITEMID_UNDERLINE
#undef ITEMID_UNDERLINE
#endif
#ifdef ITEMID_LANGUAGE
#undef ITEMID_LANGUAGE
#endif
#ifdef ITEMID_ADJUST
#undef ITEMID_ADJUST
#endif
#ifdef ITEMID_WORDLINEMODE
#undef ITEMID_WORDLINEMODE
#endif
#ifdef ITEMID_CHARSETCOLOR
#undef ITEMID_CHARSETCOLOR
#endif
#ifdef ITEMID_SEARCH
#undef ITEMID_SEARCH
#endif
#ifdef ITEMID_BRUSH
#undef ITEMID_BRUSH
#endif

// Zeichenattribute....
#define ITEMID_FONT 			EE_CHAR_FONTINFO
#define ITEMID_POSTURE			EE_CHAR_ITALIC
#define ITEMID_WEIGHT			EE_CHAR_WEIGHT
#define ITEMID_SHADOWED			EE_CHAR_SHADOW
#define ITEMID_CONTOUR			EE_CHAR_OUTLINE
#define ITEMID_CROSSEDOUT		EE_CHAR_STRIKEOUT
#define ITEMID_UNDERLINE		EE_CHAR_UNDERLINE
#define ITEMID_FONTHEIGHT		EE_CHAR_FONTHEIGHT
#define ITEMID_CHARSCALE_W		EE_CHAR_FONTWIDTH
#define ITEMID_COLOR 			EE_CHAR_COLOR
#define ITEMID_WORDLINEMODE		EE_CHAR_WLM
#define ITEMID_PROPSIZE			0
#define ITEMID_CHARSETCOLOR		0	// EE_FEATURE_NOTCONV
#define ITEMID_CASEMAP			0
#define ITEMID_LANGUAGE			0
#define ITEMID_ESCAPEMENT		EE_CHAR_ESCAPEMENT
#define ITEMID_NOLINEBREAK		0
#define ITEMID_NOHYPHENHERE		0
#define ITEMID_AUTOKERN			EE_CHAR_PAIRKERNING
#define ITEMID_KERNING			EE_CHAR_KERNING
#define ITEMID_EMPHASISMARK		EE_CHAR_EMPHASISMARK
#define ITEMID_CHARRELIEF		EE_CHAR_RELIEF

// Absatzattribute
#define ITEMID_SCRIPTSPACE		EE_PARA_ASIANCJKSPACING
#define ITEMID_ADJUST			EE_PARA_JUST
#define ITEMID_LINESPACING		EE_PARA_SBL
#define ITEMID_WIDOWS			0
#define ITEMID_ORPHANS			0
#define ITEMID_HYPHENZONE		0

#define ITEMID_TABSTOP			EE_PARA_TABS

#define ITEMID_PAPERBIN			0
#define ITEMID_LRSPACE			EE_PARA_LRSPACE
#define ITEMID_ULSPACE			EE_PARA_ULSPACE
#define ITEMID_FRAMEDIR         EE_PARA_WRITINGDIR
#define ITEMID_PRINT			0
#define ITEMID_OPAQUE			0
#define ITEMID_PROTECT			0
#define ITEMID_BACKGROUND		0
#define ITEMID_SHADOW			0
#define ITEMID_MACRO			0
#define ITEMID_BOX				0
#define ITEMID_BOXINFO			0
#define ITEMID_BRUSH			0

#define ITEMID_FIELD			EE_FEATURE_FIELD

#define ITEMID_SEARCH			0

}//end of namespace binfilter
#endif //_EEITEMID_HXX

