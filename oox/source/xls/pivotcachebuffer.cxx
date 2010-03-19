/*************************************************************************
 *
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER.
 *
 * Copyright 2000, 2010 Oracle and/or its affiliates.
 *
 * OpenOffice.org - a multi-platform office productivity suite
 *
 * This file is part of OpenOffice.org.
 *
 * OpenOffice.org is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License version 3
 * only, as published by the Free Software Foundation.
 *
 * OpenOffice.org is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License version 3 for more details
 * (a copy is included in the LICENSE file that accompanied this code).
 *
 * You should have received a copy of the GNU Lesser General Public License
 * version 3 along with OpenOffice.org.  If not, see
 * <http://www.openoffice.org/license.html>
 * for a copy of the LGPLv3 License.
 *
 ************************************************************************/

#include "oox/xls/pivotcachebuffer.hxx"
#include <set>
#include <rtl/ustrbuf.hxx>
#include <com/sun/star/container/XIndexAccess.hpp>
#include <com/sun/star/container/XNameAccess.hpp>
#include <com/sun/star/container/XNamed.hpp>
#include <com/sun/star/table/XCell.hpp>
#include <com/sun/star/sheet/DataPilotFieldGroupBy.hpp>
#include <com/sun/star/sheet/DataPilotFieldGroupInfo.hpp>
#include <com/sun/star/sheet/XDataPilotFieldGrouping.hpp>
#include "properties.hxx"
#include "oox/helper/attributelist.hxx"
#include "oox/helper/propertyset.hxx"
#include "oox/helper/recordinputstream.hxx"
#include "oox/core/filterbase.hxx"
#include "oox/xls/biffinputstream.hxx"
#include "oox/xls/defnamesbuffer.hxx"
#include "oox/xls/excelhandlers.hxx"
#include "oox/xls/pivotcachefragment.hxx"
#include "oox/xls/tablebuffer.hxx"
#include "oox/xls/unitconverter.hxx"
#include "oox/xls/worksheetbuffer.hxx"

using ::rtl::OUString;
using ::rtl::OUStringBuffer;
using ::com::sun::star::uno::Any;
using ::com::sun::star::uno::Exception;
using ::com::sun::star::uno::Reference;
using ::com::sun::star::uno::UNO_QUERY;
using ::com::sun::star::uno::UNO_QUERY_THROW;
using ::com::sun::star::container::XIndexAccess;
using ::com::sun::star::container::XNameAccess;
using ::com::sun::star::container::XNamed;
using ::com::sun::star::util::DateTime;
using ::com::sun::star::table::CellAddress;
using ::com::sun::star::sheet::DataPilotFieldGroupInfo;
using ::com::sun::star::table::XCell;
using ::com::sun::star::sheet::XDataPilotField;
using ::com::sun::star::sheet::XDataPilotFieldGrouping;
using ::oox::core::Relations;

namespace oox {
namespace xls {

// ============================================================================

namespace {

const sal_uInt16 OOBIN_PCDFIELD_SERVERFIELD         = 0x0001;
const sal_uInt16 OOBIN_PCDFIELD_NOUNIQUEITEMS       = 0x0002;
const sal_uInt16 OOBIN_PCDFIELD_DATABASEFIELD       = 0x0004;
const sal_uInt16 OOBIN_PCDFIELD_HASCAPTION          = 0x0008;
const sal_uInt16 OOBIN_PCDFIELD_MEMBERPROPFIELD     = 0x0010;
const sal_uInt16 OOBIN_PCDFIELD_HASFORMULA          = 0x0100;
const sal_uInt16 OOBIN_PCDFIELD_HASPROPERTYNAME     = 0x0200;

const sal_uInt16 OOBIN_PCDFSITEMS_HASSEMIMIXED      = 0x0001;
const sal_uInt16 OOBIN_PCDFSITEMS_HASNONDATE        = 0x0002;
const sal_uInt16 OOBIN_PCDFSITEMS_HASDATE           = 0x0004;
const sal_uInt16 OOBIN_PCDFSITEMS_HASSTRING         = 0x0008;
const sal_uInt16 OOBIN_PCDFSITEMS_HASBLANK          = 0x0010;
const sal_uInt16 OOBIN_PCDFSITEMS_HASMIXED          = 0x0020;
const sal_uInt16 OOBIN_PCDFSITEMS_ISNUMERIC         = 0x0040;
const sal_uInt16 OOBIN_PCDFSITEMS_ISINTEGER         = 0x0080;
const sal_uInt16 OOBIN_PCDFSITEMS_HASMINMAX         = 0x0100;
const sal_uInt16 OOBIN_PCDFSITEMS_HASLONGTEXT       = 0x0200;

const sal_uInt16 OOBIN_PCITEM_ARRAY_DOUBLE          = 0x0001;
const sal_uInt16 OOBIN_PCITEM_ARRAY_STRING          = 0x0002;
const sal_uInt16 OOBIN_PCITEM_ARRAY_ERROR           = 0x0010;
const sal_uInt16 OOBIN_PCITEM_ARRAY_DATE            = 0x0020;

const sal_uInt8 OOBIN_PCDFRANGEPR_AUTOSTART         = 0x01;
const sal_uInt8 OOBIN_PCDFRANGEPR_AUTOEND           = 0x02;
const sal_uInt8 OOBIN_PCDFRANGEPR_DATEGROUP         = 0x04;

const sal_uInt8 OOBIN_PCDEFINITION_SAVEDATA         = 0x01;
const sal_uInt8 OOBIN_PCDEFINITION_INVALID          = 0x02;
const sal_uInt8 OOBIN_PCDEFINITION_REFRESHONLOAD    = 0x04;
const sal_uInt8 OOBIN_PCDEFINITION_OPTIMIZEMEMORY   = 0x08;
const sal_uInt8 OOBIN_PCDEFINITION_ENABLEREFRESH    = 0x10;
const sal_uInt8 OOBIN_PCDEFINITION_BACKGROUNDQUERY  = 0x20;
const sal_uInt8 OOBIN_PCDEFINITION_UPGRADEONREFR    = 0x40;
const sal_uInt8 OOBIN_PCDEFINITION_TUPELCACHE       = 0x80;

const sal_uInt8 OOBIN_PCDEFINITION_HASUSERNAME      = 0x01;
const sal_uInt8 OOBIN_PCDEFINITION_HASRELID         = 0x02;
const sal_uInt8 OOBIN_PCDEFINITION_SUPPORTSUBQUERY  = 0x04;
const sal_uInt8 OOBIN_PCDEFINITION_SUPPORTDRILL     = 0x08;

const sal_uInt8 OOBIN_PCDWBSOURCE_HASRELID          = 0x01;
const sal_uInt8 OOBIN_PCDWBSOURCE_HASSHEET          = 0x02;

const sal_uInt16 BIFF_PCDSOURCE_WORKSHEET           = 0x0001;
const sal_uInt16 BIFF_PCDSOURCE_EXTERNAL            = 0x0002;
const sal_uInt16 BIFF_PCDSOURCE_CONSOLIDATION       = 0x0004;
const sal_uInt16 BIFF_PCDSOURCE_SCENARIO            = 0x0010;

const sal_uInt16 BIFF_PC_NOSTRING                   = 0xFFFF;

const sal_uInt16 BIFF_PCDFIELD_HASITEMS             = 0x0001;
const sal_uInt16 BIFF_PCDFIELD_HASUNSHAREDITEMS     = 0x0002;
const sal_uInt16 BIFF_PCDFIELD_CALCULATED           = 0x0004;
const sal_uInt16 BIFF_PCDFIELD_HASPARENT            = 0x0008;
const sal_uInt16 BIFF_PCDFIELD_RANGEGROUP           = 0x0010;
const sal_uInt16 BIFF_PCDFIELD_ISNUMERIC            = 0x0020;
const sal_uInt16 BIFF_PCDFIELD_HASSEMIMIXED         = 0x0080;
const sal_uInt16 BIFF_PCDFIELD_HASMINMAX            = 0x0100;
const sal_uInt16 BIFF_PCDFIELD_HASLONGINDEX         = 0x0200;
const sal_uInt16 BIFF_PCDFIELD_HASNONDATE           = 0x0400;
const sal_uInt16 BIFF_PCDFIELD_HASDATE              = 0x0800;
const sal_uInt16 BIFF_PCDFIELD_SERVERFIELD          = 0x2000;
const sal_uInt16 BIFF_PCDFIELD_NOUNIQUEITEMS        = 0x4000;

const sal_uInt16 BIFF_PCDFRANGEPR_AUTOSTART         = 0x0001;
const sal_uInt16 BIFF_PCDFRANGEPR_AUTOEND           = 0x0002;

const sal_uInt16 BIFF_PCDEFINITION_SAVEDATA         = 0x0001;
const sal_uInt16 BIFF_PCDEFINITION_INVALID          = 0x0002;
const sal_uInt16 BIFF_PCDEFINITION_REFRESHONLOAD    = 0x0004;
const sal_uInt16 BIFF_PCDEFINITION_OPTIMIZEMEMORY   = 0x0008;
const sal_uInt16 BIFF_PCDEFINITION_BACKGROUNDQUERY  = 0x0010;
const sal_uInt16 BIFF_PCDEFINITION_ENABLEREFRESH    = 0x0020;

// ----------------------------------------------------------------------------

/** Adjusts the weird date format read from binary streams.

    Dates before 1900-Mar-01 are stored including the non-existing leap day
    1900-02-29. Time values (without date) are stored as times of day
    1900-Jan-00. Nothing has to be done when the workbook is stored in 1904
    date mode (dates before 1904-Jan-01 will not occur in this case).
 */
void lclAdjustBinDateTime( DateTime& orDateTime )
{
    if( (orDateTime.Year == 1900) && (orDateTime.Month <= 2) )
    {
        OSL_ENSURE( (orDateTime.Month == 1) || ((orDateTime.Month == 2) && (orDateTime.Day > 0)), "lclAdjustBinDateTime - invalid date" );
        switch( orDateTime.Month )
        {
            case 2: if( orDateTime.Day > 1 ) --orDateTime.Day; else { orDateTime.Day += 30; --orDateTime.Month; }                       break;
            case 1: if( orDateTime.Day > 1 ) --orDateTime.Day; else { orDateTime.Day += 30; orDateTime.Month = 12; --orDateTime.Year; } break;
        }
    }
}

} // namespace

// ============================================================================

PivotCacheItem::PivotCacheItem() :
    mnType( XML_m )
{
}

void PivotCacheItem::readString( const AttributeList& rAttribs )
{
    maValue <<= rAttribs.getXString( XML_v, OUString() );
    mnType = XML_s;
}

void PivotCacheItem::readNumeric( const AttributeList& rAttribs )
{
    maValue <<= rAttribs.getDouble( XML_v, 0.0 );
    mnType = XML_n;
}

void PivotCacheItem::readDate( const AttributeList& rAttribs )
{
    maValue <<= rAttribs.getDateTime( XML_v, DateTime() );
    mnType = XML_d;
}

void PivotCacheItem::readBool( const AttributeList& rAttribs )
{
    maValue <<= rAttribs.getBool( XML_v, false );
    mnType = XML_b;
}

void PivotCacheItem::readError( const AttributeList& rAttribs, const UnitConverter& rUnitConverter )
{
    maValue <<= static_cast< sal_Int32 >( rUnitConverter.calcBiffErrorCode( rAttribs.getXString( XML_v, OUString() ) ) );
    mnType = XML_e;
}

void PivotCacheItem::readIndex( const AttributeList& rAttribs )
{
    maValue <<= rAttribs.getInteger( XML_v, -1 );
    mnType = XML_x;
}

void PivotCacheItem::readString( RecordInputStream& rStrm )
{
    maValue <<= rStrm.readString();
    mnType = XML_s;
}

void PivotCacheItem::readDouble( RecordInputStream& rStrm )
{
    maValue <<= rStrm.readDouble();
    mnType = XML_n;
}

void PivotCacheItem::readDate( RecordInputStream& rStrm )
{
    DateTime aDateTime;
    aDateTime.Year = rStrm.readuInt16();
    aDateTime.Month = rStrm.readuInt16();
    aDateTime.Day = rStrm.readuInt8();
    aDateTime.Hours = rStrm.readuInt8();
    aDateTime.Minutes = rStrm.readuInt8();
    aDateTime.Seconds = rStrm.readuInt8();
    lclAdjustBinDateTime( aDateTime );
    maValue <<= aDateTime;
    mnType = XML_d;
}

void PivotCacheItem::readBool( RecordInputStream& rStrm )
{
    maValue <<= (rStrm.readuInt8() != 0);
    mnType = XML_b;
}

void PivotCacheItem::readError( RecordInputStream& rStrm )
{
    maValue <<= static_cast< sal_Int32 >( rStrm.readuInt8() );
    mnType = XML_e;
}

void PivotCacheItem::readIndex( RecordInputStream& rStrm )
{
    maValue <<= rStrm.readInt32();
    mnType = XML_x;
}

void PivotCacheItem::readString( BiffInputStream& rStrm, const WorkbookHelper& rHelper )
{
    maValue <<= (rHelper.getBiff() == BIFF8) ? rStrm.readUniString() : rStrm.readByteStringUC( true, rHelper.getTextEncoding() );
    mnType = XML_s;
}

void PivotCacheItem::readDouble( BiffInputStream& rStrm )
{
    maValue <<= rStrm.readDouble();
    mnType = XML_n;
}

void PivotCacheItem::readInteger( BiffInputStream& rStrm )
{
    maValue <<= rStrm.readInt16();
    mnType = XML_i;                 // fake, used for BIFF only
}

void PivotCacheItem::readDate( BiffInputStream& rStrm )
{
    DateTime aDateTime;
    aDateTime.Year = rStrm.readuInt16();
    aDateTime.Month = rStrm.readuInt16();
    aDateTime.Day = rStrm.readuInt8();
    aDateTime.Hours = rStrm.readuInt8();
    aDateTime.Minutes = rStrm.readuInt8();
    aDateTime.Seconds = rStrm.readuInt8();
    lclAdjustBinDateTime( aDateTime );
    maValue <<= aDateTime;
    mnType = XML_d;
}

void PivotCacheItem::readBool( BiffInputStream& rStrm )
{
    maValue <<= (rStrm.readuInt8() != 0);
    mnType = XML_b;
}

void PivotCacheItem::readError( BiffInputStream& rStrm )
{
    maValue <<= static_cast< sal_Int32 >( rStrm.readuInt8() );
    mnType = XML_e;
}

OUString PivotCacheItem::getName() const
{
    switch( mnType )
    {
        case XML_m: return OUString();
        case XML_s: return maValue.get< OUString >();
        case XML_n: return OUString::valueOf( maValue.get< double >() );                            // !TODO
        case XML_i: return OUString::valueOf( maValue.get< sal_Int32 >() );
        case XML_d: return OUString();                                                              // !TODO
        case XML_b: return OUString::valueOf( static_cast< sal_Bool >( maValue.get< bool >() ) );   // !TODO
        case XML_e: return OUString();                                                              // !TODO
    }
    OSL_ENSURE( false, "PivotCacheItem::getName - invalid data type" );
    return OUString();
}

// ----------------------------------------------------------------------------

PivotCacheItemList::PivotCacheItemList( const WorkbookHelper& rHelper ) :
    WorkbookHelper( rHelper )
{
}

void PivotCacheItemList::importItem( sal_Int32 nElement, const AttributeList& rAttribs )
{
    PivotCacheItem& rItem = createItem();
    switch( nElement )
    {
        case XLS_TOKEN( m ):                                                        break;
        case XLS_TOKEN( s ):    rItem.readString( rAttribs );                       break;
        case XLS_TOKEN( n ):    rItem.readNumeric( rAttribs );                      break;
        case XLS_TOKEN( d ):    rItem.readDate( rAttribs );                         break;
        case XLS_TOKEN( b ):    rItem.readBool( rAttribs );                         break;
        case XLS_TOKEN( e ):    rItem.readError( rAttribs, getUnitConverter() );    break;
        default:    OSL_ENSURE( false, "PivotCacheItemList::importItem - unknown element type" );
    }
}

void PivotCacheItemList::importItem( sal_Int32 nRecId, RecordInputStream& rStrm )
{
    if( nRecId == OOBIN_ID_PCITEM_ARRAY )
    {
        importArray( rStrm );
        return;
    }

    PivotCacheItem& rItem = createItem();
    switch( nRecId )
    {
        case OOBIN_ID_PCITEM_MISSING:
        case OOBIN_ID_PCITEMA_MISSING:                              break;
        case OOBIN_ID_PCITEM_STRING:
        case OOBIN_ID_PCITEMA_STRING:   rItem.readString( rStrm );  break;
        case OOBIN_ID_PCITEM_DOUBLE:
        case OOBIN_ID_PCITEMA_DOUBLE:   rItem.readDouble( rStrm );  break;
        case OOBIN_ID_PCITEM_DATE:
        case OOBIN_ID_PCITEMA_DATE:     rItem.readDate( rStrm );    break;
        case OOBIN_ID_PCITEM_BOOL:
        case OOBIN_ID_PCITEMA_BOOL:     rItem.readBool( rStrm );    break;
        case OOBIN_ID_PCITEM_ERROR:
        case OOBIN_ID_PCITEMA_ERROR:    rItem.readError( rStrm );   break;
        default:    OSL_ENSURE( false, "PivotCacheItemList::importItem - unknown record type" );
    }
}

void PivotCacheItemList::importItemList( BiffInputStream& rStrm, sal_uInt16 nCount )
{
    bool bLoop = true;
    for( sal_uInt16 nItemIdx = 0; bLoop && (nItemIdx < nCount); ++nItemIdx )
    {
        bLoop = rStrm.startNextRecord();
        if( bLoop ) switch( rStrm.getRecId() )
        {
            case BIFF_ID_PCITEM_MISSING:    createItem();                               break;
            case BIFF_ID_PCITEM_STRING:     createItem().readString( rStrm, *this );    break;
            case BIFF_ID_PCITEM_DOUBLE:     createItem().readDouble( rStrm );           break;
            case BIFF_ID_PCITEM_INTEGER:    createItem().readInteger( rStrm );          break;
            case BIFF_ID_PCITEM_DATE:       createItem().readDate( rStrm );             break;
            case BIFF_ID_PCITEM_BOOL:       createItem().readBool( rStrm );             break;
            case BIFF_ID_PCITEM_ERROR:      createItem().readError( rStrm );            break;
            default:                        rStrm.rewindRecord(); bLoop = false;
        }
    }
    OSL_ENSURE( bLoop, "PivotCacheItemList::importItemList - could not read all cache item records" );
}

const PivotCacheItem* PivotCacheItemList::getCacheItem( sal_Int32 nItemIdx ) const
{
    return ContainerHelper::getVectorElement( maItems, nItemIdx );
}

void PivotCacheItemList::getCacheItemNames( ::std::vector< OUString >& orItemNames ) const
{
    orItemNames.clear();
    orItemNames.reserve( maItems.size() );
    for( CacheItemVector::const_iterator aIt = maItems.begin(), aEnd = maItems.end(); aIt != aEnd; ++aIt )
        orItemNames.push_back( aIt->getName() );
}

// private --------------------------------------------------------------------

PivotCacheItem& PivotCacheItemList::createItem()
{
    maItems.resize( maItems.size() + 1 );
    return maItems.back();
}

void PivotCacheItemList::importArray( RecordInputStream& rStrm )
{
    sal_uInt16 nType = rStrm.readuInt16();
    sal_Int32 nCount = rStrm.readInt32();
    for( sal_Int32 nIdx = 0; !rStrm.isEof() && (nIdx < nCount); ++nIdx )
    {
        switch( nType )
        {
            case OOBIN_PCITEM_ARRAY_DOUBLE: createItem().readDouble( rStrm );   break;
            case OOBIN_PCITEM_ARRAY_STRING: createItem().readString( rStrm );   break;
            case OOBIN_PCITEM_ARRAY_ERROR:  createItem().readError( rStrm );    break;
            case OOBIN_PCITEM_ARRAY_DATE:   createItem().readDate( rStrm );     break;
            default:
                OSL_ENSURE( false, "PivotCacheItemList::importArray - unknown data type" );
                nIdx = nCount;
        }
    }
}

// ============================================================================

PCFieldModel::PCFieldModel() :
    mnNumFmtId( 0 ),
    mnSqlType( 0 ),
    mnHierarchy( 0 ),
    mnLevel( 0 ),
    mnMappingCount( 0 ),
    mbDatabaseField( true ),
    mbServerField( false ),
    mbUniqueList( true ),
    mbMemberPropField( false )
{
}

// ----------------------------------------------------------------------------

PCSharedItemsModel::PCSharedItemsModel() :
    mbHasSemiMixed( true ),
    mbHasNonDate( true ),
    mbHasDate( false ),
    mbHasString( true ),
    mbHasBlank( false ),
    mbHasMixed( false ),
    mbIsNumeric( false ),
    mbIsInteger( false ),
    mbHasLongText( false ),
    mbHasLongIndexes( false )
{
}

// ----------------------------------------------------------------------------

PCFieldGroupModel::PCFieldGroupModel() :
    mfStartValue( 0.0 ),
    mfEndValue( 0.0 ),
    mfInterval( 1.0 ),
    mnParentField( -1 ),
    mnBaseField( -1 ),
    mnGroupBy( XML_range ),
    mbRangeGroup( false ),
    mbDateGroup( false ),
    mbAutoStart( true ),
    mbAutoEnd( true )
{
}

void PCFieldGroupModel::setBinGroupBy( sal_uInt8 nGroupBy )
{
    static const sal_Int32 spnGroupBy[] = { XML_range,
        XML_seconds, XML_minutes, XML_hours, XML_days, XML_months, XML_quarters, XML_years };
    mnGroupBy = STATIC_ARRAY_SELECT( spnGroupBy, nGroupBy, XML_range );
}

// ----------------------------------------------------------------------------

PivotCacheField::PivotCacheField( const WorkbookHelper& rHelper, bool bIsDatabaseField ) :
    WorkbookHelper( rHelper ),
    maSharedItems( rHelper ),
    maGroupItems( rHelper )
{
    maFieldModel.mbDatabaseField = bIsDatabaseField;
}

void PivotCacheField::importCacheField( const AttributeList& rAttribs )
{
    maFieldModel.maName            = rAttribs.getXString( XML_name, OUString() );
    maFieldModel.maCaption         = rAttribs.getXString( XML_caption, OUString() );
    maFieldModel.maPropertyName    = rAttribs.getXString( XML_propertyName, OUString() );
    maFieldModel.maFormula         = rAttribs.getXString( XML_formula, OUString() );
    maFieldModel.mnNumFmtId        = rAttribs.getInteger( XML_numFmtId, 0 );
    maFieldModel.mnSqlType         = rAttribs.getInteger( XML_sqlType, 0 );
    maFieldModel.mnHierarchy       = rAttribs.getInteger( XML_hierarchy, 0 );
    maFieldModel.mnLevel           = rAttribs.getInteger( XML_level, 0 );
    maFieldModel.mnMappingCount    = rAttribs.getInteger( XML_mappingCount, 0 );
    maFieldModel.mbDatabaseField   = rAttribs.getBool( XML_databaseField, true );
    maFieldModel.mbServerField     = rAttribs.getBool( XML_serverField, false );
    maFieldModel.mbUniqueList      = rAttribs.getBool( XML_uniqueList, true );
    maFieldModel.mbMemberPropField = rAttribs.getBool( XML_memberPropertyField, false );
}

void PivotCacheField::importSharedItems( const AttributeList& rAttribs )
{
    OSL_ENSURE( maSharedItems.empty(), "PivotCacheField::importSharedItems - multiple shared items elements" );
    maSharedItemsModel.mbHasSemiMixed = rAttribs.getBool( XML_containsSemiMixedTypes, true );
    maSharedItemsModel.mbHasNonDate   = rAttribs.getBool( XML_containsNonDate, true );
    maSharedItemsModel.mbHasDate      = rAttribs.getBool( XML_containsDate, false );
    maSharedItemsModel.mbHasString    = rAttribs.getBool( XML_containsString, true );
    maSharedItemsModel.mbHasBlank     = rAttribs.getBool( XML_containsBlank, false );
    maSharedItemsModel.mbHasMixed     = rAttribs.getBool( XML_containsMixedTypes, false );
    maSharedItemsModel.mbIsNumeric    = rAttribs.getBool( XML_containsNumber, false );
    maSharedItemsModel.mbIsInteger    = rAttribs.getBool( XML_containsInteger, false );
    maSharedItemsModel.mbHasLongText  = rAttribs.getBool( XML_longText, false );
}

void PivotCacheField::importSharedItem( sal_Int32 nElement, const AttributeList& rAttribs )
{
    maSharedItems.importItem( nElement, rAttribs );
}

void PivotCacheField::importFieldGroup( const AttributeList& rAttribs )
{
    maFieldGroupModel.mnParentField = rAttribs.getInteger( XML_par, -1 );
    maFieldGroupModel.mnBaseField   = rAttribs.getInteger( XML_base, -1 );
}

void PivotCacheField::importRangePr( const AttributeList& rAttribs )
{
    maFieldGroupModel.maStartDate    = rAttribs.getDateTime( XML_startDate, DateTime() );
    maFieldGroupModel.maEndDate      = rAttribs.getDateTime( XML_endDate, DateTime() );
    maFieldGroupModel.mfStartValue   = rAttribs.getDouble( XML_startNum, 0.0 );
    maFieldGroupModel.mfEndValue     = rAttribs.getDouble( XML_endNum, 0.0 );
    maFieldGroupModel.mfInterval     = rAttribs.getDouble( XML_groupInterval, 1.0 );
    maFieldGroupModel.mnGroupBy      = rAttribs.getToken( XML_groupBy, XML_range );
    maFieldGroupModel.mbRangeGroup   = true;
    maFieldGroupModel.mbDateGroup    = maFieldGroupModel.mnGroupBy != XML_range;
    maFieldGroupModel.mbAutoStart    = rAttribs.getBool( XML_autoStart, true );
    maFieldGroupModel.mbAutoEnd      = rAttribs.getBool( XML_autoEnd, true );
}

void PivotCacheField::importDiscretePrItem( sal_Int32 nElement, const AttributeList& rAttribs )
{
    OSL_ENSURE( nElement == XLS_TOKEN( x ), "PivotCacheField::importDiscretePrItem - unexpected element" );
    if( nElement == XLS_TOKEN( x ) )
        maDiscreteItems.push_back( rAttribs.getInteger( XML_v, -1 ) );
}

void PivotCacheField::importGroupItem( sal_Int32 nElement, const AttributeList& rAttribs )
{
    maGroupItems.importItem( nElement, rAttribs );
}

void PivotCacheField::importPCDField( RecordInputStream& rStrm )
{
    sal_uInt16 nFlags;
    rStrm >> nFlags >> maFieldModel.mnNumFmtId;
    maFieldModel.mnSqlType = rStrm.readInt16();
    rStrm >> maFieldModel.mnHierarchy >> maFieldModel.mnLevel >> maFieldModel.mnMappingCount >> maFieldModel.maName;
    if( getFlag( nFlags, OOBIN_PCDFIELD_HASCAPTION ) )
        rStrm >> maFieldModel.maCaption;
    if( getFlag( nFlags, OOBIN_PCDFIELD_HASFORMULA ) )
        rStrm.skip( ::std::max< sal_Int32 >( rStrm.readInt32(), 0 ) );
    if( maFieldModel.mnMappingCount > 0 )
        rStrm.skip( ::std::max< sal_Int32 >( rStrm.readInt32(), 0 ) );
    if( getFlag( nFlags, OOBIN_PCDFIELD_HASPROPERTYNAME ) )
        rStrm >> maFieldModel.maPropertyName;

    maFieldModel.mbDatabaseField   = getFlag( nFlags, OOBIN_PCDFIELD_DATABASEFIELD );
    maFieldModel.mbServerField     = getFlag( nFlags, OOBIN_PCDFIELD_SERVERFIELD );
    maFieldModel.mbUniqueList      = !getFlag( nFlags, OOBIN_PCDFIELD_NOUNIQUEITEMS );
    maFieldModel.mbMemberPropField = getFlag( nFlags, OOBIN_PCDFIELD_MEMBERPROPFIELD );
}

void PivotCacheField::importPCDFSharedItems( RecordInputStream& rStrm )
{
    sal_uInt16 nFlags;
    rStrm >> nFlags;
    maSharedItemsModel.mbHasSemiMixed = getFlag( nFlags, OOBIN_PCDFSITEMS_HASSEMIMIXED );
    maSharedItemsModel.mbHasNonDate   = getFlag( nFlags, OOBIN_PCDFSITEMS_HASNONDATE );
    maSharedItemsModel.mbHasDate      = getFlag( nFlags, OOBIN_PCDFSITEMS_HASDATE );
    maSharedItemsModel.mbHasString    = getFlag( nFlags, OOBIN_PCDFSITEMS_HASSTRING );
    maSharedItemsModel.mbHasBlank     = getFlag( nFlags, OOBIN_PCDFSITEMS_HASBLANK );
    maSharedItemsModel.mbHasMixed     = getFlag( nFlags, OOBIN_PCDFSITEMS_HASMIXED );
    maSharedItemsModel.mbIsNumeric    = getFlag( nFlags, OOBIN_PCDFSITEMS_ISNUMERIC );
    maSharedItemsModel.mbIsInteger    = getFlag( nFlags, OOBIN_PCDFSITEMS_ISINTEGER );
    maSharedItemsModel.mbHasLongText  = getFlag( nFlags, OOBIN_PCDFSITEMS_HASLONGTEXT );
}

void PivotCacheField::importPCDFSharedItem( sal_Int32 nRecId, RecordInputStream& rStrm )
{
    maSharedItems.importItem( nRecId, rStrm );
}

void PivotCacheField::importPCDFieldGroup( RecordInputStream& rStrm )
{
    rStrm >> maFieldGroupModel.mnParentField >> maFieldGroupModel.mnBaseField;
}

void PivotCacheField::importPCDFRangePr( RecordInputStream& rStrm )
{
    sal_uInt8 nGroupBy, nFlags;
    rStrm >> nGroupBy >> nFlags >> maFieldGroupModel.mfStartValue >> maFieldGroupModel.mfEndValue >> maFieldGroupModel.mfInterval;

    maFieldGroupModel.setBinGroupBy( nGroupBy );
    maFieldGroupModel.mbRangeGroup   = true;
    maFieldGroupModel.mbDateGroup    = getFlag( nFlags, OOBIN_PCDFRANGEPR_DATEGROUP );
    maFieldGroupModel.mbAutoStart    = getFlag( nFlags, OOBIN_PCDFRANGEPR_AUTOSTART );
    maFieldGroupModel.mbAutoEnd      = getFlag( nFlags, OOBIN_PCDFRANGEPR_AUTOEND );

    OSL_ENSURE( maFieldGroupModel.mbDateGroup == (maFieldGroupModel.mnGroupBy != XML_range), "PivotCacheField::importPCDFRangePr - wrong date flag" );
    if( maFieldGroupModel.mbDateGroup )
    {
        maFieldGroupModel.maStartDate = getUnitConverter().calcDateTimeFromSerial( maFieldGroupModel.mfStartValue );
        maFieldGroupModel.maEndDate   = getUnitConverter().calcDateTimeFromSerial( maFieldGroupModel.mfEndValue );
    }
}

void PivotCacheField::importPCDFDiscretePrItem( sal_Int32 nRecId, RecordInputStream& rStrm )
{
    OSL_ENSURE( nRecId == OOBIN_ID_PCITEM_INDEX, "PivotCacheField::importPCDFDiscretePrItem - unexpected record" );
    if( nRecId == OOBIN_ID_PCITEM_INDEX )
        maDiscreteItems.push_back( rStrm.readInt32() );
}

void PivotCacheField::importPCDFGroupItem( sal_Int32 nRecId, RecordInputStream& rStrm )
{
    maGroupItems.importItem( nRecId, rStrm );
}

void PivotCacheField::importPCDField( BiffInputStream& rStrm )
{
    sal_uInt16 nFlags, nGroupItems, nBaseItems, nSharedItems;
    rStrm >> nFlags;
    maFieldGroupModel.mnParentField  = rStrm.readuInt16();
    maFieldGroupModel.mnBaseField    = rStrm.readuInt16();
    rStrm.skip( 2 );    // number of unique items (either shared or group)
    rStrm >> nGroupItems >> nBaseItems >> nSharedItems;
    maFieldModel.maName = (getBiff() == BIFF8) ? rStrm.readUniString() : rStrm.readByteStringUC( true, getTextEncoding() );

    maFieldModel.mbServerField          = getFlag( nFlags, BIFF_PCDFIELD_SERVERFIELD );
    maFieldModel.mbUniqueList           = !getFlag( nFlags, BIFF_PCDFIELD_NOUNIQUEITEMS );
    maSharedItemsModel.mbHasSemiMixed   = getFlag( nFlags, BIFF_PCDFIELD_HASSEMIMIXED );
    maSharedItemsModel.mbHasNonDate     = getFlag( nFlags, BIFF_PCDFIELD_HASNONDATE );
    maSharedItemsModel.mbHasDate        = getFlag( nFlags, BIFF_PCDFIELD_HASDATE );
    maSharedItemsModel.mbIsNumeric      = getFlag( nFlags, BIFF_PCDFIELD_ISNUMERIC );
    maSharedItemsModel.mbHasLongIndexes = getFlag( nFlags, BIFF_PCDFIELD_HASLONGINDEX );
    maFieldGroupModel.mbRangeGroup      = getFlag( nFlags, BIFF_PCDFIELD_RANGEGROUP );

    // in BIFF, presence of parent group field is denoted by a flag
    if( !getFlag( nFlags, BIFF_PCDFIELD_HASPARENT ) )
        maFieldGroupModel.mnParentField = -1;

    // following PCDFSQLTYPE record contains SQL type
    if( (rStrm.getNextRecId() == BIFF_ID_PCDFSQLTYPE) && rStrm.startNextRecord() )
        maFieldModel.mnSqlType = rStrm.readInt16();

    // read group items, if any
    if( nGroupItems > 0 )
    {
        OSL_ENSURE( getFlag( nFlags, BIFF_PCDFIELD_HASITEMS ), "PivotCacheField::importPCDField - missing items flag" );
        maGroupItems.importItemList( rStrm, nGroupItems );

        sal_uInt16 nNextRecId = rStrm.getNextRecId();
        bool bHasRangePr = nNextRecId == BIFF_ID_PCDFRANGEPR;
        bool bHasDiscretePr = nNextRecId == BIFF_ID_PCDFDISCRETEPR;

        OSL_ENSURE( bHasRangePr || bHasDiscretePr, "PivotCacheField::importPCDField - missing group properties record" );
        OSL_ENSURE( bHasRangePr == maFieldGroupModel.mbRangeGroup, "PivotCacheField::importPCDField - invalid range grouping flag" );
        if( bHasRangePr && rStrm.startNextRecord() )
            importPCDFRangePr( rStrm );
        else if( bHasDiscretePr && rStrm.startNextRecord() )
            importPCDFDiscretePr( rStrm );
    }

    // read the shared items, if any
    if( nSharedItems > 0 )
    {
        OSL_ENSURE( getFlag( nFlags, BIFF_PCDFIELD_HASITEMS ), "PivotCacheField::importPCDField - missing items flag" );
        maSharedItems.importItemList( rStrm, nSharedItems );
    }
}

void PivotCacheField::importPCDFRangePr( BiffInputStream& rStrm )
{
    sal_uInt16 nFlags;
    rStrm >> nFlags;
    maFieldGroupModel.setBinGroupBy( extractValue< sal_uInt8 >( nFlags, 2, 3 ) );
    maFieldGroupModel.mbRangeGroup = true;
    maFieldGroupModel.mbDateGroup  = maFieldGroupModel.mnGroupBy != XML_range;
    maFieldGroupModel.mbAutoStart  = getFlag( nFlags, BIFF_PCDFRANGEPR_AUTOSTART );
    maFieldGroupModel.mbAutoEnd    = getFlag( nFlags, BIFF_PCDFRANGEPR_AUTOEND );

    /*  Start, end, and interval are stored in 3 separate item records. Type of
        the items is dependent on numeric/date mode. Numeric groups expect
        three PCITEM_DOUBLE records, date groups expect two PCITEM_DATE records
        and one PCITEM_INT record. */
    PivotCacheItemList aLimits( *this );
    aLimits.importItemList( rStrm, 3 );
    OSL_ENSURE( aLimits.size() == 3, "PivotCacheField::importPCDFRangePr - missing grouping records" );
    const PivotCacheItem* pStartValue = aLimits.getCacheItem( 0 );
    const PivotCacheItem* pEndValue = aLimits.getCacheItem( 1 );
    const PivotCacheItem* pInterval = aLimits.getCacheItem( 2 );
    if( pStartValue && pEndValue && pInterval )
    {
        if( maFieldGroupModel.mbDateGroup )
        {
            bool bHasTypes = (pStartValue->getType() == XML_d) && (pEndValue->getType() == XML_d) && (pInterval->getType() == XML_i);
            OSL_ENSURE( bHasTypes, "PivotCacheField::importPCDFRangePr - wrong data types in grouping items" );
            if( bHasTypes )
            {
                maFieldGroupModel.maStartDate = pStartValue->getValue().get< DateTime >();
                maFieldGroupModel.maEndDate   = pEndValue->getValue().get< DateTime >();
                maFieldGroupModel.mfInterval  = pInterval->getValue().get< sal_Int16 >();
            }
        }
        else
        {
            bool bHasTypes = (pStartValue->getType() == XML_n) && (pEndValue->getType() == XML_n) && (pInterval->getType() == XML_n);
            OSL_ENSURE( bHasTypes, "PivotCacheField::importPCDFRangePr - wrong data types in grouping items" );
            if( bHasTypes )
            {
                maFieldGroupModel.mfStartValue = pStartValue->getValue().get< double >();
                maFieldGroupModel.mfEndValue   = pEndValue->getValue().get< double >();
                maFieldGroupModel.mfInterval   = pInterval->getValue().get< double >();
            }
        }
    }
}

void PivotCacheField::importPCDFDiscretePr( BiffInputStream& rStrm )
{
    sal_Int32 nCount = static_cast< sal_Int32 >( rStrm.getLength() / 2 );
    for( sal_Int32 nIndex = 0; !rStrm.isEof() && (nIndex < nCount); ++nIndex )
        maDiscreteItems.push_back( rStrm.readuInt16() );
}

const PivotCacheItem* PivotCacheField::getCacheItem( sal_Int32 nItemIdx ) const
{
    if( hasGroupItems() )
        return maGroupItems.getCacheItem( nItemIdx );
    if( hasSharedItems() )
        return maSharedItems.getCacheItem( nItemIdx );
    return 0;
}

void PivotCacheField::getCacheItemNames( ::std::vector< OUString >& orItemNames ) const
{
    if( hasGroupItems() )
        maGroupItems.getCacheItemNames( orItemNames );
    else if( hasSharedItems() )
        maSharedItems.getCacheItemNames( orItemNames );
}

void PivotCacheField::convertNumericGrouping( const Reference< XDataPilotField >& rxDPField ) const
{
    OSL_ENSURE( hasGroupItems() && hasNumericGrouping(), "PivotCacheField::convertNumericGrouping - not a numeric group field" );
    PropertySet aPropSet( rxDPField );
    if( hasGroupItems() && hasNumericGrouping() && aPropSet.is() )
    {
        DataPilotFieldGroupInfo aGroupInfo;
        aGroupInfo.HasAutoStart  = maFieldGroupModel.mbAutoStart;
        aGroupInfo.HasAutoEnd    = maFieldGroupModel.mbAutoEnd;
        aGroupInfo.HasDateValues = sal_False;
        aGroupInfo.Start         = maFieldGroupModel.mfStartValue;
        aGroupInfo.End           = maFieldGroupModel.mfEndValue;
        aGroupInfo.Step          = maFieldGroupModel.mfInterval;
        aGroupInfo.GroupBy       = 0;
        aPropSet.setProperty( PROP_GroupInfo, aGroupInfo );
    }
}

OUString PivotCacheField::createDateGroupField( const Reference< XDataPilotField >& rxBaseDPField ) const
{
    OSL_ENSURE( hasGroupItems() && hasDateGrouping(), "PivotCacheField::createDateGroupField - not a numeric group field" );
    Reference< XDataPilotField > xDPGroupField;
    PropertySet aPropSet( rxBaseDPField );
    if( hasGroupItems() && hasDateGrouping() && aPropSet.is() )
    {
        bool bDayRanges = (maFieldGroupModel.mnGroupBy == XML_days) && (maFieldGroupModel.mfInterval >= 2.0);

        DataPilotFieldGroupInfo aGroupInfo;
        aGroupInfo.HasAutoStart  = maFieldGroupModel.mbAutoStart;
        aGroupInfo.HasAutoEnd    = maFieldGroupModel.mbAutoEnd;
        aGroupInfo.HasDateValues = sal_True;
        aGroupInfo.Start         = getUnitConverter().calcSerialFromDateTime( maFieldGroupModel.maStartDate );
        aGroupInfo.End           = getUnitConverter().calcSerialFromDateTime( maFieldGroupModel.maEndDate );
        aGroupInfo.Step          = bDayRanges ? maFieldGroupModel.mfInterval : 0.0;

        using namespace ::com::sun::star::sheet::DataPilotFieldGroupBy;
        switch( maFieldGroupModel.mnGroupBy )
        {
            case XML_years:     aGroupInfo.GroupBy = YEARS;     break;
            case XML_quarters:  aGroupInfo.GroupBy = QUARTERS;  break;
            case XML_months:    aGroupInfo.GroupBy = MONTHS;    break;
            case XML_days:      aGroupInfo.GroupBy = DAYS;      break;
            case XML_hours:     aGroupInfo.GroupBy = HOURS;     break;
            case XML_minutes:   aGroupInfo.GroupBy = MINUTES;   break;
            case XML_seconds:   aGroupInfo.GroupBy = SECONDS;   break;
            default:    OSL_ENSURE( false, "PivotCacheField::convertRangeGrouping - unknown date/time interval" );
        }

        try
        {
            Reference< XDataPilotFieldGrouping > xDPGrouping( rxBaseDPField, UNO_QUERY_THROW );
            xDPGroupField = xDPGrouping->createDateGroup( aGroupInfo );
        }
        catch( Exception& )
        {
        }
    }

    Reference< XNamed > xFieldName( xDPGroupField, UNO_QUERY );
    return xFieldName.is() ? xFieldName->getName() : OUString();
}

OUString PivotCacheField::createParentGroupField( const Reference< XDataPilotField >& rxBaseDPField, PivotCacheGroupItemVector& orItemNames ) const
{
    OSL_ENSURE( hasGroupItems() && !maDiscreteItems.empty(), "PivotCacheField::createParentGroupField - not a group field" );
    OSL_ENSURE( maDiscreteItems.size() == orItemNames.size(), "PivotCacheField::createParentGroupField - number of item names does not match grouping info" );
    Reference< XDataPilotFieldGrouping > xDPGrouping( rxBaseDPField, UNO_QUERY );
    if( !xDPGrouping.is() ) return OUString();

    // map the group item indexes from maGroupItems to all item indexes from maDiscreteItems
    typedef ::std::vector< sal_Int32 > GroupItemList;
    typedef ::std::vector< GroupItemList > GroupItemMap;
    GroupItemMap aItemMap( maGroupItems.size() );
    for( IndexVector::const_iterator aBeg = maDiscreteItems.begin(), aIt = aBeg, aEnd = maDiscreteItems.end(); aIt != aEnd; ++aIt )
        if( GroupItemList* pItems = ContainerHelper::getVectorElement( aItemMap, *aIt ) )
            pItems->push_back( static_cast< sal_Int32 >( aIt - aBeg ) );

    // process all groups
    Reference< XDataPilotField > xDPGroupField;
    for( GroupItemMap::iterator aBeg = aItemMap.begin(), aIt = aBeg, aEnd = aItemMap.end(); aIt != aEnd; ++aIt )
    {
        OSL_ENSURE( !aIt->empty(), "PivotCacheField::createParentGroupField - item/group should not be empty" );
        // if the item count is greater than 1, the item is a group of items
        if( aIt->size() > 1 )
        {
            /*  Insert the names of the items that are part of this group. Calc
                expects the names of the members of the field whose members are
                grouped (which may be the names of groups too). Excel provides
                the names of the base field items instead (no group names
                involved). Therefore, the passed collection of current item
                names as they are already grouped is used here to resolve the
                item names. */
            ::std::vector< OUString > aMembers;
            for( GroupItemList::iterator aBeg2 = aIt->begin(), aIt2 = aBeg2, aEnd2 = aIt->end(); aIt2 != aEnd2; ++aIt2 )
                if( const PivotCacheGroupItem* pName = ContainerHelper::getVectorElement( orItemNames, *aIt2 ) )
                    if( ::std::find( aMembers.begin(), aMembers.end(), pName->maGroupName ) == aMembers.end() )
                        aMembers.push_back( pName->maGroupName );

            /*  Check again, that this is not just a group that is not grouped
                further with other items. */
            if( aMembers.size() > 1 ) try
            {
                // only the first call of createNameGroup() returns the new field
                Reference< XDataPilotField > xDPNewField = xDPGrouping->createNameGroup( ContainerHelper::vectorToSequence( aMembers ) );
                OSL_ENSURE( xDPGroupField.is() != xDPNewField.is(), "PivotCacheField::createParentGroupField - missing group field" );
                if( !xDPGroupField.is() )
                    xDPGroupField = xDPNewField;

                // get current grouping info
                DataPilotFieldGroupInfo aGroupInfo;
                PropertySet aPropSet( xDPGroupField );
                aPropSet.getProperty( aGroupInfo, PROP_GroupInfo );

                /*  Find the group object and the auto-generated group name.
                    The returned field contains all groups derived from the
                    previous field if that is grouped too. To find the correct
                    group, the first item used to create the group is serached.
                    Calc provides the original item names of the base field
                    when the group is querried for its members. Its does not
                    provide the names of members that are already groups in the
                    field used to create the new groups. (Is this a bug?)
                    Therefore, a name from the passed list of original item
                    names is used to find the correct group. */
                OUString aFirstItem;
                if( const PivotCacheGroupItem* pName = ContainerHelper::getVectorElement( orItemNames, aIt->front() ) )
                    aFirstItem = pName->maOrigName;
                Reference< XNamed > xGroupName;
                OUString aAutoName;
                Reference< XIndexAccess > xGroupsIA( aGroupInfo.Groups, UNO_QUERY_THROW );
                for( sal_Int32 nIdx = 0, nCount = xGroupsIA->getCount(); (nIdx < nCount) && (aAutoName.getLength() == 0); ++nIdx ) try
                {
                    Reference< XNameAccess > xItemsNA( xGroupsIA->getByIndex( nIdx ), UNO_QUERY_THROW );
                    if( xItemsNA->hasByName( aFirstItem ) )
                    {
                        xGroupName.set( xGroupsIA->getByIndex( nIdx ), UNO_QUERY_THROW );
                        aAutoName = xGroupName->getName();
                    }
                }
                catch( Exception& )
                {
                }
                OSL_ENSURE( aAutoName.getLength() > 0, "PivotCacheField::createParentGroupField - cannot find auto-generated group name" );

                // get the real group name from the list of group items
                OUString aGroupName;
                if( const PivotCacheItem* pGroupItem = maGroupItems.getCacheItem( static_cast< sal_Int32 >( aIt - aBeg ) ) )
                    aGroupName = pGroupItem->getName();
                OSL_ENSURE( aGroupName.getLength() > 0, "PivotCacheField::createParentGroupField - cannot find group name" );
                if( aGroupName.getLength() == 0 )
                    aGroupName = aAutoName;

                if( xGroupName.is() && (aGroupName.getLength() > 0) )
                {
                    // replace the auto-generated group name with the real name
                    if( aAutoName != aGroupName )
                    {
                        xGroupName->setName( aGroupName );
                        aPropSet.setProperty( PROP_GroupInfo, aGroupInfo );
                    }
                    // replace original item names in passed vector with group name
                    for( GroupItemList::iterator aIt2 = aIt->begin(), aEnd2 = aIt->end(); aIt2 != aEnd2; ++aIt2 )
                        if( PivotCacheGroupItem* pName = ContainerHelper::getVectorElement( orItemNames, *aIt2 ) )
                            pName->maGroupName = aGroupName;
                }
            }
            catch( Exception& )
            {
            }
        }
    }

    Reference< XNamed > xFieldName( xDPGroupField, UNO_QUERY );
    return xFieldName.is() ? xFieldName->getName() : OUString();
}

void PivotCacheField::writeSourceHeaderCell( WorksheetHelper& rSheetHelper, sal_Int32 nCol, sal_Int32 nRow ) const
{
    rSheetHelper.setStringCell( rSheetHelper.getCell( CellAddress( rSheetHelper.getSheetIndex(), nCol, nRow ) ), maFieldModel.maName );
}

void PivotCacheField::writeSourceDataCell( WorksheetHelper& rSheetHelper, sal_Int32 nCol, sal_Int32 nRow, const PivotCacheItem& rItem ) const
{
    bool bHasIndex = rItem.getType() == XML_x;
    OSL_ENSURE( bHasIndex != maSharedItems.empty(), "PivotCacheField::writeSourceDataCell - shared items missing or not expected" );
    if( bHasIndex )
        writeSharedItemToSourceDataCell( rSheetHelper, nCol, nRow, rItem.getValue().get< sal_Int32 >() );
    else
        writeItemToSourceDataCell( rSheetHelper, nCol, nRow, rItem );
}

void PivotCacheField::importPCRecordItem( RecordInputStream& rStrm, WorksheetHelper& rSheetHelper, sal_Int32 nCol, sal_Int32 nRow ) const
{
    if( hasSharedItems() )
    {
        writeSharedItemToSourceDataCell( rSheetHelper, nCol, nRow, rStrm.readInt32() );
    }
    else
    {
        PivotCacheItem aItem;
        if( maSharedItemsModel.mbIsNumeric )
           aItem.readDouble( rStrm );
        else if( maSharedItemsModel.mbHasDate && !maSharedItemsModel.mbHasString )
           aItem.readDate( rStrm );
        else
           aItem.readString( rStrm );
        writeItemToSourceDataCell( rSheetHelper, nCol, nRow, aItem );
    }
}

void PivotCacheField::importPCItemIndex( BiffInputStream& rStrm, WorksheetHelper& rSheetHelper, sal_Int32 nCol, sal_Int32 nRow ) const
{
    OSL_ENSURE( hasSharedItems(), "PivotCacheField::importPCItemIndex - invalid call, no shared items found" );
    sal_Int32 nIndex = maSharedItemsModel.mbHasLongIndexes ? rStrm.readuInt16() : rStrm.readuInt8();
    writeSharedItemToSourceDataCell( rSheetHelper, nCol, nRow, nIndex );
}

// private --------------------------------------------------------------------

void PivotCacheField::writeItemToSourceDataCell( WorksheetHelper& rSheetHelper,
        sal_Int32 nCol, sal_Int32 nRow, const PivotCacheItem& rItem ) const
{
    if( rItem.getType() != XML_m )
    {
        Reference< XCell > xCell = rSheetHelper.getCell( CellAddress( rSheetHelper.getSheetIndex(), nCol, nRow ) );
        if( xCell.is() ) switch( rItem.getType() )
        {
            case XML_s: rSheetHelper.setStringCell( xCell, rItem.getValue().get< OUString >() );                                break;
            case XML_n: xCell->setValue( rItem.getValue().get< double >() );                                                    break;
            case XML_i: xCell->setValue( rItem.getValue().get< sal_Int16 >() );                                                 break;
            case XML_d: rSheetHelper.setDateTimeCell( xCell, rItem.getValue().get< DateTime >() );                              break;
            case XML_b: rSheetHelper.setBooleanCell( xCell, rItem.getValue().get< bool >() );                                   break;
            case XML_e: rSheetHelper.setErrorCell( xCell, static_cast< sal_uInt8 >( rItem.getValue().get< sal_Int32 >() ) );    break;
            default:    OSL_ENSURE( false, "PivotCacheField::writeItemToSourceDataCell - unexpected item data type" );
        }
    }
}

void PivotCacheField::writeSharedItemToSourceDataCell(
        WorksheetHelper& rSheetHelper, sal_Int32 nCol, sal_Int32 nRow, sal_Int32 nItemIdx ) const
{
    if( const PivotCacheItem* pCacheItem = maSharedItems.getCacheItem( nItemIdx ) )
        writeItemToSourceDataCell( rSheetHelper, nCol, nRow, *pCacheItem );
}

// ============================================================================

PCDefinitionModel::PCDefinitionModel() :
    mfRefreshedDate( 0.0 ),
    mnRecords( 0 ),
    mnMissItemsLimit( 0 ),
    mnDatabaseFields( 0 ),
    mbInvalid( false ),
    mbSaveData( true ),
    mbRefreshOnLoad( false ),
    mbOptimizeMemory( false ),
    mbEnableRefresh( true ),
    mbBackgroundQuery( false ),
    mbUpgradeOnRefresh( false ),
    mbTupleCache( false ),
    mbSupportSubquery( false ),
    mbSupportDrill( false )
{
}

// ----------------------------------------------------------------------------

PCSourceModel::PCSourceModel() :
    mnSourceType( XML_TOKEN_INVALID ),
    mnConnectionId( 0 )
{
}

// ----------------------------------------------------------------------------

PCWorksheetSourceModel::PCWorksheetSourceModel()
{
    maRange.StartColumn = maRange.StartRow = maRange.EndColumn = maRange.EndRow = -1;
}

// ----------------------------------------------------------------------------

PivotCache::PivotCache( const WorkbookHelper& rHelper ) :
    WorkbookHelper( rHelper ),
    mbValidSource( false ),
    mbDummySheet( false )
{
}

void PivotCache::importPivotCacheDefinition( const AttributeList& rAttribs )
{
    maDefModel.maRelId            = rAttribs.getString( R_TOKEN( id ), OUString() );
    maDefModel.maRefreshedBy      = rAttribs.getXString( XML_refreshedBy, OUString() );
    maDefModel.mfRefreshedDate    = rAttribs.getDouble( XML_refreshedDate, 0.0 );
    maDefModel.mnRecords          = rAttribs.getInteger( XML_recordCount, 0 );
    maDefModel.mnMissItemsLimit   = rAttribs.getInteger( XML_missingItemsLimit, 0 );
    maDefModel.mbInvalid          = rAttribs.getBool( XML_invalid, false );
    maDefModel.mbSaveData         = rAttribs.getBool( XML_saveData, true );
    maDefModel.mbRefreshOnLoad    = rAttribs.getBool( XML_refreshOnLoad, false );
    maDefModel.mbOptimizeMemory   = rAttribs.getBool( XML_optimizeMemory, false );
    maDefModel.mbEnableRefresh    = rAttribs.getBool( XML_enableRefresh, true );
    maDefModel.mbBackgroundQuery  = rAttribs.getBool( XML_backgroundQuery, false );
    maDefModel.mbUpgradeOnRefresh = rAttribs.getBool( XML_upgradeOnRefresh, false );
    maDefModel.mbTupleCache       = rAttribs.getBool( XML_tupleCache, false );
    maDefModel.mbSupportSubquery  = rAttribs.getBool( XML_supportSubquery, false );
    maDefModel.mbSupportDrill     = rAttribs.getBool( XML_supportAdvancedDrill, false );
}

void PivotCache::importCacheSource( const AttributeList& rAttribs )
{
    maSourceModel.mnSourceType   = rAttribs.getToken( XML_type, XML_TOKEN_INVALID );
    maSourceModel.mnConnectionId = rAttribs.getInteger( XML_connectionId, 0 );
}

void PivotCache::importWorksheetSource( const AttributeList& rAttribs, const Relations& rRelations )
{
    maSheetSrcModel.maRelId   = rAttribs.getString( R_TOKEN( id ), OUString() );
    maSheetSrcModel.maSheet   = rAttribs.getXString( XML_sheet, OUString() );
    maSheetSrcModel.maDefName = rAttribs.getXString( XML_name, OUString() );

    // resolve URL of external document
    maTargetUrl = rRelations.getExternalTargetFromRelId( maSheetSrcModel.maRelId );
    // store range address unchecked with sheet index 0, will be resolved/checked later
    getAddressConverter().convertToCellRangeUnchecked( maSheetSrcModel.maRange, rAttribs.getString( XML_ref, OUString() ), 0 );
}

void PivotCache::importPCDefinition( RecordInputStream& rStrm )
{
    sal_uInt8 nFlags1, nFlags2;
    rStrm.skip( 3 );    // create/refresh version id's
    rStrm >> nFlags1 >> maDefModel.mnMissItemsLimit >> maDefModel.mfRefreshedDate >> nFlags2 >> maDefModel.mnRecords;
    if( getFlag( nFlags2, OOBIN_PCDEFINITION_HASUSERNAME ) )
        rStrm >> maDefModel.maRefreshedBy;
    if( getFlag( nFlags2, OOBIN_PCDEFINITION_HASRELID ) )
        rStrm >> maDefModel.maRelId;

    maDefModel.mbInvalid          = getFlag( nFlags1, OOBIN_PCDEFINITION_INVALID );
    maDefModel.mbSaveData         = getFlag( nFlags1, OOBIN_PCDEFINITION_SAVEDATA );
    maDefModel.mbRefreshOnLoad    = getFlag( nFlags1, OOBIN_PCDEFINITION_REFRESHONLOAD );
    maDefModel.mbOptimizeMemory   = getFlag( nFlags1, OOBIN_PCDEFINITION_OPTIMIZEMEMORY );
    maDefModel.mbEnableRefresh    = getFlag( nFlags1, OOBIN_PCDEFINITION_ENABLEREFRESH );
    maDefModel.mbBackgroundQuery  = getFlag( nFlags1, OOBIN_PCDEFINITION_BACKGROUNDQUERY );
    maDefModel.mbUpgradeOnRefresh = getFlag( nFlags1, OOBIN_PCDEFINITION_UPGRADEONREFR );
    maDefModel.mbTupleCache       = getFlag( nFlags1, OOBIN_PCDEFINITION_TUPELCACHE );
    maDefModel.mbSupportSubquery  = getFlag( nFlags2, OOBIN_PCDEFINITION_SUPPORTSUBQUERY );
    maDefModel.mbSupportDrill     = getFlag( nFlags2, OOBIN_PCDEFINITION_SUPPORTDRILL );
}

void PivotCache::importPCDSource( RecordInputStream& rStrm )
{
    sal_Int32 nSourceType;
    rStrm >> nSourceType >> maSourceModel.mnConnectionId;
    static const sal_Int32 spnSourceTypes[] = { XML_worksheet, XML_external, XML_consolidation, XML_scenario };
    maSourceModel.mnSourceType = STATIC_ARRAY_SELECT( spnSourceTypes, nSourceType, XML_TOKEN_INVALID );
}

void PivotCache::importPCDSheetSource( RecordInputStream& rStrm, const Relations& rRelations )
{
    sal_uInt8 nIsDefName, nIsBuiltinName, nFlags;
    rStrm >> nIsDefName >> nIsBuiltinName >> nFlags;
    if( getFlag( nFlags, OOBIN_PCDWBSOURCE_HASSHEET ) )
        rStrm >> maSheetSrcModel.maSheet;
    if( getFlag( nFlags, OOBIN_PCDWBSOURCE_HASRELID ) )
        rStrm >> maSheetSrcModel.maRelId;

    // read cell range or defined name
    if( nIsDefName == 0 )
    {
        BinRange aBinRange;
        rStrm >> aBinRange;
        // store range address unchecked with sheet index 0, will be resolved/checked later
        getAddressConverter().convertToCellRangeUnchecked( maSheetSrcModel.maRange, aBinRange, 0 );
    }
    else
    {
        rStrm >> maSheetSrcModel.maDefName;
        if( nIsBuiltinName != 0 )
            maSheetSrcModel.maDefName = CREATE_OUSTRING( "_xlnm." ) + maSheetSrcModel.maDefName;
    }

    // resolve URL of external document
    maTargetUrl = rRelations.getExternalTargetFromRelId( maSheetSrcModel.maRelId );
}

void PivotCache::importPCDSource( BiffInputStream& rStrm )
{
    switch( rStrm.readuInt16() )
    {
        case BIFF_PCDSOURCE_WORKSHEET:
        {
            maSourceModel.mnSourceType = XML_worksheet;
            sal_uInt16 nNextRecId = rStrm.getNextRecId();
            switch( nNextRecId )
            {
                case BIFF_ID_DCONREF:       if( rStrm.startNextRecord() ) importDConRef( rStrm );       break;
                case BIFF_ID_DCONNAME:      if( rStrm.startNextRecord() ) importDConName( rStrm );      break;
                case BIFF_ID_DCONBINAME:    if( rStrm.startNextRecord() ) importDConBIName( rStrm );    break;
            }
        }
        break;
        case BIFF_PCDSOURCE_EXTERNAL:
            maSourceModel.mnSourceType = XML_external;
        break;
        case BIFF_PCDSOURCE_CONSOLIDATION:
            maSourceModel.mnSourceType = XML_consolidation;
        break;
        case BIFF_PCDSOURCE_SCENARIO:
            maSourceModel.mnSourceType = XML_scenario;
        break;
        default:
            maSourceModel.mnSourceType = XML_TOKEN_INVALID;
    }
}

void PivotCache::importPCDefinition( BiffInputStream& rStrm )
{
    sal_uInt16 nFlags, nUserNameLen;
    rStrm >> maDefModel.mnRecords;
    rStrm.skip( 2 );    // repeated cache ID
    rStrm >> nFlags;
    rStrm.skip( 2 );    // unused
    rStrm >> maDefModel.mnDatabaseFields;
    rStrm.skip( 6 );    // total field count, report record count, (repeated) cache type
    rStrm >> nUserNameLen;
    if( nUserNameLen != BIFF_PC_NOSTRING )
        maDefModel.maRefreshedBy = (getBiff() == BIFF8) ?
            rStrm.readUniString( nUserNameLen ) :
            rStrm.readCharArrayUC( nUserNameLen, getTextEncoding() );

    maDefModel.mbInvalid          = getFlag( nFlags, BIFF_PCDEFINITION_INVALID );
    maDefModel.mbSaveData         = getFlag( nFlags, BIFF_PCDEFINITION_SAVEDATA );
    maDefModel.mbRefreshOnLoad    = getFlag( nFlags, BIFF_PCDEFINITION_REFRESHONLOAD );
    maDefModel.mbOptimizeMemory   = getFlag( nFlags, BIFF_PCDEFINITION_OPTIMIZEMEMORY );
    maDefModel.mbEnableRefresh    = getFlag( nFlags, BIFF_PCDEFINITION_ENABLEREFRESH );
    maDefModel.mbBackgroundQuery  = getFlag( nFlags, BIFF_PCDEFINITION_BACKGROUNDQUERY );

    if( (rStrm.getNextRecId() == BIFF_ID_PCDEFINITION2) && rStrm.startNextRecord() )
        rStrm >> maDefModel.mfRefreshedDate;
}

PivotCacheField& PivotCache::createCacheField( bool bInitDatabaseField )
{
    bool bIsDatabaseField = !bInitDatabaseField || (maFields.size() < maDefModel.mnDatabaseFields);
    PivotCacheFieldVector::value_type xCacheField( new PivotCacheField( *this, bIsDatabaseField ) );
    maFields.push_back( xCacheField );
    return *xCacheField;
}

void PivotCache::finalizeImport()
{
    // collect all fields that are based on source data (needed to finalize source data below)
    OSL_ENSURE( !maFields.empty(), "PivotCache::finalizeImport - no pivot cache fields found" );
    for( PivotCacheFieldVector::const_iterator aIt = maFields.begin(), aEnd = maFields.end(); aIt != aEnd; ++aIt )
    {
        if( (*aIt)->isDatabaseField() )
        {
            OSL_ENSURE( (aIt == maFields.begin()) || (*(aIt - 1))->isDatabaseField(),
                "PivotCache::finalizeImport - database field follows a calculated field" );
            maDatabaseIndexes.push_back( static_cast< sal_Int32 >( maDatabaseFields.size() ) );
            maDatabaseFields.push_back( *aIt );
        }
        else
        {
            maDatabaseIndexes.push_back( -1 );
        }
    }
    OSL_ENSURE( !maDatabaseFields.empty(), "PivotCache::finalizeImport - no pivot cache source fields found" );

    // finalize source data depending on source type
    switch( maSourceModel.mnSourceType )
    {
        case XML_worksheet:
        {
            // decide whether an external document is used
            bool bInternal = (maTargetUrl.getLength() == 0) && (maSheetSrcModel.maRelId.getLength() == 0);
            bool bExternal = maTargetUrl.getLength() > 0;   // relation ID may be empty, e.g. BIFF import
            OSL_ENSURE( bInternal || bExternal, "PivotCache::finalizeImport - invalid external document URL" );
            if( bInternal )
                finalizeInternalSheetSource();
            else if( bExternal )
                finalizeExternalSheetSource();
        }
        break;

        // currently, we only support worksheet data sources
        case XML_external:
        break;
        case XML_consolidation:
        break;
        case XML_scenario:
        break;
    }
}

sal_Int32 PivotCache::getCacheFieldCount() const
{
    return static_cast< sal_Int32 >( maFields.size() );
}

const PivotCacheField* PivotCache::getCacheField( sal_Int32 nFieldIdx ) const
{
    return maFields.get( nFieldIdx ).get();
}

sal_Int32 PivotCache::getCacheDatabaseIndex( sal_Int32 nFieldIdx ) const
{
    return ContainerHelper::getVectorElement< sal_Int32 >( maDatabaseIndexes, nFieldIdx, -1 );
}

void PivotCache::writeSourceHeaderCells( WorksheetHelper& rSheetHelper ) const
{
    OSL_ENSURE( static_cast< size_t >( maSheetSrcModel.maRange.EndColumn - maSheetSrcModel.maRange.StartColumn + 1 ) == maDatabaseFields.size(),
        "PivotCache::writeSourceHeaderCells - source cell range width does not match number of source fields" );
    sal_Int32 nCol = maSheetSrcModel.maRange.StartColumn;
    sal_Int32 nMaxCol = getAddressConverter().getMaxApiAddress().Column;
    sal_Int32 nRow = maSheetSrcModel.maRange.StartRow;
    for( PivotCacheFieldVector::const_iterator aIt = maDatabaseFields.begin(), aEnd = maDatabaseFields.end(); (aIt != aEnd) && (nCol <= nMaxCol); ++aIt, ++nCol )
        (*aIt)->writeSourceHeaderCell( rSheetHelper, nCol, nRow );
}

void PivotCache::writeSourceDataCell( WorksheetHelper& rSheetHelper, sal_Int32 nCol, sal_Int32 nRow, const PivotCacheItem& rItem ) const
{
    OSL_ENSURE( (0 <= nCol) && (nCol <= maSheetSrcModel.maRange.EndColumn - maSheetSrcModel.maRange.StartColumn), "PivotCache::writeSourceDataCell - invalid column index" );
    OSL_ENSURE( (0 < nRow) && (nRow <= maSheetSrcModel.maRange.EndRow - maSheetSrcModel.maRange.StartRow), "PivotCache::writeSourceDataCell - invalid row index" );
    if( const PivotCacheField* pCacheField = maDatabaseFields.get( nCol ).get() )
        pCacheField->writeSourceDataCell( rSheetHelper, maSheetSrcModel.maRange.StartColumn + nCol, maSheetSrcModel.maRange.StartRow + nRow, rItem );
}

void PivotCache::importPCRecord( RecordInputStream& rStrm, WorksheetHelper& rSheetHelper, sal_Int32 nRow ) const
{
    OSL_ENSURE( (0 < nRow) && (nRow <= maSheetSrcModel.maRange.EndRow - maSheetSrcModel.maRange.StartRow), "PivotCache::importPCRecord - invalid row index" );
    sal_Int32 nCol = maSheetSrcModel.maRange.StartColumn;
    sal_Int32 nMaxCol = getAddressConverter().getMaxApiAddress().Column;
    nRow += maSheetSrcModel.maRange.StartRow;
    for( PivotCacheFieldVector::const_iterator aIt = maDatabaseFields.begin(), aEnd = maDatabaseFields.end(); !rStrm.isEof() && (aIt != aEnd) && (nCol <= nMaxCol); ++aIt, ++nCol )
        (*aIt)->importPCRecordItem( rStrm, rSheetHelper, nCol, nRow );
}

void PivotCache::importPCItemIndexList( BiffInputStream& rStrm, WorksheetHelper& rSheetHelper, sal_Int32 nRow ) const
{
    OSL_ENSURE( (0 < nRow) && (nRow <= maSheetSrcModel.maRange.EndRow - maSheetSrcModel.maRange.StartRow), "PivotCache::importPCItemIndexList - invalid row index" );
    sal_Int32 nCol = maSheetSrcModel.maRange.StartColumn;
    sal_Int32 nMaxCol = getAddressConverter().getMaxApiAddress().Column;
    nRow += maSheetSrcModel.maRange.StartRow;
    for( PivotCacheFieldVector::const_iterator aIt = maDatabaseFields.begin(), aEnd = maDatabaseFields.end(); !rStrm.isEof() && (aIt != aEnd) && (nCol <= nMaxCol); ++aIt, ++nCol )
        if( (*aIt)->hasSharedItems() )
            (*aIt)->importPCItemIndex( rStrm, rSheetHelper, nCol, nRow );
}

// private --------------------------------------------------------------------

void PivotCache::importDConRef( BiffInputStream& rStrm )
{
    BinRange aBinRange;
    aBinRange.read( rStrm, false );     // always 8-bit column indexes
    // store range address unchecked with sheet index 0, will be resolved/checked later
    getAddressConverter().convertToCellRangeUnchecked( maSheetSrcModel.maRange, aBinRange, 0 );

    // the URL with (required) sheet name and optional URL of an external document
    importDConUrl( rStrm );
    OSL_ENSURE( maSheetSrcModel.maSheet.getLength() > 0, "PivotCache::importDConRef - missing sheet name" );
}

void PivotCache::importDConName( BiffInputStream& rStrm )
{
    maSheetSrcModel.maDefName = (getBiff() == BIFF8) ? rStrm.readUniString() : rStrm.readByteStringUC( false, getTextEncoding() );
    OSL_ENSURE( maSheetSrcModel.maDefName.getLength() > 0, "PivotCache::importDConName - missing defined name" );
    importDConUrl( rStrm );
}

void PivotCache::importDConBIName( BiffInputStream& rStrm )
{
    sal_uInt8 nNameId = rStrm.readuInt8();
    rStrm.skip( 3 );
    maSheetSrcModel.maDefName = OUString( sal_Unicode( nNameId ) );
    importDConUrl( rStrm );
}

void PivotCache::importDConUrl( BiffInputStream& rStrm )
{
    // the URL with sheet name and optional URL of an external document
    OUString aEncodedUrl;
    if( getBiff() == BIFF8 )
    {
        // empty string does not contain a flags byte, cannot use simple readUniString() here...
        sal_uInt16 nChars = rStrm.readuInt16();
        if( nChars > 0 )
            aEncodedUrl = rStrm.readUniString( nChars );
    }
    else
    {
        aEncodedUrl = rStrm.readByteStringUC( false, getTextEncoding() );
    }

    if( aEncodedUrl.getLength() > 0 )
    {
        OUString aClassName;
        getAddressConverter().parseBiffTargetUrl( aClassName, maTargetUrl, maSheetSrcModel.maSheet, aEncodedUrl, true );
    }
}

void PivotCache::finalizeInternalSheetSource()
{
    // resolve sheet name to sheet index
    sal_Int16 nSheet = getWorksheets().getCalcSheetIndex( maSheetSrcModel.maSheet );

    // if cache is based on a defined name or table, try to resolve to cell range
    if( maSheetSrcModel.maDefName.getLength() > 0 )
    {
        // local or global defined name
        if( const DefinedName* pDefName = getDefinedNames().getByModelName( maSheetSrcModel.maDefName, nSheet ).get() )
        {
            mbValidSource = pDefName->getAbsoluteRange( maSheetSrcModel.maRange );
        }
        // table
        else if( const Table* pTable = getTables().getTable( maSheetSrcModel.maDefName ).get() )
        {
            // get original range from table, but exclude the totals row(s)
            maSheetSrcModel.maRange = pTable->getOriginalRange();
            mbValidSource = (pTable->getHeight() - pTable->getTotalsRows()) > 1;
            if( mbValidSource )
                maSheetSrcModel.maRange.EndRow -= pTable->getTotalsRows();
        }
    }
    // else try the cell range (if the sheet exists)
    else if( nSheet >= 0 )
    {
        // insert sheet index into the range, range address will be checked below
        maSheetSrcModel.maRange.Sheet = nSheet;
        mbValidSource = true;
    }
    // else sheet has been deleted, generate the source data from cache
    else if( maSheetSrcModel.maSheet.getLength() > 0 )
    {
        prepareSourceDataSheet();
        // return here to skip the source range check below
        return;
    }

    // check range location, do not allow ranges that overflow the sheet partly
    mbValidSource = mbValidSource &&
        getAddressConverter().checkCellRange( maSheetSrcModel.maRange, false, true ) &&
        (maSheetSrcModel.maRange.StartRow < maSheetSrcModel.maRange.EndRow);
}

void PivotCache::finalizeExternalSheetSource()
{
    /*  If pivot cache is based on external sheet data, try to restore sheet
        data from cache records. No support for external defined names or tables,
        sheet name and path to cache records fragment (OOX only) are required. */
    bool bHasRelation = (getFilterType() == FILTER_BIFF) || (maDefModel.maRelId.getLength() > 0);
    if( bHasRelation && (maSheetSrcModel.maDefName.getLength() == 0) && (maSheetSrcModel.maSheet.getLength() > 0) )
        prepareSourceDataSheet();
}

void PivotCache::prepareSourceDataSheet()
{
    // data will be inserted in top-left cell, sheet index is still set to 0 (will be set below)
    maSheetSrcModel.maRange.EndColumn -= maSheetSrcModel.maRange.StartColumn;
    maSheetSrcModel.maRange.StartColumn = 0;
    maSheetSrcModel.maRange.EndRow -= maSheetSrcModel.maRange.StartRow;
    maSheetSrcModel.maRange.StartRow = 0;
    // check range location, do not allow ranges that overflow the sheet partly
    if( getAddressConverter().checkCellRange( maSheetSrcModel.maRange, false, true ) )
    {
        OUString aSheetName = CREATE_OUSTRING( "DPCache_" ) + maSheetSrcModel.maSheet;
        maSheetSrcModel.maRange.Sheet = getWorksheets().insertEmptySheet( aSheetName, false );
        mbValidSource = mbDummySheet = maSheetSrcModel.maRange.Sheet >= 0;
    }
}

// ============================================================================

PivotCacheBuffer::PivotCacheBuffer( const WorkbookHelper& rHelper ) :
    WorkbookHelper( rHelper )
{
}

void PivotCacheBuffer::registerPivotCacheFragment( sal_Int32 nCacheId, const OUString& rFragmentPath )
{
    OSL_ENSURE( nCacheId >= 0, "PivotCacheBuffer::registerPivotCacheFragment - invalid pivot cache identifier" );
    OSL_ENSURE( maFragmentPaths.count( nCacheId ) == 0, "PivotCacheBuffer::registerPivotCacheFragment - fragment path exists already" );
    if( (nCacheId >= 0) && (rFragmentPath.getLength() > 0) )
        maFragmentPaths[ nCacheId ] = rFragmentPath;
}

void PivotCacheBuffer::importPivotCacheRef( BiffInputStream& rStrm )
{
    // read the PIVOTCACHE record that contains the stream ID
    sal_Int32 nCacheId = rStrm.readuInt16();
    OSL_ENSURE( maFragmentPaths.count( nCacheId ) == 0, "PivotCacheBuffer::importPivotCacheRef - cache stream exists already" );
    OUStringBuffer aStrmName;
    static const sal_Unicode spcHexChars[] = { '0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F' };
    for( sal_uInt8 nBit = 0; nBit < 16; nBit += 4 )
        aStrmName.insert( 0, spcHexChars[ extractValue< size_t >( nCacheId, nBit, 4 ) ] );
    aStrmName.insert( 0, (getBiff() == BIFF8) ? CREATE_OUSTRING( "_SX_DB_CUR/" ) : CREATE_OUSTRING( "_SX_DB/" ) );
    maFragmentPaths[ nCacheId ] = aStrmName.makeStringAndClear();

    // try to read PCDSOURCE record (will read following data location records too)
    sal_uInt16 nNextRecId = rStrm.getNextRecId();
    OSL_ENSURE( nNextRecId == BIFF_ID_PCDSOURCE, "PivotCacheBuffer::importPivotCacheRef - PCDSOURCE record expected" );
    if( (nNextRecId == BIFF_ID_PCDSOURCE) && rStrm.startNextRecord() )
        createPivotCache( nCacheId ).importPCDSource( rStrm );
}

PivotCache* PivotCacheBuffer::importPivotCacheFragment( sal_Int32 nCacheId )
{
    switch( getFilterType() )
    {
        /*  BIFF filter: Pivot table provides 0-based index into list of pivot
            cache source links (PIVOTCACHE/PCDSOURCE/... record blocks in
            workbook stream). First, this index has to be resolved to the cache
            identifier that is used to manage the cache stream names (the
            maFragmentPaths member). The cache object itself exists already
            before the first call for the cache source index (see
            PivotCacheBuffer::importPivotCacheRef() above), because source data
            link is part of workbook data, not of the cache stream. To detect
            subsequent calls with an already initialized cache, the entry in
            maFragmentPaths will be removed after reading the cache stream. */
        case FILTER_BIFF:
        {
            /*  Resolve cache index to cache identifier and try to find pivot
                cache. Cache must exist already for a valid cache index. */
            nCacheId = ContainerHelper::getVectorElement< sal_Int32 >( maCacheIds, nCacheId, -1 );
            PivotCache* pCache = maCaches.get( nCacheId ).get();
            if( !pCache )
                return 0;

            /*  Try to find fragment path entry (stream name). If missing, the
                stream has been read already, and the cache can be returned. */
            FragmentPathMap::iterator aIt = maFragmentPaths.find( nCacheId );
            if( aIt != maFragmentPaths.end() )
            {
                /*  Import the cache stream. This may create a dummy data sheet
                    for external sheet sources. */
                BiffPivotCacheFragment( *this, aIt->second, *pCache ).importFragment();
                // remove the fragment entry to mark that the cache is initialized
                maFragmentPaths.erase( aIt );
            }
            return pCache;
        }

        /*  OOX/OOBIN filter: On first call for the cache ID, the pivot cache
            object is created and inserted into maCaches. Then, the cache
            definition fragment is read and the cache is returned. On
            subsequent calls, the created cache will be found in maCaches and
            returned immediately. */
        case FILTER_OOX:
        {
            // try to find an imported pivot cache
            if( PivotCache* pCache = maCaches.get( nCacheId ).get() )
                return pCache;

            // check if a fragment path exists for the passed cache identifier
            FragmentPathMap::iterator aIt = maFragmentPaths.find( nCacheId );
            if( aIt == maFragmentPaths.end() )
                return 0;

            /*  Import the cache fragment. This may create a dummy data sheet
                for external sheet sources. */
            PivotCache& rCache = createPivotCache( nCacheId );
            importOoxFragment( new OoxPivotCacheDefinitionFragment( *this, aIt->second, rCache ) );
            return &rCache;
        }

        case FILTER_UNKNOWN:
            OSL_ENSURE( false, "PivotCacheBuffer::importPivotCacheFragment - unknown filter type" );
    }
    return 0;
}

PivotCache& PivotCacheBuffer::createPivotCache( sal_Int32 nCacheId )
{
    maCacheIds.push_back( nCacheId );
    PivotCacheMap::mapped_type& rxCache = maCaches[ nCacheId ];
    rxCache.reset( new PivotCache( *this ) );
    return *rxCache;
}

// ============================================================================

} // namespace xls
} // namespace oox

