/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: SchXMLParagraphContext.hxx,v $
 *
 *  $Revision: 1.2 $
 *
 *  last change: $Author: rt $ $Date: 2005-09-09 07:33:50 $
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
#ifndef _SCH_XMLPARAGRAPHCONTEXT_HXX_
#define _SCH_XMLPARAGRAPHCONTEXT_HXX_

#ifndef _XMLOFF_XMLICTXT_HXX
#include "xmlictxt.hxx"
#endif

#ifndef _RTL_USTRING_HXX_
#include "rtl/ustring.hxx"
#endif
#ifndef _RTL_USTRBUF_HXX_
#include "rtl/ustrbuf.hxx"
#endif
namespace com { namespace sun { namespace star { namespace xml { namespace sax {
        class XAttributeList;
}}}}}
namespace binfilter {

class SchXMLImport;


class SchXMLParagraphContext : public SvXMLImportContext
{
private:
    ::rtl::OUString& mrText;
    ::rtl::OUStringBuffer maBuffer;

public:
    SchXMLParagraphContext( SvXMLImport& rImport,
                            const ::rtl::OUString& rLocalName,
                            ::rtl::OUString& rText );
    virtual ~SchXMLParagraphContext();	
    virtual void EndElement();
    
    virtual SvXMLImportContext* CreateChildContext(
        USHORT nPrefix,
        const ::rtl::OUString& rLocalName,
        const ::com::sun::star::uno::Reference< ::com::sun::star::xml::sax::XAttributeList >& xAttrList );

    virtual void Characters( const ::rtl::OUString& rChars );
};

}//end of namespace binfilter
#endif	// _SCH_XMLPARAGRAPHCONTEXT_HXX_
