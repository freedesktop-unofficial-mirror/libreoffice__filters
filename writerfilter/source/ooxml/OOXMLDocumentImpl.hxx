/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: OOXMLDocumentImpl.hxx,v $
 *
 *  $Revision: 1.6 $
 *
 *  last change: $Author: hbrinkm $ $Date: 2007-06-04 08:45:42 $
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
#ifndef INCLUDED_OOXML_DOCUMENT_IMPL_HXX
#define INCLUDED_OOXML_DOCUMENT_IMPL_HXX

#ifndef INCLUDED_OOXML_DOCUMENT_HXX
#include <ooxml/OOXMLDocument.hxx>
#endif

namespace ooxml
{

class OOXMLDocumentImpl : public OOXMLDocument
{
    OOXMLStream::Pointer_t mpStream;
    rtl::OUString msXNoteId;

protected:
    virtual void resolveSubStream(Stream & rStream, 
                                  OOXMLStream::StreamType_t nType);

    doctok::Reference<Stream>::Pointer_t 
    getSubStream(const rtl::OUString & rId);

    doctok::Reference<Stream>::Pointer_t
    getXNoteStream(OOXMLStream::StreamType_t nType, 
                   const rtl::OUString & rNoteId);

    void setXNoteId(const rtl::OUString & rId);

public:
    OOXMLDocumentImpl(OOXMLStream::Pointer_t pStream);
    virtual ~OOXMLDocumentImpl();
    
    virtual void resolve(Stream & rStream);

    virtual string getType() const;

    virtual void resolveFootnote(Stream & rStream, 
                                 const rtl::OUString & rNoteId);
    virtual void resolveEndnote(Stream & rStream, 
                                const rtl::OUString & rNoteId);
    virtual void resolveHeader(Stream & rStream,
                               const sal_Int32 type,
                               const rtl::OUString & rId);
    virtual void resolveFooter(Stream & rStream,
                               const sal_Int32 type,
                               const rtl::OUString & rId);

    virtual void resolveComment(Stream & rStream, const rtl::OUString & rId);
};
}
#endif // OOXML_DOCUMENT_IMPL_HXX
