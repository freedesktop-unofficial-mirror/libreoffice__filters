/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: XMLSectionFootnoteConfigImport.hxx,v $
 *
 *  $Revision: 1.2 $
 *
 *  last change: $Author: rt $ $Date: 2005-09-09 10:09:41 $
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


#ifndef _XMLOFF_XMLSECTIONFOOTNOTECONFIGIMPORT_HXX
#define _XMLOFF_XMLSECTIONFOOTNOTECONFIGIMPORT_HXX


#ifndef _XMLOFF_XMLICTXT_HXX
#include "xmlictxt.hxx"
#endif

#ifndef _UNIVERSALL_REFERENCE_HXX
#include "uniref.hxx"
#endif

#include <vector>


namespace rtl { class OUString; }
namespace com { namespace sun { namespace star {
    namespace uno { template<class X> class Reference; }
    namespace xml { namespace sax { class XAttributeList; } }
} } }

namespace binfilter {
class SvXMLImport;
struct XMLPropertyState;
class XMLPropertySetMapper;

/**
 * Import the footnote-/endnote-configuration element in section styles.
 */
class XMLSectionFootnoteConfigImport : public SvXMLImportContext
{
    ::std::vector<XMLPropertyState> & rProperties;
    UniReference<XMLPropertySetMapper> rMapper;
    sal_Int32 nPropIndex;

public:
    
    TYPEINFO();

    XMLSectionFootnoteConfigImport(
        SvXMLImport& rImport, 
        sal_uInt16 nPrefix, 
        const ::rtl::OUString& rLocalName, 
        ::std::vector<XMLPropertyState> & rProperties,
        const UniReference<XMLPropertySetMapper> & rMapperRef,
        sal_Int32 nIndex);

    ~XMLSectionFootnoteConfigImport();

    virtual void StartElement( 
        const ::com::sun::star::uno::Reference<
                ::com::sun::star::xml::sax::XAttributeList> & xAttrList );

};

}//end of namespace binfilter
#endif
