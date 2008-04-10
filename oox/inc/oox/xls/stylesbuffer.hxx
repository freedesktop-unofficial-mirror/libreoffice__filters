/*************************************************************************
 *
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER.
 * 
 * Copyright 2008 by Sun Microsystems, Inc.
 *
 * OpenOffice.org - a multi-platform office productivity suite
 *
 * $RCSfile: stylesbuffer.hxx,v $
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

#ifndef OOX_XLS_STYLESBUFFER_HXX
#define OOX_XLS_STYLESBUFFER_HXX

#include "oox/helper/containerhelper.hxx"
#include "oox/xls/stylespropertyhelper.hxx"
#include "oox/xls/numberformatsbuffer.hxx"

namespace com { namespace sun { namespace star {
    namespace awt { struct FontDescrtiptor; }
} } }

#define OOX_XLS_USE_DEFAULT_STYLE 0

namespace oox {
namespace xls {

// ============================================================================

const sal_Int32 OOX_COLOR_WINDOWTEXT3       = 24;       /// System window text color (BIFF3-BIFF4).
const sal_Int32 OOX_COLOR_WINDOWBACK3       = 25;       /// System window background color (BIFF3-BIFF4).
const sal_Int32 OOX_COLOR_WINDOWTEXT        = 64;       /// System window text color (BIFF5+).
const sal_Int32 OOX_COLOR_WINDOWBACK        = 65;       /// System window background color (BIFF5+).
const sal_Int32 OOX_COLOR_BUTTONBACK        = 67;       /// System button background color (face color).
const sal_Int32 OOX_COLOR_CHWINDOWTEXT      = 77;       /// System window text color (BIFF8 charts).
const sal_Int32 OOX_COLOR_CHWINDOWBACK      = 78;       /// System window background color (BIFF8 charts).
const sal_Int32 OOX_COLOR_CHBORDERAUTO      = 79;       /// Automatic frame border (BIFF8 charts).
const sal_Int32 OOX_COLOR_NOTEBACK          = 80;       /// Note background color.
const sal_Int32 OOX_COLOR_NOTETEXT          = 81;       /// Note text color.
const sal_Int32 OOX_COLOR_FONTAUTO          = 0x7FFF;   /// Font auto color (system window text color).

// ============================================================================

/** Generic helper struct for a style color. */
struct OoxColor
{
    double              mfTint;             /// Color tint (darken/lighten).
    sal_Int32           mnType;             /// Color type (XML token identifier).
    sal_Int32           mnValue;            /// RGB color value or palette index.

    explicit            OoxColor();
    explicit            OoxColor( sal_Int32 nType, sal_Int32 nValue, double fTint = 0.0 );

    /** Returns true, if the color is set to automatic. */
    bool                isAuto() const;

    /** Sets the color to the passed values. */
    void                set( sal_Int32 nType, sal_Int32 nValue, double fTint = 0.0 );

    /** Imports the color from the passed attribute list. */
    void                importColor( const AttributeList& rAttribs );

    /** Imports a 64-bit color from the passed binary stream. */
    void                importColor( RecordInputStream& rStrm );
    /** Imports a 32-bit palette color identifier from the passed OOBIN stream. */
    void                importColorId( RecordInputStream& rStrm );
    /** Imports a 32-bit RGBA color value from the passed OOBIN stream. */
    void                importColorRgb( RecordInputStream& rStrm );

    /** Imports an 8-bit or 16-bit palette color identifier from the passed BIFF stream. */
    void                importColorId( BiffInputStream& rStrm, bool b16Bit = true );
    /** Imports a 32-bit RGBA color value from the passed BIFF stream. */
    void                importColorRgb( BiffInputStream& rStrm );
};

// ----------------------------------------------------------------------------

RecordInputStream& operator>>( RecordInputStream& rStrm, OoxColor& orColor );

// ============================================================================

/** Stores all colors of the color palette. */
class ColorPalette : public WorkbookHelper
{
public:
    /** Constructs the color palette with predefined color values. */
    explicit            ColorPalette( const WorkbookHelper& rHelper );

    /** Appends a new color from the passed attributes. */
    void                importPaletteColor( const AttributeList& rAttribs );
    /** Appends a new color from the passed RGBCOLOR record. */
    void                importPaletteColor( RecordInputStream& rStrm );
    /** Imports the PALETTE record from the passed stream. */
    void                importPalette( BiffInputStream& rStrm );

    /** Rturns the RGB value of the color with the passed index. */
    sal_Int32           getColor( sal_Int32 nColorId ) const;

private:
    /** Appends the passed color. */
    void                appendColor( sal_Int32 nRGBValue );

private:
    ::std::vector< sal_Int32 > maColors;    /// List of RGB values.
    size_t              mnAppendIndex;      /// Index to append a new color.
    sal_Int32           mnWindowColor;      /// System window background color.
    sal_Int32           mnWinTextColor;     /// System window text color.
};

// ============================================================================

/** Contains all XML font attributes, e.g. from a font or rPr element. */
struct OoxFontData
{
    ::rtl::OUString     maName;             /// Font name.
    OoxColor            maColor;            /// Font color.
    sal_Int32           mnScheme;           /// Major/minor scheme font.
    sal_Int32           mnFamily;           /// Font family.
    sal_Int32           mnCharSet;          /// Windows font character set.
    double              mfHeight;           /// Font height in points.
    sal_Int32           mnUnderline;        /// Underline style.
    sal_Int32           mnEscapement;       /// Escapement style.
    bool                mbBold;             /// True = bold characters.
    bool                mbItalic;           /// True = italic characters.
    bool                mbStrikeout;        /// True = Strike out characters.
    bool                mbOutline;          /// True = outlined characters.
    bool                mbShadow;           /// True = shadowed chgaracters.

    explicit            OoxFontData();

    void                setBinScheme( sal_uInt8 nScheme );
    void                setBiffHeight( sal_uInt16 nHeight );
    void                setBiffWeight( sal_uInt16 nWeight );
    void                setBiffUnderline( sal_uInt16 nUnderline );
    void                setBiffEscapement( sal_uInt16 nEscapement );
};

// ============================================================================

class Font : public WorkbookHelper
{
public:
    explicit            Font( const WorkbookHelper& rHelper, bool bDxf );
    explicit            Font( const WorkbookHelper& rHelper, const OoxFontData& rFontData );

    /** Returns true, if the passed element represents a supported font context. */
    static bool         isSupportedContext( sal_Int32 nElement, sal_Int32 nParentContext );
    /** Sets font formatting attributes for the passed element. */
    void                importAttribs( sal_Int32 nElement, const AttributeList& rAttribs );

    /** Imports the FONT record from the passed stream. */
    void                importFont( RecordInputStream& rStrm );
    /** Imports the font name from a DXF record. */
    void                importDxfName( RecordInputStream& rStrm );
    /** Imports the font color from a DXF record. */
    void                importDxfColor( RecordInputStream& rStrm );
    /** Imports the font scheme from a DXF record. */
    void                importDxfScheme( RecordInputStream& rStrm );
    /** Imports the font height from a DXF record. */
    void                importDxfHeight( RecordInputStream& rStrm );
    /** Imports the font weight from a DXF record. */
    void                importDxfWeight( RecordInputStream& rStrm );
    /** Imports the font underline style from a DXF record. */
    void                importDxfUnderline( RecordInputStream& rStrm );
    /** Imports the font escapement style from a DXF record. */
    void                importDxfEscapement( RecordInputStream& rStrm );
    /** Imports a font style flag from a DXF record. */
    void                importDxfFlag( sal_Int32 nElement, RecordInputStream& rStrm );

    /** Imports the FONT record from the passed stream. */
    void                importFont( BiffInputStream& rStrm );
    /** Imports the FONTCOLOR record from the passed stream. */
    void                importFontColor( BiffInputStream& rStrm );
    /** Sets the font attributes from the font block of a CFRULE record. */
    void                importCfRule( BiffInputStream& rStrm );

    /** Returns the OOX font data structure. This function can be called before
        finalizeImport() has been called. */
    inline const OoxFontData& getFontData() const { return maOoxData; }
    /** Returns the text encoding for strings used with this font. This
        function can be called before finalizeImport() has been called. */
    rtl_TextEncoding    getFontEncoding() const;

    /** Final processing after import of all style settings. */
    void                finalizeImport();

    /** Returns an API font descriptor with own font information. */
    const ::com::sun::star::awt::FontDescriptor& getFontDescriptor() const;
    /** Returns true, if the font requires rich text formatting in Calc.
        @descr  Example: Font escapement is a cell attribute in Excel, but Calc
        needs an rich text cell for this attribute. */
    bool                needsRichTextFormat() const;

    /** Writes all font attributes to the passed property set. */
    void                writeToPropertySet(
                            PropertySet& rPropSet,
                            FontPropertyType ePropType ) const;

private:
    /** Reads and sets height and flags. */
    void                importFontData2( BiffInputStream& rStrm );
    /** Reads and sets weight, escapement, underline, family, charset (BIFF5+). */
    void                importFontData5( BiffInputStream& rStrm );

    /** Reads and sets a byte string as font name. */
    void                importFontName2( BiffInputStream& rStrm );
    /** Reads and sets a Unicode string as font name. */
    void                importFontName8( BiffInputStream& rStrm );

private:
    OoxFontData         maOoxData;
    ApiFontData         maApiData;
    ApiFontUsedFlags    maUsedFlags;
    bool                mbDxf;
};

typedef ::boost::shared_ptr< Font > FontRef;

// ============================================================================

/** Contains all XML cell alignment attributes, e.g. from an alignment element. */
struct OoxAlignmentData
{
    sal_Int32           mnHorAlign;         /// Horizontal alignment.
    sal_Int32           mnVerAlign;         /// Vertical alignment.
    sal_Int32           mnTextDir;          /// CTL text direction.
    sal_Int32           mnRotation;         /// Text rotation angle.
    sal_Int32           mnIndent;           /// Indentation.
    bool                mbWrapText;         /// True = multi-line text.
    bool                mbShrink;           /// True = shrink to fit cell size.
    bool                mbJustLastLine;     /// True = justify last line in block text.

    explicit            OoxAlignmentData();

    /** Sets horizontal alignment from the passed OOBIN or BIFF data. */
    void                setBinHorAlign( sal_uInt8 nHorAlign );
    /** Sets vertical alignment from the passed OOBIN or BIFF data. */
    void                setBinVerAlign( sal_uInt8 nVerAlign );
    /** Sets rotation from the passed OOBIN or BIFF text orientation. */
    void                setBinTextOrient( sal_uInt8 nTextOrient );
};

// ============================================================================

class Alignment : public WorkbookHelper
{
public:
    explicit            Alignment( const WorkbookHelper& rHelper );

    /** Sets all attributes from the alignment element. */
    void                importAlignment( const AttributeList& rAttribs );

    /** Sets the alignment attributes from the passed OOBIN XF record data. */
    void                setBinData( sal_uInt32 nFlags );
    /** Sets the alignment attributes from the passed BIFF2 XF record data. */
    void                setBiff2Data( sal_uInt8 nFlags );
    /** Sets the alignment attributes from the passed BIFF3 XF record data. */
    void                setBiff3Data( sal_uInt16 nAlign );
    /** Sets the alignment attributes from the passed BIFF4 XF record data. */
    void                setBiff4Data( sal_uInt16 nAlign );
    /** Sets the alignment attributes from the passed BIFF5 XF record data. */
    void                setBiff5Data( sal_uInt16 nAlign );
    /** Sets the alignment attributes from the passed BIFF8 XF record data. */
    void                setBiff8Data( sal_uInt16 nAlign, sal_uInt16 nMiscAttrib );

    /** Final processing after import of all style settings. */
    void                finalizeImport();

    /** Returns the OOX alignment data struct. */
    inline const OoxAlignmentData& getOoxData() const { return maOoxData; }
    /** Returns the converted API alignment data struct. */
    inline const ApiAlignmentData& getApiData() const { return maApiData; }

    /** Writes all alignment attributes to the passed property set. */
    void                writeToPropertySet( PropertySet& rPropSet ) const;

private:
    OoxAlignmentData    maOoxData;          /// Data from alignment element.
    ApiAlignmentData    maApiData;          /// Alignment data converted to API constants.
};

typedef ::boost::shared_ptr< Alignment > AlignmentRef;

// ============================================================================

/** Contains all XML cell protection attributes, e.g. from a protection element. */
struct OoxProtectionData
{
    bool                mbLocked;           /// True = locked against editing.
    bool                mbHidden;           /// True = formula is hidden.

    explicit            OoxProtectionData();
};

// ============================================================================

class Protection : public WorkbookHelper
{
public:
    explicit            Protection( const WorkbookHelper& rHelper );

    /** Sets all attributes from the protection element. */
    void                importProtection( const AttributeList& rAttribs );

    /** Sets the protection attributes from the passed OOBIN XF record data. */
    void                setBinData( sal_uInt32 nFlags );
    /** Sets the protection attributes from the passed BIFF2 XF record data. */
    void                setBiff2Data( sal_uInt8 nNumFmt );
    /** Sets the protection attributes from the passed BIFF3-BIFF8 XF record data. */
    void                setBiff3Data( sal_uInt16 nProt );

    /** Final processing after import of all style settings. */
    void                finalizeImport();

    /** Returns the OOX protection data struct. */
    inline const OoxProtectionData& getOoxData() const { return maOoxData; }
    /** Returns the converted API protection data struct. */
    inline const ApiProtectionData& getApiData() const { return maApiData; }

    /** Writes all protection attributes to the passed property set. */
    void                writeToPropertySet( PropertySet& rPropSet ) const;

private:
    OoxProtectionData   maOoxData;          /// Data from protection element.
    ApiProtectionData   maApiData;          /// Protection data converted to API constants.
};

typedef ::boost::shared_ptr< Protection > ProtectionRef;

// ============================================================================

/** Contains XML attributes of a single border line. */
struct OoxBorderLineData
{
    OoxColor            maColor;            /// Borderline color.
    sal_Int32           mnStyle;            /// Border line style.
    bool                mbUsed;             /// True = line format used.

    explicit            OoxBorderLineData( bool bDxf );

    /** Sets the passed OOBIN or BIFF line style. */
    void                setBiffStyle( sal_Int32 nLineStyle );
    /** Sets line style and line color from the passed BIFF data. */
    void                setBiffData( sal_uInt8 nLineStyle, sal_uInt16 nLineColor );
};

// ----------------------------------------------------------------------------

/** Contains XML attributes of a complete cell border. */
struct OoxBorderData
{
    OoxBorderLineData   maLeft;             /// Left line format.
    OoxBorderLineData   maRight;            /// Right line format.
    OoxBorderLineData   maTop;              /// Top line format.
    OoxBorderLineData   maBottom;           /// Bottom line format.
    OoxBorderLineData   maDiagonal;         /// Diagonal line format.
    bool                mbDiagTLtoBR;       /// True = top-left to bottom-right on.
    bool                mbDiagBLtoTR;       /// True = bottom-left to top-right on.

    explicit            OoxBorderData( bool bDxf );
};

// ============================================================================

class Border : public WorkbookHelper
{
public:
    explicit            Border( const WorkbookHelper& rHelper, bool bDxf );

    /** Returns true, if the passed element represents a supported border context. */
    static bool         isSupportedContext( sal_Int32 nElement, sal_Int32 nParentContext );
    /** Sets global border attributes from the border element. */
    void                importBorder( const AttributeList& rAttribs );
    /** Sets border attributes for the border line with the passed element identifier. */
    void                importStyle( sal_Int32 nElement, const AttributeList& rAttribs );
    /** Sets color attributes for the border line with the passed element identifier. */
    void                importColor( sal_Int32 nElement, const AttributeList& rAttribs );

    /** Imports the BORDER record from the passed stream. */
    void                importBorder( RecordInputStream& rStrm );
    /** Imports a boder from a DXF record from the passed stream. */
    void                importDxfBorder( sal_Int32 nElement, RecordInputStream& rStrm );

    /** Sets the border attributes from the passed BIFF2 XF record data. */
    void                setBiff2Data( sal_uInt8 nFlags );
    /** Sets the border attributes from the passed BIFF3/BIFF4 XF record data. */
    void                setBiff3Data( sal_uInt32 nBorder );
    /** Sets the border attributes from the passed BIFF5 XF record data. */
    void                setBiff5Data( sal_uInt32 nBorder, sal_uInt32 nArea );
    /** Sets the border attributes from the passed BIFF8 XF record data. */
    void                setBiff8Data( sal_uInt32 nBorder1, sal_uInt32 nBorder2 );
    /** Sets the border attributes from the border block of a CFRULE record. */
    void                importCfRule( BiffInputStream& rStrm, sal_uInt32 nFlags );

    /** Final processing after import of all style settings. */
    void                finalizeImport();

    /** Writes all border attributes to the passed property set. */
    void                writeToPropertySet( PropertySet& rPropSet ) const;

private:
    /** Returns the border line struct specified by the passed XML token identifier. */
    OoxBorderLineData*  getBorderLine( sal_Int32 nElement );

    /** Converts border line data to an API struct, returns true, if the line is marked as used. */
    bool                convertBorderLine(
                            ::com::sun::star::table::BorderLine& rBorderLine,
                            const OoxBorderLineData& rLineData );

private:
    OoxBorderData       maOoxData;
    ApiBorderData       maApiData;
    bool                mbDxf;
};

typedef ::boost::shared_ptr< Border > BorderRef;

// ============================================================================

/** Contains XML pattern fill attributes from the patternFill element. */
struct OoxPatternFillData
{
    OoxColor            maPatternColor;     /// Pattern foreground color.
    OoxColor            maFillColor;        /// Background fill color.
    sal_Int32           mnPattern;          /// Pattern identifier (e.g. solid).
    bool                mbPattColorUsed;    /// True = pattern foreground color used.
    bool                mbFillColorUsed;    /// True = background fill color used.
    bool                mbPatternUsed;      /// True = pattern used.

    explicit            OoxPatternFillData( bool bDxf );

    /** Sets the passed OOBIN or BIFF pattern identifier. */
    void                setBinPattern( sal_Int32 nPattern );
    /** Sets the pattern and pattern colors from the passed BIFF data. */
    void                setBiffData( sal_uInt16 nPatternColor, sal_uInt16 nFillColor, sal_uInt8 nPattern );
};

// ----------------------------------------------------------------------------

/** Contains XML gradient fill attributes from the gradientFill element. */
struct OoxGradientFillData
{
    typedef ::std::map< double, OoxColor > OoxColorMap;

    sal_Int32           mnType;             /// Gradient type, linear or path.
    double              mfAngle;            /// Rotation angle for type linear.
    double              mfLeft;             /// Left convergence for type path.
    double              mfRight;            /// Right convergence for type path.
    double              mfTop;              /// Top convergence for type path.
    double              mfBottom;           /// Bottom convergence for type path.
    OoxColorMap         maColors;           /// Gradient colors.

    explicit            OoxGradientFillData();

    /** Reads OOBIN gradient settings from a FILL or DXF record. */
    void                readGradient( RecordInputStream& rStrm );
    /** Reads OOBIN gradient stop settings from a FILL or DXF record. */
    void                readGradientStop( RecordInputStream& rStrm, bool bDxf );
};

// ============================================================================

/** Contains cell fill attributes, either a pattern fill or a gradient fill. */
class Fill : public WorkbookHelper
{
public:
    explicit            Fill( const WorkbookHelper& rHelper, bool bDxf );

    /** Returns true, if the passed element represents a supported fill context. */
    static bool         isSupportedContext( sal_Int32 nElement, sal_Int32 nParentContext );
    /** Sets attributes of a patternFill element. */
    void                importPatternFill( const AttributeList& rAttribs );
    /** Sets the pattern color from the fgColor element. */
    void                importFgColor( const AttributeList& rAttribs );
    /** Sets the background color from the bgColor element. */
    void                importBgColor( const AttributeList& rAttribs );
    /** Sets attributes of a gradientFill element. */
    void                importGradientFill( const AttributeList& rAttribs );
    /** Sets a color from the color element in a gradient fill. */
    void                importColor( const AttributeList& rAttribs, double fPosition );

    /** Imports the FILL record from the passed stream. */
    void                importFill( RecordInputStream& rStrm );
    /** Imports the fill pattern from a DXF record. */
    void                importDxfPattern( RecordInputStream& rStrm );
    /** Imports the pattern color from a DXF record. */
    void                importDxfFgColor( RecordInputStream& rStrm );
    /** Imports the background color from a DXF record. */
    void                importDxfBgColor( RecordInputStream& rStrm );
    /** Imports gradient settings from a DXF record. */
    void                importDxfGradient( RecordInputStream& rStrm );
    /** Imports gradient stop settings from a DXF record. */
    void                importDxfStop( RecordInputStream& rStrm );

    /** Sets the fill attributes from the passed BIFF2 XF record data. */
    void                setBiff2Data( sal_uInt8 nFlags );
    /** Sets the fill attributes from the passed BIFF3/BIFF4 XF record data. */
    void                setBiff3Data( sal_uInt16 nArea );
    /** Sets the fill attributes from the passed BIFF5 XF record data. */
    void                setBiff5Data( sal_uInt32 nArea );
    /** Sets the fill attributes from the passed BIFF8 XF record data. */
    void                setBiff8Data( sal_uInt32 nBorder2, sal_uInt16 nArea );
    /** Sets the fill attributes from the fill block of a CFRULE record. */
    void                importCfRule( BiffInputStream& rStrm, sal_uInt32 nFlags );

    /** Final processing after import of all style settings. */
    void                finalizeImport();

    /** Writes all fill attributes to the passed property set. */
    void                writeToPropertySet( PropertySet& rPropSet ) const;

private:
    typedef ::boost::shared_ptr< OoxPatternFillData >   OoxPatternRef;
    typedef ::boost::shared_ptr< OoxGradientFillData >  OoxGradientRef;

    OoxPatternRef       mxOoxPattData;
    OoxGradientRef      mxOoxGradData;
    ApiSolidFillData    maApiData;
    bool                mbDxf;
};

typedef ::boost::shared_ptr< Fill > FillRef;

// ============================================================================

/** Contains all data for a cell format or cell style. */
struct OoxXfData
{
    sal_Int32           mnStyleXfId;        /// Index to parent style XF.
    sal_Int32           mnFontId;           /// Index to font data list.
    sal_Int32           mnNumFmtId;         /// Index to number format list.
    sal_Int32           mnBorderId;         /// Index to list of cell borders.
    sal_Int32           mnFillId;           /// Index to list of cell areas.
    bool                mbCellXf;           /// True = cell XF, false = style XF.
    bool                mbFontUsed;         /// True = font index used.
    bool                mbNumFmtUsed;       /// True = number format used.
    bool                mbAlignUsed;        /// True = alignment used.
    bool                mbProtUsed;         /// True = cell protection used.
    bool                mbBorderUsed;       /// True = border data used.
    bool                mbAreaUsed;         /// True = area data used.

    explicit            OoxXfData();
};

// ============================================================================

/** Represents a cell format or a cell style (called XF, extended format).

    This class stores the type (cell/style), the index to the parent style (if
    it is a cell format) and all "attribute used" flags, which reflect the
    state of specific attribute groups (true = user has changed the attributes)
    and all formatting data.
 */
class Xf : public WorkbookHelper
{
public:
    explicit            Xf( const WorkbookHelper& rHelper );

    /** Sets all "attribute used" flags to the passed state. */
    void                setAllUsedFlags( bool bUsed );

    /** Sets all attributes from the xf element. */
    void                importXf( const AttributeList& rAttribs, bool bCellXf );
    /** Sets all attributes from the alignment element. */
    void                importAlignment( const AttributeList& rAttribs );
    /** Sets all attributes from the protection element. */
    void                importProtection( const AttributeList& rAttribs );

    /** Imports the XF record from the passed stream. */
    void                importXf( RecordInputStream& rStrm, bool bCellXf );

    /** Imports the XF record from the passed stream. */
    void                importXf( BiffInputStream& rStrm );

    /** Final processing after import of all style settings. */
    void                finalizeImport();

    /** Returns the referred font object. */
    FontRef             getFont() const;
    /** Returns the alignment data of this style. */
    inline const Alignment& getAlignment() const { return maAlignment; }
    /** Returns the cell protection data of this style. */
    inline const Protection& getProtection() const { return maProtection; }
    /** Returns true, if any "attribute used" flags are ste in this XF. */
    bool                hasAnyUsedFlags() const;

    /** Writes all formatting attributes to the passed property set. */
    void                writeToPropertySet( PropertySet& rPropSet ) const;

private:
    /** Sets 'attribute used' flags from the passed BIFF bit field. */
    void                setBiffUsedFlags( sal_uInt8 nUsedFlags );
    /** Updates own used flags from the passed cell style XF. */
    void                updateUsedFlags( const Xf& rStyleXf );

private:
    OoxXfData           maOoxData;          /// Data from cellXf or cellStyleXf element.
    Alignment           maAlignment;        /// Cell alignment data.
    Protection          maProtection;       /// Cell protection data.
};

typedef ::boost::shared_ptr< Xf > XfRef;

// ============================================================================

class Dxf : public WorkbookHelper
{
public:
    explicit            Dxf( const WorkbookHelper& rHelper );

    /** Appends and returns a new font object. */
    FontRef             importFont( const AttributeList& rAttribs );
    /** Inserts a new number format code. */
    void                importNumFmt( const AttributeList& rAttribs );
    /** Sets all attributes from the alignment element. */
    void                importAlignment( const AttributeList& rAttribs );
    /** Sets all attributes from the protection element. */
    void                importProtection( const AttributeList& rAttribs );
    /** Appends and returns a new cell border object. */
    BorderRef           importBorder( const AttributeList& rAttribs );
    /** Appends and returns a new cell fill object. */
    FillRef             importFill( const AttributeList& rAttribs );

    /** Imports the DXF record from the passed stream. */
    void                importDxf( RecordInputStream& rStrm );

    /** Imports font, border, and fill settings from the CFRULE record. */
    void                importCfRule( BiffInputStream& rStrm, sal_uInt32 nFlags );

    /** Final processing after import of all style settings. */
    void                finalizeImport();

    /** Creates the style sheet described by the DXF. */
    const ::rtl::OUString& createDxfStyle( sal_Int32 nDxfId );

private:
    void                createFont( bool bAlwaysNew );
    void                createBorder( bool bAlwaysNew );
    void                createFill( bool bAlwaysNew );

private:
    FontRef             mxFont;             /// Font data.
    NumberFormatRef     mxNumFmt;           /// Number format data.
    AlignmentRef        mxAlignment;        /// Alignment data.
    ProtectionRef       mxProtection;       /// Protection data.
    BorderRef           mxBorder;           /// Border data.
    FillRef             mxFill;             /// Fill data.
    ::rtl::OUString     maFinalName;        /// Final style name used in API.
};

typedef ::boost::shared_ptr< Dxf > DxfRef;

// ============================================================================

/** Contains attributes of a cell style, e.g. from the cellStyle element. */
struct OoxCellStyleData
{
    ::rtl::OUString     maName;             /// Cell style name.
    sal_Int32           mnXfId;             /// Formatting for this cell style.
    sal_Int32           mnBuiltinId;        /// Identifier for builtin styles.
    sal_Int32           mnLevel;            /// Level for builtin column/row styles.
    bool                mbBuiltin;          /// True = builtin style.
    bool                mbCustom;           /// True = customized builtin style.
    bool                mbHidden;           /// True = style not visible in GUI.

    explicit            OoxCellStyleData();

    /** Returns true, if this style is a builtin style. */
    inline bool         isBuiltin() const { return mbBuiltin && (mnBuiltinId >= 0); }
    /** Returns true, if this style represents the default document cell style. */
    bool                isDefaultStyle() const;
    /** Returns the style name used in the UI. */
    ::rtl::OUString     createStyleName() const;
};

// ============================================================================

class CellStyle : public WorkbookHelper
{
public:
    explicit            CellStyle( const WorkbookHelper& rHelper );

    /** Imports passed attributes from the cellStyle element. */
    void                importCellStyle( const AttributeList& rAttribs );
    /** Imports style settings from a CELLSTYLE record. */
    void                importCellStyle( RecordInputStream& rStrm );
    /** Imports style settings from a STYLE record. */
    void                importStyle( BiffInputStream& rStrm );

    /** Returns true, if this style represents the default document cell style. */
    inline bool         isDefaultStyle() const { return maOoxData.isDefaultStyle(); }
    /** Returns the XF identifier for this cell style. */
    inline sal_Int32    getXfId() const { return maOoxData.mnXfId; }

    /** Creates the style sheet described by the style XF with the passed identifier. */
    const ::rtl::OUString& createCellStyle( sal_Int32 nXfId, bool bSkipDefaultBuiltin = false );

private:
    OoxCellStyleData    maOoxData;
    ::rtl::OUString     maFinalName;        /// Final style name used in API.
};

typedef ::boost::shared_ptr< CellStyle > CellStyleRef;

// ============================================================================

class StylesBuffer : public WorkbookHelper
{
public:
    explicit            StylesBuffer( const WorkbookHelper& rHelper );

    /** Creates a new empty font object.
        @param opnFontId  (out-param) The identifier of the new font object. */
    FontRef             createFont( sal_Int32* opnFontId = 0 );
    /** Creates a number format. */
    NumberFormatRef     createNumFmt( sal_Int32 nNumFmtId, const ::rtl::OUString& rFmtCode );
    /** Creates a new empty border object.
        @param opnBorderId  (out-param) The identifier of the new border object. */
    BorderRef           createBorder( sal_Int32* opnBorderId = 0 );
    /** Creates a new empty fill object.
        @param opnFillId  (out-param) The identifier of the new fill object. */
    FillRef             createFill( sal_Int32* opnFillId = 0 );
    /** Creates a new empty cell formatting object.
        @param opnXfId  (out-param) The identifier of the new XF object. */
    XfRef               createCellXf( sal_Int32* opnXfId = 0 );
    /** Creates a new empty style formatting object.
        @param opnXfId  (out-param) The identifier of the new XF object. */
    XfRef               createStyleXf( sal_Int32* opnXfId = 0 );
    /** Creates a new empty differential formatting object.
        @param opnDxfId  (out-param) The identifier of the new DXF object. */
    DxfRef              createDxf( sal_Int32* opnDxfId = 0 );

    /** Appends a new color to the color palette. */
    void                importPaletteColor( const AttributeList& rAttribs );
    /** Appends and returns a new font object. */
    FontRef             importFont( const AttributeList& rAttribs );
    /** Inserts a new number format code. */
    NumberFormatRef     importNumFmt( const AttributeList& rAttribs );
    /** Appends and returns a new cell border object. */
    BorderRef           importBorder( const AttributeList& rAttribs );
    /** Appends and returns a new cell fill object. */
    FillRef             importFill( const AttributeList& rAttribs );
    /** Appends and returns a new cell format or cell style object. */
    XfRef               importXf( sal_Int32 nContext, const AttributeList& rAttribs );
    /** Appends and returns a new differential cell format object. */
    DxfRef              importDxf( const AttributeList& rAttribs );
    /** Appends and returns a new named cell style object. */
    CellStyleRef        importCellStyle( const AttributeList& rAttribs );

    /** Appends a new color to the color palette. */
    void                importPaletteColor( RecordInputStream& rStrm );
    /** Imports the FONT record from the passed stream. */
    void                importFont( RecordInputStream& rStrm );
    /** Imports the NUMFMT record from the passed stream. */
    void                importNumFmt( RecordInputStream& rStrm );
    /** Imports the BORDER record from the passed stream. */
    void                importBorder( RecordInputStream& rStrm );
    /** Imports the FILL record from the passed stream. */
    void                importFill( RecordInputStream& rStrm );
    /** Imports a cell format or cell style object from the passed stream. */
    void                importXf( sal_Int32 nContext, RecordInputStream& rStrm );
    /** Imports a new differential cell format object from the passed stream. */
    void                importDxf( RecordInputStream& rStrm );
    /** Imports the CELLSTYLE record from the passed stream. */
    void                importCellStyle( RecordInputStream& rStrm );

    /** Imports the PALETTE record from the passed stream. */
    void                importPalette( BiffInputStream& rStrm );
    /** Imports the FONT record from the passed stream. */
    void                importFont( BiffInputStream& rStrm );
    /** Imports the FONTCOLOR record from the passed stream. */
    void                importFontColor( BiffInputStream& rStrm );
    /** Imports the FORMAT record from the passed stream. */
    void                importFormat( BiffInputStream& rStrm );
    /** Imports the XF record from the passed stream. */
    void                importXf( BiffInputStream& rStrm );
    /** Imports the STYLE record from the passed stream. */
    void                importStyle( BiffInputStream& rStrm );

    /** Final processing after import of all style settings. */
    void                finalizeImport();

    /** Returns the RGB value of the passed color object, or nAuto for automatic colors. */
    sal_Int32           getColor( const OoxColor& rColor, sal_Int32 nAuto ) const;
    /** Returns the specified font object. */
    FontRef             getFont( sal_Int32 nFontId ) const;
    /** Returns the specified cell format object. */
    XfRef               getCellXf( sal_Int32 nXfId ) const;
    /** Returns the specified style format object. */
    XfRef               getStyleXf( sal_Int32 nXfId ) const;
    /** Returns the specified diferential cell format object. */
    DxfRef              getDxf( sal_Int32 nDxfId ) const;

    /** Returns the font object of the specified cell XF. */
    FontRef             getFontFromCellXf( sal_Int32 nXfId ) const;
    /** Returns the default application font (used in the "Normal" cell style). */
    FontRef             getDefaultFont() const;
    /** Returns the default application font data (used in the "Normal" cell style). */
    const OoxFontData&  getDefaultFontData() const;

    /** Creates the style sheet described by the style XF with the passed identifier. */
    const ::rtl::OUString& createCellStyle( sal_Int32 nXfId ) const;
    /** Creates the style sheet described by the DXF with the passed identifier. */
    const ::rtl::OUString& createDxfStyle( sal_Int32 nDxfId ) const;
#if OOX_XLS_USE_DEFAULT_STYLE
#else
    /** Returns the default style sheet for unused cells. */
    const ::rtl::OUString& getDefaultStyleName() const;
#endif

    /** Writes the font attributes of the specified font data to the passed property set. */
    void                writeFontToPropertySet( PropertySet& rPropSet, sal_Int32 nFontId ) const;
    /** Writes the specified number format to the passed property set. */
    void                writeNumFmtToPropertySet( PropertySet& rPropSet, sal_Int32 nNumFmtId ) const;
    /** Writes the border attributes of the specified border data to the passed property set. */
    void                writeBorderToPropertySet( PropertySet& rPropSet, sal_Int32 nBorderId ) const;
    /** Writes the fill attributes of the specified fill data to the passed property set. */
    void                writeFillToPropertySet( PropertySet& rPropSet, sal_Int32 nFillId ) const;
    /** Writes the cell formatting attributes of the specified XF to the passed property set. */
    void                writeCellXfToPropertySet( PropertySet& rPropSet, sal_Int32 nXfId ) const;
    /** Writes the cell formatting attributes of the specified style XF to the passed property set. */
    void                writeStyleXfToPropertySet( PropertySet& rPropSet, sal_Int32 nXfId ) const;

private:
    void                insertCellStyle( CellStyleRef xCellStyle );

private:
    typedef RefVector< Font >               FontVec;
    typedef RefVector< Border >             BorderVec;
    typedef RefVector< Fill >               FillVec;
    typedef RefVector< Xf >                 XfVec;
    typedef RefVector< Dxf >                DxfVec;
    typedef RefMap< sal_Int32, CellStyle >  CellStyleMap;

    ColorPalette        maPalette;          /// Color palette.
    FontVec             maFonts;            /// List of font objects.
    NumberFormatsBuffer maNumFmts;          /// List of all number format codes.
    BorderVec           maBorders;          /// List of cell border objects.
    FillVec             maFills;            /// List of cell area fill objects.
    XfVec               maCellXfs;          /// List of cell formats.
    XfVec               maStyleXfs;         /// List of cell styles.
    DxfVec              maDxfs;             /// List of differential cell styles.
    CellStyleMap        maCellStyles;       /// List of named cell styles.
    ::rtl::OUString     maDefStyleName;     /// API name of default cell style.
    sal_Int32           mnDefStyleXf;       /// Style XF index of default cell style.
};

// ============================================================================

} // namespace xls
} // namespace oox

#endif

