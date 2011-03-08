/* -*- Mode: C++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */
/*************************************************************************
 *
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER.
 * 
 * Copyright 2000, 2010 Oracle and/or its affiliates.
 *
 * OpenOffice.org - a multi-platform office productivity suite
 *
<<<<<<< HEAD:binfilter/bf_sfx2/source/inc/eacopier.hxx
=======
 * $RCSfile: PropertyMap.hxx,v $
 * $Revision: 1.18 $
 *
>>>>>>> stage/ooo/dev300_m98_fixed:writerfilter/source/dmapper/PropertyMapHelper.hxx
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

#ifdef DEBUG
#include "PropertyMap.hxx"
#include <com/sun/star/beans/PropertyValues.hpp>

namespace writerfilter
{
namespace dmapper
{

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
=======
XMLTag::Pointer_t lcl_TableColumnSeparatorsToTag(const uno::Any & rTableColumnSeparators);
XMLTag::Pointer_t lcl_PropertyValuesToTag(beans::PropertyValues & rValues);
    
typedef uno::Sequence<beans::PropertyValues> PropertyValueSeq_t;    
XMLTag::Pointer_t lcl_PropertyValueSeqToTag(PropertyValueSeq_t & rPropValSeq);
    
typedef uno::Sequence<PropertyValueSeq_t> PropertyValueSeqSeq_t;
XMLTag::Pointer_t lcl_PropertyValueSeqSeqToTag(PropertyValueSeqSeq_t & rPropValSeqSeq);
}
}
#endif // DEBUG

