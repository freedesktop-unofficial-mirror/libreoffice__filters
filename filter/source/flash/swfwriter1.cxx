/*************************************************************************
 *
 *  $RCSfile: swfwriter1.cxx,v $
 *
 *  $Revision: 1.1 $
 *
 *  last change: $Author: cl $ $Date: 2002-11-21 14:58:04 $
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
 *  Contributor(s): Christian Lippka (christian.lippka@sun.com)
 *					Thorsten Behrens (thorsten.behrens@sun.com)
 *
 *
 ************************************************************************/

#ifndef _SWF_WRITER_HXX_
#include "swfwriter.hxx"
#endif

#ifndef _SV_METAACT_HXX 
#include <vcl/metaact.hxx>
#endif
#ifndef _SV_GDIMTF_HXX 
#include <vcl/gdimtf.hxx>
#endif
#ifndef _SV_BMPACC_HXX
#include <vcl/bmpacc.hxx>
#endif
#ifndef _SV_VIRDEV_HXX 
#include <vcl/virdev.hxx>
#endif
#ifndef _SV_METRIC_HXX
#include <vcl/metric.hxx>
#endif


#ifndef _FILTER_HXX
#include <svtools/Filter.hxx>
#endif
#ifndef _SVTOOLS_GRAPHICTOOLS_HXX_ 
#include <svtools/graphictools.hxx>
#endif

#include <external/zlib/zlib.h>

#ifndef _SV_SALBTYPE_HXX
#include <vcl/salbtype.hxx>
#endif

using namespace ::swf;
using namespace ::std;
using namespace ::rtl;
using namespace ::com::sun::star::uno;
using namespace ::com::sun::star::io;
using namespace ::com::sun::star::beans;

extern sal_uInt16 getMaxBitsUnsigned( sal_uInt32 nValue );
extern sal_uInt16 getMaxBitsSigned( sal_Int32 nValue );

static MapMode aTWIPSMode( MAP_TWIP );
static MapMode a100thmmMode( MAP_100TH_MM );

// -----------------------------------------------------------------------------

Point Writer::map( const Point& rPoint ) const
{
    const MapMode& aSourceMapMode = mpVDev->GetMapMode();

    Point retPoint = mpVDev->LogicToLogic( rPoint,  &aSourceMapMode, &aTWIPSMode );

    // AS: Produces a 'possible loss of data' warning that we can't fix without
    //  hurting code readability.
    retPoint.X() *= mnDocXScale;
    retPoint.Y() *= mnDocYScale;

    return retPoint;
}

// -----------------------------------------------------------------------------

Size Writer::map( const Size& rSize ) const
{
    const MapMode& aSourceMapMode = mpVDev->GetMapMode();

    Size retSize = mpVDev->LogicToLogic( rSize,  &aSourceMapMode, &aTWIPSMode );

    // AS: Produces a 'possible loss of data' warning that we can't fix without
    //  hurting code readability.
    retSize.Width() *= mnDocXScale;
    retSize.Height() *= mnDocYScale;

    return retSize;
}

// -----------------------------------------------------------------------------

void Writer::map( PolyPolygon& rPolyPolygon ) const
{
    const sal_uInt16 nPolyCount = rPolyPolygon.Count();
    if( nPolyCount )
    {
        sal_uInt16 nPoly, nPoint, nPointCount;
        for( nPoly = 0; nPoly < nPolyCount; nPoly++ )
        {
            Polygon& rPoly = rPolyPolygon[nPoly];
            nPointCount = rPoly.GetSize();

            for( nPoint = 0; nPoint < nPointCount; nPoint++ )
            {
                rPoly[nPoint] = map( rPoly[nPoint] );
            }
        }
    }
}

// -----------------------------------------------------------------------------

sal_Int32 Writer::mapRelative( sal_Int32 n100thMM ) const
{
    MapMode aSourceMapMode( mpVDev->GetMapMode() );
    aSourceMapMode.SetOrigin( Point() );

    sal_Int32 nTwips = mpVDev->LogicToLogic( Point( n100thMM, n100thMM ),  &aSourceMapMode, &aTWIPSMode ).X();
    return nTwips;
}

// -----------------------------------------------------------------------------

/**
*/
void Writer::Impl_addPolygon( BitStream& rBits, const Polygon& rPoly, sal_Bool bFilled )
{
    Point aLastPoint( rPoly[0] );

    Impl_addShapeRecordChange( rBits, _Int16(aLastPoint.X()),_Int16(aLastPoint.Y()), bFilled );

    USHORT i = 0, nSize = rPoly.GetSize();

    double d = 16.0f;

    // points
    while( ( i + 1 ) < nSize )
    {
        if( ( i + 3 ) < nSize )
        { 
            BYTE P1( rPoly.GetFlags( i ) );
            BYTE P4( rPoly.GetFlags( i + 3 ) );

            if( ( POLY_NORMAL == P1 || POLY_SMOOTH == P1 || POLY_SYMMTR == P1 ) &&
                ( POLY_CONTROL == rPoly.GetFlags( i + 1 ) ) &&
                ( POLY_CONTROL == rPoly.GetFlags( i + 2 ) ) &&
                ( POLY_NORMAL == P4 || POLY_SMOOTH == P4 || POLY_SYMMTR == P4 ) )
            {
                Impl_quadBezierApprox( rBits, aLastPoint, d*d, 
                                      rPoly.GetPoint( i ).X(),   rPoly.GetPoint( i ).Y(),
                                      rPoly.GetPoint( i+1 ).X(), rPoly.GetPoint( i+1 ).Y(),
                                      rPoly.GetPoint( i+2 ).X(), rPoly.GetPoint( i+2 ).Y(),
                                      rPoly.GetPoint( i+3 ).X(), rPoly.GetPoint( i+3 ).Y() );
                i += 3;
                continue;
            }
        }		
        
        ++i;

        const Point aPolyPoint( rPoly[ i ] );
        if( aPolyPoint != aLastPoint )
        {
            Impl_addStraightEdgeRecord( rBits, _Int16(aPolyPoint.X() - aLastPoint.X()),_Int16(aPolyPoint.Y() - aLastPoint.Y()));
            aLastPoint = aPolyPoint;
        }
    }

    if( bFilled && (rPoly[0] != rPoly[nSize-1]))
    {
        const Point aPolyPoint( rPoly[ 0 ] );
        if( aPolyPoint != aLastPoint )
        {
            Impl_addStraightEdgeRecord( rBits, _Int16(aPolyPoint.X() - aLastPoint.X()),_Int16(aPolyPoint.Y() - aLastPoint.Y()));
        }
    }
}

// -----------------------------------------------------------------------------

/** exports a style change record with a move to (x,y) and depending on bFilled a line style 1 or fill style 1
*/
void Writer::Impl_addShapeRecordChange( BitStream& rBits, sal_Int16 dx, sal_Int16 dy, sal_Bool bFilled )
{
    rBits.writeUB( 0, 1 );			// TypeFlag
    rBits.writeUB( 0, 1 );			// StateNewStyles
    rBits.writeUB( !bFilled, 1 );	// StateLineStyle
    rBits.writeUB( 0, 1 );			// StateFillStyle0
    rBits.writeUB( bFilled, 1 );		// StateFillStyle1
    rBits.writeUB( 1, 1 );			// StateMoveTo

    sal_uInt16 nMoveBits = max( getMaxBitsSigned( dx ), getMaxBitsSigned( dy ) );

    rBits.writeUB( nMoveBits, 5 );	// Number of bits per value
                                    // TODO: Optimize horizontal and vertical lines
    rBits.writeSB( dx, nMoveBits );	// DeltaX
    rBits.writeSB( dy, nMoveBits );	// DeltaY

    rBits.writeUB( 1, 1 );			// set FillStyle1 or LineStyle to 1
}

// -----------------------------------------------------------------------------

/** exports a straight edge record
*/
void Writer::Impl_addStraightEdgeRecord( BitStream& rBits, sal_Int16 dx, sal_Int16 dy )
{
    rBits.writeUB( 1, 1 );			// TypeFlag
    rBits.writeUB( 1, 1 );			// StraightFlag

    sal_uInt16 nBits = max( getMaxBitsSigned( dx ), getMaxBitsSigned( dy ) );

    rBits.writeUB( nBits - 2, 4 );	// Number of bits per value

    if( (dx != 0) && (dy != 0) )
    {
        rBits.writeUB( 1, 1 );			// GeneralLineFlag 
        rBits.writeSB( dx, nBits );		// DeltaX
        rBits.writeSB( dy, nBits );		// DeltaY
    }
    else
    {
        rBits.writeUB( 0, 1 );
        rBits.writeUB( ( dx == 0 ), 1 );
        if( dx == 0 )
        {
            rBits.writeSB( dy, nBits );		// DeltaY
        }
        else
        {
            rBits.writeSB( dx, nBits );		// DeltaX
        }
    }
}

// -----------------------------------------------------------------------------

/** exports a curved edge record
*/
void Writer::Impl_addCurvedEdgeRecord( BitStream& rBits, sal_Int16 control_dx, sal_Int16 control_dy, sal_Int16 anchor_dx, sal_Int16 anchor_dy )
{
    rBits.writeUB( 1, 1 );			// TypeFlag
    rBits.writeUB( 0, 1 );			// CurvedFlag

    sal_uInt8 nBits = static_cast<sal_uInt8>(
        max( getMaxBitsSigned( control_dx ), 
            max( getMaxBitsSigned( control_dy ), 
                max( getMaxBitsSigned( anchor_dx ),
                    max( getMaxBitsSigned( anchor_dy ), (sal_uInt16)3 ) ) ) ) );

    rBits.writeUB( nBits - 2, 4 );	// Number of bits per value

    rBits.writeSB( control_dx, nBits );		// DeltaX
    rBits.writeSB( control_dy, nBits );		// DeltaY
    rBits.writeSB( anchor_dx, nBits );		// DeltaX
    rBits.writeSB( anchor_dy, nBits );		// DeltaY
}

// -----------------------------------------------------------------------------

/** exports a end shape record
*/
void Writer::Impl_addEndShapeRecord( BitStream& rBits )
{
    rBits.writeUB( 0, 6 );
}

// -----------------------------------------------------------------------------

void Writer::Impl_writePolygon( const Polygon& rPoly, sal_Bool bFilled )
{
    PolyPolygon aPolyPoly( rPoly );
    Impl_writePolyPolygon( aPolyPoly, bFilled );
}

// -----------------------------------------------------------------------------

void Writer::Impl_writePolygon( const Polygon& rPoly, sal_Bool bFilled, const Color& rFillColor, const Color& rLineColor )
{
    PolyPolygon aPolyPoly( rPoly );
    Impl_writePolyPolygon( aPolyPoly, bFilled, rFillColor, rLineColor );
}

// -----------------------------------------------------------------------------

void Writer::Impl_writePolyPolygon( const PolyPolygon& rPolyPoly, sal_Bool bFilled, sal_uInt8 nTransparence /* = 0 */ )
{
    Color aLineColor( mpVDev->GetLineColor() );
    if( 0 == aLineColor.GetTransparency() )
        aLineColor.SetTransparency( nTransparence );
    Color aFillColor( mpVDev->GetFillColor() );
    if( 0 == aFillColor.GetTransparency() )
        aFillColor.SetTransparency( nTransparence );
    Impl_writePolyPolygon(rPolyPoly, bFilled, aFillColor, aLineColor );
}

// -----------------------------------------------------------------------------

void Writer::Impl_writePolyPolygon( const PolyPolygon& rPolyPoly, sal_Bool bFilled, const Color& rFillColor, const Color& rLineColor )
{
    PolyPolygon aPolyPoly( rPolyPoly );

    if( aPolyPoly.Count() )
    {
        map( aPolyPoly );

        if( mpClipPolyPolygon )
            rPolyPoly.GetIntersection( *mpClipPolyPolygon, aPolyPoly );

        sal_uInt16 nID;
        if( bFilled )
        {
            Color aFillColor( rFillColor );
            if( 0 != mnGlobalTransparency )
                aFillColor.SetTransparency( mnGlobalTransparency );

            FillStyle aStyle( aFillColor );
            nID = defineShape( aPolyPoly, aStyle );
        }
        else
        {
            Color aLineColor( rLineColor );
            if( 0 != mnGlobalTransparency )
                aLineColor.SetTransparency( mnGlobalTransparency );

            nID = defineShape( aPolyPoly, 1, aLineColor );
        }
        maShapeIds.push_back( nID );
    }
}

// -----------------------------------------------------------------------------

/** a gradient is a transition from one color to another, rendered inside a given polypolygon */
void Writer::Impl_writeGradientEx( const PolyPolygon& rPolyPoly, const Gradient& rGradient )
{
    if( rPolyPoly.Count() )
    {
        PolyPolygon aPolyPolygon( rPolyPoly );
        map( aPolyPolygon );

        if( (rGradient.GetStyle() == GRADIENT_LINEAR) || (rGradient.GetStyle() == GRADIENT_RADIAL) )
        {
            const Rectangle aBoundRect( aPolyPolygon.GetBoundRect() );

            FillStyle aFillStyle( aBoundRect, rGradient );

            sal_uInt16 nShapeId = defineShape( aPolyPolygon, aFillStyle );
            maShapeIds.push_back( nShapeId );
        }
        else
        {
            setClipping( &aPolyPolygon );

            // render the gradient filling to simple polygons
            {
                GDIMetaFile	aTmpMtf;
                mpVDev->AddGradientActions( aPolyPolygon.GetBoundRect(), rGradient, aTmpMtf );
                Impl_writeActions( aTmpMtf );
            }

            setClipping( NULL );
        }
    }
}

// -----------------------------------------------------------------------------

void Writer::setClipping( const PolyPolygon* pClipPolyPolygon )
{
    mpClipPolyPolygon = pClipPolyPolygon;
}

// -----------------------------------------------------------------------------

// AS: Just comparing fonts straight up is too literal.  There are some
//  differences in font that actually require different glyphs to be defined,
//  and some that don't.  This function is meant to capture all the differences
//  that we care about.
bool compare_fonts_for_me(const Font& rFont1, const Font& rFont2)
{
    return rFont1.GetName() == rFont2.GetName() &&
            rFont1.GetWeight() == rFont2.GetWeight() &&
            rFont1.GetItalic() == rFont2.GetItalic() &&
            rFont1.IsOutline() == rFont2.IsOutline() &&
            rFont1.IsShadow() == rFont2.IsShadow() &&
            rFont1.GetRelief() == rFont2.GetRelief();
}

// -----------------------------------------------------------------------------

FlashFont& Writer::Impl_getFont( const Font& rFont )
{
    FontMap::iterator aIter( maFonts.begin() );
    const FontMap::iterator aEnd( maFonts.end() );

    while( aIter != aEnd )
    {
        const Font tempFont = (*aIter)->getFont();
        if( compare_fonts_for_me(tempFont, rFont) )
        {
            return **aIter;
        }

        aIter++;
    }

    FlashFont* pFont = new FlashFont( rFont, createID() );
    maFonts.push_back( pFont );
    return *pFont;
}

// -----------------------------------------------------------------------------

void Writer::Impl_writeText( const Point& rPos, const String& rText, const long* pDXArray, long nWidth )
{
    sal_uInt32 nLen = rText.Len();

    if( nLen )
    {
        Size	aNormSize;
        long*	pOwnArray;
        long*	pDX;

        // get text sizes
        if( pDXArray )
        {
            pOwnArray = NULL;
            aNormSize = Size( mpVDev->GetTextWidth( rText ), 0 );
            pDX = (long*) pDXArray;
        }
        else
        {	
            pOwnArray = new long[ nLen ];
            aNormSize = Size( mpVDev->GetTextArray( rText, pOwnArray ), 0 );
            pDX = pOwnArray;
        }

        if( nLen > 1 )
        {
            aNormSize.Width() = pDX[ nLen - 2 ] + mpVDev->GetTextWidth( rText.GetChar(  (USHORT) nLen - 1 ) );

            if( nWidth && aNormSize.Width() && ( nWidth != aNormSize.Width() ) )
            {
                const double fFactor = (double) nWidth / aNormSize.Width();

                sal_uInt32 i;
                for( i = 0; i < ( nLen - 1 ); i++ )
                    pDX[ i ] = FRound( pDX[ i ] * fFactor );
            }
        }

        Font aOldFont( mpVDev->GetFont() );
        Point				aBaseLinePos( rPos );

        Font aFont(aOldFont);
        short nOrientation = aFont.GetOrientation();
        aFont.SetOrientation( 0 );
        aFont.SetUnderline(UNDERLINE_NONE);
        aFont.SetStrikeout(STRIKEOUT_NONE);
        mpVDev->SetFont( aFont );

        const FontMetric	aMetric( mpVDev->GetFontMetric() );

        FlashFont&			rFlashFont = Impl_getFont( aFont );
        
        // always adjust text position to match baseline alignment
        switch( aOldFont.GetAlign() )
        {
            case( ALIGN_TOP ):
                aBaseLinePos.Y() += aMetric.GetAscent();
            break;

            case( ALIGN_BOTTOM ):
                aBaseLinePos.Y() -= aMetric.GetDescent();
            break;

            default:
            break;
        }

        // get mapped text position
        const Point aPt( map( aBaseLinePos ) );

        // write text element

/* test code to create a bound rect, not realy working for rotated text
            Size		aTextSize( map( Size( mpVDev->GetTextWidth( rText ), mpVDev->GetTextHeight() ) ) );
            Point		aMetricPoint( map( Point( aMetric.GetLeading(), aMetric.GetAscent() )  ) );

            Point		aTmpPoint( map( Point( - aMetric.GetLeading(), - aMetric.GetAscent() )  ) ); ;
            Rectangle	aTmpRectangle(aTmpPoint, aTextSize );
            Polygon 	aPoly( aTmpRectangle );

            aPoly.Rotate( aTmpPoint, (USHORT) nOrientation );

            Rectangle   aTextBoundRect( aPoly.GetBoundRect() );

            aPoly.Move( aPt.X(), aPt.Y() - map( Size( 0, aMetric.GetDescent() ) ).Height() );

*/

#if	0 // makes the calculated bound rect visible for debuging
{
        Polygon aTmpPoly( aPoly );
        sal_uInt16 nID = FlashGeometryExporter::writePolygonShape( aMovieStream, aTmpPoly, false, Color(COL_MAGENTA), Color(COL_MAGENTA), mpClipPolyPolygon  );
        ImplPlaceObject( nID );
}
#endif

        // CL: This is still a hack until we figure out how to calculate a correct bound rect 
        //	   for rotatet text
        Rectangle textBounds( 0, 0, static_cast<long>(mnDocWidth*mnDocXScale), static_cast<long>(mnDocHeight*mnDocYScale) );

        Matrix3D m;
        m.Rotate( static_cast<double>(nOrientation) * F_PI1800 );
        m.Translate( double(aPt.X()), double(aPt.Y()) );	

        sal_Int16 nHeight = _Int16( map( Size( 0, aFont.GetHeight() ) ).Height() );

        startTag( TAG_DEFINETEXT );

        sal_uInt16 nTextId = createID();

        mpTag->addUI16( nTextId );
        mpTag->addRect( textBounds );
        mpTag->addMatrix( m );

        sal_uInt8 nGlyphBits = 16;
        sal_uInt8 nAdvanceBits = 16;

        mpTag->addUI8( nGlyphBits );
        mpTag->addUI8( nAdvanceBits );

        // text style change record
        mpTag->addUI8( 0x8c );
        mpTag->addUI16( rFlashFont.getID() );
        mpTag->addRGB( mpVDev->GetTextColor() );
        mpTag->addUI16( _uInt16( nHeight ) );

        DBG_ASSERT( nLen <= 127, "TODO: handle text with more than 127 characters" );

        // Glyph record
        mpTag->addUI8( (sal_uInt8) nLen );

        BitStream aBits;

        sal_Int32 nLastDX = 0;
        sal_Int32 nAdvance;
        sal_uInt32 i;
        for( i = 0; i < nLen; i++  )
        {
            if( i < (nLen-1) )
            {
                nAdvance = pDX[i] - nLastDX;
                nLastDX = pDX[i];
            }
            else
            {
                nAdvance = 0;
            }

            aBits.writeUB( rFlashFont.getGlyph(rText.GetChar(_uInt16(i)),mpVDev), nGlyphBits );
            aBits.writeSB( _Int16(map( Size( nAdvance, 0 ) ).Width() ), nAdvanceBits );
        }

        mpTag->addBits( aBits );
        mpTag->addUI8( 0 );

        endTag();

        maShapeIds.push_back( nTextId );

        // AS: Write strikeout and underline, if neccessary.  This code was originally taken from the SVG
        //  export facility, although the positioning had to be tweaked a little.  I can't explain the
        //  numbers, but the flash lines up very well with the original OOo document.  All of this should
        //  probably be converted to polygons as part of the meta file, though, as we don't handle any
        //  fancy lines (like dashes).  
        if( aOldFont.GetStrikeout() || aOldFont.GetUnderline() )
        {
            Polygon		aPoly( 4 );
            const long	nLineHeight = Max( (long) FRound( aMetric.GetLineHeight() * 0.05 ), (long) 1 );

            if( aOldFont.GetStrikeout() )
            {
                aPoly[ 0 ].X() = aBaseLinePos.X(); 
                aPoly[ 0 ].Y() = aBaseLinePos.Y() - FRound( aMetric.GetAscent() * 0.26 ) - nLineHeight;
                aPoly[ 1 ].X() = aPoly[ 0 ].X() + aNormSize.Width() - 1; 
                aPoly[ 1 ].Y() = aPoly[ 0 ].Y();
                aPoly[ 2 ].X() = aPoly[ 1 ].X(); 
                aPoly[ 2 ].Y() = aPoly[ 1 ].Y() + nLineHeight - 1;
                aPoly[ 3 ].X() = aPoly[ 0 ].X(); 
                aPoly[ 3 ].Y() = aPoly[ 2 ].Y();
                        
                Impl_writePolygon( aPoly, sal_True, aOldFont.GetColor(), aOldFont.GetColor() );
            }

            // AS: The factor of 1.5 on the nLineHeight is a magic number.  I'm not sure why it works,
            //  but it looks good to me.
            if( aOldFont.GetUnderline() )
            {
                aPoly[ 0 ].X() = aBaseLinePos.X(); 
                aPoly[ 0 ].Y() = static_cast<long>(aBaseLinePos.Y() + 1.5*nLineHeight);
                aPoly[ 1 ].X() = aPoly[ 0 ].X() + aNormSize.Width() - 1; 
                aPoly[ 1 ].Y() = aPoly[ 0 ].Y();
                aPoly[ 2 ].X() = aPoly[ 1 ].X(); 
                aPoly[ 2 ].Y() = aPoly[ 1 ].Y() + nLineHeight - 1;
                aPoly[ 3 ].X() = aPoly[ 0 ].X(); 
                aPoly[ 3 ].Y() = aPoly[ 2 ].Y();

                Impl_writePolygon( aPoly, sal_True, aOldFont.GetColor(), aOldFont.GetColor() );
            }
        }

        mpVDev->SetFont( aOldFont );
        delete[] pOwnArray;
    }
}

// -----------------------------------------------------------------------------
// AS: Because JPEGs require the alpha channel provided seperately (JPEG does not
//  natively support alpha channel, but SWF lets you provide it seperately), we
//  extract the alpha channel into a seperate array here.
void getBitmapData( const BitmapEx& aBmpEx, sal_uInt8*& tgadata, sal_uInt8*& tgaAlphadata, sal_uInt32& nWidth, sal_uInt32& nHeight )
{
    if( !aBmpEx.IsEmpty() )
    {
        Bitmap              aBmp( aBmpEx.GetBitmap() );
        BitmapReadAccess*   pRAcc = aBmp.AcquireReadAccess();

        if( pRAcc )
        {
            AlphaMask   aAlpha;
            nWidth = pRAcc->Width();
            nHeight = pRAcc->Height();
            tgadata = new sal_uInt8[nWidth*nHeight*4];
            tgaAlphadata = new sal_uInt8[nWidth*nHeight];
            sal_uInt8* p = tgadata, *pAlpha = tgaAlphadata;


            if( aBmpEx.IsAlpha() )
                aAlpha = aBmpEx.GetAlpha();
            else if( aBmpEx.IsTransparent() )
                aAlpha = aBmpEx.GetMask();
            else
            {
                sal_uInt8 cAlphaVal = 0;
                aAlpha = AlphaMask( aBmp.GetSizePixel(), &cAlphaVal );
            }

            BitmapReadAccess* pAAcc = aAlpha.AcquireReadAccess();

            if( pAAcc )
            {
                for( sal_uInt32 nY = 0; nY < nHeight; nY++ )
                {
                    for( sal_uInt32 nX = 0; nX < nWidth; nX++ )
                    {
                        const sal_uInt8     nAlpha = pAAcc->GetPixel( nY, nX ).GetIndex();
                        const BitmapColor   aPixelColor( pRAcc->GetColor( nY, nX ) );

                        if( nAlpha == 0xff )
                        {
                            *p++ = 0;
                            *p++ = 0;
                            *p++ = 0;
                            *p++ = 0;
                        }
                        else
                        {
                            *p++ = 0xff-nAlpha;
                            *p++ = aPixelColor.GetRed();
                            *p++ = aPixelColor.GetGreen();
                            *p++ = aPixelColor.GetBlue();
                        }
                        *pAlpha++ = 0xff - nAlpha;
                    }
                }

                aAlpha.ReleaseAccess( pAAcc );
            }

            aBmp.ReleaseAccess( pRAcc );
        }
    }
}

// -----------------------------------------------------------------------------
sal_uInt16 Writer::defineBitmap( const BitmapEx &bmpSource, sal_Int32 nJPEGQualityLevel )
{
    ULONG bmpChecksum = bmpSource.GetChecksum();

    ChecksumCache::iterator it = mBitmapCache.find(bmpChecksum);

    // AS: We already exported this bitmap, so just return its ID.
    if (mBitmapCache.end() != it)
        return it->second;

    sal_uInt16 nBitmapId = createID();
    mBitmapCache[bmpChecksum] = nBitmapId;

    // AS: OK, we have a good image, so now we decide whether or not to JPEG it or
    //  or Lossless compress it.

    //Figure out lossless size
    sal_uInt8 *pImageData, *pAlphaData;
    sal_uInt32 width, height;

    getBitmapData( bmpSource, pImageData, pAlphaData, width, height );
    sal_uInt32 raw_size = width * height * 4;
    sal_uInt32 compressed_size = raw_size + (sal_uInt32)(raw_size/100) + 12;
    sal_uInt8 *pCompressed = new sal_uInt8[ compressed_size ];
    
    if(compress2(pCompressed, &compressed_size, pImageData, raw_size, Z_BEST_COMPRESSION) != Z_OK)
        DBG_ASSERT( false, "compress2 failed!" );

    // AS: SWF files let you provide an Alpha mask for JPEG images, but we have 
    //  to ZLIB compress the alpha channel seperately.
    sal_uInt32 alpha_compressed_size = 0;
    sal_uInt8 *pAlphaCompressed = NULL;
    if (bmpSource.IsAlpha() || bmpSource.IsTransparent())
    {
        alpha_compressed_size = width * height + (sal_uInt32)(raw_size/100) + 12;
        pAlphaCompressed = new sal_uInt8[ compressed_size ];
        
        if(compress2(pAlphaCompressed, &alpha_compressed_size, pAlphaData, width * height, Z_BEST_COMPRESSION) != Z_OK)
            DBG_ASSERT( false, "compress2 failed!" );
    }

    //Figure out JPEG size
    const sal_uInt8* pJpgData;
    sal_uInt32 nJpgDataLength = -1;

    Graphic aGraphic( bmpSource );
    SvMemoryStream aDstStm( 65535, 65535 );

    GraphicFilter aFilter;
    Sequence< PropertyValue > aFilterData(nJPEGQualityLevel != -1);
    if( nJPEGQualityLevel != -1 )
    {
        aFilterData[0].Name = OUString( RTL_CONSTASCII_USTRINGPARAM("Quality"));
        aFilterData[0].Value <<= nJPEGQualityLevel;
    }

    if( aFilter.ExportGraphic( aGraphic, String(), aDstStm,
                                aFilter.GetExportFormatNumberForShortName( OUString( RTL_CONSTASCII_USTRINGPARAM( JPG_SHORTNAME ) ) ),
                                false, &aFilterData ) == ERRCODE_NONE )
    {
        pJpgData = reinterpret_cast<const sal_uInt8*>(aDstStm.GetData());
        nJpgDataLength = aDstStm.Seek( STREAM_SEEK_TO_END );
    }

    // AS: Ok, now go ahead and use whichever is smaller.  If JPEG is smaller, then
    //  we have to export as TAG_DEFINEBITSJPEG3 in the case that there is alpha
    //  channel data.
    if (nJpgDataLength + alpha_compressed_size < compressed_size)
        Impl_writeJPEG(nBitmapId, pJpgData, nJpgDataLength, pAlphaCompressed, alpha_compressed_size, nJPEGQualityLevel == mnJPEGCompressMode);
    else
        Impl_writeBmp( nBitmapId, width, height, pCompressed, compressed_size );

    delete[] pCompressed;
    delete[] pAlphaCompressed;
    delete[] pImageData;
    delete[] pAlphaData;

    return nBitmapId;
}

// -----------------------------------------------------------------------------

void Writer::Impl_writeImage( const BitmapEx& rBmpEx, const Point& rPt, const Size& rSz, const Point& rSrcPt, const Size& rSrcSz, const Rectangle& rClipRect, bool bNeedToMapClipRect )
{
    if( !!rBmpEx )
    {
        BitmapEx bmpSource( rBmpEx );

        Rectangle originalPixelRect(Point(), bmpSource.GetSizePixel());

        Point srcPt( map(rPt) );
        Size srcSize( map(rSz) );
        Rectangle destRect( srcPt, srcSize );

        // AS: Christian, my scaling factors are different than yours, and work better for me.
        //  However, I can't explain why exactly.  I got some of this by trial and error.
        double XScale = static_cast<double>(originalPixelRect.GetWidth())/destRect.GetWidth();
        double YScale = static_cast<double>(originalPixelRect.GetHeight())/destRect.GetHeight();
        
        // AS: If rClipRect has a value set, then we need to crop the bmp appropriately.
        //  If a map event already occurred in the metafile, then we do not need to map
        //  the clip rect as it's already been done.
        if (!rClipRect.IsEmpty())
        {
            // AS: Christian, I also don't understand why bNeedToMapClipRect is necessary, but it
            //  works like a charm.  Sometimes the map event is missing from the metafile, but why?
            Size clipSize( bNeedToMapClipRect ? map(rClipRect.GetSize()) : rClipRect.GetSize() );
            Rectangle clipRect(Point(), clipSize);
            destRect.Intersection( clipRect );

            Rectangle cropRect(destRect);

            // AS: The bmp origion is always 0,0 so we have to adjust before we crop.
            cropRect.Move(-srcPt.X(), -srcPt.Y());
            // AS: Rectangle has no scale function (?!) so I do it manually...
            Rectangle cropPixelRect(static_cast<long>(cropRect.Left()*XScale), 
                                    static_cast<long>(cropRect.Top()*YScale), 
                                    static_cast<long>(cropRect.Right()*XScale), 
                                    static_cast<long>(cropRect.Bottom()*YScale));

            bmpSource.Crop(cropPixelRect);
        }

        if( !!bmpSource )
        {
            sal_Int32 nJPEGQuality = mnJPEGCompressMode;

            Size szDestPixel = mpVDev->LogicToPixel(srcSize, aTWIPSMode);

            double pixXScale = static_cast<double>(szDestPixel.Width()) / originalPixelRect.GetWidth();
            double pixYScale = static_cast<double>(szDestPixel.Height()) / originalPixelRect.GetHeight();

            // AS: If the image has been scaled down, then scale down the quality
            //   that we use for JPEG compression.
            if (pixXScale < 1.0 && pixYScale < 1.0)
            {

                double qualityScale = (pixXScale + pixYScale)/2;

                nJPEGQuality *= qualityScale;

                if (nJPEGQuality < 10)
                    nJPEGQuality += 3;
            }

            sal_uInt16 nBitmapId = defineBitmap(bmpSource, nJPEGQuality);

            Polygon aPoly( destRect );

            // AS: Since images are being cropped now, no translation is normally necessary.
            //  However, some things like graphical bullet points are still get translated.
            Matrix3D m;
            m.Scale(1.0/XScale, 1.0/YScale);
            if (destRect.Left() || destRect.Top())
                m.Translate(destRect.Left(), destRect.Top());

            FillStyle aFillStyle( nBitmapId, true, m );

            sal_uInt16 nShapeId = defineShape( aPoly, aFillStyle );

            maShapeIds.push_back( nShapeId );
        }
    }
}
// -----------------------------------------------------------------------------

void Writer::Impl_writeBmp( sal_uInt16 nBitmapId, sal_uInt32 width, sal_uInt32 height, sal_uInt8 *pCompressed, sal_uInt32 compressed_size )
{
    startTag( TAG_DEFINEBITSLOSSLESS2 );

    mpTag->addUI16( nBitmapId );
    mpTag->addUI8( 5 );
    mpTag->addUI16( _uInt16(width) );
    mpTag->addUI16( _uInt16(height) );

    mpTag->Write( pCompressed, compressed_size );

    endTag();
}

// -----------------------------------------------------------------------------

void Writer::Impl_writeJPEG(sal_uInt16 nBitmapId, const sal_uInt8* pJpgData, sal_uInt32 nJpgDataLength, sal_uInt8 *pAlphaCompressed, sal_uInt32 alpha_compressed_size, sal_Bool bStandardCompression )
{
    // AS: Go through the actuall JPEG bits, seperating out the
    //  header fields from the actual image fields.  Fields are
    //  identifed by 0xFFXX where XX is the field type.  Both
    //  the header and the image need start and stop (D8 and D9),
    //  so that's why you see those written to both.  I don't
    //  really know what the rest of these are, I got it to work
    //  kind of by trial and error and by comparing with known 
    //  good SWF files.
    sal_uInt8 cType = 0x01;
    const sal_uInt8* pJpgSearch = pJpgData;
    const sal_uInt8* pLastMark = pJpgData;

    SvMemoryStream EncodingTableStream;
    SvMemoryStream ImageBitsStream;
    for (;pJpgSearch < pJpgData + nJpgDataLength; pJpgSearch++)
    {
        if (0xFF == *pJpgSearch)
        {
        sal_uInt32 nLength = pJpgSearch - pLastMark;
            
            if (nLength > 0)
            {
                switch(cType)
                {
                case 0xD8:
                    EncodingTableStream.Write( pLastMark, nLength );
                    ImageBitsStream.Write( pLastMark, nLength );
                    break;

                case 0x01:
                case 0x02:
                case 0xDB:
                case 0xC4:
                    EncodingTableStream.Write( pLastMark, nLength );
                    break;

                case 0xC1:
                case 0xE0:
                case 0xC0:
                case 0xDA:
                case 0x03:
                case 0x00:
                    ImageBitsStream.Write( pLastMark, nLength );
                    break;

                default:
                    DBG_ERROR( "JPEG marker I didn't handle!" );

                }
            }

            cType = *(pJpgSearch + 1);
            pLastMark = pJpgSearch;

            // AS: The way that I'm checking for markers, we'll miss the
            //  one at the end, so I special case it :(
            if (0xD9 == cType)
            {
                EncodingTableStream.Write( pLastMark, 2 );
                ImageBitsStream.Write( pLastMark, 2 );
            }
        }
    }

    EncodingTableStream.Seek( STREAM_SEEK_TO_END );
    sal_uInt32 nEncodingTableSize = EncodingTableStream.Tell();
    EncodingTableStream.Seek( STREAM_SEEK_TO_BEGIN );

    ImageBitsStream.Seek( STREAM_SEEK_TO_END );
    sal_uInt32 nImageBitsSize = ImageBitsStream.Tell();
    ImageBitsStream.Seek( STREAM_SEEK_TO_BEGIN );

    // AS: If we need alpha support, use TAG_DEFINEBITSJPEG3.
    if (alpha_compressed_size > 0)
    {
        startTag( TAG_DEFINEBITSJPEG3 );

        mpTag->addUI16( nBitmapId );

        mpTag->addUI32( nEncodingTableSize + nImageBitsSize );

        mpTag->Write(EncodingTableStream.GetData(), nEncodingTableSize);
        mpTag->Write(ImageBitsStream.GetData(), nImageBitsSize);

        mpTag->Write( pAlphaCompressed, alpha_compressed_size );

        endTag();
    }
    else if (!bStandardCompression)
    {
        startTag( TAG_DEFINEBITSJPEG2 );

        mpTag->addUI16( nBitmapId );

        mpTag->Write(EncodingTableStream.GetData(), nEncodingTableSize);
        mpTag->Write(ImageBitsStream.GetData(), nImageBitsSize);

        endTag();
    }
    else
    {
        if (!mbWrittenJPEGTables)
        {
            mbWrittenJPEGTables = true;
            startTag( TAG_JPEGTABLES );

            mpTag->Write(EncodingTableStream.GetData(), nEncodingTableSize);
            
            endTag();
        }

        startTag( TAG_DEFINEBITS );

        mpTag->addUI16( nBitmapId );
        mpTag->Write(ImageBitsStream.GetData(), nImageBitsSize);

        endTag();
    }
}

// -----------------------------------------------------------------------------

void Writer::Impl_writeLine( const Point& rPt1, const Point& rPt2, const Color* pLineColor )
{
    Color aOldColor( mpVDev->GetLineColor() );
    if( pLineColor )
        mpVDev->SetLineColor( *pLineColor );

    const Point aPtAry[2] = { rPt1, rPt2 };
    Polygon aPoly( 2, aPtAry );
    Impl_writePolyPolygon( aPoly, false );

    mpVDev->SetLineColor( aOldColor );
}

// -----------------------------------------------------------------------------

void Writer::Impl_writeRect( const Rectangle& rRect, long nRadX, long nRadY )
{
    if( (rRect.nTop == rRect.nBottom) || (rRect.nLeft == rRect.nRight) )
    {
        Color aColor( mpVDev->GetFillColor() );
        Impl_writeLine( rRect.TopLeft(), rRect.BottomRight(), &aColor ); 
    }
    else
    {
        Polygon aPoly( rRect, nRadX, nRadY );
        Impl_writePolyPolygon( aPoly, true );
    }
}

// -----------------------------------------------------------------------------

void Writer::Impl_writeEllipse( const Point& rCenter, long nRadX, long nRadY )
{
    Polygon aPoly( rCenter, nRadX, nRadY );
    Impl_writePolyPolygon( aPoly, false );
}


/** writes the stroke defined by SvtGraphicStroke and returns true or it returns
    false if it can't handle this stroke.
*/
bool Writer::Impl_writeStroke( SvtGraphicStroke& rStroke )
{
    Polygon aPolygon;
    rStroke.getPath( aPolygon );
    PolyPolygon aPolyPolygon( aPolygon );

    Rectangle aOldRect( aPolyPolygon.GetBoundRect() );

    map( aPolyPolygon );

    Rectangle aNewRect( aPolyPolygon.GetBoundRect() );

    PolyPolygon aStartArrow;
    rStroke.getStartArrow( aStartArrow );
    if( 0 != aStartArrow.Count() )
        return false;		// todo: Implement line ends

    PolyPolygon aEndArrow;
    rStroke.getEndArrow( aEndArrow );
    if( 0 != aEndArrow.Count() )
        return false;		// todo: Implement line ends

    SvtGraphicStroke::DashArray aDashArray;
    rStroke.getDashArray( aDashArray );
    if( 0 != aDashArray.size() )
        return false;		// todo: implement dashes

    double fTransparency = rStroke.getTransparency();
    double fStrokeWidth = rStroke.getStrokeWidth();

    Color aColor( mpVDev->GetLineColor() );

    if( 0.0 != rStroke.getTransparency() )
        aColor.SetTransparency( MinMax( rStroke.getTransparency() * 0xff, 0, 0xff ) );

    sal_uInt16 nShapeId = defineShape( aPolyPolygon, mapRelative( rStroke.getStrokeWidth() ), aColor );
    maShapeIds.push_back( nShapeId );
    return true;
}

// -----------------------------------------------------------------------------

/** writes the filling defined by SvtGraphicFill and returns true or it returns
    false if it can't handle this filling.
*/
bool Writer::Impl_writeFilling( SvtGraphicFill& rFilling )
{
    PolyPolygon aPolyPolygon;
    rFilling.getPath( aPolyPolygon );

    Rectangle aOldRect( aPolyPolygon.GetBoundRect() );

    map( aPolyPolygon );

    Rectangle aNewRect( aPolyPolygon.GetBoundRect() );

    switch( rFilling.getFillType() )
    {
    case SvtGraphicFill::FillType::fillSolid:
        {
            Color aColor( rFilling.getFillColor() );

            if( 0.0 != rFilling.getTransparency() )
                aColor.SetTransparency( MinMax( rFilling.getTransparency() * 0xff, 0, 0xff ) );

            FillStyle aFillStyle( aColor );

            sal_uInt16 nShapeId = defineShape( aPolyPolygon, aFillStyle );
            maShapeIds.push_back( nShapeId );
        }
        break;
    case SvtGraphicFill::FillType::fillGradient:
        return false;
    case SvtGraphicFill::FillType::fillHatch:
        return false;
    case SvtGraphicFill::FillType::fillTexture:
        {
            Graphic aGraphic;
            rFilling.getGraphic( aGraphic );

            // CL->AS: Should we also scale down the quality here depending on image scale?
            sal_uInt16 nBitmapId = defineBitmap( aGraphic.GetBitmapEx(), mnJPEGCompressMode );

            Matrix3D aMatrix;

            SvtGraphicFill::Transform aTransform;

            rFilling.getTransform( aTransform );

            int a,b;
            for( a = 0; a < 2; a++ )
            {
                for( b = 0; b < 3; b++ )
                {
                    aMatrix[a][b] = aTransform.matrix[a*3+b];
                }
            }
            aMatrix[2][0] = 0.0; aMatrix[2][1] = 0.0; aMatrix[2][2] = 1.0; 

            // scale bitmap
            Rectangle originalPixelRect(Point(), aGraphic.GetBitmapEx().GetSizePixel());

            double XScale = (double)aNewRect.GetWidth()/aOldRect.GetWidth();
            double YScale = (double)aNewRect.GetHeight()/aOldRect.GetHeight();

             aMatrix.Scale( XScale, YScale );

            FillStyle aFillStyle( nBitmapId, !rFilling.IsTiling(), aMatrix );

            sal_uInt16 nShapeId = defineShape( aPolyPolygon, aFillStyle );
            maShapeIds.push_back( nShapeId );
        }
        break;
    }
    return true;
}

// -----------------------------------------------------------------------------

void Writer::Impl_writeActions( const GDIMetaFile& rMtf )
{
    Rectangle clipRect;
    bool bMap = false;
    for( ULONG i = 0, nCount = rMtf.GetActionCount(); i < nCount; i++ )
    {
        const MetaAction*	pAction = rMtf.GetAction( i );
        const USHORT		nType = pAction->GetType();

        switch( nType )
        {
            case( META_PIXEL_ACTION	):
            {
                const MetaPixelAction* pA = (const MetaPixelAction*) pAction;

                Impl_writeLine( pA->GetPoint(), pA->GetPoint(), &pA->GetColor() );
            }
            break;

            case( META_POINT_ACTION	):
            {
                const MetaPointAction* pA = (const MetaPointAction*) pAction;

                Impl_writeLine( pA->GetPoint(), pA->GetPoint() );
            }
            break;

            case( META_LINE_ACTION ):
            {
                const MetaLineAction* pA = (const MetaLineAction*) pAction;
                
                Impl_writeLine( pA->GetStartPoint(), pA->GetEndPoint() );
            }
            break;

            case( META_RECT_ACTION ):
            {
                Impl_writeRect( ( (const MetaRectAction*) pAction )->GetRect(), 0, 0 );
            }
            break;

            case( META_ROUNDRECT_ACTION	):
            {
                const MetaRoundRectAction* pA = (const MetaRoundRectAction*) pAction;

                Impl_writeRect( pA->GetRect(), pA->GetHorzRound(), pA->GetVertRound() );
            }
            break;

            case( META_ELLIPSE_ACTION ):
            {
                const MetaEllipseAction*	pA = (const MetaEllipseAction*) pAction;
                const Rectangle&			rRect = pA->GetRect();

                Impl_writeEllipse( rRect.Center(), rRect.GetWidth() >> 1, rRect.GetHeight() >> 1 );
            }
            break;

            case( META_ARC_ACTION ):
            case( META_PIE_ACTION ):
            case( META_CHORD_ACTION	):
            case( META_POLYGON_ACTION ):
            {
                Polygon aPoly;

                switch( nType )
                {
                    case( META_ARC_ACTION ):
                    {
                        const MetaArcAction* pA = (const MetaArcAction*) pAction;
                        aPoly = Polygon( pA->GetRect(), pA->GetStartPoint(), pA->GetEndPoint(), POLY_ARC );
                    }
                    break;

                    case( META_PIE_ACTION ):
                    {
                        const MetaPieAction* pA = (const MetaPieAction*) pAction;
                        aPoly = Polygon( pA->GetRect(), pA->GetStartPoint(), pA->GetEndPoint(), POLY_PIE );
                    }
                    break;

                    case( META_CHORD_ACTION	):
                    {
                        const MetaChordAction* pA = (const MetaChordAction*) pAction;
                        aPoly = Polygon( pA->GetRect(), pA->GetStartPoint(), pA->GetEndPoint(), POLY_CHORD );
                    }
                    break;
                    
                    case( META_POLYGON_ACTION ):
                        aPoly = ( (const MetaPolygonAction*) pAction )->GetPolygon();
                    break;
                }

                if( aPoly.GetSize() )
                {
                    Impl_writePolygon( aPoly, sal_True );
                }
            }
            break;

            case( META_POLYLINE_ACTION ):
            {
                const MetaPolyLineAction*	pA = (const MetaPolyLineAction*) pAction;
                const Polygon&				rPoly = pA->GetPolygon();

                if( rPoly.GetSize() )
                    Impl_writePolygon( rPoly, sal_False );
            }
            break;

            case( META_POLYPOLYGON_ACTION ):
            {
                const MetaPolyPolygonAction*	pA = (const MetaPolyPolygonAction*) pAction;
                const PolyPolygon&				rPolyPoly = pA->GetPolyPolygon();

                if( rPolyPoly.Count() )
                    Impl_writePolyPolygon( rPolyPoly, sal_True );
            }
            break;

            case( META_GRADIENT_ACTION ):
            {
                const MetaGradientAction*	pA = (const MetaGradientAction*) pAction;

                Polygon aPoly( pA->GetRect() );
                Impl_writeGradientEx( aPoly, pA->GetGradient() );
            }
            break;

            case( META_GRADIENTEX_ACTION ):
            {
                const MetaGradientExAction*	pA = (const MetaGradientExAction*) pAction;
                Impl_writeGradientEx( pA->GetPolyPolygon(), pA->GetGradient() );
            }
            break;

            case META_HATCH_ACTION:
            {
                const MetaHatchAction*	pA = (const MetaHatchAction*) pAction;
                GDIMetaFile				aTmpMtf;

                mpVDev->AddHatchActions( pA->GetPolyPolygon(), pA->GetHatch(), aTmpMtf );
                Impl_writeActions( aTmpMtf );
            }
            break;

            case( META_TRANSPARENT_ACTION ):
            {
                const MetaTransparentAction*	pA = (const MetaTransparentAction*) pAction;
                const PolyPolygon&				rPolyPoly = pA->GetPolyPolygon();

                if( rPolyPoly.Count() )
                {
                    // convert transparence from percent into 0x00 - 0xff
                    sal_uInt8 nTransparence = (sal_uInt8) MinMax( FRound( pA->GetTransparence() * 2.55 ), 0, 255 );
                    Impl_writePolyPolygon( rPolyPoly, sal_True, nTransparence );
                }
            }
            break;

            case( META_FLOATTRANSPARENT_ACTION ):
            {
                const MetaFloatTransparentAction*	pA = (const MetaFloatTransparentAction*) pAction;
                GDIMetaFile							aTmpMtf( pA->GetGDIMetaFile() );
                Point								aSrcPt( aTmpMtf.GetPrefMapMode().GetOrigin() );
                const Size							aSrcSize( aTmpMtf.GetPrefSize() );
                const Point							aDestPt( pA->GetPoint() );
                const Size							aDestSize( pA->GetSize() );
                const double						fScaleX = aSrcSize.Width() ? (double) aDestSize.Width() / aSrcSize.Width() : 1.0;
                const double						fScaleY = aSrcSize.Height() ? (double) aDestSize.Height() / aSrcSize.Height() : 1.0;
                long								nMoveX, nMoveY;

                if( fScaleX != 1.0 || fScaleY != 1.0 )
                {
                    aTmpMtf.Scale( fScaleX, fScaleY );
                    aSrcPt.X() = FRound( aSrcPt.X() * fScaleX );
                    aSrcPt.Y() = FRound( aSrcPt.Y() * fScaleY );
                }

                nMoveX = aDestPt.X() - aSrcPt.X(), nMoveY = aDestPt.Y() - aSrcPt.Y();

                if( nMoveX || nMoveY )
                    aTmpMtf.Move( nMoveX, nMoveY );

                const Gradient& rGradient = pA->GetGradient();
                sal_uInt32 nLuminance = ((sal_Int32)rGradient.GetStartColor().GetLuminance() + (sal_Int32)rGradient.GetEndColor().GetLuminance() ) >> 1;

                sal_uInt8 nOldGlobalTransparency = mnGlobalTransparency;
                mnGlobalTransparency = (sal_uInt8)MinMax( nLuminance, 0, 0xff );

                mpVDev->Push();
                Impl_writeActions( aTmpMtf );
                mpVDev->Pop();

                mnGlobalTransparency = nOldGlobalTransparency;
            }
            break;

            case( META_EPS_ACTION ):
            {
                const MetaEPSAction*	pA = (const MetaEPSAction*) pAction;
                const GDIMetaFile		aGDIMetaFile( pA->GetSubstitute() );
                sal_Bool				bFound = sal_False;

                for( ULONG i = 0, nCount = aGDIMetaFile.GetActionCount(); ( i < nCount ) && !bFound; i++ )
                {
                    const MetaAction* pSubstAct = aGDIMetaFile.GetAction( i );
                    
                    if( pSubstAct->GetType() == META_BMPSCALE_ACTION )
                    {
                        bFound = sal_True;
                        const MetaBmpScaleAction* pBmpScaleAction = (const MetaBmpScaleAction*) pSubstAct;
                        Impl_writeImage( pBmpScaleAction->GetBitmap(), 
                                      pA->GetPoint(), pA->GetSize(), 
                                      Point(), pBmpScaleAction->GetBitmap().GetSizePixel(), clipRect, !bMap  );
                    }
                }
            }
            break;

            case( META_COMMENT_ACTION ):
            {
                const MetaCommentAction*	pA = (const MetaCommentAction*) pAction;
                const BYTE* 				pData = pA->GetData();
                String						aSkipComment;

                if( pA->GetComment().CompareIgnoreCaseToAscii( "XGRAD_SEQ_BEGIN" ) == COMPARE_EQUAL )
                {
                    const MetaGradientExAction*	pGradAction = NULL;
                    sal_Bool					bDone = sal_False;

                    while( !bDone && ( ++i < nCount ) )
                    {
                        pAction = rMtf.GetAction( i );

                        if( pAction->GetType() == META_GRADIENTEX_ACTION )
                            pGradAction = (const MetaGradientExAction*) pAction;
                        else if( ( pAction->GetType() == META_COMMENT_ACTION ) && 
                                 ( ( (const MetaCommentAction*) pAction )->GetComment().CompareIgnoreCaseToAscii( "XGRAD_SEQ_END" ) == COMPARE_EQUAL ) )
                        {
                            bDone = sal_True;
                        }
                    }

                    if( pGradAction )
                        Impl_writeGradientEx( pGradAction->GetPolyPolygon(), pGradAction->GetGradient());
                }
                else if( pA->GetComment().CompareIgnoreCaseToAscii( "XPATHFILL_SEQ_BEGIN" ) == COMPARE_EQUAL && 
                         pData )
                {

                    // this comment encapsulates all high level information for a filling that caused
                    // the meta actions between the "XPATHFILL_SEQ_BEGIN" and "XPATHFILL_SEQ_END" comment.

                    SvtGraphicFill 	aFilling;
                    SvMemoryStream	aMemStm( (void*)pData, pA->GetDataSize(), STREAM_READ );

                    // read the fill info
                    aMemStm >> aFilling;

                    // if impl_writeFilling can handle this high level filling, it returns true and we
                    // skip all meta actions until "XPATHFILL_SEQ_END"
                    if( Impl_writeFilling( aFilling ) )
                    {
                        bool bDone = sal_False;

                        while( !bDone && ( ++i < nCount ) )
                        {
                            pAction = rMtf.GetAction( i );

                            if( ( pAction->GetType() == META_COMMENT_ACTION ) && 
                                     ( ( (const MetaCommentAction*) pAction )->GetComment().CompareIgnoreCaseToAscii( "XPATHFILL_SEQ_END" ) == COMPARE_EQUAL ) )
                            {
                                bDone = sal_True;
                            }
                        }
                    }
                }
                else if( pA->GetComment().CompareIgnoreCaseToAscii( "XPATHSTROKE_SEQ_BEGIN" ) == COMPARE_EQUAL && 
                         pData )
                {

                    // this comment encapsulates all high level information for a filling that caused
                    // the meta actions between the "XPATHFILL_SEQ_BEGIN" and "XPATHFILL_SEQ_END" comment.

                    SvtGraphicStroke aStroke;
                    SvMemoryStream	aMemStm( (void*)pData, pA->GetDataSize(), STREAM_READ );

                    // read the fill info
                    aMemStm >> aStroke;

                    // if impl_writeStroke can handle this high level stroke, it returns true and we
                    // skip all meta actions until "XPATHSTROKE_SEQ_END"
                    if( Impl_writeStroke( aStroke ) )
                    {
                        bool bDone = sal_False;

                        while( !bDone && ( ++i < nCount ) )
                        {
                            pAction = rMtf.GetAction( i );

                            if( ( pAction->GetType() == META_COMMENT_ACTION ) && 
                                     ( ( (const MetaCommentAction*) pAction )->GetComment().CompareIgnoreCaseToAscii( "XPATHSTROKE_SEQ_END" ) == COMPARE_EQUAL ) )
                            {
                                bDone = sal_True;
                            }
                        }
                    }
                }
            }
            break;

            case( META_BMPSCALE_ACTION ):
            {
                const MetaBmpScaleAction* pA = (const MetaBmpScaleAction*) pAction;

                Impl_writeImage( pA->GetBitmap(), 
                          pA->GetPoint(), pA->GetSize(), 
                          Point(), pA->GetBitmap().GetSizePixel(), clipRect, !bMap );
            }
            break;

            case( META_BMP_ACTION ):
            {
                const MetaBmpAction* pA = (const MetaBmpAction*) pAction;
                Impl_writeImage( pA->GetBitmap(), 
                          pA->GetPoint(), mpVDev->PixelToLogic( pA->GetBitmap().GetSizePixel()), 
                          Point(), pA->GetBitmap().GetSizePixel(), clipRect, !bMap );
            }
            break;

            case( META_BMPSCALEPART_ACTION ):
            {
                const MetaBmpScalePartAction* pA = (const MetaBmpScalePartAction*) pAction;
                Impl_writeImage( pA->GetBitmap(), 
                          pA->GetDestPoint(), pA->GetDestSize(), 
                          pA->GetSrcPoint(), pA->GetSrcSize(), clipRect, !bMap );
            }
            break;

            case( META_BMPEX_ACTION	):
            {
                const MetaBmpExAction*	pA = (const MetaBmpExAction*) pAction;
                Impl_writeImage( pA->GetBitmapEx(), 
                          pA->GetPoint(), mpVDev->PixelToLogic( pA->GetBitmapEx().GetSizePixel() ), 
                          Point(), pA->GetBitmapEx().GetSizePixel(), clipRect, !bMap );
            }
            break;

            case( META_BMPEXSCALE_ACTION ):
            {
                const MetaBmpExScaleAction* pA = (const MetaBmpExScaleAction*) pAction;
                Impl_writeImage( pA->GetBitmapEx(), 
                          pA->GetPoint(), pA->GetSize(), 
                          Point(), pA->GetBitmapEx().GetSizePixel(), clipRect, !bMap );
            }
            break;

            case( META_BMPEXSCALEPART_ACTION ):
            {
                const MetaBmpExScalePartAction* pA = (const MetaBmpExScalePartAction*) pAction;
                Impl_writeImage( pA->GetBitmapEx(), 
                          pA->GetDestPoint(), pA->GetDestSize(), 
                          pA->GetSrcPoint(), pA->GetSrcSize(), clipRect, !bMap );
            }
            break;

            case( META_TEXT_ACTION ):
            {
                const MetaTextAction* pA = (const MetaTextAction*) pAction;
                Impl_writeText( pA->GetPoint(), String( pA->GetText(), pA->GetIndex(), pA->GetLen() ), NULL, 0);
            }			
            break;

            case( META_TEXTRECT_ACTION ):
            {
                const MetaTextRectAction* pA = (const MetaTextRectAction*) pAction;
                Impl_writeText( pA->GetRect().TopLeft(), pA->GetText(), NULL, 0  );
            }
            break;

            case( META_TEXTARRAY_ACTION	):
            {
                const MetaTextArrayAction*	pA = (const MetaTextArrayAction*) pAction;
                Impl_writeText( pA->GetPoint(), String( pA->GetText(), pA->GetIndex(), pA->GetLen() ), pA->GetDXArray(), 0 );
            }
            break;

            case( META_STRETCHTEXT_ACTION ):
            {
                const MetaStretchTextAction* pA = (const MetaStretchTextAction*) pAction;
                Impl_writeText( pA->GetPoint(), String( pA->GetText(), pA->GetIndex(), pA->GetLen() ), NULL, pA->GetWidth() );
            }
            break;

            case( META_ISECTRECTCLIPREGION_ACTION ):
            {
                const MetaISectRectClipRegionAction* pA = (const MetaISectRectClipRegionAction*) pAction;
                clipRect = pA->GetRect();
            }
            case( META_CLIPREGION_ACTION ):
            case( META_ISECTREGIONCLIPREGION_ACTION	):
            case( META_MOVECLIPREGION_ACTION ):
            {
                ( (MetaAction*) pAction )->Execute( mpVDev );
//				mbClipAttrChanged = sal_True;
            }
            break;

            case( META_MAPMODE_ACTION ):  bMap = true;
            case( META_REFPOINT_ACTION ):
            case( META_LINECOLOR_ACTION	):
            case( META_FILLCOLOR_ACTION	):
            case( META_TEXTLINECOLOR_ACTION ):
            case( META_TEXTFILLCOLOR_ACTION	):
            case( META_TEXTCOLOR_ACTION	):
            case( META_TEXTALIGN_ACTION	):
            case( META_FONT_ACTION ):
            case( META_PUSH_ACTION ):
            case( META_POP_ACTION ):
            {
                ( (MetaAction*) pAction )->Execute( mpVDev );
            }
            break;

            case( META_RASTEROP_ACTION ):
            case( META_MASK_ACTION ):
            case( META_MASKSCALE_ACTION	):
            case( META_MASKSCALEPART_ACTION	):
            case( META_WALLPAPER_ACTION	):
            case( META_TEXTLINE_ACTION ):
            case( META_LAYOUTMODE_ACTION ):
            {
                // !!! >>> we don't want to support these actions
            }
            break;

            default:
                //DBG_ERROR( "FlashActionWriter::ImplWriteActions: unsupported MetaAction #" );
            break;
        }
    }
}


/////////////////////////////////////////////////////////////////////////


void Writer::Impl_addStraightLine( BitStream& rBits, Point& rLastPoint,
                                   const double P2x, const double P2y )
{
    Point aPoint( FRound(P2x), FRound(P2y) );

    Impl_addStraightEdgeRecord( rBits, _Int16(aPoint.X() - rLastPoint.X()),_Int16(aPoint.Y() - rLastPoint.Y()));
    rLastPoint = aPoint;

}

// -----------------------------------------------------------------------------

void Writer::Impl_addQuadBezier( BitStream& rBits, Point& rLastPoint,
                                 const double P2x, const double P2y,
                                 const double P3x, const double P3y )
{

    Point aControlPoint( FRound(P2x), FRound(P2y) );
    Point aAnchorPoint( FRound(P3x), FRound(P3y) );

    Impl_addCurvedEdgeRecord( rBits,
                                _Int16(aControlPoint.X() - rLastPoint.X()),_Int16(aControlPoint.Y() - rLastPoint.Y()),
                                _Int16(aAnchorPoint.X() - aControlPoint.X()),_Int16(aAnchorPoint.Y() - aControlPoint.Y()) );
    rLastPoint = aAnchorPoint;
}

// -----------------------------------------------------------------------------

/* Approximate given cubic bezier curve by quadratic bezier segments */
void Writer::Impl_quadBezierApprox( BitStream& rBits,
                                   Point& rLastPoint,
                                   const double d2,
                                   const double P1x, const double P1y,
                                   const double P2x, const double P2y,
                                   const double P3x, const double P3y,
                                   const double P4x, const double P4y )
{
    // Check for degenerate case, where the given cubic bezier curve
    // is already quadratic: P4 == 3P3 - 3P2 + P1
    if( P4x == 3.0*P3x - 3.0*P2x + P1x &&
        P4y == 3.0*P3y - 3.0*P2y + P1y )
    {
        Impl_addQuadBezier( rBits, rLastPoint,
                           3.0/2.0*P2x - 1.0/2.0*P1x, 3.0/2.0*P2y - 1.0/2.0*P1y, 
                           P4x, P4y);
    }
    else
    {
        // Create quadratic segment for given cubic:
        // Start and end point must coincide, determine quadratic control
        // point in such a way that it lies on the intersection of the
        // tangents at start and end point, resp. Thus, both cubic and
        // quadratic curve segments will match in 0th and 1st derivative
        // at the start and end points

        // Intersection of P2P1 and P4P3
        //           (P2y-P4y)(P3x-P4x)-(P2x-P4x)(P3y-P4y)
        //  lambda = ------------------------------------- 
        //           (P1x-P2x)(P3y-P4y)-(P1y-P2y)(P3x-P4x) 
        //
        // Intersection point IP is now
        // IP = P2 + lambda(P1-P2)
        //
        const double nominator( (P2y-P4y)*(P3x-P4x) - (P2x-P4x)*(P3y-P4y) );
        const double denominator( (P1x-P2x)*(P3y-P4y) - (P1y-P2y)*(P3x-P4x) );
        const double lambda( nominator / denominator );
    
        const double IPx( P2x + lambda*( P1x - P2x) );
        const double IPy( P2y + lambda*( P1y - P2y) );

        // Introduce some alias names: quadratic start point is P1, end
        // point is P4, control point is IP
        const double QP1x( P1x );
        const double QP1y( P1y );
        const double QP2x( IPx );
        const double QP2y( IPy );
        const double QP3x( P4x );
        const double QP3y( P4y );

        // Adapted bezier flatness test (lecture notes from R. Schaback,
        // Mathematics of Computer-Aided Design, Uni Goettingen, 2000)
        //
        // ||C(t) - Q(t)|| <= max     ||c_j - q_j||
        //                    0<=j<=n
        //
        // In this case, we don't need the distance from the cubic bezier
        // to a straight line, but to a quadratic bezier. The c_j's are
        // the cubic bezier's bernstein coefficients, the q_j's the
        // quadratic bezier's. We have the c_j's given, the q_j's can be
        // calculated from QPi like this (sorry, mixed index notation, we
        // use [1,n], formulas use [0,n-1]):
        //
        // q_0 = QP1 = P1
        // q_1 = 1/3 QP1 + 2/3 QP2
        // q_2 = 2/3 QP2 + 1/3 QP3
        // q_3 = QP3 = P4
        //
        // We can drop case 0 and 3, since there the curves coincide
        // (distance is zero)

        // calculate argument of max for j=1 and j=2
        const double fJ1x( P2x - 1.0/3.0*QP1x - 2.0/3.0*QP2x );
        const double fJ1y( P2y - 1.0/3.0*QP1y - 2.0/3.0*QP2y );
        const double fJ2x( P3x - 2.0/3.0*QP2x - 1.0/3.0*QP3x );
        const double fJ2y( P3y - 2.0/3.0*QP2y - 1.0/3.0*QP3y );

        // stop if distance from cubic curve is guaranteed to be bounded by d
        // Should denominator be 0: then P1P2 and P3P4 are parallel (P1P2^T R[90,P3P4] = 0.0),
        // meaning that either we have a straight line or an inflexion point (see else block below)
        if( 0.0 != denominator &&
            ::std::max( fJ1x*fJ1x + fJ1y*fJ1y, 
                        fJ2x*fJ2x + fJ2y*fJ2y) < d2 )
        {
            // requested resolution reached.
            // Add end points to output file.
            // order is preserved, since this is so to say depth first traversal.
            Impl_addQuadBezier( rBits, rLastPoint,
                                QP2x, QP2y, 
                                QP3x, QP3y);
        }
        else
        {
            // Maybe subdivide further

            // This is for robustness reasons, since the line intersection
            // method below gets instable if the curve gets closer to a
            // straight line. If the given cubic bezier does not deviate by
            // more than d/4 from a straight line, either:
            //  - take the line (that's what we do here)
            //  - express the line by a quadratic bezier    

            // Perform bezier flatness test (lecture notes from R. Schaback,
            // Mathematics of Computer-Aided Design, Uni Goettingen, 2000)
            //
            // ||P(t) - L(t)|| <= max     ||b_j - b_0 - j/n(b_n - b_0)||
            //                    0<=j<=n
            //
            // What is calculated here is an upper bound to the distance from
            // a line through b_0 and b_3 (P1 and P4 in our notation) and the
            // curve. We can drop 0 and n from the running indices, since the
            // argument of max becomes zero for those cases.
            const double fJ1x( P2x - P1x - 1.0/3.0*(P4x - P1x) );
            const double fJ1y( P2y - P1y - 1.0/3.0*(P4y - P1y) );
            const double fJ2x( P3x - P1x - 2.0/3.0*(P4x - P1x) );
            const double fJ2y( P3y - P1y - 2.0/3.0*(P4y - P1y) );

            // stop if distance from line is guaranteed to be bounded by d/4
            if( ::std::max( fJ1x*fJ1x + fJ1y*fJ1y, 
                            fJ2x*fJ2x + fJ2y*fJ2y) < d2/16.0 )
            {
                // do not subdivide further, add straight line instead
                Impl_addStraightLine( rBits, rLastPoint, P4x, P4y);
            }
            else
            {
                // deCasteljau bezier arc, split at t=0.5
                // Foley/vanDam, p. 508
                const double L1x( P1x ), 		   	 L1y( P1y );
                const double L2x( (P1x + P2x)*0.5 ), L2y( (P1y + P2y)*0.5 );
                const double Hx ( (P2x + P3x)*0.5 ), Hy ( (P2y + P3y)*0.5 );
                const double L3x( (L2x + Hx)*0.5 ),  L3y( (L2y + Hy)*0.5 );
                const double R4x( P4x ), 		   	 R4y( P4y );
                const double R3x( (P3x + P4x)*0.5 ), R3y( (P3y + P4y)*0.5 );
                const double R2x( (Hx + R3x)*0.5 ),  R2y( (Hy + R3y)*0.5 );
                const double R1x( (L3x + R2x)*0.5 ), R1y( (L3y + R2y)*0.5 );
                const double L4x( R1x ), 		     L4y( R1y );

                // subdivide further
                Impl_quadBezierApprox(rBits, rLastPoint, d2, L1x, L1y, L2x, L2y, L3x, L3y, L4x, L4y);
                Impl_quadBezierApprox(rBits, rLastPoint, d2, R1x, R1y, R2x, R2y, R3x, R3y, R4x, R4y);
            }
        }
    }
}

/////////////////////////////////////////////////////////////////////////

// TODO: Why do I need this?

extern "C"
{

int ZEXPORT compress2 ( Bytef * dest, uLongf * destLen, const Bytef * source, uLong sourceLen, int level)
{
    z_stream stream;
    int err;

    stream.next_in = (Bytef*)source;
    stream.avail_in = (uInt)sourceLen;
#ifdef MAXSEG_64K
    /* Check for source > 64K on 16-bit machine: */
    if ((uLong)stream.avail_in != sourceLen) return Z_BUF_ERROR;
#endif
    stream.next_out = dest;
    stream.avail_out = (uInt)*destLen;
    if ((uLong)stream.avail_out != *destLen) return Z_BUF_ERROR;

    stream.zalloc = (alloc_func)0;
    stream.zfree = (free_func)0;
    stream.opaque = (voidpf)0;

    err = deflateInit(&stream, level);
    if (err != Z_OK) return err;

    err = deflate(&stream, Z_FINISH);
    if (err != Z_STREAM_END) {
        deflateEnd(&stream);
        return err == Z_OK ? Z_BUF_ERROR : err;
    }
    *destLen = stream.total_out;

    err = deflateEnd(&stream);
    return err;
}

}
