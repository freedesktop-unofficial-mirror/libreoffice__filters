/*************************************************************************
 *
 *  $RCSfile: sw_lotpar.cxx,v $
 *
 *  $Revision: 1.1.1.1 $
 *
 *  last change: $Author: hjs $ $Date: 2003-10-01 12:20:44 $
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

#ifndef _ERRHDL_HXX
#include <errhdl.hxx>
#endif
#ifndef _DOC_HXX
#include <doc.hxx>
#endif
#ifndef _SWSWERROR_H
#include <swerror.h>
#endif
#ifndef _FLTGLBLS_HXX
#include <fltglbls.hxx>
#endif
#ifndef _FLTINI_HXX
#include <fltini.hxx>
#endif
#ifndef _LOTPAR_HXX
#include <lotpar.hxx>
#endif
#ifndef _SWFLTOPT_HXX
#include <swfltopt.hxx>
#endif

LotGlob *pLotGlob = NULL;





SwLotusParser::SwLotusParser( SwDoc &rD, const SwPaM & rCrsr,
                                SvStream& rInInit, int bReadNewDoc,
                                CharSet eQ )
    : bNewDoc( bReadNewDoc )
{
    eQuellChar = eQ;
    pIn = &rInInit;
    pLotGlob = new LotGlob( rD, rCrsr );

    nReadBuffSize = 2048;
    pReadBuff = new char[ nReadBuffSize ];

//	aColRowBuff.SetDefWidth( ( USHORT ) ( 9192 ) );	// 4 Zeichen Standardbreite
}

SwLotusParser::~SwLotusParser()
{
    delete[] pReadBuff;
    delete pLotGlob;
    pLotGlob = NULL;
}


ULONG SwLotusParser::CallParser()
{
    static const sal_Char* aNames[4] = {
        "Excel_Lotus/MinRow", "Excel_Lotus/MaxRow",
        "Excel_Lotus/MinCol", "Excel_Lotus/MaxCol"
    };
    sal_uInt32 aVal[4];
    SwFilterOptions aOpt( 4, aNames, aVal );

    USHORT nMinRow = ( USHORT ) aVal[ 0 ];
    USHORT nMaxRow = ( USHORT ) aVal[ 1 ];
    USHORT nMinCol = ( USHORT ) aVal[ 2 ];
    USHORT nMaxCol = ( USHORT ) aVal[ 3 ];

    USHORT nAnzNodes = 65000U - pLotGlob->pD->GetNodes().Count();

    if( nMaxRow < nMinRow )
    {
        USHORT nTemp = nMinRow;
        nMinRow = nMaxRow;
        nMaxRow = nTemp;
    }

    if( nMaxCol < nMinCol )
    {
        USHORT nTemp = nMinCol;
        nMinCol = nMaxCol;
        nMaxCol = nTemp;
    }

    if( nMaxRow - nMinRow == 0 )
        nMaxRow = nMinRow + 30;		// Default bei 0 Rows

    if( nMaxCol - nMinCol == 0 )
        nMaxCol = nMinCol + 15;		// Default bei 0 Cols

    if( nAnzNodes < ( nMaxRow - nMinRow ) * ( nMaxCol - nMinCol ) * 3 )
        return ERR_EXCLOT_WRONG_RANGE;

    pLotGlob->SetRange( nMinCol, nMaxCol, nMinRow, nMaxRow ); // Default-Einstellung

    Parse();

    return 0;	// kein Fehler
}


ULONG LotusReader::Read( SwDoc &rDoc, SwPaM &rPam,
                    const String & /* FileName, falls benoetigt wird */ )
{
    ULONG nRet;
    if( !pStrm )
    {
        ASSERT( FALSE, "Lotus-Read ohne Stream" );
        nRet = ERR_SWG_READ_ERROR;
    }
    else
    {
        SwLotusParser* pParser = new SwLotusParser( rDoc, rPam, *pStrm,
                                                    !bInsertMode, eCodeSet );
        nRet = pParser->CallParser();		// 0 == kein Fehler aufgetreten
        delete pParser;
    }

    return nRet;
}



