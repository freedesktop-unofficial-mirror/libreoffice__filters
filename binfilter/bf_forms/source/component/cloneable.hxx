/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: cloneable.hxx,v $
 *
 *  $Revision: 1.3 $
 *
 *  last change: $Author: rt $ $Date: 2005-09-07 15:38:59 $
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

#ifndef FORMS_COMPONENT_CLONEABLE_HXX
#define FORMS_COMPONENT_CLONEABLE_HXX

#ifndef _COM_SUN_STAR_UNO_XAGGREGATION_HPP_
#include <com/sun/star/uno/XAggregation.hpp>
#endif
namespace binfilter {

//.........................................................................
namespace frm
{
//.........................................................................

    //====================================================================
    //= OCloneableAggregation
    //====================================================================
    class OCloneableAggregation
    {
    protected:
        ::com::sun::star::uno::Reference< ::com::sun::star::uno::XAggregation>	m_xAggregate;

    protected:
        static ::com::sun::star::uno::Reference< ::com::sun::star::uno::XAggregation > createAggregateClone( const OCloneableAggregation* _pOriginal );
    };

//.........................................................................
}	// namespace frm
//.........................................................................

}//end of namespace binfilter
#endif // FORMS_COMPONENT_CLONEABLE_HXX

