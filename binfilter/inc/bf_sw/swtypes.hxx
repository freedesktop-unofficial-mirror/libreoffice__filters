/* -*- Mode: C++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */
/*************************************************************************
 *
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER.
 * 
 * Copyright 2000, 2010 Oracle and/or its affiliates.
 *
 * OpenOffice.org - a multi-platform office productivity suite
 *
 * This file is part of OpenOffice.org.
 *
 * OpenOffice.org is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License version 3
 * only, as published by the Free Software Foundation.
 *
 * OpenOffice.org is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License version 3 for more details
 * (a copy is included in the LICENSE file that accompanied this code).
 *
 * You should have received a copy of the GNU Lesser General Public License
 * version 3 along with OpenOffice.org.  If not, see
 * <http://www.openoffice.org/license.html>
 * for a copy of the LGPLv3 License.
 *
 ************************************************************************/
#ifndef _SWTYPES_HXX
#define _SWTYPES_HXX

#include <bf_svtools/bf_solar.h>
#include <i18npool/lang.h>
#include <limits.h> 	//fuer LONG_MAX

#ifdef PM20
#include <stdlib.h>
#endif
#include <com/sun/star/uno/Reference.h>
#include <com/sun/star/lang/Locale.hpp>

// wenn das hier geaendert wird, dann auch im globals.hrc aendern!!!
//#define SW_FILEFORMAT_40 SOFFICE_FILEFORMAT_40

namespace com{namespace sun{namespace star{
    namespace linguistic2{
        class XDictionaryList;
        class XSpellChecker1;
        class XHyphenator;
        class XThesaurus;
    }
    namespace beans{
        class XPropertySet;
    }
}}}
namespace utl{
    class TransliterationWrapper;
}
class Size;
class MapMode;
class ResMgr;
class UniString;
class ByteString;
class Graphic;
class OutputDevice;
class CharClass;
class LocaleDataWrapper;
class CollatorWrapper;
namespace binfilter {


class SwPathFinder;


typedef long SwTwips;
#define INVALID_TWIPS	LONG_MAX
#define TWIPS_MAX		(LONG_MAX - 1)

#define MM50   283	// 1/2 cm in TWIPS

#define MINFLY 23	//Minimalgroesse fuer FlyFrms
#define MINLAY 23	//Minimalgroesse anderer Frms

// Default-Spaltenabstand zweier Textspalten entspricht 0.3 cm
#define DEF_GUTTER_WIDTH (MM50 / 5 * 3)

//Minimale Distance (Abstand zum Text) fuer das BorderAttribut, damit
//die aligned'en Linien nicht geplaettet werden.
//28 Twips == 0,4mm
#define MIN_BORDER_DIST 28

    /* minimaler Dokmentrand */
const SwTwips lMinBorder = 1134;

//Die Wiesenbreite links neben und ueber dem Dokument.
//Die halbe Wiesenbreite ist der Abstand zwischen den Seiten.
#define DOCUMENTBORDER 568L

// Konstante Strings
extern UniString aEmptyStr;			// ""
extern ByteString aEmptyByteStr;	// ""
extern UniString aDotStr;			// '.'

//Zum Einfuegen von Beschriftungen (wie bzw. wo soll eingefuegt werden).
//Hier weil ein eigenes hxx nicht lohnt und es sonst nirgendwo so recht
//hinpasst.
enum SwLabelType
{
    LTYPE_TABLE,	//Beschriftung einer Tabelle
    LTYPE_OBJECT,	//Beschriftung von Grafik oder OLE
    LTYPE_FLY,		//Beschriftung eines (Text-)Rahmens
    LTYPE_DRAW		//Beschriftung eines Zeichen-Objektes
};


const BYTE OLD_MAXLEVEL = 5;
const BYTE MAXLEVEL = 10;		//Ehemals numrule.hxx
const BYTE NO_NUM 		= 200;  //Ehemals numrule.hxx
const BYTE NO_NUMBERING = 201;  //Ehemals numrule.hxx
const BYTE NO_INIT 		= 202;  //Ehemals numrule.hxx

// fuer Absaetze mit NO_NUM aber auf unterschiedlichen Leveln
// DAMIT entfaellt das NO_NUM !!!!
const BYTE NO_NUMLEVEL  = 0x20;	// wird mit den Levels verodert


/*
 * Nette Funktionen als MACRO oder inline
 */

/* ein KiloByte sind 1024 Byte */
#define KB 1024

#define SET_CURR_SHELL( shell ) CurrShell aCurr( shell )

// pPathFinder wird von der UI initialisiert. Die Klasse liefert alle
// benoetigten Pfade.
extern SwPathFinder *pPathFinder;

// Werte fuer die Einzuege an der Nummerierung und BulletListe
// (fuer die weiteren Ebenen sind die Werte mit den Ebenen+1 zu
//	multiplizieren; Ebenen 0..4 !!!)
const USHORT lBullIndent = 567 / 2;
const short lBullFirstLineOffset = -567 / 2;
const USHORT lNumIndent = 567 / 2;
const short lNumFirstLineOffset = -567 / 2;

// Anzahl der SystemField-Types vom SwDoc
#define INIT_FLDTYPES	32
// Anzahl der vordefinierten Seq-Feldtypen. Es handelt sich dabei
// immer um die letzen Felder vor INIT_FLDTYPES
#define INIT_SEQ_FLDTYPES	4

//Die ehemaligen Rendevouz-Ids leben weiter:
//Es gibt Ids fuer die Anker (SwFmtAnchor) und ein paar weitere die nur fuer
//Schnittstellen Bedeutung haben (SwDoc).
enum RndStdIds
{
    FLY_AT_CNTNT,		//Absatzgebundener Rahmen
    FLY_IN_CNTNT,		//Zeichengebundener Rahmen
    FLY_PAGE,			//Seitengebundener Rahmen
    FLY_AT_FLY,			//Rahmengebundener Rahmen ( LAYER_IMPL )
    FLY_AUTO_CNTNT,		//Automatisch positionierter, absatzgebundener Rahmen
                        //Der Rest wird nur fuer SS benutzt.
    RND_STD_HEADER,
    RND_STD_FOOTER,
    RND_STD_HEADERL,
    RND_STD_HEADERR,
    RND_STD_FOOTERL,
    RND_STD_FOOTERR,

    RND_DRAW_OBJECT		// ein Draw-Object !! nur fuer die SwDoc-Schnittstelle!
};


extern ResMgr* pSwResMgr;			// steht in swapp0.cxx
#define SW_RES(i)		ResId(i,*pSwResMgr)
#define SW_RESSTR(i)	UniString(ResId(i,*pSwResMgr))

com::sun::star::lang::Locale	CreateLocale( LanguageType eLanguage );

::com::sun::star::uno::Reference<
    ::com::sun::star::linguistic2::XHyphenator >	GetHyphenator();
::com::sun::star::uno::Reference<
    ::com::sun::star::linguistic2::XDictionaryList >	GetDictionaryList();
::com::sun::star::uno::Reference<
    ::com::sun::star::beans::XPropertySet >			GetLinguPropertySet();

// reutns the twip size of this graphic
Size GetGraphicSizeTwip( const Graphic&, OutputDevice* pOutDev );


// Seperator fuer Sprunge im Dokument auf verschiedene Inhalttype
const sal_Unicode cMarkSeperator = '|';
extern const sal_Char* pMarkToTable;				// Strings stehen
extern const sal_Char* pMarkToFrame;             // im Init.cxx
extern const sal_Char* pMarkToRegion;
extern const sal_Char* pMarkToOutline;
extern const sal_Char* pMarkToText;
extern const sal_Char* pMarkToGraphic;
extern const sal_Char* pMarkToOLE;

#ifndef DB_DELIM							// Ist in OFA definiert!!!
#define DB_DELIM ((sal_Unicode)0xff)		// Datenbank <-> Tabellen-Trenner
#endif


enum SetAttrMode
{
    SETATTR_DEFAULT			= 0x0000,	// default
    SETATTR_DONTEXPAND 		= 0x0001,	// TextAttribute nicht weiter expand.
    SETATTR_DONTREPLACE		= 0x0002,	// kein anderes TextAttrib verdraengen

    SETATTR_NOTXTATRCHR		= 0x0004,	// bei Attr ohne Ende kein 0xFF einfuegen
    SETATTR_NOHINTADJUST	= 0x0008, 	// keine Zusammenfassung von Bereichen.
    SETATTR_NOFORMATATTR	= 0x0010,	// nicht zum FormatAttribut umwandeln
    SETATTR_DONTCHGNUMRULE  = 0x0020, 	// nicht die NumRule veraendern
    SETATTR_APICALL			= 0x0040	// called from API (all UI related
                                        // functionality will be disabled)
};

//Umrechnung Twip<-> 1/100 mm fuer UNO

#define TWIP_TO_MM100(TWIP) 	((TWIP) >= 0 ? (((TWIP)*127L+36L)/72L) : (((TWIP)*127L-36L)/72L))
#define MM100_TO_TWIP(MM100)	((MM100) >= 0 ? (((MM100)*72L+63L)/127L) : (((MM100)*72L-63L)/127L))
#define TWIP_TO_MM100_UNSIGNED(TWIP)     ((((TWIP)*127L+36L)/72L))
#define MM100_TO_TWIP_UNSIGNED(MM100)    ((((MM100)*72L+63L)/127L))

#define SW_ISPRINTABLE( c ) ( c >= ' ' && 127 != c )

#ifndef SW_CONSTASCII_DECL
#define SW_CONSTASCII_DECL( n, s ) n[sizeof(s)]
#endif
#ifndef SW_CONSTASCII_DEF
#define SW_CONSTASCII_DEF( n, s ) n[sizeof(s)] = s
#endif


#define CHAR_HARDBLANK		((sal_Unicode)0x00A0)
#define CHAR_HARDHYPHEN		((sal_Unicode)0x2011)
#define CHAR_SOFTHYPHEN		((sal_Unicode)0x00AD)

// returns the APP - CharClass instance - used for all ToUpper/ToLower/...
CharClass& GetAppCharClass();
LocaleDataWrapper& GetAppLocaleData();

ULONG GetAppLanguage();


#define SW_COLLATOR_IGNORES ( \
    ::com::sun::star::i18n::CollatorOptions::CollatorOptions_IGNORE_CASE )

CollatorWrapper& GetAppCollator();
CollatorWrapper& GetAppCaseCollator();

const ::utl::TransliterationWrapper& GetAppCmpStrIgnore();


} //namespace binfilter
#endif

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
