/* -*- Mode: C++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */
/*************************************************************************
 *
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER.
 * 
 * Copyright 2008 by Sun Microsystems, Inc.
 *
 * OpenOffice.org - a multi-platform office productivity suite
 *
 * $RCSfile: PropertyMap.hxx,v $
 * $Revision: 1.18 $
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

#if OSL_DEBUG_LEVEL > 1
#include "PropertyMap.hxx"
#include <com/sun/star/beans/PropertyValues.hpp>

namespace writerfilter
{
namespace dmapper
{

void lcl_DumpTableColumnSeparators(const TagLogger::Pointer_t pLogger,
        const uno::Any & rTableColumnSeparators);
void lcl_DumpPropertyValues(const TagLogger::Pointer_t pLogger,
        beans::PropertyValues & rValues);
    
typedef uno::Sequence<beans::PropertyValues> PropertyValueSeq_t;    
void lcl_DumpPropertyValueSeq(const TagLogger::Pointer_t pLogger,
     PropertyValueSeq_t & rPropValSeq);
    
typedef uno::Sequence<PropertyValueSeq_t> PropertyValueSeqSeq_t;
void lcl_DumpPropertyValueSeqSeq(const TagLogger::Pointer_t pLogger,
        PropertyValueSeqSeq_t & rPropValSeqSeq);
}
}
#endif // DEBUG

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
