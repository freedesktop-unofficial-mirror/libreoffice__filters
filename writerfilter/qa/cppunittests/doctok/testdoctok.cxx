// autogenerated file with codegen.pl

#include <sal/cppunit.h>
#include <osl/process.h>
#include <cppuhelper/bootstrap.hxx>
#include <ucbhelper/contentbroker.hxx>
#include <com/sun/star/io/XInputStream.hpp>
#include <com/sun/star/ucb/XSimpleFileAccess.hpp>
#include <com/sun/star/lang/XMultiServiceFactory.hpp>
#include <iostream>

#include <doctok/WW8Document.hxx>

namespace testdoctok
{
using namespace ::std;
using namespace ::com::sun::star;
using namespace ::writerfilter::doctok;

uno::Reference<io::XInputStream> xStream;
uno::Reference<uno::XComponentContext> xContext;
WW8Document::Pointer_t pDocument;
uno::Reference< ::com::sun::star::ucb::XSimpleFileAccess > xSimpleFileAccess;

class test : public CppUnit::TestFixture
{

public:
    // initialise your test code values here.
    void setUp()
    {
    }

    void tearDown()
    {
    }

    void testInitUno()
    {
        bool bResult = false;

        // initialise UCB-Broker
        uno::Reference<uno::XComponentContext>
            xComponentContext
            (::cppu::defaultBootstrap_InitialComponentContext());
        OSL_ASSERT( xComponentContext.is() );

        xContext = xComponentContext;

        uno::Reference<lang::XMultiComponentFactory>
            xFactory(xComponentContext->getServiceManager() );
        OSL_ASSERT(xFactory.is());

        uno::Sequence<uno::Any> aUcbInitSequence(2);
        aUcbInitSequence[0] <<=
            rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("Local"));
        aUcbInitSequence[1] <<=
            rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("Office"));

        uno::Reference<lang::XMultiServiceFactory>
            xServiceFactory(xFactory, uno::UNO_QUERY);
        OSL_ASSERT( xServiceFactory.is() );

        if (xServiceFactory.is())
        {
            sal_Bool bRet =
                ::ucbhelper::ContentBroker::initialize(xServiceFactory,
                                                       aUcbInitSequence);

            OSL_ASSERT(bRet);
            if (bRet)
            {
                uno::Reference< ::com::sun::star::ucb::XSimpleFileAccess >
                    xNameContainer(xFactory->createInstanceWithContext
                                   (::rtl::OUString::createFromAscii
                                    ("com.sun.star.ucb.SimpleFileAccess" ),
                                    xComponentContext), uno::UNO_QUERY );

                if (xNameContainer.is())
                {
                    xSimpleFileAccess = xNameContainer;

                    bResult = true;
                }
            }
        }

        CPPUNIT_ASSERT_MESSAGE("UNO initialization failed",
                               bResult);
    }

    // insert your test code here.
    void testOpenFile()
    {
        try
        {
            rtl_uString *dir=NULL;
            osl_getProcessWorkingDir(&dir);
            rtl_uString *fname=NULL;
            //rtl_uString_newFromAscii(&fname, "/OpenDocument-v1.doc");
            rtl_uString_newFromAscii(&fname, "/test.doc");
            //rtl_uString_newFromAscii(&fname, "/numbers.doc");
            rtl_uString *absfile=NULL;
            rtl_uString_newConcat(&absfile, dir, fname);

            rtl::OUString sInputFileURL( absfile );

            for (sal_Int32 n = 0; n < sInputFileURL.getLength(); ++n)
            {
                sal_uChar nC = sInputFileURL[n];

                if (nC < 0xff && isprint(nC))
                    clog << static_cast<char>(nC);
                else
                    clog << ".";
            }

            clog << endl;

            xStream = xSimpleFileAccess->openFileRead(sInputFileURL);

            WW8Stream::Pointer_t pStream =
                WW8DocumentFactory::createStream(xContext, xStream);

            pDocument.reset(WW8DocumentFactory::createDocument(pStream));
        }
        catch (writerfilter::Exception e)
        {
            clog << "Exception!!" << endl;
        }

        CPPUNIT_ASSERT_MESSAGE("creating document failed",
                               pDocument != NULL);
    }

    void testEvents()
    {
        try
        {
            ::writerfilter::Stream::Pointer_t pStream = ::writerfilter::createStreamHandler();

            pDocument->resolve(*pStream);
        }
        catch (writerfilter::Exception e)
        {
            clog << "Exception!!" << endl;
        }
    }

    void testEnd()
    {
        ::ucbhelper::ContentBroker::deinitialize();
    }

    // Change the following lines only, if you add, remove or rename 
    // member functions of the current class, 
    // because these macros are need by auto register mechanism.

    CPPUNIT_TEST_SUITE(test);
    CPPUNIT_TEST(testInitUno);
    CPPUNIT_TEST(testOpenFile);
    CPPUNIT_TEST(testEvents);
    CPPUNIT_TEST(testEnd);        
    CPPUNIT_TEST_SUITE_END();
}; // class test

// -----------------------------------------------------------------------------
CPPUNIT_TEST_SUITE_NAMED_REGISTRATION(testdoctok::test, "doctok");
} // namespace doctok


// -----------------------------------------------------------------------------

CPPUNIT_PLUGIN_IMPLEMENT();

