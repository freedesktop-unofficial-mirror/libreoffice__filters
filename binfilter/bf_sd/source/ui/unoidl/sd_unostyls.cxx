/*************************************************************************
 *
 *  $RCSfile: sd_unostyls.cxx,v $
 *
 *  $Revision: 1.3 $
 *
 *  last change: $Author: hr $ $Date: 2004-08-03 14:09:09 $
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

// auto strip #ifndef _VOS_MUTEX_HXX_
// auto strip #include <vos/mutex.hxx>
// auto strip #endif

// auto strip #ifndef _LIST_HXX
// auto strip #include <tools/list.hxx>
// auto strip #endif

#include <bf_svx/unoprov.hxx>

#include "unostyls.hxx"
#include "unohelp.hxx"
#include "unowcntr.hxx"
#include "unokywds.hxx"
#include "unogsfm.hxx"
#include "unopsfm.hxx"
#include "drawdoc.hxx"
#include "sdpage.hxx"
#include "glob.hxx"
namespace binfilter {

using namespace ::rtl;
using namespace ::vos;
using namespace ::com::sun::star;
    
SdUnoStyleFamilies::SdUnoStyleFamilies( SdXImpressDocument* pModel ) throw()
: mxModel( pModel ), mpModel( pModel )
{
    DBG_ASSERT( mxModel.is(), "i need a model to work with" );

    mbImpress = mpModel->IsImpressDocument();
    mpStyleFamilies = new SvUnoWeakContainer();
}

SdUnoStyleFamilies::~SdUnoStyleFamilies() throw()
{
    delete mpStyleFamilies;
}

// XServiceInfo
OUString SAL_CALL SdUnoStyleFamilies::getImplementationName()
    throw(uno::RuntimeException)
{
    return OUString( RTL_CONSTASCII_USTRINGPARAM("SdUnoStyleFamilies") );
}


sal_Bool SAL_CALL SdUnoStyleFamilies::supportsService( const OUString& ServiceName ) throw(uno::RuntimeException)
{
    return SvxServiceInfoHelper::supportsService( ServiceName, getSupportedServiceNames() );
}

uno::Sequence< OUString > SAL_CALL SdUnoStyleFamilies::getSupportedServiceNames()
    throw(uno::RuntimeException)
{
    OUString aStr( OUString::createFromAscii( sUNO_Service_StyleFamilies  ) );
    uno::Sequence< OUString > aSeq( &aStr, 1 );
    return aSeq;
}

// XNameAccess
uno::Any SAL_CALL SdUnoStyleFamilies::getByName( const OUString& aName )
    throw(container::NoSuchElementException, lang::WrappedTargetException, uno::RuntimeException)
{
    if( !isValid() )
        throw container::NoSuchElementException();

    uno::Any aAny;

    if( aName.compareToAscii( sUNO_Graphic_Style_Family_Name ) == 0 )
    {
        createGraphicStyleFamily( aAny );
    }
    else
    {
        sal_uInt16 nLayout = mbImpress ? getLayoutIndexByName( aName ) : USHRT_MAX;
        if( nLayout != USHRT_MAX )
        {
            createStyleFamilyByIndex( nLayout, aAny );
        }
        else
        {
            throw container::NoSuchElementException();
        }
    }

    return aAny;
}

uno::Sequence< OUString > SAL_CALL SdUnoStyleFamilies::getElementNames()
    throw(uno::RuntimeException)
{
    sal_uInt16 nFamilies = (sal_uInt16)getCount();

    uno::Sequence< OUString > aNameSequence( nFamilies );
    OUString* pNames = aNameSequence.getArray();

    *pNames++ = OUString::createFromAscii( sUNO_Graphic_Style_Family_Name );
    nFamilies--;

    if( mbImpress )
    {
        sal_uInt16 nLayout = 0;
        while( nFamilies )
        {
            *pNames++ = getLayoutNameByIndex( nLayout );
            nLayout++;
            nFamilies--;
        }
    }

    return aNameSequence;
}

/** returns true if this instances has a layout with the given name */
sal_Bool SAL_CALL SdUnoStyleFamilies::hasByName( const OUString& aName )
    throw(uno::RuntimeException)
{
    // is the model still valid?
    if( NULL == mpModel->GetDoc() )
        return NULL;

    // is it the graphic style?
    if( aName.compareToAscii( sUNO_Graphic_Style_Family_Name ) == 0 )
        return sal_True;

    // if this is an impress, check the master pages2
    return mbImpress && getLayoutIndexByName( aName ) != USHRT_MAX;
}

// XElementAccess

/** returns the type of a style family, the container::XNameContainer interface */
uno::Type SAL_CALL SdUnoStyleFamilies::getElementType()
    throw(uno::RuntimeException)
{
    return ITYPE( container::XNameAccess );
}

/** returns true if we have a valid model, than we always have style families */
sal_Bool SAL_CALL SdUnoStyleFamilies::hasElements()
    throw(uno::RuntimeException)
{
    return mpModel->GetDoc() != NULL;
}

// XIndexAccess
sal_Int32 SAL_CALL SdUnoStyleFamilies::getCount()
    throw(uno::RuntimeException)
{
    if( mpModel->GetDoc() != NULL )
        return mbImpress ? getLayoutCount() + 1 : 1;
    else
        return 0;
}

uno::Any SAL_CALL SdUnoStyleFamilies::getByIndex( sal_Int32 Index )
    throw(lang::IndexOutOfBoundsException, lang::WrappedTargetException, uno::RuntimeException)
{
    uno::Any aAny;

    if( Index < 0 || Index > getLayoutCount() || ( !mbImpress && Index > 0 ) )
        throw lang::IndexOutOfBoundsException();

    if( 0 == Index )
    {
        createGraphicStyleFamily( aAny );
    }
    else
    {
        createStyleFamilyByIndex( Index - 1, aAny );
    }

    return aAny;
}

/** creates a style family object for the graphic style family */
void SdUnoStyleFamilies::createGraphicStyleFamily( uno::Any& rAny )
    throw( container::NoSuchElementException )
{
    uno::Reference< container::XNameAccess > xContainer( mxGraphicStyles );
    if( !xContainer.is() )
        mxGraphicStyles = xContainer = new SdUnoGraphicStyleFamily( mpModel );

    if( !xContainer.is() )
        throw container::NoSuchElementException();

    rAny <<= xContainer;
}

sal_Bool SdUnoStyleFamilies_searchfunc( uno::WeakReference< uno::XInterface > xRef, void* pSearchData )
{
    uno::Reference< uno::XInterface > xInt( xRef );
    uno::Reference< container::XNameAccess > xFamily( xInt, uno::UNO_QUERY );
    if( xFamily.is() )
    {
        SdUnoPseudoStyleFamily* pFamily = SdUnoPseudoStyleFamily::getImplementation( xFamily );

        if( pFamily && pFamily->getPage() == (SdPage*)pSearchData )
            return sal_True;
    }
    return sal_False;
}

/** creates a style family for the given layout */
void SdUnoStyleFamilies::createStyleFamilyByIndex( sal_uInt16 nLayout, uno::Any& rAny ) throw()
{
    SdDrawDocument* pDoc = mpModel->GetDoc();
    SdPage* pMaster = (SdPage*)pDoc->GetMasterSdPage(nLayout,PK_STANDARD);

    // do we already have an instance for this layout?
    uno::WeakReference< uno::XInterface > xRef;
    uno::Reference< container::XNameAccess >  xFamily;

    if( mpStyleFamilies->findRef( xRef, (void*)pMaster, SdUnoStyleFamilies_searchfunc ) )
        xFamily = uno::Reference< container::XNameAccess >::query( xRef.get() );

    if( !xFamily.is() )
    {
        xFamily = new SdUnoPseudoStyleFamily( mpModel, pMaster );
        xRef = uno::Reference< uno::XInterface >( xFamily );
        mpStyleFamilies->insert(xRef);
    }

    rAny <<= xFamily;

}

/** returns the count of standard master pages of the document */
sal_uInt16 SdUnoStyleFamilies::getLayoutCount() throw()
{
    SdDrawDocument* pDoc = mpModel->GetDoc();
    sal_uInt16 nCount = 0;
    if( pDoc && mbImpress )
        nCount = pDoc->GetMasterSdPageCount(PK_STANDARD);

    return nCount;
}

/** returns the layout name of the standard master page with the givin index */
OUString SdUnoStyleFamilies::getLayoutNameByIndex( sal_uInt16 nIndex ) throw()
{
    String aLayoutName;

    SdDrawDocument* pDoc = mpModel->GetDoc();

    SdPage* pMaster = (SdPage*)pDoc->GetMasterSdPage(nIndex,PK_STANDARD);
    aLayoutName = pMaster->GetLayoutName();
    aLayoutName = aLayoutName.Erase(aLayoutName.Search(String( RTL_CONSTASCII_USTRINGPARAM( SD_LT_SEPARATOR )) ));

    return aLayoutName;
}

/** returns the index of the standard master page with the given layout name or
    USHRT_MAX if the layout name was not found */
sal_uInt16 SdUnoStyleFamilies::getLayoutIndexByName( const OUString& rName ) throw()
{
    const String aName( rName );

    USHORT nIndex = 0;

    SdDrawDocument* pDoc = mpModel->GetDoc();
    if( NULL != pDoc )
    {
        sal_uInt16 nCount = pDoc->GetMasterSdPageCount(PK_STANDARD); 

        for( sal_uInt16 nPage = 0; nPage < nCount; nPage++ )
        {
            SdPage* pMaster = (SdPage*)pDoc->GetMasterSdPage(nPage, PK_STANDARD);

            String aLayoutName( pMaster->GetLayoutName() );
            aLayoutName.Erase(aLayoutName.Search(String( RTL_CONSTASCII_USTRINGPARAM(SD_LT_SEPARATOR))));

            if( aName == aLayoutName )
                return nPage;
        }
    }

    return USHRT_MAX;
}

}
