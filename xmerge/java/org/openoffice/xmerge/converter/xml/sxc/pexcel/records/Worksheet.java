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

import java.io.OutputStream;
import java.io.InputStream;
import java.io.IOException;
import java.util.Vector;
import java.util.Enumeration;

import org.openoffice.xmerge.util.IntArrayList;
import org.openoffice.xmerge.util.Debug;

/**
 *  This class is used by <code>PxlDocument</code> to maintain pexcel
 *  worksheets. 
 *
 *  @author  Martin Maher 
 */
public class Worksheet {

    private String name;
    private Vector rows		= new Vector();
    private Vector colInfo	= new Vector();
    private Vector cells	= new Vector();
    private DefColWidth dcw	= new DefColWidth();
    private DefRowHeight drh	= new DefRowHeight();
    private Window2 win2	= new Window2();
    private Selection s		= new Selection();
    private BeginningOfFile bof;
    private Eof eof;
/*
    static {
        bof		= new BeginningOfFile(true);
        eof		= new Eof();
    }
*/
    /**
      *	Writes the current workbook to the <code>Outputstream</code> 
      * 
      * @param	os The destination outputstream	
      */
    public void write(OutputStream os) throws IOException {
        
        bof		= new BeginningOfFile(false);
        bof.write(os);
        dcw.write(os);
        for(Enumeration e = colInfo.elements();e.hasMoreElements();) {
            ColInfo ci = (ColInfo) e.nextElement();
            ci.write(os);
        }
        drh.write(os);
        for(Enumeration e = rows.elements();e.hasMoreElements();) {
            ColInfo ci = (ColInfo) e.nextElement();
            ci.write(os);
        }
        for(Enumeration e = cells.elements();e.hasMoreElements();) {
            CellValue cv = (CellValue) e.nextElement();
            cv.write(os);
        }
        win2.write(os);
        s.write(os);
        eof		= new Eof();
        eof.write(os);
    }

    /**
      *	Reads a worksheet from the <code>InputStream</code> and contructs a
     *	workbook object from it 
     *
      * @param	is InputStream containing a Pocket Excel Data file.
      */
    public boolean read(InputStream is) throws IOException {

        int b = is.read();

        if (b==-1)
            return false;

        while(b!=-1) {
            switch (b)
            {
                case PocketExcelBiffConstants.BLANK_CELL:
                    Debug.log(Debug.TRACE,"Blank Cell (01h)");
                    BlankCell bc = new BlankCell(is);
                    break;
                    
                case PocketExcelBiffConstants.NUMBER_CELL:
                    Debug.log(Debug.TRACE,"NUMBER: Cell Value, Floating-Point Number (03h)");
                    FloatNumber fn = new FloatNumber(is);	
                    cells.add(fn);
                    break;
                    
                case PocketExcelBiffConstants.LABEL_CELL:
                    Debug.log(Debug.TRACE,"LABEL: Cell Value, String Constant (04h)");
                    LabelCell lc = new LabelCell(is);
                    cells.add(lc);
                    break;

                case PocketExcelBiffConstants.BOOLERR_CELL:
                    Debug.log(Debug.TRACE,"BOOLERR: Cell Value, Boolean or Error (05h)");
                    BoolErrCell bec = new BoolErrCell(is);
                    break;

                case PocketExcelBiffConstants.FORMULA_CELL:
                    Debug.log(Debug.TRACE,"FORMULA: Cell Formula (06h)");
                    Formula f = new Formula(is);
                    if(f.getString()!="") 	// if it is a formula we can convert
                        cells.add(f);		// i.e. no functions
                    break;
                    
                 case PocketExcelBiffConstants.FORMULA_STRING:
                    Debug.log(Debug.TRACE,"String Value of a Formula (07h)");
                    StringValue sv = new StringValue(is);
                    break;
                   
                case PocketExcelBiffConstants.ROW_DESCRIPTION:
                    Debug.log(Debug.TRACE,"ROW: Describes a Row (08h)");
                    Row rw = new Row(is);
                    rows.add(rw);
                    break;

                case PocketExcelBiffConstants.BOF_RECORD:
                    Debug.log(Debug.TRACE,"BOF Record");
                    bof = new BeginningOfFile(is);
                    break;
                    
                case PocketExcelBiffConstants.EOF_MARKER:
                    Debug.log(Debug.TRACE,"EOF Marker");
                    eof = new Eof();
                    return true;
                    
                case PocketExcelBiffConstants.DEFINED_NAME:
                    Debug.log(Debug.TRACE,"NAME: Defined Name (18h)");
                    DefinedName dn = new DefinedName(is);
                    break;                        
                        
                case PocketExcelBiffConstants.CURRENT_SELECTION:
                    Debug.log(Debug.TRACE,"SELECTION: Current Selection (1Dh)");
                    Selection s = new Selection(is);
                    break;
                    
                case PocketExcelBiffConstants.NUMBER_FORMAT:
                    Debug.log(Debug.TRACE,"FORMAT: Number Format (1Eh)");
                    NumberFormat nf = new NumberFormat(is);
                    break;

                case PocketExcelBiffConstants.DEFAULT_ROW_HEIGHT:
                    Debug.log(Debug.TRACE,"DEFAULTROWHEIGHT: Default Row Height (25h)");
                    drh = new DefRowHeight(is);
                    break;
                    
                case PocketExcelBiffConstants.SHEET_WINDOW_INFO:
                    Debug.log(Debug.TRACE,"WINDOW2: Sheet Window Information (3Eh) [PXL 2.0]");
                    win2 = new Window2(is);
                    break;
                    
                case PocketExcelBiffConstants.PANE_INFO:
                    Debug.log(Debug.TRACE,"PANE: Number of Panes and their Position (41h) [PXL 2.0]");
                    Pane p = new Pane(is);
                    break;
                    
                case PocketExcelBiffConstants.DEF_COL_WIDTH:
                    Debug.log(Debug.TRACE,"DEFCOLWIDTH: Default Column Width (55h) [PXL 2.0]");
                    dcw = new DefColWidth(is);
                    break;
                    
                case PocketExcelBiffConstants.COLINFO:
                    Debug.log(Debug.TRACE,"COLINFO: Column Formatting Information (7Dh) [PXL 2.0]");
                    ColInfo ci = new ColInfo(is);
                    break;

                default:
                    break;
            }
            b = is.read();
            
        }
        Debug.log(Debug.TRACE,"Leaving Worksheet:");

        return true;
    }

    /**
      *	Returns an enumerator which will be used to access individual cells	
     *
      * @return an enumerator to the worksheet cells	
      */
    public Enumeration getCellEnumerator() throws IOException {
        return (cells.elements());
    }

    /**
      * Adds a cell to this worksheet. Current valdid celltypes are
     * <code>FloatNumber</code>, <code>LabelCell</code> or <code>Formula</code>
     *
      * @param	f the font recrod to add	
      */
    public void addCell(CellValue cv) {
        cells.add(cv);
    }

    /**
      * Adds a number of ColInfo Records to the worksheet base on a list of
     * clumnwidths passed in
     *
      * @param	list of column widths	
      */
    public void addColInfo(IntArrayList columnWidths) {
    
        int numColumns 	= columnWidths.size();
        int interval	= 0;
        ColInfo	newColInfo;
        
        Debug.log(Debug.TRACE,"Worksheet: addColInfo");
        for (int i = 0; i < numColumns; i++)	// for each Column width in the IntArrayList
            {
            int width = columnWidths.get(i);
            Debug.log(Debug.TRACE,"Worksheet: addColInfo width = " + width);

            if (numColumns == i + 1)			// The last ColInfo Record
                {
                newColInfo = new ColInfo(i-interval, i, width * 256, (byte) 2);
                colInfo.add(newColInfo);
            }
        else if (width == columnWidths.get(i+1)) // Look ahead to the next column
            interval++;							// Skip creatig a colInfo and
                                                // increment the interval
        else
            {
            newColInfo = new ColInfo(i-interval, i, width * 256, (byte) 2);
            interval=0;
            colInfo.add(newColInfo);
            }
        }
    }
}
