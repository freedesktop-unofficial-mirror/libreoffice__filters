#ifndef INCLUDED_WW8_PROPERTY_SET_IMPL_HXX
#define INCLUDED_WW8_PROEPRTY_SET_IMPL_HXX

#ifndef INCLUDED_WW8_RESOURCE_MODEL_HXX
#include <doctok/WW8ResourceModel.hxx>
#endif

#ifndef INCLUDED_WW8_DOCUMENT_HXX
#include <doctok/WW8Document.hxx>
#endif

#ifndef INCLUDED_WW8_STRUCT_BASE_HXX
#include <WW8StructBase.hxx>
#endif

#ifndef INCLUDED_WW8_OUTPUT_WITH_DEPTH
#include <WW8OutputWithDepth.hxx>
#endif

#include <map>

namespace doctok 
{

class WW8PropertyImpl : public WW8Property, public WW8StructBase
{
    sal_uInt8 get_ispmd() const 
    { return sal::static_int_cast<sal_uInt8>(getId() & 0xff); }
    bool get_fSpec() const { return (getId() & 0x100) != 0; }
    sal_uInt8 get_sgc() const 
    { return sal::static_int_cast<sal_uInt8>((getId() >> 10) & 0x7); }
    sal_uInt8 get_spra() const 
    { return sal::static_int_cast<sal_uInt8>((getId() >> 13) & 0x7); }

public:
    WW8PropertyImpl(WW8Stream & rStream, sal_uInt32 nOffset, sal_uInt32 nCount);
    WW8PropertyImpl(const WW8StructBase & rBase, sal_uInt32 nOffset, 
                    sal_uInt32 nCount);

    WW8PropertyImpl(WW8StructBase * pBase, sal_uInt32 nOffset, 
                    sal_uInt32 nCount);

    virtual ~WW8PropertyImpl();

    sal_uInt32 getId() const { return getU16(0); }
    sal_uInt32 getParam() const;
    WW8Stream::Sequence getParams() const;

    sal_uInt32 getByteLength() const;
    sal_uInt32 getParamOffset() const;

    virtual void dump(OutputWithDepth<string> & o) const;
    string toString() const;
};

class WW8PropertySetImpl : public WW8PropertySet, public WW8StructBase,
                           public ::doctok::Reference<Properties>
{
    bool mbPap;

public:
    typedef boost::shared_ptr<WW8PropertySet> Pointer_t;
    
    WW8PropertySetImpl(WW8Stream & rStream, sal_uInt32 nOffset,
                       sal_uInt32 nCount, bool bPap = false);

    WW8PropertySetImpl(const WW8StructBase & rBase, sal_uInt32 nOffset,
                       sal_uInt32 nCount, bool bPap = false);

    virtual ~WW8PropertySetImpl();

    virtual WW8PropertySetIterator::Pointer_t begin();
    virtual WW8PropertySetIterator::Pointer_t end();

    virtual void dump(OutputWithDepth<string> & o) const;
    virtual void dots(ostream & o);

    virtual string getType() const;

    virtual WW8Property::Pointer_t getAttribute(sal_uInt32 nOffset) const;

    virtual bool isPap() const;
    virtual sal_uInt32 get_istd() const;

    virtual void insert(const WW8PropertySet::Pointer_t /*pSet*/) {}

    virtual void resolve(Properties & rHandler);

    /**
       Get and distribute information from sprm that is used
       internally by the document.

       @param rSprm    sprm to process
     */
    virtual void resolveLocal(Sprm & rSprm);
};

class WW8PropertySetIteratorImpl : public WW8PropertySetIterator
{
    WW8PropertySetImpl * mpAttrSet;
    sal_uInt32 mnOffset;

public:
    WW8PropertySetIteratorImpl(WW8PropertySetImpl * pAttrSet, 
                               sal_uInt32 nOffset)
    : mpAttrSet(pAttrSet), mnOffset(nOffset)
    {
    }

    virtual ~WW8PropertySetIteratorImpl();

    virtual WW8PropertySetIterator & operator++();

    virtual WW8Property::Pointer_t get() const;

    virtual bool equal(const WW8PropertySetIterator & rIt) const;

    virtual string toString() const;
};


class SprmIdToString
{
    typedef boost::shared_ptr<SprmIdToString> Pointer_t;

    static Pointer_t pInstance;

    map<sal_uInt32, string> mMap;

protected:
    /**
       Generated automatically.
    */
    SprmIdToString();

public:
    static Pointer_t Instance();
    string operator()(sal_uInt32 nId);
};

::doctok::Reference<Properties>::Pointer_t createSprmProps
(WW8PropertyImpl & rProp);
::doctok::Reference<BinaryObj>::Pointer_t createSprmBinary
(WW8PropertyImpl & rProp);
}

#endif // INCLUDED_WW8_PROPERTY_SET_IMPL_HXX
