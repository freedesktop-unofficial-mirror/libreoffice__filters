/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: svt_ctypeitm.cxx,v $
 *
 *  $Revision: 1.2 $
 *
 *  last change: $Author: rt $ $Date: 2008-03-12 08:50:37 $
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

// MARKER(update_precomp.py): autogen include statement, do not remove


#ifndef _COM_SUN_STAR_UNO_ANY_HXX_
#include <com/sun/star/uno/Any.hxx>
#endif

#include <unotools/intlwrapper.hxx>

#ifndef _STREAM_HXX
#include <tools/stream.hxx>
#endif
#ifndef _SVTOOLS_CTYPEITM_HXX
#include <bf_svtools/ctypeitm.hxx>
#endif

namespace binfilter
{

//============================================================================
// The following defines are copied from chaos/source/items/cstritem.cxx:
#define CNTSTRINGITEM_STREAM_MAGIC   ( (UINT32)0xfefefefe )
#define CNTSTRINGITEM_STREAM_SEEKREL (-( (long)( sizeof( UINT32 ) ) ) )

//============================================================================
//
// class CntContentTypeItem Implementation.
//
//============================================================================

TYPEINIT1_AUTOFACTORY( CntContentTypeItem, CntUnencodedStringItem );

#define CONTENT_TYPE_NOT_INIT ( (INetContentType)-1 )

//----------------------------------------------------------------------------
CntContentTypeItem::CntContentTypeItem()
: CntUnencodedStringItem(),
  _eType( CONTENT_TYPE_NOT_INIT )
{
}

//----------------------------------------------------------------------------
CntContentTypeItem::CntContentTypeItem(	USHORT which, const XubString& rType )
: CntUnencodedStringItem( which, rType ),
  _eType( CONTENT_TYPE_NOT_INIT )
{
}

//----------------------------------------------------------------------------
CntContentTypeItem::CntContentTypeItem(	USHORT which,
                                        const INetContentType eType )
: CntUnencodedStringItem( which, INetContentTypes::GetContentType( eType ) ),
  _eType( eType )
{
}

//----------------------------------------------------------------------------
CntContentTypeItem::CntContentTypeItem( const CntContentTypeItem& rOrig )
: CntUnencodedStringItem( rOrig ),
  _eType( rOrig._eType ),
  _aPresentation( rOrig._aPresentation )
{
}

//============================================================================
// virtual
USHORT CntContentTypeItem::GetVersion(USHORT) const
{
    return 1; // because it uses SfxPoolItem::read/writeUnicodeString()
}

//----------------------------------------------------------------------------
// virtual
SfxPoolItem* CntContentTypeItem::Create( SvStream& rStream,
                                         USHORT nItemVersion ) const
{
    // CntContentTypeItem used to be derived from CntStringItem, so take that
    // into account:
    UniString aValue;
    readUnicodeString(rStream, aValue, nItemVersion >= 1);
    UINT32 nMagic = 0;
    rStream >> nMagic;
    if (nMagic == CNTSTRINGITEM_STREAM_MAGIC)
    {
        BOOL bEncrypted = FALSE;
        rStream >> bEncrypted;
        DBG_ASSERT(!bEncrypted,
                   "CntContentTypeItem::Create() reads encrypted data");
    }
    else
        rStream.SeekRel(CNTSTRINGITEM_STREAM_SEEKREL);

    return new CntContentTypeItem(Which(), aValue);
}

//----------------------------------------------------------------------------
// virtual
SvStream & CntContentTypeItem::Store(SvStream & rStream, USHORT) const
{
    // CntContentTypeItem used to be derived from CntStringItem, so take that
    // into account:
    writeUnicodeString(rStream, GetValue());
    rStream << CNTSTRINGITEM_STREAM_MAGIC << BOOL(FALSE);
    return rStream;
}

//----------------------------------------------------------------------------
// virtual
int CntContentTypeItem::operator==( const SfxPoolItem& rOrig ) const
{
    const CntContentTypeItem& rOther = (const CntContentTypeItem&)rOrig;

    if ( ( _eType != CONTENT_TYPE_NOT_INIT ) &&
         ( rOther._eType != CONTENT_TYPE_NOT_INIT ) )
        return _eType == rOther._eType;
    else
        return CntUnencodedStringItem::operator==( rOther );
}

//----------------------------------------------------------------------------
// virtual
SfxPoolItem* CntContentTypeItem::Clone( SfxItemPool* /* pPool */ ) const
{
    return new CntContentTypeItem( *this );
}

//----------------------------------------------------------------------------
void CntContentTypeItem::SetValue( const XubString& rNewVal )
{
    // De-initialize enum type and presentation.
    _eType = CONTENT_TYPE_NOT_INIT;
    _aPresentation.Erase();

    CntUnencodedStringItem::SetValue( rNewVal );
}

//----------------------------------------------------------------------------
void CntContentTypeItem::SetPresentation( const XubString& rNewVal )
{
    _aPresentation = rNewVal;
}

//----------------------------------------------------------------------------
int CntContentTypeItem::Compare( const SfxPoolItem &rWith, const ::IntlWrapper& rIntlWrapper ) const
{
    String aOwnText, aWithText;
    GetPresentation( SFX_ITEM_PRESENTATION_NAMELESS,
                     SFX_MAPUNIT_APPFONT, SFX_MAPUNIT_APPFONT, aOwnText, &rIntlWrapper );
    rWith.GetPresentation( SFX_ITEM_PRESENTATION_NAMELESS,
                           SFX_MAPUNIT_APPFONT, SFX_MAPUNIT_APPFONT, aWithText, &rIntlWrapper );
    return rIntlWrapper.getCollator()->compareString( aOwnText, aWithText );
}

//----------------------------------------------------------------------------
SfxItemPresentation CntContentTypeItem::GetPresentation(
    SfxItemPresentation ePres,
    SfxMapUnit          eCoreMetric,
    SfxMapUnit          ePresMetric,
    XubString         & rText,
    const ::IntlWrapper * pIntlWrapper) const
{
    if (_aPresentation.Len() == 0)
    {
        DBG_ASSERT(pIntlWrapper,
                   "CntContentTypeItem::GetPresentation(): No IntlWrapper");
        if (pIntlWrapper)
            SAL_CONST_CAST(CntContentTypeItem *, this)->_aPresentation
             = INetContentTypes::GetPresentation(GetEnumValue(),
                                                 pIntlWrapper->
                                                  getLocale());
    }
    if (_aPresentation.Len() > 0)
    {
        rText = _aPresentation;
        return SFX_ITEM_PRESENTATION_COMPLETE;
    }
    else
        return CntUnencodedStringItem::GetPresentation(ePres, eCoreMetric,
                                                       ePresMetric, rText,
                                                       pIntlWrapper);
}

//----------------------------------------------------------------------------
const INetContentType CntContentTypeItem::GetEnumValue() const
{
    if ( _eType == CONTENT_TYPE_NOT_INIT )
    {
        // Not yet initialized... Get enum value for string content type.

        CntContentTypeItem* pVarThis = SAL_CONST_CAST( CntContentTypeItem*, this );

        pVarThis->_eType = INetContentTypes::GetContentType( GetValue() );
    }

    return _eType;
}

//----------------------------------------------------------------------------
void CntContentTypeItem::SetValue( const INetContentType eType )
{
    SetValue( INetContentTypes::GetContentType( eType ) );

    // Note: SetValue( const String& ....) resets _eType. Set new enum value
    //       after(!) calling it.
    _eType = eType;
}

//----------------------------------------------------------------------------
// virtual
BOOL CntContentTypeItem::QueryValue( com::sun::star::uno::Any& rVal,BYTE ) const
{
    rVal <<= rtl::OUString(GetValue());
    return true;
}

//----------------------------------------------------------------------------
// virtual
BOOL CntContentTypeItem::PutValue( const com::sun::star::uno::Any& rVal,BYTE )
{
    rtl::OUString aValue;
    if ( rVal >>= aValue )
    {
        // SetValue with an empty string resets the item; so call that
        // function when PutValue is called with an empty string
        if (aValue.getLength() == 0)
            SetValue(aValue);
        else
            SetValue(
                INetContentTypes::RegisterContentType(aValue, UniString()));
        return true;
    }

    DBG_ERROR( "CntContentTypeItem::PutValue - Wrong type!" );
    return false;
}
}
