/* -*- Mode: C++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */
#include "ConversionHelper.hxx"
#include "GraphicHelpers.hxx"

#include <ooxml/resourceids.hxx>

#include <com/sun/star/text/HoriOrientation.hpp>
#include <com/sun/star/text/VertOrientation.hpp>
#include <com/sun/star/text/RelOrientation.hpp>
#include <com/sun/star/text/WrapTextMode.hpp>

#include "dmapperLoggers.hxx"

#include <iostream>
using namespace std;

namespace writerfilter {
namespace dmapper {

using namespace com::sun::star;

int PositionHandler::savedPositionOffsetV = 0;
int PositionHandler::savedPositionOffsetH = 0;
int PositionHandler::savedAlignV = text::VertOrientation::NONE;
int PositionHandler::savedAlignH = text::HoriOrientation::NONE;

PositionHandler::PositionHandler( bool vertical ) :
LoggedProperties(dmapper_logger, "PositionHandler")
{
    m_nRelation = text::RelOrientation::FRAME;
    if( vertical )
    {
        m_nPosition = savedPositionOffsetV;
        m_nOrient = savedAlignV;
        savedPositionOffsetV = 0;
        savedAlignV = text::VertOrientation::NONE;
    }
    else
    {
        m_nPosition = savedPositionOffsetH;
        m_nOrient = savedAlignH;
        savedPositionOffsetH = 0;
        savedAlignH = text::HoriOrientation::NONE;
    }
}

PositionHandler::~PositionHandler( )
{
}

void PositionHandler::lcl_attribute( Id aName, Value& rVal )
{
    sal_Int32 nIntValue = rVal.getInt( );
    switch ( aName )
    {
        case NS_ooxml::LN_CT_PosV_relativeFrom:
            {
                // TODO There are some other unhandled values
                static Id pVertRelValues[] =
                {
                    NS_ooxml::LN_Value_wordprocessingDrawing_ST_RelFromV_margin,
                    NS_ooxml::LN_Value_wordprocessingDrawing_ST_RelFromV_page,
                    NS_ooxml::LN_Value_wordprocessingDrawing_ST_RelFromV_paragraph,
                    NS_ooxml::LN_Value_wordprocessingDrawing_ST_RelFromV_line
                };

                static sal_Int16 pVertRelations[] = 
                {
                    text::RelOrientation::PAGE_PRINT_AREA,
                    text::RelOrientation::PAGE_FRAME,
                    text::RelOrientation::FRAME,
                    text::RelOrientation::TEXT_LINE
                };
                
                for ( int i = 0; i < 4; i++ )
                {
                    if ( pVertRelValues[i] == sal_uInt32( nIntValue ) )
                        m_nRelation = pVertRelations[i];
                }
            }
            break;
        case NS_ooxml::LN_CT_PosH_relativeFrom:
            {
                // TODO There are some other unhandled values
                static Id pHoriRelValues[] =
                {
                    NS_ooxml::LN_Value_wordprocessingDrawing_ST_RelFromH_margin,
                    NS_ooxml::LN_Value_wordprocessingDrawing_ST_RelFromH_page,
                    NS_ooxml::LN_Value_wordprocessingDrawing_ST_RelFromH_column,
                    NS_ooxml::LN_Value_wordprocessingDrawing_ST_RelFromH_character
                };

                static sal_Int16 pHoriRelations[] = 
                {
                    text::RelOrientation::PAGE_PRINT_AREA,
                    text::RelOrientation::PAGE_FRAME,
                    text::RelOrientation::FRAME,
                    text::RelOrientation::CHAR,
                };
                
                for ( int i = 0; i < 4; i++ )
                {
                    if ( pHoriRelValues[i] == sal_uInt32( nIntValue ) )
                        m_nRelation = pHoriRelations[i];
                }
            }
            break;
        default:
#ifdef DEBUG_DOMAINMAPPER
            dmapper_logger->element("unhandled");
#endif
            break;
    }
}

void PositionHandler::lcl_sprm( Sprm& )
{
}

void PositionHandler::setPositionOffset(const ::rtl::OUString & sText, bool vertical)
{
    if( vertical )
        savedPositionOffsetV = ConversionHelper::convertEMUToMM100( sText.toInt32());
    else
        savedPositionOffsetH = ConversionHelper::convertEMUToMM100( sText.toInt32());
}

void PositionHandler::setAlignH(const ::rtl::OUString & sText)
{
    if( sText == rtl::OUString( RTL_CONSTASCII_USTRINGPARAM( "left" )))
        savedAlignH = text::HoriOrientation::LEFT;
    else if( sText == rtl::OUString( RTL_CONSTASCII_USTRINGPARAM( "right" )))
        savedAlignH = text::HoriOrientation::RIGHT;
    else if( sText == rtl::OUString( RTL_CONSTASCII_USTRINGPARAM( "center" )))
        savedAlignH = text::HoriOrientation::CENTER;
    else if( sText == rtl::OUString( RTL_CONSTASCII_USTRINGPARAM( "inside" )))
        savedAlignH = text::HoriOrientation::INSIDE;
    else if( sText == rtl::OUString( RTL_CONSTASCII_USTRINGPARAM( "outside" )))
        savedAlignH = text::HoriOrientation::OUTSIDE;
}

void PositionHandler::setAlignV(const ::rtl::OUString & sText)
{
    if( sText == rtl::OUString( RTL_CONSTASCII_USTRINGPARAM( "top" )))
        savedAlignV = text::VertOrientation::TOP;
    else if( sText == rtl::OUString( RTL_CONSTASCII_USTRINGPARAM( "bottom" )))
        savedAlignV = text::VertOrientation::BOTTOM;
    else if( sText == rtl::OUString( RTL_CONSTASCII_USTRINGPARAM( "center" )))
        savedAlignV = text::VertOrientation::CENTER;
    else if( sText == rtl::OUString( RTL_CONSTASCII_USTRINGPARAM( "inside" )))
        savedAlignV = text::VertOrientation::NONE;
    else if( sText == rtl::OUString( RTL_CONSTASCII_USTRINGPARAM( "outside" )))
        savedAlignV = text::VertOrientation::NONE;
}

WrapHandler::WrapHandler( ) :
LoggedProperties(dmapper_logger, "WrapHandler"),
    m_nType( 0 ),
    m_nSide( 0 )
{
}

WrapHandler::~WrapHandler( )
{
}

void WrapHandler::lcl_attribute( Id aName, Value& rVal )
{
    switch ( aName )
    {
        case NS_ooxml::LN_CT_Wrap_type:
            m_nType = sal_Int32( rVal.getInt( ) );
            break;
        case NS_ooxml::LN_CT_Wrap_side:
            m_nSide = sal_Int32( rVal.getInt( ) );
            break; 
        default:;
    }
}

void WrapHandler::lcl_sprm( Sprm& )
{
}

sal_Int32 WrapHandler::getWrapMode( )
{
    sal_Int32 nMode = com::sun::star::text::WrapTextMode_NONE;

    switch ( m_nType )
    {
        case NS_ooxml::LN_Value_vml_wordprocessingDrawing_ST_WrapType_square:
        case NS_ooxml::LN_Value_vml_wordprocessingDrawing_ST_WrapType_tight:
            {
                switch ( m_nSide )
                {
                    case NS_ooxml::LN_Value_vml_wordprocessingDrawing_ST_WrapSide_left:
                        nMode = com::sun::star::text::WrapTextMode_LEFT;
                        break;
                    case NS_ooxml::LN_Value_vml_wordprocessingDrawing_ST_WrapSide_right:
                        nMode = com::sun::star::text::WrapTextMode_RIGHT;
                        break;
                    default:
                        nMode = com::sun::star::text::WrapTextMode_PARALLEL;
                }
            }
            break;
        case NS_ooxml::LN_Value_vml_wordprocessingDrawing_ST_WrapType_through:
            nMode = com::sun::star::text::WrapTextMode_THROUGHT;
            break;
        case NS_ooxml::LN_Value_vml_wordprocessingDrawing_ST_WrapType_topAndBottom:
        case NS_ooxml::LN_Value_vml_wordprocessingDrawing_ST_WrapType_none:
        default:
            nMode = com::sun::star::text::WrapTextMode_NONE;
    }

    return nMode;
}

} }

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
