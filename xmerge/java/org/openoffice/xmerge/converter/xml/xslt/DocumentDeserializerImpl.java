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

package org.openoffice.xmerge.converter.xml.xslt;

import org.w3c.dom.NodeList;
import org.w3c.dom.Node;
import org.w3c.dom.Element;

import java.io.InputStream;
import java.io.IOException;
import java.util.Enumeration;



import org.openoffice.xmerge.Document;
import org.openoffice.xmerge.ConvertData;
import org.openoffice.xmerge.ConvertException;
import org.openoffice.xmerge.DocumentDeserializer;
import org.openoffice.xmerge.converter.dom.DOMDocument;
//import org.openoffice.xmerge.converter.xml.sxw.SxwDocument;
import org.openoffice.xmerge.converter.xml.xslt.GenericOfficeDocument;
import org.openoffice.xmerge.util.Debug;
import org.openoffice.xmerge.util.registry.ConverterInfo;

// Imported TraX classes
import javax.xml.transform.TransformerFactory;
import javax.xml.transform.Transformer;
import javax.xml.transform.dom.DOMSource;
import javax.xml.transform.dom.DOMResult;
import javax.xml.transform.TransformerException;
import javax.xml.transform.TransformerConfigurationException;

//
//import org.apache.xalan.serialize.Serializer;
//import org.apache.xalan.serialize.SerializerFactory;
//import org.apache.xalan.templates.OutputProperties;

import javax.xml.parsers.DocumentBuilder;
import javax.xml.parsers.DocumentBuilderFactory;

// Imported java classes
import java.io.FileNotFoundException;


/**
 *  <p>Xslt implementation of
 *  org.openoffice.xmerge.DocumentSerializer
 *  for the {@link
 *  org.openoffice.xmerge.converter.xml.xslt.PluginFactoryImpl
 *  PluginFactoryImpl}.</p>
 *
 *  <p>The <code>serialize</code> method transforms the DOM
 *  document from the given <code>Document</code> object by 
 *  means of a supplied Xsl Stylesheet.</p>
 *
 *  @author      Aidan Butler
 */
public final class DocumentDeserializerImpl
    implements  DocumentDeserializer {

    /**  A <code>ConvertData</code> object assigned to this object. */
    private InputStream is = null;
    private ConvertData cd = null;
    private PluginFactoryImpl pluginFactory = null;

    /**
     *  Constructor that assigns the given <code>ConvertData</code>
     *  to this object.
     *
     *  @param  pf  A <code>PluginFactoryImpl</code> object.
     *              
     *  @param  cd  A <code>ConvertData</code> object to read data for
     *              the conversion process by the <code>deserialize</code>
     *              method.
     */
    public DocumentDeserializerImpl(PluginFactoryImpl pf,ConvertData cd) {
        this.cd = cd;
    pluginFactory = pf;
    }


    /**
     *  Convert the given <code>DOMDocument</code> format object
     *  into a <code>SxwDocument</code> object.
     *
     *  @return  Resulting <code>SxwDocument</code> object.
     *
     *  @throws ConvertException   If any conversion error occurs.
     *  @throws IOException        If any I/O error occurs.
     */
    public Document deserialize() throws ConvertException, IOException {

    Enumeration enum = cd.getDocumentEnumeration();
    org.w3c.dom.Document domDoc=null;
    DOMDocument docOut=null;
    DOMResult domTree=null;
    GenericOfficeDocument doc = null;
    
    while (enum.hasMoreElements()) {       
         docOut = (DOMDocument) enum.nextElement();
    }
    domDoc = docOut.getContentDOM();
    
    
    try{
        domTree=transform(domDoc);
        
     }
    catch(Exception e){
        System.out.println("The following error occurred:"+e);
    }
    GenericOfficeDocument sxwDoc = new GenericOfficeDocument("output");
    sxwDoc.initContentDOM();
    sxwDoc.setContentDOM(domTree.getNode());
        
    return sxwDoc;
    
    }

 /*
     * This method performs the sxl transformation on the supplied Dom Tree. 
     *
     *  Xslt transformation code
     *
     * @throws TransformerException,TransformerConfigurationException
     *		  , FileNotFoundException,IOException
     *
     */


    private DOMResult transform(org.w3c.dom.Document xmlDoc) 
       throws TransformerException,TransformerConfigurationException
          , FileNotFoundException,IOException{

       //System.out.println("\nTransforming...");
       DOMResult xmlDomResult = new DOMResult();
       ConverterInfo ci = pluginFactory.getConverterInfo();
      
       try{
          DocumentBuilderFactory dFactory = DocumentBuilderFactory.newInstance();
          dFactory.setNamespaceAware(true);
          DocumentBuilder dBuilder = dFactory.newDocumentBuilder();
     
          String teststr = ci.getXsltDeserial();
          teststr= teststr.substring(0,6);
          org.w3c.dom.Document xslDoc=null;
              if ((teststr.equals("http:/"))||(teststr.equals("file:/"))
                                        ||(teststr.equals("jar://"))){
              //System.out.println(ci.getXsltDeserial());
              xslDoc= dBuilder.parse(ci.getXsltDeserial());

          }
          else{      
              //System.out.println(ci.getJarName()+"!/"+ci.getXsltDeserial());
              xslDoc = dBuilder.parse(
                  "jar:"+ci.getJarName()+"!/"+ci.getXsltDeserial());
          }

        
          DOMSource xslDomSource = new DOMSource(xslDoc);
          DOMSource xmlDomSource = new DOMSource(xmlDoc);
        
           //call the tranformer using the XSL, Source and Result dom.
          TransformerFactory tFactory = TransformerFactory.newInstance();	
      
           Transformer transformer = tFactory.newTransformer(xslDomSource);
          transformer.transform(xmlDomSource, xmlDomResult);
          /*
          // Serialize for output to standard out
          Serializer serializer = SerializerFactory.getSerializer
                                   (OutputProperties.getDefaultMethodProperties("xml"));
          serializer.setOutputStream(System.out);
          serializer.asDOMSerializer().serialize(xmlDomResult.getNode());
          */
  
          //System.out.println("\n** Transform Complete ***");
         
       }
       catch(Exception e){
              System.out.println("An error occured in the transformation : "+e);
       }
       return xmlDomResult;
     }

}

