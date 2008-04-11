/*************************************************************************
 *
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER.
 * 
 * Copyright 2008 by Sun Microsystems, Inc.
 *
 * OpenOffice.org - a multi-platform office productivity suite
 *
 * $RCSfile: XMLConstantsPropertyHandler.hxx,v $
 * $Revision: 1.4 $
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

#ifndef _XMLOFF_XMLCONSTANTSPROPERTYHANDLER_HXX
#define _XMLOFF_XMLCONSTANTSPROPERTYHANDLER_HXX

#ifndef _XMLOFF_PROPERTYHANDLERBASE_HXX
#include "xmlprhdl.hxx"
#endif

#ifndef _XMLOFF_XMLTOKEN_HXX
#include "xmltoken.hxx"
#endif
namespace binfilter {

struct SvXMLEnumMapEntry;

///////////////////////////////////////////////////////////////////////////
//
/** Abstract base-class for different XML-types. Derivations of this class
    knows how to compare, im/export a special XML-type
*/
class XMLConstantsPropertyHandler: public XMLPropertyHandler
{
    const SvXMLEnumMapEntry *pMap;
    const enum ::binfilter::xmloff::token::XMLTokenEnum eDefault;

public:

    XMLConstantsPropertyHandler( const SvXMLEnumMapEntry *pM,
                                 enum ::binfilter::xmloff::token::XMLTokenEnum eDflt);


    // Just needed for virtual destruction
    virtual ~XMLConstantsPropertyHandler();

    /// Imports the given value in cas of the given XML-data-type
    virtual sal_Bool importXML(
            const ::rtl::OUString& rStrImpValue,
            ::com::sun::star::uno::Any& rValue,
            const SvXMLUnitConverter& rUnitConverter ) const;

    /// Exports the given value in cas of the given XML-data-type
    virtual sal_Bool exportXML(
            ::rtl::OUString& rStrExpValue,
            const ::com::sun::star::uno::Any& rValue,
            const SvXMLUnitConverter& rUnitConverter ) const;
};

}//end of namespace binfilter
#endif		// _XMLOFF_XMLCONSTANTSPROPERTYHANDLER_HXX
