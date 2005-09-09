/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: xmloff_XMLStarBasicExportHandler.cxx,v $
 *
 *  $Revision: 1.3 $
 *
 *  last change: $Author: rt $ $Date: 2005-09-09 09:20:34 $
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

#ifndef _XMLOFF_XMLSTARBASICEXPORTHANDLER_HXX
#include "XMLStarBasicExportHandler.hxx"
#endif

// auto strip #ifndef _COM_SUN_STAR_BEANS_PROPERTYVALUE_HPP
// auto strip #include <com/sun/star/beans/PropertyValue.hpp>
// auto strip #endif

// auto strip #ifndef _TOOLS_DEBUG_HXX
// auto strip #include <tools/debug.hxx>
// auto strip #endif

#ifndef _XMLOFF_XMLEXP_HXX
#include "xmlexp.hxx"
#endif

// auto strip #ifndef _XMLOFF_XMLTOKEN_HXX
// auto strip #include "xmltoken.hxx"
// auto strip #endif

#ifndef _XMLOFF_XMLNMSPE_HXX
#include "xmlnmspe.hxx"
#endif
namespace binfilter {


using namespace ::com::sun::star::uno;
using namespace ::binfilter::xmloff::token;

using ::rtl::OUString;
using ::com::sun::star::beans::PropertyValue;


XMLStarBasicExportHandler::XMLStarBasicExportHandler() :
    sStarBasic(RTL_CONSTASCII_USTRINGPARAM("StarBasic")),
    sStarOffice(RTL_CONSTASCII_USTRINGPARAM("StarOffice")),
    sApplication(RTL_CONSTASCII_USTRINGPARAM("application")),
    sLibrary(RTL_CONSTASCII_USTRINGPARAM("Library")),
    sMacroName(RTL_CONSTASCII_USTRINGPARAM("MacroName"))
{
}

XMLStarBasicExportHandler::~XMLStarBasicExportHandler()
{
}

void XMLStarBasicExportHandler::Export(
    SvXMLExport& rExport,
    const OUString& rEventName,
    Sequence<PropertyValue> & rValues,
    sal_Bool bUseWhitespace)
{
    rExport.AddAttribute(XML_NAMESPACE_SCRIPT, XML_LANGUAGE, sStarBasic);
    rExport.AddAttribute(XML_NAMESPACE_SCRIPT, XML_EVENT_NAME, rEventName);

    sal_Int32 nCount = rValues.getLength();
    for(sal_Int32 i = 0; i < nCount; i++)
    {
        if (sLibrary.equals(rValues[i].Name))
        {
            OUString sTmp;
            rValues[i].Value >>= sTmp;
            rExport.AddAttribute(
                XML_NAMESPACE_SCRIPT, XML_LOCATION,
                (sTmp.equalsIgnoreAsciiCase(sApplication) || sTmp.equalsIgnoreAsciiCase(sStarOffice) ) ? XML_APPLICATION
                                                        : XML_DOCUMENT );
        }
        else if (sMacroName.equals(rValues[i].Name))
        {
            OUString sTmp;
            rValues[i].Value >>= sTmp;
            rExport.AddAttribute(XML_NAMESPACE_SCRIPT, XML_MACRO_NAME, sTmp);
        }
        // else: disregard
    }

    SvXMLElementExport aEventElemt(rExport, XML_NAMESPACE_SCRIPT, XML_EVENT,
                                   bUseWhitespace, sal_False);
}
}//end of namespace binfilter
