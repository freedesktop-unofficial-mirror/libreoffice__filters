/*************************************************************************
 *
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER.
 * 
 * Copyright 2008 by Sun Microsystems, Inc.
 *
 * OpenOffice.org - a multi-platform office productivity suite
 *
 * $RCSfile: javaoptions.hxx,v $
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
#ifndef _SVTOOLS_JAVAOPTIONS_HXX
#define _SVTOOLS_JAVAOPTIONS_HXX

#ifndef _SAL_TYPES_H_
#include <sal/types.h>
#endif

#ifndef _UTL_CONFIGITEM_HXX_
#include <unotools/configitem.hxx>
#endif

namespace binfilter
{

// class SvtJavaOptions --------------------------------------------------

struct SvtJavaOptions_Impl;

class  SvtJavaOptions : public utl::ConfigItem
{
    SvtJavaOptions_Impl* pImpl;
public:
    enum EOption
    {
        E_ENABLED,
        E_SECURITY,
        E_NETACCESS,
        E_USERCLASSPATH,
        E_EXECUTEAPPLETS
    };

    SvtJavaOptions();
    ~SvtJavaOptions();

    virtual void    Commit();

    sal_Bool        IsEnabled() const;
    sal_Bool        IsSecurity()const;
    sal_Int32       GetNetAccess() const;
    rtl::OUString&  GetUserClassPath()const;
    sal_Bool        IsExecuteApplets() const;

    void SetEnabled(sal_Bool bSet) ;
    void SetSecurity(sal_Bool bSet);
    void SetNetAccess(sal_Int32 nSet) ;
    void SetUserClassPath(const rtl::OUString& rSet);
    void SetExecuteApplets(sal_Bool bSet);

    sal_Bool IsReadOnly( EOption eOption ) const;
};

}

#endif //

