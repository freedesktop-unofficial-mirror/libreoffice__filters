/*************************************************************************
 *
 *  $RCSfile: svx_fmdpage.cxx,v $
 *
 *  $Revision: 1.2 $
 *
 *  last change: $Author: mwu $ $Date: 2003-11-06 07:43:39 $
 *
 *  The Contents of this file are made available subject to the terms of
 *  either of the following licenses
 *
 *         - GNU Lesser General Public License Version 2.1
 *         - Sun Industry Standards Source License Version 1.1
 *
 *  Sun Microsystems Inc., October, 2000
 *
 *  GNU Lesser General Public License Version 2.1
 *  =============================================
 *  Copyright 2000 by Sun Microsystems, Inc.
 *  901 San Antonio Road, Palo Alto, CA 94303, USA
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public
 *  License version 2.1, as published by the Free Software Foundation.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public
 *  License along with this library; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 *  MA  02111-1307  USA
 *
 *
 *  Sun Industry Standards Source License Version 1.1
 *  =================================================
 *  The contents of this file are subject to the Sun Industry Standards
 *  Source License Version 1.1 (the "License"); You may not use this file
 *  except in compliance with the License. You may obtain a copy of the
 *  License at http://www.openoffice.org/license.html.
 *
 *  Software provided under this License is provided on an "AS IS" basis,
 *  WITHOUT WARRANTY OF ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING,
 *  WITHOUT LIMITATION, WARRANTIES THAT THE SOFTWARE IS FREE OF DEFECTS,
 *  MERCHANTABLE, FIT FOR A PARTICULAR PURPOSE, OR NON-INFRINGING.
 *  See the License for the specific provisions governing your rights and
 *  obligations concerning the Software.
 *
 *  The Initial Developer of the Original Code is: Sun Microsystems, Inc.
 *
 *  Copyright: 2000 by Sun Microsystems, Inc.
 *
 *  All Rights Reserved.
 *
 *  Contributor(s): _______________________________________
 *
 *
 ************************************************************************/

#pragma hdrstop

#ifndef _SVX_FMPAGE_HXX
#include "fmpage.hxx"
#endif

#ifndef _SVX_FMOBJ_HXX
#include "fmobj.hxx"
#endif

#ifndef _SVX_FMGLOB_HXX
#include "fmglob.hxx"
#endif

#ifndef _SVX_FMDPAGE_HXX
#include "fmdpage.hxx"
#endif

#ifndef _SVX_UNOSHAPE_HXX //autogen
#include "unoshape.hxx"
#endif
#ifndef _CPPUHELPER_QUERYINTERFACE_HXX_
#include <cppuhelper/queryinterface.hxx>
#endif
#ifndef _FM_IMPLEMENTATION_IDS_HXX_
#include "fmimplids.hxx"
#endif
namespace binfilter {

/*N*/ DBG_NAME(SvxFmDrawPage);
/*N*/ SvxFmDrawPage::SvxFmDrawPage( SdrPage* pInPage ) :
/*N*/ 	SvxDrawPage( pInPage )
/*N*/ {
/*N*/ 	DBG_CTOR(SvxFmDrawPage,NULL);
    /*N*/ 	m_pHoldImplIdHelper = new ::binfilter::form::OImplementationIdsRef(); //STRIP008 m_pHoldImplIdHelper = new ::form::OImplementationIdsRef();
/*N*/ }

/*N*/ SvxFmDrawPage::~SvxFmDrawPage() throw ()
/*N*/ {
/*N*/ 	delete m_pHoldImplIdHelper;
/*N*/ 	DBG_DTOR(SvxFmDrawPage,NULL);
/*N*/ }

/*N*/ ::com::sun::star::uno::Sequence< sal_Int8 > SAL_CALL SvxFmDrawPage::getImplementationId() throw(::com::sun::star::uno::RuntimeException)
/*N*/ {DBG_ASSERT(0, "STRIP"); ::com::sun::star::uno::Sequence< sal_Int8 > a; return a; //STRIP001 
//STRIP001 	return ::binfilter::form::OImplementationIds::getImplementationId(getTypes()); //STRIP008 return ::form::OImplementationIds::getImplementationId(getTypes());
/*N*/ }

/*N*/ ::com::sun::star::uno::Any SAL_CALL SvxFmDrawPage::queryAggregation( const ::com::sun::star::uno::Type& aType ) throw(::com::sun::star::uno::RuntimeException)
/*N*/ {
/*N*/ 	::com::sun::star::uno::Any aRet = ::cppu::queryInterface(aType,
/*N*/ 		static_cast< ::com::sun::star::form::XFormsSupplier*>(this));
/*N*/ 	if(aRet.hasValue())
/*N*/ 		return aRet;
/*N*/ 
/*N*/ 	return SvxDrawPage::queryAggregation(aType);
/*N*/ }

/***********************************************************************
*                                                                      *
***********************************************************************/
//STRIP001 ::com::sun::star::uno::Sequence< ::com::sun::star::uno::Type > SAL_CALL SvxFmDrawPage::getTypes(  ) throw(::com::sun::star::uno::RuntimeException)
//STRIP001 {
//STRIP001 	::com::sun::star::uno::Sequence< ::com::sun::star::uno::Type > aTypes(SvxDrawPage::getTypes());
//STRIP001 	aTypes.realloc(aTypes.getLength() + 1);
//STRIP001 	::com::sun::star::uno::Type* pTypes = aTypes.getArray();
//STRIP001 
//STRIP001 	pTypes[aTypes.getLength()-1] = ::getCppuType((const ::com::sun::star::uno::Reference< ::com::sun::star::form::XFormsSupplier>*)0);
//STRIP001 	return aTypes;
//STRIP001 }

/*N*/ SdrObject *SvxFmDrawPage::_CreateSdrObject( const ::com::sun::star::uno::Reference< ::com::sun::star::drawing::XShape > & xDescr ) throw ()
/*N*/ {
/*N*/ 	::rtl::OUString aShapeType( xDescr->getShapeType() );
/*N*/ 
/*N*/ 	if (aShapeType  ==  ::rtl::OUString::createFromAscii("com.sun.star.drawing.ShapeControl"))
/*?*/ 		return new FmFormObj(OBJ_FM_CONTROL);
/*N*/ 	else
/*N*/ 		return SvxDrawPage::_CreateSdrObject( xDescr );
/*N*/ 
/*N*/ }

/*N*/ ::com::sun::star::uno::Reference< ::com::sun::star::drawing::XShape >  SvxFmDrawPage::_CreateShape( SdrObject *pObj ) const throw ()
/*N*/ {
/*N*/ 	if( FmFormInventor == pObj->GetObjInventor() )
/*N*/ 	{
/*N*/ 		::com::sun::star::uno::Reference< ::com::sun::star::drawing::XShape >  xShape = (SvxShape*)new SvxShapeControl( pObj );
/*N*/ 		return xShape;
/*N*/ 	}
/*N*/ 	else
/*N*/ 		return SvxDrawPage::_CreateShape( pObj );
/*N*/ }

// ::com::sun::star::form::XFormsSupplier
/*N*/ ::com::sun::star::uno::Reference< ::com::sun::star::container::XNameContainer > SAL_CALL SvxFmDrawPage::getForms(void) throw( ::com::sun::star::uno::RuntimeException )
/*N*/ {
/*N*/ 	::com::sun::star::uno::Reference< ::com::sun::star::container::XNameContainer >  xForms;
/*N*/ 
/*N*/ 	FmFormPage *pFmPage = PTR_CAST( FmFormPage, GetSdrPage() );
/*N*/ 	if( pFmPage )
/*N*/ 		xForms = pFmPage->GetForms();
/*N*/ 
/*N*/ 	return xForms;
/*N*/ }

// ::com::sun::star::lang::XServiceInfo
/*N*/ ::com::sun::star::uno::Sequence< ::rtl::OUString > SAL_CALL SvxFmDrawPage::getSupportedServiceNames(void) throw( ::com::sun::star::uno::RuntimeException )
/*N*/ {
    /* TODO: DG? Irgendwelche Services?
    ::com::sun::star::uno::Sequence aSeq( SvxDrawPage::getSupportedServiceNames() );
    addToSequence( aSeq, 1, ::rtl::OUString::createFromAscii("stardiv.form.superservice?") );
    return aSeq;
    */
/*N*/ 
/*N*/ 	return SvxDrawPage::getSupportedServiceNames();
/*N*/ }


}
