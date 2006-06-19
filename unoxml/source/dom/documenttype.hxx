/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: documenttype.hxx,v $
 *
 *  $Revision: 1.5 $
 *
 *  last change: $Author: hr $ $Date: 2006-06-20 00:45:20 $
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

#ifndef _DOCUMENTTYPE_HXX
#define _DOCUMENTTYPE_HXX

#include <sal/types.h>
#include <com/sun/star/uno/Reference.h>
#include <com/sun/star/uno/Exception.hpp>
#include <com/sun/star/xml/dom/XDocumentType.hpp>
#include <com/sun/star/xml/dom/XNodeList.hpp>
#include <com/sun/star/xml/dom/XNamedNodeMap.hpp>

#include "node.hxx"

#include <libxml/tree.h>

using namespace rtl;
using namespace com::sun::star::uno;
using namespace com::sun::star::lang;
using namespace com::sun::star::xml::dom;

namespace DOM
{
    class CDocumentType : public cppu::ImplInheritanceHelper1< CNode, XDocumentType >
    {
        friend class CNode;
    private:
        xmlDtdPtr m_aDtdPtr;

    protected:        
        CDocumentType(const xmlDtdPtr aDtdPtr);

    public:
        /**
        A NamedNodeMap containing the general entities, both external and 
        internal, declared in the DTD.
        */
        virtual Reference< XNamedNodeMap > SAL_CALL getEntities() throw (RuntimeException);

        /**
        The internal subset as a string, or null if there is none.
        */
        virtual OUString SAL_CALL getInternalSubset() throw (RuntimeException);

        /**
        The name of DTD; i.e., the name immediately following the DOCTYPE 
        keyword.
        */
        virtual OUString SAL_CALL getName() throw (RuntimeException);

        /**
        A NamedNodeMap containing the notations declared in the DTD.
        */
        virtual Reference< XNamedNodeMap > SAL_CALL getNotations() throw (RuntimeException);

        /**
        The public identifier of the external subset.
        */
        virtual OUString SAL_CALL getPublicId() throw (RuntimeException);

        /**
        The system identifier of the external subset.
        */
        virtual OUString SAL_CALL getSystemId() throw (RuntimeException);

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

    };
}
#endif
