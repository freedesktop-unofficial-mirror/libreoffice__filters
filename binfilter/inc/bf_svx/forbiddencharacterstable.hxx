/*************************************************************************
 *
 *  $RCSfile: forbiddencharacterstable.hxx,v $
 *
 *  $Revision: 1.2 $
 *
 *  last change: $Author: mwu $ $Date: 2003-11-06 08:27:48 $
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

#ifndef _FORBIDDENCHARACTERSTABLE_HXX
#define _FORBIDDENCHARACTERSTABLE_HXX

#ifndef _TABLE_HXX //autogen
#include <tools/table.hxx>
#endif

#include <vos/refernce.hxx>

#ifndef _COM_SUN_STAR_UNO_REFERENCE_HXX_
#include <com/sun/star/uno/Reference.hxx>
#endif

#ifndef _COM_SUN_STAR_I18N_FORBIDDENCHARACTERS_HPP_
#include <com/sun/star/i18n/ForbiddenCharacters.hpp>
#endif
namespace com {
namespace sun {
namespace star {
namespace lang {
    class XMultiServiceFactory;
}}}}
namespace binfilter {

//STRIP008 namespace com {
//STRIP008 namespace sun {
//STRIP008 namespace star {
//STRIP008 namespace lang {
//STRIP008 	class XMultiServiceFactory;
//STRIP008 }}}}

struct ForbiddenCharactersInfo
{
    ::com::sun::star::i18n::ForbiddenCharacters aForbiddenChars;
    BOOL bTemporary;
};

DECLARE_TABLE( SvxForbiddenCharactersTableImpl, ForbiddenCharactersInfo* )

class SvxForbiddenCharactersTable : public SvxForbiddenCharactersTableImpl, public vos::OReference
{
private:	
    ::com::sun::star::uno::Reference< ::com::sun::star::lang::XMultiServiceFactory > mxMSF;

public:
            SvxForbiddenCharactersTable( ::com::sun::star::uno::Reference< ::com::sun::star::lang::XMultiServiceFactory > xMSF, USHORT nISize = 4, USHORT nGrow = 4 );
            ~SvxForbiddenCharactersTable();

    const ::com::sun::star::i18n::ForbiddenCharacters* GetForbiddenCharacters( USHORT nLanuage, BOOL bGetDefault ) const;
    void 	SetForbiddenCharacters(  USHORT nLanuage , const ::com::sun::star::i18n::ForbiddenCharacters& );
    void 	ClearForbiddenCharacters( USHORT nLanuage );
};

}//end of namespace binfilter
#endif // _FORBIDDENCHARACTERSTABLE_HXX

