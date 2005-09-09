/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: xpathapi.hxx,v $
 *
 *  $Revision: 1.3 $
 *
 *  last change: $Author: rt $ $Date: 2005-09-09 10:08:46 $
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

#ifndef _XPATHAPI_HXX
#define _XPATHAPI_HXX

#include <map>
#include <vector>

#include <sal/types.h>
#include <cppuhelper/implbase2.hxx>
#include <com/sun/star/uno/Reference.h>
#include <com/sun/star/uno/Sequence.h>

#include <com/sun/star/uno/XInterface.hpp>
#include <com/sun/star/uno/Exception.hpp>
#include <com/sun/star/xml/xpath/XXPathAPI.hpp>
#include <com/sun/star/xml/dom/XNode.hpp>
#include <com/sun/star/xml/dom/XNodeList.hpp>
#include <com/sun/star/xml/xpath/XXPathAPI.hpp>
#include <com/sun/star/xml/xpath/XXPathObject.hpp>
#include <com/sun/star/xml/xpath/XXPathExtension.hpp>
#include <com/sun/star/xml/xpath/Libxml2ExtensionHandle.hpp>
#include <com/sun/star/lang/XServiceInfo.hpp>
#include <com/sun/star/lang/XSingleServiceFactory.hpp>
#include <com/sun/star/lang/XMultiServiceFactory.hpp>
#include <com/sun/star/lang/XUnoTunnel.hpp>

#include "libxml/tree.h"

using namespace rtl;
using namespace com::sun::star::uno;
using namespace com::sun::star::lang;
using namespace com::sun::star::xml::dom;
using namespace com::sun::star::xml::xpath;

namespace XPath
{
    typedef std::map<OUString, OUString> nsmap_t;
    typedef std::vector< Reference<XXPathExtension> > extensions_t;

    class  CXPathAPI
        : public ::cppu::WeakImplHelper2< XXPathAPI, XServiceInfo >
    {

    private:
        nsmap_t m_nsmap;
        const Reference < XMultiServiceFactory >& m_aFactory;
        extensions_t m_extensions;

    public:
        // ctor
        CXPathAPI(const Reference< XMultiServiceFactory >& rSMgr);

        // call for factory
        static Reference< XInterface > getInstance(const Reference < XMultiServiceFactory >& xFactory);

        // static helpers for service info and component management
        static const char* aImplementationName;
        static const char* aSupportedServiceNames[];
        static OUString _getImplementationName();
        static Sequence< OUString > _getSupportedServiceNames();
        static Reference< XInterface > _getInstance(const Reference< XMultiServiceFactory >& rSMgr);

        // XServiceInfo
        virtual OUString SAL_CALL getImplementationName()
            throw (RuntimeException);
        virtual sal_Bool SAL_CALL supportsService(const OUString& ServiceName)
            throw (RuntimeException);
        virtual Sequence< OUString > SAL_CALL getSupportedServiceNames ()
            throw (RuntimeException);


        // --- XXPathAPI ---

        virtual void SAL_CALL CXPathAPI::registerNS(const OUString& aPrefix, const OUString& aURI)
            throw (RuntimeException);

        virtual void SAL_CALL CXPathAPI::unregisterNS(const OUString& aPrefix, const OUString& aURI)
            throw (RuntimeException);

        /**
        Use an XPath string to select a nodelist.
        */
        virtual Reference< XNodeList > SAL_CALL selectNodeList(const Reference< XNode >& contextNode, const OUString& str)
            throw (RuntimeException);

        /**
        Use an XPath string to select a nodelist.
        */
        virtual Reference< XNodeList > SAL_CALL selectNodeListNS(const Reference< XNode >& contextNode, const OUString& str, const Reference< XNode >&  namespaceNode)
            throw (RuntimeException);

        /**
        Use an XPath string to select a single node.
        */
        virtual Reference< XNode > SAL_CALL selectSingleNode(const Reference< XNode >& contextNode, const OUString& str)
            throw (RuntimeException);

        /**
        Use an XPath string to select a single node.
        */
        virtual Reference< XNode > SAL_CALL selectSingleNodeNS(const Reference< XNode >& contextNode, const OUString& str, const Reference< XNode >&  namespaceNode)
            throw (RuntimeException);

        virtual Reference< XXPathObject > SAL_CALL eval(const Reference< XNode >& contextNode, const OUString& str)
            throw (RuntimeException);

        virtual Reference< XXPathObject > SAL_CALL evalNS(const Reference< XNode >& contextNode, const OUString& str, const Reference< XNode >&  namespaceNode)
            throw (RuntimeException);

        virtual void SAL_CALL registerExtension(const OUString& aName) throw (RuntimeException);
        virtual void SAL_CALL registerExtensionInstance(const Reference< XXPathExtension>& aExtension) throw (RuntimeException);
     

    };
}

#endif
