/*************************************************************************
 *
 *  $RCSfile: styleexp.hxx,v $
 *
 *  $Revision: 1.1 $
 *
 *  last change: $Author: jmeng $ $Date: 2003-12-04 01:45:42 $
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
#ifndef _XMLOFF_STYLEEXP_HXX_
#define _XMLOFF_STYLEEXP_HXX_

#ifndef _RTL_USTRING_HXX_
#include <rtl/ustring.hxx>
#endif
#ifndef _COM_SUN_STAR_UNO_REFERENCE_H_
#include <com/sun/star/uno/Reference.h>
#endif

#ifndef _VCL_MAPUNIT_HXX
//#include <vcl/mapunit.hxx>
#endif

#ifndef _UNIVERSALL_REFERENCE_HXX
#include <bf_xmloff/uniref.hxx>
#endif

namespace com { namespace sun { namespace star
{
    namespace style
    {
        class XStyle;
    }
} } }
namespace binfilter {

class XMLPropertySetMapper;
class SvXMLExportPropertyMapper;
class SvXMLAutoStylePoolP;
class SvXMLExport;

class XMLStyleExport : public UniRefBase
{
    SvXMLExport& rExport;
protected:
    const ::rtl::OUString sIsPhysical;
    const ::rtl::OUString sIsAutoUpdate;
    const ::rtl::OUString sFollowStyle;
    const ::rtl::OUString sNumberingStyleName;

    SvXMLExport& GetExport() { return rExport; }
    const SvXMLExport& GetExport() const  { return rExport; }

private:

    const ::rtl::OUString sPoolStyleName;

    SvXMLAutoStylePoolP *pAutoStylePool;

protected:

    virtual sal_Bool exportStyle(
        const ::com::sun::star::uno::Reference<
                ::com::sun::star::style::XStyle > & rStyle,
        const ::rtl::OUString& rXMLFamily,
        const UniReference < SvXMLExportPropertyMapper >& rPropMapper,
        const ::rtl::OUString* pPrefix = 0L );

    virtual void exportStyleAttributes(
        const ::com::sun::star::uno::Reference<
                ::com::sun::star::style::XStyle > & rStyle );

    virtual void exportStyleContent(
        const ::com::sun::star::uno::Reference<
                ::com::sun::star::style::XStyle > & rStyle );
public:
    XMLStyleExport(
        SvXMLExport& rExp,
        const ::rtl::OUString& rPoolStyleName,
        SvXMLAutoStylePoolP *pAutoStyleP=0 );
    virtual ~XMLStyleExport();

//	void exportStyleFamily(
//		const ::rtl::OUString& rFamily, const ::rtl::OUString& rXMLFamily,
//		const UniReference < XMLPropertySetMapper >& rPropMapper,
//		sal_Bool bUsed, sal_uInt16 nFamily = 0,
//		const ::rtl::OUString* pPrefix = 0L);

//	void exportStyleFamily(
//		const sal_Char *pFamily, const ::rtl::OUString& rXMLFamily,
//		const UniReference < XMLPropertySetMapper >& rPropMapper,
//		sal_Bool bUsed, sal_uInt16 nFamily = 0,
//		const ::rtl::OUString* pPrefix = 0L);

    virtual sal_Bool exportDefaultStyle(
        const ::com::sun::star::uno::Reference<
                ::com::sun::star::beans::XPropertySet > & xPropSet,
        const ::rtl::OUString& rXMLFamily,
        const UniReference < SvXMLExportPropertyMapper >& rPropMapper );

    void exportStyleFamily(
        const ::rtl::OUString& rFamily, const ::rtl::OUString& rXMLFamily,
        const UniReference < SvXMLExportPropertyMapper >& rPropMapper,
        sal_Bool bUsed, sal_uInt16 nFamily = 0,
        const ::rtl::OUString* pPrefix = 0L);

    void exportStyleFamily(
        const sal_Char *pFamily, const ::rtl::OUString& rXMLFamily,
        const UniReference < SvXMLExportPropertyMapper >& rPropMapper,
        sal_Bool bUsed, sal_uInt16 nFamily = 0,
        const ::rtl::OUString* pPrefix = 0L);
};

}//end of namespace binfilter
#endif
