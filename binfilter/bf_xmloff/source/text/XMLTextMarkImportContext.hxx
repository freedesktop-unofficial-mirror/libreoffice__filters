/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: XMLTextMarkImportContext.hxx,v $
 *
 *  $Revision: 1.2 $
 *
 *  last change: $Author: rt $ $Date: 2005-09-09 10:12:00 $
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


#ifndef _XMLOFF_XMLTEXTMARKIMPORTCONTEXT_HXX
#define _XMLOFF_XMLTEXTMARKIMPORTCONTEXT_HXX

#ifndef _XMLOFF_XMLICTXT_HXX
#include "xmlictxt.hxx"
#endif

#ifndef _COM_SUN_STAR_UNO_REFERENCE_H_ 
#include <com/sun/star/uno/Reference.h>
#endif


namespace com { namespace sun { namespace star {
    namespace text {
        class XTextRange;
    }
    namespace xml { namespace sax {
        class XAttributeList;
    } }
} } }
namespace rtl {
    class OUString;
}
namespace binfilter {
class XMLTextImportHelper;


/**
 * import bookmarks and reference marks
 * ( <bookmark>, <bookmark-start>, <bookmark-end>,
 *   <reference>, <reference-start>, <reference-end> )
 * 
 * All elements are handled by the same class due to their similarities.
 */
class XMLTextMarkImportContext : public SvXMLImportContext
{
    
    XMLTextImportHelper& rHelper;

public:
    
    TYPEINFO();

    XMLTextMarkImportContext(
        SvXMLImport& rImport, 
        XMLTextImportHelper& rHlp,
        sal_uInt16 nPrfx,
        const ::rtl::OUString& rLocalName );

protected:

    virtual void StartElement(
        const ::com::sun::star::uno::Reference< 
            ::com::sun::star::xml::sax::XAttributeList> & xAttrList);

public:
    static void CreateAndInsertMark(
        SvXMLImport& rImport,
        const ::rtl::OUString& sServiceName,
        const ::rtl::OUString& sMarkName,
        const ::com::sun::star::uno::Reference<
            ::com::sun::star::text::XTextRange> & rRange);

    static sal_Bool FindName(
        SvXMLImport& rImport,
        const ::com::sun::star::uno::Reference<
            ::com::sun::star::xml::sax::XAttributeList> & xAttrList,
        ::rtl::OUString& sName);
};

}//end of namespace binfilter
#endif
