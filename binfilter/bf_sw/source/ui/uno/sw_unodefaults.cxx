/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: sw_unodefaults.cxx,v $
 *
 *  $Revision: 1.4 $
 *
 *  last change: $Author: rt $ $Date: 2005-09-09 06:55:50 $
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


#pragma hdrstop

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
