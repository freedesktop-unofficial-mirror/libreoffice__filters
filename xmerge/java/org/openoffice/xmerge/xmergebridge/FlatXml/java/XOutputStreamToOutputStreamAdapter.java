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

//package com.sun.star.lib.uno.adapter;

import java.io.IOException;
import com.sun.star.io.XOutputStream;
import java.io.OutputStream;

/**
 * The <code>XOutputStreamToOutputStreamAdapter</code> wraps
 * the UNO <code>XOutputStream</code> object in a Java
 * <code>OutputStream</code>.  This allows users to access
 * an <code>XOutputStream</code> as if it were an
 * <code>OutputStream</code>.
 *
 * @author  Brian Cameron
 */
public class XOutputStreamToOutputStreamAdapter extends OutputStream {

    /**
     *  Internal handle to the XInputStream
     */
    XOutputStream xout;

    /**
     *  Constructor.
     *
     *  @param  out  The <code>XOutputStream</code> to be
     *          accessed as an <code>OutputStream</code>.
     */
    XOutputStreamToOutputStreamAdapter(XOutputStream out) {
        xout = out;
    }

    public void close() throws IOException {
        try {
            xout.closeOutput();
        } catch (Exception e) {
            throw new IOException(e.toString());
        }
    }

    public void flush() throws IOException {
        try {
            xout.flush();
        } catch (Exception e) {
            throw new IOException(e.toString());
        }
    }

    public void write(byte[] b) throws IOException {
    //System.out.println("write1\n");
    try {	   
            xout.writeBytes(b);
        } catch (Exception e) {
            throw new IOException(e.toString());
        }
    }

    public void write(byte[] b, int off, int len) throws IOException {
    
        byte[] tmp = new byte[len];
    //System.out.println("write2\n");
        // Copy the input array into a temp array, and write it out.
        //
        System.arraycopy(b, off, tmp, 0, len);
        
        try {
            xout.writeBytes(tmp);
        } catch (Exception e) {
            throw new IOException(e.toString());
        }
    }

    public void write(int b) throws IOException {
    
        byte [] oneByte = new byte [1];
        oneByte[0] = (byte) b;
    //System.out.println("write3\n");
        try {
            xout.writeBytes(oneByte);
        } catch (Exception e) {
            throw new IOException(e.toString());
        }
    }
}





