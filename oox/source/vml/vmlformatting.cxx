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

#include "oox/vml/vmlformatting.hxx"

#include <rtl/strbuf.hxx>
#include "tokens.hxx"
#include "oox/drawingml/color.hxx"
#include "oox/drawingml/drawingmltypes.hxx"
#include "oox/drawingml/fillproperties.hxx"
#include "oox/drawingml/lineproperties.hxx"
#include "oox/helper/graphichelper.hxx"
#include "oox/helper/propertymap.hxx"
#include "oox/token/tokenmap.hxx"

namespace oox {
namespace vml {

// ============================================================================

using namespace ::com::sun::star::geometry;

using ::oox::drawingml::Color;
using ::oox::drawingml::FillProperties;
using ::oox::drawingml::LineArrowProperties;
using ::oox::drawingml::LineProperties;
using ::rtl::OStringBuffer;
using ::rtl::OUString;

// ============================================================================

namespace {

bool lclExtractDouble( double& orfValue, sal_Int32& ornEndPos, const OUString& rValue )
{
    // extract the double value and find start position of unit characters
    rtl_math_ConversionStatus eConvStatus = rtl_math_ConversionStatus_Ok;
    orfValue = ::rtl::math::stringToDouble( rValue, '.', '\0', &eConvStatus, &ornEndPos );
    return eConvStatus == rtl_math_ConversionStatus_Ok;
}

} // namespace

// ----------------------------------------------------------------------------

/*static*/ bool ConversionHelper::separatePair( OUString& orValue1, OUString& orValue2,
        const OUString& rValue, sal_Unicode cSep )
{
    sal_Int32 nSepPos = rValue.indexOf( cSep );
    if( nSepPos >= 0 )
    {
        orValue1 = rValue.copy( 0, nSepPos ).trim();
        orValue2 = rValue.copy( nSepPos + 1 ).trim();
    }
    else
    {
        orValue1 = rValue.trim();
    }
    return (orValue1.getLength() > 0) && (orValue2.getLength() > 0);
}

/*static*/ bool ConversionHelper::decodeBool( const OUString& rValue )
{
    // anything else than 't' or 'true' is considered to be false, as specified
    return ((rValue.getLength() == 1) && (rValue[ 0 ] == 't')) || (rValue == CREATE_OUSTRING( "true" ));
}

/*static*/ double ConversionHelper::decodePercent( const OUString& rValue, double fDefValue )
{
    if( rValue.getLength() == 0 )
        return fDefValue;

    double fValue = 0.0;
    sal_Int32 nEndPos = 0;
    if( !lclExtractDouble( fValue, nEndPos, rValue ) )
        return fDefValue;

    if( nEndPos == rValue.getLength() )
        return fValue;

    if( (nEndPos + 1 == rValue.getLength()) && (rValue[ nEndPos ] == '%') )
        return fValue / 100.0;

    OSL_ENSURE( false, "ConversionHelper::decodePercent - unknown measure unit" );
    return fDefValue;
}

/*static*/ sal_Int32 ConversionHelper::decodeMeasureToEmu( const GraphicHelper& rGraphicHelper,
        const OUString& rValue, sal_Int32 nRefValue, bool bPixelX, bool bDefaultAsPixel )
{
    // default for missing values is 0
    if( rValue.getLength() == 0 )
        return 0;

    // TODO: according to spec, value may contain "auto"
    if( rValue.equalsAscii( "auto" ) )
    {
        OSL_ENSURE( false, "ConversionHelper::decodeMeasureToEmu - special value 'auto' must be handled by caller" );
        return nRefValue;
    }

    // extract the double value and find start position of unit characters
    double fValue = 0.0;
    sal_Int32 nEndPos = 0;
    if( !lclExtractDouble( fValue, nEndPos, rValue ) || (fValue == 0.0) )
        return 0;

    // process trailing unit, convert to EMU
    static const OUString saPx = CREATE_OUSTRING( "px" );
    OUString aUnit;
    if( (0 < nEndPos) && (nEndPos < rValue.getLength()) )
        aUnit = rValue.copy( nEndPos );
    else if( bDefaultAsPixel )
        aUnit = saPx;
    // else default is EMU

    if( aUnit.getLength() == 2 )
    {
        sal_Unicode cChar1 = aUnit[ 0 ];
        sal_Unicode cChar2 = aUnit[ 1 ];
        if( (cChar1 == 'i') && (cChar2 == 'n') )        // 1 inch = 914,400 EMU
            fValue *= 914400.0;
        else if( (cChar1 == 'c') && (cChar2 == 'm') )   // 1 cm = 360,000 EMU
            fValue *= 360000.0;
        else if( (cChar1 == 'm') && (cChar2 == 'm') )   // 1 mm = 36,000 EMU
            fValue *= 36000.0;
        else if( (cChar1 == 'p') && (cChar2 == 't') )   // 1 point = 1/72 inch = 12,700 MEU
            fValue *= 12700.0;
        else if( (cChar1 == 'p') && (cChar2 == 'c') )   // 1 pica = 1/6 inch = 152,400 EMU
            fValue *= 152400.0;
        else if( (cChar1 == 'p') && (cChar2 == 'x') )   // 1 pixel, dependent on output device, factor 360 to convert 1/100mm to EMU
            fValue = bPixelX ?
                rGraphicHelper.convertScreenPixelXToHmm( 360.0 * fValue ) :
                rGraphicHelper.convertScreenPixelYToHmm( 360.0 * fValue );
    }
    else if( (aUnit.getLength() == 1) && (aUnit[ 0 ] == '%') )
    {
        fValue *= nRefValue / 100.0;
    }
    else if( bDefaultAsPixel || (aUnit.getLength() > 0) )   // default as EMU and no unit -> do nothing
    {
        OSL_ENSURE( false, "ConversionHelper::decodeMeasureToEmu - unknown measure unit" );
        fValue = nRefValue;
    }
    return static_cast< sal_Int32 >( fValue + 0.5 );
}

/*static*/ sal_Int32 ConversionHelper::decodeMeasureToHmm( const GraphicHelper& rGraphicHelper,
        const OUString& rValue, sal_Int32 nRefValue, bool bPixelX, bool bDefaultAsPixel )
{
    return (decodeMeasureToEmu( rGraphicHelper, rValue, nRefValue, bPixelX, bDefaultAsPixel ) + 180) / 360;
}

// ============================================================================

namespace {

/** Converts a VML color attribute to a DrawingML color.

    @param orDmlColor  (out-parameter) The destination DrawingML color.

    @param roVmlColor  The VML string representation of the color. If existing,
        this can be a 6-digit hexadecimal RGB value with leading '#' character,
        a predefined color name (e.g. 'black', 'red', etc.), the index into an
        application defined color palette in brackets with leading color name
        (e.g. 'red [9]' or 'windowColor [64]'), or a color modifier used in
        one-color gradients (e.g. 'fill darken(128)' or 'fill lighten(0)'.

    @param roVmlOpacity  The opacity of the color. If existing, this should be
        a floating-point value in the range [0.0;1.0].

    @param nDefaultRgb  Deafult RGB color used if the parameter roVmlColor is
        empty.

    @param nPrimaryRgb  If set to something else than API_RGB_TRANSPARENT,
        specifies the color to be used to resolve the color modifiers used in
        one-color gradients.
  */
void lclGetColor( Color& orDmlColor, const GraphicHelper& rGraphicHelper,
        const OptValue< OUString >& roVmlColor, const OptValue< double >& roVmlOpacity,
        sal_Int32 nDefaultRgb, sal_Int32 nPrimaryRgb = API_RGB_TRANSPARENT )
{
    // convert opacity
    const sal_Int32 DML_FULL_OPAQUE = ::oox::drawingml::MAX_PERCENT;
    double fOpacity = roVmlOpacity.get( 1.0 );
    sal_Int32 nOpacity = getLimitedValue< sal_Int32, double >( fOpacity * DML_FULL_OPAQUE, 0, DML_FULL_OPAQUE );
    if( nOpacity < DML_FULL_OPAQUE )
        orDmlColor.addTransformation( XML_alpha, nOpacity );

    // color attribute not present - set passed default color
    if( !roVmlColor.has() )
    {
        orDmlColor.setSrgbClr( nDefaultRgb );
        return;
    }

    // separate leading color name or RGB value from following palette index
    OUString aColorName, aColorIndex;
    ConversionHelper::separatePair( aColorName, aColorIndex, roVmlColor.get(), ' ' );

    // RGB colors in the format '#RRGGBB'
    if( (aColorName.getLength() == 7) && (aColorName[ 0 ] == '#') )
    {
        orDmlColor.setSrgbClr( aColorName.copy( 1 ).toInt32( 16 ) );
        return;
    }

    // RGB colors in the format '#RGB'
    if( (aColorName.getLength() == 4) && (aColorName[ 0 ] == '#') )
    {
        sal_Int32 nR = aColorName.copy( 1, 1 ).toInt32( 16 ) * 0x11;
        sal_Int32 nG = aColorName.copy( 2, 1 ).toInt32( 16 ) * 0x11;
        sal_Int32 nB = aColorName.copy( 3, 1 ).toInt32( 16 ) * 0x11;
        orDmlColor.setSrgbClr( (nR << 16) | (nG << 8) | nB );
        return;
    }

    /*  Predefined color names or system color names (resolve to RGB to detect
        valid color name). */
    sal_Int32 nColorToken = StaticTokenMap::get().getTokenFromUnicode( aColorName );
    sal_Int32 nRgbValue = Color::getVmlPresetColor( nColorToken, API_RGB_TRANSPARENT );
    if( nRgbValue == API_RGB_TRANSPARENT )
        nRgbValue = rGraphicHelper.getSystemColor( nColorToken, API_RGB_TRANSPARENT );
    if( nRgbValue != API_RGB_TRANSPARENT )
    {
        orDmlColor.setSrgbClr( nRgbValue );
        return;
    }

    // try palette colors enclosed in brackets
    if( (aColorIndex.getLength() >= 3) && (aColorIndex[ 0 ] == '[') && (aColorIndex[ aColorIndex.getLength() - 1 ] == ']') )
    {
        orDmlColor.setPaletteClr( aColorIndex.copy( 1, aColorIndex.getLength() - 2 ).toInt32() );
        return;
    }

    // try fill gradient modificator 'fill <modifier>(<amount>)'
    if( (nPrimaryRgb != API_RGB_TRANSPARENT) && (nColorToken == XML_fill) )
    {
        sal_Int32 nOpenParen = aColorIndex.indexOf( '(' );
        sal_Int32 nCloseParen = aColorIndex.indexOf( ')' );
        if( (2 <= nOpenParen) && (nOpenParen + 1 < nCloseParen) && (nCloseParen + 1 == aColorIndex.getLength()) )
        {
            sal_Int32 nModToken = XML_TOKEN_INVALID;
            switch( StaticTokenMap::get().getTokenFromUnicode( aColorIndex.copy( 0, nOpenParen ) ) )
            {
                case XML_darken:    nModToken = XML_shade;
                case XML_lighten:   nModToken = XML_tint;
            }
            sal_Int32 nValue = aColorIndex.copy( nOpenParen + 1, nCloseParen - nOpenParen - 1 ).toInt32();
            if( (nModToken != XML_TOKEN_INVALID) && (0 <= nValue) && (nValue < 255) )
            {
                /*  Simulate this modifier color by a color with related transformation.
                    The modifier amount has to be converted from the range [0;255] to
                    percentage [0;100000] used by DrawingML. */
                orDmlColor.setSrgbClr( nPrimaryRgb );
                orDmlColor.addTransformation( nModToken, static_cast< sal_Int32 >( nValue * ::oox::drawingml::MAX_PERCENT / 255 ) );
                return;
            }
        }
    }

    OSL_ENSURE( false, OStringBuffer( "lclGetColor - invalid VML color name '" ).
        append( OUStringToOString( roVmlColor.get(), RTL_TEXTENCODING_ASCII_US ) ).append( '\'' ).getStr() );
    orDmlColor.setSrgbClr( nDefaultRgb );
}

sal_Int32 lclGetEmu( const GraphicHelper& rGraphicHelper, const OptValue< OUString >& roValue, sal_Int32 nDefValue )
{
    return roValue.has() ? ConversionHelper::decodeMeasureToEmu( rGraphicHelper, roValue.get(), 0, false, false ) : nDefValue;
}

void lclGetDmlLineDash( OptValue< sal_Int32 >& oroPresetDash, LineProperties::DashStopVector& orCustomDash, const OptValue< OUString >& roDashStyle )
{
    if( roDashStyle.has() )
    {
        const OUString& rDashStyle = roDashStyle.get();
        switch( StaticTokenMap::get().getTokenFromUnicode( rDashStyle ) )
        {
            case XML_solid:             oroPresetDash = XML_solid;          return;
            case XML_shortdot:          oroPresetDash = XML_sysDot;         return;
            case XML_shortdash:         oroPresetDash = XML_sysDash;        return;
            case XML_shortdashdot:      oroPresetDash = XML_sysDashDot;     return;
            case XML_shortdashdotdot:   oroPresetDash = XML_sysDashDotDot;  return;
            case XML_dot:               oroPresetDash = XML_dot;            return;
            case XML_dash:              oroPresetDash = XML_dash;           return;
            case XML_dashdot:           oroPresetDash = XML_dashDot;        return;
            case XML_longdash:          oroPresetDash = XML_lgDash;         return;
            case XML_longdashdot:       oroPresetDash = XML_lgDashDot;      return;
            case XML_longdashdotdot:    oroPresetDash = XML_lgDashDotDot;   return;

            // try to convert user-defined dash style
            default:
            {
                ::std::vector< sal_Int32 > aValues;
                sal_Int32 nIndex = 0;
                while( nIndex >= 0 )
                    aValues.push_back( rDashStyle.getToken( 0, ' ', nIndex ).toInt32() );
                size_t nPairs = aValues.size() / 2; // ignore last value if size is odd
                for( size_t nPairIdx = 0; nPairIdx < nPairs; ++nPairIdx )
                    orCustomDash.push_back( LineProperties::DashStop( aValues[ 2 * nPairIdx ], aValues[ 2 * nPairIdx + 1 ] ) );
            }
        }
    }
}

sal_Int32 lclGetDmlArrowType( const OptValue< sal_Int32 >& roArrowType )
{
    if( roArrowType.has() ) switch( roArrowType.get() )
    {
        case XML_none:      return XML_none;
        case XML_block:     return XML_triangle;
        case XML_classic:   return XML_stealth;
        case XML_diamond:   return XML_diamond;
        case XML_oval:      return XML_oval;
        case XML_open:      return XML_arrow;
    }
    return XML_none;
}

sal_Int32 lclGetDmlArrowWidth( const OptValue< sal_Int32 >& roArrowWidth )
{
    if( roArrowWidth.has() ) switch( roArrowWidth.get() )
    {
        case XML_narrow:    return XML_sm;
        case XML_medium:    return XML_med;
        case XML_wide:      return XML_lg;
    }
    return XML_med;
}

sal_Int32 lclGetDmlArrowLength( const OptValue< sal_Int32 >& roArrowLength )
{
    if( roArrowLength.has() ) switch( roArrowLength.get() )
    {
        case XML_short:     return XML_sm;
        case XML_medium:    return XML_med;
        case XML_long:      return XML_lg;
    }
    return XML_med;
}

void lclConvertArrow( LineArrowProperties& orArrowProp, const StrokeArrowModel& rStrokeArrow )
{
    orArrowProp.moArrowType = lclGetDmlArrowType( rStrokeArrow.moArrowType );
    orArrowProp.moArrowWidth = lclGetDmlArrowWidth( rStrokeArrow.moArrowWidth );
    orArrowProp.moArrowLength = lclGetDmlArrowLength( rStrokeArrow.moArrowLength );
}

sal_Int32 lclGetDmlLineCompound( const OptValue< sal_Int32 >& roLineStyle )
{
    if( roLineStyle.has() ) switch( roLineStyle.get() )
    {
        case XML_single:            return XML_sng;
        case XML_thinThin:          return XML_dbl;
        case XML_thinThick:         return XML_thinThick;
        case XML_thickThin:         return XML_thickThin;
        case XML_thickBetweenThin:  return XML_tri;
    }
    return XML_sng;
}

sal_Int32 lclGetDmlLineCap( const OptValue< sal_Int32 >& roEndCap )
{
    if( roEndCap.has() ) switch( roEndCap.get() )
    {
        case XML_flat:      return XML_flat;
        case XML_square:    return XML_sq;
        case XML_round:     return XML_rnd;
    }
    return XML_flat;    // different defaults in VML (flat) and DrawingML (square)
}

sal_Int32 lclGetDmlLineJoint( const OptValue< sal_Int32 >& roJoinStyle )
{
    if( roJoinStyle.has() ) switch( roJoinStyle.get() )
    {
        case XML_round: return XML_round;
        case XML_bevel: return XML_bevel;
        case XML_miter: return XML_miter;
    }
    return XML_round;
}

} // namespace

// ============================================================================

void StrokeArrowModel::assignUsed( const StrokeArrowModel& rSource )
{
    moArrowType.assignIfUsed( rSource.moArrowType );
    moArrowWidth.assignIfUsed( rSource.moArrowWidth );
    moArrowLength.assignIfUsed( rSource.moArrowLength );
}

// ============================================================================

void StrokeModel::assignUsed( const StrokeModel& rSource )
{
    moStroked.assignIfUsed( rSource.moStroked );
    maStartArrow.assignUsed( rSource.maStartArrow );
    maEndArrow.assignUsed( rSource.maEndArrow );
    moColor.assignIfUsed( rSource.moColor );
    moOpacity.assignIfUsed( rSource.moOpacity );
    moWeight.assignIfUsed( rSource.moWeight );
    moDashStyle.assignIfUsed( rSource.moDashStyle );
    moLineStyle.assignIfUsed( rSource.moLineStyle );
    moEndCap.assignIfUsed( rSource.moEndCap );
    moJoinStyle.assignIfUsed( rSource.moJoinStyle );
}

void StrokeModel::pushToPropMap( PropertyMap& rPropMap,
        ModelObjectHelper& rModelObjectHelper, const GraphicHelper& rGraphicHelper ) const
{
    /*  Convert VML line formatting to DrawingML line formatting and let the
        DrawingML code do the hard work. */
    LineProperties aLineProps;

    if( moStroked.get( true ) )
    {
        aLineProps.maLineFill.moFillType = XML_solidFill;
        lclConvertArrow( aLineProps.maStartArrow, maStartArrow );
        lclConvertArrow( aLineProps.maEndArrow, maEndArrow );
        lclGetColor( aLineProps.maLineFill.maFillColor, rGraphicHelper, moColor, moOpacity, API_RGB_BLACK );
        aLineProps.moLineWidth = lclGetEmu( rGraphicHelper, moWeight, 1 );
        lclGetDmlLineDash( aLineProps.moPresetDash, aLineProps.maCustomDash, moDashStyle );
        aLineProps.moLineCompound = lclGetDmlLineCompound( moLineStyle );
        aLineProps.moLineCap = lclGetDmlLineCap( moEndCap );
        aLineProps.moLineJoint = lclGetDmlLineJoint( moJoinStyle );
    }
    else
    {
        aLineProps.maLineFill.moFillType = XML_noFill;
    }

    aLineProps.pushToPropMap( rPropMap, rModelObjectHelper, rGraphicHelper );
}

// ============================================================================

void FillModel::assignUsed( const FillModel& rSource )
{
    moFilled.assignIfUsed( rSource.moFilled );
    moColor.assignIfUsed( rSource.moColor );
    moOpacity.assignIfUsed( rSource.moOpacity );
    moColor2.assignIfUsed( rSource.moColor2 );
    moOpacity2.assignIfUsed( rSource.moOpacity2 );
    moType.assignIfUsed( rSource.moType );
    moAngle.assignIfUsed( rSource.moAngle );
    moFocus.assignIfUsed( rSource.moFocus );
    moFocusPos.assignIfUsed( rSource.moFocusPos );
    moFocusSize.assignIfUsed( rSource.moFocusSize );
    moBitmapPath.assignIfUsed( rSource.moBitmapPath );
    moRotate.assignIfUsed( rSource.moRotate );
}

void FillModel::pushToPropMap( PropertyMap& rPropMap,
        ModelObjectHelper& rModelObjectHelper, const GraphicHelper& rGraphicHelper ) const
{
    /*  Convert VML fill formatting to DrawingML fill formatting and let the
        DrawingML code do the hard work. */
    FillProperties aFillProps;

    if( moFilled.get( true ) )
    {
        sal_Int32 nFillType = moType.get( XML_solid );
        switch( nFillType )
        {
            case XML_gradient:
            case XML_gradientRadial:
            {
                aFillProps.moFillType = XML_gradFill;
                aFillProps.maGradientProps.moRotateWithShape = moRotate.get( false );
                double fFocus = moFocus.get( 0.0 );

                // prepare colors
                Color aColor1, aColor2;
                lclGetColor( aColor1, rGraphicHelper, moColor, moOpacity, API_RGB_WHITE );
                lclGetColor( aColor2, rGraphicHelper, moColor2, moOpacity2, API_RGB_WHITE, aColor1.getColor( rGraphicHelper ) );

                // type XML_gradient is linear or axial gradient
                if( nFillType == XML_gradient )
                {
                    // normalize angle to range [0;360) degrees
                    sal_Int32 nVmlAngle = getIntervalValue< sal_Int32, sal_Int32 >( moAngle.get( 0 ), 0, 360 );

                    // focus of -50% or 50% is axial gradient
                    if( ((-0.75 <= fFocus) && (fFocus <= -0.25)) || ((0.25 <= fFocus) && (fFocus <= 0.75)) )
                    {
                        /*  According to spec, focus of 50% is outer-to-inner,
                            and -50% is inner-to-outer (color to color2).
                            BUT: For angles >= 180 deg., the behaviour is
                            reversed... that's not spec'ed of course. So,
                            [0;180) deg. and 50%, or [180;360) deg. and -50% is
                            outer-to-inner in fact. */
                        bool bOuterToInner = (fFocus > 0.0) == (nVmlAngle < 180);
                        // simulate axial gradient by 3-step DrawingML gradient
                        const Color& rOuterColor = bOuterToInner ? aColor1 : aColor2;
                        const Color& rInnerColor = bOuterToInner ? aColor2 : aColor1;
                        aFillProps.maGradientProps.maGradientStops[ 0.0 ] = aFillProps.maGradientProps.maGradientStops[ 1.0 ] = rOuterColor;
                        aFillProps.maGradientProps.maGradientStops[ 0.5 ] = rInnerColor;
                    }
                    else    // focus of -100%, 0%, and 100% is linear gradient
                    {
                        /*  According to spec, focus of -100% or 100% swaps the
                            start and stop colors, effectively reversing the
                            gradient. BUT: For angles >= 180 deg., the
                            behaviour is reversed. This means that in this case
                            a focus of 0% swaps the gradient. */
                        if( ((fFocus < -0.75) || (fFocus > 0.75)) == (nVmlAngle < 180) )
                            (nVmlAngle += 180) %= 360;
                        // set the start and stop colors
                        aFillProps.maGradientProps.maGradientStops[ 0.0 ] = aColor1;
                        aFillProps.maGradientProps.maGradientStops[ 1.0 ] = aColor2;
                    }

                    // VML counts counterclockwise from bottom, DrawingML clockwise from left
                    sal_Int32 nDmlAngle = (630 - nVmlAngle) % 360;
                    aFillProps.maGradientProps.moShadeAngle = nDmlAngle * ::oox::drawingml::PER_DEGREE;
                }
                else    // XML_gradientRadial is rectangular gradient
                {
                    aFillProps.maGradientProps.moGradientPath = XML_rect;
                    // convert VML focus position and size to DrawingML fill-to-rect
                    DoublePair aFocusPos = moFocusPos.get( DoublePair( 0.0, 0.0 ) );
                    DoublePair aFocusSize = moFocusSize.get( DoublePair( 0.0, 0.0 ) );
                    double fLeft   = getLimitedValue< double, double >( aFocusPos.first, 0.0, 1.0 );
                    double fTop    = getLimitedValue< double, double >( aFocusPos.second, 0.0, 1.0 );
                    double fRight  = getLimitedValue< double, double >( fLeft + aFocusSize.first, fLeft, 1.0 );
                    double fBottom = getLimitedValue< double, double >( fTop + aFocusSize.second, fTop, 1.0 );
                    aFillProps.maGradientProps.moFillToRect = IntegerRectangle2D(
                        static_cast< sal_Int32 >( fLeft * ::oox::drawingml::MAX_PERCENT ),
                        static_cast< sal_Int32 >( fTop * ::oox::drawingml::MAX_PERCENT ),
                        static_cast< sal_Int32 >( (1.0 - fRight) * ::oox::drawingml::MAX_PERCENT ),
                        static_cast< sal_Int32 >( (1.0 - fBottom) * ::oox::drawingml::MAX_PERCENT ) );

                    // set the start and stop colors (focus of 0% means outer-to-inner)
                    bool bOuterToInner = (-0.5 <= fFocus) && (fFocus <= 0.5);
                    aFillProps.maGradientProps.maGradientStops[ 0.0 ] = bOuterToInner ? aColor2 : aColor1;
                    aFillProps.maGradientProps.maGradientStops[ 1.0 ] = bOuterToInner ? aColor1 : aColor2;
                }
            }
            break;

            case XML_pattern:
            case XML_tile:
            case XML_frame:
            {
                if( moBitmapPath.has() && moBitmapPath.get().getLength() > 0 )
                {
                    aFillProps.maBlipProps.mxGraphic = rGraphicHelper.importEmbeddedGraphic( moBitmapPath.get() );
                    if( aFillProps.maBlipProps.mxGraphic.is() )
                    {
                        aFillProps.moFillType = XML_blipFill;
                        aFillProps.maBlipProps.moBitmapMode = (nFillType == XML_frame) ? XML_stretch : XML_tile;
                        break;  // do not break if bitmap is missing, but run to XML_solid instead
                    }
                }
            }
            // run-through to XML_solid in case of missing bitmap path intended!
            
            case XML_solid:
            default:
            {
                aFillProps.moFillType = XML_solidFill;
                // fill color (default is white)
                lclGetColor( aFillProps.maFillColor, rGraphicHelper, moColor, moOpacity, API_RGB_WHITE );
            }
        }
    }
    else
    {
        aFillProps.moFillType = XML_noFill;
    }

    aFillProps.pushToPropMap( rPropMap, rModelObjectHelper, rGraphicHelper );
}

// ============================================================================

} // namespace vml
} // namespace oox
