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

package org.openoffice.xmerge.converter.xml.sxc.minicalc;

import jmc.Workbook;
import jmc.Worksheet;
import jmc.CellAttributes;
import jmc.CellDescriptor;
import jmc.JMCconstants;
import jmc.JMCException;

import java.awt.Color;

import java.io.ByteArrayOutputStream;
import java.io.ByteArrayInputStream;
import java.io.DataOutputStream;
import java.io.IOException;

import org.openoffice.xmerge.converter.palm.Record;
import org.openoffice.xmerge.util.Debug;
import org.openoffice.xmerge.util.IntArrayList;

import org.openoffice.xmerge.converter.xml.sxc.SpreadsheetEncoder;
import org.openoffice.xmerge.converter.xml.sxc.Format;
import org.openoffice.xmerge.converter.xml.OfficeConstants;

/**
 *  This class is used by {@link
 *  org.openoffice.xmerge.converter.xml.sxc.SxcDocumentSerializerImpl
 * SxcDocumentSerializerImpl} to encode the MiniCalc format.
 *
 *  @author   Paul Rank
 */
final class MinicalcEncoder extends SpreadsheetEncoder {

    /** MiniCalc WorkBook to store sheets. */
    private Workbook wb;

    /** MiniCalc sheet - only one sheet can be open at a time. */
    private Worksheet ws;

    /**
     *  Estimate of the number of Palm pixels per character.  Used for
     *  estimating the width of a cell on a Palm device.
     */
    private final static int pixelsPerChar = 6;

    /**
     *  The minimum width (in pixels) that we allow a column to be set to
     *  on a Palm device.
     */
    private final static int minWidth = 10;

    /**
     *  The maximum width (in pixels) that we allow a column to be set to
     *  on a Palm device.
     */
    private final static int maxWidth = 80;


    /**
     *  Constructor creates a MiniCalc WorkBook.
     *
     *  @param  log       Log object for logging.
     *  @param  name      The name of the WorkBook.
     *  @param  password  The password for the WorkBook.
     *
     *  @throws  IOException  If any I/O error occurs.
     */
    MinicalcEncoder(String name, String password) throws IOException {
        
        super(name, password);

        try {
            wb = new Workbook(name, password);
        }
        catch (JMCException e) {
            Debug.log(Debug.ERROR, "new Workbook threw exception:" + e.getMessage());
            throw new IOException(e.getMessage());
        }    
    }


    /**
     *  This method creates a WorkSheet belonging to the 
     *  WorkBook.
     *
     *  @param  sheetName  The name of the WorkSheet.
     *
     *  @throws  IOException  If any I/O error occurs.
     */
    public void createWorksheet(String sheetName) throws IOException {

        try {
            ws = wb.createWorksheet(sheetName);
        }
        catch (JMCException e) {
            Debug.log(Debug.ERROR, "wb.createWorksheet threw exception:" + e.getMessage());
            throw new IOException(e.getMessage());
        }
    }


    /**
     *  This method gets the number of sheets in the WorkBook.
     *
     *  @return  The number of sheets in the WorkBook.
     */
    public int getNumberOfSheets() {

        int numSheets = wb.getNumberOfSheets();
        return numSheets;
    }


    /**
     *  This method encodes the MiniCalc WorkBook information
     *  into an palm <code>Record</code> array in MiniCalc
     *  database format.
     *
     *  @return  Array of <code>Record</code> holding MiniCalc
     *           contents.
     *
     *  @throws  IOException  If any I/O error occurs.
     */
    public Record[] getRecords(int sheetID) throws IOException {

        // Get the WorkSheet for the input sheetID
        ws = wb.getWorksheet(sheetID);

        // Need to call ws.initWrite() before we start querying the WorkSheet
        try {
            ws.initWrite();
        }
        catch (JMCException e) {
        Debug.log(Debug.ERROR, "ws.initWrite in getRecords:" + e.getMessage());
            throw new IOException(e.getMessage());
        }

        // Get the number of records in the WorkSheet
        int numRecords = ws.getNumberOfRecords();
    
        // Create the Record array
        Record[] allRecords = new Record[numRecords];


        // Get each record from the WorkSheet and store in allRecords[]
        try {
            for (int i = 0; i < allRecords.length; i++) {

                ByteArrayOutputStream bos = new ByteArrayOutputStream();

                int length = ws.writeNextRecord(bos);

                byte cBytes[] = bos.toByteArray();

                allRecords[i] = new Record(cBytes);
            }
        }
        catch (Exception e) {
            Debug.log(Debug.ERROR, "ws.writeNextRecord in getRecords:" + e.getMessage());
            throw new IOException(e.getMessage());
        }

        return allRecords;
    }


    /**
     *  Add a cell to the current WorkSheet.
     *
     *  @param   row             The row number of the cell.
     *  @param   column          The column number of the cell.
     *  @param   fmt             The <code>Format</code> object describing
     *                           the appearance of this cell.
     *  @param   cellContents    The text or formula of the cell's contents.
     *
     *  @throws  IOException  If any I/O error occurs.
     */
    public void addCell(int row, int column, Format fmt, String cellContents) throws IOException {
        
        CellAttributes ca = new CellAttributes(getFormat(fmt), 
                                                fmt.getForeground(),
                                                fmt.getBackground());
        
        CellDescriptor cellDes = new CellDescriptor(row, column, ca, cellContents);
        
        try {
            ws.putCell(cellDes);
        }
        catch (JMCException jmce) {
            Debug.log(Debug.ERROR, "ws.putCell threw exception: " + jmce.getMessage());
            throw new IOException(jmce.getMessage());
        }
    }
    

    /**
     *  Set the width of the columns in the WorkBook.
     *
     *  @param  columnWidths  An <code>IntArrayList</code> of column
     *                        widths.
     */
    public void setColumnWidths(IntArrayList columnWidths) throws IOException {
        // Get the number of columns
        int numColumns = columnWidths.size();
        
        // Return if there are no columns in the listr
        if (numColumns == 0) {
            return;
        }
            
        // Need to set the FORM_FLAGS_NONDEFAULT flag for the column widths
        // to be used in MiniCalc
        long format = JMCconstants.FORM_FLAGS_NONDEFAULT;
        
        CellAttributes ca = new CellAttributes(format);
        
        try {
            for (int i = 0; i < numColumns; i++) {
                // Get the column width in Palm pixels
                int width = columnWidths.get(i) * pixelsPerChar;
                
                // Check limits on column width
                if (width < minWidth) {
                    width = minWidth;
                } else if (width > maxWidth) {
                    width = maxWidth;
                }
                
                // Add the column descriptor to the WorkSheet
                ws.putColumn(i + 1, width, ca);
            }
        }
        catch (JMCException jmce) {
            Debug.log(Debug.ERROR, "ws.putColumn threw exception: " + jmce.getMessage());
            throw new IOException(jmce.getMessage());
        }
    }

    
    /**
     *  This method sets the format of a cell to <i>string</i>.
     *
     *  @param  format  The cell format-may already contain display info,
     *                  such as alignment or font type.
     *
     *  @return  The updated format of the cell.
     */
    private long setFormatString(long format) {

        format = clearCellFormatType(format);

        // Set format to generic, since MiniCalc does not have a string type.
        format = format | JMCconstants.FF_FORMAT_GENERIC;

        return format;
    }


    /**
     *  This method sets the format of a cell to <i>floating point</i>.
     *
     *  @param  format         The cell format.  May already contain
     *                         display info, such as alignment or
     *                         font type.
     *  @param  decimalPlaces  The number of decimal places to
     *                         set in the floating point number.
     *
     *  @return  The updated format of the cell.
     */
    private long setFormatFloat(long format, int decimalPlaces) {

        format = clearCellFormatType(format);

        // Set format to floating point with correct number of decimal places
        format = format | JMCconstants.FF_FORMAT_DECIMAL | decimalPlaces;

        return format;
    }


    /**
     *  This method sets the format of a cell to <i>time</i>.
     *
     *  @param  format  The cell format-may already contain display info,
     *                  such as alignment or font type.
     *
     *  @return  The updated format of the cell.
     */
    private long setFormatTime(long format) {

        format = clearCellFormatType(format);

        // Set format to time.
        format = format | JMCconstants.FF_FORMAT_TIME;

        return format;
    }


    /**
     *  This method sets the format of a cell to <i>date</i>.
     *
     *  @param  format  The cell format-may already contain display info,
     *                  such as alignment or font type.
     *
     *  @return  The updated format of the cell.
     */
    private long setFormatDate(long format) {

        format = clearCellFormatType(format);

        // Set format to date.
        format = format | JMCconstants.FF_FORMAT_DATE;

        return format;
    }


    /**
     *  This method sets the format of a cell to <i>currency</i>.
     *
     *  @param  format         The cell format-may already contain
     *                         display info, such as alignment or
     *                         font type.
     *  @param  decimalPlaces  The number of decimal places to set.
     *
     *  @return  The updated format of the cell.
     */
    private long setFormatCurrency(long format, int decimalPlaces) {

        format = clearCellFormatType(format);

        // Set format to Currency with correct number of decimal places
        format = format | JMCconstants.FF_FORMAT_CURRENCY | decimalPlaces;

        return format;
    }


    /**
     *  This method sets the format of a cell to <i>boolean</i>.
     *
     *  @param  format  The cell format-may already contain display info,
     *                  such as alignment or font type.
     *
     *  @return  The updated format of the cell.
     */
    private long setFormatBoolean(long format) {

        format = clearCellFormatType(format);

        // Set format to generic, since MiniCalc does not have a Boolean type.
        format = format | JMCconstants.FF_FORMAT_GENERIC;

        return format;
    }


    /**
     *  This method sets the format of a cell to <i>percent</i>.
     *
     *  @param  format         The cell format-may already contain
     *                         display info, such as alignment or
     *                         font type.
     *  @param  decimalPlaces  The number of decimal places to set.
     *
     *  @return  The updated format of the cell.
     */
    private long setFormatPercent(long format, int decimalPlaces) {

        format = clearCellFormatType(format);

        // Set format to Percent with correct number of decimal places
        format = format | JMCconstants.FF_FORMAT_PERCENT | decimalPlaces;

        return format;
    }
    

    /**
     *  This method clears out the format bits associated with
     *  the type of data (<i>float</i>, <i>time</i>, etc...) in
     *  a cell.
     *
     *  @param  format  The original format for the cell.
     *
     *  @return  The updated cell format with the bits associated
     *           with the type of data (float, time, etc...)
     *           zeroed out.
     */
    private long clearCellFormatType(long format) {

        // First 4 bits are for the number of decimal places
        // bits 5-8 are for the data format (float, time, etc...)

        // Clear out first 8 bits
        format = format & 0xFFFFFFFFFFFFFF00L;

        return format;
    }
    
    
    /**
     *  Set a cell's formatting options via a separately create
     *  <code>Format</code> object.
     *
     *  @param  row     The row number of the cell to be changed.
     *  @param  column  The column number of the cell to be changed.
     *  @param  fmt     Object containing formatting settings for
     *                 this cell.
     */
    public void setCellFormat(int row, int column, Format fmt) {
    }
    

    /**
     *  Get the names of the sheets in the WorkBook.
     *
     *  @param  sheet  The required sheet.
     */
    public String getSheetName(int sheet) {
        return wb.getWorksheet(sheet).getName();
    }
    

    /*
     *  This method returns a MiniCalc style format from the
     *  <code>Format</code> object.
     */ 
    private long getFormat(Format fmt) 
    {
        String category = fmt.getCategory();
        
        if (category.equalsIgnoreCase(OfficeConstants.CELLTYPE_BOOLEAN)) {
            return setFormatBoolean(0);
        }
        else if (category.equalsIgnoreCase(OfficeConstants.CELLTYPE_CURRENCY)) {
            return setFormatCurrency(0, fmt.getDecimalPlaces());
        }
        else if (category.equalsIgnoreCase(OfficeConstants.CELLTYPE_DATE)) {
            return setFormatDate(0);
        }
        else if (category.equalsIgnoreCase(OfficeConstants.CELLTYPE_FLOAT)) {
            return setFormatFloat(0, fmt.getDecimalPlaces());
        }
        else if (category.equalsIgnoreCase(OfficeConstants.CELLTYPE_PERCENT)) {
            return setFormatPercent(0, fmt.getDecimalPlaces());
        }
        else if (category.equalsIgnoreCase(OfficeConstants.CELLTYPE_STRING)) {
            return setFormatString(0);
        }
        else if (category.equalsIgnoreCase(OfficeConstants.CELLTYPE_TIME)) {
            return setFormatTime(0);
        }
        else {
            // Should never get here, but just in case
            return 0;
        }
    }
}

