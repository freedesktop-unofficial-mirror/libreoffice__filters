/*************************************************************************
 *
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER.
 * 
 * Copyright 2008 by Sun Microsystems, Inc.
 *
 * OpenOffice.org - a multi-platform office productivity suite
 *
 * $RCSfile: restrictedpaths.hxx,v $
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

#ifndef SVTOOLS_RESTRICTEDPATHS_HXX
#define SVTOOLS_RESTRICTEDPATHS_HXX

#ifndef SVTOOLS_URL_FILTER_HXX
#include <bf_svtools/urlfilter.hxx>
#endif

#ifndef INCLUDED_SVTDLLAPI_H
#include <bf_svtools/svtdllapi.h>
#endif

#ifndef _STRING_HXX
#include <tools/string.hxx>
#endif

#include <vector>

namespace binfilter
{
    class  RestrictedPaths : public IUrlFilter
    {
    private:
        ::std::vector< String >     m_aUnrestrictedURLs;
        bool                        m_bFilterIsEnabled;

    public:
        RestrictedPaths();
        virtual ~RestrictedPaths();

        inline bool hasFilter() const { return !m_aUnrestrictedURLs.empty(); }
        inline const ::std::vector< String >& getFilter() const { return m_aUnrestrictedURLs; }

        inline void enableFilter( bool _bEnable ) { m_bFilterIsEnabled = _bEnable; }
        inline bool isFilterEnabled() const { return m_bFilterIsEnabled; }

    public:
        /** checks URL access permissions

            <p>with the "restriction" feature we have in the file dialog, it's possible that
            only certain URLs can be browsed. This method checks whether a given URL belongs
            to this set of permitted URLs.</p>

            <p>If no "access restriction" is effective, this method always returns <TRUE/>.</p>
        */
        virtual bool                isUrlAllowed( const String& _rURL ) const;

        /** checks URL access permissions

            <p>with the "restriction" feature we have in the file dialog, it's possible that
            only certain URLs can be browsed. This method checks whether a given URL belongs
            to this set of permitted URLs.</p>

            <p>Default behavior allows access to parent folder of a restricted folder (but not to its siblings).
            If allowParents is set to <FALSE/> parent folders will be treated as forbidden.

            <p>If no "access restriction" is effective, this method always returns <TRUE/>.</p>
        */
        bool                        isUrlAllowed( const String& _rURL, bool allowParents ) const;
    };

}

#endif  // SVTOOLS_RESTRICTEDPATHS_HXX
