/*************************************************************************
 *
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER.
 * 
 * Copyright 2008 by Sun Microsystems, Inc.
 *
 * OpenOffice.org - a multi-platform office productivity suite
 *
 * $RCSfile: tablestylelist.hxx,v $
 *
 * $Revision: 1.2 $
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

#ifndef OOX_DRAWINGML_TABLESTYLELIST_HXX
#define OOX_DRAWINGML_TABLESTYLELIST_HXX

#include <rtl/ustring.hxx>
#include <boost/shared_ptr.hpp>
#include "oox/drawingml/table/tablestyle.hxx"
#include <vector>

namespace oox { namespace drawingml { namespace table {

class TableStyleList
{
public:

    TableStyleList();
    ~TableStyleList();

    rtl::OUString&				getDefaultStyleId() { return maDefaultStyleId; };
    std::vector< TableStyle >&	getTableStyles(){ return maTableStyles; };

private:

    rtl::OUString				maDefaultStyleId;
    std::vector< TableStyle >	maTableStyles;

};

typedef boost::shared_ptr< TableStyleList > TableStyleListPtr;

} } }

#endif  //  OOX_DRAWINGML_TABLESTYLELIST_HXX
