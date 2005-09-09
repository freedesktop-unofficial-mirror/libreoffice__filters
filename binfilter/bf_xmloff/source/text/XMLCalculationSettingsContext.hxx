/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: XMLCalculationSettingsContext.hxx,v $
 *
 *  $Revision: 1.2 $
 *
 *  last change: $Author: rt $ $Date: 2005-09-09 10:01:26 $
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

#ifndef _XMLOFF_XMLCALCULATIONSETTINGSCONTEXT_HXX
#define _XMLOFF_XMLCALCULATIONSETTINGSCONTEXT_HXX

#ifndef _XMLOFF_XMLICTXT_HXX
#include "xmlictxt.hxx"
#endif
namespace binfilter {

class XMLCalculationSettingsContext : public SvXMLImportContext
{
    sal_Int16 nYear;
public:
    XMLCalculationSettingsContext( SvXMLImport& rImport, 
                                    sal_uInt16 nPrefix,
                                    const ::rtl::OUString& rLocalName,
                                     const ::com::sun::star::uno::Reference<
                                         ::com::sun::star::xml::sax::XAttributeList >& xAttrList );

    virtual ~XMLCalculationSettingsContext();
    virtual void EndElement();

};


}//end of namespace binfilter
#endif
