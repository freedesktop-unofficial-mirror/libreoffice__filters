#include <rtfdocumentimpl.hxx>
#include <rtftypes.hxx>
#include <rtfcontrolwords.hxx>
#include <rtfvalue.hxx>
#include <rtfsprm.hxx>
#include <doctok/sprmids.hxx>
#include <unotools/ucbstreamhelper.hxx>
#include <rtl/strbuf.hxx>
#include <rtl/ustrbuf.hxx>

using rtl::OString;
using rtl::OStringBuffer;
using rtl::OUString;
using rtl::OUStringBuffer;
using rtl::OUStringToOString;

namespace writerfilter {
namespace rtftok {

extern RTFSymbol aRTFControlWords[];
extern int nRTFControlWords;

RTFDocumentImpl::RTFDocumentImpl(uno::Reference<io::XInputStream> const& xInputStream)
    : m_nGroup(0),
    m_bSkipUnknown(false),
    m_pCurrentKeyword(0)
{
    OSL_ENSURE(xInputStream.is(), "no input stream");
    if (!xInputStream.is())
        throw uno::RuntimeException();
    m_pInStream = utl::UcbStreamHelper::CreateStream( xInputStream, sal_True );
}

RTFDocumentImpl::~RTFDocumentImpl()
{
}

SvStream& RTFDocumentImpl::Strm()
{
    return *m_pInStream;
}

Stream& RTFDocumentImpl::Mapper()
{
    return *m_pMapperStream;
}

void RTFDocumentImpl::resolve(Stream & rMapper)
{
    m_pMapperStream = &rMapper;
    switch (resolveParse())
    {
        case ERROR_OK:
            OSL_TRACE("%s: finished without errors", OSL_THIS_FUNC);
            break;
        case ERROR_GROUP_UNDER:
            OSL_TRACE("%s: unmatched '}'", OSL_THIS_FUNC);
            break;
        case ERROR_GROUP_OVER:
            OSL_TRACE("%s: unmatched '{'", OSL_THIS_FUNC);
            break;
        case ERROR_EOF:
            OSL_TRACE("%s: unexpected end of file", OSL_THIS_FUNC);
            break;
    }
}

int RTFDocumentImpl::resolveChars(char ch)
{
    OSL_TRACE("%s start", OSL_THIS_FUNC);
    OStringBuffer aBuf;

    if (m_aStates.top().nDestinationState == DESTINATION_SKIP)
        return 0;
    while(!Strm().IsEof() && ch != '{' && ch != '}' && ch != '\\')
    {
        if (ch != 0x0d && ch != 0x0a)
            aBuf.append(ch);
        Strm() >> ch;
    }
    if (!Strm().IsEof())
        Strm().SeekRel(-1);
    OString aStr = aBuf.makeStringAndClear();
    OSL_TRACE("%s: collected '%s'", OSL_THIS_FUNC, aStr.getStr());

    // TODO encoding handling
    OUString aOUStr(OStringToOUString(aStr, RTL_TEXTENCODING_UTF8));

    text(aOUStr);

    return 0;
}

void RTFDocumentImpl::text(OUString& rString)
{
    writerfilter::Reference<Properties>::Pointer_t const pProperties(new RTFReferenceProperties(m_aStates.top().aSprms));

    Mapper().startCharacterGroup();
    Mapper().props(pProperties);
    Mapper().utext(reinterpret_cast<sal_uInt8 const*>(rString.getStr()), rString.getLength());
    Mapper().endCharacterGroup();
}

int RTFDocumentImpl::dispatchDestination(RTFKeyword nKeyword, bool /*bParam*/, int /*nParam*/)
{
    switch (nKeyword)
    {
        case RTF_RTF:
            break;
        default:
            OSL_TRACE("%s: TODO handle destination '%s'", OSL_THIS_FUNC, m_pCurrentKeyword->getStr());
            // Make sure we skip destinations till we don't handle them
            m_aStates.top().nDestinationState = DESTINATION_SKIP;
            break;
    }

    return 0;
}

int RTFDocumentImpl::dispatchToggle(RTFKeyword nKeyword, bool bParam, int nParam)
{
    bool bOn = !bParam || nParam != 0;

    switch (nKeyword)
    {
        case RTF_B:
            m_aStates.top().aSprms[NS_sprm::LN_CFBold] = bOn;
            break;
        default:
            OSL_TRACE("%s: TODO handle toggle '%s'", OSL_THIS_FUNC, m_pCurrentKeyword->getStr());
            break;
    }

    return 0;
}

int RTFDocumentImpl::dispatchKeyword(OString& rKeyword, bool bParam, int nParam)
{
    if (m_aStates.top().nDestinationState == DESTINATION_SKIP)
        return 0;
    OSL_TRACE("%s: keyword '\\%s' with param? %d param val: '%d'", OSL_THIS_FUNC,
            rKeyword.getStr(), (bParam ? 1 : 0), (bParam ? nParam : 0));
    int i, ret;
    for (i = 0; i < nRTFControlWords; i++)
    {
        if (!strcmp(rKeyword.getStr(), aRTFControlWords[i].sKeyword))
            break;
    }
    if (i == nRTFControlWords)
    {
        OSL_TRACE("%s: unknown keyword '\\%s'", OSL_THIS_FUNC, rKeyword.getStr());
        if (m_bSkipUnknown)
        {
            m_aStates.top().nDestinationState = DESTINATION_SKIP;
            m_bSkipUnknown = false;
        }
        return 0;
    }

    // known keyword, shoult not be skipped, even if starts with \*
    m_bSkipUnknown = false;

    m_pCurrentKeyword = &rKeyword;
    switch (aRTFControlWords[i].nControlType)
    {
        case CONTROL_FLAG:
            OSL_TRACE("%s: TODO handle flag '%s'", OSL_THIS_FUNC, rKeyword.getStr());
            break;
        case CONTROL_DESTINATION:
            if ((ret = dispatchDestination(aRTFControlWords[i].nIndex, bParam, nParam)))
                return ret;
            break;
        case CONTROL_SYMBOL:
            switch (aRTFControlWords[i].nIndex)
            {
                case RTF_IGNORE:
                    m_bSkipUnknown = true;
                    break;
                case RTF_PAR:
                    {
                        // end previous paragraph
                        OUString aStr = rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("\x0d"));
                        text(aStr);
                        Mapper().endParagraphGroup();
                        // start new one
                        Mapper().startParagraphGroup();
                    }
                    break;
                default:
                    OSL_TRACE("%s: TODO handle symbol '%s'", OSL_THIS_FUNC, rKeyword.getStr());
                    break;
            }
            break;
        case CONTROL_TOGGLE:
            if ((ret = dispatchToggle(aRTFControlWords[i].nIndex, bParam, nParam)))
                return ret;
            break;
        case CONTROL_VALUE:
            OSL_TRACE("%s: TODO handle value '%s'", OSL_THIS_FUNC, rKeyword.getStr());
            break;
    }

    return 0;
}

int RTFDocumentImpl::resolveKeyword()
{
    OSL_TRACE("%s", OSL_THIS_FUNC);
    char ch;
    OStringBuffer aBuf;
    bool bNeg = false;
    bool bParam = false;
    int nParam = 0;

    Strm() >> ch;
    if (Strm().IsEof())
        return ERROR_EOF;

    if (!isalpha(ch))
    {
        aBuf.append(ch);
        OString aKeyword = aBuf.makeStringAndClear();
        // control symbols aren't followed by a space, so we can return here
        // without doing any SeekRel()
        return dispatchKeyword(aKeyword, bParam, nParam);
    }
    while(isalpha(ch))
    {
        aBuf.append(ch);
        Strm() >> ch;
    }

    if (ch == '-')
    {
        // in case we'll have a parameter, that will be negative
        bNeg = true;
        Strm() >> ch;
        if (Strm().IsEof())
            return ERROR_EOF;
    }
    if (isdigit(ch))
    {
        OStringBuffer aParameter;

        // we have a parameter
        bParam = true;
        while(isdigit(ch))
        {
            aParameter.append(ch);
            Strm() >> ch;
        }
        nParam = aParameter.makeStringAndClear().toInt32();
        if (bNeg)
            nParam = -nParam;
    }
    if (ch != ' ')
        Strm().SeekRel(-1);
    OString aKeyword = aBuf.makeStringAndClear();
    return dispatchKeyword(aKeyword, bParam, nParam);
}

int RTFDocumentImpl::pushState()
{
    OSL_TRACE("%s before push: %d", OSL_THIS_FUNC, m_nGroup);

    RTFParserState aState;
    if (!m_aStates.empty())
    {
        aState = m_aStates.top();
    }
    m_aStates.push(aState);

    m_nGroup++;

    return 0;
}

int RTFDocumentImpl::popState()
{
    OSL_TRACE("%s before pop: m_nGroup %d, dest state: %d", OSL_THIS_FUNC, m_nGroup, m_aStates.top().nDestinationState);

    m_aStates.pop();

    m_nGroup--;

    if (!m_aStates.empty())
        OSL_TRACE("%s after pop: m_nGroup %d, dest state: %d", OSL_THIS_FUNC, m_nGroup, m_aStates.top().nDestinationState);
    return 0;
}

int RTFDocumentImpl::resolveParse()
{
    OSL_TRACE("%s", OSL_THIS_FUNC);
    char ch;
    int ret;

    // start initial paragraph
    Mapper().startParagraphGroup();

    while ((Strm() >> ch, !Strm().IsEof()))
    {
        OSL_TRACE("%s: parsing character '%c'", OSL_THIS_FUNC, ch);

        if (m_nGroup < 0)
            return ERROR_GROUP_UNDER;
        if (!m_aStates.empty() && m_aStates.top().nInternalState == INTERNAL_BIN)
        {
            OSL_TRACE("%s: TODO, binary internal state", OSL_THIS_FUNC);
        }
        else
        {
            switch (ch)
            {
                case '{':
                    if ((ret = pushState()))
                        return ret;
                    break;
                case '}':
                    if ((ret = popState()))
                        return ret;
                    break;
                case '\\':
                    if ((ret = resolveKeyword()))
                        return ret;
                    break;
                case 0x0d:
                case 0x0a:
                    break; // ignore these
                default:
                    if (m_aStates.top().nInternalState == INTERNAL_NORMAL)
                    {
                        if ((ret = resolveChars(ch)))
                            return ret;
                    }
                    else
                    {
                        OSL_TRACE("%s: TODO, hex internal state", OSL_THIS_FUNC);
                    }
                    break;
            }
        }
    }

    if (m_nGroup < 0)
        return ERROR_GROUP_UNDER;
    else if (m_nGroup > 0)
        return ERROR_GROUP_OVER;
    return 0;
}

::std::string RTFDocumentImpl::getType() const
{
    return "RTFDocumentImpl";
}

RTFParserState::RTFParserState()
    : nInternalState(INTERNAL_NORMAL),
    nDestinationState(DESTINATION_NORMAL),
    aSprms()
{
}

RTFReferenceProperties::RTFReferenceProperties(std::map<int, int> rSprms)
    : m_rSprms(rSprms)
{
}

RTFReferenceProperties::~RTFReferenceProperties()
{
}

void RTFReferenceProperties::resolve(Properties& rHandler)
{
    for (std::map<int, int>::const_iterator i = m_rSprms.begin(); i != m_rSprms.end(); ++i)
    {
        RTFValue::Pointer_t pValue(new RTFValue(i->second));
        RTFSprm aSprm(i->first, pValue);
        rHandler.sprm(aSprm);
    }
}

std::string RTFReferenceProperties::getType() const
{
    return "RTFReferenceProperties";
}

} // namespace rtftok
} // namespace writerfilter

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
