/*************************************************************************
 *
 *  $RCSfile: xmlfiltercommon.hxx,v $
 *
 *  $Revision: 1.4 $
 *
 *  last change: $Author: obo $ $Date: 2004-04-29 16:12:59 $
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
 *  Source License Version 1.1 (the License); You may not use this file
 *  except in compliance with the License. You may obtain a copy of the
 *  License at http://www.openoffice.org/license.html.
 *
 *  Software provided under this License is provided on an AS IS basis,
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
#ifndef _XMLFILTERCOMMON_HXX_
#define _XMLFILTERCOMMON_HXX_

#ifndef _COM_SUN_STAR_LANG_XCOMPONENT_HPP_
#include <com/sun/star/lang/XComponent.hpp>
#endif

#ifndef _COM_SUN_STAR_LANG_XMULTISERVICEFACTORY_HPP_
#include <com/sun/star/lang/XMultiServiceFactory.hpp>
#endif

#ifndef _COM_SUN_STAR_CONTAINER_XHIERARCHICALNAME_HPP_
#include <com/sun/star/container/XHierarchicalName.hpp>
#endif

#ifndef _COM_SUN_STAR_CONTAINER_XNAMECONTAINER_HPP_
#include <com/sun/star/container/XNameContainer.hpp>
#endif

#ifndef _COM_SUN_STAR_IO_XINPUTSTREAM_HPP_
#include <com/sun/star/io/XInputStream.hpp>
#endif

#ifndef _COM_SUN_STAR_IO_XOUTPUTSTREAM_HPP_
#include <com/sun/star/io/XOutputStream.hpp>
#endif

#include <vector>

// --------------------------------------------------------------------

extern ::rtl::OUString string_encode( const ::rtl::OUString & rText );
extern ::rtl::OUString xmlname_encode( const ::rtl::OUString & rText );
extern ::rtl::OUString string_decode( const ::rtl::OUString & rText );

// --------------------------------------------------------------------

extern bool isFileURL( const ::rtl::OUString & rURL );

// --------------------------------------------------------------------

bool copyStreams( ::com::sun::star::uno::Reference< ::com::sun::star::io::XInputStream > xIS, ::com::sun::star::uno::Reference< ::com::sun::star::io::XOutputStream > xOS );
bool createDirectory( ::rtl::OUString& rURL );

// --------------------------------------------------------------------

class filter_info_impl
{
public:
    rtl::OUString	maFilterName;
    rtl::OUString	maType;
    rtl::OUString	maDocumentService;
    rtl::OUString	maFilterService;
    rtl::OUString	maInterfaceName;
    rtl::OUString	maComment;
    rtl::OUString	maExtension;
    rtl::OUString	maDTD;
    rtl::OUString	maExportXSLT;
    rtl::OUString	maImportXSLT;
    rtl::OUString	maImportTemplate;
    rtl::OUString	maDocType;

    sal_Int32		maFlags;
    sal_Int32		maFileFormatVersion;
    sal_Int32		mnDocumentIconID;

    sal_Bool        mbReadonly;
    filter_info_impl();
    filter_info_impl( const filter_info_impl& rInfo );
    int operator==( const filter_info_impl& ) const;

    com::sun::star::uno::Sequence< rtl::OUString > getFilterUserData() const;
};

// --------------------------------------------------------------------

struct application_info_impl
{
    rtl::OUString	maDocumentService;
    rtl::OUString	maDocumentUIName;
    rtl::OUString	maXMLImporter;
    rtl::OUString	maXMLExporter;

    application_info_impl( const sal_Char * pDocumentService, ResId& rUINameRes, const sal_Char * mpXMLImporter, const sal_Char * mpXMLExporter );
};

// --------------------------------------------------------------------

extern std::vector< application_info_impl* >& getApplicationInfos();
extern rtl::OUString getApplicationUIName( const rtl::OUString& rServiceName );
extern const application_info_impl* getApplicationInfo( const rtl::OUString& rServiceName );

extern ResMgr* getXSLTDialogResMgr();

#define RESID(x) ResId(x, getXSLTDialogResMgr() )

#endif
