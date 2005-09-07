/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: XMLConsolidationContext.hxx,v $
 *
 *  $Revision: 1.4 $
 *
 *  last change: $Author: rt $ $Date: 2005-09-07 18:14:01 $
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

#ifndef _SC_XMLCONSOLIDATIONCONTEXT_HXX
#define _SC_XMLCONSOLIDATIONCONTEXT_HXX

#ifndef SC_SCGLOB_HXX
#include "global.hxx"
#endif

#ifndef _XMLOFF_XMLIMP_HXX
#include <bf_xmloff/xmlimp.hxx>
#endif
namespace binfilter {

class ScXMLImport;


//___________________________________________________________________

class ScXMLConsolidationContext : public SvXMLImportContext
{
private:
    ::rtl::OUString				sSourceList;
    ::rtl::OUString				sUseLabel;
    ScAddress					aTargetAddr;
    ScSubTotalFunc				eFunction;
    sal_Bool					bLinkToSource : 1;
    sal_Bool					bTargetAddr : 1;

protected:
    const ScXMLImport&			GetScImport() const	{ return (const ScXMLImport&)GetImport(); }
    ScXMLImport&				GetScImport()		{ return (ScXMLImport&)GetImport(); }

public:
                                ScXMLConsolidationContext(
                                    ScXMLImport& rImport,
                                    USHORT nPrfx,
                                    const ::rtl::OUString& rLName,
                                    const ::com::sun::star::uno::Reference< ::com::sun::star::xml::sax::XAttributeList >& xAttrList
                                    );
    virtual						~ScXMLConsolidationContext();

    virtual SvXMLImportContext*	CreateChildContext(
                                    USHORT nPrefix,
                                    const ::rtl::OUString& rLocalName,
                                    const ::com::sun::star::uno::Reference< ::com::sun::star::xml::sax::XAttributeList >& xAttrList
                                    );
    virtual void				EndElement();
};


} //namespace binfilter
#endif

