/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: XMLIsPercentagePropertyHandler.hxx,v $
 *
 *  $Revision: 1.3 $
 *
 *  last change: $Author: rt $ $Date: 2005-09-09 17:22:32 $
 *
 *  The Contents of this file are made available subject to
 *  the terms of GNU Lesser General Public License Version 2.1.
 *
 *
 *    GNU Lesser General Public License Version 2.1
 *    =============================================
 *    Copyright 2005 by Sun Microsystems, Inc.
 *    901 San Antonio Road, Palo Alto, CA 94303, USA
 *
 *    This library is free software; you can redistribute it and/or
 *    modify it under the terms of the GNU Lesser General Public
 *    License version 2.1, as published by the Free Software Foundation.
 *
 *    This library is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *    Lesser General Public License for more details.
 *
 *    You should have received a copy of the GNU Lesser General Public
 *    License along with this library; if not, write to the Free Software
 *    Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 *    MA  02111-1307  USA
 *
 ************************************************************************/

#ifndef _XMLOFF_XMLISPERCENTAGEPROPERTYHANDLER_HXX
#define _XMLOFF_XMLISPERCENTAGEPROPERTYHANDLER_HXX

#ifndef _XMLOFF_PROPERTYHANDLERBASE_HXX
#include <xmlprhdl.hxx>
#endif
namespace binfilter {

/**
    This is a handler that returns true for import if the attribute string
    contains a '%' value. For export this is only usable for filtering.
*/
class XMLIsPercentagePropertyHandler : public XMLPropertyHandler
{
public:
    virtual ~XMLIsPercentagePropertyHandler ();

    virtual sal_Bool importXML(
            const ::rtl::OUString& rStrImpValue,
            ::com::sun::star::uno::Any& rValue,
            const SvXMLUnitConverter& rUnitConverter ) const;
    virtual sal_Bool exportXML(
            ::rtl::OUString& rStrExpValue,
            const ::com::sun::star::uno::Any& rValue,
            const SvXMLUnitConverter& rUnitConverter ) const;
};

}//end of namespace binfilter
#endif
