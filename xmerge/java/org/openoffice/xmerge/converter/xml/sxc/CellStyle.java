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

package org.openoffice.xmerge.converter.xml.sxc;

import java.awt.Color;
import java.io.IOException;

import org.w3c.dom.NodeList;
import org.w3c.dom.Node;
import org.w3c.dom.NamedNodeMap;
import org.w3c.dom.Element;

import org.openoffice.xmerge.Document;
import org.openoffice.xmerge.ConverterCapabilities;
import org.openoffice.xmerge.converter.xml.OfficeDocument;
import org.openoffice.xmerge.converter.xml.Style;
import org.openoffice.xmerge.converter.xml.StyleCatalog;
import org.openoffice.xmerge.converter.xml.sxw.SxwDocument;
import org.openoffice.xmerge.util.Debug;

/**
 *  Represents a text <code>Style</code> in an OpenOffice document.
 *
 *  @author	Martin Maher 
 */
public class CellStyle extends Style implements Cloneable {

    private Format fmt = new Format();

    /**
     *  Constructor for use when going from DOM to client device format.
     *
     *  @param  Node  The <i>style:style</i> <code>Node</code> containing
     *                the <code>Style</code>.  (This <code>Node</code> is
     *                assumed have a <i>family</i> attribute of <i>text</i>).
     *  @param  sc    The <code>StyleCatalog</code>, which is used for
     *                looking up ancestor <code>Style</code> objects.
     */
    public CellStyle(Node node, StyleCatalog sc) {
        super(node, sc);
        
        // Run through the attributes of this node, saving
        // the ones we're interested in.
        NamedNodeMap attrNodes = node.getAttributes();
        if (attrNodes != null) {
            int len = attrNodes.getLength();
            for (int i = 0; i < len; i++) {
                Node attr = attrNodes.item(i);
                handleAttribute(attr.getNodeName(), attr.getNodeValue());
            }
        }
        
        // Look for children.  Only ones we care about are "style:properties"
        // nodes.  If any are found, recursively traverse them, passing
        // along the style element to add properties to.
        if (node.hasChildNodes()) {
            NodeList children = node.getChildNodes();
            int len = children.getLength();
            for (int i = 0; i < len; i++) {
                Node child = children.item(i);
                String name = child.getNodeName();
                if (name.equals("style:properties")) {
                    NamedNodeMap childAttrNodes = child.getAttributes();
                    if (childAttrNodes != null) {
                        int nChildAttrNodes = childAttrNodes.getLength();
                        for (int j = 0; j < nChildAttrNodes; j++) {
                            Node attr = childAttrNodes.item(j);
                            handleAttribute(attr.getNodeName(),
                            attr.getNodeValue());
                        }
                    }
                }
            }
        }
    }
    
    
    /**
     *  Constructor for use when going from client device format to DOM
     *
     *  @param  name     Name of text <code>Style</code>.  Can be null.
     *  @param  family   Family of text <code>Style</code> (usually
     *                   <i>text</i>).  Can be null.
     *  @param  parent   Name of parent text <code>Style</code>, or null
     *                   for none.
     *  @param  mask     Bitwise mask of text attributes that this text
     *                   <code>Style</code> will specify.  Can be any
     *                   combination of the following, or'ed together:
     *                   {@link #BOLD}, {@link #ITALIC}, {@link #UNDERLINE},
     *                   {@link #STRIKETHRU}, {@link #SUPERSCRIPT},
     *                   {@link #SUBSCRIPT}.  This parameter determines what
     *                   attributes this <code>Style</code> will specify.
     *                   When an attribute is specified in a
     *                   <code>Style</code>, its value can be either
     *                   <i>on</i> or <i>off</i>.  The on/off value for
     *                   each attribute is controlled by the
     *                   <code>values</code> parameter.
     *  @param values    Values of text attributes that this text
     *                   <code>Style</code> will be setting.  Any of the
     *                   attributes ({@link #BOLD}, etc) listed for
     *                   <code>mask</code> can be used for this.
     *  @param fontSize  Font size in points.
     *  @param fontName  Name of font.
     *  @param sc        The <code>StyleCatalog</code>, which is used for
     *                   looking up ancestor <code>Style</code> objects.
     */
    public CellStyle(String name, String family, String parent,
    int mask, int values, int fontSize, String fontName, StyleCatalog sc) {
        super(name, family, parent, sc);
        fmt = new Format(values, mask, fontSize, fontName);
    }

    public CellStyle(String name, String family, String parent,Format fmt, StyleCatalog sc) {
        super(name, family, parent, sc);
        this.fmt = fmt;
    }

    /**
     * Returns the <code>Format</code> object for this particular style
     *
     * @returns the <code>Format</code> object 
     */
    public Format getFormat() {
        return fmt;
    }
    
    /**
     *  Parse a color specification of the form <i>#rrggbb</i>
     *
     *  @param  value  <code>Color</code> specification to parse.
     *
     *  @returns  The <code>Color</code> associated the value.
     */
    private Color parseColorString(String value) {
        // Assume color value is of form #rrggbb
        String r = value.substring(1, 3);
        String g = value.substring(3, 5);
        String b = value.substring(5, 7);
        int red = 0;
        int green = 0;
        int blue = 0;
        try {
            red = Integer.parseInt(r, 16);
            green = Integer.parseInt(g, 16);
            blue = Integer.parseInt(b, 16);
        } catch (NumberFormatException e) {
            Debug.log(Debug.ERROR, "Problem parsing a color string", e);
        }
        return new Color(red, green, blue);
    }
    

    /**
     *  Set an attribute.
     *
     *  @param  attr   The attribute to set.
     *  @param  value  The attribute value to set.
     */
    private void handleAttribute(String attr, String value) {
        
        if (attr.equals("fo:font-weight")) {
            fmt.setAttribute(Format.BOLD, value.equals("bold"));
        }
        
        else if (attr.equals("fo:font-style")) {
            if (value.equals("italic")  || value.equals("oblique"))
                fmt.setAttribute(Format.ITALIC, true);
            else if (value.equals("normal"))
                fmt.setAttribute(Format.ITALIC, false);
        }
        
        else if (attr.equals("style:text-underline")) {
            fmt.setAttribute(Format.UNDERLINE, !value.equals("none"));
        }
        
        else if (attr.equals("style:text-crossing-out")) {
            fmt.setAttribute(Format.STRIKETHRU, !value.equals("none"));
        }
        
        else if (attr.equals("style:text-position")) {
            if (value.startsWith("super "))
                fmt.setAttribute(Format.SUPERSCRIPT, true);
            else if (value.startsWith("sub "))
                fmt.setAttribute(Format.SUBSCRIPT, true);
            else if (value.startsWith("0% "))
                fmt.setAttribute(Format.SUPERSCRIPT | Format.SUBSCRIPT, false);
            else {
                String firstPart = value.substring(0, value.indexOf(" "));
                if (firstPart.endsWith("%")) {
                    firstPart = firstPart.substring(0, value.indexOf("%"));
                    int amount;
                    try {
                        amount = Integer.parseInt(firstPart);
                    } catch (NumberFormatException e) {
                        amount = 0;
                        Debug.log(Debug.ERROR, "Problem with style:text-position tag", e);
                    }
                    if (amount < 0) fmt.setAttribute(Format.SUBSCRIPT, true);
                    else if (amount > 0) fmt.setAttribute(Format.SUPERSCRIPT, false);
                }
            }
        }
        
        else if (attr.equals("fo:font-size")) {
            if (value.endsWith("pt")) {
                String num = value.substring(0, value.length() - 2);
                fmt.setFontSize(Integer.parseInt(num));
            }
        }
        
        else if (attr.equals("style:font-name"))
            fmt.setFontName(value);
        
        else if (attr.equals("fo:color"))
            fmt.setForeground(parseColorString(value));

        else if (attr.equals("style:text-background-color"))
            fmt.setBackground(parseColorString(value));
            
        else if (attr.equals("fo:text-align")) {
            fmt.setAlign(Format.RIGHT_ALIGN);
            if(value.equals("center")) {
                fmt.setAlign(Format.CENTER_ALIGN);
            } else if(value.equals("end")) {
                fmt.setAlign(Format.RIGHT_ALIGN);
            } else if(value.equals("start")) {
                fmt.setAlign(Format.LEFT_ALIGN);
            }
        }
        
        else if (isIgnored(attr)) {}
        
        else {
            Debug.log(Debug.INFO, "CellStyle Unhandled: " + attr + "=" + value);
        }
    }
    
    
    /**
     *  Return a <code>Style</code> object corresponding to this one, 
     *  but with all of the inherited information from parent
     *  <code>Style</code> objects filled in.  The object returned will
     *  be a new object, not a reference to this object, even if it does
     *  not need any information added.
     *
     *  @return  The <code>StyleCatalog</code> in which to look up
     *           ancestors.
     */
    public Style getResolved() {
        // Create a new object to return, which is a clone of this one.
        CellStyle resolved = null;
        try {
            resolved = (CellStyle)this.clone();
        } catch (Exception e) {
            Debug.log(Debug.ERROR, "Can't clone", e);
        }
        
        // Look up the parentStyle.  (If there is no style catalog
        // specified, we can't do any lookups.)
        CellStyle parentStyle = null;
        if (sc != null) {
            if (parent != null) {
                parentStyle = (CellStyle)sc.lookup(parent, family, null,
                           this.getClass());
                if (parentStyle == null)
                    Debug.log(Debug.ERROR, "parent style lookup of "
                      + parent + " failed!");
                else
                    parentStyle = (CellStyle)parentStyle.getResolved();

            } else if (!name.equals("DEFAULT_STYLE")) {
                parentStyle = (CellStyle)sc.lookup("DEFAULT_STYLE", null,
                    null, this.getClass());
            }
        }
        
        // If we found a parent, for any attributes which we don't have
        // set, try to get the values from the parent.
        if (parentStyle != null) {
            parentStyle = (CellStyle)parentStyle.getResolved();
            Format parentFormat = parentStyle.getFormat();
            Format resolvedFormat = resolved.getFormat();
               
            if ((fmt.getFontSize() == 0) && (parentFormat.getFontSize() != 0))
                resolvedFormat.setFontSize(parentFormat.getFontSize());
            if ((fmt.getFontName() == null) && (parentFormat.getFontName() != null))
                resolvedFormat.setFontName(parentFormat.getFontName());
            if ((fmt.getForeground() == null) && (parentFormat.getForeground() != null))
                resolvedFormat.setForeground(parentFormat.getForeground());
            if ((fmt.getBackground() == null) && (parentFormat.getBackground() != null))
                resolvedFormat.setBackground(parentFormat.getBackground());
            for (int m = Format.BOLD; m <= Format.SUBSCRIPT; m = m << 1) {
                if ((fmt.getAttribute(m)) && (parentFormat.getAttribute(m))) {
                    resolvedFormat.setAttribute(m, parentFormat.getAttribute(m));
                    // resolved.mask |= m;
                    // resolved.values |= (parentStyle.mask & m);
                }
            }
            
        }
        return resolved;
    }
    
    
    /**
     *  Create a new <code>Node</code> in the <code>Document</code>, and
     *  write this <code>Style</code> to it.
     *
     *  @param  parentDoc  Parent <code>Document</code> of the
     *                    <code>Node</code> to create.
     *  @param  name       Name to use for the new <code>Node</code> (e.g.
     *                    <i>style:style</i>)
     *
     *  @return  Created <code>Node</code>.
     */
    public Node createNode(org.w3c.dom.Document parentDoc, String name) {
        Element node = parentDoc.createElement(name);
        writeAttributes(node);
        return node;
    }
    
    
    /**
     *  Return true if <code>style</code> specifies as much or less 
     *  than this <code>Style</code>, and nothing it specifies
     *  contradicts this <code>Style</code>.
     *
     *  @param  style  The <code>Style</code> to check.
     *
     *  @return  true if <code>style</code> is a subset, false
     *           otherwise.
     */
    public boolean isSubset(Style style) {
        if (style.getClass() != this.getClass()) 
                return false;
        CellStyle tStyle = (CellStyle)style;
        
        Format rhs = tStyle.getFormat();

        if(!fmt.isSubset(rhs))
            return false;

        return true;
    }
    
    
    /**
     *  Write this <code>Style</code> object's attributes to a
     *  <code>Node</code> in the <code>Document</code>.
     *
     *  @param  node  The <code>Node</code> to add <code>Style</code>
     *                attributes.
     */
    public void writeAttributes(Element node) {
        
        if (fmt.getAlign()==Format.RIGHT_ALIGN)
            node.setAttribute("fo:text-align", "end");
        
        if (fmt.getAlign()==Format.LEFT_ALIGN)
            node.setAttribute("fo:text-align", "start");
        
        if (fmt.getAlign()==Format.CENTER_ALIGN)
            node.setAttribute("fo:text-align", "center");
        
        if (fmt.getAttribute(Format.BOLD))
            node.setAttribute("fo:font-weight", "bold");
        
        if (fmt.getAttribute(Format.ITALIC))
            node.setAttribute("fo:font-style", "italic");
        
        if (fmt.getAttribute(Format.UNDERLINE))
            node.setAttribute("style:text-underline", "single");
        
        if (fmt.getAttribute(Format.STRIKETHRU))
            node.setAttribute("style:text-crossing-out", "single-line");
        
        if (fmt.getAttribute(Format.SUPERSCRIPT))
            node.setAttribute("style:text-position", "super 58%");
        
        if (fmt.getAttribute(Format.SUBSCRIPT))
            node.setAttribute("style:text-position", "sub 58%");
        
        if (fmt.getFontSize() != 0) {
            Integer fs = new Integer(fmt.getFontSize());
            node.setAttribute("fo:font-size", fs.toString() + "pt");
        }
        
        if (fmt.getFontName() != null)
            node.setAttribute("style:font-name", fmt.getFontName());
            
        if (fmt.getForeground() != null)
            node.setAttribute("fo:color", buildColorString(fmt.getForeground()));

        if (fmt.getBackground() != null)
            node.setAttribute("style:text-background-color", 
                              buildColorString(fmt.getBackground()));
    }


    /**
     *  Given a <code>Color</code>, return a string of the form
     *  <i>#rrggbb</i>.
     *
     *  @param  c  The <code>Color</code> value.
     *
     *  @return  The <code>Color</code> value in the form <i>#rrggbb</i>.
     */
    private String buildColorString(Color c) {
        int v[] = new int[3];
        v[0] = c.getRed();
        v[1] = c.getGreen();
        v[2] = c.getBlue();
        String colorString = new String("#");
        for (int i = 0; i <= 2; i++) {
            String xx = Integer.toHexString(v[i]);
            if (xx.length() < 2) 
        xx = "0" + xx;
            colorString += xx;
    }
        return colorString;
    }
         
    
    private static String[] ignored = {
        "style:text-autospace",  "style:text-underline-color",
        "fo:margin-left", "fo:margin-right", "fo:text-indent",
        "fo:margin-top", "fo:margin-bottom", "text:line-number",
        "text:number-lines", "style:country-asian",
        "style:font-size-asian", "style:font-name-complex",
        "style:language-complex", "style:country-complex",
        "style:font-size-complex", "style:punctuation-wrap",
        "fo:language", "fo:country",
        "style:font-name-asian", "style:language-asian",
        "style:line-break", "fo:keep-with-next"
    };


    /*
     * This code checks whether an attribute is one that we
     * intentionally ignore.
     *
     *  @param  attribute  The attribute to check.
     *
     *  @return  true if <code>attribute</code> can be ignored,
     *           otherwise false.
     */
    private boolean isIgnored(String attribute) {
        for (int i = 0; i < ignored.length; i++) {
            if (ignored[i].equals(attribute)) 
                return true;
        }
        return false;
    }
}

