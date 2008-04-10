/*************************************************************************
 *
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER.
 * 
 * Copyright 2008 by Sun Microsystems, Inc.
 *
 * OpenOffice.org - a multi-platform office productivity suite
 *
 * $RCSfile: namespaces.hxx,v $
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

#ifndef OOX_CORE_NAMESPACES_HXX
#define OOX_CORE_NAMESPACES_HXX

#include <sal/types.h>

namespace oox {

// ============================================================================

// relations, XML
const sal_Int32 NMSP_XML                    = 1 << 16;
const sal_Int32 NMSP_PACKAGE_RELATIONSHIPS  = 2 << 16;
const sal_Int32 NMSP_RELATIONSHIPS          = 3 << 16;
const sal_Int32 NMSP_CONTENT_TYPES          = 4 << 16;
// office global
const sal_Int32 NMSP_OFFICE                 = 11 << 16;
const sal_Int32 NMSP_ACTIVATION             = 12 << 16;
// DrawingML
const sal_Int32 NMSP_DRAWINGML              = 21 << 16;
const sal_Int32 NMSP_DIAGRAM                = 22 << 16;
const sal_Int32 NMSP_CHART                  = 23 << 16;
const sal_Int32 NMSP_VML                    = 24 << 16;
// WordML
const sal_Int32 NMSP_WORD                   = 31 << 16; // Word VML
// SpreadsheetML
const sal_Int32 NMSP_XLS                    = 41 << 16;
const sal_Int32 NMSP_XDR                    = 42 << 16; // SpreadsheetDrawingML
const sal_Int32 NMSP_XM                     = 43 << 16; // Macro sheet
const sal_Int32 NMSP_EXCEL                  = 44 << 16; // Excel VML
// PresentationML
const sal_Int32 NMSP_PPT                    = 51 << 16;
const sal_Int32 NMSP_POWERPOINT             = 52 << 16; // PowerPoint VML

// ----------------------------------------------------------------------------

const sal_Int32 TOKEN_MASK                  = SAL_MAX_UINT16;
const sal_Int32 NMSP_MASK                   = SAL_MAX_INT16 << 16;

/** Returns the token identifier of the passed element without namespace. */
inline sal_Int32 getToken( sal_Int32 nElement ) { return nElement & TOKEN_MASK; }

/** Returns the namespace of the passed element without token identifier. */
inline sal_Int32 getNamespace( sal_Int32 nElement ) { return nElement & NMSP_MASK; }

// ============================================================================

} // namespace oox

#endif // OOX_CORE_NAMESPACES_HXX

