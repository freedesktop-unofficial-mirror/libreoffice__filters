/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: XMLLineNumberingExport.hxx,v $
 *
 *  $Revision: 1.2 $
 *
 *  last change: $Author: rt $ $Date: 2005-09-09 10:08:12 $
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

#ifndef _XMLOFF_XMLLINENUMBERINGEXPORT_HXX_
#define _XMLOFF_XMLLINENUMBERINGEXPORT_HXX_


#ifndef _RTL_USTRING_HXX_
#include <rtl/ustring.hxx>
#endif
#ifndef _COM_SUN_STAR_UNO_REFERENCE_H_ 
#include <com/sun/star/uno/Reference.h>
#endif
namespace binfilter {

class SvXMLExport;

/** export <text:linenumbering-configuration> and it's child elements */
class XMLLineNumberingExport 
{
    const ::rtl::OUString sCharStyleName;
    const ::rtl::OUString sCountEmptyLines;
    const ::rtl::OUString sCountLinesInFrames;
    const ::rtl::OUString sDistance;
    const ::rtl::OUString sInterval;
    const ::rtl::OUString sSeparatorText;
    const ::rtl::OUString sNumberPosition;
    const ::rtl::OUString sNumberingType;
    const ::rtl::OUString sIsOn;
    const ::rtl::OUString sRestartAtEachPage;
    const ::rtl::OUString sSeparatorInterval;

    SvXMLExport& rExport;

public:	
    XMLLineNumberingExport(SvXMLExport& rExp);

    void Export();
};

}//end of namespace binfilter
#endif
