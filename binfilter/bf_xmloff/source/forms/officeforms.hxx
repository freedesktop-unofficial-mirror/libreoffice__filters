/*************************************************************************
 *
 *  $RCSfile: officeforms.hxx,v $
 *
 *  $Revision: 1.1 $
 *
 *  last change: $Author: aw $ $Date: 2003-12-05 09:34:08 $
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
 *  WITHOUT WARRANTY OF ANY KIND, EITHER EXPRESS OR IMPLIED, INCLUDING,
 *  WITHOUT LIMITATION, WARRANTIES THAT THE SOFTWARE IS FREE OF DEFECTS,
 *  MERCHANTABLE, FIT FOR A PARTICULAR PURPOSE, OR NON-INFRINGING.
 *  See the License for the specific provisions governing your rights and
 *  obligations concerning the Software.
 *
 *  The Initial Developer of the Original Code is: Sun Microsystems, Inc..
 *
 *  Copyright: 2000 by Sun Microsystems, Inc.
 *
 *  All Rights Reserved.
 *
 *  Contributor(s): _______________________________________
 *
 *
 ************************************************************************/

#ifndef _XMLOFF_FORMS_OFFICEFORMS_HXX_
#define _XMLOFF_FORMS_OFFICEFORMS_HXX_

#ifndef _XMLOFF_FORMATTRIBUTES_HXX_
#include "formattributes.hxx"
#endif
#ifndef _XMLOFF_XMLICTXT_HXX 
#include "xmlictxt.hxx"
#endif
#ifndef XMLOFF_FORMS_LOGGING_HXX
#include "logging.hxx"
#endif
namespace binfilter {

class SvXMLElementExport;
class SvXMLExport;

//.........................................................................
namespace xmloff
{
//.........................................................................

    //=====================================================================
    //= OFormsRootImport
    //=====================================================================
    class OFormsRootImport
                :public SvXMLImportContext
                ,public OAttributeMetaData
                ,public OStackedLogging
    {
    public:
        TYPEINFO();

        OFormsRootImport( SvXMLImport& _rImport, sal_uInt16 _nPrfx, const ::rtl::OUString& _rLocalName);
        virtual ~OFormsRootImport();

        // SvXMLImportContext overriabled
        virtual SvXMLImportContext * CreateChildContext( USHORT nPrefix, const ::rtl::OUString& rLocalName,
            const ::com::sun::star::uno::Reference< ::com::sun::star::xml::sax::XAttributeList>& xAttrList );
        virtual void StartElement( const ::com::sun::star::uno::Reference< ::com::sun::star::xml::sax::XAttributeList >& _rxAttrList );
        virtual void EndElement();

    protected:
        void implImportBool(
            const ::com::sun::star::uno::Reference< ::com::sun::star::xml::sax::XAttributeList >& _rxAttributes,
            OfficeFormsAttributes _eAttribute,
            const ::com::sun::star::uno::Reference< ::com::sun::star::beans::XPropertySet >& _rxProps,
            const ::com::sun::star::uno::Reference< ::com::sun::star::beans::XPropertySetInfo >& _rxPropInfo,
            const ::rtl::OUString& _rPropName,
            sal_Bool _bDefault
            );
    };

    //=====================================================================
    //= OFormsRootExport
    //=====================================================================
    class OFormsRootExport : public OAttributeMetaData
    {
    private:
        SvXMLElementExport*		m_pImplElement;

    public:
        OFormsRootExport( SvXMLExport& _rExp );
        ~OFormsRootExport();

    private:
        void addModelAttributes(SvXMLExport& _rExp) SAL_THROW(());

        void implExportBool(
            SvXMLExport& _rExp,
            OfficeFormsAttributes _eAttribute,
            const ::com::sun::star::uno::Reference< ::com::sun::star::beans::XPropertySet >& _rxProps,
            const ::com::sun::star::uno::Reference< ::com::sun::star::beans::XPropertySetInfo >& _rxPropInfo,
            const ::rtl::OUString& _rPropName,
            sal_Bool _bDefault
            );
    };

//.........................................................................
}	// namespace xmloff
//.........................................................................

}//end of namespace binfilter
#endif // _XMLOFF_FORMS_OFFICEFORMS_HXX_


