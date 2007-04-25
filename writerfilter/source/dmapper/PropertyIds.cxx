/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: PropertyIds.cxx,v $
 *
 *  $Revision: 1.18 $
 *
 *  last change: $Author: os $ $Date: 2007-04-25 11:30:51 $
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
#ifndef INCLUDED_DMAPPER_PROPERTYIDS_HXX
#include <PropertyIds.hxx>
#endif
#include <rtl/ustring.hxx>
#include <hash_map>

namespace dmapper{

struct PropertyIdHash
{
    unsigned long operator()(const PropertyIds& eId) const
    {
        return static_cast<unsigned long>(eId);
    }
};

struct PropertyIdEq
{
    bool operator() (const PropertyIds& rA, const PropertyIds& rB) const
    {
        return rA == rB;
    }
};

typedef ::std::hash_map< PropertyIds, ::rtl::OUString, PropertyIdHash, PropertyIdEq> PropertyNameMap_t;


//typedef std::map< PropertyIds, ::rtl::OUString > PropertyNameMap_t;
struct PropertyNameSupplier_Impl
{
    PropertyNameMap_t aNameMap;
};

/*-- 14.06.2006 11:01:31---------------------------------------------------

  -----------------------------------------------------------------------*/
PropertyNameSupplier::PropertyNameSupplier() :
    m_pImpl(new PropertyNameSupplier_Impl)
{
}
/*-- 14.06.2006 11:01:32---------------------------------------------------

  -----------------------------------------------------------------------*/
PropertyNameSupplier::~PropertyNameSupplier()
{
    delete m_pImpl;
}
/*-- 14.06.2006 11:01:32---------------------------------------------------

  -----------------------------------------------------------------------*/
const rtl::OUString& PropertyNameSupplier::GetName( PropertyIds eId ) const
{
    PropertyNameMap_t::iterator aIt = m_pImpl->aNameMap.find(eId);
    if(aIt == m_pImpl->aNameMap.end())
    {
        ::rtl::OUString sName;
        switch(eId)
        {
            case PROP_CHAR_WEIGHT:     sName = ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("CharWeight")); break;
            case PROP_CHAR_POSTURE:    sName = ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("CharPosture")); break;
            case PROP_CHAR_STRIKEOUT:  sName = ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("CharStrikeout")); break;
            case PROP_CHAR_CONTOURED:  sName = ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("CharContoured")); break;
            case PROP_CHAR_SHADOWED:   sName = ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("CharShadowed")); break;
            case PROP_CHAR_CASEMAP:    sName = ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("CharCaseMap")); break;
            case PROP_CHAR_COLOR:      sName = ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("CharColor")); break;
            case PROP_CHAR_RELIEF:     sName = ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("CharRelief")); break;
            case PROP_CHAR_UNDERLINE:  sName = ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("CharUnderline")); break;
            case PROP_CHAR_UNDERLINE_COLOR:  sName = ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("CharUnderlineColor")); break;
            case PROP_CHAR_UNDERLINE_HAS_COLOR:  sName = ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("CharUnderlineHasColor")); break;
            case PROP_CHAR_WORD_MODE:  sName = ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("CharWordMode")); break;
            case PROP_CHAR_ESCAPEMENT       :     sName = ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("CharEscapement")); break;
            case PROP_CHAR_ESCAPEMENT_HEIGHT:     sName = ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("CharEscapementHeight")); break;
            case PROP_CHAR_HEIGHT:     sName = ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("CharHeight")); break;
            case PROP_CHAR_HEIGHT_COMPLEX:     sName = ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("CharHeightComplex")); break;
            case PROP_CHAR_LOCALE:     sName = ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("CharLocale")); break;
            case PROP_CHAR_LOCALE_ASIAN:     sName = ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("CharLocaleAsian")); break;
            case PROP_CHAR_LOCALE_COMPLEX:     sName = ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("CharLocaleComplex")); break;
            case PROP_CHAR_WEIGHT_COMPLEX :  sName = ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("CharWeightComplex")); break;
            case PROP_CHAR_POSTURE_COMPLEX:  sName = ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("CharPostureComplex")); break;
            case PROP_CHAR_CHAR_KERNING:     sName = ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("CharKerning")); break;
            case PROP_CHAR_AUTO_KERNING:     sName = ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("CharAutoKerning")); break;
            case PROP_CHAR_SCALE_WIDTH:      sName = ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("CharScaleWidth")); break;
            case PROP_CHAR_STYLE_NAME:      sName = ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("CharStyleName")); break;
            case PROP_CHAR_FONT_NAME:                sName = ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("CharFontName")); break;
            case PROP_CHAR_FONT_STYLE:               sName = ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("CharFontStyle")); break;
            case PROP_CHAR_FONT_FAMILY:              sName = ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("CharFontFamily")); break;
            case PROP_CHAR_FONT_CHAR_SET:            sName = ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("CharFontCharSet")); break;
            case PROP_CHAR_FONT_PITCH:               sName = ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("CharFontPitch")); break;
            case PROP_CHAR_FONT_NAME_HANSI:                sName = ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("CharFontNameHAnsi")); break;
            case PROP_CHAR_FONT_STYLE_HANSI:               sName = ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("CharFontStyleHAnsi")); break;
            case PROP_CHAR_FONT_FAMILY_HANSI:              sName = ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("CharFontFamilyHAnsi")); break;
            case PROP_CHAR_FONT_CHAR_SET_HANSI:            sName = ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("CharFontCharSetHAnsi")); break;
            case PROP_CHAR_FONT_PITCH_HANSI:               sName = ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("CharFontPitchHAnsi")); break;
            case PROP_CHAR_FONT_NAME_ASIAN     :     sName = ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("CharFontNameAsian")); break;
            case PROP_CHAR_HEIGHT_ASIAN        :     sName = ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("CharHeightAsian")); break;
            case PROP_CHAR_FONT_STYLE_ASIAN    :     sName = ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("CharFontStyleAsian")); break;
            case PROP_CHAR_FONT_FAMILY_ASIAN   :     sName = ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("CharFontFamilyAsian")); break;
            case PROP_CHAR_FONT_CHAR_SET_ASIAN :     sName = ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("CharFontCharSetAsian")); break;
            case PROP_CHAR_FONT_PITCH_ASIAN    :     sName = ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("CharFontPitchAsian")); break;
            case PROP_CHAR_FONT_NAME_COMPLEX   :     sName = ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("CharFontNameComplex")); break;
            case PROP_CHAR_FONT_STYLE_COMPLEX  :     sName = ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("CharFontStyleComplex")); break;
            case PROP_CHAR_FONT_FAMILY_COMPLEX:      sName = ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("CharFontFamilyComplex")); break;
            case PROP_CHAR_FONT_CHAR_SET_COMPLEX:    sName = ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("CharFontCharSetComplex")); break;
            case PROP_CHAR_FONT_PITCH_COMPLEX:       sName = ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("CharFontPitchComplex")); break;
            case PROP_CHAR_HIDDEN           :     sName = ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("CharHidden")); break;
            case PROP_CHAR_WEIGHT_ASIAN     :     sName = ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("CharWeightAsian")); break;
            case PROP_CHAR_POSTURE_ASIAN    :     sName = ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("CharPostureAsian")); break;
            case PROP_CHAR_BACK_COLOR:     sName = ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("CharBackColor")); break;
            case PROP_CHAR_EMPHASIS:     sName = ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("CharEmphasis")); break;
            case PROP_CHAR_COMBINE_IS_ON:     sName = ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("CharCombineIsOn")); break;
            case PROP_CHAR_COMBINE_PREFIX:     sName = ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("CharCombinePrefix")); break;
            case PROP_CHAR_COMBINE_SUFFIX:     sName = ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("CharCombineSuffix")); break;
            case PROP_CHAR_ROTATION:     sName = ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("CharRotation")); break;
            case PROP_CHAR_ROTATION_IS_FIT_TO_LINE:     sName = ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("CharRotationIsFitToLine")); break;
            case PROP_CHAR_FLASH:     sName = ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("CharFlash")); break;
//            case PROP_CHAR_:     sName = ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("Char")); break;
//            case PROP_CHAR_:     sName = ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("Char")); break;
//            case PROP_CHAR_:     sName = ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("Char")); break;

            case PROP_PARA_STYLE_NAME:      sName = ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("ParaStyleName")); break;
            case PROP_PARA_ADJUST:     sName = ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("ParaAdjust")); break;
            case PROP_PARA_LAST_LINE_ADJUST:     sName = ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("ParaLastLineAdjust")); break;
            case PROP_PARA_RIGHT_MARGIN     :    sName = ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("ParaRightMargin")); break;
            case PROP_PARA_LEFT_MARGIN      :    sName = ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("ParaLeftMargin")); break;
            case PROP_PARA_FIRST_LINE_INDENT:    sName = ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("ParaFirstLineIndent")); break;
            case PROP_PARA_KEEP_TOGETHER:       sName = ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("ParaKeepTogether")); break;
            case PROP_PARA_TOP_MARGIN:       sName = ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("ParaTopMargin")); break;
            case PROP_PARA_BOTTOM_MARGIN:       sName = ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("ParaBottomMargin")); break;
            case PROP_PARA_IS_HYPHENATION:     sName = ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("ParaIsHyphenation")); break;
            case PROP_PARA_LINE_NUMBER_COUNT:     sName = ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("ParaLineNumberCount")); break;
            case PROP_PARA_IS_HANGING_PUNCTUATION: sName = ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("ParaIsHangingPunctuation")); break;
            case PROP_PARA_LINE_SPACING:     sName = ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("ParaLineSpacing")); break;
            case PROP_PARA_TAB_STOPS:       sName = ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("ParaTabStops")); break;
            case PROP_PARA_WIDOWS:          sName = ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("ParaWidows")); break;
            case PROP_PARA_ORPHANS:         sName = ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("ParaOrphans")); break;
            case PROP_PARA_LINE_NUMBER_START_VALUE:    sName = ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("ParaLineNumberStartValue")); break;
//            case PROP_PARA_:     sName = ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("Para")); break;
//            case PROP_PARA_:     sName = ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("Para")); break;
//            case PROP_PARA_:     sName = ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("Para")); break;
//            case PROP_PARA_:     sName = ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("Para")); break;
            case PROP_NUMBERING_LEVEL:  sName = ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("NumberingLevel")); break;
            case PROP_NUMBERING_RULES:  sName = ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("NumberingRules")); break;
            case PROP_NUMBERING_TYPE:   sName = ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("NumberingType")); break;
            case PROP_START_WITH:       sName = ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("StartWith")); break;
            case PROP_ADJUST:           sName = ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("Adjust")); break;
            case PROP_PARENT_NUMBERING: sName = ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("ParentNumbering")); break;
            case PROP_RIGHT_MARGIN     :    sName = ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("RightMargin")); break;
            case PROP_LEFT_MARGIN      :    sName = ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("LeftMargin")); break;
            case PROP_TOP_MARGIN          :    sName = ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("TopMargin")); break;
            case PROP_BOTTOM_MARGIN       :    sName = ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("BottomMargin")); break;
            case PROP_FIRST_LINE_OFFSET:    sName = ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("FirstLineOffset")); break;
            case PROP_LEFT_BORDER           :    sName = ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("LeftBorder"));break;
            case PROP_RIGHT_BORDER          :    sName = ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("RightBorder"));break;
            case PROP_TOP_BORDER            :    sName = ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("TopBorder"));break;
            case PROP_BOTTOM_BORDER         :    sName = ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("BottomBorder"));break;
            case PROP_TABLE_BORDER         :    sName = ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("TableBorder"));break;
            case PROP_LEFT_BORDER_DISTANCE  :    sName = ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("LeftBorderDistance")); break;
            case PROP_RIGHT_BORDER_DISTANCE :    sName = ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("RightBorderDistance")); break;
            case PROP_TOP_BORDER_DISTANCE   :    sName = ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("TopBorderDistance"));break;
            case PROP_BOTTOM_BORDER_DISTANCE:    sName = ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("BottomBorderDistance")); break;
            case PROP_CURRENT_PRESENTATION  :    sName = ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("CurrentPresentation")); break;
            case PROP_IS_FIXED              :    sName = ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("IsFixed")); break;
            case PROP_SUB_TYPE              :    sName = ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("SubType")); break;
            case PROP_FILE_FORMAT           :    sName = ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("FileFormat")); break;
            case PROP_HYPER_LINK_U_R_L      :    sName = ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("HyperLinkURL")); break;
            case PROP_NUMBER_FORMAT         :    sName = ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("NumberFormat")); break;
            case PROP_NAME                  :    sName = ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("Name")); break;
            case PROP_IS_INPUT              :    sName = ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("IsInput")); break;
            case PROP_HINT                  :    sName = ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("Hint")); break;
            case PROP_FULL_NAME             :    sName = ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("FullName")); break;
            case PROP_KEYWORDS              :    sName = ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("Keywords")); break;
            case PROP_DESCRIPTION           :    sName = ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("Description")); break;
            case PROP_MACRO_NAME            :    sName = ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("MacroName")); break;
            case PROP_SUBJECT               :    sName = ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("Subject")); break;
            case PROP_USER_DATA_TYPE        :    sName = ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("UserDataType")); break;
            case PROP_TITLE                 :    sName = ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("Title")); break;
            case PROP_CONTENT               :    sName = ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("Content")); break;
            case PROP_DATA_COLUMN_NAME      :    sName = ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("DataColumnName")); break;
            case PROP_INPUT_STREAM          :    sName = ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("InputStream")); break;
            case PROP_GRAPHIC               :    sName = ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("Graphic")); break;
            case PROP_ANCHOR_TYPE           :    sName = ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("AnchorType")); break;
            case PROP_SIZE                  :    sName = ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("Size")); break;
            case PROP_HORI_ORIENT           :    sName = ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("HoriOrient")); break;
            case PROP_HORI_ORIENT_POSITION  :    sName = ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("HoriOrientPosition")); break;
            case PROP_HORI_ORIENT_RELATION  :    sName = ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("HoriOrientRelation")); break;
            case PROP_VERT_ORIENT           :    sName = ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("VertOrient")); break;
            case PROP_VERT_ORIENT_POSITION  :    sName = ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("VertOrientPosition")); break;
            case PROP_VERT_ORIENT_RELATION  :    sName = ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("VertOrientRelation")); break;
            case PROP_GRAPHIC_CROP          :    sName = ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("GraphicCrop")); break;
            case PROP_SIZE100th_M_M         :    sName = ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("Size100thMM")); break;
            case PROP_SIZE_PIXEL            :    sName = ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("SizePixel")); break;
            case PROP_SURROUND              :    sName = ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("Surround")); break;
            case PROP_SURROUND_CONTOUR      :    sName = ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("SurroundContour")); break;
            case PROP_ADJUST_CONTRAST       :    sName = ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("AdjustContrast")); break;
            case PROP_ADJUST_LUMINANCE      :    sName = ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("AdjustLuminance")); break;
            case PROP_GRAPHIC_COLOR_MODE    :    sName = ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("GraphicColorMode")); break;
            case PROP_GAMMA                 :    sName = ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("Gamma")); break;
            case PROP_HORI_MIRRORED_ON_EVEN_PAGES:    sName = ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("HoriMirroredOnEvenPages")); break;
            case PROP_HORI_MIRRORED_ON_ODD_PAGES :    sName = ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("HoriMirroredOnOddPages")); break;
            case PROP_VERT_MIRRORED        :    sName = ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("VertMirrored")); break;
            case PROP_CONTOUR_OUTSIDE      :    sName = ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("ContourOutside")); break;
            case PROP_CONTOUR_POLY_POLYGON :    sName = ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("ContourPolyPolygon")); break;
            case PROP_PAGE_TOGGLE          :    sName = ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("PageToggle")); break;
            case PROP_BACK_COLOR           :    sName = ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("BackColor")); break;
            case PROP_ALTERNATIVE_TEXT     :    sName = ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("AlternativeText")); break;
            case PROP_HEADER_TEXT_LEFT     :    sName = ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("HeaderTextLeft")); break;
            case PROP_HEADER_TEXT          :    sName = ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("HeaderText")); break;
            case PROP_HEADER_IS_SHARED     :    sName = ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("HeaderIsShared")); break;
            case PROP_HEADER_IS_ON         :    sName = ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("HeaderIsOn")); break;
            case PROP_FOOTER_TEXT_LEFT     :    sName = ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("FooterTextLeft")); break;
            case PROP_FOOTER_TEXT          :    sName = ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("FooterText")); break;
            case PROP_FOOTER_IS_SHARED     :    sName = ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("FooterIsShared")); break;
            case PROP_FOOTER_IS_ON         :    sName = ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("FooterIsOn")); break;
            case PROP_WIDTH                :    sName = ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("Width")); break;
            case PROP_HEIGHT               :    sName = ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("Height")); break;
            case PROP_SEPARATOR_LINE_IS_ON :    sName = ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("SeparatorLineIsOn")); break;
            case PROP_TEXT_COLUMNS         :    sName = ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("TextColumns")); break;
            case PROP_AUTOMATIC_DISTANCE   :    sName = ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("AutomaticDistance")); break;
            case PROP_IS_LANDSCAPE         :    sName = ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("IsLandscape")); break;
            case PROP_PRINTER_PAPER_TRAY_INDEX:    sName = ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("PrinterPaperTrayIndex")); break;
            case PROP_FIRST_PAGE       :    sName = ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("First Page")); break;
            case PROP_DEFAULT          :    sName = ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("Default")); break;
            case PROP_PAGE_DESC_NAME   :    sName = ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("PageDescName")); break;
            case PROP_PAGE_NUMBER_OFFSET:    sName = ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("PageNumberOffset")); break;
            case PROP_BREAK_TYPE       :    sName = ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("BreakType")); break;
            case PROP_FOOTER_IS_DYNAMIC_HEIGHT:  sName = ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("FooterIsDynamicHeight")); break;
            case PROP_FOOTER_DYNAMIC_SPACING:    sName = ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("FooterDynamicSpacing")); break;
            case PROP_FOOTER_HEIGHT         :    sName = ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("FooterHeight")); break;
            case PROP_FOOTER_BODY_DISTANCE  :    sName = ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("FooterBodyDistance")); break;
            case PROP_HEADER_IS_DYNAMIC_HEIGHT:  sName = ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("HeaderIsDynamicHeight")); break;
            case PROP_HEADER_DYNAMIC_SPACING:    sName = ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("HeaderDynamicSpacing")); break;
            case PROP_HEADER_HEIGHT         :    sName = ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("HeaderHeight")); break;
            case PROP_HEADER_BODY_DISTANCE  :    sName = ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("HeaderBodyDistance")); break;
            case PROP_WRITING_MODE          :    sName = ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("WritingMode")); break;
            case PROP_GRID_MODE             :    sName = ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("GridMode")); break;
            case PROP_GRID_DISPLAY          :    sName = ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("GridDisplay")); break;
            case PROP_GRID_PRINT            :    sName = ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("GridPrint")); break;
            case PROP_ADD_EXTERNAL_LEADING  :    sName = ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("AddExternalLeading")); break;
            case PROP_GRID_LINES            :    sName = ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("GridLines")); break;
            case PROP_GRID_BASE_HEIGHT      :    sName = ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("GridBaseHeight")); break;
            case PROP_GRID_RUBY_HEIGHT      :    sName = ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("GridRubyHeight")); break;
            case PROP_IS_ON                  :    sName = ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("IsOn")); break;
            case PROP_RESTART_AT_EACH_PAGE   :    sName = ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("RestartAtEachPage")); break;
            case PROP_COUNT_EMPTY_LINES      :    sName = ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("CountEmptyLines")); break;
            case PROP_COUNT_LINES_IN_FRAMES  :    sName = ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("CountLinesInFrames")); break;
            case PROP_INTERVAL               :    sName = ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("Interval")); break;
            case PROP_DISTANCE               :    sName = ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("Distance")); break;
            case PROP_NUMBER_POSITION        :    sName = ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("NumberPosition")); break;
            case PROP_LEVEL                  :    sName = ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("Level")); break;
            case PROP_LEVEL_PARAGRAPH_STYLES :    sName = ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("LevelParagraphStyles")); break;
            case PROP_LEVEL_FORMAT           :    sName = ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("LevelFormat")); break;
            case PROP_TOKEN_TYPE             :    sName = ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("TokenType")); break;
            case PROP_TOKEN_HYPERLINK_START  :    sName = ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("TokenHyperlinkStart")); break;
            case PROP_TOKEN_HYPERLINK_END    :    sName = ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("TokenHyperlinkEnd")); break;
            case PROP_TOKEN_CHAPTER_INFO     :    sName = ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("TokenChapterInfo")); break;
            case PROP_CHAPTER_FORMAT         :    sName = ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("ChapterFormat")); break;
            case PROP_TOKEN_TEXT             :    sName = ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("TokenText")); break;
            case PROP_TEXT                   :    sName = ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("Text")); break;
            case PROP_CREATE_FROM_OUTLINE    :    sName = ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("CreateFromOutline")); break;
            case PROP_CREATE_FROM_MARKS      :    sName = ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("CreateFromMarks")); break;
            case PROP_STANDARD               :    sName = ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("Standard")); break;
            case PROP_IS_SPLIT_ALLOWED       :    sName = ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("IsSplitAllowed")); break;
//            case       :    sName = ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("")); break;
//            case       :    sName = ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("")); break;
//            case       :    sName = ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("")); break;
//            case       :    sName = ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("")); break;
//            case       :    sName = ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("")); break;
//            case       :    sName = ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("")); break;
//            case       :    sName = ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("")); break;
        }
        ::std::pair<PropertyNameMap_t::iterator,bool> aInsertIt =
                m_pImpl->aNameMap.insert( PropertyNameMap_t::value_type( eId, sName ));
        if(aInsertIt.second)
            aIt = aInsertIt.first;
    }
    return aIt->second;
}
PropertyNameSupplier& PropertyNameSupplier::GetPropertyNameSupplier()
{
    static PropertyNameSupplier aNameSupplier;
    return aNameSupplier;
}

} //namespace dmapper
