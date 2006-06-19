/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: xmloff_XMLFootnoteSeparatorImport.cxx,v $
 *
 *  $Revision: 1.4 $
 *
 *  last change: $Author: hr $ $Date: 2006-06-19 10:12:57 $
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

#ifndef _XMLOFF_XMLFOOTNOTESEPARATORIMPORT_HXX
#include "XMLFootnoteSeparatorImport.hxx"
#endif

#include "rtl/ustring.hxx"

#ifndef _COM_SUN_STAR_UNO_REFERENCE_H_
#include <com/sun/star/uno/Reference.h>
#endif

// auto strip #ifndef _COM_SUN_STAR_XML_SAX_XATTRIBUTELIST_HPP_
// auto strip #include <com/sun/star/xml/sax/XAttributeList.hpp>
// auto strip #endif

#ifndef _COM_SUN_STAR_TEXT_HORIZONTALADJUST_HPP_
#include <com/sun/star/text/HorizontalAdjust.hpp>
#endif

#ifndef _XMLOFF_XMLIMP_HXX
#include "xmlimp.hxx"
#endif

// auto strip #ifndef _XMLOFF_XMLTOKEN_HXX
// auto strip #include "xmltoken.hxx"
// auto strip #endif

#ifndef _XMLOFF_XMLUCONV_HXX
#include "xmluconv.hxx"
#endif

#ifndef _XMLOFF_PROPERTYSETMAPPER_HXX
#include "xmlprmap.hxx"
#endif

#ifndef _XMLOFF_XMLNMSPE_HXX
#include "xmlnmspe.hxx"
#endif

#ifndef _XMLOFF_NMSPMAP_HXX
#include "nmspmap.hxx"
#endif

// auto strip #ifndef _XMLOFF_PROPMAPPINGTYPES_HXX
// auto strip #include "maptype.hxx"
// auto strip #endif

#ifndef _XMLOFF_PAGEMASTERSTYLEMAP_HXX
#include "PageMasterStyleMap.hxx"
#endif

#ifndef _TOOLS_DEBUG_HXX
#include <tools/debug.hxx>
#endif

// auto strip #ifndef _TOOLS_COLOR_HXX
// auto strip #include <tools/color.hxx>
// auto strip #endif

#include <vector>
namespace binfilter {


using namespace ::com::sun::star;
using namespace ::binfilter::xmloff::token;

using ::rtl::OUString;
using ::std::vector;
using ::com::sun::star::uno::Any;
using ::com::sun::star::uno::Reference;
using ::com::sun::star::xml::sax::XAttributeList;


TYPEINIT1(XMLFootnoteSeparatorImport, SvXMLImportContext);


XMLFootnoteSeparatorImport::XMLFootnoteSeparatorImport(
    SvXMLImport& rImport, 
    sal_uInt16 nPrefix, 
    const OUString& rLocalName, 
    vector<XMLPropertyState> & rProps,
    const UniReference<XMLPropertySetMapper> & rMapperRef,
    sal_Int32 nIndex) :
        SvXMLImportContext(rImport, nPrefix, rLocalName),
        rProperties(rProps),
        rMapper(rMapperRef),
        nPropIndex(nIndex)
{
}

XMLFootnoteSeparatorImport::~XMLFootnoteSeparatorImport()
{
}


static const SvXMLEnumMapEntry aXML_HorizontalAdjust_Enum[] =
{
    { XML_LEFT,	    text::HorizontalAdjust_LEFT },
    { XML_CENTER,	text::HorizontalAdjust_CENTER },
    { XML_RIGHT,	text::HorizontalAdjust_RIGHT },
    { XML_TOKEN_INVALID, 0 }
};

void XMLFootnoteSeparatorImport::StartElement( 
    const Reference<XAttributeList> & xAttrList)
{
    // get the values from the properties
    sal_Int16 nLineWeight = 0;
    sal_Int32 nLineColor = 0;
    sal_Int8 nLineRelWidth = 0;
    sal_Int16 eLineAdjust = text::HorizontalAdjust_LEFT; // enum text::HorizontalAdjust 
    sal_Int32 nLineTextDistance = 0;
    sal_Int32 nLineDistance = 0;

    // iterate over xattribute list and fill values
    sal_Int16 nLength = xAttrList->getLength();
    for(sal_Int16 nAttr = 0; nAttr < nLength; nAttr++)
    {
        OUString sLocalName;
        sal_uInt16 nPrefix = GetImport().GetNamespaceMap().
            GetKeyByAttrName( xAttrList->getNameByIndex(nAttr), 
                              &sLocalName );
        OUString sAttrValue = xAttrList->getValueByIndex(nAttr);

        sal_Int32 nTmp;

        if (XML_NAMESPACE_STYLE == nPrefix)
        {
            if (IsXMLToken( sLocalName, XML_WIDTH ))
            {
                if (GetImport().GetMM100UnitConverter().convertMeasure(
                    nTmp, sAttrValue))
                {
                    nLineWeight = (sal_Int16)nTmp;
                }
            }
            else if (IsXMLToken( sLocalName, XML_DISTANCE_BEFORE_SEP ))
            {
                if (GetImport().GetMM100UnitConverter().convertMeasure(
                                                        nTmp, sAttrValue))
                    nLineTextDistance = nTmp;
            }
            else if (IsXMLToken( sLocalName, XML_DISTANCE_AFTER_SEP ))
            {
                if (GetImport().GetMM100UnitConverter().convertMeasure(
                                                        nTmp, sAttrValue))
                    nLineDistance = nTmp;
            }
            else if (IsXMLToken( sLocalName, XML_ADJUSTMENT ))
            {
                sal_uInt16 nTmpU;
                if (SvXMLUnitConverter::convertEnum(
                            nTmpU, sAttrValue, aXML_HorizontalAdjust_Enum))
                    eLineAdjust = (sal_Int16)nTmpU;
            }
            else if (IsXMLToken( sLocalName, XML_REL_WIDTH ))
            {
                if (SvXMLUnitConverter::convertPercent(nTmp, sAttrValue))
                    nLineRelWidth = (sal_uInt8)nTmp;
            }
            else if (IsXMLToken( sLocalName, XML_COLOR ))
            {
                Color aColor;
                if (SvXMLUnitConverter::convertColor(aColor, sAttrValue))
                    nLineColor = (sal_Int32)aColor.GetColor();
            }
        }
    }

    // OK, now we have all values and can fill the XMLPropertyState vector
    Any aAny;
    sal_Int32 nIndex;

    aAny <<= eLineAdjust;
    nIndex = rMapper->FindEntryIndex(CTF_PM_FTN_LINE_ADJUST);
    XMLPropertyState aLineAdjust( nIndex, aAny);
    rProperties.push_back(aLineAdjust);
        
    aAny <<= nLineColor;
    nIndex = rMapper->FindEntryIndex(CTF_PM_FTN_LINE_COLOR);
    XMLPropertyState aLineColor( nIndex, aAny );
    rProperties.push_back(aLineColor);

    aAny <<= nLineDistance;
    nIndex = rMapper->FindEntryIndex(CTF_PM_FTN_DISTANCE);
    XMLPropertyState aLineDistance( nIndex, aAny );
    rProperties.push_back(aLineDistance);

    aAny <<= nLineRelWidth;
    nIndex = rMapper->FindEntryIndex(CTF_PM_FTN_LINE_WIDTH);
    XMLPropertyState aLineRelWidth( nIndex, aAny);
    rProperties.push_back(aLineRelWidth);

    aAny <<= nLineTextDistance;
    nIndex = rMapper->FindEntryIndex(CTF_PM_FTN_LINE_DISTANCE);
    XMLPropertyState aLineTextDistance( nIndex, aAny);
    rProperties.push_back(aLineTextDistance);

    DBG_ASSERT( rMapper->FindEntryIndex(CTF_PM_FTN_LINE_WEIGTH) == nPropIndex,
                "Received wrong property map index!" );
    aAny <<= nLineWeight;
    XMLPropertyState aLineWeight( nPropIndex, aAny );
    rProperties.push_back(aLineWeight);
}
}//end of namespace binfilter
