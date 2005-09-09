/************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: ActiveSyncDriver.java,v $
 *
 *  $Revision: 1.3 $
 *
 *  last change: $Author: rt $ $Date: 2005-09-09 11:39:24 $
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

package org.openoffice.xmerge.util;

import java.io.File;
import java.io.FileOutputStream;
import java.io.FileInputStream;
import java.util.StringTokenizer;

import java.net.URL;

import org.openoffice.xmerge.Convert;
import org.openoffice.xmerge.Document;
import org.openoffice.xmerge.ConvertData;
import org.openoffice.xmerge.ConverterFactory;
import org.openoffice.xmerge.util.registry.ConverterInfo;
import org.openoffice.xmerge.util.registry.ConverterInfoMgr;
import org.openoffice.xmerge.util.registry.ConverterInfoReader;

public class ActiveSyncDriver {
    public static void main(String[] args) {
        if (args.length != 4) {
            return;
        }
            
        ActiveSyncDriver asd = new ActiveSyncDriver();
        
        try {
            // At the moment can't really signal back to the calling DLL
            asd.Convert(args[0], args[1], args[2], args[3]);
        } 
        catch (Exception e) {
            return;
        }
    }
    
    
    private boolean Convert(String srcMime, String dstMime, String srcFile, String dstFile) throws Exception {
        /*
         * The classpath passed in by XMergeSync.dll should contain all of the
         * jar files, but at the least it will contain xmerge.jar, so strip off
         * the xmerge.jar portion and use the remainder to provide a root for
         * the Pocket Word and Pocket Excel plugins.
         */
        String ooClassDir = null;
        String strClassPath = System.getProperty("java.class.path");      
        
        StringTokenizer st = new StringTokenizer(strClassPath, ";");
        
        // There should be at least one element, but just in case
        while (st.hasMoreTokens()) {
            String s = st.nextToken();
            
            if (s.endsWith("xmerge.jar")) {
                ooClassDir = s.substring(0, s.indexOf("xmerge.jar"));
            }
        }
        
        if (ooClassDir == null) {
            return true;
        }
        
        
        /*
         * The XMergeSync.dll should will have checked for the presence of the
         * jars at the same location already.
         *
         * Because they can be installed separately, though, the MIME types need
         * to be check to see which one to load.
         */
        File pluginJar = null;
        if (srcMime.equals("staroffice/sxw") || srcMime.equals("application/x-pocket-word"))
        {
            pluginJar = new File(ooClassDir + "pocketWord.jar");
        }
        else if (srcMime.equals("staroffice/sxc") || srcMime.equals("application/x-pocket-excel"))
        {
            pluginJar = new File(ooClassDir + "pexcel.jar");
        }
               
        ConverterInfoReader cirPlugin = new ConverterInfoReader(pluginJar.toURL().toString(), false);     
        
        ConverterInfoMgr.addPlugIn(cirPlugin.getConverterInfoEnumeration());
        
        ConverterFactory cf = new ConverterFactory();
        Convert conv = cf.getConverter(srcMime, dstMime);
                
        if (conv == null) {
            return false;
        }
        
        // Everything is registered so do the conversion
        FileInputStream fis = new FileInputStream(srcFile);
        FileOutputStream fos = new FileOutputStream(dstFile);
        
        conv.addInputStream(srcFile, fis);
        
        ConvertData dataOut;
        try {
            dataOut = conv.convert();
        }
        catch (Exception e) {
            return false;
        }
        
        if (dataOut == null) {
            return false;
        }

        // Get the document and write it out.
        Document doc = (Document)dataOut.getDocumentEnumeration().nextElement();      
        if (doc == null) {
            return false;
        }
        
        doc.write(fos);
        fos.flush();
        fos.close();
        
        return true;         
    }
}
