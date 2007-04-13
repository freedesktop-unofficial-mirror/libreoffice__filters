/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: OOXMLPropertySetImpl.cxx,v $
 *
 *  $Revision: 1.12 $
 *
 *  last change: $Author: hbrinkm $ $Date: 2007-04-13 10:21:35 $
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

#include "OOXMLPropertySetImpl.hxx"
#include <iostream>
#include <resourcemodel/QNameToString.hxx>

#define DEBUG_RESOLVE

namespace ooxml
{
using namespace ::std;
using namespace doctok;

OOXMLProperty::~OOXMLProperty()
{
}

OOXMLPropertySet::~OOXMLPropertySet()
{
}

OOXMLTable::~OOXMLTable()
{
}

OOXMLPropertyImpl::OOXMLPropertyImpl(Id id, OOXMLValue::Pointer_t pValue,
                                     OOXMLPropertyImpl::Type_t eType)
: mId(id), mpValue(pValue), meType(eType)
{
}

OOXMLPropertyImpl::OOXMLPropertyImpl(const OOXMLPropertyImpl & rSprm)
: OOXMLProperty(), mId(rSprm.mId), mpValue(rSprm.mpValue), meType(rSprm.meType)
{
}

OOXMLPropertyImpl::~OOXMLPropertyImpl()
{
}

sal_uInt32 OOXMLPropertyImpl::getId() const
{
    return mId;
}

Value::Pointer_t OOXMLPropertyImpl::getValue()
{
    Value::Pointer_t pResult;

    if (mpValue.get() != NULL)
        pResult = Value::Pointer_t(mpValue->clone());
    else
        pResult = Value::Pointer_t(new OOXMLValue());

    return pResult;
}

doctok::Reference<BinaryObj>::Pointer_t OOXMLPropertyImpl::getBinary()
{
    doctok::Reference<BinaryObj>::Pointer_t pResult;

    if (mpValue.get() != NULL)
        pResult = mpValue->getBinary();

    return pResult;
}

doctok::Reference<Stream>::Pointer_t OOXMLPropertyImpl::getStream()
{
    doctok::Reference<Stream>::Pointer_t pResult;

    if (mpValue.get() != NULL)
        pResult = mpValue->getStream();

    return pResult;
}

doctok::Reference<Properties>::Pointer_t OOXMLPropertyImpl::getProps()
{
    doctok::Reference<Properties>::Pointer_t pResult;

    if (mpValue.get() != NULL)
        pResult = mpValue->getProperties();

    return pResult;
}

string OOXMLPropertyImpl::getName() const
{
    return (*QNameToString::Instance())(mId);
}

string OOXMLPropertyImpl::toString() const
{
    string sResult = "(";
    static char buffer[256];
    
    snprintf(buffer, sizeof(buffer), "0x%x", mId);
    sResult += buffer;
    sResult += ", ";
    if (mpValue.get() != NULL)
        sResult += mpValue->toString();
    else
        sResult +="(null)";
    sResult +=")";
    
    return sResult;
}

Sprm * OOXMLPropertyImpl::clone()
{
    return new OOXMLPropertyImpl(*this);
}

void OOXMLPropertyImpl::resolve(doctok::Properties & rProperties)
{
    switch (meType)
    {
    case SPRM:
        if (mId != 0x0)
            rProperties.sprm(*this);
        break;
    case ATTRIBUTE:
        rProperties.attribute(mId, *getValue());
        break;
    }

#ifdef DEBUG_RESOLVE
    clog << toString() << endl;
#endif
}

/* 
   class OOXMLValue
*/

OOXMLValue::OOXMLValue()
{
}

OOXMLValue::OOXMLValue(const rtl::OUString & /*rValue*/)
{
}

OOXMLValue::~OOXMLValue()
{
}

int OOXMLValue::getInt() const
{
    return 0;
}

::rtl::OUString OOXMLValue::getString() const
{
    return ::rtl::OUString();
}

uno::Any OOXMLValue::getAny() const
{
    return uno::Any();
}

doctok::Reference<Properties>::Pointer_t OOXMLValue::getProperties()
{
    return doctok::Reference<Properties>::Pointer_t();
}

doctok::Reference<Stream>::Pointer_t OOXMLValue::getStream()
{
    return doctok::Reference<Stream>::Pointer_t();
}

doctok::Reference<BinaryObj>::Pointer_t OOXMLValue::getBinary()
{
    return doctok::Reference<BinaryObj>::Pointer_t();
}

string OOXMLValue::toString() const
{
    return "OOXMLValue";
}

OOXMLValue * OOXMLValue::clone() const
{
    return new OOXMLValue(*this);
}

/*
  class OOXMLBooleanValue
*/

OOXMLBooleanValue::OOXMLBooleanValue(bool bValue)
: mbValue(bValue)
{    
}

OOXMLBooleanValue::~OOXMLBooleanValue()
{
}

int OOXMLBooleanValue::getInt() const
{
    return mbValue ? 1 : 0;
}

uno::Any OOXMLBooleanValue::getAny() const
{
    uno::Any aResult(mbValue);
    
    return aResult;
}

string OOXMLBooleanValue::toString() const
{
    return mbValue ? "true" : "false";
}

OOXMLValue * OOXMLBooleanValue::clone() const
{
    return new OOXMLBooleanValue(*this);
}

/*
  class OOXMLStringValue
*/

OOXMLStringValue::OOXMLStringValue(const rtl::OUString & rStr)
: mStr(rStr)
{
}

OOXMLStringValue::~OOXMLStringValue()
{
}

uno::Any OOXMLStringValue::getAny() const
{
    uno::Any aAny(mStr);
    
    return aAny;
}

rtl::OUString OOXMLStringValue::getString() const
{
    return mStr;
}

string OOXMLStringValue::toString() const
{
    return OUStringToOString(mStr, RTL_TEXTENCODING_ASCII_US).getStr();
}

OOXMLValue * OOXMLStringValue::clone() const
{
    return new OOXMLStringValue(*this);
}

/*
  struct OOXMLPropertySetImplCompare
 */

bool OOXMLPropertySetImplCompare::operator()(const OOXMLProperty::Pointer_t x,
                                             const OOXMLProperty::Pointer_t y) const
{
    bool bResult = false;

    if (x.get() == NULL && y.get() != NULL)
        bResult = true;
    else if (x.get() != NULL && y.get() != NULL)
        bResult = x->getId() < y->getId();

    return bResult;
}

/**
   class OOXMLPropertySetImpl
*/

OOXMLPropertySetImpl::OOXMLPropertySetImpl()
{
}

OOXMLPropertySetImpl::~OOXMLPropertySetImpl()
{
}

void OOXMLPropertySetImpl::resolve(Properties & rHandler)
{
    OOXMLProperties_t::iterator aIt = mProperties.begin();
    while (aIt != mProperties.end())
    {
        OOXMLProperty::Pointer_t pProp = *aIt;

        pProp->resolve(rHandler);

        aIt++;
    }
}

string OOXMLPropertySetImpl::getType() const
{
    return "OOXMLPropertySetImpl";
}

void OOXMLPropertySetImpl::add(OOXMLProperty::Pointer_t pProperty)
{
    if (pProperty->getId() == 0x0)
        clog << "zero property" << endl;

    mProperties.push_back(pProperty);
}

OOXMLPropertySet * OOXMLPropertySetImpl::clone() const
{
    return new OOXMLPropertySetImpl(*this);
}

/*
  class OOXMLPropertySetValue
*/

OOXMLPropertySetValue::OOXMLPropertySetValue
(OOXMLPropertySet::Pointer_t pPropertySet)
: mpPropertySet(pPropertySet)
{    
}

OOXMLPropertySetValue::~OOXMLPropertySetValue()
{
}

doctok::Reference<Properties>::Pointer_t OOXMLPropertySetValue::getProperties()
{
    return doctok::Reference<Properties>::Pointer_t
        (mpPropertySet->clone());
}

string OOXMLPropertySetValue::toString() const
{
    return "OOXMLPropertySetValue";
}

OOXMLValue * OOXMLPropertySetValue::clone() const
{
    return new OOXMLPropertySetValue(*this);
}

/*
  class OOXMLIntegerValue
*/

OOXMLIntegerValue::OOXMLIntegerValue(sal_Int32 nValue)
: mnValue(nValue)
{
}

OOXMLIntegerValue::OOXMLIntegerValue(const rtl::OUString & rValue)
: mnValue(0)
{
    mnValue = rValue.toInt32();
}

OOXMLIntegerValue::~OOXMLIntegerValue()
{
}

int OOXMLIntegerValue::getInt() const
{
    return mnValue;
}

uno::Any OOXMLIntegerValue::getAny() const
{
    uno::Any aResult(mnValue);
    
    return aResult;
}

OOXMLValue * OOXMLIntegerValue::clone() const
{
    return new OOXMLIntegerValue(*this);
}

string OOXMLIntegerValue::toString() const
{
    char buffer[256];
    snprintf(buffer, sizeof(buffer), "%ld", mnValue);

    return buffer;
}

/*
  class OOXMLHexValue
*/

OOXMLHexValue::OOXMLHexValue(sal_uInt32 nValue)
: mnValue(nValue)
{
}

OOXMLHexValue::OOXMLHexValue(const rtl::OUString & rValue)
{
    mnValue = static_cast<sal_uInt32>(rValue.toInt32(16));
}

OOXMLHexValue::~OOXMLHexValue()
{
}

int OOXMLHexValue::getInt() const
{
    return mnValue;
}

OOXMLValue * OOXMLHexValue::clone() const
{
    return new OOXMLHexValue(*this);
}

string OOXMLHexValue::toString() const
{
    char buffer[256];
    snprintf(buffer, sizeof(buffer), "0x%lx", mnValue);

    return buffer;
}

/*
  class OOXMLListValue
*/
OOXMLListValue::OOXMLListValue()
: OOXMLIntegerValue(0)
{
}

OOXMLListValue::~OOXMLListValue()
{
}

/*
  class OOXMLTableImpl
 */

OOXMLTableImpl::OOXMLTableImpl()
{
}

OOXMLTableImpl::~OOXMLTableImpl()
{
}

void OOXMLTableImpl::resolve(Table & rTable)
{
    int nPos = 0;

    PropertySets_t::iterator it = mPropertySets.begin();
    PropertySets_t::iterator itEnd = mPropertySets.end();
        
    while (it != itEnd)
    {
        doctok::Reference<Properties>::Pointer_t pProperties 
            ((*it)->getProperties());

        if (pProperties.get() != NULL)
            rTable.entry(nPos, pProperties);

        ++nPos;
        it++;
    }
}

void OOXMLTableImpl::add(ValuePointer_t pPropertySet)
{
    mPropertySets.push_back(pPropertySet);
}

string OOXMLTableImpl::getType() const
{
    return "OOXMLTableImpl";
}

OOXMLTable * OOXMLTableImpl::clone() const
{
    return new OOXMLTableImpl(*this);
}

}
