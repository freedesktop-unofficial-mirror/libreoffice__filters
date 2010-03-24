/*************************************************************************
 *
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER.
 *
 * Copyright 2000, 2010 Oracle and/or its affiliates.
 *
 * OpenOffice.org - a multi-platform office productivity suite
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

#ifndef _SV_STATUS_HXX
#include <vcl/status.hxx>
#endif
#ifndef _SV_MSGBOX_HXX
#include <vcl/msgbox.hxx>
#endif
#ifndef _VOS_PROCESS_HXX //autogen
#include <vos/process.hxx>
#endif
#ifndef _XCEPTION_HXX_
#include <vos/xception.hxx>
#endif
#ifndef _SFX_WHITER_HXX //autogen
#include <bf_svtools/whiter.hxx>
#endif
#ifndef _SFXSTRITEM_HXX //autogen
#include <bf_svtools/stritem.hxx>
#endif
#ifndef _SFXINTITEM_HXX //autogen
#include <bf_svtools/intitem.hxx>
#endif
#ifndef _SFXENUMITEM_HXX //autogen
#include <bf_svtools/eitem.hxx>
#endif
#ifndef _FILTER_HXX //autogen
#include <bf_svtools/filter.hxx>
#endif
#ifndef INCLUDED_SVTOOLS_INTERNALOPTIONS_HXX
#include <bf_svtools/internaloptions.hxx>
#endif
#ifndef INCLUDED_SVTOOLS_PATHOPTIONS_HXX
#include <bf_svtools/pathoptions.hxx>
#endif

#ifndef _COM_SUN_STAR_REGISTRY_INVALIDREGISTRYEXCEPTION_HPP_
#include <com/sun/star/registry/InvalidRegistryException.hpp>
#endif
#ifndef _COM_SUN_STAR_BEANS_PropertyValue_HPP_
#include <com/sun/star/beans/PropertyValue.hpp>
#endif
#ifndef _COM_SUN_STAR_FRAME_XFRAME_HPP_
#include <com/sun/star/frame/XFrame.hpp>
#endif
#ifndef _COM_SUN_STAR_UTIL_XURLTRANSFORMER_HPP_
#include <com/sun/star/util/XURLTransformer.hpp>
#endif
#ifndef _COM_SUN_STAR_FRAME_XFRAMESSUPPLIER_HPP_
#include <com/sun/star/frame/XFramesSupplier.hpp>
#endif
#ifndef _COM_SUN_STAR_UNO_REFERENCE_H_
#include <com/sun/star/uno/Reference.h>
#endif
#ifndef _CONFIG_HXX
#include <tools/config.hxx>
#endif
#include <tools/rcid.h>
#include <vos/mutex.hxx>
#ifdef _MSC_VER
#pragma hdrstop
#endif
#ifndef _UTL_CONFIGMGR_HXX_
#include <unotools/configmgr.hxx>
#endif
#ifndef _COM_SUN_STAR_FRAME_XDESKTOP_HPP_
#include <com/sun/star/frame/XDesktop.hpp>
#endif

#include <unotools/ucbstreamhelper.hxx>
#include <framework/menuconfiguration.hxx>
#include <comphelper/processfactory.hxx>
#include <unotools/localfilehelper.hxx>
#include <unotools/bootstrap.hxx>
#include <bf_svtools/moduleoptions.hxx>
#include <osl/file.hxx>

#include "app.hxx"
#include "appdata.hxx"
#include "cfgmgr.hxx"

#ifndef _SVTOOLS_IMGDEF_HXX
#include <bf_svtools/imgdef.hxx>
#endif

#include "docfac.hxx"
#include "docfile.hxx"
#include "docfilt.hxx"
#include "request.hxx"
#include "fcontnr.hxx"
#include "sfx.hrc"
#include "module.hxx"
#include "openflag.hxx"
#include "appimp.hxx"
#include "helper.hxx"	// SfxContentHelper::Kill()

#ifndef _LEGACYBINFILTERMGR_HXX
#include <legacysmgr/legacy_binfilters_smgr.hxx>	//STRIP002 
#endif

using namespace ::vos;
using namespace ::com::sun::star::uno;
using namespace ::com::sun::star::util;
using namespace ::com::sun::star::beans;
using namespace ::com::sun::star::container;

//===================================================================
namespace binfilter {


/*N*/ SfxProgress* SfxApplication::GetProgress() const
/*N*/ {
/*N*/     return pAppData_Impl->pProgress;
/*N*/ }

/*N*/ SfxCancelManager *SfxApplication::GetCancelManager() const
/*N*/ {
/*N*/ 	if ( !pAppData_Impl->pCancelMgr )
/*N*/ 	{
/*N*/ 		pAppData_Impl->pCancelMgr = new SfxCancelManager;
/*N*/ 	}
/*N*/ 	return pAppData_Impl->pCancelMgr;
/*N*/ }

}
