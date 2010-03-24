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

#include "notation.hxx"
#include <string.h>

namespace DOM
{
    CNotation::CNotation(const xmlNotationPtr aNotationPtr)
    {
        m_aNodeType = NodeType_NOTATION_NODE;
        m_aNotationPtr = aNotationPtr;
        init_node((xmlNodePtr)aNotationPtr);
    }

    OUString SAL_CALL CNotation::getPublicId() throw (RuntimeException)
    {
        // XXX
        return OUString();
    }

    /**
    The system identifier of this notation.
    */
    OUString SAL_CALL CNotation::getSystemId() throw (RuntimeException)
    {
        // XXX
        return OUString();
    }


    OUString SAL_CALL CNotation::getNodeName()throw (RuntimeException)
    {
       OUString aName;
        if (m_aNodePtr != NULL)
        {
            const xmlChar* xName = m_aNodePtr->name;
            aName = OUString((sal_Char*)xName, strlen((char*)xName), RTL_TEXTENCODING_UTF8);
        }
        return aName;
    }
    OUString SAL_CALL CNotation::getNodeValue() throw (RuntimeException)
    {
        return OUString();
    }
}
