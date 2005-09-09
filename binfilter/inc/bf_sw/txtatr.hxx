/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: txtatr.hxx,v $
 *
 *  $Revision: 1.5 $
 *
 *  last change: $Author: rt $ $Date: 2005-09-09 16:39:50 $
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
#ifndef _TXTATR_HXX
#define _TXTATR_HXX

// auto strip #ifndef _SV_GEN_HXX
// auto strip #include <tools/gen.hxx>
// auto strip #endif
// auto strip #ifndef _TOOLS_COLOR_HXX
// auto strip #include <tools/color.hxx>
// auto strip #endif
#ifndef _TXATBASE_HXX
#include <txatbase.hxx>     // SwTxtAttr/SwTxtAttrEnd
#endif
#ifndef _CALBCK_HXX
#include <calbck.hxx>
#endif
namespace binfilter {

class SwTxtNode;	// fuer SwTxtFld
class SvxFont;
class SwCharSetCol;
class SwCharFmt;
class SvxTwoLinesItem;

// ATT_CHARFMT *********************************************

class SwTxtCharFmt : public SwTxtAttrEnd
{
    SwTxtNode* pMyTxtNd;
    BOOL bPrevNoHyph	: 1;
    BOOL bPrevBlink		: 1;
    BOOL bPrevURL		: 1;
    BOOL bColor         : 1;

public:
    SwTxtCharFmt( const SwFmtCharFmt& rAttr, xub_StrLen nStart, xub_StrLen nEnd );
    ~SwTxtCharFmt( );

    // werden vom SwFmtCharFmt hierher weitergeleitet
    virtual void Modify( SfxPoolItem*, SfxPoolItem* );    // SwClient
    virtual BOOL GetInfo( SfxPoolItem& rInfo ) const;

    // erfrage und setze den TxtNode Pointer
    inline const SwTxtNode& GetTxtNode() const;
    void ChgTxtNode( const SwTxtNode* pNew ) { pMyTxtNd = (SwTxtNode*)pNew; }

};

// ATT_HARDBLANK ******************************

//STRIP001 class SwTxtHardBlank : public SwTxtAttr
//STRIP001 {
//STRIP001 	sal_Unicode cChar;
//STRIP001 public:
//STRIP001 	SwTxtHardBlank( const SwFmtHardBlank& rAttr, xub_StrLen nStart );
//STRIP001 	inline sal_Unicode GetChar() const 	{ return cChar; }
//STRIP001 };

// ATT_XNLCONTAINERITEM ******************************

//STRIP001 class SwTxtXMLAttrContainer : public SwTxtAttrEnd
//STRIP001 {
//STRIP001 public:
//STRIP001 	SwTxtXMLAttrContainer( const SvXMLAttrContainerItem& rAttr,
//STRIP001 						xub_StrLen nStart, xub_StrLen nEnd );
//STRIP001 };

// ******************************

class SwTxtRuby : public SwTxtAttrEnd, public SwClient
{
//STRIP001 	SwTxtNode* pMyTxtNd;

public:
    SwTxtRuby( const SwFmtRuby& rAttr, xub_StrLen nStart, xub_StrLen nEnd ): SwTxtAttrEnd( (SfxPoolItem &)rAttr, nStart, nEnd ){DBG_BF_ASSERT(0, "STRIP");} ;//STRIP001 	SwTxtRuby( const SwFmtRuby& rAttr, xub_StrLen nStart, xub_StrLen nEnd );
//STRIP001 	virtual ~SwTxtRuby();
//STRIP001 	TYPEINFO();

//STRIP001 	virtual void Modify( SfxPoolItem *pOld, SfxPoolItem *pNew);
//STRIP001 	virtual BOOL GetInfo( SfxPoolItem& rInfo ) const;
//STRIP001 
//STRIP001 	// erfrage und setze den TxtNode Pointer
//STRIP001 	const SwTxtNode* GetpTxtNode() const 			{ return pMyTxtNd; }
//STRIP001 	inline const SwTxtNode& GetTxtNode() const;
//STRIP001 	void ChgTxtNode( const SwTxtNode* pNew ) { pMyTxtNd = (SwTxtNode*)pNew; }
//STRIP001 
//STRIP001 		  SwCharFmt* GetCharFmt();
//STRIP001 	const SwCharFmt* GetCharFmt() const
//STRIP001 			{ return ((SwTxtRuby*)this)->GetCharFmt(); }
};

// ******************************

//STRIP001 class SwTxt2Lines : public SwTxtAttrEnd
//STRIP001 {
//STRIP001 public:
//STRIP001 	SwTxt2Lines( const SvxTwoLinesItem& rAttr,
//STRIP001 					xub_StrLen nStart, xub_StrLen nEnd );
//STRIP001 };

// --------------- Inline Implementierungen ------------------------

inline const SwTxtNode& SwTxtCharFmt::GetTxtNode() const
{
    ASSERT( pMyTxtNd, "SwTxtCharFmt:: wo ist mein TextNode?" );
    return *pMyTxtNd;
}

//STRIP001 inline const SwTxtNode& SwTxtRuby::GetTxtNode() const
//STRIP001 {
//STRIP001 	ASSERT( pMyTxtNd, "SwTxtRuby:: wo ist mein TextNode?" );
//STRIP001 	return *pMyTxtNd;
//STRIP001 }

} //namespace binfilter
#endif
