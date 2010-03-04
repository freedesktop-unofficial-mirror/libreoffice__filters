/*************************************************************************
 *
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER.
 *
 * Copyright 2008 by Sun Microsystems, Inc.
 *
 * OpenOffice.org - a multi-platform office productivity suite
 *
 * $RCSfile: xmlfilterbase.cxx,v $
 * $Revision: 1.5.6.2 $
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

#include "oox/core/xmlfilterbase.hxx"

#include <cstdio>

#include <rtl/strbuf.hxx>
#include <rtl/ustrbuf.hxx>
#include <com/sun/star/container/XNameContainer.hpp>
#include <com/sun/star/embed/XRelationshipAccess.hpp>
#include <com/sun/star/xml/sax/InputSource.hpp>
#include <com/sun/star/xml/sax/XFastParser.hpp>
#include <com/sun/star/document/XDocumentProperties.hpp>
#include <comphelper/mediadescriptor.hxx>
#include <sax/fshelper.hxx>
#include "properties.hxx"
#include "tokens.hxx"
#include "oox/helper/containerhelper.hxx"
#include "oox/helper/propertyset.hxx"
#include "oox/helper/zipstorage.hxx"
#include "oox/core/fasttokenhandler.hxx"
#include "oox/core/filterdetect.hxx"
#include "oox/core/fragmenthandler.hxx"
#include "oox/core/namespaces.hxx"
#include "oox/core/recordparser.hxx"
#include "oox/core/relationshandler.hxx"

using ::rtl::OStringBuffer;
using ::rtl::OUString;
using ::rtl::OUStringBuffer;
using ::com::sun::star::beans::StringPair;
using ::com::sun::star::uno::Reference;
using ::com::sun::star::uno::Sequence;
using ::com::sun::star::uno::Exception;
using ::com::sun::star::uno::RuntimeException;
using ::com::sun::star::uno::UNO_QUERY;
using ::com::sun::star::uno::UNO_QUERY_THROW;
using ::com::sun::star::uno::UNO_SET_THROW;
using ::com::sun::star::lang::Locale;
using ::com::sun::star::lang::XMultiServiceFactory;
using ::com::sun::star::embed::XRelationshipAccess;
using ::com::sun::star::embed::XStorage;
using ::com::sun::star::io::XInputStream;
using ::com::sun::star::io::XOutputStream;
using ::com::sun::star::io::XStream;
using ::com::sun::star::container::XNameContainer;
using ::com::sun::star::xml::sax::XFastParser;
using ::com::sun::star::xml::sax::XFastTokenHandler;
using ::com::sun::star::xml::sax::XFastDocumentHandler;
using ::com::sun::star::xml::sax::InputSource;
using ::com::sun::star::xml::sax::SAXException;
using ::com::sun::star::document::XDocumentProperties;
using ::com::sun::star::util::DateTime;
using ::comphelper::MediaDescriptor;
using ::sax_fastparser::FastSerializerHelper;
using ::sax_fastparser::FSHelperPtr;

namespace oox {
namespace core {

// ============================================================================

struct XmlFilterBaseImpl
{
    typedef RefMap< OUString, Relations > RelationsMap;

    OUString            maBinSuffix;
    Reference< XFastTokenHandler >
                        mxTokenHandler;
    RelationsMap        maRelationsMap;
    TextFieldStack		maTextFieldStack;
    explicit            XmlFilterBaseImpl();
};

// ----------------------------------------------------------------------------

XmlFilterBaseImpl::XmlFilterBaseImpl() :
    maBinSuffix( CREATE_OUSTRING( ".bin" ) ),
    mxTokenHandler( new FastTokenHandler )
{
}

// ============================================================================

XmlFilterBase::XmlFilterBase( const Reference< XMultiServiceFactory >& rxGlobalFactory ) :
    FilterBase( rxGlobalFactory ),
    mxImpl( new XmlFilterBaseImpl ),
    mnRelId( 1 ),
    mnMaxDocId( 0 )
{
}

XmlFilterBase::~XmlFilterBase()
{
}

// ----------------------------------------------------------------------------

OUString XmlFilterBase::getFragmentPathFromFirstType( const OUString& rType )
{
    // importRelations() caches the relations map for subsequence calls
    return importRelations( OUString() )->getFragmentPathFromFirstType( rType );
}

bool XmlFilterBase::importFragment( const ::rtl::Reference< FragmentHandler >& rxHandler )
{
    OSL_ENSURE( rxHandler.is(), "XmlFilterBase::importFragment - missing fragment handler" );
    if( !rxHandler.is() )
        return false;

    // fragment handler must contain path to fragment stream
    OUString aFragmentPath = rxHandler->getFragmentPath();
    OSL_ENSURE( aFragmentPath.getLength() > 0, "XmlFilterBase::importFragment - missing fragment path" );
    if( aFragmentPath.getLength() == 0 )
        return false;

    // try to import binary streams (fragment extension must be '.bin')
    sal_Int32 nBinSuffixPos = aFragmentPath.getLength() - mxImpl->maBinSuffix.getLength();
    if( (nBinSuffixPos >= 0) && aFragmentPath.match( mxImpl->maBinSuffix, nBinSuffixPos ) )
    {
        try
        {
            // try to open the fragment stream (this may fail - do not assert)
            Reference< XInputStream > xInStrm( openInputStream( aFragmentPath ), UNO_SET_THROW );

            // create the record parser
            RecordParser aParser;
            aParser.setFragmentHandler( rxHandler );

            // create the input source and parse the stream
            RecordInputSource aSource;
            aSource.mxInStream.reset( new BinaryXInputStream( xInStrm, true ) );
            aSource.maSystemId = aFragmentPath;
            aParser.parseStream( aSource );
            return true;
        }
        catch( Exception& )
        {
        }
        return false;
    }

    // get the XFastDocumentHandler interface from the fragment handler
    Reference< XFastDocumentHandler > xDocHandler( rxHandler.get() );
    if( !xDocHandler.is() )
        return false;

    // try to import XML stream
    try
    {
        // try to open the fragment stream (this may fail - do not assert)
        Reference< XInputStream > xInStrm( rxHandler->openFragmentStream(), UNO_SET_THROW );

        // create the fast parser
        Reference< XFastParser > xParser( getGlobalFactory()->createInstance(
            CREATE_OUSTRING( "com.sun.star.xml.sax.FastParser" ) ), UNO_QUERY_THROW );
        xParser->setFastDocumentHandler( xDocHandler );
        xParser->setTokenHandler( mxImpl->mxTokenHandler );

        // register XML namespaces
        xParser->registerNamespace( CREATE_OUSTRING( "http://www.w3.org/XML/1998/namespace" ), NMSP_XML );
        xParser->registerNamespace( CREATE_OUSTRING( "http://schemas.openxmlformats.org/package/2006/relationships" ), NMSP_PACKAGE_RELATIONSHIPS );
        xParser->registerNamespace( CREATE_OUSTRING( "http://schemas.openxmlformats.org/officeDocument/2006/relationships" ), NMSP_RELATIONSHIPS );

        xParser->registerNamespace( CREATE_OUSTRING( "http://schemas.openxmlformats.org/drawingml/2006/main" ), NMSP_DRAWINGML );
        xParser->registerNamespace( CREATE_OUSTRING( "http://schemas.openxmlformats.org/drawingml/2006/diagram" ), NMSP_DIAGRAM );
        xParser->registerNamespace( CREATE_OUSTRING( "http://schemas.openxmlformats.org/drawingml/2006/chart" ), NMSP_CHART );

        xParser->registerNamespace( CREATE_OUSTRING( "urn:schemas-microsoft-com:vml" ), NMSP_VML );
        xParser->registerNamespace( CREATE_OUSTRING( "urn:schemas-microsoft-com:office:office" ), NMSP_OFFICE );
        xParser->registerNamespace( CREATE_OUSTRING( "urn:schemas-microsoft-com:office:word" ), NMSP_VML_DOC );
        xParser->registerNamespace( CREATE_OUSTRING( "urn:schemas-microsoft-com:office:excel" ), NMSP_VML_XLS );
        xParser->registerNamespace( CREATE_OUSTRING( "urn:schemas-microsoft-com:office:powerpoint" ), NMSP_VML_PPT );
        xParser->registerNamespace( CREATE_OUSTRING( "http://schemas.microsoft.com/office/2006/activeX" ), NMSP_AX );

        xParser->registerNamespace( CREATE_OUSTRING( "http://schemas.openxmlformats.org/spreadsheetml/2006/main"), NMSP_XLS );
        xParser->registerNamespace( CREATE_OUSTRING( "http://schemas.openxmlformats.org/drawingml/2006/spreadsheetDrawing" ), NMSP_XDR );
        xParser->registerNamespace( CREATE_OUSTRING( "http://schemas.microsoft.com/office/excel/2006/main" ), NMSP_XM );

        xParser->registerNamespace( CREATE_OUSTRING( "http://schemas.openxmlformats.org/presentationml/2006/main"), NMSP_PPT );

        // create the input source and parse the stream
        InputSource aSource;
        aSource.aInputStream = xInStrm;
        aSource.sSystemId = aFragmentPath;
        // own try/catch block for showing parser failure assertion with fragment path
        try
        {
            xParser->parseStream( aSource );
            return true;
        }
        catch( Exception& )
        {
            OSL_ENSURE( false, OStringBuffer( "XmlFilterBase::importFragment - XML parser failed in fragment '" ).
                append( OUStringToOString( aFragmentPath, RTL_TEXTENCODING_ASCII_US ) ).append( '\'' ).getStr() );
        }
    }
    catch( Exception& )
    {
    }
    return false;
}

RelationsRef XmlFilterBase::importRelations( const OUString& rFragmentPath )
{
    // try to find cached relations
    RelationsRef& rxRelations = mxImpl->maRelationsMap[ rFragmentPath ];
    if( !rxRelations )
    {
        // import and cache relations
        rxRelations.reset( new Relations( rFragmentPath ) );
        importFragment( new RelationsFragment( *this, rxRelations ) );
    }
    return rxRelations;
}

Reference< XOutputStream > XmlFilterBase::openFragmentStream( const OUString& rStreamName, const OUString& rMediaType )
{
    Reference< XOutputStream > xOutputStream = openOutputStream( rStreamName );
    PropertySet aPropSet( xOutputStream );
    aPropSet.setProperty( PROP_MediaType, rMediaType );
    return xOutputStream;
}

FSHelperPtr XmlFilterBase::openFragmentStreamWithSerializer( const OUString& rStreamName, const OUString& rMediaType )
{
    return FSHelperPtr( new FastSerializerHelper( openFragmentStream( rStreamName, rMediaType ) ) );
}

TextFieldStack& XmlFilterBase::getTextFieldStack() const
{
    return mxImpl->maTextFieldStack;
}

namespace {

OUString lclAddRelation( const Reference< XRelationshipAccess > xRelations, sal_Int32 nId, const OUString& rType, const OUString& rTarget, bool bExternal )
{
    OUString sId = OUStringBuffer().appendAscii( "rId" ).append( nId ).makeStringAndClear();

    Sequence< StringPair > aEntry( bExternal ? 3 : 2 );
    aEntry[0].First = CREATE_OUSTRING( "Type" );
    aEntry[0].Second = rType;
    aEntry[1].First = CREATE_OUSTRING( "Target" );
    aEntry[1].Second = rTarget;
    if( bExternal )
    {
        aEntry[2].First = CREATE_OUSTRING( "TargetMode" );
        aEntry[2].Second = CREATE_OUSTRING( "External" );
    }
    xRelations->insertRelationshipByID( sId, aEntry, sal_True );

    return sId;
}

} // namespace

OUString XmlFilterBase::addRelation( const OUString& rType, const OUString& rTarget, bool bExternal )
{
    Reference< XRelationshipAccess > xRelations( getStorage()->getXStorage(), UNO_QUERY );
    if( xRelations.is() )
        return lclAddRelation( xRelations, mnRelId ++, rType, rTarget, bExternal );

    return OUString();
}

OUString XmlFilterBase::addRelation( const Reference< XOutputStream > xOutputStream, const OUString& rType, const OUString& rTarget, bool bExternal )
{
    sal_Int32 nId = 0;

    PropertySet aPropSet( xOutputStream );
    if( aPropSet.is() )
        aPropSet.getProperty( nId, PROP_RelId );
    else
        nId = mnRelId++;

    Reference< XRelationshipAccess > xRelations( xOutputStream, UNO_QUERY );
    if( xRelations.is() )
        return lclAddRelation( xRelations, nId, rType, rTarget, bExternal );

    return OUString();
}

static void
writeElement( FSHelperPtr pDoc, sal_Int32 nXmlElement, const OUString& sValue )
{
    if( sValue.getLength() == 0 )
        return;
    pDoc->startElement( nXmlElement, FSEND );
    pDoc->write( sValue );
    pDoc->endElement( nXmlElement );
}

static void
writeElement( FSHelperPtr pDoc, sal_Int32 nXmlElement, const sal_Int32 nValue )
{
    pDoc->startElement( nXmlElement, FSEND );
    pDoc->write( OUString::valueOf( nValue ) );
    pDoc->endElement( nXmlElement );
}

static void
writeElement( FSHelperPtr pDoc, sal_Int32 nXmlElement, const DateTime& rTime )
{
    if( rTime.Year == 0 )
        return;

    if ( ( nXmlElement >> 16 ) != XML_dcterms )
        pDoc->startElement( nXmlElement, FSEND );
    else
        pDoc->startElement( nXmlElement,
                FSNS( XML_xsi, XML_type ), "dcterms:W3CDTF",
                FSEND );

    char pStr[200];
    snprintf( pStr, sizeof( pStr ), "%d-%02d-%02dT%02d:%02d:%02d.%02dZ",
            rTime.Year, rTime.Month, rTime.Day,
            rTime.Hours, rTime.Minutes, rTime.Seconds,
            rTime.HundredthSeconds );

    pDoc->write( pStr );

    pDoc->endElement( nXmlElement );
}

static void
writeElement( FSHelperPtr pDoc, sal_Int32 nXmlElement, Sequence< rtl::OUString > aItems )
{
    if( aItems.getLength() == 0 )
        return;

    OUStringBuffer sRep;
    sRep.append( aItems[ 0 ] );

    for( sal_Int32 i = 1, end = aItems.getLength(); i < end; ++i )
    {
        sRep.appendAscii( " " ).append( aItems[ i ] );
    }

    writeElement( pDoc, nXmlElement, sRep.makeStringAndClear() );
}

static void
writeElement( FSHelperPtr pDoc, sal_Int32 nXmlElement, const Locale& rLocale )
{
    // TODO: what to do with .Country and .Variant
    writeElement( pDoc, nXmlElement, rLocale.Language );
}

static void
writeCoreProperties( XmlFilterBase& rSelf, Reference< XDocumentProperties > xProperties )
{
    rSelf.addRelation(
            CREATE_OUSTRING( "http://schemas.openxmlformats.org/package/2006/relationships/metadata/core-properties" ),
            CREATE_OUSTRING( "docProps/core.xml" ) );
    FSHelperPtr pCoreProps = rSelf.openFragmentStreamWithSerializer(
            CREATE_OUSTRING( "docProps/core.xml" ),
            CREATE_OUSTRING( "application/vnd.openxmlformats-package.core-properties+xml" ) );
    pCoreProps->startElementNS( XML_cp, XML_coreProperties,
            FSNS( XML_xmlns, XML_cp ),          "http://schemas.openxmlformats.org/package/2006/metadata/core-properties",
            FSNS( XML_xmlns, XML_dc ),          "http://purl.org/dc/elements/1.1/",
            FSNS( XML_xmlns, XML_dcterms ),     "http://purl.org/dc/terms/",
            FSNS( XML_xmlns, XML_dcmitype ),    "http://purl.org/dc/dcmitype/",
            FSNS( XML_xmlns, XML_xsi ),         "http://www.w3.org/2001/XMLSchema-instance",
            FSEND );

#if OOXTODO
    writeElement( pCoreProps, FSNS( XML_cp, XML_category ),         "category" );
    writeElement( pCoreProps, FSNS( XML_cp, XML_contentStatus ),    "status" );
    writeElement( pCoreProps, FSNS( XML_cp, XML_contentType ),      "contentType" );
#endif  /* def OOXTODO */
    writeElement( pCoreProps, FSNS( XML_dcterms, XML_created ),     xProperties->getCreationDate() );
    writeElement( pCoreProps, FSNS( XML_dc, XML_creator ),          xProperties->getAuthor() );
    writeElement( pCoreProps, FSNS( XML_dc, XML_description ),      xProperties->getDescription() );
#if OOXTODO
    writeElement( pCoreProps, FSNS( XML_dc, XML_identifier ),       "ident" );
#endif  /* def OOXTODO */
    writeElement( pCoreProps, FSNS( XML_cp, XML_keywords ),         xProperties->getKeywords() );
    writeElement( pCoreProps, FSNS( XML_dc, XML_language ),         xProperties->getLanguage() );
    writeElement( pCoreProps, FSNS( XML_cp, XML_lastModifiedBy ),   xProperties->getModifiedBy() );
    writeElement( pCoreProps, FSNS( XML_cp, XML_lastPrinted ),      xProperties->getPrintDate() );
    writeElement( pCoreProps, FSNS( XML_dcterms, XML_modified ),    xProperties->getModificationDate() );
    writeElement( pCoreProps, FSNS( XML_cp, XML_revision ),         xProperties->getEditingCycles() );
    writeElement( pCoreProps, FSNS( XML_dc, XML_subject ),          xProperties->getSubject() );
    writeElement( pCoreProps, FSNS( XML_dc, XML_title ),            xProperties->getTitle() );
#if OOXTODO
    writeElement( pCoreProps, FSNS( XML_cp, XML_version ),          "version" );
#endif  /* def OOXTODO */

    pCoreProps->endElementNS( XML_cp, XML_coreProperties );
}

static void
writeAppProperties( XmlFilterBase& rSelf, Reference< XDocumentProperties > xProperties )
{
    rSelf.addRelation(
            CREATE_OUSTRING( "http://schemas.openxmlformats.org/officeDocument/2006/relationships/extended-properties" ),
            CREATE_OUSTRING( "docProps/app.xml" ) );
    FSHelperPtr pAppProps = rSelf.openFragmentStreamWithSerializer(
            CREATE_OUSTRING( "docProps/app.xml" ),
            CREATE_OUSTRING( "application/vnd.openxmlformats-officedocument.extended-properties+xml" ) );
    pAppProps->startElement( XML_Properties,
            XML_xmlns,                  "http://schemas.openxmlformats.org/officeDocument/2006/extended-properties",
            FSNS( XML_xmlns, XML_vt ),  "http://schemas.openxmlformats.org/officeDocument/2006/docPropsVTypes",
            FSEND );

    writeElement( pAppProps, XML_Template,              xProperties->getTemplateName() );
#if OOXTODO
    writeElement( pAppProps, XML_Manager,               "manager" );
    writeElement( pAppProps, XML_Company,               "company" );
    writeElement( pAppProps, XML_Pages,                 "pages" );
    writeElement( pAppProps, XML_Words,                 "words" );
    writeElement( pAppProps, XML_Characters,            "characters" );
    writeElement( pAppProps, XML_PresentationFormat,    "presentation format" );
    writeElement( pAppProps, XML_Lines,                 "lines" );
    writeElement( pAppProps, XML_Paragraphs,            "paragraphs" );
    writeElement( pAppProps, XML_Slides,                "slides" );
    writeElement( pAppProps, XML_Notes,                 "notes" );
#endif  /* def OOXTODO */
    writeElement( pAppProps, XML_TotalTime,             xProperties->getEditingDuration() );
#if OOXTODO
    writeElement( pAppProps, XML_HiddenSlides,          "hidden slides" );
    writeElement( pAppProps, XML_MMClips,               "mm clips" );
    writeElement( pAppProps, XML_ScaleCrop,             "scale crop" );
    writeElement( pAppProps, XML_HeadingPairs,          "heading pairs" );
    writeElement( pAppProps, XML_TitlesOfParts,         "titles of parts" );
    writeElement( pAppProps, XML_LinksUpToDate,         "links up-to-date" );
    writeElement( pAppProps, XML_CharactersWithSpaces,  "characters with spaces" );
    writeElement( pAppProps, XML_SharedDoc,             "shared doc" );
    writeElement( pAppProps, XML_HyperlinkBase,         "hyperlink base" );
    writeElement( pAppProps, XML_HLinks,                "hlinks" );
    writeElement( pAppProps, XML_HyperlinksChanged,     "hyperlinks changed" );
    writeElement( pAppProps, XML_DigSig,                "digital signature" );
#endif  /* def OOXTODO */
    writeElement( pAppProps, XML_Application,           xProperties->getGenerator() );
#if OOXTODO
    writeElement( pAppProps, XML_AppVersion,            "app version" );
    writeElement( pAppProps, XML_DocSecurity,           "doc security" );
#endif  /* def OOXTODO */
    pAppProps->endElement( XML_Properties );
}

XmlFilterBase& XmlFilterBase::exportDocumentProperties( Reference< XDocumentProperties > xProperties )
{
    if( xProperties.is() )
    {
        writeCoreProperties( *this, xProperties );
        writeAppProperties( *this, xProperties );
        Sequence< ::com::sun::star::beans::NamedValue > aStats = xProperties->getDocumentStatistics();
        printf( "# Document Statistics:\n" );
        for( sal_Int32 i = 0, end = aStats.getLength(); i < end; ++i )
        {
            ::com::sun::star::uno::Any aValue = aStats[ i ].Value;
            ::rtl::OUString sValue;
            bool bHaveString = aValue >>= sValue;
            printf ("#\t%s=%s [%s]\n",
                    OUStringToOString( aStats[ i ].Name, RTL_TEXTENCODING_UTF8 ).getStr(),
                    bHaveString
                        ? OUStringToOString( sValue, RTL_TEXTENCODING_UTF8 ).getStr()
                        : "<unconvertable>",
                    OUStringToOString( aValue.getValueTypeName(), RTL_TEXTENCODING_UTF8 ).getStr());
        }
    }
    return *this;
}

// protected ------------------------------------------------------------------

Reference< XInputStream > XmlFilterBase::implGetInputStream( MediaDescriptor& rMediaDesc ) const
{
    /*  Get the input stream directly from the media descriptor, or decrypt the
        package again. The latter is needed e.g. when the document is reloaded.
        All this is implemented in the detector service. */
    FilterDetect aDetector( getGlobalFactory() );
    return aDetector.extractUnencryptedPackage( rMediaDesc );
}

// private --------------------------------------------------------------------

StorageRef XmlFilterBase::implCreateStorage( const Reference< XInputStream >& rxInStream ) const
{
    return StorageRef( new ZipStorage( getGlobalFactory(), rxInStream ) );
}

StorageRef XmlFilterBase::implCreateStorage( const Reference< XStream >& rxOutStream ) const
{
    return StorageRef( new ZipStorage( getGlobalFactory(), rxOutStream ) );
}

// ============================================================================

} // namespace core
} // namespace oox

