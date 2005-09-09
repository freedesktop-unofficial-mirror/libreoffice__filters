/************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: Selection.java,v $
 *
 *  $Revision: 1.5 $
 *
 *  last change: $Author: rt $ $Date: 2005-09-09 11:02:10 $
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
import java.awt.Point;

import org.openoffice.xmerge.util.Debug;
import org.openoffice.xmerge.util.EndianConverter;
import org.openoffice.xmerge.converter.xml.sxc.pexcel.PocketExcelConstants;


/**
 * Represents a BIFF Record that describes the selected area of a worksheet
 */
public class Selection implements BIFFRecord {

    private byte[] rwTop		= new byte[2];
    private byte   colLeft;
    private byte[] rwBottom		= new byte[2];
    private byte   colRight;
    private byte[] rwActive		= new byte[2];
    private byte   colActive;
    
    /**
     * Default Constructor
     */
    public Selection() {
        this.rwTop			= EndianConverter.writeShort((short) 0);
        this.colLeft		= 0; 
        this.rwBottom		= EndianConverter.writeShort((short) 0);
        this.colRight		= 0; 
        this.rwActive		= EndianConverter.writeShort((short) 0);
        this.colActive		= 0; 
        
    }

    /**
     * Constructs a Selection Record from the <code>InputStream</code> 
     *
     * @param	is InputStream containing a Pocket Excel Data file.
     */
    public Selection(InputStream is) throws IOException {
        read(is);	
    }

    /**
     * Get the hex code for this particular <code>BIFFRecord</code> 
     *
     * @return the hex code for <code>Selection</code>
     */
    public short getBiffType() {
        return PocketExcelConstants.CURRENT_SELECTION;
    }
    
    /**
     * Get the hex code for this particular <code>BIFFRecord</code> 
     *
     * @return the hex code for <code>Selection</code>
     */
    public Point getActiveCell() {
        Point p = new Point(colActive, EndianConverter.readShort(rwActive));
        return p;
    } 
    
    /**
     * Get the hex code for this particular <code>BIFFRecord</code> 
     *
     * @return the hex code for <code>Selection</code>
     */
    public void setActiveCell(Point p) {

        colActive = (byte) p.getX();
        rwActive = EndianConverter.writeShort((short) p.getY());
    }
    
    /**
     * Reads a Selection Record from the <code>InputStream</code> 
     *
     * @param	is InputStream containing a Pocket Excel Data file.
     */
    public int read(InputStream input) throws IOException {
        
        int numOfBytesRead	= input.read(rwTop);
        colLeft				+= (byte) input.read();
        numOfBytesRead		+= input.read(rwBottom);
        colRight			+= (byte) input.read();
        numOfBytesRead		+= input.read(rwActive);
        colActive			+= (byte) input.read();
        numOfBytesRead += 3;
                
        Debug.log(Debug.TRACE,"\trwTop : "+ EndianConverter.readShort(rwTop) + 
                            " colLeft : " + colLeft +
                            " rwBottom : " + EndianConverter.readShort(rwBottom) +
                            " colRight : "+ colRight + 
                            " rwActive : " + EndianConverter.readShort(rwActive) +
                            " colActive : " + colActive);
        
        return numOfBytesRead;                
    }
    
    public void write(OutputStream output) throws IOException {

        output.write(getBiffType());
        output.write(rwTop);
        output.write(colLeft);
        output.write(rwBottom);
        output.write(colRight);
        output.write(rwActive);
        output.write(colActive);

        Debug.log(Debug.TRACE,"Writing Selection record");
    }
    
}
