/*************************************************************************
 *
 *  $RCSfile: helper.hxx,v $
 *
 *  $Revision: 1.3 $
 *
 *  last change: $Author: hr $ $Date: 2004-08-03 14:57:07 $
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
#ifndef _SFX_HELPER_HXX
#define _SFX_HELPER_HXX

// include ---------------------------------------------------------------

#ifndef _COM_SUN_STAR_UNO_SEQUENCE_HXX_
#include <com/sun/star/uno/Sequence.hxx>
#endif
// auto strip #ifndef  _COM_SUN_STAR_UCB_NAMECLASH_HPP_
// auto strip #include <com/sun/star/ucb/NameClash.hpp>
// auto strip #endif

// auto strip #include <tools/string.hxx>
// auto strip #include <tools/errcode.hxx>
// auto strip #include <tools/bigint.hxx>
namespace binfilter {

// class SfxContentHelper ------------------------------------------------

class SfxContentHelper
{
private:
//STRIP001     static sal_Bool             Transfer_Impl( const String& rSource, const String& rDest, sal_Bool bMoveData,
//STRIP001                                                     sal_Int32 nNameClash );

public:
//STRIP001 	static sal_Bool				IsDocument( const String& rContent );
//STRIP001 	static sal_Bool				IsFolder( const String& rContent );
//STRIP001 	static sal_Bool				GetTitle( const String& rContent, String& rTitle );
//STRIP001 	static sal_Bool				Kill( const String& rContent );

//STRIP001 	static ::com::sun::star::uno::Sequence< ::rtl::OUString >
//STRIP001                                 GetFolderContents( const String& rFolder, sal_Bool bFolder, sal_Bool bSorted = sal_False );
//STRIP001 	static ::com::sun::star::uno::Sequence< ::rtl::OUString >
//STRIP001 								GetFolderContentProperties( const String& rFolder, sal_Bool bFolder );
    static ::com::sun::star::uno::Sequence< ::rtl::OUString >
                                GetResultSet( const String& rURL );
//STRIP001 	static ::com::sun::star::uno::Sequence< ::rtl::OUString >
//STRIP001 								GetHelpTreeViewContents( const String& rURL );
    static String				GetActiveHelpString( const String& rURL );
//STRIP001 	static sal_Bool				IsHelpErrorDocument( const String& rURL );

//STRIP001 	static sal_Bool				CopyTo( const String& rSource, const String& rDest );
//STRIP001     static sal_Bool             MoveTo( const String& rSource, const String& rDest, sal_Int32 nNameClash = ::com::sun::star::ucb::NameClash::ERROR );

//STRIP001 	static sal_Bool				MakeFolder( const String& rFolder );
//STRIP001 	static ErrCode				QueryDiskSpace( const String& rPath, sal_Int64& rFreeBytes );
//STRIP001 	static ULONG				GetSize( const String& rContent );
//STRIP001 	static sal_Bool				IsYounger( const String& rIsYoung, const String& rIsOlder );

    // please don't use this!
//STRIP001 	static sal_Bool				Exists( const String& rContent );
//STRIP001 	static sal_Bool				Find( const String& rFolder, const String& rName, String& rFile );
};

}//end of namespace binfilter
#endif // #ifndef _SFX_HELPER_HXX


