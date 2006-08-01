/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: SxcDocumentDeserializerImpl.java,v $
 *
 *  $Revision: 1.3 $
 *
 *  last change: $Author: ihi $ $Date: 2006-08-01 12:45:15 $
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

package org.openoffice.xmerge.converter.xml.sxc.minicalc;

import org.openoffice.xmerge.converter.xml.sxc.SxcDocumentDeserializer;
import org.openoffice.xmerge.converter.xml.sxc.SpreadsheetDecoder;
import org.openoffice.xmerge.converter.palm.PalmDB;
import org.openoffice.xmerge.ConvertData;
import org.openoffice.xmerge.converter.palm.PalmDocument;

import java.io.IOException;
import java.util.Enumeration;

/**
 *  <p>MiniCalc implementation of <code>DocumentDeserializer</code>
 *  for the {@link
 *  org.openoffice.xmerge.converter.xml.sxc.minicalc.PluginFactoryImpl
 *  PluginFactoryImpl}.</p>
 *
 *  <p>This converts a set of files in MiniCalc PDB format to a StarOffice DOM.</p>
 *
 *  @author  Mark Murnane
 */
public final class SxcDocumentDeserializerImpl extends SxcDocumentDeserializer {

    /**
     *  Creates new <code>SxcDocumentDeserializerImpl</code>.
     *
     *  @param  cd  <code>ConvertData</code>  Input data to convert.
     */
    public SxcDocumentDeserializerImpl(ConvertData cd) {
        super(cd);
    }


    /**
     *  This method will be implemented by concrete subclasses and will
     *  return an application-specific decoder.
     *
     *  @param  workbook        The WorkBook name.
     *  @param  worksheetNames  An array of WorkSheet names.
     *  @param  password        The password.
     *
     *  @return  An application-specific <code>SpreadsheetDecoder</code>.
     */
    public SpreadsheetDecoder createDecoder(String workbook,
        String[] worksheetNames, String password) throws IOException {

        return new MinicalcDecoder(workbook, worksheetNames, password);
    }
    

    /**
     *  This method will return the name of the WorkBook from the
     *  <code>ConvertData</code>.  Allows for situations where the
     *  WorkBook name differs from the PDB name.
     *
     *  Implemented in the Deserializer as the Decoder's constructor
     *  requires a name.
     *
     *  @param  cd  The <code>ConvertData</code>.
     *
     *  @return  The name of the WorkBook. 
     */
    protected String getWorkbookName(ConvertData cd) 
        throws IOException {

        Enumeration e        = cd.getDocumentEnumeration();
        PalmDocument palmDoc = (PalmDocument) e.nextElement();
        String workbookName  = palmDoc.getName();

        // Search for "-", which separates workbook from worksheet
        int end = workbookName.indexOf("-");

        if (end > 0) {
            workbookName = workbookName.substring(0, end);
        }
        
        return workbookName; 
    }
    

    /**
     *  This method will return an array of WorkSheet names from the
     *  <code>ConvertData</code>.
     *
     *  @param  cd  The <code>ConvertData</code>.
     *
     *  @return  The name of the WorkSheet. 
     */
    protected String[] getWorksheetNames(ConvertData cd) 
        throws IOException {
        int numberOfPDBs = cd.getNumDocuments();
        String worksheetName[] = new String[numberOfPDBs];
        int i=0;
        Enumeration e = cd.getDocumentEnumeration();
        while (e.hasMoreElements()) {
                PalmDocument palmDoc = (PalmDocument) e.nextElement();
                worksheetName[i] = palmDoc.getName();
                
                // Search for the "-", which seperates workbook from worksheet
                int start = worksheetName[i].indexOf("-");
                
                if (start != -1) {
                   worksheetName[i] = worksheetName[i].substring(start + 1);
                }     
                i++;
        }

        return worksheetName; 
    }
}

