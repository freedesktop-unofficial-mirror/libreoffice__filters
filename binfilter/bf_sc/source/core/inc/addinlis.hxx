/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: addinlis.hxx,v $
 *
 *  $Revision: 1.3 $
 *
 *  last change: $Author: rt $ $Date: 2005-09-07 16:56:12 $
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

#ifndef SC_ADDINLIS_HXX
#define SC_ADDINLIS_HXX

#ifndef _SC_ADIASYNC_HXX
#include "adiasync.hxx"			// for ScAddInDocs PtrArr
#endif

#ifndef _COM_SUN_STAR_SHEET_XRESULTLISTENER_HPP_
#include <com/sun/star/sheet/XResultListener.hpp>
#endif

#ifndef _COM_SUN_STAR_SHEET_XVOLATILERESULT_HPP_
#include <com/sun/star/sheet/XVolatileResult.hpp>
#endif

#ifndef _COM_SUN_STAR_LANG_XSERVICEINFO_HPP_
#include <com/sun/star/lang/XServiceInfo.hpp>
#endif

#ifndef _CPPUHELPER_IMPLBASE2_HXX_
#include <cppuhelper/implbase2.hxx>
#endif
namespace binfilter {



class ScDocument;


class ScAddInListener : public cppu::WeakImplHelper2<
                            ::com::sun::star::sheet::XResultListener,
                            ::com::sun::star::lang::XServiceInfo >,
                        public SfxBroadcaster
{
private:
    ::com::sun::star::uno::Reference< ::com::sun::star::sheet::XVolatileResult> xVolRes;
    ::com::sun::star::uno::Any	aResult;
    ScAddInDocs*				pDocs;			// documents where this is used

    static List					aAllListeners;

                            // always allocated via CreateListener
                            ScAddInListener(
                                ::com::sun::star::uno::Reference<
                                    ::com::sun::star::sheet::XVolatileResult> xVR,
                                ScDocument* pD );

public:
    virtual					~ScAddInListener();

                            // create Listener and put it into global list
    static ScAddInListener*	CreateListener(
                                ::com::sun::star::uno::Reference<
                                    ::com::sun::star::sheet::XVolatileResult> xVR,
                                ScDocument* pDoc );

    static ScAddInListener*	Get( ::com::sun::star::uno::Reference<
                                    ::com::sun::star::sheet::XVolatileResult> xVR );
    static void				RemoveDocument( ScDocument* pDocument );

    BOOL					HasDocument( ScDocument* pDoc ) const	{ return pDocs->Seek_Entry( pDoc ); }
    void					AddDocument( ScDocument* pDoc )			{ pDocs->Insert( pDoc ); }
    const ::com::sun::star::uno::Any& GetResult() const				{ return aResult; }


                            // XResultListener
    virtual void SAL_CALL	modified( const ::com::sun::star::sheet::ResultEvent& aEvent )
                                throw(::com::sun::star::uno::RuntimeException);

                            // XEventListener
    virtual void SAL_CALL	disposing( const ::com::sun::star::lang::EventObject& Source )
                                throw(::com::sun::star::uno::RuntimeException);

                            // XServiceInfo
    virtual ::rtl::OUString SAL_CALL getImplementationName(  )
                                throw(::com::sun::star::uno::RuntimeException);
    virtual sal_Bool SAL_CALL supportsService( const ::rtl::OUString& ServiceName )
                                throw(::com::sun::star::uno::RuntimeException);
    virtual ::com::sun::star::uno::Sequence< ::rtl::OUString > SAL_CALL getSupportedServiceNames(  )
                                throw(::com::sun::star::uno::RuntimeException);
};


} //namespace binfilter
#endif

