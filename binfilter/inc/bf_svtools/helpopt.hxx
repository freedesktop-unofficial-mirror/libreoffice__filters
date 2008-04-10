/*************************************************************************
 *
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER.
 * 
 * Copyright 2008 by Sun Microsystems, Inc.
 *
 * OpenOffice.org - a multi-platform office productivity suite
 *
 * $RCSfile: helpopt.hxx,v $
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
#ifndef INCLUDED_SVTOOLS_HELPOPT_HXX
#define INCLUDED_SVTOOLS_HELPOPT_HXX

#ifndef INCLUDED_SVTDLLAPI_H
#include "bf_svtools/svtdllapi.h"
#endif

#ifndef INCLUDED_LIST
#include <list>
#define INCLUDED_LIST
#endif

#ifndef _STRING_HXX
#include <tools/string.hxx>
#endif

#ifndef INCLUDED_SVTOOLS_OPTIONS_HXX
#include <bf_svtools/options.hxx>
#endif

namespace binfilter
{

typedef std::list< sal_Int32 > IdList;

class SvtHelpOptions_Impl;

class  SvtHelpOptions: public Options
{
    SvtHelpOptions_Impl*    pImp;

public:
                    SvtHelpOptions();
                    virtual ~SvtHelpOptions();

    void            SetExtendedHelp( sal_Bool b );
    sal_Bool        IsExtendedHelp() const;
    void            SetHelpTips( sal_Bool b );
    sal_Bool        IsHelpTips() const;

    void            SetHelpAgentAutoStartMode( sal_Bool b );
    sal_Bool        IsHelpAgentAutoStartMode() const;
    void			SetHelpAgentTimeoutPeriod( sal_Int32 _nSeconds );
    sal_Int32		GetHelpAgentTimeoutPeriod( ) const;
    void			SetHelpAgentRetryLimit( sal_Int32 _nTrials );
    sal_Int32		GetHelpAgentRetryLimit( ) const;

    const String&   GetHelpStyleSheet()const;
    void            SetHelpStyleSheet(const String& rStyleSheet);

    /** retrieves the help agent's ignore counter for the given URL.
        <p>	If the counter returned 0, the agent should silently drop any requests for this URL.<br/>
            If the counter is greater 0, the agent should display the URL and, if the user ignores it,
            decrement the counter by 1.
        </p>
    */
    sal_Int32		getAgentIgnoreURLCounter( const ::rtl::OUString& _rURL );
    /** decrements the help agent's ignore counter for the given URL
        @see getAgentIgnoreURLCounter
    */
    void			decAgentIgnoreURLCounter( const ::rtl::OUString& _rURL );
    /** resets the help agent's ignore counter for the given URL
    */
    void			resetAgentIgnoreURLCounter( const ::rtl::OUString& _rURL );
    /** resets the help agent's ignore counter for all URL's
    */
    void			resetAgentIgnoreURLCounter();

    void            SetWelcomeScreen( sal_Bool b );
    sal_Bool        IsWelcomeScreen() const;

    IdList*         GetPIStarterList();
    void            AddToPIStarterList( sal_Int32 nId );
    void            RemoveFromPIStarterList( sal_Int32 nId );

    String			GetLocale() const;
    String			GetSystem() const;
};

}

#endif

