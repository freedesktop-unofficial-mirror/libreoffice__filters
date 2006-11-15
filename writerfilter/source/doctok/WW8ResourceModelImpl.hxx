/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: WW8ResourceModelImpl.hxx,v $
 *
 *  $Revision: 1.4 $
 *
 *  last change: $Author: hbrinkm $ $Date: 2006-11-15 16:37:43 $
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

#ifndef INCLUDED_WW8_RESOURCE_MODEL_IMPL_HXX
#define INCLUDED_WW8_RESOURCE_MODEL_IMPL_HXX

#ifndef INCLUDED_WW8_DOCUMENT_HXX
#include <doctok/WW8Document.hxx>
#endif 

#ifndef INCLUDED_WW8_RESOURCE_MODEL_HXX
#include <doctok/WW8ResourceModel.hxx>
#endif

#ifndef INCLUDED_WW8_STRUCT_BASE_HXX
#include <WW8StructBase.hxx>
#endif

#ifndef INCLUDED_OUTPUT_WITH_DEPTH_HXX
#include <doctok/OutputWithDepth.hxx>
#endif

#include <odiapi/qname/QName.hxx>
#include <map>

namespace doctok
{
using namespace ::std;

class WW8PropertiesReference : public doctok::Reference<Properties>
{
    WW8PropertySet::Pointer_t mpPropSet;

public:
    
    WW8PropertiesReference(WW8PropertySet::Pointer_t pPropSet)
    : mpPropSet(pPropSet)
    {
    }

    ~WW8PropertiesReference()
    {
    }

    virtual void resolve(Properties & rHandler);

    virtual string getType() const;
};

class WW8TableReference : public doctok::Reference<Table>
{
public:
    WW8TableReference()
    {
    }

    ~WW8TableReference()
    {
    }

    virtual void resolve(Table & rHandler);
    
    virtual string getType() const;
};

class WW8BinaryObjReference : public doctok::Reference<BinaryObj>, 
                              public WW8StructBase
{
public:
    typedef boost::shared_ptr<WW8BinaryObjReference> Pointer_t;
    WW8BinaryObjReference(WW8Stream & rStream, sal_uInt32 nOffset, 
                          sal_uInt32 nCount);    
    WW8BinaryObjReference(WW8StructBase & rParent, sal_uInt32 nOffset, 
                          sal_uInt32 nCount); 
    WW8BinaryObjReference(WW8StructBase * rParent, sal_uInt32 nOffset, 
                          sal_uInt32 nCount); 

    WW8BinaryObjReference()
    : WW8StructBase(WW8StructBase::Sequence())
    {
    }

    ~WW8BinaryObjReference()
    {
    }

    virtual doctok::Reference<BinaryObj>::Pointer_t getBinary();

    virtual void resolve(BinaryObj & rHandler);

    virtual string getType() const;

    virtual WW8BinaryObjReference * clone() { return new WW8BinaryObjReference(*this); }
};

class WW8Sprm : public Sprm
{
    WW8Property::Pointer_t mpProperty;
    WW8BinaryObjReference::Pointer_t mpBinary;

public:
    WW8Sprm(WW8Property::Pointer_t pProperty)
    : mpProperty(pProperty)
    {        
    }

    WW8Sprm(WW8BinaryObjReference::Pointer_t pBinary)
    : mpBinary(pBinary)
    {
    }

    WW8Sprm()
    {
    }

    WW8Sprm(const WW8Sprm & rSprm)
    : Sprm(rSprm), mpProperty(rSprm.mpProperty), mpBinary(rSprm.mpBinary)
    {
    }

    virtual ~WW8Sprm()
    {
    }

    virtual Value::Pointer_t getValue();
    virtual doctok::Reference<BinaryObj>::Pointer_t getBinary();
    virtual doctok::Reference<Stream>::Pointer_t getStream();
    virtual doctok::Reference<Properties>::Pointer_t getProps();

    virtual sal_uInt32 getId() const;
    virtual string toString() const;
    virtual string getName() const;

    virtual WW8Sprm * clone() const { return new WW8Sprm(*this); }
};

class WW8Value : public Value
{
public:
    WW8Value() {}
    virtual ~WW8Value() {}

    virtual string toString() const;
    virtual int getInt() const;
    virtual ::rtl::OUString getString() const;
    virtual uno::Any getAny() const;
    virtual doctok::Reference<Properties>::Pointer_t getProperties();
    virtual doctok::Reference<Stream>::Pointer_t getStream();
    virtual WW8Value * clone() const = 0;
};

class WW8IntValue : public WW8Value
{
    int mValue;
public:
    WW8IntValue(int value) : mValue(value) {}
    virtual ~WW8IntValue() {}

    virtual int getInt() const;
    virtual ::rtl::OUString getString() const;
    virtual uno::Any getAny() const;

    virtual string toString() const;

    virtual WW8Value * clone() const { return new WW8IntValue(*this); }
};

/**
   Creates value from an integer.

   @param value   integer to create value from.
*/
WW8Value::Pointer_t createValue(int value);

ostream & operator << (ostream & o, const WW8Value & rValue);

class WW8StringValue : public WW8Value
{
    ::rtl::OUString mString;

public:
    WW8StringValue(::rtl::OUString string_) : mString(string_) {}
    virtual ~WW8StringValue() {}

    virtual int getInt() const;
    virtual ::rtl::OUString getString() const;
    virtual uno::Any getAny() const;

    virtual string toString() const;

    virtual WW8Value * clone() const { return new WW8StringValue(*this); }
};

/**
   Creates value from a string.

   @param rStr   string to create value from.
*/
WW8Value::Pointer_t createValue(const rtl::OUString & rStr);

class WW8PropertiesValue : public WW8Value
{
    mutable doctok::Reference<Properties>::Pointer_t mRef;

public:
    WW8PropertiesValue(doctok::Reference<Properties>::Pointer_t rRef)
    : mRef(rRef)
    {
    }

    virtual ~WW8PropertiesValue()
    {
    }

    virtual doctok::Reference<Properties>::Pointer_t getProperties();

    virtual string toString() const;

    virtual WW8Value * clone() const { return new WW8PropertiesValue(mRef); }
};

class WW8StreamValue : public WW8Value
{
    mutable doctok::Reference<Stream>::Pointer_t mRef;

public:
    WW8StreamValue(doctok::Reference<Stream>::Pointer_t rRef)
    : mRef(rRef)
    {
    }

    virtual ~WW8StreamValue()
    {
    }

    virtual doctok::Reference<Stream>::Pointer_t getStream();

    virtual string toString() const;

    virtual WW8Value * clone() const { return new WW8StreamValue(mRef); }
};

/**
   Creates value from a properties reference.

   @param rRef   reference to create value from.
*/
WW8Value::Pointer_t createValue(doctok::Reference<Properties>::Pointer_t rRef);

/**
   Creates value from another value.

   @param value  the value to copy
*/
WW8Value::Pointer_t createValue(WW8Value::Pointer_t value);

/**
   Creates value from a stream reference.

   @param rRef    reference to the stream
 */
WW8Value::Pointer_t createValue(doctok::Reference<Stream>::Pointer_t rRef);

class WW8StreamHandler : public Stream
{    
public:
    WW8StreamHandler();
    virtual ~WW8StreamHandler();

    virtual void startSectionGroup();
    virtual void endSectionGroup();
    virtual void startParagraphGroup();
    virtual void endParagraphGroup();
    virtual void startCharacterGroup();
    virtual void endCharacterGroup();
    virtual void text(const sal_uInt8 * data, size_t len);
    virtual void utext(const sal_uInt8 * data, size_t len);

    virtual void props(doctok::Reference<Properties>::Pointer_t ref);
    virtual void table(Id name, 
                       doctok::Reference<Table>::Pointer_t ref);

    virtual void substream(Id name, doctok::Reference<Stream>::Pointer_t ref);

    virtual void info(const string & info);    
};

class WW8PropertiesHandler : public Properties
{
public:
    WW8PropertiesHandler()
    {
    }

    virtual ~WW8PropertiesHandler()
    {
    }

    virtual void attribute(Id name, Value & val);
    virtual void sprm(Sprm & sprm);
};

class WW8BinaryObjHandler : public BinaryObj
{
public:
    WW8BinaryObjHandler()
    {
    }

    virtual ~WW8BinaryObjHandler()
    {
    }

    virtual void data(const sal_uInt8* buf, size_t len,  
                      doctok::Reference<Properties>::Pointer_t ref);    
};

class WW8TableHandler : public Table
{
public:
    WW8TableHandler()
    {
    }

    virtual ~WW8TableHandler()
    {
    }

    void entry(int pos, doctok::Reference<Properties>::Pointer_t ref);    
};

class QNameToString
{
    typedef boost::shared_ptr<QNameToString> Pointer_t;

    static Pointer_t pInstance;

    map < writerfilter::QName_t, string > mMap;

protected:
    /**
       Generated.
     */
    QNameToString();

public:
    static Pointer_t Instance();

    string operator()(writerfilter::QName_t qName);
};

void dump(OutputWithDepth<string> & o, const char * name, doctok::Reference<Properties>::Pointer_t props);
void dump(OutputWithDepth<string> & o, const char * name, sal_uInt32 n);

}

#endif // INCLUDED_WW8_RESOURCE_MODEL_IMPL_HXX
