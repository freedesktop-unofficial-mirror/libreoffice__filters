/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: XMLTextCharStyleNamesElementExport.hxx,v $
 *
 *  $Revision: 1.3 $
 *
 *  last change: $Author: rt $ $Date: 2005-09-09 10:10:44 $
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
#ifndef _XMLOFF_XMLTEXTCHARSTYLENAMESELEMENTEXPORT_HXX
#define _XMLOFF_XMLTEXTCHARSTYLENAMESELEMENTEXPORT_HXX

// auto strip #ifndef _RTL_USTRING_HXX_ 
// auto strip #include <rtl/ustring.hxx>
// auto strip #endif
#ifndef _COM_SUN_STAR_UNO_REFERENCE_HXX_ 
#include <com/sun/star/uno/Reference.hxx>
#endif


namespace com { namespace sun { namespace star {
    namespace beans { class XPropertySet; }
} } }
namespace binfilter {

class SvXMLExport;

class XMLTextCharStyleNamesElementExport
{
    SvXMLExport& rExport;
    ::rtl::OUString aName;
    sal_Int32 nCount;

public:

    XMLTextCharStyleNamesElementExport( 
                        SvXMLExport& rExp, sal_Bool bDoSomething,
                        const ::com::sun::star::uno::Reference < 
                            ::com::sun::star::beans::XPropertySet > & rPropSet,
                            const ::rtl::OUString& rPropName );
    ~XMLTextCharStyleNamesElementExport();
};

}//end of namespace binfilter
#endif
