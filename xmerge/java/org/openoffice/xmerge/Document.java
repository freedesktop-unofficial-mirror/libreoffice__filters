/************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: Document.java,v $
 *
 *  $Revision: 1.2 $
 *
 *  last change: $Author: rt $ $Date: 2005-09-09 10:19:51 $
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

package org.openoffice.xmerge;

import java.io.OutputStream;
import java.io.InputStream;
import java.io.IOException;

/**
 *  <p>A <code>Document</code> represents any <code>Document</code>
 *  to be converted and the resulting <code>Document</code> from any
 *  conversion.</p>
 *
 *  <p>It is created by the <code>PluginFactory</code> object's {@link
 *  org.openoffice.xmerge.PluginFactory#createOfficeDocument
 *  createOfficeDocument} method or the {@link
 *  org.openoffice.xmerge.PluginFactory#createDeviceDocument
 *  createDeviceDocument} method.</p>
 *
 *  @author  Herbie Ong
 *  @see     org.openoffice.xmerge.PluginFactory
 */
public interface Document {

    /**
     *  <p>Writes out the <code>Document</code> content to the specified
     *  <code>OutputStream</code>.</p>
     *
     *  <p>This method may not be thread-safe.
     *  Implementations may or may not synchronize this
     *  method.  User code (i.e. caller) must make sure that
     *  calls to this method are thread-safe.</p>
     *
     *  @param  os  <code>OutputStream</code> to write out the
     *              <code>Document</code> content.
     *
     *  @throws  IOException  If any I/O error occurs.
     */
    public void write(OutputStream os) throws IOException;


    /**
     *  <p>Reads the content from the <code>InputStream</code> into
     *  the <code>Document</code>.</p>
     *
     *  <p>This method may not be thread-safe.
     *  Implementations may or may not synchronize this
     *  method.  User code (i.e. caller) must make sure that
     *  calls to this method are thread-safe.</p>
     *
     *  @param  is  <code>InputStream</code> to read in the
     *              <code>Document</code> content.
     *
     *  @throws  IOException  If any I/O error occurs.
     */
     public void read(InputStream is) throws IOException;


    /**
     *  Returns the <code>Document</code> name with no file extension.
     *
     *  @return  The <code>Document</code> name with no file extension.
     */
    public String getName();


    /**
     *  Returns the <code>Document</code> name with file extension.
     *
     *  @return  The <code>Document</code> name with file extension.
     */
    public String getFileName();
}

