/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: FCFGMerge.java,v $
 *
 *  $Revision: 1.4 $
 *
 *  last change: $Author: rt $ $Date: 2005-09-08 21:35:23 $
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

package com.sun.star.filter.config.tools.merge;

//_______________________________________________

import java.lang.*;
import java.util.*;
import java.io.*;
import com.sun.star.filter.config.tools.utils.*;

//_______________________________________________

/**
 *  Its a simple command line tool, which can merge different XML fragments
 *  together. Such fragments must exist as files on disk, will be moved into
 *  one file together on disk.
 *
 *
 */
public class FCFGMerge
{
    //___________________________________________
    // const

    private static final java.lang.String CFGFILE = "com/sun/star/filter/config/tools/merge/FCFGMerge.cfg";
    private static final java.lang.String PROP_LOGLEVEL = "loglevel";

    //___________________________________________
    // main

    public static void main(java.lang.String[] sCmdLine)
    {
        FCFGMerge.printCopyright();

        // create log object in default mode "WARNINGS"
        // If a command line parameter indicates another
        // level - change it!
        Logger aLog = new Logger();

        try
        {
            // merge config file and overwrite properties
            // via command line
            ConfigHelper aCfg = null;
            aCfg = new ConfigHelper(CFGFILE, sCmdLine);

            // update log level
            int nLogLevel = aCfg.getInt(PROP_LOGLEVEL, Logger.LEVEL_WARNINGS);
            aLog = new Logger(nLogLevel);

            // help requested?
            if (aCfg.isHelp())
            {
                FCFGMerge.printHelp();
                System.exit(-1);
            }

            // create new merge object and start operation
            Merger aMerger = new Merger(aCfg, aLog);
            aMerger.merge();
        }
        catch(java.lang.Throwable ex)
        {
            aLog.setException(ex);
            System.exit(-1);
        }

        System.exit(0);
    }

    //___________________________________________

    /** prints out a copyright message on stdout.
     */
    private static void printCopyright()
    {
        java.lang.StringBuffer sOut = new java.lang.StringBuffer(256);
        sOut.append("FCFGMerge\n");
        sOut.append("Copyright: 2003 by Sun Microsystems, Inc.\n");
        sOut.append("All Rights Reserved.\n");
        System.out.println(sOut.toString());
    }

    //___________________________________________

    /** prints out a help message on stdout.
     */
    private static void printHelp()
    {
        java.lang.StringBuffer sOut = new java.lang.StringBuffer(256);
        sOut.append("____________________________________________________________\n");
        sOut.append("usage: FCFGMerge cfg=<file name>\n"                            );
        sOut.append("parameters:\n"                                                 );
        sOut.append("\tcfg=<file name>\n"                                           );
        sOut.append("\t\tmust point to a system file, which contains\n"             );
        sOut.append("\t\tall neccessary configuration data for the merge process.\n");
        sOut.append("\n\tFurther cou can specify every parameter allowed in the\n"  );
        sOut.append("\n\tconfig file as command line parameter too, to overwrite\n" );
        sOut.append("\n\tthe value from the file.\n"                                );
        System.out.println(sOut.toString());
    }
}
