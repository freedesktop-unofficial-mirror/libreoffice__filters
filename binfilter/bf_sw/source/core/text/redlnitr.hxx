/*************************************************************************
 *
 *  $RCSfile: redlnitr.hxx,v $
 *
 *  $Revision: 1.1 $
 *
 *  last change: $Author: aw $ $Date: 2003-10-02 15:34:34 $
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

#ifndef	_REDLNITR_HXX
#define	_REDLNITR_HXX

#include "ndhints.hxx"
#include "redlenum.hxx"	// SwRedlineType
#include "swfont.hxx"
#ifndef _SVSTDARR_USHORTS
#define _SVSTDARR_USHORTS
#include <svtools/svstdarr.hxx>
#endif

class SwTxtNode;
class SwDoc;
class SfxItemSet;
class SwAttrHandler;

class SwExtend
{
    SwFont *pFnt;
    const SvUShorts &rArr;	// XAMA: Array of xub_StrLen
    xub_StrLen nStart;
    xub_StrLen nPos;
    xub_StrLen nEnd;
    sal_Bool _Leave( SwFont& rFnt, xub_StrLen nNew );
    sal_Bool Inside() const { return ( nPos >= nStart && nPos < nEnd ); }
    void ActualizeFont( SwFont &rFnt, xub_StrLen nAttr );
public:
    SwExtend( const SvUShorts &rA, xub_StrLen nSt ) : rArr( rA ), pFnt(0),
        nStart( nSt ), nPos( STRING_LEN ), nEnd( nStart + rA.Count() ) {}
    ~SwExtend() { delete pFnt; }
    sal_Bool IsOn() const { return pFnt != 0; }
    void Reset() { if( pFnt ) { delete pFnt; pFnt = NULL; } nPos = STRING_LEN; }
    sal_Bool Leave( SwFont& rFnt, xub_StrLen nNew )
        { if( pFnt ) return _Leave( rFnt, nNew ); return sal_False; }
    short Enter( SwFont& rFnt, xub_StrLen nNew );
    xub_StrLen Next( xub_StrLen nNext );
    SwFont* GetFont()  { return pFnt; }
    void UpdateFont( SwFont &rFnt ) { ActualizeFont( rFnt, rArr[ nPos - nStart ] ); }
};

class SwRedlineItr
{
//STRIP001 	SwpHtStart_SAR aHints;
//STRIP001 	const SwDoc& rDoc;
//STRIP001 	const SwTxtNode& rNd;
//STRIP001     SwAttrHandler& rAttrHandler;
//STRIP001     SfxItemSet *pSet;
    SwExtend *pExt;
//STRIP001     ULONG nNdIdx;
//STRIP001 	xub_StrLen nFirst;
//STRIP001 	xub_StrLen nAct;
//STRIP001 	xub_StrLen nStart;
//STRIP001 	xub_StrLen nEnd;
    sal_Bool bOn;
//STRIP001 	sal_Bool bShow;
//STRIP001 
//STRIP001 	void _Clear( SwFont* pFnt );
//STRIP001 	sal_Bool _ChkSpecialUnderline() const;
//STRIP001 	void FillHints( MSHORT nAuthor, SwRedlineType eType );
//STRIP001 	short _Seek( SwFont& rFnt, xub_StrLen nNew, xub_StrLen nOld );
//STRIP001 	xub_StrLen _GetNextRedln( xub_StrLen nNext );
//STRIP001 	inline short EnterExtend( SwFont& rFnt, xub_StrLen nNew )
//STRIP001 		{ if( pExt ) return pExt->Enter( rFnt, nNew ); return 0; }
//STRIP001 	inline xub_StrLen NextExtend( xub_StrLen nNext )
//STRIP001 		{ if( pExt ) return pExt->Next( nNext ); return nNext; }
public:
SwRedlineItr( const SwTxtNode& rTxtNd, SwFont& rFnt, SwAttrHandler& rAH,//STRIP001 SwRedlineItr( const SwTxtNode& rTxtNd, SwFont& rFnt, SwAttrHandler& rAH,
xub_StrLen nRedlPos, sal_Bool bShw, const SvUShorts *pArr = 0,//STRIP001         xub_StrLen nRedlPos, sal_Bool bShw, const SvUShorts *pArr = 0,
xub_StrLen nStart = STRING_LEN ){DBG_ASSERT(0, "STRIP");} ;//STRIP001        xub_StrLen nStart = STRING_LEN );
//STRIP001 	~SwRedlineItr();
    inline sal_Bool IsOn() const { return bOn || ( pExt && pExt->IsOn() ); }
//STRIP001 	inline void Clear( SwFont* pFnt ) { if( bOn ) _Clear( pFnt ); }
//STRIP001     void ChangeTxtAttr( SwFont* pFnt, SwTxtAttr &rHt, sal_Bool bChg );
//STRIP001     inline short Seek( SwFont& rFnt, xub_StrLen nNew, xub_StrLen nOld )
//STRIP001 		{ if( bShow || pExt ) return _Seek( rFnt, nNew, nOld ); return 0; }
//STRIP001 	inline void Reset() { if( nAct != nFirst ) nAct = STRING_LEN;
//STRIP001 						  if( pExt ) pExt->Reset(); }
//STRIP001 	inline xub_StrLen GetNextRedln( xub_StrLen nNext )
//STRIP001 		{ if( bShow || pExt ) return _GetNextRedln( nNext ); return nNext; }
//STRIP001 	inline sal_Bool ChkSpecialUnderline() const
//STRIP001 		{ if ( IsOn() ) return _ChkSpecialUnderline(); return sal_False; }
            sal_Bool CheckLine( xub_StrLen nChkStart, xub_StrLen nChkEnd ){DBG_ASSERT(0, "STRIP"); return FALSE;} //STRIP001 	sal_Bool CheckLine( xub_StrLen nChkStart, xub_StrLen nChkEnd );
//STRIP001     inline sal_Bool LeaveExtend( SwFont& rFnt, xub_StrLen nNew )
//STRIP001 		{ return pExt->Leave(rFnt, nNew ); }
    inline sal_Bool ExtOn() { if( pExt ) return pExt->IsOn(); return sal_False; }
//STRIP001     inline void UpdateExtFont( SwFont &rFnt ) {
//STRIP001         ASSERT( ExtOn(), "UpdateExtFont without ExtOn" )
//STRIP001         pExt->UpdateFont( rFnt ); }
};


#endif

