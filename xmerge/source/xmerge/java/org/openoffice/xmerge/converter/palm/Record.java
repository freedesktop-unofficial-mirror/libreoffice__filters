/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: Record.java,v $
 *
 *  $Revision: 1.3 $
 *
 *  last change: $Author: ihi $ $Date: 2006-08-01 13:23:28 $
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

package org.openoffice.xmerge.converter.palm;

import java.io.OutputStream;
import java.io.InputStream;
import java.io.DataOutputStream;
import java.io.DataInputStream;
import java.io.IOException;

/**
 *  <p>Contains the raw bytes for a <code>Record</code> in a PDB.</p>
 *
 *  <p>Note that it is not associated with a <code>Record</code> number
 *  or ID.</p>
 *
 *  @author  Akhil Arora, Herbie Ong
 *  @see     PalmDocument
 *  @see     PalmDB
 */
public final class Record {

    /**  <code>Record</code> <code>byte</code> array. */
    private byte[] data;

    /**  <code>Record</code> attributes. */
    private byte attributes = 0;


    /**
     *  Default constructor.
     */
    public Record() {

        data = new byte[0];
    }


    /**
     *  <p>Constructor to create a <code>Record</code> filled with
     *  bytes.</p>
     *
     *  <p>Note that this does not check for 64k <code>Record</code>
     *  sizes.  User of this class must check for that.</p>
     *
     *  @param  d  <code>byte</code> array contents for this object.
     */
    public Record(byte[] d) {

        this(d, (byte) 0);
    }


    /**
     *  <p>Constructor to create a <code>Record</code> filled with
     *  bytes and assign <code>Record</code> attributes.</p>
     *
     *  <p>Note that this does not check for 64k <code>Record</code>
     *  sizes.  User of this class must check for that.</p>
     *
     *  @param  d      <code>byte</code> array contents for this object.
     *  @param  attrs  <code>Record</code> attributes.
     */
    public Record(byte[] d, byte attrs) {

        data = new byte[d.length];
        attributes = attrs;
        System.arraycopy(d, 0, data, 0, d.length);
    }


    /**
     *  This method returns the number of bytes in this object.
     *
     *  @return  Number of bytes in this object.
     */
    public int getSize() {

        return data.length;
    }


    /**
     *  This method returns the contents of this <code>Object</code>.
     *
     *  @return  Contents in <code>byte</code> array
     */
    public byte[] getBytes() {

        return data;
    }


    /**
     *  <p>This method returns the <code>Record</code> attributes.</p>
     *
     *  <blockquote><pre>
     *  <code>Record</code> attributes consists of (from high to low bit)
     *
     *  delete (1) - dirty (1) - busy (1) - secret (1) - category (4)
     *  </pre></blockquote>
     *
     *  @return   <code>Record</code> attribute.
     */
    public byte getAttributes() {

        return attributes;
    }


    /**
     *  Write out the <code>Record</code> attributes and
     *  <code>Record</code> length followed by the data in this
     *  <code>Record</code> object.
     *
     *  @param  out  The <code>OutputStream</code> to write the object.
     *
     *  @throws  IOException  If any I/O error occurs.
     */
    public void write(OutputStream outs) throws IOException {

        DataOutputStream out = new DataOutputStream(outs);
        out.writeByte(attributes);
        out.writeShort(data.length);
        out.write(data);
    }


    /**
     *  Read the necessary data to create a PDB from
     *  the <code>InputStream</code>.
     *
     *  @param  in  The <code>InputStream</code> to read data from
     *              in order to restore the <code>object</code>.
     *
     *  @throws  IOException  If any I/O error occurs.
     */
    public void read(InputStream ins) throws IOException {

        DataInputStream in = new DataInputStream(ins);
        attributes = in.readByte();
        int len = in.readUnsignedShort();
        data = new byte[len];
        in.readFully(data);
    }


    /**
     *  <p>Override equals method of <code>Object</code>.</p>
     *
     *  <p>Two <code>Record</code> objects are equal if they contain
     *  the same bytes in the array and the same attributes.</p>
     *
     *  <p>This is used primarily for testing purposes only for now.</p>
     *
     *  @param  obj  A <code>Record</code> object to compare with
     *
     *  @return  true if obj is equal, otherwise false.
     */
    public boolean equals(Object obj) {

        boolean bool = false;

        if (obj instanceof Record) {

            Record rec = (Record) obj;

            checkLabel: {

                if (rec.getAttributes() != attributes) {

                    break checkLabel;
                }

                if (rec.getSize() == data.length) {

                    for (int i = 0; i < data.length; i++) {

                        if (data[i] != rec.data[i]) {
                            break checkLabel;
                        }
                    }

                    bool = true;
                }
            }
        }
        return bool;
    }
}

