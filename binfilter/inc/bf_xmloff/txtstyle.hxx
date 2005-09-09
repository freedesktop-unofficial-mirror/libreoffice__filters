/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: txtstyle.hxx,v $
 *
 *  $Revision: 1.3 $
 *
 *  last change: $Author: rt $ $Date: 2005-09-09 17:36:00 $
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
#ifndef _XMLOFF_TEXTSTYLE_HXX_
#define _XMLOFF_TEXTSTYLE_HXX_

#ifndef _XMLOFF_STYLEEXP_HXX_
#include <bf_xmloff/styleexp.hxx>
#endif
#ifndef _UNIVERSALL_REFERENCE_HXX
#include <bf_xmloff/uniref.hxx>
#endif
namespace binfilter {

class XMLPropertySetMapper;

class XMLTextStyleExport : public XMLStyleExport
{
    UniReference < XMLPropertySetMapper > xParaPropMapper;

    void exportNumStyles( sal_Bool bUsed );

public:

    XMLTextStyleExport(
        SvXMLExport& rExp,
//		const ::com::sun::star::uno::Reference<
//				::com::sun::star::xml::sax::XDocumentHandler > & rHandler,
//		const ::com::sun::star::uno::Reference<
//				::com::sun::star::frame::XModel > & rModel,
        const ::rtl::OUString& rPoolStyleName,
//		const SvXMLNamespaceMap &rNamespaceMap,
//	 	MapUnit eDUnit,
        SvXMLAutoStylePoolP *pAutoStyleP=0 );
    virtual ~XMLTextStyleExport();

    void exportStyles( sal_Bool bUsed );

    UniReference < XMLPropertySetMapper >& getParaPropMapper();
};

}//end of namespace binfilter
#endif
