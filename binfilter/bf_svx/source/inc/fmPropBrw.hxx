/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: fmPropBrw.hxx,v $
 *
 *  $Revision: 1.4 $
 *
 *  last change: $Author: rt $ $Date: 2005-09-08 06:00:06 $
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
#ifndef SVX_FMPROPBRW_HXX
#define SVX_FMPROPBRW_HXX

// auto strip #ifndef _COM_SUN_STAR_LANG_XMULTISERVICEFACTORY_HPP_
// auto strip #include <com/sun/star/lang/XMultiServiceFactory.hpp>
// auto strip #endif
// auto strip #ifndef _COM_SUN_STAR_BEANS_XPROPERTYSET_HPP_
// auto strip #include <com/sun/star/beans/XPropertySet.hpp>
// auto strip #endif
#ifndef _COM_SUN_STAR_AWT_XCONTROLCONTAINER_HPP_ 
#include <com/sun/star/awt/XControlContainer.hpp>
#endif
// auto strip #ifndef _COM_SUN_STAR_FRAME_XFRAME_HPP_
// auto strip #include <com/sun/star/frame/XFrame.hpp>
// auto strip #endif
// auto strip #ifndef _BASEDLGS_HXX
// auto strip #include <bf_sfx2/basedlgs.hxx>
// auto strip #endif
// auto strip #ifndef _SFXCTRLITEM_HXX
// auto strip #include <bf_sfx2/ctrlitem.hxx>
// auto strip #endif
#ifndef _SFX_CHILDWIN_HXX 
#include <bf_sfx2/childwin.hxx>
#endif
namespace binfilter {

//========================================================================
class FmPropBrwMgr : public SfxChildWindow
{
protected:
    ::com::sun::star::uno::Reference< ::com::sun::star::awt::XControlContainer >
                    m_xUnoRepresentation;
public:
    FmPropBrwMgr(Window *pParent, sal_uInt16 nId, SfxBindings *pBindings, SfxChildWinInfo *pInfo);
    SFX_DECL_CHILDWINDOW(FmPropBrwMgr);
};

class FmPropControl;
class SfxBindings;
//========================================================================
//STRIP001 class FmPropBrw : public SfxFloatingWindow, public SfxControllerItem
//STRIP001 {
//STRIP001 	sal_Bool		m_bInitialStateChange;
//STRIP001 
//STRIP001 	::com::sun::star::uno::Reference< ::com::sun::star::lang::XMultiServiceFactory >
//STRIP001 					m_xORB;
//STRIP001 	::com::sun::star::uno::Reference< ::com::sun::star::frame::XFrame >
//STRIP001 					m_xMeAsFrame;
//STRIP001 	::com::sun::star::uno::Reference< ::com::sun::star::beans::XPropertySet >
//STRIP001 					m_xBrowserController;
//STRIP001 	::com::sun::star::uno::Reference< ::com::sun::star::awt::XWindow >
//STRIP001 					m_xBrowserComponentWindow;
//STRIP001 
//STRIP001 protected:
//STRIP001 	virtual void StateChanged(sal_uInt16 nSID, SfxItemState eState, const SfxPoolItem* pState);
//STRIP001 	virtual void FillInfo( SfxChildWinInfo& rInfo ) const;
//STRIP001 	virtual sal_Bool Close();
//STRIP001 
//STRIP001 	DECL_LINK( OnAsyncGetFocus, void* );
//STRIP001 
//STRIP001 	void implSetNewObject(
//STRIP001 		const ::com::sun::star::uno::Reference< ::com::sun::star::beans::XPropertySet >& _rxObject);
//STRIP001 	void implDetachController();
//STRIP001 
//STRIP001 public:
//STRIP001 	FmPropBrw(const ::com::sun::star::uno::Reference< ::com::sun::star::lang::XMultiServiceFactory >&	_xORB,
//STRIP001 			  SfxBindings *pBindings, SfxChildWindow *pMgr, Window* pParent);
//STRIP001 	virtual ~FmPropBrw();
//STRIP001 };
}//end of namespace binfilter
#endif //SVX_FMPROPBRW_HXX
