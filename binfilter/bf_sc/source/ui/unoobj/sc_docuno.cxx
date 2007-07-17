/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: sc_docuno.cxx,v $
 *
 *  $Revision: 1.8 $
 *
 *  last change: $Author: obo $ $Date: 2007-07-17 09:33:49 $
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
#ifdef PCH
#endif

#pragma hdrstop

#include <com/sun/star/container/XIndexContainer.hpp>

#include <bf_svx/fmdpage.hxx>
#include <bf_svx/fmview.hxx>
#include <bf_svx/svdpage.hxx>

#include <svtools/numuno.hxx>
#include <vcl/waitobj.hxx>
#include <tools/multisel.hxx>
#include <toolkit/awt/vclxdevice.hxx>
#include <ctype.h>
#include <float.h>	// DBL_MAX

#include <com/sun/star/util/Date.hpp>

#include "cellsuno.hxx"
#include "nameuno.hxx"
#include "datauno.hxx"
#include "miscuno.hxx"
#include "notesuno.hxx"
#include "styleuno.hxx"
#include "linkuno.hxx"
#include "servuno.hxx"
#include "targuno.hxx"
#include "convuno.hxx"
#include "optuno.hxx"
#include "forbiuno.hxx"
#include "docsh.hxx"
#include "hints.hxx"
#include "docfunc.hxx"
#include "dociter.hxx"
#include "cell.hxx"
#include "drwlayer.hxx"
#include "unoguard.hxx"
#include "unonames.hxx"
#include "shapeuno.hxx"
#include "printfun.hxx"
#include "scmod.hxx"
#include "docsh.hxx"
#include "viewdata.hxx"

#ifndef _SC_VIEWSETTINGSSEQUENCEDEFINES_HXX
#include "ViewSettingsSequenceDefines.hxx"
#endif
#ifndef _LEGACYBINFILTERMGR_HXX
#include <legacysmgr/legacy_binfilters_smgr.hxx>	//STRIP002 
#endif
namespace binfilter {
using namespace ::com::sun::star;

#define TABLEID_DOC                0xFFFF

//------------------------------------------------------------------------

//	alles ohne Which-ID, Map nur fuer PropertySetInfo

//!	umbenennen, sind nicht mehr nur Options
const SfxItemPropertyMap* lcl_GetDocOptPropertyMap()
{
    static SfxItemPropertyMap aDocOptPropertyMap_Impl[] =
    {
        {MAP_CHAR_LEN(SC_UNO_APPLYFMDES),	0,	&getBooleanCppuType(),									  0},
        {MAP_CHAR_LEN(SC_UNO_AREALINKS),	0,	&getCppuType((uno::Reference<sheet::XAreaLinks>*)0),	  0},
        {MAP_CHAR_LEN(SC_UNO_AUTOCONTFOC),	0,	&getBooleanCppuType(),									  0},
        {MAP_CHAR_LEN(SC_UNO_BASICLIBRARIES),0, &getCppuType((uno::Reference< script::XLibraryContainer >*)0), beans::PropertyAttribute::READONLY},
        {MAP_CHAR_LEN(SC_UNO_CALCASSHOWN),	0,	&getBooleanCppuType(),									  0},
        {MAP_CHAR_LEN(SC_UNONAME_CLOCAL),	0,	&getCppuType((lang::Locale*)0),							  0},
        {MAP_CHAR_LEN(SC_UNO_CJK_CLOCAL),	0,	&getCppuType((lang::Locale*)0),							  0},
        {MAP_CHAR_LEN(SC_UNO_CTL_CLOCAL),	0,	&getCppuType((lang::Locale*)0),							  0},
        {MAP_CHAR_LEN(SC_UNO_COLLABELRNG),	0,	&getCppuType((uno::Reference<sheet::XLabelRanges>*)0),	  0},
        {MAP_CHAR_LEN(SC_UNO_DDELINKS),		0,	&getCppuType((uno::Reference<container::XNameAccess>*)0), 0},
        {MAP_CHAR_LEN(SC_UNO_DEFTABSTOP),	0,	&getCppuType((sal_Int16*)0),							  0},
        {MAP_CHAR_LEN(SC_UNO_FORBIDDEN),	0,	&getCppuType((uno::Reference<i18n::XForbiddenCharacters>*)0), beans::PropertyAttribute::READONLY},
        {MAP_CHAR_LEN(SC_UNO_HASDRAWPAGES),	0,	&getBooleanCppuType(),									  beans::PropertyAttribute::READONLY},
        {MAP_CHAR_LEN(SC_UNO_IGNORECASE),	0,	&getBooleanCppuType(),									  0},
        {MAP_CHAR_LEN(SC_UNO_ITERENABLED),	0,	&getBooleanCppuType(),									  0},
        {MAP_CHAR_LEN(SC_UNO_ITERCOUNT),	0,	&getCppuType((sal_Int32*)0),							  0},
        {MAP_CHAR_LEN(SC_UNO_ITEREPSILON),	0,	&getCppuType((double*)0),								  0},
        {MAP_CHAR_LEN(SC_UNO_LOOKUPLABELS),	0,	&getBooleanCppuType(),									  0},
        {MAP_CHAR_LEN(SC_UNO_MATCHWHOLE),	0,	&getBooleanCppuType(),									  0},
        {MAP_CHAR_LEN(SC_UNO_NAMEDRANGES),	0,	&getCppuType((uno::Reference<sheet::XNamedRanges>*)0),	  0},
        {MAP_CHAR_LEN(SC_UNO_DATABASERNG),	0,	&getCppuType((uno::Reference<sheet::XDatabaseRanges>*)0), 0},
        {MAP_CHAR_LEN(SC_UNO_NULLDATE),		0,	&getCppuType((util::Date*)0),							  0},
        {MAP_CHAR_LEN(SC_UNO_ROWLABELRNG),	0,	&getCppuType((uno::Reference<sheet::XLabelRanges>*)0),	  0},
        {MAP_CHAR_LEN(SC_UNO_SHEETLINKS),	0,	&getCppuType((uno::Reference<container::XNameAccess>*)0), 0},
        {MAP_CHAR_LEN(SC_UNO_SPELLONLINE),	0,	&getBooleanCppuType(),									  0},
        {MAP_CHAR_LEN(SC_UNO_STANDARDDEC),	0,	&getCppuType((sal_Int16*)0),							  0},
        {MAP_CHAR_LEN(SC_UNO_REGEXENABLED), 0,  &getBooleanCppuType(),                  0},

        {0,0,0,0}
    };
    return aDocOptPropertyMap_Impl;
}

//!	StandardDecimals als Property und vom NumberFormatter ????????

const SfxItemPropertyMap* lcl_GetColumnsPropertyMap()
{
    static SfxItemPropertyMap aColumnsPropertyMap_Impl[] =
    {
        {MAP_CHAR_LEN(SC_UNONAME_MANPAGE),	0,	&getBooleanCppuType(),			0, 0 },
        {MAP_CHAR_LEN(SC_UNONAME_NEWPAGE),	0,	&getBooleanCppuType(),			0, 0 },
        {MAP_CHAR_LEN(SC_UNONAME_CELLVIS),	0,	&getBooleanCppuType(),			0, 0 },
        {MAP_CHAR_LEN(SC_UNONAME_OWIDTH),	0,	&getBooleanCppuType(),			0, 0 },
        {MAP_CHAR_LEN(SC_UNONAME_CELLWID),	0,	&getCppuType((sal_Int32*)0),	0, 0 },
        {0,0,0,0}
    };
    return aColumnsPropertyMap_Impl;
}

const SfxItemPropertyMap* lcl_GetRowsPropertyMap()
{
    static SfxItemPropertyMap aRowsPropertyMap_Impl[] =
    {
        {MAP_CHAR_LEN(SC_UNONAME_CELLHGT),	0,	&getCppuType((sal_Int32*)0),	0, 0 },
        {MAP_CHAR_LEN(SC_UNONAME_CELLFILT),	0,	&getBooleanCppuType(),			0, 0 },
        {MAP_CHAR_LEN(SC_UNONAME_OHEIGHT),	0,	&getBooleanCppuType(),			0, 0 },
        {MAP_CHAR_LEN(SC_UNONAME_MANPAGE),	0,	&getBooleanCppuType(),			0, 0 },
        {MAP_CHAR_LEN(SC_UNONAME_NEWPAGE),	0,	&getBooleanCppuType(),			0, 0 },
        {MAP_CHAR_LEN(SC_UNONAME_CELLVIS),	0,	&getBooleanCppuType(),			0, 0 },
        {0,0,0,0}
    };
    return aRowsPropertyMap_Impl;
}

//!	move these functions to a header file
inline long TwipsToHMM(long nTwips)	{ return (nTwips * 127 + 36) / 72; }
inline long HMMToTwips(long nHMM)	{ return (nHMM * 72 + 63) / 127; }

//------------------------------------------------------------------------

#define SCMODELOBJ_SERVICE			"com.sun.star.sheet.SpreadsheetDocument"
#define SCDOCSETTINGS_SERVICE		"com.sun.star.sheet.SpreadsheetDocumentSettings"
#define SCDOC_SERVICE				"com.sun.star.document.OfficeDocument"

SC_SIMPLE_SERVICE_INFO( ScAnnotationsObj, "ScAnnotationsObj", "com.sun.star.sheet.CellAnnotations" )
SC_SIMPLE_SERVICE_INFO( ScDrawPagesObj, "ScDrawPagesObj", "com.sun.star.drawing.DrawPages" )
SC_SIMPLE_SERVICE_INFO( ScScenariosObj, "ScScenariosObj", "com.sun.star.sheet.Scenarios" )
SC_SIMPLE_SERVICE_INFO( ScSpreadsheetSettingsObj, "ScSpreadsheetSettingsObj", "com.sun.star.sheet.SpreadsheetDocumentSettings" )
SC_SIMPLE_SERVICE_INFO( ScTableColumnsObj, "ScTableColumnsObj", "com.sun.star.table.TableColumns" )
SC_SIMPLE_SERVICE_INFO( ScTableRowsObj, "ScTableRowsObj", "com.sun.star.table.TableRows" )
SC_SIMPLE_SERVICE_INFO( ScTableSheetsObj, "ScTableSheetsObj", "com.sun.star.sheet.Spreadsheets" )

//------------------------------------------------------------------------

String lcl_ColumnToString( USHORT nCol )		//! irgendwo global ???
{
    if ( nCol < 26 )
        return String( (sal_Unicode) ( 'A' + nCol ) );
    else if ( nCol <= MAXCOL )
    {
        String aStr( (sal_Unicode) ( 'A' + ( nCol / 26 ) - 1 ) );
        aStr += (sal_Unicode) ( 'A' + ( nCol % 26 ) );
        return aStr;
    }
    return '*';		//! oder #REF oder so ??
}

BOOL lcl_StringToColumn( const String& rStr, USHORT& rCol )		//! irgendwo global ???
{
    BOOL bOk = FALSE;
    sal_Unicode c = rStr.GetChar(0);
    if (CharClass::isAsciiAlpha(c))
    {
        USHORT nResult = toupper((sal_Char)c) - 'A';
        c = rStr.GetChar(1);
        if (CharClass::isAsciiAlpha(c))
            nResult = ((nResult + 1) * 26) + (toupper((sal_Char)c) - 'A');
        if (nResult <= MAXCOL)
        {
            rCol = nResult;
            bOk = TRUE;
        }
    }
    return bOk;
}

//------------------------------------------------------------------------

// static
void ScModelObj::CreateAndSet(ScDocShell* pDocSh)
{
    if (pDocSh)
        pDocSh->SetBaseModel( new ScModelObj(pDocSh) );
}

ScModelObj::ScModelObj( ScDocShell* pDocSh ) :
    SfxBaseModel( pDocSh ),
    aPropSet( lcl_GetDocOptPropertyMap() ),
    pDocShell( pDocSh ),
    pPrintFuncCache( NULL )
{
    // pDocShell may be NULL if this is the base of a ScDocOptionsObj
    if ( pDocShell )
    {
        pDocShell->GetDocument()->AddUnoObject(*this);		// SfxModel is derived from SfxListener

        // setDelegator veraendert den RefCount, darum eine Referenz selber halten
        // (direkt am m_refCount, um sich beim release nicht selbst zu loeschen)
        ::comphelper::increment( m_refCount );

        // waehrend des queryInterface braucht man ein Ref auf das
        // SvNumberFormatsSupplierObj, sonst wird es geloescht.
        uno::Reference<util::XNumberFormatsSupplier> xFormatter = new SvNumberFormatsSupplierObj(
                                                pDocShell->GetDocument()->GetFormatTable() );
        {
            xNumberAgg = uno::Reference<uno::XAggregation>( xFormatter, uno::UNO_QUERY );
            // extra block to force deletion of the temporary before setDelegator
        }

        // beim setDelegator darf die zusaetzliche Ref nicht mehr existieren
        xFormatter = NULL;

        if (xNumberAgg.is())
            xNumberAgg->setDelegator( (cppu::OWeakObject*)this );

        ::comphelper::decrement( m_refCount );
    }
}

ScModelObj::~ScModelObj()
{
    if (pDocShell)
        pDocShell->GetDocument()->RemoveUnoObject(*this);

    if (xNumberAgg.is())
        xNumberAgg->setDelegator(uno::Reference<uno::XInterface>());
}

ScDocument* ScModelObj::GetDocument() const
{
    if (pDocShell)
        return pDocShell->GetDocument();
    return NULL;
}

SvEmbeddedObject* ScModelObj::GetEmbeddedObject() const
{
    return pDocShell;
}

BOOL ScModelObj::AdjustRowHeight( USHORT nStartRow, USHORT nEndRow, USHORT nTab )
{
    if (pDocShell)
        return pDocShell->AdjustRowHeight( nStartRow, nEndRow, nTab );
    return FALSE;
}

void ScModelObj::BeforeXMLLoading()
{
    if (pDocShell)
        pDocShell->BeforeXMLLoading();
}

void ScModelObj::AfterXMLLoading(sal_Bool bRet)
{
    if (pDocShell)
        pDocShell->AfterXMLLoading(bRet);
}

uno::Any SAL_CALL ScModelObj::queryInterface( const uno::Type& rType )
                                                throw(uno::RuntimeException)
{
    SC_QUERYINTERFACE( sheet::XSpreadsheetDocument )
    SC_QUERYINTERFACE( document::XActionLockable )
    SC_QUERYINTERFACE( sheet::XCalculatable )
    SC_QUERYINTERFACE( util::XProtectable )
    SC_QUERYINTERFACE( drawing::XDrawPagesSupplier )
    SC_QUERYINTERFACE( sheet::XGoalSeek )
    SC_QUERYINTERFACE( sheet::XConsolidatable )
    SC_QUERYINTERFACE( sheet::XDocumentAuditing )
    SC_QUERYINTERFACE( style::XStyleFamiliesSupplier )
    SC_QUERYINTERFACE( view::XRenderable )
    SC_QUERYINTERFACE( document::XLinkTargetSupplier )
    SC_QUERYINTERFACE( beans::XPropertySet )
    SC_QUERYINTERFACE( lang::XMultiServiceFactory )
    SC_QUERYINTERFACE( lang::XUnoTunnel )
    SC_QUERYINTERFACE( lang::XServiceInfo )

    uno::Any aRet = SfxBaseModel::queryInterface( rType );
    if ( !aRet.hasValue() && xNumberAgg.is() )
        aRet = xNumberAgg->queryAggregation( rType );

    return aRet;
}

void SAL_CALL ScModelObj::acquire() throw()
{
    SfxBaseModel::acquire();
}

void SAL_CALL ScModelObj::release() throw()
{
    SfxBaseModel::release();
}

uno::Sequence<uno::Type> SAL_CALL ScModelObj::getTypes() throw(uno::RuntimeException)
{
    static uno::Sequence<uno::Type> aTypes;
    if ( aTypes.getLength() == 0 )
    {
        uno::Sequence<uno::Type> aParentTypes = SfxBaseModel::getTypes();
        long nParentLen = aParentTypes.getLength();
        const uno::Type* pParentPtr = aParentTypes.getConstArray();

        uno::Sequence<uno::Type> aAggTypes;
        if ( xNumberAgg.is() )
        {
            const uno::Type& rProvType = ::getCppuType((uno::Reference<lang::XTypeProvider>*) 0);
            uno::Any aNumProv = xNumberAgg->queryAggregation(rProvType);
            if(aNumProv.getValueType() == rProvType)
            {
                uno::Reference<lang::XTypeProvider> xNumProv =
                    *(uno::Reference<lang::XTypeProvider>*)aNumProv.getValue();
                aAggTypes = xNumProv->getTypes();
            }
        }
        long nAggLen = aAggTypes.getLength();
        const uno::Type* pAggPtr = aAggTypes.getConstArray();

        const long nThisLen = 15;
        aTypes.realloc( nParentLen + nAggLen + nThisLen );
        uno::Type* pPtr = aTypes.getArray();
        pPtr[nParentLen + 0] = getCppuType((const uno::Reference<sheet::XSpreadsheetDocument>*)0);
        pPtr[nParentLen + 1] = getCppuType((const uno::Reference<document::XActionLockable>*)0);
        pPtr[nParentLen + 2] = getCppuType((const uno::Reference<sheet::XCalculatable>*)0);
        pPtr[nParentLen + 3] = getCppuType((const uno::Reference<util::XProtectable>*)0);
        pPtr[nParentLen + 4] = getCppuType((const uno::Reference<drawing::XDrawPagesSupplier>*)0);
        pPtr[nParentLen + 5] = getCppuType((const uno::Reference<sheet::XGoalSeek>*)0);
        pPtr[nParentLen + 6] = getCppuType((const uno::Reference<sheet::XConsolidatable>*)0);
        pPtr[nParentLen + 7] = getCppuType((const uno::Reference<sheet::XDocumentAuditing>*)0);
        pPtr[nParentLen + 8] = getCppuType((const uno::Reference<style::XStyleFamiliesSupplier>*)0);
        pPtr[nParentLen + 9] = getCppuType((const uno::Reference<view::XRenderable>*)0);
        pPtr[nParentLen +10] = getCppuType((const uno::Reference<document::XLinkTargetSupplier>*)0);
        pPtr[nParentLen +11] = getCppuType((const uno::Reference<beans::XPropertySet>*)0);
        pPtr[nParentLen +12] = getCppuType((const uno::Reference<lang::XMultiServiceFactory>*)0);
        pPtr[nParentLen +13] = getCppuType((const uno::Reference<lang::XUnoTunnel>*)0);
        pPtr[nParentLen +14] = getCppuType((const uno::Reference<lang::XServiceInfo>*)0);

        long i;
        for (i=0; i<nParentLen; i++)
            pPtr[i] = pParentPtr[i];					// parent types first

        for (i=0; i<nAggLen; i++)
            pPtr[nParentLen+nThisLen+i] = pAggPtr[i];	// aggregated types last
    }
    return aTypes;
}

uno::Sequence<sal_Int8> SAL_CALL ScModelObj::getImplementationId()
                                                    throw(uno::RuntimeException)
{
    static uno::Sequence< sal_Int8 > aId;
    if( aId.getLength() == 0 )
    {
        aId.realloc( 16 );
        rtl_createUuid( (sal_uInt8 *)aId.getArray(), 0, sal_True );
    }
    return aId;
}

void ScModelObj::Notify( SfxBroadcaster& rBC, const SfxHint& rHint )
{
    //	Not interested in reference update hints here

    if ( rHint.ISA( SfxSimpleHint ) )
    {
        ULONG nId = ((const SfxSimpleHint&)rHint).GetId();
        if ( nId == SFX_HINT_DYING )
        {
            pDocShell = NULL;		// has become invalid
            if (xNumberAgg.is())
            {
                SvNumberFormatsSupplierObj* pNumFmt =
                    SvNumberFormatsSupplierObj::getImplementation(
                        uno::Reference<util::XNumberFormatsSupplier>(xNumberAgg, uno::UNO_QUERY) );
                if ( pNumFmt )
                    pNumFmt->SetNumberFormatter( NULL );
            }
        }
    }
    else if ( rHint.ISA( ScPointerChangedHint ) )
    {
        USHORT nFlags = ((const ScPointerChangedHint&)rHint).GetFlags();
        if (nFlags & SC_POINTERCHANGED_NUMFMT)
        {
            //	NumberFormatter-Pointer am Uno-Objekt neu setzen

            if (xNumberAgg.is())
            {
                SvNumberFormatsSupplierObj* pNumFmt =
                    SvNumberFormatsSupplierObj::getImplementation(
                        uno::Reference<util::XNumberFormatsSupplier>(xNumberAgg, uno::UNO_QUERY) );
                if ( pNumFmt && pDocShell )
                    pNumFmt->SetNumberFormatter( pDocShell->GetDocument()->GetFormatTable() );
            }
        }
    }
    else
        SfxBaseModel::Notify( rBC, rHint );		// SfxBaseModel is derived from SfxListener
}

// XSpreadsheetDocument

uno::Reference<sheet::XSpreadsheets> SAL_CALL ScModelObj::getSheets() throw(uno::RuntimeException)
{
    ScUnoGuard aGuard;
    if (pDocShell)
        return new ScTableSheetsObj(pDocShell);
    return NULL;
}

// XStyleFamiliesSupplier

uno::Reference<container::XNameAccess> SAL_CALL ScModelObj::getStyleFamilies()
                                                throw(uno::RuntimeException)
{
    ScUnoGuard aGuard;
    if (pDocShell)
        return new ScStyleFamiliesObj(pDocShell);
    return NULL;
}

// XRenderable

OutputDevice* lcl_GetRenderDevice( const uno::Sequence<beans::PropertyValue>& rOptions )
{
    DBG_ERROR("Strip!");
    return 0;
}

BOOL ScModelObj::FillRenderMarkData( const uno::Any& aSelection, ScMarkData& rMark,
                                     ScPrintSelectionStatus& rStatus ) const
{
    DBG_ERROR("Strip!");
    return FALSE;
}


sal_Int32 SAL_CALL ScModelObj::getRendererCount( const uno::Any& aSelection,
                                    const uno::Sequence<beans::PropertyValue>& xOptions )
                                throw (lang::IllegalArgumentException, uno::RuntimeException)
{
    DBG_ERROR("Strip!");
    return 0;
}

uno::Sequence<beans::PropertyValue> SAL_CALL ScModelObj::getRenderer( sal_Int32 nRenderer,
                                    const uno::Any& aSelection, const uno::Sequence<beans::PropertyValue>& xOptions )
                                throw (lang::IllegalArgumentException, uno::RuntimeException)
{
    DBG_ERROR("Strip!");
    uno::Sequence<beans::PropertyValue> aSequence;
    return aSequence;
}

void SAL_CALL ScModelObj::render( sal_Int32 nRenderer, const uno::Any& aSelection,
                                    const uno::Sequence<beans::PropertyValue>& rOptions )
                                throw(lang::IllegalArgumentException, uno::RuntimeException)
{
    DBG_ERROR("Strip!");
}

// XLinkTargetSupplier

uno::Reference<container::XNameAccess> SAL_CALL ScModelObj::getLinks() throw(uno::RuntimeException)
{
    ScUnoGuard aGuard;
    if (pDocShell)
        return new ScLinkTargetTypesObj(pDocShell);
    return NULL;
}

// XActionLockable

sal_Bool SAL_CALL ScModelObj::isActionLocked() throw(uno::RuntimeException)
{
    ScUnoGuard aGuard;
    BOOL bLocked = FALSE;
    if (pDocShell)
        bLocked = ( pDocShell->GetLockCount() != 0 );
    return bLocked;
}

void SAL_CALL ScModelObj::addActionLock() throw(uno::RuntimeException)
{
    ScUnoGuard aGuard;
    if (pDocShell)
        pDocShell->LockDocument();
}

void SAL_CALL ScModelObj::removeActionLock() throw(uno::RuntimeException)
{
    ScUnoGuard aGuard;
    if (pDocShell)
        pDocShell->UnlockDocument();
}

void SAL_CALL ScModelObj::setActionLocks( sal_Int16 nLock ) throw(uno::RuntimeException)
{
    ScUnoGuard aGuard;
    if (pDocShell)
        pDocShell->SetLockCount(nLock);
}

sal_Int16 SAL_CALL ScModelObj::resetActionLocks() throw(uno::RuntimeException)
{
    ScUnoGuard aGuard;
    USHORT nRet = 0;
    if (pDocShell)
    {
        nRet = pDocShell->GetLockCount();
        pDocShell->SetLockCount(0);
    }
    return nRet;
}

void SAL_CALL ScModelObj::lockControllers() throw (::com::sun::star::uno::RuntimeException)
{
    ScUnoGuard aGuard;
    SfxBaseModel::lockControllers();
    if (pDocShell)
        pDocShell->LockPaint();
}

void SAL_CALL ScModelObj::unlockControllers() throw (::com::sun::star::uno::RuntimeException)
{
    ScUnoGuard aGuard;
    if (hasControllersLocked())
    {
        SfxBaseModel::unlockControllers();
        if (pDocShell)
            pDocShell->UnlockPaint();
    }
}

// XCalculate

void SAL_CALL ScModelObj::calculate() throw(uno::RuntimeException)
{
    ScUnoGuard aGuard;
    if (pDocShell)
        pDocShell->DoRecalc(TRUE);
    else
        DBG_ERROR("keine DocShell");		//! Exception oder so?
}

void SAL_CALL ScModelObj::calculateAll() throw(uno::RuntimeException)
{
    ScUnoGuard aGuard;
    if (pDocShell)
        pDocShell->DoHardRecalc(TRUE);
    else
        DBG_ERROR("keine DocShell");		//! Exception oder so?
}

sal_Bool SAL_CALL ScModelObj::isAutomaticCalculationEnabled() throw(uno::RuntimeException)
{
    ScUnoGuard aGuard;
    if (pDocShell)
        return pDocShell->GetDocument()->GetAutoCalc();

    DBG_ERROR("keine DocShell");		//! Exception oder so?
    return FALSE;
}

void SAL_CALL ScModelObj::enableAutomaticCalculation( sal_Bool bEnabled )
                                                throw(uno::RuntimeException)
{
    ScUnoGuard aGuard;
    if (pDocShell)
    {
        ScDocument* pDoc = pDocShell->GetDocument();
        if ( pDoc->GetAutoCalc() != bEnabled )
        {
            pDoc->SetAutoCalc( bEnabled );
            pDocShell->SetDocumentModified();
        }
    }
    else
        DBG_ERROR("keine DocShell");		//! Exception oder so?
}

// XProtectable

void SAL_CALL ScModelObj::protect( const ::rtl::OUString& aPassword ) throw(uno::RuntimeException)
{
    ScUnoGuard aGuard;
    if (pDocShell)
    {
        String aString = aPassword;

        ScDocFunc aFunc(*pDocShell);
        aFunc.Protect( TABLEID_DOC, aString, TRUE );
    }
}

void SAL_CALL ScModelObj::unprotect( const ::rtl::OUString& aPassword )
                        throw(lang::IllegalArgumentException, uno::RuntimeException)
{
    ScUnoGuard aGuard;
    if (pDocShell)
    {
        String aString = aPassword;

        ScDocFunc aFunc(*pDocShell);
        aFunc.Unprotect( TABLEID_DOC, aString, TRUE );

        //!	Rueckgabewert auswerten, Exception oder so
    }
}

sal_Bool SAL_CALL ScModelObj::isProtected() throw(uno::RuntimeException)
{
    ScUnoGuard aGuard;
    if (pDocShell)
        return pDocShell->GetDocument()->IsDocProtected();

    DBG_ERROR("keine DocShell");		//! Exception oder so?
    return FALSE;
}

// XDrawPagesSupplier

uno::Reference<drawing::XDrawPages> SAL_CALL ScModelObj::getDrawPages() throw(uno::RuntimeException)
{
    ScUnoGuard aGuard;
    if (pDocShell)
        return new ScDrawPagesObj(pDocShell);

    DBG_ERROR("keine DocShell");		//! Exception oder so?
    return NULL;
}

#if 0
// XPrintable

::rtl::OUString ScModelObj::getPrinterName(void) const
{
    ScUnoGuard aGuard;
    if (pDocShell)
    {
        SfxPrinter* pPrinter = pDocShell->GetPrinter();
        if (pPrinter)
            return pPrinter->GetName();
    }

    DBG_ERROR("getPrinterName: keine DocShell oder kein Printer");
    return ::rtl::OUString();
}

void ScModelObj::setPrinterName(const ::rtl::OUString& PrinterName)
{
    ScUnoGuard aGuard;
    //	Drucker setzen - wie in SfxViewShell::ExecPrint_Impl

    if (pDocShell)
    {
        SfxPrinter* pPrinter = pDocShell->GetPrinter();
        if (pPrinter)
        {
            String aString = PrinterName;
            SfxPrinter* pNewPrinter = new SfxPrinter( pPrinter->GetOptions().Clone(), aString );
            if (pNewPrinter->IsKnown())
                pDocShell->SetPrinter( pNewPrinter, SFX_PRINTER_PRINTER );
            else
                delete pNewPrinter;
        }
    }
}

XPropertySetRef ScModelObj::createPrintOptions(void)
{
    ScUnoGuard aGuard;
    return new ScPrintSettingsObj;		//! ScPrintSettingsObj implementieren!
}

void ScModelObj::print(const XPropertySetRef& xOptions)
{
    ScUnoGuard aGuard;
    if (pDocShell)
    {
        //!	xOptions auswerten (wie denn?)

        //!	muss noch
    }
}
#endif

// XGoalSeek

sheet::GoalResult SAL_CALL ScModelObj::seekGoal(
                                const table::CellAddress& aFormulaPosition,
                                const table::CellAddress& aVariablePosition,
                                const ::rtl::OUString& aGoalValue )
                                    throw(uno::RuntimeException)
{
    ScUnoGuard aGuard;
    sheet::GoalResult aResult;
    aResult.Divergence = DBL_MAX;		// nichts gefunden
    if (pDocShell)
    {
        WaitObject aWait( pDocShell->GetDialogParent() );
        String aGoalString = aGoalValue;
        ScDocument* pDoc = pDocShell->GetDocument();
        double fValue = 0.0;
        BOOL bFound = pDoc->Solver(
                    (USHORT)aFormulaPosition.Column, (USHORT)aFormulaPosition.Row, aFormulaPosition.Sheet,
                    (USHORT)aVariablePosition.Column, (USHORT)aVariablePosition.Row, aVariablePosition.Sheet,
                    aGoalString, fValue );
        aResult.Result = fValue;
        if (bFound)
            aResult.Divergence = 0.0;	//! das ist gelogen
    }
    return aResult;
}

// XConsolidatable

uno::Reference<sheet::XConsolidationDescriptor> SAL_CALL ScModelObj::createConsolidationDescriptor(
                                sal_Bool bEmpty ) throw(uno::RuntimeException)
{
    ScUnoGuard aGuard;
    ScConsolidationDescriptor* pNew = new ScConsolidationDescriptor;
    if ( pDocShell && !bEmpty )
    {
        ScDocument* pDoc = pDocShell->GetDocument();
        const ScConsolidateParam* pParam = pDoc->GetConsolidateDlgData();
        if (pParam)
            pNew->SetParam( *pParam );
    }
    return pNew;
}

void SAL_CALL ScModelObj::consolidate(
        const uno::Reference<sheet::XConsolidationDescriptor>& xDescriptor )
                                                throw(uno::RuntimeException)
{
    ScUnoGuard aGuard;
    //	das koennte theoretisch ein fremdes Objekt sein, also nur das
    //	oeffentliche XConsolidationDescriptor Interface benutzen, um
    //	die Daten in ein ScConsolidationDescriptor Objekt zu kopieren:
    //!	wenn es schon ein ScConsolidationDescriptor ist, direkt per getImplementation?

    ScConsolidationDescriptor aImpl;
    aImpl.setFunction( xDescriptor->getFunction() );
    aImpl.setSources( xDescriptor->getSources() );
    aImpl.setStartOutputPosition( xDescriptor->getStartOutputPosition() );
    aImpl.setUseColumnHeaders( xDescriptor->getUseColumnHeaders() );
    aImpl.setUseRowHeaders( xDescriptor->getUseRowHeaders() );
    aImpl.setInsertLinks( xDescriptor->getInsertLinks() );

    if (pDocShell)
    {
        const ScConsolidateParam& rParam = aImpl.GetParam();
        pDocShell->DoConsolidate( rParam, TRUE );
        pDocShell->GetDocument()->SetConsolidateDlgData( &rParam );
    }
}

// XDocumentAuditing

void SAL_CALL ScModelObj::refreshArrows() throw(uno::RuntimeException)
{
    ScUnoGuard aGuard;
    if (pDocShell)
    {
        ScDocFunc aFunc(*pDocShell);
        aFunc.DetectiveRefresh();
    }
}

// XViewDataSupplier
uno::Reference< container::XIndexAccess > SAL_CALL ScModelObj::getViewData(  ) 
    throw (uno::RuntimeException)
{
    uno::Reference < container::XIndexAccess > xRet( SfxBaseModel::getViewData() );

    if( !xRet.is() )
    {
        ScUnoGuard aGuard;
        if (pDocShell && pDocShell->GetCreateMode() == SFX_CREATE_MODE_EMBEDDED)
        {
            xRet = uno::Reference < container::XIndexAccess >::query(::legacy_binfilters::getLegacyProcessServiceFactory()->createInstance(::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("com.sun.star.document.IndexedPropertyValues"))));

            uno::Reference < container::XIndexContainer > xCont( xRet, uno::UNO_QUERY );
            DBG_ASSERT( xCont.is(), "ScModelObj::getViewData() failed for OLE object" );
            if( xCont.is() )
            {
                uno::Sequence< beans::PropertyValue > aSeq;
                aSeq.realloc(1);
                String sName;
                pDocShell->GetDocument()->GetName( pDocShell->GetDocument()->GetVisibleTab(), sName );
                ::rtl::OUString sOUName(sName);
                aSeq[0].Name = ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM(SC_ACTIVETABLE));
                aSeq[0].Value <<= sOUName;
                xCont->insertByIndex( 0, uno::makeAny( aSeq ) );
            }
        }
        else if ( pDocShell )
        {
            // #116578# Convert manually loaded state from sfx window data
            // into view data sequence

            String aUserData = pDocShell->GetUserData();
            if ( aUserData.Len() )
            {
                ScViewData aLocalViewData( pDocShell );
                aLocalViewData.ReadUserData( aUserData );
                uno::Sequence< beans::PropertyValue > aSeq;
                aLocalViewData.WriteUserDataSequence( aSeq );

                xRet = uno::Reference < container::XIndexAccess >::query(::legacy_binfilters::getLegacyProcessServiceFactory()->createInstance(::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("com.sun.star.document.IndexedPropertyValues"))));
                uno::Reference < container::XIndexContainer > xCont( xRet, uno::UNO_QUERY );
                if( xCont.is() )
                    xCont->insertByIndex( 0, uno::makeAny( aSeq ) );
            }
        }
    }

    return xRet;
}

//	XPropertySet (Doc-Optionen)
//!	auch an der Applikation anbieten?

uno::Reference<beans::XPropertySetInfo> SAL_CALL ScModelObj::getPropertySetInfo()
                                                        throw(uno::RuntimeException)
{
    ScUnoGuard aGuard;
    static uno::Reference<beans::XPropertySetInfo> aRef =
        new SfxItemPropertySetInfo( aPropSet.getPropertyMap() );
    return aRef;
}

void SAL_CALL ScModelObj::setPropertyValue(
                        const ::rtl::OUString& aPropertyName, const uno::Any& aValue )
                throw(beans::UnknownPropertyException, beans::PropertyVetoException,
                        lang::IllegalArgumentException, lang::WrappedTargetException,
                        uno::RuntimeException)
{
    ScUnoGuard aGuard;
    String aString = aPropertyName;

    if (pDocShell)
    {
        ScDocument* pDoc = pDocShell->GetDocument();
        const ScDocOptions& rOldOpt = pDoc->GetDocOptions();
        ScDocOptions aNewOpt = rOldOpt;

        BOOL bOpt = ScDocOptionsHelper::setPropertyValue( aNewOpt, aPropertyName, aValue );
        if (bOpt)
        {
            // done...
        }
        else if ( aString.EqualsAscii( SC_UNONAME_CLOCAL ) )
        {
            lang::Locale aLocale;
            if ( aValue >>= aLocale )
            {
                LanguageType eLatin, eCjk, eCtl;
                pDoc->GetLanguage( eLatin, eCjk, eCtl );
                eLatin = ScUnoConversion::GetLanguage(aLocale);
                pDoc->SetLanguage( eLatin, eCjk, eCtl );
            }
        }
        else if ( aString.EqualsAscii( SC_UNO_CJK_CLOCAL ) )
        {
            lang::Locale aLocale;
            if ( aValue >>= aLocale )
            {
                LanguageType eLatin, eCjk, eCtl;
                pDoc->GetLanguage( eLatin, eCjk, eCtl );
                eCjk = ScUnoConversion::GetLanguage(aLocale);
                pDoc->SetLanguage( eLatin, eCjk, eCtl );
            }
        }
        else if ( aString.EqualsAscii( SC_UNO_CTL_CLOCAL ) )
        {
            lang::Locale aLocale;
            if ( aValue >>= aLocale )
            {
                LanguageType eLatin, eCjk, eCtl;
                pDoc->GetLanguage( eLatin, eCjk, eCtl );
                eCtl = ScUnoConversion::GetLanguage(aLocale);
                pDoc->SetLanguage( eLatin, eCjk, eCtl );
            }
        }
        else if ( aString.EqualsAscii( SC_UNO_APPLYFMDES ) )
        {
            //	model is created if not there
            ScDrawLayer* pModel = pDocShell->MakeDrawLayer();
            pModel->SetOpenInDesignMode( ScUnoHelpFunctions::GetBoolFromAny( aValue ) );

        }
        else if ( aString.EqualsAscii( SC_UNO_AUTOCONTFOC ) )
        {
            //	model is created if not there
            ScDrawLayer* pModel = pDocShell->MakeDrawLayer();
            pModel->SetAutoControlFocus( ScUnoHelpFunctions::GetBoolFromAny( aValue ) );

        }

        if ( aNewOpt != rOldOpt )
        {
            pDoc->SetDocOptions( aNewOpt );
            pDocShell->DoHardRecalc( TRUE );	//! Recalc nur bei entsprechenden Optionen?
            pDocShell->SetDocumentModified();
        }
    }
}

uno::Any SAL_CALL ScModelObj::getPropertyValue( const ::rtl::OUString& aPropertyName )
                throw(beans::UnknownPropertyException, lang::WrappedTargetException,
                        uno::RuntimeException)
{
    ScUnoGuard aGuard;
    String aString = aPropertyName;
    uno::Any aRet;

    if (pDocShell)
    {
        ScDocument* pDoc = pDocShell->GetDocument();
        const ScDocOptions& rOpt = pDoc->GetDocOptions();
        aRet = ScDocOptionsHelper::getPropertyValue( rOpt, aPropertyName );
        if ( aRet.hasValue() )
        {
            // done...
        }
        else if ( aString.EqualsAscii( SC_UNONAME_CLOCAL ) )
        {
            LanguageType eLatin, eCjk, eCtl;
            pDoc->GetLanguage( eLatin, eCjk, eCtl );

            lang::Locale aLocale;
            ScUnoConversion::FillLocale( aLocale, eLatin );
            aRet <<= aLocale;
        }
        else if ( aString.EqualsAscii( SC_UNO_CJK_CLOCAL ) )
        {
            LanguageType eLatin, eCjk, eCtl;
            pDoc->GetLanguage( eLatin, eCjk, eCtl );

            lang::Locale aLocale;
            ScUnoConversion::FillLocale( aLocale, eCjk );
            aRet <<= aLocale;
        }
        else if ( aString.EqualsAscii( SC_UNO_CTL_CLOCAL ) )
        {
            LanguageType eLatin, eCjk, eCtl;
            pDoc->GetLanguage( eLatin, eCjk, eCtl );

            lang::Locale aLocale;
            ScUnoConversion::FillLocale( aLocale, eCtl );
            aRet <<= aLocale;
        }
        else if ( aString.EqualsAscii( SC_UNO_NAMEDRANGES ) )
        {
            uno::Reference<sheet::XNamedRanges> xRanges = new ScNamedRangesObj( pDocShell );
            aRet <<= xRanges;
        }
        else if ( aString.EqualsAscii( SC_UNO_DATABASERNG ) )
        {
            uno::Reference<sheet::XDatabaseRanges> xRanges = new ScDatabaseRangesObj( pDocShell );
            aRet <<= xRanges;
        }
        else if ( aString.EqualsAscii( SC_UNO_COLLABELRNG ) )
        {
            uno::Reference<sheet::XLabelRanges> xRanges = new ScLabelRangesObj( pDocShell, TRUE );
            aRet <<= xRanges;
        }
        else if ( aString.EqualsAscii( SC_UNO_ROWLABELRNG ) )
        {
            uno::Reference<sheet::XLabelRanges> xRanges = new ScLabelRangesObj( pDocShell, FALSE );
            aRet <<= xRanges;
        }
        else if ( aString.EqualsAscii( SC_UNO_AREALINKS ) )
        {
            uno::Reference<sheet::XAreaLinks> xLinks = new ScAreaLinksObj( pDocShell );
            aRet <<= xLinks;
        }
        else if ( aString.EqualsAscii( SC_UNO_DDELINKS ) )
        {
            uno::Reference<container::XNameAccess> xLinks = new ScDDELinksObj( pDocShell );
            aRet <<= xLinks;
        }
        else if ( aString.EqualsAscii( SC_UNO_SHEETLINKS ) )
        {
            uno::Reference<container::XNameAccess> xLinks = new ScSheetLinksObj( pDocShell );
            aRet <<= xLinks;
        }
        else if ( aString.EqualsAscii( SC_UNO_APPLYFMDES ) )
        {
            // default for no model is TRUE
            ScDrawLayer* pModel = pDoc->GetDrawLayer();
            sal_Bool bOpenInDesign = pModel ? pModel->GetOpenInDesignMode() : sal_True;
            ScUnoHelpFunctions::SetBoolInAny( aRet, bOpenInDesign );
        }
        else if ( aString.EqualsAscii( SC_UNO_AUTOCONTFOC ) )
        {
            // default for no model is FALSE
            ScDrawLayer* pModel = pDoc->GetDrawLayer();
            sal_Bool bAutoControlFocus = pModel ? pModel->GetAutoControlFocus() : sal_False;
            ScUnoHelpFunctions::SetBoolInAny( aRet, bAutoControlFocus );
        }
        else if ( aString.EqualsAscii( SC_UNO_FORBIDDEN ) )
        {
            uno::Reference<i18n::XForbiddenCharacters> xForbidden = new ScForbiddenCharsObj( pDocShell );
            aRet <<= xForbidden;
        }
        else if ( aString.EqualsAscii( SC_UNO_HASDRAWPAGES ) )
        {
            ScUnoHelpFunctions::SetBoolInAny( aRet, (pDocShell->GetDocument()->GetDrawLayer() != 0) );
        }
        else if ( aString.EqualsAscii( SC_UNO_BASICLIBRARIES ) )
        {
            aRet <<= pDocShell->GetBasicContainer();
        }
    }

    return aRet;
}

SC_IMPL_DUMMY_PROPERTY_LISTENER( ScModelObj )

// XMultiServiceFactory

uno::Reference<uno::XInterface> SAL_CALL ScModelObj::createInstance(
                                const ::rtl::OUString& aServiceSpecifier )
                                throw(uno::Exception, uno::RuntimeException)
{
    ScUnoGuard aGuard;
    uno::Reference<uno::XInterface> xRet;
    String aNameStr = aServiceSpecifier;
    USHORT nType = ScServiceProvider::GetProviderType(aNameStr);
    if ( nType != SC_SERVICE_INVALID )
    {
        //	drawing layer tables must be kept as long as the model is alive
        //	return stored instance if already set
        switch ( nType )
        {
            case SC_SERVICE_GRADTAB:	xRet = xDrawGradTab;	break;
            case SC_SERVICE_HATCHTAB:	xRet = xDrawHatchTab;	break;
            case SC_SERVICE_BITMAPTAB:	xRet = xDrawBitmapTab;	break;
            case SC_SERVICE_TRGRADTAB:	xRet = xDrawTrGradTab;	break;
            case SC_SERVICE_MARKERTAB:	xRet = xDrawMarkerTab;	break;
            case SC_SERVICE_DASHTAB:	xRet = xDrawDashTab;	break;
        }

        if ( !xRet.is() )
        {
            xRet = ScServiceProvider::MakeInstance( nType, pDocShell );

            //	store created instance
            switch ( nType )
            {
                case SC_SERVICE_GRADTAB:	xDrawGradTab = xRet;	break;
                case SC_SERVICE_HATCHTAB:	xDrawHatchTab = xRet;	break;
                case SC_SERVICE_BITMAPTAB:	xDrawBitmapTab = xRet;	break;
                case SC_SERVICE_TRGRADTAB:	xDrawTrGradTab = xRet;	break;
                case SC_SERVICE_MARKERTAB:	xDrawMarkerTab = xRet;	break;
                case SC_SERVICE_DASHTAB:	xDrawDashTab = xRet;	break;
            }
        }
    }
    else
    {
        //	alles was ich nicht kenn, werf ich der SvxFmMSFactory an den Hals,
        //	da wird dann 'ne Exception geworfen, wenn's nicht passt...

        {
            xRet = SvxFmMSFactory::createInstance(aServiceSpecifier);
            // extra block to force deletion of the temporary before ScShapeObj ctor (setDelegator)
        }

        //	#96117# if the drawing factory created a shape, a ScShapeObj has to be used
        //	to support own properties like ImageMap:

        uno::Reference<drawing::XShape> xShape( xRet, uno::UNO_QUERY );
        if ( xShape.is() )
        {
            xRet.clear();				// for aggregation, xShape must be the object's only ref
            new ScShapeObj( xShape );	// aggregates object and modifies xShape
            xRet = xShape;
        }
    }
    return xRet;
}

uno::Reference<uno::XInterface> SAL_CALL ScModelObj::createInstanceWithArguments(
                                const ::rtl::OUString& ServiceSpecifier,
                                const uno::Sequence<uno::Any>& Arguments )
                                throw(uno::Exception, uno::RuntimeException)
{
    //!	unterscheiden zwischen eigenen Services und denen vom Drawing-Layer?

    ScUnoGuard aGuard;
    uno::Reference<uno::XInterface> xInt = createInstance(ServiceSpecifier);
    //die Any-Sequence dient zur Initialisierung von Objekten, die auf
    //Parameter zwingend angewiesen sind - bis jetzt haben wir das nicht
    return xInt;
}

uno::Sequence< ::rtl::OUString> SAL_CALL ScModelObj::getAvailableServiceNames()
                                                throw(uno::RuntimeException)
{
    ScUnoGuard aGuard;

    //!	warum sind die Parameter bei concatServiceNames nicht const ???
    //!	return concatServiceNames( ScServiceProvider::GetAllServiceNames(),
    //!							   SvxFmMSFactory::getAvailableServiceNames() );

    uno::Sequence< ::rtl::OUString> aMyServices = ScServiceProvider::GetAllServiceNames();
    uno::Sequence< ::rtl::OUString> aDrawServices = SvxFmMSFactory::getAvailableServiceNames();

    return concatServiceNames( aMyServices, aDrawServices );
}

// XServiceInfo

::rtl::OUString SAL_CALL ScModelObj::getImplementationName() throw(uno::RuntimeException)
{
    return ::rtl::OUString::createFromAscii( "ScModelObj" );
}

sal_Bool SAL_CALL ScModelObj::supportsService( const ::rtl::OUString& rServiceName )
                                                    throw(uno::RuntimeException)
{
    String aServiceStr = rServiceName;
    return aServiceStr.EqualsAscii( SCMODELOBJ_SERVICE ) ||
           aServiceStr.EqualsAscii( SCDOCSETTINGS_SERVICE ) ||
           aServiceStr.EqualsAscii( SCDOC_SERVICE );
}

uno::Sequence< ::rtl::OUString> SAL_CALL ScModelObj::getSupportedServiceNames()
                                                    throw(uno::RuntimeException)
{
    uno::Sequence< ::rtl::OUString> aRet(3);
    ::rtl::OUString* pArray = aRet.getArray();
    pArray[0] = ::rtl::OUString::createFromAscii( SCMODELOBJ_SERVICE );
    pArray[1] = ::rtl::OUString::createFromAscii( SCDOCSETTINGS_SERVICE );
    pArray[2] = ::rtl::OUString::createFromAscii( SCDOC_SERVICE );
    return aRet;
}

// XUnoTunnel

sal_Int64 SAL_CALL ScModelObj::getSomething(
                const uno::Sequence<sal_Int8 >& rId ) throw(uno::RuntimeException)
{
    if ( rId.getLength() == 16 &&
          0 == rtl_compareMemory( getUnoTunnelId().getConstArray(),
                                    rId.getConstArray(), 16 ) )
    {
        return (sal_Int64)this;
    }

    //	aggregated number formats supplier has XUnoTunnel, too
    //	interface from aggregated object must be obtained via queryAggregation

    if ( xNumberAgg.is() )
    {
        const uno::Type& rTunnelType = ::getCppuType((uno::Reference<lang::XUnoTunnel>*) 0);
        uno::Any aNumTunnel = xNumberAgg->queryAggregation(rTunnelType);
        if(aNumTunnel.getValueType() == rTunnelType)
        {
            uno::Reference<lang::XUnoTunnel> xTunnelAgg =
                *(uno::Reference<lang::XUnoTunnel>*)aNumTunnel.getValue();
            return xTunnelAgg->getSomething( rId );
        }
    }

    return 0;
}

// static
const uno::Sequence<sal_Int8>& ScModelObj::getUnoTunnelId()
{
    static uno::Sequence<sal_Int8> * pSeq = 0;
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

// static
ScModelObj* ScModelObj::getImplementation( const uno::Reference<uno::XInterface> xObj )
{
    ScModelObj* pRet = NULL;
    uno::Reference<lang::XUnoTunnel> xUT( xObj, uno::UNO_QUERY );
    if (xUT.is())
        pRet = (ScModelObj*) xUT->getSomething( getUnoTunnelId() );
    return pRet;
}

//------------------------------------------------------------------------

ScDrawPagesObj::ScDrawPagesObj(ScDocShell* pDocSh) :
    pDocShell( pDocSh )
{
    pDocShell->GetDocument()->AddUnoObject(*this);
}

ScDrawPagesObj::~ScDrawPagesObj()
{
    if (pDocShell)
        pDocShell->GetDocument()->RemoveUnoObject(*this);
}

void ScDrawPagesObj::Notify( SfxBroadcaster& rBC, const SfxHint& rHint )
{
    //	Referenz-Update interessiert hier nicht

    if ( rHint.ISA( SfxSimpleHint ) &&
            ((const SfxSimpleHint&)rHint).GetId() == SFX_HINT_DYING )
    {
        pDocShell = NULL;		// ungueltig geworden
    }
}

uno::Reference<drawing::XDrawPage> ScDrawPagesObj::GetObjectByIndex_Impl(INT32 nIndex) const
{
    if (pDocShell)
    {
        ScDrawLayer* pDrawLayer = pDocShell->MakeDrawLayer();
        DBG_ASSERT(pDrawLayer,"kann Draw-Layer nicht anlegen");
        if ( pDrawLayer && nIndex >= 0 && nIndex < pDocShell->GetDocument()->GetTableCount() )
        {
            SdrPage* pPage = pDrawLayer->GetPage((USHORT)nIndex);
            DBG_ASSERT(pPage,"Draw-Page nicht gefunden");
            if (pPage)
            {
                return uno::Reference<drawing::XDrawPage> (pPage->getUnoPage(), uno::UNO_QUERY);
            }
        }
    }
    return NULL;
}

// XDrawPages

uno::Reference<drawing::XDrawPage> SAL_CALL ScDrawPagesObj::insertNewByIndex( sal_Int32 nPos )
                                            throw(uno::RuntimeException)
{
    ScUnoGuard aGuard;
    uno::Reference<drawing::XDrawPage> xRet;
    if (pDocShell)
    {
        String aNewName;
        pDocShell->GetDocument()->CreateValidTabName(aNewName);
        ScDocFunc aFunc(*pDocShell);
        if ( aFunc.InsertTable( (USHORT)nPos, aNewName, TRUE, TRUE ) )
            xRet = GetObjectByIndex_Impl( nPos );
    }
    return xRet;
}

void SAL_CALL ScDrawPagesObj::remove( const uno::Reference<drawing::XDrawPage>& xPage )
                                            throw(uno::RuntimeException)
{
    ScUnoGuard aGuard;
    SvxDrawPage* pImp = SvxDrawPage::getImplementation( xPage );
    if ( pDocShell && pImp )
    {
        SdrPage* pPage = pImp->GetSdrPage();
        if (pPage)
        {
            USHORT nPageNum = pPage->GetPageNum();
            ScDocFunc aFunc(*pDocShell);
            aFunc.DeleteTable( nPageNum, TRUE, TRUE );
        }
    }
}

// XIndexAccess

sal_Int32 SAL_CALL ScDrawPagesObj::getCount() throw(uno::RuntimeException)
{
    ScUnoGuard aGuard;
    if (pDocShell)
        return pDocShell->GetDocument()->GetTableCount();
    return 0;
}

uno::Any SAL_CALL ScDrawPagesObj::getByIndex( sal_Int32 nIndex )
                            throw(lang::IndexOutOfBoundsException,
                                    lang::WrappedTargetException, uno::RuntimeException)
{
    ScUnoGuard aGuard;
    uno::Reference<drawing::XDrawPage> xPage = GetObjectByIndex_Impl(nIndex);
    uno::Any aAny;
    if (xPage.is())
        aAny <<= xPage;
    else
        throw lang::IndexOutOfBoundsException();
    return aAny;
}

uno::Type SAL_CALL ScDrawPagesObj::getElementType() throw(uno::RuntimeException)
{
    ScUnoGuard aGuard;
    return getCppuType((uno::Reference<drawing::XDrawPage>*)0);
}

sal_Bool SAL_CALL ScDrawPagesObj::hasElements() throw(uno::RuntimeException)
{
    ScUnoGuard aGuard;
    return ( getCount() != 0 );
}

//------------------------------------------------------------------------

ScTableSheetsObj::ScTableSheetsObj(ScDocShell* pDocSh) :
    pDocShell( pDocSh )
{
    pDocShell->GetDocument()->AddUnoObject(*this);
}

ScTableSheetsObj::~ScTableSheetsObj()
{
    if (pDocShell)
        pDocShell->GetDocument()->RemoveUnoObject(*this);
}

void ScTableSheetsObj::Notify( SfxBroadcaster& rBC, const SfxHint& rHint )
{
    //	Referenz-Update interessiert hier nicht

    if ( rHint.ISA( SfxSimpleHint ) &&
            ((const SfxSimpleHint&)rHint).GetId() == SFX_HINT_DYING )
    {
        pDocShell = NULL;		// ungueltig geworden
    }
}

// XSpreadsheets

ScTableSheetObj* ScTableSheetsObj::GetObjectByIndex_Impl(USHORT nIndex) const
{
    if ( pDocShell && nIndex < pDocShell->GetDocument()->GetTableCount() )
        return new ScTableSheetObj( pDocShell, nIndex );

    return NULL;
}

ScTableSheetObj* ScTableSheetsObj::GetObjectByName_Impl(const ::rtl::OUString& aName) const
{
    if (pDocShell)
    {
        USHORT nIndex;
        String aString = aName;
        if ( pDocShell->GetDocument()->GetTable( aString, nIndex ) )
            return new ScTableSheetObj( pDocShell, nIndex );
    }
    return NULL;
}

void SAL_CALL ScTableSheetsObj::insertNewByName( const ::rtl::OUString& aName, sal_Int16 nPosition )
                                                throw(uno::RuntimeException)
{
    ScUnoGuard aGuard;
    BOOL bDone = FALSE;
    if (pDocShell)
    {
        String aNamStr = aName;
        ScDocFunc aFunc(*pDocShell);
        bDone = aFunc.InsertTable( nPosition, aNamStr, TRUE, TRUE );
    }
    if (!bDone)
        throw uno::RuntimeException();		// no other exceptions specified
}

void SAL_CALL ScTableSheetsObj::moveByName( const ::rtl::OUString& aName, sal_Int16 nDestination )
                                            throw(uno::RuntimeException)
{
    ScUnoGuard aGuard;
    BOOL bDone = FALSE;
    if (pDocShell)
    {
        String aNamStr = aName;
        USHORT nSource;
        if ( pDocShell->GetDocument()->GetTable( aNamStr, nSource ) )
            bDone = pDocShell->MoveTable( nSource, nDestination, FALSE, TRUE );
    }
    if (!bDone)
        throw uno::RuntimeException();		// no other exceptions specified
}

void SAL_CALL ScTableSheetsObj::copyByName( const ::rtl::OUString& aName,
                                const ::rtl::OUString& aCopy, sal_Int16 nDestination )
                                                throw(uno::RuntimeException)
{
    ScUnoGuard aGuard;
    BOOL bDone = FALSE;
    if (pDocShell)
    {
        String aNamStr = aName;
        String aNewStr = aCopy;
        USHORT nSource;
        if ( pDocShell->GetDocument()->GetTable( aNamStr, nSource ) )
        {
            bDone = pDocShell->MoveTable( nSource, nDestination, TRUE, TRUE );
            if (bDone)
            {
                ScDocFunc aFunc(*pDocShell);
                bDone = aFunc.RenameTable( nDestination, aNewStr, TRUE, TRUE );
            }
        }
    }
    if (!bDone)
        throw uno::RuntimeException();		// no other exceptions specified
}

void SAL_CALL ScTableSheetsObj::insertByName( const ::rtl::OUString& aName, const uno::Any& aElement )
                            throw(lang::IllegalArgumentException, container::ElementExistException,
                                    lang::WrappedTargetException, uno::RuntimeException)
{
    ScUnoGuard aGuard;
    BOOL bDone = FALSE;
    BOOL bIllArg = FALSE;

    //!	Type of aElement can be some specific interface instead of XInterface

    uno::Reference<uno::XInterface> xInterface;
    if ( pDocShell )
    {
        if ( aElement >>= xInterface )
        {
            ScTableSheetObj* pSheetObj = ScTableSheetObj::getImplementation( xInterface );
            if ( pSheetObj && !pSheetObj->GetDocShell() )	// noch nicht eingefuegt?
            {
                ScDocument* pDoc = pDocShell->GetDocument();
                String aNamStr = aName;
                USHORT nDummy;
                if ( pDoc->GetTable( aNamStr, nDummy ) )
                {
                    //	name already exists
                    throw container::ElementExistException();
                }
                else
                {
                    USHORT nPosition = pDoc->GetTableCount();
                    ScDocFunc aFunc(*pDocShell);
                    bDone = aFunc.InsertTable( nPosition, aNamStr, TRUE, TRUE );
                    if (bDone)
                        pSheetObj->InitInsertSheet( pDocShell, nPosition );
                    //	Dokument und neuen Range am Objekt setzen
                }
            }
            else
                bIllArg = TRUE;
        }
        else
            bIllArg = TRUE;
    }

    if (!bDone)
    {
        if (bIllArg)
            throw lang::IllegalArgumentException();
        else
            throw uno::RuntimeException();		// ElementExistException is handled above
    }
}

void SAL_CALL ScTableSheetsObj::replaceByName( const ::rtl::OUString& aName, const uno::Any& aElement )
                            throw(lang::IllegalArgumentException, container::NoSuchElementException,
                                    lang::WrappedTargetException, uno::RuntimeException)
{
    ScUnoGuard aGuard;
    BOOL bDone = FALSE;
    BOOL bIllArg = FALSE;

    //!	Type of aElement can be some specific interface instead of XInterface

    uno::Reference<uno::XInterface> xInterface;
    if ( pDocShell )
    {
        if ( aElement >>= xInterface )
        {
            ScTableSheetObj* pSheetObj = ScTableSheetObj::getImplementation( xInterface );
            if ( pSheetObj && !pSheetObj->GetDocShell() )	// noch nicht eingefuegt?
            {
                String aNamStr = aName;
                USHORT nPosition;
                if ( pDocShell->GetDocument()->GetTable( aNamStr, nPosition ) )
                {
                    ScDocFunc aFunc(*pDocShell);
                    if ( aFunc.DeleteTable( nPosition, TRUE, TRUE ) )
                    {
                        //	InsertTable kann jetzt eigentlich nicht schiefgehen...
                        bDone = aFunc.InsertTable( nPosition, aNamStr, TRUE, TRUE );
                        if (bDone)
                            pSheetObj->InitInsertSheet( pDocShell, nPosition );
                    }
                }
                else
                {
                    //	not found
                    throw container::NoSuchElementException();
                }
            }
            else
                bIllArg = TRUE;
        }
        else
            bIllArg = TRUE;
    }

    if (!bDone)
    {
        if (bIllArg)
            throw lang::IllegalArgumentException();
        else
            throw uno::RuntimeException();		// NoSuchElementException is handled above
    }
}

void SAL_CALL ScTableSheetsObj::removeByName( const ::rtl::OUString& aName )
                                throw(container::NoSuchElementException,
                                    lang::WrappedTargetException, uno::RuntimeException)
{
    ScUnoGuard aGuard;
    BOOL bDone = FALSE;
    if (pDocShell)
    {
        USHORT nIndex;
        String aString = aName;
        if ( pDocShell->GetDocument()->GetTable( aString, nIndex ) )
        {
            ScDocFunc aFunc(*pDocShell);
            bDone = aFunc.DeleteTable( nIndex, TRUE, TRUE );
        }
        else
        {
            //	not found
            throw container::NoSuchElementException();
        }
    }

    if (!bDone)
        throw uno::RuntimeException();		// NoSuchElementException is handled above
}

// XEnumerationAccess

uno::Reference<container::XEnumeration> SAL_CALL ScTableSheetsObj::createEnumeration()
                                                    throw(uno::RuntimeException)
{
    ScUnoGuard aGuard;
    return new ScIndexEnumeration(this, ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("com.sun.star.sheet.SpreadsheetsEnumeration")));
}

// XIndexAccess

sal_Int32 SAL_CALL ScTableSheetsObj::getCount() throw(uno::RuntimeException)
{
    ScUnoGuard aGuard;
    if (pDocShell)
        return pDocShell->GetDocument()->GetTableCount();
    return 0;
}

uno::Any SAL_CALL ScTableSheetsObj::getByIndex( sal_Int32 nIndex )
                            throw(lang::IndexOutOfBoundsException,
                                    lang::WrappedTargetException, uno::RuntimeException)
{
    ScUnoGuard aGuard;
    uno::Reference<sheet::XSpreadsheet> xSheet = GetObjectByIndex_Impl((USHORT)nIndex);
    uno::Any aAny;
    if (xSheet.is())
        aAny <<= xSheet;
    else
        throw lang::IndexOutOfBoundsException();
    return aAny;
}

uno::Type SAL_CALL ScTableSheetsObj::getElementType() throw(uno::RuntimeException)
{
    ScUnoGuard aGuard;
    return getCppuType((uno::Reference<sheet::XSpreadsheet>*)0);
}

sal_Bool SAL_CALL ScTableSheetsObj::hasElements() throw(uno::RuntimeException)
{
    ScUnoGuard aGuard;
    return ( getCount() != 0 );
}

// XNameAccess

uno::Any SAL_CALL ScTableSheetsObj::getByName( const ::rtl::OUString& aName )
            throw(container::NoSuchElementException,
                    lang::WrappedTargetException, uno::RuntimeException)
{
    ScUnoGuard aGuard;
    uno::Reference<sheet::XSpreadsheet> xSheet = GetObjectByName_Impl(aName);
    uno::Any aAny;
    if (xSheet.is())
        aAny <<= xSheet;
    else
        throw container::NoSuchElementException();
    return aAny;
}

uno::Sequence< ::rtl::OUString> SAL_CALL ScTableSheetsObj::getElementNames()
                                                throw(uno::RuntimeException)
{
    ScUnoGuard aGuard;
    if (pDocShell)
    {
        ScDocument* pDoc = pDocShell->GetDocument();
        USHORT nCount = pDoc->GetTableCount();
        String aName;
        uno::Sequence< ::rtl::OUString> aSeq(nCount);
        ::rtl::OUString* pAry = aSeq.getArray();
        for (USHORT i=0; i<nCount; i++)
        {
            pDoc->GetName( i, aName );
            pAry[i] = aName;
        }
        return aSeq;
    }
    return uno::Sequence< ::rtl::OUString>();
}

sal_Bool SAL_CALL ScTableSheetsObj::hasByName( const ::rtl::OUString& aName )
                                        throw(uno::RuntimeException)
{
    ScUnoGuard aGuard;
    if (pDocShell)
    {
        USHORT nIndex;
        String aString = aName;
        if ( pDocShell->GetDocument()->GetTable( aString, nIndex ) )
            return TRUE;
    }
    return FALSE;
}

//------------------------------------------------------------------------

ScTableColumnsObj::ScTableColumnsObj(ScDocShell* pDocSh, USHORT nT, USHORT nSC, USHORT nEC) :
    pDocShell( pDocSh ),
    nTab	 ( nT ),
    nStartCol( nSC ),
    nEndCol	 ( nEC )
{
    pDocShell->GetDocument()->AddUnoObject(*this);
}

ScTableColumnsObj::~ScTableColumnsObj()
{
    if (pDocShell)
        pDocShell->GetDocument()->RemoveUnoObject(*this);
}

void ScTableColumnsObj::Notify( SfxBroadcaster& rBC, const SfxHint& rHint )
{
    if ( rHint.ISA( ScUpdateRefHint ) )
    {
        const ScUpdateRefHint& rRef = (const ScUpdateRefHint&)rHint;

        //!	Referenz-Update fuer Tab und Start/Ende
    }
    else if ( rHint.ISA( SfxSimpleHint ) &&
            ((const SfxSimpleHint&)rHint).GetId() == SFX_HINT_DYING )
    {
        pDocShell = NULL;		// ungueltig geworden
    }
}

// XTableColumns

ScTableColumnObj* ScTableColumnsObj::GetObjectByIndex_Impl(USHORT nIndex) const
{
    USHORT nCol = nIndex + nStartCol;
    if ( pDocShell && nCol <= nEndCol )
        return new ScTableColumnObj( pDocShell, nCol, nTab );

    return NULL;	// falscher Index
}

ScTableColumnObj* ScTableColumnsObj::GetObjectByName_Impl(const ::rtl::OUString& aName) const
{
    USHORT nCol = 0;
    String aString = aName;
    if ( lcl_StringToColumn( aString, nCol ) )
        if ( pDocShell && nCol >= nStartCol && nCol <= nEndCol )
            return new ScTableColumnObj( pDocShell, nCol, nTab );

    return NULL;
}

void SAL_CALL ScTableColumnsObj::insertByIndex( sal_Int32 nPosition, sal_Int32 nCount )
                                                throw(uno::RuntimeException)
{
    ScUnoGuard aGuard;
    BOOL bDone = FALSE;
    if ( pDocShell && nCount > 0 && nPosition >= 0 && nStartCol+nPosition <= nEndCol &&
            nStartCol+nPosition+nCount-1 <= MAXCOL )
    {
        ScDocFunc aFunc(*pDocShell);
        ScRange aRange( (USHORT)(nStartCol+nPosition), 0, nTab,
                        (USHORT)(nStartCol+nPosition+nCount-1), MAXROW, nTab );
        bDone = aFunc.InsertCells( aRange, INS_INSCOLS, TRUE, TRUE );
    }
    if (!bDone)
        throw uno::RuntimeException();		// no other exceptions specified
}

void SAL_CALL ScTableColumnsObj::removeByIndex( sal_Int32 nIndex, sal_Int32 nCount )
                                                throw(uno::RuntimeException)
{
    ScUnoGuard aGuard;
    BOOL bDone = FALSE;
    //	Der zu loeschende Bereich muss innerhalb des Objekts liegen
    if ( pDocShell && nCount > 0 && nIndex >= 0 && nStartCol+nIndex+nCount-1 <= nEndCol )
    {
        ScDocFunc aFunc(*pDocShell);
        ScRange aRange( (USHORT)(nStartCol+nIndex), 0, nTab,
                        (USHORT)(nStartCol+nIndex+nCount-1), MAXROW, nTab );
        bDone = aFunc.DeleteCells( aRange, DEL_DELCOLS, TRUE, TRUE );
    }
    if (!bDone)
        throw uno::RuntimeException();		// no other exceptions specified
}

// XEnumerationAccess

uno::Reference<container::XEnumeration> SAL_CALL ScTableColumnsObj::createEnumeration()
                                                    throw(uno::RuntimeException)
{
    ScUnoGuard aGuard;
    return new ScIndexEnumeration(this, ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("com.sun.star.table.TableColumnsEnumeration")));
}

// XIndexAccess

sal_Int32 SAL_CALL ScTableColumnsObj::getCount() throw(uno::RuntimeException)
{
    ScUnoGuard aGuard;
    return nEndCol - nStartCol + 1;
}

uno::Any SAL_CALL ScTableColumnsObj::getByIndex( sal_Int32 nIndex )
                            throw(lang::IndexOutOfBoundsException,
                                    lang::WrappedTargetException, uno::RuntimeException)
{
    ScUnoGuard aGuard;
    uno::Reference<table::XCellRange> xColumn = GetObjectByIndex_Impl((USHORT)nIndex);
    uno::Any aAny;
    if (xColumn.is())
        aAny <<= xColumn;
    else
        throw lang::IndexOutOfBoundsException();
    return aAny;
}

uno::Type SAL_CALL ScTableColumnsObj::getElementType() throw(uno::RuntimeException)
{
    ScUnoGuard aGuard;
    return getCppuType((uno::Reference<table::XCellRange>*)0);
}

sal_Bool SAL_CALL ScTableColumnsObj::hasElements() throw(uno::RuntimeException)
{
    ScUnoGuard aGuard;
    return ( getCount() != 0 );
}

uno::Any SAL_CALL ScTableColumnsObj::getByName( const ::rtl::OUString& aName )
            throw(container::NoSuchElementException,
                    lang::WrappedTargetException, uno::RuntimeException)
{
    ScUnoGuard aGuard;
    uno::Reference<table::XCellRange> xColumn = GetObjectByName_Impl(aName);
    uno::Any aAny;
    if (xColumn.is())
        aAny <<= xColumn;
    else
        throw container::NoSuchElementException();
    return aAny;
}

uno::Sequence< ::rtl::OUString> SAL_CALL ScTableColumnsObj::getElementNames()
                                                throw(uno::RuntimeException)
{
    ScUnoGuard aGuard;
    USHORT nCount = nEndCol - nStartCol + 1;
    uno::Sequence< ::rtl::OUString> aSeq(nCount);
    ::rtl::OUString* pAry = aSeq.getArray();
    for (USHORT i=0; i<nCount; i++)
        pAry[i] = lcl_ColumnToString( nStartCol + i );

    return aSeq;
}

sal_Bool SAL_CALL ScTableColumnsObj::hasByName( const ::rtl::OUString& aName )
                                        throw(uno::RuntimeException)
{
    ScUnoGuard aGuard;
    USHORT nCol = 0;
    String aString = aName;
    if ( lcl_StringToColumn( aString, nCol ) )
        if ( pDocShell && nCol >= nStartCol && nCol <= nEndCol )
            return TRUE;

    return FALSE;		// nicht gefunden
}

// XPropertySet

uno::Reference<beans::XPropertySetInfo> SAL_CALL ScTableColumnsObj::getPropertySetInfo()
                                                        throw(uno::RuntimeException)
{
    ScUnoGuard aGuard;
    static uno::Reference<beans::XPropertySetInfo> aRef =
        new SfxItemPropertySetInfo( lcl_GetColumnsPropertyMap() );
    return aRef;
}

void SAL_CALL ScTableColumnsObj::setPropertyValue(
                        const ::rtl::OUString& aPropertyName, const uno::Any& aValue )
                throw(beans::UnknownPropertyException, beans::PropertyVetoException,
                        lang::IllegalArgumentException, lang::WrappedTargetException,
                        uno::RuntimeException)
{
    ScUnoGuard aGuard;
    if (!pDocShell)
        throw uno::RuntimeException();

    ScDocFunc aFunc(*pDocShell);
    ScDocument* pDoc = pDocShell->GetDocument();
    USHORT nColArr[2];
    nColArr[0] = nStartCol;
    nColArr[1] = nEndCol;
    String aNameString = aPropertyName;

    if ( aNameString.EqualsAscii( SC_UNONAME_CELLWID ) )
    {
        sal_Int32 nNewWidth;
        if ( aValue >>= nNewWidth )
            aFunc.SetWidthOrHeight( TRUE, 1, nColArr, nTab, SC_SIZE_ORIGINAL,
                                    (USHORT)HMMToTwips(nNewWidth), TRUE, TRUE );
    }
    else if ( aNameString.EqualsAscii( SC_UNONAME_CELLVIS ) )
    {
        BOOL bVis = ScUnoHelpFunctions::GetBoolFromAny( aValue );
        ScSizeMode eMode = bVis ? SC_SIZE_SHOW : SC_SIZE_DIRECT;
        aFunc.SetWidthOrHeight( TRUE, 1, nColArr, nTab, eMode, 0, TRUE, TRUE );
        //	SC_SIZE_DIRECT with size 0: hide
    }
    else if ( aNameString.EqualsAscii( SC_UNONAME_OWIDTH ) )
    {
        BOOL bOpt = ScUnoHelpFunctions::GetBoolFromAny( aValue );
        if (bOpt)
            aFunc.SetWidthOrHeight( TRUE, 1, nColArr, nTab,
                                    SC_SIZE_OPTIMAL, STD_EXTRA_WIDTH, TRUE, TRUE );
        // FALSE for columns currently has no effect
    }
    else if ( aNameString.EqualsAscii( SC_UNONAME_NEWPAGE ) || aNameString.EqualsAscii( SC_UNONAME_MANPAGE ) )
    {
        //!	single function to set/remove all breaks?
        BOOL bSet = ScUnoHelpFunctions::GetBoolFromAny( aValue );
        for (USHORT nCol=nStartCol; nCol<=nEndCol; nCol++)
            if (bSet)
                aFunc.InsertPageBreak( TRUE, ScAddress(nCol,0,nTab), TRUE, TRUE, TRUE );
            else
                aFunc.RemovePageBreak( TRUE, ScAddress(nCol,0,nTab), TRUE, TRUE, TRUE );
    }
}

uno::Any SAL_CALL ScTableColumnsObj::getPropertyValue( const ::rtl::OUString& aPropertyName )
                throw(beans::UnknownPropertyException, lang::WrappedTargetException,
                        uno::RuntimeException)
{
    ScUnoGuard aGuard;
    if (!pDocShell)
        throw uno::RuntimeException();

    ScDocument* pDoc = pDocShell->GetDocument();
    String aNameString = aPropertyName;
    uno::Any aAny;

    //!	loop over all columns for current state?

    if ( aNameString.EqualsAscii( SC_UNONAME_CELLWID ) )
    {
        // for hidden column, return original height
        USHORT nWidth = pDoc->GetOriginalWidth( nStartCol, nTab );
        aAny <<= (sal_Int32)TwipsToHMM(nWidth);
    }
    else if ( aNameString.EqualsAscii( SC_UNONAME_CELLVIS ) )
    {
        BOOL bVis = !(pDoc->GetColFlags( nStartCol, nTab ) & CR_HIDDEN);
        ScUnoHelpFunctions::SetBoolInAny( aAny, bVis );
    }
    else if ( aNameString.EqualsAscii( SC_UNONAME_OWIDTH ) )
    {
        BOOL bOpt = !(pDoc->GetColFlags( nStartCol, nTab ) & CR_MANUALSIZE);
        ScUnoHelpFunctions::SetBoolInAny( aAny, bOpt );
    }
    else if ( aNameString.EqualsAscii( SC_UNONAME_NEWPAGE ) )
    {
        BOOL bBreak = ( 0 != (pDoc->GetColFlags( nStartCol, nTab ) & (CR_PAGEBREAK|CR_MANUALBREAK)) );
        ScUnoHelpFunctions::SetBoolInAny( aAny, bBreak );
    }
    else if ( aNameString.EqualsAscii( SC_UNONAME_MANPAGE ) )
    {
        BOOL bBreak = ( 0 != (pDoc->GetColFlags( nStartCol, nTab ) & (CR_MANUALBREAK)) );
        ScUnoHelpFunctions::SetBoolInAny( aAny, bBreak );
    }

    return aAny;
}

SC_IMPL_DUMMY_PROPERTY_LISTENER( ScTableColumnsObj )

//------------------------------------------------------------------------

ScTableRowsObj::ScTableRowsObj(ScDocShell* pDocSh, USHORT nT, USHORT nSR, USHORT nER) :
    pDocShell( pDocSh ),
    nTab	 ( nT ),
    nStartRow( nSR ),
    nEndRow	 ( nER )
{
    pDocShell->GetDocument()->AddUnoObject(*this);
}

ScTableRowsObj::~ScTableRowsObj()
{
    if (pDocShell)
        pDocShell->GetDocument()->RemoveUnoObject(*this);
}

void ScTableRowsObj::Notify( SfxBroadcaster& rBC, const SfxHint& rHint )
{
    if ( rHint.ISA( ScUpdateRefHint ) )
    {
        const ScUpdateRefHint& rRef = (const ScUpdateRefHint&)rHint;

        //!	Referenz-Update fuer Tab und Start/Ende
    }
    else if ( rHint.ISA( SfxSimpleHint ) &&
            ((const SfxSimpleHint&)rHint).GetId() == SFX_HINT_DYING )
    {
        pDocShell = NULL;		// ungueltig geworden
    }
}

// XTableRows

ScTableRowObj* ScTableRowsObj::GetObjectByIndex_Impl(USHORT nIndex) const
{
    USHORT nRow = nIndex + nStartRow;
    if ( pDocShell && nRow <= nEndRow )
        return new ScTableRowObj( pDocShell, nRow, nTab );

    return NULL;	// falscher Index
}

void SAL_CALL ScTableRowsObj::insertByIndex( sal_Int32 nPosition, sal_Int32 nCount )
                                                throw(uno::RuntimeException)
{
    ScUnoGuard aGuard;
    BOOL bDone = FALSE;
    if ( pDocShell && nCount > 0 && nPosition >= 0 && nStartRow+nPosition <= nEndRow &&
            nStartRow+nPosition+nCount-1 <= MAXROW )
    {
        ScDocFunc aFunc(*pDocShell);
        ScRange aRange( 0, (USHORT)(nStartRow+nPosition), nTab,
                        MAXCOL, (USHORT)(nStartRow+nPosition+nCount-1), nTab );
        bDone = aFunc.InsertCells( aRange, INS_INSROWS, TRUE, TRUE );
    }
    if (!bDone)
        throw uno::RuntimeException();		// no other exceptions specified
}

void SAL_CALL ScTableRowsObj::removeByIndex( sal_Int32 nIndex, sal_Int32 nCount )
                                                throw(uno::RuntimeException)
{
    ScUnoGuard aGuard;
    BOOL bDone = FALSE;
    //	Der zu loeschende Bereich muss innerhalb des Objekts liegen
    if ( pDocShell && nCount > 0 && nIndex >= 0 && nStartRow+nIndex+nCount-1 <= nEndRow )
    {
        ScDocFunc aFunc(*pDocShell);
        ScRange aRange( 0, (USHORT)(nStartRow+nIndex), nTab,
                        MAXCOL, (USHORT)(nStartRow+nIndex+nCount-1), nTab );
        bDone = aFunc.DeleteCells( aRange, DEL_DELROWS, TRUE, TRUE );
    }
    if (!bDone)
        throw uno::RuntimeException();		// no other exceptions specified
}

// XEnumerationAccess

uno::Reference<container::XEnumeration> SAL_CALL ScTableRowsObj::createEnumeration()
                                                    throw(uno::RuntimeException)
{
    ScUnoGuard aGuard;
    return new ScIndexEnumeration(this, ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("com.sun.star.table.TableRowsEnumeration")));
}

// XIndexAccess

sal_Int32 SAL_CALL ScTableRowsObj::getCount() throw(uno::RuntimeException)
{
    ScUnoGuard aGuard;
    return nEndRow - nStartRow + 1;
}

uno::Any SAL_CALL ScTableRowsObj::getByIndex( sal_Int32 nIndex )
                            throw(lang::IndexOutOfBoundsException,
                                    lang::WrappedTargetException, uno::RuntimeException)
{
    ScUnoGuard aGuard;
    uno::Reference<table::XCellRange> xRow = GetObjectByIndex_Impl((USHORT)nIndex);
    uno::Any aAny;
    if (xRow.is())
        aAny <<= xRow;
    else
        throw lang::IndexOutOfBoundsException();
    return aAny;
}

uno::Type SAL_CALL ScTableRowsObj::getElementType() throw(uno::RuntimeException)
{
    ScUnoGuard aGuard;
    return getCppuType((uno::Reference<table::XCellRange>*)0);
}

sal_Bool SAL_CALL ScTableRowsObj::hasElements() throw(uno::RuntimeException)
{
    ScUnoGuard aGuard;
    return ( getCount() != 0 );
}

// XPropertySet

uno::Reference<beans::XPropertySetInfo> SAL_CALL ScTableRowsObj::getPropertySetInfo()
                                                        throw(uno::RuntimeException)
{
    ScUnoGuard aGuard;
    static uno::Reference<beans::XPropertySetInfo> aRef =
        new SfxItemPropertySetInfo( lcl_GetRowsPropertyMap() );
    return aRef;
}

void SAL_CALL ScTableRowsObj::setPropertyValue(
                        const ::rtl::OUString& aPropertyName, const uno::Any& aValue )
                throw(beans::UnknownPropertyException, beans::PropertyVetoException,
                        lang::IllegalArgumentException, lang::WrappedTargetException,
                        uno::RuntimeException)
{
    ScUnoGuard aGuard;
    if (!pDocShell)
        throw uno::RuntimeException();

    ScDocFunc aFunc(*pDocShell);
    ScDocument* pDoc = pDocShell->GetDocument();
    USHORT nRowArr[2];
    nRowArr[0] = nStartRow;
    nRowArr[1] = nEndRow;
    String aNameString = aPropertyName;

    if ( aNameString.EqualsAscii( SC_UNONAME_CELLHGT ) )
    {
        sal_Int32 nNewHeight;
        if ( aValue >>= nNewHeight )
            aFunc.SetWidthOrHeight( FALSE, 1, nRowArr, nTab, SC_SIZE_ORIGINAL,
                                    (USHORT)HMMToTwips(nNewHeight), TRUE, TRUE );
    }
    else if ( aNameString.EqualsAscii( SC_UNONAME_CELLVIS ) )
    {
        BOOL bVis = ScUnoHelpFunctions::GetBoolFromAny( aValue );
        ScSizeMode eMode = bVis ? SC_SIZE_SHOW : SC_SIZE_DIRECT;
        aFunc.SetWidthOrHeight( FALSE, 1, nRowArr, nTab, eMode, 0, TRUE, TRUE );
        //	SC_SIZE_DIRECT with size 0: hide
    }
    else if ( aNameString.EqualsAscii( SC_UNONAME_CELLFILT ) )
    {
        //!	undo etc.
        BOOL bFil = ScUnoHelpFunctions::GetBoolFromAny( aValue );
        for (USHORT nRow=nStartRow; nRow<=nEndRow; nRow++)
        {
            BYTE nFlags = pDoc->GetRowFlags(nRow, nTab);
            if (bFil)
                nFlags |= CR_FILTERED;
            else
                nFlags &= ~CR_FILTERED;
            pDoc->SetRowFlags(nRow, nTab, nFlags);
        }
    }
    else if ( aNameString.EqualsAscii( SC_UNONAME_OHEIGHT ) )
    {
        BOOL bOpt = ScUnoHelpFunctions::GetBoolFromAny( aValue );
        if (bOpt)
            aFunc.SetWidthOrHeight( FALSE, 1, nRowArr, nTab, SC_SIZE_OPTIMAL, 0, TRUE, TRUE );
        else
        {
            //!	manually set old heights again?
        }
    }
    else if ( aNameString.EqualsAscii( SC_UNONAME_NEWPAGE) || aNameString.EqualsAscii( SC_UNONAME_MANPAGE) )
    {
        //!	single function to set/remove all breaks?
        BOOL bSet = ScUnoHelpFunctions::GetBoolFromAny( aValue );
        for (USHORT nRow=nStartRow; nRow<=nEndRow; nRow++)
            if (bSet)
                aFunc.InsertPageBreak( FALSE, ScAddress(0,nRow,nTab), TRUE, TRUE, TRUE );
            else
                aFunc.RemovePageBreak( FALSE, ScAddress(0,nRow,nTab), TRUE, TRUE, TRUE );
    }
}

uno::Any SAL_CALL ScTableRowsObj::getPropertyValue( const ::rtl::OUString& aPropertyName )
                throw(beans::UnknownPropertyException, lang::WrappedTargetException,
                        uno::RuntimeException)
{
    ScUnoGuard aGuard;
    if (!pDocShell)
        throw uno::RuntimeException();

    ScDocument* pDoc = pDocShell->GetDocument();
    String aNameString = aPropertyName;
    uno::Any aAny;

    //!	loop over all rows for current state?

    if ( aNameString.EqualsAscii( SC_UNONAME_CELLHGT ) )
    {
        // for hidden row, return original height
        USHORT nHeight = pDoc->GetOriginalHeight( nStartRow, nTab );
        aAny <<= (sal_Int32)TwipsToHMM(nHeight);
    }
    else if ( aNameString.EqualsAscii( SC_UNONAME_CELLVIS ) )
    {
        BOOL bVis = !(pDoc->GetRowFlags( nStartRow, nTab ) & CR_HIDDEN);
        ScUnoHelpFunctions::SetBoolInAny( aAny, bVis );
    }
    else if ( aNameString.EqualsAscii( SC_UNONAME_CELLFILT ) )
    {
        BOOL bVis = ((pDoc->GetRowFlags( nStartRow, nTab ) & CR_FILTERED) != 0);
        ScUnoHelpFunctions::SetBoolInAny( aAny, bVis );
    }
    else if ( aNameString.EqualsAscii( SC_UNONAME_OHEIGHT ) )
    {
        BOOL bOpt = !(pDoc->GetRowFlags( nStartRow, nTab ) & CR_MANUALSIZE);
        ScUnoHelpFunctions::SetBoolInAny( aAny, bOpt );
    }
    else if ( aNameString.EqualsAscii( SC_UNONAME_NEWPAGE ) )
    {
        BOOL bBreak = ( 0 != (pDoc->GetRowFlags( nStartRow, nTab ) & (CR_PAGEBREAK|CR_MANUALBREAK)) );
        ScUnoHelpFunctions::SetBoolInAny( aAny, bBreak );
    }
    else if ( aNameString.EqualsAscii( SC_UNONAME_MANPAGE ) )
    {
        BOOL bBreak = ( 0 != (pDoc->GetRowFlags( nStartRow, nTab ) & (CR_MANUALBREAK)) );
        ScUnoHelpFunctions::SetBoolInAny( aAny, bBreak );
    }

    return aAny;
}

SC_IMPL_DUMMY_PROPERTY_LISTENER( ScTableRowsObj )

//------------------------------------------------------------------------

ScSpreadsheetSettingsObj::ScSpreadsheetSettingsObj(ScDocShell* pDocSh) :
    pDocShell( pDocSh )
{
    pDocShell->GetDocument()->AddUnoObject(*this);
}

ScSpreadsheetSettingsObj::~ScSpreadsheetSettingsObj()
{
    if (pDocShell)
        pDocShell->GetDocument()->RemoveUnoObject(*this);
}

void ScSpreadsheetSettingsObj::Notify( SfxBroadcaster& rBC, const SfxHint& rHint )
{
    //	Referenz-Update interessiert hier nicht

    if ( rHint.ISA( SfxSimpleHint ) &&
            ((const SfxSimpleHint&)rHint).GetId() == SFX_HINT_DYING )
    {
        pDocShell = NULL;		// ungueltig geworden
    }
}

// XPropertySet

uno::Reference<beans::XPropertySetInfo> SAL_CALL ScSpreadsheetSettingsObj::getPropertySetInfo()
                                                        throw(uno::RuntimeException)
{
    //!	muss noch
    return NULL;
}

void SAL_CALL ScSpreadsheetSettingsObj::setPropertyValue(
                        const ::rtl::OUString& aPropertyName, const uno::Any& aValue )
                throw(beans::UnknownPropertyException, beans::PropertyVetoException,
                        lang::IllegalArgumentException, lang::WrappedTargetException,
                        uno::RuntimeException)
{
    //!	muss noch
}

uno::Any SAL_CALL ScSpreadsheetSettingsObj::getPropertyValue( const ::rtl::OUString& aPropertyName )
                throw(beans::UnknownPropertyException, lang::WrappedTargetException,
                        uno::RuntimeException)
{
    //!	muss noch
    return uno::Any();
}

SC_IMPL_DUMMY_PROPERTY_LISTENER( ScSpreadsheetSettingsObj )

//------------------------------------------------------------------------

ScAnnotationsObj::ScAnnotationsObj(ScDocShell* pDocSh, USHORT nT) :
    pDocShell( pDocSh ),
    nTab( nT )
{
    pDocShell->GetDocument()->AddUnoObject(*this);
}

ScAnnotationsObj::~ScAnnotationsObj()
{
    if (pDocShell)
        pDocShell->GetDocument()->RemoveUnoObject(*this);
}

void ScAnnotationsObj::Notify( SfxBroadcaster& rBC, const SfxHint& rHint )
{
    //!	nTab bei Referenz-Update anpassen!!!

    if ( rHint.ISA( SfxSimpleHint ) &&
            ((const SfxSimpleHint&)rHint).GetId() == SFX_HINT_DYING )
    {
        pDocShell = NULL;		// ungueltig geworden
    }
}

BOOL ScAnnotationsObj::GetAddressByIndex_Impl( ULONG nIndex, ScAddress& rPos ) const
{
    if (pDocShell)
    {
        ULONG nFound = 0;
        ScDocument* pDoc = pDocShell->GetDocument();
        ScCellIterator aCellIter( pDoc, 0,0, nTab, MAXCOL,MAXROW, nTab );
        ScBaseCell* pCell = aCellIter.GetFirst();
        while (pCell)
        {
            if (pCell->GetNotePtr())
            {
                if (nFound == nIndex)
                {
                    rPos = ScAddress( aCellIter.GetCol(), aCellIter.GetRow(), aCellIter.GetTab() );
                    return TRUE;
                }
                ++nFound;
            }
            pCell = aCellIter.GetNext();
        }
    }
    return FALSE;	// nicht gefunden
}

// XSheetAnnotations

ScAnnotationObj* ScAnnotationsObj::GetObjectByIndex_Impl(USHORT nIndex) const
{
    if (pDocShell)
    {
        ScAddress aPos;
        if ( GetAddressByIndex_Impl( nIndex, aPos ) )
            return new ScAnnotationObj( pDocShell, aPos );
    }
    return NULL;
}

void SAL_CALL ScAnnotationsObj::insertNew( const table::CellAddress& aPosition,
                                            const ::rtl::OUString& aText )
                                                throw(uno::RuntimeException)
{
    ScUnoGuard aGuard;
    if (pDocShell)
    {
        DBG_ASSERT( aPosition.Sheet == nTab, "addAnnotation mit falschem Sheet" );
        ScAddress aPos( (USHORT)aPosition.Column, (USHORT)aPosition.Row, nTab );

        String aString = aText;

        ScDocFunc aFunc(*pDocShell);
        aFunc.SetNoteText( aPos, aString, TRUE );
    }
}

void SAL_CALL ScAnnotationsObj::removeByIndex( sal_Int32 nIndex ) throw(uno::RuntimeException)
{
    ScUnoGuard aGuard;
    if (pDocShell)
    {
        ScAddress aPos;
        if ( GetAddressByIndex_Impl( nIndex, aPos ) )
        {
            ScMarkData aMarkData;
            aMarkData.SelectTable( aPos.Tab(), TRUE );
            aMarkData.SetMultiMarkArea( ScRange(aPos) );

            ScDocFunc aFunc(*pDocShell);
            aFunc.DeleteContents( aMarkData, IDF_NOTE, TRUE, TRUE );
        }
    }
}

// XEnumerationAccess

uno::Reference<container::XEnumeration> SAL_CALL ScAnnotationsObj::createEnumeration()
                                                    throw(uno::RuntimeException)
{
    //!	iterate directly (more efficiently)?

    ScUnoGuard aGuard;
    return new ScIndexEnumeration(this, ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("com.sun.star.sheet.CellAnnotationsEnumeration")));
}

// XIndexAccess

sal_Int32 SAL_CALL ScAnnotationsObj::getCount() throw(uno::RuntimeException)
{
    ScUnoGuard aGuard;
    ULONG nCount = 0;
    if (pDocShell)
    {
        ScDocument* pDoc = pDocShell->GetDocument();
        ScCellIterator aCellIter( pDoc, 0,0, nTab, MAXCOL,MAXROW, nTab );
        ScBaseCell* pCell = aCellIter.GetFirst();
        while (pCell)
        {
            if (pCell->GetNotePtr())
                ++nCount;
            pCell = aCellIter.GetNext();
        }
    }
    return nCount;
}

uno::Any SAL_CALL ScAnnotationsObj::getByIndex( sal_Int32 nIndex )
                            throw(lang::IndexOutOfBoundsException,
                                    lang::WrappedTargetException, uno::RuntimeException)
{
    ScUnoGuard aGuard;
    uno::Reference<sheet::XSheetAnnotation> xAnnotation = GetObjectByIndex_Impl((USHORT)nIndex);
    uno::Any aAny;
    if (xAnnotation.is())
        aAny <<= xAnnotation;
    else
        throw lang::IndexOutOfBoundsException();
    return aAny;
}

uno::Type SAL_CALL ScAnnotationsObj::getElementType() throw(uno::RuntimeException)
{
    ScUnoGuard aGuard;
    return getCppuType((uno::Reference<sheet::XSheetAnnotation>*)0);
}

sal_Bool SAL_CALL ScAnnotationsObj::hasElements() throw(uno::RuntimeException)
{
    ScUnoGuard aGuard;
    return ( getCount() != 0 );
}

//------------------------------------------------------------------------

ScScenariosObj::ScScenariosObj(ScDocShell* pDocSh, USHORT nT) :
    pDocShell( pDocSh ),
    nTab	 ( nT )
{
    pDocShell->GetDocument()->AddUnoObject(*this);
}

ScScenariosObj::~ScScenariosObj()
{
    if (pDocShell)
        pDocShell->GetDocument()->RemoveUnoObject(*this);
}

void ScScenariosObj::Notify( SfxBroadcaster& rBC, const SfxHint& rHint )
{
    if ( rHint.ISA( ScUpdateRefHint ) )
    {
        const ScUpdateRefHint& rRef = (const ScUpdateRefHint&)rHint;

        //!	Referenz-Update fuer Tab und Start/Ende
    }
    else if ( rHint.ISA( SfxSimpleHint ) &&
            ((const SfxSimpleHint&)rHint).GetId() == SFX_HINT_DYING )
    {
        pDocShell = NULL;		// ungueltig geworden
    }
}

// XScenarios

BOOL ScScenariosObj::GetScenarioIndex_Impl( const ::rtl::OUString& rName, USHORT& rIndex )
{
    //!	Case-insensitiv ????

    if ( pDocShell )
    {
        String aString = rName;

        String aTabName;
        ScDocument* pDoc = pDocShell->GetDocument();
        USHORT nCount = (USHORT)getCount();
        for (USHORT i=0; i<nCount; i++)
            if (pDoc->GetName( nTab+i+1, aTabName ))
                if ( aTabName == aString )
                {
                    rIndex = i;
                    return TRUE;
                }
    }

    return FALSE;
}

ScTableSheetObj* ScScenariosObj::GetObjectByIndex_Impl(USHORT nIndex)
{
    USHORT nCount = (USHORT)getCount();
    if ( pDocShell && nIndex < nCount )
        return new ScTableSheetObj( pDocShell, nTab+nIndex+1 );

    return NULL;	// kein Dokument oder falscher Index
}

ScTableSheetObj* ScScenariosObj::GetObjectByName_Impl(const ::rtl::OUString& aName)
{
    USHORT nIndex;
    if ( pDocShell && GetScenarioIndex_Impl( aName, nIndex ) )
        return new ScTableSheetObj( pDocShell, nTab+nIndex+1 );

    return NULL;	// nicht gefunden
}

void SAL_CALL ScScenariosObj::addNewByName( const ::rtl::OUString& aName,
                                const uno::Sequence<table::CellRangeAddress>& aRanges,
                                const ::rtl::OUString& aComment )
                                    throw(uno::RuntimeException)
{
    ScUnoGuard aGuard;
    if ( pDocShell )
    {
        ScMarkData aMarkData;
        aMarkData.SelectTable( nTab, TRUE );

        USHORT nRangeCount = (USHORT)aRanges.getLength();
        if (nRangeCount)
        {
            const table::CellRangeAddress* pAry = aRanges.getConstArray();
            for (USHORT i=0; i<nRangeCount; i++)
            {
                DBG_ASSERT( pAry[i].Sheet == nTab, "addScenario mit falscher Tab" );
                ScRange aRange( (USHORT)pAry[i].StartColumn, (USHORT)pAry[i].StartRow, nTab,
                                (USHORT)pAry[i].EndColumn,   (USHORT)pAry[i].EndRow,   nTab );

                aMarkData.SetMultiMarkArea( aRange );
            }
        }

        String aNameStr = aName;
        String aCommStr = aComment;

        Color aColor( COL_LIGHTGRAY );	// Default
        USHORT nFlags = SC_SCENARIO_SHOWFRAME | SC_SCENARIO_PRINTFRAME | SC_SCENARIO_TWOWAY;

        pDocShell->MakeScenario( nTab, aNameStr, aCommStr, aColor, nFlags, aMarkData );
    }
}

void SAL_CALL ScScenariosObj::removeByName( const ::rtl::OUString& aName )
                                            throw(uno::RuntimeException)
{
    ScUnoGuard aGuard;
    USHORT nIndex;
    if ( pDocShell && GetScenarioIndex_Impl( aName, nIndex ) )
    {
        ScDocFunc aFunc(*pDocShell);
        aFunc.DeleteTable( nTab+nIndex+1, TRUE, TRUE );
    }
}

// XEnumerationAccess

uno::Reference<container::XEnumeration> SAL_CALL ScScenariosObj::createEnumeration()
                                                    throw(uno::RuntimeException)
{
    ScUnoGuard aGuard;
    return new ScIndexEnumeration(this, ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("com.sun.star.sheet.ScenariosEnumeration")));
}

// XIndexAccess

sal_Int32 SAL_CALL ScScenariosObj::getCount() throw(uno::RuntimeException)
{
    ScUnoGuard aGuard;
    USHORT nCount = 0;
    if ( pDocShell )
    {
        ScDocument* pDoc = pDocShell->GetDocument();
        if (!pDoc->IsScenario(nTab))
        {
            USHORT nTabCount = pDoc->GetTableCount();
            USHORT nNext = nTab + 1;
            while (nNext < nTabCount && pDoc->IsScenario(nNext))
            {
                ++nCount;
                ++nNext;
            }
        }
    }
    return nCount;
}

uno::Any SAL_CALL ScScenariosObj::getByIndex( sal_Int32 nIndex )
                            throw(lang::IndexOutOfBoundsException,
                                    lang::WrappedTargetException, uno::RuntimeException)
{
    ScUnoGuard aGuard;
    uno::Reference<sheet::XScenario> xScen = GetObjectByIndex_Impl((USHORT)nIndex);
    uno::Any aAny;
    if (xScen.is())
        aAny <<= xScen;
    else
        throw lang::IndexOutOfBoundsException();
    return aAny;
}

uno::Type SAL_CALL ScScenariosObj::getElementType() throw(uno::RuntimeException)
{
    ScUnoGuard aGuard;
    return getCppuType((uno::Reference<sheet::XScenario>*)0);
}

sal_Bool SAL_CALL ScScenariosObj::hasElements() throw(uno::RuntimeException)
{
    ScUnoGuard aGuard;
    return ( getCount() != 0 );
}

uno::Any SAL_CALL ScScenariosObj::getByName( const ::rtl::OUString& aName )
            throw(container::NoSuchElementException,
                    lang::WrappedTargetException, uno::RuntimeException)
{
    ScUnoGuard aGuard;
    uno::Reference<sheet::XScenario> xScen = GetObjectByName_Impl(aName);
    uno::Any aAny;
    if (xScen.is())
        aAny <<= xScen;
    else
        throw container::NoSuchElementException();
    return aAny;
}

uno::Sequence< ::rtl::OUString> SAL_CALL ScScenariosObj::getElementNames()
                                                throw(uno::RuntimeException)
{
    ScUnoGuard aGuard;
    USHORT nCount = (USHORT)getCount();
    uno::Sequence< ::rtl::OUString> aSeq(nCount);

    if ( pDocShell )	// sonst ist auch Count = 0
    {
        String aTabName;
        ScDocument* pDoc = pDocShell->GetDocument();
        ::rtl::OUString* pAry = aSeq.getArray();
        for (USHORT i=0; i<nCount; i++)
            if (pDoc->GetName( nTab+i+1, aTabName ))
                pAry[i] = aTabName;
    }

    return aSeq;
}

sal_Bool SAL_CALL ScScenariosObj::hasByName( const ::rtl::OUString& aName )
                                        throw(uno::RuntimeException)
{
    ScUnoGuard aGuard;
    USHORT nIndex;
    return GetScenarioIndex_Impl( aName, nIndex );
}





}
