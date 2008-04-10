/*************************************************************************
 *
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER.
 * 
 * Copyright 2008 by Sun Microsystems, Inc.
 *
 * OpenOffice.org - a multi-platform office productivity suite
 *
 * $RCSfile: cjkoptions.hxx,v $
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
#ifndef _SVTOOLS_CJKOPTIONS_HXX
#define _SVTOOLS_CJKOPTIONS_HXX

#ifndef INCLUDED_SVTDLLAPI_H
#include "bf_svtools/svtdllapi.h"
#endif

#ifndef _SAL_TYPES_H_
#include <sal/types.h>
#endif
#ifndef INCLUDED_SVTOOLS_OPTIONS_HXX
#include <bf_svtools/options.hxx>
#endif

namespace binfilter {

class SvtCJKOptions_Impl;

// class SvtCJKOptions --------------------------------------------------

class  SvtCJKOptions: public Options
{
private:
    SvtCJKOptions_Impl*    pImp;

public:

    enum EOption
    {
        E_CJKFONT,
        E_VERTICALTEXT,
        E_ASIANTYPOGRAPHY,
        E_JAPANESEFIND,
        E_RUBY,
        E_CHANGECASEMAP,
        E_DOUBLELINES,
        E_EMPHASISMARKS,
        E_VERTICALCALLOUT,
        E_ALL               // special one for IsAnyEnabled()/SetAll() functionality
    };

    // bDontLoad is for referencing purposes only
    SvtCJKOptions(sal_Bool bDontLoad = sal_False);
    virtual ~SvtCJKOptions();

    sal_Bool IsCJKFontEnabled() const;
    sal_Bool IsVerticalTextEnabled() const;
    sal_Bool IsAsianTypographyEnabled() const;
    sal_Bool IsJapaneseFindEnabled() const;
    sal_Bool IsRubyEnabled() const;
    sal_Bool IsChangeCaseMapEnabled() const;
    sal_Bool IsDoubleLinesEnabled() const;
    sal_Bool IsEmphasisMarksEnabled() const;
    sal_Bool IsVerticalCallOutEnabled() const;

    void        SetAll(sal_Bool bSet);
    sal_Bool    IsAnyEnabled() const;
    sal_Bool    IsReadOnly(EOption eOption) const;
};

}

#endif // _SVTOOLS_CJKOPTIONS_HXX

