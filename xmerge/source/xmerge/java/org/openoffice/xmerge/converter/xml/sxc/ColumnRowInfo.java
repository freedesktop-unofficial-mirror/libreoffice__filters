/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: ColumnRowInfo.java,v $
 *
 *  $Revision: 1.3 $
 *
 *  last change: $Author: ihi $ $Date: 2006-08-01 13:27:36 $
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

package org.openoffice.xmerge.converter.xml.sxc;

/**
 * This is a class to define a table-column structure. This can then be
 * used by plugins to write or read their own column types.
 *
 * @author Martin Maher
 */
public class ColumnRowInfo {

    final public static int COLUMN	= 0x01;
    final public static int ROW		= 0x02;

    final private static int DEFAULTROWSIZE_MIN	= 250;
    final private static int DEFAULTROWSIZE_MAX	= 260;

    private int type;
    private int dimension	= 0;
    private int repeated	= 1;
    private boolean userDefined = true;
    private Format fmt = new Format();

    /**
     * Constructor for a <code>ColumnRowInfo</code>
     *
     * @param dimension if it's a row the height, a column the width 
     * @param repeated 
     */
    public ColumnRowInfo(int type) {

        this.type = type;
    }
    
    /**
     * Constructor for a <code>ColumnRowInfo</code>
     *
     * @param dimension if it's a row the height, a column the width 
     * @param repeated how many times it is repeated
     * @param type whether Row or column record 
     */
    public ColumnRowInfo(int dimension, int repeated, int type) {

        this.dimension = dimension;
        this.repeated = repeated;
        this.type = type;
    }

    /**
     * Constructor that includes userDefined field
     *
     * @param userDefined whether the record is manually set
     */
    public ColumnRowInfo(int dimension, int repeated, int type, boolean userDefined) {
    
        this(dimension, repeated, type);
        this.userDefined = userDefined;
    }
    
    /**
     * sets the definition 
     *
     * @param newDefinition sets the definition
     */
    public void setFormat(Format fmt) {

        this.fmt = fmt;
    }

    /**
     * returns Name of the definition 
     * 
     * @return the name which identifies the definition
     */
    public Format getFormat() {

        return fmt;
    }

    /**
     * returns Name of the definition 
     * 
     * @return the name which identifies the definition
     */
    public int getSize() {

        return dimension;
    }
    
    /**
     * sets the definition 
     *
     * @param newDefinition sets the definition
     */
    public void setSize(int dimension) {

        this.dimension = dimension;
    }
    /**
     * Returns the definition itself
     *
     * @return the definition 
     */
    public int getRepeated() {
    
        return repeated;
    }

    /**
     * Returns the base Cell address 
     * 
     * @return the base cell address
     */
    public void setRepeated(int repeated) {

        this.repeated = repeated;
    }
    
    /**
     * Returns the definition itself
     *
     * @return the definition 
     */
    public boolean isRow() {
    
        if(type==ROW)
            return true;
        else 
            return false;
    }

    /**
     * Returns the base Cell address 
     * 
     * @return the base cell address
     */
    public boolean isColumn() {

        if(type==COLUMN)
            return true;
        else 
            return false;
    }

    /**
     * Test if the row height as been set manually
     *
     * @return true if user defined otherwise false
     */
    public boolean isUserDefined() {

        return userDefined;
    }
    
    /**
     * Test if the row height is default
     *
     * @return true if default otherwise false
     */
    public boolean isDefaultSize() {

        if(	type==ROW &&
            dimension>DEFAULTROWSIZE_MIN &&
            dimension<DEFAULTROWSIZE_MAX)
            return true;
        else 
            return false;
    }		
}
