/*************************************************************************
 *
 *  $RCSfile: fmtruby.hxx,v $
 *
 *  $Revision: 1.1.1.1 $
 *
 *  last change: $Author: hjs $ $Date: 2003-10-01 12:23:52 $
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
#ifndef _FMTRUBY_HXX
#define _FMTRUBY_HXX


#ifndef _STRING_HXX //autogen
#include <tools/string.hxx>
#endif
#ifndef _SFXPOOLITEM_HXX
#include <svtools/poolitem.hxx>
#endif


class SwFmtRuby : public SfxPoolItem
{
    friend class SwTxtRuby;

    String sRubyTxt;					// the ruby txt
    String sCharFmtName;				// name of the charformat
    SwTxtRuby* pTxtAttr;				// the TextAttribut
    USHORT nCharFmtId;					// PoolId of the charformat
    USHORT nPosition;					// Position of the Ruby-Character
    USHORT nAdjustment;					// specific adjustment of the Ruby-Ch.

public:
    SwFmtRuby( const String& rRubyTxt );
    SwFmtRuby( const SwFmtRuby& rAttr );
    virtual ~SwFmtRuby();

    SwFmtRuby& operator=( const SwFmtRuby& rAttr );

    // "pure virtual Methoden" vom SfxPoolItem
    virtual int  operator==( const SfxPoolItem& ) const{DBG_ASSERT(0, "STRIP"); return 0;}; //STRIP001 	virtual int             operator==( const SfxPoolItem& ) const;
    virtual SfxPoolItem*	Clone( SfxItemPool* pPool = 0 ) const{DBG_ASSERT(0, "STRIP");return NULL;}; //STRIP001 	virtual SfxPoolItem*	Clone( SfxItemPool* pPool = 0 ) const;
//STRIP001 	virtual SfxPoolItem*	Create(SvStream &, USHORT nVer) const;
//STRIP001 	virtual SvStream&		Store(SvStream &, USHORT nIVer) const;

//STRIP001 	virtual SfxItemPresentation GetPresentation( SfxItemPresentation ePres,
//STRIP001 									SfxMapUnit eCoreMetric,
//STRIP001 									SfxMapUnit ePresMetric,
//STRIP001 									String &rText,
//STRIP001                                     const IntlWrapper* pIntl = 0 ) const;

//STRIP001 	virtual	BOOL        	QueryValue( com::sun::star::uno::Any& rVal,
//STRIP001 										BYTE nMemberId = 0 ) const;
    virtual	BOOL			PutValue( const com::sun::star::uno::Any& rVal,
                                        BYTE nMemberId = 0 );

    virtual USHORT			GetVersion( USHORT nFFVer ) const;

    const SwTxtRuby* GetTxtRuby() const			{ return pTxtAttr; }
    SwTxtRuby* GetTxtRuby()						{ return pTxtAttr; }

    const String& GetText() const				{ return sRubyTxt; }
    void SetText( const String& rTxt )			{ sRubyTxt = rTxt; }

    const String& GetCharFmtName() const		{ return sCharFmtName; }
    void SetCharFmtName( const String& rNm )	{ sCharFmtName = rNm; }

    USHORT GetCharFmtId() const					{ return nCharFmtId; }
    void SetCharFmtId( USHORT nNew )			{ nCharFmtId = nNew; }

    USHORT GetPosition() const					{ return nPosition; }
    void SetPosition( USHORT nNew )				{ nPosition = nNew; }

    USHORT GetAdjustment() const				{ return nAdjustment; }
    void SetAdjustment( USHORT nNew )			{ nAdjustment = nNew; }
};


#endif

