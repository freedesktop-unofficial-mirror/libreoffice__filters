/*************************************************************************
 *
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER.
 * 
 * Copyright 2008 by Sun Microsystems, Inc.
 *
 * OpenOffice.org - a multi-platform office productivity suite
 *
 * $RCSfile: themebuffer.hxx,v $
 * $Revision: 1.4 $
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

#ifndef OOX_XLS_THEMEBUFFER_HXX
#define OOX_XLS_THEMEBUFFER_HXX

#include "oox/drawingml/theme.hxx"
#include "oox/xls/workbookhelper.hxx"

namespace oox {
namespace xls {

struct OoxFontData;

// ============================================================================

class ThemeBuffer : public WorkbookHelper
{
public:
    explicit            ThemeBuffer( const WorkbookHelper& rHelper );
    virtual             ~ThemeBuffer();

    /** Returns the pointer to the core drawingml theme. */
    inline const ::oox::drawingml::ThemePtr& getCoreThemePtr() const { return mxTheme; }

    /** Returns the core drawingml theme needed by the theme fragment importer. */
    ::oox::drawingml::Theme& getOrCreateCoreTheme();

    /** Returns the theme color with the specified token identifier. */
    sal_Int32           getColorByToken( sal_Int32 nToken ) const;
    /** Returns the theme color with the specified index. */
    sal_Int32           getColorByIndex( sal_Int32 nIndex ) const;

    /** Returns the system color referred by the specified token. */
    static sal_Int32    getSystemColor( sal_Int32 nElement, sal_Int32 nDefaultColor );
    /** Returns the system background color (window color). */
    static sal_Int32    getSystemWindowColor();
    /** Returns the system text color (window text color). */
    static sal_Int32    getSystemWindowTextColor();

    /** Returns the default font data for the current file type. */
    inline const OoxFontData& getDefaultFontData() const { return *mxDefFontData; }

private:
    typedef ::std::auto_ptr< OoxFontData > OoxFontDataPtr;

    ::oox::drawingml::ThemePtr mxTheme;
    OoxFontDataPtr      mxDefFontData;
};

// ============================================================================

} // namespace xls
} // namespace oox

#endif

