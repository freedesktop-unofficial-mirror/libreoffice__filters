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

#include "attr.hxx"
#include "element.hxx"
#include <com/sun/star/xml/dom/DOMException.hdl>
#include <string.h>

namespace DOM
{
    CAttr::CAttr(const xmlAttrPtr pAttr)
    {
        m_aAttrPtr = pAttr;
        m_aNodeType = NodeType_ATTRIBUTE_NODE;
        init_node((xmlNodePtr)pAttr);
    }

    OUString SAL_CALL CAttr::getNodeName()
        throw (RuntimeException)
    {
        return getName();
    }
    OUString SAL_CALL CAttr::getNodeValue()
        throw (RuntimeException)
    {
        return getValue();
    }
    OUString SAL_CALL CAttr::getLocalName()
        throw (RuntimeException)
    {
        return getName();
    }


    /**
    Returns the name of this attribute.
    */
    OUString SAL_CALL CAttr::getName() throw (RuntimeException)
    {
        OUString aName;
        if (m_aAttrPtr != NULL)
        {
            aName = OUString((char*)m_aAttrPtr->name, strlen((char*)m_aAttrPtr->name), RTL_TEXTENCODING_UTF8);
        }
        return aName;
    }

    /**
    The Element node this attribute is attached to or null if this 
    attribute is not in use.
    */
    Reference< XElement > SAL_CALL CAttr::getOwnerElement()
        throw (RuntimeException)
    {
        Reference< XElement > aElement;
        if (m_aAttrPtr != NULL && m_aAttrPtr->parent != NULL)
        {
            aElement = Reference< XElement >(static_cast< CElement* >(CNode::get(m_aAttrPtr->parent)));
        }
        return aElement;
    }

    /**
    If this attribute was explicitly given a value in the original 
    document, this is true; otherwise, it is false.
    */
    sal_Bool SAL_CALL CAttr::getSpecified()
        throw (RuntimeException)
    {
        // XXX what is this supposed do exactly?
        return sal_False;
    }

    /**
    On retrieval, the value of the attribute is returned as a string.
    */
    OUString SAL_CALL CAttr::getValue()
        throw (RuntimeException)
    {
        OUString aName;
        if (m_aAttrPtr != NULL && m_aAttrPtr->children != NULL)
        {
            aName = OUString((char*)m_aAttrPtr->children->content, strlen((char*)m_aAttrPtr->children->content),
                RTL_TEXTENCODING_UTF8);
        }
        return aName;
    }

    /**
    Sets the value of the attribute from a string.
    */
    void SAL_CALL CAttr::setValue(const OUString& value)
        throw (RuntimeException, DOMException)
    {
        // remember old value (for mutation event)
        OUString sOldValue = getValue();

        OString o1 = OUStringToOString(value, RTL_TEXTENCODING_UTF8);
        xmlChar* xValue = (xmlChar*)o1.getStr();
        // xmlChar* xName = OUStringToOString(m_aAttrPtr->name, RTL_TEXTENCODING_UTF8).getStr();
        // this does not work if the attribute was created anew
        // xmlNodePtr pNode = m_aAttrPtr->parent;
        // xmlSetProp(pNode, m_aAttrPtr->name, xValue);
        xmlChar *buffer = xmlEncodeEntitiesReentrant(m_aAttrPtr->doc, xValue);
        m_aAttrPtr->children = xmlStringGetNodeList(m_aAttrPtr->doc, buffer);
        xmlNodePtr tmp = m_aAttrPtr->children;
        while (tmp != NULL) {
            tmp->parent = (xmlNodePtr) m_aNodePtr;
            tmp->doc = m_aAttrPtr->doc;
            if (tmp->next == NULL)
                m_aNodePtr->last = tmp;
            tmp = tmp->next;
        }

        // dispatch DOM events to signal change in attribute value
        // dispatch DomAttrModified + DOMSubtreeModified
        OUString sEventName( RTL_CONSTASCII_USTRINGPARAM("DOMAttrModified") );
        Reference< XDocumentEvent > docevent(getOwnerDocument(), UNO_QUERY);
        Reference< XMutationEvent > event(docevent->createEvent(sEventName),UNO_QUERY);
        event->initMutationEvent(
                sEventName, sal_True, sal_False,
                Reference<XNode>( static_cast<XAttr*>( this ) ),
                sOldValue, value, getName(), AttrChangeType_MODIFICATION );
        dispatchEvent(Reference< XEvent >(event, UNO_QUERY));
        dispatchSubtreeModified();
        xmlFree(buffer);
    }

}
