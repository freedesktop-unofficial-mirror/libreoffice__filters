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
 * Represents a BIFF Record that describes the number and position of unfrozen
 * panes.
 */
public class Pane implements BIFFRecord {

    private byte[] x		= new byte[2];
    private byte[] y		= new byte[2];
    private byte[] rwTop	= new byte[2];
    private byte[] colLeft	= new byte[2];
    private byte   pnnAcct;
    
    /**
      * Constructs a Pane Record from the <code>InputStream</code>
      *
      * @param	is InputStream containing a Pane record 
      */
    public Pane(InputStream is) throws IOException {
        read(is);	
    }

    /**
     * Get the hex code for this particular <code>BIFFRecord</code> 
     *
     * @return the hex code for <code>Pane</code>
     */
    public short getBiffType() {
        return PocketExcelBiffConstants.PANE_INFO;
    }
    
    public int read(InputStream input) throws IOException {
        
        int numOfBytesRead	= input.read(x);
        numOfBytesRead		+= input.read(y);
        numOfBytesRead		+= input.read(rwTop);
        numOfBytesRead		+= input.read(colLeft);
        pnnAcct				= (byte) input.read();
        numOfBytesRead++;
        
        Debug.log(Debug.TRACE, "\tx : "+ EndianConverter.readShort(x) + 
                            " y : " + EndianConverter.readShort(y) +
                            " rwTop : " + EndianConverter.readShort(rwTop) +
                            " colLeft : " + EndianConverter.readShort(colLeft) +
                            " pnnAcct : " + pnnAcct);
        
        return numOfBytesRead;                
    }
    
    public void write(OutputStream output) throws IOException {

        output.write(getBiffType());
        output.write(x);
        output.write(y);
        output.write(rwTop);
        output.write(colLeft);
        output.write(pnnAcct);

        Debug.log(Debug.TRACE,"Writing Pane record");
    }
}
