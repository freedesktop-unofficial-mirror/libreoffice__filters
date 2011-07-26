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

#ifndef INCLUDED_WW8_STTBF_HXX
#define INCLUDED_WW8_STTBF_HXX

#include <WW8StructBase.hxx>
#include <WW8ResourceModelImpl.hxx>

#include <boost/shared_ptr.hpp>
#include <vector>

namespace writerfilter {
namespace doctok
{

using namespace ::std;

/**
   A string table in file.

   The string table contains strings that each can have extra data.
 */
class WW8Sttbf : public WW8StructBase
{
    /// true if strings contain two-byte characters
    bool mbComplex;

    /// the number of entries
    sal_uInt32 mnCount;

    /// the size of the extra data (per string)
    sal_uInt32 mnExtraDataCount;

    /// offsets for the strings
    vector<sal_uInt32> mEntryOffsets;

    /// offsets for the extra data
    vector<sal_uInt32> mExtraOffsets;

    /**
       Return offset of an entry.

       @param nPos    the index of the entry
    */
    sal_uInt32 getEntryOffset(sal_uInt32 nPos) const;

public:
    typedef boost::shared_ptr<WW8Sttbf> Pointer_t;

    WW8Sttbf(WW8Stream & rStream, sal_uInt32 nOffset, sal_uInt32 nCount);

    /**
       Return the number of entries.
    */
    sal_uInt32 getEntryCount() const;

    /**
       Return the string of an entry.

       @param nPos     the index of the entry
     */
    rtl::OUString getEntry(sal_uInt32 nPos) const;
};

class WW8SttbTableResource : public ::writerfilter::Reference<Table>
{
    WW8Sttbf::Pointer_t mpSttbf;
    
public:
    WW8SttbTableResource(WW8Sttbf::Pointer_t pSttbf);
    virtual ~WW8SttbTableResource();
    
    void resolve(Table & rTable);
    
    string getType() const;
};

class WW8StringProperty : public ::writerfilter::Reference<Properties>
{
    sal_uInt32 mnId;
    WW8StringValue::Pointer_t mpValue;
    
public:
    WW8StringProperty(sal_uInt32 nId, WW8StringValue::Pointer_t pValue);
    virtual ~WW8StringProperty();
    
    void resolve(Properties & rProperties);
    
    string getType() const;
};

}}
#endif // INCLUDED_WW8_STTBF

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
