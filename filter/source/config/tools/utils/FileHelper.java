/*************************************************************************
 *
 *  $RCSfile: FileHelper.java,v $
 *
 *  $Revision: 1.5 $
 *
 *  last change: $Author: hr $ $Date: 2004-02-05 16:14:35 $
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

package com.sun.star.filter.config.tools.utils;

// __________ Imports __________

import java.io.*;
import java.lang.*;
import java.net.*;
import java.util.*;

// __________ Implementation __________

/**
 * It collects some static helper functons to handle file system specific problems.
 * Sometimes it's neccessary to convert URL from/to system pathes;
 * or from string notation to structural versions (e.g. com.sun.star.util.URL).
 * And sometimes java had another notation then the office it has.
 * Further it provides functionality to work easiear with the java.io.File class of java.
 *
 * @author      Andreas Schl�ns
 */
public class FileHelper
{
    // ____________________

    /**
     * Copy the (complete!) content of one file to another file.
     *
     * @param aSource
     *        means the source file, which should be copied.
     *
     * @param aDestination
     *        means the destination file
     *
     * @throws  An IOException if it occures during execution of this method
     *          by calling other methods internaly.
     */
    public static void atomicFileCopy(java.io.File aSource     ,
                                      java.io.File aDestination)
        throws java.io.IOException
    {
        System.out.println("TODO: must be adapted to java 1.3 and support cygwin shells :-(");
        System.exit(-1);        
        
        /*TODO_JAVA
        Solution I : using nio.channel locks doesnt exists for java 1.3  :-(
        Solution II: using system call "cp" cant work with cygwin shells :-(
        
        boolean bOK = false;
        try
        {
            java.lang.Runtime aRunner = java.lang.Runtime.getRuntime();
            
            java.lang.String[] lCommands = new java.lang.String[3];
            lCommands[0] = "cp";
            lCommands[1] = aSource.getAbsolutePath();
            lCommands[2] = aDestination.getAbsolutePath();
            
            java.lang.Process aProc = aRunner.exec(lCommands);
            aProc.waitFor();
            
            bOK = (aProc.exitValue()==0);
        }
        catch(java.lang.Throwable ex)
            { bOK = false; }
            
        if (!bOK)
        {
            java.lang.String sMsg = "atomic copy from \"";
            sMsg += aSource.getAbsolutePath();
            sMsg += "\" to \"";
            sMsg += aDestination.getAbsolutePath();
            sMsg += "\" failed.";
            throw new java.io.IOException(sMsg);
        }
        */
    }

    // ____________________

    /**
     * Because the office need URLs for loading/saving documents
     * we must convert used system pathes.
     * And java use another notation for file URLs ... correct it.
     *
     * @param aSystemPath
     *          represent the file in system notation
     *
     * @return [String]
     *          a file url which represent the given system path
     */
    public static java.lang.String getFileURLFromSystemPath(java.io.File aSystemPath)
    {
        System.out.println("TODO: must be adapted to java 1.3 :-(");
        System.exit(-1);
/*TODO_JAVA        
        try
        {
            sFileURL = aSystemPath.toURI().toURL().toString();
        }
        catch( MalformedURLException exWrong )
        {
            sFileURL = null;
        }
*/        
        java.lang.String sFileURL = null;

        // problem of java: file URL's are coded with 1 slash instead of 2 or 3 ones!
        // => correct this problem first, otherwise office can't use these URL's
        if(
            (sFileURL                       != null ) &&
            (sFileURL.startsWith("file:/")  == true ) &&
            (sFileURL.startsWith("file://") == false)
          )
        {
            java.lang.StringBuffer sWorkBuffer = new java.lang.StringBuffer(sFileURL);
            sWorkBuffer.insert(6,"//");
            sFileURL = sWorkBuffer.toString();
        }

        return sFileURL;
    }

    // ____________________

    /**
     * The same as getFileURLFromSystemPath() before but uses string parameter instead
     * of a java.io.File type. It exist to supress converting of neccessary parameters in the
     * outside code. But of course getFileURLFromSystemPath(File) will be a little bit faster
     * then this method ...
     *
     * @param sSystemPath
     *          represent the file in system notation
     *
     * @return [String]
     *          a file url which represent the given system path
     */
    public static java.lang.String getFileURLFromSystemPath(java.lang.String sSystemPath)
    {
        return getFileURLFromSystemPath(new java.io.File(sSystemPath));
    }

    // ____________________

    /**
     * Does the same as getFileURLFromSystemPath() before ... but uses
     * the given protocol string (e.g."http://") insted of "file:///".
     *
     * @param aSystemPath
     *          represent the file in system notation
     *
     * @param aBasePath
     *          define the base path of the aSystemPath value,
     *          which must be replaced with the value of "sServerPath".
     *
     * @param sServerURL
     *          Will be used to replace sBasePath.
     *
     * @example
     *          System Path = "d:\test\file.txt"
     *          Base Path   = "d:\test"
     *          Server Path = "http://alaska:8000"
     *          => "http://alaska:8000/file.txt"
     *
     * @return [String]
     *          an url which represent the given system path
     *          and uses the given protocol
     */
    public static java.lang.String getURLWithProtocolFromSystemPath(java.io.File     aSystemPath,
                                                                    java.io.File     aBasePath  ,
                                                                    java.lang.String sServerURL )
    {
        System.out.println("TODO: must be adapted to java 1.3 :-(");
        System.exit(-1);
        
        java.lang.String sFileURL = FileHelper.getFileURLFromSystemPath(aSystemPath);
        java.lang.String sBaseURL = FileHelper.getFileURLFromSystemPath(aBasePath  );

        // cut last '/'!
        if (sBaseURL.lastIndexOf('/')==(sBaseURL.length()-1))
            sBaseURL = sBaseURL.substring(0,sBaseURL.length()-1);

        // cut last '/'!
        if (sServerURL.lastIndexOf('/')==(sServerURL.length()-1))
            sServerURL = sServerURL.substring(0,sServerURL.length()-1);

//TODO_JAVA        java.lang.String sURL = sFileURL.replaceFirst(sBaseURL,sServerURL);
        java.lang.String sURL = null;
        return sURL;
    }

    // ____________________

    /**
     * The same as getURLWithProtocolFromSystemPath() before but uses string parameter instead
     * of a java.io.File types. It exist to supress converting of neccessary parameters in the
     * outside code. But of course getURLWithProtocolFromSystemPath(File,File,String) will be
     * a little bit faster then this method ...
     *
     * @param sSystemPath
     *          represent the file in system notation
     *
     * @param sBasePath
     *          define the base path of the aSystemPath value,
     *          which must be replaced with the value of "sServerPath".
     *
     * @param sServerPath
     *          Will be used to replace sBasePath.
     *
     * @example
     *          System Path = "d:\test\file.txt"
     *          Base Path   = "d:\test"
     *          Server Path = "http://alaska:8000"
     *          => "http://alaska:8000/file.txt"
     *
     * @return [String]
     *          an url which represent the given system path
     *          and uses the given protocol
     */
    public static java.lang.String getURLWithProtocolFromSystemPath(java.lang.String sSystemPath,
                                                                    java.lang.String sBasePath  ,
                                                                    java.lang.String sServerPath)
    {
        return getURLWithProtocolFromSystemPath(new java.io.File(sSystemPath), new java.io.File(sBasePath), sServerPath);
    }

    //_________________________________

    /**
     * Return a list of all available files of a directory.
     * We filter sub directories. All other files
     * are returned. So they can be used for further purposes.
     * One parameter define the start directory,
     * another one enable/disable recursive search into sub directories.
     *
     * @param   aRoot
     *          the start directory, which should be analyzed.
     *
     * @param   bRecursive
     *          enable/disable search in sub directories.
     *
     * @return  [Vector]
     *          a filtered list of java java.io.File objects of all available files
     *          of the start dir (and may of its sub directories).
     */
    public static java.util.Vector getSystemFilesFromDir(java.io.File aRoot     ,
                                                         boolean      bRecursive)
    {
        java.io.File[] lAllFiles = aRoot.listFiles();
        if (lAllFiles == null)
            return null;

        int              c              = lAllFiles.length;
        java.util.Vector lFilteredFiles = new java.util.Vector(c);
        for (int i=0; i<c; ++i)
        {
            // simple files!
            if (lAllFiles[i].isFile())
                lFilteredFiles.add(lAllFiles[i]);
            else
            // recursion?
            if (bRecursive && lAllFiles[i].isDirectory())
            {
                java.util.Vector lSubFiles = FileHelper.getSystemFilesFromDir(lAllFiles[i],bRecursive);
                if (lSubFiles != null)
                {
                    java.util.Enumeration aSnapshot = lSubFiles.elements();
                    while (aSnapshot.hasMoreElements())
                        lFilteredFiles.add(aSnapshot.nextElement());
                }
            }
        }

        return lFilteredFiles;
    }

    //_________________________________
    /** it converts the given name (e.g. an internal type name) to
     *  an usable system file name.
     *
     *  Do so some special characters (e.g. "/") must be replaced with other ones.
     *
     *  @param  sName
     *              the name, which should be analyzed and converted.
     *
     *  @return A valid system file name, which should be similar to the
     *          given name, but does not contain special characters any longer.
     */
    public static java.lang.String convertName2FileName(String sName)
    {
        char             c         = '_';
        java.lang.String sFileName = sName;

        sFileName = sFileName.replace('\\',c);
        sFileName = sFileName.replace('/' ,c);
        sFileName = sFileName.replace('&' ,c);
        sFileName = sFileName.replace(':' ,c);
        sFileName = sFileName.replace(';' ,c);
        sFileName = sFileName.replace('.' ,c);
        sFileName = sFileName.replace(' ' ,c);
        sFileName = sFileName.replace('-' ,c);
        sFileName = sFileName.replace('+' ,c);
        sFileName = sFileName.replace('#' ,c);
        sFileName = sFileName.replace('*' ,c);
        sFileName = sFileName.replace('~' ,c);
        sFileName = sFileName.replace('?' ,c);
        sFileName = sFileName.replace('!' ,c);
        sFileName = sFileName.replace('=' ,c);
        sFileName = sFileName.replace('(' ,c);
        sFileName = sFileName.replace(')' ,c);
        sFileName = sFileName.replace('[' ,c);
        sFileName = sFileName.replace(']' ,c);
        sFileName = sFileName.replace('{' ,c);
        sFileName = sFileName.replace('}' ,c);
        sFileName = sFileName.replace('%' ,c);
        sFileName = sFileName.replace('$' ,c);
        sFileName = sFileName.replace('�' ,c);

        return sFileName;
    }

    //___________________________________________

    /** it removes all child nodes of a file system directory.
     *
     *  @param  aDirectory
     *          points to the directory, which should be made empty.
     *
     *  @param  bFilesOnly
     *          force deletion of files only. If its set to TRUE,
     *          no subdirectory will be removed.
     *
     *  @throw  [java.io.IOException]
     *          if some of the child nodes couldn't be removed.
     */
    public static void makeDirectoryEmpty(java.io.File aDirectory,
                                          boolean      bFilesOnly)
        throws java.io.IOException
    {
        if (!aDirectory.isDirectory())
            throw new java.io.FileNotFoundException("\""+aDirectory.toString()+"\" is not a directory.");

        java.io.File[] lChilds = aDirectory.listFiles();
        for (int f=0; f<lChilds.length; ++f)
        {
            if (lChilds[f].isDirectory())
            {
                FileHelper.makeDirectoryEmpty(lChilds[f], bFilesOnly);
                if (!bFilesOnly)
                {
                    if (!lChilds[f].delete())
                        throw new java.io.IOException("\""+lChilds[f].toString()+"\" could not be deleted.");
                }
            }
            else
            {
                if (!lChilds[f].delete())
                    throw new java.io.IOException("\""+lChilds[f].toString()+"\" could not be deleted.");
            }
        }
    }

    //___________________________________________

    /** it try to generate a new file with a unique ID
     *  inside given directory.
     *
     *  Call this method with a directory and a base name for
     *  a file. It will be used to generate a new files inside
     *  the directory. Existing files will be checked and new file
     *  name will be tested till a non existing file name would be found.
     *
     *  @param  aBaseDir
     *          must be a system path
     *          e.g.: "c:\temp"
     *
     *  @param  sBaseName
     *          must be a system file name without extensions.
     *          e.g.: "myfile_"
     *
     *  @param  sExtension
     *          the whished extension.
     *          e.g.: "dat"
     *
     *  @return A valid file object, if an unique file could be created -
     *          Null otherwhise.
     *          e.g.: "c:\temp\myfile_1.dat"
     */
    public static java.io.File createUniqueFile(java.io.File     aBaseDir  ,
                                                java.lang.String sBaseName ,
                                                java.lang.String sExtension)
    {
        java.io.File aBaseFile = new java.io.File(aBaseDir, sBaseName);
        java.io.File aFile     = null;
        long         nr        = 0;
        while (aFile == null && nr < java.lang.Long.MAX_VALUE)
        {
            java.lang.String sFileName = aBaseFile.getPath() + java.lang.String.valueOf(nr) + "." + sExtension;
            aFile = new java.io.File(sFileName);
            if (aFile.exists())
                aFile=null;
            ++nr;
        }
        return aFile;
    }

    //___________________________________________

    /** writes the given string buffer into the specified file.
     *
     *  Further it can be set, if the file should be expanded
     *  or replaced by this new string buffer.
     *
     *  @param  aFile
     *          must point to a system file. It can already exist!
     *          e.g.: "c:\temp\test.txt"
     *                "/tmp/test.txt"
     *
     *  @param  bAppend
     *          specify if an already existing file will be
     *          expanded or replaced.
     *
     *  @param  sEncoding
     *          will be used to encode the string content inside the file.
     *          e.g.: "UTF-8"
     *
     *  @param  sText
     *          the new string content for this file.
     */
    public static void writeTextToFile(java.io.File     aFile    ,
                                       boolean          bAppend  ,
                                       java.lang.String sEncoding,
                                       java.lang.String sText    )
        throws java.io.IOException
    {
        java.io.FileOutputStream   aStream = new java.io.FileOutputStream(aFile.getAbsolutePath(), bAppend);
        java.io.OutputStreamWriter aWriter = new java.io.OutputStreamWriter(aStream, sEncoding);
        aWriter.write(sText, 0, sText.length());
        aWriter.flush();
        aWriter.close();
        if (!aFile.exists())
            throw new java.io.IOException("File \""+aFile.getAbsolutePath()+"\" not written correctly.");
    }
}
