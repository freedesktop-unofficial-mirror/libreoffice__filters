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

#ifndef INCLUDED_TAG_LOGGER_HXX
#define INCLUDED_TAG_LOGGER_HXX

#if OSL_DEBUG_LEVEL > 1

#include <rtl/ustring.hxx>
#include <com/sun/star/beans/XPropertySet.hpp>
#include <WriterFilterDllApi.hxx>
#include <resourcemodel/WW8ResourceModel.hxx>
#include <string>
#include <hash_map>
#include <boost/shared_ptr.hpp>
#include <libxml/xmlwriter.h>

namespace writerfilter
{
    class IdToString
    {
    public:
        typedef boost::shared_ptr<IdToString> Pointer_t;
        virtual std::string toString(const Id & id) const = 0;
    };
    
    class WRITERFILTER_DLLPUBLIC TagLogger
    {
    public:
        typedef TagLogger* Pointer_t;
        
    private:
        xmlTextWriterPtr pWriter;
        const char* pName;

        TagLogger(const char* name);
        
    public:
        ~TagLogger();
        
        static Pointer_t getInstance(const char * name);
        
        void setFileName(const std::string & filename);

        void startDocument();
        void element(const std::string & name);
        void startElement(const std::string & name);
        void attribute(const std::string & name, const std::string & value);
        void attribute(const std::string & name, const ::rtl::OUString & value);
        void attribute(const std::string & name, sal_uInt32 value);
        void attribute(const std::string & name, const uno::Any aAny);
        void chars(const std::string & chars);
        void chars(const ::rtl::OUString & chars);
        void endElement();
        void endDocument();

        void unoPropertySet(uno::Reference<beans::XPropertySet> rPropSet);
        void propertySet(writerfilter::Reference<Properties>::Pointer_t props,
                IdToString::Pointer_t pIdToString);
    };
}

#endif // DEBUG
#endif // INCLUDED_TAG_LOGGER_HXX

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
