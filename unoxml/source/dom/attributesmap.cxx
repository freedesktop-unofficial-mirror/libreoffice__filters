/*************************************************************************
 *
 *  $RCSfile: attributesmap.cxx,v $
 *
 *  $Revision: 1.2 $
 *
 *  last change: $Author: obo $ $Date: 2004-11-16 12:18:09 $
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

#include "attributesmap.hxx"

namespace DOM
{
    CAttributesMap::CAttributesMap(const CElement* aElement)
        : m_pElement(aElement)
    {
    }

    /**
    The number of nodes in this map.
    */
    sal_Int32 SAL_CALL CAttributesMap::getLength() throw (RuntimeException)
    {
        sal_Int32 count = 0;
        xmlNodePtr pNode = m_pElement->m_aNodePtr;
        if (pNode != NULL)
        {
            xmlAttrPtr cur = pNode->properties;
            while (cur != NULL)
            {
                count++;
                cur = cur->next;
            }
        }
        return count;

    }

    /**
    Retrieves a node specified by local name     	
    */
    Reference< XNode > SAL_CALL CAttributesMap::getNamedItem(const OUString& name) throw (RuntimeException)
    {
        Reference< XNode > aNode;
        xmlNodePtr pNode = m_pElement->m_aNodePtr;
        if (pNode != NULL)
        {
            OString o1 = OUStringToOString(name, RTL_TEXTENCODING_UTF8);
            xmlChar* xName = (xmlChar*)o1.getStr();
            xmlAttrPtr cur = pNode->properties;
            while (cur != NULL)
            {
                if( strcmp((char*)xName, (char*)cur->name) == 0)
                {
                    aNode = Reference< XNode >(static_cast<CNode*>(CNode::get((xmlNodePtr)cur)));                    
                    break;
                }
                cur = cur->next;
            }
        }
        return aNode;
    }

    /**
    Retrieves a node specified by local name and namespace URI.
    */
    Reference< XNode > SAL_CALL CAttributesMap::getNamedItemNS(const OUString& namespaceURI,const OUString& localName) throw (RuntimeException)
    {
        Reference< XNode > aNode;
        xmlNodePtr pNode = m_pElement->m_aNodePtr;
        if (pNode != NULL)
        {
            OString o1 = OUStringToOString(localName, RTL_TEXTENCODING_UTF8);
            xmlChar* xName = (xmlChar*)o1.getStr();
            OString o2 = OUStringToOString(namespaceURI, RTL_TEXTENCODING_UTF8);
            xmlChar* xNs = (xmlChar*)o1.getStr();
            xmlNsPtr pNs = xmlSearchNs(pNode->doc, pNode, xNs);
            xmlAttrPtr cur = pNode->properties;
            while (cur != NULL && pNs != NULL)
            {
                if( strcmp((char*)xName, (char*)cur->name) == 0 &&
                    cur->ns == pNs)
                {
                    aNode = Reference< XNode >(static_cast< CNode* >(CNode::get((xmlNodePtr)cur)));
                    break;
                }
                cur = cur->next;
            }
        }
        return aNode;
    }

    /**
    Returns the indexth item in the map.
    */
    Reference< XNode > SAL_CALL CAttributesMap::item(sal_Int32 index) throw (RuntimeException)
    {
        Reference< XNode > aNode;
        xmlNodePtr pNode = m_pElement->m_aNodePtr;
        if (pNode != NULL)
        {
            xmlAttrPtr cur = pNode->properties;
            sal_Int32 count = 0;
            while (cur != NULL)
            {
                if (count == index)
                {
                    aNode = Reference< XNode >(static_cast< CNode* >(CNode::get((xmlNodePtr)cur)));
                    break;
                }
                count++;
                cur = cur->next;
            }
        }
        return aNode;

    }

    /**
    Removes a node specified by name.
    */
    Reference< XNode > SAL_CALL CAttributesMap::removeNamedItem(const OUString& name) throw (RuntimeException)
    {
        Reference< XNode > aNode;
        xmlNodePtr pNode = m_pElement->m_aNodePtr;
        if (pNode != NULL)
        {
            OString o1 = OUStringToOString(name, RTL_TEXTENCODING_UTF8);
            xmlChar* xName = (xmlChar*)o1.getStr();
            xmlAttrPtr cur = pNode->properties;
            while (cur != NULL)
            {
                if( strcmp((char*)xName, (char*)cur->name) == 0)
                {
                    aNode = Reference< XNode >(static_cast< CNode* >(CNode::get((xmlNodePtr)cur)));
                    xmlUnlinkNode((xmlNodePtr)cur);
                    break;
                }
                cur = cur->next;
            }
        }
        return aNode;
    }

    /**
    // Removes a node specified by local name and namespace URI.
    */
    Reference< XNode > SAL_CALL CAttributesMap::removeNamedItemNS(const OUString& namespaceURI, const OUString& localName) throw (RuntimeException)
    {
        Reference< XNode > aNode;
        xmlNodePtr pNode = m_pElement->m_aNodePtr;
        if (pNode != NULL)
        {
            OString o1 = OUStringToOString(localName, RTL_TEXTENCODING_UTF8);
            xmlChar* xName = (xmlChar*)o1.getStr();
            OString o2 = OUStringToOString(namespaceURI, RTL_TEXTENCODING_UTF8);
            xmlChar* xNs = (xmlChar*)o1.getStr();
            xmlNsPtr pNs = xmlSearchNs(pNode->doc, pNode, xNs);
            xmlAttrPtr cur = pNode->properties;
            while (cur != NULL && pNs != NULL)
            {
                if( strcmp((char*)xName, (char*)cur->name) == 0 &&
                    cur->ns == pNs)
                {
                    aNode = Reference< XNode >(static_cast< CNode* >(CNode::get((xmlNodePtr)cur)));
                    xmlUnlinkNode((xmlNodePtr)cur);
                    break;
                }
                cur = cur->next;
            }
        }
        return aNode;
    }

    /**
    // Adds a node using its nodeName attribute.
    */
    Reference< XNode > SAL_CALL CAttributesMap::setNamedItem(const Reference< XNode >& arg) throw (RuntimeException)
    {
        return Reference< XNode >();
    }

    /**
    Adds a node using its namespaceURI and localName.
    */
    Reference< XNode > SAL_CALL CAttributesMap::setNamedItemNS(const Reference< XNode >& arg) throw (RuntimeException)
    {
        return Reference< XNode >();
    }
}