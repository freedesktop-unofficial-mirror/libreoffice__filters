/*************************************************************************
 *
 *  $RCSfile: PageMasterStyleMap.hxx,v $
 *
 *  $Revision: 1.2 $
 *
 *  last change: $Author: aw $ $Date: 2003-12-05 09:17:48 $
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

#ifndef _XMLOFF_PAGEMASTERSTYLEMAP_HXX_
#define _XMLOFF_PAGEMASTERSTYLEMAP_HXX_

#ifndef _XMLOFF_PROPMAPPINGTYPES_HXX
#include <bf_xmloff/maptype.hxx>
#endif
#ifndef _XMLOFF_XMLTYPES_HXX
#include <bf_xmloff/xmltypes.hxx>
#endif
#ifndef _XMLOFF_CONTEXTID_HXX_
#include <bf_xmloff/contextid.hxx>
#endif
namespace binfilter {

//______________________________________________________________________________

#define	XML_PM_TYPE_PAGESTYLELAYOUT		(XML_PM_TYPES_START +  0)
#define	XML_PM_TYPE_NUMFORMAT			(XML_PM_TYPES_START +  1)
#define	XML_PM_TYPE_NUMLETTERSYNC		(XML_PM_TYPES_START +  2)
#define XML_PM_TYPE_PAPERTRAYNUMBER		(XML_PM_TYPES_START +  3)
#define XML_PM_TYPE_PRINTORIENTATION	(XML_PM_TYPES_START +  4)
#define XML_PM_TYPE_PRINTANNOTATIONS	(XML_PM_TYPES_START +  5)
#define XML_PM_TYPE_PRINTCHARTS			(XML_PM_TYPES_START +  6)
#define XML_PM_TYPE_PRINTDRAWING		(XML_PM_TYPES_START +  7)
#define XML_PM_TYPE_PRINTFORMULAS		(XML_PM_TYPES_START +  8)
#define XML_PM_TYPE_PRINTGRID			(XML_PM_TYPES_START +  9)
#define XML_PM_TYPE_PRINTHEADERS		(XML_PM_TYPES_START + 10)
#define XML_PM_TYPE_PRINTOBJECTS		(XML_PM_TYPES_START + 11)
#define XML_PM_TYPE_PRINTZEROVALUES		(XML_PM_TYPES_START + 12)
#define XML_PM_TYPE_PRINTPAGEORDER		(XML_PM_TYPES_START + 13)
#define XML_PM_TYPE_FIRSTPAGENUMBER		(XML_PM_TYPES_START + 14)
#define XML_PM_TYPE_CENTER_HORIZONTAL	(XML_PM_TYPES_START + 15)
#define XML_PM_TYPE_CENTER_VERTICAL		(XML_PM_TYPES_START + 16)

// control flags
#define CTF_PM_FLAGMASK					(XML_PM_CTF_START + 0x0F00)
#define CTF_PM_HEADERFLAG				(XML_PM_CTF_START + 0x0100)
#define CTF_PM_FOOTERFLAG				(XML_PM_CTF_START + 0x0200)
#define CTF_PM_PRINTMASK                (XML_PM_CTF_START + 0x1000)
// page master
#define CTF_PM_BORDERALL				(XML_PM_CTF_START + 0x0001)
#define CTF_PM_BORDERTOP				(XML_PM_CTF_START + 0x0002)
#define CTF_PM_BORDERBOTTOM				(XML_PM_CTF_START + 0x0003)
#define CTF_PM_BORDERLEFT				(XML_PM_CTF_START + 0x0004)
#define CTF_PM_BORDERRIGHT				(XML_PM_CTF_START + 0x0005)
#define CTF_PM_BORDERWIDTHALL			(XML_PM_CTF_START + 0x0006)
#define CTF_PM_BORDERWIDTHTOP			(XML_PM_CTF_START + 0x0007)
#define CTF_PM_BORDERWIDTHBOTTOM		(XML_PM_CTF_START + 0x0008)
#define CTF_PM_BORDERWIDTHLEFT			(XML_PM_CTF_START + 0x0009)
#define CTF_PM_BORDERWIDTHRIGHT			(XML_PM_CTF_START + 0x000A)
#define CTF_PM_PADDINGALL				(XML_PM_CTF_START + 0x000B)
#define CTF_PM_PADDINGTOP				(XML_PM_CTF_START + 0x000C)
#define CTF_PM_PADDINGBOTTOM			(XML_PM_CTF_START + 0x000D)
#define CTF_PM_PADDINGLEFT				(XML_PM_CTF_START + 0x000E)
#define CTF_PM_PADDINGRIGHT				(XML_PM_CTF_START + 0x000F)
#define CTF_PM_TEXTCOLUMNS				(XML_PM_CTF_START + 0x0010)
#define CTF_PM_REGISTER_STYLE			(XML_PM_CTF_START + 0x0011)
#define CTF_PM_PRINT_ANNOTATIONS        (CTF_PM_PRINTMASK|XML_PM_CTF_START + 0x0012)
#define CTF_PM_PRINT_CHARTS             (CTF_PM_PRINTMASK|XML_PM_CTF_START + 0x0013)
#define CTF_PM_PRINT_DRAWING            (CTF_PM_PRINTMASK|XML_PM_CTF_START + 0x0014)
#define CTF_PM_PRINT_FORMULAS           (CTF_PM_PRINTMASK|XML_PM_CTF_START + 0x0015)
#define CTF_PM_PRINT_GRID               (CTF_PM_PRINTMASK|XML_PM_CTF_START + 0x0016)
#define CTF_PM_PRINT_HEADERS            (CTF_PM_PRINTMASK|XML_PM_CTF_START + 0x0017)
#define CTF_PM_PRINT_OBJECTS            (CTF_PM_PRINTMASK|XML_PM_CTF_START + 0x0018)
#define CTF_PM_PRINT_ZEROVALUES         (CTF_PM_PRINTMASK|XML_PM_CTF_START + 0x0019)

#define CTF_PM_PAGEUSAGE				(XML_PM_CTF_START + 0x0031)
#define CTF_PM_GRAPHICPOSITION			(XML_PM_CTF_START + 0x0032)
#define CTF_PM_GRAPHICFILTER			(XML_PM_CTF_START + 0x0033)
#define CTF_PM_GRAPHICURL				(XML_PM_CTF_START + 0x0034)

#define CTF_PM_SCALETO					(XML_PM_CTF_START + 0x0051)	// calc specific
#define CTF_PM_SCALETOPAGES				(XML_PM_CTF_START + 0x0052)
// header
#define CTF_PM_HEADERBORDERALL			(CTF_PM_HEADERFLAG|CTF_PM_BORDERALL)
#define CTF_PM_HEADERBORDERTOP			(CTF_PM_HEADERFLAG|CTF_PM_BORDERTOP)
#define CTF_PM_HEADERBORDERBOTTOM		(CTF_PM_HEADERFLAG|CTF_PM_BORDERBOTTOM)
#define CTF_PM_HEADERBORDERLEFT			(CTF_PM_HEADERFLAG|CTF_PM_BORDERLEFT)
#define CTF_PM_HEADERBORDERRIGHT		(CTF_PM_HEADERFLAG|CTF_PM_BORDERRIGHT)
#define CTF_PM_HEADERBORDERWIDTHALL		(CTF_PM_HEADERFLAG|CTF_PM_BORDERWIDTHALL)
#define CTF_PM_HEADERBORDERWIDTHTOP		(CTF_PM_HEADERFLAG|CTF_PM_BORDERWIDTHTOP)
#define CTF_PM_HEADERBORDERWIDTHBOTTOM	(CTF_PM_HEADERFLAG|CTF_PM_BORDERWIDTHBOTTOM)
#define CTF_PM_HEADERBORDERWIDTHLEFT	(CTF_PM_HEADERFLAG|CTF_PM_BORDERWIDTHLEFT)
#define CTF_PM_HEADERBORDERWIDTHRIGHT	(CTF_PM_HEADERFLAG|CTF_PM_BORDERWIDTHRIGHT)
#define CTF_PM_HEADERPADDINGALL			(CTF_PM_HEADERFLAG|CTF_PM_PADDINGALL)
#define CTF_PM_HEADERPADDINGTOP			(CTF_PM_HEADERFLAG|CTF_PM_PADDINGTOP)
#define CTF_PM_HEADERPADDINGBOTTOM		(CTF_PM_HEADERFLAG|CTF_PM_PADDINGBOTTOM)
#define CTF_PM_HEADERPADDINGLEFT		(CTF_PM_HEADERFLAG|CTF_PM_PADDINGLEFT)
#define CTF_PM_HEADERPADDINGRIGHT		(CTF_PM_HEADERFLAG|CTF_PM_PADDINGRIGHT)
#define CTF_PM_HEADERHEIGHT				(CTF_PM_HEADERFLAG|(XML_PM_CTF_START + 0x0031))
#define CTF_PM_HEADERMINHEIGHT			(CTF_PM_HEADERFLAG|(XML_PM_CTF_START + 0x0032))
#define CTF_PM_HEADERDYNAMIC			(CTF_PM_HEADERFLAG|(XML_PM_CTF_START + 0x0033))
#define CTF_PM_HEADERGRAPHICPOSITION	(CTF_PM_HEADERFLAG|(XML_PM_CTF_START + 0x0034))
#define CTF_PM_HEADERGRAPHICFILTER		(CTF_PM_HEADERFLAG|(XML_PM_CTF_START + 0x0035))
#define CTF_PM_HEADERGRAPHICURL			(CTF_PM_HEADERFLAG|(XML_PM_CTF_START + 0x0036))
// footer
#define CTF_PM_FOOTERBORDERALL			(CTF_PM_FOOTERFLAG|CTF_PM_BORDERALL)
#define CTF_PM_FOOTERBORDERTOP			(CTF_PM_FOOTERFLAG|CTF_PM_BORDERTOP)
#define CTF_PM_FOOTERBORDERBOTTOM		(CTF_PM_FOOTERFLAG|CTF_PM_BORDERBOTTOM)
#define CTF_PM_FOOTERBORDERLEFT			(CTF_PM_FOOTERFLAG|CTF_PM_BORDERLEFT)
#define CTF_PM_FOOTERBORDERRIGHT		(CTF_PM_FOOTERFLAG|CTF_PM_BORDERRIGHT)
#define CTF_PM_FOOTERBORDERWIDTHALL		(CTF_PM_FOOTERFLAG|CTF_PM_BORDERWIDTHALL)
#define CTF_PM_FOOTERBORDERWIDTHTOP		(CTF_PM_FOOTERFLAG|CTF_PM_BORDERWIDTHTOP)
#define CTF_PM_FOOTERBORDERWIDTHBOTTOM	(CTF_PM_FOOTERFLAG|CTF_PM_BORDERWIDTHBOTTOM)
#define CTF_PM_FOOTERBORDERWIDTHLEFT	(CTF_PM_FOOTERFLAG|CTF_PM_BORDERWIDTHLEFT)
#define CTF_PM_FOOTERBORDERWIDTHRIGHT	(CTF_PM_FOOTERFLAG|CTF_PM_BORDERWIDTHRIGHT)
#define CTF_PM_FOOTERPADDINGALL			(CTF_PM_FOOTERFLAG|CTF_PM_PADDINGALL)
#define CTF_PM_FOOTERPADDINGTOP			(CTF_PM_FOOTERFLAG|CTF_PM_PADDINGTOP)
#define CTF_PM_FOOTERPADDINGBOTTOM		(CTF_PM_FOOTERFLAG|CTF_PM_PADDINGBOTTOM)
#define CTF_PM_FOOTERPADDINGLEFT		(CTF_PM_FOOTERFLAG|CTF_PM_PADDINGLEFT)
#define CTF_PM_FOOTERPADDINGRIGHT		(CTF_PM_FOOTERFLAG|CTF_PM_PADDINGRIGHT)
#define CTF_PM_FOOTERHEIGHT				(CTF_PM_FOOTERFLAG|(XML_PM_CTF_START + 0x0031))
#define CTF_PM_FOOTERMINHEIGHT			(CTF_PM_FOOTERFLAG|(XML_PM_CTF_START + 0x0032))
#define CTF_PM_FOOTERDYNAMIC			(CTF_PM_FOOTERFLAG|(XML_PM_CTF_START + 0x0033))
#define CTF_PM_FOOTERGRAPHICPOSITION	(CTF_PM_FOOTERFLAG|(XML_PM_CTF_START + 0x0034))
#define CTF_PM_FOOTERGRAPHICFILTER		(CTF_PM_FOOTERFLAG|(XML_PM_CTF_START + 0x0035))
#define CTF_PM_FOOTERGRAPHICURL			(CTF_PM_FOOTERFLAG|(XML_PM_CTF_START + 0x0036))
#define CTF_PM_FTN_HEIGTH				(XML_PM_CTF_START + 0x0060)
#define CTF_PM_FTN_LINE_WEIGTH			(XML_PM_CTF_START + 0x0061)
#define CTF_PM_FTN_LINE_COLOR			(XML_PM_CTF_START + 0x0062)
#define CTF_PM_FTN_LINE_WIDTH			(XML_PM_CTF_START + 0x0063)
#define CTF_PM_FTN_LINE_ADJUST			(XML_PM_CTF_START + 0x0064)
#define CTF_PM_FTN_LINE_DISTANCE		(XML_PM_CTF_START + 0x0065)
#define CTF_PM_FTN_DISTANCE				(XML_PM_CTF_START + 0x0066)

extern const XMLPropertyMapEntry aXMLPageMasterStyleMap[];
extern const XMLPropertyMapEntry aXMLPageMasterHeaderImportStyleMap[];
extern const XMLPropertyMapEntry aXMLPageMasterFooterImportStyleMap[];

}//end of namespace binfilter
#endif
