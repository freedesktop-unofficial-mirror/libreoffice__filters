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

// MARKER(update_precomp.py): autogen include statement, do not remove
#include "precompiled_filter.hxx"

#include "lateinitlistener.hxx"
#include "lateinitthread.hxx"

//_______________________________________________
// includes
#include <rtl/ustring.hxx>

//_______________________________________________
// namespace

namespace filter{
    namespace config{

namespace css = ::com::sun::star;

//_______________________________________________
// definitions

/*-----------------------------------------------
    14.08.2003 07:35
-----------------------------------------------*/
LateInitListener::LateInitListener(const css::uno::Reference< css::lang::XMultiServiceFactory >& xSMGR)
    : BaseLock(     )
    , m_xSMGR (xSMGR)
{
    // important to do so ...
    // Otherwhise the temp. reference to ourselves
    // will kill us at realeasing time!
    ++m_refCount;

    m_xBroadcaster = css::uno::Reference< css::document::XEventBroadcaster >(
        m_xSMGR->createInstance(::rtl::OUString::createFromAscii("com.sun.star.frame.GlobalEventBroadcaster")),
        css::uno::UNO_QUERY);

    m_xBroadcaster->addEventListener(static_cast< css::document::XEventListener* >(this));

    --m_refCount;
}

/*-----------------------------------------------
    14.08.2003 07:25
-----------------------------------------------*/
LateInitListener::~LateInitListener()
{
}

/*-----------------------------------------------
    14.08.2003 08:45
-----------------------------------------------*/
void SAL_CALL LateInitListener::notifyEvent(const css::document::EventObject& aEvent)
    throw(css::uno::RuntimeException)
{
    // wait for events, which indicates finished open of the first document
    if (
        (aEvent.EventName.equalsAscii("OnNew") ) ||
        (aEvent.EventName.equalsAscii("OnLoad"))
       )
    {
        // this thread must be started one times only ...
        // cancel listener connection before!

        // SAFE ->
        ::osl::ResettableMutexGuard aLock(m_aLock);

        m_xBroadcaster->removeEventListener(static_cast< css::document::XEventListener* >(this));
        m_xBroadcaster.clear();

        aLock.clear();
        // <- SAFE

        LateInitThread* pThread = new LateInitThread();
        pThread->create();
    }
}

/*-----------------------------------------------
    14.08.2003 07:48
-----------------------------------------------*/
void SAL_CALL LateInitListener::disposing(const css::lang::EventObject& /* aEvent */ )
    throw(css::uno::RuntimeException)
{
    // ???
    // Normaly it should never be called. Because we cancel our listener connection
    // if we got the event about finished open of the first office document.
    // But if this method was reached, it indicates an office, which was started
    // (might as remote script container for an external API client) but not realy used.

    // SAFE ->
    ::osl::ResettableMutexGuard aLock(m_aLock);
    m_xBroadcaster.clear();
    aLock.clear();
    // <- SAFE
}

    } // namespace config
} // namespace filter
