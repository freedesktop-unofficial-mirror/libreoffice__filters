/*************************************************************************
 *
 *  $RCSfile: unoshprp.hxx,v $
 *
 *  $Revision: 1.2 $
 *
 *  last change: $Author: mwu $ $Date: 2003-11-06 08:29:25 $
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

#ifndef _SVX_UNOSHPRP_HXX
#define _SVX_UNOSHPRP_HXX

#ifndef _COM_SUN_STAR_CONTAINER_XNAMECONTAINER_HPP_ 
#include <com/sun/star/container/XNameContainer.hpp>
#endif
#ifndef _COM_SUN_STAR_DRAWING_POINTSEQUENCE_HPP_
#include <com/sun/star/drawing/PointSequence.hpp>
#endif
#ifndef _COM_SUN_STAR_DRAWING_POINTSEQUENCESEQUENCE_HPP_
#include <com/sun/star/drawing/PointSequenceSequence.hpp>
#endif
#ifndef _COM_SUN_STAR_UNO_SEQUENCE_HXX_
#include <com/sun/star/uno/Sequence.hxx>
#endif
#ifndef _COM_SUN_STAR_DRAWING_RECTANGLEPOINT_HPP_
#include <com/sun/star/drawing/RectanglePoint.hpp>
#endif
#ifndef _COM_SUN_STAR_AWT_XBITMAP_HPP_
#include <com/sun/star/awt/XBitmap.hpp>
#endif
#ifndef _COM_SUN_STAR_AWT_GRADIENT_HPP_
#include <com/sun/star/awt/Gradient.hpp>
#endif
#ifndef _COM_SUN_STAR_DRAWING_HATCH_HPP_
#include <com/sun/star/drawing/Hatch.hpp>
#endif
#ifndef _COM_SUN_STAR_DRAWING_FILLSTYLE_HPP_
#include <com/sun/star/drawing/FillStyle.hpp>
#endif
#ifndef _COM_SUN_STAR_DRAWING_LINEDASH_HPP_
#include <com/sun/star/drawing/LineDash.hpp>
#endif
#ifndef _COM_SUN_STAR_DRAWING_LINEJOINT_Hpp_
#include <com/sun/star/drawing/LineJoint.hpp>
#endif
#ifndef _COM_SUN_STAR_DRAWING_LINESTYLE_HPP_
#include <com/sun/star/drawing/LineStyle.hpp>
#endif
#ifndef _COM_SUN_STAR_BEANS_PROPERTYATTRIBUTE_HPP_
#include <com/sun/star/beans/PropertyAttribute.hpp>
#endif
#ifndef _COM_SUN_STAR_AWT_RECTANGLE_HPP_
#include <com/sun/star/awt/Rectangle.hpp>
#endif
#ifndef _COM_SUN_STAR_DRAWING_TEXTANIMATIONDIRECTION_HPP_
#include <com/sun/star/drawing/TextAnimationDirection.hpp>
#endif
#ifndef _COM_SUN_STAR_DRAWING_TEXTANIMATIONKIND_HPP_
#include <com/sun/star/drawing/TextAnimationKind.hpp>
#endif
#ifndef _COM_SUN_STAR_DRAWING_TEXTFITTOSIZETYPE_HPP_
#include <com/sun/star/drawing/TextFitToSizeType.hpp>
#endif
#ifndef _COM_SUN_STAR_DRAWING_TEXTVERTICALADJUST_HPP_
#include <com/sun/star/drawing/TextVerticalAdjust.hpp>
#endif
#ifndef _COM_SUN_STAR_DRAWING_TEXTHORIZONTALADJUST_HPP_
#include <com/sun/star/drawing/TextHorizontalAdjust.hpp>
#endif
#ifndef _COM_SUN_STAR_DRAWING_CONNECTORTYPE_HPP_
#include <com/sun/star/drawing/ConnectorType.hpp>
#endif
#ifndef _COM_SUN_STAR_DRAWING_XSHAPE_HPP_
#include <com/sun/star/drawing/XShape.hpp>
#endif
#ifndef _COM_SUN_STAR_DRAWING_MEASUREKIND_HPP_
#include <com/sun/star/drawing/MeasureKind.hpp>
#endif
#ifndef _COM_SUN_STAR_DRAWING_MEASURETEXTHORZPOS_HPP_
#include <com/sun/star/drawing/MeasureTextHorzPos.hpp>
#endif
#ifndef _COM_SUN_STAR_DRAWING_MEASURETEXTVERTPOS_HPP_
#include <com/sun/star/drawing/MeasureTextVertPos.hpp>
#endif
#ifndef _COM_SUN_STAR_DRAWING_HOMOGENMATRIX3_HPP_ 
#include <com/sun/star/drawing/HomogenMatrix3.hpp>
#endif
#ifndef _COM_SUN_STAR_DRAWING_CIRCLEKIND_HPP_
#include <com/sun/star/drawing/CircleKind.hpp>
#endif
#ifndef _COM_SUN_STAR_DRAWING_POLYGONKIND_HPP_
#include <com/sun/star/drawing/PolygonKind.hpp>
#endif
#ifndef _COM_SUN_STAR_DRAWING_POLYPOLYGONBEZIERCOORDS_HPP_
#include <com/sun/star/drawing/PolyPolygonBezierCoords.hpp>
#endif
#ifndef _COM_SUN_STAR_DRAWING_COLORMODE_HPP_
#include <com/sun/star/drawing/ColorMode.hpp>
#endif
#ifndef _COM_SUN_STAR_DRAWING_HOMOGENMATRIX_HPP_
#include <com/sun/star/drawing/HomogenMatrix.hpp>
#endif
#ifndef _COM_SUN_STAR_DRAWING_DIRECTION3D_HPP_
#include <com/sun/star/drawing/Direction3D.hpp>
#endif
#ifndef _COM_SUN_STAR_DRAWING_PROJECTIONMODE_HPP_
#include <com/sun/star/drawing/ProjectionMode.hpp>
#endif
#ifndef _COM_SUN_STAR_DRAWING_SHADEMODE_HPP_
#include <com/sun/star/drawing/ShadeMode.hpp>
#endif
#ifndef _COM_SUN_STAR_DRAWING_POSITION3D_HPP_
#include <com/sun/star/drawing/Position3D.hpp>
#endif
#ifndef _COM_SUN_STAR_DRAWING_NORMALSKIND_HPP_
#include <com/sun/star/drawing/NormalsKind.hpp>
#endif
#ifndef _COM_SUN_STAR_DRAWING_TEXTUREKIND_HPP_
#include <com/sun/star/drawing/TextureKind.hpp>
#endif
#ifndef _COM_SUN_STAR_DRAWING_TEXTUREMODE_HPP_
#include <com/sun/star/drawing/TextureMode.hpp>
#endif
#ifndef _COM_SUN_STAR_DRAWING_TEXTUREPROJECTIONMODE_HPP_
#include <com/sun/star/drawing/TextureProjectionMode.hpp>
#endif
#ifndef _COM_SUN_STAR_DRAWING_POLYPOLYGONSHAPE3D_HPP_
#include <com/sun/star/drawing/PolyPolygonShape3D.hpp>
#endif
#ifndef _COM_SUN_STAR_TEXT_GRAPHICCROP_HPP_
#include <com/sun/star/text/GraphicCrop.hpp>
#endif
#ifndef _COM_SUN_STAR_DRAWING_BITMAPMODE_HPP_
#include <com/sun/star/drawing/BitmapMode.hpp>
#endif
#ifndef _COM_SUN_STAR_DRAWING_CAMERAGEOMETRY_HPP_
#include <com/sun/star/drawing/CameraGeometry.hpp>
#endif
#ifndef _COM_SUN_STAR_TEXT_WRITINGMODE_HPP_
#include <com/sun/star/text/WritingMode.hpp>
#endif

#define _SVX_USE_UNOGLOBALS_
#ifndef SVX_UNOPROV_HXX
#include <bf_svx/unoprov.hxx>
#endif
#include <bf_svx/unoprnms.hxx>
#include <bf_svx/unomid.hxx>

#ifndef _SVX_UNOTEXT_HXX
#include <bf_svx/unotext.hxx>
#endif

#ifndef _SFX_ITEMPROP_HXX
#include <svtools/itemprop.hxx>
#endif

#include <bf_svx/svxids.hrc>
namespace binfilter {

#ifndef SEQTYPE
 #if defined(__SUNPRO_CC) && (__SUNPRO_CC == 0x500)
  #define SEQTYPE(x) (new ::com::sun::star::uno::Type( x ))
 #else
  #define SEQTYPE(x) &(x)
 #endif
#endif

#define OWN_ATTR_VALUE_START					(3900)
#define OWN_ATTR_VALUE_START_TEXT				(OWN_ATTR_VALUE_START+0)	// the next 10 entries are reserved for text
#define OWN_ATTR_VALUE_POLYGONKIND				(OWN_ATTR_VALUE_START+10)
#define OWN_ATTR_VALUE_POLYPOLYGON				(OWN_ATTR_VALUE_START+11)
#define OWN_ATTR_VALUE_POLYPOLYGONBEZIER		(OWN_ATTR_VALUE_START+12)
#define	OWN_ATTR_VALUE_FILLBITMAP				(OWN_ATTR_VALUE_START+13)
#define	OWN_ATTR_3D_VALUE_TRANSFORM_MATRIX		(OWN_ATTR_VALUE_START+14)
#define	OWN_ATTR_3D_VALUE_POSITION				(OWN_ATTR_VALUE_START+15)
#define	OWN_ATTR_3D_VALUE_SIZE					(OWN_ATTR_VALUE_START+16)
#define	OWN_ATTR_3D_VALUE_POS_IS_CENTER			(OWN_ATTR_VALUE_START+17)
#define OWN_ATTR_3D_VALUE_POLYPOLYGON3D			(OWN_ATTR_VALUE_START+18)
#define	OWN_ATTR_3D_VALUE_LINEONLY				(OWN_ATTR_VALUE_START+19)
#define OWN_ATTR_BITMAP							(OWN_ATTR_VALUE_START+20)
#define OWN_ATTR_EDGE_START_OBJ					(OWN_ATTR_VALUE_START+21)
#define OWN_ATTR_EDGE_START_POS					(OWN_ATTR_VALUE_START+22)
#define OWN_ATTR_EDGE_END_OBJ					(OWN_ATTR_VALUE_START+23)
#define OWN_ATTR_EDGE_END_POS					(OWN_ATTR_VALUE_START+24)
#define OWN_ATTR_FRAMERECT						(OWN_ATTR_VALUE_START+25)
#define OWN_ATTR_VALUE_POLYGON					(OWN_ATTR_VALUE_START+26)
#define OWN_ATTR_METAFILE						(OWN_ATTR_VALUE_START+27)
#define OWN_ATTR_ISFONTWORK						(OWN_ATTR_VALUE_START+28)
#define OWN_ATTR_BOUNDRECT						(OWN_ATTR_VALUE_START+29)
#define OWN_ATTR_LDNAME							(OWN_ATTR_VALUE_START+30)
#define OWN_ATTR_LDBITMAP						(OWN_ATTR_VALUE_START+31)
#define OWN_ATTR_OLESIZE						(OWN_ATTR_VALUE_START+32)
#define OWN_ATTR_GRAFURL						(OWN_ATTR_VALUE_START+33)
#define OWN_ATTR_OLEMODEL						(OWN_ATTR_VALUE_START+34)
#define OWN_ATTR_MIRRORED						(OWN_ATTR_VALUE_START+35)
#define OWN_ATTR_CLSID							(OWN_ATTR_VALUE_START+36)
#define OWN_ATTR_GLUEID_TAIL					(OWN_ATTR_VALUE_START+37)
#define OWN_ATTR_GLUEID_HEAD					(OWN_ATTR_VALUE_START+38)
#define OWN_ATTR_ZORDER							(OWN_ATTR_VALUE_START+39)
#define OWN_ATTR_MEASURE_START_POS				(OWN_ATTR_VALUE_START+40)
#define	OWN_ATTR_MEASURE_END_POS				(OWN_ATTR_VALUE_START+41)
#define	OWN_ATTR_3D_VALUE_CAMERA_GEOMETRY		(OWN_ATTR_VALUE_START+42)
#define	OWN_ATTR_WRITINGMODE					(OWN_ATTR_VALUE_START+43)
#define	OWN_ATTR_GRAFSTREAMURL					(OWN_ATTR_VALUE_START+44)
#define OWN_ATTR_FILLBMP_MODE					(OWN_ATTR_VALUE_START+45)
#define OWN_ATTR_TRANSFORMATION					(OWN_ATTR_VALUE_START+46)
#define OWN_ATTR_BASE_GEOMETRY					(OWN_ATTR_VALUE_START+47)
#define OWN_ATTR_INTERNAL_OLE					(OWN_ATTR_VALUE_START+48)
#define OWN_ATTR_APPLET_CODEBASE				(OWN_ATTR_VALUE_START+49)
#define OWN_ATTR_APPLET_NAME					(OWN_ATTR_VALUE_START+50)
#define OWN_ATTR_APPLET_CODE					(OWN_ATTR_VALUE_START+51)
#define OWN_ATTR_APPLET_COMMANDS				(OWN_ATTR_VALUE_START+52)
#define OWN_ATTR_APPLET_ISSCRIPT				(OWN_ATTR_VALUE_START+53)
#define OWN_ATTR_PLUGIN_MIMETYPE				(OWN_ATTR_VALUE_START+54)
#define OWN_ATTR_PLUGIN_URL						(OWN_ATTR_VALUE_START+55)
#define OWN_ATTR_PLUGIN_COMMANDS				(OWN_ATTR_VALUE_START+56)
#define OWN_ATTR_FRAME_URL						(OWN_ATTR_VALUE_START+57)
#define OWN_ATTR_FRAME_NAME						(OWN_ATTR_VALUE_START+58)
#define OWN_ATTR_FRAME_ISAUTOSCROLL				(OWN_ATTR_VALUE_START+59)
#define OWN_ATTR_FRAME_ISBORDER					(OWN_ATTR_VALUE_START+60)
#define OWN_ATTR_FRAME_MARGIN_WIDTH				(OWN_ATTR_VALUE_START+61)
#define OWN_ATTR_FRAME_MARGIN_HEIGHT			(OWN_ATTR_VALUE_START+62)
#define OWN_ATTR_OLE_VISAREA					(OWN_ATTR_VALUE_START+63)
#define OWN_ATTR_CAPTION_POINT					(OWN_ATTR_VALUE_START+64)
#define OWN_ATTR_PAGE_NUMBER					(OWN_ATTR_VALUE_START+65)
#define OWN_ATTR_THUMBNAIL						(OWN_ATTR_VALUE_START+66)
#define OWN_ATTR_PERSISTNAME					(OWN_ATTR_VALUE_START+67)
#define OWN_ATTR_HASLEVELS						(OWN_ATTR_VALUE_START+68)

#define OWN_ATTR_VALUE_END						OWN_ATTR_HASLEVELS // WARNING: ee items start at 3991!

// #FontWork#
#define FONTWORK_PROPERTIES \
    { MAP_CHAR_LEN("FontWorkStyle"),			XATTR_FORMTXTSTYLE,			/*ENUM*/&::getCppuType((const sal_Int32*)0),	0,	0}, \
    { MAP_CHAR_LEN("FontWorkAdjust"),			XATTR_FORMTXTADJUST,		/*ENUM*/&::getCppuType((const sal_Int32*)0),	0,	0}, \
    { MAP_CHAR_LEN("FontWorkDistance"),			XATTR_FORMTXTDISTANCE,		&::getCppuType((const sal_Int32*)0),			0,	SFX_METRIC_ITEM}, \
    { MAP_CHAR_LEN("FontWorkStart"),			XATTR_FORMTXTSTART,			&::getCppuType((const sal_Int32*)0),			0,	SFX_METRIC_ITEM}, \
    { MAP_CHAR_LEN("FontWorkMirror"),			XATTR_FORMTXTMIRROR,		&::getBooleanCppuType(),						0,	0}, \
    { MAP_CHAR_LEN("FontWorkOutline"),			XATTR_FORMTXTOUTLINE,		&::getBooleanCppuType(),						0,	0}, \
    { MAP_CHAR_LEN("FontWorkShadow"),			XATTR_FORMTXTSHADOW,		/*ENUM*/&::getCppuType((const sal_Int32*)0),	0,	0}, \
    { MAP_CHAR_LEN("FontWorkShadowColor"),		XATTR_FORMTXTSHDWCOLOR,		&::getCppuType((const sal_Int32*)0),			0,	0}, \
    { MAP_CHAR_LEN("FontWorkShadowOffsetX"),	XATTR_FORMTXTSHDWXVAL,		&::getCppuType((const sal_Int32*)0),			0,	SFX_METRIC_ITEM}, \
    { MAP_CHAR_LEN("FontWorkShadowOffsetY"),	XATTR_FORMTXTSHDWYVAL,		&::getCppuType((const sal_Int32*)0),			0,	SFX_METRIC_ITEM}, \
    { MAP_CHAR_LEN("FontWorkForm"),				XATTR_FORMTXTSTDFORM,		/*ENUM*/&::getCppuType((const sal_Int32*)0),	0,	0}, \
    { MAP_CHAR_LEN("FontWorkHideForm"),			XATTR_FORMTXTHIDEFORM,		&::getBooleanCppuType(),						0,	0}, \
    { MAP_CHAR_LEN("FontWorkShadowTransparence"),XATTR_FORMTXTSHDWTRANSP,	&::getCppuType((const sal_Int16*)0),			0,	0},

#define SHADOW_PROPERTIES \
    { MAP_CHAR_LEN(UNO_NAME_SHADOW),			SDRATTR_SHADOW,				&::getBooleanCppuType(),	0,		0}, \
    { MAP_CHAR_LEN(UNO_NAME_SHADOWCOLOR),		SDRATTR_SHADOWCOLOR,		&::getCppuType((const sal_Int32*)0),	0,		0}, \
    { MAP_CHAR_LEN(UNO_NAME_SHADOWTRANSPARENCE),SDRATTR_SHADOWTRANSPARENCE,	&::getCppuType((const sal_Int16*)0),	0,		0}, \
    { MAP_CHAR_LEN(UNO_NAME_SHADOWXDIST),		SDRATTR_SHADOWXDIST,		&::getCppuType((const sal_Int32*)0),	0,		SFX_METRIC_ITEM}, \
    { MAP_CHAR_LEN(UNO_NAME_SHADOWYDIST),		SDRATTR_SHADOWYDIST,		&::getCppuType((const sal_Int32*)0),	0,		SFX_METRIC_ITEM},

#define LINE_PROPERTIES_DEFAULTS\
    { MAP_CHAR_LEN(UNO_NAME_LINECOLOR),			XATTR_LINECOLOR,		&::getCppuType((const sal_Int32*)0) , 			0,     0}, \
    { MAP_CHAR_LEN(UNO_NAME_LINEENDCENTER),		XATTR_LINEENDCENTER,	&::getBooleanCppuType() , 			0,     0}, \
    { MAP_CHAR_LEN(UNO_NAME_LINEENDWIDTH),		XATTR_LINEENDWIDTH,		&::getCppuType((const sal_Int32*)0) , 			0,     SFX_METRIC_ITEM}, \
    { MAP_CHAR_LEN(UNO_NAME_LINEJOINT),			XATTR_LINEJOINT,		&::getCppuType((const ::com::sun::star::drawing::LineJoint*)0),		0,	   0}, \
    { MAP_CHAR_LEN(UNO_NAME_LINESTARTCENTER),	XATTR_LINESTARTCENTER,	&::getBooleanCppuType() , 			0,     0}, \
    { MAP_CHAR_LEN(UNO_NAME_LINESTARTWIDTH),	XATTR_LINESTARTWIDTH,	&::getCppuType((const sal_Int32*)0) , 			0,     SFX_METRIC_ITEM}, \
    { MAP_CHAR_LEN(UNO_NAME_LINESTYLE),			XATTR_LINESTYLE,		&::getCppuType((const ::com::sun::star::drawing::LineStyle*)0) , 		0,     0},	\
    { MAP_CHAR_LEN(UNO_NAME_LINETRANSPARENCE),	XATTR_LINETRANSPARENCE,	&::getCppuType((const sal_Int16*)0) , 			0,     0}, \
    { MAP_CHAR_LEN(UNO_NAME_LINEWIDTH),			XATTR_LINEWIDTH,		&::getCppuType((const sal_Int32*)0) , 			0,     SFX_METRIC_ITEM},

#define LINE_PROPERTIES \
    { MAP_CHAR_LEN(UNO_NAME_LINEDASH),			XATTR_LINEDASH,			&::getCppuType((const ::com::sun::star::drawing::LineDash*)0) , 		0,     0},	\
    { MAP_CHAR_LEN("LineDashName"),				XATTR_LINEDASH,			&::getCppuType((const ::rtl::OUString*)0) , 		0,     MID_NAME},	\
    LINE_PROPERTIES_DEFAULTS

#define LINE_PROPERTIES_START_END \
    { MAP_CHAR_LEN(UNO_NAME_LINEEND),			XATTR_LINEEND,			SEQTYPE(::getCppuType((const ::com::sun::star::drawing::PolyPolygonBezierCoords*)0)), 	::com::sun::star::beans::PropertyAttribute::MAYBEVOID,     0}, \
    { MAP_CHAR_LEN("LineEndName"),				XATTR_LINEEND,			&::getCppuType((const ::rtl::OUString*)0), 0, MID_NAME }, \
    { MAP_CHAR_LEN(UNO_NAME_LINESTART),			XATTR_LINESTART,		SEQTYPE(::getCppuType((const ::com::sun::star::drawing::PolyPolygonBezierCoords*)0)), 	::com::sun::star::beans::PropertyAttribute::MAYBEVOID,     0},	\
    { MAP_CHAR_LEN("LineStartName"),			XATTR_LINESTART,			&::getCppuType((const ::rtl::OUString*)0), 0, MID_NAME },

#define FILL_PROPERTIES_BMP \
    { MAP_CHAR_LEN(UNO_NAME_FILLBMP_LOGICAL_SIZE),		XATTR_FILLBMP_SIZELOG,		&::getBooleanCppuType() , 			0,     0}, \
    { MAP_CHAR_LEN(UNO_NAME_FILLBMP_OFFSET_X),			XATTR_FILLBMP_TILEOFFSETX,	&::getCppuType((const sal_Int32*)0) , 			0,     0}, \
    { MAP_CHAR_LEN(UNO_NAME_FILLBMP_OFFSET_Y),			XATTR_FILLBMP_TILEOFFSETY,	&::getCppuType((const sal_Int32*)0) , 			0,     0}, \
    { MAP_CHAR_LEN(UNO_NAME_FILLBMP_POSITION_OFFSET_X),	XATTR_FILLBMP_POSOFFSETX,	&::getCppuType((const sal_Int32*)0) , 			0,     0}, \
    { MAP_CHAR_LEN(UNO_NAME_FILLBMP_POSITION_OFFSET_Y),	XATTR_FILLBMP_POSOFFSETY,	&::getCppuType((const sal_Int32*)0) , 			0,     0}, \
    { MAP_CHAR_LEN(UNO_NAME_FILLBMP_RECTANGLE_POINT),	XATTR_FILLBMP_POS,			&::getCppuType((const ::com::sun::star::drawing::RectanglePoint*)0) , 0,     0}, \
    { MAP_CHAR_LEN(UNO_NAME_FILLBMP_SIZE_X),			XATTR_FILLBMP_SIZEX,		&::getCppuType((const sal_Int32*)0) , 			0,     SFX_METRIC_ITEM}, \
    { MAP_CHAR_LEN(UNO_NAME_FILLBMP_SIZE_Y),			XATTR_FILLBMP_SIZEY,		&::getCppuType((const sal_Int32*)0) , 			0,     SFX_METRIC_ITEM},	\
    { MAP_CHAR_LEN(UNO_NAME_FILLBMP_STRETCH),			XATTR_FILLBMP_STRETCH,		&::getBooleanCppuType() , 			0,     0}, \
    { MAP_CHAR_LEN(UNO_NAME_FILLBMP_TILE),				XATTR_FILLBMP_TILE,			&::getBooleanCppuType() , 			0,     0},\
    { MAP_CHAR_LEN(UNO_NAME_FILLBMP_MODE),				OWN_ATTR_FILLBMP_MODE,		&::getCppuType((const ::com::sun::star::drawing::BitmapMode*)0), 			0,     0},

#define FILL_PROPERTIES_DEFAULTS \
    { MAP_CHAR_LEN(UNO_NAME_FILLCOLOR), 		XATTR_FILLCOLOR			, &::getCppuType((const sal_Int32*)0), 			0,     0}, \

#define FILL_PROPERTIES \
    FILL_PROPERTIES_BMP \
    FILL_PROPERTIES_DEFAULTS \
    { MAP_CHAR_LEN(UNO_NAME_FILLBACKGROUND),	XATTR_FILLBACKGROUND	, &::getBooleanCppuType(),				0,	 0}, \
    { MAP_CHAR_LEN(UNO_NAME_FILLBITMAP),  		XATTR_FILLBITMAP   		, &::getCppuType((const ::com::sun::star::uno::Reference< ::com::sun::star::awt::XBitmap >*)0)  , 		0,     0}, \
    { MAP_CHAR_LEN("FillBitmapName"),			XATTR_FILLBITMAP		, &::getCppuType((const ::rtl::OUString*)0), 0, MID_NAME }, \
    { MAP_CHAR_LEN("FillBitmapURL"),			XATTR_FILLBITMAP		, &::getCppuType((const ::rtl::OUString*)0), 0, MID_GRAFURL }, \
    { MAP_CHAR_LEN("FillGradientStepCount"),	XATTR_GRADIENTSTEPCOUNT	, &::getCppuType((const sal_Int16*)0), 0, 0}, \
    { MAP_CHAR_LEN(UNO_NAME_FILLGRADIENT),		XATTR_FILLGRADIENT		, &::getCppuType((const ::com::sun::star::awt::Gradient*)0),  		0,     0}, \
    { MAP_CHAR_LEN("FillGradientName"),			XATTR_FILLGRADIENT		, &::getCppuType((const ::rtl::OUString*)0), 0, MID_NAME }, \
    { MAP_CHAR_LEN(UNO_NAME_FILLHATCH),    		XATTR_FILLHATCH			, &::getCppuType((const ::com::sun::star::drawing::Hatch*)0),  			0,     0}, \
    { MAP_CHAR_LEN("FillHatchName"),			XATTR_FILLHATCH			, &::getCppuType((const ::rtl::OUString*)0), 0, MID_NAME }, \
    { MAP_CHAR_LEN(UNO_NAME_FILLSTYLE), 		XATTR_FILLSTYLE			, &::getCppuType((const ::com::sun::star::drawing::FillStyle*)0) , 		0,     0}, \
    { MAP_CHAR_LEN(UNO_NAME_FILL_TRANSPARENCE),	XATTR_FILLTRANSPARENCE, &::getCppuType((const sal_Int16*)0) , 			0,     0}, \
    { MAP_CHAR_LEN("FillTransparenceGradient"),	XATTR_FILLFLOATTRANSPARENCE, &::getCppuType((const ::com::sun::star::awt::Gradient*)0),  		0,     0}, \
    { MAP_CHAR_LEN("FillTransparenceGradientName"),	XATTR_FILLFLOATTRANSPARENCE, &::getCppuType((const ::rtl::OUString*)0), 0, MID_NAME },

#define EDGERADIUS_PROPERTIES \
    { MAP_CHAR_LEN(UNO_NAME_EDGERADIUS),  		SDRATTR_ECKENRADIUS		, &::getCppuType((const sal_Int32*)0)  , 			0,     SFX_METRIC_ITEM},

#define TEXT_PROPERTIES_DEFAULTS\
    { MAP_CHAR_LEN(UNO_NAME_TEXT_WRITINGMODE),		SDRATTR_TEXTDIRECTION,			&::getCppuType((const ::com::sun::star::text::WritingMode*)0),		0,		0},\
    { MAP_CHAR_LEN(UNO_NAME_TEXT_ANIAMOUNT),		SDRATTR_TEXT_ANIAMOUNT,			&::getCppuType((const sal_Int16*)0),		0,		0}, \
    { MAP_CHAR_LEN(UNO_NAME_TEXT_ANICOUNT),			SDRATTR_TEXT_ANICOUNT,			&::getCppuType((const sal_Int16*)0),		0,		0}, \
    { MAP_CHAR_LEN(UNO_NAME_TEXT_ANIDELAY),			SDRATTR_TEXT_ANIDELAY,			&::getCppuType((const sal_Int16*)0),		0,		0}, \
    { MAP_CHAR_LEN(UNO_NAME_TEXT_ANIDIRECTION),		SDRATTR_TEXT_ANIDIRECTION,		&::getCppuType((const ::com::sun::star::drawing::TextAnimationDirection*)0),	0,		0}, \
    { MAP_CHAR_LEN(UNO_NAME_TEXT_ANIKIND),			SDRATTR_TEXT_ANIKIND,			&::getCppuType((const ::com::sun::star::drawing::TextAnimationKind*)0),	0,		0}, \
    { MAP_CHAR_LEN(UNO_NAME_TEXT_ANISTARTINSIDE),	SDRATTR_TEXT_ANISTARTINSIDE,	&::getBooleanCppuType(),		0,		0}, \
    { MAP_CHAR_LEN(UNO_NAME_TEXT_ANISTOPINSIDE),	SDRATTR_TEXT_ANISTOPINSIDE,		&::getBooleanCppuType(),		0,		0}, \
    { MAP_CHAR_LEN(UNO_NAME_TEXT_AUTOGROWHEIGHT),	SDRATTR_TEXT_AUTOGROWHEIGHT,	&::getBooleanCppuType(),		0,		0}, \
    { MAP_CHAR_LEN(UNO_NAME_TEXT_AUTOGROWWIDTH),	SDRATTR_TEXT_AUTOGROWWIDTH,		&::getBooleanCppuType(),		0,		0}, \
    { MAP_CHAR_LEN(UNO_NAME_TEXT_CONTOURFRAME),		SDRATTR_TEXT_CONTOURFRAME,		&::getBooleanCppuType(),		0,		0}, \
    { MAP_CHAR_LEN(UNO_NAME_TEXT_FITTOSIZE),		SDRATTR_TEXT_FITTOSIZE,			&::getCppuType((const ::com::sun::star::drawing::TextFitToSizeType*)0),	0,		0}, \
    { MAP_CHAR_LEN(UNO_NAME_TEXT_HORZADJUST),		SDRATTR_TEXT_HORZADJUST,		&::getCppuType((const ::com::sun::star::drawing::TextHorizontalAdjust*)0),	0,		0}, \
    { MAP_CHAR_LEN(UNO_NAME_TEXT_LEFTDIST),			SDRATTR_TEXT_LEFTDIST,			&::getCppuType((const sal_Int32*)0),		0,		SFX_METRIC_ITEM}, \
    { MAP_CHAR_LEN(UNO_NAME_TEXT_LOWERDIST),		SDRATTR_TEXT_LOWERDIST,			&::getCppuType((const sal_Int32*)0),		0,		SFX_METRIC_ITEM}, \
    { MAP_CHAR_LEN(UNO_NAME_TEXT_MAXFRAMEHEIGHT),	SDRATTR_TEXT_MAXFRAMEHEIGHT,	&::getCppuType((const sal_Int32*)0),		0,		SFX_METRIC_ITEM}, \
    { MAP_CHAR_LEN(UNO_NAME_TEXT_MAXFRAMEWIDTH),	SDRATTR_TEXT_MAXFRAMEWIDTH,		&::getCppuType((const sal_Int32*)0),		0,		SFX_METRIC_ITEM}, \
    { MAP_CHAR_LEN(UNO_NAME_TEXT_MINFRAMEHEIGHT),	SDRATTR_TEXT_MINFRAMEHEIGHT,	&::getCppuType((const sal_Int32*)0),		0,		SFX_METRIC_ITEM}, \
    { MAP_CHAR_LEN(UNO_NAME_TEXT_MINFRAMEWIDTH),	SDRATTR_TEXT_MINFRAMEWIDTH,		&::getCppuType((const sal_Int32*)0),		0,		SFX_METRIC_ITEM}, \
    { MAP_CHAR_LEN(UNO_NAME_TEXT_RIGHTDIST),		SDRATTR_TEXT_RIGHTDIST,			&::getCppuType((const sal_Int32*)0),		0,		SFX_METRIC_ITEM}, \
    { MAP_CHAR_LEN(UNO_NAME_TEXT_UPPERDIST),		SDRATTR_TEXT_UPPERDIST,			&::getCppuType((const sal_Int32*)0),		0,		SFX_METRIC_ITEM}, \
    { MAP_CHAR_LEN(UNO_NAME_TEXT_VERTADJUST),		SDRATTR_TEXT_VERTADJUST,		&::getCppuType((const ::com::sun::star::drawing::TextVerticalAdjust*)0),	0,		0},\
    SVX_UNOEDIT_CHAR_PROPERTIES, \
    SVX_UNOEDIT_PARA_PROPERTIES,

#define TEXT_PROPERTIES \
    { MAP_CHAR_LEN("HasLevels"),					OWN_ATTR_HASLEVELS,				&::getBooleanCppuType(), ::com::sun::star::beans::PropertyAttribute::READONLY,		0},\
    SVX_UNOEDIT_NUMBERING_PROPERTIE, \
    TEXT_PROPERTIES_DEFAULTS

#define MISC_OBJ_PROPERTIES_NO_SHEAR \
    { MAP_CHAR_LEN("Transformation"),					OWN_ATTR_TRANSFORMATION,	&::getCppuType((const struct ::com::sun::star::drawing::HomogenMatrix3*)0), 0, 0 }, \
    { MAP_CHAR_LEN(UNO_NAME_MISC_OBJ_ZORDER),			OWN_ATTR_ZORDER,			&::getCppuType((const sal_Int32*)0),		0,		0}, \
    { MAP_CHAR_LEN(UNO_NAME_MISC_OBJ_FRAMERECT),		OWN_ATTR_FRAMERECT,			&::getCppuType((const ::com::sun::star::awt::Rectangle*)0), 0,	0 }, \
    { MAP_CHAR_LEN(UNO_NAME_MISC_OBJ_ROTATEANGLE),		SDRATTR_ROTATEANGLE,		&::getCppuType((const sal_Int32*)0),		0,	0}, \
    { MAP_CHAR_LEN(UNO_NAME_BITMAP),					OWN_ATTR_BITMAP,			&::getCppuType((const ::com::sun::star::uno::Reference< ::com::sun::star::awt::XBitmap >*)0),	::com::sun::star::beans::PropertyAttribute::READONLY, 0}, \
    { MAP_CHAR_LEN(UNO_NAME_OLE2_METAFILE),				OWN_ATTR_METAFILE,			SEQTYPE(::getCppuType((::com::sun::star::uno::Sequence<sal_Int8>*)0)), ::com::sun::star::beans::PropertyAttribute::READONLY, 0}, \
    { MAP_CHAR_LEN("IsFontwork"),						OWN_ATTR_ISFONTWORK,		&::getBooleanCppuType(), ::com::sun::star::beans::PropertyAttribute::READONLY, 0}, \
    { MAP_CHAR_LEN(UNO_NAME_MISC_OBJ_BOUNDRECT),		OWN_ATTR_BOUNDRECT,			&::getCppuType((const ::com::sun::star::awt::Rectangle*)0), ::com::sun::star::beans::PropertyAttribute::READONLY, 0},

#define MISC_OBJ_PROPERTIES \
    MISC_OBJ_PROPERTIES_NO_SHEAR \
    { MAP_CHAR_LEN(UNO_NAME_MISC_OBJ_SHEARANGLE),		SDRATTR_SHEARANGLE,			&::getCppuType((const sal_Int32*)0),		0,	0},

#define SHAPE_DESCRIPTOR_PROPERTIES \
    { MAP_CHAR_LEN(UNO_NAME_MISC_OBJ_LAYERID),		SDRATTR_LAYERID					, &::getCppuType((const sal_Int16*)0),			0,	0}, \
    { MAP_CHAR_LEN(UNO_NAME_MISC_OBJ_LAYERNAME),	SDRATTR_LAYERNAME				, &::getCppuType((const ::rtl::OUString*)0),	0,	0}, \
    { MAP_CHAR_LEN(UNO_NAME_MISC_OBJ_MOVEPROTECT),	SDRATTR_OBJMOVEPROTECT			, &::getBooleanCppuType(),						0,	0}, \
    { MAP_CHAR_LEN(UNO_NAME_MISC_OBJ_NAME),			SDRATTR_OBJECTNAME				, &::getCppuType((const ::rtl::OUString*)0),	0,	0}, \
    { MAP_CHAR_LEN(UNO_NAME_MISC_OBJ_PRINTABLE),	SDRATTR_OBJPRINTABLE			, &::getBooleanCppuType(),						0,	0}, \
    { MAP_CHAR_LEN(UNO_NAME_MISC_OBJ_SIZEPROTECT),	SDRATTR_OBJSIZEPROTECT			, &::getBooleanCppuType(),						0,	0},

#define LINKTARGET_PROPERTIES \
    { MAP_CHAR_LEN(UNO_NAME_LINKDISPLAYNAME),	OWN_ATTR_LDNAME				, &::getCppuType((const ::rtl::OUString*)0),	::com::sun::star::beans::PropertyAttribute::READONLY, 0}, \
    { MAP_CHAR_LEN(UNO_NAME_LINKDISPLAYBITMAP),	OWN_ATTR_LDBITMAP				, &::getCppuType((const ::com::sun::star::uno::Reference< ::com::sun::star::awt::XBitmap >*)0),	::com::sun::star::beans::PropertyAttribute::READONLY, 0},

#define CONNECTOR_PROPERTIES \
    { MAP_CHAR_LEN(UNO_NAME_EDGEKIND),          SDRATTR_EDGEKIND,			&::getCppuType((const ::com::sun::star::drawing::ConnectorType*)0),		0,     0}, \
    { MAP_CHAR_LEN(UNO_NAME_EDGENODE1HORZDIST), SDRATTR_EDGENODE1HORZDIST,  &::getCppuType((const sal_Int32*)0),       0,     0}, \
    { MAP_CHAR_LEN(UNO_NAME_EDGENODE1VERTDIST), SDRATTR_EDGENODE1VERTDIST,  &::getCppuType((const sal_Int32*)0),       0,     0}, \
    { MAP_CHAR_LEN(UNO_NAME_EDGENODE2HORZDIST), SDRATTR_EDGENODE2HORZDIST,  &::getCppuType((const sal_Int32*)0),       0,     0}, \
    { MAP_CHAR_LEN(UNO_NAME_EDGENODE2VERTDIST), SDRATTR_EDGENODE2VERTDIST,  &::getCppuType((const sal_Int32*)0),       0,     0},

#define SPECIAL_CONNECTOR_PROPERTIES \
    CONNECTOR_PROPERTIES \
    { MAP_CHAR_LEN(UNO_NAME_EDGELINE1DELTA),	SDRATTR_EDGELINE1DELTA,     &::getCppuType((const sal_Int32*)0),       0,     SFX_METRIC_ITEM}, \
    { MAP_CHAR_LEN(UNO_NAME_EDGELINE2DELTA),	SDRATTR_EDGELINE2DELTA,     &::getCppuType((const sal_Int32*)0),       0,     SFX_METRIC_ITEM}, \
    { MAP_CHAR_LEN(UNO_NAME_EDGELINE3DELTA),	SDRATTR_EDGELINE3DELTA,     &::getCppuType((const sal_Int32*)0),       0,     SFX_METRIC_ITEM}, \
    { MAP_CHAR_LEN("StartShape"),				OWN_ATTR_EDGE_START_OBJ,	&::getCppuType((const ::com::sun::star::uno::Reference< ::com::sun::star::drawing::XShape >*)0),		::com::sun::star::beans::PropertyAttribute::MAYBEVOID,	 0}, \
    { MAP_CHAR_LEN("StartGluePointIndex"),		OWN_ATTR_GLUEID_HEAD,		&::getCppuType((const sal_Int32*)0),       0,     0}, \
    { MAP_CHAR_LEN("StartPosition"),			OWN_ATTR_EDGE_START_POS,	&::getCppuType((const ::com::sun::star::awt::Point*)0),		0,	 0}, \
    { MAP_CHAR_LEN("EndShape"),					OWN_ATTR_EDGE_END_OBJ,		&::getCppuType((const ::com::sun::star::uno::Reference< ::com::sun::star::drawing::XShape>*)0),		::com::sun::star::beans::PropertyAttribute::MAYBEVOID,	 0}, \
    { MAP_CHAR_LEN("EndPosition"),				OWN_ATTR_EDGE_END_POS,		&::getCppuType((const ::com::sun::star::awt::Point*)0),		0,	 0},\
    { MAP_CHAR_LEN("EndGluePointIndex"),		OWN_ATTR_GLUEID_TAIL,		&::getCppuType((const sal_Int32*)0),       0,     0}, \
\
    { MAP_CHAR_LEN("EdgeStartConnection"),		OWN_ATTR_EDGE_START_OBJ,	&::getCppuType((const ::com::sun::star::uno::Reference< ::com::sun::star::drawing::XShape >*)0),		::com::sun::star::beans::PropertyAttribute::MAYBEVOID,	 0}, \
    { MAP_CHAR_LEN("EdgeStartPoint"),			OWN_ATTR_EDGE_START_POS,	&::getCppuType((const ::com::sun::star::awt::Point*)0),		::com::sun::star::beans::PropertyAttribute::READONLY,	 0}, \
    { MAP_CHAR_LEN("EdgeEndConnection"),		OWN_ATTR_EDGE_END_OBJ,		&::getCppuType((const ::com::sun::star::uno::Reference< ::com::sun::star::drawing::XShape>*)0),		::com::sun::star::beans::PropertyAttribute::MAYBEVOID,	 0}, \
    { MAP_CHAR_LEN("EdgeEndPoint"),				OWN_ATTR_EDGE_END_POS,		&::getCppuType((const ::com::sun::star::awt::Point*)0),		::com::sun::star::beans::PropertyAttribute::READONLY,	 0},

#define SPECIAL_DIMENSIONING_PROPERTIES_DEFAULTS \
    { MAP_CHAR_LEN(UNO_NAME_MEASUREBELOWREFEDGE),		SDRATTR_MEASUREBELOWREFEDGE,		&::getBooleanCppuType(),		0,	0}, \
    { MAP_CHAR_LEN(UNO_NAME_MEASUREFORMATSTRING),		SDRATTR_MEASUREFORMATSTRING,		&::getCppuType((const ::rtl::OUString*)0),		0,	0}, \
    { MAP_CHAR_LEN(UNO_NAME_MEASUREHELPLINE1LEN),		SDRATTR_MEASUREHELPLINE1LEN,		&::getCppuType((const sal_Int32*)0),		0,	SFX_METRIC_ITEM}, \
    { MAP_CHAR_LEN(UNO_NAME_MEASUREHELPLINE2LEN),		SDRATTR_MEASUREHELPLINE2LEN,		&::getCppuType((const sal_Int32*)0),		0,	SFX_METRIC_ITEM}, \
    { MAP_CHAR_LEN(UNO_NAME_MEASUREHELPLINEDIST),		SDRATTR_MEASUREHELPLINEDIST,		&::getCppuType((const sal_Int32*)0),		0,	SFX_METRIC_ITEM}, \
    { MAP_CHAR_LEN(UNO_NAME_MEASUREHELPLINEOVERHANG),	SDRATTR_MEASUREHELPLINEOVERHANG,	&::getCppuType((const sal_Int32*)0),		0,	SFX_METRIC_ITEM}, \
    { MAP_CHAR_LEN(UNO_NAME_MEASUREKIND),				SDRATTR_MEASUREKIND,				&::getCppuType((const ::com::sun::star::drawing::MeasureKind*)0),	0,	0}, \
    { MAP_CHAR_LEN(UNO_NAME_MEASURELINEDIST),			SDRATTR_MEASURELINEDIST,			&::getCppuType((const sal_Int32*)0),		0,	SFX_METRIC_ITEM}, \
    { MAP_CHAR_LEN(UNO_NAME_MEASUREOVERHANG),			SDRATTR_MEASUREOVERHANG,			&::getCppuType((const sal_Int32*)0),		0,	SFX_METRIC_ITEM}, \
    { MAP_CHAR_LEN(UNO_NAME_MEASUREUNIT),				SDRATTR_MEASUREUNIT,				&::getCppuType((const sal_Int32*)0),	0,	0},\
    { MAP_CHAR_LEN(UNO_NAME_MEASURESHOWUNIT),			SDRATTR_MEASURESHOWUNIT,			&::getBooleanCppuType(),		0,	0}, \
    { MAP_CHAR_LEN(UNO_NAME_MEASURETEXTAUTOANGLE),		SDRATTR_MEASURETEXTAUTOANGLE,		&::getBooleanCppuType(),		0,	0}, \
    { MAP_CHAR_LEN(UNO_NAME_MEASURETEXTAUTOANGLEVIEW),	SDRATTR_MEASURETEXTAUTOANGLEVIEW,	&::getCppuType((const sal_Int32*)0),		0,	0}, \
    { MAP_CHAR_LEN(UNO_NAME_MEASURETEXTFIXEDANGLE),		SDRATTR_MEASURETEXTFIXEDANGLE,		&::getCppuType((const sal_Int32*)0),		0,	0}, \
    { MAP_CHAR_LEN(UNO_NAME_MEASURETEXTHPOS),			SDRATTR_MEASURETEXTHPOS,			&::getCppuType((const ::com::sun::star::drawing::MeasureTextHorzPos*)0),	0,	0}, \
    { MAP_CHAR_LEN(UNO_NAME_MEASURETEXTISFIXEDANGLE),	SDRATTR_MEASURETEXTISFIXEDANGLE,	&::getBooleanCppuType(),		0,	0}, \
    { MAP_CHAR_LEN(UNO_NAME_MEASURETEXTROTA90),			SDRATTR_MEASURETEXTROTA90,			&::getBooleanCppuType(),		0,	0}, \
    { MAP_CHAR_LEN(UNO_NAME_MEASURETEXTUPSIDEDOWN),		SDRATTR_MEASURETEXTUPSIDEDOWN,		&::getBooleanCppuType(),		0,	0}, \
    { MAP_CHAR_LEN(UNO_NAME_MEASURETEXTVPOS),			SDRATTR_MEASURETEXTVPOS,			&::getCppuType((const ::com::sun::star::drawing::MeasureTextVertPos*)0),	0,	0}, \
    { MAP_CHAR_LEN("MeasureDecimalPlaces"),				SDRATTR_MEASUREDECIMALPLACES,		&::getCppuType((const sal_Int16*)0),		0,	0},

#define SPECIAL_DIMENSIONING_PROPERTIES \
    SPECIAL_DIMENSIONING_PROPERTIES_DEFAULTS \
    { MAP_CHAR_LEN("StartPosition"),					OWN_ATTR_MEASURE_START_POS,			&::getCppuType((const ::com::sun::star::awt::Point*)0),		0,	 0},\
    { MAP_CHAR_LEN("EndPosition"),						OWN_ATTR_MEASURE_END_POS,			&::getCppuType((const ::com::sun::star::awt::Point*)0),		0,	 0},

#define SPECIAL_CIRCLE_PROPERTIES \
    { MAP_CHAR_LEN(UNO_NAME_CIRCENDANGLE),	SDRATTR_CIRCENDANGLE,	&::getCppuType((const sal_Int32*)0),		0,	0}, \
    { MAP_CHAR_LEN(UNO_NAME_CIRCKIND),		SDRATTR_CIRCKIND,		&::getCppuType((const ::com::sun::star::drawing::CircleKind*)0),	0,	0}, \
    { MAP_CHAR_LEN(UNO_NAME_CIRCSTARTANGLE),SDRATTR_CIRCSTARTANGLE,	&::getCppuType((const sal_Int32*)0),		0,	0},

#define SPECIAL_POLYGON_PROPERTIES \
    { MAP_CHAR_LEN(UNO_NAME_POLYGONKIND),	OWN_ATTR_VALUE_POLYGONKIND,	&::getCppuType((const ::com::sun::star::drawing::PolygonKind*)0), ::com::sun::star::beans::PropertyAttribute::READONLY,	0},

#define SPECIAL_POLYPOLYGON_PROPERTIES \
    { MAP_CHAR_LEN(UNO_NAME_POLYPOLYGON),	OWN_ATTR_VALUE_POLYPOLYGON,	SEQTYPE(::getCppuType((const ::com::sun::star::drawing::PointSequenceSequence*)0)),	0,	0}, \
    { MAP_CHAR_LEN(UNO_NAME_POLYGON),		OWN_ATTR_VALUE_POLYGON,		SEQTYPE(::getCppuType((const ::com::sun::star::drawing::PointSequence*)0)),			0,	0},

#define SPECIAL_POLYPOLYGONBEZIER_PROPERTIES \
    { MAP_CHAR_LEN(UNO_NAME_POLYPOLYGONBEZIER),	OWN_ATTR_VALUE_POLYPOLYGONBEZIER,	&::getCppuType((const ::com::sun::star::drawing::PolyPolygonBezierCoords*)0),		0,	0},

#define SPECIAL_GRAPHOBJ_PROPERTIES_DEFAULTS \
    { MAP_CHAR_LEN(UNO_NAME_GRAPHIC_LUMINANCE),		SDRATTR_GRAFLUMINANCE		, &::getCppuType((const sal_Int16*)0),			0,	 0}, \
    { MAP_CHAR_LEN(UNO_NAME_GRAPHIC_CONTRAST),		SDRATTR_GRAFCONTRAST		, &::getCppuType((const sal_Int16*)0),			0,	 0}, \
    { MAP_CHAR_LEN(UNO_NAME_GRAPHIC_RED),			SDRATTR_GRAFRED				, &::getCppuType((const sal_Int16*)0),			0,	 0}, \
    { MAP_CHAR_LEN(UNO_NAME_GRAPHIC_GREEN),			SDRATTR_GRAFGREEN			, &::getCppuType((const sal_Int16*)0),			0,	 0}, \
    { MAP_CHAR_LEN(UNO_NAME_GRAPHIC_BLUE),			SDRATTR_GRAFBLUE			, &::getCppuType((const sal_Int16*)0),			0,	 0}, \
    { MAP_CHAR_LEN(UNO_NAME_GRAPHIC_GAMMA),			SDRATTR_GRAFGAMMA			, &::getCppuType((const double*)0),		0,	 0}, \
    { MAP_CHAR_LEN(UNO_NAME_GRAPHIC_TRANSPARENCY),	SDRATTR_GRAFTRANSPARENCE	, &::getCppuType((const sal_Int16*)0),			0,	 0}, \
    { MAP_CHAR_LEN(UNO_NAME_GRAPHIC_COLOR_MODE),	SDRATTR_GRAFMODE			, &::getCppuType((const ::com::sun::star::drawing::ColorMode*)0),		0,	 0},

#define SPECIAL_GRAPHOBJ_PROPERTIES \
    SPECIAL_GRAPHOBJ_PROPERTIES_DEFAULTS \
    { MAP_CHAR_LEN(UNO_NAME_GRAPHIC_GRAPHICCROP),	SDRATTR_GRAFCROP			, &::getCppuType((const ::com::sun::star::text::GraphicCrop*)0),		0,	0 }, \
    { MAP_CHAR_LEN(UNO_NAME_GRAPHOBJ_GRAFURL),		OWN_ATTR_GRAFURL			, &::getCppuType((const ::rtl::OUString*)0), 0, 0 }, \
    { MAP_CHAR_LEN(UNO_NAME_GRAPHOBJ_GRAFSTREAMURL),OWN_ATTR_GRAFSTREAMURL		, &::getCppuType((const ::rtl::OUString*)0), ::com::sun::star::beans::PropertyAttribute::MAYBEVOID, 0 }, \
    { MAP_CHAR_LEN(UNO_NAME_GRAPHOBJ_FILLBITMAP),	OWN_ATTR_VALUE_FILLBITMAP	, &::getCppuType((const ::com::sun::star::uno::Reference< ::com::sun::star::awt::XBitmap>*)0)  , 	0,     0},

#define SPECIAL_3DSCENEOBJECT_PROPERTIES_DEFAULTS \
    { MAP_CHAR_LEN(UNO_NAME_3D_SCENE_AMBIENTCOLOR),		SDRATTR_3DSCENE_AMBIENTCOLOR   , &::getCppuType((const sal_Int32*)0),	0,	0}, \
    { MAP_CHAR_LEN(UNO_NAME_3D_SCENE_DISTANCE),			SDRATTR_3DSCENE_DISTANCE	   , &::getCppuType((const sal_Int32*)0),	0,	SFX_METRIC_ITEM}, \
    { MAP_CHAR_LEN(UNO_NAME_3D_SCENE_FOCAL_LENGTH),		SDRATTR_3DSCENE_FOCAL_LENGTH   , &::getCppuType((const sal_Int32*)0),	0,	SFX_METRIC_ITEM}, \
    { MAP_CHAR_LEN(UNO_NAME_3D_SCENE_LIGHTCOLOR_1),		SDRATTR_3DSCENE_LIGHTCOLOR_1       , &::getCppuType((const sal_Int32*)0),	0,	0}, \
    { MAP_CHAR_LEN(UNO_NAME_3D_SCENE_LIGHTCOLOR_2),		SDRATTR_3DSCENE_LIGHTCOLOR_2       , &::getCppuType((const sal_Int32*)0),	0,	0}, \
    { MAP_CHAR_LEN(UNO_NAME_3D_SCENE_LIGHTCOLOR_3),		SDRATTR_3DSCENE_LIGHTCOLOR_3       , &::getCppuType((const sal_Int32*)0),	0,	0}, \
    { MAP_CHAR_LEN(UNO_NAME_3D_SCENE_LIGHTCOLOR_4),		SDRATTR_3DSCENE_LIGHTCOLOR_4       , &::getCppuType((const sal_Int32*)0),	0,	0}, \
    { MAP_CHAR_LEN(UNO_NAME_3D_SCENE_LIGHTCOLOR_5),		SDRATTR_3DSCENE_LIGHTCOLOR_5       , &::getCppuType((const sal_Int32*)0),	0,	0}, \
    { MAP_CHAR_LEN(UNO_NAME_3D_SCENE_LIGHTCOLOR_6),		SDRATTR_3DSCENE_LIGHTCOLOR_6       , &::getCppuType((const sal_Int32*)0),	0,	0}, \
    { MAP_CHAR_LEN(UNO_NAME_3D_SCENE_LIGHTCOLOR_7),		SDRATTR_3DSCENE_LIGHTCOLOR_7       , &::getCppuType((const sal_Int32*)0),	0,	0}, \
    { MAP_CHAR_LEN(UNO_NAME_3D_SCENE_LIGHTCOLOR_8),		SDRATTR_3DSCENE_LIGHTCOLOR_8       , &::getCppuType((const sal_Int32*)0),	0,	0}, \
    { MAP_CHAR_LEN(UNO_NAME_3D_SCENE_LIGHTDIRECTION_1),	SDRATTR_3DSCENE_LIGHTDIRECTION_1   , &::getCppuType((const ::com::sun::star::drawing::Direction3D*)0),	0,	0}, \
    { MAP_CHAR_LEN(UNO_NAME_3D_SCENE_LIGHTDIRECTION_2),	SDRATTR_3DSCENE_LIGHTDIRECTION_2   , &::getCppuType((const ::com::sun::star::drawing::Direction3D*)0),	0,	0}, \
    { MAP_CHAR_LEN(UNO_NAME_3D_SCENE_LIGHTDIRECTION_3),	SDRATTR_3DSCENE_LIGHTDIRECTION_3   , &::getCppuType((const ::com::sun::star::drawing::Direction3D*)0),	0,	0}, \
    { MAP_CHAR_LEN(UNO_NAME_3D_SCENE_LIGHTDIRECTION_4),	SDRATTR_3DSCENE_LIGHTDIRECTION_4   , &::getCppuType((const ::com::sun::star::drawing::Direction3D*)0),	0,	0}, \
    { MAP_CHAR_LEN(UNO_NAME_3D_SCENE_LIGHTDIRECTION_5),	SDRATTR_3DSCENE_LIGHTDIRECTION_5   , &::getCppuType((const ::com::sun::star::drawing::Direction3D*)0),	0,	0}, \
    { MAP_CHAR_LEN(UNO_NAME_3D_SCENE_LIGHTDIRECTION_6),	SDRATTR_3DSCENE_LIGHTDIRECTION_6   , &::getCppuType((const ::com::sun::star::drawing::Direction3D*)0),	0,	0}, \
    { MAP_CHAR_LEN(UNO_NAME_3D_SCENE_LIGHTDIRECTION_7),	SDRATTR_3DSCENE_LIGHTDIRECTION_7   , &::getCppuType((const ::com::sun::star::drawing::Direction3D*)0),	0,	0}, \
    { MAP_CHAR_LEN(UNO_NAME_3D_SCENE_LIGHTDIRECTION_8),	SDRATTR_3DSCENE_LIGHTDIRECTION_8   , &::getCppuType((const ::com::sun::star::drawing::Direction3D*)0),	0,	0}, \
    { MAP_CHAR_LEN(UNO_NAME_3D_SCENE_LIGHTON_1),		SDRATTR_3DSCENE_LIGHTON_1          , &::getBooleanCppuType(),	0,	0}, \
    { MAP_CHAR_LEN(UNO_NAME_3D_SCENE_LIGHTON_2),		SDRATTR_3DSCENE_LIGHTON_2          , &::getBooleanCppuType(),	0,	0}, \
    { MAP_CHAR_LEN(UNO_NAME_3D_SCENE_LIGHTON_3),		SDRATTR_3DSCENE_LIGHTON_3          , &::getBooleanCppuType(),	0,	0}, \
    { MAP_CHAR_LEN(UNO_NAME_3D_SCENE_LIGHTON_4),		SDRATTR_3DSCENE_LIGHTON_4          , &::getBooleanCppuType(),	0,	0}, \
    { MAP_CHAR_LEN(UNO_NAME_3D_SCENE_LIGHTON_5),		SDRATTR_3DSCENE_LIGHTON_5          , &::getBooleanCppuType(),	0,	0}, \
    { MAP_CHAR_LEN(UNO_NAME_3D_SCENE_LIGHTON_6),		SDRATTR_3DSCENE_LIGHTON_6          , &::getBooleanCppuType(),	0,	0}, \
    { MAP_CHAR_LEN(UNO_NAME_3D_SCENE_LIGHTON_7),		SDRATTR_3DSCENE_LIGHTON_7          , &::getBooleanCppuType(),	0,	0}, \
    { MAP_CHAR_LEN(UNO_NAME_3D_SCENE_LIGHTON_8),		SDRATTR_3DSCENE_LIGHTON_8          , &::getBooleanCppuType(),	0,	0}, \
    { MAP_CHAR_LEN(UNO_NAME_3D_SCENE_PERSPECTIVE),		SDRATTR_3DSCENE_PERSPECTIVE    , &::getCppuType((const ::com::sun::star::drawing::ProjectionMode*)0),	0,	0}, \
    { MAP_CHAR_LEN(UNO_NAME_3D_SCENE_SHADOW_SLANT),		SDRATTR_3DSCENE_SHADOW_SLANT   , &::getCppuType((const sal_Int16*)0),	0,	0}, \
    { MAP_CHAR_LEN(UNO_NAME_3D_SCENE_SHADE_MODE),		SDRATTR_3DSCENE_SHADE_MODE     , &::getCppuType((const ::com::sun::star::drawing::ShadeMode*)0),	0,	0}, \
    { MAP_CHAR_LEN(UNO_NAME_3D_SCENE_TWO_SIDED_LIGHTING),SDRATTR_3DSCENE_TWO_SIDED_LIGHTING, &::getBooleanCppuType(),	0,	0},

#define SPECIAL_3DSCENEOBJECT_PROPERTIES \
    SPECIAL_3DSCENEOBJECT_PROPERTIES_DEFAULTS \
    { MAP_CHAR_LEN(UNO_NAME_3D_TRANSFORM_MATRIX),		OWN_ATTR_3D_VALUE_TRANSFORM_MATRIX	, &::getCppuType((const ::com::sun::star::drawing::HomogenMatrix*)0), 0, 0}, \
    { MAP_CHAR_LEN(UNO_NAME_3D_CAMERA_GEOMETRY),		OWN_ATTR_3D_VALUE_CAMERA_GEOMETRY	, &::getCppuType((const ::com::sun::star::drawing::CameraGeometry*)0), 0, 0},

#define MISC_3D_OBJ_PROPERTIES \
    { MAP_CHAR_LEN(UNO_NAME_3D_DOUBLE_SIDED				),SDRATTR_3DOBJ_DOUBLE_SIDED			, &::getBooleanCppuType(), 0, 0}, \
    { MAP_CHAR_LEN(UNO_NAME_3D_MAT_COLOR				),SDRATTR_3DOBJ_MAT_COLOR				, &::getCppuType((const sal_Int32*)0), 0, 0}, \
    { MAP_CHAR_LEN(UNO_NAME_3D_MAT_EMISSION				),SDRATTR_3DOBJ_MAT_EMISSION			, &::getCppuType((const sal_Int32*)0), 0, 0}, \
    { MAP_CHAR_LEN(UNO_NAME_3D_MAT_SPECULAR				),SDRATTR_3DOBJ_MAT_SPECULAR			, &::getCppuType((const sal_Int32*)0), 0, 0}, \
    { MAP_CHAR_LEN(UNO_NAME_3D_MAT_SPECULAR_INTENSITY	),SDRATTR_3DOBJ_MAT_SPECULAR_INTENSITY	, &::getCppuType((const sal_Int16*)0), 0, 0}, \
    { MAP_CHAR_LEN(UNO_NAME_3D_NORMALS_INVERT			),SDRATTR_3DOBJ_NORMALS_INVERT			, &::getBooleanCppuType(), 0, 0}, \
    { MAP_CHAR_LEN(UNO_NAME_3D_NORMALS_KIND				),SDRATTR_3DOBJ_NORMALS_KIND			, &::getCppuType((const ::com::sun::star::drawing::NormalsKind*)0), 0, 0}, \
    { MAP_CHAR_LEN(UNO_NAME_3D_SHADOW_3D				),SDRATTR_3DOBJ_SHADOW_3D				, &::getBooleanCppuType(), 0, 0}, \
    { MAP_CHAR_LEN(UNO_NAME_3D_TEXTURE_FILTER			),SDRATTR_3DOBJ_TEXTURE_FILTER			, &::getBooleanCppuType(), 0, 0}, \
    { MAP_CHAR_LEN(UNO_NAME_3D_TEXTURE_KIND				),SDRATTR_3DOBJ_TEXTURE_KIND			, &::getCppuType((const ::com::sun::star::drawing::TextureKind*)0), 0, 0}, \
    { MAP_CHAR_LEN(UNO_NAME_3D_TEXTURE_MODE				),SDRATTR_3DOBJ_TEXTURE_MODE			, &::getCppuType((const ::com::sun::star::drawing::TextureMode*)0), 0, 0}, \
    { MAP_CHAR_LEN(UNO_NAME_3D_TEXTURE_PROJ_X			),SDRATTR_3DOBJ_TEXTURE_PROJ_X			, &::getCppuType((const ::com::sun::star::drawing::TextureProjectionMode*)0), 0, 0}, \
    { MAP_CHAR_LEN(UNO_NAME_3D_TEXTURE_PROJ_Y			),SDRATTR_3DOBJ_TEXTURE_PROJ_Y			, &::getCppuType((const ::com::sun::star::drawing::TextureProjectionMode*)0), 0, 0},

#define SPECIAL_3DCUBEOBJECT_PROPERTIES \
    { MAP_CHAR_LEN(UNO_NAME_3D_TRANSFORM_MATRIX	),OWN_ATTR_3D_VALUE_TRANSFORM_MATRIX	, &::getCppuType((const ::com::sun::star::drawing::HomogenMatrix*)0), 0, 0}, \
    { MAP_CHAR_LEN(UNO_NAME_3D_POS				),OWN_ATTR_3D_VALUE_POSITION			, &::getCppuType((const ::com::sun::star::drawing::Position3D*)0), 0, 0}, \
    { MAP_CHAR_LEN(UNO_NAME_3D_SIZE				),OWN_ATTR_3D_VALUE_SIZE				, &::getCppuType((const ::com::sun::star::drawing::Direction3D*)0), 0, 0}, \
    { MAP_CHAR_LEN(UNO_NAME_3D_POS_IS_CENTER	),OWN_ATTR_3D_VALUE_POS_IS_CENTER	, &::getBooleanCppuType(), 0, 0},

#define SPECIAL_3DSPHEREOBJECT_PROPERTIES \
    { MAP_CHAR_LEN(UNO_NAME_3D_TRANSFORM_MATRIX	),OWN_ATTR_3D_VALUE_TRANSFORM_MATRIX	, &::getCppuType((const ::com::sun::star::drawing::HomogenMatrix*)0), 0, 0}, \
    { MAP_CHAR_LEN(UNO_NAME_3D_POS				),OWN_ATTR_3D_VALUE_POSITION			, &::getCppuType((const ::com::sun::star::drawing::Position3D*)0), 0, 0}, \
    { MAP_CHAR_LEN(UNO_NAME_3D_SIZE				),OWN_ATTR_3D_VALUE_SIZE				, &::getCppuType((const ::com::sun::star::drawing::Direction3D*)0), 0, 0}, \
    { MAP_CHAR_LEN(UNO_NAME_3D_HORZ_SEGS		),SDRATTR_3DOBJ_HORZ_SEGS, &::getCppuType((const sal_Int32*)0), 0, 0}, \
    { MAP_CHAR_LEN(UNO_NAME_3D_VERT_SEGS		),SDRATTR_3DOBJ_VERT_SEGS, &::getCppuType((const sal_Int32*)0), 0, 0},

// #107245# New 3D properties which are possible for lathe and extrude 3d objects
#define SPECIAL_3DLATHEANDEXTRUDEOBJ_PROPERTIES \
    { MAP_CHAR_LEN(UNO_NAME_3D_SMOOTH_NORMALS	), SDRATTR_3DOBJ_SMOOTH_NORMALS,	&::getBooleanCppuType(), 0, 0}, \
    { MAP_CHAR_LEN(UNO_NAME_3D_SMOOTH_LIDS		), SDRATTR_3DOBJ_SMOOTH_LIDS,		&::getBooleanCppuType(), 0, 0}, \
    { MAP_CHAR_LEN(UNO_NAME_3D_CHARACTER_MODE	), SDRATTR_3DOBJ_CHARACTER_MODE,	&::getBooleanCppuType(), 0, 0}, \
    { MAP_CHAR_LEN(UNO_NAME_3D_CLOSE_FRONT		), SDRATTR_3DOBJ_CLOSE_FRONT,		&::getBooleanCppuType(), 0, 0}, \
    { MAP_CHAR_LEN(UNO_NAME_3D_CLOSE_BACK		), SDRATTR_3DOBJ_CLOSE_BACK,		&::getBooleanCppuType(), 0, 0},

#define SPECIAL_3DLATHEOBJECT_PROPERTIES \
    { MAP_CHAR_LEN(UNO_NAME_3D_TRANSFORM_MATRIX	),OWN_ATTR_3D_VALUE_TRANSFORM_MATRIX	,&::getCppuType((const ::com::sun::star::drawing::HomogenMatrix*)0), 0, 0}, \
    { MAP_CHAR_LEN(UNO_NAME_3D_POLYPOLYGON3D	),OWN_ATTR_3D_VALUE_POLYPOLYGON3D	,&::getCppuType((const ::com::sun::star::drawing::PolyPolygonShape3D*)0), 0, 0}, \
    { MAP_CHAR_LEN(UNO_NAME_3D_LATHE_END_ANGLE	),SDRATTR_3DOBJ_END_ANGLE			,&::getCppuType((const sal_Int16*)0), 0, 0}, \
    { MAP_CHAR_LEN(UNO_NAME_3D_HORZ_SEGS		),SDRATTR_3DOBJ_HORZ_SEGS			,&::getCppuType((const sal_Int32*)0), 0, 0}, \
    { MAP_CHAR_LEN(UNO_NAME_3D_PERCENT_DIAGONAL	),SDRATTR_3DOBJ_PERCENT_DIAGONAL	,&::getCppuType((const sal_Int16*)0), 0, 0}, \
    { MAP_CHAR_LEN(UNO_NAME_3D_VERT_SEGS		),SDRATTR_3DOBJ_VERT_SEGS			,&::getCppuType((const sal_Int32*)0), 0, 0},

#define SPECIAL_3DEXTRUDEOBJECT_PROPERTIES \
    { MAP_CHAR_LEN(UNO_NAME_3D_TRANSFORM_MATRIX	),OWN_ATTR_3D_VALUE_TRANSFORM_MATRIX	,&::getCppuType((const ::com::sun::star::drawing::HomogenMatrix*)0), 0, 0}, \
    { MAP_CHAR_LEN(UNO_NAME_3D_POLYPOLYGON3D	),OWN_ATTR_3D_VALUE_POLYPOLYGON3D	,&::getCppuType((const ::com::sun::star::drawing::PolyPolygonShape3D*)0), 0, 0}, \
    { MAP_CHAR_LEN(UNO_NAME_3D_EXTRUDE_DEPTH	),SDRATTR_3DOBJ_DEPTH				,&::getCppuType((const sal_Int32*)0), 0, SFX_METRIC_ITEM}, \
    { MAP_CHAR_LEN(UNO_NAME_3D_PERCENT_DIAGONAL	),SDRATTR_3DOBJ_PERCENT_DIAGONAL	,&::getCppuType((const sal_Int16*)0), 0, 0},

#define SPECIAL_3DPOLYGONOBJECT_PROPERTIES \
    { MAP_CHAR_LEN(UNO_NAME_3D_TRANSFORM_MATRIX	),OWN_ATTR_3D_VALUE_TRANSFORM_MATRIX	, &::getCppuType((const ::com::sun::star::drawing::HomogenMatrix*)0), 0, 0}, \
    { MAP_CHAR_LEN(UNO_NAME_3D_POLYPOLYGON3D	),OWN_ATTR_3D_VALUE_POLYPOLYGON3D	, &::getCppuType((const ::com::sun::star::drawing::PolyPolygonShape3D*)0), 0, 0}, \
    { MAP_CHAR_LEN(UNO_NAME_3D_NORMALSPOLYGON3D	),OWN_ATTR_3D_VALUE_POLYPOLYGON3D	, &::getCppuType((const ::com::sun::star::drawing::PolyPolygonShape3D*)0), 0, 0}, \
    { MAP_CHAR_LEN(UNO_NAME_3D_TEXTUREPOLYGON3D	),OWN_ATTR_3D_VALUE_POLYPOLYGON3D	, &::getCppuType((const ::com::sun::star::drawing::PolyPolygonShape3D*)0), 0, 0}, \
    { MAP_CHAR_LEN(UNO_NAME_3D_LINEONLY			),OWN_ATTR_3D_VALUE_LINEONLY		, &::getBooleanCppuType(), 0, 0},

#define SPECIAL_3DBACKSCALE_PROPERTIES \
    { MAP_CHAR_LEN(UNO_NAME_3D_BACKSCALE		),SDRATTR_3DOBJ_BACKSCALE			,&::getCppuType((const sal_Int16*)0), 0, 0}, \

#define AUTOSHAPE_PROPERTIES \
    { MAP_CHAR_LEN(UNO_NAME_AUTOSHAPE_ADJUSTMENT),SDRATTR_AUTOSHAPE_ADJUSTMENT,			SEQTYPE(::getCppuType((::com::sun::star::uno::Sequence<sal_Int32>*)0)), 0, 0}, \

}//end of namespace binfilter
#endif

