/*************************************************************************
 *
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER.
 * 
 * Copyright 2008 by Sun Microsystems, Inc.
 *
 * OpenOffice.org - a multi-platform office productivity suite
 *
 * $RCSfile: htmlout.hxx,v $
 * $Revision: 1.3 $
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

#ifndef _HTMLOUT_HXX
#define _HTMLOUT_HXX

#ifndef INCLUDED_SVTDLLAPI_H
#include "bf_svtools/svtdllapi.h"
#endif

#ifndef _SOLAR_H
#include <tools/solar.h>
#endif

#ifndef _RTL_TEXTENC_H
#include <rtl/textenc.h>
#endif
#ifndef _SFXMACITEM_HXX //autogen
#include <bf_svtools/macitem.hxx>
#endif

class Color;
class String;
class SvStream;
class SvDataObject;

namespace binfilter
{
class ImageMap;

class SvxMacroTableDtor;
class SvNumberFormatter;

struct HTMLOutEvent
{
    const sal_Char *pBasicName;
    const sal_Char *pJavaName;
    USHORT nEvent;
};

struct  HTMLOutContext
{
    rtl_TextEncoding m_eDestEnc;
    rtl_TextToUnicodeConverter m_hConv;
    rtl_TextToUnicodeContext   m_hContext;

    HTMLOutContext( rtl_TextEncoding eDestEnc );
    ~HTMLOutContext();
};

struct HTMLOutFuncs
{
#if defined(MAC) || defined(UNX)
    static const sal_Char sNewLine;		// nur \012 oder \015
#else
    static const sal_Char __FAR_DATA sNewLine[];	// \015\012
#endif

     static void ConvertStringToHTML( const String& sSrc, ByteString& rDest,
                        rtl_TextEncoding eDestEnc = RTL_TEXTENCODING_MS_1252,
                        String *pNonConvertableChars = 0);

     static SvStream& Out_AsciiTag( SvStream&, const sal_Char* pStr,
                                   BOOL bOn = TRUE,
                        rtl_TextEncoding eDestEnc = RTL_TEXTENCODING_MS_1252);
     static SvStream& Out_Char( SvStream&, sal_Unicode cChar,
                        HTMLOutContext& rContext, 
                        String *pNonConvertableChars = 0 );
     static SvStream& Out_String( SvStream&, const String&,
                        rtl_TextEncoding eDestEnc = RTL_TEXTENCODING_MS_1252,
                        String *pNonConvertableChars = 0 );
     static SvStream& Out_Hex( SvStream&, ULONG nHex, BYTE nLen,
                        rtl_TextEncoding eDestEnc = RTL_TEXTENCODING_MS_1252 );
     static SvStream& Out_Color( SvStream&, const Color&,
                        rtl_TextEncoding eDestEnc = RTL_TEXTENCODING_MS_1252 );
     static SvStream& Out_ImageMap( SvStream&, const String&, const ImageMap&, const String&,
                                   const HTMLOutEvent *pEventTable,
                                   BOOL bOutStarBasic,
                                   const sal_Char *pDelim = 0,
                                   const sal_Char *pIndentArea = 0,
                                   const sal_Char *pIndentMap = 0,
                        rtl_TextEncoding eDestEnc = RTL_TEXTENCODING_MS_1252,
                        String *pNonConvertableChars = 0 );
     static SvStream& FlushToAscii( SvStream&, HTMLOutContext& rContext );

     static SvStream& OutScript( SvStream& rStrm,
                                const String& rBaseURL,
                                const String& rSource,
                                const String& rLanguage,
                                ScriptType eScriptType,
                                const String& rSrc,
                                const String *pSBLibrary = 0,
                                const String *pSBModule = 0,
                        rtl_TextEncoding eDestEnc = RTL_TEXTENCODING_MS_1252,
                        String *pNonConvertableChars = 0 );

    // der 3. Parameter ist ein Array von HTMLOutEvents, das mit einem
    // nur aus 0 bestehen Eintrag terminiert ist.
     static SvStream& Out_Events( SvStream&, const SvxMacroTableDtor&,
                                 const HTMLOutEvent*, BOOL bOutStarBasic,
                        rtl_TextEncoding eDestEnc = RTL_TEXTENCODING_MS_1252,
                        String *pNonConvertableChars = 0 );

    // <TD SDVAL="..." SDNUM="...">
     static ByteString&	CreateTableDataOptionsValNum( ByteString& aStrTD,
                BOOL bValue, double fVal, ULONG nFormat,
                SvNumberFormatter& rFormatter,
                rtl_TextEncoding eDestEnc = RTL_TEXTENCODING_MS_1252,
                String *pNonConvertableChars = 0 );

     static BOOL PrivateURLToInternalImg( String& rURL );
};

}

#endif

