/* -*- Mode: C++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */
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

// header for class OGuard
// header for class Application
#include <vcl/svapp.hxx>

#include "schattr.hxx"
#ifndef _SVX_BRSHITEM_HXX 
#define ITEMID_BRUSH SCHATTR_SYMBOL_BRUSH
#include <bf_svx/brshitem.hxx>
#endif
// header for CreateGraphicObjectFromURL
#include <bf_svx/unoapi.hxx>
// header for SvxChartDataDescrItem
#ifndef _SVX_CHRTITEM_HXX
#define ITEMID_CHARTDATADESCR   SCHATTR_DATADESCR_DESCR

#include <bf_svtools/eitem.hxx>

#endif

#include "ChXDiagram.hxx"
#include "ChXChartAxis.hxx"
#include "ChXDataRow.hxx"
#include "ChXDataPoint.hxx"
#include "ChartTitle.hxx"
#include "ChartLine.hxx"
#include "ChartArea.hxx"
#include "ChartGrid.hxx"

#include "mapprov.hxx"

#include "schattr.hxx"
#include "charttyp.hxx"
#include "chtscene.hxx"
#include "docshell.hxx"

#include <bf_svx/unoshape.hxx>
// for OWN_ATTR_...
#include <bf_svx/unoshprp.hxx>
// for SID_ATTR_...
#include <bf_svx/svxids.hrc>
#include <rtl/uuid.h>
#include <rtl/memory.h>
// header for any2enum
#include <comphelper/extract.hxx>

#include <com/sun/star/chart/ChartDataRowSource.hpp>
#include <com/sun/star/chart/ChartErrorCategory.hpp>
#include <com/sun/star/chart/ChartErrorIndicatorType.hpp>
#include <com/sun/star/chart/ChartRegressionCurveType.hpp>
#include <com/sun/star/chart/ChartDataCaption.hpp>

#include <rtl/logfile.hxx>

#include "pairs.hxx"
#include "unonames.hxx"

namespace
{
::binfilter::ChartScene * lcl_GetScene( ::binfilter::ChartModel * pModel )
{
    ::binfilter::ChartScene * pScene = NULL;

    if( pModel && pModel->IsReal3D() )
    {
        if( ! pModel->IsInitialized())
            pModel->Initialize();
        pScene = pModel->GetScene();
    }

    return pScene;
}
} // anonymous namespace


namespace binfilter {

using namespace ::com::sun::star;
using namespace ::com::sun::star::uno;
using namespace ::com::sun::star::beans;

using rtl::OUString;

extern SchUnoPropertyMapProvider aSchMapProvider;

#if defined(MACOSX) && ( __GNUC__ < 3 )
static cppu::ClassData14 cppu::ImplHelper14::s_aCD;
static cppu::ClassData14 cppu::WeakImplHelper14::s_aCD;
#endif

#define MATRIX4D_TO_HOMOGEN_MATRIX( m, h ) \
    h.Line1.Column1 = m[0][0]; \
    h.Line1.Column2 = m[0][1]; \
    h.Line1.Column3 = m[0][2]; \
    h.Line1.Column4 = m[0][3]; \
    h.Line2.Column1 = m[1][0]; \
    h.Line2.Column2 = m[1][1]; \
    h.Line2.Column3 = m[1][2]; \
    h.Line2.Column4 = m[1][3]; \
    h.Line3.Column1 = m[2][0]; \
    h.Line3.Column2 = m[2][1]; \
    h.Line3.Column3 = m[2][2]; \
    h.Line3.Column4 = m[2][3]; \
    h.Line4.Column1 = m[3][0]; \
    h.Line4.Column2 = m[3][1]; \
    h.Line4.Column3 = m[3][2]; \
    h.Line4.Column4 = m[3][3]

#define	HOMOGEN_MATRIX_TO_MATRIX4D( h, m ) \
    m[0][0] = h.Line1.Column1; \
    m[0][1] = h.Line1.Column2; \
    m[0][2] = h.Line1.Column3; \
    m[0][3] = h.Line1.Column4; \
    m[1][0] = h.Line2.Column1; \
    m[1][1] = h.Line2.Column2; \
    m[1][2] = h.Line2.Column3; \
    m[1][3] = h.Line2.Column4; \
    m[2][0] = h.Line3.Column1; \
    m[2][1] = h.Line3.Column2; \
    m[2][2] = h.Line3.Column3; \
    m[2][3] = h.Line3.Column4; \
    m[3][0] = h.Line4.Column1; \
    m[3][1] = h.Line4.Column2; \
    m[3][2] = h.Line4.Column3; \
    m[3][3] = h.Line4.Column4

#define	CALL(object,interface,method)	{uno::Reference<interface>x(object,uno::UNO_QUERY); if(x.is())x.method();}
#define	CALL1(object,interface,method,arg1)	{uno::Reference<interface>x(object,uno::UNO_QUERY); if(x.is())x.method(arg1);}

inline	void	add_listener	(uno::Reference<uno::XInterface> xObject, ChXDiagram * p)
{
    if ( ! xObject.is())
        return;
    uno::Reference<lang::XComponent>	xComponent (xObject, uno::UNO_QUERY);
    if (xComponent.is())
        xComponent->addEventListener (p);
}

ChXDiagram::ChXDiagram( SchChartDocShell* pDocShell, sal_Bool bPreInit ) :
        mnBaseType( -1 ),
        mpModel( NULL ),
        maPropSet( aSchMapProvider.GetMap( CHMAP_CHART, NULL )),
        maListenerList (maMutex)
{
    if( bPreInit )
    {
        DBG_ASSERT( pDocShell, "Cannot do PreInit when using invalid DocShell." );
        SetDocShell( pDocShell );
    }
}

ChXDiagram::~ChXDiagram() {}

// bKeepModel = sal_True => try to keep model. If model is invalid take the one from DocShell
sal_Bool ChXDiagram::SetDocShell( SchChartDocShell* pDocShell, sal_Bool bKeepModel ) throw()
{
    SolarMutexGuard aGuard;
    sal_Bool bModelKept = sal_False;

    if( pDocShell )
    {
        if( bKeepModel && mpModel )
        {
            // copy current model
            ChartModel* pModel = SAL_STATIC_CAST( ChartModel*, mpModel->AllocModel());
            if( pModel )
            {
                pDocShell->SetModelPtr( pModel );
                if( ! pModel->SetObjectShell( pDocShell ))
                {
                    OSL_FAIL( "Couldn't set docshell" );
                }

                delete mpModel;
                mpModel = pModel;
                bModelKept = sal_True;
            }
        }
        else
        {
            // use model of new DocShell
            mpModel = pDocShell->GetModelPtr();
            if( ! bKeepModel && mpModel )
            {
                maPropSet = SvxItemPropertySet( aSchMapProvider.GetMap( CHMAP_CHART, mpModel ));
                maServiceName = getDiagramType();
            }
        }
    }
    else
        mpModel = NULL;

    return bModelKept;
}

// generate a uniqueId
const uno::Sequence< sal_Int8 > & ChXDiagram::getUnoTunnelId() throw()
{
    static uno::Sequence< sal_Int8 > * pSeq = 0;
    if( !pSeq )
    {
        osl::Guard< osl::Mutex > aGuard( osl::Mutex::getGlobalMutex() );
        if( !pSeq )
        {
            static uno::Sequence< sal_Int8 > aSeq( 16 );
            rtl_createUuid( (sal_uInt8*)aSeq.getArray(), 0, sal_True );
            pSeq = &aSeq;
        }
    }
    return *pSeq;
}

ChXDiagram* ChXDiagram::getImplementation( uno::Reference< uno::XInterface > xData ) throw()
{
    uno::Reference< lang::XUnoTunnel > xUT( xData, uno::UNO_QUERY );
    if( xUT.is() )
        return (ChXDiagram*)xUT->getSomething( ChXDiagram::getUnoTunnelId() );
    else
        return NULL;
}

uno::Any ChXDiagram::GetAnyByItem( SfxItemSet& aSet, const SfxItemPropertyMap* pMap )
{
    DBG_ASSERT( pMap, "GetAnyByItem: invalid Map!" );
    DBG_ASSERT( mpModel, "GetAnyByItem: invalid Model!" );

    uno::Any aAny;

    switch( pMap->nWID )
    {
        case CHATTR_DATA_SWITCH:	// BM: SwitchData is enum now
            {
                sal_Bool bIsOn = SAL_STATIC_CAST( const SfxBoolItem&, aSet.Get( CHATTR_DATA_SWITCH ) ).GetValue();
                chart::ChartDataRowSource eRowSource =
                    bIsOn ? chart::ChartDataRowSource_COLUMNS : chart::ChartDataRowSource_ROWS;
                aAny <<= eRowSource;
            }
            break;

        case SCHATTR_STYLE_SHAPE:
            aAny <<= SAL_STATIC_CAST( sal_Int32, mpModel->GetChartShapeType() );
            break;

        case SCHATTR_DATADESCR_DESCR:
            {
                BOOL bShowSymbol = ((const SfxBoolItem&)
                                    (aSet.Get(SCHATTR_DATADESCR_SHOW_SYM))).GetValue();
                SvxChartDataDescr eDescr = ((const SvxChartDataDescrItem&)
                                            (aSet.Get(SCHATTR_DATADESCR_DESCR))).GetValue();

                sal_Int32 nVal = 0;
                switch( eDescr )
                {
                    case CHDESCR_NONE:
                        nVal = chart::ChartDataCaption::NONE;
                        break;
                    case CHDESCR_VALUE:
                        nVal = chart::ChartDataCaption::VALUE;
                        break;
                    case CHDESCR_PERCENT:
                        nVal = chart::ChartDataCaption::PERCENT;
                        break;
                    case CHDESCR_TEXT:
                        nVal = chart::ChartDataCaption::TEXT;
                        break;
                    case CHDESCR_TEXTANDPERCENT:
                        nVal = chart::ChartDataCaption::PERCENT | chart::ChartDataCaption::TEXT;
                        break;
                    case CHDESCR_TEXTANDVALUE:
                        nVal = chart::ChartDataCaption::VALUE | chart::ChartDataCaption::TEXT;
                        break;
                    default:
                        break;
                }
                if( bShowSymbol ) nVal |= chart::ChartDataCaption::SYMBOL;

                aAny <<= nVal;
            }
            break;

        case SCHATTR_SYMBOL_BRUSH:
            {
                ::rtl::OUString aURL;
                const BfGraphicObject* pGraphObj =
                    ((const SvxBrushItem &)(aSet.Get( SCHATTR_SYMBOL_BRUSH ))).GetGraphicObject();
                if( pGraphObj )
                {
                    aURL = ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM( UNO_NAME_GRAPHOBJ_URLPREFIX ));
                    aURL += ::rtl::OUString::createFromAscii( pGraphObj->GetUniqueID().GetBuffer());
                }
                aAny <<= aURL;
            }
            break;

        default:
            aAny = maPropSet.getPropertyValue( pMap, aSet );

            if( *pMap->pType != aAny.getValueType() )
            {
                // since the sfx uint16 item now exports a sal_Int32, we may have to fix this here
                if( ( *pMap->pType == ::getCppuType((const sal_Int16*)0)) && aAny.getValueType() == ::getCppuType((const sal_Int32*)0) )
                {
                    sal_Int32 nValue(0);
                    aAny >>= nValue;
                    aAny <<= static_cast< sal_Int16 >( nValue );
                }
                else if( ( *pMap->pType == ::getCppuType((const sal_uInt16*)0)) && aAny.getValueType() == ::getCppuType((const sal_Int32*)0) )
                {
                    sal_Int32 nValue(0);
                    aAny >>= nValue;
                    aAny <<= static_cast< sal_uInt16 >( nValue );
                }
                else
                {
                    OSL_TRACE( "GetAnyByItem(): wrong Type!" );
                    OSL_FAIL( "GetAnyByItem(): wrong Type!" );
                }
            }
    }
    return aAny;
}

// XDiagram
::rtl::OUString SAL_CALL ChXDiagram::getDiagramType() throw( uno::RuntimeException )
{
    if( maServiceName.getLength() &&
        mpModel &&
        mnBaseType == mpModel->GetBaseType() )
    {
        return maServiceName;
    }

      SolarMutexGuard aGuard;

    if( mpModel )
    {
        mnBaseType = mpModel->GetBaseType();
        switch( mnBaseType )
        {
            case CHTYPE_LINE:
                maServiceName = ::rtl::OUString( RTL_CONSTASCII_USTRINGPARAM( SCH_X_STR_CHTYPE_NAMESPACE SCH_X_STR_CHTYPE_LINE ));
                break;
            case CHTYPE_AREA:
                maServiceName = ::rtl::OUString( RTL_CONSTASCII_USTRINGPARAM( SCH_X_STR_CHTYPE_NAMESPACE SCH_X_STR_CHTYPE_AREA ));
                break;
            case CHTYPE_DONUT :
                maServiceName = ::rtl::OUString( RTL_CONSTASCII_USTRINGPARAM( SCH_X_STR_CHTYPE_NAMESPACE SCH_X_STR_CHTYPE_DONUT ));
                break;
            case CHTYPE_COLUMN:		// is also treated as (vertical) bar chart
            case CHTYPE_BAR :
                maServiceName = ::rtl::OUString( RTL_CONSTASCII_USTRINGPARAM( SCH_X_STR_CHTYPE_NAMESPACE SCH_X_STR_CHTYPE_BAR ));
                break;
            case CHTYPE_CIRCLE :
                maServiceName = ::rtl::OUString( RTL_CONSTASCII_USTRINGPARAM( SCH_X_STR_CHTYPE_NAMESPACE SCH_X_STR_CHTYPE_PIE ));
                break;
            case CHTYPE_XY :
                maServiceName = ::rtl::OUString( RTL_CONSTASCII_USTRINGPARAM( SCH_X_STR_CHTYPE_NAMESPACE SCH_X_STR_CHTYPE_XY ));
                break;
            case CHTYPE_NET :
                maServiceName = ::rtl::OUString( RTL_CONSTASCII_USTRINGPARAM( SCH_X_STR_CHTYPE_NAMESPACE SCH_X_STR_CHTYPE_NET ));
                break;
            case CHTYPE_STOCK :
                maServiceName = ::rtl::OUString( RTL_CONSTASCII_USTRINGPARAM( SCH_X_STR_CHTYPE_NAMESPACE SCH_X_STR_CHTYPE_STOCK ));
                break;
            case CHTYPE_ADDIN :
                // when we get here we know that maServiceName.getLength() == 0
                OSL_FAIL( "Addin with empty name !" );
                break;
        }
        return maServiceName;
    }
    else
    {
        OSL_FAIL( "No Model" );
    }
    return SCH_ASCII_TO_OU( "UnknownChartType" );
}

uno::Reference< beans::XPropertySet > SAL_CALL ChXDiagram::getDataRowProperties( sal_Int32 Row )
    throw( uno::RuntimeException, lang::IndexOutOfBoundsException )
{
    SolarMutexGuard aGuard;

    if( mpModel )
    {
        if( Row >= 0 &&
             Row < mpModel->GetRowCount() )
        {
            ChXDataRow* pRet = new ChXDataRow( Row, mpModel );
            return uno::Reference< beans::XPropertySet >( SAL_STATIC_CAST( beans::XPropertySet*, pRet ));
        }
        else
        {
            ::rtl::OUString aMessage( RTL_CONSTASCII_USTRINGPARAM( "DataRowProperties: Invalid Index " ));
            aMessage += ::rtl::OUString::valueOf( Row );
            lang::IndexOutOfBoundsException aEx( aMessage, (::cppu::OWeakObject*)this );
            throw aEx;
        }
    }
    else
    {
        OSL_FAIL( "No Model" );
    }

    return uno::Reference< beans::XPropertySet >();
}

uno::Reference< beans::XPropertySet > SAL_CALL ChXDiagram::getDataPointProperties( sal_Int32 Column, sal_Int32 Row )
    throw( uno::RuntimeException, lang::IndexOutOfBoundsException )
{
    SolarMutexGuard aGuard;

    if( mpModel )
    {
        if( Row >= 0 && Column >= 0 &&
             (Row < mpModel->GetRowCount()) &&
             (Column < mpModel->GetColCount()) )
        {
            ChXDataPoint* pRet = new ChXDataPoint( Column, Row, mpModel );
            return uno::Reference< beans::XPropertySet >( SAL_STATIC_CAST( beans::XPropertySet*, pRet ));
        }
        else
        {
            ::rtl::OUString aMessage( RTL_CONSTASCII_USTRINGPARAM( "DataPointProperties: Invalid Index (col, row): " ));
            aMessage += ::rtl::OUString::valueOf( Column );
            aMessage += ::rtl::OUString( RTL_CONSTASCII_USTRINGPARAM( ", " ));
            aMessage += ::rtl::OUString::valueOf( Row );
            lang::IndexOutOfBoundsException aEx( aMessage, (::cppu::OWeakObject*)this );
            throw aEx;
        }
    }
    else
    {
        OSL_FAIL( "No Model" );
    }

    return uno::Reference< beans::XPropertySet >();
}

// XShape ( ::XDiagram)
awt::Size SAL_CALL ChXDiagram::getSize() throw( uno::RuntimeException )
{
    SolarMutexGuard aGuard;

    if( mpModel )
    {
        Size aSize = mpModel->GetChartRect().GetSize();
        return awt::Size( aSize.Width(), aSize.Height() );
    }
    else
        return awt::Size( 0, 0 );
}

void SAL_CALL ChXDiagram::setSize( const awt::Size& aSize )
    throw( uno::RuntimeException,
           beans::PropertyVetoException )
{
    SolarMutexGuard aGuard;
    if( mpModel )
    {
        Rectangle aRect = mpModel->GetChartRect();
        Size aOldSize = aRect.GetSize();
        if( aOldSize.Width() != aSize.Width ||
            aOldSize.Height() != aSize.Height )
        {
            mpModel->SetUseRelativePositions( TRUE );
            mpModel->SetDiagramHasBeenMovedOrResized( TRUE );
            aRect.SetSize( Size( aSize.Width, aSize.Height ) );
            mpModel->SetChartRect( aRect );
            mpModel->BuildChart( FALSE );
        }
    }
    else
    {
        OSL_FAIL( "No Model" );
    }
}

awt::Point SAL_CALL ChXDiagram::getPosition() throw( uno::RuntimeException )
{
    SolarMutexGuard aGuard;
    if( mpModel )
    {
        Point aPoint = mpModel->GetChartRect().TopLeft();
        return awt::Point( aPoint.X(), aPoint.Y() );
    }
    else
    {
        OSL_FAIL( "No Model" );
    }
    return awt::Point( 0, 0 );
}

void SAL_CALL ChXDiagram::setPosition( const awt::Point& aPosition ) throw( uno::RuntimeException )
{
    SolarMutexGuard aGuard;

    if( mpModel )
    {
        Rectangle aRect=mpModel->GetChartRect();
        Point aUpperLeft = aRect.TopLeft();
        if( aUpperLeft.X() != aPosition.X ||
            aUpperLeft.Y() != aPosition.Y )
        {
            mpModel->SetUseRelativePositions( TRUE );
            mpModel->SetDiagramHasBeenMovedOrResized( TRUE );
            aRect.SetPos( Point( aPosition.X, aPosition.Y ) );
            mpModel->SetChartRect( aRect );
            mpModel->BuildChart( FALSE );
        }
    }
    else
    {
        OSL_FAIL( "No Model" );
    }
}

// XShapeDescriptor ( ::XShape ::XDiagram )
::rtl::OUString SAL_CALL ChXDiagram::getShapeType() throw( uno::RuntimeException )
{
    return SCH_ASCII_TO_OU( "com.sun.star.chart.Diagram" );
}

// XAxisXSupplier, XAxisYSupplier, XAxisZSupplier,
// XTwoAxisXSupplier, XTwoAxisYSupplier
uno::Reference< drawing::XShape > SAL_CALL ChXDiagram::getXAxisTitle()
    throw( uno::RuntimeException )
{
    if( ! mxXAxisTitle.is())
    {
        mxXAxisTitle = new ChartTitle( mpModel, CHOBJID_DIAGRAM_TITLE_X_AXIS );
        add_listener (mxXAxisTitle, this);
    }

    return mxXAxisTitle;
}

uno::Reference< drawing::XShape > SAL_CALL ChXDiagram::getYAxisTitle()
    throw( uno::RuntimeException )
{
    if( ! mxYAxisTitle.is())
    {
        mxYAxisTitle = new ChartTitle( mpModel, CHOBJID_DIAGRAM_TITLE_Y_AXIS );
        add_listener (mxYAxisTitle, this);
    }

    return mxYAxisTitle;
}

uno::Reference< drawing::XShape > SAL_CALL ChXDiagram::getZAxisTitle()
    throw( uno::RuntimeException )
{
    if( ! mxZAxisTitle.is())
    {
        mxZAxisTitle = new ChartTitle( mpModel, CHOBJID_DIAGRAM_TITLE_Z_AXIS );
        add_listener (mxZAxisTitle, this);
    }

    return mxZAxisTitle;
}

uno::Reference< beans::XPropertySet > SAL_CALL ChXDiagram::getXAxis() throw( ::com::sun::star::uno::RuntimeException )
{
    if( ! mxXAxis.is())
    {
        mxXAxis = new ChXChartAxis( mpModel, CHOBJID_DIAGRAM_X_AXIS );
        add_listener (mxXAxis, this);
    }
    
    return mxXAxis;
}
uno::Reference< beans::XPropertySet > SAL_CALL ChXDiagram::getYAxis() throw( ::com::sun::star::uno::RuntimeException )
{
    if( ! mxYAxis.is())
    {
        mxYAxis = new ChXChartAxis( mpModel, CHOBJID_DIAGRAM_Y_AXIS );
        add_listener (mxYAxis, this);
    }
    
    return mxYAxis;
}
uno::Reference< beans::XPropertySet > SAL_CALL ChXDiagram::getZAxis() throw( ::com::sun::star::uno::RuntimeException )
{
    if( ! mxZAxis.is())
    {
        mxZAxis = new ChXChartAxis( mpModel, CHOBJID_DIAGRAM_Z_AXIS );
        add_listener (mxZAxis, this);
    }
    
    return mxZAxis;
}
uno::Reference< beans::XPropertySet > SAL_CALL ChXDiagram::getSecondaryXAxis() throw( ::com::sun::star::uno::RuntimeException )
{
    if( ! mxSecXAxis.is())
    {
        mxSecXAxis = new ChXChartAxis( mpModel, CHOBJID_DIAGRAM_A_AXIS );
        add_listener (mxSecXAxis, this);
    }
    
    return mxSecXAxis;
}
uno::Reference< beans::XPropertySet > SAL_CALL ChXDiagram::getSecondaryYAxis() throw( ::com::sun::star::uno::RuntimeException )
{
    if( ! mxSecYAxis.is())
    {
        mxSecYAxis = new ChXChartAxis( mpModel, CHOBJID_DIAGRAM_B_AXIS );
        add_listener (mxSecYAxis, this);
    }
    
    return mxSecYAxis;
}
uno::Reference< beans::XPropertySet > SAL_CALL ChXDiagram::getXMainGrid() throw( ::com::sun::star::uno::RuntimeException )
{
    // attention: x and y grids are interchanged
    if( ! mxMajorGridX.is())
    {
        mxMajorGridX = new ChartGrid( mpModel, CHOBJID_DIAGRAM_Y_GRID_MAIN_GROUP );
        add_listener (mxMajorGridX, this);
    }
    
    return mxMajorGridX;
}
uno::Reference< beans::XPropertySet > SAL_CALL ChXDiagram::getYMainGrid() throw( ::com::sun::star::uno::RuntimeException )
{
    // attention: x and y grids are interchanged
    if( ! mxMajorGridY.is())
    {
        mxMajorGridY = new ChartGrid( mpModel, CHOBJID_DIAGRAM_X_GRID_MAIN_GROUP );
        add_listener (mxMajorGridY, this);
    }
    
    return mxMajorGridY;
}
uno::Reference< beans::XPropertySet > SAL_CALL ChXDiagram::getZMainGrid() throw( ::com::sun::star::uno::RuntimeException )
{
    if( ! mxMajorGridZ.is())
    {
        mxMajorGridZ = new ChartGrid( mpModel, CHOBJID_DIAGRAM_Z_GRID_MAIN_GROUP );
        add_listener (mxMajorGridZ, this);
    }
    
    return mxMajorGridZ;
}
uno::Reference< beans::XPropertySet > SAL_CALL ChXDiagram::getXHelpGrid() throw( ::com::sun::star::uno::RuntimeException )
{
    // attention: x and y grids are interchanged
    if( ! mxMinorGridX.is())
    {
        mxMinorGridX = new ChartGrid( mpModel, CHOBJID_DIAGRAM_Y_GRID_HELP_GROUP );
        add_listener (mxMinorGridX, this);
    }
    
    return mxMinorGridX;
}
uno::Reference< beans::XPropertySet > SAL_CALL ChXDiagram::getYHelpGrid() throw( ::com::sun::star::uno::RuntimeException )
{
    // attention: x and y grids are interchanged
    if( ! mxMinorGridY.is())
    {
        mxMinorGridY = new ChartGrid( mpModel, CHOBJID_DIAGRAM_X_GRID_HELP_GROUP );
        add_listener (mxMinorGridY, this);
    }
    
    return mxMinorGridY;
}
uno::Reference< beans::XPropertySet > SAL_CALL ChXDiagram::getZHelpGrid() throw( ::com::sun::star::uno::RuntimeException )
{
    if( ! mxMinorGridZ.is())
    {
        mxMinorGridZ = new ChartGrid( mpModel, CHOBJID_DIAGRAM_Z_GRID_HELP_GROUP );
        add_listener (mxMinorGridZ, this);
    }
    
    return mxMinorGridZ;
}

// XStatisticDisplay
uno::Reference< beans::XPropertySet > SAL_CALL ChXDiagram::getMinMaxLine() throw( ::com::sun::star::uno::RuntimeException )
{
    if( ! mxMinMaxLine.is())
    {
        mxMinMaxLine = new ChartLine( mpModel, CHOBJID_DIAGRAM_STOCKLINE_GROUP );
        add_listener (mxMinMaxLine, this);
    }
    
    return mxMinMaxLine;
}
uno::Reference< beans::XPropertySet > SAL_CALL ChXDiagram::getUpBar() throw( ::com::sun::star::uno::RuntimeException )
{
    if( ! mxUpBar.is())
    {
        mxUpBar = new ChartArea( mpModel, CHOBJID_DIAGRAM_STOCKPLUS_GROUP );
        add_listener (mxUpBar, this);
    }
    
    return mxUpBar;
}
uno::Reference< beans::XPropertySet > SAL_CALL ChXDiagram::getDownBar() throw( ::com::sun::star::uno::RuntimeException )
{
    if( ! mxDownBar.is())
    {
        mxDownBar = new ChartArea( mpModel, CHOBJID_DIAGRAM_STOCKLOSS_GROUP );
        add_listener (mxDownBar, this);
    }
    
    return mxDownBar;
}

// X3DDisplay
uno::Reference< beans::XPropertySet > SAL_CALL ChXDiagram::getFloor() throw( ::com::sun::star::uno::RuntimeException )
{
    if( ! mxFloor.is())
    {
        mxFloor = new ChartArea( mpModel, CHOBJID_DIAGRAM_FLOOR );
        add_listener (mxFloor, this);
    }
    
    return mxFloor;
}
// note: this method is also valid for 2d charts
uno::Reference< beans::XPropertySet > SAL_CALL ChXDiagram::getWall() throw( ::com::sun::star::uno::RuntimeException )
{
    if( ! mxWall.is())
    {
        mxWall = new ChartArea( mpModel, CHOBJID_DIAGRAM_WALL );
        add_listener (mxWall, this);
    }
    
    return mxWall;
}


// XPropertySet
uno::Reference< beans::XPropertySetInfo > SAL_CALL ChXDiagram::getPropertySetInfo() throw( uno::RuntimeException )
{
    SolarMutexGuard aGuard;
    return maPropSet.getPropertySetInfo();
}

// needed for camera geometry
struct ImpRememberTransAndRect
{
    Matrix4D					maMat;
    Rectangle					maRect;
};

void SAL_CALL ChXDiagram::setPropertyValue( const ::rtl::OUString& aPropertyName, const uno::Any& aValue )
        throw( beans::UnknownPropertyException,
               beans::PropertyVetoException,
               lang::IllegalArgumentException,
               lang::WrappedTargetException,
               uno::RuntimeException )
{
    SolarMutexGuard aGuard;

    if( mpModel )
    {
        const SfxItemPropertyMap* pMap = maPropSet.getPropertyMapEntry( aPropertyName );

        if( pMap && pMap->nWID )
        {
            if( pMap->nFlags & PropertyAttribute::READONLY )
                throw PropertyVetoException();

            USHORT nWID = pMap->nWID;
            sal_Int32 nVal(0);

            SfxItemSet* pSet;
            switch( nWID )
            {
                case SCHATTR_DATADESCR_DESCR:
                case SCHATTR_DATADESCR_SHOW_SYM:
                    // the Property DataCaption needs two Which Ids
                    pSet = new SfxItemSet( mpModel->GetItemPool(),
                                           SCHATTR_DATADESCR_DESCR, SCHATTR_DATADESCR_DESCR,
                                           SCHATTR_DATADESCR_SHOW_SYM, SCHATTR_DATADESCR_SHOW_SYM, 0 );
                    break;

                case CHATTR_NUM_OF_LINES_FOR_BAR:
                    {
                        aValue >>= nVal;
                        if( mpModel->GetBaseType() == CHTYPE_COLUMN )
                            mpModel->SetNumLinesColChart( nVal, TRUE );
                        mpModel->BuildChart( FALSE );
                        return;									// RETURN
                    }

                case CHATTR_SPLINE_ORDER:
                    {
                        aValue >>= nVal;
                        // for some reason the value internally is one more
                        // ie order 1 is linear but is stores as 2 in the core
                        ++nVal;
                        mpModel->SplineDepth() = nVal;
                        if( mpModel->IsSplineChart())
                            mpModel->BuildChart( FALSE );
                        return;                                 // RETURN
                    }

                case CHATTR_SPLINE_RESOLUTION:
                    {
                        aValue >>= nVal;
                        mpModel->Granularity() = nVal;
                        if( mpModel->IsSplineChart())
                            mpModel->BuildChart( FALSE );
                        return;                                 // RETURN
                    }

                case SCHATTR_STYLE_STACKED:
                case SCHATTR_STYLE_PERCENT:
                    pSet = new SfxItemSet( mpModel->GetItemPool(),
                                           SCHATTR_STYLE_STACKED, SCHATTR_STYLE_STACKED,
                                           SCHATTR_STYLE_PERCENT, SCHATTR_STYLE_PERCENT, 0 );
                    break;

                case SCHATTR_STYLE_DEEP:
                    // deep implies 3d
                    pSet = new SfxItemSet( mpModel->GetItemPool(),
                                           SCHATTR_STYLE_DEEP, SCHATTR_STYLE_DEEP,
                                           SCHATTR_STYLE_3D, SCHATTR_STYLE_3D, 0 );                    
                    break;

                case OWN_ATTR_3D_VALUE_TRANSFORM_MATRIX:
                    {
                        E3dObject* pScene = lcl_GetScene( mpModel );

                        if( pScene )
                        {
                            drawing::HomogenMatrix xHomMatrix;
                            aValue >>= xHomMatrix;
                            Matrix4D aMtx;
                            HOMOGEN_MATRIX_TO_MATRIX4D( xHomMatrix, aMtx );
                            pScene->SetTransform( aMtx );
                        }
                        return;	// RETURN
                    }

                case OWN_ATTR_3D_VALUE_CAMERA_GEOMETRY:
                    {
                        E3dScene* pScene = lcl_GetScene( mpModel );

                        if( pScene )
                        {
                            drawing::CameraGeometry aCamGeo;

                            if(aValue >>= aCamGeo)
                            {
                                Vector3D aVRP(aCamGeo.vrp.PositionX, aCamGeo.vrp.PositionY, aCamGeo.vrp.PositionZ);
                                Vector3D aVPN(aCamGeo.vpn.DirectionX, aCamGeo.vpn.DirectionY, aCamGeo.vpn.DirectionZ);
                                Vector3D aVUP(aCamGeo.vup.DirectionX, aCamGeo.vup.DirectionY, aCamGeo.vup.DirectionZ);

                                // rescue scene transformation
                                ImpRememberTransAndRect aSceneTAR;
                                aSceneTAR.maMat = pScene->GetTransform();
                                aSceneTAR.maRect = pScene->GetSnapRect();

                                // fill old camera from new parameters
                                Camera3D aCam(pScene->GetCamera());
                                const Volume3D& rVolume = pScene->GetBoundVolume();
                                double fW = rVolume.GetWidth();
                                double fH = rVolume.GetHeight();
                                double fCamPosZ = 
                                    (double)((const SfxUInt32Item&)pScene->GetItem(SDRATTR_3DSCENE_DISTANCE)).GetValue();
                                double fCamFocal = 
                                    (double)((const SfxUInt32Item&)pScene->GetItem(SDRATTR_3DSCENE_FOCAL_LENGTH)).GetValue();

                                aCam.SetAutoAdjustProjection(FALSE);
                                aCam.SetViewWindow(- fW / 2, - fH / 2, fW, fH);
                                Vector3D aLookAt;
                                Vector3D aCamPos(0.0, 0.0, fCamPosZ);
                                aCam.SetPosAndLookAt(aCamPos, aLookAt);
                                aCam.SetFocalLength(fCamFocal / 100.0);
                                aCam.SetDefaults(Vector3D(0.0, 0.0, fCamPosZ), aLookAt, fCamFocal / 100.0);
                                aCam.SetDeviceWindow(Rectangle(0, 0, (long)fW, (long)fH));

                                // set at scene
                                pScene->SetCamera(aCam);

                                // set scene transformation again at scene
                                pScene->NbcSetTransform(aSceneTAR.maMat);
                                pScene->FitSnapRectToBoundVol();
                                pScene->NbcSetSnapRect(aSceneTAR.maRect);
                            }
                        }
                        return;	// RETURN
                    }

                default:
                    pSet = new SfxItemSet( mpModel->GetPool(), nWID, nWID );
            }

            // fill item: (should be optimized)
            ChartType aType( mpModel );
            aType.GetAttrSet( pSet );
            mpModel->GetAttr( *pSet );

            if( !pSet->Count() )
            {
                // get default from ItemPool
                if( mpModel->GetItemPool().IsWhich( nWID ) )
                {
                    pSet->Put( mpModel->GetItemPool().GetDefaultItem( pMap->nWID ) );
                }
                else
                {
#ifdef DBG_UTIL
                    String aTmpString( aPropertyName );
                    ByteString aProp( aTmpString, RTL_TEXTENCODING_ASCII_US );
                    DBG_ERROR2( "Diagram: Property %s has an invalid ID (%d)", aProp.GetBuffer(), nWID );
#endif
                }
            }

            if( pSet->Count() )
            {
                switch( nWID )
                {
                    case SCHATTR_STAT_KIND_ERROR:
                        {
                            chart::ChartErrorCategory eCat;
                            cppu::any2enum< chart::ChartErrorCategory >( eCat, aValue );
                            pSet->Put( SfxInt32Item( nWID, SAL_STATIC_CAST( sal_Int32, eCat )));
                            break;
                        }
                    case SCHATTR_STAT_INDICATE:
                        {
                            chart::ChartErrorIndicatorType eInd;
                            cppu::any2enum< chart::ChartErrorIndicatorType >( eInd, aValue );
                            pSet->Put( SfxInt32Item( nWID, SAL_STATIC_CAST( sal_Int32, eInd )));
                            break;
                        }
                    case SCHATTR_STAT_REGRESSTYPE:
                        {
                            chart::ChartRegressionCurveType eRegType;
                            cppu::any2enum< chart::ChartRegressionCurveType >( eRegType, aValue );
                            pSet->Put( SfxInt32Item( nWID, SAL_STATIC_CAST( sal_Int32, eRegType )));
                            break;
                        }
                    case CHATTR_DATA_SWITCH:
                        {
                            chart::ChartDataRowSource eRowSource;
                            cppu::any2enum< chart::ChartDataRowSource >( eRowSource, aValue );
                            mpModel->ChangeSwitchData( (chart::ChartDataRowSource_COLUMNS == eRowSource) );
                            return;
                        }
                    case SCHATTR_DATADESCR_DESCR:
                        {
                            // symbol
                            sal_Int32 nLclVal(0);
                            aValue >>= nLclVal;
                            pSet->Put( SfxBoolItem( SCHATTR_DATADESCR_SHOW_SYM,
                                                    ((nLclVal & chart::ChartDataCaption::SYMBOL) != 0)) );

                            // display text, percent or both or value
                            SvxChartDataDescr eDescr = CHDESCR_NONE;
                            if( nLclVal & chart::ChartDataCaption::TEXT )
                            {
                                if( nLclVal & chart::ChartDataCaption::PERCENT )
                                    eDescr = CHDESCR_TEXTANDPERCENT;
                                else if( (nLclVal & chart::ChartDataCaption::VALUE) )
                                    eDescr = CHDESCR_TEXTANDVALUE;
                                else
                                    eDescr = CHDESCR_TEXT;
                            }
                            else if( (nLclVal & chart::ChartDataCaption::VALUE) )
                            {
                                eDescr = CHDESCR_VALUE;
                            }
                            else
                            {
                                if( (nLclVal & chart::ChartDataCaption::PERCENT) )
                                    eDescr = CHDESCR_PERCENT;
                            }

                            // chart::ChartDataCaption::FORMAT (missing)

                            pSet->Put( SvxChartDataDescrItem( eDescr ) );
                        }
                        break;

                    case XATTR_FILLBITMAP:
                    case XATTR_FILLGRADIENT:
                    case XATTR_FILLHATCH:
                    case XATTR_FILLFLOATTRANSPARENCE:
                    case XATTR_LINEEND:
                    case XATTR_LINESTART:
                    case XATTR_LINEDASH:
                        if( pMap->nMemberId == MID_NAME )
                        {
                            ::rtl::OUString aStr;
                            if( aValue >>= aStr )
                                SvxShape::SetFillAttribute( nWID, aStr, *pSet, mpModel );
                        }
                        else
                            maPropSet.setPropertyValue( pMap, aValue, *pSet );
                        break;

                    case SCHATTR_STYLE_STACKED:
                    case SCHATTR_STYLE_PERCENT:
                        {
                            sal_Bool bSet(sal_False);
                            aValue >>= bSet;
                            if( bSet )
                            {
                                // setting of these two items is exclusive
                                BOOL bStacked = ( nWID == SCHATTR_STYLE_STACKED );

                                pSet->Put( SfxBoolItem( SCHATTR_STYLE_STACKED, bStacked ));
                                pSet->Put( SfxBoolItem( SCHATTR_STYLE_PERCENT, ! bStacked ));
                            }
                            else
                            {
                                // setting either of both properties to FALSE
                                // sets both to FALSE
                                pSet->Put( SfxBoolItem( SCHATTR_STYLE_STACKED, FALSE ));
                                pSet->Put( SfxBoolItem( SCHATTR_STYLE_PERCENT, FALSE ));
                            }
                        }
                        break;

                    case SCHATTR_STYLE_DEEP:
                        {
                            sal_Bool bSet(sal_False);
                            aValue >>= bSet;

                            // if deep is turned on, 3d must also be set
                            if( bSet )
                            {
                                pSet->Put( SfxBoolItem( SCHATTR_STYLE_3D, TRUE ));
                            }
                            pSet->Put( SfxBoolItem( SCHATTR_STYLE_DEEP, bSet ));
                        }
                        break;

                    case SCHATTR_SYMBOL_BRUSH:
                        {
                            ::rtl::OUString aURL;
                            aValue >>= aURL;
                            BfGraphicObject aGraphObj = CreateGraphicObjectFromURL( aURL );
                            SvxBrushItem aItem( SCHATTR_SYMBOL_BRUSH );
                            aItem.SetGraphic( aGraphObj.GetGraphic() );
                            pSet->Put( aItem );
                        }
                        break;

                    default:
                        maPropSet.setPropertyValue( pMap, aValue, *pSet );
                        break;
                }
                aType.SetType( pSet );
                mpModel->PutAttr( *pSet );
                if( nWID == SCHATTR_SYMBOL_SIZE )
                {
                    mpModel->PutDataRowAttrAll( *pSet );
                }

                if( mpModel->ChangeChart( aType.GetChartStyle(), false ))
                {
                    mpModel->BuildChart( FALSE );
                }
                else if( ! mpModel->ChangeStatistics ( *pSet ) )
                {
                    mpModel->BuildChart( FALSE );
                }
            }
            else
            {
                throw beans::UnknownPropertyException();
            }
            delete pSet;
        }
        else
        {
            throw beans::UnknownPropertyException();
        }
    }
    else
    {
        DBG_WARNING( "No Model" );
    }
}

uno::Any SAL_CALL ChXDiagram::getPropertyValue( const ::rtl::OUString& PropertyName )
    throw( beans::UnknownPropertyException,
           lang::WrappedTargetException,
           uno::RuntimeException )
{
    RTL_LOGFILE_CONTEXT (context, "sch (af119097) ::ChXDiagram::getPropertyValue");
    SolarMutexGuard aGuard;

    uno::Any aAny;

    if( mpModel )
    {
        const SfxItemPropertyMap* pMap = maPropSet.getPropertyMapEntry( PropertyName );

        if( pMap && pMap->nWID )
        {
            USHORT nWID = pMap->nWID;
            SfxItemSet* pSet;

            if( nWID == SCHATTR_STYLE_SHAPE &&
                ! mpModel->IsReal3D())
                return aAny;

            switch( nWID )
            {
                case CHATTR_NUM_OF_LINES_FOR_BAR:
                    aAny <<= SAL_STATIC_CAST( sal_Int32, mpModel->GetNumLinesColChart() );
                    return aAny;			  // RETURN

                case SCHATTR_DATADESCR_DESCR:
                    pSet = new SfxItemSet( mpModel->GetItemPool(),
                                           SCHATTR_DATADESCR_DESCR, SCHATTR_DATADESCR_DESCR,
                                           SCHATTR_DATADESCR_SHOW_SYM, SCHATTR_DATADESCR_SHOW_SYM, 0 );
                    break;

                case CHATTR_SPLINE_ORDER:
                    // for some reason the value internally is one more
                    // ie order 1 is linear but is stores as 2 in the core
                    aAny <<= static_cast< sal_Int32 >( mpModel->SplineDepth() - 1 );
                    return aAny;

                case CHATTR_SPLINE_RESOLUTION:
                    aAny <<= static_cast< sal_Int32 >( mpModel->Granularity() );
                    return aAny;

                case CHATTR_ATTRIBUTED_DATA_POINTS:
                    aAny <<= mpModel->GetSetDataPointList();
                    return aAny;

                default:
                    pSet = new SfxItemSet( mpModel->GetItemPool(), nWID, nWID );
            }

            // set attributes
            if( nWID == SCHATTR_SYMBOL_BRUSH ||
                nWID == SCHATTR_SYMBOL_SIZE )
            {
                mpModel->GetDataRowAttrAll( *pSet );
            }
            else
            {
                ChartType aType( mpModel );
                aType.GetAttrSet( pSet );
                mpModel->GetAttr( *pSet );	// copy SHOW_HIDE_PROPERTIES into ItemSet
            }

            if( ! pSet->Count() )
            {
                // get default from ItemPool
                if( mpModel->GetItemPool().IsWhich( nWID ) )
                {
                    if( ! ( OWN_ATTR_VALUE_START <= nWID && nWID <= OWN_ATTR_VALUE_END ))	// properties from SvxShape
                    {
                        pSet->Put( mpModel->GetItemPool().GetDefaultItem( nWID ) );
                    }
                    // 3d properties that have no corresponding item but come from drawing layer
                    else
                    {
                        //E3dPolyScene* mpModel->GetScene();
                        E3dObject* pScene = lcl_GetScene( mpModel );
                        if( pScene )
                        {
                            if( nWID == OWN_ATTR_3D_VALUE_TRANSFORM_MATRIX )
                            {
                                const Matrix4D& aMtx = pScene->GetFullTransform();
                                drawing::HomogenMatrix xHomMatrix;
                                MATRIX4D_TO_HOMOGEN_MATRIX( aMtx, xHomMatrix );
                                aAny <<= xHomMatrix;

                                return aAny;	// RETURN
                            }
                            else if( nWID == OWN_ATTR_3D_VALUE_CAMERA_GEOMETRY )
                            {
                                // get CameraGeometry from scene
                                 E3dScene* pE3dScene = mpModel->GetScene();
                                drawing::CameraGeometry aCamGeo;

                                // fill Vectors from scene camera
                                B3dCamera& aCameraSet = pE3dScene->GetCameraSet();
                                Vector3D aVRP = aCameraSet.GetVRP();
                                Vector3D aVPN = aCameraSet.GetVPN();
                                Vector3D aVUP = aCameraSet.GetVUV();

                                // transfer to structure
                                aCamGeo.vrp.PositionX = aVRP.X();
                                aCamGeo.vrp.PositionY = aVRP.Y();
                                aCamGeo.vrp.PositionZ = aVRP.Z();
                                aCamGeo.vpn.DirectionX = aVPN.X();
                                aCamGeo.vpn.DirectionY = aVPN.Y();
                                aCamGeo.vpn.DirectionZ = aVPN.Z();
                                aCamGeo.vup.DirectionX = aVUP.X();
                                aCamGeo.vup.DirectionY = aVUP.Y();
                                aCamGeo.vup.DirectionZ = aVUP.Z();

                                return uno::Any(&aCamGeo, ::getCppuType((const drawing::CameraGeometry*)0) );
                            }
                        }
                    }
                }
                else
                {
#ifdef DBG_UTIL
                    String aTmpString( PropertyName );
                    ByteString aProp( aTmpString, RTL_TEXTENCODING_ASCII_US );
                    DBG_ERROR2( "Diagram: Property %s has an invalid ID (%d)", aProp.GetBuffer(), nWID );
#endif
                }
            }

            if( pSet->Count() )
            {
                aAny = GetAnyByItem( *pSet, pMap );
            }
            else
                throw beans::UnknownPropertyException();

            delete pSet;
        }
        else
            throw beans::UnknownPropertyException();
    }
    else
    {
        OSL_FAIL( "No Model" );
    }
    return aAny;
}

void SAL_CALL ChXDiagram::addPropertyChangeListener( const ::rtl::OUString& /*aPropertyName*/,
                                                     const uno::Reference< beans::XPropertyChangeListener >& /*xListener*/ )
    throw( beans::UnknownPropertyException,
           lang::WrappedTargetException,
           uno::RuntimeException )
{}

void SAL_CALL ChXDiagram::removePropertyChangeListener( const ::rtl::OUString& /*aPropertyName*/,
                                                        const uno::Reference< beans::XPropertyChangeListener >& /*aListener*/ )
    throw( beans::UnknownPropertyException,
           lang::WrappedTargetException,
           uno::RuntimeException )
{}

void SAL_CALL ChXDiagram::addVetoableChangeListener( const ::rtl::OUString& /*PropertyName*/,
                                                     const uno::Reference< beans::XVetoableChangeListener >& /*aListener*/ )
    throw( beans::UnknownPropertyException,
           lang::WrappedTargetException,
           uno::RuntimeException )
{}

void SAL_CALL ChXDiagram::removeVetoableChangeListener( const ::rtl::OUString& /*PropertyName*/,
                                                        const uno::Reference< beans::XVetoableChangeListener >& /*aListener*/ )
    throw( beans::UnknownPropertyException,
           lang::WrappedTargetException,
           uno::RuntimeException )
{}


//=====  XMultiPropertySet  ===================================================

void SAL_CALL	ChXDiagram::setPropertyValues (
    const Sequence< ::rtl::OUString >&	aPropertyNames,
    const Sequence<Any >&		aValues) 
    throw (beans::PropertyVetoException, 
            lang::IllegalArgumentException,
            lang::WrappedTargetException,
            uno::RuntimeException)
{
    RTL_LOGFILE_CONTEXT (context2, "sch (af119097) ::ChXDiagram::setPropertyValues");
#if 1
    for (sal_Int32 i=0; i<aPropertyNames.getLength(); i++)
        setPropertyValue (aPropertyNames[i], aValues[i]);
#endif
}


Sequence<Any> SAL_CALL	ChXDiagram::getPropertyValues (
    const Sequence<OUString>& aPropertyNames) 
    throw (RuntimeException)
{
    RTL_LOGFILE_CONTEXT (context, "sch (af119097) ::ChXDiagram::getPropertyValues");
    SolarMutexGuard aGuard;
    
    //	This sequence is filled with the requested values for the given property names.
    Sequence<Any> aResult (aPropertyNames.getLength());
    
    //	Get pointers to first elements of lists.
    const SfxItemPropertyMap *	pProperty = maPropSet.getPropertyMap ();
    const OUString * pPropertyName = aPropertyNames.getConstArray ();
    Any * pPropertyValue = aResult.getArray ();
    
    //	Check preconditions.
    if (mpModel == NULL)
        throw UnknownPropertyException (OUString (
            RTL_CONSTASCII_USTRINGPARAM ("No model in ::ChXDiagram::getPropertyValues")),
            static_cast< ::cppu::OWeakObject*>(this));

    //	Get the models attributes.
    SfxItemSet aAttributes (mpModel->GetItemPool(),
        CHART_ROW_WHICHPAIRS,
        OWN_ATTR_VALUE_START, OWN_ATTR_VALUE_END,
        OWN_ATTR_FILLBMP_MODE, OWN_ATTR_FILLBMP_MODE,
        SCHATTR_STOCK_VOLUME, SCHATTR_STOCK_UPDOWN,
        CHATTR_START, CHATTR_END,
        CHATTR_TMP_START, CHATTR_TMP_END,
        0);

    mpModel->GetDataRowAttrAll (aAttributes);
    //	else
    ChartType aType (mpModel);
    aType.GetAttrSet (&aAttributes);
    mpModel->GetAttr (aAttributes);

    //	Used in the loop below.
    USHORT		nWID;
    E3dObject*	pScene = NULL;
    BOOL		bTryAgain;
    OUString	sMessage;

    //	Iterate over all given property names.		
    sal_Int32 nCounter = aPropertyNames.getLength();
    while (nCounter-- > 0)
    {
        AdvanceToName (pProperty, pPropertyName);

        nWID = pProperty->nWID;
        bTryAgain = TRUE;
        
        //	Handling each property is divided into three steps:
        //	1.	Handle special cases that do not depend on items.
        //	2.	If the required item is not set, then try to get a 
        //		default value.  Handle 3D properties here.
        //	3.	Try again if the item is now set in the hope that its
        //		status has been changed in step 2.
        
        //	Step 1
        if (nWID == SCHATTR_STYLE_SHAPE && ! mpModel->IsReal3D())
        {
            //	Leave the property value unchanged.
            bTryAgain = FALSE;
        }
        else if (nWID == CHATTR_NUM_OF_LINES_FOR_BAR)
        {
            *pPropertyValue <<= static_cast<sal_Int32>(mpModel->GetNumLinesColChart());
            bTryAgain = FALSE;
        }
        else if( nWID ==  CHATTR_SPLINE_ORDER )
        {
            // for some reason the value internally is one more
            // ie order 1 is linear but is stores as 2 in the core
            *pPropertyValue <<= static_cast< sal_Int32 >( mpModel->SplineDepth() - 1 );
            bTryAgain = FALSE;
        }
        else if( nWID == CHATTR_SPLINE_RESOLUTION )
        {
            *pPropertyValue <<= static_cast< sal_Int32 >( mpModel->Granularity() );
            bTryAgain = FALSE;
        }
        
        //	Step 2
        else if (aAttributes.GetItemState (nWID, sal_False) != SFX_ITEM_SET)
        {
            bTryAgain = FALSE;
            if ( ! mpModel->GetItemPool().IsWhich(nWID))
            {
            }
            else if (nWID < OWN_ATTR_VALUE_START || nWID > OWN_ATTR_VALUE_END)
            {
                // properties from SvxShape
                aAttributes.Put (mpModel->GetItemPool().GetDefaultItem (nWID));
                //	Set the flag to try again to read the item.
                bTryAgain = TRUE;
            }
            else
            {
                if (pScene == NULL)
                {
                    RTL_LOGFILE_CONTEXT_TRACE (context, "getting 3D scene");
                    pScene = lcl_GetScene( mpModel );
                }
                if (pScene != NULL)
                {
                    if (nWID == OWN_ATTR_3D_VALUE_TRANSFORM_MATRIX)
                    {
                        const Matrix4D& aMtx = pScene->GetFullTransform();
                        drawing::HomogenMatrix xHomMatrix;
                        MATRIX4D_TO_HOMOGEN_MATRIX (aMtx, xHomMatrix);
                        *pPropertyValue <<= xHomMatrix;
                    }
                    else if (nWID == OWN_ATTR_3D_VALUE_CAMERA_GEOMETRY)
                    {
                        // get CameraGeometry from scene
                         E3dScene* pE3dScene = mpModel->GetScene();

                        // fill Vectors from scene camera
                        B3dCamera& aCameraSet = pE3dScene->GetCameraSet();
                        Vector3D aVRP = aCameraSet.GetVRP();
                        Vector3D aVPN = aCameraSet.GetVPN();
                        Vector3D aVUP = aCameraSet.GetVUV();

                        // transfer to structure
                        drawing::CameraGeometry aCamGeo;
                        aCamGeo.vrp.PositionX = aVRP.X();
                        aCamGeo.vrp.PositionY = aVRP.Y();
                        aCamGeo.vrp.PositionZ = aVRP.Z();
                        aCamGeo.vpn.DirectionX = aVPN.X();
                        aCamGeo.vpn.DirectionY = aVPN.Y();
                        aCamGeo.vpn.DirectionZ = aVPN.Z();
                        aCamGeo.vup.DirectionX = aVUP.X();
                        aCamGeo.vup.DirectionY = aVUP.Y();
                        aCamGeo.vup.DirectionZ = aVUP.Z();
    
                        *pPropertyValue = 
                            Any (&aCamGeo, ::getCppuType((const drawing::CameraGeometry*)0));
                    }
                    else
                        bTryAgain = TRUE;
                }
            }
        }

        //	Step3		
        if (bTryAgain)
        {
            if (aAttributes.GetItemState (nWID, sal_False) == SFX_ITEM_SET)
            {
                *pPropertyValue = GetAnyByItem (aAttributes, pProperty);
            }
            else
            {
                //	Construct a message for an exception but wait with throwing
                //	it until all known properies have been set.
                if (sMessage.getLength() == 0)
                {
                    sMessage = OUString (RTL_CONSTASCII_USTRINGPARAM ("Property "));
                    sMessage += *pPropertyName;
                    sMessage += OUString (
                        RTL_CONSTASCII_USTRINGPARAM (" is not known in :ChXDiagram::getPropertyValues"));
                }
#ifdef DBG_UTIL
                ByteString sName = ByteString(String(*pPropertyName), RTL_TEXTENCODING_ASCII_US);
                DBG_ERROR2 ("Diagram: Property %s has an invalid ID (%d)",
                    sName.GetBuffer(), nWID);
#endif
            }
        }

        //	Advance to the next property, property name and value.
        pPropertyName++;
        pPropertyValue++;
    }
    
    //	Throw an exception if one of the properties was unknown.
    if (sMessage.getLength() > 0)
        throw UnknownPropertyException (sMessage,
            static_cast< ::cppu::OWeakObject*>(this));

    return aResult;
}


void SAL_CALL	ChXDiagram::addPropertiesChangeListener	(
    const Sequence<OUString >& /*aPropertyNames*/,
    const Reference<beans::XPropertiesChangeListener >&	/*xListener*/) 
    throw (RuntimeException)
{
    //	Not implemented.
}

void SAL_CALL	ChXDiagram::removePropertiesChangeListener (
    const Reference<beans::XPropertiesChangeListener>& /*xListener*/) 
    throw (RuntimeException)
{
    //	Not implemented.
}


void SAL_CALL	ChXDiagram::firePropertiesChangeEvent (
    const Sequence<OUString >& /*aPropertyNames*/,
    const Reference<beans::XPropertiesChangeListener >&	/*xListener*/)
    throw (RuntimeException)
{
    //	Not implemented.
}




//=====  XPropertyState  ======================================================

beans::PropertyState SAL_CALL ChXDiagram::getPropertyState( const ::rtl::OUString& PropertyName )
    throw( beans::UnknownPropertyException, uno::RuntimeException )
{
    if( mpModel )
    {
        const SfxItemPropertyMap* pMap = maPropSet.getPropertyMapEntry( PropertyName );

        if( pMap && pMap->nWID )
        {
            switch( pMap->nWID )
            {
                case SCHATTR_STYLE_PERCENT:
                    {
                        ChartType aType( mpModel );
                        return ( aType.IsPercent()
                                 ? beans::PropertyState_DIRECT_VALUE
                                 : beans::PropertyState_DEFAULT_VALUE );
                    }
                    break;
                case SCHATTR_STYLE_STACKED:
                    {
                        ChartType aType( mpModel );
                        return ( ( ! aType.IsPercent() &&
                                     aType.IsStacked())
                                 ? beans::PropertyState_DIRECT_VALUE
                                 : beans::PropertyState_DEFAULT_VALUE );
                    }
                    break;

                case CHATTR_SPLINE_ORDER:
                case CHATTR_SPLINE_RESOLUTION:
                    {
                        ChartType aType( mpModel );
                        return ( ( aType.HasSplines() )
                                 ? beans::PropertyState_DIRECT_VALUE
                                 : beans::PropertyState_DEFAULT_VALUE );
                    }

                case CHATTR_NUM_OF_LINES_FOR_BAR:
                case SCHATTR_STYLE_SHAPE:
                case SCHATTR_DATADESCR_DESCR:
                    break;

                default:
                    {
                        SolarMutexGuard aGuard;

                        SfxItemSet aSet( mpModel->GetItemPool(), pMap->nWID, pMap->nWID );
                        ChartType aType( mpModel );
                        aType.GetAttrSet( &aSet );
                        mpModel->GetAttr( aSet );

                        SfxItemState eState = aSet.GetItemState( pMap->nWID );
                        if( eState == SFX_ITEM_DEFAULT )
                            return beans::PropertyState_DEFAULT_VALUE;
                        else if( eState < SFX_ITEM_DEFAULT )
                            return beans::PropertyState_AMBIGUOUS_VALUE;
                        else
                            return beans::PropertyState_DIRECT_VALUE;
                    }
            }
        }
    }

    return beans::PropertyState_DIRECT_VALUE;
}


void SAL_CALL ChXDiagram::setPropertyToDefault( const ::rtl::OUString& PropertyName )
        throw( beans::UnknownPropertyException,
               uno::RuntimeException )
{
    SolarMutexGuard aGuard;

    const SfxItemPropertyMap* pMap = maPropSet.getPropertyMapEntry( PropertyName );

    if( pMap && pMap->nWID &&
        ( pMap->nWID == CHATTR_NUM_OF_LINES_FOR_BAR ||
          pMap->nWID == CHATTR_SPLINE_ORDER ||
          pMap->nWID == CHATTR_SPLINE_RESOLUTION ||
          pMap->nWID == SCHATTR_STYLE_SHAPE ||
          pMap->nWID == SCHATTR_DATADESCR_DESCR ))
    {
        return;
    }

    if( mpModel )
    {
        SfxItemSet aSet( mpModel->GetItemPool(), pMap->nWID, pMap->nWID );
        ChartType aType( mpModel );
        aType.GetAttrSet( &aSet );
        mpModel->GetAttr( aSet );

        aSet.ClearItem( pMap->nWID );

        aType.SetType( &aSet );
        mpModel->PutAttr( aSet );

        if( mpModel->ChangeChart( aType.GetChartStyle(), false ))
        {
            mpModel->BuildChart( FALSE );
        }
        else if( ! mpModel->ChangeStatistics ( aSet ) )
        {
            mpModel->BuildChart( FALSE );
        }
    }
}

uno::Any SAL_CALL ChXDiagram::getPropertyDefault( const ::rtl::OUString& aPropertyName )
        throw( beans::UnknownPropertyException,
               lang::WrappedTargetException,
               uno::RuntimeException )
{
    const SfxItemPropertyMap* pMap = maPropSet.getPropertyMapEntry( aPropertyName );

    if( pMap && pMap->nWID &&
        ( pMap->nWID == CHATTR_NUM_OF_LINES_FOR_BAR ||
          pMap->nWID == CHATTR_SPLINE_ORDER ||
          pMap->nWID == CHATTR_SPLINE_RESOLUTION ||
          pMap->nWID == SCHATTR_STYLE_SHAPE ||
          pMap->nWID == SCHATTR_DATADESCR_DESCR ))
    {
        return getPropertyValue( aPropertyName );
    }

    if( ! mpModel->GetItemPool().IsWhich( pMap->nWID ))
        throw beans::UnknownPropertyException();

    SfxItemSet aSet( mpModel->GetItemPool(), pMap->nWID, pMap->nWID );
    aSet.Put( mpModel->GetItemPool().GetDefaultItem( pMap->nWID ));

    return GetAnyByItem( aSet, pMap );
}




//====  XMultiPropertyStates  =================================================

Sequence<PropertyState> SAL_CALL ChXDiagram::getPropertyStates (
    const Sequence<OUString >& aPropertyName)
    throw (beans::UnknownPropertyException,
            uno::RuntimeException)
{
    SolarMutexGuard aGuard;

    //	New implementation.

    //	Setup arrays of property names and states for easier iteration.
    sal_Int32 nPropertyCount = aPropertyName.getLength();
    const OUString* pPropertyName = aPropertyName.getConstArray();
    Sequence<PropertyState> aPropertyStates (nPropertyCount);
    PropertyState* pPropertyState = aPropertyStates.getArray();
    const SfxItemPropertyMap * pProperty = maPropSet.getPropertyMap ();

    //	Check preconditions.	
    if (mpModel == NULL)
        return aPropertyStates;

    //	Get the models attributes.
    ChartType aType (mpModel);

    //	This needs still a bit of work.  What is the best set of which id ranges?
    SfxItemSet aAttributes (mpModel->GetItemPool(),
        CHART_ROW_WHICHPAIRS,
        OWN_ATTR_FILLBMP_MODE, OWN_ATTR_FILLBMP_MODE, 	// 3945 bf_svx/unoshprp.hxx
        30689,30689,									//	RID_SCH_START + 177 ?
        30720,30720,									//	RID_SCH_START + 208 ?
        SCHATTR_STOCK_VOLUME, SCHATTR_STOCK_UPDOWN,
        0);
    aType.GetAttrSet (&aAttributes);
    mpModel->GetAttr (aAttributes);

    //	Variable used in the loop below.
    USHORT nWID;
    //	Setting this error message to a non empty string results throwing an exception
    //	after the main loop has finished.
    OUString sErrorMessage;
    
    //	Iterate over all given property names.
    while (nPropertyCount-- > 0)
    {
        AdvanceToName (pProperty, pPropertyName);

        switch (nWID = pProperty->nWID)
        {
            case	SCHATTR_STYLE_PERCENT:
                if (aType.IsPercent())
                    *pPropertyState = PropertyState_DIRECT_VALUE;
                else
                    *pPropertyState = PropertyState_DEFAULT_VALUE;
                break;
            
            case	SCHATTR_STYLE_STACKED:
                if (aType.IsStacked() && ! aType.IsPercent())
                    *pPropertyState = PropertyState_DIRECT_VALUE;
                else
                    *pPropertyState = PropertyState_DEFAULT_VALUE;
                break;

            case    CHATTR_SPLINE_ORDER:
            case    CHATTR_SPLINE_RESOLUTION:
                if( aType.HasSplines())
                    *pPropertyState = PropertyState_DIRECT_VALUE;
                else
                    *pPropertyState = PropertyState_DEFAULT_VALUE;
                break;

            case	CHATTR_NUM_OF_LINES_FOR_BAR:
            case	SCHATTR_STYLE_SHAPE:
            case	SCHATTR_DATADESCR_DESCR:
                *pPropertyState = PropertyState_DIRECT_VALUE;
                break;

            default:
                switch (aAttributes.GetItemState (nWID, sal_False))
                {
                    case SFX_ITEM_DONTCARE:
                    case SFX_ITEM_DISABLED:
                        *pPropertyState = PropertyState_AMBIGUOUS_VALUE;
                        break;
                        
                    case SFX_ITEM_READONLY:
                    case SFX_ITEM_SET:
                        *pPropertyState = PropertyState_DIRECT_VALUE;
                        break;
                        
                    case SFX_ITEM_DEFAULT:
                        *pPropertyState = PropertyState_DEFAULT_VALUE;
                        break;
                        
                    case SFX_ITEM_UNKNOWN:
                    default:
                        //	Set the error message so that it can be used
                        //	to create an exception object after the loop
                        //	has finished.
                        //	The exception is not thrown here in order
                        //	to first process as many properties as possible.
                        //	All unknown properties following the first one
                        //	are ignored.
                        OSL_TRACE("nWID %d not in property set", nWID);
                        if (sErrorMessage.getLength() == 0)
                        {
                            sErrorMessage = OUString (
                                RTL_CONSTASCII_USTRINGPARAM ("Chart Object: Unknown Property "));
                            sErrorMessage += *pPropertyName;
                        }
                }
        }
        pPropertyName ++;
        pPropertyState ++;
    }
    
    //	Now throw an exception if there has been an unknown property.
    if (sErrorMessage.getLength() > 0)
        throw UnknownPropertyException (sErrorMessage,
            static_cast< ::cppu::OWeakObject*>(this));
            
    return aPropertyStates;
}


void SAL_CALL	ChXDiagram::setAllPropertiesToDefault (void)
    throw (RuntimeException)
{
    OSL_FAIL("ChXChartObject::setAllPropertiesToDefault");
}


void SAL_CALL	ChXDiagram::setPropertiesToDefault (
    const Sequence<OUString >& aPropertyNames)
    throw (beans::UnknownPropertyException,
            RuntimeException)
{
    for (sal_Int32 i=0; i<aPropertyNames.getLength(); i++)
    {
        setPropertyToDefault (aPropertyNames[i]);
    }
}


Sequence<Any> SAL_CALL	ChXDiagram::getPropertyDefaults	(
    const Sequence<OUString>& aPropertyNames) 
    throw (beans::UnknownPropertyException, 
            lang::WrappedTargetException, 
            RuntimeException)
{
    Sequence<Any>	aResult (aPropertyNames.getLength());
    
    for (sal_Int32 i=0; i<aPropertyNames.getLength(); i++)
    {
        aResult[i] = getPropertyDefault (aPropertyNames[i]);
    }
    
    return aResult;
}



//=====  XServiceInfo  ========================================================
::rtl::OUString SAL_CALL ChXDiagram::getImplementationName() throw( uno::RuntimeException )
{
    return SCH_ASCII_TO_OU( "ChXDiagram" );
}

sal_Bool SAL_CALL ChXDiagram::supportsService( const ::rtl::OUString& ServiceName )
    throw( uno::RuntimeException )
{
    return SvxServiceInfoHelper::supportsService( ServiceName, getSupportedServiceNames() );
}

uno::Sequence< ::rtl::OUString > SAL_CALL ChXDiagram::getSupportedServiceNames() throw( uno::RuntimeException )
{
    uno::Sequence< ::rtl::OUString > aSeq;
    SvxServiceInfoHelper::addToSequence(
        aSeq, 2,
        "com.sun.star.chart.Diagram",
        "com.sun.star.xml.UserDefinedAttributeSupplier" );
    if( mpModel )
    {
        long nType = mpModel->GetBaseType();
        switch( nType )
        {
            case CHTYPE_LINE:
                SvxServiceInfoHelper::addToSequence(
                    aSeq, 9,
                    "com.sun.star.chart.LineDiagram",
                    "com.sun.star.chart.ChartStatistics",
                    "com.sun.star.chart.ChartAxisXSupplier",
                    "com.sun.star.chart.ChartTwoAxisXSupplier",
                    "com.sun.star.chart.ChartAxisYSupplier",
                    "com.sun.star.chart.ChartTwoAxisYSupplier",
                    "com.sun.star.chart.StackableDiagram",
                    "com.sun.star.chart.Dim3DDiagram",
                    "com.sun.star.chart.ChartAxisZSupplier" );
                break;
            case CHTYPE_AREA:
                SvxServiceInfoHelper::addToSequence(
                    aSeq, 9,
                    "com.sun.star.chart.AreaDiagram",
                    "com.sun.star.chart.ChartStatistics",
                    "com.sun.star.chart.ChartAxisXSupplier",
                    "com.sun.star.chart.ChartTwoAxisXSupplier",
                    "com.sun.star.chart.ChartAxisYSupplier",
                    "com.sun.star.chart.ChartTwoAxisYSupplier",
                    "com.sun.star.chart.StackableDiagram",
                    "com.sun.star.chart.Dim3DDiagram",
                    "com.sun.star.chart.ChartAxisZSupplier" );
            break;
            case CHTYPE_DONUT :
                SvxServiceInfoHelper::addToSequence( aSeq, 1, "com.sun.star.chart.DonutDiagram" );
                break;
            case CHTYPE_COLUMN : // also treated as bar chart
            case CHTYPE_BAR :
                SvxServiceInfoHelper::addToSequence(
                    aSeq, 9,
                    "com.sun.star.chart.BarDiagram",
                    "com.sun.star.chart.ChartStatistics",
                    "com.sun.star.chart.ChartAxisXSupplier",
                    "com.sun.star.chart.ChartTwoAxisXSupplier",
                    "com.sun.star.chart.ChartAxisYSupplier",
                    "com.sun.star.chart.ChartTwoAxisYSupplier",
                    "com.sun.star.chart.StackableDiagram",
                    "com.sun.star.chart.Dim3DDiagram",
                    "com.sun.star.chart.ChartAxisZSupplier" );
                break;
            case CHTYPE_CIRCLE :
                SvxServiceInfoHelper::addToSequence(
                    aSeq, 2,
                    "com.sun.star.chart.PieDiagram",
                    "com.sun.star.chart.Dim3DDiagram");
                break;
            case CHTYPE_XY :
                SvxServiceInfoHelper::addToSequence(
                    aSeq, 7,
                    "com.sun.star.chart.XYDiagram",
                    "com.sun.star.chart.LineDiagram",
                    "com.sun.star.chart.ChartStatistics",
                    "com.sun.star.chart.ChartAxisXSupplier",
                    "com.sun.star.chart.ChartTwoAxisXSupplier",
                    "com.sun.star.chart.ChartAxisYSupplier",
                    "com.sun.star.chart.ChartTwoAxisYSupplier" );
                break;
            case CHTYPE_NET :
                SvxServiceInfoHelper::addToSequence(
                    aSeq, 3,
                    "com.sun.star.chart.NetDiagram",
                    "com.sun.star.chart.StackableDiagram",
                    "com.sun.star.chart.ChartAxisYSupplier" );
                break;
            case CHTYPE_STOCK :
                SvxServiceInfoHelper::addToSequence(
                    aSeq, 6,
                    "com.sun.star.chart.StockDiagram",
                    "com.sun.star.chart.ChartStatistics",
                    "com.sun.star.chart.ChartAxisXSupplier",
                    "com.sun.star.chart.ChartTwoAxisXSupplier",
                    "com.sun.star.chart.ChartAxisYSupplier",
                    "com.sun.star.chart.ChartTwoAxisYSupplier" );
                break;
        }
    }
    else
    {
        OSL_FAIL( "No Model" );
    }

    return aSeq;
}

// XUnoTunnel
sal_Int64 SAL_CALL ChXDiagram::getSomething( const uno::Sequence< sal_Int8 >& aIdentifier )
    throw( uno::RuntimeException )
{
    if( aIdentifier.getLength() == 16 && 0 == rtl_compareMemory( getUnoTunnelId().getConstArray(),
                                                                 aIdentifier.getConstArray(), 16 ) )
    {
        return (sal_Int64)this;
    }
    return 0;
}

// XComponent
void SAL_CALL ChXDiagram::dispose() throw( uno::RuntimeException )
{
    SolarMutexGuard aGuard;
  
    const int	nMemberListSize = 19;
    const uno::Reference<uno::XInterface> xMemberList[nMemberListSize] = {
        mxXAxisTitle, mxYAxisTitle, mxZAxisTitle,
        mxXAxis, mxYAxis, mxZAxis, mxSecXAxis, mxSecYAxis,
        mxMajorGridX, mxMajorGridY, mxMajorGridZ,
        mxMinorGridX, mxMinorGridY, mxMinorGridZ,
        mxMinMaxLine, mxUpBar, mxDownBar,
        mxWall, mxFloor};
    for (int i=0; i<nMemberListSize; i++)
        if (xMemberList[i].is())
        {
            uno::Reference<lang::XComponent> xComponent (xMemberList[i], uno::UNO_QUERY);
            if (xComponent.is())
            {
                xComponent->dispose();
                xComponent->removeEventListener (this);
            }
        }

    ::com::sun::star::lang::EventObject aEvent (*this);
    maListenerList.disposeAndClear (aEvent);
}

void SAL_CALL ChXDiagram::addEventListener( const uno::Reference< lang::XEventListener >& xListener )
    throw( uno::RuntimeException )
{
    maListenerList.addInterface (xListener);
}

void SAL_CALL ChXDiagram::removeEventListener( const uno::Reference< lang::XEventListener >& xListener )
    throw( uno::RuntimeException )
{
    maListenerList.removeInterface (xListener);
}




//	XEventListener
void SAL_CALL ChXDiagram::disposing (const ::com::sun::star::lang::EventObject & Source)
    throw (uno::RuntimeException)
{
    if (Source.Source == mxXAxisTitle)
        mxXAxisTitle = NULL;
    else if (Source.Source == mxYAxisTitle)
        mxYAxisTitle = NULL;
    else if (Source.Source == mxZAxisTitle)
        mxZAxisTitle = NULL;
    else if (Source.Source == mxXAxis)
        mxXAxis = NULL;
    else if (Source.Source == mxYAxis)
        mxYAxis = NULL;
    else if (Source.Source == mxZAxis)
        mxZAxis = NULL;
    else if (Source.Source == mxSecXAxis)
        mxSecXAxis = NULL;
    else if (Source.Source == mxSecYAxis)
        mxSecYAxis = NULL;
    else if (Source.Source == mxMajorGridX)
        mxMajorGridX = NULL;
    else if (Source.Source == mxMajorGridY)
        mxMajorGridY = NULL;
    else if (Source.Source == mxMajorGridZ)
        mxMajorGridZ = NULL;
    else if (Source.Source == mxMinorGridX)
        mxMinorGridX = NULL;
    else if (Source.Source == mxMinorGridY)
        mxMinorGridY = NULL;
    else if (Source.Source == mxMinorGridZ)
        mxMinorGridZ = NULL;
    else if (Source.Source == mxMinMaxLine)
        mxMinMaxLine = NULL;
    else if (Source.Source == mxUpBar)
        mxUpBar = NULL;
    else if (Source.Source == mxDownBar)
        mxDownBar = NULL;
    else if (Source.Source == mxWall)
        mxWall = NULL;
    else if (Source.Source == mxFloor)
        mxFloor = NULL;
}



//=====  protected methods  =======================================================================

void	ChXDiagram::AdvanceToName	(const SfxItemPropertyMap *& pProperty, 
                                    const OUString * pPropertyName)
                                    throw (::com::sun::star::beans::UnknownPropertyException)
{
    sal_Int32	nComparisonResult;

    //	Advance over the property list to the property with the current name.
    while ((nComparisonResult=pPropertyName->compareToAscii (pProperty->pName)) > 0)
    {
        pProperty++;
        if (pProperty->pName == NULL)
        {
            //	We reached the end of the property list.  Therefore all remaining given
            //	property names can not be found.
            OUString sMessage = OUString (
                RTL_CONSTASCII_USTRINGPARAM ("ChXChartObject::setPropertyValues: unknown property "));
            sMessage += *pPropertyName; 
            throw UnknownPropertyException (sMessage, (::cppu::OWeakObject*)this);
        }
    }
    if (nComparisonResult < 0)
    {
        //	All remaining given property names can not match any of the remaining properties
        //	because they lie alphabetically before them => Error
        OUString sMessage = OUString (
            RTL_CONSTASCII_USTRINGPARAM ("ChXChartObject::setPropertyValues: unknown property "));
        sMessage += *pPropertyName;
        throw UnknownPropertyException (sMessage, (::cppu::OWeakObject*)this);
    }
    
    //	If we reach this line then we have found the property with the name pPropertyName.
}


} //namespace binfilter

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
