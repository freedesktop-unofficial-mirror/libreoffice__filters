/*************************************************************************
 *
 *  $RCSfile: document.hxx,v $
 *
 *  $Revision: 1.3 $
 *
 *  last change: $Author: lo $ $Date: 2004-02-27 16:14:29 $
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

#ifndef _DOCUMENT_HXX
#define _DOCUMENT_HXX

#include <list>
#include <sal/types.h>
#include <cppuhelper/implbase1.hxx>
#include <cppuhelper/implbase2.hxx>
#include <com/sun/star/uno/Reference.h>
#include <com/sun/star/uno/Exception.hpp>
#include <com/sun/star/xml/dom/XNode.hpp>
#include <com/sun/star/xml/dom/XAttr.hpp>
#include <com/sun/star/xml/dom/XElement.hpp>
#include <com/sun/star/xml/dom/XDOMImplementation.hpp>
#include <com/sun/star/xml/dom/events/XDocumentEvent.hpp>
#include <com/sun/star/xml/dom/events/XEvent.hpp>

#include "node.hxx"

#include <libxml/tree.h>

using namespace rtl;
using namespace com::sun::star::uno;
using namespace com::sun::star::lang;
using namespace com::sun::star::xml::dom;
using namespace com::sun::star::xml::dom::events;

namespace DOM
{
    
    typedef std::list< Reference< XNode >* > nodereflist_t;

    class CDocument : public cppu::ImplInheritanceHelper2< CNode, XDocument, XDocumentEvent >
    {
        friend class CNode;
    private:

        nodereflist_t m_aNodeRefList;

        xmlDocPtr m_aDocPtr;
        Reference< XDocumentType > m_rDocType;
        Reference< XElement > m_rDocElement;

    protected:
        CDocument(xmlDocPtr aDocPtr);

        void addnode(xmlNodePtr aNode);
    public:

        virtual ~CDocument();
        
        /**
        Creates an Attr of the given name.
        */
        virtual Reference< XAttr > SAL_CALL createAttribute(const OUString& name)
            throw (DOMException);

        /**
        Creates an attribute of the given qualified name and namespace URI.
        */
        virtual Reference< XAttr > SAL_CALL createAttributeNS(const OUString& namespaceURI, const OUString& qualifiedName)
            throw (DOMException);

        /**
        Creates a CDATASection node whose value is the specified string.
        */
        virtual Reference< XCDATASection > SAL_CALL createCDATASection(const OUString& data)
            throw (RuntimeException);

        /**
        Creates a Comment node given the specified string.
        */
        virtual Reference< XComment > SAL_CALL createComment(const OUString& data)
            throw (RuntimeException);

        /**
        Creates an empty DocumentFragment object.
        */
        virtual Reference< XDocumentFragment > SAL_CALL createDocumentFragment()
            throw (RuntimeException);

        /**
        Creates an element of the type specified.
        */
        virtual Reference< XElement > SAL_CALL createElement(const OUString& tagName)
            throw (DOMException);

        /**
        Creates an element of the given qualified name and namespace URI.
        */
        virtual Reference< XElement > SAL_CALL createElementNS(const OUString& namespaceURI, const OUString& qualifiedName)
            throw (DOMException);

        /**
        Creates an EntityReference object.
        */
        virtual Reference< XEntityReference > SAL_CALL createEntityReference(const OUString& name)
            throw (DOMException);

        /**
        Creates a ProcessingInstruction node given the specified name and 
        data strings.
        */
        virtual Reference< XProcessingInstruction > SAL_CALL createProcessingInstruction(
                const OUString& target, const OUString& data)
            throw (DOMException);

        /**
        Creates a Text node given the specified string.
        */
        virtual Reference< XText > SAL_CALL createTextNode(const OUString& data)
            throw (RuntimeException);

        /**
        The Document Type Declaration (see DocumentType) associated with this
        document.
        */
        virtual Reference< XDocumentType > SAL_CALL getDoctype()
            throw (RuntimeException);

        /**
        This is a convenience attribute that allows direct access to the child
        node that is the root element of the document.
        */
        virtual Reference< XElement > SAL_CALL getDocumentElement()
            throw (RuntimeException);
        
        /**
        Returns the Element whose ID is given by elementId.
        */
        virtual Reference< XElement > SAL_CALL getElementById(const OUString& elementId)
            throw (RuntimeException);

        /**
        Returns a NodeList of all the Elements with a given tag name in the 
        order in which they are encountered in a preorder traversal of the
        Document tree.
        */
        virtual Reference< XNodeList > SAL_CALL getElementsByTagName(const OUString& tagname)
            throw (RuntimeException);

        /**
        Returns a NodeList of all the Elements with a given local name and 
        namespace URI in the order in which they are encountered in a preorder 
        traversal of the Document tree.
        */
        virtual Reference< XNodeList > SAL_CALL getElementsByTagNameNS(const OUString& namespaceURI, const OUString& localName)
            throw (RuntimeException);

        /**
        The DOMImplementation object that handles this document.
        */
        virtual Reference< XDOMImplementation > SAL_CALL getImplementation()
            throw (RuntimeException);

        /**
        Imports a node from another document to this document.
        */
        virtual Reference< XNode > SAL_CALL importNode(const Reference< XNode >& importedNode, sal_Bool deep)
            throw (DOMException);

        // ---- resolve uno inheritance problems...
        // overrides for XNode base
        virtual OUString SAL_CALL getNodeName()
            throw (RuntimeException);
        virtual OUString SAL_CALL getNodeValue()
            throw (RuntimeException);        
    // --- delegation for XNde base.
    virtual Reference< XNode > SAL_CALL appendChild(const Reference< XNode >& newChild)
        throw (DOMException)
    {
        return CNode::appendChild(newChild);
    }
    virtual Reference< XNode > SAL_CALL cloneNode(sal_Bool deep)
        throw (RuntimeException)
    {
        return CNode::cloneNode(deep);
    }
    virtual Reference< XNamedNodeMap > SAL_CALL getAttributes()
        throw (RuntimeException)
    {
        return CNode::getAttributes();
    }
    virtual Reference< XNodeList > SAL_CALL getChildNodes()
        throw (RuntimeException)
    {
        return CNode::getChildNodes();
    }
    virtual Reference< XNode > SAL_CALL getFirstChild()
        throw (RuntimeException)
    {
        return CNode::getFirstChild();
    }
    virtual Reference< XNode > SAL_CALL getLastChild()
        throw (RuntimeException)
    {
        return CNode::getLastChild();
    }
    virtual OUString SAL_CALL getLocalName()
        throw (RuntimeException)
    {
        return CNode::getLocalName();
    }
    virtual OUString SAL_CALL getNamespaceURI()
        throw (RuntimeException)
    {
        return CNode::getNamespaceURI();
    }
    virtual Reference< XNode > SAL_CALL getNextSibling()
        throw (RuntimeException)
    {
        return CNode::getNextSibling();
    }
    virtual NodeType SAL_CALL getNodeType()
        throw (RuntimeException)
    {
        return CNode::getNodeType();
    }
    virtual Reference< XDocument > SAL_CALL getOwnerDocument()
        throw (RuntimeException)
    {
        return CNode::getOwnerDocument();
    }
    virtual Reference< XNode > SAL_CALL getParentNode()
        throw (RuntimeException)
    {
        return CNode::getParentNode();
    }
    virtual OUString SAL_CALL getPrefix()
        throw (RuntimeException)
    {
        return CNode::getPrefix();
    }
    virtual Reference< XNode > SAL_CALL getPreviousSibling()
        throw (RuntimeException)
    {
        return CNode::getPreviousSibling();
    }
    virtual sal_Bool SAL_CALL hasAttributes()
        throw (RuntimeException)
    {
        return CNode::hasAttributes();
    }
    virtual sal_Bool SAL_CALL hasChildNodes()
        throw (RuntimeException)
    {
        return CNode::hasChildNodes();
    }
    virtual Reference< XNode > SAL_CALL insertBefore(
            const Reference< XNode >& newChild, const Reference< XNode >& refChild)
        throw (DOMException)
    {
        return CNode::insertBefore(newChild, refChild);
    }
    virtual sal_Bool SAL_CALL isSupported(const OUString& feature, const OUString& ver)
        throw (RuntimeException)
    {
        return CNode::isSupported(feature, ver);
    }
    virtual void SAL_CALL normalize()
        throw (RuntimeException)
    {
        CNode::normalize();
    }
    virtual Reference< XNode > SAL_CALL removeChild(const Reference< XNode >& oldChild)
        throw (DOMException)
    {
        return CNode::removeChild(oldChild);
    }
    virtual Reference< XNode > SAL_CALL replaceChild(
            const Reference< XNode >& newChild, const Reference< XNode >& oldChild)
        throw (DOMException)
    {
        return CNode::replaceChild(newChild, oldChild);
    }
    virtual void SAL_CALL setNodeValue(const OUString& nodeValue)
        throw (DOMException)
    {
        return CNode::setNodeValue(nodeValue);
    }
    virtual void SAL_CALL setPrefix(const OUString& prefix)
        throw (DOMException)
    {
        return CNode::setPrefix(prefix);
    }

    // XDocumentEvent
    virtual Reference< XEvent > createEvent(const OUString& eventType) throw (RuntimeException);

    };

}

#endif