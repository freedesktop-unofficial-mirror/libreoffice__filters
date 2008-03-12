/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: fontoptions.hxx,v $
 *
 *  $Revision: 1.2 $
 *
 *  last change: $Author: rt $ $Date: 2008-03-12 12:02:24 $
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
#ifndef INCLUDED_SVTOOLS_FONTOPTIONS_HXX
#define INCLUDED_SVTOOLS_FONTOPTIONS_HXX

#ifndef _SAL_TYPES_H_
#include <sal/types.h>
#endif

#ifndef _OSL_MUTEX_HXX_
#include <osl/mutex.hxx>
#endif

#ifndef _RTL_USTRING_HXX_
#include <rtl/ustring.hxx>
#endif

#ifndef INCLUDED_SVTOOLS_OPTIONS_HXX
#include <bf_svtools/options.hxx>
#endif

namespace binfilter
{

//_________________________________________________________________________________________________________________
//	forward declarations
//_________________________________________________________________________________________________________________

/*-************************************************************************************************************//**
    @short			forward declaration to our private date container implementation
    @descr			We use these class as internal member to support small memory requirements.
                    You can create the container if it is neccessary. The class which use these mechanism
                    is faster and smaller then a complete implementation!
*//*-*************************************************************************************************************/

class SvtFontOptions_Impl;

//_________________________________________________________________________________________________________________
//	declarations
//_________________________________________________________________________________________________________________

/*-************************************************************************************************************//**
    @short			collect informations about font features
    @descr          -

    @implements		-
    @base			-

    @devstatus		ready to use
*//*-*************************************************************************************************************/

class  SvtFontOptions: public Options
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

         SvtFontOptions();
        virtual ~SvtFontOptions();

        //---------------------------------------------------------------------------------------------------------
        //	interface
        //---------------------------------------------------------------------------------------------------------

        /*-****************************************************************************************************//**
            @short		interface methods to get and set value of config key "org.openoffice.Office.Common/Font"
            @descr		These values defines different states of font handling.

                        ..ReplacementTable..()	=>  Determines if the list of font replacements is applied or not.

                        ..FontHistory..()		=>  The last 5 fonts will be shown and the last one will be the
                                                    first name on the list. These will be displayed in the Font name
                                                    combo box on the Object bar.

                        ..FontWYSIWYG..()		=>  With this option the names of the selectable fonts
                                                    (for example, the fonts in the Font field in the object bar)
                                                    will be formatted as the current font.

            @seealso	-

            @param		-
            @return		-

            @onerror	No error should occurre!
        *//*-*****************************************************************************************************/

        sal_Bool	IsReplacementTableEnabled	(					) const	;
        void		EnableReplacementTable		( sal_Bool bState	)		;

        sal_Bool	IsFontHistoryEnabled		(					) const	;
        void		EnableFontHistory			( sal_Bool bState	)		;

        sal_Bool	IsFontWYSIWYGEnabled		(					) const	;
        void		EnableFontWYSIWYG			( sal_Bool bState	)		;

    //-------------------------------------------------------------------------------------------------------------
    //	private methods
    //-------------------------------------------------------------------------------------------------------------

    private:

        /*-****************************************************************************************************//**
            @short		return a reference to a static mutex
            @descr		These class use his own static mutex to be threadsafe.
                        We create a static mutex only for one ime and use at different times.

            @seealso	-

            @param		-
            @return		A reference to a static mutex member.

            @onerror	-
        *//*-*****************************************************************************************************/

         static ::osl::Mutex& impl_GetOwnStaticMutex();

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

        static SvtFontOptions_Impl*			m_pDataContainer	;	/// impl. data container as dynamic pointer for smaller memory requirements!
        static sal_Int32					m_nRefCount			;	/// internal ref count mechanism

};		// class SvtFontOptions

}

#endif	// #ifndef INCLUDED_SVTOOLS_FONTOPTIONS_HXX
