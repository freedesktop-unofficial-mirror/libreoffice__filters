/************************************************************************
 *
 *  DocumentDeserializerImpl.java
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
 *  Copyright: 2001 by Sun Microsystems, Inc.
 *
 *  All Rights Reserved.
 *
 *  Contributor(s): _______________________________________
 *
 *
 ************************************************************************/


package org.openoffice.xmerge.converter.xml.sxw.pocketword;

import org.openoffice.xmerge.ConvertData;
import org.openoffice.xmerge.ConvertException;
import org.openoffice.xmerge.Document;
import org.openoffice.xmerge.DocumentDeserializer;

import org.openoffice.xmerge.converter.xml.OfficeConstants;
import org.openoffice.xmerge.converter.xml.sxw.SxwDocument;

import org.openoffice.xmerge.converter.xml.ParaStyle;
import org.openoffice.xmerge.converter.xml.TextStyle;
import org.openoffice.xmerge.converter.xml.StyleCatalog;

import org.openoffice.xmerge.util.OfficeUtil;

import java.io.InputStream;
import java.io.IOException;
import java.io.FileInputStream;
import java.io.FileDescriptor;

import java.util.Enumeration;
import java.util.Vector;

import org.w3c.dom.NodeList;
import org.w3c.dom.Node;
import org.w3c.dom.Element;


/**
 * <p>Pocket Word implementation of <code>DocumentDeserializer</code>
 * for the {@link
 * org.openoffice.xmerge.converter.xml.sxw.pocketword.PluginFactoryImpl
 * PluginFactoryImpl}.</p>
 *
 * <p>This converts a Pocket Word file to an OpenOffice Writer XML DOM.</p>
 *
 * @author  Mark Murnane
 * @version 1.1
 */
public final class DocumentDeserializerImpl 
            implements DocumentDeserializer, OfficeConstants {
                
    private PocketWordDocument pswDoc = null;
    private SxwDocument sxwDoc = null;
    private String docName;
    
    private StyleCatalog styleCat = null;
    
    
    /**
     * Initialises a new <code>DocumentDeserializerImpl</code> using the 
     * supplied <code>ConvertData</code>.</p>
     *
     * <p>The <code>Document</code> objects in the <code>ConvertData</code>
     *    should be {@link 
     *    org.openoffice.xmerge.converter.xml.sxw.pocketword.PocketWordDocument
     *    PocketWordDocument} objects.</p>
     *
     * @param   cd      ConvertData containing a <code>PocketWordDocument</code>
     *                  for conversion.
     */
    public DocumentDeserializerImpl(ConvertData cd) {
        Enumeration e = cd.getDocumentEnumeration();       
        
        // A Pocket Word file is composed of one binary file
        while (e.hasMoreElements()) {
            pswDoc = (PocketWordDocument)e.nextElement();
        }
        
        docName = pswDoc.getName();
    }
    
    
    /**
     *  <p>Convert the data passed into the <code>DocumentDeserializer</code>
     *  constructor into the OpenOffice Writer <code>Document</code>
     *  format.</p>
     *
     *  <p>This method may or may not be thread-safe.  It is expected
     *  that the user code does not call this method in more than one
     *  thread.  And for most cases, this method is only done once.</p>
     *
     *  @return  The resulting <code>Document</code> object from conversion.
     *
     *  @throws  ConvertException  If any Convert error occurs.
     *  @throws  IOException       If any I/O error occurs.
     */
    public Document deserialize() throws IOException, ConvertException {      
        Enumeration pe = pswDoc.getParagraphEnumeration();
        
        sxwDoc = new SxwDocument (docName);
        sxwDoc.initContentDOM();
                    
        // Default to an initial 5 entries in the catalog.  
        styleCat = new StyleCatalog(5);

        try {
            buildDocument(pe);        
        }
        catch (Exception e) {
            e.printStackTrace();
            throw new ConvertException("Error building OpenOffice Writer DOM: "
                                        + e.toString());
            
        }
                
        return sxwDoc;
    }
    
    
    /**
     * This method actually takes care of the conversion.  
     *
     * @param   data    An Enumeration of all Paragraphs in the Pocket Word doc.
     *
     * @return  The OpenOffice Writer XML representation of the data.
     *
     * @throws  IOException     If any I/O errors occur.
     */
    private void buildDocument(Enumeration data) throws IOException {
        
        org.w3c.dom.Document doc = sxwDoc.getContentDOM();
        
        /*
         * There should be only one each of office:body and 
         * office:automatic-styles in each document.
         */
        Node bodyNode = doc.getElementsByTagName(TAG_OFFICE_BODY).item(0);
        
        // Not every document has an automatic style tag
        Node autoStylesNode = doc.getElementsByTagName(
                                        TAG_OFFICE_AUTOMATIC_STYLES).item(0);
        if (autoStylesNode == null) {
            autoStylesNode = doc.createElement(TAG_OFFICE_AUTOMATIC_STYLES);
            doc.insertBefore(autoStylesNode, bodyNode);
        }


        // Needed for naming new styles
        int paraStyles = 1;
        int textStyles = 1;
          
        // Pocket Word has no concept of a list.
        Element listNode = null;
        

        // Down to business ...
        while (data.hasMoreElements()) {
            Paragraph p = (Paragraph)data.nextElement();
            Element paraNode  = doc.createElement(TAG_PARAGRAPH);
                        
            // Set paragraph style information here
            ParaStyle pStyle = p.makeStyle();
            if (pStyle == null) {
                paraNode.setAttribute(ATTRIBUTE_TEXT_STYLE_NAME, 
                                        PocketWordConstants.DEFAULT_STYLE);
            }
            else {
                // Create paragraph style
                pStyle.setName(new String("PS" + paraStyles++));
                paraNode.setAttribute(ATTRIBUTE_TEXT_STYLE_NAME, pStyle.getName());
                styleCat.add(pStyle);
            }
            
            
            /*
             * For each of the paragraphs, process each segment.
             * There will always be at least one.
             */
            Enumeration paraData = p.getSegmentsEnumerator();
            Vector textSpans = new Vector(0, 1);
            
            do {
                ParagraphTextSegment pts = (ParagraphTextSegment)paraData.nextElement();
                Element span = doc.createElement(OfficeConstants.TAG_SPAN);
                
                TextStyle ts = pts.getStyle();
                
                if (ts != null) {
                    ts.setName(new String("TS" + textStyles++));
                    span.setAttribute(ATTRIBUTE_TEXT_STYLE_NAME, ts.getName());
                    styleCat.add(ts);
                }
                else {
                    span.setAttribute(ATTRIBUTE_TEXT_STYLE_NAME, 
                                        PocketWordConstants.DEFAULT_STYLE);
                }
                
                // If this isn't a blank paragraph
                if (pts.getText() != null && !pts.getText().equals("")) {
                    Node[] children = OfficeUtil.parseText(pts.getText(), doc);
                    
                    for (int j = 0; j < children.length; j++) {
                        span.appendChild(children[j]);
                    }
                }

                textSpans.add(span);
                
            } while (paraData.hasMoreElements());
            
            
            /*
             * Special case for the first span.  If it has no style, then
             * it shouldn't be a span, so just add its children with style
             * set as standard.
             */ 
            Element firstSpan = (Element)textSpans.elementAt(0);
            String  styleName = firstSpan.getAttribute(ATTRIBUTE_TEXT_STYLE_NAME);
            if (styleName.equals(PocketWordConstants.DEFAULT_STYLE)) {
                NodeList nl = firstSpan.getChildNodes();
                int len = nl.getLength();
                
                for (int i = 0; i < len; i++) {
                    paraNode.appendChild(nl.item(i));
                }
            }
            else {
                paraNode.appendChild(firstSpan);
            }

            // The rest are spans, so just add them
            for (int i = 1; i < textSpans.size(); i++) {
                paraNode.appendChild((Node)textSpans.elementAt(i));
            }
            
           
            /*
             * Pocket Word doesn't support lists, but it does have bulleted
             * paragraphs that are essentially the same thing.  
             *
             * Unlike OpenOffice Writer, a blank paragraph can be bulleted 
             * as well.  This will be handled by inserting a blank paragraph
             * into the unordered list, but OpenOffice Writer will not display
             * an item at that point in the list.
             */
            if (p.isBulleted()) {
                if (listNode == null) {
                    listNode = doc.createElement(TAG_UNORDERED_LIST);
                }
                Element listItem = doc.createElement(TAG_LIST_ITEM);
                listItem.appendChild(paraNode);
                listNode.appendChild(listItem);
            }
            else {            
                if (listNode != null) {
                    bodyNode.appendChild(listNode);
                    listNode = null;
                }
                bodyNode.appendChild(paraNode);
            }
        } // End processing paragraphs
        
        
        // Now write the style catalog to the document
        NodeList nl = styleCat.writeNode(doc, "dummy").getChildNodes();
        int nlLen = nl.getLength();     // nl.item reduces the length
        for (int i = 0; i < nlLen; i++) {
            autoStylesNode.appendChild(nl.item(0));
        }
    }
}
