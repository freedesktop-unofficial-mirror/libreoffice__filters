/*************************************************************************
 *
 *  $RCSfile: lateinitlistener.cxx,v $
 *
 *  $Revision: 1.2 $
 *
 *  last change: $Author: obo $ $Date: 2004-04-29 13:42:22 $
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

#include "lateinitlistener.hxx"
#include "lateinitthread.hxx"

//_______________________________________________
// includes

#ifndef _RTL_USTRING_HXX_
#include <rtl/ustring.hxx>
#endif

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
void SAL_CALL LateInitListener::disposing(const css::lang::EventObject& aEvent)
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
