/************************************************************************
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
 *  Source License Version 1.1 (the "License"); You may not use this file
 *  except in compliance with the License. You may obtain a copy of the
 *  License at http://www.openoffice.org/license.html.
 *
 *  Software provided under this License is provided on an "AS IS" basis,
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

package org.openoffice.xmerge.converter.xml.sxc.pexcel.Records;

import java.io.DataInputStream;
import java.io.OutputStream;
import java.io.InputStream;
import java.io.IOException;

import org.openoffice.xmerge.util.Debug;
import org.openoffice.xmerge.util.EndianConverter;

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
     * Constructor
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
        return PocketExcelBiffConstants.CURRENT_SELECTION;
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

        output.write(PocketExcelBiffConstants.CURRENT_SELECTION);
        output.write(rwTop);
        output.write(colLeft);
        output.write(rwBottom);
        output.write(colRight);
        output.write(rwActive);
        output.write(colActive);

        Debug.log(Debug.TRACE,"Writing Selection record");
    }
    
}
