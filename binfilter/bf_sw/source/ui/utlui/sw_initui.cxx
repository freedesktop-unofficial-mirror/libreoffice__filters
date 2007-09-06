/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: sw_initui.cxx,v $
 *
 *  $Revision: 1.9 $
 *
 *  last change: $Author: kz $ $Date: 2007-09-06 13:13:47 $
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


#ifdef _MSC_VER
#pragma hdrstop
#endif

#ifndef _VIEWSH_HXX
#include <viewsh.hxx>
#endif
#ifndef _EDTWIN_HXX
#include <edtwin.hxx>
#endif
#ifndef _SHELLRES_HXX
#include <shellres.hxx>
#endif

#ifndef _UTLUI_HRC
#include <utlui.hrc>
#endif
#ifndef _INITUI_HRC
#include <initui.hrc>
#endif
#ifndef _COMCORE_HRC
#include <comcore.hrc>
#endif
#ifndef _AUTHFLD_HXX
#include <authfld.hxx>
#endif
#ifndef _DBMGR_HXX
#include <dbmgr.hxx>
#endif
#ifndef _SWTYPES_HXX
#include "swtypes.hxx"
#endif
namespace binfilter {

#define C2S(cChar) UniString::CreateFromAscii(cChar)
/*--------------------------------------------------------------------
    Beschreibung:	globale Pointer
 --------------------------------------------------------------------*/

String* pOldGrfCat = 0;
String* pOldTabCat = 0;
String* pOldFrmCat = 0;
String* pOldDrwCat = 0;

SvStringsDtor* pDBNameList = 0;

SvStringsDtor* 	pAuthFieldNameList = 0;
SvStringsDtor* 	pAuthFieldTypeList = 0;

/*--------------------------------------------------------------------
    Beschreibung:	UI beenden
 --------------------------------------------------------------------*/

/*N*/ ShellResource::ShellResource()
/*N*/ 	: Resource( SW_RES(RID_SW_SHELLRES) ),
/*N*/ 	aPostItPage( SW_RES( STR_POSTIT_PAGE ) ),
/*N*/ 	aPostItAuthor( SW_RES( STR_POSTIT_AUTHOR ) ),
/*N*/ 	aPostItLine( SW_RES( STR_POSTIT_LINE ) ),
/*N*/ 	aCalc_Syntax( SW_RES( STR_CALC_SYNTAX ) ),
/*N*/ 	aCalc_ZeroDiv( SW_RES( STR_CALC_ZERODIV ) ),
/*N*/ 	aCalc_Brack( SW_RES( STR_CALC_BRACK ) ),
/*N*/ 	aCalc_Pow( SW_RES( STR_CALC_POW ) ),
/*N*/ 	aCalc_VarNFnd( SW_RES( STR_CALC_VARNFND ) ),
/*N*/ 	aCalc_Overflow( SW_RES( STR_CALC_OVERFLOW ) ),
/*N*/ 	aCalc_WrongTime( SW_RES( STR_CALC_WRONGTIME ) ),
/*N*/ 	aCalc_Default( SW_RES( STR_CALC_DEFAULT ) ),
/*N*/ 	aCalc_Error( SW_RES( STR_CALC_ERROR ) ),
/*N*/ 	aGetRefFld_Up( SW_RES( STR_GETREFFLD_UP ) ),
/*N*/ 	aGetRefFld_Down( SW_RES( STR_GETREFFLD_DOWN ) ),
/*N*/ 	aStrAllPageHeadFoot( SW_RES( STR_ALLPAGE_HEADFOOT ) ),
/*N*/ 	aStrNone( SW_RES( STR_TEMPLATE_NONE )),
/*N*/ 	aFixedStr( SW_RES( STR_FIELD_FIXED )),
/*N*/ 	aTOXIndexName(			SW_RES(STR_TOI)),
/*N*/ 	aTOXUserName(			SW_RES(STR_TOU)),
/*N*/ 	aTOXContentName(		SW_RES(STR_TOC)),
/*N*/ 	aTOXIllustrationsName(	SW_RES(STR_TOX_ILL)),
/*N*/ 	aTOXObjectsName(		SW_RES(STR_TOX_OBJ)),
/*N*/ 	aTOXTablesName(			SW_RES(STR_TOX_TBL)),
/*N*/ 	aTOXAuthoritiesName(	SW_RES(STR_TOX_AUTH)),
/*N*/ 	sPageDescFirstName(		SW_RES(STR_PAGEDESC_FIRSTNAME)),
/*N*/ 	sPageDescFollowName(	SW_RES(STR_PAGEDESC_FOLLOWNAME)),
/*N*/ 	sPageDescName(			SW_RES(STR_PAGEDESC_NAME)),
/*N*/ 	pAutoFmtNameLst( 0 )
/*N*/ {
/*N*/ 	const USHORT nCount = FLD_DOCINFO_END - FLD_DOCINFO_BEGIN;
/*N*/
/*N*/ 	for(USHORT i = 0; i < nCount; ++i)
/*N*/ 	{
/*N*/ 		String* pNew = new SW_RESSTR(FLD_DOCINFO_BEGIN + i);
/*N*/ 		aDocInfoLst.Insert(pNew, aDocInfoLst.Count());
/*N*/ 	}
/*N*/
/*N*/ 	FreeResource();
/*N*/ }

/*N*/ ShellResource::~ShellResource()
/*N*/ {
/*N*/ 	if( pAutoFmtNameLst )
/*?*/ 		delete pAutoFmtNameLst, pAutoFmtNameLst = 0;
/*N*/ }

 String ShellResource::GetPageDescName( USHORT nNo, BOOL bIsFirst, BOOL bFollow )
 {
    String sRet( bIsFirst ? sPageDescFirstName
                          : bFollow ? sPageDescFollowName
                                    : sPageDescName );
    sRet.SearchAndReplaceAscii( "$(ARG1)", String::CreateFromInt32( nNo ));
    return sRet;
 }


 const String&  SwAuthorityFieldType::GetAuthTypeName(ToxAuthorityType eType)
 {
    if(!pAuthFieldTypeList)
    {
        pAuthFieldTypeList = new SvStringsDtor(AUTH_TYPE_END, 1);
        for(USHORT i = 0; i < AUTH_TYPE_END; i++)
            pAuthFieldTypeList->Insert(
                new String(SW_RES(STR_AUTH_TYPE_START + i)),
                                    pAuthFieldTypeList->Count());
    }
    return *pAuthFieldTypeList->GetObject(eType);
 }



}
