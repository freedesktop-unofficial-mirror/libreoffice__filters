/*************************************************************************
 *
 *  $RCSfile: svx_xmlxtimp.cxx,v $
 *
 *  $Revision: 1.2 $
 *
 *  last change: $Author: mwu $ $Date: 2003-11-06 07:47:34 $
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

#ifndef _TOOLS_DEBUG_HXX
#include <tools/debug.hxx>
#endif

#ifndef _COM_SUN_STAR_DOCUMENT_XGRAPHICOBJECTRESOLVER_HPP_
#include <com/sun/star/document/XGraphicObjectResolver.hpp>
#endif

#ifndef _COM_SUN_STAR_IO_XACTIVEDATACONTROL_HPP_
#include <com/sun/star/io/XActiveDataControl.hpp>
#endif
#ifndef _COM_SUN_STAR_IO_XACTIVEDATASOURCE_HPP_
#include <com/sun/star/io/XActiveDataSource.hpp>
#endif
#ifndef _COM_SUN_STAR_XML_SAX_XPARSER_HPP_
#include <com/sun/star/xml/sax/XParser.hpp>
#endif
#ifndef _COM_SUN_STAR_CONTAINER_XNAMECONTAINER_HPP_
#include <com/sun/star/container/XNameContainer.hpp>
#endif
#ifndef _COM_SUN_STAR_XML_SAX_XDOCUMENTHANDLER_HPP_
#include <com/sun/star/xml/sax/XDocumentHandler.hpp>
#endif
#ifndef _COM_SUN_STAR_UNO_SEQUENCE_HXX_
#include <com/sun/star/uno/Sequence.hxx>
#endif
#ifndef _COM_SUN_STAR_DRAWING_POLYPOLYGONBEZIERCOORDS_HPP_
#include <com/sun/star/drawing/PolyPolygonBezierCoords.hpp>
#endif
#ifndef _COM_SUN_STAR_DRAWING_LINEDASH_HPP_
#include <com/sun/star/drawing/LineDash.hpp>
#endif
#ifndef _COM_SUN_STAR_AWT_GRADIENT_HPP_
#include <com/sun/star/awt/Gradient.hpp>
#endif
#ifndef _COM_SUN_STAR_DRAWING_HATCH_HPP_
#include <com/sun/star/drawing/Hatch.hpp>
#endif
#ifndef _COM_SUN_STAR_IO_XOUTPUTSTREAM_HPP_
#include <com/sun/star/io/XOutputStream.hpp>
#endif
#ifndef _COM_SUN_STAR_IO_XSEEKABLE_HDL_
#include <com/sun/star/io/XSeekable.hdl>
#endif
#ifndef _COMPHELPER_PROCESSFACTORY_HXX_
#include <comphelper/processfactory.hxx>
#endif

#ifndef _UTL_STREAM_WRAPPER_HXX_
#include <unotools/streamwrap.hxx>
#endif

#ifndef _RTL_USTRBUF_HXX_
#include <rtl/ustrbuf.hxx>
#endif

#ifndef _SVSTOR_HXX
#include <so3/svstor.hxx>
#endif

#ifndef _SFXDOCFILE_HXX
#include <bf_sfx2/docfile.hxx>
#endif

#ifndef _XMLOFF_XMLUCONV_HXX
#include <xmloff/xmluconv.hxx>
#endif

#ifndef _XMLOFF_XMLNMSPE_HXX
#include "xmloff/xmlnmspe.hxx"
#endif

#ifndef _XMLOFF_NMSPMAP_HXX
#include "xmloff/nmspmap.hxx"
#endif

#ifndef _XMLOFF_XMLKYWD_HXX
#include "xmloff/xmlkywd.hxx"
#endif

#ifndef _XMLOFF_XMLMETAE_HXX
#include "xmloff/xmlmetae.hxx"
#endif

#ifndef _XMLOFF_DASHSTYLE_HXX
#include "xmloff/DashStyle.hxx"
#endif

#ifndef _XMLOFF_GRADIENTSTYLE_HXX
#include "xmloff/GradientStyle.hxx"
#endif

#ifndef _XMLOFF_HATCHSTYLE_HXX
#include "xmloff/HatchStyle.hxx"
#endif

#ifndef _XMLOFF_IMAGESTYLE_HXX
#include "xmloff/ImageStyle.hxx"
#endif

#ifndef _XMLOFF_MARKERSTYLE_HXX
#include "xmloff/MarkerStyle.hxx"
#endif

#ifndef _XMLOFF_XMLICTXT_HXX
#include <xmloff/xmlictxt.hxx>
#endif

#ifndef _XMLGRHLP_HXX
#include "xmlgrhlp.hxx"
#endif

#include "xmlxtimp.hxx"
#ifndef _LEGACYBINFILTERMGR_HXX
#include <legacysmgr/legacy_binfilters_smgr.hxx>	//STRIP002 
#endif
namespace binfilter {
using namespace ::com::sun::star;
using namespace ::com::sun::star::container;
using namespace ::com::sun::star::document;
using namespace ::com::sun::star::uno;
using namespace ::com::sun::star::awt;
using namespace ::com::sun::star::lang;
using namespace ::com::sun::star::xml::sax;
using namespace ::rtl;
using namespace cppu;

///////////////////////////////////////////////////////////////////////

enum SvxXMLTableImportContextEnum { stice_unknown, stice_color, stice_marker, stice_dash, stice_hatch, stice_gradient, stice_bitmap };

///////////////////////////////////////////////////////////////////////

class SvxXMLTableImportContext : public SvXMLImportContext
{
public:
    SvxXMLTableImportContext( SvXMLImport& rImport, USHORT nPrfx, const OUString& rLName, const Reference< XAttributeList >& xAttrList, SvxXMLTableImportContextEnum eContext, const Reference< XNameContainer >& xTable );
    virtual ~SvxXMLTableImportContext();

    virtual SvXMLImportContext *CreateChildContext( USHORT nPrefix, const OUString& rLocalName, const Reference< XAttributeList >& xAttrList );

    SvxXMLXTableImport& getImport() const { return *(SvxXMLXTableImport*)&GetImport(); }

protected:
    void importColor( USHORT nPrfx, const OUString& rLocalName, const Reference< XAttributeList >& xAttrList, Any& rAny, OUString& rName );
    void importMarker( USHORT nPrfx, const OUString& rLocalName, const Reference< XAttributeList >& xAttrList, Any& rAny, OUString& rName );
    void importDash( USHORT nPrfx, const OUString& rLocalName, const Reference< XAttributeList >& xAttrList, Any& rAny, OUString& rName );
    void importHatch( USHORT nPrfx, const OUString& rLocalName, const Reference< XAttributeList >& xAttrList, Any& rAny, OUString& rName );
    void importGradient( USHORT nPrfx, const OUString& rLocalName, const Reference< XAttributeList >& xAttrList, Any& rAny, OUString& rName );
    void importBitmap( USHORT nPrfx, const OUString& rLocalName, const Reference< XAttributeList >& xAttrList, Any& rAny, OUString& rName );

private:
    Reference< XNameContainer > mxTable;
    SvxXMLTableImportContextEnum meContext;
};

///////////////////////////////////////////////////////////////////////

/*N*/ SvxXMLTableImportContext::SvxXMLTableImportContext( SvXMLImport& rImport, USHORT nPrfx, const OUString& rLName, const Reference< XAttributeList >& xAttrList, SvxXMLTableImportContextEnum eContext, const Reference< XNameContainer >& xTable )
/*N*/ : SvXMLImportContext( rImport, nPrfx, rLName ), meContext( eContext ), mxTable( xTable )
/*N*/ {
/*N*/ }

/*N*/ SvxXMLTableImportContext::~SvxXMLTableImportContext()
/*N*/ {
/*N*/ }

/*N*/ SvXMLImportContext *SvxXMLTableImportContext::CreateChildContext( USHORT nPrefix, const OUString& rLocalName, const Reference< XAttributeList >& xAttrList )
/*N*/ {
/*N*/ 	if( XML_NAMESPACE_DRAW == nPrefix )
/*N*/ 	{
/*N*/ 		try
/*N*/ 		{
/*N*/ 			Any aAny;
/*N*/ 			OUString aName;
/*N*/ 
/*N*/ 			switch( meContext )
/*N*/ 			{
/*N*/ 			case stice_color:
/*N*/ 				importColor( nPrefix, rLocalName, xAttrList, aAny, aName );
/*N*/ 				break;
/*N*/ 			case stice_marker:
/*N*/ 				importMarker( nPrefix, rLocalName, xAttrList, aAny, aName  );
/*N*/ 				break;
/*N*/ 			case stice_dash:
/*N*/ 				importDash( nPrefix, rLocalName, xAttrList, aAny, aName  );
/*N*/ 				break;
/*N*/ 			case stice_hatch:
/*N*/ 				importHatch( nPrefix, rLocalName, xAttrList, aAny, aName  );
/*N*/ 				break;
/*N*/ 			case stice_gradient:
/*N*/ 				importGradient( nPrefix, rLocalName, xAttrList, aAny, aName  );
/*N*/ 				break;
/*N*/ 			case stice_bitmap:
/*N*/ 				importBitmap( nPrefix, rLocalName, xAttrList, aAny, aName  );
/*N*/ 				break;
/*N*/ 			}
/*N*/ 
/*N*/ 			if( aName.getLength() && aAny.hasValue() )
/*N*/ 			{
/*N*/ 				if( mxTable->hasByName( aName ) )
/*N*/ 				{
/*?*/ 					mxTable->replaceByName( aName, aAny );
/*N*/ 				}
/*N*/ 				else
/*N*/ 				{
/*N*/ 					mxTable->insertByName( aName, aAny );
/*N*/ 				}
/*N*/ 			}
/*N*/ 		}
/*N*/ 		catch( uno::Exception& e )
/*N*/ 		{
/*N*/ 		}
/*N*/ 	}
/*N*/ 
/*N*/ 	return new SvXMLImportContext( GetImport(), nPrefix, rLocalName );
/*N*/ }

/*N*/ void SvxXMLTableImportContext::importColor( USHORT nPrfx, const OUString& rLocalName, const Reference< XAttributeList >& xAttrList, Any& rAny, OUString& rName )
/*N*/ {
/*N*/ 	const sal_Int16 nAttrCount = xAttrList.is() ? xAttrList->getLength() : 0;
/*N*/ 	for( sal_Int16 i=0; i < nAttrCount; i++ )
/*N*/ 	{
/*N*/ 		const OUString& rFullAttrName = xAttrList->getNameByIndex( i );
/*N*/ 		OUString aLocalName;
/*N*/ 		sal_uInt16 nPrefix = GetImport().GetNamespaceMap().GetKeyByAttrName( rFullAttrName, &aLocalName );
/*N*/ 
/*N*/ 
/*N*/ 		if( XML_NAMESPACE_DRAW == nPrefix )
/*N*/ 		{
/*N*/ 			if( aLocalName.equalsAsciiL( RTL_CONSTASCII_STRINGPARAM( sXML_name ) ) )
/*N*/ 			{
/*N*/ 				rName = xAttrList->getValueByIndex( i );
/*N*/ 			}
/*N*/ 			else if( aLocalName.equalsAsciiL( RTL_CONSTASCII_STRINGPARAM( sXML_color ) ) )
/*N*/ 			{
/*N*/ 				Color aColor;
/*N*/ 				SvXMLUnitConverter::convertColor(aColor, xAttrList->getValueByIndex( i ));
/*N*/ 				rAny <<= (sal_Int32)aColor.GetColor();
/*N*/ 			}
/*N*/ 		}
/*N*/ 	}
/*N*/ }

/*N*/ void SvxXMLTableImportContext::importMarker( USHORT nPrfx, const OUString& rLocalName, const Reference< XAttributeList >& xAttrList, Any& rAny, OUString& rName )
/*N*/ {
/*N*/ 	XMLMarkerStyleImport aMarkerStyle( GetImport() );
/*N*/ 	aMarkerStyle.importXML( xAttrList, rAny, rName );
/*N*/ }

/*N*/ void SvxXMLTableImportContext::importDash( USHORT nPrfx, const OUString& rLocalName, const Reference< XAttributeList >& xAttrList, Any& rAny, OUString& rName )
/*N*/ {
/*N*/ 	XMLDashStyleImport aDashStyle( GetImport() );
/*N*/ 	aDashStyle.importXML( xAttrList, rAny, rName );
/*N*/ }

/*N*/ void SvxXMLTableImportContext::importHatch( USHORT nPrfx, const OUString& rLocalName, const Reference< XAttributeList >& xAttrList, Any& rAny, OUString& rName )
/*N*/ {
/*N*/ 	XMLHatchStyleImport aHatchStyle( GetImport() );
/*N*/ 	aHatchStyle.importXML( xAttrList, rAny, rName );
/*N*/ }

/*N*/ void SvxXMLTableImportContext::importGradient( USHORT nPrfx, const OUString& rLocalName, const Reference< XAttributeList >& xAttrList, Any& rAny, OUString& rName )
/*N*/ {
/*N*/ 	XMLGradientStyleImport aGradientStyle( GetImport() );
/*N*/ 	aGradientStyle.importXML( xAttrList, rAny, rName );
/*N*/ }

/*N*/ void SvxXMLTableImportContext::importBitmap( USHORT nPrfx, const OUString& rLocalName, const Reference< XAttributeList >& xAttrList, Any& rAny, OUString& rName )
/*N*/ {
/*N*/ 	XMLImageStyle aImageStyle;
/*N*/ 	aImageStyle.importXML( xAttrList, rAny, rName, GetImport() );
/*N*/ }

///////////////////////////////////////////////////////////////////////

/*N*/ // #110680#
/*N*/ SvxXMLXTableImport::SvxXMLXTableImport( 
/*N*/ 	const ::com::sun::star::uno::Reference< ::com::sun::star::lang::XMultiServiceFactory > xServiceFactory,
/*N*/ 	const Reference< XNameContainer > & rTable, 
/*N*/ 	Reference< XGraphicObjectResolver >& xGrfResolver )
/*N*/ :	SvXMLImport(xServiceFactory),
/*N*/ 	mrTable( rTable )
/*N*/ {
/*N*/ 	SetGraphicResolver( xGrfResolver );
/*N*/ }

/*N*/ SvxXMLXTableImport::~SvxXMLXTableImport() throw ()
/*N*/ {
/*N*/ }

/*N*/ sal_Bool SvxXMLXTableImport::load( const OUString& rUrl, const Reference< XNameContainer >& xTable ) throw()
/*N*/ {
/*N*/ 	sal_Bool bRet = sal_True;
/*N*/ 
/*N*/ 	Reference< XGraphicObjectResolver >	xGrfResolver;
/*N*/ 	SvXMLGraphicHelper*	pGraphicHelper = 0;
/*N*/ 
/*N*/ 	try
/*N*/ 	{
/*N*/ 		do
/*N*/ 		{
/*N*/ 			SfxMedium aMedium( rUrl, STREAM_READ | STREAM_NOCREATE, TRUE );
/*N*/ 
/*N*/ 			uno::Reference<lang::XMultiServiceFactory> xServiceFactory( ::legacy_binfilters::getLegacyProcessServiceFactory() );
/*N*/ 			if( !xServiceFactory.is() )
/*N*/ 			{
/*N*/ 				DBG_ERROR( "SvxXMLXTableImport::load: got no service manager" );
/*N*/ 				break;
/*N*/ 			}
/*N*/ 
/*N*/ 			uno::Reference< xml::sax::XParser > xParser( xServiceFactory->createInstance( OUString( RTL_CONSTASCII_USTRINGPARAM( "com.sun.star.xml.sax.Parser" ) ) ), uno::UNO_QUERY );
/*N*/ 			if( !xParser.is() )
/*N*/ 			{
/*N*/ 				DBG_ERROR( "com.sun.star.xml.sax.Parser service missing" );
/*N*/ 				break;
/*N*/ 			}
/*N*/ 
/*N*/ 			SvStorageStreamRef						xIStm;
/*N*/ 			uno::Reference< io::XActiveDataSource > xSource;
/*N*/ 
/*N*/ 			SvStorage*								pStorage = aMedium.GetStorage();
/*N*/ 
/*N*/ 			xml::sax::InputSource					aParserInput;
/*N*/ 			aParserInput.sSystemId = aMedium.GetName();
/*N*/ 
/*N*/ 			if( pStorage )
/*N*/ 			{
/*N*/ 				const String aContentStmName( RTL_CONSTASCII_USTRINGPARAM( "Content.xml" ) );
/*N*/ 
/*N*/ 				xIStm = pStorage->OpenStream( aContentStmName, STREAM_READ | STREAM_NOCREATE );
/*N*/ 				if( !xIStm.Is() )
/*N*/ 				{
/*N*/ 					DBG_ERROR( "could not open Content stream" );
/*N*/ 					break;
/*N*/ 				}
/*N*/ 
/*N*/ 				xIStm->SetBufferSize( 16 * 1024 );
/*N*/ 				aParserInput.aInputStream = new ::utl::OInputStreamWrapper( *xIStm );
/*N*/ 
/*N*/ 				pGraphicHelper = SvXMLGraphicHelper::Create( *pStorage, GRAPHICHELPER_MODE_READ );
/*N*/ 				xGrfResolver = pGraphicHelper;
/*N*/ 			}
/*N*/ 			else
/*N*/ 			{
/*N*/                 aParserInput.aInputStream = aMedium.GetInputStream();
/*N*/ 				Reference< io::XSeekable > xSeek( aParserInput.aInputStream, UNO_QUERY );
/*N*/ 				if ( xSeek.is() )
/*N*/ 					xSeek->seek( 0 );
/*N*/ 			}
/*N*/ 
/*N*/ 			if( xSource.is() )
/*N*/ 			{
/*?*/ 				Reference< io::XActiveDataControl > xSourceControl( xSource, UNO_QUERY );
/*?*/ 				xSourceControl->start();
/*N*/ 			}
/*N*/ 
/*N*/ 			// #110680#
/*N*/ 			// Reference< XDocumentHandler > xHandler( new SvxXMLXTableImport( xTable, xGrfResolver ) );
/*N*/ 			Reference< XDocumentHandler > xHandler( new SvxXMLXTableImport( xServiceFactory, xTable, xGrfResolver ) );
/*N*/ 
/*N*/ 			xParser->setDocumentHandler( xHandler );
/*N*/ 			xParser->parseStream( aParserInput );
/*N*/ 		}
/*N*/ 		while(0);
/*N*/ 
/*N*/ 		if( pGraphicHelper )
/*N*/ 			SvXMLGraphicHelper::Destroy( pGraphicHelper );
/*N*/ 	}
/*N*/ 	catch( uno::Exception& e )
/*N*/ 	{
/*N*/ 		bRet = sal_False;
/*N*/ 	}
/*N*/ 
/*N*/ 	return bRet;
/*N*/ }

/*N*/ SvXMLImportContext *SvxXMLXTableImport::CreateContext( sal_uInt16 nPrefix, const OUString& rLocalName, const Reference< XAttributeList >& xAttrList )
/*N*/ {
/*N*/ 	if( XML_NAMESPACE_OFFICE == nPrefix )
/*N*/ 	{
/*N*/ 		Type aType = mrTable->getElementType();
/*N*/ 
/*N*/ 		if( rLocalName.equalsAsciiL( RTL_CONSTASCII_STRINGPARAM( "color-table" ) ) )
/*N*/ 		{
/*N*/ 			if( aType == ::getCppuType((const sal_Int32*)0) )
/*N*/ 				return new SvxXMLTableImportContext( *this, nPrefix, rLocalName, xAttrList, stice_color, mrTable );
/*N*/ 		}
/*N*/ 		else if( rLocalName.equalsAsciiL( RTL_CONSTASCII_STRINGPARAM( "marker-table" ) ) )
/*N*/ 		{
/*N*/ 			if( aType == ::getCppuType((const drawing::PolyPolygonBezierCoords*)0) )
/*N*/ 				return new SvxXMLTableImportContext( *this, nPrefix, rLocalName, xAttrList, stice_marker, mrTable );
/*N*/ 		}
/*N*/ 		else if( rLocalName.equalsAsciiL( RTL_CONSTASCII_STRINGPARAM( "dash-table" ) ) )
/*N*/ 		{
/*N*/ 			if( aType == ::getCppuType((const drawing::LineDash*)0) )
/*N*/ 				return new SvxXMLTableImportContext( *this, nPrefix, rLocalName, xAttrList, stice_dash, mrTable );
/*N*/ 		}
/*N*/ 		else if( rLocalName.equalsAsciiL( RTL_CONSTASCII_STRINGPARAM( "hatch-table" ) ) )
/*N*/ 		{
/*N*/ 			if( aType == ::getCppuType((const drawing::Hatch*)0) )
/*N*/ 				return new SvxXMLTableImportContext( *this, nPrefix, rLocalName, xAttrList, stice_hatch, mrTable );
/*N*/ 		}
/*N*/ 		else if( rLocalName.equalsAsciiL( RTL_CONSTASCII_STRINGPARAM( "gradient-table" ) ) )
/*N*/ 		{
/*N*/ 			if( aType == ::getCppuType((const awt::Gradient*)0))
/*N*/ 				return new SvxXMLTableImportContext( *this, nPrefix, rLocalName, xAttrList, stice_gradient, mrTable );
/*N*/ 		}
/*N*/ 		else if( rLocalName.equalsAsciiL( RTL_CONSTASCII_STRINGPARAM( "bitmap-table" ) ) )
/*N*/ 		{
/*N*/ 			if( aType == ::getCppuType((const OUString*)0))
/*N*/ 				return new SvxXMLTableImportContext( *this, nPrefix, rLocalName, xAttrList, stice_bitmap, mrTable );
/*N*/ 		}
/*N*/ 	}
/*N*/ 
/*?*/ 	return new SvXMLImportContext( *this, nPrefix, rLocalName );
/*N*/ }

}
