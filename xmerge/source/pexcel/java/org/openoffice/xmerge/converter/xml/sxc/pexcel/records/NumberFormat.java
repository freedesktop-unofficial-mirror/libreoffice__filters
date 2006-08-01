/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: NumberFormat.java,v $
 *
 *  $Revision: 1.3 $
 *
 *  last change: $Author: ihi $ $Date: 2006-08-01 13:03:37 $
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

package org.openoffice.xmerge.converter.xml.sxc.pexcel.records;

import java.io.DataInputStream;
import java.io.OutputStream;
import java.io.InputStream;
import java.io.IOException;

import org.openoffice.xmerge.util.Debug;
import org.openoffice.xmerge.util.EndianConverter;
import org.openoffice.xmerge.converter.xml.sxc.pexcel.PocketExcelConstants;


/**
 * Represents a BIFF Record describing a number format 
 */
public class NumberFormat implements BIFFRecord {

    private byte cce;
    private byte[] rgch;
    
    /**
     * Constructs a NumberFormat Record from the <code>InputStream</code> 
     *
     * @param	is InputStream containing the record data 
     */
    public NumberFormat(InputStream is) throws IOException {
        read(is);
    }

    /**
     * Get the hex code for this particular <code>BIFFRecord</code> 
     *
     * @return the hex code for <code>NumberFormat</code>
     */
    public short getBiffType() {
        return PocketExcelConstants.NUMBER_FORMAT;
    }
    
    /**
     * Reads the NumberFormat from the <code>InputStream</code> Byte array
     * containg strings are doubled in length becuse they use unicode
     *
     * @return the total number of bytes read 
     */
    public int read(InputStream input) throws IOException {

        cce = (byte) input.read();
        int numOfBytesRead = 1;
            
        rgch = new byte[cce*2];
        numOfBytesRead	+= input.read(rgch, 0, cce*2);        
    
        Debug.log(Debug.TRACE, "\tcce : "+ cce + 
                            " rgch : " + new String(rgch,"UTF-16LE"));
        
        return numOfBytesRead;
    }
    
    public void write(OutputStream output) throws IOException {

        output.write(getBiffType());
        output.write(cce);
        output.write(rgch);

        Debug.log(Debug.TRACE,"Writing NumberFormat record");	
    }
    
}
