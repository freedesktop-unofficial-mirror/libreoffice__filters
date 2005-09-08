/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: UnoNameItemTable.hxx,v $
 *
 *  $Revision: 1.4 $
 *
 *  last change: $Author: rt $ $Date: 2005-09-08 07:20:05 $
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

#ifndef _SVX_UNONAMEITEMTABLE_HXX_
#define _SVX_UNONAMEITEMTABLE_HXX_

#ifndef _COM_SUN_STAR_LANG_XSERVICEINFO_HPP_
#include <com/sun/star/lang/XServiceInfo.hpp>
#endif
#ifndef _COM_SUN_STAR_CONTAINER_XNAMECONTAINER_HPP_
#include <com/sun/star/container/XNameContainer.hpp>
#endif

#include <cppuhelper/implbase2.hxx>

#include <vector>

#ifndef _SFXLSTNER_HXX 
#include <svtools/lstner.hxx>
#endif

#ifndef _SVX_XIT_HXX
#include "xit.hxx"
#endif

// auto strip #include "xdef.hxx"
class SfxItemPool;
class SfxItemSet;
namespace binfilter {

class SdrModel;

typedef std::vector< SfxItemSet* > ItemPoolVector;
class SvxUnoNameItemTable : public cppu::WeakImplHelper2< ::com::sun::star::container::XNameContainer, ::com::sun::star::lang::XServiceInfo >,
                            public SfxListener
{
private:
    SdrModel*		mpModel;
    SfxItemPool*	mpModelPool;
    USHORT			mnWhich;
    BYTE			mnMemberId;

    ItemPoolVector maItemSetVector;

    void SAL_CALL ImplInsertByName( const ::rtl::OUString& aName, const ::com::sun::star::uno::Any& aElement );

public:
    SvxUnoNameItemTable( SdrModel* pModel, USHORT nWhich, BYTE nMemberId = 0 ) throw();
    virtual	~SvxUnoNameItemTable() throw();

    virtual NameOrIndex* createItem() const throw() = 0;
    void dispose();

    // SfxListener
    virtual void Notify( SfxBroadcaster& rBC, const SfxHint& rHint ) throw ();

    // XServiceInfo
    virtual sal_Bool SAL_CALL supportsService( const  ::rtl::OUString& ServiceName ) throw( ::com::sun::star::uno::RuntimeException);

    // XNameContainer
    virtual void SAL_CALL insertByName( const  ::rtl::OUString& aName, const  ::com::sun::star::uno::Any& aElement ) throw( ::com::sun::star::lang::IllegalArgumentException, ::com::sun::star::container::ElementExistException, ::com::sun::star::lang::WrappedTargetException, ::com::sun::star::uno::RuntimeException);
    virtual void SAL_CALL removeByName( const  ::rtl::OUString& Name ) throw( ::com::sun::star::container::NoSuchElementException, ::com::sun::star::lang::WrappedTargetException, ::com::sun::star::uno::RuntimeException);

    // XNameReplace
    virtual void SAL_CALL replaceByName( const  ::rtl::OUString& aName, const  ::com::sun::star::uno::Any& aElement ) throw( ::com::sun::star::lang::IllegalArgumentException, ::com::sun::star::container::NoSuchElementException, ::com::sun::star::lang::WrappedTargetException, ::com::sun::star::uno::RuntimeException);

    // XNameAccess
    virtual ::com::sun::star::uno::Any SAL_CALL getByName( const  ::rtl::OUString& aName ) throw( ::com::sun::star::container::NoSuchElementException, ::com::sun::star::lang::WrappedTargetException, ::com::sun::star::uno::RuntimeException);
    virtual ::com::sun::star::uno::Sequence<  ::rtl::OUString > SAL_CALL getElementNames(  ) throw( ::com::sun::star::uno::RuntimeException);
    virtual sal_Bool SAL_CALL hasByName( const  ::rtl::OUString& aName ) throw( ::com::sun::star::uno::RuntimeException);

    // XElementAccess
    virtual sal_Bool SAL_CALL hasElements(  ) throw( ::com::sun::star::uno::RuntimeException);
};

}//end of namespace binfilter
#endif // _SVX_UNONAMEITEMTABLE_HXX_
