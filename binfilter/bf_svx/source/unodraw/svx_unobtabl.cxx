/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: svx_unobtabl.cxx,v $
 *
 *  $Revision: 1.5 $
 *
 *  last change: $Author: rt $ $Date: 2006-10-27 21:54:29 $
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


#ifndef _SV_CVTGRF_HXX
#include <vcl/cvtgrf.hxx>
#endif

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
