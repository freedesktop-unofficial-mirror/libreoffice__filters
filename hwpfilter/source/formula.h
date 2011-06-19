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

#ifndef __FORMULA_H__
#define __FORMULA_H__

// DVO: remove DEBUG dependency
// #ifndef DEBUG
#include <com/sun/star/xml/sax/XDocumentHandler.hpp>
#include "attributes.hxx"
// DVO: remove DEBUG dependency
// #endif

class Node;

// DVO: remove DEBUG dependency
// #ifndef DEBUG
using namespace ::com::sun::star::xml::sax;
// #endif

class Formula
{
public:
    Formula(char *_eq, int _ishwpeq = 1)
        : pList(NULL)
    {
        eq = _eq;
        isHwpEQ = _ishwpeq;
        trim();
    }
    virtual ~Formula(){ }

    void setDocumentHandler(Reference < XDocumentHandler > xHandler )
    {
          m_rxDocumentHandler = xHandler;
    }
    void setAttributeListImpl( AttributeListImpl *p )
    {
        pList = p;
        rList = (XAttributeList *) pList;
    }
    int parse();
private:
     void trim();
     void makeMathML(Node *res);
     void makeLines(Node *res);
     void makeLine(Node *res);
     void makeExprList(Node *res);
     void makeExpr(Node *res);
     void makePrimary(Node *res);
     void makeIdentifier(Node *res);
     void makeSubSup(Node *res);
     void makeFraction(Node *res);
     void makeDecoration(Node *res);
     void makeFunction(Node *res);
     void makeRoot(Node *res);
     void makeArrow(Node *res);
     void makeAccent(Node *res);
     void makeParenth(Node *res);
     void makeFence(Node *res);
     void makeBracket(Node *res);
     void makeBlock(Node *res);
     void makeBegin(Node *res);
     void makeEnd(Node *res);

private:
     Reference< XDocumentHandler >  m_rxDocumentHandler;
     Reference< XAttributeList > rList;
     AttributeListImpl *pList;
     char *eq;
     int isHwpEQ;
};

#endif

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
