/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: saxbuilder.hxx,v $
 *
 *  $Revision: 1.3 $
 *
 *  last change: $Author: rt $ $Date: 2005-09-09 10:05:42 $
 *
 *  The Contents of this file are made available subject to
 *  the terms of GNU Lesser General Public License Version 2.1.
 *
 *
 *    GNU Lesser General Public License Version 2.1
 *    =============================================
 *    Copyright 2005 by Sun Microsystems, Inc.
 *    901 San Antonio Road, Palo Alto, CA 94303, USA
 *
 *    This library is free software; you can redistribute it and/or
 *    modify it under the terms of the GNU Lesser General Public
 *    License version 2.1, as published by the Free Software Foundation.
 *
 *    This library is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *    Lesser General Public License for more details.
 *
 *    You should have received a copy of the GNU Lesser General Public
 *    License along with this library; if not, write to the Free Software
 *    Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 *    MA  02111-1307  USA
 *
 ************************************************************************/

#ifndef _SAXBUILDER_HXX
#define _SAXBUILDER_HXX

#include <stack>
#include <map>

#include <sal/types.h>
#include <cppuhelper/implbase3.hxx>
#include <com/sun/star/uno/Reference.h>
#include <com/sun/star/uno/Sequence.h>

#include <com/sun/star/uno/XInterface.hpp>
#include <com/sun/star/uno/Exception.hpp>
#include <com/sun/star/xml/dom/XSAXDocumentBuilder.hpp>
#include <com/sun/star/xml/dom/SAXDocumentBuilderState.hpp>
#include <com/sun/star/xml/dom/XDocument.hpp>
#include <com/sun/star/xml/dom/XDocumentFragment.hpp>
#include <com/sun/star/xml/sax/XDocumentHandler.hpp>
#include <com/sun/star/xml/sax/XLocator.hpp>
#include <com/sun/star/xml/sax/XAttributeList.hpp>
#include <com/sun/star/lang/XServiceInfo.hpp>
#include <com/sun/star/lang/XSingleServiceFactory.hpp>
#include <com/sun/star/lang/XMultiServiceFactory.hpp>

#include "libxml/tree.h"

using namespace rtl;
using namespace com::sun::star::uno;
using namespace com::sun::star::lang;
using namespace com::sun::star::xml::dom;
using namespace com::sun::star::xml::sax;

namespace DOM
{

    typedef std::stack< Reference< XNode > > NodeStack;
    typedef std::map< OUString, OUString > NSMap;
    typedef std::map< OUString, OUString > AttrMap;
    typedef std::stack< NSMap > NSStack;
    
    class  CSAXDocumentBuilder
        : public ::cppu::WeakImplHelper3< XDocumentHandler, XSAXDocumentBuilder, XServiceInfo >
    {

    private:
        SAXDocumentBuilderState m_aState;
        NodeStack m_aNodeStack;
        NSStack m_aNSStack;

        OUString resolvePrefix(const OUString& aPrefix);

        Reference< XDocument > m_aDocument;
        Reference< XDocumentFragment > m_aFragment;
        Reference< XLocator > m_aLocator;
        const Reference< XMultiServiceFactory > m_aServiceManager;
        
    public:

        // call for factory
        static Reference< XInterface > getInstance(const Reference < XMultiServiceFactory >& xFactory);

        // static helpers for service info and component management
        static const char* aImplementationName;
        static const char* aSupportedServiceNames[];
        static OUString _getImplementationName();
        static Sequence< OUString > _getSupportedServiceNames();
        static Reference< XInterface > _getInstance(const Reference< XMultiServiceFactory >& rSMgr);

        CSAXDocumentBuilder(const Reference< XMultiServiceFactory >& mgr);
        
        // XServiceInfo
        virtual OUString SAL_CALL getImplementationName()
            throw (RuntimeException);
        virtual sal_Bool SAL_CALL supportsService(const OUString& ServiceName)
            throw (RuntimeException);
        virtual Sequence< OUString > SAL_CALL getSupportedServiceNames ()
            throw (RuntimeException);

        // XDocumentHandler
        virtual void SAL_CALL startDocument()
            throw( com::sun::star::xml::sax::SAXException );
        virtual void SAL_CALL endDocument()
            throw( com::sun::star::xml::sax::SAXException );
        virtual void SAL_CALL startElement( const OUString& aName,
             const Reference< XAttributeList >& xAttribs )
            throw( com::sun::star::xml::sax::SAXException );
        virtual void SAL_CALL endElement( const OUString& aName )
            throw( com::sun::star::xml::sax::SAXException );
        virtual void SAL_CALL characters( const OUString& aChars )
            throw( com::sun::star::xml::sax::SAXException );
        virtual void SAL_CALL ignorableWhitespace( const OUString& aWhitespaces )
            throw( com::sun::star::xml::sax::SAXException );
        virtual void SAL_CALL processingInstruction( const OUString& aTarget,
             const OUString& aData )
            throw( com::sun::star::xml::sax::SAXException );
        virtual void SAL_CALL setDocumentLocator( const Reference< XLocator >& xLocator )
            throw( com::sun::star::xml::sax::SAXException );
    
    
        // XSAXDocumentBuilder
        virtual SAXDocumentBuilderState SAL_CALL getState() 
            throw (RuntimeException);
        virtual void SAL_CALL reset() 
            throw (RuntimeException);
        virtual Reference< XDocument > SAL_CALL getDocument()
            throw (RuntimeException);
        virtual Reference< XDocumentFragment > SAL_CALL getDocumentFragment()
            throw (RuntimeException);
        virtual void SAL_CALL startDocumentFragment(const Reference< XDocument >& ownerDoc)
            throw (RuntimeException);
        virtual void SAL_CALL endDocumentFragment()
            throw (RuntimeException);
            

    };
}

#endif
