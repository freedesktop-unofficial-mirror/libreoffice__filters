/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: svx_unontabl.cxx,v $
 *
 *  $Revision: 1.3 $
 *
 *  last change: $Author: rt $ $Date: 2005-09-08 07:27:27 $
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

#ifndef _COM_SUN_STAR_LANG_XSERVICEINFO_HPP_
#include <com/sun/star/lang/XServiceInfo.hpp>
#endif
#ifndef _COM_SUN_STAR_CONTAINER_XNAMECONTAINER_HPP_
#include <com/sun/star/container/XNameContainer.hpp>
#endif
#include <cppuhelper/implbase2.hxx>

#ifndef _SFXITEMPOOL_HXX
#include <svtools/itempool.hxx>
#endif

#ifndef _SFXITEMSET_HXX //autogen
#include <svtools/itemset.hxx>
#endif

#ifndef _SVARRAY_HXX 
#include <svtools/svarray.hxx>
#endif

#include "eeitem.hxx"
#include "numitem.hxx"
#include "unonrule.hxx"

#include "svdmodel.hxx"
#include "xdef.hxx"
namespace binfilter {

using namespace ::com::sun::star;
using namespace ::rtl;
using namespace ::cppu;

SV_DECL_PTRARR( ItemSetArray_Impl, SfxItemSet*,	5, 5 )

class SvxUnoNumberingRuleTable : public WeakImplHelper2< container::XNameContainer, lang::XServiceInfo >
{
private:
    XGradientList*  mpGradientList;
    SdrModel*		mpModel;
    SfxItemPool*	mpPool;

    ItemSetArray_Impl	aItemSetArray;

    void CreateName( OUString& rStrName);

public:
    SvxUnoNumberingRuleTable( SdrModel* pModel ) throw();
    virtual	~SvxUnoNumberingRuleTable() throw();

    // XServiceInfo
    virtual OUString SAL_CALL getImplementationName(  ) throw( uno::RuntimeException );
    virtual sal_Bool SAL_CALL supportsService( const  OUString& ServiceName ) throw( uno::RuntimeException);
    virtual uno::Sequence<  OUString > SAL_CALL getSupportedServiceNames(  ) throw( uno::RuntimeException);

    static OUString getImplementationName_Static() throw()
    {
        return OUString(RTL_CONSTASCII_USTRINGPARAM("com.sun.star.drawing.SvxUnoNumberingRuleTable"));
    }

    static uno::Sequence< OUString >  getSupportedServiceNames_Static(void) throw();


    // XNameContainer
    virtual void SAL_CALL insertByName( const  OUString& aName, const  uno::Any& aElement ) throw( lang::IllegalArgumentException, container::ElementExistException, lang::WrappedTargetException, uno::RuntimeException);
    virtual void SAL_CALL removeByName( const  OUString& Name ) throw( container::NoSuchElementException, lang::WrappedTargetException, uno::RuntimeException);

    // XNameReplace
    virtual void SAL_CALL replaceByName( const  OUString& aName, const  uno::Any& aElement ) throw( lang::IllegalArgumentException, container::NoSuchElementException, lang::WrappedTargetException, uno::RuntimeException);

    // XNameAccess
    virtual uno::Any SAL_CALL getByName( const  OUString& aName ) throw( container::NoSuchElementException, lang::WrappedTargetException, uno::RuntimeException);
    virtual uno::Sequence<  OUString > SAL_CALL getElementNames(  ) throw( uno::RuntimeException);
    virtual sal_Bool SAL_CALL hasByName( const  OUString& aName ) throw( uno::RuntimeException);

    // XElementAccess
    virtual uno::Type SAL_CALL getElementType(  ) throw( uno::RuntimeException);
    virtual sal_Bool SAL_CALL hasElements(  ) throw( uno::RuntimeException);
};

SvxUnoNumberingRuleTable::SvxUnoNumberingRuleTable( SdrModel* pModel ) throw()
: mpModel( pModel ), mpPool( pModel ? &pModel->GetItemPool() : (SfxItemPool*)NULL )
{
}

SvxUnoNumberingRuleTable::~SvxUnoNumberingRuleTable() throw()
{
    for( int i = 0; i<aItemSetArray.Count(); i++ )
        delete (SfxItemSet*)aItemSetArray.GetObject( i );
}

sal_Bool SAL_CALL SvxUnoNumberingRuleTable::supportsService( const OUString& ServiceName ) throw(uno::RuntimeException)
{
    uno::Sequence< OUString > aSNL( getSupportedServiceNames() );
    const OUString * pArray = aSNL.getConstArray();

    for( INT32 i = 0; i < aSNL.getLength(); i++ )
        if( pArray[i] == ServiceName )
            return sal_True;

    return sal_False;
}

OUString SAL_CALL SvxUnoNumberingRuleTable::getImplementationName() throw( uno::RuntimeException )
{
    return getImplementationName_Static();
}

uno::Sequence< OUString > SAL_CALL SvxUnoNumberingRuleTable::getSupportedServiceNames(  )
    throw( uno::RuntimeException )
{
    return getSupportedServiceNames_Static();
}

uno::Sequence< OUString > SvxUnoNumberingRuleTable::getSupportedServiceNames_Static(void) throw()
{
    uno::Sequence< OUString > aSNS( 1 );
    aSNS.getArray()[0] = OUString( RTL_CONSTASCII_USTRINGPARAM("com.sun.star.text.NumberingRulesTable" ));
    return aSNS;
}


// XNameContainer
void SAL_CALL SvxUnoNumberingRuleTable::insertByName( const OUString& aName, const uno::Any& aElement )
    throw( lang::IllegalArgumentException, container::ElementExistException, lang::WrappedTargetException, uno::RuntimeException )
{
    SfxItemSet* mpInSet = new SfxItemSet( *mpPool, EE_PARA_NUMBULLET, EE_PARA_NUMBULLET );
    aItemSetArray.C40_INSERT( ItemSetArray_Impl, mpInSet, aItemSetArray.Count() );

    uno::Reference< container::XIndexReplace > xNumRule;
    if(aElement >>= xNumRule)
    {
        SvxUnoNumberingRules *pNumRules = SvxUnoNumberingRules::getImplementation( xNumRule );

        if( pNumRules )
        {
            mpInSet->Put( *(pNumRules->GetNumBulletItem()), EE_PARA_NUMBULLET );
            return;
        }
    }

    throw lang::IllegalArgumentException();
}



void SAL_CALL SvxUnoNumberingRuleTable::removeByName( const OUString& Name )
    throw( container::NoSuchElementException, lang::WrappedTargetException, uno::RuntimeException)
{
    /* Currently, don't know how to do this ?
    long nIndex = pTable ? ((XPropertyTable*)pTable)->Get( Name ) : -1;
    if( nIndex == -1 )
        throw container::NoSuchElementException();

    pTable->Remove( nIndex );
    */
}

// XNameReplace
void SAL_CALL SvxUnoNumberingRuleTable::replaceByName( const OUString& aName, const uno::Any& aElement )
    throw( lang::IllegalArgumentException, container::NoSuchElementException, lang::WrappedTargetException, uno::RuntimeException )
{
    /* Currently, don't know how to do this ?
    INT32 nColor;
    if( aElement >>= nColor )
        throw lang::IllegalArgumentException();

    long nIndex = pTable ? ((XPropertyTable*)pTable)->Get( aName ) : -1;
    if( nIndex == -1  )
        throw container::NoSuchElementException();

    XColorEntry* pEntry = new XColorEntry( Color( (ColorData)nColor ), aName );
    delete pTable->Replace( nIndex, pEntry );
    */
}

SvxNumBulletItem* SvxGetNumBulletItemByName( SfxItemPool* pPool, const OUString& aName ) throw()
{
    if( pPool )
    {
        const USHORT nCount = pPool->GetItemCount(EE_PARA_NUMBULLET);
        SvxNumBulletItem *pItem = NULL, *pSearchItem;

        for( USHORT nSurrogate = 0; nSurrogate < nCount; nSurrogate++ )
        {
            pSearchItem = (SvxNumBulletItem*)pPool->GetItem(EE_PARA_NUMBULLET, nSurrogate);

            if( pSearchItem && pSearchItem->GetNumRule() && pSearchItem->GetNumRule()->GetLevelCount() && ( pSearchItem->getName() == aName ) )
            {
                return pSearchItem;
            }
        }
    }

    return NULL;
}

// XNameAccess
uno::Any SAL_CALL SvxUnoNumberingRuleTable::getByName( const  OUString& aName )
    throw( container::NoSuchElementException,  lang::WrappedTargetException, uno::RuntimeException)
{
    uno::Any aAny;

    SvxNumBulletItem *pItem = SvxGetNumBulletItemByName( mpPool, aName );
    if( pItem == NULL )
        throw container::NoSuchElementException();

    aAny <<= pItem->getUnoNumRule();
    return aAny;
}

uno::Sequence< OUString > SAL_CALL SvxUnoNumberingRuleTable::getElementNames(  )
    throw( uno::RuntimeException )
{
    const USHORT nCount = mpPool ? mpPool->GetItemCount(EE_PARA_NUMBULLET) : 0;
    uno::Sequence< OUString > aSeq( nCount );
    OUString* pStrings = aSeq.getArray();
    SvxNumBulletItem *pItem;

    USHORT nRealCount = 0;

    for( USHORT nSurrogate = 0; nSurrogate < nCount; nSurrogate++ )
    {
        pItem = (SvxNumBulletItem*)mpPool->GetItem(EE_PARA_NUMBULLET, nSurrogate);

        if( pItem && pItem->GetNumRule() && pItem->GetNumRule()->GetLevelCount() )
        {
            *pStrings = pItem->getName();
        
            if( !(*pStrings).getLength() )
            {
                CreateName( *pStrings );
                pItem->setName( String( *pStrings ) );
            }

            pStrings++;
            nRealCount++;
        }
    }

    if( nRealCount != nCount )
        aSeq.realloc( nRealCount );

    return aSeq;
}

sal_Bool SAL_CALL SvxUnoNumberingRuleTable::hasByName( const OUString& aName )
    throw( uno::RuntimeException )
{
    const USHORT nCount = mpPool ? mpPool->GetItemCount(EE_PARA_NUMBULLET) : 0;
    uno::Sequence< OUString > aSeq( nCount );
    OUString* pStrings = aSeq.getArray();
    const SvxNumBulletItem *pItem;

    for( USHORT nSurrogate = 0; nSurrogate < nCount; nSurrogate++ )
    {
        pItem = (SvxNumBulletItem*)mpPool->GetItem(EE_PARA_NUMBULLET, nSurrogate);
        if( pItem && pItem->GetNumRule() && pItem->GetNumRule()->GetLevelCount() && pItem->getName() == aName )
            return sal_True;
    }

    return sal_False;
}

// XElementAccess
uno::Type SAL_CALL SvxUnoNumberingRuleTable::getElementType(  )
    throw( uno::RuntimeException )
{
    return ::getCppuType((const uno::Reference< container::XIndexAccess >*)0);
}

sal_Bool SAL_CALL SvxUnoNumberingRuleTable::hasElements(  )
    throw( uno::RuntimeException )
{
    return mpPool && mpPool->GetItemCount(EE_PARA_NUMBULLET) != 0;
}

void SvxUnoNumberingRuleTable::CreateName( OUString& rStrName)
{
    const USHORT nCount = mpPool ? mpPool->GetItemCount(EE_PARA_NUMBULLET) : 0;
    sal_Bool bFound = sal_True;

    for( sal_Int32 nPostfix = 1; nPostfix<= nCount && bFound; nPostfix++ )
    {
        rStrName = OUString::createFromAscii( "Standard " );
        rStrName += OUString::valueOf( nPostfix );
        bFound = hasByName( rStrName );
    }
}

/**
 * Create a numbering rule table
 */
uno::Reference< uno::XInterface > SAL_CALL SvxUnoNumberingRuleTable_createInstance( SdrModel* pModel )
{
    return *new SvxUnoNumberingRuleTable(pModel);
}

}
