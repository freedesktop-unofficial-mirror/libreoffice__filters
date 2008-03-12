/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: compatibility.hxx,v $
 *
 *  $Revision: 1.2 $
 *
 *  last change: $Author: rt $ $Date: 2008-03-12 11:54:07 $
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
#ifndef INCLUDED_SVTOOLS_COMPATIBILITY_HXX
#define INCLUDED_SVTOOLS_COMPATIBILITY_HXX

#ifndef _SAL_TYPES_H_
#include <sal/types.h>
#endif

#ifndef _OSL_MUTEX_HXX_
#include <osl/mutex.hxx>
#endif

#ifndef _COM_SUN_STAR_UNO_SEQUENCE_H_
#include <com/sun/star/uno/Sequence.h>
#endif

#ifndef _COM_SUN_STAR_BEANS_PROPERTYVALUE_HPP_
#include <com/sun/star/beans/PropertyValue.hpp>
#endif

#ifndef INCLUDED_SVTOOLS_OPTIONS_HXX
#include <bf_svtools/options.hxx>
#endif

namespace binfilter {

//_________________________________________________________________________________________________________________
//	types, enums, ...
//_________________________________________________________________________________________________________________

enum CompatibilityOptions
{
    COPT_USE_PRINTERDEVICE = 0,
    COPT_ADD_SPACING,
    COPT_ADD_SPACING_AT_PAGES,
    COPT_USE_OUR_TABSTOPS,
    COPT_NO_EXTLEADING,
    COPT_USE_LINESPACING,
    COPT_ADD_TABLESPACING,
    COPT_USE_OBJECTPOSITIONING,
    COPT_USE_OUR_TEXTWRAPPING,
    COPT_CONSIDER_WRAPPINGSTYLE,
    COPT_EXPAND_WORDSPACE
};

/*-************************************************************************************************************//**
    @descr			The method GetList() returns a list of property values.
                    Use follow defines to seperate values by names.
*//*-*************************************************************************************************************/
#define COMPATIBILITY_PROPERTYNAME_NAME                     OUString( RTL_CONSTASCII_USTRINGPARAM( "Name" ) )
#define COMPATIBILITY_PROPERTYNAME_MODULE                   OUString( RTL_CONSTASCII_USTRINGPARAM( "Module" ) )
#define COMPATIBILITY_PROPERTYNAME_USEPRTMETRICS            OUString( RTL_CONSTASCII_USTRINGPARAM( "UsePrinterMetrics" ) )
#define COMPATIBILITY_PROPERTYNAME_ADDSPACING               OUString( RTL_CONSTASCII_USTRINGPARAM( "AddSpacing" ) )
#define COMPATIBILITY_PROPERTYNAME_ADDSPACINGATPAGES        OUString( RTL_CONSTASCII_USTRINGPARAM( "AddSpacingAtPages" ) )
#define COMPATIBILITY_PROPERTYNAME_USEOURTABSTOPS           OUString( RTL_CONSTASCII_USTRINGPARAM( "UseOurTabStopFormat" ) )
#define COMPATIBILITY_PROPERTYNAME_NOEXTLEADING             OUString( RTL_CONSTASCII_USTRINGPARAM( "NoExternalLeading" ) )
#define COMPATIBILITY_PROPERTYNAME_USELINESPACING           OUString( RTL_CONSTASCII_USTRINGPARAM( "UseLineSpacing" ) )
#define COMPATIBILITY_PROPERTYNAME_ADDTABLESPACING          OUString( RTL_CONSTASCII_USTRINGPARAM( "AddTableSpacing" ) )
#define COMPATIBILITY_PROPERTYNAME_USEOBJECTPOSITIONING     OUString( RTL_CONSTASCII_USTRINGPARAM( "UseObjectPositioning" ) )
#define COMPATIBILITY_PROPERTYNAME_USEOURTEXTWRAPPING       OUString( RTL_CONSTASCII_USTRINGPARAM( "UseOurTextWrapping" ) )
#define COMPATIBILITY_PROPERTYNAME_CONSIDERWRAPPINGSTYLE    OUString( RTL_CONSTASCII_USTRINGPARAM( "ConsiderWrappingStyle" ) )
#define COMPATIBILITY_PROPERTYNAME_EXPANDWORDSPACE          OUString( RTL_CONSTASCII_USTRINGPARAM( "ExpandWordSpace" ) )

#define COMPATIBILITY_DEFAULT_NAME                          OUString( RTL_CONSTASCII_USTRINGPARAM( "_default" ) )

//_________________________________________________________________________________________________________________
//	forward declarations
//_________________________________________________________________________________________________________________

/*-************************************************************************************************************//**
    @short			forward declaration to our private date container implementation
    @descr			We use these class as internal member to support small memory requirements.
                    You can create the container if it is neccessary. The class which use these mechanism
                    is faster and smaller then a complete implementation!
*//*-*************************************************************************************************************/

class SvtCompatibilityOptions_Impl;

//_________________________________________________________________________________________________________________
//	declarations
//_________________________________________________________________________________________________________________

/*-************************************************************************************************************//**
    @short          collect informations about dynamic menus
    @descr          Make it possible to configure dynamic menu structures of menus like "new" or "wizard".

    @implements		-
    @base			-

    @devstatus		ready to use
*//*-*************************************************************************************************************/

class  SvtCompatibilityOptions: public Options
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

         SvtCompatibilityOptions();
        virtual ~SvtCompatibilityOptions();

        //---------------------------------------------------------------------------------------------------------
        //	interface
        //---------------------------------------------------------------------------------------------------------

        /*-****************************************************************************************************//**
            @short		clear complete specified list
            @descr      Call this methods to clear the whole list.

            @seealso	-

            @param      -
            @return		-

            @onerror	-
        *//*-*****************************************************************************************************/

        void Clear();

        /*-****************************************************************************************************//**
            @short      return complete specified list
            @descr      Call it to get all entries of compatibility options.
                        We return a list of all nodes with its names and properties.

            @seealso	-

            @param      -
            @return     A list of compatibility options is returned.

            @onerror    We return an empty list.
        *//*-*****************************************************************************************************/

        ::com::sun::star::uno::Sequence< ::com::sun::star::uno::Sequence< ::com::sun::star::beans::PropertyValue > > GetList() const;

        /*-****************************************************************************************************//**
            @short      append a new item
            @descr

            @seealso	method Clear()

            @param      "sName"             Name
            @param      "sModule"           Module

            @return		-

            @onerror	-
        *//*-*****************************************************************************************************/

        void AppendItem( const ::rtl::OUString& sName,
                         const ::rtl::OUString& sModule,
                         bool bUsePrtMetrics,
                         bool bAddSpacing,
                         bool bAddSpacingAtPages,
                         bool bUseOurTabStops,
                         bool bNoExtLeading,
                         bool bUseLineSpacing,
                         bool bAddTableSpacing,
                         bool bUseObjectPositioning,
                         bool bUseOurTextWrapping,
                         bool bConsiderWrappingStyle,
                         bool bExpandWordSpace );

        bool		IsUsePrtDevice() const;
        bool		IsAddSpacing() const;
        bool		IsAddSpacingAtPages() const;
        bool		IsUseOurTabStops() const;
        bool		IsNoExtLeading() const;
        bool		IsUseLineSpacing() const;
        bool		IsAddTableSpacing() const;
        bool		IsUseObjectPositioning() const;
        bool		IsUseOurTextWrapping() const;
        bool        IsConsiderWrappingStyle() const;
        bool        IsExpandWordSpace() const;

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

        static SvtCompatibilityOptions_Impl*	m_pDataContainer;	/// impl. data container as dynamic pointer for smaller memory requirements!
        static sal_Int32						m_nRefCount		;	/// internal ref count mechanism

};      // class SvtCompatibilityOptions

}

#endif  // #ifndef INCLUDED_SVTOOLS_COMPATIBILITY_HXX

