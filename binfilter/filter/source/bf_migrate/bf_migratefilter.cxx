/*************************************************************************
 *
 *  $RCSfile: bf_migratefilter.cxx,v $
 *
 *  $Revision: 1.6 $
 *
 *  last change: $Author: vg $ $Date: 2005-02-21 16:33:20 $
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
 *  Contributor(s): Martin Gallwey (gallwey@sun.com)
 *
 *
 ************************************************************************/

#ifndef _BF_MIGRATEFILTER_HXX
#include <bf_migratefilter.hxx>
#endif

#ifndef _COM_SUN_STAR_UTIL_XCLOSEABLE_HPP_
#include <com/sun/star/util/XCloseable.hpp>
#endif

// auto strip #ifndef _COM_SUN_STAR_IO_XOUTPUTSTREAM_HPP_
// auto strip #include <com/sun/star/io/XOutputStream.hpp>
// auto strip #endif

// auto strip #ifndef _COM_SUN_STAR_IO_XINPUTSTREAM_HPP_
// auto strip #include <com/sun/star/io/XInputStream.hpp>
// auto strip #endif

#ifndef _COM_SUN_STAR_XML_SAX_XPARSER_HPP_
#include <com/sun/star/xml/sax/XParser.hpp>
#endif

#ifndef _COM_SUN_STAR_FRAME_XSTORABLE_HPP_
#include <com/sun/star/frame/XStorable.hpp>
#endif

#ifndef _COM_SUN_STAR_FRAME_XLOADABLE_HPP_
#include <com/sun/star/frame/XLoadable.hpp>
#endif

#ifndef _COM_SUN_STAR_IO_XSEEKABLE_HPP_
#include <com/sun/star/io/XSeekable.hpp>
#endif

// auto strip #ifndef _UNTOOLS_UCBSTREAMHELPER_HXX
// auto strip #include <unotools/ucbstreamhelper.hxx>
// auto strip #endif

#ifndef _LEGACYBINFILTERMGR_HXX
#include <legacysmgr/legacy_binfilters_smgr.hxx>
#endif

#ifndef _COM_SUN_STAR_TASK_XINTERACTIONHANDLER_HPP_
#include <com/sun/star/task/XInteractionHandler.hpp>
#endif

#ifndef _SFXAPP_HXX
#include <bf_sfx2/app.hxx>
#endif

#ifndef _SFX_FCONTNR_HXX
#include <bf_sfx2/fcontnr.hxx>
#endif

#ifndef _SFX_OBJFAC_HXX
#include <bf_sfx2/docfac.hxx>
#endif

#include <so3/staticbaseurl.hxx>

namespace binfilter {

using namespace rtl;
using namespace com::sun::star::uno;
using namespace com::sun::star::lang;
using namespace com::sun::star::io;
using namespace com::sun::star::beans;
using namespace com::sun::star::document;
using namespace com::sun::star::xml;
using namespace com::sun::star::xml::sax;
using namespace com::sun::star::frame;
using namespace com::sun::star::task;
using namespace com::sun::star::util;

const OUString sServiceNameTextDocument(RTL_CONSTASCII_USTRINGPARAM("com.sun.star.text.TextDocument"));
const OUString sServiceNameGlobalDocument(RTL_CONSTASCII_USTRINGPARAM("com.sun.star.text.GlobalDocument"));
const OUString sServiceNameWebDocument(RTL_CONSTASCII_USTRINGPARAM("com.sun.star.text.WebDocument"));
const OUString sServiceNamePresentationDocument(RTL_CONSTASCII_USTRINGPARAM("com.sun.star.presentation.PresentationDocument"));
const OUString sServiceNameDrawingDocument(RTL_CONSTASCII_USTRINGPARAM("com.sun.star.drawing.DrawingDocument"));
const OUString sServiceNameSpreadsheetDocument(RTL_CONSTASCII_USTRINGPARAM("com.sun.star.sheet.SpreadsheetDocument"));
const OUString sServiceNameChartDocument(RTL_CONSTASCII_USTRINGPARAM("com.sun.star.chart.ChartDocument"));
const OUString sServiceNameFormulaProperties(RTL_CONSTASCII_USTRINGPARAM("com.sun.star.formula.FormulaProperties"));

// try to get a connection to the Stripped office here
sal_Bool bf_MigrateFilter::getContactToLegacyProcessServiceFactory()
    throw (RuntimeException)
{
    sal_Bool bRetval(sal_False);

    if(!mxLegServFact.is())
    {
        mxLegServFact = ::legacy_binfilters::getLegacyProcessServiceFactory();
    }

    if( mxLegServFact.is() )
    {
        bRetval = sal_True;
    }

    return bRetval;
}

sal_Bool bf_MigrateFilter::importImpl(const Sequence< ::com::sun::star::beans::PropertyValue >& aDescriptor)
    throw (RuntimeException)
{
    sal_Int32 nLength(aDescriptor.getLength());
    const PropertyValue* pValue = aDescriptor.getConstArray();

    Reference < XInputStream > xInputStream;
    Reference< XCloseable > rStrippedDocument;
    Reference< XMultiServiceFactory > rStrippedMSF;
    Reference < XDocumentHandler > xLocalDocumentHandler;
    Reference < XExporter > xStrippedExporter;
    Reference< XInteractionHandler > xInteractionHandler;

    OUString sFilterName;
    OUString sURL;
    OUString sXMLImportService;
    OUString sXMLExportService;
    OUString sStrippedDocumentType;

    sal_Bool bRetval(sal_True);
    sal_Bool bStrippedDocumentCreated(sal_False);

    for(sal_Int32 a(0); a < nLength; a++)
    {
        OUString sName(pValue[a].Name);

        if(pValue[a].Name.equalsAsciiL(RTL_CONSTASCII_STRINGPARAM("InputStream")))
            pValue[a].Value >>= xInputStream;

        else if(pValue[a].Name.equalsAsciiL(RTL_CONSTASCII_STRINGPARAM("FilterName")))
            pValue[a].Value >>= sFilterName;

        else if(pValue[a].Name.equalsAsciiL(RTL_CONSTASCII_STRINGPARAM("URL")))
            pValue[a].Value >>= sURL;

        else if(pValue[a].Name.equalsAsciiL(RTL_CONSTASCII_STRINGPARAM("InteractionHandler")))
            pValue[a].Value >>= xInteractionHandler;
    }

    if(bRetval)
    {
        // test for necessary parameters
        if(!xInputStream.is())
        {
            OSL_ASSERT(0);
            bRetval = sal_False;
        }
        else if(!sURL.getLength())
        {
            OSL_ASSERT(0);
            bRetval = sal_False;
        }
        else if(!sFilterName.getLength())
        {
            OSL_ASSERT(0);
            bRetval = sal_False;
        }
    }

    if(bRetval)
    {
        // try to get connection to Stripped office
        sal_Bool bGotLegacyServiceManager = getContactToLegacyProcessServiceFactory();

        if(!bGotLegacyServiceManager)
        {
            OSL_ASSERT(0);
            bRetval = sal_False;
        }
    }

    if(bRetval)
    {
        // get contact to the Stripped ServiceFactory
        rStrippedMSF = Reference< XMultiServiceFactory >::query(mxLegServFact);

        if(!rStrippedMSF.is())
        {
            OSL_ASSERT(0);
            bRetval = sal_False;
        }
    }

    if(bRetval)
    {
        // test if the InputStream is seekable
        Reference <XSeekable> xSeekable;
        xSeekable = Reference<XSeekable>::query(xInputStream);

        if(!xSeekable.is())
        {
            OSL_ASSERT(0);
            bRetval = sal_False;
        }
    }

    if(bRetval)
    {
        // Get DocumentType using GetFilterMatcher() (test)
        const SfxFilter* pFilter = SFX_APP()->GetFilterMatcher().GetFilter4FilterName( sFilterName );

        if(pFilter)
        {
            // Get sStrippedDocumentType. For SRX645 this is more simple, look below.
            const SfxFilterContainer* pFilCont = pFilter->GetFilterContainer();
            const SfxFactoryFilterContainer* pFacFilCont = (SfxFactoryFilterContainer*)pFilCont;
            const SfxObjectFactory& rFacRef = pFacFilCont->GetFactory();
            sStrippedDocumentType = rFacRef.GetDocumentServiceName();

            // for srx645:
            // sStrippedDocumentType = pFilter->GetServiceName();

            // ...fill rStrippedDocument somehow
            rStrippedDocument = Reference< XCloseable >::query(rStrippedMSF->createInstance(sStrippedDocumentType));

            if(rStrippedDocument.is())
            {
                bStrippedDocumentCreated = sal_True;
            }
            else
            {
                OSL_ASSERT(0);
                bRetval = sal_False;
            }

        }
    }

    if(bRetval)
    {
        // Make the Stripped office load the document
        Reference < XLoadable > rStrippedLoadable(rStrippedDocument, UNO_QUERY);

        if(rStrippedLoadable.is())
        {
            try
            {
                Sequence < PropertyValue > seqPropValues(xInteractionHandler.is() ? 5 : 4);

                seqPropValues[0].Name = OUString(RTL_CONSTASCII_USTRINGPARAM("ReadOnly"));
                seqPropValues[0].Value <<= sal_True;

                seqPropValues[1].Name = OUString(RTL_CONSTASCII_USTRINGPARAM("InputStream"));
                seqPropValues[1].Value <<= xInputStream;

                seqPropValues[2].Name = OUString(RTL_CONSTASCII_USTRINGPARAM("URL"));
                seqPropValues[2].Value <<= sURL;

                seqPropValues[3].Name = OUString(RTL_CONSTASCII_USTRINGPARAM("FilterName"));
                seqPropValues[3].Value <<= sFilterName;

                if(xInteractionHandler.is())
                {
                    seqPropValues[4].Name = OUString(RTL_CONSTASCII_USTRINGPARAM("InteractionHandler"));
                    seqPropValues[4].Value <<= xInteractionHandler;
                }

                rStrippedLoadable->load(seqPropValues);
            }
            catch(IOException& /*e*/)
            {
                OSL_ENSURE(sal_False, "IO exception.");
                bRetval = sal_False;
            }
            catch(IllegalArgumentException& /*e*/)
            {
                OSL_ENSURE(sal_False, "uno url invalid");
                bRetval = sal_False;
            }
        }
        else
        {
            OSL_ASSERT(0);
            bRetval = sal_False;
        }
    }

    // only the binary part should touch URLs; make sure that no BaseURL is passed to the importer also
    so3::StaticBaseUrl::SetBaseURL( String() );

    if(bRetval)
    {
        Reference < XServiceInfo > rStrippedServiceInfo(rStrippedDocument, UNO_QUERY);

        if(rStrippedServiceInfo.is())
        {
            if(rStrippedServiceInfo->supportsService(sServiceNameTextDocument)
                || rStrippedServiceInfo->supportsService(sServiceNameGlobalDocument)
                || rStrippedServiceInfo->supportsService(sServiceNameWebDocument))
            {
                // writer document
                sXMLImportService = OUString(RTL_CONSTASCII_USTRINGPARAM("com.sun.star.comp.Writer.XMLImporter"));
                sXMLExportService = OUString(RTL_CONSTASCII_USTRINGPARAM("com.sun.star.comp.Writer.XMLExporter"));
            }
            else if(rStrippedServiceInfo->supportsService(sServiceNamePresentationDocument))
            {
                // presentation: Ask BEFORE draw since presentation supports draw, too
                sXMLImportService = OUString(RTL_CONSTASCII_USTRINGPARAM("com.sun.star.comp.Impress.XMLImporter"));
                sXMLExportService = OUString(RTL_CONSTASCII_USTRINGPARAM("com.sun.star.comp.Impress.XMLExporter"));
            }
            else if(rStrippedServiceInfo->supportsService(sServiceNameDrawingDocument))
            {
                // drawing document
                sXMLImportService = OUString(RTL_CONSTASCII_USTRINGPARAM("com.sun.star.comp.Draw.XMLImporter"));
                sXMLExportService = OUString(RTL_CONSTASCII_USTRINGPARAM("com.sun.star.comp.Draw.XMLExporter"));
            }
            else if(rStrippedServiceInfo->supportsService(sServiceNameSpreadsheetDocument))
            {
                // calc document
                sXMLImportService = OUString(RTL_CONSTASCII_USTRINGPARAM("com.sun.star.comp.Calc.XMLImporter"));
                sXMLExportService = OUString(RTL_CONSTASCII_USTRINGPARAM("com.sun.star.comp.Calc.XMLExporter"));
            }
            else if(rStrippedServiceInfo->supportsService(sServiceNameChartDocument))
            {
                // chart document
                sXMLImportService = OUString(RTL_CONSTASCII_USTRINGPARAM("com.sun.star.comp.Chart.XMLImporter"));
                sXMLExportService = OUString(RTL_CONSTASCII_USTRINGPARAM("com.sun.star.comp.Chart.XMLExporter"));
            }
            else if(rStrippedServiceInfo->supportsService(sServiceNameFormulaProperties))
            {
                // formula document
                sXMLImportService = OUString(RTL_CONSTASCII_USTRINGPARAM("com.sun.star.comp.Math.XMLImporter"));
                sXMLExportService = OUString(RTL_CONSTASCII_USTRINGPARAM("com.sun.star.comp.Math.XMLExporter"));
            }
            else
            {
                OSL_ASSERT(0);
                bRetval = sal_False;
            }
        }
        else
        {
            OSL_ASSERT(0);
            bRetval = sal_False;
        }
    }

    if(bRetval)
    {
        // try to get local document handler
        xLocalDocumentHandler = Reference< XDocumentHandler >::query(mxMSF->createInstance(sXMLImportService));

        if(!xLocalDocumentHandler.is())
        {
            OSL_ASSERT(0);
            bRetval = sal_False;
        }
        else
        {
            // set target document at local document handler
            Reference < XImporter > xLocalImporter(xLocalDocumentHandler, UNO_QUERY);
            xLocalImporter->setTargetDocument(mxDoc);
        }
    }

    if(bRetval)
    {
        // try to create Stripped exporter, give local document handler as target
        Sequence < Any > aAnys(1);
        aAnys[0] <<= xLocalDocumentHandler;
        xStrippedExporter = Reference< XExporter >::query(rStrippedMSF->createInstanceWithArguments(sXMLExportService, aAnys));

        if(!xStrippedExporter.is())
        {
            OSL_ASSERT(0);
            bRetval = sal_False;
        }
        else
        {
            // set source document to Strippedly loaded read-only document
            xStrippedExporter->setSourceDocument( Reference < XComponent >( rStrippedDocument, UNO_QUERY ) );
        }
    }

    if(bRetval)
    {
        try
        {
            // lock target document controllers
            Reference < com::sun::star::frame::XModel > xTargetDocumentModel(mxDoc, UNO_QUERY);
            sal_Bool bTargetDocumentModelWasNotLocked(sal_False);

            if(xTargetDocumentModel.is() && !xTargetDocumentModel->hasControllersLocked())
            {
                bTargetDocumentModelWasNotLocked = sal_True;
                xTargetDocumentModel->lockControllers();
            }

            // now start the data exchange
            Reference < XFilter > xFilter(xStrippedExporter, UNO_QUERY);
            bRetval = xFilter->filter(aDescriptor);

            if(xTargetDocumentModel.is() && bTargetDocumentModelWasNotLocked)
            {
                xTargetDocumentModel->unlockControllers();
            }
        }
        catch(RuntimeException& /*e*/)
        {
            OSL_ENSURE(sal_False, "a Stripped call was aborted");
            bRetval = sal_False;
        }
    }

    if(bStrippedDocumentCreated)
    {
        // close Stripped document again
        try
        {
            rStrippedDocument->close(sal_True);
        }
        catch(Exception& /*e*/)
        {
        }
    }

    return bRetval;
}

sal_Bool bf_MigrateFilter::exportImpl(const Sequence< ::com::sun::star::beans::PropertyValue >& aDescriptor)
    throw (RuntimeException)
{
    sal_Int32 nLength(aDescriptor.getLength());
    const PropertyValue* pValue = aDescriptor.getConstArray();

    Reference < XOutputStream > xOutputStream;
    Reference< XMultiServiceFactory > rStrippedMSF;
    Reference< XCloseable > rStrippedDocument;
    Reference < XDocumentHandler > xStrippedDocumentHandler;
    Reference < XExporter > xLocalExporter;
    Reference< XInteractionHandler > xInteractionHandler;

    OUString sFilterName;
    OUString sXMLImportService;
    OUString sXMLExportService;
    OUString sStrippedDocumentType;

    sal_Bool bRetval(sal_True);
    sal_Bool bStrippedDocumentCreated(sal_False);

    for(sal_Int32 a(0); a < nLength; a++)
    {
        OUString sName(pValue[a].Name);

        if(pValue[a].Name.equalsAsciiL(RTL_CONSTASCII_STRINGPARAM("OutputStream")))
            pValue[a].Value >>= xOutputStream;

        else if(pValue[a].Name.equalsAsciiL(RTL_CONSTASCII_STRINGPARAM("FilterName")))
            pValue[a].Value >>= sFilterName;

        else if(pValue[a].Name.equalsAsciiL(RTL_CONSTASCII_STRINGPARAM("InteractionHandler")))
            pValue[a].Value >>= xInteractionHandler;
    }

    // only the binary part should touch URLs; make sure that no BaseURL is passed to the exporter also
    so3::StaticBaseUrl::SetBaseURL( String() );

    if(bRetval)
    {
        // test for necessary inputs
        if(!xOutputStream.is())
        {
            OSL_ASSERT(0);
            bRetval = sal_False;
        }
        else if(!sFilterName.getLength())
        {
            OSL_ASSERT(0);
            bRetval = sal_False;
        }
    }

    if(bRetval)
    {
        // try to get connection to Stripped office
        sal_Bool bGotLegacyServiceManager = getContactToLegacyProcessServiceFactory();

        if(!bGotLegacyServiceManager)
        {
            OSL_ASSERT(0);
            bRetval = sal_False;
        }
    }

    if(bRetval)
    {
        // get contact to Stripped ServiceFactory
        rStrippedMSF = Reference< XMultiServiceFactory >::query(mxLegServFact);

        if(!rStrippedMSF.is())
        {
            OSL_ASSERT(0);
            bRetval = sal_False;
        }
    }

    if(bRetval)
    {
        // what type of document am I?
        Reference < XServiceInfo > rLocalServiceInfo(mxDoc, UNO_QUERY);

        if(rLocalServiceInfo.is())
        {
            if(rLocalServiceInfo->supportsService(sServiceNameTextDocument)
                || rLocalServiceInfo->supportsService(sServiceNameGlobalDocument)
                || rLocalServiceInfo->supportsService(sServiceNameWebDocument))
            {
                // writer document
                sXMLImportService = OUString(RTL_CONSTASCII_USTRINGPARAM("com.sun.star.comp.Writer.XMLImporter"));
                sXMLExportService = OUString(RTL_CONSTASCII_USTRINGPARAM("com.sun.star.comp.Writer.XMLExporter"));

                if(rLocalServiceInfo->supportsService(sServiceNameGlobalDocument))
                {
                    sStrippedDocumentType = sServiceNameGlobalDocument;
                }
                else if(rLocalServiceInfo->supportsService(sServiceNameWebDocument))
                {
                    sStrippedDocumentType = sServiceNameWebDocument;
                }
                else
                {
                    sStrippedDocumentType = sServiceNameTextDocument;
                }
            }
            else if(rLocalServiceInfo->supportsService(sServiceNamePresentationDocument))
            {
                // presentation: Ask BEFORE draw since presentation supports draw, too
                sXMLImportService = OUString(RTL_CONSTASCII_USTRINGPARAM("com.sun.star.comp.Impress.XMLImporter"));
                sXMLExportService = OUString(RTL_CONSTASCII_USTRINGPARAM("com.sun.star.comp.Impress.XMLExporter"));
                sStrippedDocumentType = sServiceNamePresentationDocument;
            }
            else if(rLocalServiceInfo->supportsService(sServiceNameDrawingDocument))
            {
                // drawing document
                sXMLImportService = OUString(RTL_CONSTASCII_USTRINGPARAM("com.sun.star.comp.Draw.XMLImporter"));
                sXMLExportService = OUString(RTL_CONSTASCII_USTRINGPARAM("com.sun.star.comp.Draw.XMLExporter"));
                sStrippedDocumentType = sServiceNameDrawingDocument;
            }
            else if(rLocalServiceInfo->supportsService(sServiceNameSpreadsheetDocument))
            {
                // calc document
                sXMLImportService = OUString(RTL_CONSTASCII_USTRINGPARAM("com.sun.star.comp.Calc.XMLImporter"));
                sXMLExportService = OUString(RTL_CONSTASCII_USTRINGPARAM("com.sun.star.comp.Calc.XMLExporter"));
                sStrippedDocumentType = sServiceNameSpreadsheetDocument;
            }
            else if(rLocalServiceInfo->supportsService(sServiceNameChartDocument))
            {
                // chart document
                sXMLImportService = OUString(RTL_CONSTASCII_USTRINGPARAM("com.sun.star.comp.Chart.XMLImporter"));
                sXMLExportService = OUString(RTL_CONSTASCII_USTRINGPARAM("com.sun.star.comp.Chart.XMLExporter"));
                sStrippedDocumentType = sServiceNameChartDocument;
            }
            else if(rLocalServiceInfo->supportsService(sServiceNameFormulaProperties))
            {
                // formula document
                sXMLImportService = OUString(RTL_CONSTASCII_USTRINGPARAM("com.sun.star.comp.Math.XMLImporter"));
                sXMLExportService = OUString(RTL_CONSTASCII_USTRINGPARAM("com.sun.star.comp.Math.XMLExporter"));
                sStrippedDocumentType = sServiceNameFormulaProperties;
            }
            else
            {
                OSL_ASSERT(0);
                bRetval = sal_False;
            }
        }
        else
        {
            OSL_ASSERT(0);
            bRetval = sal_False;
        }
    }

    if(bRetval)
    {
        // open an empty Stripped document
        rStrippedDocument = Reference< XCloseable >::query(rStrippedMSF->createInstance(sStrippedDocumentType));

        if(!rStrippedDocument.is())
        {
            OSL_ASSERT(0);
            bRetval = sal_False;
        }
        else
        {
            // get XLoadable, call initNew()
            Reference < XLoadable > xLoadable(rStrippedDocument, UNO_QUERY);

            if(xLoadable.is())
            {
                // the new document needs to be initialized before usage
                xLoadable->initNew();
            }

            bStrippedDocumentCreated = sal_True;
        }
    }

    if(bRetval)
    {
        // try to get Stripped document handler
        xStrippedDocumentHandler = Reference< XDocumentHandler >::query(rStrippedMSF->createInstance(sXMLImportService));

        if(!xStrippedDocumentHandler.is())
        {
            OSL_ASSERT(0);
            bRetval = sal_False;
        }
        else
        {
            // set target document at Stripped document handler
            Reference < XImporter > xStrippedImporter(xStrippedDocumentHandler, UNO_QUERY);
            xStrippedImporter->setTargetDocument( Reference < XComponent >( rStrippedDocument, UNO_QUERY ) );
        }
    }

    if(bRetval)
    {
        // try to create local exporter, give Stripped document handler as target
        Sequence < Any > aAnys(1);
        aAnys[0] <<= xStrippedDocumentHandler;

        xLocalExporter = Reference< XExporter >::query(mxMSF->createInstanceWithArguments(sXMLExportService, aAnys));

        if(!xLocalExporter.is())
        {
            OSL_ASSERT(0);
            bRetval = sal_False;
        }
        else
        {
            // set source document to local document
            xLocalExporter->setSourceDocument(mxDoc);
        }
    }

    if(bRetval)
    {
        try
        {
            // lock target document controllers
            Reference < com::sun::star::frame::XModel > xTargetDocumentModel(rStrippedDocument, UNO_QUERY);
            sal_Bool bTargetDocumentModelWasNotLocked(sal_False);

            if(xTargetDocumentModel.is() && !xTargetDocumentModel->hasControllersLocked())
            {
                bTargetDocumentModelWasNotLocked = sal_True;
                xTargetDocumentModel->lockControllers();
            }

            // now start the data exchange (needs fix #98472#)
            Reference < XFilter > xFilter(xLocalExporter, UNO_QUERY);
            bRetval = xFilter->filter(aDescriptor);

            if(xTargetDocumentModel.is() && bTargetDocumentModelWasNotLocked)
            {
                xTargetDocumentModel->unlockControllers();
            }
        }
        catch(RuntimeException& /*e*/)
        {
            OSL_ENSURE(sal_False, "a local call was aborted");
            bRetval = sal_False;
        }
    }

    if(bRetval)
    {
        // save Stripped document now with given filter to given filename
        Reference < XStorable > xStrippedStorable(rStrippedDocument, UNO_QUERY);

        if(xStrippedStorable.is())
        {
            try
            {
                // is XSeekable?
                Reference <XSeekable> xSeekable;
                xSeekable = Reference<XSeekable>::query(xOutputStream);

                Sequence < PropertyValue > seqPropValues(xInteractionHandler.is() ? 4 : 3);

                seqPropValues[0].Name = OUString(RTL_CONSTASCII_USTRINGPARAM("Overwrite"));
                seqPropValues[0].Value <<= sal_True;

                seqPropValues[1].Name = OUString(RTL_CONSTASCII_USTRINGPARAM("FilterName"));
                seqPropValues[1].Value <<= sFilterName;

                seqPropValues[2].Name = OUString(RTL_CONSTASCII_USTRINGPARAM("OutputStream"));
                seqPropValues[2].Value <<= xOutputStream;

                if(xInteractionHandler.is())
                {
                    seqPropValues[3].Name = OUString(RTL_CONSTASCII_USTRINGPARAM("InteractionHandler"));
                    seqPropValues[3].Value <<= xInteractionHandler;
                }

                const OUString sUrlToReadFromXOutputStream(RTL_CONSTASCII_USTRINGPARAM("private:stream"));

                // To make this run, in the stripped sfx2 (look for #ChangedstoreAsURL# in bf_sfx2) the decision
                // for using a SFX_FILTER_STARONEFILTER needs to be removed. Else, the migrate filter will
                // be called again recursively.
                xStrippedStorable->storeToURL(
                    sUrlToReadFromXOutputStream,
                    seqPropValues
                    );
            }
            catch(IOException& /*e*/)
            {
                OSL_ENSURE(sal_False, "IO exception.");
                bRetval = sal_False;
            }
            catch(IllegalArgumentException& /*e*/)
            {
                OSL_ENSURE(sal_False, "uno url invalid");
                bRetval = sal_False;
            }
        }
        else
        {
            OSL_ASSERT(0);
            bRetval = sal_False;
        }
    }

    if(bStrippedDocumentCreated)
    {
        // close Stripped document again
        try
        {
            rStrippedDocument->close(sal_True);
        }
        catch(Exception& /*e*/)
        {
        }
    }

    return bRetval;
}

sal_Bool SAL_CALL bf_MigrateFilter::filter(const Sequence< ::com::sun::star::beans::PropertyValue >& aDescriptor)
    throw (RuntimeException)
{
    sal_Bool bRetval(sal_False);
    sal_Bool bGotLegacyServiceManager = getContactToLegacyProcessServiceFactory();

    if(bGotLegacyServiceManager)
    {
        Reference < XComponent > xWrapper( mxLegServFact->createInstance(
            ::rtl::OUString( RTL_CONSTASCII_USTRINGPARAM( "com.sun.star.office.OfficeWrapper" ))), UNO_QUERY );

        bRetval = (FILTER_EXPORT == meType) ? exportImpl(aDescriptor) : importImpl(aDescriptor);

        xWrapper->dispose();
        xWrapper = 0;
    }

    return bRetval;
}

void SAL_CALL bf_MigrateFilter::cancel()
    throw (RuntimeException)
{
}

// XExporter
void SAL_CALL bf_MigrateFilter::setSourceDocument(const Reference< ::com::sun::star::lang::XComponent >& xDoc)
    throw (::com::sun::star::lang::IllegalArgumentException, RuntimeException)
{
    meType = FILTER_EXPORT;
    mxDoc = xDoc;
}

// XImporter
void SAL_CALL bf_MigrateFilter::setTargetDocument(const Reference< ::com::sun::star::lang::XComponent >& xDoc)
    throw (::com::sun::star::lang::IllegalArgumentException, RuntimeException)
{
    meType = FILTER_IMPORT;
    mxDoc = xDoc;
}

// XInitialization
void SAL_CALL bf_MigrateFilter::initialize(const Sequence< Any >& aArguments)
    throw (Exception, RuntimeException)
{
    Sequence < PropertyValue > aAnySeq;
    sal_Int32 nLength(aArguments.getLength());

    if(nLength && (aArguments[0] >>= aAnySeq))
    {
        const PropertyValue* pValue = aAnySeq.getConstArray();
        nLength = aAnySeq.getLength();

        for(sal_Int32 a(0); a < nLength; a++)
        {
            OUString sName(pValue[a].Name);

            if(pValue[a].Name.equalsAsciiL(RTL_CONSTASCII_STRINGPARAM("Type")))
                pValue[a].Value >>= msFilterName;
        }
    }
}

OUString bf_MigrateFilter_getImplementationName()
    throw (RuntimeException)
{
    return OUString(RTL_CONSTASCII_USTRINGPARAM("com.sun.star.comp.office.BF_MigrateFilter"));
}

#define SERVICE_NAME1 "com.sun.star.document.ExportFilter"
#define SERVICE_NAME2 "com.sun.star.document.ImportFilter"

sal_Bool SAL_CALL bf_MigrateFilter_supportsService(const OUString& ServiceName)
    throw (RuntimeException)
{
    return ServiceName.equalsAsciiL(RTL_CONSTASCII_STRINGPARAM(SERVICE_NAME1)) ||
           ServiceName.equalsAsciiL(RTL_CONSTASCII_STRINGPARAM(SERVICE_NAME2));
}

Sequence< OUString > SAL_CALL bf_MigrateFilter_getSupportedServiceNames()
    throw (RuntimeException)
{
    Sequence < OUString > aRet(2);
    OUString* pArray = aRet.getArray();

    pArray[0] =  OUString(RTL_CONSTASCII_USTRINGPARAM(SERVICE_NAME1));
    pArray[1] =  OUString(RTL_CONSTASCII_USTRINGPARAM(SERVICE_NAME2));

    return aRet;
}

#undef SERVICE_NAME1
#undef SERVICE_NAME2

Reference< XInterface > SAL_CALL bf_MigrateFilter_createInstance(const Reference< XMultiServiceFactory > & rSMgr)
    throw( Exception )
{
    static ::com::sun::star::uno::Reference< ::com::sun::star::lang::XMultiServiceFactory > mxLegServFact;
    if ( !mxLegServFact.is() )
    {
        mxLegServFact = ::legacy_binfilters::getLegacyProcessServiceFactory();
        ::com::sun::star::uno::Reference < XComponent > xWrapper( mxLegServFact->createInstance(
            ::rtl::OUString( RTL_CONSTASCII_USTRINGPARAM( "com.sun.star.office.OfficeWrapper" ))), UNO_QUERY );
    }

    return (cppu::OWeakObject*)new bf_MigrateFilter(rSMgr);
}

// XServiceInfo
OUString SAL_CALL bf_MigrateFilter::getImplementationName()
    throw (RuntimeException)
{
    return bf_MigrateFilter_getImplementationName();
}

sal_Bool SAL_CALL bf_MigrateFilter::supportsService(const OUString& rServiceName)
    throw (RuntimeException)
{
    return bf_MigrateFilter_supportsService(rServiceName);
}

Sequence< OUString > SAL_CALL bf_MigrateFilter::getSupportedServiceNames()
    throw (RuntimeException)
{
    return bf_MigrateFilter_getSupportedServiceNames();
}

// eof
}
