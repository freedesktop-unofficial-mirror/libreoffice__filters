/*************************************************************************
 *
 *  $RCSfile: formlayerexport.hxx,v $
 *
 *  $Revision: 1.1 $
 *
 *  last change: $Author: jmeng $ $Date: 2003-12-04 01:45:38 $
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

#ifndef _XMLOFF_FORMLAYEREXPORT_HXX_
#define _XMLOFF_FORMLAYEREXPORT_HXX_

#ifndef _VOS_REFERNCE_HXX_
#include <vos/refernce.hxx>
#endif
#ifndef _COM_SUN_STAR_DRAWING_XDRAWPAGE_HPP_
#include <com/sun/star/drawing/XDrawPage.hpp>
#endif
#ifndef _COM_SUN_STAR_CONTAINER_XINDEXACCESS_HPP_
#include <com/sun/star/container/XIndexAccess.hpp>
#endif
#ifndef _COM_SUN_STAR_BEANS_XPROPERTYSET_HPP_
#include <com/sun/star/beans/XPropertySet.hpp>
#endif
#ifndef _COM_SUN_STAR_FRAME_XMODEL_HPP_
#include <com/sun/star/frame/XModel.hpp>
#endif
#ifndef _VOS_REF_HXX_
#include <vos/ref.hxx>
#endif
#ifndef _XMLOFF_XMLEXPPR_HXX
#include <bf_xmloff/xmlexppr.hxx>
#endif

namespace com { namespace sun { namespace star { namespace awt {
    class XControlModel;
} } } }
namespace binfilter {

class SvXMLExport;
//.........................................................................
namespace xmloff
{
//.........................................................................

    class OFormLayerXMLExport_Impl;
    class OFormsRootExport;

    //=====================================================================
    //= OFormLayerXMLExport
    //=====================================================================
    /** provides functionallity for exporting a complete form layer.
    */
    class OFormLayerXMLExport
                :public ::vos::OReference
    {
    protected:
        /// our export context
        SvXMLExport&				m_rContext;
        // impl class
        OFormLayerXMLExport_Impl*	m_pImpl;

    protected:
        ~OFormLayerXMLExport();

    public:
        OFormLayerXMLExport(SvXMLExport& _rContext);

        /** initial the object

            <p>To be called if you want to reuse the same object for exportin different documents.</p>

            <p>You don't need to call this if you just constructed the object, in this case it is already
            initialized..</p>
        */
        void initialize();

        /** initializes some internal structures for fast access to the given page

            <p>This method has to be called before you use getControlId for controls on the given page.
            This way a performance optimization can be done for faster access to the control ids</p>

            @return
                <TRUE/> if the page has been examined before. If <FALSE/> is returned, this is a serious error.

            @see getControlId
            @see examine
        */
        sal_Bool seekPage(
            const ::com::sun::star::uno::Reference< ::com::sun::star::drawing::XDrawPage >& _rxDrawPage);

        /** get the id for the given control

            <p>The page the control belongs to must have been examined and sought to.</p>

            @param _rxControl
                the control which's id should be retrieved. Must not be <NULL/>.

            @see examineForms
            @see seekPage

        */
        ::rtl::OUString getControlId(
            const ::com::sun::star::uno::Reference< ::com::sun::star::beans::XPropertySet >& _rxControl);

        /** retrieves the style name for the control's number style.

            <p>For performance reasons, this method is allowed to be called for any controls, even those which
            do not have a number style. In this case, an empty string is returned.</p>

            @param _rxControl
                the control which's id should be retrieved. Must not be <NULL/>.

            @see examineForms
            @see seekPage
        */
        ::rtl::OUString getControlNumberStyle(
            const ::com::sun::star::uno::Reference< ::com::sun::star::beans::XPropertySet >& _rxControl );

        /** examines the forms collection given.

            <p>This method will collect all form layer related data of the given draw page</p>

            @param _rxDrawPage
                the draw page to examine. The object will be queried for a <type scope="com.sun.star.form">XFormsSupplier</type>
                interface to obtain the forms container.
        */
        void examineForms(const ::com::sun::star::uno::Reference< ::com::sun::star::drawing::XDrawPage >& _rxDrawPage);

        /** exports the structure of a form layer

            <p>This method does not export styles (e.g. font properties of the controls), or any references
            external instances may have to the control models contained in the form layer (e.g. uno control
            shapes in the drawing layer may have such references)</p>

            <p>No top level element describing the whole collection is inserted. I.e. if within your document, you
            expect the the forms collection to be stored like
                <listing>
                    &lt;Forms&gt;
                        ....	// all the forms stuff here
                    &lt;/Forms&gt;
                </listing>
            you have to start the Forms element yourself.</p>

            @param	_rxDrawPage
                the draw page to examine. The object will be queried for a <type scope="com.sun.star.form">XFormsSupplier</type>
                interface to obtain the forms container.
        */
        void exportForms(const ::com::sun::star::uno::Reference< ::com::sun::star::drawing::XDrawPage >& _rxDrawPage);

        /// retrieves the property mapper for control styles
        ::vos::ORef< SvXMLExportPropertyMapper > getStylePropertyMapper();

        /** exports the controls number styles
        */
        void exportControlNumberStyles();

        /** exports the automatic controls number styles
        */
        void exportAutoControlNumberStyles();

        /** exports the auto-styles collected during the examineForms calls
        */
        void exportAutoStyles();

        /** exclude the given control (model) from export.

            <p>If your document contains form controls which are not to be exported for whatever reason,
            you need to announce the models of these controls (can be retrieved from XControlShape::getControl)
            to the form layer exporter.<br/>
            Of course you have to do this before calling <member>exportForms</member></p>
        */
        void excludeFromExport( const ::com::sun::star::uno::Reference< ::com::sun::star::awt::XControlModel > _rxControl );
    };

    //=========================================================================
    //= OOfficeFormsExport
    //=========================================================================
    /// export helper for the office::forms element
    class OOfficeFormsExport
    {
    private:
        OFormsRootExport*	m_pImpl;

    public:
        OOfficeFormsExport( SvXMLExport& _rExp );
        ~OOfficeFormsExport();
    };

//.........................................................................
}	// namespace xmloff
//.........................................................................

}//end of namespace binfilter
#endif // _XMLOFF_FORMLAYEREXPORT_HXX_

