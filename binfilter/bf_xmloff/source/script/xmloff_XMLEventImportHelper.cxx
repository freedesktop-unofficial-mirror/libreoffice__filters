/*************************************************************************
 *
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER.
 * 
 * Copyright 2008 by Sun Microsystems, Inc.
 *
 * OpenOffice.org - a multi-platform office productivity suite
 *
 * $RCSfile: xmloff_XMLEventImportHelper.cxx,v $
 * $Revision: 1.5 $
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

#ifndef _XMLOFF_XMLEVENTIMPORTHELPER_HXX
#include "XMLEventImportHelper.hxx"
#endif

#ifndef _TOOLS_DEBUG_HXX
#include <tools/debug.hxx>
#endif

#ifndef _XMLOFF_XMLIMP_HXX
#include "xmlimp.hxx"
#endif



#ifndef _XMLOFF_XMLERROR_HXX
#include "xmlerror.hxx"
#endif
namespace binfilter {

using ::rtl::OUString;
using ::com::sun::star::xml::sax::XAttributeList;
using ::com::sun::star::uno::Reference;
using ::com::sun::star::uno::Sequence;

XMLEventImportHelper::XMLEventImportHelper() :
    aFactoryMap(),
    pEventNameMap(new NameMap()),
    aEventNameMapList()
{
}


XMLEventImportHelper::~XMLEventImportHelper()
{
    // delete factories
    FactoryMap::iterator aEnd = aFactoryMap.end();
    for(FactoryMap::iterator aIter = aFactoryMap.begin(); 
        aIter != aEnd; 
        aIter++ )
    {
        delete aIter->second;
    }
    aFactoryMap.clear();

    // delete name map
    delete pEventNameMap;
}

void XMLEventImportHelper::RegisterFactory( 
    const OUString& rLanguage,
    XMLEventContextFactory* pFactory )
{
    DBG_ASSERT(pFactory != NULL, "I need a factory.");
    if (NULL != pFactory)
    {
        aFactoryMap[rLanguage] = pFactory;
    }
}

void XMLEventImportHelper::AddTranslationTable( 
    const XMLEventNameTranslation* pTransTable )
{
    if (NULL != pTransTable)
    {
        // put translation table into map
        for(const XMLEventNameTranslation* pTrans = pTransTable;
            pTrans->sAPIName != NULL;
            pTrans++)
        {
            OUString rName(OUString::createFromAscii(pTrans->sXMLName));

            // check for conflicting entries
            DBG_ASSERT(pEventNameMap->find(rName) == pEventNameMap->end(),
                       "conflicting event translations");

            // assign new translation
            (*pEventNameMap)[rName] = 
                OUString::createFromAscii(pTrans->sAPIName);
        }
    }
    // else? ignore!
}

void XMLEventImportHelper::PushTranslationTable()
{
    // save old map and install new one
    aEventNameMapList.push_back(pEventNameMap);
    pEventNameMap = new NameMap();
}

void XMLEventImportHelper::PopTranslationTable()
{
    DBG_ASSERT(aEventNameMapList.size() > 0, 
               "no translation tables left to pop");
    if (aEventNameMapList.size() > 0)
    {
        // delete current and install old map
        delete pEventNameMap;
        pEventNameMap = aEventNameMapList.back();
        aEventNameMapList.pop_back();
    }
}


SvXMLImportContext* XMLEventImportHelper::CreateContext(
    SvXMLImport& rImport,
    sal_uInt16 nPrefix,
    const OUString& rLocalName,
    const Reference<XAttributeList> & xAttrList,
    XMLEventsImportContext* rEvents,
    const OUString& rXmlEventName,
    const OUString& rLanguage)
{
    SvXMLImportContext* pContext = NULL;

    // translate event name form xml to api
    NameMap::iterator aNameIter = pEventNameMap->find(rXmlEventName);
    if (aNameIter != pEventNameMap->end())
    {
        // check for factory
        FactoryMap::iterator aFactoryIterator = aFactoryMap.find(rLanguage);
        if (aFactoryIterator != aFactoryMap.end())
        {
            // delegate to factory
            pContext = aFactoryIterator->second->CreateContext(
                rImport, nPrefix, rLocalName, xAttrList, 
                rEvents, aNameIter->second, rLanguage);
        }
    }

    // default context (if no context was created above)
    if( NULL == pContext )
    {
        pContext = new SvXMLImportContext(rImport, nPrefix, rLocalName);

        Sequence<OUString> aMsgParams(2);
        
        aMsgParams[0] = rXmlEventName;
        aMsgParams[1] = rLanguage;
        
        rImport.SetError(XMLERROR_FLAG_ERROR | XMLERROR_ILLEGAL_EVENT,
                         aMsgParams);
        
    }

    return pContext;
}
}//end of namespace binfilter
