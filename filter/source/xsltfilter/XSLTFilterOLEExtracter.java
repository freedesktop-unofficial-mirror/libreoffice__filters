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

//Standard Java classes
import java.io.FileWriter;
import java.util.*;
import java.util.zip.Inflater;
import java.util.zip.Deflater;
import sun.misc.BASE64Decoder;
import sun.misc.BASE64Encoder;

//StarOffice Interfaces and UNO
import com.sun.star.bridge.XBridgeFactory;
import com.sun.star.bridge.XBridge;
import com.sun.star.connection.XConnector;
import com.sun.star.connection.XConnection;
import com.sun.star.container.XNameContainer;
import com.sun.star.embed.XTransactedObject;
import com.sun.star.io.XStream;
import com.sun.star.io.XSeekable;
import com.sun.star.io.XInputStream;
import com.sun.star.io.XOutputStream;
import com.sun.star.lang.XMultiServiceFactory;
import com.sun.star.lang.XComponent;
import com.sun.star.uno.XComponentContext;
import com.sun.star.uno.UnoRuntime;


/** This class is an xalan extension class. It provider 2 elements
 *  and 2 functions to used in xslt script. With this elements and functions
 *  we can convert between oledata between Wordml and OOo flat.
 *  To use it, we need a running OOo. There are two ways to get the XMultiServiceFactory.
 *  When called by OOo xslt filter, an XMultiServiceFactory will be add to the transformer
 *  by setParameter(), then we can get it using getParameter(). Another way is using an 
 *  XConnection to connect to a running OOo. We connect to a running OOo, we need know the
 *  uno url. It can be set in the xslt script. The default uno url is:
 *  "uno:socket,host=localhost,port=8100;urp;StarOffice.ServiceManager"
 *  see XSLTXalanOLEExtracter.java
 */
public class XSLTFilterOLEExtracter {
    protected XMultiServiceFactory m_xMSF;
    protected XNameContainer m_Storage;
    protected XStream m_RootStream;
    protected XConnection m_Connection;
    protected String sConnectionString;
    
    public XSLTFilterOLEExtracter ()
    {}
    public void init(String unoUrl)
    {
        sConnectionString = unoUrl;
        if (sConnectionString == "")
            sConnectionString = "uno:socket,host=localhost,port=8100;urp;StarOffice.ServiceManager";
        debugln("Init with uno url=" + unoUrl);
        if (null == m_xMSF)
        {
            try{
                m_xMSF =connectAwareGetServiceFactory();
            }catch( Exception ex )
            {
                ex.printStackTrace();
            }
        }
    }
    public void exit()
    {
        m_Storage = null;
        m_xMSF = null;
        if (null != m_Connection)
        {
            try{
                m_Connection.close();
            }catch( Exception ex )
            {
                ex.printStackTrace();
            }
        }
    }
    
    //If aName = "oledata.mso" then we load the root storage from the given base64 string
    //Otherwise we compress the stream and add it to the root storage under the name of aName
    public void insertByName(String aName,String aBase64) 
    {
        debugln("insertByName(" + aName + " : " + aBase64 + ")");
        if (aName.equals("oledata.mso") )
        {
            loadRootStorageFromBase64(aBase64);
        }
        else
        {
            ensureCreateRootStorage();
            insertSubStorage(aName,aBase64);
        }
    }
    //If aName = "oledata.mso" then we return the base64 encoded string of the root storage
    //Otherwise we return the base64 encoded string of the sub stream under the name of aName
    public String getByName(String aName) 
    {
        if (aName.equals("oledata.mso") )
        {
            try{
                //get the length and seek to 0
                XSeekable xSeek=(XSeekable)UnoRuntime.queryInterface(XSeekable.class,m_RootStream);
                int oleLength = (int)xSeek.getLength();
                xSeek.seek(0);
                xSeek = null;
                //read all bytes
                XInputStream xInput = m_RootStream.getInputStream();
                byte oledata[][]=new byte[1][oleLength];
                xInput.readBytes(oledata,oleLength);
                //return the base64 encoded string
                return new sun.misc.BASE64Encoder().encodeBuffer(oledata[0]);
            }catch( Exception ex )
            {
                ex.printStackTrace();
            }
        }
        else
        {
            return getEncodedSubStorage(aName);
        }
        return "";
    }
    //get the sub stream which name = aName, decompress it and return the base64 encoded string
    public String getEncodedSubStorage(String aName) 
    {
        debugln("getByName(" + aName + ")");
        try{
            if (!m_Storage.hasByName(aName))
            {
                return "Not Found:" + aName;
            }
            Object oSubStream=m_Storage.getByName(aName);
            if ( oSubStream == null )
            {
                return "Not Found:" + aName;
            }
            XInputStream xSubStream = (XInputStream)UnoRuntime.queryInterface( XInputStream.class,
                                                                                oSubStream );
            if ( xSubStream == null )
            {
                return "Not Found:" + aName;
            }
            //The first four byte are the length of the uncompressed data
            byte pLength[][] = new byte[1][4];
            XSeekable xSeek=(XSeekable)UnoRuntime.queryInterface(XSeekable.class,xSubStream);
            xSeek.seek(0);
            xSeek = null;
            //Get the uncompressed length
            int readbytes = xSubStream.readBytes(pLength,4);
            if (4 != readbytes)
            {
                System.out.println("readbytes:" + readbytes);
                return "Can not read the length.";
            }
            int oleLength = (pLength[0][0] << 0)
                            + (pLength[0][1] << 8 )
                            + (pLength[0][2] << 16 )
                            + (pLength[0][3] << 24 );
            byte pContents[][] = new byte[1][oleLength];
            //Read all bytes. The compressed length should less then the uncompressed length
            readbytes = xSubStream.readBytes(pContents,oleLength);
            if (oleLength < readbytes)
            {
                return "oleLength :" + oleLength + " readbytes: " + readbytes;
            }
        
            // Decompress the bytes
            Inflater decompresser = new Inflater();
            decompresser.setInput(pContents[0], 0, readbytes);
            byte[] result = new byte[oleLength];
            int resultLength = decompresser.inflate(result);
            decompresser.end();
            
            //return the base64 string of the uncompressed data            
            return new sun.misc.BASE64Encoder().encodeBuffer(result);
        }catch( Exception ex )
        {
            ex.printStackTrace();
        }
        return "";
    }
    public XStream CreateTempFileStream( XMultiServiceFactory xMSF )
    {
        // try to get temporary file representation
        XStream xTempFileStream = null;
        try
        {
            Object oTempFile = xMSF.createInstance( "com.sun.star.io.TempFile" );
            xTempFileStream = (XStream)UnoRuntime.queryInterface( XStream.class, oTempFile );
        }
        catch( Exception e )
        {}

        if ( xTempFileStream == null )
            System.out.println( "Can't create temporary file!" );

        return xTempFileStream;
    }
    //decode the base64 string and create an com.sun.star.embed.OLESimpleStorage from it
    public void loadRootStorageFromBase64( String aBase64 )
    {
        try
        {
            //Decode and write the data to an temp stream
            byte[] oledata = new sun.misc.BASE64Decoder().decodeBuffer(aBase64);
            m_RootStream = CreateTempFileStream( m_xMSF );
            XOutputStream xOutput = m_RootStream.getOutputStream();
            xOutput.writeBytes(oledata);
            xOutput.flush();
            //Get the input stream and seek to begin
            XInputStream xInput = m_RootStream.getInputStream();
            XSeekable xSeek=(XSeekable)UnoRuntime.queryInterface(XSeekable.class,xInput);
            xSeek.seek(0);
            oledata = null;
            xSeek = null;
            
            //create an com.sun.star.embed.OLESimpleStorage from the temp stream
            Object pArgs[] = new Object[1];
            pArgs[0] = (Object) xInput;
            Object oTempStorage = m_xMSF.createInstanceWithArguments("com.sun.star.embed.OLESimpleStorage",pArgs);
            pArgs = null;
                
            m_Storage = (XNameContainer) UnoRuntime.queryInterface( XNameContainer.class, oTempStorage );
        }catch( Exception e )
        {
              e.printStackTrace();
        }
    }
    
    //Create a empty OLESimpleStorage if there is not one
    public void ensureCreateRootStorage()
    {
        if (null == m_RootStream || null == m_Storage)
        {
            try
            {
                m_RootStream = CreateTempFileStream( m_xMSF );
    
                Object pArgs[] = new Object[1];
                pArgs[0] = (Object) m_RootStream;
                Object oTempStorage = m_xMSF.createInstanceWithArguments("com.sun.star.embed.OLESimpleStorage",pArgs);
                pArgs = null;
                    
                m_Storage = (XNameContainer) UnoRuntime.queryInterface( XNameContainer.class, oTempStorage );
            }catch( Exception e )
            {
                  e.printStackTrace();
            }
        }
    }
    //decode the base64 string and insert the length and the compressed data of it to 
    //the root storage as a sub stream under aName
    public void insertSubStorage(String aName, String aBase64 )
    {
        try
        {
            //decode the base64 string
            byte[] oledata = new sun.misc.BASE64Decoder().decodeBuffer(aBase64);
            //create a temp stream to write data to
            XStream subStream = CreateTempFileStream( m_xMSF );
            XInputStream xInput = subStream.getInputStream();
            XOutputStream xOutput = subStream.getOutputStream();
            //write the length to the temp stream
            byte oleHead[]=new byte[4];
            oleHead[0] = (byte)((oledata.length >>> 0) & 0xFF);
            oleHead[1] = (byte)((oledata.length >>> 8) & 0xFF);
            oleHead[2] = (byte)((oledata.length >>> 16) & 0xFF);
            oleHead[3] = (byte)((oledata.length >>> 24) & 0xFF);
            xOutput.writeBytes(oleHead);
            
            // Compress the bytes
            byte[] output = new byte[oledata.length];
            Deflater compresser = new Deflater();
            compresser.setInput(oledata);
            compresser.finish();
            int compressedDataLength = compresser.deflate(output);
            //realloc the data length
            byte[] compressedBytes=new byte[compressedDataLength];
            for(int i=0;i<compressedDataLength;i++)
                compressedBytes[i] = output[i];
            
            //write the compressed data to the temp stream
            xOutput.writeBytes(compressedBytes);
            //seek to 0
            XSeekable xSeek=(XSeekable)UnoRuntime.queryInterface(XSeekable.class,xInput);
            xSeek.seek(0);
            xSeek = null;
            oledata = null;

            //insert the temp stream as a sub stream and use an XTransactedObject to commit it immediately
            XTransactedObject xTransact = (XTransactedObject) UnoRuntime.queryInterface( XTransactedObject.class, m_Storage );
            m_Storage.insertByName(aName,xInput);
            xTransact.commit();
            xTransact = null;
            
        }catch(java.io.IOException ex)
        {
              ex.printStackTrace();
        }
        catch( Exception e )
        {
              e.printStackTrace();
        }
    }
    /** separtates the uno-url into 3 different parts.
     */
    protected static String[] parseUnoUrl(  String url )
    {
        String [] aRet = new String [3];

        if( ! url.startsWith( "uno:" ) )
        {
            return null;
        }

        int semicolon = url.indexOf( ';' );
        if( semicolon == -1 )
            return null;
        
        aRet[0] = url.substring( 4 , semicolon );
        int nextSemicolon = url.indexOf( ';' , semicolon+1);

        if( semicolon == -1 )
            return null;
        aRet[1] = url.substring( semicolon+1, nextSemicolon );

        aRet[2] = url.substring( nextSemicolon+1);
        return aRet;
    }
    //connect to running OOo and keep an XConnection object so that we can disconnect from OOo as we wish
    protected XMultiServiceFactory connectAwareGetServiceFactory()throws com.sun.star.uno.Exception,
                                                                    com.sun.star.uno.RuntimeException,
                                                                    Exception
    {
        
        // Get component context
        XComponentContext xComponentContext =
            com.sun.star.comp.helper.Bootstrap.createInitialComponentContext( null );

       // instantiate connector service
       Object x = xComponentContext.getServiceManager().createInstanceWithContext(
                "com.sun.star.connection.Connector", xComponentContext );
            
       XConnector xConnector = (XConnector )
                UnoRuntime.queryInterface(XConnector.class, x);

       String a[] = parseUnoUrl( sConnectionString );
       if( null == a )
       {
            throw new com.sun.star.uno.Exception( "Couldn't parse uno-url "+ sConnectionString );
       }

       // connect using the connection string part of the uno-url only.
       m_Connection = xConnector.connect( a[0] );
        
       x = xComponentContext.getServiceManager().createInstanceWithContext(
                "com.sun.star.bridge.BridgeFactory", xComponentContext );

       XBridgeFactory xBridgeFactory = (XBridgeFactory) UnoRuntime.queryInterface(
                XBridgeFactory.class , x );

       // create a nameless bridge with no instance provider
       // using the middle part of the uno-url
       XBridge bridge = xBridgeFactory.createBridge( "" , a[1] , m_Connection , null );

       // query for the XComponent interface and add this as event listener
       XComponent xComponent = (XComponent) UnoRuntime.queryInterface(
                XComponent.class, bridge );

       // get the remote instance 
       x = bridge.getInstance( a[2] );

       // Did the remote server export this object ?
       if( null == x )
       {
           throw new com.sun.star.uno.Exception(
               "Server didn't provide an instance for" + a[2], null );
       }
      
       XMultiServiceFactory xFac = (XMultiServiceFactory)UnoRuntime.queryInterface( XMultiServiceFactory.class, x );
       return xFac;
    }

    protected static boolean DEBUG = false;
    protected static boolean DEBUGCHK = false;
    protected static String debugfile;        
    protected static void debugln(String s)
    {
        debug(s + "\n");
    }
    protected static void debug(String s)
    {
        if (!DEBUGCHK) {
            if (System.getProperty("xsltfilter.debug")==null){
                DEBUGCHK=true;
                return;
            } else {                
                debugfile = System.getProperty("xsltfilter.debug");
                DEBUG=true;
            }
        }
        if (!DEBUG) return;
        try {
            FileWriter dbgwriter = new FileWriter(debugfile, true);
            dbgwriter.write(s);
            dbgwriter.close();
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}
