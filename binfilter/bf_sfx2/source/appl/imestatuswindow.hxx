/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: imestatuswindow.hxx,v $
 *
 *  $Revision: 1.5 $
 *
 *  last change: $Author: rt $ $Date: 2006-10-27 18:52:00 $
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

#if !defined INCLUDED_SFX2_APPL_IMESTATUSWINDOW_HXX
#define INCLUDED_SFX2_APPL_IMESTATUSWINDOW_HXX

#include "com/sun/star/beans/XPropertyChangeListener.hpp"
#include "cppuhelper/implbase1.hxx"

namespace com { namespace sun { namespace star {
    namespace beans { class XPropertySet; }
    namespace lang { class XMultiServiceFactory; }
} } }
namespace binfilter {

class SfxApplication;

namespace sfx2 { namespace appl {

// The MS compiler needs this typedef work-around to accept the using
// declarations within ImeStatusWindow:
typedef cppu::WeakImplHelper1< ::com::sun::star::beans::XPropertyChangeListener >
ImeStatusWindow_Impl;

/** Control the behavior of any (platform-dependent) IME status windows.

    The decision of whether a status window shall be displayed or not can be
    stored permanently in the configuration (under key
    org.openoffice.office.Common/I18N/InputMethod/ShowStatusWindow; if that
    entry is nil, VCL is asked for a default).
 */
class ImeStatusWindow: private ImeStatusWindow_Impl
{
public:
    ImeStatusWindow(SfxApplication & rApplication,
                    ::com::sun::star::uno::Reference<
                            ::com::sun::star::lang::XMultiServiceFactory > const &
                        rServiceFactory);

    /** Set up VCL according to the configuration.

        Is it not strictly required that this method is called exactly once
        (though that will be the typical use).

        Must only be called with the Solar mutex locked.
     */
    void init();

    /** Return true if the status window is toggled on.

        This is only meaningful when canToggle returns true.

        Can be called without the Solar mutex locked.
     */
    bool isShowing();

    /** Toggle the status window on or off.

        This only works if canToggle returns true (otherwise, any calls of this
        method are ignored).

        Must only be called with the Solar mutex locked.
     */
    void show(bool bShow);

    /** Return true if the status window can be toggled on and off externally.

        Must only be called with the Solar mutex locked.
     */
    bool canToggle() const;

    // At least the Solaris "CC: Forte Developer 7 C++ 5.4 2002/03/09" compiler
    // does not accept the following using-declarations for virtual functions,
    // so use (deprecated) access declarations instead:
    /*using*/ ImeStatusWindow_Impl::acquire;
    /*using*/ ImeStatusWindow_Impl::release;
    using ImeStatusWindow_Impl::operator new;
    using ImeStatusWindow_Impl::operator delete;

private:
    ImeStatusWindow(ImeStatusWindow &); // not implemented
    void operator =(ImeStatusWindow); // not implemented

    virtual ~ImeStatusWindow();

    virtual void SAL_CALL
    disposing(::com::sun::star::lang::EventObject const & rSource)
        throw (::com::sun::star::uno::RuntimeException);

    virtual void SAL_CALL
    propertyChange(::com::sun::star::beans::PropertyChangeEvent const & rEvent)
        throw (::com::sun::star::uno::RuntimeException);

    ::com::sun::star::uno::Reference< ::com::sun::star::beans::XPropertySet >
    getConfig();

    SfxApplication & m_rApplication;
    ::com::sun::star::uno::Reference< ::com::sun::star::lang::XMultiServiceFactory >
        m_xServiceFactory;

    osl::Mutex m_aMutex;
    ::com::sun::star::uno::Reference< ::com::sun::star::beans::XPropertySet >
        m_xConfig;
    bool m_bDisposed;
};

} }

}//end of namespace binfilter
#endif // INCLUDED_SFX2_APPL_IMESTATUSWINDOW_HXX
