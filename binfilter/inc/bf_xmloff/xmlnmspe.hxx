/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: xmlnmspe.hxx,v $
 *
 *  $Revision: 1.3 $
 *
 *  last change: $Author: rt $ $Date: 2005-09-09 17:41:24 $
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

#ifndef _XMLOFF_XMLNMSPE_HXX
#define _XMLOFF_XMLNMSPE_HXX

#ifndef _SAL_TYPES_H_
#include <sal/types.h>
#endif
namespace binfilter {

#define XML_NAMESPACE( prefix, key ) \
const sal_uInt16 XML_NAMESPACE_##prefix			= key; \
const sal_uInt16 XML_NAMESPACE_##prefix##_IDX	= key;

#define XML_OLD_NAMESPACE( prefix, index ) \
const sal_uInt16 XML_OLD_NAMESPACE_##prefix##_IDX = \
    (_XML_OLD_NAMESPACE_BASE+index);

// current namespaces
// These namespaces have the same index in the namespace table as prefix used.
// If a namespace is added, _XML_OLD_NAMESPACE_BASE has to be adjusted!
XML_NAMESPACE( OFFICE, 			0U )
XML_NAMESPACE( STYLE, 			1U )
XML_NAMESPACE( TEXT	, 			2U )
XML_NAMESPACE( TABLE, 			3U )
XML_NAMESPACE( DRAW	, 			4U )
XML_NAMESPACE( FO	, 			5U )
XML_NAMESPACE( XLINK, 			6U )
XML_NAMESPACE( DC	, 			7U )
XML_NAMESPACE( META	, 			8U )
XML_NAMESPACE( NUMBER, 			9U )
XML_NAMESPACE( PRESENTATION, 	10U )
XML_NAMESPACE( SVG, 			11U )
XML_NAMESPACE( CHART, 			12U )
XML_NAMESPACE( DR3D, 			13U )
XML_NAMESPACE( MATH, 			14U )
XML_NAMESPACE( FORM, 			15U )
XML_NAMESPACE( SCRIPT, 			16U )
XML_NAMESPACE( BLOCKLIST, 		17U )
XML_NAMESPACE( FRAMEWORK, 		18U )
XML_NAMESPACE( CONFIG,			19U )

#define _XML_OLD_NAMESPACE_BASE 20U

// namespaces used in the technical preview (SO 5.2)
XML_OLD_NAMESPACE( FO,		0U )
XML_OLD_NAMESPACE( XLINK,	1U )

XML_OLD_NAMESPACE( OFFICE,	2U )
XML_OLD_NAMESPACE( STYLE,	3U )
XML_OLD_NAMESPACE( TEXT,	4U )
XML_OLD_NAMESPACE( TABLE,	5U )
XML_OLD_NAMESPACE( META,	6U )

}//end of namespace binfilter
#endif	//  _XMLOFF_XMLNMSPE_HXX
