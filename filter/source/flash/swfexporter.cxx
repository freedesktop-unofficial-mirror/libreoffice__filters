/*************************************************************************
 *
 *  $RCSfile: swfexporter.cxx,v $
 *
 *  $Revision: 1.2 $
 *
 *  last change: $Author: cl $ $Date: 2002-11-22 14:22:38 $
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
 *  Contributor(s): Christian Lippka (christian.lippka@sun.com)
 *
 *
 ************************************************************************/

#ifndef _COM_SUN_STAR_AWT_RECTANGLE_HPP_ 
#include <com/sun/star/awt/Rectangle.hpp>
#endif
#ifndef _COM_SUN_STAR_BEANS_PROPERTYVALUE_HPP_
#include <com/sun/star/beans/PropertyValue.hpp>
#endif
#ifndef _COM_SUN_STAR_DRAWING_XMASTERPAGETARGET_HPP_
#include <com/sun/star/drawing/XMasterPageTarget.hpp>
#endif
#ifndef _COM_SUN_STAR_DRAWING_XDRAWPAGESSUPPLIER_HPP_
#include <com/sun/star/drawing/XDrawPagesSupplier.hpp>
#endif
#ifndef _COM_SUN_STAR_CONTAINER_XINDEXACCESS_HPP_
#include <com/sun/star/container/XIndexAccess.hpp>
#endif
#ifndef _COM_SUN_STAR_DRAWING_XDRAWPAGESSUPPLIER_HPP_
#include <com/sun/star/drawing/XDrawPagesSupplier.hpp>
#endif
#ifndef _COM_SUN_STAR_DOCUMENT_XFILTER_HPP_
#include <com/sun/star/document/XFilter.hpp>
#endif
#ifndef _COM_SUN_STAR_DOCUMENT_XEXPORTER_HPP_
#include <com/sun/star/document/XExporter.hpp>
#endif
#ifndef _COM_SUN_STAR_FRAME_XMODEL_HPP_
#include <com/sun/star/frame/XModel.hpp>
#endif
#ifndef _COM_SUN_STAR_TASK_XSTATUSINDICATORFACTORY_HPP_
#include <com/sun/star/task/XStatusIndicatorFactory.hpp>
#endif
#ifndef _COM_SUN_STAR_LANG_XSERVICEINFO_HPP_
#include <com/sun/star/lang/XServiceInfo.hpp>
#endif

#ifndef _SV_GDIMTF_HXX 
#include <vcl/gdimtf.hxx>
#endif

#ifndef _UNOTOOLS_TEMPFILE_HXX
#include <unotools/tempfile.hxx>
#endif

#ifndef _OSL_DIAGNOSE_H_
#include <osl/diagnose.h>
#endif
#ifndef _OSL_FILE_HXX_
#include <osl/file.hxx>
#endif
#ifndef _SV_METAACT_HXX 
#include <vcl/metaact.hxx>
#endif

#ifndef _WMF_HXX
#include <svtools/wmf.hxx>
#endif
#ifndef _FILTER_HXX
#include <svtools/Filter.hxx>
#endif

#include "swfexporter.hxx"
#include "swfwriter.hxx"

using rtl::OUString;
using namespace ::com::sun::star::uno;
using namespace ::com::sun::star::drawing;
using namespace ::com::sun::star::presentation;
using namespace ::com::sun::star::task;
using namespace ::std;
using namespace ::swf;

using com::sun::star::lang::XMultiServiceFactory;
using com::sun::star::io::XOutputStream;
using com::sun::star::beans::PropertyValue;
using com::sun::star::container::XIndexAccess;
using com::sun::star::beans::XPropertySet;
using com::sun::star::lang::XComponent;
using com::sun::star::lang::IllegalArgumentException;
using com::sun::star::document::XExporter;
using com::sun::star::document::XFilter;
using com::sun::star::frame::XModel;
using com::sun::star::lang::XServiceInfo;

// -----------------------------------------------------------------------------

static const char* pszCurrentPageName = "current_page";		// TODO: Size optimize later?
static const char* pszLastPageName = "last_page";			// TODO: Size optimize later?

// -----------------------------------------------------------------------------

PageInfo::PageInfo()
:		meFadeEffect( FadeEffect_NONE ),
        meFadeSpeed( AnimationSpeed_MEDIUM ),
        mnDuration( 0 ),
        mnChange( 0 )
{
}

// -----------------------------------------------------------------------------

PageInfo::~PageInfo()
{
    vector<ShapeInfo*>::iterator aIter( maShapesVector.begin() );
    const vector<ShapeInfo*>::iterator aEnd( maShapesVector.end() );
    while( aIter != aEnd )
    {
        delete (*aIter++);
    }
}

// -----------------------------------------------------------------------------

void PageInfo::addShape( ShapeInfo* pShapeInfo )
{
    maShapesVector.push_back( pShapeInfo );
}


// -----------------------------------------------------------------------------

FlashExporter::FlashExporter(const Reference< XMultiServiceFactory > &rxMSF, sal_Int32 nJPEGCompressMode, sal_Bool bExportOLEAsJPEG)
:	mxMSF( rxMSF ), mpWriter( NULL ), mnJPEGcompressMode(nJPEGCompressMode), mbExportOLEAsJPEG(bExportOLEAsJPEG), mbPresentation(true)
{
}

// -----------------------------------------------------------------------------

FlashExporter::~FlashExporter()
{
    Flush();
}

void FlashExporter::Flush()
{
    delete mpWriter;
    mpWriter = NULL;

    maPagesMap.clear();
}

// -----------------------------------------------------------------------------

const sal_uInt16 cBackgroundDepth = 2;
const sal_uInt16 cBackgroundObjectsDepth = 3;
const sal_uInt16 cPageObjectsDepth = 4;
const sal_uInt16 cWaitButtonDepth = 10;

sal_Bool FlashExporter::exportAll( Reference< XComponent > xDoc, Reference< XOutputStream > &xOutputStream, Reference< XStatusIndicator> &xStatusIndicator )
{
    Reference< XServiceInfo > xDocServInfo( xDoc, UNO_QUERY );
    if( xDocServInfo.is() )
        mbPresentation = xDocServInfo->supportsService( OUString( RTL_CONSTASCII_USTRINGPARAM("com.sun.star.presentation.PresentationDocument"))) ;

    Reference< XDrawPagesSupplier > xDrawPagesSupplier(xDoc, UNO_QUERY);
    if(!xDrawPagesSupplier.is())
        return sal_False;

    Reference< XIndexAccess > xDrawPages( xDrawPagesSupplier->getDrawPages(), UNO_QUERY );
    if(!xDrawPages.is())
        return sal_False;

    Reference< XDrawPage > xDrawPage;
    xDrawPages->getByIndex(0) >>= xDrawPage;

    Reference< XPropertySet > xProp( xDrawPage, UNO_QUERY );
    try
    {
        xProp->getPropertyValue( OUString( RTL_CONSTASCII_USTRINGPARAM("Width") ) ) >>= mnDocWidth;
        xProp->getPropertyValue( OUString( RTL_CONSTASCII_USTRINGPARAM("Height") ) ) >>= mnDocHeight;

        sal_Int32 nOutputWidth = 14400;
        sal_Int32 nOutputHeight = (nOutputWidth * mnDocHeight ) / mnDocWidth;
        delete mpWriter;
        mpWriter = new Writer( nOutputWidth, nOutputHeight, mnDocWidth, mnDocHeight, mnJPEGcompressMode  );
    }
    catch( exception& )
    {
        OSL_ASSERT( false );
        return false; // no writer, no cookies
    }

    const sal_Int32 nPageCount = xDrawPages->getCount();
    sal_uInt16 nPage;
    xStatusIndicator->start(OUString( RTL_CONSTASCII_USTRINGPARAM( "Macromedia Flash (SWF)" )), nPageCount);
    for( nPage = 0; nPage < nPageCount; nPage++)
    {
        xStatusIndicator->setValue( nPage );
        xDrawPages->getByIndex(nPage) >>= xDrawPage;

        if( !xDrawPage.is())
            continue;

        Reference< XPropertySet > xPropSet( xDrawPage, UNO_QUERY );
        if( mbPresentation )
        {
            sal_Bool bVisible;
            xPropSet->getPropertyValue( OUString( RTL_CONSTASCII_USTRINGPARAM("Visible") ) ) >>= bVisible;
            if( !bVisible )
                continue;
        }

        exportBackgrounds( xDrawPage, nPage, false );
        exportBackgrounds( xDrawPage, nPage, true );

        maPagesMap[nPage].mnForegroundID = mpWriter->startSprite();
        exportDrawPageContents( xDrawPage, false );
        mpWriter->endSprite();

        // AS: If the background is different than the previous slide,
        //  we have to remove the old one and place the new one.
        if (nPage) 
        {
            if (maPagesMap[nPage].mnBackgroundID != maPagesMap[nPage-1].mnBackgroundID)
            {
                mpWriter->removeShape(cBackgroundDepth);
                mpWriter->placeShape( maPagesMap[nPage].mnBackgroundID, cBackgroundDepth, 0, 0 );
            }

            if (maPagesMap[nPage].mnObjectsID != maPagesMap[nPage-1].mnObjectsID)
            {
                mpWriter->removeShape(cBackgroundObjectsDepth);
                mpWriter->placeShape( maPagesMap[nPage].mnObjectsID, cBackgroundObjectsDepth, 0, 0 );
            }

            // AS: Remove the Foreground of the previous slide.
            mpWriter->removeShape(cPageObjectsDepth);
        }
        else
        {
            mpWriter->placeShape( maPagesMap[nPage].mnBackgroundID, cBackgroundDepth, 0, 0 );
            mpWriter->placeShape( maPagesMap[nPage].mnObjectsID, cBackgroundObjectsDepth, 0, 0 );
        }

        mpWriter->placeShape( maPagesMap[nPage].mnForegroundID, cPageObjectsDepth, 0, 0 );

        mpWriter->waitOnClick( cWaitButtonDepth );
        mpWriter->showFrame();
    }

    mpWriter->removeShape( cBackgroundDepth );
    mpWriter->removeShape( cBackgroundObjectsDepth );
    mpWriter->removeShape( cPageObjectsDepth );
    mpWriter->gotoFrame( 0 );
    mpWriter->showFrame();

    mpWriter->storeTo( xOutputStream );

    return sal_True;
}


sal_Bool FlashExporter::exportSlides( Reference< XDrawPage > xDrawPage, Reference< XOutputStream > &xOutputStream, sal_uInt16 nPage)
{
    Reference< XPropertySet > xPropSet( xDrawPage, UNO_QUERY );
    if( !xDrawPage.is() || !xPropSet.is() )
        return sal_False;

    try
    {
        if( NULL == mpWriter )
        {
            xPropSet->getPropertyValue( OUString( RTL_CONSTASCII_USTRINGPARAM("Width") ) ) >>= mnDocWidth;
            xPropSet->getPropertyValue( OUString( RTL_CONSTASCII_USTRINGPARAM("Height") ) ) >>= mnDocHeight;

            mpWriter = new Writer( 14400, 10800, mnDocWidth, mnDocHeight, mnJPEGcompressMode );
        }

        if( mbPresentation )
        {
            sal_Bool bVisible;
            xPropSet->getPropertyValue( OUString( RTL_CONSTASCII_USTRINGPARAM("Visible") ) ) >>= bVisible;
            if( !bVisible )
                return sal_False;
        }
    }
    catch( exception& )
    {
        OSL_ASSERT( false );
    }

    exportDrawPageContents(xDrawPage, true);

    mpWriter->storeTo( xOutputStream );

    return sal_True;
}

sal_uInt16 FlashExporter::exportBackgrounds( Reference< XDrawPage > xDrawPage, Reference< XOutputStream > &xOutputStream, sal_uInt16 nPage, sal_Bool bExportObjects )
{
    Reference< XPropertySet > xPropSet( xDrawPage, UNO_QUERY );
    if( !xDrawPage.is() || !xPropSet.is() )
        return sal_False;

    if( NULL == mpWriter )
    {
        xPropSet->getPropertyValue( OUString( RTL_CONSTASCII_USTRINGPARAM("Width") ) ) >>= mnDocWidth;
        xPropSet->getPropertyValue( OUString( RTL_CONSTASCII_USTRINGPARAM("Height") ) ) >>= mnDocHeight;

        mpWriter = new Writer( 14400, 10800, mnDocWidth, mnDocHeight, mnJPEGcompressMode );
    }

    sal_uInt16 ret = exportBackgrounds(xDrawPage, nPage, bExportObjects);

    if (ret != nPage)
        return ret;

    if (bExportObjects)
        mpWriter->placeShape( maPagesMap[nPage].mnObjectsID, _uInt16(1), 0, 0 );
    else
        mpWriter->placeShape( maPagesMap[nPage].mnBackgroundID, _uInt16(0), 0, 0 );

    mpWriter->storeTo( xOutputStream );

    return nPage;
}

sal_uInt16 FlashExporter::exportBackgrounds( Reference< XDrawPage > xDrawPage, sal_uInt16 nPage, sal_Bool bExportObjects )
{
    Reference< XPropertySet > xPropSet( xDrawPage, UNO_QUERY );
    if( !xDrawPage.is() || !xPropSet.is() )
        return sal_False;

    sal_Bool bBackgroundVisible = true;
    sal_Bool bBackgroundObjectsVisible = true;

    if( mbPresentation )
    {
        xPropSet->getPropertyValue( OUString( RTL_CONSTASCII_USTRINGPARAM("IsBackgroundVisible") ) ) >>= bBackgroundVisible;
        xPropSet->getPropertyValue( OUString( RTL_CONSTASCII_USTRINGPARAM("IsBackgroundObjectsVisible") ) ) >>= bBackgroundObjectsVisible;
    }


    if (bExportObjects)
    {
        if (bBackgroundObjectsVisible)
        {
            Reference< XMasterPageTarget > xMasterPageTarget( xDrawPage, UNO_QUERY );
            if( !xMasterPageTarget.is() )
            {
                maPagesMap[nPage].mnObjectsID = -1;
                return -1;
            }
            
            sal_uInt16 ret = exportMasterPageObjects(nPage, xMasterPageTarget->getMasterPage());
            if (ret != nPage)
                return ret;
        }
        else
        {
            maPagesMap[nPage].mnObjectsID = -1;
            return -1;
        }
    }
    else
    {
        if (bBackgroundVisible)
        {
            sal_uInt16 ret = exportDrawPageBackground(nPage, xDrawPage);

            if (ret != nPage)
                return ret;
        }
        else
        {
            maPagesMap[nPage].mnBackgroundID = -1;
            return -1;
        }
    }

    return nPage;
}

#ifdef AUGUSTUS
sal_Bool FlashExporter::exportSound( Reference< XOutputStream > &xOutputStream, const char* wavfilename )
{
    try
    {
        delete mpWriter;
        mpWriter = new Writer( 0, 0, 0, 0 );
    }
    catch( exception& )
    {
        OSL_ASSERT( false );
    }

    if (!mpWriter->streamSound(wavfilename))
        return sal_False;
    else
        mpWriter->storeTo( xOutputStream );

    return sal_True;
}
#endif // defined AUGUSTUS

// -----------------------------------------------------------------------------

sal_Int32 nPlaceDepth;
// AS: A Slide can have a private background or use its masterpage's background.
//  We use the checksums on the metafiles to tell if backgrounds are the same and
//  should be reused.  The return value indicates which slide's background to use.
//  If the return value != nPage, then there is no background (if == -1) or the
//  background has already been exported.
sal_uInt16 FlashExporter::exportDrawPageBackground(sal_uInt16 nPage, Reference< XDrawPage >& xPage)
{
    sal_uInt16 rBackgroundID;

    GDIMetaFile aMtfPrivate, aMtfMaster;
    Reference< XComponent > xComponent( xPage, UNO_QUERY );

    Reference< XMasterPageTarget > xMasterPageTarget( xPage, UNO_QUERY );
    if( !xMasterPageTarget.is() )
        return -1;

    Reference< XDrawPage > xMasterPage = xMasterPageTarget->getMasterPage();
    if( !xMasterPage.is())
        return -1;

    Reference< XComponent > xCompMaster( xMasterPage, UNO_QUERY );

    getMetaFile( xCompMaster, aMtfMaster, true );
    getMetaFile( xComponent, aMtfPrivate, true );

    sal_uInt32 masterchecksum = aMtfMaster.GetChecksum();
    sal_uInt32 privatechecksum = aMtfPrivate.GetChecksum();

    // AS: If the slide has its own background
    if (privatechecksum)
    {
        ChecksumCache::iterator it = gPrivateCache.find(privatechecksum);

        // AS: and we've previously encountered this background, just return
        //  the previous index.
        if (gPrivateCache.end() != it)
        {
            maPagesMap[nPage].mnBackgroundID = 
                maPagesMap[it->second].mnBackgroundID;
            return it->second;
        }
        else
        {
            // AS: Otherwise, cache this checksum.
            gPrivateCache[privatechecksum] = nPage;

            rBackgroundID = mpWriter->defineShape( aMtfPrivate );

            mpWriter->placeShape( rBackgroundID, _uInt16(0), 0, 0 );

            maPagesMap[nPage].mnBackgroundID = rBackgroundID;
            return nPage;
        }
    }

    // AS: Ok, no private background.  Use the master page's.
    // AS: Have we already exported this master page?
    ChecksumCache::iterator it = gMasterCache.find(masterchecksum);

    if (gMasterCache.end() != it)
    {
        maPagesMap[nPage].mnBackgroundID = 
            maPagesMap[it->second].mnBackgroundID;

        return it->second;                // AS: Yes, so don't export it again.
    }

    gMasterCache[masterchecksum] = nPage;

    rBackgroundID = mpWriter->defineShape( aMtfMaster );

    maPagesMap[nPage].mnBackgroundID = rBackgroundID;

    return nPage;
}

sal_uInt16 FlashExporter::exportMasterPageObjects(sal_uInt16 nPage, Reference< XDrawPage >& xMasterPage)
{
    Reference< XShapes > xShapes( xMasterPage, UNO_QUERY );

    sal_uInt32 shapesum = ActionSummer(xShapes);

    ChecksumCache::iterator it = gObjectCache.find(shapesum);

    if (gObjectCache.end() != it)
    {
        maPagesMap[nPage].mnObjectsID = 
            maPagesMap[it->second].mnObjectsID;

        return it->second;                // AS: Yes, so don't export it again.
    }

    gObjectCache[shapesum] = nPage;
    
    sal_uInt16 rObjectsID = mpWriter->startSprite();
    exportDrawPageContents( xMasterPage, sal_False );
    mpWriter->endSprite();

    maPagesMap[nPage].mnObjectsID = rObjectsID;

    return nPage;
}

// -----------------------------------------------------------------------------

/** export's the definition of the shapes inside this drawing page and adds the
    shape infos to the current PageInfo */
void FlashExporter::exportDrawPageContents( Reference< XDrawPage >& xPage, sal_Bool bStream )
{
    Reference< XShapes > xShapes( xPage, UNO_QUERY );
    exportShapes(xShapes, bStream);
}

// -----------------------------------------------------------------------------

/** export's the definition of the shapes inside this XShapes container and adds the
    shape infos to the current PageInfo */
void FlashExporter::exportShapes( Reference< XShapes >& xShapes, sal_Bool bStream)
{
    OSL_ENSURE( (xShapes->getCount() <= 0xffff), "overflow in FlashExporter::exportDrawPageContents()" );

    sal_uInt16 nShapeCount = (sal_uInt16)min( xShapes->getCount(), (sal_Int32)0xffff );
    sal_uInt16 nShape;

    Reference< XShape > xShape;

    for( nShape = 0; nShape < nShapeCount; nShape++ )
    {
        xShapes->getByIndex( nShape ) >>= xShape;

        if( xShape.is() )
        {
            Reference< XShapes > xShapes( xShape, UNO_QUERY );
            if( xShapes.is() && xShape->getShapeType().equalsAsciiL(RTL_CONSTASCII_STRINGPARAM("com.sun.star.drawing.GroupShape")))
                // export the contents of group shapes, but we only ever stream at the top 
                // recursive level anyway, so pass false for streaming.
                exportShapes( xShapes, false);
            else
                exportShape( xShape);
        }

        if (bStream)
            mpWriter->showFrame();
    }
}

// -----------------------------------------------------------------------------

/** export this shape definition and adds it's info to the current PageInfo */
void FlashExporter::exportShape( Reference< XShape >& xShape)
{
    Reference< XPropertySet > xPropSet( xShape, UNO_QUERY );
    if( !xPropSet.is() )
        return;

    if( mbPresentation )
    {
        try
        {
            // skip empty presentation objects
            sal_Bool bEmpty;
            xPropSet->getPropertyValue( OUString( RTL_CONSTASCII_USTRINGPARAM("IsEmptyPresentationObject") ) ) >>= bEmpty;
            if( bEmpty )
                return;
        }
        catch( Exception& )
        {
            // TODO: If we are exporting a draw, this property is not available
        }
    }

    try
    {
            com::sun::star::awt::Point aPosition( xShape->getPosition() );
            com::sun::star::awt::Size aSize( xShape->getSize() );

            com::sun::star::awt::Rectangle aBoundRect;//(aPosition.X, aPosition.Y, aSize.Width, aSize.Height);
            xPropSet->getPropertyValue( OUString( RTL_CONSTASCII_USTRINGPARAM("BoundRect") ) ) >>= aBoundRect;

            ShapeInfo* pShapeInfo = new ShapeInfo();
            pShapeInfo->mnX = aBoundRect.X;
            pShapeInfo->mnY = aBoundRect.Y;
            pShapeInfo->mnWidth = aBoundRect.Width;
            pShapeInfo->mnHeight = aBoundRect.Height;

            if( mbPresentation )
            {
                xPropSet->getPropertyValue( OUString( RTL_CONSTASCII_USTRINGPARAM("Bookmark") ) ) >>= pShapeInfo->maBookmark;
                xPropSet->getPropertyValue( OUString( RTL_CONSTASCII_USTRINGPARAM("DimColor") ) ) >>= pShapeInfo->mnDimColor;
                xPropSet->getPropertyValue( OUString( RTL_CONSTASCII_USTRINGPARAM("DimHide") ) ) >>= pShapeInfo->mbDimHide;
                xPropSet->getPropertyValue( OUString( RTL_CONSTASCII_USTRINGPARAM("DimPrevious") ) ) >>= pShapeInfo->mbDimPrev;
                xPropSet->getPropertyValue( OUString( RTL_CONSTASCII_USTRINGPARAM("Effect") ) ) >>= pShapeInfo->meEffect;
                xPropSet->getPropertyValue( OUString( RTL_CONSTASCII_USTRINGPARAM("PlayFull") ) ) >>= pShapeInfo->mbPlayFull;
                xPropSet->getPropertyValue( OUString( RTL_CONSTASCII_USTRINGPARAM("PresentationOrder") ) ) >>= pShapeInfo->mnPresOrder;
                xPropSet->getPropertyValue( OUString( RTL_CONSTASCII_USTRINGPARAM("Sound") ) ) >>= pShapeInfo->maSoundURL;
                xPropSet->getPropertyValue( OUString( RTL_CONSTASCII_USTRINGPARAM("SoundOn") ) ) >>= pShapeInfo->mbSoundOn;
                xPropSet->getPropertyValue( OUString( RTL_CONSTASCII_USTRINGPARAM("Speed") ) ) >>= pShapeInfo->meEffectSpeed;
                xPropSet->getPropertyValue( OUString( RTL_CONSTASCII_USTRINGPARAM("TextEffect") ) ) >>= pShapeInfo->meTextEffect;
                xPropSet->getPropertyValue( OUString( RTL_CONSTASCII_USTRINGPARAM("TransparentColor") ) ) >>= pShapeInfo->mnBlueScreenColor;
            }

//			long ZOrder;
//			xPropSet->getPropertyValue( OUString( RTL_CONSTASCII_USTRINGPARAM("ZOrder") ) ) >>= ZOrder;

            GDIMetaFile		aMtf;
            Reference< XComponent > xComponent( xShape, UNO_QUERY );

            bool bIsOleObject = xShape->getShapeType().equalsAsciiL(RTL_CONSTASCII_STRINGPARAM("com.sun.star.presentation.OLE2Shape"))
                                || xShape->getShapeType().equalsAsciiL(RTL_CONSTASCII_STRINGPARAM("com.sun.star.drawing.OLE2Shape"));

            getMetaFile( xComponent, aMtf );

            // AS: If it's an OLE object, then export a JPEG if the user requested.
            //  In this case, we use the bounding rect info generated in the first getMetaFile
            //  call, and then clear the metafile and add a BMP action.  This may be turned into
            //  a JPEG, depending on what gives the best compression.
            if (bIsOleObject && mbExportOLEAsJPEG)
                getMetaFile( xComponent, aMtf, false, true );

            sal_uInt16 nID;
            sal_uInt32 checksum = aMtf.GetChecksum();

            ChecksumCache::iterator it = gMetafileCache.find(checksum);

            if (gMetafileCache.end() != it)
                nID = it->second;
            else
            {
                nID = mpWriter->defineShape( aMtf );
                gMetafileCache[checksum] = nID;
            }

            if (!nID)
                return;

            pShapeInfo->mnID = nID;

//			pPageInfo->addShape( pShapeInfo );

            mpWriter->placeShape( pShapeInfo->mnID, _uInt16(nPlaceDepth++), pShapeInfo->mnX, pShapeInfo->mnY );

            delete pShapeInfo;
    }
    catch( Exception& )
    {
        OSL_ASSERT(false);
    }
}

// -----------------------------------------------------------------------------

bool FlashExporter::getMetaFile( Reference< XComponent >&xComponent, GDIMetaFile& rMtf, bool bOnlyBackground /* = false */, bool bExportAsJPEG /* = false */)
{
    if( !mxGraphicExporter.is() )
        mxGraphicExporter = Reference< XExporter >::query( mxMSF->createInstance( OUString( RTL_CONSTASCII_USTRINGPARAM("com.sun.star.drawing.GraphicExportFilter") ) ) );

    Reference< XFilter > xFilter( mxGraphicExporter, UNO_QUERY );

    utl::TempFile aFile;
    aFile.EnableKillingFile();
    
    Sequence< PropertyValue > aFilterData(bExportAsJPEG ? 2 : 1);
    aFilterData[0].Name = OUString( RTL_CONSTASCII_USTRINGPARAM("Version") );
    aFilterData[0].Value <<= (sal_Int32)6000;

    if(bExportAsJPEG)
    {
        aFilterData[1].Name = OUString( RTL_CONSTASCII_USTRINGPARAM("Translucent") );
        aFilterData[1].Value <<= (sal_Bool)sal_True;
    }

    Sequence< PropertyValue > aDescriptor( bOnlyBackground ? 4 : 3 );
    aDescriptor[0].Name = OUString( RTL_CONSTASCII_USTRINGPARAM("FilterName") );

    // AS: If we've been asked to export as an image, then use the BMP filter.
    //  Otherwise, use SVM.  This is useful for things that don't convert well as
    //  metafiles, like the occasional OLE object.
    aDescriptor[0].Value <<= OUString( RTL_CONSTASCII_USTRINGPARAM(bExportAsJPEG ? "PNG" : "SVM") );

    aDescriptor[1].Name = OUString( RTL_CONSTASCII_USTRINGPARAM("URL") );
    aDescriptor[1].Value <<= OUString( aFile.GetURL() );
    aDescriptor[2].Name = OUString( RTL_CONSTASCII_USTRINGPARAM("FilterData") );
    aDescriptor[2].Value <<= aFilterData;
    if( bOnlyBackground )
    {
        aDescriptor[3].Name = OUString( RTL_CONSTASCII_USTRINGPARAM("ExportOnlyBackground") );
        aDescriptor[3].Value <<= (sal_Bool)bOnlyBackground;
    }
    mxGraphicExporter->setSourceDocument( xComponent );
    xFilter->filter( aDescriptor );

    if (bExportAsJPEG)
    {
        Graphic aGraphic;
        GraphicFilter aFilter(false);

        USHORT nRet = aFilter.ImportGraphic( aGraphic, String(aFile.GetURL()), *aFile.GetStream( STREAM_READ ) );
        BitmapEx rBitmapEx( aGraphic.GetBitmap(), Color(255,255,255) );

        sal_Bool bHasAlpha = rBitmapEx.IsAlpha();
        sal_Bool bIsTransparent = rBitmapEx.IsTransparent();

        Rectangle clipRect;
        for( ULONG i = 0, nCount = rMtf.GetActionCount(); i < nCount; i++ )
        {
            const MetaAction*	pAction = rMtf.GetAction( i );
            const USHORT		nType = pAction->GetType();

            switch( nType )
            {
                case( META_ISECTRECTCLIPREGION_ACTION ):
                {
                    const MetaISectRectClipRegionAction* pA = (const MetaISectRectClipRegionAction*) pAction;
                    clipRect = pA->GetRect();
                    i = nCount;
                    break;
                }
            }
        }
        MetaBmpExScaleAction *pmetaAct = new MetaBmpExScaleAction(Point(clipRect.Left(), clipRect.Top()), Size(clipRect.GetWidth(), clipRect.GetHeight()), rBitmapEx);

        rMtf.Clear();
        rMtf.AddAction(pmetaAct);

    }
    else
        rMtf.Read( *aFile.GetStream( STREAM_READ ) );

    int icount = rMtf.GetActionCount();
    return icount != 0;
}

sal_uInt32 FlashExporter::ActionSummer(Reference< XShape >& xShape)
{
    Reference< XShapes > xShapes( xShape, UNO_QUERY );

    if( xShapes.is() )
    {
        return ActionSummer(xShapes);
    }
    else
    {
        Reference< XComponent > xComponentShape( xShape, UNO_QUERY );

        GDIMetaFile	aMtf;
        getMetaFile( xComponentShape, aMtf);

        return aMtf.GetChecksum();
    }
}

sal_uInt32 FlashExporter::ActionSummer(Reference< XShapes >& xShapes)
{
    sal_uInt32 nShapeCount = xShapes->getCount();
    sal_uInt32 shapecount = 0;

    Reference< XShape > xShape2;

    for( sal_uInt16 nShape = 0; nShape < nShapeCount; nShape++ )
    {
        xShapes->getByIndex( nShape ) >>= xShape2;

        shapecount += ActionSummer(xShape2);
    }

    return shapecount;
}