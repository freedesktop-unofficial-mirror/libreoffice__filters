/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: shapeimport.hxx,v $
 *
 *  $Revision: 1.4 $
 *
 *  last change: $Author: ihi $ $Date: 2006-11-14 12:26:01 $
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

#ifndef _XMLOFF_SHAPEIMPORT_HXX_
#define _XMLOFF_SHAPEIMPORT_HXX_

#ifndef _COM_SUN_STAR_BEANS_XPROPERTYSET_HPP_ 
#include <com/sun/star/beans/XPropertySet.hpp>
#endif

#ifndef _COM_SUN_STAR_FRAME_XMODEL_HPP_
#include <com/sun/star/frame/XModel.hpp>
#endif

#ifndef _COM_SUN_STAR_XML_SAX_XATTRIBUTELIST_HPP_
#include <com/sun/star/xml/sax/XAttributeList.hpp>
#endif

#ifndef _COM_SUN_STAR_DRAWING_XSHAPES_HPP_
#include <com/sun/star/drawing/XShapes.hpp>
#endif

#ifndef _COM_SUN_STAR_DRAWING_HOMOGENMATRIX_HPP_
#include <com/sun/star/drawing/HomogenMatrix.hpp>
#endif

#ifndef _COM_SUN_STAR_DRAWING_PROJECTIONMODE_HPP_
#include <com/sun/star/drawing/ProjectionMode.hpp>
#endif

#ifndef _COM_SUN_STAR_DRAWING_SHADEMODE_HPP_
#include <com/sun/star/drawing/ShadeMode.hpp>
#endif

#ifndef _TOOLS_COLOR_HXX 
#include <tools/color.hxx>
#endif

#ifndef _SVX_VECTOR3D_HXX
#include <bf_goodies/vector3d.hxx>
#endif

#ifndef _UNIVERSALL_REFERENCE_HXX
#include <bf_xmloff/uniref.hxx>
#endif

#ifndef _XMLOFF_XMLICTXT_HXX 
#include <bf_xmloff/xmlictxt.hxx>
#endif
namespace binfilter {

class SvXMLImport;
class SvXMLImportContext;
class SvXMLTokenMap;
class SvXMLStylesContext;
class XMLSdPropHdlFactory;
class XMLPropertySetMapper;
class SvXMLImportPropertyMapper;

//////////////////////////////////////////////////////////////////////////////

enum SdXMLGroupShapeElemTokenMap
{
    XML_TOK_GROUP_GROUP,
    XML_TOK_GROUP_RECT,
    XML_TOK_GROUP_LINE,
    XML_TOK_GROUP_CIRCLE,
    XML_TOK_GROUP_ELLIPSE,
    XML_TOK_GROUP_POLYGON,
    XML_TOK_GROUP_POLYLINE,
    XML_TOK_GROUP_PATH,
    XML_TOK_GROUP_TEXT_BOX,

    XML_TOK_GROUP_CONTROL,
    XML_TOK_GROUP_CONNECTOR,
    XML_TOK_GROUP_MEASURE,
    XML_TOK_GROUP_PAGE,
    XML_TOK_GROUP_CAPTION,

    XML_TOK_GROUP_CHART,
    XML_TOK_GROUP_IMAGE,
    XML_TOK_GROUP_3DSCENE,

    XML_TOK_GROUP_OBJECT,
    XML_TOK_GROUP_OBJECT_OLE,

    XML_TOK_GROUP_PLUGIN,
    XML_TOK_GROUP_FRAME,
    XML_TOK_GROUP_APPLET,

    XML_TOK_GROUP_LAST
};

enum SdXML3DSceneShapeElemTokenMap
{
    XML_TOK_3DSCENE_3DSCENE,
    XML_TOK_3DSCENE_3DCUBE,
    XML_TOK_3DSCENE_3DSPHERE,
    XML_TOK_3DSCENE_3DLATHE,
    XML_TOK_3DSCENE_3DEXTRUDE,

    XML_TOK_3DSCENE_LAST
};

enum SdXMLShapeAttrTokenMap
{
    XML_TOK_SHAPE_NAME,
    XML_TOK_SHAPE_DRAWSTYLE_NAME_GRAPHICS,
    XML_TOK_SHAPE_PRESENTATION_CLASS,
    XML_TOK_SHAPE_DRAWSTYLE_NAME_PRESENTATION,
    XML_TOK_SHAPE_TRANSFORM,
    XML_TOK_SHAPE_IS_PLACEHOLDER,
    XML_TOK_SHAPE_IS_USER_TRANSFORMED
};

enum SdXML3DObjectAttrTokenMap
{
    XML_TOK_3DOBJECT_DRAWSTYLE_NAME,
    XML_TOK_3DOBJECT_TRANSFORM
};

enum SdXML3DPolygonBasedAttrTokenMap
{
    XML_TOK_3DPOLYGONBASED_VIEWBOX,
    XML_TOK_3DPOLYGONBASED_D
};

enum SdXML3DCubeObjectAttrTokenMap
{
    XML_TOK_3DCUBEOBJ_MINEDGE,
    XML_TOK_3DCUBEOBJ_MAXEDGE
};

enum SdXML3DSphereObjectAttrTokenMap
{
    XML_TOK_3DSPHEREOBJ_CENTER,
    XML_TOK_3DSPHEREOBJ_SIZE
};

enum SdXMLPolygonShapeAttrTokenMap
{
    XML_TOK_POLYGONSHAPE_VIEWBOX,
    XML_TOK_POLYGONSHAPE_POINTS
};

enum SdXMLPathShapeAttrTokenMap
{
    XML_TOK_PATHSHAPE_VIEWBOX,
    XML_TOK_PATHSHAPE_D
};

enum SdXML3DSceneShapeAttrTokenMap
{
    XML_TOK_3DSCENESHAPE_TRANSFORM,
    XML_TOK_3DSCENESHAPE_VRP,
    XML_TOK_3DSCENESHAPE_VPN,
    XML_TOK_3DSCENESHAPE_VUP,
    XML_TOK_3DSCENESHAPE_PROJECTION,
    XML_TOK_3DSCENESHAPE_DISTANCE,
    XML_TOK_3DSCENESHAPE_FOCAL_LENGTH,
    XML_TOK_3DSCENESHAPE_SHADOW_SLANT,
    XML_TOK_3DSCENESHAPE_SHADE_MODE,
    XML_TOK_3DSCENESHAPE_AMBIENT_COLOR,
    XML_TOK_3DSCENESHAPE_LIGHTING_MODE
};

enum SdXML3DLightAttrTokenMap
{
    XML_TOK_3DLIGHT_DIFFUSE_COLOR,
    XML_TOK_3DLIGHT_DIRECTION,
    XML_TOK_3DLIGHT_ENABLED,
    XML_TOK_3DLIGHT_SPECULAR
};

//////////////////////////////////////////////////////////////////////////////
// dr3d:3dlight context

class SdXML3DLightContext: public SvXMLImportContext
{
    // local parameters which need to be read
    Color						maDiffuseColor;
    Vector3D					maDirection;
    BOOL						mbEnabled;
    BOOL						mbSpecular;

public:
    SdXML3DLightContext( 
        SvXMLImport& rImport, 
        sal_uInt16 nPrfx,
        const ::rtl::OUString& rLName, 
        const ::com::sun::star::uno::Reference< ::com::sun::star::xml::sax::XAttributeList >& xAttrList);
    virtual ~SdXML3DLightContext();

    const Color& GetDiffuseColor() { return maDiffuseColor; }
    const Vector3D& GetDirection() { return maDirection; }
    BOOL GetEnabled() { return mbEnabled; }
    BOOL GetSpecular() { return mbSpecular; }
};

//////////////////////////////////////////////////////////////////////////////

DECLARE_LIST(Imp3DLightList, SdXML3DLightContext*)//STRIP007 ;

class SdXML3DSceneAttributesHelper
{
protected:
    SvXMLImport& mrImport;

    // list for local light contexts
    Imp3DLightList				maList;

    // local parameters which need to be read
    ::com::sun::star::drawing::HomogenMatrix mxHomMat;
    BOOL						mbSetTransform;

    ::com::sun::star::drawing::ProjectionMode mxPrjMode;
    sal_Int32					mnDistance;
    sal_Int32					mnFocalLength;
    sal_Int32					mnShadowSlant;
    ::com::sun::star::drawing::ShadeMode mxShadeMode;
    Color						maAmbientColor;
    BOOL						mbLightingMode;

    Vector3D					maVRP;
    Vector3D					maVPN;
    Vector3D					maVUP;
    BOOL						mbVRPUsed;
    BOOL						mbVPNUsed;
    BOOL						mbVUPUsed;

public:
    SdXML3DSceneAttributesHelper( SvXMLImport& rImporter );
    ~SdXML3DSceneAttributesHelper();

    /** creates a 3d ligth context and adds it to the internal list for later processing */
    SvXMLImportContext * create3DLightContext( sal_uInt16 nPrfx, const ::rtl::OUString& rLName, const ::com::sun::star::uno::Reference< ::com::sun::star::xml::sax::XAttributeList >& xAttrList);

    /** this should be called for each scene attribute */
    void processSceneAttribute( sal_uInt16 nPrefix, const ::rtl::OUString& rLocalName, const ::rtl::OUString& rValue );

    /** this sets the scene attributes at this propertyset */
    void setSceneAttributes( const ::com::sun::star::uno::Reference< ::com::sun::star::beans::XPropertySet >& xPropSet );
};

//////////////////////////////////////////////////////////////////////////////

class ShapeSortContext;
struct XMLShapeImportHelperImpl;
struct XMLShapeImportPageContextImpl;

class XMLShapeImportHelper : public UniRefBase
{
    XMLShapeImportHelperImpl*	mpImpl;

    XMLShapeImportPageContextImpl*	mpPageContext;

    ::com::sun::star::uno::Reference< ::com::sun::star::frame::XModel > mxModel;

    // PropertySetMappers and factory
    XMLSdPropHdlFactory*		mpSdPropHdlFactory;
    SvXMLImportPropertyMapper*		mpPropertySetMapper;
    SvXMLImportPropertyMapper*		mpPresPagePropsMapper;

    // contexts for Style and AutoStyle import
    SvXMLStylesContext*			mpStylesContext;
    SvXMLStylesContext*			mpAutoStylesContext;

    // contexts for xShape contents TokenMaps
    SvXMLTokenMap*				mpGroupShapeElemTokenMap;
    SvXMLTokenMap*				mp3DSceneShapeElemTokenMap;
    SvXMLTokenMap*				mp3DObjectAttrTokenMap;
    SvXMLTokenMap*				mp3DPolygonBasedAttrTokenMap;
    SvXMLTokenMap*				mp3DCubeObjectAttrTokenMap;
    SvXMLTokenMap*				mp3DSphereObjectAttrTokenMap;
    SvXMLTokenMap*				mp3DSceneShapeAttrTokenMap;
    SvXMLTokenMap*				mp3DLightAttrTokenMap;
    SvXMLTokenMap*				mpPathShapeAttrTokenMap;
    SvXMLTokenMap*				mpPolygonShapeAttrTokenMap;

    const ::rtl::OUString		msStartShape;
    const ::rtl::OUString		msEndShape;
    const ::rtl::OUString		msStartGluePointIndex;
    const ::rtl::OUString		msEndGluePointIndex;

protected:
    SvXMLImport& mrImporter;

public:
    XMLShapeImportHelper( SvXMLImport& rImporter,
        const ::com::sun::star::uno::Reference< ::com::sun::star::frame::XModel>& rModel,
    SvXMLImportPropertyMapper *pExtMapper=0 );

    ~XMLShapeImportHelper();

    SvXMLImportContext* CreateGroupChildContext(
        SvXMLImport& rImport, sal_uInt16 nPrefix, const ::rtl::OUString& rLocalName,
        const ::com::sun::star::uno::Reference< ::com::sun::star::xml::sax::XAttributeList >& xAttrList,
        ::com::sun::star::uno::Reference< ::com::sun::star::drawing::XShapes >& rShapes);

    SvXMLImportContext* Create3DSceneChildContext(
        SvXMLImport& rImport, sal_uInt16 nPrefix, const ::rtl::OUString& rLocalName,
        const ::com::sun::star::uno::Reference< ::com::sun::star::xml::sax::XAttributeList >& xAttrList,
        ::com::sun::star::uno::Reference< ::com::sun::star::drawing::XShapes >& rShapes);

    const SvXMLTokenMap& GetGroupShapeElemTokenMap();
    const SvXMLTokenMap& Get3DSceneShapeElemTokenMap();
    const SvXMLTokenMap& Get3DObjectAttrTokenMap();
    const SvXMLTokenMap& Get3DPolygonBasedAttrTokenMap();
    const SvXMLTokenMap& Get3DCubeObjectAttrTokenMap();
    const SvXMLTokenMap& Get3DSphereObjectAttrTokenMap();
    const SvXMLTokenMap& Get3DSceneShapeAttrTokenMap();
    const SvXMLTokenMap& Get3DLightAttrTokenMap();
    const SvXMLTokenMap& GetPathShapeAttrTokenMap();
    const SvXMLTokenMap& GetPolygonShapeAttrTokenMap();

    // Styles and AutoStyles contexts
    SvXMLStylesContext* GetStylesContext() const { return mpStylesContext; }
    void SetStylesContext(SvXMLStylesContext* pNew);
    SvXMLStylesContext* GetAutoStylesContext() const { return mpAutoStylesContext; }
    void SetAutoStylesContext(SvXMLStylesContext* pNew);

    // get factories and mappers
    SvXMLImportPropertyMapper* GetPropertySetMapper() const { return mpPropertySetMapper; }
    SvXMLImportPropertyMapper* GetPresPagePropsMapper() const { return mpPresPagePropsMapper; }

    // this function is called whenever the implementation classes like to add this new
    // shape to the given XShapes.
    virtual void addShape(
        ::com::sun::star::uno::Reference< ::com::sun::star::drawing::XShape >& rShape,
        const ::com::sun::star::uno::Reference< ::com::sun::star::xml::sax::XAttributeList >& xAttrList,
        ::com::sun::star::uno::Reference< ::com::sun::star::drawing::XShapes >& rShapes);

    // this function is called whenever the implementation classes have finished importing
    // a shape to the given XShapes. The shape is already inserted into its XShapes and
    // all properties and styles are set.
    virtual void finishShape(
        ::com::sun::star::uno::Reference< ::com::sun::star::drawing::XShape >& rShape,
        const ::com::sun::star::uno::Reference< ::com::sun::star::xml::sax::XAttributeList >& xAttrList,
        ::com::sun::star::uno::Reference< ::com::sun::star::drawing::XShapes >& rShapes);

    // helper functions for z-order sorting
    void pushGroupForSorting( ::com::sun::star::uno::Reference< ::com::sun::star::drawing::XShapes >& rShapes );
    void popGroupAndSort();

    void shapeWithZIndexAdded( ::com::sun::star::uno::Reference< ::com::sun::star::drawing::XShape >& rShape,
                               sal_Int32 nZIndex );

    void addShapeConnection( ::com::sun::star::uno::Reference< ::com::sun::star::drawing::XShape >& rConnectorShape,
                             sal_Bool bStart,
                             sal_Int32 nDestShapeId,
                             sal_Int32 nDestGlueId );

    /** adds a mapping for a glue point identifier from an xml file to the identifier created after inserting
        the new glue point into the core. The saved mappings can be retrieved by getGluePointId() */
    void addGluePointMapping( ::com::sun::star::uno::Reference< ::com::sun::star::drawing::XShape >& xShape,
                              sal_Int32 nSourceId, sal_Int32 nDestinnationId );

    /** retrieves a mapping for a glue point identifier from the current xml file to the identifier created after
        inserting the new glue point into the core. The mapping must be initialized first with addGluePointMapping() */
    sal_Int32 getGluePointId( ::com::sun::star::uno::Reference< ::com::sun::star::drawing::XShape >& xShape, sal_Int32 nSourceId );

    void createShapeId( ::com::sun::star::uno::Reference< ::com::sun::star::drawing::XShape >& xShape, sal_Int32 nId );

    ::com::sun::star::uno::Reference< ::com::sun::star::drawing::XShape > getShapeFromId( sal_Int32 nId );

    /** this method must be calling before the first shape is imported for the given page.
        Calls to this method can be nested */
    void startPage( ::com::sun::star::uno::Reference< ::com::sun::star::drawing::XShapes >& rShapes );

    /** this method must be calling after the last shape is imported for the given page
        Calls to this method can be nested */
    void endPage( ::com::sun::star::uno::Reference< ::com::sun::star::drawing::XShapes >& rShapes );

    void restoreConnections();

    /** creates a property mapper for external chaining */
    static SvXMLImportPropertyMapper* CreateShapePropMapper(
        const ::com::sun::star::uno::Reference< ::com::sun::star::frame::XModel>& rModel, SvXMLImport& rImport );

    /** creates a shape property set mapper that can be used for non shape elements */
    static SvXMLImportPropertyMapper* CreateExternalShapePropMapper(
        const ::com::sun::star::uno::Reference< ::com::sun::star::frame::XModel>& rModel, SvXMLImport& rImport );

    // #88546#
    /** defines if the import should increment the progress bar or not */
    void enableHandleProgressBar( sal_Bool bEnable = sal_True );
    sal_Bool IsHandleProgressBarEnabled() const;

    /** queries the capability of the current model to create presentation shapes */
    sal_Bool IsPresentationShapesSupported();
};

}//end of namespace binfilter
#endif // _XMLOFF_SHAPEIMPORT_HXX_
