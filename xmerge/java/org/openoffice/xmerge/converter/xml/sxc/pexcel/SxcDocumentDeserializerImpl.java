/************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: SxcDocumentDeserializerImpl.java,v $
 *
 *  $Revision: 1.5 $
 *
 *  last change: $Author: rt $ $Date: 2005-09-09 10:55:11 $
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

package org.openoffice.xmerge.converter.xml.sxc.pexcel;

import java.io.IOException;
import java.util.Enumeration;
import java.util.Vector;

import org.openoffice.xmerge.util.Debug;
import org.openoffice.xmerge.ConvertData;
import org.openoffice.xmerge.converter.xml.sxc.SpreadsheetDecoder;
import org.openoffice.xmerge.converter.xml.sxc.SxcDocumentDeserializer;
import org.openoffice.xmerge.converter.xml.sxc.pexcel.PocketExcelDecoder;
import org.openoffice.xmerge.converter.xml.sxc.pexcel.records.Workbook;


/**
 *  <p>Pocket Excel implementation of <code>DocumentDeserializer</code>
 *  for the {@link
 *  org.openoffice.xmerge.converter.xml.sxc.pexcel.PluginFactoryImpl
 *  PluginFactoryImpl}.</p>
 *
 *  <p>This converts a set of files in Pocket Excel PXL format to a StarOffice DOM.</p>
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

        return new PocketExcelDecoder(workbook, worksheetNames, password);
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

        Enumeration e = cd.getDocumentEnumeration();
        Workbook wb = (Workbook) e.nextElement();

        String workbookName = wb.getName();
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

        Enumeration e = cd.getDocumentEnumeration();
        Workbook wb = (Workbook) e.nextElement();
        Vector v = wb.getWorksheetNames();
        e = v.elements();
        String worksheetNames[] = new String[v.size()];
        int i = 0;
        while(e.hasMoreElements()) {
            worksheetNames[i] = (String) e.nextElement();
            Debug.log(Debug.TRACE,"Worksheet Name : " + worksheetNames[i]);
            i++;
        }
        return worksheetNames; 
    }
}

