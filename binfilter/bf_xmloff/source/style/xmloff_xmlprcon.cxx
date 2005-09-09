/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: xmloff_xmlprcon.cxx,v $
 *
 *  $Revision: 1.2 $
 *
 *  last change: $Author: rt $ $Date: 2005-09-09 09:58:24 $
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

#ifndef _XMLOFF_XMLIMP_HXX
#include "xmlimp.hxx"
#endif


#ifndef _XMLOFF_XMLPROPERTYSETCONTEXT_HXX
#include "xmlprcon.hxx"
#endif
namespace binfilter {

using namespace ::rtl;
using namespace ::com::sun::star;
using namespace ::std;

SvXMLPropertySetContext::SvXMLPropertySetContext(
    SvXMLImport& rImp, USHORT nPrfx,
    const OUString& rLName,
    const uno::Reference< xml::sax::XAttributeList >& xAttrList,
    vector< XMLPropertyState > &rProps,
    const UniReference < SvXMLImportPropertyMapper >  &rMap,
    sal_Int32 nSIdx, sal_Int32 nEIdx ):
    SvXMLImportContext( rImp, nPrfx, rLName ),
    rProperties( rProps ),
    xMapper    ( rMap ),
    nStartIdx( nSIdx ),
    nEndIdx( nEIdx )
{
    xMapper->importXML( rProperties, xAttrList,
                        GetImport().GetMM100UnitConverter(),
                        GetImport().GetNamespaceMap(), nStartIdx, nEndIdx );
}

SvXMLPropertySetContext::~SvXMLPropertySetContext()
{
}

SvXMLImportContext *SvXMLPropertySetContext::CreateChildContext(
    USHORT nPrefix,
    const OUString& rLocalName,
    const uno::Reference< xml::sax::XAttributeList >& xAttrList )
{
    UniReference< XMLPropertySetMapper > aSetMapper(
            xMapper->getPropertySetMapper() );
    sal_Int32 nEntryIndex = aSetMapper->GetEntryIndex( nPrefix, rLocalName,
                                                       nStartIdx );

    if( ( nEntryIndex != -1 ) && (-1 == nEndIdx || nEntryIndex < nEndIdx ) &&
        ( 0 != ( aSetMapper->GetEntryFlags( nEntryIndex )
                         & MID_FLAG_ELEMENT_ITEM_IMPORT ) ) )
    {
        XMLPropertyState aProp( nEntryIndex );
        return CreateChildContext( nPrefix, rLocalName, xAttrList,
                                   rProperties, aProp );
    }
    else
    {
        return new SvXMLImportContext( GetImport(), nPrefix, rLocalName );
    }
}

/** This method is called from this instance implementation of
    CreateChildContext if the element matches an entry in the
    SvXMLImportItemMapper with the mid flag MID_FLAG_ELEMENT
*/
SvXMLImportContext *SvXMLPropertySetContext::CreateChildContext(
    USHORT nPrefix,
    const ::rtl::OUString& rLocalName,
    const uno::Reference< xml::sax::XAttributeList >& xAttrList,
    ::std::vector< XMLPropertyState > &rProperties,
    const XMLPropertyState& rProp )
{
    return new SvXMLImportContext( GetImport(), nPrefix, rLocalName );
}


}//end of namespace binfilter
