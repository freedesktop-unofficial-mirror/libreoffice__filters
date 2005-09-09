/************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: Style.java,v $
 *
 *  $Revision: 1.2 $
 *
 *  last change: $Author: rt $ $Date: 2005-09-09 10:44:24 $
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

package org.openoffice.xmerge.converter.xml;

import org.w3c.dom.NodeList;
import org.w3c.dom.Node;
import org.w3c.dom.NamedNodeMap;
import org.w3c.dom.Element;

import org.openoffice.xmerge.Document;
import org.openoffice.xmerge.ConverterCapabilities;
import org.openoffice.xmerge.converter.xml.OfficeDocument;
import java.io.IOException;
import org.openoffice.xmerge.converter.xml.sxw.SxwDocument;

/**
 *  An object of class <code>Style</code> represents a <i>style</i>
 *  in an OpenOffice document.  In practice subclasses of this
 *  <code>Style</code>, such as <code>TextStyle</code>,
 *  <code>ParaStyle</code> are used.
 *
 *  @author   David Proulx
 *  @see <a href="TextStyle.html">TextStyle</a>, 
 *  <a href="ParaStyle.html">ParaStyle</a>
 */
public class Style {
    
    /**  Name of the <code>Style</code>. */
    protected String name = null;
    /**  Family of the <code>Style</code>. */
    protected String family = null;
    /**  Parent of the <code>Style</code>. */
    protected String parent = null;

    /** 
     *  A reference to the <code>StyleCatalog</code> to be used for
     *  looking up ancestor <code>Style</code> objects.
     */
    protected StyleCatalog sc;
    

    /**
     *  Constructor for use when going from DOM to client device format.
     *
     *  @param  node  A <i>style:style</i> or <i>style:default-style</i> 
     *                <code>Node</code> from the document being parsed.
     *                No checking of <code>Node</code> is done, so if it
     *                is not of the proper type the results will be
     *                unpredictable.
     *  @param  sc    The <code>StyleCatalog</code>, which is used for 
     *                looking up ancestor <code>Style</code> objects.
     */
    public Style(Node node, StyleCatalog sc) {

        this.sc = sc;

        // Run through the attributes of this node, saving
        // the ones we're interested in.
        if (node.getNodeName().equals("style:default-style"))
            name = "DEFAULT_STYLE";
        NamedNodeMap attrNodes = node.getAttributes();
        if (attrNodes != null) {
            int len = attrNodes.getLength();
            for (int i = 0; i < len; i++) {
                Node attr = attrNodes.item(i);
                if (attr.getNodeName().equals("style:family"))
                    family = attr.getNodeValue();
                else if (attr.getNodeName().equals("style:name")) {
                    name = attr.getNodeValue();
                } else if (attr.getNodeName().equals("style:parent-style-name"))
                    parent = attr.getNodeValue();
                
            }
        }
    }

    
    /**
     *  Constructor for use when going from client device format to DOM.
     *
     *  @param  name    Name of the <code>Style</code>.  Can be null.
     *  @param  family  Family of the <code>Style</code> - usually
     *                  <i>paragraph</i>, <i>text</i>, etc.  Can be null.
     *  @param  parent  Name of the parent <code>Style</code>, or null if none.
     *  @param  sc      The <code>StyleCatalog</code>, which is used for 
     *                  looking up ancestor <code>Style</code> objects.
     */
    public Style(String name, String family, String parent, StyleCatalog sc) {
        this.sc = sc;
        this.name = name;
        this.family = family;
        this.parent = parent;
    }
    

    /**
     *  Set the <code>StyleCatalog</code> to be used when looking up the
     *  <code>Style</code> parent.
     *
     *  @param  sc  The <code>StyleCatalog</code>, which is used for 
     *              looking up ancestor <code>Style</code> objects.
     */
    public void setCatalog(StyleCatalog sc) {
        this.sc = sc;
    }
    

    /**
     *  Returns the name of this <code>Style</code>.
     *
     *  @return  The name of this <code>Style</code>.
     */
    public String getName() {
        return name;
    }

    
    /** 
     *  Sets the name of this <code>Style</code>.
     *
     *  @param  newName  The new name of this <code>Style</code>.
     */
    public void setName(String newName) {
        name = newName;
    }

    
    /**
     *  Return the family of this <code>Style</code>.
     *
     *  @return  The family of this <code>Style</code>.
     */
    public String getFamily() {
        return family;
    }
    
    /**
     *  Return the name of the parent of this <code>Style</code>.
     *
     *  @return  The parent of this <code>Style</code>.
     */
    public String getParent() {
        return parent;
    }
    
    
    /**
     *  Return a <code>Style</code> object corresponding to this one, but with
     *  all of the inherited information from parent <code>Style</code>
     *  objects filled in.  The object returned will be a new object, not a
     *  reference to this object, even if it does not need any information
     *  added.
     *
     *  @return  A resolved <code>Style</code> object in which to look up
     *           ancestors.
     */
    public Style getResolved() {
        return new Style(name, family, parent, sc);
    }

        
    /**
     *  Write a <code>Node</code> in <code>parentDoc</code>
     *  representing this <code>Style</code>.  Note that the
     *  <code>Node</code> is returned unconnected.
     *
     *  @param  parentDoc  Document to which new <code>Node</code> will
     *                     belong.
     *  @param  name       Name to use for new <code>Node</code>.
     */
    public Node createNode(org.w3c.dom.Document parentDoc, String name) {
        // DJP: write this!  Should call writeAttributes()
        return null;
    }
    
    
    /**
     *  Write this <code>Style</code> object's attributes to the given
     *  <code>Node</code>.  This may involve writing child
     *  <code>Node</code> objects as well.  This is similar to the
     *  <code>writeNode</code> method, but the <code>Node</code>
     *  already exists, and this does  <b>not</b> write the name,
     *  family, and parent attributes, which are assumed to already
     *  exist in the <code>Node</code>.
     *
     *  @param  node  The <code>Node</code> to add style attributes.
     */
    public void writeAttributes(Node node) {
    }
    

    /**
     *  Return true if <code>Style</code> is a subset of this one.  Note
     *  that this will return true even if <code>Style</code> is less
     *  specific than this <code>Style</code>, so long as it does not
     *  contradict this <code>Style</code> in any way.
     *
     *  This always returns true since only subclasses of
     *  <code>Style</code> contain any actual <code>Style</code>
     *  information.
     *
     *  @param  style  The <code>Style</code> to check
     *
     *  @return  true if the <code>Style</code> is a subset, false otherwise.
     */
    public boolean isSubset(Style style) {
        return true;
    }
}

