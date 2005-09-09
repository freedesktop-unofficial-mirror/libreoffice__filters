/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: XMLIndexSimpleEntryContext.hxx,v $
 *
 *  $Revision: 1.2 $
 *
 *  last change: $Author: rt $ $Date: 2005-09-09 10:05:21 $
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

#ifndef _XMLOFF_XMLINDEXSIMPLEENTRYCONTEXT_HXX_
#define _XMLOFF_XMLINDEXSIMPLEENTRYCONTEXT_HXX_

#ifndef _XMLOFF_XMLICTXT_HXX 
#include "xmlictxt.hxx"
#endif

#ifndef _COM_SUN_STAR_UNO_REFERENCE_H_ 
#include <com/sun/star/uno/Reference.h>
#endif

#ifndef _COM_SUN_STAR_UNO_SEQUENCE_H_
#include <com/sun/star/uno/Sequence.h>
#endif

#ifndef _COM_SUN_STAR_BEANS_PROPERTYVALUE_HPP_
#include <com/sun/star/beans/PropertyValue.hpp>
#endif


namespace com { namespace sun { namespace star {
    namespace xml { namespace sax { class XAttributeList; } }
} } }
namespace rtl {	class OUString; }
namespace binfilter {
class XMLIndexTemplateContext;

/**
 * Import index entry templates
 */
class XMLIndexSimpleEntryContext : public SvXMLImportContext
{

    // entry type	
    const ::rtl::OUString& rEntryType;

protected:
    // character style
    ::rtl::OUString sCharStyleName;
    sal_Bool bCharStyleNameOK;

    // surrounding template
    XMLIndexTemplateContext& rTemplateContext;
    
    // number of values for PropertyValues
    sal_Int32 nValues;

public:

    TYPEINFO();

    XMLIndexSimpleEntryContext(
        SvXMLImport& rImport, 
        const ::rtl::OUString& rEntry,
        XMLIndexTemplateContext& rTemplate,
        sal_uInt16 nPrfx,
        const ::rtl::OUString& rLocalName );

    ~XMLIndexSimpleEntryContext();

protected:

    /** process parameters */
    virtual void StartElement(
        const ::com::sun::star::uno::Reference< 
            ::com::sun::star::xml::sax::XAttributeList> & xAttrList);

    /** call FillPropertyValues and insert into template */
    virtual void EndElement();

    /** fill property values for this template entry */
    virtual void FillPropertyValues(
        ::com::sun::star::uno::Sequence<
            ::com::sun::star::beans::PropertyValue> & rValues);

};

}//end of namespace binfilter
#endif
