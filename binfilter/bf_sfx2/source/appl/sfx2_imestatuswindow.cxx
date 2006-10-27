/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: sfx2_imestatuswindow.cxx,v $
 *
 *  $Revision: 1.5 $
 *
 *  last change: $Author: rt $ $Date: 2006-10-27 18:58:03 $
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

#include "imestatuswindow.hxx"

#include "app.hxx"
#include "sfxsids.hrc"

#include "com/sun/star/beans/PropertyValue.hpp"
#include "com/sun/star/beans/XPropertySet.hpp"
#include "com/sun/star/lang/DisposedException.hpp"
#include "com/sun/star/util/XChangesBatch.hpp"
#include "osl/diagnose.h"
#include "rtl/ustring.h"
#include "sal/types.h"
#include "vos/mutex.hxx"

namespace binfilter {

namespace css = ::com::sun::star;

using sfx2::appl::ImeStatusWindow;

ImeStatusWindow::ImeStatusWindow(
    SfxApplication & rApplication,
    css::uno::Reference< css::lang::XMultiServiceFactory > const &
        rServiceFactory):
    m_rApplication(rApplication),
    m_xServiceFactory(rServiceFactory),
    m_bDisposed(false)
{}

void ImeStatusWindow::init()
{
    if (Application::CanToggleImeStatusWindow())
        try
        {
            sal_Bool bShow;
            if (getConfig()->getPropertyValue(
                    ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM(
                                      "ShowStatusWindow")))
                >>= bShow)
                Application::ShowImeStatusWindow(bShow);
        }
        catch (css::uno::Exception &)
        {
            OSL_ENSURE(false, "com.sun.star.uno.Exception");
            // Degrade gracefully and use the VCL-supplied default if no
            // configuration is available.
        }
}

bool ImeStatusWindow::isShowing()
{
    try
    {
        sal_Bool bShow;
        if (getConfig()->getPropertyValue(
                ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("ShowStatusWindow")))
            >>= bShow)
            return bShow;
    }
    catch (css::uno::Exception &)
    {
        OSL_ENSURE(false, "com.sun.star.uno.Exception");
        // Degrade gracefully and use the VCL-supplied default if no
        // configuration is available.
    }
    return Application::GetShowImeStatusWindowDefault();
}

void ImeStatusWindow::show(bool bShow)
{
    try
    {
        css::uno::Reference< css::beans::XPropertySet > xConfig(getConfig());
        xConfig->setPropertyValue(
            ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("ShowStatusWindow")),
            css::uno::makeAny(static_cast< sal_Bool >(bShow)));
        css::uno::Reference< css::util::XChangesBatch > xCommit(
            xConfig, css::uno::UNO_QUERY);
        // Degrade gracefully by not saving the settings permanently:
        if (xCommit.is())
            xCommit->commitChanges();
        // Alternatively, setting the VCL status could be done even if updating
        // the configuration failed:
        Application::ShowImeStatusWindow(bShow);
    }
    catch (css::uno::Exception &)
    {
        OSL_ENSURE(false, "com.sun.star.uno.Exception");
    }
}

bool ImeStatusWindow::canToggle() const
{
    return Application::CanToggleImeStatusWindow();
}

ImeStatusWindow::~ImeStatusWindow()
{
    if (m_xConfig.is())
        // We should never get here, but just in case...
        try
        {
            m_xConfig->removePropertyChangeListener(
                ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("ShowStatusWindow")),
                this);
        }
        catch (css::uno::Exception &)
        {
            OSL_ENSURE(false, "com.sun.star.uno.RuntimeException");
        }
}

void SAL_CALL ImeStatusWindow::disposing(css::lang::EventObject const & rSource)
    throw (css::uno::RuntimeException)
{
    osl::MutexGuard aGuard(m_aMutex);
    m_xConfig = 0;
    m_bDisposed = true;
}

void SAL_CALL
ImeStatusWindow::propertyChange(css::beans::PropertyChangeEvent const & rEvent)
    throw (css::uno::RuntimeException)
{
    vos::OGuard aGuard(Application::GetSolarMutex());
    m_rApplication.Invalidate(SID_SHOW_IME_STATUS_WINDOW);
}

css::uno::Reference< css::beans::XPropertySet > ImeStatusWindow::getConfig()
{
    css::uno::Reference< css::beans::XPropertySet > xConfig;
    bool bAdd = false;
    {
        osl::MutexGuard aGuard(m_aMutex);
        if (!m_xConfig.is())
        {
            if (m_bDisposed)
                throw css::lang::DisposedException();
            if (!m_xServiceFactory.is())
                throw css::uno::RuntimeException(
                    ::rtl::OUString(
                        RTL_CONSTASCII_USTRINGPARAM(
                            "null ::legacy_binfilters::getLegacyProcessServiceFactory()")),
                    0);
            css::uno::Reference< css::lang::XMultiServiceFactory > xProvider(
                m_xServiceFactory->createInstance(
                    ::rtl::OUString(
                        RTL_CONSTASCII_USTRINGPARAM(
                          "com.sun.star.configuration.ConfigurationProvider"))),
                css::uno::UNO_QUERY);
            if (!xProvider.is())
                throw css::uno::RuntimeException(
                    ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM(
                                      "null com.sun.star.configuration."
                                      "ConfigurationProvider")),
                    0);
            css::beans::PropertyValue aArg(
                ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("nodepath")), -1,
                css::uno::makeAny(
                    ::rtl::OUString(
                        RTL_CONSTASCII_USTRINGPARAM(
                            "/org.openoffice.Office.Common/I18N/InputMethod"))),
                css::beans::PropertyState_DIRECT_VALUE);
            css::uno::Sequence< css::uno::Any > aArgs(1);
            aArgs[0] <<= aArg;
            m_xConfig
                = css::uno::Reference< css::beans::XPropertySet >(
                    xProvider->createInstanceWithArguments(
                        ::rtl::OUString(
                            RTL_CONSTASCII_USTRINGPARAM(
                       "com.sun.star.configuration.ConfigurationUpdateAccess")),
                        aArgs),
                    css::uno::UNO_QUERY);
            if (!m_xConfig.is())
                throw css::uno::RuntimeException(
                    ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM(
                                      "null com.sun.star.configuration."
                                      "ConfigurationUpdateAccess")),
                    0);
            bAdd = true;
        }
        xConfig = m_xConfig;
    }
    if (bAdd)
        // Exceptions here could be handled individually, to support graceful
        // degradation (no update notification mechanism in this case---but also
        // no dispose notifications):
        xConfig->addPropertyChangeListener(
            ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("ShowStatusWindow")),
            this);
    return xConfig;
}

}
