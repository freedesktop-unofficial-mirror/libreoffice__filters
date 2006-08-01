/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: ConverterFactory.java,v $
 *
 *  $Revision: 1.3 $
 *
 *  last change: $Author: ihi $ $Date: 2006-08-01 13:18:27 $
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

package org.openoffice.xmerge;

import org.openoffice.xmerge.util.registry.ConverterInfo;
import org.openoffice.xmerge.util.registry.ConverterInfoMgr;

/**
 *  Factory that provides access to <code>Convert</code> objects, which
 *  are used to do a conversion.  The <code>ConvertFactory</code> does
 *  this via the <code>ConvertInfoMgr</code> which maintains a list of
 *  which <code>Convert</code> objects are available and their
 *  capabilities.
 *
 *  @see  Convert
 *  @see  org.openoffice.xmerge.util.registry.ConverterInfoMgr
 *
 *  @author  Martin Maher
 */
public class ConverterFactory {

   /**
    *  Confirms whether or not a particular conversion can be done 
    *  based on the Mime types of the files to be converted to and 
    *  from.
    *
    *  @param  mimeTypeIn   The mime input type.
    *  @param  mimeTypeOut  The mime output type.
    *
    *  @return  true if the conversion is possible, false otherwise.
    */
    public boolean canConvert(String mimeTypeIn, String mimeTypeOut) {

        ConverterInfo foundInfo = null;

        // findConverterInfo expects the second paramenter to be the
        // destination MimeType 
        if (foundInfo.isValidOfficeType(mimeTypeOut))  
            foundInfo = ConverterInfoMgr.findConverterInfo(mimeTypeIn, mimeTypeOut);
        else
            foundInfo = ConverterInfoMgr.findConverterInfo(mimeTypeOut, mimeTypeIn);

        if (foundInfo != null)
            return true;
        else 
            return false;
    }


   /**
    *  Returns the <code>Convert</code> object that converts
    *  the specified device/office mime type conversion.  If there
    *  are multiple <code>Converter</code> objects registered
    *  that support this conversion, only the first is returned.
    *
    *  @param  mimeTypeIn   The mime input type.
    *  @param  mimeTypeOut  The mime output type.
    *
    *  @return  The first <code>Convert</code> object that supports 
    *           the specified conversion. 
    */
    public Convert getConverter(String mimeTypeIn, String mimeTypeOut) {

        ConverterInfo foundInfo = null;
        boolean toOffice;
        
        toOffice = foundInfo.isValidOfficeType(mimeTypeOut);
        
        // findConverterInfo expects the second paramenter to be the
        // destination MimeType 
        if (toOffice)
            foundInfo = ConverterInfoMgr.findConverterInfo(mimeTypeIn, mimeTypeOut);
        else 
            foundInfo = ConverterInfoMgr.findConverterInfo(mimeTypeOut, mimeTypeIn);
        
        if (foundInfo != null)
            return getConverter(foundInfo, toOffice);    
        else 
            return null;
    }

    
   /**
    *  Returns the <code>Convert</code> object that is described 
    *  by the <code>ConverterInfo</code> parameter.
    *
    *  @param  ci  The <code>ConverterInfo</code> describing the converter.
    *
    *  @param  toOffice  true to convert to office, false to convert to device.
    *
    *  @return  The <code>Convert</code> object
    */
    public Convert getConverter(ConverterInfo ci, boolean toOffice) {
            
        Convert myConvert = new Convert(ci, toOffice);
        return myConvert;
    }
}

