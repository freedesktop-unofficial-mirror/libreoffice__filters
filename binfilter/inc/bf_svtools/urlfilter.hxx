/*************************************************************************
 *
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER.
 * 
 * Copyright 2008 by Sun Microsystems, Inc.
 *
 * OpenOffice.org - a multi-platform office productivity suite
 *
 * $RCSfile: urlfilter.hxx,v $
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

#ifndef SVTOOLS_URL_FILTER_HXX
#define SVTOOLS_URL_FILTER_HXX

#ifndef _STRING_HXX
#include <tools/string.hxx>
#endif
#ifndef _WLDCRD_HXX
#include <tools/wldcrd.hxx>
#endif
#include <functional>
#include <vector>

namespace binfilter
{

/** filters allowed URLs
*/
class IUrlFilter
{
public:
    virtual bool isUrlAllowed( const String& _rURL ) const = 0;

protected:
    virtual inline ~IUrlFilter() = 0;
};

inline IUrlFilter::~IUrlFilter() {}

struct FilterMatch : public ::std::unary_function< bool, WildCard >
{
private:
    const String&	m_rCompareString;
public:
    FilterMatch( const String& _rCompareString ) : m_rCompareString( _rCompareString ) { }

    bool operator()( const WildCard& _rMatcher )
    {
        return _rMatcher.Matches( m_rCompareString ) ? true : false;
    }

    static void createWildCardFilterList(const String& _rFilterList,::std::vector< WildCard >& _rFilters);
};

}

#endif // SVTOOLS_URL_FILTER_HXX
