/*************************************************************************
 *
 *  $RCSfile: svx_unobtabl.cxx,v $
 *
 *  $Revision: 1.3 $
 *
 *  last change: $Author: hr $ $Date: 2004-08-03 16:40:35 $
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

// auto strip #ifndef _SFXITEMPOOL_HXX
// auto strip #include <svtools/itempool.hxx>
// auto strip #endif

#ifndef _SV_CVTGRF_HXX
#include <vcl/cvtgrf.hxx>
#endif

// auto strip #ifndef _SFXITEMSET_HXX //autogen
// auto strip #include <svtools/itemset.hxx>
// auto strip #endif
// auto strip #ifndef _SVX_XIT_HXX 
// auto strip #include <xit.hxx>
// auto strip #endif
#ifndef SVX_LIGHT
#ifndef _SFXDOCFILE_HXX 
#include <bf_sfx2/docfile.hxx>
#endif
#endif

#ifndef _SVX_UNONAMEITEMTABLE_HXX_
#include "UnoNameItemTable.hxx"
#endif

#ifndef _XDEF_HXX
#include "xdef.hxx"
#endif

#include "xbtmpit.hxx"
// auto strip #include "svdmodel.hxx"
// auto strip #include "xflhtit.hxx"
// auto strip #include "unoapi.hxx"
// auto strip #include "impgrf.hxx"
#include "unomid.hxx"
#include "unoprnms.hxx"
namespace binfilter {

using namespace ::com::sun::star;
using namespace ::rtl;
using namespace ::cppu;

class SvxUnoBitmapTable : public SvxUnoNameItemTable
{
public:
    SvxUnoBitmapTable( SdrModel* pModel ) throw();
    virtual	~SvxUnoBitmapTable() throw();

    virtual NameOrIndex* createItem() const throw();

    // XServiceInfo
    virtual OUString SAL_CALL getImplementationName(  ) throw( uno::RuntimeException );
    virtual uno::Sequence<  OUString > SAL_CALL getSupportedServiceNames(  ) throw( uno::RuntimeException);

    // XElementAccess
    virtual uno::Type SAL_CALL getElementType(  ) throw( uno::RuntimeException);
};

SvxUnoBitmapTable::SvxUnoBitmapTable( SdrModel* pModel ) throw()
: SvxUnoNameItemTable( pModel, XATTR_FILLBITMAP, MID_GRAFURL )
{
}

SvxUnoBitmapTable::~SvxUnoBitmapTable() throw()
{
}

OUString SAL_CALL SvxUnoBitmapTable::getImplementationName() throw( uno::RuntimeException )
{
    return OUString( RTL_CONSTASCII_USTRINGPARAM("SvxUnoBitmapTable") );
}

uno::Sequence< OUString > SAL_CALL SvxUnoBitmapTable::getSupportedServiceNames(  )
    throw( uno::RuntimeException )
{
    uno::Sequence< OUString > aSNS( 1 );
    aSNS.getArray()[0] = OUString( RTL_CONSTASCII_USTRINGPARAM("com.sun.star.drawing.BitmapTable" ));
    return aSNS;
}

NameOrIndex* SvxUnoBitmapTable::createItem() const throw()
{
    return new XFillBitmapItem();
}

// XElementAccess
uno::Type SAL_CALL SvxUnoBitmapTable::getElementType(  )
    throw( uno::RuntimeException )
{
    return ::getCppuType( (const ::rtl::OUString*)0 );
}

/**
 * Create a bitmaptable
 */
uno::Reference< uno::XInterface > SAL_CALL SvxUnoBitmapTable_createInstance( SdrModel* pModel )
{
    return *new SvxUnoBitmapTable(pModel);
}
} //STRIP009 namespace bifilter
// auto strip #ifndef _STREAM_HXX 
// auto strip #include <tools/stream.hxx>
// auto strip #endif
// auto strip #ifndef _UNOTOOLS_LOCALFILEHELPER_HXX
// auto strip #include <unotools/localfilehelper.hxx>
// auto strip #endif

namespace binfilter {//STRIP009
/** returns a GraphicObject for this URL */
GraphicObject CreateGraphicObjectFromURL( const ::rtl::OUString &rURL ) throw()
{
    const String aURL( rURL ), aPrefix( RTL_CONSTASCII_STRINGPARAM(UNO_NAME_GRAPHOBJ_URLPREFIX) );

    if( aURL.Search( aPrefix ) == 0 )
    {
        // graphic manager url
        ByteString aUniqueID( String(rURL.copy( sizeof( UNO_NAME_GRAPHOBJ_URLPREFIX ) - 1 )), RTL_TEXTENCODING_UTF8 );
        return GraphicObject( aUniqueID );
    }
    else
    {
        Graphic		aGraphic;

#ifndef SVX_LIGHT
        SfxMedium	aMedium( aURL, STREAM_READ, TRUE );
        SvStream*	pStream = aMedium.GetInStream();

        if( pStream )
            GraphicConverter::Import( *pStream, aGraphic );
#else
        String aSystemPath( rURL );
        ::utl::LocalFileHelper::ConvertURLToSystemPath( aSystemPath, aSystemPath );
        SvFileStream aFile( aSystemPath, STREAM_READ );
        GraphicConverter::Import( aFile, aGraphic );
#endif
        

        return GraphicObject( aGraphic );
    }
}
}
