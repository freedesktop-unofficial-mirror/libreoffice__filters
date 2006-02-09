/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: svx_editobj.cxx,v $
 *
 *  $Revision: 1.8 $
 *
 *  last change: $Author: rt $ $Date: 2006-02-09 15:09:38 $
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


// auto strip #include <eeng_pch.hxx>

#pragma hdrstop

//#define ENABLE_STRING_STREAM_OPERATORS
// auto strip #include <tools/stream.hxx>

#ifndef _SV_OUTDEV_HXX
#include <vcl/outdev.hxx>
#endif

#include <editobj2.hxx>
// auto strip #include <editdata.hxx>
// auto strip #include <editattr.hxx>
#include <editeng.hxx>
#include <fontitem.hxx>
#include <cscoitem.hxx>
//#include <vcl/system.hxx>

// auto strip #ifndef _PSTM_HXX //autogen
// auto strip #include <tools/pstm.hxx>
// auto strip #endif

// auto strip #ifndef _SFXPOOLITEM_HXX //autogen
// auto strip #include <svtools/poolitem.hxx>
// auto strip #endif

#ifndef _SVX_ITEMDATA_HXX
#include "itemdata.hxx"
#endif

// auto strip #ifndef _DATE_HXX //autogen
// auto strip #include <tools/date.hxx>
// auto strip #endif

// auto strip #ifndef _TIME_HXX //autogen
// auto strip #include <tools/time.hxx>
// auto strip #endif

#include <flditem.hxx>
#include <lrspitem.hxx>
#include <tstpitem.hxx>
#include <bulitem.hxx>
#include <numitem.hxx>
#include <brshitem.hxx>
// auto strip #include <vcl/graph.hxx>
#include <svtools/intitem.hxx>
// auto strip #include <vcl/fontcvt.hxx>

#ifndef _TOOLS_TENCCVT_HXX
#include <tools/tenccvt.hxx>
#endif
namespace binfilter {

/*N*/ DBG_NAME( EE_EditTextObject )
/*N*/ DBG_NAME( XEditAttribute )

//--------------------------------------------------------------

/*N*/ BOOL lcl_CreateBulletItem( const SvxNumBulletItem& rNumBullet, USHORT nLevel, SvxBulletItem& rBullet )
/*N*/ {
/*N*/ 	const SvxNumberFormat* pFmt = rNumBullet.GetNumRule()->Get( nLevel );
/*N*/ 	if ( pFmt )
/*N*/ 	{
/*N*/ 		rBullet.SetWidth( (-pFmt->GetFirstLineOffset()) + pFmt->GetCharTextDistance() );
/*N*/ 		rBullet.SetSymbol( pFmt->GetBulletChar() );
/*N*/ 		rBullet.SetPrevText( pFmt->GetPrefix() );
/*N*/ 		rBullet.SetFollowText( pFmt->GetSuffix() );
/*N*/ 		rBullet.SetStart( pFmt->GetStart() );
/*N*/ 		rBullet.SetScale( pFmt->GetBulletRelSize() );
/*N*/ 
/*N*/ 		Font aBulletFont( rBullet.GetFont() );
/*N*/ 		if ( pFmt->GetBulletFont() )
/*N*/ 			aBulletFont = *pFmt->GetBulletFont();
/*N*/ 		aBulletFont.SetColor( pFmt->GetBulletColor() );
/*N*/ 		rBullet.SetFont( aBulletFont );
/*N*/ 
/*N*/ 		if ( pFmt->GetBrush() && pFmt->GetBrush()->GetGraphic() )
/*N*/ 		{
/*?*/ 			DBG_BF_ASSERT(0, "STRIP"); //STRIP001 Bitmap aBmp( pFmt->GetBrush()->GetGraphic()->GetBitmap() );
//STRIP001 /*?*/ 			aBmp.SetPrefSize( pFmt->GetGraphicSize() );
//STRIP001 /*?*/ 			aBmp.SetPrefMapMode( MAP_100TH_MM );
//STRIP001 /*?*/ 			rBullet.SetBitmap( aBmp );
/*N*/ 		}
/*N*/ 
/*N*/ 		switch ( pFmt->GetNumberingType() )
/*N*/ 		{
/*?*/ 			case SVX_NUM_CHARS_UPPER_LETTER:
/*?*/ 			case SVX_NUM_CHARS_UPPER_LETTER_N:
/*?*/ 				rBullet.SetStyle( BS_ABC_BIG );
/*?*/ 				break;
/*?*/ 			case SVX_NUM_CHARS_LOWER_LETTER:
/*?*/ 			case SVX_NUM_CHARS_LOWER_LETTER_N:
/*?*/ 				rBullet.SetStyle( BS_ABC_SMALL );
/*?*/ 				break;
/*?*/ 			case SVX_NUM_ROMAN_UPPER:
/*?*/ 				rBullet.SetStyle( BS_ROMAN_BIG );
/*?*/ 				break;
/*?*/ 			case SVX_NUM_ROMAN_LOWER:
/*?*/ 				rBullet.SetStyle( BS_ROMAN_SMALL );
/*?*/ 				break;
/*?*/ 			case SVX_NUM_ARABIC:
/*?*/ 				rBullet.SetStyle( BS_123 );
/*?*/ 				break;
/*?*/ 			case SVX_NUM_NUMBER_NONE:
/*?*/ 				rBullet.SetStyle( BS_NONE );
/*?*/ 				break;
/*?*/ 			case SVX_NUM_CHAR_SPECIAL:
/*N*/ 				rBullet.SetStyle( BS_BULLET );
/*N*/ 				break;
/*?*/ 			case SVX_NUM_PAGEDESC:
/*?*/ 				DBG_ERROR( "Unknown: SVX_NUM_PAGEDESC" );
/*?*/ 				rBullet.SetStyle( BS_BULLET );
/*?*/ 				break;
/*?*/ 			case SVX_NUM_BITMAP:
/*?*/ 				rBullet.SetStyle( BS_BMP );
/*?*/ 				break;
/*?*/ 			default:
/*?*/ 				DBG_ERROR( "Unknown NumType" );
/*N*/ 		}
/*N*/ 
/*N*/ 		switch ( pFmt->GetNumAdjust() )
/*N*/ 		{
/*N*/ 			case SVX_ADJUST_LEFT:
/*N*/ 				rBullet.SetJustification( BJ_VCENTER|BJ_HLEFT );
/*N*/ 				break;
/*?*/ 			case SVX_ADJUST_RIGHT:
/*?*/ 				rBullet.SetJustification( BJ_VCENTER|BJ_HRIGHT );
/*?*/ 				break;
/*?*/ 			case SVX_ADJUST_CENTER:
/*?*/ 				rBullet.SetJustification( BJ_VCENTER|BJ_HCENTER );
/*?*/ 				break;
/*?*/ 			default:
/*?*/ 				DBG_ERROR( "Unknown or invalid NumAdjust" );
/*N*/ 		}
/*N*/ 	}
/*N*/ 	return pFmt ? TRUE : FALSE;
/*N*/ }


/*N*/ XEditAttribute* MakeXEditAttribute( SfxItemPool& rPool, const SfxPoolItem& rItem, USHORT nStart, USHORT nEnd )
/*N*/ {
/*N*/ 	// das neue Attribut im Pool anlegen
/*N*/ 	const SfxPoolItem& rNew = rPool.Put( rItem );
/*N*/ 
/*N*/ 	XEditAttribute* pNew = new XEditAttribute( rNew, nStart, nEnd );
/*N*/ 	return pNew;
/*N*/ }


//STRIP001 XEditAttribute::XEditAttribute( const SfxPoolItem& rAttr )
//STRIP001 {
//STRIP001 	DBG_CTOR( XEditAttribute, 0 );
//STRIP001 	pItem = &rAttr;
//STRIP001 	nStart = 0;
//STRIP001 	nEnd = 0;
//STRIP001 }

/*N*/ XEditAttribute::XEditAttribute( const SfxPoolItem& rAttr, USHORT nS, USHORT nE )
/*N*/ {
/*N*/ 	DBG_CTOR( XEditAttribute, 0 );
/*N*/ 	pItem = &rAttr;
/*N*/ 	nStart = nS;
/*N*/ 	nEnd = nE;
/*N*/ }

/*N*/ XEditAttribute::~XEditAttribute()
/*N*/ {
/*N*/ 	DBG_DTOR( XEditAttribute, 0 );
/*N*/ 	pItem = 0;	// Gehoert dem Pool.
/*N*/ }

/*N*/ XEditAttribute* XEditAttributeList::FindAttrib( USHORT nWhich, USHORT nChar ) const
/*N*/ {
/*N*/     for ( USHORT n = Count(); n; )
/*N*/     {
/*N*/         XEditAttribute* pAttr = GetObject( --n );
/*N*/         if( ( pAttr->GetItem()->Which() == nWhich ) && ( pAttr->GetStart() <= nChar ) && ( pAttr->GetEnd() > nChar ) )
/*N*/             return pAttr;
/*N*/     }
/*N*/     return NULL;
/*N*/ }

/*N*/ ContentInfo::ContentInfo( SfxItemPool& rPool ) : aParaAttribs( rPool, EE_PARA_START, EE_CHAR_END )
/*N*/ {
/*N*/ 	eFamily = SFX_STYLE_FAMILY_PARA;
/*N*/ 	pWrongs = NULL;
/*N*/     pTempLoadStoreInfos = NULL;
/*N*/ }

// Richtiger CopyCTOR unsinning, weil ich mit einem anderen Pool arbeiten muss!
/*N*/ ContentInfo::ContentInfo( const ContentInfo& rCopyFrom, SfxItemPool& rPoolToUse )
/*N*/ 	: aParaAttribs( rPoolToUse, EE_PARA_START, EE_CHAR_END )
/*N*/ {
/*N*/ 	pWrongs = NULL;
/*N*/     pTempLoadStoreInfos = NULL;
/*N*/ #ifndef SVX_LIGHT
/*N*/ 	if ( rCopyFrom.GetWrongList() )
/*?*/ 	{DBG_BF_ASSERT(0, "STRIP");} //STRIP001 	pWrongs = rCopyFrom.GetWrongList()->Clone();
/*N*/ #endif // !SVX_LIGHT
/*N*/ 	// So sollten die Items im richtigen Pool landen!
/*N*/ 	aParaAttribs.Set( rCopyFrom.GetParaAttribs() );
/*N*/ 	aText = rCopyFrom.GetText();
/*N*/ 	aStyle = rCopyFrom.GetStyle();
/*N*/ 	eFamily = rCopyFrom.GetFamily();
/*N*/ 
/*N*/ 	// Attribute kopieren...
/*N*/ 	for ( USHORT n = 0; n < rCopyFrom.GetAttribs().Count(); n++  )
/*N*/ 	{
/*N*/ 		XEditAttribute* pAttr = rCopyFrom.GetAttribs().GetObject( n );
/*N*/ 		XEditAttribute* pMyAttr = MakeXEditAttribute( rPoolToUse, *pAttr->GetItem(), pAttr->GetStart(), pAttr->GetEnd() );
/*N*/ 		aAttribs.Insert( pMyAttr, aAttribs.Count()  );
/*N*/ 	}
/*N*/ 
/*N*/ 	// Wrongs
/*N*/ 	pWrongs = NULL;
/*N*/ #ifndef SVX_LIGHT
/*N*/ 	if ( rCopyFrom.GetWrongList() )
/*?*/ 	{DBG_BF_ASSERT(0, "STRIP");} //STRIP001 	pWrongs = rCopyFrom.GetWrongList()->Clone();
/*N*/ #endif // !SVX_LIGHT
/*N*/ }

/*N*/ ContentInfo::~ContentInfo()
/*N*/ {
/*N*/ 	for ( USHORT nAttr = 0; nAttr < aAttribs.Count(); nAttr++ )
/*N*/ 	{
/*N*/ 		XEditAttribute* pAttr = aAttribs.GetObject(nAttr);
/*N*/ 		// Item aus Pool entfernen!
/*N*/ 		aParaAttribs.GetPool()->Remove( *pAttr->GetItem() );
/*N*/ 		delete pAttr;
/*N*/ 	}
/*N*/ 	aAttribs.Remove( 0, aAttribs.Count() );
/*N*/ #ifndef SVX_LIGHT
/*N*/ 	delete pWrongs;
/*N*/ #endif
/*N*/ }

/*N*/ void ContentInfo::CreateLoadStoreTempInfos()
/*N*/ {
/*N*/     delete pTempLoadStoreInfos; 
/*N*/     pTempLoadStoreInfos = new LoadStoreTempInfos;
/*N*/ }

/*N*/ void ContentInfo::DestroyLoadStoreTempInfos()
/*N*/ {
/*N*/     delete pTempLoadStoreInfos; 
/*N*/     pTempLoadStoreInfos = NULL; 
/*N*/ }

/*N*/ EditTextObject::EditTextObject( USHORT n)
/*N*/ {
/*N*/ 	DBG_CTOR( EE_EditTextObject, 0 );
/*N*/ 	nWhich = n;
/*N*/ }

/*N*/ EditTextObject::EditTextObject( const EditTextObject& r )
/*N*/ {
/*N*/ 	DBG_CTOR( EE_EditTextObject, 0 );
/*N*/ 	nWhich = r.nWhich;
/*N*/ }

/*N*/ __EXPORT EditTextObject::~EditTextObject()
/*N*/ {
/*N*/ 	DBG_DTOR( EE_EditTextObject, 0 );
/*N*/ }

/*N*/ USHORT EditTextObject::GetParagraphCount() const
/*N*/ {
/*N*/ 	DBG_ERROR( "V-Methode direkt vom EditTextObject!" );
/*N*/ 	return 0;
/*N*/ }

/*N*/ XubString EditTextObject::GetText( USHORT nParagraph ) const
/*N*/ {DBG_BF_ASSERT(0, "STRIP"); return XubString();//STRIP001 
//STRIP001 	DBG_ERROR( "V-Methode direkt vom EditTextObject!" );
//STRIP001 	return XubString();
/*N*/ }

/*N*/ void EditTextObject::Insert( const EditTextObject& rObj, USHORT nPara )
/*N*/ {
/*N*/ 	DBG_ERROR( "V-Methode direkt vom EditTextObject!" );
/*N*/ }

//STRIP001 EditTextObject* EditTextObject::CreateTextObject( USHORT nPara, USHORT nParas ) const
//STRIP001 {
//STRIP001 	DBG_ERROR( "V-Methode direkt vom EditTextObject!" );
//STRIP001 	return 0;
//STRIP001 }

//STRIP001 void EditTextObject::RemoveParagraph( USHORT nPara )
//STRIP001 {
//STRIP001 	DBG_ERROR( "V-Methode direkt vom EditTextObject!" );
//STRIP001 }

//STRIP001 BOOL EditTextObject::HasPortionInfo() const
//STRIP001 {
//STRIP001 	DBG_ERROR( "V-Methode direkt vom EditTextObject!" );
//STRIP001 	return FALSE;
//STRIP001 }

/*N*/ void EditTextObject::ClearPortionInfo()
/*N*/ {
/*N*/ 	DBG_ERROR( "V-Methode direkt vom EditTextObject!" );
/*N*/ }

//STRIP001 BOOL EditTextObject::HasOnlineSpellErrors() const
//STRIP001 {
//STRIP001 	DBG_ERROR( "V-Methode direkt vom EditTextObject!" );
//STRIP001 	return FALSE;
//STRIP001 }

//STRIP001 BOOL EditTextObject::HasCharAttribs( USHORT nWhich ) const
//STRIP001 {
//STRIP001 	DBG_ERROR( "V-Methode direkt vom EditTextObject!" );
//STRIP001 	return FALSE;
//STRIP001 }

//STRIP001 void EditTextObject::GetCharAttribs( USHORT nPara, EECharAttribArray& rLst ) const
//STRIP001 {
//STRIP001 	DBG_ERROR( "V-Methode direkt vom EditTextObject!" );
//STRIP001 }

/*N*/ void EditTextObject::MergeParaAttribs( const SfxItemSet& rAttribs, USHORT nStart, USHORT nEnd )
/*N*/ {
/*N*/ 	DBG_ERROR( "V-Methode direkt vom EditTextObject!" );
/*N*/ }

//STRIP001 BOOL EditTextObject::IsFieldObject() const
//STRIP001 {
//STRIP001 	DBG_ERROR( "V-Methode direkt vom EditTextObject!" );
//STRIP001 	return FALSE;
//STRIP001 }

//STRIP001 const SvxFieldItem* EditTextObject::GetField() const
//STRIP001 {
//STRIP001 	DBG_ERROR( "V-Methode direkt vom EditTextObject!" );
//STRIP001 	return 0;
//STRIP001 }

/*N*/ BOOL EditTextObject::HasField( TypeId aType ) const
/*N*/ {
/*N*/ 	DBG_ERROR( "V-Methode direkt vom EditTextObject!" );
/*N*/ 	return FALSE;
/*N*/ }

/*N*/ SfxItemSet EditTextObject::GetParaAttribs( USHORT nPara ) const
/*N*/ {
/*N*/ 	DBG_ERROR( "V-Methode direkt vom EditTextObject!" );
/*N*/ 	return SfxItemSet( *(SfxItemPool*)NULL );
/*N*/ }

//STRIP001 void EditTextObject::SetParaAttribs( USHORT nPara, const SfxItemSet& rAttribs )
//STRIP001 {
//STRIP001 	DBG_ERROR( "V-Methode direkt vom EditTextObject!" );
//STRIP001 }

//STRIP001 BOOL EditTextObject::RemoveCharAttribs( USHORT nWhich )
//STRIP001 {
//STRIP001 	DBG_ERROR( "V-Methode direkt vom EditTextObject!" );
//STRIP001 	return FALSE;
//STRIP001 }

//STRIP001 BOOL EditTextObject::RemoveParaAttribs( USHORT nWhich )
//STRIP001 {
//STRIP001 	DBG_ERROR( "V-Methode direkt vom EditTextObject!" );
//STRIP001 	return FALSE;
//STRIP001 }

//STRIP001 BOOL EditTextObject::HasStyleSheet( const XubString& rName, SfxStyleFamily eFamily ) const
//STRIP001 {
//STRIP001 	DBG_ERROR( "V-Methode direkt vom EditTextObject!" );
//STRIP001 	return FALSE;
//STRIP001 }

/*N*/ void EditTextObject::GetStyleSheet( USHORT nPara, XubString& rName, SfxStyleFamily& eFamily ) const
/*N*/ {
/*N*/ 	DBG_ERROR( "V-Methode direkt vom EditTextObject!" );
/*N*/ }

/*N*/ void EditTextObject::SetStyleSheet( USHORT nPara, const XubString& rName, const SfxStyleFamily& eFamily )
/*N*/ {
/*N*/ 	DBG_ERROR( "V-Methode direkt vom EditTextObject!" );
/*N*/ }

/*N*/ BOOL __EXPORT EditTextObject::ChangeStyleSheets( const XubString&, SfxStyleFamily,
/*N*/ 											const XubString&, SfxStyleFamily )
/*N*/ {
/*N*/ 	DBG_ERROR( "V-Methode direkt vom EditTextObject!" );
/*N*/ 	return FALSE;
/*N*/ }

/*N*/ void __EXPORT EditTextObject::ChangeStyleSheetName( SfxStyleFamily eFamily,
/*N*/ 				const XubString& rOldName, const XubString& rNewName )
/*N*/ {
/*N*/ 	DBG_ERROR( "V-Methode direkt vom EditTextObject!" );
/*N*/ }

/*N*/ USHORT EditTextObject::GetUserType() const
/*N*/ {
/*N*/ 	DBG_ERROR( "V-Methode direkt vom EditTextObject!" );
/*N*/ 	return 0;
/*N*/ }

/*N*/ void EditTextObject::SetUserType( USHORT n )
/*N*/ {
/*N*/ 	DBG_ERROR( "V-Methode direkt vom EditTextObject!" );
/*N*/ }

//STRIP001 ULONG EditTextObject::GetObjectSettings() const
//STRIP001 {
//STRIP001 	DBG_ERROR( "V-Methode direkt vom EditTextObject!" );
//STRIP001 	return 0;
//STRIP001 }

//STRIP001 void EditTextObject::SetObjectSettings( ULONG n )
//STRIP001 {
//STRIP001 	DBG_ERROR( "V-Methode direkt vom EditTextObject!" );
//STRIP001 }

/*N*/ BOOL EditTextObject::IsVertical() const
/*N*/ {
/*N*/ 	DBG_ERROR( "V-Methode direkt vom EditTextObject!" );
/*N*/ 	return FALSE;
/*N*/ }

/*N*/ void EditTextObject::SetVertical( BOOL bVertical )
/*N*/ {DBG_BF_ASSERT(0, "STRIP"); //STRIP001 
//STRIP001 	DBG_ERROR( "V-Methode direkt vom EditTextObject!" );
//STRIP001 	((BinTextObject*)this)->SetVertical( bVertical );
/*N*/ }

//STRIP001 USHORT EditTextObject::GetScriptType() const
//STRIP001 {
//STRIP001 	DBG_ERROR( "V-Methode direkt vom EditTextObject!" );
//STRIP001 	return ((const BinTextObject*)this)->GetScriptType();
//STRIP001 }


/*N*/ BOOL EditTextObject::Store( SvStream& rOStream ) const
/*N*/ {
/*N*/ 	if ( rOStream.GetError() )
/*N*/ 		return FALSE;
/*N*/ 
/*N*/ 	// Vorspann:
/*N*/ 	ULONG nStartPos = rOStream.Tell();
/*N*/ 
/*N*/ 	USHORT nWhich = Which();
/*N*/ 	rOStream << nWhich;
/*N*/ 
/*N*/ 	ULONG nStructSz = 0;
/*N*/ 	rOStream << nStructSz;
/*N*/ 
/*N*/ 	// Eigene Daten:
/*N*/ 	StoreData( rOStream );
/*N*/ 
/*N*/ 	// Nachspann:
/*N*/ 	ULONG nEndPos = rOStream.Tell();
/*N*/ 	nStructSz = nEndPos - nStartPos - sizeof( nWhich ) - sizeof( nStructSz );
/*N*/ 	rOStream.Seek( nStartPos + sizeof( nWhich ) );
/*N*/ 	rOStream << nStructSz;
/*N*/ 	rOStream.Seek( nEndPos );
/*N*/ 
/*N*/ 	return rOStream.GetError() ? FALSE : TRUE;
/*N*/ }

/*N*/ EditTextObject*	EditTextObject::Create( SvStream& rIStream, SfxItemPool* pGlobalTextObjectPool )
/*N*/ {
/*N*/ 	ULONG nStartPos = rIStream.Tell();
/*N*/ 
/*N*/ 	// Ertmal sehen, was fuer ein Object...
/*N*/ 	USHORT nWhich;
/*N*/ 	rIStream >> nWhich;
/*N*/ 
/*N*/ 	ULONG nStructSz;
/*N*/ 	rIStream >> nStructSz;
/*N*/ 
/*N*/ 	DBG_ASSERT( ( nWhich == 0x22 /*EE_FORMAT_BIN300*/ ) || ( nWhich == EE_FORMAT_BIN ), "CreateTextObject: Unbekanntes Objekt!" );
/*N*/ 
/*N*/ 	if ( rIStream.GetError() )
/*N*/ 		return NULL;
/*N*/ 
/*N*/ 	EditTextObject* pTxtObj = NULL;
/*N*/ 	switch ( nWhich )
/*N*/ 	{
/*N*/ 		case 0x22 /*BIN300*/:		pTxtObj = new BinTextObject( 0 );
/*N*/ 									((BinTextObject*)pTxtObj)->CreateData300( rIStream );
/*N*/ 									break;
/*N*/ 		case EE_FORMAT_BIN:			pTxtObj = new BinTextObject( pGlobalTextObjectPool );
/*N*/ 									pTxtObj->CreateData( rIStream );
/*N*/ 									break;
/*N*/ 		default:
/*N*/ 		{
/*N*/ 			// Wenn ich das Format nicht kenne, ueberlese ich den Inhalt:
/*?*/ 			rIStream.SetError( EE_READWRITE_WRONGFORMAT );
/*N*/ 		}
/*N*/ 	}
/*N*/ 
/*N*/ 	// Sicherstellen, dass der Stream an der richtigen Stelle hinterlassen wird.
/*N*/ 	ULONG nFullSz = sizeof( nWhich ) + sizeof( nStructSz ) + nStructSz;
/*N*/ 	rIStream.Seek( nStartPos + nFullSz );
/*N*/ 	return pTxtObj;
/*N*/ }

//STRIP001 void EditTextObject::Skip( SvStream& rIStream )
//STRIP001 {
//STRIP001 	ULONG nStartPos = rIStream.Tell();
//STRIP001 
//STRIP001 	USHORT nWhich;
//STRIP001 	rIStream >> nWhich;
//STRIP001 
//STRIP001 	ULONG nStructSz;
//STRIP001 	rIStream >> nStructSz;
//STRIP001 
//STRIP001 	ULONG nFullSz = sizeof( nWhich ) + sizeof( nStructSz ) + nStructSz;
//STRIP001 	rIStream.Seek( nStartPos + nFullSz );
//STRIP001 }

/*N*/ void __EXPORT EditTextObject::StoreData( SvStream& rOStream ) const
/*N*/ {
/*N*/ 	DBG_ERROR( "StoreData: Basisklasse!" );
/*N*/ }

/*N*/ void __EXPORT EditTextObject::CreateData( SvStream& rIStream )
/*N*/ {
/*N*/ 	DBG_ERROR( "CreateData: Basisklasse!" );
/*N*/ }

/*N*/ USHORT EditTextObject::GetVersion() const
/*N*/ {
/*N*/ 	DBG_ERROR( "V-Methode direkt vom EditTextObject!" );
/*N*/ 	return 0;
/*N*/ }

//STRIP001 void EditTextObject::SetLRSpaceItemFlags( BOOL bOutlineMode )
//STRIP001 {
//STRIP001 	DBG_ERROR( "V-Methode direkt vom EditTextObject!" );
//STRIP001 }

/*N*/ void EditTextObject::AdjustImportedLRSpaceItems( BOOL bTurnOfBullets )
/*N*/ {
/*N*/ 	DBG_ERROR( "V-Methode direkt vom EditTextObject!" );
/*N*/ }

/*N*/ void EditTextObject::PrepareStore( SfxStyleSheetPool* pStyleSheetPool )
/*N*/ {
/*N*/ 	DBG_ERROR( "V-Methode direkt vom EditTextObject!" );
/*N*/ }

/*N*/ void EditTextObject::FinishStore()
/*N*/ {
/*N*/ 	DBG_ERROR( "V-Methode direkt vom EditTextObject!" );
/*N*/ }

/*N*/ void EditTextObject::FinishLoad( SfxStyleSheetPool* pStyleSheetPool )
/*N*/ {
/*N*/ 	DBG_ERROR( "V-Methode direkt vom EditTextObject!" );
/*N*/ }

/*N*/ BinTextObject::BinTextObject( SfxItemPool* pP ) :
/*N*/ 	EditTextObject( EE_FORMAT_BIN )
/*N*/ {
/*N*/ 	nVersion = 0;
/*N*/ 	nMetric = 0xFFFF;
/*N*/ 	nUserType = 0;
/*N*/ 	nObjSettings = 0;
/*N*/ 	pPortionInfo = 0;
/*N*/ 	if ( pP )
/*N*/ 	{
/*N*/ 		pPool =	pP;
/*N*/ 		bOwnerOfPool = FALSE;
/*N*/ 	}
/*N*/ 	else
/*N*/ 	{
/*N*/ 		pPool =	EditEngine::CreatePool();
/*N*/ 		bOwnerOfPool =	TRUE;
/*N*/ 	}
/*N*/ 	bVertical = FALSE;
/*N*/ 	bStoreUnicodeStrings = FALSE;
/*N*/ 	nScriptType = 0;
/*N*/ }

/*N*/ BinTextObject::BinTextObject( const BinTextObject& r ) :
/*N*/ 	EditTextObject( r )
/*N*/ {
/*N*/ 	nVersion = r.nVersion;
/*N*/ 	nMetric = r.nMetric;
/*N*/ 	nUserType = r.nUserType;
/*N*/ 	nObjSettings = r.nObjSettings;
/*N*/ 	bVertical = r.bVertical;
/*N*/ 	nScriptType = r.nScriptType;
/*N*/ 	pPortionInfo = NULL;	// PortionInfo nicht kopieren
/*N*/ 	bStoreUnicodeStrings = FALSE;
/*N*/ 	if ( !r.bOwnerOfPool )
/*N*/ 	{
/*N*/ 		// Dann den Pool mitverwenden
/*N*/ 		pPool =	r.pPool;
/*N*/ 		bOwnerOfPool = FALSE;
/*N*/ 	}
/*N*/ 	else
/*N*/ 	{
/*N*/ 		pPool =	EditEngine::CreatePool();
/*N*/ 		bOwnerOfPool =	TRUE;
/*N*/ 
/*N*/ 	}
/*N*/ 
/*N*/ 	if ( bOwnerOfPool && pPool && r.pPool )
/*N*/ 		pPool->SetDefaultMetric( r.pPool->GetMetric( DEF_METRIC ) );
/*N*/ 
/*N*/ 	for ( USHORT n = 0; n < r.aContents.Count(); n++ )
/*N*/ 	{
/*N*/ 		ContentInfo* pOrg = r.aContents.GetObject( n );
/*N*/ 		DBG_ASSERT( pOrg, "NULL-Pointer in ContentList!" );
/*N*/ 		ContentInfo* pNew = new ContentInfo( *pOrg, *pPool );
/*N*/ 		aContents.Insert( pNew, aContents.Count() );
/*N*/ 	}
/*N*/ }

/*N*/ __EXPORT BinTextObject::~BinTextObject()
/*N*/ {
/*N*/ 	ClearPortionInfo();
/*N*/ 	DeleteContents();
/*N*/ 	if ( bOwnerOfPool )
/*N*/ 	{
/*N*/ 		// Nicht mehr, wegen 1xDefItems.
/*N*/ 		// siehe auch ~EditDoc().
/*N*/ //		pPool->ReleaseDefaults( TRUE /* bDelete */ );
/*N*/ 		delete pPool;
/*N*/ 	}
/*N*/ }

/*N*/ USHORT BinTextObject::GetUserType() const
/*N*/ {
/*N*/ 	return nUserType;
/*N*/ }

/*N*/ void BinTextObject::SetUserType( USHORT n )
/*N*/ {
/*N*/ 	nUserType = n;
/*N*/ }

//STRIP001 ULONG BinTextObject::GetObjectSettings() const
//STRIP001 {
//STRIP001 	return nObjSettings;
//STRIP001 }

//STRIP001 void BinTextObject::SetObjectSettings( ULONG n )
//STRIP001 {
//STRIP001 	nObjSettings = n;
//STRIP001 }

/*N*/ BOOL BinTextObject::IsVertical() const
/*N*/ {
/*N*/ 	return bVertical;
/*N*/ }

/*N*/ void BinTextObject::SetVertical( BOOL b )
/*N*/ {
/*N*/ 	if ( b != bVertical )
/*N*/ 	{
/*?*/ 		bVertical = b;
/*?*/ 		ClearPortionInfo();
/*N*/ 	}
/*N*/ }

//STRIP001 USHORT BinTextObject::GetScriptType() const
//STRIP001 {
//STRIP001 	return nScriptType;
//STRIP001 }

/*N*/ void BinTextObject::SetScriptType( USHORT nType )
/*N*/ {
/*N*/ 	nScriptType = nType;
/*N*/ }


/*N*/ void BinTextObject::DeleteContents()
/*N*/ {
/*N*/ 	for ( USHORT n = 0; n < aContents.Count(); n++ )
/*N*/ 	{
/*N*/ 		ContentInfo* p = aContents.GetObject( n );
/*N*/ 		DBG_ASSERT( p, "NULL-Pointer in ContentList!" );
/*N*/ 		delete p;
/*N*/ 	}
/*N*/ 	aContents.Remove( 0, aContents.Count() );
/*N*/ }

/*N*/ EditTextObject*	__EXPORT BinTextObject::Clone() const
/*N*/ {
/*N*/ 	return new BinTextObject( *this );
/*N*/ }

/*N*/ XEditAttribute* BinTextObject::CreateAttrib( const SfxPoolItem& rItem, USHORT nStart, USHORT nEnd )
/*N*/ {
/*N*/ 	return MakeXEditAttribute( *pPool, rItem, nStart, nEnd );
/*N*/ }

/*N*/ void BinTextObject::DestroyAttrib( XEditAttribute* pAttr )
/*N*/ {
/*N*/ 	pPool->Remove( *pAttr->GetItem() );
/*N*/ 	delete pAttr;
/*N*/ }

/*N*/ ContentInfo* BinTextObject::CreateAndInsertContent()
/*N*/ {
/*N*/ 	ContentInfo* pC = new ContentInfo( *pPool );
/*N*/ 	aContents.Insert( pC, aContents.Count() );
/*N*/ 	return pC;
/*N*/ }

/*N*/ USHORT BinTextObject::GetParagraphCount() const
/*N*/ {
/*N*/ 	return aContents.Count();
/*N*/ }

/*N*/ XubString BinTextObject::GetText( USHORT nPara ) const
/*N*/ {
/*N*/ 	DBG_ASSERT( nPara < aContents.Count(), "BinTextObject::GetText: Absatz existiert nicht!" );
/*N*/ 	if ( nPara < aContents.Count() )
/*N*/ 	{
/*N*/ 		ContentInfo* pC = aContents[ nPara ];
/*N*/ 		return pC->GetText();
/*N*/ 	}
/*?*/ 	return XubString();
/*N*/ }

/*N*/ void BinTextObject::Insert( const EditTextObject& rObj, USHORT nDestPara )
/*N*/ {
/*N*/ 	DBG_ASSERT( rObj.Which() == EE_FORMAT_BIN, "UTO: Unbekanntes Textobjekt" );
/*N*/ 
/*N*/ 	const BinTextObject& rBinObj = (const BinTextObject&)rObj;
/*N*/ 
/*N*/ 	if ( nDestPara > aContents.Count() )
/*N*/ 		nDestPara = aContents.Count();
/*N*/ 
/*N*/ 	const USHORT nParas = rBinObj.GetContents().Count();
/*N*/ 	for ( USHORT nP = 0; nP < nParas; nP++ )
/*N*/ 	{
/*N*/ 		ContentInfo* pC = rBinObj.GetContents()[ nP ];
/*N*/ 		ContentInfo* pNew = new ContentInfo( *pC, *GetPool() );
/*N*/ 		aContents.Insert( pNew, nDestPara+nP );
/*N*/ 	}
/*N*/ 	ClearPortionInfo();
/*N*/ }

//STRIP001 EditTextObject* BinTextObject::CreateTextObject( USHORT nPara, USHORT nParas ) const
//STRIP001 {
//STRIP001 	if ( ( nPara >= aContents.Count() ) || !nParas )
//STRIP001 		return NULL;
//STRIP001 
//STRIP001 	// Pool nur teilen, wenn von aussen eingestellter Pool.
//STRIP001 	BinTextObject* pObj = new BinTextObject( bOwnerOfPool ? 0 : pPool );
//STRIP001 	if ( bOwnerOfPool && pPool )
//STRIP001 		pObj->GetPool()->SetDefaultMetric( pPool->GetMetric( DEF_METRIC ) );
//STRIP001 
//STRIP001 	// If complete text is only one ScriptType, this is valid.
//STRIP001 	// If text contains different ScriptTypes, this shouldn't be a problem...
//STRIP001 	pObj->nScriptType = nScriptType;
//STRIP001 
//STRIP001 	const USHORT nEndPara = nPara+nParas-1;
//STRIP001 	for ( USHORT nP = nPara; nP <= nEndPara; nP++ )
//STRIP001 	{
//STRIP001 		ContentInfo* pC = aContents[ nP ];
//STRIP001 		ContentInfo* pNew = new ContentInfo( *pC, *pObj->GetPool() );
//STRIP001 		pObj->GetContents().Insert( pNew, pObj->GetContents().Count() );
//STRIP001 	}
//STRIP001 	return pObj;
//STRIP001 }

//STRIP001 void BinTextObject::RemoveParagraph( USHORT nPara )
//STRIP001 {
//STRIP001 	DBG_ASSERT( nPara < aContents.Count(), "BinTextObject::GetText: Absatz existiert nicht!" );
//STRIP001 	if ( nPara < aContents.Count() )
//STRIP001 	{
//STRIP001 		ContentInfo* pC = aContents[ nPara ];
//STRIP001 		aContents.Remove( nPara );
//STRIP001 		delete pC;
//STRIP001 		ClearPortionInfo();
//STRIP001 	}
//STRIP001 }

//STRIP001 BOOL BinTextObject::HasPortionInfo() const
//STRIP001 {
//STRIP001 	return pPortionInfo ? TRUE : FALSE;
//STRIP001 }

/*N*/ void BinTextObject::ClearPortionInfo()
/*N*/ {
/*N*/ 	if ( pPortionInfo )
/*N*/ 	{
/*?*/ 		for ( USHORT n = pPortionInfo->Count(); n; )
/*?*/ 			delete pPortionInfo->GetObject( --n );
/*?*/ 		delete pPortionInfo;
/*?*/ 		pPortionInfo = NULL;
/*N*/ 	}
/*N*/ }

//STRIP001 BOOL BinTextObject::HasOnlineSpellErrors() const
//STRIP001 {
//STRIP001 #ifndef SVX_LIGHT
//STRIP001 	for ( USHORT n = 0; n < aContents.Count(); n++ )
//STRIP001 	{
//STRIP001 		ContentInfo* p = aContents.GetObject( n );
//STRIP001 		if ( p->GetWrongList() && p->GetWrongList()->Count() )
//STRIP001 			return TRUE;
//STRIP001 	}
//STRIP001 #endif // !SVX_LIGHT
//STRIP001 	return FALSE;
//STRIP001 
//STRIP001 }

//STRIP001 BOOL BinTextObject::HasCharAttribs( USHORT nWhich ) const
//STRIP001 {
//STRIP001 	for ( USHORT nPara = GetContents().Count(); nPara; )
//STRIP001 	{
//STRIP001 		ContentInfo* pC = GetContents().GetObject( --nPara );
//STRIP001 
//STRIP001 		USHORT nAttribs = pC->GetAttribs().Count();
//STRIP001 		if ( nAttribs && !nWhich )
//STRIP001 			return TRUE;
//STRIP001 
//STRIP001 		for ( USHORT nAttr = nAttribs; nAttr; )
//STRIP001 		{
//STRIP001 			XEditAttribute* pX = pC->GetAttribs().GetObject( --nAttr );
//STRIP001 			if ( pX->GetItem()->Which() == nWhich )
//STRIP001 				return TRUE;
//STRIP001 		}
//STRIP001 	}
//STRIP001 	return FALSE;
//STRIP001 }

//STRIP001 void BinTextObject::GetCharAttribs( USHORT nPara, EECharAttribArray& rLst ) const
//STRIP001 {
//STRIP001 	rLst.Remove( 0, rLst.Count() );
//STRIP001 	ContentInfo* pC = GetContents().GetObject( nPara );
//STRIP001 	if ( pC )
//STRIP001 	{
//STRIP001 		for ( USHORT nAttr = 0; nAttr < pC->GetAttribs().Count(); nAttr++ )
//STRIP001 		{
//STRIP001 			XEditAttribute* pAttr = pC->GetAttribs().GetObject( nAttr );
//STRIP001 			EECharAttrib aEEAttr;
//STRIP001 			aEEAttr.pAttr = pAttr->GetItem();
//STRIP001 			aEEAttr.nPara = nPara;
//STRIP001 			aEEAttr.nStart = pAttr->GetStart();
//STRIP001 			aEEAttr.nEnd = pAttr->GetEnd();
//STRIP001 			rLst.Insert( aEEAttr, rLst.Count() );
//STRIP001 		}
//STRIP001 	}
//STRIP001 }

/*N*/ void BinTextObject::MergeParaAttribs( const SfxItemSet& rAttribs, USHORT nStart, USHORT nEnd )
/*N*/ {
/*N*/ 	BOOL bChanged = FALSE;
/*N*/ 
/*N*/ 	for ( USHORT nPara = GetContents().Count(); nPara; )
/*N*/ 	{
/*N*/ 		ContentInfo* pC = GetContents().GetObject( --nPara );
/*N*/ 
/*N*/ 		for ( USHORT nW = nStart; nW <= nEnd; nW++ )
/*N*/ 		{
/*N*/ 			if ( ( pC->GetParaAttribs().GetItemState( nW, FALSE ) != SFX_ITEM_ON )
/*N*/ 					&& ( rAttribs.GetItemState( nW, FALSE ) == SFX_ITEM_ON ) )
/*N*/ 			{
/*N*/ 				pC->GetParaAttribs().Put( rAttribs.Get( nW ) );
/*N*/ 				bChanged = TRUE;
/*N*/ 			}
/*N*/ 		}
/*N*/ 	}
/*N*/ 
/*N*/ 	if ( bChanged )
/*N*/ 		ClearPortionInfo();
/*N*/ }

//STRIP001 BOOL BinTextObject::IsFieldObject() const
//STRIP001 {
//STRIP001 	return BinTextObject::GetField() ? TRUE : FALSE;
//STRIP001 }

//STRIP001 const SvxFieldItem* BinTextObject::GetField() const
//STRIP001 {
//STRIP001 	if ( GetContents().Count() == 1 )
//STRIP001 	{
//STRIP001 		ContentInfo* pC = GetContents()[0];
//STRIP001 		if ( pC->GetText().Len() == 1 )
//STRIP001 		{
//STRIP001 			USHORT nAttribs = pC->GetAttribs().Count();
//STRIP001 			for ( USHORT nAttr = nAttribs; nAttr; )
//STRIP001 			{
//STRIP001 				XEditAttribute* pX = pC->GetAttribs().GetObject( --nAttr );
//STRIP001 				if ( pX->GetItem()->Which() == EE_FEATURE_FIELD )
//STRIP001 					return (const SvxFieldItem*)pX->GetItem();
//STRIP001 			}
//STRIP001 		}
//STRIP001 	}
//STRIP001 	return 0;
//STRIP001 }

/*N*/ BOOL BinTextObject::HasField( TypeId aType ) const
/*N*/ {
/*N*/ 	USHORT nParagraphs = GetContents().Count();
/*N*/ 	for ( USHORT nPara = 0; nPara < nParagraphs; nPara++ )
/*N*/ 	{
/*N*/ 		ContentInfo* pC = GetContents().GetObject( nPara );
/*N*/ 		USHORT nAttrs = pC->GetAttribs().Count();
/*N*/ 		for ( USHORT nAttr = 0; nAttr < nAttrs; nAttr++ )
/*N*/ 		{
/*N*/ 			XEditAttribute* pAttr = pC->GetAttribs()[nAttr];
/*N*/ 			if ( pAttr->GetItem()->Which() == EE_FEATURE_FIELD )
/*N*/ 			{
/*N*/ 				if ( !aType )
/*N*/ 					return TRUE;
/*N*/ 
/*N*/ 				const SvxFieldData* pFldData = ((const SvxFieldItem*)pAttr->GetItem())->GetField();
/*N*/ 				if ( pFldData && pFldData->IsA( aType ) )
/*N*/ 					return TRUE;
/*N*/ 			}
/*N*/ 		}
/*N*/ 	}
/*N*/ 	return FALSE;
/*N*/ }

/*N*/ SfxItemSet BinTextObject::GetParaAttribs( USHORT nPara ) const
/*N*/ {
/*N*/ 	ContentInfo* pC = GetContents().GetObject( nPara );
/*N*/ 	return pC->GetParaAttribs();
/*N*/ }

//STRIP001 void BinTextObject::SetParaAttribs( USHORT nPara, const SfxItemSet& rAttribs )
//STRIP001 {
//STRIP001 	ContentInfo* pC = GetContents().GetObject( nPara );
//STRIP001 	pC->GetParaAttribs().Set( rAttribs );
//STRIP001 	ClearPortionInfo();
//STRIP001 }

//STRIP001 BOOL BinTextObject::RemoveCharAttribs( USHORT nWhich )
//STRIP001 {
//STRIP001 	BOOL bChanged = FALSE;
//STRIP001 
//STRIP001 	for ( USHORT nPara = GetContents().Count(); nPara; )
//STRIP001 	{
//STRIP001 		ContentInfo* pC = GetContents().GetObject( --nPara );
//STRIP001 
//STRIP001 		for ( USHORT nAttr = pC->GetAttribs().Count(); nAttr; )
//STRIP001 		{
//STRIP001 			XEditAttribute* pAttr = pC->GetAttribs().GetObject( --nAttr );
//STRIP001 			if ( !nWhich || ( pAttr->GetItem()->Which() == nWhich ) )
//STRIP001 			{
//STRIP001 				pC->GetAttribs().Remove( nAttr );
//STRIP001 				DestroyAttrib( pAttr );
//STRIP001 				bChanged = TRUE;
//STRIP001 			}
//STRIP001 		}
//STRIP001 	}
//STRIP001 
//STRIP001 	if ( bChanged )
//STRIP001 		ClearPortionInfo();
//STRIP001 
//STRIP001 	return bChanged;
//STRIP001 }

//STRIP001 BOOL BinTextObject::RemoveParaAttribs( USHORT nWhich )
//STRIP001 {
//STRIP001 	BOOL bChanged = FALSE;
//STRIP001 
//STRIP001 	for ( USHORT nPara = GetContents().Count(); nPara; )
//STRIP001 	{
//STRIP001 		ContentInfo* pC = GetContents().GetObject( --nPara );
//STRIP001 
//STRIP001 		if ( !nWhich )
//STRIP001 		{
//STRIP001 			if( pC->GetParaAttribs().Count() )
//STRIP001 				bChanged = TRUE;
//STRIP001 			pC->GetParaAttribs().ClearItem();
//STRIP001 		}
//STRIP001 		else
//STRIP001 		{
//STRIP001 			if ( pC->GetParaAttribs().GetItemState( nWhich ) == SFX_ITEM_ON )
//STRIP001 			{
//STRIP001 				pC->GetParaAttribs().ClearItem( nWhich );
//STRIP001 				bChanged = TRUE;
//STRIP001 			}
//STRIP001 		}
//STRIP001 	}
//STRIP001 
//STRIP001 	if ( bChanged )
//STRIP001 		ClearPortionInfo();
//STRIP001 
//STRIP001 	return bChanged;
//STRIP001 }

//STRIP001 BOOL BinTextObject::HasStyleSheet( const XubString& rName, SfxStyleFamily eFamily ) const
//STRIP001 {
//STRIP001 	USHORT nParagraphs = GetContents().Count();
//STRIP001 	for ( USHORT nPara = 0; nPara < nParagraphs; nPara++ )
//STRIP001 	{
//STRIP001 		ContentInfo* pC = GetContents().GetObject( nPara );
//STRIP001 		if ( ( pC->GetFamily() == eFamily ) && ( pC->GetStyle() == rName ) )
//STRIP001 			return TRUE;
//STRIP001 	}
//STRIP001 	return FALSE;
//STRIP001 }

/*N*/ void BinTextObject::GetStyleSheet( USHORT nPara, XubString& rName, SfxStyleFamily& rFamily ) const
/*N*/ {
/*N*/ 	if ( nPara < aContents.Count() )
/*N*/ 	{
/*N*/ 		ContentInfo* pC = aContents[ nPara ];
/*N*/ 		rName = pC->GetStyle();
/*N*/ 		rFamily = pC->GetFamily();
/*N*/ 	}
/*N*/ }

/*N*/ void BinTextObject::SetStyleSheet( USHORT nPara, const XubString& rName, const SfxStyleFamily& rFamily )
/*N*/ {DBG_BF_ASSERT(0, "STRIP"); //STRIP001 
//STRIP001 	if ( nPara < aContents.Count() )
//STRIP001 	{
//STRIP001 		ContentInfo* pC = aContents[ nPara ];
//STRIP001 		pC->GetStyle() = rName;
//STRIP001 		pC->GetFamily() = rFamily;
//STRIP001 	}
/*N*/ }

/*N*/ BOOL BinTextObject::ImpChangeStyleSheets(
/*N*/ 					const XubString& rOldName, SfxStyleFamily eOldFamily,
/*N*/ 					const XubString& rNewName, SfxStyleFamily eNewFamily )
/*N*/ {
/*N*/ 	const USHORT nParagraphs = GetContents().Count();
/*N*/ 	BOOL bChanges = FALSE;
/*N*/ 
/*N*/ 	for ( USHORT nPara = 0; nPara < nParagraphs; nPara++ )
/*N*/ 	{
/*N*/ 		ContentInfo* pC = GetContents().GetObject( nPara );
/*N*/ 		if ( pC->GetFamily() == eOldFamily )
/*N*/ 		{
/*N*/ 			if ( pC->GetStyle() == rOldName )
/*N*/ 			{
/*N*/ 				pC->GetStyle() = rNewName;
/*N*/ 				pC->GetFamily() = eNewFamily;
/*N*/ 				bChanges = TRUE;
/*N*/ 			}
/*N*/ 		}
/*N*/ 	}
/*N*/ 	return bChanges;
/*N*/ }

/*N*/ BOOL __EXPORT BinTextObject::ChangeStyleSheets(
/*N*/ 					const XubString& rOldName, SfxStyleFamily eOldFamily,
/*N*/ 					const XubString& rNewName, SfxStyleFamily eNewFamily )
/*N*/ {
/*N*/ 	BOOL bChanges = ImpChangeStyleSheets( rOldName, eOldFamily, rNewName, eNewFamily );
/*N*/ 	if ( bChanges )
/*N*/ 		ClearPortionInfo();
/*N*/ 
/*N*/ 	return bChanges;
/*N*/ }

/*N*/ void __EXPORT BinTextObject::ChangeStyleSheetName( SfxStyleFamily eFamily,
/*N*/ 				const XubString& rOldName, const XubString& rNewName )
/*N*/ {
/*N*/ 	ImpChangeStyleSheets( rOldName, eFamily, rNewName, eFamily );
/*N*/ }

/*N*/ void __EXPORT BinTextObject::StoreData( SvStream& rOStream ) const
/*N*/ {
/*N*/ 	USHORT nVer = 602;
/*N*/ 	rOStream << nVer;
/*N*/ 
/*N*/ 	rOStream << bOwnerOfPool;
/*N*/ 
/*N*/ 	// Erst den Pool speichern, spaeter nur noch Surregate
/*N*/ 	if ( bOwnerOfPool )
/*N*/ 	{
/*N*/ 		GetPool()->SetFileFormatVersion( SOFFICE_FILEFORMAT_50 );
/*N*/ 		GetPool()->Store( rOStream );
/*N*/ 	}
/*N*/ 
/*N*/ 	// Aktuelle Zeichensatz speichern...
/*N*/ 	// #90477# GetSOStoreTextEncoding: Bug in 5.2, when default char set is multi byte text encoding
/*N*/ 	rtl_TextEncoding eEncoding = GetSOStoreTextEncoding( gsl_getSystemTextEncoding(), (USHORT) rOStream.GetVersion() );
/*N*/ 	rOStream << (USHORT) eEncoding;
/*N*/ 
/*N*/ 	// Die Anzahl der Absaetze...
/*N*/ 	USHORT nParagraphs = GetContents().Count();
/*N*/ 	rOStream << nParagraphs;
/*N*/ 
/*N*/ 	char cFeatureConverted = ByteString( CH_FEATURE, eEncoding ).GetChar(0);
/*N*/ 
/*N*/ 	// Die einzelnen Absaetze...
/*N*/ 	for ( USHORT nPara = 0; nPara < nParagraphs; nPara++ )
/*N*/ 	{
/*N*/ 		ContentInfo* pC = GetContents().GetObject( nPara );
/*N*/ 
/*N*/ 		// Text...
/*N*/ 		ByteString aText( pC->GetText(), eEncoding );
/*N*/ 
/*N*/         // Symbols?
/*N*/         BOOL bSymbolPara = FALSE;
/*N*/         if ( pC->GetLoadStoreTempInfos() && pC->GetLoadStoreTempInfos()->bSymbolParagraph_Store )
/*N*/         {
/*?*/             DBG_ASSERT( pC->GetParaAttribs().GetItemState( EE_CHAR_FONTINFO ) != SFX_ITEM_ON, "Why bSymbolParagraph_Store?" );
/*?*/ 		    aText = ByteString( pC->GetText(), RTL_TEXTENCODING_SYMBOL );
/*?*/             bSymbolPara = TRUE;
/*N*/         }
/*N*/         else if ( pC->GetParaAttribs().GetItemState( EE_CHAR_FONTINFO ) == SFX_ITEM_ON )
/*N*/         {
/*N*/             const SvxFontItem& rFontItem = (const SvxFontItem&)pC->GetParaAttribs().Get( EE_CHAR_FONTINFO );
/*N*/             if ( rFontItem.GetCharSet() == RTL_TEXTENCODING_SYMBOL )
/*N*/             {
/*?*/ 		        aText = ByteString( pC->GetText(), RTL_TEXTENCODING_SYMBOL );
/*?*/                 bSymbolPara = TRUE;
/*N*/             }
/*N*/         }
/*N*/ 		for ( USHORT nA = 0; nA < pC->GetAttribs().Count(); nA++ )
/*N*/ 		{
/*N*/ 			XEditAttribute* pAttr = pC->GetAttribs().GetObject( nA );
/*N*/ 
/*N*/ 			if ( pAttr->GetItem()->Which() == EE_CHAR_FONTINFO )
/*N*/ 			{
/*N*/                 const SvxFontItem& rFontItem = (const SvxFontItem&)*pAttr->GetItem();
/*N*/                 if ( ( !bSymbolPara && ( rFontItem.GetCharSet() == RTL_TEXTENCODING_SYMBOL ) )
/*N*/                       || ( bSymbolPara && ( rFontItem.GetCharSet() != RTL_TEXTENCODING_SYMBOL ) ) )
/*N*/                 {
/*N*/                     // Not correctly converted
/*N*/                     String aPart( pC->GetText(), pAttr->GetStart(), pAttr->GetEnd() - pAttr->GetStart() );
/*N*/                     ByteString aNew( aPart, rFontItem.GetCharSet() );
/*N*/                     aText.Erase( pAttr->GetStart(), pAttr->GetEnd() - pAttr->GetStart() );
/*N*/                     aText.Insert( aNew, pAttr->GetStart() );
/*N*/                 }
/*N*/ 
/*N*/                 // #88414# Convert StarSymbol back to StarBats
/*N*/                 FontToSubsFontConverter hConv = CreateFontToSubsFontConverter( rFontItem.GetFamilyName(), FONTTOSUBSFONT_EXPORT | FONTTOSUBSFONT_ONLYOLDSOSYMBOLFONTS );
/*N*/                 if ( hConv )
/*N*/                 {
/*N*/                     // Don't create a new Attrib with StarBats font, MBR changed the
/*N*/                     // SvxFontItem::Store() to store StarBats instead of StarSymbol!
/*N*/                     for ( USHORT nChar = pAttr->GetStart(); nChar < pAttr->GetEnd(); nChar++ )
/*N*/                     {
/*N*/                         sal_Unicode cOld = pC->GetText().GetChar( nChar );
/*N*/                         char cConv = ByteString::ConvertFromUnicode( ConvertFontToSubsFontChar( hConv, cOld ), RTL_TEXTENCODING_SYMBOL );
/*N*/                         if ( cConv )
/*N*/                             aText.SetChar( nChar, cConv );
/*N*/                     }
/*N*/ 
/*N*/                     DestroyFontToSubsFontConverter( hConv );
/*N*/                 }
/*N*/ 			}
/*N*/ 		}
/*N*/ 
/*N*/         // #88414# Convert StarSymbol back to StarBats
/*N*/         // StarSymbol as paragraph attribute or in StyleSheet?
/*N*/ 
/*N*/         FontToSubsFontConverter hConv = NULL;
/*N*/         if ( pC->GetParaAttribs().GetItemState( EE_CHAR_FONTINFO ) == SFX_ITEM_ON )
/*N*/         {
/*N*/             hConv = CreateFontToSubsFontConverter( ((const SvxFontItem&)pC->GetParaAttribs().Get( EE_CHAR_FONTINFO )).GetFamilyName(), FONTTOSUBSFONT_EXPORT | FONTTOSUBSFONT_ONLYOLDSOSYMBOLFONTS );
/*N*/         }
/*N*/         else if ( pC->GetStyle().Len() && pC->GetLoadStoreTempInfos() )
/*N*/         {
/*?*/             hConv = pC->GetLoadStoreTempInfos()->hOldSymbolConv_Store;
/*N*/         }
/*N*/ 
/*N*/         if ( hConv )
/*N*/         {
/*?*/             for ( USHORT nChar = 0; nChar < pC->GetText().Len(); nChar++ )
/*?*/             {
/*?*/                 if ( !pC->GetAttribs().FindAttrib( EE_CHAR_FONTINFO, nChar ) )
/*?*/                 {
/*?*/                     sal_Unicode cOld = pC->GetText().GetChar( nChar );
/*?*/                     char cConv = ByteString::ConvertFromUnicode( ConvertFontToSubsFontChar( hConv, cOld ), RTL_TEXTENCODING_SYMBOL );
/*?*/                     if ( cConv )
/*?*/                         aText.SetChar( nChar, cConv );
/*?*/                 }
/*?*/             }
/*?*/ 
/*?*/             DestroyFontToSubsFontConverter( hConv );
/*?*/ 
/*?*/             if ( pC->GetLoadStoreTempInfos() )
/*?*/                 pC->GetLoadStoreTempInfos()->hOldSymbolConv_Store = NULL;
/*N*/         }
/*N*/ 
/*N*/ 
/*N*/ 		// Convert CH_FEATURE to CH_FEATURE_OLD
/*N*/ 		aText.SearchAndReplaceAll( cFeatureConverted, CH_FEATURE_OLD );
/*N*/ 		rOStream.WriteByteString( aText );
/*N*/ 
/*N*/ 		// StyleName und Family...
/*N*/ 		rOStream.WriteByteString( ByteString( pC->GetStyle(), eEncoding ) );
/*N*/ 		rOStream << (USHORT)pC->GetFamily();
/*N*/ 
/*N*/ 		// Absatzattribute...
/*N*/ 		pC->GetParaAttribs().Store( rOStream );
/*N*/ 
/*N*/ 		// Die Anzahl der Attribute...
/*N*/ 		USHORT nAttribs = pC->GetAttribs().Count();
/*N*/ 		rOStream << nAttribs;
/*N*/ 
/*N*/ 		// Und die einzelnen Attribute
/*N*/ 		// Items als Surregate => immer 8 Byte pro Attrib
/*N*/ 		// Which = 2; Surregat = 2; Start = 2; End = 2;
/*N*/ 		for ( USHORT nAttr = 0; nAttr < nAttribs; nAttr++ )
/*N*/ 		{
/*N*/ 			XEditAttribute* pX = pC->GetAttribs().GetObject( nAttr );
/*N*/ 
/*N*/ 			rOStream << pX->GetItem()->Which();
/*N*/ 			GetPool()->StoreSurrogate( rOStream, pX->GetItem() );
/*N*/ 			rOStream << pX->GetStart();
/*N*/ 			rOStream << pX->GetEnd();
/*N*/ 		}
/*N*/ 	}
/*N*/ 
/*N*/ 	// Ab 400:
/*N*/ 	rOStream << nMetric;
/*N*/ 
/*N*/ 	// Ab 600
/*N*/ 	rOStream << nUserType;
/*N*/ 	rOStream << nObjSettings;
/*N*/ 
/*N*/ 	// Ab 601
/*N*/ 	rOStream << bVertical;
/*N*/ 
/*N*/ 	// Ab 602
/*N*/ 	rOStream << nScriptType;
/*N*/ 
/*N*/ 	rOStream << bStoreUnicodeStrings;
/*N*/ 	if ( bStoreUnicodeStrings )
/*N*/ 	{
/*?*/ 		for ( USHORT nPara = 0; nPara < nParagraphs; nPara++ )
/*?*/ 		{
/*?*/ 			ContentInfo* pC = GetContents().GetObject( nPara );
/*?*/ 			USHORT nL = pC->GetText().Len();
/*?*/ 			rOStream << nL;
/*?*/ 			rOStream.Write( pC->GetText().GetBuffer(), nL*sizeof(sal_Unicode) );
/*?*/ 
/*?*/             // #91575# StyleSheetName must be Unicode too!
/*?*/             // Copy/Paste from EA3 to BETA or from BETA to EA3 not possible, not needed...
/*?*/             // If needed, change nL back to ULONG and increase version...
/*?*/             nL = pC->GetStyle().Len();
/*?*/ 			rOStream << nL;
/*?*/ 			rOStream.Write( pC->GetStyle().GetBuffer(), nL*sizeof(sal_Unicode) );
/*?*/ 		}
/*N*/ 	}
/*N*/ }

/*N*/ void __EXPORT BinTextObject::CreateData( SvStream& rIStream )
/*N*/ {
/*N*/ 	rIStream >> nVersion;
/*N*/ 
/*N*/ 	// Das Textobject wurde erstmal mit der aktuellen Einstellung
/*N*/ 	// von pTextObjectPool erzeugt.
/*N*/ 	BOOL bOwnerOfCurrent = bOwnerOfPool;
/*N*/ 	rIStream >> bOwnerOfPool;
/*N*/ 
/*N*/ 	if ( bOwnerOfCurrent && !bOwnerOfPool )
/*N*/ 	{
/*N*/ 		// Es wurde ein globaler Pool verwendet, mir jetzt nicht uebergeben,
/*N*/ 		// aber ich brauche ihn!
/*?*/ 		DBG_ERROR( "Man gebe mir den globalen TextObjectPool!" );
/*?*/ 		return;
/*N*/ 	}
/*N*/ 	else if ( !bOwnerOfCurrent && bOwnerOfPool )
/*N*/ 	{
/*N*/ 		// Es soll ein globaler Pool verwendet werden, aber dieses
/*N*/ 		// Textobject hat einen eigenen.
/*N*/ 		pPool =	EditEngine::CreatePool();
/*N*/ 	}
/*N*/ 
/*N*/ 	if ( bOwnerOfPool )
/*N*/ 		GetPool()->Load( rIStream );
/*N*/ 
/*N*/ 	// CharSet, in dem gespeichert wurde:
/*N*/ 	USHORT nCharSet;
/*N*/ 	rIStream >> nCharSet;
/*N*/ 
/*N*/ 	rtl_TextEncoding eSrcEncoding = GetSOLoadTextEncoding( (rtl_TextEncoding)nCharSet, (USHORT)rIStream.GetVersion() );
/*N*/ 
/*N*/ 	// Die Anzahl der Absaetze...
/*N*/ 	USHORT nParagraphs;
/*N*/ 	rIStream >> nParagraphs;
/*N*/ 
/*N*/ 	// Die einzelnen Absaetze...
/*N*/ 	for ( ULONG nPara = 0; nPara < nParagraphs; nPara++ )
/*N*/ 	{
/*N*/ 		ContentInfo* pC = CreateAndInsertContent();
/*N*/ 
/*N*/ 		// Der Text...
/*N*/ 		ByteString aByteString;
/*N*/ 		rIStream.ReadByteString( aByteString );
/*N*/ 		pC->GetText() = String( aByteString, eSrcEncoding );
/*N*/ 
/*N*/ 		// StyleName und Family...
/*N*/ 		rIStream.ReadByteString( pC->GetStyle(), eSrcEncoding );
/*N*/ 		USHORT nStyleFamily;
/*N*/ 		rIStream >> nStyleFamily;
/*N*/ 		pC->GetFamily() = (SfxStyleFamily)nStyleFamily;
/*N*/ 
/*N*/ 		// Absatzattribute...
/*N*/ 		pC->GetParaAttribs().Load( rIStream );
/*N*/ 
/*N*/ 		// Die Anzahl der Attribute...
/*N*/ 		USHORT nAttribs;
/*N*/ 		rIStream >> nAttribs;
/*N*/ 
/*N*/ 		// Und die einzelnen Attribute
/*N*/ 		// Items als Surregate => immer 8 Byte pro Attrib
/*N*/ 		// Which = 2; Surregat = 2; Start = 2; End = 2;
/*N*/         USHORT nAttr;
/*N*/ 		for ( nAttr = 0; nAttr < nAttribs; nAttr++ )
/*N*/ 		{
/*N*/ 			USHORT nWhich, nStart, nEnd;
/*N*/ 			const SfxPoolItem* pItem;
/*N*/ 
/*N*/ 			rIStream >> nWhich;
/*N*/ 			nWhich = pPool->GetNewWhich( nWhich );
/*N*/ 			pItem = pPool->LoadSurrogate( rIStream, nWhich, 0 );
/*N*/ 			rIStream >> nStart;
/*N*/ 			rIStream >> nEnd;
/*N*/ 			if ( pItem )
/*N*/ 			{
/*N*/ 				if ( pItem->Which() == EE_FEATURE_NOTCONV )
/*N*/ 				{
/*?*/ 					pC->GetText().SetChar( nStart, ByteString::ConvertToUnicode( aByteString.GetChar( nStart ), ((SvxCharSetColorItem*)pItem)->GetCharSet() ) );
/*N*/ 				}
/*N*/ 				else
/*N*/ 				{
/*N*/ 					XEditAttribute* pAttr = new XEditAttribute( *pItem, nStart, nEnd );
/*N*/ 					pC->GetAttribs().Insert( pAttr, pC->GetAttribs().Count() );
/*N*/ 
/*N*/ 					if ( ( nWhich >= EE_FEATURE_START ) && ( nWhich <= EE_FEATURE_END ) )
/*N*/ 					{
/*N*/ 						// Convert CH_FEATURE to CH_FEATURE_OLD
/*N*/ 						DBG_ASSERT( (BYTE) aByteString.GetChar( nStart ) == CH_FEATURE_OLD, "CreateData: CH_FEATURE expected!" );
/*N*/ 						if ( (BYTE) aByteString.GetChar( nStart ) == CH_FEATURE_OLD )
/*N*/ 							pC->GetText().SetChar( nStart, CH_FEATURE );
/*N*/ 					}
/*N*/ 				}
/*N*/ 			}
/*N*/ 		}
/*N*/ 
/*N*/         // Symbol-Conversion neccessary?
/*N*/         // All Strings are converted with the SourceCharSet in CreateData()...
/*N*/ 
/*N*/         // Keep old ByteString, maybe Symbol-Conversion neccessary, will be
/*N*/         // checked in FinishLoad(), I need the StyleSheetPool for this...
/*N*/         if ( pC->GetStyle().Len() && ( pC->GetParaAttribs().GetItemState( EE_CHAR_FONTINFO ) != SFX_ITEM_ON ) )
/*N*/         {
/*N*/             pC->CreateLoadStoreTempInfos();
/*N*/             pC->GetLoadStoreTempInfos()->aOrgString_Load = aByteString;
/*N*/         }
/*N*/ 
/*N*/         // But check for paragraph and character symbol attribs here,
/*N*/         // FinishLoad will not be called in OpenOffice Calc, no StyleSheets...
/*N*/ 
/*N*/         BOOL bSymbolPara = FALSE;
/*N*/         if ( pC->GetParaAttribs().GetItemState( EE_CHAR_FONTINFO ) == SFX_ITEM_ON )
/*N*/         {
/*N*/             const SvxFontItem& rFontItem = (const SvxFontItem&)pC->GetParaAttribs().Get( EE_CHAR_FONTINFO );
/*N*/             if ( rFontItem.GetCharSet() == RTL_TEXTENCODING_SYMBOL )
/*N*/             {
/*N*/ 		        pC->GetText() = String( aByteString, RTL_TEXTENCODING_SYMBOL );
/*N*/                 bSymbolPara = TRUE;
/*N*/             }
/*N*/         }
/*N*/ 
/*N*/ 		for ( nAttr = pC->GetAttribs().Count(); nAttr; )
/*N*/ 		{
/*N*/ 			XEditAttribute* pAttr = pC->GetAttribs().GetObject( --nAttr );
/*N*/             if ( pAttr->GetItem()->Which() == EE_CHAR_FONTINFO )
/*N*/             {
/*N*/                 const SvxFontItem& rFontItem = (const SvxFontItem&)*pAttr->GetItem();
/*N*/                 if ( ( !bSymbolPara && ( rFontItem.GetCharSet() == RTL_TEXTENCODING_SYMBOL ) )
/*N*/                       || ( bSymbolPara && ( rFontItem.GetCharSet() != RTL_TEXTENCODING_SYMBOL ) ) )
/*N*/                 {
/*N*/                     // Not correctly converted
/*N*/                     ByteString aPart( aByteString, pAttr->GetStart(), pAttr->GetEnd()-pAttr->GetStart() );
/*N*/                     String aNew( aPart, rFontItem.GetCharSet() );
/*N*/                     pC->GetText().Erase( pAttr->GetStart(), pAttr->GetEnd()-pAttr->GetStart() );
/*N*/                     pC->GetText().Insert( aNew, pAttr->GetStart() );
/*N*/                 }
/*N*/ 
/*N*/                 // #88414# Convert StarMath and StarBats to StarSymbol
/*N*/                 FontToSubsFontConverter hConv = CreateFontToSubsFontConverter( rFontItem.GetFamilyName(), FONTTOSUBSFONT_IMPORT | FONTTOSUBSFONT_ONLYOLDSOSYMBOLFONTS );
/*N*/                 if ( hConv )
/*N*/                 {
/*N*/                     SvxFontItem aNewFontItem( rFontItem );
/*N*/ 		            aNewFontItem.GetFamilyName() = GetFontToSubsFontName( hConv );
/*N*/ 
/*N*/                     pC->GetAttribs().Remove( nAttr );
/*N*/                     XEditAttribute* pNewAttr = CreateAttrib( aNewFontItem, pAttr->GetStart(), pAttr->GetEnd() );
/*N*/                     pC->GetAttribs().Insert( pNewAttr, nAttr );
/*N*/                     DestroyAttrib( pAttr );
/*N*/ 
/*N*/                     for ( USHORT nChar = pNewAttr->GetStart(); nChar < pNewAttr->GetEnd(); nChar++ )
/*N*/                     {
/*N*/                         sal_Unicode cOld = pC->GetText().GetChar( nChar );
/*N*/                         DBG_ASSERT( cOld >= 0xF000, "cOld not converted?!" );
/*N*/                         sal_Unicode cConv = ConvertFontToSubsFontChar( hConv, cOld );
/*N*/                         if ( cConv )
/*N*/                             pC->GetText().SetChar( nChar, cConv );
/*N*/                     }
/*N*/ 
/*N*/                     DestroyFontToSubsFontConverter( hConv );
/*N*/                 }
/*N*/             }
/*N*/         }
/*N*/ 
/*N*/ 
/*N*/         // #88414# Convert StarMath and StarBats to StarSymbol
/*N*/         // Maybe old symbol font as paragraph attribute?
/*N*/         if ( pC->GetParaAttribs().GetItemState( EE_CHAR_FONTINFO ) == SFX_ITEM_ON )
/*N*/         {
/*N*/             const SvxFontItem& rFontItem = (const SvxFontItem&)pC->GetParaAttribs().Get( EE_CHAR_FONTINFO );
/*N*/             FontToSubsFontConverter hConv = CreateFontToSubsFontConverter( rFontItem.GetFamilyName(), FONTTOSUBSFONT_IMPORT | FONTTOSUBSFONT_ONLYOLDSOSYMBOLFONTS );
/*N*/             if ( hConv )
/*N*/             {
/*N*/                 SvxFontItem aNewFontItem( rFontItem );
/*N*/ 		        aNewFontItem.GetFamilyName() = GetFontToSubsFontName( hConv );
/*N*/                 pC->GetParaAttribs().Put( aNewFontItem );
/*N*/ 
/*N*/                 for ( USHORT nChar = 0; nChar < pC->GetText().Len(); nChar++ )
/*N*/                 {
/*N*/                     if ( !pC->GetAttribs().FindAttrib( EE_CHAR_FONTINFO, nChar ) )
/*N*/                     {
/*N*/                         sal_Unicode cOld = pC->GetText().GetChar( nChar );
/*N*/                         DBG_ASSERT( cOld >= 0xF000, "cOld not converted?!" );
/*N*/                         sal_Unicode cConv = ConvertFontToSubsFontChar( hConv, cOld );
/*N*/                         if ( cConv )
/*N*/                             pC->GetText().SetChar( nChar, cConv );
/*N*/                     }
/*N*/                 }
/*N*/ 
/*N*/                 DestroyFontToSubsFontConverter( hConv );
/*N*/             }
/*N*/         }
/*N*/     }
/*N*/ 
/*N*/ 	// Ab 400 auch die DefMetric:
/*N*/ 	if ( nVersion >= 400 )
/*N*/ 	{
/*N*/ 		USHORT nTmpMetric;
/*N*/ 		rIStream >> nTmpMetric;
/*N*/ 		if ( nVersion >= 401 )
/*N*/ 		{
/*N*/ 			// In der 400 gab es noch einen Bug bei Textobjekten mit eigenem
/*N*/ 			// Pool, deshalb erst ab 401 auswerten.
/*N*/ 			nMetric = nTmpMetric;
/*N*/ 			if ( bOwnerOfPool && pPool && ( nMetric != 0xFFFF ) )
/*N*/ 				pPool->SetDefaultMetric( (SfxMapUnit)nMetric );
/*N*/ 		}
/*N*/ 	}
/*N*/ 
/*N*/ 	if ( nVersion >= 600 )
/*N*/ 	{
/*N*/ 		rIStream >> nUserType;
/*N*/ 		rIStream >> nObjSettings;
/*N*/ 	}
/*N*/ 
/*N*/ 	if ( nVersion >= 601 )
/*N*/ 	{
/*N*/ 		rIStream >> bVertical;
/*N*/ 	}
/*N*/ 
/*N*/ 	if ( nVersion >= 602 )
/*N*/ 	{
/*N*/ 		rIStream >> nScriptType;
/*N*/ 
/*N*/ 		BOOL bUnicodeStrings;
/*N*/ 		rIStream >> bUnicodeStrings;
/*N*/ 		if ( bUnicodeStrings )
/*N*/ 		{
/*?*/ 			for ( USHORT nPara = 0; nPara < nParagraphs; nPara++ )
/*?*/ 			{
/*?*/ 				ContentInfo* pC = GetContents().GetObject( nPara );
/*?*/ 				USHORT nL;
/*?*/ 
/*?*/                 // Text
/*?*/ 				rIStream >> nL;
/*?*/                 if ( nL )
/*?*/                 {
/*?*/ 				    pC->GetText().AllocBuffer( nL );
/*?*/ 				    rIStream.Read( pC->GetText().GetBufferAccess(), nL*sizeof(sal_Unicode) );
/*?*/ 				    pC->GetText().ReleaseBufferAccess( (USHORT)nL );
/*?*/                 }
/*?*/ 
/*?*/                 // StyleSheetName
/*?*/                 rIStream >> nL;
/*?*/                 if ( nL )
/*?*/                 {
/*?*/ 				    pC->GetStyle().AllocBuffer( nL );
/*?*/ 				    rIStream.Read( pC->GetStyle().GetBufferAccess(), nL*sizeof(sal_Unicode) );
/*?*/ 				    pC->GetStyle().ReleaseBufferAccess( (USHORT)nL );
/*?*/                 }
/*?*/ 			}
/*N*/ 		}
/*N*/ 	}
/*N*/ 
/*N*/ 
/*N*/ 	// Ab 500 werden die Tabs anders interpretiert: TabPos + LI, vorher nur TabPos.
/*N*/ 	// Wirkt nur wenn auch Tab-Positionen eingestellt wurden, nicht beim DefTab.
/*N*/ 	if ( nVersion < 500 )
/*N*/ 	{
/*N*/ 		for ( USHORT n = 0; n < aContents.Count(); n++ )
/*N*/ 		{
/*N*/ 			ContentInfo* pC = aContents.GetObject( n );
/*N*/ 			const SvxLRSpaceItem& rLRSpace = (const SvxLRSpaceItem&) pC->GetParaAttribs().Get( EE_PARA_LRSPACE );
/*N*/ 			if ( rLRSpace.GetTxtLeft() && ( pC->GetParaAttribs().GetItemState( EE_PARA_TABS ) == SFX_ITEM_ON ) )
/*N*/ 			{
/*N*/ 				const SvxTabStopItem& rTabs = (const SvxTabStopItem&) pC->GetParaAttribs().Get( EE_PARA_TABS );
/*N*/ 				SvxTabStopItem aNewTabs( 0, 0, SVX_TAB_ADJUST_LEFT, EE_PARA_TABS );
/*N*/ 				for ( USHORT t = 0; t < rTabs.Count(); t++ )
/*N*/ 				{
/*N*/ 					const SvxTabStop& rT = rTabs[ t ];
/*N*/ 					aNewTabs.Insert( SvxTabStop( rT.GetTabPos() - rLRSpace.GetTxtLeft(),
/*N*/ 								rT.GetAdjustment(), rT.GetDecimal(), rT.GetFill() ) );
/*N*/ 				}
/*N*/ 				pC->GetParaAttribs().Put( aNewTabs );
/*N*/ 			}
/*N*/ 		}
/*N*/ 	}
/*N*/ }

/*N*/ USHORT BinTextObject::GetVersion() const
/*N*/ {
/*N*/ 	return nVersion;
/*N*/ }

//STRIP001 void BinTextObject::SetLRSpaceItemFlags( BOOL bOutlineMode )
//STRIP001 {
//STRIP001 	for ( USHORT nPara = GetContents().Count(); nPara; )
//STRIP001 	{
//STRIP001 		ContentInfo* pC = GetContents().GetObject( --nPara );
//STRIP001 		for ( USHORT n = 0; n <=1; n++ )
//STRIP001 		{
//STRIP001 			USHORT nItemId = n ? EE_PARA_LRSPACE : EE_PARA_OUTLLRSPACE;
//STRIP001 			if ( pC->GetParaAttribs().GetItemState( nItemId ) == SFX_ITEM_ON )
//STRIP001 			{
//STRIP001 				const SvxLRSpaceItem& rItem = (const SvxLRSpaceItem&) pC->GetParaAttribs().Get( nItemId );
//STRIP001 				if ( rItem.IsBulletFI() != bOutlineMode )
//STRIP001 				{
//STRIP001 					SvxLRSpaceItem aNewItem( rItem );
//STRIP001 					aNewItem.SetBulletFI( bOutlineMode );
//STRIP001 					pC->GetParaAttribs().Put( aNewItem );
//STRIP001 				}
//STRIP001 			}
//STRIP001 		}
//STRIP001 	}
//STRIP001 }

/*N*/ void BinTextObject::PrepareStore( SfxStyleSheetPool* pStyleSheetPool )
/*N*/ {
/*N*/ 	// Some Items must be generated for the 5.0 file format,
/*N*/ 	// because we don't have a special format for 5.x or 6.x
/*N*/ 	USHORT nParas = GetContents().Count();
/*N*/ 	const SvxNumBulletItem** ppNumBulletItems = new const SvxNumBulletItem*[nParas];
/*N*/ 	for ( USHORT nPara = nParas; nPara; )
/*N*/ 	{
/*N*/ 		ContentInfo* pC = GetContents().GetObject( --nPara );
/*N*/ 		const SvxNumBulletItem* pSvxNumBulletItem = NULL;
/*N*/ 		const SfxPoolItem* pTmpItem = NULL;
/*N*/ 		if ( pC->GetParaAttribs().GetItemState(EE_PARA_NUMBULLET, FALSE, &pTmpItem ) == SFX_ITEM_ON )
/*N*/ 		{
/*N*/ 			pSvxNumBulletItem = (const SvxNumBulletItem*)pTmpItem;
/*N*/ 		}
/*N*/ 		else if ( pStyleSheetPool && pC->GetStyle().Len() )
/*N*/ 		{
/*N*/ 			SfxStyleSheet* pStyle = (SfxStyleSheet*)pStyleSheetPool->Find( pC->GetStyle(), pC->GetFamily() );
/*N*/ 			if ( pStyle )
/*N*/ 				pSvxNumBulletItem = &(const SvxNumBulletItem&)pStyle->GetItemSet().Get(EE_PARA_NUMBULLET);
/*N*/ 		}
/*N*/ 
/*N*/ 		ppNumBulletItems[nPara] = pSvxNumBulletItem;
/*N*/ 
/*N*/ 		if ( pSvxNumBulletItem )
/*N*/ 		{
/*N*/ 			// Check if Item allready used, don't create a new one in this case.
/*N*/ 			BOOL bInserted = FALSE;
/*N*/ 			for ( USHORT nP = nPara+1; nP < nParas; nP++ )
/*N*/ 			{
/*N*/ 				if ( ppNumBulletItems[nP] == pSvxNumBulletItem )
/*N*/ 				{
/*N*/ 					ContentInfo* pTmpC = GetContents().GetObject( nP );
/*N*/ 					pC->GetParaAttribs().Put( pTmpC->GetParaAttribs().Get( EE_PARA_BULLET ) );
/*N*/ 					bInserted = TRUE;
/*N*/ 					break;
/*N*/ 				}
/*N*/ 			}
/*N*/ 			if ( !bInserted )
/*N*/ 			{
/*N*/ 				SvxBulletItem aNewBullet( EE_PARA_BULLET );
/*N*/ 				const SfxUInt16Item& rLevel = (const SfxUInt16Item&) pC->GetParaAttribs().Get( EE_PARA_OUTLLEVEL );
/*N*/ 				lcl_CreateBulletItem( *pSvxNumBulletItem, rLevel.GetValue(), aNewBullet );
/*N*/ 				pC->GetParaAttribs().Put( aNewBullet );
/*N*/ 			}
/*N*/ 		}
/*N*/ 
/*N*/         // SymbolConvertion because of StyleSheet?
/*N*/         // Cannot be checked in StoreData, no StyleSheetPool, so do it here...
/*N*/ 
/*N*/         pC->DestroyLoadStoreTempInfos();    // Maybe old infos, if somebody is not calling FinishLoad after CreateData, but PrepareStore...
/*N*/ 
/*N*/         if ( ( pC->GetParaAttribs().GetItemState( EE_CHAR_FONTINFO ) != SFX_ITEM_ON ) && pC->aStyle.Len() && pStyleSheetPool )
/*N*/         {
/*N*/             SfxStyleSheet* pStyle = (SfxStyleSheet*)pStyleSheetPool->Find( pC->GetStyle(), pC->GetFamily() );
/*N*/             if ( pStyle )
/*N*/             {
/*N*/                 const SvxFontItem& rFontItem = (const SvxFontItem&)pStyle->GetItemSet().Get( EE_CHAR_FONTINFO );
/*N*/                 if ( rFontItem.GetCharSet() == RTL_TEXTENCODING_SYMBOL )
/*N*/                 {
/*?*/                     if ( !pC->GetLoadStoreTempInfos() )
/*?*/                         pC->CreateLoadStoreTempInfos();
/*?*/                     pC->GetLoadStoreTempInfos()->bSymbolParagraph_Store = TRUE;
/*N*/                 }
/*N*/ 
/*N*/                 FontToSubsFontConverter hConv = CreateFontToSubsFontConverter( rFontItem.GetFamilyName(), FONTTOSUBSFONT_EXPORT | FONTTOSUBSFONT_ONLYOLDSOSYMBOLFONTS );
/*N*/                 if ( hConv )
/*N*/                 {
/*?*/                     // #88414# Convert StarSymbol back to StarBats
/*?*/                     if ( !pC->GetLoadStoreTempInfos() )
/*?*/                         pC->CreateLoadStoreTempInfos();
/*?*/                     pC->GetLoadStoreTempInfos()->hOldSymbolConv_Store = hConv;
/*N*/                 }
/*N*/             }
/*N*/         }
/*N*/  	}
/*N*/ 
/*N*/     delete[] ppNumBulletItems;
/*N*/ }

/*N*/ void BinTextObject::FinishStore()
/*N*/ {
/*N*/ 	for ( USHORT nPara = GetContents().Count(); nPara; )
/*N*/ 	{
/*N*/ 		ContentInfo* pC = GetContents().GetObject( --nPara );
/*N*/ 		pC->GetParaAttribs().ClearItem( EE_PARA_BULLET );
/*N*/ 
/*N*/         pC->DestroyLoadStoreTempInfos();
/*N*/ 	}
/*N*/ }

/*N*/ void BinTextObject::FinishLoad( SfxStyleSheetPool* pStyleSheetPool )
/*N*/ {
/*N*/ 	BOOL bCreateNumBulletItem = nVersion && ( nVersion < 501 );
/*N*/ 	for ( USHORT nPara = GetContents().Count(); nPara; )
/*N*/ 	{
/*N*/ 		ContentInfo* pC = GetContents().GetObject( --nPara );
/*N*/ 
/*N*/ 		if( GetUserType() == 0x0003 ) // !! OUTLINERMODE_OUTLINEOBJECT !!
/*N*/ 		{
/*N*/ 			if ( pC->GetParaAttribs().GetItemState( EE_PARA_NUMBULLET ) == SFX_ITEM_ON )
/*N*/ 			{
/*?*/ 				SvxNumBulletItem* pNumBullet = (SvxNumBulletItem*) &pC->GetParaAttribs().Get( EE_PARA_NUMBULLET );
/*?*/ 				if( pNumBullet->GetNumRule()->GetNumRuleType() != SVX_RULETYPE_PRESENTATION_NUMBERING )
/*?*/ 				{
/*?*/ 					pNumBullet->GetNumRule()->SetNumRuleType( SVX_RULETYPE_PRESENTATION_NUMBERING );
/*?*/ 					pC->GetParaAttribs().Put( *pNumBullet, EE_PARA_NUMBULLET );
/*?*/ 				}
/*N*/ 			}
/*N*/ 		}
/*N*/ 
/*N*/ 		if ( bCreateNumBulletItem )
/*N*/ 		{
/*N*/ 			BOOL bBulletInPara = pC->GetParaAttribs().GetItemState( EE_PARA_BULLET ) == SFX_ITEM_ON;
/*N*/ 			BOOL bLRSpaceInPara = pC->GetParaAttribs().GetItemState( EE_PARA_LRSPACE ) == SFX_ITEM_ON;
/*N*/ 
/*N*/ 			// Nur wenn ein Attribut hart gesetzt, ansonsten muss es in den Vorlagen
/*N*/ 			// richtig konvertiert sein.
/*N*/ 
/*N*/ 			if ( bBulletInPara || bLRSpaceInPara )
/*N*/ 			{
/*N*/ 				const SvxBulletItem* pBullet = NULL;
/*N*/ 				const SvxLRSpaceItem* pLRSpace = NULL;
/*N*/ 				SvxNumBulletItem* pNumBullet = NULL;
/*N*/ 				SfxStyleSheet* pStyle = NULL;
/*N*/ 
/*N*/ 				if ( pC->GetStyle().Len() )
/*N*/ 					pStyle = (SfxStyleSheet*)pStyleSheetPool->Find( pC->GetStyle(), pC->GetFamily() );
/*N*/ 
/*N*/ 				const SfxUInt16Item& rLevel = (const SfxUInt16Item&) pC->GetParaAttribs().Get( EE_PARA_OUTLLEVEL );
/*N*/ 				USHORT nLevel = rLevel.GetValue();
/*N*/ 
/*N*/ 				if ( !pStyle || bBulletInPara )
/*N*/ 					pBullet = (const SvxBulletItem*) &pC->GetParaAttribs().Get( EE_PARA_BULLET );
/*N*/ 				else
/*N*/ 					pBullet = (const SvxBulletItem*) &pStyle->GetItemSet().Get( EE_PARA_BULLET );
/*N*/ 
/*N*/ 				if ( !pStyle || bLRSpaceInPara )
/*N*/ 					pLRSpace = (const SvxLRSpaceItem*) &pC->GetParaAttribs().Get( EE_PARA_LRSPACE );
/*N*/ 				else
/*?*/ 					pLRSpace = (const SvxLRSpaceItem*) &pStyle->GetItemSet().Get( EE_PARA_LRSPACE );
/*N*/ 
/*N*/ 				if ( !pStyle || ( pC->GetParaAttribs().GetItemState( EE_PARA_NUMBULLET ) == SFX_ITEM_ON ) )
/*?*/ 					pNumBullet = (SvxNumBulletItem*) &pC->GetParaAttribs().Get( EE_PARA_NUMBULLET );
/*N*/ 				else
/*N*/ 					pNumBullet = (SvxNumBulletItem*) &pStyle->GetItemSet().Get( EE_PARA_NUMBULLET );
/*N*/ 
/*N*/ 				SvxNumBulletItem aNumBullet( *pNumBullet );
/*N*/ 				EditEngine::ImportBulletItem( aNumBullet, nLevel, pBullet, pLRSpace );
/*N*/ 				pC->GetParaAttribs().Put( aNumBullet );
/*N*/ 
/*N*/ 				if ( bLRSpaceInPara )
/*N*/ 					pC->GetParaAttribs().ClearItem( EE_PARA_LRSPACE );
/*N*/ 			}
/*N*/ 		}
/*N*/ 
/*N*/         // Symbol-Convertion because of StyleSheet?
/*N*/         if ( pStyleSheetPool && pC->GetLoadStoreTempInfos() && pC->GetLoadStoreTempInfos()->aOrgString_Load.Len() )
/*N*/         {
/*N*/             SfxStyleSheet* pStyle = (SfxStyleSheet*)pStyleSheetPool->Find( pC->GetStyle(), pC->GetFamily() );
/*N*/             if ( pStyle )
/*N*/             {
/*N*/                 const SvxFontItem& rFontItem = (const SvxFontItem&)pStyle->GetItemSet().Get( EE_CHAR_FONTINFO );
/*N*/                 if ( rFontItem.GetCharSet() == RTL_TEXTENCODING_SYMBOL )
/*N*/                 {
/*?*/                     String aConverted( pC->GetLoadStoreTempInfos()->aOrgString_Load, RTL_TEXTENCODING_SYMBOL );
/*?*/ 
/*?*/                     // Replace only Parts without hard font attribute, other symbol encoding
/*?*/                     // is already done in CreateData()...
/*?*/ 
/*?*/                     USHORT nLastEnd = 0;
/*?*/                     for ( USHORT nAttr = 0; nAttr < pC->GetAttribs().Count(); nAttr++ )
/*?*/ 		            {
/*?*/ 			            XEditAttribute* pAttr = pC->GetAttribs().GetObject( nAttr );
/*?*/                         if ( pAttr->GetItem()->Which() == EE_CHAR_FONTINFO )
/*?*/                         {
/*?*/                             if ( nLastEnd < pAttr->GetStart() )
/*?*/                             {
/*?*/                                 USHORT nLen = pAttr->GetStart() - nLastEnd;
/*?*/                                 pC->GetText().Erase( nLastEnd, nLen );
/*?*/                                 pC->GetText().Insert( aConverted, nLastEnd, nLen, nLastEnd );
/*?*/                             }
/*?*/                             nLastEnd = pAttr->GetEnd();
/*?*/ 
/*?*/                         }
/*?*/                     }
/*?*/                     if ( nLastEnd < pC->GetText().Len() )
/*?*/                     {
/*?*/                         USHORT nLen = pC->GetText().Len() - nLastEnd;
/*?*/                         pC->GetText().Erase( nLastEnd, nLen );
/*?*/                         pC->GetText().Insert( aConverted, nLastEnd, nLen, nLastEnd );
/*?*/                     }
/*N*/                 }
/*N*/             }
/*N*/         }
/*N*/ 
/*N*/         pC->DestroyLoadStoreTempInfos();
/*N*/ 
/*N*/ 		// MT 07/00: EE_PARA_BULLET no longer needed
/*N*/ 		pC->GetParaAttribs().ClearItem( EE_PARA_BULLET );
/*N*/ 	}
/*N*/ }

/*N*/ void BinTextObject::AdjustImportedLRSpaceItems( BOOL bTurnOfBullets )
/*N*/ {
/*N*/ 	for ( USHORT nPara = GetContents().Count(); nPara; )
/*N*/ 	{
/*N*/ 		ContentInfo* pC = GetContents().GetObject( --nPara );
/*N*/ 		if ( !bTurnOfBullets )
/*N*/ 		{
/*N*/ 			for ( USHORT n = 0; n <=1; n++ )
/*N*/ 			{
/*N*/ 				USHORT nItemId = n ? EE_PARA_LRSPACE : EE_PARA_OUTLLRSPACE;
/*N*/ 				if ( pC->GetParaAttribs().GetItemState( nItemId ) == SFX_ITEM_ON )
/*N*/ 				{
/*N*/ 					const SvxLRSpaceItem& rItem = (const SvxLRSpaceItem&) pC->GetParaAttribs().Get( nItemId );
/*N*/ 					if ( !rItem.GetTxtFirstLineOfst() )
/*N*/ 					{
/*N*/ 						SvxLRSpaceItem aNewItem( rItem );
/*N*/ 						aNewItem.SetTxtFirstLineOfst( (short) -1200 ); // Outliner im Draw mit MAP100TH_MM
/*N*/ 						if( pC->GetParaAttribs().GetItemState( EE_PARA_NUMBULLET ) == SFX_ITEM_ON )
/*N*/ 						{
/*?*/ 							const SvxNumBulletItem& rNumBullet = (const SvxNumBulletItem&) pC->GetParaAttribs().Get( EE_PARA_NUMBULLET );
/*?*/ 							const SfxUInt16Item& rLevel = (const SfxUInt16Item&) pC->GetParaAttribs().Get( EE_PARA_OUTLLEVEL );
/*?*/ 							const SvxNumberFormat* pFmt = rNumBullet.GetNumRule()->Get( rLevel.GetValue() );
/*?*/ 							if ( pFmt )
/*?*/ 								aNewItem.SetTxtFirstLineOfst( pFmt->GetFirstLineOffset() );
/*N*/ 						}
/*N*/ 						pC->GetParaAttribs().Put( aNewItem );
/*N*/ 					}
/*N*/ 				}
/*N*/ 			}
/*N*/ 		}
/*N*/ 
/*N*/ 		// Wurden in alten Versionen vom Outliner mal am Absatz gesetzt, soll nicht mehr sein
/*N*/ 		if ( !bTurnOfBullets && ( nVersion < 500 ) )
/*N*/ 		{
/*N*/ 			for ( USHORT nW = EE_CHAR_START; nW <= EE_CHAR_END; nW++  )
/*N*/ 				pC->GetParaAttribs().ClearItem( nW );
/*N*/ 		}
/*N*/ 
/*N*/ 		if ( bTurnOfBullets )
/*N*/ 		{
/*N*/ 			SfxUInt16Item aBulletState( EE_PARA_BULLETSTATE, 0 );
/*N*/ 			pC->GetParaAttribs().Put( aBulletState );
/*N*/ 		}
/*N*/ 	}
/*N*/ }



/*N*/ #define CHARSETMARKER	0x9999

/*N*/ void __EXPORT BinTextObject::CreateData300( SvStream& rIStream )
/*N*/ {
/*N*/ 	// Fuer Aufwaertskompatibilitaet.
/*N*/ 
/*N*/ 	// Erst den Pool laden...
/*N*/ 	// Ist in der 300 immer gespeichert worden!
/*N*/ 	GetPool()->Load( rIStream );
/*N*/ 
/*N*/ 	// Die Anzahl der Absaetze...
/*N*/ 	ULONG nParagraphs;
/*N*/ 	rIStream >> nParagraphs;
/*N*/ 
/*N*/ 	// Die einzelnen Absaetze...
/*N*/ 	for ( ULONG nPara = 0; nPara < nParagraphs; nPara++ )
/*N*/ 	{
/*N*/ 		ContentInfo* pC = CreateAndInsertContent();
/*N*/ 
/*N*/ 		// Der Text...
/*N*/ 		rIStream.ReadByteString( pC->GetText() );
/*N*/ 
/*N*/ 		// StyleName und Family...
/*N*/ 		rIStream.ReadByteString( pC->GetStyle() );
/*N*/ 		USHORT nStyleFamily;
/*N*/ 		rIStream >> nStyleFamily;
/*N*/ 		pC->GetFamily() = (SfxStyleFamily)nStyleFamily;
/*N*/ 
/*N*/ 		// Absatzattribute...
/*N*/ 		pC->GetParaAttribs().Load( rIStream );
/*N*/ 
/*N*/ 		// Die Anzahl der Attribute...
/*N*/ 		ULONG nAttribs;
/*N*/ 		rIStream >> nAttribs;
/*N*/ 
/*N*/ 		// Und die einzelnen Attribute
/*N*/ 		// Items als Surregate => immer 8 Byte pro Attrib
/*N*/ 		// Which = 2; Surregat = 2; Start = 2; End = 2;
/*N*/ 		for ( ULONG nAttr = 0; nAttr < nAttribs; nAttr++ )
/*N*/ 		{
/*N*/ 			USHORT nWhich, nStart, nEnd;
/*N*/ 			const SfxPoolItem* pItem;
/*N*/ 
/*N*/ 			rIStream >> nWhich;
/*N*/ 			nWhich = pPool->GetNewWhich( nWhich );
/*N*/ 			pItem = pPool->LoadSurrogate( rIStream, nWhich, 0 );
/*N*/ 			rIStream >> nStart;
/*N*/ 			rIStream >> nEnd;
/*N*/ 			if ( pItem )
/*N*/ 			{
/*N*/ 				XEditAttribute* pAttr = new XEditAttribute( *pItem, nStart, nEnd );
/*N*/ 				pC->GetAttribs().Insert( pAttr, pC->GetAttribs().Count() );
/*N*/ 			}
/*N*/ 		}
/*N*/ 	}
/*N*/ 
/*N*/ 	// Prueffen, ob ein Zeichensatz gespeichert wurde
/*N*/ 	USHORT nCharSetMarker;
/*N*/ 	rIStream >> nCharSetMarker;
/*N*/ 	if ( nCharSetMarker == CHARSETMARKER )
/*N*/ 	{
/*N*/ 		USHORT nCharSet;
/*N*/ 		rIStream >> nCharSet;
/*N*/ 	}
/*N*/ }
}
