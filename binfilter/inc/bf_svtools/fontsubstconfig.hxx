/*************************************************************************
 *
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER.
 * 
 * Copyright 2008 by Sun Microsystems, Inc.
 *
 * OpenOffice.org - a multi-platform office productivity suite
 *
 * $RCSfile: fontsubstconfig.hxx,v $
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
#ifndef _SVT_FONTSUBSTCONFIG_HXX
#define _SVT_FONTSUBSTCONFIG_HXX

#ifndef INCLUDED_SVTDLLAPI_H
#include "bf_svtools/svtdllapi.h"
#endif

#ifndef _UTL_CONFIGITEM_HXX_
#include <unotools/configitem.hxx>
#endif

namespace binfilter
{

struct SvtFontSubstConfig_Impl;

//-----------------------------------------------------------------------------
struct SubstitutionStruct
{
    rtl::OUString 	sFont;
    rtl::OUString 	sReplaceBy;
    sal_Bool		bReplaceAlways;
    sal_Bool		bReplaceOnScreenOnly;
};
//-----------------------------------------------------------------------------
class  SvtFontSubstConfig : public utl::ConfigItem
{
    sal_Bool					bIsEnabled;
    SvtFontSubstConfig_Impl*	pImpl;
public:
    SvtFontSubstConfig();
    virtual ~SvtFontSubstConfig();

    virtual void			Commit();

    sal_Bool 				IsEnabled() const {return bIsEnabled;}
    void	 				Enable(sal_Bool bSet)  {bIsEnabled = bSet; SetModified();}

    sal_Int32					SubstitutionCount() const;
    void						ClearSubstitutions();
    const SubstitutionStruct*	GetSubstitution(sal_Int32 nPos);
    void						AddSubstitution(const SubstitutionStruct&	rToAdd);
    void						Apply();
};

}

#endif



