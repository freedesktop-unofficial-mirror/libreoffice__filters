/*************************************************************************
 *
 *  $RCSfile: exporter.cxx,v $
 *
 *  $Revision: 1.2 $
 *
 *  last change: $Author: cl $ $Date: 2002-09-25 12:22:26 $
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

#ifndef _COM_SUN_STAR_UTIL_XCHANGESBATCH_HPP_
#include <com/sun/star/util/XChangesBatch.hpp>
#endif
#ifndef _COM_SUN_STAR_IO_XACTIVEDATASINK_HPP_
#include <com/sun/star/io/XActiveDataSink.hpp>
#endif
#ifndef _COM_SUN_STAR_LANG_XSINGLESERVICEFACTORY_HPP_
#include <com/sun/star/lang/XSingleServiceFactory.hpp>
#endif
#ifndef _COM_SUN_STAR_CONTAINER_XNAMED_HPP_
#include <com/sun/star/container/XNamed.hpp>
#endif
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
#ifndef _COM_SUN_STAR_CONTAINER_XHIERARCHICALNAMEACCESS_HPP_
#include <com/sun/star/container/XHierarchicalNameAccess.hpp>
#endif
#ifndef _COM_SUN_STAR_CONTAINER_XCHILD_HPP_
#include <com/sun/star/container/XChild.hpp>
#endif
#ifndef _COM_SUN_STAR_TEXT_XTEXT_HPP_
#include <com/sun/star/text/XText.hpp>
#endif
#ifndef _COM_SUN_STAR_DOCUMENT_XDOCUMENTINFOSUPPLIER_HPP_
#include <com/sun/star/document/XDocumentInfoSupplier.hpp>
#endif

#ifndef _SV_GDIMTF_HXX 
#include <vcl/gdimtf.hxx>
#endif
#ifndef _RTL_USTRBUF_HXX_
#include <rtl/ustrbuf.hxx>
#endif

#ifndef _UNOTOOLS_TEMPFILE_HXX
#include <unotools/tempfile.hxx>
#endif

#ifndef _OSL_DIAGNOSE_H_
#include <osl/diagnose.h>
#endif

#include <vector>

#ifndef _WMF_HXX
#include <svtools/wmf.hxx>
#endif
#ifndef _STREAM_HXX
#include <tools/stream.hxx>
#endif
#ifndef _UTL_STREAM_WRAPPER_HXX_
#include <unotools/streamwrap.hxx>
#endif
#include "exporter.hxx"
#include "Base64Codec.hxx"

using rtl::OUString;
using namespace ::com::sun::star::uno;
using namespace ::com::sun::star::util;
using namespace ::com::sun::star::drawing;
using namespace ::com::sun::star::container;
using namespace ::com::sun::star::document;
using namespace ::com::sun::star::io;
using namespace ::com::sun::star::lang;
using namespace ::com::sun::star::text;
using namespace ::std;

using com::sun::star::beans::PropertyValue;
using com::sun::star::beans::XPropertySet;

// -----------------------------------------------------------------------------

PlaceWareExporter::PlaceWareExporter(const Reference< XMultiServiceFactory > &rxMSF)
:	mxMSF( rxMSF )
{
}

// -----------------------------------------------------------------------------

PlaceWareExporter::~PlaceWareExporter()
{
}

// -----------------------------------------------------------------------------
class PageEntry
{
private:
    utl::TempFile aFile;
    rtl::OUString maName;
    rtl::OUString maTitle;
    rtl::OUString maNotes;
    rtl::OUString maURL;

public:
    PageEntry();

    OUString getTempURL() const { return aFile.GetURL(); }

    void setName( const rtl::OUString& rName ) { maName = rName; }
    const rtl::OUString& getName() const { return maName; }

    void setTitle( const rtl::OUString& rTitle ) { maTitle = rTitle; }
    const rtl::OUString& getTitle() const { return maTitle; }

    void setNotes( const rtl::OUString& rNotes ) { maNotes = rNotes; }
    const rtl::OUString& getNotes() const { return maNotes; }

    void setURL( const rtl::OUString& rURL ) { maURL = rURL; }
    const rtl::OUString& getURL() const { return maURL; }
};

PageEntry::PageEntry()
{
    aFile.EnableKillingFile();
}


static void addFile( Reference< XInterface > xRootFolder, Reference< XSingleServiceFactory > xFactory, Reference< XInputStream > xInput, OUString aName )
{
    Reference< XActiveDataSink > xSink( xFactory->createInstance(), UNO_QUERY );
    Reference< XNamed > xNamed( xSink, UNO_QUERY );
    Reference< XChild > xChild( xSink, UNO_QUERY );

    if( xSink.is() && xNamed.is() && xChild.is() )
    {
        xChild->setParent( xRootFolder );
        xNamed->setName( aName );
        xSink->setInputStream( xInput );
    }
}

sal_Bool PlaceWareExporter::doExport( Reference< XComponent > xDoc, Reference < XOutputStream > xOutputStream, const rtl::OUString& rURL, Reference < XInterface > xHandler )
{
    mxGraphicExporter = Reference< XExporter >::query( mxMSF->createInstance( OUString( RTL_CONSTASCII_USTRINGPARAM("com.sun.star.drawing.GraphicExportFilter") ) ) );

    Reference< XDrawPagesSupplier > xDrawPagesSupplier(xDoc, UNO_QUERY);
    if(!xDrawPagesSupplier.is())
        return sal_False;

    Reference< XIndexAccess > xDrawPages( xDrawPagesSupplier->getDrawPages(), UNO_QUERY );
    if(!xDrawPages.is())
        return sal_False;

    Reference< XDrawPage > xDrawPage;

/*
    utl::TempFile aFile;
    aFile.EnableKillingFile();
*/
    SvFileStream aFile( OUString( RTL_CONSTASCII_USTRINGPARAM("file:///e:/test.zip") ), STREAM_TRUNC|STREAM_WRITE|STREAM_READ );
    
    vector< PageEntry* > aPageEntries;

    // Create new package...
    try
    {
        Reference< XInputStream > xInput;

//		OUString aURL( aFile.GetURL() );
        OUString aURL( RTL_CONSTASCII_USTRINGPARAM("file:///e:/test.zip") );
        Sequence< Any > aArguments( 1 );
        aArguments[ 0 ] <<= aURL;

        Reference< XHierarchicalNameAccess > xIfc(
            mxMSF->createInstanceWithArguments(
                rtl::OUString::createFromAscii(
                                "com.sun.star.packages.comp.ZipPackage" ),
                aArguments ), UNO_QUERY );

        Reference< XSingleServiceFactory > xFactory( xIfc, UNO_QUERY );
        Reference< XPropertySet > xZipProperties( xFactory, UNO_QUERY );

        if ( xZipProperties.is() )
        {
            try
            {
                xZipProperties->setPropertyValue( OUString( RTL_CONSTASCII_USTRINGPARAM("UseManifest") ), makeAny( (sal_Bool)sal_False ) );
            }
            catch( Exception& )
            {
            }

            // get root zip folder
            Reference< XInterface > xRootFolder;
            OUString szRootFolder( RTL_CONSTASCII_USTRINGPARAM("/") );
            xIfc->getByHierarchicalName( szRootFolder ) >>= xRootFolder;

            // export pages
            const sal_Int32 nPageCount = xDrawPages->getCount();
            sal_Int32 nPage;
            for( nPage = 0; nPage < nPageCount; nPage++)
            {
                xDrawPages->getByIndex(nPage) >>= xDrawPage;

                if( !xDrawPage.is() )
                    continue;

                PageEntry* pEntry = exportPage( xDrawPage );
                aPageEntries.push_back( pEntry );

                OUString aName( RTL_CONSTASCII_USTRINGPARAM("i") );
                aName += OUString::valueOf( nPage );
                aName += OUString( RTL_CONSTASCII_USTRINGPARAM(".gif") );
                pEntry->setURL( aName );
                xInput = new utl::OSeekableInputStreamWrapper( new SvFileStream(pEntry->getTempURL(), STREAM_READ ), true );

                addFile( xRootFolder, xFactory, xInput, aName );
            }

            ByteString aInfo;

            const sal_Char* pNewLine = "\r\n";
            OUString aTemp;

//
            Reference< XDocumentInfoSupplier > xInfoSup( xDoc, UNO_QUERY );
            Reference< XPropertySet > xDocInfo( xInfoSup->getDocumentInfo(), UNO_QUERY );

            xDocInfo->getPropertyValue(OUString(RTL_CONSTASCII_USTRINGPARAM("Title"))) >>= aTemp;
            if( 0 == aTemp.getLength() )
            {
                sal_Int32 nPos1 = rURL.lastIndexOf( (sal_Unicode)'/' );
                if( -1 != nPos1 )
                {
                    sal_Int32 nPos2 = rURL.lastIndexOf( (sal_Unicode)'.' );
                    if( nPos2 > nPos1 )
                    {
                        aTemp = rURL.copy( nPos1 + 1, nPos2 - nPos1 - 1 );
                    }
                    else
                    {
                        aTemp = rURL.copy( nPos1 + 1 );
                    }
                }
                else
                {
                    aTemp = rURL;
                }
            }

            aInfo.Append( "SlideSetName: " );
            aInfo.Append( ByteString( aTemp.getStr() , RTL_TEXTENCODING_UTF8 ) );
            aInfo.Append( pNewLine );

            xDocInfo->getPropertyValue(OUString(RTL_CONSTASCII_USTRINGPARAM("Author"))) >>= aTemp;

            aInfo.Append( "PresenterName: " );
            aInfo.Append( ByteString( aTemp.getStr() , RTL_TEXTENCODING_UTF8 ) );
            aInfo.Append( pNewLine );

            vector< PageEntry* >::iterator aIter = aPageEntries.begin();
            vector< PageEntry* >::iterator aEnd = aPageEntries.end();
            while( aIter != aEnd )
            {
                PageEntry* pEntry = (*aIter++);

                aInfo.Append( "slide: " );

                {
                    UniString aTemp( pEntry->getName() );
                    aInfo.Append( ByteString( aTemp , RTL_TEXTENCODING_UTF8 ) );
                    aInfo.Append( pNewLine );
                }

                aInfo.Append( "type: gif");
                aInfo.Append( pNewLine );

                {
                    UniString aTemp( pEntry->getURL() );
                    aInfo.Append( "url: " );
                    aInfo.Append( ByteString( aTemp, RTL_TEXTENCODING_UTF8 ) );
                    aInfo.Append( pNewLine );
                }
                if( pEntry->getTitle().getLength() )
                {
                    aInfo.Append( "text: " );
                    aInfo.Append( ByteString( UniString( pEntry->getTitle() ), RTL_TEXTENCODING_UTF8 ) );
                    aInfo.Append( pNewLine );
                }

                if( pEntry->getNotes().getLength() )
                {
                    aInfo.Append( "notes: " );
                    aInfo.Append( ByteString( UniString( pEntry->getNotes() ), RTL_TEXTENCODING_UTF8 ) );
                    aInfo.Append( pNewLine );
                }
            }

            utl::TempFile aInfoFile;
            aInfoFile.EnableKillingFile();

            SvStream* pInfoFileStream = aInfoFile.GetStream( STREAM_WRITE );

            pInfoFileStream->Write( aInfo.GetBuffer(), aInfo.Len() );

            xInput = new utl::OSeekableInputStreamWrapper( pInfoFileStream );

            OUString aName( RTL_CONSTASCII_USTRINGPARAM("slides.txt") );
            addFile( xRootFolder, xFactory, xInput, aName );

            Reference< XChangesBatch > xBatch( xIfc, UNO_QUERY );
            if( xBatch.is() )
                xBatch->commitChanges();

//			xInput = new utl::OSeekableInputStreamWrapper( aFile.GetStream( STREAM_READ ) );
            xInput = new utl::OSeekableInputStreamWrapper( aFile );

            const sal_Int32 nLen = xInput->available();
            Sequence< sal_Int8 > aSeq( nLen );
            xInput->readBytes( aSeq, nLen );

            rtl::OUStringBuffer aStrBuffer;
            Base64Codec::encodeBase64( aStrBuffer, aSeq );

            sal_Int32 nCount = aStrBuffer.getLength();
            aSeq.realloc( nCount );
            sal_Int8* pBytes = aSeq.getArray();
            const sal_Unicode* pUnicode = aStrBuffer.getStr();

            while( nCount-- )
            {
                *pBytes++ = (sal_Int8)(*pUnicode++);
            }

            xOutputStream->writeBytes( aSeq );
        }
    }
    catch ( RuntimeException const & )
    {
        return sal_False;
    }
    catch ( Exception const & )
    {
        return sal_False;
    }


    return sal_True;
}

// -----------------------------------------------------------------------------

PageEntry* PlaceWareExporter::exportPage( Reference< XDrawPage >&xDrawPage )
{
    Reference< XComponent > xComp( xDrawPage, UNO_QUERY );

    PageEntry* pEntry = new PageEntry();

    // get page name
    Reference< XNamed > xNamed( xDrawPage, UNO_QUERY );
    if( xNamed.is() )
        pEntry->setName( xNamed->getName() );

    // get title text from title presentation shape if available
    const OUString szTitleTextShape( RTL_CONSTASCII_USTRINGPARAM("com.sun.star.presentation.TitleTextShape") );
    const OUString szIsEmptyPresObj( RTL_CONSTASCII_USTRINGPARAM("IsEmptyPresentationObject") );

    const sal_Int32 nShapeCount = xDrawPage->getCount();
    sal_Int32 nShape;
    for( nShape = 0; nShape < nShapeCount; nShape++ )
    {
        Reference< XShape > xShape;
        xDrawPage->getByIndex( nShape ) >>= xShape;

        if( xShape.is() && xShape->getShapeType() == szTitleTextShape )
        {
            Reference< XPropertySet > xPropSet( xShape, UNO_QUERY );
            if( xPropSet.is() )
            {
                sal_Bool bIsEmpty = true;
                xPropSet->getPropertyValue( szIsEmptyPresObj ) >>= bIsEmpty;

                if( !bIsEmpty )
                {
                    Reference< XText > xText( xShape, UNO_QUERY );
                    if( xText.is() )
                    {
                        pEntry->setTitle( xText->getString() );
                    }
                }
            }
            break;
        }
    }

    // create the gif
    Reference< XFilter > xFilter( mxGraphicExporter, UNO_QUERY );

    Sequence< PropertyValue > aFilterData( 2 );
    aFilterData[0].Name = OUString( RTL_CONSTASCII_USTRINGPARAM("Width") );
    aFilterData[0].Value <<= (sal_Int32)704;
    aFilterData[1].Name = OUString( RTL_CONSTASCII_USTRINGPARAM("Translucent") );
    aFilterData[1].Value <<= (sal_Bool)sal_False;

    Sequence< PropertyValue > aDescriptor( 3 );
    aDescriptor[0].Name = OUString( RTL_CONSTASCII_USTRINGPARAM("FilterName") );
    aDescriptor[0].Value <<= OUString( RTL_CONSTASCII_USTRINGPARAM("GIF") );
    aDescriptor[1].Name = OUString( RTL_CONSTASCII_USTRINGPARAM("URL") );
    aDescriptor[1].Value <<= OUString( pEntry->getTempURL() );
    aDescriptor[2].Name = OUString( RTL_CONSTASCII_USTRINGPARAM("FilterData") );
    aDescriptor[2].Value <<= aFilterData;
    mxGraphicExporter->setSourceDocument( xComp );
    xFilter->filter( aDescriptor );

    return pEntry;
}
