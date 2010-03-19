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


#ifdef _MSC_VER
#pragma hdrstop
#endif

#ifndef _UNODEFAULTS_HXX
#include <unodefaults.hxx>
#endif

#ifndef _SVDMODEL_HXX
#include <bf_svx/svdmodel.hxx>
#endif
#include <bf_svx/unoprov.hxx>

#ifndef _HORIORNT_HXX
#include <horiornt.hxx>
#endif

#include <doc.hxx>
namespace binfilter {

/* -----------------------------13.03.01 14:16--------------------------------

 ---------------------------------------------------------------------------*/
SwSvxUnoDrawPool::SwSvxUnoDrawPool( SwDoc* pDoc ) throw() :
    SvxUnoDrawPool(pDoc->GetDrawModel(), SVXUNO_SERVICEID_COM_SUN_STAR_DRAWING_DEFAULTS_WRITER),
    m_pDoc(pDoc)
{
}
/* -----------------------------13.03.01 14:16--------------------------------

 ---------------------------------------------------------------------------*/
SwSvxUnoDrawPool::~SwSvxUnoDrawPool() throw()
{
}
/* -----------------------------13.03.01 14:16--------------------------------

 ---------------------------------------------------------------------------*/
SfxItemPool* SwSvxUnoDrawPool::getModelPool( sal_Bool bReadOnly ) throw()
{
    if(m_pDoc)
    {
        SdrModel* pModel = m_pDoc->MakeDrawModel();
        return &pModel->GetItemPool();
    }
    return 0;
}



}
