/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: xmloff_XMLEventsImportContext.cxx,v $
 *
 *  $Revision: 1.3 $
 *
 *  last change: $Author: rt $ $Date: 2005-09-09 09:19:22 $
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

#ifndef _XMLOFF_XMLEVENTSIMPORTCONTEXT_HXX
#include "XMLEventsImportContext.hxx"
#endif

#ifndef _XMLOFF_XMLEVENTIMPORTHELPER_HXX
#include "XMLEventImportHelper.hxx"
#endif

#ifndef _COM_SUN_STAR_DOCUMENT_XEVENTSSUPPLIER_HPP
#include <com/sun/star/document/XEventsSupplier.hpp>
#endif

// auto strip #ifndef _TOOLS_DEBUG_HXX
// auto strip #include <tools/debug.hxx>
// auto strip #endif

#ifndef _XMLOFF_XMLIMP_HXX
#include "xmlimp.hxx"
#endif

#ifndef _XMLOFF_NMSPMAP_HXX 
#include "nmspmap.hxx"
#endif

#ifndef _XMLOFF_XMLNMSPE_HXX
#include "xmlnmspe.hxx"
#endif

// auto strip #ifndef _XMLOFF_XMLTOKEN_HXX
// auto strip #include "xmltoken.hxx"
// auto strip #endif

#ifndef _XMLOFF_XMLERROR_HXX
#include "xmlerror.hxx"
#endif // _XMLOFF_XMLERROR_HXX
namespace binfilter {

using namespace ::com::sun::star::uno;
using namespace ::binfilter::xmloff::token;

using ::rtl::OUString;
using ::com::sun::star::xml::sax::XAttributeList;
using ::com::sun::star::beans::PropertyValue;
using ::com::sun::star::container::XNameReplace;
using ::com::sun::star::document::XEventsSupplier;
using ::com::sun::star::lang::IllegalArgumentException;

TYPEINIT1(XMLEventsImportContext,  SvXMLImportContext);


XMLEventsImportContext::XMLEventsImportContext(
    SvXMLImport& rImport, 
    sal_uInt16 nPrfx,
    const OUString& rLocalName) :
        SvXMLImportContext(rImport, nPrfx, rLocalName)
{
}


XMLEventsImportContext::XMLEventsImportContext(
    SvXMLImport& rImport, 
    sal_uInt16 nPrfx,
    const OUString& rLocalName,
    const Reference<XEventsSupplier> & xEventsSupplier) :
        SvXMLImportContext(rImport, nPrfx, rLocalName),
        xEvents(xEventsSupplier->getEvents())
{
}


XMLEventsImportContext::XMLEventsImportContext(
    SvXMLImport& rImport, 
    sal_uInt16 nPrfx,
    const OUString& rLocalName,
    const Reference<XNameReplace> & xNameReplace) :
        SvXMLImportContext(rImport, nPrfx, rLocalName),
        xEvents(xNameReplace)
{
}

XMLEventsImportContext::~XMLEventsImportContext()
{
// 	// if, for whatever reason, the object gets destroyed prematurely,
// 	// we need to delete the collected events
// 	EventsVector::iterator aEnd = aCollectEvents.end();
// 	for(EventsVector::iterator aIter = aCollectEvents.begin();
// 		aIter != aEnd;
// 		aIter++)
// 	{
// 		EventNameValuesPair* pPair = &(*aIter);
// 		delete pPair;
// 	}
// 	aCollectEvents.clear();
}


void XMLEventsImportContext::StartElement(
    const Reference<XAttributeList> & xAttrList)
{
    // nothing to be done
}

void XMLEventsImportContext::EndElement()
{
    // nothing to be done
}

SvXMLImportContext* XMLEventsImportContext::CreateChildContext( 
    sal_uInt16 nPrefix,
    const OUString& rLocalName,
    const Reference<XAttributeList> & xAttrList )
{
    // a) search for script:language and script:event-name attribute
    // b) delegate to factory. The factory will:
    //    1) translate XML event name into API event name
    //    2) get proper event context factory from import
    //    3) instantiate context

    // a) search for script:language and script:event-name attribute
    OUString sLanguage;
    OUString sEventName;
    sal_Int16 nCount = xAttrList->getLength();
    for (sal_Int16 nAttr = 0; nAttr < nCount; nAttr++)
    {
        OUString sLocalName;
        sal_uInt16 nPrefix = GetImport().GetNamespaceMap().
            GetKeyByAttrName( xAttrList->getNameByIndex(nAttr), &sLocalName );

        if (XML_NAMESPACE_SCRIPT == nPrefix)
        {
            if (IsXMLToken(sLocalName, XML_EVENT_NAME))
            {
                sEventName = xAttrList->getValueByIndex(nAttr);
            }
            else if (IsXMLToken(sLocalName, XML_LANGUAGE))
            {
                sLanguage = xAttrList->getValueByIndex(nAttr);
            }
            // else: ignore -> let child context handle this
        }
        // else: ignore -> let child context handle this
    }

    // b) delegate to factory
    return GetImport().GetEventImport().CreateContext(
        GetImport(), nPrefix, rLocalName, xAttrList, 
        this, sEventName, sLanguage);
}

void XMLEventsImportContext::SetEvents(
    const Reference<XEventsSupplier> & xEventsSupplier)
{
    if (xEventsSupplier.is())
    {
        SetEvents(xEventsSupplier->getEvents());
    }
}

void XMLEventsImportContext::SetEvents(
    const Reference<XNameReplace> & xNameRepl)
{
    if (xNameRepl.is())
    {
        xEvents = xNameRepl;

        // now iterate over vector and a) insert b) delete all elements
        EventsVector::iterator aEnd = aCollectEvents.end();
        for(EventsVector::iterator aIter = aCollectEvents.begin();
            aIter != aEnd;
            aIter++)
        {
            AddEventValues(aIter->first, aIter->second);
// 			EventNameValuesPair* pPair = &(*aIter);
// 			delete pPair;
        }
        aCollectEvents.clear();
    }
}

sal_Bool XMLEventsImportContext::GetEventSequence(
    const OUString& rName,
    Sequence<PropertyValue> & rSequence )
{
    // search through the vector
    // (This shouldn't take a lot of time, since this method should only get
    //  called if only one (or few) events are being expected)

    // iterate over vector until end or rName is found;
    EventsVector::iterator aIter = aCollectEvents.begin();
    while( (aIter != aCollectEvents.end()) && (aIter->first != rName) )
    {
        aIter++;
    }
    
    // if we're not at the end, set the sequence
    sal_Bool bRet = (aIter != aCollectEvents.end());
    if (bRet)
        rSequence = aIter->second;

    return bRet;
}

void XMLEventsImportContext::AddEventValues( 
    const OUString& rEventName,
    const Sequence<PropertyValue> & rValues )
{
    // if we already have the events, set them; else just collect
    if (xEvents.is())
    {
        // set event (if name is known)
        if (xEvents->hasByName(rEventName))
        {
            Any aAny;
            aAny <<= rValues;
            
            try
            {
                xEvents->replaceByName(rEventName, aAny);
            } catch ( const IllegalArgumentException & rException )
            {
                Sequence<OUString> aMsgParams(1);

                aMsgParams[0] = rEventName;
                
                GetImport().SetError(XMLERROR_FLAG_ERROR | 
                                     XMLERROR_ILLEGAL_EVENT,
                                     aMsgParams, rException.Message, 0);
            }
        }
    }
    else
    {
// 		EventNameValuesPair* aPair = new EventNameValuesPair(rEventName, 
// 															rValues);
// 		aCollectEvents.push_back(*aPair);
        EventNameValuesPair aPair(rEventName, rValues);
        aCollectEvents.push_back(aPair);
    }
}
}//end of namespace binfilter
