/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: docpasswdrequest.hxx,v $
 *
 *  $Revision: 1.2 $
 *
 *  last change: $Author: rt $ $Date: 2008-03-12 11:56:10 $
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

#ifndef INCLUDED_SVTOOLS_DOCPASSWDREQUEST_HXX
#define INCLUDED_SVTOOLS_DOCPASSWDREQUEST_HXX

#ifndef _COM_SUN_STAR_TASK_DOCUMENTPASSWORDREQUEST_HPP_
#include <com/sun/star/task/DocumentPasswordRequest.hpp>
#endif
#ifndef _COM_SUN_STAR_TASK_XINTERACTIONREQUEST_HPP_
#include <com/sun/star/task/XInteractionRequest.hpp>
#endif

#ifndef _RTL_USTRING_HXX_
#include <rtl/ustring.hxx>
#endif

#ifndef _CPPUHELPER_IMPLBASE1_HXX_
#include <cppuhelper/implbase1.hxx>
#endif

namespace binfilter {

class AbortContinuation;
class PasswordContinuation;

class  RequestDocumentPassword : public ::cppu::WeakImplHelper1< ::com::sun::star::task::XInteractionRequest >
{
    ::com::sun::star::uno::Any m_aRequest;
        
    ::com::sun::star::uno::Sequence< 
                    ::com::sun::star::uno::Reference< ::com::sun::star::task::XInteractionContinuation > 
                > m_lContinuations;
        
    AbortContinuation*	    m_pAbort;
    PasswordContinuation*	m_pPassword;

public:
    RequestDocumentPassword( ::com::sun::star::task::PasswordRequestMode nMode, ::rtl::OUString aName );
    
    sal_Bool isAbort();
    sal_Bool isPassword();
        
    ::rtl::OUString getPassword();
        
    virtual ::com::sun::star::uno::Any SAL_CALL getRequest() 
        throw( ::com::sun::star::uno::RuntimeException );

    virtual ::com::sun::star::uno::Sequence< 
                ::com::sun::star::uno::Reference< ::com::sun::star::task::XInteractionContinuation > 
            > SAL_CALL getContinuations() 
        throw( ::com::sun::star::uno::RuntimeException );
};  

}

#endif /* INCLUDED_SVTOOLS_DOCPASSWDREQUEST_HXX */
