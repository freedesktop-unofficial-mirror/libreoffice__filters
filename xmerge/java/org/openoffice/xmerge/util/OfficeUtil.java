/************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: OfficeUtil.java,v $
 *
 *  $Revision: 1.2 $
 *
 *  last change: $Author: rt $ $Date: 2005-09-09 11:41:02 $
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

import org.w3c.dom.Document;
import org.w3c.dom.Element;
import org.w3c.dom.Node;
import org.w3c.dom.Text;

import org.openoffice.xmerge.converter.xml.OfficeConstants;

import java.util.Vector;


/**
 * Class providing utility methods for OpenOffice plugins.
 *
 * @author  Mark Murnane
 * @version 1.1
 */
public class OfficeUtil implements OfficeConstants {
    
    /**
     * <p>Method to replace whitespace character within text with appropriate 
     *    OpenOffice tags.</p>
     *
     * @param   text      The text to parse for whitespace.
     *
     * @return  <code>Node</code> array containing OpenOffice XML nodes
     *          representing the text.
     */
    public static Node[] parseText(String text, Document parentDoc) {
        Vector nodeVec = new Vector();

        /* 
         * Break up the text from the text run into Open
         * Office text runs.  There may be more runs in OO because
         * runs of 2 or more spaces map to nodes.
         */
        while ((text.indexOf("  ") != -1) || (text.indexOf("\t") != 1)) {

            /*
             * Find the indices of tabs and multiple spaces, and
             * figure out which of them occurs first in the string.
             */
            int spaceIndex = text.indexOf("  ");
            int tabIndex = text.indexOf("\t");
            if ((spaceIndex == -1) && (tabIndex == -1))
                break;  // DJP This should not be necessary.  What is wrong
            // with the while() stmt up above?
            int closerIndex;  // Index of the first of these
            if (spaceIndex == -1)
                closerIndex = tabIndex;
            else if (tabIndex == -1)
                closerIndex = spaceIndex;
            else
                closerIndex = (spaceIndex > tabIndex) ? tabIndex : spaceIndex;
                
            /*
             * If there is any text prior to the first occurrence of a
             * tab or spaces, create a text node from it, then chop it
             * off the string we're working with.
             */
            if (closerIndex > 0) {
                String beginningText = text.substring(0, closerIndex);
                Text textNode = parentDoc.createTextNode(beginningText);
                nodeVec.addElement(textNode);
            }
            text = text.substring(closerIndex);

            /* 
             * Handle either tab character or space sequence by creating
             * an element for it, and then chopping out the text that
             * represented it in "text".
             */
            if (closerIndex == tabIndex) {
                Element tabNode = parentDoc.createElement(TAG_TAB_STOP);
                nodeVec.add(tabNode);
                text = text.substring(1);  // tab is always a single character
            } else {
                // Compute length of space sequence.
                int nrSpaces = 2;
                while ((nrSpaces < text.length())
                && text.substring(nrSpaces, nrSpaces + 1).equals(" "))
                    nrSpaces++;

                Element spaceNode = parentDoc.createElement(TAG_SPACE);
                spaceNode.setAttribute(ATTRIBUTE_SPACE_COUNT, 
                                       new Integer(nrSpaces).toString());
                nodeVec.add(spaceNode);
                text = text.substring(nrSpaces);
            }
        }

        /*
         * No more tabs or space sequences.  If there's any remaining
         * text create a text node for it.
         */
        if (text.length() > 0) {
            Text textNode = parentDoc.createTextNode(text);
            nodeVec.add(textNode);
        }

        // Now create and populate an array to return the nodes in.
        Node nodes[] = new Node[nodeVec.size()];
        for (int i = 0; i < nodeVec.size(); i++)
            nodes[i] = (Node)nodeVec.elementAt(i);
        return nodes;
    }
}
