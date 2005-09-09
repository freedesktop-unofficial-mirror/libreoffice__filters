/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: XMLFontStylesContext.hxx,v $
 *
 *  $Revision: 1.3 $
 *
 *  last change: $Author: rt $ $Date: 2005-09-09 17:21:00 $
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
#ifndef _XMLOFF_XMLFONTSTYLESCONTEXT_HXX_
#define _XMLOFF_XMLFONTSTYLESCONTEXT_HXX_

#ifndef __SGI_STL_VECTOR
#include <vector>
#endif

#ifndef _XMLOFF_XMLSTYLE_HXX_
#include <bf_xmloff/xmlstyle.hxx>
#endif
namespace binfilter {

struct XMLPropertyState;
class SvXMLTokenMap;
class XMLFontFamilyNamePropHdl;
class XMLFontFamilyPropHdl;
class XMLFontPitchPropHdl;
class XMLFontEncodingPropHdl;

class XMLFontStylesContext : public SvXMLStylesContext
{
    XMLFontFamilyNamePropHdl 	*pFamilyNameHdl;
    XMLFontFamilyPropHdl 		*pFamilyHdl;
    XMLFontPitchPropHdl 		*pPitchHdl;
    XMLFontEncodingPropHdl 		*pEncHdl;

    SvXMLTokenMap			*pFontStyleAttrTokenMap;

    rtl_TextEncoding		eDfltEncoding;

protected:

    virtual SvXMLStyleContext *CreateStyleChildContext( sal_uInt16 nPrefix,
        const ::rtl::OUString& rLocalName,
        const ::com::sun::star::uno::Reference<
            ::com::sun::star::xml::sax::XAttributeList > & xAttrList );

public:

    TYPEINFO();

    XMLFontStylesContext( SvXMLImport& rImport, sal_uInt16 nPrfx,
            const ::rtl::OUString& rLName,
            const ::com::sun::star::uno::Reference<
                ::com::sun::star::xml::sax::XAttributeList > & xAttrList,
            rtl_TextEncoding eDfltEnc );
    virtual ~XMLFontStylesContext();

    const SvXMLTokenMap& GetFontStyleAttrTokenMap() const
    {
        return *pFontStyleAttrTokenMap;
    }

    sal_Bool FillProperties( const ::rtl::OUString& rName,
                         ::std::vector< XMLPropertyState > &rProps,
                         sal_Int32 nFamilyNameIdx,
                         sal_Int32 nStyleNameIdx,
                         sal_Int32 nFamilyIdx,
                         sal_Int32 nPitchIdx,
                         sal_Int32 nCharsetIdx ) const;

    rtl_TextEncoding GetDfltCharset() const { return eDfltEncoding; }

    XMLFontFamilyNamePropHdl& GetFamilyNameHdl() const { return *pFamilyNameHdl; }
    XMLFontFamilyPropHdl& GetFamilyHdl() const { return *pFamilyHdl; }
    XMLFontPitchPropHdl& GetPitchHdl() const { return *pPitchHdl; }
    XMLFontEncodingPropHdl& GetEncodingHdl() const { return *pEncHdl; }

};

}//end of namespace binfilter
#endif
