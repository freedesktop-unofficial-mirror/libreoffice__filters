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

#ifndef OOX_VML_VMLDRAWINGFRAGMENT_HXX
#define OOX_VML_VMLDRAWINGFRAGMENT_HXX

#include "oox/core/fragmenthandler2.hxx"

namespace oox {
namespace vml {

class Drawing;

// ============================================================================

class DrawingFragment : public ::oox::core::FragmentHandler2
{
public:
    explicit            DrawingFragment(
                            ::oox::core::XmlFilterBase& rFilter,
                            const ::rtl::OUString& rFragmentPath,
                            Drawing& rDrawing );

    virtual ::com::sun::star::uno::Reference< ::com::sun::star::io::XInputStream >
                        openFragmentStream() const;

    virtual ::oox::core::ContextHandlerRef
                        onCreateContext( sal_Int32 nElement, const AttributeList& rAttribs );

    virtual void        finalizeImport();

private:
    Drawing&            mrDrawing;
};

// ============================================================================

} // namespace vml
} // namespace oox

#endif
