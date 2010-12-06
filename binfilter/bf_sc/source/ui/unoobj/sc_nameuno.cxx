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

#ifdef _MSC_VER
#pragma hdrstop
#endif

#include <com/sun/star/beans/PropertyAttribute.hpp>
#include <com/sun/star/sheet/NamedRangeFlag.hpp>
#include <com/sun/star/awt/XBitmap.hpp>

using namespace ::com::sun::star;


#include "nameuno.hxx"
#include "miscuno.hxx"
#include "cellsuno.hxx"
#include "convuno.hxx"
#include "targuno.hxx"
#include "docsh.hxx"
#include "docfunc.hxx"
#include "rangenam.hxx"
#include "namecrea.hxx"		// NAME_TOP etc.
#include <vcl/svapp.hxx>
#include "unonames.hxx"
namespace binfilter {

//------------------------------------------------------------------------

const SfxItemPropertyMap* lcl_GetNamedRangeMap()
{
    static SfxItemPropertyMap aNamedRangeMap_Impl[] =
    {
        {MAP_CHAR_LEN(SC_UNO_LINKDISPBIT),	0,	&getCppuType((uno::Reference<awt::XBitmap>*)0),	beans::PropertyAttribute::READONLY, 0 },
        {MAP_CHAR_LEN(SC_UNO_LINKDISPNAME),	0,	&getCppuType((::rtl::OUString*)0),				beans::PropertyAttribute::READONLY, 0 },
        {0,0,0,0}
    };
    return aNamedRangeMap_Impl;
}

//------------------------------------------------------------------------

#define SCNAMEDRANGEOBJ_SERVICE		"com.sun.star.sheet.NamedRange"

SC_SIMPLE_SERVICE_INFO( ScLabelRangeObj, "ScLabelRangeObj", "com.sun.star.sheet.LabelRange" )
SC_SIMPLE_SERVICE_INFO( ScLabelRangesObj, "ScLabelRangesObj", "com.sun.star.sheet.LabelRanges" )
SC_SIMPLE_SERVICE_INFO( ScNamedRangesObj, "ScNamedRangesObj", "com.sun.star.sheet.NamedRanges" )

//------------------------------------------------------------------------

sal_Bool lcl_UserVisibleName( const ScRangeData* pData )
{
    //!	als Methode an ScRangeData

    return ( pData && !pData->HasType( RT_DATABASE ) && !pData->HasType( RT_SHARED ) );
}

//------------------------------------------------------------------------

ScNamedRangeObj::ScNamedRangeObj(ScDocShell* pDocSh, const String& rNm) :
    pDocShell( pDocSh ),
    aName( rNm )
{
    pDocShell->GetDocument()->AddUnoObject(*this);
}

ScNamedRangeObj::~ScNamedRangeObj()
{
    if (pDocShell)
        pDocShell->GetDocument()->RemoveUnoObject(*this);
}

void ScNamedRangeObj::Notify( SfxBroadcaster& rBC, const SfxHint& rHint )
{
    //	Ref-Update interessiert nicht

    if ( rHint.ISA( SfxSimpleHint ) && ((const SfxSimpleHint&)rHint).GetId() == SFX_HINT_DYING )
        pDocShell = NULL;		// ungueltig geworden
}

// Hilfsfuntionen

ScRangeData* ScNamedRangeObj::GetRangeData_Impl()
{
    ScRangeData* pRet = NULL;
    if (pDocShell)
    {
        ScRangeName* pNames = pDocShell->GetDocument()->GetRangeName();
        if (pNames)
        {
            sal_uInt16 nPos = 0;
            if (pNames->SearchName( aName, nPos ))
            {
                pRet = (*pNames)[nPos];
                pRet->ValidateTabRefs();		// adjust relative tab refs to valid tables
            }
        }
    }
    return pRet;
}

// sheet::XNamedRange

void ScNamedRangeObj::Modify_Impl( const String* pNewName, const String* pNewContent,
                                    const ScAddress* pNewPos, const sal_uInt16* pNewType )
{
    if (pDocShell)
    {
        ScDocument* pDoc = pDocShell->GetDocument();
        ScRangeName* pNames = pDoc->GetRangeName();
        if (pNames)
        {
            ScRangeName aNewRanges( *pNames );
            sal_uInt16 nPos = 0;
            if (aNewRanges.SearchName( aName, nPos ))
            {
                ScRangeData* pOld = (*pNames)[nPos];

                String aInsName = pOld->GetName();
                if (pNewName)
                    aInsName = *pNewName;
                String aContent;				// Inhalt immer ueber Strings ->
                pOld->GetEnglishSymbol(aContent);		//	keine Probleme mit geaenderter Position etc.
                if (pNewContent)
                    aContent = *pNewContent;
                ScAddress aPos = pOld->GetPos();
                if (pNewPos)
                    aPos = *pNewPos;
                sal_uInt16 nType = pOld->GetType();
                if (pNewType)
                    nType = *pNewType;

                ScRangeData* pNew = new ScRangeData( pDoc, aInsName, aContent,
                                                    aPos, nType, sal_True );
                pNew->SetIndex( pOld->GetIndex() );

                aNewRanges.AtFree( nPos );
                if ( aNewRanges.Insert(pNew) )
                {
                    ScDocFunc aFunc(*pDocShell);
                    aFunc.ModifyRangeNames( aNewRanges, sal_True );

                    aName = aInsName;	//! broadcast?
                }
                else
                    delete pNew;		//! uno::Exception/Fehler oder so
            }
        }
    }
}


::rtl::OUString SAL_CALL ScNamedRangeObj::getName() throw(uno::RuntimeException)
{
    SolarMutexGuard aGuard;
    return aName;
}

void SAL_CALL ScNamedRangeObj::setName( const ::rtl::OUString& aNewName )
                                                throw(uno::RuntimeException)
{
    SolarMutexGuard aGuard;
    //!	Formeln anpassen ?????

    String aNewStr = aNewName;
    Modify_Impl( &aNewStr, NULL, NULL, NULL );

    if ( aName != aNewStr )					// some error occurred...
        throw uno::RuntimeException();		// no other exceptions specified
}

::rtl::OUString SAL_CALL ScNamedRangeObj::getContent() throw(uno::RuntimeException)
{
    SolarMutexGuard aGuard;
    String aContent;
    ScRangeData* pData = GetRangeData_Impl();
    if (pData)
        pData->GetEnglishSymbol(aContent);
    return aContent;
}

void SAL_CALL ScNamedRangeObj::setContent( const ::rtl::OUString& aContent )
                                                throw(uno::RuntimeException)
{
    SolarMutexGuard aGuard;
    String aContStr = aContent;
    Modify_Impl( NULL, &aContStr, NULL, NULL );
}

table::CellAddress SAL_CALL ScNamedRangeObj::getReferencePosition()
                                                throw(uno::RuntimeException)
{
    SolarMutexGuard aGuard;
    ScAddress aPos;
    ScRangeData* pData = GetRangeData_Impl();
    if (pData)
        aPos = pData->GetPos();
    table::CellAddress aAddress;
    aAddress.Column	= aPos.Col();
    aAddress.Row	= aPos.Row();
    aAddress.Sheet	= aPos.Tab();
    if (pDocShell)
    {
        USHORT nDocTabs = pDocShell->GetDocument()->GetTableCount();
        if ( aAddress.Sheet >= nDocTabs && nDocTabs > 0 )
        {
            //	Even after ValidateTabRefs, the position can be invalid if
            //	the content points to preceding tables. The resulting string
            //	is invalid in any case, so the position is just shifted.
            aAddress.Sheet = nDocTabs - 1;
        }
    }
    return aAddress;
}

void SAL_CALL ScNamedRangeObj::setReferencePosition( const table::CellAddress& aReferencePosition )
                                                throw(uno::RuntimeException)
{
    SolarMutexGuard aGuard;
    ScAddress aPos( (USHORT)aReferencePosition.Column, (USHORT)aReferencePosition.Row, aReferencePosition.Sheet );
    Modify_Impl( NULL, NULL, &aPos, NULL );
}

sal_Int32 SAL_CALL ScNamedRangeObj::getType() throw(uno::RuntimeException)
{
    SolarMutexGuard aGuard;
    sal_Int32 nType=0;
    ScRangeData* pData = GetRangeData_Impl();
    if (pData)
    {
        //	interne RT_* Flags werden weggelassen

        if ( pData->HasType(RT_CRITERIA) )	nType |= sheet::NamedRangeFlag::FILTER_CRITERIA;
        if ( pData->HasType(RT_PRINTAREA) )	nType |= sheet::NamedRangeFlag::PRINT_AREA;
        if ( pData->HasType(RT_COLHEADER) )	nType |= sheet::NamedRangeFlag::COLUMN_HEADER;
        if ( pData->HasType(RT_ROWHEADER) )	nType |= sheet::NamedRangeFlag::ROW_HEADER;
    }
    return nType;
}

void SAL_CALL ScNamedRangeObj::setType( sal_Int32 nUnoType ) throw(uno::RuntimeException)
{
    SolarMutexGuard aGuard;
    sal_uInt16 nNewType = RT_NAME;
    if ( nUnoType & sheet::NamedRangeFlag::FILTER_CRITERIA )	nNewType |= RT_CRITERIA;
    if ( nUnoType & sheet::NamedRangeFlag::PRINT_AREA )			nNewType |= RT_PRINTAREA;
    if ( nUnoType & sheet::NamedRangeFlag::COLUMN_HEADER )		nNewType |= RT_COLHEADER;
    if ( nUnoType & sheet::NamedRangeFlag::ROW_HEADER )			nNewType |= RT_ROWHEADER;

    Modify_Impl( NULL, NULL, NULL, &nNewType );
}

// XCellRangeSource

uno::Reference<table::XCellRange> SAL_CALL ScNamedRangeObj::getReferredCells()
                                                throw(uno::RuntimeException)
{
    SolarMutexGuard aGuard;
    ScRange aRange;
    ScRangeData* pData = GetRangeData_Impl();
    if ( pData && pData->IsReference( aRange ) )
    {
        //!	static Funktion um ScCellObj/ScCellRangeObj zu erzeugen am ScCellRangeObj ???

        if ( aRange.aStart == aRange.aEnd )
            return new ScCellObj( pDocShell, aRange.aStart );
        else
            return new ScCellRangeObj( pDocShell, aRange );
    }
    return NULL;
}

// beans::XPropertySet

uno::Reference<beans::XPropertySetInfo> SAL_CALL ScNamedRangeObj::getPropertySetInfo()
                                                        throw(uno::RuntimeException)
{
    SolarMutexGuard aGuard;
    static uno::Reference< beans::XPropertySetInfo >  aRef = new SfxItemPropertySetInfo( lcl_GetNamedRangeMap() );
    return aRef;
}

void SAL_CALL ScNamedRangeObj::setPropertyValue(
                        const ::rtl::OUString& aPropertyName, const uno::Any& aValue )
                throw(beans::UnknownPropertyException, beans::PropertyVetoException,
                        lang::IllegalArgumentException, lang::WrappedTargetException,
                        uno::RuntimeException)
{
    //	everything is read-only
}

uno::Any SAL_CALL ScNamedRangeObj::getPropertyValue( const ::rtl::OUString& aPropertyName )
                throw(beans::UnknownPropertyException, lang::WrappedTargetException,
                        uno::RuntimeException)
{
    SolarMutexGuard aGuard;
    uno::Any aRet;
    String aString = aPropertyName;
    if ( aString.EqualsAscii( SC_UNO_LINKDISPBIT ) )
    {
        //	no target bitmaps for individual entries (would be all equal)
        // ScLinkTargetTypeObj::SetLinkTargetBitmap( aRet, SC_LINKTARGETTYPE_RANGENAME );
    }
    else if ( aString.EqualsAscii( SC_UNO_LINKDISPNAME ) )
        aRet <<= ::rtl::OUString( aName );
    return aRet;
}

SC_IMPL_DUMMY_PROPERTY_LISTENER( ScNamedRangeObj )

// lang::XServiceInfo

::rtl::OUString SAL_CALL ScNamedRangeObj::getImplementationName() throw(uno::RuntimeException)
{
    return ::rtl::OUString( RTL_CONSTASCII_USTRINGPARAM( "ScNamedRangeObj" ));
}

sal_Bool SAL_CALL ScNamedRangeObj::supportsService( const ::rtl::OUString& rServiceName )
                                                    throw(uno::RuntimeException)
{
    String aServiceStr( rServiceName );
    return aServiceStr.EqualsAscii( SCNAMEDRANGEOBJ_SERVICE );
}

uno::Sequence< ::rtl::OUString> SAL_CALL ScNamedRangeObj::getSupportedServiceNames()
                                                    throw(uno::RuntimeException)
{
    uno::Sequence< ::rtl::OUString> aRet(1);
    ::rtl::OUString* pArray = aRet.getArray();
    pArray[0] = ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM( SCNAMEDRANGEOBJ_SERVICE ));
    return aRet;
}

//------------------------------------------------------------------------

ScNamedRangesObj::ScNamedRangesObj(ScDocShell* pDocSh) :
    pDocShell( pDocSh )
{
    pDocShell->GetDocument()->AddUnoObject(*this);
}

ScNamedRangesObj::~ScNamedRangesObj()
{
    if (pDocShell)
        pDocShell->GetDocument()->RemoveUnoObject(*this);
}

void ScNamedRangesObj::Notify( SfxBroadcaster& rBC, const SfxHint& rHint )
{
    //	Referenz-Update interessiert hier nicht

    if ( rHint.ISA( SfxSimpleHint ) &&
            ((const SfxSimpleHint&)rHint).GetId() == SFX_HINT_DYING )
    {
        pDocShell = NULL;		// ungueltig geworden
    }
}

// sheet::XNamedRanges

ScNamedRangeObj* ScNamedRangesObj::GetObjectByIndex_Impl(sal_uInt16 nIndex)
{
    if (pDocShell)
    {
        ScRangeName* pNames = pDocShell->GetDocument()->GetRangeName();
        if (pNames)
        {
            sal_uInt16 nCount = pNames->GetCount();
            sal_uInt16 nPos = 0;
            for (sal_uInt16 i=0; i<nCount; i++)
            {
                ScRangeData* pData = (*pNames)[i];
                if (lcl_UserVisibleName(pData))			// interne weglassen
                {
                    if ( nPos == nIndex )
                        return new ScNamedRangeObj( pDocShell, pData->GetName() );
                    ++nPos;
                }
            }
        }
    }
    return NULL;
}

ScNamedRangeObj* ScNamedRangesObj::GetObjectByName_Impl(const ::rtl::OUString& aName)
{
    if ( pDocShell && hasByName(aName) )
    {
        String aString = aName;
        return new ScNamedRangeObj( pDocShell, aString );
    }
    return NULL;
}

void SAL_CALL ScNamedRangesObj::addNewByName( const ::rtl::OUString& aName,
        const ::rtl::OUString& aContent, const table::CellAddress& aPosition,
        sal_Int32 nUnoType ) throw(uno::RuntimeException)
{
    SolarMutexGuard aGuard;
    String aNameStr = aName;
    String aContStr = aContent;
    ScAddress aPos( (USHORT)aPosition.Column, (USHORT)aPosition.Row, aPosition.Sheet );

    sal_uInt16 nNewType = RT_NAME;
    if ( nUnoType & sheet::NamedRangeFlag::FILTER_CRITERIA )	nNewType |= RT_CRITERIA;
    if ( nUnoType & sheet::NamedRangeFlag::PRINT_AREA )			nNewType |= RT_PRINTAREA;
    if ( nUnoType & sheet::NamedRangeFlag::COLUMN_HEADER )		nNewType |= RT_COLHEADER;
    if ( nUnoType & sheet::NamedRangeFlag::ROW_HEADER )			nNewType |= RT_ROWHEADER;

    BOOL bDone = FALSE;
    if (pDocShell)
    {
        ScDocument* pDoc = pDocShell->GetDocument();
        ScRangeName* pNames = pDoc->GetRangeName();
        USHORT nIndex = 0;
        if (pNames && !pNames->SearchName(aNameStr, nIndex))
        {
            ScRangeName aNewRanges( *pNames );
            ScRangeData* pNew = new ScRangeData( pDoc, aNameStr, aContStr,
                                                aPos, nNewType, sal_True );
            if ( aNewRanges.Insert(pNew) )
            {
                ScDocFunc aFunc(*pDocShell);
                aFunc.ModifyRangeNames( aNewRanges, sal_True );
                bDone = TRUE;
            }
            else
                delete pNew;
        }
    }

    if (!bDone)
        throw uno::RuntimeException();		// no other exceptions specified
}

void SAL_CALL ScNamedRangesObj::addNewFromTitles( const table::CellRangeAddress& aSource,
                                    sheet::Border aBorder ) throw(uno::RuntimeException)
{
    SolarMutexGuard aGuard;
    //!	das darf kein enum sein, weil mehrere Bits gesetzt sein koennen !!!

    sal_Bool bTop    = ( aBorder == sheet::Border_TOP );
    sal_Bool bLeft   = ( aBorder == sheet::Border_LEFT );
    sal_Bool bBottom = ( aBorder == sheet::Border_BOTTOM );
    sal_Bool bRight  = ( aBorder == sheet::Border_RIGHT );

    ScRange aRange;
    ScUnoConversion::FillScRange( aRange, aSource );

    sal_uInt16 nFlags = 0;
    if (bTop)	 nFlags |= NAME_TOP;
    if (bLeft)	 nFlags |= NAME_LEFT;
    if (bBottom) nFlags |= NAME_BOTTOM;
    if (bRight)	 nFlags |= NAME_RIGHT;

    if (nFlags)
    {
        ScDocFunc aFunc(*pDocShell);
        aFunc.CreateNames( aRange, nFlags, sal_True );
    }
}

void SAL_CALL ScNamedRangesObj::removeByName( const ::rtl::OUString& aName )
                                                throw(uno::RuntimeException)
{
    SolarMutexGuard aGuard;
    BOOL bDone = FALSE;
    if (pDocShell)
    {
        ScRangeName* pNames = pDocShell->GetDocument()->GetRangeName();
        if (pNames)
        {
            String aString = aName;
            sal_uInt16 nPos = 0;
            if (pNames->SearchName( aString, nPos ))
                if ( lcl_UserVisibleName((*pNames)[nPos]) )
                {
                    ScRangeName aNewRanges(*pNames);
                    aNewRanges.AtFree(nPos);
                    ScDocFunc aFunc(*pDocShell);
                    aFunc.ModifyRangeNames( aNewRanges, sal_True );
                    bDone = TRUE;
                }
        }
    }

    if (!bDone)
        throw uno::RuntimeException();		// no other exceptions specified
}

void SAL_CALL ScNamedRangesObj::outputList( const table::CellAddress& aOutputPosition )
                                                throw(uno::RuntimeException)
{
    SolarMutexGuard aGuard;
    ScAddress aPos( (USHORT)aOutputPosition.Column, (USHORT)aOutputPosition.Row, aOutputPosition.Sheet );
    if (pDocShell)
    {
        ScDocFunc aFunc(*pDocShell);
        aFunc.InsertNameList( aPos, sal_True );
    }
}

// container::XEnumerationAccess

uno::Reference<container::XEnumeration> SAL_CALL ScNamedRangesObj::createEnumeration()
                                                    throw(uno::RuntimeException)
{
    SolarMutexGuard aGuard;
    return new ScIndexEnumeration(this, ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("com.sun.star.sheet.NamedRangesEnumeration")));
}

// container::XIndexAccess

sal_Int32 SAL_CALL ScNamedRangesObj::getCount() throw(uno::RuntimeException)
{
    SolarMutexGuard aGuard;
    long nRet = 0;
    if (pDocShell)
    {
        ScRangeName* pNames = pDocShell->GetDocument()->GetRangeName();
        if (pNames)
        {
            sal_uInt16 nCount = pNames->GetCount();
            for (sal_uInt16 i=0; i<nCount; i++)
                if (lcl_UserVisibleName( (*pNames)[i] ))	// interne weglassen
                    ++nRet;
        }
    }
    return nRet;
}

uno::Any SAL_CALL ScNamedRangesObj::getByIndex( sal_Int32 nIndex )
                            throw(lang::IndexOutOfBoundsException,
                                    lang::WrappedTargetException, uno::RuntimeException)
{
    SolarMutexGuard aGuard;
    uno::Reference< sheet::XNamedRange >  xRange = GetObjectByIndex_Impl((sal_uInt16)nIndex);
    uno::Any aAny;
    if ( xRange.is() )
        aAny <<= xRange;
    else
        throw lang::IndexOutOfBoundsException();
    return aAny;
}

uno::Type SAL_CALL ScNamedRangesObj::getElementType() throw(uno::RuntimeException)
{
    SolarMutexGuard aGuard;
    return ::getCppuType((const uno::Reference< sheet::XNamedRange >*)0);	// muss zu getByIndex passen
}

sal_Bool SAL_CALL ScNamedRangesObj::hasElements() throw(uno::RuntimeException)
{
    SolarMutexGuard aGuard;
    return ( getCount() != 0 );
}

uno::Any SAL_CALL ScNamedRangesObj::getByName( const ::rtl::OUString& aName )
            throw(container::NoSuchElementException,
                    lang::WrappedTargetException, uno::RuntimeException)
{
    SolarMutexGuard aGuard;
    uno::Reference< sheet::XNamedRange >  xRange = GetObjectByName_Impl(aName);
    uno::Any aAny;
    if ( xRange.is() )
        aAny <<= xRange;
    else
        throw container::NoSuchElementException();
    return aAny;
}

uno::Sequence< ::rtl::OUString> SAL_CALL ScNamedRangesObj::getElementNames()
                                                throw(uno::RuntimeException)
{
    SolarMutexGuard aGuard;
    if (pDocShell)
    {
        ScRangeName* pNames = pDocShell->GetDocument()->GetRangeName();
        if (pNames)
        {
            long nVisCount = getCount();			// Namen mit lcl_UserVisibleName
            uno::Sequence< ::rtl::OUString> aSeq(nVisCount);
            ::rtl::OUString* pAry = aSeq.getArray();

            sal_uInt16 nCount = pNames->GetCount();
            sal_uInt16 nVisPos = 0;
            for (sal_uInt16 i=0; i<nCount; i++)
            {
                ScRangeData* pData = (*pNames)[i];
                if ( lcl_UserVisibleName(pData) )
                    pAry[nVisPos++] = pData->GetName();
            }
//			DBG_ASSERT(nVisPos == nVisCount, "huch, verzaehlt?");
            return aSeq;
        }
    }
    return uno::Sequence< ::rtl::OUString>(0);
}

sal_Bool SAL_CALL ScNamedRangesObj::hasByName( const ::rtl::OUString& aName )
                                        throw(uno::RuntimeException)
{
    SolarMutexGuard aGuard;
    if (pDocShell)
    {
        ScRangeName* pNames = pDocShell->GetDocument()->GetRangeName();
        if (pNames)
        {
            String aString = aName;
            sal_uInt16 nPos = 0;
            if (pNames->SearchName( aString, nPos ))
                if ( lcl_UserVisibleName((*pNames)[nPos]) )
                    return sal_True;
        }
    }
    return sal_False;
}

//------------------------------------------------------------------------

ScLabelRangeObj::ScLabelRangeObj(ScDocShell* pDocSh, sal_Bool bCol, const ScRange& rR) :
    pDocShell( pDocSh ),
    bColumn( bCol ),
    aRange( rR )
{
    pDocShell->GetDocument()->AddUnoObject(*this);
}

ScLabelRangeObj::~ScLabelRangeObj()
{
    if (pDocShell)
        pDocShell->GetDocument()->RemoveUnoObject(*this);
}

void ScLabelRangeObj::Notify( SfxBroadcaster& rBC, const SfxHint& rHint )
{
    //!	Ref-Update !!!

    if ( rHint.ISA( SfxSimpleHint ) && ((const SfxSimpleHint&)rHint).GetId() == SFX_HINT_DYING )
        pDocShell = NULL;		// ungueltig geworden
}

// Hilfsfuntionen

ScRangePair* ScLabelRangeObj::GetData_Impl()
{
    ScRangePair* pRet = NULL;
    if (pDocShell)
    {
        ScDocument* pDoc = pDocShell->GetDocument();
        ScRangePairList* pList = bColumn ? pDoc->GetColNameRanges() : pDoc->GetRowNameRanges();
        if (pList)
            pRet = pList->Find( aRange );
    }
    return pRet;
}

void ScLabelRangeObj::Modify_Impl( const ScRange* pLabel, const ScRange* pData )
{
    if (pDocShell)
    {
        ScDocument* pDoc = pDocShell->GetDocument();
        ScRangePairList* pOldList = bColumn ? pDoc->GetColNameRanges() : pDoc->GetRowNameRanges();
        if (pOldList)
        {
            ScRangePairListRef xNewList = pOldList->Clone();
            ScRangePair* pEntry = xNewList->Find( aRange );
            if (pEntry)
            {
                xNewList->Remove( pEntry );		// nur aus der Liste entfernt, nicht geloescht

                if ( pLabel )
                    pEntry->GetRange(0) = *pLabel;
                if ( pData )
                    pEntry->GetRange(1) = *pData;

                xNewList->Join( *pEntry );
                delete pEntry;

                if (bColumn)
                    pDoc->GetColNameRangesRef() = xNewList;
                else
                    pDoc->GetRowNameRangesRef() = xNewList;

                pDoc->CompileColRowNameFormula();
                pDocShell->PostPaint( 0,0,0, MAXCOL,MAXROW,MAXTAB, PAINT_GRID );
                pDocShell->SetDocumentModified();

                //!	Undo ?!?! (hier und aus Dialog)

                if ( pLabel )
                    aRange = *pLabel;	// Objekt anpassen, um Range wiederzufinden
            }
        }
    }
}

// sheet::XLabelRange

table::CellRangeAddress SAL_CALL ScLabelRangeObj::getLabelArea()
                                                throw(uno::RuntimeException)
{
    SolarMutexGuard aGuard;
    table::CellRangeAddress aRet;
    ScRangePair* pData = GetData_Impl();
    if (pData)
        ScUnoConversion::FillApiRange( aRet, pData->GetRange(0) );
    return aRet;
}

void SAL_CALL ScLabelRangeObj::setLabelArea( const table::CellRangeAddress& aLabelArea )
                                                throw(uno::RuntimeException)
{
    SolarMutexGuard aGuard;
    ScRange aLabelRange;
    ScUnoConversion::FillScRange( aLabelRange, aLabelArea );
    Modify_Impl( &aLabelRange, NULL );
}

table::CellRangeAddress SAL_CALL ScLabelRangeObj::getDataArea()
                                                throw(uno::RuntimeException)
{
    SolarMutexGuard aGuard;
    table::CellRangeAddress aRet;
    ScRangePair* pData = GetData_Impl();
    if (pData)
        ScUnoConversion::FillApiRange( aRet, pData->GetRange(1) );
    return aRet;
}

void SAL_CALL ScLabelRangeObj::setDataArea( const table::CellRangeAddress& aDataArea )
                                                throw(uno::RuntimeException)
{
    SolarMutexGuard aGuard;
    ScRange aDataRange;
    ScUnoConversion::FillScRange( aDataRange, aDataArea );
    Modify_Impl( NULL, &aDataRange );
}

//------------------------------------------------------------------------

ScLabelRangesObj::ScLabelRangesObj(ScDocShell* pDocSh, sal_Bool bCol) :
    pDocShell( pDocSh ),
    bColumn( bCol )
{
    pDocShell->GetDocument()->AddUnoObject(*this);
}

ScLabelRangesObj::~ScLabelRangesObj()
{
    if (pDocShell)
        pDocShell->GetDocument()->RemoveUnoObject(*this);
}

void ScLabelRangesObj::Notify( SfxBroadcaster& rBC, const SfxHint& rHint )
{
    //	Referenz-Update interessiert hier nicht

    if ( rHint.ISA( SfxSimpleHint ) &&
            ((const SfxSimpleHint&)rHint).GetId() == SFX_HINT_DYING )
    {
        pDocShell = NULL;		// ungueltig geworden
    }
}

// sheet::XLabelRanges

ScLabelRangeObj* ScLabelRangesObj::GetObjectByIndex_Impl(sal_uInt16 nIndex)
{
    if (pDocShell)
    {
        ScDocument* pDoc = pDocShell->GetDocument();
        ScRangePairList* pList = bColumn ? pDoc->GetColNameRanges() : pDoc->GetRowNameRanges();
        if ( pList && nIndex < pList->Count() )
        {
            ScRangePair* pData = pList->GetObject(nIndex);
            if (pData)
                return new ScLabelRangeObj( pDocShell, bColumn, pData->GetRange(0) );
        }
    }
    return NULL;
}

void SAL_CALL ScLabelRangesObj::addNew( const table::CellRangeAddress& aLabelArea,
                                const table::CellRangeAddress& aDataArea )
                                                throw(uno::RuntimeException)
{
    SolarMutexGuard aGuard;
    if (pDocShell)
    {
        ScDocument* pDoc = pDocShell->GetDocument();
        ScRangePairList* pOldList = bColumn ? pDoc->GetColNameRanges() : pDoc->GetRowNameRanges();
        if (pOldList)
        {
            ScRangePairListRef xNewList = pOldList->Clone();

            ScRange aLabelRange;
            ScRange aDataRange;
            ScUnoConversion::FillScRange( aLabelRange, aLabelArea );
            ScUnoConversion::FillScRange( aDataRange,  aDataArea );
            xNewList->Join( ScRangePair( aLabelRange, aDataRange ) );

            if (bColumn)
                pDoc->GetColNameRangesRef() = xNewList;
            else
                pDoc->GetRowNameRangesRef() = xNewList;

            pDoc->CompileColRowNameFormula();
            pDocShell->PostPaint( 0,0,0, MAXCOL,MAXROW,MAXTAB, PAINT_GRID );
            pDocShell->SetDocumentModified();

            //!	Undo ?!?! (hier und aus Dialog)
        }
    }
}

void SAL_CALL ScLabelRangesObj::removeByIndex( sal_Int32 nIndex )
                                                throw(uno::RuntimeException)
{
    SolarMutexGuard aGuard;
    BOOL bDone = FALSE;
    if (pDocShell)
    {
        ScDocument* pDoc = pDocShell->GetDocument();
        ScRangePairList* pOldList = bColumn ? pDoc->GetColNameRanges() : pDoc->GetRowNameRanges();

        if ( pOldList && nIndex < (sal_Int32)pOldList->Count() )
        {
            ScRangePairListRef xNewList = pOldList->Clone();

            ScRangePair* pEntry = xNewList->GetObject( nIndex );
            if (pEntry)
            {
                xNewList->Remove( pEntry );
                delete pEntry;

                if (bColumn)
                    pDoc->GetColNameRangesRef() = xNewList;
                else
                    pDoc->GetRowNameRangesRef() = xNewList;

                pDoc->CompileColRowNameFormula();
                pDocShell->PostPaint( 0,0,0, MAXCOL,MAXROW,MAXTAB, PAINT_GRID );
                pDocShell->SetDocumentModified();
                bDone = TRUE;

                //!	Undo ?!?! (hier und aus Dialog)
            }
        }
    }
    if (!bDone)
        throw uno::RuntimeException();		// no other exceptions specified
}

// container::XEnumerationAccess

uno::Reference<container::XEnumeration> SAL_CALL ScLabelRangesObj::createEnumeration()
                                                    throw(uno::RuntimeException)
{
    SolarMutexGuard aGuard;
    return new ScIndexEnumeration(this, ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("com.sun.star.sheet.LabelRangesEnumeration")));
}

// container::XIndexAccess

sal_Int32 SAL_CALL ScLabelRangesObj::getCount() throw(uno::RuntimeException)
{
    SolarMutexGuard aGuard;
    if (pDocShell)
    {
        ScDocument* pDoc = pDocShell->GetDocument();
        ScRangePairList* pList = bColumn ? pDoc->GetColNameRanges() : pDoc->GetRowNameRanges();
        if (pList)
            return pList->Count();
    }
    return 0;
}

uno::Any SAL_CALL ScLabelRangesObj::getByIndex( sal_Int32 nIndex )
                            throw(lang::IndexOutOfBoundsException,
                                    lang::WrappedTargetException, uno::RuntimeException)
{
    SolarMutexGuard aGuard;
    uno::Reference< sheet::XLabelRange >  xRange = GetObjectByIndex_Impl((sal_uInt16)nIndex);
    uno::Any aAny;
    if ( xRange.is() )
        aAny <<= xRange;
    else
        throw lang::IndexOutOfBoundsException();
    return aAny;
}

uno::Type SAL_CALL ScLabelRangesObj::getElementType() throw(uno::RuntimeException)
{
    SolarMutexGuard aGuard;
    return ::getCppuType((const uno::Reference< sheet::XLabelRange >*)0);	// muss zu getByIndex passen

}

sal_Bool SAL_CALL ScLabelRangesObj::hasElements() throw(uno::RuntimeException)
{
    SolarMutexGuard aGuard;
    return ( getCount() != 0 );
}

//------------------------------------------------------------------------



}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
