/* -*- Mode: C++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */
/*************************************************************************
 *
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER.
 * 
 * Copyright 2000, 2010 Oracle and/or its affiliates.
 *
 * OpenOffice.org - a multi-platform office productivity suite
 *
 * This file is part of OpenOffice.org.
 *
 * OpenOffice.org is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License version 3
 * only, as published by the Free Software Foundation.
 *
 * OpenOffice.org is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License version 3 for more details
 * (a copy is included in the LICENSE file that accompanied this code).
 *
 * You should have received a copy of the GNU Lesser General Public License
 * version 3 along with OpenOffice.org.  If not, see
 * <http://www.openoffice.org/license.html>
 * for a copy of the LGPLv3 License.
 *
 ************************************************************************/

#ifndef _XMLOFF_ELEMENTEXPORT_HXX_
#define _XMLOFF_ELEMENTEXPORT_HXX_

#include <com/sun/star/beans/XPropertySet.hpp>
#include <com/sun/star/container/XIndexAccess.hpp>
#include <com/sun/star/script/ScriptEventDescriptor.hpp>
#include "propertyexport.hxx"
#include "callbacks.hxx"
#include "controlelement.hxx"
#include "valueproperties.hxx"
namespace binfilter {

class SvXMLElementExport;
//.........................................................................
namespace xmloff
{
//.........................................................................

    //=====================================================================
    //= OElementExport
    //=====================================================================
    class OElementExport : public OPropertyExport
    {
    protected:
        ::com::sun::star::uno::Sequence< ::com::sun::star::script::ScriptEventDescriptor >
                                m_aEvents;

        SvXMLElementExport*		m_pXMLElement;			// XML element doing the concrete startElement etc.

    public:
        OElementExport(IFormsExportContext& _rContext,
            const ::com::sun::star::uno::Reference< ::com::sun::star::beans::XPropertySet >& _rxProps,
            const ::com::sun::star::uno::Sequence< ::com::sun::star::script::ScriptEventDescriptor >& _rEvents);
        ~OElementExport();

        void doExport();

    protected:
        /// get the name of the XML element
        virtual const sal_Char* getXMLElementName() const = 0;
        /// examine the element we're exporting
        virtual void examine();
        /// export the attributes
        virtual void exportAttributes();
        /// export any sub tags
        virtual void exportSubTags();

        /** exports the events (as script:events tag)
        */
        void exportEvents();

        /** add the service-name attribute to the export context
        */
        virtual void exportServiceNameAttribute();

        /// start the XML element
        virtual void implStartElement(const sal_Char* _pName);

        /// ends the XML element
        virtual void implEndElement();
    };

    //=====================================================================
    //= OControlExport
    //=====================================================================
    /** Helper class for handling xml elements representing a form control
    */
    class OControlExport
                :public OControlElement
                ,public OValuePropertiesMetaData
                ,public OElementExport
    {
    protected:
        DECLARE_STL_STDKEY_SET(sal_Int16, Int16Set);
            // used below

        ::rtl::OUString			m_sControlId;			// the control id to use when exporting
        ::rtl::OUString			m_sReferringControls;	// list of referring controls (i.e. their id's)
        sal_Int16				m_nClassId;				// class id of the control we're representing
        ElementType				m_eType;				// (XML) type of the control we're representing
        sal_Int32				m_nIncludeCommon;		// common control attributes to include
        sal_Int32				m_nIncludeDatabase;		// common database attributes to include
        sal_Int32				m_nIncludeSpecial;		// special attributes to include
        sal_Int32				m_nIncludeEvents;		// events to include
        sal_Int32               m_nIncludeBindings;	    // binding attributes to include

        SvXMLElementExport*		m_pOuterElement;		// XML element doing the concrete startElement etc. for the outer element

    public:
        /** constructs an object capable of exporting controls

            <p>You need at least two pre-requisites from outside: The control to be exported needs to have a class id
            assigned, and you need the list control-ids of all the controls referring to this one as LabelControl.<br/>
            This information can't be collected when known only the control itself and not it's complete context.</p>

            @param _rControlId
                the control id to use when exporting the control
            @param _rReferringControls
                the comma-separated list of control-ids of all the controls referring to this one as LabelControl
        */
        OControlExport(IFormsExportContext& _rContext,
            const ::com::sun::star::uno::Reference< ::com::sun::star::beans::XPropertySet >& _rxControl,
            const ::rtl::OUString& _rControlId,
            const ::rtl::OUString& _rReferringControls,
            const ::com::sun::star::uno::Sequence< ::com::sun::star::script::ScriptEventDescriptor >& _rxEvents);
        ~OControlExport();

    protected:
        /// start the XML element
        virtual void implStartElement(const sal_Char* _pName);

        /// ends the XML element
        virtual void implEndElement();

        /// get the name of the outer XML element
        virtual const sal_Char* getOuterXMLElementName() const;

        // get the name of the XML element
        virtual const sal_Char* getXMLElementName() const;

        /** examine the control. Some kind of CtorImpl.
        */
        virtual void examine();

        /// exports the attributes for the outer element
        void exportOuterAttributes();

        /// exports the attributes for the inner element
        void exportInnerAttributes();

        /// export the attributes
        virtual void exportAttributes();

        /** writes everything which needs to be represented as sub tag
        */
        void exportSubTags() throw (::com::sun::star::uno::Exception);

        /**	adds common control attributes to the XMLExport context given

            <p>The attribute list of the context is not cleared initially, this is the responsibility of the caller.</p>
        */
        void exportCommonControlAttributes();

        /**	adds database attributes to the XMLExport context given

            <p>The attribute list of the context is not cleared initially, this is the responsibility of the caller.</p>
        */
        void exportDatabaseAttributes();

        /**	adds the XML attributes which are related to binding controls to
            external values and/or list sources
        */
        void exportBindingAtributes();

        /** adds attributes which are special to a control type to the export context's attribute list
        */
        void exportSpecialAttributes();

        /** exports the ListSource property of a control as attribute

            <p>The ListSource property may be exported in different ways: For a ComboBox, it is an attribute
            of the form:combobox element.</p>

            <p>For a ListBox, it's an attribute if the ListSourceType states that the ListBox does <em>not</em>
            display a value list. In case of a value list, the ListSource is not exported, and the pairs of
            StringItem/ValueItem are exported as sub-elements.<br/>
            (For a value list ListBox, As every setting of the ListSource immediately sets the ValueList to the
            same value, so nothing is lost when exporting this).</p>

            <p>It's really strange, isn't it? Don't know why we have this behaviour in our controls ...</p>

            <p>This method does the attribute part: It exports the ListSource property as attribute, not caring
            about whether the object is a ComboBox or a ListBox.</p>
        */
        void exportListSourceAsAttribute();

        /** exports the ListSource property of a control as XML elements

            @see exportListSourceAsAttribute
        */
        void exportListSourceAsElements();

        /** get's a Sequence&lt; sal_Int16 &gt; property value as set of sal_Int16's
            @param _rPropertyName
                the property name to use
            @param _rOut
                out parameter. The set of integers.
        */
        void getSequenceInt16PropertyAsSet(const ::rtl::OUString& _rPropertyName, Int16Set& _rOut);

        /** exports the attribute which descrives a cell value binding of a control
            in a spreadsheet document
        */
        void exportCellBindingAttributes( bool _bIncludeListLinkageType );

        /** exports the attribute which descrives a cell range which acts as list source for
            a list-like control
        */
        void exportCellListSourceRange( );
    };

    //=====================================================================
    //= OColumnExport
    //=====================================================================
    /** Helper class for exporting a grid column
    */
    class OColumnExport : public OControlExport
    {
    public:
        /** ctor
            @see OColumnExport::OColumnExport
        */
        OColumnExport(IFormsExportContext& _rContext, 
            const ::com::sun::star::uno::Reference< ::com::sun::star::beans::XPropertySet >& _rxControl,
            const ::com::sun::star::uno::Sequence< ::com::sun::star::script::ScriptEventDescriptor >& _rxEvents);

        ~OColumnExport();

    protected:
        // OControlExport overridables
        virtual const sal_Char* getOuterXMLElementName() const;
        virtual void exportServiceNameAttribute();
        virtual void exportAttributes();

        // OElementExport overridables
        virtual void examine();
    };

    //=====================================================================
    //= OFormExport
    //=====================================================================
    /** Helper class for handling xml elements representing a form

        <p>In opposite to the class <type>OControlExport</type>, OFormExport is unable to export a <em>complete</em>
        form. Instead the client has to care for sub elements of the form itself.</p>
    */
    class OFormExport
                :public OControlElement
                ,public OElementExport
    {
    public:
        /** constructs an object capable of exporting controls
        */
        OFormExport(IFormsExportContext& _rContext,
            const ::com::sun::star::uno::Reference< ::com::sun::star::beans::XPropertySet >& _rxForm,
            const ::com::sun::star::uno::Sequence< ::com::sun::star::script::ScriptEventDescriptor >& _rxEvents
            );

    protected:
        virtual const sal_Char* getXMLElementName() const;
        virtual void exportSubTags();
        virtual void exportAttributes();
    };

//.........................................................................
}	// namespace xmloff
//.........................................................................

}//end of namespace binfilter
#endif // _XMLOFF_ELEMENTEXPORT_HXX_

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
