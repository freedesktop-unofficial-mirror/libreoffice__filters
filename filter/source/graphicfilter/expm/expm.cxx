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

// MARKER(update_precomp.py): autogen include statement, do not remove
#include "precompiled_filter.hxx"

#include <vcl/graph.hxx>
#include <vcl/bmpacc.hxx>
#include <svtools/fltcall.hxx>

//============================ XPMWriter ==================================

class XPMWriter {

private:

    SvStream&			m_rOStm; 			// Die auszugebende XPM-Datei
    sal_uInt16				mpOStmOldModus;

    sal_Bool				mbStatus;
    sal_Bool				mbTrans;
    BitmapReadAccess*	mpAcc;
    sal_uLong				mnWidth, mnHeight;	// Bildausmass in Pixeln
    sal_uInt16				mnColors;

    com::sun::star::uno::Reference< com::sun::star::task::XStatusIndicator > xStatusIndicator;

    void				ImplCallback( sal_uInt16 nPercent );
    sal_Bool				ImplWriteHeader();
    void				ImplWritePalette();
    void				ImplWriteColor( sal_uInt16 );
    void				ImplWriteBody();
    void				ImplWriteNumber( sal_Int32 );
    void				ImplWritePixel( sal_uLong ) const;

public:
    XPMWriter(SvStream& rOStm);
    ~XPMWriter();

    sal_Bool				WriteXPM( const Graphic& rGraphic, FilterConfigItem* pFilterConfigItem );
};

//=================== Methoden von XPMWriter ==============================

XPMWriter::XPMWriter(SvStream& rOStm)
    : m_rOStm(rOStm)
    , mbStatus(sal_True)
    , mbTrans(sal_False)
    , mpAcc(NULL)
{
}

// ------------------------------------------------------------------------

XPMWriter::~XPMWriter()
{
}

// ------------------------------------------------------------------------

void XPMWriter::ImplCallback( sal_uInt16 nPercent )
{
    if ( xStatusIndicator.is() )
    {
        if ( nPercent <= 100 )
            xStatusIndicator->setValue( nPercent );
    }
}

//	------------------------------------------------------------------------

sal_Bool XPMWriter::WriteXPM( const Graphic& rGraphic, FilterConfigItem* pFilterConfigItem)
{
    Bitmap	aBmp;

    if ( pFilterConfigItem )
    {
        xStatusIndicator = pFilterConfigItem->GetStatusIndicator();
        if ( xStatusIndicator.is() )
        {
            rtl::OUString aMsg;
            xStatusIndicator->start( aMsg, 100 );
        }
    }

    BitmapEx	aBmpEx( rGraphic.GetBitmapEx() );
    aBmp = aBmpEx.GetBitmap();

    if ( rGraphic.IsTransparent() )					// event. transparente Farbe erzeugen
    {
        mbTrans = sal_True;
        if ( aBmp.GetBitCount() >= 8 )				// wenn noetig Bild auf 8 bit konvertieren
            aBmp.Convert( BMP_CONVERSION_8BIT_TRANS );
        else
            aBmp.Convert( BMP_CONVERSION_4BIT_TRANS );
        aBmp.Replace( aBmpEx.GetMask(), BMP_COL_TRANS );
    }
    else
    {
        if ( aBmp.GetBitCount() > 8 )				// wenn noetig Bild auf 8 bit konvertieren
            aBmp.Convert( BMP_CONVERSION_8BIT_COLORS );
    }
    mpAcc = aBmp.AcquireReadAccess();
    if ( mpAcc )
    {
        mnColors = mpAcc->GetPaletteEntryCount();
        mpOStmOldModus = m_rOStm.GetNumberFormatInt();
        m_rOStm.SetNumberFormatInt( NUMBERFORMAT_INT_BIGENDIAN );

        if ( ImplWriteHeader() )
        {
            ImplWritePalette();
            ImplWriteBody();
            m_rOStm << "\x22XPMENDEXT\x22\x0a};";
        }
        aBmp.ReleaseAccess( mpAcc );
    }
    else
        mbStatus = sal_False;

    m_rOStm.SetNumberFormatInt( mpOStmOldModus );

    if ( xStatusIndicator.is() )
        xStatusIndicator->end();

    return mbStatus;
}

// ------------------------------------------------------------------------

sal_Bool XPMWriter::ImplWriteHeader()
{
    mnWidth = mpAcc->Width();
    mnHeight = mpAcc->Height();
    if ( mnWidth && mnHeight && mnColors )
    {
        m_rOStm << "/* XPM */\x0astatic char * image[] = \x0a{\x0a\x22";
        ImplWriteNumber( mnWidth );
        m_rOStm << (sal_uInt8)32;
        ImplWriteNumber( mnHeight );
        m_rOStm << (sal_uInt8)32;
        ImplWriteNumber( mnColors );
        m_rOStm << (sal_uInt8)32;
        ImplWriteNumber( ( mnColors > 26 ) ? 2 : 1 );
        m_rOStm << "\x22,\x0a";
    }
    else mbStatus = sal_False;
    return mbStatus;
}

// ------------------------------------------------------------------------

void XPMWriter::ImplWritePalette()
{
    sal_uInt16 nTransIndex = 0xffff;

    if ( mbTrans )
        nTransIndex = mpAcc->GetBestMatchingColor( BMP_COL_TRANS );
    for ( sal_uInt16 i = 0; i < mnColors; i++ )
    {
        m_rOStm << "\x22";
        ImplWritePixel( i );
        m_rOStm << (sal_uInt8)32;
        if ( nTransIndex != i )
        {
            ImplWriteColor( i );
            m_rOStm << "\x22,\x0a";
        }
        else
            m_rOStm << "c none\x22,\x0a";
    }
}

// ------------------------------------------------------------------------

void XPMWriter::ImplWriteBody()
{
    for ( sal_uLong y = 0; y < mnHeight; y++ )
    {
        ImplCallback( (sal_uInt16)( ( 100 * y ) / mnHeight ) );			// processing output in percent
        m_rOStm << (sal_uInt8)0x22;
        for ( sal_uLong x = 0; x < mnWidth; x++ )
        {
            ImplWritePixel( (sal_uInt8)(mpAcc->GetPixel( y, x ) ) );
        }
        m_rOStm << "\x22,\x0a";
    }
}

// ------------------------------------------------------------------------
// eine Dezimalzahl im ASCII format wird in den Stream geschrieben

void XPMWriter::ImplWriteNumber(sal_Int32 nNumber)
{
    const rtl::OString aNum(rtl::OString::valueOf(nNumber));
    m_rOStm << aNum.getStr();
}

// ------------------------------------------------------------------------

void XPMWriter::ImplWritePixel( sal_uLong nCol ) const
{
    if ( mnColors > 26 )
    {
        sal_uInt8 nDiff = (sal_uInt8) ( nCol / 26 );
        m_rOStm << (sal_uInt8)( nDiff + 'A' );
        m_rOStm << (sal_uInt8)( nCol - ( nDiff*26 ) + 'A' );
    }
    else
        m_rOStm << (sal_uInt8)( nCol + 'A' );
}

// ------------------------------------------------------------------------
// ein Farbwert wird im Hexadezimalzahlformat in den Stream geschrieben
void XPMWriter::ImplWriteColor( sal_uInt16 nNumber )
{
    sal_uLong	nTmp;
    sal_uInt8	j;

    m_rOStm << "c #";	// # zeigt einen folgenden Hexwert an
    const BitmapColor& rColor = mpAcc->GetPaletteColor( nNumber );
    nTmp = ( rColor.GetRed() << 16 ) | ( rColor.GetGreen() << 8 ) | rColor.GetBlue();
    for ( signed char i = 20; i >= 0 ; i-=4 )
    {
        if ( ( j = (sal_uInt8)( nTmp >> i ) & 0xf ) > 9 )
            j += 'A' - 10;
        else
            j += '0';
        m_rOStm << j;
    }
}

// ------------------------------------------------------------------------

// ---------------------
// - exported function -
// ---------------------

extern "C" sal_Bool __LOADONCALLAPI GraphicExport( SvStream& rStream, Graphic& rGraphic, FilterConfigItem* pFilterConfigItem, sal_Bool )
{
    XPMWriter aXPMWriter(rStream);

    return aXPMWriter.WriteXPM( rGraphic, pFilterConfigItem );
}


/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
