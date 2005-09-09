/************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: BoundSheet.java,v $
 *
 *  $Revision: 1.5 $
 *
 *  last change: $Author: rt $ $Date: 2005-09-09 10:57:54 $
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

import java.io.IOException;
import java.io.UnsupportedEncodingException;
import java.io.OutputStream;
import java.io.InputStream;

import org.openoffice.xmerge.util.Debug;
import org.openoffice.xmerge.util.EndianConverter;
import org.openoffice.xmerge.converter.xml.sxc.pexcel.PocketExcelConstants;

/**
 * Represents a BoundSheet Record which describes the name of a worksheet 
 */
public class BoundSheet implements BIFFRecord {

    private byte	reserved;
    private byte	cch; 
    private byte[]	sheetName;
    
    /**
     * Constructs a pocket Excel Document assigns it the document name passed in
      *
     * @param	name name of the worksheet represented	
     */
    public BoundSheet(String name) throws IOException {
        setSheetName(name);	
        reserved = 0;
    }

    /**
      * Constructs a pocket Excel Document from the
      * <code>InputStream</code> and assigns it the document name passed in
      *
      * @param	is InputStream containing a Pocket Excel Data file.
      */
    public BoundSheet(InputStream is) throws IOException {
        read(is);	
    }

    /**
      * Sets the worksheet name. The sheetname length must be doubled as the
     * String is stored in unicode format. 
      *
      * @param	sheetname	worksheet name 
      */
    void setSheetName(String sheetName) throws IOException {
        this.cch		= (byte) sheetName.length();
        this.sheetName	= new byte[cch*2];
        this.sheetName	= sheetName.getBytes("UTF-16LE");
    }
    
    public String getSheetName() {
        String name;

        try {
            name = new String(sheetName, "UTF-16LE");
        } catch (UnsupportedEncodingException e){
            name = "unknown";
        }
        return name;
    }
 
     /**
     * Get the hex code for this particular <code>BIFFRecord</code> 
     *
     * @return the hex code for <code>BoundSheet</code>
     */
    public short getBiffType() {
        return PocketExcelConstants.BOUND_SHEET;
    }   
    
     /**
     * Write this particular <code>BIFFRecord</code> to the <code>OutputStream</code>
     *
     * @param ouput the <code>OutputStream</code>
     */    
    public void write(OutputStream output) throws IOException {

        output.write(getBiffType());
        output.write(reserved);
        output.write(cch);
        output.write(sheetName);

        Debug.log(Debug.TRACE,"Writing BoundSheet record");
    }
    
    /**
      * Reads a BoundSheet from the <code>InputStream</code> The byte array
     * must be twice the size of the String as it uses unicode.
      *
      * @param	is InputStream containing the record data 
      */
    public int read(InputStream input) throws IOException {
    
        reserved			= (byte) input.read();
        cch					= (byte) input.read();
        int numOfBytesRead = 2;
        int strLen = cch*2;
        sheetName	= new byte[strLen];
        numOfBytesRead		+= input.read(sheetName, 0, strLen);        
        
           Debug.log(Debug.TRACE,"\tReserved : "+ reserved + 
                            " cch : " + cch +
                            " sheetName : " + new String(sheetName,"UTF-16LE"));          

        return numOfBytesRead;
    }
    
}
