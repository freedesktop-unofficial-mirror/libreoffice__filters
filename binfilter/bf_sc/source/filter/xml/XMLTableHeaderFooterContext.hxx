/*************************************************************************
 *
 *  $RCSfile: XMLTableHeaderFooterContext.hxx,v $
 *
 *  $Revision: 1.1.1.1 $
 *
 *  last change: $Author: hjs $ $Date: 2003-10-01 12:18:07 $
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
#ifndef _SC_XMLTABLEHEADERFOOTERCONTEXT_HXX_
#define _SC_XMLTABLEHEADERFOOTERCONTEXT_HXX_


#ifndef _XMLOFF_XMLICTXT_HXX_
#include <xmloff/xmlictxt.hxx>
#endif

#ifndef _XMLOFF_XMLIMP_HXX_
#include <xmloff/xmlimp.hxx>
#endif
#ifndef _COM_SUN_STAR_SHEET_XHEADERFOOTERCONTENT_HPP_
#include <com/sun/star/sheet/XHeaderFooterContent.hpp>
#endif

namespace com { namespace sun { namespace star {
    namespace text { class XTextCursor; }
    namespace beans { class XPropertySet; }
} } }

class XMLTableHeaderFooterContext: public SvXMLImportContext
{
    ::com::sun::star::uno::Reference <
        ::com::sun::star::text::XTextCursor > xTextCursor;
    ::com::sun::star::uno::Reference <
        ::com::sun::star::text::XTextCursor > xOldTextCursor;
    ::com::sun::star::uno::Reference <
        ::com::sun::star::beans::XPropertySet > xPropSet;
    ::com::sun::star::uno::Reference <
        ::com::sun::star::sheet::XHeaderFooterContent > xHeaderFooterContent;

    const ::rtl::OUString	sOn;
    const ::rtl::OUString	sShareContent;
    const ::rtl::OUString	sContent;
    const ::rtl::OUString	sContentLeft;
    const ::rtl::OUString	sEmpty;
    rtl::OUString			sCont;

    sal_Bool	bDisplay : 1;
    sal_Bool	bInsertContent : 1;
    sal_Bool 	bLeft : 1;
    sal_Bool	bContainsLeft : 1;
    sal_Bool	bContainsRight : 1;
    sal_Bool	bContainsCenter : 1;

public:
    TYPEINFO();

    XMLTableHeaderFooterContext( SvXMLImport& rImport, sal_uInt16 nPrfx,
            const ::rtl::OUString& rLName,
            const ::com::sun::star::uno::Reference<
                    ::com::sun::star::xml::sax::XAttributeList > & xAttrList,
            const ::com::sun::star::uno::Reference <
                       ::com::sun::star::beans::XPropertySet > & rPageStylePropSet,
               sal_Bool bFooter, sal_Bool bLft );

    virtual ~XMLTableHeaderFooterContext();

    virtual SvXMLImportContext *CreateChildContext(
            sal_uInt16 nPrefix,
            const ::rtl::OUString& rLocalName,
            const ::com::sun::star::uno::Reference< ::com::sun::star::xml::sax::XAttributeList > & xAttrList );

    virtual void EndElement();
};

class XMLHeaderFooterRegionContext: public SvXMLImportContext
{
private:
    ::com::sun::star::uno::Reference <
        ::com::sun::star::text::XTextCursor >& xTextCursor;
    ::com::sun::star::uno::Reference <
        ::com::sun::star::text::XTextCursor > xOldTextCursor;

public:
    TYPEINFO();

    XMLHeaderFooterRegionContext( SvXMLImport& rImport, sal_uInt16 nPrfx,
            const ::rtl::OUString& rLName,
            const ::com::sun::star::uno::Reference<
                    ::com::sun::star::xml::sax::XAttributeList > & xAttrList,
            com::sun::star::uno::Reference< com::sun::star::text::XTextCursor >& xCursor );

    virtual ~XMLHeaderFooterRegionContext();

    virtual SvXMLImportContext *CreateChildContext(
            sal_uInt16 nPrefix,
            const ::rtl::OUString& rLocalName,
            const ::com::sun::star::uno::Reference< ::com::sun::star::xml::sax::XAttributeList > & xAttrList );

    virtual void EndElement();
};


#endif
