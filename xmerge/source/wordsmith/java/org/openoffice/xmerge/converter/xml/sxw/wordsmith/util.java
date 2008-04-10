/*************************************************************************
 *
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER.
 * 
 * Copyright 2008 by Sun Microsystems, Inc.
 *
 * OpenOffice.org - a multi-platform office productivity suite
 *
 * $RCSfile: util.java,v $
 * $Revision: 1.4 $
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

package org.openoffice.xmerge.converter.xml.sxw.wordsmith;

/**
 *  WordSmith utility class.
 *
 *  @author   David Proulx
 */
class util {

    /**
     *  Convert 2 bytes to an integer.
     *
     *  @param  data   <code>byte</code> data to convert.
     *  @param  index  Index to convert.
     *
     *  @return  Converted integer.
     */
    static int intFrom2bytes(byte[] data, int index) {
        return (((data[index] & 0xFF) << 8)
                | (data[index+1] & 0xFF));

    }


    /**
     *  Convert 4 bytes to an integer.
     *
     *  @param  data   <code>byte</code> data to convert.
     *  @param  index  Index to convert.
     *
     *  @return  Converted integer.
     */
    static int intFrom4bytes(byte[] data, int index) {
        return (((data[index] & 0xFF) << 24)
          | ((data[index + 1] & 0xFF) << 16)
          | ((data[index + 2] & 0xFF) << 8)
                | (data[index+3] & 0xFF));

    }
}

