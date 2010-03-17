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

package org.openoffice.xmerge.converter.xml.sxw.pocketword;

import org.openoffice.xmerge.converter.xml.TextStyle;

import org.openoffice.xmerge.util.EndianConverter;

import org.openoffice.xmerge.util.ColourConverter;

import java.io.ByteArrayOutputStream;
import java.io.IOException;

/**
 * This class represents a portion of text with a particular formatting style.
 * The style may differ from the default style of the paragraph of which it
 * is part.
 *
 * @author  Mark Murnane
 * @version 1.1
 */
class ParagraphTextSegment implements PocketWordConstants {
    
    private String    pText;
    private TextStyle pStyle;
    
    
    /**
     * <p>Initialise a new <code>ParagraphTextSegment</p>.
     * <p>Both parameters may be <code>null</code>.</p>
     *
     * @param   data    The text of this segment.
     * @param   style   The style describing this segment.
     */
    public ParagraphTextSegment (String data, TextStyle style) {
        pText  = data;
        pStyle = style;
    }
    
    /**
     * <p>Sets the text for this segment.</p>
     *
     * @param   data    The text of this segment.
     */
    public void setText (String data) {
        pText = data;
    }

    /**
     * <p>Gets the text for this segment.</p>
     *
     * @return    The text of this segment.
     */    
    public String getText () {
        return pText;
    }
    
    
    /**
     * <p>Sets the style for this segment.</p>
     *
     * @param   data    The style describing this segment.
     */
    public void setStyle (TextStyle style) {
        pStyle = style;
    }
    
    
    /**
     * <p>Gets the style for this segment.</p>
     *
     * @return  The style describing this segment.
     */
    public TextStyle getStyle () {
        return pStyle;
    }
    
    
    /**
     * <p>Returns the string data for this text segment wrapped with the 
     *    appropriate byte codes for the formatting settings used.</p>
     *
     * @return  <code>byte</code> array containing formatted text in Pocket Word 
     *          format.
     */
    public byte[] getData () {
        ByteArrayOutputStream data = new ByteArrayOutputStream();
        
        boolean colourSet    = false;
        boolean boldSet      = false;
        boolean italicSet    = false;
        boolean underlineSet = false;
        boolean strikeSet    = false;
        boolean highlightSet = false;
        
        // TODO: Font changes need to be worked out here

        try {
            if (pStyle != null) {
                if (pStyle.getFontColor() != null) {
                    ColourConverter cc = new ColourConverter();
                    short colourCode = cc.convertFromRGB(pStyle.getFontColor());
                    if (colourCode != 0) {	// not black 
                        data.write(COLOUR_TAG);
                        data.write(EndianConverter.writeShort(colourCode));
                        colourSet = true;
                    }
                }
                if (pStyle.isSet(TextStyle.BOLD) && pStyle.getAttribute(TextStyle.BOLD)) {
                    data.write(new byte[] { FONT_WEIGHT_TAG, FONT_WEIGHT_BOLD, 0x00 } );
                    boldSet = true;
                }   
                if (pStyle.isSet(TextStyle.ITALIC) && pStyle.getAttribute(TextStyle.ITALIC)) {
                    data.write(new byte[] { ITALIC_TAG, 0x01 } );
                    italicSet = true;
                }
                if (pStyle.isSet(TextStyle.UNDERLINE) && pStyle.getAttribute(TextStyle.UNDERLINE)) {
                    data.write(new byte[] { UNDERLINE_TAG, 0x01 } );
                    underlineSet = true;
                }
                if (pStyle.isSet(TextStyle.STRIKETHRU) && pStyle.getAttribute(TextStyle.STRIKETHRU)) {
                    data.write(new byte[] { STRIKETHROUGH_TAG, 0x01 } );
                    strikeSet = true;
                }        
                if (pStyle.getBackgroundColor() != null) {
                    data.write(new byte[] { HIGHLIGHT_TAG, 0x01 } );
                    highlightSet = true;
                }
            }
        
        
            // Now write out the data
            if (!pText.equals("\t")) {
                data.write(pText.getBytes());
            }
            else {
                /*
                 * Tabs are a special case.  They are represented by Pocket Word
                * as the LE sequence 0xC4 0x04.
                */
                data.write(new byte[] { (byte)0xC4, 0x04 } );
            }
        
        
            // Now close out any of the settings changes
            if (colourSet) {
                /*
                 * Colours may change without changing back to black, but
                 * without knowing what the previous colour was, the only
                 * way to ensure correct conversion is to restore to black and
                 * let the next segment change the colour again.
                 */
                data.write(new byte[] { COLOUR_TAG, 0x00, 0x00 } );
            }
            if (boldSet) {
                data.write(new byte[] { FONT_WEIGHT_TAG, FONT_WEIGHT_NORMAL, 0x00 } );
            }
            if (italicSet) {
                data.write(new byte[] { ITALIC_TAG, 0x00 } );
            }
            if (underlineSet) {
                data.write(new byte[] { UNDERLINE_TAG, 0x00 } );
            }
            if (strikeSet) {
                data.write(new byte[] { STRIKETHROUGH_TAG, 0x00 } );
            }
            if (highlightSet) {
                data.write(new byte[] { HIGHLIGHT_TAG, 0x00 } );
            }
        }
        catch (IOException ioe) {
            // Should never occur in a memory based stream
        }
        
        return data.toByteArray();
    }
}
