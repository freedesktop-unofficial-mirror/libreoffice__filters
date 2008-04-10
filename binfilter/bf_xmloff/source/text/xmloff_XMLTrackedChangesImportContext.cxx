/*************************************************************************
 *
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER.
 * 
 * Copyright 2008 by Sun Microsystems, Inc.
 *
 * OpenOffice.org - a multi-platform office productivity suite
 *
 * $RCSfile: xmloff_XMLTrackedChangesImportContext.cxx,v $
 * $Revision: 1.5 $
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

#ifndef _XMLOFF_XMLTRACKEDCHANGESIMPORTCONTEXT_HXX
#include "XMLTrackedChangesImportContext.hxx"
#endif

#ifndef _XMLOFF_XMLCHANGEDREGIONIMPORTCONTEXT_HXX
#include "XMLChangedRegionImportContext.hxx"
#endif

#ifndef _COM_SUN_STAR_UNO_REFERENCE_H_
#include <com/sun/star/uno/Reference.h>
#endif

#ifndef _COM_SUN_STAR_UNO_SEQUENCE_H_
#include <com/sun/star/uno/Sequence.h>
#endif

#ifndef _XMLOFF_XMLIMP_HXX
#include "xmlimp.hxx"
#endif

#ifndef _XMLOFF_XMLNMSPE_HXX
#include "xmlnmspe.hxx"
#endif

#ifndef _XMLOFF_NMSPMAP_HXX
#include "nmspmap.hxx"
#endif

#ifndef _XMLOFF_XMLUCONV_HXX
#include "xmluconv.hxx"
#endif

namespace binfilter {


using ::rtl::OUString;
using ::com::sun::star::uno::Reference;
using ::com::sun::star::uno::Sequence;
using ::com::sun::star::xml::sax::XAttributeList;
using namespace ::binfilter::xmloff::token;



TYPEINIT1( XMLTrackedChangesImportContext, SvXMLImportContext );

XMLTrackedChangesImportContext::XMLTrackedChangesImportContext(
    SvXMLImport& rImport,
    sal_uInt16 nPrefix,
    const OUString& rLocalName) :
        SvXMLImportContext(rImport, nPrefix, rLocalName)
{
}

XMLTrackedChangesImportContext::~XMLTrackedChangesImportContext()
{
}

void XMLTrackedChangesImportContext::StartElement( 
    const Reference<XAttributeList> & xAttrList )
{
    sal_Bool bTrackChanges = sal_True;
    Sequence<sal_Int8> aProtectionKey;

    // scan for text:track-changes and text:protection-key attributes
    sal_Int16 nLength = xAttrList->getLength();
    for( sal_Int16 i = 0; i < nLength; i++ )
    {
        OUString sLocalName;
        sal_uInt16 nPrefix = GetImport().GetNamespaceMap().
            GetKeyByAttrName( xAttrList->getNameByIndex(i), &sLocalName );

        if ( XML_NAMESPACE_TEXT == nPrefix )
        {
            if ( IsXMLToken( sLocalName, XML_TRACK_CHANGES ) )
            {
                sal_Bool bTmp;
                if( SvXMLUnitConverter::convertBool( 
                    bTmp, xAttrList->getValueByIndex(i)) )
                {
                    bTrackChanges = bTmp;
                }
            }
            else if ( IsXMLToken( sLocalName, XML_PROTECTION_KEY ) )			{
                Sequence<sal_Int8> aSequence;
                SvXMLUnitConverter::decodeBase64( 
                    aSequence, xAttrList->getValueByIndex(i));
                if ( aSequence.getLength() > 0 )
                {
                    aProtectionKey = aSequence;
                }
            }
        }
    }

    // set tracked changes
    GetImport().GetTextImport()->SetRecordChanges( bTrackChanges );
    GetImport().GetTextImport()->SetChangesProtectionKey( aProtectionKey );
}  


SvXMLImportContext* XMLTrackedChangesImportContext::CreateChildContext(
    sal_uInt16 nPrefix,
    const OUString& rLocalName,
    const Reference<XAttributeList> & xAttrList)
{
    SvXMLImportContext* pContext = NULL;

    if ( (XML_NAMESPACE_TEXT == nPrefix) &&
         IsXMLToken( rLocalName, XML_CHANGED_REGION ) )
    {
        pContext = new XMLChangedRegionImportContext(GetImport(), 
                                                     nPrefix, rLocalName);
    }

    if (NULL == pContext)
    {
        pContext = SvXMLImportContext::CreateChildContext(nPrefix, rLocalName, 
                                                          xAttrList);
    }

    return pContext;
}
}//end of namespace binfilter
