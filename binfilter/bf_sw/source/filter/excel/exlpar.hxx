/*************************************************************************
 *
 *  $RCSfile: exlpar.hxx,v $
 *
 *  $Revision: 1.6 $
 *
 *  last change: $Author: kz $ $Date: 2006-11-08 15:42:31 $
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
#ifndef _EXLPAR_HXX
#define _EXLPAR_HXX

#include "fltbase.hxx"

#include "exccrts.hxx"
// auto strip #include "excdocum.hxx"
class SvStream; 
class String; 
namespace binfilter {


// einige Forward-Deklaratioen

class SwPaM;
class SwDoc;

class ValueFormBuffer;


enum StringInfoLen {
    LenByte = 0,// 1 Byte lange Stringlaengeninfo
    LenWord	= 1	// 2 Byte 	"		"
    };

enum BiffTyp {
    Biff2 = 0,
    Biff3 = 2,
    Biff3W = 3,
    Biff4 = 4,
    Biff4W = 5,
    Biff5 = 8,
    Biff5W = 9,
    BiffX = -1 };


class SwExcelParser : public SwFilterBase
{
    int 			bNewDoc : 1;
    BiffTyp			eDateiTyp;	// aktuelles Tabellen-Format
    static const double fExcToTwips;
    static const sal_Char *pBuildInName[];

    CharSet			eQuellChar;	// Quell-Zeichensatz (interner Zeichensatz)
    CharSet			eZielChar;	// Ziel-Zeichensatz

    USHORT			nLastCol;
    USHORT			nLastRow;
    USHORT			nLastXF;

//	ULONG			nLastBof;	// Stream Position NACH letzten BOF

    ColRowSettings	aColRowBuff;		// Col/Row-Einstellungen 1 Tabelle
    FltTabelle		aFltTab;			// Attribute-Optimierung

#ifdef USED
    ExcDokument		aExcDok;			// merkt sich Tabellen-Parameter
    ExcDataPool		aDataPool;			// merkt sich benannte Bereiche,
                                        //	Tabellenname, ... fuer'n Dialog
#endif

    ValueFormBuffer	*pValueFormBuffer;	// Exc->Sv-Numberformats

    USHORT			nIxfeIndex;	// merkt sich Angabe im IXFE-Record

    BOOL			bResultString;

    // ---------------------------------------------------------------
//	void			NI();				// nicht implementierter Opcode
    void			Dimensions();		// 0x00
    void			Blank25();			// 0x01
    void			Number25();			// 0x03
    void			Label25();			// 0x04
    void			Formula25();		// 0x06
    void			REC_String();		// 0x07
//	void			Row25();			// 0x08
    void			Bof2();				// 0x09
    void			Eof();				// 0x0A
//	void			Externsheet();		// 0x17
//	void			Name25();			// 0x18
//	void			Note();				// 0x1C
    void			Format235();		// 0x1E
//	void			Formatcount();		// 0x1F
//	void			Columndefault();	// 0x20
//	void			Array25();			// 0x21
//	void			Externname25();		// 0x23
    void			Colwidth();			// 0x24
//	void			Defrowheight2();	// 0x25
    void			Font25();			// 0x31
    void			Codepage();			// 0x42
    void			XF2();				// 0x43
    void			Ixfe();				// 0x44
    void			DefColWidth();		// 0x55
//	void			Builtinfmtcnt();	// 0x56
    void			Colinfo();			// 0x7D
    void			Rk();				// 0x7E
    void			Boundsheet();		// 0x85
//	void			Country();			// 0x8C
//	void			Bundlesoffset();	// 0x8E
//	void			Bundleheader();		// 0x8F
    void			Palette();			// 0x92
    void			Standardwidth();	// 0x99
//	void			Shrfmla();			// 0xBC
    void			Mulrk();			// 0xBD
    void			Mulblank();			// 0xBE
    void			Rstring();			// 0xD6
    void			XF5();				// 0xE0
    //									// 0x0200 -> 0x00
    void			Blank34();			// 0x0201
    void			Number34();			// 0x0203
    void			Label34();			// 0x0204
    void			Formula3();			// 0x0206
//	void			Row34();			// 0x0208
    void			Bof3();				// 0x0209
//	void			Name34();			// 0x0218
    void			Array34();			// 0x0221
    void			Externname34();		// 0x0223
    void			Defrowheight345();	// 0225
    void			Font34();			// 0x0231
    void			XF3();				// 0x0243
    //void			Rk();				// 0x027E -> 0x7E
    void			Formula4();			// 0x0406
    void			Bof4();				// 0x0409
    void			Format4();			// 0x041E
    void			XF4();				// 0x0443
    void			Bof5();				// 0x0809
    // ---------------------------------------------------------------
    double			RkToDouble( const UINT32 &nRk );
    String			&ReadExcString( StringInfoLen eLen, String &aString );
#ifdef USED
    void			ResetBof();
#endif
    void			EndSheet();
    void			ReadExcString( StringInfoLen eLen );
    void			PutCell( USHORT nCol, USHORT nRow, const String &rText,
                        USHORT nXF );
    void			PutCell( USHORT nCol, USHORT nRow, double fVal,
                        USHORT nXF );
    void			Parse();
    BOOL			GetRange( USHORT nLenExpr, USHORT &rTab, USHORT &rCS,
                        USHORT &rCE, USHORT &rRS, USHORT &RE );
    // ---------------------------------------------------------------
    void			Init();
    void			ScanDokuInfos();	// Info-Sammler fuer Arbeitsmappen
    void			ScanBiff2();
    void			ScanBiff3();
    void			ScanBiff4();
    void			ScanBiff3W();
    void			ScanBiff4W();
    void			ScanBiff5W();
#ifdef USED
    void			ReadTab( const ExcUiEntry &rUiEntry, ULONG nStrPos );
#endif
public:
    // Parameter bReadNewDoc gibt an, ob in ein bestehendes Dokument ein-
    // gelesen wird. TRUE: in ein "neues" Dokument einfuegen.
    SwExcelParser( SwDoc& rDoc, const SwPaM & rCrsr, SvStream& pIn,
        int bReadNewDoc, CharSet eQ );
    ~SwExcelParser();

    ULONG CallParser();
};

} //namespace binfilter
#endif
    // _EXLPAR_HXX

