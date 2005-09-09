/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: xmloff_eventimport.cxx,v $
 *
 *  $Revision: 1.3 $
 *
 *  last change: $Author: rt $ $Date: 2005-09-09 09:12:09 $
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

#ifndef _XMLOFF_FORMS_EVENTIMPORT_HXX_
#include "eventimport.hxx"
#endif
#ifndef _COM_SUN_STAR_SCRIPT_XEVENTATTACHERMANAGER_HPP_
#include <com/sun/star/script/XEventAttacherManager.hpp>
#endif
// auto strip #ifndef _COM_SUN_STAR_BEANS_PROPERTYVALUE_HPP_
// auto strip #include <com/sun/star/beans/PropertyValue.hpp>
// auto strip #endif
#ifndef _COMPHELPER_EXTRACT_HXX_
#include <comphelper/extract.hxx>
#endif
#ifndef _XMLOFF_FORMS_STRINGS_HXX_
#include "strings.hxx"
#endif
namespace binfilter {

//.........................................................................
namespace xmloff
{
//.........................................................................

    using namespace ::com::sun::star::uno;
    using namespace ::com::sun::star::beans;
    using namespace ::com::sun::star::script;
    using namespace ::com::sun::star::container;

    //=====================================================================
    //= OFormEventsImportContext
    //=====================================================================
    //---------------------------------------------------------------------
    OFormEventsImportContext::OFormEventsImportContext(SvXMLImport& _rImport, sal_uInt16 _nPrefix, const ::rtl::OUString& _rLocalName, IEventAttacher& _rEventAttacher)
        :XMLEventsImportContext(_rImport, _nPrefix, _rLocalName)
        ,m_rEventAttacher(_rEventAttacher)
    {
    }

    //---------------------------------------------------------------------
    void OFormEventsImportContext::EndElement()
    {
        Sequence< ScriptEventDescriptor > aTranslated(aCollectEvents.size());
        ScriptEventDescriptor* pTranslated = aTranslated.getArray();

        // loop through the collected events and translate them
        const PropertyValue* pEventDescription;
        const PropertyValue* pEventDescriptionEnd;
        sal_Int32 nSeparatorPos = -1;
        for	(	EventsVector::const_iterator aEvent = aCollectEvents.begin();
                aEvent != aCollectEvents.end();
                ++aEvent, ++pTranslated
            )
        {
            // the name of the event is built from ListenerType::EventMethod
            nSeparatorPos = aEvent->first.indexOf(EVENT_NAME_SEPARATOR);
            OSL_ENSURE(-1 != nSeparatorPos, "OFormEventsImportContext::EndElement: invalid (unrecognized) event name!");
            pTranslated->ListenerType = aEvent->first.copy(0, nSeparatorPos);
            pTranslated->EventMethod = aEvent->first.copy(nSeparatorPos + EVENT_NAME_SEPARATOR.length);

            ::rtl::OUString sLibrary;

            // the local macro name and the event type are specified as properties
            pEventDescription		=						aEvent->second.getConstArray();
            pEventDescriptionEnd	=	pEventDescription + aEvent->second.getLength();
            for (;pEventDescription != pEventDescriptionEnd; ++pEventDescription)
            {
                if (0 == pEventDescription->Name.compareToAscii(EVENT_LOCALMACRONAME))
                    pEventDescription->Value >>= pTranslated->ScriptCode;
                else if (0 == pEventDescription->Name.compareToAscii(EVENT_TYPE))
                    pEventDescription->Value >>= pTranslated->ScriptType;
                else if ( 0 == pEventDescription->Name.compareToAscii( EVENT_LIBRARY ) )
                    pEventDescription->Value >>= sLibrary;
            }

            if ( 0 == pTranslated->ScriptType.compareToAscii( EVENT_STARBASIC ) )
            {
                if ( 0 == sLibrary.compareToAscii( EVENT_STAROFFICE ) )
                    sLibrary = EVENT_APPLICATION;

                if ( sLibrary.getLength() )
                {
                    // for StarBasic, the library is prepended
                    sal_Unicode cLibSeparator = ':';
                    sLibrary += ::rtl::OUString( &cLibSeparator, 1 );
                }
                sLibrary += pTranslated->ScriptCode;
                pTranslated->ScriptCode = sLibrary;
            }
        }

        // register the events
        m_rEventAttacher.registerEvents(aTranslated);

        XMLEventsImportContext::EndElement();
    }

    //=====================================================================
    //= ODefaultEventAttacherManager
    //=====================================================================
    //-------------------------------------------------------------------------
    void ODefaultEventAttacherManager::registerEvents(const Reference< XPropertySet >& _rxElement,
        const Sequence< ScriptEventDescriptor >& _rEvents)
    {
        OSL_ENSURE(m_aEvents.end() == m_aEvents.find(_rxElement),
            "ODefaultEventAttacherManager::registerEvents: already have events for this object!");
        // for the moment, only remember the script events
        m_aEvents[_rxElement] = _rEvents;
    }

    //-------------------------------------------------------------------------
    void ODefaultEventAttacherManager::setEvents(const Reference< XIndexAccess >& _rxContainer)
    {
        Reference< XEventAttacherManager > xEventManager(_rxContainer, UNO_QUERY);
        if (!xEventManager.is())
        {
            OSL_ENSURE(sal_False, "ODefaultEventAttacherManager::setEvents: invalid argument!");
            return;
        }

        // loop through all elements
        sal_Int32 nCount = _rxContainer->getCount();
        Reference< XPropertySet > xCurrent;
        ConstMapPropertySet2ScriptSequenceIterator aRegisteredEventsPos;
        for (sal_Int32 i=0; i<nCount; ++i)
        {
            ::cppu::extractInterface(xCurrent, _rxContainer->getByIndex(i));
            if (xCurrent.is())
            {
                aRegisteredEventsPos = m_aEvents.find(xCurrent);
                if (m_aEvents.end() != aRegisteredEventsPos)
                    xEventManager->registerScriptEvents(i, aRegisteredEventsPos->second);
            }
        }
    }

//.........................................................................
}	// namespace xmloff
//.........................................................................


}//end of namespace binfilter
