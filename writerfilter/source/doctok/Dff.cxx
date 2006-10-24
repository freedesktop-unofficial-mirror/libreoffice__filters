#include "Dff.hxx"
#include <doctok/resourceids.hxx>
#include "resources.hxx"

namespace doctok {

DffRecord::DffRecord(WW8Stream & rStream, sal_uInt32 nOffset, 
                     sal_uInt32 nCount)
: WW8StructBase(rStream, nOffset, nCount), bInitialized(false)
{
}

DffRecord::DffRecord(WW8StructBase * pParent, sal_uInt32 nOffset, 
                     sal_uInt32 nCount)
: WW8StructBase(pParent, nOffset, nCount), bInitialized(false)
{
}

Records_t::iterator DffRecord::begin()
{
    if (! bInitialized)
        initChildren();

    return mRecords.begin();
}

Records_t::iterator DffRecord::end()
{
    if (! bInitialized)
        initChildren();

    return mRecords.end();
}

bool DffRecord::isContainer() const
{
    return getVersion() == 0xf;
}

sal_uInt32 DffRecord::calcSize() const
{
    sal_uInt32 nResult = 0;

    switch (getRecordType())
    {
    case 0xf000:
    case 0xf001:
    case 0xf002:
    case 0xf003:
    case 0xf004:
        nResult = getU32(0x4) + 8;
        
        break;
    case 0xf700:
        nResult = 8;

        break;
    default:
        nResult = getU32(0x4);

        if (! isContainer())
            nResult += 8;
        break;
    }

    return nResult;
}

sal_uInt32 DffRecord::getVersion() const
{
    return getU8(0x0) & 0xf;
}

sal_uInt32 DffRecord::getInstance() const
{
    return (getU16(0x0) & 0xfff0) >> 4;
}

sal_uInt32 DffRecord::getRecordType() const
{
    return getU16(0x2);
}

void DffRecord::initChildren()
{
    if (isContainer())
    {
        sal_uInt32 nOffset = 8;
        sal_uInt32 nCount = calcSize();
        
        while (nCount - nOffset >= 8)
        {
            sal_uInt32 nSize = 0;
            boost::shared_ptr<DffRecord> pRec
                (createDffRecord(this, nOffset, &nSize));
            
            mRecords.push_back(pRec);
            
            nOffset += nSize;
        }
    }

    bInitialized = true;
}

Records_t DffRecord::findRecords(sal_uInt32 nType, bool bRecursive, bool bAny)
{
    Records_t aResult;

    findRecords(nType, aResult, bRecursive, bAny);

    return aResult;
}

void DffRecord::findRecords
(sal_uInt32 nType, Records_t & rRecords, bool bRecursive, bool bAny)
{
    Records_t::iterator aIt = begin();

    while (aIt != end())
    {
        Pointer_t pPointer = *aIt;
        if (bAny || pPointer->getRecordType() == nType) 
            rRecords.push_back(pPointer);

        if (bRecursive)
            pPointer->findRecords(nType, rRecords, bRecursive, 
                                      bAny);

        ++aIt;
    }
}

void DffRecord::resolveChildren(Properties & rHandler)
{
    Records_t::iterator aIt;
    for (aIt = begin(); aIt != end(); ++aIt)
    {
        rHandler.sprm(**aIt);
    }
}

void DffRecord::resolveLocal(Properties &)
{
}

void DffRecord::resolve(Properties & rHandler)
{
    WW8Value::Pointer_t pVal = createValue(getRecordType());
    rHandler.attribute(NS_rtf::LN_dfftype, *pVal);

    pVal = createValue(getInstance());
    rHandler.attribute(NS_rtf::LN_dffinstance, *pVal);

    pVal = createValue(getVersion());
    rHandler.attribute(NS_rtf::LN_dffversion, *pVal);
        
    if (isContainer())
    {
        resolveChildren(rHandler);
    }
    else
    {
        resolveLocal(rHandler);
    }
}

string DffRecord::getType() const
{
    return "DffRecord";
}

Value::Pointer_t DffRecord::getValue()
{
    return Value::Pointer_t();
}

doctok::Reference<BinaryObj>::Pointer_t DffRecord::getBinary()
{
    return doctok::Reference<BinaryObj>::Pointer_t();
}

doctok::Reference<Stream>::Pointer_t DffRecord::getStream()
{
    return doctok::Reference<Stream>::Pointer_t();
}

doctok::Reference<Properties>::Pointer_t DffRecord::getProps()
{
    return doctok::Reference<Properties>::Pointer_t(this->clone());
}

string DffRecord::toString() const
{
    char sBuffer[1024];

    snprintf(sBuffer, sizeof(sBuffer), 
             "<dffrecord type=\"%lx\" instance=\"%lx\" version=\"%lx\">\n",
             getRecordType(), getInstance(), getVersion());
    string aResult = sBuffer;
   

    if (!isContainer())
        aResult += mSequence.toString();
    else
    {
        WW8StructBase::Sequence aSeq(mSequence, 0, 8);
        aResult += aSeq.toString();
    }

    aResult += "</dffrecord>";

    return aResult;
}

string DffRecord::getName() const
{
    return "";
}

DffBlock::DffBlock(WW8Stream & rStream, sal_uInt32 nOffset, 
                   sal_uInt32 nCount, sal_uInt32 nPadding)
: WW8StructBase(rStream, nOffset, nCount), bInitialized(false),
  mnPadding(nPadding)
{
}

DffBlock::DffBlock(WW8StructBase * pParent, sal_uInt32 nOffset, 
                   sal_uInt32 nCount, sal_uInt32 nPadding)
: WW8StructBase(pParent, nOffset, nCount), bInitialized(false), 
  mnPadding(nPadding)
{
}

DffBlock::DffBlock(const DffBlock & rSrc)
: WW8StructBase(rSrc), doctok::Reference<Properties>(rSrc), 
  bInitialized(false), mnPadding(rSrc.mnPadding)
{
}

void DffBlock::initChildren()
{
    sal_uInt32 nOffset = 0;
    sal_uInt32 nCount = getCount();
    
    while (nOffset < nCount)
    {
        sal_uInt32 nSize = 0;
        DffRecord::Pointer_t pDffRecord
            (createDffRecord(this, nOffset, &nSize));

        mRecords.push_back(pDffRecord);
        
        nOffset +=  nSize + mnPadding;
    }    

    bInitialized = true;
}

Records_t DffBlock::findRecords(sal_uInt32 nType, bool bRecursive, bool bAny)
{
    Records_t aResult;

    findRecords(nType, aResult, bRecursive, bAny);

    return aResult;
}

void DffBlock::findRecords
(sal_uInt32 nType, Records_t & rRecords, bool bRecursive, bool bAny)
{
    Records_t::iterator aIt = begin();

    while (aIt != end())
    {
        DffRecord::Pointer_t pPointer(*aIt);

        if (bAny || pPointer->getRecordType() == nType)
            rRecords.push_back(pPointer);

        if (bRecursive)
            pPointer->findRecords(nType, rRecords, bRecursive, 
                                  bAny);
        
        ++aIt;
    }
}

void DffBlock::resolve(Properties & rHandler)
{
    Records_t::iterator aIt;

    for (aIt = begin(); aIt != end(); ++aIt)
    {
        DffRecord * pDff = aIt->get();
        rHandler.sprm(*pDff);
    }
}

DffRecord::Pointer_t DffBlock::getShape(sal_uInt32 nSpid)
{
    DffRecord::Pointer_t pResult;

    Records_t aRecords = findRecords(0xf004);
    Records_t::iterator aIt;
    for (aIt = aRecords.begin(); aIt != aRecords.end(); ++aIt)
    {
        DffRecord::Pointer_t pPointer = *aIt;

        Records_t aFSPs = pPointer->findRecords(0xf00a);
        Records_t::iterator aItFSP = aFSPs.begin();
        
        if (aItFSP != aFSPs.end())
        {
            DffFSP * pFSP = dynamic_cast<DffFSP *>((*aItFSP).get());

            if (pFSP->get_shpid() == nSpid)
            {
                pResult = pPointer;

                break;
            }
        }
    }

    return pResult;
}

Records_t::iterator DffBlock::begin()
{
    if (! bInitialized)
        initChildren();

    return mRecords.begin();
}

Records_t::iterator DffBlock::end()
{
    if (! bInitialized)
        initChildren();

    return mRecords.end();
}

string DffBlock::getType() const
{
    return "DffBlock";
}

}
