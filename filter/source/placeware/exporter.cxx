/*************************************************************************
 *
 *  $RCSfile: exporter.cxx,v $
 *
 *  $Revision: 1.9 $
 *
 *  last change: $Author: rt $ $Date: 2004-08-20 12:20:16 $
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

#ifndef _COM_SUN_STAR_CONTAINER_XNAMED_HPP_
#include <com/sun/star/container/XNamed.hpp>
#endif
#ifndef _COM_SUN_STAR_BEANS_PROPERTYVALUE_HPP_
#include <com/sun/star/beans/PropertyValue.hpp>
#endif
#ifndef _COM_SUN_STAR_BEANS_XPROPERTYSET_HPP_
#include <com/sun/star/beans/XPropertySet.hpp>
#endif
#ifndef _COM_SUN_STAR_DRAWING_XDRAWPAGESSUPPLIER_HPP_
#include <com/sun/star/drawing/XDrawPagesSupplier.hpp>
#endif
#ifndef _COM_SUN_STAR_PRESENTATION_PRESENTATIONPAGE_HPP_
#include <com/sun/star/presentation/XPresentationPage.hpp>
#endif
#ifndef _COM_SUN_STAR_CONTAINER_XINDEXACCESS_HPP_
#include <com/sun/star/container/XIndexAccess.hpp>
#endif
#ifndef _COM_SUN_STAR_DOCUMENT_XFILTER_HPP_
#include <com/sun/star/document/XFilter.hpp>
#endif
#ifndef _COM_SUN_STAR_TEXT_XTEXT_HPP_
#include <com/sun/star/text/XText.hpp>
#endif
#ifndef _COM_SUN_STAR_DOCUMENT_XDOCUMENTINFOSUPPLIER_HPP_
#include <com/sun/star/document/XDocumentInfoSupplier.hpp>
#endif
#ifndef _COM_SUN_STAR_FRAME_XMODEL_HPP_
#include <com/sun/star/frame/XModel.hpp>
#endif
#ifndef _COM_SUN_STAR_TASK_XSTATUSINDICATORFACTORY_HPP_
#include <com/sun/star/task/XStatusIndicatorFactory.hpp>
#endif

#ifndef _RTL_USTRBUF_HXX_
#include <rtl/ustrbuf.hxx>
#endif
#ifndef _RTL_STRING_HXX_ 
#include <rtl/string.hxx>
#endif

#ifndef _OSL_DIAGNOSE_H_
#include <osl/diagnose.h>
#endif

#include <vector>

#include "exporter.hxx"
#include "Base64Codec.hxx"
#include "zip.hxx"
#include "tempfile.hxx"

using rtl::OUString;
using rtl::OString;
using namespace ::com::sun::star::uno;
using namespace ::com::sun::star::drawing;
using namespace ::com::sun::star::container;
using namespace ::com::sun::star::document;
using namespace ::com::sun::star::io;
using namespace ::com::sun::star::lang;
using namespace ::com::sun::star::text;
using namespace ::std;

using com::sun::star::beans::PropertyValue;
using com::sun::star::beans::XPropertySet;
using com::sun::star::presentation::XPresentationPage;
using com::sun::star::task::XStatusIndicator;

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
    TempFile maTempFile;
    rtl::OUString maName;
    rtl::OUString maTitle;
    rtl::OUString maNotes;
    rtl::OUString maURL;

public:
    PageEntry();
    ~PageEntry();

    OUString getTempURL() { return maTempFile.getFileURL(); }

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
: maTempFile( TempFile::createTempFileURL() )
{
}

PageEntry::~PageEntry()
{
}


static void encodeFile( osl::File& rSourceFile, Reference< XOutputStream >& xOutputStream ) throw( ::com::sun::star::uno::Exception )
{
    if( xOutputStream.is() )
    {
        sal_uInt64 nTemp;

        osl::File::RC nRC = rSourceFile.setPos( osl_Pos_End, 0  );
        if( osl::File::E_None == nRC )
        {
            nRC = rSourceFile.getPos( nTemp );
            if( osl::File::E_None == nRC )
            {
                nRC = rSourceFile.setPos( osl_Pos_Absolut, 0 );
            }
        }

        sal_Int32 nLen = static_cast<sal_Int32>(nTemp);

        if( osl::File::E_None != nRC )
            throw IOException();

        sal_Int32 nBufferSize = 3*1024;	// !!! buffer size must be a factor of 3 for base64 to work
        Sequence< sal_Int8 > aInBuffer( nBufferSize < nLen ? nBufferSize : nLen );
        void* pInBuffer = aInBuffer.getArray();

        Sequence< sal_Int8 > aOutBuffer;
        sal_Int32 nRead;
        while( nLen )
        {
            sal_uInt64 nTemp;
            nRC = rSourceFile.read( pInBuffer, aInBuffer.getLength(), nTemp );

            if( (nRC != osl::File::E_None) || (0 == nTemp) )
                throw IOException();

            nRead = static_cast<sal_Int32>( nTemp );

            if( nRead < aInBuffer.getLength() )
            {
                aInBuffer.realloc( nRead );
                pInBuffer = aInBuffer.getArray();
            }

            nLen -= nRead;

            rtl::OUStringBuffer aStrBuffer;
            Base64Codec::encodeBase64( aStrBuffer, aInBuffer );

            sal_Int32 nCount = aStrBuffer.getLength();

            if( aOutBuffer.getLength() != nCount )
                aOutBuffer.realloc( nCount );

            sal_Int8* pBytes = aOutBuffer.getArray();
            const sal_Unicode* pUnicode = aStrBuffer.getStr();

            while( nCount-- )
            {
                // since base64 is always ascii, we can cast safely
                *pBytes++ = static_cast<sal_Int8>(*pUnicode++);
            }

            xOutputStream->writeBytes( aOutBuffer );
        }
    }
}

static OString convertString( OUString aInput )
{
    OString aRet( aInput.getStr(), aInput.getLength(), RTL_TEXTENCODING_ASCII_US );
    aRet = aRet.replace( '\r', ' ' );
    aRet = aRet.replace( '\n', ' ' );

    return aRet;
}

static void createSlideFile( Reference< XComponent > xDoc, ZipFile& rZipFile, const rtl::OUString& rURL, vector< PageEntry* >& rPageEntries  ) throw( ::com::sun::star::uno::Exception )
{
    OString aInfo;

    const OString aNewLine( "\r\n" );
    OUString aTemp;

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

    aInfo += OString( "SlideSetName: " );
    aInfo += convertString( aTemp );
    aInfo += aNewLine;

    xDocInfo->getPropertyValue(OUString(RTL_CONSTASCII_USTRINGPARAM("Author"))) >>= aTemp;

    if( aTemp.getLength() )
    {
        aInfo += OString( "PresenterName: " );
        aInfo += convertString( aTemp );
        aInfo += aNewLine;
    }

    vector< PageEntry* >::iterator aIter( rPageEntries.begin() );
    vector< PageEntry* >::iterator aEnd( rPageEntries.end() );
    while( aIter != aEnd )
    {
        PageEntry* pEntry = (*aIter++);

        aInfo += OString( "slide: " );
        if( pEntry->getTitle().getLength() )
        {
            aInfo += convertString( pEntry->getTitle() );
        }
        else
        {
            aInfo += convertString( pEntry->getName() );
        }
        aInfo += aNewLine;

        aInfo += OString( "type: gif");
        aInfo += aNewLine;

        aInfo += OString( "url: " );
        aInfo += convertString( pEntry->getURL() );
        aInfo += aNewLine;


        if( pEntry->getNotes().getLength() )
        {
            aInfo += OString( "notes: " );
            aInfo += convertString( pEntry->getNotes() );
            aInfo += aNewLine;
        }
    }

    TempFile aInfoFile( TempFile::createTempFileURL() );

    osl::File::RC nRC;
    sal_uInt64 nTemp;

    nRC = aInfoFile.open( OpenFlag_Write );
    if( osl::File::E_None == nRC )
    {
        nRC = aInfoFile.write( aInfo.getStr(), aInfo.getLength(), nTemp );
        if( osl::File::E_None == nRC )
        {
            nRC = aInfoFile.setPos( osl_Pos_Absolut, 0 );
            if( osl::File::E_None == nRC )
            {
                nRC = aInfoFile.close();
            }
        }
    }

    if( (osl::File::E_None != nRC) || !rZipFile.addFile( aInfoFile, OString( RTL_CONSTASCII_STRINGPARAM("slides.txt") ) ))
        throw IOException();
}

//#define PLACEWARE_DEBUG 1

sal_Bool PlaceWareExporter::doExport( Reference< XComponent > xDoc, Reference < XOutputStream > xOutputStream,
                                        const rtl::OUString& rURL, Reference < XInterface > xHandler, Reference < XStatusIndicator >& xStatusIndicator )
{
    sal_Bool bRet = sal_False;

    mxGraphicExporter = Reference< XExporter >::query( mxMSF->createInstance( OUString( RTL_CONSTASCII_USTRINGPARAM("com.sun.star.drawing.GraphicExportFilter") ) ) );
    Reference< XDrawPagesSupplier > xDrawPagesSupplier(xDoc, UNO_QUERY);
    if(!xDrawPagesSupplier.is())
        return sal_False;

    Reference< XIndexAccess > xDrawPages( xDrawPagesSupplier->getDrawPages(), UNO_QUERY );
    if(!xDrawPages.is())
        return sal_False;

    if(xStatusIndicator.is())
    {
        xStatusIndicator->start(OUString(  RTL_CONSTASCII_USTRINGPARAM( "PlaceWare:" )),xDrawPages->getCount());
    }

    Reference< XDrawPage > xDrawPage;

    osl::File::RC nRC;

#ifndef PLACEWARE_DEBUG
    TempFile aTempFile( TempFile::createTempFileURL() );
    nRC = aTempFile.open( osl_File_OpenFlag_Write|osl_File_OpenFlag_Read );
    OUString aURL( aTempFile.getFileURL() );
#else
    OUString aURL( RTL_CONSTASCII_USTRINGPARAM("file:///e:/test.zip") );
    osl::File::remove( aURL );
    osl::File aTempFile( aURL );
    nRC = aTempFile.open( osl_File_OpenFlag_Create|osl_File_OpenFlag_Write|osl_File_OpenFlag_Read );
#endif
    
    if( osl::File::E_None != nRC )
        return sal_False;

    vector< PageEntry* > aPageEntries;

    // Create new package...
    try
    {
        ZipFile aZipFile(aTempFile);

        // export slides as gifs and collect information for slides

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

            if(xStatusIndicator.is())
            {
                xStatusIndicator->setValue( nPage + 1 );
            }
        }

        // create the slide.txt file

        createSlideFile( xDoc, aZipFile, rURL, aPageEntries );

        // add gifs to zip
        vector< PageEntry* >::iterator aIter( aPageEntries.begin() );
        vector< PageEntry* >::iterator aEnd( aPageEntries.end() );
        while( aIter != aEnd )
        {
            PageEntry* pEntry = (*aIter++);

            osl::File aFile(pEntry->getTempURL() );
            const OUString aTemp( pEntry->getURL() );

            if( (osl::File::E_None != nRC) || !aZipFile.addFile( aFile, OString( aTemp.getStr(), aTemp.getLength(), RTL_TEXTENCODING_ASCII_US ) ) )
                throw IOException();
        }

        if(!aZipFile.close())
            throw IOException();

        encodeFile( aTempFile, xOutputStream );

        bRet = sal_True;
    }
    catch ( RuntimeException const & )
    {
    }
    catch ( Exception const & )
    {
    }

    vector< PageEntry* >::iterator aIter( aPageEntries.begin() );
    vector< PageEntry* >::iterator aEnd( aPageEntries.end() );
    while( aIter != aEnd )
    {
        delete (*aIter++);
    }

    if( xStatusIndicator.is() )
        xStatusIndicator->end();

    return bRet;
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

    // get notes text if available
    Reference< XPresentationPage > xPresPage( xDrawPage, UNO_QUERY );
    if( xPresPage.is() )
    {
        Reference< XDrawPage > xNotesPage( xPresPage->getNotesPage() );

        const OUString szNotesShape( RTL_CONSTASCII_USTRINGPARAM("com.sun.star.presentation.NotesShape") );

        const sal_Int32 nShapeCount = xNotesPage->getCount();
        sal_Int32 nShape;
        for( nShape = 0; nShape < nShapeCount; nShape++ )
        {
            Reference< XShape > xShape;
            xNotesPage->getByIndex( nShape ) >>= xShape;

            if( xShape.is() && (xShape->getShapeType() == szNotesShape) )
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
                            pEntry->setNotes( xText->getString() );
                        }
                    }
                }
                break;
            }
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
