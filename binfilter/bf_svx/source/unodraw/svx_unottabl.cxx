/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: svx_unottabl.cxx,v $
 *
 *  $Revision: 1.4 $
 *
 *  last change: $Author: rt $ $Date: 2005-09-08 07:30:45 $
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

#ifndef _COM_SUN_STAR_AWT_GRADIENT_HPP_
#include <com/sun/star/awt/Gradient.hpp>
#endif

// auto strip #ifndef _SFXITEMPOOL_HXX
// auto strip #include <svtools/itempool.hxx>
// auto strip #endif

// auto strip #ifndef _SFXITEMSET_HXX //autogen
// auto strip #include <svtools/itemset.hxx>
// auto strip #endif

// auto strip #ifndef _SVX__XGRADIENT_HXX //autogen
// auto strip #include "xgrad.hxx"
// auto strip #endif

#ifndef _XDEF_HXX
#include "xdef.hxx"
#endif

#ifndef _SVX_XFLFTRIT_HXX
#include "xflftrit.hxx"
#endif

// auto strip #include "svdmodel.hxx"
// auto strip #include "xflhtit.hxx"

#ifndef _SVX_UNONAMEITEMTABLE_HXX_
#include "UnoNameItemTable.hxx"
#endif
namespace binfilter {

using namespace ::com::sun::star;
using namespace ::rtl;
using namespace ::cppu;

class SvxUnoTransGradientTable : public SvxUnoNameItemTable
{
public:
    SvxUnoTransGradientTable( SdrModel* pModel ) throw();
    virtual	~SvxUnoTransGradientTable() throw();

    virtual NameOrIndex* createItem() const throw();

    // XServiceInfo
    virtual OUString SAL_CALL getImplementationName(  ) throw( uno::RuntimeException );
    virtual uno::Sequence<  OUString > SAL_CALL getSupportedServiceNames(  ) throw( uno::RuntimeException);

    // XElementAccess
    virtual uno::Type SAL_CALL getElementType(  ) throw( uno::RuntimeException);
};

SvxUnoTransGradientTable::SvxUnoTransGradientTable( SdrModel* pModel ) throw()
: SvxUnoNameItemTable( pModel, XATTR_FILLFLOATTRANSPARENCE )
{
}

SvxUnoTransGradientTable::~SvxUnoTransGradientTable() throw()
{
}

OUString SAL_CALL SvxUnoTransGradientTable::getImplementationName() throw( uno::RuntimeException )
{
    return OUString( RTL_CONSTASCII_USTRINGPARAM("SvxUnoTransGradientTable") );
}

uno::Sequence< OUString > SAL_CALL SvxUnoTransGradientTable::getSupportedServiceNames(  )
    throw( uno::RuntimeException )
{
    uno::Sequence< OUString > aSNS( 1 );
    aSNS.getArray()[0] = OUString( RTL_CONSTASCII_USTRINGPARAM("com.sun.star.drawing.TransparencyGradientTable" ));
    return aSNS;
}

NameOrIndex* SvxUnoTransGradientTable::createItem() const throw()
{
    XFillFloatTransparenceItem* pNewItem = new XFillFloatTransparenceItem();
    pNewItem->SetEnabled( TRUE );
    return pNewItem;
}

// XElementAccess
uno::Type SAL_CALL SvxUnoTransGradientTable::getElementType(  )
    throw( uno::RuntimeException )
{
    return ::getCppuType((const struct awt::Gradient*)0);
}

/**
 * Create a hatchtable
 */
uno::Reference< uno::XInterface > SAL_CALL SvxUnoTransGradientTable_createInstance( SdrModel* pModel )
{
    return *new SvxUnoTransGradientTable(pModel);
}



}
