/*************************************************************************
 *
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER.
 *
 * Copyright 2000, 2010 Oracle and/or its affiliates.
 *
 * OpenOffice.org - a multi-platform office productivity suite
 *
 * This file is part of OpenOffice.org.
 *
 * OpenOffice.org is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License version 3
 * only, as published by the Free Software Foundation.
 *
 * OpenOffice.org is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License version 3 for more details
 * (a copy is included in the LICENSE file that accompanied this code).
 *
 * You should have received a copy of the GNU Lesser General Public License
 * version 3 along with OpenOffice.org.  If not, see
 * <http://www.openoffice.org/license.html>
 * for a copy of the LGPLv3 License.
 *
 ************************************************************************/

package complex.filter.detection.typeDetection;

import com.sun.star.beans.PropertyValue;
import com.sun.star.io.NotConnectedException;
import com.sun.star.io.XInputStream;

import helper.StreamSimulator;
import java.io.*;
import java.net.URL;
import java.net.URLConnection;
import java.util.Enumeration;
import java.util.Hashtable;
import java.util.StringTokenizer;
import java.util.Vector;
import lib.TestParameters;
import share.LogWriter;
import util.utils;



/** Helper class for "TypeDetection"
 * This class do file hanlding.
 */
public class Helper  {
    
    /** The runner log writer
     * @member m_log            for log purposes
     * @member m_sTestDocPath   directory for seraching files to load
     * @member m_vFiles         list of all files describet in "files.csv"
     * @member m_hFileURLs     contains the postition of a file name in the m_vFiles Vector
     * @member m_hFileTypes      contains the postition of a file type in the m_vFiles Vector
     * @member m_param          the test parameters
     */
    
    LogWriter m_log = null;

    String m_sTestDocPath = null;
    
    Vector m_vFiles = null;
    
    Hashtable m_hFileURLs = new Hashtable();
    
    Hashtable m_hFileTypes = new Hashtable();
    
    TestParameters m_param = null;

    /**
     * construct a new instance of this class
     * It creates the "todo" list and position lists for <code>URL</code> and
     * and <code>Type</code> inside the "todo" list
     *
     * @param   param the test parameters
     *
     * @param   log the log writer
     */
    
    public Helper(TestParameters param, LogWriter log) {

        m_param = param;
        m_log = log;
   
        
        // get all files from the given directory
        m_sTestDocPath = (String)param.get("TestDocumentPath");

        // get all files from "files.csv"
        m_vFiles = getToDoList((String)m_param.get("csv.files"));
        
        createFilesList();
    }

     
     /** Reads a comma separated file (CSV). Every line of the file is
      * repesented by an <code>Vector</code> entry. Every data entry of a row is
      * also stored in a <code>Vector</code>. So the returned value is a
      * <code>Vector[][]</code> where the first dimension represents a row
      * and the second dimenesion inclueds the data values.
      * @param csvFileName the name of the csv file
      * @return Vector filled with Vector filled with data of a row
      */
     public Vector getToDoList(String csvFileName){
         
       try  {
         
         Vector vAll = new Vector();
         Vector vFields = new Vector();
         
         // get content of file
         Vector content = getCSVFileContent(csvFileName);
         
         // remove superfluous content like "#" started lines
         content = removeSuperfluousContent(content);
         
         // replace all place holders in file
         content = replacePlaceHolder(content);
         
         // create Enumeration
         Enumeration contentEnum = content.elements();
         
         // the first line contains field names of the columns
         // split line by ";"
         StringTokenizer fields = new StringTokenizer(
                                      contentEnum.nextElement().toString(),";");
         int fieldCount = 0;
         while (fields.hasMoreElements()){
             vFields.add(fields.nextElement());
             fieldCount++;
         }
         
         // fill vData with data of CSV-row
         while (contentEnum.hasMoreElements()){
             Vector vData = new Vector();

             StringTokenizer data = new StringTokenizer(
                                      contentEnum.nextElement().toString(),";", true);
             
             // example: data = "firstData;secondData;;forthData"
             // => three tokens => missing one data because the imagine 
             // "thirdData" was not recieved by data.nextToken()
             // Therefore here comes a special handling for empty datas
             boolean nextIsData = false;
             int dataCount = 0;
             while (data.hasMoreTokens()) {
                 Object myToken = data.nextToken();
                 // if the "thirdData" will be recieved, myToken=";" but  
                 // vData must add an empty String
                 if (myToken.equals(";")){
                     if (nextIsData ) {
                         vData.add("");
                         dataCount++;
                         nextIsData = false;
                     }
                     nextIsData = true;
                 } else {
                     vData.add(myToken.toString());
                     dataCount++;
                     nextIsData = false;
                 }
             }
             for (int i=dataCount; i < fieldCount; i++) vData.add("");
             vAll.add(vData);
         }
         
         
         return vAll;
           
       } catch(ClassCastException e) {
             e.printStackTrace();
       }
         return null;
     }
        
     /** The csv files "files", "preselectedFilter", "preselectedType" and
      * "serviceName" are delivered beside this class. This function seeks for
      * the csv files and read them.
      * @param csvFileName the name of the csv file
      * @return a Vector containing the content of the file. <null/> if the file
      * cannot be read
      */
    
    public Vector getCSVFileContent(String csvFileName) {
        try {
            Vector content = new Vector();
            BufferedReader br;
            String line;
            if ( m_param.DebugIsActive ) {
                System.out.println("Looking for "+csvFileName);
            }
            
            URL url = getClassURL(csvFileName);
            
            if (url != null) {
                URLConnection connection = url.openConnection();
                InputStream in = connection.getInputStream();
                
                br = new BufferedReader(new InputStreamReader(in));
                try {
                    while( ( line = br.readLine() ) != null ) {
                            content.addElement( line );
                    }
                } catch (IOException e) {
                    br.close();
                    return null;
                }
                br.close();
                return content;
            }
                 
        }catch (IOException e) {
        }catch(java.lang.NullPointerException e) {
            return null;
        }
        return null;
    }
    
    /** returns a XInputStream of given file
     * @param filePath the path to the file which shoud be loaded
     * @return the XInputStream, <null/> if the
     * file cannot be read
     * @throws NotConnectedException was thrown if it was not possible to open <CODE>filePath</CODE>
     */
    public XInputStream getFileStream( String filePath ) 
                                                throws NotConnectedException {
        return new StreamSimulator(filePath, true, m_param);
    }
    
    /** replaces place holder in preselectedFilter.
     * Because of filter names depend on StarOffice version like
     * "StarOffice 6.0 Textdokument" or ""StarSuite 7 Textdokument"
     * The filter names must be changed. The place holder will be replaced
     * by an equivalent in "typeDetection.props"
     * @param content the content of a csv file
     * @return changed file content
     */
    private Vector replacePlaceHolder(Vector content){
        
        Vector vReturn = new Vector();
        
        Vector placeHolders = new Vector(); 
        Enumeration m_params = m_param.keys();
        String placeHolder = (String)m_param.get("placeHolder");
        
        // get all place holdes from typeDetection.csv
        while (m_params.hasMoreElements()){
                String holderKey = (String) m_params.nextElement();
                if (holderKey.startsWith(placeHolder)){
                    placeHolders.add(holderKey);
                }
        }
        
        // replace all occurrences of place holders in 'CSVData' 
        Enumeration cont = content.elements();
        
        while( cont.hasMoreElements() ) {
            
            String line = (String) cont.nextElement();
            String newLine = line;
            Enumeration holders = placeHolders.elements();
            
            while( holders.hasMoreElements() ) {
                
                String holder = (String) holders.nextElement();
                int startPos = line.indexOf(holder);

                if (startPos > -1){
                    try{
                        String holderValue = (String) m_param.get(holder);

                        newLine = newLine.substring(0,startPos) + holderValue + 
                                newLine.substring(startPos + holder.length());
                        
                    } catch (java.lang.IndexOutOfBoundsException e){
                        m_log.println("ERROR: problems while creating placeholder" + 
                                    " replaced list: "+ e);
                    }
                }
           }
           vReturn.add(newLine);
        }
        return vReturn;
    }
    
    /** Removes lines of an ascii file content which starts with "#"
     * or are empty
     * @param content content of a csv fi�e
     * @return a stripped Vector
     */
    public Vector removeSuperfluousContent(Vector content){
        try{
            Vector newContent = new Vector();
            Enumeration cont = content.elements();
            while( cont.hasMoreElements() ) {
                String line = (String) cont.nextElement();
                    if (( ! line.startsWith( "#" ))&& ( line.length() != 0 )) {
                        newContent.addElement( line );
                    }
            }
            return newContent;
        } catch (ClassCastException e){
            return null;
        }
    }
    
    /** returns a <code>MediaDescripto</code> filled with given properties and
     * values.
     * @param propNames String Array of propertie names
     * @param values Objecr Array of propertie values
     * @return <code>PropertyValue[]<code>
     * @see com.sun.star.benas.PropertyValue
     * @see com.sun.star.document.MediaDescriptor
     */
    public PropertyValue[] createMediaDescriptor(String[] propNames, Object[] values) {
        PropertyValue[] props = new PropertyValue[propNames.length] ;

        for (int i = 0; i < props.length; i++) {
            props[i] = new PropertyValue() ;
            props[i].Name = propNames[i] ;
            if (values != null && i < values.length) {
                props[i].Value = values[i] ;
            }
        }

        return props ;
    }
    
    /** Appends system file separator if needed
     * @param s the system path
     * @return system path with ending system file separator
     */
    public String ensureEndingFileSep(String s){
        if(s != null && !s.equals("") && !s.endsWith(File.separator)){
                s = s.trim() + File.separator;
        }else if(s == null)
            s = "";
        return s;
    }	                	
   
    /** Returns the file URL for the given file name assembled by
     * "TestDocumentPath" of typeDetection.props and "fileURL" of files.csv
     * @param fileAlias the alias name of the file
     * @return file URL
     * @throws FileAliasNotFoundException was thrown if alias does not exist
     */
    public String getURLforfileAlias(String fileAlias)
                                        throws FileAliasNotFoundException{
        try{                                
            String fileURL = (String) m_hFileURLs.get(fileAlias).toString();
            return utils.getFullURL(ensureEndingFileSep(m_sTestDocPath) + fileURL);
        } catch (java.lang.NullPointerException e){
            throw new FileAliasNotFoundException(fileAlias);
       }

    }

    /** Returns the file type for the given file name containing in files.csv
     * @param fileAlias the alias name of the file
     * @return file type
     * @throws FileAliasNotFoundException was thrown if not alias was thorwn
     */
    public String getTypeforfileAlias(String fileAlias)
                                        throws FileAliasNotFoundException{
        try{
            return (String) m_hFileTypes.get(fileAlias).toString();
        } catch (java.lang.NullPointerException e){
            throw new FileAliasNotFoundException(fileAlias);
       }
    }

    /**
     *  Filles the Hashtable m_hFileURLs with all file names and their URL
     *  and the Hashtable m_hFilesTypes with all file names and thier file
     *  typ name. This informations are extracted from "files.csv"
     *  This is for faster acccess to get fileURL and fileType of fileAlias
     */
    public void createFilesList(){
        for (int i = 0; i < m_vFiles.size();i++){
            Vector toDo = (Vector) m_vFiles.get(i);
                m_hFileURLs.put((String) toDo.get(0).toString(), 
                                               (String) toDo.get(1).toString());
                m_hFileTypes.put((String) toDo.get(0).toString(), 
                                               (String) toDo.get(2).toString());
        }
    }
    
    
    /**  Validate the returned file type for the file alias with the
     *  possible file types
     * @param currentFileType the returned file type
     * @param fileTypes all possible file types
     * @return true if valid
     */
    public boolean checkFileType(String currentFileType, String fileTypes){
            
        StringTokenizer data = new StringTokenizer(fileTypes,":", true);

        boolean found = false;
        while (data.hasMoreElements()) {
            
            String actualFileType = data.nextElement().toString();
            
            found = found || currentFileType.equals(actualFileType);
        }
        return found;
    }
    
    /** creates an input/output parameter of <code>PropertyValue[]<code>.
     * @return PropertyValue[][]
     * @param PropVal a PropertyValue
     */
    public PropertyValue[][] createInOutPropertyValue(PropertyValue[] PropVal){        
        PropertyValue[][] dummy = new PropertyValue[1][];
        dummy[0] = PropVal;
        return dummy;
    }
    
    public URL getClassURL(String fileName){
        String PackagePath = this.getClass().getPackage().getName().replace('.','/');
        return this.getClass().getResource("/" + PackagePath +"/" + fileName);
    }
    
    public String getClassURLString(String fileName){
        return getClassURL(fileName).toString().replaceAll("file:","");
    }


}

/** This exeception should be thrown if a method seeks for an invalid alias name */
class FileAliasNotFoundException extends java.lang.Exception{
    /** throws error message with wrong alias name
     * @param fileAlias the alias name
     */    
    public FileAliasNotFoundException(String fileAlias){
        super("Could not get '"+fileAlias +"'");
    }
}