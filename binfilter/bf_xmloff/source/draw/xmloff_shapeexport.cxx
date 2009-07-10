/*************************************************************************
 *
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER.
 * 
 * Copyright 2008 by Sun Microsystems, Inc.
 *
 * OpenOffice.org - a multi-platform office productivity suite
 *
 * $RCSfile: xmloff_shapeexport.cxx,v $
 * $Revision: 1.5 $
 *
 * This file is part of OpenOffice.org.
 *
 * OpenOffice.org is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License version 3
 * only, as published by the Free Software Foundation.
 *
 * OpenOffice.org is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License version 3 for more details
 * (a copy is included in the LICENSE file that accompanied this code).
 *
 * You should have received a copy of the GNU Lesser General Public License
 * version 3 along with OpenOffice.org.  If not, see
 * <http://www.openoffice.org/license.html>
 * for a copy of the LGPLv3 License.
 *
 ************************************************************************/

#ifndef _COM_SUN_STAR_LANG_SERVICENOTREGISTEREDEXCEPTION_HPP_ 
#include <com/sun/star/lang/ServiceNotRegisteredException.hpp>
#endif

#ifndef _COM_SUN_STAR_CONTAINER_XCHILD_HPP_
#include <com/sun/star/container/XChild.hpp>
#endif

#ifndef _COM_SUN_STAR_TEXT_XTEXT_HPP_
#include <com/sun/star/text/XText.hpp>
#endif


#ifndef _COM_SUN_STAR_DRAWING_XCONTROLSHAPE_HPP_
#include <com/sun/star/drawing/XControlShape.hpp>
#endif

#ifndef _COM_SUN_STAR_STYLE_XSTYLE_HPP_
#include <com/sun/star/style/XStyle.hpp>
#endif

#ifndef _COM_SUN_STAR_DRAWING_XGLUEPOINTSSUPPLIER_HPP_
#include <com/sun/star/drawing/XGluePointsSupplier.hpp>
#endif
#ifndef _COM_SUN_STAR_CONTAINER_XIDENTIFIERACCESS_HPP_
#include <com/sun/star/container/XIdentifierAccess.hpp>
#endif

#ifndef _COM_SUN_STAR_DRAWING_GLUEPOINT2_HPP_
#include <com/sun/star/drawing/GluePoint2.hpp>
#endif
#ifndef _XMLOFF_XMLUCONV_HXX
#include "xmluconv.hxx"
#endif



#ifndef _SDPROPLS_HXX
#include "sdpropls.hxx"
#endif

#ifndef _SDXMLEXP_IMPL_HXX
#include "sdxmlexp_impl.hxx"
#endif


#ifndef _TOOLS_DEBUG_HXX
#include <tools/debug.hxx>
#endif

#ifndef _XMLOFF_CONTEXTID_HXX_
#include "contextid.hxx"
#endif



#ifndef _SOT_CLSIDS_HXX
#include <sot/clsids.hxx>
#endif

#ifndef _GLOBNAME_HXX
#include <tools/globname.hxx>
#endif

#ifndef _COM_SUN_STAR_BEANS_XPROPERTYSTATE_HPP_
#include <com/sun/star/beans/XPropertyState.hpp>
#endif

#include "xmlnmspe.hxx"
namespace binfilter {

using namespace ::rtl;
using namespace ::com::sun::star;
using namespace ::binfilter::xmloff::token;

//////////////////////////////////////////////////////////////////////////////

XMLShapeExport::XMLShapeExport(SvXMLExport& rExp,
                                SvXMLExportPropertyMapper *pExtMapper )
:	rExport( rExp ),
    // #88546# init to FALSE
    mbHandleProgressBar( sal_False ),
    mnNextUniqueShapeId(1),
    mbExportLayer( sal_False ),
    msZIndex( RTL_CONSTASCII_USTRINGPARAM("ZOrder") ),
    msEmptyPres( RTL_CONSTASCII_USTRINGPARAM("IsEmptyPresentationObject") ),
    msModel( RTL_CONSTASCII_USTRINGPARAM("Model") ),
    msStartShape( RTL_CONSTASCII_USTRINGPARAM("StartShape") ),
    msEndShape( RTL_CONSTASCII_USTRINGPARAM("EndShape") ),
    msOnClick( RTL_CONSTASCII_USTRINGPARAM("OnClick") ),
    msEventType( RTL_CONSTASCII_USTRINGPARAM("EventType") ),
    msPresentation( RTL_CONSTASCII_USTRINGPARAM("Presentation") ),
    msMacroName( RTL_CONSTASCII_USTRINGPARAM("MacroName") ),
    msLibrary( RTL_CONSTASCII_USTRINGPARAM("Library") ),
    msClickAction( RTL_CONSTASCII_USTRINGPARAM("ClickAction") ),
    msBookmark( RTL_CONSTASCII_USTRINGPARAM("Bookmark") ),
    msEffect( RTL_CONSTASCII_USTRINGPARAM("Effect") ),
    msPlayFull( RTL_CONSTASCII_USTRINGPARAM("PlayFull") ),
    msVerb( RTL_CONSTASCII_USTRINGPARAM("Verb") ),
    msSoundURL( RTL_CONSTASCII_USTRINGPARAM("SoundURL") ),
    msSpeed( RTL_CONSTASCII_USTRINGPARAM("Speed") ),
    msStarBasic( RTL_CONSTASCII_USTRINGPARAM("StarBasic") )
{
    // construct PropertyHandlerFactory
    xSdPropHdlFactory = new XMLSdPropHdlFactory( rExport.GetModel() );

    // construct PropertySetMapper
    xPropertySetMapper = CreateShapePropMapper( rExport );
    if( pExtMapper )
    {
        UniReference < SvXMLExportPropertyMapper > xExtMapper( pExtMapper );
        xPropertySetMapper->ChainExportMapper( xExtMapper );
    }

/*
    // chain text attributes
    xPropertySetMapper->ChainExportMapper(XMLTextParagraphExport::CreateParaExtPropMapper(rExp));
*/

    rExport.GetAutoStylePool()->AddFamily(
        XML_STYLE_FAMILY_SD_GRAPHICS_ID,
        OUString(RTL_CONSTASCII_USTRINGPARAM(XML_STYLE_FAMILY_SD_GRAPHICS_NAME)),
        GetPropertySetMapper(),
        OUString(RTL_CONSTASCII_USTRINGPARAM(XML_STYLE_FAMILY_SD_GRAPHICS_PREFIX)));
    rExport.GetAutoStylePool()->AddFamily(
        XML_STYLE_FAMILY_SD_PRESENTATION_ID,
        OUString(RTL_CONSTASCII_USTRINGPARAM(XML_STYLE_FAMILY_SD_PRESENTATION_NAME)),
        GetPropertySetMapper(),
        OUString(RTL_CONSTASCII_USTRINGPARAM(XML_STYLE_FAMILY_SD_PRESENTATION_PREFIX)));

    maCurrentInfo = maShapeInfos.end();
}

///////////////////////////////////////////////////////////////////////

XMLShapeExport::~XMLShapeExport()
{
}

///////////////////////////////////////////////////////////////////////

// This method collects all automatic styles for the given XShape
void XMLShapeExport::collectShapeAutoStyles(const uno::Reference< drawing::XShape >& xShape)
{
    if( maCurrentShapesIter == maShapesInfos.end() )
    {
        DBG_ERROR( "XMLShapeExport::collectShapeAutoStyles(): no call to seekShapes()!" );
        return;
    }

    sal_Int32 nZIndex = 0;
    uno::Reference< beans::XPropertySet > xSet( xShape, uno::UNO_QUERY );
    if( xSet.is() )
        xSet->getPropertyValue(msZIndex) >>= nZIndex;

    ImplXMLShapeExportInfoVector& aShapeInfoVector = (*maCurrentShapesIter).second;

    if( aShapeInfoVector.size() <= nZIndex )
    {
        DBG_ERROR( "XMLShapeExport::collectShapeAutoStyles(): no shape info allocated for a given shape" );
        return;
    }

    ImplXMLShapeExportInfo& aShapeInfo = aShapeInfoVector[nZIndex];

    // -----------------------------
    // first compute the shapes type
    // -----------------------------
    ImpCalcShapeType(xShape, aShapeInfo.meShapeType);

    const bool bObjSupportsText =
//		aShapeInfo.meShapeType != XmlShapeTypeDrawControlShape &&
        aShapeInfo.meShapeType != XmlShapeTypeDrawChartShape &&
        aShapeInfo.meShapeType != XmlShapeTypePresChartShape &&
        aShapeInfo.meShapeType != XmlShapeTypeDrawOLE2Shape &&
        aShapeInfo.meShapeType != XmlShapeTypePresOLE2Shape &&
        aShapeInfo.meShapeType != XmlShapeTypeDraw3DSceneObject &&
        aShapeInfo.meShapeType != XmlShapeTypeDraw3DCubeObject &&
        aShapeInfo.meShapeType != XmlShapeTypeDraw3DSphereObject &&
        aShapeInfo.meShapeType != XmlShapeTypeDraw3DLatheObject &&
        aShapeInfo.meShapeType != XmlShapeTypeDraw3DExtrudeObject &&
        aShapeInfo.meShapeType != XmlShapeTypeDrawPageShape &&
        aShapeInfo.meShapeType != XmlShapeTypePresPageShape &&
        aShapeInfo.meShapeType != XmlShapeTypeDrawGroupShape;

    const bool bObjSupportsStyle = 
        aShapeInfo.meShapeType != XmlShapeTypeDrawGroupShape;

    sal_Bool bIsEmptyPresObj = sal_False;

    uno::Reference< beans::XPropertySet > xPropSet(xShape, uno::UNO_QUERY);

    // ----------------
    // prep text styles
    // ----------------
    if( xPropSet.is() && bObjSupportsText )
    {
        uno::Reference< text::XText > xText(xShape, uno::UNO_QUERY);
        if(xText.is() && xText->getString().getLength())
        {
            uno::Reference< beans::XPropertySetInfo > xPropSetInfo( xPropSet->getPropertySetInfo() );

            if( xPropSetInfo.is() && xPropSetInfo->hasPropertyByName(msEmptyPres) )
            {
                uno::Any aAny = xPropSet->getPropertyValue(msEmptyPres);
                aAny >>= bIsEmptyPresObj;
            }

            if(!bIsEmptyPresObj)
            {
                GetExport().GetTextParagraphExport()->collectTextAutoStyles( xText );
            }
        }
    }

    // ------------------------------
    // compute the shape parent style
    // ------------------------------
    if( xPropSet.is() )
    {
        uno::Reference< beans::XPropertySetInfo > xPropSetInfo( xPropSet->getPropertySetInfo() );

        OUString aParentName;
        uno::Reference< style::XStyle > xStyle;

        if( bObjSupportsStyle )
        {
            if( xPropSetInfo.is() && xPropSetInfo->hasPropertyByName( OUString(RTL_CONSTASCII_USTRINGPARAM("Style"))) )
                xPropSet->getPropertyValue(OUString(RTL_CONSTASCII_USTRINGPARAM("Style"))) >>= xStyle;

            if(xStyle.is())
            {
                // get family ID
                uno::Reference< beans::XPropertySet > xStylePropSet(xStyle, uno::UNO_QUERY);
                DBG_ASSERT( xStylePropSet.is(), "style without a XPropertySet?" );
                if(xStylePropSet.is())
                {
                    OUString aFamilyName;
                    xStylePropSet->getPropertyValue(OUString(RTL_CONSTASCII_USTRINGPARAM("Family"))) >>= aFamilyName;
                    if(aFamilyName.getLength() && aFamilyName.equals(OUString(RTL_CONSTASCII_USTRINGPARAM("presentation"))))
                        aShapeInfo.mnFamily = XML_STYLE_FAMILY_SD_PRESENTATION_ID;
                }

                // get parent-style name
                if(XML_STYLE_FAMILY_SD_PRESENTATION_ID == aShapeInfo.mnFamily)
                {
                    aParentName = msPresentationStylePrefix;
                }

                aParentName += xStyle->getName();
            }
        }

        // filter propset
        std::vector< XMLPropertyState > xPropStates;

        sal_Int32 nCount = 0;
        if( (!bIsEmptyPresObj || (aShapeInfo.meShapeType != XmlShapeTypePresPageShape)) )
        {
            xPropStates = GetPropertySetMapper()->Filter( xPropSet );

            if (XmlShapeTypeDrawControlShape == aShapeInfo.meShapeType)
            {
                // for control shapes, we additionally need the number format style (if any)
                uno::Reference< drawing::XControlShape > xControl(xShape, uno::UNO_QUERY);
                DBG_ASSERT(xControl.is(), "XMLShapeExport::collectShapeAutoStyles: ShapeType control, but no XControlShape!");
                if (xControl.is())
                {
                    uno::Reference< beans::XPropertySet > xControlModel(xControl->getControl(), uno::UNO_QUERY);
                    DBG_ASSERT(xControlModel.is(), "XMLShapeExport::collectShapeAutoStyles: no control model on the control shape!");

                    ::rtl::OUString sNumberStyle = rExport.GetFormExport()->getControlNumberStyle(xControlModel);
                    if (0 != sNumberStyle.getLength())
                    {
                        sal_Int32 nIndex = GetPropertySetMapper()->getPropertySetMapper()->FindEntryIndex(CTF_SD_CONTROL_SHAPE_DATA_STYLE);
                            // TODO : this retrieval of the index should be moved into the ctor, holding the index
                            //			as member, thus saving time.
                        DBG_ASSERT(-1 != nIndex, "XMLShapeExport::collectShapeAutoStyles: could not obtain the index for our context id!");

                        XMLPropertyState aNewState(nIndex, uno::makeAny(sNumberStyle));
                        xPropStates.push_back(aNewState);
                    }
                }
            }

            std::vector< XMLPropertyState >::iterator aIter = xPropStates.begin();
            std::vector< XMLPropertyState >::iterator aEnd = xPropStates.end();
            while( aIter != aEnd )
            {
                if( aIter->mnIndex != -1 )
                    nCount++;
                aIter++;
            }
        }

        if(nCount == 0)
        {
            // no hard attributes, use parent style name for export
            aShapeInfo.msStyleName = aParentName;
        }
        else
        {
            // there are filtered properties -> hard attributes
            // try to find this style in AutoStylePool
            aShapeInfo.msStyleName = rExport.GetAutoStylePool()->Find(aShapeInfo.mnFamily, aParentName, xPropStates);

            if(!aShapeInfo.msStyleName.getLength())
            {
                // Style did not exist, add it to AutoStalePool
                aShapeInfo.msStyleName = rExport.GetAutoStylePool()->Add(aShapeInfo.mnFamily, aParentName, xPropStates);
            }
        }

        // optionaly generate auto style for text attributes
        if( (!bIsEmptyPresObj || (aShapeInfo.meShapeType != XmlShapeTypePresPageShape)) && bObjSupportsText )
        {
            xPropStates = GetExport().GetTextParagraphExport()->GetParagraphPropertyMapper()->Filter( xPropSet );

            // ----------------------------------------------------------------------
            // yet more additionally, we need to care for the ParaAdjust property
            if ( XmlShapeTypeDrawControlShape == aShapeInfo.meShapeType )
            {
                // this is because:
                // * if controls shapes have a ParaAdjust property, then this is the Align property of the control model
                // * control models are allowed to have an Align of "void"
                // * the Default for control model's Align is TextAlign_LEFT
                // * defaults for style properties are not written, but we need to write the "left",
                //   because we need to distiguish this "left" from the case where not align attribute
                //   is present which means "void"
                // 102407 - 2002-11-01 - fs@openoffice.org
                static const ::rtl::OUString s_sParaAdjustPropertyName( RTL_CONSTASCII_USTRINGPARAM( "ParaAdjust" ) );
                uno::Reference< beans::XPropertySetInfo > xPropSetInfo( xPropSet->getPropertySetInfo() );
                if ( xPropSetInfo.is() && xPropSetInfo->hasPropertyByName( s_sParaAdjustPropertyName ) )
                {
                    uno::Reference< beans::XPropertyState > xPropState( xPropSet, uno::UNO_QUERY );
                    if ( xPropState.is() && beans::PropertyState_DEFAULT_VALUE == xPropState->getPropertyState( s_sParaAdjustPropertyName ) )
                    {
                        sal_Int32 nIndex = GetExport().GetTextParagraphExport()->GetParagraphPropertyMapper()->getPropertySetMapper()->FindEntryIndex( CTF_SD_SHAPE_PARA_ADJUST );
                            // TODO : this retrieval of the index should be moved into the ctor, holding the index
                            //			as member, thus saving time.
                        DBG_ASSERT(-1 != nIndex, "XMLShapeExport::collectShapeAutoStyles: could not obtain the index for the ParaAdjust context id!");

                        uno::Any aParaAdjustValue = xPropSet->getPropertyValue( s_sParaAdjustPropertyName );
                        XMLPropertyState aAlignDefaultState( nIndex, aParaAdjustValue );

                        xPropStates.push_back( aAlignDefaultState );
                    }
                }
            }
            // ----------------------------------------------------------------------

            nCount = 0;
            std::vector< XMLPropertyState >::iterator aIter = xPropStates.begin();
            std::vector< XMLPropertyState >::iterator aEnd = xPropStates.end();
            while( aIter != aEnd )
            {
                if( aIter->mnIndex != -1 )
                    nCount++;
                aIter++;
            }

            if( nCount )
            {
                const OUString aEmpty;
                aShapeInfo.msTextStyleName = rExport.GetAutoStylePool()->Find( XML_STYLE_FAMILY_TEXT_PARAGRAPH, aEmpty, xPropStates );
                if(!aShapeInfo.msTextStyleName.getLength())
                {
                    // Style did not exist, add it to AutoStalePool
                    aShapeInfo.msTextStyleName = rExport.GetAutoStylePool()->Add(XML_STYLE_FAMILY_TEXT_PARAGRAPH, aEmpty, xPropStates);
                }
            }
        }
    }

    // ----------------------------------------
    // prepare animation informations if needed
    // ----------------------------------------
    if( mxAnimationsExporter.is() )
        mxAnimationsExporter->prepare( xShape );

    // -------------------
    // check for connector
    // -------------------
    if( aShapeInfo.meShapeType == XmlShapeTypeDrawConnectorShape )
    {
        uno::Reference< drawing::XShape > xConnection;

        // create shape ids for export later
        if( xPropSet->getPropertyValue( msStartShape ) >>= xConnection )
        {
            createShapeId( xConnection );
        }
        if( xPropSet->getPropertyValue( msEndShape ) >>= xConnection )
        {
            createShapeId( xConnection );
        }
    }

    maShapeInfos.push_back( aShapeInfo );
    maCurrentInfo = maShapeInfos.begin();

    // -----------------------------------------------------
    // check for shape collections (group shape or 3d scene)
    // and collect contained shapes style infos
    // -----------------------------------------------------
    {
        uno::Reference< drawing::XShapes > xShapes( xShape, uno::UNO_QUERY );
        if( xShapes.is() )
        {
            collectShapesAutoStyles( xShapes );
        }
    }
}

///////////////////////////////////////////////////////////////////////

// This method exports the given XShape
void XMLShapeExport::exportShape(const uno::Reference< drawing::XShape >& xShape,
                                 sal_Int32 nFeatures /* = SEF_DEFAULT */,
                                 ::com::sun::star::awt::Point* pRefPoint /* = NULL */ )
{
    if( maCurrentShapesIter == maShapesInfos.end() )
    {
        DBG_ERROR( "XMLShapeExport::exportShape(): no auto styles where collected before export" );
        return;
    }

    sal_Int32 nZIndex = 0;
    uno::Reference< beans::XPropertySet > xSet( xShape, uno::UNO_QUERY );
    if( xSet.is() )
        xSet->getPropertyValue(msZIndex) >>= nZIndex;

    ImplXMLShapeExportInfoVector& aShapeInfoVector = (*maCurrentShapesIter).second;

    if( aShapeInfoVector.size() <= nZIndex )
    {
        DBG_ERROR( "XMLShapeExport::exportShape(): no shape info collected for a given shape" );
        return;
    }

    const ImplXMLShapeExportInfo& aShapeInfo = aShapeInfoVector[nZIndex];

#ifdef DBG_UTIL
    // ---------------------------------------
    // check if this is the correct ShapesInfo
    // ---------------------------------------
    uno::Reference< container::XChild > xChild( xShape, uno::UNO_QUERY );
    if( xChild.is() )
    {
        uno::Reference< drawing::XShapes > xParent( xChild->getParent(), uno::UNO_QUERY );
        DBG_ASSERT( xParent.is() && xParent.get() == (*maCurrentShapesIter).first.get(), "XMLShapeExport::exportShape(): Wrong call to XMLShapeExport::seekShapes()" );
    }

    // -----------------------------
    // first compute the shapes type
    // -----------------------------
    {
        XmlShapeType eShapeType(XmlShapeTypeNotYetSet);
        ImpCalcShapeType(xShape, eShapeType);

        DBG_ASSERT( eShapeType == aShapeInfo.meShapeType, "exportShape callings do not correspond to collectShapeAutoStyles calls!" );
    }
#endif

    // ----------------------------------------
    // collect animation informations if needed
    // ----------------------------------------
    if( mxAnimationsExporter.is() )
        mxAnimationsExporter->collect( xShape );

    // -------------------------------
    // export shapes name if he has one
    // -------------------------------
    {
        uno::Reference< container::XNamed > xNamed( xShape, uno::UNO_QUERY );
        if( xNamed.is() )
        {
            const OUString aName( xNamed->getName() );
            if( aName.getLength() )
                rExport.AddAttribute(XML_NAMESPACE_DRAW, XML_NAME, aName );
        }
    }

    // ------------------
    // export style name
    // ------------------
    if( aShapeInfo.msStyleName.getLength() != 0 )
    {
        if(XML_STYLE_FAMILY_SD_GRAPHICS_ID == aShapeInfo.mnFamily)
            rExport.AddAttribute(XML_NAMESPACE_DRAW, XML_STYLE_NAME, aShapeInfo.msStyleName);
        else
            rExport.AddAttribute(XML_NAMESPACE_PRESENTATION, XML_STYLE_NAME, aShapeInfo.msStyleName);
    }

    // ------------------
    // export text style name
    // ------------------
    if( aShapeInfo.msTextStyleName.getLength() != 0 )
    {
        rExport.AddAttribute(XML_NAMESPACE_DRAW, XML_TEXT_STYLE_NAME, aShapeInfo.msTextStyleName);
    }

    // --------------------------
    // export shapes id if needed
    // --------------------------
    {
        const sal_Int32 nShapeId = getShapeId( xShape );
        if( nShapeId != -1 )
        {
            const OUString sId( OUString::valueOf( nShapeId ) );
            rExport.AddAttribute(XML_NAMESPACE_DRAW, XML_ID, sId );
        }
    }

    // --------------------------
    // export layer information
    // --------------------------
    if( IsLayerExportEnabled() )
    {
        // check for group or scene shape and not export layer if this is one
        uno::Reference< drawing::XShapes > xShapes( xShape, uno::UNO_QUERY );
        if( !xShapes.is() )
        {
            try
            {
                uno::Reference< beans::XPropertySet > xProps( xShape, uno::UNO_QUERY );
                OUString aLayerName;
                xProps->getPropertyValue( OUString::createFromAscii( "LayerName" ) ) >>= aLayerName;
                rExport.AddAttribute(XML_NAMESPACE_DRAW, XML_LAYER, aLayerName );

            }
            catch( uno::Exception e )
            {
                DBG_ERROR( "could not export layer name for shape!" );
            }
        }
    }

    // #82003# test export count
    // #91587# ALWAYS increment since now ALL to be exported shapes are counted.
    if(rExport.GetShapeExport()->IsHandleProgressBarEnabled())
    {
        rExport.GetProgressBarHelper()->Increment();
    }

    onExport( xShape );

    // --------------------
    // export shape element
    // --------------------
    switch(aShapeInfo.meShapeType)
    {
        case XmlShapeTypeDrawRectangleShape:
        {
            ImpExportRectangleShape(xShape, aShapeInfo.meShapeType, nFeatures, pRefPoint );
            break;
        }
        case XmlShapeTypeDrawEllipseShape:
        {
            ImpExportEllipseShape(xShape, aShapeInfo.meShapeType, nFeatures, pRefPoint );
            break;
        }
        case XmlShapeTypeDrawLineShape:
        {
            ImpExportLineShape(xShape, aShapeInfo.meShapeType, nFeatures, pRefPoint );
            break;
        }
        case XmlShapeTypeDrawPolyPolygonShape:	// closed PolyPolygon
        case XmlShapeTypeDrawPolyLineShape:		// open PolyPolygon
        case XmlShapeTypeDrawClosedBezierShape:	// closed PolyPolygon containing curves
        case XmlShapeTypeDrawOpenBezierShape:	// open PolyPolygon containing curves
        {
            ImpExportPolygonShape(xShape, aShapeInfo.meShapeType, nFeatures, pRefPoint );
            break;
        }

        case XmlShapeTypeDrawTextShape:
        case XmlShapeTypePresTitleTextShape:
        case XmlShapeTypePresOutlinerShape:
        case XmlShapeTypePresSubtitleShape:
        case XmlShapeTypePresNotesShape:
        {
            ImpExportTextBoxShape(xShape, aShapeInfo.meShapeType, nFeatures, pRefPoint );
            break;
        }

        case XmlShapeTypeDrawGraphicObjectShape:
        case XmlShapeTypePresGraphicObjectShape:
        {
            ImpExportGraphicObjectShape(xShape, aShapeInfo.meShapeType, nFeatures, pRefPoint );
            break;
        }

        case XmlShapeTypeDrawChartShape:
        case XmlShapeTypePresChartShape:
        {
            ImpExportChartShape(xShape, aShapeInfo.meShapeType, nFeatures, pRefPoint );
            break;
        }

        case XmlShapeTypeDrawTableShape:
        case XmlShapeTypePresTableShape:
        {
            ImpExportSpreadsheetShape(xShape, aShapeInfo.meShapeType, nFeatures, pRefPoint );
            break;
        }

        case XmlShapeTypeDrawControlShape:
        {
            ImpExportControlShape(xShape, aShapeInfo.meShapeType, nFeatures, pRefPoint );
            break;
        }

        case XmlShapeTypeDrawConnectorShape:
        {
            ImpExportConnectorShape(xShape, aShapeInfo.meShapeType, nFeatures, pRefPoint );
            break;
        }

        case XmlShapeTypeDrawMeasureShape:
        {
            ImpExportMeasureShape(xShape, aShapeInfo.meShapeType, nFeatures, pRefPoint );
            break;
        }

        case XmlShapeTypeDrawOLE2Shape:
        case XmlShapeTypePresOLE2Shape:
        {
            ImpExportOLE2Shape(xShape, aShapeInfo.meShapeType, nFeatures, pRefPoint );
            break;
        }

        case XmlShapeTypeDrawPageShape:
        case XmlShapeTypePresPageShape:
        case XmlShapeTypeHandoutShape:
        {
            ImpExportPageShape(xShape, aShapeInfo.meShapeType, nFeatures, pRefPoint );
            break;
        }

        case XmlShapeTypeDrawCaptionShape:
        {
            ImpExportCaptionShape(xShape, aShapeInfo.meShapeType, nFeatures, pRefPoint );
            break;
        }

        case XmlShapeTypeDraw3DCubeObject:
        case XmlShapeTypeDraw3DSphereObject:
        case XmlShapeTypeDraw3DLatheObject:
        case XmlShapeTypeDraw3DExtrudeObject:
        {
            ImpExport3DShape(xShape, aShapeInfo.meShapeType);
            break;
        }

        case XmlShapeTypeDraw3DSceneObject:
        {
            ImpExport3DSceneShape( xShape, aShapeInfo.meShapeType, nFeatures, pRefPoint );
            break;
        }

        case XmlShapeTypeDrawGroupShape:
        {
            // empty group
            ImpExportGroupShape( xShape, aShapeInfo.meShapeType, nFeatures, pRefPoint );
            break;
        }

        case XmlShapeTypeDrawFrameShape:
        {
            ImpExportFrameShape(xShape, aShapeInfo.meShapeType, nFeatures, pRefPoint );
            break;
        }

        case XmlShapeTypeDrawAppletShape:
        {
            ImpExportAppletShape(xShape, aShapeInfo.meShapeType, nFeatures, pRefPoint );
            break;
        }

        case XmlShapeTypeDrawPluginShape:
        {
            ImpExportPluginShape(xShape, aShapeInfo.meShapeType, nFeatures, pRefPoint );
            break;
        }

        case XmlShapeTypePresOrgChartShape:
        case XmlShapeTypeUnknown:
        case XmlShapeTypeNotYetSet:
        default:
        {
            // this should never happen and is an error
            DBG_ERROR("XMLEXP: WriteShape: unknown or unexpected type of shape in export!");
            break;
        }
    }

    // #97489# #97111#
    // if there was an error and no element for the shape was exported
    // we need to clear the attribute list or the attributes will be
    // set on the next exported element, which can result in corrupt
    // xml files due to duplicate attributes

    rExport.CheckAttrList();	// asserts in non pro if we have attributes left
    rExport.ClearAttrList();	// clears the attributes
}

///////////////////////////////////////////////////////////////////////

// This method collects all automatic styles for the shapes inside the given XShapes collection
void XMLShapeExport::collectShapesAutoStyles( const uno::Reference < drawing::XShapes >& xShapes )
{
    ShapesInfos::iterator aOldCurrentShapesIter = maCurrentShapesIter;
    seekShapes( xShapes );

    uno::Reference< drawing::XShape > xShape;
    const sal_Int32 nShapeCount(xShapes->getCount());
    for(sal_Int32 nShapeId = 0; nShapeId < nShapeCount; nShapeId++)
    {
        xShapes->getByIndex(nShapeId) >>= xShape;
        DBG_ASSERT( xShape.is(), "Shape without a XShape?" );
        if(!xShape.is())
            continue;

        collectShapeAutoStyles( xShape );
    }

    maCurrentShapesIter = aOldCurrentShapesIter;
}

///////////////////////////////////////////////////////////////////////

// This method exports all XShape inside the given XShapes collection
void XMLShapeExport::exportShapes( const uno::Reference < drawing::XShapes >& xShapes, sal_Int32 nFeatures /* = SEF_DEFAULT */, awt::Point* pRefPoint /* = NULL */ )
{
    ShapesInfos::iterator aOldCurrentShapesIter = maCurrentShapesIter;
    seekShapes( xShapes );

    uno::Reference< drawing::XShape > xShape;
    const sal_Int32 nShapeCount(xShapes->getCount());
    for(sal_Int32 nShapeId = 0; nShapeId < nShapeCount; nShapeId++)
    {
        xShapes->getByIndex(nShapeId) >>= xShape;
        DBG_ASSERT( xShape.is(), "Shape without a XShape?" );
        if(!xShape.is())
            continue;

        exportShape( xShape, nFeatures, pRefPoint );
    }

    maCurrentShapesIter = aOldCurrentShapesIter;
}

///////////////////////////////////////////////////////////////////////

void XMLShapeExport::seekShapes( const uno::Reference< drawing::XShapes >& xShapes ) throw()
{
    if( xShapes.is() )
    {
        maCurrentShapesIter = maShapesInfos.find( xShapes );
        if( maCurrentShapesIter == maShapesInfos.end() )
        {
            ImplXMLShapeExportInfoVector aNewInfoVector;
            aNewInfoVector.resize( (ShapesInfos::size_type) xShapes->getCount() );
            maShapesInfos[ xShapes ] = aNewInfoVector;

            maCurrentShapesIter = maShapesInfos.find( xShapes );

            DBG_ASSERT( maCurrentShapesIter != maShapesInfos.end(), "XMLShapeExport::seekShapes(): insert into stl::map failed" );
        }

        DBG_ASSERT( (*maCurrentShapesIter).second.size() == (ShapesInfos::size_type)xShapes->getCount(), "XMLShapeExport::seekShapes(): XShapes size varied between calls" );

    }
    else
    {
        maCurrentShapesIter = maShapesInfos.end();
    }
}

///////////////////////////////////////////////////////////////////////

void XMLShapeExport::exportAutoStyles()
{
    // export all autostyle infos

    // ...for graphic
//	if(IsFamilyGraphicUsed())
    {
        GetExport().GetAutoStylePool()->exportXML(
            XML_STYLE_FAMILY_SD_GRAPHICS_ID
            , GetExport().GetDocHandler(),
            GetExport().GetMM100UnitConverter(),
            GetExport().GetNamespaceMap()
            );
    }

    // ...for presentation
//	if(IsFamilyPresentationUsed())
    {
        GetExport().GetAutoStylePool()->exportXML(
            XML_STYLE_FAMILY_SD_PRESENTATION_ID
            , GetExport().GetDocHandler(),
            GetExport().GetMM100UnitConverter(),
            GetExport().GetNamespaceMap()
            );
    }
}

///////////////////////////////////////////////////////////////////////

/** creates a unique id for this shape, this id is saved and exported with this shape later
    with the exportShape method. Its ok to call this twice with the same shape */
void XMLShapeExport::createShapeId( const uno::Reference < drawing::XShape >& xShape )
{
    ShapeIdsMap::iterator aId( maShapeIds.find( xShape ) );

    if( aId == maShapeIds.end() )
        maShapeIds[xShape] = mnNextUniqueShapeId++;
}

///////////////////////////////////////////////////////////////////////

/** returns the unique id for this shape. It returns -1 if the was no createShapeId call
    for this shape yet. */
sal_Int32 XMLShapeExport::getShapeId( const uno::Reference < drawing::XShape >& xShape )
{
    ShapeIdsMap::iterator aId( maShapeIds.find( xShape ) );

    if( aId != maShapeIds.end() )
        return (*aId).second;

    return -1;
}

///////////////////////////////////////////////////////////////////////

/// returns the export property mapper for external chaining
SvXMLExportPropertyMapper* XMLShapeExport::CreateShapePropMapper(
    SvXMLExport& rExport )
{
    UniReference< XMLPropertyHandlerFactory > xFactory = new XMLSdPropHdlFactory( rExport.GetModel() );
    UniReference < XMLPropertySetMapper > xMapper = new XMLShapePropertySetMapper( xFactory );
    SvXMLExportPropertyMapper* pResult =
        new XMLShapeExportPropertyMapper( xMapper,
                                          (XMLTextListAutoStylePool*)&rExport.GetTextParagraphExport()->GetListAutoStylePool(),
                                          rExport );
    // chain text attributes
    return pResult;
}

///////////////////////////////////////////////////////////////////////

void XMLShapeExport::ImpCalcShapeType(const uno::Reference< drawing::XShape >& xShape,
    XmlShapeType& eShapeType)
{
    // set in every case, so init here
    eShapeType = XmlShapeTypeUnknown;

    uno::Reference< drawing::XShapeDescriptor > xShapeDescriptor(xShape, uno::UNO_QUERY);
    if(xShapeDescriptor.is())
    {
        String aType((OUString)xShapeDescriptor->getShapeType());

        if(aType.EqualsAscii((const sal_Char*)"com.sun.star.", 0, 13))
        {
            if(aType.EqualsAscii("drawing.", 13, 8))
            {
                // drawing shapes
                if     (aType.EqualsAscii("Rectangle", 21, 9)) { eShapeType = XmlShapeTypeDrawRectangleShape; }
                else if(aType.EqualsAscii("Ellipse", 21, 7)) { eShapeType = XmlShapeTypeDrawEllipseShape; }
                else if(aType.EqualsAscii("Control", 21, 7)) { eShapeType = XmlShapeTypeDrawControlShape; }
                else if(aType.EqualsAscii("Connector", 21, 9)) { eShapeType = XmlShapeTypeDrawConnectorShape; }
                else if(aType.EqualsAscii("Measure", 21, 7)) { eShapeType = XmlShapeTypeDrawMeasureShape; }
                else if(aType.EqualsAscii("Line", 21, 4)) { eShapeType = XmlShapeTypeDrawLineShape; }
                else if(aType.EqualsAscii("PolyPolygon", 21, 11)) { eShapeType = XmlShapeTypeDrawPolyPolygonShape; }
                else if(aType.EqualsAscii("PolyLine", 21, 8)) { eShapeType = XmlShapeTypeDrawPolyLineShape; }
                else if(aType.EqualsAscii("OpenBezier", 21, 10)) { eShapeType = XmlShapeTypeDrawOpenBezierShape; }
                else if(aType.EqualsAscii("ClosedBezier", 21, 12)) { eShapeType = XmlShapeTypeDrawClosedBezierShape; }
                else if(aType.EqualsAscii("GraphicObject", 21, 13)) { eShapeType = XmlShapeTypeDrawGraphicObjectShape; }
                else if(aType.EqualsAscii("Group", 21, 5)) { eShapeType = XmlShapeTypeDrawGroupShape; }
                else if(aType.EqualsAscii("Text", 21, 4)) { eShapeType = XmlShapeTypeDrawTextShape; }
                else if(aType.EqualsAscii("OLE2", 21, 4))
                {
                    eShapeType = XmlShapeTypeDrawOLE2Shape;

                    // get info about presentation shape
                    uno::Reference <beans::XPropertySet> xPropSet(xShape, uno::UNO_QUERY);

                    if(xPropSet.is())
                    {
                        uno::Any aAny;
                        aAny = xPropSet->getPropertyValue(OUString(RTL_CONSTASCII_USTRINGPARAM("CLSID")));
                        ::rtl::OUString sCLSID;
                        if (aAny >>= sCLSID)
                        {
                            if (sCLSID.equals(rExport.GetChartExport()->getChartCLSID()))
                            {
                                eShapeType = XmlShapeTypeDrawChartShape;
                            }
                            else if (
                                sCLSID.equals( ::rtl::OUString( SvGlobalName( SO3_SC_CLASSID ).GetHexName()))
                                // #110680#
                                // same reaction for binfilter
                                || sCLSID.equals( ::rtl::OUString( SvGlobalName( BF_SO3_SC_CLASSID ).GetHexName()))
                                )
                            {
                                eShapeType = XmlShapeTypeDrawTableShape;
                            }
                            else
                            {
                                // general OLE2 Object
                            }
                        }
/*						uno::Reference <lang::XServiceInfo> xObjectInfo;

                        if(aAny >>= xObjectInfo)
                        {
                            if(xObjectInfo->supportsService(OUString(RTL_CONSTASCII_USTRINGPARAM
                                ("com.sun.star.chart.ChartDocument"))))
                            {
                                eShapeType = XmlShapeTypeDrawChartShape;
                            }
                            else if(xObjectInfo->supportsService(OUString(RTL_CONSTASCII_USTRINGPARAM
                                ("com.sun.star.sheet.SpreadsheetDocument"))))
                            {
                                eShapeType = XmlShapeTypeDrawTableShape;
                            }
                            else
                            {
                                // general OLE2 Object
                            }
                        }*/
                    }
                }
                else if(aType.EqualsAscii("Page", 21, 4)) { eShapeType = XmlShapeTypeDrawPageShape; }
                else if(aType.EqualsAscii("Frame", 21, 5)) { eShapeType = XmlShapeTypeDrawFrameShape; }
                else if(aType.EqualsAscii("Caption", 21, 7)) { eShapeType = XmlShapeTypeDrawCaptionShape; }
                else if(aType.EqualsAscii("Plugin", 21, 6)) { eShapeType = XmlShapeTypeDrawPluginShape; }
                else if(aType.EqualsAscii("Applet", 21, 6)) { eShapeType = XmlShapeTypeDrawAppletShape; }

                // 3D shapes
                else if(aType.EqualsAscii("Scene", 21 + 7, 5)) { eShapeType = XmlShapeTypeDraw3DSceneObject; }
                else if(aType.EqualsAscii("Cube", 21 + 7, 4)) { eShapeType = XmlShapeTypeDraw3DCubeObject; }
                else if(aType.EqualsAscii("Sphere", 21 + 7, 6)) { eShapeType = XmlShapeTypeDraw3DSphereObject; }
                else if(aType.EqualsAscii("Lathe", 21 + 7, 5)) { eShapeType = XmlShapeTypeDraw3DLatheObject; }
                else if(aType.EqualsAscii("Extrude", 21 + 7, 7)) { eShapeType = XmlShapeTypeDraw3DExtrudeObject; }
            }
            else if(aType.EqualsAscii("presentation.", 13, 13))
            {
                // presentation shapes
                if     (aType.EqualsAscii("TitleText", 26, 9)) { eShapeType = XmlShapeTypePresTitleTextShape; }
                else if(aType.EqualsAscii("Outliner", 26, 8)) { eShapeType = XmlShapeTypePresOutlinerShape;  }
                else if(aType.EqualsAscii("Subtitle", 26, 8)) { eShapeType = XmlShapeTypePresSubtitleShape;  }
                else if(aType.EqualsAscii("GraphicObject", 26, 13)) { eShapeType = XmlShapeTypePresGraphicObjectShape;  }
                else if(aType.EqualsAscii("Page", 26, 4)) { eShapeType = XmlShapeTypePresPageShape;  }
                else if(aType.EqualsAscii("OLE2", 26, 4)) { eShapeType = XmlShapeTypePresOLE2Shape; }
                else if(aType.EqualsAscii("Chart", 26, 5)) { eShapeType = XmlShapeTypePresChartShape;  }
                else if(aType.EqualsAscii("Table", 26, 5)) { eShapeType = XmlShapeTypePresTableShape;  }
                else if(aType.EqualsAscii("OrgChart", 26, 8)) { eShapeType = XmlShapeTypePresOrgChartShape;  }
                else if(aType.EqualsAscii("Notes", 26, 5)) { eShapeType = XmlShapeTypePresNotesShape;  }
                else if(aType.EqualsAscii("HandoutShape", 26, 12)) { eShapeType = XmlShapeTypeHandoutShape; }
            }
        }
    }
}

///////////////////////////////////////////////////////////////////////

extern SvXMLEnumMapEntry aXML_GlueAlignment_EnumMap[];
extern SvXMLEnumMapEntry aXML_GlueEscapeDirection_EnumMap[];

/** exports all user defined glue points */
void XMLShapeExport::ImpExportGluePoints( const uno::Reference< drawing::XShape >& xShape )
{
    uno::Reference< drawing::XGluePointsSupplier > xSupplier( xShape, uno::UNO_QUERY );
    if( !xSupplier.is() )
        return;

    uno::Reference< container::XIdentifierAccess > xGluePoints( xSupplier->getGluePoints(), uno::UNO_QUERY );
    if( !xGluePoints.is() )
        return;

    drawing::GluePoint2 aGluePoint;

    uno::Sequence< sal_Int32 > aIdSequence( xGluePoints->getIdentifiers() );

    const sal_Int32 nCount = aIdSequence.getLength();
    for( sal_Int32 nIndex = 0; nIndex < nCount; nIndex++ )
    {
        const sal_Int32 nIdentifier = aIdSequence[nIndex];
        if( (xGluePoints->getByIdentifier( nIdentifier ) >>= aGluePoint) && aGluePoint.IsUserDefined )
        {
            // export only user defined glue points

            const OUString sId( OUString::valueOf( nIdentifier ) );
            rExport.AddAttribute(XML_NAMESPACE_DRAW, XML_ID, sId );

            rExport.GetMM100UnitConverter().convertMeasure(msBuffer, aGluePoint.Position.X);
            rExport.AddAttribute(XML_NAMESPACE_SVG, XML_X, msBuffer.makeStringAndClear());

            rExport.GetMM100UnitConverter().convertMeasure(msBuffer, aGluePoint.Position.Y);
            rExport.AddAttribute(XML_NAMESPACE_SVG, XML_Y, msBuffer.makeStringAndClear());

            if( !aGluePoint.IsRelative )
            {
                SvXMLUnitConverter::convertEnum( msBuffer, aGluePoint.PositionAlignment, aXML_GlueAlignment_EnumMap );
                rExport.AddAttribute( XML_NAMESPACE_DRAW, XML_ALIGN, msBuffer.makeStringAndClear() );
            }

            if( aGluePoint.Escape != drawing::EscapeDirection_SMART )
            {
                SvXMLUnitConverter::convertEnum( msBuffer, aGluePoint.Escape, aXML_GlueEscapeDirection_EnumMap );
                rExport.AddAttribute( XML_NAMESPACE_DRAW, XML_ESCAPE_DIRECTION, msBuffer.makeStringAndClear() );
            }

            SvXMLElementExport aEventsElemt(rExport, XML_NAMESPACE_DRAW, XML_GLUE_POINT, sal_True, sal_True);
        }
    }
}

void XMLShapeExport::ExportGraphicDefaults()
{
    XMLStyleExport aStEx(rExport, OUString(), rExport.GetAutoStylePool().get());

    // construct PropertySetMapper
    UniReference< SvXMLExportPropertyMapper > xPropertySetMapper( CreateShapePropMapper( rExport ) );
    ((XMLShapeExportPropertyMapper*)xPropertySetMapper.get())->SetAutoStyles( sal_False );

    // chain text attributes
    xPropertySetMapper->ChainExportMapper(XMLTextParagraphExport::CreateParaExtPropMapper(rExport));

    // write graphic family default style
    uno::Reference< lang::XMultiServiceFactory > xFact( rExport.GetModel(), uno::UNO_QUERY );
    if( xFact.is() )
    {
        try
        {
            uno::Reference< beans::XPropertySet > xDefaults( xFact->createInstance( OUString(RTL_CONSTASCII_USTRINGPARAM("com.sun.star.drawing.Defaults") ) ), uno::UNO_QUERY );
            if( xDefaults.is() )
            {
                aStEx.exportDefaultStyle( xDefaults, OUString(RTL_CONSTASCII_USTRINGPARAM(XML_STYLE_FAMILY_SD_GRAPHICS_NAME)), xPropertySetMapper );

                // write graphic family styles
                aStEx.exportStyleFamily(XML_STYLE_FAMILY_SD_GRAPHICS_NAME, OUString(RTL_CONSTASCII_USTRINGPARAM(XML_STYLE_FAMILY_SD_GRAPHICS_NAME)), xPropertySetMapper, FALSE, XML_STYLE_FAMILY_SD_GRAPHICS_ID);
            }
        }
        catch( lang::ServiceNotRegisteredException& )
        {
        }
    }
}

void XMLShapeExport::onExport( const ::com::sun::star::uno::Reference < ::com::sun::star::drawing::XShape >& xShape )
{
}

}//end of namespace binfilter
