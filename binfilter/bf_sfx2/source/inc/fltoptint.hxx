/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: fltoptint.hxx,v $
 *
 *  $Revision: 1.5 $
 *
 *  last change: $Author: rt $ $Date: 2006-10-27 19:35:31 $
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

#ifndef _COM_SUN_STAR_DOCUMENT_XINTERACTIONFILTEROPTIONS_HPP_
#include <com/sun/star/document/XInteractionFilterOptions.hpp>
#endif
#ifndef _COM_SUN_STAR_FRAME_XMODEL_HPP_
#include <com/sun/star/frame/XModel.hpp>
#endif

#ifndef __FRAMEWORK_DISPATCH_INTERACTION_HXX_
#include <framework/interaction.hxx>
#endif

using namespace ::framework;
namespace binfilter {
 
class FilterOptionsContinuation : public ContinuationBase< ::com::sun::star::document::XInteractionFilterOptions >
{
    ::com::sun::star::uno::Sequence< ::com::sun::star::beans::PropertyValue > rProperties;

public:
    virtual void SAL_CALL setFilterOptions( const ::com::sun::star::uno::Sequence< ::com::sun::star::beans::PropertyValue >& rProp ) throw (::com::sun::star::uno::RuntimeException);
    virtual ::com::sun::star::uno::Sequence< ::com::sun::star::beans::PropertyValue > SAL_CALL getFilterOptions(  ) throw (::com::sun::star::uno::RuntimeException);
};

class RequestFilterOptions : public ::cppu::WeakImplHelper1< ::com::sun::star::task::XInteractionRequest >
{
    ::com::sun::star::uno::Any m_aRequest;
        
    ::com::sun::star::uno::Sequence< 
                    ::com::sun::star::uno::Reference< ::com::sun::star::task::XInteractionContinuation > 
                > m_lContinuations;
        
    ContinuationAbort*	m_pAbort;
        
    FilterOptionsContinuation*	m_pOptions;

public:
    RequestFilterOptions( ::com::sun::star::uno::Reference< ::com::sun::star::frame::XModel > rModel,
                              ::com::sun::star::uno::Sequence< ::com::sun::star::beans::PropertyValue > rProperties );
    
    sal_Bool	isAbort() { return m_pAbort->isSelected(); }
        
    ::com::sun::star::uno::Sequence< ::com::sun::star::beans::PropertyValue > getFilterOptions()
    {
        return m_pOptions->getFilterOptions();
    }
        
    virtual ::com::sun::star::uno::Any SAL_CALL getRequest() 
        throw( ::com::sun::star::uno::RuntimeException );

    virtual ::com::sun::star::uno::Sequence< 
                ::com::sun::star::uno::Reference< ::com::sun::star::task::XInteractionContinuation > 
            > SAL_CALL getContinuations() 
        throw( ::com::sun::star::uno::RuntimeException );
};  
}//end of namespace binfilter
