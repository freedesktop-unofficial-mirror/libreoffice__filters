/*************************************************************************
 *
 *  $RCSfile: txtstyli.hxx,v $
 *
 *  $Revision: 1.2 $
 *
 *  last change: $Author: aw $ $Date: 2003-12-05 09:18:03 $
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
#ifndef _XMLOFF_TXTSTYLI_HXX_
#define _XMLOFF_TXTSTYLI_HXX_

#ifndef _XMLOFF_PRSTYLEI_HXX_
#include <bf_xmloff/prstylei.hxx>
#endif
namespace binfilter {

class SvXMLTokenMap;
class XMLEventsImportContext;

class XMLTextStyleContext : public XMLPropStyleContext
{
    ::rtl::OUString				sListStyleName;
    ::rtl::OUString				sCategoryVal;
    ::rtl::OUString				sDropCapTextStyleName;
    ::rtl::OUString				sMasterPageName;
    const ::rtl::OUString		sIsAutoUpdate;
    const ::rtl::OUString		sCategory;
    const ::rtl::OUString		sNumberingStyleName;
public:
    const ::rtl::OUString		sDropCapCharStyleName;
private:
    const ::rtl::OUString		sPageDescName;

    sal_Bool	bAutoUpdate : 1;
    sal_Bool	bHasMasterPageName : 1;

    sal_Bool bHasCombinedCharactersLetter : 1;

    XMLEventsImportContext* pEventContext;

protected:

    virtual void SetAttribute( sal_uInt16 nPrefixKey,
                               const ::rtl::OUString& rLocalName,
                               const ::rtl::OUString& rValue );

public:

    TYPEINFO();

    XMLTextStyleContext( SvXMLImport& rImport, sal_uInt16 nPrfx,
            const ::rtl::OUString& rLName,
            const ::com::sun::star::uno::Reference<
                ::com::sun::star::xml::sax::XAttributeList > & xAttrList,
            SvXMLStylesContext& rStyles, sal_uInt16 nFamily,
            sal_Bool bDefaultStyle = sal_False );
    virtual ~XMLTextStyleContext();

    virtual SvXMLImportContext *CreateChildContext(
            sal_uInt16 nPrefix,
            const ::rtl::OUString& rLocalName,
            const ::com::sun::star::uno::Reference< ::com::sun::star::xml::sax::XAttributeList > & xAttrList );

    sal_Bool IsAutoUpdate() const { return bAutoUpdate; }

    const ::rtl::OUString& GetListStyle() const { return sListStyleName; }
    const ::rtl::OUString& GetMasterPageName() const { return sMasterPageName; }
    sal_Bool HasMasterPageName() const { return bHasMasterPageName; }
    const ::rtl::OUString& GetDropCapStyleName() const { return sDropCapTextStyleName; }

    virtual void CreateAndInsert( sal_Bool bOverwrite );
    virtual void Finish( sal_Bool bOverwrite );
    virtual void SetDefaults();

    // overload FillPropertySet, so we can get at the combined characters
    virtual void FillPropertySet(
            const ::com::sun::star::uno::Reference<
                ::com::sun::star::beans::XPropertySet > & rPropSet );

    inline sal_Bool HasCombinedCharactersLetter() 
        { return bHasCombinedCharactersLetter; }

#ifdef CONV_STAR_FONTS
    const ::std::vector< XMLPropertyState > & _GetProperties() { return GetProperties(); }
#endif
};

}//end of namespace binfilter
#endif
