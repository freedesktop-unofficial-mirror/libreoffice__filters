/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: svx_postattr.cxx,v $
 *
 *  $Revision: 1.4 $
 *
 *  last change: $Author: rt $ $Date: 2005-09-08 06:19:15 $
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

// include ---------------------------------------------------------------

#pragma hdrstop

#define _SVX_POSTATTR_CXX
#define ITEMID_AUTHOR	0
#define ITEMID_DATE		0
#define ITEMID_TEXT		0

#ifndef _SFXSTRITEM_HXX //autogen
#include <svtools/stritem.hxx>
#endif

#include "postattr.hxx"
// auto strip #include "itemtype.hxx"
namespace binfilter {

// -----------------------------------------------------------------------

/*N*/ TYPEINIT1_AUTOFACTORY(SvxPostItAuthorItem, SfxStringItem);
/*N*/ TYPEINIT1_AUTOFACTORY(SvxPostItDateItem, SfxStringItem);
/*N*/ TYPEINIT1_AUTOFACTORY(SvxPostItTextItem, SfxStringItem);

// class SvxPostItAuthorItem ---------------------------------------------

//STRIP001 SvxPostItAuthorItem::SvxPostItAuthorItem( sal_uInt16 nWhich )
//STRIP001 {
//STRIP001 	SetWhich( nWhich );
//STRIP001 }

// -----------------------------------------------------------------------

//STRIP001 SvxPostItAuthorItem::SvxPostItAuthorItem( const XubString& rAuthor,
//STRIP001 										  sal_uInt16 nWhich ) :
//STRIP001 	SfxStringItem( nWhich, rAuthor )
//STRIP001 {
//STRIP001 }

//------------------------------------------------------------------------

//STRIP001 SfxItemPresentation SvxPostItAuthorItem::GetPresentation
//STRIP001 (
//STRIP001 	SfxItemPresentation ePres,
//STRIP001 	SfxMapUnit			eCoreUnit,
//STRIP001 	SfxMapUnit			ePresUnit,
//STRIP001     XubString&          rText, const IntlWrapper *
//STRIP001 )	const
//STRIP001 {
//STRIP001 	switch ( ePres )
//STRIP001 	{
//STRIP001 		case SFX_ITEM_PRESENTATION_NONE:
//STRIP001 			rText.Erase();
//STRIP001 			return SFX_ITEM_PRESENTATION_NONE;
//STRIP001 		case SFX_ITEM_PRESENTATION_NAMELESS:
//STRIP001 			rText = GetValue();
//STRIP001 			return SFX_ITEM_PRESENTATION_NAMELESS;
//STRIP001 		case SFX_ITEM_PRESENTATION_COMPLETE:
//STRIP001 			rText = SVX_RESSTR(RID_SVXITEMS_AUTHOR_COMPLETE);
//STRIP001 			rText += GetValue();
//STRIP001 			return SFX_ITEM_PRESENTATION_COMPLETE;
//STRIP001 	}
//STRIP001 	return SFX_ITEM_PRESENTATION_NONE;
//STRIP001 }

// -----------------------------------------------------------------------

//STRIP001 SfxPoolItem* __EXPORT SvxPostItAuthorItem::Clone( SfxItemPool * ) const
//STRIP001 {
//STRIP001 	return new SvxPostItAuthorItem( *this );
//STRIP001 }

// class SvxPostItDateItem -----------------------------------------------

//STRIP001 SvxPostItDateItem::SvxPostItDateItem( sal_uInt16 nWhich )
//STRIP001 {
//STRIP001 	SetWhich( nWhich );
//STRIP001 }

// -----------------------------------------------------------------------

//STRIP001 SvxPostItDateItem::SvxPostItDateItem( const XubString& rDate, sal_uInt16 nWhich ) :
//STRIP001 
//STRIP001 	SfxStringItem( nWhich, rDate )
//STRIP001 {
//STRIP001 }

//------------------------------------------------------------------------

//STRIP001 SfxItemPresentation SvxPostItDateItem::GetPresentation
//STRIP001 (
//STRIP001 	SfxItemPresentation ePres,
//STRIP001 	SfxMapUnit			eCoreUnit,
//STRIP001 	SfxMapUnit			ePresUnit,
//STRIP001     XubString&          rText, const IntlWrapper *
//STRIP001 )	const
//STRIP001 {
//STRIP001 	switch ( ePres )
//STRIP001 	{
//STRIP001 		case SFX_ITEM_PRESENTATION_NONE:
//STRIP001 			rText.Erase();
//STRIP001 			return SFX_ITEM_PRESENTATION_NONE;
//STRIP001 		case SFX_ITEM_PRESENTATION_NAMELESS:
//STRIP001 			rText = GetValue();
//STRIP001 			return SFX_ITEM_PRESENTATION_NAMELESS;
//STRIP001 		case SFX_ITEM_PRESENTATION_COMPLETE:
//STRIP001 			rText = SVX_RESSTR(RID_SVXITEMS_DATE_COMPLETE);
//STRIP001 			rText += GetValue();
//STRIP001 			return SFX_ITEM_PRESENTATION_COMPLETE;
//STRIP001 	}
//STRIP001 	return SFX_ITEM_PRESENTATION_NONE;
//STRIP001 }

// -----------------------------------------------------------------------

//STRIP001 SfxPoolItem* __EXPORT SvxPostItDateItem::Clone( SfxItemPool * ) const
//STRIP001 {
//STRIP001 	return new SvxPostItDateItem( *this );
//STRIP001 }

// class SvxPostItTextItem -----------------------------------------------

//STRIP001 SvxPostItTextItem::SvxPostItTextItem( sal_uInt16 nWhich )
//STRIP001 {
//STRIP001 	SetWhich( nWhich );
//STRIP001 }

// -----------------------------------------------------------------------

//STRIP001 SvxPostItTextItem::SvxPostItTextItem( const XubString& rText, sal_uInt16 nWhich ) :
//STRIP001 
//STRIP001 	SfxStringItem( nWhich, rText )
//STRIP001 {
//STRIP001 }

//------------------------------------------------------------------------

//STRIP001 SfxItemPresentation SvxPostItTextItem::GetPresentation
//STRIP001 (
//STRIP001 	SfxItemPresentation ePres,
//STRIP001 	SfxMapUnit			eCoreUnit,
//STRIP001 	SfxMapUnit			ePresUnit,
//STRIP001     XubString&          rText, const IntlWrapper *
//STRIP001 )	const
//STRIP001 {
//STRIP001 	switch ( ePres )
//STRIP001 	{
//STRIP001 		case SFX_ITEM_PRESENTATION_NONE:
//STRIP001 			rText.Erase();
//STRIP001 			return SFX_ITEM_PRESENTATION_NONE;
//STRIP001 		case SFX_ITEM_PRESENTATION_NAMELESS:
//STRIP001 			rText = GetValue();
//STRIP001 			return SFX_ITEM_PRESENTATION_NAMELESS;
//STRIP001 		case SFX_ITEM_PRESENTATION_COMPLETE:
//STRIP001 			rText = SVX_RESSTR(RID_SVXITEMS_TEXT_COMPLETE);
//STRIP001 			rText += GetValue();
//STRIP001 			return SFX_ITEM_PRESENTATION_COMPLETE;
//STRIP001 	}
//STRIP001 	return SFX_ITEM_PRESENTATION_NONE;
//STRIP001 }

// -----------------------------------------------------------------------

//STRIP001 SfxPoolItem* __EXPORT SvxPostItTextItem::Clone( SfxItemPool * ) const
//STRIP001 {
//STRIP001 	return new SvxPostItTextItem( *this );
//STRIP001 }


}
