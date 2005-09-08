/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: wrong.hxx,v $
 *
 *  $Revision: 1.4 $
 *
 *  last change: $Author: rt $ $Date: 2005-09-08 09:43:17 $
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

#ifndef	_WRONG_HXX
#define	_WRONG_HXX

#ifndef _SVSTDARR_HXX
#define _SVSTDARR_XUB_STRLEN
#define _SVSTDARR_ULONGS
#include <svtools/svstdarr.hxx>
#endif
/*N*/ #include <tools/debug.hxx> //for stripping
namespace binfilter {
#define WRPOS( nIdx ) ((xub_StrLen)( GetObject( nIdx ) ))
#define WRLEN( nIdx ) ((xub_StrLen)( aLen.GetObject( nIdx ) ))

class SwWrongList : public SvXub_StrLens
{
    SvXub_StrLens aLen;
    xub_StrLen nBeginInvalid;	// Start des ungueltigen Bereichs
    xub_StrLen nEndInvalid;		// Ende des ungueltigen Bereichs
    void ShiftLeft( xub_StrLen &rPos, xub_StrLen nStart, xub_StrLen nEnd )
    { if( rPos > nStart ) rPos = rPos > nEnd ? rPos - nEnd + nStart : nStart; }
    void ShiftRight( xub_StrLen &rPos, xub_StrLen nStart, xub_StrLen nEnd )
    { if( rPos >= nStart ) rPos += nStart - nEnd; }
    void _Invalidate( xub_StrLen nBegin, xub_StrLen nEnd );
public:
    inline SwWrongList() :
        SvXub_StrLens(5,5), aLen(5,5), nBeginInvalid( STRING_LEN ){}
    inline xub_StrLen GetBeginInv() const { return nBeginInvalid; }
    inline xub_StrLen GetEndInv() const { return nEndInvalid; }
    inline BOOL InsideInvalid( xub_StrLen nChk ) const
        { return nChk >= nBeginInvalid && nChk <= nEndInvalid; }
    inline void SetInvalid( xub_StrLen nBegin, xub_StrLen nEnd )
        { nBeginInvalid = nBegin; nEndInvalid = nEnd; }
    inline void Validate(){ nBeginInvalid = STRING_LEN; }
    inline void Invalidate( xub_StrLen nBegin, xub_StrLen nEnd )
        { if( STRING_LEN == GetBeginInv() ) SetInvalid( nBegin, nEnd );
          else _Invalidate( nBegin, nEnd ); }
    BOOL InvalidateWrong();
//STRIP001 	BOOL Fresh( xub_StrLen &rStart, xub_StrLen &rEnd, xub_StrLen nPos,
//STRIP001 			xub_StrLen nLen, USHORT nIndex, xub_StrLen nCursorPos );
//STRIP001 	USHORT GetPos( xub_StrLen nValue ) const;
//STRIP001 	sal_Bool Check( xub_StrLen &rChk, xub_StrLen &rLn ) const;
//STRIP001 	sal_Bool InWrongWord( xub_StrLen &rChk, xub_StrLen &rLn ) const;
//STRIP001 	xub_StrLen NextWrong( xub_StrLen nChk ) const;
//STRIP001 	xub_StrLen LastWrong( xub_StrLen nChk ) const;
    void Move( xub_StrLen nPos, long nDiff ){DBG_BF_ASSERT(0, "STRIP");} ;//STRIP001 	void Move( xub_StrLen nPos, long nDiff );
//STRIP001 	void Clear();
//STRIP001 	void Clear( xub_StrLen nBegin, xub_StrLen nEnd );

    // Divide the list into two part, the wrong words until nSplitPos will be
    // removed and transferred to a new SwWrongList.
//STRIP001     SwWrongList* SplitList( xub_StrLen nSplitPos );
    // Join the next SwWrongList, nInsertPos is my own text length, where
    // the other wrong list has to be inserted.
//STRIP001     void JoinList( SwWrongList* pNext, xub_StrLen nInsertPos );

    inline xub_StrLen Len( USHORT nIdx ) const { return WRLEN( nIdx );	}
    inline xub_StrLen Pos( USHORT nIdx ) const { return WRPOS( nIdx );	}
    inline void Insert( xub_StrLen nNewPos, xub_StrLen nNewLen, USHORT nWhere )
    {SvXub_StrLens::Insert( nNewPos, nWhere ); aLen.Insert( nNewLen, nWhere );}

// Wer braucht dies?
    void Insert( ULONG nNew )
    ;//	{ SvULongs::Insert( nNew, GetPos( (USHORT)( nNew & WRMASK ) ) ); }
};


} //namespace binfilter
#endif

