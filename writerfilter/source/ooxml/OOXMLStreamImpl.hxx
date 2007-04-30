/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: OOXMLStreamImpl.hxx,v $
 *
 *  $Revision: 1.3 $
 *
 *  last change: $Author: fridrich_strba $ $Date: 2007-04-30 16:32:23 $
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
#ifndef INCLUDED_OOXML_STREAM_IMPL_HXX
#define INCLUDED_OOXML_STREAM_IMPL_HXX

#ifndef INCLUDED_OOXML_DOCUMENT_HXX
#include <ooxml/OOXMLDocument.hxx>
#endif

#ifndef _COMPHELPER_STORAGEHELPER_HXX
#include <comphelper/storagehelper.hxx>
#endif

#ifndef _COM_SUN_STAR_EMBED_XRELATIONSHIPACCESS_HPP_
#include <com/sun/star/embed/XRelationshipAccess.hpp>
#endif

#ifndef _COM_SUN_STAR_IO_XSTREAM_HPP_
#include <com/sun/star/io/XStream.hpp>
#endif

namespace ooxml
{

using namespace com::sun::star;

class OOXMLStreamImpl : public OOXMLStream
{
protected:
    uno::Reference<uno::XComponentContext> mxContext;
    uno::Reference<embed::XStorage> mxStorage;
    uno::Reference<io::XInputStream> mxInputStream;
    uno::Reference<embed::XRelationshipAccess> mxRelationshipAccess;
    uno::Reference<io::XStream> mxDocumentStream;

    rtl::OUString msPath;

    StreamType_t mnStreamType;
    
public:
    typedef boost::shared_ptr<OOXMLStreamImpl> Pointer_t;

    OOXMLStreamImpl
    (OOXMLStreamImpl & rStream, StreamType_t nType);
    OOXMLStreamImpl
    (uno::Reference<uno::XComponentContext> xContext,
     uno::Reference<embed::XStorage> xStorage, 
     StreamType_t nType);

    virtual ~OOXMLStreamImpl();

    void init();

    OOXMLStream::Pointer_t getSubStream(StreamType_t nStreamType);

    virtual uno::Reference<xml::sax::XParser> getParser();
    virtual uno::Reference<io::XInputStream> getInputStream();
    virtual uno::Reference<uno::XComponentContext> getContext();
};
}
#endif // INCLUDED_OOXML_STREAM_IMPL_HXX
