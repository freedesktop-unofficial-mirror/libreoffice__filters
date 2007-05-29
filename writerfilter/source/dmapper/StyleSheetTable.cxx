/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: StyleSheetTable.cxx,v $
 *
 *  $Revision: 1.17 $
 *
 *  last change: $Author: fridrich_strba $ $Date: 2007-05-29 10:07:58 $
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
#ifndef INCLUDED_STYLESHEETTABLE_HXX
#include <StyleSheetTable.hxx>
#endif
#ifndef INCLUDED_DOMAINMAPPER_HXX
#include <dmapper/DomainMapper.hxx>
#endif
#ifndef INCLUDED_RESOURCESIDS
#include <doctok/resourceids.hxx>
#include <ooxml/resourceids.hxx>
#endif
#include <vector>
#ifndef _COM_SUN_STAR_BEANS_XMULTIPROPERTYSET_HPP_
#include <com/sun/star/beans/XMultiPropertySet.hpp>
#endif
#ifndef _COM_SUN_STAR_BEANS_XPROPERTYVALUE_HPP_
#include <com/sun/star/beans/PropertyValue.hpp>
#endif
#ifndef _COM_SUN_STAR_CONTAINER_XNAMECONTAINER_HPP_
#include <com/sun/star/container/XNameContainer.hpp>
#endif
#ifndef _COM_SUN_STAR_TEXT_XTEXTDOCUMENT_HPP_
#include <com/sun/star/text/XTextDocument.hpp>
#endif
#ifndef _COM_SUN_STAR_STYLE_XSTYLEFAMILIESSUPPLIER_HPP_
#include <com/sun/star/style/XStyleFamiliesSupplier.hpp>
#endif
#ifndef _COM_SUN_STAR_STYLE_XSTYLE_HPP_
#include <com/sun/star/style/XStyle.hpp>
#endif
#ifndef _COM_SUN_STAR_TEXT_WRITINGMODE_HPP_
#include <com/sun/star/text/WritingMode.hpp>
#endif
#ifndef _COM_SUN_STAR_LANG_XMULTISERVICEFACTORY_HPP_
#include <com/sun/star/lang/XMultiServiceFactory.hpp>
#endif
#include <map>
#include <stdio.h>
#include <rtl/ustrbuf.hxx>

using namespace ::com::sun::star;
namespace dmapper
{
using namespace writerfilter;

typedef ::std::map< ::rtl::OUString, ::rtl::OUString> StringPairMap_t;

/*-- 21.06.2006 07:34:44---------------------------------------------------

  -----------------------------------------------------------------------*/
StyleSheetEntry::StyleSheetEntry() :
        nStyleIdentifierI(0)
        ,nStyleIdentifierD(0)
        ,bInvalidHeight(false)
        ,bHasUPE(false)
        ,nStyleTypeCode(STYLE_TYPE_UNKNOWN)
        ,nBaseStyleIdentifier(0xfff)
        ,nNextStyleIdentifier(-1)
        ,pProperties(new PropertyMap)
        {
        }

/*-- 19.06.2006 12:04:32---------------------------------------------------

  -----------------------------------------------------------------------*/
struct StyleSheetTable_Impl
{
    DomainMapper&                           m_rDMapper;
    std::vector< StyleSheetEntry >          m_aStyleSheetEntries;
    StyleSheetEntry                         *m_pCurrentEntry;
    PropertyMapPtr                          m_pDefaultParaProps, m_pDefaultCharProps;
    PropertyMapPtr                          m_pCurrentProps;
    StringPairMap_t                         m_aStyleNameMap;
    StyleSheetTable_Impl(DomainMapper& rDMapper) :
            m_rDMapper( rDMapper ),
            m_pCurrentEntry(0),
            m_pDefaultParaProps(new PropertyMap),
            m_pDefaultCharProps(new PropertyMap) {};
};
/*-- 19.06.2006 12:04:32---------------------------------------------------

  -----------------------------------------------------------------------*/
StyleSheetTable::StyleSheetTable(DomainMapper& rDMapper) :
    m_pImpl( new StyleSheetTable_Impl(rDMapper) )
{
}
/*-- 19.06.2006 12:04:33---------------------------------------------------

  -----------------------------------------------------------------------*/
StyleSheetTable::~StyleSheetTable()
{
    delete m_pImpl;
}
/*-- 19.06.2006 12:04:33---------------------------------------------------

  -----------------------------------------------------------------------*/
void StyleSheetTable::attribute(doctok::Id Name, doctok::Value & val)
{
    OSL_ENSURE( m_pImpl->m_pCurrentEntry, "current entry has to be set here");
    if(!m_pImpl->m_pCurrentEntry)
        return ;
    int nIntValue = val.getInt();
    (void)nIntValue;
    ::rtl::OUString sValue = val.getString();
//    printf ( "StyleSheetTable::attribute(0x%.4x, 0x%.4x) [%s]\n", (unsigned int)Name, (unsigned int)nIntValue, ::rtl::OUStringToOString(sValue, RTL_TEXTENCODING_DONTKNOW).getStr());
    switch(Name)
    {
        case NS_rtf::LN_ISTD:
            m_pImpl->m_pCurrentEntry->nStyleIdentifierD = nIntValue;
        break;
//        case NS_rtf::LN_ISTARTAT: break;
//        case NS_rtf::LN_NFC: break;
//        case NS_rtf::LN_JC: break;
//        case NS_rtf::LN_FLEGAL: break;
//        case NS_rtf::LN_FNORESTART: break;
//        case NS_rtf::LN_FPREV: break;
//        case NS_rtf::LN_FPREVSPACE: break;
//        case NS_rtf::LN_FWORD6: break;
//        case NS_rtf::LN_UNUSED5_7: break;
//        case NS_rtf::LN_RGBXCHNUMS: break;
//        case NS_rtf::LN_IXCHFOLLOW: break;
//        case NS_rtf::LN_DXASPACE: break;
//        case NS_rtf::LN_DXAINDENT: break;
//        case NS_rtf::LN_CBGRPPRLCHPX: break;
//        case NS_rtf::LN_CBGRPPRLPAPX: break;
//        case NS_rtf::LN_LSID: break;
//        case NS_rtf::LN_TPLC: break;
//        case NS_rtf::LN_RGISTD: break;
//        case NS_rtf::LN_FSIMPLELIST: break;
//        case NS_rtf::LN_FRESTARTHDN: break;
//        case NS_rtf::LN_UNSIGNED26_2: break;
//        case NS_rtf::LN_ILVL: break;
//        case NS_rtf::LN_FSTARTAT: break;
//        case NS_rtf::LN_FFORMATTING: break;
//        case NS_rtf::LN_UNSIGNED4_6: break;
//        case NS_rtf::LN_UNUSED4: break;
//        case NS_rtf::LN_UNUSED8: break;
//        case NS_rtf::LN_CLFOLVL: break;
//        case NS_rtf::LN_CBFFNM1: break;
//        case NS_rtf::LN_PRQ: break;
//        case NS_rtf::LN_FTRUETYPE: break;
//        case NS_rtf::LN_UNUSED1_3: break;
//        case NS_rtf::LN_FF: break;
//        case NS_rtf::LN_UNUSED1_7: break;
//        case NS_rtf::LN_WWEIGHT: break;
//        case NS_rtf::LN_CHS: break;
//        case NS_rtf::LN_IXCHSZALT: break;
//        case NS_rtf::LN_PANOSE: break;
//        case NS_rtf::LN_FS: break;
        case NS_rtf::LN_STI:
            m_pImpl->m_pCurrentEntry->nStyleIdentifierI = nIntValue;
        break;
        case NS_rtf::LN_SGC:
            m_pImpl->m_pCurrentEntry->nStyleTypeCode = (StyleType)nIntValue;
        break;
        case NS_rtf::LN_ISTDBASE:
            m_pImpl->m_pCurrentEntry->nBaseStyleIdentifier = nIntValue;
        break;
        case NS_rtf::LN_ISTDNEXT:
            m_pImpl->m_pCurrentEntry->nNextStyleIdentifier = nIntValue;
        break;
        case NS_rtf::LN_FSCRATCH:
        case NS_rtf::LN_FINVALHEIGHT:
        case NS_rtf::LN_FHASUPE:
        case NS_rtf::LN_FMASSCOPY:
        case NS_rtf::LN_CUPX:
        case NS_rtf::LN_BCHUPE:
        case NS_rtf::LN_FAUTOREDEF:
        case NS_rtf::LN_FHIDDEN:
        case NS_rtf::LN_UNUSED8_3:
            //noone seems to care about it
        break;
//        case NS_rtf::LN_CSTD: break;
//        case NS_rtf::LN_CBSTDBASEINFILE: break;
//        case NS_rtf::LN_FSTDSTYLENAMESWRITTEN: break;
//        case NS_rtf::LN_UNUSED4_2: break;
//        case NS_rtf::LN_STIMAXWHENSAVED: break;
//        case NS_rtf::LN_ISTDMAXFIXEDWHENSAVED: break;
//        case NS_rtf::LN_NVERBUILTINNAMESWHENSAVED: break;
//        case NS_rtf::LN_RGFTCSTANDARDCHPSTSH: break;
//        case NS_rtf::LN_WIDENT: break;
//        case NS_rtf::LN_NFIB: break;
//        case NS_rtf::LN_NPRODUCT: break;
//        case NS_rtf::LN_LID: break;
//        case NS_rtf::LN_PNNEXT: break;
//        case NS_rtf::LN_FDOT: break;
//        case NS_rtf::LN_FGLSY: break;
//        case NS_rtf::LN_FCOMPLEX: break;
//        case NS_rtf::LN_FHASPIC: break;
//        case NS_rtf::LN_CQUICKSAVES: break;
//        case NS_rtf::LN_FENCRYPTED: break;
//        case NS_rtf::LN_FWHICHTBLSTM: break;
//        case NS_rtf::LN_FREADONLYRECOMMENDED: break;
//        case NS_rtf::LN_FWRITERESERVATION: break;
//        case NS_rtf::LN_FEXTCHAR: break;
//        case NS_rtf::LN_FLOADOVERRIDE: break;
//        case NS_rtf::LN_FFAREAST: break;
//        case NS_rtf::LN_FCRYPTO: break;
//        case NS_rtf::LN_NFIBBACK: break;
//        case NS_rtf::LN_LKEY: break;
//        case NS_rtf::LN_ENVR: break;
//        case NS_rtf::LN_FMAC: break;
//        case NS_rtf::LN_FEMPTYSPECIAL: break;
//        case NS_rtf::LN_FLOADOVERRIDEPAGE: break;
//        case NS_rtf::LN_FFUTURESAVEDUNDO: break;
//        case NS_rtf::LN_FWORD97SAVED: break;
//        case NS_rtf::LN_FSPARE0: break;
//        case NS_rtf::LN_CHSTABLES: break;
//        case NS_rtf::LN_FCMIN: break;
//        case NS_rtf::LN_FCMAC: break;
//        case NS_rtf::LN_CSW: break;
//        case NS_rtf::LN_WMAGICCREATED: break;
//        case NS_rtf::LN_WMAGICREVISED: break;
//        case NS_rtf::LN_WMAGICCREATEDPRIVATE: break;
//        case NS_rtf::LN_WMAGICREVISEDPRIVATE: break;
//        case NS_rtf::LN_PNFBPCHPFIRST_W6: break;
//        case NS_rtf::LN_PNCHPFIRST_W6: break;
//        case NS_rtf::LN_CPNBTECHP_W6: break;
//        case NS_rtf::LN_PNFBPPAPFIRST_W6: break;
//        case NS_rtf::LN_PNPAPFIRST_W6: break;
//        case NS_rtf::LN_CPNBTEPAP_W6: break;
//        case NS_rtf::LN_PNFBPLVCFIRST_W6: break;
//        case NS_rtf::LN_PNLVCFIRST_W6: break;
//        case NS_rtf::LN_CPNBTELVC_W6: break;
//        case NS_rtf::LN_LIDFE: break;
//        case NS_rtf::LN_CLW: break;
//        case NS_rtf::LN_CBMAC: break;
//        case NS_rtf::LN_LPRODUCTCREATED: break;
//        case NS_rtf::LN_LPRODUCTREVISED: break;
//        case NS_rtf::LN_CCPTEXT: break;
//        case NS_rtf::LN_CCPFTN: break;
//        case NS_rtf::LN_CCPHDD: break;
//        case NS_rtf::LN_CCPMCR: break;
//        case NS_rtf::LN_CCPATN: break;
//        case NS_rtf::LN_CCPEDN: break;
//        case NS_rtf::LN_CCPTXBX: break;
//        case NS_rtf::LN_CCPHDRTXBX: break;
//        case NS_rtf::LN_PNFBPCHPFIRST: break;
//        case NS_rtf::LN_PNCHPFIRST: break;
//        case NS_rtf::LN_CPNBTECHP: break;
//        case NS_rtf::LN_PNFBPPAPFIRST: break;
//        case NS_rtf::LN_PNPAPFIRST: break;
//        case NS_rtf::LN_CPNBTEPAP: break;
//        case NS_rtf::LN_PNFBPLVCFIRST: break;
//        case NS_rtf::LN_PNLVCFIRST: break;
//        case NS_rtf::LN_CPNBTELVC: break;
//        case NS_rtf::LN_FCISLANDFIRST: break;
//        case NS_rtf::LN_FCISLANDLIM: break;
//        case NS_rtf::LN_CFCLCB: break;
//        case NS_rtf::LN_FCSTSHFORIG: break;
//        case NS_rtf::LN_LCBSTSHFORIG: break;
//        case NS_rtf::LN_FCSTSHF: break;
//        case NS_rtf::LN_LCBSTSHF: break;
//        case NS_rtf::LN_FCPLCFFNDREF: break;
//        case NS_rtf::LN_LCBPLCFFNDREF: break;
//        case NS_rtf::LN_FCPLCFFNDTXT: break;
//        case NS_rtf::LN_LCBPLCFFNDTXT: break;
//        case NS_rtf::LN_FCPLCFANDREF: break;
//        case NS_rtf::LN_LCBPLCFANDREF: break;
//        case NS_rtf::LN_FCPLCFANDTXT: break;
//        case NS_rtf::LN_LCBPLCFANDTXT: break;
//        case NS_rtf::LN_FCPLCFSED: break;
//        case NS_rtf::LN_LCBPLCFSED: break;
//        case NS_rtf::LN_FCPLCFPAD: break;
//        case NS_rtf::LN_LCBPLCFPAD: break;
//        case NS_rtf::LN_FCPLCFPHE: break;
//        case NS_rtf::LN_LCBPLCFPHE: break;
//        case NS_rtf::LN_FCSTTBFGLSY: break;
//        case NS_rtf::LN_LCBSTTBFGLSY: break;
//        case NS_rtf::LN_FCPLCFGLSY: break;
//        case NS_rtf::LN_LCBPLCFGLSY: break;
//        case NS_rtf::LN_FCPLCFHDD: break;
//        case NS_rtf::LN_LCBPLCFHDD: break;
//        case NS_rtf::LN_FCPLCFBTECHPX: break;
//        case NS_rtf::LN_LCBPLCFBTECHPX: break;
//        case NS_rtf::LN_FCPLCFBTEPAPX: break;
//        case NS_rtf::LN_LCBPLCFBTEPAPX: break;
//        case NS_rtf::LN_FCPLCFSEA: break;
//        case NS_rtf::LN_LCBPLCFSEA: break;
//        case NS_rtf::LN_FCSTTBFFFN: break;
//        case NS_rtf::LN_LCBSTTBFFFN: break;
//        case NS_rtf::LN_FCPLCFFLDMOM: break;
//        case NS_rtf::LN_LCBPLCFFLDMOM: break;
//        case NS_rtf::LN_FCPLCFFLDHDR: break;
//        case NS_rtf::LN_LCBPLCFFLDHDR: break;
//        case NS_rtf::LN_FCPLCFFLDFTN: break;
//        case NS_rtf::LN_LCBPLCFFLDFTN: break;
//        case NS_rtf::LN_FCPLCFFLDATN: break;
//        case NS_rtf::LN_LCBPLCFFLDATN: break;
//        case NS_rtf::LN_FCPLCFFLDMCR: break;
//        case NS_rtf::LN_LCBPLCFFLDMCR: break;
//        case NS_rtf::LN_FCSTTBFBKMK: break;
//        case NS_rtf::LN_LCBSTTBFBKMK: break;
//        case NS_rtf::LN_FCPLCFBKF: break;
//        case NS_rtf::LN_LCBPLCFBKF: break;
//        case NS_rtf::LN_FCPLCFBKL: break;
//        case NS_rtf::LN_LCBPLCFBKL: break;
//        case NS_rtf::LN_FCCMDS: break;
//        case NS_rtf::LN_LCBCMDS: break;
//        case NS_rtf::LN_FCPLCMCR: break;
//        case NS_rtf::LN_LCBPLCMCR: break;
//        case NS_rtf::LN_FCSTTBFMCR: break;
//        case NS_rtf::LN_LCBSTTBFMCR: break;
//        case NS_rtf::LN_FCPRDRVR: break;
//        case NS_rtf::LN_LCBPRDRVR: break;
//        case NS_rtf::LN_FCPRENVPORT: break;
//        case NS_rtf::LN_LCBPRENVPORT: break;
//        case NS_rtf::LN_FCPRENVLAND: break;
//        case NS_rtf::LN_LCBPRENVLAND: break;
//        case NS_rtf::LN_FCWSS: break;
//        case NS_rtf::LN_LCBWSS: break;
//        case NS_rtf::LN_FCDOP: break;
//        case NS_rtf::LN_LCBDOP: break;
//        case NS_rtf::LN_FCSTTBFASSOC: break;
//        case NS_rtf::LN_LCBSTTBFASSOC: break;
//        case NS_rtf::LN_FCCLX: break;
//        case NS_rtf::LN_LCBCLX: break;
//        case NS_rtf::LN_FCPLCFPGDFTN: break;
//        case NS_rtf::LN_LCBPLCFPGDFTN: break;
//        case NS_rtf::LN_FCAUTOSAVESOURCE: break;
//        case NS_rtf::LN_LCBAUTOSAVESOURCE: break;
//        case NS_rtf::LN_FCGRPXSTATNOWNERS: break;
//        case NS_rtf::LN_LCBGRPXSTATNOWNERS: break;
//        case NS_rtf::LN_FCSTTBFATNBKMK: break;
//        case NS_rtf::LN_LCBSTTBFATNBKMK: break;
//        case NS_rtf::LN_FCPLCDOAMOM: break;
//        case NS_rtf::LN_LCBPLCDOAMOM: break;
//        case NS_rtf::LN_FCPLCDOAHDR: break;
//        case NS_rtf::LN_LCBPLCDOAHDR: break;
//        case NS_rtf::LN_FCPLCSPAMOM: break;
//        case NS_rtf::LN_LCBPLCSPAMOM: break;
//        case NS_rtf::LN_FCPLCSPAHDR: break;
//        case NS_rtf::LN_LCBPLCSPAHDR: break;
//        case NS_rtf::LN_FCPLCFATNBKF: break;
//        case NS_rtf::LN_LCBPLCFATNBKF: break;
//        case NS_rtf::LN_FCPLCFATNBKL: break;
//        case NS_rtf::LN_LCBPLCFATNBKL: break;
//        case NS_rtf::LN_FCPMS: break;
//        case NS_rtf::LN_LCBPMS: break;
//        case NS_rtf::LN_FCFORMFLDSTTBF: break;
//        case NS_rtf::LN_LCBFORMFLDSTTBF: break;
//        case NS_rtf::LN_FCPLCFENDREF: break;
//        case NS_rtf::LN_LCBPLCFENDREF: break;
//        case NS_rtf::LN_FCPLCFENDTXT: break;
//        case NS_rtf::LN_LCBPLCFENDTXT: break;
//        case NS_rtf::LN_FCPLCFFLDEDN: break;
//        case NS_rtf::LN_LCBPLCFFLDEDN: break;
//        case NS_rtf::LN_FCPLCFPGDEDN: break;
//        case NS_rtf::LN_LCBPLCFPGDEDN: break;
//        case NS_rtf::LN_FCDGGINFO: break;
//        case NS_rtf::LN_LCBDGGINFO: break;
//        case NS_rtf::LN_FCSTTBFRMARK: break;
//        case NS_rtf::LN_LCBSTTBFRMARK: break;
//        case NS_rtf::LN_FCSTTBFCAPTION: break;
//        case NS_rtf::LN_LCBSTTBFCAPTION: break;
//        case NS_rtf::LN_FCSTTBFAUTOCAPTION: break;
//        case NS_rtf::LN_LCBSTTBFAUTOCAPTION: break;
//        case NS_rtf::LN_FCPLCFWKB: break;
//        case NS_rtf::LN_LCBPLCFWKB: break;
//        case NS_rtf::LN_FCPLCFSPL: break;
//        case NS_rtf::LN_LCBPLCFSPL: break;
//        case NS_rtf::LN_FCPLCFTXBXTXT: break;
//        case NS_rtf::LN_LCBPLCFTXBXTXT: break;
//        case NS_rtf::LN_FCPLCFFLDTXBX: break;
//        case NS_rtf::LN_LCBPLCFFLDTXBX: break;
//        case NS_rtf::LN_FCPLCFHDRTXBXTXT: break;
//        case NS_rtf::LN_LCBPLCFHDRTXBXTXT: break;
//        case NS_rtf::LN_FCPLCFFLDHDRTXBX: break;
//        case NS_rtf::LN_LCBPLCFFLDHDRTXBX: break;
//        case NS_rtf::LN_FCSTWUSER: break;
//        case NS_rtf::LN_LCBSTWUSER: break;
//        case NS_rtf::LN_FCSTTBTTMBD: break;
//        case NS_rtf::LN_LCBSTTBTTMBD: break;
//        case NS_rtf::LN_FCUNUSED: break;
//        case NS_rtf::LN_LCBUNUSED: break;
//        case NS_rtf::LN_FCPGDMOTHER: break;
//        case NS_rtf::LN_LCBPGDMOTHER: break;
//        case NS_rtf::LN_FCBKDMOTHER: break;
//        case NS_rtf::LN_LCBBKDMOTHER: break;
//        case NS_rtf::LN_FCPGDFTN: break;
//        case NS_rtf::LN_LCBPGDFTN: break;
//        case NS_rtf::LN_FCBKDFTN: break;
//        case NS_rtf::LN_LCBBKDFTN: break;
//        case NS_rtf::LN_FCPGDEDN: break;
//        case NS_rtf::LN_LCBPGDEDN: break;
//        case NS_rtf::LN_FCBKDEDN: break;
//        case NS_rtf::LN_LCBBKDEDN: break;
//        case NS_rtf::LN_FCSTTBFINTLFLD: break;
//        case NS_rtf::LN_LCBSTTBFINTLFLD: break;
//        case NS_rtf::LN_FCROUTESLIP: break;
//        case NS_rtf::LN_LCBROUTESLIP: break;
//        case NS_rtf::LN_FCSTTBSAVEDBY: break;
//        case NS_rtf::LN_LCBSTTBSAVEDBY: break;
//        case NS_rtf::LN_FCSTTBFNM: break;
//        case NS_rtf::LN_LCBSTTBFNM: break;
//        case NS_rtf::LN_FCPLCFLST: break;
//        case NS_rtf::LN_LCBPLCFLST: break;
//        case NS_rtf::LN_FCPLFLFO: break;
//        case NS_rtf::LN_LCBPLFLFO: break;
//        case NS_rtf::LN_FCPLCFTXBXBKD: break;
//        case NS_rtf::LN_LCBPLCFTXBXBKD: break;
//        case NS_rtf::LN_FCPLCFTXBXHDRBKD: break;
//        case NS_rtf::LN_LCBPLCFTXBXHDRBKD: break;
//        case NS_rtf::LN_FCDOCUNDO: break;
//        case NS_rtf::LN_LCBDOCUNDO: break;
//        case NS_rtf::LN_FCRGBUSE: break;
//        case NS_rtf::LN_LCBRGBUSE: break;
//        case NS_rtf::LN_FCUSP: break;
//        case NS_rtf::LN_LCBUSP: break;
//        case NS_rtf::LN_FCUSKF: break;
//        case NS_rtf::LN_LCBUSKF: break;
//        case NS_rtf::LN_FCPLCUPCRGBUSE: break;
//        case NS_rtf::LN_LCBPLCUPCRGBUSE: break;
//        case NS_rtf::LN_FCPLCUPCUSP: break;
//        case NS_rtf::LN_LCBPLCUPCUSP: break;
//        case NS_rtf::LN_FCSTTBGLSYSTYLE: break;
//        case NS_rtf::LN_LCBSTTBGLSYSTYLE: break;
//        case NS_rtf::LN_FCPLGOSL: break;
//        case NS_rtf::LN_LCBPLGOSL: break;
//        case NS_rtf::LN_FCPLCOCX: break;
//        case NS_rtf::LN_LCBPLCOCX: break;
//        case NS_rtf::LN_FCPLCFBTELVC: break;
//        case NS_rtf::LN_LCBPLCFBTELVC: break;
//        case NS_rtf::LN_DWLOWDATETIME: break;
//        case NS_rtf::LN_DWHIGHDATETIME: break;
//        case NS_rtf::LN_FCPLCFLVC: break;
//        case NS_rtf::LN_LCBPLCFLVC: break;
//        case NS_rtf::LN_FCPLCASUMY: break;
//        case NS_rtf::LN_LCBPLCASUMY: break;
//        case NS_rtf::LN_FCPLCFGRAM: break;
//        case NS_rtf::LN_LCBPLCFGRAM: break;
//        case NS_rtf::LN_FCSTTBLISTNAMES: break;
//        case NS_rtf::LN_LCBSTTBLISTNAMES: break;
//        case NS_rtf::LN_FCSTTBFUSSR: break;
//        case NS_rtf::LN_LCBSTTBFUSSR: break;
//        case NS_rtf::LN_FN: break;
//        case NS_rtf::LN_FCSEPX: break;
//        case NS_rtf::LN_FNMPR: break;
//        case NS_rtf::LN_FCMPR: break;
//        case NS_rtf::LN_ICOFORE: break;
//        case NS_rtf::LN_ICOBACK: break;
//        case NS_rtf::LN_IPAT: break;
//        case NS_rtf::LN_SHDFORECOLOR: break;
//        case NS_rtf::LN_SHDBACKCOLOR: break;
//        case NS_rtf::LN_SHDPATTERN: break;
//        case NS_rtf::LN_DPTLINEWIDTH: break;
//        case NS_rtf::LN_BRCTYPE: break;
//        case NS_rtf::LN_ICO: break;
//        case NS_rtf::LN_DPTSPACE: break;
//        case NS_rtf::LN_FSHADOW: break;
//        case NS_rtf::LN_FFRAME: break;
//        case NS_rtf::LN_UNUSED2_15: break;
//        case NS_rtf::LN_FFIRSTMERGED: break;
//        case NS_rtf::LN_FMERGED: break;
//        case NS_rtf::LN_FVERTICAL: break;
//        case NS_rtf::LN_FBACKWARD: break;
//        case NS_rtf::LN_FROTATEFONT: break;
//        case NS_rtf::LN_FVERTMERGE: break;
//        case NS_rtf::LN_FVERTRESTART: break;
//        case NS_rtf::LN_VERTALIGN: break;
//        case NS_rtf::LN_FUNUSED: break;
//        case NS_rtf::LN_WUNUSED: break;
//        case NS_rtf::LN_BRCTOP: break;
//        case NS_rtf::LN_BRCLEFT: break;
//        case NS_rtf::LN_BRCBOTTOM: break;
//        case NS_rtf::LN_BRCRIGHT: break;
//        case NS_rtf::LN_IBKL: break;
//        case NS_rtf::LN_ITCFIRST: break;
//        case NS_rtf::LN_FPUB: break;
//        case NS_rtf::LN_ITCLIM: break;
//        case NS_rtf::LN_FCOL: break;
//        case NS_rtf::LN_LINECOLOR: break;
//        case NS_rtf::LN_LINEWIDTH: break;
//        case NS_rtf::LN_LINETYPE: break;
//        case NS_rtf::LN_MM: break;
//        case NS_rtf::LN_XEXT: break;
//        case NS_rtf::LN_YEXT: break;
//        case NS_rtf::LN_HMF: break;
//        case NS_rtf::LN_LCB: break;
//        case NS_rtf::LN_CBHEADER: break;
//        case NS_rtf::LN_MFP: break;
//        case NS_rtf::LN_BM_RCWINMF: break;
//        case NS_rtf::LN_DXAGOAL: break;
//        case NS_rtf::LN_DYAGOAL: break;
//        case NS_rtf::LN_MX: break;
//        case NS_rtf::LN_MY: break;
//        case NS_rtf::LN_DXACROPLEFT: break;
//        case NS_rtf::LN_DYACROPTOP: break;
//        case NS_rtf::LN_DXACROPRIGHT: break;
//        case NS_rtf::LN_DYACROPBOTTOM: break;
//        case NS_rtf::LN_BRCL: break;
//        case NS_rtf::LN_FFRAMEEMPTY: break;
//        case NS_rtf::LN_FBITMAP: break;
//        case NS_rtf::LN_FDRAWHATCH: break;
//        case NS_rtf::LN_FERROR: break;
//        case NS_rtf::LN_BPP: break;
//        case NS_rtf::LN_DXAORIGIN: break;
//        case NS_rtf::LN_DYAORIGIN: break;
//        case NS_rtf::LN_CPROPS: break;
//        case NS_rtf::LN_LINEPROPSTOP: break;
//        case NS_rtf::LN_LINEPROPSLEFT: break;
//        case NS_rtf::LN_LINEPROPSBOTTOM: break;
//        case NS_rtf::LN_LINEPROPSRIGHT: break;
//        case NS_rtf::LN_LINEPROPSHORIZONTAL: break;
//        case NS_rtf::LN_LINEPROPSVERTICAL: break;
//        case NS_rtf::LN_headerr: break;
//        case NS_rtf::LN_footerr: break;
//        case NS_rtf::LN_endnote: break;
//        case NS_rtf::LN_BOOKMARKNAME: break;

//        case NS_rtf::LN_LISTLEVEL: break;
//        case NS_rtf::LN_LFO: break;
//        case NS_rtf::LN_F: break;
//        case NS_rtf::LN_ALTFONTNAME: break;
//        case NS_rtf::LN_XSZFFN: break;
        case NS_rtf::LN_XSTZNAME:
            m_pImpl->m_pCurrentEntry->sStyleName1 = sValue;
        break;
        case NS_rtf::LN_XSTZNAME1:
            m_pImpl->m_pCurrentEntry->sStyleName = sValue;
        break;
//        case NS_rtf::LN_UPXSTART: break;
        case NS_rtf::LN_UPX:
            resolveAttributeProperties(val);
        break;
//        case NS_rtf::LN_sed: break;
//        case NS_rtf::LN_picf: break;
//        case NS_rtf::LN_rgbrc: break;
//        case NS_rtf::LN_shd: break;
//        case NS_rtf::LN_cellShd: break;
//        case NS_rtf::LN_cellTopColor: break;
//        case NS_rtf::LN_cellLeftColor: break;
//        case NS_rtf::LN_cellBottomColor: break;
//        case NS_rtf::LN_cellRightColor: break;

//        case NS_rtf::LN_LISTTABLE: break;
//        case NS_rtf::LN_LFOTABLE: break;
//        case NS_rtf::LN_StyleSheetTable: break;
//        case NS_rtf::LN_STYLESHEET: break;
        break;
        case NS_ooxml::LN_CT_Style_type:
            if (nIntValue == 1)
                *(m_pImpl->m_pCurrentEntry->pProperties) = *(m_pImpl->m_pDefaultParaProps);
            else if (nIntValue == 2)
                *(m_pImpl->m_pCurrentEntry->pProperties) = *(m_pImpl->m_pDefaultCharProps);
            m_pImpl->m_pCurrentEntry->nStyleTypeCode = (StyleType)nIntValue;
        break;
        default:
        {
            //----> debug
            int nVal = val.getInt();
            ++nVal;
            //<---- debug
        }
    }
}
/*-- 19.06.2006 12:04:33---------------------------------------------------

  -----------------------------------------------------------------------*/
void StyleSheetTable::sprm(doctok::Sprm & sprm_)
{
    sal_uInt32 nId = sprm_.getId();
    doctok::Value::Pointer_t pValue = sprm_.getValue();
    sal_Int32 nIntValue = pValue.get() ? pValue->getInt() : 0;
    (void)nIntValue;
    rtl::OUString sStringValue = pValue.get() ? pValue->getString() : rtl::OUString();
    //printf ( "StyleSheetTable::sprm(0x%.4x, 0x%.4x) [%s]\n", (unsigned int)nId, (unsigned int)nIntValue, ::rtl::OUStringToOString(sStringValue, RTL_TEXTENCODING_DONTKNOW).getStr());
    
    switch(nId)
    {
    case NS_ooxml::LN_CT_Style_name:
        m_pImpl->m_pCurrentEntry->sStyleName == sStringValue;
        if (m_pImpl->m_pCurrentEntry->nStyleTypeCode == STYLE_TYPE_PARA)
            m_pImpl->m_pCurrentEntry->pProperties->Insert(PROP_PARA_STYLE_NAME, uno::makeAny(sStringValue));
        else if (m_pImpl->m_pCurrentEntry->nStyleTypeCode == STYLE_TYPE_CHAR)
            m_pImpl->m_pCurrentEntry->pProperties->Insert(PROP_CHAR_STYLE_NAME, uno::makeAny(sStringValue));
        break;    	
    case NS_ooxml::LN_CT_Style_basedOn:
        break;
    case NS_ooxml::LN_CT_Style_next:
        break;
    case NS_ooxml::LN_CT_Style_aliases:
    case NS_ooxml::LN_CT_Style_link:
    case NS_ooxml::LN_CT_Style_autoRedefine:
    case NS_ooxml::LN_CT_Style_hidden:
    case NS_ooxml::LN_CT_Style_uiPriority:
    case NS_ooxml::LN_CT_Style_semiHidden:
    case NS_ooxml::LN_CT_Style_unhideWhenUsed:
    case NS_ooxml::LN_CT_Style_qFormat:
    case NS_ooxml::LN_CT_Style_locked:
    case NS_ooxml::LN_CT_Style_personal:
    case NS_ooxml::LN_CT_Style_personalCompose:
    case NS_ooxml::LN_CT_Style_personalReply:
    case NS_ooxml::LN_CT_Style_rsid:
    case NS_ooxml::LN_CT_Style_tblPr:
    case NS_ooxml::LN_CT_Style_trPr:
    case NS_ooxml::LN_CT_Style_tcPr:
    case NS_ooxml::LN_CT_Style_tblStylePr:
        break;
    case NS_ooxml::LN_CT_DocDefaults_pPrDefault:
    case NS_ooxml::LN_CT_DocDefaults_rPrDefault:
        resolveSprmProps(sprm_);
        break;
    case NS_ooxml::LN_CT_PPrDefault_pPr:
        m_pImpl->m_rDMapper.sprm( sprm_, m_pImpl->m_pDefaultParaProps );
        break;
    case NS_ooxml::LN_CT_RPrDefault_rPr:
        m_pImpl->m_rDMapper.sprm( sprm_, m_pImpl->m_pDefaultCharProps );
        break;
    case NS_ooxml::LN_CT_Style_pPr:
    case NS_ooxml::LN_CT_Style_rPr:
    default:
        if (!m_pImpl->m_pCurrentEntry)
            break;
        m_pImpl->m_rDMapper.sprm( sprm_, m_pImpl->m_pCurrentEntry->pProperties );
        break;
    }

//    if(!m_pImpl->m_pCurrentEntry)
//    	return;

    //fill the attributes of the style sheet
//    m_pImpl->m_rDMapper.sprm( sprm_, m_pImpl->m_pCurrentProps );
}
/*-- 19.06.2006 12:04:33---------------------------------------------------

  -----------------------------------------------------------------------*/
void StyleSheetTable::entry(int /*pos*/, doctok::Reference<Properties>::Pointer_t ref)
{
    //create a new style entry
//    printf("StyleSheetTable::entry(...)\n");
    OSL_ENSURE( !m_pImpl->m_pCurrentEntry, "current entry has to be NULL here");
    m_pImpl->m_pCurrentEntry = new StyleSheetEntry;
    ref->resolve(*this);
    //append it to the table
    m_pImpl->m_aStyleSheetEntries.push_back( *m_pImpl->m_pCurrentEntry );
    m_pImpl->m_pCurrentEntry = 0;
}
/*-- 21.06.2006 15:34:49---------------------------------------------------
    sorting helper
  -----------------------------------------------------------------------*/
typedef std::vector< beans::PropertyValue > _PropValVector;
class PropValVector : public _PropValVector
{
public:
    PropValVector(){}

    void    Insert( beans::PropertyValue aVal );
    uno::Sequence< uno::Any > getValues();
    uno::Sequence< ::rtl::OUString > getNames();
};
void    PropValVector::Insert( beans::PropertyValue aVal )
{
    _PropValVector::iterator aIt = begin();
    while(aIt != end())
    {
        if(aIt->Name > aVal.Name)
        {
            insert( aIt, aVal );
            return;
        }
        ++aIt;
    }
    push_back( aVal );
}
uno::Sequence< uno::Any > PropValVector::getValues()
{
    uno::Sequence< uno::Any > aRet( size() );
    uno::Any* pValues = aRet.getArray();
    sal_Int32 nVal = 0;
    _PropValVector::iterator aIt = begin();
    while(aIt != end())
    {
        pValues[nVal++] = aIt->Value;
        ++aIt;
    }
    return aRet;
}
uno::Sequence< ::rtl::OUString > PropValVector::getNames()
{
    uno::Sequence< ::rtl::OUString > aRet( size() );
    ::rtl::OUString* pNames = aRet.getArray();
    sal_Int32 nVal = 0;
    _PropValVector::iterator aIt = begin();
    while(aIt != end())
    {
        pNames[nVal++] = aIt->Name;
        ++aIt;
    }
    return aRet;
}
/*-- 21.06.2006 13:35:48---------------------------------------------------

  -----------------------------------------------------------------------*/
void StyleSheetTable::ApplyStyleSheets(uno::Reference< text::XTextDocument> xTextDocument, FontTablePtr rFontTable)
{
    try
    {
        uno::Reference< style::XStyleFamiliesSupplier > xStylesSupplier( xTextDocument, uno::UNO_QUERY_THROW );
        uno::Reference< lang::XMultiServiceFactory > xDocFactory( xTextDocument, uno::UNO_QUERY_THROW );
        uno::Reference< container::XNameAccess > xStyleFamilies = xStylesSupplier->getStyleFamilies();
        uno::Reference<container::XNameContainer> xCharStyles;
        uno::Reference<container::XNameContainer> xParaStyles;

        xStyleFamilies->getByName(::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("CharacterStyles"))) >>= xCharStyles;
        xStyleFamilies->getByName(::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("ParagraphStyles"))) >>= xParaStyles;
        if(xCharStyles.is() && xParaStyles.is())
        {
            std::vector< StyleSheetEntry >::iterator aIt = m_pImpl->m_aStyleSheetEntries.begin();
            while( aIt != m_pImpl->m_aStyleSheetEntries.end() )
            {
                bool bParaStyle = aIt->nStyleTypeCode == STYLE_TYPE_PARA;
                bool bInsert = false;
                uno::Reference< container::XNameContainer > xStyles = bParaStyle ? xParaStyles : xCharStyles;
                uno::Reference< style::XStyle > xStyle;
                ::rtl::OUString sConvertedStyleName = ConvertStyleName( aIt->sStyleName/*, bParaStyle*/ );
                if(xStyles->hasByName( sConvertedStyleName ))
                    xStyles->getByName( sConvertedStyleName ) >>= xStyle;
                else
                {
                    bInsert = true;
                    xStyle = uno::Reference< style::XStyle >(xDocFactory->createInstance(
                                bParaStyle ?
                                    ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("com.sun.star.style.ParagraphStyle")) :
                                    ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("com.sun.star.style.CharacterStyle"))),
                                    uno::UNO_QUERY_THROW);
                }
                if(aIt->nBaseStyleIdentifier != 0xfff )
                {
                    //find the name of the base style
                    std::vector< StyleSheetEntry >::iterator aBaseStyleIt = m_pImpl->m_aStyleSheetEntries.begin();
                    for( ; aBaseStyleIt !=  m_pImpl->m_aStyleSheetEntries.end(); ++aBaseStyleIt )
                        if(aBaseStyleIt->nStyleIdentifierD == aIt->nBaseStyleIdentifier)
                        {
                            xStyle->setParentStyle(ConvertStyleName( aBaseStyleIt->sStyleName/*, bParaStyle*/ ));
                            break;
                        }
                }
                else if( bParaStyle )
                {
                    //now it's time to set the default parameters - for paragraph styles
                    //Fonts: Western first entry in font table
                    //CJK: second entry
                    //CTL: third entry, if it exists

                    sal_uInt32 nFontCount = rFontTable->size();
                    if( nFontCount > 2 )
                    {
                        uno::Any aTwoHundredFortyTwip = uno::makeAny(12.);
//                      font size to 240 twip (12 pts) for all if not set
                        aIt->pProperties->Insert(PROP_CHAR_HEIGHT        , aTwoHundredFortyTwip, false);
//                      western font not already set -> apply first font
                        const FontEntry* pWesternFontEntry = rFontTable->getFontEntry( 0 );
                        aIt->pProperties->Insert(PROP_CHAR_FONT_NAME, uno::makeAny( pWesternFontEntry->sFontName ), false);
//                      CJK  ... apply second font
                        const FontEntry* pCJKFontEntry  = rFontTable->getFontEntry( 2 );
                        aIt->pProperties->Insert(PROP_CHAR_FONT_NAME_ASIAN, uno::makeAny( pCJKFontEntry->sFontName ), false);
                        aIt->pProperties->Insert(PROP_CHAR_HEIGHT_ASIAN  , aTwoHundredFortyTwip, false);
//                      CTL  ... apply third font, if available
                        if( nFontCount > 3 )
                        {
                            const FontEntry* pCTLFontEntry  = rFontTable->getFontEntry( 3 );
                            aIt->pProperties->Insert(PROP_CHAR_FONT_NAME_COMPLEX, uno::makeAny( pCTLFontEntry->sFontName ), false);
                            aIt->pProperties->Insert(PROP_CHAR_HEIGHT_COMPLEX, aTwoHundredFortyTwip, false);
                        }
                    }
//                  Widow/Orphan -> set both to two if not already set
                    uno::Any aTwo = uno::makeAny(sal_Int8(2));
                    aIt->pProperties->Insert(PROP_PARA_WIDOWS, aTwo, false);
                    aIt->pProperties->Insert(PROP_PARA_ORPHANS, aTwo, false);
//                  Left-to-right direction if not already set
                    aIt->pProperties->Insert(PROP_WRITING_MODE, uno::makeAny( sal_Int16(text::WritingMode_LR_TB) ), false);
//                  font color COL_AUTO if not already set
                    aIt->pProperties->Insert(PROP_CHAR_COLOR, uno::makeAny( sal_Int32(0xffffffff) ), false);
                }

                uno::Sequence< beans::PropertyValue > aPropValues = aIt->pProperties->GetPropertyValues();
                bool bAddFollowStyle = false;
                if(bParaStyle && aIt->nNextStyleIdentifier >= 0 )
                {
                        bAddFollowStyle = true;
                }
                if(bAddFollowStyle || aPropValues.getLength())
                {
//                    sal_Int32 nSetProperties = aPropValues.getLength();
//                    if(bAddFollowStyle)
//                        ++nSetProperties;

//                    uno::Sequence< ::rtl::OUString > aNames( nSetProperties );
//                    ::rtl::OUString* pNames = aNames.getArray();
//                    uno::Sequence< uno::Any > aValues( nSetProperties );
//                    uno::Any* pValues = aValues.getArray();
                    const beans::PropertyValue* pPropValues = aPropValues.getConstArray();
                    PropValVector aSortedPropVals;
                    for( sal_Int32 nProp = 0; nProp < aPropValues.getLength(); ++nProp)
                    {
                        aSortedPropVals.Insert( pPropValues[nProp] );

//                        pNames[nProp] = pPropValues[nProp].Name;
//                        pValues[nProp] = pPropValues[nProp].Value;
                    }
                    if(bAddFollowStyle)
                    {
                        //find the name of the Next style
                        std::vector< StyleSheetEntry >::iterator aNextStyleIt = m_pImpl->m_aStyleSheetEntries.begin();
                        for( ; aNextStyleIt !=  m_pImpl->m_aStyleSheetEntries.end(); ++aNextStyleIt )
                            if(aNextStyleIt->nStyleIdentifierD == aIt->nNextStyleIdentifier)
                            {
                                beans::PropertyValue aNew;
                                aNew.Name = ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("FollowStyle"));
                                aNew.Value = uno::makeAny(ConvertStyleName( aNextStyleIt->sStyleName/*, bParaStyle*/ ));
                                aSortedPropVals.Insert( aNew );
                                break;
                            }
//                        pNames[--nSetProperties] = ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("FollowStyle"));
//                        pValues[nSetProperties] =  uno::makeAny(
//                                m_pImpl->m_aStyleSheetEntries[aIt->nNextStyleIdentifier].sStyleName);
                    }

                    uno::Reference< beans::XMultiPropertySet > xMultiPropertySet( xStyle, uno::UNO_QUERY_THROW);
//                    xMultiPropertySet->setPropertyValues( aNames, aValues );
                    xMultiPropertySet->setPropertyValues( aSortedPropVals.getNames(), aSortedPropVals.getValues() );
                }
                if(bInsert)
                    xStyles->insertByName( sConvertedStyleName, uno::makeAny( xStyle) );
                ++aIt;
            }
        }
    }
    catch( uno::Exception& )
    {
        OSL_ASSERT("Styles could not be imported completely");
    }
}
/*-- 22.06.2006 15:56:56---------------------------------------------------

  -----------------------------------------------------------------------*/
const StyleSheetEntry* StyleSheetTable::FindStyleSheetByISTD(sal_Int32 nIndex)
{
    const StyleSheetEntry* pRet = 0;
    for( sal_uInt32 nPos = 0; nPos < m_pImpl->m_aStyleSheetEntries.size(); ++nPos )
    {
        if( m_pImpl->m_aStyleSheetEntries[nPos].nStyleIdentifierD == nIndex)
        {
            pRet = &m_pImpl->m_aStyleSheetEntries[nPos];
            break;
        }
    }
    return pRet;
}

/*-- 17.07.2006 11:47:00---------------------------------------------------

  -----------------------------------------------------------------------*/
const StyleSheetEntry* StyleSheetTable::FindParentStyleSheet(sal_Int32 nBaseStyle)
{
    if(nBaseStyle < 0 && m_pImpl->m_pCurrentEntry)
        nBaseStyle = m_pImpl->m_pCurrentEntry->nBaseStyleIdentifier;

    const StyleSheetEntry* pRet = 0;
    for( sal_uInt32 nPos = 0; nPos < m_pImpl->m_aStyleSheetEntries.size(); ++nPos )
    {
        if( m_pImpl->m_aStyleSheetEntries[nPos].nStyleIdentifierD == nBaseStyle)
        {
            pRet = &m_pImpl->m_aStyleSheetEntries[nPos];
            break;
        }
    }
    return pRet;
}
/*-- 21.12.2006 15:58:23---------------------------------------------------

  -----------------------------------------------------------------------*/
static const sal_Char *aStyleNamePairs[] =
{
    "Normal",                     "Standard",               //0
    "Heading 1",                  "Heading 1",              //1
    "Heading 2",                  "Heading 2",              //2
    "Heading 3",                  "Heading 3",              //3
    "Heading 4",                  "Heading 4",              //4
    "Heading 5",                  "Heading 5",              //5
    "Heading 6",                  "Heading 6",              //6
    "Heading 7",                  "Heading 7",              //7
    "Heading 8",                  "Heading 8",              //8
    "Heading 9",                  "Heading 9",              //9
    "Index 1",                   "Index 1",               //10
    "Index 2",                   "Index 2",               //11
    "Index 3",                   "Index 3",               //12
    "Index 4",                   0,                       //13
    "Index 5",                   0,                       //14
    "Index 6",                   0,                       //15
    "Index 7",                   0,                       //16
    "Index 8",                   0,                       //17
    "Index 9",                   0,                       //18
    "TOC 1",                     "Contents 1",            //19
    "TOC 2",                     "Contents 2",            //20
    "TOC 3",                     "Contents 3",            //21
    "TOC 4",                     "Contents 4",            //22
    "TOC 5",                     "Contents 5",            //23
    "TOC 6",                     "Contents 6",            //24
    "TOC 7",                     "Contents 7",            //25
    "TOC 8",                     "Contents 8",            //26
    "TOC 9",                     "Contents 9",            //27
    "Normal Indent",             0,                        //28
    "Footnote Text",             "Footnote",              //29
    "Annotation Text",           0,                       //30
    "Header",                    "Header"                 //31
    "Footer",                    "Footer"                 //32
    "Index Heading",             "Index Heading"          //33
    "Caption",                   0,                       //34
    "Table of Figures",          0,                       //35
    "Envelope Address",          "Addressee",             //36
    "Envelope Return",           "Sender",                //37
    "Footnote Reference",        "Footnote anchor",      //38
    "Annotation Reference",      0,                    //39
    "Line Number",               "Line numbering",         //40
    "Page Number",               "Page Number",            //41
    "Endnote Reference",         "Endnote anchor"         //42
    "Endnote Text",              "Endnote Symbol",        //43
    "Table of Authorities",      0,                    //44
    "Macro Text",                0,                      //45
    "TOA Heading",               0,                      //46
    "List",                      "List",                   //47
    "List 2",                    0,                        //48
    "List 3",                    0,                        //49
    "List 4",                    0,                        //50
    "List 5",                    0,                        //51
    "List Bullet",               0,                        //52
    "List Bullet 2",             0,                        //53
    "List Bullet 3",             0,                        //54
    "List Bullet 4",             0,                        //55
    "List Bullet 5",             0,                        //56
    "List Number",               0,                        //57
    "List Number 2",             0,                        //58
    "List Number 3",             0,                        //59
    "List Number 4",             0,                        //60
    "List Number 5",             0,                        //61
    "Title",                     "Title",                  //62
    "Closing",                   0,                        //63
    "Signature",                 "Signature",      //64
    "Default Paragraph Font",    0,                //65
    "Body Text",                 "Text body",      //66
    "Body Text Indent",          "Text body indent",//67
    "List Continue",             0,                //68
    "List Continue 2",           0,                //69
    "List Continue 3",           0,                //70
    "List Continue 4",           0,                //71
    "List Continue 5",           0,                //72
    "Message Header",            0,                //73
    "Subtitle",                  "Subtitle",       //74
    "Salutation",                0,                //75
    "Date",                      0,                //76
    "Body Text First Indent",    "Body Text Indent",//77
    "Body Text First Indent 2",  0,                //78
    "Note Heading",              0,                //79
    "Body Text 2",               0,                //80
    "Body Text 3",               0,                //81
    "Body Text Indent 2",        0,                //82
    "Body Text Indent 3",        0,                //83
    "Block Text",                0,                //84
    "Hyperlink",                 "Internet link",   //85
    "Followed Hyperlink",        "Visited Internet Link", //86
    "Strong",                    "Strong Emphasis",    //87
    "Emphasis",                  "Emphasis",           //88
    "Document Map",              0,                //89
    "Plain Text",                0                 //90
};


::rtl::OUString StyleSheetTable::ConvertStyleName( const ::rtl::OUString& rWWName/*, bool bParagraphStyle*/ )
{
    ::rtl::OUString sRet( rWWName );
    if(!m_pImpl->m_aStyleNameMap.size())
    {
        for( sal_uInt32 nPair = 0; nPair < sizeof(aStyleNamePairs) / sizeof( sal_Char*) / 2; ++nPair)
        {
            //::std::pair<PropertyNameMap_t::iterator,bool> aInsertIt =
                m_pImpl->m_aStyleNameMap.insert( StringPairMap_t::value_type(
                    ::rtl::OUString::createFromAscii(aStyleNamePairs[2 * nPair]),
                    ::rtl::OUString::createFromAscii(aStyleNamePairs[2 * nPair + 1]) ));
        }
    }
    StringPairMap_t::iterator aIt = m_pImpl->m_aStyleNameMap.find( rWWName );
    if(aIt != m_pImpl->m_aStyleNameMap.end() && aIt->second.getLength())
        sRet = aIt->second;
    return sRet;
}

::rtl::OUString StyleSheetTable::GetStyleIdFromIndex(const sal_uInt32 sti)
{
    ::rtl::OUString sRet;
    if (sti < sizeof(aStyleNamePairs) / sizeof( sal_Char*) / 2)
        sRet = ::rtl::OUString::createFromAscii(aStyleNamePairs[2 * sti]);
    return sRet;
}

void StyleSheetTable::resolveSprmProps(doctok::Sprm & sprm_)
{
    doctok::Reference<Properties>::Pointer_t pProperties = sprm_.getProps();
    if( pProperties.get())
        pProperties->resolve(*this);
}

void StyleSheetTable::resolveAttributeProperties(doctok::Value & val)
{
    doctok::Reference<Properties>::Pointer_t pProperties = val.getProperties();
    if( pProperties.get())
        pProperties->resolve(*this);
}

}//namespace dmapper

