/*************************************************************************
 *
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER.
 * 
 * Copyright 2008 by Sun Microsystems, Inc.
 *
 * OpenOffice.org - a multi-platform office productivity suite
 *
 * $RCSfile: xmloff_XMLFootnoteSeparatorExport.cxx,v $
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

#ifndef _XMLOFF_XMLFOOTNOTESEPARATOREXPORT_HXX
#include "XMLFootnoteSeparatorExport.hxx"
#endif

#ifndef _TOOLS_DEBUG_HXX
#include <tools/debug.hxx>
#endif

#ifndef _XMLOFF_XMLEXP_HXX
#include "xmlexp.hxx"
#endif

#ifndef _XMLOFF_XMLNMSPE_HXX
#include "xmlnmspe.hxx"
#endif

#ifndef _XMLOFF_XMLUCONV_HXX
#include "xmluconv.hxx"
#endif



#ifndef _XMLOFF_PAGEMASTERSTYLEMAP_HXX
#include "PageMasterStyleMap.hxx"
#endif

#ifndef _COM_SUN_STAR_TEXT_HORIZONTALADJUST_HPP_
#include <com/sun/star/text/HorizontalAdjust.hpp>
#endif

namespace binfilter {


using namespace ::com::sun::star;
using namespace ::binfilter::xmloff::token;
using ::rtl::OUStringBuffer;
using ::std::vector;

XMLFootnoteSeparatorExport::XMLFootnoteSeparatorExport(SvXMLExport& rExp) :
    rExport(rExp)
{
}

XMLFootnoteSeparatorExport::~XMLFootnoteSeparatorExport()
{
}


static const SvXMLEnumMapEntry aXML_HorizontalAdjust_Enum[] =
{
    { XML_LEFT,	    text::HorizontalAdjust_LEFT },
    { XML_CENTER,	text::HorizontalAdjust_CENTER },
    { XML_RIGHT,	text::HorizontalAdjust_RIGHT },
    { XML_TOKEN_INVALID, 0 }
};

void XMLFootnoteSeparatorExport::exportXML(
    const vector<XMLPropertyState> * pProperties,
    sal_uInt32 nIdx,
    const UniReference<XMLPropertySetMapper> & rMapper)
{
    DBG_ASSERT(NULL != pProperties, "Need property states");

    // intialize values
    sal_Int16 eLineAdjust = text::HorizontalAdjust_LEFT;
    sal_Int32 nLineColor = 0;
    sal_Int32 nLineDistance = 0;
    sal_Int8 nLineRelWidth = 0;
    sal_Int32 nLineTextDistance = 0;
    sal_Int16 nLineWeight = 0;

    // find indices into property map and get values
    sal_uInt32 nCount = pProperties->size();
    for(sal_uInt32 i = 0; i < nCount; i++)
    {
        const XMLPropertyState& rState = (*pProperties)[i];

        switch (rMapper->GetEntryContextId(rState.mnIndex))
        {
        case CTF_PM_FTN_LINE_ADJUST:
            rState.maValue >>= eLineAdjust;
            break;
        case CTF_PM_FTN_LINE_COLOR:
            rState.maValue >>= nLineColor;
            break;
        case CTF_PM_FTN_DISTANCE:
            rState.maValue >>= nLineDistance;
            break;
        case CTF_PM_FTN_LINE_WIDTH:
            rState.maValue >>= nLineRelWidth;
            break;
        case CTF_PM_FTN_LINE_DISTANCE:
            rState.maValue >>= nLineTextDistance;
            break;
        case CTF_PM_FTN_LINE_WEIGTH:
            DBG_ASSERT( i == nIdx, 
                        "received wrong property state index" );
            rState.maValue >>= nLineWeight;
            break;
        }
    }

    OUStringBuffer sBuf;

    // weight/width
    if (nLineWeight > 0)
    {
        rExport.GetMM100UnitConverter().convertMeasure(sBuf, nLineWeight);
        rExport.AddAttribute(XML_NAMESPACE_STYLE, XML_WIDTH, 
                             sBuf.makeStringAndClear());
    }

    // line text distance
    if (nLineTextDistance > 0)
    {
        rExport.GetMM100UnitConverter().convertMeasure(sBuf,nLineTextDistance);
        rExport.AddAttribute(XML_NAMESPACE_STYLE, XML_DISTANCE_BEFORE_SEP,
                             sBuf.makeStringAndClear());
    }

    // line distance
    if (nLineDistance > 0)
    {
        rExport.GetMM100UnitConverter().convertMeasure(sBuf, nLineDistance);
        rExport.AddAttribute(XML_NAMESPACE_STYLE, XML_DISTANCE_AFTER_SEP, 
                             sBuf.makeStringAndClear());
    }

    // adjustment
    if (rExport.GetMM100UnitConverter().convertEnum(
        sBuf, eLineAdjust, aXML_HorizontalAdjust_Enum))
    {
        rExport.AddAttribute(XML_NAMESPACE_STYLE, XML_ADJUSTMENT, 
                             sBuf.makeStringAndClear());
    }

    // relative line width
    SvXMLUnitConverter::convertPercent(sBuf, nLineRelWidth);
    rExport.AddAttribute(XML_NAMESPACE_STYLE, XML_REL_WIDTH,
                         sBuf.makeStringAndClear());

    // color
    rExport.GetMM100UnitConverter().convertColor(sBuf, nLineColor);
    rExport.AddAttribute(XML_NAMESPACE_STYLE, XML_COLOR, 
                         sBuf.makeStringAndClear());
        
    SvXMLElementExport aElem(rExport, XML_NAMESPACE_STYLE, 
                             XML_FOOTNOTE_SEP, sal_True, sal_True);
}
}//end of namespace binfilter
