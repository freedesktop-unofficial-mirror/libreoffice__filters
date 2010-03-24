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

#ifndef OOX_DRAWINGML_LINEPROPERTIES_HXX
#define OOX_DRAWINGML_LINEPROPERTIES_HXX

#include "oox/drawingml/fillproperties.hxx"

namespace oox {
namespace drawingml {

// ============================================================================

enum LinePropertyId
{
    LineStyleId,
    LineWidthId,
    LineColorId,
    LineTransparenceId,
    LineDashId,
    LineJointId,
    LineStartId,
    LineStartWidthId,
    LineStartCenterId,
    LineEndId,
    LineEndWidthId,
    LineEndCenterId,
    LineId_END
};

struct LinePropertyIds
{
    const sal_Int32*    mpnPropertyIds;
    bool                mbNamedLineDash;
    bool                mbNamedLineMarker;

    explicit            LinePropertyIds(
                            const sal_Int32* pnPropertyIds,
                            bool bNamedLineDash,
                            bool bNamedLineMarker );

    inline bool         has( LinePropertyId ePropId ) const { return mpnPropertyIds[ ePropId ] >= 0; }
    inline sal_Int32    operator[]( LinePropertyId ePropId ) const { return mpnPropertyIds[ ePropId ]; }
};

// ============================================================================

struct LineArrowProperties
{
    OptValue< sal_Int32 > moArrowType;
    OptValue< sal_Int32 > moArrowWidth;
    OptValue< sal_Int32 > moArrowLength;

    /** Overwrites all members that are explicitly set in rSourceProps. */
    void                assignUsed( const LineArrowProperties& rSourceProps );
};

// ============================================================================

struct LineProperties
{
    typedef ::std::pair< sal_Int32, sal_Int32 > DashStop;
    typedef ::std::vector< DashStop >           DashStopVector;

    LineArrowProperties maStartArrow;       /// Start line arrow style.
    LineArrowProperties maEndArrow;         /// End line arrow style.
    FillProperties      maLineFill;         /// Line fill (solid, gradient, ...).
    DashStopVector      maCustomDash;       /// User-defined line dash style.
    OptValue< sal_Int32 > moLineWidth;      /// Line width (EMUs).
    OptValue< sal_Int32 > moPresetDash;     /// Preset dash (OOXML token).
    OptValue< sal_Int32 > moLineCompound;   /// Line compound type (OOXML token).
    OptValue< sal_Int32 > moLineCap;        /// Line cap (OOXML token).
    OptValue< sal_Int32 > moLineJoint;      /// Line joint type (OOXML token).

    static LinePropertyIds DEFAULT_IDS;     /// Default line property identifiers.

    /** Overwrites all members that are explicitly set in rSourceProps. */
    void                assignUsed( const LineProperties& rSourceProps );

    /** Writes the properties to the passed property map. */
    void                pushToPropMap(
                            PropertyMap& rPropMap,
                            const ::oox::core::FilterBase& rFilter,
                            ModelObjectHelper& rModelObjHelper,
                            const LinePropertyIds& rPropIds = DEFAULT_IDS,
                            sal_Int32 nPhClr = API_RGB_TRANSPARENT ) const;

    /** Writes the properties to the passed property map. */
    void                pushToPropSet(
                            PropertySet& rPropSet,
                            const ::oox::core::FilterBase& rFilter,
                            ModelObjectHelper& rModelObjHelper,
                            const LinePropertyIds& rPropIds = DEFAULT_IDS,
                            sal_Int32 nPhClr = API_RGB_TRANSPARENT ) const;
};

// ============================================================================

} // namespace drawingml
} // namespace oox

#endif

