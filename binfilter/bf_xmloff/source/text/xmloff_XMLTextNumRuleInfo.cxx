/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: xmloff_XMLTextNumRuleInfo.cxx,v $
 *
 *  $Revision: 1.4 $
 *
 *  last change: $Author: rt $ $Date: 2006-10-28 02:19:11 $
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


#ifndef _COM_SUN_STAR_BEANS_XPROPERTYSET_HPP_ 
#include <com/sun/star/beans/XPropertySet.hpp>
#endif
#ifndef _COM_SUN_STAR_BEANS_PROPERTYVALUE_HPP_ 
#include <com/sun/star/beans/PropertyValue.hpp>
#endif
#ifndef _COM_SUN_STAR_STYLE_NUMBERINGTYPE_HPP_
#include <com/sun/star/style/NumberingType.hpp>
#endif
#ifndef _COM_SUN_STAR_CONTAINER_XNAMED_HPP_ 
#include <com/sun/star/container/XNamed.hpp>
#endif

#ifndef _XMLOFF_XMLTEXTNUMRULEINFO_HXX
#include "XMLTextNumRuleInfo.hxx"
#endif
namespace binfilter {

using namespace ::rtl;
using namespace ::com::sun::star;
using namespace ::com::sun::star::uno;
using namespace ::com::sun::star::beans;
using namespace ::com::sun::star::container;
using namespace ::com::sun::star::style;

XMLTextNumRuleInfo::XMLTextNumRuleInfo() :
    sNumberingRules(RTL_CONSTASCII_USTRINGPARAM("NumberingRules")),
    sNumberingLevel(RTL_CONSTASCII_USTRINGPARAM("NumberingLevel")),
    sNumberingStartValue(RTL_CONSTASCII_USTRINGPARAM("NumberingStartValue")),
    sParaIsNumberingRestart(RTL_CONSTASCII_USTRINGPARAM("ParaIsNumberingRestart")),
    sNumberingType(RTL_CONSTASCII_USTRINGPARAM("NumberingType")),
    sIsNumbering(RTL_CONSTASCII_USTRINGPARAM("IsNumbering")),
    sNumberingIsNumber(RTL_CONSTASCII_USTRINGPARAM("NumberingIsNumber"))
{
    Reset();
}

void XMLTextNumRuleInfo::Set(
        const ::com::sun::star::uno::Reference < 
            ::com::sun::star::text::XTextContent > & xTextContent )
{
    Reset();

    Reference< XPropertySet > xPropSet( xTextContent, UNO_QUERY );
    Reference< XPropertySetInfo > xPropSetInfo = xPropSet->getPropertySetInfo();

    Any aAny;

    // check if this paragraph supports a numbering
    if( !xPropSetInfo->hasPropertyByName( sNumberingLevel ) )
        return;

    if( xPropSetInfo->hasPropertyByName( sNumberingRules ) )
    {
        aAny = xPropSet->getPropertyValue( sNumberingRules );
        aAny >>= xNumRules;
    }

    if( xNumRules.is() )
    {
        Reference < XNamed > xNamed( xNumRules, UNO_QUERY );
        if( xNamed.is() )
        {
            bIsNamed = sal_True;
            sName = xNamed->getName();
        }

        aAny = xPropSet->getPropertyValue( sNumberingLevel );
        aAny >>= nLevel;
        
        bIsNumbered = sal_True;
        if( xPropSetInfo->hasPropertyByName( sNumberingIsNumber ) )
        {
            aAny = xPropSet->getPropertyValue( sNumberingIsNumber );
            bIsNumbered = *(sal_Bool *)aAny.getValue();
        }

        if( bIsNumbered )
        {
            if( xPropSetInfo->hasPropertyByName( sParaIsNumberingRestart ) )
            {
                aAny = xPropSet->getPropertyValue( sParaIsNumberingRestart );
                bIsRestart = *(sal_Bool *)aAny.getValue();
            }
            if( xPropSetInfo->hasPropertyByName( sNumberingStartValue ) )
            {
                aAny = xPropSet->getPropertyValue( sNumberingStartValue );
                aAny >>= nStartValue;
            }
        }

        OSL_ENSURE( nLevel < xNumRules->getCount(), "wrong num rule level" );
        if( nLevel >= xNumRules->getCount() )
        {
            Reset();
            return;
        }

        aAny = xNumRules->getByIndex( nLevel );
        Sequence<PropertyValue> aProps;
        aAny >>= aProps;
        const PropertyValue* pPropArray = aProps.getConstArray();
        sal_Int32 nCount = aProps.getLength();
        for( sal_Int32 i=0; i<nCount; i++ )
        {
            const beans::PropertyValue& rProp = pPropArray[i];

            if( rProp.Name == sNumberingType )
            {
                sal_Int16 nType;
                rProp.Value >>= nType;
                if( NumberingType::CHAR_SPECIAL != nType &&
                    NumberingType::BITMAP != nType )
                {
                    bIsOrdered = sal_True;
                }
                break;
            }
        }
        nLevel++;
    }
}



}//end of namespace binfilter
