/*************************************************************************
 *
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER.
 * 
 * Copyright 2008 by Sun Microsystems, Inc.
 *
 * OpenOffice.org - a multi-platform office productivity suite
 *
 * $RCSfile: menuoptions.hxx,v $
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
#ifndef INCLUDED_SVTOOLS_MENUOPTIONS_HXX
#define INCLUDED_SVTOOLS_MENUOPTIONS_HXX

//_________________________________________________________________________________________________________________
//	includes
//_________________________________________________________________________________________________________________

#ifndef _SAL_TYPES_H_
#include <sal/types.h>
#endif

#ifndef _OSL_MUTEX_HXX_
#include <osl/mutex.hxx>
#endif

#ifndef INCLUDED_SVTOOLS_OPTIONS_HXX
#include <bf_svtools/options.hxx>
#endif

//_________________________________________________________________________________________________________________
//	forward declarations
//_________________________________________________________________________________________________________________

/*-************************************************************************************************************//**
    @short			forward declaration to our private date container implementation
    @descr			We use these class as internal member to support small memory requirements.
                    You can create the container if it is neccessary. The class which use these mechanism
                    is faster and smaller then a complete implementation!
*//*-*************************************************************************************************************/

class Link;

namespace binfilter
{
class SvtMenuOptions_Impl;

//_________________________________________________________________________________________________________________
//	declarations
//_________________________________________________________________________________________________________________

/*-************************************************************************************************************//**
    @short			collect informations about menu features
    @descr          -

    @implements		-
    @base			-

    @devstatus		ready to use
*//*-*************************************************************************************************************/

class  SvtMenuOptions: public Options
{
    //-------------------------------------------------------------------------------------------------------------
    //	public methods
    //-------------------------------------------------------------------------------------------------------------

    public:

        //---------------------------------------------------------------------------------------------------------
        //	constructor / destructor
        //---------------------------------------------------------------------------------------------------------

        /*-****************************************************************************************************//**
            @short		standard constructor and destructor
            @descr		This will initialize an instance with default values.
                        We implement these class with a refcount mechanism! Every instance of this class increase it
                        at create and decrease it at delete time - but all instances use the same data container!
                        He is implemented as a static member ...

            @seealso	member m_nRefCount
            @seealso	member m_pDataContainer

            @param		-
            @return		-

            @onerror	-
        *//*-*****************************************************************************************************/

         SvtMenuOptions();
        virtual ~SvtMenuOptions();

        void AddListener( const Link& rLink );
        void RemoveListener( const Link& rLink );
        //---------------------------------------------------------------------------------------------------------
        //	interface
        //---------------------------------------------------------------------------------------------------------

        /*-****************************************************************************************************//**
            @short		interface methods to get and set value of config key "org.openoffice.Office.Common/View/Menu/..."
            @descr      These options describe internal states to enable/disable features of installed office.

                        IsEntryHidingEnabled()
                        SetEntryHidingState()	=>	Activate this field for viewing all deactivated menu entries.
                                                    Menu commands that are normally not necessary are hidden by default.
                                                    Default=false

                        IsFollowMouseEnabled()
                        SetFollowMouseState() 	=>  Automatic selection while moving the mouse on a menu.
                                                    Default=true

            @seealso	configuration package "org.openoffice.Office.Common/View/Menu"
        *//*-*****************************************************************************************************/

        sal_Bool IsEntryHidingEnabled() const;
        sal_Bool IsFollowMouseEnabled() const;
        sal_Bool IsMenuIconsEnabled() const;

        void SetEntryHidingState( sal_Bool bState );
        void SetFollowMouseState( sal_Bool bState );
        void SetMenuIconsState( sal_Bool bState );

    //-------------------------------------------------------------------------------------------------------------
    //	private methods
    //-------------------------------------------------------------------------------------------------------------

    private:

        /*-****************************************************************************************************//**
            @short		return a reference to a static mutex
            @descr		These class is partially threadsafe (for de-/initialization only).
                        All access methods are'nt safe!
                        We create a static mutex only for one ime and use at different times.

            @seealso	-

            @param		-
            @return		A reference to a static mutex member.

            @onerror	-
        *//*-*****************************************************************************************************/

         static ::osl::Mutex& GetOwnStaticMutex();

    //-------------------------------------------------------------------------------------------------------------
    //	private member
    //-------------------------------------------------------------------------------------------------------------

    private:

        /*Attention

            Don't initialize these static member in these header!
            a) Double dfined symbols will be detected ...
            b) and unresolved externals exist at linking time.
            Do it in your source only.
         */

        static SvtMenuOptions_Impl*	m_pDataContainer	;	/// impl. data container as dynamic pointer for smaller memory requirements!
        static sal_Int32			m_nRefCount			;	/// internal ref count mechanism

};		// class SvtMenuOptions

}

#endif	// #ifndef INCLUDED_SVTOOLS_MENUOPTIONS_HXX
