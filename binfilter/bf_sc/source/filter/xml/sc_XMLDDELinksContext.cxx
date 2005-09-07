/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: sc_XMLDDELinksContext.cxx,v $
 *
 *  $Revision: 1.5 $
 *
 *  last change: $Author: rt $ $Date: 2005-09-07 18:23:01 $
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
// auto strip #include "filt_pch.hxx"
#endif

#pragma hdrstop

// INCLUDE ---------------------------------------------------------------

#ifndef _SC_XMLDDELINKSCONTEXT_HXX
#include "XMLDDELinksContext.hxx"
#endif
#ifndef SC_XMLIMPRT_HXX
#include "xmlimprt.hxx"
#endif
#ifndef SC_DOCUMENT_HXX
#include "document.hxx"
#endif

// auto strip #ifndef _XMLOFF_XMLTOKEN_HXX
// auto strip #include <bf_xmloff/xmltoken.hxx>
// auto strip #endif
#ifndef _XMLOFF_XMLNMSPE_HXX
#include <bf_xmloff/xmlnmspe.hxx>
#endif
#ifndef _XMLOFF_NMSPMAP_HXX
#include <bf_xmloff/nmspmap.hxx>
#endif
#ifndef _XMLOFF_XMLUCONV_HXX
#include <bf_xmloff/xmluconv.hxx>
#endif

#ifndef _TOOLS_DEBUG_HXX
#include <tools/debug.hxx>
#endif
namespace binfilter {

using namespace ::com::sun::star;
using namespace xmloff::token;

//------------------------------------------------------------------

ScXMLDDELinksContext::ScXMLDDELinksContext( ScXMLImport& rImport,
                                      USHORT nPrfx,
                                      const ::rtl::OUString& rLName,
                                      const ::com::sun::star::uno::Reference<
                                      ::com::sun::star::xml::sax::XAttributeList>& xAttrList) :
    SvXMLImportContext( rImport, nPrfx, rLName )
{
    // here are no attributes
    rImport.LockSolarMutex();
}

ScXMLDDELinksContext::~ScXMLDDELinksContext()
{
    GetScImport().UnlockSolarMutex();
}

SvXMLImportContext *ScXMLDDELinksContext::CreateChildContext( USHORT nPrefix,
                                            const ::rtl::OUString& rLName,
                                            const ::com::sun::star::uno::Reference<
                                          ::com::sun::star::xml::sax::XAttributeList>& xAttrList )
{
    SvXMLImportContext *pContext = 0;

    if ((nPrefix == XML_NAMESPACE_TABLE) && IsXMLToken(rLName, XML_DDE_LINK))
        pContext = new ScXMLDDELinkContext(GetScImport(), nPrefix, rLName, xAttrList);

    if( !pContext )
        pContext = new SvXMLImportContext( GetImport(), nPrefix, rLName );

    return pContext;
}

void ScXMLDDELinksContext::EndElement()
{
}

ScXMLDDELinkContext::ScXMLDDELinkContext( ScXMLImport& rImport,
                                      USHORT nPrfx,
                                      const ::rtl::OUString& rLName,
                                      const ::com::sun::star::uno::Reference<
                                      ::com::sun::star::xml::sax::XAttributeList>& xAttrList) :
    SvXMLImportContext( rImport, nPrfx, rLName ),
    aDDELinkTable(),
    aDDELinkRow(),
    sApplication(),
    sTopic(),
    sItem(),
    nMode(SC_DDE_DEFAULT),
    nPosition(-1),
    nColumns(0),
    nRows(0)
{
    // here are no attributes
}

ScXMLDDELinkContext::~ScXMLDDELinkContext()
{
}

SvXMLImportContext *ScXMLDDELinkContext::CreateChildContext( USHORT nPrefix,
                                            const ::rtl::OUString& rLName,
                                            const ::com::sun::star::uno::Reference<
                                          ::com::sun::star::xml::sax::XAttributeList>& xAttrList )
{
    SvXMLImportContext *pContext = 0;

    if ((nPrefix == XML_NAMESPACE_OFFICE) && IsXMLToken(rLName, XML_DDE_SOURCE))
        pContext = new ScXMLDDESourceContext(GetScImport(), nPrefix, rLName, xAttrList, this);
    else if ((nPrefix == XML_NAMESPACE_TABLE) && IsXMLToken(rLName, XML_TABLE))
        pContext = new ScXMLDDETableContext(GetScImport(), nPrefix, rLName, xAttrList, this);

    if( !pContext )
        pContext = new SvXMLImportContext( GetImport(), nPrefix, rLName );

    return pContext;
}

void ScXMLDDELinkContext::CreateDDELink()
{
    if (GetScImport().GetDocument() &&
        sApplication.getLength() &&
        sTopic.getLength() &&
        sItem.getLength())
    {
        String sAppl(sApplication);
        String sTop(sTopic);
        String sIt(sItem);
        GetScImport().GetDocument()->CreateDdeLink(sAppl, sTop, sIt, nMode);
        sal_uInt16 nPos;
        if(GetScImport().GetDocument()->FindDdeLink(sAppl, sTop, sIt, nMode, nPos))
            nPosition = nPos;
        else
            nPosition = -1;
        DBG_ASSERT(nPosition > -1, "DDE Link not inserted");
    }
}

void ScXMLDDELinkContext::AddCellToRow(const ScDDELinkCell& aCell)
{
    aDDELinkRow.push_back(aCell);
}

void ScXMLDDELinkContext::AddRowsToTable(const sal_Int32 nRows)
{
    for (sal_Int32 i = 0; i < nRows; i++)
        aDDELinkTable.insert(aDDELinkTable.end(), aDDELinkRow.begin(), aDDELinkRow.end());
    aDDELinkRow.clear();
}

void ScXMLDDELinkContext::EndElement()
{
    if (nPosition > -1 && nColumns && nRows)
    {
        ScMatrix* pMatrix;
        if (GetScImport().GetDocument() &&
            GetScImport().GetDocument()->CreateDdeLinkResultDimension(static_cast<USHORT>(nPosition),
            static_cast<USHORT>(nColumns), static_cast<USHORT>(nRows), pMatrix))
        {
            if (pMatrix)
            {
                DBG_ASSERT(static_cast<sal_uInt32>(nColumns * nRows) == aDDELinkTable.size(), "there is a wrong cells count");
                sal_Int32 nCol(0);
                sal_Int32 nRow(-1);
                sal_Int32 nIndex(0);
                for (ScDDELinkCells::iterator aItr = aDDELinkTable.begin(); aItr != aDDELinkTable.end(); aItr++)
                {
                    if (nIndex % nColumns == 0)
                    {
                        nRow++;
                        nCol = 0;
                    }
                    else
                        nCol++;
                    String sValue(aItr->sValue);
                    GetScImport().GetDocument()->SetDdeLinkResult(pMatrix, static_cast<USHORT>(nCol), static_cast<USHORT>(nRow),
                        sValue,	aItr->fValue, aItr->bString, aItr->bEmpty);
                    nIndex++;
                }
            }
        }
    }
}

ScXMLDDESourceContext::ScXMLDDESourceContext( ScXMLImport& rImport,
                                      USHORT nPrfx,
                                      const ::rtl::OUString& rLName,
                                      const ::com::sun::star::uno::Reference<
                                      ::com::sun::star::xml::sax::XAttributeList>& xAttrList,
                                        ScXMLDDELinkContext* pTempDDELink) :
    SvXMLImportContext( rImport, nPrfx, rLName ),
    pDDELink(pTempDDELink)
{
    if( !xAttrList.is() ) return;

    sal_Int16				nAttrCount		= xAttrList->getLength();

    for( sal_Int16 nIndex = 0; nIndex < nAttrCount; nIndex++ )
    {
        OUString sAttrName	= xAttrList->getNameByIndex( nIndex );
        OUString sValue		= xAttrList->getValueByIndex( nIndex );
        OUString aLocalName;
        USHORT nPrefix		= GetScImport().GetNamespaceMap().GetKeyByAttrName( sAttrName, &aLocalName );

        if (nPrefix == XML_NAMESPACE_OFFICE)
        {
            if (IsXMLToken(aLocalName, XML_DDE_APPLICATION))
                pDDELink->SetApplication(sValue);
            else if (IsXMLToken(aLocalName, XML_DDE_TOPIC))
                pDDELink->SetTopic(sValue);
            else if (IsXMLToken(aLocalName, XML_DDE_ITEM))
                pDDELink->SetItem(sValue);
        }
        else if ((nPrefix == XML_NAMESPACE_TABLE) && IsXMLToken(aLocalName, XML_CONVERSION_MODE))
            if (IsXMLToken(sValue, XML_INTO_ENGLISH_NUMBER))
                pDDELink->SetMode(SC_DDE_ENGLISH);
            else if (IsXMLToken(sValue, XML_LET_TEXT))
                pDDELink->SetMode(SC_DDE_TEXT);
            else
                pDDELink->SetMode(SC_DDE_DEFAULT);
    }
}

ScXMLDDESourceContext::~ScXMLDDESourceContext()
{
}

SvXMLImportContext *ScXMLDDESourceContext::CreateChildContext( USHORT nPrefix,
                                            const ::rtl::OUString& rLName,
                                            const ::com::sun::star::uno::Reference<
                                          ::com::sun::star::xml::sax::XAttributeList>& xAttrList )
{
    SvXMLImportContext *pContext = new SvXMLImportContext( GetImport(), nPrefix, rLName );

    return pContext;
}

void ScXMLDDESourceContext::EndElement()
{
    pDDELink->CreateDDELink();
}

ScXMLDDETableContext::ScXMLDDETableContext( ScXMLImport& rImport,
                                      USHORT nPrfx,
                                      const ::rtl::OUString& rLName,
                                      const ::com::sun::star::uno::Reference<
                                      ::com::sun::star::xml::sax::XAttributeList>& xAttrList,
                                        ScXMLDDELinkContext* pTempDDELink) :
    SvXMLImportContext( rImport, nPrfx, rLName ),
    pDDELink(pTempDDELink)
{
    // here are no attributes
}

ScXMLDDETableContext::~ScXMLDDETableContext()
{
}

SvXMLImportContext *ScXMLDDETableContext::CreateChildContext( USHORT nPrefix,
                                            const ::rtl::OUString& rLName,
                                            const ::com::sun::star::uno::Reference<
                                          ::com::sun::star::xml::sax::XAttributeList>& xAttrList )
{
    SvXMLImportContext *pContext = NULL;

    if (nPrefix == XML_NAMESPACE_TABLE)
        if (IsXMLToken(rLName, XML_TABLE_COLUMN))
            pContext = new ScXMLDDEColumnContext(GetScImport(), nPrefix, rLName, xAttrList, pDDELink);
        else if (IsXMLToken(rLName, XML_TABLE_ROW))
            pContext = new ScXMLDDERowContext(GetScImport(), nPrefix, rLName, xAttrList, pDDELink);

    if (!pContext)
        pContext = new SvXMLImportContext( GetImport(), nPrefix, rLName );

    return pContext;
}

void ScXMLDDETableContext::EndElement()
{
}

ScXMLDDEColumnContext::ScXMLDDEColumnContext( ScXMLImport& rImport,
                                      USHORT nPrfx,
                                      const ::rtl::OUString& rLName,
                                      const ::com::sun::star::uno::Reference<
                                      ::com::sun::star::xml::sax::XAttributeList>& xAttrList,
                                        ScXMLDDELinkContext* pTempDDELink) :
    SvXMLImportContext( rImport, nPrfx, rLName ),
    pDDELink(pTempDDELink)
{
    if( !xAttrList.is() ) return;
    sal_Int32 nCols(1);

    sal_Int16				nAttrCount		= xAttrList->getLength();

    for( sal_Int16 nIndex = 0; nIndex < nAttrCount; nIndex++ )
    {
        OUString sAttrName	= xAttrList->getNameByIndex( nIndex );
        OUString sValue		= xAttrList->getValueByIndex( nIndex );
        OUString aLocalName;
        USHORT nPrefix		= GetScImport().GetNamespaceMap().GetKeyByAttrName( sAttrName, &aLocalName );

        if (nPrefix == XML_NAMESPACE_TABLE)
            if (IsXMLToken(aLocalName, XML_NUMBER_COLUMNS_REPEATED))
                GetScImport().GetMM100UnitConverter().convertNumber(nCols, sValue);
    }
    pDDELink->AddColumns(nCols);
}

ScXMLDDEColumnContext::~ScXMLDDEColumnContext()
{
}

SvXMLImportContext *ScXMLDDEColumnContext::CreateChildContext( USHORT nPrefix,
                                            const ::rtl::OUString& rLName,
                                            const ::com::sun::star::uno::Reference<
                                          ::com::sun::star::xml::sax::XAttributeList>& xAttrList )
{
    SvXMLImportContext *pContext = new SvXMLImportContext( GetImport(), nPrefix, rLName );

    return pContext;
}

void ScXMLDDEColumnContext::EndElement()
{
}

ScXMLDDERowContext::ScXMLDDERowContext( ScXMLImport& rImport,
                                      USHORT nPrfx,
                                      const ::rtl::OUString& rLName,
                                      const ::com::sun::star::uno::Reference<
                                      ::com::sun::star::xml::sax::XAttributeList>& xAttrList,
                                        ScXMLDDELinkContext* pTempDDELink) :
    SvXMLImportContext( rImport, nPrfx, rLName ),
    pDDELink(pTempDDELink),
    nRows(1)
{
    if( !xAttrList.is() ) return;

    sal_Int16				nAttrCount		= xAttrList->getLength();

    for( sal_Int16 nIndex = 0; nIndex < nAttrCount; nIndex++ )
    {
        OUString sAttrName	= xAttrList->getNameByIndex( nIndex );
        OUString sValue		= xAttrList->getValueByIndex( nIndex );
        OUString aLocalName;
        USHORT nPrefix		= GetScImport().GetNamespaceMap().GetKeyByAttrName( sAttrName, &aLocalName );

        if (nPrefix == XML_NAMESPACE_TABLE)
            if (IsXMLToken(aLocalName, XML_NUMBER_ROWS_REPEATED))
                GetScImport().GetMM100UnitConverter().convertNumber(nRows, sValue);
    }
    pDDELink->AddRows(nRows);
}

ScXMLDDERowContext::~ScXMLDDERowContext()
{
}

SvXMLImportContext *ScXMLDDERowContext::CreateChildContext( USHORT nPrefix,
                                            const ::rtl::OUString& rLName,
                                            const ::com::sun::star::uno::Reference<
                                          ::com::sun::star::xml::sax::XAttributeList>& xAttrList )
{
    SvXMLImportContext *pContext = NULL;

    if (nPrefix == XML_NAMESPACE_TABLE)
        if (IsXMLToken(rLName, XML_TABLE_CELL))
            pContext = new ScXMLDDECellContext(GetScImport(), nPrefix, rLName, xAttrList, pDDELink);

    if (!pContext)
        pContext = new SvXMLImportContext( GetImport(), nPrefix, rLName );

    return pContext;
}

void ScXMLDDERowContext::EndElement()
{
    pDDELink->AddRowsToTable(nRows);
}

ScXMLDDECellContext::ScXMLDDECellContext( ScXMLImport& rImport,
                                      USHORT nPrfx,
                                      const ::rtl::OUString& rLName,
                                      const ::com::sun::star::uno::Reference<
                                      ::com::sun::star::xml::sax::XAttributeList>& xAttrList,
                                        ScXMLDDELinkContext* pTempDDELink) :
    SvXMLImportContext( rImport, nPrfx, rLName ),
    pDDELink(pTempDDELink),
    sValue(),
    fValue(),
    nCells(1),
    bString(sal_True),
    bString2(sal_True),
    bEmpty(sal_True)
{
    if( !xAttrList.is() ) return;

    sal_Int16				nAttrCount		= xAttrList->getLength();

    for( sal_Int16 nIndex = 0; nIndex < nAttrCount; nIndex++ )
    {
        OUString sAttrName	= xAttrList->getNameByIndex( nIndex );
        OUString sTempValue		= xAttrList->getValueByIndex( nIndex );
        OUString aLocalName;
        USHORT nPrefix		= GetScImport().GetNamespaceMap().GetKeyByAttrName( sAttrName, &aLocalName );

        if (nPrefix == XML_NAMESPACE_TABLE)
            if (IsXMLToken(aLocalName, XML_VALUE_TYPE))
            {
                if (IsXMLToken(sTempValue, XML_STRING))
                    bString = sal_True;
                else
                    bString = sal_False;
            }
            else if (IsXMLToken(aLocalName, XML_STRING_VALUE))
            {
                sValue = sTempValue;
                bEmpty = sal_False;
                bString2 = sal_True;
            }
            else if (IsXMLToken(aLocalName, XML_VALUE))
            {
                GetScImport().GetMM100UnitConverter().convertDouble(fValue, sTempValue);
                bEmpty = sal_False;
                bString2 = sal_False;
            }
            else if (IsXMLToken(aLocalName, XML_NUMBER_COLUMNS_REPEATED))
                GetScImport().GetMM100UnitConverter().convertNumber(nCells, sTempValue);
    }
}

ScXMLDDECellContext::~ScXMLDDECellContext()
{
}

SvXMLImportContext *ScXMLDDECellContext::CreateChildContext( USHORT nPrefix,
                                            const ::rtl::OUString& rLName,
                                            const ::com::sun::star::uno::Reference<
                                          ::com::sun::star::xml::sax::XAttributeList>& xAttrList )
{
    SvXMLImportContext *pContext = new SvXMLImportContext( GetImport(), nPrefix, rLName );

    return pContext;
}

void ScXMLDDECellContext::EndElement()
{
    DBG_ASSERT(bString == bString2, "something wrong with this type");
    ScDDELinkCell aCell;
    aCell.sValue = sValue;
    aCell.fValue = fValue;
    aCell.bEmpty = bEmpty;
    aCell.bString = bString2;
    for(sal_Int32 i = 0; i < nCells; i++)
        pDDELink->AddCellToRow(aCell);
}
}
