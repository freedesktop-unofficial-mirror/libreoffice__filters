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
#if defined(_MSC_VER) && (_MSC_VER > 1310)
#pragma warning(disable : 4701)
#endif

#include "node.hxx"
#include "saxbuilder.hxx"
#include <com/sun/star/xml/dom/XDocumentBuilder.hpp>
#include <libxml/tree.h>
#include <com/sun/star/uno/Sequence.h>

namespace DOM
{
    Reference< XInterface > CSAXDocumentBuilder::_getInstance(const Reference< XMultiServiceFactory >& rSMgr)
    {
        return static_cast< XSAXDocumentBuilder* >(new CSAXDocumentBuilder(rSMgr));
    }

    const char* CSAXDocumentBuilder::aImplementationName = "com.sun.star.comp.xml.dom.SAXDocumentBuilder";
    const char* CSAXDocumentBuilder::aSupportedServiceNames[] = {
        "com.sun.star.xml.dom.SAXDocumentBuilder",
        NULL
    };

    CSAXDocumentBuilder::CSAXDocumentBuilder(const Reference< XMultiServiceFactory >& mgr)
        : m_aServiceManager(mgr)
        , m_aState( SAXDocumentBuilderState_READY)
    {}

    OUString CSAXDocumentBuilder::_getImplementationName()
    {
        return OUString::createFromAscii(aImplementationName);
    }
    Sequence<OUString> CSAXDocumentBuilder::_getSupportedServiceNames()
    {
        Sequence<OUString> aSequence;
        for (int i=0; aSupportedServiceNames[i]!=NULL; i++) {
            aSequence.realloc(i+1);
            aSequence[i]=(OUString::createFromAscii(aSupportedServiceNames[i]));
        }
        return aSequence;
    }

    Sequence< OUString > SAL_CALL CSAXDocumentBuilder::getSupportedServiceNames()
        throw (RuntimeException)
    {
        return CSAXDocumentBuilder::_getSupportedServiceNames();
    }

    OUString SAL_CALL CSAXDocumentBuilder::getImplementationName()
        throw (RuntimeException)
    {
        return CSAXDocumentBuilder::_getImplementationName();
    }

    sal_Bool SAL_CALL CSAXDocumentBuilder::supportsService(const OUString& aServiceName)
        throw (RuntimeException)
    {
        Sequence< OUString > supported = CSAXDocumentBuilder::_getSupportedServiceNames();
        for (sal_Int32 i=0; i<supported.getLength(); i++)
        {
            if (supported[i] == aServiceName) return sal_True;
        }
        return sal_False;
    }


    SAXDocumentBuilderState SAL_CALL CSAXDocumentBuilder::getState()
        throw (RuntimeException)
    {
        return m_aState;
    }

    void SAL_CALL CSAXDocumentBuilder::reset()
        throw (RuntimeException)
    {
        m_aDocument = Reference< XDocument >();
        m_aFragment = Reference< XDocumentFragment >();
        while (!m_aNodeStack.empty()) m_aNodeStack.pop();
        while (!m_aNSStack.empty()) m_aNSStack.pop();
        m_aState = SAXDocumentBuilderState_READY;
    }

    Reference< XDocument > SAL_CALL CSAXDocumentBuilder::getDocument()
        throw (RuntimeException)
    {
        if (m_aState != SAXDocumentBuilderState_DOCUMENT_FINISHED)
            throw RuntimeException();

        return m_aDocument;
    }

    Reference< XDocumentFragment > SAL_CALL CSAXDocumentBuilder::getDocumentFragment()
         throw (RuntimeException)
    {
        if (m_aState != SAXDocumentBuilderState_FRAGMENT_FINISHED)
            throw RuntimeException();
        return m_aFragment;
    }

    void SAL_CALL CSAXDocumentBuilder::startDocumentFragment(const Reference< XDocument >& ownerDoc)
        throw (RuntimeException)
    {
        // start a new document fragment and push it onto the stack
        // we have to be in a clean state to do this
        if (!m_aState == SAXDocumentBuilderState_READY)
            throw RuntimeException();

        m_aDocument = ownerDoc;
        Reference< XDocumentFragment > aFragment = m_aDocument->createDocumentFragment();
        m_aNodeStack.push(Reference< XNode >(aFragment, UNO_QUERY));
        m_aFragment = aFragment;
        m_aState = SAXDocumentBuilderState_BUILDING_FRAGMENT;
    }

    void SAL_CALL CSAXDocumentBuilder::endDocumentFragment()
        throw (RuntimeException)
    {
        // there should only be the document left on the node stack
        if (m_aState != SAXDocumentBuilderState_BUILDING_FRAGMENT)
            throw RuntimeException();

        Reference< XNode > aNode = m_aNodeStack.top();
        if ( aNode->getNodeType() != NodeType_DOCUMENT_FRAGMENT_NODE)
            throw RuntimeException();
        m_aNodeStack.pop();
        m_aState = SAXDocumentBuilderState_FRAGMENT_FINISHED;
    }

    // document handler

    void SAL_CALL  CSAXDocumentBuilder::startDocument() throw (RuntimeException, SAXException)
    {

        // start a new document and push it onto the stack
        // we have to be in a clean state to do this
        if (!m_aState == SAXDocumentBuilderState_READY)
            throw SAXException();

        Reference< XDocumentBuilder > aBuilder(m_aServiceManager->createInstance(
                OUString::createFromAscii("com.sun.star.xml.dom.DocumentBuilder")), UNO_QUERY_THROW);
        Reference< XDocument > aDocument = aBuilder->newDocument();
        m_aNodeStack.push(Reference< XNode >(aDocument, UNO_QUERY));
        m_aDocument = aDocument;
        m_aState = SAXDocumentBuilderState_BUILDING_DOCUMENT;
    }

    void SAL_CALL CSAXDocumentBuilder::endDocument() throw (RuntimeException, SAXException)
    {
        // there should only be the document left on the node stack
        if (!m_aState == SAXDocumentBuilderState_BUILDING_DOCUMENT)
            throw SAXException();

        Reference< XNode > aNode = m_aNodeStack.top();
        if ( aNode->getNodeType() != NodeType_DOCUMENT_NODE)
            throw SAXException();
        m_aNodeStack.pop();
        m_aState = SAXDocumentBuilderState_DOCUMENT_FINISHED;
    }

    void SAL_CALL CSAXDocumentBuilder::startElement(const OUString& aName, const Reference< XAttributeList>& attribs)
        throw (RuntimeException, SAXException)
    {
        if ( m_aState != SAXDocumentBuilderState_BUILDING_DOCUMENT &&
             m_aState != SAXDocumentBuilderState_BUILDING_FRAGMENT)
        {
            throw SAXException();
        }

        // start with mappings in effect for last level
        NSMap aNSMap;
        if (!m_aNSStack.empty())
            aNSMap = NSMap(m_aNSStack.top());

        // handle xmlns: attributes and add to mappings
        OUString attr_qname;
        OUString attr_value;
        OUString newprefix;
        AttrMap aAttrMap;
        sal_Int32 idx=-1;
        sal_Int16 nAttributes = attribs->getLength();
        for (sal_Int16 i=0; i<nAttributes; i++)
        {
            attr_qname = attribs->getNameByIndex(i);
            attr_value = attribs->getValueByIndex(i);
            // new prefix mapping
            if (attr_qname.indexOf(OUString::createFromAscii("xmlns:")) == 0)
            {
                newprefix = attr_qname.copy(attr_qname.indexOf(':')+1);
                aNSMap.insert(NSMap::value_type(newprefix, attr_value));
            }
            else if (attr_qname == OUString::createFromAscii("xmlns"))
            {
                // new default prefix
                aNSMap.insert(NSMap::value_type(OUString(), attr_value));
            }
            else
            {
                aAttrMap.insert(AttrMap::value_type(attr_qname, attr_value));
            }
        }

        // does the element have a prefix?
        OUString aPrefix;
        OUString aURI;
        Reference< XElement > aElement;
        idx = aName.indexOf(':');
        if (idx != -1)
        {
            aPrefix = aName.copy(0, idx);
        }
        else
            aPrefix = OUString();

        NSMap::const_iterator result = aNSMap.find(aPrefix);
        if ( result != aNSMap.end())
        {
            // found a URI for prefix
            aElement = m_aDocument->createElementNS( result->second, aName); // qualified name 
        }
        else
        {
            // no URI for prefix
            aElement = m_aDocument->createElement(aName);
        }
        aElement = Reference< XElement > (
            m_aNodeStack.top()->appendChild(Reference< XNode >(aElement, UNO_QUERY)),
            UNO_QUERY);
        m_aNodeStack.push(Reference< XNode >(aElement, UNO_QUERY));

        // set non xmlns attributes
        aPrefix = OUString();
        aURI = OUString();
        AttrMap::const_iterator a = aAttrMap.begin();
        while (a != aAttrMap.end())
        {
            attr_qname = a->first;
            attr_value = a->second;
            idx = attr_qname.indexOf(':');
            if (idx != -1)
                aPrefix = attr_qname.copy(0, idx);
            else
                aPrefix = OUString();

            result = aNSMap.find(aPrefix);
            if (result != aNSMap.end())
            {
                // set attribute with namespace
                aElement->setAttributeNS(result->second, attr_qname, attr_value);
            }
            else
            {
                // set attribute without namespace
                aElement->setAttribute(attr_qname, attr_value);
            }
            ++a;
        }
        m_aNSStack.push(aNSMap);
    }

    void SAL_CALL CSAXDocumentBuilder::endElement(const OUString& aName)
        throw (RuntimeException, SAXException)
    {
        // pop the current element from the stack
        if ( m_aState != SAXDocumentBuilderState_BUILDING_DOCUMENT &&
             m_aState != SAXDocumentBuilderState_BUILDING_FRAGMENT)
            throw SAXException();

        Reference< XNode > aNode(m_aNodeStack.top());
        if (aNode->getNodeType() != NodeType_ELEMENT_NODE)
            throw SAXException();

        Reference< XElement > aElement(aNode, UNO_QUERY);
        OUString aRefName;
        OUString aPrefix = aElement->getPrefix();
        if (aPrefix.getLength() > 0)
            aRefName = aPrefix + OUString::createFromAscii(":") + aElement->getTagName();
        else
            aRefName = aElement->getTagName();
        if (aRefName != aName) // consistency check
            throw SAXException();

        // pop it
        m_aNodeStack.pop();
        m_aNSStack.pop();
    }

    void SAL_CALL CSAXDocumentBuilder::characters(const OUString& aChars)
        throw (RuntimeException, SAXException)
    {
        //  append text node to the current top element
         if (m_aState != SAXDocumentBuilderState_BUILDING_DOCUMENT &&
             m_aState != SAXDocumentBuilderState_BUILDING_FRAGMENT)
            throw SAXException();

         Reference< XText > aText = m_aDocument->createTextNode(aChars);
         m_aNodeStack.top()->appendChild(Reference< XNode >(aText, UNO_QUERY));
    }

    void SAL_CALL CSAXDocumentBuilder::ignorableWhitespace(const OUString& )
        throw (RuntimeException, SAXException)
    {
        //  ignore ignorable whitespace
        if ( m_aState != SAXDocumentBuilderState_BUILDING_DOCUMENT &&
             m_aState != SAXDocumentBuilderState_BUILDING_FRAGMENT)
            throw SAXException();
    }

    void SAL_CALL CSAXDocumentBuilder::processingInstruction(const OUString& aTarget, const OUString& aData)
        throw (RuntimeException, SAXException)
    {
        //  append PI node to the current top
        if ( m_aState != SAXDocumentBuilderState_BUILDING_DOCUMENT &&
             m_aState != SAXDocumentBuilderState_BUILDING_FRAGMENT)
            throw SAXException();

        Reference< XProcessingInstruction > aInstruction = m_aDocument->createProcessingInstruction(
                aTarget, aData);
        m_aNodeStack.top()->appendChild(Reference< XNode >(aInstruction, UNO_QUERY));
    }

    void SAL_CALL CSAXDocumentBuilder::setDocumentLocator(const Reference< XLocator >& aLocator)
        throw (RuntimeException, SAXException)
    {
        // set the document locator...
        m_aLocator = aLocator;
    }
}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
