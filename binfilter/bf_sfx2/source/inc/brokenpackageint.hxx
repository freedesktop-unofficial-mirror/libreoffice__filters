/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: brokenpackageint.hxx,v $
 *
 *  $Revision: 1.4 $
 *
 *  last change: $Author: rt $ $Date: 2005-09-08 03:22:30 $
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

// auto strip #ifndef _COM_SUN_STAR_DOCUMENT_BROKENPACKAGEREQUEST_HPP_
// auto strip #include <com/sun/star/document/BrokenPackageRequest.hpp>
// auto strip #endif
// auto strip #ifndef _COM_SUN_STAR_TASK_XINTERACTIONAPPROVE_HPP_
// auto strip #include <com/sun/star/task/XInteractionApprove.hpp>
// auto strip #endif
// auto strip #ifndef _COM_SUN_STAR_TASK_XINTERACTIONDISAPPROVE_HPP_
// auto strip #include <com/sun/star/task/XInteractionDisapprove.hpp>
// auto strip #endif

#ifndef __FRAMEWORK_DISPATCH_INTERACTION_HXX_
#include <framework/interaction.hxx>
#endif
namespace binfilter {

using namespace ::framework;
typedef ContinuationBase< ::com::sun::star::task::XInteractionApprove > SfxContinuationApprove;
typedef ContinuationBase< ::com::sun::star::task::XInteractionDisapprove > SfxContinuationDisapprove;
 
class RequestPackageReparation : public ::cppu::WeakImplHelper1< ::com::sun::star::task::XInteractionRequest >
{
    ::com::sun::star::uno::Any m_aRequest;
        
    ::com::sun::star::uno::Sequence< 
                    ::com::sun::star::uno::Reference< ::com::sun::star::task::XInteractionContinuation > 
                > m_lContinuations;
        
    SfxContinuationApprove*	m_pApprove;
    SfxContinuationDisapprove*	m_pDisapprove;

public:
    RequestPackageReparation( ::rtl::OUString aName );
    
    sal_Bool	isApproved() { return m_pApprove->isSelected(); }
        
    virtual ::com::sun::star::uno::Any SAL_CALL getRequest() 
        throw( ::com::sun::star::uno::RuntimeException );

    virtual ::com::sun::star::uno::Sequence< 
                ::com::sun::star::uno::Reference< ::com::sun::star::task::XInteractionContinuation > 
            > SAL_CALL getContinuations() 
        throw( ::com::sun::star::uno::RuntimeException );
}; 

class NotifyBrokenPackage : public ::cppu::WeakImplHelper1< ::com::sun::star::task::XInteractionRequest >
{
    ::com::sun::star::uno::Any m_aRequest;
        
    ::com::sun::star::uno::Sequence< 
                    ::com::sun::star::uno::Reference< ::com::sun::star::task::XInteractionContinuation > 
                > m_lContinuations;
        
    ContinuationAbort*	m_pAbort;

public:
    NotifyBrokenPackage( ::rtl::OUString aName );
    
    sal_Bool	isAborted() { return m_pAbort->isSelected(); }
        
    virtual ::com::sun::star::uno::Any SAL_CALL getRequest() 
        throw( ::com::sun::star::uno::RuntimeException );

    virtual ::com::sun::star::uno::Sequence< 
                ::com::sun::star::uno::Reference< ::com::sun::star::task::XInteractionContinuation > 
            > SAL_CALL getContinuations() 
        throw( ::com::sun::star::uno::RuntimeException );
};  
}//end of namespace binfilter

