/*************************************************************************
 *
 *  $RCSfile: sd_unogstyl.cxx,v $
 *
 *  $Revision: 1.2 $
 *
 *  last change: $Author: mwu $ $Date: 2003-11-06 07:36:50 $
 *
 *  The Contents of this file are made available subject to the terms of
 *  either of the following licenses
 *
 *         - GNU Lesser General Public License Version 2.1
 *         - Sun Industry Standards Source License Version 1.1
 *
 *  Sun Microsystems Inc., October, 2000
 *
 *  GNU Lesser General Public License Version 2.1
 *  =============================================
 *  Copyright 2000 by Sun Microsystems, Inc.
 *  901 San Antonio Road, Palo Alto, CA 94303, USA
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public
 *  License version 2.1, as published by the Free Software Foundation.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public
 *  License along with this library; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 *  MA  02111-1307  USA
 *
 *
 *  Sun Industry Standards Source License Version 1.1
 *  =================================================
 *  The contents of this file are subject to the Sun Industry Standards
 *  Source License Version 1.1 (the "License"); You may not use this file
 *  except in compliance with the License. You may obtain a copy of the
 *  License at http://www.openoffice.org/license.html.
 *
 *  Software provided under this License is provided on an "AS IS" basis,
 *  WITHOUT WARRANTY OF ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING,
 *  WITHOUT LIMITATION, WARRANTIES THAT THE SOFTWARE IS FREE OF DEFECTS,
 *  MERCHANTABLE, FIT FOR A PARTICULAR PURPOSE, OR NON-INFRINGING.
 *  See the License for the specific provisions governing your rights and
 *  obligations concerning the Software.
 *
 *  The Initial Developer of the Original Code is: Sun Microsystems, Inc.
 *
 *  Copyright: 2000 by Sun Microsystems, Inc.
 *
 *  All Rights Reserved.
 *
 *  Contributor(s): _______________________________________
 *
 *
 ************************************************************************/

#ifndef _VOS_MUTEX_HXX_ //autogen
#include <vos/mutex.hxx>
#endif

#ifndef _SV_SVAPP_HXX
#include <vcl/svapp.hxx>
#endif

#ifndef _SFXSTYLE_HXX
#include <svtools/style.hxx>
#endif

#ifndef _SFX_ITEMPROP_HXX
#include <svtools/itemprop.hxx>
#endif

#ifndef _SD_STLSHEET_HXX
#include "stlsheet.hxx"
#endif
#ifndef _SFXSMPLHINT_HXX
#include <svtools/smplhint.hxx>
#endif

#include <comphelper/extract.hxx>
#include <rtl/uuid.h>
#include <rtl/memory.h>

#include <bf_svx/unoprov.hxx>

#include <unohelp.hxx>
#include <unogsfm.hxx>
#include <unogstyl.hxx>
#include <unokywds.hxx>
#include <unomodel.hxx>
#include <helpids.h>
#include <unoprnms.hxx>
namespace binfilter {

using namespace ::rtl;
using namespace ::vos;
using namespace ::com::sun::star;

SdUnoGraphicStyle::SdUnoGraphicStyle( SdXImpressDocument* pModel /* = NULL */, 
                                      SfxStyleSheetBase* pStyleSheet /* = NULL */ ) throw()
: SdUnoPseudoStyle( pModel, pStyleSheet )
{
}

SdUnoGraphicStyle::~SdUnoGraphicStyle() throw()
{
}

const ::com::sun::star::uno::Sequence< sal_Int8 > & SdUnoGraphicStyle::getUnoTunnelId() throw()
{
    static ::com::sun::star::uno::Sequence< sal_Int8 > * pSeq = 0;
    if( !pSeq )
    {
        ::osl::Guard< ::osl::Mutex > aGuard( ::osl::Mutex::getGlobalMutex() );
        if( !pSeq )
        {
            static ::com::sun::star::uno::Sequence< sal_Int8 > aSeq( 16 );
            rtl_createUuid( (sal_uInt8*)aSeq.getArray(), 0, sal_True );
            pSeq = &aSeq;
        }
    }
    return *pSeq;
}

SdUnoGraphicStyle* SdUnoGraphicStyle::getImplementation( uno::Reference< uno::XInterface > xInt ) throw()
{
    ::com::sun::star::uno::Reference< ::com::sun::star::lang::XUnoTunnel > xUT( xInt, ::com::sun::star::uno::UNO_QUERY );
    if( xUT.is() )
        return (SdUnoGraphicStyle*)xUT->getSomething( SdUnoGraphicStyle::getUnoTunnelId() );
    else
        return NULL;
}

sal_Int64 SAL_CALL SdUnoGraphicStyle::getSomething( const ::com::sun::star::uno::Sequence< sal_Int8 >& rId ) throw(::com::sun::star::uno::RuntimeException)
{
    if( rId.getLength() == 16 && 0 == rtl_compareMemory( getUnoTunnelId().getConstArray(), rId.getConstArray(), 16 ) )
    {
        return (sal_Int64)this;
    }
    else
    {
        return SdUnoPseudoStyle::getSomething( rId );
    }
}

/** attaches a style sheet to this instance and fill it with things the user
    already set on this instance
*/
void SdUnoGraphicStyle::create( SdXImpressDocument* pModel, SfxStyleSheetBase* pStyleSheet ) throw()
{
    DBG_ASSERT( pModel != NULL, "where is my model? [CL]" );
    DBG_ASSERT( pStyleSheet != NULL, "where is my style? [CL]" );
    DBG_ASSERT( mpStyleSheet == NULL, "creating already existing style! [CL]" );

    mxModel = pModel;
    mpModel = pModel;

    mpStyleSheet = pStyleSheet;
    StartListening( pStyleSheet->GetPool() );

    if( maPreInitName.getLength() )
        setName( maPreInitName );

    if( maPreInitParent.getLength() )
        setParentStyle( maPreInitParent );

    if( maPropSet.AreThereOwnUsrAnys() )
    {
        uno::Any* pAny;
        const SfxItemPropertyMap* pMap = maPropSet.getPropertyMap();
        while( pMap->pName )
        {
            pAny = maPropSet.GetUsrAnyForID( pMap->nWID );
            if( pAny )
            {
                OUString aPropertyName( OUString::createFromAscii(pMap->pName) );
                setPropertyValue( aPropertyName, *pAny );
            }
            pMap++;
        }
    }
}

// XNamed
OUString SAL_CALL SdUnoGraphicStyle::getName(  )
    throw(uno::RuntimeException)
{
    OGuard aGuard( Application::GetSolarMutex() );

    OUString aName;
    if( mpStyleSheet )
    {
        aName = SdUnoGraphicStyleFamily::getExternalStyleName( mpStyleSheet->GetName() );
    }
    else
    {
        aName = maPreInitName;
    }

    return aName;
}

void SAL_CALL SdUnoGraphicStyle::setName( const OUString& aName )
    throw(uno::RuntimeException)
{
    OGuard aGuard( Application::GetSolarMutex() );

    if( mpStyleSheet )
    {
        if( mpStyleSheet->IsUserDefined() )
        {
            mpStyleSheet->SetName( aName );
            ((SdStyleSheet*)mpStyleSheet)->Broadcast(SfxSimpleHint(SFX_HINT_DATACHANGED));
        }
    }
    else
    {
        maPreInitName = aName;
    }

    if( mpModel )
        mpModel->SetModified();
}

// XPropertySet
uno::Reference< ::com::sun::star::beans::XPropertySetInfo > SAL_CALL SdUnoGraphicStyle::getPropertySetInfo() throw(::com::sun::star::uno::RuntimeException)
{
    return SdUnoPseudoStyle::getPropertySetInfo();
}

void SAL_CALL SdUnoGraphicStyle::setPropertyValue( const ::rtl::OUString& aPropertyName, const ::com::sun::star::uno::Any& aValue ) throw(::com::sun::star::beans::UnknownPropertyException, ::com::sun::star::beans::PropertyVetoException, ::com::sun::star::lang::IllegalArgumentException, ::com::sun::star::lang::WrappedTargetException, ::com::sun::star::uno::RuntimeException)
{
    SdUnoPseudoStyle::setPropertyValue( aPropertyName, aValue );
}

uno::Any SAL_CALL SdUnoGraphicStyle::getPropertyValue( const ::rtl::OUString& PropertyName ) throw(::com::sun::star::beans::UnknownPropertyException, ::com::sun::star::lang::WrappedTargetException, ::com::sun::star::uno::RuntimeException)
{
    static OUString aStyleName( OUString::createFromAscii( UNO_NAME_STYLE_FAMILY ) );
    if( PropertyName == aStyleName )
    {
        uno::Any aAny;
        aAny <<= OUString::createFromAscii( "graphic" );
        return aAny;
    }
    else
    {
        return SdUnoPseudoStyle::getPropertyValue( PropertyName );
    }
}

void SAL_CALL SdUnoGraphicStyle::addPropertyChangeListener( const ::rtl::OUString& aPropertyName, const ::com::sun::star::uno::Reference< ::com::sun::star::beans::XPropertyChangeListener >& xListener ) throw(::com::sun::star::beans::UnknownPropertyException, ::com::sun::star::lang::WrappedTargetException, ::com::sun::star::uno::RuntimeException)
{
    SdUnoPseudoStyle::addPropertyChangeListener( aPropertyName, xListener );
}

void SAL_CALL SdUnoGraphicStyle::removePropertyChangeListener( const ::rtl::OUString& aPropertyName, const ::com::sun::star::uno::Reference< ::com::sun::star::beans::XPropertyChangeListener >& aListener ) throw(::com::sun::star::beans::UnknownPropertyException, ::com::sun::star::lang::WrappedTargetException, ::com::sun::star::uno::RuntimeException)
{
    SdUnoPseudoStyle::removePropertyChangeListener( aPropertyName, aListener );
}

void SAL_CALL SdUnoGraphicStyle::addVetoableChangeListener( const ::rtl::OUString& PropertyName, const ::com::sun::star::uno::Reference< ::com::sun::star::beans::XVetoableChangeListener >& aListener ) throw(::com::sun::star::beans::UnknownPropertyException, ::com::sun::star::lang::WrappedTargetException, ::com::sun::star::uno::RuntimeException)
{
    SdUnoPseudoStyle::addVetoableChangeListener( PropertyName, aListener );
}

void SAL_CALL SdUnoGraphicStyle::removeVetoableChangeListener( const ::rtl::OUString& PropertyName, const ::com::sun::star::uno::Reference< ::com::sun::star::beans::XVetoableChangeListener >& aListener ) throw(::com::sun::star::beans::UnknownPropertyException, ::com::sun::star::lang::WrappedTargetException, ::com::sun::star::uno::RuntimeException)
{
    SdUnoPseudoStyle::removeVetoableChangeListener( PropertyName, aListener );
}

// XStyle
OUString SAL_CALL SdUnoGraphicStyle::getParentStyle(  )
    throw(uno::RuntimeException)
{
    OGuard aGuard( Application::GetSolarMutex() );

    OUString aName;
    if( mpStyleSheet )
    {
        aName = SdUnoGraphicStyleFamily::getExternalStyleName( mpStyleSheet->GetParent() );
    }
    else
    {
        aName = maPreInitParent;
    }

    return aName;
}

void SAL_CALL SdUnoGraphicStyle::setParentStyle( const OUString& aParentStyle )
    throw(container::NoSuchElementException, uno::RuntimeException)
{
    OGuard aGuard( Application::GetSolarMutex() );

    if( mpStyleSheet )
    {
        String aStyleName( SdUnoGraphicStyleFamily::getInternalStyleName(aParentStyle) );
        if( aStyleName.Len() && mpStyleSheet->GetPool().Find( aStyleName, SFX_STYLE_FAMILY_PARA ) == NULL )
            throw container::NoSuchElementException();

        mpStyleSheet->SetParent( aStyleName );
        ((SdStyleSheet*)mpStyleSheet)->Broadcast(SfxSimpleHint(SFX_HINT_DATACHANGED));
    }
    else
    {
        maPreInitParent = aParentStyle;
    }

    if( mpModel )
        mpModel->SetModified();
}

//XServiceInfo
OUString SAL_CALL SdUnoGraphicStyle::getImplementationName()
    throw(uno::RuntimeException)
{
    return OUString( OUString::createFromAscii(sUNO_SdUnoGraphicStyle) );
}

}
