/*************************************************************************
 *
 *  $RCSfile: saxbuilder.cxx,v $
 *
 *  $Revision: 1.1 $
 *
 *  last change: $Author: lo $ $Date: 2004-01-28 16:31:43 $
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
 *  Copyright: 2004 by Sun Microsystems, Inc.
 *
 *  All Rights Reserved.
 *
 *  Contributor(s): _______________________________________
 *
 *
 ************************************************************************/

#include <stdio.h>
#include "saxbuilder.hxx"
#include <com/sun/star/xml/dom/XDocumentBuilder.hpp>
#include <libxml/tree.h>
#include <com/sun/star/lang/XUnoTunnel.hpp>
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

        // some debugging...
        
        Reference< XUnoTunnel > aTun(m_aDocument, UNO_QUERY);
        xmlNodePtr pNode = (xmlNodePtr) aTun->getSomething(Sequence< sal_Int8 >());
        if( pNode->type == XML_DOCUMENT_NODE )
        {
            xmlDocPtr pDoc = (xmlDocPtr)pNode;
            FILE *f = fopen("c:\\xmlout.xml", "w");
            xmlDocDump(f, pDoc);
            fclose(f);
        }
        
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

    void SAL_CALL  CSAXDocumentBuilder::startDocument() throw (SAXException)
    {

        fprintf(stderr, "startdocument\n");
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

    void SAL_CALL CSAXDocumentBuilder::endDocument() throw (SAXException)
    {
        fprintf(stderr, "enddocument\n");
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
        throw (SAXException)    
    {
        fprintf(stderr, "startElement <%s>\n", OUStringToOString(aName, RTL_TEXTENCODING_UTF8).getStr());

        if ( m_aState != SAXDocumentBuilderState_BUILDING_DOCUMENT &&
             m_aState != SAXDocumentBuilderState_BUILDING_FRAGMENT)
        {
            fprintf(stderr, "illegal state in startElement()\n");
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
                fprintf(stderr, "new namespace mapping: %s -> %s\n",
                    OUStringToOString(newprefix, RTL_TEXTENCODING_UTF8).getStr(),
                    OUStringToOString(attr_value, RTL_TEXTENCODING_UTF8).getStr());
            }
            else if (attr_qname == OUString::createFromAscii("xmlns"))
            {
                // new default prefix
                fprintf(stderr, "new default NS: %s\n",
                    OUStringToOString(attr_value, RTL_TEXTENCODING_UTF8).getStr());
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
            if(idx != -1)            
            {
                aPrefix = attr_qname.copy(0, idx);
            }
            else
                aPrefix = OUString();

             fprintf(stderr, "set attribute: %s=\"%s\"\n",        
                OUStringToOString(attr_qname, RTL_TEXTENCODING_UTF8).getStr(),
                OUStringToOString(attr_value, RTL_TEXTENCODING_UTF8).getStr());
             
            result = aNSMap.find(aPrefix);
            if (result != aNSMap.end())
            {
                // set attribute with namespace
                aElement->setAttributeNS(result->second, attr_qname, attr_value);
            } else {
                // set attribute without namespace
                aElement->setAttribute(attr_qname, attr_value);
           }        
            a++;
        }
        m_aNSStack.push(aNSMap);
    }

    void SAL_CALL CSAXDocumentBuilder::endElement(const OUString& aName) 
        throw (SAXException)
    {
        fprintf(stderr, "endElement </%s>\n", OUStringToOString(aName, RTL_TEXTENCODING_UTF8).getStr());
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
        throw (SAXException)
    {
        fprintf(stderr, "characters [%s]\n", OUStringToOString(aChars, RTL_TEXTENCODING_UTF8).getStr());
        //  append text node to the current top element
         if (m_aState != SAXDocumentBuilderState_BUILDING_DOCUMENT &&
             m_aState != SAXDocumentBuilderState_BUILDING_FRAGMENT)
            throw SAXException();
    
         Reference< XText > aText = m_aDocument->createTextNode(aChars);
         m_aNodeStack.top()->appendChild(Reference< XNode >(aText, UNO_QUERY));
    }

    void SAL_CALL CSAXDocumentBuilder::ignorableWhitespace(const OUString& aSpaces)
        throw (SAXException)
    { 
        fprintf(stderr, "whitespace: [%s]\n", OUStringToOString(aSpaces, RTL_TEXTENCODING_UTF8).getStr());
        //  ignore ignorable whitespace
        if ( m_aState != SAXDocumentBuilderState_BUILDING_DOCUMENT &&
             m_aState != SAXDocumentBuilderState_BUILDING_FRAGMENT)
            throw SAXException();
    }

    void SAL_CALL CSAXDocumentBuilder::processingInstruction(const OUString& aTarget, const OUString& aData)
        throw (SAXException)
    {
        fprintf(stderr, "processinginstruction: [target=%s, data=%s]\n", OUStringToOString(aTarget, RTL_TEXTENCODING_UTF8).getStr(),
                OUStringToOString(aData, RTL_TEXTENCODING_UTF8).getStr());
        //  append PI node to the current top
        if ( m_aState != SAXDocumentBuilderState_BUILDING_DOCUMENT &&
             m_aState != SAXDocumentBuilderState_BUILDING_FRAGMENT)
            throw SAXException();
        
        Reference< XProcessingInstruction > aInstruction = m_aDocument->createProcessingInstruction(
                aTarget, aData);
        m_aNodeStack.top()->appendChild(Reference< XNode >(aInstruction, UNO_QUERY));
    }

    void SAL_CALL CSAXDocumentBuilder::setDocumentLocator(const Reference< XLocator >& aLocator)
        throw (SAXException)
    {
        fprintf(stderr, "setdocumentlocator\n");
        // set the document locator...
        m_aLocator = aLocator;
    }    
}
