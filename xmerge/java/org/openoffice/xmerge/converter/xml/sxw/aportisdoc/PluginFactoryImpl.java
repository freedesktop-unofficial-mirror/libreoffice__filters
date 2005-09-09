/************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: PluginFactoryImpl.java,v $
 *
 *  $Revision: 1.2 $
 *
 *  last change: $Author: rt $ $Date: 2005-09-09 11:14:05 $
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

package org.openoffice.xmerge.converter.xml.sxw.aportisdoc;

import org.openoffice.xmerge.Document;
import org.openoffice.xmerge.ConvertData;
import org.openoffice.xmerge.DocumentMerger;
import org.openoffice.xmerge.DocumentMergerFactory;
import org.openoffice.xmerge.DocumentSerializer;
import org.openoffice.xmerge.DocumentSerializerFactory;
import org.openoffice.xmerge.DocumentDeserializer;
import org.openoffice.xmerge.DocumentDeserializerFactory;
import org.openoffice.xmerge.ConverterCapabilities;
import org.openoffice.xmerge.converter.xml.sxw.SxwPluginFactory;
import org.openoffice.xmerge.converter.palm.PalmDocument;
import org.openoffice.xmerge.util.registry.ConverterInfo;
import java.io.IOException;
import java.io.InputStream;

/**
 *  <p>AportisDoc implementation of the <code>PluginFactory</code>.
 *  This encapsulates conversion of StarWriter XML format to and from
 *  AportisDoc format.</p>
 *
 *  <p>The superclass produces a particular
 *  {@link org.openoffice.xmerge.Document Document}
 *  object, i.e. {@link
 *  org.openoffice.xmerge.converter.xml.sxw.SxwDocument
 *  SxwDocument} that the converters in this class works with.	Thus,
 *  this class only implements the methods that produces the converters,
 *  i.e. {@link
 *  org.openoffice.xmerge.DocumentSerializer
 *  DocumentSerializer} and {@link
 *  org.openoffice.xmerge.DocumentDeserializer
 *  DocumentDeserializer};
 *  as well as the {@link
 *  org.openoffice.xmerge.ConverterCapabilities
 *  ConverterCapabilities} object that is specific to this format
 *  conversion.  That superclass also  produces a {@link
 *  org.openoffice.xmerge.DocumentMerger DocumentMerger}
 *  object, i.e. {@link
 *  org.openoffice.xmerge.converter.xml.sxw.aportisdoc.DocumentMergerImpl
 *  DocumentMergerImpl} which this class derives the functionality.</p>
 *
 *  @author   Herbie Ong
 */
public final class PluginFactoryImpl extends SxwPluginFactory 
    implements DocumentDeserializerFactory, DocumentSerializerFactory,
    DocumentMergerFactory {

    public PluginFactoryImpl (ConverterInfo ci) {
        super(ci);
    }

    /** ConverterCapabilities object for this type of conversion. */
    private final static ConverterCapabilities converterCap =
        new ConverterCapabilitiesImpl();


    /**
     *  Returns an instance of <code>DocumentSerializerImpl</code>,
     *  which is an implementation of the <code>DocumentSerializer</code>
     *  interface.
     *
     *  @param  doc  <code>Document</code> object to be
     *               converted/serialized.
     *
     *  @return  A <code>DocumentSerializerImpl</code> object.
     */
    public DocumentSerializer createDocumentSerializer(Document doc) {

        return new DocumentSerializerImpl(doc);
    }


    /**
     *  Returns an instance of <code>DocumentDeserializerImpl</code>,
     *  which is an implementation of the <code>DocumentDeserializer</code>
     *  interface.
     *
     *  @param  cd   <code>ConvertData</code> object for reading data 
     *               which will be converted back to a
     *               <code>Document</code> object.
     *
     *  @return  A DocumentDeserializerImpl object.
     */
    public DocumentDeserializer createDocumentDeserializer(ConvertData cd) {

        return new DocumentDeserializerImpl(cd);
    }


    /**
     *  Returns an instance of <code>DocumentMergerImpl</code>,
     *  which is an implementation of the <code>DocumentMerger</code>
     *  interface.
     *
     *  @param  doc  <code>Document</code> to merge.
     *
     *  @return  A DocumentMergerImpl object.
     */
    public DocumentMerger createDocumentMerger(Document doc) {

        ConverterCapabilities cc = converterCap;
        DocumentMergerImpl merger = new DocumentMergerImpl(doc, cc);
        return merger;
    }

    public Document createDeviceDocument(String name, InputStream is)
    throws IOException {

        PalmDocument palmDoc = new PalmDocument(is);
        return palmDoc;
    }
}

