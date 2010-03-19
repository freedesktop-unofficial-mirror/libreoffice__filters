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
#ifndef _SWFTLOPT_HXX
#define _SWFTLOPT_HXX

#ifndef _UTL_CONFIGITEM_HXX_
#include <unotools/configitem.hxx>
#endif
namespace binfilter {

class SwFilterOptions : public ::utl::ConfigItem
{
public:
    SwFilterOptions();
    SwFilterOptions( sal_uInt16 nCnt, const sal_Char** ppNames,
                      sal_uInt32* pValues );

    sal_Bool CheckNodeContentExist( const sal_Char* pNode,
                                 const sal_Char* pCntnt );

    void GetValues( sal_uInt16 nCnt, const sal_Char** ppNames,
                     sal_uInt32* pValues );
};

} //namespace binfilter
#endif
