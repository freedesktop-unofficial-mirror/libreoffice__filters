/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: svt_macitem.cxx,v $
 *
 *  $Revision: 1.2 $
 *
 *  last change: $Author: rt $ $Date: 2008-03-12 08:47:23 $
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

#include <tools/stream.hxx>
#include <tools/table.hxx>

#include <bf_svtools/macitem.hxx>

namespace binfilter
{

// STATIC DATA -----------------------------------------------------------

DBG_NAME(SvxMacroItem)

// -----------------------------------------------------------------------

TYPEINIT1_FACTORY(SvxMacroItem, SfxPoolItem, new SvxMacroItem(0));

// -----------------------------------------------------------------------


SjJSbxObjectBase::~SjJSbxObjectBase()
{
}

SjJSbxObjectBase* SjJSbxObjectBase::Clone( void )
{
    return NULL;
}

SvxMacro::SvxMacro( const String &rMacName, const String &rLanguage)
    : aMacName( rMacName ), aLibName( rLanguage),
      pFunctionObject(NULL), eType( EXTENDED_STYPE)
{
    if (rLanguage.EqualsAscii(SVX_MACRO_LANGUAGE_STARBASIC))
        eType=STARBASIC;
    else if (rLanguage.EqualsAscii(SVX_MACRO_LANGUAGE_JAVASCRIPT))
        eType=JAVASCRIPT;
}


SvxMacro::~SvxMacro()
{
    delete pFunctionObject;
}

String SvxMacro::GetLanguage()const
{
    if(eType==STARBASIC)
    {
        return UniString::CreateFromAscii(
                   RTL_CONSTASCII_STRINGPARAM(SVX_MACRO_LANGUAGE_STARBASIC));
    }
    else if(eType==JAVASCRIPT)
    {
        return UniString::CreateFromAscii(
                   RTL_CONSTASCII_STRINGPARAM(SVX_MACRO_LANGUAGE_JAVASCRIPT));
    }
    else if(eType==EXTENDED_STYPE)
    {
        return UniString::CreateFromAscii(
                   RTL_CONSTASCII_STRINGPARAM(SVX_MACRO_LANGUAGE_SF));

    }
    return aLibName;
}



SvxMacro& SvxMacro::operator=( const SvxMacro& rBase )
{
    if( this != &rBase )
    {
        aMacName = rBase.aMacName;
        aLibName = rBase.aLibName;
        delete pFunctionObject;
        pFunctionObject = rBase.pFunctionObject ? rBase.pFunctionObject->Clone() : NULL;
        eType = rBase.eType;
    }
    return *this;
}


SvxMacroTableDtor& SvxMacroTableDtor::operator=( const SvxMacroTableDtor& rTbl )
{
    DelDtor();
    SvxMacro* pTmp = ((SvxMacroTableDtor&)rTbl).First();
    while( pTmp )
    {
        SvxMacro *pNew = new SvxMacro( *pTmp );
        Insert( rTbl.GetCurKey(), pNew );
        pTmp = ((SvxMacroTableDtor&)rTbl).Next();
    }
    return *this;
}


SvStream& SvxMacroTableDtor::Read( SvStream& rStrm, USHORT nVersion )
{
    if( SVX_MACROTBL_VERSION40 <= nVersion )
        rStrm >> nVersion;
    short nMacro;
    rStrm >> nMacro;

    for( short i = 0; i < nMacro; ++i )
    {
        USHORT nCurKey, eType = STARBASIC;
        String aLibName, aMacName;
        rStrm >> nCurKey;
        SfxPoolItem::readByteString(rStrm, aLibName);
        SfxPoolItem::readByteString(rStrm, aMacName);

        if( SVX_MACROTBL_VERSION40 <= nVersion )
            rStrm >> eType;

        SvxMacro* pNew = new SvxMacro( aMacName, aLibName, (ScriptType)eType );

        SvxMacro *pOld = Get( nCurKey );
        if( pOld )
        {
            delete pOld;
            Replace( nCurKey, pNew );
        }
        else
            Insert( nCurKey, pNew );
    }
    return rStrm;
}


SvStream& SvxMacroTableDtor::Write( SvStream& rStream ) const
{
    USHORT nVersion = SOFFICE_FILEFORMAT_31 == rStream.GetVersion()
                                    ? SVX_MACROTBL_VERSION31
                                    : SVX_MACROTBL_AKTVERSION;

    if( SVX_MACROTBL_VERSION40 <= nVersion )
        rStream << nVersion;

    rStream << (USHORT)Count();

    SvxMacro* pMac = ((SvxMacroTableDtor*)this)->First();
    while( pMac && rStream.GetError() == SVSTREAM_OK )
    {
        rStream << (short)GetCurKey();
        SfxPoolItem::writeByteString(rStream, pMac->GetLibName());
        SfxPoolItem::writeByteString(rStream, pMac->GetMacName());

        if( SVX_MACROTBL_VERSION40 <= nVersion )
            rStream << (USHORT)pMac->GetScriptType();
        pMac = ((SvxMacroTableDtor*)this)->Next();
    }
    return rStream;
}

// -----------------------------------------------------------------------

void SvxMacroTableDtor::DelDtor()
{
    SvxMacro* pTmp = First();
    while( pTmp )
    {
        delete pTmp;
        pTmp = Next();
    }
    Clear();
}

// -----------------------------------------------------------------------

int SvxMacroItem::operator==( const SfxPoolItem& rAttr ) const
{
    DBG_ASSERT( SfxPoolItem::operator==(rAttr), "unequal types" );

    const SvxMacroTableDtor& rOwn = aMacroTable;
    const SvxMacroTableDtor& rOther = ( (SvxMacroItem&) rAttr ).aMacroTable;

    // Anzahl unterschiedlich => auf jeden Fall ungleich
    if ( rOwn.Count() != rOther.Count() )
        return FALSE;

    // einzeln verleichen; wegen Performance ist die Reihenfolge wichtig
    for ( USHORT nNo = 0; nNo < rOwn.Count(); ++nNo )
    {
        const SvxMacro *pOwnMac = rOwn.GetObject(nNo);
        const SvxMacro *pOtherMac = rOther.GetObject(nNo);
        if ( 	rOwn.GetKey(pOwnMac) != rOther.GetKey(pOtherMac)  ||
                pOwnMac->GetLibName() != pOtherMac->GetLibName() ||
                pOwnMac->GetMacName() != pOtherMac->GetMacName() )
            return FALSE;
    }

    return TRUE;
}

// -----------------------------------------------------------------------

SfxPoolItem* SvxMacroItem::Clone( SfxItemPool* ) const
{
    return new SvxMacroItem( *this );
}

//------------------------------------------------------------------------

SfxItemPresentation SvxMacroItem::GetPresentation
(
    SfxItemPresentation /*ePres*/,
    SfxMapUnit			/*eCoreUnit*/,
    SfxMapUnit			/*ePresUnit*/,
    XubString& 			rText,
    const ::IntlWrapper *
)	const
{
/*!!!
    SvxMacroTableDtor& rTbl = (SvxMacroTableDtor&)GetMacroTable();
    SvxMacro* pMac = rTbl.First();

    while ( pMac )
    {
        rText += pMac->GetLibName();
        rText += cpDelim;
        rText += pMac->GetMacName();
        pMac = rTbl.Next();
        if ( pMac )
            rText += cpDelim;
    }
*/
    rText.Erase();
    return SFX_ITEM_PRESENTATION_NONE;
}

// -----------------------------------------------------------------------

SvStream& SvxMacroItem::Store( SvStream& rStrm , USHORT ) const
{
    return aMacroTable.Write( rStrm );
}

// -----------------------------------------------------------------------

SfxPoolItem* SvxMacroItem::Create( SvStream& rStrm, USHORT nVersion ) const
{
    SvxMacroItem* pAttr = new SvxMacroItem( Which() );
    pAttr->aMacroTable.Read( rStrm, nVersion );
    return pAttr;
}

// -----------------------------------------------------------------------

void SvxMacroItem::SetMacro( USHORT nEvent, const SvxMacro& rMacro )
{
    SvxMacro *pMacro;
    if ( 0 != (pMacro=aMacroTable.Get(nEvent)) )
    {
        delete pMacro;
        aMacroTable.Replace(nEvent, new SvxMacro( rMacro ) );
    }
    else
        aMacroTable.Insert(nEvent, new SvxMacro( rMacro ) );
}

// -----------------------------------------------------------------------

USHORT SvxMacroItem::GetVersion( USHORT nFileFormatVersion ) const
{
    return SOFFICE_FILEFORMAT_31 == nFileFormatVersion
                ? 0 : aMacroTable.GetVersion();
}

}
