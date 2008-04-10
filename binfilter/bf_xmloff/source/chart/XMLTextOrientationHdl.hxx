/*************************************************************************
 *
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER.
 * 
 * Copyright 2008 by Sun Microsystems, Inc.
 *
 * OpenOffice.org - a multi-platform office productivity suite
 *
 * $RCSfile: XMLTextOrientationHdl.hxx,v $
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
#ifndef _XMLTEXTORIENTATIONHDL_HXX_
#define _XMLTEXTORIENTATIONHDL_HXX_

#ifndef _XMLOFF_PROPERTYHANDLERBASE_HXX
#include "xmlprhdl.hxx"
#endif
namespace binfilter {

class XMLTextOrientationHdl : public XMLPropertyHandler
{
private:
public:
    virtual ~XMLTextOrientationHdl();
    
    virtual sal_Bool importXML( const ::rtl::OUString& rStrImpValue,
                                ::com::sun::star::uno::Any& rValue,
                                const SvXMLUnitConverter& rUnitConverter ) const;
    virtual sal_Bool exportXML( ::rtl::OUString& rStrExpValue,
                                const ::com::sun::star::uno::Any& rValue,
                                const SvXMLUnitConverter& rUnitConverter ) const;
};

}//end of namespace binfilter
#endif	// _XMLTEXTORIENTATIONHDL_HXX_
