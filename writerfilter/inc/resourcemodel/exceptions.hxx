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

#ifndef _DOCTOK_EXCEPTIONS_HXX
#define _DOCTOK_EXCEPTIONS_HXX

#include <string>
#include <WriterFilterDllApi.hxx>

namespace writerfilter {
using namespace ::std;

class WRITERFILTER_DLLPUBLIC Exception
{
    string mText;

public:
    Exception(string text) : mText(text) {}

    const string & getText() const { return mText; }
};

class WRITERFILTER_DLLPUBLIC ExceptionNotFound : public Exception
{
public:
    ExceptionNotFound(string text) : Exception(text) {}
};

class WRITERFILTER_DLLPUBLIC ExceptionOutOfBounds : public Exception
{
public:
    ExceptionOutOfBounds(string text) : Exception(text) {}
};
}

#endif // _DOCTOK_EXCEPTIONS_HXX
