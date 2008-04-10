/*************************************************************************
 *
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER.
 * 
 * Copyright 2008 by Sun Microsystems, Inc.
 *
 * OpenOffice.org - a multi-platform office productivity suite
 *
 * $RCSfile: xmllabri.hxx,v $
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
#ifndef SC_XMLLABRI_HXX
#define SC_XMLLABRI_HXX

#ifndef _XMLOFF_XMLICTXT_HXX
#include <bf_xmloff/xmlictxt.hxx>
#endif
namespace binfilter {

class ScXMLImport;


//___________________________________________________________________

class ScXMLLabelRangesContext : public SvXMLImportContext
{
private:
    const ScXMLImport&			GetScImport() const		{ return (const ScXMLImport&)GetImport(); }
    ScXMLImport&				GetScImport()			{ return (ScXMLImport&)GetImport(); }

public:
                                ScXMLLabelRangesContext(
                                    ScXMLImport& rImport,
                                    USHORT nPrefix,
                                    const ::rtl::OUString& rLName,
                                    const ::com::sun::star::uno::Reference< ::com::sun::star::xml::sax::XAttributeList>& xAttrList
                                    );
    virtual						~ScXMLLabelRangesContext();

    virtual SvXMLImportContext*	CreateChildContext(
                                    USHORT nPrefix,
                                    const ::rtl::OUString& rLocalName,
                                    const ::com::sun::star::uno::Reference< ::com::sun::star::xml::sax::XAttributeList>& xAttrList
                                    );
    virtual void				EndElement();
};


//___________________________________________________________________

class ScXMLLabelRangeContext : public SvXMLImportContext
{
private:
    ::rtl::OUString				sLabelRangeStr;
    ::rtl::OUString				sDataRangeStr;
    sal_Bool					bColumnOrientation : 1;

    const ScXMLImport&			GetScImport() const		{ return (const ScXMLImport&)GetImport(); }
    ScXMLImport&				GetScImport()			{ return (ScXMLImport&)GetImport(); }

public:
                                ScXMLLabelRangeContext(
                                    ScXMLImport& rImport,
                                    USHORT nPrefix,
                                    const ::rtl::OUString& rLName,
                                    const ::com::sun::star::uno::Reference< ::com::sun::star::xml::sax::XAttributeList>& xAttrList
                                    );
    virtual						~ScXMLLabelRangeContext();

    virtual SvXMLImportContext*	CreateChildContext(
                                    USHORT nPrefix,
                                    const ::rtl::OUString& rLocalName,
                                    const ::com::sun::star::uno::Reference< ::com::sun::star::xml::sax::XAttributeList>& xAttrList
                                    );
    virtual void				EndElement();
};

} //namespace binfilter
#endif
