/*************************************************************************
 *
 *  $RCSfile: attributes.cxx,v $
 *
 *  $Revision: 1.1 $
 *
 *  last change: $Author: dvo $ $Date: 2003-10-15 14:38:39 $
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
 *  Copyright 2001 by Mizi Research Inc.
 *  Copyright 2003 by Sun Microsystems, Inc.
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
 *  The Initial Developer of the Original Code is: Mizi Research Inc.
 *
 *  Copyright: 2001 by Mizi Research Inc.
 *  Copyright: 2003 by Sun Microsystems, Inc.
 *
 *  All Rights Reserved.
 *
 *  Contributor(s): _______________________________________
 *
 *
 ************************************************************************/

#include <assert.h>
#ifndef __SGI_STL_VECTOR
#include <vector>
#endif

#ifndef _CONFIGMGR_MISC_ATTRIBUTES_HXX_
#include "attributes.hxx"
#endif

//using namespace ::std;

struct TagAttribute
{
    TagAttribute(){}
    TagAttribute( const OUString &sName, const OUString &sType , const OUString &sValue )
    {
        this->sName     = sName;
        this->sType     = sType;
        this->sValue    = sValue;
    }

    OUString sName;
    OUString sType;
    OUString sValue;
};

struct AttributeListImpl_impl
{
    AttributeListImpl_impl()
    {
// performance improvement during adding
        vecAttribute.reserve(20);
    }
    std::vector<struct TagAttribute> vecAttribute;
};

sal_Int16 SAL_CALL AttributeListImpl::getLength(void) throw (RuntimeException)
{
    return m_pImpl->vecAttribute.size();
}


AttributeListImpl::AttributeListImpl( const AttributeListImpl &r )
{
    m_pImpl = new AttributeListImpl_impl;
    *m_pImpl = *(r.m_pImpl);
}


OUString AttributeListImpl::getNameByIndex(sal_Int16 i) throw (RuntimeException)
{
    if( i < m_pImpl->vecAttribute.size() )
    {
        return m_pImpl->vecAttribute[i].sName;
    }
    return OUString();
}


OUString AttributeListImpl::getTypeByIndex(sal_Int16 i) throw (RuntimeException)
{
    if( i < m_pImpl->vecAttribute.size() )
    {
        return m_pImpl->vecAttribute[i].sType;
    }
    return OUString();
}


OUString AttributeListImpl::getValueByIndex(sal_Int16 i) throw (RuntimeException)
{
    if( i < m_pImpl->vecAttribute.size() )
    {
        return m_pImpl->vecAttribute[i].sValue;
    }
    return OUString();

}


OUString AttributeListImpl::getTypeByName( const OUString& sName ) throw (RuntimeException)
{
    std::vector<struct TagAttribute>::iterator ii = m_pImpl->vecAttribute.begin();

    for( ; ii != m_pImpl->vecAttribute.end() ; ii ++ )
    {
        if( (*ii).sName == sName )
        {
            return (*ii).sType;
        }
    }
    return OUString();
}


OUString AttributeListImpl::getValueByName(const OUString& sName) throw (RuntimeException)
{
    std::vector<struct TagAttribute>::iterator ii = m_pImpl->vecAttribute.begin();

    for( ; ii != m_pImpl->vecAttribute.end() ; ii ++ )
    {
        if( (*ii).sName == sName )
        {
            return (*ii).sValue;
        }
    }
    return OUString();
}


AttributeListImpl::AttributeListImpl()
{
    m_pImpl = new AttributeListImpl_impl;
}


AttributeListImpl::~AttributeListImpl()
{
    delete m_pImpl;
}


void AttributeListImpl::addAttribute(   const OUString &sName ,
const OUString &sType ,
const OUString &sValue )
{
    m_pImpl->vecAttribute.push_back( TagAttribute( sName , sType , sValue ) );
}


void AttributeListImpl::clear()
{
    std::vector<struct TagAttribute> dummy;
    m_pImpl->vecAttribute.swap( dummy );

    assert( ! getLength() );
}
