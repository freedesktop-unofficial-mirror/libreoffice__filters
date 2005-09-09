/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: XInputStreamToInputStreamAdapter.java,v $
 *
 *  $Revision: 1.2 $
 *
 *  last change: $Author: rt $ $Date: 2005-09-09 11:47:34 $
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
//package com.sun.star.lib.uno.adapter;



import java.io.IOException;
import com.sun.star.io.XInputStream;
import java.io.InputStream;

/**
 * The <code>XInputStreamToInputStreamAdapter</code> wraps
 * the UNO <code>XInputStream</code> object in a Java
 * <code>InputStream</code>.  This allows users to access
 * an <code>XInputStream</code> as if it were an
 * <code>InputStream</code>.
 *
 * @author  Brian Cameron
 */
public class XInputStreamToInputStreamAdapter extends InputStream {

    /** 
     *  Internal handle to the XInputStream
     */
    private XInputStream xin;
 
    /**
     *  Constructor.
     *
     *  @param  in  The <code>XInputStream</code> to be 
     *              accessed as an <code>InputStream</code>.
     */
    public XInputStreamToInputStreamAdapter (XInputStream in) {
        xin = in;
    }

    public int available() throws IOException {

        int bytesAvail;

        try {
            bytesAvail = xin.available();
        } catch (Exception e) {
            throw new IOException(e.toString());
        }

        return(bytesAvail);
    }

    public void close() throws IOException {
        try {
            xin.closeInput();
        } catch (Exception e) {
            throw new IOException(e.toString());
        }
    }

    public int read () throws IOException {	
        byte [][] tmp = new byte [1][1]; 
    //System.out.println("read1\n");
        try {
            long bytesRead = xin.readBytes(tmp, 1);
      
            if (bytesRead <= 0) {
               return (-1);
            } else {
        int tmpInt = tmp[0][0];
        if (tmpInt< 0 ){
            tmpInt = 256 +tmpInt;
        }
                return(tmpInt);
            }

        } catch (Exception e) {
            throw new IOException(e.toString());
        }
    }

    public int read (byte[] b) throws IOException {
    
        byte [][] tmp = new byte [1][b.length]; 
        int bytesRead;
    //System.out.println("read2\n");
        try {
            bytesRead = xin.readBytes(tmp, b.length);
            if (bytesRead <= 0) {
                return(-1);
            } else if (bytesRead < b.length) {
                System.arraycopy(tmp[0], 0, b, 0, bytesRead);
            } else {
                System.arraycopy(tmp[0], 0, b, 0, b.length);
            }
        } catch (Exception e) {
            throw new IOException(e.toString());
        }

        return (bytesRead);
    }

    public int read(byte[] b, int off, int len) throws IOException {
        int count = 0;
        byte [][] tmp = new byte [1][b.length];
    //System.out.println("read3\n");
        try {
            long bytesRead = xin.readBytes(tmp,len);
            // Casting bytesRead to an int is okay, since the user can
            // only pass in an integer length to read, so the bytesRead 
            // must <= len.
            //
            if (bytesRead <= 0) {
                return(-1);
        } else if (bytesRead < len) {
        System.arraycopy(tmp[0], 0, b, off, (int)bytesRead);
        } else {
                System.arraycopy(tmp[0], 0, b, off, len);
        }
        
        return ((int)bytesRead);
        
        
        } catch (Exception e) {
            throw new IOException("reader error: "+e.toString());
        }
    }

    public long skip(long n) throws IOException {

        int avail;
        long tmpLongVal = n;
        int  tmpIntVal;

        try {
            avail = xin.available();
        } catch (Exception e) {
            throw new IOException(e.toString());
        }

        do {
            if (tmpLongVal >= Integer.MAX_VALUE) {
               tmpIntVal = Integer.MAX_VALUE;
            } else {
               // Casting is safe here.
               tmpIntVal = (int)tmpLongVal;
            }
            tmpLongVal -= tmpIntVal;
 
            try {
                xin.skipBytes(tmpIntVal);
            } catch (Exception e) {
                throw new IOException(e.toString());
            }
        } while (tmpLongVal > 0);

        if (avail < n) {
            return(avail);
        } else {
            return(n);
        }
    }

   /**
    *  Tests if this input stream supports the mark and reset methods.
    *  The markSupported method of
    *  <code>XInputStreamToInputStreamAdapter</code> returns false.
    *
    *  @returns  false
    */
    public boolean markSupported() {
       return false;
    }

    public void mark(int readlimit) {
        // Not supported.
    }

    public void reset() throws IOException {
        // Not supported.
    }
}

