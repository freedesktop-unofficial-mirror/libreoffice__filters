/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: appuno.hxx,v $
 *
 *  $Revision: 1.5 $
 *
 *  last change: $Author: obo $ $Date: 2007-07-17 12:32:55 $
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
#ifndef _SFX_APPUNO_HXX
#define _SFX_APPUNO_HXX

//____________________________________________________________________________________________________________________________________
//	generated header
//____________________________________________________________________________________________________________________________________

#ifndef _COM_SUN_STAR_FRAME_XFRAME_HPP_
#include <com/sun/star/frame/XFrame.hpp>
#endif

#ifndef _COM_SUN_STAR_LANG_XMULTISERVICEFACTORY_HPP_
#include <com/sun/star/lang/XMultiServiceFactory.hpp>
#endif

#ifndef _COM_SUN_STAR_LANG_XSERVICEINFO_HPP_
#include <com/sun/star/lang/XServiceInfo.hpp>
#endif

#ifndef _COM_SUN_STAR_LANG_XINITIALIZATION_HPP_
#include <com/sun/star/lang/XInitialization.hpp>
#endif

#ifndef _COM_SUN_STAR_LANG_XTYPEPROVIDER_HPP_
#include <com/sun/star/lang/XTypeProvider.hpp>
#endif

#ifndef _COM_SUN_STAR_REGISTRY_XSIMPLEREGISTRY_HPP_
#include <com/sun/star/registry/XSimpleRegistry.hpp>
#endif

#ifndef _COM_SUN_STAR_BEANS_PROPERTYVALUE_HPP_
#include <com/sun/star/beans/PropertyValue.hpp>
#endif

#ifndef _COM_SUN_STAR_UTIL_URL_HPP_
#include <com/sun/star/util/URL.hpp>
#endif

#ifndef _COM_SUN_STAR_UNO_EXCEPTION_HPP_
#include <com/sun/star/uno/Exception.hpp>
#endif

#ifndef _COM_SUN_STAR_FRAME_XDISPATCHPROVIDER_HPP_
#include <com/sun/star/frame/XDispatchProvider.hpp>
#endif

#ifndef _COM_SUN_STAR_FRAME_XDISPATCH_HPP_
#include <com/sun/star/frame/XDispatch.hpp>
#endif

#ifndef _COM_SUN_STAR_FRAME_XSYNCHRONOUSDISPATCH_HPP_
#include <com/sun/star/frame/XSynchronousDispatch.hpp>
#endif

#ifndef _COM_SUN_STAR_FRAME_XNOTIFYINGDISPATCH_HPP_
#include <com/sun/star/frame/XNotifyingDispatch.hpp>
#endif

#ifndef _COM_SUN_STAR_FRAME_XDISPATCHRESULTLISTENER_HPP_
#include <com/sun/star/frame/XDispatchResultListener.hpp>
#endif

#ifndef _COM_SUN_STAR_FRAME_DISPATCHDESCRIPTOR_HPP_
#include <com/sun/star/frame/DispatchDescriptor.hpp>
#endif

#ifndef _COM_SUN_STAR_LANG_XMULTISERVICEFACTORY_HPP_
#include <com/sun/star/lang/XMultiServiceFactory.hpp>
#endif

//____________________________________________________________________________________________________________________________________
//	fix uno header
//____________________________________________________________________________________________________________________________________

#ifndef _COM_SUN_STAR_UNO_ANY_H_
#include <com/sun/star/uno/Any.h>
#endif

#ifndef _COM_SUN_STAR_UNO_REFERENCE_H_
#include <com/sun/star/uno/Reference.h>
#endif

#ifndef _COM_SUN_STAR_UNO_SEQUENCE_HXX_
#include <com/sun/star/uno/Sequence.hxx>
#endif

#ifndef _CPPUHELPER_WEAK_HXX_
#include <cppuhelper/weak.hxx>
#endif

#ifndef _CPPUHELPER_IMPLBASE3_HXX_
#include <cppuhelper/implbase3.hxx>
#endif

//____________________________________________________________________________________________________________________________________
//	something else header
//____________________________________________________________________________________________________________________________________

#ifndef _ERRCODE_HXX
#include <tools/errcode.hxx>
#endif
#include <svtools/svarray.hxx>
#define _SVSTDARR_STRINGSDTOR
#include <svtools/svstdarr.hxx>
#include <bf_sfx2/sfxuno.hxx>

#include <svtools/poolitem.hxx>

class SfxAllItemSet;
class SfxItemSet;

namespace binfilter {

class SfxUsrAnyItem : public SfxPoolItem
{
    ::com::sun::star::uno::Any  aValue;
public:
                                TYPEINFO();
                                SfxUsrAnyItem( sal_uInt16 nWhich, const ::com::sun::star::uno::Any& rAny );
    ::com::sun::star::uno::Any  GetValue() const
                                { return aValue; }
    virtual int                 operator==( const SfxPoolItem& ) const;
    virtual String              GetValueText() const{DBG_BF_ASSERT(0, "STRIP"); return String();} //STRIP001 virtual String              GetValueText() const;
    virtual SfxPoolItem*        Clone( SfxItemPool *pPool = 0 ) const;
};

typedef SfxUsrAnyItem SfxUnoAnyItem;

void TransformParameters(           sal_uInt16                          nSlotId     ,
                            const	UNOSEQUENCE< UNOPROPERTYVALUE >&	seqArgs		,
                                    SfxAllItemSet&						aSet	);

void TransformItems(        sal_uInt16                          nSlotId     ,
                            const	SfxItemSet&							aSet		,
                                    UNOSEQUENCE< UNOPROPERTYVALUE >&	seqArgs	 );


}//end of namespace binfilter
#endif
