/*************************************************************************
 *
 *  $RCSfile: zforauto.hxx,v $
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

#ifndef _ZFORAUTO_HXX_
#define _ZFORAUTO_HXX_

#ifndef _STRING_HXX //autogen
#include <tools/string.hxx>
#endif

#ifndef _LANG_HXX //autogen
#include <tools/lang.hxx>
#endif


//STRIP001 class SvStream;
//STRIP001 class SvNumberFormatter;


class ScNumFormatAbbrev
{
    String sFormatstring;
    LanguageType eLnge;
    LanguageType eSysLnge;
public:
    ScNumFormatAbbrev();
    ScNumFormatAbbrev(const ScNumFormatAbbrev& aFormat);
    ScNumFormatAbbrev(SvStream& rStream);
    ScNumFormatAbbrev(ULONG nFormat, SvNumberFormatter& rFormatter) {DBG_ASSERT(0, "STRIP"); } //STRIP001 	ScNumFormatAbbrev(ULONG nFormat, SvNumberFormatter& rFormatter);
    void Load( SvStream& rStream );			// Laden der Zahlenformate
    void Save( SvStream& rStream ) const;	// Speichern der Zahlenformate
//STRIP001 	void PutFormatIndex(ULONG nFormat, SvNumberFormatter& rFormatter);
//STRIP001     ULONG GetFormatIndex( SvNumberFormatter& rFormatter);
//STRIP001     inline int operator==(const ScNumFormatAbbrev& rNumFormat) const
//STRIP001 	{
//STRIP001 		return ((sFormatstring == rNumFormat.sFormatstring)
//STRIP001 			&& (eLnge == rNumFormat.eLnge)
//STRIP001 			&& (eSysLnge == rNumFormat.eSysLnge));
//STRIP001 	}
//STRIP001 	inline ScNumFormatAbbrev& operator=(const ScNumFormatAbbrev& rNumFormat)
//STRIP001 	{
//STRIP001 		sFormatstring = rNumFormat.sFormatstring;
//STRIP001 		eLnge = rNumFormat.eLnge;
//STRIP001 		eSysLnge = rNumFormat.eSysLnge;
//STRIP001 		return *this;
//STRIP001 	}
//STRIP001 	inline LanguageType GetLanguage() const { return eLnge; }
};



#endif


