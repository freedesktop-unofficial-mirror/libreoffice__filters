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

package org.openoffice.xmerge.converter.xml.sxc.pexcel.records;

import java.io.OutputStream;
import java.io.InputStream;
import java.io.IOException;
import java.util.Vector;
import java.util.Enumeration;

import org.openoffice.xmerge.converter.xml.OfficeConstants;
import org.openoffice.xmerge.converter.xml.sxc.Format;
import org.openoffice.xmerge.util.Debug;
import org.openoffice.xmerge.util.IntArrayList;

/**
 *  This class is used by <code> PxlDocument</code> to maintain pexcel
 *  workbooks. 
 *
 *  @author  Martin Maher 
 */
public class Workbook implements org.openoffice.xmerge.Document {

    private Vector fonts				= new Vector();
    private Vector extendedFormats		= new Vector();
    private Vector worksheets			= new Vector();
    private Vector boundsheets			= new Vector();
    private static final CodePage cp;
    private static final Window1 win1;
    private static final BeginningOfFile bof;;
    private static final Eof eof;
    private String fileName;

    static {
        cp 				= new CodePage();
        win1			= new Window1();
        bof				= new BeginningOfFile(true);
        eof				= new Eof();

    }


    /**
     * Constructs a pocket Excel Workbook with the name of the file passed in
     * as an argument. Also fills out a basic header block containing the
     * minimum number of objects that can be created at this time.
     *
     * @param	name	Name of the Pocket Excel Data file. (excluding the file
     * 					extension)
     */
    public Workbook(String name) {
        fileName = name + ".pxl";
    }

    /**
     * Constructs a pocket Excel Workbook from the
     * <code>InputStream</code> and assigns it the document name passed in
     *
     * @param	is InputStream containing a Pocket Excel Data file.
     */
    public Workbook(String name, InputStream is) throws IOException {
        read(is);
        fileName = name;
    }

    /**
      *	Writes the current workbook to the <code>Outputstream</code> 
      * 
      * @param	os The destination outputstream	
      */
    public void write(OutputStream os) throws IOException {
        bof.write(os);
        cp.write(os);
        win1.write(os);
        for(Enumeration e = fonts.elements();e.hasMoreElements();) {
            FontDescription fd = (FontDescription) e.nextElement();
            fd.write(os);
        }
        for(Enumeration e = extendedFormats.elements();e.hasMoreElements();) {
            ExtendedFormat xf = (ExtendedFormat) e.nextElement();
            xf.write(os);
        }
        for(Enumeration e = boundsheets.elements();e.hasMoreElements();) {
            BoundSheet bs = (BoundSheet) e.nextElement();
            bs.write(os);
        }
        eof.write(os);
        for(Enumeration e = worksheets.elements();e.hasMoreElements();) {
            Worksheet ws = (Worksheet) e.nextElement();
            ws.write(os);
        }
    }

    /**
      *	Reads a workbook from the <code>InputStream</code> and contructs a
     *	workbook object from it 
     *
      * @param	is InputStream containing a Pocket Excel Data file.
      */
    public void read(InputStream is) throws IOException {

        boolean done = false;

        int b = 0;
        while (!done)
        {
            b = is.read();
            if (b == -1)
            {
                Debug.log(Debug.TRACE,"End of file reached");
                break;
            }
                
            switch (b)
            {
                case PocketExcelBiffConstants.BOF_RECORD:
                    Debug.log(Debug.TRACE,"BOF Record");
                    bof.read(is);
                    break;
                    
                case PocketExcelBiffConstants.EOF_MARKER:
                    Debug.log(Debug.TRACE,"EOF Marker");
                    eof.read(is);
                    Worksheet ws = new Worksheet();
                    while(ws.read(is)) {
                        worksheets.add(ws);
                        // ws.reset();	
                        ws = new Worksheet();
                    }
                    break;
                    
                case PocketExcelBiffConstants.FONT_DESCRIPTION:
                    Debug.log(Debug.TRACE,"FONT: Font Description (31h)");
                    FontDescription fd = new FontDescription(is);
                    fonts.add(fd);
                    break;

                case PocketExcelBiffConstants.WINDOW_INFO:
                    Debug.log(Debug.TRACE,"WINDOW1: Window Information (3Dh) [PXL 2.0]");
                    win1.read(is);
                    break;
                    
                case PocketExcelBiffConstants.CODEPAGE:
                    Debug.log(Debug.TRACE,"CODEPAGE : Codepage and unknown fields (42h)");
                    cp.read(is);
                    break;

                case PocketExcelBiffConstants.BOUND_SHEET:
                    Debug.log(Debug.TRACE,"BOUNDSHEET: Sheet Information (85h)");
                    BoundSheet bs = new BoundSheet(is);
                    boundsheets.add(bs);
                    break;
                        
                case PocketExcelBiffConstants.EXTENDED_FORMAT:
                    Debug.log(Debug.TRACE,"XF: Extended Format (E0h) [PXL 2.0]");
                    ExtendedFormat xf = new ExtendedFormat(is);
                    extendedFormats.add(xf);
                    break;
                                            
                default:
                    b = is.read();
                    break;
            }
                
        }
        is.close();
    }
    
    /**
      *	Adds a font recrod to the workbook 
     *
      * @param	f the font recrod to add	
      */	
    public int addFont(FontDescription f) {

        boolean alreadyExists = false;
        int i = 0;
        
        for(Enumeration e = fonts.elements();e.hasMoreElements();) {
            FontDescription fd = (FontDescription) e.nextElement();
            if(fd.compareTo(f))
                alreadyExists = true;
            else 
                i++;
        }
        
        if(!alreadyExists) 
                fonts.add(f);

        return i; 
    }

    /**
      *	Adds a ExtendedFormat record to the workbook 
     *
      * @param	f the font recrod to add	
      */	
    public int addExtendedFormat(ExtendedFormat xf) {

        boolean alreadyExists = false;
        int i = 0;
        
        for(Enumeration e = extendedFormats.elements();e.hasMoreElements();) {
            ExtendedFormat currentXF = (ExtendedFormat) e.nextElement();
            if(xf.compareTo(currentXF))
                alreadyExists = true;
            else 
                i++;
        }
        
        if(!alreadyExists)
            extendedFormats.add(xf);

        return i; 
    }
    
    /**
      *	Gets a worksheet at a particular index from mthe current workbook. 
     *
      * @param	index the index of the worksheet to retrieve	
      */
    public Worksheet getWorksheet(int index) {

        return ((Worksheet) worksheets.elementAt(index));
    }

    /**
     * Returns a <code>Vector</code> containing all the worksheet Names  
     *
     * @return a <code>Vector</code> containing all the worksheet Names 
     */	 
    public Vector getWorksheetNames() {

        Vector wsNames = new Vector();

        for(Enumeration e = boundsheets.elements();e.hasMoreElements();) {
            BoundSheet bs = (BoundSheet) e.nextElement();
            wsNames.add(bs.getSheetName());
        }	

        return wsNames;
    }

    /**
     * Adds a <code>Worksheet</code> to the workbook.  
     *
     * @return name the name of the <code>Worksheet</code> to be added 
     */	 
    public void addWorksheet(String name) throws IOException {
    
        BoundSheet bs = new BoundSheet(name);
        boundsheets.add(bs);

        Worksheet ws = new Worksheet();
        worksheets.add(ws);
    }

    /**
     * Adds a cell to the current worksheet.  
     *
     * @return the name of the <code>Worksheet</code> to be added 
     */
    public void addCell(int row,int col, Format fmt, String cellContents)
    throws IOException {
        
        Worksheet currentWS = (Worksheet) worksheets.elementAt(worksheets.size()-1);
        FontDescription fd = new FontDescription(fmt.isItalic(), fmt.isBold(), fmt.isUnderline());
        int ixfnt = addFont(fd);
        ExtendedFormat xf = new ExtendedFormat(ixfnt);
        int ixfe = addExtendedFormat(xf);

        String category = fmt.getCategory();

        // Now the formatting is out of the way add the cell
        if(cellContents.startsWith("=")) {
            Formula f = new Formula(row, col, cellContents, ixfe, fmt.getValue());
            currentWS.addCell(f);
        } else if(category.equalsIgnoreCase(OfficeConstants.CELLTYPE_FLOAT)) {
            FloatNumber num = new FloatNumber(row, col, cellContents, ixfe);
            currentWS.addCell(num);
        } else {
            LabelCell lc = new LabelCell(row, col, cellContents, ixfe);
            currentWS.addCell(lc); 	// three because we assume the last three 
                                    // Records in any worksheet is the selection, 
                                    // window2 and eof Records 
        }
    }

    /**
      * Will create a number of ColInfo recrods based on the column widths
     * based in.	
     *
      * @param	an integer list representing the column widths	
      */
    public void addColInfo(IntArrayList columnWidths) {
        Worksheet currentWS = (Worksheet) worksheets.elementAt(worksheets.size()-1);
        currentWS.addColInfo(columnWidths);
    }



    /**
     * Return the filename of the pxl document without the file extension  
     *
     * @return filename without the file extension 
     */
    public String getName() {

        // We have to strip off the file extension
        int end = fileName.lastIndexOf(".");
        String name;
        if( end >= 0)	// check in case the filename is already stripped
            name = fileName.substring(0, end);
        else
            name = fileName;

        return name;
    }
    
    /**
     * Returns the filename of the pxl document with the file extension 
     *
     * @return filename with the file extension 
     */
    public String getFileName() {

        return fileName;
    }
    
}
