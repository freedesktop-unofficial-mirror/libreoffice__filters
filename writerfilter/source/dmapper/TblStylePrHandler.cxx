#include <TblStylePrHandler.hxx>
#include <PropertyMap.hxx>
#include <ooxml/resourceids.hxx>
#include <dmapperLoggers.hxx>
#ifdef DEBUG_DMAPPER_TBL_STYLE_HANDLER
#include <resourcemodel/QNameToString.hxx>
#endif

#include "dmapperLoggers.hxx"

namespace writerfilter {
namespace dmapper {

TblStylePrHandler::TblStylePrHandler( DomainMapper & rDMapper ) :
LoggedProperties(dmapper_logger, "TblStylePrHandler"),
m_rDMapper( rDMapper ), 
m_pTablePropsHandler( new TablePropertiesHandler( true ) ),
m_nType( TBL_STYLE_UNKNOWN ),
m_pProperties( new PropertyMap )
{
}

TblStylePrHandler::~TblStylePrHandler( )
{
    delete m_pTablePropsHandler, m_pTablePropsHandler = NULL;
}

void TblStylePrHandler::lcl_attribute(Id rName, Value & rVal)
{
#ifdef DEBUG_DMAPPER_TBL_STYLE_HANDLER
    dmapper_logger->startElement("TblStylePrHandler.attribute");
    dmapper_logger->attribute("name", (*QNameToString::Instance())(rName));
    dmapper_logger->chars(rVal.toString());
    dmapper_logger->endElement("TblStylePrHandler.attribute");
#endif

    switch ( rName )
    {
        case NS_ooxml::LN_CT_TblStyleOverrideType:
            {
                // The tokenid should be the same in the model.xml than
                // in the TblStyleType enum
                m_nType = TblStyleType( rVal.getInt( ) );
            }
            break;
    }
}

void TblStylePrHandler::lcl_sprm(Sprm & rSprm)
{
#ifdef DEBUG_DMAPPER_TBL_STYLE_HANDLER
    dmapper_logger->startElement("TblStylePrHandler.sprm");
    dmapper_logger->attribute("sprm", rSprm.toString());
#endif

    Value::Pointer_t pValue = rSprm.getValue();
    switch ( rSprm.getId( ) )
    {
        case NS_ooxml::LN_CT_PPrBase:
        case NS_ooxml::LN_EG_RPrBase:
        case NS_ooxml::LN_CT_TblPrBase:
        case NS_ooxml::LN_CT_TrPrBase: 
        case NS_ooxml::LN_CT_TcPrBase:
            resolveSprmProps( rSprm );
            break;
        default:
            // Tables specific properties have to handled here
            m_pTablePropsHandler->SetProperties( m_pProperties );
            bool bRet = m_pTablePropsHandler->sprm( rSprm );

            if ( !bRet )
            {
                // The DomainMapper can handle some of the properties
                m_rDMapper.PushStyleSheetProperties( m_pProperties, true );
                m_rDMapper.sprm( rSprm );
                m_rDMapper.PopStyleSheetProperties( true );
            }
    }
    
#ifdef DEBUG_DMAPPER_TBL_STYLE_HANDLER
    dmapper_logger->endElement("TblStylePrHandler.sprm");
#endif
}

void TblStylePrHandler::resolveSprmProps(Sprm & rSprm)
{
    writerfilter::Reference<Properties>::Pointer_t pProperties = rSprm.getProps();
    if( pProperties.get())
        pProperties->resolve(*this);
}

}}
