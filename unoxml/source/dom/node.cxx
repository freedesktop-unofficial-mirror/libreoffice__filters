/*************************************************************************
 *
 *  $RCSfile: node.cxx,v $
 *
 *  $Revision: 1.4 $
 *
 *  last change: $Author: lo $ $Date: 2004-02-27 16:14:30 $
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
#include "node.hxx"
#include "element.hxx"
#include "text.hxx"
#include "cdatasection.hxx"
#include "entityreference.hxx"
#include "entity.hxx"
#include "processinginstruction.hxx"
#include "comment.hxx"
#include "document.hxx"
#include "documenttype.hxx"
#include "documentfragment.hxx"
#include "notation.hxx"
#include "childlist.hxx"
#include "attr.hxx"

#include "../events/eventdispatcher.hxx"
#include "../events/mutationevent.hxx"

namespace DOM
{
    nodemap_t CNode::theNodeMap;

    void CNode::remove(const xmlNodePtr aNode)
    {
        nodemap_t::iterator i = CNode::theNodeMap.find(aNode);
        if (i != CNode::theNodeMap.end())
        {
            CNode *pNode = i->second;
            CNode::theNodeMap.erase(i);
        }
    }

    
    CNode* CNode::get(const xmlNodePtr aNode, sal_Bool bCreate)
    {
        CNode* pNode = 0;        
        if (aNode == NULL)
            return 0;

        //check whether there is already an instance for this node
        nodemap_t::const_iterator i = CNode::theNodeMap.find(aNode);
        if (i != CNode::theNodeMap.end())
        {
            pNode = i->second;
        } else
        {
        
            // there is not yet an instance wrapping this node,
            // create it and store it in the map
            if (!bCreate) return NULL;

            switch (aNode->type)
            {
            case XML_ELEMENT_NODE:
                // m_aNodeType = NodeType::ELEMENT_NODE;                
                pNode = static_cast< CNode* >(new CElement(aNode));
                break;
            case XML_TEXT_NODE:
                // m_aNodeType = NodeType::TEXT_NODE;
                pNode = static_cast< CNode* >(new CText(aNode));
                break;
            case XML_CDATA_SECTION_NODE:
                // m_aNodeType = NodeType::CDATA_SECTION_NODE;
                pNode = static_cast< CNode* >(new CCDATASection(aNode));
                break;
            case XML_ENTITY_REF_NODE:
                // m_aNodeType = NodeType::ENTITY_REFERENCE_NODE;
                pNode = static_cast< CNode* >(new CEntityReference(aNode));
                break;
            case XML_ENTITY_NODE:
                // m_aNodeType = NodeType::ENTITY_NODE;
                pNode = static_cast< CNode* >(new CEntity((xmlEntityPtr)aNode));
                break;
            case XML_PI_NODE:
                // m_aNodeType = NodeType::PROCESSING_INSTRUCTION_NODE;
                pNode = static_cast< CNode* >(new CProcessingInstruction(aNode));
                break;
            case XML_COMMENT_NODE:
                // m_aNodeType = NodeType::COMMENT_NODE;
                pNode = static_cast< CNode* >(new CComment(aNode));
                break;
            case XML_DOCUMENT_NODE:
                // m_aNodeType = NodeType::DOCUMENT_NODE;
                pNode = static_cast< CNode* >(new CDocument((xmlDocPtr)aNode));
                break;
            case XML_DOCUMENT_TYPE_NODE:
            case XML_DTD_NODE:
                // m_aNodeType = NodeType::DOCUMENT_TYPE_NODE;
                pNode = static_cast< CNode* >(new CDocumentType((xmlDtdPtr)aNode));
                break;
            case XML_DOCUMENT_FRAG_NODE:
                // m_aNodeType = NodeType::DOCUMENT_FRAGMENT_NODE;
                pNode = static_cast< CNode* >(new CDocumentFragment(aNode));
                break;
            case XML_NOTATION_NODE:
                // m_aNodeType = NodeType::NOTATION_NODE;
                pNode = static_cast< CNode* >(new CNotation((xmlNotationPtr)aNode));
                break;
            case XML_ATTRIBUTE_NODE:
                // m_aNodeType = NodeType::NOTATION_NODE;
                pNode = static_cast< CNode* >(new CAttr((xmlAttrPtr)aNode));
                break;
            // unsopported node types
            case XML_HTML_DOCUMENT_NODE:
            case XML_ELEMENT_DECL:
            case XML_ATTRIBUTE_DECL:
            case XML_ENTITY_DECL:
            case XML_NAMESPACE_DECL:
            default:
                pNode = 0;
                break;
            }
        }
        if ( pNode != 0 )
        {
            if(CNode::theNodeMap.insert(nodemap_t::value_type(aNode, pNode)).second)
            {
                // insertion done, register node with document
                xmlDocPtr doc = aNode->doc;
                if( doc != NULL)
                {
                    CDocument* pDoc = static_cast< CDocument* >(CNode::get((xmlNodePtr)doc));
                    pDoc->addnode(aNode);
                } else
                {
                    // if insertion failed, delete the new instance and return null
                    delete pNode;
                    pNode = 0;
                }
            }
        }
        OSL_ENSURE(pNode, "no node produced during CNode::get!");
        return pNode;
    }

    CNode::CNode()
        : m_aNodePtr(0)
    {
    }

    void CNode::init_node(const xmlNodePtr aNode)
    {
        m_aNodePtr = aNode;

        // keep containing document alive
        // (if we are not that document ourselves)
        if (m_aNodePtr->type != XML_DOCUMENT_NODE)
            m_rDocument = getOwnerDocument();
    }

    CNode::~CNode()
    {
        //remove from list if this wrapper goes away
        if (m_aNodePtr != 0)
            CNode::remove(m_aNodePtr);
    }

    static void _nscleanup(const xmlNodePtr aNode, const xmlNodePtr aParent)
    {   
        xmlNodePtr cur = aNode;

        //handle attributes
        if (cur != NULL && cur->type == XML_ELEMENT_NODE)
        {
            xmlAttrPtr curAttr = cur->properties;
            while(curAttr != 0)
            {
                if (curAttr->ns != NULL)
                {
                    xmlNsPtr ns = xmlSearchNs(cur->doc, aParent, curAttr->ns->prefix);
                    if (ns != NULL)
                        curAttr->ns = ns;
                }
                curAttr = curAttr->next;
            }
        }

        while (cur != NULL)
        {
            _nscleanup(cur->children, cur);
            if (cur->ns != NULL)
            {
                xmlNsPtr ns = xmlSearchNs(cur->doc, aParent, cur->ns->prefix);
                if (ns != NULL && ns != cur->ns && strcmp((char*)ns->href, (char*)cur->ns->href)==0)
                {
                    cur->ns = ns;
                    xmlNsPtr curDef = cur->nsDef;
                    xmlNsPtr *refp = &(cur->nsDef); // insert point
                    while (curDef != NULL)
                    {
                        ns = xmlSearchNs(cur->doc, aParent, curDef->prefix);
                        if (ns != NULL && ns != curDef && strcmp((char*)ns->href, (char*)curDef->href)==0)
                        {
                            *refp = curDef->next;
                            xmlFreeNs(curDef);
                            curDef = *refp;
                        } else {
                            refp = &(curDef->next);                        
                            curDef = curDef->next;
                        }
                    }
                }
            }
            cur = cur->next;
        }
    }
     
    /**    
    Adds the node newChild to the end of the list of children of this node.
    */
    Reference< XNode > CNode::appendChild(const Reference< XNode >& newChild)
        throw (DOMException)
    {
        Reference< XNode> aNode;
        if (m_aNodePtr != NULL) {
            Reference< XUnoTunnel > tun(newChild, UNO_QUERY);
            xmlNodePtr cur = (xmlNodePtr)(tun->getSomething(Sequence <sal_Int8>()));

            // error checks:
            // from other document
            if (cur->doc != m_aNodePtr->doc) {
                DOMException e;
                e.Code = DOMExceptionType_WRONG_DOCUMENT_ERR;
                throw e;
            }
            // same node
            if (cur == m_aNodePtr) {
                DOMException e;
                e.Code = DOMExceptionType_HIERARCHY_REQUEST_ERR;
                throw e;                
            }
            // already has parant and is not attribute
            if (cur->parent != NULL && cur->type != XML_ATTRIBUTE_NODE) {
                DOMException e;
                e.Code = DOMExceptionType_HIERARCHY_REQUEST_ERR;
                throw e;                
            }

            // check whether this is an attribute node so we remove it's
            // carrier node
            xmlNodePtr res = NULL;
            if (cur->type == XML_ATTRIBUTE_NODE)
            {
                if (m_aNodePtr->type != XML_ELEMENT_NODE || cur->parent == NULL 
                    || strcmp((char*)cur->parent->name, "__private") != NULL)
                {
                    DOMException e;
                    e.Code = DOMExceptionType_HIERARCHY_REQUEST_ERR;
                    throw e;                
                }

                xmlNsPtr pAttrNs = cur->ns;
                xmlNsPtr pParentNs = xmlSearchNs(m_aNodePtr->doc, m_aNodePtr, pAttrNs->prefix);
                if (pParentNs == NULL || strcmp((char*)pParentNs->href, (char*)pAttrNs->href) != 0)                
                    pParentNs = xmlNewNs(m_aNodePtr, pAttrNs->href, pAttrNs->prefix);

                res = (xmlNodePtr)xmlNewNsProp(
                    m_aNodePtr, pParentNs, cur->name, cur->children->content);
                xmlFreeNode(cur->parent);
            }
            else
            {
                res = xmlAddChild(m_aNodePtr, cur);
            }
            
            // libxml can do optimizations, when appending nodes.
            // if res != cur, something was optimized and the newchild-wrapper 
            // should be updated
            if (cur != res)
                CNode::remove(cur);
          
            _nscleanup(res, m_aNodePtr);

            aNode = Reference< XNode>(CNode::get(res));
        }
        //XXX check for errors

        // dispatch DOMNodeInserted event, target is the new node
        // this node is the related node
        // does bubble
        if (aNode.is())
        {
            Reference< XDocumentEvent > docevent(getOwnerDocument(), UNO_QUERY); 
            Reference< XMutationEvent > event(docevent->createEvent(
                OUString::createFromAscii("DOMNodeInserted")), UNO_QUERY);
            event->initMutationEvent(OUString::createFromAscii("DOMNodeInserted")
                , sal_True, sal_False, Reference< XNode >(CNode::get(m_aNodePtr)),
                OUString(), OUString(), OUString(), (AttrChangeType)0 );
            dispatchEvent(Reference< XEvent >(event, UNO_QUERY));
        }
        return aNode;
    }

    /**
    Returns a duplicate of this node, i.e., serves as a generic copy 
    constructor for nodes.
    */
    Reference< XNode > CNode::cloneNode(sal_Bool bDeep)
        throw (RuntimeException)
    {
        Reference< XNode> aNode;
        if (m_aNodePtr != NULL)
        {
            aNode = Reference< XNode>(CNode::get(
                xmlCopyNode (m_aNodePtr, static_cast< int >(bDeep))
                ));
        }
        //XXX check for errors
        return aNode;
    }

    /**
    A NamedNodeMap containing the attributes of this node (if it is an Element) 
    or null otherwise.
    */
    Reference< XNamedNodeMap > CNode::getAttributes()
        throw (RuntimeException)
    {
        // return empty reference 
        // only element node may override this impl
        return Reference< XNamedNodeMap>();

        // get all children that are attributes
        /* --> CElement
        Reference< NamedNodeMap > aNodeMap(new AttributeNamedNodeMap(m_aNodePtr), UNO_QUERY);
        return aNodeMap;
        */
    }

    /**
    A NodeList that contains all children of this node.
    */
    Reference< XNodeList > CNode::getChildNodes()
        throw (RuntimeException)
    {
        Reference< XNodeList > aNodeList;
        if (m_aNodePtr != NULL)
        {
            aNodeList = Reference< XNodeList >(new CChildList(CNode::get(m_aNodePtr)));
        }
        // XXX check for errors?
        return aNodeList;
    }

    /**
    The first child of this node.
    */
    Reference< XNode > CNode::getFirstChild()
        throw (RuntimeException)
    {
        Reference< XNode > aNode;
        if (m_aNodePtr != NULL) {
            aNode = Reference< XNode >(CNode::get(m_aNodePtr->children));
        }
        return aNode;
    }

    /**
    The last child of this node.
    */
    Reference< XNode > SAL_CALL CNode::getLastChild()
        throw (RuntimeException)
    {
        Reference< XNode > aNode;
        if (m_aNodePtr != NULL) {
            aNode = Reference< XNode >(CNode::get(xmlGetLastChild(m_aNodePtr)));
        }
        return aNode;
    }

    /**
    Returns the local part of the qualified name of this node.    
    */
    OUString SAL_CALL CNode::getLocalName()
        throw (RuntimeException)
    {
        OUString aName;
        /*
         --> Element / Attribute
        if(m_aNodePtr != NULL && (m_aNodeType == NodeType::ATTRIBUTE_NODE
            || m_aNodeType == NodeType::ELEMENT_NODE))
        {
            aName = OUString(m_aNodePtr->name, RTL_TEXTENCODING_UTF8);
        }
        //XXX error checking
        */
        return aName;
    }


    /**
    The namespace URI of this node, or null if it is unspecified.
    */
    OUString SAL_CALL CNode::getNamespaceURI()
        throw (RuntimeException)
    {
        OUString aURI;
        if (m_aNodePtr != NULL && m_aNodePtr->ns != NULL)
        {
            const xmlChar* xHref = m_aNodePtr->ns->href; 
            aURI = OUString((sal_Char*)xHref, strlen((char*)xHref), RTL_TEXTENCODING_UTF8);
        }
        return aURI;            
    }

    /**
    The node immediately following this node.
    */
    Reference< XNode > SAL_CALL CNode::getNextSibling()
        throw (RuntimeException)
    {
        Reference< XNode > aNode;
        if(m_aNodePtr != NULL) 
        {
            aNode = Reference< XNode >(CNode::get(m_aNodePtr->next));
        }
        return aNode;
    }

    /**
    The name of this node, depending on its type; see the table above.
    */
    OUString SAL_CALL CNode::getNodeName()
        throw (RuntimeException)
    {
        /*
        Interface  	     nodeName  	            nodeValue  	                    attributes
        --------------------------------------------------------------------------------------
        Attr 	         name of attribute 	    value of attribute 	            null
        CDATASection 	 "#cdata-section" 	    content of the CDATA Section 	null
        Comment 	     "#comment" 	        content of the comment 	        null
        Document 	     "#document" 	        null 	                        null
        DocumentFragment "#document-fragment" 	null 	                        null
        DocumentType 	 document type name 	null 	                        null
        Element 	     tag name 	            null 	                        NamedNodeMap
        Entity 	         entity name 	        null 	                        null
        EntityReference  name of entity         null 	                        null
                         referenced 	        
        Notation 	     notation name 	        null 	                        null
        Processing\   	 target                 entire content excluding        null 
        Instruction 	                        the target 	                                                                        
        Text 	         "#text" 	            content of the text node     	null
        */
        OUString aName;
        return aName;
    }

    /**
    A code representing the type of the underlying object, as defined above.
    */
    NodeType SAL_CALL CNode::getNodeType()
        throw (RuntimeException)
    {
        return m_aNodeType;            
    }

    /**
    The value of this node, depending on its type; see the table above.
    */
    OUString SAL_CALL CNode::getNodeValue()
        throw (RuntimeException)
    {
        OUString aValue;
        return aValue;
    }

    /**
    The Document object associated with this node.
    */
    Reference< XDocument > SAL_CALL CNode::getOwnerDocument()
        throw (RuntimeException)
    {
        Reference<XDocument> aDoc;
        if (m_aNodePtr != NULL)
        {
            aDoc = Reference< XDocument >(static_cast< CDocument* >(
                CNode::get((xmlNodePtr)m_aNodePtr->doc)));
        }
        return aDoc;

    }

    /**
    The parent of this node.
    */
    Reference< XNode > SAL_CALL CNode::getParentNode()
        throw (RuntimeException)
    {
        Reference<XNode> aNode;
        if (m_aNodePtr != NULL)
        {
            aNode = Reference< XNode >(CNode::get(m_aNodePtr->parent));
        }
        return aNode;
    }

    /**
    The namespace prefix of this node, or null if it is unspecified.
    */
    OUString SAL_CALL CNode::getPrefix()
        throw (RuntimeException)
    {
        OUString aPrefix;
        if (m_aNodePtr != NULL && m_aNodePtr->ns != NULL)
        {
            const xmlChar* xPrefix = m_aNodePtr->ns->prefix;
            aPrefix = OUString((sal_Char*)xPrefix, strlen((char*)xPrefix), RTL_TEXTENCODING_UTF8);
        }
        return aPrefix;            

    }

    /**
    The node immediately preceding this node.
    */
    Reference< XNode > SAL_CALL CNode::getPreviousSibling()
        throw (RuntimeException)
    {
        Reference< XNode > aNode;
        if (m_aNodePtr != NULL)
        {
            aNode = Reference< XNode >(CNode::get(m_aNodePtr->prev));
        }
        return aNode;
    }

    /**
    Returns whether this node (if it is an element) has any attributes.
    */
    sal_Bool SAL_CALL CNode::hasAttributes()
        throw (RuntimeException)
    {
        return (m_aNodePtr != NULL && m_aNodePtr->properties != NULL);
    }

    /**
    Returns whether this node has any children.
    */
    sal_Bool SAL_CALL CNode::hasChildNodes()
        throw (RuntimeException)
    {
        return (m_aNodePtr != NULL && m_aNodePtr->children != NULL);
    }

    /**
    Inserts the node newChild before the existing child node refChild.
    */
    Reference< XNode > SAL_CALL CNode::insertBefore(
            const Reference< XNode >& newChild, const Reference< XNode >& refChild)
        throw (DOMException)
    {
        
        if (newChild->getOwnerDocument() != getOwnerDocument()) {
            DOMException e;
            e.Code = DOMExceptionType_WRONG_DOCUMENT_ERR;
            throw e;
        }
        if (refChild->getParentNode() != Reference< XNode >(this)) {
            DOMException e;
            e.Code = DOMExceptionType_HIERARCHY_REQUEST_ERR;
            throw e;
        }

        Reference< XUnoTunnel > tref(refChild, UNO_QUERY);
        Reference< XUnoTunnel > tnew(newChild, UNO_QUERY);
        xmlNodePtr pRefChild = (xmlNodePtr)tref->getSomething(Sequence< sal_Int8>());
        xmlNodePtr pNewChild = (xmlNodePtr)tnew->getSomething(Sequence< sal_Int8>());
        xmlNodePtr cur = m_aNodePtr->children;

        //search cild before which to insert
        while (cur != NULL)
        {
            if (cur == pRefChild) {
                // insert before
                pNewChild->next = cur;
                pNewChild->prev = cur->prev;
                cur->prev = pNewChild;
                if( pNewChild->prev != NULL)
                    pNewChild->prev->next = pNewChild;
            }
            cur = cur->next;
        }
        return refChild;
    }

    /**
    Tests whether the DOM implementation implements a specific feature and
    that feature is supported by this node.
    */
    sal_Bool SAL_CALL CNode::isSupported(const OUString& feature, const OUString& ver)
        throw (RuntimeException)
    {
        // XXX
        return sal_False;
    }

    /**
    Puts all Text nodes in the full depth of the sub-tree underneath this 
    Node, including attribute nodes, into a "normal" form where only structure
    (e.g., elements, comments, processing instructions, CDATA sections, and 
    entity references) separates Text nodes, i.e., there are neither adjacent
    Text nodes nor empty Text nodes.
    */
    void SAL_CALL CNode::normalize()
        throw (RuntimeException)
    {
        //XXX combine adjacent text nodes and remove empty ones
    }

    /**
    Removes the child node indicated by oldChild from the list of children,
    and returns it.
    */
    Reference< XNode > SAL_CALL CNode::removeChild(const Reference< XNode >& oldChild)
        throw (DOMException)
    {

        if (oldChild->getParentNode() != Reference< XNode >(this)) {
            DOMException e;
            e.Code = DOMExceptionType_HIERARCHY_REQUEST_ERR;
            throw e;
        }

        Reference< XUnoTunnel > told(oldChild, UNO_QUERY);
        xmlNodePtr old = (xmlNodePtr)told->getSomething(Sequence< sal_Int8>());
        xmlNodePtr cur = m_aNodePtr->children;
        //find old node in child list
        while (cur != NULL)
        {
            if(cur == old)
            {
                // unlink node from list
                if (cur->prev != NULL)
                    cur->prev->next = cur->next;
                if (cur->next != NULL)
                    cur->next->prev = cur->prev;
                cur->prev = NULL;
                cur->next = NULL;
            }
            cur = cur->next;
        }

        /*DOMNodeRemoved
         * Fired when a node is being removed from its parent node. 
         * This event is dispatched before the node is removed from the tree. 
         * The target of this event is the node being removed.
         *   Bubbles: Yes
         *   Cancelable: No
         *   Context Info: relatedNode holds the parent node
         */
        if (oldChild.is())
        {
            Reference< XDocumentEvent > docevent(getOwnerDocument(), UNO_QUERY); 
            Reference< XMutationEvent > event(docevent->createEvent(
                OUString::createFromAscii("DOMNodeRemoved")), UNO_QUERY);
            event->initMutationEvent(OUString::createFromAscii("DOMNodeRemoved"), sal_True, 
                sal_False, Reference< XNode >(CNode::get(m_aNodePtr)),
                OUString(), OUString(), OUString(), (AttrChangeType)0 );
            dispatchEvent(Reference< XEvent >(event, UNO_QUERY));
        }
        return oldChild;
    }    

    /**
    Replaces the child node oldChild with newChild in the list of children,
    and returns the oldChild node.
    */
    Reference< XNode > SAL_CALL CNode::replaceChild(
            const Reference< XNode >& newChild, const Reference< XNode >& oldChild)
        throw (DOMException)
    {
        // XXX check node types

        if (oldChild->getParentNode() != Reference< XNode >(this)) {
            DOMException e;
            e.Code = DOMExceptionType_HIERARCHY_REQUEST_ERR;
            throw e;
        }

        Reference< XNode > aNode = removeChild(oldChild);
        appendChild(newChild);
/*
        Reference< XUnoTunnel > tOld(oldChild, UNO_QUERY);
        xmlNodePtr pOld = (xmlNodePtr)tOld->getSomething(Sequence< sal_Int8>());
        Reference< XUnoTunnel > tNew(newChild, UNO_QUERY);
        xmlNodePtr pNew = (xmlNodePtr)tNew->getSomething(Sequence< sal_Int8>());
        xmlNodePtr cur = m_aNodePtr->children;
        //find old node in child list
        while (cur != NULL)
        {
            if(cur == pOld)
            {
                // exchange nodes
                pNew->prev = pOld->prev;
                if (pNew->prev != NULL)
                    pNew->prev->next = pNew;
                pNew->next = pOld->next;
                if (pNew->next != NULL)
                    pNew->next->prev = pNew;
                pOld->next = NULL;
                pOld->prev = NULL;
            }
            cur = cur->next;
        }
*/
        // dispatch DOMSubtreeModified
        // target is _this_ node
        Reference< XDocumentEvent > docevent(getOwnerDocument(), UNO_QUERY); 
        Reference< XMutationEvent > event(docevent->createEvent(
            OUString::createFromAscii("DOMSubtreeModified")), UNO_QUERY);
        event->initMutationEvent(OUString::createFromAscii("DOMSubtreeModified"), sal_True, 
            sal_False, Reference< XNode >(),
            OUString(), OUString(), OUString(), (AttrChangeType)0 );
        dispatchEvent(Reference< XEvent >(event, UNO_QUERY));

        return aNode;
    }

    /**
    The value of this node, depending on its type; see the table above.
    */
    void SAL_CALL CNode::setNodeValue(const OUString& nodeValue)
        throw (DOMException)
    {
        // use specific node implememntation
        // if we end up down here, something went wrong
        DOMException e;
        e.Code = DOMExceptionType_NO_MODIFICATION_ALLOWED_ERR;
        throw e;
    }

    /**
    The namespace prefix of this node, or null if it is unspecified.
    */
    void SAL_CALL CNode::setPrefix(const OUString& prefix)
        throw (DOMException)
    {
        OString o1 = OUStringToOString(prefix, RTL_TEXTENCODING_UTF8);
        xmlChar *pBuf = (xmlChar*)o1.getStr();
        // XXX copy buf?
        // XXX free old string? (leak?)
        if (m_aNodePtr != NULL && m_aNodePtr->ns != NULL)
        {
            m_aNodePtr->ns->prefix = pBuf;
        }
        
    }

    sal_Int64 SAL_CALL CNode::getSomething(const Sequence< sal_Int8 >& id) throw (RuntimeException)
    {
        // XXX check ID
        return (sal_Int64)m_aNodePtr;
    }


        // --- XEventTarget
    void SAL_CALL CNode::addEventListener(const OUString& eventType, 
        const Reference< XEventListener >& listener, 
        sal_Bool useCapture)
        throw (RuntimeException)
    {
        events::CEventDispatcher::addListener(m_aNodePtr, eventType, listener, useCapture);
    }

    void SAL_CALL CNode::removeEventListener(const OUString& eventType, 
        const Reference< XEventListener >& listener, 
        sal_Bool useCapture)
        throw (RuntimeException)
    {
        events::CEventDispatcher::removeListener(m_aNodePtr, eventType, listener, useCapture);
    }

    sal_Bool SAL_CALL CNode::dispatchEvent(const Reference< XEvent >& evt) 
        throw(EventException)
    {
        events::CEventDispatcher::dispatchEvent(m_aNodePtr, evt);
        return sal_True;
    }
}
    
