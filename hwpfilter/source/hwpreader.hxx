/* -*- Mode: C++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */
/*************************************************************************
 *
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER.
 * 
 * Copyright 2000, 2010 Oracle and/or its affiliates.
 *
 * OpenOffice.org - a multi-platform office productivity suite
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

#ifndef _HWPREADER_HXX_
#define _HWPREADER_HXX_
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <sal/alloca.h>

#include <com/sun/star/lang/XServiceInfo.hpp>
#include <com/sun/star/lang/XComponent.hpp>
#include <com/sun/star/io/XInputStream.hpp>
#include <com/sun/star/document/XFilter.hpp>
#include <com/sun/star/document/XImporter.hpp>
#include <com/sun/star/xml/sax/XDocumentHandler.hpp>

#include <com/sun/star/ucb/XContentIdentifierFactory.hpp>
#include <com/sun/star/ucb/XContentProvider.hpp>
#include <com/sun/star/ucb/XContentIdentifier.hpp>
#include <com/sun/star/ucb/XContent.hpp>
#include <com/sun/star/ucb/OpenCommandArgument2.hpp>
#include <com/sun/star/ucb/OpenMode.hpp>
#include <com/sun/star/ucb/XCommandProcessor.hpp>
#include <com/sun/star/ucb/XCommandEnvironment.hpp>
#include <cppuhelper/implbase2.hxx>
#include <com/sun/star/io/XActiveDataSink.hpp>
#include <com/sun/star/io/XActiveDataControl.hpp>
#include <com/sun/star/io/XStreamListener.hpp>

#include <cppuhelper/factory.hxx>
#include <cppuhelper/weak.hxx>
#include <cppuhelper/implbase1.hxx>
#include <cppuhelper/implbase3.hxx>
#include <cppuhelper/servicefactory.hxx>

using namespace ::rtl;
using namespace ::cppu;
using namespace ::com::sun::star::ucb;
using namespace ::com::sun::star::lang;
using namespace ::com::sun::star::uno;
using namespace ::com::sun::star::io;
using namespace ::com::sun::star::registry;
using namespace ::com::sun::star::document;
using namespace ::com::sun::star::beans;
using namespace ::com::sun::star::xml::sax;

#include <assert.h>

#include "hwpfile.h"
#include "hcode.h"
#include "hbox.h"
#include "htags.h"
#include "hstream.h"
#include "drawdef.h"
#include "attributes.hxx"	


#define IMPLEMENTATION_NAME "com.sun.comp.hwpimport.HwpImportFilter"
#define  SERVICE_NAME       "com.sun.star.document.ImportFilter"
#define WRITER_IMPORTER_NAME    "com.sun.star.comp.Writer.XMLImporter"

class MyDataSink : public ::cppu::WeakImplHelper2< XActiveDataControl, XActiveDataSink >
{
  Reference < XInputStream >	m_xInputStream;
public:

  // XActiveDataControl.
  virtual void SAL_CALL   addListener ( const Reference<XStreamListener> &)
    throw(RuntimeException) {}
  virtual void SAL_CALL   removeListener ( const Reference<XStreamListener> &)
    throw(RuntimeException) {}
  virtual void SAL_CALL   start (void) throw(RuntimeException) {}
  virtual void SAL_CALL   terminate (void) throw(RuntimeException) {}

  // XActiveDataSink.
  virtual void SAL_CALL   setInputStream ( const Reference<XInputStream> &rxInputStream)
    throw(RuntimeException);
  virtual Reference<XInputStream> SAL_CALL getInputStream (void) 
    throw(RuntimeException);
};

void SAL_CALL MyDataSink::setInputStream ( const Reference<XInputStream> &rxInputStream)
  throw(RuntimeException )
{
  m_xInputStream = rxInputStream;
}

Reference < XInputStream > SAL_CALL MyDataSink::getInputStream (void) 
  throw(RuntimeException)
{
  return m_xInputStream;
}

struct HwpReaderPrivate;
/**
 * This class implements the external Parser interface
 */
class HwpReader : public WeakImplHelper1<XFilter>
{
    
public:	
    HwpReader();
    ~HwpReader();
    
public:
    /**
     * parseStream does Parser-startup initializations
     */
    virtual sal_Bool SAL_CALL filter(const Sequence< PropertyValue >& aDescriptor) throw (RuntimeException);
    virtual void SAL_CALL cancel() throw(RuntimeException) {}
    virtual void SAL_CALL setDocumentHandler(Reference< XDocumentHandler >  xHandler) 
    {
        rDocumentHandler = xHandler;
    }
     void setUCB( Reference< XInterface > xUCB ){
         rUCB = xUCB;
     }
private:
    Reference< XDocumentHandler >   rDocumentHandler;
     Reference< XInterface > rUCB;
    Reference< XAttributeList > rList;
    AttributeListImpl *pList;
    HWPFile hwpfile;
     HwpReaderPrivate *d;

private:
    /* -------- Document Parsing --------- */
    void makeMeta();
    void makeStyles();
    void makeDrawMiscStyle(HWPDrawingObject *);
    void makeAutoStyles();
    void makeMasterStyles();
    void makeBody();

    void makeTextDecls();

    /* -------- Paragraph Parsing --------- */
    void parsePara(HWPPara *para, sal_Bool bParaStart = sal_False);
    void make_text_p0(HWPPara *para, sal_Bool bParaStart = sal_False);
    void make_text_p1(HWPPara *para, sal_Bool bParaStart = sal_False);
    void make_text_p3(HWPPara *para, sal_Bool bParaStart = sal_False);

    /* -------- rDocument->characters(x) --------- */
    void makeChars(hchar *, int);

    /* -------- Special Char Parsing --------- */
    void makeFieldCode(FieldCode *hbox);		//6
    void makeBookmark(Bookmark *hbox);		//6
    void makeDateFormat(DateCode *hbox);	//7
    void makeDateCode(DateCode *hbox);		//8
    void makeTab(Tab *hbox);			//9
    void makeTable(TxtBox *hbox);			
    void makeTextBox(TxtBox *hbox);			
    void makeFormula(TxtBox *hbox);			
    void makeHyperText(TxtBox *hbox);			
    void makePicture(Picture *hbox);			
    void makePictureDRAW(HWPDrawingObject *drawobj, Picture *hbox);
    void makeLine(Line *hbox);			
    void makeHidden(Hidden *hbox);	
    void makeFootnote(Footnote *hbox);	
    void makeAutoNum(AutoNum *hbox);
    void makeShowPageNum();	
    void makeMailMerge(MailMerge *hbox);
    void makeTocMark(TocMark *hbox);		
    void makeIndexMark(IndexMark *hbox);
    void makeOutline(Outline *hbox);

    /* --------- Styles Parsing ------------ */
    void makePageStyle();
     void makeColumns(ColumnDef *);
    void makeTStyle(CharShape *);
    void makePStyle(ParaShape *);
    void makeFStyle(FBoxStyle *);
    void makeCaptionStyle(FBoxStyle *);
    void makeDrawStyle(HWPDrawingObject *,FBoxStyle *);
    void makeTableStyle(Table *);
    void parseCharShape(CharShape *);
    void parseParaShape(ParaShape *);
    char* getTStyleName(int, char *);
    char* getPStyleName(int, char *);
};

class HwpImportFilter : public WeakImplHelper3< XFilter, XImporter, XServiceInfo >
{
public:
    HwpImportFilter( const Reference< XMultiServiceFactory > xFact );
    ~HwpImportFilter();

public:
    static Sequence< OUString > getSupportedServiceNames_Static( void ) throw();
    static OUString getImplementationName_Static() throw();

public:
        // XFilter
    virtual sal_Bool SAL_CALL filter( const Sequence< PropertyValue >& aDescriptor )
        throw( RuntimeException );
    virtual void SAL_CALL cancel() throw(RuntimeException);
        // XImporter
    virtual void SAL_CALL setTargetDocument( const Reference< XComponent >& xDoc)
        throw( IllegalArgumentException, RuntimeException );
        // XServiceInfo
    OUString SAL_CALL getImplementationName() throw (RuntimeException);
    Sequence< OUString > SAL_CALL getSupportedServiceNames(void) throw (::com::sun::star::uno::RuntimeException);
    sal_Bool SAL_CALL supportsService(const OUString& ServiceName) throw (::com::sun::star::uno::RuntimeException);

public:
    Reference< XFilter > rFilter;
    Reference< XImporter > rImporter;
};

Reference< XInterface > HwpImportFilter_CreateInstance(
    const Reference< XMultiServiceFactory >& rSMgr ) throw( Exception )
{
    HwpImportFilter *p = new HwpImportFilter( rSMgr );

    return Reference< XInterface > ( (OWeakObject* )p );
}

Sequence< OUString > HwpImportFilter::getSupportedServiceNames_Static( void ) throw ()
{
    Sequence< OUString > aRet(1);
    aRet.getArray()[0] = HwpImportFilter::getImplementationName_Static();
    return aRet;
}
HwpImportFilter::HwpImportFilter( const Reference< XMultiServiceFactory > xFact )
{
    OUString sService(RTL_CONSTASCII_USTRINGPARAM( WRITER_IMPORTER_NAME ));
    try {
        Reference< XDocumentHandler >
            xHandler( xFact->createInstance( sService ), UNO_QUERY );

        HwpReader *p = new HwpReader;
        p->setDocumentHandler( xHandler );

          Sequence< Any > aArgs( 2 );
          aArgs[0] <<= OUString(RTL_CONSTASCII_USTRINGPARAM("Local"));
          aArgs[1] <<= OUString(RTL_CONSTASCII_USTRINGPARAM("Office"));
          Reference< XInterface > xUCB 
              ( xFact->createInstanceWithArguments
                 (OUString(RTL_CONSTASCII_USTRINGPARAM("com.sun.star.ucb.UniversalContentBroker")),
                  aArgs));
          p->setUCB( xUCB );


        Reference< XImporter > xImporter = Reference< XImporter >( xHandler, UNO_QUERY );
        rImporter = xImporter;
        Reference< XFilter > xFilter = Reference< XFilter >( p );
        rFilter = xFilter;
    }
    catch( Exception & )
    {
        printf(" fail to instanciate %s\n", WRITER_IMPORTER_NAME );
        exit( 1 );
    }
}

HwpImportFilter::~HwpImportFilter()
{
}

sal_Bool HwpImportFilter::filter( const Sequence< PropertyValue >& aDescriptor )
    throw( RuntimeException )
{
        // delegate to IchitaroImpoter
    rFilter->filter( aDescriptor );

    return sal_True;
}

void HwpImportFilter::cancel() throw(::com::sun::star::uno::RuntimeException)
{
    rFilter->cancel();
}

void HwpImportFilter::setTargetDocument( const Reference< XComponent >& xDoc )
    throw( IllegalArgumentException, RuntimeException )
{
        // delegate
    rImporter->setTargetDocument( xDoc );
}

OUString HwpImportFilter::getImplementationName_Static() throw()
{
    return OUString(RTL_CONSTASCII_USTRINGPARAM( IMPLEMENTATION_NAME ));
}

OUString HwpImportFilter::getImplementationName() throw(::com::sun::star::uno::RuntimeException)
{
    return OUString(RTL_CONSTASCII_USTRINGPARAM( IMPLEMENTATION_NAME ));
}
sal_Bool HwpImportFilter::supportsService( const OUString& ServiceName ) throw(::com::sun::star::uno::RuntimeException)
{
    Sequence< OUString > aSNL = getSupportedServiceNames();
    const OUString *pArray = aSNL.getConstArray();

    for ( sal_Int32 i = 0; i < aSNL.getLength(); i++ )
        if ( pArray[i] == ServiceName )
            return sal_True;

    return sal_False;
}

Sequence< OUString> HwpImportFilter::getSupportedServiceNames( void ) throw(::com::sun::star::uno::RuntimeException)
{
    Sequence< OUString > seq(1);
    seq.getArray()[0] = OUString(RTL_CONSTASCII_USTRINGPARAM( SERVICE_NAME ));
    return seq;
}

/////////////////////////////////////////////////////////////////////////////////////
// The below three C functions are nessesary for this shared library is treaded as
// UNO component library.
/////////////////////////////////////////////////////////////////////////////////////
extern "C"
{

    void SAL_CALL component_getImplementationEnvironment(
        const sal_Char ** ppEnvTypeName, uno_Environment **  )
    {
        *ppEnvTypeName = CPPU_CURRENT_LANGUAGE_BINDING_NAME;
    }

    void * SAL_CALL component_getFactory( const sal_Char * pImplName, void * pServiceManager, void *  )
    {
        void * pRet = 0;

        if (pServiceManager )
        {
            Reference< XSingleServiceFactory > xRet;
            Reference< XMultiServiceFactory > xSMgr = reinterpret_cast< XMultiServiceFactory * > ( pServiceManager );

            OUString aImplementationName = OUString::createFromAscii( pImplName );

            if (aImplementationName == OUString(RTL_CONSTASCII_USTRINGPARAM( IMPLEMENTATION_NAME )) )
            {
                xRet = createSingleFactory( xSMgr, aImplementationName,
                                            HwpImportFilter_CreateInstance,
                                            HwpImportFilter::getSupportedServiceNames_Static() );
            }
            if (xRet.is())
            {
                xRet->acquire();
                pRet = xRet.get();
            }
        }

        return pRet;
    }
}

#endif 

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
