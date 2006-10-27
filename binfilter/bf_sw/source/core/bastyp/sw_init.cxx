/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: sw_init.cxx,v $
 *
 *  $Revision: 1.6 $
 *
 *  last change: $Author: rt $ $Date: 2006-10-27 22:16:05 $
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

#define ITEMID_BOXINFO      SID_ATTR_BORDER_INNER

#ifndef _HINTIDS_HXX
#include <hintids.hxx>
#endif

#ifndef _GLOBNAME_HXX
#include <tools/globname.hxx>
#endif
#ifndef _SV_MAPMOD_HXX
#include <vcl/mapmod.hxx>
#endif

#ifndef _SVX_XMLCNITM_HXX
#include <bf_svx/xmlcnitm.hxx>
#endif

#ifndef _SFXMACITEM_HXX
#include <svtools/macitem.hxx>
#endif
#ifndef _SVX_PBINITEM_HXX
#include <bf_svx/pbinitem.hxx>
#endif
#ifndef _SVX_KEEPITEM_HXX
#include <bf_svx/keepitem.hxx>
#endif
#ifndef _SVX_NLBKITEM_HXX
#include <bf_svx/nlbkitem.hxx>
#endif
#ifndef _SVX_HYZNITEM_HXX
#include <bf_svx/hyznitem.hxx>
#endif
#ifndef _SVX_PROTITEM_HXX
#include <bf_svx/protitem.hxx>
#endif
#ifndef _SVX_ULSPITEM_HXX
#include <bf_svx/ulspitem.hxx>
#endif
#ifndef _SVX_PRSZITEM_HXX
#include <bf_svx/prszitem.hxx>
#endif
#ifndef _SVX_OPAQITEM_HXX
#include <bf_svx/opaqitem.hxx>
#endif
#ifndef _SVX_SHADITEM_HXX
#include <bf_svx/shaditem.hxx>
#endif
#ifndef _SVX_PRNTITEM_HXX
#include <bf_svx/prntitem.hxx>
#endif
#ifndef _SVX_BRKITEM_HXX
#include <bf_svx/brkitem.hxx>
#endif
#ifndef _SVX_TSTPITEM_HXX
#include <bf_svx/tstpitem.hxx>
#endif
#ifndef _SVX_LANGITEM_HXX
#include <bf_svx/langitem.hxx>
#endif
#ifndef _SVX_WRLMITEM_HXX
#include <bf_svx/wrlmitem.hxx>
#endif
#ifndef _SVX_KERNITEM_HXX
#include <bf_svx/kernitem.hxx>
#endif
#ifndef _SVX_ESCPITEM_HXX
#include <bf_svx/escpitem.hxx>
#endif
#ifndef _SVX_CSCOITEM_HXX
#include <bf_svx/cscoitem.hxx>
#endif
#ifndef _SVX_LRSPITEM_HXX
#include <bf_svx/lrspitem.hxx>
#endif
#ifndef _SVX_ORPHITEM_HXX
#include <bf_svx/orphitem.hxx>
#endif
#ifndef _SVX_WIDWITEM_HXX
#include <bf_svx/widwitem.hxx>
#endif
#ifndef _SVX_NHYPITEM_HXX
#include <bf_svx/nhypitem.hxx>
#endif
#ifndef _SVX_SPLTITEM_HXX
#include <bf_svx/spltitem.hxx>
#endif
#ifndef _SVX_LSPCITEM_HXX
#include <bf_svx/lspcitem.hxx>
#endif
#ifndef _SVX_BLNKITEM_HXX
#include <bf_svx/blnkitem.hxx>
#endif
#ifndef _SVX_AKRNITEM_HXX
#include <bf_svx/akrnitem.hxx>
#endif
#ifndef _SVX_EMPHITEM_HXX
#include <bf_svx/emphitem.hxx>
#endif
#ifndef _SVX_TWOLINESITEM_HXX
#include <bf_svx/twolinesitem.hxx>
#endif
#ifndef _SVX_SCRIPSPACEITEM_HXX
#include <bf_svx/scriptspaceitem.hxx>
#endif
#ifndef _SVX_HNGPNCTITEM_HXX
#include <bf_svx/hngpnctitem.hxx>
#endif
#ifndef _SVX_CMAPITEM_HXX
#include <bf_svx/cmapitem.hxx>
#endif
#ifndef _SVX_CHARSCALEITEM_HXX
#include <bf_svx/charscaleitem.hxx>
#endif
#ifndef _SVX_CHARROTATEITEM_HXX
#include <bf_svx/charrotateitem.hxx>
#endif
#ifndef _SVX_CHARRELIEFITEM_HXX
#include <bf_svx/charreliefitem.hxx>
#endif
#ifndef _SVX_FRMDIRITEM_HXX
#include <bf_svx/frmdiritem.hxx>
#endif
#ifndef _SVX_DIALOGS_HRC
#include <bf_svx/dialogs.hrc>
#endif
#ifndef _MySVXACORR_HXX
#include <bf_svx/svxacorr.hxx>
#endif
#ifndef _OFF_APP_HXX
#include <bf_offmgr/app.hxx>
#endif
#ifndef _SVX_FORBIDDENRULEITEM_HXX
#include <bf_svx/forbiddenruleitem.hxx>
#endif
#ifndef _SVX_PARAVERTALIGNITEM_HXX
#include <bf_svx/paravertalignitem.hxx>
#endif
#ifndef _SVX_PGRDITEM_HXX
#include <bf_svx/pgrditem.hxx>
#endif


#ifndef _FMTHBSH_HXX
#include <fmthbsh.hxx>
#endif
#ifndef _FMTANCHR_HXX
#include <fmtanchr.hxx>
#endif

#ifndef _HORIORNT_HXX
#include <horiornt.hxx>
#endif

#ifndef _FMTORNT_HXX
#include <fmtornt.hxx>
#endif
#ifndef _FMTSRND_HXX
#include <fmtsrnd.hxx>
#endif
#ifndef _FMTFSIZE_HXX
#include <fmtfsize.hxx>
#endif
#ifndef _FMTFLD_HXX
#include <fmtfld.hxx>
#endif
#ifndef _FMTRFMRK_HXX
#include <fmtrfmrk.hxx>
#endif
#ifndef _FMTTSPLT_HXX
#include <fmtlsplt.hxx>
#endif
#ifndef _FMTEIRO_HXX
#include <fmteiro.hxx>
#endif
#ifndef _FMTCLDS_HXX
#include <fmtclds.hxx>
#endif
#ifndef _FMTURL_HXX
#include <fmturl.hxx>
#endif
#ifndef _FMTCNTNT_HXX
#include <fmtcntnt.hxx>
#endif
#ifndef _FMTHDFT_HXX
#include <fmthdft.hxx>
#endif
#ifndef _FMTPDSC_HXX
#include <fmtpdsc.hxx>
#endif
#ifndef _FMTFTN_HXX
#include <fmtftn.hxx>
#endif
#ifndef _FMTFORDR_HXX
#include <fmtfordr.hxx>
#endif
#ifndef _FMTFLCNT_HXX
#include <fmtflcnt.hxx>
#endif
#ifndef _FCHRFMT_HXX
#include <fchrfmt.hxx>
#endif
#ifndef _FMTINFMT_HXX
#include <fmtinfmt.hxx>
#endif
#ifndef _FMTCNCT_HXX
#include <fmtcnct.hxx>
#endif
#ifndef _FMTLINE_HXX
#include <fmtline.hxx>
#endif
#ifndef _FMTFTNTX_HXX
#include <fmtftntx.hxx>
#endif
#ifndef _FMTRUBY_HXX
#include <fmtruby.hxx>
#endif
#ifndef SW_TGRDITEM_HXX
#include <tgrditem.hxx>
#endif
#ifndef _SW_HF_EAT_SPACINGITEM_HXX
#include <hfspacingitem.hxx>
#endif
#ifndef _EDITSH_HXX
#include <editsh.hxx>
#endif
#ifndef _INIT_HXX
#include <init.hxx>
#endif
#ifndef _PARATR_HXX
#include <paratr.hxx>
#endif
#ifndef _GRFATR_HXX
#include <grfatr.hxx>
#endif
#ifndef _TOX_HXX
#include <tox.hxx>
#endif
#ifndef _CELLATR_HXX
#include <cellatr.hxx>
#endif
#ifndef _TBLAFMT_HXX
#include <tblafmt.hxx>
#endif
#ifndef _VISCRS_HXX
#include <viscrs.hxx>
#endif
#ifndef _FNTCACHE_HXX
#include <fntcache.hxx>
#endif
#ifndef _DOC_HXX
#include <doc.hxx>
#endif
#ifndef _ACMPLWRD_HXX
#include <acmplwrd.hxx>
#endif
#ifndef _FMTCLBL_HXX
#include <fmtclbl.hxx>
#endif
#ifndef _CMDID_H
#include <cmdid.h>
#endif
#ifndef _BREAKIT_HXX
#include <breakit.hxx>
#endif
#ifndef _CHECKIT_HXX
#include <checkit.hxx>
#endif

#ifndef _SWCALWRP_HXX
#include <swcalwrp.hxx>
#endif
#ifndef _SWSTYLENAMEMAPPER_HXX
#include <SwStyleNameMapper.hxx>
#endif
#ifndef _LEGACYBINFILTERMGR_HXX
#include <legacysmgr/legacy_binfilters_smgr.hxx>	//STRIP002 
#endif
namespace binfilter {

extern void _FrmFinit();
extern void ClearFEShellTabCols();

/*************************************************************************
|*	einige Bereiche fuer die Set in Collections / Nodes
|*************************************************************************/
    // AttrSet-Range fuer die 2 Break-Attribute
USHORT __FAR_DATA aBreakSetRange[] = {
    RES_PAGEDESC, RES_BREAK,
    0 };

    // AttrSet-Range fuer die TxtFmtColl
USHORT __FAR_DATA aTxtFmtCollSetRange[] = {
    RES_FRMATR_BEGIN, RES_FRMATR_END-1,
    RES_CHRATR_BEGIN, RES_CHRATR_END-1,
    RES_PARATR_BEGIN, RES_PARATR_END-1,
    RES_UNKNOWNATR_BEGIN, RES_UNKNOWNATR_END-1,
    0
};

    // AttrSet-Range fuer die GrfFmtColl
USHORT __FAR_DATA aGrfFmtCollSetRange[] = {
    RES_FRMATR_BEGIN, RES_FRMATR_END-1,
    RES_GRFATR_BEGIN, RES_GRFATR_END-1,
    RES_UNKNOWNATR_BEGIN, RES_UNKNOWNATR_END-1,
    0
};

    // AttrSet-Range fuer die TextNode
USHORT __FAR_DATA aTxtNodeSetRange[] = {
    RES_FRMATR_BEGIN, RES_FRMATR_END-1,
    RES_CHRATR_BEGIN, RES_CHRATR_END-1,
    RES_PARATR_BEGIN, RES_PARATR_END-1,
    RES_UNKNOWNATR_BEGIN, RES_UNKNOWNATR_END-1,
    0
};

    // AttrSet-Range fuer die NoTxtNode
USHORT __FAR_DATA aNoTxtNodeSetRange[] = {
    RES_FRMATR_BEGIN, RES_FRMATR_END-1,
    RES_GRFATR_BEGIN, RES_GRFATR_END-1,
    RES_UNKNOWNATR_BEGIN, RES_UNKNOWNATR_END-1,
    0
};

USHORT __FAR_DATA aTableSetRange[] = {
    RES_FILL_ORDER, 	RES_FRM_SIZE,
    RES_LR_SPACE, 		RES_BREAK,
    RES_BACKGROUND, 	RES_SHADOW,
    RES_HORI_ORIENT,	RES_HORI_ORIENT,
    RES_KEEP,			RES_KEEP,
    RES_LAYOUT_SPLIT,	RES_LAYOUT_SPLIT,
    RES_FRAMEDIR,       RES_FRAMEDIR,
    RES_UNKNOWNATR_BEGIN, RES_UNKNOWNATR_END-1,
    0
};

USHORT __FAR_DATA aTableLineSetRange[] = {
    RES_FILL_ORDER, 	RES_FRM_SIZE,
    RES_LR_SPACE, 		RES_UL_SPACE,
    RES_BACKGROUND, 	RES_SHADOW,
    RES_PROTECT, 		RES_PROTECT,
    RES_VERT_ORIENT,	RES_VERT_ORIENT,
    RES_UNKNOWNATR_BEGIN, RES_UNKNOWNATR_END-1,
    0
};

USHORT __FAR_DATA aTableBoxSetRange[] = {
    RES_FILL_ORDER, 	RES_FRM_SIZE,
    RES_LR_SPACE, 		RES_UL_SPACE,
    RES_BACKGROUND, 	RES_SHADOW,
    RES_PROTECT, 		RES_PROTECT,
    RES_VERT_ORIENT,	RES_VERT_ORIENT,
    RES_BOXATR_BEGIN,	RES_BOXATR_END-1,
    RES_UNKNOWNATR_BEGIN, RES_UNKNOWNATR_END-1,
    0
};

// AttrSet-Range fuer die SwFrmFmt
USHORT __FAR_DATA aFrmFmtSetRange[] = {
    RES_FRMATR_BEGIN, RES_FRMATR_END-1,
    RES_UNKNOWNATR_BEGIN, RES_UNKNOWNATR_END-1,
    0
};

// AttrSet-Range fuer die SwCharFmt
USHORT __FAR_DATA aCharFmtSetRange[] = {
    RES_CHRATR_BEGIN, RES_CHRATR_END-1,
    RES_UNKNOWNATR_BEGIN, RES_UNKNOWNATR_END-1,
    0
};

// AttrSet-Range fuer die SwPageDescFmt
USHORT __FAR_DATA aPgFrmFmtSetRange[] = {
    RES_FRMATR_BEGIN, RES_FRMATR_END-1,
    RES_UNKNOWNATR_BEGIN, RES_UNKNOWNATR_END-1,
    0
};

/******************************************************************************
 * lege eine Tabelle fuer einen Zugriff auf die
 * Default-Format-Attribute an
 ******************************************************************************/
SwDfltAttrTab __FAR_DATA aAttrTab;

SfxItemInfo __FAR_DATA aSlotTab[] =
{
    { SID_ATTR_CHAR_CASEMAP, SFX_ITEM_POOLABLE },   	// RES_CHRATR_CASEMAP
    { SID_ATTR_CHAR_CHARSETCOLOR, SFX_ITEM_POOLABLE },	// RES_CHRATR_CHARSETCOLOR
    { SID_ATTR_CHAR_COLOR, SFX_ITEM_POOLABLE },     	// RES_CHRATR_COLOR
    { SID_ATTR_CHAR_CONTOUR, SFX_ITEM_POOLABLE },    	// RES_CHRATR_CONTOUR
    { SID_ATTR_CHAR_STRIKEOUT, SFX_ITEM_POOLABLE },  	// RES_CHRATR_CROSSEDOUT
    { SID_ATTR_CHAR_ESCAPEMENT, SFX_ITEM_POOLABLE }, 	// RES_CHRATR_ESCAPEMENT
    { SID_ATTR_CHAR_FONT, SFX_ITEM_POOLABLE },     		// RES_CHRATR_FONT
    { SID_ATTR_CHAR_FONTHEIGHT, SFX_ITEM_POOLABLE }, 	// RES_CHRATR_FONTSIZE
    { SID_ATTR_CHAR_KERNING, SFX_ITEM_POOLABLE },    	// RES_CHRATR_KERNING
    { SID_ATTR_CHAR_LANGUAGE, SFX_ITEM_POOLABLE },   	// RES_CHRATR_LANGUAGE
    { SID_ATTR_CHAR_POSTURE, SFX_ITEM_POOLABLE },    	// RES_CHRATR_POSTURE
    { SID_ATTR_CHAR_PROPSIZE, SFX_ITEM_POOLABLE },   	// RES_CHRATR_PROPORTIONALFONTSIZE
    { SID_ATTR_CHAR_SHADOWED, SFX_ITEM_POOLABLE },   	// RES_CHRATR_SHADOWED
    { SID_ATTR_CHAR_UNDERLINE, SFX_ITEM_POOLABLE },  	// RES_CHRATR_UNDERLINE
    { SID_ATTR_CHAR_WEIGHT, SFX_ITEM_POOLABLE },     	// RES_CHRATR_WEIGHT
    { SID_ATTR_CHAR_WORDLINEMODE, SFX_ITEM_POOLABLE },	// RES_CHRATR_WORDLINEMODE
    { SID_ATTR_CHAR_AUTOKERN, SFX_ITEM_POOLABLE },	   	// RES_CHRATR_AUTOKERN
    { SID_ATTR_FLASH, SFX_ITEM_POOLABLE },				// RES_CHRATR_BLINK
    { 0, SFX_ITEM_POOLABLE },							// RES_CHRATR_NOLINEBREAK
    { 0, SFX_ITEM_POOLABLE },							// RES_CHRATR_NOHYPHEN
    { SID_ATTR_BRUSH_CHAR, SFX_ITEM_POOLABLE },			// RES_CHRATR_BACKGROUND
    { SID_ATTR_CHAR_CJK_FONT, SFX_ITEM_POOLABLE },		// RES_CHRATR_CJK_FONT
    { SID_ATTR_CHAR_CJK_FONTHEIGHT, SFX_ITEM_POOLABLE },// RES_CHRATR_CJK_FONTSIZE
    { SID_ATTR_CHAR_CJK_LANGUAGE, SFX_ITEM_POOLABLE },	// RES_CHRATR_CJK_LANGUAGE
    { SID_ATTR_CHAR_CJK_POSTURE, SFX_ITEM_POOLABLE },	// RES_CHRATR_CJK_POSTURE
    { SID_ATTR_CHAR_CJK_WEIGHT, SFX_ITEM_POOLABLE },	// RES_CHRATR_CJK_WEIGHT
    { SID_ATTR_CHAR_CTL_FONT, SFX_ITEM_POOLABLE },		// RES_CHRATR_CTL_FONT
    { SID_ATTR_CHAR_CTL_FONTHEIGHT, SFX_ITEM_POOLABLE },// RES_CHRATR_CTL_FONTSIZE
    { SID_ATTR_CHAR_CTL_LANGUAGE, SFX_ITEM_POOLABLE },	// RES_CHRATR_CTL_LANGUAGE
    { SID_ATTR_CHAR_CTL_POSTURE, SFX_ITEM_POOLABLE },	// RES_CHRATR_CTL_POSTURE
    { SID_ATTR_CHAR_CTL_WEIGHT, SFX_ITEM_POOLABLE },	// RES_CHRATR_CTL_WEIGHT
    { SID_ATTR_CHAR_ROTATED, SFX_ITEM_POOLABLE },		// RES_CHRATR_ROTATE
    { SID_ATTR_CHAR_EMPHASISMARK, SFX_ITEM_POOLABLE },	// RES_CHRATR_EMPHASIS_MARK
    { SID_ATTR_CHAR_TWO_LINES, SFX_ITEM_POOLABLE },		// RES_CHRATR_TWO_LINES
    { SID_ATTR_CHAR_SCALEWIDTH, SFX_ITEM_POOLABLE },	// RES_CHRATR_SCALEW
    { SID_ATTR_CHAR_RELIEF, SFX_ITEM_POOLABLE },		// RES_CHRATR_RELIEF
    { 0, SFX_ITEM_POOLABLE },							// RES_CHRATR_DUMMY1

    { FN_TXTATR_INET, 0 }, 								// RES_TXTATR_INETFMT
    { 0, SFX_ITEM_POOLABLE },					 		// RES_TXTATR_DUMMY4
    { 0, 0 }, 											// RES_TXTATR_REFMARK
    { 0, 0 },											// RES_TXTATR_TOXMARK
    { 0, 0 },											// RES_TXTATR_CHARFMT
    { 0, SFX_ITEM_POOLABLE },					 		// RES_TXTATR_DUMMY5,
    { SID_ATTR_CHAR_CJK_RUBY, 0 },					 	// RES_TXTATR_CJK_RUBY,
    { 0, SFX_ITEM_POOLABLE },					 		// RES_TXTATR_UNKNOWN_CONTAINER,
    { 0, SFX_ITEM_POOLABLE },					 		// RES_TXTATR_DUMMY6,
    { 0, SFX_ITEM_POOLABLE },					 		// RES_TXTATR_DUMMY7,

    { 0, 0 },											// RES_TXTATR_FIELD
    { 0, 0 },											// RES_TXTATR_FLYCNT
    { 0, 0 },											// RES_TXTATR_FTN
    { 0, SFX_ITEM_POOLABLE },							// RES_TXTATR_SOFTHYPH
    { 0, SFX_ITEM_POOLABLE },							// RES_TXTATR_HARDBLANK
    { 0, SFX_ITEM_POOLABLE },							// RES_TXTATR_DUMMY1
    { 0, SFX_ITEM_POOLABLE },							// RES_TXTATR_DUMMY2

    { SID_ATTR_PARA_LINESPACE, SFX_ITEM_POOLABLE }, 	// RES_PARATR_LINESPACING
    { SID_ATTR_PARA_ADJUST, SFX_ITEM_POOLABLE }, 		// RES_PARATR_ADJUST
    { SID_ATTR_PARA_SPLIT, SFX_ITEM_POOLABLE }, 		// RES_PARATR_SPLIT
    { SID_ATTR_PARA_ORPHANS, SFX_ITEM_POOLABLE },  		// RES_PARATR_ORPHANS
    { SID_ATTR_PARA_WIDOWS, SFX_ITEM_POOLABLE }, 		// RES_PARATR_WIDOWS
    { SID_ATTR_TABSTOP, SFX_ITEM_POOLABLE }, 			// RES_PARATR_TABSTOP
    { SID_ATTR_PARA_HYPHENZONE, SFX_ITEM_POOLABLE }, 	// RES_PARATR_HYPHENZONE
    { FN_FORMAT_DROPCAPS, 0 },							// RES_PARATR_DROP
    { SID_ATTR_PARA_REGISTER, SFX_ITEM_POOLABLE },		// RES_PARATR_REGISTER
    { SID_ATTR_PARA_NUMRULE, 0 },						// RES_PARATR_NUMRULE
    { SID_ATTR_PARA_SCRIPTSPACE, SFX_ITEM_POOLABLE },	// RES_PARATR_SCRIPTSPACE
    { SID_ATTR_PARA_HANGPUNCTUATION, SFX_ITEM_POOLABLE },// RES_PARATR_HANGINGPUNCTUATION

    { SID_ATTR_PARA_FORBIDDEN_RULES, SFX_ITEM_POOLABLE },// RES_PARATR_FORBIDDEN_RULES
    { SID_PARA_VERTALIGN, SFX_ITEM_POOLABLE },          // RES_PARATR_VERTALIGN
    { SID_ATTR_PARA_SNAPTOGRID, SFX_ITEM_POOLABLE },    // RES_PARATR_SNAPTOGRID
    { 0, SFX_ITEM_POOLABLE },                           // RES_PARATR_CONNECT_BORDER
    { 0, SFX_ITEM_POOLABLE },							// RES_PARATR_DUMMY5
    { 0, SFX_ITEM_POOLABLE },							// RES_PARATR_DUMMY6
    { 0, SFX_ITEM_POOLABLE },							// RES_PARATR_DUMMY7
    { 0, SFX_ITEM_POOLABLE },							// RES_PARATR_DUMMY8

    { 0, SFX_ITEM_POOLABLE },							// RES_FILL_ORDER
    { 0, SFX_ITEM_POOLABLE }, 							// RES_FRM_SIZE
    { SID_ATTR_PAGE_PAPERBIN, SFX_ITEM_POOLABLE }, 		// RES_PAPER_BIN
    { SID_ATTR_LRSPACE, SFX_ITEM_POOLABLE }, 			// RES_LR_SPACE
    { SID_ATTR_ULSPACE, SFX_ITEM_POOLABLE }, 			// RES_UL_SPACE
    { 0, 0 },											// RES_PAGEDESC
    { SID_ATTR_PARA_PAGEBREAK, SFX_ITEM_POOLABLE }, 	// RES_BREAK
    { 0, 0 },											// RES_CNTNT
    { 0, SFX_ITEM_POOLABLE },							// RES_HEADER
    { 0, SFX_ITEM_POOLABLE },							// RES_FOOTER
    { 0, SFX_ITEM_POOLABLE },							// RES_PRINT
    { FN_OPAQUE, SFX_ITEM_POOLABLE },					// RES_OPAQUE
    { FN_SET_PROTECT, SFX_ITEM_POOLABLE },				// RES_PROTECT
    { FN_SURROUND, SFX_ITEM_POOLABLE },					// RES_SURROUND
    { FN_VERT_ORIENT, SFX_ITEM_POOLABLE },				// RES_VERT_ORIENT
    { FN_HORI_ORIENT, SFX_ITEM_POOLABLE },				// RES_HORI_ORIENT
    { 0, 0 },											// RES_ANCHOR
    { SID_ATTR_BRUSH, SFX_ITEM_POOLABLE },		 		// RES_BACKGROUND
    { SID_ATTR_BORDER_OUTER, SFX_ITEM_POOLABLE }, 		// RES_BOX
    { SID_ATTR_BORDER_SHADOW, SFX_ITEM_POOLABLE }, 		// RES_SHADOW
    { SID_ATTR_MACROITEM, SFX_ITEM_POOLABLE },			// RES_FRMMACRO
    { FN_ATTR_COLUMNS, SFX_ITEM_POOLABLE },				// RES_COL
    { SID_ATTR_PARA_KEEP, SFX_ITEM_POOLABLE },			// RES_KEEP
    { 0, SFX_ITEM_POOLABLE },							// RES_URL
    { 0, SFX_ITEM_POOLABLE },							// RES_EDIT_IN_READONLY

    { 0, SFX_ITEM_POOLABLE },							// RES_LAYOUT_SPLIT
    { 0, 0 },											// RES_CHAIN
    { 0, SFX_ITEM_POOLABLE },                           // RES_TEXTGRID
    { FN_FORMAT_LINENUMBER, SFX_ITEM_POOLABLE },        // RES_LINENUMBER
    { 0, SFX_ITEM_POOLABLE },							// RES_FTN_AT_TXTEND
    { 0, SFX_ITEM_POOLABLE },							// RES_END_AT_TXTEND
    { 0, SFX_ITEM_POOLABLE },							// RES_COLUMNBALANCE

#ifdef VERTICAL_LAYOUT
    { SID_ATTR_FRAMEDIRECTION, SFX_ITEM_POOLABLE },		// RES_FRAMEDIR
#else
    { 0, SFX_ITEM_POOLABLE },							// RES_FRAMEDIR
#endif

    { SID_ATTR_HDFT_DYNAMIC_SPACING, SFX_ITEM_POOLABLE }, // RES_HEADER_FOOTER_EAT_SPACING
    { 0, SFX_ITEM_POOLABLE },							// RES_FRMATR_DUMMY9

    { 0, SFX_ITEM_POOLABLE },							// RES_GRFATR_MIRRORGRF
    { SID_ATTR_GRAF_CROP, SFX_ITEM_POOLABLE }, 			// RES_GRFATR_CROPGRF
    { 0, SFX_ITEM_POOLABLE },							// RES_GRFATR_ROTATION,
    { 0, SFX_ITEM_POOLABLE },							// RES_GRFATR_LUMINANCE,
    { 0, SFX_ITEM_POOLABLE },							// RES_GRFATR_CONTRAST,
    { 0, SFX_ITEM_POOLABLE },							// RES_GRFATR_CHANNELR,
    { 0, SFX_ITEM_POOLABLE },							// RES_GRFATR_CHANNELG,
    { 0, SFX_ITEM_POOLABLE },							// RES_GRFATR_CHANNELB,
    { 0, SFX_ITEM_POOLABLE },							// RES_GRFATR_GAMMA,
    { 0, SFX_ITEM_POOLABLE },							// RES_GRFATR_INVERT,
    { 0, SFX_ITEM_POOLABLE },							// RES_GRFATR_TRANSPARENCY,
    { 0, SFX_ITEM_POOLABLE },							// RES_GRFATR_DUMMY1,
    { 0, SFX_ITEM_POOLABLE },							// RES_GRFATR_DUMMY2,
    { 0, SFX_ITEM_POOLABLE },							// RES_GRFATR_DUMMY3,
    { 0, SFX_ITEM_POOLABLE },							// RES_GRFATR_DUMMY4,
    { 0, SFX_ITEM_POOLABLE },							// RES_GRFATR_DUMMY5,
    { 0, SFX_ITEM_POOLABLE },							// RES_GRFATR_DUMMY6,

    { 0, SFX_ITEM_POOLABLE },							// RES_BOXATR_FORMAT
    { 0, 0 },											// RES_BOXATR_FORMULA,
    { 0, SFX_ITEM_POOLABLE },							// RES_BOXATR_VALUE

    { 0, SFX_ITEM_POOLABLE }							// RES_UNKNOWNATR_CONTAINER
};


USHORT* SwAttrPool::pVersionMap1 = 0;
USHORT* SwAttrPool::pVersionMap2 = 0;
USHORT* SwAttrPool::pVersionMap3 = 0;
USHORT* SwAttrPool::pVersionMap4 = 0;
SwIndexReg* SwIndexReg::pEmptyIndexArray = 0;

const sal_Char* __FAR_DATA pMarkToTable		= "table";
const sal_Char* __FAR_DATA pMarkToFrame		= "frame";
const sal_Char* __FAR_DATA pMarkToRegion	= "region";
const sal_Char* __FAR_DATA pMarkToText		= "text";
const sal_Char* __FAR_DATA pMarkToOutline	= "outline";
const sal_Char* __FAR_DATA pMarkToGraphic	= "graphic";
const sal_Char* __FAR_DATA pMarkToOLE		= "ole";

SvPtrarr *pGlobalOLEExcludeList = 0;

SwAutoCompleteWord* SwDoc::pACmpltWords = 0;

SwBreakIt* pBreakIt = 0;
SwCheckIt* pCheckIt = 0;
CharClass* pAppCharClass = 0;
SwCalendarWrapper* pCalendarWrapper = 0;
CollatorWrapper* pCollator = 0, *pCaseCollator = 0;
::utl::TransliterationWrapper* pTransWrp = 0;

/******************************************************************************
 *	void _InitCore()
 ******************************************************************************/
class SwDontWrite : public SfxBoolItem
{
public:
    SwDontWrite( USHORT nId ) : SfxBoolItem( nId ) {}

};





/*N*/ void _InitCore()
/*N*/ {
/*N*/ 	SfxPoolItem* pItem;
/*N*/ 
/*N*/ 	// erstmal alle Attribut-Pointer auf 0 setzen
/*N*/ 	memset( aAttrTab, 0, (POOLATTR_END - POOLATTR_BEGIN) *
/*N*/ 							sizeof( SfxPoolItem* ) );
/*N*/ 
/*N*/ 	aAttrTab[ RES_CHRATR_CASEMAP- POOLATTR_BEGIN ] = new SvxCaseMapItem;
/*N*/ 	aAttrTab[ RES_CHRATR_CHARSETCOLOR- POOLATTR_BEGIN ] = new SvxCharSetColorItem;
/*N*/ 	aAttrTab[ RES_CHRATR_COLOR- POOLATTR_BEGIN ] = new SvxColorItem;
/*N*/ 	aAttrTab[ RES_CHRATR_CONTOUR- POOLATTR_BEGIN ] = new SvxContourItem;
/*N*/ 	aAttrTab[ RES_CHRATR_CROSSEDOUT- POOLATTR_BEGIN ] = new SvxCrossedOutItem;
/*N*/ 	aAttrTab[ RES_CHRATR_ESCAPEMENT- POOLATTR_BEGIN ] = new SvxEscapementItem;
/*N*/ 	aAttrTab[ RES_CHRATR_FONT- POOLATTR_BEGIN ] =
/*N*/ 										new SvxFontItem( RES_CHRATR_FONT );
/*N*/ 
/*N*/ 	aAttrTab[ RES_CHRATR_FONTSIZE- POOLATTR_BEGIN ] = new SvxFontHeightItem;
/*N*/ 	aAttrTab[ RES_CHRATR_KERNING- POOLATTR_BEGIN ] = new SvxKerningItem;
/*N*/ 	aAttrTab[ RES_CHRATR_LANGUAGE- POOLATTR_BEGIN ] = new SvxLanguageItem(LANGUAGE_DONTKNOW);
/*N*/ 	aAttrTab[ RES_CHRATR_POSTURE- POOLATTR_BEGIN ] = new SvxPostureItem;
/*N*/ 	aAttrTab[ RES_CHRATR_PROPORTIONALFONTSIZE- POOLATTR_BEGIN ] = new SvxPropSizeItem;
/*N*/ 	aAttrTab[ RES_CHRATR_SHADOWED- POOLATTR_BEGIN ] = new SvxShadowedItem;
/*N*/ 	aAttrTab[ RES_CHRATR_UNDERLINE- POOLATTR_BEGIN ] = new SvxUnderlineItem;
/*N*/ 	aAttrTab[ RES_CHRATR_WEIGHT- POOLATTR_BEGIN ] = new SvxWeightItem;
/*N*/ 	aAttrTab[ RES_CHRATR_WORDLINEMODE- POOLATTR_BEGIN ] = new SvxWordLineModeItem;
/*N*/ 	aAttrTab[ RES_CHRATR_AUTOKERN- POOLATTR_BEGIN ] = new SvxAutoKernItem;
/*N*/ 	aAttrTab[ RES_CHRATR_BLINK - POOLATTR_BEGIN ]
/*N*/ 				= new SvxBlinkItem( FALSE, RES_CHRATR_BLINK );
/*N*/ 	aAttrTab[ RES_CHRATR_NOHYPHEN - POOLATTR_BEGIN ]
/*N*/ 				= new SvxNoHyphenItem( TRUE, RES_CHRATR_NOHYPHEN );
/*N*/ 	aAttrTab[ RES_CHRATR_NOLINEBREAK- POOLATTR_BEGIN ]
/*N*/ 				= new SvxNoLinebreakItem( TRUE, RES_CHRATR_NOLINEBREAK );
/*N*/ 	aAttrTab[ RES_CHRATR_BACKGROUND - POOLATTR_BEGIN ]
/*N*/ 				= new SvxBrushItem( RES_CHRATR_BACKGROUND );
/*N*/ 
/*N*/ 	// CJK-Attributes
/*N*/ 	aAttrTab[ RES_CHRATR_CJK_FONT - POOLATTR_BEGIN ] =
/*N*/ 									new SvxFontItem( RES_CHRATR_CJK_FONT );
/*N*/ 
/*N*/ 	pItem = new SvxFontHeightItem;
/*N*/ 	pItem->SetWhich( RES_CHRATR_CJK_FONTSIZE );
/*N*/ 	aAttrTab[ RES_CHRATR_CJK_FONTSIZE - POOLATTR_BEGIN ] = pItem;
/*N*/ 
/*N*/ 	pItem = new SvxLanguageItem(LANGUAGE_DONTKNOW);
/*N*/ 	pItem->SetWhich( RES_CHRATR_CJK_LANGUAGE );
/*N*/ 	aAttrTab[ RES_CHRATR_CJK_LANGUAGE - POOLATTR_BEGIN ] = pItem;
/*N*/ 
/*N*/ 	pItem = new SvxPostureItem;
/*N*/ 	pItem->SetWhich( RES_CHRATR_CJK_POSTURE );
/*N*/ 	aAttrTab[ RES_CHRATR_CJK_POSTURE - POOLATTR_BEGIN ] = pItem;
/*N*/ 
/*N*/ 	pItem = new SvxWeightItem;
/*N*/ 	pItem->SetWhich( RES_CHRATR_CJK_WEIGHT );
/*N*/ 	aAttrTab[ RES_CHRATR_CJK_WEIGHT - POOLATTR_BEGIN ] = pItem;
/*N*/ 
/*N*/ 	// CTL-Attributes
/*N*/ 	aAttrTab[ RES_CHRATR_CTL_FONT - POOLATTR_BEGIN ] =
/*N*/ 									new SvxFontItem( RES_CHRATR_CTL_FONT );
/*N*/ 
/*N*/ 	pItem = new SvxFontHeightItem;
/*N*/ 	pItem->SetWhich( RES_CHRATR_CTL_FONTSIZE );
/*N*/ 	aAttrTab[ RES_CHRATR_CTL_FONTSIZE - POOLATTR_BEGIN ] = pItem;
/*N*/ 
/*N*/ 	pItem = new SvxLanguageItem(LANGUAGE_DONTKNOW);
/*N*/ 	pItem->SetWhich( RES_CHRATR_CTL_LANGUAGE );
/*N*/ 	aAttrTab[ RES_CHRATR_CTL_LANGUAGE - POOLATTR_BEGIN ] = pItem;
/*N*/ 
/*N*/ 	pItem = new SvxPostureItem;
/*N*/ 	pItem->SetWhich( RES_CHRATR_CTL_POSTURE );
/*N*/ 	aAttrTab[ RES_CHRATR_CTL_POSTURE - POOLATTR_BEGIN ] = pItem;
/*N*/ 
/*N*/ 	pItem = new SvxWeightItem;
/*N*/ 	pItem->SetWhich( RES_CHRATR_CTL_WEIGHT );
/*N*/ 	aAttrTab[ RES_CHRATR_CTL_WEIGHT - POOLATTR_BEGIN ] = pItem;
/*N*/ 
/*N*/ 	aAttrTab[ RES_CHRATR_ROTATE - POOLATTR_BEGIN ] = new SvxCharRotateItem;
/*N*/ 	aAttrTab[ RES_CHRATR_EMPHASIS_MARK - POOLATTR_BEGIN ] =
/*N*/ 				new SvxEmphasisMarkItem;
/*N*/ 	aAttrTab[ RES_CHRATR_TWO_LINES - POOLATTR_BEGIN ] = new SvxTwoLinesItem( FALSE );
/*N*/ 	aAttrTab[ RES_CHRATR_SCALEW - POOLATTR_BEGIN ] = new SvxCharScaleWidthItem;
/*N*/ 	aAttrTab[ RES_CHRATR_RELIEF - POOLATTR_BEGIN ] = new SvxCharReliefItem;
/*N*/ 
/*N*/ // CharakterAttr - Dummies
/*N*/ 	aAttrTab[ RES_CHRATR_DUMMY1 - POOLATTR_BEGIN ] = new SfxBoolItem( RES_CHRATR_DUMMY1 );
/*N*/ // CharakterAttr - Dummies
/*N*/ 
/*N*/ // TextAttr Ende - Dummies
/*N*/ 	aAttrTab[ RES_TXTATR_DUMMY4 - POOLATTR_BEGIN ]
/*N*/ 				= new SfxBoolItem( RES_TXTATR_DUMMY4 );
/*N*/ // TextAttr Ende - Dummies
/*N*/ 
/*N*/ 	aAttrTab[ RES_TXTATR_INETFMT - POOLATTR_BEGIN ]
/*N*/ 				= new SwFmtINetFmt( aEmptyStr, aEmptyStr );
/*N*/ 	aAttrTab[ RES_TXTATR_REFMARK - POOLATTR_BEGIN ] = new SwFmtRefMark( aEmptyStr );
/*N*/ 	aAttrTab[ RES_TXTATR_TOXMARK - POOLATTR_BEGIN ] = new SwTOXMark;
/*N*/ 	aAttrTab[ RES_TXTATR_CHARFMT- POOLATTR_BEGIN ] = new SwFmtCharFmt( 0 );
/*N*/ 
/*N*/ 	aAttrTab[ RES_TXTATR_CJK_RUBY - POOLATTR_BEGIN ] = new SwFmtRuby( aEmptyStr );
/*N*/ 	aAttrTab[ RES_TXTATR_UNKNOWN_CONTAINER - POOLATTR_BEGIN ] =
/*N*/ 				new SvXMLAttrContainerItem( RES_TXTATR_UNKNOWN_CONTAINER );
/*N*/ 
/*N*/ 	aAttrTab[ RES_TXTATR_FIELD- POOLATTR_BEGIN ] = new SwFmtFld;
/*N*/ 	aAttrTab[ RES_TXTATR_FLYCNT - POOLATTR_BEGIN ] = new SwFmtFlyCnt( 0 );
/*N*/ 	aAttrTab[ RES_TXTATR_FTN - POOLATTR_BEGIN ] = new SwFmtFtn;
/*N*/ 	aAttrTab[ RES_TXTATR_SOFTHYPH- POOLATTR_BEGIN ] = new SwFmtSoftHyph;
/*N*/ 	aAttrTab[ RES_TXTATR_HARDBLANK- POOLATTR_BEGIN ] = new SwFmtHardBlank( ' ', FALSE );
/*N*/ 
/*N*/ // TextAttr ohne Ende - Dummies
/*N*/ 	aAttrTab[ RES_TXTATR_DUMMY1 - POOLATTR_BEGIN ] = new SfxBoolItem( RES_TXTATR_DUMMY1 );
/*N*/ 	aAttrTab[ RES_TXTATR_DUMMY2 - POOLATTR_BEGIN ] = new SfxBoolItem( RES_TXTATR_DUMMY2 );
/*N*/ 	aAttrTab[ RES_TXTATR_DUMMY5 - POOLATTR_BEGIN ] = new SfxBoolItem( RES_TXTATR_DUMMY5 );
/*N*/ 	aAttrTab[ RES_TXTATR_DUMMY6 - POOLATTR_BEGIN ] = new SfxBoolItem( RES_TXTATR_DUMMY6 );
/*N*/ 	aAttrTab[ RES_TXTATR_DUMMY7 - POOLATTR_BEGIN ] = new SfxBoolItem( RES_TXTATR_DUMMY7 );
/*N*/ // TextAttr ohne Ende - Dummies
/*N*/ 
/*N*/ 	aAttrTab[ RES_PARATR_LINESPACING- POOLATTR_BEGIN ] = new SvxLineSpacingItem;
/*N*/ 	aAttrTab[ RES_PARATR_ADJUST- POOLATTR_BEGIN ] = new SvxAdjustItem;
/*N*/ 	aAttrTab[ RES_PARATR_SPLIT- POOLATTR_BEGIN ] = new SvxFmtSplitItem;
/*N*/ 	aAttrTab[ RES_PARATR_WIDOWS- POOLATTR_BEGIN ] = new SvxWidowsItem;
/*N*/ 	aAttrTab[ RES_PARATR_ORPHANS- POOLATTR_BEGIN ] = new SvxOrphansItem;
/*N*/ 	aAttrTab[ RES_PARATR_TABSTOP- POOLATTR_BEGIN ] = new
/*N*/ 							SvxTabStopItem( 1, SVX_TAB_DEFDIST );
/*N*/ 
/*N*/ 	pItem = new SvxHyphenZoneItem;
/*N*/ 	((SvxHyphenZoneItem*)pItem)->GetMaxHyphens() = 0; // Default z.Z. auf 0
/*N*/ 	aAttrTab[ RES_PARATR_HYPHENZONE- POOLATTR_BEGIN ] = pItem;
/*N*/ 
/*N*/ 	aAttrTab[ RES_PARATR_DROP- POOLATTR_BEGIN ] = new SwFmtDrop;
/*N*/ 	aAttrTab[ RES_PARATR_REGISTER - POOLATTR_BEGIN ] = new SwRegisterItem( FALSE );
/*N*/ 	aAttrTab[ RES_PARATR_NUMRULE - POOLATTR_BEGIN ] = new SwNumRuleItem( aEmptyStr );
/*N*/ 
/*N*/ 	aAttrTab[ RES_PARATR_SCRIPTSPACE - POOLATTR_BEGIN ] =
/*N*/ 										new SvxScriptSpaceItem( TRUE );
/*N*/ 	aAttrTab[ RES_PARATR_HANGINGPUNCTUATION - POOLATTR_BEGIN ] =
/*N*/ 										new SvxHangingPunctuationItem( TRUE );
/*N*/ 	aAttrTab[ RES_PARATR_FORBIDDEN_RULES - POOLATTR_BEGIN ] =
/*N*/ 										new SvxForbiddenRuleItem( TRUE );
/*N*/ 	aAttrTab[ RES_PARATR_VERTALIGN - POOLATTR_BEGIN ] =
/*N*/ 							new SvxParaVertAlignItem( 0 );
/*N*/     aAttrTab[ RES_PARATR_SNAPTOGRID - POOLATTR_BEGIN ] = new SvxParaGridItem;
/*N*/     aAttrTab[ RES_PARATR_CONNECT_BORDER - POOLATTR_BEGIN ] = new SwParaConnectBorderItem;
/*N*/ // ParaAttr - Dummies
/*N*/ 	aAttrTab[ RES_PARATR_DUMMY5 - POOLATTR_BEGIN ] = new SfxBoolItem( RES_PARATR_DUMMY5 );
/*N*/ 	aAttrTab[ RES_PARATR_DUMMY6 - POOLATTR_BEGIN ] = new SfxBoolItem( RES_PARATR_DUMMY6 );
/*N*/ 	aAttrTab[ RES_PARATR_DUMMY7 - POOLATTR_BEGIN ] = new SfxBoolItem( RES_PARATR_DUMMY7 );
/*N*/ 	aAttrTab[ RES_PARATR_DUMMY8 - POOLATTR_BEGIN ] = new SfxBoolItem( RES_PARATR_DUMMY8 );
/*N*/ // ParatAttr - Dummies
/*N*/ 
/*N*/ 	aAttrTab[ RES_FILL_ORDER- POOLATTR_BEGIN ] = new SwFmtFillOrder;
/*N*/ 	aAttrTab[ RES_FRM_SIZE- POOLATTR_BEGIN ] = new SwFmtFrmSize;
/*N*/ 	aAttrTab[ RES_PAPER_BIN- POOLATTR_BEGIN ] = new SvxPaperBinItem;
/*N*/ 	aAttrTab[ RES_LR_SPACE- POOLATTR_BEGIN ] = new SvxLRSpaceItem;
/*N*/ 	aAttrTab[ RES_UL_SPACE- POOLATTR_BEGIN ] = new SvxULSpaceItem;
/*N*/ 	aAttrTab[ RES_PAGEDESC- POOLATTR_BEGIN ] = new SwFmtPageDesc;
/*N*/ 	aAttrTab[ RES_BREAK- POOLATTR_BEGIN ] = new SvxFmtBreakItem;
/*N*/ 	aAttrTab[ RES_CNTNT- POOLATTR_BEGIN ] = new SwFmtCntnt;
/*N*/ 	aAttrTab[ RES_HEADER- POOLATTR_BEGIN ] = new SwFmtHeader;
/*N*/ 	aAttrTab[ RES_FOOTER- POOLATTR_BEGIN ] = new SwFmtFooter;
/*N*/ 	aAttrTab[ RES_PRINT- POOLATTR_BEGIN ] = new SvxPrintItem;
/*N*/ 	aAttrTab[ RES_OPAQUE- POOLATTR_BEGIN ] = new SvxOpaqueItem;
/*N*/ 	aAttrTab[ RES_PROTECT- POOLATTR_BEGIN ] = new SvxProtectItem;
/*N*/ 	aAttrTab[ RES_SURROUND- POOLATTR_BEGIN ] = new SwFmtSurround;
/*N*/ 	aAttrTab[ RES_VERT_ORIENT- POOLATTR_BEGIN ] = new SwFmtVertOrient;
/*N*/ 	aAttrTab[ RES_HORI_ORIENT- POOLATTR_BEGIN ] = new SwFmtHoriOrient;
/*N*/ 	aAttrTab[ RES_ANCHOR- POOLATTR_BEGIN ] = new SwFmtAnchor;
/*N*/ 	aAttrTab[ RES_BACKGROUND- POOLATTR_BEGIN ] = new SvxBrushItem;
/*N*/ 	aAttrTab[ RES_BOX- POOLATTR_BEGIN ] = new SvxBoxItem;
/*N*/ 	aAttrTab[ RES_SHADOW- POOLATTR_BEGIN ] = new SvxShadowItem;
/*N*/ 	aAttrTab[ RES_FRMMACRO- POOLATTR_BEGIN ] = new SvxMacroItem;
/*N*/ 	aAttrTab[ RES_COL- POOLATTR_BEGIN ] = new SwFmtCol;
/*N*/ 	aAttrTab[ RES_KEEP - POOLATTR_BEGIN ] = new SvxFmtKeepItem( FALSE );
/*N*/ 	aAttrTab[ RES_URL - POOLATTR_BEGIN ] = new SwFmtURL();
/*N*/ 	aAttrTab[ RES_EDIT_IN_READONLY - POOLATTR_BEGIN ] = new SwFmtEditInReadonly;
/*N*/ 	aAttrTab[ RES_LAYOUT_SPLIT - POOLATTR_BEGIN ] = new SwFmtLayoutSplit;
/*N*/ 	aAttrTab[ RES_CHAIN - POOLATTR_BEGIN ] = new SwFmtChain;
/*N*/   aAttrTab[ RES_TEXTGRID - POOLATTR_BEGIN ] = new SwTextGridItem;
/*M*/   aAttrTab[ RES_HEADER_FOOTER_EAT_SPACING - POOLATTR_BEGIN ] = new SwHeaderAndFooterEatSpacingItem;
/*N*/ 	aAttrTab[ RES_LINENUMBER - POOLATTR_BEGIN ] = new SwFmtLineNumber;
/*N*/ 	aAttrTab[ RES_FTN_AT_TXTEND - POOLATTR_BEGIN ] = new SwFmtFtnAtTxtEnd;
/*N*/ 	aAttrTab[ RES_END_AT_TXTEND - POOLATTR_BEGIN ] = new SwFmtEndAtTxtEnd;
/*N*/ 	aAttrTab[ RES_COLUMNBALANCE - POOLATTR_BEGIN ] = new SwFmtNoBalancedColumns;
/*N*/     aAttrTab[ RES_FRAMEDIR - POOLATTR_BEGIN ] = new SvxFrameDirectionItem(FRMDIR_ENVIRONMENT);
/*N*/ 
/*N*/ // FrameAttr - Dummies
/*N*/ 	aAttrTab[ RES_FRMATR_DUMMY9 - POOLATTR_BEGIN ] = new SfxBoolItem( RES_FRMATR_DUMMY9 );
/*N*/ // FrameAttr - Dummies
/*N*/ 
/*N*/ 	aAttrTab[ RES_GRFATR_MIRRORGRF- POOLATTR_BEGIN ] = new SwMirrorGrf;
/*N*/ 	aAttrTab[ RES_GRFATR_CROPGRF- POOLATTR_BEGIN ] = new SwCropGrf;
/*N*/ 
/*N*/ 	aAttrTab[ RES_GRFATR_ROTATION - POOLATTR_BEGIN ] = new SwRotationGrf;
/*N*/ 	aAttrTab[ RES_GRFATR_LUMINANCE - POOLATTR_BEGIN ] = new SwLuminanceGrf;
/*N*/ 	aAttrTab[ RES_GRFATR_CONTRAST - POOLATTR_BEGIN ] = new SwContrastGrf;
/*N*/ 	aAttrTab[ RES_GRFATR_CHANNELR - POOLATTR_BEGIN ] = new SwChannelRGrf;
/*N*/ 	aAttrTab[ RES_GRFATR_CHANNELG - POOLATTR_BEGIN ] = new SwChannelGGrf;
/*N*/ 	aAttrTab[ RES_GRFATR_CHANNELB - POOLATTR_BEGIN ] = new SwChannelBGrf;
/*N*/ 	aAttrTab[ RES_GRFATR_GAMMA - POOLATTR_BEGIN ] = new SwGammaGrf;
/*N*/ 	aAttrTab[ RES_GRFATR_INVERT - POOLATTR_BEGIN ] = new SwInvertGrf;
/*N*/ 	aAttrTab[ RES_GRFATR_TRANSPARENCY - POOLATTR_BEGIN ] = new SwTransparencyGrf;
/*N*/ 	aAttrTab[ RES_GRFATR_DRAWMODE - POOLATTR_BEGIN ] = new SwDrawModeGrf;
/*N*/ 
/*N*/ // GraphicAttr - Dummies
/*N*/ 	aAttrTab[ RES_GRFATR_DUMMY1 - POOLATTR_BEGIN ] = new SfxBoolItem( RES_GRFATR_DUMMY1 );
/*N*/ 	aAttrTab[ RES_GRFATR_DUMMY2 - POOLATTR_BEGIN ] = new SfxBoolItem( RES_GRFATR_DUMMY2 );
/*N*/ 	aAttrTab[ RES_GRFATR_DUMMY3 - POOLATTR_BEGIN ] = new SfxBoolItem( RES_GRFATR_DUMMY3 );
/*N*/ 	aAttrTab[ RES_GRFATR_DUMMY4 - POOLATTR_BEGIN ] = new SfxBoolItem( RES_GRFATR_DUMMY4 );
/*N*/ 	aAttrTab[ RES_GRFATR_DUMMY5 - POOLATTR_BEGIN ] = new SfxBoolItem( RES_GRFATR_DUMMY5 );
/*N*/ // GraphicAttr - Dummies
/*N*/ 
/*N*/ 	aAttrTab[ RES_BOXATR_FORMAT- POOLATTR_BEGIN ] = new SwTblBoxNumFormat;
/*N*/ 	aAttrTab[ RES_BOXATR_FORMULA- POOLATTR_BEGIN ] = new SwTblBoxFormula( aEmptyStr );
/*N*/ 	aAttrTab[ RES_BOXATR_VALUE- POOLATTR_BEGIN ] = new SwTblBoxValue;
/*N*/ 
/*N*/ 	aAttrTab[ RES_UNKNOWNATR_CONTAINER- POOLATTR_BEGIN ] =
/*N*/ 				new SvXMLAttrContainerItem( RES_UNKNOWNATR_CONTAINER );
/*N*/ 
/*N*/ 	// get the correct fonts:
/*N*/ 	::binfilter::GetDefaultFonts( *(SvxFontItem*)aAttrTab[ RES_CHRATR_FONT- POOLATTR_BEGIN ],
/*N*/ 					   *(SvxFontItem*)aAttrTab[ RES_CHRATR_CJK_FONT - POOLATTR_BEGIN ],
/*N*/ 					   *(SvxFontItem*)aAttrTab[ RES_CHRATR_CTL_FONT - POOLATTR_BEGIN ] );
/*N*/ 
/*N*/ 	// 1. Version - neue Attribute:
/*N*/ 	//		- RES_CHRATR_BLINK
/*N*/ 	//		- RES_CHRATR_NOHYPHEN
/*N*/ 	//		- RES_CHRATR_NOLINEBREAK
/*N*/ 	// 		- RES_PARATR_REGISTER
/*N*/ 	// 		+ 2 Dummies fuer die einzelnen "Bereiche"
/*N*/ 	SwAttrPool::pVersionMap1 = new USHORT[ 60 ];
        USHORT i;
/*N*/ 	for( i = 1; i <= 17; i++ )
/*N*/ 		SwAttrPool::pVersionMap1[ i-1 ] = i;
/*N*/ 	for ( i = 18; i <= 27; ++i )
/*N*/ 		SwAttrPool::pVersionMap1[ i-1 ] = i + 5;
/*N*/ 	for ( i = 28; i <= 35; ++i )
/*N*/ 		SwAttrPool::pVersionMap1[ i-1 ] = i + 7;
/*N*/ 	for ( i = 36; i <= 58; ++i )
/*N*/ 		SwAttrPool::pVersionMap1[ i-1 ] = i + 10;
/*N*/ 	for ( i = 59; i <= 60; ++i )
/*N*/ 		SwAttrPool::pVersionMap1[ i-1 ] = i + 12;
/*N*/ 
/*N*/ 	// 2. Version - neue Attribute:
/*N*/ 	// 		10 Dummies fuer den Frame "Bereich"
/*N*/ 	SwAttrPool::pVersionMap2 = new USHORT[ 75 ];
/*N*/ 	for( i = 1; i <= 70; i++ )
/*N*/ 		SwAttrPool::pVersionMap2[ i-1 ] = i;
/*N*/ 	for ( i = 71; i <= 75; ++i )
/*N*/ 		SwAttrPool::pVersionMap2[ i-1 ] = i + 10;
/*N*/ 
/*N*/ 	// 3. Version - neue Attribute:
/*N*/ 	// 		neue Attribute und Dummies fuer die CJK-Version
/*N*/ 	// 		und neue Grafik-Attribute
/*N*/ 	SwAttrPool::pVersionMap3 = new USHORT[ 86 ];
/*N*/ 	for( i = 1; i <= 21; i++ )
/*N*/ 		SwAttrPool::pVersionMap3[ i-1 ] = i;
/*N*/ 	for ( i = 22; i <= 27; ++i )
/*N*/ 		SwAttrPool::pVersionMap3[ i-1 ] = i + 15;
/*N*/ 	for ( i = 28; i <= 82; ++i )
/*N*/ 		SwAttrPool::pVersionMap3[ i-1 ] = i + 20;
/*N*/ 	for ( i = 83; i <= 86; ++i )
/*N*/ 		SwAttrPool::pVersionMap3[ i-1 ] = i + 35;
/*N*/ 
/*N*/ 	// 4. Version - neue Paragraph Attribute fuer die CJK-Version
/*N*/ 	SwAttrPool::pVersionMap4 = new USHORT[ 121 ];
/*N*/ 	for( i = 1; i <= 65; i++ )
/*N*/ 		SwAttrPool::pVersionMap4[ i-1 ] = i;
/*N*/ 	for ( i = 66; i <= 121; ++i )
/*N*/ 		SwAttrPool::pVersionMap4[ i-1 ] = i + 9;
/*N*/ 
/*N*/ 	pBreakIt = new SwBreakIt;
/*N*/ 	const ::com::sun::star::lang::Locale& rLcl = pBreakIt->GetLocale(
/*N*/ 											(LanguageType)GetAppLanguage() );
/*M*/   pCheckIt = NULL;
/*N*/ 	::com::sun::star::uno::Reference<
/*N*/ 			::com::sun::star::lang::XMultiServiceFactory > xMSF =
/*N*/ 									::legacy_binfilters::getLegacyProcessServiceFactory();
/*N*/ 	pAppCharClass = new CharClass( xMSF, rLcl );
/*N*/ 	pCalendarWrapper = new SwCalendarWrapper( xMSF );
/*N*/ 
/*N*/ 	_FrmInit();
/*N*/ 	_TextInit();
/*N*/ 
/*N*/ 	SwSelPaintRects::pMapMode = new MapMode;
/*N*/ 	SwFntObj::pPixMap = new MapMode;
/*N*/ 
/*N*/ 	SwIndexReg::pEmptyIndexArray = new SwIndexReg;
/*N*/ 
/*N*/ 	pGlobalOLEExcludeList = new SvPtrarr;
/*N*/ 
/*N*/ 	const SvxSwAutoFmtFlags& rAFlags = OFF_APP()->GetAutoCorrect()->GetSwFlags();
/*N*/ 	SwDoc::pACmpltWords = new SwAutoCompleteWord( rAFlags.nAutoCmpltListLen,
/*N*/ 											rAFlags.nAutoCmpltWordLen );
/*N*/ }

/******************************************************************************
 *	void _FinitCore()
 ******************************************************************************/



/*N*/ void _FinitCore()
/*N*/ {
/*N*/ 	_FrmFinit();
/*N*/ 	_TextFinit();
/*N*/ 
/*N*/ 	delete pBreakIt;
/*M*/   delete pCheckIt;
/*N*/ 	delete pAppCharClass;
/*N*/ 	delete pCalendarWrapper;
/*N*/ 	delete pCollator;
/*N*/ 	delete pCaseCollator;
/*N*/ 
/*N*/ 	// das default TableAutoFormat zerstoeren
/*N*/ 	delete SwTableAutoFmt::pDfltBoxAutoFmt;
/*N*/ 
/*N*/ 	delete SwSelPaintRects::pMapMode;
/*N*/ 	delete SwFntObj::pPixMap;
/*N*/ 
/*N*/ 	delete SwEditShell::pAutoFmtFlags;
/*N*/ 	delete SwNumRule::pDefBulletFont;
/*N*/ 
/*N*/ #ifndef PRODUCT
/*N*/ 	//Defaultattribut freigeben lassen um asserts zu vermeiden.
/*N*/ 	if ( aAttrTab[0]->GetRefCount() )
/*N*/ 		SfxItemPool::ReleaseDefaults( aAttrTab, POOLATTR_END-POOLATTR_BEGIN, FALSE);
/*N*/ #endif
/*N*/ 	delete SwDoc::pACmpltWords;
/*N*/ 
/*N*/ 	delete SwStyleNameMapper::pTextUINameArray;
/*N*/ 	delete SwStyleNameMapper::pListsUINameArray;
/*N*/ 	delete SwStyleNameMapper::pExtraUINameArray;
/*N*/ 	delete SwStyleNameMapper::pRegisterUINameArray;
/*N*/ 	delete SwStyleNameMapper::pDocUINameArray;
/*N*/ 	delete SwStyleNameMapper::pHTMLUINameArray;
/*N*/ 	delete SwStyleNameMapper::pFrmFmtUINameArray;
/*N*/ 	delete SwStyleNameMapper::pChrFmtUINameArray;
/*N*/ 	delete SwStyleNameMapper::pHTMLChrFmtUINameArray;
/*N*/ 	delete SwStyleNameMapper::pPageDescUINameArray;
/*N*/ 	delete SwStyleNameMapper::pNumRuleUINameArray;
/*N*/ 
/*N*/ 	// Delete programmatic name arrays also
/*N*/ 	delete SwStyleNameMapper::pTextProgNameArray;
/*N*/ 	delete SwStyleNameMapper::pListsProgNameArray;
/*N*/ 	delete SwStyleNameMapper::pExtraProgNameArray;
/*N*/ 	delete SwStyleNameMapper::pRegisterProgNameArray;
/*N*/ 	delete SwStyleNameMapper::pDocProgNameArray;
/*N*/ 	delete SwStyleNameMapper::pHTMLProgNameArray;
/*N*/ 	delete SwStyleNameMapper::pFrmFmtProgNameArray;
/*N*/ 	delete SwStyleNameMapper::pChrFmtProgNameArray;
/*N*/ 	delete SwStyleNameMapper::pHTMLChrFmtProgNameArray;
/*N*/ 	delete SwStyleNameMapper::pPageDescProgNameArray;
/*N*/ 	delete SwStyleNameMapper::pNumRuleProgNameArray;
/*N*/ 
/*N*/ 	// And finally, any hash tables that we used
/*N*/ 	delete SwStyleNameMapper::pParaUIMap;
/*N*/ 	delete SwStyleNameMapper::pCharUIMap;
/*N*/ 	delete SwStyleNameMapper::pPageUIMap;
/*N*/ 	delete SwStyleNameMapper::pFrameUIMap;
/*N*/ 	delete SwStyleNameMapper::pNumRuleUIMap;
/*N*/ 
/*N*/ 	delete SwStyleNameMapper::pParaProgMap;
/*N*/ 	delete SwStyleNameMapper::pCharProgMap;
/*N*/ 	delete SwStyleNameMapper::pPageProgMap;
/*N*/ 	delete SwStyleNameMapper::pFrameProgMap;
/*N*/ 	delete SwStyleNameMapper::pNumRuleProgMap;
/*N*/ 
/*N*/ 
/*N*/ 	// loesche alle default-Attribute
/*N*/ 	SfxPoolItem* pHt;
/*N*/ 	for( USHORT n = 0; n < POOLATTR_END - POOLATTR_BEGIN; n++ )
/*N*/ 		if( 0 != ( pHt = aAttrTab[n] ))
/*N*/ 			delete pHt;
/*N*/ 
/*N*/ 	::binfilter::ClearFEShellTabCols();
/*N*/ 
/*N*/ 	delete SwIndexReg::pEmptyIndexArray;
/*N*/     delete[] SwAttrPool::pVersionMap1;
/*N*/     delete[] SwAttrPool::pVersionMap2;
/*N*/     delete[] SwAttrPool::pVersionMap3;
/*N*/     delete[] SwAttrPool::pVersionMap4;
/*N*/ 
/*N*/ 	for ( USHORT i = 0; i < pGlobalOLEExcludeList->Count(); ++i )
/*N*/ 		delete (SvGlobalName*)(*pGlobalOLEExcludeList)[i];
/*N*/ 	delete pGlobalOLEExcludeList;
/*N*/ }

// returns the APP - CharClass instance - used for all ToUpper/ToLower/...
/*N*/ CharClass& GetAppCharClass()
/*N*/ {
/*N*/ 	return *pAppCharClass;
/*N*/ }

/*N*/ LocaleDataWrapper& GetAppLocaleData()
/*N*/ {
/*N*/ 	SvtSysLocale aSysLocale;
/*N*/ 	return (LocaleDataWrapper&)aSysLocale.GetLocaleData();
/*N*/ }




/*N*/ ULONG GetAppLanguage()
/*N*/ {
/*N*/ 	return Application::GetSettings().GetLanguage();
/*N*/ }

/*N*/ CollatorWrapper& GetAppCollator()
/*N*/ {
/*?*/ 	if( !pCollator )
/*?*/ 	{
/*?*/ 		const ::com::sun::star::lang::Locale& rLcl = pBreakIt->GetLocale(
/*?*/ 											(LanguageType)GetAppLanguage() );
/*?*/ 		::com::sun::star::uno::Reference<
/*?*/ 			::com::sun::star::lang::XMultiServiceFactory > xMSF =
/*?*/ 									::legacy_binfilters::getLegacyProcessServiceFactory();
/*?*/ 
/*?*/ 		pCollator = new ::CollatorWrapper( xMSF );
/*?*/ 		pCollator->loadDefaultCollator( rLcl, SW_COLLATOR_IGNORES );
/*?*/ 	}
/*?*/ 	return *pCollator;
/*N*/ }

/*N*/ const ::utl::TransliterationWrapper& GetAppCmpStrIgnore()
/*N*/ {
/*N*/ 	if( !pTransWrp )
/*N*/ 	{
/*N*/ 		::com::sun::star::uno::Reference<
/*N*/ 			::com::sun::star::lang::XMultiServiceFactory > xMSF =
/*N*/ 									::legacy_binfilters::getLegacyProcessServiceFactory();
/*N*/ 
/*N*/ 		pTransWrp = new ::utl::TransliterationWrapper( xMSF,
/*N*/ 				::com::sun::star::i18n::TransliterationModules_IGNORE_CASE |
/*N*/ 				::com::sun::star::i18n::TransliterationModules_IGNORE_KANA |
/*N*/ 				::com::sun::star::i18n::TransliterationModules_IGNORE_WIDTH );
/*N*/ 		pTransWrp->loadModuleIfNeeded( GetAppLanguage() );
/*N*/ 	}
/*N*/ 	return *pTransWrp;
/*N*/ }

}
