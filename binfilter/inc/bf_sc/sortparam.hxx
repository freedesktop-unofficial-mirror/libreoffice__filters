/*************************************************************************
 *
 *  $RCSfile: sortparam.hxx,v $
 *
 *  $Revision: 1.1.1.1 $
 *
 *  last change: $Author: hjs $ $Date: 2003-10-01 12:23:22 $
 *
 *  The Contents of this file are made available subject to the terms of
 *  either of the following licenses
 *
 *         - GNU Lesser General Public License Version 2.1
 *         - Sun Industry Standards Source License Version 1.1
 *
 *  Sun Microsystems Inc., October, 2000
 *
 *  GNU Lesser General Public License Version 2.1
 *  =============================================
 *  Copyright 2000 by Sun Microsystems, Inc.
 *  901 San Antonio Road, Palo Alto, CA 94303, USA
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public
 *  License version 2.1, as published by the Free Software Foundation.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public
 *  License along with this library; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 *  MA  02111-1307  USA
 *
 *
 *  Sun Industry Standards Source License Version 1.1
 *  =================================================
 *  The contents of this file are subject to the Sun Industry Standards
 *  Source License Version 1.1 (the "License"); You may not use this file
 *  except in compliance with the License. You may obtain a copy of the
 *  License at http://www.openoffice.org/license.html.
 *
 *  Software provided under this License is provided on an "AS IS" basis,
 *  WITHOUT WARRANTY OF ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING,
 *  WITHOUT LIMITATION, WARRANTIES THAT THE SOFTWARE IS FREE OF DEFECTS,
 *  MERCHANTABLE, FIT FOR A PARTICULAR PURPOSE, OR NON-INFRINGING.
 *  See the License for the specific provisions governing your rights and
 *  obligations concerning the Software.
 *
 *  The Initial Developer of the Original Code is: Sun Microsystems, Inc.
 *
 *  Copyright: 2000 by Sun Microsystems, Inc.
 *
 *  All Rights Reserved.
 *
 *  Contributor(s): _______________________________________
 *
 *
 ************************************************************************/

#ifndef SC_SORTPARAM_HXX
#define SC_SORTPARAM_HXX

#ifndef _STRING_HXX
#include <tools/string.hxx>
#endif
#ifndef _SOLAR_H
#include <tools/solar.h>
#endif
#ifndef _COM_SUN_STAR_LANG_LOCALE_HPP_
#include <com/sun/star/lang/Locale.hpp>
#endif


#define MAXSORT		3


struct ScSubTotalParam;
struct ScQueryParam;

struct ScSortParam
{
    USHORT		nCol1;
    USHORT		nRow1;
    USHORT		nCol2;
    USHORT		nRow2;
    BOOL		bHasHeader;
    BOOL		bByRow;
    BOOL		bCaseSens;
    BOOL		bUserDef;
    USHORT		nUserIndex;
    BOOL		bIncludePattern;
    BOOL		bInplace;
    USHORT		nDestTab;
    USHORT		nDestCol;
    USHORT		nDestRow;
    BOOL		bDoSort[MAXSORT];
    USHORT		nField[MAXSORT];
    BOOL		bAscending[MAXSORT];
    ::com::sun::star::lang::Locale		aCollatorLocale;
    String		aCollatorAlgorithm;

    ScSortParam();
    ScSortParam( const ScSortParam& r );
    /// SubTotals sort
//STRIP001 	ScSortParam( const ScSubTotalParam& rSub, const ScSortParam& rOld );
    /// TopTen sort
//STRIP001 	ScSortParam( const ScQueryParam&, USHORT nCol );

//STRIP001 	ScSortParam&	operator=	( const ScSortParam& r );
//STRIP001 	BOOL			operator==	( const ScSortParam& rOther ) const;
    void			Clear		();

//STRIP001 	void			MoveToDest();
};


#endif // SC_SORTPARAM_HXX
