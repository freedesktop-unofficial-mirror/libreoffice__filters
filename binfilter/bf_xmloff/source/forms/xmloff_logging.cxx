/*************************************************************************
 *
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER.
 * 
 * Copyright 2008 by Sun Microsystems, Inc.
 *
 * OpenOffice.org - a multi-platform office productivity suite
 *
 * $RCSfile: xmloff_logging.cxx,v $
 * $Revision: 1.3 $
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

#ifndef XMLOFF_FORMS_LOGGING_HXX
#include "logging.hxx"
#endif
#ifndef _RTL_LOGFILE_HXX_ 
#include <rtl/logfile.hxx>
#endif
namespace binfilter {

//.........................................................................
namespace xmloff
{
//.........................................................................

#ifdef TIMELOG
    //=====================================================================
    //= OStackedLogging
    //=====================================================================
    //---------------------------------------------------------------------
    void OStackedLogging::enterContext( const sal_Char* _pContextName )
    {
        m_aLogger.push( new ::rtl::Logfile( _pContextName ) );
    }

    //---------------------------------------------------------------------
    void OStackedLogging::leaveTopContext( )
    {
        delete m_aLogger.top();
        m_aLogger.pop();
    }
#endif

//.........................................................................
}	// namespace xmloff
//.........................................................................


}//end of namespace binfilter
