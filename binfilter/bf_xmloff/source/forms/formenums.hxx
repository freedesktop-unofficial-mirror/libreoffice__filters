/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: formenums.hxx,v $
 *
 *  $Revision: 1.2 $
 *
 *  last change: $Author: rt $ $Date: 2005-09-09 09:06:38 $
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

#ifndef _XMLOFF_FORMENUMS_HXX_
#define _XMLOFF_FORMENUMS_HXX_

#ifndef _XMLOFF_XMLEMENT_HXX
#include "xmlement.hxx"
#endif
namespace binfilter {

//.........................................................................
namespace xmloff
{
//.........................................................................

    //=====================================================================
    //= OEnumMapper
    //=====================================================================
    class OEnumMapper
    {
    public:
        enum EnumProperties
        {
            epSubmitEncoding = 0,
            epSubmitMethod,
            epCommandType,
            epNavigationType,
            epTabCyle,
            epButtonType,
            epListSourceType,
            epCheckState,
            epTextAlign,
            epBorderWidth,
            epFontEmphasis,
            epFontRelief,
            epListLinkageType,

            KNOWN_ENUM_PROPERTIES
        };

    private:
        static const SvXMLEnumMapEntry*	s_pEnumMap[KNOWN_ENUM_PROPERTIES];

    public:
        static const SvXMLEnumMapEntry*	getEnumMap(EnumProperties _eProperty);
    };

//.........................................................................
}	// namespace xmloff
//.........................................................................

}//end of namespace binfilter
#endif // _XMLOFF_FORMENUMS_HXX_

/*************************************************************************
 * history:
 *	$Log: not supported by cvs2svn $
 *	Revision 1.1.158.1  2005/09/05 11:30:11  rt
 *	#i54170# Change license header: remove SISSL
 *	
 *	Revision 1.1  2003/12/05 09:34:05  aw
 *	Added bf_xmloff files
 *	
 *	Revision 1.7  2003/10/21 08:39:48  obo
 *	INTEGRATION: CWS formcelllinkage (1.6.190); FILE MERGED
 *	2003/10/01 09:55:22 fs 1.6.190.1: #i18994# merging the changes from the CWS fs002
 *	
 *	Revision 1.6.190.1  2003/10/01 09:55:22  fs
 *	#i18994# merging the changes from the CWS fs002
 *	
 *	Revision 1.6.186.1  2003/09/25 14:28:40  fs
 *	#18994# merging the changes from cws_srx645_fs002 branch
 *	
 *	Revision 1.6.182.1  2003/09/18 14:00:38  fs
 *	#18995# changes for binding list boxes to cells, while exchanging selection indexes instead of strings
 *	
 *	Revision 1.6  2001/06/07 12:25:52  fs
 *	#86096# enums for FontEmphasis and FontRelief
 *	
 *	Revision 1.5  2000/12/19 12:13:57  fs
 *	some changes ... now the exported styles are XSL conform
 *	
 *	Revision 1.4  2000/12/19 08:42:19  fs
 *	removed the epFontWidth
 *	
 *	Revision 1.3  2000/12/18 15:14:35  fs
 *	some changes ... now exporting/importing styles
 *	
 *	Revision 1.2  2000/12/06 17:28:05  fs
 *	changes for the formlayer import - still under construction
 *	
 *	Revision 1.1  2000/11/17 19:02:06  fs
 *	initial checkin - export and/or import the applications form layer
 *	
 *
 *	Revision 1.0 15.11.00 11:49:51  fs
 ************************************************************************/

