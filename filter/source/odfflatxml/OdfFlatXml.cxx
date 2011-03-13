/* -*- Mode: C++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */
/*
 * Version: MPL 1.1 / GPLv3+ / LGPLv3+
 *
 * The contents of this file are subject to the Mozilla Public License Version
 * 1.1 (the "License"); you may not use this file except in compliance with
 * the License or as specified alternatively below. You may obtain a copy of
 * the License at http://www.mozilla.org/MPL/
 *
 * Software distributed under the License is distributed on an "AS IS" basis,
 * WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License
 * for the specific language governing rights and limitations under the
 * License.
 *
 * The Initial Developer of the Original Code is
 *       Peter Jentsch <pjotr@guineapics.de>
 *
 * Portions created by the Initial Developer are Copyright (C) 2011 the
 * Initial Developer. All Rights Reserved.
 *
 * For minor contributions see the git repository.
 *
 * Alternatively, the contents of this file may be used under the terms of
 * either the GNU General Public License Version 3 or later (the "GPLv3+"), or
 * the GNU Lesser General Public License Version 3 or later (the "LGPLv3+"),
 * in which case the provisions of the GPLv3+ or the LGPLv3+ are applicable
 * instead of those above.
 */

// MARKER(update_precomp.py): autogen include statement, do not remove
#include "precompiled_filter.hxx"

#include <cppuhelper/factory.hxx>
#include <cppuhelper/servicefactory.hxx>
#include <cppuhelper/implbase3.hxx>
#include <cppuhelper/implbase.hxx>

#include <sax/tools/documenthandleradapter.hxx>

#include <com/sun/star/lang/XComponent.hpp>

#include <com/sun/star/uno/Any.hxx>
#include <com/sun/star/uno/Type.hxx>

#include <com/sun/star/beans/PropertyValue.hpp>

#include <com/sun/star/xml/XImportFilter.hpp>
#include <com/sun/star/xml/XExportFilter.hpp>
#include <com/sun/star/xml/sax/XParser.hpp>
#include <com/sun/star/xml/sax/InputSource.hpp>
#include <com/sun/star/xml/sax/XDocumentHandler.hpp>
#include <com/sun/star/xml/sax/XExtendedDocumentHandler.hpp>
#include <com/sun/star/xml/sax/SAXException.hpp>

#include <com/sun/star/io/XInputStream.hpp>
#include <com/sun/star/io/XOutputStream.hpp>
#include <com/sun/star/io/XActiveDataSource.hpp>
#include <com/sun/star/io/XSeekable.hpp>

#include <registration.hxx>

using namespace ::rtl;
using namespace ::cppu;
using namespace ::osl;
using namespace ::sax;
using namespace ::com::sun::star::beans;
using namespace ::com::sun::star::io;
using namespace ::com::sun::star::uno;
using namespace ::com::sun::star::lang;
using namespace ::com::sun::star::registry;
using namespace ::com::sun::star::xml;
using namespace ::com::sun::star::xml::sax;

namespace filter {
    namespace odfflatxml {
        /*
         * OdfFlatXml export and imports ODF flat XML documents by plugging a pass-through
         * filter implementation into XmlFilterAdaptor.
         */
        class OdfFlatXml : public WeakImplHelper3<XImportFilter,
                                                  XExportFilter, DocumentHandlerAdapter>
        {
        private:
            Reference< XMultiServiceFactory > m_rServiceFactory;

        public:

            OdfFlatXml(const Reference<XMultiServiceFactory> &r) :
                m_rServiceFactory(r)
            {
            }

            // XImportFilter
            virtual sal_Bool SAL_CALL
            importer(const Sequence< PropertyValue >& sourceData,
                     const Reference< XDocumentHandler >& docHandler,
                     const Sequence< OUString >& userData)
                throw (IllegalArgumentException, RuntimeException);

            // XExportFilter
            virtual sal_Bool SAL_CALL
            exporter(
                     const Sequence< PropertyValue >& sourceData,
                     const Sequence< OUString >& userData)
                throw (IllegalArgumentException,
                       RuntimeException);

            // UNO component helper methods

            static OUString impl_getImplementationName();

            static Sequence< OUString > impl_getSupportedServiceNames();

            static Reference< XInterface > impl_createInstance(const Reference< XMultiServiceFactory >& fact);
        };
    }
}

using namespace ::filter::odfflatxml;

sal_Bool
OdfFlatXml::importer(
                     const Sequence< PropertyValue >& sourceData,
                     const Reference< XDocumentHandler >& docHandler,
                     const Sequence< OUString >& /* userData */)
    throw (IllegalArgumentException, RuntimeException)
{
    // Read InputStream to read from and an URL used for the system id
    // of the InputSource we create from the given sourceData sequence
    Reference<XInputStream> inputStream;
    OUString paramName;
    OUString url;

    sal_Int32 paramCount = sourceData.getLength();
    for (sal_Int32 paramIdx = 0; paramIdx < paramCount; paramIdx++)
        {
            paramName = sourceData[paramIdx].Name;
            if (paramName.equalsAscii("InputStream"))
                sourceData[paramIdx].Value >>= inputStream;
            else if (paramName.equalsAscii("URL"))
                sourceData[paramIdx].Value >>= url;
        }

    OSL_ASSERT(inputStream.is());
    if (!inputStream.is())
        return sal_False;

    OUString SAX_PARSER_SERVICE(
                                RTL_CONSTASCII_USTRINGPARAM("com.sun.star.xml.sax.Parser"));
    Reference<XParser> saxParser(m_rServiceFactory->createInstance(
                                                                   SAX_PARSER_SERVICE), UNO_QUERY);

    OSL_ASSERT(saxParser.is());
    if (!saxParser.is())
        return sal_False;

    InputSource inputSource;
    inputSource.sSystemId = url;
    inputSource.sPublicId = url;
    inputSource.aInputStream = inputStream;
    saxParser->setDocumentHandler(docHandler);
    try
        {
            saxParser->parseStream(inputSource);
        }
    catch (Exception &exc)
        {
            OString msg = OUStringToOString(exc.Message,
                                            RTL_TEXTENCODING_ASCII_US);
            OSL_ENSURE(0, msg);
            return sal_False;
        }
    return sal_True;
}

sal_Bool
OdfFlatXml::exporter(const Sequence< PropertyValue >& sourceData,
                     const Sequence< OUString >& /*msUserData*/)
    throw (IllegalArgumentException, RuntimeException)
{
    OUString paramName;
    OUString targetURL;
    Reference<XOutputStream> outputStream;

    // Read output stream and target URL from the parameters given in sourceData.
    sal_Int32 paramCount = sourceData.getLength();
    for (sal_Int32 paramIdx = 0; paramIdx < paramCount; paramIdx++)
        {
            paramName = sourceData[paramIdx].Name;
            if (paramName.equalsAscii("OutputStream"))
                sourceData[paramIdx].Value >>= outputStream;
            else if (paramName.equalsAscii("URL"))
                sourceData[paramIdx].Value >>= targetURL;
        }

    if (!getDelegate().is())
        {
            OUString SAX_WRITER_SERVICE(RTL_CONSTASCII_USTRINGPARAM("com.sun.star.xml.sax.Writer"));
            Reference< XDocumentHandler > saxWriter(m_rServiceFactory->createInstance(SAX_WRITER_SERVICE),
                                                    UNO_QUERY);
            setDelegate(saxWriter);
            if (!getDelegate().is())
                return sal_False;
        }
    // get data source interface ...
    Reference<XActiveDataSource> dataSource(getDelegate(), UNO_QUERY);
    OSL_ASSERT(dataSource.is());
    if (!dataSource.is())
        return sal_False;
    OSL_ASSERT(outputStream.is());
    if (!outputStream.is())
        return sal_False;
    dataSource->setOutputStream(outputStream);

    return sal_True;
}


OUString OdfFlatXml::impl_getImplementationName()
{
    return OUString( RTL_CONSTASCII_USTRINGPARAM("com.sun.star.comp.filter.OdfFlatXml"));
}

Sequence< OUString > OdfFlatXml::impl_getSupportedServiceNames()
{
    Sequence< OUString > lServiceNames(2);
    lServiceNames[0] = OUString( RTL_CONSTASCII_USTRINGPARAM( "com.sun.star.document.ImportFilter" ));
    lServiceNames[1] = OUString( RTL_CONSTASCII_USTRINGPARAM( "com.sun.star.document.ExportFilter" ));
    return lServiceNames;
}

Reference< XInterface > SAL_CALL OdfFlatXml::impl_createInstance(const Reference< XMultiServiceFactory >& fact)
{
    return Reference<XInterface> ((OWeakObject *) new OdfFlatXml(fact));

}

_COMPHELPER_COMPONENT_GETIMPLEMENTATIONENVIRONMENT

// extern "C" component_getFactory()
_COMPHELPER_COMPONENT_GETFACTORY
(
 {},
 _COMPHELPER_ONEINSTANCEFACTORY( OdfFlatXml::impl_getImplementationName(),
                                 OdfFlatXml::impl_getSupportedServiceNames(),
                                 OdfFlatXml::impl_createInstance)

)

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
