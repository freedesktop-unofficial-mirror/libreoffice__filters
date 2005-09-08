/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: sw_swtypes.cxx,v $
 *
 *  $Revision: 1.5 $
 *
 *  last change: $Author: rt $ $Date: 2005-09-08 08:22:04 $
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


#pragma hdrstop

#ifndef _SV_WINDOW_HXX //autogen
#include <vcl/window.hxx>
#endif
#ifndef _SV_GRAPH_HXX //autogen
#include <vcl/graph.hxx>
#endif
#ifndef _OFF_APP_HXX //autogen
#include <bf_offmgr/app.hxx>
#endif
// auto strip #ifndef _OFA_OSPLCFG_HXX //autogen
// auto strip #include <bf_offmgr/osplcfg.hxx>
// auto strip #endif
// auto strip #ifndef _LANG_HXX
// auto strip #include <tools/lang.hxx>
// auto strip #endif
// auto strip #ifndef _ISOLANG_HXX
// auto strip #include <tools/isolang.hxx>
// auto strip #endif

#ifndef _COMPHELPER_PROCESSFACTORY_HXX_
#include <comphelper/processfactory.hxx>
#endif
// auto strip #ifndef _COM_SUN_STAR_LANG_LOCALE_HPP_
// auto strip #include <com/sun/star/lang/Locale.hpp>
// auto strip #endif
// auto strip #ifndef _COM_SUN_STAR_LINGUISTIC2_XSPELLCHECKER1_HPP_
// auto strip #include <com/sun/star/linguistic2/XSpellChecker1.hpp>
// auto strip #endif
// auto strip #ifndef _COM_SUN_STAR_LINGUISTIC2_XHYPHENATOR_HPP_
// auto strip #include <com/sun/star/linguistic2/XHyphenator.hpp>
// auto strip #endif
#ifndef _UNO_LINGU_HXX
#include <bf_svx/unolingu.hxx>
#endif
// auto strip #ifndef _COM_SUN_STAR_LINGUISTIC2_XTHESAURUS_HPP_
// auto strip #include <com/sun/star/linguistic2/XThesaurus.hpp>
// auto strip #endif
// auto strip #ifndef _COM_SUN_STAR_BEANS_XPROPERTYSET_HPP_
// auto strip #include <com/sun/star/beans/XPropertySet.hpp>
// auto strip #endif
// auto strip #ifndef _COM_SUN_STAR_LANG_XMULTISERVICEFACTORY_HPP_
// auto strip #include <com/sun/star/lang/XMultiServiceFactory.hpp>
// auto strip #endif

#ifndef _PAGEFRM_HXX
#include <pagefrm.hxx>
#endif
// auto strip #ifndef _SWATRSET_HXX
// auto strip #include <swatrset.hxx>
// auto strip #endif
// auto strip #ifndef _FRMFMT_HXX
// auto strip #include <frmfmt.hxx>
// auto strip #endif
#ifndef _FRMTOOL_HXX
#include <frmtool.hxx>
#endif
#ifndef _NDTXT_HXX
#include <ndtxt.hxx>
#endif
#ifndef _UNDOBJ_HXX
#include <undobj.hxx>
#endif
// auto strip #ifndef _SWTABLE_HXX
// auto strip #include <swtable.hxx>
// auto strip #endif
#ifndef _VISCRS_HXX
#include <viscrs.hxx>
#endif
#ifndef _FNTCACHE_HXX
#include <fntcache.hxx>
#endif
#ifndef _SWFNTCCH_HXX
#include <swfntcch.hxx>
#endif
#ifndef _HFFRM_HXX
#include <hffrm.hxx>
#endif
#ifndef _COLFRM_HXX
#include <colfrm.hxx>
#endif
#ifndef _BODYFRM_HXX
#include <bodyfrm.hxx>
#endif
#ifndef _TABFRM_HXX
#include <tabfrm.hxx>
#endif
#ifndef _TXTFRM_HXX
#include <txtfrm.hxx>
#endif
#ifndef _SWTBLFMT_HXX
#include <swtblfmt.hxx>
#endif
#ifndef _ROWFRM_HXX
#include <rowfrm.hxx>
#endif
#ifndef _CELLFRM_HXX
#include <cellfrm.hxx>
#endif
#ifndef _SECTFRM_HXX
#include <sectfrm.hxx>
#endif
namespace binfilter {

using namespace ::com::sun::star;
using namespace ::com::sun::star::uno;
using namespace ::com::sun::star::util;
using namespace ::com::sun::star::lang;
using namespace ::com::sun::star::linguistic2;
using namespace ::comphelper;

#ifndef PROFILE
// Code zum Initialisieren von Statics im eigenen Code-Segment
#pragma code_seg( "SWSTATICS" )
#endif

ByteString aEmptyByteStr;		// Konstante Strings
String aEmptyStr;				// Konstante Strings
String aDotStr('.');			// Konstante Strings

IMPL_FIXEDMEMPOOL_NEWDEL( SwAttrSet, 25, 25 )
IMPL_FIXEDMEMPOOL_NEWDEL( SwStartNode, 20, 20 )
IMPL_FIXEDMEMPOOL_NEWDEL( SwEndNode,   20, 20 )
IMPL_FIXEDMEMPOOL_NEWDEL( SwTableBox, 50, 50 )
IMPL_FIXEDMEMPOOL_NEWDEL( SwUndoDelete, 10, 10 )
IMPL_FIXEDMEMPOOL_NEWDEL( SwUndoInsert, 10, 10 )
IMPL_FIXEDMEMPOOL_NEWDEL( SwPaM, 10, 10 )
IMPL_FIXEDMEMPOOL_NEWDEL( SwCursor, 10, 10 )
IMPL_FIXEDMEMPOOL_NEWDEL( SwShellCrsr, 10, 10 )
IMPL_FIXEDMEMPOOL_NEWDEL( SwTxtNode, 50, 50 )
IMPL_FIXEDMEMPOOL_NEWDEL( SwpHints, 25, 25 )
IMPL_FIXEDMEMPOOL_NEWDEL( SwFntObj, 50, 50 )
IMPL_FIXEDMEMPOOL_NEWDEL( SwFontObj, 50, 50 )
IMPL_FIXEDMEMPOOL_NEWDEL( SwFrmFmt,		20, 20 )
IMPL_FIXEDMEMPOOL_NEWDEL( SwFlyFrmFmt,	10, 10 )
IMPL_FIXEDMEMPOOL_NEWDEL( SwDrawFrmFmt,	10, 10 )
IMPL_FIXEDMEMPOOL_NEWDEL( SwBorderAttrs, 100, 100 )
IMPL_FIXEDMEMPOOL_NEWDEL( SwCellFrm,	50, 50 )
IMPL_FIXEDMEMPOOL_NEWDEL( SwRowFrm,		10, 10 )
IMPL_FIXEDMEMPOOL_NEWDEL( SwColumnFrm,	40, 40 )
IMPL_FIXEDMEMPOOL_NEWDEL( SwSectionFrm,	20, 20 )
IMPL_FIXEDMEMPOOL_NEWDEL( SwTabFrm,	10, 10 )
IMPL_FIXEDMEMPOOL_NEWDEL( SwPageFrm,	20, 20 )
IMPL_FIXEDMEMPOOL_NEWDEL( SwBodyFrm,	20, 20 )
IMPL_FIXEDMEMPOOL_NEWDEL( SwHeaderFrm,	20, 20 )
IMPL_FIXEDMEMPOOL_NEWDEL( SwFooterFrm,	20, 20 )
IMPL_FIXEDMEMPOOL_NEWDEL( SwTxtFrm, 	50,  50 )
IMPL_FIXEDMEMPOOL_NEWDEL( SwTableFmt, 10, 10 )
IMPL_FIXEDMEMPOOL_NEWDEL( SwTableLineFmt, 10, 10 )
IMPL_FIXEDMEMPOOL_NEWDEL( SwTableBoxFmt, 50, 50 )
IMPL_FIXEDMEMPOOL_NEWDEL( _SwCursor_SavePos, 20, 20 )


#ifndef PROFILE
#pragma code_seg()
#endif

/*N*/ Size GetGraphicSizeTwip( const Graphic& rGraphic, OutputDevice* pOutDev )
/*N*/ {
/*N*/ 	const MapMode aMapTwip( MAP_TWIP );
/*N*/  	Size aSize( rGraphic.GetPrefSize() );
/*N*/ 	if( MAP_PIXEL == rGraphic.GetPrefMapMode().GetMapUnit() )
/*N*/ 	{
/*N*/ 		if( !pOutDev )
/*N*/ 			pOutDev = Application::GetDefaultDevice();
/*N*/ 		aSize = pOutDev->PixelToLogic( aSize, aMapTwip );
/*N*/ 	}
/*N*/ 	else
/*N*/ 		aSize = OutputDevice::LogicToLogic( aSize,
/*N*/ 										rGraphic.GetPrefMapMode(), aMapTwip );
/*N*/ 	return aSize;
/*N*/ }


/*N*/ Locale CreateLocale( LanguageType eLanguage )
/*N*/ {
/*?*/ 			DBG_BF_ASSERT(0, "STRIP"); Locale temp; return temp;//STRIP001 	String aLangStr, aCtryStr;
//STRIP001 	if (LANGUAGE_NONE != eLanguage)
//STRIP001 		ConvertLanguageToIsoNames( eLanguage, aLangStr, aCtryStr );
//STRIP001 
//STRIP001 /*?*/ 	return Locale( aLangStr, aCtryStr, ::rtl::OUString() );
/*N*/ }


/*N*/ Reference< XSpellChecker1 >  GetSpellChecker()
/*N*/ {
/*N*/ 	return LinguMgr::GetSpellChecker();
/*N*/ }


/*N*/ Reference< XHyphenator >  GetHyphenator()
/*N*/ {
/*N*/ 	return LinguMgr::GetHyphenator();
/*N*/ }


/*N*/ Reference< XThesaurus >  GetThesaurus()
/*N*/ {
/*N*/ 	return LinguMgr::GetThesaurus();
/*N*/ }


/*N*/ Reference< XDictionaryList >  GetDictionaryList()
/*N*/ {
/*N*/ 	return LinguMgr::GetDictionaryList();
/*N*/ }


//STRIP001 Reference< beans::XPropertySet > 	GetLinguPropertySet()
//STRIP001 {
//STRIP001 	return LinguMgr::GetLinguPropertySet();
//STRIP001 }


}
