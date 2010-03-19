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

#include "documenttype.hxx"
#include "entitiesmap.hxx"
#include "notationsmap.hxx"

#include <string.h>

namespace DOM
{

    CDocumentType::CDocumentType(const xmlDtdPtr aDtdPtr)
    {
        m_aNodeType = NodeType_DOCUMENT_TYPE_NODE;
        m_aDtdPtr = aDtdPtr;
        init_node((xmlNodePtr)aDtdPtr);
    }

    /**
    A NamedNodeMap containing the general entities, both external and 
    internal, declared in the DTD.
    */
    Reference< XNamedNodeMap > SAL_CALL CDocumentType::getEntities() throw (RuntimeException)
    {
        Reference< XNamedNodeMap > aMap;
        if (m_aDtdPtr != NULL)
        {
            aMap = Reference< XNamedNodeMap >(new CEntitiesMap(this));
        }
        return aMap;
    }

    /**
    The internal subset as a string, or null if there is none.
    */
    OUString SAL_CALL CDocumentType::getInternalSubset() throw (RuntimeException)
    {
        // XXX
        return OUString();
    }

    /**
    The name of DTD; i.e., the name immediately following the DOCTYPE 
    keyword.
    */
    OUString SAL_CALL CDocumentType::getName() throw (RuntimeException)
    {
        OUString aName;
        if (m_aDtdPtr != NULL)
        {
            aName = OUString((sal_Char*)m_aDtdPtr->name, strlen((char*)m_aDtdPtr->name), RTL_TEXTENCODING_UTF8);
        }
        return aName;
    }

    /**
    A NamedNodeMap containing the notations declared in the DTD.
    */
    Reference< XNamedNodeMap > SAL_CALL CDocumentType::getNotations() throw (RuntimeException)
    {
        Reference< XNamedNodeMap > aMap;
        if (m_aDtdPtr != NULL)
        {
            aMap.set(new CNotationsMap(this));
        }
        return aMap;
    }

    /**
    The public identifier of the external subset.
    */
    OUString SAL_CALL CDocumentType::getPublicId() throw (RuntimeException)
    {
        OUString aId;
        if (m_aDtdPtr != NULL)
        {
            aId = OUString((sal_Char*)m_aDtdPtr->name, strlen((char*)m_aDtdPtr->ExternalID), RTL_TEXTENCODING_UTF8);
        }
        return aId;
    }

    /**
    The system identifier of the external subset.
    */
    OUString SAL_CALL CDocumentType::getSystemId() throw (RuntimeException)
    {
        OUString aId;
        if (m_aDtdPtr != NULL)
        {
            aId = OUString((sal_Char*)m_aDtdPtr->name, strlen((char*)m_aDtdPtr->SystemID), RTL_TEXTENCODING_UTF8);
        }
        return aId;
    }
    OUString SAL_CALL CDocumentType::getNodeName()throw (RuntimeException)
    {
        return getName();
    }
    OUString SAL_CALL CDocumentType::getNodeValue() throw (RuntimeException)
    {
        return OUString();
    }
}
