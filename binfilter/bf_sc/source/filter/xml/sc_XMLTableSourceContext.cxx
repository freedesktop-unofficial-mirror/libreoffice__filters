/*************************************************************************
 *
 *  $RCSfile: sc_XMLTableSourceContext.cxx,v $
 *
 *  $Revision: 1.4 $
 *
 *  last change: $Author: hr $ $Date: 2004-08-03 11:29:44 $
 *
 *  The Contents of this file are made available subject to the terms of
 *  either of the following licenses
 *
 *         - GNU Lesser General Public License Version 2.1
 *         - Sun Industry Standards Source License Version 1.1
 *
 *  Sun Microsystems Inc., October, 2000
 *
 *  GNU Lesser General Public License Version 2.1
 *  =============================================
 *  Copyright 2000 by Sun Microsystems, Inc.
 *  901 San Antonio Road, Palo Alto, CA 94303, USA
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public
 *  License version 2.1, as published by the Free Software Foundation.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public
 *  License along with this library; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 *  MA  02111-1307  USA
 *
 *
 *  Sun Industry Standards Source License Version 1.1
 *  =================================================
 *  The contents of this file are subject to the Sun Industry Standards
 *  Source License Version 1.1 (the "License"); You may not use this file
 *  except in compliance with the License. You may obtain a copy of the
 *  License at http://www.openoffice.org/license.html.
 *
 *  Software provided under this License is provided on an "AS IS" basis,
 *  WITHOUT WARRANTY OF ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING,
 *  WITHOUT LIMITATION, WARRANTIES THAT THE SOFTWARE IS FREE OF DEFECTS,
 *  MERCHANTABLE, FIT FOR A PARTICULAR PURPOSE, OR NON-INFRINGING.
 *  See the License for the specific provisions governing your rights and
 *  obligations concerning the Software.
 *
 *  The Initial Developer of the Original Code is: Sun Microsystems, Inc.
 *
 *  Copyright: 2000 by Sun Microsystems, Inc.
 *
 *  All Rights Reserved.
 *
 *  Contributor(s): _______________________________________
 *
 *
 ************************************************************************/

#ifdef PCH
// auto strip #include "filt_pch.hxx"
#endif

#pragma hdrstop

// INCLUDE ---------------------------------------------------------------

#ifndef _SC_XMLTABLESOURCECONTEXT_HXX
#include "XMLTableSourceContext.hxx"
#endif
#ifndef SC_XMLIMPRT_HXX
#include "xmlimprt.hxx"
#endif
#ifndef SC_DOCUMENT_HXX
#include "document.hxx"
#endif
// auto strip #ifndef SC_XMLSUBTI_HXX
// auto strip #include "xmlsubti.hxx"
// auto strip #endif
#ifndef SC_TABLINK_HXX
#include "tablink.hxx"
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

#ifndef _COM_SUN_STAR_SHEET_XSHEETLINKABLE_HPP_
#include <com/sun/star/sheet/XSheetLinkable.hpp>
#endif
namespace binfilter {

using namespace ::com::sun::star;
using namespace xmloff::token;

//------------------------------------------------------------------

ScXMLTableSourceContext::ScXMLTableSourceContext( ScXMLImport& rImport,
                                      USHORT nPrfx,
                                      const ::rtl::OUString& rLName,
                                      const ::com::sun::star::uno::Reference<
                                      ::com::sun::star::xml::sax::XAttributeList>& xAttrList) :
    SvXMLImportContext( rImport, nPrfx, rLName ),
    sLink(),
    sTableName(),
    sFilterName(),
    sFilterOptions(),
    nRefresh(0),
    nMode(sheet::SheetLinkMode_NORMAL)
{
    sal_Int16 nAttrCount = xAttrList.is() ? xAttrList->getLength() : 0;
    for( sal_Int16 i=0; i < nAttrCount; i++ )
    {
        ::rtl::OUString sAttrName = xAttrList->getNameByIndex( i );
        ::rtl::OUString aLocalName;
        sal_uInt16 nPrefix = GetScImport().GetNamespaceMap().GetKeyByAttrName(
                                            sAttrName, &aLocalName );
        ::rtl::OUString sValue = xAttrList->getValueByIndex( i );
        if(nPrefix == XML_NAMESPACE_XLINK)
        {
            if (IsXMLToken(aLocalName, XML_HREF))
                sLink = GetScImport().GetAbsoluteReference(sValue);
        }
        else if (nPrefix == XML_NAMESPACE_TABLE)
        {
            if (IsXMLToken(aLocalName, XML_TABLE_NAME))
                sTableName = sValue;
            else if (IsXMLToken(aLocalName, XML_FILTER_NAME))
                sFilterName = sValue;
            else if (IsXMLToken(aLocalName, XML_FILTER_OPTIONS))
                sFilterOptions = sValue;
            else if (IsXMLToken(aLocalName, XML_MODE))
            {
                if (IsXMLToken(sValue, XML_COPY_RESULTS_ONLY))
                    nMode = sheet::SheetLinkMode_VALUE;
            }
            else if (IsXMLToken(aLocalName, XML_REFRESH_DELAY))
            {
                double fTime;
                if( SvXMLUnitConverter::convertTime( fTime, sValue ) )
                    nRefresh = Max( (sal_Int32)(fTime * 86400.0), (sal_Int32)0 );
            }
        }
    }
}

ScXMLTableSourceContext::~ScXMLTableSourceContext()
{
}

SvXMLImportContext *ScXMLTableSourceContext::CreateChildContext( USHORT nPrefix,
                                            const ::rtl::OUString& rLName,
                                            const ::com::sun::star::uno::Reference<
                                          ::com::sun::star::xml::sax::XAttributeList>& xAttrList )
{
    SvXMLImportContext *pContext = new SvXMLImportContext( GetImport(), nPrefix, rLName );
    return pContext;
}

void ScXMLTableSourceContext::EndElement()
{
    if (sLink.getLength())
    {
        uno::Reference <sheet::XSheetLinkable> xLinkable (GetScImport().GetTables().GetCurrentXSheet(), uno::UNO_QUERY);
        ScDocument* pDoc = GetScImport().GetDocument();
        if (xLinkable.is() && pDoc)
        {
            GetScImport().LockSolarMutex();
            if (pDoc->RenameTab( GetScImport().GetTables().GetCurrentSheet(),
                GetScImport().GetTables().GetCurrentSheetName(), sal_False, sal_True))
            {
                 String aFileString(sLink);
                String aFilterString(sFilterName);
                String aOptString(sFilterOptions);
                String aSheetString(sTableName);

                aFileString = ScGlobal::GetAbsDocName( aFileString, pDoc->GetDocumentShell() );
                if ( !aFilterString.Len() )
                    ScDocumentLoader::GetFilterName( aFileString, aFilterString, aOptString );

                BYTE nLinkMode = SC_LINK_NONE;
                if ( nMode == sheet::SheetLinkMode_NORMAL )
                    nLinkMode = SC_LINK_NORMAL;
                else if ( nMode == sheet::SheetLinkMode_VALUE )
                    nLinkMode = SC_LINK_VALUE;

                pDoc->SetLink( GetScImport().GetTables().GetCurrentSheet(),
                    nLinkMode, aFileString, aFilterString, aOptString,
                    aSheetString, nRefresh );
            }
            GetScImport().UnlockSolarMutex();
        }
    }
}

}
