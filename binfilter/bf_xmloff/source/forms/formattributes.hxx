/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: formattributes.hxx,v $
 *
 *  $Revision: 1.3 $
 *
 *  last change: $Author: rt $ $Date: 2005-09-09 09:05:59 $
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

#ifndef _XMLOFF_FORMATTRIBUTES_HXX_
#define _XMLOFF_FORMATTRIBUTES_HXX_

// auto strip #ifndef _COM_SUN_STAR_BEANS_XPROPERTYSET_HPP_
// auto strip #include <com/sun/star/beans/XPropertySet.hpp>
// auto strip #endif
#ifndef _SAL_TYPES_H_
#include <sal/types.h>
#endif
// auto strip #ifndef _VOS_REFERNCE_HXX_
// auto strip #include <vos/refernce.hxx>
// auto strip #endif
#ifndef _COMPHELPER_STLTYPES_HXX_
#include <comphelper/stl_types.hxx>
#endif
namespace binfilter {

class SvXMLExport;
struct SvXMLEnumMapEntry;

//.........................................................................
namespace xmloff
{
//.........................................................................

    // flags for common control attributes
    #define CCA_NAME					0x00000001
    #define CCA_SERVICE_NAME			0x00000002
    #define CCA_BUTTON_TYPE				0x00000004
    #define CCA_CONTROL_ID				0x00000008
    #define CCA_CURRENT_SELECTED		0x00000010
    #define CCA_CURRENT_VALUE			0x00000020
    #define CCA_DISABLED				0x00000040
    #define CCA_DROPDOWN				0x00000080
    #define CCA_FOR						0x00000100
    #define CCA_IMAGE_DATA				0x00000200
    #define CCA_LABEL					0x00000400
    #define CCA_MAX_LENGTH				0x00000800
    #define CCA_PRINTABLE				0x00001000
    #define CCA_READONLY				0x00002000
    #define CCA_SELECTED				0x00004000
    #define CCA_SIZE					0x00008000
    #define CCA_TAB_INDEX				0x00010000
    #define CCA_TARGET_FRAME			0x00020000
    #define CCA_TARGET_LOCATION			0x00040000
    #define CCA_TAB_STOP				0x00080000
    #define CCA_TITLE					0x00100000
    #define CCA_VALUE					0x00200000

    // flags for database control atttributes
    #define DA_BOUND_COLUMN				0x00000001
    #define DA_CONVERT_EMPTY			0x00000002
    #define DA_DATA_FIELD				0x00000004
    #define DA_LIST_SOURCE				0x00000008
    #define DA_LIST_SOURCE_TYPE			0x00000010

    // flags for binding related control attributes
    #define BA_LINKED_CELL              0x00000001
    #define BA_LIST_LINKING_TYPE        0x00000002
    #define BA_LIST_CELL_RANGE          0x00000004

    // flags for event attributes
    #define EA_CONTROL_EVENTS			0x00000001
    #define EA_ON_CHANGE				0x00000002
    #define EA_ON_CLICK					0x00000004
    #define EA_ON_DBLCLICK				0x00000008
    #define EA_ON_SELECT				0x00000010

    /// attributes in the xml tag representing a form
    enum FormAttributes
    {
        faName,
        faServiceName,
        faAction,
        faEnctype,
        faMethod,
        faTargetFrame,
        faAllowDeletes,
        faAllowInserts,
        faAllowUpdates,
        faApplyFilter,
        faCommand,
        faCommandType,
        faEscapeProcessing,
        faDatasource,
        faDetailFiels,
        faFilter,
        faIgnoreResult,
        faMasterFields,
        faNavigationMode,
        faOrder,
        faTabbingCycle
    };

    // any other attributes, which are special to some control types
    #define SCA_ECHO_CHAR				0x00000001
    #define SCA_MAX_VALUE				0x00000002
    #define SCA_MIN_VALUE				0x00000004
    #define SCA_VALIDATION				0x00000008
    #define SCA_MULTI_LINE				0x00000020
    #define SCA_AUTOMATIC_COMPLETION	0x00000080
    #define SCA_MULTIPLE				0x00000100
    #define SCA_DEFAULT_BUTTON			0x00000200
    #define SCA_CURRENT_STATE			0x00000400
    #define SCA_IS_TRISTATE				0x00000800
    #define SCA_STATE					0x00001000
    #define SCA_COLUMN_STYLE_NAME		0x00002000

    // attributes of the office:forms element
    enum OfficeFormsAttributes
    {
        ofaAutomaticFocus,
        ofaApplyDesignMode
    };

    //=====================================================================
    //= OAttributeMetaData
    //=====================================================================
    /** allows the translation of attribute ids into strings.

        <p>This class does not allow to connect xml attributes to property names or
        something like that, it only deals with the xml side</p>
    */
    class OAttributeMetaData
    {
    protected:
        /** ctor.
            <p>This default constructor is protected, 'cause this class is not intended to be instantiated
            directly. Instead, the derived classes should be used.</p>
        */
        OAttributeMetaData() { }

    protected:
        /** calculates the xml attribute representation of a common control attribute.
            @param _nId
                the id of the attribute. Has to be one of the CCA_* constants.
        */
        static const sal_Char* getCommonControlAttributeName(sal_Int32 _nId);

        /** calculates the xml namespace key to use for a common control attribute
            @param _nId
                the id of the attribute. Has to be one of the CCA_* constants.
        */
        static sal_uInt16 getCommonControlAttributeNamespace(sal_Int32 _nId);

        /** retrieves the name of an attribute of a form xml representation
            @param	_eAttrib
                enum value specifying the attribute
        */
        static const sal_Char* getFormAttributeName(FormAttributes _eAttrib);

        /** calculates the xml namespace key to use for a attribute of a form xml representation
            @param	_eAttrib
                enum value specifying the attribute
        */
        static sal_uInt16 getFormAttributeNamespace(FormAttributes _eAttrib);

        /** calculates the xml attribute representation of a database attribute.
            @param _nId
                the id of the attribute. Has to be one of the DA_* constants.
        */
        static const sal_Char* getDatabaseAttributeName(sal_Int32 _nId);

        /** calculates the xml namespace key to use for a database attribute.
            @param _nId
                the id of the attribute. Has to be one of the DA_* constants.
        */
        static sal_uInt16 getDatabaseAttributeNamespace(sal_Int32 _nId);

        /** calculates the xml attribute representation of a special attribute.
            @param _nId
                the id of the attribute. Has to be one of the SCA_* constants.
        */
        static const sal_Char* getSpecialAttributeName(sal_Int32 _nId);

        /** calculates the xml attribute representation of a binding attribute.
            @param _nId
                the id of the attribute. Has to be one of the BA_* constants.
        */
        static const sal_Char* getBindingAttributeName(sal_Int32 _nId);

        /** calculates the xml namespace key to use for a binding attribute.
            @param _nId
                the id of the attribute. Has to be one of the BA_* constants.
        */
        static sal_uInt16 getBindingAttributeNamespace(sal_Int32 _nId);

        /** calculates the xml namespace key to use for a special attribute.
            @param _nId
                the id of the attribute. Has to be one of the SCA_* constants.
        */
        static sal_uInt16 getSpecialAttributeNamespace(sal_Int32 _nId);

        /** calculates the xml attribute representation of a attribute of the office:forms element
            @param _nId
                the id of the attribute
        */
        static const sal_Char* getOfficeFormsAttributeName(OfficeFormsAttributes _eAttrib);

        /** calculates the xml namedspace key of a attribute of the office:forms element
            @param _nId
                the id of the attribute
        */
        static sal_uInt16 getOfficeFormsAttributeNamespace(OfficeFormsAttributes _eAttrib);
    };

    //=====================================================================
    //= OAttribute2Property
    //=====================================================================
    /** some kind of opposite to the OAttributeMetaData class. Able to translate
        attributes into property names/types

        <p>The construction of this class is rather expensive (or at least it's initialization from outside),
        so it should be shared</p>
    */
    class OAttribute2Property
    {
    public:
        // TODO: maybe the following struct should be used for exports, too. In this case we would not need to
        // store it's instances in a map, but in a vector for faster access.
        struct AttributeAssignment
        {
            ::rtl::OUString					sAttributeName;			// the attribute name
            ::rtl::OUString					sPropertyName;			// the property name
            ::com::sun::star::uno::Type		aPropertyType;			// the property type
            ::rtl::OUString					sAttributeDefault;		// the default if the attribute is not present

            // entries which are special to some value types
            const SvXMLEnumMapEntry*		pEnumMap;				// the enum map, if appliable
            sal_Bool						bInverseSemantics;		// for booleanss: attribute and property value have the same or an inverse semantics?

            AttributeAssignment() : pEnumMap(NULL), bInverseSemantics(sal_False) { }
        };

    protected:
        DECLARE_STL_USTRINGACCESS_MAP( AttributeAssignment, AttributeAssignments );
        AttributeAssignments		m_aKnownProperties;

    public:
        OAttribute2Property();
        virtual ~OAttribute2Property();

        /** return the AttributeAssignment which corresponds to the given attribute

            @param _rAttribName
                the name of the attrribute
            @return
                a pointer to the <type>AttributeAssignment</type> structure as requested, NULL if the attribute
                does not represent a property.
        */
        const AttributeAssignment* getAttributeTranslation(
            const ::rtl::OUString& _rAttribName);

        /** add a attribute assignment referring to a string property to the map
            @param _pAttributeName
                the name of the attrribute
            @param _rPropertyName
                the name of the property assigned to the attribute
            @param _pAttributeDefault
                the default value for the attribute, if any. May be NULL, in this case the default is assumed to be
                an empty string.
        */
        void	addStringProperty(
            const sal_Char* _pAttributeName, const ::rtl::OUString& _rPropertyName,
            const sal_Char* _pAttributeDefault = NULL);

        /** add a attribute assignment referring to a boolean property to the map

            @param _pAttributeName
                the name of the attrribute
            @param _rPropertyName
                the name of the property assigned to the attribute
            @param _bAttributeDefault
                the default value for the attribute.
            @param _bInverseSemantics
                if <TRUE/>, a attribute value of <TRUE/> means a property value of <FALSE/> and vice verse.<br/>
                if <FALSE/>, the attribute value is used as property value directly
        */
        void	addBooleanProperty(
            const sal_Char* _pAttributeName, const ::rtl::OUString& _rPropertyName,
            const sal_Bool _bAttributeDefault, const sal_Bool _bInverseSemantics = sal_False);

        /** add a attribute assignment referring to an int16 property to the map

            @param _pAttributeName
                the name of the attrribute
            @param _rPropertyName
                the name of the property assigned to the attribute
            @param _nAttributeDefault
                the default value for the attribute.
        */
        void	addInt16Property(
            const sal_Char* _pAttributeName, const ::rtl::OUString& _rPropertyName,
            const sal_Int16 _nAttributeDefault);

        /** add a attribute assignment referring to an enum property to the map

            @param _pAttributeName
                the name of the attrribute
            @param _rPropertyName
                the name of the property assigned to the attribute
            @param _nAttributeDefault
                the default value for the attribute, as (32bit) integer
            @param _pValueMap
                the map to translate strings into enum values
            @param _pType
                the type of the property. May be NULL, in this case 32bit integer is assumed.
        */
        void	addEnumProperty(
            const sal_Char* _pAttributeName, const ::rtl::OUString& _rPropertyName,
            const sal_uInt16 _nAttributeDefault, const SvXMLEnumMapEntry* _pValueMap,
            const ::com::sun::star::uno::Type* _pType = NULL);

    protected:
        /// some common code for the various add*Property methods
        AttributeAssignment& implAdd(
            const sal_Char* _pAttributeName, const ::rtl::OUString& _rPropertyName,
            const ::com::sun::star::uno::Type& _rType, const ::rtl::OUString& _rDefaultString);
    };
//.........................................................................
}	// namespace xmloff
//.........................................................................

}//end of namespace binfilter
#endif // _XMLOFF_FORMATTRIBUTES_HXX_

/*************************************************************************
 * history:
 *	$Log: not supported by cvs2svn $
 *	Revision 1.2.128.1  2005/09/05 11:30:10  rt
 *	#i54170# Change license header: remove SISSL
 *	
 *	Revision 1.2  2004/08/03 19:56:29  hr
 *	INTEGRATION: CWS bff2 (1.1.20); FILE MERGED
 *	2004/07/08 16:32:18 aw 1.1.20.1: #117295#
 *	
 *	Revision 1.1.20.1  2004/07/08 16:32:18  aw
 *	#117295#
 *	
 *	Revision 1.1  2003/12/05 09:34:04  aw
 *	Added bf_xmloff files
 *	
 *	Revision 1.7  2003/10/21 08:39:13  obo
 *	INTEGRATION: CWS formcelllinkage (1.6.160); FILE MERGED
 *	2003/10/01 09:55:19 fs 1.6.160.1: #i18994# merging the changes from the CWS fs002
 *	
 *	Revision 1.6.160.1  2003/10/01 09:55:19  fs
 *	#i18994# merging the changes from the CWS fs002
 *	
 *	Revision 1.6.156.1  2003/09/25 14:28:38  fs
 *	#18994# merging the changes from cws_srx645_fs002 branch
 *	
 *	Revision 1.6.152.2  2003/09/18 14:00:37  fs
 *	#18995# changes for binding list boxes to cells, while exchanging selection indexes instead of strings
 *	
 *	Revision 1.6.152.1  2003/09/17 12:26:53  fs
 *	#18999# #19367# persistence for cell value and cell range bindings
 *	
 *	Revision 1.6  2002/10/25 07:54:55  fs
 *	#104402# +SCA_COLUMN_STYLE_NAME
 *	
 *	Revision 1.5  2001/03/20 13:33:39  fs
 *	#83970# +getOfficeFormsAttributeName(/-space)
 *	
 *	Revision 1.4  2000/12/12 12:01:05  fs
 *	new implementations for the import - still under construction
 *	
 *	Revision 1.3  2000/12/06 17:28:05  fs
 *	changes for the formlayer import - still under construction
 *	
 *	Revision 1.2  2000/11/19 15:41:32  fs
 *	extended the export capabilities - generic controls / grid columns / generic properties / some missing form properties
 *	
 *	Revision 1.1  2000/11/17 19:01:46  fs
 *	initial checkin - export and/or import the applications form layer
 *	
 *
 *	Revision 1.0 13.11.00 17:49:43  fs
 ************************************************************************/

