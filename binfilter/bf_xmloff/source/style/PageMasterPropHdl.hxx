/*************************************************************************
 *
 *  $RCSfile: PageMasterPropHdl.hxx,v $
 *
 *  $Revision: 1.1 $
 *
 *  last change: $Author: aw $ $Date: 2003-12-05 09:36:10 $
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

#ifndef _XMLOFF_PAGEMASTERPROPHDL_HXX_
#define _XMLOFF_PAGEMASTERPROPHDL_HXX_

#ifndef _XMLOFF_PROPERTYHANDLERBASE_HXX
#include "xmlprhdl.hxx"
#endif

#ifndef _RTL_USTRING_
#include <rtl/ustring>
#endif

#ifndef _XMLOFF_XMLTOKEN_HXX
#include "xmltoken.hxx"
#endif
namespace binfilter {


//______________________________________________________________________________
// property handler for style:page-usage (style::PageStyleLayout)

class XMLPMPropHdl_PageStyleLayout : public XMLPropertyHandler
{
public:
    virtual					~XMLPMPropHdl_PageStyleLayout();
    virtual sal_Bool		equals(
                                const ::com::sun::star::uno::Any& rAny1,
                                const ::com::sun::star::uno::Any& rAny2
                                ) const;
    virtual sal_Bool		importXML(
                                const ::rtl::OUString& rStrImpValue,
                                ::com::sun::star::uno::Any& rValue,
                                const SvXMLUnitConverter& rUnitConverter
                                ) const;
    virtual sal_Bool		exportXML(
                                ::rtl::OUString& rStrExpValue,
                                const ::com::sun::star::uno::Any& rValue,
                                const SvXMLUnitConverter& rUnitConverter
                                ) const;
};


//______________________________________________________________________________
// property handler for style:num-format (style::NumberingType)

class XMLPMPropHdl_NumFormat : public XMLPropertyHandler
{
public:
    virtual					~XMLPMPropHdl_NumFormat();
    virtual sal_Bool		importXML(
                                const ::rtl::OUString& rStrImpValue,
                                ::com::sun::star::uno::Any& rValue,
                                const SvXMLUnitConverter& rUnitConverter
                                ) const;
    virtual sal_Bool		exportXML(
                                ::rtl::OUString& rStrExpValue,
                                const ::com::sun::star::uno::Any& rValue,
                                const SvXMLUnitConverter& rUnitConverter
                                ) const;
};


//______________________________________________________________________________
// property handler for style:num-letter-sync (style::NumberingType)

class XMLPMPropHdl_NumLetterSync : public XMLPropertyHandler
{
public:
    virtual					~XMLPMPropHdl_NumLetterSync();
    virtual sal_Bool		importXML(
                                const ::rtl::OUString& rStrImpValue,
                                ::com::sun::star::uno::Any& rValue,
                                const SvXMLUnitConverter& rUnitConverter
                                ) const;
    virtual sal_Bool		exportXML(
                                ::rtl::OUString& rStrExpValue,
                                const ::com::sun::star::uno::Any& rValue,
                                const SvXMLUnitConverter& rUnitConverter
                                ) const;
};


//______________________________________________________________________________
// property handler for style:paper-tray-number

class XMLPMPropHdl_PaperTrayNumber : public XMLPropertyHandler
{
public:
    virtual					~XMLPMPropHdl_PaperTrayNumber();
    virtual sal_Bool		importXML(
                                const ::rtl::OUString& rStrImpValue,
                                ::com::sun::star::uno::Any& rValue,
                                const SvXMLUnitConverter& rUnitConverter
                                ) const;
    virtual sal_Bool		exportXML(
                                ::rtl::OUString& rStrExpValue,
                                const ::com::sun::star::uno::Any& rValue,
                                const SvXMLUnitConverter& rUnitConverter
                                ) const;
};


//______________________________________________________________________________
// property handler for style:print

class XMLPMPropHdl_Print : public XMLPropertyHandler
{
protected:
    ::rtl::OUString			sAttrValue;

public:
                            XMLPMPropHdl_Print( enum ::binfilter::xmloff::token::XMLTokenEnum eValue );
    virtual					~XMLPMPropHdl_Print();

    virtual sal_Bool		importXML(
                                const ::rtl::OUString& rStrImpValue,
                                ::com::sun::star::uno::Any& rValue,
                                const SvXMLUnitConverter& rUnitConverter
                                ) const;
    virtual sal_Bool		exportXML(
                                ::rtl::OUString& rStrExpValue,
                                const ::com::sun::star::uno::Any& rValue,
                                const SvXMLUnitConverter& rUnitConverter
                                ) const;
};

//______________________________________________________________________________
// property handler for style:table-centering

class XMLPMPropHdl_CenterHorizontal : public XMLPropertyHandler
{
public:
    virtual					~XMLPMPropHdl_CenterHorizontal();
    virtual sal_Bool		importXML(
                                const ::rtl::OUString& rStrImpValue,
                                ::com::sun::star::uno::Any& rValue,
                                const SvXMLUnitConverter& rUnitConverter
                                ) const;
    virtual sal_Bool		exportXML(
                                ::rtl::OUString& rStrExpValue,
                                const ::com::sun::star::uno::Any& rValue,
                                const SvXMLUnitConverter& rUnitConverter
                                ) const;
};

class XMLPMPropHdl_CenterVertical : public XMLPropertyHandler
{
public:
    virtual					~XMLPMPropHdl_CenterVertical();
    virtual sal_Bool		importXML(
                                const ::rtl::OUString& rStrImpValue,
                                ::com::sun::star::uno::Any& rValue,
                                const SvXMLUnitConverter& rUnitConverter
                                ) const;
    virtual sal_Bool		exportXML(
                                ::rtl::OUString& rStrExpValue,
                                const ::com::sun::star::uno::Any& rValue,
                                const SvXMLUnitConverter& rUnitConverter
                                ) const;
};

}//end of namespace binfilter
#endif

