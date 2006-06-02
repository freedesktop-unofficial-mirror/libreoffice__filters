/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: brshitem.hxx,v $
 *
 *  $Revision: 1.4 $
 *
 *  last change: $Author: vg $ $Date: 2006-06-02 12:24:17 $
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
#ifndef _SVX_BRSHITEM_HXX
#define _SVX_BRSHITEM_HXX

// include ---------------------------------------------------------------

#ifndef _SFXPOOLITEM_HXX //autogen
#include <svtools/poolitem.hxx>
#endif
#ifndef _SVX_SVXIDS_HRC
#include <bf_svx/svxids.hrc>
#endif
#ifndef _SV_WALL_HXX
#include <vcl/wall.hxx>
#endif
#ifndef _LINK_HXX
#include <tools/link.hxx>
#endif
namespace rtl
{
    class OUString;
}
class Graphic;
class GraphicObject;
namespace binfilter {

// class SvxBrushItem ----------------------------------------------------

class SfxObjectShell;
class CntWallpaperItem;
//STRIP008 #ifdef _USE_NAMESPACE
//STRIP008 namespace rtl
//STRIP008 {
//STRIP008 #endif
//STRIP008 	class OUString;
//STRIP008 #ifdef _USE_NAMESPACE
//STRIP008 }
//STRIP008 #endif

#define	BRUSH_GRAPHIC_VERSION	((USHORT)0x0001)

enum SvxGraphicPosition
{
    GPOS_NONE,
    GPOS_LT, GPOS_MT, GPOS_RT,
    GPOS_LM, GPOS_MM, GPOS_RM,
    GPOS_LB, GPOS_MB, GPOS_RB,
    GPOS_AREA, GPOS_TILED
};

class SvxBrushItem_Impl;
class SvxBrushItem : public SfxPoolItem
{
    Color 				aColor;
    SvxBrushItem_Impl*  pImpl;
    String*				pStrLink;
    String*				pStrFilter;
    SvxGraphicPosition	eGraphicPos;
    BOOL				bLoadAgain;

    void        ApplyGraphicTransparency_Impl();
//STRIP001     DECL_STATIC_LINK( SvxBrushItem, DoneHdl_Impl, void *);
    // wird nur von Create benutzt
    SvxBrushItem( SvStream& rStrm,
                  USHORT nVersion, USHORT nWhich = ITEMID_BRUSH );

public:
    TYPEINFO();

    SvxBrushItem( USHORT nWhich = ITEMID_BRUSH );
    SvxBrushItem( const Color& rColor, USHORT nWhich = ITEMID_BRUSH );

    SvxBrushItem( const Graphic& rGraphic,
                  SvxGraphicPosition ePos, USHORT nWhich = ITEMID_BRUSH );
    SvxBrushItem( const GraphicObject& rGraphicObj,
                  SvxGraphicPosition ePos, USHORT nWhich = ITEMID_BRUSH );
    SvxBrushItem( const String& rLink, const String& rFilter,
                  SvxGraphicPosition ePos, USHORT nWhich = ITEMID_BRUSH );
    SvxBrushItem( const SvxBrushItem& );
    SvxBrushItem( const CntWallpaperItem&, USHORT nWhich );

    ~SvxBrushItem();

public:

//STRIP001 	virtual SfxItemPresentation GetPresentation( SfxItemPresentation ePres,
//STRIP001 									SfxMapUnit eCoreMetric,
//STRIP001 									SfxMapUnit ePresMetric,
//STRIP001                                     String &rText, const IntlWrapper * = 0 ) const;

    virtual int 			 operator==( const SfxPoolItem& ) const;
    virtual	sal_Bool        	 QueryValue( ::com::sun::star::uno::Any& rVal, BYTE nMemberId = 0 ) const;
    virtual	sal_Bool			 PutValue( const ::com::sun::star::uno::Any& rVal, BYTE nMemberId = 0 );

    virtual SfxPoolItem*     Clone( SfxItemPool *pPool = 0 ) const;
    virtual SfxPoolItem*	 Create( SvStream&, USHORT nVersion ) const;
    virtual SvStream&		 Store( SvStream& , USHORT nItemVersion ) const;
    virtual USHORT			 GetVersion( USHORT nFileVersion ) const;

    const Color& 	GetColor() const 				{ return aColor; }
    Color& 			GetColor()  					{ return aColor; }
    void			SetColor( const Color& rCol)  	{ aColor = rCol; }

//STRIP001 	void                SetDoneLink( const Link& rLink );

    SvxGraphicPosition	GetGraphicPos() const		{ return eGraphicPos; }

//STRIP001 	void                PurgeGraphic() const;
//STRIP001 	void                PurgeMedium() const;

    const Graphic* 			GetGraphic( SfxObjectShell* pSh = 0) const;
    const GraphicObject* 	GetGraphicObject( SfxObjectShell* pSh = 0) const;
    const String* 			GetGraphicLink() const		{ return pStrLink; }
    const String* 			GetGraphicFilter() const	{ return pStrFilter; }

    void				SetGraphicPos( SvxGraphicPosition eNew );
    void 				SetGraphic( const Graphic& rNew );
//STRIP001 	void 				SetGraphicObject( const GraphicObject& rNewObj );
    void		 		SetGraphicLink( const String& rNew );
    void		 		SetGraphicFilter( const String& rNew );

    SvxBrushItem&		operator=( const SvxBrushItem& rItem);

    static void					InitSfxLink();
//STRIP001 	static SvxGraphicPosition 	WallpaperStyle2GraphicPos( WallpaperStyle eStyle );
//STRIP001 	static WallpaperStyle 		GraphicPos2WallpaperStyle( SvxGraphicPosition ePos );
//STRIP001 	CntWallpaperItem*			CreateCntWallpaperItem() const;
};

}//end of namespace binfilter
#endif // #ifndef _SVX_BRSHITEM_HXX

