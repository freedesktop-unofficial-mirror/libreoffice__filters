/*************************************************************************
 *
 *  $RCSfile: EditBase.hxx,v $
 *
 *  $Revision: 1.3 $
 *
 *  last change: $Author: hr $ $Date: 2004-08-03 10:44:32 $
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

#ifndef _FORMS_EDITBASE_HXX_
#define _FORMS_EDITBASE_HXX_

#ifndef _FORMS_FORMCOMPONENT_HXX_
#include "FormComponent.hxx"
#endif
// auto strip #ifndef _DATE_HXX
// auto strip #include <tools/date.hxx>
// auto strip #endif
// auto strip #ifndef _LINK_HXX
// auto strip #include <tools/link.hxx>
// auto strip #endif

// auto strip #ifndef _COM_SUN_STAR_UTIL_XNUMBERFORMATTER_HPP_
// auto strip #include <com/sun/star/util/XNumberFormatter.hpp>
// auto strip #endif
// auto strip #ifndef _COM_SUN_STAR_AWT_XFOCUSLISTENER_HPP_
// auto strip #include <com/sun/star/awt/XFocusListener.hpp>
// auto strip #endif
// auto strip #ifndef _COM_SUN_STAR_AWT_XKEYLISTENER_HPP_
// auto strip #include <com/sun/star/awt/XKeyListener.hpp>
// auto strip #endif
// auto strip #ifndef _COM_SUN_STAR_FORM_XCHANGEBROADCASTER_HPP_
// auto strip #include <com/sun/star/form/XChangeBroadcaster.hpp>
// auto strip #endif
// auto strip #ifndef _COM_SUN_STAR_LANG_XEVENTLISTENER_HPP_
// auto strip #include <com/sun/star/lang/XEventListener.hpp>
// auto strip #endif
// auto strip #ifndef _COM_SUN_STAR_LANG_XSERVICEINFO_HPP_
// auto strip #include <com/sun/star/lang/XServiceInfo.hpp>
// auto strip #endif
// auto strip #ifndef _COM_SUN_STAR_LANG_XCOMPONENT_HPP_
// auto strip #include <com/sun/star/lang/XComponent.hpp>
// auto strip #endif
namespace binfilter {

// persistence flags for use with the version id
#define PF_HANDLE_COMMON_PROPS	0x8000
    // Derived classes which use their own persistence methods (read/write) and have an own
    // version handling therein may want to clear this flag in getPersistenceFlags.
    // If done so, this class will write an version without a call to writeCommonEditProperties.
#define PF_FAKE_FORMATTED_FIELD	0x4000
    // .... hmmm .... a fake, as the name suggests. see OFormattedFieldWrapper
#define PF_RESERVED_2			0x2000
#define PF_RESERVED_3			0x1000
#define PF_RESERVED_4			0x0800
#define PF_RESERVED_5			0x0400
#define PF_RESERVED_6			0x0200
#define PF_RESERVED_7			0x0100

#define PF_SPECIAL_FLAGS		0xFF00

//.........................................................................
namespace frm
{

//==================================================================
//= OEditBaseModel
//==================================================================
class OEditBaseModel :	public OBoundControlModel
{
    sal_Int16					m_nLastReadVersion;

protected:
// [properties]			fuer all Editierfelder
    ::com::sun::star::uno::Any	m_aDefault;
    ::rtl::OUString				m_aDefaultText;				// default value
    sal_Bool					m_bEmptyIsNull : 1;			// empty string will be interepreted as NULL when committing
    sal_Bool					m_bFilterProposal : 1;		// use a list of possible value in filtermode
// [properties]

    sal_Int16	getLastReadVersion() const { return m_nLastReadVersion; }

public:
    DECLARE_DEFAULT_XTOR( OEditBaseModel );

    // XPersistObject
    virtual void SAL_CALL write(const ::com::sun::star::uno::Reference< ::com::sun::star::io::XObjectOutputStream>& _rxOutStream) throw ( ::com::sun::star::io::IOException, ::com::sun::star::uno::RuntimeException);
    virtual void SAL_CALL read(const ::com::sun::star::uno::Reference< ::com::sun::star::io::XObjectInputStream>& _rxInStream) throw ( ::com::sun::star::io::IOException, ::com::sun::star::uno::RuntimeException);

    // XPropertySet
    virtual void SAL_CALL getFastPropertyValue(::com::sun::star::uno::Any& rValue, sal_Int32 nHandle ) const;
    virtual sal_Bool SAL_CALL convertFastPropertyValue(::com::sun::star::uno::Any& rConvertedValue, ::com::sun::star::uno::Any& rOldValue,
                                          sal_Int32 nHandle, const ::com::sun::star::uno::Any& rValue )
                                        throw(::com::sun::star::lang::IllegalArgumentException);
    virtual void SAL_CALL setFastPropertyValue_NoBroadcast(sal_Int32 nHandle, const ::com::sun::star::uno::Any& rValue) throw ( ::com::sun::star::uno::Exception);

    // XPropertyState
    virtual	::com::sun::star::beans::PropertyState getPropertyStateByHandle(sal_Int32 nHandle);
    virtual	void setPropertyToDefaultByHandle(sal_Int32 nHandle);
    virtual ::com::sun::star::uno::Any getPropertyDefaultByHandle( sal_Int32 nHandle ) const;

protected:
    // new properties common to all edit models should be handled with the following two methods
    void SAL_CALL readCommonEditProperties(const ::com::sun::star::uno::Reference< ::com::sun::star::io::XObjectInputStream>& _rxInStream);
    void SAL_CALL writeCommonEditProperties(const ::com::sun::star::uno::Reference< ::com::sun::star::io::XObjectOutputStream>& _rxOutStream);
    void defaultCommonEditProperties();

    virtual sal_Int16 getPersistenceFlags() const;
        // derived classes may use this if they want this base class to write additinal version flags
        // (one of the PF_.... constants). After ::read they may ask for that flags with getLastReadVersion
};

//.........................................................................
}
//.........................................................................

}//end of namespace binfilter
#endif // _FORMS_EDITBASE_HXX_

